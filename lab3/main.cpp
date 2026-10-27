/**
 * @file main.cpp
 * @brief Демонстрация работы класса Matrix: конструкторы, унарные операторы,
 *        арифметическое присваивание, бинарные операторы, сравнение,
 *        explicit, mutable для const-объекта, история операций.
 *
 * Компиляция (C++14):
 *   g++ -std=c++14 -Wall -Wextra -o matrix Matrix.cpp main.cpp
 */

#include "Matrix.h"
#include <iostream>
#include <type_traits>

// Проверки на этапе компиляции: explicit запрещает неявные преобразования.
static_assert(!std::is_convertible<double, Matrix>::value,
              "explicit: double не должен неявно превращаться в Matrix");
static_assert(!std::is_convertible<Matrix, bool>::value,
              "explicit operator bool: Matrix не должен неявно превращаться в bool");

int main()
{
    std::cout << std::boolalpha;

    // ===== 1. Конструкторы и статическое поле
    std::cout << "=== 1. Конструкторы ===" << std::endl;
    Matrix Z;                 // по умолчанию: нулевая матрица
    Matrix A(1, 2, 3, 4);     // по четырём элементам
    Matrix S(2.0);            // explicit: скалярная матрица
    Matrix B(1, 1, 0, 1);
    Matrix F(2, 0, 0, -1);
    Matrix copyOfA(A);        // копирующий конструктор
    std::cout << "Z = " << Z << std::endl;
    std::cout << "A = " << A << ", det(A) = " << A.determinant() << std::endl;
    std::cout << "S = " << S << std::endl;
    std::cout << "B = " << B << ", F = " << F << std::endl;
    std::cout << "copyOfA = " << copyOfA << std::endl;
    std::cout << "Живых объектов Matrix: " << Matrix::getObjectCount() << std::endl;

    // ===== 2. Унарные операторы: префикс/постфикс ++ и --
    std::cout << std::endl << "=== 2. Унарные операторы (все элементы на +-1) ===" << std::endl;
    Matrix P = A;
    std::cout << "Исходная P = " << P << std::endl;

    Matrix r1 = ++P;
    std::cout << "r1 = ++P  -> r1 = " << r1 << ", P = " << P << std::endl;
    Matrix r2 = P++;
    std::cout << "r2 = P++  -> r2 = " << r2 << " (старое значение), P = " << P << std::endl;
    Matrix r3 = --P;
    std::cout << "r3 = --P  -> r3 = " << r3 << ", P = " << P << std::endl;
    Matrix r4 = P--;
    std::cout << "r4 = P--  -> r4 = " << r4 << " (старое значение), P = " << P << std::endl;

    // ===== 3. Арифметическое присваивание: +=, -=, *=, /=
    std::cout << std::endl << "=== 3. Арифметическое присваивание ===" << std::endl;
    Matrix C = A;
    std::cout << "C = " << C << ", B = " << B << std::endl;
    C += B;
    std::cout << "C += B -> " << C << std::endl;
    C -= B;
    std::cout << "C -= B -> " << C << std::endl;
    C *= B;
    std::cout << "C *= B -> " << C << std::endl;
    C /= B;
    std::cout << "C /= B -> " << C << " (вернулась к A)" << std::endl;
    std::cout << "C /= Z (деление на нулевую матрицу):" << std::endl;
    C /= Z;
    std::cout << "C после отклонённого деления -> " << C << std::endl;

    // ===== 4. Бинарные операторы: +, -, *, / (через +=, -=, *=, /=)
    std::cout << std::endl << "=== 4. Бинарные арифметические операторы ===" << std::endl;
    std::cout << "A + B = " << (A + B) << std::endl;
    std::cout << "A - B = " << (A - B) << std::endl;
    std::cout << "A * B = " << (A * B) << std::endl;
    std::cout << "A / B = " << (A / B) << std::endl;
    std::cout << "A после всех операций не изменилась: " << A << std::endl;

    // ===== 5. Сравнение матриц (по определителю)
    std::cout << std::endl << "=== 5. Операторы сравнения (по определителю) ===" << std::endl;
    std::cout << "A = " << A << ", det = " << A.determinant() << std::endl;
    std::cout << "B = " << B << ", det = " << B.determinant() << std::endl;
    std::cout << "F = " << F << ", det = " << F.determinant()
              << " (другие элементы, но тот же определитель, что у A)" << std::endl;
    std::cout << "A <  B : " << (A < B) << std::endl;
    std::cout << "A >  B : " << (A > B) << std::endl;
    std::cout << "A <= F : " << (A <= F) << std::endl;
    std::cout << "A >= F : " << (A >= F) << std::endl;
    std::cout << "A == F : " << (A == F) << std::endl;
    std::cout << "A != F : " << (A != F) << std::endl;
    std::cout << "A != B : " << (A != B) << std::endl;

    // ===== 6. explicit: защита от нежелательных неявных преобразований
    std::cout << std::endl << "=== 6. explicit ===" << std::endl;
    std::cout << "double -> Matrix неявно:  "
              << std::is_convertible<double, Matrix>::value << std::endl;
    std::cout << "double -> Matrix явно:    "
              << std::is_constructible<Matrix, double>::value << std::endl;
    std::cout << "Matrix -> bool неявно:    "
              << std::is_convertible<Matrix, bool>::value << std::endl;
    std::cout << "Matrix -> bool явно:      "
              << std::is_constructible<bool, Matrix>::value << std::endl;

    // Следующие строки НЕ компилируются именно из-за explicit:
    // Matrix m = 5.0;           // ошибка: неявное double -> Matrix запрещено
    // Matrix bad = A + 2.0;     // ошибка: 2.0 не превращается в Matrix сам
    // bool b = A;               // ошибка: неявное Matrix -> bool запрещено

    Matrix R = A + Matrix(2.0);  // правильно: преобразование записано явно
    std::cout << "A + Matrix(2.0) = " << R << std::endl;
    if (A)
    {
        std::cout << "if (A): A невырождена (det != 0)" << std::endl;
    }
    std::cout << "static_cast<bool>(Z) = " << static_cast<bool>(Z)
              << " (нулевая матрица вырождена)" << std::endl;

    // ===== 7. const-объект и mutable-поля
    std::cout << std::endl << "=== 7. const-объект и mutable ===" << std::endl;
    const Matrix K(5, 6, 7, 9);
    std::cout << "K = " << K << " (const)" << std::endl;
    std::cout << "Обращений к K до: " << K.getAccessCount() << std::endl;
    K.determinant();
    K.at(0, 1);
    bool less = (K < A);
    std::cout << "K < A = " << less << std::endl;
    std::cout << "Обращений к K после: " << K.getAccessCount()
              << " (счётчик изменился, хотя объект const)" << std::endl;

    // ===== 8. История операций
    std::cout << std::endl << "=== 8. История операций ===" << std::endl;
    std::cout << "История матрицы C:" << std::endl;
    C.printHistory();
    std::cout << std::endl << "История const-матрицы K (запись о сравнении добавлена через mutable):" << std::endl;
    K.printHistory();

    std::cout << std::endl << "Переполнение истории (массив рассчитан на 32 записи):" << std::endl;
    {
        Matrix big;
        for (int i = 0; i < 40; ++i)
        {
            ++big;
        }
        std::cout << "Записано операций: " << big.getHistoryTotal()
                  << ", хранится: " << big.getHistorySize() << std::endl;
        std::cout << "Матрица после 40 инкрементов: " << big << std::endl;
    }

    // ===== 9. Деструктор и статический счётчик
    std::cout << std::endl << "=== 9. Деструктор и статический счётчик ===" << std::endl;
    std::cout << "Объектов до блока:    " << Matrix::getObjectCount() << std::endl;
    {
        Matrix temp(9, 9, 9, 9);
        std::cout << "Объектов внутри блока: " << Matrix::getObjectCount() << std::endl;
    }
    std::cout << "Объектов после блока: " << Matrix::getObjectCount() << std::endl;

    std::cout << std::endl << "Конец main(): сейчас будут уничтожены все матрицы." << std::endl;
    return 0;
}
