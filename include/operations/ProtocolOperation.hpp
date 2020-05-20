#pragma once

#include "Operation.hpp"

namespace susi {

    class ProtocolOperation : public Operation {
    public:
        ProtocolOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}