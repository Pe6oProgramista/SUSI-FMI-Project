#pragma once

#include "Operation.hpp"

namespace susi {

    class ChangeOperation : public Operation {
    public:
        ChangeOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}