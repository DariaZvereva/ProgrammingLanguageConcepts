#pragma once

#include "future.h"
#include <memory>


template <typename T>
class Promise {
public:
    Promise(): state(new SharedState<T>) {};
    Promise(Promise<T>&& other): state(other.state) {};
    Promise(const Promise& other) = delete;
    ~Promise() { }

    void Set(const T& value) { state->SetValue(value); }
    void SetException(){ state->SetException(); }

    Future<T> Result() { return Future<T>(state); }

private:
    std::shared_ptr<SharedState<T>> state;
};
