#pragma once

#include <vector>
#include <string>

#include "../include/Operation.hpp"
#include "../include/App.hpp"

namespace susi {
    namespace utils {
        std::vector<std::string> split(const std::string& s, char delimiter);

        App load_app(std::string filename);

        std::vector<Operation*> generate_operations();
    }
}