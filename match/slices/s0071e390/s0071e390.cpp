// Slice s0071e390: SP mesh / primitive helpers (fills, index collectors, face-cluster
// vector resize).  Optimized module: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast.
#include "types.h"

// external specialisations (bodies in other slices)
void DoInsertValuesInt(int* end, unsigned n, const int* value);   // 0x0071e870
void EraseIntRange(int* first, int* last);                        // 0x004ce270
void DoInsertValueInt(int* end, const int* value);                // 0x004558a0

struct VecInt {
    int* mpBegin; int* mpEnd; int* mpCapacity; unsigned mAlloc[1];
    void resize(unsigned n);
};

struct Vec20B {                     // 0x20-byte entry
    unsigned mA, mB, mC, mKey;
    unsigned mVal, mD, mE, mF;
};
struct Container20 {
    char pad_00[8];
    char* mpBegin;                  // +0x08
    char* mpEnd;                    // +0x0c
};

// @ 0x0071e5e0
void FillInt(int* first, int* last, const int* value)
{
    for (; first != last; ++first)
        *first = *value;
}

// @ 0x0071e7a0
void FillNInt(int* first, unsigned n, const int* value)
{
    if (n != 0) {
        do {
            if (first)
                *first = *value;
            ++first;
        } while (--n);
    }
}

// @ 0x0071ef50
void VecInt::resize(unsigned n)
{
    if ((unsigned)(mpEnd - mpBegin) < n) {
        int v = 0;
        DoInsertValuesInt(mpEnd, n - (unsigned)(mpEnd - mpBegin), &v);
    } else {
        EraseIntRange(mpBegin + n, mpEnd);
    }
}

// @ 0x0071ecc0
void Container20_collect(const Container20* c, VecInt* out, int key)
{
    int n = (int)((c->mpEnd - c->mpBegin) >> 5);
    for (int i = 0; i < n; ++i) {
        if (*(int*)(c->mpBegin + i * 0x20 + 0xc) == key)
            DoInsertValueInt(out->mpEnd, &i);
    }
}

// ---------------------------------------------------------------------------
// Remaining functions: skeletons (partial).
// ---------------------------------------------------------------------------
// @ 0x0071e390
void SP_WriteMesh(void* a, void* b) { (void)a; (void)b; }
// @ 0x0071e600
void Obj14_e600(void* self, void* a, void* b, void* c) { (void)self; (void)a; (void)b; (void)c; }
// @ 0x0071e7d0
void Obj14_e7d0(void* self, unsigned n, const void* v) { (void)self; (void)n; (void)v; }
// @ 0x0071e870
void Obj14_e870(void* a, unsigned n, void* b) { (void)a; (void)n; (void)b; }
// @ 0x0071ea40
void Obj14_ea40(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }
// @ 0x0071ec20
void Obj14_ec20(void* a, void* b) { (void)a; (void)b; }
// @ 0x0071ed30
void Obj14_ed30(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }
// @ 0x0071ee10
void SP_FindPrimitives(void* a, void* b) { (void)a; (void)b; }
// @ 0x0071efa0
void FaceClusterVec_resize(void* self, unsigned n) { (void)self; (void)n; }
// @ 0x0071f040
void Obj14_f040(void* a, void* b) { (void)a; (void)b; }
// @ 0x0071f0f0
void Obj14_f0f0(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }
// @ 0x0071f300
void Obj14_f300(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }
