//
// Created by awilt on 23/10/22.
//

#ifndef EXPORT
#define EXPORT /*NO EXPORT MACRO*/
#endif

#ifndef NEUTRONLOGGER_H
#define NEUTRONLOGGER_H

#include <list>
#include <cstdio>
#include <iostream>


#ifndef BOOST_STACKTRACE_USE_BACKTRACE
#ifndef COMPILE_RELEASE
#warning BOOST_STACKTRACE_USE_BACKTRACE was not set, so the Neutron Logging system will be limited. Please set the macro and recompile
#endif
#endif

//TODO: provide some sort of stream

__attribute__((constructor)) void initLogger();

namespace Logger {
    enum Levels {
        ERROR = 5,
        CRIT = 4,
        WARN = 3,
        LOG = 2,
        INFO = 1,
        ALL = 0
    };

    void Info(std::basic_string<char> text, std::string name = "");
    void Log(std::basic_string<char> text, std::string name = "");
    void Warn(std::basic_string<char> text, std::string name = "");
    void Crit(std::basic_string<char> text, std::string name = "", int stack_mod = 0);
    void Error(std::basic_string<char> text, std::string name = "", int stack_mod = 0);

    bool Assert(bool condition, std::basic_string<char> error = "Assertion failed", int level = 4, std::string name = "");
    void LogAt(int level, std::basic_string<char> message, std::string name = "", int stack_mod = 0);

    struct Config {
        inline static std::ostream* output = &std::cout;
        inline static int level = Levels::ALL;
    };
}

#endif //NEUTRONLOGGER_H
