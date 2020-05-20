#pragma once

#include "Operation.hpp"

namespace susi {

    class HelpOperation : public Operation {
    public:
        HelpOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}