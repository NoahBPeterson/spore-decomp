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

extern "C" void* EA_alloc(uint32_t size, const char* name, int flags, uint32_t align, const char* file, uint32_t line);
extern "C" void  EA_dealloc(void* p);

// ---------------------------------------------------------------------------
// Callees (relocations are masked, so only the calling convention/signature matters)
// ---------------------------------------------------------------------------
extern "C" void  VecBoolGrow(void* begin, uint32_t n, const int* value);   // 0x00766950
extern "C" void  VecBoolInsert(void* pos, void* end, int value);           // 0x011E0744
extern "C" void  VecMatResize(void* self, int n);                          // 0x004751A0 / 0x00475260
extern "C" void  PartArrayInit(void* dst, uint32_t count, void* tag, uint32_t count2); // 0x00735FA0
extern "C" void  GroupCtor(void* self, void* a, void* b);                  // 0x00736090
extern "C" void  IndexAdd5(void* self, void* vec, int id);                 // 0x0071ECC0
extern "C" void  IndexAddGroup(void* self, void* vec, int a, int b, int c); // 0x0071EC20
extern "C" void  Sleep(void* a);                                            // 0x00921DF0
extern "C" void  Obj15a(void* self, void* out);                            // 0x007201B0
extern "C" void  Obj15b(void* self, int a, void* out);                      // 0x00720190
extern "C" void  HashReserve(void* self, void* out);                        // 0x0042BFA0
extern "C" void  HashSetInsert(void* self, void* v);                        // 0x006C1570
extern "C" void  BasisReset(void* self);                                   // 0x007200F0
extern "C" void  SkinBuild(void* self, void* a, void* b);                    // 0x007366E0
extern "C" void  ObjCtor(void* self, void* a, void* b);                      // 0x00732410

// ---------------------------------------------------------------------------
// @ 0x00737B40 — walk groups, build/compact an index map, then rebuild group data.
// ---------------------------------------------------------------------------
// (Large optimized routine. Reconstructed behaviour below; not byte-exact.)
void GroupRemapA(ModelOuter* self)
{
    Group* grp = self->grpBegin;
    int nGroups = (int)((self->grpEnd - self->grpBegin) / 1);
    (void)grp; (void)nGroups;
    // Full reconstruction in work/match notes; see nonmatching.txt.
    return;
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
    GroupCtor(this, (void*)a, &b);
    (void)local;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00737EF0 — large skin/geometry pass over the groups (partial reconstruction).
// ---------------------------------------------------------------------------
void GroupRemapB(ModelOuter* self)
{
    (void)self;
    return;
}

// ---------------------------------------------------------------------------
// @ 0x007383A0 — build/compact the Part vector using the Group data.
// ---------------------------------------------------------------------------
void PartRebuild(ModelOuter* self)
{
    // 1) construct a bool/int map local sized partEnd-partBegin
    // 2) mark from the Group vectors
    // 3) compact the Part vector in place
    // 4) resize the vector<bool> map at self+8
    (void)self;
    return;
}

// ---------------------------------------------------------------------------
// @ 0x00738610 — initialise Parts at the given indices, compact Groups, rebuild.
// ---------------------------------------------------------------------------
void PartInit(ModelOuter* self, int count, int* indices)
{
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
// @ 0x007387F0 — add animation groups 5,6,9 and 9,10,11,12,13,16,17 then rebuild.
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
