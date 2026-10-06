/**
 * @file Wallet.h
 * @brief Объявление классов Wallet (электронный кошелёк) и Owner (его владелец),
 *        а также перечисления Currency.
 */

#ifndef WALLET_H
#define WALLET_H

#include <string>

/**
 * @brief Валюта кошелька.
 *
 * Пользовательский тип данных (поле currency класса Wallet).
 */
enum class Currency
{
    RUB, ///< Российский рубль
    USD, ///< Доллар США
    EUR  ///< Евро
};

/**
 * @brief Преобразует значение Currency в читаемую строку ("RUB", "USD", "EUR").
 * @param currency Валюта.
 * @return Строковое представление валюты.
 */
std::string currencyToString(Currency currency);

/**
 * @brief Класс, описывающий владельца кошелька.
 *
 * Объект Owner хранится внутри Wallet по значению (композиция):
 * Wallet "владеет" своим Owner, и время жизни Owner в составе
 * кошелька совпадает со временем жизни самого кошелька.
 *
 * Инварианты класса:
 *  1. Имя владельца никогда не пустое (иначе подставляется "Unknown").
 *  2. Email либо не указан (пустая строка), либо содержит символ '@'
 *     с непустыми частями до и после него.
 */
class Owner
{
public:
    /**
     * @brief Конструктор по умолчанию: имя "Unknown", email не указан.
     */
    Owner();

    /**
     * @brief Конструктор с именем (email не указан).
     * @param ownerName Имя владельца. Пустое имя заменяется на "Unknown".
     */
    explicit Owner(const std::string& ownerName);

    /**
     * @brief Конструктор с именем и email.
     * @param ownerName  Имя владельца. Пустое имя заменяется на "Unknown".
     * @param ownerEmail Email. Некорректный адрес отбрасывается
     *                   (email остаётся не указанным).
     */
    Owner(const std::string& ownerName, const std::string& ownerEmail);

    /// @brief Возвращает имя владельца.
    std::string getName() const;

    /// @brief Возвращает email (пустая строка, если не указан).
    std::string getEmail() const;

    /// @brief Возвращает true, если email указан.
    bool hasEmail() const;

    /**
     * @brief Меняет email владельца.
     * @param newEmail Новый адрес. Должен быть корректным.
     * @return true, если email изменён; false, если адрес некорректен
     *         (старый email сохраняется).
     */
    bool changeEmail(const std::string& newEmail);

private:
    std::string name;   ///< Имя владельца
    std::string email;  ///< Email (пустая строка — не указан)

    /// @brief Проверяет формат email (есть '@' с непустыми частями по краям).
    static bool isValidEmail(const std::string& value);
};

#endif // WALLET_H
