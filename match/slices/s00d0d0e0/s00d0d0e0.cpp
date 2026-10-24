// Slice s00d0d0e0 -- Simulator::cCommunityEditor helpers (SporeApp.exe
// 0x00d0d0e0..0x00d0dfb2).  Every function here is a __thiscall member of the
// community-editor object (`CE`, engine name SP::cCommunityEditor).
//
// Frozen batch gold6.  32-bit x86, MSVC 2008 SP1, flags
// /O2 /MD /Gy /TP /arch:SSE /GS- (no /EHsc).

#include "types.h"

// Declare N throwaway virtuals so a named slot lands at the right vtable index.
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

typedef unsigned char u8;

// ---------------------------------------------------------------------------
// A reference-counted object whose vtable slot +0x0c takes one int and returns
// void (used by the mSpan vector loops).
// ---------------------------------------------------------------------------
struct RefObj {
    PV2 PV
    virtual void Slot0C(int a);            // +0x0c
    PV4
    virtual void Slot20(void* p);          // +0x20  (refcount release stub)
};

struct Vector3 { float x, y, z; };

// An object that carries a refcount pair at the top of its vtable.
struct RCObj {
    virtual void AddRef();                 // +0x00
    virtual void Release();                // +0x04
};

// The pointer vector living at +0x260 of CE.
struct PtrVec {
    RCObj** mBegin;                        // +0x260
    RCObj** mEnd;                          // +0x264
    RCObj** mCap;                          // +0x268
    // 0x00533500  __thiscall (ecx = &vec): erase/clear [first,last)
    void Fn533500(RCObj** first, RCObj** last);
    // 0x00a0a360  __thiscall (ecx = &vec): grow + insert, ret 8
    void FnA0A360(RCObj** pos, RCObj** value);
    void push_back(RCObj* v)
    {
        if (mEnd < mCap) {
            RCObj** p = mEnd;
            mEnd = p + 1;
            if (p != 0)
                *p = v;
            if (v != 0)
                v->AddRef();
        } else {
            FnA0A360(mEnd, &v);
        }
    }
};

// Interface object with a vtable slot +0x0c returning a sibling object.
struct Obj;

struct Obj {
    PV2 PV
    virtual void* Slot0C(unsigned id);             // +0x0c
    virtual void* Slot10();
    PV8 PV8 PV4                                    // slots +0x10 .. +0x58
    virtual char  Slot58();                        // +0x58
    PV
    virtual Vector3* Slot5C();                     // +0x60-ish (unused here)
    // non-virtual helpers
    void FnBDCA30(Vector3* out, void* param);      // 0x00bdca30
};

struct CE {
    char   pad000[0x40];
    Obj*   m40;                            // +0x40
    char   pad044[0x260 - 0x44];
    PtrVec mSpan;                          // +0x260  vector<RCObj*>
    char   pad26C[0x10];                   // +0x26c..+0x27b
    int    m27c;                           // +0x27c

    void FUN_00d0dea0();
    void StartVehicleAttractorEffects(void* param_2);  // 0x00d0ddc0
    void FnBBD0(Vector3 v, RCObj** out);               // 0x00d0bbd0, ret 0x10
};

// 0x00d0dea0 -- call vfn(+0x0c)(0) on every live element of mSpan, then clear it.
void CE::FUN_00d0dea0()
{
    PtrVec& v = this->mSpan;
    int n = (int)(v.mEnd - v.mBegin);
    int i = 0;
    if (0 < n) {
        for (; i < n; ++i) {
            RefObj* p = (RefObj*)v.mBegin[i];
            if (p != 0)
                p->Slot0C(0);
        }
    }
    v.Fn533500(v.mBegin, v.mEnd);
}

// @ 0x00d0ddc0 -- if the attractor-effect list is empty, build one entry: ask
// the manipulated object for its sub-object, turn the dropped key into a
// vector3, spawn the effect object and push it into mSpan.
void CE::StartVehicleAttractorEffects(void* param_2)
{
    if (this->mSpan.mBegin != this->mSpan.mEnd)
        return;
    Obj* p = 0;
    if (this->m40 != 0)
        p = (Obj*)this->m40->Slot0C(0xee9b2232);
    Vector3 v;
    p->FnBDCA30(&v, param_2);
    RCObj* local = 0;
    this->m27c = 0x9fdf8751;
    this->FnBBD0(v, &local);
    this->mSpan.push_back(local);
    if (local != 0)
        local->Release();
}

// ---------------------------------------------------------------------------
// Functions assigned to this slice that are only categorised (see partial.txt):
//
// @ 0x00d0d0e0  FUN_00d0d0e0 - eastl RBTree multi-insert_impl (RBTreeIncrement
//               0x921580 + FUN_00d0ca00/FUN_00d0cb30); partial, no source.
// @ 0x00d0d200  Simulator::cCommunityEditor::cCommunityEditor - 842-byte ctor;
//               base-class vtable stores are inlined then overwritten by the
//               real cCommunityEditor vtables, plus 4 eastl container inits;
//               partial, no source.
// @ 0x00d0d570  FUN_00d0d570 - drop the manipulated noun, retarget the editor to
//               a picked object and push an effect handle into mSpan; partial,
//               no source.
// @ 0x00d0d6b0  SP::CreatedInterpolatedVectorList - SSE/x87 interpolation that
//               appends 10 Vector3s; partial, no source.
// @ 0x00d0d880  FUN_00d0d880 (PDB candidate cCommunityEditor::UpdateBuildingLinkEffect,
//               687 bytes) - SSE key-frame stepping + a 0xd0d6b0 call + virtual
//               pushes; partial, no source.
// @ 0x00d0db30  FUN_00d0db30 (649 bytes) - many virtual queries over the
//               community noun list with an early-out byte flag; partial, no
//               source.
// ---------------------------------------------------------------------------