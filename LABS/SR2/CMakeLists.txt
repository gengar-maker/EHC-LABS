
file(GLOB SOURCE_V0 *.cpp)

project(sle LANGUAGES CXX)

add_executable(sle ${SOURCE_V0})

target_compile_options(sle PRIVATE /Qopt-report:max /QxCORE-AVX2 /ZI /DEBUG /Qipo- /Qopenmp /O3)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
