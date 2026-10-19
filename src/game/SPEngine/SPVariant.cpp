// src/game/SPEngine/SPVariant.cpp -- migrated from slice(s) s00454330 by tools/migrate/rewrite.py
// Object file: SPEngine/SPVariant.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>

// ---- items of slice s00454330 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl  FUN_006bb640(void* variant);                                           // 0x6bb640
struct Variant {
    void* mData;            // 0x00 (heap pointer when the 0x30 flags are set)
    char pad[0x0C];
    unsigned short mFlags;  // 0x10
    unsigned short mType;   // 0x12
};
// ---- items of slice s00454330 end

// @ 0x00454b10
void* __fastcall VariantTypeTraits_Key_GetTPTR(Variant* v)
{
    void* result;
    if (v->mType == 0x20 || v->mType == 0x10) {
        if ((v->mFlags & 0x30) == 0) {
            result = v;
            if (v->mType == 0) result = 0;
        } else {
            result = v->mData;
        }
    } else {
        result = FUN_006bb640(v);
    }
    return result;
}
