#include <iostream>

#include "operations/CloseOperation.hpp"
#include "App.hpp"

namespace susi {
    
    CloseOperation::CloseOperation(App& app)
        : Operation(app, "close", "closes currently opened file", 0, "") {}
    
    void CloseOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        std::string app_filename = app.get_app_filename();

        app.close();
        std::cout << "Successfully closed " << app_filename << '\n';
    }

}