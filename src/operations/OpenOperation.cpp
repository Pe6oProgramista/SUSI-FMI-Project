#include <fstream>
#include <string>

#include "operations/OpenOperation.hpp"
#include "App.hpp"

namespace susi {
    
    OpenOperation::OpenOperation(App& app)
        : Operation(app, "open", "opens <file>", 1, "<file>") {}
    
    void OpenOperation::execute(const std::vector<std::string>& args) {
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        // create file if not exists
        std::ofstream create(args[0], std::ios::app);
        create.close();


        std::ifstream in(args[0]);
        if (in.fail()) {
            throw OperationException("ERROR: File can't be opened. Filename: " + args[0]);
        }

        app.set_app_filename(args[0]);
        app.read(in);
        app.set_status(true);
        std::cout << "Successfully opened " << args[0] << '\n';
    }

}