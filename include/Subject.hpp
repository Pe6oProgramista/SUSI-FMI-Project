#pragma once

#include <string>

namespace susi {

    class Subject {
    public:
        class Ptr {
        private:
            Subject* s;
        public:
            Ptr() : s(nullptr) {}
            Ptr(Subject* s) : s(s) { ++s->count; }
            Ptr(const Ptr& p) : s(p.s) { ++s->count; }
            ~Ptr() { if (!is_null() && --s->count == 0) delete s; }

            Ptr& operator= (const Ptr& p) {
                Subject* const old = s;
                s = p.s;
                ++s->count;
                if (--old->count == 0) delete old;
                return *this;
            }
            Subject* operator-> () const { return s; }
            Subject& operator* ()  { return *s; }

            bool is_null() const { return s == nullptr; }
        };

    private:
        std::size_t count = 0;

        std::string name;

    public:
        Subject() = default;
        Subject(std::string name);
        Subject(const Subject& s) = default;
        ~Subject() = default;
        
        Subject operator= (const Subject& s);

        std::string get_name() const;

        void read(std::ifstream& in);
        void write(std::ofstream& out) const;
    };

}