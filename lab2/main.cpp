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

    std::cout << std::endl << "=== Корректные операции ===" << std::endl;
    w1.deposit(1000.0);
    w2.deposit(200.0);
    w3.withdraw(100.0);
    w2.transferTo(w3, 50.0); // перевод между двумя кошельками одной валюты (USD)

    std::cout << std::endl << "=== Некорректные операции ===" << std::endl;
    w1.deposit(-50.0);        // отрицательная сумма — должно быть отклонено
    w2.withdraw(100000.0);    // недостаточно средств — должно быть отклонено
    w3.block();
    w3.deposit(10.0);         // кошелёк заблокирован — должно быть отклонено
    w3.unblock();
    w1.transferTo(w2, 10.0);  // разные валюты (RUB -> USD) — должно быть отклонено
    Owner broken("", "wrong-email");  // пустое имя и некорректный email — Owner исправит состояние сам
    std::cout << "Owner после исправления: " << broken.getName()
              << ", email указан: " << (broken.hasEmail() ? "да" : "нет") << std::endl;

    std::cout << std::endl << "=== Состояние после операций (объекты сохранили корректность) ===" << std::endl;
    w1.printInfo();
    w2.printInfo();
    w3.printInfo();

    std::cout << std::endl << "=== Проверка независимости объектов ===" << std::endl;
    std::cout << "Баланс w2 и w3 до изменения w1:" << std::endl;
    std::cout << "w2: " << w2.getBalance() << " " << currencyToString(w2.getCurrency()) << std::endl;
    std::cout << "w3: " << w3.getBalance() << " " << currencyToString(w3.getCurrency()) << std::endl;

    w1.deposit(99999.0); // сильно меняем состояние только w1
    alice.changeEmail("alice.new@mail.ru"); // меняем исходный Owner — копия внутри w2 не меняется

    std::cout << "После изменения w1 — балансы w2 и w3 не изменились:" << std::endl;
    std::cout << "w2: " << w2.getBalance() << " " << currencyToString(w2.getCurrency()) << std::endl;
    std::cout << "w3: " << w3.getBalance() << " " << currencyToString(w3.getCurrency()) << std::endl;
    std::cout << "Email внутри w2: " << w2.getOwner().getEmail()
              << " (исходный alice: " << alice.getEmail() << ")" << std::endl;

    std::cout << std::endl << "Текущее количество объектов: " << Wallet::getObjectCount() << std::endl;

    return 0;
}
