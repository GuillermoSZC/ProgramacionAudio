#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"


#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#include <glfw3.h>
#include <sstream>
#include <vector>
#include <litegfx.h>

#include <fstream>     
#include <iterator>

#include "AudioBuffer.h"
#include "AudioSource.h"
#include "Listener.h"


int main() {
#pragma region VARIABLES
    Listener* listener = Listener::GetInstance();

    int widthScreen = 1080;
    int heightScreen = 960;
    double deltaTime = 0, lastTime = 0, updateTime = glfwGetTime();
    const float pitch = 0.01f;
    const float position = 0.1f;
    float x = 0.f, y = 0.f, z = 0.f;
    bool doOnce = false;
    bool doOnceSupp = false;

#pragma endregion

    ALCdevice* device = alcOpenDevice(nullptr);
    if (!device)
    {
        printf("Error trying to init device.\n");
        return 1;
    }
    ALCcontext* context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(widthScreen, heightScreen, "Practica 1 - Sonido ", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    lgfx_setup2d(widthScreen, heightScreen);

    auto aBuffer = AudioBuffer::Load("data/music.wav");
    auto aSource = new AudioSource(aBuffer);

    aSource->Play();

    while (!glfwWindowShouldClose(window)) // ~ Game loop
    {
        lgfx_clearcolorbuffer(0, 0, 0);

        lastTime = updateTime;
        updateTime = glfwGetTime();
        deltaTime = updateTime - lastTime;

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            aSource->UpdatePosition(x, y, z);
            aSource->SetPosition(x - position, y, z);
        }
        else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            aSource->UpdatePosition(x, y, z);
            aSource->SetPosition(x + position, y, z);
        }
        else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            aSource->SetPitch(aSource->UpdatePitch() - pitch);
        }
        else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            aSource->SetPitch(aSource->UpdatePitch() + pitch);
        }
        doOnceSupp = glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS; // P key to pause and resume the song
        if (!doOnce && doOnceSupp) // this condition is for exec only once time the input action
        {
            if (aSource->IsPlaying())
            {
                aSource->Pause();
            }
            else
            {
                aSource->Play();
            }
        }
        doOnce = doOnceSupp;

        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) // X key to stop the song
        {
            aSource->Stop();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    aSource->Stop();
    glfwTerminate();

#pragma region GARBAGE_COLLECTOR
    delete aSource;
    context = alcGetCurrentContext();
    device = alcGetContextsDevice(context);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
#pragma endregion

    return 0;
}
