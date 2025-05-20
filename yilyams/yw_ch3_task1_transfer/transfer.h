#ifndef TRANSFER_H
#define TRANSFER_H
#include <mutex>


struct Account {
    std::mutex m;
    int balance{};
};


#endif //TRANSFER_H
