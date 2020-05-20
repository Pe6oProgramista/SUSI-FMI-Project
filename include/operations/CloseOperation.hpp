#pragma once

#include "Operation.hpp"

namespace susi {

    class CloseOperation : public Operation {
    public:
        CloseOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}