cmake_minimum_required(VERSION 3.10)


project(ElevatorSimulation)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(SOURCES
    ControlPanel.cpp
    Elevator.cpp
    Floor.cpp
    Manager.cpp
    TestAssignment.cpp 
)


set(HEADERS
    ControlPanel.h
    Elevator.h
    Floor.h
    Manager.h
)


add_executable(ElevatorSimulation ${SOURCES} ${HEADERS})