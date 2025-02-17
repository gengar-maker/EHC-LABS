
file(GLOB SOURCE_V0 *.cpp)

project(mmult LANGUAGES CXX)

add_executable(mmult ${SOURCE_V0})

target_compile_options(mmult PRIVATE /ZI /DEBUG /Qopt-report:5)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
