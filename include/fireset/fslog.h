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

static const char* FS_ERROR_STRING[FS_SEV_COUNT] = {
    "INFO",
    "WARNING",
    "ERROR",
    "FATAL"
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

#include <stdarg.h>
#include <stdio.h>

static inline void fsLog(FS_SEVERITY sev, const char* fmt, ...){
    if (sev < 0 || sev >= FS_SEV_COUNT)
        sev = FS_ERROR;

    int total = (int)(fsTimeGetTime());

    int h = total / 3600;
    int m = (total % 3600) / 60;
    int s = total % 60;

    printf(
        "[ Fireset %02d:%02d:%02d ] ( %s%s\033[0m ) ",
        h, m, s,
        FS_ERROR_COLOR[sev],
        FS_ERROR_STRING[sev]
    );

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    printf("\n");
    fflush(stdout);

    if (sev == FS_FATAL) exit(EXIT_FAILURE);
}