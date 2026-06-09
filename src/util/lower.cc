#include "../../include/xutils.hpp"

std::string xsef::lower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { 
        return static_cast<char>(std::tolower(c)); 
    });

    return str;
}