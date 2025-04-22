#include <iostream>
#include "lesson1.h"

template<typename T>
void f(T arr) {
    std::cout << type_id_with_cvr<T>().pretty_name() << "\n";
}

template<typename T>
void f2(T &arr) {
    std::cout << type_id_with_cvr<T>().pretty_name() << "\n";
}


int main() {
    int i = 2;
    const int ci = 4;
    const int &cli = i;
    int &li = i;

    //При аргументе функции без const срезаются только ссылки. Параметр шаблона может быть константным и не константным
    func1(cli);
    func1(li);

    // При аргументе функции с const срезается еще константность. Параметр шаблона всегда чистый
    func2(cli);
    func2(li);

    // При передаче по значению происходит копирование и параметр шаблона всегда не константный.
    func3(cli);
    func3(li);

    ArrTest();

    const char is[] = "lol";
    //Передача по значению передает указатель на массив
    f(is);
    //Передача по ссылке массива передает ссылку на массив
    f2(is);

    //Функции передают всегда указатель на функцию

    // В auto есть подводные камни с initialize_list.
    // из-за фигурных скобок авто приводит к initialize_list
    auto x = {3};


    // можно возвращать auto из функции, но также надо быть осторожным
    // т.к. если возврат через фигурные скобки, то возвращается initialize_list
    //
    return 0;
}
