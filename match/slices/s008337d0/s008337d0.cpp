// Slice s008337d0 -- texture-instance hashtable nodes + UTFWin cSPUITextWin + UI::TextZoomName.
// Region flags /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

typedef void*  (__thiscall *VFi)(void*);
typedef void   (__thiscall *VFv)(void*);
static inline void** VT(void* o) { return *(void***)o; }

extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

// ---------------------------------------------------------------- masked externs
extern char g_vtblX0;          // 0x141aabc
extern char g_vtblX4;          // 0x141aab8
extern char g_vtblEditorRes;   // 0x13eb938
extern char g_vtblImgTmp;      // 0x13ef094
extern char g_vtblPaintSystem; // 0x13eb394
extern char g_vtblContentValid;// 0x13ec458
extern char g_vtblTextWin0;    // 0x141ac90
extern char g_vtblTextWin4;    // 0x141ab70
extern char g_vtblTextWin20c;  // 0x141ab34
extern char g_vtblZoom0;       // 0x141ada8
extern char g_vtblZoom8;       // 0x141ad98
extern char g_vtblZoomC;       // 0x141ad7c
extern char g_vtblScenario;    // 0x14426a0
extern char g_vtblAnimBase;    // 0x13eb384
extern char g_vtblBehavior0;   // 0x13eb90c
extern char g_vtblBehavior1;   // 0x13eb844
extern char g_vtblAnimTmp0;    // 0x13f6400
extern char g_vtblAnimTmp1;    // 0x13f63fc
extern uint32_t g_counter164efec; // 0x164efec
extern void* g_mgr164f0e0;     // 0x164f0e0
extern uint32_t g_164f240;     // 0x164f240
extern uint32_t g_164f244;     // 0x164f244
extern uint32_t g_164f248;     // 0x164f248
extern char g_htA;             // 0x1547f54
extern void* g_htA_buckets;    // 0x1547f58
extern uint32_t g_htA_count;   // 0x1547f5c
extern uint32_t g_flagF60;     // 0x1547f60
extern char g_htB;             // 0x1547f78
extern void* g_htB_buckets;    // 0x1547f7c
extern uint32_t g_htB_count;   // 0x1547f80
extern uint32_t g_flagF84;     // 0x1547f84

extern "C" void  FUN_007f83e0(void);   // cSPUIAnimator ctor
extern "C" void  FUN_007f8c20(void);   // cSPUIAnimator dtor
extern "C" void  FUN_007f63b0(void);   // cSPUIAnimator::Update
extern "C" void  FUN_007f6340(void);   // cSPUIAnimator::Empty
extern "C" void  FUN_007f8d10(void);   // cSPUIAnimator::AddAnimation
extern "C" void  FUN_007f60d0(void);   // SmoothRamp
extern "C" void  FUN_007f7530(void);   // ShadeAlpha target
extern "C" void  FUN_007f7740(void);   // SPUICreateObjectAnimation
extern "C" void  FUN_00811000(void);   // layout ctor
extern "C" void  FUN_00811fe0(void);   // cSPUILayout dtor
extern "C" void  FUN_0080a460(void);
extern "C" void  FUN_00833840(void);
extern "C" void  FUN_008338c0(void);
extern "C" void  FUN_008339a0(void);
extern "C" void  FUN_00834220(void);
extern "C" void  FUN_00834660(void);
extern "C" void  FUN_008105b0(void);   // FindWindowByID
extern "C" void  FUN_00808d20(void);   // GetBoundingScreenRect
extern "C" void  FUN_008070d0(void);   // AnchorWindowToScreen
extern "C" void  FUN_00807340(void);   // AnchorWindowToWindow
extern "C" void  FUN_00957f30(void);   // UTFWin::GetManager
extern "C" void  FUN_009579f0(void);   // UI::Image::Image(big)
extern "C" void  FUN_00957980(void);
extern "C" void  FUN_00989000(void);   // WinText ctor
extern "C" void  FUN_0093dd80(void);
extern "C" void  FUN_0093db80(void);   // Variant::Destruct
extern "C" void  FUN_00576620(void);
extern "C" void  FUN_00ac9480(void);
extern "C" void  FUN_00b5f950(void);   // AutoRefCount::operator=
extern "C" void  FUN_008833a20(void);
extern "C" void  FUN_0088333b0(void);  // UI::Image::Image(small)
extern "C" void  FUN_0088332a0(void);  // GetWidth
extern "C" void  FUN_0088332d0(void);  // GetHeight
extern "C" void* FUN_00f473a0(void);   // EASTL allocator allocate
extern "C" void* FUN_00883860(void);   // GetServer
extern "C" void* FUN_0067dd60(void);
extern "C" void  FUN_008052f0(void);
extern "C" void  FUN_00805300(void);

// ---------------------------------------------------------------- texture node table
struct TexNode {
    uint32_t k0, k4, k8;  // +0x00 ResourceKey
    void*    value;       // +0x0c
    TexNode* next;        // +0x10
};

struct TexTable {
    uint32_t f0;          // +0x00
    void*    f4;          // +0x04
    uint32_t f8;          // +0x08
    char     pad0c[0x10];
    void*    alloc;       // +0x1c
    uint32_t f20;         // +0x20
    TexNode* CreateNode(const void* src);
    void     Clear(TexNode** buckets, uint32_t count);
};

// ---------------------------------------------------------------- manager (vtable 0x141aabc)
struct TexMgr {
    void*    vptr0;   // +0x00
    void*    vptr4;   // +0x04
    uint32_t f8;      // +0x08
    TexMgr*  Init();
    void     Dtor();
};

// ---------------------------------------------------------------- UTFWin cSPUITextWin
struct cSPUITextWin {
    void* vptr0;        // +0x000
    void* vptr4;        // +0x004
    char  pad8[0x204];
    void* vptr20c;      // +0x20c
    cSPUITextWin();
};

// ---------------------------------------------------------------- UI::TextZoomName
struct TextZoomName {
    void*    vptr0;    // +0x00
    uint32_t rc;       // +0x04
    void*    vptr8;    // +0x08
    void*    vptrC;    // +0x0c
    char     anim[0x20]; // +0x10
    char     layout[0x18]; // +0x30
    uint32_t f48, f4c, f50; // +0x48
    int32_t  f54;      // +0x54
    float    f58, f5c; // +0x58
    uint8_t  b60;      // +0x60
    char     pad61[3];
    void*    f64;      // +0x64
    void*    f68;      // +0x68
    void*    f6c;      // +0x6c
    void*    f70;      // +0x70

    TextZoomName();
    void Dtor();
    void SetActive(char active);
    void Tick(char param);
    void Recalc();
    void Anim1(int a2, int a3, int a4, int a5);
    void Anim2(int a2, int a3, int a4);
};

// `this` of the secondary (message-handler) subobject lives at object+8.
struct TextZoomMsg {
    bool HandleMessage(int msgId, void* msg);
};

struct RefWrap {
    void* vt;
    int   rc;   // +0x04
    int Release();
};

struct VWrap { void M(int a); };

// ================================================================ bodies

// @ 0x008337d0
TexNode* TexTable::CreateNode(const void* src)
{
    void* alloc = *(void**)((char*)this + 0x1c);
    TexNode* node = (TexNode*)((void* (__thiscall*)(void*, int, int, int))VT(alloc)[8 / 4])
        (alloc, 0x14, 0, *(int*)((char*)this + 0x20));
    if (node) {
        node->k0 = *(uint32_t*)((char*)src + 0);
        node->k4 = *(uint32_t*)((char*)src + 4);
        node->k8 = *(uint32_t*)((char*)src + 8);
        void* v = *(void**)((char*)src + 0xc);
        node->value = v;
        if (v)
            ((VFv)VT(v)[0 / 4])(v);
    }
    *(uint32_t*)((char*)node + 0x10) = 0;
    return node;
}

// @ 0x00833a20
void TexTable::Clear(TexNode** buckets, uint32_t count)
{
    for (uint32_t i = 0; i < count; ++i) {
        TexNode* node = buckets[i];
        while (node != 0) {
            TexNode* cur = node;
            void* v = *(void**)((char*)cur + 0xc);
            node = node->next;
            if (v)
                ((VFv)VT(v)[4 / 4])(v);
            void* alloc = *(void**)((char*)this + 0x1c);
            ((void (__thiscall*)(void*, TexNode*, int))VT(alloc)[0xc / 4])(alloc, cur, 0x14);
        }
        buckets[i] = 0;
    }
}

// @ 0x00833a80
void TexMgr::Dtor()
{
    *(void* volatile*)((char*)this + 0) = &g_vtblX0;
    *(void* volatile*)((char*)this + 4) = &g_vtblX4;
    if (--g_counter164efec == 0) {
        ((TexTable*)&g_htA)->Clear((TexNode**)g_htA_buckets, g_htA_count);
        g_flagF60 = 0;
        ((TexTable*)&g_htB)->Clear((TexNode**)g_htB_buckets, g_htB_count);
        g_flagF84 = 0;
    }
    *(void* volatile*)((char*)this + 0) = &g_vtblEditorRes;
    *(void* volatile*)((char*)this + 4) = &g_vtblImgTmp;
}

// @ 0x00833af0 (partial: hashtable find/insert wrapper)
void* FUN_00833af0(void* self, void* key)
{
    int local_1c[3];
    ((void (__cdecl*)(int*, void*))FUN_00833840)(local_1c, key);
    if (local_1c[0] != *(int*)(*(int*)((char*)self + 4) + *(int*)((char*)self + 8) * 4))
        return (char*)local_1c[0] + 0xc;
    int local_10 = *(int*)key;
    int local_c  = *(int*)((char*)key + 4);
    int local_8  = *(int*)((char*)key + 8);
    int* local_4 = 0;
    ((void (__cdecl*)(int*, int*, int*))FUN_008338c0)(local_1c, &local_10, (int*)((uint32_t)key & 0xffffff00));
    if (local_4)
        ((VFv)VT(local_4)[4 / 4])(local_4);
    return (char*)local_1c[0] + 0xc;
}

// @ 0x00833ba0 (partial)
__declspec(noinline) bool FUN_00833ba0(void* param_1, int param_2, void* param_3, float param_4, float param_5)
{
    (void)param_1; (void)param_3; (void)param_4; (void)param_5;
    g_counter164efec = g_counter164efec + (uint32_t)param_2;
    return false;
}

// @ 0x00834000
void __stdcall FUN_00834000(int a1, int a2, int a3)
{
    ((void (__stdcall*)(int, int, int, int, int))FUN_00833ba0)(a1, a2, a3, -1, -1);
}

// @ 0x00834020
cSPUITextWin::cSPUITextWin()
{
    ((VFv)FUN_00989000)(this);
    vptr0 = &g_vtblTextWin0;
    vptr4 = &g_vtblTextWin4;
    *(void**)((char*)this + 0x20c) = &g_vtblTextWin20c;
}

// @ 0x00834140
void VWrap::M(int a)
{
    void* mgr = g_mgr164f0e0;
    int v = *(int*)((char*)mgr + 0x10);
    ((void (__thiscall*)(void*, int, int))VT(this)[0x8c / 4])(this, a, v);
}

// @ 0x00834160
void TextZoomName::Dtor()
{
    *(void* volatile*)((char*)this + 0x00) = &g_vtblZoom0;
    *(void* volatile*)((char*)this + 0x08) = &g_vtblZoom8;
    *(void* volatile*)((char*)this + 0x0c) = &g_vtblZoomC;
    void* p70 = *(void* volatile*)((char*)this + 0x70);
    if (p70) ((VFv)VT(p70)[4 / 4])(p70);
    void* p6c = *(void* volatile*)((char*)this + 0x6c);
    if (p6c) ((VFv)VT(p6c)[4 / 4])(p6c);
    void* p68 = *(void* volatile*)((char*)this + 0x68);
    if (p68) ((VFv)VT(p68)[4 / 4])(p68);
    void* p64 = *(void* volatile*)((char*)this + 0x64);
    if (p64) ((VFv)VT(p64)[4 / 4])(p64);
    ((VFv)FUN_00811fe0)((char*)this + 0x30);
    ((VFv)FUN_007f8c20)((char*)this + 0x10);
    *(void* volatile*)((char*)this + 0x0c) = &g_vtblEditorRes;
    *(void* volatile*)((char*)this + 0x08) = &g_vtblPaintSystem;
    *(void* volatile*)((char*)this + 0x00) = &g_vtblContentValid;
}

// @ 0x00834200
int RefWrap::Release()
{
    int n = *(volatile int*)&rc;
    n += -1;
    *(volatile int*)&rc = n;
    if (n == 0) {
        *(volatile int*)&rc = 1;
        ((void (__thiscall*)(void*, int))VT(this)[0 / 4])(this, 1);
        n = 0;
    }
    return n;
}

// @ 0x00834220 (partial)
void TextZoomName::Recalc()
{
    // full layout/anchor pass not translated; see partial.txt
}

// @ 0x008344d0 (partial: tail-calls Recalc)
void __cdecl FUN_008344d0(int a1, uint32_t* a2, int a3, int a4, float a5)
{
    uint32_t u;
    if ((a2[4] & 0x30) == 0)
        u = -(uint32_t)(*(int16_t*)((char*)a2 + 0x12) != 0) & (uint32_t)a2;
    else
        u = *a2;
    TextZoomName* self = (TextZoomName*)u;
    void* pi = ((VFi)VT(*(void**)((char*)self + 0x64))[0x10 / 4])(*(void**)((char*)self + 0x64));
    ((VFi)VT(*(void**)((char*)self + 0x68))[0x10 / 4])(*(void**)((char*)self + 0x68));
    float f1 = *(float*)((char*)self + 0x5c);
    float f2 = *(float*)((char*)self + 0x58);
    float* r = ((float* (__thiscall*)(void*))VT(pi)[0x38 / 4])(pi);
    ((void (__thiscall*)(void*, float, float))VT(pi)[0x74 / 4])
        (pi, (f2 - f1) * a5 + f1, r[3] - r[1]);
    ((void (__thiscall*)(void*))FUN_00834220)(self);
}

// @ 0x00834560
typedef void* (__thiscall *FUN34560_Fn)(void*, int);
bool __cdecl FUN_00834560(void* p, void* unused, int mode)
{
    (void)unused;
    void* r;
    if (p != 0) {
        FUN34560_Fn f = (FUN34560_Fn)VT(p)[0xc / 4];
        r = f(p, (int)0xeeee8218);
    } else {
        r = 0;
    }
    if (mode == 0) {
        ((void (__cdecl*)(void*))FUN_008052f0)(r);
        return true;
    }
    if (mode == 1) {
        ((void (__cdecl*)(void*))FUN_00805300)(r);
    }
    return true;
}

// @ 0x008345c0
TextZoomName::TextZoomName()
{
    rc = 0;
    vptr8 = &g_vtblAnimBase;
    vptrC = &g_vtblScenario;
    vptr0 = &g_vtblZoom0;
    vptr8 = &g_vtblZoom8;
    vptrC = &g_vtblZoomC;
    ((VFv)FUN_007f83e0)((char*)this + 0x10);
    ((VFv)FUN_00811000)((char*)this + 0x30);
    f48 = g_164f240;
    f4c = g_164f244;
    f50 = g_164f248;
    f54 = 0;
    b60 = 0;
    f58 = 0.0f;
    f5c = 0.0f;
    f64 = 0;
    f68 = 0;
    f6c = 0;
    f70 = 0;
}

// @ 0x00834660
void TextZoomName::SetActive(char active)
{
    if (active == 0) {
        if (b60 != 0) {
            void* srv = FUN_00883860();
            ((void (__thiscall*)(void*, void*, int, int))VT(srv)[0x2c / 4])
                (srv, (char*)this + 8, 0x61dd1b7, -9999);
            b60 = 0;
        }
        return;
    }
    if (b60 != 0)
        return;
    void* srv = FUN_00883860();
    ((void (__thiscall*)(void*, void*, int))VT(srv)[0x20 / 4])
        (srv, (char*)this + 8, 0x61dd1b7);
    void* m = ((void* (__cdecl*)(int, const void*, int, int, int, int))FUN_00f473a0)
        (0x40, (const void*)0x13f6b3c, 0, 0, 0, 0);
    if (m) {
        *(uint32_t*)((char*)m + 0x30) = 0;
        *(void**)m = &g_vtblBehavior0;
        _InterlockedExchange((volatile long*)((char*)m + 4), 0);
        *(void**)m = &g_vtblBehavior1;
        *(uint32_t*)((char*)m + 0x38) = 0;
    }
    *(void**)((char*)m + 8) = this;
    srv = FUN_00883860();
    ((void (__thiscall*)(void*, int, void*, int, int))VT(srv)[0x18 / 4])
        (srv, 0x61dd1b7, m, 0, 0);
    b60 = 1;
}

// @ 0x00834730 (partial)
void TextZoomName::Anim1(int a2, int a3, int a4, int a5)
{
    char ramp[0x14];
    ((void (__cdecl*)(void*, int, int, int, int, int))FUN_007f60d0)(ramp, a3, 0, 0, a4, 0);
    char target[0x14];
    ((void (__cdecl*)(void*, int, int, void*))FUN_007f7530)(target, a2, a5, ramp);
    ((void (__thiscall*)(void*, void*, int, int))FUN_007f8d10)
        ((char*)this + 0x10, target, a2, 0x61ee329);
    SetActive(1);
    *(void**)(target + 0) = &g_vtblAnimTmp0;
    *(void**)(target + 8) = &g_vtblAnimTmp1;
    void* r = *(void**)(target + 0x10);
    if (r) ((VFv)VT(r)[4 / 4])(r);
    *(void**)(ramp + 0) = &g_vtblAnimTmp1;
    r = *(void**)(ramp + 4);
    if (r) ((VFv)VT(r)[4 / 4])(r);
}

// @ 0x008347f0 (partial)
void TextZoomName::Anim2(int a2, int a3, int a4)
{
    (void)a2; (void)a3; (void)a4;
    // full Variant/SPUICreateObjectAnimation path not translated; see partial.txt
}

// @ 0x00834930
void TextZoomName::Tick(char param)
{
    if (b60 != 0) {
        void* anim = (char*)this + 0x10;
        ((VFv)FUN_007f63b0)(anim);
        char e = ((char (__thiscall*)(void*))FUN_007f6340)(anim);
        ((void (__thiscall*)(void*, int))FUN_00834660)(this, e == 0);
    }
    if (param != 0 && f64 != 0) {
        void* p = ((VFi)VT(f64)[0x10 / 4])(f64);
        char c = ((char (__thiscall*)(void*))VT(p)[0x28 / 4])(p);
        if (c & 1)
            ((void (__thiscall*)(void*))FUN_00834220)(this);
    }
}

// @ 0x00834990
bool TextZoomMsg::HandleMessage(int msgId, void* msg)
{
    if (msgId == 0x61dd1b7) {
        if (*(void**)((char*)msg + 8) != (char*)this - 8)
            return false;
        if (*(uint8_t*)((char*)this + 0x58) != 0) {
            void* anim = (char*)this + 8;
            ((VFv)FUN_007f63b0)(anim);
            char e = ((char (__thiscall*)(void*))FUN_007f6340)(anim);
            ((void (__thiscall*)(void*, int))FUN_00834660)((char*)this - 8, e == 0);
        }
        void* srv = FUN_00883860();
        ((void (__thiscall*)(void*, int, void*, int, int))VT(srv)[0x18 / 4])
            (srv, 0x61dd1b7, msg, 0, 0);
    }
    return true;
}
