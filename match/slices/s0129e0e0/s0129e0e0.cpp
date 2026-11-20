// @ 0x0129e0e0
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_15f38dc[];

#include "types.h"

// Static initialiser of a four-float global record at 0x015f38dc:
// { 0.0f, 1.0f, 0.0f, 0.0f }; the y constant is loaded from .rdata at 0x01485720.

struct S0129e0e0_Record
{
    float x;    // 0x015f38dc
    float y;    // 0x015f38e0
    float z;    // 0x015f38e4
    float w;    // 0x015f38e8
};

S0129e0e0_Record* const g_p15f38dc = (S0129e0e0_Record*)g_15f38dc;

void FUN_0129e0e0()
{
    g_p15f38dc->x = 0.0f;
    g_p15f38dc->y = 1.0f;
    g_p15f38dc->z = 0.0f;
    g_p15f38dc->w = 0.0f;
}
