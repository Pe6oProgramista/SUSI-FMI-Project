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

        std::size_t fn = (std::size_t)atol(args[0].c_str());
        Student& s = app.find_student(fn);
        
        if(args[1] == "program") {
            s.change_specialty(args[2], app);
        } else if(args[1] == "group") {
            unsigned short group = atoi(args[2].c_str());
            s.change_group(group);
        } else if(args[1] == "year") {
            unsigned short course = atoi(args[2].c_str());
            s.change_course(course);
        } else {
            throw OperationException("ERROR: Invalid option. Choose one of: program, group, year");
        }

        std::cout << "Student " << s.get_name() << " successfully changed " << args[1] << '\n';
    }

}