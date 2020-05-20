#pragma once

#include <string>
#include <vector>
#include <fstream>

namespace susi {
    class Specialty {
    public:
        class Ptr {
        private:
            Specialty* s;
        public:
            Ptr() : s(nullptr) {}
            Ptr(Specialty* s) : s(s) { ++s->count; }
            Ptr(const Ptr& p) : s(p.s) { ++s->count; }
            ~Ptr() { if (!is_null() && --s->count == 0) delete s; }

            Ptr& operator= (const Ptr& p) {
                Specialty* const old = s;
                s = p.s;
                ++s->count;
                if (--old->count == 0) delete old;
                return *this;
            }
            
            Specialty* operator-> () const { return s; }
            Specialty& operator* ()  { return *s; }

            bool is_null() const { return s == nullptr; }
        };

    private:
        std::size_t count = 0;

        std::string name;
        std::string command_name;
        unsigned short groups_cnt;

    public:
        Specialty() = default;
        Specialty(std::string name, std::string command_name, unsigned short groups_cnt);
        Specialty(const Specialty& s) = default;
        ~Specialty() = default;

        Specialty operator= (const Specialty& s);

        std::string get_name() const;
        std::string get_command_name() const;
        unsigned short get_groups_cnt() const;

        void read(std::ifstream& in);
        void write(std::ofstream& out) const;
    };

}