#pragma once

#include "Operation.hpp"

namespace susi {

    class AddSpecialtyOperation : public Operation {
    public:
        AddSpecialtyOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}