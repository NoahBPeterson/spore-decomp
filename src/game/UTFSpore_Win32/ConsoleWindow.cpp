// src/game/UTFSpore_Win32/ConsoleWindow.cpp -- migrated from slice(s) s00968da0, s0096ad00, s00969e30 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ConsoleWindow.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinControls/IWinButton.h"
#include "EA/UTFWinControls/IWinText.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/IWindowMgr.h"
#include "EA/Text/LineLayout.h"
#include "EA/UTFWin/Message.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/Text/TextStyle.h"
#include "EA/Text/Typesetter.h"
#include "EA/UTFWin/Window.h"

// unnamed retail callees and globals (address in the comment)
extern "C" uint32_t __cdecl FNV1_String8(const char*, uint32_t, uint32_t);  // 0x932e80

// ---- items of slice s00969e30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_011e0744(void*, const void*, int);            // 0x11e0744  vector<bool> DoInsertValue
extern "C" void  __cdecl FUN_0093c950(const char*, int, int, void*, int*, int); // 0x93c950 ConvertEncoding
extern "C" int   __cdecl IsWideSpace(unsigned short, int);                 // 0xa63a70
extern "C" int   __cdecl IsByteSpace(unsigned char);                       // 0xa66e30
struct Sub {                                   // sub-objects inside ConsoleWindow
    void m_967690();                           // 0x967690
    void m_9676f0(void*, int);                 // 0x9676f0
};
struct Alloc {                                 // allocator sub-object at CW+0x20c
    uint32_t Avail(int);                       // 0x967770
    void*    AllocBlock(uint32_t, int);        // 0x9676a0
    void     Free(void*);                      // 0xfd9450
};
struct CW {
    void InvalidateLayout();                   // 0x9609b0  Window::InvalidateLayout
    void m_969d40();                           // 0x969d40
    bool BaseDoMessage(int);                   // 0x950bb0  Window::DoMessage
    __declspec(noinline) void Refresh(char);   // 0x969e30
    void ResetLayout();                        // 0x969ed0
    bool DoMessageProc(int);                   // 0x969f00 (retail returns via al, upper eax preserved)
    int  Scroll(int, int, char, int);          // 0x969f80
    int  Init();                               // 0x96a670
    void LayoutLines();                        // 0x96a790
    void Clear();                              // 0x96ab30
    void Find(int*, void**);                   // 0x96ab90
    void Destroy();                            // 0x96ac10
    void SetRegion(void*);                     // 0x96acd0
    void LineNode(void*);                      // 0x969bf0
    void AppendW(unsigned short*, int);        // 0x96a860
    void Append(char*, int);                   // 0x96a9b0
};
extern "C" void* __cdecl FUN_009512c0_s0096_9e30();                                   // 0x9512c0
struct CWBaseWindow {                          // the Window base at CW+0
    char Initialize();                         // 0xb1fbf0  Window::Initialize
};
struct CWScrollbar {
    CWScrollbar* Ctor();                       // 0x983790
};
struct CWRef {
    CWRef* operator=(void*);                   // 0xb5f950  AutoRefCount::operator=
};
struct CWDrawable {
    void* Ctor();                              // 0x969ac0
};
// ---- items of slice s00969e30 end

// ---- items of slice s0096ad00 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n()
inline void* operator new(unsigned int, void* p) { return p; }
namespace EA {
namespace Text {
class StyleManager;
}
}
namespace EA {
namespace Text {
struct TextStyle_s0096_ad00 {
    char pad00[0x1c];
    int  mfSize;                   // +0x1c
    char pad20[0x178];
    int  mHAlignment;
    char pad1fc[0x78];
    int  mTextWrap;

    TextStyle_s0096_ad00();                   // 0x008941d0
};
}
}
namespace EA {
namespace Text {
class StyleManager { public:
    TextStyle_s0096_ad00* GetStyle(uint32_t styleId, int alloc);   // 0x00894670
    void       AddStyle(uint32_t styleId, TextStyle_s0096_ad00* style); // 0x00894970
};
}
}
namespace EA {
namespace Text {
StyleManager* GetStyleManager(bool);
}
}
namespace EA {
namespace UTFWin {
struct IWindow_s0096_ad00;
}
}
namespace EA {
namespace UTFWin {
struct RenderContext_s0096_ad00 {
    void* Begin2D(int mode);       // 0x0095bc10
    void  End2D();                 // 0x0095bb20

    // vtable slots touched through the returned interface pointer.
    PV(0); PV(1);
    virtual void v08(int);         // +0x04
    PV(3); PV(4);
    virtual void v14(void*);       // +0x14
    PV(6); PV(7); PV(8);
    virtual void v1c(int, int, float, float, int); // +0x1c
    PV(10); PV(11);
    virtual void v30(void*, void*, void*);         // +0x30
    PV(13);
    virtual void v38(int, int, int, int);          // +0x38
};
}
}
namespace EA {
namespace UTFWin {
struct IWindow_s0096_ad00 {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7);
    PV(8); PV(9); PV(10); PV(11); PV(12); PV(13); PV(14);
    PV(15); PV(16); PV(17); PV(18); PV(19); PV(20);
    PV(21); PV(22); PV(23); PV(24); PV(25); PV(26); PV(27); PV(28); PV(29); PV(30);
    virtual void SetFlag(uint32_t flag, int value);    // +0x7c
    PV(32); PV(33); PV(34); PV(35);
    virtual int  Invalidate();                         // +0x90
};
}
}
namespace EA {
namespace UTFWin {
struct WindowVt {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7); PV(8); PV(9);
    PV(10); PV(11); PV(12); PV(13); PV(14); PV(15); PV(16); PV(17); PV(18); PV(19);
    PV(20); PV(21); PV(22); PV(23); PV(24); PV(25); PV(26); PV(27); PV(28); PV(29);
    PV(30); PV(31); PV(32); PV(33); PV(34);
    PV(35);
    virtual int  GetComponentAt(float x, float y);     // +0x90
    PV(37); PV(38); PV(39);
    virtual void UpdateLayout(int mode);               // +0xa0

    bool Window_Initialize();       // 0x00b1fbf0
    void Window_SerUpdate();        // 0x009614a0
    void Window_InvalidateLayout(); // 0x009609b0
    void Window_Shutdown();         // 0x00961e80
};
}
}
using EA::UTFWin::IWindow_s0096_ad00;
namespace Console {
void InitChannelColors(void* sub, int arg);   // 0x009677d0
}
namespace Console {
void ResizeBuffers(void* sub, int count, int arg); // 0x009676f0
}
void __fastcall Window_ctor(void*);   // 0x00962a10
struct ConsoleWindow {
    ConsoleWindow(bool param2);                          // 0x0096b0b0
    int  OnRebuild(EA::UTFWin::RenderContext_s0096_ad00* ctx);      // 0x0096ad00
    char mDummy;
};
namespace EA {
namespace Text {
struct Typesetter_s0096_ad00 {
    Typesetter_s0096_ad00(bool unicode);      // 0x0089d820
};
}
}
namespace EA {
namespace Text {
struct LineLayout_s0096_ad00 {
    LineLayout_s0096_ad00(bool unicode);      // 0x00898bd0
    void Clear(bool arg);          // 0x0089cbc0
};
}
}
int __cdecl FUN_009512c0();
void* __cdecl FUN_009512d0(int size, int align, const char* type, void* factory);
// ---- items of slice s0096ad00 end

// ---- items of slice s00968da0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* f_GetStyleManager(int b);                              // 0x885bd0
extern "C" void* f_GetStyle(void* mgr, unsigned id, void* base);        // 0x894670
extern "C" void  f_LineLayout_Clear(void* self, int a);                 // 0x89cbc0
extern uint8_t g_vtbl_ScrollbarDrawable0[];    // 0x1441a44
extern uint8_t g_vtbl_ScrollbarDrawable1[];    // 0x144485c
extern uint8_t g_vtbl_ScrollbarDrawable2[];    // 0x1441a2c
extern "C" int   f_00961e80(void* self);                 // 0x961e80 Window::Shutdown
extern "C" void* f_LayoutParagraph_3(void* text, int len, float x, float y,
                                     float w, float h, void* style, void* ll, int flags); // 0x89dc00
struct IRefCounted {                              // minimal COM shape (vtable slots)
    virtual void slot0();
    virtual void Release();                       // slot 1 (vtbl+4)
};
struct ScrollbarBase {
    void BaseCtor();                // 0x9838a0 UI::ScrollbarDrawable::ScrollbarDrawable
};
struct ScrollbarDrawable : ScrollbarBase {
    ScrollbarDrawable();            // 0x969ac0
};
struct ConsoleLine {            // the object handed to LayoutLine/Draw
    char* mpText;               // +0x00
    char pad04[0x0c - 0x04];
    int   mnField0c;            // +0x0c
    int   mnLen;                // +0x10
    float mPosX;                // +0x14
};
struct ConsoleWindow_s0096_8da0 {
    bool Shutdown();                        // 0x969b90
    void LayoutLine(ConsoleLine* line);     // 0x969bf0
    void Draw();                            // 0x969d40
};
// ---- items of slice s00968da0 end

// @ 0x00969ac0
ScrollbarDrawable::ScrollbarDrawable()
{
    ((ScrollbarBase*)this)->BaseCtor();
    *(void**)((char*)this + 0x0) = g_vtbl_ScrollbarDrawable0;
    *(void**)((char*)this + 0x4) = g_vtbl_ScrollbarDrawable1;
    *(void**)((char*)this + 0xc) = g_vtbl_ScrollbarDrawable2;
}

// @ 0x00969b10
bool __stdcall GetComboSize(float* out, unsigned a, unsigned b)
{
    if (b == 3) {
        out[0] = 20.0f;
        out[1] = 12.0f;
        return true;
    }
    return false;
}

// @ 0x00969b90
bool ConsoleWindow_s0096_8da0::Shutdown()
{
    char* s = (char*)this;
    void* p = *(void**)(s + 0x864);
    if (p) {
        void** vt = *(void***)p;
        void* r = ((void* (*)(void*))vt[0x10 / 4])(p);
        void** wt = *(void***)(s + 4);
        ((void (*)(void*, void*))wt[0xe0 / 4])(s + 4, r);
        p = *(void**)(s + 0x864);
        if (p) {
            *(void**)(s + 0x864) = 0;
            ((IRefCounted*)p)->Release();
        }
    }
    *(char*)(s + 0x860) = 0;
    return f_00961e80(s) != 0;
}

// @ 0x00969bf0
void ConsoleWindow_s0096_8da0::LayoutLine(ConsoleLine* line)
{
    char* s = (char*)this;
    if (*(char*)(s + 0x860) == 0) {
        *(char*)(s + 0x861) = 1;
        return;
    }
    float x = *(float*)(s + 0x84c);
    float y = *(float*)(s + 0x850);
    float w = (*(float*)(s + 0x90) - *(float*)(s + 0x88)) -
              (*(float*)(s + 0x854) - 3.0f);

    if (*(char*)(s + 0x868) != 0) {
        void* p = *(void**)(s + 0x864);
        void** vt = *(void***)p;
        void* inner = ((void* (*)(void*))vt[0x10 / 4])(p);
        void** it = *(void***)inner;
        float* r = (float*)((void* (*)(void*))it[0x34 / 4])(inner);
        w = (r[2] - r[0]) + w;
    }

    void* mgr = f_GetStyleManager(1);
    void* style = f_GetStyle(mgr, 0xefe945b2u, 0);
    if (!style)
        return;

    char* ll = s + 0x788;
    f_LineLayout_Clear(ll, 1);
    f_LayoutParagraph_3((char*)line + 0x14, line->mnLen, x, y, w, 100000.0f,
                        style, ll, 0);
    float f = (float)*(int*)(s + 0x830);
    if (*(int*)(s + 0x830) < 0)
        f += 4294967296.0f;
    long long v = (long long)(f * (*(float*)(s + 0x828) - *(float*)(s + 0x82c)));
    line->mnField0c = (int)v;
}

// @ 0x00969d40
void ConsoleWindow_s0096_8da0::Draw()
{
    char* s = (char*)this;
    if (*(void**)(s + 0x864) == 0)
        return;

    float quad[3];
    quad[0] = 20.0f;
    quad[1] = 20.0f;

    void** vt = *(void***)(s + 4);
    void* r = ((void* (*)(void*))vt[0x14 / 4])(s + 4);

    struct { int a; int b; float c; int d; int e; } item;
    item.a = 0x16;
    item.b = 0;
    (void)item;

    if (r) {
        void* p = *(void**)(s + 0x864);
        void** objvt = *(void***)p;
        void* inner = ((void* (*)(void*))objvt[0x10 / 4])(p);
        void** ivt = *(void***)inner;
        ((void (*)(void*, void*))ivt[0x10 / 4])(inner, (void*)&item.c);
    }

    float w = *(float*)(s + 0x90) - *(float*)(s + 0x88);
    float h = *(float*)(s + 0x94) - *(float*)(s + 0x8c);

    float rect[5];
    rect[0] = w;
    rect[1] = 0.0f;
    rect[2] = h;
    rect[3] = 0.0f;
    rect[4] = w;

    void* p = *(void**)(s + 0x864);
    void** pvt = *(void***)p;
    void* inner = ((void* (*)(void*))pvt[0x10 / 4])(p);
    void** ivt = *(void***)inner;
    ((void (*)(void*, float*))ivt[0x60 / 4])(inner, &rect[2]);
    (void)quad;
}

// @ 0x00969ed0
void CW::ResetLayout()
{
    ((CW*)this)->InvalidateLayout();
    CW* base = (CW*)((char*)this - 4);
    base->m_969d40();
    base->Refresh(0);
    *(char*)((char*)this + 0x85d) = 1;
}

// @ 0x00969f00
bool CW::DoMessageProc(int msg)
{
    if (*(int*)(msg + 8) != (int)0x8ef0c8dd)
        return BaseDoMessage(msg);
    if (*(char*)((char*)this + 0x868) != 0) {
        int* p = *(int**)((char*)this + 0x864);
        int iVar3 = (*(int(__thiscall**)(int*))((char*)*p + 0x28))(p);
        int iVar4 = (*(int(__thiscall**)(int*))((char*)*p + 0x38))(p);
        iVar4 -= iVar3;
        iVar4 -= (*(int(__thiscall**)(int*))((char*)*p + 0x40))(p);
        *(int*)((char*)this + 0x224) = iVar4;
        if (iVar4 < 0)
            *(int*)((char*)this + 0x224) = 0;
        void* p2 = (char*)this + 4;
        (*(void(__thiscall**)(void*))((char*)*(void**)p2 + 0x90))(p2);
    }
    return 1;
}

// @ 0x00969f80
int CW::Scroll(int, int, char flags, int amount)
{
    int* p = *(int**)((char*)this + 0x864);
    int iVar2 = (*(int(__thiscall**)(int*))((char*)*p + 0x40))(p);
    int iVar3 = (*(int(__thiscall**)(int*))((char*)*p + 0x38))(p);
    if (iVar2 < iVar3) {
        int v = amount;
        if (flags & 1) v += v;
        if (flags & 2) v += v;
        if (flags & 4) v += v;
        int q = *(int*)((char*)this + 0x228) / *(int*)((char*)this + 0x234);
        float prod = (float)(unsigned)q * (float)v * *(float*)0x13eb960;
        int add = (int)prod;
        *(int*)((char*)this + 0x224) += add;

        float dx = ((*(float*)((char*)this + 0x94) - *(float*)((char*)this + 0x8c))
                  - *(float*)((char*)this + 0x850)) - *(float*)((char*)this + 0x858);
        int iVar4 = (int)dx;
        if (*(int*)((char*)this + 0x224) < 0) {
            *(int*)((char*)this + 0x224) = 0;
            ((CW*)this)->Refresh(1);
            return 1;
        }
        int lim = (*(int(__thiscall**)(int*))((char*)*p + 0x38))(p) - iVar4;
        if (*(int*)((char*)this + 0x224) > lim) {
            int lim2 = (*(int(__thiscall**)(int*))((char*)*p + 0x38))(p) - iVar4;
            *(int*)((char*)this + 0x224) = lim2;
        }
        ((CW*)this)->Refresh(1);
    }
    return 1;
}

// @ 0x0096a0a0
int __cdecl FUN_0096a0a0(void* ctx, int* rect, uint32_t* style)
{
    int* rc = (int*)(*(int(__cdecl*)(void*, int))0x95bc10)(ctx, 0);   // RenderContext::Begin2D
    uint32_t u6 = (uint32_t)(int)(*(float*)0x166b1bc * 145.0f + 110.0f) << 24;
    uint32_t u2 = (uint32_t)(int)(*(float*)0x166b1bc * 169.0f + 86.0f) << 24;
    uint32_t sel = *style & 7;
    uint32_t colA = u2 | 0x3d517f;
    uint32_t colB = (uint32_t)(int)(*(float*)0x166b1bc * 139.0f + 116.0f) << 24 | 0x8e98b5;
    uint32_t locA = u6 | 0x8a9dc4;
    if (sel == 1) {
        colA = u2 | 0x52607f;
        colB = u6 | 0x8f98aa;
        locA = colB;
    } else if (sel == 2) {
        colA = u2 | 0x5a78bc;
        colB = u6 | 0xdce3ef;
        locA = u6 | 0xacc4f4;
    } else if (sel == 3) {
        uint32_t u2b = (uint32_t)(int)(*(float*)0x166b1bc * 101.0f + 154.0f) << 24;
        colA = u2b | 0x5a78bc;
        colB = (uint32_t)(int)(*(float*)0x166b1bc * 48.0f + 207.0f) << 24 | 0xdce3ef;
        locA = u2b | 0xacc4f4;
    }

    float* f = (float*)rect;
    void (__thiscall* col)(int*, uint32_t) = (void(__thiscall*)(int*, uint32_t))((char*)*rc + 4);
    void (__thiscall* rectf)(int*, float, float, float, float) = (void(__thiscall*)(int*, float, float, float, float))((char*)*rc + 0x38);
    void (__thiscall* recti)(int*, int, int, int, int) = (void(__thiscall*)(int*, int, int, int, int))((char*)*rc + 0x1c);
    void (__thiscall* poly)(int*, float*, float*, float*, float*) = (void(__thiscall*)(int*, float*, float*, float*, float*))((char*)*rc + 0x3c);

    uint32_t kind = style[1];
    if (kind == 3) {
        col(rc, locA);
        rectf(rc, f[0] + 4.0f, f[1] + 2.0f, f[2] - 4.0f, f[3] - 2.0f);
    } else if (kind == 4) {
        col(rc, colA);
        rectf(rc, f[0], f[1], f[2], f[3]);
        col(rc, colA);
        rectf(rc, f[0], f[1], f[0] + 2.0f, f[3]);
        rectf(rc, f[2] - 2.0f, f[1], f[2], f[3]);
    } else if (kind == 1 || kind == 6) {
        col(rc, colA);
        rectf(rc, f[0], f[1], f[2], f[3]);
        col(rc, colA);
        recti(rc, (int)f[0], (int)f[1], (int)f[2], (int)f[3]);
        // the following block refines the highlight (0x40000000) case
        col(rc, colA);
        recti(rc, (int)f[0], (int)f[1], (int)f[2], (int)f[3]);
    }

    if (kind == 1) {
        col(rc, colB);
        float x0 = f[0];
        float wy = (f[2] - x0) * 0.2857143f;
        float hx = (f[3] - f[1]) * 0.2857143f;
        if ((*style & 0x80) != 0) {
            float a = f[3] - hx;
            float b = x0 + wy;
            float c = f[2] - wy;
            float d = (f[2] - x0) * 0.5f + x0;
            float e = f[1] + hx;
            float t1 = a, t2 = b, t3 = d, t4 = e;
            poly(rc, &t1, &t3, &t2, &t4);
            return 0;
        }
        float a = f[1];
        float e = (f[3] - a) * 0.5f + a;
        float b = x0 + wy;
        float c = f[2] - wy;
        float d = f[3] - hx;
        float aa = a + hx;
        float t1 = b, t2 = c, t3 = aa, t4 = d;
        poly(rc, &t1, &t2, &t3, &t4);
        return 0;
    } else if (kind == 6) {
        col(rc, colB);
        float x0 = f[0];
        float wy = (f[2] - x0) * 0.2857143f;
        float hx = (f[3] - f[1]) * 0.2857143f;
        if ((*style & 0x80) != 0) {
            float a = f[1] + hx;
            float b = x0 + wy;
            float c = f[2] - wy;
            float d = (f[2] - x0) * 0.5f + x0;
            float e = f[3] - hx;
            float t1 = b, t2 = c, t3 = d, t4 = e;
            poly(rc, &t1, &t2, &t3, &t4);
            return 0;
        }
        float a = f[1];
        float b = x0 + wy;
        float e = hx + a;
        float d = f[3] - hx;
        float c = f[2] - wy;
        float aa = (f[3] - a) * 0.5f + a;
        float t1 = b, t2 = c, t3 = aa, t4 = d;
        poly(rc, &t1, &t2, &t3, &t4);
        return 0;
    }
    return 0;
}

// @ 0x0096a620
void* __cdecl DoFindNode(void* node, void** pkey, uint32_t)
{
    if (node == 0)
        return 0;
    const char* key = (const char*)*pkey;
    for (;;) {
        const char* s = *(const char**)node;
        int r;
        for (;;) {
            unsigned char x = (unsigned char)s[0];
            unsigned char y = (unsigned char)key[0];
            if (x != y) { r = (x < y) ? -1 : 1; break; }
            if (x == 0) { r = 0; break; }
            x = (unsigned char)s[1];
            y = (unsigned char)key[1];
            if (x != y) { r = (x < y) ? -1 : 1; break; }
            s += 2;
            key += 2;
            if (x == 0) { r = 0; break; }
        }
        if (r == 0)
            return node;
        node = *(void**)((char*)node + 8);
        if (node == 0)
            return 0;
    }
}

// @ 0x0096a670
int CW::Init()
{
    if (!((CWBaseWindow*)this)->Initialize())
        return 0;
    if (*(char*)((char*)this + 0x868) != 0 &&
        *(int*)((char*)this + 0x864) == 0) {
        void* p = FUN_009512d0(0x2d0, 8, "UTFWin/ConsoleWindow/Scrollbar", FUN_009512c0_s0096_9e30());
        if (p != 0)
            p = ((CWScrollbar*)p)->Ctor();
        if (p == 0) {
            p = 0;
        } else {
            p = (char*)p + 0x20c;
        }
        ((CWRef*)((char*)this + 0x864))->operator=(p);

        int* sb = *(int**)((char*)this + 0x864);
        (*(void(__thiscall**)(int*, int))((char*)*sb + 0x14))(sb, 2);
        int* it = (int*)(*(int(__thiscall**)(int*))((char*)*sb + 0x10))(sb);
        (*(void(__thiscall**)(int*, int, int))((char*)*it + 0x7c))(it, 1, 1);

        void* d = FUN_009512d0(0x2c, 4, "UTFWin/ConsoleWindow/ScrollbarDrawable", FUN_009512c0_s0096_9e30());
        if (d != 0)
            d = ((CWDrawable*)d)->Ctor();
        else
            d = 0;
        it = (int*)(*(int(__thiscall**)(int*))((char*)*sb + 0x10))(sb);
        (*(void(__thiscall**)(int*, void*))((char*)*it + 0xb0))(it, d);
        (*(void(__thiscall**)(int*, int, int))((char*)*sb + 0x1c))(sb, 1, 1);
        (*(void(__thiscall**)(int*, int))((char*)*sb + 0x4c))(sb, 0x96);

        int* base = *(int**)((char*)this + 4);
        it = (int*)(*(int(__thiscall**)(int*))((char*)*sb + 0x10))(sb);
        (*(void(__thiscall**)(int*, int*))((char*)base + 0xd8))(base, it);
    }
    ((CW*)this)->m_969d40();
    *(char*)((char*)this + 0x860) = 1;
    return 1;
}

// @ 0x0096a790
void CW::LayoutLines()
{
    void** base = (void**)((char*)this + 0x22c);
    char* p = (char*)*(void**)((char*)this + 0x22c);
    *(int*)((char*)this + 0x228) = 0;
    while (p != (char*)base) {
        ((CW*)this)->LineNode(p);              // 0x969bf0
        *(int*)((char*)this + 0x228) += *(int*)(p + 0xc);
        p = *(char**)p;
    }
    if (*(int*)((char*)this + 0x864) != 0) {
        float dx = ((*(float*)((char*)this + 0x94) - *(float*)((char*)this + 0x8c))
                  - *(float*)((char*)this + 0x850)) - *(float*)((char*)this + 0x858);
        int iVar5 = (int)dx;
        int* sb = *(int**)((char*)this + 0x864);
        int total = *(int*)((char*)this + 0x228);
        (*(void(__thiscall**)(int*, int, int))((char*)*sb + 0x34))(sb, total, 1);
        (*(void(__thiscall**)(int*, int, int))((char*)*sb + 0x3c))(sb, iVar5, 1);
        (*(void(__thiscall**)(int*, int, int))((char*)*sb + 0x24))(sb, (total - iVar5) - *(int*)((char*)this + 0x224), 0);
    }
    void* p2 = (char*)this + 4;
    (*(void(__thiscall**)(void*))((char*)*(void**)p2 + 0x90))(p2);
}

// @ 0x0096a860
void CW::AppendW(unsigned short* str, int param3)
{
    const unsigned short* s = str;
    while (*s) s++;
    int len = (int)(s - (str + 1));
    if (len != 0) {
        while (len != 0) {
            if (IsWideSpace(str[len - 1], 8) == 0) break;
            len--;
        }
    }
    uint32_t need = len * 2 + 0x14;
    Alloc* al = (Alloc*)((char*)this + 0x20c);
    void** base = (void**)((char*)this + 0x22c);
    for (;;) {
        int cur = *(int*)((char*)this + 0x234);
        if (*(uint32_t*)((char*)this + 0x21c) > (uint32_t)cur) {
            if (cur <= 0)
                break;                                   // insert
            if (al->Avail(8) >= need)
                break;                                   // insert
        }
        // pop front
        char* f = (char*)*(void**)((char*)this + 0x22c);
        *(int*)((char*)this + 0x228) -= *(int*)(f + 0xc);
        *(void**)((char*)*(void**)f + 4) = base;
        void* nx = *(void**)(*(void**)base);
        *(void**)((char*)this + 0x22c) = *(void**)nx;
        if (f != (char*)base) {
            *(int*)(f + 4) = 0;
            *(int*)f = 0;
        }
        al->Free(f);
        *(int*)((char*)this + 0x234) -= 1;
    }
    if (al->Avail(8) < need) return;
    char* node = (char*)al->AllocBlock(need, 8);
    *(int*)(node + 8) = param3;
    *(int*)(node + 0x10) = len;
    FUN_011e0744(node + 0x14, str, len * 2);
    *(int*)(node + 4) = *(int*)((char*)this + 0x230);
    *(void**)node = base;
    *(void**)((char*)base + 4) = node;
    *(void**)(*(void**)(node + 4)) = node;
    *(int*)((char*)this + 0x234) += 1;
    if (*(char*)((char*)this + 0x860) != 0) {
        ((CW*)this)->LineNode(node);
        *(int*)((char*)this + 0x228) += *(int*)(node + 0xc);
    }
    *(int*)((char*)this + 0x224) = 0;
    this->Refresh(1);
}

// @ 0x0096a9b0
void CW::Append(char* str, int param3)
{
    char* s = str;
    while (*s) s++;
    int len = (int)(s - (str + 1));
    int conv = -1;
    if (len != 0) {
        while (len != 0) {
            if (IsByteSpace((unsigned char)str[len - 1]) == 0) break;
            len--;
        }
    }
    FUN_0093c950(str, len, 8, 0, &conv, 0x10);
    uint32_t need = conv * 2 + 0x14;
    Alloc* al = (Alloc*)((char*)this + 0x20c);
    void** base = (void**)((char*)this + 0x22c);
    for (;;) {
        int cur = *(int*)((char*)this + 0x234);
        if (*(uint32_t*)((char*)this + 0x21c) > (uint32_t)cur) {
            if (cur <= 0) break;
            if (al->Avail(8) >= need) break;
        }
        char* f = (char*)*(void**)((char*)this + 0x22c);
        *(int*)((char*)this + 0x228) -= *(int*)(f + 0xc);
        *(void**)((char*)*(void**)f + 4) = base;
        void* nx = *(void**)(*(void**)base);
        *(void**)((char*)this + 0x22c) = *(void**)nx;
        if (f != (char*)base) {
            *(int*)(f + 4) = 0;
            *(int*)f = 0;
        }
        al->Free(f);
        *(int*)((char*)this + 0x234) -= 1;
    }
    if (al->Avail(8) < need) return;
    char* node = (char*)al->AllocBlock(need, 8);
    if (node != 0) {
        *(int*)(node + 4) = 0;
        *(int*)node = 0;
    } else {
        node = 0;
    }
    *(int*)(node + 8) = param3;
    *(int*)(node + 0x10) = len;
    FUN_0093c950(str, len, 8, node + 0x14, &conv, 0x10);
    *(int*)(node + 4) = *(int*)((char*)this + 0x230);
    *(void**)node = base;
    *(void**)((char*)base + 4) = node;
    *(void**)(*(void**)(node + 4)) = node;
    *(int*)((char*)this + 0x234) += 1;
    if (*(char*)((char*)this + 0x860) != 0) {
        ((CW*)this)->LineNode(node);
        *(int*)((char*)this + 0x228) += *(int*)(node + 0xc);
    }
    *(int*)((char*)this + 0x224) = 0;
    this->Refresh(1);
}

// @ 0x0096ab30
void CW::Clear()
{
    void** base = (void**)((char*)this + 0x22c);
    void** p = (void**)*(void**)((char*)this + 0x22c);
    while (p != base) {
        void** n = (void**)*p;
        p[1] = 0;
        *p = 0;
        p = n;
    }
    base[1] = base;
    base[0] = base;
    ((Sub*)((char*)this + 0x20c))->m_967690();
    *(int*)((char*)this + 0x228) = 0;
    *(int*)((char*)this + 0x224) = 0;
    *(int*)((char*)this + 0x234) = 0;
    ((CW*)this)->Refresh(1);
}

// @ 0x0096ab90
void CW::Find(int* out, void** pkey)
{
    uint32_t h = FNV1_String8((const char*)*pkey, 0x811c9dc5, 0);
    uint32_t nbuckets = *(uint32_t*)((char*)this + 8);
    int* buckets = *(int**)((char*)this + 4);
    int* slot = buckets + (h % nbuckets);
    int found = (int)DoFindNode((void*)*slot, pkey, h);
    int v0, v1;
    if (found != 0) {
        v0 = found;
        v1 = (int)slot;
    } else {
        int* endslot = buckets + nbuckets;
        v0 = *endslot;
        v1 = (int)endslot;
    }
    out[0] = v0;
    out[1] = v1;
}

// @ 0x0096ac10
void CW::Destroy()
{
    *(void**)this = (void*)0x1441c18;
    *(void**)((char*)this + 4) = (void*)0x1441af8;
    ((CW*)this)->Clear();
    void* sm = ((void*(__cdecl*)(int))0x885bd0)(1);
    if (sm != 0)
        (*(void(__thiscall**)(void*, uint32_t))((char*)*(void**)sm + 0))(sm, 0xefe945b2);
    int* p = *(int**)((char*)this + 0x864);
    if (p != 0)
        (*(void(__thiscall**)(int*))((char*)*p + 4))(p);
    ((Sub*)((char*)this + 0x788))->m_967690();
    ((Sub*)((char*)this + 0x258))->m_967690();
    ((Sub*)((char*)this + 0x238))->m_9676f0(*(void**)((char*)this + 0x240), *(int*)((char*)this + 0x23c));
    ((Sub*)((char*)this + 0x22c))->m_967690();
    ((Sub*)((char*)this + 0x20c))->m_967690();
    ((CW*)this)->m_969d40();
}

// @ 0x0096acd0
void CW::SetRegion(void* p)
{
    ((CW*)this)->Clear();
    *(void**)((char*)this + 0x220) = p;
    ((Sub*)((char*)this + 0x20c))->m_9676f0(p, 0);
}

// @ 0x0096ad00
int ConsoleWindow::OnRebuild(EA::UTFWin::RenderContext_s0096_ad00* ctx)
{
    EA::UTFWin::RenderContext_s0096_ad00* pRC = (EA::UTFWin::RenderContext_s0096_ad00*)ctx;
    pRC->Begin2D(0);
    return 1;
}

// @ 0x0096b0b0
ConsoleWindow::ConsoleWindow(bool param2)
{
    char* this_ = (char*)this;
    char* esi = this_;
    EA::UTFWin::WindowVt* self = (EA::UTFWin::WindowVt*)this_;

    // UTFWin::Window::Window(this) -- base construction.
    Window_ctor(this_);

    *(void**)esi = (void*)0x1441c18;            // primary vtable
    *(void**)(esi + 4) = (void*)0x1441af8;      // IWindow vtable

    Console::InitChannelColors(esi + 0x20c, 0);

    *(int*)(esi + 0x21c) = 0x3e8;
    *(int*)(esi + 0x220) = 0x1000;
    *(int*)(esi + 0x224) = 0;
    *(int*)(esi + 0x228) = 0;
    *(int*)(esi + 0x22c) = (int)(esi + 0x22c);
    *(int*)(esi + 0x230) = (int)(esi + 0x22c);
    *(int*)(esi + 0x234) = 0;
    *(float*)(esi + 0x248) = 0.0f;
    *(float*)(esi + 0x24c) = 0.0f;
    *(int*)(esi + 0x240) = 1;
    *(int*)(esi + 0x23c) = 0x154df28;
    *(int*)(esi + 0x244) = 0;
    *(int*)(esi + 0x250) = 0;
    *(float*)(esi + 0x838) = 0.0f;
    *(float*)(esi + 0x83c) = 0.0f;
    *(float*)(esi + 0x840) = 0.0f;
    *(float*)(esi + 0x844) = 0.0f;

    // Typesetter / LineLayout sub-objects.
    new (esi + 0x258) EA::Text::Typesetter_s0096_ad00(false);
    new (esi + 0x788) EA::Text::LineLayout_s0096_ad00(false);

    *(int*)(esi + 0x848)   = -1;
    *(float*)(esi + 0x84c) = 0.0f;
    *(float*)(esi + 0x850) = 0.0f;
    *(float*)(esi + 0x854) = 0.0f;
    *(float*)(esi + 0x858) = 0.0f;
    *(int*)(esi + 0x85c)   = -1;
    *(unsigned char*)(esi + 0x860) = 0;
    *(unsigned char*)(esi + 0x861) = 0;
    *(int*)(esi + 0x864)   = 0;
    *(unsigned char*)(esi + 0x868) = param2 ? 1 : 0;
    *(float*)(esi + 0x86c) = 0.0f;

    Console::ResizeBuffers(esi + 0x20c, 0x1000, 0);
    ((IWindow_s0096_ad00*)(esi + 4))->SetFlag(0x10, true);

    EA::Text::StyleManager* sm = EA::Text::GetStyleManager(true);
    if (sm) {
        if (sm->GetStyle(0xefe945b2, 0) == 0) {
            EA::Text::TextStyle_s0096_ad00 style;
            // name copied from L"Trebuchet MS"
            style.mfSize = 9.0f;
            style.mHAlignment = 0;
            style.mTextWrap = 0;
            sm->AddStyle(0xefe945b2, &style);
        }
    }
}

// @ 0x0096b2d0
void* __stdcall Factory_ConsoleWindow_CreateInstance(int param1, void* param2)
{
    if (param2 == 0)
        param2 = (void*)FUN_009512c0();
    char* obj = (char*)FUN_009512d0(0x870, 4,
                                    "UTFWin/EA::UTFWinControls::ConsoleWindow", param2);
    if (obj != 0) {
        void* r = ::new (obj) ConsoleWindow(true);
        if (r != 0)
            return (char*)r + 4;
    }
    return 0;
}
