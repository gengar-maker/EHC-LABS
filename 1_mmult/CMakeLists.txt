
file(GLOB SOURCE_V0 *.cpp)

project(mmult LANGUAGES CXX)

add_executable(mmult ${SOURCE_V0})

# https://www.intel.com/content/www/us/en/docs/advisor/user-guide/2023-0/build-target.html
target_compile_options(mmult PRIVATE /ZI /DEBUG /O3 /Qopt-report:max /Qvec /Qipo- /I$ENV{ONEAPI_ROOT}\\advisor\\latest\\include)
# target_compile_options(mmult PRIVATE /O3 /Qvec)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
