set(CMAKE_CXX_STANDARD 17)
project(NeutronLogger)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(NeutronLogger SHARED ${SOURCES})