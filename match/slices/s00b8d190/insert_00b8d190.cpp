// Slice s00b8d190 -- find-or-insert on the 0x1c-byte-element eastl vector at +0xd4:
// the key is an ordered (uint32, uint32) pair, and whichever element ends up holding
// the key gets the 0x14-byte vec3-vector value copied onto its +8 member.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

void* FUN_00f473a0(unsigned int, const char*, int, int, const char*, int);  // 0x00f473a0 operator new[]
void  FUN_00f47380(void*);                                                  // 0x00f47380 operator delete[]

struct Vec3 { float x, y, z; };   // 0x0c

// ---------------------------------------------------------------------------
// eastl::sp_vector<cSPVector3> -- 0x14 bytes: 3 pointers + a 2-int allocator.
// ---------------------------------------------------------------------------
class Vec3Vec {
 public:
    Vec3* mpBegin;        // +0x00
    Vec3* mpEnd;          // +0x04
    Vec3* mpCapacity;     // +0x08
    int   mAllocator[2];  // +0x0c

    Vec3Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    Vec3Vec& operator=(const Vec3Vec&) throw();   // 0x00473500
    void Free() {
        if (mpBegin && ((int32_t*)mpBegin)[-1] != 0)
            FUN_00f47380(mpBegin);
    }
};

// ---------------------------------------------------------------------------
// 0x1c-byte vector element: the (mA, mB) key followed by the vec3 vector.
// ---------------------------------------------------------------------------
struct Elem1c {
    uint32_t mA;      // +0x00
    uint32_t mB;      // +0x04
    Vec3Vec  mVec;    // +0x08
};

class Vec1c {
 public:
    Elem1c* mpBegin;     // +0x00
    Elem1c* mpEnd;       // +0x04
    Elem1c* mpCapacity;  // +0x08

    void DoInsertValue28(Elem1c*, const Elem1c&);  // 0x00b89830

    // Trivial accessors: spelling the container through these (instead of the raw
    // members) is what picks the original's register assignment.
    int32_t Count() const { return (int32_t)(mpEnd - mpBegin); }
    Elem1c& At(int32_t i) { return mpBegin[i]; }
    Elem1c* End() const { return mpEnd; }
    void SetEnd(Elem1c* p) { mpEnd = p; }
    Elem1c* Capacity() const { return mpCapacity; }
    Elem1c& Back() { return mpEnd[-1]; }
};

// ---------------------------------------------------------------------------
// Owner: the element vector sits at +0xd4, the "changed" flag at +0xea.
// ---------------------------------------------------------------------------
class cMap_s00b8d190 {
 public:
    char   _pad00[0xd4];
    Vec1c  mElems;     // +0xd4
    char   _pad0e[0x0a];
    bool   mChanged;   // +0xea

    void FUN_00b8d190(uint32_t a, uint32_t b, const Vec3Vec& v);
};

// ---------------------------------------------------------------------------
// @ 0x00b8d190  find the element keyed by the ordered pair (min(a, b), max(a, b));
// append a default element when the key is absent, then assign the value.
// ---------------------------------------------------------------------------
void cMap_s00b8d190::FUN_00b8d190(uint32_t a, uint32_t b, const Vec3Vec& v)
{
    // The key is an unordered pair: order it in place (the parameters double as
    // the two key slots the search below reads).
    if (b < a) {
        uint32_t const t = a;
        a = b;
        b = t;
    }

    // The index is live before the count: the original orders the two locals this
    // way, which is what gives the loop its ebp/esi/edi/edx register assignment.
    int32_t i = 0;
    int32_t const n = mElems.Count();
    for (; i < n; ++i) {
        if (mElems.At(i).mA == a && mElems.At(i).mB == b) {
            mElems.At(i).mVec = v;
            mChanged = true;
            return;
        }
    }

    // Re-binding the container here keeps its address in the register the count
    // already computed, so the append below addresses the members off that base
    // (a disp8) instead of re-deriving them from the object pointer (a disp32).
    Vec1c& elems = mElems;
    Elem1c* e = elems.End();
    if (e < elems.Capacity()) {
        elems.SetEnd(e + 1);
        if (e) {
            e->mVec.mpBegin = 0;
            e->mVec.mpEnd = 0;
            e->mVec.mpCapacity = 0;
        }
    } else {
        Elem1c value;
        elems.DoInsertValue28(e, value);
        value.mVec.Free();
    }

    mElems.Back().mA = a;
    mElems.Back().mB = b;
    mElems.Back().mVec = v;
    mChanged = true;
}
