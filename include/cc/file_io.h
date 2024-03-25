//
// Created by Jakit on 2024/3/25.
//

#ifndef CHOCO_CPP_FILE_IO_H
#define CHOCO_CPP_FILE_IO_H

#include "cc/io.h"

namespace CC {
    struct FileIO : IO {
        void * context;

        FileIO();

        FileIO(const char * fileName, const char * mode, int * error = nullptr);

        ~FileIO();

        bool Open(const char * fileName, const char * mode, int * error = nullptr);

        virtual Size Write(void * buffer, Size length) override;

        virtual Size WriteNonBlock(void * buffer, Size length) override;

        virtual Size Read(void * buffer, Size length) override;

        virtual Size ReadNonBlock(void * buffer, Size length) override;

        virtual bool Close() override;

        virtual bool IsClosed() override;
    };
}

#endif //CHOCO_CPP_FILE_IO_H
