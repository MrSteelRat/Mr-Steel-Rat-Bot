cmake_minimum_required(VERSION 3.16)

project(Sofi_Si_Body_Therapy)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_GENERATOR "Ninja" CACHE STRING "Ninja")
set(Boost_USE_MULTITHREADED ON)

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time") 
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

enable_testing()

# Укажите пути к заголовочным файлам вашего проекта
include_directories(/usr/local/include)

# Укажите пути к библиотекам
set(CMAKE_PREFIX_PATH "/usr/local" ${CMAKE_PREFIX_PATH})

# Укажите библиотеки, которые нужно подключить

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(SQLite3)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

# Создайте исполняемый файл
add_subdirectory(module)
# Получите список всех файлов исходного кода в каталоге 'module'
file(GLOB MODULE_SOURCES module/*.cpp)
file(GLOB MODULE_HEADERS module/*.h)

# Создайте исполняемый файл и добавьте файлы исходного кода
add_executable(telegram_bot src/main.cpp ${MODULE_SOURCES} ${MODULE_HEADERS})

# Assuming your executable target is named "telegram_bot"
# Укажите пути к заголовочным файлам из module
target_include_directories(telegram_bot PRIVATE module)

# Подключите библиотеки к вашему исполняемому файлу
target_link_libraries(telegram_bot PRIVATE /usr/local/lib/libTgBot.a Boost::system ssl crypto pthread SQLite::SQLite3)

# Добавьте статическую линковку с библиотекой C++
target_link_libraries(telegram_bot PRIVATE stdc++)

# Добавьте тесты с использованием Google Test
#add_subdirectory(tests)

# Добавьте цель для тестирования
#add_test(NAME my_tests COMMAND telegram_bot_tests)
