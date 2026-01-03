#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include "fireset/vertex.h"

typedef struct{
    int channels;
    int sampleRate;
    int bps;
    int frames;
    short* samples;
    ALenum format;
    ALuint buffer;
}FsSound;

typedef struct{
    ALuint* handle;
    FsVec2 position;
}FsSoundSource;

FsSound fsSoundLoad(const char* filename);
void fsSoundPlay(const FsSound* sound, const FsSoundSource* source, int volume);
void fsSoundFree(FsSound* sound);