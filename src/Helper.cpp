//
// Created by aw1lt on 03/12/22.
//

#include <fstream>
#include "../include/Logger/Helper.h"

namespace Logger::Utils::Helper {
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

    std::vector<std::string> readLines(std::string file, int min, int max) {
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

    std::vector<int> range(unsigned int start, unsigned int end, int step) {
        std::vector<int> res = {};

        for(int x = start; x != end; x+=step) {
            res.push_back(x);
        }

        return res;
    }

    std::vector<int> range(unsigned int end) {
        return range(0, end, 1);
    }
    std::vector<std::string> split(std::string string, std::string delimiter) {
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

    int parseInt(std::string str) {
        int temp = 0;
        for (int i = 0; i < str.length(); i++) {
            temp = temp * 10 + (str[i] - '0');
        }
        return temp;
    }
}