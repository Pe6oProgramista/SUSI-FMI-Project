#include <iostream>

#include "operations/AddSubjectToOperation.hpp"
#include "App.hpp"

namespace susi {
    
    AddSubjectToOperation::AddSubjectToOperation(App& app)
        : Operation(app, "add_subject_to", "add subject to specialty", 4, "<subject_name> <specialty_name> <type>(required, optional) <course>") {}
    
    void AddSubjectToOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        const App::SpecSubj& ss = app.add_spec_subj(args[1], args[0], args[2], atoi(args[3].c_str()));

        std::cout << "Successfully added subject " << ss.subject->get_name()
            << " to specialty " << ss.specialty->get_name() << '\n';
    }

}