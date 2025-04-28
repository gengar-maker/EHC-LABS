cmake_minimum_required(VERSION 3.21.0)

project(EHC_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(1_mmult)
add_subdirectory(2_aos_soa)
add_subdirectory(3_primary_nums)
add_subdirectory(4_vector_remainder)
add_subdirectory(4_vector_map)
add_subdirectory(4_vector_intrinsics)

add_subdirectory(LABS)

add_subdirectory(n-body-example)

