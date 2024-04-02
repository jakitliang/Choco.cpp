//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/28.
//

#include "cc/handle.h"
#include "cc/types.h"
#include <iostream>
#include <unordered_map>

using HandleMapType = std::unordered_map<void *, CC::Size>;

static HandleMapType HandleMap = {};

void * CC::Handle::Retain(void *handle) {
    if (handle == nullptr) return handle;

    auto ret = HandleMap.find(handle);
    if (ret != HandleMap.end()) {
        ret->second += 1;
        std::cout << "HRetain:  <" << handle << "> ref [" << ret->second << "]" << std::endl;

    } else {
        HandleMap[handle] = 1;
        std::cout << "HRetain:  <" << handle << "> ref [1]" << std::endl;
    }

    return handle;
}

bool CC::Handle::Release(void *handle, Finalizer finalizer) {
    if (handle == nullptr) return false;

    auto ret = HandleMap.find(handle);
    if (ret == HandleMap.end()) return false;

    ret->second -= 1;

    std::cout << "HRelease: <" << handle << "> ref [" << ret->second << "]" << std::endl;

    if (ret->second > 0) {
        return false;
    }

    if (finalizer) finalizer(handle);
    HandleMap.erase(handle);

    return true;
}

bool CC::ReleaseHandle(void *handle, Handle::Finalizer finalizer) {
    return Handle::Release(handle, finalizer);
}
