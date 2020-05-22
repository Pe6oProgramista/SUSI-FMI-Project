#include <iostream>
#include <cmath>
#include <string>

#include "operations/EnrollOperation.hpp"
#include "App.hpp"

namespace susi {
    
    EnrollOperation::EnrollOperation(App& app)
        : Operation(app,
            "enroll",
            "enroll a student <name> in <program> 1 course",
            4,
            "<fn> <program> <group> <name>") {}
    
    void EnrollOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }


        std::size_t fn = atol(args[0].c_str());
        unsigned short group = atoi(args[2].c_str());

        std::string name = args[3];
        for(std::size_t i = 0; i < name.size(); i++) {
            if(name[i] == '_') name[i] = ' ';
        }

        app.add_student(name, fn, args[1], group);
        std::cout << "Successfully enrolled student " << name << '\n';
    }

}