#include "../include/App.hpp"

#include "../include/Specialty.hpp"
#include "../include/Subject.hpp"
#include "../include/Student.hpp"
#include "../include/Operation.hpp"

namespace susi {

    App::~App() {
        for(Operation*& it : operations) {
            delete it;
        }
    }

    bool App::get_status() const { return status; }
    void App::set_status(bool status) { this->status = status; }

    std::string App::get_app_filename() const { return app_filename; }
    void App::set_app_filename(std::string filename) { app_filename = filename; }

    std::string App::get_specialties_fn() const { return specialties_filename; }
    void App::set_specialties_fn(std::string filename) { specialties_filename = filename; }

    std::string App::get_subjects_fn() const { return subjects_filename; }
    void App::set_subjects_fn(std::string filename) { subjects_filename = filename; }

    std::string App::get_students_fn() const { return students_filename; }
    void App::set_students_fn(std::string filename) { students_filename = filename; }

    std::string App::get_spec_subj_fn() const { return spec_subj_filename; }
    void App::set_spec_subj_fn(std::string filename) { spec_subj_filename = filename; }

    const std::vector<Specialty::Ptr>& App::get_specialties() const { return specialties; }

    const std::vector<Subject::Ptr>& App::get_subjects() const { return subjects; }

    void App::add_specialty(Specialty::Ptr specialty) {
        specialties.push_back(specialty);
    }

    void App::add_subject(Subject::Ptr subject) {
        subjects.push_back(subject);
    }

    void App::add_student(Student& student) {
        students.push_back(student);
    }

    void App::add_spec_subj(SpecSubj& connection) {
        spec_subjecs.push_back(connection);
    }

    void App::add_spec_subj(std::string spec_name, std::string subj_name, std::string type) {
        SpecSubj s;
        
        for(size_t i = 0; i < sizeof(types); i++) {
            if(type == types[i]) {
                break;
            } else if(i == (sizeof(types) - 1)) {
                throw AppException("ERROR: Invalid type");
            }
        }
        s.type = type;

        for(size_t i = 0; i < specialties.size(); i++) {
            if (specialties[i]->get_name() == spec_name) {
                s.specialty = specialties[i];
                break;
            }
        }
        if(s.specialty.is_null()) {
            throw AppException("ERROR: Can't find such specialty");
        }
    
        for(size_t i = 0; i < subjects.size(); i++) {
            if (subjects[i]->get_name() == subj_name) {
                s.subject = subjects[i];
                break;
            }
        }
        if(s.subject.is_null()) {
            throw AppException("ERROR: Can't find such subject");
        }

        add_spec_subj(s);
    }

    const std::vector<Operation*>& App::get_operations() const { return operations; }

    void App::add_operation(Operation* operation) {
        operations.push_back(operation);
    }

    Operation* App::find_operation(std::string name) {
        for (std::vector<Operation*>::iterator it = operations.begin(); it != operations.end(); ++it) {
			if ((*it)->get_name() == name) {
				return *it;
			}
		}
		throw OperationException("ERROR: Unknown operation");
    }

    // read/write funcitons
    void App::read_specialties() {
        std::ofstream create(specialties_filename, std::ios::binary | std::ios::app);
        create.close();

        std::ifstream in(specialties_filename, std::ios::binary);
        if (in.fail()) {
            throw AppException("ERROR: File can't be opened. Filename: " + specialties_filename);
        }

        size_t size = 0;
        in.read((char*) &size, sizeof(size));

        for(size_t i = 0; i < size; i++) {
            Specialty* s = new Specialty();
            s->read(in);
            specialties.push_back(s);
        }
    }
    
    void App::write_specialties() const {
        std::ofstream out(specialties_filename, std::ios::binary | std::ios::trunc);
        if (out.fail()) {
            throw AppException("ERROR: File can't be opened. Filename: " + specialties_filename);
        }

        size_t size = specialties.size();
        out.write((char*) &size, sizeof(size));
        for (size_t i = 0; i < size; i++) {
			specialties[i]->write(out);
		}
    }

    void App::read_subjects() {
        std::ofstream create(subjects_filename, std::ios::binary | std::ios::app);
        create.close();

        std::ifstream in(subjects_filename, std::ios::binary);
        if (in.fail()) {
            throw AppException("ERROR: File can't be opened. Filename: " + subjects_filename);
        }

        size_t size = 0;
        in.read((char*) &size, sizeof(size));

        for(size_t i = 0; i < size; i++) {
            Subject* s = new Subject();
            s->read(in);
            subjects.push_back(s);
        }
    }

    void App::write_subjects() const {
        std::ofstream out(subjects_filename, std::ios::binary | std::ios::trunc);
        if (out.fail()) {
            throw AppException("ERROR: File can't be opened. Filename: " + subjects_filename);
        }

        size_t size = subjects.size();
        out.write((char*) &size, sizeof(size));

        for (size_t i = 0; i < size; i++) {
			subjects[i]->write(out);
		}
    }

    void App::read_students() {
        std::ofstream create(students_filename, std::ios::binary | std::ios::app);
        create.close();

        std::ifstream in(students_filename, std::ios::binary);
        if (in.fail()) {
            throw AppException("ERROR: File can't be opened. Filename: " + students_filename);
        }

        size_t size = 0;
        in.read((char*) &size, sizeof(size));

        for(size_t i = 0; i < size; i++) {
            Student s;
            s.read(in, *this);
            students.push_back(s);
        }
    }

    void App::write_students() const {
        std::ofstream out(students_filename, std::ios::binary | std::ios::trunc);
        if (out.fail()) {
            throw AppException("ERROR: File can't be opened. Filename: " + students_filename);
        }

        size_t size = students.size();
        out.write((char*) &size, sizeof(size));

        for (size_t i = 0; i < size; i++) {
			students[i].write(out);
		}
    }

    void App::read_spec_subj() {
        std::ofstream create(spec_subj_filename, std::ios::binary | std::ios::app);
        create.close();

        std::ifstream in(spec_subj_filename, std::ios::binary);
        if (in.fail()) {
            throw AppException("ERROR: File can't be opened. Filename: " + spec_subj_filename);
        }

        size_t count = 0;
        in.read((char*) &count, sizeof(count));

        for(size_t i = 0; i < count; i++) {
            size_t size;
            char* spec_name;
            char* subj_name;
            char* type;

            // read specialty name
            in.read((char*) &size, sizeof(size));
            spec_name = new char[size + 1];
            in.read(spec_name, size);
            spec_name[size] = '\0';

            // read subject name
            in.read((char*) &size, sizeof(size));
            subj_name = new char[size + 1];
            in.read(subj_name, size);
            subj_name[size] = '\0';

            // read type
            in.read((char*) &size, sizeof(size));
            type = new char[size + 1];
            in.read(type, size);
            type[size] = '\0';

            // add readed SpecSubj
            try {
                add_spec_subj(spec_name, subj_name, type);
            } catch(std::exception& e) {
                delete[] spec_name;
                delete[] subj_name;
                delete[] type;
                throw e;
            }

            delete[] spec_name;
            delete[] subj_name;
            delete[] type;
        }
    }

    void App::write_spec_subj() const {
        std::ofstream out(spec_subj_filename, std::ios::binary | std::ios::trunc);
        if (out.fail()) {
            throw AppException("ERROR: File can't be opened. Filename: " + spec_subj_filename);
        }

        size_t count = spec_subjecs.size();
        out.write((char*) &count, sizeof(count));

        for(size_t i = 0; i < count; i++) {
            size_t size;
            std::string name;

            // write specialty name
            name = spec_subjecs[i].specialty->get_name();
            size = name.size();
            out.write((const char*) &size, sizeof(size));
            out.write(name.c_str(), size);

            // write subject name
            name = spec_subjecs[i].subject->get_name();
            size = name.size();
            out.write((const char*) &size, sizeof(size));
            out.write(name.c_str(), size);

            // write type
            name = spec_subjecs[i].type;
            size = name.size();
            out.write((const char*) &size, sizeof(size));
            out.write(name.c_str(), size);
        }
    }

    void App::read(std::ifstream& in) {
        if(!std::getline(in, specialties_filename)) specialties_filename = app_filename + "_specialties.bin";
        if(!std::getline(in, subjects_filename)) subjects_filename = app_filename + "_subjects.bin";
        if(!std::getline(in, students_filename)) students_filename = app_filename + "_students.bin";
        if(!std::getline(in, spec_subj_filename)) spec_subj_filename = app_filename + "_spec_subj.bin";
        
        // if app_file is bin
        {
            // size_t size;
            // char* filename;

            // // read size specialties_filename
            // in.read((char*) &size, sizeof(size));
            // filename = new char[size + 1];
            // in.read(filename, size);
            // filename[size] = '\0';
            // specialties_filename = filename;
            // delete [] filename;

            // // read size subjects_filename
            // in.read((char*) &size, sizeof(size));
            // filename = new char[size + 1];
            // in.read(filename, size);
            // filename[size] = '\0';
            // subjects_filename = filename;
            // delete [] filename;

            // //read size students_filename
            // in.read((char*) &size, sizeof(size));
            // filename = new char[size + 1];
            // in.read(filename, size);
            // filename[size] = '\0';
            // students_filename = filename;
            // delete [] filename;

            // //read size spec_subj_filename
            // in.read((char*) &size, sizeof(size));
            // filename = new char[size + 1];
            // in.read(filename, size);
            // filename[size] = '\0';
            // spec_subj_filename = filename;
            // delete [] filename;
        }

        read_specialties();
        read_subjects();
        read_students();
        read_spec_subj();
    }

    // Write files
    void App::write(std::ofstream& out) const {
        out << specialties_filename << '\n'
            << subjects_filename << '\n'
            << students_filename << '\n'
            << spec_subj_filename << '\n';
        
        // if app_file is bin
        {
            // size_t size;
            
            // // write size specialties_filename
            // size = specialties_filename.size();
            // out.write((const char*) &size, sizeof(size));
            // out.write(specialties_filename.c_str(), size);

            // // write size subjects_filename
            // size = subjects_filename.size();
            // out.write((const char*) &size, sizeof(size));
            // out.write(subjects_filename.c_str(), size);

            // // write size students_filename
            // size = students_filename.size();
            // out.write((const char*) &size, sizeof(size));
            // out.write(students_filename.c_str(), size);

            // // write size spec_subj_filename
            // size = spec_subj_filename.size();
            // out.write((const char*) &size, sizeof(size));
            // out.write(spec_subj_filename.c_str(), size);
        }

        write_specialties();
        write_subjects();
        write_students();
        write_spec_subj();
    }

}