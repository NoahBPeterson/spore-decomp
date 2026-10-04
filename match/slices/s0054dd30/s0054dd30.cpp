// Slice s0054dd30: SP::Pollen::cAssetDirectory (Pollinator asset id <-> resource key directory)
// and its cAssetMetadataResourceFactory.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
// EASTL notes: hashtable::find and ~hashtable are inline but cl /Ob1 declines them; callers then
// reserve the declined callee's frame, which reproduces the original's dead stack slots.
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

namespace SP {
namespace Pollen {
class cAssetDirectory;

class cAssetMetadataResourceFactory : public EA::ResourceMan::Factory {
public:
    cAssetMetadataResourceFactory(cAssetDirectory* pAssetDir) : mpAssetDir(pAssetDir) {}
    virtual uint32_t GetSupportedTypes(uint32_t* pTypes, uint32_t count) const;
    cAssetDirectory* mpAssetDir;
};

typedef eastl::hash_map<uint64_t, Key> LocalKeyMap;
typedef eastl::hash_map<Key, uint64_t> ServerIdMap;
typedef eastl::hash_set<uint64_t> AssetIdSet;
typedef eastl::hash_map<uint32_t, uint64_t> AuthorMap;

class cAssetDirectory : public EA::Messaging::IHandler {
public:
    cAssetDirectory();
    ~cAssetDirectory();
    bool Init();
    bool Shutdown();
    virtual bool HandleMessage(uint32_t messageId, void* pMessage);
    bool RestoreMappings();   // 0x0054FB00
    void SaveMappings();      // 0x0054F0F0
    void FlushMappings();     // 0x0054F1A0
    bool AddMapping(uint64_t serverId, const Key& key);
    bool GetLocalKey(uint64_t serverId, Key* pKey) const;
    bool GetServerId(const Key& key, uint64_t* pServerId, bool bLoad) const;
    bool IsPending(uint64_t id) const;
    void SetPending(uint64_t id, bool bPending);
    bool IsPending2(uint64_t id) const;
    void AddPending2(uint64_t id);
    void SetAuthorA(uint32_t id, uint64_t v);
    uint64_t GetAuthorA(uint32_t id);
    void SetAuthorB(uint32_t id, uint64_t v);
    uint64_t GetAuthorB(uint32_t id);
    bool SetAuthorFlag(uint32_t id, bool b);
    bool GetAuthorFlag(uint32_t id);

    uint32_t mField4;                     // 0x04
    mutable EA::Thread::Mutex mMutex;             // 0x08
    bool mbInited;                        // 0x38
    LocalKeyMap mLocalKey;                // 0x3C
    ServerIdMap mServerId;                // 0x5C
    AssetIdSet mPendingAssets;            // 0x7C
    AssetIdSet mPendingAssets2;           // 0x9C
    uint32_t mnAssetWriteCount;           // 0xBC
    EA::LimitStopwatch mWriteTimer;       // 0xC0
    AuthorMap mAuthorMapA;                // 0xE0
    AuthorMap mAuthorMapB;                // 0x100
};

class cAssetMetadata {
public:
    const uint64_t& GetServerID() const;   // 0x005507A0
};
template <class T> T* object_cast(const EA::ResourceMan::ResourcePtr<EA::ResourceMan::ResourceObject>& p);   // 0x00421F60
class cAutoLock {
public:
    cAutoLock(EA::Thread::Mutex& m) : mMutex(m) { mMutex.Lock(kInfinite); }
    ~cAutoLock() { mMutex.Unlock(); }
    EA::Thread::Mutex& mMutex;
    static const char kInfinite[];
};

// @ 0x0054DD30
cAssetMetadataResourceFactory* CreateMetadataFactory(cAssetDirectory* pDir)
{
    return new ("Pollinator") cAssetMetadataResourceFactory(pDir);
}

// @ 0x0054DDC0
uint32_t cAssetMetadataResourceFactory::GetSupportedTypes(uint32_t* pTypes, uint32_t count) const
{
    if (count > 0)
        pTypes[0] = 0x030BDEE3;
    return 1;
}

// @ 0x0054DDF0
cAssetDirectory::cAssetDirectory()
    : mbInited(false), mnAssetWriteCount(0), mWriteTimer(5, 2)
{
}

// @ 0x0054DEF0
// NONMATCHING: the original omits the vptr store at the start of the destructor (only the base
// IHandler vptr is restored at the end); 21 bytes differ.
cAssetDirectory::~cAssetDirectory()
{
}

// @ 0x0054DF60
bool cAssetDirectory::Init()
{
    if (!mbInited) {
        EA::ResourceMan::IResourceManager* pResourceMan = EA::ResourceMan::GetManager();
        if (pResourceMan)
            pResourceMan->RegisterFactory(true, CreateMetadataFactory(this), 0);
        mbInited = RestoreMappings();
        if (mnAssetWriteCount)
            FlushMappings();
        EA::Messaging::IServer* pMessageServer = EA::Messaging::GetServer();
        if (pMessageServer) {
            pMessageServer->AddHandler(this, 0x01EE100A);
            pMessageServer->AddHandler(this, 0x0212D3E7);
            pMessageServer->AddHandler(this, 0x02319914);
        }
    }
    return mbInited;
}

// @ 0x0054E020
bool cAssetDirectory::Shutdown()
{
    mbInited = false;
    if (mnAssetWriteCount)
        FlushMappings();
    EA::Messaging::IServer* pServer = EA::Messaging::GetServer();
    if (pServer) {
        pServer->RemoveHandler(this, 0x01EE100A, -9999);
        pServer->RemoveHandler(this, 0x0212D3E7, -9999);
        pServer->RemoveHandler(this, 0x02319914, -9999);
    }
    return true;
}

// @ 0x0054E0B0
bool cAssetDirectory::HandleMessage(uint32_t messageId, void* pMessage)
{
    switch (messageId) {
    case 0x01EE100A:
        if (mnAssetWriteCount > 20) {
            SaveMappings();
            mnAssetWriteCount = 0;
        } else if (mnAssetWriteCount > 0) {
            if (!mWriteTimer.IsRunning())
                mWriteTimer.SetTimeLimit(2, true);
            else if (mWriteTimer.IsTimeUp()) {
                SaveMappings();
                mnAssetWriteCount = 0;
            }
        } else if (mWriteTimer.IsRunning())
            mWriteTimer.Reset();
        break;
    case 0x0212D3E7:
    case 0x02319914:
        if (mnAssetWriteCount > 0)
            FlushMappings();
        break;
    }
    return true;
}

// @ 0x0054E250
bool cAssetDirectory::AddMapping(uint64_t serverId, const Key& key)
{
    cAutoLock lock(mMutex);
    if (mLocalKey.insert(eastl::make_pair(serverId, key)).second) {
        eastl::insert_return_type<ServerIdMap::node_type> result = mServerId.insert(eastl::make_pair(key, serverId));
        if (result.second) {
            mnAssetWriteCount++;
            return true;
        }
        result.first.mpNode->mValue.second = serverId;
        mnAssetWriteCount++;
        return true;
    }
    return false;
}

// @ 0x0054E460
bool cAssetDirectory::GetLocalKey(uint64_t serverId, Key* pKey) const
{
    cAutoLock lock(mMutex);
    if (mbInited) {
        LocalKeyMap::const_iterator it = mLocalKey.find(serverId);
        if (it != mLocalKey.end()) {
            if (pKey)
                *pKey = it.mpNode->mValue.second;
            return true;
        }
    }
    return false;
}

// @ 0x0054E530
bool cAssetDirectory::GetServerId(const Key& key, uint64_t* pServerId, bool bLoad) const
{
    cAutoLock lock(mMutex);
    if (mbInited) {
        ServerIdMap::const_iterator it = mServerId.find(key);
        if (it != mServerId.end()) {
            if (pServerId)
                *pServerId = it.mpNode->mValue.second;
            return true;
        }
    }
    if (bLoad) {
        EA::ResourceMan::ResourceKey metaKey(key.mInstance, 0x030BDEE3, key.mGroup);
        EA::ResourceMan::ResourcePtr<EA::ResourceMan::ResourceObject> pResource;
        if (EA::ResourceMan::GetManager()->GetResource(metaKey, pResource.AsPPTypeParam(), 0, 0, 0, 0)) {
            cAssetMetadata* pMetadata = object_cast<cAssetMetadata>(pResource);
            if (pMetadata && pMetadata->GetServerID() != (uint64_t)-1 && pMetadata->GetServerID() > 0xFFFFFFFF) {
                if (pServerId)
                    *pServerId = pMetadata->GetServerID();
                return true;
            }
        }
    }
    return false;
}

// @ 0x0054E740
bool cAssetDirectory::IsPending(uint64_t id) const
{
    return mPendingAssets.find(id) != mPendingAssets.end();
}

// @ 0x0054E7B0
void cAssetDirectory::SetPending(uint64_t id, bool bPending)
{
    if (bPending)
        mPendingAssets.insert(id);
    else
        mPendingAssets.erase(id);
}

// @ 0x0054E800
bool cAssetDirectory::IsPending2(uint64_t id) const
{
    return mPendingAssets2.find(id) != mPendingAssets2.end();
}

// @ 0x0054E870
void cAssetDirectory::AddPending2(uint64_t id)
{
    if (mPendingAssets2.insert(id).second)
        mnAssetWriteCount++;
}

// @ 0x0054E8C0
void cAssetDirectory::SetAuthorA(uint32_t id, uint64_t v)
{
    mAuthorMapA[id] = v;
}

// @ 0x0054E8F0
uint64_t cAssetDirectory::GetAuthorA(uint32_t id)
{
    AuthorMap::iterator it = mAuthorMapA.find(id);
    if (it != mAuthorMapA.end())
        return it.mpNode->mValue.second;
    return 0;
}

// @ 0x0054E970
void cAssetDirectory::SetAuthorB(uint32_t id, uint64_t v)
{
    mAuthorMapB[id] = v;
}

// @ 0x0054E9A0
uint64_t cAssetDirectory::GetAuthorB(uint32_t id)
{
    AuthorMap::iterator it = mAuthorMapB.find(id);
    if (it != mAuthorMapB.end())
        return it.mpNode->mValue.second;
    return 0;
}

// @ 0x0054EA20
bool cAssetDirectory::SetAuthorFlag(uint32_t id, bool b)
{
    uint64_t v = GetAuthorB(id);
    bool bOld = (v & 0x8000000000000000ULL) == 0x8000000000000000ULL;
    if (b)
        v |= 0x8000000000000000ULL;
    else
        v &= 0x7FFFFFFFFFFFFFFFULL;
    SetAuthorB(id, v);
    return bOld;
}

// @ 0x0054EAC0
bool cAssetDirectory::GetAuthorFlag(uint32_t id)
{
    return (GetAuthorB(id) & 0x8000000000000000ULL) == 0x8000000000000000ULL;
}
}
}
