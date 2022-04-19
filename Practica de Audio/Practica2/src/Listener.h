#pragma once
#include <iostream>
#include <Math.h>

class Listener
{
private:
    static Listener* instance;
    Listener();

public:
    static Listener* GetInstance();

public:
    void SetListenerPosition(float _x, float _y, float _z);
    void SetListenerVelocity(float _x, float _y, float _z);
    void SetListenerOrientation(float _x, float _y, float _z);

};