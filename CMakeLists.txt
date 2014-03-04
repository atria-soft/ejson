cmake_minimum_required(VERSION 2.8)

# Declare the project
project(ejson)

##
## Include C++ X11 dependency ... (check correct flags)
##
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
	CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
	if(COMPILER_SUPPORTS_CXX0X)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	else()
		message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
	endif()
endif()


# set output path:
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

include_directories(.)

#Create src file list
set(src_files
	ejson/debug.cpp
	ejson/debug.h
	ejson/ejson.cpp
	ejson/ejson.h
	ejson/Array.cpp
	ejson/Array.h
	ejson/Boolean.cpp
	ejson/Boolean.h
	ejson/Null.cpp
	ejson/Null.h
	ejson/Number.cpp
	ejson/Number.h
	ejson/String.cpp
	ejson/String.h
	ejson/Object.cpp
	ejson/Object.h
	ejson/Value.cpp
	ejson/Value.h
)

add_definitions( -DDEBUG_LEVEL=3 )
add_definitions( -DDEBUG=1 )
if (APPLE)
	add_definitions( -D__TARGET_OS__MacOs )
elseif (UNIX)
	add_definitions( -D__TARGET_OS__Linux )
elseif (WIN32)
	add_definitions( -D__TARGET_OS__Windows )
endif ()


include_directories(${etk_SOURCE_DIR})
include_directories(${linearmath_SOURCE_DIR}/bullet/src/)

#Create a static Lib:
add_library(ejson STATIC ${src_files} )
target_link_libraries(ejson etk)

