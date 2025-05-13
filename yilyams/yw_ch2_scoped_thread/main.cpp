#include <iostream>
#include <thread>
#include <chrono>

void worker() {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

class scoped_thread {
public:
    explicit scoped_thread(std::thread t): t_(std::move(t)) {
    }

    ~scoped_thread() {
        if (t_.joinable()) {
            t_.join();
        } else {
            std::terminate();
        }
    }

    scoped_thread(const scoped_thread &) = delete;

    scoped_thread &operator=(const scoped_thread &) = delete;

private:
    std::thread t_;
};

void run_leaking_thread() {
    std::thread t1(worker);
}

void run_scoped() {
    scoped_thread t1{std::thread(worker)};
    std::cout << "Correct" << std::endl;
}

int main() {
    run_scoped();
    std::cout << "Hello, World!" << std::endl;
    run_scoped();
    run_leaking_thread();
    return 0;
}
