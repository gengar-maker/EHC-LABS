cmake_minimum_required(VERSION 3.14)



set(CMAKE_CXX_COMPILER "icx-cl")
set(CMAKE_C_COMPILER "icx-cl")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-O3 -Qopt-report=max -debug -fsycl)

# /arch:CORE-AVX2 -Qopenmp /QxCORE-AVX2

project(mmult)
project(aos_soa)
project(vector_remainder)
project(vector_map)
project(vector_functions)
project(sycl_example)

add_subdirectory(1_mmult)
add_subdirectory(2_aos_soa)
add_subdirectory(3_vector_remainder)
add_subdirectory(4_vector_map)
add_subdirectory(sycl_example)
# add_subdirectory(5_vector_functions)