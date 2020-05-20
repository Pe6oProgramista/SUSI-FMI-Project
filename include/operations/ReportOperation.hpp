#pragma once

#include "Operation.hpp"

namespace susi {

    class ReportOperation : public Operation {
    public:
        ReportOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}