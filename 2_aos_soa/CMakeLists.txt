
file(GLOB SOURCE_V0 *.cpp)

project(aos_soa LANGUAGES CXX)

add_executable(aos_soa ${SOURCE_V0})

# https://www.intel.com/content/www/us/en/docs/advisor/user-guide/2023-0/build-target.html
target_compile_options(aos_soa PRIVATE /I$ENV{ONEAPI_ROOT}\\advisor\\latest\\include)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
