// Slice s00666cb0: SP::cSPUIFeedListItem (asset-browser feed item) - refresh/selection,
// constructor/destructor, mouse handling and the constructor helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"
#include <intrin.h>

// -----------------------------------------------------------------------------
// thiscall / vtable helpers
// -----------------------------------------------------------------------------
typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnVoidI)(void*, int);
typedef void  (__thiscall *FnVoidII)(void*, int, int);
typedef int   (__thiscall *FnIntV)(void*);
typedef void* (__thiscall *FnPtrV)(void*);
typedef void  (__thiscall *FnVoidIP)(void*, int, void*);
#define VT(p) (*(void***)(p))

// -----------------------------------------------------------------------------
// external callees (masked relocations - signatures only)
// -----------------------------------------------------------------------------
void* __cdecl SP_AssetBrowser();                              // 0x00401030
void* __cdecl FUN_00666b20(void* out, void* a, unsigned key); // 0x00666b20
void  __cdecl EASTL_allocator_deallocate(void* p);            // 0x00f47380
void  __cdecl FUN_00571db0(void* h, void* a, void* b, void* c, void* d); // RemoveHandler
void* __cdecl EA_Audio_GetSystemAT();                         // 0x00a206f0
void* __cdecl SP_MessageServer();                             // 0x0067dcc0
void  __cdecl SlotMessage_Destruct(void* self);               // 0x00421cf0
void  __stdcall WString_Assign(void* a, void* b);             // 0x00423650
float __cdecl FUN_004e1c70(void* a, unsigned key, float v);   // 0x004e1c70 GetPropertyT<float>

struct cSPUILayout {
    virtual void s0();
    virtual void s1();
    virtual int  Release();                        // +0x08
    void Shutdown(bool);                           // 0x00811ad0
    void* FindWindowByID(unsigned id, int flag);   // 0x008105b0
};

struct Sub158 { void init(int a, void* b); };      // 0x0066a5e0
struct P184Obj { void FUN_00829160(int v); };      // 0x00829160
struct P40Obj  { void SetCallToActionMessage(void* p); }; // 0x006455b0
struct Sub54   { unsigned char FUN_0054eac0(int v); };     // 0x0054eac0

// -----------------------------------------------------------------------------
// globals
// -----------------------------------------------------------------------------
extern float gG1a, gG1b, gG1c, gG1d;   // 0x015fae5c
extern float gG2a, gG2b, gG2c, gG2d;   // 0x01527678
extern float gG3a, gG3b, gG3c, gG3d;   // 0x015275e8
extern float g13f08c0;                 // 0x013f08c0
extern int   g14004c;                  // 0x0140042c
extern int gVt6f0_0, gVt6f0_1, gVt6f0_2, gVt6f0_3;
extern int gVt6f0_4, gVt6f0_5, gVt6f0_6;
extern int gEmptyStrA, gEmptyStrB, gEmptyStrC;
extern int gVT_base0, gVT_base1, gVT_base2;
extern int gVtbl676b0;

struct Key16 { uint32_t a, b, c, d; };

// -----------------------------------------------------------------------------
// SP::cSPUIFeedListItem
// -----------------------------------------------------------------------------
struct FeedItem {
    void       FUN_00666cb0();
    void       FUN_006673a0(bool sel);
    FeedItem*  FUN_006676b0(unsigned flags);
    FeedItem*  FUN_006676f0();
    void       FUN_006678f0();
    void       FUN_00667ac0();
    void       FUN_00667ae0();
    void       FUN_00667b00();
};

// @ 0x00666cb0  refresh the feed item's icon/thumbnail keys
void FeedItem::FUN_00666cb0() {
    void* self = this;
    void* b = SP_AssetBrowser();
    if (!b) return;
    b = SP_AssetBrowser();
    if (!*(void**)((char*)b + 0x18)) return;

    const uint8_t c3 = *(uint8_t*)((char*)self + 0xc3);
    const uint8_t c2 = *(uint8_t*)((char*)self + 0xc2);
    const uint8_t c1 = *(uint8_t*)((char*)self + 0xc1);
    const int     e  = *(int*)((char*)self + 0x13c);

    uint32_t h1, h2;
    const float* g2;
    const float* g3;
    if (c3) {
        g2 = &gG1a; g3 = &gG1a;
        if (e == 0xb) { h1 = 0x3c9e2f78; h2 = 0x29bb594b; }
        else          { h1 = 0x01374de4; h2 = 0x662e782f; }
    } else if (c2 && c1) {
        g2 = &gG2a; g3 = &gG3a;
        if (e == 0xb) { h1 = 0x2fe293fe; h2 = 0x1ebe1819; }
        else          { h1 = 0x7dfbb96a; h2 = 0x9f1eaf9d; }
    } else if (c2) {
        g2 = &gG2a; g3 = &gG3a;
        if (e == 0xb) { h1 = 0x77db09a5; h2 = 0x808686c2; }
        else          { h1 = 0x2fba3a11; h2 = 0xd2c09a86; }
    } else if (c1) {
        g2 = &gG2a; g3 = &gG3a;
        if (e == 0xb) { h1 = 0x6fe3fc19; h2 = 0xb924dfa6; }
        else          { h1 = 0x2eeb1c55; h2 = 0x5c2eddea; }
    } else {
        g2 = &gG2a; g3 = &gG3a;
        if (e == 0xb) { h1 = 0x139ac029; h2 = 0xe025f710; }
        else          { h1 = 0x6b9f30ed; h2 = 0x2695d23c; }
    }

    float tmp[4] = { g2[0], g2[1], g2[2], g2[3] };
    void* br = SP_AssetBrowser();
    void* r = FUN_00666b20(tmp, *(void**)((char*)br + 0x18), h1);
    *(Key16*)((char*)self + 0xd4) = *(Key16*)r;

    float tmp2[4] = { g3[0], g3[1], g3[2], g3[3] };
    void* br2 = SP_AssetBrowser();
    void* r2 = FUN_00666b20(tmp2, *(void**)((char*)br2 + 0x18), h2);
    *(Key16*)((char*)self + 0xf4) = *(Key16*)r2;
}

// @ 0x006673a0  SP::cSPUIFeedListItem::SetIsSelected
void FeedItem::FUN_006673a0(bool sel) {
    void* self = this;
    *(uint8_t*)((char*)self + 0xc2) = sel ? 1 : 0;
    void* b = SP_AssetBrowser();
    if (!b) return;
    b = SP_AssetBrowser();
    if (!*(void**)((char*)b + 0x18)) return;

    FUN_00666cb0();

    if (*(uint8_t*)((char*)self + 0xc2)) {
        void* p = *(void**)((char*)self + 0x40);
        void* bb = SP_AssetBrowser();
        ((P40Obj*)bb)->SetCallToActionMessage(p);
    }

    void* ecx = *(void**)((char*)self + 0xa0);
    if (!ecx) return;
    int e = *(int*)((char*)self + 0x13c);
    if (!(e == 1 || e == 2 || e == 3 || e == 0xb)) return;

    ((FnVoid)VT(ecx)[14])(ecx);

    float v = 0.0f;
    e = *(int*)((char*)self + 0x13c);
    if (e == 1 || e == 8 || e == 0xb) {
        v = FUN_004e1c70(SP_AssetBrowser(), 0x34dbde45, g13f08c0);
        void* q = *(void**)((char*)self + 0xb8);
        if (q) ((FnVoidII)VT(q)[31])(q, 1, *(uint8_t*)((char*)self + 0xc2));
    } else {
        v = FUN_004e1c70(SP_AssetBrowser(), 0xc6bcae27, g13f08c0);
    }

    void* q = *(void**)((char*)self + 0xbc);
    if (q) ((FnVoidII)VT(q)[31])(q, 1, *(uint8_t*)((char*)self + 0xc2));

    float add = *(uint8_t*)((char*)self + 0xc2) ? v : 0.0f;
    float base = *(float*)((char*)self + 0xc8);
    *(float*)((char*)self + 0xcc) = base + add;

    void* layout = *(void**)((char*)self + 0x94);
    if (!layout) return;
    void* w = ((cSPUILayout*)layout)->FindWindowByID(0x07d5f060, 1);
    if (w) {
        int flag;
        if (*(int*)((char*)self + 0x13c) == 0xb && *(uint8_t*)((char*)self + 0xc2))
            flag = 1;
        else
            flag = 0;
        ((FnVoidII)VT(w)[31])(w, 1, flag);
    }

    if (*(uint8_t*)((char*)self + 0x140)) {
        void* layout2 = *(void**)((char*)self + 0x94);
        void* w2 = ((cSPUILayout*)layout2)->FindWindowByID(0x948f0e66, 1);
        if (w2)
            ((FnVoidII)VT(w2)[31])(w2, 1, *(uint8_t*)((char*)self + 0xc2));
        void* layout3 = *(void**)((char*)self + 0x94);
        void* w3 = ((cSPUILayout*)layout3)->FindWindowByID(0xd48f0e8a, 1);
        if (!w3) return;
        ((FnVoidII)VT(w3)[31])(w3, 1, *(uint8_t*)((char*)self + 0xc2));
        return;
    }

    if (*(int*)((char*)self + 0x13c) != 0xb) {
        void* layout4 = *(void**)((char*)self + 0x94);
        void* w4 = ((cSPUILayout*)layout4)->FindWindowByID(0x748e61d2, 1);
        if (w4)
            ((FnVoidII)VT(w4)[31])(w4, 1, *(uint8_t*)((char*)self + 0xc2));
        if (*(uint32_t*)((char*)self + 0x38) | *(uint32_t*)((char*)self + 0x3c)) {
            void* layout5 = *(void**)((char*)self + 0x94);
            void* w5 = ((cSPUILayout*)layout5)->FindWindowByID(0xb48e8be4, 1);
            if (w5)
                ((FnVoidII)VT(w5)[31])(w5, 1, *(uint8_t*)((char*)self + 0xc2));
        }
        return;
    }

    void* ms = SP_MessageServer();
    void* sub = *(void**)((char*)ms + 0x58);
    unsigned char bl = ((Sub54*)sub)->FUN_0054eac0(*(int*)((char*)self + 0x134));
    void* layout6 = *(void**)((char*)self + 0x94);
    void* w6 = ((cSPUILayout*)layout6)->FindWindowByID(0x07c64218, 1);
    if (w6) {
        bool flag = *(uint8_t*)((char*)self + 0xc2) && !bl;
        ((FnVoidII)VT(w6)[31])(w6, 1, flag ? 1 : 0);
    }
    void* layout7 = *(void**)((char*)self + 0x94);
    void* w7 = ((cSPUILayout*)layout7)->FindWindowByID(0x07c64df0, 1);
    if (!w7) return;
    bool flag2 = *(uint8_t*)((char*)self + 0xc2) && bl;
    ((FnVoidII)VT(w7)[31])(w7, 1, flag2 ? 1 : 0);
}

// @ 0x006676b0  scalar deleting destructor helper
FeedItem* FeedItem::FUN_006676b0(unsigned flags) {
    void* self = this;
    void* p = *(void**)((char*)self + 4);
    if (p && *(int*)((char*)p - 4) != 0)
        EASTL_allocator_deallocate(p);
    *(void**)self = &gVtbl676b0;
    if (flags & 1)
        EASTL_allocator_deallocate(self);
    return this;
}

// @ 0x006676f0  SP::cSPUIFeedListItem constructor
FeedItem* FeedItem::FUN_006676f0() {
    void* self = this;
    *(void**)((char*)self + 4)  = &gVt6f0_4;
    *(void**)((char*)self + 8)  = &gVt6f0_5;
    *(void**)((char*)self + 0xc) = &gVt6f0_6;
    *(uint32_t*)((char*)self + 0x10) = 0;
    *(void**)self = &gVt6f0_0;
    *(void**)((char*)self + 4)  = &gVt6f0_1;
    *(void**)((char*)self + 8)  = &gVt6f0_2;
    *(void**)((char*)self + 0xc) = &gVt6f0_3;
    *(uint8_t*)((char*)self + 0x14) = 0;
    *(uint8_t*)((char*)self + 0x15) = 0;
    *(uint8_t*)((char*)self + 0x16) = 0;
    *(void**)((char*)self + 0x18) = &gEmptyStrB;
    *(void**)((char*)self + 0x1c) = &gEmptyStrB;
    *(void**)((char*)self + 0x20) = &gEmptyStrA;
    *(void**)((char*)self + 0x28) = &gEmptyStrB;
    *(void**)((char*)self + 0x2c) = &gEmptyStrB;
    *(void**)((char*)self + 0x30) = &gEmptyStrA;
    *(void**)((char*)self + 0x38) = 0;
    *(void**)((char*)self + 0x3c) = 0;
    *(void**)((char*)self + 0x40) = &gEmptyStrB;
    *(void**)((char*)self + 0x44) = &gEmptyStrB;
    *(void**)((char*)self + 0x48) = &gEmptyStrA;
    *(void**)((char*)self + 0x50) = &gEmptyStrB;
    *(void**)((char*)self + 0x54) = &gEmptyStrB;
    *(void**)((char*)self + 0x58) = &gEmptyStrC;
    *(uint32_t*)((char*)self + 0x60) = 0;
    *(uint32_t*)((char*)self + 0x64) = 0xffffffff;
    *(uint32_t*)((char*)self + 0x78) = 0;
    *(uint32_t*)((char*)self + 0x7c) = 0;
    *(uint32_t*)((char*)self + 0x80) = 0;
    *(uint8_t*)((char*)self + 0x84) = 0;
    *(uint8_t*)((char*)self + 0x85) = 0;
    *(uint8_t*)((char*)self + 0x86) = 0;
    *(uint32_t*)((char*)self + 0x88) = 0;
    *(uint32_t*)((char*)self + 0x8c) = 0;
    *(uint32_t*)((char*)self + 0x90) = 0;
    *(uint32_t*)((char*)self + 0x94) = 0;
    *(uint32_t*)((char*)self + 0x98) = 0;
    *(uint32_t*)((char*)self + 0x9c) = 0;
    *(uint32_t*)((char*)self + 0xa0) = 0;
    *(uint32_t*)((char*)self + 0xa4) = 0;
    *(uint32_t*)((char*)self + 0xa8) = 0;
    *(uint32_t*)((char*)self + 0xac) = 0;
    *(uint32_t*)((char*)self + 0xb0) = 0;
    *(uint32_t*)((char*)self + 0xb4) = 0;
    *(uint32_t*)((char*)self + 0xb8) = 0;
    *(uint32_t*)((char*)self + 0xbc) = 0;
    *(uint8_t*)((char*)self + 0xc0) = 0;
    *(uint8_t*)((char*)self + 0xc1) = 0;
    *(uint8_t*)((char*)self + 0xc2) = 0;
    *(uint8_t*)((char*)self + 0xc3) = 0;
    *(uint32_t*)((char*)self + 0xc4) = 0;
    *(uint32_t*)((char*)self + 0xc8) = 0;
    *(uint32_t*)((char*)self + 0xcc) = 0;
    *(uint32_t*)((char*)self + 0x114) = 0;
    *(uint32_t*)((char*)self + 0x118) = 0;
    *(uint32_t*)((char*)self + 0x11c) = 0;
    *(uint32_t*)((char*)self + 0x120) = 0;
    *(uint32_t*)((char*)self + 0x124) = 0;
    *(uint32_t*)((char*)self + 0x128) = 0;
    *(uint32_t*)((char*)self + 0x12c) = 0;
    *(uint32_t*)((char*)self + 0x130) = 0;
    *(uint32_t*)((char*)self + 0x134) = 0;
    *(uint32_t*)((char*)self + 0x138) = 0xffffffff;
    *(uint32_t*)((char*)self + 0x13c) = 0;
    *(uint8_t*)((char*)self + 0x140) = 0;
    *(uint8_t*)((char*)self + 0x141) = 0;
    *(uint8_t*)((char*)self + 0x142) = 0;
    *(uint32_t*)((char*)self + 0x144) = 0xffffffff;
    *(uint32_t*)((char*)self + 0x148) = 0xffffffff;
    *(uint32_t*)((char*)self + 0x14c) = 0;
    *(uint32_t*)((char*)self + 0x150) = 0;
    *(uint32_t*)((char*)self + 0x154) = 0;
    ((Sub158*)((char*)self + 0x158))->init(1, (void*)g14004c);
    *(uint32_t*)((char*)self + 0x178) = 0xffffffff;
    *(uint32_t*)((char*)self + 0x17c) = 0;
    *(uint32_t*)((char*)self + 0x180) = 0;
    *(uint32_t*)((char*)self + 0x184) = 0;
    *(uint32_t*)((char*)self + 0x188) = 0;
    return this;
}

// @ 0x006678f0  SP::cSPUIFeedListItem::~cSPUIFeedListItem
void FeedItem::FUN_006678f0() {
    void* self = this;
    *(void**)self = &gVt6f0_0;
    *(void**)((char*)self + 4)  = &gVt6f0_1;
    *(void**)((char*)self + 8)  = &gVt6f0_2;
    *(void**)((char*)self + 0xc) = &gVt6f0_3;
    _ReadWriteBarrier();

    void* p;
    p = *(void**)((char*)self + 0x184);
    if (p) ((FnVoid)VT(p)[2])(p);
    p = *(void**)((char*)self + 0x180);
    if (p) ((FnVoid)VT(p)[1])(p);
    void* h = *(void**)((char*)self + 0x114);
    if (h) {
        void* a = *(void**)((char*)self + 0x118);
        void* b = *(void**)((char*)self + 0x11c);
        void* c = *(void**)((char*)self + 0x120);
        void* d = *(void**)((char*)self + 0x124);
        *(uint32_t*)((char*)self + 0x114) = 0;
        FUN_00571db0(h, a, b, c, d);
    }
    p = *(void**)((char*)self + 0xbc);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0xb8);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0xb4);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0xb0);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0xac);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0xa8);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0xa4);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0xa0);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0x9c);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0x98);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0x94);
    if (p) ((FnVoid)VT(p)[2])(p);
    p = *(void**)((char*)self + 0x90);
    if (p) ((FnVoid)VT(p)[3])(p);

    {
        uint8_t* a = *(uint8_t**)((char*)self + 0x50);
        uint8_t* c = *(uint8_t**)((char*)self + 0x58);
        if ((int)(c - a) > 1 && a) EASTL_allocator_deallocate(a);
    }
    {
        uint8_t* a = *(uint8_t**)((char*)self + 0x40);
        uint8_t* c = *(uint8_t**)((char*)self + 0x48);
        if ((int)((c - a) & 0xfffffffe) > 2 && a) EASTL_allocator_deallocate(a);
    }
    {
        uint8_t* a = *(uint8_t**)((char*)self + 0x28);
        uint8_t* c = *(uint8_t**)((char*)self + 0x30);
        if ((int)((c - a) & 0xfffffffe) > 2 && a) EASTL_allocator_deallocate(a);
    }
    {
        uint8_t* a = *(uint8_t**)((char*)self + 0x18);
        uint8_t* c = *(uint8_t**)((char*)self + 0x20);
        if ((int)((c - a) & 0xfffffffe) > 2 && a) EASTL_allocator_deallocate(a);
    }

    *(void**)((char*)self + 0xc) = &gVT_base2;
    *(void**)((char*)self + 4)  = &gVT_base1;
    *(void**)self = &gVT_base0;
}

// @ 0x00667ac0 / 0x00667ae0
void FeedItem::FUN_00667ac0() {
    FUN_00666cb0();
    void* p = *(void**)((char*)this + 0x184);
    if (p) ((P184Obj*)p)->FUN_00829160(1);
}

void FeedItem::FUN_00667ae0() {
    FUN_00666cb0();
    void* p = *(void**)((char*)this + 0x184);
    if (p) ((P184Obj*)p)->FUN_00829160(0);
}

// @ 0x00667b00  SP::cSPUIFeedListItem::OnLeftMouseDown
struct MsgBuffer { uint32_t a, b, c, d; void* e; uint8_t f, g; };

void FeedItem::FUN_00667b00() {
    void* self = this;
    void* at = EA_Audio_GetSystemAT();
    void* r = at ? ((FnPtrV)VT(at)[8])(at) : 0;

    void* at2 = EA_Audio_GetSystemAT();
    if (at2) {
        ((FnVoidI)VT(at2)[14])(at2, 0x03475365);
        ((FnVoidII)VT(at2)[16])(at2, 0x03475381, 0x0f05a8af);
        ((FnVoidII)VT(at2)[16])(at2, 0x03475385, (int)r);
        ((FnVoid)VT(at2)[22])(at2);
    }

    void* ms = SP_MessageServer();
    MsgBuffer buf;
    buf.a = 0x0140029c;
    buf.b = 0x01400298;
    buf.c = 0;
    buf.d = 0;
    buf.e = self;
    if (self) ((FnVoid)VT(self)[0])(self);
    buf.f = 0;
    buf.g = 0;
    ((FnVoidIP)VT(ms)[5])(ms, 0xb3d53f95, &buf);

    *(uint8_t*)((char*)self + 0x142) = 0;
    void* p = *(void**)((char*)self + 0x14c);
    if (p) {
        MsgBuffer buf2;
        buf2.a = 0x013eb90c;
        buf2.b = 0x013eb844;
        buf2.d = 0;
        buf2.e = 0;
        (void)buf2;
    }

    void* q = *(void**)((char*)self + 0x184);
    if (q) ((P184Obj*)q)->FUN_00829160(1);
}

// @ 0x00667c40
void __stdcall FUN_00667c40(void** p) {
    void* b = p[1];
    void* a = p[0];
    WString_Assign(a, b);
}
