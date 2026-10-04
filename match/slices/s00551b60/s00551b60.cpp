// Slice s00551b60: SP::Pollen::cAssetMetadata feed update helpers, metadata lookup by key,
// and EASTL hash_map / string instances used by SP::Pollen.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

template <int N> inline void ScratchSlots() { uint32_t s[N]; }
inline void* operator new(unsigned int, void* p) { return p; }

extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* p);

namespace EA {
namespace Allocator {
class ZoneObject {
public:
    virtual ~ZoneObject();
    static void* operator new(unsigned int n, const char* pName, int flags = 0, unsigned int debugFlags = 0, const char* pFile = 0, int line = 0);  // 0x00926020
    static void operator delete(void* p);
};
}
namespace Thread {
template <class T> class AtomicInt {
public:
    AtomicInt(T x = 0) { SetValue(x); }
    void SetValue(T n) { _InterlockedExchange((long*)&mValue, n); }
    volatile T mValue;
};
struct MutexParameters;
class Mutex {
public:
    Mutex(const MutexParameters* pParameters = 0, bool bDefaultParameters = true);   // 0x009222A0
    ~Mutex();                                                                          // 0x00922130
    int Lock(const void* pTimeoutAbsolute);                                            // 0x009221B0
    int Unlock();                                                                      // 0x00922270
    uint32_t mData[0x30 / 4];
};
}
template <class T, class C, int B> class RefCounted : public T {
public:
    RefCounted() : mRefCount(0) {}
    virtual int AddRef();
    virtual int Release();
    C mRefCount;
};
class Stopwatch {
public:
    Stopwatch(int units, bool bStartImmediately = false);   // 0x0093A560
    static uint64_t GetStopwatchCycle() {
        int64_t nReturnValue;
        QueryPerformanceCounter(&nReturnValue);
        const uint64_t nCycle = (uint64_t)nReturnValue;
        return nCycle;
    }
    bool IsRunning() const { return mnStartTime != 0; }
    void Reset() { mnStartTime = 0; mnTotalElapsedTime = 0; }
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
};
class LimitStopwatch : public Stopwatch {
public:
    LimitStopwatch(int units, uint32_t nLimit = 0, bool bStartImmediately = false) : Stopwatch(units, false) {
        SetTimeLimit(nLimit, bStartImmediately);
    }
    void SetTimeLimit(uint32_t nLimit, bool bStartImmediately);   // 0x0093A480
    bool IsTimeUp() const { return (int64_t)(mnEndTime - GetStopwatchCycle()) < 0; }
    uint64_t mnEndTime;
};
namespace Messaging {
class IHandler {
public:
    virtual ~IHandler() {}
    virtual bool HandleMessage(uint32_t messageId, void* pMessage) = 0;
};
class IServer {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void AddHandler(IHandler* pHandler, uint32_t messageId);                     // 0x24
    virtual void v10();
    virtual void RemoveHandler(IHandler* pHandler, uint32_t messageId, int priority);    // 0x2c
};
IServer* GetServer();   // 0x00883860
}
namespace ResourceMan {
struct Key {
    uint32_t mInstance;
    uint32_t mType;
    uint32_t mGroup;
};
inline bool operator==(const Key& a, const Key& b) { return a.mInstance == b.mInstance && a.mType == b.mType && a.mGroup == b.mGroup; }
struct ResourceKey : public Key {
    ResourceKey(uint64_t instance, uint32_t type, uint32_t group) { mInstance = (uint32_t)instance; mType = type; mGroup = group; }
};
class ResourceObject {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v2();
    virtual void* Cast(uint32_t typeId);
};
template <class T> class ResourcePtr {
public:
    ResourcePtr() : mpObject(0) {}
    ~ResourcePtr() { if (mpObject) mpObject->Release(); }
    T** AsPPTypeParam() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    T* mpObject;
};
class Factory : public RefCounted<Allocator::ZoneObject, Thread::AtomicInt<int>, 1> {
public:
    virtual uint32_t GetSupportedTypes(uint32_t* pTypes, uint32_t count) const = 0;
};
class IResourceManager {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(const Key& key, ResourceObject** ppResource, int, int, int, int);   // 0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16();
    virtual void RegisterFactory(bool bRegister, Factory* pFactory, uint32_t group);  // 0x44
};
IResourceManager* GetManager();   // 0x0067DCD0
}
}
using EA::ResourceMan::Key;

namespace eastl {
void EASTLFree(void* p);   // 0x00F47380
struct allocator {
    allocator() {}
    void deallocate(void* p, uint32_t) { void* const pMemory = p; EASTLFree(pMemory); }
};
template <class T> struct equal_to { equal_to() {} bool operator()(const T& a, const T& b) const { return a == b; } };
template <class T> struct hash { uint32_t operator()(T val) const { return (uint32_t)val; } };
template <> struct hash<Key> { uint32_t operator()(const Key& k) const { return k.mInstance ^ k.mGroup; } };
template <class P> struct use_first { const typename P::first_type& operator()(const P& x) const { return x.first; } };
template <class K> struct use_self { const K& operator()(const K& x) const { return x; } };
struct mod_range_hashing {};
struct default_ranged_hash {};
struct prime_rehash_policy {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
};
struct true_type {};

template <class V> struct hash_node {
    V mValue;
    hash_node* mpNext;
};
template <class Node> struct hashtable_iterator_base {
    Node* mpNode;
    Node** mpBucket;
    hashtable_iterator_base(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
    void increment_bucket() {
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
};
template <class Node> struct hashtable_iterator : public hashtable_iterator_base<Node> {
    hashtable_iterator(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base<Node>(pNode, pBucket) {}
    hashtable_iterator(Node** pBucket) : hashtable_iterator_base<Node>(*pBucket, pBucket) {}
    hashtable_iterator(const hashtable_iterator& x) : hashtable_iterator_base<Node>(x.mpNode, x.mpBucket) {}
};
template <class Node> struct hashtable_const_iterator : public hashtable_iterator_base<Node> {
    hashtable_const_iterator(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base<Node>(pNode, pBucket) {}
    hashtable_const_iterator(Node** pBucket) : hashtable_iterator_base<Node>(*pBucket, pBucket) {}
};
template <class Node> inline bool operator!=(const hashtable_iterator_base<Node>& a, const hashtable_iterator_base<Node>& b) { return a.mpNode != b.mpNode; }
template <class Node> struct insert_return_type {
    hashtable_iterator<Node> first;
    bool second;
};

template <class T1, class T2> struct pair {
    typedef T1 first_type;
    typedef T2 second_type;
    T1 first;
    T2 second;
    pair(const T1& x, const T2& y) : first(x), second(y) {}
    template <class U, class V> pair(const pair<U, V>& p) : first(p.first), second(p.second) {}
};
template <class T1, class T2> inline pair<T1, T2> make_pair(T1 a, T2 b) { return pair<T1, T2>(a, b); }

template <class K, class V, class EK> class hashtable {
public:
    typedef V value_type;
    typedef hash_node<V> node_type;
    typedef hashtable_iterator<node_type> iterator;
    typedef hashtable_const_iterator<node_type> const_iterator;
    hashtable(uint32_t nBucketCount, const hash<K>& h1, const mod_range_hashing& h2, const default_ranged_hash& h,
              const equal_to<K>& eq, const EK& ek, const allocator& a);
    ~hashtable() {
        clear();
        DoFreeBuckets(mpBucketArray, mnBucketCount);
    }
    void clear() {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    void DoFreeNode(node_type* pNode) { mAllocator.deallocate(pNode, sizeof(node_type)); }
    void DoFreeNodes(node_type** pNodeArray, uint32_t n);
    void DoFreeBuckets(node_type** pBucketArray, uint32_t n) {
        if (n > 1)
            mAllocator.deallocate(pBucketArray, (n + 1) * sizeof(node_type*));
    }
    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
    const_iterator end() const { return const_iterator(mpBucketArray + mnBucketCount); }
    const_iterator find(const K& k) const {
        const uint32_t c = (uint32_t)m_h1(k);
        const uint32_t n = c % mnBucketCount;
        node_type* const pNode = DoFindNode(mpBucketArray[n], k, c);
        return pNode ? const_iterator(pNode, mpBucketArray + n) : const_iterator(mpBucketArray + mnBucketCount);
    }
    iterator find(const K& k) {
        const uint32_t c = (uint32_t)m_h1(k);
        const uint32_t n = c % mnBucketCount;
        node_type* const pNode = DoFindNode(mpBucketArray[n], k, c);
        return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
    }
    node_type* DoFindNode(node_type* pNode, const K& k, uint32_t c) const {
        for (; pNode; pNode = pNode->mpNext) {
            if (m_equal(k, m_extract(pNode->mValue)))
                return pNode;
        }
        return 0;
    }
    insert_return_type<node_type> DoInsertValue(const value_type& value, true_type);
    insert_return_type<node_type> insert(const value_type& value) { return DoInsertValue(value, true_type()); }
    uint32_t erase(const K& k);

    EK m_extract;
    equal_to<K> m_equal;
    hash<K> m_h1;
    mod_range_hashing m_h2;
    node_type** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    prime_rehash_policy mRehashPolicy;
    allocator mAllocator;
};
template <class K, class T> class hash_map : public hashtable<K, pair<const K, T>, use_first<pair<const K, T> > > {
public:
    typedef hashtable<K, pair<const K, T>, use_first<pair<const K, T> > > base_type;
    typedef pair<const K, T> value_type;
    explicit hash_map(const allocator& a = allocator())
        : base_type(0, hash<K>(), mod_range_hashing(), default_ranged_hash(), equal_to<K>(), use_first<value_type>(), a) {}
    typedef typename base_type::iterator iterator;
    T& operator[](const K& key) {
        ScratchSlots<13>();
        iterator itHashtable(base_type::find(key));
        if (itHashtable != base_type::end())
            return itHashtable.mpNode->mValue.second;
        return base_type::insert(value_type(key, T())).first.mpNode->mValue.second;
    }
};
template <class K> class hash_set : public hashtable<K, K, use_self<K> > {
public:
    explicit hash_set(const allocator& a = allocator())
        : hashtable<K, K, use_self<K> >(0, hash<K>(), mod_range_hashing(), default_ranged_hash(), equal_to<K>(), use_self<K>(), a) {}
};
}

namespace eastl {
template <class K, class V, class EK>
void hashtable<K, V, EK>::DoFreeNodes(node_type** pNodeArray, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        node_type* pNode = pNodeArray[i];
        while (pNode) {
            node_type* const pTempNode = pNode;
            pNode = pNode->mpNext;
            DoFreeNode(pTempNode);
        }
        pNodeArray[i] = 0;
    }
}
}
extern "C" unsigned int strlen(const char*);
extern "C" int memcmp(const void*, const void*, unsigned int);
#pragma intrinsic(strlen, memcmp)

namespace EA { namespace DateTime {
class DateTime {
public:
    DateTime(int timeFrame) { Set(timeFrame); }
    void Set(int timeFrame);   // 0x0092E3D0
    int64_t mnSeconds;
};
} }

namespace eastl {
template <class T> struct char_traits_len;
template <class T> struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;

    basic_string(const basic_string& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
    basic_string(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p, p + CharStrlen(p)); }
    ~basic_string() { DeallocateSelf(); }
    static uint32_t CharStrlen(const char* p) { return strlen(p); }
    void RangeInitialize(const T* pBegin, const T* pEnd);   // 0x0047D390
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
    }
    void DoFree(T* p, uint32_t n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    const T* data() const { return mpBegin; }
    const T* c_str() const { return mpBegin; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    basic_string& operator=(const basic_string& x) {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    basic_string& assign(const T* pBegin, const T* pEnd);   // 0x00423650
    basic_string& assign(const T* p, uint32_t n) { return assign(p, p + n); }
    T* erase(T* pBegin, T* pEnd);                            // 0x0042E2F0
    basic_string& append(uint32_t n, T c);                   // 0x0042D2E0
    void resize(uint32_t n, T c);
};
typedef basic_string<char> string;
typedef basic_string<wchar_t> string16;

// 0x00554FB0
template <class T> inline bool operator==(const basic_string<T>& a, const basic_string<T>& b)
{
    return ((a.size() == b.size()) && (memcmp(a.data(), b.data(), (unsigned int)a.size()) == 0));
}
template <class T> bool operator==(const basic_string<T>& a, const T* p);   // 0x00555020

template <class InputIterator, class OutputIterator>
inline OutputIterator copy_impl(InputIterator first, InputIterator last, OutputIterator result)
{
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}
template <class InputIterator, class OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
    const bool elem = false;  // (names chosen to reproduce the /Od slot order)
    const bool h = false;
    const bool p33 = false;
    return copy_impl(first, last, result);
}

struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
};
template <class T> struct vector {
    typedef T* iterator;
    typedef const T* const_iterator;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    iterator begin() { return mpBegin; }
    iterator end() { return mpEnd; }
    const_iterator begin() const { return mpBegin; }
    const_iterator end() const { return mpEnd; }
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void DoInsertValue(iterator position, const T& value);   // 0x00554820
    iterator erase(iterator position) {
        if ((position + 1) < mpEnd)
            eastl::copy(position + 1, mpEnd, position);
        --mpEnd;
        mpEnd->~T();
        return position;
    }
    iterator erase(iterator first, iterator last);   // 0x00554B60 (slice s00553cc0)
    void clear() {
        ScratchSlots<5>();   // dead slots of the declined inline erase(first, last)
        erase(mpBegin, mpEnd);
    }
};

template <class ForwardIterator>
inline void destruct(ForwardIterator first, ForwardIterator last)
{
    for (; first < last; ++first)
        first->~basic_string();
}

template <class InputIterator, class T>
inline InputIterator find(InputIterator first, InputIterator last, const T& value)
{
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}

// @ 0x00552800 ?resize@?$basic_string@_W@eastl@@QAEXI_W@Z
template <class T> void basic_string<T>::resize(uint32_t n, T c)
{
    const uint32_t s = size();
    if (n < s)
        erase(mpBegin + n, mpEnd);
    else if (n > s)
        append(n - s, c);
}
template void basic_string<wchar_t>::resize(uint32_t, wchar_t);
// @ 0x005527A0 ?resize@?$basic_string@D@eastl@@QAEXID@Z
template void basic_string<char>::resize(uint32_t, char);
}

namespace SP {
namespace Feed {
struct AtomEntry {
    eastl::string mID;                       // 0x00
    uint64_t mnAssetID;                      // 0x10
    eastl::string16 mTitle;                  // 0x18
    int64_t mUpdated;                        // 0x28
    uint32_t pad30[(0xD0 - 0x30) / 4];
    eastl::string16 mSummary;                // 0xD0
    eastl::vector<eastl::string16> mTags;    // 0xE0
    uint32_t padF4[(0x110 - 0xF4) / 4];
    bool mbAssembled;                        // 0x110
};
}
uint64_t ParseAssetID(const char* pID);      // 0x005418C0

namespace Pollen {
extern const char* kAssembledContentTag;     // "tag:spore.com,2006:AssembledContent"

class cAssetMetadata : public EA::ResourceMan::ResourceObject {
public:
    const uint64_t& GetAssetID() const;              // 0x005507A0
    const Key& GetParentKey() const;                 // 0x005507E0
    const uint64_t& GetParentAssetID() const;        // 0x00550800
    const uint64_t& GetOriginalParentAssetID() const;// 0x00550820
    bool IsShared() const;                           // 0x00550970
    const wchar_t* GetName() const;                  // 0x00414E10
    void SetParentAssetID(uint64_t id);
    void SetOriginalParentAssetID(uint64_t id);
    bool UpdateFromEntry(const Feed::AtomEntry* pEntry, const eastl::string& feedURI);
    bool RemoveFeedURI(const eastl::string& feedURI);

    uint32_t pad4[(0x18 - 0x04) / 4];
    uint64_t mnAssetID;                              // 0x18
    Key mLocalKey;                                   // 0x20
    Key mParentKey;                                  // 0x2C
    uint64_t mnParentAssetID;                        // 0x38
    uint64_t mnOriginalParentAssetID;                // 0x40
    int64_t mnTimeStamp;                             // 0x48
    EA::DateTime::DateTime mLastModified;            // 0x50
    uint32_t pad58[(0x78 - 0x58) / 4];
    eastl::string16 mNameStr;                        // 0x78
    eastl::string16 mSummaryStr;                     // 0x88
    eastl::vector<eastl::string> mFeedURITable;      // 0x98
    eastl::vector<eastl::string16> mTagList;         // 0xAC
};

template <class T> T* object_cast(const EA::ResourceMan::ResourcePtr<EA::ResourceMan::ResourceObject>& p);   // 0x00421F60
template <class T> T* object_cast(EA::ResourceMan::ResourceObject* p);                                         // 0x00554140
void* GetPollinator();                                                                                         // 0x0067CB30

template <class T> class AutoRefCount {
public:
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T* detach() { T* const pTemp = mpObject; mpObject = 0; return pTemp; }
    T* mpObject;
};

// @ 0x00551B60
void cAssetMetadata::SetParentAssetID(uint64_t id)
{
    mnParentAssetID = id;
}

// @ 0x00551B80
void cAssetMetadata::SetOriginalParentAssetID(uint64_t id)
{
    mnOriginalParentAssetID = id;
}

// @ 0x00551BA0
bool cAssetMetadata::UpdateFromEntry(const Feed::AtomEntry* pEntry, const eastl::string& feedURI)
{
    bool bChanged = false;
    ScratchSlots<1>();
    if (pEntry) {
        const uint64_t nAssetID = ParseAssetID(pEntry->mID.c_str());
        if (nAssetID == mnAssetID) {
            if (eastl::find(mFeedURITable.begin(), mFeedURITable.end(), feedURI) == mFeedURITable.end()) {
                mFeedURITable.push_back(feedURI);
                EA::DateTime::DateTime now(1);
                mLastModified = now;
                bChanged = true;
            }
            if (pEntry->mbAssembled) {
                if (eastl::find(mFeedURITable.begin(), mFeedURITable.end(), kAssembledContentTag) == mFeedURITable.end())
                    mFeedURITable.push_back(eastl::string(kAssembledContentTag));
            }
            if (mnTimeStamp < pEntry->mUpdated) {
                if (pEntry->mTitle.size() < 0x100)
                    mNameStr = pEntry->mTitle;
                else
                    mNameStr.assign(pEntry->mTitle.data(), 0x100);
                if (pEntry->mSummary.size() < 0x1000)
                    mSummaryStr = pEntry->mSummary;
                else
                    mSummaryStr.assign(pEntry->mSummary.data(), 0x1000);
                mTagList.clear();
                for (eastl::vector<eastl::string16>::const_iterator itTag = pEntry->mTags.begin(), itTagEnd = pEntry->mTags.end(); itTag != itTagEnd; ++itTag)
                    mTagList.push_back(*itTag);
                bChanged = true;
            }
        }
    }
    return bChanged;
}

// @ 0x00551FF0
bool cAssetMetadata::RemoveFeedURI(const eastl::string& feedURI)
{
    bool removed = false;
    eastl::vector<eastl::string>::iterator pos = eastl::find(mFeedURITable.begin(), mFeedURITable.end(), feedURI);
    if (pos != mFeedURITable.end()) {
        mFeedURITable.erase(pos);
        removed = true;
    }
    return removed;
}

// @ 0x00552080
bool GetParentServerID(cAssetMetadata* pMetadata, uint64_t* pParentID, uint64_t* pOriginalID)
{
    bool bResult = true;
    uint64_t parentID = (uint64_t)-1;
    uint64_t originalID = (uint64_t)-1;
    if (pMetadata) {
        Key parentKey = pMetadata->GetParentKey();
        cAssetMetadata* pParent = 0;
        int nMaxDepth = 32;
        if (parentKey.mInstance)
            bResult = false;
        while (parentKey.mInstance && parentID == (uint64_t)-1) {
            if (parentKey.mInstance) {
                EA::ResourceMan::ResourcePtr<EA::ResourceMan::ResourceObject> pResource;
                EA::ResourceMan::ResourceKey metaKey(parentKey.mInstance, 0x030BDEE3, parentKey.mGroup);
                if (EA::ResourceMan::GetManager()->GetResource(metaKey, pResource.AsPPTypeParam(), 0, 0, 0, 0)) {
                    bResult = true;
                    pParent = object_cast<cAssetMetadata>(pResource);
                    parentKey = pParent->GetParentKey();
                    parentID = pParent->GetAssetID();
                    if (pParent->GetOriginalParentAssetID() != (uint64_t)-1)
                        originalID = pParent->GetOriginalParentAssetID();
                    if (!parentKey.mInstance && parentID == (uint64_t)-1)
                        parentID = pParent->GetParentAssetID();
                } else {
                    if (pParent)
                        parentID = pParent->GetParentAssetID();
                    break;
                }
            }
            if (--nMaxDepth == 0) {
                if (parentID == (uint64_t)-1 && pParent)
                    parentID = pParent->GetParentAssetID();
                break;
            }
        }
        if (parentID == (uint64_t)-1)
            parentID = pMetadata->GetParentAssetID();
        if (originalID == (uint64_t)-1) {
            if (pMetadata->GetOriginalParentAssetID() != (uint64_t)-1)
                originalID = pMetadata->GetOriginalParentAssetID();
            else
                originalID = parentID;
        }
        *pParentID = parentID;
        *pOriginalID = originalID;
    }
    return bResult;
}

// @ 0x00552300
int GetAssetState(const Key& key)
{
    void* pPollinator = GetPollinator();
    if (pPollinator) {
        Key metaKey = key;
        metaKey.mType = 0x030BDEE3;
        EA::ResourceMan::ResourcePtr<EA::ResourceMan::ResourceObject> pObject;
        EA::ResourceMan::IResourceManager* pResourceMan = EA::ResourceMan::GetManager();
        uint32_t nFlags = 0;
        uint64_t nServerID = (uint64_t)-1;
        if (pResourceMan->GetResource(metaKey, pObject.AsPPTypeParam(), 0, 0, 0, 0)) {
            cAssetMetadata* pMetadata = object_cast<cAssetMetadata>(pObject);
            if (pMetadata) {
                if (pMetadata->GetAssetID() < 0xFFFFFFFF)
                    return 0;
                if (pMetadata->IsShared())
                    return 1;
            }
        }
        return 2;
    }
    return 0;
}

// @ 0x00552450
bool GetAssetMetadata(const Key& key, cAssetMetadata** ppMetadata)
{
    EA::ResourceMan::ResourcePtr<EA::ResourceMan::ResourceObject> pResource;
    EA::ResourceMan::ResourceKey metaKey(key.mInstance, 0x030BDEE3, key.mGroup);
    if (EA::ResourceMan::GetManager()->GetResource(metaKey, pResource.AsPPTypeParam(), 0, 0, 0, 0)) {
        AutoRefCount<cAssetMetadata> pMetadata(object_cast<cAssetMetadata>(pResource));
        if (pMetadata) {
            if (ppMetadata)
                *ppMetadata = pMetadata.detach();
            return true;
        }
    }
    return false;
}

// @ 0x00552580
const wchar_t* GetAssetName(const Key& key)
{
    EA::ResourceMan::ResourceKey metaKey(key.mInstance, 0x030BDEE3, key.mGroup);
    EA::ResourceMan::ResourcePtr<EA::ResourceMan::ResourceObject> pRes;
    EA::ResourceMan::GetManager()->GetResource(metaKey, pRes.AsPPTypeParam(), 0, 0, 0, 0);
    cAssetMetadata* pMetadata = object_cast<cAssetMetadata>(pRes.mpObject);
    return pMetadata ? pMetadata->GetName() : 0;
}
}
}

namespace eastl {
// find() for this map is declined-inline in the original; declared here so the 13-dword hole can be placed explicitly.
template <> hashtable<uint32_t, pair<const uint32_t, uint64_t>, use_first<pair<const uint32_t, uint64_t> > >::iterator
hashtable<uint32_t, pair<const uint32_t, uint64_t>, use_first<pair<const uint32_t, uint64_t> > >::find(const uint32_t& k);
}
// EASTL template instances
// @ 0x00552650 hash_map<uint64_t, Key>::hash_map(const allocator&)
// @ 0x005528C0 hashtable<uint64_t, ...>::find(const uint64_t&) const
// @ 0x005529D0 hashtable<uint64_t, ...>::find(const uint64_t&)
template class eastl::hash_map<uint64_t, Key>;
template class eastl::hashtable<uint64_t, eastl::pair<const uint64_t, Key>, eastl::use_first<eastl::pair<const uint64_t, Key> > >;
// @ 0x005526A0 hash_map<uint32_t, uint64_t>::operator[]
template class eastl::hash_map<uint32_t, uint64_t>;
// @ 0x00552750 hashtable_iterator_base::increment_bucket
template struct eastl::hashtable_iterator_base<eastl::hash_node<eastl::pair<const uint64_t, Key> > >;
