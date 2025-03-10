cmake_minimum_required(VERSION 3.21.0)

# set (CMAKE_GENERATOR "Ninja" CACHE STRING "" FORCE)

project(EHC_project)

# find_package(IntelSYCL REQUIRED)

# if(IntelSYCL_FOUND)
#     message(STATUS "Using Intel compiler")
# endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(1_mmult)
add_subdirectory(2_aos_soa)
add_subdirectory(3_vector_remainder)
add_subdirectory(4_vector_map)
add_subdirectory(6_primary_nums)
# add_subdirectory(sycl_example)
# add_subdirectory(n_vector)
# add_subdirectory(5_vector_functions)
