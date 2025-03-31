
file(GLOB SOURCE_V0 *.cpp)

project(vector_intr LANGUAGES CXX)

add_executable(vector_intr ${SOURCE_V0})

target_compile_options(vector_intr PRIVATE /ZI /DEBUG /Qipo- /QxCORE-AVX2 /Qopt-report:max /Qvec-)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
