#pragma once

#include "Operation.hpp"

namespace susi {

    class AddSubjectToOperation : public Operation {
    public:
        AddSubjectToOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}