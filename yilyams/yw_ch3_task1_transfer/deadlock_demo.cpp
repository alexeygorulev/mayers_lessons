//
// Created by alexe on 20.05.2025.
//

#include "deadlock_demo.h"

#include <iostream>
#include <mutex>
#include <thread>

#include "transfer.h"

inline void transfer_safe(Account &a, Account &b, int money) {
    std::scoped_lock lg(a.m, b.m);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    a.balance += money;
    b.balance -= money;
}

void transfer_AB(Account &a, Account &b, int money) // порядок A→B
{
    std::lock_guard lg1(a.m);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::lock_guard lg2(b.m);
    a.balance -= money;
    b.balance += money;
}

void transfer_BA(Account &a, Account &b, int money) // порядок B→A
{
    std::lock_guard lg1(b.m);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::lock_guard lg2(a.m);
    b.balance -= money;
    a.balance += money;
}


void deadlock_demo::demo() {
    Account a;
    Account b;
    // std::thread t1(transfer_AB, std::ref(a), std::ref(b), 100);
    // std::thread t2(transfer_BA, std::ref(a), std::ref(b), 200);

    std::thread t1(transfer_safe, std::ref(a), std::ref(b), 100);
    std::thread t2(transfer_safe, std::ref(a), std::ref(b), 200);
    t1.join();
    t2.join();
    std::cout << a.balance << std::endl;
    std::cout << b.balance << std::endl;
}
