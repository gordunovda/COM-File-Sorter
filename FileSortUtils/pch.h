// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

#define FSC_UPDATE_TIMEOUT 200
#define MAX_PATH 256
#define WM_USER_UPDATE_TASK WM_USER+1000
#define WM_USER_UPDATE_PROGRESS WM_USER+1001
#define WM_USER_FINISH_TASKS WM_USER+1002

#endif //PCH_H
