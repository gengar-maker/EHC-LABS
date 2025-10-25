
file(GLOB SOURCE_V0 *.cpp)

project(primary_nums LANGUAGES CXX)

add_executable(primary_nums ${SOURCE_V0})

# https://www.intel.com/content/www/us/en/docs/advisor/user-guide/2023-0/build-target.html
target_compile_options(primary_nums PRIVATE /I$ENV{ONEAPI_ROOT}\\advisor\\latest\\include)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
