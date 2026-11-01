# Лабораторная работа №4 — Наследование и полиморфизм. Вариант 2: Транспортные средства

Все команды выполняются из этой папки (`lab4/`).

## Задание

Создать иерархию транспортных средств: от абстрактного `Vehicle` через `LandVehicle` к `Car` и `Truck`. Также добавить «способность к перевозке пассажиров» и «грузоподъёмность» как отдельные интерфейсы. Реализовать класс `Minivan` с множественным наследованием.

## Структура проекта

```
lab4/
├── include/              # Заголовочные файлы
│   ├── Vehicle.h         # Абстрактный базовый класс
│   ├── LandVehicle.h     # Промежуточный класс
│   ├── Car.h             # Легковой автомобиль
│   ├── Truck.h           # Грузовик
│   ├── Minivan.h         # Минивэн (множественное наследование)
│   ├── IPassengerCarrier.h  # Интерфейс перевозки пассажиров
│   └── ICargoCarrier.h   # Интерфейс перевозки грузов
├── src/                  # Реализация классов
│   ├── Vehicle.cpp
│   ├── LandVehicle.cpp
│   ├── Car.cpp
│   ├── Truck.cpp
│   └── Minivan.cpp
├── tests/
│   └── main.cpp          # Тестовая программа
├── data/
│   └── vehicles.txt      # Данные объектов (10 шт)
├── diagrams/
│   └── vehicles_hierarchy.puml  # UML диаграмма
├── build/
│   ├── static/           # Статическая библиотека и тест
│   └── dynamic/          # Динамическая библиотека и тест
├── Doxyfile              # Конфигурация Doxygen
├── .gitignore
└── README.md
```

## Иерархия классов

```
Vehicle (абстрактный)
    ↑
    | (виртуальное наследование)
    |
LandVehicle (промежуточный)
    ↑
    |
    ├── Car ← IPassengerCarrier
    ├── Truck ← ICargoCarrier
    └── Minivan ← Car + ICargoCarrier
```

### Особенности реализации

1. **Виртуальное наследование**: `LandVehicle` виртуально наследуется от `Vehicle` для решения проблемы "алмаза" (diamond problem) в `Minivan`
2. **Множественное наследование**: `Minivan` наследуется от `Car` и реализует `ICargoCarrier`
3. **Чисто виртуальные функции**: `startEngine()`, `move()`, `getType()` в `Vehicle`
4. **Виртуальная функция с реализацией**: `getInfo()` в `Vehicle` с переопределением в производных классах
5. **Статические члены**:
   - `globalMaxSpeed_` — максимальная зарегистрированная скорость
   - `objectCount_` — счётчик созданных объектов
6. **Дружественная функция**: `isHeavier()` для сравнения массы наземных ТС

## Сборка проекта

Все команды выполняются из папки `lab4/`.

### Вариант 1: Статическая библиотека (Windows)

```cmd
REM Создаём директорию для сборки
mkdir build\static

REM Компилируем объектные файлы
g++ -std=c++14 -Wall -Wextra -Iinclude -c src/Vehicle.cpp -o build/static/Vehicle.o
g++ -std=c++14 -Wall -Wextra -Iinclude -c src/LandVehicle.cpp -o build/static/LandVehicle.o
g++ -std=c++14 -Wall -Wextra -Iinclude -c src/Car.cpp -o build/static/Car.o
g++ -std=c++14 -Wall -Wextra -Iinclude -c src/Truck.cpp -o build/static/Truck.o
g++ -std=c++14 -Wall -Wextra -Iinclude -c src/Minivan.cpp -o build/static/Minivan.o

REM Создаём статическую библиотеку
ar rcs build/static/liblab4.a build/static/Vehicle.o build/static/LandVehicle.o build/static/Car.o build/static/Truck.o build/static/Minivan.o

REM Линкуем тестовую программу
g++ -std=c++14 -Wall -Wextra -Iinclude tests/main.cpp build/static/liblab4.a -o build/static/test.exe

REM Запускаем тесты
build\static\test.exe
```

### Вариант 2: Статическая библиотека (Linux)

```bash
# Создаём директорию для сборки
mkdir -p build/static

# Компилируем объектные файлы
g++ -std=c++14 -Wall -Wextra -Iinclude -c src/Vehicle.cpp -o build/static/Vehicle.o
g++ -std=c++14 -Wall -Wextra -Iinclude -c src/LandVehicle.cpp -o build/static/LandVehicle.o
g++ -std=c++14 -Wall -Wextra -Iinclude -c src/Car.cpp -o build/static/Car.o
g++ -std=c++14 -Wall -Wextra -Iinclude -c src/Truck.cpp -o build/static/Truck.o
g++ -std=c++14 -Wall -Wextra -Iinclude -c src/Minivan.cpp -o build/static/Minivan.o

# Создаём статическую библиотеку
ar rcs build/static/liblab4.a build/static/*.o

# Линкуем тестовую программу
g++ -std=c++14 -Wall -Wextra -Iinclude tests/main.cpp build/static/liblab4.a -o build/static/test

# Запускаем тесты
./build/static/test
```

### Вариант 3: Динамическая библиотека (Windows)

```cmd
mkdir build\dynamic

REM Компилируем с -fPIC для динамической библиотеки
g++ -std=c++14 -Wall -Wextra -fPIC -Iinclude -c src/Vehicle.cpp -o build/dynamic/Vehicle.o
g++ -std=c++14 -Wall -Wextra -fPIC -Iinclude -c src/LandVehicle.cpp -o build/dynamic/LandVehicle.o
g++ -std=c++14 -Wall -Wextra -fPIC -Iinclude -c src/Car.cpp -o build/dynamic/Car.o
g++ -std=c++14 -Wall -Wextra -fPIC -Iinclude -c src/Truck.cpp -o build/dynamic/Truck.o
g++ -std=c++14 -Wall -Wextra -fPIC -Iinclude -c src/Minivan.cpp -o build/dynamic/Minivan.o

REM Создаём динамическую библиотеку
g++ -shared -o build/dynamic/liblab4.dll build/dynamic/*.o

REM Линкуем тестовую программу
g++ -std=c++14 -Wall -Wextra -Iinclude tests/main.cpp -Lbuild/dynamic -llab4 -o build/dynamic/test.exe

REM Запускаем тесты (DLL должна быть в PATH или в той же папке)
build\dynamic\test.exe
```

### Вариант 4: Динамическая библиотека (Linux)

```bash
mkdir -p build/dynamic

# Компилируем с -fPIC
g++ -std=c++14 -Wall -Wextra -fPIC -Iinclude -c src/Vehicle.cpp -o build/dynamic/Vehicle.o
g++ -std=c++14 -Wall -Wextra -fPIC -Iinclude -c src/LandVehicle.cpp -o build/dynamic/LandVehicle.o
g++ -std=c++14 -Wall -Wextra -fPIC -Iinclude -c src/Car.cpp -o build/dynamic/Car.o
g++ -std=c++14 -Wall -Wextra -fPIC -Iinclude -c src/Truck.cpp -o build/dynamic/Truck.o
g++ -std=c++14 -Wall -Wextra -fPIC -Iinclude -c src/Minivan.cpp -o build/dynamic/Minivan.o

# Создаём динамическую библиотеку
g++ -shared -o build/dynamic/liblab4.so build/dynamic/*.o

# Линкуем тестовую программу
g++ -std=c++14 -Wall -Wextra -Iinclude tests/main.cpp -Lbuild/dynamic -llab4 -o build/dynamic/test

# Запускаем тесты (добавляем путь к .so в LD_LIBRARY_PATH)
LD_LIBRARY_PATH=build/dynamic:$LD_LIBRARY_PATH ./build/dynamic/test
```

## Работа с данными

Файл `data/vehicles.txt` содержит 10 объектов:

- 3 объекта `Car` (легковые автомобили)
- 3 объекта `Truck` (грузовики)
- 3 объекта `Minivan` (минивэны)

Формат сериализации:

- Car: `Car;brand;maxSpeed;wheelCount;mass;passengerCapacity;currentPassengers`
- Truck: `Truck;brand;maxSpeed;wheelCount;mass;cargoCapacity;currentCargo`
- Minivan: `Minivan;brand;maxSpeed;wheelCount;mass;passengerCapacity;currentPassengers;cargoCapacity;currentCargo`

## Тестирование

Программа `tests/main.cpp` демонстрирует:

1. ✓ Загрузку 10 объектов из файла
2. ✓ Полиморфизм через указатели на базовый класс
3. ✓ Работу статических членов (`getMaxSpeed()`, `getObjectCount()`, `resetMaxSpeed()`)
4. ✓ Создание объектов всех типов
5. ✓ Конструктор копирования и оператор присваивания
6. ✓ Проверку независимости копий
7. ✓ Работу с интерфейсами `IPassengerCarrier` и `ICargoCarrier`
8. ✓ Множественное наследование в `Minivan`
9. ✓ Дружественную функцию `isHeavier()`
10. ✓ Корректную очистку памяти

## Соответствие требованиям задания

| №   | Требование                                      | Реализация                                             |
| --- | ----------------------------------------------- | ------------------------------------------------------ |
| 1   | Иерархия из 3 уровней                           | `Vehicle` → `LandVehicle` → `Car`/`Truck`/`Minivan`    |
| 2   | Абстрактный базовый класс                       | `Vehicle` с чисто виртуальными функциями               |
| 3   | Чисто виртуальные функции                       | `startEngine()`, `move()`, `getType()`                 |
| 4   | Виртуальная функция с реализацией               | `getInfo()` в `Vehicle` с переопределением             |
| 5   | Конструктор копирования и оператор присваивания | Реализованы во всех классах                            |
| 6   | Глубокое копирование                            | Проверено в тестах (независимость копий)               |
| 7   | Статическая функция                             | `getMaxSpeed()`, `resetMaxSpeed()`, `getObjectCount()` |
| 8   | Статический член данных                         | `globalMaxSpeed_`, `objectCount_`                      |
| 9   | Полиморфизм                                     | Через указатели на `Vehicle*`                          |
| 10  | Множественное наследование                      | `Minivan` : `Car` + `ICargoCarrier`                    |
| 11  | Виртуальное наследование                        | `LandVehicle` : virtual `Vehicle`                      |
| 12  | Дружественная функция                           | `friend bool isHeavier(...)`                           |
| 13  | Многофайловая структура                         | Каждый класс в отдельных .h и .cpp                     |
| 14  | Статическая библиотека                          | `liblab4.a` / `lab4.lib`                               |
| 15  | Динамическая библиотека                         | `liblab4.so` / `lab4.dll`                              |
| 16  | Две тестовые программы                          | `test_static` и `test_dynamic`                         |
| 17  | Данные в файле                                  | 10 объектов в `data/vehicles.txt`                      |
| 18  | Ручная сборка g++                               | Скрипты содержат прямые вызовы компилятора             |

## Диаграмма классов

Исходник — `diagrams/vehicles_hierarchy.puml`. Генерация изображения:

```bash
java -jar plantuml.jar -charset UTF-8 diagrams/vehicles_hierarchy.puml
```

## Документация (Doxygen)

```bash
doxygen Doxyfile
```

Результат: `docs/html/index.html`

## Примечания

1. **Проблема "алмаза"**: Решена с помощью виртуального наследования в `LandVehicle`
2. **Множественное наследование в Minivan**: Класс может работать и как пассажирское, и как грузовое ТС
3. **Сериализация**: Каждый класс знает, как сохранить и восстановить свое состояние
4. **Статические члены**: Отслеживают глобальную статистику по всем транспортным средствам
5. **Дружественная функция**: Имеет доступ к `private` полю `mass_` класса `LandVehicle`
