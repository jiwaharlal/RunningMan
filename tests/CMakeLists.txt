cmake_minimum_required (VERSION 2.6)

SET(CMAKE_CXX_FLAGS "-std=c++11")
add_definitions(-std=c++11 -D_VARIADIC_MAX=10)

set (PROJECT Test)

add_subdirectory(gtest-1.6.0)

project (${PROJECT})

set (SOURCES
    Test.cpp
    ${PROJECT_SOURCE_DIR}/../src/BasicStructs.cpp
    ${PROJECT_SOURCE_DIR}/../src/GameField.cpp
    ${PROJECT_SOURCE_DIR}/../src/GameViewFrame.cpp
    ${PROJECT_SOURCE_DIR}/../src/Paths.cpp
    )

set (HEADERS
    ${PROJECT_SOURCE_DIR}/../src/BasicStructs.h
    ${PROJECT_SOURCE_DIR}/../src/GameField.h
    ${PROJECT_SOURCE_DIR}/../src/GameViewFrame.h
    ${PROJECT_SOURCE_DIR}/../src/Paths.cpp
    )

if (MSVC)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/gtest-1.6.0/include)
  link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/gtest-1.6.0/lib/${CMAKE_CFG_INTDIR})
  # target_link_libraries(${PROJECT} gtest)
endif (MSVC)

# if(${CMAKE_CFG_INTDIR} MATCHES "Debug")
    # target_link_libraries(${PROJECT} gtestd)
# elseif(${CMAKE_CFG_INTDIR} MATCHES "Release")
    # target_link_libraries(${PROJECT} gtest)
# endif(${CMAKE_CFG_INTDIR} MATCHES "Debug")

add_executable(${PROJECT} ${HEADERS} ${SOURCES})


include_directories(${gtest_INCLUDE_DIR})
target_link_libraries (${PROJECT} ${gtest_LIBRARY})
ADD_DEPENDENCIES(${PROJECT} gtest gtest_main)

link_directories(${CMAKE_CURRENT_BINARY_DIR}/gtest-1.6.0)
target_link_libraries(${PROJECT} gtest)

add_definitions(-D_VARIADIC_MAX=10)

if (MSVC)
	# static link with runtime library
	foreach(flag_var
			CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
			CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
	   if(${flag_var} MATCHES "/MD")
		  string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
	   endif(${flag_var} MATCHES "/MD")
	endforeach(flag_var)
endif (MSVC)

GET_TARGET_PROPERTY(BIN_NAME ${PROJECT} LOCATION)

# copy bin to binary folder
ADD_CUSTOM_COMMAND(TARGET ${PROJECT}
          POST_BUILD
          COMMAND ${BIN_NAME}
)
