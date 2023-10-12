cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_COMPILER "icx-cl.exe")
set(CMAKE_C_COMPILER "icx-cl.exe")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Lab1)

add_subdirectory(1_mmult_scalar)
