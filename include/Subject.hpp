#pragma once

#include <string>

namespace susi {

    class Subject {
    private:
        std::string command_name;

    public:
        Subject() = default;
        Subject(const std::string& command_name);
        Subject(const Subject& s) = default;
        ~Subject() = default;
        
        Subject& operator= (const Subject& s);

        std::string get_name() const;
        const std::string& get_command_name() const;

        void read(std::ifstream& in);
        void write(std::ofstream& out) const;

        bool operator== (const Subject& s) const;
    };

}