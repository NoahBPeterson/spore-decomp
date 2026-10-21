// src/game/UTFSpore_Win32/ConsoleWindow.cpp -- migrated from slice(s) s0096ad00, s00969e30 by tools/migrate/rewrite.py
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
extern "C" uint32_t __cdecl FNV1_String8(const char*, uint32_t, uint32_t);  // 0x932e80
struct Sub {                                   // sub-objects inside ConsoleWindow
    void m_967690();                           // 0x967690
    void m_9676f0(void*, int);                 // 0x9676f0
};
struct CW {
    void InvalidateLayout();                   // 0x9609b0  Window::InvalidateLayout
    void m_969d40();                           // 0x969d40
    int  BaseDoMessage(int);                   // 0x950bb0  Window::DoMessage
    __declspec(noinline) void Refresh(char);   // 0x969e30
    void ResetLayout();                        // 0x969ed0
    int  DoMessageProc(int);                   // 0x969f00
    int  Scroll(int, int, char, int);          // 0x969f80
    int  Init();                               // 0x96a670
    void Clear();                              // 0x96ab30
    void Find(int*, void**);                   // 0x96ab90
    void Destroy();                            // 0x96ac10
    void SetRegion(void*);                     // 0x96acd0
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
int CW::DoMessageProc(int msg)
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
int __cdecl FUN_0096a0a0(int, int, int, int)
{
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
    return 0;
}

// @ 0x0096a790
int __cdecl FUN_0096a790(int, int, int, int)
{
    return 0;
}

// @ 0x0096a860
int __cdecl FUN_0096a860(int, int, int)
{
    return 0;
}

// @ 0x0096a9b0
int __cdecl FUN_0096a9b0(int, int, int)
{
    return 0;
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
