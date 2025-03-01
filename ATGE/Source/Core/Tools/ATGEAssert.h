#pragma once

#ifdef _WIN32
#include <windows.h>
#define DEBUG_BREAK() __debugbreak()
#else
#include <signal.h>
#define DEBUG_BREAK() raise(SIGTRAP) // Works on Linux/macOS
#endif

#include "ATGELogger.h"

#define ATGE_ASSERTIONS_ENABLED

#ifdef ATGE_ASSERTIONS_ENABLED
#define ATGE_ASSERT(condition)                                                    \
{                                                                                 \
    if (condition) {                                                              \
    }                                                                             \
    else {                                                                        \
        ATGE::Logger::reportAssertFailure(#condition, "", __FILE__, __LINE__);    \
    }                                                                             \
                                                                                  \
}                                                                                 \

#define ATGE_ASSERT_MSG(condition, message) \
{                                                                                 \
    if (condition) {                                                              \
    }                                                                             \
    else {                                                                        \
        ATGE::Logger::reportAssertFailure(#condition, message, __FILE__, __LINE__);  \
    }                                                                             \
                                                                                  \
}      

#ifdef _DEBUG

#define ATGE_ASSERT_DEBUG(condition)                                              \
{                                                                                 \
    if (condition) {                                                              \
    }                                                                             \
    else {                                                                        \
        ATGE::Logger::reportAssertFailure(#condition, "", __FILE__, __LINE__);  \
    }                                                                             \
                                                                                  \
}                                                                                 \

#else

#define ATGE_ASSERT_DEBUG(condition) ((void)0)

#endif

#else

#define ATGE_ASSERT(condition) ((void)0)
#define ATGE_ASSERT_MSG(condition, message) ((void)0)

#endif
