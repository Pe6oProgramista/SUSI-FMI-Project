#pragma once

#include "Operation.hpp"

namespace susi {

    class EnrollInOperation : public Operation {
    public:
        EnrollInOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}