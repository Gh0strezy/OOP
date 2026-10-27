/**
 * @file Matrix.cpp
 * @brief Реализация класса Matrix и перегруженных операторов.
 */

#include "Matrix.h"
#include <cmath>
#include <sstream>

namespace
{
/// Точность сравнения вещественных чисел.
const double EPS = 1e-9;

/// Сравнение двух чисел с допуском EPS.
bool nearlyEqual(double x, double y)
{
    return std::fabs(x - y) < EPS;
}

/// Число в строку (минус ноль печатается как 0).
std::string num(double value)
{
    std::ostringstream oss;
    oss << (value == 0.0 ? 0.0 : value);
    return oss.str();
}
} // namespace

int Matrix::objectCount = 0;

Matrix::Matrix()
    : data{{0.0, 0.0}, {0.0, 0.0}}, historyCount(0), historyTotal(0), accessCount(0)
{
    ++objectCount;
    record("Создана нулевая матрица " + toString());
}

Matrix::Matrix(double a, double b, double c, double d)
    : data{{a, b}, {c, d}}, historyCount(0), historyTotal(0), accessCount(0)
{
    ++objectCount;
    record("Создана матрица " + toString());
}

Matrix::Matrix(double scalar)
    : data{{scalar, 0.0}, {0.0, scalar}}, historyCount(0), historyTotal(0), accessCount(0)
{
    ++objectCount;
    record("Создана скалярная матрица " + toString());
}

Matrix::Matrix(const Matrix& other)
    : data{{other.data[0][0], other.data[0][1]}, {other.data[1][0], other.data[1][1]}},
      historyCount(other.historyCount),
      historyTotal(other.historyTotal),
      accessCount(0)
{
    ++objectCount;
    for (int i = 0; i < historyCount; ++i)
    {
        history[i] = other.history[i];
    }
}

Matrix::~Matrix()
{
    --objectCount;
    if (objectCount == 0)
    {
        std::cout << "Деструктор: последняя матрица уничтожена, "
                     "активных объектов Matrix не осталось." << std::endl;
    }
}

int Matrix::getObjectCount() { return objectCount; }

void Matrix::record(const std::string& text) const
{
    ++historyTotal;
    if (historyCount == MAX_HISTORY)
    {
        // Массив заполнен: сдвигаем записи на одну влево, самая старая вытесняется.
        for (int i = 1; i < MAX_HISTORY; ++i)
        {
            history[i - 1] = history[i];
        }
        --historyCount;
    }
    history[historyCount] = text;
    ++historyCount;
}

std::string Matrix::toString() const
{
    return "[[" + num(data[0][0]) + ", " + num(data[0][1]) + "], ["
               + num(data[1][0]) + ", " + num(data[1][1]) + "]]";
}

double Matrix::at(int row, int col) const
{
    ++accessCount;
    if (row < 0 || row > 1 || col < 0 || col > 1)
    {
        std::cout << "Ошибка: индекс (" << row << ", " << col
                  << ") вне границ матрицы 2x2." << std::endl;
        return 0.0;
    }
    return data[row][col];
}

double Matrix::determinant() const
{
    ++accessCount;
    return data[0][0] * data[1][1] - data[0][1] * data[1][0];
}

bool Matrix::isInvertible() const
{
    return !nearlyEqual(determinant(), 0.0);
}

Matrix::operator bool() const
{
    return isInvertible();
}

int Matrix::getAccessCount() const { return accessCount; }
int Matrix::getHistorySize() const { return historyCount; }
int Matrix::getHistoryTotal() const { return historyTotal; }

int Matrix::compareByDeterminant(const Matrix& other) const
{
    double x = determinant();
    double y = other.determinant();
    int result = nearlyEqual(x, y) ? 0 : (x < y ? -1 : 1);

    record("Сравнение определителей: det = " + num(x) + " и det = " + num(y)
           + " -> " + (result < 0 ? "меньше" : (result > 0 ? "больше" : "равны")));
    return result;
}

void Matrix::printHistory() const
{
    std::cout << "История операций (хранится " << historyCount
              << " из " << historyTotal << " записанных):" << std::endl;
    if (historyCount == 0)
    {
        std::cout << "  (пусто)" << std::endl;
    }
    if (historyTotal > historyCount)
    {
        std::cout << "  (более старые записи вытеснены, показаны последние "
                  << historyCount << ")" << std::endl;
    }
    for (int i = 0; i < historyCount; ++i)
    {
        // Номер записи считаем от начала всей истории, а не от начала массива.
        std::cout << "  " << (historyTotal - historyCount + i + 1)
                  << ". " << history[i] << std::endl;
    }
}
