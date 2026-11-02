// src/game/SPGonzago/SPUIRolloverCivCity.cpp -- migrated from slice(s) s00e2b9d0, s00e29c80, s00e2d6a0, s00e2cb00 by tools/migrate/rewrite.py
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
#include "SP/cPropertyList.h"
#include "cSPUIAnimationSequence.h"
#include "SP/cSPUINewProgressBar.h"
#include "SP/cTribe.h"

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
class cRelationshipManager_s00e2_cb00 {
public:
    float CalculateRelationshipEvent(uint32_t nFrom, uint32_t nTo, uint32_t nEvent);  // 0x00d03d70
};
cRelationshipManager_s00e2_cb00* __stdcall RelationshipManager_s00e2_cb00();       // 0x00b3d2c0
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

// ---- items of slice s00e29c80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float gSPUIRowPad;                                        // 0x1481654 (2.0f)
extern const float gSPUIRowHeight;                                     // 0x14816ec (88.0f)
extern char gVftblCursorAttachment00[];                                // 0x01481694
extern char gVftblCursorAttachment04[];                                // 0x01481684
extern char gVftblCursorAttachment78[];                                // 0x01481668
struct IRefCount {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
struct IWindow_s00e2_9c80;
struct IWindow_s00e2_9c80 : IRefCount {
    virtual void  P02();
    virtual IWindow_s00e2_9c80*  FindChildByID(uint32_t id);        // +0x0c
    virtual IWindow_s00e2_9c80*  GetParent();                       // +0x10
    virtual void  SetFlag(int v);                        // +0x14
    virtual void  P06();
    virtual void  P07();
    virtual void  P08();
    virtual void  P09();
    virtual void  P0a();
    virtual void  P0b();
    virtual void  P0c();
    virtual const float*  GetAreaRaw();                  // +0x34
    virtual const float*  GetArea();                     // +0x38 (left, top, right, bottom)
    virtual void  P0f();
    virtual void  P10();
    virtual void  P11();
    virtual void  P12();
    virtual void  P13();
    virtual void  P14();
    virtual void  P15();
    virtual void  P16();
    virtual void  SetShadeColor(uint32_t color);         // +0x5c
    virtual void  SetAreaA(const float* area);            // +0x60
    virtual void  SetPosition(float x, float y);          // +0x64
    virtual void  SetSize(float width, float height);     // +0x68
    virtual void  SetAreaB(const float* area);            // +0x6c
    virtual void  P1c();
    virtual void  P1d();
    virtual void  P1e();
    virtual void  SetVisible(int what, uint8_t on);       // +0x7c (the flag is passed zero-extended)
    virtual void  SetCaption(const wchar_t* text);        // +0x80
virtual void  P20();
virtual void  P21();
virtual void  P22();
virtual void  P23();
virtual void  P24();
virtual void  P25();
virtual void  P26();
virtual void  P27();
virtual void  P28();
virtual void  P29();
virtual void  P2a();
virtual void  P2b();
virtual void  P2c();
virtual void  P2d();
virtual void  P2e();
virtual void  P2f();
virtual void  P30();
virtual void  P31();
virtual void  P32();
virtual void  P33();
    virtual void  P34();                                  // +0xd4
    virtual void  AddChild(IWindow_s00e2_9c80* child);               // +0xd8
    virtual void  RemoveChild(IWindow_s00e2_9c80* child);            // +0xdc
virtual void  P38();
virtual void  P39();
virtual void  P3a();
virtual void  P3b();
    virtual IWindow_s00e2_9c80*  FindWindowByID2(uint32_t id, bool recursive);   // +0xf0
};
class cSPUILayout_s00e2_9c80 { public:
    IWindow_s00e2_9c80*  FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0
    uint8_t mData[0x28];                                            // sizeof == 0x28 (never read here)
};
struct AutoRefCount;
struct cProperty;
struct IPropertyManager {
virtual void  M00();
virtual void  M04();
virtual void  M08();
virtual void  M0c();
virtual void  M10();
virtual void  M14();
virtual void  M18();
virtual void  M1c();
virtual void  M20();
virtual void  M24();
    virtual void  M28();
    virtual void  AddProperty(const void* owner, uint32_t id, IRefCount** out);   // +0x2c
    virtual bool  GetPropertyList(uint32_t id, IRefCount** out);                  // +0x30
};
IPropertyManager* PropertyManager();                                   // 0x67de30
struct cProperty {
    uint8_t  mPad00[0x12];                                             // +0x00
    uint16_t mType;                                                    // +0x12
    int* GetInt();                                                     // 0x41e990
};
struct cPropertyList : IRefCount {
virtual void  L08();
virtual void  L0c();
virtual void  L10();
virtual void  L14();
virtual void  L18();
virtual void  L1c();
    virtual void  L20();
    virtual bool  GetProperty(uint32_t id, cProperty** out);  // +0x24
};
struct AutoRefCount {
    IRefCount* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    void Reset() { if (mpObject) { IRefCount* p = mpObject; mpObject = 0; p->Release(); } }
};
struct cSPUILayoutManager_s00e2_9c80 {
    IWindow_s00e2_9c80* GetWorldMainWindow();                                     // 0x810620
};
namespace SPUIHelpers {
    cSPUILayoutManager_s00e2_9c80* __stdcall GetLayoutManager(uint32_t arg);      // 0x805070
}
struct RBNode {
    uint8_t  mPad00[0x1c];                                             // +0x00
    uint32_t mField1c;                                                 // +0x1c
    uint32_t mField20;                                                 // +0x20
};
RBNode* __cdecl RBTreeIncrement(RBNode* node);                         // 0x921580
struct RBTree {
    void*   mHeader;                                                   // +0x78
    RBNode* mEndNode;                                                  // +0x7c
    RBNode* mRoot;                                                     // +0x80
    void  find(RBNode** out, const uint32_t* key);            // 0xe5c780
};
class cSPUIPropertyLayout_s00e2_9c80 {
public:
    virtual void  P00();                                      // +0x00 (dtor)
    virtual void  P04();
    virtual void  P08();
    virtual void  V0c();
    virtual void  V10();
    virtual void  V14();
    virtual void  V18();
    virtual void  V1c();
    virtual void  V20();
    virtual void  HideRollover();                             // +0x24

    bool Init();                                                       // 0x828250
    IWindow_s00e2_9c80* GetRootWindow();                                          // 0x828100
    uint32_t GetEventMask();                                           // 0x828070
    bool func24h();                                                    // 0x828be0

    int mRefCount;                                                     // +0x04
    int mField08;                                                      // +0x08
    cSPUILayout_s00e2_9c80 mLayout;                                               // +0x0c (0x28 bytes)
    uint8_t mPad34[0x10];                                              // +0x34
    bool mFlag44;                                                      // +0x44
    uint8_t mPad45[0x33];                                              // +0x45
    RBTree mTree;                                                      // +0x78
    uint8_t mPad84[0x10];                                              // +0x84
    uint32_t mCounter94;                                               // +0x94
    uint32_t mValue98;                                                 // +0x98
    uint32_t mKey9c;                                                   // +0x9c
    uint32_t mValueA0;                                                 // +0xa0
    uint8_t mFlagA4;                                                   // +0xa4
    uint8_t mPadA5;                                                    // +0xa5
    uint8_t mFlagA6;                                                   // +0xa6
    uint8_t mPadA7;                                                    // +0xa7
    uint32_t mFieldA8;                                                 // +0xa8
};
struct cSPUIRolloverCivCityVehicle : cSPUIPropertyLayout_s00e2_9c80 {
    bool Init(uint32_t arg);                                           // 0x00e2a550
};
struct cSPUICursorLayoutWidget : cSPUIPropertyLayout_s00e2_9c80 {
    void SetShown(bool shown);                                         // 0x00e2a600
};
struct cSPUIRolloverRelationship : cSPUIPropertyLayout_s00e2_9c80 {
    void HideRelationshipRollover();                                   // 0x00e2a6c0
};
struct cSPUIRolloverVehicleFlags : cSPUIPropertyLayout_s00e2_9c80 {
    uint32_t GetEventFlags();                                          // 0x00e2a690
};
struct cSPUIRolloverCityFlags : cSPUIPropertyLayout_s00e2_9c80 {
    uint32_t GetEventFlags();                                          // 0x00e2a6a0
};
struct cSPUIRolloverPropertyFlags : cSPUIPropertyLayout_s00e2_9c80 {
    uint32_t GetEventFlags();                                          // 0x00e2a5f0
};
struct cSPUIRolloverCivCityHall : cSPUIPropertyLayout_s00e2_9c80 {
    void SetSpecialtyIcon(uint32_t icon);                              // 0x00e2a7b0
    void calculate_layout();                                           // 0x00e2a920
    bool SetPrimaryPopulationGroupId(uint32_t id);                     // 0x00e2ab10
    void UpdatePlacement();                                            // 0x00e2abc0
    void read_properties();                                            // 0x00e2acc0
};
namespace UI {
class CursorAttachment : public cSPUIPropertyLayout_s00e2_9c80 {
public:
    void Dispose();                                                    // 0x00e2a5b0
};  // namespace UI
}
struct cSPUIRolloverCivCityVehicleCtor {
    void* mpVftable00;                                                 // +0x00
    void* mpVftable04;                                                 // +0x04
    uint8_t mPad08[0x70];                                              // +0x08
    void* mpVftable78;                                                 // +0x78

    void BaseConstruct();                                              // 0x801280 (cSPUICursorAttachmentLayout ctor)
    void  SetKey(const wchar_t* key, uint32_t id);            // 0x827fc0
    void  SetRootWindowId(uint32_t id);                       // 0xc87bc0
    cSPUIRolloverCivCityVehicleCtor* Initialize();                     // 0x00e2a640
};
// ---- items of slice s00e29c80 end

// ---- items of slice s00e2b9d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PV virtual void CAT_(_pv, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
void __cdecl ea_delete(void* p);                           // 0x00f47380
struct cString_s00e2_b9d0   // SP::cString, 0x14 bytes
{
    uint32_t d[5];
    cString_s00e2_b9d0();                                                                      // 0x006b5060
    cString_s00e2_b9d0(uint32_t tableID, uint32_t instanceID, const wchar_t* defaultText);   // 0x006b5770 (ret 0xc)
    ~cString_s00e2_b9d0();                                                                    // 0x006b5240
    const wchar_t* GetText();                                                      // 0x006b55c0
};
namespace civroll {
void* ea_operator_new(uint32_t size, const char* name, int flags, int align, const char* file, int line);  // 0x00f473a0
}
namespace civroll {
cString_s00e2_b9d0* F_e2a6f0(cString_s00e2_b9d0* a, cString_s00e2_b9d0* b, cString_s00e2_b9d0* c);                                  // 0x00e2a6f0
}
namespace civroll {
void     F_e2aad0(cString_s00e2_b9d0** out, cString_s00e2_b9d0* first, cString_s00e2_b9d0* last, cString_s00e2_b9d0* init, cString_s00e2_b9d0* extra);  // 0x00e2aad0
}
namespace civroll {
void     F_e2aaa0(cString_s00e2_b9d0* first, cString_s00e2_b9d0* last, cString_s00e2_b9d0* src);                         // 0x00e2aaa0
}
namespace civroll {
void     F_e2ad70(cString_s00e2_b9d0* dst, uint32_t n, const cString_s00e2_b9d0* src);                        // 0x00e2ad70
}
namespace civroll {
cString_s00e2_b9d0* F_aed430(cString_s00e2_b9d0* first, cString_s00e2_b9d0* last, cString_s00e2_b9d0* dst);                         // 0x00aed430
}
namespace civroll {
cString_s00e2_b9d0* F_aed510(cString_s00e2_b9d0* first, cString_s00e2_b9d0* last, cString_s00e2_b9d0* dst);                         // 0x00aed510
}
namespace civroll {
cString_s00e2_b9d0* F_aed470(cString_s00e2_b9d0* first, cString_s00e2_b9d0* last, cString_s00e2_b9d0* dst);                         // 0x00aed470
}
namespace civroll {
struct cStringVec
{
    cString_s00e2_b9d0* mpBegin;      // +0x00
    cString_s00e2_b9d0* mpEnd;        // +0x04
    cString_s00e2_b9d0* mpCapacity;   // +0x08
    ~cStringVec()
    {
        cString_s00e2_b9d0* end = mpEnd;
        for (cString_s00e2_b9d0* p = mpBegin; p < end; p = (cString_s00e2_b9d0*)((char*)p + 0x14))
            p->~cString_s00e2_b9d0();
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            ea_delete(mpBegin);
    }
    cString_s00e2_b9d0* Erase(cString_s00e2_b9d0* first, cString_s00e2_b9d0* last);                    // 0x00e2c290
    void     Insert(cString_s00e2_b9d0* pos, uint32_t n, const cString_s00e2_b9d0* value);  // 0x00e2c2f0
    void     Index(uint32_t i);                                       // 0x00e2ca70
};
}
namespace civroll {
struct Variant_s00e2_b9d0;
}
namespace civroll {
struct CPL
{
    void*  mpVftable;      // +0x00
    void*  mpVftable2;     // +0x04
    char   pad008[0x3c];   // +0x08
    bool   mFlag44;        // +0x44
    char   pad045[0x33];   // +0x45..0x78
    CPL();                                                      // 0x008286d0
    ~CPL();                                                     // 0x00828670
    bool   Init();                                              // 0x00828250
    void*  GetRootWindow();                                     // 0x00828100
    void   SetKey(const wchar_t* key, uint32_t flags);          // 0x00827fc0 (ret 8)
    void   SetRootWindowId(uint32_t id);                        // 0x00c87bc0 (ret 4)
    bool   func24h();                                           // 0x00828be0
    void   SetProp(uint32_t id, Variant_s00e2_b9d0* v, int a, int b);      // 0x00828c30 (ret 0x10)
};
}
namespace civroll {
struct cSPUIRolloverCivCityVehicle_s00e2_b9d0 : CPL
{
    void SetPurposeIcon(uint32_t icon);                          // 0x00e2b4f0
    bool Initialize();                                           // @ 0x00e2c1e0
};
}
namespace civroll {
struct FeedbackEvent { int mField00, mField04, mField08, mField0c; };
}
namespace civroll {
struct FeedbackNode
{
    void*           mpLeft;    // +0x00
    void*           mpRight;   // +0x04
    void*           mpParent;  // +0x08
    uint32_t        mColor;    // +0x0c
    uint32_t        mKey;      // +0x10
    FeedbackEvent   mValue;    // +0x14
};
}
namespace civroll {
struct IdMap
{
    void*           mpField00;   // +0x00
    FeedbackNode*   mpAnchor;    // +0x04 (sentinel node: right/parent/color follow)
    FeedbackNode*   mpAnchorEnd; // +0x08
    FeedbackNode*   mpRoot;      // +0x0c
    uint32_t        mnColor;     // +0x10
    uint32_t        mnSize;      // +0x14
    uint32_t        mField18;    // +0x18
    void Find(FeedbackNode** out, const uint32_t* key);                       // 0x00e5c780
    void Insert(FeedbackNode** out, const FeedbackEvent* value, uint32_t key); // 0x00e2c200
};
}
namespace civroll {
class cSPUIRolloverFeedbackGrid
{
public:
    void*           mpVftable;   // +0x00
    char            pad004[0x74];// +0x04
    IdMap           mMap;        // +0x78
    int             mCounter94;  // +0x94
    int             mField98;    // +0x98
    int             mField9c;    // +0x9c
    int             mPerRowA0;   // +0xa0
    bool  FUN_00e2c840(uint32_t key, int a, int b);   // 0x00e2c840
    void  FUN_00e2ab10(uint32_t key);                 // 0x00e2ab10
};
}
namespace civroll {
struct RBTree_s00e2_b9d0
{
    void*     mpField00;   // +0x00
    void*     mpAnchor;    // +0x04
    void*     mpAnchorEnd; // +0x08
    void*     mpRoot;      // +0x0c
    union { uint32_t mnColor; uint8_t mbColor; };   // +0x10
    uint32_t  mnSize;      // +0x14
    uint32_t  mField18;    // +0x18
    uint32_t  mFieldF8;    // +0x1c
    void DoNukeSubtree(void* node);                     // 0x00e2b680 (this = tree)
};
}
namespace civroll {
struct cSPUIRolloverCivRelationship_s00e2_b9d0 : CPL
{
    cString_s00e2_b9d0      mString78;    // +0x78
    cString_s00e2_b9d0      mString8c;    // +0x8c
    cString_s00e2_b9d0      mStringA0;    // +0xa0
    cString_s00e2_b9d0      mStringB4;    // +0xb4
    cStringVec   mVecC8;       // +0xc8
    char         padD4[8];     // +0xd4..0xdb
    RBTree_s00e2_b9d0       mMapDC;       // +0xdc

    cSPUIRolloverCivRelationship_s00e2_b9d0();
    ~cSPUIRolloverCivRelationship_s00e2_b9d0();
    void Shutdown();  // 0x00e2c9f0 (civroll::cSPUIRolloverCivRelationship::Shutdown)
};
}
namespace civroll {
class IWindowEx
{
public:
    PV2 PV                                              // slots 0-2
    virtual void* GetChildByID(uint32_t id);            // slot 3  (+0x0c)
    PV4 PV2                                             // slots 4-9
    virtual void  SetColor(uint32_t color);             // slot 10 (+0x28)
    PV8 PV4                                             // slots 11-22
    virtual void  SetShade(uint32_t color);             // slot 23 (+0x5c)
    PV4 PV2 PV                                          // slots 24-30
    virtual void  SetFlag(int flag, bool on);           // slot 31 (+0x7c)
    PV8 PV8 PV4 PV2 PV                                  // slots 32-54
    virtual void  DisposeWindow(void* w);               // slot 55 (+0xdc)
    PV4                                                 // slots 56-59
    virtual IWindowEx* FindWindow(uint32_t id, int recurse);   // slot 60 (+0xf0)
};
}
namespace civroll {
struct cSPUILayoutManager
{
    void* GetWorldMainWindow();                 // 0x00810620
};
}
namespace civroll {
cSPUILayoutManager* __stdcall SPUIHelpers_GetLayoutManager_s00e2_b9d0(uint32_t id);   // 0x00805070
}
namespace civroll {
struct WStr_s00e2_b9d0
{
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    void RangeInitialize(const wchar_t* s);                  // 0x00579a90 (this = string)
    void assign(const wchar_t* first, const wchar_t* last);  // 0x00423650
};
}
namespace civroll {
struct Variant_s00e2_b9d0
{
    char     mData[0x10];   // +0x00
    uint16_t mFlags;        // +0x10
    uint16_t mTypeId;       // +0x12
    void Set(uint32_t type, uint32_t kind, void* p, uint32_t size, uint32_t copy);  // 0x0093dd80
    void Destruct(int a);                                                          // 0x0093db80
};
}
namespace civroll {
void   __cdecl SetNumberString(long long v, wchar_t* buffer, int n);   // 0x00881ae0
}
namespace civroll {
WStr_s00e2_b9d0*  eastl_operator_plus(WStr_s00e2_b9d0* out, const wchar_t* prefix, WStr_s00e2_b9d0* self);  // 0x006309e0
}
namespace civroll {
extern "C" double __cdecl fabs(double);
}
namespace civroll {
static __forceinline void WStr_Free(WStr_s00e2_b9d0& s)
{
    if (((int)((char*)s.mpCapacity - (char*)s.mpBegin) & ~1) > 2 && s.mpBegin)
        ea_delete(s.mpBegin);
}
}
namespace civroll {
extern const wchar_t gwPlus[];    // 0x01419de8
}
namespace civroll {
extern const wchar_t gwMinus[];   // 0x013faf54
}
// ---- items of slice s00e2b9d0 end

// @ 0x00e2a550
bool cSPUIRolloverCivCityVehicle::Init(uint32_t arg)
{
    mFieldA8 = 0;
    if (cSPUIPropertyLayout_s00e2_9c80::Init()) {
        IWindow_s00e2_9c80* root = GetRootWindow();
        if (!root->GetParent()) {
            cSPUILayoutManager_s00e2_9c80* manager = SPUIHelpers::GetLayoutManager(arg);
            IWindow_s00e2_9c80* main = manager->GetWorldMainWindow();
            main->AddChild(root);
        }
        return true;
    }
    return false;
}

// @ 0x00e2a5b0
void UI::CursorAttachment::Dispose()
{
    if (mFlag44) {
        IWindow_s00e2_9c80* root = GetRootWindow();
        IWindow_s00e2_9c80* parent = root->GetParent();
        IWindow_s00e2_9c80* root2 = GetRootWindow();
        parent->RemoveChild(root2);
    }
    func24h();
}

// @ 0x00e2a5f0
uint32_t cSPUIRolloverPropertyFlags::GetEventFlags()
{
    return GetEventMask() | 0x48c;
}

// @ 0x00e2a600
void cSPUICursorLayoutWidget::SetShown(bool shown)
{
    mFlagA4 = shown;
    IWindow_s00e2_9c80* window = mLayout.FindWindowByID(0x46adf86, true);
    window->SetVisible(1, mFlagA4);
}

// @ 0x00e2a640
cSPUIRolloverCivCityVehicleCtor* cSPUIRolloverCivCityVehicleCtor::Initialize()
{
    BaseConstruct();
    mpVftable00 = gVftblCursorAttachment00;
    mpVftable04 = gVftblCursorAttachment04;
    mpVftable78 = gVftblCursorAttachment78;
    SetKey(L"RolloverCivCityVehicle", 0x40464100);
    SetRootWindowId(0x199a7de);
    return this;
}

// @ 0x00e2a690
uint32_t cSPUIRolloverVehicleFlags::GetEventFlags()
{
    return GetEventMask() | 0x400;
}

// @ 0x00e2a6a0
uint32_t cSPUIRolloverCityFlags::GetEventFlags()
{
    return GetEventMask() | 0x40c;
}

// @ 0x00e2a6c0
void cSPUIRolloverRelationship::HideRelationshipRollover()
{
    if (mFlag44) {
        IWindow_s00e2_9c80* root = GetRootWindow();
        root->SetVisible(1, false);
        HideRollover();
    }
}

// @ 0x00e2a760
int __cdecl CountRolloverRows(cSPUIPropertyLayout_s00e2_9c80* self)
{
    int i = 0;
next:
    {
        IWindow_s00e2_9c80* root = self->GetRootWindow();
        IWindow_s00e2_9c80* row = root->FindWindowByID2((uint32_t)(i + 0x4d18700), true);
        if (!row)
            return i;
        if (!row->FindChildByID(0xf15f4bd))
            return i;
        i++;
    }
    goto next;
}

// @ 0x00e2a7b0
void cSPUIRolloverCivCityHall::SetSpecialtyIcon(uint32_t icon)
{
    float area[4];

    mLayout.FindWindowByID(0x2cf2f30, true)->SetVisible(1, false);
    mLayout.FindWindowByID(0x2cf2f34, true)->SetVisible(1, false);
    mLayout.FindWindowByID(0x2cf2f38, true)->SetVisible(1, false);

    if (icon) {
        IWindow_s00e2_9c80* iconWindow = mLayout.FindWindowByID(icon, true);
        if (iconWindow) {
            iconWindow->SetVisible(1, true);
            IWindow_s00e2_9c80* image = mLayout.FindWindowByID(0x2cf2f44, true);
            if (!image)
                return;
            const float* imageArea = image->GetArea();
            area[0] = imageArea[0];
            area[1] = imageArea[1];
            area[2] = imageArea[2];
            area[3] = imageArea[3];
            const float* iconArea = iconWindow->GetArea();
            area[0] = iconArea[2] + 3.0f;
            image->SetAreaB(area);
            return;
        }
    }

    IWindow_s00e2_9c80* image = mLayout.FindWindowByID(0x2cf2f44, true);
    if (!image)
        return;
    const float* imageArea = image->GetArea();
    area[0] = imageArea[0];
    area[1] = imageArea[1];
    area[2] = imageArea[2];
    area[3] = imageArea[3];
    area[0] = 4.0f;
    image->SetAreaB(area);
}

// @ 0x00e2a920
void cSPUIRolloverCivCityHall::calculate_layout()
{
    float extend = gSPUIRowPad;

    IWindow_s00e2_9c80* header = mLayout.FindWindowByID(0x4b1f8ae, true);
    header->SetVisible(1, mFlagA6);
    if (mFlagA6) {
        const float* headerArea = header->GetAreaRaw();
        extend = (headerArea[3] - headerArea[1]) + gSPUIRowPad + gSPUIRowPad;
    }

    IWindow_s00e2_9c80* bar = mLayout.FindWindowByID(0x4b1f8bd, true);
    const float* barArea = bar->GetAreaRaw();
    float barRect[4];
    barRect[0] = barArea[0];
    barRect[1] = barArea[1];
    barRect[2] = barArea[2];
    barRect[3] = barArea[3];
    barRect[1] = extend;
    bar->SetAreaA(barRect);

    IWindow_s00e2_9c80* root = GetRootWindow();
    const float* rootArea = root->GetArea();
    float rootRect[4];
    rootRect[0] = rootArea[0];
    rootRect[1] = rootArea[1];
    rootRect[2] = rootArea[2];
    rootRect[3] = (extend + gSPUIRowHeight) + gSPUIRowPad + rootArea[1];
    root->SetAreaA(rootRect);
}

// @ 0x00e2ab10
bool cSPUIRolloverCivCityHall::SetPrimaryPopulationGroupId(uint32_t id)
{
    mKey9c = id;
    RBNode* found;
    mTree.find(&found, &mKey9c);
    if (found != mTree.mEndNode) {
        found->mField1c = 0;
        mValue98 = found->mField20;
        for (RBNode* node = mTree.mRoot; node != mTree.mEndNode; ) {
            if (node != found) {
                mCounter94++;
                node->mField1c = mCounter94;
                break;
            }
            node = RBTreeIncrement(node);
        }
    }

    IWindow_s00e2_9c80* window = mLayout.FindWindowByID(0x2cf324c, true);
    if (window) {
        IWindow_s00e2_9c80* child = window->FindChildByID(0xeeee8218);
        if (child)
            child->SetShadeColor(mValue98);
    }
    return true;
}

// @ 0x00e2acc0
void cSPUIRolloverCivCityHall::read_properties()
{
    AutoRefCount props;
    IPropertyManager* pm = PropertyManager();
    props.Reset();
    if (pm->GetPropertyList(0x5c770db7, &props.mpObject)) {
        if (props.mpObject) {
            cPropertyList* list = (cPropertyList*)props.mpObject;
            cProperty* prop;
            if (list->GetProperty(0x1b53f12, &prop) && prop->mType == 9)
                mValueA0 = (uint32_t)*prop->GetInt();
        }
    }
}

// @ 0x00e2c1e0
namespace civroll {
bool cSPUIRolloverCivCityVehicle_s00e2_b9d0::Initialize()
{
    if (Init())
    {
        SetPurposeIcon(0x338babf);
        return true;
    }
    return false;
}
}  // namespace civroll

// @ 0x00e2c290
namespace civroll {
cString_s00e2_b9d0* cStringVec::Erase(cString_s00e2_b9d0* first, cString_s00e2_b9d0* last)
{
    cString_s00e2_b9d0* p = F_e2a6f0(last, mpEnd, first);
    cString_s00e2_b9d0* end = mpEnd;
    while (p < end)
    {
        p->~cString_s00e2_b9d0();
        p = (cString_s00e2_b9d0*)((char*)p + 0x14);
    }
    const int count = (int)((char*)last - (char*)first) / 20;
    mpEnd = (cString_s00e2_b9d0*)((char*)mpEnd + count * 20);
    return first;
}
}  // namespace civroll

// @ 0x00e2c2f0
namespace civroll {
void cStringVec::Insert(cString_s00e2_b9d0* pos, uint32_t n, const cString_s00e2_b9d0* value)
{
    const uint32_t room = (uint32_t)((int)((char*)mpCapacity - (char*)mpEnd) / 20);
    if (room < n)
    {
        const int size = (int)((char*)mpEnd - (char*)mpBegin) / 20;
        uint32_t newCapacity = (uint32_t)size * 2;
        if (size == 0)
            newCapacity = 1;
        uint32_t total = (uint32_t)size + n;
        if (total < newCapacity)
            total = newCapacity;
        cString_s00e2_b9d0* buf = total ? (cString_s00e2_b9d0*)ea_operator_new(total * 20, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        cString_s00e2_b9d0* p = F_aed430(mpBegin, pos, buf);
        F_aed510(mpBegin, pos, buf);
        F_e2ad70(p, n, value);
        cString_s00e2_b9d0* after = (cString_s00e2_b9d0*)((char*)p + n * 20);
        cString_s00e2_b9d0* end = mpEnd;
        cString_s00e2_b9d0* q = F_aed430(pos, end, after);
        F_aed510(pos, end, after);
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            ea_delete(mpBegin);
        mpEnd = q;
        mpBegin = buf;
        mpCapacity = (cString_s00e2_b9d0*)((char*)buf + total * 20);
    }
    else if (n != 0)
    {
        cString_s00e2_b9d0 tmp;
        cString_s00e2_b9d0* end = mpEnd;
        const uint32_t room2 = (uint32_t)((int)((char*)end - (char*)pos) / 20);
        if (n < room2)
        {
            cString_s00e2_b9d0* m = (cString_s00e2_b9d0*)((char*)end - n * 20);
            cString_s00e2_b9d0* out = 0;
            F_e2aad0(&out, m, end, end, 0);
            cString_s00e2_b9d0* p = pos;
            mpEnd = (cString_s00e2_b9d0*)((char*)mpEnd + n * 20);
            F_aed470(p, m, end);
            F_e2aaa0(p, (cString_s00e2_b9d0*)((char*)p + n * 20), &tmp);
        }
        else
        {
            F_e2ad70(end, n - room2, &tmp);
            cString_s00e2_b9d0* p = pos;
            mpEnd = (cString_s00e2_b9d0*)((char*)mpEnd + (n - room2) * 20);
            F_e2aad0(&p, pos, end, mpEnd, 0);
            mpEnd = (cString_s00e2_b9d0*)((char*)mpEnd + room2 * 20);
            F_e2aaa0(pos, end, &tmp);
        }
        tmp.~cString_s00e2_b9d0();
    }
}
}  // namespace civroll

// @ 0x00e2c4f0
namespace civroll {
cSPUIRolloverCivRelationship_s00e2_b9d0::~cSPUIRolloverCivRelationship_s00e2_b9d0()
{
    mpVftable = (void*)0x148175c;
    mpVftable2 = (void*)0x148174c;
    mMapDC.DoNukeSubtree(mMapDC.mpRoot);
}
}  // namespace civroll

// @ 0x00e2c590
namespace civroll {
void SetValueTextForRollover(cSPUIRolloverCivRelationship_s00e2_b9d0* layout, uint32_t id, float value)
{
    wchar_t number[64];
    IWindowEx* root = (IWindowEx*)layout->GetRootWindow();
    IWindowEx* w = root->FindWindow(id, 1);
    if (!w)
        return;
    IWindowEx* child = (IWindowEx*)w->GetChildByID(0xf15f4bd);
    if (!child)
        return;

    SetNumberString((long long)fabs((double)(value * 100.0f)), number, 0x40);

    Variant_s00e2_b9d0 var;
    WStr_s00e2_b9d0 text;
    text.mpBegin = 0;
    text.mpEnd = 0;
    text.mpCapacity = 0;
    text.RangeInitialize(number);

    if (value > 0.0f)
    {
        {
            WStr_s00e2_b9d0 tmp;
            WStr_s00e2_b9d0* r = eastl_operator_plus(&tmp, gwPlus, &text);
            if (r != &text)
                text.assign(r->mpBegin, r->mpEnd);
            WStr_Free(tmp);
        }
        child->SetColor(0xff00ff00);
    }
    if (value < 0.0f)
    {
        {
            WStr_s00e2_b9d0 tmp;
            WStr_s00e2_b9d0* r = eastl_operator_plus(&tmp, gwMinus, &text);
            if (r != &text)
                text.assign(r->mpBegin, r->mpEnd);
            WStr_Free(tmp);
        }
        child->SetColor(0xffff0000);
    }

    var.mFlags = 0;
    var.mTypeId = 0;
    var.Set(0x13, 9, &text, 0x10, 1);
    layout->SetProp(id, &var, 1, 0);
    if (var.mFlags & 4)
        var.Destruct(0);
    WStr_Free(text);
}
}  // namespace civroll

// @ 0x00e2c840
namespace civroll {
bool cSPUIRolloverFeedbackGrid::FUN_00e2c840(uint32_t key, int a, int b)
{
    int page = (mPerRowA0 + a - 1) / mPerRowA0;
    if (!(page > 0))
        page = 1;

    FeedbackNode* node;
    mMap.Find(&node, &key);
    if ((void*)node == (void*)&mMap.mpAnchor)
    {
        FeedbackEvent value;
        value.mField00 = 0;
        value.mField04 = 0;
        value.mField08 = 0;
        value.mField0c = 0;
        value.mField08 = (int)key;
        const uint32_t maskedKey = key & 0xffffff00u;
        mMap.Insert(&node, &value, maskedKey);
        if (key != (uint32_t)mField9c)
            node->mValue.mField08 = ++mCounter94;
        else
            node->mValue.mField08 = 0;
    }

    node->mValue.mField04 = page;
    node->mValue.mField0c = b;
    node->mValue.mField00 = a;

    if (key == (uint32_t)mField9c &&
        (node->mValue.mField08 > 0 || mField98 != b))
        FUN_00e2ab10(key);
    return true;
}
}  // namespace civroll

// @ 0x00e2c920
namespace civroll {
cSPUIRolloverCivRelationship_s00e2_b9d0::cSPUIRolloverCivRelationship_s00e2_b9d0()
{
    mpVftable = (void*)0x148175c;
    mpVftable2 = (void*)0x148174c;
    mVecC8.mpBegin = 0;
    mVecC8.mpEnd = 0;
    mVecC8.mpCapacity = 0;
    mMapDC.mpAnchorEnd = 0;
    mMapDC.mpRoot = 0;
    mMapDC.mnColor = 0;
    mMapDC.mpRoot = 0;
    mMapDC.mbColor = 0;
    mMapDC.mnSize = 0;
    mMapDC.mpAnchor = &mMapDC.mpAnchor;
    mMapDC.mpAnchorEnd = &mMapDC.mpAnchor;
    mMapDC.mFieldF8 = 0;
    SetKey(L"CivCommRollover", 0x40464100);
    SetRootWindowId(0x4d18738);
}
}  // namespace civroll

// @ 0x00e2c9f0
namespace civroll {
void cSPUIRolloverCivRelationship_s00e2_b9d0::Shutdown()
{
    if (mFlag44)
    {
        cSPUILayoutManager* lm = SPUIHelpers_GetLayoutManager_s00e2_b9d0(0x5b598f6);
        IWindowEx* world = (IWindowEx*)lm->GetWorldMainWindow();
        world->DisposeWindow(GetRootWindow());
    }
    mMapDC.DoNukeSubtree(mMapDC.mpRoot);
    mMapDC.mpAnchor = &mMapDC.mpAnchor;
    mMapDC.mpAnchorEnd = &mMapDC.mpAnchor;
    mMapDC.mpRoot = 0;
    mMapDC.mbColor = 0;
    mMapDC.mnSize = 0;
    mVecC8.Erase(mVecC8.mpBegin, mVecC8.mpEnd);
    func24h();
}
}  // namespace civroll

// @ 0x00e2ca70
namespace civroll {
void cStringVec::Index(uint32_t i)
{
    if (i > (uint32_t)((int)((char*)mpEnd - (char*)mpBegin) / 20))
    {
        cString_s00e2_b9d0 tmp;
        Insert(mpEnd, i - (uint32_t)((int)((char*)mpEnd - (char*)mpBegin) / 20), &tmp);
    }
    else
    {
        Erase((cString_s00e2_b9d0*)((char*)mpBegin + i * 20), mpEnd);
    }
}
}  // namespace civroll

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
            fValue = RelationshipManager_s00e2_cb00()->CalculateRelationshipEvent(nFrom, nTo, nEvent);
        *GetValue(nEvent) = fValue;
    }
    return *this;
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

// @ 0x00e2d430
void RelationshipPartialSort(cAbsValueLess& less, uint32_t* pFirst, uint32_t* pMiddle, uint32_t* pLast)
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
void RelationshipIntrosortLoop(cAbsValueLess& less, uint32_t* pFirst, uint32_t* pLast, int32_t nDepthLimit)
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
