/**
 * @file Wallet.cpp
 * @brief Реализация классов Owner и Wallet.
 */

#include "Wallet.h"
#include <iostream>

bool Owner::isValidEmail(const std::string& value)
{
    std::string::size_type at = value.find('@');
    return at != std::string::npos && at > 0 && at + 1 < value.size();
}

Owner::Owner()
    : name("Unknown"), email("")
{
}

Owner::Owner(const std::string& ownerName)
    : name(ownerName.empty() ? "Unknown" : ownerName), email("")
{
}

Owner::Owner(const std::string& ownerName, const std::string& ownerEmail)
    : name(ownerName.empty() ? "Unknown" : ownerName),
      email(isValidEmail(ownerEmail) ? ownerEmail : "")
{
    if (!ownerEmail.empty() && !isValidEmail(ownerEmail))
    {
        std::cout << "Предупреждение: некорректный email \"" << ownerEmail
                  << "\" отброшен." << std::endl;
    }
}

std::string Owner::getName() const { return name; }
std::string Owner::getEmail() const { return email; }
bool Owner::hasEmail() const { return !email.empty(); }

bool Owner::changeEmail(const std::string& newEmail)
{
    if (!isValidEmail(newEmail))
    {
        std::cout << "Ошибка: некорректный email \"" << newEmail << "\"." << std::endl;
        return false;
    }
    email = newEmail;
    return true;
}

int Wallet::objectCount = 0;

std::string currencyToString(Currency currency)
{
    switch (currency)
    {
        case Currency::RUB: return "RUB";
        case Currency::USD: return "USD";
        case Currency::EUR: return "EUR";
    }
    return "UNKNOWN";
}

Wallet::Wallet()
    : owner(), balance(0.0), currency(Currency::RUB),
      transactionCount(0), blocked(false)
{
    ++objectCount;
}

Wallet::Wallet(const Owner& owner, Currency currency)
    : owner(owner), balance(0.0), currency(currency),
      transactionCount(0), blocked(false)
{
    ++objectCount;
}

Wallet::Wallet(const Owner& owner, double initialBalance, Currency currency)
    : owner(owner),
      balance(initialBalance >= 0.0 ? initialBalance : 0.0),
      currency(currency),
      transactionCount(0),
      blocked(false)
{
    if (initialBalance < 0.0)
    {
        std::cout << "Предупреждение: отрицательный начальный баланс для \""
                  << owner.getName() << "\" заменён на 0." << std::endl;
    }
    ++objectCount;
}

Wallet::~Wallet()
{
    std::cout << "Кошелёк владельца \"" << owner.getName() << "\" уничтожен." << std::endl;
    --objectCount;
}

const Owner& Wallet::getOwner() const { return owner; }
double Wallet::getBalance() const { return balance; }
Currency Wallet::getCurrency() const { return currency; }
int Wallet::getTransactionCount() const { return transactionCount; }
bool Wallet::isBlocked() const { return blocked; }

bool Wallet::deposit(double amount)
{
    if (blocked)
    {
        std::cout << "Ошибка: кошелёк \"" << owner.getName()
                  << "\" заблокирован, пополнение невозможно." << std::endl;
        return false;
    }
    if (amount <= 0.0)
    {
        std::cout << "Ошибка: сумма пополнения должна быть положительной." << std::endl;
        return false;
    }

    balance += amount;
    ++transactionCount;
    return true;
}

bool Wallet::withdraw(double amount)
{
    if (blocked)
    {
        std::cout << "Ошибка: кошелёк \"" << owner.getName()
                  << "\" заблокирован, снятие невозможно." << std::endl;
        return false;
    }
    if (amount <= 0.0)
    {
        std::cout << "Ошибка: сумма снятия должна быть положительной." << std::endl;
        return false;
    }
    if (amount > balance)
    {
        std::cout << "Ошибка: недостаточно средств на кошельке \""
                  << owner.getName() << "\"." << std::endl;
        return false;
    }

    balance -= amount;
    ++transactionCount;
    return true;
}
