// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"

namespace eastl {

class allocator {
public:
    const char* mpName;
};

template <typename T> struct use_first {};
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

template <typename K, typename V, typename A, typename E, typename P, typename H>
class hashtable {
public:
    typedef hash_node<V> node_type;

    ~hashtable();
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    void DoFreeNodes(node_type** pBucketArray, uint32_t nBucketCount);
    void DoFreeBuckets(node_type** pBucketArray, uint32_t nBucketCount)
    {
        if (nBucketCount > 1) {
            operator delete(pBucketArray);
        }
    }

    uint32_t mFunctors;
    node_type** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    prime_rehash_policy mRehashPolicy;
    A mAllocator;
};

// @ 0x007e27a0
template <typename K, typename V, typename A, typename E, typename P, typename H>
hashtable<K, V, A, E, P, H>::~hashtable()
{
    clear();
    DoFreeBuckets(mpBucketArray, mnBucketCount);
}

}

namespace SP {

class cAppStateManager {
public:
    struct cTransitionHash {};
};

}

typedef eastl::pair<unsigned int, unsigned int> TransitionKey;
typedef eastl::pair<const TransitionKey, unsigned int> TransitionValue;

template eastl::hashtable<TransitionKey, TransitionValue, eastl::allocator,
                          eastl::use_first<TransitionValue>, eastl::equal_to<TransitionKey>,
                          SP::cAppStateManager::cTransitionHash>::~hashtable();
