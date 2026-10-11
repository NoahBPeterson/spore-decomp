// Slice s0095a580 -- EA::UTFWin::WindowMgr message-queue processing + display-list rebuild.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#pragma once
#include "../s00958a70/s00958a70.h"

typedef float f32;
typedef uint16_t u16;

// ---------------------------------------------------------------- local support types
struct RectF { float x0, y0, x1, y1; };
struct Xform { float m[17]; };
struct IRenderMode;
struct IRenderer {
    virtual void AddRef();                                         // +0
    virtual void Release(); virtual void r2(); virtual void r3();
    virtual void* CreateData(IWin* w);                             // +0x10
};
struct Base2D { Base2D(void*); virtual ~Base2D(); u32 d[8]; };      // ctor 0x9520a0 dtor 0x951ba0
struct Builder { Builder(); ~Builder(); u32 d[40]; };               // ctor 0x952aa0 dtor 0x952f80
struct Batch2D : Base2D { Builder b; Batch2D(void* a) : Base2D(a) {} };
struct RenderCtx {
    Xform* xf; u32 shade; RectF clip; RectF vp; float trans[3]; float scale[3];
    IRenderMode* mode; IRenderMode* defMode; Node* list; Xform* mat; u32 colorMod; Chunk* chunks;
    Batch2D batch;
    RenderCtx(void* a);                                            // 0x95bb80
};
struct DLEntry {                                                  // 0x100
    Node link;                                                    // +0
    DLEntry* prevEntry;                                           // +8
    u8 b0c, b0d, b0e, b0f;                                        // +0xc
    u16 depth, lowest;                                            // +0x10
    IRenderer* renderer;                                          // +0x14
    Chunk chunks;                                                 // +0x18
    u8 data[0x44];                                                // +0x48
    u8 clip[0x10];                                                // +0x8c
    u32 f9c;                                                      // +0x9c
    u32 fA0;                                                      // +0xa0
    u8 pad[0x58];                                                 // +0xa4 .. +0xfb
    u32 fFC;                                                      // +0xfc
};
extern DLEntry* __cdecl AllocDisplayListEntry();                  // 0x956ff0
extern void __cdecl FreeDisplayListEntry(void* p);                // 0x956e90
extern void __cdecl EastlListSwap(void* a, void* b);              // 0x75d8d0
extern float g_1470f1c;                                           // 2.0f

// ---------------------------------------------------------------- WindowMgr slice methods
struct WindowMgr : WM {
    // @ 0x95a580
    void __thiscall BuildDisplayList(Node* out, Win* w, void* info);
    // @ 0x95a8e0
    void __thiscall SetViewportSize(float vw, float vh);
    // @ 0x95a980
    bool __thiscall SendMsg(IWin* src, IWin* win, Msg* m, bool a4);
    // @ 0x95a9a0
    void __thiscall PostMsg(IWin* src, IWin* dst, const Msg* m);
    // @ 0x95aa80
    void __thiscall ProcessMessages();
    // @ 0x95add0
    void __thiscall AttachWindow(Win* w);
    // @ 0x95af00
    void __thiscall UpdateWindowCachedTransforms(Win* w);
    // @ 0x95af20
    bool __thiscall SetFocusWindow(IWin* w, ICb* cb);
    // @ 0x95b080
    bool __thiscall SetMainWindow(IWin* w, char release);
    // @ 0x95b290
    void __thiscall FlushMessageQueue();

    // callees outside this slice
    void __thiscall F959fe0(Win* w);          // 0x959fe0
    void __thiscall F9588c0(Win* w);          // 0x9588c0
    void __thiscall F958860(Win* w);          // 0x958860
    void __thiscall F958110();                // 0x958110
    void __thiscall DetachWindow(Win* w);     // 0x959e00
    bool __thiscall FCtx(Msg* m, int flag);   // 0x959780
};

struct MsgListX : MsgList {
    // @ 0x95a870
    MsgListX* __thiscall AssignFrom(MsgListX* src);
    // @ 0x95afd0
    void __thiscall Swap(MsgListX& other);
};
struct FocusListX : FocusList {
    // @ 0x95a820
    void __thiscall InsertFront(const void* value);
};

// ---------------------------------------------------------------- equiv annotations
namespace __equiv_ann {
struct Base2D {
    ~Base2D();                                                         // 0x951ba0
};
struct Builder {
    ~Builder();                                                        // 0x952f80
};
}
