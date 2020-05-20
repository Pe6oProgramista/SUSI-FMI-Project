#include <iostream>

#include "operations/EnrollOperation.hpp"
#include "App.hpp"

namespace susi {
    
    EnrollOperation::EnrollOperation(App& app)
        : Operation(app, "enroll", "enroll a student <name> in 1 course, specialty <program>, group <group> and faculty number <fn>", 4, "<fn> <program> <group> <name>") {}
    
    void EnrollOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }


        // TODO
    }

}