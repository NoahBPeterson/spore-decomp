// slice s0070c040: cLightingWorld local-light sample plumbing (add/update light,
// lighting-info allocation, local-light sample creation) plus the spstl
// slot-vector `create` helpers and the local-light-info deque destructor.
// /O2 + SSE region.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include <new>
#include "types.h"

// eastl's deallocator never throws; declaring it that way keeps the compiler
// from adding a second unwind state around the call sites in destructors.
void __cdecl EastlFree(void* p) throw();                          // 0x00F47380
bool __cdecl IsNAN(const void* value);                            // 0x00481F00
bool __cdecl ValidateColour(const void* colour);                  // 0x0059AB70
int  __cdecl ComputeSampleId(const void* colour, float scale);    // 0x007052E0
int  __cdecl ComputeCellB(const void* colour, float scale);       // 0x00705470
int  __cdecl ComputeCellA(const void* colour, const void* grid,
                          float scale);                           // 0x00705660

struct Vec3 { float x, y, z; };

// ===========================================================================
// heap-backed eastl vector (mBlocks of the slot-vector deque) and the
// intrusive-list node embedded in the local-light cell entries
// ===========================================================================
struct ListLink {
    ListLink* mpNext;       // +0x00
    ListLink* mpPrev;       // +0x04
    ~ListLink();            // 0x00620230 unlinks the node from its list
};

struct ElemVector {
    void* mpBegin;          // +0x00
    void* mpEnd;            // +0x04
    void* mpCapacity;       // +0x08
    int   mAllocField;      // +0x0c
    ~ElemVector()
    {
        // eastl heap allocations carry their size in the dword before the block;
        // a zero size means the storage was never taken from the heap.
        if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0)
            EastlFree(mpBegin);
    }
};

// One 0x34-byte payload of the small (local-light cell) slot vector.
struct LocalCellEntry {
    ElemVector mVec0;       // +0x00
    ElemVector mVec1;       // +0x10
    int        mField24;    // +0x24
    int        mField28;    // +0x28
    ListLink   mLink;       // +0x2c
    LocalCellEntry(const LocalCellEntry& x);   // 0x0070A130
};

// ===========================================================================
// fixed_vector<cCellInfo, 16> used by cLocalLightInfo
// ===========================================================================
struct CellInfo { int x, y; };
struct FixedCellVector;

struct CellAllocator {
    int   mField0;          // +0x00
    void* mpPoolBegin;      // +0x04 (inline pool start)
    int   mField8;          // +0x08
};

struct CellVectorBase {
    CellInfo* mpBegin;      // +0x00
    CellInfo* mpEnd;        // +0x04
    CellInfo* mpCapacity;   // +0x08
    CellAllocator mAllocator;   // +0x0c (0x0c bytes; mpPoolBegin at +0x10)
    void DoAssignFromIterator(const CellInfo* first, const CellInfo* last,
                              const FixedCellVector* src);        // 0x00708340
    // The vector base owns the storage, so a copying constructor of the
    // derived fixed_vector has to tear it down if the element copy throws.
    ~CellVectorBase()
    {
        if (mpBegin != 0 && mpBegin != (CellInfo*)mAllocator.mpPoolBegin)
            EastlFree(mpBegin);
    }
};

struct FixedCellVector : CellVectorBase {
    CellInfo mBuffer[16];       // +0x18
    FixedCellVector(const FixedCellVector& x);   // 0x0070C3A0
};

// @ 0x0070c3a0
FixedCellVector::FixedCellVector(const FixedCellVector& x)
{
    CellInfo* p = mBuffer;
    mAllocator.mpPoolBegin = p;
    mpEnd = p;
    mpBegin = p;
    mpCapacity = p + 16;
    DoAssignFromIterator(x.mpBegin, x.mpEnd, &x);
}

struct cLocalLightInfo {
    Vec3 mColour;           // +0x00
    float mSize;            // +0x0c
    Vec3 mPosition;         // +0x10
    float mStrength;        // +0x1c
    void* mDecal;           // +0x20
    bool  mGlobal;          // +0x24
    uint8_t mPad25[3];      // +0x25
    FixedCellVector mCells; // +0x28
    cLocalLightInfo(const cLocalLightInfo& x);   // 0x0070C7C0
};

// @ 0x0070c7c0
cLocalLightInfo::cLocalLightInfo(const cLocalLightInfo& x)
    : mColour(x.mColour), mSize(x.mSize), mPosition(x.mPosition), mStrength(x.mStrength),
      mDecal(x.mDecal), mGlobal(x.mGlobal), mCells(x.mCells)
{
}

// ===========================================================================
// slot-vector payloads
// ===========================================================================
// 0x1e0-byte cached environment-light sample.  Only the head fields are ever
// initialised by the creators; the copy ctor handles the rest.
struct EnvEntry {
    uint8_t  mField000;     // +0x000
    uint8_t  mField001;     // +0x001
    short    mField002;     // +0x002
    float    mColourX;      // +0x004
    float    mColourY;      // +0x008
    float    mColourZ;      // +0x00c
    float    mSize;         // +0x010
    uint8_t  mPad014[0x0c]; // +0x014
    uint32_t mField020[4];  // +0x020
    uint8_t  mTail[0x19c];  // +0x030
    uint32_t mRefCount;     // +0x1cc
    int      mGridIndex;    // +0x1d0
    uint8_t  mPad1d4[0x0c]; // +0x1d4
    EnvEntry() {}
    EnvEntry(const EnvEntry& x);   // 0x007068C0
};

// 0x1d0-byte local-light cell payload.
struct LocalLightCell {
    uint8_t  mField00;      // +0x000
    uint8_t  mField01;      // +0x001
    short    mField02;      // +0x002
    float    mField04;      // +0x004
    float    mField08;      // +0x008
    float    mField0c;      // +0x00c
    float    mField10;      // +0x010
    uint8_t  mField14[0x0c];// +0x014
    uint32_t mField20[4];   // +0x020
    uint8_t  mField30[0x190]; // +0x030
    void*    mInfo;         // +0x1c0 owning lighting-info entry
    uint32_t mPad1c4[3];    // +0x1c4
    LocalLightCell() {}
    LocalLightCell(const LocalLightCell& x);   // 0x00705B50
};

// ===========================================================================
// spstl::slot_vector headers (0x20 bytes each)
// ===========================================================================
struct EnvSlotVector {
    void** mpBlocks;        // +0x00
    void** mpBlocksEnd;     // +0x04
    void** mpBlocksCapacity; // +0x08
    int    mField0c;        // +0x0c
    int    mField10;        // +0x10
    int    mLastIndex;      // +0x14
    int    mMinFree;        // +0x18
    int    mFreeList;       // +0x1c
    uint32_t create(const EnvEntry& init);   // 0x0070C090
    EnvEntry* at(int id);                    // 0x00706870
    void Grow();                             // 0x00708C40
};

struct CellSlotVector {
    void** mpBlocks;        // +0x00
    void** mpBlocksEnd;     // +0x04
    void** mpBlocksCapacity; // +0x08
    int    mField0c;        // +0x0c
    int    mField10;        // +0x10
    int    mLastIndex;      // +0x14
    int    mMinFree;        // +0x18
    int    mFreeList;       // +0x1c
    uint32_t create(const LocalLightCell& init);   // 0x0070C200
    LocalLightCell* at(int id);                    // 0x00706230 (unused here)
    void Grow();                                   // 0x00708CB0
};

struct SmallSlotVector {
    void** mpBlocks;        // +0x00
    void** mpBlocksEnd;     // +0x04
    void** mpBlocksCapacity; // +0x08
    int    mField0c;        // +0x0c
    int    mField10;        // +0x10
    int    mLastIndex;      // +0x14
    int    mMinFree;        // +0x18
    int    mFreeList;       // +0x1c
    uint32_t create(const LocalCellEntry& init);   // 0x0070C5E0
    LocalCellEntry* at(int id);                    // 0x00706890
    void Grow();                                   // 0x00708D20
};

struct LocalInfoSlotVector {
    void** mpBlocks;        // +0x00
    void** mpBlocksEnd;     // +0x04
    void** mpBlocksCapacity; // +0x08
    int    mField0c;        // +0x0c
    int    mField10;        // +0x10
    int    mLastIndex;      // +0x14
    int    mMinFree;        // +0x18
    int    mFreeList;       // +0x1c
    uint32_t create(const cLocalLightInfo& init);  // 0x0070CCE0
    cLocalLightInfo* at(int id);                   // 0x00706870 (unused here)
    void Grow();                                   // 0x00708BD0
};

// Payload address for a slot index; the callers that were compiled with the
// address computation inlined (instead of calling at()) expand this helper.
template <class Entry, int STRIDE, int PAYLOAD>
__forceinline Entry* PayloadAt(void** blocks, int id)
{
    return (Entry*)((char*)blocks[id >> 7] + (id & 0x7f) * STRIDE + PAYLOAD);
}

// Intrusive list pass; only the small slot payload owns a list node.
__forceinline void LinkSelf(LocalCellEntry* e)
{
    e->mLink.mpNext = &e->mLink;
    e->mLink.mpPrev = &e->mLink;
}
template <class T> __forceinline void LinkSelf(T*) {}

// Extra payload field the copy ctor of the cell sample does not cover.
__forceinline void CopyExtra(LocalLightCell* dst, const LocalLightCell& src)
{
    dst->mInfo = src.mInfo;
}
template <class T> __forceinline void CopyExtra(T*, const T&) {}

template <class Vec, class Entry, int STRIDE, int PAYLOAD>
__forceinline uint32_t CreateSlot(Vec* v, const Entry& init)
{
    uint32_t id = (uint32_t)v->mFreeList;
    Entry* result;
    if (id == 0x3fffffffu) {
        Entry temp(init);
        LinkSelf(&temp);
        id = (uint32_t)((int)(v->mpBlocksEnd - v->mpBlocks) * 0x80 - 0x7f + v->mLastIndex);
        v->Grow();
        uint32_t* last = (uint32_t*)((char*)v->mpBlocksEnd[-1] + v->mLastIndex * STRIDE);
        if (last != 0)
            *last = 0x80000000u;
        if (id != 0) {
            uint32_t* prev = (uint32_t*)((char*)v->mpBlocks[(id - 1) >> 7] +
                                         ((id - 1) & 0x7f) * STRIDE);
            *prev &= 0xbfffffffu;
        }
        uint32_t* hdr = (uint32_t*)((char*)v->mpBlocks[id >> 7] + (id & 0x7f) * STRIDE);
        *hdr |= 0x40000000u;
        *hdr &= 0x7fffffffu;
        result = (Entry*)((char*)hdr + PAYLOAD);
        new (result) Entry(temp);
    } else {
        uint32_t* hdr = (uint32_t*)((char*)v->mpBlocks[id >> 7] + (id & 0x7f) * STRIDE);
        v->mFreeList = (int)(*hdr & 0x3fffffffu);
        *hdr &= 0x7fffffffu;
        result = (Entry*)((char*)hdr + PAYLOAD);
        new (result) Entry(init);
    }
    CopyExtra(result, init);
    LinkSelf(result);
    if ((uint32_t)v->mMinFree > id)
        v->mMinFree = (int)id;
    return id;
}

// @ 0x0070c090
uint32_t EnvSlotVector::create(const EnvEntry& init)
{
    return CreateSlot<EnvSlotVector, EnvEntry, 0x1f0, 0x10>(this, init);
}

// @ 0x0070c200
uint32_t CellSlotVector::create(const LocalLightCell& init)
{
    return CreateSlot<CellSlotVector, LocalLightCell, 0x1e0, 0x10>(this, init);
}

// @ 0x0070c5e0
uint32_t SmallSlotVector::create(const LocalCellEntry& init)
{
    return CreateSlot<SmallSlotVector, LocalCellEntry, 0x38, 4>(this, init);
}

// @ 0x0070cce0
uint32_t LocalInfoSlotVector::create(const cLocalLightInfo& init)
{
    return CreateSlot<LocalInfoSlotVector, cLocalLightInfo, 0xc4, 4>(this, init);
}

// ===========================================================================
// lighting-info entries / pool / local-info deque
// ===========================================================================
struct LightingInfoEntry {
    void*  mpLightingInfo;  // +0x00
    ListLink mLink;         // +0x04
    Vec3   mPos;            // +0x0c
    float  mIntensity;      // +0x18
    float  mScale;          // +0x1c
    int    mCell;           // +0x20
    int    mLocalSample;    // +0x24
    int    mEnvSample;      // +0x28
    void copyFrom(const LightingInfoEntry* other);   // 0x00705BB0
};

struct LightingInfoPool {
    uint8_t  mPad00[0x18];  // +0x00
    LightingInfoEntry* mpUsed;      // +0x18
    LightingInfoEntry* mpBlockEnd;  // +0x1c
    LightingInfoEntry* mpLimit;     // +0x20
    void**   mpBlocks;              // +0x24
    int      mField28;              // +0x28
    LightingInfoEntry** mpFreeBegin; // +0x2c
    LightingInfoEntry** mpFreeEnd;   // +0x30
    uint8_t  mPad34[0x10];  // +0x34
    uint8_t  mInline[0x100]; // +0x44
    void grow(const LightingInfoEntry* init);   // 0x00706B50
};

struct DequeVector {
    void* mpBegin;          // +0x00
    void* mpEnd;            // +0x04
    void* mpCapacity;       // +0x08
    int   mAllocField0c;    // +0x0c
    int   mAllocField10;    // +0x10
    ~DequeVector()
    {
        if (mpBegin != 0)
            EastlFree(mpBegin);
    }
};

void __stdcall ClearDequeImpl(void* deque);   // 0x0070A1F0

struct LocalInfoSlotDeque {
    DequeVector mBlocks;    // +0x00 (0x14 bytes)
    int mBlockPos;          // +0x14
    int mField18;           // +0x18
    int mField1c;           // +0x1c
    ~LocalInfoSlotDeque();
};

// @ 0x0070c040
LocalInfoSlotDeque::~LocalInfoSlotDeque()
{
    // ClearDequeImpl frees every block but not the block-index vector itself;
    // the member vector's destructor releases that one afterwards.
    ClearDequeImpl(this);
}

// ===========================================================================
// cLightingWorld
// ===========================================================================
struct cLightingWorld {
    uint8_t  mPad000[0x18];          // +0x000
    int      mCellMode;              // +0x018
    const void* mCellData;           // +0x01c
    uint8_t  mPad020[0x240];         // +0x020
    uint8_t  mGlobalInfo[0x1c0];     // +0x260 default lighting info
    uint32_t mSentinel;              // +0x420 "no entry" result
    uint8_t  mSampleEnabled;         // +0x424
    uint8_t  mPad425[3];             // +0x425
    LocalInfoSlotDeque mInfoDeque;   // +0x428
    int      mField448;              // +0x448
    LightingInfoPool mPool;          // +0x44c
    uint8_t  mCacheEnabled;          // +0x590
    uint8_t  mPad591[3];             // +0x591
    EnvSlotVector mEnvSlots;         // +0x594
    int*     mEnvGridBegin;          // +0x5b4
    int*     mEnvGridEnd;            // +0x5b8
    int*     mEnvGridCapacity;       // +0x5bc
    uint8_t  mPad5c0[0x10];          // +0x5c0
    int      mCellGridMode;          // +0x5d0
    void*    mField5d4;              // +0x5d4
    void*    mField5d8;              // +0x5d8
    uint8_t  mPad5dc[0x24];          // +0x5dc
    ListLink mFreeListHead;          // +0x600 entries with no cell
    CellSlotVector mCellSlots;       // +0x608
    int*     mCellGridBegin;         // +0x628
    int*     mCellGridEnd;           // +0x62c
    int*     mCellGridCapacity;      // +0x630
    uint8_t  mPad634[8];             // +0x634
    SmallSlotVector mSmallSlots;     // +0x63c
    int      mField65c;              // +0x65c
    uint8_t  mField660;              // +0x660

    float ComputeScale(const void* colour, float intensity);          // 0x00705970
    void CreateEnvLightSample(EnvEntry* entry, const void* pos,
                              int gridIndex);                         // 0x007074E0
    void UpdateEnvLightSample(EnvEntry* entry);                       // 0x00706170
    void FreeEnvSample(LightingInfoEntry* entry);                     // 0x00707790
    void ReleaseLocalSample(LightingInfoEntry* entry);                // 0x00707740
    void UpdateLocalLightSample(LightingInfoEntry* entry);            // 0x00707370
    void CreateLocalLightSample(LightingInfoEntry* entry);            // 0x0070C410
    uint32_t* CreateLightingInfo(LightingInfoEntry* entry, int gridIndex); // 0x0070C4B0
    LightingInfoEntry* AddLight(float intensity, const void* colour); // 0x0070C830
    void UpdateLightingInfo(float intensity, const void* colour,
                            LightingInfoEntry* entry);                // 0x0070CAB0
};

// @ 0x0070c410
void cLightingWorld::CreateLocalLightSample(LightingInfoEntry* entry)
{
    // A fresh cell only clears the head fields; the padding at +0x14 and the
    // cell storage at +0x30 keep whatever the slot block held before.
    LocalLightCell init;
    init.mField00 = 0;
    init.mField01 = 0;
    init.mField02 = 0;
    init.mField04 = 0.0f;
    init.mField08 = 0.0f;
    init.mField0c = 0.0f;
    init.mField10 = 0.0f;
    init.mField20[0] = 0;
    init.mField20[1] = 0;
    init.mField20[2] = 0;
    init.mField20[3] = 0;
    uint32_t id = mCellSlots.create(init);
    entry->mLocalSample = (int)id;
    LocalLightCell* cell = PayloadAt<LocalLightCell, 0x1e0, 0x10>(mCellSlots.mpBlocks,
                                                                 (int)id);
    cell->mInfo = entry;
    UpdateLocalLightSample(entry);
}

// @ 0x0070c4b0
uint32_t* cLightingWorld::CreateLightingInfo(LightingInfoEntry* entry, int gridIndex)
{
    int id = -1;
    if (gridIndex >= 0)
        id = mEnvGridBegin[gridIndex];
    if (id < 0) {
        EnvEntry init;
        init.mField000 = 0;
        init.mField001 = 0;
        init.mField002 = 0;
        init.mColourX = 0.0f;
        init.mColourY = 0.0f;
        init.mColourZ = 0.0f;
        init.mSize = 0.0f;
        init.mField020[0] = 0;
        init.mField020[1] = 0;
        init.mField020[2] = 0;
        init.mField020[3] = 0;
        id = (int)mEnvSlots.create(init);
        EnvEntry* created = PayloadAt<EnvEntry, 0x1f0, 0x10>(mEnvSlots.mpBlocks, id);
        CreateEnvLightSample(created, &entry->mPos, gridIndex);
        if (gridIndex >= 0) {
            mEnvGridBegin[gridIndex] = id;
            created->mGridIndex = gridIndex;
        }
    }
    EnvEntry* payload = PayloadAt<EnvEntry, 0x1f0, 0x10>(mEnvSlots.mpBlocks, id);
    entry->mEnvSample = id;
    entry->mpLightingInfo = payload;
    payload->mRefCount++;
    return &payload->mRefCount;
}

// @ 0x0070c830
LightingInfoEntry* cLightingWorld::AddLight(float intensity, const void* colour)
{
    const Vec3* v = (const Vec3*)colour;
    if (mCacheEnabled == 0)
        return (LightingInfoEntry*)&mSentinel;
    if (!ValidateColour(colour))
        return (LightingInfoEntry*)&mSentinel;

    LightingInfoEntry init;
    init.mLink.mpNext = 0;
    init.mLink.mpPrev = 0;
    init.mPos.x = 0.0f;
    init.mPos.y = 0.0f;
    init.mPos.z = 0.0f;
    init.mIntensity = 0.0f;
    init.mScale = 1.0f;
    init.mCell = -1;
    init.mLocalSample = -1;
    init.mEnvSample = -1;

    LightingInfoEntry* entry;
    if (mPool.mpFreeBegin != mPool.mpFreeEnd) {
        entry = *(mPool.mpFreeEnd - 1);
        *entry = init;
        mPool.mpFreeEnd = mPool.mpFreeEnd - 1;
    } else {
        if (mPool.mpUsed + 1 == mPool.mpLimit) {
            mPool.grow(&init);
        } else {
            mPool.mpUsed->copyFrom(&init);
            mPool.mpUsed = mPool.mpUsed + 1;
        }
        entry = mPool.mpUsed - 1;
        if (mPool.mpUsed == mPool.mpBlockEnd)
            entry = (LightingInfoEntry*)((char*)((void**)mPool.mpBlocks)[-1] + 0xb0) - 1;
    }

    float scale = ComputeScale(colour, intensity);
    entry->mPos = *v;
    entry->mIntensity = intensity;
    entry->mScale = scale;
    entry->mpLightingInfo = mGlobalInfo;

    if (mSampleEnabled != 0 &&
        v->x * v->x + v->y * v->y + v->z * v->z >= 10.0f) {
        int sample = ComputeSampleId(colour, scale);
        CreateLightingInfo(entry, sample);
    }

    if (mCellGridMode != 0) {
        int cell = -1;
        if (mCellMode == 1)
            cell = ComputeCellA(colour, &mCellData, scale);
        else if (mCellMode == 2)
            cell = ComputeCellB(colour, scale);
        if (cell >= 0) {
            cell = mCellGridBegin[cell];
            if (cell >= 0) {
                entry->mCell = cell;
                LocalCellEntry* local = mSmallSlots.at(cell);
                entry->mLink.mpPrev = local->mLink.mpPrev;
                entry->mLink.mpNext = &local->mLink;
                entry->mLink.mpPrev->mpNext = &entry->mLink;
                local->mLink.mpPrev = &entry->mLink;
            }
        }
        if (mField5d4 != mField5d8 || entry->mCell >= 0)
            CreateLocalLightSample(entry);
    }

    if (entry->mCell < 0) {
        entry->mLink.mpPrev = mFreeListHead.mpPrev;
        entry->mLink.mpNext = &mFreeListHead;
        entry->mLink.mpPrev->mpNext = &entry->mLink;
        mFreeListHead.mpPrev = &entry->mLink;
    }
    return entry;
}

// @ 0x0070cab0
void cLightingWorld::UpdateLightingInfo(float intensity, const void* colour,
                                        LightingInfoEntry* entry)
{
    const Vec3* v = (const Vec3*)colour;
    if (entry == (LightingInfoEntry*)&mSentinel)
        return;
    if (mCacheEnabled == 0)
        return;
    if (IsNAN(colour))
        return;

    float scale = ComputeScale(colour, intensity);
    entry->mPos = *v;
    entry->mIntensity = intensity;

    if (mSampleEnabled != 0 &&
        v->x * v->x + v->y * v->y + v->z * v->z >= 10.0f) {
        int sample = ComputeSampleId(colour, scale);
        int old = entry->mEnvSample;
        if (old >= 0 && mEnvSlots.at(old)->mGridIndex == sample) {
            if (sample < 0)
                UpdateEnvLightSample(mEnvSlots.at(old));
        } else {
            if (old >= 0)
                FreeEnvSample(entry);
            CreateLightingInfo(entry, sample);
        }
    } else {
        entry->mEnvSample = -1;
        entry->mpLightingInfo = mGlobalInfo;
    }

    if (mCellGridMode == 0)
        return;

    int cell = -1;
    if (mCellMode == 1)
        cell = ComputeCellA(colour, &mCellData, scale);
    else if (mCellMode == 2)
        cell = ComputeCellB(colour, scale);
    if (cell >= 0)
        cell = mCellGridBegin[cell];

    bool hadLocal = entry->mLocalSample >= 0;
    if (entry->mCell != cell) {
        entry->mLink.mpPrev->mpNext = entry->mLink.mpNext;
        entry->mLink.mpNext->mpPrev = entry->mLink.mpPrev;
        entry->mLink.mpNext = 0;
        entry->mLink.mpPrev = 0;
        if (cell >= 0) {
            entry->mCell = cell;
            LocalCellEntry* local = mSmallSlots.at(cell);
            entry->mLink.mpPrev = local->mLink.mpPrev;
            entry->mLink.mpNext = &local->mLink;
            entry->mLink.mpPrev->mpNext = &entry->mLink;
            local->mLink.mpPrev = &entry->mLink;
            if (entry->mLocalSample < 0)
                CreateLocalLightSample(entry);
        } else {
            entry->mCell = -1;
            entry->mLink.mpPrev = mFreeListHead.mpPrev;
            entry->mLink.mpNext = &mFreeListHead;
            entry->mLink.mpPrev->mpNext = &entry->mLink;
            mFreeListHead.mpPrev = &entry->mLink;
            if (mField5d4 == mField5d8 && entry->mLocalSample >= 0)
                ReleaseLocalSample(entry);
        }
    }
    if (hadLocal)
        UpdateLocalLightSample(entry);
}
