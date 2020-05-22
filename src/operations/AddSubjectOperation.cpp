#include <iostream>

#include "operations/AddSubjectOperation.hpp"
#include "App.hpp"

namespace susi {
    
    // add name with "_" instead " "
    AddSubjectOperation::AddSubjectOperation(App& app)
        : Operation(app, "add_subject", "add new subject", 1, "<command_name>") {}
    
    void AddSubjectOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        SubjectPtr sp(new Subject(args[0]));
        app.add_subject(sp);

        std::cout << "Successfully added subject " << sp->get_name() << '\n';
    }

}