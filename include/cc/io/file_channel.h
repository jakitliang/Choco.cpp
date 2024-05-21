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

        Result Read(void * data, Size length, Size * bytesRead) override;

        Result ReadNonBlock(void * data, Size length, Size * bytesRead) override;

        Result Write(const void * data, Size length, Size * bytesWritten) override;

        Result WriteNonBlock(const void * data, Size length, Size * bytesWritten) override;

        FileChannel & operator=(const FileChannel & fileChannel);

        FileChannel & operator=(FileChannel && fileChannel) noexcept;

        static bool Exists(const char *dir);

        static Result GetContents(const char *dir, void *data, Size length, Size * bytesRead);

        static Result PutContents(const char *dir, const void *data, Size length, Size * bytesWritten);

        static bool MakeDir(const char *dir);

        static bool Unlink(const char *dir);
    };
}

#endif //CHOCO_CPP_FILE_CHANNEL_H
