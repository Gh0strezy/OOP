/**
 * @file Matrix.h
 * @brief Объявление класса Matrix — матрица 2x2 с перегруженными операторами.
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>

/**
 * @brief Матрица 2x2 с историей выполненных над ней операций.
 *
 * Элементы хранятся в массиве data[2][2]. Класс перегружает:
 *  - унарные операторы ++ и -- (префиксные и постфиксные): изменяют
 *    ВСЕ элементы матрицы на +1 или -1;
 *  - арифметическое присваивание +=, -=, *=, /=;
 *  - бинарные +, -, *, / (реализованы через +=, -=, *=, /=);
 *  - сравнение <, >, <=, >=, ==, != — сравниваются ОПРЕДЕЛИТЕЛИ матриц
 *    (две разные матрицы с одинаковым определителем считаются равными).
 *
 * Деление A / B понимается как умножение на обратную матрицу: A * B^(-1).
 * Если B вырождена (определитель равен 0), деление отклоняется, матрица
 * остаётся без изменений.
 *
 * Каждая операция записывается в историю, которую можно просмотреть
 * через printHistory(). История хранится в массиве фиксированного размера
 * (MAX_HISTORY записей): контейнеры STL и динамическая память не
 * используются. При переполнении самая старая запись вытесняется.
 */
class Matrix
{
public:
    /// @name Конструкторы и деструктор
    /// @{

    /**
     * @brief Конструктор по умолчанию: нулевая матрица [[0, 0], [0, 0]].
     */
    Matrix();

    /**
     * @brief Конструктор по четырём элементам.
     * @param a Элемент [0][0].
     * @param b Элемент [0][1].
     * @param c Элемент [1][0].
     * @param d Элемент [1][1].
     */
    Matrix(double a, double b, double c, double d);

    /**
     * @brief Конструктор скалярной матрицы [[s, 0], [0, s]].
     * @param scalar Значение на главной диагонали.
     *
     * Помечен explicit: число типа double НЕ превращается в Matrix
     * неявно (например, `Matrix m = 5.0;` или `A + 2.0` не компилируются).
     */
    explicit Matrix(double scalar);

    /**
     * @brief Копирующий конструктор.
     * @param other Копируемая матрица.
     *
     * Нужен из-за пользовательского деструктора и статического счётчика
     * (правило трёх): копия тоже должна учитываться в objectCount.
     * Копируются элементы и история; счётчик обращений у копии нулевой.
     */
    Matrix(const Matrix& other);

    /// @brief Копирующее присваивание (поведение по умолчанию).
    Matrix& operator=(const Matrix& other) = default;

    /**
     * @brief Деструктор (не по умолчанию).
     *
     * Уменьшает статический счётчик живых объектов и, когда уничтожена
     * последняя матрица, сообщает об этом.
     */
    ~Matrix();

    /// @}

    /// @name Методы чтения (const)
    /// @{

    /**
     * @brief Возвращает элемент матрицы.
     * @param row Номер строки (0 или 1).
     * @param col Номер столбца (0 или 1).
     * @return Значение элемента; при неверном индексе — 0 и сообщение об ошибке.
     *
     * Увеличивает mutable-счётчик обращений accessCount, поэтому
     * работает и для const-объектов.
     */
    double at(int row, int col) const;

    /**
     * @brief Вычисляет определитель a*d - b*c.
     * @return Определитель матрицы (увеличивает accessCount).
     */
    double determinant() const;

    /// @brief Возвращает true, если определитель отличен от нуля.
    bool isInvertible() const;

    /// @brief Возвращает значение mutable-счётчика обращений.
    int getAccessCount() const;

    /// @brief Возвращает число записей, которые сейчас хранятся в истории (не больше MAX_HISTORY).
    int getHistorySize() const;

    /// @brief Возвращает общее число записанных операций (включая вытесненные).
    int getHistoryTotal() const;

    /**
     * @brief Сравнивает матрицы по определителю.
     * @param other Вторая матрица.
     * @return -1, если det(this) < det(other); 0, если равны (с точностью
     *         1e-9); 1, если det(this) > det(other).
     *
     * На этом методе построены все шесть операторов сравнения.
     * Запись о сравнении попадает в mutable-историю this.
     */
    int compareByDeterminant(const Matrix& other) const;

    /// @brief Выводит историю операций над матрицей на экран.
    void printHistory() const;

    /**
     * @brief Явное преобразование к bool: true, если матрица невырождена.
     *
     * Помечено explicit: `if (m)` и `static_cast<bool>(m)` работают,
     * а `bool b = m;` или `int x = m + 1;` — нет.
     */
    explicit operator bool() const;

    /// @}

    /// @name Унарные операторы (изменяют все элементы на ±1)
    /// @{

    /// @brief Префиксный инкремент: все элементы +1, возвращает ссылку на this.
    Matrix& operator++();

    /// @brief Постфиксный инкремент: все элементы +1, возвращает старое значение.
    Matrix operator++(int);

    /// @brief Префиксный декремент: все элементы -1, возвращает ссылку на this.
    Matrix& operator--();

    /// @brief Постфиксный декремент: все элементы -1, возвращает старое значение.
    Matrix operator--(int);

    /// @}

    /// @name Арифметическое присваивание
    /// @{

    /// @brief Поэлементное сложение: this += rhs.
    Matrix& operator+=(const Matrix& rhs);

    /// @brief Поэлементное вычитание: this -= rhs.
    Matrix& operator-=(const Matrix& rhs);

    /// @brief Матричное умножение: this = this * rhs.
    Matrix& operator*=(const Matrix& rhs);

    /**
     * @brief Деление: this = this * rhs^(-1).
     * @param rhs Делитель. Если его определитель равен 0 — операция
     *            отклоняется с сообщением, this не меняется.
     */
    Matrix& operator/=(const Matrix& rhs);

    /// @}

    /// @brief Возвращает количество существующих в данный момент объектов Matrix.
    static int getObjectCount();

    /// @brief Вывод матрицы в поток в виде [[a, b], [c, d]].
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

private:
    /// Максимальное число записей, хранимых в истории одной матрицы.
    enum { MAX_HISTORY = 32 };

    double data[2][2];                      ///< Элементы матрицы
    mutable std::string history[MAX_HISTORY]; ///< История операций (mutable — пишется и из const-методов)
    mutable int historyCount;               ///< Сколько записей сейчас в массиве history (mutable)
    mutable int historyTotal;               ///< Сколько записей было сделано за всё время (mutable)
    mutable int accessCount;                ///< Счётчик обращений (mutable)

    static int objectCount;                 ///< Статическое поле: число живых объектов Matrix

    /// @brief Добавляет запись в историю; при заполнении массива вытесняет самую старую запись.
    void record(const std::string& text) const;

    /// @brief Прибавляет delta ко всем элементам и записывает операцию в историю.
    void shiftAll(double delta, const std::string& label);

    /// @brief Строковое представление матрицы [[a, b], [c, d]].
    std::string toString() const;
};

/// @name Бинарные арифметические операторы (реализованы через +=, -=, *=, /=)
/// @{
Matrix operator+(Matrix lhs, const Matrix& rhs);
Matrix operator-(Matrix lhs, const Matrix& rhs);
Matrix operator*(Matrix lhs, const Matrix& rhs);
Matrix operator/(Matrix lhs, const Matrix& rhs);
/// @}

/// @name Операторы сравнения (по определителю)
/// @{
bool operator<(const Matrix& lhs, const Matrix& rhs);
bool operator>(const Matrix& lhs, const Matrix& rhs);
bool operator<=(const Matrix& lhs, const Matrix& rhs);
bool operator>=(const Matrix& lhs, const Matrix& rhs);
bool operator==(const Matrix& lhs, const Matrix& rhs);
bool operator!=(const Matrix& lhs, const Matrix& rhs);
/// @}

#endif // MATRIX_H
