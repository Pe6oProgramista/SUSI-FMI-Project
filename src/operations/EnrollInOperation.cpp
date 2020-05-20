#include <iostream>

#include "operations/EnrollInOperation.hpp"
#include "App.hpp"

namespace susi {
    
    EnrollInOperation::EnrollInOperation(App& app)
        : Operation(app, "enrollin", "enroll student in <course>", 2, "<fn> <course>") {}
    
    void EnrollInOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }


        // TODO
    }

}