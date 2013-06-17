cmake_minimum_required (VERSION 2.6)

if (MSVC)
	SET(TPN_WIN32 "/EHsc")
else (MSVC)
	SET(CMAKE_CXX_FLAGS "-std=c++11")
	add_definitions(-std=c++11)
endif (MSVC)

set (PROJECT RunningMan)

project (${PROJECT})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set (HEADERS
	BasicStructs.h
	BitmapProvider.h
	GameField.h
	GameViewFrame.h
	ImageLoader.h
	#LodePngImageLoader.h
	Paths.h
	SdlBitmap.h
	Sprite.h
	SpriteInfoProvider.h
    SpriteProvider.h
    Surface.h
	)

set (SOURCES
	BasicStructs.cpp
	BitmapProvider.cpp
	GameField.cpp
	GameViewFrame.cpp
	ImageLoader.cpp
	#LodePngImageLoader.cpp
	main.cpp
	Paths.cpp
	SdlBitmap.cpp
	Sprite.cpp
	SpriteInfoProvider.cpp
	SpriteProvider.cpp
	)

set (LIBS
    SDL
    SDLmain
    SDL_image
    lodepng
	)

if(MSVC)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL-1.2.15/include
						${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/include
                        ${CMAKE_CURRENT_SOURCE_DIR}/../libs/lodepng/include
                        d:/libs/boost_1_53_0)

    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL-1.2.15/lib/x86
					${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/lib/x86
                    ${CMAKE_BINARY_DIR}/libs/lodepng
				    d:/libs/boost_1_53_0/lib)
else(MSVC)
	find_package(Boost COMPONENTS system filesystem REQUIRED)
	if (Boost_FOUND)
		MESSAGE(boost found)
	endif (Boost_FOUND)

	foreach(lib ${Boost_LIBRARIES})
		message(${lib})
	endforeach(lib)

	set(LIBS
		${LIBS}
		${Boost_LIBRARIES}
		)
endif(MSVC)

add_executable(${PROJECT} WIN32 ${HEADERS} ${SOURCES})

ADD_DEPENDENCIES(${PROJECT} lodepng)

#if (SDL_FOUND)
#    include_directories(${SDL_INCLUDE_DIR})
#    target_link_libraries (helloworld ${SDL_LIBRARY})
#endif (SDL_FOUND)


target_link_libraries(
    ${PROJECT}
    ${LIBS}
	)

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

message("hello")
macro(CopyDllsToProgramFolder dllPathNames)
	message("again")
	foreach(dllPathName 
				${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL-1.2.15/lib/x86/sdl.dll
				${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/lib/x86/SDL_image.dll
				${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/lib/x86/libjpeg-8.dll
				${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/lib/x86/libpng15-15.dll
				${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/lib/x86/libtiff-5.dll
				${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/lib/x86/libwebp-2.dll
				${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/lib/x86/zlib1.dll)
		message(${dllPathName})
		ADD_CUSTOM_COMMAND(TARGET ${PROJECT}
				  POST_BUILD
				  COMMAND ${CMAKE_COMMAND} -E copy ${dllPathName} ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR})
	endforeach(dllPathName)
endmacro(CopyDllsToProgramFolder)

set(DLLS
				${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL-1.2.15/lib/x86/sdl.dll
				${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/lib/x86/SDL_image.dll
				${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/lib/x86/libjpeg-8.dll
				${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/lib/x86/libpng15-15.dll
				${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/lib/x86/libtiff-5.dll
				${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/lib/x86/libwebp-2.dll
				${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/lib/x86/zlib1.dll)

CopyDllsToProgramFolder(${DLLS})

#if (MSVC)
#    ADD_CUSTOM_COMMAND(TARGET ${PROJECT}
#              POST_BUILD
#              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL-1.2.15/lib/x86/sdl.dll ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}
#              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/lib/x86/SDL_image.dll ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}
#    )

#    ADD_CUSTOM_COMMAND(TARGET ${PROJECT}
#              POST_BUILD
#              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/lib/x86/*.dll ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}
#    )
#endif (MSVC)

#ADD_CUSTOM_COMMAND(TARGET ${PROJECT}
#    POST_BUILD
 #   COMMAND ${CMAKE_COMMAND} create_directory ${CMAKE_BINARY_DIR}/data)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../data/ DESTINATION ${CMAKE_BINARY_DIR}/data)

# ADD_CUSTOM_COMMAND(TARGET ${PROJECT}
#    POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../data ${CMAKE_BINARY_DIR}/data)
