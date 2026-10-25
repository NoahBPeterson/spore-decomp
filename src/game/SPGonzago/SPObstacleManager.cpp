// src/game/SPGonzago/SPObstacleManager.cpp -- migrated from slice(s) s00422950 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPObstacleManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Variant.h"

// ---- items of slice s00422950 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec12 {
    uint32_t x, y, z;
};
struct Variant {
    uint32_t data[4];
    uint16_t flags;  // bit1: locked to type, bit2: needs reset
    uint16_t type;
    void Reset(int);                                                            // 0x0093DB80
    void SetSlow(int type, int, const void* v, int size, int);                   // 0x0093DD80
    Variant* SetChar(const char* v);
    Variant* SetU32(const uint32_t* v);
    Variant* SetVec12(const Vec12* v);
};
// ---- items of slice s00422950 end

// @ 0x00422e20
Variant* Variant::SetChar(const char* v)
{
    if (flags & 4)
        Reset(1);
    if (1 && (!(flags & 2) || type == 1)) {
        *(char*)this = *v;
        type = 1;
        flags = flags & 2;
    } else {
        SetSlow(1, 0, v, 1, 1);
    }
    return this;
}
