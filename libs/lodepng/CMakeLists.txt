set (SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/lodepng.cpp)
set (HDRS ${CMAKE_CURRENT_SOURCE_DIR}/include/lodepng.h)

add_library(lodepng ${SRCS} ${HDRS})