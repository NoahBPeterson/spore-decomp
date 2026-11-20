// @ 0x00d33ec0
// Builds a small list of 12-byte pick-priority entries and hands it to the
// pick-priority manager, then releases the list's storage.
//
// The entries' first field is an opaque 32-bit id: the retail code loads the
// ids as immediates (0x23a6cc8 etc.) and the analysis image holds no string
// data at those values, so their names cannot be recovered here.
#include "game/types.h"

void* __cdecl  SP_GetCurrentGameMode();            // 0x00b5b800 (SP::GetCurrentGameMode)
void           EASTL_allocator_deallocate(void* p); // 0x00f47380

namespace SP {

struct Elem12 {
    uint32_t mId;        // opaque property / text id
    int32_t  mValue;
    int32_t  mPriority;
};

// The vector's allocator member: only its size (8 bytes) is observable from this
// function - it puts the vector at 0x14 bytes, which is what the retail frame
// reserves.  Its contents are never touched here.
struct Vec12Allocator {
    void*    mpPool;
    uint32_t mFlags;
};

struct Vec12 {
    Elem12*        mpBegin;
    Elem12*        mpEnd;
    Elem12*        mpCapacity;
    Vec12Allocator mAllocator;                           // +0xc

    void push_back(const Elem12& value);                 // 0x00cd92b0
    void Insert(Elem12* position, const Elem12& value);  // 0x00b535d0
};

} // namespace SP

// The manager's vtable slot used by this function is +0x2c.  The slots before
// it are not touched here, so they are left as unnamed interface entries.
struct IPickPriorityMgr {
    virtual void v00() = 0;
    virtual void v04() = 0;
    virtual void v08() = 0;
    virtual void v0c() = 0;
    virtual void v10() = 0;
    virtual void v14() = 0;
    virtual void v18() = 0;
    virtual void v1c() = 0;
    virtual void v20() = 0;
    virtual void v24() = 0;
    virtual void v28() = 0;
    virtual void SetPriorities(SP::Vec12* list, int mode) = 0;   // vtable +0x2c
};

IPickPriorityMgr* PickPriorityMgr();               // 0x00b3d240

// The game mode whose priority list is left empty.
extern char g_1654c10;                             // 0x01654c10

// Retail returns with `ret 4`, i.e. the one stack argument is popped by the
// callee (stdcall / thiscall shape).
void __stdcall SetPickPriorities(int mode)
{
    switch (mode) {
    case 0:
        {
            SP::Elem12 entry;
            SP::Vec12  list;

            list.mpBegin = 0;
            list.mpEnd = 0;
            list.mpCapacity = 0;
            if (SP_GetCurrentGameMode() != &g_1654c10) {
                entry.mId = 0x23a6ccd;
                entry.mValue = 0;
                entry.mPriority = 100;
                list.push_back(entry);

                entry.mId = 0x23a7919;
                entry.mValue = 0;
                entry.mPriority = 100;
                list.push_back(entry);

                entry.mId = 0x2a0349a;
                entry.mValue = 0;
                entry.mPriority = 100;
                list.push_back(entry);

                entry.mId = 0x2c9cc8e;
                entry.mValue = 0;
                entry.mPriority = 100;
                list.push_back(entry);

                entry.mId = 0x2a8fe3c;
                entry.mValue = 0;
                entry.mPriority = 100;
                list.push_back(entry);

                entry.mId = 0x3a25119;
                entry.mValue = 0;
                entry.mPriority = 100;
                list.push_back(entry);

                entry.mId = 0x23a79d8;
                entry.mValue = 0;
                entry.mPriority = 100;
                list.push_back(entry);

                entry.mId = 0x2785dd8;
                entry.mValue = 0;
                entry.mPriority = 100;
                list.push_back(entry);

                entry.mId = 0x23a6cc8;
                entry.mValue = 0;
                entry.mPriority = 100;
                list.push_back(entry);

                entry.mId = 0x40ce1b1;
                entry.mValue = 0;
                entry.mPriority = 100;
                list.push_back(entry);

                entry.mId = 0x1b92b27;
                entry.mValue = 0;
                entry.mPriority = 100;
                list.push_back(entry);

                entry.mId = 0xb033b403;
                entry.mValue = 0;
                entry.mPriority = 100;
                list.push_back(entry);
            }

            PickPriorityMgr()->SetPriorities(&list, 1);

            if (list.mpBegin && ((int32_t*)list.mpBegin)[-1] != 0)
                EASTL_allocator_deallocate(list.mpBegin);
        }
        break;

    case 1:
        {
            SP::Elem12 entry;
            SP::Vec12  list;

            list.mpBegin = 0;
            list.mpEnd = 0;
            list.mpCapacity = 0;

            entry.mId = 0x23a6cc8;
            entry.mValue = 0;
            entry.mPriority = 100;
            list.Insert(0, entry);

            PickPriorityMgr()->SetPriorities(&list, 1);

            if (list.mpBegin && ((int32_t*)list.mpBegin)[-1] != 0)
                EASTL_allocator_deallocate(list.mpBegin);
        }
        break;

    default:
        return;
    }
}
