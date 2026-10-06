// Slice s008124a0 (w2g7 #0), 32-bit MSVC 2008 SP1.
// UI module: cSPUILayoutZoom, cSPUILayoutCheat, cSPUIMainWin and helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

// ===========================================================================
// generic vtable stubs
// ===========================================================================
struct Mouse;
struct Rect4f { float x0, y0, x1, y1; };
struct Rect4i { int x0, y0, x1, y1; };

// cSPUIMainWin+4 subobject (IWindow-ish).  slots 5 (0x14) and 13 (0x34) used.
struct Sub {
    virtual void   s00();
    virtual void   s01();
    virtual void   s02();
    virtual void   s03();
    virtual void   s04();
    virtual Mouse* s05();
    virtual void   s06();
    virtual void   s07();
    virtual void   s08();
    virtual void   s09();
    virtual void   s0a();
    virtual void   s0b();
    virtual void   s0c();
    virtual Rect4f* s0d();
};

// Refcounted control interface used for cSPUIMainWin+0x268 / +0x26c.
// slots: 0,1,2,3, 11 (0x2c)->Y*, 14 (0x38)->Y*, 20 (0x50)->X*
struct Y {
    virtual void y00(); virtual void y01(); virtual void y02(); virtual void y03();
    virtual void y04(); virtual void y05(); virtual void y06(); virtual void y07();
    virtual void y08(int);          // 0x20
    virtual void y09(int);          // 0x24
    virtual bool y10(int, int);     // 0x28
    virtual bool y11(int, int);     // 0x2c
};
struct X {
    virtual void x00(); virtual void x01(); virtual void x02(); virtual void x03();
    virtual void x04(); virtual void x05(); virtual void x06(); virtual void x07();
    virtual void x08(); virtual void x09(); virtual void x0a();
    virtual Y*   x0b();
    virtual void x0c(); virtual void x0d();
    virtual Y*   x0e();
    virtual void x0f(); virtual void x10(); virtual void x11(); virtual void x12();
    virtual void x13();
    virtual X*   x14();
};

// cSPUILayoutZoom input window: slot 4 (0x10)->ZoomWin*, 13 (0x34)->float*, 14 (0x38)->float*
struct ZoomWin {
    virtual void z00(); virtual void z01(); virtual void z02(); virtual void z03();
    virtual ZoomWin* z04();
    virtual void z05(); virtual void z06(); virtual void z07(); virtual void z08();
    virtual void z09(); virtual void z0a(); virtual void z0b(); virtual void z0c();
    virtual float* z0d();
    virtual float* z0e();
};

// 10-slot stub for cSPUIMainWin+0x260.
struct W9 {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
    virtual void w4(); virtual void w5(); virtual void w6(); virtual void w7();
    virtual void w8(); virtual void w9();
};

// 32-slot Canvas interface (slots 15 and 31 used).
struct Canvas {
    virtual void  c00(); virtual void  c01(); virtual void  c02(); virtual void  c03();
    virtual void  c04(); virtual void  c05(); virtual void  c06(); virtual void  c07();
    virtual void  c08(); virtual void  c09(); virtual void  c10(); virtual void  c11();
    virtual void  c12(); virtual void  c13(); virtual void  c14(); virtual void* c15(void*);
    virtual void  c16(); virtual void  c17(); virtual void  c18(); virtual void  c19();
    virtual void  c20(); virtual void  c21(); virtual void  c22(); virtual void  c23();
    virtual void  c24(); virtual void  c25(); virtual void  c26(); virtual void  c27();
    virtual void  c28(); virtual void  c29(); virtual void  c30(); virtual void  c31(int, int);
};

// 13-slot stub for the mouse-message dispatch target.
struct Q12 {
    virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3();
    virtual void q4(); virtual void q5(); virtual void q6(); virtual void q7();
    virtual void q8(); virtual void q9(); virtual void q10(); virtual void q11();
    virtual void q12(int, int, int);
};

extern "C" Canvas* SP_Canvas();
extern "C" void*   SP_MessageServer();
extern "C" void*   SP_CheatManager();

#define sMouseXScale (*(float*)0x15451e8)
#define sMouseYScale (*(float*)0x15451ec)

// ===========================================================================
// cSPUILayoutZoom  (vtable 0x01418518, size 0x44)
// ===========================================================================
struct Vector4 { float x, y, z, w; };

struct ZoomBase {
    void SetStyleWindow(int);
};

struct Zoom : ZoomBase {
    char pad0[0x10];
    float m10, m14, m18, m1c;   // +0x10 mMyArea
    float m20, m24, m28, m2c;   // +0x20 mMyPhysicalArea
    float m30, m34, m38, m3c;   // +0x30 mRelArea
    void* mpMyWindow;           // +0x40

    Zoom();
    void SetWindow(void* p);
    void Transform(const float* r, float* out);
    bool Init(ZoomWin* p);
};

// @ 0x00812b70
Zoom::Zoom() {
    *(uint32_t*)((char*)this + 0x4) = 0x13fa72c;
    *(int*)((char*)this + 0x8) = 0;
    *(uint32_t*)((char*)this + 0xc) = 0x14426a0;
    *(uint32_t*)((char*)this + 0x0) = 0x1418518;
    *(uint32_t*)((char*)this + 0x4) = 0x1418500;
    *(uint32_t*)((char*)this + 0xc) = 0x14184e4;
    m10 = m14 = m18 = m1c = 0.0f;
    m20 = m24 = m28 = m2c = 0.0f;
    m30 = m34 = 0.0f;
    m38 = m3c = 1.0f;
    mpMyWindow = 0;
}

// @ 0x00812a10
void Zoom::SetWindow(void* p) {
    mpMyWindow = p;
    SetStyleWindow((int)p);
}

// @ 0x00812a20
void Zoom::Transform(const float* r, float* out) {
    out[0] = (r[2] - r[0]) * m24;
    out[2] = (r[2] - r[0]) * m2c;
    out[1] = (r[3] - r[1]) * m28;
    out[3] = (r[3] - r[1]) * m30;
}

// @ 0x00812aa0
bool Zoom::Init(ZoomWin* p) {
    mpMyWindow = p;
    if (p->z04()) {
        float* r = p->z0d();
        m10 = r[0]; m14 = r[1]; m18 = r[2]; m1c = r[3];
        float* s = p->z04()->z0e();
        float f = s[2] - s[0];
        if (f < 1.0f) f = 1.0f;
        m30 = m10 * (1.0f / f);
        m38 = m18 * (1.0f / f);
        float g = s[3] - s[1];
        if (g < 1.0f) g = 1.0f;
        m34 = m14 * (1.0f / g);
        m3c = m1c * (1.0f / g);
    }
    return false;
}

// ===========================================================================
// cSPUIMainWin-ish container
// ===========================================================================
struct MainWin {
    char pad0[0x4];
    Sub  sub;                   // +0x4
    char pad1[0x260 - 0x4 - sizeof(Sub)];
    W9*  mp260;                 // +0x260
    char pad2[0x268 - 0x260 - 4];
    X*   mp268;                 // +0x268
    X*   mp26c;                 // +0x26c
    char pad3[0x284 - 0x26c - 4];
    uint8_t b284, b285, b286;   // +0x284
    char pad4[0x28d - 0x287];
    uint8_t b28d;               // +0x28d
    char pad5[0x2dc - 0x28e];
    uint8_t b2dc;               // +0x2dc

    void BaseSetup();
    unsigned GetFlags();
    void Teardown(int);
    bool BuildMouseMsg(const void* in, void* out);
    void OnMouse(bool active);
    void UpdateMouseScale();
    void SetFocusObj(X* p);
    void ApplyToFocus(int arg);
    bool RouteKey(int a, int key, int mod);
};

// @ 0x00812c30
__declspec(noinline) unsigned MainWin::GetFlags() {
    unsigned r = 0;
    if (b284) r = 8;
    if (b285) r |= 0x10;
    if (b286) r |= 0x20;
    return r;
}

// @ 0x00812c60  (free)
__declspec(noinline) unsigned MapFlags(unsigned char f) {
    unsigned r = 0;
    if (f & 1) r = 1;
    if (f & 2) r |= 2;
    if (f & 0x1c) r |= 4;
    return r;
}

// @ 0x00812d30
void MainWin::Teardown(int) {
    BaseSetup();
    if (mp260) mp260->w9();
}

// @ 0x00812db0
bool MainWin::BuildMouseMsg(const void* pin, void* pout) {
    const char* in = (const char*)pin;
    char* out = (char*)pout;
    uint32_t type = *(uint32_t*)(in + 8);
    switch (type) {
    case 1:
        *(int*)(out + 8) = (*(uint8_t*)(in + 0x11) == 0) + 1;
        *(int*)(out + 0xc) = 0;
        *(int*)(out + 0x10) = *(int*)(in + 0xc);
        *(unsigned*)(out + 0x14) = MapFlags(*(uint8_t*)(in + 0x10));
        if (*(uint16_t*)(in + 0x12) > 1) *(unsigned*)(out + 0x14) |= 0x40;
        return true;
    case 2:
        *(int*)(out + 8) = 5;
        *(int*)(out + 0xc) = 0;
        *(int*)(out + 0x10) = *(int*)(in + 0xc);
        *(unsigned*)(out + 0x14) = MapFlags(*(uint8_t*)(in + 0x10));
        return true;
    case 3: {
        int v = 1;
        if (*(float*)(in + 0x10) <= 0.5f) v = 2;
        *(int*)(out + 8) = v;
        *(int*)(out + 0xc) = *(int*)(in + 4) + 2;
        *(int*)(out + 0x10) = *(int*)(in + 0xc);
        *(int*)(out + 0x14) = 0;
        return true;
    }
    case 5:
        *(int*)(out + 8) = (*(uint8_t*)(in + 0x10) == 0) + 6;
        *(float*)(out + 0xc) = (float)*(int*)(in + 0x14) * sMouseXScale;
        *(float*)(out + 0x10) = (float)*(int*)(in + 0x18) * sMouseYScale;
        *(int*)(out + 0x18) = *(int*)(in + 0xc);
        break;
    case 6:
        *(int*)(out + 8) = 9;
        *(float*)(out + 0xc) = (float)*(int*)(in + 0x14) * sMouseXScale;
        *(float*)(out + 0x10) = (float)*(int*)(in + 0x18) * sMouseYScale;
        *(int*)(out + 0x18) = *(int*)(in + 0xc);
        break;
    case 7:
        *(int*)(out + 8) = 8;
        *(float*)(out + 0xc) = (float)*(int*)(in + 0xc) * sMouseXScale;
        *(float*)(out + 0x10) = (float)*(int*)(in + 0x10) * sMouseYScale;
        break;
    default:
        return false;
    }
    unsigned flags = MapFlags(*(uint8_t*)(in + 0x1c));
    flags |= GetFlags();
    *(unsigned*)(out + 0x14) = flags;
    return true;
}

// @ 0x00812d00  (free, __cdecl, 3 args)
bool __cdecl DispatchMouseMsg(void*, void* p, Q12* q) {
    if (*(int*)((char*)p + 8) == 6)
        q->q12(0, 0xc0, 0);
    return false;
}

// ===========================================================================
// messages / canvas helpers
// ===========================================================================
struct Mouse {
    void GetPositionStatic(int, int);
};

// @ 0x008130c0  cSPUIMainWin::GetMousePosition
void MainWin::OnMouse(bool active) {
    if (active) {
        if (b2dc) return;
        b2dc = 1;
        void* s = SP_MessageServer();
        typedef void (__thiscall *MsgSendFn)(void*, unsigned, int, int, int);
        ((MsgSendFn*)(*(void**)s))[0x18 / 4](s, 0x61205e6, 0, 0, 0);
        return;
    }
    if (sub.s05()) {
        Mouse* m = sub.s05();
        m->GetPositionStatic(0, 0);
    }
}

// @ 0x008131b0  cSPUIMainWin::UpdateMouseScale
void MainWin::UpdateMouseScale() {
    Rect4i local;
    Canvas* c = SP_Canvas();
    Rect4i* r = (Rect4i*)c->c15(&local);
    sMouseXScale = (float)(r->x1 - r->x0);
    if (sMouseXScale > 0.0f) {
        Rect4f* s = sub.s0d();
        sMouseXScale = (s->x1 - s->x0) / sMouseXScale;
    }
    Canvas* c2 = SP_Canvas();
    Rect4i* r2 = (Rect4i*)c2->c15(&local);
    sMouseYScale = (float)(r2->y1 - r2->y0);
    if (sMouseYScale > 0.0f) {
        Rect4f* s = sub.s0d();
        sMouseYScale = (s->y1 - s->y0) / sMouseYScale;
    }
}

// @ 0x00813260
void MainWin::SetFocusObj(X* p) {
    X* old = mp268;
    if (p != old) {
        if (p) p->x00();
        mp268 = p;
        if (old) old->x01();
    }
    if (mp268 != 0) {
        X* q = mp268->x14();
        X* o = mp26c;
        if (q != o) {
            if (q) q->x02();
            mp26c = q;
            if (o) o->x03();
        }
    } else {
        X* o = mp26c;
        if (o) { mp26c = 0; o->x03(); }
    }
}

// @ 0x00813300
void MainWin::ApplyToFocus(int arg) {
    X* p = mp268;
    if (p && p->x0b()) {
        p->x0b()->y08(arg);
    }
    X* o = mp26c;
    if (o && p && p->x14()) {
        o->x0e()->y09(arg);
    }
}

// @ 0x00813370
bool MainWin::RouteKey(int, int key, int mod) {
    if (b28d) return true;
    if (mod == 0 && (key == 0x43 || key == 0x56)) return true;
    if (mp268) {
        if (mp268->x0b()->y10(key, mod)) return true;
    }
    if (mp26c) {
        if (mp26c->x0e()->y11(key, mod)) return true;
    }
    return false;
}

// @ 0x00812c90  (free, partial: simplified message envelope)
struct MsgEnv {
    uint32_t id;
    Canvas* canvas;
    void* p;
    uint32_t payload[8];
};

void __cdecl PostMouseEdgeMsg(void* data) {
    Canvas* c = SP_Canvas();
    if (!c || !data) return;
    MsgEnv msg;
    msg.canvas = c;
    msg.p = 0;
    for (int i = 0; i < 8; ++i) msg.payload[i] = ((uint32_t*)data)[i];
    msg.id = 0x1ee1001;
    msg.p = &msg.payload;
    void* s = SP_MessageServer();
    typedef void (__thiscall *MsgPostFn)(void*, uint32_t, void*, int);
    if (s)
        ((MsgPostFn*)(*(void**)s))[0x14 / 4](s, msg.id, &msg, 0);
}

// @ 0x00812f70
void __cdecl FUN_008d2f30(int*, int*);

void __stdcall GetScaledMouse(float* p1, float* p2) {
    int l1, l2;
    FUN_008d2f30(&l1, &l2);
    Rect4i r;
    Canvas* c = SP_Canvas();
    int* q1 = (int*)c->c15(&r);
    l1 -= q1[0];
    Canvas* c2 = SP_Canvas();
    int* q2 = (int*)c2->c15(&r);
    l2 -= q2[1];
    float fx = (float)l1 * sMouseXScale;
    *(float*)p1 = fx;
    float fy = (float)l2 * sMouseYScale;
    *(float*)p2 = fy;
}

// @ 0x00812ff0
void __stdcall ScreenToClient(float x, float y) {
    x /= sMouseXScale;
    y /= sMouseYScale;
    Canvas* c = SP_Canvas();
    int ix = (int)x;
    int iy = (int)y;
    c->c31(ix, iy);
}

// @ 0x00813040
void __stdcall ScaleXY(float x, float y, float* px, float* py) {
    *px = sMouseXScale * x;
    *py = sMouseYScale * y;
}

// ===========================================================================
// stopwatch helper
// ===========================================================================
struct Stopwatch {
    char pad[0x14];
    float mScale;                    // +0x14
    int64_t GetElapsedTimeFloat();   // 0x93a3a0
};

struct MainWinTimer {
    char pad[0x228];
    Stopwatch mTimer;                // +0x228
    float GetScaledElapsed();
};

// @ 0x00813070
float MainWinTimer::GetScaledElapsed() {
    Stopwatch* t = &mTimer;
    return (float)t->GetElapsedTimeFloat() * t->mScale;
}

// @ 0x008130a0
struct AutoRefPair {
    char pad[0x250];
    uint32_t lo, hi;
    uint64_t Get();
};
uint64_t AutoRefPair::Get() { return *(uint64_t*)&lo; }

// ===========================================================================
// drop shadow quality init
// ===========================================================================
struct Property {
    char pad[0x12];
    uint16_t type;      // +0x12
    int* GetInt();
};
struct cDirectPropertyList {
    virtual bool p0(void*); virtual bool p1(void*); virtual bool p2(void*);
    virtual bool p3(void*); virtual bool p4(void*); virtual bool p5(void*);
    virtual bool p6(void*); virtual bool p7(void*); virtual bool p8(void*);
    virtual bool GetProp(uint32_t id, Property* out);
};
extern cDirectPropertyList* g_AppProperties;             // 0x15fd918
void __cdecl SetDropShadowQuality(int q, int level);     // 0x96e500

// @ 0x00813120
void sInitDropShadowQuality() {
    cDirectPropertyList* props = g_AppProperties;
    Property p;
    int q = 0;
    if (props && props->GetProp(0xe30a842c, &p) && p.type == 9)
        q = *p.GetInt();
    SetDropShadowQuality(q, 0);
    if (props && props->GetProp(0xa5bbb508, &p) && p.type == 9)
        q = *p.GetInt();
    SetDropShadowQuality(q, 1);
}

// ===========================================================================
// cSPUILayoutCheat + ArgScript
// ===========================================================================
namespace EA { namespace ArgScript {
struct cArguments {
    void  MainArguments(int);
    int   NumArguments();
    char* OptionArguments(const char* name, int a, int b, int c);
    char* OptionArguments(const char* name, int a);
    bool  HasFlag(const char* name);
};
struct cCommandBase {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual ~cCommandBase();
    char* mParser;      // +4
    int   mRefCount;    // +8
    void* mState;       // +0xc
};
} }
using EA::ArgScript::cArguments;
using EA::ArgScript::cCommandBase;

// Minimal EASTL-like map; the destructor nukes the tree rooted at +0xc.
struct LayoutMap {
    char pad0[0x0c];
    void* mRoot;         // +0xc
    char pad1[0x1c - 0x10];
    void DoNukeSubtree(void* root);
    ~LayoutMap();
};
inline LayoutMap::~LayoutMap() { DoNukeSubtree(mRoot); }

struct cSPUILayoutCheat : cCommandBase {
    LayoutMap mLayouts;                 // +0x10
    cSPUILayoutCheat();
    void Execute(cArguments* args);
};

extern "C" void EA_ArgScript_Output(char* parser, const char* fmt, ...);

cSPUILayoutCheat::cSPUILayoutCheat() {
    mParser = 0;
    mRefCount = 0;
    mState = 0;
    *(void**)((char*)this + 0x14) = (char*)this + 0x14;
    *(void**)((char*)this + 0x18) = (char*)this + 0x14;
    *(int*)((char*)this + 0x1c) = 0;
    *(uint8_t*)((char*)this + 0x20) = 0;
    *(int*)((char*)this + 0x24) = 0;
}

// @ 0x00812990  scalar deleting destructor (implicit virtual dtor)

// @ 0x008124a0  (partial: main paths only)
void cSPUILayoutCheat::Execute(cArguments* args) {
    args->MainArguments(0);
    int n = args->NumArguments();
    if (n < 2) {
        EA_ArgScript_Output(mParser, "List of loaded UI layouts:\n");
        return;
    }
    char* load = args->OptionArguments("load", 1, 3, 0);
    if (load) {
        return;
    }
    char* unload = args->OptionArguments("unload", 1);
    if (unload) {
        return;
    }
    if (args->HasFlag("textures")) {
        SP_CheatManager();
    }
}

// @ 0x008129c0
void RegisterLayoutCheat() {
    cSPUILayoutCheat* p = new cSPUILayoutCheat();
    (void)p;
    SP_CheatManager();
}
