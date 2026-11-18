// @ 0x00cd6e40
#include "game/types.h"

namespace SP {
// Layout of the tribe strategy's ID-to-object table.
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
    void find(TribeObjectIterator* result, const unsigned int* key); // 0x00645ed0
};
class cTribeModeStrategy {
public:
    bool HasObject(unsigned int id);
    unsigned char mUnknown[0xa8];
    TribeObjectTable mObjects;
};

bool cTribeModeStrategy::HasObject(unsigned int id)
{
    TribeObjectTable& table = mObjects;
    TribeObjectIterator it;
    unsigned int key = id;
    table.find(&it, &key);
    if (it.mpNode != table.mpBuckets[table.mnBucketCount])
        return it.mpNode->mValue != 0;
    return false;
}
}
