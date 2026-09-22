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

/**
 * @brief Выводит массив на экран через range-based for и auto.
 * @param arr Ссылка на константный массив (только чтение, менять не нужно).
 */
void printArray(const int (&arr)[ARRAY_SIZE])
{
    for (const auto& x : arr)
    {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
}

/**
 * @brief Меняет местами два элемента массива по их индексам.
 * @param arr Ссылка на массив, в котором происходит обмен.
 * @param i   Индекс первого элемента.
 * @param j   Индекс второго элемента.
 *
 * Индексы дополнительно проверяются на выход за границы, чтобы функция
 * не привела к неопределённому поведению при неверном вызове.
 */
void swapElements(int (&arr)[ARRAY_SIZE], int i, int j)
{
    if (i < 0 || i >= ARRAY_SIZE || j < 0 || j >= ARRAY_SIZE)
    {
        std::cout << "Ошибка: индекс вне диапазона массива." << std::endl;
        return;
    }

    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int numbers[ARRAY_SIZE];
    fillArray(numbers);

    std::cout << "Исходный массив:" << std::endl;
    printArray(numbers);

    std::cout << "Меняем местами элементы с индексами 0 и 9:" << std::endl;
    swapElements(numbers, 0, 9);
    printArray(numbers);

    return 0;
}
