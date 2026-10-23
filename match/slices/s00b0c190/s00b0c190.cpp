// Slice s00b0c190 -- the planet-object record table (insert / find-or-create / save / load of the
// 0x19a8-byte planet object records), the sparse key-slot helpers used to stream object
// references, the unload / selection-key paths of the planet manager and the message handler that
// turns "planet object" messages into records.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
//
// Layout notes (offsets recovered from the disassembly; these classes are unnamed in the PDB):
//  * a planet record is 0x19a8 bytes: {uint mKey; uint mPad; cPlanetObjectData mData;} with the
//    payload at +0x08; the payload's three 0x58-byte sub-objects sit at +0x44/+0x9c/+0xf4.
//  * a record table keeps begin/end at +0x00/+0x04 and its "sorted" flag at +0x19a818 -- the
//    planet data block is one very large object of which the table is the part at +0x1e5f0.
//  * the manager's message listener is a sub-object four bytes into the manager (handler id at
//    listener+0x1c = manager+0x20); retail walks back four bytes (`lea esi,[ecx-4]`) to reach the
//    manager, hence Owner() below.

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// out-of-slice helpers (declared only)
// ---------------------------------------------------------------------------

namespace EA
{
namespace IO
{
class IStream;
bool WriteUint32(IStream* pStream, const uint* pValue, uint nCount, int nFlags);
bool ReadInt32(IStream* pStream, int* pValue, uint nCount, int nFlags);
}
}

class cPlanetRecord;
class cPlanetRecordTable;
class cPlanetObjectData;
class cSlotObject;
class cObjectKey;
class cPlanetManager;
class cNoun;
class cNounManager;
class cHierGrid;
class cWorld;
class cPlanetModel;

// binary search over the record array (0x00b02750): lower_bound by record key.
extern cPlanetRecord* LowerBoundRecords(cPlanetRecord* pBegin, cPlanetRecord* pEnd,
                                        const uint* pKey, bool bSorted);
// tear the payloads of a record range down (0x00b057b0 per sub-object, 0x00b051f0 the buffer).
extern void DestroyRecordRange(cPlanetRecord* pBegin, cPlanetRecord* pEnd);
extern void CollapseRecordRange(cPlanetRecord* pBegin, cPlanetRecord* pEnd);

// slot helpers
extern void __stdcall SetSelectedKey(const cObjectKey* pKey);                   // 0x00b01db0
extern void ShutdownSelection(cPlanetManager* pOwner);                         // 0x00b09b00
extern void RemoveHandler(int nHandler, uint nKey0, uint nKey1, uint nKey2, uint nKey3);

// planet model / singleton access
extern void* GetActivePlanet();                                                // 0x01021260
extern cPlanetModel* PlanetModel();                                            // 0x00b3d350
extern cNounManager* GetNounManager();                                         // 0x00b3d300
extern cPlanetManager* PlanetManager();                                        // 0x00b3d440

struct cPlanetKey
{
    const void* mBegin;    // +0x00
    char mPad[4];          // +0x04
    const void* mEnd;      // +0x08
};

class cPropertyRef
{
 public:
    ~cPropertyRef();
    virtual void v00();
};

class cPropertyManager
{
 public:
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
    virtual void FindProperty(const void* pBegin, const void* pEnd, cPropertyRef* pProperty);
};

extern cPlanetKey GetPlanetKey(const cPlanetModel* pPlanet);                   // 0x00b7e380
extern cPropertyManager* PropertyManager();                                    // 0x0067de30
extern bool GetPropertyAsUInt(const cPropertyRef& property, uint nPropertyId, uint* pValue);
extern float GetPlanetObjectValue();                                           // 0x00b00000
extern const float kPlanetObjectScale;                                         // 0x015673a0
extern const cObjectKey sNullKey;                                              // 0x01654c08

class cPlanetModel
{
 public:
    void DirectionToSurfacePosition(float* pPosition, const float* pDirection); // 0x00b815a0
    void PlaceObject(const float* pPosition, float nHeight, uint nFlags, int nArg);// 0x00b83c40
};

// ---------------------------------------------------------------------------
// streaming interfaces (only the slots touched by this slice are named)
// ---------------------------------------------------------------------------

class IStreamAccess
{
 public:
    virtual void v00();                        // +0x00
    virtual void v04();                        // +0x04
    virtual void v08();                        // +0x08
    virtual void v0c();                        // +0x0c
    virtual void v10();                        // +0x10
    virtual void v14();                        // +0x14
    virtual EA::IO::IStream* GetBytes();       // +0x18
};

class IObjectPipe
{
 public:
    virtual void v00();                        // +0x00
    virtual void v04();                        // +0x04
    virtual void v08();                        // +0x08
    virtual void v0c();                        // +0x0c
    virtual void v10();                        // +0x10
    virtual void v14();                        // +0x14
    virtual void v18();                        // +0x18
    virtual void BeginRecord();                // +0x1c
    virtual IStreamAccess* Stream();           // +0x20
    virtual void v24();                        // +0x24
    virtual void v28();                        // +0x28
    virtual void WriteObject(uint nValue);     // +0x2c
};

// ---------------------------------------------------------------------------
// referenced objects and key slots
// ---------------------------------------------------------------------------

class cSlotObject
{
 public:
    virtual int AddRef();                      // +0x00
    virtual int Release();                     // +0x04
    virtual uint SaveToTag(uint nTag);         // +0x08
    virtual int ReleaseRef(bool bForce);       // +0x0c
    virtual void v10();                        // +0x10
    virtual void v14();                        // +0x14
    virtual void v18();                        // +0x18
    virtual void v1c();                        // +0x1c
    virtual void v20();                        // +0x20
    virtual void v24();                        // +0x24
    virtual void v28();                        // +0x28
    virtual void v2c();                        // +0x2c
    virtual void v30();                        // +0x30
    virtual void v34();                        // +0x34
    virtual void v38();                        // +0x38
    virtual void v3c();                        // +0x3c
    virtual void v40();                        // +0x40
    virtual void v44();                        // +0x44
    virtual void v48();                        // +0x48
    virtual void v4c();                        // +0x4c
    virtual void v50();                        // +0x50
    virtual void v54();                        // +0x54
    virtual void v58();                        // +0x58
    virtual void v5c();                        // +0x5c
    virtual void AddRefShared();               // +0x60
};

// The payload of one slot: a reference to an object, or a plain inline value.
class cSlotValue
{
 public:
    void Assign(const cSlotValue& rhs);      // 0x00ac9480

    cSlotObject* mpObject;                   // +0x00
};

// One entry of the sparse key list. Bit 31 marks an entry that carries no object, bit 30 marks the
// last entry of a run (the sentinel is 0x3fffffff).
struct cKeySlot
{
    uint mFlags;            // +0x00
    cSlotValue mpValue;     // +0x04

    cKeySlot& operator=(const cKeySlot& rhs);
};

class cKeySlotList
{
 public:
    int NextRun(uint i) const;

    cKeySlot* mSlots;       // +0x00
    cKeySlot* mSlotsEnd;    // +0x04
};

class cSlotObjectList
{
 public:
    cSlotObject** mBegin;   // +0x00
    cSlotObject** mEnd;     // +0x04
};

// A plain set of object ids.
class cObjectIdSet
{
 public:
    bool ContainsId(uint id) const;

    char mPad00[0x24];      // +0x00
    const uint* mBegin;     // +0x24
    const uint* mEnd;       // +0x28
};

// ---------------------------------------------------------------------------
// planet object records
// ---------------------------------------------------------------------------

struct cRecordSubObject
{
    char mBody[0x58];
};

class cPlanetObjectData
{
 public:
    float mPosition[3];              // +0x00
    float mHeight;                   // +0x0c
    uint mObjectKey;                 // +0x10
    uint mValue14;                   // +0x14
    uint mValue18;                   // +0x18
    uint mValue1c;                   // +0x1c
    char mPad20[0x24];               // +0x20
    cRecordSubObject mSubA;          // +0x44
    cRecordSubObject mSubB;          // +0x9c
    cRecordSubObject mSubC;          // +0xf4
    float mScaledHeight;             // +0x14c
    float mScale;                    // +0x150
    char mBody[0x19a0 - 0x154];      // +0x154
};

struct cPlanetRecord
{
    uint mKey;                       // +0x00
    uint mPad;                       // +0x04
    cPlanetObjectData mData;         // +0x08
};

// The scratch object used while one record is streamed in: the payload, the record key and the
// reader helpers that consume the pipe.
class cPlanetObjectReader
{
 public:
    cPlanetObjectReader();
    ~cPlanetObjectReader();
    void ReadFrom(IObjectPipe& pipe);
    void Initialize();

    cPlanetObjectData mData;         // +0x0000
    uint mKey;                       // +0x19a0
    char mPadA4[4];                  // +0x19a4
    char mTail[0x3358 - 0x19a8];     // +0x19a8 (stream helpers)
};

class cPlanetRecordTable
{
 public:
    cPlanetRecord* Insert(cPlanetRecord* pPos, const uint* pKey);
    cPlanetRecord* InsertRecord(cPlanetRecord* pPos, const uint* pKey);   // 0x00b0c110
    cPlanetObjectData* FindOrCreate(const uint* pKey);
    void ReleaseAll();

    cPlanetRecord* mBegin;           // +0x0000
    cPlanetRecord* mEnd;             // +0x0004
    char mBody[0x19a810];            // +0x0008 (rest of the planet data block)
    bool mbSorted;                   // +0x19a818
};

// The object that owns the key slots and is streamed with Save().
class cPlanetDataBlockSaver
{
 public:
    bool Save(IObjectPipe* pPipe);

    char mPad00[0x20];               // +0x00
    cSlotObjectList mObjects;        // +0x20
    char mBody[0x94 - 0x28];         // +0x28
    uint mId;                        // +0x94
};

// ---------------------------------------------------------------------------
// planet manager support types
// ---------------------------------------------------------------------------

struct cTrackedTreeNode
{
    char mBody[0x28];                // +0x00
    cSlotObject* mpObject;           // +0x28
    cTrackedTreeNode* Next() const;  // 0x00921580
};

// The manager's "objects to release" tree.
class cTrackedTree
{
 public:
    cTrackedTreeNode* First() const;   // 0x00b09510
    cTrackedTreeNode* End() const { return (cTrackedTreeNode*)&mpAnchorBegin; }
    void Reset()
    {
        mpAnchorBegin = &mpAnchorBegin;
        mpAnchorEnd = &mpAnchorBegin;
        mpRoot = 0;
        mbFlag = false;
        mCount = 0;
    }

    char mPad00[4];                  // +0x00
    void* mpAnchorBegin;             // +0x04
    void* mpAnchorEnd;               // +0x08
    cTrackedTreeNode* mpRoot;        // +0x0c
    bool mbFlag;                     // +0x10
    uint mCount;                     // +0x14
};

struct cEffect
{
    char mBody[0x10];                // +0x00
    cSlotObject* mpObject;           // +0x10
    char mTail[0x0c];                // +0x14
};

class cEffectList
{
 public:
    void Clear();

    cEffect* mBegin;                 // +0x00
    cEffect* mEnd;                   // +0x04
};

class cNoun
{
 public:
    virtual void v00();              // +0x00
    virtual int Release();           // +0x04
};

class cNounList
{
 public:
    void EraseFirst()
    {
        cNoun** pp = mBegin + 1;
        for (; pp < mEnd; ++pp)
            pp[-1] = pp[0];
        --mEnd;
        cNoun* pNoun = *mEnd;
        if (pNoun != 0)
            pNoun->Release();
    }

    cNoun** mBegin;                  // +0x00
    cNoun** mEnd;                    // +0x04
};

class cNounManager
{
 public:
    void RemoveNoun(cNoun* pNoun);   // 0x00b225d0
};

class cHierGrid
{
 public:
    bool Shutdown();                 // 0x00704060
};

class cWorld
{
 public:
    void Shutdown();                 // 0x007cd990
};

class cSlotContainer
{
 public:
    void* mBegin;                    // +0x00
    void* mEnd;                      // +0x04
};

// The planet manager: selection key, grid, tracked objects, noun lists and the record array.
class cPlanetManager
{
 public:
    void Unload(bool bUnloadRecords);
    void SetCurrentKey(const cObjectKey* pKey);
    void ClearContainer(cSlotContainer* pContainer, void* pArg2, void* pArg3); // 0x00b068c0
    cSlotObject** UnloadTrackedObject(cSlotObject** ppObject);                // 0x00b06a40
    void RefreshFromSelection();                                              // 0x00b0b150

    char mPad00[0x20];               // +0x0000
    int mHandlerId;                  // +0x0020
    uint mHandlerKey[4];             // +0x0024
    cSlotContainer mContainerA;      // +0x0034
    char mGap3c[0x8080 - 0x003c];    // +0x003c
    cTrackedTree mTracked;           // +0x8080
    char mGap8098[0x160e8 - 0x8098]; // +0x8098
    cEffectList mEffects;            // +0x160e8
    char mGap160f0[0x16500 - 0x160f0];  // +0x160f0
    cHierGrid* mpHierGrid;           // +0x16500
    char mGap16504[0x165a0 - 0x16504];  // +0x16504
    cSlotContainer mContainerB;      // +0x165a0
    char mGap165a8[0x1e5f0 - 0x165a8];  // +0x165a8
    cPlanetRecordTable mRecords;     // +0x1e5f0
    char mGap1b8e0c[0x1b8f2c - 0x1b8e0c];   // +0x1b8e0c
    const cObjectKey* mpCurrentKey;  // +0x1b8f2c
    cWorld* mpWorld;                 // +0x1b8f30
    char mGap1b8f34[0x1b8f44 - 0x1b8f34];   // +0x1b8f34
    cNounList mNouns;                // +0x1b8f44
    char mGap1b8f4c[0x1b905c - 0x1b8f4c];   // +0x1b8f4c
    cSlotObjectList mTrackedObjects; // +0x1b905c
    char mGap1b9064[0x1b9174 - 0x1b9064];   // +0x1b9064
    cNounList mExtraNouns;           // +0x1b9174
    char mGap1b917c[0x1ba18c - 0x1b917c];   // +0x1b917c
    uint mFlags;                     // +0x1ba18c
};

// ---------------------------------------------------------------------------
// messages
// ---------------------------------------------------------------------------

struct cPlanetObjectSpawn
{
    uint mUnknown00;                 // +0x00
    float mDirection[3];             // +0x04
    float mHeight;                   // +0x10
    char mRest[0x4c - 0x14];         // +0x14
};

class cPlanetObjectMessage
{
 public:
    cPlanetObjectSpawn* mpSpawns;    // +0x00
    char mPad04[4];                  // +0x04
    uint mnSpawns;                   // +0x08
    char mPad0c[0x14];               // +0x0c
    uint mBaseIndex;                 // +0x20
};

class cMessageHandler
{
 public:
    virtual bool DoMessage(uint nMessageId, cPlanetObjectMessage* pMessage); // 0x007cf8d0
};

// The listener that reacts to planet-object messages; see the note at the top of the file.
class cKeyChangeNotifier : public cMessageHandler
{
 public:
    void Shutdown();
    bool DoMessage(uint nMessageId, cPlanetObjectMessage* pMessage);

    cPlanetManager* Owner() const
    {
        return reinterpret_cast<cPlanetManager*>(reinterpret_cast<char*>(
            const_cast<cKeyChangeNotifier*>(this)) - 4);
    }

    char mGap04[0x18];               // +0x04
    int mHandlerId;                  // +0x1c
    uint mHandlerKey[4];             // +0x20
};

// ---------------------------------------------------------------------------
// slot list helpers
// ---------------------------------------------------------------------------

// @ 0x00b0ce80
bool cObjectIdSet::ContainsId(uint id) const
{
    const uint* pEnd = mEnd;
    const uint* p = mBegin;
    while (p != pEnd && *p != id)
        ++p;
    return p != pEnd;
}

// @ 0x00b0ceb0
int cKeySlotList::NextRun(uint i) const
{
    const cKeySlot* p = &mSlots[i];
    for (;;) {
        bool bLast = ((p->mFlags >> 30) & 1) != 0;
        if (bLast)
            return 0x3fffffff;
        uint uFlags = (++p)->mFlags;
        bool bEmpty = ((uFlags >> 31) & 1) != 0;
        ++i;
        if (!bEmpty)
            return (int)i;
    }
}

// @ 0x00b0cf80
void FindSlotRun(cKeySlot** ppOut, cKeySlot* pBegin, cKeySlot* pEnd, cSlotObject* const* ppValue)
{
    while (pEnd != pBegin) {
        if (pBegin->mpValue.mpObject == *ppValue)
            break;
        bool bContinues = true;
        do {
            cKeySlot* pPrev = pBegin;
            ++pBegin;
            bool bLast = ((pPrev->mFlags >> 30) & 1) != 0;
            if (bLast)
                break;
            bContinues = ((pBegin->mFlags >> 31) & 1) != 0;
        } while (bContinues);
    }
    *ppOut = pBegin;
}

// @ 0x00b0cfd0
void __stdcall DestroySlots(cKeySlot* pBegin, cKeySlot* pEnd)
{
    for (; pBegin < pEnd; ++pBegin) {
        bool bEmpty = ((pBegin->mFlags >> 31) & 1) != 0;
        if (bEmpty)
            continue;
        cSlotObject* pObject = pBegin->mpValue.mpObject;
        if (pObject != 0)
            pObject->Release();
    }
}

// @ 0x00b0d010
int CountSlots(cKeySlot* pBegin, cKeySlot* pEnd)
{
    int nRuns = 0;
    do {
        if (pEnd == pBegin)
            return nRuns;
        for (;;) {
            cKeySlot* pPrev = pBegin;
            ++pBegin;
            bool bLast = ((pPrev->mFlags >> 30) & 1) != 0;
            if (!bLast) {
                bool bContinues = ((pBegin->mFlags >> 31) & 1) != 0;
                if (bContinues)
                    continue;
            }
            break;
        }
        ++nRuns;
    } while (pEnd != pBegin);
    return nRuns;
}

// @ 0x00b0d050
cKeySlot& cKeySlot::operator=(const cKeySlot& rhs)
{
    bool bRhsEmpty = (rhs.mFlags >> 31) & 1;
    if (bRhsEmpty) {
        bool bEmpty = ((mFlags >> 31) & 1) != 0;
        if (!bEmpty && mpValue.mpObject != 0) {
            mpValue.mpObject->Release();
            mFlags = rhs.mFlags;
            return *this;
        }
    } else if (!bRhsEmpty && ((mFlags >> 31) & 1) != 0) {
        if (&mpValue != 0) {
            mpValue.mpObject = rhs.mpValue.mpObject;
            if (mpValue.mpObject != 0) {
                mpValue.mpObject->AddRef();
                mFlags = rhs.mFlags;
                return *this;
            }
        }
    } else {
        mpValue.Assign(rhs.mpValue);
    }
    mFlags = rhs.mFlags;
    return *this;
}

// @ 0x00b0ce40
void CopySlotObjects(cSlotObject** ppDst, uint nCount, cSlotObject* const* ppSrc)
{
    while (nCount-- != 0) {
        if (ppDst != 0) {
            *ppDst = *ppSrc;
            if (*ppDst != 0)
                (*ppDst)->AddRefShared();
        }
        ++ppDst;
    }
}

// @ 0x00b0cef0
void WriteObjectList(IObjectPipe* pPipe, const cSlotObjectList& objects)
{
    int nCount = (int)(objects.mEnd - objects.mBegin);
    IStreamAccess* pAccess = pPipe->Stream();
    EA::IO::WriteUint32(pAccess->GetBytes(), (const uint*)&nCount, 1, 0);
    for (uint i = 0; i < (uint)(objects.mEnd - objects.mBegin); ++i) {
        cSlotObject* pObject = objects.mBegin[i];
        pPipe->WriteObject(pObject != 0 ? pObject->SaveToTag(0x179c807) : 0);
    }
}

// @ 0x00b0d250
bool cPlanetDataBlockSaver::Save(IObjectPipe* pPipe)
{
    IStreamAccess* pAccess = pPipe->Stream();
    uint nId = mId;
    EA::IO::IStream* pStream = pAccess->GetBytes();
    EA::IO::WriteUint32(pStream, &nId, 1, 0);
    WriteObjectList(pPipe, mObjects);
    return true;
}

// ---------------------------------------------------------------------------
// record table
// ---------------------------------------------------------------------------

// @ 0x00b0c570
cPlanetRecord* cPlanetRecordTable::Insert(cPlanetRecord* pPos, const uint* pKey)
{
    cPlanetRecord* pEnd = mEnd;
    cPlanetRecord* pFound;
    if (pPos == pEnd || *pKey >= pPos->mKey)
        pFound = LowerBoundRecords(pPos, pEnd, pKey, mbSorted);
    else
        pFound = LowerBoundRecords(mBegin, pPos, pKey, mbSorted);
    if (pFound == pEnd || *pKey < pFound->mKey)
        pFound = InsertRecord(pFound, pKey);
    return pFound;
}

// @ 0x00b0c610
cPlanetObjectData* cPlanetRecordTable::FindOrCreate(const uint* pKey)
{
    cPlanetRecord* pEnd = mEnd;
    cPlanetRecord* pFound = LowerBoundRecords(mBegin, pEnd, pKey, mbSorted);
    if (pFound != pEnd && *pKey <= pFound->mKey)
        return &pFound->mData;
    cPlanetObjectReader reader;
    reader.mKey = *pKey;
    reader.Initialize();
    cPlanetRecord* pRecord = Insert(pFound, &reader.mKey);
    return &pRecord->mData;
}

// @ 0x00b0c730
void LoadPlanetRecords(IObjectPipe* pPipe, cPlanetRecordTable* pTable)
{
    pTable->ReleaseAll();
    int nCount = 0;
    EA::IO::ReadInt32(pPipe->Stream()->GetBytes(), &nCount, 1, 0);
    for (int i = 0; i < nCount; ++i) {
        cPlanetObjectReader reader;
        int nKey = 0;
        EA::IO::ReadInt32(pPipe->Stream()->GetBytes(), &nKey, 1, 0);
        pPipe->BeginRecord();
        reader.ReadFrom(*pPipe);
        pPipe->BeginRecord();
        reader.mKey = (uint)nKey;
        reader.Initialize();
        cPlanetRecord* pEnd = pTable->mEnd;
        cPlanetRecord* pFound =
            LowerBoundRecords(pTable->mBegin, pEnd, &reader.mKey, pTable->mbSorted);
        bool bInserted;
        cPlanetRecord* pRecord;
        if (pFound == pEnd || reader.mKey < pFound->mKey) {
            pRecord = pTable->InsertRecord(pFound, &reader.mKey);
            bInserted = true;
        } else {
            pRecord = pFound;
            bInserted = false;
        }
        if (!bInserted)
            pRecord->mData = reader.mData;
    }
    pPipe->BeginRecord();
}

// ---------------------------------------------------------------------------
// planet manager
// ---------------------------------------------------------------------------

// @ 0x00b0c520
void cPlanetManager::SetCurrentKey(const cObjectKey* pKey)
{
    if (mpCurrentKey != pKey) {
        if (pKey != &sNullKey) {
            SetSelectedKey(pKey);
            if (mFlags & 1) {
                RefreshFromSelection();
                mpCurrentKey = pKey;
                return;
            }
            Unload(false);
        }
        mpCurrentKey = pKey;
    }
}

// @ 0x00b0c190
void cPlanetManager::Unload(bool bUnloadRecords)
{
    mpCurrentKey = (const cObjectKey*)-1;
    if ((mFlags >> 1) & 1) {
        mpHierGrid->Shutdown();
        ClearContainer(&mContainerA, 0, 0);
        ClearContainer(&mContainerB, 0, 0);
        if (mTracked.mCount != 0) {
            cTrackedTreeNode* pEnd = mTracked.End();
            for (cTrackedTreeNode* pNode = mTracked.First(); pNode != pEnd;
                 pNode = pNode->Next()) {
                if (pNode->mpObject != 0)
                    pNode->mpObject->ReleaseRef(true);
            }
            mTracked.Reset();
        }
        if (mEffects.mBegin != mEffects.mEnd)
            mEffects.Clear();
        for (cSlotObject** pp = mTrackedObjects.mBegin; pp != mTrackedObjects.mEnd;
             pp = UnloadTrackedObject(pp)) {
        }
        for (; mNouns.mBegin != mNouns.mEnd; mNouns.EraseFirst())
            GetNounManager()->RemoveNoun(*mNouns.mBegin);
        for (; mExtraNouns.mBegin != mExtraNouns.mEnd; mExtraNouns.EraseFirst())
            GetNounManager()->RemoveNoun(*mExtraNouns.mBegin);
        ShutdownSelection(this);
        mFlags &= ~2u;
    }
    if (bUnloadRecords) {
        DestroyRecordRange(mRecords.mBegin, mRecords.mEnd);
        CollapseRecordRange(mRecords.mBegin, mRecords.mEnd);
    }
}

// @ 0x00b0c5d0
void cKeyChangeNotifier::Shutdown()
{
    cPlanetManager* pOwner = Owner();
    pOwner->Unload(true);
    if (pOwner->mHandlerId != 0) {
        int nHandler = pOwner->mHandlerId;
        pOwner->mHandlerId = 0;
        RemoveHandler(nHandler, pOwner->mHandlerKey[0], pOwner->mHandlerKey[1],
                      pOwner->mHandlerKey[2], pOwner->mHandlerKey[3]);
    }
    pOwner->mpWorld->Shutdown();
}

// @ 0x00b0cbb0
bool cKeyChangeNotifier::DoMessage(uint nMessageId, cPlanetObjectMessage* pMessage)
{
    bool bHandled = cMessageHandler::DoMessage(nMessageId, pMessage);
    if (nMessageId == (uint)mHandlerId && pMessage->mpSpawns != 0 && pMessage->mnSpawns != 0) {
        void* pActivePlanet = GetActivePlanet();
        cPlanetModel* pPlanet = PlanetModel();
        if (pActivePlanet != 0 && pPlanet != 0) {
            cPlanetRecordTable* pTable = &PlanetManager()->mRecords;
            uint nKey = pMessage->mBaseIndex * 3;
            cPlanetObjectSpawn* pSpawn = pMessage->mpSpawns;
            for (uint i = pMessage->mnSpawns; i > 0; --i, ++nKey) {
                cPlanetRecord* pEnd = pTable->mEnd;
                cPlanetRecord* pFound =
                    LowerBoundRecords(pTable->mBegin, pEnd, &nKey, pTable->mbSorted);
                if (pFound != pEnd && nKey >= pFound->mKey)
                    continue;
                cPlanetKey planetKey = GetPlanetKey(pPlanet);
                cPropertyManager* pProperties = PropertyManager();
                cPropertyRef property;
                pProperties->FindProperty(planetKey.mBegin, planetKey.mEnd, &property);
                float position[3];
                pPlanet->DirectionToSurfacePosition(position, pSpawn->mDirection);
                cPlanetObjectData* pData = pTable->FindOrCreate(&nKey);
                pData->mPosition[0] = position[0];
                pData->mPosition[1] = position[1];
                pData->mPosition[2] = position[2];
                pData->mHeight = pSpawn->mHeight;
                pData->mObjectKey = nKey;
                pData->mValue14 = 0;
                GetPropertyAsUInt(property, 0x35494e9, &pData->mValue14);
                pData->mValue18 = 0;
                GetPropertyAsUInt(property, 0x35494e6, &pData->mValue18);
                pData->mValue1c = 0;
                GetPropertyAsUInt(property, 0x35494e3, &pData->mValue1c);
                pData->mSubA.~cRecordSubObject();
                pData->mSubB.~cRecordSubObject();
                pData->mSubC.~cRecordSubObject();
                pData->mScaledHeight = GetPlanetObjectValue();
                pData->mScale = kPlanetObjectScale;
                pPlanet->PlaceObject(position, pSpawn->mHeight, 0x4000000, 0);
                pSpawn = (cPlanetObjectSpawn*)((char*)pSpawn + 0x4c);
            }
        }
    }
    return bHandled;
}
