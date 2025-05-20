#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::chrono_literals;

// ------------------ модель работы ------------------
inline void worker(int id, int ms_work) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms_work));
    std::cout << "T" << id << " done work\n";
}

// ---------------------------------------------------

// ----- ① один общий мьютекс ------------------------
std::mutex g;

inline void task_global(int id) {
    std::lock_guard<std::mutex> lg(g); // крит. секция = ВСЁ
    worker(id, 10); // 50 мс имитация
    worker(id, 5); // 50 мс имитация
    worker(id, 1); // 50 мс имитация
}

// ----- ② иерархия трёх мьютексов -------------------
#include "hierarchial_mutex.h"

hierarchial_mutex m_db(10000);
hierarchial_mutex m_cache(8000);
hierarchial_mutex m_log(500);

inline void task_hier(int id) {
    std::lock_guard<hierarchial_mutex> lg1(m_db);
    worker(id, 10); // основная работа с базой

    {
        std::lock_guard<hierarchial_mutex> lg2(m_cache);
        worker(id, 5); // кэш-обновление
    } {
        std::lock_guard<hierarchial_mutex> lg3(m_log);
        worker(id, 1); // быстрая запись в лог
    }
}

// ----------------- launch helper -------------------
template<typename F>
void run(const char *label, F func) {
    std::cout << "=== " << label << " ===\n";
    auto t0 = std::chrono::steady_clock::now();
    std::thread t1(func, 1), t2(func, 2), t3(func, 3), t4(func, 4);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    auto dt = std::chrono::steady_clock::now() - t0;
    std::cout << "Elapsed: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(dt).count()
            << " ms\n\n";
}

inline void task_hier_better(int id) { {
        // 1) Коротко блокируем базу
        std::lock_guard<hierarchial_mutex> lg1(m_db);
        worker(id, 10); // чисто DB-доступ
    } // m_db освобождён

    {
        // 2) Работаем с кэшем
        std::lock_guard<hierarchial_mutex> lg2(m_cache);
        worker(id, 1);
    } {
        // 3) Быстрая запись в лог
        std::lock_guard<hierarchial_mutex> lg3(m_log);
        worker(id, 1);
    }
}


inline void testFunc() {
    run("global mutex", task_global);
    run("hierarchical mutex", task_hier);
    run("task_hier_better", task_hier_better);
}
