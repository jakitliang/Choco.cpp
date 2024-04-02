//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/25.
//

#include "cc/channel.h"
//#include "cc/zone.h"

const CC::Size BufferSize = 8 * 1024 * 1024;

CC::Channel::Channel()
    : input(Clone(CC::Data(BufferSize))), output(CC::Make<CC::Data>()), io(nullptr) {}

CC::Channel::Channel(const CC::Channel &channel)
    : input(Retain(channel.input)), output(CC::Make<CC::Data>()), io(channel.io) {}

CC::Channel::Channel(Channel && channel) noexcept
    : input(channel.input), output(channel.output), io(channel.io) {
    channel.input = nullptr;
    channel.output = nullptr;
}

CC::Channel::Channel(CC::IO *io)
    : input(Clone(CC::Data(BufferSize))), output(CC::Make<CC::Data>()), io(io) {}

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

CC::Channel & CC::Channel::operator=(const CC::Channel & channel) {
    if (this == &channel) return *this;

    Destroy(channel.input);
    Destroy(channel.output);

    input = Retain(channel.input);
    output = Retain(channel.output);
    io = channel.io;

    return *this;
}

CC::Channel &CC::Channel::operator=(CC::Channel &&channel) noexcept {
    Destroy(channel.input);
    Destroy(channel.output);

    input = channel.input;
    output = channel.output;
    io = channel.io;

    channel.input = nullptr;
    channel.output = nullptr;
    channel.io = nullptr;

    return *this;
}
