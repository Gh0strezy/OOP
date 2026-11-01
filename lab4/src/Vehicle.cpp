/**
 * @file Vehicle.cpp
 * @brief Реализация абстрактного базового класса Vehicle
 */

#include "../include/Vehicle.h"
#include <sstream>

// Инициализация статических членов
double Vehicle::globalMaxSpeed_ = 0.0;
int Vehicle::objectCount_ = 0;

Vehicle::Vehicle(double maxSpeed)
    : maxSpeed_(maxSpeed)
{
    ++objectCount_;
    updateMaxSpeed(maxSpeed);
}

Vehicle::Vehicle(const Vehicle& other)
    : maxSpeed_(other.maxSpeed_)
{
    ++objectCount_;
}

Vehicle& Vehicle::operator=(const Vehicle& other)
{
    if (this != &other)
    {
        maxSpeed_ = other.maxSpeed_;
    }
    return *this;
}

Vehicle::~Vehicle()
{
    --objectCount_;
}

std::string Vehicle::getInfo() const
{
    std::ostringstream oss;
    oss << "Тип: " << getType() 
        << ", Макс. скорость: " << maxSpeed_ << " км/ч";
    return oss.str();
}

void Vehicle::updateMaxSpeed(double speed)
{
    if (speed > globalMaxSpeed_)
    {
        globalMaxSpeed_ = speed;
    }
}

double Vehicle::getMaxSpeed()
{
    return globalMaxSpeed_;
}

void Vehicle::resetMaxSpeed()
{
    globalMaxSpeed_ = 0.0;
}

int Vehicle::getObjectCount()
{
    return objectCount_;
}
