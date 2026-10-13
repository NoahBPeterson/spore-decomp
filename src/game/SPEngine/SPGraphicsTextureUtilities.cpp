// src/game/SPEngine/SPGraphicsTextureUtilities.cpp -- migrated from slice(s) s007b19c0, s007b0a70, s007af8b0, s007aea30, s007ada40, s004e01d0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsTextureUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* memcpy(void* dst, const void* src, unsigned int n);
#pragma pack(push, 4)
#pragma intrinsic(memcpy)
#include "EA/AutoRefCount.h"
#include "eastl/vector.h"
#include "SP/cTextureInstance.h"
#include "EA/IO/FileStream.h"
#include <intrin.h>
#include <xmmintrin.h>
#include "SP/cTexturePreload.h"
#include "EA/ArgScript/cIParser.h"
#include "SP/cJob.h"
#include "SP/cDXTCompressJobData.h"
#include "SP/cImageDataRaw.h"

// ---- items of slice s004e01d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots() { uint32_t s[N]; }
void EASTLFree(void* p);                                                         // 0x00F47380
void* EASTLAlloc(void* allocator_s004e_01d0, uint32_t n, uint32_t align, uint32_t offset);  // 0x0042DEE0
extern "C" void* memcpy(void* dst, const void* src, unsigned int n);
namespace EA {
template <class T> class AutoRefCount_s004e_01d0 {
public:
    AutoRefCount_s004e_01d0(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s004e_01d0(const AutoRefCount_s004e_01d0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s004e_01d0() { if (mpObject) mpObject->Release(); }
    T* mpObject;
};
}
namespace EA {
namespace ResourceMan {
struct Key_s004e_01d0 {
    uint32_t mInstance;
    uint32_t mType;
    uint32_t mGroup;
};
}
}
namespace EA {
namespace ResourceMan {
inline bool operator==(const Key_s004e_01d0& a, const Key_s004e_01d0& b) { return a.mInstance == b.mInstance && a.mType == b.mType && a.mGroup == b.mGroup; }
}
}
namespace EA {
namespace ResourceMan {
struct KeyHash_s004e_01d0 { uint32_t operator()(const Key_s004e_01d0& k) const { return k.mInstance ^ k.mGroup; } };
}
}
using EA::ResourceMan::Key_s004e_01d0;
namespace eastl {
struct sp_vector_allocator_s004e_01d0 {
    const char* mpName;
    uint32_t mFlags;
};
}
namespace eastl {
template <class T> inline void destruct(T*, T*) {}   // trivial destructor: nothing to do
}
namespace eastl {
template <class T> inline T* copy_memcpy(T* first, T* last, T* result)
{
    return (T*)((last - first) * sizeof(T) + (char*)memcpy(result, first, (char*)last - (char*)first));
}
}
namespace eastl {
template <class T> inline T* uninitialized_copy_ptr(T* first, T* last, T* result)
{
    const bool bA = true;
    T* p = copy_memcpy(first, last, result);
    const bool bB = true;
    return p;
}
}
namespace eastl {
template <class T> struct vector_s004e_01d0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s004e_01d0 mAllocator;

    T* DoAllocate(uint32_t n) { return n ? (T*)EASTLAlloc(&mAllocator, n * sizeof(T), 4, 0) : 0; }
    void DoFree(T* p, uint32_t n) { if (p) deallocate(p, n * sizeof(T)); }
    static void deallocate(void* p, uint32_t) { if (*((uint32_t*)p - 1)) FreeBlock(p); }
    static void FreeBlock(void* p) { void* pBlock = p; EASTLFree(pBlock); }
    void DoInsertValue(T* position, const T& value);
    void reserve(uint32_t n);
    void push_back(const T& value);
};
}
namespace eastl {
template <class T> struct equal_to_s004e_01d0 { bool operator()(const T& a, const T& b) const { return a == b; } };
}
namespace eastl {
template <class T> struct hash_s004e_01d0 { uint32_t operator()(T val) const { return (uint32_t)val; } };
}
namespace eastl {
struct mod_range_hashing { uint32_t operator()(uint32_t r, uint32_t n) const { return r % n; } };
}
namespace eastl {
struct default_ranged_hash {};
}
namespace eastl {
template <class P> struct use_first_s004e_01d0 {};
}
namespace eastl {
struct true_type {};
}
namespace eastl {
struct prime_rehash_policy_s004e_01d0 {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
    prime_rehash_policy_s004e_01d0(float fMaxLoadFactor = 1.f) : mfMaxLoadFactor(fMaxLoadFactor), mfGrowthFactor(2.f), mnNextResize(0) {}
    static uint32_t GetPrevBucketCountOnly(uint32_t nBucketCountHint);   // 0x00921340
    uint32_t GetNextBucketCount(uint32_t nBucketCountHint) const;        // 0x00921360
    uint32_t GetBucketCount(uint32_t nElementCount) const;               // 0x009213C0
};
}
namespace eastl {
template <class Node> struct hashtable_iterator_base {
    Node* mpNode;
    Node** mpBucket;
    hashtable_iterator_base(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
    void increment() {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
};
}
namespace eastl {
template <class Node> struct hashtable_iterator : public hashtable_iterator_base<Node> {
    hashtable_iterator(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base<Node>(pNode, pBucket) {}
    hashtable_iterator(Node** pBucket) : hashtable_iterator_base<Node>(*pBucket, pBucket) {}
    hashtable_iterator(const hashtable_iterator& x) : hashtable_iterator_base<Node>(x.mpNode, x.mpBucket) {}
    hashtable_iterator& operator++() { this->increment(); return *this; }
};
}
namespace eastl {
template <class Node> struct hashtable_const_iterator : public hashtable_iterator_base<Node> {
    hashtable_const_iterator(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base<Node>(pNode, pBucket) {}
    hashtable_const_iterator(Node** pBucket) : hashtable_iterator_base<Node>(*pBucket, pBucket) {}
};
}
namespace eastl {
template <class Node> inline bool operator!=(const hashtable_iterator_base<Node>& a, const hashtable_iterator_base<Node>& b) { return a.mpNode != b.mpNode; }
}
namespace eastl {
template <class Node> struct insert_return_type {
    hashtable_iterator<Node> first;
    bool second;
};
}
namespace eastl {
struct allocator_s004e_01d0 {
    void deallocate(void* p, uint32_t) { void* const pMemory = p; EASTLFree(pMemory); }
};
}
namespace eastl {
extern void* gpEmptyBucketArray[2];                  // 0x0154DF28
}
namespace eastl {
template <class K, class V> struct pair_s004e_01d0 {
    K first;
    V second;
    pair_s004e_01d0(const K& x, const V& y) : first(x), second(y) {}
};
}
namespace eastl {
template <class K, class V> struct hash_node_s004e_01d0 {
    pair_s004e_01d0<K, V> mValue;
    hash_node_s004e_01d0* mpNext;
};
}
namespace eastl {
template <class K, class V, class H, class A> class hashtable_s004e_01d0 {
public:
    typedef hash_node_s004e_01d0<K, V> node_type;
    typedef hashtable_iterator<node_type> iterator;
    typedef hashtable_const_iterator<node_type> const_iterator;
    typedef pair_s004e_01d0<K, V> value_type;

    hashtable_s004e_01d0(uint32_t nBucketCount, const H& h1, const mod_range_hashing& h2, const default_ranged_hash& h,
              const equal_to_s004e_01d0<K>& eq, const use_first_s004e_01d0<value_type>& ek, const A& allocator_s004e_01d0);
    ~hashtable_s004e_01d0();

    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
    iterator find(const K& k);
    const_iterator find_const(const K& k);
    insert_return_type<node_type> DoInsertValue(const value_type& value, true_type);
    insert_return_type<node_type> insert(const value_type& value) { return DoInsertValue(value, true_type()); }
    uint32_t erase(const K& k);
    iterator erase(iterator i);
    void set_max_load_factor(float fMaxLoadFactor);
    void rehash_policy(const prime_rehash_policy_s004e_01d0& rehashPolicy) {
        mRehashPolicy = rehashPolicy;
        const uint32_t nBuckets = rehashPolicy.GetBucketCount((uint32_t)mnElementCount);
        if (nBuckets > mnBucketCount)
            DoRehash(nBuckets);
    }
    void reset() {
        ScratchSlots<1>();
        mnBucketCount = 1;
        mpBucketArray = (node_type**)&gpEmptyBucketArray[0];
        mnElementCount = 0;
        mRehashPolicy.mnNextResize = 0;
    }
    void clear() {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    void DoFreeBuckets(node_type** pBucketArray, uint32_t n) {
        if (n > 1)
            mAllocator.deallocate(pBucketArray, (n + 1) * sizeof(node_type*));
    }
    void DoFreeNode(node_type* pNode) { mAllocator.deallocate(pNode, sizeof(node_type)); }
    void DoFreeNodes(node_type** pBucketArray, uint32_t n);
    node_type** DoAllocateBuckets(uint32_t n);
    void DoRehash(uint32_t nBucketCount);
    uint32_t get_hash_code(const K& key) const { return (uint32_t)m_h1(key); }
    uint32_t bucket_index(const K&, uint32_t c, uint32_t n) const { return (uint32_t)m_h2(c, n); }
    bool compare(const K& k, uint32_t, node_type* pNode) const { return m_equal(k, pNode->mValue.first); }
    node_type* DoFindNode(node_type* pNode, const K& k, uint32_t c) const {
        for (; pNode; pNode = pNode->mpNext) {
            if (compare(k, c, pNode))
                return pNode;
        }
        return 0;
    }

    use_first_s004e_01d0<value_type> m_extract;   // 0x00
    equal_to_s004e_01d0<K> m_equal;               // 0x01
    H m_h1;                            // 0x02
    mod_range_hashing m_h2;            // 0x03
    node_type** mpBucketArray;         // 0x04
    uint32_t mnBucketCount;            // 0x08
    uint32_t mnElementCount;           // 0x0C
    prime_rehash_policy_s004e_01d0 mRehashPolicy; // 0x10
    A mAllocator;                      // 0x1C
};
}
namespace eastl {
template <class K, class V, class H, class A>
typename hashtable_s004e_01d0<K, V, H, A>::iterator hashtable_s004e_01d0<K, V, H, A>::find(const K& k)
{
    const uint32_t c = get_hash_code(k);
    const uint32_t n = (uint32_t)bucket_index(k, c, (uint32_t)mnBucketCount);
    node_type* const pNode = DoFindNode(mpBucketArray[n], k, c);
    return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
}
}
namespace eastl {
template <class K, class V, class H, class A>
typename hashtable_s004e_01d0<K, V, H, A>::const_iterator hashtable_s004e_01d0<K, V, H, A>::find_const(const K& k)
{
    const uint32_t c = get_hash_code(k);
    const uint32_t n = (uint32_t)bucket_index(k, c, (uint32_t)mnBucketCount);
    node_type* const pNode = DoFindNode(mpBucketArray[n], k, c);
    return pNode ? const_iterator(pNode, mpBucketArray + n) : const_iterator(mpBucketArray + mnBucketCount);
}
}
namespace eastl {
template <class K, class V, class H, class A>
uint32_t hashtable_s004e_01d0<K, V, H, A>::erase(const K& k)
{
    const uint32_t c = get_hash_code(k);
    const uint32_t n = (uint32_t)bucket_index(k, c, (uint32_t)mnBucketCount);
    const uint32_t nElementCountSaved = mnElementCount;
    node_type** pBucketArray = mpBucketArray + n;
    while (*pBucketArray && !compare(k, c, *pBucketArray))
        pBucketArray = &(*pBucketArray)->mpNext;
    while (*pBucketArray && compare(k, c, *pBucketArray)) {
        node_type* const pNode = *pBucketArray;
        *pBucketArray = pNode->mpNext;
        DoFreeNode(pNode);
        --mnElementCount;
    }
    return nElementCountSaved - mnElementCount;
}
}
namespace eastl {
template <class K, class V, class H, class A>
typename hashtable_s004e_01d0<K, V, H, A>::iterator hashtable_s004e_01d0<K, V, H, A>::erase(iterator i)
{
    iterator iNext(i);
    ++iNext;
    node_type* pNode = i.mpNode;
    node_type* pNodeCurrent = *i.mpBucket;
    if (pNodeCurrent == pNode)
        *i.mpBucket = pNodeCurrent->mpNext;
    else {
        node_type* pNodeNext = pNodeCurrent->mpNext;
        while (pNodeNext != pNode) {
            pNodeCurrent = pNodeNext;
            pNodeNext = pNodeCurrent->mpNext;
        }
        pNodeCurrent->mpNext = pNodeNext->mpNext;
    }
    DoFreeNode(pNode);
    --mnElementCount;
    return iNext;
}
}
namespace eastl {
template <class K, class V, class H, class A>
hashtable_s004e_01d0<K, V, H, A>::~hashtable_s004e_01d0()
{
    clear();
    DoFreeBuckets(mpBucketArray, mnBucketCount);
}
}
namespace eastl {
template <class K, class V, class H, class A>
void hashtable_s004e_01d0<K, V, H, A>::set_max_load_factor(float fMaxLoadFactor)
{
    hashtable_s004e_01d0* const pThis = this;
    pThis->rehash_policy(prime_rehash_policy_s004e_01d0(fMaxLoadFactor));
}
}
namespace eastl {
template <class K, class V, class H, class A> class hash_map_s004e_01d0 : public hashtable_s004e_01d0<K, V, H, A> {
public:
    typedef hashtable_s004e_01d0<K, V, H, A> base_type;
    typedef typename base_type::iterator iterator;
    typedef typename base_type::value_type value_type;
    hash_map_s004e_01d0(uint32_t nBucketCount, const H& hashFunction, const equal_to_s004e_01d0<K>& predicate, const A& allocator_s004e_01d0)
        : base_type(nBucketCount, hashFunction, mod_range_hashing(), default_ranged_hash(), predicate,
                    use_first_s004e_01d0<value_type>(), allocator_s004e_01d0) {}
    V& operator[](const K& key);
};
}
namespace eastl {
template <class V> struct OperatorIndexSlots { enum { N = 13 }; };
}
namespace eastl {
template <class V> struct OperatorIndexSlots<V*> { enum { N = 12 }; };
}
namespace eastl {
template <class K, class V, class H, class A>
V& hash_map_s004e_01d0<K, V, H, A>::operator[](const K& key)
{
    ScratchSlots<OperatorIndexSlots<V>::N>();
    iterator it = base_type::find(key);
    if (it != base_type::end())
        return (*it.mpNode).mValue.second;
    return (*base_type::insert(value_type(key, V())).first.mpNode).mValue.second;
}
}
namespace SP {
class cSpeciesProfile;
}
namespace SP {
class cSpeciesArchetype {
public:
    cSpeciesArchetype();                               // 0x004DA440
    cSpeciesArchetype(const cSpeciesArchetype& x);     // 0x004E1CB0
    ~cSpeciesArchetype();                              // 0x004DB1B0
    uint32_t mData[0x110];
};
}
namespace SP {
class cTextureInstance_s004e_01d0;
}
namespace eastl {
template class hash_map_s004e_01d0<Key_s004e_01d0, SP::cSpeciesProfile*, EA::ResourceMan::KeyHash_s004e_01d0, allocator_s004e_01d0>;
}
namespace eastl {
template class hashtable_s004e_01d0<Key_s004e_01d0, SP::cSpeciesProfile*, EA::ResourceMan::KeyHash_s004e_01d0, allocator_s004e_01d0>;
}
namespace eastl {
template class hash_map_s004e_01d0<uint32_t, SP::cSpeciesArchetype, hash_s004e_01d0<uint32_t>, allocator_s004e_01d0>;
}
// ---- items of slice s004e01d0 end

// ---- items of slice s007ada40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint32_t g_alphaIndexTable[8];   // 0x153bcec
#pragma auto_inline(on)
class Span {
public:
    void Init(int x, int y, int dx, int dy, int extra);
    int mX;         // +0x00
    int mY;         // +0x04
    int mXEnd;      // +0x08
    int mYEnd;      // +0x0c
    int mExtra;     // +0x10
    int mM1;        // +0x14
    int mM2;        // +0x18
    uint8_t mFlag;  // +0x1c
};
class InnerData {
public:
    char    mPad00[0x1c];
    uint8_t mFlag;      // +0x1c
};
class FlagHolder {
public:
    uint8_t IsSet();
    InnerData* mpData;  // +0x00
};
class DxtBase1 { public: virtual void v1(); virtual ~DxtBase1() {} };
class DxtBase2 { public: virtual void v2(); virtual ~DxtBase2() {} };
class DxtRefCount {
public:
    long mCount;
    DxtRefCount() { _InterlockedExchange((volatile long*)&mCount, 0); }
};
struct IRel1 { virtual void v0(); virtual void Release(); };            // Release at slot 1 (+4)
struct IRel2 { virtual void v0(); virtual void v1(); virtual void Release(); };  // Release at slot 2 (+8)
template<class T> struct RelPtr {
    T* mp;
    RelPtr() {}
    RelPtr(int) : mp(0) {}
    ~RelPtr() { if (mp) mp->Release(); }
};
class DxtSurface : public DxtBase1, public DxtBase2, public DxtRefCount {
public:
    RelPtr<IRel1> mC;   // +0x0c
    int m10;            // +0x10
    RelPtr<IRel2> m14;  // +0x14
    int m18;            // +0x18
    int m1c;            // +0x1c
    int m20;            // +0x20
    int m24;            // +0x24
    DxtSurface();
};
static inline uint32_t Expand565(uint32_t c)
{
    uint32_t r = ((c >> 11) << 3) & 0xff;
    r |= (c >> 13) & 7;
    uint32_t g = ((c >> 5) << 2) & 0xff;
    uint32_t g2 = (c >> 9) & 3;
    uint32_t b = (c << 3) & 0xff;
    uint32_t b2 = (c >> 2) & 7;
    uint32_t v = (0xffffff00u | r) << 8;
    v |= g2;
    v |= g;
    v <<= 8;
    v |= b2;
    v |= b;
    return v;
}
static inline void BuildPalette(uint32_t* pal, uint32_t c0, uint32_t c1, uint32_t raw0, uint32_t raw1)
{
    pal[0] = c0;
    pal[1] = c1;
    if (raw0 > raw1) {
        uint32_t r0 = (c0 >> 16) & 0xff, g0 = (c0 >> 8) & 0xff, b0 = c0 & 0xff;
        uint32_t r1 = (c1 >> 16) & 0xff, g1 = (c1 >> 8) & 0xff, b1 = c1 & 0xff;
        uint32_t t = (0xffffff00u | ((r1 + r0 * 2) / 3)) << 8;
        t |= ((g1 + g0 * 2) / 3) & 0xff;
        t <<= 8;
        t |= ((b1 + b0 * 2) / 3) & 0xff;
        pal[2] = t;
        uint32_t u = (0xffffff00u | ((r0 + r1 * 2) / 3)) << 8;
        u |= ((g0 + g1 * 2) / 3) & 0xff;
        u <<= 8;
        u |= ((b0 + b1 * 2) / 3) & 0xff;
        pal[3] = u;
    } else {
        pal[2] = ((((c1 & 0xfefefe) + (c0 & 0xfefefe)) >> 1) + (c1 & c0 & 0x10101)) | 0xff000000u;
        pal[3] = 0;
    }
}
void mappixeltransparent(uint32_t pix, int* idx, const uint32_t* pal);   // @ 0x007ad400
void __fastcall mappixel(uint32_t pix, const uint32_t* pal, int* idx);    // @ 0x007ad2e0 (pal in eax in the original)
uint32_t rbmappixel(uint32_t pix, const uint32_t* pal);                  // @ 0x007ad760 (pal in esi, pix in edx)
uint32_t trymapblockfast(const uint32_t* px, uint32_t c0, uint32_t c1, uint32_t limit);  // @ 0x007ad950
static const unsigned __int64 kMaskRGB = 0x0000000000ffffffULL;    // 0x140fbd0
static const unsigned __int64 kThird = 0x5555555555555555ULL;      // 0x140fbc8
// ---- items of slice s007ada40 end

// ---- items of slice s007aea30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" uint32_t trymapblock(uint32_t c0, uint32_t c1, uint32_t* map,
                                const uint32_t* pixels, uint32_t best);       // 0x7ad810
struct Endpoint {
    int      v[7];   // +0x00
    uint8_t  c;      // +0x1c
};
uint32_t rtrymapblock(const uint32_t* src, uint32_t raw0, uint32_t raw1);  // 0x7ade70
uint32_t rbtrymapblock(const uint32_t* src, uint32_t raw0, uint32_t raw1); // 0x7ae0b0
union DxtColor {
    uint32_t u;
    struct { uint8_t b, g, r, a; } c;
};
struct Rgb565 {
    uint8_t b, g, r, pad;
};
#define RGB888TO565(x) (((((x) >> 3) & 0x1f0000 | (x) & 0xfc00) >> 2 | (x) & 0xf8) >> 3)
#define CLAMP0(x)      ((x) < 0 ? 0 : (x))
#define MIN(a, b)      ((a) < (b) ? (a) : (b))
#define MAX(a, b)      ((a) > (b) ? (a) : (b))
struct EndpointColors {
    uint32_t v[2];
    uint32_t findendpoints(const uint32_t* pixels, uint32_t* out0, uint32_t* out1, int alpha, int quality);
};
// ---- items of slice s007aea30 end

// ---- items of slice s007af8b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl EAFree(void* p);                                   // 0x00F47380
void  __cdecl eadxt(void* dst, void* src, int stride, int count, int mode, int quality); // 0x007AF490
void  __cdecl FUN_007ad0c0(void* a, void* b);                    // 0x007AD0C0
bool  __cdecl FUN_007ae910();                                    // 0x007AE910
bool  __cdecl FUN_007b0030();                                    // 0x007B0030
void* __cdecl FUN_0067dcc0();                                    // 0x0067DCC0  MessageServer()
void* __cdecl FUN_0067dd60();                                    // 0x0067DD60
struct CJob {
    int pad0[7];
    int   mSlot;              // +0x1c
    void* mpReturn;           // +0x20
    void* mpCleanup;          // +0x24
    bool Continuation(void* fn, void* arg);   // 0x0068F9F0 __thiscall
};
struct VecCore  { void DestroyRange(void* b, void* e); };        // 0x0070F520 __thiscall
struct VecReserve { void Reserve(int n); };                      // 0x004E0880 __thiscall
struct VecAssignOp { void Assign(void*, void*, void*, void*, void*); }; // 0x004E8EE0
struct VecGrow  { void* Grow(int n, void* a, void* b); };        // 0x007B0370 __thiscall
struct RasterOps{ void GetMipSize(void* p, int mip); };          // 0x011F0270 __thiscall
struct IFac { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
              virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
              virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
              virtual void v12(); virtual void v13(void*);      // +0x34
              virtual void v14();
              virtual void* v15(int,int,int,int,int,int,int,int); // +0x3C
              virtual void v16(); };
struct IMsg { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
              virtual void v4(); virtual void v5(); virtual void v6(void*,void*,int,int); };
struct Elem { char pad[0x28]; unsigned char* data; };           // pixel element at +0x28
struct VecObj { char pad[0xc]; Elem** begin; Elem** end; };     // vector at +0xc
struct cImageDataRaw {
    char pad0[0x1c];
    int mWidth;               // +0x1c
    int mHeight;              // +0x20
    int mFormat;              // +0x24
    unsigned char* mData;     // +0x28
};
struct cDXTCompressJobData {
    char pad0[0xc];
    cImageDataRaw* mSource;   // +0xc
    cImageDataRaw* mOutput;   // +0x10
    int mMode;                // +0x14
    int mQuality;             // +0x18
    int mBlockSize;           // +0x1c
    unsigned mMessageID;      // +0x20
    void* mMessage;           // +0x24
    int DXTCompressRow(int row);
    bool RunJob(CJob* job);
};
struct cRowJobData {
    char pad[0xc];
    VecObj* mP;               // +0xc
    int mMsgId;               // +0x10
    int mMsgArg;              // +0x14
    bool mFlag18;             // +0x18
    bool StepDown(CJob* job);
    bool StepUp(CJob* job);
};
namespace __equiv_ann1 {
struct VecReserve {
    void Reserve();   // 0x004e0880 (equiv t2)
};
}
// ---- items of slice s007af8b0 end

// ---- items of slice s007b0a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl EAAlloc(unsigned n, const char* name, int a, int b, const char* f, int l); // 0x00F473A0
void  __cdecl DestroyElems(void* first, void* last);              // 0x00B007F0
void  __cdecl RemoveIf(void* a, void* b, void* c);                // 0x0076DE80
void* __cdecl MoveNodes(void* a, void* b, void* c);               // 0x007AF5D0
void  __cdecl MoveNodes2(void* a, void* b, void* c);              // 0x007AF6D0
void* __cdecl DoCopy4(void* first, void* last, void* dest);       // 0x006782C0
void** CopyRefRange4(void** first, void** last, void** dest);     // 0x007B0040
struct T20 {
    int a,b,c,d,e,f,g; char h;
    T20& operator=(const T20& o) { a=o.a;b=o.b;c=o.c;d=o.d;e=o.e;f=o.f;g=o.g;h=o.h; return *this; }
};
struct C20;
void C20_InsertTail(C20* self, T20* pos, int count, void* value); // 0x007B0BE0
struct C20 {
    T20* begin;  T20* end;  T20* cap;                             // +0x0
    char pad0[8];                                                 // +0xc
    int* freeBegin;  int* freeEnd;  int* freeCap;                 // +0x14
    void grow(T20* p, const T20& v);                              // 0x007b0a70
    void push_back(const T20& v);                                 // 0x007b0f40
    void resize(int n);                                           // 0x007b1040
    int  Alloc();                                                 // 0x007b10a0
    void clear();                                                 // 0x007b1950
};
struct C4 {
    void** begin; void** end; void** cap;
    void assign(void** first, void** last);                       // 0x007b0da0
};
// ---- items of slice s007b0a70 end

// ---- items of slice s007b19c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct S3 { int a, b, c; };
struct IFac_s007b_19c0 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void* v7(S3 s, int z);                  // +0x1C
    virtual void* v8(int,int);                      // +0x20 (RTT create)
};
struct W1e70 {
    void helper(int, void*, void*);
    void f(void* a, void* b);
};
struct W1da0 {
    void Handler(void* r);                          // 0x007B1AF0 __thiscall
    void f(S3* p);
};
// ---- items of slice s007b19c0 end

// @ 0x004e0880
template <class T> void eastl::vector_s004e_01d0<T>::reserve(uint32_t n)
{
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        T* const pNewData = DoAllocate(n);
        uninitialized_copy_ptr(mpBegin, mpEnd, pNewData);
        destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        const int nPrevSize = mpEnd - mpBegin;
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = mpBegin + n;
    }
}
template void eastl::vector_s004e_01d0<EA::AutoRefCount_s004e_01d0<SP::cTextureInstance_s004e_01d0> >::reserve(uint32_t);





// @ 0x007ada40
void mapblock(const uint32_t* src, uint8_t* dst, uint32_t c0, uint32_t c1, int mode)
{
    uint32_t pal[4];
    pal[0] = Expand565(c0);
    pal[1] = Expand565(c1);
    dst[0] = (uint8_t)c0;
    dst[2] = (uint8_t)c1;
    dst[1] = (uint8_t)(c0 >> 8);
    dst[3] = (uint8_t)(c1 >> 8);
    if (mode == 0) {
        BuildPalette(pal, pal[0], pal[1], c0, c1);
        for (int row = 0; row < 4; row++) {
            int bits = 0;
            for (int k = 0; k < 8; k += 2) {
                int idx = 0;
                mappixeltransparent(*src, &idx, pal);
                bits |= idx << k;
                src++;
            }
            dst[4 + row] = (uint8_t)bits;
        }
    } else {
        for (int row = 0; row < 4; row++) {
            int bits = 0;
            for (int k = 0; k < 8; k += 2) {
                int idx = 0;
                mappixel(*src, pal, &idx);
                bits |= idx << k;
                src++;
            }
            dst[4 + row] = (uint8_t)bits;
        }
    }
}





// @ 0x007adcf0
void FUN_007adcf0(const uint32_t* src, uint8_t* dst, uint32_t cB, uint32_t cA)
{
    uint32_t a565 = ((cA >> 8) & 0xf800) | ((cA >> 5) & 0x7e0) | ((cA >> 3) & 0x1f);
    uint32_t b565 = ((cB >> 8) & 0xf800) | ((cB >> 5) & 0x7e0) | ((cB >> 3) & 0x1f);
    *(uint16_t*)(dst + 0) = (uint16_t)a565;
    *(uint16_t*)(dst + 2) = (uint16_t)b565;
    if ((uint16_t)a565 <= (uint16_t)b565) {
        *(uint32_t*)(dst + 4) = 0;
        return;
    }
    __m64 mask = *(const __m64*)&kMaskRGB;
    __m64 m0 = _mm_and_si64(_mm_cvtsi32_si64((int)cA), mask);
    __m64 m1 = _mm_and_si64(_mm_cvtsi32_si64((int)cB), mask);
    __m64 zero = _mm_setzero_si64();
    m0 = _mm_unpacklo_pi8(m0, zero);
    m1 = _mm_unpacklo_pi8(m1, zero);
    __m64 m2 = _mm_shuffle_pi16(m0, 0xe4);
    __m64 m3 = _mm_shuffle_pi16(m1, 0xe4);
    m2 = _mm_add_pi16(m2, m0);
    m3 = _mm_add_pi16(m3, m0);
    m2 = _mm_add_pi16(m2, m1);
    m3 = _mm_add_pi16(m3, m1);
    __m64 third = *(const __m64*)&kThird;
    m2 = _mm_mulhi_pi16(m2, third);
    m3 = _mm_mulhi_pi16(m3, third);
    uint32_t result = 0;
    for (int off = 0x3c; off >= 0; off -= 4) {
        __m64 p = _mm_unpacklo_pi8(_mm_and_si64(_mm_cvtsi32_si64(*(const int*)((const uint8_t*)src + off)), mask), zero);
        __m64 d0 = _mm_madd_pi16(_mm_sub_pi16(p, m0), _mm_sub_pi16(p, m0));
        __m64 d1 = _mm_madd_pi16(_mm_sub_pi16(p, m1), _mm_sub_pi16(p, m1));
        uint32_t best = (((uint32_t)_mm_cvtsi64_si32(d0) + (uint32_t)_mm_cvtsi64_si32(_mm_unpackhi_pi32(d0, d0))) * 4);
        uint32_t e1 = (((uint32_t)_mm_cvtsi64_si32(d1) + (uint32_t)_mm_cvtsi64_si32(_mm_unpackhi_pi32(d1, d1))) * 4) | 1;
        if (e1 < best) best = e1;
        __m64 d2 = _mm_madd_pi16(_mm_sub_pi16(p, m2), _mm_sub_pi16(p, m2));
        uint32_t e2 = (((uint32_t)_mm_cvtsi64_si32(d2) + (uint32_t)_mm_cvtsi64_si32(_mm_unpackhi_pi32(d2, d2))) * 4) | 2;
        if (e2 < best) best = e2;
        __m64 d3 = _mm_madd_pi16(_mm_sub_pi16(p, m3), _mm_sub_pi16(p, m3));
        uint32_t e3 = (((uint32_t)_mm_cvtsi64_si32(d3) + (uint32_t)_mm_cvtsi64_si32(_mm_unpackhi_pi32(d3, d3))) * 4) | 3;
        if (e3 < best) best = e3;
        result = (result << 2) | (best & 3);
    }
    *(uint32_t*)(dst + 4) = result;
}





// @ 0x007ade70
uint32_t rtrymapblock(const uint32_t* src, uint32_t raw0, uint32_t raw1)
{
    uint32_t pal[4];
    pal[0] = Expand565(raw0);
    pal[1] = Expand565(raw1);
    BuildPalette(pal, pal[0], pal[1], raw0, raw1);
    uint32_t p0 = pal[0] & 0xff, p1 = pal[1] & 0xff, p2 = pal[2] & 0xff, p3 = pal[3] & 0xff;
    uint32_t total = 0;
    const uint8_t* p = (const uint8_t*)src + 2;
    for (int i = 0; i < 16; i++) {
        int v = p[0];
        uint32_t best = 0x7fffffff;
        uint32_t e;
        e = (uint32_t)((v - (int)p0) * (v - (int)p0)); if (e < best) best = e;
        e = (uint32_t)((v - (int)p1) * (v - (int)p1)); if (e < best) best = e;
        e = (uint32_t)((v - (int)p2) * (v - (int)p2)); if (e < best) best = e;
        e = (uint32_t)((v - (int)p3) * (v - (int)p3)); if (e < best) best = e;
        total += best;
        p += 4;
    }
    return total;
}





// @ 0x007ae0b0
uint32_t rbtrymapblock(const uint32_t* src, uint32_t raw0, uint32_t raw1)
{
    uint32_t pal[4];
    pal[0] = Expand565(raw0);
    pal[1] = Expand565(raw1);
    BuildPalette(pal, pal[0], pal[1], raw0, raw1);
    uint32_t total = 0;
    for (int i = 0; i < 16; i++)
        total += rbmappixel(src[i], pal);
    return total;
}





// @ 0x007ae2a0
uint32_t RefineMinMaxColors(const uint32_t* px, uint32_t* out)
{
    uint32_t q[5];
    static const int kSample[5] = { 0, 2, 5, 11, 13 };
    for (int i = 0; i < 5; i++) {
        uint32_t v = px[kSample[i]];
        uint32_t c565 = ((((v >> 3) & 0x1f0000) | (v & 0xfc00)) >> 2 | (v & 0xf8)) >> 3;
        uint32_t base = ((((c565 >> 11) << 3) & 0xff) << 8 | (((c565 >> 5) << 2) & 0xff)) << 8 | ((c565 << 3) & 0xff);
        base &= 0xffffff;
        uint32_t rep = (((((c565 >> 13) & 7) << 8) | ((c565 >> 9) & 3)) << 8) | ((c565 >> 2) & 7);
        q[i] = base | rep;
    }
    uint32_t best = trymapblockfast(px, out[0] & 0xffffff, out[1] & 0xffffff, 0x7fffffff);
    if (best > 8) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                uint32_t c0 = q[i], c1 = q[j];
                if (c0 < c1) {
                    uint32_t e = trymapblockfast(px, c0, c1, best);
                    if (e < best) {
                        best = e;
                        out[0] = c0;
                        out[1] = c1;
                        if (best <= 8) return best;
                    }
                }
            }
        }
    }
    return best;
}





// @ 0x007ae5b0
void FUN_007ae5b0(const uint8_t* src, uint8_t* dst, int stride)
{
    const uint8_t* p = src;
    for (int i = 0; i < 4; i++) {
        dst[i * 2] = (p[7] & 0xf0) | (p[3] >> 4);
        dst[i * 2 + 1] = (p[0xf] & 0xf0) | (p[0xb] >> 4);
        p += stride;
    }
}





// @ 0x007ae660
void InterpolatedAlphaBlock(int hi, int lo, const uint8_t* src, uint8_t* dst)
{
    dst[0] = (uint8_t)hi;
    dst[1] = (uint8_t)lo;
    if (hi - lo == 0) {
        *(uint32_t*)(dst + 2) = 0;
        *(uint16_t*)(dst + 6) = 0;
        return;
    }
    uint32_t scale = 0x7ffffffu / (uint32_t)(hi - lo);
    uint32_t rows[4];
    for (int r = 0; r < 4; r++) {
        uint32_t v = 0;
        for (int c = 3; c >= 0; c--) {
            uint32_t a = src[r * 16 + c * 4 + 3];
            uint32_t t = g_alphaIndexTable[((a - (uint32_t)lo) * scale) >> 24];
            v = (v << 3) | t;
        }
        rows[r] = v;
    }
    uint32_t lo24 = rows[0] | (rows[1] << 12);
    dst[2] = (uint8_t)lo24;
    dst[3] = (uint8_t)(lo24 >> 8);
    dst[4] = (uint8_t)(lo24 >> 16);
    uint32_t hi24 = rows[2] | (rows[3] << 12);
    dst[5] = (uint8_t)hi24;
    dst[6] = (uint8_t)(hi24 >> 8);
    dst[7] = (uint8_t)(hi24 >> 16);
}





// @ 0x007ae840
void FUN_007ae840(const uint8_t* src, int stride, __m64* copy, uint32_t* out)
{
    const uint8_t* p = src;
    __m64 r0 = *(const __m64*)p;
    __m64 r1 = *(const __m64*)(p + 8);
    p += stride;
    __m64 r2 = *(const __m64*)p;
    __m64 r3 = *(const __m64*)(p + 8);
    p += stride;
    __m64 r4 = *(const __m64*)p;
    __m64 r5 = *(const __m64*)(p + 8);
    __m64 r6 = *(const __m64*)(p + stride);
    __m64 r7 = *(const __m64*)(p + stride + 8);
    copy[0] = r0; copy[1] = r1; copy[2] = r2; copy[3] = r3;
    copy[4] = r4; copy[5] = r5; copy[6] = r6; copy[7] = r7;
    __m64 mn = _mm_min_pu8(r0, r1);
    __m64 mx = _mm_max_pu8(r1, copy[0]);
    mn = _mm_min_pu8(mn, r2); mx = _mm_max_pu8(mx, r2);
    mn = _mm_min_pu8(mn, r3); mx = _mm_max_pu8(mx, r3);
    mn = _mm_min_pu8(mn, r4); mx = _mm_max_pu8(mx, r4);
    mn = _mm_min_pu8(mn, r5); mx = _mm_max_pu8(mx, r5);
    mn = _mm_min_pu8(mn, r6); mx = _mm_max_pu8(mx, r6);
    mn = _mm_min_pu8(mn, r7); mx = _mm_max_pu8(mx, r7);
    __m64 mn2 = _mm_srli_si64(mn, 32);
    __m64 mx2 = _mm_srli_si64(mx, 32);
    mn = _mm_min_pu8(mn, mn2);
    mx = _mm_max_pu8(mx, mx2);
    out[0] = (uint32_t)_mm_cvtsi64_si32(mn);
    out[1] = (uint32_t)_mm_cvtsi64_si32(mx);
}





// @ 0x007ae920
void Span::Init(int x, int y, int dx, int dy, int extra)
{
    int* p = (int*)this;
    p[0] = x;
    p[2] = x + dx;
    p[1] = y;
    p[3] = y + dy;
    p[4] = extra;
    p[5] = -1;
    p[6] = -1;
    ((uint8_t*)this)[0x1c] = 0;
}





// @ 0x007ae960
uint8_t FlagHolder::IsSet()
{
    return mpData->mFlag;
}





// @ 0x007ae980
#pragma auto_inline(off)
void DestroyDxtSurface(DxtSurface* p)
{
    p->~DxtSurface();
}





// @ 0x007ae9f0
DxtSurface::DxtSurface()
: mC(0), m10(0), m24(0)
{
}




// @ 0x007aeab0
uint32_t EndpointColors::findendpoints(const uint32_t* pixels, uint32_t* out0, uint32_t* out1, int alpha, int quality)
{
    const uint32_t* colors = v;
    DxtColor c0, c1;
    uint32_t map[257];
    c0.u = colors[0];
    c1.u = colors[1];
    map[0] = 0;

    uint32_t thresh = 4;
    if (quality >= 40) thresh = 3;
    if (quality >= 60) thresh = 1;
    if (quality >= 70) thresh = 0;

    uint32_t e0 = RGB888TO565(c1.u);
    uint32_t e1 = RGB888TO565(c0.u);
    uint32_t best = 0x7fffffff;

    if (quality >= 5)
    {
        best = trymapblock(e0, e1, map, pixels, best);
        if (best > thresh)
        {
            if (quality < 10)
            {
                uint32_t err = trymapblock(e1, e0, map, pixels, best);
                if (err < best)
                {
                    uint32_t t = e0;
                    best = err;
                    e0 = e1;
                    e1 = t;
                }
            }
            else
            {
                for (int i = 0; i < 16; ++i)
                {
                    uint32_t a = RGB888TO565(pixels[i]);
                    for (int j = 0; j < 16; ++j)
                    {
                        uint32_t b = RGB888TO565(pixels[j]);
                        if (a > b)
                        {
                            uint32_t err = trymapblock(a, b, map, pixels, best);
                            if (err < best)
                            {
                                best = err;
                                e0 = a;
                                e1 = b;
                                if (err <= thresh)
                                    goto done;
                            }
                        }
                    }
                }
            }
        }
    }

    for (int pass = 0; pass < 1; ++pass)
    {
        if (quality > 10)
        {
            // Extrapolated 888 box: lo = 2*c0 - c1, hi = 2*c1 - c0.
            uint8_t lo8r = (uint8_t)CLAMP0((int)c0.c.r * 2 - (int)c1.c.r);
            uint8_t lo8g = (uint8_t)CLAMP0((int)c0.c.g * 2 - (int)c1.c.g);
            uint8_t lo8b = (uint8_t)CLAMP0((int)c0.c.b * 2 - (int)c1.c.b);
            int x;
            uint8_t hi8r, hi8g, hi8b;
            x = (int)c1.c.r * 2 - (int)c0.c.r;  hi8r = x > 0xff ? 0xff : (uint8_t)x;
            x = (int)c1.c.g * 2 - (int)c0.c.g;  hi8g = x > 0xff ? 0xff : (uint8_t)x;
            x = (int)c1.c.b * 2 - (int)c0.c.b;  hi8b = x > 0xff ? 0xff : (uint8_t)x;

            Rgb565 lo, hi;
            lo.r = (uint8_t)CLAMP0((int)(lo8r >> 3) - 1);
            lo.g = (uint8_t)CLAMP0((int)(lo8g >> 2) - 1);
            lo.b = (uint8_t)CLAMP0((int)(lo8b >> 3) - 1);
            x = (hi8r >> 3) + 2;  hi.r = x > 0x1f ? 0x1f : (uint8_t)x;
            x = (hi8g >> 2) + 2;  hi.g = x > 0x3f ? 0x3f : (uint8_t)x;
            x = (hi8b >> 3) + 2;  hi.b = x > 0x1f ? 0x1f : (uint8_t)x;

            // Search boxes around e0 (lo0..hi0) and e1 (lo1..hi1).
            Rgb565 lo0, hi0, lo1, hi1;
            if (quality >= 100)
            {
                lo0 = lo;
                lo1 = lo;
                hi0 = hi;
                hi1 = hi;
            }
            else
            {
                uint32_t dn = quality / 50;
                uint32_t up = quality / 40 + 1;
                uint32_t r, g, b;

                r = (e0 >> 11) & 0x1f;  g = (e0 >> 5) & 0x3f;  b = e0 & 0x1f;
                lo0.r = (uint8_t)MAX((uint32_t)lo.r, r - dn);
                lo0.g = (uint8_t)MAX((uint32_t)lo.g, g - dn);
                lo0.b = (uint8_t)MAX((uint32_t)lo.b, b - dn);
                hi0.r = (uint8_t)MIN(MIN((uint32_t)hi.r, r + up), 0x1fu);
                hi0.g = (uint8_t)MIN(MIN((uint32_t)hi.g, g + up), 0x3fu);
                hi0.b = (uint8_t)MIN(MIN((uint32_t)hi.b, b + up), 0x1fu);

                r = (e1 >> 11) & 0x1f;  g = (e1 >> 5) & 0x3f;  b = e1 & 0x1f;
                lo1.r = (uint8_t)MAX((uint32_t)lo.r, r - dn);
                lo1.g = (uint8_t)MAX((uint32_t)lo.g, g - dn);
                lo1.b = (uint8_t)MAX((uint32_t)lo.b, b - dn);
                hi1.r = (uint8_t)MIN(MIN((uint32_t)hi.r, r + up), 0x1fu);
                hi1.g = (uint8_t)MIN(MIN((uint32_t)hi.g, g + up), 0x3fu);
                hi1.b = (uint8_t)MIN(MIN((uint32_t)hi.b, b + up), 0x1fu);
            }

            // Vary e0 with e1 fixed.
            if (quality >= 20)
            {
                for (uint32_t r = lo0.r; r <= hi0.r; ++r)
                    for (uint32_t b = lo0.b; b <= hi0.b; ++b)
                        for (uint32_t g = lo0.g; g <= hi0.g; ++g)
                        {
                            uint32_t c = ((r << 6 | g) << 5) | b;
                            if (c > e1)
                            {
                                uint32_t err = trymapblock(c, e1, map, pixels, best);
                                if (err < best)
                                {
                                    best = err;
                                    e0 = c;
                                    if (err <= thresh)
                                        goto done;
                                }
                            }
                        }
            }

            // Vary e1 with e0 fixed.
            if (quality >= 25)
            {
                for (uint32_t r = lo1.r; r <= hi1.r; ++r)
                    for (uint32_t b = lo1.b; b <= hi1.b; ++b)
                        for (uint32_t g = lo1.g; g <= hi1.g; ++g)
                        {
                            uint32_t c = ((r << 6 | g) << 5) | b;
                            if (e0 > c)
                            {
                                uint32_t err = trymapblock(e0, c, map, pixels, best);
                                if (err < best)
                                {
                                    best = err;
                                    e1 = c;
                                    if (err <= thresh)
                                        goto done;
                                }
                            }
                        }
            }

            // Vary both: red pairs, then red/blue pairs, pre-screened by the
            // partial-channel error bounds.
            if (quality >= 30)
            {
                for (uint32_t r0 = lo0.r; r0 <= hi0.r; ++r0)
                    for (uint32_t r1 = lo1.r; r1 <= hi1.r; ++r1)
                    {
                        if (!(r0 > r1 || quality >= 50))
                            continue;
                        if (rtrymapblock(pixels, r0, r1) >= best)
                            continue;
                        for (uint32_t b0 = lo0.b; b0 <= hi0.b; ++b0)
                            for (uint32_t b1 = lo1.b; b1 <= hi1.b; ++b1)
                            {
                                uint32_t err = rbtrymapblock(pixels, b0 | r0 << 11, r1 << 11 | b1);
                                if (err < best)
                                {
                                    for (uint32_t g0 = lo0.g; g0 <= hi0.g; ++g0)
                                    {
                                        uint32_t ca = ((r0 << 6 | g0) << 5) | b0;
                                        for (uint32_t g1 = lo1.g; g1 <= hi1.g; ++g1)
                                        {
                                            uint32_t cb = ((r1 << 6 | g1) << 5) | b1;
                                            if (ca > cb || quality >= 60)
                                            {
                                                uint32_t e = trymapblock(ca, cb, map, pixels, best);
                                                if (e < best)
                                                {
                                                    best = e;
                                                    e0 = ca;
                                                    e1 = cb;
                                                    if (e <= thresh)
                                                        goto done;
                                                }
                                                else if (e - best > 16)
                                                {
                                                    ++g1;
                                                }
                                            }
                                        }
                                    }
                                }
                                else if (err - best > 0x1000)
                                {
                                    ++b1;
                                }
                            }
                    }
            }

            if (quality == 100)
                break;
        }
    }

done:
    if (!alpha && c0.c.a < 0x80 && e0 > e1)
    {
        uint32_t t = e0;
        e0 = e1;
        e1 = t;
    }
    *out0 = e0;
    *out1 = e1;
    return best;
}




// @ 0x007af5d0
void FUN_007af5d0(Endpoint* first, Endpoint* last, Endpoint* dest)
{
    for (; first != last; ++first) {
        if (dest != 0) {
            dest->v[0] = first->v[0];
            dest->v[1] = first->v[1];
            dest->v[2] = first->v[2];
            dest->v[3] = first->v[3];
            dest->v[4] = first->v[4];
            dest->v[5] = first->v[5];
            dest->v[6] = first->v[6];
            dest->c    = first->c;
        }
        ++dest;
    }
}




// @ 0x007af620
void FUN_007af620(Endpoint* first, Endpoint* last, const Endpoint* src)
{
    for (; first != last; ++first) {
        first->v[0] = src->v[0];
        first->v[1] = src->v[1];
        first->v[2] = src->v[2];
        first->v[3] = src->v[3];
        first->v[4] = src->v[4];
        first->v[5] = src->v[5];
        first->v[6] = src->v[6];
        first->c    = src->c;
    }
}




// @ 0x007af670
void FUN_007af670(Endpoint* dest, uint32_t n, const Endpoint* src)
{
    Endpoint* d = dest;
    while (n > 0) {
        if (d != 0) {
            d->v[0] = src->v[0];
            d->v[1] = src->v[1];
            d->v[2] = src->v[2];
            d->v[3] = src->v[3];
            d->v[4] = src->v[4];
            d->v[5] = src->v[5];
            d->v[6] = src->v[6];
            d->c    = src->c;
        }
        --n;
        d = (Endpoint*)((char*)d + 0x20);
    }
}




// @ 0x007af6d0
void FUN_007af6d0(Endpoint* first, Endpoint* last, Endpoint* dest)
{
    while (last != first) {
        last = (Endpoint*)((char*)last - 0x20);
        dest = (Endpoint*)((char*)dest - 0x20);
        dest->v[0] = last->v[0];
        dest->v[1] = last->v[1];
        dest->v[2] = last->v[2];
        dest->v[3] = last->v[3];
        dest->v[4] = last->v[4];
        dest->v[5] = last->v[5];
        dest->v[6] = last->v[6];
        dest->c    = last->c;
    }
}



// @ 0x007afae0
bool cRowJobData::StepDown(CJob* job)
{
    int slot = job->mSlot;
    FUN_007ad0c0((void*)mP->begin[slot], (void*)mP->begin[slot-1]);
    if (--slot == 0) {
        void* oldCln = job->mpCleanup;
        void* oldRet = job->mpReturn;
        job->mpReturn = mP;
        job->mpCleanup = (void*)slot;
        if (oldCln)
            ((void (__cdecl*)(void*))oldCln)(oldRet);
        if (mMsgId) {
            IMsg* s = (IMsg*)FUN_0067dcc0();
            s->v6((void*)mMsgId, (void*)mMsgArg, 0, 0);
        }
        return true;
    }
    job->mSlot = slot;
    return job->Continuation((void*)&FUN_007ae910, this);
}



// @ 0x007afb70
int cDXTCompressJobData::DXTCompressRow(int row)
{
    cImageDataRaw* src = mSource;
    cImageDataRaw* out = mOutput;
    int blocksW = (src->mWidth + 3) >> 2;
    int blockRow = row >> 2;
    if (row + 3 < src->mHeight) {
        unsigned rem = (unsigned)src->mWidth & 3;
        int nBlocks = blocksW;
        if (rem != 0)
            nBlocks = blocksW - 1;
        if (nBlocks > 0) {
            eadxt(out->mData + blockRow * mBlockSize * blocksW,
                  src->mData + src->mWidth * row * 4,
                  src->mWidth * 4, nBlocks, mMode, mQuality);
        }
        if (rem != 0) {
            int stride = src->mWidth;
            int off = nBlocks * 4;
            unsigned char* rowp = src->mData + stride * row * 4;
            int block[16];
            int k = 4;
            do {
                block[0] = (off < stride) ? *(int*)(rowp + nBlocks*0x10)
                                          : *(int*)(rowp + stride*4 - 4);
                block[1] = (off+1 < src->mWidth) ? *(int*)(rowp + 4 + nBlocks*0x10)
                                                 : *(int*)(rowp + src->mWidth*4 - 4);
                block[2] = (off+2 < src->mWidth) ? *(int*)(rowp + (off+2)*4)
                                                 : *(int*)(rowp + src->mWidth*4 - 4);
                block[3] = (off+3 < src->mWidth) ? *(int*)(rowp + (off+3)*4)
                                                 : *(int*)(rowp + src->mWidth*4 - 4);
                stride = src->mWidth;
                rowp += stride * 4;
                k--;
            } while (k);
            eadxt(out->mData + (blockRow * blocksW + nBlocks) * mBlockSize,
                  block, 0x10, 1, mMode, mQuality);
        }
        return 4;
    }
    if (src->mHeight <= row)
        return 0;
    if (blocksW > 0) {
        int dstOff = blockRow * blocksW;
        int srcOff = 0xc;
        int n = blocksW;
        do {
            int* rowp = (int*)(src->mData + src->mWidth * row * 4);
            int col = 2;
            int block[16];
            int m = 0;
            do {
                block[0] = (col-2 < src->mWidth) ? *(int*)((char*)rowp + srcOff-0xc)
                                                 : *(int*)((char*)rowp + src->mWidth*4 - 4);
                block[1] = (col-1 < src->mWidth) ? *(int*)((char*)rowp + srcOff-8)
                                                 : *(int*)((char*)rowp + src->mWidth*4 - 4);
                block[2] = (col   < src->mWidth) ? *(int*)((char*)rowp + srcOff-4)
                                                 : *(int*)((char*)rowp + src->mWidth*4 - 4);
                block[3] = (col+1 < src->mWidth) ? *(int*)((char*)rowp + srcOff)
                                                 : *(int*)((char*)rowp + src->mWidth*4 - 4);
                if (++m < 4)
                    rowp = (int*)((char*)rowp + src->mWidth*4);
                col += 4;
            } while (m < 4);
            eadxt(out->mData + mBlockSize * dstOff, block, 0x10, 1, mMode, mQuality);
            srcOff += 0x10;
            dstOff++;
            n--;
        } while (n);
    }
    return src->mHeight - row;
}



// @ 0x007afe10
bool cDXTCompressJobData::RunJob(CJob* job)
{
    int row = job->mSlot;
    int work = 0;
    unsigned limit = (9 < mQuality) ? 0x100 : 0x600;
    do {
        int n = DXTCompressRow(row);
        row += n;
        if (mSource->mHeight <= row) {
            void* oldCln = job->mpCleanup;
            void* oldRet = job->mpReturn;
            job->mpReturn = mOutput;
            job->mpCleanup = 0;
            if (oldCln)
                ((void (__cdecl*)(void*))oldCln)(oldRet);
            if (mMessageID) {
                IMsg* s = (IMsg*)FUN_0067dcc0();
                s->v6((void*)mMessageID, mMessage, 0, 0);
            }
            return true;
        }
        work += mSource->mWidth >> 2;
    } while (work < (int)limit);
    job->mSlot = row;
    return job->Continuation((void*)&FUN_007b0030, this);
}



// @ 0x007aff00
bool WriteImageDataAsTexture(void* ppData, int a, int b, void** out)
{
    cImageDataRaw* img = *(cImageDataRaw**)(*(void**)ppData);
    unsigned fmt = img->mFormat;
    unsigned dxt;
    if (fmt == 2)        dxt = 0x15;
    else if (fmt == 4)   dxt = 0x31545844;
    else if (fmt == 5)   dxt = 0x33545844;
    else if (fmt == 6)   dxt = 0x35545844;
    else                 return false;
    IFac* fac = (IFac*)FUN_0067dd60();
    void* tex = fac->v15(a, b, img->mWidth, img->mHeight,
                         ((int*)ppData)[1] - *(int*)ppData >> 2, 8, dxt, 0);
    if (tex)
        _InterlockedExchange((volatile long*)((char*)tex + 8), 1 + *(long*)((char*)tex + 8));
    if (!tex)
        return false;
    if ((*((unsigned char*)tex + 4) & 1) == 0) {
        IFac* f2 = (IFac*)FUN_0067dd60();
        f2->v13(tex);
    }
    int n = ((int*)ppData)[1] - *(int*)ppData >> 2;
    for (int i = 0; i < n; ++i)
        ((RasterOps*)*(void**)tex)->GetMipSize(*(void**)(*(int*)(*(int*)ppData + i*4) + 0x28), i);
    *out = tex;
    return true;
}



// @ 0x007b07e0
SP::cTexturePreload::cTexturePreload(int n)
{
    if (n >= 0) {
        ((VecReserve*)&mComplete)->Reserve(n);
        ((VecReserve*)&mInProgress)->Reserve(n);
    }
}



// @ 0x007b0980
void** VecAssign(void** self, void** other)
{
    if (other != self) {
        int n = (int)((char*)other[1] - (char*)other[0]) >> 2;
        if ((int)((char*)self[2] - (char*)self[0]) >> 2 < n) {
            void* p = ((VecGrow*)self)->Grow(n, other[0], other[1]);
            if (self[0] && *((int*)self[0] - 1))
                EAFree(self[0]);
            self[2] = (char*)p + n*4;
            self[1] = (char*)p + n*4;
            self[0] = p;
        } else {
            int cur = (int)((char*)self[1] - (char*)self[0]) >> 2;
            if (cur < n) {
                ((VecCore*)self)->DestroyRange(other[0], (char*)other[0] + cur*4);
                ((VecAssignOp*)self)->Assign(0, (char*)other[0] + cur*4, other[1], self[1], 0);
                self[1] = (char*)self[0] + n*4;
            } else {
                ((VecCore*)other)->DestroyRange(other[0], other[1]);
                ((VecCore*)self)->DestroyRange(self[0], self[1]);
                self[1] = (char*)self[0] + n*4;
            }
        }
    }
    return self;
}


// @ 0x007b0a70
void C20::grow(T20* pos, const T20& v)
{
    T20* e = end;
    if (e != cap) {
        T20* src = pos;
        if (pos <= &v && &v < e)
            src = (T20*)((char*)&v + 0x20);
        if (e) {
            e->a = e[-1].a; e->b = e[-1].b; e->c = e[-1].c; e->d = e[-1].d;
            e->e = e[-1].e; e->f = e[-1].f; e->g = e[-1].g; e->h = e[-1].h;
        }
        MoveNodes2(pos, (char*)e - 0x20, e);
        *pos = v;
        end = (T20*)((char*)e + 0x20);
        return;
    }
    int n = (int)(e - begin);
    n = (n == 0) ? 1 : n * 2;
    T20* p = n ? (T20*)EAAlloc(n << 5, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    T20* q = (T20*)MoveNodes(begin, pos, p);
    if (q)
        *q = v;
    T20* ne = (T20*)MoveNodes(pos, e, (char*)q + 0x20);
    if (begin && *((int*)begin - 1))
        EAFree(begin);
    end = ne;
    cap = (T20*)((char*)p + n*0x20);
    begin = p;
}


// @ 0x007b0da0
void C4::assign(void** first, void** last)
{
    int n = (int)((char*)last - (char*)first) >> 2;
    if ((int)((char*)cap - (char*)begin) >> 2 < n) {
        void** p = (void**)DoCopy4(first, last, 0);   // reuse as grow helper FUN_007b0920
        DestroyElems(begin, end);
        if (begin && *((int*)begin - 1))
            EAFree(begin);
        void** ne = (void**)((char*)p + n*4);
        begin = p; end = ne; cap = ne;
        return;
    }
    int cur = (int)((char*)end - (char*)begin) >> 2;
    if (n <= cur) {
        void** ne = (void**)DoCopy4(first, last, begin);
        DestroyElems(ne, end);
        end = ne;
        return;
    }
    void** mid = (void**)((char*)first + cur*4);
    DoCopy4(first, mid, begin);
    CopyRefRange4(mid, last, end);
    end = (void**)((char*)end + (n - cur)*4);
}


// @ 0x007b0f40
void C20::push_back(const T20& v)
{
    T20* p = end;
    if (p < cap) {
        end = p + 1;
        if (p)
            *p = v;
    } else {
        grow(p, v);
    }
}


// @ 0x007b1040
void C20::resize(int n)
{
    int cnt = (int)(end - begin);
    if (n > cnt) {
        char tmp[0x20];
        C20_InsertTail(this, end, n - cnt, tmp);
    } else {
        T20* ne = begin + n;
        RemoveIf(end, end, ne);
        end = (T20*)((char*)end - ((char*)end - (char*)ne));
    }
}


// @ 0x007b10a0
int C20::Alloc()
{
    if (freeBegin != freeEnd) {
        int v = freeEnd[-1];
        freeEnd--;
        return v;
    }
    int n = (int)(end - begin);
    resize(n + 1);
    return n;
}

// @ 0x007b1da0
void W1da0::f(S3* p)
{
    IFac_s007b_19c0* fac = (IFac_s007b_19c0*)FUN_0067dd60();
    Handler(fac->v7(*p, 0));
}

// @ 0x007b1e70
void W1e70::f(void* a, void* b)
{ helper(0, a, b); }
