#include <iostream>
#include <string>
#include <vector>

#include "../include/Specialty.hpp"
#include "../include/Subject.hpp"
#include "../include/Student.hpp"
#include "../include/App.hpp"

#include "../include/operations/OpenOperation.hpp"
#include "../include/operations/ExitOperation.hpp"

#include "../utility/utils.hpp"

int main() {
    susi::App app;
    app.add_operation(new susi::OpenOperation(app));

    std::string command;
    while (true) {
        try {
            std::cout << "> ";
            std::getline(std::cin, command);

            std::vector<std::string> args = susi::utils::split(command, ' ');
            susi::Operation* operation = app.find_operation(args[0]);

            args.erase(args.begin());
            operation->execute(args);

            if(operation->get_name() == "exit") { // dynamic_cast<susi::ExitOperation*>(operation)
                break;
            }

        } catch(std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    
    return 0;
}