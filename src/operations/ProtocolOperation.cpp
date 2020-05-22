#include <iostream>
#include <iomanip>

#include "operations/ProtocolOperation.hpp"
#include "App.hpp"

#include "utility/utils.hpp"

namespace susi {
    
    ProtocolOperation::ProtocolOperation(App& app)
        : Operation(app, "protocol", "print protocol for all students for subject <course>", 1, "<course>") {}
    
    void ProtocolOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        std::string subj_name = args[0];
        
        int fn_size = sizeof("Fn");
        std::size_t name_size = sizeof("Name");
        std::size_t spec_name_size = sizeof("Specialty");
        int course_size = sizeof("Course");
        int group_size = sizeof("Group");
        std::size_t status_size = sizeof("Status");

        std::vector<Student> students;
        const std::vector<Student>& all_students = app.get_students();
        for(const Student& s : all_students) {
            for(const Student::Grade& g : s.get_grades()) {
                if(g.subject->get_command_name() == subj_name) {
                    // change offsets for output
                    {
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

                    bool added = false;
                    for(std::vector<Student>::iterator it = students.begin(); it != students.end() - 1; it++) {
                        if(it->get_specialty()->get_command_name() == s.get_specialty()->get_command_name()) {
                            if(it->get_course() == s.get_course()) {
                                if(it->get_fn() > s.get_fn()) {
                                    students.insert(it, s);
                                    added = true;
                                    break;
                                }
                            }
                            if((it + 1)->get_course() > s.get_course()) {
                                students.insert(it + 1, s);
                                added = true;
                                break;
                            }
                        }
                        if((it + 1)->get_specialty()->get_command_name() > s.get_specialty()->get_command_name()) {
                            students.insert(it + 1, s);
                            added = true;
                            break;
                        }
                    }
                    if(!added) {
                        students.push_back(s);
                    }
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

        std::string spec_name;
        unsigned short course = 0;
        for(const Student& s : students) {
            if(s.get_specialty()->get_name() != spec_name ||
                s.get_course() != course) {
                    spec_name = s.get_specialty()->get_name();
                    course = s.get_course();

                    std::cout << "Protocol for " << spec_name << " " << course << " course:\n";
                }
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