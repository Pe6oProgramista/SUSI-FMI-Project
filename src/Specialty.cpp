#include <iostream>
#include <fstream>

#include "Specialty.hpp"

namespace susi {

    Specialty::Specialty(const std::string& command_name,
        const std::vector<unsigned short>& groups_cnts,
        const unsigned int& max_failed_exams)
        : command_name(command_name),
            groups_cnts(groups_cnts),
            max_failed_exams(max_failed_exams) {}

    Specialty& Specialty::operator= (const Specialty& s) {
        command_name = s.command_name;
        groups_cnts = s.groups_cnts;
        max_failed_exams = s.max_failed_exams;
        return *this;
    }

    std::string Specialty::get_name() const {
        std::string name = command_name;

        if(name[0] >= 'a' && name[0] <= 'z') {
            name[0] -= 'a' - 'A';
        }

        for(std::size_t i = 0; i < name.size(); i++) {
            if(name[i] == '_') name[i] = ' ';
            if(name[i + 1] >= 'a' && name[i + 1] <= 'z') {
                name[i + 1] -= 'a' - 'A';
            }
        };

        return name;
    }

    const std::string& Specialty::get_command_name() const { return command_name; }

    unsigned short Specialty::get_courses_cnt() const { return groups_cnts.size(); }

    const std::vector<unsigned short>& Specialty::get_groups_cnts() const { return groups_cnts; }

    const unsigned int& Specialty::get_max_failed_exams() const { return max_failed_exams; }

    void Specialty::read(std::ifstream& in) {
        size_t size;
        char* tmp;

        // read size, command_name
        in.read((char*) &size, sizeof(size));
        tmp = new char[size + 1];
        in.read(tmp, size);
        tmp[size] = '\0';
        command_name = tmp;
        delete [] tmp;

        //read courses_cnt (groups_cnts count)
        size_t count;
        in.read((char*) &count, sizeof(count));

        for(size_t i = 0; i < count; i++) {
            // read groups_cnt
            unsigned short groups_cnt;
            in.read((char*) &groups_cnt, sizeof(groups_cnt));

            groups_cnts.push_back(groups_cnt);
        }

        // read max_failed_exams
        in.read((char*) &max_failed_exams, sizeof(max_failed_exams));
    }

    void Specialty::write(std::ofstream& out) const {
        size_t size;

        // write size, command_name
        size = command_name.size();
        out.write((const char*) &size, sizeof(size));
	    out.write(command_name.c_str(), size);

        // write courses_cnt (groups_cnts count)
        size = groups_cnts.size();
        out.write((char*) &size, sizeof(size));

        for(size_t i = 0; i < groups_cnts.size(); i++) {
            // write groups_cnt
            out.write((char*) &groups_cnts[i], sizeof(groups_cnts[i]));
        }

        // write max_failed_exams
        out.write((char*) &max_failed_exams, sizeof(max_failed_exams));
    }

    bool Specialty::operator== (const Specialty& s) const {
        return command_name == s.command_name &&
            std::equal(groups_cnts.begin(), groups_cnts.end(), s.groups_cnts.begin()) &&
            max_failed_exams == s.max_failed_exams;
    }
}