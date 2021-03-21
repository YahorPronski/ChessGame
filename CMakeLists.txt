# The minimum version of CMake required
cmake_minimum_required(VERSION 3.15)
# The project name
project(kursovaya_final)
# The C++ standard version. Can be 98 11 14 or 17
set(CMAKE_CXX_STANDARD 14)
set(SFML_INCLUDE_DIR "./SFML/include")
set(SFML_LIBRARY_DIR "./SFML/build/lib")
link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/kursovaya_final/src/Application.cpp
        ${PROJECT_SOURCE_DIR}/kursovaya_final/Headers/Model/Data.h
        ${PROJECT_SOURCE_DIR}/kursovaya_final/Headers/Model/Moves.h
        ${PROJECT_SOURCE_DIR}/kursovaya_final/Headers/Model/SquareFinders.h
        ${PROJECT_SOURCE_DIR}/kursovaya_final/Headers/Model/Values.h
        ${PROJECT_SOURCE_DIR}/kursovaya_final/Headers/ViewModel/OnClickHandler.h
        ${PROJECT_SOURCE_DIR}/kursovaya_final/src/Model/Data.cpp
        ${PROJECT_SOURCE_DIR}/kursovaya_final/src/Model/Moves.cpp
        ${PROJECT_SOURCE_DIR}/kursovaya_final/src/Model/SquareFinders.cpp
        ${PROJECT_SOURCE_DIR}/kursovaya_final/src/ViewModel/OnClickHandler.cpp

        )
target_link_libraries (${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
