// Slice s00b0e560 (batch bfs1) — shared stub types.
//
// Module: "Spore" (work/xmatch/retail_lib.json).  The region is a serialization /
// render-queue manager (EASTL/spstl containers) plus a polymorphic input host whose
// SP::cLocalInputState lives at +0x31c (functions 00b0f140..00b0f240).  The 2008
// dev-build PDB supplies the real cLocalInputState layout (size 0x48).

#pragma once
#include "types.h"

// ---- SP::cLocalInputState (PDB, size 0x48) ---------------------------------
struct cLocalInputState
{
    void Reset();                                    // 0x00697980
    bool OnKeyDown(int vkCode, int modifiers);       // 0x00697a50
    bool OnMouseDown(int button, float x, float y, int state);   // 0x00697ab0
    bool OnMouseUp(int button, float x, float y, int state);     // 0x00697af0
};

// ---- polymorphic input host (this+0x31c = cLocalInputState) ----------------
// Only the vtable slot used by FUN_00b0f170 (offset 0x50, index 20) matters.
struct InputHost
{
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();

    char  pad_front[0x10c - 4];   // vptr is 4 bytes; data members follow at +0x04
    float m10c;          // +0x10c
    char  pad_110[4];
    float m114;          // +0x114
    char  pad_118[0x130 - 0x118];
    float m130;          // +0x130
    char  pad_134[4];
    float m138;          // +0x138
    char  pad_13c[0x154 - 0x13c];
    float m154;          // +0x154
    char  pad_158[4];
    float m15c;          // +0x15c
    char  pad_160[0x31c - 0x160];
    cLocalInputState mInput;   // +0x31c

    bool  FUN_00b0f140(int);
    void  FUN_00b0f170();
    bool  FUN_00b0f190(int, int);
    bool  FUN_00b0f1b0(int, float, float, int);
    bool  FUN_00b0f1e0(int, float, float, int);
    void  FUN_00b0f210(float*, float*, float*);
    void  FUN_00b0f240(float*, float*, float*);
};

// ---------------------------------------------------------------------------
// spstl::slot_vector<T, spstl::simple_deque<slot_vector_entry<T>,
//                      eastl::allocator, 128>>
// ---------------------------------------------------------------------------
// Recovered from the 2008 dev-build PDB (size 0x1c).  The embedded simple_deque
// is { eastl::vector<slot_vector_entry<T>*> mBlocks; uint32_t mBlockPos; } and
// the base appends mBegin / mFreeChain.
//
//   slot_vector_entry<T> = { uint32_t mSlotInfo; T mData; }             (8 bytes)
//     mSlotInfo bit31 -> "slot is free"
//              bit30 -> "last slot of a free run"
//              bits 0-29 -> head of the free-slot chain (a slot index)
//
// The queue object's own vectors are walked through mVec.mBlocks.mpBegin read
// as a flat array of 8-byte slots, so that dword is named mpSlots here.
struct SlotVector
{
    static const uint32_t kNil = 0x3fffffffu;

    uint8_t*  mpSlots;       // +0x00  mVec.mBlocks.mpBegin
    uint8_t*  mpSlotsEnd;    // +0x04  mVec.mBlocks.mpEnd
    uint8_t*  mpSlotsCap;    // +0x08  mVec.mBlocks.mpCapacity
    void*     mBlocksAlloc;  // +0x0c  mVec.mBlocks.mAllocator
    uint32_t  mBlockPos;     // +0x10  mVec.mBlockPos
    uint32_t  mBegin;        // +0x14  index of the lowest used slot
    uint32_t  mFreeChain;    // +0x18  head of the free-slot chain

    uint8_t* slotAt(uint32_t i) const { return mpSlots + i * 8; }
    void*    slotData(uint32_t i) const { return *(void**)(mpSlots + 4 + i * 8); }
    uint8_t* beginSlot() const { return mBegin < kNil ? slotAt(mBegin) : mpSlotsEnd; }
};

// One 8-byte slot_vector_entry<T>.
struct SlotEntry
{
    uint32_t mSlotInfo;   // +0x00
    void*    mpData;      // +0x04
};

// Intrusive job-list node.  The sentinel lives inline in the queue object; only
// its first two dwords are meaningful, but the payload slot keeps the following
// member aligned at +0x44.
struct JobListNode
{
    JobListNode* mpNext;    // +0x00
    JobListNode* mpPrev;    // +0x04
    void*        mpPayload; // +0x08  (only present on heap-allocated nodes)
};

// ---------------------------------------------------------------------------
// Serialization / render-queue manager (functions 00b0e560..00b0ee10).
// Layout recovered from the disassembly: three consecutive slot vectors at
// +0x44 / +0x60 / +0x7c, an eastl::vector<void*> of jobs at +0x24 and an
// intrusive EASTL list at +0x38.
// ---------------------------------------------------------------------------
struct RenderQueueView
{
    uint8_t     pad_00[0x24];
    void**      mpJobBegin;   // +0x24  eastl::vector<void*> of jobs
    void**      mpJobEnd;     // +0x28
    void**      mpJobCap;     // +0x2c
    uint8_t     pad_30[0x38 - 0x30];
    JobListNode mJobList;     // +0x38  intrusive list sentinel
    SlotVector  mVecA;        // +0x44
    SlotVector  mVecB;        // +0x60
    SlotVector  mVecC;        // +0x7c
    uint8_t     pad_98[0x9c - 0x98];
    int         mSelectedJob; // +0x9c
    char        mSkipFlag;    // +0xa0
};

// The same object as seen by FUN_00b0eae0, whose `this` is 4 bytes above the
// base used by the other methods.
struct RenderQueueInnerView
{
    uint8_t   pad_00[0x20];
    void**    mpJobBegin;   // +0x20  (== RenderQueueView::mpJobBegin)
    void**    mpJobEnd;     // +0x24
    void**    mpJobCap;     // +0x28
    uint8_t   pad_2c[0x40 - 0x2c];
    SlotVector mVecA;       // +0x40  (== RenderQueueView::mVecA)
    uint8_t   pad_5c[0x98 - 0x5c];
    int       mSelectedJob; // +0x98  (== RenderQueueView::mSelectedJob)
    char      mSkipFlag;    // +0x9c  (== RenderQueueView::mSkipFlag)
};

// ---------------------------------------------------------------------------
// Supporting views for the interaction pass (00b0eae0 / 00b0ee10).
// ---------------------------------------------------------------------------
// The eastl::vector<slot_vector_entry<T>*> that a slot vector owns; the
// helpers take it by address, so the fields must stay contiguous.
struct AgentBlocks
{
    void** mpBegin;     // +0x00
    void** mpEnd;       // +0x04
    void** mpCapacity;  // +0x08
    void*  mAllocator;  // +0x0c
};

// spstl::slot_vector_base<...>::iterator — { owner, slot index }.
struct SlotIter
{
    void*    mpOwner;   // +0x00
    uint32_t mIndex;    // +0x04
};

// Fields of SP::cInteractionAgent touched by the interaction pass.
struct InteractionAgentView
{
    uint8_t  pad_00[0x2c];
    void**   mpBlocks;      // +0x2c  eastl::vector<slot_vector_entry<T>*>
    void**   mpBlocksEnd;   // +0x30
    void**   mpBlocksCap;   // +0x34
    void*    mBlocksAlloc;  // +0x38
    uint32_t mBlockPos;     // +0x3c
    uint32_t mBegin;        // +0x40
    uint32_t mFreeChain;    // +0x44
    uint8_t  pad_48[0x50 - 0x48];
    void*    mpMapHeader;   // +0x50  ordered-map header node
    void*    mpMapRoot;     // +0x58
    uint8_t  pad_5c[0x70 - 0x5c];
    int32_t  mTickState;    // +0x70  (1 => the slot vector must be walked)

    uint32_t blockCount() const
    { return (uint32_t)((char*)mpBlocksEnd - (char*)mpBlocks) >> 2; }
    // Slot index one past the last slot of the block array.
    uint32_t indexEnd() const { return blockCount() * 0x80 - 0x7f + mBegin; }
};

// Node of the ordered map embedded at InteractionAgentView::mpMapHeader.
struct MapNode
{
    MapNode* mpChild0;   // +0x00
    MapNode* mpChild1;   // +0x04
    uint8_t  pad_08[0x10 - 0x08];
    uint32_t mKey;       // +0x10
    int32_t  mValue;     // +0x14
    int32_t  mValue2;    // +0x18
};

struct cRenderQueue
{
    char pad[0x364];

    void FUN_00b0e560(int, int, uint32_t);                 // @ 0x00b0e560
    bool FUN_00b0e610(int);                                // @ 0x00b0e610
    void FUN_00b0e6a0();                                   // @ 0x00b0e6a0
    cRenderQueue* FUN_00b0e780(int);                       // @ 0x00b0e780
    void FUN_00b0e810(int);                                // @ 0x00b0e810
    void FUN_00b0e890();                                   // @ 0x00b0e890
    int  FUN_00b0e920();                                   // @ 0x00b0e920
    void FUN_00b0ea30();                                   // @ 0x00b0ea30
    void FUN_00b0eae0(int, int);                           // @ 0x00b0eae0
    int  FUN_00b0ee10(int);                                // @ 0x00b0ee10
};