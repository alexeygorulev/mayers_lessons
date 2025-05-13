При передаче аргументов в std::thread аргументы копируются в поток. Если необходимо передавать ссылку в аргументах
то нужно использовать std::ref(аргумент).

семантика передачи параметров
class X {
public: void do_lengthy_work()

}

X my_x;
std::thread(&X::do_lengthy_work, &my_x)