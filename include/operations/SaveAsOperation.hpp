#pragma once

#include "Operation.hpp"

namespace susi {

    class SaveAsOperation : public Operation {
    public:
        SaveAsOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}