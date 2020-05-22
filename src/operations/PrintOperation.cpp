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

        std::size_t fn = (std::size_t)atol(args[0].c_str());
        Student& s = app.find_student(fn);
        
        std::cout << "Fn" << "  "
            << "Name" << "  "
            << "Specialty" << "  "
            << "Course" << "  "
            << "Group" << "  "
            << "Status" << "\n\n";

        std::cout << s.get_fn() << "  "
            << s.get_name() << "  "
            << s.get_specialty()->get_name() << "  "
            << s.get_course() << "  "
            << s.get_group() << "  "
            << s.get_status() << '\n';
    }

}