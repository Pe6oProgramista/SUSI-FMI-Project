#include <iostream>
#include <fstream>

#include "Student.hpp"

#include "Specialty.hpp"
#include "Subject.hpp"
#include "App.hpp"
#include "utility/utils.hpp"

namespace susi {

    Student::Student(std::string name,
        std::size_t faculty_number,
        utils::SmartPtr<Specialty> s,
        unsigned short group)
        : name(name),
            faculty_number(faculty_number),
            specialty(s),
            course(1),
            group(group),
            status(enrolled) {}
    
    Student& Student::operator= (const Student& s) {
        name = s.name;
        faculty_number = s.faculty_number;
        specialty = s.specialty;
        course = s.course;
        group = s.group;
        status = s.status;
        grades = s.grades;

        return *this;
    }

    const std::string& Student::get_name() const { return name; }

    const std::size_t& Student::get_fn() const { return faculty_number; }

    const utils::SmartPtr<Specialty>& Student::get_specialty() const { return specialty; }

    const unsigned short& Student::get_course() const { return course; }
    
    const unsigned short& Student::get_group() const { return group; }

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

    const std::vector<Student::Grade>& Student::get_grades() const { return grades; }

    void Student::change_specialty(const std::string& specialty_name, App& app) {
        const std::vector<App::SpecSubj>& spec_subjs = app.get_spec_subjs();
        utils::SmartPtr<Specialty> sp;
        for(const App::SpecSubj& ss : spec_subjs) {
            if(ss.specialty->get_command_name() == specialty_name && ss.type == "required") {
                if(sp.is_null()) sp = ss.specialty;

                bool found = false;
                for(const Grade& g : grades) {
                    if(*g.subject == *ss.subject) {
                        found = true;
                        if(g.value < 3. - utils::GRADES_EPS) {
                            throw StudentException("The student can't change specialty due to unpassed exam in " + ss.subject->get_name());
                        }
                        break;
                    }
                }
                if(!found) {
                    throw StudentException("The student can't change specialty due to unpassed exam in " + ss.subject->get_name());
                }
            }
        }

        specialty = sp;
        
        if(course > sp->get_courses_cnt()) {
            graduate();
        }
        if(group > sp->get_groups_cnts()[course - 1]) {
            group = sp->get_groups_cnts()[course - 1];
        }
    }

    void Student::change_group(const unsigned short& group) {
        if(group == 0 || group > specialty->get_groups_cnts()[course - 1]) {
            throw StudentException("ERROR: Invalid group for course "
                + std::to_string(course)
                + " in this specialty");
        }
        this->group = group;
    }

    void Student::change_course(const unsigned short& course) {
        if(status == graduated) {
            throw StudentException("Can't change course. The student is graduated");
        }

        if(course != this->course + 1) {
            throw StudentException("Course can be changed only to next course");
        }

        advance();
    }

    void Student::enroll_in(const std::string& subject_name, App& app) {
        if(status == withdrawn) {
            throw StudentException("The student is withdrawn");
        }

        for(Grade& g : grades) {
            if(g.subject->get_command_name() == subject_name) {
                throw StudentException("The student is already enrolled in this subject");
            }
        }

        const std::vector<App::SpecSubj> spec_subjs = app.get_spec_subjs();
        for(const App::SpecSubj& ss : spec_subjs) {
            if(ss.specialty->get_command_name() == specialty->get_command_name() &&
                ss.subject->get_command_name() == subject_name &&
                ss.course == course) {
                    grades.push_back(Grade(2., ss.subject));
                    return;
                }
        }

        throw StudentException("Student's doesn't contain this subject");
    }

    void Student::add_grade(const double& value, const std::string& subject_name, App& app) {
        if(status == withdrawn) {
            throw StudentException("The student is withdrawn");
        }

        if(value < 2. - utils::GRADES_EPS || value > 6. + utils::GRADES_EPS) {
            throw StudentException("ERROR: Invalid grade value");
        }

        for(Grade& g : grades) {
            if(g.subject->get_command_name() == subject_name) {
                g.value = value;
                return;
            }
        }

        throw StudentException("The student hasn't been enrolled for this subject");
    }

    void Student::enroll() {
        if(status == enrolled) {
            throw StudentException("The student is already enrolled");
        }
        if(status == graduated) {
            throw StudentException("The student is graduated");
        }
        status = enrolled;
    }

    void Student::withdraw() {
        if(status == withdrawn) {
            throw StudentException("The student is already withdrawn");
        }
        status = withdrawn;
    }
    
    void Student::graduate() {
        if(status == withdrawn) {
            throw StudentException("The student is withdrawn");
        }

        for(const Grade& g : grades) {
            if(g.value < 3. - utils::GRADES_EPS) {
                throw StudentException("Can't graduate. The student has failed exams");
            }
        }
        status = graduated;
    }
    
    void Student::advance() {
        if(status == withdrawn) {
            throw StudentException("The student is withdrawn");
        }

        unsigned int failed_exams = 0;
        for(Grade& g : grades) {
            if(g.value < 3. - utils::GRADES_EPS) failed_exams++;
            if(failed_exams > specialty->get_max_failed_exams()) {
                throw StudentException("The student can't pass to the next course due to failed exams");
            }
        }

        if(course == specialty->get_courses_cnt()) {
            graduate();
            return;
        }

        course++;
        if(group > specialty->get_groups_cnts()[course]) {
            group = specialty->get_groups_cnts()[course];
        }
    }

    double Student::avg_grade() const {
        double grade = 0;
        for(size_t i = 0; i < grades.size(); i++) {
            grade += grades[i].value;
        }

        if(grades.size() == 0) return 0;

        return grade / grades.size();
    }

    void Student::read(std::ifstream& in, const App& app) {
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

        const std::vector<utils::SmartPtr<Specialty>>& specialties = app.get_specialties();
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

        // read course
        in.read((char*) &s.course, sizeof(s.course));
        if(s.course > s.specialty->get_courses_cnt()) {
            throw StudentException("ERROR: Invalid course for this specialty");
        }

        // read group
        in.read((char*) &s.group, sizeof(s.group));
        if(s.group > s.specialty->get_groups_cnts()[s.course - 1]) {
            throw StudentException("ERROR: Invalid group for course "
                + std::to_string(course)
                + " in this specialty");
        }
        
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
            Grade grade(0, utils::SmartPtr<Subject>());
            in.read((char*) &grade.value, sizeof(grade.value));

            if(grade.value < 2. - utils::GRADES_EPS || grade.value > 6. + utils::GRADES_EPS) {
                throw StudentException("ERROR: Invalid grade value");
            }

            // read size, subject->name
            in.read((char*) &size, sizeof(size));
            tmp = new char[size + 1];
            in.read(tmp, size);
            tmp[size] = '\0';
            
            const std::vector<utils::SmartPtr<Subject>>& subjects = app.get_subjects();
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

        // write course
        out.write((char*) &course, sizeof(course));

        // write group
        out.write((char*) &group, sizeof(group));
        
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