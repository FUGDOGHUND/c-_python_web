# 🐍 Змейка на C++ с веб-интерфейсом

Простая реализация классической игры "Змейка" на C++ с использованием:
- **Crow** (микро-фреймворк для веб-сервера)
- **Boost** (для многопоточности и тестирования)
- **Docker** (для контейнеризации)

http://176.123.168.39:8080/

## 📋 Требования
- Компилятор C++ (GCC ≥ 9 или Clang)
- CMake (≥ 3.10)
- Boost (≥ 1.70)
- Docker (опционально)

## 🚀 Быстрый старт

wget https://github.com/CrowCpp/Crow/releases/download/v1.0%2B5/crow_all.h -O include/crow.h


### Сборка и запуск
```bash
git clone https://github.com/FUGDOGHUND/zmeyka_na_cplusplus.git
cd zmeyka_na_cplusplus
make build
make run
```

##Запуск тестов
```bashmake test ```
##🐳 Запуск через Docker
```
docker build -t snake-game .
docker run -p 8080:8080 snake-game
```
# Тест только Boost компонентов
make boost-test

# Тест Crow + Boost
make crow-test

# Полный тест всех компонентов
make full-test


make ci  # Проверка зависимостей → сборка → все тесты


# Запуск всех тестов
make full-test

# Или по отдельности
make unit-test       
# Только юнит-тесты
make integration-test 
```
# Только интеграционные тесты
docker build -t snake-game-test .
docker run --rm snake-game-test
````
    Тестирование ASIO - проверка асинхронных операций

    Тестирование потоков - проверка работы boost::thread

    Тестирование ошибок - валидация системы ошибок Boost

    Интеграция с Crow - проверка работы веб-фреймворка

    Автоматическая проверка версий - через check-boost-version
