// src/game/SPEngine/SPGraphicsMeshCreators.cpp -- migrated from slice(s) s0071c900 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsMeshCreators.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s0071c900 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IVt {
    void** mpVtbl;      // +0x0
};
typedef void (__thiscall* Fn0)(IVt*);
typedef void (__thiscall* Fn1)(IVt*, int);
typedef void (__thiscall* FnPv)(IVt*, const void*);
// ---- items of slice s0071c900 end

// @ 0x0071d0d0
void SP_CreateArrowheadMesh(IVt* self, const float* p)
{
    void** vt = self->mpVtbl;
    ((Fn0)vt[3])(self);
    float v[3] = { p[0], p[1], p[2] };
    ((FnPv)vt[6])(self, v);
    ((Fn1)vt[0x14])(self, 4);
    ((Fn0)vt[0x1f])(self);
    ((Fn0)vt[4])(self);
}
