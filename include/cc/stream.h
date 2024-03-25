//
// Created by Jakit on 2024/3/11.
//

#ifndef CC_STREAM_H
#define CC_STREAM_H

#include "types.h"
#include "cc/data.h"

namespace CC {
    struct IStream {
        virtual Size onWrite(const void * buffer, Size length) = 0;

        virtual Size onRead(void * buffer, Size length) = 0;

        virtual bool onClose() = 0;
    };

    struct Stream {
        using Type = IStream;

        Type * delegate;

        Stream() : delegate(nullptr) { }

        Stream(const Stream & var) : delegate(Retain(var.delegate)) {}

        Stream(Stream && var) noexcept : delegate(var.delegate) {
            var.delegate = nullptr;
        }

        Stream(Type * object) : delegate(object) {}

        virtual Size Write(const void * buffer, Size length) {
            return delegate->onWrite(buffer, length);
        }

        virtual Size Read(void * buffer, Size length) {
            return delegate->onRead(buffer, length);
        }

        virtual bool Close() {
            return delegate->onClose();
        }
    };
}

#endif //CC_STREAM_H
