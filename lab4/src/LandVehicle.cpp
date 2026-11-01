/**
 * @file LandVehicle.cpp
 * @brief Реализация промежуточного класса LandVehicle
 */

#include "../include/LandVehicle.h"
#include <sstream>

LandVehicle::LandVehicle(double maxSpeed, int wheelCount, double mass)
    : Vehicle(maxSpeed), wheelCount_(wheelCount), mass_(mass)
{
}

LandVehicle::LandVehicle(const LandVehicle& other)
    : Vehicle(other), wheelCount_(other.wheelCount_), mass_(other.mass_)
{
}

LandVehicle& LandVehicle::operator=(const LandVehicle& other)
{
    if (this != &other)
    {
        Vehicle::operator=(other);
        wheelCount_ = other.wheelCount_;
        mass_ = other.mass_;
    }
    return *this;
}

LandVehicle::~LandVehicle()
{
}

int LandVehicle::getWheelCount() const
{
    return wheelCount_;
}

double LandVehicle::getMass() const
{
    return mass_;
}

std::string LandVehicle::getInfo() const
{
    std::ostringstream oss;
    oss << Vehicle::getInfo()
        << ", Колёса: " << wheelCount_
        << ", Масса: " << mass_ << " кг";
    return oss.str();
}

std::string LandVehicle::serialize() const
{
    std::ostringstream oss;
    oss << maxSpeed_ << ";" << wheelCount_ << ";" << mass_;
    return oss.str();
}

// Реализация дружественной функции
bool isHeavier(const LandVehicle& lv1, const LandVehicle& lv2)
{
    return lv1.mass_ > lv2.mass_;
}
