//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/io/file_channel.h"
#include "cc/handle.h"
#include <cstdio>
#include <cerrno>
#include <fstream>

#ifdef _WIN32
#include <direct.h>
#else
extern "C" {
#include <sys/stat.h>
#include <unistd.h>
};
#endif

void FileHandleFinalizer(void * handle) {
    fclose(static_cast<FILE *>(handle));
}

CC::IO::FileChannel::FileChannel() : context(nullptr) {}

CC::IO::FileChannel::FileChannel(const CC::IO::FileChannel &fileChannel) : context(RetainHandle(fileChannel.context)){}

CC::IO::FileChannel::FileChannel(CC::IO::FileChannel &&fileChannel) noexcept : context(fileChannel.context) {
    fileChannel.context = nullptr;
}

CC::IO::FileChannel::~FileChannel() {
    ReleaseHandle(context, FileHandleFinalizer);
}

void CC::IO::FileChannel::Open(const char *fileName, const char *mode, int *error) {
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

bool CC::IO::FileChannel::Close() {
    if (context == nullptr) return true;

    ReleaseHandle(context, FileHandleFinalizer);

    context = nullptr;

    return true;
}

bool CC::IO::FileChannel::IsClosed() {
    return context == nullptr;
}

CC::Size CC::IO::FileChannel::Write(const void *data, CC::Size length) {
    return fwrite(data, 1, length, static_cast<FILE *>(context));
}

CC::Size CC::IO::FileChannel::WriteNonBlock(const void *data, CC::Size length) {
    return Write(data, length);
}

CC::Size CC::IO::FileChannel::Read(void *data, CC::Size length) {
    return fread(data, 1, length, static_cast<FILE *>(context));
}

CC::Size CC::IO::FileChannel::ReadNonBlock(void *data, CC::Size length) {
    return Read(data, length);
}

CC::IO::FileChannel &CC::IO::FileChannel::operator=(const CC::IO::FileChannel &fileChannel) {
    if (this == &fileChannel) return *this;

    ReleaseHandle(context, FileHandleFinalizer);
    context = RetainHandle(fileChannel.context);

    return *this;
}

CC::IO::FileChannel &CC::IO::FileChannel::operator=(CC::IO::FileChannel &&fileChannel) noexcept {
    if (this == &fileChannel) return *this;

    ReleaseHandle(context, FileHandleFinalizer);
    context = fileChannel.context;
    fileChannel.context = nullptr;

    return *this;
}

bool CC::IO::FileChannel::Exists(const char *dir) {
    return std::ifstream(dir).good();
}

CC::Size CC::IO::FileChannel::GetContents(const char *dir, void *data, CC::Size length) {
    if (!Exists(dir)) return 0;

    std::ifstream f(dir);
    // Seek end
    f.seekg(0, std::ios_base::end);

    if (length == 0 || length > f.tellg()) length = f.tellg(); // Out of file size

    // Seek begin
    f.seekg(0, std::ios_base::beg);

    // Read content
    f.read(static_cast<char *>(data), (std::streamsize) length);

    return length;
}

CC::Size CC::IO::FileChannel::PutContents(const char *dir, const void *data, CC::Size length) {
    std::ofstream f(dir, std::ios::binary);

    if (!f.is_open()) return 0;

    f.write(static_cast<const char *>(data), (std::streamsize) length);

    return length;
}

bool CC::IO::FileChannel::MakeDir(const char *dir) {
#ifdef _WIN32
    return _mkdir(dir) == 0;
#else
    return mkdir(dir, 0755) == 0;
#endif
}

bool CC::IO::FileChannel::Unlink(const char *dir) {
#ifdef _WIN32
    return _unlink(dir) == 0;
#else
    return unlink(dir) == 0;
#endif
}
