/**
 * @file Car.h
 * @brief Класс легкового автомобиля
 */

#ifndef CAR_H
#define CAR_H

#include "LandVehicle.h"
#include "IPassengerCarrier.h"
#include <string>

/**
 * @brief Класс Car - легковой автомобиль
 * 
 * Конкретный класс, представляющий легковой автомобиль.
 * Наследуется от LandVehicle и реализует интерфейс IPassengerCarrier.
 */
class Car : public LandVehicle, public IPassengerCarrier
{
public:
    /**
     * @brief Конструктор с параметрами
     * @param brand Марка автомобиля
     * @param maxSpeed Максимальная скорость (км/ч)
     * @param wheelCount Количество колёс
     * @param mass Масса автомобиля (кг)
     * @param passengerCapacity Вместимость пассажиров
     */
    Car(const std::string& brand, double maxSpeed, int wheelCount, 
        double mass, int passengerCapacity);

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    Car(const Car& other);

    /**
     * @brief Оператор присваивания
     * @param other Копируемый объект
     * @return Ссылка на текущий объект
     */
    Car& operator=(const Car& other);

    /**
     * @brief Деструктор
     */
    virtual ~Car();

    // Реализация чисто виртуальных функций Vehicle
    virtual std::string startEngine() const override;
    virtual std::string move() const override;
    virtual std::string getType() const override;
    virtual std::string getInfo() const override;

    // Реализация интерфейса IPassengerCarrier
    virtual int getPassengerCapacity() const override;
    virtual bool boardPassengers(int count) override;
    virtual bool unboardPassengers(int count) override;
    virtual int getCurrentPassengers() const override;

    /**
     * @brief Получить марку автомобиля
     * @return Марка автомобиля
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
     * @return Указатель на созданный объект Car
     */
    static Car* deserialize(const std::string& data);

private:
    std::string brand_;         ///< Марка автомобиля
    int passengerCapacity_;     ///< Вместимость пассажиров
    int currentPassengers_;     ///< Текущее количество пассажиров
};

#endif // CAR_H
