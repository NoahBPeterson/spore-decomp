// Slice s0070efa0: SP::cMaterialManager shader IO + eastl container/refcount helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

void* __cdecl EAlloc(size_t n, const char* name, int a, unsigned b, const char* file, int line); // 0x00f473a0
void  __cdecl EFree(void* p);                                                                    // 0x00f47380
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);                            // msvcr90

struct RC3c { void AddRef(); void Release(); };  // refcount at +0x3c
struct RC3b { void AddRef(); void Release(); };  // refcount at +0x3c (second family)

// assign forward: *dst = *src with AddRef/Release (matches AssignCopyA in slice 45)
void** AssignCopyA(void** first, void** last, void** dst); // 0x0070e340
void** AssignCopyB(void** first, void** last, void** dst); // 0x0070e390

struct VecBase {
    void** mpBegin; void** mpEnd; void** mpCap;
    void DestroyRange(void** first, void** last);   // 0x70f520
};

// @ 0x0070f520  (atomic weak-release over a range; refcount at +8)
void VecBase::DestroyRange(void** first, void** last)
{
    for (; first < last; ++first)
    {
        void* p = *first;
        if (p != 0)
        {
            volatile long* rc = (volatile long*)((char*)p + 8);
            if (*rc > 1)
                --*rc;
        }
    }
}

// @ 0x0070f320  (vector<AutoRefCount<RC3c>> storage teardown)
struct VecA {
    void** mpBegin; void** mpEnd; void** mpCap;
    ~VecA();
    void Shrink(void** a, void** b);
};
VecA::~VecA()
{
    void** first = mpBegin;
    void** last = mpEnd;
    for (; first < last; ++first)
    {
        if (*first != 0)
            ((RC3c*)*first)->Release();
    }
    void* p = mpBegin;
    if ((p != 0) && (*(int*)((char*)p - 4) != 0))
        EFree(p);
}

// @ 0x0070f390  (vector<AutoRefCount<RC3b>> storage teardown)
struct VecB {
    void** mpBegin; void** mpEnd; void** mpCap;
    ~VecB();
    void Shrink(void** a, void** b);
};
VecB::~VecB()
{
    void** first = mpBegin;
    void** last = mpEnd;
    for (; first < last; ++first)
    {
        if (*first != 0)
            ((RC3b*)*first)->Release();
    }
    void* p = mpBegin;
    if ((p != 0) && (*(int*)((char*)p - 4) != 0))
        EFree(p);
}

// @ 0x0070f570
void FillWeak14N(void** dst, unsigned n, void** value)
{
    while (n > 0)
    {
        if (dst != 0)
        {
            void* p = *value;
            *dst = p;
            if (p != 0)
                ++*(int*)((char*)p + 0x14);
        }
        --n;
        ++dst;
    }
}

// @ 0x0070f660
struct FVecA {
    VecBase mVec; void** mpAllocName; void** mp16;
    void Teardown();
};
void FVecA::Teardown()
{
    mVec.DestroyRange(mVec.mpBegin, mVec.mpEnd);
    void* p = mVec.mpBegin;
    if ((p != 0) && (p != mp16))
        EFree(p);
}

// @ 0x0070f890
struct FVecB { char _p[0x20]; void Teardown(); };
void FVecB::Teardown()
{
    VecBase* v = (VecBase*)((char*)this + 0x20);
    v->DestroyRange(v->mpBegin, v->mpEnd);
    void* p = v->mpBegin;
    if ((p != 0) && (p != *(void**)((char*)v + 0x10)))
        EFree(p);
}

// @ 0x0070fa30
struct FVecC { char _p[0x24]; void Teardown(); };
void FVecC::Teardown()
{
    VecBase* v = (VecBase*)((char*)this + 0x24);
    v->DestroyRange(v->mpBegin, v->mpEnd);
    void* p = v->mpBegin;
    if ((p != 0) && (p != *(void**)((char*)v + 0x10)))
        EFree(p);
}

// @ 0x0070fa60
void VecA::Shrink(void** arg1, void** arg2)
{
    void** p = AssignCopyA(arg1, mpEnd, arg2);
    void** end = mpEnd;
    for (; p < end; ++p)
    {
        if (*p != 0)
            ((RC3c*)*p)->Release();
    }
    mpEnd = (void**)((char*)mpEnd + ((char*)arg2 - (char*)arg1));
}

// @ 0x0070fab0
void VecB::Shrink(void** arg1, void** arg2)
{
    void** p = AssignCopyB(arg1, mpEnd, arg2);
    void** end = mpEnd;
    for (; p < end; ++p)
    {
        if (*p != 0)
            ((RC3b*)*p)->Release();
    }
    mpEnd = (void**)((char*)mpEnd + ((char*)arg2 - (char*)arg1));
}

struct HashNodeA { char _p[4]; RC3c* mpRef; HashNodeA* mpNext; };
struct HashNodeB { char _p[4]; RC3b* mpRef; HashNodeB* mpNext; };

// ---- remaining functions (behavioral reconstructions) ------------------------
struct Mutex  { void Lock(void* p); void Unlock(); };            // 0x009221b0 / 0x00922270
void* __cdecl ResGetManager(void);                               // 0x0067dcd0
void* __cdecl FindInMap(void* out, void* key);                   // 0x0070f690
void* __cdecl MemCopyThunk(void* dst, void* src, size_t n);      // 0x011e0744
void __cdecl CopyBackwardIntrusive(void*, void*, void*);         // 0x006f4450
int  __cdecl ReadInt32Stub(void*, void*, int, int);              // 0x0093a780
int  __cdecl WriteUint32Stub(void*, void*, int, int);            // 0x0093aa70
char __cdecl ShaderAWrite(void*, int*);                          // 0x006e6100
char __cdecl ShaderBWrite(void*, int*);                          // 0x006fcf90
void __cdecl MiscA(void*);                                        // 0x006ff170
void __cdecl MiscB(void*);                                        // 0x006fbf70
void __cdecl MiscC(void*);                                        // 0x006ff750
void __cdecl MiscD(void*, int);                                   // 0x006fc780
int  __cdecl ReadShaders_helper2(void*);                          // 0x006ff750
void __cdecl WriteBlock(void*, void*, int);                       // 0x0093a9a0

// ---- eastl vector element-operation helpers (callees, not slice targets) ----
// 16-byte element family (Vec16):
void* __cdecl UninitCopy16(void** outIter, void** first, void** last, void** dst); // 0x7f1890
void  __cdecl DoCopyBackward16(void** first, void** last, void** result);          // 0xedba80
void  __cdecl DoFill16(void** first, void** last, const void* value);              // 0x898580
void  __cdecl UninitFillN16(void** dst, unsigned n, const void* value);            // 0x88f820
void* __cdecl DoInsertValue16(void** first, void** last, void** dst); // 0xc7ea30

// AutoRefCount (RC3c) family:
void* __cdecl UninitCopyA2(void** outIter, void** first, void** last, void** dst); // 0x70e8c0
void* __cdecl CopyBackwardA(void** first, void** last, void** result);             // 0x70e3e0
void  __cdecl FillA(void** first, void** last, void** value);                      // 0x70e950
void  __cdecl UninitFillNA2(void** dst, unsigned n, void** value);                 // 0x70e9a0

// AutoRefCount (RC3b) family:
void* __cdecl CopyBackwardB(void** first, void** last, void** result);             // 0x70e430
void  __cdecl FillB(void** first, void** last, void** value);                      // 0x70ea20

// atomic-refcount family:
void* __cdecl UninitCopyAtomic8(void** outIter, void** first, void** last, void** dst); // 0x70ea70
void  __cdecl FillAtomic8(void** first, void** last, void** value);                 // 0x70eac0
void  __cdecl FillNAtomic8(void** dst, unsigned n, void** value);                   // 0x70eb30

void* __cdecl RefReleaseSeq(void* p);                                             // 0x6e54c0
void  __cdecl ShaderStateRelease(void* p);                                        // 0x6e57a0
void  __cdecl TexInstRelease(void* p);                                            // 0x6fd300

struct MatMgrR { char ReadShaders(void* stream); };
struct MatMgrW { char WriteShaders(void* stream); };

// @ 0x0070efa0  (SP::cMaterialManager::ReadShaders)
char MatMgrR::ReadShaders(void* stream)
{
    void* self = this;
    int local[3];
    local[0] = *(int*)((char*)self + 0x200);
    local[2] = *(int*)0x01535f68;
    local[1] = 0x469a3f7;
    int saved = 0;
    void** vt = *(void***)stream;
    char ok = ((char(__thiscall*)(void*, int*, int*, int, int, int, int))vt[0x34 / 4])
              (stream, local, &saved, 1, 6, 1, 0);
    if (ok == 0)
        return 1;
    int s = ((int(__thiscall*)(void*))vt[0x18 / 4])(stream);
    ReadInt32Stub((void*)s, &saved, 1, 0);
    if (saved == 1)
    {
        ReadShaders_helper2((void*)s);
        MiscD((void*)s, 1);
        ((void(__thiscall*)(void*))vt[0x24 / 4])(stream);
        return 1;
    }
    return 0;
}

// @ 0x0070f0d0  (SP::cMaterialManager::WriteShaders)
char MatMgrW::WriteShaders(void* stream)
{
    void* self = this;
    int local[4];
    local[0] = *(int*)((char*)self + 0x200);
    local[1] = 0x469a3f7;
    local[2] = *(int*)0x01535f6c;
    local[3] = 0;                          // result flag: 1 when every element wrote OK
    void** vt = *(void***)stream;
    char ok = ((char(__thiscall*)(void*, int*, int*, int, int, int, int))vt[0x34 / 4])
              (stream, local, 0, 2, 6, 1, 0);
    if (ok == 0)
        return 0;

    int s = ((int(__thiscall*)(void*))vt[0x18 / 4])(stream);

    int seven = 7;
    WriteUint32Stub((void*)s, &seven, 1, 0);

    // Direct-shader list: write count, then each shader's id + body.
    int cnt = (*(int*)((char*)self + 0x9c) - *(int*)((char*)self + 0x98)) >> 2;
    WriteUint32Stub((void*)s, &cnt, 1, 0);
    for (int i = 0; i < cnt; i++)
    {
        int id = *(int*)(*(int*)(*(int*)((char*)self + 0x98) + i * 4) + 0x38);
        WriteUint32Stub((void*)s, &id, 1, 0);
        if (ShaderAWrite((void*)s, &id) == 0)
            local[3] = 0;
    }

    // Fragment-shader list.
    int cnt2 = (*(int*)((char*)self + 0xf0) - *(int*)((char*)self + 0xec)) >> 2;
    WriteUint32Stub((void*)s, &cnt2, 1, 0);
    for (int j = 0; j < cnt2; j++)
    {
        int id = *(int*)(*(int*)(*(int*)((char*)self + 0xec) + j * 4) + 0x38);
        WriteUint32Stub((void*)s, &id, 1, 0);
        if (ShaderBWrite((void*)s, &id) == 0)
            local[3] = 0;
    }

    MiscA((void*)s);
    MiscB((void*)s);

    // Pixel-shader byte block.
    int sz = *(int*)((char*)self + 0x124) - *(int*)((char*)self + 0x120);
    WriteUint32Stub((void*)s, &sz, 1, 0);
    WriteBlock((void*)s, (void*)*(int*)((char*)self + 0x120), sz);

    ((void(__thiscall*)(void*))vt[0x24 / 4])(stream);
    return (char)(local[3] & 0xff);
}

// @ 0x0070f8c0  (SP::cMaterialManager::HasMaterial)
bool cMaterialManager_HasMaterial(void* self, int key, unsigned flags)
{
    int found[3];
    if (flags == 0)
    {
        Mutex* m = (Mutex*)((char*)self + 600);
        m->Lock((void*)0x0140c860);
        FindInMap(found, &key);
        int* vec = (int*)((char*)self + 0x174);
        if (found[0] != *(int*)(vec[1] + vec[2] * 4))
        {
            char c = *(char*)(found[0] + 4);
            m->Unlock();
            return c != 0;
        }
        m->Unlock();
        found[2] = 0;
    }
    else
    {
        if ((flags & 0xc0000000) != 0x40000000)
            return false;
        found[2] = flags & 0xffffff00;
    }
    found[0] = key;
    found[1] = 0x2f4e681b;
    void* mgr = ResGetManager();
    void** vt = *(void***)mgr;
    return ((char(__thiscall*)(void*, int*, int, int, int, int, int))vt[0xc / 4])
           (mgr, found, 0, 0, 0, 0, 0) != 0;
}

// @ 0x0070f6f0  (vector of 16-byte elements: insert)
struct Vec16 {
    char* mpBegin; char* mpEnd; char* mpCap; void* mpAllocName;
    void Insert(char* pos, unsigned n, void* value);
};
void Vec16::Insert(char* pos, unsigned n, void* value)
{
    Vec16* self = this;
    // Grow path: capacity (in elements) is strictly less than the insert count.
    unsigned cap = (unsigned)((self->mpEnd - self->mpBegin) >> 4);
    if (cap < n)
    {
        unsigned prev = (unsigned)((self->mpEnd - self->mpBegin) >> 4);
        unsigned grow = prev ? prev * 2 : 1;
        unsigned nw = prev + n;
        if (nw < grow) nw = grow;
        char* nd = (nw == 0) ? 0 : (char*)EAlloc(nw << 4, "Graphics", 0, 0, ALLOC_FILE, 0xd1);
        char* p = (char*)DoInsertValue16((void**)self->mpBegin, (void**)pos, (void**)nd);
        UninitFillN16((void**)p, n, value);
        char* p2 = (char*)DoInsertValue16((void**)pos, (void**)self->mpEnd,
                                          (void**)(p + (n << 4)));
        if (self->mpBegin != 0 && self->mpBegin != *(char**)((char*)self + 0x10))
            EFree(self->mpBegin);
        self->mpBegin = nd;
        self->mpEnd = p2;
        self->mpCap = nd + (nw << 4);
        return;
    }

    if (n == 0)
        return;

    // In-place path: extra = elements after pos.
    char* e = self->mpEnd;
    unsigned extra = (unsigned)((e - pos) >> 4);
    unsigned elemN = n;
    if (elemN < extra)
    {
        // Room at the tail: move the last n elements out, then copy-backward and fill.
        char* tailPos = e - (n << 4);
        UninitCopy16((void**)&value, (void**)tailPos, (void**)e, (void**)e);
        self->mpEnd = e + (n << 4);
        DoCopyBackward16((void**)pos, (void**)tailPos, (void**)e);
        DoFill16((void**)pos, (void**)(pos + (n << 4)), value);
    }
    else
    {
        // Not enough tail elements: fill the new tail region, copy-backward the rest, fill front.
        char* newTail = e + ((n - extra) << 4);
        UninitFillN16((void**)e, n - extra, value);
        self->mpEnd = newTail;
        UninitCopy16((void**)&value, (void**)pos, (void**)e, (void**)newTail);
        self->mpEnd = newTail + (extra << 4);
        DoFill16((void**)pos, (void**)e, value);
    }
}

// @ 0x0070fb00  (vector<AutoRefCount>: insert, RC3c family)
struct VecARef {
    void** mpBegin; void** mpEnd; void** mpCap;
    void InsertA(void** pos, unsigned n, void** value);
    void InsertB(void** pos, unsigned n, void** value);
    void InsertAtom(void** pos, unsigned n, void** value);
};
void VecARef::InsertA(void** pos, unsigned n, void** value)
{
    VecARef* self = this;
    unsigned cap = (unsigned)((self->mpEnd - self->mpBegin) >> 2);
    if (cap < n)
    {
        unsigned prev = (unsigned)((self->mpEnd - self->mpBegin) >> 2);
        unsigned grow = prev ? prev * 2 : 1;
        unsigned nw = prev + n;
        if (nw < grow) nw = grow;
        void** nd = (nw == 0) ? 0 : (void**)EAlloc(nw * 4, "Graphics", 0, 0, ALLOC_FILE, 0xd1);
        void** a = (void**)MemCopyThunk(nd, self->mpBegin, (char*)pos - (char*)self->mpBegin);
        void** p = (void**)((char*)a + ((char*)pos - (char*)self->mpBegin));
        UninitFillNA2(p, n, value);
        void** p2 = (void**)MemCopyThunk(p + n, pos, (char*)self->mpEnd - (char*)pos);
        if (self->mpBegin != 0 && *(int*)((char*)self->mpBegin - 4) != 0)
            EFree(self->mpBegin);
        self->mpBegin = nd;
        self->mpEnd = p2;
        self->mpCap = nd + nw;
        return;
    }

    if (n == 0)
        return;

    // Take ownership of *value (nulling the slot) so the range ops use a stable local.
    void* v = *value;
    void** val = value;
    *val = (void*)0;
    if (v != 0)
        RefReleaseSeq(v);
    void* local = v;

    void** e = self->mpEnd;
    unsigned extra = (unsigned)((e - pos) >> 2);
    if (n < extra)
    {
        // Room past pos: shift the last n elements up by n, copy-back, then fill.
        void** dst = e - n;
        UninitCopyA2(&local, dst, e, e);
        self->mpEnd = (void**)((char*)e + (n << 2));
        CopyBackwardA(pos, dst, e);
        FillA(pos, e, &local);
    }
    else
    {
        // Not enough tail: fill new tail, copy-back the tail, fill the front.
        UninitFillNA2(e, n - extra, &local);
        void** newEnd = (void**)((char*)e + ((n - extra) << 2));
        self->mpEnd = newEnd;
        UninitCopyA2(&local, pos, e, newEnd);
        self->mpEnd = (void**)((char*)newEnd + (extra << 2));
        FillA(pos, e, &local);
    }
    if (local != 0)
        ShaderStateRelease(&local);
}

// @ 0x0070fd50  (vector<AutoRefCount>: insert, RC3b family)
void VecARef::InsertB(void** pos, unsigned n, void** value)
{
    VecARef* self = this;
    unsigned cap = (unsigned)((self->mpEnd - self->mpBegin) >> 2);
    if (cap < n)
    {
        unsigned prev = (unsigned)((self->mpEnd - self->mpBegin) >> 2);
        unsigned grow = prev ? prev * 2 : 1;
        unsigned nw = prev + n;
        if (nw < grow) nw = grow;
        void** nd = (nw == 0) ? 0 : (void**)EAlloc(nw * 4, "Graphics", 0, 0, ALLOC_FILE, 0xd1);
        void** a = (void**)MemCopyThunk(nd, self->mpBegin, (char*)pos - (char*)self->mpBegin);
        void** p = (void**)((char*)a + ((char*)pos - (char*)self->mpBegin));
        UninitFillNA2(p, n, value);
        void** p2 = (void**)MemCopyThunk(p + n, pos, (char*)self->mpEnd - (char*)pos);
        if (self->mpBegin != 0 && *(int*)((char*)self->mpBegin - 4) != 0)
            EFree(self->mpBegin);
        self->mpBegin = nd;
        self->mpEnd = p2;
        self->mpCap = nd + nw;
        return;
    }

    if (n == 0)
        return;

    void* v = *value;
    void** val = value;
    *val = (void*)0;
    if (v != 0)
        RefReleaseSeq(v);
    void* local = v;

    void** e = self->mpEnd;
    unsigned extra = (unsigned)((e - pos) >> 2);
    if (n < extra)
    {
        void** dst = e - n;
        UninitCopyA2(&local, dst, e, e);
        self->mpEnd = (void**)((char*)e + (n << 2));
        CopyBackwardB(pos, dst, e);
        FillB(pos, e, &local);
    }
    else
    {
        UninitFillNA2(e, n - extra, &local);
        void** newEnd = (void**)((char*)e + ((n - extra) << 2));
        self->mpEnd = newEnd;
        UninitCopyA2(&local, pos, e, newEnd);
        self->mpEnd = (void**)((char*)newEnd + (extra << 2));
        FillB(pos, e, &local);
    }
    if (local != 0)
        TexInstRelease(&local);
}

// @ 0x0070ffa0  (vector<AutoRefCount>: insert, atomic refcount)
void VecARef::InsertAtom(void** pos, unsigned n, void** value)
{
    VecARef* self = this;
    unsigned cap = (unsigned)((self->mpEnd - self->mpBegin) >> 2);
    if (cap < n)
    {
        unsigned prev = (unsigned)((self->mpEnd - self->mpBegin) >> 2);
        unsigned grow = prev ? prev * 2 : 1;
        unsigned nw = prev + n;
        if (nw < grow) nw = grow;
        void** nd = (nw == 0) ? 0 : (void**)EAlloc(nw * 4, "Graphics", 0, 0, ALLOC_FILE, 0xd1);
        void** a = (void**)MemCopyThunk(nd, self->mpBegin, (char*)pos - (char*)self->mpBegin);
        void** p = (void**)((char*)a + ((char*)pos - (char*)self->mpBegin));
        FillNAtomic8(p, n, value);
        void** p2 = (void**)MemCopyThunk(p + n, pos, (char*)self->mpEnd - (char*)pos);
        if (self->mpBegin != 0 && self->mpBegin != *(void***)((char*)self + 0x10))
            EFree(self->mpBegin);
        self->mpBegin = nd;
        self->mpEnd = p2;
        self->mpCap = nd + nw;
        return;
    }

    if (n == 0)
        return;

    // AddRef the incoming element (atomic at +8), then carry the raw pointer in a local.
    void* v = *value;
    *value = (void*)0;
    if (v != 0)
        _InterlockedExchangeAdd((volatile long*)((char*)v + 8), 1);
    void* local = v;

    void** e = self->mpEnd;
    unsigned extra = (unsigned)((e - pos) >> 2);
    if (n < extra)
    {
        void** dst = e - n;
        UninitCopyAtomic8(&local, dst, e, e);
        self->mpEnd = (void**)((char*)e + (n << 2));
        CopyBackwardIntrusive(pos, dst, e);
        FillAtomic8(pos, e, &local);
    }
    else
    {
        FillNAtomic8(e, n - extra, &local);
        void** newEnd = (void**)((char*)e + ((n - extra) << 2));
        self->mpEnd = newEnd;
        UninitCopyAtomic8(&local, pos, e, newEnd);
        self->mpEnd = (void**)((char*)newEnd + (extra << 2));
        FillAtomic8(pos, e, &local);
    }

    // Release the local reference (atomic at +8): decrement, then either resurrect or drop.
    if (local != 0)
    {
        volatile long* rc = (volatile long*)((char*)local + 8);
        _InterlockedExchangeAdd(rc, -1);
        const long after = *rc;
        if (after < 1)
            _InterlockedExchangeAdd(rc, 1);
        else
            _InterlockedExchangeAdd(rc, 0);
    }
}

// @ 0x0070fd00  (hash bucket-chain destructor, RC3c family)
void __stdcall HashChainDtorA(void** buckets, unsigned n)
{
    for (unsigned i = 0; i < n; i++)
    {
        HashNodeA* node = (HashNodeA*)buckets[i];
        while (node != 0)
        {
            HashNodeA* p = node;
            RC3c* ref = p->mpRef;
            node = p->mpNext;
            if (ref != 0)
                ref->Release();
            EFree(p);
        }
        buckets[i] = 0;
    }
}

// @ 0x0070ff50  (hash bucket-chain destructor, RC3b family)
void __stdcall HashChainDtorB(void** buckets, unsigned n)
{
    for (unsigned i = 0; i < n; i++)
    {
        HashNodeB* node = (HashNodeB*)buckets[i];
        while (node != 0)
        {
            HashNodeB* p = node;
            RC3b* ref = p->mpRef;
            node = p->mpNext;
            if (ref != 0)
                ref->Release();
            EFree(p);
        }
        buckets[i] = 0;
    }
}
// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct Mutex {
    void Unlock();   // 0x00922270 (equiv t2)
};
}
