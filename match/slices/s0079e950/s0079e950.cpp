// slice s0079e950 - mesh triangle clipping against a sphere, plus 8-byte
// (intrusive_ptr, int) vector helpers.  /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <intrin.h>

typedef unsigned int uint;
typedef unsigned short ushort;

extern "C" void* operator_new(uint size, const char* tag, int a, int b, const char* file, int line);
extern "C" void operator_delete__(void* p);
static const char kAllocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// ---------------------------------------------------------------- vector<ushort>
struct UShortVec {
    ushort* mpBegin; ushort* mpEnd; ushort* mpCap;
    void DoInsert(ushort* pos, const ushort* val);      // 0x6f5bc0
    void PushBackOOL(const ushort* val);                // 0x6f66a0 (cVecU16::push_back)
    void push_back(ushort v) {
        ushort tmp = v;
        if (mpEnd < mpCap) {
            ushort* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsert(mpEnd, &tmp);
        }
    }
};

// ---------------------------------------------------------------- mesh streams
extern const uint g_formatMask[];                       // 0x140f544

struct Stream {                                         // vertex / index stream view
    uint  pad0;
    char* data;                                         // +4
    ushort fmt;                                         // +8
    ushort stride;                                      // +0xa
    uint  Read(uint i) const { return *(uint*)(data + stride * i) & g_formatMask[fmt]; }
    ushort ReadU16(uint i) const { return (ushort)(*(ushort*)(data + stride * i) & (ushort)g_formatMask[fmt]); }
};
struct IndexStream : Stream {                           // 0x8c bytes
    char pad1[0x14 - 0xc];
    char* table;                                        // +0x14: 4-byte entries, short at +2
    char pad2[0x44 - 0x18];
    Stream* remapBegin;                                 // +0x44 (0x10-byte records)
    Stream* remapEnd;                                   // +0x48
};
struct Mesh {
    char pad0[8];
    char* streams;                                      // +8: 0x20-byte stream descriptors, view at +0x10
    char pad1[0x1c - 0xc];
    char* indexStreams;                                 // +0x1c
};

extern "C" int FUN_0071ddc0(Mesh* m, int a, int b, int c, int d);   // find vertex stream (position)

struct Out {                                            // clip output builder
    char pad0[4];
    int  f4, f8;                                        // +4 / +8 : 16-byte records begin / end
    char pad1[0x18 - 0xc];
    char* vecs;                                         // +0x18: 0x14-byte ushort vectors
    char pad2[0x30 - 0x1c];
    int  cur;                                           // +0x30
    void AddVert(void* src, int idx);                   // 0x79b4b0
    void AddLerp(void* src, int i, int j, float t);     // 0x79b520
    void AddTri(int idx);                               // 0x79b590
    UShortVec* IdxVec() { return (UShortVec*)(vecs + cur * 0x14); }
};
struct Job {
    char pad0[4];
    void* src;                                          // +4
    int  start;                                         // +8
    int  end;                                           // +0xc
};

struct Vec3C {
    float x, y, z;
    float Intersect(const float* a, const float* b);    // 0x799b50 (x87 return)
};
struct Slicer {
    char pad0[8];
    int   mode;                                         // +8
    Vec3C center;                                       // +0xc
    float radiusSq;                                     // +0x18
    void Run(Mesh* mesh, Job* job, UShortVec* vecAllOut, UShortVec* vecAllIn, Out* out6, Out* out7);
};

static inline float distSq(const float* p, const Vec3C& c)
{
    float dy = p[1] - c.y;
    float dx = p[0] - c.x;
    float dz = p[2] - c.z;
    return (dy * dy + dx * dx) + dz * dz;
}

// @ 0x0079e950
void Slicer::Run(Mesh* mesh, Job* job, UShortVec* vecAllOut, UShortVec* vecAllIn, Out* out6, Out* out7)
{
    int sidx = FUN_0071ddc0(mesh, 1, 0, 3, 0xe);
    IndexStream* ib = (IndexStream*)(mesh->indexStreams + *(int*)((char*)job + 4) * 0x8c);
    Stream* vs = (Stream*)(mesh->streams + sidx * 0x20 + 0x10);

    for (int a = job->start; a < job->end; a += 3) {
        int b = a + 1;
        int c = a + 2;
        uint ia, ib_, ic;
        if (ib->remapBegin == ib->remapEnd) {
            ia = ib->Read(a);
            ib_ = ib->Read(b);
            ic = ib->Read(c);
        } else {
            Stream* rm = (Stream*)((char*)ib->remapBegin + *(short*)(ib->table + sidx * 4 + 2) * 0x10);
            ia = rm->Read(ib->Read(a));
            ib_ = rm->Read(ib->Read(b));
            ic = rm->Read(ib->Read(c));
        }
        const float* pA = (const float*)(vs->data + vs->stride * ia);
        const float* pB = (const float*)(vs->data + vs->stride * ib_);
        const float* pC = (const float*)(vs->data + vs->stride * ic);
        int fA = distSq(pA, center) > radiusSq ? 1 : 0;
        int fB = distSq(pB, center) > radiusSq ? 1 : 0;
        int fC = distSq(pC, center) > radiusSq ? 1 : 0;
        int sum = fC + fB + fA;

        if (sum == (sum / 3) * 3) {
            // all inside (0) or all outside (3): copy the triangle's indices
            UShortVec* v = (fA == sum % 3) ? vecAllIn : vecAllOut;
            v->push_back(ib->ReadU16(a));
            v->push_back(ib->ReadU16(b));
            v->push_back(ib->ReadU16(c));
        } else {
            switch (mode) {
            case 0:
                vecAllOut->push_back(ib->ReadU16(a));
                vecAllOut->push_back(ib->ReadU16(b));
                vecAllOut->push_back(ib->ReadU16(c));
                break;
            case 1:
                vecAllIn->push_back(ib->ReadU16(a));
                vecAllIn->push_back(ib->ReadU16(b));
                vecAllIn->push_back(ib->ReadU16(c));
                break;
            case 2: {
                ushort va = ib->ReadU16(a);
                UShortVec* v;
                if (sum > 1) {
                    vecAllOut->PushBackOOL(&va);
                    v = vecAllOut;
                } else {
                    vecAllIn->PushBackOOL(&va);
                    v = vecAllIn;
                }
                ushort vb = ib->ReadU16(b);
                v->PushBackOOL(&vb);
                ushort vc = ib->ReadU16(c);
                v->PushBackOOL(&vc);
                break;
            }
            case 3: {
                uint n6 = (uint)(out6->f8 - out6->f4) >> 4;
                uint n7 = (uint)(out7->f8 - out7->f4) >> 4;
                void* src = job->src;
                Out* tail7 = out7;
                if (fA == 0) {
                    out7->AddVert(src, a);
                    if (fB == 0) {
                        float p = center.Intersect(pC, pA);
                        float q = center.Intersect(pC, pB);
                        out6->AddLerp(src, c, a, p);
                        out6->AddLerp(src, c, b, q);
                        out6->AddVert(src, c);
                        out7->AddVert(src, b);
                        out7->AddLerp(src, b, c, 1.0f - q);
                        out7->AddLerp(src, a, c, 1.0f - p);
                    } else {
                        float u = center.Intersect(pB, pA);
                        out6->AddLerp(src, b, a, u);
                        out6->AddVert(src, b);
                        out7->AddLerp(src, a, b, 1.0f - u);
                        if (fC == 0) {
                            float z = center.Intersect(pB, pC);
                            out6->AddLerp(src, b, c, z);
                            out7->AddLerp(src, c, b, 1.0f - z);
                            out7->AddVert(src, c);
                        } else {
                            float w = center.Intersect(pC, pA);
                            out6->AddVert(src, c);
                            out6->AddLerp(src, c, a, w);
                            out7->AddLerp(src, a, c, 1.0f - w);
                        }
                    }
                } else {
                    out6->AddVert(src, a);
                    if (fB == 0) {
                        float t = center.Intersect(pA, pB);
                        out6->AddLerp(src, a, b, t);
                        out7->AddLerp(src, b, a, 1.0f - t);
                        out7->AddVert(src, b);
                        if (fC == 0) {
                            float tt = center.Intersect(pA, pC);
                            out6->AddLerp(src, a, c, tt);
                            out7->AddVert(src, c);
                            out7->AddLerp(src, c, a, 1.0f - tt);
                        } else {
                            float tt = center.Intersect(pC, pB);
                            out6->AddLerp(src, c, b, tt);
                            out6->AddVert(src, c);
                            out7->AddLerp(src, b, c, 1.0f - tt);
                        }
                    } else {
                        float t1 = center.Intersect(pB, pC);
                        float t2 = center.Intersect(pA, pC);
                        out6->AddVert(src, b);
                        out6->AddLerp(src, b, c, t1);
                        out6->AddLerp(src, a, c, t2);
                        out7->AddLerp(src, c, a, 1.0f - t2);
                        out7->AddLerp(src, c, b, 1.0f - t1);
                        out7->AddVert(src, c);
                    }
                }
                (void)tail7;
                UShortVec* i6 = out6->IdxVec();
                i6->push_back((ushort)n6);
                i6 = out6->IdxVec();
                i6->push_back((ushort)(n6 + 1));
                i6 = out6->IdxVec();
                i6->push_back((ushort)(n6 + 2));
                UShortVec* i7 = out7->IdxVec();
                i7->push_back((ushort)n7);
                i7 = out7->IdxVec();
                i7->push_back((ushort)(n7 + 1));
                i7 = out7->IdxVec();
                i7->push_back((ushort)(n7 + 2));
                Out* t = out7;
                uint base = n7;
                if (sum > 1) {
                    base = n6;
                    t = out6;
                }
                t->AddTri(base);
                t->AddTri(base + 2);
                t->AddTri(base + 3);
                break;
            }
            }
        }
    }
}

// ---------------------------------------------------------------- vector<RefElem>
struct RefCounted { int vtbl; int refCount; };
struct RefElem {                                        // 8 bytes
    RefCounted* p;
    int x;
    void CopyFrom(const RefElem& o) {                   // copy-construct with addref
        p = o.p;
        if (p)
            _InterlockedExchangeAdd((long*)&p->refCount, 1);
        x = o.x;
    }
    RefElem& Assign(const RefElem& o);                  // 0x8dee30
};
struct RefVec {
    RefElem* mpBegin; RefElem* mpEnd; RefElem* mpCap;
    void DoInsertValue(RefElem* pos, const RefElem& val);   // 0x79f4e0
    RefVec& Assign(const RefVec& rhs);                      // 0x79f640
    void ReleaseAndClear();                                 // 0x79f7b0 (free function form below)
    RefElem* DoAllocateCopy(uint n, RefElem* first, RefElem* last);   // 0x799d60
    void DestroyRange(RefElem* first, RefElem* last);       // 0x8dede0
};
extern "C" RefElem* FUN_007992e0(RefElem* a, RefElem* b, RefElem* dst);   // uninitialized_copy
extern "C" void FUN_008def80(RefElem* a, RefElem* b, RefElem* dst);        // destroy/relocate helper
extern "C" void FUN_00799e00(RefElem* first, RefElem* last, RefElem* dstEnd);  // copy_backward
extern "C" RefElem* FUN_008defe0(RefElem* first, RefElem* last, RefElem* dst); // copy
extern "C" void FUN_00799290(RefElem** out, RefElem* a, RefElem* b, RefElem* c, const RefVec* hint);
void FUN_00762d70(int n, void** items);

// @ 0x0079f4e0
void RefVec::DoInsertValue(RefElem* pos, const RefElem& val)
{
    if (mpEnd != mpCap) {
        const RefElem* pv = &val;
        if (pv >= pos && pv < mpEnd)
            pv++;
        RefElem* e = mpEnd;
        if (e)
            e->CopyFrom(e[-1]);
        FUN_00799e00(pos, mpEnd - 1, mpEnd);
        pos->Assign(*pv);
        mpEnd++;
        return;
    }
    uint size = (uint)(mpEnd - mpBegin);
    const uint newCap = (size ? (2 * size) : 1);
    RefElem* mem = 0;
    if (newCap)
        mem = (RefElem*)operator_new(newCap * 8, "Graphics", 0, 0, kAllocFile, 0xd1);
    RefElem* b = mpBegin;
    RefElem* ne = FUN_007992e0(b, pos, mem);
    FUN_008def80(b, pos, mem);
    if (ne)
        ne->CopyFrom(val);
    RefElem* e = mpEnd;
    RefElem* ne2 = FUN_007992e0(pos, e, ne + 1);
    FUN_008def80(pos, e, ne + 1);
    if (mpBegin && ((int*)mpBegin)[-1])
        operator_delete__(mpBegin);
    mpBegin = mem;
    mpEnd = ne2;
    mpCap = mem + newCap;
}

// @ 0x0079f640
RefVec& RefVec::Assign(const RefVec& rhs)
{
    if (&rhs != this) {
        RefElem* rb = rhs.mpBegin;
        RefElem* re = rhs.mpEnd;
        uint n = (uint)(re - rb);
        if (n > (uint)(mpCap - mpBegin)) {
            RefElem* np = DoAllocateCopy(n, rb, re);
            DestroyRange(mpBegin, mpEnd);
            if (mpBegin && ((int*)mpBegin)[-1])
                operator_delete__(mpBegin);
            mpCap = np + n;
            mpEnd = np + n;
            mpBegin = np;
            return *this;
        }
        uint size = (uint)(mpEnd - mpBegin);
        if (n > size) {
            FUN_008defe0(rb, rb + size, mpBegin);
            RefElem* out;
            FUN_00799290(&out, rhs.mpBegin + (mpEnd - mpBegin), rhs.mpEnd, mpEnd, &rhs);
            mpEnd = mpBegin + n;
            return *this;
        }
        RefElem* p = FUN_008defe0(rb, re, mpBegin);
        DestroyRange(p, mpEnd);
        mpEnd = mpBegin + n;
    }
    return *this;
}

struct PtrFixedVec64 {
    void** mpBegin; void** mpEnd; void** mpCap; void** fixed;
    void* buf[64];
    PtrFixedVec64() { mpBegin = buf; mpEnd = buf; mpCap = buf + 64; fixed = buf; }
    ~PtrFixedVec64() {
        if (mpBegin && mpBegin != fixed)
            operator_delete__(mpBegin);
    }
    void DoInsert(void** pos, void* const* val);        // 0x6c1570
};

// @ 0x0079f7b0
void ReleaseAndClear(RefVec* v)
{
    PtrFixedVec64 held;
    int n = (int)(v->mpEnd - v->mpBegin);
    for (int i = 0; i < n; i++) {
        if (v->mpBegin[i].p != 0) {
            if (held.mpEnd < held.mpCap) {
                void** s = held.mpEnd++;
                if (s)
                    *s = (void*)v->mpBegin[i].p;
            } else {
                held.DoInsert(held.mpEnd, (void* const*)&v->mpBegin[i].p);
            }
            v->mpBegin[i].p = 0;
        }
    }
    FUN_00762d70((int)(held.mpEnd - held.mpBegin), held.mpBegin);
    // inlined vector::erase(begin(), end()): copy [end, end) down, then end -= count
    RefElem* first = v->mpBegin;
    RefElem* last = v->mpEnd;
    RefElem* d = first;
    for (RefElem* s = last; s != last; ++s, ++d) {
        d->p = s->p;
        d->x = s->x;
    }
    v->mpEnd -= (last - first);
}
