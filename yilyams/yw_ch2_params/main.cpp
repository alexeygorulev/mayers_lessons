#include <iostream>
#include <thread>

void add_to(int &sum) {
    for (size_t i = 0; i < 1000000; i++) {
        sum++;
    }
}

int main() {
    int sum = 0;
    std::thread t1(add_to, std::ref(sum));
    t1.join();
    std::cout << sum << std::endl;
    return 0;
}
