// Slice s00e52d80 (batch bfs3, slice 17). Region 0xe52d80-0xe53c66.
// Cell-game mission UI / collectable panel glue. Optimised:
// /O2 /MD /Gy /TP /arch:SSE /fp:fast.  Recurring scope guard = 0x743b50/0xe82130.
#include "types.h"

struct cGuard17 { void* p; cGuard17(); ~cGuard17(); };

extern "C" {
  float    __cdecl FUN_00e52b70();
  void     __cdecl FUN_00e52c70();
  int      __cdecl FUN_00e4fca0();
  int      __cdecl FUN_00e4fd30(char*);
  int      __cdecl FUN_00e530e0();
  void     __cdecl FUN_00e53660(int, int);
  void     __cdecl FUN_00e53b40();
  void     __cdecl FUN_00e569b0();
  void     __cdecl FUN_00e82d10(int);
  int      __cdecl FUN_00e84490(int, int);
  void     __cdecl FUN_00e848c0(int);
  int      __cdecl FUN_00e4ee60(int);
  void     __cdecl FUN_00e7ce10(int, int);
  void*    __cdecl FUN_00b721d0(int);
  void*    __cdecl FUN_00b3d400(void*);
  void*    __cdecl FUN_00b3d3f0(int);
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

// @ 0x00e530e0
int FUN_00e530e0() {
  char local[16];
  int n = FUN_00e4fd30(local);
  int count = 0;
  if (n > 0) {
    int off = 0x34;
    for (int i = 0; i < n; ++i) {
      if (local[i] != 0) {
        int v = *(int*)(off + *(int*)(g_16b3c04 + 0x5190));
        if (v != 1 && v != 2) ++count;
      }
      off += 4;
    }
  }
  return count;
}

// @ 0x00e53130
void FUN_00e53130() {
  FUN_00e82d10(0xde776d90);
  int esi = *(int*)(g_16b3c04 + 0x5190);
  int r = FUN_00e84490(0xd0d8ca6, 0x5bef305);
  if (*(int*)(esi + 0x74) < r) FUN_00e82d10(0xd0d8ca6);
  if (*(int*)(*(int*)(g_16b3c04 + 0x5190) + 0x6c) == 0) FUN_00e82d10(0x662732af);
  if (*(int*)(*(int*)(g_16b3c04 + 0x5190) + 0x7c) == 2) FUN_00e82d10(0x20b852b8);
  FUN_00e848c0(*(int*)(*(int*)(g_16b3c04 + 0x5190) + 0x78));
}

// @ 0x00e531c0
bool FUN_00e531c0(int* self) {
  if (self[0x24] == 4 || self[0x24] == 5) self[0x24] = 0;
  int v = *(int*)((self[0x24] + 8) * 0x10 + *(int*)(g_16b3c04 + 0x5190));
  return v == 2 || v == 3;
}

// @ 0x00e53210
int FUN_00e53210(int* self) {
  int v = self[0x24];
  if (v == 1) return 6 - FUN_00e530e0();
  if (v > 3 && v <= 5) v = 0;
  return *(int*)(*(int*)(g_16b3c04 + 0x5190) + 0x84 + v * 0x10);
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
  char* esi = g_16b3c04;
  int edi = *(int*)(*(int*)(esi + 0x5190) + 0x7c);
  if (edi == 0) return false;
  if (esi[0x51dc] != 0) return false;
  int lvl = FUN_00e4ee60(*(int*)(*(int*)(esi + 0x5190) + 0x1c));
  if (lvl < 3) return false;
  if (esi[0x51c0] != 0 && edi == 1) return false;
  if (!(*(float*)(esi + 0x51bc) <= 0.0f)) return false;
  return true;
}

// @ 0x00e532e0
bool FUN_00e532e0(char* flag, float dt) {
  void* o = FUN_00b721d0(*(int*)(g_16b3c04 + 0x411c));
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

// @ 0x00e53460
void FUN_00e53460(int idx) {
  if (idx == 3) {
    float f = FUN_00e52b70();
    *(float*)(g_16b3c04 + 0x51bc) = f;
  } else {
    FUN_00e82690(0xc1fa4704, 1.0f);
    SP_PatchSoundStart("ui_mission_complete", 0);
  }
  *(int*)((idx + 8) * 0x10 + *(int*)(g_16b3c04 + 0x5190)) = 3;
  *(float*)(*(int*)(g_16b3c04 + 0x5190) + idx * 0x10 + 0x8c) = 5.0f;
  if (idx == 0) {
    FUN_00e53340();
  } else if (idx == 3) {
    *(int*)(g_16b3c04 + 0x51b4) = -1;
    *(int*)(g_16b3c04 + 0x51b0) = 0;
  }
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
    void* w = SubWindow(FindWin(0x6244208));
    Vis(w, 1);
  }
  void* o = FUN_00b3d3f0(0);
  FUN_00e190c0(o);
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
  cSPUILayout17* layout = ((cAlloc17*)(*(int*)(g_16b3c0c + 0x98)))->GetAllocator();
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
  void* a = *(void**)(g_16b3c08 + 0x161c4);
  (*(void(__thiscall**)(void*, float, int))((char*)Vt(a) + 0x24))(a, v, 0);
  void* b = *(void**)(g_16b3c08 + 0x161d0);
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

// @ 0x00e52d80  large mission HUD update -- partial
void FUN_00e52d80(float dt) {
  (void)dt;
}
