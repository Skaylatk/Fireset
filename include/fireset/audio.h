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
    ALuint handle;
    FsVec2 position;
    bool looping;
    bool playing;
}FsSoundSource;

FsSound fsSoundLoad(const char* filename);
void fsSoundFree(FsSound* sound);
void fsSoundSourcePlay(FsSound* sound, FsSoundSource* source, int volume);
void fsSoundSourceStop(FsSoundSource* source);
void fsSoundSourceFree(FsSoundSource* source);
void fsSoundSourceHandle(int count, FsSoundSource* sources);
FsSoundSource fsSoundSourceCreate(FsVec2 position, bool looping);