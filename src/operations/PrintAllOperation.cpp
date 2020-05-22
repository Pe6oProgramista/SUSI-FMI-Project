#include <iostream>
#include <iomanip>

#include "operations/PrintAllOperation.hpp"

#include "App.hpp"
#include "utility/utils.hpp"

namespace susi {
    
    PrintAllOperation::PrintAllOperation(App& app)
        : Operation(app, "printall", "prints info about all students in <program> and course <year>", 2, "<program> <year>") {}
    
    void PrintAllOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        unsigned short course = atoi(args[1].c_str());

        const std::vector<Student>& students = app.get_students();
        
        int fn_size = sizeof("Fn");
        std::size_t name_size = sizeof("Name");
        std::size_t spec_name_size = sizeof("Specialty");
        int course_size = sizeof("Course");
        int group_size = sizeof("Group");
        std::size_t status_size = sizeof("Status");
        
        for(const Student& s : students) {
            if(s.get_specialty()->get_command_name() == args[0] && s.get_course() == course) {
                int size = utils::countDigit(s.get_fn());
                if(fn_size < size) {
                    fn_size = size;
                }

                if(name_size < s.get_name().size()) {
                    name_size = s.get_name().size();
                }

                if(spec_name_size < s.get_specialty()->get_name().size()) {
                    spec_name_size = s.get_specialty()->get_name().size();
                }

                size = utils::countDigit(s.get_course());
                if(course_size < size) {
                    course_size = size;
                }

                size = utils::countDigit(s.get_group());
                if(group_size < size) {
                    group_size = size;
                }

                if(status_size < s.get_status().size()) {
                    status_size = s.get_status().size();
                }
            }
        }

        std::cout << std::left << std::setw(fn_size)
            << "Fn" << "  "
            << std::left << std::setw(name_size)
            << "Name" << "  "
            << std::left << std::setw(spec_name_size)
            << "Specialty" << "  "
            << std::left << std::setw(course_size)
            << "Course" << "  "
            << std::left << std::setw(group_size)
            << "Group" << "  "
            << std::left << std::setw(status_size)
            << "Status" << "\n\n";

        for(const Student& s : students) {
            if(s.get_specialty()->get_command_name() == args[0] && s.get_course() == course) {
                std::cout << std::left << std::setw(fn_size)
                    << s.get_fn() << "  "
                    << std::left << std::setw(name_size)
                    << s.get_name() << "  "
                    << std::left << std::setw(spec_name_size)
                    << s.get_specialty()->get_name() << "  "
                    << std::left << std::setw(course_size)
                    << s.get_course() << "  "
                    << std::left << std::setw(group_size)
                    << s.get_group() << "  "
                    << std::left << std::setw(status_size)
                    << s.get_status() << '\n';
            }
        }
    }

}