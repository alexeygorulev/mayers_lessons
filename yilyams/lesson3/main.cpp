#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include "test.h"

std::list<int> some_list;
std::mutex m;


void add_to_list(int num) {
    std::lock_guard<std::mutex> lock(m);
    some_list.push_back(num);
}

bool list_contains(int num) {
    std::lock_guard<std::mutex> lock(m);
    return std::find(some_list.begin(), some_list.end(), num) != some_list.end();
}


class some_data {
    int a;
    std::string b;

public:
    void do_something() {
    }
};

class data_wrapper {
private:
    some_data data;
    std::mutex m;

public:
    template<typename Function>
    void process_data(Function func) {
        std::lock_guard<std::mutex> lock(m);
        func(data);
    }
};

some_data *unprotected;

void malicious_function(some_data &protected_data) {
    unprotected = &protected_data;
}

data_wrapper x;

void foo() {
    x.process_data(malicious_function);
    unprotected->do_something();
}

hierarchial_mutex high_level_mutex(10000);
hierarchial_mutex low_level_mutex(5000);
hierarchial_mutex other_mutex(6000);


int do_low_level_stuff() {
    return 0;
};

int low_level_func() {
    std::lock_guard lk(low_level_mutex);
    return do_low_level_stuff();
}

void high_level_stuff(int some_param) {
}

void high_level_func() {
    std::lock_guard lk(high_level_mutex);
    high_level_stuff(5);
}

void threadA() {
    high_level_func();
}

void do_other_stuff() {
}

void other_stuff() {
    high_level_func();
    do_other_stuff();
}

void threadB() {
    std::lock_guard lk(other_mutex);
    other_stuff();
}

int main() {
    testFunc();

    return 0;
}
