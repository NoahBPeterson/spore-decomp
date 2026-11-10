// Slice s0129e170: initialize small float vectors in globals.
// Flags: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast /GS-
#include "types.h"

extern float g_1485720;  // 0x01485720 = 1.0f

extern float g_15f3990, g_15f3994, g_15f3998, g_15f399c;
extern float g_15f38dc, g_15f38e0, g_15f38e4, g_15f38e8;
extern float g_15f39a0, g_15f39a4, g_15f39a8, g_15f39ac;
extern float g_15f387c, g_15f3880, g_15f3884, g_15f3888;

// @ 0x0129e170
void FUN_0129e170()
{
    g_15f3990 = 0.0f;
    g_15f3994 = 0.0f;
    g_15f3998 = 0.0f;
    g_15f399c = 0.0f;
}

// @ 0x0129e0e0
void FUN_0129e0e0()
{
    g_15f38dc = 0.0f;
    g_15f38e0 = g_1485720;
    g_15f38e4 = 0.0f;
    g_15f38e8 = 0.0f;
}

// @ 0x0129e110
void FUN_0129e110()
{
    g_15f39a0 = 0.0f;
    g_15f39a4 = 0.0f;
    g_15f39a8 = g_1485720;
    g_15f39ac = 0.0f;
}

// @ 0x0129e140
void FUN_0129e140()
{
    g_15f387c = 0.0f;
    g_15f3880 = 0.0f;
    g_15f3884 = 0.0f;
    g_15f3888 = g_1485720;
}
