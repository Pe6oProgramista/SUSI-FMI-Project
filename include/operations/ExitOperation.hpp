#pragma once

#include "../Operation.hpp"

namespace susi {

    class ExitOperation : public Operation {
    public:
        ExitOperation(App& app);
        
        void execute(std::vector<std::string> args);
    };

}