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

    sleep(1);
    state_.SetValue(value_);

    std::thread thread2([&state_, value_]() {
        state_.Wait();
        assert(value_ ==  *state_.GetValue());
    });

    thread1.join();
    thread2.join();
}


// падает при попытке переустановить значение
void Test2() {
    SharedState<int> state_;
    int value_ = 777;

    std::thread thread1([&state_, value_]() {
        state_.Wait();
        assert(value_ ==  *state_.GetValue());
    });

    sleep(1);
    state_.SetValue(value_);

    std::thread thread2([&state_, value_]() {
        state_.Wait();
        assert(value_ ==  *state_.GetValue());
    });

    int value2_ = 888;
    state_.SetValue(value2_);

    thread1.join();
    thread2.join();
}



int main()
{
    Test1();
    std::cout << "OK 1!" << std::endl;
    Test2();
    std::cout << "OK 2!" << std::endl;
}