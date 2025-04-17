# Базовый образ с компилятором
FROM ubuntu:22.04 as builder

# Установка зависимостей
RUN apt-get update && \
    apt-get install -y \
    g++ \
    make \
    libboost-all-dev \
    wget \
    python3-pip && \
    rm -rf /var/lib/apt/lists/*

# Установка Crow
RUN mkdir -p include && \
    wget https://github.com/CrowCpp/Crow/releases/download/v1.0%2B5/crow_all.h -O include/crow.h

# Копирование исходников
WORKDIR /app
COPY . .

# Сборка и тестирование
RUN make build && \
    make unit-test && \
    make integration-test

# Финальный образ
FROM ubuntu:22.04

# Установка рантайм-зависимостей
RUN apt-get update && \
    apt-get install -y \
    libboost-system1.74.0 \
    libboost-thread1.74.0 && \
    rm -rf /var/lib/apt/lists/*

# Копируем бинарники
COPY --from=builder /app/snake /app/snake
COPY --from=builder /app/tests/unit_test /app/tests/unit_test
COPY --from=builder /app/tests/integration_test /app/tests/integration_test

# Тестовые команды
CMD ["sh", "-c", "./tests/unit_test && ./tests/integration_test && ./snake"]
