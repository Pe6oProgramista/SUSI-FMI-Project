#include <iostream>
#include <string>
#include <vector>

#include "Specialty.hpp"
#include "Subject.hpp"
#include "Student.hpp"
#include "App.hpp"

#include "operations/OpenOperation.hpp"
#include "operations/CloseOperation.hpp"
#include "operations/SaveOperation.hpp"
#include "operations/SaveAsOperation.hpp"
#include "operations/HelpOperation.hpp"
#include "operations/ExitOperation.hpp"

#include "utility/utils.hpp"

int main() {
    susi::App app;
    app.add_operation(new susi::OpenOperation(app));
    app.add_operation(new susi::CloseOperation(app));
    app.add_operation(new susi::SaveOperation(app));
    app.add_operation(new susi::SaveAsOperation(app));
    app.add_operation(new susi::HelpOperation(app));
    app.add_operation(new susi::ExitOperation(app));

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

            if(operation->get_name() == "exit") { // dynamic_cast<susi::ExitOperation*>(operation)
                break;
            }

        } catch(std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    
    return 0;
}