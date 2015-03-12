cmake_minimum_required(VERSION 2.8.3)
project(ejson)

set(CMAKE_VERBOSE_MAKEFILE ON)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  etk
  )


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS ../
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS etk
  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  ..
  ${catkin_INCLUDE_DIRS}
)

## Declare a cpp library
add_library(${PROJECT_NAME}
  ../${PROJECT_NAME}/debug.cpp
  ../${PROJECT_NAME}/ejson.cpp
  ../${PROJECT_NAME}/Array.cpp
  ../${PROJECT_NAME}/Boolean.cpp
  ../${PROJECT_NAME}/Null.cpp
  ../${PROJECT_NAME}/Number.cpp
  ../${PROJECT_NAME}/String.cpp
  ../${PROJECT_NAME}/Object.cpp
  ../${PROJECT_NAME}/Value.cpp
)

set(CMAKE_CXX_FLAGS "-std=c++11 -DDEBUG_LEVEL=3 -DDEBUG=1 -D__CPP_VERSION__=2011")


## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
#add_dependencies(${PROJECT_NAME} test_perfo_core_generate_messages_cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark cpp header files for installation
install(DIRECTORY ../${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)
