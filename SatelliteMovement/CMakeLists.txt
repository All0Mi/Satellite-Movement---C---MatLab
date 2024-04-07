cmake_minimum_required(VERSION 3.26)
project(SatelliteMovement)

set(CMAKE_CXX_STANDARD 17)

#find_package(Catch2 3 REQUIRED HINTS /opt/catch2/lib/cmake/Catch2)
#find_package(Catch2 3 REQUIRED HINTS "./Catch2/build/lib/lib/cmake/Catch2/")


add_executable(SatelliteMovement main.cpp
        src/const.h
        src/Satellite/Satellite.h
        src/Plot/Plot.cpp
        src/Plot/Plot.h
        src/CalcEngine/CalcEngine.cpp
        src/CalcEngine/CalcEngine.h
        src/SatRange/SatRange.h
        src/Vector3/Vector3.h
        src/Initializer/Initializer.h
        src/RandomGenerator/RandomGenerator.h
        src/Saver/Saver.h
        src/SafeVector/SafeVector.h
        src/SatelliteData/SatelliteData.h
        src/SatelliteData/SatelliteData.cpp
        src/Saver/Saver.cpp
        src/Simulator/Simulator.cpp
)

configure_file("src/Plot/scripts/matlabPlot.m" "matlabPlot.m" COPYONLY)
#target_link_libraries(SatelliteMovement PRIVATE  Catch2::Catch2 Catch2::Catch2WithMain)
#include_directories(${CATCH2_INCLUDE_DIRECTORIES})

#include(Catch)
#catch_discover_tests(SatelliteMovement)

add_subdirectory(tests)