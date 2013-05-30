cmake_minimum_required (VERSION 2.6)

set (PROJECT Test)

project (${PROJECT})

set (SOURCES
    Test.cpp
    ../src/HelloFunctions.cpp)
    
set (HEADERS
    ../src/HelloFunctions.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/gtest-1.6.0/include)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/gtest-1.6.0/lib/${CMAKE_CFG_INTDIR})

# if(${CMAKE_CFG_INTDIR} MATCHES "Debug")
    # target_link_libraries(${PROJECT} gtestd)
# elseif(${CMAKE_CFG_INTDIR} MATCHES "Release")
    # target_link_libraries(${PROJECT} gtest)
# endif(${CMAKE_CFG_INTDIR} MATCHES "Debug")

add_executable(${PROJECT} ${HEADERS} ${SOURCES})

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
