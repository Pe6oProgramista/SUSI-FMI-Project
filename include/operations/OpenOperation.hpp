#pragma once

#include "Operation.hpp"

namespace susi {

    class OpenOperation : public Operation {
    public:
        OpenOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}