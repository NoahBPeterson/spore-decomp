// src/game/SPEngine/SPAppCertStore.cpp -- migrated from slice(s) s007c77e0, s007c6750 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppCertStore.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCameraManager.h"
#include "EA/ArgScript/cIFileParser.h"
#include "SP/cConfigManager.h"
#include "SP/cConfigScriptState.h"
#include "SP/cOption.h"

// unnamed retail callees and globals (address in the comment)
extern char UNK_01410e24[];

// ---- items of slice s007c6750 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
extern char UNK_01410e24[];
struct cBitLength {
    int pad0;
    int mValue;      // +0x04
    u32 mMask;       // +0x08
    int pad0c;
    u32 mTableA;     // +0x10
    u32 mTableB;     // +0x14
    int mLimit;      // +0x18
    void BitLengthInit(int value, u32 mask);
};
// ---- items of slice s007c6750 end

// ---- items of slice s007c77e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint8_t g_randomData[];  // 0x01410708
extern const uint32_t g_BitLengthTable[];   // 0x01410e24
uint32_t __cdecl FNVHash(const char* p, uint32_t hash, int ignore);              // 0x00932e80
struct cRandom {
    char pad0[4];
    const uint8_t* mData;   // +0x04
    uint32_t mSize;         // +0x08
    uint32_t mPos;          // +0x0c
    uint32_t mPoly;         // +0x10
    uint32_t mState;        // +0x14
    uint32_t mMask;         // +0x18

    void Init(const uint8_t* data, uint32_t size);  // 0x007c7770
    bool Seed(const char* name);                    // 0x007c77e0
    int  Mode();                                    // 0x007c78c0
    int  Query(int which);                          // 0x007c78e0
    int  Read(void* dst, int n);                    // 0x007c7910
    bool Reset();                                   // 0x007c7980
};
extern cRandom g_random;    // 0x0153cf9c
// ---- items of slice s007c77e0 end

// @ 0x007c7770
void cBitLength::BitLengthInit(int value, u32 mask)
{
    mValue = value;
    mMask = mask;
    int bits = 0;
    if (mask & 0xffff0000) { bits = 0x10; mask >>= 16; }
    if (mask & 0xff00)     { bits += 8;  mask >>= 8; }
    if (mask & 0xf0)       { bits += 4; }
    if (mask & 0xc)        { bits += 2; }
    if (mask & 2)          { bits += 1; }
    u32 v = *(u32*)(UNK_01410e24 + bits * 4);
    mTableA = v;
    mTableB = v;
    mLimit = (1 << ((char)bits + 1 & 0x1f)) + -1;
}

// @ 0x007c77e0
bool cRandom::Seed(const char* name)
{
    if (mData != 0) {
        uint32_t v = mSize;
        int n = 0;
        if (v & 0xffff0000u) { n = 0x10; v >>= 0x10; }
        if (v & 0xff00u)     { n += 8;   v >>= 8; }
        if (v & 0xf0u)       { n += 4;   v >>= 4; }
        if (v & 0xcu)        { n += 2;   v >>= 2; }
        if (v & 2u)          { n += 1; }
        uint32_t p = g_BitLengthTable[n];
        int m = ++n;
        mPoly  = p;
        mState = p;
        mMask  = (1u << m) - 1;
        uint32_t h = FNVHash(name, 0x811c9dc5u, 0);
        mState = mMask & h;
        mPos   = 0;
        return true;
    }
    return false;
}

// @ 0x007c7870
cRandom* __stdcall GetRandom(const char* name, int, int)
{
    g_random.Init(g_randomData, 0x6d5);
    g_random.Seed(name);
    return &g_random;
}
