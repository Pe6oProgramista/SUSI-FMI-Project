#include <iostream>
#include <string>
#include <vector>

#include "App.hpp"
#include "Specialty.hpp"
#include "Subject.hpp"
#include "Student.hpp"

#include "utility/utils.hpp"

// add_specialty informatics 3 4 6 5 4 3
// add_subject math
// add_subject linear_algebra
// add_subject_to linear_algebra informatics required 1
// add_subject_to math informatics optional 2
// add_subject_to math informatics required 1
// enroll 1 informatics 1 Pancho_Iliev
// enroll 2 informatics 1 Gosho
// advance 2
// enroll 564 informatics 3 Ivan

int main() {
    susi::App app;
    susi::utils::load_all_operations(app);

    std::string command;
    while (true) {
        try {
            std::cout << "> ";
            std::getline(std::cin, command);

            std::vector<std::string> args = susi::utils::split(command, ' ');
            if(args.size() == 0) continue;
            
            susi::Operation* operation = app.find_operation(args[0]);

            args.erase(args.begin());
            operation->execute(args);

            if(operation->get_name() == "exit") {
                break;
            }

        } catch(std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    
    return 0;
}