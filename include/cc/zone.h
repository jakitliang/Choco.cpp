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
        using Finalizer = void (*)(void * object, Size size);

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

//        static void Replace(void * object, Size index, const void * elements, Size count);
    };

    template<typename T>
    T * Alloc(bool construct = true) {
        if (construct) return Construct<T>(static_cast<T *>(Zone::Alloc(sizeof(T))), 0, 1);

        return static_cast<T *>(Zone::Alloc(sizeof(T)));
    }

    template<typename T>
    T * Alloc(Size count, bool construct = true) {
        if (construct) return Construct<T>(static_cast<T *>(Zone::Alloc(count * sizeof(T))), 0, count);

        return static_cast<T *>(Zone::Alloc(count * sizeof(T)));
    }

    template<typename T>
    T & Make(bool construct = true) { return *Alloc<T>(construct); }

    template<typename T>
    T & Make(Size count, bool construct = true) { return *Alloc<T>(count, construct); }

    template<typename T>
    T * Clone(const T & copyObject) {
        return CopyConstruct<T>(Alloc<T>(false), 0, &copyObject, 1);
    }

    template<typename T>
    T * Clone(T && moveObject) {
        return MoveConstruct<T>(Alloc<T>(false), 0, &moveObject, 1);
    }

    template<typename T>
    T & ReMake(const T & copyObject) {
        return *Clone(copyObject);
    }

    template<typename T>
    T & ReMake(T && moveObject) {
        return *Clone(static_cast<T &&>(moveObject));
    }

    template<typename T>
    T * ReAlloc(void * oldObject, Size count, bool construct = false) {
        bool result = false;
        Size oldCount = count;
        if (construct) oldCount = Count<T>(oldObject);

        auto object = static_cast<T *>(Zone::ReAlloc(oldObject, count * sizeof(T), &result));
        if (!construct) return object;

        if (result && count > oldCount) Construct<T>(object, oldCount, count - oldCount);

        return object;
    }

    template<typename T>
    T * Retain(T * object) {
        return static_cast<T *>(Zone::Retain(object));
    }

    template<typename T>
    T & Retain(T & object) {
        return *Retain(&object);
    }

    template<typename T>
    bool Release(T * object, bool destruct = true) {
        static const auto destructor = [](void * o, Size size) {
            Destruct<T>(static_cast<T *>(o), 0, size / sizeof(T));
        };

        if (destruct) {
            return Zone::Release(object, destructor);
        }

        return Zone::Release(object);
    }

    template<typename T>
    bool Release(T & object, bool destruct = true) {
        return Release<T>(&object, destruct);
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

        if constexpr (std::is_trivial<T>::value) {
            Zone::Set(target, 0, sizeof(T) * count);

        } else {
            for (int i = 0; i < count; ++i) {
                new (&target[i]) T();
            }
        }

        return object;
    }

    template<typename T>
    static void Copy(T * object, Size index, const T * elements, Size count) {
        object = object + index;

        if constexpr (std::is_trivially_copy_assignable<T>::value) {
            Zone::BlockCopy(object, 0, elements, sizeof(T) * count);

        } else {
            for (int i = 0; i < count; ++i) {
                object[i] = elements[i];
            }
        }
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
    static void Move(T * object, Size index, T * elements, Size count) {
        object = object + index;

        if constexpr (std::is_trivially_move_assignable<T>::value) {
            Zone::BlockCopy(object, 0, elements, sizeof(T) * count);

        } else {
            for (int i = 0; i < count; ++i) {
                object[i] = static_cast<T &&>(elements[i]);
            }
        }
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
    void Destruct(T * object, Size index, Size count) {
        auto target = object + index;

        if constexpr (std::is_trivial<T>::value) {
            Zone::Set(target, 0, sizeof(T) * count);

        } else {
            for (int i = 0; i < count; ++i) {
                target[i].~T();
            }
        }
    }
}

#endif //CC_ZONE_H
