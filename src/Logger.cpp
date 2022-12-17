//
// Created by awilt on 23/10/22.
//

#include <ctime>
#include <iostream>
#include <csignal>
#include <utility>
#include <sstream>

#include <boost/stacktrace.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "../include/Logger/Logger.h"
#include "../include/Logger/Helper.h"

using namespace Logger::Utils::Helper;
namespace Logger {

    void initLogger() {
#ifdef LOGGER_VERBOSE
        Logger::Info("Logger initialized", Logger::Config::system_name);
#endif

        // register signal handlers

        for (int x : {SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV, SIGTERM}) {
            signal(x, exitHandler);
        }
    }


    void exitHandler(int sig) {
        // get exit code name from signal number
        int mod = 1;

        std::string exitCode;

        switch (sig) {
            case SIGABRT:
                exitCode = "SIGABRT";
                break;
            case SIGFPE:
                exitCode = "SIGFPE";
                break;
            case SIGILL:
                exitCode = "SIGILL";
                break;
            case SIGINT:
                exitCode = "SIGINT";
                break;
            case SIGSEGV:
                exitCode = "SIGSEGV";
                break;
            case SIGTERM:
                Logger::Log("Term signal received, exiting", Logger::Config::system_name);
                return;

            default:
                exitCode = "UNKNOWN";
                break;
        }

        try {
            Logger::Error("Exiting with signal " + std::to_string(sig) + " (" + exitCode + ")", Logger::Config::system_name, mod, 1);
        } catch (std::exception &e) {
            std::cerr << "Error while logging exit signal " << sig << " (" << exitCode << "): " << e.what() << std::endl;
        }

        exit(sig);
    }

    std::string fill(std::string str, int len = 2, char fill = 48) {
        if (str.length() < len)
            str.insert(str.front() == '-' ? 1 : 0, len - str.length(), fill);
        return str;
    }

    std::string prettyStacktrace(std::string t, int highlight_frame, std::string highlight_color, int keep_going) {
        Logger::Log("prettyStacktrace");
        std::vector<std::string> t_list = split(t);

        int current_trace = highlight_frame;

        #ifdef BOOST_STACKTRACE_USE_BACKTRACE
        // -- Insert a snippet of the most important frame's respective file right below it (only if we have access to boost stacktrace) -- //

        bool done = false;

        int max_iterations = 5;

        while (!done) {
            max_iterations--;
            if (max_iterations == 0) {
                current_trace = highlight_frame;
                done = true;
            }
            std::string stack =  t_list[current_trace];

            //Logger::Log(stack);

            // if " at " is not in this stack frame, add keep_going to current_trace and try again
            if (stack.find(" at ") == std::string::npos && max_iterations != 0 && keep_going != 0) {
                current_trace += keep_going; // keep_going is usually 1 or -1 meaning go up or down the stacktrace in search of a frame with " at "
                continue;
            }

            std::vector<std::string> file_and_line = split(split(stack, " at ")[1],":");
            std::string filename = file_and_line[0];
            int line = parseInt(file_and_line[1]);

            int min_line = line - 1;
            int max_line = line + 1;

            std::vector<int> t_lines = {};
            std::vector<std::string> important_lines = readLines_gi(filename, t_lines, min_line, max_line);

            std::ostringstream oss;

            int i = 0;
            for (std::string x : important_lines) {
                if (t_lines[i] == line) {
                    oss << highlight_color;
                    oss << "\n  * ";
                    oss << RESET;
                } else {
                    oss << "\n    ";
                }

                oss << fill(std::to_string(t_lines[i]), 2, ' ') << RESET << FORE_GRAY << " | " << RESET << x << RESET;
                i++;
            }
            std::string s = oss.str();
            t_list[current_trace] = stack + oss.str();

            done = true;
        }
        #endif

        t = join(t_list, "\n");

        // -- Highlight the most important frame and dim the others -- //
        for (int x : range(t_list.size())) {

            std::string c_color;
            if (x == current_trace) {
                c_color = highlight_color + BOLD;
            } else {
                c_color = FORE_GRAY;
            }

            std::string n = fill(std::to_string(x), 2, 32);

            boost::replace_all(t, n + "# ", c_color + n + "# " + RESET);
        }

        return t;
    }

    std::string fancyTime() {
        time_t currentTime;
        struct tm *localTime;

        time(&currentTime);
        localTime = localtime(&currentTime);

        std::string Hour = fill(std::to_string(localTime->tm_hour));
        std::string Min = fill(std::to_string(localTime->tm_min));
        std::string Sec = fill(std::to_string(localTime->tm_sec));

        return "[" + Hour + ":" + Min + ":" + Sec + "]";
    }

    void Info(std::basic_string<char> text, std::string name) {
        if (Config::level >= Levels::INFO) { return; }

        if (name != "") {
            name = "[" + name + "] ";
        }

        std::stringstream end;

        end << FORE_GRAY;
        end << BOLD;
        end << fancyTime() << " ";
        end << name;
        end << RESET;
        end << text;

        *Config::output << end.str() << std::endl;
    }

    void Log(std::string text, std::string name) {
        if (Config::level >= Levels::LOG) {return;}

        if (name != "") {
            name = "[" + name + "] ";
        }

        std::stringstream end;

        end << FORE_GRAY;
        end << BOLD;
        end << fancyTime() << " ";
        end << name;
        end << RESET;
        end << text;

        *Config::output << end.str() << std::endl;
    }

    void Warn(std::string text, std::string name) {
        if (Config::level >= Levels::WARN) {return;}

        if (name != "") {
            name = "[" + name + "] ";
        }

        std::stringstream end;

        end << FORE_YELLOW;
        end << BOLD;
        end << fancyTime() << " ";
        end << name << "WARNING: ";
        end << RESET;
        end << text;

        *Config::output << end.str() << std::endl;
    }

    void Crit(std::string text, std::string name, int stack_mod, int keep_going) {
        if (Config::level >= Levels::CRIT) {return;}

        if (name != "") {
            name = "[" + name + "] ";
        }

        std::stringstream end;

        end << FORE_BRIGHT_MAGENTA;
        end << BOLD;
        end << fancyTime() << " ";
        end << name << "CRITICAL: ";
        end << RESET;
        end << text;
        end << "\n";
        end << prettyStacktrace(to_string(boost::stacktrace::stacktrace()), 1 + stack_mod, FORE_BRIGHT_MAGENTA, keep_going);

        *Config::output << end.str() << std::endl;
    }

    void Crit(std::basic_string<char> text, std::string name, std::string stack_trace) {
        if (Config::level >= Levels::CRIT) {return;}

        if (name != "") {
            name = "[" + name + "] ";
        }

        std::stringstream end;

        end << FORE_BRIGHT_MAGENTA;
        end << BOLD;
        end << fancyTime() << " ";
        end << name << "CRITICAL: ";
        end << RESET;
        end << text;
        end << "\n";
        end << stack_trace;

        *Config::output << end.str() << std::endl;
    }
    void Error(std::basic_string<char> text, std::string name, std::string stack_trace) {
        if (Config::level >= Levels::ERROR) {return;}

        if (name != "") {
            name = "[" + name + "] ";
        }

        std::stringstream end;

        end << FORE_BRIGHT_RED;
        end << BOLD;
        end << fancyTime() << " ";
        end << name << "ERROR: ";
        end << RESET;
        end << text;
        end << "\n";
        end << stack_trace;

        *Config::output << end.str() << std::endl;
    }

    void Error(std::string text, std::string name, int stack_mod, int keep_going) {
        if (Config::level >= Levels::ERROR) { return; }

        if (name != "") {
            name = "[" + name + "] ";
        }

        std::stringstream end;

        end << FORE_RED;
        end << BOLD;
        end << fancyTime() << " ";
        end << name << "Error: ";
        end << RESET;
        end << text;
        end << "\n";
        end << prettyStacktrace(to_string(boost::stacktrace::stacktrace()), 1 + stack_mod, FORE_RED, keep_going);

        *Config::output << end.str() << std::endl;

        exit(1);
    }

    void LogAt(int level, std::basic_string<char> message, std::string name, int stack_mod) {
        if (level == 5) Error(message, name, stack_mod+1);
        else if (level == 4) Crit(message, name, stack_mod+1);
        else if (level == 3) Warn(message, name);
        else if (level == 2) Log(message, name);
        else if (level == 1) Info(message, name);
    }

    bool Assert(bool condition, std::basic_string<char> error, int level, std::string name) {
        if (condition) return true;

        LogAt(level, std::move(error), std::move(name), 1);

        return false;
    }

}