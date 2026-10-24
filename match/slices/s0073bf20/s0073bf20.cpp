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
// Model/render channel tables shared by the four ModelPass* samplers
// (0073bf20 / 0073c040 / 0073c170 / 0073c290).
//   this  : ModelSet (+8 slot index, +0x10 base offset, +0x14 entry count); *this : Doc.
//   A Doc holds the 0x20-byte element array (+8) and the 0x8c-byte record array (+0x1c).
// ---------------------------------------------------------------------------
struct Chan {                       // channel value descriptor (0x0c)
    int      pad00;                 // +0x00
    int*     data;                  // +0x04
    uint16_t idx;                   // +0x08   mask-table index
    uint16_t stride;                // +0x0a
};
struct Element {                    // 0x20-byte keyed element
    int  k0;                        // +0x00
    int  k1;                        // +0x04
    int  k2;                        // +0x08
    int  pad0c;                     // +0x0c
    Chan val;                       // +0x10
    int  pad1c;                     // +0x1c
};
struct Rec {                        // 0x8c-byte record
    Chan     head;                  // +0x00
    int      pad0c;                 // +0x0c
    int      pad10;                 // +0x10
    int16_t* list;                  // +0x14
    int16_t* listEnd;               // +0x18
    char     pad1c[0x44 - 0x1c];    // +0x1c
    int*     frames;                // +0x44
    int*     framesEnd;             // +0x48
    char     pad4c[0x8c - 0x4c];    // +0x4c
};
struct Doc {
    char     pad0[0x08];
    Element* elems;                 // +0x08
    char     pad0c[0x1c - 0x0c];
    Rec*     recs;                  // +0x1c
};
extern unsigned g_0140d5ac[];       // 0x0140d5ac channel mask table

struct ModelSet {
    Doc* pDoc;                      // +0x00
    int  pad04;                     // +0x04
    int  idx;                       // +0x08
    int  pad0c;                     // +0x0c
    int  base;                      // +0x10
    int  count;                     // +0x14
    bool SampleA(float* out, int a, int b, int c, int d);   // 0x0073bf20
    bool Sample4(int*   out, int a, int b, int c, int d);   // 0x0073c040
    bool Sample2(int*   out, int a, int b, int c, int d);   // 0x0073c170
    bool Sample3(int*   out, int a, int b, int c, int d);   // 0x0073c290
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
// @ 0x0073BF20 — model update pass (277 bytes): sample channel (a,b,c,d) into *out as float.
bool ModelSet::SampleA(float* out, int a, int b, int c, int d)
{
    if (b < 0 || count <= b)
        return 0;
    b = b + base;
    Rec* rec = (Rec*)((char*)pDoc->recs + idx * 0x8c);
    int n = (int)(((char*)rec->listEnd - (char*)rec->list) >> 2);
    if (0 < n) {
        Element* elems = pDoc->elems;
        int16_t* p = rec->list;
        int i = 0;
        do {
            Element* e = (Element*)((char*)elems + (*p) * 0x20);
            if ((c == 0 || e->k0 == c) && (d == -1 || e->k1 == d) && e->k2 == a) {
                Chan* v = &e->val;
                if (rec->head.data != 0)
                    b = *(unsigned*)((char*)rec->head.data + rec->head.stride * b) & g_0140d5ac[rec->head.idx];
                if (rec->frames != rec->framesEnd) {
                    Rec* f = (Rec*)((char*)rec->frames + p[1] * 0x10);
                    if (f->head.data != 0)
                        b = *(unsigned*)((char*)f->head.data + f->head.stride * b) & g_0140d5ac[f->head.idx];
                }
                *out = *(float*)((char*)v->data + v->stride * b);
                return 1;
            }
            ++i;
            p += 2;
        } while (i < n);
    }
    return 0;
}
// @ 0x0073C040 — model update pass (294 bytes): copy channel (a,b,c,d) as four dwords.
bool ModelSet::Sample4(int* out, int a, int b, int c, int d)
{
    if (b < 0 || count <= b)
        return 0;
    b = b + base;
    Rec* rec = (Rec*)((char*)pDoc->recs + idx * 0x8c);
    int n = (int)(((char*)rec->listEnd - (char*)rec->list) >> 2);
    if (0 < n) {
        Element* elems = pDoc->elems;
        int16_t* p = rec->list;
        int i = 0;
        do {
            Element* e = (Element*)((char*)elems + (*p) * 0x20);
            if ((c == 0 || e->k0 == c) && (d == -1 || e->k1 == d) && e->k2 == a) {
                Chan* v = &e->val;
                if (rec->head.data != 0)
                    b = *(unsigned*)((char*)rec->head.data + rec->head.stride * b) & g_0140d5ac[rec->head.idx];
                if (rec->frames != rec->framesEnd) {
                    Rec* f = (Rec*)((char*)rec->frames + p[1] * 0x10);
                    if (f->head.data != 0)
                        b = *(unsigned*)((char*)f->head.data + f->head.stride * b) & g_0140d5ac[f->head.idx];
                }
                int* w = (int*)((char*)v->data + v->stride * b);
                out[0] = w[0];
                out[1] = w[1];
                out[2] = w[2];
                out[3] = w[3];
                return 1;
            }
            ++i;
            p += 2;
        } while (i < n);
    }
    return 0;
}
// @ 0x0073C170 — model update pass (284 bytes): copy channel (a,b,c,d) as two dwords.
bool ModelSet::Sample2(int* out, int a, int b, int c, int d)
{
    if (b < 0 || count <= b)
        return 0;
    b = b + base;
    Rec* rec = (Rec*)((char*)pDoc->recs + idx * 0x8c);
    int n = (int)(((char*)rec->listEnd - (char*)rec->list) >> 2);
    if (0 < n) {
        Element* elems = pDoc->elems;
        int16_t* p = rec->list;
        int i = 0;
        do {
            Element* e = (Element*)((char*)elems + (*p) * 0x20);
            if ((c == 0 || e->k0 == c) && (d == -1 || e->k1 == d) && e->k2 == a) {
                Chan* v = &e->val;
                if (rec->head.data != 0)
                    b = *(unsigned*)((char*)rec->head.data + rec->head.stride * b) & g_0140d5ac[rec->head.idx];
                if (rec->frames != rec->framesEnd) {
                    Rec* f = (Rec*)((char*)rec->frames + p[1] * 0x10);
                    if (f->head.data != 0)
                        b = *(unsigned*)((char*)f->head.data + f->head.stride * b) & g_0140d5ac[f->head.idx];
                }
                int* w = (int*)((char*)v->data + v->stride * b);
                out[0] = w[0];
                out[1] = w[1];
                return 1;
            }
            ++i;
            p += 2;
        } while (i < n);
    }
    return 0;
}
// @ 0x0073C290 — model update pass (288 bytes): copy channel (a,b,c,d) as three dwords.
bool ModelSet::Sample3(int* out, int a, int b, int c, int d)
{
    if (b < 0 || count <= b)
        return 0;
    b = b + base;
    Rec* rec = (Rec*)((char*)pDoc->recs + idx * 0x8c);
    int n = (int)(((char*)rec->listEnd - (char*)rec->list) >> 2);
    if (0 < n) {
        Element* elems = pDoc->elems;
        int16_t* p = rec->list;
        int i = 0;
        do {
            Element* e = (Element*)((char*)elems + (*p) * 0x20);
            if ((c == 0 || e->k0 == c) && (d == -1 || e->k1 == d) && e->k2 == a) {
                Chan* v = &e->val;
                if (rec->head.data != 0)
                    b = *(unsigned*)((char*)rec->head.data + rec->head.stride * b) & g_0140d5ac[rec->head.idx];
                if (rec->frames != rec->framesEnd) {
                    Rec* f = (Rec*)((char*)rec->frames + p[1] * 0x10);
                    if (f->head.data != 0)
                        b = *(unsigned*)((char*)f->head.data + f->head.stride * b) & g_0140d5ac[f->head.idx];
                }
                int* w = (int*)((char*)v->data + v->stride * b);
                out[0] = w[0];
                out[1] = w[1];
                out[2] = w[2];
                return 1;
            }
            ++i;
            p += 2;
        } while (i < n);
    }
    return 0;
}
// @ 0x0073C4B0 — large skinning/collect pass (674 bytes)
void SkinCollect() {}
// @ 0x0073C780 — large animation/collect pass (822 bytes)
void AnimCollect() {}
// Simulator ability ctors: multiple-inheritance chain (GmeRefCount sub-object at +4, refcount at
// +8; ability base holds a counted ref at +0xc).
struct AbilityP0 { virtual void p0(); };
struct AbilityGmeRC { virtual void g0(); int rc; AbilityGmeRC() : rc(0) {} };
struct AbilityBase : AbilityP0, AbilityGmeRC {
    RefObjV* m; int x;
    AbilityBase(RefObjV* a, int b) : m(a) { if (a) ++a->mnRefCount; x = b; }
    virtual void p0(); virtual void g0();
};
struct AbilityD : AbilityBase {
    int pad[(0x98 - 0x14) / 4];
    int y;
    AbilityD(RefObjV* a, int b, int c);
    virtual void p0(); virtual void g0();
};
struct AbilityC : AbilityBase {
    AbilityC(RefObjV* a, int b);
    virtual void p0(); virtual void g0();
};
// @ 0x0073CAC0 — Simulator ability constructor (66 bytes): same chain as AbilityD, two arguments.
AbilityC::AbilityC(RefObjV* a, int b) : AbilityBase(a, b) {}
// @ 0x0073CB40
AbilityD::AbilityD(RefObjV* a, int b, int c) : AbilityBase(a, b), y(c) {}
// @ 0x0073CBC0 — large ability method (515 bytes)
void AbilityMethodE() {}
