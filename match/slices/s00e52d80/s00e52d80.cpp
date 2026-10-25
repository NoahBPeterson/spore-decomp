// Slice s00e52d80 (batch bfs3, slice 17). Region 0xe52d80-0xe53c66.
// Cell-game mission UI / collectable panel glue. Optimised:
// /O2 /MD /Gy /TP /arch:SSE /fp:fast.  Recurring scope guard = 0x743b50/0xe82130.
#include "types.h"

struct cSlotOwner17 { int pad[0x24]; int state; bool F_00e531c0(); int F_00e53210(); };
struct cGuard17 { void* p; cGuard17(); ~cGuard17(); };

extern "C" {
  float    __cdecl FUN_00e52b70();
  char     __cdecl FUN_00e52c70();
  char     __cdecl FUN_00e52cd0();
  void*    __cdecl FUN_00e4ce40(void* out);   // 0x00e4ce40 layer catalog lookup
  int      __cdecl FUN_00e4fca0();
  int      __cdecl FUN_00e4fd30(char*);
  int      __cdecl FUN_00e530e0();
  void     __cdecl FUN_00e53340();
  void     __cdecl FUN_00e53660(int, int);
  void     __cdecl FUN_00e53b40();
  void     __cdecl FUN_00e569b0();
  void     __cdecl FUN_00e82d10(int);
  int      __cdecl FUN_00e84490(int, int);
  void     __cdecl FUN_00e848c0(int);
  int      __fastcall FUN_00e4ee60(int unusedEcx, int levelInEdx);   // 0x00e4ee60: level in EDX
  void     __cdecl FUN_00e7ce10(int, int);
  void*    __cdecl FUN_00b721d0(int);
  void*    __cdecl FUN_00b3d400(void*);
  void*    __cdecl FUN_00b3d3f0(int);
  void*    __cdecl FUN_00b3d3f0_get();   // 0x00b3d3f0 (really takes no arguments)
  void     __cdecl FUN_00e190c0(void*);
  void     __cdecl FUN_00e19010(void*);
  void*    __cdecl FUN_00b3d4d0(int);
  void*    __cdecl FUN_00ad7dc0(void*);
  void*    __cdecl SP_ConfigManager();
  void*    __cdecl SP_MessageServer();
  int      __cdecl SP_GetCurrentGameMode();
  void     __cdecl FUN_006035d0(int);
  bool     __cdecl FUN_00e00ac0();
  void*    __cdecl EA_Messaging_GetServer();   // 0x883860
  void     __cdecl FUN_00e82690(int, float);
  void     __cdecl SP_PatchSoundStart(const char*, int);
  void     __cdecl FUN_00e3c6f0(int, int);
  void     __cdecl SetTooltipText(void* w, const wchar_t* text);   // 0x00806de0
}

extern char g_16b3c04[];
extern char g_16b3c0c[];
extern char g_16b3c08[];
extern int  g_16b3c28, g_16b3c2c, g_16b3c30;
extern int  g_15a7c4c, g_15a7c50, g_15a7c54, g_15a7c58;

static inline void** Vt(void* p) { return *(void***)p; }

struct cSPUILayout17 {
  void* FindWindowByID(int id, int flag);   // 0x8105b0
  void  SetVisibility(int v);               // 0x810590
};
struct cAlloc17 { cSPUILayout17* GetAllocator(); };   // 0x7f54d0
struct cMgr94 { void f(); };                          // 0xe28a00 (float ignored)
struct cCellSub54 { void* Get(); void* Add(void*); }; // 0xb72160 / 0xb72210

// ---- cell-game singletons: 0x16b3c04 / 0x16b3c0c / 0x16b3c08 hold POINTERS ----
struct cCellSub17 { void* Fn_b721d0(int key); };      // 0x00b721d0
struct SlotRec17 { int mType; int mValue; int mPad0; float mField_c; };   // 16-byte slot record
struct cSlotData17 {                       // pointed to by cCellGame17::mpSlotData_5190
  char      pad_00[0x1c];
  int       mField_1c;
  char      pad_20[0x34 - 0x20];
  union {
    int           mCounts_34[14];          // +0x34 .. +0x6c
    struct { char pad_34[0x69 - 0x34]; unsigned char mField_69; char pad_6a[0x6c - 0x6a]; };
  };
  int       mField_6c;
  int       mField_70;
  int       mField_74;
  int       mField_78;
  int       mField_7c;
  SlotRec17 mRecords_80[8];                // +0x80
};
struct cCellGame17 {
  char       pad_00[0x1c];
  cCellSub17 mSub_1c;
  char       pad_20[0x411c - 0x20];
  int        mField_411c;
  char       pad_4120[0x5158 - 0x4120];
  int        mField_5158;
  int        mField_515c;
  char       pad_5160[0x5190 - 0x5160];
  cSlotData17* mpSlotData_5190;
  char       pad_5194[0x51b0 - 0x5194];
  int        mField_51b0;
  int        mField_51b4;
  char       pad_51b8[0x51bc - 0x51b8];
  float      mField_51bc;
  unsigned char mField_51c0;
  char       pad_51c1[0x51cc - 0x51c1];
  float      mTime_51cc;
  float      mTime_51d0;
  char       pad_51d4[0x51dc - 0x51d4];
  unsigned char mField_51dc;
};
struct cCellGfx17 {                        // gspCellGfx
  char           pad_00[0x90];
  cSPUILayout17* mpLayout_90;
  void*          mpMgr_94;
  cAlloc17*      mpAlloc_98;
  char           pad_9c[0x938 - 0x9c];
  unsigned char  mField_938;
  float          mField_93c;
  float          mField_940;
};
struct cGfxObj17 {                         // gspCellGfx's render objects
  char  pad_00[0x161b4];
  void* mpP_161b4;
  char  pad_161b8[0x161bc - 0x161b8];
  void* mpQ_161bc;
  char  pad_161c0[0x161c4 - 0x161c0];
  void* mpA_161c4;
  void* mpR_161c8;
  char  pad_161cc[0x161d0 - 0x161cc];
  void* mpB_161d0;
};
struct cPanel17 { void Fn_190c0(int a); }; // 0x00e190c0

// SP::cString (localised text handle)
struct cString17 {
  cString17();                                                              // 0x006b5060
  ~cString17();                                                             // 0x006b5240
  int Load(unsigned tableID, unsigned instanceID, const wchar_t* pDefault);  // 0x006b54b0
  const wchar_t* GetText(int, int);                                         // 0x006b55c0
  unsigned mData[6];
};
// SP::cDirectPropertyList::SetBoolProperty
struct cDirectPropertyList17 { void SetBoolProperty(unsigned id, bool v); };  // 0x006a17e0
extern cDirectPropertyList17* g_15fd918;

static inline cCellGame17* CellGame17() { return *(cCellGame17**)g_16b3c04; }
static inline cCellGfx17*  CellGfx17()  { return *(cCellGfx17**)g_16b3c0c; }
static inline cGfxObj17*   GfxObj17()   { return *(cGfxObj17**)g_16b3c08; }

static void* FindWin(int id) {
  char* st = g_16b3c0c;
  cSPUILayout17* layout = *(cSPUILayout17**)(st + 0x90);
  return layout->FindWindowByID(id, 1);
}
static void* SubWindow(void* w) {
  if (!w) return 0;
  return (*(void*(__thiscall**)(void*, int))((char*)Vt(w) + 0xc))(w, 0x8ed27e7a);
}
static void Vis(void* w, int v) {
  (*(void(__thiscall**)(void*, int, int))((char*)Vt(w) + 0x28))(w, 4, v);
}
// mission-HUD variant: vtable +0x7c with a fixed leading 1
static void Vis7c(void* w, int v) {
  (*(void(__thiscall**)(void*, int, int))((char*)Vt(w) + 0x7c))(w, 1, v);
}
// set the visible flag (1) of a gfx render object (vtable +0xc)
static void GfxVis(void* o, int v) {
  (*(void(__thiscall**)(void*, int))((char*)Vt(o) + 0xc))(o, v);
}

// @ 0x00e530e0
int FUN_00e530e0() {
  char local[16];
  int n = FUN_00e4fd30(local);
  int count = 0;
  if (n > 0) {
    cSlotData17* d = CellGame17()->mpSlotData_5190;
    for (int i = 0; i < n; ++i) {
      if (local[i] != 0) {
        int v = d->mCounts_34[i];
        if (v != 1 && v != 2) ++count;
      }
    }
  }
  return count;
}

// @ 0x00e53130
void FUN_00e53130() {
  FUN_00e82d10(0xde776d90);
  cSlotData17* d = CellGame17()->mpSlotData_5190;
  int r = FUN_00e84490(0xd0d8ca6, 0x5bef305);
  if (d->mField_74 < r) FUN_00e82d10(0xd0d8ca6);
  if (CellGame17()->mpSlotData_5190->mField_6c == 0) FUN_00e82d10(0x662732af);
  if (CellGame17()->mpSlotData_5190->mField_7c == 2) FUN_00e82d10(0x20b852b8);
  FUN_00e848c0(CellGame17()->mpSlotData_5190->mField_78);
}

// @ 0x00e531c0
bool cSlotOwner17::F_00e531c0() { int* self = (int*)this;
  if (self[0x24] == 4 || self[0x24] == 5) self[0x24] = 0;
  int v = CellGame17()->mpSlotData_5190->mRecords_80[self[0x24]].mType;
  if (v != 2 && v != 3) return false;
  return true;
}

// @ 0x00e53210
int cSlotOwner17::F_00e53210() { int* self = (int*)this;
  int v = self[0x24];
  if (v != 1) {
    if (v > 3 && v < 6) v = 0;
    return CellGame17()->mpSlotData_5190->mRecords_80[v].mValue;
  }
  return 6 - FUN_00e530e0();
}

// @ 0x00e53250
void FUN_00e53250(int idx) {
  char* o = (char*)(*(int*)(g_16b3c04 + 0x5190)) + (idx + 8) * 0x10;
  *(int*)o = 1;
  *(int*)(o + 4) = 0;
  *(int*)(o + 8) = 0;
  *(float*)(o + 0xc) = 0.0f;
}

// @ 0x00e53280
bool FUN_00e53280() {
  cCellGame17* esi = CellGame17();
  int edi = esi->mpSlotData_5190->mField_7c;
  if (edi == 0) return false;
  if (esi->mField_51dc != 0) return false;
  int lvl = FUN_00e4ee60(0, esi->mpSlotData_5190->mField_1c);
  if (lvl < 3) return false;
  if (esi->mField_51c0 != 0 && edi == 1) return false;
  if (!(esi->mField_51bc <= 0.0f)) return false;
  return true;
}

// @ 0x00e532e0
bool FUN_00e532e0(char* flag, float dt) {
  cCellGame17* game = CellGame17();
  void* o = game->mSub_1c.Fn_b721d0(game->mField_411c);
  if (o) {
    *(char*)((char*)o + 0x17c) = 1;
    *(char*)((char*)o + 0x17b) = 1;
  }
  if (*flag == 0 && dt > 1.0f) {
    FUN_00e7ce10(0x32, 1);
    *flag = 1;
  }
  return true;
}

// @ 0x00e53340
void FUN_00e53340() {
  cCellSub54* cs = (cCellSub54*)(g_16b3c04 + 0x54);
  void* h = cs->Get();
  char* o = (char*)cs->Add(h);
  *(float*)(o + 0x1c) = 5.0f;
  *(float*)(o + 0x20) = 5.0f;
  *(int*)(o + 0x24) = 0x2b;
  *(float*)(o + 0x40) = 0.0f;
  *(float*)(o + 0x44) = 0.0f;
  *(int*)(o + 0x28) = 0;
  *(int*)(o + 0x2c) = 0;
  *(int*)(o + 0x38) = 0;
  *(int*)(o + 0x3c) = 0;
  *(int*)(o + 0x30) = -1;
  *(int*)(o + 0x34) = -1;
  *(int*)(o + 0x48) = g_16b3c28;
  *(int*)(o + 0x4c) = g_16b3c2c;
  *(int*)(o + 0x50) = g_16b3c30;
  *(int*)(o + 0x54) = g_16b3c28;
  *(int*)(o + 0x58) = g_16b3c2c;
  *(int*)(o + 0x5c) = g_16b3c30;
  *(int*)(o + 0x60) = g_15a7c4c;
  *(int*)(o + 0x64) = g_15a7c50;
  *(int*)(o + 0x68) = g_15a7c54;
  *(int*)(o + 0x6c) = g_15a7c58;
  *(int*)(o + 0x70) = 0;
  *(char*)(o + 0x74) = 0;
  *(int*)(o + 0x78) = 0;
  *(int*)(o + 4) = 0;
  *(char*)(o + 8) = 0;
  void* w = FindWin(0x5af4ae3);
  if (w) Vis(w, 1);
  void* x = FUN_00b721d0(*(int*)(g_16b3c04 + 0x411c));
  if (x) { *(char*)((char*)x + 0x17c) = 1; *(char*)((char*)x + 0x17b) = 1; }
}

// @ 0x00e53580
void FUN_00e53580() {
  void* w = FindWin(0xd305ca84);
  w = SubWindow(w);
  (*(void(__thiscall**)(void*, int, int))((char*)Vt(w) + 0x28))(w, 4, 0);
  (*(void(__thiscall**)(void*, int))((char*)Vt(*(void**)(g_16b3c08 + 0x161bc)) + 0xc))(*(void**)(g_16b3c08 + 0x161bc), 0);
  (*(void(__thiscall**)(void*, int))((char*)Vt(*(void**)(g_16b3c08 + 0x161b4)) + 0xc))(*(void**)(g_16b3c08 + 0x161b4), 0);
  (*(void(__thiscall**)(void*, int))((char*)Vt(*(void**)(g_16b3c08 + 0x161c8)) + 0xc))(*(void**)(g_16b3c08 + 0x161c8), 0);
  void* srv = EA_Messaging_GetServer();
  if (*(unsigned char*)(g_16b3c04 + 0x515c) & 2)
    (*(void(__thiscall**)(void*, int, int, int))((char*)Vt(srv) + 0x14))(srv, 0x3867294, 0, 0);
  if (*(unsigned char*)(g_16b3c04 + 0x515c) & 1)
    (*(void(__thiscall**)(void*, int, int, int))((char*)Vt(srv) + 0x14))(srv, 0x546bbb8, 0, 0);
  *(int*)(g_16b3c04 + 0x515c) = 0;
}

// @ 0x00e53860
void FUN_00e53860(char flag) {
  if (flag) {
    cSPUILayout17* layout = CellGfx17()->mpLayout_90;
    void* w = layout->FindWindowByID(0x6244208, 1);
    w = SubWindow(w);
    Vis(w, 1);
  }
  void* o = FUN_00b3d3f0_get();
  ((cPanel17*)o)->Fn_190c0(0);
}

// @ 0x00e538b0
void FUN_00e538b0(char flag) {
  void* ms = SP_MessageServer();
  if (flag) {
    (*(void(__thiscall**)(void*, int, int, int))((char*)Vt(ms) + 0x14))(ms, 0x5120264, 0, 0);
    void* w = SubWindow(FindWin(0x447060c));
    Vis(w, 1);
    FUN_00e53660(2, 1);
  } else {
    (*(void(__thiscall**)(void*, int, int, int))((char*)Vt(ms) + 0x14))(ms, 0x574f0a6, 0, 0);
  }
}

// @ 0x00e53920
void FUN_00e53920() {
  if (g_16b3c04[0x515c] & 1) FUN_00e53660(1, 0);
  else FUN_00e53660(1, 1);
}

// @ 0x00e53950
void FUN_00e53950(char flag) {
  if (flag) {
    ((cMgr94*)(*(int*)(g_16b3c0c + 0x94)))->f();
    FUN_00e3c6f0(*(int*)(g_16b3c04 + 0x5158) == 5, 0);
    (*(cSPUILayout17**)(g_16b3c0c + 0x90))->SetVisibility(0);
    void* o = FUN_00b3d3f0(0);
    FUN_00e19010(o);
    FUN_00e53660(2, 1);
  }
}

// @ 0x00e539c0
void FUN_00e539c0() {
  ((cMgr94*)(*(int*)(g_16b3c0c + 0x94)))->f();
  FUN_00e3c6f0(*(int*)(g_16b3c04 + 0x5158) == 5, 0);
  (*(cSPUILayout17**)(g_16b3c0c + 0x90))->SetVisibility(0);
  void* o = FUN_00b3d3f0(0);
  FUN_00e19010(o);
  FUN_00e53660(2, 1);
}

// @ 0x00e53a20
void FUN_00e53a20() {
  int mode = SP_GetCurrentGameMode();
  FUN_006035d0(mode);
  cSPUILayout17* layout = ((cAlloc17*)(*(int*)(g_16b3c0c + 0x98)))->GetAllocator();
  void* w = layout->FindWindowByID(0x43b72d0, 1);
  w = SubWindow(w);
  Vis(w, 1);
}

// @ 0x00e53a80
void FUN_00e53a80() {
  cSPUILayout17* layout = CellGfx17()->mpAlloc_98->GetAllocator();
  void* w = layout->FindWindowByID(0x43b72d0, 1);
  w = SubWindow(w);
  Vis(w, 0);
}

// @ 0x00e53ad0
void FUN_00e53ad0() {
  if (FUN_00e00ac0()) FUN_00e53660(2, 1);
  else FUN_00e53660(2, 0);
}

// @ 0x00e53b00
void FUN_00e53b00(float v) {
  void* a = GfxObj17()->mpA_161c4;
  (*(void(__thiscall**)(void*, float, int))((char*)Vt(a) + 0x24))(a, v, 0);
  void* b = GfxObj17()->mpB_161d0;
  (*(void(__thiscall**)(void*, float, int))((char*)Vt(b) + 0x24))(b, v, 0);
}

// @ 0x00e53b40
void FUN_00e53b40() {
  cCellSub54* cs = (cCellSub54*)(g_16b3c04 + 0x54);
  void* h = cs->Get();
  char* o = (char*)cs->Add(h);
  *(float*)(o + 0x1c) = 0.5f;
  *(float*)(o + 0x20) = 0.5f;
  *(int*)(o + 0x24) = 0x30;
  *(int*)(o + 0x28) = 0;
  *(int*)(o + 0x2c) = 0;
  *(int*)(o + 0x30) = -1;
  *(int*)(o + 0x34) = -1;
  *(int*)(o + 0x38) = 0;
  *(int*)(o + 0x3c) = 0;
  *(float*)(o + 0x40) = 0.0f;
  *(float*)(o + 0x44) = 0.0f;
  *(int*)(o + 0x48) = g_16b3c28;
  *(int*)(o + 0x4c) = g_16b3c2c;
  *(int*)(o + 0x50) = g_16b3c30;
  *(int*)(o + 0x54) = g_16b3c28;
  *(int*)(o + 0x58) = g_16b3c2c;
  *(int*)(o + 0x5c) = g_16b3c30;
  *(int*)(o + 0x60) = g_15a7c4c;
  *(int*)(o + 0x64) = g_15a7c50;
  *(int*)(o + 0x68) = g_15a7c54;
  *(int*)(o + 0x6c) = g_15a7c58;
  *(int*)(o + 0x70) = 0;
  *(char*)(o + 0x74) = 0;
  *(int*)(o + 0x78) = 0;
  *(int*)(o + 4) = 0;
  *(char*)(o + 8) = 0;
  *(char*)(g_16b3c04 + 0x51dc) = 1;
  FUN_00e569b0();
}

// @ 0x00e53c20
void FUN_00e53c20() {
  void* o = FUN_00b3d4d0(0);
  FUN_00ad7dc0(o);
  g_16b3c0c[0xe4] = 0;
  g_16b3c04[0x51dc] = 0;
  void* cm = SP_ConfigManager();
  int r = (*(int(__thiscall**)(void*, int))((char*)Vt(cm) + 0x30))(cm, 0x4ea96cb);
  if (r > 0) FUN_00e53b40();
}

// @ 0x00e52d80
void FUN_00e52d80(float dt) {
  if (CellGame17()->mTime_51d0 > 0.0f) CellGame17()->mTime_51d0 -= dt;
  if (CellGame17()->mTime_51cc > 0.0f) CellGame17()->mTime_51cc -= dt;
  char byteA = (CellGame17()->mTime_51cc <= 0.0f) && (CellGame17()->mpSlotData_5190->mField_69 != 0);
  bool eq1000 = (CellGame17()->mpSlotData_5190->mField_1c == 1000);

  Vis7c(FindWin(0x44837c0), byteA);
  Vis7c(FindWin(0x6455c5e), eq1000);
  Vis7c(FindWin(0x652a628), eq1000);
  Vis7c(FindWin(0x44827b8), !eq1000);
  Vis7c(FindWin(0x4001120), byteA);

  int layer;
  { cGuard17 g; layer = *(int*)((char*)FUN_00e4ce40(&g) + 0xdc); }
  if (layer != 0) {
    { cGuard17 g2; layer = *(int*)((char*)FUN_00e4ce40(&g2) + 0xdc); }
    if (layer != 2) return;
  }

  char uA = FUN_00e52c70();
  char cB = FUN_00e52cd0();
  Vis7c(FindWin(0x5af4ae0), uA);

  int visA = 0;
  if (cB) {
    cCellGfx17* gp = CellGfx17();
    gp->mField_940 += dt;
    while (gp->mField_940 > 30.0f) gp->mField_940 -= 30.0f;
    visA = (gp->mField_940 < 10.0f);
  }
  Vis7c(FindWin(0x5af4ae1), visA);

  void* cm = SP_ConfigManager();
  int cfg = (*(int(__thiscall**)(void*, int))((char*)Vt(cm) + 0x30))(cm, 0x4ea96cb);
  bool bVar1 = false;
  if (cfg > 0) {
    if (CellGame17()->mpSlotData_5190->mField_1c == 1000 && CellGame17()->mField_51dc == 0) {
      bVar1 = true;
      if (CellGfx17()->mField_938 == 0) CellGfx17()->mField_93c += dt;
    }
  }
  cCellGfx17* gq = CellGfx17();
  while (gq->mField_93c > 30.0f) gq->mField_93c -= 30.0f;
  bool visB = (gq->mField_93c < 10.0f);
  int vis2 = (bVar1 && CellGfx17()->mField_938 == 0 && visB) ? 1 : 0;
  Vis7c(FindWin(0x5af4ae2), vis2);
}

// @ 0x00e53460
void FUN_00e53460(int idx) {
  if (idx == 3) {
    CellGame17()->mField_51bc = FUN_00e52b70();
  } else {
    FUN_00e82690(0xc1fa4704, 1.0f);
    SP_PatchSoundStart("ui_mission_complete", 0);
  }
  CellGame17()->mpSlotData_5190->mRecords_80[idx].mType = 3;
  CellGame17()->mpSlotData_5190->mRecords_80[idx].mField_c = 5.0f;
  if (idx == 0) {
    int v;
    { cGuard17 g; v = *(int*)((char*)FUN_00e4ce40(&g) + 0xdc); }
    if (v == 0) { FUN_00e53340(); return; }
    { cGuard17 g2; v = *(int*)((char*)FUN_00e4ce40(&g2) + 0xdc); }
    if (v == 1 || FUN_00e4fca0() == 2) FUN_00e7ce10(0x32, 1);
  } else if (idx == 3) {
    CellGame17()->mField_51b4 = -1;
    CellGame17()->mField_51b0 = 0;
  }
}

// @ 0x00e53660
void FUN_00e53660(int param_1, int param_2) {
  int state = CellGame17()->mField_515c;
  int comb = param_2 ? (state | param_1) : (state & ~param_1);

  cString17 s;
  void* w = FindWin(0xd305ca84);
  unsigned loadId;
  if (comb & 1) {
    Vis(SubWindow(w), 1);
    loadId = 0x655200d;
  } else {
    Vis(SubWindow(w), 0);
    loadId = 0xf81c278b;
  }
  s.Load(0xc0152a6d, loadId, 0);
  w = FindWin(0xd305ca84);
  SetTooltipText(w, s.GetText(-1, 1));

  bool visArg;
  if (comb) {
    GfxVis(GfxObj17()->mpQ_161bc, 1);
    GfxVis(GfxObj17()->mpP_161b4, 1);
    GfxVis(GfxObj17()->mpR_161c8, 1);
    visArg = (comb == 1);
  } else {
    GfxVis(GfxObj17()->mpQ_161bc, 0);
    GfxVis(GfxObj17()->mpP_161b4, 0);
    GfxVis(GfxObj17()->mpR_161c8, 0);
    visArg = false;
  }
  g_15fd918->SetBoolProperty(0x387d0a8, visArg);

  void* ms = EA_Messaging_GetServer();
  if (param_1 == 2) {
    (*(void(__thiscall**)(void*, int, int, int))((char*)Vt(ms) + 0x14))(ms, 0x3867294, param_2 ? 1 : 0, 0);
  } else if (param_1 == 1) {
    (*(void(__thiscall**)(void*, int, int, int))((char*)Vt(ms) + 0x14))(ms, 0x546bbb8, param_2 ? 1 : 0, 0);
    (*(void(__thiscall**)(void*, int, int, int))((char*)Vt(ms) + 0x14))(ms, 0x3867294, param_2 ? 1 : 0, 0);
  }
  CellGame17()->mField_515c = comb;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct cCellSub54 {
    void Add();   // 0x00b72210 (equiv t2)
    void Get();   // 0x00b72160 (equiv t2)
};
}
