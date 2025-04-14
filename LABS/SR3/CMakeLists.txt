
file(GLOB SOURCE_V0 *.cpp)

project(nqeens LANGUAGES CXX)

add_executable(nqeens ${SOURCE_V0})

target_compile_options(nqeens PRIVATE /Qopt-report:max /QxCORE-AVX2 /ZI /DEBUG /Qipo- /Qopenmp /O3)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
