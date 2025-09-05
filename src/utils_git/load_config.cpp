
#include "load_config.h"
#include <fstream>
#include <string>
#include <vector>
namespace utils_git {

std::vector<std::string> loadRepoConfig(const std::string &filePath){
    std::ifstream file(filePath);
    std::string line;
    std::vector<std::string> result;

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open the endpoint config");
    }

    while (std::getline(file, line)){
        if (!line.empty()) {
            result.push_back(line);
        }
    }

    return result;
}

}
