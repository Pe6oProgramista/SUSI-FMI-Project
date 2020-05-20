#pragma once

#include "../Operation.hpp"

namespace susi {

    class OpenOperation : public Operation {
    public:
        OpenOperation(App& app);
        
        void execute(std::vector<std::string>& args);
    };

}