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
    bool SampleU(uint32_t* out, int a, int b, int c, int d); // 0x0073bdf0 (raw dword sample)
};

// 0073c4b0 is a free helper: it takes the sampler object as its first stack argument and loads
// it into ECX for the __thiscall samplers (hence the plain `ret`/caller cleanup).
bool SkinCollect(ModelSet* self, int b, uint32_t* outKeys, float* outVals);

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
// @ 0x0073BDF0 — raw dword sample: same keyed lookup as SampleA but writes the masked dword.
bool ModelSet::SampleU(uint32_t* out, int a, int b, int c, int d)
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
                *out = *(uint32_t*)((char*)v->data + v->stride * b);
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
// @ 0x0073C4B0 — skinning collect: resolve an RGBA key and a packed index triple.
bool SkinCollect(ModelSet* self, int b, uint32_t* outKeys, float* outVals)
{
    outKeys[0] = 0;
    outKeys[1] = 0;
    outKeys[2] = 0;
    outKeys[3] = 0;
    outVals[0] = 0.0f;
    outVals[1] = 0.0f;
    outVals[2] = 0.0f;
    outVals[3] = 0.0f;

    float scale = 1.0f;
    uint32_t raw;
    float f0 = 0.0f, f1 = 0.0f, f2 = 0.0f, f3 = 0.0f;
    if (self->SampleU(&raw, 10, b, 10, -1)) {
        scale = 0.003921569f;                       // 1/255
        outVals[0] = (float)(int)(raw & 0xffu);
        outVals[1] = (float)(int)((raw >> 8) & 0xffu);
        outVals[2] = (float)(int)((raw >> 16) & 0xffu);
        outVals[3] = (float)(int)(raw >> 24);
        goto applyScale;
    }
    if (self->SampleA(&f0, 1, b, 10, -1)) {
        outVals[0] = f0;
        goto applyScale;
    }
    if (self->Sample2((int*)&f0, 2, b, 10, -1)) {
        outVals[0] = f0;
        outVals[1] = f1;
        goto applyScale;
    }
    if (self->Sample3((int*)&f0, 3, b, 10, -1)) {
        outVals[0] = f0;
        outVals[1] = f1;
        outVals[2] = f2;
        goto applyScale;
    }
    if (self->Sample4((int*)&f0, 4, b, 10, -1)) {
        outVals[0] = f0;
        outVals[1] = f1;
        outVals[2] = f2;
        outVals[3] = f3;
        goto applyScale;
    }
    outVals[0] = 1.0f;

applyScale:
    outVals[0] = outVals[0] * scale;
    outVals[1] = outVals[1] * scale;
    outVals[2] = outVals[2] * scale;
    outVals[3] = outVals[3] * scale;

    uint32_t k3 = 0, k2 = 0, k1 = 0;
    if (self->SampleU(&raw, 8, b, 9, -1)) {
        outKeys[0] = (int)(int16_t)(raw & 0xffffu);
        k1 = (int)(int16_t)((raw >> 16) & 0xffffu);
    } else if (self->Sample2((int*)&raw, 9, b, 9, -1)) {
        // raw holds {local_10 (lo/hi), local_c (lo/hi)} as four 16-bit fields.
        outKeys[0] = (int)(int16_t)(raw & 0xffffu);
        k1 = (int)(int16_t)((raw >> 16) & 0xffffu);
        k2 = (int)(int16_t)(*(uint32_t*)((char*)&raw + 4) & 0xffffu);
        k3 = (int)(int16_t)((*(uint32_t*)((char*)&raw + 4) >> 16) & 0xffffu);
    } else if (self->SampleU(&raw, 7, b, 9, -1)) {
        outKeys[0] = (int)(raw & 0xffu);
        k1 = (int)((raw >> 8) & 0xffu);
        k2 = (int)((raw >> 16) & 0xffu);
        k3 = (int)(raw >> 24);
    } else {
        return false;
    }
    outKeys[1] = k1;
    outKeys[2] = k2;
    outKeys[3] = k3;

    outKeys[0] = (int)outKeys[0] / 3;
    outKeys[1] = (int)outKeys[1] / 3;
    outKeys[2] = (int)outKeys[2] / 3;
    outKeys[3] = (int)outKeys[3] / 3;
    return true;
}
// A 3x3 transform plus scale/translation blob read by AnimCollect.
struct AnimXform {
    char  pad00[0x74];
    float tx;            // +0x74
    float ty;            // +0x78
    float tz;            // +0x7c
    float scale;         // +0x80
    float m00;           // +0x84
    float m01;           // +0x88
    float m02;           // +0x8c
    float m10;           // +0x90
    float m11;           // +0x94
    float m12;           // +0x98
    float m20;           // +0x9c
    float m21;           // +0xa0
    float m22;           // +0xa4
};

struct ModelAnim {
    void** vftable;              // +0
    int    pad04;
    int    pad08;
    AnimXform* pXform;           // +0xc
    char   pad10[0x98 - 0x10];
    int*   pBoneData;            // +0x98
    bool AnimCollect(float* out);   // 0x0073c780
    bool AbilityMethodE(float* out); // 0x0073cbc0
};

typedef bool (__thiscall* AnimVfn)(void*, float*);
void __cdecl ResetBone(int* p, int v);      // 0x0073A900
extern float g_162e898, g_162e89c, g_162e8a0;   // 0x0162e898 (weight fallback triple)

// @ 0x0073C780 — animation collect: apply the object's transform to three packed vectors.
bool ModelAnim::AnimCollect(float* out)
{
    AnimVfn fn = (AnimVfn)(*(void***)this)[3];   // vtable slot +0xc
    if (!fn(this, out))
        return false;

    AnimXform* xf = pXform;
    if (((unsigned char*)xf)[0x70] & 2) {
        float y = out[1], z = out[2], x = out[0];
        out[0] = (xf->m10 * y + xf->m20 * z) + xf->m00 * x;
        out[1] = (xf->m01 * x + xf->m11 * y) + xf->m21 * z;
        out[2] = (xf->m02 * x + xf->m12 * y) + xf->m22 * z;
    }
    {
        float s = xf->scale;
        float y = out[1], z = out[2];
        out[0] = s * out[0];
        out[1] = y * s;
        out[2] = s * z;
        float ty = xf->ty, tz = xf->tz;
        out[0] = xf->tx + out[0];
        out[1] = ty + y * s;
        out[2] = tz + s * z;
    }
    if (((unsigned char*)xf)[0x70] & 2) {
        float z = out[5], y = out[4], x = out[3];
        out[3] = (xf->m10 * y + xf->m20 * z) + xf->m00 * x;
        out[4] = (xf->m01 * x + xf->m11 * y) + xf->m21 * z;
        out[5] = (xf->m02 * x + xf->m12 * y) + xf->m22 * z;
    }
    {
        float s = xf->scale;
        float z = out[5];
        out[3] = out[3] * s;
        out[4] = s * out[4];
        out[5] = s * z;
        float tz = xf->tz, ty = xf->ty;
        out[3] = out[3] + xf->tx;
        out[4] = ty + out[4];
        out[5] = tz + s * z;
    }
    if (((unsigned char*)xf)[0x70] & 2) {
        float z = out[8], y = out[7], x = out[6];
        out[6] = (xf->m10 * y + xf->m20 * z) + xf->m00 * x;
        out[7] = (xf->m01 * x + xf->m11 * y) + xf->m21 * z;
        out[8] = (xf->m02 * x + xf->m12 * y) + xf->m22 * z;
    }
    {
        float s = xf->scale;
        float z = out[8];
        out[6] = out[6] * s;
        out[7] = s * out[7];
        out[8] = s * z;
        float tz = xf->tz, ty = xf->ty;
        out[6] = out[6] + xf->tx;
        out[7] = ty + out[7];
        out[8] = tz + s * z;
    }
    return true;
}
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
// @ 0x0073CBC0 — ability method: blend four bone matrices into three output vertices.
bool ModelAnim::AbilityMethodE(float* out)
{
    ResetBone(pBoneData, 0);
    out[0] = 0.0f; out[1] = 0.0f; out[2] = 0.0f;
    out[3] = 0.0f; out[4] = 0.0f; out[5] = 0.0f;
    out[6] = 0.0f; out[7] = 0.0f; out[8] = 0.0f;

    float* p = (float*)((char*)this + 0x1c);
    for (int v = 0; v < 3; ++v) {
        float* boneBase = (float*)**(int**)(*(int*)((char*)pBoneData + 8) + 8);
        float f1 = p[0], f2 = p[-2], f3 = p[-1];
        float a0 = g_162e898, a1 = g_162e89c, a2 = g_162e8a0;
        for (int i = 0; i < 4; ++i) {
            float* m = (float*)((char*)boneBase + *(int*)&p[1 + i] * 0x30);
            float w = p[5 + i];
            a0 += w * ((m[2] * f1 + m[1] * f3 + m[0] * f2) + m[3]);
            a1 += w * ((m[6] * f1 + m[5] * f3 + m[4] * f2) + m[7]);
            a2 += w * ((m[10] * f1 + m[9] * f3 + m[8] * f2) + m[11]);
        }
        out[0] = a0;
        out[1] = a1;
        out[2] = a2;
        p += 0xb;
        out += 3;
    }
    return true;
}
