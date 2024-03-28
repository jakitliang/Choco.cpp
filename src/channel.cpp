//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/25.
//

#include "cc/channel.h"

const CC::Size BufferSize = 8 * 1024 * 1024;

CC::Channel::Channel()
    : input(Clone(CC::Data(BufferSize))), output(CC::Make<CC::Data>()) {}

CC::Channel::Channel(const CC::Channel &channel)
    : input(Retain(channel.input)), output(CC::Make<CC::Data>()) {}

CC::Channel::Channel(Channel && channel)
    : input(channel.input), output(channel.output) {
    channel.input = nullptr;
    channel.output = nullptr;
}

CC::Channel::Channel(CC::IO *io)
    : io(io), input(Clone(CC::Data(BufferSize))), output(CC::Make<CC::Data>()) {}

CC::Channel::~Channel() {
    Destroy(input);
    Destroy(output);
}

CC::Size CC::Channel::Write(const void *buffer, CC::Size length) {
    Size len;

    output->Push(buffer, length);
    len = io->Write(output->CData(), output->Length());

    if (len > 0) output->Shift(len);

    return len;
}

CC::Size CC::Channel::WriteAsync(const void *buffer, CC::Size length) {
    Size len;

    output->Push(buffer, length);
    len = io->WriteNonBlock(output->CData(), output->Length());

    if (len > 0) output->Shift(len);

    return len;
}

CC::Data & CC::Channel::Read(CC::Size length, Size * size) {
    Size len;
    auto needLength = length + input->Length();

    if (needLength > input->Count()) {
        input->Resize(needLength);
    }

    len = io->Read(input->CData(input->Length()), length);

    if (size != nullptr) *size = len;

    return *input;
}

CC::Data & CC::Channel::ReadAsync(CC::Size length, CC::Size *size) {
    Size len;
    auto needLength = length + input->Length();

    if (needLength > input->Count()) {
        input->Resize(needLength);
    }

    len = io->ReadNonBlock(input->CData(input->Length()), length);

    if (size != nullptr) *size = len;

    return *input;
}

bool CC::Channel::Close() {
    return io->Close();
}
