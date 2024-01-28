#!/bin/bash

# Создаем директорию для сборки
mkdir -p build

# Переходим в директорию сборки
cd build

# Генерируем Makefile с помощью CMake и указываем Ninja в качестве генератора
cmake -G Ninja ..

# Собираем проект с помощью Ninja
ninja

# Запускаем исполняемый файл
./telegram_bot
