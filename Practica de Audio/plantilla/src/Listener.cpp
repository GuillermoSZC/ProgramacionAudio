#include "Listener.h"
#include "AL/al.h"

Listener* Listener::instance = nullptr;

Listener::Listener()
{
    alListener3f(AL_POSITION, 0.f, 0.f, 0.f);
    alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f);
    alListener3f(AL_ORIENTATION, 0.f, 0.f, 0.f);
}

Listener* Listener::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Listener();
    }
    return instance;
}

void Listener::SetListenerPosition(float _x, float _y, float _z)
{
    alListener3f(AL_POSITION, _x, _y, _z);
}

void Listener::SetListenerVelocity(float _x, float _y, float _z)
{
    alListener3f(AL_VELOCITY, _x, _y, _z);
}

void Listener::SetListenerOrientation(float _x, float _y, float _z)
{
    alListener3f(AL_ORIENTATION, _x, _y, _z);
}
