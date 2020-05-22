#include <iostream>

#include "operations/EnrollInOperation.hpp"
#include "App.hpp"

namespace susi {
    
    EnrollInOperation::EnrollInOperation(App& app)
        : Operation(app, "enrollin", "enroll student in <course>", 2, "<fn> <course>") {}
    
    void EnrollInOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }


        std::size_t fn = (std::size_t)atol(args[0].c_str());
        Student& s = app.find_student(fn);

        std::string subject_name = args[1];
        for(std::size_t i = 0; i < subject_name.size(); i++) {
            if(subject_name[i] == '_') subject_name[i] = ' ';
        }

        s.enroll_in(subject_name, app);

        std::cout << "The student successfully enrolled for subject " << subject_name << '\n';
    }

}