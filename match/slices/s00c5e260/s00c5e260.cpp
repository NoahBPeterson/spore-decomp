// Decompiled slice s00c5e260 -- Simulator/SP mission objects.
// Reconstructed from the shipped binary; helper addresses noted per call.
#include "types.h"

// ---------------------------------------------------------------------------
// shared shapes
// ---------------------------------------------------------------------------
struct Vtbl { void* p[64]; };

typedef int   (__thiscall* FnI0)(void*);
typedef char  (__thiscall* FnC0)(void*);
typedef void* (__thiscall* FnP1)(void*, int);
typedef void  (__thiscall* FnV1)(void*, int);
typedef void  (__thiscall* FnV2)(void*, void*, int);
typedef void  (__thiscall* FnV3)(void*, void*, int, int);
typedef void  (__thiscall* FnVoid)(void*);

struct Planet {
  uint8_t mPad000[0x13c];
  int     mField13c;      // +0x13c
};

struct PlanetFilter {
  int  mField0;           // +0x00
  int  mPad04[0x11];      // +0x04 .. +0x47
  void FUN_00ba7bd0();    // 0x00ba7bd0 (constructor)
  void FUN_00ba8220();    // 0x00ba8220 (destructor)
};

struct TargetObj {
  void FUN_00c74690();    // 0x00c74690
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

struct cGameNounManager {
  void* GetPlayerTribe();          // 0x00bfc5f0
};

struct TribeObj {
  void FUN_00fe5430();             // 0x00fe5430
};

// Small vector returned by the +0x180 object's slot 0x28 method.
struct SomeVec {
  void*    mpField0;      // +0x00
  int      mPad04;        // +0x04
  int      mField8;       // +0x08
  int      mPad0C;        // +0x0c
  uint16_t mField10;      // +0x10
  uint16_t mField12;      // +0x12
};

// ---------------------------------------------------------------------------
// mission base object (cGenericPressureEvent layout shared by both missions)
// ---------------------------------------------------------------------------
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

struct MissionScan : Mission {
  MissionScan();                  // 0x00c5e740
};

struct MissionStory201 : Mission {
  MissionStory201();              // 0x00c5f1b0
};

namespace SP {
  void* __stdcall SpaceGameGet(int a, int b); // 0x01002bd0
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

// The shared base constructor lives outside this translation unit.
void __fastcall MissionBaseCtor(void* self);

// ===========================================================================
// 0x00c5e740 -- Simulator::cMissionScan::cMissionScan
// ===========================================================================
// @ 0x00c5e740
MissionScan::MissionScan()
{
  MissionBaseCtor(this);
  mpVtable  = (Vtbl*)0x146fc00;
  mpField04 = (void*)0x146dfb4;
  mpField34 = (void*)0x146fbf0;
  mField1f0 = 0;
  mpField1f4 = (void*)*(int*)0x16925c0;
  mField1f8 = *(int*)0x16925c4;
  mField1fc = *(int*)0x16925c8;
}

// ===========================================================================
// 0x00c5ea60 -- SP::cSPMissionScan::Init
// ===========================================================================
// @ 0x00c5ea60
char Mission::FUN_00c5ea60()
{
  if (!Init())
    return 0;

  int t = FUN_00c45b40();
  void* rec = GetPlanetRecordFromTargetType(t);
  if (rec != 0)
    FUN_00c47180(rec);

  uint32_t raw = *(volatile uint32_t*)&mField130;
  raw >>= 3;
  if ((raw & 1) != 0 && (uint32_t)mField078 == 0x89238409u) {
    void* p = (void*)((char*)this + 0x170);
    int species = ReadTargetAnimalSpeciesType(p);
    GetAnimalSpeciesFromType(species);
    void* obj = GetTargetPlanet(p, 0, 0);
    ((TargetObj*)obj)->FUN_00c74690();
  }

  if (GetTargetPlanet() == 0) {
    PlanetFilter filter;
    filter.FUN_00ba7bd0();
    filter.mField0 = 0x38;
    void* picked = PickPlanet(&filter);
    if (picked == 0) {
      filter.FUN_00ba8220();
      return 0;
    }
    FUN_00c47180(picked);
    filter.FUN_00ba8220();
  }

  if (((FnC0)mpVtable->p[0x128 / 4])(this) == '\0')
    return 0;
  FUN_00c4a0c0();
  ((FnVoid)mpVtable->p[0x170 / 4])(this);
  return 1;
}
// ===========================================================================
// 0x00c5ed90 -- set the mission state and refresh the UI
// ===========================================================================
// @ 0x00c5ed90
void Mission::FUN_00c5ed90(int v)
{
  if (mField1f0 != v) {
    mField1f0 = v;
    TriggerUIUpdate();
  }
}

// ===========================================================================
// 0x00c5edb0 -- install six message handlers, then register with the server
// ===========================================================================
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

// ===========================================================================
// 0x00c5ee40 -- remove six message handlers, then deregister
// ===========================================================================
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

// ===========================================================================
// 0x00c5eed0 -- medium UI description
// ===========================================================================
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

// ===========================================================================
// 0x00c5efb0 -- long UI description
// ===========================================================================
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

// ===========================================================================
// 0x00c5f090 -- conversation group id for the current state
// ===========================================================================
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

// ===========================================================================
// 0x00c5f0f0 -- dynamic response id for the current state
// ===========================================================================
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

// ===========================================================================
// 0x00c5f150 -- true while the mission is in state 0 or 1
// ===========================================================================
// @ 0x00c5f150
int Mission::FUN_00c5f150()
{
  if (mField1f0 != 0 && mField1f0 != 1)
    return 0;
  return 1;
}

// ===========================================================================
// 0x00c5f190 -- release the player tribe's game data
// ===========================================================================
// @ 0x00c5f190
void FUN_00c5f190()
{
  FUN_00c47a10();
  cGameNounManager* m = (cGameNounManager*)SP::SpaceGameGet(0x11, 1);
  TribeObj* t = (TribeObj*)m->GetPlayerTribe();
  t->FUN_00fe5430();
}

// ===========================================================================
// 0x00c5f1b0 -- Simulator::cMissionStory201::cMissionStory201
// ===========================================================================
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

// ===========================================================================
// 0x00c5f250 -- release the target planet object, then reset
// ===========================================================================
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

// ===========================================================================
// 0x00c5f280 -- SP::cSPMissionStory201::ReturnForRewards
// ===========================================================================
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

// ===========================================================================
// 0x00c5f2c0 -- give every entry of the player's inventory reward item
// ===========================================================================
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

// ===========================================================================
// 0x00c5f360 -- initialize and hand out rewards if still active
// ===========================================================================
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

// ===========================================================================
// 0x00c5f3d0 -- target planet's field 0x13c
// ===========================================================================
// @ 0x00c5f3d0
int Mission::FUN_00c5f3d0()
{
  if (GetTargetPlanet() != 0) {
    Planet* p = (Planet*)GetTargetPlanet();
    return p->mField13c;
  }
  return 0;
}

// ===========================================================================
// 0x00c5f4e0 -- compare the current and target planet's field 0x13c
// ===========================================================================
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
