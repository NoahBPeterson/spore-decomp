// src/game/SPCreatureAnim/jiggles.cpp -- migrated from slice(s) s009f9b40 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/jiggles.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" const int g_0166c01c;            // 0x0166c01c
extern "C" const int g_01550b0c;            // 0x01550b0c
extern "C" const int g_01550b10;            // 0x01550b10
extern "C" const int g_01550b14;            // 0x01550b14
extern "C" const int g_0166c020;            // 0x0166c020
#ifndef S009F9B40_H
#endif
#include <string.h>
#include <math.h>

// ---- items of slice s009f9b40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct AnimNameRef
{
    unsigned char m_bytes[8];       // +0x00 (raw name text)
    bool HasTag(int tag) const;     // 0x009B30E0
    int  GetValue() const;          // 0x009B3110
};
struct AnimNameHolder
{
    char pad0[0x150];
    AnimNameRef m_name;         // +0x150
    char pad158[0x208 - 0x158];
    int m_208;                  // +0x208
};
extern "C" const int g_0166c01c;            // 0x0166c01c
extern "C" const int g_01550b0c;            // 0x01550b0c
extern "C" const int g_01550b10;            // 0x01550b10
extern "C" const int g_01550b14;            // 0x01550b14
extern "C" const int g_0166c020;            // 0x0166c020
// ---- items of slice s009f9b40 end

// @ 0x009f9ce0
int animNameAllowed(AnimNameHolder* obj)
{
    if (g_0166c01c != 0 && obj->m_name.HasTag(0x00657965))    // "eye"
        return 0;
    if (g_01550b0c != 0 && obj->m_name.HasTag(0x74756f6d))    // "mout"
        return 0;
    if (g_01550b10 != 0 && obj->m_name.HasTag(0x65677263))    // "crge"
        return 0;
    if (g_01550b14 != 0 && obj->m_name.HasTag(0x676e6977))    // "wing"
        return 0;
    if (obj->m_name.HasTag(0x6c637077))                       // "wpcl"
        return 0;
    if (obj->m_name.HasTag(0x6c63746d))                       // "mtcl"
        return 0;
    if (g_0166c020 != 0)
    {
        int v = obj->m_name.GetValue();
        if (v != 0)
            return 1;
        if (obj->m_208 == v)
            return 0;
    }
    return 1;
}
