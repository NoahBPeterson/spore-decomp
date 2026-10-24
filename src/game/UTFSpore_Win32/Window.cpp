// src/game/UTFSpore_Win32/Window.cpp -- migrated from slice(s) s00961db0, s00960be0, s0095ff20, s0095eeb0, s00925770 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Window.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <windows.h>
#include <stddef.h>
#include <string.h>
#include "EA/UTFWin/Window.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/IWindowMgr.h"
#include "EA/Audio/IPrimitive.h"
#include "EA/UTFWin/Transform.h"
#include "EA/UTFWin/cGetChildWindowCache.h"
#include "EA/ArgScript/cIParser.h"

// ---- items of slice s00925770 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Trace {
extern void FUN_00925d60();
}
}
namespace EA { namespace Trace { void FUN_00925d60(void* self); }}  // 0x00925d60 (defined below; used by a stub's inline body)
namespace EA {
namespace Trace {
struct HashHolder { void FUN_00925e60() { *(void**)this = (void*)0x0143e104; FUN_00925d60(); } };
}
}
// ---- items of slice s00925770 end

// ---- items of slice s0095eeb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl FUN_00958860(void*);
extern "C" void __cdecl FUN_009580E0(void*);
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd)
struct Window {
    char pad[0x28];
    volatile long mRefCount;   // +0x28
    char pad2[4];              // +0x2c
    int m30;                   // +0x30
    int m34;                   // +0x34
    int m38;                   // +0x38
    char pad3[0x1d4 - 0x3c];
    int m1d4;                  // +0x1d4
    int m1d8;                  // +0x1d8
    int m1dc;                  // +0x1dc

    Window* AsInterface(int iid);
    int     Release();
    int     GetAt34();
    void    Set1D8(int v);
    bool    IsAncestorOf(void* other);
    bool    Test30Slot48(int v);
    bool    Test30Slot54(int v);
    bool    AllDescendants(char param);
    bool    AllDescendantsAll(char param);
    int     FindChild(int arg);
    int     WalkChildren(int* iface);
    void    SetA8(int v);
    void    Set1D4(int v);
    void    SetArea(float* area);
    void    ResizeBy(float dx, float dy);
};
// ---- items of slice s0095eeb0 end

// ---- items of slice s0095ff20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl FUN_00958820(void*);
extern "C" int  __cdecl FUN_0095A0B0(void*, int);
extern "C" void __cdecl FUN_0095AF00(void*);
extern "C" void* __cdecl operator_new_size(unsigned int, const char*, int, int, const char*, int);
struct Window_s0095_ff20 {
    char  pad0[0x28];
    int   m28;                 // +0x28
    int   m2c;                 // +0x2c
    int   m30;                 // +0x30
    int   m34;                 // +0x34
    int   m38;                 // +0x38
    char  pad1[0x84 - 0x3c];
    float m84, m88, m8c, m90;  // +0x84
    float m94, m98, m9c, mA0;  // +0x94
    int   mA4;                 // +0xa4
    char  pad2[0x148 - 0xa8];
    float mMat[16];            // +0x148
    char  pad3[0x1d4 - 0x188];
    int   m1d4;                // +0x1d4
    int   m1d8;                // +0x1d8
    int   m1dc;                // +0x1dc
    void* m1e4;                // +0x1e4

    void MoveBy(float dx, float dy);            // 0x0095FF20
    void GrowBy(float dw, float dh);            // 0x0095FF70
    void MoveBy2(float dx, float dy);           // 0x0095FFD0
    void SetA4(int v);                          // 0x00960020
    void Set1E4(void* p);                       // 0x00960050
    void OnPaint2();                            // 0x009600A0
    void CallSlot();                            // 0x009600D0
    void TransformPoint(float x, float y, float* out);  // 0x00960100
    void ScreenToLocal(float x, float y, float* out);   // 0x00960180
    void GetChild(void* out, void* node);       // 0x009601E0
    void RemoveChild(void* node);               // 0x00960230
    void ClearChildren();                       // 0x00960280
    int  Dispatch14(void* p);                   // 0x009602C0
    int  Dispatch(void* p);                     // 0x009602F0
    void OnPaint();                             // 0x00960310 (partial)
    void DoMessage();                           // 0x00960410 (partial)
    void SetPhysicalArea();                     // 0x009608C0 (partial)
    void InvalidateLayout();                    // 0x009609B0 (partial)
};
extern "C" void __cdecl FUN_009580B0(void*);
extern "C" void __cdecl FUN_009588C0(void*);
// ---- items of slice s0095ff20 end

// ---- items of slice s00960be0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __stdcall FUN_008fe6d0(void* a, void* b, void* c);   // 0x8fe6d0
extern "C" void __fastcall FUN_0095af00(void* p);                     // 0x95af00
extern "C" void FUN_009592a0();                                       // 0x9592a0
extern "C" void __fastcall FUN_00958110(void* p);                     // 0x958110
extern "C" void FUN_009580e0();                                       // 0x9580e0
extern "C" void FUN_009588c0();                                       // 0x9588c0
extern "C" void __fastcall FUN_00960b40(void* p);                     // 0x960b40
extern "C" void __fastcall FUN_00960ae0(void* p);                     // 0x960ae0
extern "C" int  FUN_0095fc50();                                       // 0x95fc50
extern "C" int  FUN_009634b60();                                      // 0x634b60
typedef void (__thiscall *TC_void_1)(void*, void*);
typedef void (__thiscall *TC_void_p)(void*, char*);
typedef int  (__thiscall *TC_int_1)(void*, int);
typedef int  (__thiscall *TC_int_2)(void*, void*, void*);
extern "C" unsigned g_SerTypeTable[];                               // 0x154eea0
struct Mat44 {
    float m[16];
    float* TransformPoint3(float* out, const float* v);          // 0x95eeb0
    float* TransformPoint3NoTrans(float* out, const float* v);   // 0x95efb0
};
struct Transform {
    float m[17];                                                 // 0x44 bytes
    void Invert();                                               // 0x95f620
};
struct Node {
    Node*    next;      // +0x00
    Node*    prev;      // +0x04
    void*    field8;    // +0x08
    unsigned fieldc;    // +0x0c
};
struct IUnk {
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void QueryInterface(int id, void** out);    // +0x1c
};
struct IMgr {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void SendEvent(int a, int b, void* c, int d);   // +0x10
};
struct Win {
    char   pad_00[0x28];
    unsigned    mFlags28;               // +0x28
    unsigned char mBits2c;              // +0x2c
    unsigned char mBits2d;              // +0x2d
    unsigned char m2e, m2f;
    IMgr*  mpMgr30;                     // +0x30
    void*  mp34;                        // +0x34
    void*  m38;                         // +0x38
    void*  m3c;                         // +0x3c
    char   pad_40[0x20];                // ..0x60
    void*  m60;                         // +0x60
    void*  m64;                         // +0x64
    void*  m68;                         // +0x68
    void*  alloc6c;                     // +0x6c
    unsigned m70;                       // +0x70
    unsigned flag74;                    // +0x74
    char   pad_78[0xc];                 // ..0x84
    float  f84, f88, f8c, f90;          // +0x84
    char   pad_94[0x30];                // ..0xc4
    Transform mXformC4;                 // +0xc4
    Transform mXform108;                // +0x108
    char   pad_14c[0x40];               // ..0x18c
    Mat44  mMat18c;                     // +0x18c
    char   pad_1cc[0x10];               // ..0x1dc
    IUnk*  mpUnk1dc;                    // +0x1dc
    IUnk*  mpUnk1e0;                    // +0x1e0
    char   pad_1e4[0x1c];               // ..0x200

    void  SetUserData(IUnk* p);
    bool  TestHit(float x, float y);
    bool  ScreenToWindow(float x, float y, float* out);
    void  GetId(void** out);
    void  GetIdAddr(void** out);
    void  ListRemove(void* iface);
    void  ListInsert(void* iface);
    void* Find60(void* key);
    void  RecomputeFlags();
    void  NotifyTree();
    void  SerUpdate();
    void* CloneNode(int unused);
    void  SetFlag(unsigned flag, unsigned char on);
    void  Show();
    void  Hide();
    void  DestroyProc(void* proc);
    void  ClearProcs();
    void  PurgeProcs();
    bool  SerUpdateTrue(int unused);
};
struct GeomObj { bool Geom(float* out); };
struct ListCopy { unsigned* Copy(unsigned* src); };
struct Iface4 {
    void DestroyProcAndRecompute(int proc);
};
// ---- items of slice s00960be0 end

// ---- items of slice s00961db0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_166b190[];        // EA::UTFWin global cGetChildWindowCache singleton
extern void FUN_00a7bf40(void*, void*);
extern void FUN_009615c0(void*, void*, int);
extern int  FUN_6ab760(void*, void*);
extern void* FUN_009512c0(...);
struct RefObj {                 // object with a virtual Release() in vtable slot 1 (+4)
  virtual void r0();
  virtual void Release();
  virtual void r2();
};
struct AllocObj {               // allocator with a virtual deallocate(void*, unsigned) in slot 3
  virtual void a0();
  virtual void a1();
  virtual void a2();
  virtual void deallocate(void*, unsigned);
};
struct VObj4 {                  // object with virtuals; slot 3 (+0xc)
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual int v3(int);
};
struct VObj90 {                 // object with virtuals; slot 0x90/4 = 0x24
virtual void x00();
virtual void x01();
virtual void x02();
virtual void x03();
virtual void x04();
virtual void x05();
virtual void x06();
virtual void x07();
virtual void x08();
virtual void x09();
virtual void x0a();
virtual void x0b();
virtual void x0c();
virtual void x0d();
virtual void x0e();
virtual void x0f();
virtual void x10();
virtual void x11();
virtual void x12();
virtual void x13();
virtual void x14();
virtual void x15();
virtual void x16();
virtual void x17();
virtual void x18();
virtual void x19();
virtual void x1a();
virtual void x1b();
virtual void x1c();
virtual void x1d();
virtual void x1e();
virtual void x1f();
virtual void x20();
virtual void x21();
virtual void x22();
virtual void x23();
  virtual void v90();
};
extern void (*g_free_16f4aec)(void*);   // operator delete(void*) thunk in the IAT
struct S95e7a0 { void f(); };
struct S925f30 { void f(void*); };
struct S925e60 { void f(); };
struct S620230 { void f(); };
struct VtblE0 { char pad[0xe0]; void (__thiscall *fn)(void*, int); };
struct S961a50 { void f(); };
struct S961db0 { void f(void**, unsigned); };
struct S961e80 { bool f(); };
struct S961f20 { void f(void*); };
struct S962100 { int* f(void*); void g(void*); };
struct S962180 { void* f(void*, void*, void*); };
struct S962360 { void* f(int, int, int); };
struct S9625f0 { void f(void*); };
struct S959add0 { void f(void*); };
struct S960b40 { void f(); };
struct S960ae0 { void f(); };
struct S961450 { void f(); };
struct S961b40 { void f(void*); };
struct S965fcc0 { void* f(int, int, int); };
struct S9613e0 { void f(); };
struct S645ed0 { void find(void*, void*); };
struct S423650 { void assign(wchar_t*, wchar_t*); };
struct S962580 { void f(int, int); };
struct S9625b0 { int f(int, int, int); };
struct S962530 { void f(int, int); };
struct S962840 { bool f(void*); };
struct S962740 { void f(); };
struct S962950 { void f(); };
struct HNode { int k0; int k1; RefObj* a; RefObj* b; HNode* next; };
// ---- items of slice s00961db0 end

// @ 0x00925e60
namespace EA { namespace Trace {
void FUN_00925e60_hash(HashHolder* h)
{ h->FUN_00925e60(); }
}}  // namespace EA::Trace

// @ 0x0095f960
void * EA::UTFWin::Window::AsInterface(EA::COM::InterfaceId iid)
{
    if (iid == (int)0xee3f516e)
        goto common;
    if (iid == (int)0xeec58382)
        return this;
    if (iid != (int)0xeeee8218)
        return 0;
common:
    if (this == 0)
        return 0;
    return (Window*)((char*)this + 4);
}

// @ 0x0095f9a0
int Window::Release()
{
    int n = _InterlockedExchangeAdd(&mRefCount, -1) - 1;
    if (n == 0) {
        _InterlockedExchangeAdd(&mRefCount, 1);
        if (this != 0)
            (*(void(__thiscall**)(Window*, int))((char*)*(void**)this + 8))(this, 1);
    }
    return n;
}

// @ 0x0095f9d0
int Window::GetAt34()
{
    if (m34 != 0)
        return m34 + 4;
    return 0;
}

// @ 0x0095fa60
void Window::Set1D8(int v)
{
    if (m1d8 != v) {
        m1d8 = v;
        (*(void(__thiscall**)(Window*))((char*)*(void**)this + 0x90))(this);
        if (m30 != 0) {
            int local[3];
            local[0] = 0xe;
            local[1] = 4;
            int a = ((char*)this - 4) != 0 ? (int)this : 0;
            (*(void(__thiscall**)(int, int, int, int, int))((char*)*(void**)m30 + 0x10))(
                m30, a, a, (int)local, 0);
        }
    }
}

// @ 0x0095fad0
bool EA::UTFWin::Window::IsChild(EA::UTFWin::IWindow * other)
{
    if (other == 0)
        return false;
    void* p = (*(void*(__thiscall**)(void*))((char*)*(void**)other + 0x10))(other);
    while (p != 0) {
        if (p == (void*)(this))
            return true;
        p = (*(void*(__thiscall**)(void*))((char*)*(void**)p + 0x10))(p);
    }
    return false;
}

// @ 0x0095fb20
bool Window::Test30Slot48(int v)
{
    if (m30 != 0) {
        int r = (*(int(__thiscall**)(int, int))((char*)*(void**)m30 + 0x48))(m30, v);
        if (r == (int)this)
            return true;
    }
    return false;
}

// @ 0x0095fb60
bool Window::Test30Slot54(int v)
{
    if (m30 != 0) {
        int r = (*(int(__thiscall**)(int, int))((char*)*(void**)m30 + 0x54))(m30, v);
        if (r == (int)this)
            return true;
    }
    return false;
}

// @ 0x0095fbb0
bool Window::AllDescendants(char param)
{
    unsigned mask = ((param != 0) - 1) & 2 | 1;
    int node = m38;
    while (node != 0) {
        unsigned r = (*(unsigned(__thiscall**)(int))((char*)*(void**)(node + 4) + 0x28))(node + 4);
        if ((mask & r) == 0)
            break;
        node = *(int*)(node + 0x38);
    }
    return node == 0;
}

// @ 0x0095fc00
bool Window::AllDescendantsAll(char param)
{
    unsigned mask = ((param != 0) - 1) & 2 | 1;
    int node = m38;
    while (node != 0) {
        unsigned r = (*(unsigned(__thiscall**)(int))((char*)*(void**)(node + 4) + 0x28))(node + 4);
        if ((r & mask) == mask)
            return true;
        node = *(int*)(node + 0x38);
    }
    return false;
}

// @ 0x0095fc50
int Window::FindChild(int arg)
{
    int edi = m34;
    if (edi == 0)
        return 0;
    for (int i = 0; i < 2; i++) {
        int r = (*(int(__thiscall**)(int, int))((char*)*(void**)edi + 0x48))(edi, i);
        if (r == 0)
            break;
        r -= 4;
        if (r == 0)
            break;
        int node = r;
        while (node != 0 && node != (int)this)
            node = *(int*)(node + 0x38);
        if (node == 0)
            break;
        (void)arg;
        return node + 4;
    }
    return 0;
}

// @ 0x0095fcc0
int Window::WalkChildren(int* iface)
{
    (void)iface;
    return 0;
}

// @ 0x0095fd60
void Window::SetA8(int v)
{
    int old = *(int*)((char*)this + 0xa8);
    if (v != old) {
        *(int*)((char*)this + 0xa8) = v;
        int local[4];
        local[0] = 0x13;
        local[2] = v;
        local[3] = old;
        (*(void(__thiscall**)(Window*, int*))((char*)*(void**)this + 0x114))(this, local);
        if (*(int*)((char*)this + 0x1dc) != 0)
            (*(void(__thiscall**)(Window*))((char*)*(void**)this + 0x90))(this);
    }
}

// @ 0x0095fdc0
void Window::Set1D4(int v)
{
    if (m1d4 != v) {
        m1d4 = v;
        if (m30 != 0) {
            FUN_00958860((char*)this - 4);
            FUN_009580E0((char*)this - 4);
        }
    }
}

// @ 0x0095fe40
void Window::SetArea(float* area)
{
    float x = area[0];
    if (*(float*)((char*)this + 0x94) == x &&
        *(float*)((char*)this + 0x98) == area[1] &&
        *(float*)((char*)this + 0x9c) == area[2] &&
        *(float*)((char*)this + 0xa0) == area[3])
        return;
    *(float*)((char*)this + 0x94) = x;
    *(float*)((char*)this + 0x98) = area[1];
    *(float*)((char*)this + 0x9c) = area[2];
    *(float*)((char*)this + 0xa0) = area[3];
    (*(void(__thiscall**)(Window*))((char*)*(void**)this + 0x94))(this);
}

// @ 0x0095fec0
void Window::ResizeBy(float dx, float dy)
{
    float area[4];
    area[0] = dx;
    area[1] = dy;
    area[2] = (*(float*)((char*)this + 0x9c) - *(float*)((char*)this + 0x94)) + dx;
    area[3] = (*(float*)((char*)this + 0xa0) - *(float*)((char*)this + 0x98)) + dy;
    (*(void(__thiscall**)(Window*, float*))((char*)*(void**)this + 0x60))(this, area);
}

// @ 0x0095ff20
void Window_s0095_ff20::MoveBy(float dx, float dy)
{
    float a[4];
    a[0] = m94;
    a[1] = m98;
    a[2] = a[0] + dx;
    a[3] = a[1] + dy;
    (*(void(__thiscall**)(Window_s0095_ff20*, float*))((char*)*(void**)this + 0x60))(this, a);
}

// @ 0x0095ff70
void Window_s0095_ff20::GrowBy(float dw, float dh)
{
    float a[4];
    a[0] = dw;
    a[1] = dh;
    a[2] = (m8c - m84) + dw;
    a[3] = (m90 - m88) + dh;
    (*(void(__thiscall**)(Window_s0095_ff20*, float*))((char*)*(void**)this + 0x6c))(this, a);
}

// @ 0x0095ffd0
void Window_s0095_ff20::MoveBy2(float dx, float dy)
{
    float a[4];
    a[0] = m84;
    a[1] = m88;
    a[2] = a[0] + dx;
    a[3] = a[1] + dy;
    (*(void(__thiscall**)(Window_s0095_ff20*, float*))((char*)*(void**)this + 0x6c))(this, a);
}

// @ 0x00960020
void EA::UTFWin::Window::SetCursor(unsigned int v)
{
    if (mLocalXform.mTransform.yAxis.y != v) {
        mLocalXform.mTransform.yAxis.y = v;
        if (mpWinMgr != 0) {
            FUN_009580B0(this);
        }
    }
}

// @ 0x00960050
void Window_s0095_ff20::Set1E4(void* p)
{
    if (p != m1e4) {
        void* old = m1e4;
        if (p != old) {
            if (p != 0)
                (*(void(__thiscall**)(void*))((char*)*(void**)p))(p);
            m1e4 = p;
            if (old != 0)
                (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
        }
        (*(void(__thiscall**)(Window_s0095_ff20*))((char*)*(void**)this + 0x90))(this);
    }
}

// @ 0x009600a0
void Window_s0095_ff20::OnPaint2()
{
    if ((m2c & 4) == 0) {
        if ((m2c & 1) != 0 || (m28 & 1) != 0) {
            if (m30 != 0)
                FUN_00958820((char*)this - 4);
        }
    }
}

// @ 0x009600d0
void EA::UTFWin::Window::InvalidateTransform()
{
    if (mpWinMgr != 0)
        FUN_009588C0(this);
}

// @ 0x00960100
void Window_s0095_ff20::TransformPoint(float x, float y, float* out)
{
    Window_s0095_ff20* w = (Window_s0095_ff20*)((char*)this - 4);
    if (m30 != 0) {
        Window_s0095_ff20* found = 0;
        do {
            if ((*((uint8_t*)w + 0x30) & 0x20) != 0)
                found = w;
            w = (Window_s0095_ff20*)((char*)w + 0x38);
        } while (w != 0);
        if (found != 0)
            FUN_0095AF00(found);
    }
    out[0] = x;
    out[1] = y;
}

// @ 0x00960180
void Window_s0095_ff20::ScreenToLocal(float x, float y, float* out)
{
    (void)x;
    (void)y;
    out[0] = 0.0f;
    out[1] = 0.0f;
}

// @ 0x009601e0
void Window_s0095_ff20::GetChild(void* out, void* node)
{
    *(void**)out = node;
}

// @ 0x00960230
void Window_s0095_ff20::RemoveChild(void* node)
{
    if (node != 0) {
        (*(void(__thiscall**)(void*))((char*)*(void**)node))(node);
        (*(void(__thiscall**)(Window_s0095_ff20*, void*))((char*)*(void**)this + 0xdc))(this, node);
        (*(void(__thiscall**)(void*))((char*)*(void**)node + 0x1c))(node);
        (*(void(__thiscall**)(void*))((char*)*(void**)node + 4))(node);
    }
}

// @ 0x00960280
void Window_s0095_ff20::ClearChildren()
{
    int* head = (int*)((char*)this + 0x38);
    while (head[1] != (int)head) {
        int node = *head;
        int v;
        if (node == 0 || node == 8)
            v = 0;
        else
            v = node - 4;
        (*(void(__thiscall**)(Window_s0095_ff20*, int))((char*)*(void**)this + 0xe0))(this, v);
    }
}

// @ 0x009602c0
int Window_s0095_ff20::Dispatch14(void* p)
{
    if (m30 != 0)
        return (*(int(__thiscall**)(int, int, void*))((char*)*(void**)m30 + 0x14))(
            m30, *(int*)p, p);
    return 0;
}

// @ 0x009602f0
int Window_s0095_ff20::Dispatch(void* p)
{
    if (m30 != 0)
        return FUN_0095A0B0((char*)this - 4, (int)p);
    return 0;
}

// @ 0x00960310
void Window_s0095_ff20::OnPaint()
{
}

// @ 0x00960410
void Window_s0095_ff20::DoMessage()
{
}

// @ 0x00960550
void* __stdcall AllocPair(void* p)
{
    int* r = (int*)operator_new_size(
        0xc, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (r != 0) {
        r[0] = ((int*)p)[0];
        int* q = (int*)((int*)p)[1];
        r[1] = (int)q;
        if (q != 0)
            (*(void(__thiscall**)(int*))(*q))(q);
    }
    r[2] = 0;
    return r;
}

// @ 0x009605a0
void Rehash(void* self, unsigned int n)
{
    (void)self;
    (void)n;
}

// @ 0x00960650
int WindowListMarshaller_Read(void* self, void* src, void* dst)
{
    (void)self;
    (void)src;
    (void)dst;
    return 0;
}

// @ 0x009608c0
void EA::UTFWin::Window::SetPhysicalArea(EA::RectT<float> const & a1)
{
}

// @ 0x009609b0
void EA::UTFWin::Window::InvalidateLayout()
{
}

// @ 0x00960ae0
int FUN_00960AE0(void* self)
{
    (void)self;
    return 0;
}

// @ 0x00960b40
int FUN_00960B40(void* self)
{
    (void)self;
    return 0;
}

// @ 0x00960be0
bool GeomObj::Geom(float* out)
{
    char* p = (char*)this;
    unsigned uVar4 = *(unsigned*)(p + 0x2c) & 0x400;
    if (uVar4 == 0 && (*(unsigned char*)(p + 0x30) & 2) == 0)
        return false;
    bool bVar6 = uVar4 != 0;
    if (bVar6) {
        float f7  = *(float*)(p + 0x90);
        float f9  = *(float*)(p + 0x94);
        float f10 = *(float*)(p + 0x88);
        float f8  = *(float*)(p + 0x8c);
        out[0] = 0.0f;
        out[1] = 0.0f;
        out[2] = f7 - f10;
        out[3] = f9 - f8;
    }
    if ((*(unsigned char*)(p + 0x30) & 2) != 0) {
        float f7  = *(float*)(p + 0x90);
        float f9  = *(float*)(p + 0x88);
        float f10 = *(float*)(p + 0x94);
        float f8  = *(float*)(p + 0x8c);
        float pt[3];
        float tmp[3];
        pt[0] = -((*(float*)(p + 0x90) - *(float*)(p + 0x88)) * 0.5f);
        pt[1] = -((*(float*)(p + 0x94) - *(float*)(p + 0x8c)) * 0.5f);
        pt[2] = 0.0f;
        float* pf = ((Mat44*)(p + 0xc4))->TransformPoint3(tmp, pt);
        pt[0] = pf[0] + (f7 + f9) * 0.5f;
        pt[1] = pf[1] + (f10 + f8) * 0.5f;
        pt[2] = pf[2];
        for (unsigned i = *(unsigned*)(p + 0x38); i != 0; i = *(unsigned*)(i + 0x38)) {
            if ((*(unsigned*)(i + 0x2c) & 0x400) != 0) {
                float a = -pt[0];
                float b = -pt[1];
                float c = (*(float*)(i + 0x90) - *(float*)(i + 0x88)) + a;
                float d = (*(float*)(i + 0x94) - *(float*)(i + 0x8c)) + b;
                if (!bVar6) {
                    out[0] = a;
                    out[1] = b;
                    out[3] = d;
                    out[2] = c;
                } else if (out[2] <= a || c <= out[0] || out[3] <= b || d <= out[1]) {
                    out[3] = 0.0f;
                    out[1] = 0.0f;
                    out[0] = 0.0f;
                    out[2] = 0.0f;
                } else {
                    if (a < out[0]) a = out[0];
                    out[0] = a;
                    if (b < out[1]) b = out[1];
                    out[1] = b;
                    if (out[2] < c) c = out[2];
                    out[2] = c;
                    float t = out[3];
                    if (d <= out[3]) t = d;
                    out[3] = t;
                }
                bVar6 = true;
            }
            if ((*(unsigned char*)(i + 0x30) & 2) == 0)
                return bVar6;
            float f7b  = *(float*)(i + 0x90);
            float f9b  = *(float*)(i + 0x88);
            float f10b = *(float*)(i + 0x94);
            float f8b  = *(float*)(i + 0x8c);
            pt[0] = pt[0] - (*(float*)(i + 0x90) - *(float*)(i + 0x88)) * 0.5f;
            pt[1] = pt[1] - (*(float*)(i + 0x94) - *(float*)(i + 0x8c)) * 0.5f;
            pf = ((Mat44*)((char*)i + 0xc4))->TransformPoint3(tmp, pt);
            pt[0] = pf[0] + (f7b + f9b) * 0.5f;
            pt[1] = pf[1] + (f10b + f8b) * 0.5f;
            pt[2] = pf[2];
        }
    }
    return bVar6;
}

// @ 0x00960f20
void Win::SetUserData(IUnk* p)
{
    if (p != mpUnk1dc) {
        IUnk* old = mpUnk1dc;
        if (p != old) {
            if (p) p->AddRef();
            mpUnk1dc = p;
            if (old) old->Release();
        }
        void* q = 0;
        if (mpUnk1dc) mpUnk1dc->QueryInterface(0x19c46fb, &q);
        unsigned char bit = (unsigned char)((((q != 0) ? 8 : 0) ^ mBits2d) & 8);
        mBits2d ^= bit;
        if (mpMgr30) {
            int local[3];
            local[0] = 0xe;
            local[1] = 4;
            int self = (this != (Win*)4) ? (int)this : 0;
            (*(void(__thiscall**)(IMgr*, int, int, int*, int))((char*)*(void**)mpMgr30 + 0x10))(
                mpMgr30, self, self, local, 0);
        }
    }
}

static inline float AbsF(float v)
{
    unsigned u = *(unsigned*)&v & 0x7fffffffu;
    return *(float*)&u;
}

// @ 0x00960fe0
bool Win::TestHit(float x, float y)
{
    char* p = (char*)this;
    float local_30 = (*(float*)(p + 0x90) - *(float*)(p + 0x88)) * 0.5f;
    float fVar1    = (*(float*)(p + 0x8c) - *(float*)(p + 0x84)) * 0.5f;
    if (local_30 < AbsF(y - local_30) || fVar1 < AbsF(x - fVar1))
        return false;
    float rect[4];
    bool cVar2 = ((GeomObj*)((char*)this - 4))->Geom(rect);
    if (cVar2) {
        float b[4];
        b[0] = 0.0f;
        b[1] = 0.0f;
        b[2] = *(float*)(p + 0x8c) - *(float*)(p + 0x84);
        b[3] = *(float*)(p + 0x90) - *(float*)(p + 0x88);
        ((TC_int_2)FUN_009634b60)(rect, rect, b);
        if (x < rect[0]) return false;
        if (y < rect[1]) return false;
        if (rect[2] <= x) return false;
        if (rect[3] <= y) return false;
    }
    unsigned char local_31 = 1;
    if (mpMgr30 != 0 &&
        (((*(unsigned char*)(p + 0x28) & 0x20) != 0) || ((*(unsigned char*)(p + 0x2d) & 0xc) != 0))) {
        int local[4];
        local[0] = 0x14;
        local[1] = 0;   // overwritten below with pointer to local_31
        *(float*)((char*)local + 8) = x;
        *(float*)((char*)local + 0xc) = y;
        (*(void(__thiscall**)(IMgr*, int, int, int*, int))((char*)*(void**)mpMgr30 + 0x10))(
            mpMgr30, (int)this, (int)this, local, 0);
    }
    return local_31 != 0;
}

// @ 0x00961150
bool Win::ScreenToWindow(float x, float y, float* out)
{
    char* p = (char*)this;
    if (mpMgr30) {
        char* eax = p - 4;
        char* q = 0;
        do {
            if (*(unsigned char*)(eax + 0x30) & 0x20) q = eax;
            eax = *(char**)(eax + 0x38);
        } while (eax != 0);
        if (q) FUN_0095af00(q);
    }
    float in0[3];
    in0[0] = x;
    in0[1] = y;
    in0[2] = 0.0f;
    float a[3];
    ((Mat44*)(p + 0x18c))->TransformPoint3(a, in0);
    float in1[3];
    in1[0] = 0.0f;
    in1[1] = 0.0f;
    in1[2] = -1.0f;
    float b[3];
    ((Mat44*)(p + 0x18c))->TransformPoint3NoTrans(b, in1);
    if (b[2] <= 1.1920929e-07f && -1.1920929e-07f <= b[2]) {
        out[0] = 0.0f;
        out[1] = 0.0f;
        return false;
    }
    out[0] = a[0] - b[0] * (a[2] / b[2]);
    out[1] = a[1] - b[1] * (a[2] / b[2]);
    return true;
}

// @ 0x00961260
void Win::GetId(void** out)
{
    if (!out)
        return;
    *out = m38;
}

// @ 0x00961270
void Win::GetIdAddr(void** out)
{
    *out = (void*)&m38;
}

// @ 0x00961280
void Win::ListRemove(void* iface)
{
    char* ip = (char*)iface;
    if (!iface)
        return;
    unsigned r = (*(unsigned(__thiscall**)(void*))((char*)*(void**)ip + 0x10))(iface);
    if (r != (unsigned)((this != (Win*)4) ? (unsigned)this : 0))
        return;
    char* head = (char*)&m38;
    char* n = (char*)m38;
    char* anchor = ip + 4;
    if ((*(unsigned char*)(ip + 0x28) & 0x40) == 0) {
        if (n == anchor)
            return;
        while (true) {
            char* q = n ? n - 8 : 0;
            if ((*(unsigned char*)(q + 0x2c) & 0x40) == 0)
                break;
            n = *(char**)n;
            if (n == anchor)
                return;
        }
    }
    if (n != anchor) {
        FUN_008fe6d0(n, anchor, head);
        if (*(int*)((char*)this + 0x30) != 0)
            FUN_00958110(mpMgr30);
    }
}

// @ 0x00961300
void Win::ListInsert(void* iface)
{
    char* ip = (char*)iface;
    if (!iface)
        return;
    unsigned r = (*(unsigned(__thiscall**)(void*))((char*)*(void**)ip + 0x10))(iface);
    if (r != (unsigned)((this != (Win*)4) ? (unsigned)this : 0))
        return;
    char* anchor = ip + 4;
    char* head = (char*)&m38;
    if ((*(unsigned char*)(ip + 0x28) & 0x40) == 0) {
        FUN_008fe6d0(head, head, anchor);
    } else {
        char* n = *(char**)anchor;
        char* i = n;
        for (; i != head; i = *(char**)i) {
            char* q = i ? i - 8 : 0;
            if ((*(unsigned char*)(q + 0x2c) & 0x40) == 0)
                break;
        }
        if (i != anchor) {
            char* edx = *(char**)(ip + 8);
            *(char**)(n + 4) = edx;
            *(char**)edx = n;
            char* e2 = *(char**)(i + 4);
            *(char**)e2 = anchor;
            *(char**)(i + 4) = anchor;
            *(char**)(ip + 8) = e2;
            *(char**)anchor = i;
        }
    }
    if (*(int*)((char*)this + 0x30) != 0)
        FUN_00958110(mpMgr30);
}

// @ 0x009613a0
void* Win::Find60(void* key)
{
    Node* head = (Node*)&m60;
    Node* p = (Node*)m60;
    bool b = (key == 0);
    while (true) {
        if (p == head)
            return 0;
        if (b)
            break;
        b = (p->field8 == key);
        p = p->next;
    }
    return p->field8;
}

// @ 0x009613e0
void Win::RecomputeFlags()
{
    char* a = (char*)this;
    Node* head = (Node*)(a + 0x64);
    Node* p = *(Node**)(a + 0x64);
    *(unsigned char*)(a + 0x31) &= 0xf9;
    unsigned char bl = 0;
    for (; p != head; p = p->next) {
        unsigned v = p->fieldc;
        if (v & 2)     bl = 1;
        if (v & 0x100) *(unsigned char*)(a + 0x31) |= 2;
        if (v & 0x20)  *(unsigned char*)(a + 0x31) |= 4;
    }
    unsigned char cl = *(unsigned char*)(a + 0x31);
    unsigned char dl = cl & 1;
    if (dl == bl)
        return;
    dl = (unsigned char)((((cl ^ bl) & 1) ^ cl));
    *(unsigned char*)(a + 0x31) = dl;
    if (*(unsigned char*)(a + 0x2c) & 8)
        return;
    if (*(unsigned*)(a + 0x34) == 0)
        return;
    ((TC_void_1)FUN_009592a0)(*(void**)(a + 0x34), a);
}

// @ 0x00961450
void Win::NotifyTree()
{
    char* a = (char*)this;
    (*(void(__thiscall**)(char*))((char*)*(void**)(a + 4) + 0x90))(a + 4);
    Node* head = (Node*)(a + 0x3c);
    for (Node* p = *(Node**)(a + 0x3c); p != head; p = p->next) {
        char* q = p ? (char*)p - 8 : 0;
        if (((*(unsigned char*)(q + 0x30) & 1) != 0) || ((*(unsigned char*)(q + 0x2c) & 1) != 0))
            ((Win*)q)->NotifyTree();
    }
}

// @ 0x009614a0
void Win::SerUpdate()
{
    char* a = (char*)this;
    float* src = (float*)(a + 0xc4);
    float* dst = (float*)(a + 0x108);
    for (int i = 0; i < 0x11; i++)
        dst[i] = src[i];
    ((Transform*)dst)->Invert();
    void* q = 0;
    if (mpUnk1e0)
        mpUnk1e0->QueryInterface(0x19c46fb, &q);
    unsigned char bit = (unsigned char)((((q != 0) ? 8 : 0) ^ *(unsigned char*)(a + 0x31)) & 8);
    *(unsigned char*)(a + 0x31) ^= bit;
    void* m34 = *(void**)(a + 0x34);
    if (m34 == 0) {
        *(float*)(a + 0x88) = *(float*)(a + 0x98);
        *(float*)(a + 0x8c) = *(float*)(a + 0x9c);
        *(float*)(a + 0x90) = *(float*)(a + 0xa0);
        *(float*)(a + 0x94) = *(float*)(a + 0xa4);
        return;
    }
    if (*(unsigned char*)(a + 0x2c) & 1) {
        unsigned r = (*(unsigned(__thiscall**)(char*))((char*)*(void**)(a + 4) + 0x14))(a + 4);
        if (r != 0) {
            NotifyTree();
            goto lab;
        }
    }
    (*(void(__thiscall**)(char*))((char*)*(void**)(a + 4) + 0x90))(a + 4);
lab:
    ((TC_void_p)FUN_009580e0)(m34, a);
    ((TC_void_p)FUN_009588c0)(m34, a);
    FUN_00958110(m34);
    (*(void(__thiscall**)(char*))((char*)*(void**)(a + 4) + 0x94))(a + 4);
    int local[3];
    local[0] = 0xe;
    local[1] = -1;
    (*(void(__thiscall**)(void*, char*, char*, int*, int))((char*)*(void**)m34 + 0x10))(
        m34, a + 4, a + 4, local, 0);
}

// @ 0x00961680
void* Win::CloneNode(int unused)
{
    (void)unused;
    char* p = (char*)this;
    char* src = *(char**)(p + 0x20);
    void* alloc = *(void**)(p + 0x1c);
    char* obj = (char*)(*(void*(__thiscall**)(void*, int, int, void*))((char*)*(void**)alloc + 8))(
        alloc, 0x18, 0, src);
    if (obj) {
        *(unsigned*)obj = *(unsigned*)src;
        *(unsigned*)(obj + 4) = *(unsigned*)(src + 4);
        void* q = *(void**)(src + 8);
        *(void**)(obj + 8) = q;
        if (q) (*(void(__thiscall**)(void*))*(void**)q)(q);
        q = *(void**)(src + 0xc);
        *(void**)(obj + 0xc) = q;
        if (q) (*(void(__thiscall**)(void*))*(void**)q)(q);
    }
    *(unsigned*)(obj + 0x10) = 0;
    return obj;
}

// @ 0x009616f0
bool FUN_009616f0(unsigned* param_1, void* param_2, char* param_3, void* param_4)
{
    (void)param_2;
    unsigned* lp = (unsigned*)((char*)param_1[1] + 0x64);
    unsigned* lhead = lp;
    unsigned count = 0;
    for (unsigned* p = (unsigned*)*lp; p != lhead; p = (unsigned*)*p)
        count++;
    param_1[2] = count;
    unsigned* arr = (unsigned*)(*(void*(__thiscall**)(void*, unsigned, int))*(void**)param_4)(
        param_4, count * 4, 4);
    param_1[1] = (unsigned)arr;
    param_1[0] = g_SerTypeTable[(*(unsigned short*)(param_3 + 0xc)) & 0xfff];
    if (arr == 0)
        return false;
    for (unsigned* p = (unsigned*)*lhead; p != lhead; p = (unsigned*)*p) {
        *arr = p[2];
        arr++;
    }
    return true;
}

// @ 0x00961760
void Win::SetFlag(unsigned flag, unsigned char on)
{
    char* a = (char*)this;
    unsigned old = mFlags28;
    unsigned nv = ~flag & old;
    if (on) nv |= flag;
    if (nv == old)
        return;
    mFlags28 = nv;
    if (flag < 9) {
        if (flag == 8) {
            if ((mBits2d & 1) != 0)
                goto lab;
            if (mpMgr30 != 0)
                ((TC_void_1)FUN_009592a0)(mpMgr30, a - 4);
            goto lab;
        }
        if (flag == 1) {
            if ((mBits2c & 4) == 0) {
                FUN_00960b40(a - 4);
                if (!on) ((TC_int_1)FUN_0095fc50)(a - 4, 1);
                NotifyTree();
                if (mpMgr30 != 0)
                    FUN_00958110(mpMgr30);
            }
            goto lab;
        }
        if (flag != 2)
            goto lab;
        if (!on) ((TC_int_1)FUN_0095fc50)(a - 4, 1);
    } else if (flag != 0x400) {
        goto lab;
    }
    FUN_00960ae0(a - 4);
    NotifyTree();
lab:
    if (mpMgr30 != 0) {
        int local[4];
        local[0] = 0xe;
        local[1] = 1;
        local[2] = (int)old;
        local[3] = (int)nv;
        int self = (this != (Win*)4) ? (int)this : 0;
        (*(void(__thiscall**)(IMgr*, int, int, int*, int))((char*)*(void**)mpMgr30 + 0x10))(
            mpMgr30, self, self, local, 0);
    }
}

// @ 0x00961860
void Win::Show()
{
    char* a = (char*)this;
    if (*(unsigned char*)(a + 0x2c) & 1)
        return;
    if (((*(unsigned char*)(a + 0x28) & 1) == 0) && mpMgr30 != 0)
        FUN_00958110(mpMgr30);
    *(unsigned char*)(a + 0x2c) |= 1;
    FUN_00960b40(a - 4);
    NotifyTree();
    if (mpMgr30 != 0) {
        int local[3];
        local[0] = 0xf;
        local[1] = *(unsigned char*)(a + 0x2c) & 1;
        int self = (this != (Win*)4) ? (int)this : 0;
        (*(void(__thiscall**)(IMgr*, int, int, int*, int))((char*)*(void**)mpMgr30 + 0x10))(
            mpMgr30, self, self, local, 0);
    }
}

// @ 0x009618e0
void Win::Hide()
{
    char* a = (char*)this;
    if ((*(unsigned char*)(a + 0x2c) & 1) == 0)
        return;
    *(unsigned char*)(a + 0x2c) &= 0xfe;
    FUN_00960b40(a - 4);
    if (mpMgr30 != 0)
        FUN_00958110(mpMgr30);
    if (mpMgr30 != 0) {
        int local[3];
        local[0] = 0xf;
        local[1] = *(unsigned char*)(a + 0x2c) & 1;
        int self = (this != (Win*)4) ? (int)this : 0;
        (*(void(__thiscall**)(IMgr*, int, int, int*, int))((char*)*(void**)mpMgr30 + 0x10))(
            mpMgr30, self, self, local, 0);
    }
}

// @ 0x00961990
void Win::DestroyProc(void* proc)
{
    char* a = (char*)this;
    Node* head = (Node*)(a + 0x64);
    Node* p = *(Node**)(a + 0x64);
    if (p == head)
        return;
    while (p->field8 != proc) {
        p = p->next;
        if (p == head)
            return;
    }
    int local[3];
    local[0] = 0x1001;
    (*(void(__thiscall**)(void*, char*, int*))((char*)*(void**)proc + 0x18))(proc, a + 4, local);
    (*(void(__thiscall**)(void*))((char*)*(void**)proc + 4))(proc);
    if (*(int*)(a + 0x74) == 0) {
        Node* nx = p->next;
        Node* pv = p->prev;
        pv->next = nx;
        nx->prev = pv;
        (*(void(__thiscall**)(void*, Node*, int))((char*)*(void**)alloc6c + 0xc))(alloc6c, p, 0x10);
        return;
    }
    p->field8 = (void*)0x154ef48;
    p->fieldc = 0;
}

// @ 0x00961a30
void Iface4::DestroyProcAndRecompute(int proc)
{
    Win* w = (Win*)((char*)this - 4);
    w->DestroyProc((void*)proc);
    w->RecomputeFlags();
}

// @ 0x00961a50
void Win::ClearProcs()
{
    char* a = (char*)this;
    Node* head = (Node*)(a + 0x64);
    for (Node* p = *(Node**)(a + 0x64); p != head; p = p->next) {
        void* proc = p->field8;
        if (proc == (void*)0x154ef48)
            continue;
        int local[3];
        local[0] = 0x1001;
        (*(void(__thiscall**)(void*, char*, int*))((char*)*(void**)proc + 0x18))(proc, a + 4, local);
        (*(void(__thiscall**)(void*))((char*)*(void**)proc + 4))(proc);
        p->field8 = (void*)0x154ef48;
        p->fieldc = 0;
    }
    if (*(int*)(a + 0x74) == 0) {
        Node* p = *(Node**)(a + 0x64);
        while (p != head) {
            Node* nxt = p->next;
            (*(void(__thiscall**)(void*, Node*, int))((char*)*(void**)alloc6c + 0xc))(alloc6c, p, 0x10);
            p = nxt;
        }
        *(void**)(a + 0x64) = (void*)(a + 0x64);
        *(void**)(a + 0x68) = (void*)(a + 0x64);
    }
    RecomputeFlags();
}

// @ 0x00961ae0
void EA::UTFWin::Window::RemoveAllProcs()
{
    char* a = (char*)this;
    Node* head = (Node*)(a + 0x64);
    Node* p = *(Node**)(a + 0x64);
    while (p != head) {
        if (p->field8 == (void*)0x154ef48) {
            Node* nxt = p->next;
            Node* pv = p->prev;
            pv->next = nxt;
            nxt->prev = pv;
            (*(void(__thiscall**)(void*, Node*, int))((char*)*(void**)mText.mpBegin + 0xc))(mText.mpBegin, p, 0x10);
            p = nxt;
        } else {
            p = p->next;
        }
    }
}

// @ 0x00961b30
bool Win::SerUpdateTrue(int unused)
{
    (void)unused;
    SerUpdate();
    return true;
}

// @ 0x00961b40
unsigned* ListCopy::Copy(unsigned* src)
{
    unsigned* dst = (unsigned*)this;
    dst[0] = src[0];
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    dst[7] = src[7];
    dst[8] = src[8];
    if (dst[3] != 0) {
        unsigned size = dst[2] * 4;
        void* buf = (*(void*(__thiscall**)(void*, unsigned, int, void*))((char*)*(void**)dst[7] + 8))(
            (void*)dst[7], size + 4, 0, (void*)dst[8]);
        *(unsigned*)((char*)buf + size) = 0xffffffff;
        dst[1] = (unsigned)buf;
        unsigned idx = 0;
        if (src[2] != 0) {
            do {
                unsigned* slot = (unsigned*)((char*)dst[1] + idx * 4);
                unsigned* node = *(unsigned**)((char*)src[1] + idx * 4);
                for (; node != 0; node = (unsigned*)node[4]) {
                    unsigned* obj = (unsigned*)(*(void*(__thiscall**)(void*, int, int, void*))(
                        (char*)*(void**)dst[7] + 8))((void*)dst[7], 0x18, 0, (void*)dst[8]);
                    if (obj != 0) {
                        obj[0] = node[0];
                        obj[1] = node[1];
                        void* q = (void*)node[2];
                        obj[2] = (unsigned)q;
                        if (q) (*(void(__thiscall**)(void*))*(void**)q)(q);
                        q = (void*)node[3];
                        obj[3] = (unsigned)q;
                        if (q) (*(void(__thiscall**)(void*))*(void**)q)(q);
                    }
                    obj[4] = 0;
                    *slot = (unsigned)obj;
                    slot = obj + 4;
                }
                idx++;
            } while (idx < src[2]);
        }
        return dst;
    }
    dst[2] = 1;
    dst[1] = 0x154df28;
    dst[3] = 0;
    dst[6] = 0;
    return dst;
}

// @ 0x00961d50
bool FUN_00961d50(Win* p)
{
    p->SerUpdate();
    return true;
}

// @ 0x00961db0
void S961db0::f(void** pbuckets, unsigned count)
{
  HNode** buckets = (HNode**)pbuckets;
  for (unsigned i = 0; i < count; i++) {
    HNode* p = buckets[i];
    while (p) {
      HNode* node = p;
      RefObj* r = node->b;
      HNode* next = p->next;
      if (r) r->Release();
      r = node->a;
      if (r) r->Release();
      ((AllocObj*)*(void**)((char*)this + 0x1c))->deallocate(node, 0x18);
      p = next;
    }
    buckets[i] = 0;
  }
}

// @ 0x00961e20
bool FUN_00961e20(void* a, void* b)
{
  void* obj = *(void**)((char*)a + 4);
  ((S961a50*)obj)->f();
  unsigned n = *(unsigned*)((char*)b + 8);
  char* p = (char*)(*(int*)((char*)b + 4) + n * 4 - 4);
  while (n) {
    void* q = *(void**)p;
    n--;
    p -= 4;
    if (q) {
      int r = ((int(__thiscall*)(void*, int))((void**)(*(void***)q))[3])(q, (int)0x2f009dd0);
      if (r) {
        void* base = (char*)obj + 4;
        ((void(__thiscall*)(void*, int))((void**)(*(void***)base))[0x41])(base, r);
      }
    }
  }
  return 1;
}

// @ 0x00961e80
bool EA::UTFWin::Window::Shutdown()
{
  ((S961a50*)this)->f();
  char* self = (char*)this;
  int* lst = (int*)(self + 0x3c);
  if (lst[1] != (int)lst) {
    char* base = self + 4;
    do {
      char* v = *(char**)(self + 0x40);
      char* adj;
      if (v) { v -= 8; adj = v ? v + 4 : 0; }
      else adj = 0;
      ((VtblE0*)*(void**)base)->fn(base, (int)(size_t)adj);
    } while (lst[1] != (int)lst);
  }
  RefObj* p;
  p = *(RefObj**)(self + 0x1e0);
  if (p) { *(void**)(self + 0x1e0) = 0; p->Release(); }
  p = *(RefObj**)(self + 0x1e8);
  if (p) { *(void**)(self + 0x1e8) = 0; p->Release(); }
  p = *(RefObj**)(self + 0x1e4);
  if (p) { *(void**)(self + 0x1e4) = 0; p->Release(); }
  return true;
}

// @ 0x00961f20
void S961f20::f(void* key)
{
  char* self = (char*)this;
  if (FUN_6ab760(self + 0xac, key)) return;
  wchar_t* k = (wchar_t*)key;
  wchar_t* e = k;
  while (*e) e++;
  ((S423650*)(self + 0xac))->assign(k, e);
  ((VObj90*)self)->v90();
  int* m = *(int**)(self + 0x30);
  if (m) {
    void* base = self;
    int tmp[2];
    tmp[0] = 0xe; tmp[1] = 2;
    ((void(__thiscall*)(void*, int, int, void*, int))((void**)(*(void***)m))[4])(
        m, (int)(uint32_t)(size_t)base, (int)(uint32_t)(size_t)base, tmp, 0);
  }
}

// @ 0x00961fc0
void EA::UTFWin::Window::AddProc(EA::UTFWin::IWinProc * win)
{
  char* self = (char*)static_cast<EA::UTFWin::IWindow *>(this);
  int* head = (int*)(self + 0x60);
  int* it = *(int**)head;
  int best = (int)0x80000000;
  int* bestIt = head;
  int prio = ((int(__thiscall*)(void*))((void**)(*(void***)win))[4])(win);
  if (it != head) {
    do {
      void* n = *(void**)((char*)it + 8);
      if (n != (void*)0x154ef48) {
        if (n == win) {
          int old = *(int*)((char*)it + 0xc);
          int v = ((int(__thiscall*)(void*))((void**)(*(void***)win))[5])(win);
          *(int*)((char*)it + 0xc) = v;
          if (((v ^ old) & 2) == 0) return;
          ((S9613e0*)self)->f();
          return;
        }
        int p = ((int(__thiscall*)(void*))((void**)(*(void***)n))[4])(n);
        if (p <= prio && best < p) { bestIt = it; best = p; }
      }
      it = *(int**)it;
    } while (it != head);
  }
  ((void(__thiscall*)(void*))((void**)(*(void***)win))[0])(win);
  int v = ((int(__thiscall*)(void*))((void**)(*(void***)win))[5])(win);
  void* b = *(void**)(self + 0x68);
  int* node = (int*)((void*(__thiscall*)(void*, int, int, int))((void**)(*(void***)b))[2])(
      b, 0x10, 0, *(int*)(self + 0x6c));
  if (node + 2) { node[2] = (int)(size_t)win; node[3] = v; }
  *node = (int)(size_t)bestIt;
  node[1] = bestIt[1];
  *(int*)bestIt[1] = (int)(size_t)node;
  bestIt[1] = (int)(size_t)node;
  ((S9613e0*)self)->f();
  ((void(__thiscall*)(void*, int, int))((void**)(*(void***)win))[6])(win, (int)(uint32_t)(size_t)self, 0);
  if (*(int*)(self + 0x30) != 0)
    ((void(__thiscall*)(void*, int, int))((void**)(*(void***)win))[6])(win, (int)(uint32_t)(size_t)self, 0);
}

// @ 0x00962100
int* S962100::f(void* key)
{
  char* self = (char*)this;
  int found;
  ((S645ed0*)self)->find(&found, key);
  int cnt = *(int*)(self + 8);
  int* buckets = *(int**)(self + 4);
  if ((void*)(uint32_t)found != (void*)buckets[cnt])
    return (int*)((char*)(uint32_t)found + 4);
  int k = *(int*)key;
  int local[3];
  FUN_009615c0(local, &k, 0);
  return (int*)((char*)(uint32_t)local[0] + 4);
}

// @ 0x00962180
void* S962180::f(void* a_, void* b_, void* c_)
{
  int* a = (int*)a_;
  char* b = (char*)b_;
  int* c = (int*)c_;
  int iVar1 = *(int*)(b + 0x10);
  a[1] = (int)(size_t)c;
  *a = iVar1;
  while (iVar1 == 0) {
    a[1] += 4;
    iVar1 = *(int*)(size_t)a[1];
    *a = iVar1;
  }
  int iVar2 = *c;
  if (iVar2 == (int)(size_t)b) {
    *c = *(int*)(iVar2 + 0x10);
  } else {
    int i3 = *(int*)(iVar2 + 0x10);
    while (i3 != (int)(size_t)b) { iVar2 = i3; i3 = *(int*)(i3 + 0x10); }
    *(int*)(iVar2 + 0x10) = *(int*)(i3 + 0x10);
  }
  RefObj* r;
  r = *(RefObj**)(b + 0xc);
  if (r) r->Release();
  r = *(RefObj**)(b + 8);
  if (r) r->Release();
  ((AllocObj*)*(void**)((char*)this + 0x1c))->deallocate(b, 0x18);
  *(int*)((char*)this + 0xc) -= 1;
  return a_;
}

// @ 0x00962360
void* S962360::f(int a, int b, int c)
{
  char* self = (char*)this;
  int local_1c = a;
  unsigned local_20 = (unsigned)b;
  FUN_00a7bf40(&local_1c, &local_1c);
  while ((void*)(uint32_t)local_1c != (void*)*(int*)(*(int*)(self + 4) + *(int*)(self + 8) * 4)) {
    void* node = (void*)(uint32_t)local_1c;
    int v = *(int*)((char*)node + 0xc);
    int id = ((int(__thiscall*)(void*))((void**)(*(void***)*(void**)((char*)node + 8))[4]))(*(void**)((char*)node + 8));
    if (id == v) return *(void**)((char*)node + 8);
    if (*(RefObj**)((char*)node + 8)) ((RefObj*)*(void**)((char*)node + 8))->r0();
    if (*(RefObj**)((char*)node + 0xc)) ((RefObj*)*(void**)((char*)node + 0xc))->r0();
    int tmp[1];
    ((S962180*)self)->f(tmp, node, (void*)(size_t)local_20);
    if (*(RefObj**)((char*)node + 0xc)) ((RefObj*)*(void**)((char*)node + 0xc))->Release();
    if (*(RefObj**)((char*)node + 8)) ((RefObj*)*(void**)((char*)node + 8))->Release();
    FUN_00a7bf40(&local_1c, &local_1c);
  }
  void* found = ((S965fcc0*)self)->f(a, b, c);
  return found;
}

// @ 0x00962530
void S962530::f(int a, int b)
{
  char* self = (char*)this + 0x1e8;
  if (b != 0) {
    int* slot = ((S962100*)self)->f(&a);
    int old = *slot;
    if (b != old) {
      ((RefObj*)b)->r0();
      *slot = b;
      if (old) ((RefObj*)old)->Release();
    }
  } else {
    ((S962100*)self)->g(&a);
  }
}

// @ 0x00962580
void S962580::f(int a, int b)
{
  int t = (int)(size_t)this;
  int adj = (t - 4) ? t : 0;
  ((S962360*)g_166b190)->f(adj, a, b);
}

// @ 0x009625b0
int S9625b0::f(int a, int b, int c)
{
  int t = (int)(size_t)this;
  int adj = (t - 4) ? t : 0;
  void* p = ((S962360*)g_166b190)->f(adj, a, c);
  if (p) return ((VObj4*)p)->v3(b);
  return 0;
}

// @ 0x009625f0
void EA::UTFWin::cGetChildWindowCache::Remove(EA::UTFWin::IWindow * win)
{
  char* self = (char*)this;
  int local_vec[64];
  int* vecBegin = local_vec;
  int* vecEnd = local_vec;
  int** buckets = *(int***)(self + 4);
  int* it = *buckets;
  int** bit = buckets;
  if (!it) {
    bit = buckets + 1;
    it = buckets[1];
    while (!it) { bit++; it = *bit; }
  }
  int count = *(int*)(self + 8);
  if ((void*)it != (void*)buckets[count]) {
    do {
      int* next = *(int**)((char*)it + 0x10);
      int** bit2 = bit;
      while (!next) { bit2++; next = *(int**)bit2; }
      char* ci = (char*)it + 8;
      if (*(void**)it == win || *(void**)(ci + 0) == win || *(void**)(ci + 4) == win) {
        int w = *(int*)(ci + 0);
        if (vecEnd < local_vec + 64) { *vecEnd++ = w; if (w) ((RefObj*)(uint32_t)w)->r0(); }
        else { int tmp[2]; tmp[0] = w; ((S9613e0*)self)->f(); }
        int wp = *(int*)(ci + 4);
        if (vecEnd < local_vec + 64) { *vecEnd++ = wp; if (wp) ((RefObj*)(uint32_t)wp)->r0(); }
        else { int tmp[2]; tmp[0] = wp; ((S9613e0*)self)->f(); }
        ((S962180*)self)->f(0, it, bit2);
      }
      bit = bit2;
      it = next;
    } while ((void*)it != (void*)buckets[count]);
  }
  volatile int dummy = 0; (void)dummy;
}

// @ 0x00962740
void S962740::f()
{
  int* self = (int*)this;
  *self = (int)0x1440b44;
  *(int*)((char*)self + 4) = (int)0x14431f8;
  ((S961e80*)self)->f();
  ((S961db0*)((char*)self + 0x1ec))->f((void**)*(void**)((char*)self + 0x1f0), *(unsigned*)((char*)self + 0x1f4));
  *(int*)((char*)self + 0x1f8) = 0;
  if (*(unsigned*)((char*)self + 0x1f4) > 1) g_free_16f4aec(*(void**)((char*)self + 0x1f0));
  RefObj* p;
  p = *(RefObj**)((char*)self + 0x1e8); if (p) p->Release();
  p = *(RefObj**)((char*)self + 0x1e4); if (p) p->Release();
  p = *(RefObj**)((char*)self + 0x1e0); if (p) p->Release();
  int b = *(int*)((char*)self + 0xb0);
  if ((2 < (*(int*)((char*)self + 0xb8) - b)) && b) g_free_16f4aec((void*)b);
  char* head = (char*)self + 0x64;
  char* it = *(char**)((char*)self + 0x64);
  while (it != head) {
    char* nx = *(char**)it;
    void* b = *(void**)((char*)self + 0x6c);
    ((void(__thiscall*)(void*, void*, int))((void**)(*(void***)b))[3])(b, it, 0x10);
    it = nx;
  }
  ((S925e60*)((char*)self + 0x44))->f();
  ((S620230*)((char*)self + 0x3c))->f();
  *(int*)((char*)self + 4) = (int)0x13eb938;
  *self = (int)0x13eb938;
}

// @ 0x00962840
bool S962840::f(void* win)
{
  char* self = (char*)this;
  ((S9625f0*)g_166b190)->f(win);
  char* obj;
  if (win) obj = (char*)win - 4; else obj = 0;
  ((void(__thiscall*)(void*))((void**)(*(void***)obj))[0])(obj);
  *(int*)(obj + 0x38) = (int)((char*)self - 4);
  int* it = *(int**)(self + 0x38);
  int* head = (int*)(self + 0x38);
  while (it != head) {
    int* n = it ? it - 2 : 0;
    if ((*(unsigned char*)((char*)n + 0x2c) & 0x40) == 0) break;
    it = *(int**)it;
  }
  int* p2 = (int*)it[1];
  int* p4 = (int*)(obj + 8);
  it[1] = (int)(size_t)p4;
  *p2 = (int)(size_t)p4;
  *(int*)(obj + 0xc) = (int)(size_t)p2;
  *p4 = (int)(size_t)it;
  int mgr = *(int*)(self + 0x30);
  if (mgr) ((S959add0*)mgr)->f(obj);
  if (((bool(__thiscall*)(void*))((void**)(*(void***)obj))[6])(obj)) {
    ((S960b40*)((char*)self - 4))->f();
    ((S960ae0*)((char*)self - 4))->f();
    ((S961450*)((char*)self - 4))->f();
    return true;
  }
  ((void(__thiscall*)(void*, int))((void**)(*(void***)self))[0x38])(self, (int)(size_t)p4 + 4);
  return false;
}

// @ 0x00962950
void S962950::f()
{
  char* self = (char*)this;
  int tmp[8];
  ((S961b40*)tmp)->f(self);
  ((S961db0*)self)->f((void**)*(void**)(self + 4), *(unsigned*)(self + 8));
  *(int*)(self + 0xc) = 0;
  if (*(unsigned*)(self + 8) > 1) {
    void* alloc = *(void**)(self + 0x1c);
    ((void(__thiscall*)(void*, void*, int))((void**)(*(void***)alloc))[3])(alloc, *(void**)(self + 4),
                                                                            *(int*)(self + 8) * 4 + 4);
  }
  *(void**)(self + 0x1c) = FUN_009512c0();
  *(int*)(self + 0x10) = 0x3f800000;
  *(int*)(self + 0x14) = 0x40000000;
  *(int*)(self + 0x20) = 0;
  *(int*)(self + 8) = 1;
  *(int*)(self + 4) = (int)0x154df28;
  *(int*)(self + 0xc) = 0;
  *(int*)(self + 0x18) = 0;
  unsigned n = *(unsigned*)((char*)tmp + 8);
  if (n > 1) {
    void* alloc = *(void**)((char*)tmp + 0x10);
    ((void(__thiscall*)(void*, void*, unsigned))((void**)(*(void***)alloc))[3])(
        alloc, *(void**)((char*)tmp + 4), n * 4 + 4);
  }
}

// @ 0x00962a10
EA::UTFWin::Window::Window()
{
  char* self = (char*)this;
  *(int*)(self + 0xc) = 0; *(int*)(self + 8) = 0;
  *(int*)(self + 0x14) = 0; *(int*)(self + 0x10) = 0;
  *(int*)(self + 0x1c) = 0; *(int*)(self + 0x18) = 0;
  *(int*)(self + 0x24) = 0; *(int*)(self + 0x20) = 0;
  *(int*)(self + 4) = (int)0x13f1ab0;
  *(int*)(self) = (int)0x1440b44;
  *(int*)(self + 4) = (int)0x14431f8;
  *(int*)(self + 0x28) = 0;
  *(unsigned char*)(self + 0x31) &= 0xf0;
  *(int*)(self + 0x2c) = 3;
  *(unsigned char*)(self + 0x30) = 0;
  *(int*)(self + 0x34) = 0;
  *(int*)(self + 0x38) = 0;
  *(int*)(self + 0x40) = (int)(self + 0x3c);
  *(int*)(self + 0x3c) = (int)(self + 0x3c);
  void* t = FUN_009512c0(0x10, 0x10);
  ((S925f30*)(self + 0x44))->f(t);
  *(int*)(self + 0x70) = 0;
  *(int*)(self + 0x6c) = (int)(self + 0x44);
  *(int*)(self + 0x64) = (int)(self + 0x64);
  *(int*)(self + 0x68) = (int)(self + 0x64);
  *(int*)(self + 0x74) = 0; *(int*)(self + 0x78) = 0; *(int*)(self + 0x7c) = 0;
  *(int*)(self + 0x80) = 0; *(int*)(self + 0x84) = 0;
  for (int i = 0; i < 8; i++) *(float*)(self + 0x88 + i * 4) = 0.0f;
  *(int*)(self + 0xa8) = 0; *(int*)(self + 0xac) = 0;
  *(int*)(self + 0xb8) = (int)0x1667bae;
  *(int*)(self + 0xb0) = (int)0x1667bac;
  *(int*)(self + 0xb4) = (int)0x1667bac;
  *(int*)(self + 0x1d4) = 0; *(int*)(self + 0x1dc) = 0;
  *(int*)(self + 0x1d8) = -1;
  *(int*)(self + 0xc0) = 1;
  *(int*)(self + 0x1e0) = 0; *(int*)(self + 0x1e4) = 0; *(int*)(self + 0x1e8) = 0;
  *(float*)(self + 0x1fc) = 1.0f;
  *(float*)(self + 0x200) = 2.0f;
  *(int*)(self + 0x1f8) = 0;
  *(int*)(self + 0x204) = 0;
  *(int*)(self + 0x1f4) = 1;
  *(int*)(self + 0x1f0) = (int)0x154df28;
  ((S95e7a0*)(self + 0xc4))->f();
  for (int i = 0; i < 0x11; i++) {
    *(int*)(self + 0x108 + i * 4) = *(int*)(self + 0xc4 + i * 4);
    *(int*)(self + 0x14c + i * 4) = *(int*)(self + 0xc4 + i * 4);
    *(int*)(self + 0x190 + i * 4) = *(int*)(self + 0xc4 + i * 4);
  }
  return;
}
