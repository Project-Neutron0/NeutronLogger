//
// Created by awilt on 21/11/22.
//

#ifndef EXPORT
#define EXPORT /*NO EXPORT MACRO*/
#endif

#ifndef NEUTRONENGINE_HELPER_H
#define NEUTRONENGINE_HELPER_H

#include <string>
#include <iostream>
#include "vector"


namespace Logger::Utils::Helper {
    std::vector<std::string> readLines_gi(std::string file, std::vector<int> &index_of, int min = 0, int max = -1);
    std::vector<std::string> readLines(std::string file, int min = 0, int max = -1);
    std::vector<std::string> readLines(std::string file, int max = -1);
    std::string read(std::string file);

    EXPORT std::vector<int> range(unsigned int start, unsigned int end, int step = 1);
    EXPORT std::vector<int> range(unsigned int end);
    EXPORT std::vector<std::string> split(std::string string, std::string delimiter = "\n");

    template <typename T, typename J>
    EXPORT T join(std::vector<T> list, J join = " ") {
        T res;

        int len = list.size();
        int i = 1;
        for (T x : list) {
            res += x + (i == len ? "" : (std::string)join);
            i++;
        }

        return res;
    }

    int parseInt(std::string str);
}

#endif //NEUTRONENGINE_HELPER_H
