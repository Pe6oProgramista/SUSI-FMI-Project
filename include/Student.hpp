#pragma once

#include <string>
#include <vector>

#include "Specialty.hpp"
#include "Subject.hpp"
#include "utility/SmrtPtr.hpp"


namespace susi {
    typedef utils::SmrtPtr<Specialty> SpecialtyPtr;
    typedef utils::SmrtPtr<Subject> SubjectPtr;
    
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
            SubjectPtr subject;
        
            Grade() : value(0), subject(SubjectPtr()) {}
            Grade(double val, SubjectPtr subj) : value(val), subject(subj) {}
        };

    private:
        std::string name;
        std::size_t faculty_number;
        SpecialtyPtr specialty;
        unsigned short course;
        unsigned short group;
        Status status;
        
        std::vector<Grade> grades;

    public:
        Student() = default;
        Student(std::string name,
            std::size_t faculty_number,
            SpecialtyPtr s,
            unsigned short group);
        Student(const Student& s) = default;
        ~Student() = default;
        
        Student& operator= (const Student& s);

        const std::string& get_name() const;
        const std::size_t& get_fn() const;
        const SpecialtyPtr& get_specialty() const;
        const unsigned short& get_course() const;
        const unsigned short& get_group() const;
        std::string get_status() const;

        void change_specialty(const std::string& specialty_name, App& app);
        void change_group(const unsigned short& group);
        void change_course(const unsigned short& course);

        void enroll_in(const std::string& subject_name, App& app);
        void add_grade(const double& value, const std::string& subject_name, App& app);

        void enroll();
        void withdraw();
        void graduate();
        void advance();
        double avg_grade() const;

        void read(std::ifstream& in, const App& app);
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