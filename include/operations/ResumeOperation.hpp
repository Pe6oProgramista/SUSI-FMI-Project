#pragma once

#include "Operation.hpp"

namespace susi {

    class ResumeOperation : public Operation {
    public:
        ResumeOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}