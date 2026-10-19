// src/game/SPEngine/SPAppSplitModelEffect.cpp -- migrated from slice(s) s00798d30 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppSplitModelEffect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include <math.h>

// ---- items of slice s00798d30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Mat3 { void Assign(void *); };
struct CSplitCtor { int *copy(int *src); };
// ---- items of slice s00798d30 end

// @ 0x00799450
int *CSplitCtor::copy(int *param_2)
{
    int *this_ = (int *)this;
    *(char *)this_ = *(char *)param_2;
    *(short *)((char *)this_ + 4) = *(unsigned short *)((char *)param_2 + 4);
    *(short *)((char *)this_ + 6) = *(unsigned short *)((char *)param_2 + 6);
    *(float *)((char *)this_ + 8) = *(float *)((char *)param_2 + 8);
    *(float *)((char *)this_ + 0xc) = *(float *)((char *)param_2 + 0xc);
    *(float *)((char *)this_ + 0x10) = *(float *)((char *)param_2 + 0x10);
    *(float *)((char *)this_ + 0x14) = *(float *)((char *)param_2 + 0x14);
    ((Mat3 *)((char *)this_ + 0x18))->Assign((char *)param_2 + 0x18);
    *(short *)((char *)this_ + 0x3c) = *(unsigned short *)((char *)param_2 + 0x3c);
    *(short *)((char *)this_ + 0x3e) = *(unsigned short *)((char *)param_2 + 0x3e);
    *(float *)((char *)this_ + 0x40) = *(float *)((char *)param_2 + 0x40);
    *(float *)((char *)this_ + 0x44) = *(float *)((char *)param_2 + 0x44);
    *(float *)((char *)this_ + 0x48) = *(float *)((char *)param_2 + 0x48);
    *(float *)((char *)this_ + 0x4c) = *(float *)((char *)param_2 + 0x4c);
    ((Mat3 *)((char *)this_ + 0x50))->Assign((char *)param_2 + 0x50);
    return this_;
}
