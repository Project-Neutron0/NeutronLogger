//
// Created by aw1lt on 08/12/22.
//

#include <fstream>
#include <utility>
#include "../include/Logger/Files.h"

namespace Neutron::Utils::Files {
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

}