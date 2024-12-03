# Минимальная версия CMake
cmake_minimum_required(VERSION 3.14)

# Название проекта и стандарт C++
project(SDLTextExample VERSION 1.0 LANGUAGES CXX)

# Установить стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указываем пути к заголовочным файлам и библиотекам (если они нестандартные)
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

# Автоматически добавляем все .cpp файлы из src/ и .h файлы из include/
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

# Добавляем исполняемый файл
add_executable(sdl_demo ${SOURCES} ${HEADERS})

# Линкуем библиотеки SDL2 и SDL2_ttf
target_link_libraries(sdl_demo SDL2 SDL2_ttf SDL2_image)

target_include_directories(sdl_demo PRIVATE include) # instead of include "include/some_file.h"

