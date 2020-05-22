#include <iostream>
#include <iomanip>
#include <cmath>

#include "operations/ReportOperation.hpp"
#include "App.hpp"
#include "utility/utils.hpp"

namespace susi {
    
    ReportOperation::ReportOperation(App& app)
        : Operation(app, "report", "academic transcript of student", 1, "<fn>") {}
    
    void ReportOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        std::size_t fn = (std::size_t)atol(args[0].c_str());
        Student& s = app.find_student(fn);
        
        std::cout << "Passed exams of " << s.get_name() << ":\n";
        int subj_size = sizeof("Subject");
        int grade_size = sizeof("Grade");

        for(const Student::Grade& g : s.get_grades()) {
            if(g.value - 3. > utils::GRADES_EPS && subj_size < (int)g.subject->get_name().size()) {
                subj_size = g.subject->get_name().size();
            }
        }

         std::cout << std::left << std::setw(subj_size)
            << "Subject" << "  "
            << std::left << std::setw(grade_size)
            << "Grade" << "\n";

        for(const Student::Grade& g : s.get_grades()) {
            if(g.value - 3. > utils::GRADES_EPS) {
                std::cout << std::left << std::setw(subj_size)
                << g.subject->get_name() << "  "
                << std::left << std::setw(grade_size)
                << g.value << "\n";
            }
        }

        std::cout << "\nFailed exams of " << s.get_name() << ":\n";
        subj_size = sizeof("Subject");
        grade_size = sizeof("Grade");

        for(const Student::Grade& g : s.get_grades()) {
            if(3. - g.value > utils::GRADES_EPS && subj_size < (int)g.subject->get_name().size()) {
                subj_size = g.subject->get_name().size();
            }
        }

         std::cout << std::left << std::setw(subj_size)
            << "Subject" << "  "
            << std::left << std::setw(grade_size)
            << "Grade" << "\n";

        for(const Student::Grade& g : s.get_grades()) {
            if(3. - g.value > utils::GRADES_EPS) {
                std::cout << std::left << std::setw(subj_size)
                << g.subject->get_name() << "  "
                << std::left << std::setw(grade_size)
                << g.value << "\n";
            }
        }

        std::cout << "\nAverage grade: " << s.avg_grade() << "\n";
    }

}