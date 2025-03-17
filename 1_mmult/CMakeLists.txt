
file(GLOB SOURCE_V0 *.cpp)

project(mmult LANGUAGES CXX)

add_executable(mmult ${SOURCE_V0})

target_compile_options(mmult PRIVATE /ZI /DEBUG /Qipo- /QxCORE-AVX2 /O3 /I"C:\\Program Files (x86)\\Intel\\oneAPI\\advisor\\latest\\include")

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
