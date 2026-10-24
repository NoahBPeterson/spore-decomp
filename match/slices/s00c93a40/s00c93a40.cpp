// Slice s00c93a40 -- SP tribe per-tick update, fishing hot-spot copy/insert,
// position partition/partial-sort and debug tooltip.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (00c93dc0 uses /arch:IA32)
#include "types.h"
#include <stddef.h>

typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;
typedef unsigned short u16;

// ---------------------------------------------------------------------------
// External runtime / EASTL support.
// ---------------------------------------------------------------------------
extern "C" void* __cdecl operator_new(u32 size, const char* name, int a, int b,
                                      const char* file, int line);
extern "C" void  __cdecl operator_delete__(void* p);
extern const char g_EastlAllocator[];          // 0x013ebb38 (only its address is used)
extern const char g_SimulatorName[];           // 0x013f09b4

struct Vec3 { float x; float y; float z; };
struct CmpPos {
  float x; float y; float z;
  CmpPos() {}
  CmpPos(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};

// ---------------------------------------------------------------------------
// 0x14-byte EASTL element used by the insert helper.
// ---------------------------------------------------------------------------
struct Elem14 {
  float mX;       // 0x00
  float mY;       // 0x04
  float mZ;       // 0x08
  float mW;       // 0x0c
  u8    mTag;     // 0x10
  u8    mPad[3];  // 0x11
};

extern "C" void __cdecl CopyElems14(Elem14** out, const Elem14* first,
                                    const Elem14* last, Elem14* dst);      // 0x00c90da0
extern "C" void __cdecl FillElems14(Elem14* dst, u32 count,
                                    const Elem14* value);                  // 0x00c90df0
extern "C" Elem14* __cdecl CopyElems14Range(Elem14* first, const Elem14* last,
                                            Elem14* dst);                  // 0x00c90e40
extern "C" Elem14* __cdecl CopyBackward14(Elem14* first, Elem14* last,
                                          Elem14* resultEnd);              // 0x00c50ad0
extern "C" void __cdecl FillRange14(Elem14* first, Elem14* last,
                                    const Elem14* value);                  // 0x00f96e70

struct ElemVec14 {
  Elem14* mpBegin;     // 0x00
  Elem14* mpEnd;       // 0x04
  Elem14* mpCapacity;  // 0x08

  void insert(Elem14* pos, u32 count, const Elem14* value);
};

// ---------------------------------------------------------------------------
// Intrusive reference-counted interface.
// ---------------------------------------------------------------------------
struct IRef {
  virtual void AddRef();
  virtual void Release();
};

struct cPointerVector {
  void*    mpBegin;       // 0x00
  void*    mpEnd;         // 0x04
  void*    mpCapacity;    // 0x08
  uint32_t mAllocator[3]; // 0x0c

  cPointerVector* CopyFrom(const cPointerVector* src);   // 0x00c93810
};

// 0x58-byte fishing hot-spot value.
struct cFishingHotSpot {
  Vec3             mPos;            // 0x00
  float            mFood;           // 0x0c
  float            mMaxFood;        // 0x10
  float            mResupply;       // 0x14
  s32              mCubeIndex[3];   // 0x18
  IRef*            mpEffect;        // 0x24
  IRef*            mpHitSphere;     // 0x28
  u32              mPad_2c;         // 0x2c
  u32              mStartTimeLow;   // 0x30
  u32              mStartTimeHigh;  // 0x34
  bool             mbActive;        // 0x38
  bool             mbRemove;        // 0x39
  u8               mPad_3a[2];      // 0x3a
  IRef*            mpOrnament;      // 0x3c
  cPointerVector   mPointers;       // 0x40

  cFishingHotSpot(const cFishingHotSpot& src);
};

// ---------------------------------------------------------------------------
// Hot-spot map globals (0x60-byte rows: key at +0, value at +8).
// ---------------------------------------------------------------------------
struct HotSpotRow;

extern "C" HotSpotRow* __cdecl HotSpotLowerBound(HotSpotRow* first, HotSpotRow* last,
                                                 u32* key, u8 less);   // 0x00c92d50

extern HotSpotRow* g_HotSpotBegin;   // 0x0157abb0
extern HotSpotRow* g_HotSpotEnd;     // 0x0157abb4
extern u8          g_HotSpotLess;    // 0x0157b7c8

struct HotSpotRow {
  u32             mKey;       // 0x00
  u8              mPad_04[4]; // 0x04
  cFishingHotSpot mSpot;      // 0x08
};

cFishingHotSpot* findHotSpot(u32 key);

// ---------------------------------------------------------------------------
// Heap helpers over Vec3 with the ComparePositions functor.
// ---------------------------------------------------------------------------
extern "C" void __cdecl HeapMake(Vec3* first, Vec3* last, float x, float y, float z);          // 0x00c938f0
extern "C" void __cdecl HeapAdjust(Vec3* first, int top, int heapSize, int pos,
                                   Vec3 value, float x, float y, float z);                    // 0x00c92e20
extern "C" void __cdecl HeapSort(Vec3* first, Vec3* last, float x, float y, float z);          // 0x00c93980

void __cdecl PartitionPositions(Vec3* first, Vec3* last,
                                float px, float py, float pz,
                                float qx, float qy, float qz);

void __cdecl PartialSortPositions(Vec3* first, Vec3* mid, Vec3* last,
                                  float x, float y, float z);

// ---------------------------------------------------------------------------
// cTribe layout.
// ---------------------------------------------------------------------------
struct cSub34 { void** mpVtable; };                 // embedded at cTribe+0x34

struct cSpatial120Base {
  void** mpVtable;          // 0x000
  u8     mPad_004[0x10c];   // 0x004 .. 0x10f  (total 0x110)
};

// View used by GetDebugToolTip: this pointer is cTribe+0x120.
struct cString;
struct cSpatialView {
  void** mpVtable;          // 0x000 (cTribe+0x120)
  u8     mPad_004[0x210];   // 0x004 .. 0x213
  bool   mbFlag214;         // 0x214 (cTribe+0x334)

  void GetDebugToolTip(cString* out);   // 0x00c94470
};

struct TreeNode {
  TreeNode* mpLeft;     // 0x00
  TreeNode* mpRight;    // 0x04
  TreeNode* mpParent;   // 0x08
  u32       mColor;     // 0x0c
  u32       mKey;       // 0x10
  u32       mValue;     // 0x14
};

struct TreeHeader {
  TreeNode* mpEnd;      // 0x00
  u32       mSize;      // 0x04
  TreeNode* mpRoot;     // 0x08
  u32       mPad_0c;    // 0x0c
  u32       mPad_10;    // 0x10
  u32       mValue;     // 0x14
};

struct WString {
  wchar_t* mpBegin;      // 0x00
  wchar_t* mpEnd;        // 0x04
  wchar_t* mpCapacity;   // 0x08
};

struct cTribe;

struct cString {
  void* mpBegin;     // 0x00
  void* mpEnd;       // 0x04
  void* mpCapacity;  // 0x08

  void ctor();                                  // 0x006b5060
  void dtor();                                  // 0x006b5240
  bool Load(u32 id, u32 a, int b);              // 0x006b54b0
  const wchar_t* GetText();                     // 0x006b55c0
  void Append(const char* a, const char* b);    // 0x00455d60
};

struct cSpeciesProfile {
  void** mpVtable;
  u8     mPad_04[0x5c];

  void GetUiName(WString* out);                 // 0x004da330
};

struct cGameNounManager {
  void** mpVtable;
  u8     mPad_04[0x100];

  void FinishUpdate();                          // 0x00b6e1f0
  void* GetPlayerTribe();                       // 0x00bfc5f0
  void* GetPlayerCivilization();                // 0x00b25fb0
};

struct cRelationshipManager {
  void* GetPlayerString(void* out, cTribe* tribe, void* player);   // 0x00d01db0
  void* GetDebugString(void* out, u32 id, void* player);           // 0x00d01bb0
  float GetRelationship(void* a);                                  // 0x00d00a10
  float CalculateRelationshipEvent(void* a, void* b);              // 0x00d03d70
};

struct cStrategyResult {
  void Finish();                                // 0x00ccc400
};

struct cTribePlanner {
  u8     mPad_000[0x34];
  void** mpVtable34;       // cTribePlanner+0x34
};

struct cPos4ec {
  u8   mPad_000[0x4ec];
  Vec3 mPos;               // 0x4ec
};

struct cTarget4c {
  u8   mPad_000[0x4c];
  Vec3 mPos;               // 0x4c
};

struct cTarget180 {
  u8            mPad_000[0x180];
  cTarget4c*    mpTarget;  // 0x180
};

struct cCitizen {
  void**         mpVtable;     // 0x000
  u8             mPad_004[0xb1c]; // 0x004
  cPos4ec*       mpB20;        // 0xb20
  u8             mPad_b24[0x30];  // 0xb24
  cTarget180*    mpB54;        // 0xb54

  cSub34* sub() { return (cSub34*)((char*)this + 0x34); }
  u32  ToolEffect();                           // 0x00c22a70
  void SetToolEffect(u32 tool, int slot);      // 0x00c24f40
};

struct CitizenVec {
  cCitizen** mpBegin;      // 0x00
  cCitizen** mpEnd;        // 0x04
};

struct cNameMap230 {
  u32                mPad_00;         // 0x00
  cGameNounManager*  mpNounManager;   // 0x04 (cTribe+0x234)
  u32                mMap;            // 0x08 (cTribe+0x238)

  void Setup(WString* src);           // 0x00b6f380
};

struct cTribe {
  void**            mpVtable;         // 0x000
  u8                mPad_004[0x30];   // 0x004
  cSub34            mSub34;           // 0x034
  u8                mPad_038[0xe8];   // 0x038 .. 0x11f
  cSpatial120Base   mSpatial120;      // 0x120 .. 0x22f
  cNameMap230       mNameMap230;      // 0x230
  TreeHeader        mTree;            // 0x23c .. 0x253
  u8                mPad_254[0xe0];   // 0x254 .. 0x333
  bool              mbFlag334;        // 0x334
  u8                mPad_335[3];      // 0x335
  u32               mCount338;        // 0x338
  bool              mbFlag33c;        // 0x33c
  u8                mPad_33d[0x2b];   // 0x33d .. 0x367
  cTribePlanner*    mpPlanner;        // 0x368
  u8                mPad_36c[0x1560]; // 0x36c .. 0x18cb
  cSpeciesProfile*  mpSpeciesProfile; // 0x18cc

  cSub34* sub() { return (cSub34*)((char*)this + 0x34); }
  cGameNounManager* nounManager() { return mNameMap230.mpNounManager; }
};

typedef char check_spatial[(offsetof(cTribe, mSpatial120) == 0x120) ? 1 : -1];
typedef char check_namemap[(offsetof(cTribe, mNameMap230) == 0x230) ? 1 : -1];
typedef char check_tree[(offsetof(cTribe, mTree) == 0x23c) ? 1 : -1];
typedef char check_planner[(offsetof(cTribe, mpPlanner) == 0x368) ? 1 : -1];
typedef char check_profile[(offsetof(cTribe, mpSpeciesProfile) == 0x18cc) ? 1 : -1];

// ---------------------------------------------------------------------------
// External callees.
// ---------------------------------------------------------------------------
extern "C" Vec3* __cdecl FUN_00b6f0c0(cGameNounManager* mgr);            // 0x00b6f0c0
extern "C" void* __cdecl FUN_00cd40b0();                                 // 0x00cd40b0
extern "C" void* __cdecl FUN_00829110(void** out, void* first, void* last,
                                      void* dst, void* ctx);             // 0x00829110

extern "C" void* __cdecl FUN_00b3d2c0();                                 // 0x00b3d2c0
extern "C" void* __cdecl FUN_00b3d300();                                 // 0x00b3d300
extern "C" void* __cdecl FUN_00b5b800();                                 // 0x00b5b800
extern "C" void* __cdecl FUN_01021300();                                 // 0x01021300
extern "C" void* __cdecl FUN_00d026d0();                                 // 0x00d026d0
extern "C" void  __cdecl FUN_00454cb0(char* src, u32 len);               // 0x00454cb0
extern "C" void  __cdecl FUN_00472fe0(void* out, const char* fmt, ...);  // 0x00472fe0
extern "C" void  __cdecl FUN_005f9450(void* str, const char* fmt, ...);  // 0x005f9450

extern u8 g_GameModeTribe;    // 0x01654c02
extern u8 g_GameModeCiv;      // 0x01654c04
extern u8 g_GameModeSpace;    // 0x01654c05

#define VF(p, off) (*(void**)((char*)(*(void**)p) + (off)))

// ---------------------------------------------------------------------------
// @ 0x00c93a40 - per-tick tribe update.
// ---------------------------------------------------------------------------
void __fastcall TribeUpdate(cTribe* self)
{
  typedef bool (__thiscall* IsValidFn)(void*);
  IsValidFn isValid = (IsValidFn)VF(&self->mSpatial120, 0x58);
  bool valid = isValid(&self->mSpatial120);

  if (!valid) {
    CitizenVec* vec = (CitizenVec*)((void*(__thiscall*)(cTribe*))VF(self, 0x90))(self);
    cCitizen** p = vec->mpBegin;
    while (p != vec->mpEnd) {
      cCitizen* c = *p;
      if (c != 0 && c->mpB20 != 0) {
        Vec3* pos = FUN_00b6f0c0(self->nounManager());
        ((void(__thiscall*)(cCitizen*, Vec3*))VF(c, 0xe4))(c, pos);

        if (c->mpB54 != 0 && c->mpB54->mpTarget != 0) {
          c->mpB54->mpTarget->mPos = c->mpB20->mPos;
        }

        u32 tool = c->ToolEffect();
        c->SetToolEffect(0, -1);
        c->SetToolEffect(tool, -1);

        void* strategy = FUN_00cd40b0();
        cStrategyResult* result = (cStrategyResult*)((void*(__thiscall*)(void*, cCitizen*))VF(strategy, 0x6c))(strategy, c);
        result->Finish();
      }
      ++p;
    }
  }

  if (self->mpPlanner != 0) {
    cSub34* sub = (cSub34*)((char*)self->mpPlanner + 0x34);
    cTarget4c* target = (cTarget4c*)((void*(__thiscall*)(void*))VF(sub, 0xac))(sub);
    if (target != 0) {
      Vec3* pos = FUN_00b6f0c0(self->nounManager());
      cSub34* sub2 = (cSub34*)((char*)self->mpPlanner + 0x34);
      cTarget4c* target2 = (cTarget4c*)((void*(__thiscall*)(void*))VF(sub2, 0xac))(sub2);
      target2->mPos = *pos;
    }
  }

  CitizenVec* sel = (CitizenVec*)((void*(__thiscall*)(cTribe*))VF(self, 0xbc))(self);
  u32 count = (u32)(sel->mpEnd - sel->mpBegin);
  cCitizen** arr = 0;
  if (count != 0) {
    arr = (cCitizen**)operator_new(count * 4, g_SimulatorName, 0, 0,
                                   g_EastlAllocator, 0xd1);
  }
  cCitizen** out = 0;
  FUN_00829110((void**)&out, sel->mpBegin, sel->mpEnd, arr, sel);

  for (cCitizen** q = arr; q != out; ++q) {
    cCitizen* c = *q;
    cSub34* sub = c->sub();
    cTarget4c* target = (cTarget4c*)((void*(__thiscall*)(void*))VF(sub, 0xac))(sub);
    if (target != 0) {
      Vec3* pos = FUN_00b6f0c0(self->nounManager());
      cSub34* sub2 = c->sub();
      cTarget4c* target2 = (cTarget4c*)((void*(__thiscall*)(void*))VF(sub2, 0xac))(sub2);
      target2->mPos = *pos;
    }
  }

  wchar_t* empty = (wchar_t*)0x01667bac;
  WString name;
  name.mpBegin = empty;
  name.mpEnd = empty;
  name.mpCapacity = (wchar_t*)0x01667bae;
  self->mpSpeciesProfile->GetUiName(&name);
  self->mNameMap230.Setup(&name);

  IsValidFn isValid2 = (IsValidFn)VF(&self->mSpatial120, 0x58);
  u32 key = isValid2(&self->mSpatial120) ? 0 : 0xe;

  TreeNode* node = self->mTree.mpRoot;
  TreeNode* end = (TreeNode*)&self->mTree;
  TreeNode* candidate = end;
  while (node != 0) {
    if (node->mKey < key)
      node = node->mpLeft;
    else {
      node = node->mpRight;
      candidate = node;
    }
  }
  if (candidate == end || key < candidate->mKey)
    candidate = end;

  ((void(__thiscall*)(cSub34*, u32))VF(&self->mSub34, 0))(&self->mSub34, candidate->mValue);
  self->nounManager()->FinishUpdate();

  if ((char*)name.mpEnd - (char*)name.mpBegin > 2 && name.mpBegin != 0)
    operator_delete__(name.mpBegin);

  if (arr != 0) {
    for (cCitizen** q = arr; q != out; ++q) {
      cCitizen* c = *q;
      if (c != 0)
        ((void(__thiscall*)(cCitizen*))VF(c, 4))(c);
    }
    if (((s32*)arr)[-1] != 0)
      operator_delete__(arr);
  }
}

// ---------------------------------------------------------------------------
// @ 0x00c93dc0 - cFishingHotSpot copy constructor.
// ---------------------------------------------------------------------------
cFishingHotSpot::cFishingHotSpot(const cFishingHotSpot& src)
{
  mPos.x = src.mPos.x;
  mPos.y = src.mPos.y;
  mPos.z = src.mPos.z;
  mFood = src.mFood;
  mMaxFood = src.mMaxFood;
  mResupply = src.mResupply;

  mCubeIndex[0] = src.mCubeIndex[0];
  mCubeIndex[1] = src.mCubeIndex[1];
  mCubeIndex[2] = src.mCubeIndex[2];

  mpEffect = src.mpEffect;
  if (mpEffect != 0)
    mpEffect->AddRef();

  mpHitSphere = src.mpHitSphere;
  if (mpHitSphere != 0)
    mpHitSphere->AddRef();

  mStartTimeLow = src.mStartTimeLow;
  mStartTimeHigh = src.mStartTimeHigh;
  mbActive = src.mbActive;
  mbRemove = src.mbRemove;

  mpOrnament = src.mpOrnament;
  if (mpOrnament != 0)
    mpOrnament->AddRef();

  mPointers.CopyFrom(&src.mPointers);
}

// ---------------------------------------------------------------------------
// @ 0x00c93e60 - ElemVec14::insert(pos, count, value).
// ---------------------------------------------------------------------------
void ElemVec14::insert(Elem14* pos, u32 count, const Elem14* value)
{
  if (count > (u32)(mpCapacity - mpEnd)) {
    u32 oldSize = (u32)(mpEnd - mpBegin);
    u32 newCap = oldSize * 2;
    if (oldSize == 0)
      newCap = 1;
    u32 want = oldSize + count;
    if (want > newCap)
      newCap = want;

    Elem14* newBuf = 0;
    if (newCap != 0)
      newBuf = (Elem14*)operator_new(newCap * sizeof(Elem14), g_SimulatorName, 0, 0,
                                     g_EastlAllocator, 0xd1);

    Elem14* cursor = CopyElems14Range(mpBegin, pos, newBuf);
    FillElems14(cursor, count, value);
    cursor += count;
    Elem14* newEnd = CopyElems14Range(pos, mpEnd, cursor);

    if (mpBegin != 0 && ((s32*)mpBegin)[-1] != 0)
      operator_delete__(mpBegin);

    mpBegin = newBuf;
    mpEnd = newEnd;
    mpCapacity = newBuf + newCap;
  } else if (count != 0) {
    Elem14 valueCopy;
    valueCopy.mTag = value->mTag;
    valueCopy.mX = value->mX;
    valueCopy.mY = value->mY;
    valueCopy.mZ = value->mZ;
    valueCopy.mW = value->mW;

    Elem14* oldEnd = mpEnd;
    u32 after = (u32)(oldEnd - pos);
    if (count < after) {
      Elem14* cut = oldEnd - count;
      CopyElems14((Elem14**)&value, cut, oldEnd, oldEnd);
      mpEnd = oldEnd + count;
      CopyBackward14(pos, cut, oldEnd);
      FillRange14(pos, pos + count, &valueCopy);
    } else {
      u32 extra = count - after;
      FillElems14(oldEnd, extra, &valueCopy);
      mpEnd = oldEnd + extra;
      CopyElems14((Elem14**)&pos, pos, oldEnd, mpEnd);
      mpEnd += after;
      FillRange14(pos, oldEnd, &valueCopy);
    }
  }
}

// ---------------------------------------------------------------------------
// @ 0x00c940d0 - partition a cSPVector3 range around a squared-distance pivot.
// ---------------------------------------------------------------------------
void __cdecl PartitionPositions(Vec3* first, Vec3* last,
                                float px, float py, float pz,
                                float qx, float qy, float qz)
{
  float dx = qx - px;
  float dy = qy - py;
  float dz = qz - pz;

  for (;;) {
    for (;;) {
      float ax = qx - first->x;
      float ay = qy - first->y;
      float az = qz - first->z;
      if (dx * dx + dy * dy + dz * dz <= ax * ax + ay * ay + az * az)
        break;
      ++first;
    }
    do {
      --last;
      float bx = qx - last->x;
      float by = qy - last->y;
      float bz = qz - last->z;
      if (dx * dx + dy * dy + dz * dz >= bx * bx + by * by + bz * bz)
        break;
    } while (true);

    if (last <= first)
      break;

    float tx = first->x, ty = first->y, tz = first->z;
    first->x = last->x;
    first->y = last->y;
    first->z = last->z;
    last->x = tx;
    last->y = ty;
    last->z = tz;
    ++first;
  }
}

// ---------------------------------------------------------------------------
// @ 0x00c94270 - partial_sort of positions by distance to (x,y,z).
// ---------------------------------------------------------------------------
void __cdecl PartialSortPositions(Vec3* first, Vec3* mid, Vec3* last,
                                  float x, float y, float z)
{
  HeapMake(first, mid, x, y, z);

  for (Vec3* p = mid; p < last; ++p) {
    float ax = x - p->x;
    float ay = y - p->y;
    float az = z - p->z;
    float da = ax * ax + ay * ay + az * az;

    float bx = x - first->x;
    float by = y - first->y;
    float bz = z - first->z;
    float db = bx * bx + by * by + bz * bz;

    if (da < db) {
      Vec3 tmp = *p;
      *p = *first;
      HeapAdjust(first, 0, (int)(mid - first), 0, tmp, x, y, z);
    }
  }

  HeapSort(first, mid, x, y, z);
}

// ---------------------------------------------------------------------------
// @ 0x00c94430 - hot-spot map lookup.
// ---------------------------------------------------------------------------
cFishingHotSpot* findHotSpot(u32 key)
{
  HotSpotRow* end = g_HotSpotEnd;
  HotSpotRow* it = HotSpotLowerBound(g_HotSpotBegin, end, &key, g_HotSpotLess);
  if (it != end && key >= it->mKey && it != &it[1])
    return &it->mSpot;
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00c94470 - SP::cTribe::GetDebugToolTip.
// `self` is the spatial sub-object at cTribe+0x120.
// ---------------------------------------------------------------------------
void cSpatialView::GetDebugToolTip(cString* out)
{
  cTribe* tribe = (cTribe*)((char*)this - offsetof(cTribe, mSpatial120));

  cString text;
  text.ctor();

  void* relMgr = FUN_00b3d2c0();
  void* mode = FUN_00b5b800();

  char* selected = 0;
  char* selectedEnd = 0;
  if (mode == &g_GameModeTribe) {
    void* nouns = FUN_00b3d300();
    void* player = ((cGameNounManager*)nouns)->GetPlayerTribe();
    void* s = ((cRelationshipManager*)relMgr)->GetPlayerString(&text, tribe, player);
    if (s != &text) {
      selected = *(char**)s;
      selectedEnd = *((char**)s + 1);
    }
  } else if (mode == &g_GameModeCiv) {
    void* nouns = FUN_00b3d300();
    void* player = ((cGameNounManager*)nouns)->GetPlayerCivilization();
    void* s = ((cRelationshipManager*)relMgr)->GetPlayerString(&text, tribe, player);
    if (s != &text) {
      selected = *(char**)s;
      selectedEnd = *((char**)s + 1);
    }
  } else if (mode == &g_GameModeSpace) {
    void* empire = FUN_01021300();
    void* player = *(void**)((char*)empire + 0x84);
    u32 id = ((u32(__thiscall*)(cTribe*))VF(tribe, 0x4c))(tribe);
    void* s = ((cRelationshipManager*)relMgr)->GetDebugString(&text, id, player);
    if (s != &text) {
      selected = *(char**)s;
      selectedEnd = *((char**)s + 1);
    }
  }

  if (selectedEnd - selected > 1 && selected != 0)
    operator_delete__(selected);

  u32 count;
  if (this->mbFlag214 != 0 && tribe->mbFlag33c == 0)
    count = tribe->mCount338;
  else {
    CitizenVec* v = (CitizenVec*)((void*(__thiscall*)(cTribe*))VF(tribe, 0x90))(tribe);
    count = (u32)(v->mpEnd - v->mpBegin);
  }

  u32 food = ((u32(__thiscall*)(cTribe*))VF(tribe, 0xa4))(tribe);
  FUN_00472fe0(out, "Tribe\n%s\nPopulation = %d\nFood = %d", &text, count, food);

  if (mode == &g_GameModeTribe) {
    bool valid = ((bool(__thiscall*)(cSpatialView*))VF(this, 0x58))(this);
    if (!valid) {
      out->Append("\nRelationship Events:", "");

      cString line;
      line.ctor();

      void* nouns = FUN_00b3d300();
      void* playerTribe = ((cGameNounManager*)nouns)->GetPlayerTribe();
      u32 a = ((u32(__thiscall*)(void*))VF(playerTribe, 0x4c))(playerTribe);
      u32 b = ((u32(__thiscall*)(cTribe*))VF(tribe, 0x4c))(tribe);
      relMgr = FUN_00b3d2c0();
      float f = ((cRelationshipManager*)relMgr)->GetRelationship((void*)a);
      FUN_005f9450(out, "\n  This Tribe Feelings for Player [%.3f]:", (double)f);

      CitizenVec* events = (CitizenVec*)FUN_00d026d0();
      for (cCitizen** p = events->mpBegin; p != events->mpEnd; ++p) {
        u32 ev = (u32)*p;
        u32 c = ((u32(__thiscall*)(void*))VF(playerTribe, 0x4c))(playerTribe);
        u32 d = ((u32(__thiscall*)(cTribe*))VF(tribe, 0x4c))(tribe);
        relMgr = FUN_00b3d2c0();
        float val = ((cRelationshipManager*)relMgr)->CalculateRelationshipEvent((void*)c, (void*)d);
        float absVal = val < 0 ? -val : val;
        if (absVal >= 0.1f) {
          line.Load(0xa14ee9b6, ev, 0);
          const wchar_t* s = line.GetText();
          FUN_005f9450(out, "\n    %ls [%.3f]", s, (double)val);
        }
      }

      for (cCitizen** p = events->mpBegin; p != events->mpEnd; ++p) {
        u32 ev = (u32)*p;
        u32 c = ((u32(__thiscall*)(void*))VF(tribe, 0x4c))(tribe);
        u32 d = ((u32(__thiscall*)(void*))VF(playerTribe, 0x4c))(playerTribe);
        relMgr = FUN_00b3d2c0();
        float val = ((cRelationshipManager*)relMgr)->CalculateRelationshipEvent((void*)c, (void*)d);
        float absVal = val < 0 ? -val : val;
        if (absVal >= 0.1f) {
          line.Load(0xa14ee9b6, ev, 0);
          const wchar_t* s = line.GetText();
          FUN_005f9450(out, "\n    %ls [%.3f]", s, (double)val);
        }
      }

      line.GetText();
      line.dtor();
    }
  }

  text.dtor();
}
