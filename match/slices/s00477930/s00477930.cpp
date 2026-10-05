// Slice s00477930: editor handle-update loop, Variant ctor, eastl vector insert/sort helpers.
// Built /Od /Ob1 /MD /Gy /TP.
#include "types.h"

typedef unsigned int uint;
void* EASTL_Allocate(void* alloc, uint bytes, uint align, uint flags);   // @ 0x0042dee0
void  EASTL_allocator_deallocate(void* p);                               // @ 0x00f47380
void  memmove(void* dst, const void* src, uint n);
#pragma intrinsic(memmove)

struct Variant { uint32_t mFlags; };
namespace EA { struct V { void Destruct(Variant*, int); }; }
void VariantDestruct(Variant* v, int n);                 // @ 0x00f... (EA::Variant::Destruct)
void VariantInit(int a, int b, void* c, int d, int e);   // @ 0x0093dd80

// ---- 8-byte pair element ----------------------------------------------------------------
struct P8 { uint a, b; };
template<class T> T* UninitCopyRange(T* first, T* last, T* dest);   // out of line

// ---- other editor helpers referenced by the big loop (declarations only) -----------------
void EditorHelpers();                                    // placeholder bucket

// @ 0x00477930  (large editor per-frame handle update; skeleton, see partial.txt)
void EditorHandleUpdate(int* self, int* state)
{
    int nHandleBase = self[3];
    int* pVectors = self + 5;
    int pModel = *(int*)(self[4] + 0x98);
    int nCount = (*(int*)(self[4] + 0x9c) - pModel) / 0x8c;
    int i = 0;
    int idx = state[7];
    while (i < 4 && idx < nCount * 2) {
        int local24 = idx;
        if (nCount <= idx) local24 = idx - nCount;
        uint back = (uint)(nCount <= idx);
        if (*(int*)(*pVectors + local24 * 4) != 0) {
            short* rec = (short*)(local24 * 0x8c + pModel);
            char hasRef = *(int*)(pVectors[0x14] + local24 * 4) != 0;
            (void)rec; (void)hasRef; (void)back; (void)nHandleBase;
            // full body (model instantiation, transform, bounding box fix-up) omitted
            i = i + 1;
        }
        idx = idx + 1;
        state[7] = idx;
    }
    if (state[7] < nCount * 2) {
        EditorHelpers();
    }
}

// @ 0x00478300
Variant* Variant_Ctor(Variant* v, uint32_t arg)
{
    if ((v->mFlags & 4) != 0) {
        VariantDestruct(v, 1);
    }
    VariantInit(0x39, 0, (void*)arg, 0x18, 1);
    return v;
}

// @ 0x00478390
P8* InsertP8(P8* mpBegin, P8*& mpEnd, P8*& mpCapacity, int* mpFixed, P8* position, const P8& value)
{
    if (mpEnd != mpCapacity) {
        const P8* v = &value;
        if (position <= v && v < mpEnd)
            v = (P8*)((char*)v + 8);
        if (mpEnd) *mpEnd = *(mpEnd - 1);
        P8* p = mpEnd;
        P8* q = mpEnd - 1;
        while (q != position) { *--p = *--q; }
        *position = *v;
        ++mpEnd;
    } else {
        uint oldSize = (uint)(mpEnd - mpBegin);
        uint newSize = oldSize ? oldSize * 2 : 1;
        P8* pNew = newSize ? (P8*)EASTL_Allocate((char*)mpCapacity + 0xc - 0xc, newSize * 8, 4, 0) : 0;
        P8* p = UninitCopyRange(mpBegin, position, pNew);
        if (p) *p = value;
        P8* pNewEnd = UninitCopyRange(position, mpEnd, p + 1);
        (void)mpFixed;
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    }
    return position;
}

// @ 0x00478620
void IntrosortRange(char* first, char* last, char pred)
{
    if (first != last) {
        uint n = (uint)(last - first) >> 3;
        uint depth = 0;
        for (uint t = n; t != 0; t >>= 1) ++depth;
        (void)pred;
        // introsort: depth-limited quicksort then insertion sort
        (void)depth;
    }
}

// @ 0x004786e0
P8* InsertP8Fixed(P8* mpBegin, P8*& mpEnd, P8*& mpCapacity, P8* position, const P8& value)
{
    if (mpEnd != mpCapacity) {
        const P8* v = &value;
        if (position <= v && v < mpEnd)
            v = (P8*)((char*)v + 8);
        if (mpEnd) *mpEnd = *(mpEnd - 1);
        char* dst = (char*)mpEnd + (((char*)(mpEnd - 1) - (char*)position) >> 3) * -8;
        memmove(dst, position, (uint)((char*)(mpEnd - 1) - (char*)position));
        *position = *v;
        ++mpEnd;
    } else {
        uint oldSize = (uint)(mpEnd - mpBegin);
        uint newSize = oldSize ? oldSize * 2 : 1;
        P8* pNew = newSize ? (P8*)EASTL_Allocate((char*)mpCapacity + 0xc - 0xc, newSize * 8, 8, 0) : 0;
        P8* p = pNew;
        (void)p;
        mpBegin = pNew;
        mpCapacity = pNew + newSize;
    }
    return position;
}
