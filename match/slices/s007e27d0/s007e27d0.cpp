// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"

namespace EA {
class AppCommandLine;
namespace COM { typedef unsigned int InterfaceId; }
}

namespace eastl {

class allocator {
public:
    const char* mpName;
};

template <typename T> struct use_first {};
template <typename T> struct hash {};
template <typename T> struct equal_to {};

template <typename K, typename V>
struct pair {
    K first;
    V second;
};

struct prime_rehash_policy {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
};

template <typename V>
struct hash_node {
    V mValue;
    hash_node* mpNext;
};

template <typename V>
struct hashtable_iterator {
    hash_node<V>* mpNode;
    hash_node<V>** mpBucket;
};

template <typename V>
inline bool operator!=(const hashtable_iterator<V>& a, const hashtable_iterator<V>& b)
{
    return a.mpNode != b.mpNode;
}

template <typename K, typename V, typename A, typename E, typename P, typename H>
class hashtable {
public:
    typedef hash_node<V> node_type;
    typedef hashtable_iterator<V> const_iterator;

    const_iterator find(const K& key) const;
    const_iterator end() const
    {
        const_iterator it;
        it.mpNode = mpBucketArray[mnBucketCount];
        it.mpBucket = mpBucketArray + mnBucketCount;
        return it;
    }

    uint32_t mFunctors;
    node_type** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    prime_rehash_policy mRehashPolicy;
    A mAllocator;
};

template <typename K, typename V, typename H = hash<K>, typename P = equal_to<K>, typename A = allocator>
class hash_map : public hashtable<K, pair<const K, V>, A, use_first<pair<const K, V> >, P, H> {};

}

namespace SP {

class cAppStateManager {
public:
    virtual int AddRef();
    virtual int Release();
    virtual ~cAppStateManager();
    virtual void* AsInterface(EA::COM::InterfaceId);
    virtual bool Init(const char*);
    virtual bool Shutdown();
    virtual void Update();
    virtual bool LoadConfigFile(unsigned int, unsigned int, EA::AppCommandLine&, bool);
    virtual bool LoadConfigFile(const wchar_t*, EA::AppCommandLine&, bool);
    virtual bool SwitchToState(unsigned int stateID);

    uint32_t mUnknown004[(0xb8 - 4) / 4];
    eastl::hash_map<unsigned int, int> mStateActionsMap;
};

// @ 0x007e27d0
bool cAppStateManager::SwitchToState(unsigned int stateID)
{
    eastl::hash_map<unsigned int, int>::const_iterator it = mStateActionsMap.find(stateID);
    bool found = it != mStateActionsMap.end();
    return found;
}

}
