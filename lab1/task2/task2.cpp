/**
 * @file task2.cpp
 * @brief Задание №2. Работа с одномерным динамическим массивом:
 *        new/delete, ссылка на указатель, защита от dangling pointer.
 *
 * Компиляция (C++14):
 *   g++ -std=c++14 -Wall -Wextra -o task2 task2.cpp
 */

#include <iostream>

int main()
{
    int n;
    std::cout << "Введите размер массива N: ";
    std::cin >> n;

    if (n <= 0)
    {
        std::cout << "Размер массива должен быть положительным." << std::endl;
        return 1;
    }

    // new int[N]{} — выделение памяти с инициализацией нулями
    int* arr = new int[n]{};

    std::cout << "Введите " << n << " целых чисел:" << std::endl;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i];
    }

    delete[] arr;
    arr = nullptr;

    return 0;
}
