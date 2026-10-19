// Slice s008133f0 (w2g7 #1), 32-bit MSVC 2008 SP1.
// cSPUIMainWin focus/key routing, resource factory helpers, title screen.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

static inline void** Vtbl(void* o) { return *(void***)o; }

// ---------------------------------------------------------------------------
extern "C" void* __cdecl GetManager();  // 0x0067dcd0
extern "C" void* __cdecl SP_WindowManager();  // 0x0067caa0
extern "C" void* __cdecl SP_CheatManager();  // 0x0067de20
extern "C" void* __cdecl SP_AppSystem();  // 0x0067dd00
extern "C" void* __cdecl SP_MessageServer();  // 0x0067dcc0

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

struct SW {
    long long GetElapsedTimeFloat();   // 0x93a3a0
    char p0[0x14];
    float scale;                       // +0x14
    char p1[4];
};
struct MsgSrv {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void Send(uint32_t id, void* msg, int);            // 0x14
    virtual void Send4(uint32_t id, void* msg, int, int);      // 0x18
};
// SP::MessageBasicRC<5> as laid out on the stack (0x3c bytes)
struct Msg {
    void* vtbl;           // +0
    volatile long rc;     // +4
    uint32_t f08, f0c, f10, f14, f18, f1c;
    uint32_t pad20[4];
    uint32_t id;          // +0x30
    uint32_t pad34;
    uint32_t f38;         // +0x38
    uint32_t f3c;
    void Destruct();      // 0x421cf0
};
extern char vtbl_BehaviorMessage[];  // 0x13eb90c
extern char vtbl_MessageBasicRC5[];  // 0x13eb844
extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)
extern int g_DAT_01545184;           // 0x1545184
void* __cdecl OpNew(int size, const char* name, int, int, int, int);  // 0xf473a0
extern char kName_013f6b3c[];        // 0x13f6b3c
static inline MsgSrv* MS() { return (MsgSrv*)SP_MessageServer(); }
struct Fn801410 { void FUN_00801410(bool b); };  // 0x801410
void* __cdecl FUN_0067cab0();                   // 0x67cab0

// 0x8133f0/0x813550 callee shapes (per vtable slot)
struct YK1 { virtual void y00(); virtual void y01(); virtual void y02(); virtual void y03();
    virtual void y04(); virtual void y05(); virtual void y06(); virtual void y07();
    virtual void y08(); virtual void y09(); virtual void y0a();
    virtual bool y0b(int, float, float, int);   // 0x2c
    virtual bool y0c(int, float, float, int);   // 0x30
    virtual bool y0d(int, float, float, int);   // 0x34
};
struct XK1 { virtual void x00(); virtual void x01(); virtual void x02(); virtual void x03();
    virtual void x04(); virtual void x05(); virtual void x06(); virtual void x07();
    virtual void x08(); virtual void x09(); virtual void x0a();
    virtual YK1* x0b();     // 0x2c
    virtual void x0c(); virtual void x0d();
    virtual int  x0e();     // 0x38
};
struct XK2 { virtual void x00(); virtual void x01(); virtual void x02(); virtual void x03();
    virtual void x04(); virtual void x05(); virtual void x06(); virtual void x07();
    virtual void x08(); virtual void x09(); virtual void x0a(); virtual void x0b();
    virtual void x0c(); virtual void x0d();
    virtual YK1* x0e();     // 0x38
};
struct WinV { virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
    virtual void w04();
    virtual struct WinO* w05();   // 0x14
};
struct WinO { virtual void o00(); virtual void o01(); virtual void o02(); virtual void o03();
    virtual void o04(); virtual void o05(); virtual void o06(); virtual void o07();
    virtual void o08(); virtual void o09(); virtual void o0a(); virtual void o0b();
    virtual void o0c(); virtual void o0d(); virtual void o0e(); virtual void o0f();
    virtual void o10(); virtual void o11(); virtual void o12();
    virtual void o13(int, void*); };   // 0x4c

struct FocusSvc { virtual void f00(); virtual void f01(); virtual void f02(); virtual void f03();
    virtual void f04(); virtual void f05(); virtual void f06(); virtual void f07();
    virtual void f08(); virtual void f09(); virtual void f0a(); virtual void f0b();
    virtual void f0c(); virtual void f0d(); virtual void f0e(); virtual void f0f();
    virtual void f10(); virtual void f11(); virtual void f12(); virtual void f13();
    virtual void f14();
    virtual void* f15(int);               // 0x54
    virtual void  f16(int, void*);        // 0x58
    virtual void  f17(int, void*);        // 0x5c
};

struct SrcV {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual int  s08();   // 0x20
};
struct SrcO {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06();
    virtual int  s07();   // 0x1c
    virtual int  s08();   // 0x20
    virtual void s09(); virtual void s0a();
    virtual int  s0b();   // 0x2c
};
struct UIMsg {
    SrcO* src;       // +0
    int   pad4;
    uint32_t id;     // +8
    int   kind;      // +0xc
    int   p10, p14;
    void* target;    // +0x18
};

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
    char pad3[0x228 - 0x224];
    SW sw;                      // +0x228 (EA::Stopwatch, scale float at +0x14)
    void* mp244;                // +0x244
    int   i248, i24c;           // +0x248, +0x24c
    uint64_t u250, u258;        // +0x250, +0x258
    char pad4[0x268 - 0x260];
    void* mp268;                // +0x268
    void* mp26c;                // +0x26c
    char pad5[0x287 - 0x270];
    uint8_t fl[5];              // +0x287..0x28b (key-held flags)
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
    void DoMessage(UIMsg* msg);    // 0x813e70
    bool KeyRouted(float a, float b, int c, int d);   // 0x8133f0
    bool FocusInput(float a, float b, int c, int d);  // 0x813550
    static bool __stdcall KeyHandler(int, int key, int kind);  // 0x814090
    void ApplyToFocus(bool b);      // 0x813300
    void FUN_00950bb0(UIMsg* m);   // 0x950bb0
    void Dtor();                   // 0x813ca0
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
// 0x8133f0 / 0x813550 : key capture + focus dispatch
// ---------------------------------------------------------------------------
// @ 0x008133f0
bool MainWin::KeyRouted(float a, float b, int c, int d) {
    if (b28d) return true;
    WinV* w = (WinV*)&win;
    w->w05()->o13(1, w);
    w->w05()->o13(0, w);
    bool hit = false;
    if (mp268) {
        XK1* p = (XK1*)mp268;
        if (p->x0b()->y0b(c, a, b, d)) hit = true;
        else goto second;
    } else {
    second:
        if (mp26c) {
            XK2* q = (XK2*)mp26c;
            if (q->x0e()->y0c(c, a, b, d)) hit = true;
        }
    }
    if (mp268) {
        XK1* p = (XK1*)mp268;
        if (p->x0e() != g_DAT_01545184 && hit) {
            void* cur = ((FocusSvc*)mp34)->f15(1);
            if (!cur || cur == w) {
                ((FocusSvc*)mp34)->f16(1, w);
                for (int i = 0; i < 5; i++) {
                    uint8_t* f = &fl[i];
                    int key = (int)(f - (uint8_t*)this) + 0x161;
                    if (!*f) {
                        unsigned mask = 0;
                        switch (key) {
                        case 1000: mask = 8; break;
                        case 1001: mask = 0x10; break;
                        case 1002: mask = 0x20; break;
                        }
                        if (d & mask) *f = 1;
                    }
                }
            }
            return true;
        }
    }
    return false;
}

// @ 0x00813550
bool MainWin::FocusInput(float a, float b, int c, int d) {
    if (b28d) return true;
    if (mp268) {
        XK1* p = (XK1*)mp268;
        uint8_t* flags = (uint8_t*)this + c - 0x161;
        if (p->x0e() != g_DAT_01545184 && *flags) {
            *flags = 0;
            unsigned i = 0;
            do {
                if (fl[i]) goto skip;
                i++;
            } while (i < 5);
            {
                FocusSvc* f = (FocusSvc*)mp34;
                WinV* w = (WinV*)&win;
                f->f17(1, w);
            }
        }
    }
skip:
    XK1* p2 = (XK1*)mp268;
    if (p2) {
        if (p2->x0b()->y0c(c, a, b, d)) return true;
    }
    XK2* q2 = (XK2*)mp26c;
    if (q2) {
        if (q2->x0e()->y0d(c, a, b, d)) return true;
    }
    return false;
}

// @ 0x00814090
bool __stdcall MainWin::KeyHandler(int, int key, int kind) {
    if (kind == 3 && key == 0x43) {
        void* wm = SP_WindowManager();
        if (!((int(__thiscall*)(void*))Vtbl(wm)[0x84 / 4])(wm)) {
            void* cm = SP_CheatManager();
            ((void(__thiscall*)(void*, int))Vtbl(cm)[0x44 / 4])(cm, 1);
        }
        return true;
    }
    if (key == 0xd) {
        if (kind == 4) {
            void* as = SP_AppSystem();
            ((void(__thiscall*)(void*))Vtbl(as)[0x64 / 4])(as);
            MS()->Send(0x62752d3, 0, 0);
            return true;
        }
        if (kind == 5) {
            void* as = SP_AppSystem();
            ((void(__thiscall*)(void*))Vtbl(as)[0x68 / 4])(as);
            return true;
        }
    } else if (key == 0x73 && kind == 4) {
        Msg m;
        m.id = 0x657abe5;
        m.vtbl = vtbl_BehaviorMessage;
        _InterlockedExchange(&m.rc, 0);
        m.vtbl = vtbl_MessageBasicRC5;
        m.f38 = 0;
        m.f08 = 1;
        MS()->Send(m.id, &m, 0);
        if (m.f08 != 0) MS()->Send(0x153c326, 0, 0);
        m.Destruct();
    }
    return false;
}

// ---- DoMessage 0x813e70 ----
__forceinline int TruncToInt(float f) { __asm cvttss2si eax, f }
inline void* operator new(unsigned int, void* p) { return p; }
struct IM { virtual void m0(); virtual void AddRef(); virtual void Release(); };
struct MRC : IM {
    volatile long rc; uint32_t d[10]; uint32_t id; uint32_t pad34;
    __forceinline MRC(uint32_t i) : id(i) { _InterlockedExchange(&rc, 0); }
};
struct HMsg : MRC { uint32_t flags; __forceinline HMsg(uint32_t i) : MRC(i), flags(0) {} };

// @ 0x00813e70
void MainWin::DoMessage(UIMsg* msg) {
    SW* s = &sw;
    long long el = s->GetElapsedTimeFloat();
    int t = TruncToInt((float)el * s->scale);
    unsigned delta = t - i248;
    i248 = t;
    i24c = 0;
    if (delta < 0xf) u250 += delta;
    else u258 += delta;
    if (msg->id == 0x287259f6 && msg->kind != 0 && msg->src != 0) {
        void* mem = OpNew(0x40, kName_013f6b3c, 0, 0, 0, 0);
        HMsg* o = mem ? new (mem) HMsg(msg->src->s08()) : 0;
        if (mem) o->AddRef();
        o->d[0] = msg->src->s07();
        o->d[2] = msg->src->s0b();
        MS()->Send4(o->id, o, 0, 0);
        o->Release();
    }
    if (msg->id == 10) {
        if (msg->kind == 1) {
            Msg m;
            m.id = 0x255abf5;
            m.vtbl = vtbl_BehaviorMessage;
            _InterlockedExchange(&m.rc, 0);
            bool on = msg->target == (void*)&win;
            m.vtbl = vtbl_MessageBasicRC5;
            m.f08 = on ? 1u : 0u;
            m.f38 = 0;
            MS()->Send(m.id, &m, 0);
            void* p = FUN_0067cab0();
            if (p) ((Fn801410*)p)->FUN_00801410(on);
            m.Destruct();
        }
        if (msg->id == 10 && msg->kind == 0) {
            bool on = msg->target == (void*)&win;
            if (b220 && b223 != on) ApplyToFocus(on);
            b223 = on;
        }
    }
    if (mp268) {
        if (((XK1*)mp268)->x0e() != g_DAT_01545184 && msg->id == 0xb && msg->target != (void*)&win && msg->kind == 1) {
            *(int*)fl = 0;
            fl[4] = 0;
        }
    }
    FUN_00950bb0(msg);
}

// ---- Tooltip manager init 0x813b20 ----
struct TKey { uint32_t inst, type, group; };
struct TRes {
    virtual void t0(); virtual void Release(); virtual void t2();
    virtual struct TObj* Find(uint32_t id);   // 0xc
};
struct TIter { uint32_t d[2]; void Ctor(); };     // 0xb90720
struct TObj {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void Begin();                                  // 0x18
    virtual bool Next(TIter*, void** key, void** val);     // 0x1c
};
struct TMgr {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6();
    virtual int Get(TKey*, TRes** out, int, int, int, int); // 0x1c
};
void __cdecl FUN_00888480();                                // 0x888480
uint32_t __cdecl FNV1_String8(const char*, uint32_t, int);  // 0x932e80
void __cdecl FUN_00889d90(void*);                           // 0x889d90
extern char kStr_dnt[];                                     // 0x14186a4 "dnt_no_word_break_dictionary"
struct cSPUITooltipManager { static void Init(); };

// @ 0x00813b20
void cSPUITooltipManager::Init() {
    FUN_00888480();
    TRes* volatile res = 0;
    TMgr* m = (TMgr*)GetManager();
    {
        TRes* t = res;
        if (t) { res = 0; t->Release(); }
    }
    TKey key;
    key.inst = FNV1_String8(kStr_dnt, 0x811c9dc5, 1);
    key.type = 0x2fac0b6;
    key.group = 0x2fabf01;
    m->Get(&key, (TRes**)&res, 0, 0, 0, 0);
    TRes* r = res;
    if (r) {
        TObj* o = r->Find(0x30410fc);
        if (o) {
            o->Begin();
            TIter it;
            it.Ctor();
            void* k; void* v;
            while (o->Next(&it, &k, &v)) FUN_00889d90(k);
        }
        TRes* t = res;
        if (t) t->Release();
    }
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
void MainWin::Dtor() {
    char* t = (char*)this;
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
