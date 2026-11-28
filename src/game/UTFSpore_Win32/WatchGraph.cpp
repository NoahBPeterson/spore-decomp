// src/game/UTFSpore_Win32/WatchGraph.cpp -- migrated from slice(s) s009913d0, s00992480 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/WatchGraph.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinControls/IScrollbarDrawable.h"
#include "EA/UTFWinControls/IWinScrollbar.h"
#include <stddef.h>
#include <math.h>
#include <intrin.h>

// ---- items of slice s00992480 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
static inline u32  ld32(char* b, u32 off) { return *(u32*)(b + off); }
static inline void st32(char* b, u32 off, u32 v) { *(u32*)(b + off) = v; }
void  IntrusiveList_dtor(char* list);                                // 0x00620230
void  Obj962740_f(char* p);                                          // 0x00962740  base dtor
void  MultiHeapObject_delete(void* p);                               // 0x00951330
void  FUN_00991f90(char* p);                                         // WatchGraph::Clear
// ---- items of slice s00992480 end

// ---- items of slice s009913d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_13f18d4;  // 1e-07f          0x013f18d4
extern void* g_vtbl_1446078;   // 0x01446078  WatchGraph::vftable
extern void* g_vtbl_1445f58;   // 0x01445f58  WatchGraph::vftable (IWindow subobject)
#pragma intrinsic(fabs)
double __cdecl iat_floor(double x);                       // 0x011e0906
void __cdecl FUN_00f47380(void* p);                       // 0x00f47380  operator delete
void* __cdecl EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
void __cdecl FUN_011e0744(void* dst, void* src, unsigned int n);   // 0x011e0744 memset/memmove
void* __fastcall FUN_00962a10(void* p);                         // 0x00962a10  base Window ctor (this in ecx)
struct IWinSub { void SetFlag(unsigned int flag, unsigned char on); };  // 0x00961760  Window::SetFlag
namespace eastl {
struct intrusive_list_node_s0099_13d0 {
    intrusive_list_node_s0099_13d0* mpNext;
    intrusive_list_node_s0099_13d0* mpPrev;
};
}
namespace EA {
namespace UTFWin {
struct RectF { float left, top, right, bottom; };
}
}
namespace EA {
namespace UTFWin {
struct RenderCtx;
}
}
namespace EA {
namespace UTFWin {
struct Batch2D {
virtual void b0();
virtual void b1(int idx);
virtual void b2();
virtual void b3();
virtual void b4();
virtual void b5(float* colors);
virtual void b6();
virtual void b7();
virtual void b8();
virtual void b9();
virtual void b10();
virtual void b11();
virtual void b12();
    virtual void b13(float a, float b, float c, float d, float e);   // +0x1c
    virtual void b14(float a, float b, float c, float d);           // +0x38
};
}
}
namespace EA {
namespace UTFWin {
void End2D(RenderCtx* ctx);                                    // 0x0095bb20
}
}
namespace EA {
namespace UTFWin {
Batch2D* Begin2D_batch(RenderCtx* ctx, void* mode);            // 0x0095bc10
}
}
namespace EA {
namespace UTFWinControls {
struct __declspec(novtable) IWindow {
virtual void w0();
virtual void w1();
virtual void w2();
virtual void w3();
    virtual void w4();
    virtual void* w5();                                         // +0x14
virtual void w6();
virtual void w7();
virtual void w8();
virtual void w9();
    virtual unsigned int w10();                                 // +0x28
virtual void w11();
virtual void w12();
virtual void w13();
virtual void w14();
virtual void w15();
virtual void w16();
virtual void w17();
virtual void w18();
virtual void w19();
virtual void w20();
virtual void w21();
virtual void w22();
virtual void w23();
virtual void w24();
virtual void w25();
virtual void w26();
virtual void w27();
virtual void w28();
virtual void w29();
    virtual void w30();
    virtual void w31(int a, int b);                             // +0x7c
virtual void w32();
virtual void w33();
virtual void w34();
virtual void w35();
    virtual void w36();                                         // +0x90
virtual void w37();
virtual void w38();
virtual void w39();
virtual void w40();
virtual void w41();
virtual void w42();
virtual void w43();
virtual void w44();
    virtual void w45();
    virtual void w46(void* w);                                  // +0xb8
virtual void w47();
virtual void w48();
virtual void w49();
virtual void w50();
virtual void w51();
virtual void w52();
virtual void w53();
    virtual void w54(void* d);                                  // +0xd8
    virtual void w55();
    virtual void w56(void* d);                                  // +0xe0
};
}
}
namespace EA {
namespace UTFWinControls {
class WatchGraph { public:
    void* mpVtbl;                                               // +0x0
    IWindow mWindow;                                            // +0x4
    unsigned int pad0[0x81];                                    // +0x8 .. 0x20c
    eastl::intrusive_list_node_s0099_13d0 mChannels;                       // +0x20c
    float mSample0;                                             // +0x214
    float mSample1;                                             // +0x218
    bool mbAutoScale;                                           // +0x21c
    bool mbClip;                                                // +0x21d
    unsigned char pad1[2];                                      // +0x21e .. 0x220
    unsigned int mHistorySize;                                  // +0x220
    unsigned int mHistoryCount;                                 // +0x224

    WatchGraph();                                               // 0x00991ff0
    void Clear();                                               // 0x00991f90
    void SetHistorySize(unsigned int n);                        // 0x00992080
    void OnAreaChanged(EA::UTFWin::RectF* r);                   // 0x00992140
    bool OnRebuild(void* ctx);                                  // 0x00992180
};
}
}
using EA::UTFWinControls::WatchGraph;
using EA::UTFWinControls::IWindow;
// ---- items of slice s009913d0 end

// @ 0x00991f90
void EA::UTFWinControls::WatchGraph::Clear()
{
    eastl::intrusive_list_node_s0099_13d0* anchor = &mChannels;
    while (anchor->mpPrev != anchor) {
        eastl::intrusive_list_node_s0099_13d0* obj = anchor->mpNext ? (eastl::intrusive_list_node_s0099_13d0*)((char*)anchor->mpNext - 4) : 0;
        FUN_00f47380(*(void**)((char*)obj + 0x14));
        eastl::intrusive_list_node_s0099_13d0* first = anchor->mpNext;
        first->mpNext->mpPrev = anchor;
        anchor->mpNext = anchor->mpNext->mpNext;
        if (first != anchor) {
            first->mpPrev = 0;
            first->mpNext = 0;
        }
        (*(void(__thiscall**)(void*, int))(*(void**)obj))(obj, 1);
    }
}

// @ 0x00991ff0
EA::UTFWinControls::WatchGraph::WatchGraph()
{
    FUN_00962a10(this);
    *(void**)this = &g_vtbl_1446078;
    *(void**)((char*)this + 4) = &g_vtbl_1445f58;
    eastl::intrusive_list_node_s0099_13d0* anchor = &mChannels;
    anchor->mpPrev = anchor;
    anchor->mpNext = anchor;
    mSample0 = 0.0f;
    mSample1 = 0.0f;
    mbAutoScale = false;
    mbClip = true;
    mHistorySize = 0;
    mHistoryCount = 0;
    ((IWinSub*)((char*)this + 4))->SetFlag(0x10, 1);
    ((IWinSub*)((char*)this + 4))->SetFlag(8, 1);
}

// @ 0x00992080
void EA::UTFWinControls::WatchGraph::SetHistorySize(unsigned int n)
{
    if (n == mHistorySize)
        return;
    mHistorySize = n;
    eastl::intrusive_list_node_s0099_13d0* anchor = &mChannels;
    eastl::intrusive_list_node_s0099_13d0* it = anchor->mpNext;
    while (it != anchor) {
        eastl::intrusive_list_node_s0099_13d0* cur = it;
        it = it->mpNext;
        if (*(void**)((char*)cur + 0x14) != 0)
            FUN_00f47380(*(void**)((char*)cur + 0x14));
        if (n == 0) {
            *(void**)((char*)cur + 0x14) = 0;
        } else {
            void* p = EAAllocate(n * 4, "WatchGraph/ChannelHistory", 0, 0, 0, 0);
            *(void**)((char*)cur + 0x14) = p;
            FUN_011e0744(p, 0, n * 4);
        }
    }
    mHistoryCount = 0;
}

// @ 0x00992140
void EA::UTFWinControls::WatchGraph::OnAreaChanged(EA::UTFWin::RectF* r)
{
    int v = (int)(r->right - r->left);
    SetHistorySize((unsigned int)v);
}

// @ 0x00992180
bool EA::UTFWinControls::WatchGraph::OnRebuild(void* ctx)
{
    EA::UTFWin::RenderCtx* pCtx = (EA::UTFWin::RenderCtx*)ctx;
    EA::UTFWin::Batch2D* b = EA::UTFWin::Begin2D_batch(pCtx, 0);
    float w = *(float*)((char*)this + 0xa0) - *(float*)((char*)this + 0x98);
    float h = *(float*)((char*)this + 0xa4) - *(float*)((char*)this + 0x9c);
    b->b1(0x563d517f);
    b->b14(0.0f, 0.0f, w, h);
    b->b1(0x6e8a9dc4);
    b->b13(0.0f, 0.0f, w, h, 2.0f);
    float gap = (h - 2.0f) - 2.0f;
    float scale;
    float absSample1 = (float)fabs((double)*(float*)((char*)this + 0x218));
    if (absSample1 > g_13f18d4)
        scale = gap / *(float*)((char*)this + 0x218);
    else
        scale = 1.0f;
    float z = 0.0f;
    (void)z;
    unsigned int n = *(unsigned int*)((char*)this + 0x220);
    if ((int)(n - 4) > 0) {
        int total = (int)(n - 4);
        for (int i = 0; i < total; ++i) {
            unsigned int idx = (*(unsigned int*)((char*)this + 0x224) - (unsigned int)i) - 1;
            if ((int)idx < 0)
                idx += n;
            float top = h;
            float bot = h;
            eastl::intrusive_list_node_s0099_13d0* anchor = (eastl::intrusive_list_node_s0099_13d0*)((char*)this + 0x20c);
            eastl::intrusive_list_node_s0099_13d0* it = anchor->mpNext;
            while (it != anchor) {
                float* hist = *(float**)((char*)it + 0x14);
                float v = (float)iat_floor((double)(hist[idx] * scale + 0.5f));
                if (v > 0.0f) {
                    float y = top - v;
                    bot = y;
                    top = y;
                } else if (v < 0.0f) {
                    top = top - v;
                    bot = top;
                }
                if (*(char*)((char*)this + 0x21c) != 0) {
                    if (2.0f > bot)
                        bot = 2.0f;
                    if (top > h)
                        top = h;
                }
                if (bot < top) {
                    b->b1(*(int*)((char*)it + 0x10));
                    b->b14(h, v, v + 1.0f, top);
                }
                if (*(char*)((char*)this + 0x21d) == 0) {
                    top = h;
                    bot = h;
                }
                it = it->mpNext;
            }
        }
    }
    EA::UTFWin::End2D(pCtx);
    return true;
}

// 0x00992480 (byte-exact lifted version: match/slices/s00992480/s00992480_lifted.cpp)
u8 __fastcall WatchGraph_OnTick(char* self, int)
{
    // Rings the history buffer: for each live history node, sample the graph value into the ring
    // at index mRingIndex (self+0x224), then advance the ring and repaint.
    char* head = (char*)ld32(self, 0x20c);
    char* node = head ? head - 4 : 0;
    char* end  = (self + 0x20c) ? self + 0x20c - 4 : 0;
    while (node != end) {
        if (ld32(node, 0x14) != 0) {
            float v = (*(float(__fastcall**)(char*))(*(u32*)node + 4))(node);
            float* dest = (float*)ld32(node, 0x14);
            dest[ld32(self, 0x224)] = v;
        }
        char* next = (char*)ld32(node, 4);
        node = next ? next - 4 : 0;
    }
    u32 idx = ld32(self, 0x224) + 1;
    st32(self, 0x224, idx);
    if (idx >= ld32(self, 0x220)) st32(self, 0x224, 0);
    (*(void(__fastcall**)(char*))(*(u32*)(self + 4) + 0x90))(self + 4);
    return 1;
}

// 0x00992550 (byte-exact lifted version: match/slices/s00992550/s00992550.cpp)
void* __fastcall WatchGraph_scalarDtor(char* self, int, u8 flags)
{
    st32(self, 0, 0x1446078u);            // vtbl WatchGraph
    st32(self, 4, 0x1445f58u);
    FUN_00991f90(self);
    IntrusiveList_dtor(self + 0x20c);
    Obj962740_f(self);
    if (flags & 1) MultiHeapObject_delete(self);
    return self;
}
