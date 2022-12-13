# NeutronLogger
Part of the [NeutronEngine](https://github.com/AW1534/NeutronEngine) Project.

[Example](https://github.com/AW1534/NeutronEngine/tree/master/NeutronExample/Logging)

## What is NeutronLogger?
NeutronLogger is a simple logging library for C++. It is designed to be easy to use and easy to integrate into your project.
It is a part of the NeutronEngine project, but I like it so much I decided to make it a standalone library to be used in other projects.

My personal favourite feature of NeutronLogger is that it can catch exceptions such as segfaults and tell you where they happened. yay :)

## Setup
Set the `BOOST_STACKTRACE_USE_BACKTRACE` define in your project to use the backtrace library.

Also set either `COMPILE_DEBUG` or `COMPILE_RELEASE` to compile the library in debug or release mode.

An example CMakelists.txt file:
```cmake
project(NeutronExampleLogging DESCRIPTION "An example project for NeutronEngine made to show off Logging")

project(NeutronExampleLogging)
file(GLOB_RECURSE NEL_FILES "./NeutronExample/Logging/*")

include_directories(NeutronLogger/include)
add_executable(NeutronExampleLogging ${NEL_FILES})
target_link_libraries(NeutronExampleLogging NeutronEngine)
include_directories(NeutronEngine/Neutron/include)
```


## How to use
```cpp
#include <Logger/Logger.h>

// using namespace Logger; // (if you do this, you can use the functions without the Logger:: prefix)

int main(int argc, char* argv[]) {
    // Log some messages
    Logger::Log("Hello World!");
    Logger::Warn("This is a warning!", "Namespace");
    Logger::Crit("This is a critical error!", "Namespace"); // critcial errors will not end the program execution, but will print a stack trace.
    Logger::LogAt("This is another critical error!", Logger::Levels::CRIT, "Namespace"); // you can also use the LogAt function to log at a specific level.
    
    Logger::Error("This is an error!", "Namespace"); // errors will end the program execution.
    
    return 0;
}
```