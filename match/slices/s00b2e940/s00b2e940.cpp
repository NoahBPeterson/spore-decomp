// s00b2e940.cpp — SP::cAppModeTerrainEditor / cGameTerrainCursor region (mostly unnamed in PDB)
// Reconstructed from Ghidra decompiles + disassembly.  __thiscall entries are modelled as
// member methods of `S` (cl rejects __thiscall on free functions); virtual dispatch goes through
// __thiscall function-pointer typedefs so no edx gets clobbered at the call site.

#include <stddef.h>

typedef unsigned char      u8;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef void  (__thiscall *TCV0)(void*);
typedef void  (__thiscall *TCV1)(void*, int);
typedef void  (__thiscall *TCV2)(void*, int, int);
typedef void  (__thiscall *TCV3)(void*, int, int, int);
typedef void* (__thiscall *TCP0)(void*);
typedef void* (__thiscall *TCP1)(void*, int);
typedef void* (__thiscall *TCP5)(void*, void*, int, void*, void*, int);
typedef int   (__thiscall *TCI1)(void*, int);
typedef char  (__thiscall *TCR2)(void*, unsigned, int**);
typedef void  (__thiscall *TCVV)(void*, void*, int);
#define VTO(o) (*(void***)(o))

// ---- cursor object data layout ---------------------------------------------
// 0x24-byte "noun under cursor" record kept in the vector at +0x17c.
struct CursorEntry {
  u32 mField00;                  // +0x00
  u32 mId04;                     // +0x04  matched against the message payload
  u32 mId08;                     // +0x08  matched against the message payload
  u8  mPad0c[0x20 - 0x0c];
  u32 mFlags20;                  // +0x20  bit1 = candidate
};

// Intrusive red/black tree node: the 32-bit cell key at +0x10, the slot list at +0x14.
struct CursorMapNode {
  void* mpLeft;                  // +0x00
  void* mpRight;                 // +0x04
  u32   mField08;                // +0x08
  u32   mField0c;                // +0x0c
  u32   mKey;                    // +0x10
  void* mpValue;                 // +0x14
};

// Cursor slot map.  The end() iterator is the address of the sentinel node that
// is embedded at +0x04 (i.e. `this + 4`).
struct CursorMap {
  u32  mField00;                 // +0x00
  u8   mAnchorNode[8];           // +0x04  embedded sentinel -> the end iterator
  CursorMapNode* mpRoot;         // +0x0c
  u32  mFlag10;                  // +0x10
  u32  mCount14;                 // +0x14
  void* End() { return &mAnchorNode[0]; }
  void  Find(void* out, void* key);                    // 0x00e5c780
  void  EraseKey(void* key);                           // 0x00b2b5b0
  void  Insert(void* out, u32* key, u32 extra);        // 0x00ba8420
};

// eastl-style fixed-capacity vector: 0x18-byte header followed by inline storage.
template <typename T, int N>
struct FixedVec {
  T*  mpBegin;                   // +0x00
  T*  mpEnd;                     // +0x04
  T*  mpCapacity;                // +0x08
  u32 mField0c;                  // +0x0c
  u32 mField10;                  // +0x10
  u32 mAllocFlag;                // +0x14  non-zero once heap storage is used
  T   mBuffer[N];                // +0x18
  FixedVec() {
    mpBegin = mBuffer;
    mpEnd = mBuffer;
    mpCapacity = mBuffer + N;
    mAllocFlag = 0;
  }
  unsigned Size() const { return (unsigned)(mpEnd - mpBegin); }
  void Release();                // 0x007a41a0
};

// Slot list built by 0x00b2c230: array of per-slot AutoRefCounts plus the cell key.
struct CursorSlotList {
  u32   mField00;                // +0x00
  u32   mField04;                // +0x04
  u32   mCount08;                // +0x08  number of slots
  void** mpSlots0c;              // +0x0c  slot vector begin
  void*  mpSlotsEnd10;           // +0x10
  void*  mpSlotsCap14;           // +0x14
  u8    mPad18[0x120 - 0x18];
  u64   mKey120;                 // +0x120  packed cell key
};

// 12-byte descriptor handed to the slot-spawn helper at 0x00b2b2d0.
struct CursorHitInfo {
  u32 mCellId;                   // +0x00
  u32 mTypeId;                   // +0x04  0x00b1b104
  u32 mPropertyId;               // +0x08  0x01568d3c
};

// 0x10-byte result of the map insert at 0x00ba8420.
struct CursorMapInsert {
  void* mpNode;                  // +0x00  (written by Insert)
  u32   mInserted;               // +0x04  (written by Insert)
  u32   mKey;                    // +0x08  key handed in
  void* mpExtra;                 // +0x0c  value handed in
};

// ---- thiscall helpers (addresses in comments) ------------------------------
struct E {
  void* GetAvatar();                             // 0x00b1fdb0
  void* func8Ch();                               // 0x00ad2800
  void  e830();                                  // 0x00b2e830
  void  bb90();                                  // 0x00b2bb90
  void  dac0();                                  // 0x00b2dac0
  void  bbe0();                                  // 0x00b2bbe0
  void  ProcessPending();                        // 0x00b22960
  void  removeNoun(void*);                       // 0x00b225d0
  void  b090(int);                               // 0x00b2b090
  void  b5b0(void*);                             // 0x00b2b5b0
  void* c230();                                  // 0x00b2c230
  void  ff35e0(int);                             // 0x00ff35e0
  void  bc3170();                                // 0x00bc3170
  void  bc30f0();                                // 0x00bc30f0  cSPTimer::Start
  void  a110();                                  // 0x00b2a110
  void  nukeSubtree(void*);                      // 0x009a9600
  void* b03320(int,int,int);                     // 0x00b03320
  void* b72410(int,int);                         // 0x00b72410
  void  b2b600(int*, int*);                      // 0x00b2b600
  int   b2b6a0(int,int,int,int);                 // 0x00b2b6a0
  void* b2b2d0(int,int,int,int*);                // 0x00b2b2d0
  void  spawn(int,int,int,int,int,int,float);    // 0x00b2e010  SpawnMgr::Spawn
  void  FUN_00b2c2a0(int,int);                   // 0x00b2c2a0
  void  FUN_00b2c830(int,int);                   // 0x00b2c830
  void  FUN_00b2cd90();                          // 0x00b2cd90  refresh from avatar
  char* getBool();                               // 0x0041e920  Property::GetBool
  int*  getInt();                                // 0x0041e990  Property::GetInt
  void  b09340(void*, float, void*, int, int);   // 0x00b09340  vtbl[0x2c] + probe
  void* b79c30(void*, void*, int, float, int, int); // 0x00b79c30  collect effect targets
  void* GetGameDataVector(int,int,int,int,int);  // 0x00b21340
  void* b90410(void*);                           // 0x00b90410  species from position
  void* GetPlantProfile(void*);                  // 0x004df440
  void  b73de0(int);                             // 0x00b73de0
  void  b725e0(int);                             // 0x00b725e0
  void* b74e90(int, int, int);                   // 0x00b74e90
  void  ca30(int);                               // 0x00b2ca30  slot vector resize
  void  b5f950(void*);                           // 0x00b5f950  AutoRefCount::operator=
  void* FUN_00b1daf0(int, int);                  // 0x00b1daf0
};

// ---- cdecl / stdcall runtime helpers ---------------------------------------
extern "C" void* __cdecl FUN_00b3d3c0(void);                        // 0x00b3d3c0
extern "C" void* __stdcall NounManager0(void);                      // 0x00b3d300 (0 args)
extern "C" void* __stdcall NounManager1(void*);                     // 0x00b3d300 (1 arg)
extern "C" void* __stdcall FUN_00b3d440(void);                      // 0x00b3d440 (0 args)
extern "C" void* __stdcall FUN_00b79c30(void*, void*, int, float, int, int); // 0x00b79c30
extern "C" void  __cdecl operator_delete__(void*);                  // 0x00f47380
extern "C" void* __cdecl operator_new(int, void*, int, int, int, int); // 0x00f473a0
extern "C" void* __cdecl FUN_00b2af80(void*, void*, u32, u32);      // 0x00b2af80
extern "C" void* __cdecl RBTreeIncrement(void*);                    // 0x00921580
extern "C" void  __stdcall FUN_00f921d0(int,int);                   // 0x00f921d0
extern "C" void* __cdecl FUN_01021260(void);                        // 0x01021260
extern "C" void  __cdecl FUN_010210e0(void*);                       // 0x010210e0
extern "C" void* __cdecl GetActiveTerrainSphere(void);              // 0x00f48aa0
extern "C" void  __cdecl RemoveHandler(int,int,int,int,int);        // 0x00571db0
extern "C" void* __cdecl GetCurrentGameMode(void);                  // 0x00b5b800
extern "C" void* __cdecl GetCurrentGameModeAlt(void);               // 0x00b5b820
extern "C" void* __cdecl FUN_00b3d320(void);                        // 0x00b3d320 (0 args)
extern "C" void* __cdecl SpaceGameGet(void);                        // 0x01002bd0
extern "C" void* __cdecl cCivModeStrategy_Get(void);                // 0x00cf74c0
extern "C" void* __cdecl cTribeModeStrategy_Instance(void);         // 0x00cd40b0
extern "C" void* __cdecl FUN_0067ddc0(void);                        // 0x0067ddc0
extern "C" void* __cdecl EffectsManager(void);                      // 0x0067ddd0
extern "C" void* __cdecl ModelManager(void);                        // 0x0067dd80
extern "C" void* __stdcall FUN_0067de00(int);                         // 0x0067de00
extern "C" void* __cdecl GonzagoModelWorld(void);                   // 0x00b3d520
extern "C" void* __cdecl FUN_00b33f40(void);                        // 0x00b33f40 (0 args)
extern "C" void* __cdecl FUN_00b3d420(void);                        // 0x00b3d420 (0 args)
extern "C" void* __cdecl PlantProfileMgr(void);                     // 0x00401090 (0 args)
extern "C" void* __cdecl FUN_00b5b820(void);                        // 0x00b5b820

extern "C" int g_167e09c;   // 0x0167e09c
extern "C" int g_167e690;   // 0x0167e690  cSPTimer
extern "C" int g_1568d3c;   // 0x01568d3c
extern "C" int g_167ea54;   // 0x0167ea54
extern "C" int g_1568cf0;   // 0x01568cf0

struct Xdac0  { void FUN_00b2dac0(); };            // 0x00b2dac0
struct Xd09660{ bool FUN_00d09660(); };            // 0x00d09660
struct Xcf94b0{ bool FUN_00cf94b0(); };            // 0x00cf94b0
struct Xb1daf0{ void* FUN_00b1daf0(void*); };      // 0x00b1daf0

struct S {
  void  FUN_00b2e940(float dt);
  void  FUN_00b2ec10(int param_2, int param_3);
  void  FUN_00b2ec80(char param_2);
  void  FUN_00b2ed10();
  char  FUN_00b2ede0(void* msg, int* data);
  void  FUN_00b2f140();
  void  FUN_00b2f210();
  void  FUN_00b2f340();
  void  FUN_00b2f350(int mode);
  void  FUN_00b2f680(void* mode);
  void  FUN_00b2f710();
  void  FUN_00b2f7e0(int param_2);
  void  FUN_00b2d7c0(unsigned a, unsigned b, void* c);

  // ---- data members (explicit offsets; this class is never instantiated) ----
  u8    mPad00[0x20];            // +0x00
  u32   mFlags20;                // +0x20  bit0 active, bit1 reveal, bit2 hidden
  float mTimer24;                // +0x24  cursor refresh countdown
  u64   mKey28;                  // +0x28  packed cell under the cursor
  u32   mField30;                // +0x30
  u8    mField34;                // +0x34
  u8    mPad35[3];               // +0x35
  void* mpField38;               // +0x38
  void* mpField3c;               // +0x3c
  void* mpField40;               // +0x40
  u8    mPad44[0x140 - 0x44];
  u32   mHandler140;             // +0x140
  u32   mHandler144;             // +0x144
  u32   mHandler148;             // +0x148
  u32   mHandler14c;             // +0x14c
  u32   mHandler150;             // +0x150
  u8    mPad154[0x158 - 0x154];
  int   mMode158;                // +0x158  current game mode
  u8    mPad15c[0x17c - 0x15c];
  CursorEntry* mpEntries17c;     // +0x17c  cursor entry vector begin
  CursorEntry* mpEntries180;     // +0x180  cursor entry vector end
  u8    mPad184[0x190 - 0x184];
  CursorMap mMap190;             // +0x190  cell key -> slot list
};

// ---------------------------------------------------------------------------
// @ 0x00b2e940 — per-tick cursor refresh: when the reveal flag is set and the
// countdown expired, re-probe the cell under the cursor, remember its packed
// position and spawn the "cursor arrived" effects for the new cell.
// ---------------------------------------------------------------------------
void S::FUN_00b2e940(float dt) {
  if (((mFlags20 >> 2) & 1) == 0) return;

  void* avatar = ((E*)NounManager0())->GetAvatar();
  float remain = mTimer24 - dt;
  mTimer24 = remain;
  if (avatar == 0) return;
  if (remain > 0.0f) return;
  mTimer24 = 3.0f;

  FixedVec<void*, 32> cells;                       // probe results (max 32 cells)
  void* probe = ((TCP0)(VTO((char*)avatar + 0xc0))[0x2c / 4])((char*)avatar + 0xc0);
  ((E*)FUN_00b3d440())->b09340(probe, 50.0f, &cells, 1, 0);
  void* cell = cells.mpBegin != cells.mpEnd ? *cells.mpBegin : 0;

  u64 key = 0;
  if (cell != 0) {
    float* pos = (float*)cell;
    key = ((u64)(long long)pos[0] << 32) | ((u64)(long long)pos[1] << 16) |
          (u64)(long long)pos[2];
  }
  if (key != mKey28) {
    FUN_00b2d7c0((u32)mKey28, (u32)(mKey28 >> 32), 0);
    mKey28 = key;
    if (key != 0) {
      void* mgr = FUN_00b3d3c0();
      FixedVec<void*, 256> hits;                   // effect targets (max 256)
      ((E*)mgr)->b79c30(cell, &hits, 1, *(float*)((char*)cell + 0xc), 0, 0);
      if (hits.Size() != 0) {
        void* first = *hits.mpBegin;
        void* hit = ((E*)FUN_00b3d440())->b03320(0x3a8be428, *(int*)((char*)first + 0x50), 0);
        if (hit != 0) {
          void* ctx = ((E*)mgr)->func8Ch();
          u32 out[4];
          u64 key2 = ((u64)*(u32*)((char*)hit + 0x50) << 32) |
                     *(u32*)((char*)hit + 0x4c);
          ((E*)ctx)->b2b600((int*)out, (int*)&key2);
          int n = ((E*)out[1])->b2b6a0((int)out[0], (int)out[1], (int)out[2], (int)out[3]);
          if (n > 0) {
            char* o = *(char**)((char*)out[0] + 8);
            ((E*)this)->spawn(3, 1, (int)key, (int)(key >> 32), *(int*)(o + 0x58), n,
                              *(float*)(o + 0x44));
            ((E*)this)->spawn(1, 2, (int)key, (int)(key >> 32), *(int*)(o + 0x58), n,
                              *(float*)(o + 0x44));
          }
        }
      }
      hits.Release();
    }
  }
  if (cells.mpBegin != 0 && ((u32*)cells.mpBegin)[-1] != 0)
    operator_delete__(cells.mpBegin);
}

// ---------------------------------------------------------------------------
// @ 0x00b2ec10 — tick: timer glitch + advance cursor
// ---------------------------------------------------------------------------
void S::FUN_00b2ec10(int param_2, int param_3) {
  (void)param_2;
  if (0 < g_167e09c) {
    g_167e09c = g_167e09c - 1;
    if (g_167e09c == 0) {
      g_167e09c = 0;
      if (*(int*)((char*)this + 0x38) != 0) ((E*)*(void**)((char*)this + 0x38))->ff35e0(1);
      if (*(int*)((char*)this + 0x3c) != 0) ((E*)*(void**)((char*)this + 0x3c))->a110();
    }
  }
  char* q = (char*)this - 4;
  ((Xdac0*)q)->FUN_00b2dac0();
  double f = (double)param_3;
  if (param_3 < 0) f = f + 4294967296.0f;
  f = f * 0.001f;
  ((S*)q)->FUN_00b2e940((float)f);
}

// ---------------------------------------------------------------------------
// @ 0x00b2ec80 — enter/leave cursor editing
// ---------------------------------------------------------------------------
void S::FUN_00b2ec80(char param_2) {
  char* p = (char*)this;
  *(char*)(p + 0x34) = 1;
  ((E*)&g_167e690)->bc3170();            // 0x00bc3170
  ((E*)&g_167e690)->bc30f0();            // 0x00bc30f0  cSPTimer::Start
  *(int*)(p + 0x30) = 0;
  void* t = GetActiveTerrainSphere();
  if (t) ((TCV1)(VTO(t))[0x24/4])(t, *(int*)(p + 0x40));
  ((E*)p)->e830();
  void* planet = FUN_01021260();
  if (planet != 0 && param_2 == 0) FUN_010210e0(planet);
  ((E*)p)->bbe0();
  if (param_2 != 0) {
    void* q = GetActiveTerrainSphere();
    if (q) {
      ((TCV0)(VTO(q))[0xac/4])(q);
      ((TCV0)(VTO(q))[0xa8/4])(q);
    }
  }
}

// ---------------------------------------------------------------------------
// @ 0x00b2ed10 — teardown cursor maps
// ---------------------------------------------------------------------------
void S::FUN_00b2ed10() {
  char* p = (char*)this;
  FUN_00f921d0(0x80, 0);
  ((E*)p)->e830();
  for (void* n = *(void**)(p + 0x198); n != (void*)(p + 0x194); n = RBTreeIncrement(n)) {
    void* v = *(void**)((char*)n + 0x14);
    if (v) { ((E*)v)->bb90(); operator_delete__(v); }
  }
  void* n = *(void**)(p + 0x19c);
  while (n != 0) {
    ((E*)(p + 0x190))->nukeSubtree(*(void**)n);
    void* nxt = *(void**)((char*)n + 4);
    operator_delete__(n);
    n = nxt;
  }
  *(int*)(p + 0x194) = (int)(p + 0x194);
  *(int*)(p + 0x198) = (int)(p + 0x194);
  *(int*)(p + 0x19c) = 0;
  *(char*)(p + 0x1a0) = 0;
  *(int*)(p + 0x1a4) = 0;
  ((S*)p)->FUN_00b2d7c0(0xffffffffu, 0xffffffffu, (void*)1);
  *(char*)(p + 0x34) = 0;
  void* t = GetActiveTerrainSphere();
  if (t) ((TCV1)(VTO(t))[0x24/4])(t, 0);
}

// ---------------------------------------------------------------------------
// @ 0x00b2ede0 — cursor message handler: refresh, reveal timer, enter/leave.
// ---------------------------------------------------------------------------
char S::FUN_00b2ede0(void* msg, int* data) {
  switch ((unsigned)msg) {
    case 0xf62def:                       // cursor re-derived from the avatar
      if (data[4] != g_1568d3c && data[4] != 0x314f28a) return 0;
      ((E*)this)->FUN_00b2cd90();
      return 0;
    case 0x182c582:                      // end the reveal countdown
      g_167e09c = 3;
      return 0;
    case 0x1a0219e:                      // cursor entered a noun
      if (data[2] == 1) ((E*)this)->e830();
      return 1;
    case 0x32f76e7:
      return 1;
    case 0x31018b9:                      // cursor moved onto / off a cell
      break;
    default:
      return 0;
  }

  if (((mFlags20 >> 1) & 1) == 0) return 0;

  int* pos = (int*)data[2];
  u32 cellId = (u32)data[4];
  if (pos == 0) {
    void* it;
    mMap190.Find(&it, &cellId);
    if (it != mMap190.End())
      ((E*)(*(void**)((char*)it + 0x14)))->b090(1);
    return 1;
  }

  u32 count = (u32)(mpEntries180 - mpEntries17c);
  u32 i = 0;
  while (i < count) {
    if (mpEntries17c[i].mId04 == (u32)data[6] ||
        mpEntries17c[i].mId08 == (u32)data[6])
      break;
    count = (u32)(mpEntries180 - mpEntries17c);
    ++i;
  }
  if (i >= count) return 1;

  CursorEntry* entry = &mpEntries17c[i];
  if (((entry->mFlags20 >> 1) & 1) == 0) return 1;
  if (data[0] == 0) return 1;

  CursorHitInfo hit;
  hit.mCellId = entry->mId04;
  hit.mTypeId = 0x00b1b104;
  hit.mPropertyId = (u32)g_1568d3c;

  u64 key = ((u64)(long long)pos[1] << 32) | ((u64)(long long)pos[2] << 16) |
            (u64)(long long)pos[3];

  CursorSlotList* list;
  void* node;
  FUN_00b2af80(&node, &mMap190, (u32)key, (u32)(key >> 32));
  if (node != mMap190.End()) {
    list = (CursorSlotList*)(*(void**)((char*)node + 0x14));
    mMap190.EraseKey((char*)node + 0x10);
  } else {
    void* mem = operator_new(0x128, (void*)0x145fe50, 0, 0, 0, 0);
    list = mem != 0 ? (CursorSlotList*)((E*)mem)->c230() : 0;
    list->mCount08 = (u32)data[0];
    ((E*)((char*)list + 0x0c))->ca30(data[0]);
    list->mKey120 = key;
  }

  bool spawned = false;
  for (u32 s = 0; s < list->mCount08; ++s) {
    if (list->mpSlots0c[s] != 0) continue;
    void* slot = ((E*)this)->b2b2d0((int)cellId, (int)pos, (int)s, (int*)&hit);
    if (slot != 0) {
      ((E*)&list->mpSlots0c[s])->b5f950(slot);
      spawned = true;
    }
  }

  CursorMapInsert res;
  res.mKey = cellId;
  res.mpExtra = list;
  mMap190.Insert(&res, &res.mKey, 0);
  if (spawned) ((E*)NounManager0())->ProcessPending();
  return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00b2f140 — destroy cursor entries (thiscall, tail-calls e830)
// ---------------------------------------------------------------------------
void S::FUN_00b2f140() {
  void* pc = FUN_00b3d3c0();
  void* iVar5 = ((E*)pc)->func8Ch();
  int* piVar1 = *(int**)((char*)iVar5 + 4);
  int iVar6 = *piVar1;
  int* piVar7 = piVar1;
  if (iVar6 == 0) {
    piVar7 = piVar1 + 1;
    iVar6 = piVar1[1];
    while (iVar6 == 0) { piVar7++; iVar6 = *piVar7; }
    iVar6 = *piVar7;
  }
  int stop = piVar1[*(int*)((char*)iVar5 + 8)];
  while (iVar6 != stop) {
    int iVar2 = *(int*)(iVar6 + 8);
    void* puVar3 = *(void**)(iVar2 + 0x78);
    if (puVar3) {
      void* o1 = *(void**)puVar3;
      ((TCVV)(VTO(o1))[0x16c/4])(o1, puVar3, 0);
      puVar3 = *(void**)(iVar2 + 0x78);
      if (puVar3) {
        *(int*)(iVar2 + 0x78) = 0;
        void* o2 = *(void**)puVar3;
        if (*(int*)((char*)puVar3 + 0x40) < 2) {
          ((TCVV)(VTO(o2))[0x170/4])(o2, puVar3, ((unsigned)*(int*)((char*)puVar3 + 4)) >> 31);
        } else {
          *(int*)((char*)puVar3 + 0x40) -= 1;
        }
      }
    }
    iVar6 = *(int*)(iVar6 + 0x10);
    while (iVar6 == 0) { piVar7++; iVar6 = *piVar7; }
  }
  ((E*)this)->e830();
}

// ---------------------------------------------------------------------------
// @ 0x00b2f210 — Teardown / Deactivate
// ---------------------------------------------------------------------------
void S::FUN_00b2f210() {
  char* p = (char*)this;
  int iVar2 = *(int*)(p + 0x140);
  if (iVar2 != 0) {
    *(int*)(p + 0x140) = 0;
    RemoveHandler(iVar2, *(int*)(p + 0x144), *(int*)(p + 0x148), *(int*)(p + 0x14c), *(int*)(p + 0x150));
  }
  ((E*)p)->e830();
  for (void* n = *(void**)(p + 0x198); n != (void*)(p + 0x194); n = RBTreeIncrement(n)) {
    void* v = *(void**)((char*)n + 0x14);
    if (v) { ((E*)v)->bb90(); operator_delete__(v); }
  }
  void* n = *(void**)(p + 0x19c);
  while (n != 0) {
    ((E*)(p + 0x190))->nukeSubtree(*(void**)n);
    void* nxt = *(void**)((char*)n + 4);
    operator_delete__(n);
    n = nxt;
  }
  *(int*)(p + 0x194) = (int)(p + 0x194);
  *(int*)(p + 0x198) = (int)(p + 0x194);
  *(int*)(p + 0x19c) = 0;
  *(char*)(p + 0x1a0) = 0;
  *(int*)(p + 0x1a4) = 0;
  ((E*)(p + 0x17c))->FUN_00b2c2a0(*(int*)(p + 0x17c), *(int*)(p + 0x180));
  ((S*)p)->FUN_00b2d7c0(0xffffffffu, 0xffffffffu, (void*)1);
  void* q = *(void**)(p + 0x40);
  if (q) { *(int*)(p + 0x40) = 0; ((TCV0)(VTO(q))[4/4])(q); }
  void* planet = FUN_01021260();
  if (planet) ((S*)p)->FUN_00b2ed10();
  void* fx = EffectsManager();
  ((void(__thiscall*)(void*, int, int, int))(VTO(fx))[0x88/4])(fx, 0x107ae878, 0, 0);
  void* r = *(void**)(p + 0x3c);
  if (r) { *(int*)(p + 0x3c) = 0; ((TCV0)(VTO(r))[4/4])(r); }
  *(int*)(p + 0x38) = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00b2f340 — thunk: FUN_00b2f210 on (this-4)
// ---------------------------------------------------------------------------
void S::FUN_00b2f340() {
  ((S*)((char*)this - 4))->FUN_00b2f210();
}

// ---------------------------------------------------------------------------
// @ 0x00b2f350 — apply the settings of `mode` to the cursor object.
// ---------------------------------------------------------------------------
void S::FUN_00b2f350(int mode) {
  bool active = false;          // cursor active   (property 0x25f0761)
  bool reveal = false;          // cell reveal     (property 0x32a54b9)
  bool hidden = false;          // cursor hidden   (property 0x3dad600)

  if (mode == 0x1654c06) mode = (int)GetCurrentGameModeAlt();
  void* obj = ((E*)FUN_00b3d320())->FUN_00b1daf0(mode, 1);
  int* prop = 0;
  if (obj != 0) {
    ((TCV0)(VTO(obj))[0 / 4])(obj);
    if ((char)((TCR2)(VTO(obj))[0x24 / 4])(obj, 0x25f0761u, &prop) &&
        *(short*)((char*)prop + 0x12) == 1)
      active = *((E*)prop)->getBool() != 0;
    if ((char)((TCR2)(VTO(obj))[0x24 / 4])(obj, 0x32a54b9u, &prop) &&
        *(short*)((char*)prop + 0x12) == 1)
      reveal = *((E*)prop)->getBool() != 0;
    if ((char)((TCR2)(VTO(obj))[0x24 / 4])(obj, 0x3dad600u, &prop) &&
        *(short*)((char*)prop + 0x12) == 1)
      hidden = *((E*)prop)->getBool() != 0;
    if ((char)((TCR2)(VTO(obj))[0x24 / 4])(obj, 0x6e212ea9u, &prop) &&
        *(short*)((char*)prop + 0x12) == 9)
      g_1568cf0 = *((E*)prop)->getInt();
  }

  bool wasActive = (mFlags20 & 1) != 0;
  if (active) mFlags20 |= 1u; else mFlags20 &= ~1u;
  if (wasActive && !active) FUN_00b2f140();

  if ((mFlags20 & 1) != 0) {
    void* planet = FUN_01021260();
    char* terrain = *(char**)((char*)planet + 0x13c);
    int count = (*(int*)(terrain + 0xc0) - *(int*)(terrain + 0xbc)) / 0xc;
    int off = 0;
    for (int n = count; n > 0; --n) {
      void* sphere = FUN_00b33f40();
      void* species = ((E*)FUN_00b3d420())->b90410(terrain + 0xbc + off);
      if (species != 0) {
        void* key = ((TCP0)(VTO(species))[0x18 / 4])(species);
        void* profile = ((E*)PlantProfileMgr())->GetPlantProfile(key);
        if (profile != 0 && *(int*)((char*)profile + 0x504) != 0) {
          int pos3[3];
          pos3[0] = *(int*)((char*)profile + 0x504);
          pos3[1] = *(int*)((char*)profile + 0x508);
          pos3[2] = *(int*)((char*)profile + 0x50c);
          void* h = ((TCP5)(VTO(sphere))[0x30 / 4])(sphere, pos3, 2,
                                                   (void*)0x167e0a0,
                                                   (void*)0x1568d04, 1);
          ((TCV1)(VTO(sphere))[0x3c / 4])(sphere, (int)h);
        }
      }
      off += 0xc;
    }
  }

  if (mode != 0xdbdba1 && reveal != (((mFlags20 >> 1) & 1) != 0) && !reveal) {
    void* vec = ((E*)NounManager0())->GetGameDataVector(0xcd7d10, 0xd3d420, 0xb2d1d0,
                                                       0xb1e500, 0x2a8fb3f);
    char* begin = *(char**)((char*)vec + 4);
    int count = (int)(*(char**)((char*)vec + 8) - begin) / 4;
    for (int n = 0; n < count; ++n) {
      char* elem = ((char**)begin)[n];
      if (elem == 0) continue;
      if (*(int*)(elem + 0x13c) == 0) continue;
      void* r = ((E*)FUN_00b3d3c0())->b74e90(*(int*)(elem + 0x13c), 0,
                                             *(int*)(elem + 0x140));
      if (r != 0) {
        ((E*)r)->b73de0(0);
        if (*(int*)((char*)r + 0x64) == 0) ((E*)r)->b725e0(1);
      }
      ((E*)NounManager0())->removeNoun(elem);
    }
  }

  if (reveal) mFlags20 |= 2u; else mFlags20 &= ~2u;
  if (hidden != (((mFlags20 >> 2) & 1) != 0)) {
    if (!hidden) FUN_00b2d7c0(0xffffffffu, 0xffffffffu, (void*)1);
    if (hidden) mFlags20 |= 4u; else mFlags20 &= ~4u;
  }

  if (obj != 0) ((TCV0)(VTO(obj))[4 / 4])(obj);
}

// ---------------------------------------------------------------------------
// @ 0x00b2f680 — set current game mode (jump table)
// ---------------------------------------------------------------------------
void S::FUN_00b2f680(void* mode) {
  char* p = (char*)this;
  if (*(void**)(p + 0x158) == mode) return;
  switch ((unsigned)mode) {
    case 0x1654c01: case 0x1654c02: case 0x1654c04: case 0x1654c10:
      ((S*)p)->FUN_00b2ec80(*(void**)(p + 0x158) == (void*)0x1654c08);
      ((S*)p)->FUN_00b2f350((int)mode);
      *(void**)(p + 0x158) = mode;
      break;
    case 0x1654c05:
      ((S*)p)->FUN_00b2f350((int)mode);
      break;
  }
  *(void**)(p + 0x158) = mode;
}

// ---------------------------------------------------------------------------
// @ 0x00b2f710 — set current game-mode with teardown
// ---------------------------------------------------------------------------
void S::FUN_00b2f710() {
  char* p = (char*)this;
  if (*(int*)(p + 0x158) != -1) {
    ((S*)p)->FUN_00b2ed10();
    ((S*)p)->FUN_00b2f140();
    ((S*)p)->FUN_00b2f350(-1);
    *(int*)(p + 0x158) = -1;
  }
}

// ---------------------------------------------------------------------------
// @ 0x00b2f740 — query current game mode
// ---------------------------------------------------------------------------
extern "C" bool FUN_00b2f740() {
  char* mode = (char*)GetCurrentGameMode();
  switch ((unsigned)mode) {
    case 0x1654c02: {
      void* p = cTribeModeStrategy_Instance();
      void* q = ((void*(__thiscall*)(void*))(VTO(p))[0x70/4])(p);
      return ((Xd09660*)(*(void**)((char*)q + 0x5c)))->FUN_00d09660();
    }
    case 0x1654c04: {
      void* civ = cCivModeStrategy_Get();
      return ((Xcf94b0*)civ)->FUN_00cf94b0();
    }
    case 0x1654c05: {
      if (SpaceGameGet() != 0) {
        void* sg = SpaceGameGet();
        if (*(int*)((char*)sg + 0x20) != 0) {
          void* sg2 = SpaceGameGet();
          if (((Xd09660*)(*(void**)((char*)sg2 + 0x20)))->FUN_00d09660()) return true;
        }
      }
      return false;
    }
    default:
      return false;
  }
}

// ---------------------------------------------------------------------------
// @ 0x00b2f7b0 — refresh renderer from property manager
// ---------------------------------------------------------------------------
extern "C" void FUN_00b2f7b0() {
  void* p = FUN_0067ddc0();
  if (p != 0) {
    ((TCV1)(VTO(p))[0x28/4])(p, 0);
    ((TCV0)(VTO(p))[0x24/4])(p);
  }
}

// ---------------------------------------------------------------------------
// @ 0x00b2f7e0 — initialise renderer from mode + model
// ---------------------------------------------------------------------------
void S::FUN_00b2f7e0(int param_2) {
  char* p = (char*)this;
  void* piVar1 = FUN_0067ddc0();
  if (piVar1 != 0) {
    *(int*)p = param_2;
    ((TCV1)(VTO(piVar1))[0x10/4])(piVar1, g_167ea54);
    void* world = GonzagoModelWorld();
    ((TCV2)(VTO(piVar1))[0x18/4])(piVar1, (int)world, 3);
    void* mm = ModelManager();
    int iVar4 = ((TCI1)(VTO(mm))[0x1c/4])(mm, 0x3fbae24);
    if (iVar4 != 0) ((TCV2)(VTO(piVar1))[0x18/4])(piVar1, iVar4, 0);
    void** vt = VTO(piVar1);
    void* x = FUN_0067de00(0x20007);
    ((TCV1)vt[0x1c/4])(piVar1, (int)x);
    ((TCV1)(VTO(piVar1))[0x48/4])(piVar1, *(int*)p);
    ((TCV1)(VTO(piVar1))[0x28/4])(piVar1, 1);
  }
}
