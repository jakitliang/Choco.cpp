//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/8.
//

#ifndef CHOCO_CPP_STRING_H
#define CHOCO_CPP_STRING_H

#include "cc/array.h"
#include "cc/sequence.h"

namespace CC {
    struct String : Var<char []> {
        using Type = char;

        Type * object;
        Size * length;

        String();

        String(const String & str);

        String(String && str) noexcept;

        String(const char * cStr, Size length);

        String(const char * cStr);

        String(const Byte * bytes, Size length);

        ~String();

        Size Length() const;

        Size Count() const override;

        char * CString();

        const char * CString() const;

        bool operator!() const;

        // Algorithms

        void Insert(Size index, const char * str, Size length);

        void Insert(Size index, const char * str);

        void Insert(Size index, const char & t);

        void Push(const char * str, Size length);

        void Push(const char * str);

        void Push(const char & t);

        void Delete(Size index, Size length);

        void Delete(Size index);

        String & operator=(const String & string);

        String & operator=(String && string) noexcept;

        bool operator==(const char * cString) const;

        bool operator==(const String & string) const;

        bool operator!=(const char * cString) const;

        bool operator!=(const String & string) const;

        String operator+(const char * cString) const;

        String operator+(const String &string) const;

        String &operator+=(const char * cString);

        String &operator+=(const String &string);

        char & operator[](Size index) override;

        const char & operator[](Size index) const override;

        Iterator end() override;

        Iterator end() const override;

        template<typename OS>
        friend OS & operator<<(OS &os, const String & str) {
            return os << str.CString();
        }

        static String Format(const char * format, ...);
    };
}

#endif //CHOCO_CPP_STRING_H
