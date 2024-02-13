cmake_minimum_required(VERSION 3.14)

# set(CMAKE_CXX_COMPILER "icx-cl.exe")
# set(CMAKE_C_COMPILER "icx-cl.exe")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-O3)

project(Lab1)

# add_subdirectory(1_mmult)
add_subdirectory(2_aos_soa)
