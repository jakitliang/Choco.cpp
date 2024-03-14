//
// Created by Jakit on 2024/3/14.
//

#include "cc/zone.h"
#include <iostream>
#include <unordered_map>

CC_C_BEGIN
#include <malloc.h>
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

void *CC::Zone::ReAlloc(void *oldObject, CC::Size size) {
    if (oldObject == nullptr) return nullptr;

    auto ret = MemoryMap.find(oldObject);
    if (ret == MemoryMap.end()) return nullptr;

    auto object = realloc(oldObject, size + 1);

    if (object == nullptr) return oldObject;

    Byte * end = (Byte *) object + size;
    *end = 0;

    cout << "ReAlloc <" << oldObject << "> "
         << "-> <" << object << "> "
         << "ref[" << ret->second.Ref << "] "
         << "size[" << (UInt64) end - (UInt64) object << "]"
         << endl;

    MemoryMap[object] = {end, ret->second.Ref};
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

CC::Size CC::Zone::Size(void *object) {
    auto ret = MemoryMap.find(object);

    if (ret == MemoryMap.end()) {
#ifdef _WINDOWS
        return _msize(object);
#else
        return malloc_usable_size(object);
#endif
    }

    return (UInt64) ret->second.End - (UInt64) object;
}

CC::Size CC::Zone::Size(const void *object) {
    auto ret = MemoryMap.find((void *) (CC::UInt64) object);

    if (ret == MemoryMap.end()) {
#ifdef _WINDOWS
        return _msize(((void *) (CC::UInt64) object));
#else
        return malloc_usable_size(((void *) (CC::UInt64) object));
#endif
    }

    return (UInt64) ret->second.End - (UInt64) object;
}
