// Copyright (c) 2025 Henrique Rodrigues Santos
// Licensed under the MIT License
// Repo: https://github.com/saintsHr/Fireset

#define _POSIX_C_SOURCE 199309L

#include "fireset/fstime.h"
#include <stdint.h>

static double s_start_time = 0.0;
static double s_last_time  = 0.0;

#if defined(_WIN32)

#include <windows.h>

double fsTimeGetSystemTime(void){
    static LARGE_INTEGER freq;
    static int initialized = 0;

    if (!initialized){
        QueryPerformanceFrequency(&freq);
        initialized = 1;
    }

    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);

    return (double)counter.QuadPart / (double)freq.QuadPart;
}

#elif defined(__APPLE__)

#include <mach/mach_time.h>

double fsTimeGetSystemTime(void){
    static mach_timebase_info_data_t timebase;
    static int initialized = 0;

    if (!initialized){
        mach_timebase_info(&timebase);
        initialized = 1;
    }

    uint64_t t = mach_absolute_time();

    return (double)t * (double)timebase.numer / (double)timebase.denom * 1e-9;
}

#elif defined(__linux__)

#include <time.h>

double fsTimeGetSystemTime(void){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

#else
    #error "OS not supported"
#endif

void fsTimeInit(void){
    double now = fsTimeGetSystemTime();
    s_start_time = now;
    s_last_time  = now;
}

double fsTimeGetTime(void){
    return fsTimeGetSystemTime() - s_start_time;
}

double fsTimeGetDelta(void){
    double now = fsTimeGetSystemTime();
    double dt = now - s_last_time;
    s_last_time = now;
    return dt;
}

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#include <errno.h>
#endif

void fsWait(unsigned long ms){
#ifdef _WIN32
    Sleep(ms);
#else
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000L;

    while (nanosleep(&ts, &ts) == -1 && errno == EINTR);
#endif
}