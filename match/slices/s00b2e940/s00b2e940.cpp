// s00b2e940.cpp — SP::cAppModeTerrainEditor / cGameTerrainCursor region (mostly unnamed in PDB)
// Reconstructed from Ghidra decompiles + disassembly.  __thiscall entries are modelled as
// member methods of `S` (cl rejects __thiscall on free functions); virtual dispatch goes through
// __thiscall function-pointer typedefs so no edx gets clobbered at the call site.

#include <stddef.h>

typedef void  (__thiscall *TCV0)(void*);
typedef void  (__thiscall *TCV1)(void*, int);
typedef void  (__thiscall *TCV2)(void*, int, int);
typedef void  (__thiscall *TCV3)(void*, int, int, int);
typedef void* (__thiscall *TCP1)(void*, int);
typedef int   (__thiscall *TCI1)(void*, int);
typedef char  (__thiscall *TCR2)(void*, unsigned, int*);
typedef void  (__thiscall *TCVV)(void*, void*, int);
#define VTO(o) (*(void***)(o))

// ---- thiscall helpers (addresses in comments) ------------------------------
struct E {
  void* GetAvatar();                             // 0x00b1fdb0
  void* func8Ch();                               // 0x00ad2800
  void  e830();                                  // 0x00b2e830
  void  bb90();                                  // 0x00b2bb90
  void  dac0();                                  // 0x00b2dac0
  void  bbe0();                                  // 0x00b2bbe0
  void  ProcessPending();                        // 0x00b22960
  void  removeNoun();                            // 0x00b225d0
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
  void  b2b2d0(int,int,int,int*);                // 0x00b2b2d0
  void  spawn(int,int,int,int,int,int,float);    // 0x00b2e010  SpawnMgr::Spawn
  void  FUN_00b2c2a0(int,int);                   // 0x00b2c2a0
  void  FUN_00b2c830(int,int);                   // 0x00b2c830
  void  FUN_00b2af80();                          // 0x00b2af80
  char* getBool();                               // 0x0041e920  Property::GetBool
  int   getInt();                                // 0x0041e990  Property::GetInt
  void  b09340(float, void**, int, int);         // 0x00b09340
  void* GetGameDataVector(int,int,int,int,int);  // 0x00b21340
  void* SpeciesFromID();                         // 0x00b90410
  void* GetPlantProfile();                       // 0x004df440
  void  b73de0(int);                             // 0x00b73de0
  void  b725e0(int);                             // 0x00b725e0
  void* b74e90(int, int);                        // 0x00b74e90
};

// ---- cdecl / stdcall runtime helpers ---------------------------------------
extern "C" void* __cdecl FUN_00b3d3c0(void);                        // 0x00b3d3c0
extern "C" void* __stdcall NounManager0(void);                      // 0x00b3d300 (0 args)
extern "C" void* __stdcall NounManager1(void*);                     // 0x00b3d300 (1 arg)
extern "C" void* __stdcall FUN_00b3d440(void*, void*, int);         // 0x00b3d440
extern "C" void* __stdcall FUN_00b79c30(void*, void*, int, float, int, int); // 0x00b79c30
extern "C" void  __cdecl operator_delete__(void*);                  // 0x00f47380
extern "C" void* __cdecl RBTreeIncrement(void*);                    // 0x00921580
extern "C" void  __stdcall FUN_00f921d0(int,int);                   // 0x00f921d0
extern "C" void* __cdecl FUN_01021260(void);                        // 0x01021260
extern "C" void  __cdecl FUN_010210e0(void*);                       // 0x010210e0
extern "C" void* __cdecl GetActiveTerrainSphere(void);              // 0x00f48aa0
extern "C" void  __cdecl RemoveHandler(int,int,int,int,int);        // 0x00571db0
extern "C" void* __cdecl GetCurrentGameMode(void);                  // 0x00b5b800
extern "C" void* __cdecl GetCurrentGameModeAlt(void);               // 0x00b5b820
extern "C" void* __cdecl FUN_00b3d320(void*,int);                   // 0x00b3d320
extern "C" void* __cdecl SpaceGameGet(void);                        // 0x01002bd0
extern "C" void* __cdecl cCivModeStrategy_Get(void);                // 0x00cf74c0
extern "C" void* __cdecl cTribeModeStrategy_Instance(void);         // 0x00cd40b0
extern "C" void* __cdecl FUN_0067ddc0(void);                        // 0x0067ddc0
extern "C" void* __cdecl EffectsManager(void);                      // 0x0067ddd0
extern "C" void* __cdecl ModelManager(void);                        // 0x0067dd80
extern "C" void* __stdcall FUN_0067de00(int);                         // 0x0067de00
extern "C" void* __cdecl GonzagoModelWorld(void);                   // 0x00b3d520
extern "C" void* __cdecl FUN_00b33f40(void);                        // 0x00b33f40
extern "C" void* __cdecl FUN_00b3d420(void*);                       // 0x00b3d420
extern "C" void* __cdecl GetSetting9(void*);                        // 0x00401090
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
};

// ---------------------------------------------------------------------------
// @ 0x00b2e940 — cursor combat/reveal update (711 B); main flow reconstructed
// ---------------------------------------------------------------------------
void S::FUN_00b2e940(float dt) {
  char* p = (char*)this;
  if (((*(unsigned*)(p + 0x20) >> 2) & 1) != 0) {
    void* pcVar4 = NounManager0();
    void* iVar5 = ((E*)pcVar4)->GetAvatar();
    float d = *(float*)(p + 0x24) - dt;
    *(float*)(p + 0x24) = d;
    if (iVar5 != 0 && d <= 0.0f) {
      void* local_4a0[2];
      local_4a0[0] = 0; local_4a0[1] = 0;
      void* a = (void*)local_4a0;
      *(float*)(p + 0x24) = 3.0f;
      void* obj = (char*)iVar5 + 0xc0;
      void* res = ((void*(__thiscall*)(void*, float, void**, int, int))(VTO(obj))[0x2c/4])(obj, 48.0f, &a, 1, 0);
      void* uVar6 = FUN_00b3d440(res, 0, 0);
      ((E*)uVar6)->b09340(0.0f, &a, 1, 0);
    }
  }
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
// @ 0x00b2ede0 — message handler (862 B); switch reconstructed
// ---------------------------------------------------------------------------
char S::FUN_00b2ede0(void* msg, int* data) {
  char* p = (char*)this;
  if ((unsigned)msg < 0x1a0219fu) {
    if (msg == (void*)0x1a0219e) {
      if (data[2] == 1) ((E*)p)->e830();
      return 1;
    }
    if (msg == (void*)0xf62def) {
      if (data[4] != g_1568d3c && data[4] != 0x314f28a) return 0;
      // FUN_00b2cd90-equivalent refresh
      return 0;
    }
    if (msg == (void*)0x182c582) { g_167e09c = 3; return 0; }
    return 0;
  }
  if (msg == (void*)0x31018b9) {
    if (((*(unsigned*)(p + 0x20) >> 1) & 1) == 0) return 0;
    int iVar2 = data[2];
    int iVar3 = data[4];
    if (iVar2 == 0) {
      int local_34;
      ((void(__thiscall*)(void*, int*, int*))(VTO(p + 0x190))[0])(p + 0x190, &local_34, &iVar3);
      if (local_34 != (int)(p + 0x194)) ((E*)*(void**)(local_34 + 0x14))->b090(1);
    } else {
      int count = (*(int*)(p + 0x180) - *(int*)(p + 0x17c)) / 0x24;
      if (count != 0) {
        int* piVar7 = (int*)(*(int*)(p + 0x17c) + 8);
        unsigned u8 = 0;
        while (piVar7[-1] != data[6] && *piVar7 != data[6]) {
          u8++;
          piVar7 += 9;
          if ((unsigned)count <= u8) return 1;
        }
        if (((*(unsigned*)(*(int*)(p + 0x17c) + 0x20 + u8 * 0x24) >> 1) & 1) != 0 && u8 != 0xffffffffu) {
          (void)iVar3;
        }
      }
    }
    return 1;
  }
  if (msg == (void*)0x32f76e7) return 1;
  return 0;
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
// @ 0x00b2f350 — apply mode settings (806 B); flow reconstructed
// ---------------------------------------------------------------------------
void S::FUN_00b2f350(int mode) {
  char* p = (char*)this;
  char cMode = 0, cFlag2 = 0, cFlag3 = 0;
  if (mode == 0x1654c06) mode = (int)GetCurrentGameModeAlt();
  void* o = FUN_00b3d320((void*)mode, 1);
  void* edi = ((Xb1daf0*)o)->FUN_00b1daf0((void*)mode);
  if (edi != 0) {
    ((TCV0)(VTO(edi))[0/4])(edi);
    int l0 = 0, l1 = 0, l2 = 0, l3 = 0;
    char ok = (char)((TCR2)(VTO(edi))[0x24/4])(edi, 0x25f0761u, &l0);
    if (ok && *(short*)(l0 + 0x12) == 1) cMode = *((E*)l0)->getBool();
    ok = (char)((TCR2)(VTO(edi))[0x24/4])(edi, 0x32a54b9u, &l1);
    if (ok && *(short*)(l1 + 0x12) == 1) cFlag2 = *((E*)l1)->getBool();
    ok = (char)((TCR2)(VTO(edi))[0x24/4])(edi, 0x3dad600u, &l2);
    if (ok && *(short*)(l2 + 0x12) == 1) cFlag3 = *((E*)l2)->getBool();
    ok = (char)((TCR2)(VTO(edi))[0x24/4])(edi, 0x6e212ea9u, &l3);
    if (ok && *(short*)(l3 + 0x12) == 9) g_1568cf0 = ((E*)l3)->getInt();
  }
  (void)cFlag2; (void)cFlag3;
  char oldBit = *(char*)(p + 0x20) & 1;
  if (cMode != 0) *(unsigned*)(p + 0x20) |= 1u; else *(unsigned*)(p + 0x20) &= ~1u;
  if (oldBit != 0 && cMode == 0) ((S*)p)->FUN_00b2f140();
  if ((*(unsigned*)(p + 0x20) & 1) != 0) {
    void* planet = FUN_01021260();
    char* iVar6 = *(char**)((char*)planet + 0x13c);
    int iVar13 = (*(int*)(iVar6 + 0xc0) - *(int*)(iVar6 + 0xbc)) / 0xc;
    int off = 0;
    while (iVar13 > 0) {
      void* piVar3 = FUN_00b33f40();
      void* iVar7 = FUN_00b3d420(iVar6 + 0xbc + off);
      void* piVar8 = ((void*(__thiscall*)(void*))(VTO(piVar3))[0x18/4])(piVar3);
      if (piVar8 != 0) {
        void* sp = GetSetting9(iVar7);
        (void)sp;
      }
      off += 0xc;
      iVar13--;
    }
  }
  if (mode != 0xdbdba1 && ((*(unsigned*)(p + 0x20) >> 1) & 1) != 0) {
    void* nm = NounManager1((void*)0);
    ((E*)nm)->GetGameDataVector(0xcd7d10, 0xd3d420, 0xb2d1d0, 0xb1e500, 0x2a8fb3f);
  }
  if (edi != 0) ((TCV0)(VTO(edi))[4/4])(edi);
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
