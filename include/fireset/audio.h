#pragma once

typedef struct{
    int channels;
    int sampleRate;
    int frames;
    float* buffer;
}FsSound;

FsSound fsSoundLoad(const char* filename);
void fsSoundFree(FsSound* sound);