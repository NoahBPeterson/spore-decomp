// slice s007a9ae0  --  texture-manager deque/allocator internals.
// Reconstructed C++ (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
#include "types.h"

extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void  EASTL_allocator_deallocate(void* p);
extern "C" long  _InterlockedExchangeAdd(volatile long* addend, long value);
#pragma intrinsic(_InterlockedExchangeAdd)
extern "C" void  memmove(void*, const void*, unsigned int);
extern "C" void* VectorDoInsertValue(void*, void*, unsigned int);
extern "C" void  FUN_00690_120_GetStatus(void*);
extern "C" void* FUN_0067dd60();
extern "C" unsigned int FUN_00932e80_hash(const char*, unsigned int, int);
extern "C" int   FUN_011ef750(int, int, void*);
extern "C" int   FUN_011ef880(void*);
extern "C" void  FUN_00761b40();
extern "C" void  FUN_00761c00();
extern "C" void* FUN_00576650_GetImageResource(void*, void*);
extern "C" void  FUN_0041e990_GetInt();
extern "C" int   FUN_00926650_AddCore(void*, int, int);

// ---- deque map (eastl::deque storage) ----------------------------------------
struct DequeMap {
    int*  mpBegin;      // +0x00
    int   mCapacity;    // +0x04
    int*  mFirst;       // +0x0c
    int*  mLast;        // +0x10
    int*  mCur;         // +0x14
    int*  mNextBegin;   // +0x18
    int*  mNextLast;    // +0x1c / +0x18?
    int*  mTailFirst;   // +0x20
    int*  mTailLast;    // +0x24
    void InsertAt(int count, int zero);
    void PushBack(int* value);
    void ReverseCopyTo(int* out, int* end);
};

struct Chunk {
    Chunk* mpNext;      // +0x00
    int    pad04;
    int    pad08;
    char   m0c;
    long   mRef;        // +0x10
    int    pad14[2];
    int    pad1c;
    int    pad20;
    int    pad24;
    int    pad28;
    int    pad2c;
};

struct cNodeAllocator {
    int   pad00[4];
    Chunk* mpHeadChunk; // +0x10
    Chunk* Create();
};

// @ 0x007a9ae0
void DequeMap::InsertAt(int count, int zero)
{
    int* first = this->mCur;
    int used = ((char*)this->mTailLast - (char*)first) >> 2;
    int n = used + 1;
    int need = n + count;
    unsigned int cap = (unsigned int)this->mCapacity;
    if ((unsigned int)(need * 2) < cap) {
        int* dst = (int*)((char*)this->mpBegin +
            ((int)((cap - need) >> 1) + (~-(unsigned)(zero != 0) & count)) * 4);
        if (dst < first)
            VectorDoInsertValue(dst, first, (used + 1) * 4);
        else
            memmove(dst + (n - (((used + 1) * 4) >> 2)), first, (used + 1) * 4);
    }
    else {
        int cap2 = (this->mCapacity < count) ? count : this->mCapacity;
        int total = cap2 + 2 + (int)cap;
        int* nb = (int*)EASTL_allocator_allocate(total * 4, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        int* src = (int*)this->mCur;
        int* dst = (int*)((char*)nb + ((((char*)src - (char*)this->mpBegin) >> 2) +
                          (~-(unsigned)(zero != 0) & count)) * 4);
        if (this->mpBegin)
            VectorDoInsertValue(dst, src, this->mTailLast - src + 1);
        if (this->mpBegin)
            EASTL_allocator_deallocate(this->mpBegin);
        this->mpBegin = nb;
        this->mCapacity = total;
    }
    this->mCur = 0;
}

// @ 0x007a9d70  reverse copy into a deque range (behavioral)
void FUN_007a9d70(int** out, int* end, int* first, int** map, int* mfirst, int* mlast, int** map2)
{
    int* a = first; int* b = map[0]; int** c = map; int* d = mfirst;
    while (a != end) {
        if (a == b) { --c; b = *c; a = b + 0x40; }
        --a;
        if (d == mlast) { --map2; mlast = *map2; d = mlast + 0x40; }
        --d; *d = *a;
    }
    out[0] = d; out[1] = mlast; out[2] = *map2; out[3] = (int*)map2;
}

// @ 0x007a9e10  Editor::cPropertyList-like ctor
extern "C" char VT_PropertyListA[];
extern "C" char VT_PropertyListB[];
extern "C" char VT_PropertyListC[];
void* FUN_007a9e10(void* self, int w, int h)
{
    *(void**)self = (void*)VT_PropertyListA;
    *(void**)((char*)self + 4) = 0;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = 0;
    *(void**)((char*)self + 0x10) = 0;
    *(void**)((char*)self + 0x14) = 0;
    *(void**)((char*)self + 0x18) = (void*)VT_PropertyListB;
    *(int*)((char*)self + 0x1c) = w;
    *(int*)((char*)self + 0x20) = h;
    *(int*)((char*)self + 0x24) = -1;
    *(void**)((char*)self + 0x28) = 0;
    *(void**)self = (void*)VT_PropertyListC;
    *(void**)((char*)self + 0x18) = (void*)VT_PropertyListB;
    void* buf = EASTL_allocator_allocate((unsigned)(w * h), "Graphics", 0, 0, 0, 0);
    *(void**)((char*)self + 0x28) = buf;
    *(int*)((char*)self + 0x24) = 1;
    return self;
}

// @ 0x007a9eb0
extern "C" char VT_ArenaResource[];
void FUN_007a9eb0(int* self)
{
    if (self[4])
        ((void(__thiscall*)(void*))((void**)self[4])[2])((void*)self[4]);
    if (self[2])
        _InterlockedExchangeAdd((volatile long*)((char*)self[2] + 8), -1);
    *(void**)self = (void*)VT_ArenaResource;
}

// @ 0x007a9f30  (large placeholder-texture init)
int FUN_007a9f30(int* self)
{
    // behavioural skeleton
    if (*(char*)((char*)self + 0xc)) return 0;
    *(unsigned char*)((char*)self + 0xc) = 1;
    *(void**)((char*)self + 0x10) = (void*)FUN_00761b40;
    *(void**)((char*)self + 0x14) = (void*)FUN_00761c00;
    return 1;
}

// @ 0x007aa320
void FUN_007aa320(int* self)
{
    if (self[1]) { void* old = (void*)self[1]; self[1] = 0; FUN_00690_120_GetStatus(old); }
    if (self[0]) {
        volatile long* rc = (volatile long*)((char*)self[0] + 0x10);
        self[0] = 0;
        _InterlockedExchangeAdd(rc, -1);
        long cur = _InterlockedExchangeAdd(rc, 0);
        if (cur < 1) _InterlockedExchangeAdd(rc, 1); else _InterlockedExchangeAdd(rc, 0);
    }
    if (self[2]) { void* p = (void*)self[2]; self[2] = 0; ((void(__thiscall*)(void*))((void**)p)[1])(p); }
    if (self[3]) { void* p = (void*)self[3]; self[3] = 0; ((void(__thiscall*)(void*))((void**)p)[1])(p); }
}

// @ 0x007aa3a0
int FUN_007aa3a0(int self, int param_2)
{
    int* a = *(int**)(self + 0xc);
    if (a && *(int*)(self + 8) == 0) {
        int* b = *(int**)(self + 8);
        if (b) { *(int*)(self + 8) = 0; ((void(__thiscall*)(void*))((void**)b)[1])(b); }
        ((void(__thiscall*)(void*, int*))((void**)a)[0x14 / 4])(a, (int*)(self + 8));
    }
    int* c = *(int**)(self + 0xc);
    if (c) { *(int*)(self + 0xc) = 0; ((void(__thiscall*)(void*))((void**)c)[1])(c); }
    int* d = *(int**)(self + 8);
    if (d && d[6]) {
        void (*cb)(int) = *(void(**)(int))(param_2 + 0x24);
        int old = *(int*)(param_2 + 0x20);
        *(int*)(param_2 + 0x20) = d[6];
        *(int*)(param_2 + 0x24) = 0;
        if (cb) cb(old);
        return 1;
    }
    return 0;
}

// @ 0x007aa430
int FUN_007aa430(int self, int a2, int a3, int a4, int a5) { (void)self;a2;a3;a4;a5; return 0; }
// @ 0x007aa530
int FUN_007aa530(int self, int a2, int a3, int a4, int a5) { (void)self;a2;a3;a4;a5; return 0; }

// @ 0x007aa620
struct Empty16 { int a, b, c, d; };
void FUN_007aa620(Empty16* self)
{
    self->a = 0; self->b = 0; self->c = 0; self->d = 0;
}

// @ 0x007aa660
void FUN_007aa660(int* self)
{
    if (self[3]) { void* p = (void*)self[3]; self[3] = 0; ((void(__thiscall*)(void*))((void**)p)[1])(p); }
}

// @ 0x007aa710
void FUN_007aa710(int* self)
{
    if (self[3]) { void* p = (void*)self[3]; self[3] = 0; ((void(__thiscall*)(void*))((void**)p)[1])(p); }
}

struct FixedAllocatorBase { bool AddCore(int, int); };

// @ 0x007aa800  SP::cNodeAllocator<...>::Create
Chunk* cNodeAllocator::Create()
{
    while (this->mpHeadChunk == 0) {
        if (!((FixedAllocatorBase*)this)->AddCore(0, 0))
            return 0;
    }
    Chunk* p = this->mpHeadChunk;
    this->mpHeadChunk = p->mpNext;
    *(int*)((char*)p + 4) = 0;
    *(int*)((char*)p + 0) = 0;
    *(int*)((char*)p + 8) = 0;
    *(unsigned char*)((char*)p + 0xc) = 0;
    _InterlockedExchangeAdd((volatile long*)((char*)p + 0x10), 1);
    *(int*)((char*)p + 0x18) = 0;
    *(int*)((char*)p + 0x1c) = 0;
    *(int*)((char*)p + 0x20) = 0;
    *(int*)((char*)p + 0x24) = 0;
    *(int*)((char*)p + 0x2c) = 0;
    return p;
}

// @ 0x007aa850  deque push_back with block allocation
void FUN_007aa850(int* self, int* value)
{
    int v = *value;
    if (self[1] <= ((self[9] - *self) >> 2) + 1)
        ((DequeMap*)self)->InsertAt(1, 1);
    int* buf = (int*)EASTL_allocator_allocate(0x100, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    *(int*)(self[9] + 4) = (int)buf;
    if (self[6]) *(int*)self[6] = v;
    int t = self[9];
    self[9] = t + 4;
    int base = *(int*)(t + 4);
    self[7] = base;
    self[8] = base + 0x100;
    self[6] = self[7];
}

// @ 0x007aaa00
int FUN_007aaa00(int* self) { (void)self; return 0; }

// @ 0x007aa0d0  SP::cTextureManager::AddTextureLoadDependency (partial skeleton)
int FUN_007aa0d0(int* self) { (void)self; return 0; }
// @ 0x007aa200  SP::cTextureManager::ReloadTexture (partial skeleton)
int FUN_007aa200(int* self) { (void)self; return 0; }
