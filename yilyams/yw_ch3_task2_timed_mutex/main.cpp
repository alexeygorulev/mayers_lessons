#include <iostream>
#include <mutex>
#include <thread>

struct Resource {
    std::string name = "NAME";
    std::timed_mutex mutex;

    void use_resource() {
        std::unique_lock lock(mutex, std::defer_lock);

        if (lock.try_lock_for(std::chrono::microseconds(80))) {
            std::cout << std::this_thread::get_id() << " AVAILABLE" << std::endl;
            std::this_thread::sleep_for(std::chrono::microseconds(450));
        } else {
            std::cout << std::this_thread::get_id() << ": Resource is locked\n";
        }
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    Resource resource;

    std::thread t1(&Resource::use_resource, std::ref(resource)),
            t2(&Resource::use_resource, std::ref(resource)),
            t3(&Resource::use_resource, std::ref(resource)),
            t4(&Resource::use_resource, std::ref(resource)),
            t5(&Resource::use_resource, std::ref(resource)),
            t6(&Resource::use_resource, std::ref(resource));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    return 0;
}
