#include <iostream>
#include <string>
#include <vector>

#include "App.hpp"
#include "Specialty.hpp"
#include "Subject.hpp"
#include "Student.hpp"

#include "utility/utils.hpp"

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