#pragma once

#include "Operation.hpp"

namespace susi {

    class ExitOperation : public Operation {
    public:
        ExitOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}