// Slice s0070efa0: SP::cMaterialManager shader IO + eastl container/refcount helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

void* __cdecl EAlloc(size_t n, const char* name, int a, unsigned b, const char* file, int line); // 0x00f473a0
void  __cdecl EFree(void* p);                                                                    // 0x00f47380

struct RC3c { void AddRef(); void Release(); };  // refcount at +0x3c
struct RC3b { void AddRef(); void Release(); };  // refcount at +0x3c (second family)

// assign forward: *dst = *src with AddRef/Release (matches AssignCopyA in slice 45)
void** AssignCopyA(void** first, void** last, void** dst);
void** AssignCopyB(void** first, void** last, void** dst);
void __stdcall RangeAtomic8Release(void** first, void** last);

// @ 0x0070f320  (vector<AutoRefCount<RC3c>> storage teardown)
struct VecA { void** mpBegin; void** mpEnd; void** mpCap; };
void VecA_Teardown(VecA* self)
{
    void** first = self->mpBegin;
    void** last = self->mpEnd;
    for (; first < last; ++first)
    {
        if (*first != 0)
            ((RC3c*)*first)->Release();
    }
    void* p = self->mpBegin;
    if ((p != 0) && (*(int*)((char*)p - 4) != 0))
        EFree(p);
}

// @ 0x0070f390  (vector<AutoRefCount<RC3b>> storage teardown)
void VecB_Teardown(VecA* self)
{
    void** first = self->mpBegin;
    void** last = self->mpEnd;
    for (; first < last; ++first)
    {
        if (*first != 0)
            ((RC3b*)*first)->Release();
    }
    void* p = self->mpBegin;
    if ((p != 0) && (*(int*)((char*)p - 4) != 0))
        EFree(p);
}

// @ 0x0070f570
void FillWeak14N(void** dst, unsigned n, void** value)
{
    for (; n != 0; --n)
    {
        if (dst != 0)
        {
            void* p = *value;
            *dst = p;
            if (p != 0)
                ++*(int*)((char*)p + 0x14);
        }
        ++dst;
    }
}

// @ 0x0070f660
struct FVecA { void** mpBegin; void** mpEnd; void** mpCap; void** mpAllocName; void** mp16; };
void FVecA_Teardown(FVecA* self)
{
    RangeAtomic8Release(self->mpBegin, self->mpEnd);
    void* p = self->mpBegin;
    if ((p != 0) && (p != *(void**)((char*)self + 0x10)))
        EFree(p);
}

// @ 0x0070f890
struct FVecB { char _p[0x20]; void** mpBegin; void** mpEnd; char _q[8]; void** mpAllocName; };
void FVecB_Teardown(FVecB* self)
{
    RangeAtomic8Release(self->mpBegin, self->mpEnd);
    void* p = self->mpBegin;
    if ((p != 0) && (p != *(void**)((char*)self + 0x30)))
        EFree(p);
}

// @ 0x0070fa30
struct FVecC { char _p[0x24]; void** mpBegin; void** mpEnd; char _q[8]; void** mpAllocName; };
void FVecC_Teardown(FVecC* self)
{
    RangeAtomic8Release(self->mpBegin, self->mpEnd);
    void* p = self->mpBegin;
    if ((p != 0) && (p != *(void**)((char*)self + 0x34)))
        EFree(p);
}

// @ 0x0070fa60
void VecA_Shrink(VecA* self, void** arg1, void** arg2)
{
    void** p = AssignCopyA(arg1, self->mpEnd, arg2);
    void** end = self->mpEnd;
    for (; p < end; ++p)
    {
        if (*p != 0)
            ((RC3c*)*p)->Release();
    }
    self->mpEnd = (void**)((char*)self->mpEnd + ((char*)arg2 - (char*)arg1));
}

// @ 0x0070fab0
void VecB_Shrink(VecA* self, void** arg1, void** arg2)
{
    void** p = AssignCopyB(arg1, self->mpEnd, arg2);
    void** end = self->mpEnd;
    for (; p < end; ++p)
    {
        if (*p != 0)
            ((RC3b*)*p)->Release();
    }
    self->mpEnd = (void**)((char*)self->mpEnd + ((char*)arg2 - (char*)arg1));
}

// @ 0x0070fd00  (hash bucket-chain destructor, RC3c family)
void __stdcall HashChainDtorA(void** buckets, unsigned n)
{
    for (unsigned i = 0; i < n; i++)
    {
        void* node = buckets[i];
        while (node != 0)
        {
            void* next = *(void**)((char*)node + 8);
            void* ref = *(void**)((char*)node + 4);
            if (ref != 0)
                ((RC3c*)ref)->Release();
            EFree(node);
            node = next;
        }
        buckets[i] = 0;
    }
}

// @ 0x0070ff50  (hash bucket-chain destructor, RC3b family)
void __stdcall HashChainDtorB(void** buckets, unsigned n)
{
    for (unsigned i = 0; i < n; i++)
    {
        void* node = buckets[i];
        while (node != 0)
        {
            void* next = *(void**)((char*)node + 8);
            void* ref = *(void**)((char*)node + 4);
            if (ref != 0)
                ((RC3b*)ref)->Release();
            EFree(node);
            node = next;
        }
        buckets[i] = 0;
    }
}
