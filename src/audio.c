#include "fireset/audio.h"
#include "fireset/settings.h"

#include <sndfile.h>
#include <stdlib.h>
#include <stdbool.h>

static ALuint g_sources[AUDIO_MAX_SOURCES];
static int g_sourceCount = 0;

FsSound fsSoundLoad(const char* filename){
    FsSound sound = {0};
    SF_INFO info = {0};

    // opens file
    SNDFILE* file = sf_open(filename, SFM_READ, &info);
    if (!file) return sound;

    // checks channels compability
    if (info.channels != 1 && info.channels != 2) return sound;

    // fills struct
    sound.channels   = info.channels;
    sound.frames     = info.frames;
    sound.sampleRate = info.samplerate;
    sound.bps        = 16;
    sound.format = (sound.channels == 1)
        ? AL_FORMAT_MONO16
        : AL_FORMAT_STEREO16;

    // fills samples
    sound.samples = malloc(sound.frames * sound.channels * sizeof(short));
    sf_readf_short(file, sound.samples, sound.frames);
    if (!sound.samples){
        sf_close(file);
        return sound;
    }

    // generates buffer
    ALuint buffer;
    alGenBuffers(1, &buffer);
    alBufferData(
        buffer,
        sound.format,
        sound.samples,
        sound.frames * sound.channels * sizeof(short),
        sound.sampleRate
    );
    sound.buffer = buffer;

    sf_close(file);
    return sound;
}

static inline void fsAudioRegisterSource(ALuint src){
    if (g_sourceCount < AUDIO_MAX_SOURCES) g_sources[g_sourceCount++] = src;
}

void fsAudioHandle(void){
    for (int i = 0; i < g_sourceCount;){
        ALint state;
        alGetSourcei(g_sources[i], AL_SOURCE_STATE, &state);

        if (state == AL_STOPPED){
            alDeleteSources(1, &g_sources[i]);
            g_sources[i] = g_sources[--g_sourceCount];
        }else{
            i++;
        }
    }
}

void fsSoundPlayAt(FsSound* sound, FsVec2 position, int volume){
    // create source
    ALuint src;
    alGenSources(1, &src);
    alSourcei(src, AL_BUFFER, sound->buffer);
    alSourcei(src, AL_SOURCE_RELATIVE, AL_FALSE);

    // attenuation
    alSourcef(src, AL_REFERENCE_DISTANCE, AUDIO_FULL_VOLUME_DISTANCE * volume);
    alSourcef(src, AL_ROLLOFF_FACTOR, AUDIO_DECAY_FACTOR / volume);

    // position
    alSource3f(src, AL_POSITION, position.x, position.y, 0);

    // registers source
    fsAudioRegisterSource(src);

    // plays audio
    alSourcePlay(src);
}

void fsSoundFree(FsSound* sound){
    if (!sound) return;
    free(sound->samples);
    sound->samples = NULL;
    sound->channels = 0;
    sound->sampleRate = 0;
    sound->frames = 0;
    sound->bps = 0;
}