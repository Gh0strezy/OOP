/**
 * @file Truck.cpp
 * @brief Реализация класса Truck
 */

#include "../include/Truck.h"
#include <sstream>

Truck::Truck(const std::string& brand, double maxSpeed, int wheelCount, 
             double mass, double cargoCapacity)
    : Vehicle(maxSpeed),
      LandVehicle(maxSpeed, wheelCount, mass),
      brand_(brand),
      cargoCapacity_(cargoCapacity),
      currentCargo_(0.0)
{
}

Truck::Truck(const Truck& other)
    : Vehicle(other),
      LandVehicle(other),
      ICargoCarrier(),
      brand_(other.brand_),
      cargoCapacity_(other.cargoCapacity_),
      currentCargo_(other.currentCargo_)
{
}

Truck& Truck::operator=(const Truck& other)
{
    if (this != &other)
    {
        LandVehicle::operator=(other);
        brand_ = other.brand_;
        cargoCapacity_ = other.cargoCapacity_;
        currentCargo_ = other.currentCargo_;
    }
    return *this;
}

Truck::~Truck()
{
}

std::string Truck::startEngine() const
{
    return "Грузовик " + brand_ + " запустил мощный дизельный двигатель";
}

std::string Truck::move() const
{
    return brand_ + " перевозит груз массой " + 
           std::to_string(static_cast<int>(currentCargo_)) + " кг";
}

std::string Truck::getType() const
{
    return "Грузовой автомобиль";
}

std::string Truck::getBrand() const
{
    return brand_;
}

std::string Truck::getInfo() const
{
    std::ostringstream oss;
    oss << LandVehicle::getInfo()
        << ", Марка: " << brand_
        << ", Груз: " << currentCargo_ << "/" << cargoCapacity_ << " кг";
    return oss.str();
}

double Truck::getCargoCapacity() const
{
    return cargoCapacity_;
}

bool Truck::loadCargo(double weight)
{
    if (weight <= 0 || currentCargo_ + weight > cargoCapacity_)
    {
        return false;
    }
    currentCargo_ += weight;
    return true;
}

bool Truck::unloadCargo(double weight)
{
    if (weight <= 0 || currentCargo_ < weight)
    {
        return false;
    }
    currentCargo_ -= weight;
    return true;
}

double Truck::getCurrentCargo() const
{
    return currentCargo_;
}

std::string Truck::serialize() const
{
    std::ostringstream oss;
    oss << "Truck;" << brand_ << ";" << maxSpeed_ << ";" 
        << wheelCount_ << ";" << mass_ << ";" 
        << cargoCapacity_ << ";" << currentCargo_;
    return oss.str();
}

Truck* Truck::deserialize(const std::string& data)
{
    std::istringstream iss(data);
    std::string type, brand;
    double maxSpeed, mass, cargoCapacity, currentCargo;
    int wheelCount;
    char delim;

    std::getline(iss, type, ';');
    std::getline(iss, brand, ';');
    iss >> maxSpeed >> delim >> wheelCount >> delim >> mass >> delim 
        >> cargoCapacity >> delim >> currentCargo;

    Truck* truck = new Truck(brand, maxSpeed, wheelCount, mass, cargoCapacity);
    truck->currentCargo_ = currentCargo;
    return truck;
}
