// Slice s006f1770 — SP::cEffectsRenderer particle-set / hash-table helpers.
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE.
#include "types.h"
#include <intrin.h>
#include <new>

extern "C" void FUN_00a7bca0(int, int);
extern "C" void EASTL_allocator_deallocate(void* p);

struct IVt {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

// ---- 0x006f1840 -------------------------------------------------------------
// @ 0x006f1840
void __stdcall Forward1840(int a, int b)
{
    FUN_00a7bca0(a, b);
}

// ---- 0x006f1950 -------------------------------------------------------------
// @ 0x006f1950
struct VtStub1950 {
    virtual void v0();
    virtual int  v1(int, int, int);
};
struct Owner1950 {
    char pad0[0x60];
    VtStub1950** mArray;   // +0x60
    int Call(int idx, int a, int b, int c);
};
// @ 0x006f1950
int Owner1950::Call(int idx, int a, int b, int c)
{
    mArray[idx]->v1(a, b, c);
    return 1;
}

// ---- remaining functions (skeletons / approximate) -------------------------

// @ 0x006f1770
bool AddParticleSet(int a, int b, int c, int d)
{ (void)a; (void)b; (void)c; (void)d; return true; }

// @ 0x006f1860
bool ResourceInfoInit()
{ return true; }

// @ 0x006f1a30
void* Alloc18(void* p)
{ (void)p; return 0; }

// @ 0x006f1b60
bool LookupAndUse(int, int, int, int)
{ return false; }

// @ 0x006f1c40
bool CreateResource(int, int)
{ return false; }

// @ 0x006f1df0
void ReleaseAt4(int* self)
{ (void)self; }

// @ 0x006f1e20
void ReleaseAt8(int* self)
{ (void)self; }

// @ 0x006f1f20
int ClassifyVertexDesc(int, int, int)
{ return 0; }

// @ 0x006f2000
bool ContainsKey(int, void*)
{ return true; }

// @ 0x006f2050
int FindEntry(int, void*)
{ return 0; }

// @ 0x006f20a0
void* Alloc10(void* p)
{ (void)p; return 0; }

// @ 0x006f20f0
int FindOrInsert(int, void*)
{ return 0; }

// @ 0x006f2270
struct HashNode {
    char pad0[8];
    IVt* mpAt8;      // +0x08
    void* pC;        // +0x0c
    HashNode* mpNext;// +0x10
};
// @ 0x006f2270
void __stdcall FreeBucketList(HashNode** table, unsigned int count)
{
    for (unsigned int i = 0; i < count; ++i) {
        HashNode* n = table[i];
        while (n) {
            HashNode* next = n->mpNext;
            IVt* p = n->mpAt8;
            if (p)
                p->v0();
            EASTL_allocator_deallocate(n);
            n = next;
        }
        table[i] = 0;
    }
}

// Fixed-capacity vector with an inline push_back (slow path out of line), as EASTL.
template<class T>
struct evec2 {
    T* mpBegin; T* mpEnd; T* mpCapacity; char mAllocator[4];
    void push_back(const T& v) { if (mpEnd < mpCapacity) ::new(mpEnd++) T(v); else DoInsertValue(mpEnd, v); }
    void DoInsertValue(T* pos, const T& v);
};

struct Owner23d0 {
    char pad0[0x60];
    IVt** mpAt60;    // +0x60
    IVt** mpAt64;    // +0x64
    char pad1[0x74 - 0x68];
    evec2<int> mVec74;   // +0x74
    void Remove(int index);
};
// @ 0x006f23d0
void Owner23d0::Remove(int index)
{
    if (index < 0)
        return;
    if (index >= (int)(mpAt64 - mpAt60))
        return;
    mVec74.push_back(index);
    mpAt60[index]->v3();
    mpAt60[index] = 0;
}

// @ 0x006f2310
bool InsertEntry(int, unsigned int, unsigned int, int*)
{ return false; }

// @ 0x006f2430
void FreeBucketList2(void* table, unsigned int n)
{ (void)table; (void)n; }

// @ 0x006f24a0
void AssignByKey(unsigned int key, int* val)
{ (void)key; (void)val; }

// @ 0x006f2510
int FindOrInsert2(int, void*)
{ return 0; }

// @ 0x006f2620
bool ClearAll()
{ return true; }
