#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Specialty.hpp"
#include "Subject.hpp"
#include "Student.hpp"
#include "Operation.hpp"

namespace susi {

    class App {
    public:
        struct SpecSubj {
            Specialty::Ptr specialty;
            Subject::Ptr subject;
            std::string type;

            SpecSubj() : specialty(Specialty::Ptr()), subject(Subject::Ptr()), type(std::string()) {}
        };
    private:

        std::vector<Specialty::Ptr> specialties;
        std::vector<Subject::Ptr> subjects;
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

    private:
        void add_spec_subj(SpecSubj& connection);
    
    public:
        App() = default;
        App(const App& app) = delete;
        ~App();

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

        const std::vector<Specialty::Ptr>& get_specialties() const;
        const std::vector<Subject::Ptr>& get_subjects() const;

        void add_specialty(Specialty::Ptr specialty);
        void add_subject(Subject::Ptr subject);
        void add_student(Student& student);
        void add_spec_subj(std::string spec_name, std::string subj_name, std::string type);
    
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