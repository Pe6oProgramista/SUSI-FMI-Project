#include <sstream>
#include <string>
#include <vector>

#include "utility/utils.hpp"

#include "App.hpp"
#include "Operation.hpp"

#include "operations/OpenOperation.hpp"
#include "operations/CloseOperation.hpp"
#include "operations/SaveOperation.hpp"
#include "operations/SaveAsOperation.hpp"
#include "operations/HelpOperation.hpp"
#include "operations/ExitOperation.hpp"

#include "operations/AddSpecialtyOperation.hpp"
#include "operations/AddSubjectOperation.hpp"
#include "operations/AddSubjectToOperation.hpp"
#include "operations/PrintSpecialtiesOperation.hpp"
#include "operations/PrintSubjectsOperation.hpp"

#include "operations/EnrollOperation.hpp"
#include "operations/AdvanceOperation.hpp"
#include "operations/ChangeOperation.hpp"
#include "operations/GraduateOperation.hpp"
#include "operations/InterruptOperation.hpp"
#include "operations/ResumeOperation.hpp"
#include "operations/PrintOperation.hpp"
#include "operations/PrintAllOperation.hpp"
#include "operations/EnrollInOperation.hpp"
#include "operations/AddGradeOperation.hpp"
#include "operations/ProtocolOperation.hpp"
#include "operations/ReportOperation.hpp"

namespace susi {
    namespace utils {

        std::vector<std::string> split(const std::string& s, char delimiter) {
            std::vector<std::string> tokens;
            std::string token;
            std::istringstream tokenStream(s);
            while (std::getline(tokenStream, token, delimiter)) {
                token = trim(token);
                if(token == "") continue;
                tokens.push_back(token);
            }
            return tokens;
        }

        std::vector<std::string> split(const std::string& s, std::string delimiter) {
            std::vector<std::string> tokens;
            char token;
            std::string curr_str;
            std::istringstream tokenStream(s);
            while (tokenStream.get(token)) {
                if(delimiter.find(token)) {
                    curr_str = trim(curr_str);
                    if(curr_str == "") continue;
                    tokens.push_back(curr_str);
                    curr_str.clear();
                } else {
                    curr_str.push_back(token);
                }
            }

            return tokens;
        }

        std::string trim(std::string s) {
            std::size_t startpos = s.find_first_not_of(" \t");
            std::size_t endpos = s.find_last_not_of(" \t");

            if(startpos == std::string::npos || endpos == std::string::npos) {
                return "";
            }

            s = s.substr(startpos, endpos - startpos + 1);

            return s;
        }

        char toUpperCase(char& c) {
            c &= ~('a' - 'A');
            return c;
        }

        char toLowerCase(char& c) {
            c |= ('a' - 'A');
            return c;
        }

        int countDigit(int n) { 
            int count = 0; 
            while (n != 0) { 
                n = n / 10; 
                ++count; 
            } 
            return count; 
        } 

        void load_all_operations(App& app) {
            // default operations
            app.add_operation(new susi::OpenOperation(app));
            app.add_operation(new susi::CloseOperation(app));
            app.add_operation(new susi::SaveOperation(app));
            app.add_operation(new susi::SaveAsOperation(app));
            app.add_operation(new susi::HelpOperation(app));
            app.add_operation(new susi::ExitOperation(app));

            // additional operations
            app.add_operation(new susi::AddSpecialtyOperation(app));
            app.add_operation(new susi::AddSubjectOperation(app));
            app.add_operation(new susi::AddSubjectToOperation(app));
            app.add_operation(new susi::PrintSpecialtiesOperation(app));
            app.add_operation(new susi::PrintSubjectsOperation(app));

            app.add_operation(new susi::EnrollOperation(app));
            app.add_operation(new susi::AdvanceOperation(app));
            app.add_operation(new susi::ChangeOperation(app));
            app.add_operation(new susi::GraduateOperation(app));
            app.add_operation(new susi::InterruptOperation(app));
            app.add_operation(new susi::ResumeOperation(app));
            app.add_operation(new susi::PrintOperation(app));
            app.add_operation(new susi::PrintAllOperation(app));
            app.add_operation(new susi::EnrollInOperation(app));
            app.add_operation(new susi::AddGradeOperation(app));
            app.add_operation(new susi::ProtocolOperation(app));
            app.add_operation(new susi::ReportOperation(app));
        }
    }
}