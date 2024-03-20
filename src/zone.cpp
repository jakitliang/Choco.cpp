//
// Created by Jakit on 2024/3/14.
//

#include "cc/zone.h"
#include <iostream>
#include <unordered_map>
#include <cstring>

CC_C_BEGIN
#if defined(_WINDOWS)
#include <malloc.h>
#elif defined(__APPLE__)
#include <malloc/malloc.h>
#elif defined(__GNUC__)
#include <malloc.h>
#endif
CC_C_END

using namespace std;

using MemoryMapType = unordered_map<void *, CC::Zone::Record>;
static MemoryMapType MemoryMap = {};

void *CC::Zone::Alloc(CC::Size size) {
    void * object = malloc(size + 1);
    Byte * end = (Byte *) object + size;
    *end = 0;

    MemoryMap[object] = {end, 1};

    cout << "Alloc   <" << object << "> "
         << "ref[" << 1 << "] "
         << "size[" << size << "]"
         << endl;

    return object;
}

void *CC::Zone::ReAlloc(void *oldObject, CC::Size size, bool * result) {
    if (oldObject == nullptr) return nullptr;

    auto ret = MemoryMap.find(oldObject);
    if (ret == MemoryMap.end()) return nullptr;

    auto object = realloc(oldObject, size + 1);

    if (result != nullptr) *result = (object != nullptr);
    if (object == nullptr) return oldObject;

    Byte * end = (Byte *) object + size;
    *end = 0;

    cout << "ReAlloc <" << oldObject << "> "
         << "-> <" << object << "> "
         << "ref[" << ret->second.Ref << "] "
         << "size[" << (UInt64) end - (UInt64) object << "]"
         << endl;

    MemoryMap[object] = {end, ret->second.Ref};
    if (object == oldObject) return object; // Same address

    MemoryMap.erase(oldObject);
    return object;
}

void *CC::Zone::Retain(void *object) {
    if (object == nullptr) return nullptr;

    auto ret = MemoryMap.find(object);
    if (ret == MemoryMap.end()) return nullptr;

    ret->second.Ref += 1;

    cout << "Retain  <" << object << "> "
         << "ref[" << ret->second.Ref << "] "
         << "size[" << (UInt64) ret->second.End - (UInt64) object << "]"
         << endl;

    return object;
}

bool CC::Zone::Release(void *object) {
    if (object == nullptr) return false;

    auto ret = MemoryMap.find(object);
    if (ret == MemoryMap.end()) return false;

    ret->second.Ref -= 1;

    cout << "Release <" << object << "> "
         << "ref[" << ret->second.Ref << "] "
         << "size[" << (UInt64) ret->second.End - (UInt64) object << "]"
         << (ret->second.Ref == 0 ? " freed!" : "") << endl;

    if (ret->second.Ref > 0) return false;
    MemoryMap.erase(object);
    free(object);

    return true;
}

bool CC::Zone::Release(void * object, Finalizer finalizer) {
    if (object == nullptr) return false;

    auto ret = MemoryMap.find(object);
    if (ret == MemoryMap.end()) return false;

    ret->second.Ref -= 1;

    cout << "Release <" << object << "> "
         << "ref[" << ret->second.Ref << "] "
         << "size[" << (UInt64) ret->second.End - (UInt64) object << "]"
         << (ret->second.Ref == 0 ? " freed!" : "") << endl;

    if (ret->second.Ref > 0) return false;
    (*finalizer)(object, 0, (Size) ret->second.End - (Size) object);
    MemoryMap.erase(object);
    free(object);

    return true;
}

CC::Size CC::Zone::Count(void *object) {
    auto ret = MemoryMap.find(object);

    if (ret == MemoryMap.end()) {
#ifdef _WINDOWS
        return _msize(object);
#elif defined(__MINGW64__) || defined(__MINGW32__)
        return _msize(object);
#elif defined(__APPLE__)
        return malloc_size(((void *) (CC::UInt64) object));
#else
        return malloc_usable_size(object);
#endif
    }

    return (UInt64) ret->second.End - (UInt64) object;
}

CC::Size CC::Zone::Count(const void *object) {
    auto ret = MemoryMap.find((void *) (CC::UInt64) object);

    if (ret == MemoryMap.end()) {
#ifdef _WINDOWS
        return _msize(((void *) (CC::UInt64) object));
#elif defined(__MINGW64__) || defined(__MINGW32__)
        return _msize(((void *) (CC::UInt64) object));
#elif defined(__APPLE__)
        return malloc_size(((void *) (CC::UInt64) object));
#else
        return malloc_usable_size(((void *) (CC::UInt64) object));
#endif
    }

    return (UInt64) ret->second.End - (UInt64) object;
}

void CC::Zone::Set(void * object, int n, Size size){
    memset(object, n, size);
}

void CC::Zone::Zero(void *object, CC::Size size) {
    std::memset(object, 0, size);
}

void CC::Zone::BlockCopy(void * object, Size index, const void * elements, Size count) {
    memmove((Byte *) object + index, elements, count);
}
