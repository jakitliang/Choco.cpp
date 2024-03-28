//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/11.
//

#ifndef CC_FILE_H
#define CC_FILE_H

#include "cc/object.h"
#include "cc/stream.h"

namespace CC {
    struct FileStream : Stream {
        struct IO : Stream::IO {
            Size Write(const void * buffer, Size length) override {
                return 0;
            }

            Size Read(void * buffer, Size length) override {
                return 0;
            }

            bool Close() override {
                return false;
            }
        };

        FileStream() : Stream(Make<FileStream::IO>()) {}

        FileStream(const FileStream & fileStream);

        FileStream(FileStream && fileStream);
    };
}

#endif //CC_FILE_H
