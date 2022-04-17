#include "AudioBuffer.h"
#include <iostream>


#define REPEAT(x) for(int i = x; i--;)

AudioBuffer::AudioBuffer(ALuint _idBuffer)
{
    idBuffer = _idBuffer;
}

AudioBuffer::~AudioBuffer()
{
    alDeleteBuffers(1, &idBuffer);
}

AudioBuffer* AudioBuffer::Load(const char* _filename)
{
    ALuint alBuffer = NULL;

    alGenBuffers(1, &alBuffer);
    if (alGetError() != AL_NO_ERROR)
    {
        printf("Generate buffer error.\n");
        return nullptr;
    }

    FILE* file = fopen(_filename, "r");
    if (!file)
    {
        printf("Can't open file\n");
        return nullptr;
    }

    char cBuffer[5] = "";
    fread(cBuffer, sizeof(char), 4, file);
    if (strcmp(cBuffer, "RIFF") != 0) // ChunkID
    {
        printf("wav not found - file: %s\n", _filename);
        return nullptr;
    }

    REPEAT(3)
    {
        fread(cBuffer, sizeof(char), 4, file);
    }

    fread(cBuffer, sizeof(char), 4, file);
    int chunkSize = cBuffer[3] << 24 | cBuffer[2] << 16 | cBuffer[1] << 8 | cBuffer[0];

    fread(cBuffer, sizeof(char), 2, file);
    int audioFormat = cBuffer[1] << 8 | cBuffer[0];

    fread(cBuffer, sizeof(char), 2, file);
    int channels = cBuffer[1] << 8 | cBuffer[0];

    fread(cBuffer, sizeof(char), 4, file);
    ALsizei sampleRate = cBuffer[3] << 24 | cBuffer[2] << 16 | cBuffer[1] << 8 | cBuffer[0];

    fread(cBuffer, sizeof(char), 4, file);
    fread(cBuffer, sizeof(char), 2, file);

    fread(cBuffer, sizeof(char), 2, file);
    int sampleBits = cBuffer[1] << 8 | cBuffer[0];

    if (chunkSize > 16 && audioFormat != 1)
    {
        fread(cBuffer, sizeof(char), 2, file);
        int  extraParamsSize = cBuffer[1] << 8 | cBuffer[0];
        fread(cBuffer, sizeof(char), extraParamsSize, file);
    }

    bool val = false;
    while (!val)
    {
        fread(cBuffer, sizeof(char), 1, file);
        if (strcmp(cBuffer, "d") == 0)
        {
            fread(cBuffer, sizeof(char), 1, file);
            if (strcmp(cBuffer, "a") == 0)
            {
                fread(cBuffer, sizeof(char), 1, file);
                if (strcmp(cBuffer, "t") == 0)
                {
                    fread(cBuffer, sizeof(char), 1, file);
                    if (strcmp(cBuffer, "a") == 0)
                    {
                        val = true;
                    }
                }
            }
        }
    }

    fread(cBuffer, sizeof(char), 4, file);
    unsigned int dataSize =
        static_cast<unsigned char>(cBuffer[3]) << 24 |
        static_cast<unsigned char>(cBuffer[2]) << 16 |
        static_cast<unsigned char>(cBuffer[1]) << 8 |
        static_cast<unsigned char>(cBuffer[0]);

    char* data = new char[dataSize];

    fread(data, sizeof(char), dataSize, file);

    ALenum alEnumBuffer = AL_FORMAT_MONO8;
    if (sampleBits == 8)
    {
        alEnumBuffer = (channels == 1) ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8;
    }
    else if (sampleBits == 16)
    {
        alEnumBuffer = (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    }

    alBufferData(alBuffer, alEnumBuffer, data, dataSize, sampleRate);

    delete[] data;
    fclose(file);

    return new AudioBuffer(alBuffer);
}


uint32_t AudioBuffer::GetAlBuffer() const
{
    return idBuffer;
}