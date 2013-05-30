cmake_minimum_required (VERSION 2.6)

set (PROJECT RunningMan)

project (${PROJECT})

set (HEADERS
    )
    
set (SOURCES
    main.cpp)
    
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL-1.2.15/include)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL-1.2.15/lib/x86)

add_executable(${PROJECT} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT} SDL SDLmain)

if (MSVC)
	# static link with runtime library
	foreach(flag_var
			CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
			CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
	   if(${flag_var} MATCHES "/MT")
		  string(REGEX REPLACE "/MT" "/MD" ${flag_var} "${${flag_var}}")
	   endif(${flag_var} MATCHES "/MT")
	endforeach(flag_var)
endif (MSVC)
