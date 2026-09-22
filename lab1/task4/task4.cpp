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

int main()
{
    const int students = 4;
    const int subjects = 3;

    int** grades = allocateMatrix(students, subjects);

    for (int i = 0; i < students; ++i)
    {
        delete[] grades[i];
    }
    delete[] grades;

    return 0;
}
