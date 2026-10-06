// Slice s00832790 -- SPUI subtitles overlay + UTFWin cSPUISwarmEffect + UI::Image.
// Region flags /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

typedef void*  (__thiscall *VFi)(void*);
typedef void   (__thiscall *VFv)(void*);
static inline void** VT(void* o) { return *(void***)o; }

// ---------------------------------------------------------------- masked externs
extern char g_vtblSub0;       // 0x141a894
extern char g_vtblSub1;       // 0x141a884
extern char g_vtblSubTmp;     // 0x13eb384
extern char g_vtblSubWin0;    // 0x1414b10
extern char g_vtblSubWin4;    // 0x14431f8
extern char g_vtblSwarm0;     // 0x141a998
extern char g_vtblSwarm4;     // 0x141a97c
extern char g_vtblSwarmC;     // 0x141a940
extern char g_emptyStr;       // 0x1667bac
extern char g_vtblImgTmp;     // 0x13ef094
extern char g_vtblImgBase;    // 0x13eb938
extern char g_vtblImg0;       // 0x141aaa0
extern char g_vtblImg8;       // 0x141aa9c
extern char g_vtblX0;         // 0x141aabc
extern char g_vtblX4;         // 0x141aab8
extern uint32_t g_imgCounter; // 0x164efec

extern "C" void  FUN_004c1c80(void);          // string assign/reset
extern "C" void  FUN_007f8f00(void);          // animator stop
extern "C" void  FUN_008324d0(void);
extern "C" void  FUN_008326c0(void);
extern "C" void  FUN_00832e70(void);
extern "C" void  FUN_006863e0(void);          // WFixed::Append
extern "C" void  FUN_0093a560(void);          // Stopwatch ctor
extern "C" void  FUN_007f83e0(void);          // animator ctor
extern "C" void  FUN_009634c0(void);          // IWinProc::GetEventMask
extern "C" void  FUN_00963780(void);          // IWinProc::HandleUIMessage
extern "C" void  FUN_00963db0(void);          // FadeEffect ctor
extern "C" void  FUN_00980420(void);          // Navigator dtor
extern "C" void  FUN_00951330(void);          // MultiHeapObject::operator delete
extern "C" void  FUN_00f47380(void);          // EASTL allocator deallocate
extern "C" void  FUN_00b5f950(void);          // AutoRefCount::operator=
extern "C" void* FUN_009512c0(void);
extern "C" void* FUN_009512d0(void);
extern "C" void  FUN_00962a10(void);          // Window::Window
extern "C" void* FUN_0067dd10(void);          // SP::App
extern "C" void* FUN_0067ddd0(void);          // SP::EffectsManager
extern "C" void* FUN_0067dd60(void);
extern "C" void* FUN_00883860(void);          // EA::Messaging::GetServer
extern "C" void* FUN_00957510(void);
extern "C" void  FUN_007c4730(void);          // GetWorldRayFromScreenCoords
extern "C" void  FUN_007c3c90(void);
extern "C" void  FUN_0089d820(void);          // Typesetter ctor
extern "C" void  FUN_00898bd0(void);          // LineLayout ctor
extern "C" void  FUN_0089c540(void);          // Typesetter dtor
extern "C" void  FUN_008323d0(void);          // LineLayout dtor
extern "C" void  FUN_008975c0(void);
extern "C" void  FUN_0089dc00(void);
extern "C" void* FUN_00885bd0(void);          // EA::Text::GetStyleManager
extern "C" void  FUN_00894670(void);          // StyleManager::GetStyle
extern "C" void* FUN_00f473a0(void);          // EASTL allocator allocate
extern "C" void  FUN_0011e073e(void);         // operator new[]
extern "C" void  FUN_00887cde0(void);
extern "C" void  FUN_0087ce00(void);
extern "C" void  FUN_0087d070(void);
extern "C" void  FUN_0087d0b0(void);
extern "C" void  FUN_00887ced0(void);
extern "C" void  FUN_005725b0(void);
extern "C" void  FUN_0046f260(void);
extern "C" void  FUN_011ef750(void);
extern "C" void  FUN_00887cf00(void);
extern "C" void  FUN_011ef880(void);
extern "C" void  FUN_00887cef0(void);
extern "C" void  FUN_00576620(void);
extern "C" void  FUN_009579f0(void);          // UI::Image::Image(tex,...)

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement)

// ---------------------------------------------------------------- SPUI subtitles
struct Anim2 { char pad[0x20]; };

struct Subtitles {
    void*    vptr0;      // +0x00
    uint32_t rc;         // +0x04
    void*    vptr1;      // +0x08
    uint32_t f0c;        // +0x0c
    char     sw[0x18];   // +0x10 stopwatch
    float    f28;        // +0x28
    float    f2c;        // +0x2c
    float    f30;        // +0x30
    float    f34;        // +0x34
    uint8_t  b38;        // +0x38
    uint8_t  b39;        // +0x39
    char     pad3a[2];
    uint32_t f3c;        // +0x3c
    char     anim[0x20]; // +0x40
    void*    mpTextWin;  // +0x60
    void*    mpWindow;   // +0x64
    float    v68, v6c, v70, v74;   // +0x68
    float    v78, v7c, v80, v84;   // +0x78
    uint32_t s88, s8c, s90, s94, s98;  // +0x88
    wchar_t  buf[0x100]; // +0x9c

    Subtitles();
    void Clear();
    bool Set(const wchar_t* text, float a2, int a3, bool a4, float a5);
    bool SetWindow(void* window);
};

// `this` of the secondary (message-handler) subobject lives at object+8.
struct SubtitlesMsg {
    bool HandleMessage(int msgId, void* msg);
};

// ---------------------------------------------------------------- UTFWin swarm effect
struct cSPUISwarmEffect {
    void*    vptr0;         // +0x00
    void*    vptr4;         // +0x04
    uint32_t f8;            // +0x08
    void*    vptrC;         // +0x0c
    char     pad10[0x50];   // +0x10..+0x5f
    wchar_t* s60;           // +0x60
    wchar_t* s64;           // +0x64
    wchar_t* s68;           // +0x68
    uint32_t s6c;           // +0x6c
    void*    mpEffectProp;  // +0x70
    void*    mpVisualEffect;// +0x74

    cSPUISwarmEffect();
    void*  Dtor(unsigned flags);
    uint32_t GetEventMask();
    void   DoMessage(int event, void* msg);
    void   PositionSwarm(void* window);
    void   ApplyVisibility(void* p, float t);
};

// ---------------------------------------------------------------- UI::Image (0x2c)
struct UI_Image {
    void*    volatile vptr0;   // +0x00
    uint32_t f4;      // +0x04
    void*    volatile vptr8;   // +0x08
    uint32_t fc;      // +0x0c
    void*    mpImage; // +0x10
    uint32_t f14, f18, f1c, f20, f24, f28;

    UI_Image(void* img);
    void  Dtor();
};

// ---------------------------------------------------------------- misc small classes
struct ObjCaster {
    void* Cast(void* type);
};

struct RefHolder {
    char  pad[0x10];
    void* p;          // +0x10
    uint32_t GetC();
    uint32_t GetE();
};

struct Mat33 { float m[9]; };
struct Xform {
    uint16_t w0, w2;
    uint32_t f4, f8, fc;
    float    f10;
    Mat33    mat;
    void Init();
};
extern Mat33 g_m33;      // 0x164efc8
extern uint32_t g_v3[3]; // 0x164ee48

// generic reference-increment used by UI::Image
static inline void Image_AddRef(void* p) {
    if (p) {
        volatile long* rc = (volatile long*)((char*)p + 8);
        _InterlockedExchangeAdd(rc, 1);
    }
}
static inline void Image_Release(void* p) {
    if (p) {
        volatile long* rc = (volatile long*)((char*)p + 8);
        _InterlockedExchangeAdd(rc, -1);
        long cur = _InterlockedExchangeAdd(rc, 0);
        if (cur < 1) _InterlockedExchangeAdd(rc, 1);
        else         _InterlockedExchangeAdd(rc, 0);
    }
}

// ================================================================ bodies

// @ 0x00832790
void Subtitles::Clear()
{
    if (mpWindow == 0 || mpTextWin == 0)
        return;
    if (*(volatile uint32_t*)((char*)this + 0x10) | *(uint32_t*)((char*)this + 0x14))
        ((VFv)FUN_008324d0)(this);
    ((void (__thiscall*)(void*, int))FUN_004c1c80)((char*)this + 0x88, 0);
    ((VFv)FUN_007f8f00)((char*)this + 0x40);
    void* p = ((VFi)VT(mpWindow)[0x10 / 4])(mpWindow);
    ((VFv)VT(mpTextWin)[0x38 / 4])(mpTextWin);
    ((void (__thiscall*)(void*, void*))VT(mpTextWin)[0xdc / 4])(mpTextWin, p);
    void* q = ((VFi)VT(mpTextWin)[0x10 / 4])(mpTextWin);
    ((void (__thiscall*)(void*, void*))VT(q)[0xd8 / 4])(q, p);
    q = ((VFi)VT(mpTextWin)[0x10 / 4])(mpTextWin);
    ((void (__thiscall*)(void*, void*))VT(q)[0xe0 / 4])(q, mpTextWin);
    ((void (__thiscall*)(void*, float, float, float, float))VT(mpWindow)[0x38 / 4])
        (mpWindow, v78, v7c, v80, v84);
    ((void (__thiscall*)(void*, void*))VT(p)[0x6c / 4])(p, (char*)this + 0x68);
    if (mpTextWin != 0) {
        void* t = mpTextWin;
        mpTextWin = 0;
        ((VFv)VT(t)[4 / 4])(t);
    }
    if (mpWindow != 0) {
        void* t = mpWindow;
        mpWindow = 0;
        ((VFv)VT(t)[4 / 4])(t);
    }
    void* srv = FUN_00883860();
    ((void (__thiscall*)(void*, void*, int, int))VT(srv)[0x2c / 4])
        (srv, (char*)this + 8, 0x61dd1b7, -9999);
}

// @ 0x008328b0
bool SubtitlesMsg::HandleMessage(int msgId, void* msg)
{
    if (msgId == 0x61dd1b7) {
        if (*(void**)((char*)msg + 8) != (char*)this - 8)
            return false;
        ((VFv)FUN_008326c0)((char*)this - 8);
        void* srv = FUN_00883860();
        ((void (__thiscall*)(void*, int, void*, int, int))VT(srv)[0x18 / 4])
            (srv, 0x61dd1b7, msg, 0, 0);
    }
    return true;
}

// @ 0x00832900
Subtitles::Subtitles()
{
    rc = 0;
    vptr1 = &g_vtblSubTmp;
    vptr0 = &g_vtblSub0;
    vptr1 = &g_vtblSub1;
    ((void (__thiscall*)(void*, int, int))FUN_0093a560)((char*)this + 0x10, 5, 0);
    f28 = 1.0f;
    f2c = 0.0f;
    f30 = 1.0f;
    f34 = 1.0f;
    b38 = 0;
    b39 = 0;
    f3c = 0;
    ((VFv)FUN_007f83e0)((char*)this + 0x40);
    mpTextWin = 0;
    mpWindow = 0;
    s98 = (uint32_t)((char*)this + 0x9c);
    s8c = (uint32_t)((char*)this + 0x9c);
    s88 = (uint32_t)((char*)this + 0x9c);
    s90 = (uint32_t)((char*)this + 0x29c);
    *(uint16_t*)((char*)this + 0x9c) = 0;
}

// @ 0x008329b0 -- SetWindow (large; partial)
bool Subtitles::SetWindow(void* window)
{
    if (window == 0)
        return false;
    void* a = ((VFi)VT(window)[0x10 / 4])(window);
    void* b = ((VFi)VT(a)[0x10 / 4])(a);
    if (b == 0)
        return false;
    if (mpWindow == window)
        return true;
    Clear();
    ((void (__thiscall*)(void*, void*))FUN_00b5f950)((char*)this + 0x64, window);
    void* win = ((void* (__cdecl*)(int, int, const char*, void*))FUN_009512d0)
        (0x20c, 4, "UI/cSPUISubtitles", FUN_009512c0());
    if (win) {
        ((VFv)FUN_00962a10)(win);
        *(void**)win = &g_vtblSubWin0;
        *(void**)((char*)win + 4) = &g_vtblSubWin4;
    }
    void* textWin = win ? win : 0;
    ((void (__thiscall*)(void*, void*))FUN_00b5f950)((char*)this + 0x60, textWin);
    ((void (__thiscall*)(void*, int))VT(*(void**)((char*)this + 0x60))[0x5c / 4])
        (*(void**)((char*)this + 0x60), -1);
    ((void (__thiscall*)(void*, int, int))VT(*(void**)((char*)this + 0x60))[0x7c / 4])
        (*(void**)((char*)this + 0x60), 0x400, 1);
    ((void (__thiscall*)(void*, int, int))VT(*(void**)((char*)this + 0x60))[0x7c / 4])
        (*(void**)((char*)this + 0x60), 0x10, 1);
    // remaining layout/text-typesetter work: see partial.txt
    return true;
}

// @ 0x00832d50
bool Subtitles::Set(const wchar_t* text, float a2, int a3, bool a4, float a5)
{
    if (mpWindow == 0 || mpTextWin == 0)
        return false;
    if (*(volatile uint32_t*)((char*)this + 0x10) | *(uint32_t*)((char*)this + 0x14))
        ((VFv)FUN_008324d0)(this);
    f3c = a3;
    b38 = 1;
    if (text != 0)
        ((void (__thiscall*)(void*, const wchar_t*))FUN_006863e0)((char*)this + 0x88, text);
    else
        ((void (__thiscall*)(void*, int))FUN_004c1c80)((char*)this + 0x88, 0);
    f2c = a5;
    f30 = a2;
    b39 = a4;
    return true;
}

// @ 0x00832dc0
void Xform::Init()
{
    Xform* p = this;
    float one = 1.0f;
    p->mat = g_m33;
    p->f10 = one;
    p->f4 = g_v3[0];
    p->f8 = g_v3[1];
    p->fc = g_v3[2];
    p->w0 = 0;
    p->w2 = 0;
}

// @ 0x00832e10
uint32_t cSPUISwarmEffect::GetEventMask()
{
    return ((uint32_t (__thiscall*)(void*))FUN_009634c0)(this) | 0x288;
}

// @ 0x00832e70 -- PositionSwarm (partial)
void cSPUISwarmEffect::PositionSwarm(void* window)
{
    if (mpVisualEffect == 0)
        return;
    float* r = ((float* (__thiscall*)(void*))VT(window)[0x38 / 4])(window);
    float dx = (r[2] - r[0]) * 0.5f;
    float dy = (r[3] - r[1]) * 0.5f;
    float* q = ((float* (__thiscall*)(void*, float, float))VT(window)[0xc0 / 4])(window, dx, dy);
    float f1 = q[0];
    float f2 = q[1];
    void* app = FUN_0067dd10();
    void* viewer = ((VFi)VT(app)[0x50 / 4])(app);
    float p1 = 0, p2 = 0;
    viewer = ((void* (__thiscall*)(void*, float, float, float*, float*))VT(viewer)[0x1c / 4])
        (viewer, f1, f2, &p1, &p2);
    ((void (__thiscall*)(void*, float*, float*))FUN_007c4730)(viewer, &p1, &p2);
    app = FUN_0067dd10();
    viewer = ((VFi)VT(app)[0x50 / 4])(app);
    void* r2 = ((VFi)VT(viewer)[0x1c / 4])(viewer);
    float d = ((float (__thiscall*)(void*))FUN_007c3c90)(r2) + 10.0f;
    p1 += 0.0f * d;
    p2 += 0.0f * d;
    float x = p1, y = p2;
    void* vfx = mpVisualEffect;
    ((void (__thiscall*)(void*, float, float, float, float))VT(vfx)[0x18 / 4])
        (vfx, x, y + 0.0f, x + 0.0f, y);
    ((void (__thiscall*)(void*, float, float, float, float))VT(mpVisualEffect)[0x14 / 4])
        (mpVisualEffect, x, y, 0.0f, 0.0f);
}

// @ 0x00833080
void cSPUISwarmEffect::ApplyVisibility(void* p, float t)
{
    if (FUN_0067ddd0() == 0)
        return;
    if (t > 0.5f && mpVisualEffect == 0) {
        if (mpEffectProp != 0) {
            void* mgr = FUN_0067ddd0();
            char ok = ((char (__thiscall*)(void*, void*, int, void**))VT(mgr)[0x2c / 4])
                (mgr, mpEffectProp, 0, &mpVisualEffect);
            if (ok != 0) {
                PositionSwarm(p);
                ((void (__thiscall*)(void*, int))VT(mpVisualEffect)[8 / 4])(mpVisualEffect, 0);
            }
        }
        return;
    }
    if (t < 0.5f && mpVisualEffect != 0) {
        ((void (__thiscall*)(void*, int))VT(mpVisualEffect)[0xc / 4])(mpVisualEffect, 0);
        mpVisualEffect = 0;
    }
}

// @ 0x00833110
cSPUISwarmEffect::cSPUISwarmEffect()
{
    ((VFv)FUN_00963db0)(this);
    *(void* volatile*)((char*)this + 0x00) = &g_vtblSwarm0;
    *(void* volatile*)((char*)this + 0x04) = &g_vtblSwarm4;
    *(void* volatile*)((char*)this + 0x0c) = &g_vtblSwarmC;
    *(wchar_t* volatile*)((char*)this + 0x60) = (wchar_t*)&g_emptyStr;
    *(wchar_t* volatile*)((char*)this + 0x64) = (wchar_t*)&g_emptyStr;
    *(wchar_t* volatile*)((char*)this + 0x68) = (wchar_t*)&g_emptyStr + 1;
    *(void* volatile*)((char*)this + 0x70) = 0;
    *(void* volatile*)((char*)this + 0x74) = 0;
}

// @ 0x008331a0
void cSPUISwarmEffect::DoMessage(int event, void* msg)
{
    int code = *(int*)((char*)msg + 8);
    if (code == 0x12) {
        if (mpVisualEffect != 0) {
            if (FUN_0067ddd0() != 0)
                ((void (__thiscall*)(void*, int))VT(mpVisualEffect)[0xc / 4])(mpVisualEffect, 0);
        }
        mpVisualEffect = 0;
        ((void (__thiscall*)(void*, int, void*))FUN_00963780)(this, event, msg);
        return;
    }
    if (code == 0x10 || code == 0x15 || code == 0x10002)
        ((void (__thiscall*)(void*, int))FUN_00832e70)(this, event);
    ((void (__thiscall*)(void*, int, void*))FUN_00963780)(this, event, msg);
}

// @ 0x00833210
void* cSPUISwarmEffect::Dtor(unsigned flags)
{
    *(void* volatile*)((char*)this + 0x00) = &g_vtblSwarm0;
    *(void* volatile*)((char*)this + 0x04) = &g_vtblSwarm4;
    *(void* volatile*)((char*)this + 0x0c) = &g_vtblSwarmC;
    wchar_t* e = *(wchar_t* volatile*)((char*)this + 0x68);
    wchar_t* p = *(wchar_t* volatile*)((char*)this + 0x60);
    if ((((int)((char*)e - (char*)p) & ~1) > 2) && p != 0)
        ((void (__cdecl*)(void*))FUN_00f47380)(p);
    ((VFv)FUN_00980420)(this);
    if (flags & 1)
        ((void (__cdecl*)(void*))FUN_00951330)(this);
    return this;
}

// @ 0x00833270
void* ObjCaster::Cast(void* type)
{
    ObjCaster* self = this;
    if ((uint32_t)type != 0xae9cb0fa && (uint32_t)type != 0xee3f516e &&
        (uint32_t)type != 0x147d84e)
        return ((void* (__thiscall*)(void*, void*))FUN_00957510)(self, type);
    return self;
}

// @ 0x008332a0
uint32_t RefHolder::GetC()
{
    void* p = *(void**)((char*)this + 0x10);
    if ((*(uint8_t*)((char*)p + 4) & 1) == 0) {
        void* m = FUN_0067dd60();
        ((void (__thiscall*)(void*, void*))VT(m)[0x34 / 4])(m, p);
    }
    return *(uint16_t*)((char*)(*(void**)p) + 0xc);
}

// @ 0x008332d0
uint32_t RefHolder::GetE()
{
    void* p = *(void**)((char*)this + 0x10);
    if ((*(uint8_t*)((char*)p + 4) & 1) == 0) {
        void* m = FUN_0067dd60();
        ((void (__thiscall*)(void*, void*))VT(m)[0x34 / 4])(m, p);
    }
    return *(uint16_t*)((char*)(*(void**)p) + 0xe);
}

// @ 0x00833300 -- eastl hashtable rehash (nonmatching)
struct HashNode { uint32_t key; uint32_t hash; uint32_t field8; uint32_t f0c; HashNode* next; };
struct Hashtable {
    uint32_t   f0;
    HashNode** mpBuckets;   // +0x04
    uint32_t   mnElementCount; // +0x08
    char       pad0c[0x10];
    void*      mpAllocator; // +0x1c
    uint32_t   f20;         // +0x20
    void Rehash(uint32_t nNewBucketCount);
};

void Hashtable::Rehash(uint32_t nNewBucketCount)
{
    uint32_t size = nNewBucketCount * 4;
    HashNode** pNew = (HashNode**)((void* (__thiscall*)(void*, uint32_t, int, uint32_t))
        VT(mpAllocator)[8 / 4])(mpAllocator, f20, 0, size + 4);
    ((void (__cdecl*)(void*, int, uint32_t))FUN_0011e073e)(pNew, 0, size);
    *(uint32_t*)((char*)pNew + size) = 0xffffffff;
    for (uint32_t i = 0; i < mnElementCount; ++i) {
        HashNode* node = mpBuckets[i];
        while (node != 0) {
            uint32_t b = (node->hash ^ node->key) % nNewBucketCount;
            mpBuckets[i] = node->next;
            node->next = pNew[b];
            pNew[b] = node;
            node = mpBuckets[i];
        }
    }
    if (mnElementCount > 1)
        ((void (__thiscall*)(void*, HashNode**, uint32_t))VT(mpAllocator)[0xc / 4])
            (mpAllocator, mpBuckets, mnElementCount * 4 + 4);
    mpBuckets = pNew;
    mnElementCount = nNewBucketCount;
}

// @ 0x008333b0
UI_Image::UI_Image(void* img)
{
    vptr8 = &g_vtblImgTmp;
    fc = 0;
    vptr0 = &g_vtblImg0;
    vptr8 = &g_vtblImg8;
    mpImage = img;
    if (img != 0) {
        volatile long* rc = (volatile long*)((char*)img + 8);
        _InterlockedIncrement((volatile long*)rc);
    }
    f4 = 0;
}

// @ 0x00833400
void UI_Image::Dtor()
{
    *(void* volatile*)((char*)this + 0x00) = &g_vtblImg0;
    *(void* volatile*)((char*)this + 0x08) = &g_vtblImg8;
    void* p = *(void* volatile*)((char*)this + 0x10);
    if (p != 0) {
        volatile long* rc = (volatile long*)((char*)p + 8);
        _InterlockedExchangeAdd(rc, -1);
        if (_InterlockedExchangeAdd(rc, 0) < 1)
            _InterlockedExchangeAdd(rc, 1);
        else
            _InterlockedExchangeAdd(rc, 0);
    }
    *(void* volatile*)((char*)this + 0x08) = &g_vtblImgTmp;
    *(void* volatile*)((char*)this + 0x00) = &g_vtblImgBase;
}

// @ 0x00833460 -- UI::Image::GetImage(filename) (partial)
struct ImageReq { char pad[0x34]; };
bool UI_Image_GetImage(ImageReq* out, void* out2, void* req)
{
    const char* name = *(const char**)((char*)req + 0x10);
    if (name == 0 || name[0] != 'i' || name[1] != 'm' || name[2] != 'a' || name[3] != 'g' ||
        name[4] != 'e' || name[5] != '/')
        return false;
    // full loader (extension match + texture manager lookup) not reproduced; see partial.txt
    (void)out; (void)out2;
    return false;
}

// @ 0x00833790
struct ImageAux {
    void*    vptr0;   // +0x00
    void*    vptr4;   // +0x04
    uint32_t f8;      // +0x08
    ImageAux* Init();
};
ImageAux* ImageAux::Init()
{
    ImageAux* self = this;
    *(void* volatile*)((char*)self + 0x04) = &g_vtblImgTmp;
    *(uint32_t*)((char*)self + 0x08) = 0;
    *(void* volatile*)((char*)self + 0x00) = &g_vtblX0;
    *(void* volatile*)((char*)self + 0x04) = &g_vtblX4;
    ++g_imgCounter;
    return self;
}
