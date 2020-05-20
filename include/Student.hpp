#pragma once

#include <string>
#include <vector>

// #include "App.hpp"
#include "Specialty.hpp"
#include "Subject.hpp"

namespace susi {
    class App;

    class Student {
    private:
        enum Status {
            enrolled,
            withdrawn,
            graduated
        };

        struct Grade {
            double value;
            Subject::Ptr subject;
        
            Grade() : value(0), subject(Subject::Ptr()) {}
            Grade(double val, Subject::Ptr subj) : value(val), subject(subj) {}
        };

    private:
        std::string name;
        std::size_t faculty_number;
        Specialty::Ptr specialty;
        unsigned short group;

        unsigned short course;
        Status status;
        
        std::vector<Grade> grades;

    public:
        Student() = default;
        Student(std::string name,
            std::size_t faculty_number,
            Specialty* s,
            unsigned short group);
        Student(const Student& s) = default;
        ~Student() = default;
        
        Student operator= (const Student& s);

        std::string get_name() const;
        std::size_t get_fn() const;
        Specialty::Ptr get_specialty() const;
        unsigned short get_group() const;
        
        unsigned short get_course() const;
        std::string get_status() const;

        void enroll();
        void withdraw();
        void graduate();
        double avg_grade() const;

        void read(std::ifstream& in, App& app);
        void write(std::ofstream& out) const;
    };

    class StudentException: virtual public std::exception {
    protected:
        std::string error_message;
        
    public:
        StudentException(const std::string& msg)
            : error_message(msg) {}

        virtual ~StudentException() throw () {}
        
        virtual const char* what() const throw () { return error_message.c_str(); }
    };

}