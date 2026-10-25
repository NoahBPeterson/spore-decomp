// src/game/SPGonzago/SPUIRolloverCivCity.cpp -- migrated from slice(s) s00e2d6a0, s00e2cb00 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIRolloverCivCity.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cRelationshipManager.h"
#include "cSPUILayoutManager.h"
#include "cSPUIPropertyLayout.h"
#include "SP/cString.h"
#include <math.h>
#include "EA/Variant.h"
#include "SP/cGameNounManager.h"
#include "SP/cStarManager.h"

// ---- items of slice s00e2cb00 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
namespace SP {
class cString_s00e2_cb00 {
public:
    cString_s00e2_cb00();                                   // 0x006b5060
    cString_s00e2_cb00(const cString_s00e2_cb00& rhs);                 // 0x006b56f0
    ~cString_s00e2_cb00();                                  // 0x006b5240
    bool Load(uint32_t nTableId, uint32_t nKey, int32_t nFlags);  // 0x006b54b0

    uint8_t m_pad000[0x14];
};
}
namespace EA {
namespace UTFWin {
class IWindow_s00e2_cb00 {
public:
virtual void W00();
virtual void W04();
virtual void W08();
virtual void W0c();
    virtual int32_t GetParentWindow();           // +0x10

virtual void W14();
virtual void W18();
virtual void W1c();
virtual void W20();
virtual void W24();
virtual void W28();
virtual void W2c();
virtual void W30();
virtual void W34();
virtual void W38();
virtual void W3c();
virtual void W40();
virtual void W44();
virtual void W48();
virtual void W4c();
virtual void W50();
virtual void W54();
virtual void W58();
virtual void W5c();
virtual void W60();
virtual void W64();
virtual void W68();
virtual void W6c();
virtual void W70();
virtual void W74();
virtual void W78();
virtual void W7c();
virtual void W80();
virtual void W84();
virtual void W88();
virtual void W8c();
virtual void W90();
virtual void W94();
virtual void W98();
virtual void W9c();
virtual void Wa0();
virtual void Wa4();
virtual void Wa8();
virtual void Wac();
virtual void Wb0();
virtual void Wb4();
virtual void Wb8();
virtual void Wbc();
virtual void Wc0();
virtual void Wc4();
virtual void Wc8();
virtual void Wcc();
virtual void Wd0();
virtual void Wd4();
    virtual void AddChildWindow(IWindow_s00e2_cb00* pWindow);        // +0xd8
};
}
}
class cSPUILayoutManager_s00e2_cb00 {
public:
    EA::UTFWin::IWindow_s00e2_cb00* GetWorldMainWindow(uint32_t nKey);      // 0x00810620
};
cSPUILayoutManager_s00e2_cb00* __cdecl SPUIHelpers_GetLayoutManager(uint32_t nKey);  // 0x00805070
class cSPUIPropertyLayout_s00e2_cb00 {
public:
    bool Init();                                              // 0x00828250
    EA::UTFWin::IWindow_s00e2_cb00* GetRootWindow();                     // 0x00828100

    uint8_t m_pad000[0x78];
};
struct cEventVector {
    uint32_t* m_pBegin;                          // +0x00
    uint32_t* m_pEnd;                            // +0x04
    uint32_t* m_pCapacity;                       // +0x08
};
cEventVector* __cdecl GetRelationshipEvents();   // 0x00d026d0
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
class cStringMap {
public:
    struct Node {
        Node* m_pLeft;                           // +0x00
        Node* m_pRight;                          // +0x04
        void* m_pad008;                          // +0x08
        void* m_pad00c;                          // +0x0c
        uint32_t m_nKey;                         // +0x10
        SP::cString_s00e2_cb00 m_cValue;                    // +0x14
    };

    // the string slot for a key, inserted empty when the key is new
    SP::cString_s00e2_cb00& GetStringSlot(uint32_t nKey);                    // 0x00e2cb00

    // insert a node below the hint
    Node* Insert(Node* pHint, uint32_t nKey, const SP::cString_s00e2_cb00& cValue);  // 0x00e2c770

    Node* m_pRoot;                               // +0x00
    Node m_stHeader;                             // +0x04
    uint32_t m_nSize;                            // +0x10
};
class cStringVector {
public:
    SP::cString_s00e2_cb00& operator[](int32_t nIndex);     // 0x00e2ca70

    SP::cString_s00e2_cb00* m_pBegin;                       // +0x00
    SP::cString_s00e2_cb00* m_pEnd;                         // +0x04
    SP::cString_s00e2_cb00* m_pCapacity;                    // +0x08
};
class cSPUIRolloverCivRelationship : public cSPUIPropertyLayout_s00e2_cb00 {
public:
    bool Init();                                 // 0x00e2cba0

    // cSPUIPropertyLayout occupies +0x00 .. +0x77
    SP::cString_s00e2_cb00 mTooManyCitiesString;            // +0x78
    SP::cString_s00e2_cb00 mTooCloseToUsString;             // +0x8c
    SP::cString_s00e2_cb00 mNemesisString;                  // +0xa0
    SP::cString_s00e2_cb00 mNemesisTitleString;             // +0xb4
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
// ---- items of slice s00e2cb00 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void RelationshipIntrosortLoop(cAbsValueLess& less, uint32_t* pFirst, uint32_t* pLast, int32_t nDepthLimit);  // 0x00e2d520 (stays in the slice: not this object's)

// ---- items of slice s00e2d6a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char kGameModeA;   // 0x01654c02
    extern char kGameModeB; // 0x01654c04
    extern char kGameModeC; // 0x01654c05
extern wchar_t gEmptyW[2];   // 0x01667bac
struct Vector2 { float x, y; };
struct WStr {  // eastl::basic_string<wchar_t> (begin, end, capacity-end)
    wchar_t *b, *e, *cap;
    void RangeInitialize(const wchar_t* s);   // 0x00579a90
};
struct Variant {  // EA::Variant
    char data[0x10];
    unsigned short mFlags;
    unsigned short mTypeId;
    void Set(int type, int kind, void* p, int size, int copy);   // 0x0093dd80
    void Destruct(int);   // 0x0093db80
};
struct cString {
    char d[0x14];
    const wchar_t* GetText();   // 0x006b55c0
};
struct IWindow {
virtual void v00();
virtual void v04();
virtual void v08();
    virtual IWindow* QueryChild(unsigned id);                 // 0x0c
    virtual void v10();
    virtual void SetFlag14(int on);                           // 0x14
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual void SetColor(unsigned argb);                     // 0x28
virtual void v2c();
virtual void v30();
    virtual float* GetArea();                                 // 0x34
    virtual float* GetParentArea();                           // 0x38
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
    virtual void v5c();
    virtual void SetArea(const float* r);                     // 0x60
    virtual void SetOffset(float x, float y);                 // 0x64
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
    virtual void SetVisible(int a, int b);                    // 0x7c
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
    virtual void GetPos(Vector2* out, float x, float y);      // 0xc0
virtual void vc4();
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void ve8();
virtual void vec();
    virtual IWindow* FindWindow(unsigned id, int recurse);    // 0xf0
};
struct Civ {
    int Index();   // 0x00bf0f40
};
struct Sphere {
    bool Check();   // 0x00c75650
};
struct Owner { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void va();
virtual void vb();
virtual void vc();
virtual void vd();
virtual void ve();
virtual void vf();
virtual void v10();
virtual void v11();
virtual void v12();
               virtual int GetEmpireId(); };  // 0x4c
struct cGameNounManager {
    Civ* GetPlayerCivilization();       // 0x00b25fb0 SP::cGameNounManager::GetPlayerCivilization
    Owner* GetPlayerTribe();            // 0xbfc5f0
    Civ* FindCivById(int id);           // FUN_00b25f40
    Sphere* GetCurrentTerrainSphere();  // 0xf67d90
};
struct cStarManager {
    void* GetEmpireByID(int id);   // 0x00ba9370
};
struct cRelationshipManager {
    float CalculateRelationshipAbsolute(int a, int b, int c);
    float CalculateRelationshipPersonality(Civ* a, Civ* b);
    float Relation2(Civ* a, Civ* b);       // FUN_00d007f0
    float CalculateRelationshipCityProximity(Civ* a, Civ* b);
    float Relation4(Civ* a, Civ* b);       // FUN_00d00b40
    int   GetLevel(int a, int b, int c);   // FUN_00d00a70
    void  GetThresholds(float* a, float* b, float* c, float* d);  // FUN_00d00750
};
const void* GetCurrentGameMode();
cGameNounManager* NounManager();
cStarManager* StarManager();   // 0x00b3d2a0
cRelationshipManager* RelationshipManager();
int GetPlayerEmpireOrMinus1();
struct Events { unsigned *b, *e, *c; char alloc; };
Events* GetRelationshipEvents_s00e2_d6a0();   // 0x00d026d0
struct U32Vec {
    unsigned *b, *e, *c;
    void Init(int n, void* alloc);      // FUN_00b93c60
    void Truncate(int n);               // FUN_00b98ea0
};
void* CopyBytes(void* dst, const void* src, unsigned bytes);   // eastl DoInsertValue (uninitialized copy)
struct RelMap {   // 28-byte scored-event map / comparator
    unsigned a, b, c;
    void* root;
    unsigned d, e, f;
    RelMap() {}
    RelMap(const RelMap& o) { CopyFrom(&o); }
    ~RelMap() { DoNukeSubtree(root); }
    void Build(int emp, int myEmp);     // FUN_00e2cce0
    void CopyFrom(const RelMap* o);     // FUN_00d01a40
    float* Find(unsigned* key);         // FUN_00be0790
    void DoNukeSubtree(void* n);
};
void SortEvents(unsigned* b, unsigned* e, RelMap cmp);        // FUN_00e2d5f0
void* op_new(unsigned n, const char* name, int a, unsigned b, const char* file, int line);   // 0x00f473a0
void op_delete(void* p);   // 0x00f47380
void SetNumberString(long long v, wchar_t* buf, int n);   // 0x00881ae0
void FUN_00808b20(IWindow* a, IWindow* b, int c);
class cSPUIPropertyLayout_s00e2_d6a0 { public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void Vf1c();
    virtual void Vf20();
    IWindow* GetRootWindow();  // 0x00828100 (cSPUIPropertyLayout::GetRootWindow)
    char pad[0x74];
};
class cSPUIRolloverCivRelationship_s00e2_d6a0 : public cSPUIPropertyLayout_s00e2_d6a0 { public:
    cString mTooManyCities;       // +0x78
    cString mTooClose;            // +0x8c
    cString mNemesis;             // +0xa0
    cString mTerrain;             // +0xb4
    cString* mPersonality;        // +0xc8
    char pad2[0x10];
    char mStringMap;              // +0xdc (map<uint, cString>)
    char pad3[0x1b];
    int mMaxRows;                 // +0xf8

    cString* LookupString(unsigned* key);   // FUN_00e2cb00 on +0xdc
    void SetProp(unsigned id, Variant* v, int a, int b);   // FUN_00828c30
    void ShowRelationshipRollover(IWindow* anchor, int empireId, int anchorMode);  // 0x00e2d6a0 (cSPUIRolloverCivRelationship::ShowRelationshipRollover)
};
void SetValueTextForRollover(cSPUIRolloverCivRelationship_s00e2_d6a0* t, unsigned id, float v);   // 0x00e2c590
static const char kEastlFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static inline void MakeWStr(WStr& s, const wchar_t* p) {
    s.b = s.e = s.cap = 0;
    const wchar_t* q = p;
    while (*q) ++q;
    unsigned n = (unsigned)(q - p);
    unsigned sz = n + 1;
    wchar_t* buf;
    if (sz > 1) {
        buf = (wchar_t*)op_new(sz * 2, "Simulator", 0, 0, kEastlFile, 0xd1);
        s.b = buf; s.cap = (wchar_t*)((char*)buf + sz * 2);
    } else {
        buf = gEmptyW; s.b = gEmptyW; s.cap = gEmptyW + 1;
    }
    s.e = buf;
    CopyBytes(buf, p, n * 2);
    s.e = buf + n;
    *s.e = 0;
}
static __forceinline void SendText(cSPUIRolloverCivRelationship_s00e2_d6a0* t, int row, WStr& s, float value) {
    Variant v;
    v.mFlags = 0; v.mTypeId = 0;
    v.Set(0x13, 9, &s, 0x10, 1);
    t->SetProp(row + 0x4d186b0, &v, 1, 0);
    if (v.mFlags & 4) v.Destruct(0);
    if ((int)(((char*)s.cap - (char*)s.b) & ~1) > 2 && s.b) op_delete(s.b);
    SetValueTextForRollover(t, row + 0x4d18700, value);
}
static __forceinline void AddRow(cSPUIRolloverCivRelationship_s00e2_d6a0* t, int row, const wchar_t* text, float value) {
    WStr s; s.b = s.e = s.cap = 0;
    s.RangeInitialize(text);
    SendText(t, row, s, value);
}
// ---- items of slice s00e2d6a0 end

// @ 0x00e2cb00
SP::cString_s00e2_cb00& cStringMap::GetStringSlot(uint32_t nKey)
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
        SP::cString_s00e2_cb00 cEmpty;
        Node* pInserted = Insert(pParent, nKey, cEmpty);
        if (pInserted != nullptr)
            pParent = pInserted;
    }
    return pParent->m_cValue;
}

// @ 0x00e2cba0
bool cSPUIRolloverCivRelationship::Init()
{
    bool bLayoutReady = false;
    if (cSPUIPropertyLayout_s00e2_cb00::Init()) {
        EA::UTFWin::IWindow_s00e2_cb00* pRootWindow = GetRootWindow();
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
    SP::cString_s00e2_cb00* pPersonality = m_vPersonality.m_pBegin;
    for (int32_t i = 0; i < 3; ++i)
        pPersonality[i].Load(kStringTable, kPersonalityKeys[i], 0);

    cEventVector* pEvents = GetRelationshipEvents();
    for (uint32_t* pEvent = pEvents->m_pBegin; pEvent != pEvents->m_pEnd; ++pEvent)
        m_mRelationshipStrings.GetStringSlot(*pEvent).Load(kStringTable, *pEvent, 0);

    m_nRelationshipCount = CountRelationshipRows(this);
    return bLayoutReady;
}

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
uint32_t* RelationshipMedianOfThree(cAbsValueLess& less, uint32_t* pFirst, uint32_t* pMiddle, uint32_t* pLast)
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
uint32_t* RelationshipPartition(cAbsValueLess& less, uint32_t* pFirst, uint32_t* pLast, uint32_t nPivot)
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
void RelationshipPushHeap(cAbsValueLess& less, uint32_t* pFirst, int32_t nHole, uint32_t nValue)
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
void RelationshipAdjustHeap(cAbsValueLess& less, uint32_t* pFirst, int32_t nHole, int32_t nLength, uint32_t nValue)
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

// @ 0x00e2d6a0
void cSPUIRolloverCivRelationship_s00e2_d6a0::ShowRelationshipRollover(IWindow* anchor, int empireId, int anchorMode)
{
    const void* mode = GetCurrentGameMode();
    Civ* playerCiv = 0;
    if (mode == &kGameModeB) playerCiv = NounManager()->GetPlayerCivilization();
    Civ* otherCiv = 0;
    if (!StarManager()->GetEmpireByID(empireId)) otherCiv = NounManager()->FindCivById(empireId);

    Vector2 anchorPos;
    anchor->GetPos(&anchorPos, 0.0f, 0.0f);
    Vf1c();
    IWindow* root = GetRootWindow();
    int rows = 0;

    int myEmpire;
    cGameNounManager* nm = NounManager();
    if (mode == &kGameModeA) myEmpire = nm->GetPlayerTribe()->GetEmpireId();
    else myEmpire = GetPlayerEmpireOrMinus1();

    float rel;
    if (empireId == myEmpire) rel = 10.0f;
    else rel = RelationshipManager()->CalculateRelationshipAbsolute(empireId, myEmpire, 0);

    int n = 0;
    if (mode == &kGameModeB) {
        if (otherCiv && otherCiv != playerCiv) {
            float f = RelationshipManager()->CalculateRelationshipPersonality(otherCiv, playerCiv);
            if (f >= 0.1f || f <= -0.1f) n = 1;
            f = RelationshipManager()->Relation2(otherCiv, playerCiv);
            if (f >= 0.1f || f <= -0.1f) n++;
            f = RelationshipManager()->CalculateRelationshipCityProximity(otherCiv, playerCiv);
            if (f >= 0.1f || f <= -0.1f) n++;
            f = RelationshipManager()->Relation4(otherCiv, playerCiv);
            if (f >= 0.1f || f <= -0.1f) n++;
        }
    } else if (mode == &kGameModeC) {
        if (empireId != myEmpire && rel < 0.0f) {
            if (NounManager()->GetCurrentTerrainSphere()->Check()) n = 1;
        }
    }

    Events* ev = GetRelationshipEvents_s00e2_d6a0();
    U32Vec tmp;
    tmp.Init((int)(ev->e - ev->b), &ev->alloc);
    unsigned bytes = (unsigned)((char*)ev->e - (char*)ev->b);
    void* r = CopyBytes(tmp.b, ev->b, bytes);
    tmp.e = (unsigned*)r + (bytes >> 2);

    RelMap scores;
    scores.Build(empireId, myEmpire);
    {
        RelMap cmp(scores);
        SortEvents(tmp.b, tmp.e, cmp);
    }
    int limit = mMaxRows - n;
    if ((int)(tmp.e - tmp.b) > limit) tmp.Truncate(limit);

    int pass = 0;
    do {
        if (mode == &kGameModeB && otherCiv && otherCiv != playerCiv) {
            float f = RelationshipManager()->CalculateRelationshipPersonality(otherCiv, playerCiv);
            if (pass == 0 ? (f >= 0.1f) : (f <= -0.1f)) {
                AddRow(this, rows, mPersonality[playerCiv->Index()].GetText(), f);
                rows++;
            }
            f = RelationshipManager()->Relation2(otherCiv, playerCiv);
            if (pass == 0 ? (f >= 0.1f) : (f <= -0.1f)) {
                AddRow(this, rows, mTooManyCities.GetText(), f);
                rows++;
            }
            f = RelationshipManager()->CalculateRelationshipCityProximity(otherCiv, playerCiv);
            if (pass == 0 ? (f >= 0.1f) : (f <= -0.1f)) {
                AddRow(this, rows, mTooClose.GetText(), f);
                rows++;
            }
            f = RelationshipManager()->Relation4(otherCiv, playerCiv);
            if (pass == 0 ? (f >= 0.1f) : (f <= -0.1f)) {
                AddRow(this, rows, mNemesis.GetText(), f);
                rows++;
            }
        }
        if (pass == 0 && mode == &kGameModeC) {
            if (empireId == myEmpire) goto next_pass;
            if (rel < 0.0f && NounManager()->GetCurrentTerrainSphere()->Check()) {
                AddRow(this, rows, mTerrain.GetText(), -rel);
                rows++;
            }
        }
        if (empireId == myEmpire) goto next_pass;
        for (unsigned* it = tmp.b; it != tmp.e; ++it) {
            unsigned id = *it;
            float f = *scores.Find(&id);
            if (pass == 0 ? (f >= 0.1f) : (f <= -0.1f)) {
                id = *it;
                WStr s;
                MakeWStr(s, LookupString(&id)->GetText());
                SendText(this, rows, s, f);
                rows++;
            }
        }
    next_pass:
        pass++;
    } while (pass < 2);

    wchar_t numbuf[64];
    SetNumberString((long long)(rel * 10.0f), numbuf, 0x40);
    {
        WStr s;
        MakeWStr(s, numbuf);
        Variant v;
        v.mFlags = 0; v.mTypeId = 0;
        v.Set(0x13, 9, &s, 0x10, 1);
        SetProp(0x4d3f26b, &v, 1, 0);
        if (v.mFlags & 4) v.Destruct(0);
        if ((int)(((char*)s.cap - (char*)s.b) & ~1) > 2 && s.b) op_delete(s.b);
    }

    IWindow* title = root->FindWindow(0x4d3f26b, 1);
    IWindow* colorObj = 0;
    if (title) colorObj = (IWindow*)((IWindow*)title)->QueryChild(0xf15f4bd);

    int level;
    if (empireId == myEmpire) level = 4;
    else level = RelationshipManager()->GetLevel(empireId, myEmpire, 1);

    float t0 = 0, t1 = 0, t2 = 0, t3 = 0;
    float lo = 0, range = 0, base = 0;
    RelationshipManager()->GetThresholds(&t0, &t1, &t2, &t3);
    t0 += 10.0f; t1 += 10.0f; t2 += 10.0f; t3 += 10.0f;
    switch (level) {
    case 4: colorObj->SetColor(0xff00ff00); base = 4.0f; lo = t3; range = 20.0f - t3; break;
    case 3: colorObj->SetColor(0xff77e700); base = 3.0f; lo = t2; range = t3 - t2; break;
    case 2: colorObj->SetColor(0xffeed000); base = 2.0f; lo = t1; range = t2 - t1; break;
    case 1: colorObj->SetColor(0xfff66800); base = 1.0f; lo = t0; range = t1 - t0; break;
    case 0: colorObj->SetColor(0xffff0000); base = 0.0f; lo = 0.0f; range = t0; break;
    }

    for (unsigned i = 0; i < 5; i++) {
        IWindow* w = root->FindWindow(i + 0x4b47d00, 1);
        IWindow* c = w->QueryChild(0x105a93d);
        if (c) c->SetFlag14(1);
    }
    IWindow* sel = root->FindWindow(level + 0x4b47d00, 1);
    sel->SetVisible(1, 1);
    sel->QueryChild(0x105a93d)->SetFlag14(0);

    float pos = ((rel + 10.0f - lo) / range + base) * 0.2f;
    float lim = 1.0f;
    if (pos < 0.0f) pos = 0.0f;
    if (pos > lim) pos = lim;

    IWindow* bar = root->FindWindow(0x66b72e6, 1);
    bar->SetOffset(pos * 126.0f + 8.0f, 25.0f);

    Vf20();
    float* a = root->GetArea();
    float rect[4];
    rect[0] = a[0];
    rect[1] = a[1];
    rect[2] = a[2];
    rect[3] = (float)(rows * 0x15 + 0x3b) + a[1];
    root->SetArea(rect);

    IWindow* target;
    if (anchorMode == 0) {
        FUN_00808b20(anchor, root, 0);
        target = root;
    } else {
        float x, y;
        if (anchorMode == 1) {
            float* pr = anchor->GetParentArea();
            x = anchorPos.x;
            y = (pr[3] - pr[1]) + anchorPos.y;
        } else {
            float* pr = anchor->GetParentArea();
            x = (pr[2] - pr[0]) + anchorPos.x;
            y = anchorPos.y;
        }
        target = root;
        target->SetOffset(x, y);
    }
    target->SetVisible(1, 1);
}
