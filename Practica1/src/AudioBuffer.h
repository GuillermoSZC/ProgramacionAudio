#pragma once
#include <stdint.h>
#include <iostream>

class AudioBuffer
{
public:
    AudioBuffer(AudioBuffer* _buffer);
    ~AudioBuffer() { printf("AudioBuffer object deleted.\n"); }

private:
    AudioBuffer* buffer;
    float pitch, gain;
    bool loop;
    float x, y, z;

public:
    void SetPitch(float _pitch);
    void SetGain(float _gain);
    void SetLooping(bool _loop);
    void SetPosition(float _x, float _y, float _z);
    void SetVelocity(float _x, float _y, float _z);

    void Play();
    void Stop();
    void Pause();
    void IsPlaying() const;

public:
    static AudioBuffer* Load(const char* _filename)
    {
        AudioBuffer* foo = nullptr;
        return foo;
    }

    uint32_t GetAlBuffer() const   
    {
        return 0;
    }

};