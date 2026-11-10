// Slice s007e27d0: SP::cAppStateManager::SwitchToState (the vtable slot at 0x007e27d0) -- reports
// whether the requested state has an entry in the state-action map at +0xb8.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

// state-action hash map (lives at manager+0xb8): allocator, buckets, bucket count
struct cStateActionsMap {
    void*   mpNodeAllocator;   // +0x00
    void**  mpBucketArray;     // +0x04
    int     mnBucketCount;     // +0x08
    void find(void** out, const unsigned int* key);   // 0x00645ed0 __thiscall ret 8
};

struct cAppStateManager {
    char pad00[0xb8];
    cStateActionsMap mStateActionsMap;            // +0xb8
    bool SwitchToState(unsigned int state);
};

// @ 0x007e27d0
bool cAppStateManager::SwitchToState(unsigned int state) {
    cStateActionsMap* map = &mStateActionsMap;
    void* out[2];
    map->find(out, &state);
    bool found = out[0] != map->mpBucketArray[map->mnBucketCount];
    return found;
}
