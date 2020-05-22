#pragma once

#include "Operation.hpp"

namespace susi {

    class PrintSpecialtiesOperation : public Operation {
    public:
        PrintSpecialtiesOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}