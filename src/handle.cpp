//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/28.
//

#include "cc/handle.h"
#include "cc/zone.h"
#include <unordered_map>

static std::unordered_map<void *, CC::Size> HandleRef = {};

void Retain(CC::Handle & handle) {
    HandleRef.find
}

void Release() {}

CC::Handle::Handle() : object(Make<Type>()) { *object = nullptr; }

CC::Handle::Handle(const Handle & handle) : object(Retain(handle.object)) {}

CC::Handle::Handle(Handle && handle) noexcept : object(handle.object) { handle.object = nullptr; }

CC::Handle::~Handle() {
    Release(object);
    object = nullptr;
}

CC::Handle & CC::Handle::operator=(const Handle & handle) {
    if (this == &handle) return *this;

    Release(object);
    object = Retain(handle.object);

    return *this;
}

CC::Handle & CC::Handle::operator=(Handle && handle) noexcept {
    if (this == &handle) return *this;

    Release(object);
    object = handle.object;
    handle.object = nullptr;

    return *this;
}
