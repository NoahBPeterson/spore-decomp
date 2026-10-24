// Slice s0106f5b0 -- SP::cSPUISpace::~cSPUISpace (0x0106f5b0)
// Retail layout (cString is 0x14 bytes here; the 2008 PDB's 0x1c is not retail). Only members that have
// a destructor are modelled; plain data between them is padding. Members are declared in ascending
// offset order, so cl destroys them in the original reverse order by itself.
#include "types.h"

void operator_delete__(void* p);                         // 0x00f47380

// ---- intrusive pointer flavours (differ only in the vtable slot of Release) ----
struct IRel1 { virtual void v0(); virtual void Release(); };                // Release at +4
struct IRel2 { virtual void v0(); virtual void v1(); virtual void Release(); };  // Release at +8
struct IRelC0 {                                                              // Release at +0xc0
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
    virtual void Release();
};
struct RefCounted {                                  // EA RefCountTemplate: vptr, count at +4, deleting dtor in slot 0
    virtual ~RefCounted();
    int mnRefCount;
    void Release()
    {
        int n = mnRefCount;
        mnRefCount = n - 1;
        n--;
        if (n == 0) {
            mnRefCount = 1;
            delete this;
        }
    }
};

struct Arc1 { IRel1* p; ~Arc1() { if (p) p->Release(); } };
struct Arc2 { IRel2* p; ~Arc2() { if (p) p->Release(); } };
struct ArcC0 { IRelC0* p; ~ArcC0() { if (p) p->Release(); } };
struct ArcRC { RefCounted* p; ~ArcRC() { if (p) p->Release(); } };

// sp_vector_allocator block: a header dword sits in front of the data
struct SpBlock { void* p; ~SpBlock() { if (p && ((int*)p)[-1] != 0) operator_delete__(p); } };
struct RawPtr  { void* p; ~RawPtr() { if (p) operator_delete__(p); } };

struct cString { uint32_t d[5]; ~cString();                            // 0x006b5240 (out of line)
                 const char* GetText(const void* pKey, int flags); };   // 0x006b55c0

struct StrVec {                                                        // eastl::vector<cString, sp_vector_allocator> (+ 1 dword)
    cString* mpBegin; cString* mpEnd; cString* mpCap; uint32_t alloc; uint32_t extra;
    ~StrVec()
    {
        cString* e = mpEnd;
        for (cString* it = mpBegin; it < e; ++it)
            it->~cString();
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
};

// eastl::hashtable instances: bucket array (+4), bucket count (+8), element count (+0xc)
struct HashWStr {                                   // hashtable<wchar_t const*, ...>   DoFreeNodes at 0x00693230
    uint32_t pad0; void** mpBuckets; uint32_t mnBuckets; uint32_t mnElements;
    void DoFreeNodes(void** b, uint32_t n);
    ~HashWStr() { DoFreeNodes(mpBuckets, mnBuckets); mnElements = 0; if (mnBuckets > 1) operator_delete__(mpBuckets); }
};
struct HashB {                                      // hashtable at +0x2a0, free routine at 0x01068400
    uint32_t pad0; void** mpBuckets; uint32_t mnBuckets; uint32_t mnElements;
    void DoFreeNodes(void** b, uint32_t n);
    ~HashB() { DoFreeNodes(mpBuckets, mnBuckets); mnElements = 0; if (mnBuckets > 1) operator_delete__(mpBuckets); }
};
struct HashTool {                                   // hashtable<uint, pair<uint, AutoRefCount<cSPToolStrategy>>>   0x00961d60
    uint32_t pad0; void** mpBuckets; uint32_t mnBuckets; uint32_t mnElements;
    void DoFreeNodes(void** b, uint32_t n);
    ~HashTool() { DoFreeNodes(mpBuckets, mnBuckets); mnElements = 0; if (mnBuckets > 1) operator_delete__(mpBuckets); }
};

// out-of-line member destructors (callee addresses in the comments)
struct ObjE0A400 { uint32_t d[29]; ~ObjE0A400(); };   // 0x00e0a400
struct Obj4AA120 { uint32_t d[12]; ~Obj4AA120(); };   // 0x004aa120
struct Obj6CB90  { uint32_t d[14]; ~Obj6CB90(); }; // 0x0106cb90 (0x530..0x568)
struct Obj4B5440 { uint32_t d[5]; ~Obj4B5440(); }; // 0x004b5440
struct SharedLibVec { void* a; void* b; void* c; uint32_t alloc; ~SharedLibVec(); };  // 0x005c7f10

void EA_Messaging_RemoveHandler(void* h, uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00571db0, cdecl
struct AutoHandler {
    void* mpHandler; uint32_t a, b, c, d;
    ~AutoHandler()
    {
        if (mpHandler) {
            void* h = mpHandler;
            mpHandler = 0;
            EA_Messaging_RemoveHandler(h, a, b, c, d);
        }
    }
};

// ---- base classes (vtable restore order in the epilogue: +0xc, +4, +0) ----
struct BaseRes   { virtual ~BaseRes() {} };                        // GmeEditorResBase-side vptr at +0
struct BaseCount { virtual ~BaseCount() {} int mnRefCount; };      // RefCountVTemplate<int> at +4
struct BaseMsg   { virtual ~BaseMsg() {} };                        // IMsgHandler at +0xc

struct UIMgrA; struct UIMgrB;
UIMgrA* FUN_0067de40();                                            // cdecl, no args
struct UIMgrB { virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
                virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
                virtual void Set(void* v); };                       // +0x20
struct UIMgrA { virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
                virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
                virtual UIMgrB* Get(); };                           // +0x20
struct DeletableObj { virtual ~DeletableObj(); };

// SP space-token translator, reached through the 0x016e0d08 global the dtor hands back to the UI manager.
struct cSpaceTokenTranslator
{
    char     pad00[0xc];
    uint32_t mPlanetId;    // +0x0c: planet id of the active planet, refreshed on every focus change
    uint32_t mPad14;       // +0x14
    void*    mpRecord;     // +0x24: species profile of the focused record
};
extern cSpaceTokenTranslator* g_16e0d08;                            // 0x016e0d08

namespace SP {

// ---- focus / tooltip model used by DoFocusChange ----------------------------------------------------------
struct cSPUIWidget;
struct cSPUISpace;
struct cSPTool;
struct IFocusTarget;

// The object whose focus is about to change; only the slots DoFocusChange calls are named.
struct IFocusTarget
{
    virtual void OnFocusLost();                        // +0x00
    virtual void Release();                            // +0x04
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06();
    virtual uint32_t GetTypeId();                      // +0x1c
    virtual uint32_t GetClassHash();                   // +0x20
    virtual void v09();
    virtual uint32_t GetFocusFlags();                  // +0x28
    virtual void v0b(); virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v1a(); virtual void v1b(); virtual void v1c(); virtual void v1d(); virtual void v1e();
    virtual void v1f(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual void v29(); virtual void v2a(); virtual void v2b(); virtual void v2c(); virtual void v2d();
    virtual void v2e(); virtual void v2f();
    virtual void GetFocusTransform(float u, float v, float* pOut);             // +0xc0 (slot 48)
};

struct cSPUIWindow                                    // UI window handed out by cSPUIGlobalUI::FindWindowByID
{
    virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
    virtual cSPUIWidget* GetContent();                 // +0x10
    virtual void w05(); virtual void w06(); virtual void w07(); virtual void w08(); virtual void w09();
    virtual void w0a(); virtual void w0b(); virtual void w0c(); virtual void w0d(); virtual void w0e();
    virtual void w0f(); virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13();
    virtual void w14(); virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18();
    virtual void w19(); virtual void w1a(); virtual void w1b();
    virtual void SetPosition(float x, float y);        // +0x70 (slot 28)
    virtual void w1d(); virtual void w1e();
    virtual void SetVisible(bool show, bool focusSame); // +0x7c (slot 31)
};
struct cSPUIWidget : public IFocusTarget              // IFocusTarget supplies slots 0..0xc0
{
    virtual void SetLayoutPosition(float x, float y, const float* pAnchor);   // +0xc4 (slot 49)
};
struct cSPUIGlobalUI
{
    cSPUIWindow* FindWindowByID(uint32_t id);           // 0x00e012b0 (thiscall, not virtual)
};
struct cUITimedTooltip { void Hide(); };               // 0x00e36620
struct cSPUIRolloverCivRelationship
{
    void ShowRelationshipRollover(IFocusTarget* pTarget, uint32_t civId, bool a);   // 0x00e2d6a0
    void HideRelationshipRollover();                                                // 0x00e2a6c0
};

// The 12-byte resource key used by the property / tool lookups.
struct Key { uint32_t mHash; uint32_t mPad04; uint32_t mPad08; };

struct cSPEditorSpeciesProfile
{
    char pad00[0x51c];
    void* mpIconBlock;                                 // +0x51c
};
struct cSPEditorSpeciesManager
{
    cSPEditorSpeciesProfile* GetProfile(const Key& id); // 0x004df550
};
cSPEditorSpeciesManager* FUN_00401090(const Key& id);  // 0x00401090

struct cSPLivingUniverse
{
    char pad00[0x13c];
    uint32_t mPlanetId;                                // +0x13c
    static cSPLivingUniverse* GetActivePlanet();       // 0x01021260
    static void* GetActivePlanetRecord();              // 0x010212a0
    static cSPLivingUniverse* GetPlayerEmpire();       // 0x01021300
    void* GetFocusedCiv();                             // 0x00c71e30
};

int  GetRecorderState();                               // 0x00435e90
void KillSetiEffects(uint32_t hash, uint32_t value);   // 0x00435ed0

struct cTerraformingManager { int GetUnlockedCount(); };           // 0x00bbe470
cTerraformingManager* TerraformingManager();                       // 0x00b3d430
int FUN_00bbce40(void* pPlanetRecord);                             // 0x00bbce40

struct cGameNounAction { virtual void n00(); virtual const char* GetName(int a, int b, int c); };  // +0x04
struct cGameNoun
{
    char pad00[0x34];
    cGameNounAction mAction;                           // +0x34
};
struct cGameNounList { cGameNoun** mpNouns; };
struct cPlayerCivilization
{
    char pad00[0x84];
    uint32_t mId;                                      // +0x84
    int GetNounCount();                                // 0x00bf01e0
    cGameNounList* GetNounList();                      // 0x00bef6c0
};
struct cGameNounManager
{
    cPlayerCivilization* GetPlayerCivilization();      // 0x00b25fb0
};
cGameNounManager* NounManager();                       // 0x00b3d300

struct cAudioSystem
{
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void* GetParam();                          // +0x20
};
cAudioSystem* GetSystemAT();                           // 0x00a206f0

struct cSPPlayerInventory;
struct cSPTool;
struct cSPSimulatorSpaceGame
{
    char pad00[0x14];
    cSPUISpace*  mpUISpace;                            // +0x14
    cSPPlayerInventory* GetPlayerInventory();          // 0x00a1ad60
};
cSPSimulatorSpaceGame* SpaceGameGet();                 // 0x01002bd0
inline cSPUISpace* GetUISpace()                        // inlined everywhere: SpaceGameGet() ? ->mpUISpace : 0
{
    cSPSimulatorSpaceGame* pGame = SpaceGameGet();
    return pGame != 0 ? pGame->mpUISpace : 0;
}
bool GetPropertyAsKeyInstance(const void* pList, const Key* pKey, uint32_t& keyInstance);   // 0x006a12a0
struct cSPPlayerInventory
{
    cSPTool* GetToolFromToolID(const Key& id);         // 0x00ff3d40
};

// Record behind a focused UI object (hash-dispatched in DoFocusChange).
struct cFocusRecord
{
    uint32_t mPad00;                                   // +0x00
    Key      mKey04;                                   // +0x04
    uint32_t mValue0c;                                 // +0x0c
    uint32_t mKind10;                                  // +0x10 (sub kind / key hash)
    uint32_t mSubType14;                               // +0x14
    uint32_t mKind18;                                  // +0x18 (0 = species, 2 = planet, 3 = plant/tool)
    uint8_t  mbFlag1c;                                 // +0x1c
    char     pad1d[3];
    int      mIndex20;                                 // +0x20
};

// Focus change request: +0x18 is the object that receives focus.
struct cFocusChangeData
{
    char pad00[0x18];
    IFocusTarget* mpNewTarget;                         // +0x18
};

class cSPUISpace : public BaseRes, public BaseCount, public BaseMsg { public:
    uint32_t     pad10;               // 0x10
    uint32_t     mDeleteButtonWindow; // 0x14 (focus window id of the delete button)
    ArcC0        m018;                // 0x18
    cString      s01c,
                 s030,
                 s044,
                 s058,
                 s06c,
                 s080,
                 s094,
                 s0a8,
                 s0bc,
                 s0d0,
                 s0e4,
                 s0f8,
                 s10c,
                 s120,
                 s134,
                 s148,
                 s15c,
                 s170,
                 s184,
                 s198,
                 s1ac,
                 s1c0,
                 s1d4,
                 s1e8,
                 s1fc,
                 s210;   // 0x1c .. 0x210 (step 0x14)
    cSPUIGlobalUI* mpGlobalUI;        // 0x224
    ArcRC        m228;                // 0x228
    Arc2         m22c, m230, m234;    // 0x22c
    Arc1         m238;                // 0x238
    uint32_t     pad23c;              // 0x23c
    SpBlock      m240;                // 0x240
    uint32_t     pad244[4];           // 0x244
    Arc2         m254, m258;          // 0x254
    HashTool     m25c;                // 0x25c
    uint32_t     pad26c[4];           // 0x26c
    RawPtr       m27c;                // 0x27c
    uint32_t     pad280[5];           // 0x280
    Arc1         m294, m298, m29c;    // 0x294
    HashB        m2a0;                // 0x2a0
    uint32_t     pad2b0[4];           // 0x2b0
    SpBlock      m2c0;                // 0x2c0
    uint32_t     pad2c4[4];           // 0x2c4
    HashWStr     m2d4;                // 0x2d4
    uint32_t     pad2e4[6];           // 0x2e4
    Arc1         m2fc, m300, m304;    // 0x2fc
    Obj4B5440    m308;                // 0x308
    Arc1         m31c;                // 0x31c
    uint32_t     pad320;              // 0x320
    cString      s324,
                 s338,
                 s34c,
                 s360,
                 s374,
                 s388,
                 s39c,
                 s3b0,
                 s3c4,
                 s3d8,
                 s3ec,
                 s400,
                 s414,
                 s428,
                 s43c,
                 s450,
                 s464,
                 s478,
                 s48c,
                 s4a0,
                 s4b4,
                 s4c8,
                 s4dc,
                 s4f0;   // 0x324 .. 0x4f0 (step 0x14)
    StrVec       v504;                // 0x504
    StrVec       v518;                // 0x518
    uint32_t     pad52c;              // 0x52c
    Obj6CB90     m530;                // 0x530
    DeletableObj* mp568;              // 0x568
    AutoHandler  m56c;                // 0x56c
    Arc1         m580;                // 0x580
    ArcC0        m584;                // 0x584
    Arc1         m588, m58c, m590, m594, m598, m59c, m5a0, m5a4;   // 0x588
    ArcRC        m5a8;                // 0x5a8
    Arc1         m5ac, m5b0, m5b4;    // 0x5ac
    uint32_t     pad5b8[2];           // 0x5b8
    Arc1         m5c0, m5c4;          // 0x5c0
    uint8_t      m5c8[0xb];           // 0x5c8
    uint8_t      mb5d3;               // 0x5d3: delete-button focus state (class hash 0x34ef68d)
    uint8_t      mb5d4;               // 0x5d4: star-object focus state (class hash 0x3e1a6a5)
    uint8_t      pad5d5[3];           // 0x5d5
    SpBlock      m5d8;                // 0x5d8
    uint32_t     pad5dc[4];           // 0x5dc
    Obj4AA120    m5ec;                // 0x5ec
    Arc2         m61c;                // 0x61c
    ObjE0A400    m620;                // 0x620
    Arc1         m694;                // 0x694
    SharedLibVec m698;                // 0x698

    // focus / tooltip plumbing (addresses in the comments)
    cUITimedTooltip* GetTimedTooltip() { return (cUITimedTooltip*)m5a8.p; }
    cSPUIRolloverCivRelationship* GetCivRollover() { return (cSPUIRolloverCivRelationship*)m5a4.p; }
    bool DoFocusChange(IFocusTarget* pOld, const cFocusChangeData* pChange);  // 0x0106fc90
    void SetToolTip(IFocusTarget* pTarget, const char* pText, void* pIconBlock);  // 0x01067c50
    cFocusRecord* FUN_01067ef0(uint32_t typeId);                             // 0x01067ef0
    void FUN_0106f1a0(cFocusRecord* pRecord, int a);                         // 0x0106f1a0
    void* FUN_01066120(uint32_t typeId);                                     // 0x01066120
    void FUN_0106e720(IFocusTarget* pTarget, void* pInfo);                   // 0x0106e720
    void FUN_0106e680(cSPTool* pTool);                                       // 0x0106e680
    uint32_t FUN_0106edc0(cSPTool* pTool);                                   // 0x0106edc0

    virtual ~cSPUISpace();
};

// @ 0x0106f5b0
cSPUISpace::~cSPUISpace()
{
    delete mp568;
    mp568 = 0;
    FUN_0067de40()->Get()->Set(g_16e0d08);
    g_16e0d08 = 0;
}

// ---------------------------------------------------------------------------
// Focus change: pOld loses the focus, pChange->mpNewTarget gains it.  A class hash from the old target's
// vtable decides which piece of the UI reacts; `same` is set when the old and the new target are the same
// object, in which case the widgets keep their state (SetVisible(.., same)).
// ---------------------------------------------------------------------------
// @ 0x0106fc90
bool cSPUISpace::DoFocusChange(IFocusTarget* pOld, const cFocusChangeData* pChange)
{
    cSPLivingUniverse* pPlanet = cSPLivingUniverse::GetActivePlanet();
    if (pPlanet != 0)
        g_16e0d08->mPlanetId = pPlanet->mPlanetId;

    IFocusTarget* pNew = pChange->mpNewTarget;
    if (pNew != 0)
        pNew->OnFocusLost();

    const bool same = (pOld == pNew);
    if (GetTimedTooltip() != 0)
        GetTimedTooltip()->Hide();

    const uint32_t typeId = pOld->GetTypeId();
    const uint32_t classHash = pOld->GetClassHash();

    bool refreshAudio = false;       // the delete button and the editor focus end in the tooltip / audio refresh

    if (classHash == 0x5232c00)
    {
        // editor plane windows: the class id picks two windows that become visible together
        cSPUIWindow* pWindowA = 0;
        cSPUIWindow* pWindowB = 0;
        if (typeId == 0x5233980) {
            pWindowA = mpGlobalUI->FindWindowByID(0x51dec70);
            pWindowB = mpGlobalUI->FindWindowByID(0x5243538);
        }
        else if (typeId == 0x52339a8) {
            pWindowA = mpGlobalUI->FindWindowByID(0x51decd0);
            pWindowB = mpGlobalUI->FindWindowByID(0x5243548);
        }
        else if (typeId == 0x52339c0) {
            pWindowA = mpGlobalUI->FindWindowByID(0x51decd8);
            pWindowB = mpGlobalUI->FindWindowByID(0x5243558);
        }
        else {
            pWindowA = (cSPUIWindow*)pNew;
            pWindowB = (cSPUIWindow*)pNew;
        }
        if (pWindowA != 0 && pWindowB != 0)
        {
            pWindowA->SetVisible(true, same);
            pWindowB->SetVisible(true, same);
        }
    }
    else if (classHash == 0x34ef68d)
    {
        mb5d3 = same;
        if (same)
        {
            // place the delete button window on the focused object
            float anchor[2] = { 0.0f, 0.0f };
            float pos[4];
            pOld->GetFocusTransform(anchor[0], anchor[1], pos);
            cSPUIWindow* pDeleteButton = mpGlobalUI->FindWindowByID(0xb2001000);
            cSPUIWidget* pContent = pDeleteButton->GetContent();
            pContent->SetLayoutPosition(pos[0], pos[1], pos);
            pDeleteButton->SetPosition(pos[0], pos[1]);
            mDeleteButtonWindow = pOld->GetTypeId();
            refreshAudio = true;
        }
        else
            goto done;
    }
    else if (classHash == 0x37e9018)
    {
            if (!same)
                goto done;
            cFocusRecord* pRecord = FUN_01067ef0(typeId);
            if (pRecord == 0)
                goto done;
            FUN_0106f1a0(pRecord, 0);
            if (pRecord->mKind18 == 0)
            {
                // species / planet record: the localised name becomes the tooltip
                KillSetiEffects(0xd0840db7, GetRecorderState());
                cSPEditorSpeciesProfile* pProfile =
                    FUN_00401090(pRecord->mKey04)->GetProfile(pRecord->mKey04);
                if (pProfile == 0)
                    goto done;
                g_16e0d08->mPad14 = 0;
                g_16e0d08->mpRecord = pProfile;
                cString* pText = (pRecord->mKind10 != 0) ? &s478 : &s48c;
                if (pRecord->mbFlag1c == 0)
                    SetToolTip(pOld, pText->GetText(0, 0), 0);
                else
                {
                    Key key = pRecord->mKey04;
                    key.mHash = 0x2f7d0004;
                    SetToolTip(pOld, pText->GetText(&key, 0), pProfile->mpIconBlock);
                }
            }
            else if (pRecord->mKind18 == 2)
            {
                // planet statistics: the last unlocked planet reads differently
                const int numPlanets = FUN_00bbce40(cSPLivingUniverse::GetActivePlanetRecord()) + 1;
                cString* pText = (pRecord->mIndex20 == numPlanets) ? &s388 : &s39c;
                SetToolTip(pOld, pText->GetText(0, 0), 0);
            }
            else if (pRecord->mKind18 == 3)
            {
                // editor verb icon: the plant / tool size picks the tooltip string
                cString* pText = 0;
                if (pRecord->mKind10 == 0)
                {
                    if (pRecord->mSubType14 == 0x29c388a)      pText = &s338;
                    else if (pRecord->mSubType14 == 0x3a8be428) pText = &s34c;
                    else if (pRecord->mSubType14 == 0x6d60a1cc) pText = &s324;
                }
                else if (pRecord->mKind10 == 1)                pText = &s360;
                else if (pRecord->mKind10 == 2)                pText = &s374;
                if (pText == 0)
                    goto done;
                SetToolTip(pOld, pText->GetText(0, 0), 0);
            }
            else
                goto done;
    }
    else if (classHash == 0x3e1a6a5)                        // star object
    {
        mb5d4 = same;
    }
    else if (classHash == 0x678fa20)
    {
        // terraforming manager: count the unlocked planets to pick the tooltip string
        if (!same)
            goto done;
        const int index = (int)typeId - 0x535cbd8;
        const int numUnlocked = TerraformingManager()->GetUnlockedCount();
        cPlayerCivilization* pCiv = NounManager()->GetPlayerCivilization();
        if (numUnlocked > index)
        {
            if (pCiv != 0 && index < pCiv->GetNounCount())
            {
                cGameNoun* pNoun = pCiv->GetNounList()->mpNouns[index];
                SetToolTip(pOld, pNoun->mAction.GetName(0, 0, 0), 0);
                goto done;
            }
            SetToolTip(pOld, s4f0.GetText(0, 0), 0);
            goto done;
        }
        SetToolTip(pOld, s4dc.GetText(0, 0), 0);
        goto done;
    }
    else if (classHash == 0x70648eae)
    {
        refreshAudio = true;
    }
    else
    {
        // any other class: a civilization rollover follows the planet's focused civ
        if (typeId != 0x36c0957)
            goto done;
        cSPLivingUniverse* pActive = cSPLivingUniverse::GetActivePlanet();
        if (pActive == 0)
            goto done;
        cPlayerCivilization* pCiv = (cPlayerCivilization*)pActive->GetFocusedCiv();
        if (pCiv != 0 && pCiv != (cPlayerCivilization*)cSPLivingUniverse::GetPlayerEmpire() && same)
            GetCivRollover()->ShowRelationshipRollover(pOld, pCiv->mId, false);
        else
            GetCivRollover()->HideRelationshipRollover();
    }

    // the delete button / editor focus also refreshes the editor info and the tooltip audio
    if (refreshAudio && same)
    {
        void* pInfo = FUN_01066120(typeId);
        FUN_0106e720(pOld, pInfo);
        if ((pOld->GetFocusFlags() & 2) != 0)
        {
            cAudioSystem* pAudio = GetSystemAT();
            KillSetiEffects(0xe784e681, pAudio != 0 ? (uint32_t)pAudio->GetParam() : 0);
        }
        else
        {
            cAudioSystem* pAudio = GetSystemAT();
            KillSetiEffects(0xb284b22, pAudio != 0 ? (uint32_t)pAudio->GetParam() : 0);
        }
    }

done:
    if (pNew != 0)
        pNew->Release();
    return false;
}

// The property key the tool chest reads (0x0678b59a): a global Key handed to GetPropertyAsKeyInstance.
extern const Key g_propKeyToolSlot;

// @ 0x010701e0
uint32_t FUN_010701e0(const void* pList)
{
    uint32_t keyInstance = 0;
    Key toolId;
    if (GetPropertyAsKeyInstance(pList, &g_propKeyToolSlot, keyInstance))
    {
        toolId.mHash = keyInstance;
        toolId.mPad04 = 0;
        toolId.mPad08 = 0;
        cSPPlayerInventory* pInventory = SpaceGameGet()->GetPlayerInventory();
        cSPTool* pTool = pInventory->GetToolFromToolID(toolId);
        if (pTool != 0)
        {
            GetUISpace()->FUN_0106e680(pTool);
            return GetUISpace()->FUN_0106edc0(pTool);
        }
        return 0;
    }
    return 0;
}
}   // namespace SP
