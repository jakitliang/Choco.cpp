//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/28.
//

#include "cc/handle.h"
#include "cc/zone.h"

CC::Handle::Handle() : object(Make<Type>()) { *object = nullptr; }

CC::Handle::Handle(const Handle & handle) : object(Retain(handle.object)) {}

CC::Handle::~Handle() {
    Release(object);
    object = nullptr;
}
