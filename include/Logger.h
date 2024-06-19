//
// Created by awilt on 23/10/22.
//

#ifndef EXPORT
#define EXPORT // This macro is defined by NeutronEngine. The code will still compile and work without it.
#endif

#ifndef NEUTRONLOGGER_H
#define NEUTRONLOGGER_H

#include <list>
#include <cstdio>
#include <iostream>
#include <boost/stacktrace.hpp>
#include <map>
#include <sstream>
#include <csignal>
#include <fstream>

#pragma region ANSI codes
#define FORE_BLACK "\e[30m"
#define FORE_RED "\e[31m"
#define FORE_GREEN "\e[32m"
#define FORE_YELLOW "\e[33m"
#define FORE_BLUE "\e[34m"
#define FORE_MAGENTA "\e[35m"
#define FORE_CYAN "\e[36m"
#define FORE_WHITE "\e[37m"
#define FORE_GRAY "\e[90m"
#define FORE_BRIGHT_RED "\e[91m"
#define FORE_BRIGHT_GREEN "\e[92m"
#define FORE_BRIGHT_YELLOW "\e[93m"
#define FORE_BRIGHT_BLUE "\e[94m"
#define FORE_BRIGHT_MAGENTA "\e[95m"
#define FORE_BRIGHT_CYAN "\e[96m"
#define FORE_BRIGHT_WHITE "\e[97m"

#define BACK_BLACK "\e[40m"
#define BACK_RED "\e[41m"
#define BACK_GREEN "\e[42m"
#define BACK_YELLOW "\e[43m"
#define BACK_BLUE "\e[44m"
#define BACK_MAGENTA "\e[45m"
#define BACK_CYAN "\e[46m"
#define BACK_WHITE "\e[47m"
#define BACK_GRAY "\e[100m"
#define BACK_BRIGHT_RED "\e[101m"
#define BACK_BRIGHT_GREEN "\e[102m"
#define BACK_BRIGHT_YELLOW "\e[103m"
#define BACK_BRIGHT_BLUE "\e[104m"
#define BACK_BRIGHT_MAGENTA "\e[105m"
#define BACK_BRIGHT_CYAN "\e[106m"
#define BACK_BRIGHT_WHITE "\e[107m"

#define RESET "\e[0m"
#define BOLD "\e[1m"
#define DIM "\e[2m"
#define ITALIC "\e[3m"
#define UNDERLINE "\e[4m"
#define SLOW_BLINK "\e[5m"
#define RAPID_BLINK "\e[6m"
#define INVERT "\e[7m"
#define CONCEAL "\e[8m"
#define CROSSED_OUT "\e[9m"
#pragma endregion

#ifndef BOOST_STACKTRACE_USE_BACKTRACE
#ifndef COMPILE_RELEASE
#warning BOOST_STACKTRACE_USE_BACKTRACE was not set, so the Neutron Logging system will be limited. Please set the macro and recompile
#endif
#endif

//TODO: provide some sort of stream

#ifndef LOGGER_NO_INIT
__attribute__((constructor)) void initLogger();
#else
void initLogger();
#endif

namespace Logger {
    enum Levels {
        ERROR = 5,
        CRIT = 4,
        WARN = 3,
        LOG = 2,
        INFO = 1,
        ALL = 0
    };

    template<typename T>
    inline std::string ContainerToString(const T& container);

    template<typename T>
    inline std::string AsString(T obj);

    inline std::vector<std::string> readLines_gi(std::string file, std::vector<int> &index_of, int min = 0, int max = -1);

    inline std::vector<std::string> readLines(std::string file, int min = 0, int max = -1);

    inline std::vector<std::string> readLines(std::string file, int max = -1);

    inline std::string read(std::string file);

    inline std::string read(std::string file);

    EXPORT inline std::vector<int> range(unsigned int start, unsigned int end, int step = 1);

    EXPORT inline  std::vector<int> range(unsigned int end);

    EXPORT inline std::vector<std::string> split(std::string string, std::string delimiter = "\n");

    template<typename T_t, typename T_s, typename T_r>
    inline std::string replace_all(T_t text, T_s search, T_r replace);

    template <typename T, typename J>
    EXPORT inline std::string join(std::vector<T> list, J join = " ");

    inline int parseInt(std::string str);

    struct Config;

    inline void exitHandler(int sig);

    inline void initLogger();

    inline std::string prettyStacktrace(std::string t, int highlight_frame = -1, std::string highlight_color = FORE_BRIGHT_MAGENTA);

    inline std::string fill(std::string str, int len, char fill);

    inline std::string fancyTime();

    inline std::string _indenter(std::string text, int indent);

    template <typename T>
    inline void Info(T text, std::string name = "");

    template <typename T>
    inline void Log(T text, std::string name = "");

    template <typename T>
    inline void Warn(T text, std::string name = "");

    template <typename T>
    inline void Crit(T text, std::string name = "", int stack_mod = 0);

    template <typename T>
    inline void Error(T text, std::string name = "", int stack_mod = 0);

    template <typename T>
    inline void LogAt(int level, T message, std::string name = "", int stack_mod = 0);

    template <typename T>
    inline bool Assert(bool condition, T text = "", int level = Levels::CRIT, std::string name = "");

    #pragma region bro wth

    // Helper traits to check for the presence of a nested type.
    template<typename, typename = std::void_t<>>
    struct has_first_type_impl : std::false_type {};

    template<typename T>
    struct has_first_type_impl<T, std::void_t<typename T::first_type>> : std::true_type {};

    template<typename, typename = std::void_t<>>
    struct has_second_type_impl : std::false_type {};

    template<typename T>
    struct has_second_type_impl<T, std::void_t<typename T::second_type>> : std::true_type {};

    template<typename, typename = std::void_t<>>
    struct has_key_type_impl : std::false_type {};

    template<typename T>
    struct has_key_type_impl<T, std::void_t<typename T::key_type>> : std::true_type {};

    template<typename, typename = std::void_t<>>
    struct has_mapped_type_impl : std::false_type {};

    template<typename T>
    struct has_mapped_type_impl<T, std::void_t<typename T::mapped_type>> : std::true_type {};

    template<typename, typename = std::void_t<>>
    struct has_value_type_impl : std::false_type {};

    template<typename T>
    struct has_value_type_impl<T, std::void_t<typename T::value_type>> : std::true_type {};

    // Convenience functions to check for the presence of nested types.
    template <typename T>
    constexpr bool has_first_type() {
        return has_first_type_impl<T>::value;
    }

    template <typename T>
    constexpr bool has_second_type() {
        return has_second_type_impl<T>::value;
    }

    template <typename T>
    constexpr bool has_key_type() {
        return has_key_type_impl<T>::value;
    }

    template <typename T>
    constexpr bool has_mapped_type() {
        return has_mapped_type_impl<T>::value;
    }

    template <typename T>
    constexpr bool has_value_type() {
        return has_value_type_impl<T>::value;
    }

    #pragma endregion bro wth

    template<typename T>
    std::string ContainerToString(const T& container) {
        std::string res;
        res += "{ ";
        res += join(container, ", ");
        res+= " }";
        return res;
    }

    template<typename T>
    std::string AsString(T obj) {
        std::string res = "Unsupported object of type [" + std::string(typeid(T).name()) + "]";

        try {
            if constexpr (std::is_convertible<T, std::string>::value) {
                res = (std::string)obj;
            } else if constexpr (std::is_convertible<T, char*>::value) {
                res = std::string((char*)obj);
            } else if constexpr (std::is_same<T, bool>::value) {
                res = obj ? "true" : "false";
            } else if constexpr (std::is_integral<T>::value || std::is_floating_point<T>::value) {
                res = std::to_string(obj);
            } else if constexpr (std::is_same<T, const char*>::value) {
                res = std::string(obj);
            } else if constexpr (std::is_same<T, const unsigned char*>::value) {
                res = std::string(reinterpret_cast<const char *>(obj));
            } else if constexpr (std::is_same<T, std::string_view>::value) {
                res = std::string(obj);
            } else if constexpr (std::is_same<T, std::wstring>::value) {
                res = std::string(obj.begin(), obj.end());
            } else if constexpr (std::is_same<T, std::u16string>::value) {
                res = std::string(obj.begin(), obj.end());
            } else if constexpr (std::is_same<T, std::u32string>::value) {
                res = std::string(obj.begin(), obj.end());
            } else if constexpr (has_value_type<T>()) {
                if constexpr (
                        std::is_same<T, std::vector<typename T::value_type>>::value ||
                        std::is_same<T, std::list<typename T::value_type>>::value
                        ) {
                    res = ContainerToString(obj);
                } else if constexpr (has_key_type<T>() && has_mapped_type<T>()) {
                    if constexpr (std::is_same<T, std::map<typename T::key_type, typename T::mapped_type>>::value) {
                        res = ContainerToString(obj);
                    }
                }
            } else if constexpr (has_first_type<T>() && has_second_type<T>()) {
                if constexpr (std::is_same<T, std::pair<typename T::first_type, typename T::second_type>>::value) {
                    res = "(" + AsString(obj.first) + ", " + AsString(obj.second) + ")";
                }
            } else {
                try {
                    res = (std::string)(obj);
                } catch (...) {
                    try {
                        res = static_cast<std::string>(obj);
                    }
                    catch(...) {
                        try {
                            const char* cstr = (const char*)(obj);
                            if (cstr != nullptr) {
                                res = std::string(cstr);
                            } else {
                                throw std::runtime_error("Conversion to const char* failed");
                            }
                        } catch (...) {
                            try {
                                std::stringstream ss;
                                ss << obj;
                                res = ss.str();
                            } catch (...) { }
                        }
                    }
                }
            }
        } catch(...) { }

        return res;
    }

    std::vector<std::string> readLines_gi(std::string file, std::vector<int> &index_of, int min, int max) {
        int m = max;

        std::fstream stream = std::fstream(file);

        std::string line;
        std::vector<std::string> end;

        int i = 0;

        while (getline(stream, line)) {
            i += 1;

            if (max < 0) (m = i + 1);

            if (i >= min && i <= m) {
                end.push_back(line);
                index_of.push_back(i);
            }
        }
        return end;
    }

    std::vector<std::string> readLines(std::string file, int min, int max ) {
        std::vector<int> v;
        return readLines_gi(std::move(file), v, min, max);
    }

    std::vector<std::string> readLines(std::string file, int max) {
        std::vector<int> v;
        return readLines_gi(std::move(file), v, 0, max);
    }

    std::string read(std::string file) {
        std::string end;

        std::vector<int> v;
        for (std::string x : readLines_gi(file, v, 0, -1)) {
            end.append(x + "\n");
        }

        return end;
    }

    EXPORT std::vector<int> range(unsigned int start, unsigned int end, int step) {
        std::vector<int> res = {};

        for(int x = start; x != end; x+=step) {
            res.push_back(x);
        }

        return res;
    }

    EXPORT std::vector<int> range(unsigned int end) {
        return range(0, end, 1);
    }

    EXPORT std::vector<std::string> split(std::string string, std::string delimiter) {
        std::vector<std::string> results;
        size_t pos = 0;
        while (true) {
            size_t next = string.find(delimiter, pos);
            results.push_back(string.substr(pos, next - pos));
            if (next == std::string::npos) break;
            pos = next + delimiter.size();
        }

        return results;
    }

    template<typename T_t, typename T_s, typename T_r>
    std::string replace_all(T_t text, T_s search, T_r replace) {
        std::string text_str = AsString(text);
        std::string search_str = AsString(search);
        std::string replace_str = AsString(replace);

        size_t start_pos = 0;
        while ((start_pos = text_str.find(search_str, start_pos)) != std::string::npos) {
            text_str.replace(start_pos, search_str.length(), replace_str);
            start_pos += replace_str.length(); // Handles case where 'replace' is a substring of 'search'
        }

        return text_str;
    }

    template <typename T, typename J>
    EXPORT std::string join(std::vector<T> list, J join) {
        std::string res;

        int len = list.size();
        int i = 1;
        for (T x : list) {
            res += AsString(x) + (i == len ? "" : AsString(join));
            i++;
        }

        return res;
    }

    int parseInt(std::string str) {
        int temp = 0;
        for (int i = 0; i < str.length(); i++) {
            temp = temp * 10 + (str[i] - '0');
        }
        return temp;
    }


    struct Config {
        inline static std::ostream* output = &std::cout;
        inline static int level = Levels::ALL;
        inline static std::string system_name = "Logger";
    };

    void exitHandler(int sig) {
        // get exit code name from signal number
        std::string exitCode = "(UNKNOWN)";
        int mod = 0;

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
                mod = 2;
                break;
            case SIGTERM:
                exitCode = "SIGTERM";
                Logger::Log("Term signal received, exiting", Logger::Config::system_name);
                return;
                break;
            default: // This should never occur.
                exitCode = "?????";
        }

        try {
            Logger::Error("Exiting with signal " + std::to_string(sig) + " (" + exitCode + ")", Logger::Config::system_name, mod);
        } catch (...) {
            Logger::Error("Exiting with signal " + std::to_string(sig) + " (" + exitCode + ")", Logger::Config::system_name);
        }

        exit(sig);
    }

    void initLogger() {
    #ifdef LOGGER_VERBOSE
        Logger::Info("Logger initialized", Logger::Config::system_name);
    #endif

        // register signal handlers

        for (int x : {SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV, SIGTERM}) {
            signal(x, exitHandler);
        }
    }

    std::string prettyStacktrace(std::string t, int highlight_frame, std::string highlight_color) {

        // -- Highlight the most important frame and dim the others -- //
        for (int x : range(split(t,"\n").size())) {
            std::string c_color;
            if (x == highlight_frame) {
                c_color = highlight_color + BOLD;
            } else {
                c_color = FORE_GRAY;
            }

            std::string n = fill(std::to_string(x), 2, 32);

            t = replace_all(t, n + "# ", c_color + n + "# " + RESET);
        }

#ifndef BOOST_STACKTRACE_USE_BACKTRACE
        return t;
#endif

#ifdef BOOST_STACKTRACE_USE_BACKTRACE
        std::vector<std::string> t_list = split(t);

        // -- Insert a snippet of the most important frame's respective file right below it -- //
        int current_trace = 0;

        for (const std::string& stack : t_list) {
            if (current_trace == highlight_frame) {
                std::vector<std::string> file_and_line = split(split(stack, " at ")[1],":");
                std::string filename = file_and_line[0];
                int line = parseInt(file_and_line[1]);

                int min_line = line - 2;
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

                break;  //end the loop because the if statement should only be true once
            }
            current_trace++;
        }


        return join(t_list,"\n");

#endif
    }

    std::string fill(std::string str, int len = 2, char fill = 48) {
        if (str.length() < len)
            str.insert(str.front() == '-' ? 1 : 0, len - str.length(), fill);
        return str;
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

    // probably doesn't do what you expect so don't use it
    // abstracted from Logger functions
    std::string _indenter(std::string text, int indent) {
        std::vector<std::string> text_lst = split(std::move(text), "\n");

        std::string end;

        // adds first element and removes it since we dont want it to be indented
        end.append(text_lst[0]);
        text_lst.erase(text_lst.begin());

        for (const auto& line : text_lst) {
            std::string res;
            for (int i : range(indent)) {
                res+=" ";
            }

            end.append("\n").append(res).append(line);
        }

        return end;
    }

    template <typename T>
    void Info(T text, std::string name) {
        if (Config::level >= Levels::INFO) { return; }

        if (!name.empty()) {
            name = "[" + name + "] ";
        }

        std::string end = std::string("");

        auto time = fancyTime() + " ";

        end.append(FORE_GRAY);
        end.append(BOLD);
        end.append(time);
        end.append(name);
        end.append(RESET);

        int indent = (int)(time+name).length();
        end.append(_indenter(AsString(text), indent));

        *Config::output << end << std::endl;
    }

    template <typename T>
    void Log(T text, std::string name) {
        if (Config::level >= Levels::LOG) {return;}

        if (!name.empty()) {
            name = "[" + name + "] ";
        }

        std::string end = std::string("");

        auto time = fancyTime() + " ";

        end.append(FORE_GRAY);
        end.append(BOLD);
        end.append(time);
        end.append(name);
        end.append(RESET);

        int indent = (int)(time+name).length();
        end.append(_indenter(AsString(text), indent));

        *Config::output << end << std::endl;
    }

    template <typename T>
    void Warn(T text, std::string name) {
        if (Config::level >= Levels::WARN) {return;}

        if (!name.empty()) {
            name = "[" + name + "] ";
        }

        std::string end = std::string("");

        auto time = fancyTime() + " ";

        std::string prefix = "WARNING: ";

        end.append(FORE_YELLOW);
        end.append(BOLD);
        end.append(time);
        end.append(name + prefix);
        end.append(RESET);

        int indent = (int)(time+name+prefix).length();
        end.append(_indenter(AsString(text), indent));

        *Config::output << end << std::endl;
    }

    template <typename T>
    void Crit(T text, std::string name, int stack_mod) {
        if (Config::level >= Levels::CRIT) {return;}

        if (!name.empty()) {
            name = "[" + name + "] ";
        }

        std::string end = std::string("");

        auto time = fancyTime() + " ";

        std::string prefix = "CRITICAL: ";

        end.append(FORE_BRIGHT_MAGENTA);
        end.append(BOLD);
        end.append(time);
        end.append(name + prefix);
        end.append(RESET);

        int indent = (int)(time+name+prefix).length();
        end.append(_indenter(AsString(text), indent));

        end.append("\n");
        end.append(prettyStacktrace(to_string(boost::stacktrace::stacktrace()), 1 + stack_mod, FORE_BRIGHT_MAGENTA));

        *Config::output << end << std::endl;
    }

    template <typename T>
    void Error(T text, std::string name, int stack_mod) {
        if (Config::level >= Levels::ERROR) { return; }


        if (!name.empty()) {
            name = "[" + name + "] ";
        }

        std::string end = std::string("");

        auto time = fancyTime() + " ";

        std::string prefix = "ERROR: ";

        end.append(FORE_RED);
        end.append(BOLD);
        end.append(time);
        end.append(name + prefix);
        end.append(RESET);

        int indent = (int)(time+name+prefix).length();
        end.append(_indenter(AsString(text), indent));

        end.append("\n");
        end.append(prettyStacktrace(to_string(boost::stacktrace::stacktrace()), 1 + stack_mod, FORE_RED));

        *Config::output << end << std::endl;
        exit(1);
    }

    template <typename T>
    void LogAt(int level, T message, std::string name , int stack_mod) {
        std::string message_str = AsString(message);

        if (level == 5) Error(message_str, name, stack_mod+1);
        else if (level == 4) Crit(message_str, name, stack_mod+1);
        else if (level == 3) Warn(message_str, name);
        else if (level == 2) Log(message_str, name);
        else if (level == 1) Info(message_str, name);
    }

    template <typename T>
    bool Assert(bool condition, T text, int level, std::string name) {
        if (condition) return true;

        std::string text_str = AsString(text);

        LogAt(level, text_str, name, 1);

        return false;
    }

}

#endif //NEUTRONLOGGER_H
