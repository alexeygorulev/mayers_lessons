#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>

// ---------- 1. КОПИЯ -----------------
void demo_value_copy(int sum) // sum — локальная копия
{
    std::vector<std::thread> threads;
    threads.reserve(4);

    // Захватываем КОПИЕЙ (без &). У каждого потока будет свой sum.
    for (int n = 0; n < 4; ++n)
        threads.emplace_back([sum]() mutable {
            for (int i = 0; i < 1'000'000; ++i)
                ++sum; // модифицирует свою копию
        });

    for (auto &t: threads) t.join();

    std::cout << "[copy ] WAIT 4 000 000, REALLY " << sum
            << "  (главная копия не изменилась)\n";
}

// ---------- 2. ОБЩАЯ ССЫЛКА -----------
//   Вариант а) без защиты — гонка
void demo_shared_ref_race(int &sum) {
    std::vector<std::thread> threads;
    threads.reserve(4);

    for (int n = 0; n < 4; ++n)
        threads.emplace_back([&sum] {
            for (int i = 0; i < 1'000'000; ++i)
                ++sum; // гонка
        });

    for (auto &t: threads) t.join();

    std::cout << "[race ] WAIT 4 000 000, REALLY " << sum << '\n';
}

//   Вариант б) c защитой mutex — корректно
void demo_shared_ref_safe(int &sum) {
    std::vector<std::thread> threads;
    threads.reserve(4);

    std::mutex m;
    for (int n = 0; n < 4; ++n)
        threads.emplace_back([&] {
            for (int i = 0; i < 1'000'000; ++i) {
                std::lock_guard<std::mutex> lg(m);
                ++sum;
            }
        });

    for (auto &t: threads) t.join();

    std::cout << "[mutex] WAIT 4 000 000, REALLY " << sum << '\n';
}

//   Вариант в) c атомарикой — тоже корректно
void demo_shared_ref_atomic(std::atomic<int> &sum) {
    std::vector<std::thread> threads;
    threads.reserve(4);

    for (int n = 0; n < 4; ++n)
        threads.emplace_back([&sum] {
            for (int i = 0; i < 1'000'000; ++i)
                ++sum; // атомарная операция
        });

    for (auto &t: threads) t.join();

    std::cout << "[atomic] WAIT 4 000 000, REALLY " << sum << '\n';
}

int main() {
    // 1) Копия — глобальный sum не изменится
    demo_value_copy(0);

    // 2а) Общий int без синхронизации — гонка
    int sum_race = 0;
    demo_shared_ref_race(sum_race);

    // 2б) Общий int + mutex
    int sum_safe = 0;
    demo_shared_ref_safe(sum_safe);

    // 2в) Общий std::atomic<int>
    std::atomic<int> sum_atomic{0};
    demo_shared_ref_atomic(sum_atomic);
}
