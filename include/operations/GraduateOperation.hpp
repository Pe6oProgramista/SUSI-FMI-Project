#pragma once

#include "Operation.hpp"

namespace susi {

    class GraduateOperation : public Operation {
    public:
        GraduateOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}