// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"

namespace eastl {

template <typename T>
class vector {
public:
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }

    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocatorSlot[2];
};

}

namespace SP {

class cSPMission {
public:
    bool IsListeningForMessage(unsigned int messageID);

    uint32_t mUnknown000[0x1d0 / 4];
    eastl::vector<unsigned int> mListenedMessageIDs;
};

// @ 0x00c451a0
bool cSPMission::IsListeningForMessage(unsigned int messageID)
{
    int count = (int)mListenedMessageIDs.size();
    for (int i = 0; i < count; i++) {
        if (mListenedMessageIDs[i] == messageID) {
            return true;
        }
    }
    return false;
}

}
