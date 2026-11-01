/**
 * @file Vehicle.h
 * @brief Абстрактный базовый класс для всех транспортных средств
 */

#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

/**
 * @brief Абстрактный базовый класс Vehicle
 * 
 * Представляет общую концепцию транспортного средства.
 * Содержит чисто виртуальные функции, которые должны быть реализованы
 * в производных классах.
 */
class Vehicle
{
public:
    /**
     * @brief Виртуальный деструктор
     * 
     * Необходим для корректного удаления объектов производных классов
     * через указатель на базовый класс.
     */
    virtual ~Vehicle();

    /**
     * @brief Запуск двигателя (чисто виртуальная функция)
     * @return Строка с описанием процесса запуска
     */
    virtual std::string startEngine() const = 0;

    /**
     * @brief Начало движения (чисто виртуальная функция)
     * @return Строка с описанием процесса движения
     */
    virtual std::string move() const = 0;

    /**
     * @brief Получение типа транспортного средства (чисто виртуальная функция)
     * @return Строка с типом ТС
     */
    virtual std::string getType() const = 0;

    /**
     * @brief Виртуальная функция для получения информации о ТС
     * 
     * Реализация по умолчанию в базовом классе.
     * Может быть переопределена в производных классах.
     * 
     * @return Строка с информацией о транспортном средстве
     */
    virtual std::string getInfo() const;

    /**
     * @brief Получить максимальную зарегистрированную скорость
     * @return Максимальная скорость среди всех созданных объектов
     */
    static double getMaxSpeed();

    /**
     * @brief Сбросить максимальную скорость
     */
    static void resetMaxSpeed();

    /**
     * @brief Получить общее количество созданных транспортных средств
     * @return Счётчик созданных объектов
     */
    static int getObjectCount();

protected:
    /**
     * @brief Конструктор с параметрами
     * @param maxSpeed Максимальная скорость транспортного средства (км/ч)
     */
    explicit Vehicle(double maxSpeed);

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    Vehicle(const Vehicle& other);

    /**
     * @brief Оператор присваивания
     * @param other Копируемый объект
     * @return Ссылка на текущий объект
     */
    Vehicle& operator=(const Vehicle& other);

    /**
     * @brief Обновить глобальную максимальную скорость
     * @param speed Скорость для сравнения
     */
    void updateMaxSpeed(double speed);

    double maxSpeed_; ///< Максимальная скорость данного ТС (км/ч)

private:
    static double globalMaxSpeed_;  ///< Максимальная зарегистрированная скорость среди всех ТС
    static int objectCount_;        ///< Счётчик созданных объектов класса Vehicle
};

#endif // VEHICLE_H
