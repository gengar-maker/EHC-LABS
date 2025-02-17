
file(GLOB SOURCE_V0 *.cpp)

project(aos_soa LANGUAGES CXX)

add_executable(aos_soa ${SOURCE_V0})

target_compile_options(aos_soa PRIVATE /ZI /DEBUG /Qopt-report:5)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
