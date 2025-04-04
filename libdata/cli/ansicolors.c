#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>

#include "ansicolors.h"

#ifdef _WIN32
// Some old MinGW/CYGWIN distributions don't define this:
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

static HANDLE stdoutHandle;
static DWORD  outModeInit;

void ansi_setup(void) {
    DWORD outMode = 0;
    stdoutHandle  = GetStdHandle(STD_OUTPUT_HANDLE);

    if (stdoutHandle == INVALID_HANDLE_VALUE)
        exit(GetLastError());

    if (!GetConsoleMode(stdoutHandle, &outMode))
        exit(GetLastError());

    outModeInit = outMode;

    // Enable ANSI escape codes
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if (!SetConsoleMode(stdoutHandle, outMode))
        exit(GetLastError());
}

void ansi_restore(void) {
    printf(RESET_TEXT);

    // Reset console mode
    if (!SetConsoleMode(stdoutHandle, outModeInit))
        exit(GetLastError());
}
#else
void ansi_setup(void) {}

void ansi_restore(void) {
    printf(RESET_TEXT);
}
#endif
