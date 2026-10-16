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
extern "C" void FUN_008fe6d0(void* a, void* b, void* c);          // 0x8fe6d0
extern "C" void FUN_0095af00(void* p);                              // 0x95af00
extern "C" void FUN_009592a0(void* p);                              // 0x9592a0
extern "C" void FUN_00958110(void* p);                              // 0x958110
extern "C" void FUN_009580e0(void* p);                              // 0x9580e0
extern "C" void FUN_009588c0(void* p);                              // 0x9588c0
extern "C" void FUN_00960b40(void* p);                              // 0x960b40
extern "C" void FUN_00960ae0(void* p);                              // 0x960ae0
extern "C" int  FUN_0095fc50(void* p, int arg);                     // 0x95fc50
extern "C" void FUN_009634b60(void* out, void* a, void* b);         // 0x634b60
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
    char   pad_1d0[0xc];                // ..0x1dc
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
struct VtblE0 { char pad[0xe0]; void (__thiscall *fn)(void*, int); };
struct S961a50 { void f(); };
struct S961db0 { void f(void**, unsigned); };
struct S962100 { int* f(void*); void g(void*); };
struct S962180 { void* f(void*, void*, void*); };
struct S962360 { void* f(int, int, int); };
struct S962580 { void f(int, int); };
struct S9625b0 { int f(int, int, int); };
struct S962530 { void f(int, int); };
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
        float local_18 = -((*(float*)(p + 0x90) - *(float*)(p + 0x88)) * 0.5f);
        float local_14 = -((*(float*)(p + 0x94) - *(float*)(p + 0x8c)) * 0.5f);
        float local_10 = 0.0f;
        float local_c[3];
        float* pf = ((Mat44*)(p + 0xc4))->TransformPoint3(local_c, &local_18);
        local_18 = pf[0] + (f7 + f9) * 0.5f;
        local_14 = pf[1] + (f10 + f8) * 0.5f;
        local_10 = pf[2];
        for (unsigned i = *(unsigned*)(p + 0x38); i != 0; i = *(unsigned*)(i + 0x38)) {
            if ((*(unsigned*)(i + 0x2c) & 0x400) != 0) {
                float a = -local_18;
                float b = -local_14;
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
            local_18 = local_18 - (*(float*)(i + 0x90) - *(float*)(i + 0x88)) * 0.5f;
            local_14 = local_14 - (*(float*)(i + 0x94) - *(float*)(i + 0x8c)) * 0.5f;
            pf = ((Mat44*)(p + 0xc4))->TransformPoint3(local_c, &local_18);
            local_18 = pf[0] + (f7b + f9b) * 0.5f;
            local_14 = pf[1] + (f10b + f8b) * 0.5f;
            local_10 = pf[2];
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



// @ 0x00960fe0
bool Win::TestHit(float x, float y)
{
    char* p = (char*)this;
    float local_30 = (*(float*)(p + 0x90) - *(float*)(p + 0x88)) * 0.5f;
    float fVar1    = (*(float*)(p + 0x8c) - *(float*)(p + 0x84)) * 0.5f;
    float dx = x - fVar1;  if (dx < 0) dx = -dx;
    float dy = y - local_30; if (dy < 0) dy = -dy;
    if (fVar1 < dx || local_30 < dy)
        return false;
    float rect[4];
    bool cVar2 = ((GeomObj*)((char*)this - 4))->Geom(rect);
    if (cVar2) {
        float b[4];
        b[0] = 0.0f;
        b[1] = 0.0f;
        b[2] = *(float*)(p + 0x8c) - *(float*)(p + 0x84);
        b[3] = *(float*)(p + 0x90) - *(float*)(p + 0x88);
        FUN_009634b60(rect, rect, b);
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
    unsigned r = (*(unsigned(__thiscall**)(void*))*(void**)ip)(iface);
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
        FUN_008fe6d0(n, head, anchor);
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
    unsigned r = (*(unsigned(__thiscall**)(void*))*(void**)ip)(iface);
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
    FUN_009592a0(a);
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
    FUN_009580e0(m34);
    FUN_009588c0(m34);
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
                FUN_009592a0(a);
            goto lab;
        }
        if (flag == 1) {
            if ((mBits2c & 4) == 0) {
                FUN_00960b40(a - 4);
                if (!on) FUN_0095fc50(a - 4, 1);
                NotifyTree();
                if (mpMgr30 != 0)
                    FUN_00958110(mpMgr30);
            }
            goto lab;
        }
        if (flag != 2)
            goto lab;
        if (!on) FUN_0095fc50(a - 4, 1);
    } else if (flag != 0x400) {
        goto lab;
    }
    FUN_00960ae0(a - 4);
    NotifyTree();
lab:
    if (mpMgr30 != 0) {
        int local[3];
        local[0] = 0xe;
        local[1] = 1;
        local[2] = (int)old;
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
        void* alloc = (void*)dst[7];
        void* buf = (*(void*(__thiscall**)(void*, unsigned, int, void*))((char*)*(void**)alloc + 8))(
            alloc, size + 4, 0, (void*)dst[8]);
        *(unsigned*)((char*)buf + size) = 0xffffffff;
        dst[1] = (unsigned)buf;
        unsigned idx = 0;
        if (src[2] != 0) {
            do {
                unsigned* slot = (unsigned*)((char*)dst[1] + idx * 4);
                unsigned* node = *(unsigned**)((char*)src[1] + idx * 4);
                for (; node != 0; node = (unsigned*)node[4]) {
                    unsigned* obj = (unsigned*)(*(void*(__thiscall**)(void*, int, int, void*))(
                        (char*)*(void**)alloc + 8))(alloc, 0x18, 0, (void*)dst[8]);
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
  EA::ArgScript::cIParser* p;
  p = *(EA::ArgScript::cIParser**)(self + 0x1e0);
  if (p) { *(void**)(self + 0x1e0) = 0; p->Release(); }
  p = *(EA::ArgScript::cIParser**)(self + 0x1e8);
  if (p) { *(void**)(self + 0x1e8) = 0; p->Release(); }
  p = *(EA::ArgScript::cIParser**)(self + 0x1e4);
  if (p) { *(void**)(self + 0x1e4) = 0; p->Release(); }
  return true;
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
