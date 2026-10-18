// src/game/SPBake/SPPollinatorAssetDirectory.cpp -- migrated from slice(s) s00849f70, s00567a90, s00551b60, s00550bd0, s0054fb00, s0054f1a0, s0054eb10, s0054dd30, s0054c780, s0054b7b0, s0054afe0 by tools/migrate/rewrite.py
// Object file: SPBake/SPPollinatorAssetDirectory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/CustomWindow.h"
#include "EA/ResourceMan/Key.h"
#include "EA/Audio/IPrimitive.h"
#include "SP/Pollen/cAssetMetadata.h"
#include "SP/Pollen/cAssetMetadataResourceFactory.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cString.h"
#include "EA/AutoRefCount.h"
#include "SP/Pollen/cAssetDirectory.h"
#include "EA/LimitStopwatch.h"
#include "EA/Thread/Mutex.h"
#include "EA/Stopwatch.h"
#include "EA/Allocator/ZoneObject.h"
#include "SP/cJob.h"
#include "EA/DateTime/DateTime.h"

// ---- items of slice s0054afe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cAssetMetadata;
void* cAssetMetadata_ctor(cAssetMetadata* p);                      // 0x550450
void* operator_new_meta(unsigned int n, const char* name, int a, unsigned b, const char* c, int d);
struct IObj10 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int* GetBounds();       // vtable slot 4
};
struct IHost {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual bool Make(void* a, void* b, int c, int d);  // vtable slot 9
    // The factory method receives the host as `this` (ECX); 4 stack args (ret 0x10).
    bool cAssetMetadataFactory_Create(struct IObj10* param2, struct IMeta** out, int param4, int param5);
};
struct IMeta {
    char pad0[8];
    uint32_t f2, f3, f4;
    virtual void s0();
    virtual void Delete();          // vtable slot 1
};
// ---- items of slice s0054afe0 end

// ---- items of slice s0054b7b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
bool  WriteU32(void* writer, const void* p, int n, int flags);   // EA::IO::WriteUint32
bool  FUN_0093ab10(void* writer, const void* p, int n, int flags); // writes 8 bytes
void* FUN_00554140(int a);                                        // 0x554140
void* FUN_00550880();                                             // 0x550880
void* FUN_00414e10(int n);                                        // 0x414e10
void* FUN_005508c0(int n);                                        // 0x5508c0
struct IMeta_s0054_b7b0 {
    virtual void Init();      // vtable slot 0
    virtual void Delete();    // vtable slot 1
};
struct IObj {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void* GetWriter();  // vtable slot 6
};
struct IWriter {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual bool WriteBytes(const void* p, int n);  // vtable slot 14 (0x38)
};
struct Stub0054b7b0 { bool FUN_0054b7b0(int param_1, IObj* param_2, int* param_3, int param_4); };
// ---- items of slice s0054b7b0 end

// ---- items of slice s0054dd30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* p);
#pragma intrinsic(_InterlockedExchange)
inline void* operator new(unsigned int, void* p) { return p; }
namespace EA {
namespace Allocator {
class ZoneObject_s0054_dd30 {
public:
    virtual ~ZoneObject_s0054_dd30();
    static void* operator new(unsigned int n, const char* pName, int flags = 0, unsigned int debugFlags = 0, const char* pFile = 0, int line = 0);  // 0x00926020
    static void operator delete(void* p);
};
}
}
namespace EA {
namespace Thread {
template <class T> class AtomicInt_s0054_dd30 {
public:
    AtomicInt_s0054_dd30(T x = 0) { SetValue(x); }
    void SetValue(T n) { _InterlockedExchange((long*)&mValue, n); }
    volatile T mValue;
};
}
}
namespace EA {
namespace Thread {
struct MutexParameters;
}
}
namespace EA {
namespace Thread {
class Mutex_s0054_dd30 {
public:
    Mutex_s0054_dd30(const MutexParameters* pParameters = 0, bool bDefaultParameters = true);   // 0x009222A0
    ~Mutex_s0054_dd30();                                                                          // 0x00922130
    int Lock(const void* pTimeoutAbsolute);                                            // 0x009221B0
    int Unlock();                                                                      // 0x00922270
    uint32_t mData[0x30 / 4];
};
}
}
namespace EA {
template <class T, class C, int B> class RefCounted_s0054_dd30 : public T {
public:
    RefCounted_s0054_dd30() : mRefCount(0) {}
    virtual int AddRef();
    virtual int Release();
    C mRefCount;
};
}
namespace EA {
class Stopwatch_s0054_dd30 {
public:
    Stopwatch_s0054_dd30(int units, bool bStartImmediately = false);   // 0x0093A560
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
}
namespace EA {
class LimitStopwatch_s0054_dd30 : public Stopwatch_s0054_dd30 {
public:
    LimitStopwatch_s0054_dd30(int units, uint32_t nLimit = 0, bool bStartImmediately = false) : Stopwatch_s0054_dd30(units, false) {
        SetTimeLimit(nLimit, bStartImmediately);  // 0x0093a480 (EA::LimitStopwatch::SetTimeLimit)
    }
    void SetTimeLimit(uint32_t nLimit, bool bStartImmediately);   // 0x0093A480
    bool IsTimeUp() const { return (int64_t)(mnEndTime - GetStopwatchCycle()) < 0; }
    uint64_t mnEndTime;
};
}
namespace EA {
namespace Messaging {
class IHandler_s0054_dd30 {
public:
    virtual ~IHandler_s0054_dd30() {}
    virtual bool HandleMessage(uint32_t messageId, void* pMessage) = 0;
};
}
}
namespace EA {
namespace Messaging {
class IServer {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void AddHandler(IHandler_s0054_dd30* pHandler, uint32_t messageId);                     // 0x24
    virtual void v10();
    virtual void RemoveHandler(IHandler_s0054_dd30* pHandler, uint32_t messageId, int priority);    // 0x2c
};
}
}
namespace EA {
namespace Messaging {
IServer* GetServer();   // 0x00883860
}
}
namespace EA {
namespace ResourceMan {
struct Key_s0054_dd30 {
    uint32_t mInstance;
    uint32_t mType;
    uint32_t mGroup;
};
}
}
namespace EA {
namespace ResourceMan {
inline bool operator==(const Key_s0054_dd30& a, const Key_s0054_dd30& b) { return a.mInstance == b.mInstance && a.mType == b.mType && a.mGroup == b.mGroup; }
}
}
namespace EA {
namespace ResourceMan {
struct ResourceKey : public Key_s0054_dd30 {
    ResourceKey(uint64_t instance, uint32_t type, uint32_t group) { mInstance = (uint32_t)instance; mType = type; mGroup = group; }
};
}
}
namespace EA {
namespace ResourceMan {
class ResourceObject {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v2();
    virtual void* Cast(uint32_t typeId);
};
}
}
namespace EA {
namespace ResourceMan {
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
}
}
namespace EA {
namespace ResourceMan {
class Factory_s0054_dd30 : public RefCounted_s0054_dd30<Allocator::ZoneObject_s0054_dd30, Thread::AtomicInt_s0054_dd30<int>, 1> {
public:
    virtual uint32_t GetSupportedTypes(uint32_t* pTypes, uint32_t count) const = 0;
};
}
}
namespace EA {
namespace ResourceMan {
class IResourceManager {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(const Key_s0054_dd30& key, ResourceObject** ppResource, int, int, int, int);   // 0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16();
    virtual void RegisterFactory(bool bRegister, Factory_s0054_dd30* pFactory, uint32_t group);  // 0x44
};
}
}
namespace EA {
namespace ResourceMan {
IResourceManager* GetManager();   // 0x0067DCD0
}
}
using EA::ResourceMan::Key_s0054_dd30;
namespace eastl {
void EASTLFree(void* p);   // 0x00F47380
}
namespace eastl {
struct allocator_s0054_dd30 {
    allocator_s0054_dd30() {}
    void deallocate(void* p, uint32_t) { void* const pMemory = p; EASTLFree(pMemory); }
};
}
namespace eastl {
template <class T> struct equal_to_s0054_dd30 { equal_to_s0054_dd30() {} bool operator()(const T& a, const T& b) const { return a == b; } };
}
namespace eastl {
template <class T> struct hash_s0054_dd30 { uint32_t operator()(T val) const { return (uint32_t)val; } };
}
namespace eastl {
template <> struct hash_s0054_dd30<Key_s0054_dd30> { uint32_t operator()(const Key_s0054_dd30& k) const { return k.mInstance ^ k.mGroup; } };
}
namespace eastl {
template <class P> struct use_first_s0054_dd30 { const typename P::first_type& operator()(const P& x) const { return x.first; } };
}
namespace eastl {
template <class K> struct use_self_s0054_dd30 { const K& operator()(const K& x) const { return x; } };
}
namespace eastl {
struct mod_range_hashing {};
}
namespace eastl {
struct default_ranged_hash {};
}
namespace eastl {
struct prime_rehash_policy_s0054_dd30 {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
};
}
namespace eastl {
struct true_type {};
}
namespace eastl {
template <class V> struct hash_node_s0054_dd30 {
    V mValue;
    hash_node_s0054_dd30* mpNext;
};
}
namespace eastl {
template <class Node> struct hashtable_iterator_base {
    Node* mpNode;
    Node** mpBucket;
    hashtable_iterator_base(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
};
}
namespace eastl {
template <class Node> struct hashtable_iterator : public hashtable_iterator_base<Node> {
    hashtable_iterator(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base<Node>(pNode, pBucket) {}
    hashtable_iterator(Node** pBucket) : hashtable_iterator_base<Node>(*pBucket, pBucket) {}
    hashtable_iterator(const hashtable_iterator& x) : hashtable_iterator_base<Node>(x.mpNode, x.mpBucket) {}
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
template <class T1, class T2> struct pair_s0054_dd30 {
    typedef T1 first_type;
    typedef T2 second_type;
    T1 first;
    T2 second;
    pair_s0054_dd30(const T1& x, const T2& y) : first(x), second(y) {}
    template <class U, class V> pair_s0054_dd30(const pair_s0054_dd30<U, V>& p) : first(p.first), second(p.second) {}
};
}
namespace eastl {
template <class T1, class T2> inline pair_s0054_dd30<T1, T2> make_pair(T1 a, T2 b) { return pair_s0054_dd30<T1, T2>(a, b); }
}
namespace eastl {
template <class K, class V, class EK> class hashtable_s0054_dd30 {
public:
    typedef V value_type;
    typedef hash_node_s0054_dd30<V> node_type;
    typedef hashtable_iterator<node_type> iterator;
    typedef hashtable_const_iterator<node_type> const_iterator;
    hashtable_s0054_dd30(uint32_t nBucketCount, const hash_s0054_dd30<K>& h1, const mod_range_hashing& h2, const default_ranged_hash& h,
              const equal_to_s0054_dd30<K>& eq, const EK& ek, const allocator_s0054_dd30& a);
    ~hashtable_s0054_dd30() {
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
    equal_to_s0054_dd30<K> m_equal;
    hash_s0054_dd30<K> m_h1;
    mod_range_hashing m_h2;
    node_type** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    prime_rehash_policy_s0054_dd30 mRehashPolicy;
    allocator_s0054_dd30 mAllocator;
};
}
namespace eastl {
template <class K, class T> class hash_map_s0054_dd30 : public hashtable_s0054_dd30<K, pair_s0054_dd30<const K, T>, use_first_s0054_dd30<pair_s0054_dd30<const K, T> > > {
public:
    typedef hashtable_s0054_dd30<K, pair_s0054_dd30<const K, T>, use_first_s0054_dd30<pair_s0054_dd30<const K, T> > > base_type;
    typedef pair_s0054_dd30<const K, T> value_type;
    explicit hash_map_s0054_dd30(const allocator_s0054_dd30& a = allocator_s0054_dd30())
        : base_type(0, hash_s0054_dd30<K>(), mod_range_hashing(), default_ranged_hash(), equal_to_s0054_dd30<K>(), use_first_s0054_dd30<value_type>(), a) {}
    typedef typename base_type::iterator iterator;
    T& operator[](const K& key) {
        iterator itHashtable(base_type::find(key));
        if (itHashtable != base_type::end())
            return itHashtable.mpNode->mValue.second;
        return base_type::insert(value_type(key, T())).first.mpNode->mValue.second;
    }
};
}
namespace eastl {
template <class K> class hash_set_s0054_dd30 : public hashtable_s0054_dd30<K, K, use_self_s0054_dd30<K> > {
public:
    explicit hash_set_s0054_dd30(const allocator_s0054_dd30& a = allocator_s0054_dd30())
        : hashtable_s0054_dd30<K, K, use_self_s0054_dd30<K> >(0, hash_s0054_dd30<K>(), mod_range_hashing(), default_ranged_hash(), equal_to_s0054_dd30<K>(), use_self_s0054_dd30<K>(), a) {}
};
}
namespace eastl {
template <class K, class V, class EK>
void hashtable_s0054_dd30<K, V, EK>::DoFreeNodes(node_type** pNodeArray, uint32_t n)
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
class cAssetDirectory_s0054_dd30;
}
}
namespace SP {
namespace Pollen {
class cAssetMetadataResourceFactory_s0054_dd30 : public EA::ResourceMan::Factory_s0054_dd30 {
public:
    cAssetMetadataResourceFactory_s0054_dd30(cAssetDirectory_s0054_dd30* pAssetDir) : mpAssetDir(pAssetDir) {}
    virtual uint32_t GetSupportedTypes(uint32_t* pTypes, uint32_t count) const;  // 0x0054ddc0 (SP::Pollen::cAssetMetadataResourceFactory::GetSupportedTypes)
    cAssetDirectory_s0054_dd30* mpAssetDir;
};
}
}
namespace SP {
namespace Pollen {
typedef eastl::hash_map_s0054_dd30<uint64_t, Key_s0054_dd30> LocalKeyMap;
}
}
namespace SP {
namespace Pollen {
typedef eastl::hash_map_s0054_dd30<Key_s0054_dd30, uint64_t> ServerIdMap;
}
}
namespace SP {
namespace Pollen {
typedef eastl::hash_set_s0054_dd30<uint64_t> AssetIdSet;
}
}
namespace SP {
namespace Pollen {
typedef eastl::hash_map_s0054_dd30<uint32_t, uint64_t> AuthorMap;
}
}
namespace SP {
namespace Pollen {
class cAssetDirectory_s0054_dd30 : public EA::Messaging::IHandler_s0054_dd30 {
public:
    cAssetDirectory_s0054_dd30();
    ~cAssetDirectory_s0054_dd30();
    bool Init();
    bool Shutdown();  // 0x0054e020 (SP::Pollen::cAssetDirectory::Shutdown)
    virtual bool HandleMessage(uint32_t messageId, void* pMessage);
    bool RestoreMappings();   // 0x0054FB00
    void SaveMappings();      // 0x0054F0F0
    void FlushMappings();     // 0x0054F1A0
    bool AddMapping(uint64_t serverId, const Key_s0054_dd30& key);
    bool GetLocalKey(uint64_t serverId, Key_s0054_dd30* pKey) const;
    bool GetServerId(const Key_s0054_dd30& key, uint64_t* pServerId, bool bLoad) const;
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
    mutable EA::Thread::Mutex_s0054_dd30 mMutex;             // 0x08
    bool mbInited;                        // 0x38
    LocalKeyMap mLocalKey;                // 0x3C
    ServerIdMap mServerId;                // 0x5C
    AssetIdSet mPendingAssets;            // 0x7C
    AssetIdSet mPendingAssets2;           // 0x9C
    uint32_t mnAssetWriteCount;           // 0xBC
    EA::LimitStopwatch_s0054_dd30 mWriteTimer;       // 0xC0
    AuthorMap mAuthorMapA;                // 0xE0
    AuthorMap mAuthorMapB;                // 0x100
};
}
}
namespace SP {
namespace Pollen {
class cAssetMetadata_s0054_dd30 {
public:
    const uint64_t& GetServerID() const;   // 0x005507A0
};
}
}
namespace SP {
namespace Pollen {
template <class T> T* object_cast(const EA::ResourceMan::ResourcePtr<EA::ResourceMan::ResourceObject>& p);   // 0x00421F60
}
}
namespace SP {
namespace Pollen {
class cAutoLock {
public:
    cAutoLock(EA::Thread::Mutex_s0054_dd30& m) : mMutex(m) { mMutex.Lock(kInfinite); }
    ~cAutoLock() { mMutex.Unlock(); }
    EA::Thread::Mutex_s0054_dd30& mMutex;
    static const char kInfinite[];
};
}
}
// ---- items of slice s0054dd30 end

// ---- items of slice s0054eb10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Mtx {
    int Lock(const void* p);   // EA::Thread::Mutex::Lock
    int Unlock();              // EA::Thread::Mutex::Unlock
};
struct Ctr {
    void F90(void* out, int key);          // 0x553090 map find
    void F9d0(void* out, const void* key); // 0x5529d0 map lower_bound
    void Fc20(const void* iter);           // 0x552c20 map erase
    void F620(const void* key);            // 0x553620 set/map find
    void F3a0(void* first, void* last);    // 0x5543a0 vector clear
    void F140(void* out);                  // 0x564140 hash find
    void FreeNodes(void* first, void* last); // 0x5687d0 hashtable DoFreeNodes
};
struct Dir {
    void F210(int ptr);        // 0x550210
    bool FUN_0054eb10(int param2, char param3);
    bool FUN_0054ed50(int param2, int param3, char param4);
    char FUN_0054efb0();
    int  FUN_0054f0f0();
};
struct CJob {
    int GetStatus();           // 0x690120
};
int*  ObjectTemplateDB();      // 0x67cb40
void  FUN_0054f1a0(int self);
void* FUN_0068f4d0();
int   FUN_006909b0();
void  FUN_0068f5a0();
struct It { int a; int b; };
// ---- items of slice s0054eb10 end

// ---- items of slice s0054f1a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const int kSaveTimeout;   // 0x013F3CB0
extern const int kSaveKey;       // 0x015E3294
extern const int kMagicA;        // 0x013F3CEC
extern const int kMagicB;        // 0x013F3CE8
namespace EA {
namespace Thread {
class Mutex_s0054_f1a0 {
public:
    int Lock(const void* pTimeoutAbsolute);   // 0x009221B0
    int Unlock();                             // 0x00922270
    uint32_t mData[0x30 / 4];
};
}
}
class IWriteStream {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13();
    virtual bool Write(const void* pData, int nSize);
};
class ISaveFile {
public:
    virtual void s0(); virtual void s1();
    virtual void Release();
    virtual void s3(); virtual void s4(); virtual void s5();
    virtual IWriteStream* GetStream();
    virtual void s7(); virtual void s8();
    virtual void Close();
};
class ISaveArea {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8();
    virtual void Close();
    virtual void s10(); virtual void s11(); virtual void s12();
    virtual bool OpenFile(const void* pKey, ISaveFile** ppOut, int a, int b, int c, int d);
};
ISaveArea* GetSaveArea(int id);   // SP::GetSaveArea 0x006B1F90
struct SaveFilePtr {
    ISaveFile* p;
    SaveFilePtr() : p(0) {}
    ~SaveFilePtr() { if (p) p->Release(); }
    ISaveFile** Reset();       // 0x0041DA30 (releases the held file, returns &p)
    ISaveFile** operator&() { return Reset(); }
    ISaveFile* operator->() const { return p; }
};
template <class Node> struct HBase {
    Node* mpNode;
    Node** mpBucket;
    HBase(Node* n, Node** b) : mpNode(n), mpBucket(b) {}
    void increment() {
        mpNode = mpNode->mpNext;
        while (mpNode == 0) {
            mpBucket = mpBucket + 1;
            mpNode = *mpBucket;
        }
    }
    __declspec(noinline) void increment_bucket() {   // eastl::hashtable_iterator_base::increment_bucket 0x00552750
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
};
template <class Node> struct HIter : public HBase<Node> {
    HIter(Node* n = 0, Node** b = 0) : HBase<Node>(n, b) {}
    HIter(Node** b) : HBase<Node>(*b, b) {}
    HIter(const HIter& x) : HBase<Node>(x.mpNode, x.mpBucket) {}
};
template <class Node> struct HIterC : public HBase<Node> {
    HIterC(Node* n = 0, Node** b = 0) : HBase<Node>(n, b) {}
    HIterC(Node** b) : HBase<Node>(*b, b) {}
    HIterC(const HIter<Node>& x) : HBase<Node>(x.mpNode, x.mpBucket) {}
    HIterC& operator++() {
        this->mpNode = this->mpNode->mpNext;
        while (this->mpNode == 0) {
            this->mpBucket = this->mpBucket + 1;
            this->mpNode = *this->mpBucket;
        }
        return *this;
    }
};
template <class Node> inline bool operator!=(const HBase<Node>& a, const HBase<Node>& b) { return a.mpNode != b.mpNode; }
template <class Node> struct HTable {
    int mPad0;
    Node** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    char mRest[0x20 - 0x10];
    __declspec(noinline) HIter<Node> begin() {                                     // 0x00564140 (out of line in the original)
        HIter<Node> it(mpBucketArray);
        if (it.mpNode == 0) it.increment_bucket();
        return it;
    }
    HIter<Node> beginInline() {
        HIter<Node> it(mpBucketArray);
        if (it.mpNode == 0) it.increment_bucket();
        return it;
    }
    HIter<Node> end() { return HIter<Node>(mpBucketArray + mnBucketCount); }
    uint32_t size() const { return mnElementCount; }
    bool empty() const { return mnElementCount == 0; }
};
struct NodeA { char v[0x18]; NodeA* mpNext; };       // 24-byte value, next at +0x18
struct NodeB { char v[0x10]; NodeB* mpNext; };       // next at +0x10
struct NodeD { char v[8]; NodeD* mpNext; };          // next at +8
struct AssetDir {
    int vtbl;
    int pad4;
    EA::Thread::Mutex_s0054_f1a0 mMutex;          // +0x08
    char pad38[0x3c - 0x38];
    HTable<NodeA> mTableA;             // +0x3c
    char pad5c[0x9c - 0x5c];
    HTable<NodeD> mTableD;             // +0x9c
    int mbBusy;                        // +0xbc
    char padc0[0xe0 - 0xc0];
    HTable<NodeB> mTableB;             // +0xe0
    HTable<NodeB> mTableC;             // +0x100

    bool Save();
};
struct MutexGuard {
    EA::Thread::Mutex_s0054_f1a0* mpMutex;
    MutexGuard(EA::Thread::Mutex_s0054_f1a0* m, const void* t) : mpMutex(m) { mpMutex->Lock(t); }
    ~MutexGuard() { mpMutex->Unlock(); }
};
// ---- items of slice s0054f1a0 end

// ---- items of slice s0054fb00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* vtbl_cAssetMetadata[];   // 0x013f3d8c (equiv t2)
extern void* vtbl_cPropertyList[];   // 0x013ebcdc (equiv t2)
extern void* vtbl_cEditorResource[]; // 0x013eb938
extern char  DAT_013ec47c[];
extern char  DAT_01667bac[];
struct MetaBase { void ctor(); };
void  FUN_00553b90(void* v);
void  FUN_00553e00(void* v);
void  FUN_00553fb0(void* v);
void  WString_FreeBuffer(void* self);                // 0x4237d0
struct Map5 {
    void F4020(void* out, int* key);   // 0x554020
    void F40d0(int* key);              // 0x5540d0
};
void  FUN_00555980(void* out, void* k);
int64_t FUN_005418c0(int a);
struct Meta {
    char pad[0x400];
    Meta();                       // 00550450
    void FUN_005506c0();          // dtor
    int64_t FUN_005508a0();
    void* FUN_00550910(unsigned idx);
    unsigned FUN_005509e0(unsigned idx);
    unsigned FUN_00550a60(unsigned idx);
    bool FUN_00550aa0(void* key);
    void FUN_00550b00(int key);
    void FUN_00550b30(int key);
    char FUN_00550b60(int key);
    Meta* Cast(int type);
};
// ---- items of slice s0054fb00 end

// ---- items of slice s00550bd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char DAT_013f027c[];
extern char DAT_013f3da0[];
void  FUN_00423820(void* self, const void* a, const void* b);   // WStr construct
void  FUN_004237d0(void* self);                                 // WStr dtor
void  FUN_0047d390(void* self, const void* a, const void* b);   // char string range ctor
void  FUN_00554170();
void  FUN_005541e0();
void  FUN_006b8f40(void* v);
int*  FUN_00607a60();                                           // AuthManager
int   FUN_0067cb30();                                           // returns something
void  FUN_00553cc0(void* v);                                    // vector<string> clear/push
void  FUN_00554b60(void* a, void* b);
void  FUN_004769b0(void* a, void* b);
void  FUN_00554760(void* a, void* b);
void  FUN_00554020(void* a, void* b);
void  operator_delete(void* p);
void  EA_DateTime_Set(int);
void  WStr_Assign(void* self, const void* a, const void* b);
char  GetParentServerID(int a, void* b, void* c);
char  AddPollinatorDebugInfo(int a, void* b, void* c);
struct WStr {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    int       mAlloc;
    void Append(const void* a, const void* b);   // 0x429580
};
void WStr_Format(void* out, const void* fmt, int arg);   // 0x41e050 cdecl
struct Meta_s0055_0bd0 {
    char pad[0x400];
    char FUN_00550b60(int key);  // 0x00550b60 (Meta::FUN_00550b60)
    char FUN_00550bd0(uint16_t* str);
    void FUN_00550cf0(WStr* out);
    char FUN_00550da0(int* param_2, int* param_3, int* param_4);
    char FUN_00551240(int* param_2, uint16_t* param_3, uint16_t* param_4, int param_5,
                      int* param_6, char param_7);
    char SetMetadata(uint32_t* param_2, int param_3, int param_4, int param_5, void* param_6,
                     uint16_t* param_7, void* param_8, uint16_t* param_9, uint16_t* param_10,
                     uint16_t* param_11, int param_12, void* param_13, char param_14);
    void FUN_005519d0(uint16_t* a, uint16_t* b, int c);
    void FUN_00551af0(int a, int b);
};
// ---- items of slice s00550bd0 end

// ---- items of slice s00551b60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned int strlen(const char*);
extern "C" int memcmp(const void*, const void*, unsigned int);
#pragma intrinsic(strlen, memcmp)
template <int N> inline void ScratchSlots() { uint32_t s[N]; }
namespace EA {
namespace Allocator {
class ZoneObject_s0055_1b60 {
public:
    virtual ~ZoneObject_s0055_1b60();
    static void* operator new(unsigned int n, const char* pName, int flags = 0, unsigned int debugFlags = 0, const char* pFile = 0, int line = 0);  // 0x00926020
    static void operator delete(void* p);
};
}
}
namespace EA {
namespace Thread {
template <class T> class AtomicInt_s0055_1b60 {
public:
    AtomicInt_s0055_1b60(T x = 0) { SetValue(x); }
    void SetValue(T n) { _InterlockedExchange((long*)&mValue, n); }
    volatile T mValue;
};
}
}
namespace EA {
template <class T, class C, int B> class RefCounted_s0055_1b60 : public T {
public:
    RefCounted_s0055_1b60() : mRefCount(0) {}
    virtual int AddRef();
    virtual int Release();
    C mRefCount;
};
}
namespace EA {
namespace ResourceMan {
struct Key_s0055_1b60 {
    uint32_t mInstance;
    uint32_t mType;
    uint32_t mGroup;
};
}
}
namespace EA {
namespace ResourceMan {
inline bool operator==(const Key_s0055_1b60& a, const Key_s0055_1b60& b) { return a.mInstance == b.mInstance && a.mType == b.mType && a.mGroup == b.mGroup; }
}
}
namespace EA {
namespace ResourceMan {
struct ResourceKey_s0055_1b60 : public Key_s0055_1b60 {
    ResourceKey_s0055_1b60(uint64_t instance, uint32_t type, uint32_t group) { mInstance = (uint32_t)instance; mType = type; mGroup = group; }
};
}
}
namespace EA {
namespace ResourceMan {
class Factory_s0055_1b60 : public RefCounted_s0055_1b60<Allocator::ZoneObject_s0055_1b60, Thread::AtomicInt_s0055_1b60<int>, 1> {
public:
    virtual uint32_t GetSupportedTypes(uint32_t* pTypes, uint32_t count) const = 0;
};
}
}
namespace EA {
namespace ResourceMan {
class IResourceManager_s0055_1b60 {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(const Key_s0055_1b60& key, ResourceObject** ppResource, int, int, int, int);   // 0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16();
    virtual void RegisterFactory(bool bRegister, Factory_s0055_1b60* pFactory, uint32_t group);  // 0x44
};
}
}
namespace EA {
namespace ResourceMan {
IResourceManager_s0055_1b60* GetManager_s0055_1b60();   // 0x0067DCD0
}
}
using EA::ResourceMan::Key_s0055_1b60;
namespace eastl {
struct allocator_s0055_1b60 {
    allocator_s0055_1b60() {}
    void deallocate(void* p, uint32_t) { void* const pMemory = p; EASTLFree(pMemory); }
};
}
namespace eastl {
template <class T> struct equal_to_s0055_1b60 { equal_to_s0055_1b60() {} bool operator()(const T& a, const T& b) const { return a == b; } };
}
namespace eastl {
template <class T> struct hash_s0055_1b60 { uint32_t operator()(T val) const { return (uint32_t)val; } };
}
namespace eastl {
template <> struct hash_s0055_1b60<Key_s0055_1b60> { uint32_t operator()(const Key_s0055_1b60& k) const { return k.mInstance ^ k.mGroup; } };
}
namespace eastl {
template <class P> struct use_first_s0055_1b60 { const typename P::first_type& operator()(const P& x) const { return x.first; } };
}
namespace eastl {
struct prime_rehash_policy_s0055_1b60 {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
};
}
namespace eastl {
template <class V> struct hash_node_s0055_1b60 {
    V mValue;
    hash_node_s0055_1b60* mpNext;
};
}
namespace eastl {
template <class Node> struct hashtable_iterator_base_s0055_1b60 {
    Node* mpNode;
    Node** mpBucket;
    hashtable_iterator_base_s0055_1b60(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
    void increment_bucket() {
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
};
}
namespace eastl {
template <class Node> struct hashtable_iterator_s0055_1b60 : public hashtable_iterator_base_s0055_1b60<Node> {
    hashtable_iterator_s0055_1b60(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base_s0055_1b60<Node>(pNode, pBucket) {}
    hashtable_iterator_s0055_1b60(Node** pBucket) : hashtable_iterator_base_s0055_1b60<Node>(*pBucket, pBucket) {}
    hashtable_iterator_s0055_1b60(const hashtable_iterator_s0055_1b60& x) : hashtable_iterator_base_s0055_1b60<Node>(x.mpNode, x.mpBucket) {}
};
}
namespace eastl {
template <class Node> struct hashtable_const_iterator_s0055_1b60 : public hashtable_iterator_base_s0055_1b60<Node> {
    hashtable_const_iterator_s0055_1b60(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base_s0055_1b60<Node>(pNode, pBucket) {}
    hashtable_const_iterator_s0055_1b60(Node** pBucket) : hashtable_iterator_base_s0055_1b60<Node>(*pBucket, pBucket) {}
};
}
namespace eastl {
template <class Node> inline bool operator!=(const hashtable_iterator_base_s0055_1b60<Node>& a, const hashtable_iterator_base_s0055_1b60<Node>& b) { return a.mpNode != b.mpNode; }
}
namespace eastl {
template <class Node> struct insert_return_type_s0055_1b60 {
    hashtable_iterator_s0055_1b60<Node> first;
    bool second;
};
}
namespace eastl {
template <class T1, class T2> struct pair_s0055_1b60 {
    typedef T1 first_type;
    typedef T2 second_type;
    T1 first;
    T2 second;
    pair_s0055_1b60(const T1& x, const T2& y) : first(x), second(y) {}
    template <class U, class V> pair_s0055_1b60(const pair_s0055_1b60<U, V>& p) : first(p.first), second(p.second) {}
};
}
namespace eastl {
template <class K, class V, class EK> class hashtable_s0055_1b60 {
public:
    typedef V value_type;
    typedef hash_node_s0055_1b60<V> node_type;
    typedef hashtable_iterator_s0055_1b60<node_type> iterator;
    typedef hashtable_const_iterator_s0055_1b60<node_type> const_iterator;
    hashtable_s0055_1b60(uint32_t nBucketCount, const hash_s0055_1b60<K>& h1, const mod_range_hashing& h2, const default_ranged_hash& h,
              const equal_to_s0055_1b60<K>& eq, const EK& ek, const allocator_s0055_1b60& a);
    ~hashtable_s0055_1b60() {
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
    insert_return_type_s0055_1b60<node_type> DoInsertValue(const value_type& value, true_type);
    insert_return_type_s0055_1b60<node_type> insert(const value_type& value) { return DoInsertValue(value, true_type()); }
    uint32_t erase(const K& k);

    EK m_extract;
    equal_to_s0055_1b60<K> m_equal;
    hash_s0055_1b60<K> m_h1;
    mod_range_hashing m_h2;
    node_type** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    prime_rehash_policy_s0055_1b60 mRehashPolicy;
    allocator_s0055_1b60 mAllocator;
};
}
namespace eastl {
template <class K, class T> class hash_map_s0055_1b60 : public hashtable_s0055_1b60<K, pair_s0055_1b60<const K, T>, use_first_s0055_1b60<pair_s0055_1b60<const K, T> > > {
public:
    typedef hashtable_s0055_1b60<K, pair_s0055_1b60<const K, T>, use_first_s0055_1b60<pair_s0055_1b60<const K, T> > > base_type;
    typedef pair_s0055_1b60<const K, T> value_type;
    explicit hash_map_s0055_1b60(const allocator_s0055_1b60& a = allocator_s0055_1b60())
        : base_type(0, hash_s0055_1b60<K>(), mod_range_hashing(), default_ranged_hash(), equal_to_s0055_1b60<K>(), use_first_s0055_1b60<value_type>(), a) {}
    typedef typename base_type::iterator iterator;
    T& operator[](const K& key) {
        ScratchSlots<13>();
        iterator itHashtable(base_type::find(key));
        if (itHashtable != base_type::end())
            return itHashtable.mpNode->mValue.second;
        return base_type::insert(value_type(key, T())).first.mpNode->mValue.second;
    }
};
}
namespace eastl {
template <class K, class V, class EK>
void hashtable_s0055_1b60<K, V, EK>::DoFreeNodes(node_type** pNodeArray, uint32_t n)
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
namespace EA {
namespace DateTime {
class DateTime_s0055_1b60 {
public:
    DateTime_s0055_1b60(int timeFrame) { Set(timeFrame); }
    void Set(int timeFrame);   // 0x0092E3D0
    int64_t mnSeconds;
};
}
}
namespace eastl {
template <class T> struct basic_string_s0055_1b60 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s0055_1b60 mAllocator;

    basic_string_s0055_1b60(const basic_string_s0055_1b60& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
    basic_string_s0055_1b60(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p, p + CharStrlen(p)); }
    ~basic_string_s0055_1b60() { DeallocateSelf(); }
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
    basic_string_s0055_1b60& operator=(const basic_string_s0055_1b60& x) {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    basic_string_s0055_1b60& assign(const T* pBegin, const T* pEnd);   // 0x00423650
    basic_string_s0055_1b60& assign(const T* p, uint32_t n) { return assign(p, p + n); }
    T* erase(T* pBegin, T* pEnd);                            // 0x0042E2F0
    basic_string_s0055_1b60& append(uint32_t n, T c);                   // 0x0042D2E0
    void resize(uint32_t n, T c);
};
}
namespace eastl {
typedef basic_string_s0055_1b60<char> string;
}
namespace eastl {
typedef basic_string_s0055_1b60<wchar_t> string16_s0055_1b60;
}
namespace eastl {
template <class T> inline bool operator==(const basic_string_s0055_1b60<T>& a, const basic_string_s0055_1b60<T>& b)
{
    return ((a.size() == b.size()) && (memcmp(a.data(), b.data(), (unsigned int)a.size()) == 0));
}
}
namespace eastl {
template <class T> bool operator==(const basic_string_s0055_1b60<T>& a, const T* p);   // 0x00555020
}
namespace eastl {
template <class InputIterator, class OutputIterator>
inline OutputIterator copy_impl(InputIterator first, InputIterator last, OutputIterator result)
{
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}
}
namespace eastl {
template <class InputIterator, class OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
    const bool elem = false;  // (names chosen to reproduce the /Od slot order)
    const bool h = false;
    const bool p33 = false;
    return copy_impl(first, last, result);
}
}
namespace eastl {
struct sp_vector_allocator_s0055_1b60 {
    const char* mpName;
    uint32_t mFlags;
};
}
namespace eastl {
template <class T> struct vector_s0055_1b60 {
    typedef T* iterator;
    typedef const T* const_iterator;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s0055_1b60 mAllocator;
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
}
namespace eastl {
template <class InputIterator, class T>
inline InputIterator find(InputIterator first, InputIterator last, const T& value)
{
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}
}
namespace eastl {
template void basic_string_s0055_1b60<wchar_t>::resize(uint32_t, wchar_t);
}
namespace eastl {
template void basic_string_s0055_1b60<char>::resize(uint32_t, char);
}
namespace SP {
namespace Feed {
struct AtomEntry_s0055_1b60 {
    eastl::string mID;                       // 0x00
    uint64_t mnAssetID;                      // 0x10
    eastl::string16_s0055_1b60 mTitle;                  // 0x18
    int64_t mUpdated;                        // 0x28
    uint32_t pad30[(0xD0 - 0x30) / 4];
    eastl::string16_s0055_1b60 mSummary;                // 0xD0
    eastl::vector_s0055_1b60<eastl::string16_s0055_1b60> mTags;    // 0xE0
    uint32_t padF4[(0x110 - 0xF4) / 4];
    bool mbAssembled;                        // 0x110
};
}
}
namespace SP {
uint64_t ParseAssetID(const char* pID);      // 0x005418C0
}
namespace SP {
namespace Pollen {
extern const char* kAssembledContentTag;     // "tag:spore.com,2006:AssembledContent"
}
}
namespace SP {
namespace Pollen {
class cAssetMetadata_s0055_1b60 : public EA::ResourceMan::ResourceObject {
public:
    const uint64_t& GetAssetID() const;              // 0x005507A0
    const Key_s0055_1b60& GetParentKey() const;                 // 0x005507E0
    const uint64_t& GetParentAssetID() const;        // 0x00550800
    const uint64_t& GetOriginalParentAssetID() const;// 0x00550820
    bool IsShared() const;                           // 0x00550970
    const wchar_t* GetName() const;                  // 0x00414E10
    void SetParentAssetID(uint64_t id);
    void SetOriginalParentAssetID(uint64_t id);
    bool UpdateFromEntry(const Feed::AtomEntry_s0055_1b60* pEntry, const eastl::string& feedURI);
    bool RemoveFeedURI(const eastl::string& feedURI);

    uint32_t pad4[(0x18 - 0x04) / 4];
    uint64_t mnAssetID;                              // 0x18
    Key_s0055_1b60 mLocalKey;                                   // 0x20
    Key_s0055_1b60 mParentKey;                                  // 0x2C
    uint64_t mnParentAssetID;                        // 0x38
    uint64_t mnOriginalParentAssetID;                // 0x40
    int64_t mnTimeStamp;                             // 0x48
    EA::DateTime::DateTime_s0055_1b60 mLastModified;            // 0x50
    uint32_t pad58[(0x78 - 0x58) / 4];
    eastl::string16_s0055_1b60 mNameStr;                        // 0x78
    eastl::string16_s0055_1b60 mSummaryStr;                     // 0x88
    eastl::vector_s0055_1b60<eastl::string> mFeedURITable;      // 0x98
    eastl::vector_s0055_1b60<eastl::string16_s0055_1b60> mTagList;         // 0xAC
};
}
}
namespace SP {
namespace Pollen {
template <class T> T* object_cast(EA::ResourceMan::ResourceObject* p);                                         // 0x00554140
}
}
namespace eastl {
template <> hashtable_s0055_1b60<uint32_t, pair_s0055_1b60<const uint32_t, uint64_t>, use_first_s0055_1b60<pair_s0055_1b60<const uint32_t, uint64_t> > >::iterator
hashtable_s0055_1b60<uint32_t, pair_s0055_1b60<const uint32_t, uint64_t>, use_first_s0055_1b60<pair_s0055_1b60<const uint32_t, uint64_t> > >::find(const uint32_t& k);
}
template class eastl::hashtable_s0055_1b60<uint64_t, eastl::pair_s0055_1b60<const uint64_t, Key_s0055_1b60>, eastl::use_first_s0055_1b60<eastl::pair_s0055_1b60<const uint64_t, Key_s0055_1b60> > >;
template class eastl::hash_map_s0055_1b60<uint64_t, Key_s0055_1b60>;
template class eastl::hash_map_s0055_1b60<uint32_t, uint64_t>;
template struct eastl::hashtable_iterator_base_s0055_1b60<eastl::hash_node_s0055_1b60<eastl::pair_s0055_1b60<const uint64_t, Key_s0055_1b60> > >;
// ---- items of slice s00551b60 end

// ---- items of slice s00567a90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
namespace eastl {
void EASTL_allocator_deallocate(void* p); // 0x00f47380
}
struct HashFreeStub { void DoFreeNodes(void** pArr, unsigned n); };
// ---- items of slice s00567a90 end

// ---- items of slice s00849f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct WString {
    wchar_t* mpBegin;      // +0
    wchar_t* mpEnd;        // +4
    wchar_t* mpCapacity;   // +8
    uint32_t mAllocPad;    // +c
    WString() { mpBegin = (wchar_t*)0x1667bac; mpEnd = (wchar_t*)0x1667bac; mpCapacity = (wchar_t*)0x1667bae; }
    WString(unsigned n, wchar_t c, const void* alloc = 0);  // @ 0084a780
    WString(const WString& o);        // @ 0084a7e0
    WString(wchar_t c);               // @ 0084aa60
    void AllocateSelf(unsigned n);    // 0x00429760
    WString& assign(const wchar_t* first, const wchar_t* last); // 0x00423650
    void resize(unsigned n);          // 0x00429520
};
// ---- items of slice s00849f70 end

// @ 0x0054b6f0
bool IHost::cAssetMetadataFactory_Create(IObj10* param2, IMeta** out, int param4, int param5)
{
    IMeta* meta = (IMeta*)operator_new_meta(0xd8, "Pollinator/cAssetMetadata", 0, 0, 0, 0);
    if (meta == 0) {
        meta = 0;
    } else {
        meta = (IMeta*)cAssetMetadata_ctor((cAssetMetadata*)meta);
    }
    meta->s0();
    int* p = param2->GetBounds();
    meta->f2 = p[0];
    meta->f3 = p[1];
    meta->f4 = p[2];
    bool ok = this->Make(param2, meta, param4, param5);
    if (!ok) {
        meta->Delete();
    } else {
        *out = meta;
    }
    return ok;
}










// @ 0x0054b7b0
bool Stub0054b7b0::FUN_0054b7b0(int param_1, IObj* param_2, int* param_3, int param_4)
{
    bool ok;
    if (param_4 != 0x30bdee3) return false;
    int* m = (int*)FUN_00554140(param_1);
    if (m != 0) ((IMeta_s0054_b7b0*)m)->Init();
    IWriter* w = (IWriter*)param_2->GetWriter();

    { int v = 0xd; ok = WriteU32(w, &v, 1, 0); }
    if (ok) { int v[2]; v[0] = m[6]; v[1] = m[7]; ok = FUN_0093ab10(w, v, 1, 0); }
    if (ok) { int v = m[9]; ok = WriteU32(w, &v, 1, 0); }
    if (ok) { int v = m[10]; ok = WriteU32(w, &v, 1, 0); }
    if (ok) { int v = m[8]; ok = WriteU32(w, &v, 1, 0); }
    if (ok) { int v = m[0xc]; ok = WriteU32(w, &v, 1, 0); }
    if (ok) { int v = m[0xd]; ok = WriteU32(w, &v, 1, 0); }
    if (ok) { int v = m[0xb]; ok = WriteU32(w, &v, 1, 0); }
    if (ok) { int v[2]; v[0] = m[0xe]; v[1] = m[0xf]; ok = FUN_0093ab10(w, v, 1, 0); }
    if (ok) { int v[2]; v[0] = m[0x10]; v[1] = m[0x11]; ok = FUN_0093ab10(w, v, 1, 0); }
    if (ok) { int v[2]; v[0] = m[0x12]; v[1] = m[0x13]; ok = FUN_0093ab10(w, v, 1, 0); }
    if (ok) { int v[2]; v[0] = m[0x14]; v[1] = m[0x15]; ok = FUN_0093ab10(w, v, 1, 0); }

    if (param_3 == 0) {
        if (ok) { int v = 0; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { int v[2]; v[0] = m[0x1a]; v[1] = m[0x1b]; ok = FUN_0093ab10(w, v, 1, 0); }
        void* str = FUN_00550880();
        int len;
        { uint16_t* p = (uint16_t*)str; while (*p) p++; len = (int)((char*)p - ((char*)str + 2)) >> 1; }
        if (ok) { int v = len; ok = WriteU32(w, &v, 1, 0); }
        if (ok) ok = w->WriteBytes(str, len << 1);
        int len2 = (m[0x1f] - m[0x1e]) >> 1;
        if (!(ok && len2 < 0x100)) ok = false;
        if (ok) { int v = len2; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { void* b = FUN_00414e10(len2 << 1); ok = w->WriteBytes(b, len2 << 1); }
        int len3 = (m[0x23] - m[0x22]) >> 1;
        if (!(ok && len3 < 0x1000)) ok = false;
        if (ok) { int v = len3; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { void* b = FUN_005508c0(len3 << 1); ok = w->WriteBytes(b, len3 << 1); }
    } else {
        if (ok) { int v = 0xffffffff; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { int v = param_3[0]; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { int v = param_3[3]; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { int v = param_3[1]; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { int v = param_3[2]; ok = WriteU32(w, &v, 1, 0); }
    }

    if (ok) { int v = (m[0x27] - m[0x26]) >> 4; ok = WriteU32(w, &v, 1, 0); }
    int* p1 = (int*)m[0x26];
    int* e1 = (int*)m[0x27];
    for (; p1 != e1; p1 = p1 + 4) {
        int len = p1[1] - p1[0];
        if (ok) { int v = len; ok = WriteU32(w, &v, 1, 0); }
        if (ok) ok = w->WriteBytes((const void*)p1[0], len);
    }

    if (param_3 == 0 || param_3[4] == 0) {
        if (ok) { int v = 0; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { int v = (m[0x2c] - m[0x2b]) >> 4; ok = WriteU32(w, &v, 1, 0); }
        int* p2 = (int*)m[0x2b];
        int* e2 = (int*)m[0x2c];
        for (; ok && p2 != e2; p2 = p2 + 4) {
            int len = (p2[1] - p2[0]) >> 1;
            if (ok) { int v = len; ok = WriteU32(w, &v, 1, 0); }
            if (ok) ok = w->WriteBytes((const void*)p2[0], len << 1);
        }
    } else {
        if (ok) { int v = 0xffffffff; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { int v = param_3[4]; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { int v = param_3[5]; ok = WriteU32(w, &v, 1, 0); }
    }

    if (ok) { int v = -((int)((char)m[0x1d] != 0)); ok = WriteU32(w, &v, 1, 0); }
    if (ok) { int v = (m[0x31] - m[0x30]) >> 2; ok = WriteU32(w, &v, 1, 0); }
    int* p3 = (int*)m[0x30];
    int* e3 = (int*)m[0x31];
    for (;;) {
        if (!ok || p3 == e3) {
            bool result = ok;
            if (m != 0) ((IMeta_s0054_b7b0*)m)->Delete();
            return result;
        }
        if (ok) { int v = *p3; ok = WriteU32(w, &v, 1, 0); }
        p3 = p3 + 1;
    }
}









// @ 0x0054dd30
namespace SP { namespace Pollen {
cAssetMetadataResourceFactory_s0054_dd30* CreateMetadataFactory(cAssetDirectory_s0054_dd30* pDir)
{
    return new ("Pollinator") cAssetMetadataResourceFactory_s0054_dd30(pDir);
}
}}  // namespace SP::Pollen








// @ 0x0054ddc0
unsigned int SP::Pollen::cAssetMetadataResourceFactory::GetSupportedTypes(unsigned int * pTypes, unsigned int count)
{
    if (count > 0)
        pTypes[0] = 0x030BDEE3;
    return 1;
}








// @ 0x0054ddf0
namespace SP { namespace Pollen {
cAssetDirectory_s0054_dd30::cAssetDirectory_s0054_dd30()
: mbInited(false), mnAssetWriteCount(0), mWriteTimer(5, 2)
{
}
}}  // namespace SP::Pollen








// @ 0x0054def0
SP::Pollen::cAssetDirectory::~cAssetDirectory()
{
}








// @ 0x0054df60
namespace SP { namespace Pollen {
bool cAssetDirectory_s0054_dd30::Init()
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
}}  // namespace SP::Pollen








// @ 0x0054e020
namespace SP { namespace Pollen {
bool cAssetDirectory_s0054_dd30::Shutdown()
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
}}  // namespace SP::Pollen








// @ 0x0054e0b0
namespace SP { namespace Pollen {
bool cAssetDirectory_s0054_dd30::HandleMessage(uint32_t messageId, void* pMessage)
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
}}  // namespace SP::Pollen








// @ 0x0054e250
namespace SP { namespace Pollen {
bool cAssetDirectory_s0054_dd30::AddMapping(uint64_t serverId, const Key_s0054_dd30& key)
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
}}  // namespace SP::Pollen








// @ 0x0054e460
namespace SP { namespace Pollen {
bool cAssetDirectory_s0054_dd30::GetLocalKey(uint64_t serverId, Key_s0054_dd30* pKey) const
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
}}  // namespace SP::Pollen








// @ 0x0054e530
namespace SP { namespace Pollen {
bool cAssetDirectory_s0054_dd30::GetServerId(const Key_s0054_dd30& key, uint64_t* pServerId, bool bLoad) const
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
            cAssetMetadata_s0054_dd30* pMetadata = object_cast<cAssetMetadata_s0054_dd30>(pResource);
            if (pMetadata && pMetadata->GetServerID() != (uint64_t)-1 && pMetadata->GetServerID() > 0xFFFFFFFF) {
                if (pServerId)
                    *pServerId = pMetadata->GetServerID();
                return true;
            }
        }
    }
    return false;
}
}}  // namespace SP::Pollen








// @ 0x0054e740
namespace SP { namespace Pollen {
bool cAssetDirectory_s0054_dd30::IsPending(uint64_t id) const
{
    return mPendingAssets.find(id) != mPendingAssets.end();
}
}}  // namespace SP::Pollen








// @ 0x0054e7b0
namespace SP { namespace Pollen {
void cAssetDirectory_s0054_dd30::SetPending(uint64_t id, bool bPending)
{
    if (bPending)
        mPendingAssets.insert(id);
    else
        mPendingAssets.erase(id);
}
}}  // namespace SP::Pollen








// @ 0x0054e800
namespace SP { namespace Pollen {
bool cAssetDirectory_s0054_dd30::IsPending2(uint64_t id) const
{
    return mPendingAssets2.find(id) != mPendingAssets2.end();
}
}}  // namespace SP::Pollen








// @ 0x0054e870
namespace SP { namespace Pollen {
void cAssetDirectory_s0054_dd30::AddPending2(uint64_t id)
{
    if (mPendingAssets2.insert(id).second)
        mnAssetWriteCount++;
}
}}  // namespace SP::Pollen








// @ 0x0054e8c0
namespace SP { namespace Pollen {
void cAssetDirectory_s0054_dd30::SetAuthorA(uint32_t id, uint64_t v)
{
    mAuthorMapA[id] = v;
}
}}  // namespace SP::Pollen








// @ 0x0054e8f0
namespace SP { namespace Pollen {
uint64_t cAssetDirectory_s0054_dd30::GetAuthorA(uint32_t id)
{
    AuthorMap::iterator it = mAuthorMapA.find(id);
    if (it != mAuthorMapA.end())
        return it.mpNode->mValue.second;
    return 0;
}
}}  // namespace SP::Pollen








// @ 0x0054e970
namespace SP { namespace Pollen {
void cAssetDirectory_s0054_dd30::SetAuthorB(uint32_t id, uint64_t v)
{
    mAuthorMapB[id] = v;
}
}}  // namespace SP::Pollen








// @ 0x0054e9a0
namespace SP { namespace Pollen {
uint64_t cAssetDirectory_s0054_dd30::GetAuthorB(uint32_t id)
{
    AuthorMap::iterator it = mAuthorMapB.find(id);
    if (it != mAuthorMapB.end())
        return it.mpNode->mValue.second;
    return 0;
}
}}  // namespace SP::Pollen








// @ 0x0054ea20
namespace SP { namespace Pollen {
bool cAssetDirectory_s0054_dd30::SetAuthorFlag(uint32_t id, bool b)
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
}}  // namespace SP::Pollen








// @ 0x0054eac0
namespace SP { namespace Pollen {
bool cAssetDirectory_s0054_dd30::GetAuthorFlag(uint32_t id)
{
    return (GetAuthorB(id) & 0x8000000000000000ULL) == 0x8000000000000000ULL;
}
}}  // namespace SP::Pollen







// @ 0x0054eb10
bool Dir::FUN_0054eb10(int param2, char param3)
{
    int self = (int)this;
    char* s = (char*)self;
    bool r = false;
    Mtx* mtx = (Mtx*)(s + 8);
    mtx->Lock(&r);
    if (*(char*)(s + 0x38) != 0) {
        It it;
        ((Ctr*)(s + 0x5c))->F90(&it, param2);
        int* miss = (int*)(*(int*)(s + 0x60) + *(int*)(s + 100) * 4);
        if (*(int*)&it != *miss) {
            It it2;
            ((Ctr*)(s + 0x3c))->F9d0(&it2, (char*)&it + 0x10);
            int* miss2 = (int*)(*(int*)(s + 0x40) + *(int*)(s + 0x44) * 4);
            if (*(int*)&it2 != *miss2) {
                ((Ctr*)(s + 0x3c))->Fc20(&it2);
                ((Ctr*)(s + 0x5c))->Fc20(&it);
                ((Ctr*)(s + 0x9c))->F620((char*)&it + 0x10);
                if (param3 != 0) {
                    int* db = ObjectTemplateDB();
                    ((void(__thiscall*)(void*, int, int))((*(void***)db)[0x78 / 4]))(db, param2, 0);
                } else {
                    ((Dir*)s)->F210(param2);
                }
                *(int*)(s + 0xbc) = *(int*)(s + 0xbc) + 1;
            }
            r = true;
        }
    }
    mtx->Unlock();
    return r;
}







// @ 0x0054ed50
bool Dir::FUN_0054ed50(int param2, int param3, char param4)
{
    int self = (int)this;
    char* s = (char*)self;
    bool r = false;
    Mtx* mtx = (Mtx*)(s + 8);
    mtx->Lock(&r);
    if (*(char*)(s + 0x38) != 0) {
        It it2;
        ((Ctr*)(s + 0x9c))->F620(&param2);
        It it;
        ((Ctr*)(s + 0x3c))->F9d0(&it, &param2);
        int* miss = (int*)(*(int*)(s + 0x40) + *(int*)(s + 0x44) * 4);
        if (*(int*)&it != *miss) {
            if (param4 == 0) {
                ((Dir*)s)->F210(it2.a);
            } else {
                int* db = ObjectTemplateDB();
                ((void(__thiscall*)(void*, int, int))((*(void***)db)[0x78 / 4]))(db, (int)(char*)&it + 8, 0);
            }
            ((Ctr*)(s + 0x3c))->Fc20(&it);
            It it3;
            ((Ctr*)(s + 0x5c))->F90(&it3, *(int*)&it);
            int* miss2 = (int*)(*(int*)(s + 0x60) + *(int*)(s + 100) * 4);
            if (*(int*)&it3 != *miss2 && *(int*)((char*)&it3 + 0x10) == param2
                && *(int*)((char*)&it3 + 0x14) == param3) {
                ((Ctr*)(s + 0x5c))->Fc20(&it3);
            }
            *(int*)(s + 0xbc) = *(int*)(s + 0xbc) + 1;
            r = true;
        }
    }
    mtx->Unlock();
    return r;
}







// @ 0x0054efb0
char Dir::FUN_0054efb0()
{
    int self = (int)this;
    char* s = (char*)self;
    if (*(char*)(s + 0x38) != 0) {
        Mtx* mtx = (Mtx*)(s + 8);
        mtx->Lock(0);
        void* q[2];
        ((Ctr*)(s + 0x5c))->F140(q);
        ((Ctr*)(s + 0x3c))->F3a0(*(void**)(s + 0x40), *(void**)(s + 0x44));
        *(int*)(s + 0x48) = 0;
        ((Ctr*)(s + 0x5c))->F3a0(*(void**)(s + 0x60), *(void**)(s + 100));
        *(int*)(s + 0x68) = 0;
        ((Ctr*)(s + 0x9c))->FreeNodes(*(void**)(s + 0xa0), *(void**)(s + 0xa4));
        *(int*)(s + 0xa8) = 0;
        FUN_0054f1a0(self);
        mtx->Unlock();
    }
    return *(char*)(s + 0x38);
}







// @ 0x0054f0f0
int Dir::FUN_0054f0f0()
{
    int* job = 0;
    int* sched = (int*)FUN_0068f4d0();
    if (job != 0) {
        ((CJob*)job)->GetStatus();
    }
    int ok = ((int(__thiscall*)(int*, int**))((*(void***)sched)[0x10 / 4]))(sched, &job);
    if (ok == 0) {
        if (job != 0) ((CJob*)job)->GetStatus();
        return 0;
    }
    job[6] = 4;
    job[0] = (int)&FUN_0068f5a0;
    job[1] = 0x15e3188;
    FUN_006909b0();
    if (job != 0) ((CJob*)job)->GetStatus();
    return 1;
}






// @ 0x0054f1a0
bool AssetDir::Save()
{
    MutexGuard guard(&mMutex, &kSaveTimeout);
    ISaveArea* sa = GetSaveArea(0x11ac19d);
    if (sa != 0) {
        SaveFilePtr file;
        bool ok = true;
        if (!mTableA.empty()) {
            if (sa->OpenFile(&kSaveKey, &file, 2, 2, 1, 0)) {
                IWriteStream* st = file->GetStream();
                ok = st->Write(&kMagicA, 4);
                ok = ok && st->Write(&kMagicB, 4);
                int n = mTableA.size();
                ok = ok && st->Write(&n, 4);
                for (HIterC<NodeA> it = mTableA.begin(), e = mTableA.end(); ok && it != e; ++it) {
                    NodeA* nd = it.mpNode;
                    ok = st->Write(nd, 8);
                    ok = ok && st->Write((char*)nd + 0xc, 4);
                    ok = ok && st->Write((char*)nd + 0x10, 4);
                    ok = ok && st->Write((char*)nd + 8, 4);
                }
                n = mTableB.size();
                ok = ok && st->Write(&n, 4);
                for (HIterC<NodeB> it = mTableB.begin(), e = mTableB.end(); it != e; ++it) {
                    NodeB* nd = it.mpNode;
                    ok = ok && st->Write(nd, 4);
                    ok = ok && st->Write((char*)nd + 8, 8);
                }
                n = mTableC.size();
                ok = ok && st->Write(&n, 4);
                for (HIterC<NodeB> it = mTableC.begin(), e = mTableC.end(); it != e; ++it) {
                    NodeB* nd = it.mpNode;
                    ok = ok && st->Write(nd, 4);
                    ok = ok && st->Write((char*)nd + 8, 8);
                }
                n = mTableD.size();
                ok = ok && st->Write(&n, 4);
                for (HIterC<NodeD> it = mTableD.beginInline(), e = mTableD.end(); ok && it != e; ++it) {
                    NodeD* nd = it.mpNode;
                    ok = st->Write(nd, 8);
                }
                file->Close();
                sa->Close();
            } else {
                return false;
            }
        }
        mbBusy = 0;
        return ok;
    }
    return false;
}





// @ 0x00550450
Meta::Meta()
{
    char* s = (char*)this;
    ((MetaBase*)s)->ctor();
    *(void**)s = (void*)vtbl_cAssetMetadata;
    *(int*)(s + 0x18) = 0xffffffff;
    *(int*)(s + 0x1c) = 0xffffffff;
    *(int*)(s + 0x20) = 0;
    *(int*)(s + 0x24) = 0;
    *(int*)(s + 0x28) = 0;
    *(int*)(s + 0x2c) = 0xffffffff;
    *(int*)(s + 0x30) = 0xffffffff;
    *(int*)(s + 0x34) = 0xffffffff;
    *(int*)(s + 0x38) = 0xffffffff;
    *(int*)(s + 0x3c) = 0xffffffff;
    *(int*)(s + 0x40) = 0xffffffff;
    *(int*)(s + 0x44) = 0xffffffff;
    *(int*)(s + 0x48) = 0;
    *(int*)(s + 0x4c) = 0;
    *(int*)(s + 0x50) = 0;
    *(int*)(s + 0x54) = 0;
    *(int*)(s + 0x58) = 0; *(int*)(s + 0x5c) = 0; *(int*)(s + 0x60) = 0;
    *(int*)(s + 0x58) = (int)DAT_01667bac;
    *(int*)(s + 0x5c) = *(int*)(s + 0x58);
    *(int*)(s + 0x60) = *(int*)(s + 0x58) + 2;
    *(int*)(s + 0x68) = 0xfffffffe;
    *(int*)(s + 0x6c) = 0xffffffff;
    *(int*)(s + 0x70) = 0xffffffff;
    *(char*)(s + 0x74) = 1;
    *(int*)(s + 0x78) = 0; *(int*)(s + 0x7c) = 0; *(int*)(s + 0x80) = 0;
    *(int*)(s + 0x78) = (int)DAT_01667bac;
    *(int*)(s + 0x7c) = *(int*)(s + 0x78);
    *(int*)(s + 0x80) = *(int*)(s + 0x78) + 2;
    *(int*)(s + 0x88) = 0; *(int*)(s + 0x8c) = 0; *(int*)(s + 0x90) = 0;
    *(int*)(s + 0x88) = (int)DAT_01667bac;
    *(int*)(s + 0x8c) = *(int*)(s + 0x88);
    *(int*)(s + 0x90) = *(int*)(s + 0x88) + 2;
    *(int*)(s + 0x98) = 0; *(int*)(s + 0x9c) = 0; *(int*)(s + 0xa0) = 0;
    *(int*)(s + 0xac) = 0; *(int*)(s + 0xb0) = 0; *(int*)(s + 0xb4) = 0;
    *(int*)(s + 0xc0) = 0; *(int*)(s + 0xc4) = 0; *(int*)(s + 0xc8) = 0;
}





// @ 0x005506c0
void Meta::FUN_005506c0()
{
    char* s = (char*)this;
    *(void**)s = (void*)vtbl_cAssetMetadata;
    FUN_00553fb0(s + 0xc0);
    FUN_00553e00(s + 0xac);
    FUN_00553b90(s + 0x98);
    WString_FreeBuffer(s + 0x88);
    WString_FreeBuffer(s + 0x78);
    WString_FreeBuffer(s + 0x58);
    *(void**)s = (void*)vtbl_cPropertyList;
    *(void**)s = (void*)vtbl_cEditorResource;
}





// @ 0x00550740
void * SP::Pollen::cAssetMetadata::AsInterface(EA::COM::InterfaceId param_2)
{
    if (param_2 == 0x30bdee3) return this;
    if (param_2 == 0x2269ed1) return this;
    if (param_2 == (int)0xee3f516e) return this;
    return 0;
}





// @ 0x005508a0
int64_t Meta::FUN_005508a0()
{
    return *(int64_t*)((char*)this + 0x68);
}





// @ 0x00550910
void* Meta::FUN_00550910(unsigned idx)
{
    char** v = (char**)((char*)this + 0x98);
    void* result;
    if (idx < (unsigned)(((char*)v[1] - (char*)v[0]) >> 4)) {
        void** p = (void**)(*(char**)((char*)this + 0x98) + (idx << 4));
        result = *p;
    } else {
        result = DAT_013ec47c;
    }
    return result;
}





// @ 0x005509e0
unsigned Meta::FUN_005509e0(unsigned idx)
{
    char** v = (char**)((char*)this + 0xac);
    if (idx < (unsigned)(((char*)v[1] - (char*)v[0]) >> 4)) {
        unsigned* p = (unsigned*)(*(char**)((char*)this + 0xac) + (idx << 4));
        unsigned result = *p;
        return result;
    }
    return 0;
}





// @ 0x00550a60
unsigned Meta::FUN_00550a60(unsigned idx)
{
    unsigned** v = (unsigned**)((char*)this + 0xc0);
    if (idx < (unsigned)(((char*)v[1] - (char*)v[0]) >> 2)) {
        return (*(unsigned**)((char*)this + 0xc0))[idx];
    }
    return 0;
}





// @ 0x00550aa0
bool Meta::FUN_00550aa0(void* key)
{
    char* s = (char*)this;
    int local_c;
    int local_8;
    FUN_00555980(&local_c, &key);
    int local_2c;
    if (local_c == local_8) {
        local_2c = *(int*)(s + 0xc4);
    } else {
        local_2c = local_c;
    }
    return local_2c != *(int*)(s + 0xc4);
}





// @ 0x00550b00
void Meta::FUN_00550b00(int key)
{
    char* s = (char*)this;
    char local_8[8];
    ((Map5*)(s + 0xc0))->F4020(local_8, &key);
}





// @ 0x00550b30
void Meta::FUN_00550b30(int key)
{
    char* s = (char*)this;
    ((Map5*)(s + 0xc0))->F40d0(&key);
}





// @ 0x00550b60
char Meta::FUN_00550b60(int key)
{
    char* s = (char*)this;
    int64_t v = FUN_005418c0(key);
    *(int64_t*)(s + 0x18) = v;
    if (((*(unsigned*)(s + 0x18) & *(unsigned*)(s + 0x1c)) != 0xffffffff)
        && (*(int*)(s + 0x18) != 0 || *(int*)(s + 0x1c) != 0)) {
        return 1;
    }
    return 0;
}




// @ 0x00550bd0
char Meta_s0055_0bd0::FUN_00550bd0(uint16_t* param_1)
{
    uint16_t* local_10 = param_1;
    uint16_t* local_6c = param_1;
    short sVar1;
    do { sVar1 = *local_6c; local_6c++; } while (sVar1 != 0);
    uint16_t* local_c = param_1 + (((int)local_6c - (int)(param_1 + 1)) >> 1);
    uint16_t* local_8 = 0;
    do {
        uint16_t* local_28;
        for (local_28 = local_10; local_28 != local_c && *local_28 != 0x2c; local_28++) { }
        local_8 = local_28;
        if (local_28 != local_10) {
            int local_20 = 0, local_1c = 0, local_18 = 0;
            FUN_00423820(&local_20, local_10, local_28);
            FUN_00554170();
            FUN_005541e0();
            FUN_006b8f40(&local_20);
            if (local_20 != local_1c) {
                FUN_00553cc0(&local_20);
            }
            FUN_004237d0(&local_20);
        }
        local_10 = local_8 + 1;
    } while (local_8 != local_c && local_10 != local_c);
    return 1;
}




// @ 0x00550cf0
void Meta_s0055_0bd0::FUN_00550cf0(WStr* out)
{
    char* s = (char*)this;
    char* pe = *(char**)(s + 0xb0);
    bool first = true;
    for (char* p = *(char**)(s + 0xac); p != pe; p += 0x10) {
        if (!first) {
            uint16_t* sep = (uint16_t*)DAT_013f027c;
            uint16_t* q = sep;
            while (*q != 0) q++;
            out->Append(sep, sep + (((int)q - (int)sep) >> 1));
        }
        out->Append(*(void**)p, *(void**)(p + 4));
        first = false;
    }
}




// @ 0x00550da0
char Meta_s0055_0bd0::FUN_00550da0(int* param_2, int* param_3, int* param_4)
{
    char* s = (char*)this;
    char result = 0;
    if (param_3 != 0) {
        int local_50 = param_3[0];
        if (FUN_00550b60(local_50) != 0) {
            *(int*)(s + 0x20) = param_2[0];
            *(int*)(s + 0x24) = param_2[1];
            *(int*)(s + 0x28) = param_2[2];
            *(int*)(s + 0x2c) = 0;
            *(int*)(s + 0x30) = 0;
            *(int*)(s + 0x34) = 0;
            *(int*)(s + 0x38) = param_3[0xe];
            *(int*)(s + 0x3c) = param_3[0xf];
            *(int*)(s + 0x40) = param_3[0x16];
            *(int*)(s + 0x44) = param_3[0x17];
            *(int*)(s + 8) = param_2[0];
            *(int*)(s + 0xc) = 0x30bdee3;
            *(int*)(s + 0x10) = param_2[2];
            *(int*)(s + 0x48) = param_3[10];
            *(int*)(s + 0x4c) = param_3[0xb];
            int64_t dt = 0;
            EA_DateTime_Set(1);
            *(int*)(s + 0x50) = (int)dt;
            *(int*)(s + 0x54) = (int)(dt >> 32);
            int local_54 = param_3[0x29];
            WStr* dst = (WStr*)(s + 0x58);
            char* src = (char*)(local_54 + 8);
            if (src != (char*)dst) {
                WStr_Assign(dst, *(void**)(local_54 + 8), *(void**)(local_54 + 0xc));
            }
            int local_60 = param_3[0x29];
            *(int*)(s + 0x68) = *(int*)(local_60 + 0x18);
            *(int*)(s + 0x6c) = *(int*)(local_60 + 0x1c);
            int* am = (int*)FUN_00607a60();
            int64_t u = ((int64_t(__thiscall*)(void*))((*(void***)am)[0x40 / 4]))(am);
            *(char*)(s + 0x74) = (*(int*)(s + 0x68) == (int)u && *(int*)(s + 0x6c) == (int)(u >> 32));
            *(int*)(s + 0x70) = 0xffffffff;
            if (param_3 + 6 != (int*)(s + 0x78)) {
                WStr_Assign((WStr*)(s + 0x78), (void*)param_3[6], (void*)param_3[7]);
            }
            if (param_3 + 0x34 != (int*)(s + 0x88)) {
                WStr_Assign((WStr*)(s + 0x88), (void*)param_3[0x34], (void*)param_3[0x35]);
            }
            if (*param_4 != param_4[1]) {
                FUN_00553cc0(param_4);
            }
            if (*(char*)(param_3 + 0x44) != 0) {
                int local_48[3] = {0, 0, 0};
                char* e = (char*)"tag:spore.com,2006:AssembledContent";
                char* q = e;
                while (*q != 0) q++;
                FUN_0047d390(local_48, e, q);
                FUN_00553cc0(local_48);
                if (1 < local_48[2] - local_48[0] && local_48[0] != 0) {
                    operator_delete((void*)local_48[0]);
                }
            }
            FUN_00554b60(*(void**)(s + 0xac), *(void**)(s + 0xb0));
            int local_2c = param_3[0x39];
            for (int it = param_3[0x38]; it != local_2c; it += 0x10) {
                /* push_back string at it (PARTIAL shape) */
                FUN_00553cc0((void*)it);
            }
            FUN_004769b0(*(void**)(s + 0xc0), *(void**)(s + 0xc4));
            int local_a4 = param_3[0x3f];
            int local_cc = param_3[0x3e];
            for (; local_cc != local_a4; local_cc += 4) {
                char local_b0[8];
                FUN_00554020(local_b0, (void*)local_cc);
            }
            result = 1;
        }
    }
    return result;
}




// @ 0x00551240
char Meta_s0055_0bd0::FUN_00551240(int* param_2, uint16_t* param_3, uint16_t* param_4, int param_5, int* param_6, char param_7)
{
    char* s = (char*)this;
    *(int*)(s + 0x20) = param_2[0];
    *(int*)(s + 0x24) = param_2[1];
    *(int*)(s + 0x28) = param_2[2];
    *(int*)(s + 8) = param_2[0];
    *(int*)(s + 0xc) = 0x30bdee3;
    *(int*)(s + 0x10) = param_2[2];
    EA_DateTime_Set(1);
    *(int*)(s + 0x48) = 0;
    *(int*)(s + 0x4c) = 0;
    *(int*)(s + 0x50) = *(int*)(s + 0x48);
    *(int*)(s + 0x54) = *(int*)(s + 0x4c);
    int* am = (int*)FUN_00607a60();
    int* p = (int*)((int(__thiscall*)(void*))((*(void***)am)[0x38 / 4]))(am);
    WStr_Format((void*)(s + 0x58), (void*)&DAT_013f3da0, *p);
    int64_t u = ((int64_t(__thiscall*)(void*))((*(void***)am)[0x40 / 4]))(am);
    *(int64_t*)(s + 0x68) = u;
    *(int*)(s + 0x70) = 0xffffffff;
    *(char*)(s + 0x74) = 1;
    {
        uint16_t* q = param_3; while (*q) q++;
        unsigned n = (unsigned)((q - param_3) >> 1);
        if (n > 0xff) n = 0x100;
        WStr_Assign((WStr*)param_3, param_3, param_3 + n);
    }
    {
        uint16_t* q = param_4; while (*q) q++;
        unsigned n = (unsigned)((q - param_4) >> 1);
        if (n > 0xfff) n = 0x1000;
        WStr_Assign((WStr*)param_4, param_4, param_4 + n);
    }
    *(int*)(s + 0x2c) = param_6[0];
    *(int*)(s + 0x30) = param_6[1];
    *(int*)(s + 0x34) = param_6[2];
    *(int*)(s + 0x38) = 0xffffffff;
    *(int*)(s + 0x3c) = 0xffffffff;
    *(int*)(s + 0x40) = 0xffffffff;
    *(int*)(s + 0x44) = 0xffffffff;
    if (*(int*)(s + 0x2c) != 0
        && GetParentServerID((int)s, s + 0x38, s + 0x40) == 0
        && ((*(unsigned*)(s + 0x38) & *(unsigned*)(s + 0x3c)) == 0xffffffff)) {
        FUN_0067cb30();
        if (AddPollinatorDebugInfo((int)(s + 0x2c), s + 0x38, 0) != 0) {
            *(int*)(s + 0x40) = *(int*)(s + 0x38);
            *(int*)(s + 0x44) = *(int*)(s + 0x3c);
        }
    }
    if (param_7 == 0) {
        *(int*)(s + 0x18) = 0xffffffff;
        *(int*)(s + 0x1c) = 0xffffffff;
    } else {
        int t = (int)FUN_0067cb30();
        *(int*)(s + 0x18) = *(int*)(t + 0x60);
        *(int*)(s + 0x1c) = *(int*)(t + 100);
    }
    FUN_00554760(*(void**)(s + 0x98), *(void**)(s + 0x9c));
    FUN_00553cc0(p);
    if (param_5 != 0) {
        FUN_00554b60(*(void**)(s + 0xac), *(void**)(s + 0xb0));
        FUN_00550bd0((uint16_t*)param_5);
    }
    return 1;
}




// @ 0x00551620
char Meta_s0055_0bd0::SetMetadata(uint32_t* param_2, int param_3, int param_4, int param_5, void* param_6, uint16_t* param_7, void* param_8, uint16_t* param_9, uint16_t* param_10, uint16_t* param_11, int param_12, void* param_13, char param_14)
{
    char* s = (char*)this;
    *(unsigned*)(s + 0x20) = param_2[0];
    *(unsigned*)(s + 0x24) = param_2[1];
    *(unsigned*)(s + 0x28) = param_2[2];
    *(unsigned*)(s + 8) = param_2[0];
    *(int*)(s + 0xc) = 0x30bdee3;
    *(unsigned*)(s + 0x10) = param_2[2];
    *(int*)(s + 0x18) = param_3;
    *(int*)(s + 0x1c) = param_4;
    *(int*)(s + 0x58) = param_5;
    *(int*)(s + 0x5c) = (int)param_6;
    if (param_14 == 0) {
        *(int*)(s + 0x18) = *(int*)(s + 0x58);
        *(int*)(s + 0x1c) = *(int*)(s + 0x5c);
    } else {
        EA_DateTime_Set(1);
        *(int*)(s + 0x18) = 0;
        *(int*)(s + 0x1c) = 0;
    }
    {
        uint16_t* q = param_7; while (*q) q++;
        unsigned n = (unsigned)((q - param_7) >> 1);
        if (n > 0xff) n = 0x100;
        WStr_Assign((WStr*)param_7, param_7, param_7 + n);
    }
    *(int*)(s + 0x78) = (int)param_8;
    *(int*)(s + 0x88) = (int)param_9;
    *(int*)(s + 0x8c) = 0xffffffff;
    *(char*)(s + 0x90) = 0;
    int* am = (int*)FUN_00607a60();
    int64_t u = ((int64_t(__thiscall*)(void*))((*(void***)am)[0x40 / 4]))(am);
    *(char*)(s + 0x90) = (*(int*)(s + 0x78) == (int)u && *(int*)(s + 0x88) == (int)(u >> 32));
    {
        uint16_t* q = param_10; while (*q) q++;
        unsigned n = (unsigned)((q - param_10) >> 1);
        if (n > 0xff) n = 0x100;
        WStr_Assign((WStr*)param_10, param_10, param_10 + n);
    }
    {
        uint16_t* q = param_11; while (*q) q++;
        unsigned n = (unsigned)((q - param_11) >> 1);
        if (n > 0xfff) n = 0x1000;
        WStr_Assign((WStr*)param_11, param_11, param_11 + n);
    }
    FUN_00550bd0((uint16_t*)param_12);
    if (param_13 != 0) {
        FUN_00554760(*(void**)(s + 0x98), *(void**)(s + 0x9c));
        int local_2c[3] = {0, 0, 0};
        char* e = (char*)param_13;
        char* q = e;
        while (*q != 0) q++;
        FUN_0047d390(local_2c, e, q);
        FUN_00553cc0(local_2c);
        if (1 < local_2c[2] - local_2c[0] && local_2c[0] != 0) {
            operator_delete((void*)local_2c[0]);
        }
    }
    return 1;
}




// @ 0x005519d0
void Meta_s0055_0bd0::FUN_005519d0(uint16_t* param_2, uint16_t* param_3, int param_4)
{
    char* s = (char*)this;
    {
        uint16_t* q = param_2; while (*q) q++;
        unsigned n = (unsigned)((q - param_2) >> 1);
        if (n > 0xff) n = 0x100;
        WStr_Assign((WStr*)(s + 0x78), param_2, param_2 + n);
    }
    {
        uint16_t* q = param_3; while (*q) q++;
        unsigned n = (unsigned)((q - param_3) >> 1);
        if (n > 0xfff) n = 0x1000;
        WStr_Assign((WStr*)(s + 0x88), param_3, param_3 + n);
    }
    if (param_4 != 0) {
        FUN_00554b60(*(void**)(s + 0xac), *(void**)(s + 0xb0));
        FUN_00550bd0((uint16_t*)param_4);
    }
}




// @ 0x00551af0
void Meta_s0055_0bd0::FUN_00551af0(int a, int b)
{
    *(int*)((char*)this + 0x18) = a;
    *(int*)((char*)this + 0x1c) = b;
    int* am = (int*)FUN_00607a60();
    int* p = (int*)((int(__thiscall*)(void*))((*(void***)am)[0x38 / 4]))(am);
    WStr_Format((void*)((char*)this + 0x58), (void*)&DAT_013f3da0, *p);
    *(int64_t*)((char*)this + 0x68) = ((int64_t(__thiscall*)(void*))((*(void***)am)[0x40 / 4]))(am);
}



// @ 0x00551b60
namespace SP { namespace Pollen {
void cAssetMetadata_s0055_1b60::SetParentAssetID(uint64_t id)
{
    mnParentAssetID = id;
}
}}  // namespace SP::Pollen



// @ 0x00551b80
namespace SP { namespace Pollen {
void cAssetMetadata_s0055_1b60::SetOriginalParentAssetID(uint64_t id)
{
    mnOriginalParentAssetID = id;
}
}}  // namespace SP::Pollen



// @ 0x00551ba0
namespace SP { namespace Pollen {
bool cAssetMetadata_s0055_1b60::UpdateFromEntry(const Feed::AtomEntry_s0055_1b60* pEntry, const eastl::string& feedURI)
{
    bool bChanged = false;
    ScratchSlots<1>();
    if (pEntry) {
        const uint64_t nAssetID = ParseAssetID(pEntry->mID.c_str());
        if (nAssetID == mnAssetID) {
            if (eastl::find(mFeedURITable.begin(), mFeedURITable.end(), feedURI) == mFeedURITable.end()) {
                mFeedURITable.push_back(feedURI);
                EA::DateTime::DateTime_s0055_1b60 now(1);
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
                for (eastl::vector_s0055_1b60<eastl::string16_s0055_1b60>::const_iterator itTag = pEntry->mTags.begin(), itTagEnd = pEntry->mTags.end(); itTag != itTagEnd; ++itTag)
                    mTagList.push_back(*itTag);
                bChanged = true;
            }
        }
    }
    return bChanged;
}
}}  // namespace SP::Pollen



// @ 0x00551ff0
namespace SP { namespace Pollen {
bool cAssetMetadata_s0055_1b60::RemoveFeedURI(const eastl::string& feedURI)
{
    bool removed = false;
    eastl::vector_s0055_1b60<eastl::string>::iterator pos = eastl::find(mFeedURITable.begin(), mFeedURITable.end(), feedURI);
    if (pos != mFeedURITable.end()) {
        mFeedURITable.erase(pos);
        removed = true;
    }
    return removed;
}
}}  // namespace SP::Pollen



// @ 0x00552080
namespace SP { namespace Pollen {
bool GetParentServerID(cAssetMetadata_s0055_1b60* pMetadata, uint64_t* pParentID, uint64_t* pOriginalID)
{
    bool bResult = true;
    uint64_t parentID = (uint64_t)-1;
    uint64_t originalID = (uint64_t)-1;
    if (pMetadata) {
        Key_s0055_1b60 parentKey = pMetadata->GetParentKey();
        cAssetMetadata_s0055_1b60* pParent = 0;
        int nMaxDepth = 32;
        if (parentKey.mInstance)
            bResult = false;
        while (parentKey.mInstance && parentID == (uint64_t)-1) {
            if (parentKey.mInstance) {
                EA::ResourceMan::ResourcePtr<EA::ResourceMan::ResourceObject> pResource;
                EA::ResourceMan::ResourceKey_s0055_1b60 metaKey(parentKey.mInstance, 0x030BDEE3, parentKey.mGroup);
                if (EA::ResourceMan::GetManager_s0055_1b60()->GetResource(metaKey, pResource.AsPPTypeParam(), 0, 0, 0, 0)) {
                    bResult = true;
                    pParent = object_cast<cAssetMetadata_s0055_1b60>(pResource);
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
}}  // namespace SP::Pollen


// @ 0x005687d0
void HashFreeStub::DoFreeNodes(void** pArr, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        void* node = pArr[i];
        while (node) {
            void* next = *(void**)node;
            EASTL_allocator_deallocate(node);
            node = next;
        }
    }
}

// @ 0x0084ab40
WString* CopyWStrings(const WString* first, const WString* last, WString* dst)
{
    for (; first != last; first = (const WString*)((const char*)first + 0x10),
                         dst = (WString*)((char*)dst + 0x10)) {
        if (first != dst)
            dst->assign(first->mpBegin, first->mpEnd);
    }
    return dst;
}
