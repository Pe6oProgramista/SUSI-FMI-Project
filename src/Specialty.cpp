#include <iostream>
#include <fstream>

#include "../include/Specialty.hpp"

namespace susi {

    Specialty::Specialty(std::string name, std::string command_name, unsigned short groups_cnt)
        : name(name), command_name(command_name), groups_cnt(groups_cnt) {}

    Specialty Specialty::operator= (const Specialty& s) {
        name = s.name;
        command_name = s.command_name;
        groups_cnt = s.groups_cnt;
        return *this;
    }

    std::string Specialty::get_name() const { return name; }

    std::string Specialty::get_command_name() const { return command_name; }

    unsigned short Specialty::get_groups_cnt() const { return groups_cnt; }

    void Specialty::read(std::ifstream& in) {
        size_t size;
        char* tmp;

        // read size, name
        in.read((char*) &size, sizeof(size));
        tmp = new char[size + 1];
        in.read(tmp, size);
        tmp[size] = '\0';
        name = tmp;
        delete [] tmp;

        // read size, command_name
        in.read((char*) &size, sizeof(size));
        tmp = new char[size + 1];
        in.read(tmp, size);
        tmp[size] = '\0';
        command_name = tmp;
        delete [] tmp;

        //read groups_cnt
        in.read((char*) &groups_cnt, sizeof(groups_cnt));
    }

    void Specialty::write(std::ofstream& out) const {
        size_t size;
        
        // write size, name
        size = name.size();
        out.write((const char*) &size, sizeof(size));
	    out.write(name.c_str(), size);

        // write size, command_name
        size = command_name.size();
        out.write((const char*) &size, sizeof(size));
	    out.write(command_name.c_str(), size);

        // write groups_cnt
        out.write((const char*) &groups_cnt, sizeof(groups_cnt));
    }

}