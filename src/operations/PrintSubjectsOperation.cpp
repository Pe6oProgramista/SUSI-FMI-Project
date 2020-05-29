#include <iostream>
#include <iomanip>
#include <string>

#include "operations/PrintSubjectsOperation.hpp"

#include "App.hpp"
#include "utility/utils.hpp"

namespace susi {
    
    PrintSubjectsOperation::PrintSubjectsOperation(App& app)
        : Operation(app, "print_subjects", "prints all subjects", 0, "") {}
    
    void PrintSubjectsOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }
        
        std::cout << "Name\n\n";
        for(const utils::SmartPtr<Subject>& s : app.get_subjects()) {
            std::cout << s->get_name() << '\n';
        }
    }

}