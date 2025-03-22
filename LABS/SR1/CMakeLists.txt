
file(GLOB SOURCE_V0 *.cpp)

project(integral LANGUAGES CXX)

add_executable(integral ${SOURCE_V0})

target_compile_options(integral PRIVATE /Qopt-report:5 /QxCORE-AVX2 /ZI /DEBUG /Qipo- /Qopenmp /O3)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
