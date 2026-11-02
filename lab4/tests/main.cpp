/**
 * @file main.cpp
 * @brief Тестовая программа для демонстрации иерархии транспортных средств
 */

#include "../include/Vehicle.h"
#include "../include/LandVehicle.h"
#include "../include/Car.h"
#include "../include/Truck.h"
#include "../include/Minivan.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

/**
 * @brief Загрузить транспортные средства из файла
 * @param filename Имя файла с данными
 * @return Вектор указателей на загруженные объекты
 */
std::vector<Vehicle*> loadVehicles(const std::string& filename)
{
    std::vector<Vehicle*> vehicles;
    std::ifstream file(filename);
    
    if (!file.is_open())
    {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return vehicles;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        
        // Определяем тип по первому полю
        if (line.substr(0, 3) == "Car")
        {
            vehicles.push_back(Car::deserialize(line));
        }
        else if (line.substr(0, 5) == "Truck")
        {
            vehicles.push_back(Truck::deserialize(line));
        }
        else if (line.substr(0, 7) == "Minivan")
        {
            vehicles.push_back(Minivan::deserialize(line));
        }
    }

    file.close();
    return vehicles;
}

/**
 * @brief Сохранить транспортные средства в файл
 * @param vehicles Вектор указателей на объекты
 * @param filename Имя файла для сохранения
 */
void saveVehicles(const std::vector<Vehicle*>& vehicles, const std::string& filename)
{
    std::ofstream file(filename);
    
    if (!file.is_open())
    {
        std::cerr << "Не удалось открыть файл для записи: " << filename << std::endl;
        return;
    }

    for (const auto& vehicle : vehicles)
    {
        // Используем dynamic_cast для определения типа и сериализации
        if (const Minivan* minivan = dynamic_cast<const Minivan*>(vehicle))
        {
            file << minivan->serialize() << std::endl;
        }
        else if (const Car* car = dynamic_cast<const Car*>(vehicle))
        {
            file << car->serialize() << std::endl;
        }
        else if (const Truck* truck = dynamic_cast<const Truck*>(vehicle))
        {
            file << truck->serialize() << std::endl;
        }
        else if (const LandVehicle* lv = dynamic_cast<const LandVehicle*>(vehicle))
        {
            file << lv->serialize() << std::endl;
        }
    }

    file.close();
}

/**
 * @brief Демонстрация полиморфизма
 * @param vehicle Указатель на базовый класс
 */
void demonstratePolymorphism(Vehicle* vehicle)
{
    std::cout << "\n=== Полиморфный вызов ===" << std::endl;
    std::cout << vehicle->getInfo() << std::endl;
    std::cout << vehicle->startEngine() << std::endl;
    std::cout << vehicle->move() << std::endl;
}

int main()
{
    std::cout << "=== Лабораторная работа №4: Транспортные средства ===" << std::endl;
    std::cout << "=== Вариант 2: Иерархия классов с множественным наследованием ===" << std::endl;

    // 1. Загрузка объектов из файла
    std::cout << "\n--- 1. Загрузка транспортных средств из файла ---" << std::endl;
    std::vector<Vehicle*> vehicles = loadVehicles("../data/vehicles.txt");
    std::cout << "Загружено объектов: " << vehicles.size() << std::endl;
    std::cout << "Счётчик объектов Vehicle: " << Vehicle::getObjectCount() << std::endl;

    // 2. Вывод информации о всех объектах
    std::cout << "\n--- 2. Информация о всех транспортных средствах ---" << std::endl;
    for (size_t i = 0; i < vehicles.size(); ++i)
    {
        std::cout << i + 1 << ". " << vehicles[i]->getInfo() << std::endl;
    }

    // 3. Демонстрация полиморфизма через указатели на базовый класс
    std::cout << "\n--- 3. Демонстрация полиморфизма ---" << std::endl;
    if (!vehicles.empty())
    {
        demonstratePolymorphism(vehicles[0]);  // Car
        if (vehicles.size() > 3)
            demonstratePolymorphism(vehicles[3]);  // Truck
        if (vehicles.size() > 6)
            demonstratePolymorphism(vehicles[6]);  // Minivan
    }

    // 4. Работа со статическими членами
    std::cout << "\n--- 4. Статические члены класса ---" << std::endl;
    std::cout << "Максимальная зарегистрированная скорость: " 
              << Vehicle::getMaxSpeed() << " км/ч" << std::endl;
    std::cout << "Общее количество объектов Vehicle: " 
              << Vehicle::getObjectCount() << std::endl;

    // 5. Создание новых объектов разных типов
    std::cout << "\n--- 5. Создание новых объектов ---" << std::endl;
    
    Car* newCar = new Car("Lada Vesta", 180, 4, 1400, 5);
    std::cout << "Создан: " << newCar->getInfo() << std::endl;
    
    Truck* newTruck = new Truck("KAMAZ 5490", 130, 18, 14000, 25000);
    std::cout << "Создан: " << newTruck->getInfo() << std::endl;
    
    Minivan* newMinivan = new Minivan("GAZelle NEXT", 140, 4, 1900, 13, 1500);
    std::cout << "Создан: " << newMinivan->getInfo() << std::endl;

    vehicles.push_back(newCar);
    vehicles.push_back(newTruck);
    vehicles.push_back(newMinivan);

    std::cout << "Новое количество объектов: " << Vehicle::getObjectCount() << std::endl;
    std::cout << "Новая максимальная скорость: " << Vehicle::getMaxSpeed() << " км/ч" << std::endl;

    // 6. Тестирование конструктора копирования и оператора присваивания
    std::cout << "\n--- 6. Копирование и присваивание ---" << std::endl;
    
    Car originalCar("Tesla Model 3", 261, 4, 1800, 5);
    std::cout << "Оригинал: " << originalCar.getInfo() << std::endl;
    
    // Конструктор копирования
    Car copiedCar(originalCar);
    std::cout << "Копия (конструктор): " << copiedCar.getInfo() << std::endl;
    
    // Оператор присваивания
    Car assignedCar("Nissan Leaf", 150, 4, 1600, 5);
    assignedCar = originalCar;
    std::cout << "Копия (присваивание): " << assignedCar.getInfo() << std::endl;
    
    // Проверка независимости копий
    originalCar.boardPassengers(3);
    std::cout << "\nПосле изменения оригинала:" << std::endl;
    std::cout << "Оригинал: пассажиров " << originalCar.getCurrentPassengers() << std::endl;
    std::cout << "Копия: пассажиров " << copiedCar.getCurrentPassengers() << std::endl;
    std::cout << "Присвоенная копия: пассажиров " << assignedCar.getCurrentPassengers() << std::endl;
    std::cout << "✓ Копии независимы от оригинала" << std::endl;

    // 7. Работа с интерфейсами IPassengerCarrier и ICargoCarrier
    std::cout << "\n--- 7. Работа с интерфейсами ---" << std::endl;
    
    Car* car1 = dynamic_cast<Car*>(vehicles[0]);
    if (car1)
    {
        std::cout << "\nЛегковой автомобиль: " << car1->getBrand() << std::endl;
        std::cout << "Вместимость: " << car1->getPassengerCapacity() << " пассажиров" << std::endl;
        std::cout << "Текущих пассажиров: " << car1->getCurrentPassengers() << std::endl;
        
        if (car1->boardPassengers(2))
        {
            std::cout << "✓ Посадили 2 пассажиров. Теперь: " 
                      << car1->getCurrentPassengers() << std::endl;
        }
    }

    Truck* truck1 = dynamic_cast<Truck*>(vehicles[3]);
    if (truck1)
    {
        std::cout << "\nГрузовик: " << truck1->getBrand() << std::endl;
        std::cout << "Грузоподъёмность: " << truck1->getCargoCapacity() << " кг" << std::endl;
        std::cout << "Текущий груз: " << truck1->getCurrentCargo() << " кг" << std::endl;
        
        if (truck1->loadCargo(3000))
        {
            std::cout << "✓ Загрузили 3000 кг. Теперь: " 
                      << truck1->getCurrentCargo() << " кг" << std::endl;
        }
    }

    // 8. Множественное наследование (Minivan)
    std::cout << "\n--- 8. Множественное наследование (Minivan) ---" << std::endl;
    
    Minivan* minivan1 = dynamic_cast<Minivan*>(vehicles[6]);
    if (minivan1)
    {
        std::cout << "Минивэн: " << minivan1->getBrand() << std::endl;
        std::cout << minivan1->getInfo() << std::endl;
        
        // Работа как с пассажирским ТС
        std::cout << "\n→ Работа с пассажирами:" << std::endl;
        IPassengerCarrier* asPassenger = minivan1;
        std::cout << "Вместимость: " << asPassenger->getPassengerCapacity() << " чел." << std::endl;
        if (asPassenger->boardPassengers(2))
        {
            std::cout << "✓ Посадили 2 пассажиров" << std::endl;
        }
        
        // Работа как с грузовым ТС
        std::cout << "\n→ Работа с грузами:" << std::endl;
        ICargoCarrier* asCargo = minivan1;
        std::cout << "Грузоподъёмность: " << asCargo->getCargoCapacity() << " кг" << std::endl;
        if (asCargo->loadCargo(200))
        {
            std::cout << "✓ Загрузили 200 кг груза" << std::endl;
        }
        
        std::cout << "\nИтоговое состояние минивэна:" << std::endl;
        std::cout << minivan1->getInfo() << std::endl;
        std::cout << minivan1->move() << std::endl;
    }

    // 9. Дружественная функция
    std::cout << "\n--- 9. Дружественная функция ---" << std::endl;
    if (vehicles.size() >= 2)
    {
        LandVehicle* lv1 = dynamic_cast<LandVehicle*>(vehicles[0]);
        LandVehicle* lv2 = dynamic_cast<LandVehicle*>(vehicles[3]);
        
        if (lv1 && lv2)
        {
            std::cout << vehicles[0]->getType() << " (" << lv1->getMass() << " кг) vs "
                      << vehicles[3]->getType() << " (" << lv2->getMass() << " кг)" << std::endl;
            
            if (isHeavier(*lv1, *lv2))
            {
                std::cout << "→ Первое транспортное средство тяжелее" << std::endl;
            }
            else
            {
                std::cout << "→ Второе транспортное средство тяжелее" << std::endl;
            }
        }
    }

    // 10. Сброс максимальной скорости
    std::cout << "\n--- 10. Статическая функция resetMaxSpeed ---" << std::endl;
    std::cout << "Текущая максимальная скорость: " << Vehicle::getMaxSpeed() << " км/ч" << std::endl;
    Vehicle::resetMaxSpeed();
    std::cout << "После сброса: " << Vehicle::getMaxSpeed() << " км/ч" << std::endl;

    // 11. Сохранение обновлённых данных в файл
    std::cout << "\n--- 11. Сохранение данных в файл ---" << std::endl;
    saveVehicles(vehicles, "../data/vehicles_updated.txt");
    std::cout << "✓ Данные сохранены в vehicles_updated.txt" << std::endl;

    // 12. Очистка памяти
    std::cout << "\n--- 12. Очистка памяти ---" << std::endl;
    std::cout << "Удаление " << vehicles.size() << " объектов..." << std::endl;
    
    for (auto vehicle : vehicles)
    {
        delete vehicle;
    }
    vehicles.clear();
    
    std::cout << "Объектов Vehicle осталось: " << Vehicle::getObjectCount() << std::endl;

    std::cout << "\n=== Все тесты выполнены успешно! ===" << std::endl;
    
    return 0;
}
