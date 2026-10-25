// Slice s00834a00 -- UI::TextZoomName animators + UI::TooltipManager / cSPUITooltipWinProc.
// Region flags /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef float          f32;

typedef void*  (__thiscall *VFi)(void*);
typedef void   (__thiscall *VFv)(void*);
typedef uint32_t (__thiscall *VFu)(void*);
typedef void*  (*GetObjFn)(void*);          // vtbl +0x10: window -> inner object
typedef float* (*GetRectFn)(void*);         // vtbl +0x38: window -> float rect
static inline void** VT(void* o) { return *(void***)o; }

// ---------------------------------------------------------------- masked externs
extern char  g_vtblTooltipMgr;   // 0x141aec8
extern char  g_vtblContentValid; // 0x13ec458
extern void* g_p164f328;         // 0x164f328
extern float g_164f45c;          // 0x164f45c
extern float g_164f44c;          // 0x164f44c
extern float g_164f46c;          // 0x164f46c
extern float g_164f47c;          // 0x164f47c
extern float g_13fdcf4;          // 0x13fdcf4
extern float g_13fdcf8;          // 0x13fdcf8
extern char  g_1548560;          // 0x1548560

extern "C" float FUN_00805080(void);   // SPUIHelpers::GetElapsedSeconds
extern "C" void  FUN_0080fee0(void);   // MultiHeapObject::operator_new
extern "C" void  FUN_00805ea0(void);   // SPUIHelpers::GetMainWindowArea
extern "C" void  FUN_006237d0(void);   // eastl copy_impl
extern "C" void* FUN_0067de30(void);   // SP::PropertyManager
extern "C" void* __cdecl FUN_00810620(void);             // cSPUILayoutManager::GetWorldMainWindow
extern "C" void* __stdcall FUN_0067cad0(void*, u32, u32);  // cSPBoundingBox::AddBoundingBox
extern "C" bool  __cdecl FUN_00805150(int, int);         // SPUIHelpers::Contains
extern "C" void  __cdecl FUN_00834730(void*, u32, u32, u32);
extern "C" void  __cdecl FUN_008347f0(void*, u32, u32);
extern "C" void  __cdecl FUN_00834660(int);
extern "C" void  __cdecl FUN_007f8f00(void*);            // cSPUIAnimator::ClearAll
extern "C" void  __cdecl FUN_00808d20(void*, void*, u32);
extern "C" void* __cdecl FUN_009512c0(void);
extern "C" void* __cdecl FUN_009512d0(int, int, const char*);
extern "C" char  __cdecl FUN_004eb930(void);
extern "C" void  __cdecl FUN_00811ad0(void*, u32);       // cSPUILayout::Shutdown
extern "C" void* __cdecl FUN_008105b0(void*, int, int);  // cSPUILayout::FindWindowByID

// Same entry point reached as a real thiscall member so `ecx` holds the layout
// pointer exactly like the retail code.
struct LayoutFind {
    void* FindWindowByID(int id, int one);
};
extern "C" void  __cdecl FUN_0080d710(void*, u32, u32);  // SPUIHelpers::Renderer

// ---------------------------------------------------------------- generic UI window
// Real virtuals so the compiler puts `this` in `ecx` (thiscall) exactly like the
// retail code, instead of pushing the object as a stack argument.
struct ZoomWin {
    virtual void v00();            // +0x00  AddRef
    virtual void v04();            // +0x04  Release
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(u32, u32); virtual void v50();
    virtual void v54(); virtual void v58(); virtual void v5c(u32); virtual void v60();
    virtual void v64(); virtual void v68(); virtual void v6c(); virtual void v70();
    virtual void v74(); virtual void v78(); virtual void v7c(u32, u32); virtual void v80(u32);
    virtual void v84(u32); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual void va4(); virtual void va8(); virtual void vac(u32); virtual void vb0();
    virtual void vb4(); virtual void vb8(); virtual void vbc(); virtual void vc0();
    virtual void vc4(); virtual void vc8(); virtual void vcc(); virtual void vd0();
    virtual void vd4(); virtual void vd8(void*); virtual void vdc(); virtual void ve0(u32);
};

// ---------------------------------------------------------------- UI::TooltipManager (retail layout)
struct TooltipManager {
    void*    vptr;   // +0x00
    int      rc;     // +0x04
    void*    layout; // +0x08
    void*    window; // +0x0c
    void*    parent; // +0x10
    void*    props;  // +0x14
    uint32_t key0;   // +0x18
    uint32_t key1;   // +0x1c
    uint32_t key2;   // +0x20
    float    f24;    // +0x24
    float    f28;    // +0x28
    uint8_t  b2c;    // +0x2c
    uint8_t  b2d;    // +0x2d
    uint8_t  b2e;    // +0x2e

    TooltipManager();
    void Dtor();
    bool ReleaseRefs();
    bool ShouldDisplayTooltip(void* w);
    int  ShouldTimeoutTooltip();
    int  ShouldDisplayDetailedTooltip();
    void SetTooltipText(int a, int b);
    void MakeFullyVisibleInMainWindow(int dummy);
    bool LoadProps();
    void ShowWindow(u32 id, u32 a3, u32 a4);   // 0x00835660  ret 0xc
};

struct TooltipWinProc {
    char    pad[0x58];
    uint8_t mbMouseOver;   // +0x58
    uint32_t GetEventMask();
};

// ---------------------------------------------------------------- UI::TextZoomName (retail layout)
// Reached through the 0x834f30 message dispatch; ecx = this (an offset into a
// larger object, so several fields are addressed from this pointer).
struct TextZoomName {
    char pad0[0x10];
    u8   animator[0x20];      // +0x10  cSPUIAnimator (updated/cleared)
    u8   layout[0x18];        // +0x30  cSPUILayout (FindWindowByID / Shutdown / Init)
    void* targetId;           // +0x48  (layer id passed to Activate/Deactivate)
    char pad4c[0x8];          // +0x4c..+0x53
    u32  savedParam;          // +0x54  (param stored by Activate / SetTargetWindow)
    float width;              // +0x58
    float height;             // +0x5c
    u8   b60;                 // +0x60  (animator active)
    char pad61[0x3];
    void* winA;               // +0x64  (sub-window / source)
    void* winB;               // +0x68  (target window)
    void* winC;               // +0x6c  (parent layout window)
    void* winD;               // +0x70  (props window)
    u32  field74;             // +0x74

    // Real member functions so `this` lands in `ecx` and the stack arguments
    // match the retail `ret N` clean-up exactly.
    u32  Activate(u32 param);                       // 0x00834a00  ret 4
    void Deactivate(u32 param);                     // 0x00834c60  ret 4
    void Shutdown();                                // 0x00834e30  ret
    u32  SetTargetWindow(void* p2, void* p3, u32 p4, u32 p5,
                         void* p6, void* p7, void* p8);  // 0x00834fa0  ret 0x1c
};

// The message handler's `this` sits 0xc bytes before the TextZoomName, so the
// retail dispatch reaches the object via `lea ecx, [esi - 0xc]`.
struct MsgSender {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10();
    virtual u32  GetObj();   // +0x14
};
struct MsgSender2 {
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
    virtual void t10(); virtual void t14(); virtual void t18(); virtual void t1c();
    virtual void t20(); virtual void t24(); virtual void t28(); virtual void t2c();
    virtual void t30(); virtual void t34(); virtual void t38(); virtual void t3c();
    virtual void t40(); virtual void t44();
    virtual u32  GetId(u32 one);    // +0x48
};
struct TextZoomProc {
    char         pad0[0xc];
    TextZoomName zoom;         // +0x0c
    u32 OnMessage(u32 sender, u32 msg);   // 0x00834f30  ret 8
};

struct TextZoomWindow {
    virtual void z00(); virtual void z04(); virtual void z08(); virtual void z0c();
    virtual void z10(); virtual void z14(); virtual void z18(); virtual void z1c();
    virtual void z20(); virtual void z24(); virtual void z28(); virtual void z2c();
    virtual void z30(); virtual void z34(); virtual void z38(); virtual void z3c();
    virtual void z40(); virtual void z44(); virtual void z48(); virtual void z4c();
    virtual void z50(); virtual void z54(); virtual void z58(); virtual void z5c(float);
    virtual void z60(); virtual void z64(); virtual void z68(); virtual void z6c();
    virtual void z70(); virtual void z74(); virtual void z78(); virtual void z7c(u32, u32);
    virtual void z80(u32); virtual void z84(u32); virtual void z88(); virtual void z8c();
    virtual void z90(); virtual void z94(); virtual void z98(); virtual void z9c();
    virtual void za0(); virtual void za4(); virtual void za8(); virtual void zac(u32);
};

extern "C" bool   __cdecl FUN_00805150(int, int);       // SPUIHelpers::Contains
extern "C" void   __cdecl FUN_00834730(void*, u32, u32, u32);   // animator setup
extern "C" void   __cdecl FUN_008347f0(void*, u32, u32);
extern "C" void   __cdecl FUN_00834660(int);
extern "C" void   __cdecl FUN_007f8f00(void*);           // cSPUIAnimator::ClearAll
extern "C" void*  __cdecl FUN_009512c0(void);            // WinText factory
extern "C" void*  __cdecl FUN_009512d0(int, int, const char*);
extern "C" char   __cdecl FUN_004eb930(void);

// ================================================================ bodies

// ---------------------------------------------------------------------------
// @ 0x00834a00  UI::TextZoomName::Activate — snap the zoomed title/subtitle
// windows over the source window's bounding rectangle and start the fade-in.
// `ret 4` with `ecx` read at entry: thiscall, one stack argument.
// ---------------------------------------------------------------------------
u32 TextZoomName::Activate(u32 param) {
    TextZoomName* const self = this;
    if (self->winA == 0 || self->winB == 0) {
        return 0;
    }
    self->savedParam = param;

    u32* const srcVt = *(u32**)self->winA;
    char* const src = (char*)(*(GetObjFn)(srcVt + (0x10 / 4)))(self->winA);
    u32* const dstVt = *(u32**)self->winB;
    char* const dst = (char*)(*(GetObjFn)(dstVt + (0x10 / 4)))(self->winB);

    float rect[4];
    FUN_00808d20(rect, dst, 0);
    u32* const sv = *(u32**)src;
    const u32 srcH = (u32)(*(GetObjFn)(sv + (0x3c / 4)))(src);
    (*(void(**)(char*, u32))(srcVt + (0x80 / 4)))(src, srcH);

    u32 anchor[2];
    anchor[0] = 0;
    anchor[1] = 0;
    (*(void(**)(char*, u32*, float, float))(srcVt + (0x6c / 4)))(
        src, anchor, rect[2] - rect[0], rect[3] - rect[1]);
    const u32 dstH = (u32)(*(GetObjFn)(dstVt + (0x40 / 4)))(dst);
    (*(void(**)(char*, u32))(srcVt + (0x84 / 4)))(src, dstH);
    const u32 srcExtra = (u32)(*(GetObjFn)(dstVt + (0x24 / 4)))(self->winB);
    (*(void(**)(char*, u32))(srcVt + (0x28 / 4)))(src, srcExtra);
    (*(void(**)(char*, u32))(srcVt + (0x5c / 4)))(src, 0xffffffu);
    (*(void(**)(char*, u32))(srcVt + (0xac / 4)))(src, 0);

    u32 r3, r2, r1, r0;
    (*(void(**)(void*, u32*, u32*, u32*, u32*))(dstVt + (0x34 / 4)))(
        self->winB, &r3, &r2, &r1, &r0);
    (*(void(**)(char*, u32, u32, u32, u32))(srcVt + (0x38 / 4)))(
        src, dstH, srcExtra, 0xffffffu, 0);

    float* const srcRect = (*(GetRectFn)(srcVt + (0x38 / 4)))(src);
    (*(void(**)(void*, u32))(*(u32**)self->winA + (0x1c / 4)))(self->winA, 0);
    float* const srcRect2 = (*(GetRectFn)(srcVt + (0x38 / 4)))(src);
    const float theight = srcRect2[2] - srcRect2[0];
    self->width = theight;

    if (self->height <= theight && theight != self->height) {
        (*(void(**)(char*, u32, u32))(srcVt + (0x7c / 4)))(src, 1, 1);
        FUN_00834730(dst, 0x3e19999a, 0, 0);
        FUN_00834730(src, 0x3e19999a, 0, 0xff);
        FUN_008347f0(src, 0x3e19999a, 0);
        char* const sub = (char*)FUN_008105b0((char*)self + 0x30, 0x626e3b8, 0);
        if (sub != 0) {
            u32* const subVt = *(u32**)sub;
            (*(void(**)(char*, u32, u32))(subVt + (0x7c / 4)))(sub, 1, 1);
            FUN_00834730(sub, 0x3e19999a, 0, 0xff);
        }
        if (self->b60 != 0) {
            FUN_007f8f00((char*)self + 0x10);
            FUN_00834660(1);
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00834c60  UI::TextZoomName::Deactivate — reverse pass: hide the zoomed
// windows and fade them out.  `ret 4` with `ecx` read at entry.
// ---------------------------------------------------------------------------
void TextZoomName::Deactivate(u32 param) {
    TextZoomName* const self = this;
    if (self->winA == 0 || self->winB == 0) {
        return;
    }
    u32* const aVt = *(u32**)self->winA;
    char* const a = (char*)(*(GetObjFn)(aVt + (0x10 / 4)))(self->winA);
    u32* const bVt = *(u32**)self->winB;
    char* const b = (char*)(*(GetObjFn)(bVt + (0x10 / 4)))(self->winB);

    bool flag = true;
    if (param == 0) {
        float* const ar = (*(GetRectFn)(*(u32**)a + (0x38 / 4)))(a);
        const float aw = ar[2] - ar[0];
        float* const br = (*(GetRectFn)(*(u32**)b + (0x38 / 4)))(b);
        if (br[2] - br[0] < aw) {
            flag = false;
        }
    }

    float rect[4];
    FUN_00808d20(rect, b, 0);
    float* const ar2 = (*(GetRectFn)(*(u32**)a + (0x38 / 4)))(a);
    self->height = ar2[2] - ar2[0];
    self->width = rect[3] - rect[0];

    u32 scale;
    if (flag) {
        scale = 0;
    } else {
        scale = 0x3e19999a;
    }
    FUN_00834730(b, scale, 0, 0xff);
    FUN_00834730(a, scale, 0, 0);
    FUN_008347f0(a, scale, 0);
    (*(void(**)(char*, u32, u32))(*(u32**)a + (0x7c / 4)))(a, 1, 0);
    char* const sub = (char*)FUN_008105b0((char*)self + 0x30, 0x626e3b8, 0);
    if (sub != 0) {
        (*(void(**)(char*, u32, u32))(*(u32**)sub + (0x7c / 4)))(sub, 1, 0);
        FUN_00834730(sub, scale, 0, 0);
    }
    if (self->b60 != 0) {
        FUN_007f8f00((char*)self + 0x10);
        FUN_00834660(1);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00834e30  UI::TextZoomName::Shutdown — stop the animator, shut the layout
// down and release both retained windows.  Plain `ret` with `ecx` at entry.
// ---------------------------------------------------------------------------
void TextZoomName::Shutdown() {
    TextZoomName* const self = this;
    self->Deactivate(1);
    FUN_007f8f00((char*)self + 0x10);
    FUN_00811ad0((char*)self + 0x30, 1);

    if (self->winB != 0) {
        u32* const v = *(u32**)self->winB;
        char* const w = (char*)(*(GetObjFn)(v + (0x10 / 4)))(self->winB);
        (*(void(**)(char*, u32))(*(u32**)w + (0x5c / 4)))(w, self->field74);
        if (self->winB != 0) {
            void* const dead = self->winB;
            self->winB = 0;
            (*(void(**)(void*))(*(u32**)dead + (0x04 / 4)))(dead);
        }
    }
    if (self->winA != 0) {
        u32* const v = *(u32**)self->winA;
        char* const p1 = (char*)(*(GetObjFn)(v + (0x10 / 4)))(self->winA);
        char* const p2 = (char*)(*(GetObjFn)(*(u32**)p1 + (0x10 / 4)))(p1);
        const u32 arg = (*(u32(**)(void*))(v + (0x10 / 4)))(self->winA);
        (*(void(**)(char*, u32))(*(u32**)p2 + (0xe0 / 4)))(p2, arg);
        if (self->winA != 0) {
            void* const dead = self->winA;
            self->winA = 0;
            (*(void(**)(void*))(*(u32**)dead + (0x04 / 4)))(dead);
        }
    }
    if (self->winD != 0) {
        (*(void(**)(void*, char*))(*(u32**)self->winD + (0x108 / 4)))(
            self->winD, (char*)self + 0x0c);
        if (self->winD != 0) {
            void* const dead = self->winD;
            self->winD = 0;
            (*(void(**)(void*))(*(u32**)dead + (0x04 / 4)))(dead);
        }
    }
    if (self->winC != 0) {
        void* const dead = self->winC;
        self->winC = 0;
        (*(void(**)(void*))(*(u32**)dead + (0x04 / 4)))(dead);
    }
    if (self->b60 != 0) {
        void* const srv = FUN_0067de30();
        (*(void(**)(void*, char*, u32, u32))(*(u32**)srv + (0x2c / 4)))(
            srv, (char*)self + 8, 0x61dd1b7, 0xffffd8f1);
        self->b60 = 0;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00834f30  TextZoomName message dispatch — reacts to layout messages 0x1b
// and 0x1c: if the sender is contained in the current target, activate; else
// deactivate.  `ret 8` with `ecx` read at entry (2 stack arguments).
// ---------------------------------------------------------------------------
u32 TextZoomProc::OnMessage(u32 sender, u32 msg) {
    TextZoomName* const self = &zoom;
    MsgSender*  const snd = (MsgSender*)sender;
    int*        const msgAsInt = (int*)msg;
    const u32 kind = (u32)(msgAsInt[2] - 0x1b);
    u32 result = 0;
    if (kind < 2 && msgAsInt[3] == 1) {
        MsgSender2* const obj = (MsgSender2*)snd->GetObj();
        const u32 id = obj->GetId(1);
        if (FUN_00805150((int)self->winA, (int)id)) {
            self->Activate((u32)self->targetId);
        } else {
            self->Deactivate(0);
        }
        result = 0;
    }
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x00834fa0  UI::TextZoomName::SetTargetWindow — rebind the source, target
// and layout windows, create the "UI/cSPUITextZoom" window when needed and
// re-initialise the layout.  `ret 0x1c` with `ecx` at entry (7 stack args).
// ---------------------------------------------------------------------------
u32 TextZoomName::SetTargetWindow(void* p2, void* p3, u32 p4, u32 p5,
                                  void* p6, void* p7, void* p8) {
    TextZoomName* const self = this;
    (void)p4;
    (void)p5;
    int* const srcWin = (int*)p2;
    int* const parentWin = (int*)p3;
    if (srcWin == 0) {
        return 0;
    }
    u32* const sv = *(u32**)srcWin;
    char* const inner = (char*)(*(GetObjFn)(sv + (0x10 / 4)))(srcWin);
    const u32 inner2 = (*(u32(**)(char*))(*(u32**)inner + (0x10 / 4)))(inner);
    if (inner2 == 0) {
        return 0;
    }
    if ((void*)self->winB == (void*)srcWin &&
        ((p6 != (void*)0x164f240 || p7 != (void*)0x164f244) ||
         p8 != (void*)0x164f248)) {
        if (FUN_004eb930() != 0 && (void*)self->winC == (void*)parentWin) {
            return 1;
        }
    }

    self->Shutdown();

    if ((void*)srcWin != self->winB) {
        (*(void(**)(int*))(sv + 0))(srcWin);
        void* const old = self->winB;
        self->winB = srcWin;
        if (old != 0) {
            (*(void(**)(void*))(*(u32**)old + (0x04 / 4)))(old);
        }
    }

    u32* const bw = *(u32**)self->winB;
    char* const bwInner = (char*)(*(GetObjFn)(bw + (0x10 / 4)))(self->winB);
    self->field74 = (*(u32(**)(char*))(*(u32**)bwInner + (0x30 / 4)))(bwInner);

    void* created = FUN_009512d0(0x834, 4, "UI/cSPUITextZoom");
    char* winText = 0;
    if (created != 0) {
        void* const wt = FUN_009512c0();
        if (wt != 0) {
            winText = (char*)wt + 0x20c;
        }
    }
    if (winText != self->winA) {
        if (winText != 0) {
            (*(void(**)(char*))(*(u32**)winText + 0))(winText);
        }
        void* const oldA = self->winA;
        self->winA = winText;
        if (oldA != 0) {
            (*(void(**)(void*))(*(u32**)oldA + (0x04 / 4)))(oldA);
        }
    }

    char* const a = (char*)(*(GetObjFn)(*(u32**)self->winA + (0x10 / 4)))(
        self->winA);
    if ((void*)parentWin != self->winC) {
        if (parentWin != 0) {
            (*(void(**)(int*))(*(u32**)parentWin + 0))(parentWin);
        }
        void* const oldC = self->winC;
        self->winC = parentWin;
        if (oldC != 0) {
            (*(void(**)(void*))(*(u32**)oldC + (0x04 / 4)))(oldC);
        }
    }
    if (self->winC == 0) {
        void* const world = FUN_00810620();
        self->winC = world;
    }
    (*(void(**)(void*, u32*))(*(u32**)self->winC + (0xd8 / 4)))(
        self->winC, (u32*)a);
    (*(void(**)(char*, u32, u32))(*(u32**)a + (0x7c / 4)))(a, 1, 0);
    (*(void(**)(char*, u32, u32))(*(u32**)a + (0x7c / 4)))(a, 0x10, 1);

    if (self->winD != 0) {
        (*(void(**)(void*, char*))(*(u32**)self->winD + (0x108 / 4)))(
            self->winD, (char*)self + 0x0c);
    }
    void* const oldD = self->winD;
    if ((void*)self->winD != 0) {
        self->winD = 0;
        (*(void(**)(void*))(*(u32**)oldD + (0x04 / 4)))(oldD);
    }
    self->savedParam = 0;
    if (self->winD != 0) {
        (*(void(**)(void*, char*))(*(u32**)self->winD + (0x104 / 4)))(
            self->winD, (char*)self + 0x0c);
    }

    (*(void(**)(char*, u32, u32, u32))(*(u32**)a + (0x7c / 4)))(a, 1, 0, 0);
    (*(void(**)(char*, u32, u32))(*(u32**)a + (0x7c / 4)))(a, 1, 0);

    char* const sub = (char*)FUN_008105b0((char*)self + 0x30, 0x626e3b8, 0);
    if (sub != 0) {
        (*(void(**)(char*, u32, u32))(*(u32**)sub + (0x7c / 4)))(sub, 1, 0);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00835660  TooltipManager window refresh — look the window up by id, swap
// it into the cached slot, add it to the bounding box and set its text.
// `ret 0xc` with `ecx` read at entry (3 stack arguments).
// ---------------------------------------------------------------------------
struct BoundingBox {
    void Add(u32 kind, u32 one);   // thiscall: FUN_0080d710
};

void TooltipManager::ShowWindow(u32 id, u32 a3, u32 a4) {
    TooltipManager* const self = this;
    ZoomWin* const found =
        (ZoomWin*)((LayoutFind*)self->layout)->FindWindowByID((int)id, 1);
    ZoomWin* const old = (ZoomWin*)self->window;
    if (found != old) {
        if (found != 0) {
            found->v00();
        }
        self->window = found;
        if (old != 0) {
            old->v04();
        }
    }
    ZoomWin* const win = (ZoomWin*)self->window;
    if (win != 0) {
        win->v7c(0x10, 1);
        BoundingBox* const bb =
            (BoundingBox*)FUN_0067cad0(self->window, 0xe, 1);
        bb->Add(0xe, 1);
        self->SetTooltipText(a3, a4);
    }
}

// @ 0x008352a0
uint32_t TooltipWinProc::GetEventMask()
{
    return (uint32_t)(((mbMouseOver != 0) ? 0xFFFFFFFFu : 0) & 2) | 0x441;
}

// @ 0x008352c0
void* FUN_008352c0()
{
    if (g_p164f328 != 0)
        return (char*)g_p164f328 - 8;
    return 0;
}

// @ 0x008352d0
TooltipManager::TooltipManager()
{
    g_p164f328 = (void*)((char*)this + 8);
    rc = 0;
    vptr = &g_vtblTooltipMgr;
    layout = 0;
    window = 0;
    parent = 0;
    props = 0;
    key0 = 0;
    key1 = 0;
    key2 = 0;
    f24 = 0.0f;
    f28 = 0.0f;
    b2c = 0;
    b2d = 0;
    b2e = 0;
}

// @ 0x00835320
void TooltipManager::Dtor()
{
    *(void* volatile*)this = &g_vtblTooltipMgr;
    void* p14 = *(void* volatile*)((char*)this + 0x14);
    if (p14)  ((VFv)VT(p14)[4 / 4])(p14);
    void* p10 = *(void* volatile*)((char*)this + 0x10);
    if (p10) ((VFv)VT(p10)[4 / 4])(p10);
    void* pc = *(void* volatile*)((char*)this + 0x0c);
    if (pc) ((VFv)VT(pc)[4 / 4])(pc);
    void* p8 = *(void* volatile*)((char*)this + 0x08);
    if (p8) ((VFv)VT(p8)[8 / 4])(p8);
    *(void* volatile*)this = &g_vtblContentValid;
    g_p164f328 = 0;
}

// @ 0x008353a0
bool TooltipManager::ReleaseRefs()
{
    if (void* p = layout) { layout = 0; ((VFv)VT(p)[8 / 4])(p); }
    if (void* p = window) { window = 0; ((VFv)VT(p)[4 / 4])(p); }
    if (void* p = parent) { parent = 0; ((VFv)VT(p)[4 / 4])(p); }
    if (void* p = props)  { props = 0;  ((VFv)VT(p)[4 / 4])(p); }
    return true;
}

// @ 0x008353f0
bool TooltipManager::ShouldDisplayTooltip(void* w)
{
    bool r = false;
    if (b2c == 0 && w != parent) {
        if (b2d != 0 && FUN_00805080() - f28 < g_164f45c)
            r = true;
        if (FUN_00805080() - f24 > g_164f44c)
            return true;
    }
    return r;
}

// @ 0x00835440
int TooltipManager::ShouldTimeoutTooltip()
{
    if (b2c != 0) {
        if (FUN_00805080() - f24 > g_164f46c)
            return 1;
    }
    return 0;
}

// @ 0x00835470
int TooltipManager::ShouldDisplayDetailedTooltip()
{
    if (b2c != 0 && b2e == 0) {
        if (FUN_00805080() - f24 > g_164f47c)
            return 1;
    }
    return 0;
}

// @ 0x008354a0
void TooltipManager::SetTooltipText(int a, int b)
{
    ((void (__thiscall*)(void*, int))VT(window)[0x80 / 4])(window, a);
    ((void (__thiscall*)(void*, int))VT(window)[0x5c / 4])(window, b);
    if (window) {
        void* p = ((void* (__thiscall*)(void*, void*))VT(window)[0xc / 4])(window, (void*)0xf15f4bd);
        if (p) {
            ((void (__thiscall*)(void*, float, float))VT(window)[0x68 / 4])(window, g_13fdcf4, g_13fdcf8);
            ((void (__thiscall*)(void*, int))VT(p)[0x14 / 4])(p, 1);
            ((void (__thiscall*)(void*, int))VT(p)[0x14 / 4])(p, 0);
        }
    }
}

// @ 0x00835520
void TooltipManager::MakeFullyVisibleInMainWindow(int dummy)
{
    (void)dummy;
    float area[4];
    ((void (__cdecl*)(void*))FUN_00805ea0)(area);
    float* r = ((float* (__thiscall*)(void*))VT(window)[0x38 / 4])(window);
    float sx = 0.0f;
    float* p = r;
    if (!(*r > 0.0f)) p = &sx;
    sx = *p;
    float sy = 0.0f;
    float* q = r + 1;
    if (!(r[1] > 0.0f)) q = &sy;
    sy = *q;
    if (area[2] < r[2]) sx = r[0] - (r[2] - area[2]);
    if (area[3] < r[3]) sy = r[1] - (r[3] - r[1]);
    ((void (__thiscall*)(void*, float, float))VT(window)[0x70 / 4])(window, sx, sy);
}

// @ 0x00835610
bool TooltipManager::LoadProps()
{
    void* pm = FUN_0067de30();
    if (void* p = props) { props = 0; ((VFv)VT(p)[4 / 4])(p); }
    char c = ((char (__thiscall*)(void*, int, void**))VT(pm)[0x30 / 4])(pm, 0x5c770db7, &props);
    if (c)
        ((void (__thiscall*)(void*, void*))FUN_006237d0)(&g_1548560, props);
    return true;
}
