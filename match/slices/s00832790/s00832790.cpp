// Slice s00832790 -- SPUI subtitles overlay + UTFWin cSPUISwarmEffect + UI::Image.
// Region flags /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.

// math.h with a plain (non-dllimport) floor(): calls go through the local CRT thunk 0x011e0906.
#define _CRTIMP
#include <math.h>
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
extern char g_vtblMsg0;       // 0x13eb90c  (UI::BehaviorMessage)
extern char g_vtblMsg1;       // 0x13eb844
extern char g_allocTag;       // 0x13f6b3c  EASTL allocator name
extern char g_allocTagImg;    // 0x13ffd40  "UI/Image"

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
extern "C" void* __cdecl FUN_00f473a0(uint32_t size, const char* name, int a, int b, int c, int d); // EASTL allocator
extern "C" void  FUN_0011e073e(void);         // operator new[]
extern "C" int   memcmp(const void*, const void*, unsigned);
extern "C" int   strcmp(const char*, const char*);
extern "C" void* __cdecl FUN_009579f0(void);  // UI image-view ctor (thiscall); see call site

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedExchange)

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
class cSPUISwarmEffect { public:
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
    static int __stdcall GetImage(void* out1, void* out2, void* req);
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

struct Rect { float left, top, right, bottom; };

// ---------------------------------------------------------------- image file loading
struct HeaderFileInfo {
    uint32_t pad[4];
    uint32_t width;    // +0x10
    uint32_t height;   // +0x14
    uint32_t bpp;      // +0x18
};

struct HeaderReader {                                 // opaque DDS/header stream
    uint32_t pad[5];
    HeaderReader();                                    // 0x0087cde0
    ~HeaderReader();                                   // 0x0087d070
    bool Open(void* p);                                // 0x0087ce00
    bool Get(int kind, uint32_t* count);               // 0x0087d0b0
    HeaderFileInfo* Item(int idx);                     // 0x0087ced0
    void Free(void* p);                                // 0x0087cef0
    bool Read(HeaderFileInfo* info, void* dst, uint32_t n);  // 0x0087cf00
};

struct ImageResObj {                                   // raster resource object
    void*    mpPixels;   // +0x00
    uint32_t mFlags;     // +0x04
    void* GetPixels();                                 // 0x0046f260
};

struct ImageResPtr {                                   // atomic refcounted pointer to ImageResObj
    ImageResObj* mpObject;   // +0x00
    ImageResPtr(ImageResObj* x);                       // 0x005725b0
    ~ImageResPtr();                                    // 0x00576620
};

struct TextureInstance {                               // cTextureInstanceWrapper
    uint32_t f0, f4, f8;
    uint16_t width;    // +0x0c
    uint16_t height;   // +0x0e
    int  Lock(int mode, int z, void** out);            // 0x011ef750
    void Unlock(void** out);                           // 0x011ef880
};

struct ImageLockInfo { void* mpData; uint32_t f4, f8; uint32_t cbData; };

extern const char* g_pszImageBmp;    // 0x01547df4  "image/bmp"
extern const char* g_pszImageGif;    // 0x01547df8  "image/gif"
extern const char* g_pszImageJpeg;   // 0x01547dfc  "image/jpeg"
extern const char* g_pszImagePng;    // 0x01547e00  "image/png"
extern const char* g_pszImageTarga;  // 0x01547e04  "image/targa"

inline void* operator new(unsigned int, void* p) { return p; }

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

// @ 0x008329b0
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
    ((void (__thiscall*)(void*, void*))FUN_00b5f950)((char*)this + 0x60, win);
    void* tw = *(void**)((char*)this + 0x60);
    ((void (__thiscall*)(void*, int))VT(tw)[0x5c / 4])(tw, -1);
    ((void (__thiscall*)(void*, int, int))VT(tw)[0x7c / 4])(tw, 0x400, 1);
    ((void (__thiscall*)(void*, int, int))VT(tw)[0x7c / 4])(tw, 0x10, 1);

    void* c = ((VFi)VT(mpWindow)[0x10 / 4])(mpWindow);
    float* r = ((float* (__thiscall*)(void*))VT(c)[0x38 / 4])(c);
    v68 = r[0];
    v6c = r[1];
    v70 = r[2];
    v74 = r[3];
    ((void (__thiscall*)(void*, float*, float*, float*, float*))VT(mpWindow)[0x34 / 4])
        (mpWindow, &v78, &v7c, &v80, &v84);
    void* d = ((VFi)VT(c)[0x10 / 4])(c);
    ((void (__thiscall*)(void*, void*))VT(d)[0xd8 / 4])(d, *(void**)((char*)this + 0x60));
    void* e = ((VFi)VT(c)[0x10 / 4])(c);
    ((void (__thiscall*)(void*, void*))VT(e)[0xdc / 4])(e, c);
    ((void (__thiscall*)(void*, void*))VT(*(void**)((char*)this + 0x60))[0xd8 / 4])
        (*(void**)((char*)this + 0x60), c);

    char* winBase = mpWindow ? (char*)mpWindow - 0x20c : 0;

    char tsMem[0x540];
    char llMem[0xb0];
    wchar_t txt[2];
    txt[0] = 0x37;
    txt[1] = 0;
    ((void (__thiscall*)(void*, int))FUN_0089d820)(tsMem, 0);
    ((void (__thiscall*)(void*, int))FUN_00898bd0)(llMem, 0);
    uint32_t styleId = ((uint32_t (__thiscall*)(void*))VT(winBase + 4)[0x40 / 4])(winBase + 4);
    void* sm = ((void* (__cdecl*)(int))FUN_00885bd0)(0);
    const void* style = ((const void* (__thiscall*)(void*, uint32_t, void*))FUN_00894670)(sm, styleId, 0);
    ((void (__thiscall*)(void*, const wchar_t*, uint32_t, float, float, float, float,
                         const void*, void*, int))FUN_0089dc00)
        (tsMem, txt, 2, 0.0f, 0.0f, 100.0f, 100.0f, style, llMem, 2);
    float hgt = ((float (__thiscall*)(void*))FUN_008975c0)(llMem);
    f28 = hgt;
    Rect rc;
    rc.left = v68 + v78;
    rc.top = v6c + v7c;
    rc.right = v70 - v80;
    rc.bottom = v74 - v84;
    rc.bottom = (float)floor((double)((rc.bottom - rc.top) / hgt)) * hgt + rc.top;
    ((void (__thiscall*)(void*, Rect*))VT(tw)[0x6c / 4])(tw, &rc);
    ((void (__thiscall*)(void*, float, float, float, float))VT(mpWindow)[0x38 / 4])
        (mpWindow, 0.0f, 0.0f, 0.0f, 0.0f);
    Rect rc2;
    rc2.left = 0.0f;
    rc2.top = 0.0f;
    rc2.right = rc.right - rc.left;
    rc2.bottom = rc.bottom - rc.top;
    ((void (__thiscall*)(void*, Rect*))VT(c)[0x6c / 4])(c, &rc2);

    void* srv = FUN_00883860();
    ((void (__thiscall*)(void*, void*, int))VT(srv)[0x20 / 4])(srv, (char*)this + 8, 0x61dd1b7);
    void* m = FUN_00f473a0(0x40, &g_allocTag, 0, 0, 0, 0);
    if (m) {
        *(uint32_t*)((char*)m + 0x30) = 0;
        *(void**)m = &g_vtblMsg0;
        _InterlockedExchange((volatile long*)((char*)m + 4), 0);
        *(void**)m = &g_vtblMsg1;
        *(uint32_t*)((char*)m + 0x38) = 0;
    }
    *(void**)((char*)m + 8) = this;
    srv = FUN_00883860();
    ((void (__thiscall*)(void*, int, void*, int, int))VT(srv)[0x18 / 4])
        (srv, 0x61dd1b7, m, 0, 0);
    ((void (__thiscall*)(void*))FUN_008323d0)(llMem);
    ((void (__thiscall*)(void*))FUN_0089c540)(tsMem);
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

// @ 0x00832e70
void cSPUISwarmEffect::PositionSwarm(void* window)
{
    if (mpVisualEffect == 0)
        return;
    float* r = ((float* (__thiscall*)(void*))VT(window)[0x38 / 4])(window);
    float scratch[2];
    float* q = ((float* (__thiscall*)(void*, float*, float, float))VT(window)[0xc0 / 4])
        (window, scratch, (r[2] - r[0]) * 0.5f, (r[3] - r[1]) * 0.5f);
    float f1 = q[0];
    float f2 = q[1];
    void* app = FUN_0067dd10();
    void* viewer = ((VFi)VT(app)[0x50 / 4])(app);
    float a[3];
    float b[3];
    void* ray = ((void* (__thiscall*)(void*, float, float, float*, float*))VT(viewer)[0x1c / 4])
        (viewer, f1, f2, a, b);
    ((void (__thiscall*)(void*))FUN_007c4730)(ray);
    app = FUN_0067dd10();
    viewer = ((VFi)VT(app)[0x50 / 4])(app);
    void* r2 = ((VFi)VT(viewer)[0x1c / 4])(viewer);
    float d = ((float (__thiscall*)(void*))FUN_007c3c90)(r2) + 10.0f;
    a[0] = b[0] * d + a[0];
    a[1] = a[1] + b[1] * d;
    a[2] = a[2] + b[2] * d;
    Xform xf;
    xf.w0 = 0;
    xf.w2 = 0;
    xf.f4 = g_v3[0];
    xf.f8 = g_v3[1];
    xf.fc = g_v3[2];
    xf.f10 = 1.0f;
    xf.mat = g_m33;
    ((void (__thiscall*)(void*, Xform*))VT(mpVisualEffect)[0x18 / 4])(mpVisualEffect, &xf);
    xf.w0 |= 4;
    xf.w2 += 1;
    xf.f4 = a[0];
    xf.f8 = a[1];
    xf.fc = a[2];
    ((void (__thiscall*)(void*, Xform*))VT(mpVisualEffect)[0x14 / 4])(mpVisualEffect, &xf);
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
    uint32_t t = (uint32_t)type;
    void* r = self;
    if (t != 0xae9cb0fa && t != 0xee3f516e && t != 0x147d84e)
        r = ((void* (__thiscall*)(void*, void*))FUN_00957510)(self, type);
    return r;
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

// @ 0x00833460
int __stdcall UI_Image::GetImage(void* out1, void* out2, void* req)
{
    const char* name = *(const char**)((char*)req + 0x10);
    if (memcmp(name, "image/", 6) != 0)
        return 3;

    int ext;
    if (strcmp(name, g_pszImageBmp) == 0)
        ext = 5;
    else if (strcmp(name, g_pszImageGif) == 0)
        ext = 7;
    else if (strcmp(name, g_pszImageJpeg) == 0)
        ext = 2;
    else if (strcmp(name, g_pszImagePng) == 0)
        ext = 4;
    else if (strcmp(name, g_pszImageTarga) == 0)
        ext = 6;
    else
        return 3;

    int flag = 1;
    HeaderReader reader;
    void* res = *(void**)((char*)req + 0x3c);
    *(void**)out2 = ((void* (__thiscall*)(void*))VT(res)[0x1c / 4])(res);

    if (!reader.Open(res))
        return 1;

    uint32_t count;
    if (reader.Get(ext, &count)) {
        HeaderFileInfo* info = reader.Item(0);
        if (info) {
            void* mgr = FUN_0067dd60();
            ImageResObj* tex = (ImageResObj*)((void* (__thiscall*)(void*, uint32_t, uint32_t,
                                 int, int, int, int))VT(mgr)[0x40 / 4])
                (mgr, info->width, info->height, 1, 8, 0x15, 0);
            ImageResPtr holder(tex);
            ImageResObj* obj = holder.mpObject;
            if (obj != 0) {
                TextureInstance* surface = (TextureInstance*)obj->GetPixels();
                if (surface != 0) {
                    ImageLockInfo li;
                    if (surface->Lock(2, 0, (void**)&li)) {
                        if (!reader.Read(info, li.mpData, li.cbData))
                            flag = 0;
                        ((TextureInstance*)obj->GetPixels())->Unlock((void**)&li);
                    }
                }
            }
            reader.Free(info);
            if (!flag) {
                UI_Image* img = (UI_Image*)FUN_00f473a0(0x14, &g_allocTag, 0, 0, 0, 0);
                if (img != 0)
                    img = new (img) UI_Image(obj);
                void* view = FUN_00f473a0(0x2c, &g_allocTagImg, 0, 0, 0, 0);
                if (view == 0) {
                    view = 0;
                } else {
                    uint32_t h = ((TextureInstance*)obj->GetPixels())->height;
                    uint32_t w = ((TextureInstance*)obj->GetPixels())->width;
                    view = ((void* (__thiscall*)(void*, UI_Image*, uint32_t, uint32_t,
                             int, int, float, float, int))FUN_009579f0)
                        (view, img, w, h, 0, 0, 1.0f, 1.0f, 0);
                }
                ((void (__thiscall*)(void*))VT(view)[0])(view);
                *(void**)out1 = view;
            }
        }
    }
    return flag;
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
