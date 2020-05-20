#include <iostream>

#include "operations/ResumeOperation.hpp"
#include "App.hpp"

namespace susi {
    
    ResumeOperation::ResumeOperation(App& app)
        : Operation(app, "resume", "resume an interrupted student", 1, "<fn>") {}
    
    void ResumeOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }


        // TODO
    }

}