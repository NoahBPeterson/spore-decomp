// Slice s00b1d870 -- Simulator object factories, Gonzago/window toggles, terrain accessors.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

void* operator new(unsigned int size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
int GetCurrentGameMode();   // 0x00b5b800
int GetPlayerEmpireID();    // 0x1021090

// ------------------------------------------------------------ tiny accessors
struct VObj {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual int  v0c(int a);
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual int  v20();
};

// @ 0x00b1e500
bool EqualsStreamId(VObj* o, int id) {
    return o->v20() == id;
}

// @ 0x00b1e520
bool CheckId(VObj* o, int a) {
    return o->v0c(a) != 0;
}

namespace Simulator {
struct cSpaceInventoryItem {
    bool mFlag;
    bool IsAvailableInCurrentPlanet();
    void* SetAvailable();
};
}
// @ 0x00b1e4d0
bool Simulator::cSpaceInventoryItem::IsAvailableInCurrentPlanet() { return false; }
// @ 0x00b1e540
void* Simulator::cSpaceInventoryItem::SetAvailable() { mFlag = true; return this; }

// ------------------------------------------------------------ object factories
struct cCelestialBody { void* ctor(int a); };
struct cPlanet { void* ctor(); };
struct cVisiblePlanet { void* ctor(); };
struct cSolarSystem { void* ctor(); };
struct cTribePlanner { void* ctor(); };
struct cGenericPressureEvent { void ctor(); };
extern void* gVtblPressureA;
extern void* gVtblPressureB;
extern void* gVtblPressureC;

// @ 0x00b1eba0
void* New_cCelestialBody() {
    cCelestialBody* p = (cCelestialBody*)operator new(0xcc, "Simulator/cCelestialBody", 0, 0, 0, 0);
    if (p)
        return p->ctor(-1);
    return 0;
}

// @ 0x00b1f590
void* New_cPlanet() {
    cPlanet* p = (cPlanet*)operator new(0x1c8, "Simulator/cPlanet", 0, 0, 0, 0);
    if (p) {
        void* q = p->ctor();
        if (q)
            return (void*)((char*)q + 0xd4);
    }
    return 0;
}

// @ 0x00b1f5d0
void* New_cVisiblePlanet() {
    cVisiblePlanet* p = (cVisiblePlanet*)operator new(0x10c, "Simulator/cVisiblePlanet", 0, 0, 0, 0);
    if (p) {
        void* q = p->ctor();
        if (q)
            return (void*)((char*)q + 0xd4);
    }
    return 0;
}

// @ 0x00b1f640
void* New_cSolarSystem() {
    cSolarSystem* p = (cSolarSystem*)operator new(0x54, "Simulator/cSolarSystem", 0, 0, 0, 0);
    if (p) {
        void* q = p->ctor();
        if (q)
            return (void*)((char*)q + 8);
    }
    return 0;
}

// @ 0x00b1f790
void* New_cTribePlanner() {
    cTribePlanner* p = (cTribePlanner*)operator new(0x7c, "Simulator/cTribePlanner", 0, 0, 0, 0);
    if (p) {
        void* q = p->ctor();
        if (q)
            return (void*)((char*)q + 8);
    }
    return 0;
}

// @ 0x00b1e820
void* New_cGenericPressureEvent() {
    cGenericPressureEvent* p = (cGenericPressureEvent*)operator new(0x1f8, "Simulator/cGenericPressureEvent", 0, 0, 0, 0);
    if (p) {
        p->ctor();
        *(void**)p = &gVtblPressureA;
        *(void**)((char*)p + 4) = &gVtblPressureB;
        *(void**)((char*)p + 0x34) = &gVtblPressureC;
        *(uint32_t*)((char*)p + 0x1f0) = 0x78;
        return p;
    }
    return 0;
}

// @ 0x00b1fc30
void* New_cMissionHappinessEvent() {
    cGenericPressureEvent* p = (cGenericPressureEvent*)operator new(0x1f0, "Simulator/cMissionHappinessEvent", 0, 0, 0, 0);
    if (p) {
        p->ctor();
        *(void**)p = &gVtblPressureA;
        *(void**)((char*)p + 4) = &gVtblPressureB;
        *(void**)((char*)p + 0x34) = &gVtblPressureC;
        return p;
    }
    return 0;
}

// @ 0x00b1f9d0
int GetPlayerEmpireOrMinus1() {
    int id = -1;
    switch (GetCurrentGameMode()) {
    case 0x1654c01:
    case 0x1654c02:
    case 0x1654c04:
    case 0x1654c05:
    case 0x1654c10:
        id = GetPlayerEmpireID();
        break;
    }
    return id;
}

namespace UTFWin {
struct Window { bool Initialize(); };
}
// @ 0x00b1fbf0
bool UTFWin::Window::Initialize() { return true; }

// ------------------------------------------------------------ window toggles
struct SubObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78();
    virtual void v7c(int, int);
};
struct WMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual void v58(int, void*);
    virtual void v5c(int, void*);
};
void* WindowManager();   // 0x0067caa0

struct Host {
    char  pad00[0x38];
    void* mpSub;   // 0x38
    void Fn1();
    void Fn2();
};

// @ 0x00b1db60  (complete, near miss: window-manager toggle)
void Host::Fn1() {
    void* p = mpSub;
    if (p) {
        ((SubObj*)((char*)p + 4))->v7c(1, 1);
        ((WMgr*)WindowManager())->v58(1, mpSub ? (char*)mpSub + 4 : 0);
        void* q = mpSub;
        if (q) {
            ((WMgr*)WindowManager())->v58(0, (char*)q + 4);
            return;
        }
        ((WMgr*)WindowManager())->v58(0, 0);
    }
}

// @ 0x00b1dbd0  (complete, near miss)
void Host::Fn2() {
    void* p = mpSub;
    if (p) {
        ((SubObj*)((char*)p + 4))->v7c(1, 0);
        ((WMgr*)WindowManager())->v5c(1, mpSub ? (char*)mpSub + 4 : 0);
        void* q = mpSub;
        if (q) {
            ((WMgr*)WindowManager())->v5c(0, (char*)q + 4);
            return;
        }
        ((WMgr*)WindowManager())->v5c(0, 0);
    }
}

// ------------------------------------------------------------ terrain accessors
// The sphere accessor returns a pointer and 0x00c75420 is a THISCALL on it (the
// original reloads ecx with the returned eax before the call).
struct TerrainSphere {
    int FUN_00C75420();
};
struct cTerrainEditor { TerrainSphere* GetCurrentTerrainSphere(); };
cTerrainEditor* SP_NounManager();   // 0x00b3d300

struct TerrainMgr {
    char pad00[0x20];
    void* mId;              // 0x20
    char padTo90[0x90 - 0x24];
    int  Fn1(int id, bool flag);
    int  Fn2();
};

// @ 0x00b1daf0  (complete, near miss)
int TerrainMgr::Fn1(int id, bool flag) {
    int idx = 1;
    if (flag) {
        cTerrainEditor* te = SP_NounManager();
        TerrainSphere* s = te->GetCurrentTerrainSphere();
        if (s)
            idx = s->FUN_00C75420();
    }
    if ((unsigned)(id - 0x1654c00) <= 6)
        return ((int*)this)[idx + (id - 0x1654bfb) * 3];
    if (id != 0x1654c10)
        return 0;
    return *(int*)((char*)this + 0x90 + idx * 4);
}

// @ 0x00b1de80  (complete, near miss)
int TerrainMgr::Fn2() {
    void* id = mId;
    int idx = 1;
    cTerrainEditor* te = SP_NounManager();
    TerrainSphere* s = te->GetCurrentTerrainSphere();
    if (s)
        idx = s->FUN_00C75420();
    if ((unsigned)((int)id - 0x1654c00) <= 6)
        return ((int*)this)[idx + ((int)id - 0x1654bfb) * 3];
    if (id != (void*)0x1654c10)
        return 0;
    return *(int*)((char*)this + 0x90 + idx * 4);
}

// @ 0x00b1dfc0  (complete, near miss: refcounted member reset)
struct RObj {
    virtual void v00();
    virtual void v04();          // slot 1: release
    virtual char v08(int a);     // slot 2: query, 1 arg
};
struct RefMgr {
    virtual void v00();
    virtual void v04();
    virtual char v08(int key, int a, void* out);   // slot 2: query by key
};
struct RefHolder {
    char pad00[0x30];
    RefMgr* mpMgr;   // 0x30
    RObj*   mpObj;   // 0x34
    void Reset();
};
void RefHolder::Reset() {
    RObj** slot = &mpObj;
    RefMgr* mg = mpMgr;
    RObj* p = *slot;
    if (p) {
        *slot = 0;
        p->v04();
    }
    if (mg->v08(0xf08ce134, 0, slot)) {
        RObj* q = *slot;
        q->v08(0);
        q = *slot;
        if (q) {
            *slot = 0;
            q->v04();
        }
    }
}

// =====================================================================
// The paint-system host itself (constructor through play-mode change) is
// reconstructed at the end of this file.
// =====================================================================

// ------------------------------------------------------------ Gonzago layout/effect toggle
// SP::SysGUI singleton at 0x0167c988 (methods below take their text by pointer id)
struct SysGUI {
    void ShowLayout(const void* pText, int x, int y);   // 0x00a6ca00
    void HideLayout();                                  // 0x00c2e4e0
};
#define SYS_GUI ((SysGUI*)0x0167c988)

struct LayoutHolder {
    char pad00[0x10];
    bool mbLayoutActive;   // +0x10
};
struct LayoutOwner {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual LayoutHolder* GetLayout();   // slot 7 (+0x1c)
};
LayoutOwner* GetLayoutOwner();   // 0x0067dd50

// @ 0x00b1f960
void FUN_b1f960(bool enable) {
    if (GetLayoutOwner()->GetLayout()->mbLayoutActive)
        return;
    if (enable) {
        SYS_GUI->ShowLayout((const void*)0x0145e9e8, 500, 400);
        SYS_GUI->ShowLayout((const void*)0x0000000a, 10, 1);
    } else {
        SYS_GUI->HideLayout();
    }
}

// ------------------------------------------------------------ subsystem init-state query
bool __stdcall CheckGonzagoSubsystemInitState(int mode);   // 0x00b5b840 (ecx = the listener)

// intrusive list node: head node lives in the owner, mpPrev of an empty list is the head
struct ListNode2 {
    ListNode2* mpNext;   // +0x00
    ListNode2* mpPrev;   // +0x04

    // links this node in front of pWhere
    void LinkBefore(ListNode2* pWhere) {
        mpNext = pWhere;
        mpPrev = pWhere->mpPrev;
        pWhere->mpPrev = this;
        mpPrev->mpNext = this;
    }
};

struct InitStateOwner {
    char      pad00[0x74];
    ListNode2 mLoading;                            // +0x74
    bool SubsystemReady(int mode);
    void Load(struct IReader* pReader);
};

// @ 0x00b1fbb0
bool InitStateOwner::SubsystemReady(int mode) {
    const bool bReady = CheckGonzagoSubsystemInitState(mode);
    if (mode == 0x01654c08 || mode == 0x02ccd1d2) {
        if (bReady) {
            ListNode2* pHead = &mLoading;
            if (pHead->mpPrev == pHead)
                return true;
        }
        return false;
    }
    return bReady;
}

// =====================================================================
// Gonzago paint-system host: transition state machine, play-mode
// environment change and the transition-data loader.
// =====================================================================

inline void* operator new(unsigned int, void* pWhere) { return pWhere; }

// ------------------------------------------------------------ engine objects
// refcounted engine object: vtable slots 0/1/2 = AddRef/Release/Destroy
struct RCObj {
    virtual int  AddRef();
    virtual void Release();
    virtual void Destroy();
};

// transition data handed to the post-process effect (filled by IEffect::Query)
struct ITransitionData {
    virtual int  AddRef();        // +0x00
    virtual void Release();       // +0x04
    virtual void Reset(int arg);  // +0x08
    virtual void Finish(int arg); // +0x0c
};

// post-process / transition effect owned by the effects manager
struct IEffect {
    virtual int  AddRef();                                              // +0x00
    virtual void Release();                                             // +0x04
    virtual bool Query(uint32_t key, int arg, ITransitionData** ppOut);  // +0x08
    virtual void e0c(); virtual void e10(); virtual void e14(); virtual void e18();
    virtual void e1c(); virtual void e20(); virtual void e24(); virtual void e28();
    virtual void e2c(); virtual void e30();
    virtual void Stop();                                                // +0x34
};

// SP::cEditorLaunchData: what an editor launch consumes
struct IEditorData {
    virtual void d00();        // +0x00
    virtual int  AddRef();     // +0x04
    virtual void Destroy();    // +0x08
    uint32_t mUnused04;        // +0x04
    uint32_t mUnused08;        // +0x08
    uint32_t mEffectId;        // +0x0c  transition id handed to the ticker
};

// opaque engine singleton: only the vtable slots this slice dispatches on
struct IFat {
    virtual void   s00();
    virtual IFat*  s01();                                    // window manager: active manager
    virtual void   s02(); virtual void s03();
    virtual IFat*  s04();                                    // window face: scene
    virtual void   s05();
    virtual void*  s06();                                    // reader: underlying stream
    virtual void   s07();
    virtual IFat*  s08();                                    // reader: stream owner
    virtual void   s09(void* pHandler, uint32_t id);         // message server: add handler
    virtual void   s10(int code);                            // play-mode facade: change environment
    virtual void   s11(uint32_t key, uint32_t tag, void* pOut);
    virtual void   s12(); virtual void s13();
    virtual int    s14(const char* pName);                   // play-mode facade: post mode name
    virtual void   s15(); virtual void s16(); virtual void s17();
    virtual void   s18(int id);
    virtual RCObj* s19(uint32_t id, const char* pName);      // effects manager: find effect
    virtual void   s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void   s24(float* pVector);                      // window face: set position
    virtual void   s25(); virtual void s26(); virtual void s27();
    virtual void   s28(); virtual void s29(); virtual void s30();
    virtual void   s31(int a, int b);                        // window face: set flags
    virtual void   s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void   s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void   s40(); virtual void s41(); virtual void s42(); virtual void s43();
    virtual void   s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void   s48(); virtual void s49(); virtual void s50(); virtual void s51();
    virtual void   s52(); virtual void s53();
    virtual void   s54(void* pArg);                          // window manager: set active window
    virtual void   s55(void* pArg);                          // window face: release scene
    virtual void   s56(); virtual void s57(); virtual void s58(); virtual void s59();
    virtual void   s60(); virtual void s61(); virtual void s62(); virtual void s63();
};

// serializer reader: slot 8 wraps the byte stream, slot 10 reads one tagged object
struct IReader {
    virtual void  r00(); virtual void r01(); virtual void r02(); virtual void r03();
    virtual void  r04(); virtual void r05(); virtual void r06(); virtual void r07();
    virtual IFat* r08();
    virtual void  r09();
    virtual void  r10(uint32_t key, void** ppOut, int flags);
};

// ------------------------------------------------------------ engine entry points
IFat* GetPlayModeFacade();                         // 0x0067dd20
IFat* EffectsManagerPtr();                         // 0x0067ddd0
IFat* PropertyManager();                           // 0x0067de30
IFat* MessageServer();                             // 0x0067dcc0
IFat* gTickerManager;                              // 0x015e4ef0
bool  IsWorldLayoutFlagSet(int flag);              // 0x00685520
void  EditorLaunch(IEditorData* pData);            // 0x005a9200
void* WindowAllocator();                           // 0x009512c0
void* WindowAlloc(int size, int count, const char* pName, void* pAllocator);  // 0x009512d0
void  ReadInt32(void* pStream, int* pValues, int nCount, int flags);          // 0x0093a780

struct ISimTicker {
    char SmoothTickToggle();   // 0x00801400
    void Enable(char enable);  // 0x010829f0
};
ISimTicker* SimTicker();       // 0x00b3d330

struct cGameTimeManager {
    void IncPauseGate(int gate);   // 0x00b32220
    void DecPauseGate(int gate);   // 0x00b32250
};
cGameTimeManager* GameTimeManager();   // 0x00b3d380

// ------------------------------------------------------------ transition window
// EA::UTFWin::Window: two interface vtables (serializable at +0x00, window at +0x04)
class WindowSerializable : public RCObj {
};
class WindowFace : public IFat {
};
class Window : public WindowSerializable, public WindowFace {
public:
    Window();                                   // 0x00962a10
};

// the transition-blocking window the paint system parks over the scene
class TransitionWindow : public Window {
public:
    TransitionWindow() {}
    WindowFace* Face() { return static_cast<WindowFace*>(this); }
};

// ------------------------------------------------------------ SP::cGonzagoSubsystem base
struct cIGonzagoSubsystem {
    virtual void g0(); virtual void g1(); virtual void g2(); virtual void g3();
    virtual void g4(); virtual void g5();
};
struct RefCountSub {
    virtual int  AddRef();
    virtual void Release();
};
class cGonzagoSubsystem : public cIGonzagoSubsystem, public RefCountSub {
public:
    cGonzagoSubsystem();      // 0x00b5b960
    ~cGonzagoSubsystem();     // 0x00b5b9a0
private:
    char pad00[0x14];         // 0x08..0x1b
};

// message handler base published at +0x1c of the host
class PaintHandler {
public:
    virtual void Dispatch(uint32_t id, uint32_t data);
    bool HandleGonzagoMessage(uint32_t id, uint32_t data);   // 0x00b1e020

    int   m20;                        // 0x04  current play mode
    int   m24;                        // 0x08  pending play mode
    bool  mb28;                       // 0x0c  environment change happened
    bool  mb29;                       // 0x0d
    short pad2a;                      // 0x0e
    IEditorData*      mpTransition;        // 0x10  pending editor launch data
    IEffect*          mpTransitionEffect;  // 0x14  world transition effect
    ITransitionData*  mpTransitionData;    // 0x18  live transition data
    TransitionWindow* mpBlockingWin;       // 0x1c  blocking window over the scene
};

// ------------------------------------------------------------ the paint-system host
class PaintSystemHost : public cGonzagoSubsystem, public PaintHandler {
public:
    PaintSystemHost();                              // 0x00b1d870
    ~PaintSystemHost() throw();                     // 0x00b1d970
    void ClearTransition();                         // 0x00b1da20
    void InitTransition();                          // 0x00b1dc60
    void SetTransitionData(IEditorData* pData);     // 0x00b1dee0
    bool SetPlayMode(int mode);                     // 0x00b1e410

    PaintHandler* HandlerView() { return static_cast<PaintHandler*>(this); }
    static PaintSystemHost* HostOf(PaintHandler* pHandler) { return static_cast<PaintSystemHost*>(pHandler); }

    RCObj* mEffects[21];                   // 0x3c  per-mode transition effects
    RCObj* mWorldEffects[3];               // 0x90  world-layout transition effects
};

// @ 0x00b1d870
PaintSystemHost::PaintSystemHost()
{
    m20 = -1;
    m24 = -1;
    mb28 = false;
    mb29 = false;
    mpTransition = 0;
    mpTransitionEffect = 0;
    mpTransitionData = 0;
    mpBlockingWin = 0;
    for (int i = 0; i < 21; ++i)
        mEffects[i] = 0;
    for (int i = 0; i < 3; ++i)
        mWorldEffects[i] = 0;
}

// destroys an array of refcounted members from the last element back
static void ReleaseRefArray(RCObj** pArray, int nCount)
{
    for (int i = nCount - 1; i >= 0; --i) {
        RCObj* pEffect = pArray[i];
        if (pEffect != 0)
            pEffect->Release();
    }
}

// @ 0x00b1d970
PaintSystemHost::~PaintSystemHost() throw()
{
    ReleaseRefArray(mWorldEffects, 3);
    ReleaseRefArray(mEffects, 21);
    if (mpBlockingWin)
        mpBlockingWin->Release();
    if (mpTransitionData)
        mpTransitionData->Release();
    if (mpTransitionEffect)
        mpTransitionEffect->Release();
    if (mpTransition)
        mpTransition->Destroy();
}

// @ 0x00b1da20
void PaintSystemHost::ClearTransition()
{
    if (mpBlockingWin) {
        IFat* pScene = mpBlockingWin->Face()->s04();
        if (pScene != 0)
            pScene->s55(mpBlockingWin ? mpBlockingWin->Face() : 0);
        TransitionWindow* pOldWin = mpBlockingWin;
        if (pOldWin != 0) {
            mpBlockingWin = 0;
            pOldWin->Release();
        }
    }
    if (mpTransitionEffect != 0) {
        mpTransitionEffect->Stop();
        IEffect* pOldEffect = mpTransitionEffect;
        if (pOldEffect != 0) {
            mpTransitionEffect = 0;
            pOldEffect->Release();
        }
    }
    RCObj** pSlot = mEffects;
    for (int row = 0; row < 7; ++row) {
        for (int i = 0; i < 3; ++i, ++pSlot) {
            RCObj* pEffect = *pSlot;
            if (pEffect != 0) {
                *pSlot = 0;
                pEffect->Release();
            }
        }
    }
    if (IsWorldLayoutFlagSet(2)) {
        RCObj** pWorldSlot = mWorldEffects;
        for (int i = 0; i < 3; ++i, ++pWorldSlot) {
            RCObj* pEffect = *pWorldSlot;
            if (pEffect != 0) {
                *pWorldSlot = 0;
                pEffect->Release();
            }
        }
    }
}

// property table of the transition effects: { tag, id0, id1, id2 } per play mode (0x0145d5c0)
struct EffectRow {
    uint32_t mTag;
    uint32_t mIds[3];
};
extern const EffectRow gEffectRows[7];        // 0x0145d5c0
extern const EffectRow gWorldEffectRow;       // 0x01568448
extern void* gVtblBlockingWin;                // 0x0145d758
extern void* gVtblBlockingWinFace;            // 0x0145d638
const char kBlockingWinName[] = "UI/cTransitionBlockingWin";
const char kTransitionWorldName[] = "TransitionEffectWorld";

// @ 0x00b1dc60
void PaintSystemHost::InitTransition()
{
    IFat* pProperties = PropertyManager();
    int nSlot = 14;
    const uint32_t* pIds = gEffectRows[0].mIds;
    while (pIds < gEffectRows[6].mIds + 4) {
        const uint32_t nTag = pIds[-1];
        const uint32_t* pId = pIds;
        for (int i = 1; i <= 3; ++i, ++pId) {
            const uint32_t nId = *pId;
            if (nId != 0) {
                RCObj*& rSlot = mEffects[nSlot + i - 15];
                RCObj* pOldEffect = rSlot;
                if (pOldEffect != 0) {
                    rSlot = 0;
                    pOldEffect->Release();
                }
                pProperties->s11(nId, nTag, &rSlot);
            }
        }
        nSlot += 3;
        pIds += 4;
    }
    if (IsWorldLayoutFlagSet(2)) {
        const uint32_t nTag = gWorldEffectRow.mTag;
        const uint32_t* pWorldIds = gWorldEffectRow.mIds;
        for (int i = 1; i <= 3; ++i) {
            const uint32_t nId = pWorldIds[i - 1];
            if (nId != 0) {
                RCObj*& rWorldSlot = mWorldEffects[i - 1];
                RCObj* pOldEffect = rWorldSlot;
                if (pOldEffect != 0) {
                    rWorldSlot = 0;
                    pOldEffect->Release();
                }
                pProperties->s11(nId, nTag, &rWorldSlot);
            }
        }
    }
    IEffect* pNewEffect = (IEffect*)EffectsManagerPtr()->s19(0x05e5284a, kTransitionWorldName);
    IEffect* pOldEffect = mpTransitionEffect;
    if (pNewEffect != pOldEffect) {
        if (pNewEffect != 0)
            pNewEffect->AddRef();
        mpTransitionEffect = pNewEffect;
        if (pOldEffect != 0)
            pOldEffect->Release();
    }
    IFat* pManager = ((IFat*)WindowManager())->s01();
    if (pManager != 0) {
        TransitionWindow* pNewWin = (TransitionWindow*)WindowAlloc(
            0x20c, 4, kBlockingWinName, WindowAllocator());
        pNewWin = pNewWin ? new (pNewWin) TransitionWindow : 0;
        TransitionWindow* pOldWin = mpBlockingWin;
        if (pNewWin != pOldWin) {
            if (pNewWin != 0)
                pNewWin->AddRef();
            mpBlockingWin = pNewWin;
            if (pOldWin != 0)
                pOldWin->Release();
        }
        float vPosition[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        mpBlockingWin->Face()->s24(vPosition);
        mpBlockingWin->Face()->s31(1, 0);
        pManager->s54(mpBlockingWin ? mpBlockingWin->Face() : 0);
    }
}

// @ 0x00b1dee0
void PaintSystemHost::SetTransitionData(IEditorData* pData)
{
    IEditorData* pOldData = mpTransition;
    if (pData != pOldData) {
        if (pData != 0)
            pData->AddRef();
        mpTransition = pData;
        if (pOldData != 0)
            pOldData->Destroy();
    }
    gTickerManager->s18((int)mpTransition->mEffectId);
    ITransitionData* pOldTransition = mpTransitionData;
    IEffect* pEffect = mpTransitionEffect;
    if (pOldTransition != 0) {
        mpTransitionData = 0;
        pOldTransition->Release();
    }
    if (pEffect->Query(0x4cf52822, 0, &mpTransitionData)) {
        mpTransitionData->Reset(0);
        PaintHandler* pHandler = HandlerView();
        MessageServer()->s09(pHandler, 0x0462c656);
        cGameTimeManager* pTimeManager = GameTimeManager();
        pTimeManager->IncPauseGate(0x04bf38a6);
        ((Host*)this)->Fn1();
        return;
    }
    EditorLaunch(mpTransition);
    IEditorData* pLaunchData = mpTransition;
    if (pLaunchData != 0) {
        mpTransition = 0;
        pLaunchData->Destroy();
    }
}

// @ 0x00b1e020
bool PaintHandler::HandleGonzagoMessage(uint32_t id, uint32_t data)
{
    (void)data;
    if (id == 0x0462c656) {
        if (mpTransitionData != 0) {
            MessageServer()->s11((uint32_t)(PaintSystemHost::HostOf(this) ? this : 0),
                                 0x0462c656, (void*)0xffffd8f1u);
            mpTransitionData->Finish(0);
            ITransitionData* pOldTransition = mpTransitionData;
            if (pOldTransition != 0) {
                mpTransitionData = 0;
                pOldTransition->Release();
            }
            ((Host*)PaintSystemHost::HostOf(this))->Fn2();
            EditorLaunch(mpTransition);
            IEditorData* pLaunchData = mpTransition;
            if (pLaunchData != 0) {
                mpTransition = 0;
                pLaunchData->Destroy();
            }
            GameTimeManager()->DecPauseGate(0x04bf38a6);
        }
    }
    return false;
}

// ------------------------------------------------------------ play-mode environment change
// play-mode ids: 0C00 cell, 0C01 creature, 0C02 tribe, 0C03 civilisation, 0C04 space,
// 0C06 level editor, 0C08 load game; 0DBDBA1 is the "enter editor" request.
static int PostModeName(const char* pName) {
    return GetPlayModeFacade()->s14(pName);
}

// minimal eastl-style string: the mode name is assembled on the stack
char gEmptyString;                                     // 0x01667bac
class EAString {
public:
    char* mpBegin;        // +0x00
    char* mpEnd;          // +0x04
    char* mpCapacity;     // +0x08
    uint32_t mPad0c;      // +0x0c  keeps the stack object 16-byte aligned

    void Init() {
        mpBegin = &gEmptyString;
        mpEnd = mpBegin;
        mpCapacity = &gEmptyString + 1;
    }
    void Release() {
        if (mpCapacity - mpBegin > 1 && mpBegin != 0)
            operator delete(mpBegin);
    }
    EAString& assign(const char* pText);   // 0x006a4380
    EAString& append(const char* pText);   // 0x0060c4e0
    const char* c_str() const { return mpBegin; }
};

// @ 0x00b1e0c0
int ChangeEnvironmentMode(int fromMode, int toMode)
{
    if (toMode == 0x01654c08)
        return GetPlayModeFacade()->s14("LoadGame");
    if (fromMode == 0x01654c06) {
        switch (toMode) {
        case 0x01654c00: return GetPlayModeFacade()->s14("CellGameFromLevelEditor");
        case 0x01654c01: return GetPlayModeFacade()->s14("CreatureGameFromLevelEditor");
        case 0x01654c02: return GetPlayModeFacade()->s14("TribeGameFromLevelEditor");
        case 0x01654c04: return GetPlayModeFacade()->s14("CivilisationGameFromLevelEditor");
        case 0x01654c05: return GetPlayModeFacade()->s14("SpaceGameFromLevelEditor");
        }
    }
    if (toMode == 0x00dbdba1) {
        switch (fromMode) {
        case 0x01654c00: return GetPlayModeFacade()->s14("CellEditor");
        case 0x01654c01: return GetPlayModeFacade()->s14("CreatureEditor");
        case 0x01654c02: return GetPlayModeFacade()->s14("HutEditor");
        case 0x01654c04: return GetPlayModeFacade()->s14("BuildingEditor");
        case 0x01654c05: return GetPlayModeFacade()->s14("PlanetEditor");
        }
    } else if (toMode == 0x01654c06) {
        switch (fromMode) {
        case 0x01654c00: return GetPlayModeFacade()->s14("LevelEditorFromCellGame");
        case 0x01654c01: return GetPlayModeFacade()->s14("LevelEditorFromCreatureGame");
        case 0x01654c02: return GetPlayModeFacade()->s14("LevelEditorFromTribeGame");
        case 0x01654c04: return GetPlayModeFacade()->s14("LevelEditorFromCivilisationGame");
        case 0x01654c05: return GetPlayModeFacade()->s14("LevelEditorFromSpaceGame");
        }
    }
    EAString modeName;
    modeName.Init();
    switch (toMode) {
    case 0x01654c00: modeName.assign("CellGame"); break;
    case 0x01654c01: modeName.assign("CreatureGame"); break;
    case 0x01654c02: modeName.assign("TribeGame"); break;
    case 0x01654c04: modeName.assign("CivilisationGame"); break;
    case 0x01654c05: modeName.assign("SpaceGame"); break;
    }
    switch (fromMode) {
    case 0x01654c00: modeName.append("FromCellGame"); break;
    case 0x01654c01: modeName.append("FromCreatureGame"); break;
    case 0x01654c02: modeName.append("FromTribeGame"); break;
    case 0x01654c04: modeName.append("FromCivilisationGame"); break;
    case 0x01654c05: modeName.append("FromSpaceGame"); break;
    case 0x01654c08: modeName.append("FromLoadGame"); break;
    }
    int nResult = GetPlayModeFacade()->s14(modeName.c_str());
    modeName.Release();
    return nResult;
}

// @ 0x00b1e410
bool PaintSystemHost::SetPlayMode(int mode)
{
    if (mode == -2)
        mode = m24;
    if (mode != m20) {
        const char bTickerEnabled = SimTicker()->SmoothTickToggle();
        SimTicker()->Enable(0);
        GetPlayModeFacade()->s10(ChangeEnvironmentMode(m20, mode));
        mb28 = true;
        SimTicker()->Enable(bTickerEnabled);
    }
    return true;
}

// entry read back from the save stream: refcounted, list node embedded at +0xc
struct ListEntry {
    virtual int  AddRef();     // +0x00
    virtual void Release();    // +0x04
    uint32_t mTag04;           // +0x04
    uint32_t mMagic08;         // +0x08
    ListNode2 mNode;           // +0x0c
};

// SP::cVarListSerializer (0x00a14 bytes in retail): reads the tagged variable list
struct cVarListSerializer {
    cVarListSerializer(const void* pOwner, void* pGeneric, unsigned int id);   // 0x00692f90
    void Read(IReader* pReader);                                              // 0x00693e10
    char mData[0xa14];
};

// the serializer records its owner four bytes before the list head of the loader
inline const void* SerializerOwner(const void* pSelf) { return (const uint32_t*)pSelf - 1; }

// @ 0x00b1fc80
void InitStateOwner::Load(IReader* pReader)
{
    int nCount;
    ReadInt32(pReader->r08()->s06(), &nCount, 1, 0);
    for (int i = 0; i < nCount; ++i) {
        ListEntry* pEntry = 0;
        pReader->r10(0x017f243b, (void**)&pEntry, 0);
        if (pEntry != 0) {
            ListNode2* pNode = &pEntry->mNode;
            ListNode2* pPrev = mLoading.mpPrev;
            pNode->mpNext = &mLoading;
            pNode->mpPrev = pPrev;
            mLoading.mpPrev = pNode;
            pPrev->mpNext = pNode;
            pEntry->AddRef();
            if (pEntry != 0)
                pEntry->Release();
        }
    }
    cVarListSerializer serializer(SerializerOwner(this), (void*)0x015685a8, 0x1a80d26);
    serializer.Read(pReader);
}
