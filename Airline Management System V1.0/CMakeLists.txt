#Author: Mohamed Newir
#Date: 10/5/2025
#File Name: CMakelists.txt
#Description: This file is used to compile the source code for the project
#             and set the required version of cmake and the required standard version of C++.
#             It also sets the compile options and the include directories for the project. 

#set the minimum required version of cmake
cmake_minimum_required(VERSION 3.10)

#set the project name
project(Air_Line_Management_V1.0
        VERSION 1.0.0
        DESCRIPTION "Air Line Management V1.0"
        LANGUAGES CXX)

#CPP standard version required for the project  
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set the sources to be compiled 
set(SOURCES 
    ./Source/main.cpp
    ./Source/aircraft.cpp
    ./Source/airlineSystem.cpp
    ./Source/dataHandling.cpp
    ./Source/flight.cpp
    ./Source/users.cpp
)

#add the executable
add_executable(Output ${SOURCES})
#add the include directories
target_include_directories(Output PRIVATE ./Include)
#compile features required for the project
target_compile_features(Output PRIVATE cxx_std_17)
#add the compile options
# target_compile_options(Output PRIVATE -Wall -Wextra -Werror -Wpedantic)
