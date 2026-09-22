/**
 * @file task4.cpp
 * @brief Задание №4. Система учёта оценок студентов на основе
 *        двумерного динамического массива (int**).
 *
 * Компиляция (C++14):
 *   g++ -std=c++14 -Wall -Wextra -o task4 task4.cpp
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

/**
 * @brief Выделяет память под двумерный массив (матрицу) rows x cols.
 * @param rows Количество строк (например, количество студентов).
 * @param cols Количество столбцов (например, количество предметов).
 * @return Указатель на массив указателей — саму матрицу.
 */
int** allocateMatrix(int rows, int cols)
{
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = new int[cols];
    }
    return matrix;
}

/**
 * @brief Заполняет матрицу случайными оценками в диапазоне [2, 5].
 * @param matrix Матрица, которую нужно заполнить.
 * @param rows   Количество строк.
 * @param cols   Количество столбцов.
 */
void fillMatrix(int** matrix, int rows, int cols)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            matrix[i][j] = std::rand() % 4 + 2; // оценки от 2 до 5
        }
    }
}

/**
 * @brief Красиво выводит матрицу оценок на экран.
 * @param matrix      Матрица для вывода.
 * @param rows        Количество строк.
 * @param cols        Количество столбцов.
 * @param showBorders Если true — вокруг матрицы рисуется рамка из '*'.
 *                     По умолчанию true.
 * @param title       Заголовок, который печатается перед матрицей.
 *                     По умолчанию "Matrix".
 */
void printMatrix(int** matrix, int rows, int cols, bool showBorders = true, std::string title = "Matrix")
{
    std::cout << title << std::endl;

    int width = cols * 3 + 1;

    if (showBorders)
    {
        for (int k = 0; k < width; ++k) std::cout << '*';
        std::cout << std::endl;
    }

    for (int i = 0; i < rows; ++i)
    {
        if (showBorders) std::cout << "* ";

        for (int j = 0; j < cols; ++j)
        {
            std::cout << matrix[i][j] << "  ";
        }

        if (showBorders) std::cout << '*';
        std::cout << std::endl;
    }

    if (showBorders)
    {
        for (int k = 0; k < width; ++k) std::cout << '*';
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

/**
 * @brief Освобождает память, выделенную под матрицу.
 * @param matrix Матрица для освобождения.
 * @param rows   Количество строк (нужно, чтобы знать, сколько
 *               вложенных массивов освобождать).
 *
 * Сначала освобождаются вложенные массивы (каждая строка), а затем
 * массив указателей на них — именно в таком порядке, иначе
 * получится утечка памяти.
 */
void freeMatrix(int** matrix, int rows)
{
    for (int i = 0; i < rows; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    const int students = 4;
    const int subjects = 3;

    int** grades = allocateMatrix(students, subjects);
    fillMatrix(grades, students, subjects);

    // 1. Вызов без дополнительных параметров (используются значения по умолчанию)
    printMatrix(grades, students, subjects);

    // 2. Вызов только с заголовком
    printMatrix(grades, students, subjects, true, "Оценки студентов");

    // 3. Вызов со всеми параметрами (без рамки)
    printMatrix(grades, students, subjects, false, "Оценки студентов (без рамки)");

    freeMatrix(grades, students);
    grades = nullptr;

    return 0;
}
