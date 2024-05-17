//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/25.
//

#ifndef CHOCO_CPP_FILE_CHANNEL_H
#define CHOCO_CPP_FILE_CHANNEL_H

#include "cc/io/channel.h"

namespace CC::IO {
    struct FileChannel : IChannel, IChannelReader, IChannelWriter {
        void * context;

        FileChannel();

        FileChannel(const FileChannel & fileChannel);

        FileChannel(FileChannel && fileChannel) noexcept;

        ~FileChannel();

        void Open(const char * fileName, const char * mode, int * error = nullptr);

        bool Close() override;

        bool IsClosed() override;

        Size Read(void * data, Size length) override;

        Size ReadNonBlock(void * data, Size length) override;

        Size Write(const void * data, Size length) override;

        Size WriteNonBlock(const void * data, Size length) override;

        FileChannel & operator=(const FileChannel & fileChannel);

        FileChannel & operator=(FileChannel && fileChannel) noexcept;

        static bool Exists(const char *dir);

        static Size GetContents(const char *dir, void *data, Size length = 0);

        static Size PutContents(const char *dir, const void *data, Size length);

        static bool MakeDir(const char *dir);

        static bool Unlink(const char *dir);
    };
}

#endif //CHOCO_CPP_FILE_CHANNEL_H
