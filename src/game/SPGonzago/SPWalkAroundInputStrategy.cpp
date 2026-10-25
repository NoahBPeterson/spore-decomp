// src/game/SPGonzago/SPWalkAroundInputStrategy.cpp -- migrated from slice(s) s0107b260, s0107c4b0, s0107c1e0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPWalkAroundInputStrategy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include "SP/cInputStrategy.h"
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"
#include "SP/cSPMission.h"
#include "SP/cSPPlanetaryArtifact.h"

// ---- items of slice s0107c1e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3
{
    uint32_t x;
    uint32_t y;
    uint32_t z;
};
struct CNoun;
struct CTool;
struct CPlanet;
struct CInventory;
struct CIntVector;
struct CToolManager;
struct CNounManager;
struct CUIEventLog;
struct CSpaceTokenTranslator;
struct SimGame;
struct CNoun
{
    virtual void vfn00();   // slot 0
    virtual void vfn01();   // slot 1  (Release)
    virtual void vfn02();   // slot 2

    /* 004h */ uint8_t mPad_004[0x638 - 0x04];
    /* 638h */ uint32_t mField_638;     // noun id handed to RemoveArtifact
    /* 63ch */ uint8_t mPad_63c[0x64c - 0x63c];
    /* 64ch */ Vec3     mVec_64c;       // position of the pending interaction
    /* 658h */ uint32_t mField_658;     // pending interaction kind (4/5/other)
    /* 65ch */ uint8_t mPad_65c[0x660 - 0x65c];
    /* 660h */ float    mField_660;     // pending interaction timer
};
struct CTool
{
    virtual void vfn00();               // slot 0
    virtual void vfn01();               // slot 1
    virtual void vfn02();               // slot 2  (Release)
    virtual void vfn03();               // slot 3
    virtual void vfn04();               // slot 4
    virtual void vfn05();               // slot 5
    virtual uint32_t* vfn06();          // slot 6  (0x018) -> tool id slot

    /* 004h */ uint8_t mPad_004[0x7c - 0x04];
    /* 07ch */ uint32_t mField_7c;      // last id used, mirrored to the translator
};
struct CInventory
{
virtual void d00();
virtual void d01();
virtual void d02();
virtual void d03();
virtual void d04();
virtual void d05();
virtual void d06();
virtual void d07();
virtual void d08();
virtual void d09();
virtual void d10();
virtual void d11();
virtual void d12();
virtual void d13();
virtual void d14();
virtual void d15();
virtual void d16();
virtual void d17();
virtual void d18();
virtual void d19();
virtual void d20();
virtual void d21();
virtual void d22();
virtual void d23();
virtual void d24();
virtual void d25();
virtual void d26();
virtual void d27();
virtual void d28();
virtual void d29();
virtual void d30();
virtual void d31();
    virtual void UseTool(void* pTool, uint32_t nA, uint32_t nB);    // slot 32 (0x080)
};
struct CIntVector
{
    /* 000h */ uint8_t   mPad_000[0x0c];
    /* 00ch */ uint32_t* mpData;

    void resize(uint32_t nCount);       // 0x007eb820
};
struct CToolManager
{
    bool CreateToolFromToolID(uint32_t nToolId);    // 0x0104e340
};
struct CNounManager
{
    void RemoveNoun(CNoun* pNoun);      // 0x00b225d0
};
struct CPlanet
{
    /* 000h */ uint8_t mPad_000[0x13c];
    /* 13ch */ void*   mField_13c;
};
struct SimGame
{
    void*       f5180(int nArg);        // 0x01005180
    CInventory* GetPlayerInventory();   // 0x00a1ad60
};
struct CSpaceTokenTranslator
{
    /* 000h */ uint8_t  mPad_000[0x14];
    /* 014h */ CTool*   mField_14;
    /* 018h */ uint8_t  mPad_018[0x3c - 0x18];
    /* 03ch */ uint32_t mField_3c;
};
struct CUIEventLog
{
    void PostFeedbackEvent();           // 0x00dd8640
};
struct cWalkAroundInputStrategy
{
    /* 000h */ uint8_t mPad_000[0x11c];
    /* 11ch */ CNoun*  mField_11c;      // the noun currently tracked

    void HandleSimulationUpdate(int nDelta);
};
Vec3 gnComparePos;                                      // 0x016e395c
float gfNegativeOne = -1.0f;                            // 0x013eb1bc
CSpaceTokenTranslator* gpSpaceTokenTranslator;          // 0x016e0d08
SimGame*       SpaceGameGet();                          // 0x01002bd0
CNounManager*  GetNounManager();                        // 0x00b3d300
CPlanet*       GetActivePlanet();                       // 0x01021260
void CollectSpicePile(CTool* pTool);
CTool* FUN_00b3d3d0(int nKind, CNoun* pNoun);
Vec3* FUN_00ad2620(CNoun* pNoun, void** ppOut);
uint32_t FUN_00c463d0(CTool** ppOut);
uint32_t FUN_00c463d0(CTool** ppOut, Vec3 pos);
void FUN_00c878d0(uint32_t nValue);
CToolManager* __stdcall FUN_00b3d390(Vec3* pItem);
void RemoveArtifact(void* pPlanetSlot, const Vec3& pos, uint32_t nNounId);
CUIEventLog* __stdcall EventLog(uint32_t a, uint32_t b, uint32_t c,
                                uint32_t d, uint32_t e, uint32_t f);
void FUN_00d32fb0(cWalkAroundInputStrategy* pSelf, int nDelta);
// ---- items of slice s0107c1e0 end

// ---- items of slice s0107c4b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_BoolVecBuf[2];      // 0x01667bac: static storage of a fixed_vector<bool,1>
extern char g_BoolVecDefault[];   // 0x013ec47c: default (empty) vector<bool> prototype
extern char g_ConnName[];      // 0x0149c750
extern "C" void* __cdecl FUN_011e0744(void*, const void*, unsigned);
void __cdecl operator delete[](void*);
struct BoolVec
{
    char* b;
    char* e;
    char* cap;
    void CopyCtor(const void* src);   // FUN_0057cc10
};
struct StateMachine;
struct StateBuilder
{
    uint32_t pad[4];
    int* field;
    StateBuilder(StateMachine* sm);   // FUN_00b198d0
    void AddState(int idx, const char* name);   // FUN_00b1c080
    void AddTransition(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j,
                       BoolVec* v, int k);      // FUN_00b1c8d0
    ~StateBuilder();                  // 0x0083c750 EA::ArgScript::cCommandBase::~cCommandBase
};
struct Entry { uint32_t id, z, w; };
struct EntryVec
{
    Entry* b;
    Entry* e;
    Entry* cap;
    void DoInsertValue(Entry* pos, const Entry* v);   // FUN_00b535d0
    void Push(uint32_t id)
    {
        Entry t = { id, 0, 100 };
        if (e < cap) { Entry* p = e; e = e + 1; if (p) *p = t; }
        else DoInsertValue(e, &t);
    }
};
struct Server;
struct Connector { void Init(Server* s, void* h, const char* name, int n); };   // Connector::Init 0x4db620
Server* GetServer();   // EA::Messaging::GetServer 0x883860
struct Dispatcher { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual void Apply(EntryVec* v, int n); };
Dispatcher* GetDispatcher();   // FUN_00b3d240
static inline void MakeA(BoolVec& v)
{
    char* p = g_BoolVecBuf;
    v.b = p; v.cap = p + 1;
    FUN_011e0744(p, g_BoolVecDefault, 0);
    *(v.e = g_BoolVecBuf) = 0;
}
static inline void MakeB(BoolVec& v)
{
    v.b = 0; v.e = 0; v.cap = 0;
    v.CopyCtor(g_BoolVecDefault);
}
struct cWalkAroundInputStrategy_s0107_c4b0
{
    char pad0[4];
    StateMachine* sm() { return (StateMachine*)((char*)this + 4); }
    char pad1[0x44];
    char handler[0xBC];
    char connector[16];
    void Init();  // 0x0107c4b0 (cWalkAroundInputStrategy::Init)
};
// ---- items of slice s0107c4b0 end

// ---- items of slice s0107b260 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(n) virtual void _v##n();
template <class T>
class AutoRefCount_s0107_b260 {
public:
    T* mpObject;                 // +0x00
    AutoRefCount_s0107_b260() : mpObject(0) {}
    ~AutoRefCount_s0107_b260()
    {
        if (mpObject != 0)
            mpObject->Release();
    }
    AutoRefCount_s0107_b260& operator=(T* pObject); // 0x00b5f950
};
namespace EA {
using ::AutoRefCount_s0107_b260;
}
namespace EA {
namespace Messaging {
class IHandler_s0107_b260 {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3)
};
}
}
namespace EA {
namespace Messaging {
class Server_s0107_b260 {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8)
    virtual void AddHandler(IHandler_s0107_b260* pHandler, uint32_t nMessageId); // +0x24
};
}
}
namespace EA {
namespace Messaging {
void RemoveHandler(Server_s0107_b260* pServer, IHandler_s0107_b260* pHandler, uint32_t* pIds,
                   uint32_t nIdCount, int32_t nPriority); // 0x00571db0
}
}
namespace EA {
namespace Messaging {
class AutoHandler_s0107_b260 {
public:
    Server_s0107_b260* mpServer;            // +0x00
    IHandler_s0107_b260* mpHandler;         // +0x04
    uint32_t* mpIdArray;         // +0x08
    uint32_t mnIdArrayCount;     // +0x0c
    int32_t mnPriority;          // +0x10
    AutoHandler_s0107_b260()
        : mpServer(0), mpHandler(0), mpIdArray(0), mnIdArrayCount(0),
          mnPriority(0) {}
    ~AutoHandler_s0107_b260()
    {
        if (mpServer != 0) {
            Server_s0107_b260* pServer = mpServer;
            mpServer = 0;
            RemoveHandler(pServer, mpHandler, mpIdArray, mnIdArrayCount,
                          mnPriority);
        }
    }
};
}
}
class cUIObject {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6)
    virtual void* GetItem();       // +0x1c
    virtual uint32_t GetTypeId();  // +0x20
};
class cToolsEvent {
public:
    cUIObject* mpObject;         // +0x00
    uint32_t mnPad04;            // +0x04
    uint32_t mnType;             // +0x08
    uint32_t mnPad0c;            // +0x0c
    void* mpCard;                // +0x10
};
class IWinText {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3)
    virtual void Release();      // +0x10
    uint8_t mnPad14[0x64c];      // +0x014
    float mHighlightAlpha;       // +0x660
};
class cSPPlanetaryArtifact {
public:
    VSLOT(0)
    virtual void Release();      // +0x04
};
class cInputStrategy {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3)
    virtual ~cInputStrategy();
    uint8_t mnPad04[0x38];       // +0x004
};
class cSPUICursorStrategy {
public:
    VSLOT(0) VSLOT(1)
    virtual ~cSPUICursorStrategy();
    uint8_t mnPad04[4];          // +0x004
};
class IWinProc {
public:
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual ~IWinProc();
};
class IHandlerRC_s0107_b260 {
public:
    VSLOT(0) VSLOT(1)
    virtual ~IHandlerRC_s0107_b260();
};
template <class T>
class RefCountVTemplate {
public:
    VSLOT(0) VSLOT(1)
    virtual ~RefCountVTemplate();
    int32_t mnRefCount;          // +0x004
};
class cCreatureModeInputStrategy : public cInputStrategy,
                                   public cSPUICursorStrategy,
                                   public IWinProc,
                                   public IHandlerRC_s0107_b260,
                                   public RefCountVTemplate<int> {
public:
    cCreatureModeInputStrategy();
    virtual ~cCreatureModeInputStrategy();
    uint8_t mnPad54[0x80];       // +0x054
    AutoRefCount_s0107_b260<IWinText> mHoverText; // +0x0d4
    uint8_t mnPadD8[0x30];       // +0x0d8
    bool HandleMessage(uint32_t nMessage, cToolsEvent* pEvent); // 0x00d37c40
};
class cWalkAroundInputStrategy_s0107_b260 : public cCreatureModeInputStrategy {
public:
    EA::Messaging::AutoHandler_s0107_b260 mAutoHandler;          // +0x108
    AutoRefCount_s0107_b260<cSPPlanetaryArtifact> mpCollectingArtifact; // +0x11c
    cWalkAroundInputStrategy_s0107_b260();
    virtual ~cWalkAroundInputStrategy_s0107_b260();
    bool HandleMessage(uint32_t nMessage, cToolsEvent* pEvent); // 0x0107bf40
};
// ---- items of slice s0107b260 end

// @ 0x0107c0b0
cWalkAroundInputStrategy_s0107_b260::cWalkAroundInputStrategy_s0107_b260()
{
}

// @ 0x0107c160
cWalkAroundInputStrategy_s0107_b260::~cWalkAroundInputStrategy_s0107_b260()
{
}

// @ 0x0107c1e0
void cWalkAroundInputStrategy::HandleSimulationUpdate(int nDelta)
{
    CNoun* pNoun = mField_11c;
    if (pNoun != 0)
    {
        pNoun->mField_660 = pNoun->mField_660 - (float)(uint32_t)nDelta * 0.001f;
        if (pNoun->mField_660 < 0.0f)
        {
            pNoun->mField_660 = gfNegativeOne;

            if (pNoun->mVec_64c.x != gnComparePos.x ||
                pNoun->mVec_64c.y != gnComparePos.y ||
                pNoun->mVec_64c.z != gnComparePos.z)
            {
                if (pNoun->mField_638 != 0)
                {
                    uint32_t eState = pNoun->mField_658;
                    CTool*   pTool  = 0;
                    if (eState == 4)
                    {
                        CollectSpicePile(FUN_00b3d3d0(0, pNoun));
                    }
                    else if (eState == 5)
                    {
                        Vec3  pos;
                        Vec3* pPos = FUN_00ad2620(pNoun, (void**)&pos);
                        uint32_t nKey = FUN_00c463d0((CTool**)&pTool, *pPos);
                        FUN_00c878d0(nKey);
                        if (pTool != 0)
                            SpaceGameGet()->GetPlayerInventory()->UseTool(pTool, 0, 1);
                        if (pTool != 0)
                            pTool->vfn02();
                    }
                    else
                    {
                        Vec3 pos;
                        if (FUN_00b3d390(FUN_00ad2620(pNoun, (void**)&pos))
                                ->CreateToolFromToolID(FUN_00c463d0((CTool**)&pTool)))
                        {
                            pTool->mField_7c = mField_11c->mField_638;
                            SpaceGameGet()->GetPlayerInventory()->UseTool(pTool, 0, 1);

                            CIntVector* pInts = (CIntVector*)SpaceGameGet()->f5180(0xf);
                            pInts->resize(9);
                            pInts->mpData[7] = *pTool->vfn06();
                            pInts->mpData[8] = 5;

                            gpSpaceTokenTranslator->mField_3c = pTool->mField_7c;
                            gpSpaceTokenTranslator->mField_14 = pTool;
                            EventLog(0xc417e56d, 0x131a9f54, 0, 0, 1, 0)->PostFeedbackEvent();
                        }
                        if (pTool != 0)
                            pTool->vfn02();
                    }
                }
            }

            CPlanet* pPlanet = GetActivePlanet();
            if (pPlanet != 0)
            {
                Vec3 pos = mField_11c->mVec_64c;
                RemoveArtifact(pPlanet->mField_13c, pos, mField_11c->mField_638);
            }

            GetNounManager()->RemoveNoun(mField_11c);

            CNoun* pOld = mField_11c;
            if (pOld != 0)
            {
                mField_11c = 0;
                pOld->vfn01();
            }
        }
    }

    FUN_00d32fb0(this, nDelta);
}

// @ 0x0107c4b0
void cWalkAroundInputStrategy_s0107_c4b0::Init()
{
    StateBuilder b(sm());
    b.AddState(0, "Walk around: neutral");
    b.AddState(1, "Walk around: mouse moving");
    b.AddState(2, "Walk around: ban");
    b.AddState(3, "Walk around: inspect");
    { BoolVec v; MakeA(v); b.AddTransition(0, 10, 0x3ff, 0x16, 0, 0, 0x19edcf3, 0, 1, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(1, 0xb, 0x3ff, 0x16, -1, 0, 0xd02dcc68, 0, 0, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(0, 0xb, 0x3ff, 0x12345678, -1, 0, 0xd02dcc68, 0, 0, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x16, 0xd0036e08, 2, 0x1a53705, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x16, 0x4f176642, 0, 0x1a53705, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x16, 0x3ed590d, 0, 0x3f3eb2c, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x16, 0xd0036e08, 1, 0x17dab3f, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x16, 0x2dd8c33, 0, 0x2df01f2, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x16, -1, 0, 0x1c38e3b, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 0xb, 0x3ff, 0x16, -1, 0, 0x1c38e3b, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x18, -1, 0, 0x35f7b83, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 0xb, 0x3ff, 0x18, -1, 0, 0x35f7b83, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 1, 0x3ff, 0x3ea, -1, 0, 0x6493c83, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 3, 0x3ff, 0x3ea, -1, 0, 0x6493c83, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 1, 0x3ff, 0x3e9, -1, 0, 0x6493c83, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 3, 0x3ff, 0x3e9, -1, 0, 0x6493c83, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x14, -1, 0, 0x50567351, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 1, -1, 0, 0x27c7119, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 2, -1, 0, 0x27c7119, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 3, -1, 0, 0x27c67ea, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 4, -1, 0, 0x27c67ea, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x10, -1, 0, 0x705673e1, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 0xb, 0x3ff, 0x10, -1, 0, 0x705673e1, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x11, -1, 0, 0x705673e9, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 0xb, 0x3ff, 0x11, -1, 0, 0x705673e9, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x13, -1, 0, 0x25db76f, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 0xb, 0x3ff, 0x13, -1, 0, 0x25db76f, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x12, -1, 0, 0x25db76a, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 0xb, 0x3ff, 0x12, -1, 0, 0x25db76a, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(-1, 10, 0x3ff, 0x16, -1, 0, 0x2c4bfde, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(-1, 0xb, 0x3ff, 0x16, -1, 0, 0x2c4bfde, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(-1, 10, 0x3ff, 0x15, -1, 0, 0x1c41da1, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(2, 1, 0x3ff, 1000, -1, 0, 0xb332763d, -1, 2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(2, 4, 0x3ff, 0x1b, -1, 0, 0xf3327645, 0, 0, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(2, 6, 0x3ff, -1, -1, 0, 0x639939b, -1, 2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(2, 1, 0x3ff, 0x3ea, -1, 0, 0x6493c83, 1, 2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(2, 3, 0x3ff, 0x3ea, -1, 0, 0x6493c83, 0, 2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(3, 1, 0x3ff, 1000, -1, 0, 0x62663dc, -1, 3, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(3, 4, 0x3ff, 0x1b, -1, 0, 0x62663dd, 0, 0, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(3, 1, 0x3ff, 0x3ea, -1, 0, 0x6493c83, 1, 3, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(3, 3, 0x3ff, 0x3ea, -1, 0, 0x6493c83, 0, 3, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(-1, 10, 0x3ff, -1717986926, -1, 0, 0x274847c, 0x29a, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }

    Server* srv = GetServer();
    Connector* c = (Connector*)((char*)this + 0x108);
    c->Init(srv, this ? (char*)this + 0x48 : 0, g_ConnName, 0x15);
    EntryVec vec = { 0, 0, 0 };
    vec.Push(0x23a6ccd);
    vec.Push(0x23a7919);
    vec.Push(0x2dd8c33);
    vec.Push(0x116d858);
    vec.Push(0x23a6cc8);
    GetDispatcher()->Apply(&vec, 1);
    if (vec.b && ((int*)vec.b)[-1] != 0) operator delete[](vec.b);
    if (b.field && b.field[-1] != 0) operator delete[](b.field);
}
