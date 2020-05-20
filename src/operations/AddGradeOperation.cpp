#include <iostream>

#include "operations/AddGradeOperation.hpp"
#include "App.hpp"

namespace susi {
    
    AddGradeOperation::AddGradeOperation(App& app)
        : Operation(app, "addgrade", "add grade for subject <course>", 3, "<fn> <course> <grade>") {}
    
    void AddGradeOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }


        // TODO
    }

}