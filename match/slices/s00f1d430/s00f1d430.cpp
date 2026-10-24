// Slice s00f1d430 - scenario/feedback bookkeeping of the cSPUILayoutManager family.
// /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
// The time formatter (00f1dc50) comes from a VC7.1-built translation unit - it divides by 60
// with `idiv` where cl15 always uses a magic multiply - so its manifest row carries /vc71.
//
// The manager (PB) owns an array of 0x1ac-byte scenario entries (PBEl).  Each entry keeps a
// map of already-fired feedback events (eastl::rbtree<unsigned, AutoRefCount<cFeedbackEvent>>),
// a list of "worlds" and a weight.  Events arriving from a script packet either get added to
// the running scenario (types 4/5) or handled through the per-index path (type 3).

typedef unsigned int uint;

#if _MSC_VER < 1400
typedef unsigned short wchar_t;        // VC7.1 has no native wchar_t
#endif

struct WStr;
WStr* __cdecl WStr_Format(WStr* pOut, const wchar_t* pFormat, ...);   // 0x0041e050
void __cdecl EASTL_allocator_deallocate(void* p);                       // 0x00f47380

struct CString {
    uint mPad[5];
    const wchar_t* GetText();        // 0x006b55c0
    void Release();                  // 0x006b5240 (out-of-line destructor body)
};

void __cdecl InitTimeString(CString* pOut);   // 0x00f39110

// ---- feedback event map ----------------------------------------------------
// Iterator returned by value (8 bytes, returned through a hidden pointer).
struct EvIter {
    void* mpNode;                    // +0x00
    void* mpOwner;                   // +0x04
};

// The map's insert helper takes (and ignores) a small tag object; only its first byte is
// ever initialised by the caller, so it is modelled as a 4-byte pass-by-value aggregate.
struct InsertTag {
    bool mbAtEnd;                    // +0x00
    char mPad[3];                    // +0x01
};

struct EvNode {                      // rbtree node
    EvNode* mpLeft;                  // +0x00
    EvNode* mpNext;                  // +0x04
};

struct EventMap {                    // eastl::rbtree<unsigned, AutoRefCount<cFeedbackEvent>>
    uint    mSize;                   // +0x00
    void*   mAnchor;                 // +0x04 (its address is end())
    uint    mPad08;                  // +0x08
    EvNode* mpRoot;                  // +0x0c

    EvIter find(const uint& key);                        // 0x00e5c780
    void   insert(EvIter* pResult, uint key, InsertTag tag);   // 0x00a17a70
    void   DoNukeSubtree(EvNode* pNode);                 // 0x009a9600
};

// ---- scenario entry --------------------------------------------------------
struct WorldPart {                   // body of a world record
    void Free();                     // 0x00f280f0
};

struct World {                       // 0x44-byte element of an entry's world list
    uint      mId;                   // +0x00
    WorldPart mPart;                 // +0x04
    char      mPad08[0x3c];          // +0x08
};

struct PB;

struct PBEl {                        // 0x1ac-byte scenario entry
    bool      mbDisabled;            // +0x00
    char      mPad01[7];             // +0x01
    EventMap  mEvents;               // +0x08
    char      mPad18[0x0c];          // +0x18
    int       mnType;                // +0x24
    int       mnId;                  // +0x28
    char      mPad2c[0x10];          // +0x2c
    World*    mpWorldBegin;          // +0x3c
    World*    mpWorldEnd;            // +0x40
    char      mPad44[0x1ac - 0x44];  // +0x44

    void Destroy();                  // 0x00f1dec0
};

// ---- 16-byte string vector --------------------------------------------------
// The scenario keeps its strings (feedback text) in an eastl vector of 16-byte elements.
struct Elem16 {
    char mData[16];
};

void* __cdecl CopyStrings(void* pFirst, void* pLast, void* pDest);   // 0x007c8b70
void* __cdecl UninitializedCopy(void* pOut, void* pFirst, void* pLast, void* pDest,
                                void* pExtra);                       // 0x00555aa0

struct ElemVector {
    Elem16* mpBegin;      // +0x00
    Elem16* mpEnd;        // +0x04
    Elem16* mpCapacity;   // +0x08

    Elem16* Grow(int nCount, Elem16* pFirst, Elem16* pLast);        // 0x007f1b90
    void    DestroyRange(Elem16* pFirst, Elem16* pLast);            // 0x006a4950
    void    Assign(Elem16* pFirst, Elem16* pLast, int nUnused);     // 0x00f1dcc0
};

// Event descriptor carried by the script packet; the lookup of the referenced event object is
// the fourth virtual of the packet class.
struct PBPacket {
    virtual void* mSlot0();
    virtual void* mSlot1();
    virtual void* mSlot2();
    virtual void* GetEventRef(uint nId, int nArg);
    char     mPad04[0x18];           // +0x04
    int      mnId;                   // +0x1c
    char     mPad20[4];              // +0x20
    uint     mnKey;                  // +0x24
};

// one-shot event reference id handed to the packet's virtual lookup
enum { kPacketRef = 0x1186577 };

struct GBlock {                      // *0x016c7aa4
    char  mPad00[0x6c];
    void* mpf_6c;                    // +0x6c
};
extern GBlock* g_16c7aa4;
void FUN_00f0e6c0(void* p);          // 0x00f0e6c0

struct PB {                          // scenario manager
    char   mPad00[0x1c];             // +0x00
    int    mCount;                   // +0x1c
    char   mPad20[0x64 - 0x20];      // +0x20
    PBEl*  mpBegin;                  // +0x64
    PBEl*  mpEnd;                    // +0x68
    char   mPad6c[0x90 - 0x6c];      // +0x6c
    int    mState;                   // +0x90
    char   mPad94[0xbc - 0x94];      // +0x94
    int    mTime;                    // +0xbc
    char   mPadc0[0xec - 0xc0];      // +0xc0
    char   mf_ec;                    // +0xec

    void Add(PBEl* e, void* a, void* b);                             // 0x00f1ae10
    bool FireType3(PBEl* e, bool* pFlag, void** ppA, void** ppB);    // 0x00f1d5d0
    void FireType4(PBPacket* pPacket);                               // 0x00f1d430
    void FireType5(PBPacket* pPacket);                               // 0x00f1d500
    void FormatTime(WStr* pOut);                                     // 0x00f1dc50
    bool Handle(int nIndex);                                         // 0x00f1dd90
    bool Run(int nIndex);                                            // 0x00f1de30
};

// @ 0x00f1d430
// Fires the type-4 feedback events of a scenario: every armed entry with a matching id that
// has not seen this event yet gets it added, then the event is recorded in the entry's map.
void PB::FireType4(PBPacket* pPacket)
{
    if (mState != 3)
        return;
    ++mCount;
    int id = pPacket->mnId;
    if (id == -1)
        return;
    for (PBEl* e = mpBegin; e != mpEnd; ++e) {
        if (!e->mbDisabled && e->mnId == id && e->mnType == 4) {
            if (e->mEvents.find(pPacket->mnKey).mpNode == (void*)&e->mEvents.mAnchor) {
                void* pEvent = pPacket->GetEventRef(kPacketRef, 0);
                Add(e, pEvent, 0);
                InsertTag tag;
                tag.mbAtEnd = false;
                int it[2];
                e->mEvents.insert((EvIter*)it, pPacket->mnKey, tag);
            }
        }
    }
}

// @ 0x00f1d500
// Same as the type-4 pass, for type-5 entries; it does not bump the scenario's counter.
void PB::FireType5(PBPacket* pPacket)
{
    if (mState != 3)
        return;
    int id = pPacket->mnId;
    if (id == -1)
        return;
    for (PBEl* e = mpBegin; e != mpEnd; ++e) {
        if (!e->mbDisabled && e->mnId == id && e->mnType == 5) {
            if (e->mEvents.find(pPacket->mnKey).mpNode == (void*)&e->mEvents.mAnchor) {
                void* pEvent = pPacket->GetEventRef(kPacketRef, 0);
                Add(e, pEvent, 0);
                InsertTag tag;
                tag.mbAtEnd = false;
                EvIter it;
                e->mEvents.insert(&it, pPacket->mnKey, tag);
            }
        }
    }
}

// @ 0x00f1dc50
// Formats the scenario's running time as "mm:ss" into a fresh string.
void PB::FormatTime(WStr* pOut)
{
    CString text;
    InitTimeString(&text);
    int nMs = mTime / 1000;
    int nMin = nMs / 60;
    int nSec = nMs % 60;
    WStr_Format(pOut, L"%02d%s%02d", nMin, text.GetText(), nSec);
    text.Release();
}

// @ 0x00f1dd90
// Handles the type-3 event of the entry at the given index; returns true when the entry
// produced something, in which case the produced object is added to the scenario.
bool PB::Handle(int nIndex)
{
    bool bHandled = false;
    if (mState == 3) {
        if (nIndex < mpEnd - mpBegin) {
            PBEl* e = &mpBegin[nIndex];
            if (!e->mbDisabled) {
                bool bAdd = false;
                void* pA = 0;
                void* pB = 0;
                if (FireType3(e, &bAdd, &pA, &pB)) {
                    bHandled = true;
                    if (bAdd)
                        Add(e, pA, pB);
                }
            }
        }
    }
    return bHandled;
}

// @ 0x00f1de30
// Runs the scenario entry at the given index until it is armed or nothing is left to do.
bool PB::Run(int nIndex)
{
    bool bDisabled = false;
    if (mState == 3) {
        if (nIndex < mpEnd - mpBegin) {
            PBEl* e = &mpBegin[nIndex];
            if (!e->mbDisabled) {
                while (Handle(nIndex) && !e->mbDisabled)
                    ;
            }
            bDisabled = e->mbDisabled != 0;
            if (!mf_ec)
                FUN_00f0e6c0(g_16c7aa4->mpf_6c);
        }
    }
    return bDisabled;
}

// @ 0x00f1dec0
// Tears an entry down: destroys its worlds, releases the world list and nukes its event map.
void PBEl::Destroy()
{
    World* pEnd = mpWorldEnd;
    for (World* p = mpWorldBegin; p < pEnd; ++p)
        p->mPart.Free();
    if (mpWorldBegin != 0 && ((uint*)mpWorldBegin)[-1] != 0)
        EASTL_allocator_deallocate(mpWorldBegin);
    EventMap* pEvents = &mEvents;
    EvNode* pRoot = pEvents->mpRoot;
    pEvents->DoNukeSubtree(pRoot);
}

// @ 0x00f1df10
// Same teardown for a whole range of entries; returns the advanced end pointer.
PBEl* FreeEntries(PBEl* pFirst, PBEl* pLast, PBEl* pOut)
{
    for (; pFirst != pLast; ++pFirst, ++pOut) {
        World* pEnd = pFirst->mpWorldEnd;
        for (World* p = pFirst->mpWorldBegin; p < pEnd; ++p)
            p->mPart.Free();
        if (pFirst->mpWorldBegin != 0 && ((uint*)pFirst->mpWorldBegin)[-1] != 0)
            EASTL_allocator_deallocate(pFirst->mpWorldBegin);
        EventMap& events = pFirst->mEvents;
        EvNode* pNode = events.mpRoot;
        while (pNode != 0) {
            events.DoNukeSubtree(pNode->mpLeft);
            EvNode* pNext = pNode->mpNext;
            EASTL_allocator_deallocate(pNode);
            pNode = pNext;
        }
    }
    return pOut;
}

// @ 0x00f1dcc0
// Replaces the vector's contents with [pFirst, pLast): reuses the buffer when it is large
// enough, otherwise grows it and releases the old storage.  The third argument is part of
// the caller's signature but is not used by the body.
void ElemVector::Assign(Elem16* pFirst, Elem16* pLast, int nUnused)
{
    (void)nUnused;
    uint nCapacity = (uint)(mpCapacity - mpBegin);
    uint nCount = (uint)(pLast - pFirst);
    if (nCount > nCapacity) {
        Elem16* pNew = Grow(nCount, pFirst, pLast);
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin != 0 && ((uint*)mpBegin)[-1] != 0)
            EASTL_allocator_deallocate(mpBegin);
        mpBegin = pNew;
        mpCapacity = pNew + nCount;
        mpEnd = mpCapacity;
        return;
    }
    uint nCur = (uint)(mpEnd - mpBegin);
    if (nCount <= nCur) {
        Elem16* pNewEnd = (Elem16*)CopyStrings(pFirst, pLast, mpBegin);
        DestroyRange(pNewEnd, mpEnd);
        mpEnd = pNewEnd;
        return;
    }
    Elem16* pMid = mpBegin + nCur;
    CopyStrings(pFirst, pMid, mpBegin);
    void* pNewEnd;
    UninitializedCopy(&pNewEnd, pMid, pLast, mpEnd, pLast);
    mpEnd = (Elem16*)pNewEnd;
}
