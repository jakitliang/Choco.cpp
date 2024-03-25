//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/25.
//

#include "cc/file_io.h"
#include <cstdio>

CC::FileIO::FileIO() : context(nullptr) {}

CC::FileIO::FileIO(const char * fileName, const char * mode, int * error) {
    Open(fileName, mode, error);
}

CC::FileIO::~FileIO() {
    fclose(static_cast<FILE *>(context));
}

bool CC::FileIO::Open(const char *fileName, const char *mode, int *error) {
    auto fp = static_cast<FILE *>(context);
    errno_t err = fopen_s(&fp, fileName, mode);

    if (error != nullptr) *error = err;

    return err == 0;
}

CC::Size CC::FileIO::Write(void *buffer, CC::Size length) {
    return fwrite(buffer, 1, length, static_cast<FILE *>(context));
}

CC::Size CC::FileIO::WriteNonBlock(void *buffer, CC::Size length) {
#ifdef _WINDOWS
    return _fwrite_nolock(buffer, 1, length, static_cast<FILE *>(context));
#endif
}

CC::Size CC::FileIO::Read(void *buffer, CC::Size length) {
    return fread(buffer, 1, length, static_cast<FILE *>(context));
}

CC::Size CC::FileIO::ReadNonBlock(void *buffer, CC::Size length) {
#ifdef _WINDOWS
    return _fread_nolock(buffer, 1, length, static_cast<FILE *>(context));
#endif
}

bool CC::FileIO::Close() {
    if (context == nullptr) return true;

    fclose(static_cast<FILE *>(context));
    context = nullptr;

    return true;
}

bool CC::FileIO::IsClosed() {
    return context == nullptr;
}
