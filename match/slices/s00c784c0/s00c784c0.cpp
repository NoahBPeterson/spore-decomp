// s00c784c0 -- SP::cPlayer war-victory test, the eastl fixed-hash container
// constructors that live next to it and the templated serializer writers that
// write one named container each.
//
//   0x00c784c0 SP::cPlayer::TestPlayerWarVictory
//   0x00c785e0 eastl::fixed_hash_set<EA::ResourceMan::Key,64,65,1,...> ctor
//   0x00c786b0 eastl::hashtable<EA::ResourceMan::Key,...> ctor
//   0x00c78790 eastl::fixed_hash_map<unsigned int,unsigned int,128,129,...> ctor
//   0x00c788d0 WriteValue<eastl::fixed_hash_set<int32_t,...> >  (name "set")
//   0x00c78ea0 WriteValue<vector of 0xb0-byte pairs>            (name "map")
//   0x00c78ff0 WriteValue<vector of 8-byte pairs>               (name "map")
//   0x00c79140 WriteValue<vector<int32_t> >                     (name "list")
//   0x00c79290 WriteValue<vector of 0x10-byte bool pairs>       (name "map")
//
// Layout note: the field offsets are taken from the disassembly of this build.
// The one-time-event set sits at cPlayer+0x11f8 and its end() sentinel is the
// address of the set's second iterator word (cPlayer+0x11fc).
#include "types.h"

#define nullptr 0

void __cdecl operator_delete_array(void* pBlock);           // 0x00f47380

// ---------------------------------------------------------------------------
// engine types
// ---------------------------------------------------------------------------
struct StarVector {
    int32_t* mpBegin;           // +0x00
    int32_t* mpEnd;             // +0x04
    int32_t* mpCapacity;        // +0x08
};

class cEmpire {
public:
    StarVector* GetStars();                         // 0x00c308d0
};

class cStarManager {
public:
    cEmpire* GetEmpireByID(int32_t nEmpireId);      // 0x00ba9370
    void*    FUN_00baf700(cEmpire* pEmpire);        // 0x00baf700
};

cStarManager* __cdecl StarManager();                // 0x00b3d2a0

class cSPSpaceCombatTuning {
public:
    float GetWarSurrenderThreshold();               // 0x01029c30
};

cSPSpaceCombatTuning* __cdecl GetSpaceCombatTuning();   // 0x01029940

class cRandom {
public:
    double RandomDoubleUniform();                   // 0x009360d0
};

extern cRandom gRandom;                             // 0x01601760

template <typename T>
void __cdecl GetPropertyT(void* pObject, uint32_t nPropertyId, T* pValue);   // 0x0040cf10

// ---------------------------------------------------------------------------
// one-time-event record and its set
// ---------------------------------------------------------------------------
struct WarEventRecord {
    uint8_t mPad00[0x4c];       // +0x000
    int32_t mnLimit;            // +0x04c  clamped denominator of the war score
    int32_t mnProgress;         // +0x050
    int32_t mnBaseline;         // +0x054
};

class cWarEventSet {
public:
    uint32_t mPad00;            // +0x00
    WarEventRecord* mpEnd;      // +0x04  address of this word is the end() sentinel
    void Find(WarEventRecord** ppResult, const int32_t* pnKey);     // 0x00e5c780
    WarEventRecord* End() const { return (WarEventRecord*)&mpEnd; }
};

namespace SP {

class cPlayer {
public:
    bool TestPlayerWarVictory(int32_t nEmpireId);       // 0x00c784c0
    void NoteWarEndedWithPlayer(cEmpire* pEmpire);      // 0x00c78450

private:
    uint8_t mPad00[0x11f8];         // +0x0000
    cWarEventSet mWarEvents;        // +0x11f8
};

} // namespace SP

// @ 0x00c784c0
bool SP::cPlayer::TestPlayerWarVictory(int32_t nEmpireId)
{
    WarEventRecord* pRecord;
    mWarEvents.Find(&pRecord, &nEmpireId);
    if (pRecord == mWarEvents.End())
        return false;

    cEmpire* pEmpire = StarManager()->GetEmpireByID(nEmpireId);
    StarVector* pStars = pEmpire->GetStars();
    int32_t nStarCount = (int32_t)(pStars->mpEnd - pStars->mpBegin);
    if (nStarCount == 0) {
        NoteWarEndedWithPlayer(pEmpire);
        return false;
    }

    int32_t nProgress = pRecord->mnProgress - pRecord->mnBaseline;
    if (nProgress <= 0)
        return false;

    int32_t nCombined = nProgress + nStarCount;
    if (pRecord->mnLimit > nCombined)
        pRecord->mnLimit = nCombined;

    int32_t nLimit = pRecord->mnLimit;
    float fFraction = 1.0f - (float)nProgress / (float)nLimit;

    float fChance = 1.0f;
    if (nLimit == 1 || nStarCount != 1) {
        if (!(fFraction < GetSpaceCombatTuning()->GetWarSurrenderThreshold()))
            return false;
        GetPropertyT<float>(StarManager()->FUN_00baf700(pEmpire), 0x682ede3, &fChance);
    } else {
        GetPropertyT<float>(StarManager()->FUN_00baf700(pEmpire), 0x682f155, &fChance);
    }

    double fRoll = gRandom.RandomDoubleUniform();
    return fChance > fRoll;
}

// ---------------------------------------------------------------------------
// eastl::fixed_pool_base and the fixed-hashtable allocator block
// ---------------------------------------------------------------------------
class FixedPoolBase {
public:
    void* mpHead;               // +0x00
    void* mpTail;               // +0x04
    void* mpEnd;                // +0x08
    int32_t mnSize;             // +0x0c
    void Init(void* pPoolBegin, int32_t nPoolSize, int32_t nNodeSize,
              int32_t nNodeAlignment, int32_t nAlignmentOffset);     // 0x00921260
};

struct FixedHashtableAlloc {
    void* mpPoolHead;           // +0x00
    float mfLoadFactor;         // +0x04
    void* mpPoolBegin;          // +0x08
    void* mpPoolEnd;            // +0x0c
    int32_t mnNodeSize;         // +0x10
    void* mpBuckets;            // +0x14
};

uint32_t __cdecl GetBucketCountFor(uint32_t nRequested);        // 0x00921340
uint32_t __cdecl GetRehashBucketCount(uint32_t nElementCount);  // 0x009213c0

// The three containers below are the fixed-hash members of the same object; the
// constructors chain the pool, the bucket array and the hashtable base and then
// clamp the load factor.
class cFixedHashtableBase {
public:
    void Construct(uint32_t nBucketCount, uint32_t nArg1, const FixedHashtableAlloc& rAlloc);   // 0x00c76a80
    void ConstructKeyed(uint32_t nBucketCount, uint32_t nArg1, const FixedHashtableAlloc& rAlloc);  // 0x00c76b30
    void ConstructMap(uint32_t nBucketCount, uint32_t nArg1, const FixedHashtableAlloc& rAlloc);    // 0x00c76e60

    void DoFreeNodes(uint32_t nBucketCount);        // 0x00c76440
    void DoFreeNodesKeyed(uint32_t nBucketCount);   // 0x00b5d220
    void DoFreeNodesMap(uint32_t nBucketCount);     // 0x00c76610

    uint8_t mPad00[0x08];       // +0x00
    uint32_t mnBucketCapacity;  // +0x08
    uint32_t mnBucketCount;     // +0x0c
    float mfLoadFactor;         // +0x10
    float mfGrowthFactor;       // +0x14
    uint32_t mnElementCount;    // +0x18
    uint8_t mPad1c[0x34 - 0x1c];        // +0x1c
    void* mpBuckets;            // +0x34
};

class cResourceKeySet {
public:
    cResourceKeySet* Construct(uint32_t nArg1, uint32_t nArg2);     // 0x00c785e0
private:
    cFixedHashtableBase mHashtable;     // +0x00
    uint8_t mPad38[0x13c - 0x38];       // +0x38
    uint8_t mPool[0x400];               // +0x13c
};

class cResourceKeyTable {
public:
    cResourceKeyTable* Construct(uint32_t nArg1, uint32_t nArg2);   // 0x00c786b0
private:
    cFixedHashtableBase mHashtable;     // +0x00
    uint8_t mPad38[0x23c - 0x38];       // +0x38
    uint8_t mPool[0x600];               // +0x23c
};

class cUInt32Map {
public:
    cUInt32Map* Construct(uint32_t nArg1, uint32_t nArg2);          // 0x00c78790
private:
    cFixedHashtableBase mHashtable;     // +0x00
    uint8_t mPad38[0xbc - 0x38];        // +0x38
    uint8_t mPool[0x300];               // +0xbc
};

// @ 0x00c785e0
cResourceKeySet* cResourceKeySet::Construct(uint32_t nArg1, uint32_t nArg2)
{
    FixedPoolBase pool;
    pool.mpHead = nullptr;
    pool.Init(mPool, 0x400, 0x10, 4, 0);

    FixedHashtableAlloc alloc;
    alloc.mpPoolHead = mPool;
    alloc.mpPoolBegin = mPool;
    alloc.mpPoolEnd = mPool + 0x400;
    alloc.mnNodeSize = 0x10;
    alloc.mpBuckets = &mHashtable.mpBuckets;

    uint32_t nBucketCount = GetBucketCountFor(0x41);
    mHashtable.Construct(nBucketCount, nArg1, alloc);

    mHashtable.mfLoadFactor = 12390.0f;
    mHashtable.mfGrowthFactor = 2.0f;
    mHashtable.mnElementCount = 0;

    uint32_t nWanted = GetRehashBucketCount(mHashtable.mnBucketCount);
    if (mHashtable.mnBucketCapacity < nWanted)
        mHashtable.DoFreeNodes(nWanted);
    (void)nArg2;
    return this;
}

// @ 0x00c786b0
cResourceKeyTable* cResourceKeyTable::Construct(uint32_t nArg1, uint32_t nArg2)
{
    FixedPoolBase pool;
    pool.mpHead = nullptr;
    pool.Init(mPool, 0x600, 0xc, 4, 0);

    FixedHashtableAlloc alloc;
    alloc.mpPoolHead = mPool;
    alloc.mpPoolBegin = mPool;
    alloc.mpPoolEnd = mPool + 0x600;
    alloc.mnNodeSize = 0xc;
    alloc.mpBuckets = &mHashtable.mpBuckets;

    uint32_t nBucketCount = GetBucketCountFor(0x81);
    mHashtable.ConstructKeyed(nBucketCount, nArg1, alloc);

    mHashtable.mfLoadFactor = 12390.0f;
    mHashtable.mfGrowthFactor = 2.0f;
    mHashtable.mnElementCount = 0;

    uint32_t nWanted = GetRehashBucketCount(mHashtable.mnBucketCount);
    if (mHashtable.mnBucketCapacity < nWanted)
        mHashtable.DoFreeNodesKeyed(nWanted);
    (void)nArg2;
    return this;
}

// @ 0x00c78790
cUInt32Map* cUInt32Map::Construct(uint32_t nArg1, uint32_t nArg2)
{
    FixedPoolBase pool;
    pool.mpHead = nullptr;
    pool.Init(mPool, 0x300, 0x18, 8, 0);

    FixedHashtableAlloc alloc;
    alloc.mpPoolHead = mPool;
    alloc.mpPoolBegin = mPool;
    alloc.mpPoolEnd = mPool + 0x300;
    alloc.mnNodeSize = 0x18;
    alloc.mpBuckets = &mHashtable.mpBuckets;

    uint32_t nBucketCount = GetBucketCountFor(0x21);
    mHashtable.ConstructMap(nBucketCount, nArg1, alloc);

    mHashtable.mfLoadFactor = 12390.0f;
    mHashtable.mfGrowthFactor = 2.0f;
    mHashtable.mnElementCount = 0;

    uint32_t nWanted = GetRehashBucketCount(mHashtable.mnBucketCount);
    if (mHashtable.mnBucketCapacity < nWanted)
        mHashtable.DoFreeNodesMap(nWanted);
    (void)nArg2;
    return this;
}

// ---------------------------------------------------------------------------
// serializer side: eastl::wstring, the writer virtuals and the value writers
// ---------------------------------------------------------------------------
class WString {
public:
    wchar_t* mpBegin;           // +0x00
    wchar_t* mpEnd;             // +0x04
    wchar_t* mpCapacity;        // +0x08

    WString();                                  // 0x00579a90  (RangeInitialize(0))
    WString(const WString& rOther);             // 0x0056e2d0
    ~WString()
    {
        if (mpEnd - mpBegin > 1 && mpBegin != nullptr)
            operator_delete_array(mpBegin);
    }

    bool empty() const { return mpBegin == mpEnd; }
    const wchar_t* c_str() const { return mpBegin; }
};

WString __cdecl EAConvertToString16(const char* pText, int32_t nLength);    // 0x0093c5a0

class cSerializer {
public:
    virtual void BeginContainer(const wchar_t* pszName);    // +0x00
    virtual void EndContainer(const wchar_t* pszName);      // +0x04
};

bool __cdecl WriteTypedValue32(cSerializer* pSerializer, int32_t nFlags,
                               const void* pValue, const wchar_t* pszType);     // 0x0057c770
bool __cdecl WriteTypedValueBool(cSerializer* pSerializer, int32_t nFlags,
                                 const void* pValue, const wchar_t* pszType);   // 0x0057c940
bool __cdecl WriteTypedValuePair(cSerializer* pSerializer, int32_t nFlags,
                                 const void* pValue);                           // 0x00ac8050

struct Int32List {
    int32_t* mpBegin;           // +0x00
    int32_t* mpEnd;             // +0x04
    int32_t* mpCapacity;        // +0x08
};

struct KeyPair8 {
    int32_t mnKey;              // +0x00
    int32_t mnValue;            // +0x04
};

struct KeyPair16 {
    uint8_t mPad00[0x0c];       // +0x00
    int32_t mnValue;            // +0x0c
};

struct PairList8 {
    KeyPair8* mpBegin;          // +0x00
    KeyPair8* mpEnd;            // +0x04
    KeyPair8* mpCapacity;       // +0x08
};

struct PairList16 {
    KeyPair16* mpBegin;         // +0x00
    KeyPair16* mpEnd;           // +0x04
    KeyPair16* mpCapacity;      // +0x08
};

struct WidePair {
    uint8_t mPad00[0x08];       // +0x00
    uint8_t mValue[0xb0 - 0x08];    // +0x08
};

struct WidePairList {
    WidePair* mpBegin;          // +0x00
    WidePair* mpEnd;            // +0x04
    WidePair* mpCapacity;       // +0x08
};

// eastl fixed-hash node of the int32 set written at 0x00c788d0
class cInt32SetNode {
public:
    int32_t mnValue;            // +0x00
    cInt32SetNode* mpNext;      // +0x04
};

class cInt32Set {
public:
    uint8_t mPad00[0x04];       // +0x00
    cInt32SetNode** mpBuckets;  // +0x04  bucket[nBucketCount] holds the end node
    int32_t mnBucketCount;      // +0x08
    int32_t mnElementCount;     // +0x0c
};

// @ 0x00c788d0
bool __cdecl FUN_00c788d0(cSerializer* pSerializer, const char* pName, const cInt32Set* pSet)
{
    bool bOk = true;
    if (pSet->mnElementCount == 0)
        return bOk;

    WString sName(pName != nullptr ? EAConvertToString16(pName, -1) : WString());
    const wchar_t* pszName = sName.empty() ? L"set" : sName.c_str();
    pSerializer->BeginContainer(pszName);

    cInt32SetNode** pBucket = pSet->mpBuckets;
    cInt32SetNode* pNode = *pBucket;
    if (pNode == nullptr) {
        do {
            ++pBucket;
        } while (*pBucket == nullptr);
        pNode = *pBucket;
    }
    cInt32SetNode* pEnd = pSet->mpBuckets[pSet->mnBucketCount];
    while (pNode != pEnd) {
        if (bOk && !WriteTypedValue32(pSerializer, 0, &pNode->mnValue, L"int32_t"))
            bOk = false;
        pNode = pNode->mpNext;
        if (pNode == nullptr) {
            do {
                ++pBucket;
            } while (*pBucket == nullptr);
            pNode = *pBucket;
        }
    }

    pSerializer->EndContainer(pszName);
    return bOk;
}

// @ 0x00c78ea0
bool __cdecl FUN_00c78ea0(cSerializer* pSerializer, const char* pName, const WidePairList* pList)
{
    bool bOk = true;
    if (pList->mpBegin == pList->mpEnd)
        return bOk;

    WString sName(pName != nullptr ? EAConvertToString16(pName, -1) : WString());
    const wchar_t* pszName = sName.empty() ? L"map" : sName.c_str();
    pSerializer->BeginContainer(pszName);
    for (const WidePair* p = pList->mpBegin; p != pList->mpEnd; ++p) {
        if (bOk && !WriteTypedValuePair(pSerializer, 0, p->mValue))
            bOk = false;
    }
    pSerializer->EndContainer(pszName);
    return bOk;
}

// @ 0x00c78ff0
bool __cdecl FUN_00c78ff0(cSerializer* pSerializer, const char* pName, const PairList8* pList)
{
    bool bOk = true;
    if (pList->mpBegin == pList->mpEnd)
        return bOk;

    WString sName(pName != nullptr ? EAConvertToString16(pName, -1) : WString());
    const wchar_t* pszName = sName.empty() ? L"map" : sName.c_str();
    pSerializer->BeginContainer(pszName);
    for (const KeyPair8* p = pList->mpBegin; p != pList->mpEnd; ++p) {
        if (bOk && !WriteTypedValuePair(pSerializer, 0, &p->mnValue))
            bOk = false;
    }
    pSerializer->EndContainer(pszName);
    return bOk;
}

// @ 0x00c79140
bool __cdecl FUN_00c79140(cSerializer* pSerializer, const char* pName, const Int32List* pList)
{
    bool bOk = true;
    if (pList->mpBegin == pList->mpEnd)
        return bOk;

    WString sName(pName != nullptr ? EAConvertToString16(pName, -1) : WString());
    const wchar_t* pszName = sName.empty() ? L"list" : sName.c_str();
    pSerializer->BeginContainer(pszName);
    for (const int32_t* p = pList->mpBegin; p != pList->mpEnd; ++p) {
        if (bOk && !WriteTypedValue32(pSerializer, 0, p, L"int32_t"))
            bOk = false;
    }
    pSerializer->EndContainer(pszName);
    return bOk;
}

// @ 0x00c79290
bool __cdecl FUN_00c79290(cSerializer* pSerializer, const char* pName, const PairList16* pList)
{
    bool bOk = true;
    if (pList->mpBegin == pList->mpEnd)
        return bOk;

    WString sName(pName != nullptr ? EAConvertToString16(pName, -1) : WString());
    const wchar_t* pszName = sName.empty() ? L"map" : sName.c_str();
    pSerializer->BeginContainer(pszName);
    for (const KeyPair16* p = pList->mpBegin; p != pList->mpEnd; ++p) {
        if (bOk && !WriteTypedValueBool(pSerializer, 0, &p->mnValue, L"bool"))
            bOk = false;
    }
    pSerializer->EndContainer(pszName);
    return bOk;
}
