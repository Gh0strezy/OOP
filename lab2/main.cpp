/**
 * @file main.cpp
 * @brief Тестирование класса Wallet: создание объектов разными
 *        конструкторами, корректные и некорректные операции, проверка
 *        независимости объектов друг от друга.
 *
 * Компиляция (C++14):
 *   g++ -std=c++14 -Wall -Wextra -o wallet Wallet.cpp main.cpp
 */

#include "Wallet.h"
#include <iostream>

int main()
{
    std::cout << "=== Создание объектов ===" << std::endl;

    Owner alice("Alice", "alice@mail.ru");   // отдельный объект класса Owner

    Wallet w1;                                    // конструктор по умолчанию
    Wallet w2(alice, Currency::USD);              // владелец + валюта (без начального баланса)
    Wallet w3(Owner("Bob"), 500.0, Currency::USD); // владелец + начальный баланс + валюта

    std::cout << "Создано кошельков: " << Wallet::getObjectCount() << std::endl << std::endl;

    std::cout << "=== Начальное состояние ===" << std::endl;
    w1.printInfo();
    w2.printInfo();
    w3.printInfo();

    return 0;
}
