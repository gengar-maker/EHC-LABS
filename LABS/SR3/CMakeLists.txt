
file(GLOB SOURCE_V0 *.cpp)

project(nqeens LANGUAGES CXX)

add_executable(nqeens ${SOURCE_V0})
set_property(TARGET nqeens PROPERTY CXX_STANDARD 17)
target_compile_options(nqeens PRIVATE /Qopt-report:5 /QxCORE-AVX2 /ZI /DEBUG /Qipo- /Qopenmp /O3)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
