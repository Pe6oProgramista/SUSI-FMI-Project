#include <iostream>

#include "operations/InterruptOperation.hpp"
#include "App.hpp"

namespace susi {
    
    InterruptOperation::InterruptOperation(App& app)
        : Operation(app, "interrupt", "a student interrupts", 1, "<fn>") {}
    
    void InterruptOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }


        // TODO
    }

}