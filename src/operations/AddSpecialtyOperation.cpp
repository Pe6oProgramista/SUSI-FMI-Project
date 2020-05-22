#include <iostream>
#include <cmath>

#include "operations/AddSpecialtyOperation.hpp"
#include "App.hpp"

namespace susi {
    
    // add name with "_" instead " "
    AddSpecialtyOperation::AddSpecialtyOperation(App& app)
        : Operation(app, "add_specialty", "add new specialty", 3, "<command_name> <max_failed_exams> <courses> [groups_cnt ]") {}
    
    void AddSpecialtyOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(args.size() < get_args_count()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        unsigned short courses = atoi(args[2].c_str());
        if(courses == 0) {
            throw OperationException("ERROR: Specialty must have at least 1 course");
        }
        if(args.size() - get_args_count() != courses) {
            throw OperationException("ERROR: Different count of groups_cnt");
        }

        unsigned int max_failed_exams = atoi(args[1].c_str());

        std::vector<unsigned short> groups_cnts;
        for(unsigned short i = 0; i < courses; i++) {
            groups_cnts.push_back(atoi(args[i + get_args_count()].c_str()));
        }

        SpecialtyPtr sp(new Specialty(args[0], groups_cnts, max_failed_exams));

        app.add_specialty(sp);

        std::cout << "Successfully added specialty " << sp->get_name() << '\n';
    }

}