cmake_minimum_required(VERSION 2.8.12)

# Change this to your project's name
set(PROJECT_NAME "Sample")

project(${PROJECT_NAME} CXX C)

# This template purpose is for experimenting, so start from v0.0.1
exec_program(
    "git"
    ${CMAKE_CURRENT_SOURCE_DIR}
    ARGS "describe" "--tags"
    OUTPUT_VARIABLE VERSION_FULL)

string(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR "${VERSION_FULL}")
string(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${VERSION_FULL}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${VERSION_FULL}")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# Avoid source tree pollution
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files already created:\nrm -rf CMakeCache.txt CMakeFiles")
endif(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)

if(WIN32)
    string(REGEX REPLACE "\\\\" "/" OGRE_HOME "$ENV{OGRE_HOME}") 
elseif(UNIX)
	if(EXISTS "/usr/local/lib/OGRE")
	  set(OGRE_HOME "/usr/local/lib/OGRE")
	elseif(EXISTS "/usr/lib/OGRE")
	  set(OGRE_HOME "/usr/lib/OGRE")
	else ()
	  message(SEND_ERROR "Failed to find module path.")
	endif(EXISTS "/usr/local/lib/OGRE")
endif(WIN32)
set(CMAKE_MODULE_PATH "${OGRE_HOME}/CMake/;${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
 
if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif (CMAKE_BUILD_TYPE STREQUAL "")

set(CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")

if (WIN32)
    set(Boost_USE_STATIC_LIBS TRUE)
    set(Boost_USE_MULTITHREADED TRUE)
    set(Boost_USE_STATIC_RUNTIME FALSE)
else ()
    set(Boost_USE_STATIC_LIBS FALSE)
    set(Boost_USE_MULTITHREADED TRUE)
    set(Boost_USE_STATIC_RUNTIME FALSE)
endif (WIN32)
find_package(Boost COMPONENTS system thread filesystem REQUIRED) # Specify the required components

find_package(SDL2 REQUIRED)

find_package(OGRE REQUIRED)
if (${OGRE_VERSION} VERSION_LESS "2.1" OR ${OGRE_VERSION} VERSION_GREATER "2.2")
    message(FATAL_ERROR "${PROJECT_NAME} requires Ogre 2.1")
endif()
set(OGRE_SDK_BUILD TRUE)
set(OGRE_TEMPLATES_DIR "${OGRE_HOME}/CMake")
include(OgreAddTargets)
include(OgreConfigTargets)

find_package(OIS REQUIRED)
if(NOT OIS_FOUND)
	message(SEND_ERROR "Failed to find OIS.")
endif()

# Specify build paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
if (WIN32 OR APPLE)
  if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # We don't want to install in default system location, install is really for the SDK, so call it that
    set(CMAKE_INSTALL_PREFIX
	  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}" CACHE PATH "${PROJECT_NAME} install prefix" FORCE
    )
  endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
endif(WIN32 OR APPLE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
