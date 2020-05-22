#pragma once

namespace susi {
    namespace utils {

        template<class T>
        class SmrtPtr {
        private:
            T* t;
            unsigned int* count;
        public:
            SmrtPtr() : t(nullptr), count(nullptr) {}
            SmrtPtr(T* t) : t(t) {
                count = new unsigned int(1);
            }
            SmrtPtr(const SmrtPtr& p) : t(p.t), count(p.count) { ++(*count); }
            ~SmrtPtr() {
                if(!is_null() && --(*count) == 0) {
                    delete t;
                    delete count;
                }
            }

            SmrtPtr& operator= (const SmrtPtr& p) {
                T* const old_t = t;
                unsigned int* const old_count = count;

                t = p.t;
                count = p.count;
                ++(*count);

                if (old_t != nullptr && --(*old_count) == 0) {
                    delete old_t;
                    delete old_count;
                }
                return *this;
            }
            T* operator-> () const { return t; }
            T& operator* ()  { return *t; }
            const T& operator* () const { return *t; }

            bool is_null() const { return t == nullptr; }
        };

    }
}