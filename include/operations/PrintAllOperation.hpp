#pragma once

#include "Operation.hpp"

namespace susi {

    class PrintAllOperation : public Operation {
    public:
        PrintAllOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}