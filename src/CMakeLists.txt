cmake_minimum_required (VERSION 2.6)

set (PROJECT RunningMan)

project (${PROJECT})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set (HEADERS
	BasicStructs.h
	GameField.h
	GameViewFrame.h
	SdlBitmap.h
	Sprite.h
    SpriteProvider.h
	)

set (SOURCES
	BasicStructs.cpp
	GameField.cpp
	GameViewFrame.cpp
	main.cpp
	SdlBitmap.cpp
	Sprite.cpp
	SpriteProvider.cpp
	)

if(MSVC)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL-1.2.15/include
                        d:/libs/boost_1_53_0)

    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL-1.2.15/lib/x86
				    d:/libs/boost_1_53_0/lib)
endif(MSVC)

add_executable(${PROJECT} WIN32 ${HEADERS} ${SOURCES})

if (SDL_FOUND)
    include_directories(${SDL_INCLUDE_DIR})
    target_link_libraries (helloworld ${SDL_LIBRARY})
endif (SDL_FOUND)

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
    # SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows")
    # set_target_properties(${PROJECT} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
    # set_target_properties(${PROJECT} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
endif (MSVC)

if (WIN32)
    ADD_CUSTOM_COMMAND(TARGET ${PROJECT}
              POST_BUILD
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL-1.2.15/lib/x86/sdl.dll ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}
    )
endif (WIN32)
