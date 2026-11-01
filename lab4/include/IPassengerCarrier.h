/**
 * @file IPassengerCarrier.h
 * @brief Интерфейс для транспортных средств, перевозящих пассажиров
 */

#ifndef IPASSENGERCARRIER_H
#define IPASSENGERCARRIER_H

#include <string>

/**
 * @brief Интерфейс IPassengerCarrier
 * 
 * Определяет возможность перевозки пассажиров.
 * Все методы являются чисто виртуальными.
 */
class IPassengerCarrier
{
public:
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~IPassengerCarrier() = default;

    /**
     * @brief Получить вместимость пассажиров
     * @return Количество пассажирских мест
     */
    virtual int getPassengerCapacity() const = 0;

    /**
     * @brief Посадить пассажиров
     * @param count Количество пассажиров для посадки
     * @return true, если операция выполнена успешно
     */
    virtual bool boardPassengers(int count) = 0;

    /**
     * @brief Высадить пассажиров
     * @param count Количество пассажиров для высадки
     * @return true, если операция выполнена успешно
     */
    virtual bool unboardPassengers(int count) = 0;

    /**
     * @brief Получить текущее количество пассажиров
     * @return Количество пассажиров на борту
     */
    virtual int getCurrentPassengers() const = 0;
};

#endif // IPASSENGERCARRIER_H
