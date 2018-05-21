#pragma once 

#include <memory>
#include "state.h"

template <typename T>
class Future {
public:
    explicit Future(const std::shared_ptr< SharedState<T> >& state): state(state) {}
    Future(const Future& other): state(other.state) {}
    Future(Future& other): state(other.state) {}

    const T& Get()
    {
        state->Wait();
        return *state->GetValue();
    };

    bool TryGet(T& value)
    {
        T* current = state->GetValue();
        if(current == nullptr) {
            return false;
        }
        value = *current;
        return true;
    };

private:
    std::shared_ptr< SharedState <T> > state;
};