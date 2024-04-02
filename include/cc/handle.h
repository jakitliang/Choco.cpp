//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/27.
//

#ifndef CHOCO_CPP_HANDLE_H
#define CHOCO_CPP_HANDLE_H

namespace CC {
    struct Handle {
        using Finalizer = void (*)(void * handle);

        static void * Retain(void * handle);

        static bool Release(void * handle, Finalizer finalizer);
    };

    template<typename T>
    T * RetainHandle(T * handle) {
        return reinterpret_cast<T *>(Handle::Retain(handle));
    }

    bool ReleaseHandle(void * handle, Handle::Finalizer finalizer);
}

#endif //CHOCO_CPP_HANDLE_H
