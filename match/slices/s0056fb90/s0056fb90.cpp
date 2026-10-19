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

// ---------------------------------------------------------------- rig block-key set (0x015e4a1c)
struct SetPair { void* first; void* second; };
struct VectorSetU32 {
    void*    mpBegin;                   // +0
    void*    mpEnd;                     // +4  (0x015e4a20)
    void*    mpCapacity;                // +8
    uint32_t mAllocator;                // +0xc
    void  insert(void* position, const void* value);      // 0x00554020
    void  eraseKey(const void* value);                    // 0x005540d0
    void  equal_range(SetPair* out, const void* value);   // 0x00555980
};
VectorSetU32 g_rigBlockSet;             // 0x015e4a1c

struct Elem1cB {                        // 0x1c-byte element: 4-byte key + 0x18-byte payload
    uint32_t key;                       // +0
    struct Payload {
        char b[0x18];
        void DoDestroyValues();         // 0x00553fb0 (thiscall ret 0)
        void AssignFrom(const void* src);  // 0x0050d440 (thiscall ret 4)
    } body;                            // +4
    // An explicit p->~Elem1cB() makes cl /Od emit the destroy call plus the
    // guarded "scalar deleting destructor" tail (operator delete) seen in the original.
    ~Elem1cB() { body.DoDestroyValues(); }
};
Elem1cB* UninitCopyB(Elem1cB* first, Elem1cB* last, Elem1cB* dst);   // 0x00570400 (cdecl)

struct Key1c {
    uint32_t a; uint32_t b;
    bool operator<(const Key1c& k) const;    // @ 0x005715d0
    bool operator==(const Key1c& k) const;   // @ 0x00571610
};

// ---------------------------------------------------------------- cFeatureVector (0x1c bytes)
struct FeatureVector {
    void*    mpBegin;                   // +0
    void*    mpEnd;                     // +4
    void*    mpCapacity;                // +8
    uint32_t mAllocator;                // +0xc
    void* begin();                      // 0x005716c0
    void* end();                        // 0x005716e0
    void  clear();                      // 0x00571680
    float add(const void* key, float weight);   // 0x00571790 (thiscall ret 8)
};
struct Elem12 {                         // entry of a cFeatureVector: 8-byte key + float
    Key1c key;                          // +0
    float f;                            // +8
};
struct TraitData {                      // object holding two cFeatureVector members
    FeatureVector mBase;                // +0
    char          pad[0x1c - 0x10];     // +0x10
    FeatureVector mExtra;               // +0x1c
    float Intersect(FeatureVector* lhs, FeatureVector* rhs);   // 0x005704c0 (ret 8)
    void  Blend(bool positive, FeatureVector* src, uint32_t amount);   // 0x005708d0 (ret 0xc)
};

// ---------------------------------------------------------------- vector<StreamElem>::DoInsertValue
struct Str16 {                          // eastl::basic_string<wchar_t> (16 bytes with allocator)
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAlloc;
    Str16(const Str16& x);              // 0x0056e2d0
    void FreeBuffer();                  // 0x004237d0 (thiscall ret 0)
};
struct MetaI {                          // float weight + description string
    float f;
    Str16 str;
    MetaI(const MetaI& s) : f(s.f), str(s.str) {}
    void* CopyInit(const MetaI* src);   // 0x0056b020 (thiscall ret 4)
    void  FreeBuffer();                 // 0x004237d0 (thiscall ret 0, frees str's buffer)
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
    ~ElemI() { meta.str.FreeBuffer(); }
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

// @ 0x005702c0
// vector<...>::DoDestroyValues: uninitialized-copy the 0x1c-byte elements
// [first,last) into dst, then tear down the source range (destroy each
// element's payload; the debug allocator branch is dead here).
// Local names chosen via tools/matching/od_names.py to reproduce the /Od slot order.
void* CopyDestroyRange1c(void* first, void* last, void* dst)
{
    void* p30 = UninitCopyB((Elem1cB*)first, (Elem1cB*)last, (Elem1cB*)dst);
    uint32_t v[8];
    uint32_t t32[10];
    bool t21 = false;   // unused initialised local: cl /Od still materialises the store
    uint32_t n30[4];
    char* owner = (char*)dst;
    char* b = (char*)first;
    for (; b != last; b += 0x1c, owner += 0x1c) {
        ((Elem1cB*)b)->~Elem1cB();
    }
    return p30;
}

// @ 0x00570330
// Uninitialized copy of the 0x1c-byte {Key,MetaI} elements [first,last) to dst,
// destroying the source MetaI strings afterwards.
// Local names chosen via tools/matching/od_names.py to reproduce the /Od slot
// order (highest slot first: p30 first it p v last dst t21 n30).
ElemI* UninitCopy(ElemI* first, ElemI* last, ElemI* dst)
{
    const bool bUnused = false;
    ScratchSlots<4>();
    ElemI* out = dst;
    ElemI* src = first;
    for (; src != last; ++src, ++out) {
        ElemI* pElem = out;
        ElemI* pCreated;
        if (pElem != 0) {
            pElem->key = src->key;
            pElem->meta.CopyInit(&src->meta);
            pCreated = pElem;
        } else {
            pCreated = 0;
        }
        (void)pCreated;
    }
    ElemI* result = out;
    const bool bBlocks = false;
    ElemI* freeDst = dst;
    ElemI* freeSrc = first;
    for (; freeSrc != last; ++freeSrc, ++freeDst) {
        freeSrc->~ElemI();
    }
    (void)bUnused;
    (void)bBlocks;
    return result;
}

// @ 0x00570400
// Uninitialized copy of the 0x1c-byte {uint32,payload} elements [first,last) to dst.
// Local names chosen via tools/matching/od_names.py to reproduce the /Od slot order.
Elem1cB* UninitCopyB(Elem1cB* first, Elem1cB* last, Elem1cB* dst)
{
    bool v6 = false;                // bUnused: /Od still materialises the store
    Elem1cB* n26 = dst;             // out
    Elem1cB* n24 = first;           // src
    uint32_t t20[18];               // dead pad filling the original frame
    for (; n24 != last; n24 = n24 + 1) {
        Elem1cB* v22 = n26;         // pElem
        Elem1cB::Payload* n17 = &v22->body;   // pBody
        Elem1cB* p30;               // pCreated
        if (v22 != 0) {
            v22->key = n24->key;
            n17->AssignFrom(&n24->body);
            p30 = v22;
        } else {
            p30 = 0;
        }
        (void)p30;
        (void)t20;
        n26 = n26 + 1;
    }
    (void)v6;
    return n26;
}

// @ 0x00570480
// Insert (or drop) one rig-block key in the global block-key set.
void RigBlockSetInsert(uint32_t key, bool bInsert)
{
    SetPair stack;
    ScratchSlots<22>();
    if (bInsert) {
        g_rigBlockSet.insert(&stack, &key);
    } else {
        g_rigBlockSet.eraseKey(&key);
    }
}

// @ 0x005704c0
// Weighted intersection of two cFeatureVector maps: the weight of every key that
// is also present in the global rig-block set, summed with a greedy merge of the
// two sorted key runs.
float TraitData::Intersect(FeatureVector* lhs, FeatureVector* rhs)
{
    // Declaration order chosen to reproduce the original /Od slot order.
    ScratchSlots<17>();
    Elem12* itA = (Elem12*)lhs->begin();
    Elem12* endA;
    Elem12* endB;
    Elem12* itB = (Elem12*)rhs->begin();
    endA = (Elem12*)lhs->end();
    endB = (Elem12*)rhs->end();
    float sum = 0.0f;
    while (itA != endA && itB != endB) {
        while (itA != endA && itB != endB && itA->key < itB->key) {
            Elem12* saved1 = itA;
            SetPair pair1;
            g_rigBlockSet.equal_range(&pair1, saved1);
            Elem12* found1 = (pair1.first == pair1.second) ? (Elem12*)g_rigBlockSet.mpEnd : (Elem12*)pair1.first;
            if (found1 != (Elem12*)g_rigBlockSet.mpEnd) {
                sum += saved1->f;
            }
            itA += 1;
        }
        while (itA != endA && itB != endB && itB->key < itA->key) {
            Elem12* saved2 = itB;
            SetPair pair2;
            g_rigBlockSet.equal_range(&pair2, saved2);
            Elem12* found2 = (pair2.first == pair2.second) ? (Elem12*)g_rigBlockSet.mpEnd : (Elem12*)pair2.first;
            if (found2 != (Elem12*)g_rigBlockSet.mpEnd) {
                sum += saved2->f;
            }
            itB += 1;
        }
        while (itA->key == itB->key && itA != endA && itB != endB) {
            Elem12* saved3 = itA;
            float w3 = itB->f;
            SetPair pair3;
            g_rigBlockSet.equal_range(&pair3, saved3);
            Elem12* found3 = (pair3.first == pair3.second) ? (Elem12*)g_rigBlockSet.mpEnd : (Elem12*)pair3.first;
            if (found3 != (Elem12*)g_rigBlockSet.mpEnd) {
                if (w3 > saved3->f) {
                    sum += w3 - saved3->f;
                } else {
                    sum += saved3->f - w3;
                }
            }
            itA += 1;
            itB += 1;
        }
    }
    while (itA != endA && itB == endB) {
        Elem12* saved4 = itA;
        SetPair pair4;
        g_rigBlockSet.equal_range(&pair4, saved4);
        Elem12* found4 = (pair4.first == pair4.second) ? (Elem12*)g_rigBlockSet.mpEnd : (Elem12*)pair4.first;
        if (found4 != (Elem12*)g_rigBlockSet.mpEnd) {
            sum += saved4->f;
        }
        itA += 1;
    }
    for (; itA == endA && itB != endB; itB += 1) {
        Elem12* saved5 = itB;
        SetPair pair5;
        g_rigBlockSet.equal_range(&pair5, saved5);
        Elem12* found5 = (pair5.first == pair5.second) ? (Elem12*)g_rigBlockSet.mpEnd : (Elem12*)pair5.first;
        if (found5 != (Elem12*)g_rigBlockSet.mpEnd) {
            sum += saved5->f;
        }
    }
    return sum;
}

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

// @ 0x005708d0
// Copy every key of src into mBase scaled by +-1, then rebuild mExtra with each
// mBase weight renormalised by `amount` over the original weight.
// Local names chosen via tools/matching/od_names.py to reproduce the /Od slot order.
void TraitData::Blend(bool positive, FeatureVector* vec, uint32_t amount)
{
    float n30 = 1.0f;
    if (!positive) {
        n30 = -n30;
    }
    Elem12* p30 = (Elem12*)vec->begin();
    Elem12* v = (Elem12*)vec->end();
    for (; p30 != v; p30 += 1) {
        mBase.add(p30, n30);
    }
    mExtra.clear();
    Elem12* t32 = (Elem12*)mBase.begin();
    Elem12* t21 = (Elem12*)mBase.end();
    for (; t32 != t21; t32 += 1) {
        Elem12* b = t32;
        mExtra.add(b, amount / b->f);
    }
}
