#include <iostream>

#include "operations/ReportOperation.hpp"
#include "App.hpp"

namespace susi {
    
    ReportOperation::ReportOperation(App& app)
        : Operation(app, "report", "academic transcript of student", 1, "<fn>") {}
    
    void ReportOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }


        // TODO
    }

}