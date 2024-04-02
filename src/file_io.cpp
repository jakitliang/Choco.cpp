//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/25.
//

#include "cc/file_io.h"
#include "cc/handle.h"
#include <cstdio>
#include <cerrno>

static void Finalizer(void * context) {
    fclose(static_cast<FILE *>(context));
}

CC::FileIO::FileIO() : context(nullptr) {}

CC::FileIO::FileIO(const CC::FileIO &fileIO) : context(RetainHandle(fileIO.context)) {}

CC::FileIO::FileIO(CC::FileIO &&fileIO) noexcept : context(fileIO.context) { fileIO.context = nullptr; }

CC::FileIO::~FileIO() {
    ReleaseHandle(context, Finalizer);
}

void CC::FileIO::Open(const char *fileName, const char *mode, int *error) {
#ifdef _WINDOWS
    errno_t err = fopen_s(reinterpret_cast<FILE **>(&context), fileName, mode);
#else
    context = fopen(fileName, mode);
#endif

#ifdef _WINDOWS
    if (error != nullptr) *error = err;
#else
    if (context == nullptr) *error = errno;
#endif

    if (context) {
        RetainHandle(context);
    }
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

    ReleaseHandle(context, Finalizer);
    context = nullptr;

    return true;
}

bool CC::FileIO::IsClosed() {
    return context == nullptr;
}

CC::FileIO &CC::FileIO::operator=(const CC::FileIO &fileIO) {
    ReleaseHandle(context, Finalizer);
    context = RetainHandle(fileIO.context);
    return *this;
}

CC::FileIO &CC::FileIO::operator=(CC::FileIO &&fileIO) {
    ReleaseHandle(context, Finalizer);
    context = fileIO.context;
    fileIO.context = nullptr;
    return *this;
}
