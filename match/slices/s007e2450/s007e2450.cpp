// Slice s007e2450: SP::cAppStateManager::CurrentStateName -- walks the state-name hash map at
// +0xf8 and returns the name whose value is the current state, or the empty string.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

namespace eastl {
struct EString {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mAllocator;
};
}  // namespace eastl

// node of the state-name hash map: string key, unsigned value, next node
struct StateNameNode {
    eastl::EString  key;    // +0x00
    unsigned int    value;  // +0x10
    StateNameNode*  next;   // +0x14
};

struct cStateNameMap {
    void*            mpAllocator;   // +0x00
    StateNameNode**  mpBuckets;     // +0x04
    int              mnBucketCount; // +0x08
    StateNameNode* end() const { return mpBuckets[mnBucketCount]; }
};

struct cAppStateManager {
    char pad00[0x88];
    unsigned int mCurrentState;      // +0x88
    char pad8c[0x6c];
    cStateNameMap mStateNameMap;     // +0xf8
    const char* CurrentStateName() const;
};

// @ 0x007e2450
const char* cAppStateManager::CurrentStateName() const {
    StateNameNode** b = mStateNameMap.mpBuckets;
    StateNameNode* node = *b;
    if (!node) {
        ++b;
        while (!*b)
            ++b;
        node = *b;
    }
    // the end marker is the node stored one past the last bucket
    StateNameNode* end = mStateNameMap.end();
    while (node != end) {
        if (node->value == mCurrentState)
            return node->key.mpBegin;
        node = node->next;
        if (!node) {
            // end of a collision chain: continue with the next non-empty bucket (do-first)
            do {
                ++b;
                node = *b;
            } while (!node);
        }
    }
    return "";
}
