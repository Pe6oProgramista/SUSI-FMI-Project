#include <iostream>
#include <fstream>

#include "../include/Student.hpp"

#include "../include/Specialty.hpp"
#include "../include/Subject.hpp"
#include "../include/App.hpp"

namespace susi {

    Student::Student(std::string name,
        std::size_t faculty_number,
        Specialty* s,
        unsigned short group)
        : name(name), faculty_number(faculty_number), specialty(s), group(group) {}
    
    Student Student::operator= (const Student& s) {
        name = s.name;
        faculty_number = s.faculty_number;
        specialty = s.specialty;
        group = s.group;

        return *this;
    }

    std::string Student::get_name() const { return name; }

    std::size_t Student::get_fn() const { return faculty_number; }

    Specialty::Ptr Student::get_specialty() const { return specialty; }

    unsigned short Student::get_group() const { return group; }
    
    unsigned short Student::get_course() const { return course; }

    std::string Student::get_status() const {
        if(status == enrolled) {
            return "enrolled";
        } else if(status == withdrawn) {
            return "withdrawn";
        } else if(status == graduated) {
            return "graduated";
        }

        throw StudentException("ERROR: Unknown status");
    }

    void Student::enroll() {
        status = enrolled;
    }

    void Student::withdraw() {
        status = withdrawn;
    }
    
    void Student::graduate() {
        status = graduated;
    }
    
    double Student::avg_grade() const {
        double grade = 0;
        for(size_t i = 0; i < grades.size(); i++) {
            grade += grades[i].value;
        }

        return grade / grades.size();
    }

    // TODO
    // figure out solution for app
    void Student::read(std::ifstream& in, App& app) {
        Student s;

        size_t size;
        char* tmp;

        // read size, name
        in.read((char*) &size, sizeof(size));
        tmp = new char[size + 1];
        in.read(tmp, size);
        tmp[size] = '\0';
        s.name = tmp;
        delete [] tmp;

        // read faculty_number
        in.read((char*) &s.faculty_number, sizeof(s.faculty_number));

        // read specialty(ptr)
        //      read size, specialty->name
        in.read((char*) &size, sizeof(size));
        tmp = new char[size + 1];
        in.read(tmp, size);
        tmp[size] = '\0';

        const std::vector<Specialty::Ptr>& specialties = app.get_specialties();
        for(size_t i = 0; i < specialties.size(); i++) {
            if(specialties[i]->get_name() == tmp) {
                s.specialty = specialties[i];
                break;
            }
        }
        delete [] tmp;

        if(s.specialty.is_null()) {
            throw StudentException("ERROR: Invalid specialty");
        }

        // read group
        in.read((char*) &s.group, sizeof(s.group));
        if(s.group > s.specialty->get_groups_cnt()) {
            throw StudentException("ERROR: Invalid group for this specialty");
        }

        // read course
        in.read((char*) &s.course, sizeof(s.course));
        
        // read status
        in.read((char*) &size, sizeof(size));
        tmp = new char[size + 1];
        in.read(tmp, size);
        tmp[size] = '\0';

        std::string stat(tmp);
        delete[] tmp;

        if(stat == "enrolled") {
            s.status = enrolled;
        } else if (stat == "withdrawn") {
            s.status = withdrawn;
        } else if (stat == "graduated") {
            s.status = graduated;
        } else {
            throw StudentException("ERROR: Invalid status");
        }

        // read grades count
        size_t count;
        in.read((char*) &count, sizeof(count));

        for(size_t i = 0; i < count; i++) {
            // read value
            Grade grade(0, Subject::Ptr());
            in.read((char*) &grade.value, sizeof(grade.value));

            if(grade.value < 2. || grade.value > 6.) {
                throw StudentException("ERROR: Invalid grade value");
            }

            // read size, subject->name
            in.read((char*) &size, sizeof(size));
            tmp = new char[size + 1];
            in.read(tmp, size);
            tmp[size] = '\0';
            
            const std::vector<Subject::Ptr>& subjects = app.get_subjects();
            for(size_t i = 0; i < subjects.size(); i++) {
                if(subjects[i]->get_name() == tmp) {
                    grade.subject = subjects[i];
                    break;
                }
            }
            delete [] tmp;

            if(grade.subject.is_null()) {
                throw StudentException("ERROR: Invalid subject");
            }

            s.grades.push_back(grade);
        }

        *this = s;
    }

    void Student::write(std::ofstream& out) const {

        size_t size;

        // write size, name
        size = name.size();
        out.write((char*) &size, sizeof(size));
        out.write(name.c_str(), size);

        // write faculty_number
        out.write((char*) &faculty_number, sizeof(faculty_number));

        // write specialty(ptr)
        //      write size, specialty->name
        size = specialty->get_name().size();
        out.write((char*) &size, sizeof(size));
        out.write(specialty->get_name().c_str(), size);

        // write group
        out.write((char*) &group, sizeof(group));

        // write course
        out.write((char*) &course, sizeof(course));
        
        // write status
        size = get_status().size();
        out.write((char*) &size, sizeof(size));
        out.write(get_status().c_str(), size);

        // write grades count
        size = grades.size();
        out.write((char*) &size, sizeof(size));

        for(size_t i = 0; i < grades.size(); i++) {
            // write value
            out.write((char*) &grades[i].value, sizeof(grades[i].value));

            // write size, subject->name
            size = grades[i].subject->get_name().size();
            out.write((char*) &size, sizeof(size));
            out.write(grades[i].subject->get_name().c_str(), size);
        }
    }
}