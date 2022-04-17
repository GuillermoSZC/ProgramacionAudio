#pragma once
#include "AL/al.h"


class AudioBuffer;

class AudioSource
{
public:
    AudioSource() = default;
    AudioSource(AudioBuffer* _buffer);
    ~AudioSource();

private:
    ALuint idSource;
    ALfloat pitch;
    ALint isPlaying;

public:
    void SetPitch(float _pitch);
    void SetGain(float _gain);
    void SetLooping(bool _loop);
    void SetPosition(float _x, float _y, float _z);
    void SetVelocity(float _x, float _y, float _z);

    void Play();
    void Stop();
    void Pause();
    bool IsPlaying() const;
    void UpdatePosition(float& _x, float& _y, float& _z);
    float UpdatePitch();
};