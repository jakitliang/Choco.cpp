//
// Created by Jakit on 2024/3/14.
//

#ifndef CC_ZONE_H
#define CC_ZONE_H

#include "types.h"

#if defined(_WINDOWS)
#include <vcruntime_new.h>
#else
#include <new>
#endif

namespace CC {
    template<typename T>
    using Initializer = void (*)(T & object);

    template<typename T>
    using TypeInitializer = void (T::*)();

    template<typename T>
    using Finalizer = void (*)(typename RemoveAll<T>::type & object);

    struct Zone {
        using Finalizer = void (*)(void * object);

        struct Record {
            void *End;
            Size Ref;
        };

        static void * Alloc(Size size);

        template<typename T>
        static auto Alloc(CC::Size count) {
            return reinterpret_cast<T *>(Alloc(sizeof(T) * count));
        }

        static void * ReAlloc(void * oldObject, Size size);

        template<typename T>
        static auto ReAlloc(void * oldObject, CC::Size count) {
            return reinterpret_cast<T *>(ReAlloc(oldObject, sizeof(T) * count));
        }

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
    T & Alloc(bool construct = true) {
        auto object = Zone::Alloc<T>(1);

        if (construct) {
            ::new (object) T();
        }

        return *object;
    }

    template<typename T>
    T & Alloc(Size count) {
        return *Zone::Alloc<T>(count);
    }

    template<typename T>
    T & Alloc(const T & copyObject) {
        auto object = Zone::Alloc<T>(1);
        *object = copyObject;
        return *object;
    }

    template<typename T>
    T & Alloc(T && moveObject) {
        auto object = Zone::Alloc<T>(1);
        *object = static_cast<T &&>(moveObject);
        return *object;
    }

    template<typename T>
    T & Alloc(Initializer<T> & initializer) {
        auto object = Zone::Alloc<T>(1);
        initializer(*object);
        return *object;
    }

    template<typename T>
    T & Alloc(TypeInitializer<T> initializer) {
        auto object = Zone::Alloc<T>(1);
        ((*object).*initializer)();
        return *object;
    }

//    template<typename T>
//    T & ReAlloc(void * oldObject, Size size) {
//
//    }

    template<typename T>
    T & Retain(T & object) {
        return *static_cast<T *>(Zone::Retain(&object));
    }

    template<typename T>
    bool Release(T & object, bool destruct = true) {
        static const auto destructor = [](void * o) {
            reinterpret_cast<T *>(o)->~T();
        };

        if (destruct) {
            return Zone::Release(&object, destructor);
        }

        return Zone::Release(&object);
    }

    template<typename T>
    bool Release(T & object, Finalizer<T> finalizer) {
        Zone::Release(&object, *reinterpret_cast<Zone::Finalizer *>(&finalizer));
        return true;
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
    void Construct(T * object, Size index, Size count) {
        object = object + index;

        if constexpr (std::is_trivial<T>::value) {
            Zone::Set(&object, 0, sizeof(T) * count);

        } else {
            for (int i = 0; i < count; ++i) {
                new (&object[i]) T();
            }
        }
    }

    template<typename T>
    static void Copy(T * object, Size index, const T * elements, Size count) {
        object = object + index;

        if constexpr (std::is_trivially_move_constructible<T>::value) {
            Zone::BlockCopy(object, 0, elements, sizeof(T) * count);

        } else {
            for (int i = 0; i < count; ++i) {
                object[i] = elements[i];
            }
        }
    }

    template<typename T>
    static void CopyConstruct(T * object, Size index, const T * elements, Size count) {
        object = object + index;

        if constexpr (std::is_trivially_move_constructible<T>::value) {
            Zone::BlockCopy(object, 0, elements, sizeof(T) * count);

        } else {
            for (int i = 0; i < count; ++i) {
                new (&object[i]) T(elements[i]);
            }
        }
    }

    template<typename T>
    static void Move(T * object, Size index, T * elements, Size count) {
        object = object + index;

        if constexpr (std::is_trivially_move_constructible<T>::value) {
            Zone::BlockCopy(object, 0, elements, sizeof(T) * count);

        } else {
            for (int i = 0; i < count; ++i) {
                object[i] = static_cast<T &&>(elements[i]);
            }
        }
    }

    template<typename T>
    static void MoveConstruct(T * object, Size index, T * elements, Size count) {
        object = object + index;

        if constexpr (std::is_trivially_move_constructible<T>::value) {
            Zone::BlockCopy(object, 0, elements, sizeof(T) * count);

        } else {
            for (int i = 0; i < count; ++i) {
                new (&object[i]) T(static_cast<T &&>(elements[i]));
            }
        }
    }

    template<typename T>
    void Destruct(T * object, Size index, Size count) {
        object = reinterpret_cast<T *>(object) + index;

        if constexpr (std::is_trivially_move_constructible<T>::value) {
            Zone::Set(object, 0, sizeof(T) * count);

        } else {
            for (int i = 0; i < count; ++i) {
                object[i].~T();
            }
        }
    }
}

#endif //CC_ZONE_H
