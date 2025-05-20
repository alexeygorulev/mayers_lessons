#pragma once
#include <limits.h>
#include <mutex>

class hierarchial_mutex {
    std::mutex internal_mutex;
    unsigned long const hierarchy_value;
    unsigned long  previous_hierarchy_value;
    static thread_local unsigned long this_thread_hierarchy_value;

    void check_for_hierarchy_violation() const {
        if (this_thread_hierarchy_value <= hierarchy_value) {
            throw std::logic_error("hierarchy violation");
        }
    }

    void update_hierarchy_value() {
        previous_hierarchy_value = this_thread_hierarchy_value;
        this_thread_hierarchy_value = hierarchy_value;
    }

public:
    explicit hierarchial_mutex(unsigned long hierarchy_value) : hierarchy_value(hierarchy_value),
                                                                previous_hierarchy_value(0) {
    }

    void lock() {
        check_for_hierarchy_violation();
        internal_mutex.lock();
        update_hierarchy_value();
    }

    void unlock() {
        if (this_thread_hierarchy_value != hierarchy_value) {
            throw std::logic_error("mutex hierarchy violation");
        }
        this_thread_hierarchy_value = previous_hierarchy_value;
        internal_mutex.unlock();
    }

    bool try_lock() {
        check_for_hierarchy_violation();
        if (!internal_mutex.try_lock()) {
            return false;
        }
        update_hierarchy_value();
        return true;
    }
};

thread_local unsigned long hierarchial_mutex::this_thread_hierarchy_value(ULONG_MAX);
