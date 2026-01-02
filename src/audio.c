#include "fireset/audio.h"

#include <sndfile.h>
#include <stdlib.h>

FsSound fsSoundLoad(const char* filename){
    FsSound sound = {0};
    SF_INFO info;

    // opens file
    SNDFILE* file = sf_open(filename, SFM_READ, &info);
    if (!file) return sound;

    // fills sound struct
    sound.channels = info.channels;
    sound.frames = info.frames;
    sound.sampleRate = info.samplerate;
    sound.buffer = (float*)malloc(info.frames * info.channels * sizeof(float));
    if (!sound.buffer){
        sf_close(file);
        return sound;
    }

    // fills buffer
    sf_readf_float(file, sound.buffer, info.frames);
    sf_close(file);

    return sound;
}

void fsSoundFree(FsSound* sound){
    if (!sound) return;
    free(sound->buffer);
    sound->buffer = NULL;
    sound->channels = 0;
    sound->sampleRate = 0;
    sound->frames = 0;
}