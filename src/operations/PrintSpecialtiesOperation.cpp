#include <iostream>
#include <iomanip>
#include <string>

#include "operations/PrintSpecialtiesOperation.hpp"

#include "App.hpp"
#include "utility/utils.hpp"

namespace susi {
    
    PrintSpecialtiesOperation::PrintSpecialtiesOperation(App& app)
        : Operation(app, "print_specialties", "prints all specialties", 0, "") {}
    
    void PrintSpecialtiesOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        const std::vector<utils::SmartPtr<Specialty>>& specialties = app.get_specialties();
        
        std::size_t name_size = sizeof("Name");
        int courses_size = sizeof("Courses");
        int groups_size = sizeof("Groups");
        int failed_exams_size = sizeof("Failed Exams");
        
        std::vector<std::string> groups_strs;

        for(const utils::SmartPtr<Specialty>& s : specialties) {
            if(name_size < s->get_name().size()) {
                name_size = s->get_name().size();
            }

            const std::vector<unsigned short>& groups = s->get_groups_cnts();
            int size = utils::countDigit(groups.size());
            if(courses_size < size) {
                courses_size = size;
            }

            std::string groups_str;
            for(const unsigned short& g : groups) {
                groups_str += std::to_string(g) + " ";
            }
            groups_strs.push_back(groups_str);

            size = groups_str.size() - 1; // -1 cause of last space
            if(groups_size < size) {
                groups_size = size;
            }

            size = utils::countDigit(s->get_max_failed_exams());
            if(failed_exams_size < size) {
                failed_exams_size = size;
            }
        }

        std::cout << std::left << std::setw(name_size)
            << "Name" << "  "
            << std::left << std::setw(courses_size)
            << "Courses" << "  "
            << std::left << std::setw(groups_size)
            << "Groups" << "  "
            << std::left << std::setw(failed_exams_size)
            << "Failed Exams" << "\n\n";

        for(std::size_t i = 0; i < specialties.size(); i++) {
            std::cout << std::left << std::setw(name_size)
                << specialties[i]->get_name() << "  "
                << std::left << std::setw(courses_size)
                << specialties[i]->get_courses_cnt() << "  "
                << std::left << std::setw(groups_size)
                << groups_strs[i] << " "
                << std::left << std::setw(failed_exams_size)
                << specialties[i]->get_max_failed_exams() << "\n";
        }
    }

}