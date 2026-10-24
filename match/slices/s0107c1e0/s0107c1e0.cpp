// 0x0107c1e0..0x0107c481 -- SP::cWalkAroundInputStrategy (SPGonzago).
// Walk-around (on-foot) input strategy simulation tick: ages the pending
// interaction timer on the tracked noun and, when it expires, consumes the
// carried tool / spice pile for the current noun and hands the artifact back.
// Flags: /O2 /MD /Gy /EHsc /TP.

#include "types.h"

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

// ---------------------------------------------------------------------------
// The tracked noun that is about to be interacted with.
// ---------------------------------------------------------------------------
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

// A tool built from a property list (an AutoRefCount target).
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

// Player inventory; the consumed slot is 32 (0x080).
struct CInventory
{
    virtual void d00();  virtual void d01();  virtual void d02();  virtual void d03();
    virtual void d04();  virtual void d05();  virtual void d06();  virtual void d07();
    virtual void d08();  virtual void d09();  virtual void d10();  virtual void d11();
    virtual void d12();  virtual void d13();  virtual void d14();  virtual void d15();
    virtual void d16();  virtual void d17();  virtual void d18();  virtual void d19();
    virtual void d20();  virtual void d21();  virtual void d22();  virtual void d23();
    virtual void d24();  virtual void d25();  virtual void d26();  virtual void d27();
    virtual void d28();  virtual void d29();  virtual void d30();  virtual void d31();
    virtual void UseTool(void* pTool, uint32_t nA, uint32_t nB);    // slot 32 (0x080)
};

// SP::IntVector -- resizable integer array.
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

// The strategy object itself (walk-around / on-foot input strategy).
struct cWalkAroundInputStrategy
{
    /* 000h */ uint8_t mPad_000[0x11c];
    /* 11ch */ CNoun*  mField_11c;      // the noun currently tracked

    void HandleSimulationUpdate(int nDelta);
};

// ---------------------------------------------------------------------------
// Globals / helpers.
// ---------------------------------------------------------------------------
Vec3 gnComparePos;                                      // 0x016e395c
float gfNegativeOne = -1.0f;                            // 0x013eb1bc
CSpaceTokenTranslator* gpSpaceTokenTranslator;          // 0x016e0d08

SimGame*       SpaceGameGet();                          // 0x01002bd0
CNounManager*  GetNounManager();                        // 0x00b3d300
CPlanet*       GetActivePlanet();                       // 0x01021260

// 0x0103fe90: cSPSpaceTrading::CollectSpicePile(CTool*)
void CollectSpicePile(CTool* pTool);
// 0x00b3d3d0: fetch the trading object for the given noun/kind pair.
CTool* FUN_00b3d3d0(int nKind, CNoun* pNoun);
// 0x00ad2620: walk to the next interaction item of the noun.
Vec3* FUN_00ad2620(CNoun* pNoun, void** ppOut);
// 0x00c463d0: build an interaction property list (overloads at one address).
uint32_t FUN_00c463d0(CTool** ppOut);
uint32_t FUN_00c463d0(CTool** ppOut, Vec3 pos);
// 0x00c878d0: post a property list result.
void FUN_00c878d0(uint32_t nValue);
// 0x00b3d390: hand an interaction item to the tool manager.
CToolManager* __stdcall FUN_00b3d390(Vec3* pItem);
// 0x00c71160: remove an artifact from the planet.
void RemoveArtifact(void* pPlanetSlot, const Vec3& pos, uint32_t nNounId);
// 0x00b3e0: fetch the UI event log to post a feedback event on.
CUIEventLog* __stdcall EventLog(uint32_t a, uint32_t b, uint32_t c,
                                uint32_t d, uint32_t e, uint32_t f);
// 0x00d32fb0: base strategy simulation tick.
void FUN_00d32fb0(cWalkAroundInputStrategy* pSelf, int nDelta);

// ---------------------------------------------------------------------------
// 0x0107c1e0: SP::cWalkAroundInputStrategy::HandleSimulationUpdate -- advance
// the walk-around strategy by one simulation step.
// ---------------------------------------------------------------------------
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