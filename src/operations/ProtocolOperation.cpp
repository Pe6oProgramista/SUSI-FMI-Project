#include <iostream>

#include "operations/ProtocolOperation.hpp"
#include "App.hpp"

namespace susi {
    
    ProtocolOperation::ProtocolOperation(App& app)
        : Operation(app, "protocol", "print protocol for all students for subject <course>", 1, "<course>") {}
    
    void ProtocolOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }


        // TODO
    }

}