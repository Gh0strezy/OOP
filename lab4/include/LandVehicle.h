/**
 * @file LandVehicle.h
 * @brief Промежуточный класс для наземных транспортных средств
 */

#ifndef LANDVEHICLE_H
#define LANDVEHICLE_H

#include "Vehicle.h"

/**
 * @brief Промежуточный класс LandVehicle
 * 
 * Наследуется от Vehicle и добавляет характеристики,
 * специфичные для наземного транспорта: количество колёс и массу.
 * 
 * Использует виртуальное наследование для решения проблемы "алмаза"
 * в случае множественного наследования в производных классах.
 */
class LandVehicle : virtual public Vehicle
{
public:
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~LandVehicle();

    /**
     * @brief Получить количество колёс
     * @return Количество колёс
     */
    int getWheelCount() const;

    /**
     * @brief Получить массу транспортного средства
     * @return Масса в килограммах
     */
    double getMass() const;

    /**
     * @brief Переопределение функции получения информации
     * @return Строка с подробной информацией о наземном ТС
     */
    virtual std::string getInfo() const override;

    /**
     * @brief Сохранить состояние объекта в строку
     * @return Строка с сериализованными данными
     */
    virtual std::string serialize() const;

    /**
     * @brief Дружественная функция для сравнения массы двух наземных ТС
     * @param lv1 Первое транспортное средство
     * @param lv2 Второе транспортное средство
     * @return true, если масса первого больше массы второго
     */
    friend bool isHeavier(const LandVehicle& lv1, const LandVehicle& lv2);

protected:
    /**
     * @brief Конструктор с параметрами
     * @param maxSpeed Максимальная скорость (км/ч)
     * @param wheelCount Количество колёс
     * @param mass Масса транспортного средства (кг)
     */
    LandVehicle(double maxSpeed, int wheelCount, double mass);

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    LandVehicle(const LandVehicle& other);

    /**
     * @brief Оператор присваивания
     * @param other Копируемый объект
     * @return Ссылка на текущий объект
     */
    LandVehicle& operator=(const LandVehicle& other);

    int wheelCount_;    ///< Количество колёс
    double mass_;       ///< Масса транспортного средства (кг)
};

#endif // LANDVEHICLE_H
