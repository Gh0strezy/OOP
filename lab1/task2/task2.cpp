/**
 * @file task2.cpp
 * @brief Задание №2. Работа с одномерным динамическим массивом:
 *        new/delete, ссылка на указатель, защита от dangling pointer.
 *
 * Компиляция (C++14):
 *   g++ -std=c++14 -Wall -Wextra -o task2 task2.cpp
 */

#include <iostream>

/**
 * @brief Обрабатывает динамический массив: ищет первый отрицательный
 *        элемент.
 *
 * @param arr  Ссылка на указатель на массив (int*&). Ссылка нужна,
 *             чтобы в дальнейшем функция могла заменить сам указатель
 *             на новый блок памяти, и это было видно вызывающему коду.
 * @param size Текущий размер массива, на который указывает arr.
 * @return Новый размер массива после возможной обрезки.
 *
 * Если отрицательный элемент найден, создаётся новый динамический
 * массив, в который копируются все элементы до него, старая память
 * освобождается через delete[], а указатель arr переставляется на
 * новый массив.
 */
int process(int*& arr, int size)
{
    int negativeIndex = -1;

    for (int i = 0; i < size; ++i)
    {
        if (arr[i] < 0)
        {
            negativeIndex = i;
            break;
        }
    }

    if (negativeIndex == -1)
    {
        std::cout << "Отрицательных элементов не найдено, массив не изменён." << std::endl;
        return size;
    }

    std::cout << "Первый отрицательный элемент найден на позиции " << negativeIndex << std::endl;

    int newSize = negativeIndex;
    int* newArr = new int[newSize];

    for (int i = 0; i < newSize; ++i)
    {
        newArr[i] = arr[i];
    }

    delete[] arr;  // освобождаем старую память
    arr = newArr;  // указатель теперь смотрит на новый массив

    return newSize;
}

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

    int currentSize = process(arr, n);

    std::cout << "Результат:" << std::endl;
    for (int i = 0; i < currentSize; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;

    delete[] arr;
    arr = nullptr;

    return 0;
}
