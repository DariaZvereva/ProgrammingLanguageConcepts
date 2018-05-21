#include "future.h"
#include "promise.h"
#include <iostream>
#include <thread>
#include <condition_variable>
#include <assert.h>
#include <unistd.h>

void Test1() {
    SharedState<int> state_;
    int value_ = 777;

    std::thread thread1([&state_, value_]() {
        state_.Wait();
        assert(value_ ==  *state_.GetValue());
    });

    sleep(2);
    state_.SetValue(value_);

    thread1.join();
}

int main()
{
    Test1();
    std::cout << "HELLO!" << std::endl;
}