#pragma once

#include "Operation.hpp"

namespace susi {

    class AddSubjectOperation : public Operation {
    public:
        AddSubjectOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}