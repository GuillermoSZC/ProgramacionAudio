#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"


#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#include <iostream>
#include <glfw3.h>
#include <sstream>
#include <vector>

#include <fstream>     
#include <iterator>

int main()
{
    ALCdevice* device = alcOpenDevice(nullptr);
    ALCcontext* context = nullptr;
    if (device)
    {
        context = alcCreateContext(device, nullptr);
        alcMakeContextCurrent(context);
    }
    else
    {
        printf("Device not found..\n");
    }




    alcDestroyContext(context);
    alcCloseDevice(device);
    return 0;
}
