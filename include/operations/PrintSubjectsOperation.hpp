#pragma once

#include "Operation.hpp"

namespace susi {

    class PrintSubjectsOperation : public Operation {
    public:
        PrintSubjectsOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}