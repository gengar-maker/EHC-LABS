
file(GLOB SOURCE_V0 *.cpp)

project(graph LANGUAGES CXX)

add_executable(graph ${SOURCE_V0})

target_compile_options(graph PRIVATE /Qopt-report:5 /QxCORE-AVX2 /ZI /DEBUG /Qipo- /Qopenmp /O3)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
