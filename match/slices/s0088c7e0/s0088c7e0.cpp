// Slice s0088c7e0 -- constructor of an 0x80-byte render object.
//
//  0x0088c7e0  Obj0088c7e0::Obj0088c7e0(): zeroes the header fields, seeds the float
//              defaults from 0x13f0e84 / 0x1485720, sets the two -1 ids, the
//              0xff000000 colour word and the byte at +0x7c, then initialises the
//              sub-object that starts at +0x80 (0x88c050).
#include "types.h"

// compile with /O2 /MD /Gy /TP /arch:SSE /fp:fast

extern float g_f_13f0e84;      // 0x13f0e84
extern float g_f_1485720;      // 0x1485720

struct Sub0088c7e0 {
    char  mData[8];            // +0x00
    void  Init();              // 0x88c050
};

struct Obj0088c7e0 {
    void* mp0;                 // +0x00
    void* mp4;                 // +0x04
    short m8;                  // +0x08
    char  pad_0a[0x48 - 0x0a];
    float mf48;                // +0x48
    int   m4c;                 // +0x4c
    float mf50;                // +0x50
    float mf54;                // +0x54
    int   m58;                 // +0x58
    int   m5c;                 // +0x5c
    int   m60;                 // +0x60
    int   m64;                 // +0x64
    float mf68;                // +0x68
    float mf6c;                // +0x6c
    int   m70;                 // +0x70
    int   m74;                 // +0x74
    int   m78;                 // +0x78
    char  m7c;                 // +0x7c
    char  pad_7d[0x80 - 0x7d];
    Sub0088c7e0 mSub80;        // +0x80

    Obj0088c7e0();
};

// @ 0x0088c7e0
Obj0088c7e0::Obj0088c7e0()
{
    mp0 = 0;
    mp4 = 0;
    mf48 = 0.0f;
    mf50 = g_f_13f0e84;
    m70 = -1;
    m78 = -1;
    m8 = 0;
    m4c = 0;
    mf54 = g_f_1485720;
    m58 = 0;
    m5c = 0;
    m60 = 0;
    m64 = 0;
    mf68 = g_f_1485720;
    mf6c = g_f_1485720;
    m74 = 0xff000000;
    m7c = 0;
    mSub80.Init();
}
