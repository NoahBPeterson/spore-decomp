// Slice s00d311b0 -- SporeApp.exe: an effect/state-update driver for an audio
// emitter object (0x00d311b0), a game-mode/kind predicate (0x00d317e0) and the
// two heap-sift helpers (0x00d31840 sift-down, 0x00d31980 pop) that a priority
// queue of ref-counted sound-effect objects is built on.
//
// Frozen batch gold6.  32-bit x86, MSVC 2008 SP1, flags /O2 /MD /Gy /TP /arch:SSE /GS-.

#include "types.h"

// Declare N throwaway virtuals so a named slot lands at the right vtable index.
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV1 PV
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// ---------------------------------------------------------------------------
// external callees
// ---------------------------------------------------------------------------
extern "C" void* SP_GetCurrentGameMode(void);               // 0x00b5b800
extern "C" int   FUN_00d30830(void* p);                     // 0x00d30830

// ---------------------------------------------------------------------------
// Heap element.  Only the two refcount slots are named; the remaining vtable
// entries are padding virtuals so AddRef lands at +0xbc and Release at +0xc0.
// ---------------------------------------------------------------------------
struct HeapObj {
    PV8 PV8 PV8 PV8 PV8 PV4 PV2 PV1
    virtual void AddRef();                                 // vtable +0xbc
    virtual void Release();                                // vtable +0xc0
};

// Ref-counted pointer: the heap stores these by value and every element
// assignment is AddRef(new)/Release(old) with the identity check inlined.
struct Ref {
    HeapObj* p;                                            // +0x00
    Ref() : p(0) {}
    Ref(const Ref& o) { p = o.p; if (p) p->AddRef(); }
    Ref& operator=(const Ref& o)
    {
        HeapObj* old = p;
        HeapObj* nw  = o.p;
        if (nw != old) {
            if (nw) nw->AddRef();
            p = nw;
            if (old) old->Release();
        }
        return *this;
    }
    ~Ref() { if (p) p->Release(); }
    operator HeapObj*() const { return p; }                 // read as a raw ptr
};

// Ordering functor: keeps the element closest to the three-float position at
// the top of the heap.
struct Cmp {
    float px;                                              // +0x00
    float py;                                              // +0x04
    float pz;                                              // +0x08
    bool operator()(HeapObj* a, HeapObj* b) const;         // 0x00d2f3c0
};

// The payload handed to a pop (seven priority floats).
struct Prior {
    float mF[7];
};

// The value carried with a sift (the element payload plus the ordering point).
// The copy constructor must copy the float block before the ref-counted member,
// which is what the original compiler emits.
struct Value {
    Ref   mRef;                                            // +0x00
    Cmp   mCmp;                                            // +0x04
    float mF[4];                                           // +0x10
    Value() {}
    Value(const Prior& src, HeapObj* owner)
    {
        mCmp.px = src.mF[0];
        mCmp.py = src.mF[1];
        mCmp.pz = src.mF[2];
        mF[0] = src.mF[3];
        mF[1] = src.mF[4];
        mF[2] = src.mF[5];
        mF[3] = src.mF[6];
        mRef.p = owner;
        if (mRef.p) mRef.p->AddRef();
    }
    Value(const Value& o)
    {
        mCmp.px = o.mCmp.px;
        mCmp.py = o.mCmp.py;
        mCmp.pz = o.mCmp.pz;
        mF[0] = o.mF[0];
        mF[1] = o.mF[1];
        mF[2] = o.mF[2];
        mF[3] = o.mF[3];
        mRef.p = o.mRef.p;
        if (mRef.p) mRef.p->AddRef();
    }
};

extern "C" void FUN_00d2f880(Ref* first, int top, int hole, Value val);  // 0x00d2f880

// ===========================================================================
// @ 0x00d317e0  FUN_00d317e0
// ===========================================================================
bool FUN_00d317e0(int param_1)
{
    if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
        return false;
    }
    switch (FUN_00d30830((void*)param_1)) {
    case 3:
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
        return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00d31840  FUN_00d31840  (sift-down: std::_Adjust_heap of a Ref heap)
// ===========================================================================
void FUN_00d31840(Ref* first, int top, int len, int hole, Value val)
{
    int idx;
    for (; (idx = 2 * hole + 2) < len; hole = idx) {
        if (val.mCmp(first[idx], first[idx - 1])) {
            --idx;
        }
        first[hole] = first[idx];
    }
    if (len == idx) {
        first[hole] = first[idx - 1];
        hole = idx - 1;
    }
    FUN_00d2f880(first, top, hole, val);
}

// ===========================================================================
// @ 0x00d31980  FUN_00d31980  (pop: std::_Pop_heap of a Ref heap)
// ===========================================================================
void FUN_00d31980(Ref* first, Ref* last, Prior val)
{
    Ref tmp(*(last - 1));

    *(last - 1) = *first;

    FUN_00d31840(first, 0, (int)(last - first) - 1, 0, Value(val, tmp.p));
}