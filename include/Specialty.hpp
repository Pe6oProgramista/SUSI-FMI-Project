#pragma once

#include <string>
#include <vector>
#include <fstream>

namespace susi {
    class Specialty {
    private:
        std::string command_name;
        std::vector<unsigned short> groups_cnts;
        unsigned int max_failed_exams;

    public:
        Specialty() = default;
        Specialty(const std::string& command_name,
            const std::vector<unsigned short>& groups_cnts,
            const unsigned int& max_failed_exams);
        Specialty(const Specialty& s) = default;
        ~Specialty() = default;

        Specialty& operator= (const Specialty& s);

        std::string get_name() const;
        const std::string& get_command_name() const;
        unsigned short get_courses_cnt() const;
        const std::vector<unsigned short>& get_groups_cnts() const;
        const unsigned int& get_max_failed_exams() const;
        

        void read(std::ifstream& in);
        void write(std::ofstream& out) const;

        bool operator== (const Specialty& s) const;
    };

}