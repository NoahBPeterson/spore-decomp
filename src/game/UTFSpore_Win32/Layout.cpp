// src/game/UTFSpore_Win32/Layout.cpp -- migrated from slice(s) s0097e1f0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Layout.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinControls/WinGrid.h"
#include <math.h>

// ---- items of slice s0097e1f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct INode {                                   // object reached via a window's slot 4
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual INode* Slot4();                      // +0x10
    char pad_;
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
    virtual void v13();
    virtual const float* GetArea();              // +0x38
};
struct Sink14 {                                  // object at holder+0xc, slot 5 (0x14)
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual void v4();
    virtual void Apply(const float* area, float* rect);   // +0x14
};
struct AreaHolder {                              // the `this` of 0x97e8a0
virtual void v0();
virtual void v1();
virtual void v2();
    Sink14* GetSink() { return (Sink14*)*(void**)((char*)this + 0xc); }
};
// ---- items of slice s0097e1f0 end

// @ 0x0097e8a0
void __fastcall FUN_0097e8a0(AreaHolder* self, int unused, INode* node, float* rect)
{
    const float* area;
    float tmp[4];
    INode* inner;

    inner = node->Slot4();
    area = inner->GetArea();
    tmp[0] = area[0];
    tmp[1] = area[1];
    tmp[2] = area[2];
    tmp[3] = area[3];
    self->GetSink()->Apply(tmp, rect);
    if (rect[0] > rect[2])
        rect[2] = rect[0];
    if (rect[1] > rect[3])
        rect[3] = rect[1];
}
