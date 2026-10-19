// Slice s0056fb90: SP::Traits cRigBlockTag BlockKey/vector_set hashtable helpers.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <new>

typedef unsigned int size_t;
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

extern "C" void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                                          const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);

// ---------------------------------------------------------------- hashtable/vector helpers
// ---------------------------------------------------------------- vector<12-byte POD>::DoAssign
struct Vec12 { uint32_t a, b, c; };
struct Vec12Alloc {
    uint32_t mpName;
    void deallocate(void* p, uint32_t n) { void* q = p; EASTL_allocator_deallocate(q); }
};
struct FalseTag { FalseTag() {} };
Vec12* UninitCopy12(const Vec12* first, const Vec12* last, Vec12* dst);        // 0x00475ef0 (cdecl)
inline Vec12* CopyImpl12(const Vec12* first, const Vec12* last, Vec12* result)
{
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}
inline Vec12* Copy12(const Vec12* first, const Vec12* last, Vec12* result)
{
    const bool bA = false, bC = false, bB = false;
    return CopyImpl12(first, last, result);
}
struct Vec12Vector {
    Vec12* mpBegin;                     // +0
    Vec12* mpEnd;                       // +4
    Vec12* mpCapacity;                  // +8
    Vec12Alloc mAllocator;              // +0xc
    Vec12* DoRealloc(uint32_t n, const Vec12* first, const Vec12* last);   // 0x00475fa0 (thiscall, ret 0xc)
    void DoFree(Vec12* p, uint32_t n)
    {
        if (p && ((int*)p)[-1] != 0)
            mAllocator.deallocate(p, n * sizeof(Vec12));
    }
    void DestroyFrom(Vec12* first)
    {
        for (Vec12* p = first; p < mpEnd; ++p)
            ;
    }
    void DoAssign(const Vec12* first, const Vec12* last, const FalseTag& tag);
};
// @ 0x0056fee0
void Vec12Vector::DoAssign(const Vec12* first, const Vec12* last, const FalseTag& tag)
{
    const uint32_t n = (uint32_t)(last - first);
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        Vec12* const pNewData = DoRealloc(n, first, last);
        ScratchSlots<10>();
        DestroyFrom(mpBegin);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = mpBegin + n;
        mpCapacity = mpEnd;
    }
    else if (n <= (uint32_t)(mpEnd - mpBegin)) {
        Vec12* const pNewEnd = Copy12(first, last, mpBegin);
        DestroyFrom(pNewEnd);
        mpEnd = pNewEnd;
    }
    else {
        const Vec12* const pMid = first + (mpEnd - mpBegin);
        Copy12(first, pMid, mpBegin);
        mpEnd = UninitCopy12(pMid, last, mpEnd);
        ScratchSlots<12>();
    }
}

struct Key { uint32_t a; uint32_t b; };
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void assign(wchar_t* p, wchar_t* q);   // @ 0x00423650
};
struct StreamMeta {
    float f;                               // +0
    WStr str;                              // +4
    StreamMeta(const StreamMeta& s) { f = s.f; if (&str != &s.str) str.assign(s.str.mpBegin, s.str.mpEnd); }
};
struct StreamElem {
    Key key;                               // +0
    StreamMeta meta;                       // +8   (size 0x1c)
    StreamElem(const StreamElem& src);     // @ 0x00570140
};

StreamElem::StreamElem(const StreamElem& src) : key(src.key), meta(src.meta)
{
}

// ---------------------------------------------------------------- vector<StreamElem>::DoInsertValue
struct Str16 {                          // eastl::basic_string<wchar_t> (16 bytes with allocator)
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAlloc;
    Str16(const Str16& x);              // 0x0056e2d0
};
struct MetaI {                          // float weight + description string
    float f;
    Str16 str;
    MetaI(const MetaI& s) : f(s.f), str(s.str) {}
};
struct MetaO {                          // same layout; copy ctor is the out-of-line one
    float f;
    Str16 str;
    MetaO(const MetaO& s);              // 0x0056b020 (thiscall, ret 4)
};
struct ElemO {
    Key key;
    MetaO meta;
    ElemO(const ElemO& s) : key(s.key), meta(s.meta) {}
};
struct ElemI {                          // 0x1c-byte vector element
    Key key;                            // +0
    MetaI meta;                         // +8
    ElemI(const ElemI& s) : key(s.key), meta(s.meta) {}
    ElemI& operator=(const ElemI& s);   // 0x00570140 (assign)
};
ElemI* UninitCopy(ElemI* first, ElemI* last, ElemI* dst);                 // 0x00570330 (cdecl)
inline ElemI* CopyBackwardImpl(ElemI* first, ElemI* last, ElemI* result)
{
    while (last != first)
        *--result = *--last;
    return result;
}
inline ElemI* CopyBackward(ElemI* first, ElemI* last, ElemI* result)
{
    const bool bA = false, bC = false, bB = false;
    ScratchSlots<4>();
    return CopyBackwardImpl(first, last, result);
}
struct ElemAlloc {
    uint32_t mpName;
    void deallocate(void* p, uint32_t n) { void* q = p; EASTL_allocator_deallocate(q); }
};
struct ElemVec {
    ElemI* mpBegin;                     // +0
    ElemI* mpEnd;                       // +4
    ElemI* mpCapacity;                  // +8
    ElemAlloc mAllocator;               // +0xc
    ElemI* DoAllocate(uint32_t n)
    {
        return n ? (ElemI*)EASTL_Allocate(&mAllocator, n * sizeof(ElemI), 4, 0) : 0;
    }
    void DoFree(ElemI* p, uint32_t n)
    {
        if (p)
            mAllocator.deallocate(p, n * sizeof(ElemI));
    }
    void DoInsertValue(ElemI* position, const ElemI& value);
};
// @ 0x0056fb90
void ElemVec::DoInsertValue(ElemI* position, const ElemI& value)
{
    if (mpEnd != mpCapacity) {
        const ElemI* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) ElemI(*(mpEnd - 1));
        CopyBackward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    }
    else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        ElemI* const pNewData = DoAllocate(nNewSize);
        ElemI* pNewEnd = UninitCopy(mpBegin, position, pNewData);
        ::new(pNewEnd) ElemO(*(const ElemO*)&value);
        pNewEnd = UninitCopy(position, mpEnd, ++pNewEnd);
        ScratchSlots<28>();
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}


struct Pair8 { uint32_t a; uint32_t b; };
inline bool LessU32(uint32_t a, uint32_t b) { return a < b; }
Pair8* LowerBoundPair(Pair8* first, Pair8* last, const Pair8* key);   // @ 0x005701b0
Pair8* LowerBoundPair(Pair8* first, Pair8* last, const Pair8* key)
{
    int n = (int)(last - first);
    ScratchSlots<1>();
    while (n > 0) {
        Pair8* it = first;
        int half = n >> 1;
        it = it + half;
        if (LessU32(it->a, key->a)) {
            it = it + 1;
            first = it;
            n = n - (half + 1);
        }
        else {
            n = half;
        }
    }
    return first;
}

struct Key1c { uint32_t a; uint32_t b; };
struct Elem1c {
    char pad[0x1c];
    bool operator<(const Key1c& k) const;   // @ 0x005715d0
};
Elem1c* LowerBound1c(Elem1c* first, Elem1c* last, Key1c* key);        // @ 0x0056fe60
Elem1c* LowerBound1c(Elem1c* first, Elem1c* last, Key1c* key)
{
    // Names chosen from od_names.py fit 5 to reproduce the original /Od slot order.
    int it = (int)((char*)last - (char*)first) / 0x1c;
    ScratchSlots<1>();
    while (it > 0) {
        Elem1c* n28 = first;
        int v13 = it >> 1;
        n28 = n28 + v13;
        Elem1c* v28 = n28;
        if ((*v28).operator<(*key)) {
            n28 = n28 + 1;
            first = n28;
            it = it - (v13 + 1);
        }
        else {
            it = v13;
        }
    }
    return first;
}

// hashtable<BlockKey, pair<const BlockKey, vector_set<uint>>>::DoFreeNodes
struct OuterVec {                       // eastl::vector<pair<uint, vector_set<uint>>>
    void* mpBegin; void* mpEnd; void* mpCapacity; uint32_t mAlloc;
    void DoDestroyValues();             // 0x00553fb0
};
struct HashNode {
    Key mKey;                           // +0
    OuterVec mValue;                    // +8
    char pad18[8];                      // +0x18
    HashNode* mpNext;                   // +0x20
    ~HashNode() { mValue.DoDestroyValues(); }
};
struct NodeAlloc {
    void deallocate(void* p, uint32_t n) { void* q = p; EASTL_allocator_deallocate(q); }
};
struct HashTable {
    NodeAlloc mAllocator;
    void DoFreeNode(HashNode* pNode)
    {
        pNode->~HashNode();
        ScratchSlots<4>();
        mAllocator.deallocate(pNode, sizeof(HashNode));
    }
    void DoFreeNodes(HashNode** pNodeArray, uint32_t n);
};
// @ 0x00570230
void HashTable::DoFreeNodes(HashNode** pNodeArray, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        HashNode* pNode = pNodeArray[i];
        while (pNode) {
            HashNode* pTempNode = pNode;
            pNode = pNode->mpNext;
            DoFreeNode(pTempNode);
        }
        pNodeArray[i] = 0;
    }
}

void* MoveDestroyRange(void* first, void* last, void* dst);           // @ 0x005702c0
void* MoveDestroyRange(void* first, void* last, void* dst)
{
    void* r = 0;
    for (char* p = (char*)first; p != last; p += 0x1c)
        dst = (char*)dst + 0x1c;
    return r;
}

struct UnkClass_00570330 { void Method(void* a); };                   // @ 0x00570330
void UnkClass_00570330::Method(void*) { /* partial */ }

struct UnkClass_00570400 { void Method(void* a, void* b, void* c); }; // @ 0x00570400
void UnkClass_00570400::Method(void*, void*, void*) { /* partial */ }

extern void* g_015e4a1c;
void UnkInsert_00570480(int key, bool flag);                          // @ 0x00570480
void UnkInsert_00570480(int key, bool flag)
{
    /* partial: dispatches to one of two global-singleton methods */
    (void)key; (void)flag;
}

struct UnkClass_005704c0 { void Method(void* a); };                   // @ 0x005704c0
void UnkClass_005704c0::Method(void*) { /* partial */ }

// ---------------------------------------------------------------- object with two sub-inits
struct Sub { void Init(); };                                          // @ 0x00571640
struct Big {
    Sub a;                                  // +0
    char padA[0x1c - 1];                    // +1
    Sub b;                                  // +0x1c
    char padB[0x38 - 0x1c - 1];             // +0x1d
    float vx, vy, vz;                       // +0x38
    char padC[0x50 - 0x44];                 // +0x44
    bool flag;                              // +0x50
    char padD[3];                           // +0x51
    int value;                              // +0x54
    Big* Init();                            // @ 0x00570870
};

Big* Big::Init()
{
    a.Init();
    b.Init();
    float* pVec = &vx;
    int tmp;
    ((int*)pVec)[0] = 0;
    ((int*)pVec)[1] = 0;
    ((int*)pVec)[2] = 0;
    flag = false;
    value = 0;
    return this;
}

struct UnkClass_005708d0 { void Method(void* a); };                   // @ 0x005708d0
void UnkClass_005708d0::Method(void*) { /* partial */ }
