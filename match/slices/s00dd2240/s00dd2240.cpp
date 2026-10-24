// Slice s00dd2240 -- SP::cSPUICommScreen (the communication-screen UI window) helpers.
//
// The screen owns a UTFWin layout (cSPUILayout* at +0xc) plus a handful of ref-counted window
// sub-objects (+0x10 .. +0x2c, +0xbc, +0xc0) and an EA messaging handler record (+0xd8..+0xe8).
// FUN_00dd2820 rebinds the current empire/planet objects; the Show / SetSpeakerText members drive
// the widgets; FUN_00dd2320 lazily builds two static animation tables indexed by a creature kind.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

#define PV(n) virtual void pv##n();

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };
struct SList { SList* mpNext; };

extern const float kClampMax;                                    // 0x013ec4d0
extern uint8_t     kGameModeA;                                   // 0x01654c04
extern uint8_t     kGameModeB;                                   // 0x01654c05
extern uint32_t    gAnimFlags;                                   // 0x016a025c
extern char*       gAnimBase;                                    // 0x01440aec
extern float       kAudioPos[3];                                 // 0x016a0260

namespace SP {

// --------------------------------------------------------------------- ref-counted UI objects
// EA COM root: slot 0 = AddRef, slot 1 = Release.
class IWin {
 public:
    virtual void  AddRef();                                  // +0x00
    virtual void  Release();                                 // +0x04
    virtual void  pv02();                                    // +0x08
    virtual void* pv03(int id);                              // +0x0c
    virtual void* pv04();                                    // +0x10
    virtual void  pv05();                                    // +0x14
    virtual void  pv06();                                    // +0x18
    virtual void  pv07(int a);                               // +0x1c
    virtual void  pv08();                                    // +0x20
    virtual void  pv09(void* p);                             // +0x24
    virtual void  pv10();                                    // +0x28
    virtual char  pv11(int id, int a, void* out);            // +0x2c
    virtual void  pv12(void* p);                             // +0x30
    virtual void* pv13();                                    // +0x34
    virtual void  pv14();                                    // +0x38
    virtual void  pv15();                                    // +0x3c
    virtual void  pv16();                                    // +0x40
    virtual void  pv17();                                    // +0x44
    virtual void  pv18();                                    // +0x48
    virtual void  pv19();                                    // +0x4c
    virtual void  pv20();                                    // +0x50
    virtual void  pv21();                                    // +0x54
    virtual void  pv22();                                    // +0x58
    virtual void  pv23();                                    // +0x5c
    virtual void  pv24(void* p);                             // +0x60
    virtual void  pv25(float a, float b);                    // +0x64
    virtual void  pv26();                                    // +0x68
    virtual void  pv27();                                    // +0x6c
    virtual void  pv28();                                    // +0x70
    virtual void  pv29();                                    // +0x74
    virtual void  pv30();                                    // +0x78
    virtual void  pv31(int a, int b);                        // +0x7c
    virtual void  pv32(void* a);                             // +0x80
    virtual void  pv33();                                    // +0x84
    virtual void  pv34();                                    // +0x88
    virtual void  pv35();                                    // +0x8c
    virtual void  pv36();                                    // +0x90
    virtual void  pv37();                                    // +0x94
    virtual void  pv38();                                    // +0x98
    virtual void  pv39();                                    // +0x9c
    virtual void  pv40();                                    // +0xa0
    virtual void  pv41();                                    // +0xa4
    virtual void  pv42();                                    // +0xa8
    virtual void  pv43();                                    // +0xac
    virtual void  pv44();                                    // +0xb0
    virtual void  pv45();                                    // +0xb4
    virtual void  pv46();                                    // +0xb8
    virtual void  pv47();                                    // +0xbc
    virtual void  pv48();                                    // +0xc0
    virtual void  pv49();                                    // +0xc4
    virtual void  pv50();                                    // +0xc8
    virtual void* pv51(void* p);                             // +0xcc
    virtual void  pv52(void* p);                             // +0xd0
    virtual void  pv53();                                    // +0xd4
    virtual void  pv54();                                    // +0xd8
    virtual void  pv55();                                    // +0xdc
    virtual void  pv56();                                    // +0xe0
    virtual void  pv57();                                    // +0xe4
    virtual void  pv58(void* p);                             // +0xe8
};

// effect object returned by an effects-manager: slot +0x08 sets visibility
class IEffectWin {
 public:
    virtual void AddRef();                                   // +0x00
    virtual void Release();                                  // +0x04
    virtual void SetVisible(int a);                          // +0x08
};

// effect node reached through IWin::pv03: slot +0x04 applies a value
class IEffectNode {
 public:
    virtual void AddRef();                                   // +0x00
    virtual void Apply(float t);                             // +0x04
};

// --------------------------------------------------------------------- widgets returned by the layout
class cSPUILayout {
 public:
    IWin* FindWindowByID(int id, int flags);                 // 0x008105b0
    bool  SetParentWin(IWin* win, bool b, int id);           // 0x008121b0
};
class cSPUIGlobalUI {
 public:
    void* FindWindowByID(int id);                            // 0x00e012b0
};
class cUIHints {
 public:
    int   SetFlag(int a, int b);                             // 0x0067c420
};
class cDatabasePackedFile {
 public:
    void* GetLocation();                                     // 0x00a42730
};
class cLocation {
 public:
    uint8_t pad00[0x0c];
    int     mKind_0c;                                        // +0x0c
    void*   FUN_006c0200();                                  // 0x006c0200
};
class cEmpire {
 public:
    void* GetHomePlanet();                                   // 0x00c31730
    int   FUN_00c30cb0();                                    // 0x00c30cb0
    uint8_t pad00[0x84];
    void*   mp_84;                                           // +0x84
};
class cStarManager {
 public:
    int   GetEmpireByID(void* id);                           // 0x00ba9370
    void* FUN_00885c90();                                    // 0x00885c90
    void* FUN_00bce4c0();                                    // 0x00bce4c0
};
class cRelationshipManager {
 public:
    char  FUN_00d01b50(void* a, void* b);                    // 0x00d01b50
    void* FUN_00d00a70(void* a, void* b, int c);             // 0x00d00a70
};
class cGameNounManager {
 public:
    int   GetPlayerCivilization();                           // 0x00b25fb0
    void* FUN_00b25f40();                                    // 0x00b25f40
};
class cUFO {
 public:
    void* GetPlayerInventory();                              // 0x00a1ad60
};
// EA string object (FUN_006b55c0 = SP::cString_s006b_47a0::GetText); 0x14 bytes wide
class cString {
 public:
    const wchar_t* GetText();                                // 0x006b55c0
    uint8_t mData_00[0x14];
};
class cInventory {
 public:
    uint8_t pad7f4[0x7f4];
    float   mValue_7f4;                                      // +0x7f4
    float   mValue_7f8;                                      // +0x7f8
};
class cCreature {
 public:
    void* FUN_00c71e30();                                    // 0x00c71e30
    uint8_t pad84[0x84];
    void*   mp_84;                                           // +0x84
    uint8_t pad88[0x13c - 0x88];
    void*   mp_13c;                                          // +0x13c
};
// the app object behind FUN_010666a0 (owns the global UI singleton at +0x224)
class cAppObj {
 public:
    void* FUN_01068330();                                    // 0x01068330
    uint8_t pad224[0x224];
    cSPUIGlobalUI* mpGlobalUI_224;                           // +0x224
};
// civ-mode strategy chain
class cCivModeStrategy {
 public:
    void* FUN_00cf7500();                                    // 0x00cf7500
};
class cCivModeB {
 public:
    void* FUN_00ce8db0();                                    // 0x00ce8db0
};
// the effects manager (singleton from EffectsManagerPtr): slot +0x2c
class cEffectsManager {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual char AddEffect(int id, int a, void** out);       // +0x2c
};
// the audio system (singleton from FUN_00a206f0): slot +0x10
class cAudioSystem {
 public:
    PV(0) PV(1) PV(2) PV(3)
    virtual void* pv04(int a);                               // +0x10
};
// the EA message server object: slot +0x24 registers a handler
class cMessageServer {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual void RegisterHandler(void* a, void* b);          // +0x24
};
// mission-card panel (FUN_00b3d400)
class cMissionCardPanel {
 public:
    void SetCardsVisibility(bool b);                         // 0x00e14c10
};
// the object behind FUN_00b3d4f0
class cPanelB {
 public:
    void FUN_00e2f270(int a);                                // 0x00e2f270
};
// W1da0 helper (FUN_007b1da0)
class W1da0 {
 public:
    void f(void* p);                                         // 0x007b1da0
};
// object behind FUN_00bf0f40 / FUN_00bf1e20 / FUN_00bf0f90 (city music / planet view)
class cPlanetView {
 public:
    void* FUN_00bf0f40();                                    // 0x00bf0f40
    void* FUN_00bf1e20();                                    // 0x00bf1e20
    void  FUN_00bf0f90();                                    // 0x00bf0f90
};
// the kind-indexed descriptor passed to FUN_00dd2320
class cKindObj {
 public:
    uint8_t pad58[0x58];
    int     mKind_58;                                        // +0x58
};

// 3-dword row used by the lazily-built animation tables
struct AnimRow { uint32_t a, b, c; };
extern AnimRow gAnimTableA[9];                               // 0x016a01f0
extern AnimRow gAnimTableB[10];                              // 0x016a0178

// --------------------------------------------------------------------- helper free functions
void*  NounManager();                                        // 0x00b3d300
void*  StarManager();                                        // 0x00b3d2a0
void*  RelationshipManager();                                // 0x00b3d2c0
void*  CommManager();                                        // 0x00b3d4a0
void*  MessageServer();                                      // 0x0067dcc0
void*  EffectsManagerPtr();                                  // 0x0067ddd0
void*  FUN_0067ddc0();                                       // 0x0067ddc0
void*  FUN_0067cac0();                                       // 0x0067cac0
void*  FUN_00ae9da0();                                       // 0x00ae9da0
void*  FUN_01021300();                                       // 0x01021300
void*  GetUFOSimulator();                                    // 0x00ffbe50
void*  GetCurrentGameMode();                                 // 0x00b5b800
void*  FUN_00b3d400();                                       // 0x00b3d400
void*  FUN_00b3d4f0();                                       // 0x00b3d4f0
void*  FUN_00a206f0();                                       // 0x00a206f0
cCivModeStrategy* FUN_00cf74c0();                            // 0x00cf74c0
cAppObj* FUN_010666a0();                                     // 0x010666a0
float  FUN_00bd80d0(void* p);                                // 0x00bd80d0
void   FUN_00e2e6e0(void* p, void* q);                       // 0x00e2e6e0
void   FUN_006572f0(void* a, void* b);                       // 0x006572f0
void   FUN_00571db0(void* a, void* b, void* c, void* d, void* e); // 0x00571db0
void   FUN_00dd1c50(void* a, void* b);                       // 0x00dd1c50
void   FUN_00807690(void* a, int b);                         // 0x00807690
void*  FUN_00bef920(void* a);                                // 0x00bef920
float* SPUIHelpers_GetBoundingScreenRect(float* out, void* win, char a); // 0x00808d20

// --------------------------------------------------------------------- cSPUICommScreen
class cSPUICommScreen {
 public:
    void  Show();                                            // 0x00dd2e80
    void  SetSpeakerText(void* text);                        // 0x00dd2ad0
    void  GetMainCreatureScreen();                           // 0x00dd2cf0
    void  FUN_00dd2820();                                    // 0x00dd2820
    void  FUN_00dd2a10();                                    // 0x00dd2a10
    void  FUN_00dd2c60(int index, void* a, void* b);         // 0x00dd2c60
    void  FUN_00dd2d00();                                    // 0x00dd2d00
    void  FUN_00dd2d30();                                    // 0x00dd2d30
    void  FUN_00dd27c0();                                    // 0x00dd27c0
    void  FUN_00dd2800(void* w);                             // 0x00dd2800
    void  FUN_00dd2780(int kind, int count);                 // 0x00dd2780
    IWin* FUN_00dd2320(cKindObj* obj, void* other);          // 0x00dd2320
    char  FUN_00dd2650(cCreature* param_2, void** out);      // 0x00dd2650
    void* FUN_00dd1ce0(int a, int b);                        // 0x00dd1ce0

    uint8_t  pad00[0x0c];
    cSPUILayout* mLayout_0c;                                 // +0x0c
    IWin*    mScrollRoot_10;                                 // +0x10
    void*    pad14;                                          // +0x14
    IWin*    mpObj18;                                        // +0x18
    void*    mpObj1c;                                        // +0x1c
    IWin*    mTextScroll_20;                                 // +0x20
    IWin*    mpObj24;                                        // +0x24
    IWin*    mpComm_28;                                      // +0x28
    IWin*    mpButtons_2c;                                   // +0x2c
    IWin*    mpObj30;                                        // +0x30
    uint8_t  pad34[0x0c];                                    // +0x34
    uint8_t  mbShown_40;                                     // +0x40
    uint8_t  pad41[0x80 - 0x41];                             // +0x41
    cString  mStr_80;                                        // +0x80
    uint8_t  pad94[0xa8 - 0x94];                             // +0x94
    cString  mStr_a8;                                        // +0xa8
    IWin*    mpObjBc;                                        // +0xbc
    IWin*    mpObjC0;                                        // +0xc0
    uint8_t  padc4[0xd8 - 0xc4];                             // +0xc4
    void*    mpMsg_d8;                                       // +0xd8
    void*    mpMsgDc;                                        // +0xdc
    void*    mMsg_e0;                                        // +0xe0
    uint32_t mMsg_e4;                                        // +0xe4
    void*    mMsg_e8;                                        // +0xe8
};

// --------------------------------------------------------------------- free helpers
void __stdcall FUN_00dd2240(void* obj, void* civ);          // 0x00dd2240
void* FUN_00dd22f0();                                        // 0x00dd22f0

// ===================================================================== bodies

// @ 0x00dd2240
void __stdcall FUN_00dd2240(void* param_1, void* param_2)
{
    IWin* obj = (IWin*)param_1;
    int civ = ((cGameNounManager*)NounManager())->GetPlayerCivilization();
    obj->pv31(1, civ != (int)param_2);
    if (civ != (int)param_2)
    {
        float v = FUN_00bd80d0(param_2);
        IEffectNode* node = (IEffectNode*)obj->pv03(0x10edf11);
        if (node != 0)
        {
            float t = v;
            if (t <= 0.0f) t = 0.0f;
            if (t >= kClampMax) t = kClampMax;
            node->Apply(t);
        }
    }
}

// @ 0x00dd22f0
void* FUN_00dd22f0()
{
    if (GetCurrentGameMode() == &kGameModeB)
        return FUN_010666a0()->mpGlobalUI_224->FindWindowByID(0x64e7368);
    return 0;
}

// @ 0x00dd2320
IWin* cSPUICommScreen::FUN_00dd2320(cKindObj* obj, void* other)
{
    if (obj != 0)
    {
        uint32_t f = gAnimFlags;
        if ((f & 1) == 0)
        {
            f |= 1;
            gAnimFlags = f;
            gAnimTableA[0].a = 0xbf4a63b8; gAnimTableA[0].b = 0x2f7d0004; gAnimTableA[0].c = 0x0354663b;
            gAnimTableA[1].a = 0xc69009ce; gAnimTableA[1].b = 0x2f7d0004; gAnimTableA[1].c = 0x0354663b;
            gAnimTableA[2].a = 0xea3a7080; gAnimTableA[2].b = 0x2f7d0004; gAnimTableA[2].c = 0x0354663b;
            gAnimTableA[3].a = 0x85888400; gAnimTableA[3].b = 0x2f7d0004; gAnimTableA[3].c = 0x0354663b;
            gAnimTableA[4].a = 0xfd35de13; gAnimTableA[4].b = 0x2f7d0004; gAnimTableA[4].c = 0x0354663b;
            gAnimTableA[5].a = 0x29dab11f; gAnimTableA[5].b = 0x2f7d0004; gAnimTableA[5].c = 0x0354663b;
            gAnimTableA[6].a = 0xf9852530; gAnimTableA[6].b = 0x2f7d0004; gAnimTableA[6].c = 0x0354663b;
            gAnimTableA[7].a = 0x2845e1fb; gAnimTableA[7].b = 0x2f7d0004; gAnimTableA[7].c = 0x0354663b;
            gAnimTableA[8].a = 0xb865a25e; gAnimTableA[8].b = 0x2f7d0004; gAnimTableA[8].c = 0x0354663b;
        }
        if ((f & 2) == 0)
        {
            f |= 2;
            gAnimFlags = f;
            gAnimTableB[0].a = 0xbf4a63b8; gAnimTableB[0].b = 0x2f7d0004; gAnimTableB[0].c = 0x0354663b;
            gAnimTableB[1].a = 0xc69009ce; gAnimTableB[1].b = 0x2f7d0004; gAnimTableB[1].c = 0x0354663b;
            gAnimTableB[2].a = 0xea3a7080; gAnimTableB[2].b = 0x2f7d0004; gAnimTableB[2].c = 0x0354663b;
            gAnimTableB[3].a = 0x85888400; gAnimTableB[3].b = 0x2f7d0004; gAnimTableB[3].c = 0x0354663b;
            gAnimTableB[4].a = 0xfd35de13; gAnimTableB[4].b = 0x2f7d0004; gAnimTableB[4].c = 0x0354663b;
            gAnimTableB[5].a = 0x29dab11f; gAnimTableB[5].b = 0x2f7d0004; gAnimTableB[5].c = 0x0354663b;
            gAnimTableB[6].a = 0xf9852530; gAnimTableB[6].b = 0x2f7d0004; gAnimTableB[6].c = 0x0354663b;
            gAnimTableB[7].a = 0x2845e1fb; gAnimTableB[7].b = 0x2f7d0004; gAnimTableB[7].c = 0x0354663b;
            gAnimTableB[8].a = 0x24c6341d; gAnimTableB[8].b = 0x2f7d0004; gAnimTableB[8].c = 0x0354663b;
            gAnimTableB[9].a = 0x3e17e328; gAnimTableB[9].b = 0x2f7d0004; gAnimTableB[9].c = 0x0354663b;
        }
        switch (obj->mKind_58)
        {
        case 0:  return (IWin*)&gAnimTableA[0];
        case 1:  return (IWin*)&gAnimTableA[1];
        case 2:  return (IWin*)&gAnimTableA[2];
        case 3:  return (IWin*)&gAnimTableA[3];
        case 4:  return (IWin*)&gAnimTableA[4];
        case 5:  return (IWin*)&gAnimTableA[5];
        case 6:  return (IWin*)&gAnimTableA[6];
        case 7:  return (IWin*)&gAnimTableA[7];
        case 8:  return (IWin*)&gAnimTableA[8];
        case 9:  return (IWin*)&gAnimTableB[0];
        case 10: return (IWin*)&gAnimTableB[1];
        case 0xb: return (IWin*)&gAnimTableB[2];
        case 0xc: return (IWin*)&gAnimTableB[3];
        case 0xd: return (IWin*)&gAnimTableB[4];
        case 0xe: return (IWin*)&gAnimTableB[5];
        case 0xf: return (IWin*)&gAnimTableB[6];
        case 0x10: return (IWin*)&gAnimTableB[7];
        case 0x12: return (IWin*)&gAnimTableB[8];
        default: return (IWin*)&gAnimTableB[9];
        }
    }

    cPlanetView* pv = (cPlanetView*)other;
    void* a = pv->FUN_00bf0f40();
    void* b = FUN_00bef920(a);
    void* c = pv->FUN_00bf1e20();
    return (IWin*)FUN_00dd1ce0((int)b, (int)c);
}

// @ 0x00dd2650
char cSPUICommScreen::FUN_00dd2650(cCreature* param_2, void** param_3)
{
    char flag = 0;
    cCreature* a = (cCreature*)param_2->FUN_00c71e30();
    cEmpire* empire = (cEmpire*)FUN_01021300();
    cInventory* inv = (cInventory*)((cUFO*)GetUFOSimulator())->GetPlayerInventory();

    if (a != 0)
    {
        cStarManager* sm = (cStarManager*)StarManager();
        if (a->mp_84 == sm->FUN_00885c90())
        {
            cRelationshipManager* rm = (cRelationshipManager*)RelationshipManager();
            if (rm->FUN_00d01b50(a->mp_84, empire->mp_84))
            {
                void* u = rm->FUN_00d00a70(a->mp_84, empire->mp_84, 1);
                if (u == 0 || u == (void*)1)
                    return flag;
            }
        }
    }

    if (((cEmpire*)FUN_01021300())->FUN_00c30cb0() == 0)
    {
        if (param_2->mp_13c != empire->GetHomePlanet())
        {
            *param_3 = (void*)mStr_80.GetText();
            return flag;
        }
    }

    if (inv->mValue_7f4 == inv->mValue_7f8)
    {
        *param_3 = (void*)mStr_a8.GetText();
        return flag;
    }
    return 1;
}

// @ 0x00dd2780
void cSPUICommScreen::FUN_00dd2780(int kind, int count)
{
    if (kind == 2 && count > 0)
        count = 1;
    for (int i = 0; i < count; i++)
    {
        void* r = FUN_00dd1ce0(kind, i);
        ((W1da0*)mpObj30)->f(r);
    }
}

// @ 0x00dd27c0
void cSPUICommScreen::FUN_00dd27c0()
{
    IWin* w = mLayout_0c->FindWindowByID(0x4a4504f, 1);
    if (w != 0)
    {
        cLocation* loc = (cLocation*)((cDatabasePackedFile*)CommManager())->GetLocation();
        if (loc != 0)
        {
            FUN_00e2e6e0(loc->FUN_006c0200(), w);
        }
    }
}

// @ 0x00dd2800
void cSPUICommScreen::FUN_00dd2800(void* w)
{
    if (mLayout_0c != 0)
        mLayout_0c->SetParentWin((IWin*)w, true, 0x5b598fa);
}

// @ 0x00dd2820
void cSPUICommScreen::FUN_00dd2820()
{
    cLocation* loc = (cLocation*)((cDatabasePackedFile*)CommManager())->GetLocation();
    IWin* piVar5;
    if (loc->mKind_0c == 1)
    {
        IWin* p = (IWin*)FUN_00ae9da0();
        IWin* old = mpObjBc;
        if (p != old)
        {
            if (p) p->AddRef();
            mpObjBc = p;
            if (old) old->Release();
        }
        piVar5 = *(IWin**)((char*)mpObjBc + 0x274);
    }
    else
    {
        void* u = loc->FUN_006c0200();
        piVar5 = 0;
        cStarManager* sm = (cStarManager*)StarManager();
        int i = sm->GetEmpireByID(u);
        cGameNounManager* nm = (cGameNounManager*)NounManager();
        IWin* p = (IWin*)nm->FUN_00b25f40();
        IWin* old = mpObjBc;
        if (p != old)
        {
            if (p) p->AddRef();
            mpObjBc = p;
            if (old) old->Release();
        }
        if (i != 0)
            piVar5 = (IWin*)sm->FUN_00bce4c0();
    }
    {
        IWin* old = mpObjC0;
        if (piVar5 != old)
        {
            if (piVar5) piVar5->AddRef();
            mpObjC0 = piVar5;
            if (old) old->Release();
        }
    }

    Vec3 vec;
    void* sys = FUN_00a206f0();
    if (sys != 0)
    {
        float* p = (float*)((cAudioSystem*)sys)->pv04(0);
        vec.x = p[0]; vec.y = p[1]; vec.z = p[2];
    }
    else
    {
        vec.x = kAudioPos[0]; vec.y = kAudioPos[1]; vec.z = kAudioPos[2];
    }

    if (mpObjBc == 0)
    {
        if (mpObjC0 != 0) mpObjC0->pv09(&vec);
    }
    else
    {
        if (mpObjC0 != 0) mpObjC0->pv12(&vec);
    }

    if (mpObjC0 != 0)
        FUN_006572f0((void*)0xedf69848, mpObjC0->pv13());

    void* msg = MessageServer();
    mpMsg_d8 = msg;
    mpMsgDc = (char*)this + 4;
    mMsg_e0 = (void*)0x15a2b2c;
    mMsg_e4 = 1;
    mMsg_e8 = 0;
    if (msg != 0 && mpMsgDc != 0)
        ((cMessageServer*)msg)->RegisterHandler(mpMsgDc, mMsg_e0);
}

// @ 0x00dd2a10
void cSPUICommScreen::FUN_00dd2a10()
{
    void* h = mpMsg_d8;
    if (h != 0)
    {
        mpMsg_d8 = 0;
        FUN_00571db0(h, mpMsgDc, mMsg_e0, (void*)mMsg_e4, mMsg_e8);
    }
    if (mpObjC0 != 0)
        FUN_00dd1c50((void*)0xedf69848, mpObjC0->pv13());

    if (mpObjBc != 0)
    {
        ((cPlanetView*)mpObjBc)->FUN_00bf0f90();
    }
    else
    {
        if (mpObjC0 != 0) mpObjC0->pv10();
    }

    IWin* p = mpObjBc;
    if (p != 0)
    {
        mpObjBc = 0;
        p->Release();
    }
    IWin* q = mpObjC0;
    if (q != 0)
    {
        mpObjC0 = 0;
        q->Release();
    }
}

// @ 0x00dd2ad0
void cSPUICommScreen::SetSpeakerText(void* text)
{
    IWin* edi;
    if (mpComm_28 == 0) edi = 0;
    else edi = (IWin*)mpComm_28->pv03(0xf15f4bd);

    mpComm_28->pv32(text);

    {
        float* a = (float*)mTextScroll_20->pv13();
        float ax = a[0], az = a[2];
        float* b = (float*)mpComm_28->pv13();
        float b0 = b[0];
        float v[4];
        v[0] = b[0]; v[1] = b[1]; v[2] = b[2]; v[3] = b[3];
        v[2] = (az - ax) + b0;
        mpComm_28->pv24(v);
    }
    mpComm_28->pv25(0.0f, 0.0f);
    edi->pv07(1);
    FUN_00807690(mpObj1c, 1);

    {
        float* a = (float*)mTextScroll_20->pv13();
        float ax = a[0], az = a[2];
        float* b = (float*)mpComm_28->pv13();
        float b0 = b[0];
        float v[4];
        v[0] = b[0]; v[1] = b[1]; v[2] = b[2]; v[3] = b[3];
        v[2] = (az - ax) + b0;
        mpComm_28->pv24(v);
    }
    mpComm_28->pv25(0.0f, 0.0f);
    edi->pv07(1);
    FUN_00807690(mpObj1c, 1);
}

// @ 0x00dd2c60
void cSPUICommScreen::FUN_00dd2c60(int index, void* a, void* b)
{
    int i = 0;
    SList* begin;
    SList* local;
    mpObj24->pv52(&begin);
    SList* cur = *(SList**)mpObj24->pv51(&local);
    if (cur != begin)
    {
        for (;;)
        {
            if (i == index) break;
            cur = cur->mpNext;
            i++;
            if (cur == begin) return;
        }
        IWin* node = (IWin*)(gAnimBase + (uint32_t)cur);
        node->pv32(a);
        node->pv31(2, (int)b);
    }
}

// @ 0x00dd2cf0
void cSPUICommScreen::GetMainCreatureScreen()
{
    mLayout_0c->FindWindowByID(0x3619a7e, 1);
}

// @ 0x00dd2d00
void cSPUICommScreen::FUN_00dd2d00()
{
    IWin* w = mLayout_0c->FindWindowByID(-1, 1);
    IWin* c = (IWin*)w->pv04();
    c->pv58(w);
}

// @ 0x00dd2d30
void cSPUICommScreen::FUN_00dd2d30()
{
    if (mpObj24 == 0) return;
    if (mpObj18 == 0) return;
    if (mpObj18->pv04() == 0) return;

    float rect[4];
    SPUIHelpers_GetBoundingScreenRect(rect, mpObj18->pv04(), 0);

    SList* begin;
    SList* local;
    mpObj24->pv52(&begin);
    SList* cur = *(SList**)mpObj24->pv51(&local);
    if (cur == begin) return;

    for (;;)
    {
        float r2[4];
        IWin* node = (IWin*)(gAnimBase + (uint32_t)cur);
        SPUIHelpers_GetBoundingScreenRect(r2, node, 0);

        bool vis;
        if (rect[2] <= r2[0] || rect[0] <= r2[2] || rect[3] <= r2[1] || rect[1] <= r2[3])
        {
            r2[1] = 0.0f; r2[3] = 0.0f; r2[2] = 0.0f; r2[0] = 0.0f;
            vis = false;
        }
        else
        {
            if (r2[0] <= r2[2]) r2[0] = r2[2];
            if (r2[1] <= r2[3]) r2[1] = r2[3];
            if (rect[0] <= r2[2]) r2[2] = rect[0];
            if (rect[1] <= r2[3]) r2[3] = rect[1];
            vis = true;
        }
        node->pv31(0x10, !vis);
        cur = cur->mpNext;
        if (cur == begin) break;
    }
}

// @ 0x00dd2e80
void cSPUICommScreen::Show()
{
    if (mbShown_40 != 0) return;

    ((cUIHints*)FUN_0067cac0())->SetFlag(0, 1);
    IWin* ebx = mLayout_0c->FindWindowByID(0x1c3bb0c, 1);
    if (ebx == 0) return;

    mbShown_40 = 1;
    cEffectsManager* em = (cEffectsManager*)EffectsManagerPtr();
    if (mpButtons_2c != 0)
    {
        IWin* t = mpButtons_2c;
        mpButtons_2c = 0;
        t->Release();
    }
    if (em->AddEffect(0x4c4ba0a9, 0, (void**)&mpButtons_2c))
        ((IEffectWin*)mpButtons_2c)->SetVisible(0);

    ((IWin*)FUN_0067ddc0())->pv16();
    ((IWin*)FUN_0067ddc0())->pv10();

    void* mode = GetCurrentGameMode();
    void* win = 0;
    if (mode == &kGameModeB)
    {
        win = FUN_010666a0()->mpGlobalUI_224->FindWindowByID(0x5e66e88);
        FUN_010666a0()->FUN_01068330();
    }
    else if (mode == &kGameModeA)
    {
        win = ((cCivModeB*)FUN_00cf74c0()->FUN_00cf7500())->FUN_00ce8db0();
    }

    if (mLayout_0c != 0)
        mLayout_0c->SetParentWin((IWin*)win, true, 0x5b598fa);

    if (FUN_00b3d400() != 0)
        ((cMissionCardPanel*)FUN_00b3d400())->SetCardsVisibility(false);

    ((cPanelB*)FUN_00b3d4f0())->FUN_00e2f270(1);

    ebx->pv31(1, 1);

    IWin* w = mLayout_0c->FindWindowByID(0x5e4e5f8, 1);
    if (w != 0) w->pv31(1, 1);
    w = mLayout_0c->FindWindowByID(0x5e4e5f0, 1);
    if (w != 0) w->pv31(1, 1);
    w = mLayout_0c->FindWindowByID(0x6429c80, 1);
    if (w != 0) w->pv31(1, 1);
    w = mLayout_0c->FindWindowByID(0x5e3c090, 1);
    if (w != 0) w->pv31(1, 0);

    void* out2 = 0;
    cEffectsManager* em2 = (cEffectsManager*)EffectsManagerPtr();
    if (out2 != 0)
    {
        IWin* t = (IWin*)out2;
        out2 = 0;
        t->Release();
    }
    if (em2->AddEffect(0x3d6f608, 0, &out2))
        ((IEffectWin*)out2)->SetVisible(0);

    cEffectsManager* em3 = (cEffectsManager*)EffectsManagerPtr();
    if (mScrollRoot_10 != 0)
    {
        IWin* t = mScrollRoot_10;
        mScrollRoot_10 = 0;
        t->Release();
    }
    if (em3->AddEffect(0x3d6f60b, 0, (void**)&mScrollRoot_10))
        ((IEffectWin*)mScrollRoot_10)->SetVisible(0);

    FUN_00dd2820();

    if (out2 != 0)
        ((IWin*)out2)->Release();
}

} // namespace SP