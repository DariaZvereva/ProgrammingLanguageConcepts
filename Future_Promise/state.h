#pragma once

#include <mutex>
#include <condition_variable>
#include <exception>
#include <functional>
#include <iostream>
#include "future.h"

template<typename T>
class Future;

struct ResetPromiseValueException : public std::exception
{
    const char* what() const throw ()
    {
        return "You have already set value";
    }
};


template<typename T>
class SharedState {
public:
    SharedState(): exception(nullptr) {}

    void Wait()
    {
        std::unique_lock<std::mutex> lock(critical);
        cv.wait(lock, [this]() {
            return value.get() != nullptr || exception != nullptr;
        });
    };

    T* GetValue()
    {
        std::lock_guard<std::mutex> guard(critical);
        if(exception != nullptr) {
            std::rethrow_exception(exception);
        }
        return value.get();
    };

    T* GetOrSetValue(const T& val)
    {
       
    };

    void SetValue(const T& val)
    {
        std::lock_guard<std::mutex> lock(critical);
        //std::cout << "QEQEQ" << std::endl;
        if(value != nullptr || exception != nullptr) {
            throw ResetPromiseValueException {};
        }
        value = std::move(std::make_unique<T>(val));
        cv.notify_all();
    };

    void SetException()
    {
        std::lock_guard<std::mutex> lock(critical);
        exception = std::current_exception();
        cv.notify_all();
    };

    void TryThrow() const
    {
        std::lock_guard<std::mutex> guard(critical);
        if(exception != nullptr) {
            std::rethrow_exception(exception);
        }
    };

private:
    std::unique_ptr<T> value;
    std::exception_ptr exception;
    std::mutex critical;
    std::condition_variable cv;
};

template<typename T, typename R>
class ChainState: public SharedState<R> {
public:
    ChainState(Future<T> future_, std::function<R(const T&)> task):
        future(future_),
        then_process(task)
    {}

    virtual void Wait() override { return; }

    virtual R* GetValue() override {
        std::lock_guard<std::mutex> guard(this->critical);
        if(this->exception != nullptr) {
            std::rethrow_exception(this->exception);
        }
        if(this->value != nullptr) {
            return this->value.get();
        }
        R val = worker(future.get());
        this->value = std::move(std::make_unique<T>(val));
        this->cv.notify_all();
        return this->value.get();
    };

private:
    Future<T> future;
    std::function<R(const T&)> then_process;
};