// Slice s007e2680: SP::cAppStateManager::cActions destructor.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

void __cdecl AllocDeallocate(void* p);   // 0x00F47380

namespace eastl {
// eastl::basic_string<char> (EString): begin/end/capacity + allocator.
struct EString {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mAllocator;
    ~EString() throw() {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            AllocDeallocate(mpBegin);
    }
};
}  // namespace eastl

struct RefObj {
    virtual void r0();
    virtual int  AddRef();
    virtual int  Release();
};

// 8-byte refcounted message: object pointer + flag.
struct cActionMessage {
    RefObj* p;
    int     flag;
};

// eastl vector<cActionMessage> (0x14 bytes); destructor is out of line at 0x007e24b0.
struct AMVec {
    cActionMessage* mpBegin;
    cActionMessage* mpEnd;
    cActionMessage* mpCapacity;
    cActionMessage* a10;
    cActionMessage* a14;
    ~AMVec();   // 0x007e24b0
};

// eastl vector of trivially-destructible elements (0x14 bytes); destructor inlined.
struct PodVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* a10;
    void* a14;
    ~PodVec() throw() {
        if (mpBegin && ((int*)mpBegin)[-1])
            AllocDeallocate(mpBegin);
    }
};

// SP::cAppStateManager::cActions (size 0x50)
struct cActions {
    AMVec           mEntryMessages;    // +0x00
    AMVec           mExitMessages;     // +0x14
    PodVec          mHandler;          // +0x28
    eastl::EString  mName;             // +0x3c
    int             field4c;           // +0x4c
    ~cActions();
};

// @ 0x007e2680
cActions::~cActions() {}
