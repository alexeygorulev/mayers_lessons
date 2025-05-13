#include <iostream>
#include <thread>

struct func {
    int &i;
    size_t sum = 0;

    func(int &i) : i(i) {
    }

    void operator()() {
        for (size_t j = 0; j <= 1000000; j++) {
            sum = j;
        }
        std::cout << "sum = " << sum << std::endl;
    }
};

class thread_guard {
    std::thread &t;

public:
    explicit thread_guard(std::thread &t) : t(t) {
    }

    ~thread_guard() {
        if (t.joinable()) {
            t.join();
        }
    }

    thread_guard(const thread_guard &) = delete;

    thread_guard &operator=(const thread_guard &) = delete;
};


void test1(int &u) {
    for (size_t j = 0; j <= 1000000; j++) {
    }
    u += 4;
    std::cout << u << std::endl;
}

void testMove(std::string &&u) {
    std::cout << u << std::endl;
}

class X {
public:
    void some_work(int i) {
        for (size_t j = 0; j <= 100; j++) {
        }

        std::cout << "X: " << i << std::endl;
    }
};

int main() {
    int u = 2;
    int dummy = 0;
    X my_x;
    std::string l = "24";
    std::thread t1{func{dummy}};
    std::thread t2(test1, std::ref(u));
    std::thread t3(&X::some_work, my_x, 10);
    std::thread t4(testMove, std::move(l));

    t3.join();
    std::cout << "FROM MAIN: " << u << std::endl;
    t2.join();


    thread_guard g1(t1);
    thread_guard g2(t4);
    std::cout << "after t1.join()" << std::endl;
    return 0;
}
