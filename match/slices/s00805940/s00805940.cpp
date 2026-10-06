// Slice s00805940 (w2g6 #16): SPUIHelpers + UTFWin UI window helpers.
// 32-bit MSVC 2008 SP1. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
extern "C" void* SP_WindowManager();                     // 0x0067caa0
extern "C" void* FUN_0067dd60();                         // texture/image manager
extern "C" void* FUN_009512c0();                         // GetUIAllocator
extern "C" void* FUN_009512d0(int, int, const char*, void*);
extern "C" void* FUN_008332a0();
extern "C" void* FUN_008332d0();
extern "C" void* SPKeyFromName(void*, int, int, int);    // 0x0068d840
extern "C" void* AllocEAL(unsigned size, const char* name, int, int, int, int);  // 0x00f473a0

struct ImgHelper {
    void* UI_Image_Image(void*);                                            // 0x008333b0
    void* UI_Image_Image2(void*, int, int, float, float, float, float);     // 0x009579f0
};
struct WindowHelper {
    void* UI_Window_Window();                                               // 0x00962a10
    void* UI_WinText_WinText();                                             // 0x00989000
    void* UI_WinButton_WinButton();                                         // 0x00966f90
};
struct LayoutHelper {
    void* FindWindowByID(int, int);                                         // 0x008105b0
};
struct CtxHelper {
    void FUN_00833790();                                                    // 0x00833790
    void FUN_00833a80();                                                    // 0x00833a80
    char FUN_00833ba0(void*, int, void*, int, int);                         // 0x00833ba0
};
struct AllocHelper { void* GetAllocator(); };                               // 0x007f54d0
struct DrawHelper { void* FUN_00830cf0(int); };                             // 0x00830cf0

extern float g_13ec4d0;   // default window size
extern unsigned char DAT_013f6b3c;
extern char DAT_014178f4;

typedef uint8_t  u8;
typedef uint32_t u32;

struct Vec4 { float x, y, z, w; };

// vtable stub macros: S(n) = no-arg virtual returning void*.
#define S(n) virtual void* v##n();

// Master window interface: all slots used by the simple helpers.
struct W {
    S(00) S(04) S(08)
    virtual void* m0c(int);          // +0x0c  Cast(typeID)
    S(10)
    virtual void  m14(void*, void*); // +0x14
    S(18)
    virtual void  m1c(int);          // +0x1c
    virtual void* m20(int, int, int);// +0x20
    S(24) S(28) S(2c) S(30)
    S(34)                            // +0x34 GetArea -> Vec4*
    S(38)
    S(3c) S(40) S(44) S(48)
    virtual void  m4c(int, int);     // +0x4c
    virtual void  m50(int);          // +0x50
    virtual void  m54(int);          // +0x54
    S(58)
    virtual void  m5c(int);          // +0x5c
    virtual void  m60(void*);        // +0x60
    virtual void  m64(float, float); // +0x64
    virtual void  m68(float, float); // +0x68
    S(6c) S(70) S(74) S(78)
    virtual void  m7c(int, int);     // +0x7c
    S(80) S(84) S(88) S(8c)
    S(90)
    S(94) S(98) S(9c) S(a0) S(a4)
    S(a8)
    virtual void  mAc(int);          // +0xac
    virtual void  mB0(void*);        // +0xb0
    S(b4) S(b8) S(bc)
    virtual void* mC0(void*, int);   // +0xc0
    S(c4) S(c8) S(cc) S(d0) S(d4)
    virtual void  mD8(void*);        // +0xd8
    S(dc) S(e0) S(e4) S(e8) S(ec) S(f0) S(f4) S(f8) S(fc) S(100) S(104) S(108)
    virtual void* m10c(void*);       // +0x10c
};

// Variant used by 00806610: slot +0x18 takes (void*, int, int).
struct DWin {
    S(00) S(04) S(08)
    virtual void* m0c(int);
    S(10)
    virtual void  m14(void*, void*);
    virtual void  m18(void*, int, int);
    virtual void  m1c(int);
    virtual void* m20(int, int);
    S(24) S(28) S(2c) S(30)
    S(34)
    S(38)
    S(3c) S(40) S(44) S(48)
    virtual void  m4c(int, int);
    virtual void  m50(int);
    virtual void  m54(int);
    S(58)
    virtual void  m5c(int);
    virtual void  m60(void*);
    virtual void  m64(float, float);
    virtual void  m68(float, float);
    S(6c) S(70) S(74) S(78)
    virtual void  m7c(int, int);
    S(80) S(84) S(88) S(8c)
    S(90)
    S(94) S(98) S(9c) S(a0) S(a4)
    S(a8)
    virtual void  mAc(int);
    virtual void  mB0(void*);
    S(b4) S(b8) S(bc)
    virtual void* mC0(void*, int);
    S(c4) S(c8) S(cc) S(d0) S(d4)
    virtual void  mD8(void*);
    S(dc) S(e0) S(e4) S(e8) S(ec) S(f0) S(f4) S(f8) S(fc) S(100) S(104) S(108)
    virtual void* m10c(void*);
};

// Variant for GetImageFromLayout / FUN_008067f0: +0x10 and +0x0c take an int.
struct W2 {
    S(00) S(04) S(08)
    virtual void* m0c(int);
    virtual void* m10(int);
    S(14) S(18)
    S(1c) S(20) S(24) S(28) S(2c) S(30) S(34) S(38) S(3c) S(40) S(44) S(48)
    S(4c) S(50) S(54) S(58) S(5c) S(60) S(64) S(68) S(6c) S(70) S(74) S(78)
    S(7c) S(80) S(84) S(88) S(8c) S(90) S(94) S(98) S(9c) S(a0) S(a4)
    S(a8)
};

// WindowManager stub: slot 1 (+0x04) returns the main window.
struct WMgr { virtual void s0(); virtual void* s1(); };

// vtable-slot helper (for the two drawing functions with irregular signatures)
static inline void* VSlot(void* p, unsigned byteOff) {
    return (void*)&((void**)*(void**)p)[byteOff / 4];
}
#define VC2(R, p, o, a, b)    (*(R(__thiscall**)(void*, int, int))VSlot(p, o))(p, (int)(a), (int)(b))

// @ 0x00805ea0
Vec4* SPUIHelpers_GetMainWindowArea(Vec4* out) {
    WMgr* wm = (WMgr*)SP_WindowManager();
    char* p = (char*)wm->s1();
    p = p ? (char*)((char*)p - 4) : (char*)0;
    char* q = p + 4;
    Vec4* a = (Vec4*)((W*)q)->v34();
    out->x = a->x;
    out->y = a->y;
    out->z = a->z;
    out->w = a->w;
    return out;
}

// @ 0x00805ef0
Vec4* FUN_00805ef0(Vec4* out, W* w) {
    Vec4* a = (Vec4*)w->v34();
    out->x = a->x; out->y = a->y; out->z = a->z; out->w = a->w;
    W* r = (W*)w->v10();
    if (r == 0) return out;
    Vec4* b = (Vec4*)r->v38();
    Vec4 tmp;
    tmp.x = b->x; tmp.y = b->y; tmp.z = b->z; tmp.w = b->w;
    W* it = (W*)w->m10c(0);
    if (it != 0) {
        do {
            W* v = (W*)it->m0c(0xcf3df10b);
            if (v != 0) {
                v->v00();
                v->m14(&tmp, out);
                v->v04();
            }
            it = (W*)w->m10c(it);
        } while (it != 0);
    }
    return out;
}

// @ 0x00805fe0
Vec4* FUN_00805fe0(Vec4* out, W* w) {
    out->x = 0; out->y = 0; out->z = 0; out->w = 0;
    if (w == 0) return out;
    Vec4* r = (Vec4*)w->v38();
    float wdt = r->z - r->x;
    float hgt = r->w - r->y;
    Vec4 p1;
    p1.x = 0; p1.y = 0;
    w->mC0(&p1, 0);
    Vec4* q = (Vec4*)w->mC0(&p1, 0);
    out->x = 0; out->y = 0; out->z = q->x; out->w = q->y;
    (void)wdt; (void)hgt;
    return out;
}

// @ 0x008060d0 SPUIHelpers::GetImageFromTexture
void* GetImageFromTexture(int arg1, int arg2, int arg3, int arg4) {
    W* mgr = (W*)FUN_0067dd60();
    W* i = (W*)mgr->m20(arg1, arg2, 0);
    if (i == 0) return 0;
    void* img = AllocEAL(0x14, (const char*)&DAT_013f6b3c, 0, 0, 0, 0);
    if (img == 0) return 0;
    img = ((ImgHelper*)img)->UI_Image_Image(i);
    if (img == 0) return 0;
    ((W*)img)->v00();
    int b = arg3;
    if (b < 0) b = (int)FUN_008332a0();
    int c = arg4;
    if (c < 0) c = (int)FUN_008332d0();
    void* img2 = AllocEAL(0x2c, (const char*)&DAT_013f6b3c, 0, 0, 0, 0);
    if (img2 == 0) {
        ((W*)img)->v04();
        return 0;
    }
    void* r = ((ImgHelper*)img2)->UI_Image_Image2(img, b, c, 0.0f, 0.0f, 1.0f, 1.0f);
    ((W*)img)->v04();
    return r;
}

// @ 0x008061c0 SPUIHelpers::GetImageFromLayout
void* GetImageFromLayout(void* layout, int id) {
    if (layout == 0) return 0;
    W* w = (W*)((LayoutHelper*)layout)->FindWindowByID(id, 1);
    if (w == 0) return 0;
    W2* d = (W2*)w->va8();
    if (d == 0) return 0;
    W2* a = (W2*)d->m0c(0xef3c47cf);
    if (a != 0) return a->v18();
    W2* b = (W2*)d->m0c(0x103c1908);
    if (b != 0) return b->m10(0);
    return 0;
}

// @ 0x00806230 SPUIHelpers::CreateImageFromResource
char CreateImageFromResource2(void* key, void** out, char flag, int a, int b) {
    int* k = (int*)key;
    int k0 = k[0], k1 = k[1], k2 = k[2];
    (void)k2;
    char ctx[0x1c];
    *out = 0;
    ((CtxHelper*)ctx)->FUN_00833790();
    void** slot = (void**)(ctx + 0);
    slot[0] = &DAT_014178f4;
    slot[1] = out;
    slot[2] = (void*)1;
    *out = 0;
    char c;
    if (k1 != 0 && k0 != 0) {
        c = ((CtxHelper*)ctx)->FUN_00833ba0(slot, 0x3fd, &k0, a, b);
        if (c != 0) { c = 1; goto done; }
    }
    c = 0;
done:
    if (*out != 0) ((W*)*out)->v00();
    if (c != 0 && flag != 0) {
        void* p = *(void**)((char*)*out + 4);
        void* v;
        if (p == 0) v = 0;
        else v = ((W*)p)->m0c((int)"itorButtonBounceDuration");
        void* alloc = ((AllocHelper*)v)->GetAllocator();
        if ((*(u8*)((char*)alloc + 4) & 1) == 0) {
            W* m = (W*)FUN_0067dd60();
            (*(void(__thiscall**)(void*, void*))VSlot(m, 0x34))(m, alloc);
        }
    }
    ((CtxHelper*)ctx)->FUN_00833a80();
    return c;
}

// @ 0x00806320 SPUIHelpers::CreateImageFromResource (overload)
void CreateImageFromResourceA(int a, int b, int c, int d, int e, int f, int g) {
    int key[3] = {0, 0, 0};
    SPKeyFromName(&key, c, a, b);
    CreateImageFromResource2(&key, (void**)d, (char)e, f, g);
}

// @ 0x00806370
void* FUN_00806370(W* parent) {
    void* alloc = FUN_009512c0();
    void* mem = FUN_009512d0(0x20c, 4, (const char*)"UI/Window", alloc);
    void* win = 0;
    if (mem != 0) {
        win = ((WindowHelper*)mem)->UI_Window_Window();
    }
    W* esi = win ? (W*)((char*)win + 4) : 0;
    if (esi == 0) return esi;
    esi->m54(0);
    esi->m50(0);
    Vec4 r;
    r.x = 0; r.y = 0;
    r.z = g_13ec4d0; r.w = g_13ec4d0;
    esi->m60(&r);
    esi->m5c(-1);
    esi->mAc(0xffffff);
    esi->m7c(1, 1);
    esi->m7c(0x10, 0);
    esi->m7c(2, 1);
    if (parent != 0) {
        Vec4* a = (Vec4*)parent->v34();
        r.x = 0; r.y = 0;
        r.z = a->z - a->x;
        r.w = a->w - a->y;
        esi->m60(&r);
        parent->mD8(esi);
    }
    esi->v90();
    return esi;
}

// @ 0x008064c0
void* FUN_008064c0(W* parent) {
    void* alloc = FUN_009512c0();
    void* mem = FUN_009512d0(0x834, 4, (const char*)"UI/WinText", alloc);
    void* txt = 0;
    if (mem != 0) {
        txt = ((WindowHelper*)mem)->UI_WinText_WinText();
    }
    W* esi = txt ? (W*)((char*)txt + 0x20c) : 0;
    esi = (W*)esi->v10();
    if (esi == 0) return esi;
    esi->m54(0);
    esi->m50(0);
    Vec4 r;
    r.x = 0; r.y = 0;
    r.z = g_13ec4d0; r.w = g_13ec4d0;
    esi->m60(&r);
    esi->m5c(-1);
    esi->mAc(0xffffff);
    esi->m7c(1, 1);
    esi->m7c(0x10, 0);
    esi->m7c(2, 1);
    if (parent != 0) {
        Vec4* a = (Vec4*)parent->v34();
        r.x = 0; r.y = 0;
        r.z = a->z - a->x;
        r.w = a->w - a->y;
        esi->m60(&r);
        parent->mD8(esi);
    }
    esi->v90();
    return esi;
}

// @ 0x00806610
void FUN_00806610(DWin* win, int a, int b, Vec4* rc, W* obj) {
    DWin* dw = (DWin*)win->v10();
    win->m1c(a);
    for (int i = 0; i < 8; i++) win->m4c(i, 0xff000000);
    dw->m54(0);
    dw->m50(b);
    dw->mAc(0);
    dw->m5c(-1);
    DWin* d = (DWin*)dw->va8();
    Vec4 area;
    d->m18(&area, 0, 0);
    dw->m64(rc->x, rc->y);
    dw->m68(area.x, area.y);
    if (obj != 0) obj->mD8(dw);
    dw->v90();
}

// @ 0x00806780
void* FUN_00806780(int a, int b, int c, int d, int e, int f) {
    void* alloc = FUN_009512c0();
    void* mem = FUN_009512d0(0x888, 4, (const char*)"UI/WinButton", alloc);
    void* btn = 0;
    if (mem != 0) {
        btn = ((WindowHelper*)mem)->UI_WinButton_WinButton();
    }
    DWin* esi = btn ? (DWin*)((char*)btn + 0x20c) : 0;
    DWin* w = (DWin*)esi->v10();
    w->mB0((void*)a);
    FUN_00806610(esi, b, c, (Vec4*)&d, (W*)f);
    (void)e;
    return esi;
}

// @ 0x008067f0
void* FUN_008067f0(W2* w, int index) {
    if (w == 0) return 0;
    W2* a = (W2*)w->va8();
    if (a != 0) a = (W2*)a->m0c(0x103c1908);
    else a = 0;
    W2* b = (W2*)w->va8();
    if (b != 0) b = (W2*)b->m0c(0xef3c47cf);
    else b = 0;
    if (a != 0) {
        if (index < 0 || index >= 8) index = 0;
        return a->m10(index);
    }
    if (b != 0) return b->v18();
    return 0;
}

// @ 0x00806880
void* FUN_00806880(W2* w, int index) {
    if (w == 0) return 0;
    W2* d = (W2*)w->va8();
    if (d == 0) return 0;
    void* r = d->m0c(0x53eb526);
    if (r == 0) return 0;
    if (index < 0 || index >= 8) index = 0;
    return ((DrawHelper*)r)->FUN_00830cf0(index);
}

// @ 0x00805940
void FUN_00805940(void* obj, float cx, float cy, float rad, int p5, int p6,
                  float a0, float a1, void* p9, float step) {
    int* self = (int*)obj;
    float f1 = a1;
    int l3c = p6;
    int l14 = p6;
    if (a1 < a0) { a1 = a0; a0 = f1; }
    if (rad < 0.1f && p9 != 0) rad = (float)*(int*)((char*)p9 + 0x20);
    float sa = sinf(a0);
    float ca = cosf(a0);
    float l44 = cx, l40 = cy;
    float l2c = cy - sa * rad;
    float l30 = ca * rad + cx;
    int l28 = p5;
    if (a1 <= a0) return;
    float s = a0;
    for (;;) {
        float d = step;
        if (a1 - a0 < step) d = a1 - a0;
        s = s + d;
        a0 = s;
        float s2 = sinf(s);
        float c2 = cosf(s);
        float l18 = cy - s2 * rad;
        float l1c = c2 * rad + cx;
        float lc = rad, l10 = rad;
        if (p9 != 0) {
            lc = (float)*(int*)((char*)p9 + 0x20);
            l10 = (float)*(int*)((char*)p9 + 0x1c);
        }
        l10 = 1.0f / l10;
        lc = 1.0f / lc;
        float l38 = l10 * l44;
        float l34 = lc * l40;
        float l24 = l10 * l30;
        float l20 = lc * l2c;
        float l10b = l10 * l1c;
        float lcb = lc * l18;
        (void)l38; (void)l34; (void)l24; (void)l20; (void)l10b; (void)lcb;
        if (p9 == 0) {
            float l54 = l30, l50 = l2c, l5c = l1c, l58 = l18, l4c = l44, l48 = l40;
            (*(void(__thiscall**)(void*, void*, int, void*, int, void*, int))VSlot(self, 0x4c))(
                self, &l4c, l3c, &l54, l28, &l5c, l14);
        } else {
            VC2(void, self, 0x50, &l44, 1);
        }
        l30 = l1c;
        l2c = l18;
        if (a1 <= a0) break;
        l28 = l14;
    }
}

// @ 0x00805bb0
void FUN_00805bb0(void* obj, float cx, float cy, float w, float h, int p6, int p7,
                  float a0, float a1, int p10, float step) {
    int* self = (int*)obj;
    float f10 = a1;
    float hw = w * 0.5f;
    float hh = h * 0.5f;
    if (a1 < a0) { a1 = a0; a0 = f10; }
    float sa = sinf(a0);
    float ca = cosf(a0);
    float aa = ca < 0 ? -ca : ca;
    float ab = sa < 0 ? -sa : sa;
    float denom = aa;
    if (aa <= ab) denom = ab;
    float nx = (1.0f / denom) * sa;
    float ny = (1.0f / denom) * ca;
    float u0 = (ny + 1.0f) * 0.5f;
    float v0 = (1.0f - nx) * 0.5f;
    float py0 = cy - nx * hh;
    float px0 = ny * hw + cx;
    int l28 = p6;
    int l3c = p7;
    float f5 = cx, f6 = cy, f13 = px0, f11 = py0;
    float f10b = 0, f12 = 0, f1 = 0, f2 = 0, f3 = 0, f4 = 0;
    (void)u0; (void)v0; (void)f10b;
    for (;;) {
        f2 = f6; f1 = f5; f3 = f13; f4 = f11;
        if (!(a0 < a1)) break;
        float d = step;
        if (a1 - a0 < step) d = a1 - a0;
        float ang = d + a0;
        float s2 = sinf(ang);
        float c2 = cosf(ang);
        float ba = c2 < 0 ? -c2 : c2;
        float bb = s2 < 0 ? -s2 : s2;
        float dn = ba;
        if (ba <= bb) dn = bb;
        float nnx = (1.0f / dn) * s2;
        float nny = (1.0f / dn) * c2;
        float py = cy - nnx * hh;
        float px = nny * hw + cx;
        float l5c = px, l58 = py;
        (void)l58;
        if (p10 == 0) {
            float l44 = f3, l40 = f4;
            (*(void(__thiscall**)(void*, void*, int, void*, int, void*, int))VSlot(self, 0x4c))(
                self, &l44, l3c, &f1, l28, &l5c, l3c);
        } else {
            float l44 = f3, l40 = f4;
            (*(void(__thiscall**)(void*, void*, int, void*))VSlot(self, 0x50))(
                self, &l44, 1, (void*)p10);
        }
        (void)f2; (void)f12;
        if (a1 <= a0) break;
        a0 = ang;
    }
}
