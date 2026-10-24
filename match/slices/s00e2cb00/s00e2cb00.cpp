// s00e2cb00 -- the civil-relationship rollover window and the relationship-event
// ordering helpers behind it.
//
//  0x00e2cb00  eastl::map<unsigned int, SP::cString> slot lookup (GetStringSlot)
//  0x00e2cba0  cSPUIRolloverCivRelationship::Init
//  0x00e2cce0  cRelationshipValues::Read  (event id -> cached relationship value)
//  0x00e2cd70  insertion sort by |value|
//  0x00e2ce30  insertion sort by |value| (unguarded tail variant)
//  0x00e2ced0  median of three
//  0x00e2d0a0  partition around a pivot
//  0x00e2d180  heap push (sift up)
//  0x00e2d220  heap adjust (sift down)
//  0x00e2d300  make heap
//  0x00e2d360  sort heap
//  0x00e2d430  partial sort
//  0x00e2d520  introsort loop
//  0x00e2d5f0  sort
//
// The ordering helpers are the eastl template instantiations for a range of
// relationship-event ids that is ordered by the absolute cached relationship
// value; retail hands the comparator (a snapshot of the value map) to every
// helper by value, which is why each one ends with a map-destruction loop.
#include "types.h"
#include <math.h>

#define nullptr 0

// ---------------------------------------------------------------------------
// engine types
// ---------------------------------------------------------------------------

namespace SP {

// the 0x14-byte localized string
class cString {
public:
    cString();                                   // 0x006b5060
    cString(const cString& rhs);                 // 0x006b56f0
    ~cString();                                  // 0x006b5240
    bool Load(uint32_t nTableId, uint32_t nKey, int32_t nFlags);  // 0x006b54b0

    uint8_t m_pad000[0x14];
};

}

namespace EA {
namespace UTFWin {

class IWindow {
public:
    virtual void W00();  virtual void W04();  virtual void W08();  virtual void W0c();
    virtual int32_t GetParentWindow();           // +0x10

    virtual void W14();  virtual void W18();  virtual void W1c();
    virtual void W20();  virtual void W24();  virtual void W28();  virtual void W2c();
    virtual void W30();  virtual void W34();  virtual void W38();  virtual void W3c();
    virtual void W40();  virtual void W44();  virtual void W48();  virtual void W4c();
    virtual void W50();  virtual void W54();  virtual void W58();  virtual void W5c();
    virtual void W60();  virtual void W64();  virtual void W68();  virtual void W6c();
    virtual void W70();  virtual void W74();  virtual void W78();  virtual void W7c();
    virtual void W80();  virtual void W84();  virtual void W88();  virtual void W8c();
    virtual void W90();  virtual void W94();  virtual void W98();  virtual void W9c();
    virtual void Wa0();  virtual void Wa4();  virtual void Wa8();  virtual void Wac();
    virtual void Wb0();  virtual void Wb4();  virtual void Wb8();  virtual void Wbc();
    virtual void Wc0();  virtual void Wc4();  virtual void Wc8();  virtual void Wcc();
    virtual void Wd0();  virtual void Wd4();
    virtual void AddChildWindow(IWindow* pWindow);        // +0xd8
};

}
}

class cSPUILayoutManager {
public:
    EA::UTFWin::IWindow* GetWorldMainWindow(uint32_t nKey);      // 0x00810620
};

cSPUILayoutManager* __cdecl SPUIHelpers_GetLayoutManager(uint32_t nKey);  // 0x00805070

// the property layout the rollover derives from
class cSPUIPropertyLayout {
public:
    bool Init();                                              // 0x00828250
    EA::UTFWin::IWindow* GetRootWindow();                     // 0x00828100

    uint8_t m_pad000[0x78];
};

// the shared relationship-event id list
struct cEventVector {
    uint32_t* m_pBegin;                          // +0x00
    uint32_t* m_pEnd;                            // +0x04
    uint32_t* m_pCapacity;                       // +0x08
};

cEventVector* __cdecl GetRelationshipEvents();   // 0x00d026d0

// ---------------------------------------------------------------------------
// event id -> cached relationship value (eastl::map<unsigned int, float>)
// ---------------------------------------------------------------------------

class cRelationshipValues {
public:
    // the value slot for an event, inserted as 0.0f when it is new
    float* GetValue(uint32_t nEvent);            // 0x00be0790

    // rebuild the whole map from the relationship events
    cRelationshipValues& Read(uint32_t nFrom, uint32_t nTo);   // 0x00e2cce0

    void Reset()
    {
        m_pRoot = nullptr;
        m_nSize = 0;
        m_bMulti = 0;
        m_pAllocator = nullptr;
    }

    void* m_pRoot;                               // +0x00
    uint8_t m_pad004[0x0c];                      // +0x04
    uint32_t m_nSize;                            // +0x10
    uint8_t m_bMulti;                            // +0x14
    uint8_t m_pad015[3];                         // +0x15
    void* m_pAllocator;                          // +0x18
};

// the relationship manager the values come from
class cRelationshipManager {
public:
    float CalculateRelationshipEvent(uint32_t nFrom, uint32_t nTo, uint32_t nEvent);  // 0x00d03d70
};

cRelationshipManager* __stdcall RelationshipManager();       // 0x00b3d2c0

// descending order by absolute relationship value
struct cAbsValueLess {
    float Abs(uint32_t nEvent) const
    {
        float fValue = *m_pValues->GetValue(nEvent);
        return (float)fabs(fValue);
    }

    bool operator()(uint32_t nLeft, uint32_t nRight) const
    {
        return Abs(nLeft) > Abs(nRight);
    }

    cRelationshipValues* m_pValues;              // +0x00
};

// ---------------------------------------------------------------------------
// event id -> localized string (eastl::map<unsigned int, SP::cString>)
// ---------------------------------------------------------------------------

class cStringMap {
public:
    struct Node {
        Node* m_pLeft;                           // +0x00
        Node* m_pRight;                          // +0x04
        void* m_pad008;                          // +0x08
        void* m_pad00c;                          // +0x0c
        uint32_t m_nKey;                         // +0x10
        SP::cString m_cValue;                    // +0x14
    };

    // the string slot for a key, inserted empty when the key is new
    SP::cString& GetStringSlot(uint32_t nKey);                    // 0x00e2cb00

    // insert a node below the hint
    Node* Insert(Node* pHint, uint32_t nKey, const SP::cString& cValue);  // 0x00e2c770

    Node* m_pRoot;                               // +0x00
    Node m_stHeader;                             // +0x04
    uint32_t m_nSize;                            // +0x10
};

// the personality-string list the rollover keeps
class cStringVector {
public:
    SP::cString& operator[](int32_t nIndex);     // 0x00e2ca70

    SP::cString* m_pBegin;                       // +0x00
    SP::cString* m_pEnd;                         // +0x04
    SP::cString* m_pCapacity;                    // +0x08
};

// ---------------------------------------------------------------------------
// the rollover window
// ---------------------------------------------------------------------------

class cSPUIRolloverCivRelationship : public cSPUIPropertyLayout {
public:
    bool Init();                                 // 0x00e2cba0

    // cSPUIPropertyLayout occupies +0x00 .. +0x77
    SP::cString mTooManyCitiesString;            // +0x78
    SP::cString mTooCloseToUsString;             // +0x8c
    SP::cString mNemesisString;                  // +0xa0
    SP::cString mNemesisTitleString;             // +0xb4
    cStringVector m_vPersonality;                // +0xc8
    cStringMap m_mRelationshipStrings;           // +0xdc
    int32_t m_nRelationshipCount;                // +0xf8
};

int32_t __cdecl CountRelationshipRows(cSPUIRolloverCivRelationship* pRollover);  // 0x00e2a760

static const uint32_t kStringTable = 0xa14ee9b6;
static const uint32_t kTooManyCitiesKey = 0x0526e60d;
static const uint32_t kTooCloseToUsKey = 0x0526e617;
static const uint32_t kNemesisKey = 0x05663bc8;
static const uint32_t kNemesisTitleKey = 0x0601a074;
static const uint32_t kPersonalityKeys[3] = { 0x0526e4d6, 0x0526e4db, 0x0526e4e1 };

// ---------------------------------------------------------------------------
// event id -> localized string lookup
// ---------------------------------------------------------------------------

// @ 0x00e2cb00
SP::cString& cStringMap::GetStringSlot(uint32_t nKey)
{
    Node* pHeader = &m_stHeader;
    Node* pNode = m_pRoot;
    Node* pParent = pHeader;
    while (pNode != nullptr) {
        if (pNode->m_nKey < nKey)
            pNode = pNode->m_pLeft;
        else {
            pParent = pNode;
            pNode = pNode->m_pRight;
        }
    }
    if (pParent == pHeader || nKey < pParent->m_nKey) {
        SP::cString cEmpty;
        Node* pInserted = Insert(pParent, nKey, cEmpty);
        if (pInserted != nullptr)
            pParent = pInserted;
    }
    return pParent->m_cValue;
}

// ---------------------------------------------------------------------------
// the rollover initialisation
// ---------------------------------------------------------------------------

// @ 0x00e2cba0
bool cSPUIRolloverCivRelationship::Init()
{
    bool bLayoutReady = false;
    if (cSPUIPropertyLayout::Init()) {
        EA::UTFWin::IWindow* pRootWindow = GetRootWindow();
        if (pRootWindow->GetParentWindow() == 0) {
            SPUIHelpers_GetLayoutManager(0x05b598f6)
                ->GetWorldMainWindow(0x05b598f6)
                ->AddChildWindow(pRootWindow);
        }
        bLayoutReady = true;
    }

    mTooManyCitiesString.Load(kStringTable, kTooManyCitiesKey, 0);
    mTooCloseToUsString.Load(kStringTable, kTooCloseToUsKey, 0);
    mNemesisString.Load(kStringTable, kNemesisKey, 0);
    mNemesisTitleString.Load(kStringTable, kNemesisTitleKey, 0);

    // the personality list always keeps its three entries
    m_vPersonality[3];
    SP::cString* pPersonality = m_vPersonality.m_pBegin;
    for (int32_t i = 0; i < 3; ++i)
        pPersonality[i].Load(kStringTable, kPersonalityKeys[i], 0);

    cEventVector* pEvents = GetRelationshipEvents();
    for (uint32_t* pEvent = pEvents->m_pBegin; pEvent != pEvents->m_pEnd; ++pEvent)
        m_mRelationshipStrings.GetStringSlot(*pEvent).Load(kStringTable, *pEvent, 0);

    m_nRelationshipCount = CountRelationshipRows(this);
    return bLayoutReady;
}

// ---------------------------------------------------------------------------
// the relationship value snapshot
// ---------------------------------------------------------------------------

// @ 0x00e2cce0
cRelationshipValues& cRelationshipValues::Read(uint32_t nFrom, uint32_t nTo)
{
    Reset();

    cEventVector* pEvents = GetRelationshipEvents();
    for (uint32_t* pEvent = pEvents->m_pBegin; pEvent != pEvents->m_pEnd; ++pEvent) {
        uint32_t nEvent = *pEvent;
        float fValue;
        if (nFrom == nTo)
            fValue = 0.0f;
        else
            fValue = RelationshipManager()->CalculateRelationshipEvent(nFrom, nTo, nEvent);
        *GetValue(nEvent) = fValue;
    }
    return *this;
}

// ---------------------------------------------------------------------------
// ordering helpers
// ---------------------------------------------------------------------------

// @ 0x00e2cd70
void RelationshipInsertionSort(cAbsValueLess& less, uint32_t* pFirst, uint32_t* pLast)
{
    if (pFirst == pLast)
        return;

    for (uint32_t* pCur = pFirst + 1; pCur != pLast; ++pCur) {
        uint32_t nValue = *pCur;
        uint32_t* pHole = pCur;
        for (; pHole != pFirst; --pHole) {
            uint32_t nPrev = pHole[-1];
            if (!less(nValue, nPrev))
                break;
            *pHole = nPrev;
        }
        *pHole = nValue;
    }
}

// @ 0x00e2ce30
void RelationshipInsertionSortTail(cAbsValueLess& less, uint32_t* pFirst, uint32_t* pLast)
{
    for (uint32_t* pCur = pFirst; pCur != pLast; ++pCur) {
        uint32_t nValue = *pCur;
        uint32_t* pHole = pCur;
        while (less(nValue, pHole[-1])) {
            *pHole = pHole[-1];
            --pHole;
        }
        *pHole = nValue;
    }
}

// @ 0x00e2ced0
uint32_t* RelationshipMedianOfThree(cAbsValueLess& less, uint32_t* pFirst,
                                    uint32_t* pMiddle, uint32_t* pLast)
{
    if (less(*pFirst, *pMiddle)) {
        if (less(*pMiddle, *pLast))
            return pMiddle;
        if (less(*pFirst, *pLast))
            return pLast;
        return pFirst;
    }
    if (less(*pFirst, *pLast))
        return pFirst;
    if (less(*pMiddle, *pLast))
        return pLast;
    return pMiddle;
}

// @ 0x00e2d0a0
uint32_t* RelationshipPartition(cAbsValueLess& less, uint32_t* pFirst, uint32_t* pLast,
                                uint32_t nPivot)
{
    for (;;) {
        while (less(*pFirst, nPivot))
            ++pFirst;
        --pLast;
        while (less(nPivot, *pLast))
            --pLast;
        if (pLast <= pFirst)
            return pFirst;
        uint32_t nSwap = *pFirst;
        *pFirst = *pLast;
        *pLast = nSwap;
        ++pFirst;
    }
}

// @ 0x00e2d180
void RelationshipPushHeap(cAbsValueLess& less, uint32_t* pFirst, int32_t nHole,
                          uint32_t nValue)
{
    int32_t nParent = (nHole - 1) / 2;
    while (nHole > 0 && less(pFirst[nParent], nValue)) {
        pFirst[nHole] = pFirst[nParent];
        nHole = nParent;
        nParent = (nHole - 1) / 2;
    }
    pFirst[nHole] = nValue;
}

// @ 0x00e2d220
void RelationshipAdjustHeap(cAbsValueLess& less, uint32_t* pFirst, int32_t nHole,
                            int32_t nLength, uint32_t nValue)
{
    int32_t nChild = nHole * 2 + 2;
    while (nChild < nLength) {
        if (less(pFirst[nChild], pFirst[nChild - 1]))
            --nChild;
        pFirst[nHole] = pFirst[nChild];
        nHole = nChild;
        nChild = nChild * 2 + 2;
    }
    if (nChild == nLength) {
        pFirst[nHole] = pFirst[nChild - 1];
        nHole = nChild - 1;
    }
    RelationshipPushHeap(less, pFirst, nHole, nValue);
}

// @ 0x00e2d300
void RelationshipMakeHeap(cAbsValueLess& less, uint32_t* pFirst, uint32_t* pLast)
{
    int32_t nLength = (int32_t)(pLast - pFirst);
    if (nLength < 2)
        return;

    int32_t nHole = (nLength - 2) / 2 + 1;
    do {
        --nHole;
        RelationshipAdjustHeap(less, pFirst, nHole, nLength, pFirst[nHole]);
    } while (nHole != 0);
}

// @ 0x00e2d360
void RelationshipSortHeap(cAbsValueLess& less, uint32_t* pFirst, uint32_t* pLast)
{
    int32_t nLength = (int32_t)(pLast - pFirst);
    while (nLength > 1) {
        --pLast;
        uint32_t nValue = *pLast;
        *pLast = *pFirst;
        --nLength;
        RelationshipAdjustHeap(less, pFirst, 0, nLength, nValue);
    }
}

// @ 0x00e2d430
void RelationshipPartialSort(cAbsValueLess& less, uint32_t* pFirst, uint32_t* pMiddle,
                             uint32_t* pLast)
{
    RelationshipMakeHeap(less, pFirst, pMiddle);
    for (uint32_t* pCur = pMiddle; pCur < pLast; ++pCur) {
        if (less(*pFirst, *pCur)) {
            uint32_t nValue = *pCur;
            *pCur = *pFirst;
            RelationshipAdjustHeap(less, pFirst, 0, (int32_t)(pMiddle - pFirst), nValue);
        }
    }
    RelationshipSortHeap(less, pFirst, pMiddle);
}

// @ 0x00e2d520
void RelationshipIntrosortLoop(cAbsValueLess& less, uint32_t* pFirst, uint32_t* pLast,
                               int32_t nDepthLimit)
{
    while ((int32_t)(pLast - pFirst) > 0x1c && nDepthLimit > 0) {
        uint32_t* pMiddle = pFirst + (pLast - pFirst) / 2;
        uint32_t* pMedian = RelationshipMedianOfThree(less, pFirst, pMiddle, pLast - 1);
        uint32_t nPivot = *pMedian;
        uint32_t* pCut = RelationshipPartition(less, pFirst, pLast, nPivot);
        --nDepthLimit;
        RelationshipIntrosortLoop(less, pCut, pLast, nDepthLimit);
        pLast = pCut;
    }
    if (nDepthLimit == 0)
        RelationshipPartialSort(less, pFirst, pLast, pLast);
}

// @ 0x00e2d5f0
void RelationshipSort(cAbsValueLess& less, uint32_t* pFirst, uint32_t* pLast)
{
    if (pFirst == pLast)
        return;

    int32_t nLength = (int32_t)(pLast - pFirst);
    int32_t nDepth = 0;
    for (int32_t nRemaining = nLength; nRemaining != 0; nRemaining >>= 1)
        ++nDepth;

    RelationshipIntrosortLoop(less, pFirst, pLast, nDepth * 2 - 2);
    if (nLength > 0x1c) {
        RelationshipInsertionSort(less, pFirst, pFirst + 0x1c);
        RelationshipInsertionSortTail(less, pFirst + 0x1c, pLast);
    } else {
        RelationshipInsertionSort(less, pFirst, pLast);
    }
}
