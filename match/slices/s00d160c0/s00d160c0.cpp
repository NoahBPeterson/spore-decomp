// Slice s00d160c0 - SporeApp 0x00d160c0..0x00d16eb0
// Gameplay-marker UI helpers plus the string-comparator sort template helpers.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;

// ---------------------------------------------------------------------------------------------
// Support types
// ---------------------------------------------------------------------------------------------
// 3-dword vector used by SetPlanet.
struct cVec3i {
    int x;                              // 0x00
    int y;                              // 0x04
    int z;                              // 0x08
};

// eastl-style wide string: begin / end / capacity + one trailing field.
struct cWString {
    void* mpBegin;                      // 0x00
    void* mpEnd;                        // 0x04
    void* mpCap;                        // 0x08
    void* mpField0c;                    // 0x0c
};

// 3-dword value handed to the locale converter (value + two tags).
struct cConvertArg {
    void* mpValue;                      // 0x00
    void* mpTag04;                      // 0x04
    void* mpScratch08;                  // 0x08
};

// Stateful compare functor: keeps a converter object and two scratch strings.
// The two compared values are formatted into the scratch strings, which are
// then compared lexicographically.
struct cStrCmp {
    void*    mpField00;                 // 0x00
    void*    mpConv04;                  // 0x04
    cWString mStr08;                    // 0x08
    cWString mStr18;                    // 0x18

    bool operator()(u32 a, u32 b);      // 0x00d16760
};

struct cGameEditInputStrategy;

// ---------------------------------------------------------------------------------------------
// External helpers implemented in other slices.
// ---------------------------------------------------------------------------------------------
void __fastcall cStrCmp_Destroy(cStrCmp* p);                                   // 0x00d167e0
int  __cdecl StringCompare(const void* b1, const void* e1,
                           const void* b2, const void* e2);                    // 0x00576970
void* __cdecl ObjectError();                                                   // 0x008de1a0
void __cdecl operator delete[](void* p);                                       // 0x00f47380

// vtable dispatch helpers, one per slot used by this slice.
static inline void VT_7C_2(void* p, void* a, void* b)
{
    ((void (__thiscall*)(void*, void*, void*))(*(void***)p)[0x1f])(p, a, b);
}
static inline void VT_60_1(void* p, void* a, int b)
{
    ((void (__thiscall*)(void*, void*, int))(*(void***)p)[0x18])(p, a, b);
}

// Frees both scratch strings of a comparator held by value (the code the
// compiler emits for the inlined destructor).
static inline void cStrCmp_FreeStrings(cStrCmp& comp)
{
    if ((int)(((char*)comp.mStr18.mpCap - (char*)comp.mStr18.mpBegin) & 0xfffffffe) > 2
        && comp.mStr18.mpBegin != 0)
        operator delete[](comp.mStr18.mpBegin);
    if ((int)(((char*)comp.mStr08.mpCap - (char*)comp.mStr08.mpBegin) & 0xfffffffe) > 2
        && comp.mStr08.mpBegin != 0)
        operator delete[](comp.mStr08.mpBegin);
}

// ---------------------------------------------------------------------------------------------
// SP::cGameEditInputStrategy
// ---------------------------------------------------------------------------------------------
struct cGameEditInputStrategy {
    u8      mPad0000[0x7c];
    void*   mpField7c;                  // 0x7c  planet-name text edit object
    u8      mPad0080[0xf8 - 0x80];
    cVec3i  mPlanetF8;                  // 0xf8  selected planet

    void SetPlanet(const cVec3i* planet);   // 0x00d16b90
};

// ---------------------------------------------------------------------------------------------
// Definitions
// ---------------------------------------------------------------------------------------------
// @ 0x00d167e0
// Releases both scratch strings of the compare functor.
void __fastcall cStrCmp_Destroy(cStrCmp* p)
{
    if ((int)(((char*)p->mStr18.mpCap - (char*)p->mStr18.mpBegin) & 0xfffffffe) > 2
        && p->mStr18.mpBegin != 0)
        operator delete[](p->mStr18.mpBegin);
    if ((int)(((char*)p->mStr08.mpCap - (char*)p->mStr08.mpBegin) & 0xfffffffe) > 2
        && p->mStr08.mpBegin != 0)
        operator delete[](p->mStr08.mpBegin);
}

// @ 0x00d16760
// Formats both values through the converter, then compares the two strings.
bool cStrCmp::operator()(u32 a, u32 b)
{
    cWString& strA = mStr08;
    cWString& strB = mStr18;
    cConvertArg argA = { (void*)a, (void*)0x00b1b104, mpField00 };
    cConvertArg argB = { (void*)b, (void*)0x00b1b104, mpField00 };
    VT_7C_2(mpConv04, &argA, &strA);
    VT_7C_2(mpConv04, &argB, &strB);
    return StringCompare(strA.mpBegin, strA.mpEnd, strB.mpBegin, strB.mpEnd) < 0;
}

// @ 0x00d16b90
// Stores the selected planet and pushes its name into the planet-name edit.
void cGameEditInputStrategy::SetPlanet(const cVec3i* planet)
{
    mPlanetF8 = *planet;
    if (mpField7c != 0) {
        cWString str;
        str.mpBegin = (void*)0x01667bac;
        str.mpEnd = (void*)0x01667bac;
        str.mpCap = (void*)0x01667bae;
        if (planet->y != 0)
            VT_7C_2(ObjectError(), (void*)planet, &str);
        VT_60_1(mpField7c, str.mpBegin, 0);
        if ((int)(((char*)str.mpCap - (char*)str.mpBegin) & 0xfffffffe) > 2
            && str.mpBegin != 0)
            operator delete[](str.mpBegin);
    }
}

// @ 0x00d16c30
// Insertion sort over 4-byte elements using the string comparator.
void SortInsertBounded(u32* first, u32* last, cStrCmp comp)
{
    if (first != last) {
        for (u32* i = first + 1; i != last; ++i) {
            u32 value = *i;
            u32* j = i;
            while (j != first && comp(value, j[-1])) {
                *j = j[-1];
                --j;
            }
            *j = value;
        }
    }
    cStrCmp_FreeStrings(comp);
}

// @ 0x00d16cc0
// Insertion sort variant without the lower bound check.
void SortInsert(u32* first, u32* last, cStrCmp comp)
{
    for (u32* i = first; i != last; ++i) {
        u32 value = *i;
        u32* dst = i;
        u32* src = i - 1;
        while (comp(value, *src)) {
            *dst = *src;
            --dst;
            --src;
        }
        *dst = value;
    }
    cStrCmp_FreeStrings(comp);
}

// @ 0x00d16d60
// Median-of-three: returns the pointer whose element sorts in the middle.
u32* Median3(u32* a, u32* b, u32* c, cStrCmp comp)
{
    if (comp(*a, *b)) {
        if (comp(*b, *c)) {
            cStrCmp_Destroy(&comp);
            return b;
        }
        if (comp(*a, *c)) {
            cStrCmp_Destroy(&comp);
            return c;
        }
        cStrCmp_Destroy(&comp);
        return a;
    } else {
        if (comp(*a, *c)) {
            cStrCmp_Destroy(&comp);
            return a;
        }
        if (!comp(*b, *c)) {
            cStrCmp_Destroy(&comp);
            return b;
        }
        cStrCmp_Destroy(&comp);
        return c;
    }
}

// @ 0x00d16e00
// Hoare partition around the pivot value; returns the split point.
u32* Partition(u32* first, u32* last, u32 pivot, cStrCmp comp)
{
    for (;;) {
        while (comp(*first, pivot))
            ++first;
        while (comp(pivot, *--last))
            ;
        if (first >= last)
            break;
        u32 tmp = *first;
        *first = *last;
        *last = tmp;
        ++first;
    }
    cStrCmp_FreeStrings(comp);
    return first;
}

// @ 0x00d16eb0
// Heap sift-up: moves `value` towards the root of the heap stored in `arr`.
void SiftUp(u32* arr, int start, int pos, u32 value, cStrCmp comp)
{
    int parent = (pos - 1) >> 1;
    while (pos > start) {
        if (!comp(arr[parent], value))
            break;
        arr[pos] = arr[parent];
        pos = parent;
        parent = (parent - 1) >> 1;
    }
    arr[pos] = value;
    cStrCmp_FreeStrings(comp);
}
