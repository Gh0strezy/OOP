/**
 * @file task1.cpp
 * @brief Задание №1. Работа со статическим массивом из 10 целых чисел.
 *
 * Компиляция (C++14):
 *   g++ -std=c++14 -Wall -Wextra -o task1 task1.cpp
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

const int ARRAY_SIZE = 10;

/**
 * @brief Заполняет массив случайными числами в диапазоне [-9, 9].
 * @param arr Ссылка на массив из 10 int. Изменяется на месте.
 */
void fillArray(int (&arr)[ARRAY_SIZE])
{
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        arr[i] = std::rand() % 19 - 9; // числа от -9 до 9
    }
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int numbers[ARRAY_SIZE];
    fillArray(numbers);

    return 0;
}
