// Slice s00737b40 — graphics/model pipeline helpers in the model region of SporeApp.exe.
//
// Optimized module: /O2 /MD /Gy /EHsc /TP (no frame pointer, SEH prologue, small stack frames).
// Functions here operate on a class whose members are EASTL vectors. Retail offsets differ from the
// 2008 dev PDB, so members are placed at the offsets observed in the disassembly; unknown gaps are pad.
//
// The allocation helpers used throughout are:
//   0x00F473A0  allocate(size, name, flags, align, file, line)
//   0x00F47380  deallocate(p)   (no-op if *(int*)(p-4) == 0)
//
// Several local containers are `eastl::vector<T, sp_vector_allocator>` (16 bytes: begin/end/capacity
// and a 4-byte allocator); their destructor frees only when the 4 bytes before the block are non-zero.

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef short int16_t;

#include <intrin.h>

// ---------------------------------------------------------------------------
// Small shared types
// ---------------------------------------------------------------------------
struct RefCounted {
    virtual void AddRef();      // slot 0
    virtual void Release();     // slot 1
    int mnRefCount;
};

// Element of the 0x8c-byte "group" vector (fields as observed in the disassembly).
struct GroupIdx { int16_t a; int16_t b; };

struct GroupMat {               // 0x10 bytes
    int f0;
    int f4;
    int16_t f8;
    int16_t fA;
    RefCounted* pC;
};

// 0x8c-byte group element.
struct Group {
    int n0;                     // +0x00
    void* p4;                   // +0x04
    int16_t s8;                 // +0x08
    int16_t sA;                 // +0x0a
    RefCounted* pC;             // +0x0c
    int n10;                    // +0x10
    GroupIdx* idxBegin;         // +0x14
    GroupIdx* idxEnd;           // +0x18
    GroupIdx* idxCap;           // +0x1c
    char pad20[0x24];           // +0x20..+0x44
    GroupMat* matBegin;         // +0x44
    GroupMat* matEnd;           // +0x48
    GroupMat* matCap;           // +0x4c
    char pad50[0x3c];           // +0x50..+0x8c
};

// Element of the 0x20-byte "anim/part" vector.
struct Part {
    int f0;                     // +0x00
    int f4;                     // +0x04
    int f8;                     // +0x08
    int fC;                     // +0x0c
    int f10;                    // +0x10
    int f14;                    // +0x14
    int16_t f18;                // +0x18
    int16_t f1A;                // +0x1a
    RefCounted* pC;             // +0x1c
};

// Outer object seen by the 0x738610-family: vector<Part> at +8, vector<Group> at +0x1c.
struct ModelOuter {
    char pad0[8];               // +0x00
    Part* partBegin;            // +0x08
    Part* partEnd;              // +0x0c
    Part* partCap;              // +0x10
    int f14;                    // +0x14
    int f18;                    // +0x18
    Group* grpBegin;            // +0x1c
    Group* grpEnd;              // +0x20
    Group* grpCap;              // +0x24
    char pad28[0x14];
};

extern "C" void* EA_alloc(uint32_t size, const char* name, int flags, uint32_t align, const char* file, uint32_t line); // 0x00F473A0
extern "C" void  EA_dealloc(void* p); // 0x00F47380

// ---------------------------------------------------------------------------
// Callees (relocations are masked, so only the calling convention/signature matters)
// ---------------------------------------------------------------------------
extern "C" void  VecBoolGrow(void* begin, uint32_t n, const int* value);   // 0x00766950
extern "C" void  VecBoolInsert(void* pos, void* end, int value);           // 0x011E0744
extern "C" void  VecMatResize(void* self, int n);                          // 0x004751A0 / 0x00475260
extern "C" void  PartArrayInit(void* dst, uint32_t count, void* tag, uint32_t count2); // 0x00735FA0
// GroupCtor is a thiscall member-style initializer (this in ecx); declared on InlineBuf below.
extern "C" void  IndexAdd5(void* self, void* vec, int id);                 // 0x0071ECC0
extern "C" void  IndexAddGroup(void* self, void* vec, int a, int b, int c); // 0x0071EC20
extern "C" void  Sleep(void* a);                                            // 0x00921DF0
extern "C" void  Obj15a(void* self, void* out);                            // 0x007201B0
extern "C" void  Obj15b(void* self, int a, void* out);                      // 0x00720190
extern "C" void  HashReserve(void* self, void* out);                        // 0x0042BFA0
extern "C" void  HashSetInsert(void* self, void* v);                        // 0x006C1570
extern "C" void  BasisReset(void* self);                                   // 0x007200F0
extern "C" void  SkinBuild(void* self);                                    // 0x007366E0
extern "C" void  ObjCtor(void* self, void* a, void* b);                      // 0x00732410

// Out-of-line desc helpers used by the group-remap passes.
extern "C" void* RefBlockAlloc(unsigned bytes);                            // 0x00720010
extern "C" void  ThreadSleep(int zero);                                    // 0x00921DF0

// Ref-counted allocation block: the descriptor payload starts 0xc bytes in (vptr + refcount).
struct RefBlock {
    virtual void AddRef();      // slot 0 (+0x00)
    virtual void Release();     // slot 1 (+0x04)
    int mnRefCount;             // +0x08
};

// A 0x10-byte strided small-int array descriptor. This is the prefix of both a Group and a
// GroupMat: count(+0), data(+4), element size class in bytes (+8), element stride (+0xa),
// owning ref-counted block (+0xc).
struct Desc {
    int        count;           // +0x00
    void*      data;            // +0x04
    int16_t    elemClass;       // +0x08   element width: 1, 2 or 4 bytes
    int16_t    stride;          // +0x0a   byte distance between elements
    RefBlock*  owner;           // +0x0c
};

static inline uint32_t ElemMask(int cls)
{
    if (cls >= 4) return 0xffffffffu;
    if (cls <= 0) return 0u;
    return (1u << (cls * 8)) - 1u;
}

static inline uint32_t ReadElem(const char* base, int off, uint32_t mask)
{
    return *(const uint32_t*)(base + off) & mask;
}

static inline void WriteElem(char* base, int off, uint32_t v, int cls)
{
    if (cls == 1)
        *(char*)(base + off) = (char)v;
    else if (cls == 2)
        *(short*)(base + off) = (short)v;
    else if (cls == 4)
        *(uint32_t*)(base + off) = v;
}

// 0x00720070 — (re)allocate the payload for a descriptor: a ref-counted block whose payload
// starts at +0xc, `count * elemClass` bytes, with stride set to the element width.
static void DescAllocate(Desc* d)
{
    if (d->count > 0) {
        RefBlock* mem = (RefBlock*)RefBlockAlloc((unsigned)(d->count * d->elemClass));
        d->data = (char*)mem + 0xc;
        RefBlock* old = d->owner;
        if (mem != old) {
            if (mem) mem->AddRef();
            d->owner = mem;
            if (old) old->Release();
        }
        d->stride = d->elemClass;
    }
}

// 0x007201B0 — clone a descriptor's count/size and allocate a fresh payload.
static void DescClone(const Desc* src, Desc* out)
{
    out->count     = src->count;
    out->elemClass = src->elemClass;
    DescAllocate(out);
}

// 0x00720190 — build a descriptor with an explicit count and element size, then allocate.
static void DescMake(Desc* out, int count, int cls)
{
    out->count     = count;
    out->elemClass = (int16_t)cls;
    DescAllocate(out);
}

// Int vector with a 16-element inline buffer (the scratch index map used by the remap passes).
struct IntMap {
    int* begin;
    int* end;
    int* cap;
    char pad0c[0xc];            // eastl allocator state
    int  inlineBuf[16];

    void Init() { begin = end = inlineBuf; cap = inlineBuf + 16; }
    unsigned Size() const { return (unsigned)(end - begin); }

    void Reserve(unsigned n)
    {
        if (n <= (unsigned)(cap - begin))
            return;
        unsigned old = Size();
        int* nb = (int*)EA_alloc(n * 4, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        for (unsigned i = 0; i < old; ++i)
            nb[i] = begin[i];
        if (begin != inlineBuf)
            EA_dealloc(begin);
        begin = nb;
        end   = nb + old;
        cap   = nb + n;
    }

    void Resize(unsigned n)
    {
        unsigned sz = Size();
        if (n > sz) {
            Reserve(n);
            while (sz < n) {
                begin[sz++] = 0;
                end = begin + sz;
            }
        } else {
            end = begin + n;
        }
    }

    void Clear() { end = begin; }

    int& operator[](unsigned i) { return begin[i]; }

    void Destroy()
    {
        if (begin != inlineBuf)
            EA_dealloc(begin);
        begin = end = cap = 0;
    }
};

// Ordered, duplicate-free list of raw element values (inline buffer of 256 ints).
struct KeyVec {
    int* begin;
    int* end;
    int* cap;
    int  inlineBuf[256];

    void Init() { begin = end = inlineBuf; cap = inlineBuf + 256; }

    int Find(int key) const
    {
        for (int* p = begin; p != end; ++p)
            if (*p == key)
                return (int)(p - begin);
        return -1;
    }

    int operator[](unsigned i) const { return begin[i]; }

    void Push(int key)
    {
        if (end == cap) {
            unsigned old = (unsigned)(end - begin);
            unsigned n = old ? old * 2 : 1;
            int* nb = (int*)EA_alloc(n * 4, "Graphics", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
            for (unsigned i = 0; i < old; ++i)
                nb[i] = begin[i];
            if (begin != inlineBuf)
                EA_dealloc(begin);
            begin = nb;
            end   = nb + old;
            cap   = nb + n;
        }
        *end++ = key;
    }

    void Destroy()
    {
        if (begin != inlineBuf)
            EA_dealloc(begin);
        begin = end = cap = 0;
    }
};

// Out-of-line EASTL vector resizes; `this` is the vector header (begin/end/capacity).
struct MatVecOps {
    void Resize(int n);         // 0x004751A0
};
struct PartVecOps {
    void Resize(int n);         // 0x00475260
};

// Out-of-line constructor for the inline-buffered int vector (size `count`, every element `value`).
struct IntMapCtor {
    void Construct(unsigned count, int value);  // 0x00737E80
};

// ---------------------------------------------------------------------------
// @ 0x00737B40 — walk groups, build/compact an index map, then rebuild group data.
// ---------------------------------------------------------------------------
// (Large optimized routine. Reconstructed behaviour below; not byte-exact.)
//
// For every group with materials: build a map over the material slots, mark the slots referenced
// by the group's index list, compact the live materials to the front (renumbering them in the map)
// and finally rewrite each index to the compacted slot number.
void GroupRemapA(ModelOuter* self)
{
    IntMap map;
    map.Init();

    int nGroups = (int)(self->grpEnd - self->grpBegin);
    for (int gi = 0; gi < nGroups; ++gi) {
        Group* g = self->grpBegin + gi;
        if (g->matBegin == g->matEnd)
            continue;

        unsigned nMat = (unsigned)(g->matEnd - g->matBegin);
        map.Resize(nMat);

        unsigned nIdx = (unsigned)(g->idxEnd - g->idxBegin);
        for (unsigned i = 0; i < nIdx; ++i)
            map[(unsigned)(unsigned short)g->idxBegin[i].b] = 1;

        unsigned w = 0;
        for (unsigned j = 0; j < nMat; ++j) {
            if (map[j] == 0)
                continue;

            map[j] = (int)w;
            GroupMat* dst = g->matBegin + w;
            GroupMat* src = g->matBegin + j;
            dst->f0 = src->f0;
            dst->f4 = src->f4;
            dst->f8 = src->f8;
            dst->fA = src->fA;
            RefCounted* nw  = src->pC;
            RefCounted* old = dst->pC;
            if (nw != old) {
                if (nw) nw->AddRef();
                dst->pC = nw;
                if (old) old->Release();
            }
            ++w;
        }

        MatVecOps* mops = (MatVecOps*)&g->matBegin;
        mops->Resize((int)w);

        for (unsigned i = 0; i < nIdx; ++i) {
            unsigned short slot = (unsigned short)g->idxBegin[i].b;
            g->idxBegin[i].b = (int16_t)map[slot];
        }

        map.Clear();
    }

    map.Destroy();
}

// ---------------------------------------------------------------------------
// @ 0x00737DC0 — construct a pool of `count` 0x24-byte elements via the EA allocator.
// ---------------------------------------------------------------------------
struct ElemPool24 {
    void* begin;                // +0x00
    void* end;                  // +0x04
    void* cap;                  // +0x08
    void* ctor(unsigned count, void* tag);
};

void* ElemPool24::ctor(unsigned count, void* tag)
{
    void* mem;
    if (count == 0)
        mem = 0;
    else
        mem = EA_alloc(count * 0x24,
                       "Graphics", 0, 0,
                       "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                       0xd1);
    this->begin = mem;
    this->end = mem;
    this->cap = (char*)mem + count * 0x24;
    char local[16];
    PartArrayInit(mem, count, local, count);
    if (local && *(int*)(local - 4))
        EA_dealloc(local);
    this->end = (char*)this->begin + count * 0x24;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00737E80 — construct an inline-buffered container (buffer at this+0x18, capacity 0x40).
// ---------------------------------------------------------------------------
struct InlineBuf {
    void* f0;                   // +0x00
    void* f4;                   // +0x04
    void* f8;                   // +0x08
    char padC[4];
    void* f10;                  // +0x10
    char pad14[4];
    char buffer[0x40];          // +0x18
    void GroupCtor(void* a, void* b);   // 0x00736090 (this in ecx)
    void* ctor(unsigned a, unsigned b);
};

void* InlineBuf::ctor(unsigned a, unsigned b)
{
    char* bufBase = buffer;
    f0 = bufBase;
    f4 = bufBase;
    f8 = bufBase + 0x40;
    f10 = bufBase;
    int local = 0;
    GroupCtor((void*)a, &b);
    (void)local;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00737EF0 — large skin/geometry pass over the groups (partial reconstruction).
//
// Each group's strided small-int array is rewritten to dense 0..n-1 ids (first occurrence order),
// its materials are expanded to n elements in that same order, and the distinct-key table used for
// the expansion is kept in `grp->n10`/`grp->mat*` for later passes.
// ---------------------------------------------------------------------------
void GroupRemapB(ModelOuter* self)
{
    SkinBuild(self);

    int nGroups = (int)(self->grpEnd - self->grpBegin);
    for (int gi = 0; gi < nGroups; ++gi) {
        Group* g = self->grpBegin + gi;
        if (g->p4 == 0)
            continue;

        Desc* gd = (Desc*)g;
        KeyVec keys;
        keys.Init();

        Desc nd = { 0, 0, 0, 0, 0 };
        DescClone(gd, &nd);                     // count/element class from the group

        unsigned count = (unsigned)g->n0;
        int distinct = 0;
        uint32_t gmask = ElemMask(gd->elemClass);
        for (unsigned i = 0; i < count; ++i) {
            uint32_t key = ReadElem((const char*)gd->data, gd->stride * (int)i, gmask);
            int id = keys.Find((int)key);
            if (id < 0) {
                id = distinct++;
                keys.Push((int)key);
            }
            WriteElem((char*)nd.data, nd.stride * (int)i, (uint32_t)id, nd.elemClass);
        }

        gd->data      = nd.data;
        gd->elemClass = nd.elemClass;
        gd->stride    = nd.stride;
        if (nd.owner != gd->owner) {
            if (nd.owner) nd.owner->AddRef();
            RefBlock* old = gd->owner;
            gd->owner = nd.owner;
            if (old) old->Release();
        }
        g->n10 = distinct;

        for (GroupMat* m = g->matBegin; m != g->matEnd; ++m) {
            Desc* md = (Desc*)m;
            int mcls    = md->elemClass;
            int mstride = md->stride;
            void* mdata = md->data;
            RefBlock* mold = md->owner;
            if (mold) mold->AddRef();

            Desc nd2 = { 0, 0, 0, 0, 0 };
            DescMake(&nd2, distinct, mcls);

            uint32_t mmask = ElemMask(mcls);
            for (int i = 0; i < distinct; ++i) {
                uint32_t v = ReadElem((const char*)mdata, mstride * keys[i], mmask);
                WriteElem((char*)nd2.data, nd2.stride * i, v, nd2.elemClass);
            }

            md->data      = nd2.data;
            md->elemClass = nd2.elemClass;
            md->stride    = nd2.stride;
            if (nd2.owner != md->owner) {
                if (nd2.owner) nd2.owner->AddRef();
                RefBlock* old = md->owner;
                md->owner = nd2.owner;
                if (old) old->Release();
            }
            if (nd2.owner) nd2.owner->Release();
            if (mold) mold->Release();
        }

        keys.Destroy();
        ThreadSleep(0);
    }
}

// ---------------------------------------------------------------------------
// @ 0x007383A0 — build/compact the Part vector using the Group data.
//
// Parts referenced by any group index (or that carry a non-default class) survive; the rest are
// dropped, surviving parts keep their relative order, and group indices are renumbered to match.
// ---------------------------------------------------------------------------
void PartRebuild(ModelOuter* self)
{
    int nPart = (int)(self->partEnd - self->partBegin);
    if (nPart < 0)
        nPart = 0;

    IntMap map;
    ((IntMapCtor*)&map)->Construct((unsigned)nPart, 0);
    map.Resize((unsigned)nPart);

    for (int i = 0; i < nPart; ++i) {
        Part* p = self->partBegin + i;
        if (p->fC > 3 && p->fC != 0xe)
            map[(unsigned)i] = 1;
    }

    int nGroups = (int)(self->grpEnd - self->grpBegin);
    for (int gi = 0; gi < nGroups; ++gi) {
        Group* g = self->grpBegin + gi;
        unsigned n = (unsigned)(g->idxEnd - g->idxBegin);
        for (unsigned i = 0; i < n; ++i)
            map[(unsigned)(unsigned short)g->idxBegin[i].a] = 1;
    }

    unsigned w = 0;
    for (int j = 0; j < nPart; ++j) {
        if (map[(unsigned)j] == 0)
            continue;

        map[(unsigned)j] = (int)w;
        Part* dst = self->partBegin + w;
        Part* src = self->partBegin + j;
        dst->f0  = src->f0;
        dst->f4  = src->f4;
        dst->f8  = src->f8;
        dst->fC  = src->fC;
        dst->f10 = src->f10;
        dst->f14 = src->f14;
        dst->f18 = src->f18;
        dst->f1A = src->f1A;
        RefCounted* nw  = src->pC;
        RefCounted* old = dst->pC;
        if (nw != old) {
            if (nw) nw->AddRef();
            dst->pC = nw;
            if (old) old->Release();
        }
        ++w;
    }

    PartVecOps* pops = (PartVecOps*)&self->partBegin;
    pops->Resize((int)w);

    for (int gi = 0; gi < nGroups; ++gi) {
        Group* g = self->grpBegin + gi;
        unsigned n = (unsigned)(g->idxEnd - g->idxBegin);
        for (unsigned i = 0; i < n; ++i) {
            unsigned short slot = (unsigned short)g->idxBegin[i].a;
            g->idxBegin[i].a = (int16_t)map[slot];
        }
    }

    map.Destroy();
}

// ---------------------------------------------------------------------------
// @ 0x00738610 — initialise Parts at the given indices, compact Groups, rebuild.
// ---------------------------------------------------------------------------
void PartInit(ModelOuter* self, int count, int* indices)
{
    if (count <= 0)
        return;
    int i;
    for (i = 0; i < count; ++i) {
        Part* p = self->partBegin + indices[i];
        p->f0 = 0; p->f4 = 0; p->f8 = 0; p->fC = 0xe;
        p->f10 = 0; p->f14 = 0; p->f18 = 0; p->f1A = 0;
        if (p->pC) {
            RefCounted* old = p->pC;
            p->pC = 0;
            old->Release();
        }
    }
    bool changed = false;
    Group* g = self->grpBegin;
    for (; g != self->grpEnd; ++g) {
        int n = (int)(g->idxEnd - g->idxBegin);
        int w = 0;
        for (i = 0; i < n; ++i) {
            int idx = g->idxBegin[i].a;
            if (*(int*)((char*)self->partBegin + idx * 0x20) != 0)
                g->idxBegin[w++] = g->idxBegin[i];
        }
        if (w != n) {
            // resize/erase tail
            changed = true;
        }
    }
    PartRebuild(self);
    if (changed)
        GroupRemapA(self);
}

// ---------------------------------------------------------------------------
// Add animation groups 5,6,9 and 9,10,11,12,13,16,17 then rebuild.
// ---------------------------------------------------------------------------
struct IntVec {
    int* begin;
    int* end;
    int* cap;
    int alloc[2];               // 8-byte sp_vector_allocator
    ~IntVec()
    {
        if (begin && *(int*)((char*)begin - 4))
            EA_dealloc(begin);
    }
};

// @ 0x007387F0
void AddAnimGroupsA(ModelOuter* self)
{
    IntVec v;
    v.begin = 0; v.end = 0; v.cap = 0;
    _ReadWriteBarrier();
    IndexAdd5(self, &v, 5);
    IndexAdd5(self, &v, 6);
    IndexAdd5(self, &v, 9);
    IndexAddGroup(self, &v, 9, 0, 0xe);
    IndexAddGroup(self, &v, 10, 0, 0xe);
    IndexAddGroup(self, &v, 11, 0, 0xe);
    IndexAddGroup(self, &v, 12, 0, 0xe);
    IndexAddGroup(self, &v, 13, 0, 0xe);
    IndexAddGroup(self, &v, 16, 0, 0xe);
    IndexAddGroup(self, &v, 17, 0, 0xe);
    PartInit(self, (int)(v.end - v.begin), v.begin);
}

// ---------------------------------------------------------------------------
// @ 0x00738900 — add animation groups 3,14,4,15 then rebuild.
// ---------------------------------------------------------------------------
void AddAnimGroupsB(ModelOuter* self)
{
    IntVec v;
    v.begin = 0; v.end = 0; v.cap = 0;
    IndexAddGroup(self, &v, 3, 0, 0xe);
    IndexAddGroup(self, &v, 0xe, 0, 0xe);
    IndexAddGroup(self, &v, 4, 0, 0xe);
    IndexAddGroup(self, &v, 0xf, 0, 0xe);
    PartInit(self, (int)(v.end - v.begin), v.begin);
}
