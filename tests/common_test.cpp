#include <iostream>
#include <string>
#include <vector>

#include "App.hpp"

#include "utility/utils.hpp"

const std::vector<std::string> commands = {
    "help",
    "open data/susi",
    "add_specialty informatics 3 4 6 5 4 3",
    "add_specialty informatics 3 4 4 3 2 1",
    "add_specialty comp_science 3 4 4 3 2 1",
    "add_subject math",
    "add_subject linear_algebra",
    "add_subject_to linear_algebra informatics required 1",
    "add_subject_to math informatics optional 2",
    "add_subject_to math informatics optional 1",
    "add_subject_to linear_algebra comp_science optional 1",
    "add_subject_to math comp_science required 4",
    "",
    "enroll 1 informatics 1 Pancho_Iliev",
    "enroll 2 informatics 1 Gosho",
    "advance 2",
    "enroll 5 comp_science 4 Petoko",
    "advance 5",
    "advance 5",
    "advance 5",
    "enroll 564 informatics 3 Ivan",
    "report 1",
    "save",
    "close",
    "print 1",
    "open data/susi",
    "report 1",
    "exit",
    "help"
};

int main() {
    susi::App app;
    susi::utils::load_all_operations(app);

    for(std::size_t i = 0; i < commands.size(); i++) {
        try {
            std::vector<std::string> args = susi::utils::split(commands[i], ' ');
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