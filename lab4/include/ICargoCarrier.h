/**
 * @file ICargoCarrier.h
 * @brief Интерфейс для транспортных средств, перевозящих грузы
 */

#ifndef ICARGOCARRIER_H
#define ICARGOCARRIER_H

#include <string>

/**
 * @brief Интерфейс ICargoCarrier
 * 
 * Определяет возможность перевозки грузов.
 * Все методы являются чисто виртуальными.
 */
class ICargoCarrier
{
public:
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~ICargoCarrier() = default;

    /**
     * @brief Получить грузоподъёмность
     * @return Максимальная грузоподъёмность в килограммах
     */
    virtual double getCargoCapacity() const = 0;

    /**
     * @brief Загрузить груз
     * @param weight Вес груза для загрузки (кг)
     * @return true, если операция выполнена успешно
     */
    virtual bool loadCargo(double weight) = 0;

    /**
     * @brief Разгрузить груз
     * @param weight Вес груза для разгрузки (кг)
     * @return true, если операция выполнена успешно
     */
    virtual bool unloadCargo(double weight) = 0;

    /**
     * @brief Получить текущий вес груза
     * @return Текущий вес груза на борту (кг)
     */
    virtual double getCurrentCargo() const = 0;
};

#endif // ICARGOCARRIER_H
