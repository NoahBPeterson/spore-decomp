// src/game/UTFSpore_Win32/Adapter.cpp -- migrated from slice(s) s0097cea0, s00950bb0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Adapter.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/CustomWinProc.h"
#include "EA/UTFWin/MultiHeapObject.h"
#include "EA/UTFWin/Image.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/UTFWin/cDropShadowDescriptor.h"
#include <math.h>

// ---- items of slice s0097cea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct CustomWinProc2 {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2(int);
    int field4;         // +4
    int mRefCount;      // +8

    int Release();
};
// ---- items of slice s0097cea0 end

// @ 0x00950eb0
void * EA::UTFWin::CustomWinProc::AsInterface(EA::COM::InterfaceId typeId)
{
    if (typeId == 0x2f009dd0) return this;
    if (typeId == (int)0xee3f516e || typeId == (int)0xeec58382) {
        if (this) return (char*)this + 4;
    }
    return 0;
}

// @ 0x0097da40
int CustomWinProc2::Release()
{
    int n = (*(volatile int*)&mRefCount += -1);
    if (n == 0) slot2(1);
    return n;
}
