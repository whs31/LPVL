cmake_minimum_required (VERSION 3.15)

project(LPVL LANGUAGES CXX)

option(USE_QT_POSITIONING_LIBRARY
  "Link against Qt5::Positioning and expose Geo-related features"
  OFF
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)

if(USE_QT_POSITIONING_LIBRARY)
  message("Linking with Qt::Positioning.")
  find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core
    Quick
    Positioning
  )
else()
  find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core
    Quick
  )
endif()

include_directories( include src/c++ )

file(GLOB_RECURSE LPVL_CORE src/c++/*)
file(GLOB_RECURSE LPVL_CORE_INCLUDE include/*)

set(SRC ${LPVL_CORE} ${LPVL_CORE_INCLUDE})

add_library(${PROJECT_NAME} ${SRC})

if(USE_QT_POSITIONING_LIBRARY)
  target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Positioning
  )
else()
  target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
  )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include src)

