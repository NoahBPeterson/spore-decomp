#include "game/types.h"

unsigned char __cdecl GetTribeProperty(void* object, int property, unsigned char defaultValue); // 0x0064f350
extern void* gTribeStrategyProperties; // 0x01581288

namespace SP {
struct TribeObjectNode {
    unsigned int mKey;
    void* mValue;
    TribeObjectNode* mpNext;
};
struct TribeObjectIterator {
    TribeObjectNode* mpNode;
    TribeObjectNode** mpBucket;
};
struct TribeObjectTable {
    void* mpPolicy;
    TribeObjectNode** mpBuckets;
    unsigned int mnBucketCount;
    unsigned int mnElementCount;
    TribeObjectIterator* find(TribeObjectIterator* result, const unsigned int* key); // 0x00645ed0
    TribeObjectNode* End() { return mpBuckets[mnBucketCount]; }
};
class cTribeModeStrategy {
public:
    bool IsObjectAllowed(unsigned int id);
    unsigned char mUnknown[0xa8];
    TribeObjectTable mObjects;
    unsigned char mUnknownB8[0x198 - 0xb8];
    bool mAllowAllObjects;
};

// @ 0x00cd6ef0
bool cTribeModeStrategy::IsObjectAllowed(unsigned int id)
{
    if (!mAllowAllObjects && GetTribeProperty(gTribeStrategyProperties, 0x1ccfdbe6, 0)) {
        unsigned int key = id;
        TribeObjectIterator it;
        TribeObjectNode* end = mObjects.End();
        unsigned char found = mObjects.find(&it, &key)->mpNode != end;
        return found != 0;
    }
    return true;
}
}
