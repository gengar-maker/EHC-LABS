
file(GLOB SOURCE_V0 *.cpp)

project(vector_remainder LANGUAGES CXX)

add_executable(vector_remainder ${SOURCE_V0})
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
