# module/CMakeLists.txt

# Получите список исходных файлов в module
file(GLOB MODULE_SOURCES *.cpp)

# Создайте библиотеку из исходных файлов
add_library(module_lib ${MODULE_SOURCES})

# Укажите пути к заголовочным файлам из module
target_include_directories(module_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
