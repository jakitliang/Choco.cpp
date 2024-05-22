//
// Created by liangjie on 2024/5/22.
//

#ifndef CHOCO_CPP_RESULT_H
#define CHOCO_CPP_RESULT_H

#include <type_traits>

namespace CC {
    template<typename T>
    struct BasicResult : T {
        int Code;

        BasicResult() : Code(T::DefaultCode) {};

        // NOLINTNEXTLINE
        BasicResult(const int & code) : Code(code) {}

        BasicResult & operator=(const int & code) {
            Code = code;
            return *this;
        }

        bool operator==(const BasicResult & rhs) const {
            return Code == rhs.Code;
        }

        bool operator!=(const BasicResult & rhs) const {
            return Code != rhs.Code;
        }

        // NOLINTNEXTLINE
        operator bool() const {
            return test<T>(Code, nullptr);
        }

        template<typename OS>
        friend OS & operator<<(OS &os, const BasicResult & result) {
            return os << result.Code;
        }

        template<typename C>
        static bool test(const int & code, decltype(&C::Check) ) {
            return C::Check(code);
        }

        template<typename C>
        static bool test(const int & code, ...) {
            return code == T::DefaultCode;
        }
    };
}

#endif //CHOCO_CPP_RESULT_H
