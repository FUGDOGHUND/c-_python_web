# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -pedantic
LDFLAGS = -lboost_system -lpthread -lboost_thread -lboost_unit_test_framework

# Основные цели
.PHONY: all build run clean

all: build

build:
	$(CXX) $(CXXFLAGS) -o snake src/main.cpp src/game.cpp $(LDFLAGS)

run: build
	./snake

clean:
	rm -f snake tests/unit_test tests/integration_test *.o

# Тестирование
.PHONY: test unit-test integration-test full-test check-deps

test: unit-test integration-test

unit-test:
	$(CXX) $(CXXFLAGS) -o tests/unit_test tests/unit_test.cpp src/game.cpp $(LDFLAGS)
	./tests/unit_test

integration-test:
	$(CXX) $(CXXFLAGS) -o tests/integration_test tests/integration_test.cpp src/game.cpp $(LDFLAGS)
	./tests/integration_test --log_level=test_suite

full-test: unit-test integration-test
	@echo "Все тесты пройдены успешно!"

check-deps:
	@echo "Проверка зависимостей..."
	@which $(CXX) >/dev/null || (echo "Ошибка: g++ не установлен" && exit 1)
	@which make >/dev/null || (echo "Ошибка: make не установлен" && exit 1)
	@dpkg -l | grep -q libboost-dev || (echo "Ошибка: libboost-dev не установлен" && exit 1)
	@echo "Все зависимости в порядке ✓"
