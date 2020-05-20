#pragma once

#include "Operation.hpp"

namespace susi {

    class InterruptOperation : public Operation {
    public:
        InterruptOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}