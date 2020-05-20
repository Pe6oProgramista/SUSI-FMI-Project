#pragma once

#include "Operation.hpp"

namespace susi {

    class AdvanceOperation : public Operation {
    public:
        AdvanceOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}