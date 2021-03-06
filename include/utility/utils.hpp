#pragma once

#include <vector>
#include <string>

#include "Operation.hpp"
#include "App.hpp"

namespace susi {
    namespace utils {
        const double GRADES_EPS = 0.001; 

        std::vector<std::string> split(const std::string& s, char delimiter);

        std::vector<std::string> split(const std::string& s, std::string delimiter);
        
        std::string trim(std::string s);

        int countDigit(int n);

        void load_all_operations(App& app);
    }
}