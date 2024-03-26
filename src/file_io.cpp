//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/25.
//

#include "cc/file_io.h"
#include <cstdio>
#include <cerrno>

CC::FileIO::FileIO() : context(nullptr) {}

CC::FileIO::~FileIO() {
    fclose(static_cast<FILE *>(context));
}

void CC::FileIO::Open(const char *fileName, const char *mode, int *error) {
    auto fp = static_cast<FILE *>(context);
#ifdef _WINDOWS
    errno_t err = fopen_s(&fp, fileName, mode);
#else
    fp = fopen(fileName, mode);
#endif

#ifdef _WINDOWS
    if (error != nullptr) *error = err;
#else
    if (fp == nullptr) *error = errno;
#endif
}

CC::Size CC::FileIO::Write(void *buffer, CC::Size length) {
    return fwrite(buffer, 1, length, static_cast<FILE *>(context));
}

CC::Size CC::FileIO::WriteNonBlock(void *buffer, CC::Size length) {
    return Write(buffer, length);
}

CC::Size CC::FileIO::Read(void *buffer, CC::Size length) {
    return fread(buffer, 1, length, static_cast<FILE *>(context));
}

CC::Size CC::FileIO::ReadNonBlock(void *buffer, CC::Size length) {
    return Read(buffer, length);
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
