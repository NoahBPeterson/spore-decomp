// src/game/cmn/timermanager.cpp.cpp -- migrated from slice(s) s0112ce20 by tools/migrate/rewrite.py
// Object file: cmn/timermanager.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/TimerManager.h"
#include "rw/audio/core/TimerHandle.h"
#include <string.h>
#include "rw/audio/core/Collection.h"

// ---- items of slice s0112ce20 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace audio {
namespace core {
class Collection_s0112_ce20
{
public:
    struct Node // Collection::ItemNode
    {
        Node* mpNext;     // +0x0
        Node* mpPrev;     // +0x4
        void** mppOwner;  // +0x8 (owner is &handle->mItemHandleNode)
    };

    void* mpBlockHead;   // +0x0
    void* mpBlockTail;   // +0x4
    int   miBlockCount;  // +0x8
    Node* mpFreeHead;    // +0xc
    Node* mpUsedHead;    // +0x10
    int   mSize;         // +0x14
    int   mCapacity;     // +0x18

    int AddCapacity(int count);        // 0x01133ad0
    bool AddItem(void** outOwner);     // 0x01133bd0
    Node* GetUsedHead();               // 0x01133b60
    Node* UnlinkUsed(void** owner);    // 0x01133a60
    void RemoveNode(void** owner);     // 0x01133c30
    void RemoveUsedNode(Node* node);   // 0x01133a80
    void Defragment();                 // 0x01133c90
    Collection_s0112_ce20* Clear();               // 0x01133e30
    Collection_s0112_ce20* Release();             // 0x01133b70
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class TimerHandle_s0112_ce20
{ public:
    void* mpItemHandleNode;         // +0x0  ItemHandle::pNode
    void* mpCallback;               // +0x4
    void* mpContext;                // +0x8
    const char* mpName;             // +0xc
    unsigned int mCpuTicks;         // +0x10
    unsigned char mStage;           // +0x14
    unsigned char mTimerVisibility; // +0x15
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class TimerManager_s0112_ce20
{ public:
    Collection_s0112_ce20 maCollections[2]; // +0x0
    float mfCallbackTime;        // +0x38
    TimerHandle_s0112_ce20* mpCurrentHandle;// +0x3c
    int miCurrentCollection;     // +0x40
    Collection_s0112_ce20::Node* mpDeferredRemoveNode; // +0x44

    TimerManager_s0112_ce20();                            // 0x0112da90
    bool AddTimer(TimerHandle_s0112_ce20* handle, void* callback, void* context, const char* name,
                  int collectionIndex, unsigned char visibility); // 0x0112d8e0
    void RemoveTimer(TimerHandle_s0112_ce20* handle);     // 0x0112d940
    void ExecuteTimers(int collectionIndex);   // 0x0112d9b0
    void Defragment();                         // 0x0112da30
    void Release();                            // 0x0112da60
};
}
}
}
// ---- items of slice s0112ce20 end

// @ 0x0112d8e0
namespace rw { namespace audio { namespace core {
bool TimerManager_s0112_ce20::AddTimer(TimerHandle_s0112_ce20* handle, void* callback, void* context, const char* name, int collectionIndex, unsigned char visibility)
{
    Collection_s0112_ce20* pCollection = &maCollections[collectionIndex];
    if (pCollection->mCapacity == 0)
        pCollection->AddCapacity(74);

    bool result = pCollection->AddItem(&handle->mpItemHandleNode);
    if (!result)
    {
        handle->mpCallback = callback;
        handle->mpContext = context;
        handle->mpName = name;
        handle->mStage = (unsigned char)collectionIndex;
        handle->mTimerVisibility = visibility;
        handle->mCpuTicks = 0;
    }
    return result;
}
}}}  // namespace rw::audio::core
