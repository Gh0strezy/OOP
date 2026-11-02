/**
 * @file Truck.h
 * @brief Класс грузового автомобиля
 */

#ifndef TRUCK_H
#define TRUCK_H

#include "LandVehicle.h"
#include "ICargoCarrier.h"
#include <string>

/**
 * @brief Класс Truck - грузовой автомобиль
 * 
 * Конкретный класс, представляющий грузовой автомобиль.
 * Наследуется от LandVehicle и реализует интерфейс ICargoCarrier.
 */
class Truck : public LandVehicle, public ICargoCarrier
{
public:
    /**
     * @brief Конструктор с параметрами
     * @param brand Марка грузовика
     * @param maxSpeed Максимальная скорость (км/ч)
     * @param wheelCount Количество колёс
     * @param mass Масса грузовика (кг)
     * @param cargoCapacity Грузоподъёмность (кг)
     */
    Truck(const std::string& brand, double maxSpeed, int wheelCount, 
          double mass, double cargoCapacity);

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    Truck(const Truck& other);

    /**
     * @brief Оператор присваивания
     * @param other Копируемый объект
     * @return Ссылка на текущий объект
     */
    Truck& operator=(const Truck& other);

    /**
     * @brief Деструктор
     */
    virtual ~Truck();

    // Реализация чисто виртуальных функций Vehicle
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
     * @brief Получить марку грузовика
     * @return Марка грузовика
     */
    std::string getBrand() const;

    /**
     * @brief Сериализация объекта
     * @return Строка с данными объекта
     */
    virtual std::string serialize() const override;

    /**
     * @brief Десериализация объекта из строки
     * @param data Строка с данными
     * @return Указатель на созданный объект Truck
     */
    static Truck* deserialize(const std::string& data);

private:
    std::string brand_;         ///< Марка грузовика
    double cargoCapacity_;      ///< Грузоподъёмность (кг)
    double currentCargo_;       ///< Текущий вес груза (кг)
};

#endif // TRUCK_H
