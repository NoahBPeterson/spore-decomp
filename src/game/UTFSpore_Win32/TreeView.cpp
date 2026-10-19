// src/game/UTFSpore_Win32/TreeView.cpp -- migrated from slice(s) s01300280, s0098e3a0, s00950bb0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/TreeView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/CustomWinProc.h"
#include "EA/UTFWin/MultiHeapObject.h"
#include <intrin.h>
#include "EA/Text/FontServer.h"
#include "EA/Text/LineLayout.h"
#include "EA/Stopwatch.h"
#include "EA/Text/TextStyle.h"
#include "EA/Text/Typesetter.h"
#include <stddef.h>

// ---- items of slice s00950bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWin {
struct CustomWinProc_s0095_0bb0 {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2(int);
    char pad[0x18];
    unsigned int mnRefCount;    // +0x1c

    void* AsInterface(int typeId);   // 0x00950EB0
    void* AsInterfaceA(int typeId);  // 0x00951240
    int   Release();                 // 0x009514A0
};
}
}
using EA::UTFWin::CustomWinProc_s0095_0bb0;
// ---- items of slice s00950bb0 end

// ---- items of slice s0098e3a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned __int64 __rdtsc();
#pragma pack(4)
#pragma intrinsic(__rdtsc)
namespace EA {
namespace UTFWinControls {
struct TypeRegistry {
    virtual void v0();
    virtual void Register(void* type, int flags);
};
}
}
namespace EA {
namespace UTFWinControls {
TypeRegistry* GetTypeRegistry();                              // 0x920090
}
}
namespace EA {
namespace UTFWinControls {
extern void* g_WinTextEditType0;                              // 0x154fe5c
}
}
namespace EA {
namespace UTFWinControls {
extern void* g_WinTextEditType1;                              // 0x154fe60
}
}
namespace EA {
namespace UTFWinControls {
extern void* g_WinTextEditType2;                              // 0x154fe64
}
}
namespace EA {
namespace UTFWinControls {
struct UTFWindow { bool Initialize(); };                      // 0xb1fbf0
}
}
namespace EA {
namespace UTFWinControls {
struct WinTreeView : UTFWindow {
    uint32_t pad[0x84];
    bool mInited;                                             // +0x210
    bool Init();
};
}
}
// ---- items of slice s0098e3a0 end

// @ 0x00951240
namespace EA { namespace UTFWin {
void* CustomWinProc_s0095_0bb0::AsInterfaceA(int typeId)
{
    if (typeId == 0x6ec581fd) return this;
    if (typeId == (int)0xee3f516e || typeId == (int)0xeec58382) {
        if (this) return (char*)this + 4;
    }
    return 0;
}
}}  // namespace EA::UTFWin

// @ 0x0098f330
namespace EA { namespace UTFWinControls {
void RegisterWinTextEditTypes()
{
    GetTypeRegistry()->Register(&g_WinTextEditType0, 0);
    GetTypeRegistry()->Register(&g_WinTextEditType1, 0);
    GetTypeRegistry()->Register(&g_WinTextEditType2, 0);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098f3d0
namespace EA { namespace UTFWinControls {
bool WinTreeView::Init()
{
    if (!mInited) {
        if (Initialize())
            mInited = true;
    }
    return mInited;
}
}}  // namespace EA::UTFWinControls

// @ 0x01300e90
void init_154ff0c()
{
    *(int*)0x154ff0c = 1;
    *(int*)0x154ff10 = 0;
    *(void**)0x154ff14 = (void*)0x1418fd8;
    *(int*)0x154ff18 = 0x302a0006;
    *(short*)0x154ff1c = 0x13;
    *(int*)0x154ff20 = 0x2b4;
    *(int*)0x154ff24 = 1;
    *(int*)0x154ff28 = 0;
    *(int*)0x154ff2c = 0;
    *(int*)0x154ff30 = 0x302a0007;
    *(short*)0x154ff34 = 9;
    *(int*)0x154ff38 = 0x2b8;
    *(int*)0x154ff3c = 1;
    *(int*)0x154ff40 = 0;
    *(int*)0x154ff44 = 0;
    *(int*)0x154ff48 = 0x302a0008;
    *(short*)0x154ff4c = 9;
    *(int*)0x154ff50 = 0x2bc;
    *(int*)0x154ff54 = 1;
    *(int*)0x154ff58 = 0;
    *(int*)0x154ff5c = 0;
    *(int*)0x154ff60 = 0x302a0009;
    *(short*)0x154ff64 = 9;
    *(int*)0x154ff68 = 0x2c0;
    *(int*)0x154ff6c = 1;
    *(int*)0x154ff70 = 0;
    *(int*)0x154ff74 = 0;
    *(int*)0x154ff78 = 0x302a000a;
    *(short*)0x154ff7c = 9;
    *(int*)0x154ff80 = 0x2c4;
    *(int*)0x154ff84 = 1;
    *(int*)0x154ff88 = 0;
    *(void**)0x154ff8c = (void*)0x14455f4;
    *(int*)0x154ff90 = 0x302a000b;
    *(short*)0x154ff94 = 9;
    *(int*)0x154ff98 = 0x2fc;
    *(int*)0x154ff9c = 1;
    *(int*)0x154ffa0 = 0;
    *(void**)0x154ffa4 = (void*)0x14455f4;
    *(int*)0x154ffa8 = 0x302a000c;
    *(short*)0x154ffac = 9;
    *(int*)0x154ffb0 = 0x14 + 0x2fc;
    *(int*)0x154ffb4 = 1;
    *(int*)0x154ffb8 = 0;
    *(void**)0x154ffbc = (void*)0x1441580;
    *(int*)0x154ffc0 = 0x302a000d;
    *(short*)0x154ffc4 = 0x13;
    *(int*)0x154ffc8 = 0x2f8;
    *(int*)0x154ffcc = 1;
    *(int*)0x154ffd0 = 0;
    *(void**)0x154ffd4 = (void*)0x1441580;
    *(int*)0x154ffd8 = 0x302a000e;
    *(short*)0x154ffdc = 0x13;
    *(int*)0x154ffe0 = 0x14 + 0x2f8;
    *(int*)0x154ffe4 = 1;
}
