cmake_minimum_required (VERSION 3.15)

project(LPVL LANGUAGES CXX)

set(LPVL_COMPILE_TO_STATIC FALSE)
set(LPVL_TESTS_ENABLED FALSE)
set(LPVL_REMOVE_QT_RELATED_FUNCTIONS FALSE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT ${LPVL_REMOVE_QT_RELATED_FUNCTIONS})
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
        Core
        Quick
    )
endif()

if(${LPVL_TESTS_ENABLED})
    find_package(GTest)
endif()

include_directories(src include)

set(LPVL_CORE
    src/global/lpvlglobal.h
    src/global/lpvlregister.h src/global/lpvlregister.c++
    src/global/lpvlmath.h src/global/lpvlmath.c++

    src/geometry/lpvlglvertex.h
    src/geometry/lpvlglnodegeometry.h src/geometry/lpvlglnodegeometry.c++
    src/utils/lpvlcrypto.h src/utils/lpvlcrypto.c++

    src/quick/lpvlmatrixplot.h src/quick/lpvlmatrixplot.c++
    src/quick/lpvllineplot.h src/quick/lpvllineplot.c++
    src/quick/lpvlrealtimelineplot.h src/quick/lpvlrealtimelineplot.c++
)

set(LPVL_CORE_INCLUDE
    include/LPVL/Global
    include/LPVL/Register
    include/LPVL/Math
    include/LPVL/GLGeometry
    include/LPVL/MatrixPlot
    include/LPVL/LinePlot
    include/LPVL/RealtimeLinePlot
    include/LPVL/Crypto
)

set(SRC
    ${LPVL_CORE} ${LPVL_CORE_INCLUDE}
)

message("Compiling to static: ${LPVL_COMPILE_TO_STATIC}")
if(${LPVL_COMPILE_TO_STATIC})
    add_library(${PROJECT_NAME} ${SRC})
    target_compile_definitions (${PROJECT_NAME} PRIVATE LPVL_LIBRARY LPVL_STATIC)
else()
    add_library(${PROJECT_NAME} SHARED ${SRC} )
    target_compile_definitions (${PROJECT_NAME} PRIVATE LPVL_LIBRARY)
endif()

if (NOT ${LPVL_REMOVE_QT_RELATED_FUNCTIONS})
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Quick
    )
endif()

if(${LPVL_TESTS_ENABLED})
    set(TESTS
        ${SRC}
    )

    add_executable(test_lpvl ${TESTS})

    target_link_libraries(test_lpvl
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Quick
        GTest::GTest
    )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include src)

set_target_properties (${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "lpvl"
    PREFIX "lib"
)
