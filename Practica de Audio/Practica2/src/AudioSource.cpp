#include "AudioBuffer.h"
#include "AudioSource.h"
#include <iostream>

AudioSource::AudioSource(AudioBuffer* _buffer) : isPlaying(0), pitch(0.f)
{
    alGenSources(1, &idSource);
    if (alGetError() != AL_NO_ERROR)
    {
        printf("Constructor ERROR.\n");
        return;
    }

    alSourcei(idSource, AL_LOOPING, 0);
    alSourcef(idSource, AL_PITCH, 1.f);
    alSourcef(idSource, AL_GAIN, 1.f);
    alSource3f(idSource, AL_POSITION, 0.f, 0.f, 0.f);
    alSource3f(idSource, AL_VELOCITY, 0.f, 0.f, 0.f);
    alSourcei(idSource, AL_BUFFER, _buffer->GetAlBuffer());
}

AudioSource::~AudioSource()
{
    alDeleteSources(1, &idSource);
}

#pragma region SETTERS
void AudioSource::SetPitch(float _pitch)
{
    alSourcef(idSource, AL_PITCH, _pitch);
}

void AudioSource::SetGain(float _gain)
{
    alSourcef(idSource, AL_GAIN, _gain);
}

void AudioSource::SetLooping(bool _loop)
{
    alSourcei(idSource, AL_LOOPING, (_loop) ? 1 : 0);
}

void AudioSource::SetPosition(float _x, float _y, float _z)
{
    alSource3f(idSource, AL_POSITION, _x, _y, _z);
}

void AudioSource::SetVelocity(float _x, float _y, float _z)
{
    alSource3f(idSource, AL_VELOCITY, _x, _y, _z);
}
#pragma endregion

#pragma region CLASS_FUNCTIONS
void AudioSource::Play()
{
    isPlaying = 1;
    alSourcePlay(idSource);
}

void AudioSource::Stop()
{
    isPlaying = 0;
    alSourceStop(idSource);
}

void AudioSource::Pause()
{
    isPlaying = 0;
    alSourcePause(idSource);
}

bool AudioSource::IsPlaying() const
{
    alGetSourcei(idSource, AL_PLAYING, const_cast<ALint*>(&isPlaying));
    return (isPlaying == 0) ? false : true;
}

void AudioSource::UpdatePosition(float& _x, float& _y, float& _z)
{
    alGetSource3f(idSource, AL_POSITION, &_x, &_y, &_z);
}

float AudioSource::UpdatePitch()
{
    alGetSourcef(idSource, AL_PITCH, &pitch);
    return pitch;
}
#pragma endregion