//
// Created by Jakit on 2024/3/14.
//

#ifndef CC_ZONE_H
#define CC_ZONE_H

#include "types.h"

#if defined(_WINDOWS)
#include <vcruntime_new.h>
#include <type_traits>
#else
#include <new>
#endif

namespace CC {
    struct Zone {
        using Finalizer = void (*)(void * object, Size index, Size size);

        struct Record {
            void *End;
            Size Ref;
        };

        static void * Alloc(Size size);

        static void * ReAlloc(void * oldObject, Size size, bool * result = nullptr);

        static void * Retain(void * object);

        static bool Release(void * object);

        static bool Release(void * object, Finalizer finalizer);

        static Size Count(void * object);

        static CC::Size Count(const void * object);

        static void Set(void * object, int n, Size size);

        static void Zero(void * object, Size size);

        static void BlockCopy(void * object, Size index, const void * elements, Size count);
    };

    template<typename T>
    void Swap(T & lhs, T & rhs) {
        T    tmp = static_cast<T &&>(lhs);
        lhs      = static_cast<T &&>(rhs);
        rhs      = static_cast<T &&>(tmp);
    }

    template<typename T>
    static CC::Size Count(void * object) {
        return object == nullptr ? 0 : Zone::Count(object) / sizeof(T);
    }

    template<typename T>
    static CC::Size Count(const void * object) {
        return object == nullptr ? 0 : Zone::Count(object) / sizeof(T);
    }

    template<typename T>
    T * Construct(T * object, Size index, Size count) {
        auto target = object + index;

        if constexpr (std::is_trivially_constructible<T>::value) {
            Zone::Set(target, 0, sizeof(T) * count);

        } else {
            for (int i = 0; i < count; ++i) {
                new (&target[i]) T();
            }
        }

        return object;
    }

    template<typename T>
    T * Construct(T * object) {
        return Construct(object, 0, 1);
    }

    template<typename T>
    static T * Copy(T * object, Size index, const T * elements, Size count) {
        auto target = object + index;

        if constexpr (std::is_trivially_copy_assignable<T>::value) {
            Zone::BlockCopy(target, 0, elements, sizeof(T) * count);

        } else {
            for (int i = 0; i < count; ++i) {
                target[i] = elements[i];
            }
        }

        return object;
    }

    template<typename T>
    static T * Copy(T * object, const T * element) {
        return Copy(object, 0, element, 1);
    }

    template<typename T>
    static T * CopyConstruct(T * object, Size index, const T * elements, Size count) {
        auto target = object + index;

        if constexpr (std::is_trivially_copy_constructible<T>::value) {
            Zone::BlockCopy(target, 0, elements, sizeof(T) * count);

        } else {
            for (int i = 0; i < count; ++i) {
                new (&target[i]) T(elements[i]);
            }
        }

        return object;
    }

    template<typename T>
    static T * CopyConstruct(T * object, const T * element) {
        return CopyConstruct(object, 0, element, 1);
    }

    template<typename T>
    static T * Move(T * object, Size index, T * elements, Size count) {
        auto target = object + index;

        if constexpr (std::is_trivially_move_assignable<T>::value) {
            Zone::BlockCopy(target, 0, elements, sizeof(T) * count);

        } else {
            for (int i = 0; i < count; ++i) {
                target[i] = static_cast<T &&>(elements[i]);
            }
        }

        return object;
    }

    template<typename T>
    static T * Move(T * object, T * element) {
        return Move(object, 0, element, 1);
    }

    template<typename T>
    static T * MoveConstruct(T * object, Size index, T * elements, Size count) {
        auto target = object + index;

        if constexpr (std::is_trivially_move_constructible<T>::value) {
            Zone::BlockCopy(target, 0, elements, sizeof(T) * count);

        } else {
            for (int i = 0; i < count; ++i) {
                new (&target[i]) T(static_cast<T &&>(elements[i]));
            }
        }

        return object;
    }

    template<typename T>
    static T * MoveConstruct(T * object, T * element) {
        return MoveConstruct(object, 0, element, 1);
    }

    template<typename T>
    T * Destruct(T * object, Size index, Size count) {
        auto target = object + index;

        if constexpr (std::is_trivially_destructible<T>::value) {
            Zone::Set(target, 0, sizeof(T) * count);

        } else {
            for (int i = 0; i < count; ++i) {
                target[i].~T();
            }
        }

        return nullptr;
    }

    template<typename T>
    T * Destruct(T * object) {
        return Destruct(object, 0, 1);
    }

    template<typename T>
    T * Alloc() {
        return static_cast<T *>(Zone::Alloc(sizeof(T)));
    }

    template<typename T>
    T * Alloc(Size count) {
        return static_cast<T *>(Zone::Alloc(count * sizeof(T)));
    }

    template<typename T>
    T * Make() {
        return Construct<T>(static_cast<T *>(Zone::Alloc(sizeof(T))), 0, 1);
    }

    template<typename T>
    T * Make(Size count) {
        return Construct<T>(static_cast<T *>(Zone::Alloc(count * sizeof(T))), 0, count);
    }

    template<typename T>
    T * Clone(const T & copyObject) {
        return CopyConstruct<T>(Alloc<T>(), 0, &copyObject, 1);
    }

    template<typename T>
    T * Clone(T && moveObject) {
        return MoveConstruct<T>(Alloc<T>(), 0, &moveObject, 1);
    }

    template<typename T, Size S>
    T * Clone(const T (&copyObject)[S]) {
        return CopyConstruct<T>(Alloc<T>(S), 0, &copyObject[0], S);
    }

    template<typename T, Size S>
    T * Clone(T (&&moveObject)[S]) {
        return MoveConstruct<T>(Alloc<T>(S), 0, &moveObject[0], S);
    }

    template<typename T>
    T * ReAlloc(void * oldObject, Size count) {
        bool result = false;
        return static_cast<T *>(Zone::ReAlloc(oldObject, count * sizeof(T), &result));
    }

    template<typename T>
    T * ReMake(void * oldObject, Size count) {
        bool result = false;
        Size oldCount = Count<T>(oldObject);

        if (oldCount > count) Destruct<T>(reinterpret_cast<T *>(oldObject), count, oldCount - count);

        auto object = static_cast<T *>(Zone::ReAlloc(oldObject, count * sizeof(T), &result));

        if (result && count > oldCount) Construct<T>(object, oldCount, count - oldCount);

        return object;
    }

    template<typename T>
    T * Retain(T * object) {
        return static_cast<T *>(Zone::Retain(object));
    }

    template<typename T>
    bool Release(T * object) {
        return Zone::Release(object);
    }

    template<typename T>
    bool Destroy(T * object) {
        static const auto destructor = [](void * o, Size index, Size size) {
            Destruct<T>(static_cast<T *>(o), index, size / sizeof(T));
        };

        return Zone::Release(object, destructor);
    }
}

#endif //CC_ZONE_H
