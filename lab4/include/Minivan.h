/**
 * @file Minivan.h
 * @brief Класс минивэна с множественным наследованием
 */

#ifndef MINIVAN_H
#define MINIVAN_H

#include "Car.h"
#include "ICargoCarrier.h"
#include <string>

/**
 * @brief Класс Minivan - многофункциональный автомобиль
 * 
 * Демонстрирует множественное наследование:
 * - Наследуется от Car (который уже наследуется от LandVehicle)
 * - Дополнительно реализует интерфейс ICargoCarrier
 * 
 * Использует виртуальное наследование (в LandVehicle) для решения
 * проблемы "алмаза" (diamond problem), когда Vehicle является
 * общим базовым классом для нескольких веток наследования.
 */
class Minivan : public Car, public ICargoCarrier
{
public:
    /**
     * @brief Конструктор с параметрами
     * @param brand Марка минивэна
     * @param maxSpeed Максимальная скорость (км/ч)
     * @param wheelCount Количество колёс
     * @param mass Масса минивэна (кг)
     * @param passengerCapacity Вместимость пассажиров
     * @param cargoCapacity Грузоподъёмность (кг)
     */
    Minivan(const std::string& brand, double maxSpeed, int wheelCount, 
            double mass, int passengerCapacity, double cargoCapacity);

    /**
     * @brief Конструктор копирования с глубоким копированием
     * @param other Копируемый объект
     */
    Minivan(const Minivan& other);

    /**
     * @brief Оператор присваивания с глубоким копированием
     * @param other Копируемый объект
     * @return Ссылка на текущий объект
     */
    Minivan& operator=(const Minivan& other);

    /**
     * @brief Деструктор
     */
    virtual ~Minivan();

    // Переопределение методов Vehicle
    virtual std::string startEngine() const override;
    virtual std::string move() const override;
    virtual std::string getType() const override;
    virtual std::string getInfo() const override;

    // Реализация интерфейса ICargoCarrier
    virtual double getCargoCapacity() const override;
    virtual bool loadCargo(double weight) override;
    virtual bool unloadCargo(double weight) override;
    virtual double getCurrentCargo() const override;

    /**
     * @brief Сериализация объекта
     * @return Строка с данными объекта
     */
    virtual std::string serialize() const override;

    /**
     * @brief Десериализация объекта из строки
     * @param data Строка с данными
     * @return Указатель на созданный объект Minivan
     */
    static Minivan* deserialize(const std::string& data);

private:
    double cargoCapacity_;      ///< Грузоподъёмность (кг)
    double currentCargo_;       ///< Текущий вес груза (кг)
};

#endif // MINIVAN_H
