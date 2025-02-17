
file(GLOB SOURCE_V0 *.cpp)
project(n_vector)

# find_package( OpenCV REQUIRED )
# include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(n_vector ${SOURCE_V0})

# target_link_libraries( DisplayImage ${OpenCV_LIBS} )

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

