#include <iostream>

#include "operations/GraduateOperation.hpp"
#include "App.hpp"

namespace susi {
    
    GraduateOperation::GraduateOperation(App& app)
        : Operation(app, "graduate", "a student garduates", 1, "<fn>") {}
    
    void GraduateOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        std::size_t fn = (std::size_t)atol(args[0].c_str());
        Student& s = app.find_student(fn);
        s.graduate();

        std::cout << "Student " << s.get_name() << " successfully graduated\n";
    }

}