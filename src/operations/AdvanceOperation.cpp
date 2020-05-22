#include <iostream>

#include "operations/AdvanceOperation.hpp"
#include "App.hpp"

namespace susi {
    
    AdvanceOperation::AdvanceOperation(App& app)
        : Operation(app, "advance", "advance student to next course", 1, "<fn>") {}
    
    void AdvanceOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        std::size_t fn = (std::size_t)atol(args[0].c_str());
        Student& s = app.find_student(fn);
        s.advance();

        std::cout << "Student " << s.get_name() << " successfully advanced\n";
    }

}