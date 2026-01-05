// Copyright (c) 2025 Henrique Rodrigues Santos
// Licensed under the MIT License
// Repo: https://github.com/saintsHr/Fireset

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "fireset/fstime.h"

static double s_log_start_time = 0.0;

typedef enum{
    FS_INFO,
    FS_WARNING,
    FS_ERROR,
    FS_FATAL,

    FS_SEV_COUNT
}FS_SEVERITY;

typedef enum{
    FS_AUDIO,
    FS_CORE,
    FS_TIME,
    FS_ASSETS,
    FS_INPUT,
    FS_RENDER,
    FS_WINDOW,

    FS_MOD_COUNT
}FS_MODULE;

static const char* FS_ERROR_STRING[FS_SEV_COUNT] = {
    "INFO",
    "WARNING",
    "ERROR",
    "FATAL"
};

static const char* FS_MODULE_STRING[FS_MOD_COUNT] = {
    "Audio",
    "Core",
    "Time",
    "Assets",
    "Input",
    "Render",
    "Window"
};

static const char* FS_ERROR_COLOR[FS_SEV_COUNT] = {
    "\033[96m",
    "\033[95m",
    "\033[91m",
    "\033[31m"
};

static inline void fsLogInit(void){
    s_log_start_time = fsTimeGetSystemTime();
}

static inline void fsLog(FS_SEVERITY sev, FS_MODULE mod, const char* fmt, ...){
    if (sev < 0 || sev >= FS_SEV_COUNT) return;
    if (mod < 0 || mod >= FS_MOD_COUNT) return;

    double time = fsTimeGetTime();

    long long totalMs = (long long)(time * 1000.0);

    int ms = totalMs % 1000;
    int totalSeconds = totalMs / 1000;

    int s = totalSeconds % 60;
    int m = (totalSeconds / 60) % 60;
    int h = totalSeconds / 3600;

    printf(
        "[%02d:%02d:%02d.%03d][%s%s\033[0m][%s] ",
        h, m, s, ms,
        FS_ERROR_COLOR[sev],
        FS_ERROR_STRING[sev],
        FS_MODULE_STRING[mod]
    );

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    printf("\n");
    fflush(stdout);

    if (sev == FS_FATAL) exit(EXIT_FAILURE);
}