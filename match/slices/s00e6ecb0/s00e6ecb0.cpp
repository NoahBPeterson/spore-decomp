// @ 0x00e6ecb0
// SP::sHatchFromIce_Start (SPGonzago, SPCellGame.obj).
// NOTE: retail reads its argument from ESI at entry ([esi] is the cell handle,
// esi itself is forwarded to 0x00e66840 and 0x00e5ec70) and never saves it, so
// the retail build used MSVC's custom convention for internal functions (the
// same mechanism that gives 0x00e5ec70 its handle in EAX). That needs a static
// function plus call sites in the TU; with them MSVC passes the cell in EDI
// here instead of retail's ESI.
#include "game/types.h"

struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };

struct cObjectPool {
  char  mReserved[0x38];
  void* Get(int handle);          // 0x00b72210  thiscall
  int   Alloc();                  // 0x00b72160  thiscall
  void* GetSafe(int handle);      // 0x00b721d0  thiscall
};

struct cCellGame {
  char        mReserved00[0x1c];
  cObjectPool mCells;             // +0x001c
  cObjectPool mPool54;            // +0x0054
  char        mReserved8c[0x5194 - 0x8c];
  int         mSpawnHandle5194;   // +0x5194
};

struct cCell {
  int  mHandle;                   // +0x000
  char mReserved04[0x178 - 0x04];
  char mFlag178;                  // +0x178
  char mReserved179[0x17b - 0x179];
  char mFlag17b;                  // +0x17b
  char mFlag17c;                  // +0x17c
  char mReserved17d[0x18c - 0x17d];
  int  mMode;                     // +0x18c
  char mReserved190[0x1ac - 0x190];
  char mFlag1ac;                  // +0x1ac
  char mReserved1ad[0x1b0 - 0x1ad];
  int  mField1b0;                 // +0x1b0
};

struct cIceEffect {
  virtual void v00();             // +0x00
};

struct cSpawnParams {
  char       mReserved00[0x04];
  int        mField04;            // +0x04
  char       mByte08;             // +0x08
  char       mReserved09[0x1c - 0x09];
  float      mField1c;            // +0x1c
  float      mField20;            // +0x20
  int        mField24;            // +0x24
  int        mHandle28;           // +0x28
  int        mField2c;            // +0x2c
  int        mField30;            // +0x30
  int        mField34;            // +0x34
  int        mField38;            // +0x38
  int        mField3c;            // +0x3c
  float      mField40;            // +0x40
  float      mField44;            // +0x44
  Vector3    mPos48;              // +0x48
  Vector3    mPos54;              // +0x54
  Quaternion mQuat60;             // +0x60
  cIceEffect* mpEffect70;         // +0x70
  char       mByte74;             // +0x74
  char       mReserved75[3];
  int        mField78;            // +0x78
};

struct cTempKey {
  void Init();                    // 0x00ae0930  thiscall
};

extern cCellGame* gspCellGame;    // 0x016b3c04
extern Vector3    gCellPosition;  // 0x016b3c28
extern Quaternion gKSpawnQuat;    // 0x015a7c4c

uint32_t __cdecl FUN_00932e80(const char* name, uint32_t seed, int flag); // 0x00932e80
void*    __cdecl FUN_00e66840(cCell* owner, uint32_t key);                // 0x00e66840
cTempKey* __stdcall FUN_00b3d4d0(const char* name, int, int, int, int, int); // 0x00b3d4d0
float    __cdecl FUN_00e6d200(cCell* cell, int a, int mode, int field);    // 0x00e6d200

// sCellSpawn44 is internal in retail (its own custom convention takes the
// handle in EAX), so its definition has to live in this TU, not an extern
// declaration -- otherwise the call below cannot pass the handle in EAX.
static __declspec(noinline) bool sCellSpawn44(int handle, float dist);

struct cHandleRef {
  cHandleRef();                   // 0x00743b50
  ~cHandleRef();                  // 0x00e82130
  int mValue;
};

struct cLayerCatalog {
  char mReserved[0xdc];
  int  mCount;                    // +0xdc
};

extern int         gCell516c;     // 0x016b3c10
extern const float gKOneSpawn;    // 0x015a8438
extern const Vector3 gKSpawnPos;  // 0x015a7d3c
cLayerCatalog* __cdecl FUN_00e4ce40(cHandleRef* ref);                     // 0x00e4ce40
void __cdecl FUN_00e56870();                                             // 0x00e56870
void __cdecl sCellSetPosition(cCell* cell, const Vector3* pos);           // 0x00e5e590

// @ 0x00e6ecb0
static void sHatchFromIce_Start(cCell* cell)
{
  uint32_t key = FUN_00932e80("sHatchFromIce", 0x811c9dc5u, 1);
  cIceEffect* effect = (cIceEffect*)FUN_00e66840(cell, key);
  effect->v00();

  cTempKey* tmpKey = FUN_00b3d4d0("sHatchFromIce", 0, 0, 0, 0, 0);
  tmpKey->Init();

  int targetHandle = cell->mHandle;
  cObjectPool& cells = gspCellGame->mCells;
  cCell* target = (cCell*)cells.Get(targetHandle);
  float dist = FUN_00e6d200(target, 0, 0x2c, target->mField1b0);

  int handle = cell->mHandle;
  int slot = gspCellGame->mPool54.Alloc();
  cObjectPool& pool54 = gspCellGame->mPool54;
  cSpawnParams* params = (cSpawnParams*)pool54.Get(slot);
  params->mField1c = dist;
  params->mField20 = dist;
  params->mHandle28 = handle;
  params->mField24 = 0x1b;
  params->mField2c = 0;
  params->mField38 = 0;
  params->mField3c = 0;
  params->mField40 = 0.0f;
  params->mField44 = 0.0f;
  params->mField30 = -1;
  params->mField34 = -1;
  params->mPos48 = gCellPosition;
  params->mPos54 = gCellPosition;
  params->mQuat60 = gKSpawnQuat;
  params->mpEffect70 = effect;
  params->mByte74 = 0;
  params->mField78 = 0;
  params->mField04 = 0;
  params->mByte08 = 0;

  gspCellGame->mSpawnHandle5194 = slot;

  sCellSpawn44(cell->mHandle, dist);
}

// Real body of 0x00e5ec70 (slice s00e5eb20), defined here so that the call
// above is compiled against the same internal custom convention.
static __declspec(noinline) bool sCellSpawn44(int handle, float dist)
{
  cObjectPool& cells = gspCellGame->mCells;
  cCell* cell = (cCell*)cells.GetSafe(handle);
  if (!cell)
    return false;
  int n;
  {
    cHandleRef ref;
    n = FUN_00e4ce40(&ref)->mCount;
  }
  if (n == 0) {
    cObjectPool& pool54 = gspCellGame->mPool54;
    void* found = pool54.GetSafe(gCell516c);
    if (gKOneSpawn > dist && found == 0)
      FUN_00e56870();
  }
  cell->mFlag178 = 1;
  cell->mFlag17c = 1;
  cell->mFlag17b = 1;
  cell->mMode = 0x2c;
  cell->mFlag1ac = 0;
  sCellSetPosition(cell, &gKSpawnPos);
  return true;
}

// Retail's sHatchFromIce_Start is an internal (static) function: MSVC only
// selects its custom register convention -- the cell arriving in ESI -- when
// the translation unit contains its call sites, so these two entry points
// stand in for them.
void sHatchFromIce_Begin(cCell* cell) { sHatchFromIce_Start(cell); }
void sHatchFromIce_BeginAlt(cCell* cell) { sHatchFromIce_Start(cell); }
