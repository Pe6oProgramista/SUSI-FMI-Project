#include <iostream>
#include <fstream>

#include "Subject.hpp"

#include "utility/utils.hpp"

namespace susi {

    Subject::Subject(const std::string& command_name)
        : command_name(command_name) {}

    Subject& Subject::operator= (const Subject& s) {
        command_name = s.command_name;
        return *this;
    }

    std::string Subject::get_name() const {
        std::string name = command_name;

        if(name[0] >= 'a' && name[0] <= 'z') {
            name[0] -= 'a' - 'A';
        }

        for(std::size_t i = 0; i < name.size(); i++) {
            if(name[i] == '_') {
                name[i] = ' ';
                if(name[i + 1] >= 'a' && name[i + 1] <= 'z') {
                    name[i + 1] -= 'a' - 'A';
                }
            }
        };

        return name;
    }

    const std::string& Subject::get_command_name() const { return command_name; }

    void Subject::read(std::ifstream& in) {
        size_t size;
        char* tmp;

        // read size, command_name
        in.read((char*) &size, sizeof(size));
        tmp = new char[size + 1];
        in.read(tmp, size);
        tmp[size] = '\0';
        command_name = tmp;
        delete [] tmp;
    }

    void Subject::write(std::ofstream& out) const {
        size_t size;
        
        // write size, command_name
        size = command_name.size();
        out.write((const char*) &size, sizeof(size));
	    out.write(command_name.c_str(), size);
    }

    bool Subject::operator== (const Subject& s) const {
        return command_name == s.command_name;
    }

}