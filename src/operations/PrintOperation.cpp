#include <iostream>

#include "operations/PrintOperation.hpp"
#include "App.hpp"

namespace susi {
    
    PrintOperation::PrintOperation(App& app)
        : Operation(app, "print", "prints all about a student", 1, "<fn>") {}
    
    void PrintOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }


        // TODO
    }

}