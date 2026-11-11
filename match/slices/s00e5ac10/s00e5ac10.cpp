// Slice s00e5ac10 -- SPGonzago cell-game object update: ease a cached position
// toward a target and push it to the creature animation controller.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// ---- globals ---------------------------------------------------------------
extern void* g_16b3c04;                        // 0x016b3c04 (cCellGame*)
extern void* g_16b3c08;                        // 0x016b3c08
extern const float g_1488874[];                // 0x01488874 (ease factor)
#define kEase g_1488874[0]

// ---- callees ---------------------------------------------------------------
struct Table_00b72210 {
    void* At(unsigned int id);                 // 0x00b72210 (thiscall, ret 4)
};

struct Controller_00a02bf0 {
    void SetMode(const int* mode, char a);     // 0x00a02bf0 (thiscall, ret 8)
};

struct Vec3_00e5ac10 {
    float x, y, z;
};
inline Vec3_00e5ac10 operator-(const Vec3_00e5ac10& a, const Vec3_00e5ac10& b)
{
    Vec3_00e5ac10 r = { a.x - b.x, a.y - b.y, a.z - b.z };
    return r;
}
inline Vec3_00e5ac10 operator*(const Vec3_00e5ac10& a, float s)
{
    Vec3_00e5ac10 r = { a.x * s, a.y * s, a.z * s };
    return r;
}
inline Vec3_00e5ac10 operator+(const Vec3_00e5ac10& a, const Vec3_00e5ac10& b)
{
    Vec3_00e5ac10 r = { a.x + b.x, a.y + b.y, a.z + b.z };
    return r;
}

struct CellObj_00e5ac10 {
    char    pad_000[0xfc];                     // +0x000 .. +0xfb
    int     mfc;                               // +0x0fc
    char    pad_100[0x12c - 0x100];            // +0x100 .. +0x12b
    Vec3_00e5ac10 mTarget;                     // +0x12c
    Vec3_00e5ac10 mCurrent;                    // +0x138
    char    pad_144[0x248 - 0x144];            // +0x144 .. +0x247
    void*   m248;                              // +0x248
    char    pad_24c[0x35c - 0x24c];            // +0x24c .. +0x35b
    int     m35c;                              // +0x35c
};

struct CellGame_00e5ac10 {
    char    pad_000[0x4100];                   // +0x0000 .. +0x40ff
    int     m4100;                             // +0x4100
};

// @ 0x00e5ac10
void __cdecl FUN_00e5ac10(CellObj_00e5ac10* obj)
{
    if (obj->m35c == ((CellGame_00e5ac10*)g_16b3c04)->m4100 || obj->mfc == 0)
        return;

    float f = kEase;
    Vec3_00e5ac10 d = (obj->mTarget - obj->mCurrent) * f;
    Vec3_00e5ac10& cur = obj->mCurrent;
    cur.x += d.x;
    cur.y += d.y;
    cur.z += d.z;

    if (obj->m248 != 0 && obj->mfc != 0) {
        Table_00b72210* table = (Table_00b72210*)((char*)g_16b3c08 + 0x168);
        char* p = (char*)table->At((unsigned int)obj->m248);
        Controller_00a02bf0* c = *(Controller_00a02bf0**)(p + 0x24);
        if (c != 0)
            c->SetMode((const int*)&obj->mCurrent, 1);
    }
}
