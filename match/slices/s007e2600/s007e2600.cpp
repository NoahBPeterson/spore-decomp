// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"

namespace eastl {

class allocator {
public:
    const char* mpName;
};

struct sp_vector_allocator : public allocator {};

union EmptyString {
    uint32_t mUint32;
    char mEmpty8[1];
    wchar_t mEmpty16[1];
};
extern EmptyString gEmptyString;

template <typename T, typename A = allocator>
class vector {
public:
    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}

    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;
    uint32_t mAllocatorPad;
};

template <typename T, typename A = allocator>
class basic_string {
public:
    basic_string()
        : mpBegin(gEmptyString.mEmpty8), mpEnd(gEmptyString.mEmpty8), mpCapacity(gEmptyString.mEmpty8 + 1)
    {
    }

    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;
};

}

namespace SP {

template <int N> class MessageBasicRC;

class cAppStateManager {
public:
    struct cActionMessage {
        MessageBasicRC<5>* mMessage;
        unsigned int mFlags;
    };

    struct cAppFlagSetting {
        int mFlag;
        bool mSetting;
    };

    struct cActions {
        cActions();

        eastl::vector<cActionMessage, eastl::sp_vector_allocator> mEntryMessages;
        eastl::vector<cActionMessage, eastl::sp_vector_allocator> mExitMessages;
        eastl::vector<cAppFlagSetting, eastl::sp_vector_allocator> mEffectAppFlags;
        eastl::basic_string<char, eastl::allocator> mDescription;
        unsigned int mNextState;
    };
};

// @ 0x007e2600
cAppStateManager::cActions::cActions()
    : mNextState(0xffffffff)
{
}

}
