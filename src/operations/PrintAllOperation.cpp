#include <iostream>

#include "operations/PrintAllOperation.hpp"
#include "App.hpp"

namespace susi {
    
    PrintAllOperation::PrintAllOperation(App& app)
        : Operation(app, "printall", "prints info about all students in <program> and course <year>", 2, "<program> <year>") {}
    
    void PrintAllOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }


        // TODO
    }

}