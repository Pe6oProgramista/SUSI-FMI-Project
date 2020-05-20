#pragma once

#include <vector>
#include <string>

#include "../include/Operation.hpp"
#include "../include/App.hpp"

namespace susi {
    namespace utils {
        std::vector<std::string> split(const std::string& s, char delimiter);

        std::vector<std::string> split(const std::string& s, std::string delimiter);
        
        std::string trim(std::string s);

        std::vector<Operation*> generate_operations();
    }
}