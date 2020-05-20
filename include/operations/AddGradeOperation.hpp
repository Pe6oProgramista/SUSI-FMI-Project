#pragma once

#include "Operation.hpp"

namespace susi {

    class AddGradeOperation : public Operation {
    public:
        AddGradeOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}