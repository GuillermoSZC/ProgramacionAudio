#pragma once
#include <cstdint>
#include "AL/al.h"


class AudioBuffer
{
public:
    AudioBuffer() = default;
    AudioBuffer(ALuint _idBuffer);
    ~AudioBuffer();

private:
    ALuint idBuffer;

public:
    static AudioBuffer* Load(const char* _filename);
    uint32_t GetAlBuffer() const;

};