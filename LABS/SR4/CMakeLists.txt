
file(GLOB SOURCE_V0 *.cpp)

project(graph LANGUAGES CXX)

add_executable(graph ${SOURCE_V0})

# https://www.intel.com/content/www/us/en/docs/advisor/user-guide/2023-0/build-target.html
target_compile_options(graph PRIVATE /ZI /DEBUG /O3 /Qopt-report:max /Qvec /Qipo- /I$ENV{ONEAPI_ROOT}\\advisor\\latest\\include)
# target_compile_options(graph PRIVATE /O3 /Qvec)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
