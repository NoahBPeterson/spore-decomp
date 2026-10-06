// Slice s008133f0 (w2g7 #1), 32-bit MSVC 2008 SP1.
// cSPUIMainWin focus/key routing, resource factory helpers, title screen.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

static inline void** Vtbl(void* o) { return *(void***)o; }

// ---------------------------------------------------------------------------
extern "C" void* __cdecl GetManager();
extern "C" void* __cdecl SP_WindowManager();
extern "C" void* __cdecl SP_CheatManager();
extern "C" void* __cdecl SP_AppSystem();
extern "C" void* __cdecl SP_MessageServer();

void* __cdecl ZoneObjectNew(int size, const char* name, int a, int b, int c, int d); // 0x926020
void* __cdecl StringManCtor(void*, void*);    // 0x999820
void  __cdecl FUN_00572680(void*);
void  __cdecl FUN_00999930();
void  __cdecl FUN_00999780(void*);
void  __cdecl FUN_00999790(void*);

struct Ref {
    virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03();
    virtual void r04(); virtual void r05(); virtual void r06(); virtual void r07();
    virtual void r08(); virtual void r09(); virtual void r0a(); virtual void r0b();
    virtual void r0c(); virtual void r0d(); virtual void r0e(); virtual void r0f();
    virtual void r10(); virtual void r11(); virtual void r12(); virtual void r13();
    virtual void r14(); virtual void r15(); virtual void r16(); virtual void r17();
    Ref* Ctor997f30();
    Ref* Ctor999c20();
};

struct Mgr {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m0a(); virtual void m0b();
    virtual void m0c(); virtual void m0d(); virtual void m0e(); virtual void m0f();
    virtual void m10(); virtual void m11();
};

// focus-controller interfaces (per call-site arg shape)
struct Y3 {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08(); virtual void a09(); virtual void a0a(); virtual void a0b();
    virtual void a0c();
    virtual bool a0d(float, float, int);   // 0x34
    virtual bool a0e(float, float, int);   // 0x38
};
struct X3 {
    virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
    virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
    virtual void b08(); virtual void b09(); virtual void b0a();
    virtual Y3*  b0b();                     // 0x2c
    virtual void b0c(); virtual void b0d();
    virtual Y3*  b0e();                     // 0x38
};
struct Y4 {
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08(); virtual void c09(); virtual void c0a(); virtual void c0b();
    virtual void c0c(); virtual void c0d();
    virtual bool c0e(int, float, float, int);  // 0x38
    virtual bool c0f(int, float, float, int);  // 0x3c
};
struct X4 {
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
    virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void d08(); virtual void d09(); virtual void d0a();
    virtual Y4*  d0b();                     // 0x2c
    virtual void d0c(); virtual void d0d();
    virtual Y4*  d0e();                     // 0x38
};

// ---------------------------------------------------------------------------
struct MainWin;
struct WinBase { void SetArea(int); };
struct WinSub : WinBase { void SetAreaNotify(int a); };

struct MainWin {
    char pad0[0x4];
    WinSub win;                 // +0x4
    char pad1[0x34 - 0x4 - sizeof(WinSub)];
    Ref*  mp34;                 // +0x34
    char pad2[0x218 - 0x38];
    uint8_t b218;               // +0x218
    int   i21c;                 // +0x21c
    uint8_t b220;               // +0x220
    uint8_t b221, b222, b223;   // +0x221..0x223
    char pad3[0x244 - 0x224];
    void* mp244;                // +0x244
    char pad4[0x268 - 0x248];
    void* mp268;                // +0x268
    void* mp26c;                // +0x26c
    char pad5[0x287 - 0x270];
    int   i287;                 // +0x287
    uint8_t b28b;               // +0x28b
    uint8_t b28c;               // +0x28c
    uint8_t b28d;               // +0x28d
    void* mp290;                // +0x290
    void* mp294;                // +0x294
    void* mp298;                // +0x298
    void* mp29c;                // +0x29c

    void UpdateMouseScale();       // 0x8131b0
    bool FocusKey2(float a, float b, int c);         // 0x813630
    bool FocusKey4(float a, float b, int c, int d);  // 0x8136b0
    bool InitHitMaskFactory();     // 0x813760
    bool InitStringFactories();    // 0x8137f0
    bool ShutdownStringFactories();// 0x8138e0
    bool InitTitleScreen();        // 0x813980
    void DoMessage(int* msg);      // 0x813e70
    bool KeyRouted(int a, int b, int c, int d);   // 0x8133f0
    bool FocusInput(int a, int b, int c, int d);  // 0x813550
};

// @ 0x00813740
void WinSub::SetAreaNotify(int a) {
    SetArea(a);
    ((MainWin*)((char*)this - 4))->UpdateMouseScale();
}

// @ 0x00813630
bool MainWin::FocusKey2(float a, float b, int c) {
    X3* p = (X3*)mp268;
    if (p && p->b0b()->a0d(a, b, c)) return true;
    X3* q = (X3*)mp26c;
    if (q && q->b0e()->a0e(a, b, c)) return true;
    return false;
}

// @ 0x008136b0
bool MainWin::FocusKey4(float a, float b, int c, int d) {
    X4* p = (X4*)mp268;
    if (p && p->d0b()->c0e(d, a, b, c)) return true;
    X4* q = (X4*)mp26c;
    if (q && q->d0e()->c0f(d, a, b, c)) return true;
    return false;
}

// ---------------------------------------------------------------------------
Ref* Ctor997f30(Ref*);   // 0x997f30
Ref* Ctor999c20(Ref*);   // 0x999c20

// @ 0x00813760
bool MainWin::InitHitMaskFactory() {
    Mgr* m = (Mgr*)GetManager();
    if (m) {
        Ref* p = (Ref*)ZoneObjectNew(8, "UI/HitMaskFactory", 0, 0, 0, 0);
        if (p) p = p->Ctor997f30();
        else p = 0;
        Ref* old = (Ref*)mp298;
        if (p != old) {
            if (p) p->r01();
            mp298 = p;
            if (old) old->r02();
        }
        if (mp298) {
            ((Ref*)mp298)->r04();
            ((void(__thiscall*)(Mgr*, int, void*, int))Vtbl(m)[0x44 / 4])(m, 1, mp298, 0);
        }
    }
    return true;
}

// @ 0x008137f0
bool MainWin::InitStringFactories() {
    Mgr* m = (Mgr*)GetManager();
    if (m) {
        Ref* p = (Ref*)ZoneObjectNew(0x10, "UI/FactoryStringTableXml", 0, 0, 0, 0);
        if (p) p = p->Ctor999c20();
        else p = 0;
        Ref* old = (Ref*)mp290;
        if (p != old) {
            if (p) p->r01();
            mp290 = p;
            if (old) old->r02();
        }
        if (mp290) {
            ((void(__thiscall*)(Mgr*, int, void*, int))Vtbl(m)[0x44 / 4])(m, 1, mp290, 0);
            char local[8];
            ((void(__thiscall*)(void*, void*, int))Vtbl(mp290)[0x2c / 4])(mp290, local, 8);
            void* sm = ZoneObjectNew(0x14, "UI/StringMan", 0, 0, 0, 0);
            if (sm) sm = StringManCtor(sm, m);
            else sm = 0;
            FUN_00572680(sm);
            FUN_00999930();
            FUN_00999780(*(void**)((char*)this + 0x29c));
        }
    }
    return true;
}

// @ 0x008138e0
bool MainWin::ShutdownStringFactories() {
    Mgr* m = (Mgr*)GetManager();
    if (mp29c) {
        FUN_00999780(0);
        FUN_00999790(mp29c);
        Ref* p = (Ref*)mp29c;
        if (p) {
            mp29c = 0;
            int n = *(int*)((char*)p + 4);
            *(int*)((char*)p + 4) = n - 1;
            if (n - 1 == 0) {
                *(int*)((char*)p + 4) = 1;
                ((void(__thiscall*)(Ref*, int))Vtbl(p)[0])(p, 1);
            }
        }
    }
    if (m && mp290) {
        ((void(__thiscall*)(Mgr*, int, void*, int))Vtbl(m)[0x44 / 4])(m, 0, mp290, 0);
        ((Ref*)mp290)->r05();
        Ref* p = (Ref*)mp290;
        if (p) { mp290 = 0; p->r02(); }
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x8133f0 / 0x813550 : key capture + focus dispatch (approximate, vcalls)
// ---------------------------------------------------------------------------
bool MainWin::KeyRouted(int a, int b, int c, int d) {
    if (b28d) return true;
    if (mp268) {
        // capture / release then route
    }
    return false;
}

bool MainWin::FocusInput(int a, int b, int c, int d) {
    if (b28d) return true;
    if (mp268) {
        void* q = ((void*(__thiscall*)(void*))Vtbl(mp268)[0x2c / 4])(mp268);
        if (q) return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// title screen
// ---------------------------------------------------------------------------
void* __cdecl CtorConnectionDialog(void*);        // 0x810000
bool  __cdecl LayoutInit(void*, const wchar_t*, int, int, int); // 0x812160
void* __cdecl LayoutFindByID(void*, int, int);    // 0x8105b0
void  __cdecl GetMainWindowArea(void*);           // 0x805ea0
void  __cdecl SP_Pollinator(void*, void*);        // 0x806d10
void* __cdecl AddBoundingBox(void*, int, int);    // 0x67cad0
void  __cdecl SP_Renderer(void*, int, int);       // 0x80d710

// @ 0x00813980  (partial: allocation/refcount/init reproduced, float sizing summarised)
bool MainWin::InitTitleScreen() {
    void* p = ZoneObjectNew(0x18, "UI/TitleScreen", 0, 0, 0, 0);
    if (p) p = CtorConnectionDialog(p);
    else p = 0;
    void* old = *(void**)((char*)this + 0x244);
    if (p != old) {
        if (p) ((Ref*)p)->r01();
        *(void**)((char*)this + 0x244) = p;
        if (old) ((Ref*)old)->r02();
    }
    void* layout = *(void**)((char*)this + 0x244);
    LayoutInit(layout, L"TitleScreen", 0x40464100, 1, 0x5b598fa);
    if (LayoutFindByID(layout, 0x362c790, 1)) {
        int area[4];
        GetMainWindowArea(area);
        void* w = LayoutFindByID(layout, 0x362c790, 1);
        ((void(__thiscall*)(void*, void*))Vtbl(w)[0x60 / 4])(w, area);
        void* w2 = LayoutFindByID(layout, 0x362d0b0, 1);
        float f = ((float(__thiscall*)(void*))Vtbl(w2)[0x34 / 4])(w2);
        (void)f;
        SP_Pollinator(w2, area);
        void* w3 = LayoutFindByID(layout, 0x362c790, 1);
        void* bb = AddBoundingBox(w3, 1, 1);
        SP_Renderer(bb, 1, 1);
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x813c20
// ---------------------------------------------------------------------------
// @ 0x00813c20
int LowerBoundUShort(int a, int b, unsigned short* key) {
    int n = b - a >> 1;
    if (n > 0) {
        int step;
        do {
            step = n >> 1;
            if (*(unsigned short*)(a + step * 2) <= *key) {
                a = a + 2 + step * 2;
                n = n + (-1 - step);
            } else {
                n = step;
            }
        } while (n > 0);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// destructor + constructor (partial)
// ---------------------------------------------------------------------------
void __cdecl SetBoolProperty(void*);            // 0x93a2e0
void __cdecl FUN_008e2b20(void*);
void __cdecl FUN_00962740(void*);
void __cdecl FUN_008a7790(void*, void*, void*);
void* __cdecl FUN_00805510();
void  __cdecl FUN_008859e0(void*, int);
void  __cdecl FUN_00900b10();
void  __cdecl FUN_00f47410();
void  __cdecl FUN_006abeb0();
void  __cdecl StopwatchCtor(void*, int, int);   // 0x93a560
void* __cdecl CtorWindowPlaceholder(void*);     // 0x962a10 UI::Window::Window

static void ReleaseSlot(void* p, int slot) {
    if (p) ((void(__thiscall*)(void*))Vtbl(p)[slot / 4])(p);
}

// @ 0x00813ca0  (partial: vtable stores + reference releases)
void MainWin_Dtor(MainWin* self) {
    char* t = (char*)self;
    *(uint32_t*)(t + 0x0) = 0x1418838;
    *(uint32_t*)(t + 0x4) = 0x1418718;
    *(uint32_t*)(t + 0x20c) = 0x1418708;
    *(uint32_t*)(t + 0x214) = 0x14186f8;
    SetBoolProperty(t + 0x228);
    ReleaseSlot(*(void**)(t + 0x2d8), 4);
    ReleaseSlot(*(void**)(t + 0x2d0), 0xc);
    FUN_008e2b20(t + 0x2a8);
    ReleaseSlot(*(void**)(t + 0x2a4), 8);
    ReleaseSlot(*(void**)(t + 0x2a0), 0xc);
    // mp29c refcount release
    void* p = *(void**)(t + 0x29c);
    if (p) {
        int n = *(int*)((char*)p + 4);
        *(int*)((char*)p + 4) = n - 1;
        if (n - 1 == 0) {
            *(int*)((char*)p + 4) = 1;
            ((void(__thiscall*)(void*, int))Vtbl(p)[0])(p, 1);
        }
    }
    ReleaseSlot(*(void**)(t + 0x298), 8);
    ReleaseSlot(*(void**)(t + 0x294), 8);
    ReleaseSlot(*(void**)(t + 0x290), 8);
    ReleaseSlot(*(void**)(t + 0x280), 4);
    ReleaseSlot(*(void**)(t + 0x27c), 8);
    ReleaseSlot(*(void**)(t + 0x274), 8);
    ReleaseSlot(*(void**)(t + 0x26c), 0xc);
    ReleaseSlot(*(void**)(t + 0x268), 4);
    ReleaseSlot(*(void**)(t + 0x244), 8);
    *(uint32_t*)(t + 0x214) = 0x13eb394;
    *(uint32_t*)(t + 0x20c) = 0x13ec458;
    FUN_00962740(t);
}

// @ 0x008141b0  (partial: field zeroing + vtable stores)
void* MainWin_Ctor(MainWin* self) {
    char* t = (char*)self;
    // base Window ctor (relocation)
    CtorWindowPlaceholder(t);
    *(uint32_t*)(t + 0x20c) = 0x13ec458;
    *(uint32_t*)(t + 0x210) = 0;
    *(uint32_t*)(t + 0x214) = 0x13eb384;
    *(uint32_t*)(t + 0x0) = 0x1418838;
    *(uint32_t*)(t + 0x4) = 0x1418718;
    *(uint32_t*)(t + 0x20c) = 0x1418708;
    *(uint32_t*)(t + 0x214) = 0x14186f8;
    *(uint8_t*)(t + 0x218) = 0;
    *(uint32_t*)(t + 0x21c) = 0;
    *(uint8_t*)(t + 0x220) = 1;
    *(uint8_t*)(t + 0x221) = 0;
    *(uint8_t*)(t + 0x222) = 0;
    *(uint8_t*)(t + 0x223) = 1;
    StopwatchCtor(t + 0x228, 5, 0);
    for (int off = 0x240; off <= 0x280; off += 4) *(uint32_t*)(t + off) = 0;
    *(uint8_t*)(t + 0x284) = 0;
    *(uint8_t*)(t + 0x285) = 0;
    *(uint8_t*)(t + 0x286) = 0;
    *(uint8_t*)(t + 0x28d) = 0;
    for (int off = 0x290; off <= 0x2a4; off += 4) *(uint32_t*)(t + off) = 0;
    return self;
}
