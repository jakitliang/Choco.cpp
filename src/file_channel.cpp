//
// Created by Jakit on 2024/3/26.
//

#include "cc/file_channel.h"

CC::FileChannel::FileChannel() : file(*dynamic_cast<CC::FileIO *>(this->io)) {}

CC::FileChannel::FileChannel(const char *fileName, const char *mode, int * error)
    : Channel(CC::Clone(CC::FileIO(fileName, mode, error))), file(*dynamic_cast<CC::FileIO *>(this->io)) {}