// Slice s00718640: more SP::cMeshBuilder vector helpers (index insert+adjust,
// range copy) and larger editor routines.  Built /O2 /MD /Gy /EHsc /TP.
// This region is not in the 2008 dev PDB; layouts read from the disassembly and
// from the constructor in slice s00716110.
#include <stddef.h>

typedef unsigned int u32;
typedef unsigned char u8;

struct VecN {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    VecN& operator=(const VecN& o);                                // masked
    void  insert(void* pos, const void* first, const void* last, int tag); // masked range insert
};
struct VecSlotN { VecN v; char pad[8]; };   // 0x14 bytes

struct Elem28 { VecN v0; char p0[8]; VecN v14; char p1[8]; };

struct MeshBuilder8 {
    char   pad0[0xd0];               // +0x00
    void*  pD0;                      // +0xd0
    char   padD4[0xe8 - 0xd4];
    void*  pE8;                      // +0xe8
    char   padEC[0x150 - 0xec];
    u8     b150;                     // +0x150
    char   pad151[0x160 - 0x151];
    int    n160;                     // +0x160
    char   pad164[0x188 - 0x164];
    VecSlotN v188[8];                // +0x188 .. +0x228

    void addIndices0(int count, const int* values, int delta);
    void addIndices1(int count, const int* values, int delta);
    void addIndicesSlot(int count, const int* values, int delta, int index);
    void addIndicesSlot6(int count, const int* values, int delta, int index);
    void finish();
    // callees (other slices / TUs), masked
    void sub18820();
    void sub17ce0();
    void sub173e0();
    void sub18050();
};

// ---------------------------------------------------------------------------
// range copies / fills
// ---------------------------------------------------------------------------

// @ 0x00718640
Elem28* copyBack28(Elem28* first, Elem28* last, Elem28* dst)
{
    while (last != first) {
        --last;
        --dst;
        dst->v0 = last->v0;
        dst->v14 = last->v14;
    }
    return dst;
}

// @ 0x00719200
void fill28(Elem28* first, Elem28* last, const Elem28* value)
{
    while (first != last) {
        first->v0 = value->v0;
        first->v14 = value->v14;
        ++first;
    }
}

// ---------------------------------------------------------------------------
// insert values then add delta to the freshly inserted elements
// ---------------------------------------------------------------------------

// @ 0x00718680
void MeshBuilder8::addIndices0(int count, const int* values, int delta)
{
    v188[0].v.insert(v188[0].v.mpEnd, values, values + count, count);
    if (delta != 0) {
        int* p = (int*)v188[0].v.mpEnd - count;
        while (p != (int*)v188[0].v.mpEnd) {
            *p += delta;
            ++p;
        }
    }
}

// @ 0x007186e0
void MeshBuilder8::addIndices1(int count, const int* values, int delta)
{
    v188[1].v.insert(v188[1].v.mpEnd, values, values + count, count);
    if (delta != 0) {
        int* p = (int*)v188[1].v.mpEnd - count;
        while (p != (int*)v188[1].v.mpEnd) {
            *p += delta;
            ++p;
        }
    }
}

// @ 0x00718740
void MeshBuilder8::addIndicesSlot(int count, const int* values, int delta, int index)
{
    VecN& v = v188[2 + index].v;
    v.insert(v.mpEnd, values, values + count, count);
    if (delta != 0) {
        int* p = (int*)v.mpEnd - count;
        while (p != (int*)v.mpEnd) {
            *p += delta;
            ++p;
        }
    }
}

// @ 0x007187b0
void MeshBuilder8::addIndicesSlot6(int count, const int* values, int delta, int index)
{
    VecN& v = v188[6 + index].v;
    v.insert(v.mpEnd, values, values + count, count);
    if (delta != 0) {
        int* p = (int*)v.mpEnd - count;
        while (p != (int*)v.mpEnd) {
            *p += delta;
            ++p;
        }
    }
}

// @ 0x00719240
void MeshBuilder8::finish()
{
    if (n160 >= 0) {
        char* base = (char*)pD0 + n160 * 0xd0;
        *(int*)((char*)pE8 - 8) = (*(int*)(base + 0xc0) - *(int*)(base + 0xbc)) >> 2;
    }
    sub18820();
    sub17ce0();
    sub173e0();
    sub18050();
    b150 = 0;
}

// ---------------------------------------------------------------------------
// remaining routines (nonmatching / partial reconstructions)
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Rework VAs: the fixed-id vector and the 0xd0 / 0x50-byte element vectors.
// ---------------------------------------------------------------------------

// spstl fixed-id vector (16-bit ids, 4-byte slots).
struct FixedIdVector6
{
    u32* mpBegin;      // +0x00
    u32* mpEnd;        // +0x04
    u32* mpCapacity;   // +0x08

    FixedIdVector6* Assign(const FixedIdVector6& x);               // @ 0x00719170
    void DoAssign(u32* first, u32* last, const FixedIdVector6& x); // 0x0042cd50
};
typedef void (__thiscall* FixedIdDoAssignFn)(void*, const u32*, const u32*, const void*);
extern "C" void FUN_0042cd50(void);                 // FixedIdVector6::DoAssign

// @ 0x00719170  FixedIdVector6::Assign  (inlined erase, then DoAssign)
FixedIdVector6* FixedIdVector6::Assign(const FixedIdVector6& x)
{
    if (this != &x) {
        u32* first = mpBegin;
        u32* last  = mpEnd;
        u32* dst   = first;
        for (const u32* src = last; src != last; ++src)   // empty tail copy
            *dst++ = *src;
        mpEnd = mpEnd - (last - first);
        ((FixedIdDoAssignFn)(void*)FUN_0042cd50)(this, x.mpBegin, x.mpEnd, &x);
    }
    return this;
}

// eastl-style vector of 0xd0-byte elements (SP::cMeshBuilder instances).
struct MeshVecD0
{
    u8* mpBegin;      // +0x00
    u8* mpEnd;        // +0x04
    u8* mpCapacity;   // +0x08

    u8*  relocateRange(u8* first, u8* last);              // @ 0x00719330
    void insert(u8* position, u32 n, const void* value);  // @ 0x007193e0
};

// eastl-style vector of 0x50-byte elements.
struct MeshVec50
{
    u8* mpBegin;      // +0x00
    u8* mpEnd;        // +0x04
    u8* mpCapacity;   // +0x08

    u8* copyEraseRange(u8* first, u8* last);              // @ 0x00719390
};

extern "C" void* FUN_00717a90(void*, void*, void*);       // relocate 0xd0 elements
extern "C" void* FUN_00717ad0(void*, void*, void*);       // copy 0x50 elements
extern "C" void  FUN_00714b40(void);                      // tail teardown (thiscall, 2 args)
extern "C" void  FUN_007146c0(void);                      // AdapterTeardown::Destroy
extern "C" void  FUN_00716110(void);                      // 0xd0-element copy ctor
extern "C" void  FUN_00716440(void*, u32, void*, void*);   // construct n copies
extern "C" void  FUN_007191d0(void*, void*, void*);        // construct a range
extern "C" void  FUN_007163c0(void*, void*, void*, void*, void*); // range relocation
extern "C" void* FUN_007165c0(void*, void*, void*);       // copy-construct a range
extern "C" void  FUN_00714960(void*, void*, void*);       // destroy a range
extern "C" void  FUN_00717b30(void*, void*, void*);       // move an element range

typedef void (__thiscall* DestroyFn)(void*);
typedef void (__thiscall* CopyCtorFn)(void*, const void*);
typedef void (__thiscall* TailFn)(void*, u8*, u8*);

#define ELEM_D0 0xd0
#define ELEM_50 0x50

// @ 0x00719330  MeshVecD0::relocateRange — relocate [first,last) and destroy the tail
u8* MeshVecD0::relocateRange(u8* first, u8* last)
{
    u8* r      = (u8*)FUN_00717a90(last, mpEnd, first);
    u8* oldEnd = mpEnd;
    for (; r < oldEnd; r += ELEM_D0)
        ((DestroyFn)(void*)FUN_007146c0)(r);
    mpEnd -= ((ptrdiff_t)(last - first) / ELEM_D0) * ELEM_D0;
    return first;
}

// @ 0x00719390  MeshVec50::copyEraseRange — copy [first,last) down and tear down the tail
u8* MeshVec50::copyEraseRange(u8* first, u8* last)
{
    u8* r = (u8*)FUN_00717ad0(last, mpEnd, first);
    ((TailFn)(void*)FUN_00714b40)(this, r, mpEnd);
    mpEnd -= ((ptrdiff_t)(last - first) / ELEM_50) * ELEM_50;
    return first;
}

// ---------------------------------------------------------------------------
// 0x00718820: merge duplicate texcoord/color index tuples of the sections
// ---------------------------------------------------------------------------

void* __cdecl xmemcpy(void* d, const void* s, size_t n);          // 0x011e0744
void* __cdecl EAAlloc(size_t n, const char* name, int flags, int align, const char* file, int line); // 0x00f473a0
void  __cdecl EAFree(void* p);                                    // 0x00f47380

#define ALLOC_H "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

struct Vec2 { float x, y; Vec2() {} Vec2(const Vec2& o) : x(o.x), y(o.y) {}
  Vec2& operator=(const Vec2& o) { x = o.x; y = o.y; return *this; } };
struct Byte4 { u8 b[4]; Byte4() { b[0] = 0; b[1] = 0; b[2] = 0; b[3] = 0; } };
struct Vertex6 { int a[4]; int b[2]; };

extern Vec2 gDefaultTexCoord;      // 0x0162a4e8
extern u32  gUVMask;               // 0x015366b8 (bitset<11> mask)

// EASTL-style vector with sp_vector_allocator (new[]-style header word before the data).
// The out-of-line members are per element type (CRTP), each with its original address.
template <class T, class D> struct SVecBase {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    SVecBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    explicit SVecBase(u32 n) {
        mpBegin = n ? (T*)EAAlloc(n * sizeof(T), "Graphics", 0, 0, ALLOC_H, 0xd1) : 0;
        mpEnd = mpBegin + n;
        mpCapacity = mpEnd;
        for (T* p = mpBegin; n; --n) { *p = T(); ++p; }
    }
    ~SVecBase() { if (mpBegin && ((u32*)mpBegin)[-1] != 0) EAFree(mpBegin); }
    int size() const { return (int)(mpEnd - mpBegin); }
    void erase(T* first, T* last) {
        xmemcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd = mpEnd - (last - first);
    }
    void clear() { erase(mpBegin, mpEnd); }
    void resize(u32 n, const T& v) {
        u32 cur = (u32)(mpEnd - mpBegin);
        if (cur < n) static_cast<D*>(this)->insert(mpEnd, n - cur, v);
        else erase(mpBegin + n, mpEnd);
    }
    void push_back(const T& v) {
        if (mpEnd < mpCapacity) { if (mpEnd) *mpEnd = v; ++mpEnd; }
        else static_cast<D*>(this)->DoInsertValue(mpEnd, v);
    }
};
struct UIntVec : SVecBase<u32, UIntVec> {
    UIntVec() {}
    explicit UIntVec(u32 n) : SVecBase<u32, UIntVec>(n) {}
    void DoInsertValue(u32* pos, const u32& v);                    // 0x004558a0
};
struct IntVec : SVecBase<int, IntVec> {
    IntVec() {}
    explicit IntVec(u32 n) : SVecBase<int, IntVec>(n) {}
    void insert(int* pos, u32 n, const int& v);                    // 0x004cea40
};
struct Vec2Vec : SVecBase<Vec2, Vec2Vec> {
    void reserve(u32 n);                                           // 0x00473e40
    void DoInsertValue(Vec2* pos, const Vec2& v);                  // 0x00476000
    void assign(const Vec2Vec& o);                                 // 0x00473b00
};
struct Byte4Vec : SVecBase<Byte4, Byte4Vec> {
    void reserve(u32 n);                                           // 0x00714cd0
    void DoInsertValue(Byte4* pos, const Byte4& v);                // 0x00715350
    void assign(const Byte4Vec& o);                                // 0x00715250
};
template <class V> struct Slot { V v; u32 pad[2]; };

struct VertexVec {
    Vertex6* mpBegin; Vertex6* mpEnd; Vertex6* mpCapacity;
    void resize(u32 n);                                            // 0x00717890 masked
};
void __cdecl SortVertexOrder(int* first, int* last, VertexVec* verts);   // 0x00717960

struct Section {
    u32 flags; int count; char pad8[0x28];
    Slot<IntVec> tex[4];    // +0x30
    Slot<IntVec> col[2];    // +0x80
    IntVec indices;         // +0xa8
    char padB4[0xd0 - 0xb4];
};

struct MeshBuilderUV {
    char pad0[0x30];
    Slot<Vec2Vec> tex[4];  // +0x30
    Slot<Byte4Vec> col[2]; // +0x80
    char padA8[0xd0 - 0xa8];
    Section* mpSectionsBegin;   // +0xd0
    Section* mpSectionsEnd;     // +0xd4

    void CompactAttributeVertices();
};

static inline bool SameVertex(const Vertex6* p, const Vertex6* q)
{
    for (int k = 0; k < 4; ++k)
        if (p->a[k] != q->a[k]) return false;
    for (int k = 0; k < 2; ++k)
        if (p->b[k] != q->b[k]) return false;
    return true;
}

static inline void Bump(u32& c, int& id)
{
    if (c != 0xffffffff) {
        ++c;
        id = (id < (int)c) ? (int)c : id;
    }
}

// @ 0x00718820
void MeshBuilderUV::CompactAttributeVertices()
{
    u32 c4[4];
    u32 c2[2];
    VertexVec verts = { 0, 0, 0 };
    UIntVec starts;

    for (Section* sec = mpSectionsBegin; sec != mpSectionsEnd; ++sec) {
        u32 base = (u32)(verts.mpEnd - verts.mpBegin);
        starts.push_back(base);
        u32 m = sec->flags & gUVMask;
        if (m) {
            verts.resize(base + sec->count);
            Vertex6* dst = verts.mpBegin + ((verts.mpEnd - verts.mpBegin) - sec->count);
            for (int i = 0; i < 4; ++i) {
                IntVec& v = sec->tex[i].v;
                if (v.mpBegin != v.mpEnd) {
                    for (int j = 0; j < sec->count; ++j) dst[j].a[i] = v.mpBegin[j];
                    v.clear();
                }
            }
            for (int i = 0; i < 2; ++i) {
                IntVec& v = sec->col[i].v;
                if (v.mpBegin != v.mpEnd) {
                    for (int j = 0; j < sec->count; ++j) dst[j].b[i] = v.mpBegin[j];
                    v.clear();
                }
            }
        }
    }

    if (verts.mpBegin != verts.mpEnd) {
        u32 nv = (u32)(verts.mpEnd - verts.mpBegin);
        IntVec order(nv);
        for (int i = 0; i < order.size(); ++i) order.mpBegin[i] = i;
        SortVertexOrder(order.mpBegin, order.mpEnd, (VertexVec*)&verts);

        u32 nv2 = (u32)(verts.mpEnd - verts.mpBegin);
        UIntVec remap(nv2);
        UIntVec unique;
        u32 first = order.mpBegin[0];
        unique.DoInsertValue(unique.mpEnd, first);
        remap.mpBegin[first] = 0;

        c4[0] = c4[1] = c4[2] = c4[3] = 0;
        c2[0] = c2[1] = 0;
        const Vertex6* cur = verts.mpBegin + first;
        int n = remap.size();
        int id = 0;
        for (int i = 1; i < n; ++i) {
            u32 oi = order.mpBegin[i];
            const Vertex6* v = verts.mpBegin + oi;
            if (!SameVertex(cur, v)) {
                cur = v;
                unique.push_back(oi);
                id = -1;
                for (int k = 0; k < 4; ++k) Bump(c4[k], id);
                for (int k = 0; k < 2; ++k) Bump(c2[k], id);
            }
            remap.mpBegin[oi] = id;
        }
        order.clear();

        u32* st = starts.mpBegin;
        for (Section* sec = mpSectionsBegin; sec != mpSectionsEnd; ++sec, ++st) {
            if (sec->flags & gUVMask) {
                int zero = 0;
                sec->indices.resize(sec->count, zero);
                for (int j = 0; j < sec->count; ++j)
                    sec->indices.mpBegin[j] = remap.mpBegin[*st + j];
            }
        }
        starts.clear();
        remap.clear();

        for (int i = 0; i < 4; ++i) {
            Vec2Vec& v = tex[i].v;
            if (v.mpBegin != v.mpEnd) {
                Vec2Vec tmp;
                tmp.reserve(unique.size());
                for (u32* it = unique.mpBegin; it != unique.mpEnd; ++it) {
                    int idx = verts.mpBegin[*it].a[i];
                    if (idx == -1) tmp.push_back(gDefaultTexCoord);
                    else tmp.push_back(v.mpBegin[idx]);
                }
                v.assign(tmp);
            }
        }
        Byte4 defColor;
        for (int i = 0; i < 2; ++i) {
            Byte4Vec& v = col[i].v;
            if (v.mpBegin != v.mpEnd) {
                Byte4Vec tmp;
                tmp.reserve(unique.size());
                for (u32* it = unique.mpBegin; it != unique.mpEnd; ++it) {
                    int idx = verts.mpBegin[*it].b[i];
                    if (idx == -1) tmp.push_back(defColor);
                    else tmp.push_back(v.mpBegin[idx]);
                }
                v.assign(tmp);
            }
        }
    }
    if (verts.mpBegin && ((u32*)verts.mpBegin)[-1]) EAFree(verts.mpBegin);
}

// 0xd0-byte element (SP::cMeshBuilder).  Only the pieces the insert path uses.
struct ElemD0
{
    u8    pad00[0xc];    // +0x00
    void* mpAux;         // +0x0c  auxiliary pointer forwarded to the range helpers
    u8    pad10[0xd0 - 0x10];
};

// @ 0x007193e0  MeshVecD0::insert — insert n copies of value before position
void MeshVecD0::insert(u8* position, u32 n, const void* value)
{
    if ((u32)((ptrdiff_t)(mpCapacity - mpEnd) / ELEM_D0) < n) {
        // not enough spare capacity: reallocate, copy the head, fill, move the tail
        u32 size = (u32)((ptrdiff_t)(mpEnd - mpBegin) / ELEM_D0);
        u32 grown = size * 2;
        if (size == 0) grown = 1;
        u32 cap = size + n;
        if (cap < grown) cap = grown;
        u8* buf = cap ? (u8*)EAAlloc(cap * ELEM_D0, "Graphics", 0, 0, ALLOC_H, 0xd1) : 0;
        u8* oldBegin = mpBegin;
        u8* mid = (u8*)FUN_007165c0(oldBegin, position, buf);
        FUN_00714960(oldBegin, position, buf);
        FUN_00716440(mid, n, (void*)value, oldBegin);
        u8* tailDst = mid + n * ELEM_D0;
        u8* oldEnd  = mpEnd;
        u8* newEnd  = (u8*)FUN_007165c0(position, oldEnd, tailDst);
        FUN_00714960(position, oldEnd, tailDst);
        if (mpBegin && ((u32*)mpBegin)[-1] != 0)
            EAFree(mpBegin);
        mpEnd      = newEnd;
        mpBegin    = buf;
        mpCapacity = buf + cap * ELEM_D0;
    }
    else if (n != 0) {
        ElemD0 temp;
        ((CopyCtorFn)(void*)FUN_00716110)(&temp, value);
        u32 tail = (u32)((ptrdiff_t)(mpEnd - position) / ELEM_D0);
        if (n < tail) {
            // the tail is longer than n: shift the last n elements on by n, then fill
            u8* split = mpEnd - n * ELEM_D0;
            FUN_007163c0(&temp.mpAux, split, mpEnd, mpEnd, temp.mpAux);
            mpEnd = mpEnd + n * ELEM_D0;
            FUN_00717b30(position, split, mpEnd);
            FUN_007191d0(position, position + n * ELEM_D0, &temp);
        }
        else {
            // construct the overflow past the end, then shift the whole tail
            FUN_00716440(mpEnd, n - tail, &temp, temp.mpAux);
            u8* oldEnd = mpEnd;
            mpEnd = mpEnd + (n - tail) * ELEM_D0;
            FUN_007163c0(&temp.mpAux, position, oldEnd, mpEnd, temp.mpAux);
            mpEnd = mpEnd + tail * ELEM_D0;
            FUN_007191d0(position, oldEnd, &temp);
        }
        ((DestroyFn)(void*)FUN_007146c0)(&temp);
    }
}
