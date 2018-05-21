#pragma once

#include <mutex>
#include <condition_variable>
#include <exception>


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
        std::lock_guard<std::mutex> guard(critical);
        if(exception != nullptr) {
            std::rethrow_exception(exception);
        }
        if(value != nullptr) {
            return value.get();
        }
        value = std::move(std::make_unique<T>(val));
        cv.notify_all();
        return value.get();
    };

    void SetValue(const T& val)
    {
        std::lock_guard<std::mutex> lock(critical);
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