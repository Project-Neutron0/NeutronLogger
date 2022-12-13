cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)
project(NeutronLogger)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_compile_definitions(LOGGER_COMPILE_VERBOSE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(BOOST_STACKTRACE_USE_BACKTRACE)
    add_compile_definitions(COMPILE_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(COMPILE_RELEASE)
endif()

add_library(NeutronLogger SHARED ${SOURCES})