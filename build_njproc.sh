#!/bin/bash

# Создаем директорию для сборки
mkdir -p build

# Переходим в директорию сборки
cd build

# Генерируем Makefile с помощью CMake
cmake ..

# Собираем проект
make -j$((`nproc`+1))

# Запускаем исполняемый файл
./telegram_bot