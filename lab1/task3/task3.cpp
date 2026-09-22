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

/**
 * @brief Безопасный доступ к элементу массива по индексу.
 * @param arr   Ссылка на SafeArray, к которому обращаемся.
 * @param index Индекс запрашиваемого элемента.
 * @return Ссылка на элемент arr.data[index], если индекс корректен;
 *         иначе — ссылка на статическую переменную-заглушку.
 *
 * Благодаря тому, что функция возвращает int&, её можно использовать
 * слева от знака "=", т.е. как lvalue: getElement(arr, i) = 999;
 * Если индекс некорректен, программа не падает: печатается сообщение
 * об ошибке и возвращается ссылка на "заглушку".
 */
int& getElement(SafeArray& arr, int index)
{
    static int dummy = 0; // статическая переменная-заглушка

    if (index < 0 || index >= arr.size)
    {
        std::cout << "Ошибка: индекс " << index
                  << " выходит за границы массива размером " << arr.size << std::endl;
        dummy = 0;
        return dummy;
    }

    return arr.data[index];
}

/**
 * @brief Выводит содержимое SafeArray на экран.
 * @param arr Константная ссылка на SafeArray (печать не меняет данные).
 */
void printSafe(const SafeArray& arr)
{
    for (int i = 0; i < arr.size; ++i)
    {
        std::cout << arr.data[i] << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    SafeArray myArr = createArray(5);

    for (int i = 0; i < myArr.size; ++i)
    {
        getElement(myArr, i) = (i + 1) * 10; // заполняем массив: 10 20 30 40 50
    }

    std::cout << "Исходный массив:" << std::endl;
    printSafe(myArr);

    // Демонстрация использования getElement слева от знака "="
    getElement(myArr, 2) = 999;
    std::cout << "После getElement(myArr, 2) = 999:" << std::endl;
    printSafe(myArr);

    // Попытка выйти за границы массива — программа не падает
    getElement(myArr, 100) = 12345;

    delete[] myArr.data;
    myArr.data = nullptr;

    return 0;
}
