#include "types.h"

// ---------------------------------------------------------------------------
// Shared views over the retail SP::cPlayer object and the containers it owns.
// Every field used below is named; no raw-offset accesses.
// ---------------------------------------------------------------------------

// Element of the eastl::map<unsigned, unsigned> flag map at +0x11d8.
// The lower-bound helper returns a pointer straight at this pair.
struct cFlagPair {
    uint32_t mKey;         // +0x00
    uint8_t  mValue;       // +0x04
};

// Node of an eastl::map<unsigned, X> tree (left/right/parent then the pair).
struct cMapNode {
    cMapNode*  mLeft;      // +0x00
    cMapNode*  mRight;     // +0x04
    cMapNode*  mParent;    // +0x08
    uint8_t    mPad0c[0x04]; // +0x0c
    uint32_t   mKey;       // +0x10
    uint32_t   mValue;     // +0x14
};

// eastl::rbtree header as consumed by this slice: end node at +4, root at +0x0c.
struct cTree {
    uint8_t    mPad00[0x04]; // +0x00
    cMapNode*  mEnd;       // +0x04
    uint8_t    mPad08[0x04]; // +0x08
    cMapNode*  mRoot;      // +0x0c

    // 0x00c7a8f0
    uint32_t* MapEntry(const uint32_t& key);
    // 0x00e5c780
    cMapNode** Find(cMapNode** out, const uint32_t* key);
};

struct cTimerElem {                    // eastl::pair<unsigned, SP::cGonzagoTimer>, stride 0x28
    uint32_t mKey;                     // +0x00
    uint32_t mPad04;                   // +0x04
    uint32_t mTimerVtable;             // +0x08
    uint32_t mRefCount;                // +0x0c
    uint32_t mElapsedLo;               // +0x10
    uint32_t mElapsedHi;               // +0x14
    uint32_t mBaseLo;                  // +0x18
    uint32_t mBaseHi;                  // +0x1c
    uint8_t  mbRunning;                // +0x20
    uint8_t  mPad21[0x03];             // +0x21
    uint32_t mFn;                      // +0x24

    // cGonzagoTimer copy constructor (constructs this from src); __thiscall.
    void Construct(const cTimerElem* src);                              // 0x00c76f10
};

struct cNatElem {                      // 0x14 bytes
    uint32_t mId;                      // +0x00
    uint8_t  mPad04[0x10];             // +0x04
};

// ---------------------------------------------------------------------------
// External helpers (retail addresses in comments; not defined here).
// ---------------------------------------------------------------------------
uint8_t* lowerBound(cFlagPair* begin, cFlagPair* end, const uint32_t* key, uint8_t flag); // 0x00d01260
uint32_t* mapInsertOrAssign(uint32_t* hintOut, cMapNode* hint, uint32_t* query, uint32_t flag); // 0x00abff10
uint8_t* eastlCopyImpl(void* dst, void* src, void* last);                                 // 0x00c771e0
struct cGonzagoTimer { void Dtor(); };                                                     // 0x00b638b0
void     FUN_00db5b30(void* elem);                                                        // 0x00db5b30
void     vectorErase(void* a, void* b);                                                   // 0x00b48e40
struct cStarRecordRefView {                                                              // SP::cStarRecordRef
    int32_t  GetCommContext();                                                             // 0x00ce6950
    void*    SortBanners();                                                                // 0x00b8de30
    uint8_t  mPad08[0x68];                                                                 // +0x08
    uint32_t mId;                                                                          // +0x70
};
struct cAvatarHost { void* GetAvatar(); };                                                 // 0x00b1fdb0

struct cSPTimerView { uint64_t GetElapsedTime(); };                                       // 0x00bc3190
void*    GetSpaceCombatTuning();                                                          // 0x01029940
struct cTuningView { int32_t GetCaptureDecayTimeS(); };                                   // 0x01029c80
void*    StarManager(uint32_t handle);                                                    // 0x00b3d2a0
int32_t  BannerListFun(void* bannerList, uint32_t handle);                                // 0x00ba6d80
void     FUN_00c8c9d0(int32_t value);                                                     // 0x00c8c9d0

// ---------------------------------------------------------------------------
// SP::cPlayer
// ---------------------------------------------------------------------------
namespace SP {

struct cPlayer {
    uint8_t    mPad0000[0x113c];       // +0x0000
    cNatElem*  mNatTable;              // +0x113c  (0x14-stride element table)

    uint8_t    mPad1140[0x11d8 - 0x1140]; // +0x1140
    cFlagPair* mFlagMapRoot;           // +0x11d8
    cFlagPair* mFlagMapEnd;            // +0x11dc
    uint8_t    mPad11e0[0x11ec - 0x11e0]; // +0x11e0
    uint8_t    mFlagCompareFlag;       // +0x11ec

    uint8_t    mPad11ed[0x1214 - 0x11ed]; // +0x11ed
    cTimerElem* mCaptureBegin;         // +0x1214
    cTimerElem* mCaptureEnd;           // +0x1218

    uint8_t    mPad121c[0x1228 - 0x121c]; // +0x121c
    cTree      mCMap;                  // +0x1228

    // 0x00c7a6c0  map flag bit 0
    bool GetFlag0(uint32_t key);
    // 0x00c7a710  map flag bit 1
    bool GetFlag1(uint32_t key);
    // 0x00c7a770  map flag bit 2
    bool GetFlag2(uint32_t key);
    // 0x00c7a7d0  map flag bit 3
    bool GetFlag3(uint32_t key);
    // 0x00c7a830  map flag bit 4
    bool GetFlag4(uint32_t key);
    // 0x00c7a890  map flag bit 5
    bool GetFlag5(uint32_t key);
    // 0x00c7ad00  nat-table dispatch
    void NatOp(uint32_t index, void* arg);
    // 0x00c7ad40  remove a star from the capture progress list
    void RemoveStarFromPlayerCaptureProgressList(cStarRecordRefView* star);
    // 0x00c7ae80  ensure the embassy entry for a star
    void FUN_00c7ae80(cStarRecordRefView* star);
    // 0x00c7ada0  decay the capture progress list
    void UpdatePlayerCaptureProgressDecay();
};

// 0x00c7a6c0
bool cPlayer::GetFlag0(uint32_t key)
{
    cFlagPair* end = mFlagMapEnd;
    uint8_t* it = lowerBound(mFlagMapRoot, end, &key, mFlagCompareFlag);
    if (it == (uint8_t*)end || key < ((cFlagPair*)it)->mKey || it + 8 == it) {
        it = (uint8_t*)end;
    }
    if (it == (uint8_t*)end) {
        return 0;
    }
    return ((cFlagPair*)it)->mValue & 1;
}

// 0x00c7a710
bool cPlayer::GetFlag1(uint32_t key)
{
    cFlagPair* end = mFlagMapEnd;
    uint8_t* it = lowerBound(mFlagMapRoot, end, &key, mFlagCompareFlag);
    if (it == (uint8_t*)end || key < ((cFlagPair*)it)->mKey || it + 8 == it) {
        it = (uint8_t*)end;
    }
    if (it == (uint8_t*)end) {
        return 0;
    }
    return (((cFlagPair*)it)->mValue >> 1) & 1;
}

// 0x00c7a770
bool cPlayer::GetFlag2(uint32_t key)
{
    cFlagPair* end = mFlagMapEnd;
    uint8_t* it = lowerBound(mFlagMapRoot, end, &key, mFlagCompareFlag);
    if (it == (uint8_t*)end || key < ((cFlagPair*)it)->mKey || it + 8 == it) {
        it = (uint8_t*)end;
    }
    if (it == (uint8_t*)end) {
        return 0;
    }
    return (((cFlagPair*)it)->mValue >> 2) & 1;
}

// 0x00c7a7d0
bool cPlayer::GetFlag3(uint32_t key)
{
    cFlagPair* end = mFlagMapEnd;
    uint8_t* it = lowerBound(mFlagMapRoot, end, &key, mFlagCompareFlag);
    if (it == (uint8_t*)end || key < ((cFlagPair*)it)->mKey || it + 8 == it) {
        it = (uint8_t*)end;
    }
    if (it == (uint8_t*)end) {
        return 0;
    }
    return (((cFlagPair*)it)->mValue >> 3) & 1;
}

// 0x00c7a830
bool cPlayer::GetFlag4(uint32_t key)
{
    cFlagPair* end = mFlagMapEnd;
    uint8_t* it = lowerBound(mFlagMapRoot, end, &key, mFlagCompareFlag);
    if (it == (uint8_t*)end || key < ((cFlagPair*)it)->mKey || it + 8 == it) {
        it = (uint8_t*)end;
    }
    if (it == (uint8_t*)end) {
        return 0;
    }
    return (((cFlagPair*)it)->mValue >> 4) & 1;
}

// 0x00c7a890
bool cPlayer::GetFlag5(uint32_t key)
{
    cFlagPair* end = mFlagMapEnd;
    uint8_t* it = lowerBound(mFlagMapRoot, end, &key, mFlagCompareFlag);
    if (it == (uint8_t*)end || key < ((cFlagPair*)it)->mKey || it + 8 == it) {
        it = (uint8_t*)end;
    }
    if (it == (uint8_t*)end) {
        return 0;
    }
    return (((cFlagPair*)it)->mValue >> 5) & 1;
}

// 0x00c7ad00  nat-table element dispatch
void cPlayer::NatOp(uint32_t index, void* arg)
{
    if (index < 10) {
        FUN_00db5b30(&mNatTable[index]);
        return;
    }
    vectorErase(*(void**)arg, *(void**)((char*)arg + 4));
}

// 0x00c7ad40  remove a star from the capture progress list
void cPlayer::RemoveStarFromPlayerCaptureProgressList(cStarRecordRefView* star)
{
    cTimerElem* begin = mCaptureBegin;
    cTimerElem* end   = mCaptureEnd;
    if (begin == end) {
        return;
    }
    uint32_t id = *(uint32_t*)((char*)star + 0x70);
    do {
        if (begin->mKey == id) {
            goto found;
        }
        begin = (cTimerElem*)((char*)begin + 0x28);
    } while (begin != end);
    return;
found:
    if ((cTimerElem*)((char*)begin + 0x28) < mCaptureEnd) {
        eastlCopyImpl((char*)begin + 0x28, mCaptureEnd, begin);
    }
    mCaptureEnd = (cTimerElem*)((char*)mCaptureEnd - 0x28);
    ((cGonzagoTimer*)((char*)mCaptureEnd + 8))->Dtor();
}

// 0x00c7ae80  ensure the embassy entry for a star
void cPlayer::FUN_00c7ae80(cStarRecordRefView* star)
{
    uint32_t ctx = (uint32_t)star->GetCommContext();
    cMapNode* probe;
    cMapNode** iter = mCMap.Find(&probe, &ctx);
    if ((char*)*iter == (char*)&mCMap.mEnd) {
        uint32_t key2 = (uint32_t)star->GetCommContext();
        uint32_t* entry = mCMap.MapEntry(key2);
        entry[1] = 0;
        *entry = (uint32_t)((cAvatarHost*)star->SortBanners())->GetAvatar();
    }
}

} // namespace SP

// 0x00c7ada0  decay the capture progress list
void SP::cPlayer::UpdatePlayerCaptureProgressDecay()
{
    cTimerElem* begin = mCaptureBegin;
    if (begin == mCaptureEnd) {
        return;
    }
    do {
        cSPTimerView* timer = (cSPTimerView*)((char*)begin + 8);
        uint64_t elapsed = timer->GetElapsedTime();
        cTuningView* tuning = (cTuningView*)GetSpaceCombatTuning();
        int32_t  decayTime = tuning->GetCaptureDecayTimeS();
        float    seconds = (float)(int64_t)elapsed * 0.001f;
        if (seconds <= (float)decayTime) {
            return;
        }
        uint32_t handle = begin->mKey;
        int32_t  value  = BannerListFun(StarManager(handle), handle);
        FUN_00c8c9d0(value);
        if ((cTimerElem*)((char*)begin + 0x28) < mCaptureEnd) {
            eastlCopyImpl((char*)begin + 0x28, mCaptureEnd, begin);
        }
        mCaptureEnd = (cTimerElem*)((char*)mCaptureEnd - 0x28);
        ((cGonzagoTimer*)((char*)mCaptureEnd + 8))->Dtor();
    } while (begin != mCaptureEnd);
}

// 0x00c7a8f0  eastl::map::operator[]-style find-or-insert (value at node+0x14)
uint32_t* cTree::MapEntry(const uint32_t& key)
{
    cMapNode* node  = mRoot;
    cMapNode* found = mEnd;
    while (node != 0) {
        if (node->mKey < key) {
            node = node->mLeft;
        } else {
            found = node;
            node = node->mRight;
        }
    }
    if (found != mEnd && found->mKey <= key) {
        return &found->mValue;
    }
    uint32_t query[3];
    query[0] = key;
    query[1] = 0;
    query[2] = 0;
    uint32_t flag = 0;
    mapInsertOrAssign((uint32_t*)&found, found, query, flag);
    return (uint32_t*)((char*)found + 0x14);
}

// ---------------------------------------------------------------------------
// Stream-backed vector readers (EASTL vector instantiations)
// ---------------------------------------------------------------------------

// Serialiser read primitive (also declared below for the quad-vector reader).
void ReadInt32(void* reader, int* out, int count, int flags);          // 0x0093a780

// Deserialiser node interface (vtable +0x18 reader, +0x1c end-entry, +0x20 sub-node).
class IStreamNode {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void* GetReader();           // +0x18
    virtual void EndChunk();             // +0x1c
    virtual IStreamNode* GetSubNode();   // +0x20
};

// eastl::vector<unsigned int> (4-byte elements).
struct U32Vector {
    uint32_t* mpBegin;                   // +0x0
    uint32_t* mpEnd;                     // +0x4
    uint32_t* mpCapacity;                // +0x8

    void Clear();                        // inlined clear()
    void Reserve(uint32_t n);            // 0x00c77b60
    void PushBack(const uint32_t& value); // fast path + slow DoInsertValue
    void DoInsertValue(uint32_t* position, const uint32_t& value);  // 0x00cd0550
};

// eastl's memmove wrapper used by the range algorithms.
void EastlMove(void* dst, const void* src, unsigned bytes);            // 0x011e0744

void U32Vector::Clear()
{
    EastlMove(mpBegin, mpEnd, 0);
    mpEnd -= (mpEnd - mpBegin);
}

void U32Vector::PushBack(const uint32_t& value)
{
    if (mpEnd < mpCapacity) {
        uint32_t* p = mpEnd;
        mpEnd = p + 1;
        if (p)
            *p = value;
    } else {
        DoInsertValue(mpEnd, value);
    }
}

// @ 0x00c7a970
void FUN_00c7a970(IStreamNode* stream, U32Vector* vec)
{
    vec->Clear();

    uint32_t count = 0;
    IStreamNode* node = stream->GetSubNode();
    void* reader = node->GetReader();
    ReadInt32(reader, (int*)&count, 1, 0);
    vec->Reserve(count);

    for (uint32_t i = 0; i < count; ++i) {
        IStreamNode* itemNode = stream->GetSubNode();
        void* itemReader = itemNode->GetReader();
        uint32_t value;
        ReadInt32(itemReader, (int*)&value, 1, 0);
        vec->PushBack(value);
    }
    stream->EndChunk();
}

// eastl::vector<eastl::pair<unsigned int, SP::cGonzagoTimer>> (0x28-byte elements).
// The pair's copy assignment only touches the timer's state fields, not its
// vtable/refcount words, so the copy helpers below do the same.

// Range copy-construct [first,last) into dst; returns the new end.
cTimerElem* TimerConstructRange(cTimerElem* first, cTimerElem* last, cTimerElem* dst); // 0x00c77160
// Range copy-assign [first,last) backwards ending at dst; returns new begin.
cTimerElem* TimerCopyBackward(cTimerElem* first, cTimerElem* last, cTimerElem* dst);  // 0x00c77250
// Range destroy [first,last) (dst only carries the return value).
void TimerDestroyRange(cTimerElem* first, cTimerElem* last, cTimerElem* dst);         // 0x0100daa0
void* EastlAllocate(unsigned size, const char* name, int flags, unsigned debugFlags,
                    const char* file, int line);                        // 0x00f473a0
void  EastlFree(void* p);                                               // 0x00f47380

struct cTimerVector {
    cTimerElem* mpBegin;                 // +0x0
    cTimerElem* mpEnd;                   // +0x4
    cTimerElem* mpCapacity;              // +0x8

    void Insert(cTimerElem* position, const cTimerElem& value);          // 0x00c7aa40
};

// @ 0x00c7aa40
void cTimerVector::Insert(cTimerElem* position, const cTimerElem& value)
{
    if (mpEnd != mpCapacity) {
        const cTimerElem* source = &value;
        // Self-insertion fixup (EASTL adjusts a value that lives in the vector).
        if ((const char*)source >= (const char*)position && source < mpEnd)
            source = (const cTimerElem*)((const char*)source + 0x28);

        if (mpEnd != 0)
            mpEnd->Construct(mpEnd - 1);
        TimerCopyBackward(position, mpEnd - 1, mpEnd);

        position->mKey       = source->mKey;
        position->mElapsedLo = source->mElapsedLo;
        position->mElapsedHi = source->mElapsedHi;
        position->mBaseLo    = source->mBaseLo;
        position->mBaseHi    = source->mBaseHi;
        position->mbRunning  = source->mbRunning;
        position->mFn        = source->mFn;
        mpEnd = mpEnd + 1;
        return;
    }

    int count = (int)(mpEnd - mpBegin);
    int newCapacity;
    cTimerElem* buffer;
    if (count == 0) {
        newCapacity = 1;
    } else {
        newCapacity = count * 2;
        if (newCapacity == 0) {
            buffer = 0;
            goto haveBuffer;
        }
    }
    buffer = (cTimerElem*)EastlAllocate(newCapacity * 0x28, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
haveBuffer:
    cTimerElem* mid = TimerConstructRange(mpBegin, position, buffer);
    TimerDestroyRange(mpBegin, position, buffer);
    if (mid)
        mid->Construct(&value);

    cTimerElem* newEnd = TimerConstructRange(position, mpEnd, mid + 1);
    TimerDestroyRange(position, mpEnd, mid + 1);

    if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
        EastlFree(mpBegin);

    mpEnd = newEnd;
    mpBegin = buffer;
    mpCapacity = (cTimerElem*)((char*)buffer + newCapacity * 0x28);
}
