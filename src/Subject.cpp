#include <iostream>
#include <fstream>

#include "../include/Subject.hpp"

namespace susi {

    Subject::Subject(std::string name) : name(name) {}

    Subject Subject::operator= (const Subject& s) {
        name = s.name;
        return *this;
    }

    std::string Subject::get_name() const { return name; }



    void Subject::read(std::ifstream& in) {
        size_t size;
        char* tmp;

        // read size, name
        in.read((char*) &size, sizeof(size));
        tmp = new char[size + 1];
        in.read(tmp, size);
        tmp[size] = '\0';
        name = tmp;
        delete [] tmp;
    }

    void Subject::write(std::ofstream& out) const {
        size_t size;
        
        // write size, name
        size = name.size();
        out.write((const char*) &size, sizeof(size));
	    out.write(name.c_str(), size);
    }

}