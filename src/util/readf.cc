#include "../../include/xutils.hpp"

std::string xsef::readf(const std::string& path) {
    std::ifstream file(path);
    std::string content;

    if(file.is_open()) {
        std::stringstream ss;
        ss << file.rdbuf();
        content = ss.str();
        file.close();
    }

    return content;
}