#include <iostream>

#include "operations/ChangeOperation.hpp"
#include "App.hpp"

namespace susi {
    
    ChangeOperation::ChangeOperation(App& app)
        : Operation(app, "change", "change <option> of student to <value>", 3, "<fn> <option> <value>") {}
    
    void ChangeOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }


        // TODO
    }

}