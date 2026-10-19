// Slice s006f1770 — SP::cEffectsRenderer particle-set / hash-table helpers.
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE.
#include "types.h"
#include <intrin.h>
#include <new>

extern "C" void FUN_00a7bca0(int, int);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* EAAllocate(unsigned int n, const char* name, int flags, int align, const char* file, int line); // 0x00f473a0

struct IVt {
    virtual void v0(int);
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

// A richer interface used via raw vtable slot indices.
struct IVt2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual bool s9(unsigned key);
};

// An object with >= 11 virtual slots (used via raw indices).
struct IVt3 {
    virtual void t0(); virtual void t1(); virtual void t2(); virtual void t3();
    virtual void t4(); virtual void t5(); virtual void t6(); virtual void t7();
    virtual void t8(); virtual void t9();
    virtual void* slot10(unsigned key);
};

// eastl hashtable<unsigned, value> (out-of-line find at 0x00685f30, VSIZE 12).
struct HtValue { unsigned first; unsigned pad[2]; };
struct HtNode  { HtValue mValue; HtNode* mpNext; };
struct HtIter  { HtNode* node; HtNode** bucket; };
struct HtTable {
    unsigned   mFunctors;         // +0x00
    HtNode**   mBuckets;          // +0x04
    unsigned   mBucketCount;      // +0x08
    unsigned   mElementCount;     // +0x0c
    HtIter find(const unsigned& key);   // 0x00685f30 thiscall, sret, ret 8
};

struct HtOwner {
    void* FindEntry(unsigned key, unsigned a);    // 0x006f2050
    int   ContainsKey(unsigned key);              // 0x006f2000
    int   ClassifyVertexDesc(unsigned a, unsigned b, unsigned c);  // 0x006f1f20
};

// A vertex-descriptor stream entry and its owning descriptor.
struct VdStream { int type; int a; int b; };
struct VtxDesc  { char pad[0xc]; unsigned short count; char pad2[0x20 - 0xe]; VdStream streams[]; };
struct VdState  { VtxDesc* GetVertexDescriptor(); };   // 0x011edcd0 thiscall (ecx = state)

// ---- particle-set storage (slice 006f1770) ---------------------------------
// Each particle-set entry is 0xC0 bytes; entries 4..8 hold a wide-string view.
struct PSetElem {
    int      f00;                 // +0x00
    wchar_t* mStrBegin;           // +0x04
    wchar_t* mStrEnd;             // +0x08
    char     pad0c[0xa0 - 0x0c];
    int      ma0;                 // +0xa0
    int      ma4;                 // +0xa4
    float    ma8;                 // +0xa8
    char     padac[0xc0 - 0xac];
};
struct PSetVec {                  // +0x224
    PSetElem* begin; PSetElem* end; PSetElem* cap;
    void PushBack();              // 0x006f16c0 thiscall
};
struct IndexVec {                 // +0x238
    int* begin; int* end; int* cap;
};
void FUN_006ebd20(const wchar_t* name, const wchar_t* end);  // 0x006ebd20 string assign

struct PSetOwner {
    char     pad0[0x224];
    PSetVec  mVec;                // +0x224
    char     pad22c[0x238 - 0x230];
    IndexVec mFree;               // +0x238
    bool AddParticleSet(wchar_t* name, int b, int c, float d, unsigned* out); // 0x006f1770
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
bool PSetOwner::AddParticleSet(wchar_t* name, int b, int c, float d, unsigned* out)
{
    if (mFree.begin != mFree.end)
    {
        *out = (unsigned)mFree.end[-1];
        mFree.end -= 1;
    }
    else
    {
        *out = (int)(mVec.end - mVec.begin);
        mVec.PushBack();
    }
    PSetElem* e = &mVec.begin[*out];
    if (e->mStrBegin != name)
    {
        if (e->mStrBegin != e->mStrEnd)
        {
            e->mStrBegin[0] = 0;
            e->mStrEnd = e->mStrBegin;
        }
        const wchar_t* p = name;
        while (*p) p++;
        FUN_006ebd20(name, p);
    }
    e->ma0 = b;
    e->ma4 = c;
    e->ma8 = d;
    return true;
}

// @ 0x006f1860
bool ResourceInfoInit()
{ return true; }

// @ 0x006f1a30
void* __stdcall Alloc18(void* src)
{
    char* p = (char*)EAAllocate(0x18, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (p)
    {
        int* s = (int*)src;
        *(int*)(p + 0)  = s[0];
        *(int*)(p + 4)  = s[1];
        int c = s[2];
        *(int*)(p + 8)  = c;
        if (c)
            (*(void (__thiscall**)(void*))c)((void*)c);   // vt[0]()
    }
    *(int*)(p + 0x10) = 0;
    return p;
}
// @ 0x006f1b60
bool LookupAndUse(int, int, int, int)
{ return false; }

// @ 0x006f1c40
bool CreateResource(int, int)
{ return false; }

// @ 0x006f1df0
void __fastcall ReleaseAt4(int* self)
{
    int* p = (int*)self[1];
    if (!p) return;
    long n = _InterlockedDecrement((volatile long*)(p + 1));
    if (n == 0)
    {
        _InterlockedExchange((volatile long*)(p + 1), 1);
        if (p)
            ((IVt*)p)->v0(1);
    }
}

// @ 0x006f1e20
void __fastcall ReleaseAt8(int* self)
{
    int* p = (int*)self[2];
    if (!p) return;
    long n = _InterlockedDecrement((volatile long*)(p + 1));
    if (n == 0)
    {
        _InterlockedExchange((volatile long*)(p + 1), 1);
        if (p)
            ((IVt*)p)->v0(1);
    }
}

// @ 0x006f1f20
int HtOwner::ClassifyVertexDesc(unsigned a, unsigned b, unsigned c)
{
    if (a) return a;
    char* s = (char*)this;
    HtTable* t = (HtTable*)(s + 0x88);
    HtNode* end = t->mBuckets[t->mBucketCount];
    HtIter it = t->find(b);
    void* v;
    if (it.node != end)
        v = *(void**)((char*)it.node + 4);
    else
        v = ((IVt3*)*(void**)(s + 0x58))->slot10(b);
    if (!v) return a;
    void* st = *(void**)((char*)v + 4);
    if ((*(unsigned*)((char*)st + 8) & 0x100000) == 0) return a;

    const VtxDesc* vd = ((VdState*)st)->GetVertexDescriptor();
    int n = vd->count;
    char has2 = 0, has13 = 0, has5 = 0;
    for (int i = 0; i < n; i++)
    {
        int ty = vd->streams[i].type;
        if (ty == 2) has2 = 1;
        if (ty == 0x13) has13 = 1;
        else if (ty == 5) has5 = 1;
    }
    if (!has2) return a;
    if (!has5) return 2;
    return (has13 ? 1 : 0) + 3;
}

// @ 0x006f2050
void* HtOwner::FindEntry(unsigned key, unsigned)
{
    HtTable* t = (HtTable*)((char*)this + 0x88);
    unsigned k = key;
    HtIter it = t->find(k);
    if (it.node != t->mBuckets[t->mBucketCount])
        return (char*)it.node + 4;
    return 0;
}

// @ 0x006f2000
int HtOwner::ContainsKey(unsigned key)
{
    char* s = (char*)this;
    HtTable* t = (HtTable*)(s + 0x3c);
    HtNode* end = t->mBuckets[*(unsigned*)(s + 0x44)];
    if (t->find(key).node != end)
        goto yes;
    if (!((IVt2*)*(void**)(s + 0xc))->s9(key))
        return 0;
yes:
    return 1;
}
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
                p->v0(1);
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
