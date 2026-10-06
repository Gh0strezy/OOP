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
