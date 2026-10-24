// Slice s00a3af80: 00a3b640.
// eastl::hash_map<unsigned, String8>::operator[](const uint32& key), the same shape as the
// hash_map::operator[] instantiations already matched at 0x5526a0:
//     iterator it = find(key);
//     if (it != end()) return it.mpNode->mValue.second;
//     return insert(value_type(key, T())).first.mpNode->mValue.second;
// The stored value is the 16-byte char eastl string (begin/end/capacity/allocator): its destructor
// compares mpCapacity - mpBegin byte-wise against 1, and its default ctor points at the shared empty
// string gStrEmpty (0x1667bac), which is what the insert path materialises at 0xa3b694.

typedef unsigned int uint32;

extern char gStrEmpty[];   // 0x1667bac (shared empty eastl string)

void* operator new(unsigned int, const char*, int, int, const char*, int);
void operator delete[](void*);   // 0x00f47380

struct String8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int mAlloc;
    String8() {
        mpBegin = gStrEmpty;
        mpEnd = gStrEmpty;
        mpCapacity = gStrEmpty + 1;
    }
    ~String8() { if (mpCapacity - mpBegin > 1 && mpBegin) operator delete[](mpBegin); }
};

struct StrPair {
    const uint32 first;
    String8 second;
    StrPair(const uint32& key, const String8& value);   // 0x00b209f0
};

// eastl::hashtable node: the value_type pair first, the chain link after it.
struct StrNode {
    StrPair mValue;      // +0x00
    StrNode* mpNext;     // +0x14
};

// eastl::hashtable_iterator_base / hashtable_iterator
struct StrIterBase {
    StrNode* mpNode;
    StrNode** mpBucket;
    StrIterBase(StrNode* pNode, StrNode** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
};
struct StrIter : StrIterBase {
    StrIter(StrNode* pNode = 0, StrNode** pBucket = 0) : StrIterBase(pNode, pBucket) {}
    StrIter(StrNode** pBucket) : StrIterBase(*pBucket, pBucket) {}
    StrIter(const StrIter& x) : StrIterBase(x.mpNode, x.mpBucket) {}
};
inline bool operator!=(const StrIterBase& a, const StrIterBase& b) { return a.mpNode != b.mpNode; }

namespace eastl {
struct true_type {};
template <typename T1, typename T2> struct pair { T1 first; T2 second; };
}

// eastl::prime_rehash_policy
struct RehashPolicy {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    unsigned mnNextResize;
};

struct StrHashTable {
    int mFunctors;                // +0x00
    StrNode** mpBucketArray;      // +0x04
    unsigned mnBucketCount;       // +0x08
    unsigned mnElementCount;      // +0x0c
    RehashPolicy mRehashPolicy;   // +0x10
    StrIter find(const uint32& key);                                   // 0x00a3b2c0
    StrIter end() { return StrIter(mpBucketArray + mnBucketCount); }
    eastl::pair<StrIter, bool> DoInsertValue(const StrPair& value,
                                             eastl::true_type);        // 0x00a3b580
    eastl::pair<StrIter, bool> insert(const StrPair& value) {
        return DoInsertValue(value, eastl::true_type());
    }
    // eastl::hash_map<unsigned, String8>::operator[]; named OperatorIndex (not operator[]) so the
    // checker can bind the symbol (MSVC mangles operator[] as ??A, which the marker match rejects).
    String8& OperatorIndex(const uint32& key);
};

// @ 0x00a3b640
String8& StrHashTable::OperatorIndex(const uint32& key) {
    StrIter it = find(key);
    if (it != end())
        return it.mpNode->mValue.second;
    return insert(StrPair(key, String8())).first.mpNode->mValue.second;
}