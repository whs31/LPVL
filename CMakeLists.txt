cmake_minimum_required (VERSION 3.15)

project(LPVL LANGUAGES CXX)

if(TARGET ${PROJECT_NAME})
  return()
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS Core Quick)

include_directories(include src/c++)

file(GLOB_RECURSE LPVL_CORE src/c++/*)
file(GLOB_RECURSE LPVL_CORE_INCLUDE include/*)

set(SRC ${LPVL_CORE} ${LPVL_CORE_INCLUDE})

add_subdirectory(libs/CTRE)
add_library(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC
  Qt5::Core
  Qt5::Quick
  CTRE
)

target_include_directories(${PROJECT_NAME} PUBLIC include src)
