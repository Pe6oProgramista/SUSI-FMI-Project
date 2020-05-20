#include <sstream>
#include <string>
#include <vector>

#include "utils.hpp"

#include "../include/App.hpp"
#include "../include/Operation.hpp"
#include "../include/operations/OpenOperation.hpp"

namespace susi {
    namespace utils {
        std::vector<std::string> split(const std::string& s, char delimiter) {
            std::vector<std::string> tokens;
            std::string token;
            std::istringstream tokenStream(s);
            while (std::getline(tokenStream, token, delimiter)) {
                tokens.push_back(token);
            }
            return tokens;
        }

        // App load_app(std::string filename) {

        // }

        std::vector<Operation*> generate_operations(App& app) {
            std::vector<Operation*> ops;

            ops.push_back(new OpenOperation(app));
            // ops.push_back(new CloseOperation(app));
            // ops.push_back(new SaveOperation(app));
            // ops.push_back(new SaveAsOperation(app));
            // ops.push_back(new HelpOperation(app));
            // ops.push_back(new ExitOperation(app));

            return ops;
        }
    }
}