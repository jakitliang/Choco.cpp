//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/file_channel.h"

CC::FileChannel::FileChannel() : Channel(), file(*dynamic_cast<CC::FileIO *>(this->io)) {}

CC::FileChannel::FileChannel(const char *fileName, const char *mode, int * error)
    : Channel(Make<CC::FileIO>()), file(*dynamic_cast<CC::FileIO *>(this->io)) {
    file.Open(fileName, mode, error);
}

CC::FileChannel::~FileChannel() noexcept {
    if (io == nullptr) return;

    auto fileIO = dynamic_cast<CC::FileIO *>(this->io);
    Destroy(fileIO);
}
