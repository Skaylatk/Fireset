#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include "fireset/vertex.h"

typedef enum{
    FS_MONO,

}FS_AUDIO_FORMAT;

typedef struct{
    int channels;
    int sampleRate;
    int bps;
    int frames;
    short* samples;
    bool playing;
    ALenum format;
    ALuint buffer;
}FsSound;

FsSound fsSoundLoad(const char* filename);
void fsSoundPlayAt(FsSound* sound, FsVec2 position, int volume);
void fsAudioHandle(void);
void fsSoundFree(FsSound* sound);