#pragma once

#include "Operation.hpp"

namespace susi {

    class EnrollOperation : public Operation {
    public:
        EnrollOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}