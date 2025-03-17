
file(GLOB SOURCE_V0 *.cpp)

project(primary_nums LANGUAGES CXX)

add_executable(primary_nums ${SOURCE_V0})

target_compile_options(primary_nums PRIVATE /ZI /DEBUG /Qipo- /QxCOMMON-AVX512 /Qopt-zmm-usage:high /O3 /I"C:\\Program Files (x86)\\Intel\\oneAPI\\advisor\\latest\\include")

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
