/**
 * @file task3.cpp
 * @brief Задание №3. "Безопасный" динамический массив на основе
 *        структуры SafeArray.
 *
 * Компиляция (C++14):
 *   g++ -std=c++14 -Wall -Wextra -o task3 task3.cpp
 */

#include <iostream>

/**
 * @brief Структура "безопасного" массива: указатель на данные + размер.
 */
struct SafeArray
{
    int* data; ///< Указатель на динамически выделенный массив
    int size;  ///< Текущий размер массива
};

/**
 * @brief Создаёт новый SafeArray заданного размера.
 * @param size Требуемый размер массива.
 * @return Структура SafeArray, возвращённая по значению.
 *
 * Память инициализируется нулями (new int[size]{}).
 */
SafeArray createArray(int size)
{
    SafeArray arr;
    arr.size = size;
    arr.data = new int[size]{};
    return arr;
}

int main()
{
    SafeArray myArr = createArray(5);

    delete[] myArr.data;
    myArr.data = nullptr;

    return 0;
}
