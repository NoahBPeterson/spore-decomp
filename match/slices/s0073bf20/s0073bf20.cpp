// Slice s0073bf20 — model/mesh container helpers and Simulator ability ctors.
//
// Optimized /O2 (no frame pointer).  Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast.

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef short int16_t;

#include <intrin.h>

// Refcounted object: vtable at +0, refcount at +4 (manual vftable keeps the exact layout).
struct RefObjV {
    void** vftable;                 // +0
    int mnRefCount;                 // +4
};

// ---------------------------------------------------------------------------
// @ 0x0073C410 — copy a range of 8-byte {int, RefObj*} pairs, AddRef'ing the object.
// ---------------------------------------------------------------------------
struct PairPtr {
    int a;                          // +0
    RefObjV* b;                     // +4
};

void CopyPairs(PairPtr* first, PairPtr* last, PairPtr* dst)
{
    while (first != last) {
        if (dst != 0) {
            dst->a = first->a;
            RefObjV* p = first->b;
            dst->b = p;
            if (p != 0)
                _InterlockedIncrement((volatile long*)&p->mnRefCount);
        }
        ++first;
        ++dst;
    }
}

// ---------------------------------------------------------------------------
// @ 0x0073C450 — release a range of 8-byte {int, RefObj*} pairs (atomic), return dst.
// ---------------------------------------------------------------------------
PairPtr* ReleasePairs(PairPtr* first, PairPtr* last, PairPtr* dst)
{
    if (first != last) {
        do {
            RefObjV* p = first->b;
            if (p != 0) {
                volatile long* r = (volatile long*)&p->mnRefCount;
                long n = _InterlockedDecrement(r);
                if (n == 0) {
                    _InterlockedExchange(r, 1);
                    if (p != 0)
                        ((void(__thiscall*)(RefObjV*, int))p->vftable[0])(p, 1);
                }
            }
            first = (PairPtr*)((char*)first + 8);
            dst = (PairPtr*)((char*)dst + 8);
        } while (first != last);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// @ 0x0073C3B0 — destroy a range of 0xc4-byte elements, releasing the ref at +0xc.
// ---------------------------------------------------------------------------
struct BigElem {
    char pad0[0xc];
    RefObjV* p;                     // +0xc
    char pad10[0xc4 - 0x10];
};

BigElem* DestroyElems(BigElem* first, BigElem* last, BigElem* dst)
{
    while (first != last) {
        RefObjV* p = first->p;
        if (p != 0) {
            int n = (*(volatile int*)&p->mnRefCount += -1);
            if (n == 0) {
                (*(volatile int*)&p->mnRefCount) = 1;
                _ReadWriteBarrier();
                ((void(__thiscall*)(RefObjV*, int))p->vftable[0])(p, 1);
            }
        }
        first = (BigElem*)((char*)first + 0xc4);
        dst = (BigElem*)((char*)dst + 0xc4);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// Remaining slice functions (large drivers / Simulator ability ctors).
// ---------------------------------------------------------------------------
// @ 0x0073BF20 — model update pass (277 bytes)
void ModelPassA() {}
// @ 0x0073C040 — model update pass (294 bytes)
void ModelPassB() {}
// @ 0x0073C170 — model update pass (284 bytes)
void ModelPassC() {}
// @ 0x0073C290 — model update pass (288 bytes)
void ModelPassD() {}
// @ 0x0073C4B0 — large skinning/collect pass (674 bytes)
void SkinCollect() {}
// @ 0x0073C780 — large animation/collect pass (822 bytes)
void AnimCollect() {}
// @ 0x0073CAC0 — Simulator ability constructor (66 bytes)
void AbilityCtorC() {}
// @ 0x0073CB40 — Simulator ability constructor (76 bytes)
void AbilityCtorD() {}
// @ 0x0073CBC0 — large ability method (515 bytes)
void AbilityMethodE() {}
