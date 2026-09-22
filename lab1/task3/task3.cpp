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

/**
 * @brief Изменяет размер массива с N элементов на M.
 * @param arr Ссылка на SafeArray, который нужно изменить (текущий
 *            размер arr.size играет роль "N" из условия задания).
 * @param M   Новый желаемый размер массива.
 *
 * Если M < N (массив уменьшается) — на экран выводятся элементы,
 * которые будут "потеряны" при изменении размера.
 * Если M > N (массив увеличивается) — новые элементы инициализируются
 * нулями по умолчанию.
 * Старая память корректно освобождается через delete[].
 */
void reSizeArray(SafeArray& arr, int M)
{
    int N = arr.size;

    if (M == N)
    {
        std::cout << "Новый размер совпадает со старым, изменений не требуется." << std::endl;
        return;
    }

    int* newData = new int[M]{};

    if (M < N)
    {
        std::cout << "Массив уменьшается, удаляются элементы: ";
        for (int i = M; i < N; ++i)
        {
            std::cout << arr.data[i] << ' ';
        }
        std::cout << std::endl;

        for (int i = 0; i < M; ++i)
        {
            newData[i] = arr.data[i];
        }
    }
    else // M > N, массив увеличивается
    {
        for (int i = 0; i < N; ++i)
        {
            newData[i] = arr.data[i];
        }
        // Элементы с индексами [N, M) уже равны 0 благодаря new int[M]{}
    }

    delete[] arr.data;
    arr.data = newData;
    arr.size = M;
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

    std::cout << "Уменьшаем массив с 5 до 3 элементов:" << std::endl;
    reSizeArray(myArr, 3);
    printSafe(myArr);

    std::cout << "Увеличиваем массив с 3 до 6 элементов:" << std::endl;
    reSizeArray(myArr, 6);
    printSafe(myArr);

    delete[] myArr.data;
    myArr.data = nullptr;

    return 0;
}
