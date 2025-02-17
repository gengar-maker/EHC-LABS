
file(GLOB SOURCE_V0 *.cpp)

project(vector_map LANGUAGES CXX)

add_executable(vector_map ${SOURCE_V0})
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
