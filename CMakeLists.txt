cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)

project(NeutronLogger DESCRIPTION "A Logging system written for the Neutron game engine, but has been seperated for general purpose use.")

set(N_LOGGER_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../include)


file(GLOB_RECURSE LOGGER_LIB_INCLUDE_FILES "include/*")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(PLATFORM_TEGRA)
    add_compile_definitions(BOOST_STACKTRACE_USE_BACKTRACE)
    add_compile_definitions(COMPILE_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(COMPILE_RELEASE)
endif()

add_library(NeutronLogger STATIC src/Helper.cpp src/Files.cpp src/Logger.cpp)