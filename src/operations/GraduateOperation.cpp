#include <iostream>

#include "operations/GraduateOperation.hpp"
#include "App.hpp"

namespace susi {
    
    GraduateOperation::GraduateOperation(App& app)
        : Operation(app, "graduate", "a student garduates", 1, "<fn>") {}
    
    void GraduateOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }


        // TODO
    }

}