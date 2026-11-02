/**
 * @file Car.cpp
 * @brief Реализация класса Car
 */

#include "../include/Car.h"
#include <sstream>

Car::Car(const std::string& brand, double maxSpeed, int wheelCount, 
         double mass, int passengerCapacity)
    : Vehicle(maxSpeed),
      LandVehicle(maxSpeed, wheelCount, mass),
      brand_(brand),
      passengerCapacity_(passengerCapacity),
      currentPassengers_(0)
{
}

Car::Car(const Car& other)
    : Vehicle(other),
      LandVehicle(other),
      IPassengerCarrier(),
      brand_(other.brand_),
      passengerCapacity_(other.passengerCapacity_),
      currentPassengers_(other.currentPassengers_)
{
}

Car& Car::operator=(const Car& other)
{
    if (this != &other)
    {
        LandVehicle::operator=(other);
        brand_ = other.brand_;
        passengerCapacity_ = other.passengerCapacity_;
        currentPassengers_ = other.currentPassengers_;
    }
    return *this;
}

Car::~Car()
{
}

std::string Car::startEngine() const
{
    return "Легковой автомобиль " + brand_ + " завёл двигатель";
}

std::string Car::move() const
{
    return brand_ + " движется по дороге со скоростью до " + 
           std::to_string(static_cast<int>(maxSpeed_)) + " км/ч";
}

std::string Car::getType() const
{
    return "Легковой автомобиль";
}

std::string Car::getBrand() const
{
    return brand_;
}

std::string Car::getInfo() const
{
    std::ostringstream oss;
    oss << LandVehicle::getInfo()
        << ", Марка: " << brand_
        << ", Пассажиров: " << currentPassengers_ << "/" << passengerCapacity_;
    return oss.str();
}

int Car::getPassengerCapacity() const
{
    return passengerCapacity_;
}

bool Car::boardPassengers(int count)
{
    if (count <= 0 || currentPassengers_ + count > passengerCapacity_)
    {
        return false;
    }
    currentPassengers_ += count;
    return true;
}

bool Car::unboardPassengers(int count)
{
    if (count <= 0 || currentPassengers_ < count)
    {
        return false;
    }
    currentPassengers_ -= count;
    return true;
}

int Car::getCurrentPassengers() const
{
    return currentPassengers_;
}

std::string Car::serialize() const
{
    std::ostringstream oss;
    oss << "Car;" << brand_ << ";" << maxSpeed_ << ";" 
        << wheelCount_ << ";" << mass_ << ";" 
        << passengerCapacity_ << ";" << currentPassengers_;
    return oss.str();
}

Car* Car::deserialize(const std::string& data)
{
    std::istringstream iss(data);
    std::string type, brand;
    double maxSpeed, mass;
    int wheelCount, passengerCapacity, currentPassengers;
    char delim;

    std::getline(iss, type, ';');
    std::getline(iss, brand, ';');
    iss >> maxSpeed >> delim >> wheelCount >> delim >> mass >> delim 
        >> passengerCapacity >> delim >> currentPassengers;

    Car* car = new Car(brand, maxSpeed, wheelCount, mass, passengerCapacity);
    car->currentPassengers_ = currentPassengers;
    return car;
}
