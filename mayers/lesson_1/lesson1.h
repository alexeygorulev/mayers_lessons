#pragma once
#include <iostream>
#include <ostream>
#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

template<typename T>
void func1(T &t) {
    std::cout << "Without const T " << type_id_with_cvr<T>().pretty_name() << "\n";
}

template<typename T>
void func2(const T &t) {
    std::cout << "with const T: " << type_id_with_cvr<T>().pretty_name() << "\n";
}


template<typename T>
void func3(T t) {
    std::cout << type_id_with_cvr<T>().pretty_name() << "\n";
}

void ArrTest() {
    const char name[] = "ArrTest";
    const char* ptr_name = name;
    std::cout << ptr_name << "\n";
}
