#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"


#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#define PI 3.14159265359

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

    int widthScreen = 1280;
    int heightScreen = 960;
    const float pitch = 0.01f;
    const float position = 0.1f;
    float xListenerPosition = widthScreen * 0.5f, yListenerPosition = 800.f;
    float deltaTime = 0.f, currentTime = 0.f, lastTime = 0.f;
    float x = 0.f, y = 0.f, z = 0.f;
    float audioSourceMovement = 0.f;
    float xPosition = 0.f, yPosition = 0.f;
    float limitMovement = 150.f;
    float speed = 2.f;
    float distanceTo = 260.f;
    float rectSize = 20.f;
    float angle = 0.f;
    bool doOnce = false;
    bool doOnceSupp = false;

#pragma endregion

    ALCdevice* device = alcOpenDevice(nullptr);
    if (!device)
    {
        printf("Error trying to init device.\n");
        return -1;
    }
    ALCcontext* context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);

    if (!glfwInit())
    {
        printf("Can't init GLFW.\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(widthScreen, heightScreen, "Practica 1 - Sonido ", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    lgfx_setup2d(widthScreen, heightScreen);

    auto aBuffer = AudioBuffer::Load("data/music.wav");
    auto aSource = new AudioSource(aBuffer);

    aSource->Play();

    while (!glfwWindowShouldClose(window)) // ~ Game loop
    {
        lgfx_clearcolorbuffer(0, 0, 0);

        currentTime = (float)glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            aSource->UpdatePosition(x, y, z);
            aSource->SetPosition(x - position, y, z);
            if (xListenerPosition > widthScreen * 0.5f - limitMovement)
            {
                xListenerPosition -= 6.f;
            }
        }
        else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            aSource->UpdatePosition(x, y, z);
            aSource->SetPosition(x + position, y, z);
            if (xListenerPosition < widthScreen * 0.5f + limitMovement)
            {
                xListenerPosition += 6.f;
            }
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

        audioSourceMovement += 0.1f * (float)deltaTime;

        lgfx_setcolor(1.f, 1.f, 1.f, 0.f);
        lgfx_drawoval(xListenerPosition, yListenerPosition, 25.f, 25.f);

        angle = 32.f * ((float)PI / 180.f);
        xPosition = widthScreen * 0.5f;
        yPosition = heightScreen * 0.5f;
        xPosition = xPosition + (float)cos(angle * glfwGetTime() * speed) * distanceTo;
        yPosition = yPosition + (float)sin(angle * glfwGetTime() * speed) * distanceTo;

        lgfx_setcolor(1.f, 0.f, 0.f, 0.f);
        lgfx_drawrect(xPosition, yPosition, rectSize, rectSize);

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
