#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Specialty.hpp"
#include "Subject.hpp"
#include "Student.hpp"
#include "Operation.hpp"
#include "utility/SmrtPtr.hpp"

namespace susi {
    typedef utils::SmrtPtr<Specialty> SpecialtyPtr;
    typedef utils::SmrtPtr<Subject> SubjectPtr;

    class App {
    public:
        struct SpecSubj {
            SpecialtyPtr specialty;
            SubjectPtr subject;
            std::string type;
            unsigned short course;

            SpecSubj() : specialty(SpecialtyPtr()), subject(SubjectPtr()), type(std::string()), course(0) {}
        };
    private:

        std::vector<SpecialtyPtr> specialties;
        std::vector<SubjectPtr> subjects;
        std::vector<Student> students;

        const char types[2][10] = { "required", "optional" };
        std::vector<SpecSubj> spec_subjecs;

        std::vector<Operation*> operations;

        bool status = false;
        std::string app_filename;
        std::string specialties_filename;
        std::string subjects_filename;
        std::string students_filename;
        std::string spec_subj_filename;
    
    public:
        App() = default;
        App(const App& app) = delete;
        ~App();

        void close();

        bool get_status() const;
        void set_status(bool status);

        std::string get_app_filename() const;
        void set_app_filename(std::string filename);

        std::string get_specialties_fn() const;
        void set_specialties_fn(std::string filename);

        std::string get_subjects_fn() const;
        void set_subjects_fn(std::string filename);

        std::string get_students_fn() const;
        void set_students_fn(std::string filename);

        std::string get_spec_subj_fn() const;
        void set_spec_subj_fn(std::string filename);

        const std::vector<SpecialtyPtr>& get_specialties() const;
        const std::vector<SubjectPtr>& get_subjects() const;
        const std::vector<Student>& get_students() const;
        const std::vector<SpecSubj>& get_spec_subjs() const;

        void add_specialty(SpecialtyPtr specialty);
        void add_subject(SubjectPtr subject);
        void add_student(const std::string& name, const std::size_t& fn, const std::string& specialty_name, const unsigned short& group);
        SpecSubj add_spec_subj(const std::string& spec_name, const std::string& subj_name, const std::string& type, const unsigned short& course);

        Student& find_student(const std::size_t& fn);
    
        const std::vector<Operation*>& get_operations() const;
        void add_operation(Operation* operation);
        Operation* find_operation(std::string name);

        // read/write funcitons
        void read_specialties();
        void write_specialties() const;

        void read_subjects();
        void write_subjects() const;

        void read_students();
        void write_students() const;

        void read_spec_subj();
        void write_spec_subj() const;

        void read(std::ifstream& in);
        void write(std::ofstream& out) const;
    };

    class AppException: virtual public std::exception {
    protected:
        std::string error_message;
        
    public:
        AppException(const std::string& msg)
            : error_message(msg) {}

        virtual ~AppException() throw () {}
        
        virtual const char* what() const throw () { return error_message.c_str(); }
    };

}