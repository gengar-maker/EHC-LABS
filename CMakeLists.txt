cmake_minimum_required(VERSION 3.21.0)
<<<<<<< HEAD
=======

# set (CMAKE_GENERATOR "Ninja" CACHE STRING "" FORCE)
>>>>>>> ebc351269a351b3f0543576061f2f33f37b1c5f9

project(EHC_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(1_mmult)
add_subdirectory(2_aos_soa)
add_subdirectory(3_vector_remainder)
add_subdirectory(4_vector_map)
add_subdirectory(6_primary_nums)
<<<<<<< HEAD

add_subdirectory(LABS)
=======
# add_subdirectory(sycl_example)
# add_subdirectory(n_vector)
# add_subdirectory(5_vector_functions)
>>>>>>> ebc351269a351b3f0543576061f2f33f37b1c5f9
