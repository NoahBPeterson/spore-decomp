// Slice s00de23a0: UI callout sequencer / property-table group behaviour (timed callout ticks,
// rolling star hint windows, property-list id->value tables and their construction).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
// Layouts: cUICalloutSequencer (Stopwatch +0x08, ids +0x24..0x2c, countdown +0x30, effect +0x34,
// event id +0x38, xform +0x40, owner +0x48, Stopwatch +0xb8, flags +0xa0), cUIHintTrigger
// (Stopwatch +0x08, payload id +0x20, countdown +0x40, callout id +0x44, owner +0x48),
// cUIPropertyTableSet (Stopwatch +0x08, listener +0x34, table triple +0x40, Stopwatch +0xb8,
// string hashes +0xd4..+0xe0), eastl hash tables are 0x20 bytes with the bucket array at +0x04.
#include "types.h"
#include <math.h>

#define VSLOT(n) virtual void _v##n();

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float fX, float fY, float fZ) : x(fX), y(fY), z(fZ) {}
};

struct Matrix3 {
    float m[3][3];
};

// Transform message posted to the effect system (see cIEffectsManager).
struct XformMsg {
    uint16_t mnFlags;       // +0x00
    uint16_t mnVersion;     // +0x02
    Vector3 mPos;           // +0x04
    float mfScale;          // +0x10
    Matrix3 mMatrix;        // +0x14
};

// ---------------------------------------------------------------------------
// EA::Stopwatch
// ---------------------------------------------------------------------------
namespace EA {
// The original Stopwatch only needs 4-byte alignment: classes that put a byte flag
// between the vfptr and the timer (cUICalloutSequencer) still see the timer at +0x08.
#pragma pack(push, 4)
class Stopwatch {
public:
    enum Units { kUnitsCycles = 0, kUnitsMilliseconds = 4, kUnitsSeconds = 5 };
    Stopwatch(int nUnits, bool bStartImmediately);   // 0x0093A560
    int64_t GetElapsedTime() const;                  // 0x0093A3A0
    void SetUnits(int nUnits);                       // 0x0093A1A0
    void Reset();                                    // 0x0093A2E0
    uint64_t mnStartTime;         // +0x00
    uint64_t mnTotalElapsedTime;  // +0x08
    int32_t mnUnits;              // +0x10
    float mfUnitsPerCycle;        // +0x14
};
#pragma pack(pop)
} // namespace EA

// ---------------------------------------------------------------------------
// reference counted objects
// ---------------------------------------------------------------------------
class IRefCounted {
public:
    VSLOT(0)
    virtual int Release();                                          // +0x04
};

class IVisualEffect {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual void SetTransform(const XformMsg* pMsg);                  // +0x18
};

// ---------------------------------------------------------------------------
// property lists
// ---------------------------------------------------------------------------
class SP_cString;

class cPropertyList : public IRefCounted {
public:
};

class cPropertyManager {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10)
    virtual bool GetProperty(void* pObject, int32_t nFlags, cPropertyList** ppList);  // +0x2c
};

template <class T>
class AutoRefCount {
public:
    AutoRefCount() : mpObject(0) {}
    AutoRefCount& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* mpObject;
};

namespace SP {
cPropertyManager* PropertyManager();                                             // 0x0067de30
bool GetPropertyAsUint32Array(cPropertyList* pList, uint32_t nProperty,
                              int32_t* pnCount, uint32_t** ppValues);            // 0x006a0840
bool GetPropertyAsString16(cPropertyList* pList, uint32_t nProperty,
                           const wchar_t** ppString);                            // 0x006a1400
uint32_t FNV1_String16(const wchar_t* pString, uint32_t nSeed, uint32_t nSalt);  // 0x00932f30

// Localised string built from a (table, key) pair (ctor 0x006b5770).
class cString {
public:
    cString(uint32_t nTable, uint32_t nKey, const wchar_t* pString);
    cString(const cString& other);   // 0x006b56f0
    ~cString();                      // 0x006b5240
    uint32_t mnTable;                // +0x00
    uint32_t mnKey;                  // +0x04
};

void InsertStringEntry(void* pTable, uint32_t nKey, const cString& value, bool bFlag);  // 0x00de19a0
void DeleteArray(void* pBlock);                                                          // 0x00f47380
void* memcpy(void* pDst, const void* pSrc, uint32_t nSize);                              // 0x011e0744
} // namespace SP

// ---------------------------------------------------------------------------
// eastl hash tables
// ---------------------------------------------------------------------------
struct sHashNode;
extern sHashNode* gEmptyBucketArray[1];   // 0x0154df28

// eastl::vector<uint32_t> as stored inside the table nodes (begin +0x00, end +0x04, cap +0x08).
struct sU32List {
    uint32_t* mpBegin;      // +0x00
    uint32_t* mpEnd;        // +0x04
    uint32_t* mpCapacity;   // +0x08
    uint32_t* InsertAt(uint32_t* pWhere, const uint32_t* pValue);   // 0x004558a0
};

struct sHashNode {
    uint32_t mnKey;         // +0x00
    sU32List mValues;       // +0x04
    uint32_t mnPad10;       // +0x10
    uint32_t mnPad14;       // +0x14
    sHashNode* mpNext;      // +0x18
};

struct sTableIterator {
    sHashNode* mpNode;      // +0x00
    sHashNode** mppBucket;  // +0x04
};

// node payload handed to the insert helper: the key plus a vector of ids to copy into the node
struct sKeyValuePair {
    uint32_t mnKey;         // +0x00
    sU32List mValues;       // +0x04
};

// result of the insert helper: the node found/created, its bucket and whether it was created
struct sInsertResult {
    sHashNode* mpNode;      // +0x00
    sHashNode** mppBucket;  // +0x04
    uint8_t mbInserted;     // +0x08
    uint8_t mnPad09[0x03];  // +0x09
};

// Frees a vector block allocated by sU32List::InsertAt (the block carries a count word in front).
inline void FreeU32List(sU32List& list) {
    if (list.mpBegin) {
        int32_t* pHeader = (int32_t*)list.mpBegin - 1;
        if (*pHeader != 0)
            SP::DeleteArray(list.mpBegin);
    }
    list.mpBegin = 0;
    list.mpEnd = 0;
    list.mpCapacity = 0;
}

struct sHashTable {
    uint32_t mnFlags;         // +0x00  (left untouched by the ctor)
    sHashNode** mpBuckets;    // +0x04
    uint32_t mnBucketCount;   // +0x08
    uint32_t mnElementCount;  // +0x0c
    float mfMaxLoadFactor;    // +0x10
    float mfGrowthFactor;     // +0x14
    uint32_t mnPad18;         // +0x18
    uint32_t mnPad1c;         // +0x1c
    sHashTable() : mfMaxLoadFactor(1.0f), mfGrowthFactor(2.0f), mnElementCount(0),
                   mnPad18(0), mnBucketCount(1), mpBuckets(gEmptyBucketArray) {}
    void Find(sTableIterator* pIt, const uint32_t* pKey) const;           // 0x00aea1b0
    void Insert(sInsertResult* pOut, const sKeyValuePair* pPair, bool bFindExisting); // 0x00aeb960
    void DestroyBuckets(sHashNode** pBuckets, uint32_t nBucketCount);     // 0x00aeb030
    void DestroyStringBuckets(sHashNode** pBuckets, uint32_t nBucketCount); // 0x00de2350
};

// ---------------------------------------------------------------------------
// property tables: three id-keyed tables, the last one holds vectors of ids
// ---------------------------------------------------------------------------
class cPropertyTableTriple {
public:
    sHashTable mTable0;     // +0x00
    sHashTable mTable1;     // +0x20
    sHashTable mTable2;     // +0x40
    cPropertyTableTriple() {}   // inlined into 0x00de2d00
    void LoadStringPairs(uint32_t nObject, uint32_t nProperty);   // 0x00de28f0
    void Clear();                                                 // 0x00de29f0
    void Destroy();                                               // 0x00de2a50
    void AddValue1(uint32_t nKey, uint32_t nValue);               // 0x00de2ae0
    void AddValue0(uint32_t nKey, uint32_t nValue);               // 0x00de2bf0
    void LoadGroup0(uint32_t nObject, uint32_t nProperty);        // 0x00de2e20
    void LoadGroup1(uint32_t nObject, uint32_t nProperty);        // 0x00de2ed0
};

// Base object created by 0x00e00630.
class cUIPropertyBase {
public:
    cUIPropertyBase();
};

class cUIPropertyTableSet : public cUIPropertyBase {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18)
    VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26)
    virtual ~cUIPropertyTableSet();                               // 0x00de2de0
    cUIPropertyTableSet();                                        // 0x00de2d00
    void Init();                                                  // 0x00de2f80
    uint32_t mnPad04;               // +0x04 (never touched)
    EA::Stopwatch mTimer;           // +0x08
    uint32_t mnPad20;               // +0x20
    uint32_t mnPad24;               // +0x24
    uint32_t mnPad28;               // +0x28
    uint32_t mnPad2c;               // +0x2c
    uint32_t mnPad30;               // +0x30
    IRefCounted* mpListener;        // +0x34
    uint32_t mnPad38;               // +0x38
    uint32_t mnPad3c;               // +0x3c
    cPropertyTableTriple mTables;   // +0x40
    uint8_t mbA0;                   // +0xa0
    uint32_t mnPadA4;               // +0xa4
    uint32_t mnPadA8;               // +0xa8
    uint32_t mnPadAC;               // +0xac
    void* mpB0;                     // +0xb0
    uint32_t mnPadB4;               // +0xb4
    EA::Stopwatch mTimer2;          // +0xb8
    uint8_t mbD0;                   // +0xd0
    uint32_t mnPadD4;               // +0xd4
    uint32_t mnPadD8;               // +0xd8
    uint32_t mnPadDC;               // +0xdc
    uint32_t mnPadE0;               // +0xe0
};

// ---------------------------------------------------------------------------
// UI globals
// ---------------------------------------------------------------------------
class cUIWindow;
class cStarEntry;

class cWindowManager {
public:
    cUIWindow* FindWindowByID(uint32_t nID);    // 0x00e012b0
    void* GetActiveXform();                     // 0x0093b6c0
};

class cSPUIGlobalUI {
public:
    uint8_t mnPad000[0x101];        // +0x000
    uint8_t mbMenuActive;           // +0x101
    uint8_t mbOverlayActive;        // +0x102
    uint8_t mnPad103[0x05];         // +0x103
    int32_t mnMode;                 // +0x108
    uint8_t mnPad10c[0x78];         // +0x10c
    cWindowManager* mpWindows;      // +0x184
    uint8_t mnPad188[0x50];         // +0x188
    cStarEntry** mppStars;          // +0x1d8
    cStarEntry** mppStarsEnd;       // +0x1dc
    cStarEntry** mppStarsCapacity;  // +0x1e0
    uint8_t mnPad1e4[0x0d];         // +0x1e4
    uint8_t mbNoCallouts;           // +0x1f1
    uint8_t mnPad1f2[0x7e];         // +0x1f2
    uint8_t mbGalaxyOpen;           // +0x270
    void SetCalloutEnabled(int bEnabled);          // 0x00de53d0
    void SetEditorMode(int nMode, int nArg);       // 0x00de86d0
    void UpdateCalloutWindows();                   // 0x00de5260
};

extern cSPUIGlobalUI* gUI;                   // 0x016a1344
extern uint8_t gCalloutWindowsEnabled;       // 0x016a0e68
extern uint32_t gHintWindowId;               // 0x016a0e88
extern float gCalloutFadePeriod;             // 0x016a0f48
extern float gCalloutSpinRate;               // 0x016a114c
extern float gCalloutSpinBias;               // 0x016a0f58
extern float gCalloutTimeout;                // 0x016a0ed8
extern Matrix3 gCalloutMatrix;               // 0x016a1184
extern Vector3 gCalloutTranslation;          // 0x016a11a8

struct cAppSettings {
    uint8_t mnPad00[0x1c];      // +0x00
    uint8_t mbFreeCam;          // +0x1c
};
cAppSettings* GetSetting3();                    // 0x00401030

class cUIWindow {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    virtual bool IsPlaying();                                  // +0x28
    VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19)
    VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28)
    VSLOT(29) VSLOT(30)
    virtual void SetVisible(bool bVisible, bool bFlag);        // +0x7c
};

void SetWindowScale(cUIWindow* pWindow, float fX, float fY);     // 0x00808190
void CalloutMessageBox(void* pOwner, const void* pMsgSpec);      // 0x00809db0
bool IsWorldLayoutFlagSet(uint32_t nFlag);                       // 0x00685520
void GetCameraBasis(float* pfA, float* pfB);                     // 0x00804ed0

// Queued sound/effect event (0x2c bytes) reset by 0x00ef19f0.
struct sPositionEvent {
    int32_t mFrom[3];       // +0x00
    int32_t mTo[3];         // +0x0c
    int32_t mnPad18;        // +0x18
    int32_t mnPad1c;        // +0x1c
    int32_t mnPad20;        // +0x20
    int32_t mnType;         // +0x24
    int32_t mnPad28;        // +0x28
};
sPositionEvent* ResetPositionEvent();                            // 0x00ef19f0

class cEventDispatcher {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    virtual void Dispatch(uint32_t nEventId);                    // +0x28
};
cEventDispatcher* GetEventDispatcher();                          // 0x0067dd20

// ---------------------------------------------------------------------------
// callout sequencer (owns the visual effect and the queued event)
// ---------------------------------------------------------------------------
class cUICalloutSequencer {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18)
    VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22)
    virtual void OnCalloutEnded();                                // +0x5c
    void Update(float fDeltaTime);                                // 0x00de23a0
    uint8_t mbBlocked;              // +0x04
    uint8_t mnPad05[0x03];          // +0x05
    EA::Stopwatch mTimer;           // +0x08
    uint8_t mbStarted;              // +0x20
    uint8_t mbPreviousFreeCam;      // +0x21
    uint8_t mnPad22[0x02];          // +0x22
    int32_t mnValue24;              // +0x24
    int32_t mnValue28;              // +0x28
    int32_t mnValue2C;              // +0x2c
    int32_t mnCountdown;            // +0x30
    IVisualEffect* mpEffect;        // +0x34
    uint32_t mnEventID;             // +0x38
    uint32_t mnPad3C;               // +0x3c
    uint32_t mnPad40;               // +0x40
    uint32_t mnPad44;               // +0x44
    void* mpOwner;                  // +0x48
    uint8_t mnPad4C[0x54];          // +0x4c
    uint8_t mbA0;                   // +0xa0
    uint8_t mnPadA1[0x03];          // +0xa1
    uint32_t mnPadA4;               // +0xa4
    uint32_t mnPadA8;               // +0xa8
    uint32_t mnPadAC;               // +0xac
    void* mpB0;                     // +0xb0
    uint32_t mnPadB4;               // +0xb4
    EA::Stopwatch mTimer2;          // +0xb8
    uint8_t mbD0;                   // +0xd0
};

void PostCalloutXform(void* pXform, float fA, float fB, uint32_t nEventID);   // 0x00de2180

// @ 0x00de23a0
void cUICalloutSequencer::Update(float fDeltaTime) {
    if (mnCountdown != 0) {
        --mnCountdown;
        if (mnCountdown == 0) {
            if (mnEventID == 0x7a7f799) {
                mnEventID = 0;
                if (mnValue24 != 0) {
                    sPositionEvent* pEvent = ResetPositionEvent();
                    pEvent->mFrom[0] = mnValue24;
                    pEvent->mFrom[1] = mnValue28;
                    pEvent->mFrom[2] = mnValue2C;
                    pEvent->mTo[0] = 0;
                    pEvent->mTo[1] = 0;
                    pEvent->mTo[2] = 0;
                    pEvent->mnPad18 = 0;
                    pEvent->mnPad1c = 0;
                    pEvent->mnPad20 = 0;
                    pEvent->mnType = 1;
                    pEvent->mnPad28 = 0;
                    GetEventDispatcher()->Dispatch(0x21851ebe);
                    return;
                }
            } else if (mnEventID == 0x7a7f798) {
                mnEventID = 0;
                if (mnValue24 != 0) {
                    sPositionEvent* pEvent = ResetPositionEvent();
                    pEvent->mFrom[0] = 0;
                    pEvent->mFrom[1] = 0;
                    pEvent->mFrom[2] = 0;
                    pEvent->mTo[0] = mnValue24;
                    pEvent->mTo[1] = mnValue28;
                    pEvent->mTo[2] = mnValue2C;
                    pEvent->mnPad18 = 0;
                    pEvent->mnPad1c = 0;
                    pEvent->mnPad20 = 0;
                    pEvent->mnType = 1;
                    pEvent->mnPad28 = 0;
                    GetEventDispatcher()->Dispatch(0x21851ebe);
                    return;
                }
            }
        }
    }
    if (mTimer2.mnStartTime) {
        uint32_t aWindowIDs[4] = {0x7a7f799, 0x7a7f798, 0x5943b78, 0x6260bc8};
        float fFade = (float)mTimer2.GetElapsedTime() * mTimer2.mfUnitsPerCycle /
                      (gCalloutFadePeriod * 1000.0f);
        for (uint32_t i = 0; i < 4; ++i) {
            cUIWindow* pWindow = gUI->mpWindows->FindWindowByID(aWindowIDs[i]);
            if (!pWindow)
                continue;
            if (1.0f <= fFade) {
                SetWindowScale(pWindow, 1.0f, 1.0f);
                mTimer2.Reset();
            } else {
                float fScale = (float)sin((double)gCalloutSpinRate * (double)fFade) *
                                   (1.0f - fFade) * gCalloutSpinBias + 1.0f;
                SetWindowScale(pWindow, fScale, fScale);
            }
        }
    }
    gUI->UpdateCalloutWindows();
    cAppSettings* pSettings = GetSetting3();
    uint8_t bFreeCam = pSettings->mbFreeCam;
    if (!bFreeCam && mbPreviousFreeCam) {
        gUI->SetCalloutEnabled(0);
        gUI->SetCalloutEnabled(1);
        if (gUI->mnMode == 3)
            gUI->SetEditorMode(5, 0);
        mnPadA8 = 0;
    }
    IVisualEffect* pEffect = mpEffect;
    mbPreviousFreeCam = bFreeCam;
    if (pEffect) {
        XformMsg msg;
        Vector3 vZero(0.0f, 0.0f, 0.0f);
        msg.mnVersion = 1;
        msg.mnFlags = 4;
        msg.mMatrix = gCalloutMatrix;
        msg.mfScale = 1.0f;
        msg.mPos.x = (gCalloutMatrix.m[2][0] + gCalloutMatrix.m[0][0]) * vZero.x -
                     gCalloutMatrix.m[1][0] * 10.0f + gCalloutTranslation.x;
        msg.mPos.y = (gCalloutMatrix.m[2][1] + gCalloutMatrix.m[0][1]) * vZero.y -
                     gCalloutMatrix.m[1][1] * 10.0f + gCalloutTranslation.y;
        msg.mPos.z = (gCalloutMatrix.m[2][2] + gCalloutMatrix.m[0][2]) * vZero.z -
                     gCalloutMatrix.m[1][2] * 10.0f + gCalloutTranslation.z;
        pEffect->SetTransform(&msg);
    }
    if (mTimer.mnStartTime) {
        if ((float)mTimer.GetElapsedTime() * mTimer.mfUnitsPerCycle <= gCalloutTimeout)
            return;
        mTimer.Reset();
        return;
    }
    cUIWindow* pWindow = gUI->mpWindows->FindWindowByID(0x3685038);
    if (pWindow) {
        bool bPlaying = pWindow->IsPlaying();
        bool bShouldPlay = !(gUI->mbMenuActive || bFreeCam || mbBlocked || mbStarted ||
                             gUI->mbGalaxyOpen || gUI->mbOverlayActive);
        if (bPlaying) {
            if (!bShouldPlay) {
                gUI->SetCalloutEnabled(0);
                pWindow->SetVisible(1, false);
            }
        } else if (bShouldPlay) {
            gUI->SetCalloutEnabled(1);
            pWindow->SetVisible(1, true);
        }
    }
    if (!gCalloutWindowsEnabled)
        return;
    if (gUI->mbNoCallouts)
        return;
    float fA;
    float fB;
    GetCameraBasis(&fB, &fA);
    if (!pSettings || !pSettings->mbFreeCam) {
        mpB0 = gUI->mpWindows->GetActiveXform();
        PostCalloutXform(&mnPad40, fA, fB, mnEventID);
    }
    pWindow = gUI->mpWindows->FindWindowByID(gHintWindowId);
    if (pWindow)
        pWindow->SetVisible(1, mbA0 == 0);
    bool bGalaxyHint;
    if (mnEventID != 0 && mnEventID != 0x7a7ec60 && gUI->mbGalaxyOpen)
        bGalaxyHint = true;
    else
        bGalaxyHint = false;
    pWindow = gUI->mpWindows->FindWindowByID(0x689a975);
    if (pWindow)
        pWindow->SetVisible(1, bGalaxyHint);
    bool bGalaxyEntry = (mnEventID == 0x7a7ec60);
    uint32_t aHintIDs[2] = {0x7a7f799, 0x7a7f798};
    if (IsWorldLayoutFlagSet(2)) {
        for (uint32_t i = 0; i < 2; ++i) {
            pWindow = gUI->mpWindows->FindWindowByID(aHintIDs[i]);
            if (pWindow)
                pWindow->SetVisible(1, bGalaxyEntry);
        }
    }
}

// ---------------------------------------------------------------------------
// callout trigger (countdown -> callout message)
// ---------------------------------------------------------------------------
class cEffectSet;

struct cCalloutOwner {
    uint32_t mnID;              // +0x00
    uint8_t mnPad04[0xb4];      // +0x04
    cEffectSet* mpEffectSet;    // +0xb8
};

class cPlanetRecord {
public:
    void Setup();                                             // 0x00b28850
};
cPlanetRecord* __stdcall GetPlanetRecord(uint32_t nID);       // 0x00b3d340 (callee pops its arg)

class cStarManager {
public:
    void UpdateRolloverStars();                               // 0x00bb6040
    void UpdateStarEffects();                                 // 0x00bb7620
};
cStarManager* StarManager();                                  // 0x00b3d2a0

class cLocalPlayer {
public:
    bool FindLocal(uint32_t nID);                             // 0x00801bb0
};
cLocalPlayer* __stdcall GetLocalPlayer(uint32_t nID);         // 0x0067cab0 (callee pops its arg)

class cEffectSet {
public:
    void SetFlag(int nFlag);                                  // 0x00df6850
    void Highlight(int nFlag);                                // 0x00df6700
};

class cRolloverManager {
public:
    void SetupRolloverStarEffects();                          // 0x00df8330
};
cRolloverManager* GetRolloverManager();                       // 0x00df5f40
void* GetGameData();                                          // 0x0067de40

class cGameDataIface {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    virtual cGameDataIface* GetSub();                         // +0x20
    VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12)
    virtual void SetStar(uint32_t nID, bool bValue);           // +0x34
};

class cStarEntry {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11)
    virtual void SetFlag(int nFlag);                          // +0x30
};

// Callout message descriptor objects handed to CalloutMessageBox by address.
extern uint32_t gCalloutMessageSpec;  // 0x015a3328
extern uint32_t gGalaxyMessageSpec;   // 0x015a331c

class cUIHintTrigger {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18)
    VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22)
    virtual void OnTriggerEnded();                            // +0x5c
    void Tick(float fDeltaTime);                              // 0x00de3130
    void Close();                                             // 0x00de3240
    uint32_t mnPad04;           // +0x04 (never touched)
    EA::Stopwatch mTimer;       // +0x08
    uint32_t mnValue20;         // +0x20
    uint8_t mnPad24[0x1c];      // +0x24
    int32_t mnCountdown;        // +0x40
    uint32_t mnCalloutID;       // +0x44
    cCalloutOwner* mpOwner;     // +0x48
};

// @ 0x00de3130
void cUIHintTrigger::Tick(float fDeltaTime) {
    if (mnCountdown > 0) {
        --mnCountdown;
        if (mnCountdown <= 0) {
            mnCountdown = 0;
            GetPlanetRecord((uint32_t)mpOwner)->Setup();
            OnTriggerEnded();
            StarManager()->UpdateRolloverStars();
            StarManager()->UpdateStarEffects();
            GetLocalPlayer(mnCalloutID)->FindLocal(0);
        }
    }
    if (mTimer.mnStartTime) {
        if (200.0f < (float)mTimer.GetElapsedTime() * mTimer.mfUnitsPerCycle)
            mpOwner->mpEffectSet->SetFlag(0);
        if (2000.0f < (float)mTimer.GetElapsedTime() * mTimer.mfUnitsPerCycle) {
            cGameDataIface* pData = ((cGameDataIface*)GetGameData())->GetSub();
            pData->SetStar(mnValue20, false);
            CalloutMessageBox(this, &gCalloutMessageSpec);
            mTimer.Reset();
            mTimer.mnStartTime = 0;
            mTimer.mnTotalElapsedTime = 0;
        }
    }
}

// @ 0x00de3240
void cUIHintTrigger::Close() {
    if (mpOwner == 0) {
        gUI->SetEditorMode(2, 0);
        return;
    }
    GetRolloverManager()->SetupRolloverStarEffects();
    for (uint32_t i = 0; i < (uint32_t)(gUI->mppStarsEnd - gUI->mppStars); ++i)
        gUI->mppStars[i]->SetFlag(1);
    mpOwner->mpEffectSet->Highlight(0);
    cGameDataIface* pData = ((cGameDataIface*)GetGameData())->GetSub();
    pData->SetStar(mpOwner->mnID, false);
    CalloutMessageBox(this, &gGalaxyMessageSpec);
}
// ---------------------------------------------------------------------------
// property table triple
// ---------------------------------------------------------------------------
// @ 0x00de28f0
void cPropertyTableTriple::LoadStringPairs(uint32_t nObject, uint32_t nProperty) {
    AutoRefCount<cPropertyList> props;
    cPropertyManager* pManager = SP::PropertyManager();
    props = (cPropertyList*)0;
    if (pManager->GetProperty((void*)nObject, 0, &props.mpObject)) {
        int32_t nCount;
        uint32_t* pValues = 0;
        nCount = 0;
        SP::GetPropertyAsUint32Array(props.mpObject, nProperty, &nCount, &pValues);
        for (int32_t i = 0; i < nCount; i += 2) {
            SP::cString name(0x2b7a0311, pValues[i + 1], 0);
            SP::InsertStringEntry(&mTable2, pValues[i], name, false);
        }
    }
    if (props.mpObject)
        props.mpObject->Release();
}

// @ 0x00de29f0
void cPropertyTableTriple::Clear() {
    mTable0.DestroyBuckets(mTable0.mpBuckets, mTable0.mnBucketCount);
    mTable0.mnElementCount = 0;
    mTable1.DestroyBuckets(mTable1.mpBuckets, mTable1.mnBucketCount);
    mTable1.mnElementCount = 0;
    mTable2.DestroyStringBuckets(mTable2.mpBuckets, mTable2.mnBucketCount);
    mTable2.mnElementCount = 0;
}

// @ 0x00de2a50
void cPropertyTableTriple::Destroy() {
    mTable2.DestroyStringBuckets(mTable2.mpBuckets, mTable2.mnBucketCount);
    mTable2.mnElementCount = 0;
    if (mTable2.mnBucketCount > 1)
        SP::DeleteArray(mTable2.mpBuckets);
    mTable1.DestroyBuckets(mTable1.mpBuckets, mTable1.mnBucketCount);
    mTable1.mnElementCount = 0;
    if (mTable1.mnBucketCount > 1)
        SP::DeleteArray(mTable1.mpBuckets);
    mTable0.DestroyBuckets(mTable0.mpBuckets, mTable0.mnBucketCount);
    mTable0.mnElementCount = 0;
    if (mTable0.mnBucketCount > 1)
        SP::DeleteArray(mTable0.mpBuckets);
}

// @ 0x00de2ae0
void cPropertyTableTriple::AddValue1(uint32_t nKey, uint32_t nValue) {
    sTableIterator it;
    mTable1.Find(&it, &nKey);
    if (it.mpNode == mTable1.mpBuckets[mTable1.mnBucketCount]) {
        sKeyValuePair pair;
        pair.mnKey = nKey;
        pair.mValues.mpBegin = 0;
        pair.mValues.mpEnd = 0;
        pair.mValues.mpCapacity = 0;
        pair.mValues.InsertAt(0, &nValue);
        sInsertResult result;
        mTable1.Insert(&result, &pair, false);
        FreeU32List(pair.mValues);
    } else {
        uint32_t* pEnd = it.mpNode->mValues.mpEnd;
        if (pEnd < it.mpNode->mValues.mpCapacity) {
            it.mpNode->mValues.mpEnd = pEnd + 1;
            if (pEnd)
                *pEnd = nValue;
        } else {
            it.mpNode->mValues.InsertAt(pEnd, &nValue);
        }
    }
}

// @ 0x00de2bf0
void cPropertyTableTriple::AddValue0(uint32_t nKey, uint32_t nValue) {
    sTableIterator it;
    mTable0.Find(&it, &nKey);
    if (it.mpNode == mTable0.mpBuckets[mTable0.mnBucketCount]) {
        sKeyValuePair pair;
        pair.mnKey = nKey;
        pair.mValues.mpBegin = 0;
        pair.mValues.mpEnd = 0;
        pair.mValues.mpCapacity = 0;
        pair.mValues.InsertAt(0, &nValue);
        sInsertResult result;
        mTable0.Insert(&result, &pair, false);
        FreeU32List(pair.mValues);
    } else {
        uint32_t* pEnd = it.mpNode->mValues.mpEnd;
        if (pEnd < it.mpNode->mValues.mpCapacity) {
            it.mpNode->mValues.mpEnd = pEnd + 1;
            if (pEnd)
                *pEnd = nValue;
        } else {
            it.mpNode->mValues.InsertAt(pEnd, &nValue);
        }
    }
}

// @ 0x00de2e20
void cPropertyTableTriple::LoadGroup0(uint32_t nObject, uint32_t nProperty) {
    AutoRefCount<cPropertyList> props;
    cPropertyManager* pManager = SP::PropertyManager();
    props = (cPropertyList*)0;
    if (pManager->GetProperty((void*)nObject, 0, &props.mpObject)) {
        int32_t nCount;
        uint32_t* pValues = 0;
        nCount = 0;
        SP::GetPropertyAsUint32Array(props.mpObject, nProperty, &nCount, &pValues);
        for (int32_t i = 0; i < nCount; i += 2)
            AddValue1(pValues[i], pValues[i + 1]);
    }
    if (props.mpObject)
        props.mpObject->Release();
}

// @ 0x00de2ed0
void cPropertyTableTriple::LoadGroup1(uint32_t nObject, uint32_t nProperty) {
    AutoRefCount<cPropertyList> props;
    cPropertyManager* pManager = SP::PropertyManager();
    props = (cPropertyList*)0;
    if (pManager->GetProperty((void*)nObject, 0, &props.mpObject)) {
        int32_t nCount;
        uint32_t* pValues = 0;
        nCount = 0;
        SP::GetPropertyAsUint32Array(props.mpObject, nProperty, &nCount, &pValues);
        for (int32_t i = 0; i < nCount; i += 2)
            AddValue0(pValues[i], pValues[i + 1]);
    }
    if (props.mpObject)
        props.mpObject->Release();
}

// ---------------------------------------------------------------------------
// property table set
// ---------------------------------------------------------------------------
// Small string holder used by the property getters (empty string lives at 0x01667bac).
extern const wchar_t gEmptyString16[];   // 0x01667bac

struct sString16 {
    const wchar_t* mpBegin;      // +0x00
    const wchar_t* mpCapacity;   // +0x04
    const wchar_t* mpEnd;        // +0x08
    sString16() {
        mpBegin = gEmptyString16;
        mpCapacity = gEmptyString16;
        mpEnd = gEmptyString16 + 1;
    }
    ~sString16() {
        if ((((uint32_t)mpEnd - (uint32_t)mpBegin) & 0xfffffffe) > 2)
            SP::DeleteArray((void*)mpBegin);
    }
};

extern cPropertyList* gScriptProperties;   // 0x015a2df8

// @ 0x00de2d00
cUIPropertyTableSet::cUIPropertyTableSet()
    : mTimer(0, false), mnPad24(0), mnPad28(0), mnPad2c(0), mnPad30(0), mpListener(0),
      mTables(), mbA0(0), mnPadA4(0), mnPadA8(0), mpB0(0), mTimer2(0, false) {
    mbD0 = 0;
}

// @ 0x00de2de0
cUIPropertyTableSet::~cUIPropertyTableSet() {
    mTables.Destroy();
    if (mpListener)
        mpListener->Release();
}

// @ 0x00de2f80
void cUIPropertyTableSet::Init() {
    mTables.LoadGroup1(0xb33d24db, 0x95eb6ed);
    mTables.LoadGroup0(0xb33d24db, 0x34419b24);
    mTables.LoadStringPairs(0xb33d24db, 0x7d5f207d);
    mTimer2.SetUnits(EA::Stopwatch::kUnitsMilliseconds);
    AutoRefCount<cPropertyList> props;
    cPropertyManager* pManager = SP::PropertyManager();
    props = (cPropertyList*)0;
    if (pManager->GetProperty(gScriptProperties, 0, &props.mpObject)) {
        sString16 name;
        if (SP::GetPropertyAsString16(props.mpObject, 0xb08e885a, &name.mpBegin))
            mnPadD4 = SP::FNV1_String16(name.mpBegin, 0x811c9dc5, 1);
        if (SP::GetPropertyAsString16(props.mpObject, 0xc3398948, &name.mpBegin))
            mnPadD8 = SP::FNV1_String16(name.mpBegin, 0x811c9dc5, 1);
        if (SP::GetPropertyAsString16(props.mpObject, 0x5ad618b8, &name.mpBegin))
            mnPadDC = SP::FNV1_String16(name.mpBegin, 0x811c9dc5, 1);
        if (SP::GetPropertyAsString16(props.mpObject, 0xd74f5e46, &name.mpBegin))
            mnPadE0 = SP::FNV1_String16(name.mpBegin, 0x811c9dc5, 1);
    }
    if (props.mpObject)
        props.mpObject->Release();
}
