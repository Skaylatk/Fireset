// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#define VERSION "v0.3.0"

#define STB_IMAGE_IMPLEMENTATION
#include "fireset/stb_image.h"

#include "fireset/core.h"
#include "fireset/fstime.h"
#include "fireset/fslog.h"

#include <AL/al.h>
#include <AL/alc.h>

static ALCdevice* g_device = NULL;
static ALCcontext* g_context = NULL;

bool fsInit(void){
    fsTimeInit();
    fsLogInit();

    fsLog(FS_INFO, FS_CORE, "Logging system initialized");

    if(!glfwInit()){
        fsLog(FS_ERROR, FS_WINDOW, "Cannot initialize GLFW");
        return false;
    }

    fsLog(FS_INFO, FS_WINDOW, "Window & Input backend (GLFW) initialized");

    g_device = alcOpenDevice(NULL);
    if (!g_device){
        fsLog(FS_ERROR, FS_AUDIO, "Cannot open OpenAL device");
        return false;
    }

    g_context = alcCreateContext(g_device, NULL);
    if (!g_context){
        alcCloseDevice(g_device);
        fsLog(FS_ERROR, FS_AUDIO, "Cannot create OpenAL context");
        return false;
    }

    alcMakeContextCurrent(g_context);
    alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);

    fsLog(FS_INFO, FS_AUDIO, "Audio backend (OpenAL) initialized");

    fsLog(FS_INFO, FS_CORE, "Fireset Engine %s initialized", VERSION);
    return true;
}

void fsExit(void){
    if(g_context) {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(g_context);
        g_context = NULL;
    }

    if(g_device) {
        alcCloseDevice(g_device);
        g_device = NULL;
    }

    alcMakeContextCurrent(NULL);
    
    glfwTerminate();

    fsLog(FS_INFO, FS_CORE, "Engine shutdown");
}