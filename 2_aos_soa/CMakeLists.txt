
file(GLOB SOURCE_V0 *.cpp)

project(aos_soa LANGUAGES CXX)

add_executable(aos_soa ${SOURCE_V0})
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
