//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/25.
//

#ifndef CHOCO_CPP_FILE_CHANNEL_H
#define CHOCO_CPP_FILE_CHANNEL_H

#include "cc/channel.h"
#include "cc/file_io.h"

namespace CC {
    struct FileChannel : Channel {
        FileIO & file;

        FileChannel(); // Todo: Random file RW

        FileChannel(const char * fileName, const char * mode, int * error = nullptr);
    };
}

#endif //CHOCO_CPP_FILE_CHANNEL_H
