/**
 * @file Minivan.cpp
 * @brief Реализация класса Minivan
 */

#include "../include/Minivan.h"
#include <sstream>

Minivan::Minivan(const std::string& brand, double maxSpeed, int wheelCount, 
                 double mass, int passengerCapacity, double cargoCapacity)
    : Vehicle(maxSpeed),  // Явно вызываем конструктор виртуального базового класса
      Car(brand, maxSpeed, wheelCount, mass, passengerCapacity),
      ICargoCarrier(),
      cargoCapacity_(cargoCapacity),
      currentCargo_(0.0)
{
}

Minivan::Minivan(const Minivan& other)
    : Vehicle(other),  // Явно вызываем конструктор копирования виртуального базового класса
      Car(other),
      ICargoCarrier(),
      cargoCapacity_(other.cargoCapacity_),
      currentCargo_(other.currentCargo_)
{
}

Minivan& Minivan::operator=(const Minivan& other)
{
    if (this != &other)
    {
        Car::operator=(other);
        cargoCapacity_ = other.cargoCapacity_;
        currentCargo_ = other.currentCargo_;
    }
    return *this;
}

Minivan::~Minivan()
{
}

std::string Minivan::startEngine() const
{
    return "Минивэн " + getBrand() + " готов к перевозке пассажиров и грузов";
}

std::string Minivan::move() const
{
    std::ostringstream oss;
    oss << getBrand() << " везёт " << getCurrentPassengers() << " пассажиров "
        << "и " << static_cast<int>(currentCargo_) << " кг груза";
    return oss.str();
}

std::string Minivan::getType() const
{
    return "Минивэн (пассажирско-грузовой)";
}

std::string Minivan::getInfo() const
{
    std::ostringstream oss;
    oss << Car::getInfo()
        << ", Груз: " << currentCargo_ << "/" << cargoCapacity_ << " кг";
    return oss.str();
}

double Minivan::getCargoCapacity() const
{
    return cargoCapacity_;
}

bool Minivan::loadCargo(double weight)
{
    if (weight <= 0 || currentCargo_ + weight > cargoCapacity_)
    {
        return false;
    }
    currentCargo_ += weight;
    return true;
}

bool Minivan::unloadCargo(double weight)
{
    if (weight <= 0 || currentCargo_ < weight)
    {
        return false;
    }
    currentCargo_ -= weight;
    return true;
}

double Minivan::getCurrentCargo() const
{
    return currentCargo_;
}

std::string Minivan::serialize() const
{
    std::ostringstream oss;
    oss << "Minivan;" << getBrand() << ";" << maxSpeed_ << ";" 
        << wheelCount_ << ";" << mass_ << ";" 
        << getPassengerCapacity() << ";" << getCurrentPassengers() << ";"
        << cargoCapacity_ << ";" << currentCargo_;
    return oss.str();
}

Minivan* Minivan::deserialize(const std::string& data)
{
    std::istringstream iss(data);
    std::string type, brand;
    double maxSpeed, mass, cargoCapacity, currentCargo;
    int wheelCount, passengerCapacity, currentPassengers;
    char delim;

    std::getline(iss, type, ';');
    std::getline(iss, brand, ';');
    iss >> maxSpeed >> delim >> wheelCount >> delim >> mass >> delim 
        >> passengerCapacity >> delim >> currentPassengers >> delim
        >> cargoCapacity >> delim >> currentCargo;

    Minivan* minivan = new Minivan(brand, maxSpeed, wheelCount, mass, 
                                    passengerCapacity, cargoCapacity);
    // Устанавливаем текущих пассажиров и груз
    for (int i = 0; i < currentPassengers; ++i)
    {
        minivan->boardPassengers(1);
    }
    minivan->currentCargo_ = currentCargo;
    return minivan;
}
