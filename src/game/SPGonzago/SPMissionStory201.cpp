// src/game/SPGonzago/SPMissionStory201.cpp -- migrated from slice(s) s00c5f530, s00c5e260 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionStory201.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanet.h"
#include "SP/cSPMission.h"
#include "SP/cSolarSystem.h"
#include "SP/cStar.h"
#include "SP/cStarManager.h"

// ---- items of slice s00c5e260 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vtbl { void* p[64]; };
typedef int   (__thiscall* FnI0)(void*);
typedef void* (__thiscall* FnP1)(void*, int);
typedef void  (__thiscall* FnV1)(void*, int);
typedef void  (__thiscall* FnV2)(void*, void*, int);
typedef void  (__thiscall* FnV3)(void*, void*, int, int);
typedef void  (__thiscall* FnVoid)(void*);
struct Planet {
  uint8_t mPad000[0x13c];
  int     mField13c;      // +0x13c
};
struct Item {
  int mField0;            // +0x00
  int mField4;            // +0x04
  int mField8;            // +0x08
};
struct Inventory {
  void FUN_00ff45e0(Item* item);  // 0x00ff45e0
};
struct cSPSimulatorSpaceGame {
  Inventory* GetPlayerInventory(); // 0x00a1ad60
};
struct cGameNounManager_s00c5_e260 {
  void* GetPlayerTribe();          // 0x00bfc5f0
};
struct TribeObj {
  void FUN_00fe5430();             // 0x00fe5430
};
struct SomeVec {
  void*    mpField0;      // +0x00
  int      mPad04;        // +0x04
  int      mField8;       // +0x08
  int      mPad0C;        // +0x0c
  uint16_t mField10;      // +0x10
  uint16_t mField12;      // +0x12
};
struct Mission {
  Vtbl*   mpVtable;       // +0x000
  void*   mpField04;      // +0x004
  uint8_t mPad008[0x2c];  // +0x008 .. +0x033
  void*   mpField34;      // +0x034
  uint8_t mPad038[0x40];  // +0x038 .. +0x077
  int     mField078;      // +0x078
  uint8_t mPad07C[0xb4];  // +0x07c .. +0x12f
  uint32_t mField130;     // +0x130
  uint8_t mPad134[0x3c];  // +0x134 .. +0x16f
  uint8_t mField170[0x10];// +0x170 .. +0x17f
  void*   mpField180;     // +0x180
  uint8_t mPad184[0x6c];  // +0x184 .. +0x1ef
  int     mField1f0;      // +0x1f0
  void*   mpField1f4;     // +0x1f4
  int     mField1f8;      // +0x1f8
  int     mField1fc;      // +0x1fc

  // base helpers (addresses from the shipped binary)
  void  TriggerUIUpdate();        // 0x00c47d80
  void* GetTargetPlanet();        // 0x00970b30
  void  FUN_00c44b80();           // 0x00c44b80
  void  FUN_00c44bd0();           // 0x00c44bd0
  void  FUN_00c49f90();           // 0x00c49f90
  void  FUN_00c472e0();           // 0x00c472e0
  void  FUN_00c471c0();           // 0x00c471c0
  int   FUN_00c44cb0();           // 0x00c44cb0
  bool  IsActive();               // 0x00c44c80
  void  GetText(int id, int arg); // 0x00c487d0
  void  SetSerializer();          // 0x00c2e4e0
  bool  Init();                   // 0x00c4ad50
  int   ReadTargetPlanetType();   // 0x00c45b40
  void* GetPlanetRecordFromTargetType(int t); // 0x00c474b0
  void  FUN_00c47180(void* p);    // 0x00c47180
  int   ReadTargetAnimalSpeciesType(void* p); // 0x00c45b60
  void* GetAnimalSpeciesFromType(int t);      // 0x00c47610
  void* GetTargetPlanet(void* p, int a, int b); // 0x00970b30 (3-arg)
  void* PickPlanet(void* filter); // 0x00c47e20
  int   FUN_00c45b40();           // 0x00c45b40 (alias: ReadTargetPlanetType)
  void  FUN_00c4a0c0();           // 0x00c4a0c0
  char  FUN_00c5ea60();           // 0x00c5ea60 (see body)

  void  FUN_00c5ed90(int v);      // 0x00c5ed90
  void  FUN_00c5edb0();           // 0x00c5edb0
  void  FUN_00c5ee40();           // 0x00c5ee40
  void  FUN_00c5eed0(int arg);    // 0x00c5eed0
  void  FUN_00c5efb0(int arg);    // 0x00c5efb0
  int   FUN_00c5f090();           // 0x00c5f090
  int   FUN_00c5f0f0(int a, int b);// 0x00c5f0f0
  int   FUN_00c5f150();           // 0x00c5f150
  void  FUN_00c5f250();           // 0x00c5f250
  void  FUN_00c5f280();           // 0x00c5f280
  void  FUN_00c5f2c0();           // 0x00c5f2c0
  void  FUN_00c5f360();           // 0x00c5f360
  int   FUN_00c5f3d0();           // 0x00c5f3d0
  int   FUN_00c5f4e0(int id);     // 0x00c5f4e0
};
struct MissionStory201 : Mission {
  MissionStory201();              // 0x00c5f1b0
};
namespace SP {
  void* __stdcall SpaceGameGet(int a, int b); // 0x01002bd0
}
namespace SP {
  void* __stdcall SpaceGameGet();             // 0x01002bd0 (no-arg overload)
}
void* MessageServer();              // 0x0067dcc0
void  FUN_00c47a10();               // 0x00c47a10
void* FUN_01021370();               // 0x01021370
int   FUN_01021240();               // 0x01021240
int   FUN_01021080();               // 0x01021080
struct HomePlanetObj {
  int FUN_00b8de30();               // 0x00b8de30
};
void __fastcall MissionBaseCtor(void* self);
// ---- items of slice s00c5e260 end

// ---- items of slice s00c5f530 begin (TODO(rewrite): local stubs, replace by canonical classes)
class wstring {
public:
    unsigned short* mpBegin;      // +0x00
    unsigned short* mpEnd;        // +0x04
    unsigned short* mpCapacity;   // +0x08
    void assign(const unsigned short* first, const unsigned short* last);  // 0x00423650
};
struct cPlanet {
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual void v090();
virtual void v094();
virtual void v098();
virtual void v09c();
virtual void v0a0();
virtual void v0a4();
virtual void v0a8();
virtual void v0ac();
virtual void v0b0();
virtual void v0b4();
virtual void v0b8();
virtual void v0bc();
    virtual void v0c0();   // +0xc0

    char    pad_04[0x13c - 0x04];
    void*   m13c;          // +0x13c

    wstring* GetName();        // 0x00c707e0
    int      FUN_00c70fb0();   // 0x00c70fb0
};
struct cSolarSystem {
    char      pad_00[0x10];
    cPlanet** m10;   // +0x10  begin
    cPlanet** m14;   // +0x14  end
};
struct cStar {
    cSolarSystem* GetSolarSystem();   // 0x00c8b770
};
struct cBioElemSort {
    cBioElemSort* SortBanners();      // 0x00b8de30
    void FUN_00bb9b00(int a, int b);  // 0x00bb9b00
    void FUN_00bb9c30();              // 0x00bb9c30
};
struct cStarManager {
    void GetOrActivatePlanet(void* id, cPlanet** out);   // 0x00bb59b0
};
struct cMissionMgr {
    void FUN_00feba80();   // 0x00feba80
};
void  FUN_00c46b80();      // 0x00c46b80
void* FUN_01021260();      // 0x01021260  (cSPLivingUniverse::GetActivePlanet)
void* FUN_01021230();      // 0x01021230
void* StarManager();       // 0x00b3d2a0
cMissionMgr* __stdcall GetMissionManager(int id);   // 0x00feb9f0
void  TryGetUIntProperty(void* obj, unsigned id, unsigned* out);  // 0x00410370
struct cSPMission {
    char pad_00[0x180];

    void     FUN_00c46b80();                            // 0x00c46b80
    bool     Init();                                    // 0x00c4ad50
    cPlanet* GetTargetPlanet();                         // 0x00970b30
    bool     GetTagString(unsigned tag, wstring* out);  // 0x00c491c0
    void     FUN_00c4a0c0();                            // 0x00c4a0c0
};
struct cSPMissionStory201 : cSPMission {
    void*    m180;   // +0x180
    char     pad_184[0x1f4 - 0x184];
    cPlanet* m1f4;   // +0x1f4
    unsigned m1f8;   // +0x1f8
    unsigned m1fc;   // +0x1fc

    bool PickUFOWreckPlanet();                          // 0x00c5f530
    void FUN_00c5f5f0();                                // 0x00c5f5f0
    bool GetTagString(unsigned tag, wstring* out);      // 0x00c5f640
    void GetUIShortDescription();                       // 0x00c5f690
    bool FUN_00c5f770();                                // 0x00c5f770
    bool FUN_00c5fcf0();                                // 0x00c5fcf0
    void FUN_00c5fe00();                                // 0x00c5fe00
    void FUN_00c5ff50();                                // 0x00c5ff50
    void OnArtifactScanned();                           // 0x00c60120
};
static bool TagNameHelper(cPlanet* planet, wstring* out)
{
    wstring* name = planet->GetName();
    if (name != out)
        out->assign(name->mpBegin, name->mpEnd);
    return true;
}
// ---- items of slice s00c5f530 end

// @ 0x00c5edb0
void Mission::FUN_00c5edb0()
{
  FUN_00c44b80();
  ((FnV1)mpVtable->p[0x14c / 4])(this, 0x248975f);
  ((FnV1)mpVtable->p[0x14c / 4])(this, 0x2489766);
  ((FnV1)mpVtable->p[0x14c / 4])(this, 0x248976a);
  ((FnV1)mpVtable->p[0x14c / 4])(this, 0x44f1189);
  ((FnV1)mpVtable->p[0x14c / 4])(this, 0xf46093da);
  ((FnV1)mpVtable->p[0x14c / 4])(this, 0x6441936);

  void* dst = (void*)&mpField34;
  void* ms = MessageServer();
  ((FnV2)(*(Vtbl**)ms)->p[0x20 / 4])(ms, dst, 0x2489760);
}

// @ 0x00c5ee40
void Mission::FUN_00c5ee40()
{
  FUN_00c44bd0();
  ((FnV1)mpVtable->p[0x150 / 4])(this, 0x248975f);
  ((FnV1)mpVtable->p[0x150 / 4])(this, 0x2489766);
  ((FnV1)mpVtable->p[0x150 / 4])(this, 0x248976a);
  ((FnV1)mpVtable->p[0x150 / 4])(this, 0x44f1189);
  ((FnV1)mpVtable->p[0x150 / 4])(this, 0xf46093da);
  ((FnV1)mpVtable->p[0x150 / 4])(this, 0x6441936);

  void* dst = (void*)&mpField34;
  void* ms = MessageServer();
  ((FnV3)(*(Vtbl**)ms)->p[0x2c / 4])(ms, dst, 0x2489760, 0xffffd8f1);
}

// @ 0x00c5eed0
void Mission::FUN_00c5eed0(int arg)
{
  if (!IsActive())
    return;

  switch (mField1f0) {
  case 0:
    GetText(0xb98c20c5, arg);
    return;
  case 1:
    GetText(0x2f8f74df, arg);
    return;
  case 2: {
    void* p = FUN_01021370();
    int a = ((HomePlanetObj*)p)->FUN_00b8de30();
    int b = FUN_01021240();
    if (a == b && FUN_01021080() != 2)
      GetText(0xed4b67a7, arg);
    else
      GetText(0xd0fbdf85, arg);
    return;
  }
  case 3:
    GetText(0xa29d2048, arg);
    return;
  case 4:
    GetText(0x81128ae1, arg);
    return;
  }
}

// @ 0x00c5efb0
void Mission::FUN_00c5efb0(int arg)
{
  if (!IsActive())
    return;

  switch (mField1f0) {
  case 0:
    GetText(0xda9e8dc6, arg);
    return;
  case 1:
    GetText(0xc28f4e24, arg);
    return;
  case 2: {
    void* p = FUN_01021370();
    int a = ((HomePlanetObj*)p)->FUN_00b8de30();
    int b = FUN_01021240();
    if (a == b && FUN_01021080() != 2)
      GetText(0xc404af28, arg);
    else
      GetText(0x48cc6b76, arg);
    return;
  }
  case 3:
    GetText(0x2dc5caa7, arg);
    return;
  case 4:
    GetText(0xba93258e, arg);
    return;
  }
}

// @ 0x00c5f090
int Mission::FUN_00c5f090()
{
  if (((FnI0)mpVtable->p[0x60 / 4])(this) == 3) {
    switch (mField1f0) {
    case 0: return 0x2864b01f;
    case 1: return 0x0501dd96;
    case 2: return 0x1d3ce6e6;
    case 3: return 0x7b0daf98;
    case 4: return 0x11965a4d;
    }
  }
  return FUN_00c44cb0();
}

// @ 0x00c5f0f0
int Mission::FUN_00c5f0f0(int a, int b)
{
  if (((FnI0)mpVtable->p[0x60 / 4])(this) == 3) {
    switch (mField1f0) {
    case 0: return 0xcb268f51;
    case 1: return 0x1e1135ac;
    case 2: return 0xc04fa4e8;
    case 3: return 0x2d28ce76;
    }
  }
  return -1;
}

// @ 0x00c5f150
int Mission::FUN_00c5f150()
{
  if (mField1f0 != 0 && mField1f0 != 1)
    return 0;
  return 1;
}

// @ 0x00c5f190
void FUN_00c5f190()
{
  FUN_00c47a10();
  cGameNounManager_s00c5_e260* m = (cGameNounManager_s00c5_e260*)SP::SpaceGameGet(0x11, 1);
  TribeObj* t = (TribeObj*)m->GetPlayerTribe();
  t->FUN_00fe5430();
}

// @ 0x00c5f1b0
MissionStory201::MissionStory201()
{
  MissionBaseCtor(this);
  int zero = 0;
  *(volatile int*)&mField1f0 = zero;
  *(volatile int*)&mpVtable  = (int)0x146fe60;
  *(volatile int*)&mpField04 = (int)0x146fe4c;
  *(volatile int*)&mpField34 = (int)0x146fe3c;
  *(volatile int*)&mpField1f4 = zero;
  *(volatile int*)&mField1f8 = zero;
  *(volatile int*)&mField1fc = zero;
}

// @ 0x00c5f250
void Mission::FUN_00c5f250()
{
  void* p = mpField1f4;
  if (p != 0) {
    mpField1f4 = 0;
    ((FnVoid)(*(Vtbl**)p)->p[0xc0 / 4])(p);
  }
  FUN_00c49f90();
}

// @ 0x00c5f280
void Mission::FUN_00c5f280()
{
  if (mField1f0 != 4) {
    ((FnVoid)mpVtable->p[0x6c / 4])(this);
    if (mField1f0 != 4) {
      mField1f0 = 4;
      TriggerUIUpdate();
    }
    FUN_00c472e0();
    FUN_00c471c0();
  }
}

// @ 0x00c5f2c0
void Mission::FUN_00c5f2c0()
{
  void* obj = mpField180;
  SomeVec* v = (SomeVec*)((FnP1)(*(Vtbl**)obj)->p[0x28 / 4])(obj, 0xedcaee05);

  uint16_t mask = (uint16_t)(v->mField10 & 0x30);
  int count;
  int* items;

  if (mask != 0) {
    count = v->mField8;
    if (count <= 0)
      return;
  } else {
    if (v->mField12 == 0)
      return;
    count = 1;
  }

  if (mask != 0)
    items = (int*)v->mpField0;
  else {
    uint16_t f12 = *(volatile uint16_t*)&v->mField12;
    items = (f12 != 0) ? (int*)v : 0;
  }

  Inventory* inv = ((cSPSimulatorSpaceGame*)SP::SpaceGameGet())->GetPlayerInventory();
  if (inv == 0 || count <= 0)
    return;

  do {
    Item item;
    item.mField0 = items[0];
    item.mField4 = 0;
    item.mField8 = 0;
    inv->FUN_00ff45e0(&item);
    items += 3;
  } while (--count != 0);
}

// @ 0x00c5f360
void Mission::FUN_00c5f360()
{
  SetSerializer();
  FUN_00c5f2c0();
  if (mField1f0 != 4) {
    ((FnVoid)mpVtable->p[0x6c / 4])(this);
    if (mField1f0 != 4) {
      mField1f0 = 4;
      TriggerUIUpdate();
    }
    FUN_00c472e0();
    FUN_00c471c0();
  }
}

// @ 0x00c5f3d0
int Mission::FUN_00c5f3d0()
{
  if (GetTargetPlanet() != 0) {
    Planet* p = (Planet*)GetTargetPlanet();
    return p->mField13c;
  }
  return 0;
}

// @ 0x00c5f4e0
int Mission::FUN_00c5f4e0(int id)
{
  int v0 = (mpField1f4 != 0) ? ((Planet*)mpField1f4)->mField13c : 0;

  if (v0 != id) {
    int v1 = (GetTargetPlanet() != 0)
               ? ((Planet*)GetTargetPlanet())->mField13c
               : 0;
    if (v1 != id)
      return 0;
  }
  return 1;
}

// @ 0x00c5f530
bool cSPMissionStory201::PickUFOWreckPlanet()
{
    FUN_01021260();
    cStar* star = (cStar*)FUN_01021230();
    if (star == 0)
        return false;

    cSolarSystem* ss = star->GetSolarSystem();
    if (ss != 0) {
        int count = ss->m14 - ss->m10;
        for (int i = 0; i < count; i++) {
            cPlanet* p = ss->m10[i];
            if (p != 0) {
                void* a = p->m13c;
                if (a != FUN_01021370()) {
                    if (p->FUN_00c70fb0() > 0) {
                        cPlanet* old = m1f4;
                        if (old != 0) {
                            m1f4 = 0;
                            old->v0c0();
                        }
                        ((cStarManager*)StarManager())->GetOrActivatePlanet(p->m13c, &m1f4);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// @ 0x00c5f5f0
void cSPMissionStory201::FUN_00c5f5f0()
{
    FUN_00c46b80();
    cBioElemSort* s;
    if (GetTargetPlanet())
        s = ((cBioElemSort*)GetTargetPlanet()->m13c)->SortBanners();
    else
        s = ((cBioElemSort*)0)->SortBanners();
    s->FUN_00bb9b00(0x40000, 0);
    s->FUN_00bb9c30();
    GetMissionManager(1)->FUN_00feba80();
}

// @ 0x00c5f640
bool cSPMissionStory201::GetTagString(unsigned tag, wstring* out)
{
    if (tag == 0x7a216096)
        return TagNameHelper(m1f4, out);
    if (tag == 0xe3d3c424)
        return TagNameHelper(GetTargetPlanet(), out);
    return cSPMission::GetTagString(tag, out);
}

// @ 0x00c5fcf0
bool cSPMissionStory201::FUN_00c5fcf0()
{
    if (!Init())
        return false;
    if (!PickUFOWreckPlanet())
        return false;
    if (!FUN_00c5f770())
        return false;
    FUN_00c4a0c0();
    if (m180 != 0) {
        TryGetUIntProperty(m180, 0x637cf275, &m1f8);
        TryGetUIntProperty(m180, 0x637cf276, &m1fc);
    }
    return true;
}
