#pragma once

#include "Operation.hpp"

namespace susi {

    class SaveOperation : public Operation {
    public:
        SaveOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}