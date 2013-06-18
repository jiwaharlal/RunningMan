cmake_minimum_required (VERSION 2.6)

if (MSVC)
	SET(TPN_WIN32 "/EHsc")
	add_definitions(-D_VARIADIC_MAX=10)
else (MSVC)
	SET(CMAKE_CXX_FLAGS "-std=c++11")
	add_definitions(-std=c++11 -D_VARIADIC_MAX=10)
endif (MSVC)

set (PROJECT Test)

add_subdirectory(gtest-1.6.0)

project (${PROJECT})

set (SOURCES
    Test.cpp
    ${PROJECT_SOURCE_DIR}/../src/BasicStructs.cpp
    ${PROJECT_SOURCE_DIR}/../src/BitmapProvider.cpp
	${PROJECT_SOURCE_DIR}/../src/GameField.cpp
    ${PROJECT_SOURCE_DIR}/../src/GameViewFrame.cpp
    ${PROJECT_SOURCE_DIR}/../src/Paths.cpp
	${PROJECT_SOURCE_DIR}/../src/SdlBitmap.cpp
    ${PROJECT_SOURCE_DIR}/../src/Sprite.cpp
	${PROJECT_SOURCE_DIR}/../src/SpriteInfoProvider.cpp
	${PROJECT_SOURCE_DIR}/../src/SpriteProvider.cpp
    )

set (HEADERS
    ${PROJECT_SOURCE_DIR}/../src/BasicStructs.h
    ${PROJECT_SOURCE_DIR}/../src/BitmapProvider.h
    ${PROJECT_SOURCE_DIR}/../src/GameField.h
    ${PROJECT_SOURCE_DIR}/../src/GameViewFrame.h
    ${PROJECT_SOURCE_DIR}/../src/Paths.h
	${PROJECT_SOURCE_DIR}/../src/SdlBitmap.h
    ${PROJECT_SOURCE_DIR}/../src/Sprite.h
	${PROJECT_SOURCE_DIR}/../src/SpriteInfoProvider.h
	${PROJECT_SOURCE_DIR}/../src/SpriteProvider.h
    )

if (MSVC)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/gtest-1.6.0/include
					d:/libs/boost_1_53_0
					${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL-1.2.15/include
					${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/include)
  link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/gtest-1.6.0/lib/${CMAKE_CFG_INTDIR}
					d:/libs/boost_1_53_0/lib
					${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL-1.2.15/lib/x86
					${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL_image-1.2.12/lib/x86)
  # target_link_libraries(${PROJECT} gtest)
endif (MSVC)

# if(${CMAKE_CFG_INTDIR} MATCHES "Debug")
    # target_link_libraries(${PROJECT} gtestd)
# elseif(${CMAKE_CFG_INTDIR} MATCHES "Release")
    # target_link_libraries(${PROJECT} gtest)
# endif(${CMAKE_CFG_INTDIR} MATCHES "Debug")

add_executable(${PROJECT} ${HEADERS} ${SOURCES})


include_directories(${gtest_INCLUDE_DIR})
target_link_libraries (${PROJECT} ${gtest_LIBRARY} SDL SDLmain SDL_image)
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

message(${BIN_NAME})
#ADD_CUSTOM_COMMAND(TARGET ${PROJECT}
#          POST_BUILD
#          COMMAND -E ${BIN_NAME}
#)
