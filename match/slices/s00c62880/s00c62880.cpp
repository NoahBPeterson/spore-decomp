// Slice s00c62880 — SP::cSPMissionWar / cMissionWar mission helpers.
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int);
void  __cdecl operator_delete__(void*);
void  __cdecl WStr_Format(void*, const wchar_t*, ...);          // 0x41e050
void  __cdecl FUN_00ebb720(int, int);                           // 0xebb720
void* __cdecl FUN_00b18460();                                   // 0xb18460
void* __cdecl SP_NounManager();                                 // 0xb3d300
void* __cdecl SP_GetUniverseContext();                          // 0x1021080
void* __cdecl SP_GetActivePlanet();                             // 0x1021260
void* __cdecl SP_GetPlayerEmpire();                             // 0x1021300
void  __cdecl FUN_00c4a0c0();                                   // 0xc4a0c0
void  __cdecl FUN_00c472e0_(void);                              // placeholder

extern float gF_0;

struct VObj { void __fastcall v(); };
static inline void** Vt(void* p){ return *(void***)p; }

// ---- base / mission stub ----------------------------------------------
struct MissionBase {
  void BaseCtor();       // 0xc48e90 cGenericPressureEvent ctor
  void BaseDtor();       // 0xc47680 cSPMission dtor
  bool Init();           // 0xc4ad50
  bool IsActive();       // 0xc44c80
  void GetText(int key, void* out);   // 0xc487d0
  void TriggerUIUpdate();             // 0xc47d80
  void FUN_00c472e0();               // 0xc472e0
  void FUN_00c471c0();               // 0xc471c0
};

struct M {
  char pad00[0x1f0];
  int  state;      // +0x1f0
  int  f1f4;       // +0x1f4
  int  f1f8;       // +0x1f8
  uint8_t f1fc;    // +0x1fc
};

// @ 0x00c62cc0
void* __fastcall cMissionWar_ctor(void* self, int _e) {
  ((MissionBase*)self)->BaseCtor();
  *(int*)((char*)self + 0x1f0) = 0;
  *(int*)((char*)self + 0x1f4) = 0;
  *(uint8_t*)((char*)self + 0x1fc) = 0;
  *(void**)self = (void*)0x1470b88;
  *(void**)((char*)self + 4) = (void*)0x146dfb4;
  *(void**)((char*)self + 0x34) = (void*)0x1470b74;
  *(int*)((char*)self + 0x1f8) = -1;
  return self;
}

// @ 0x00c62ed0
void __fastcall M_GetUIMedium(void* self, int _e, void* out) {
  if (!((MissionBase*)self)->IsActive()) return;
  switch (*(int*)((char*)self + 0x1f0)) {
    case 0: ((MissionBase*)self)->GetText(0xd79a86a8, out); return;
    case 1: ((MissionBase*)self)->GetText(0x81128ae1, out); return;
    case 2: ((MissionBase*)self)->GetText(0xbb0eec72, out); return;
    case 3: ((MissionBase*)self)->GetText(0xa6f2b74a, out); return;
  }
}

// @ 0x00c62f60
void __fastcall M_GetUILong(void* self, int _e, void* out) {
  if (!((MissionBase*)self)->IsActive()) return;
  switch (*(int*)((char*)self + 0x1f0)) {
    case 0: ((MissionBase*)self)->GetText(0x247d8d51, out); return;
    case 1: ((MissionBase*)self)->GetText(0xba93258e, out); return;
    case 2: ((MissionBase*)self)->GetText(0xd22abb35, out); return;
    case 3: ((MissionBase*)self)->GetText(0x1ec90679, out); return;
  }
}

// @ 0x00c63130
void __fastcall M_FailureCityDestroyed(void* self, int _e) {
  if (*(int*)((char*)self + 0x1f0) != 0) return;
  (*(void(__thiscall*)(void*))((*(void***)self)[0x70/4]))(self);
  if (*(int*)((char*)self + 0x1f0) != 2) {
    *(int*)((char*)self + 0x1f0) = 2;
    ((MissionBase*)self)->TriggerUIUpdate();
  }
  ((MissionBase*)self)->FUN_00c472e0();
  ((MissionBase*)self)->FUN_00c471c0();
}

// @ 0x00c63170
void __fastcall M_OnTimerExpire(void* self, int _e) {
  if (*(int*)((char*)self + 0x1f0) != 0) return;
  (*(void(__thiscall*)(void*))((*(void***)self)[0x70/4]))(self);
  if (*(int*)((char*)self + 0x1f0) != 3) {
    *(int*)((char*)self + 0x1f0) = 3;
    ((MissionBase*)self)->TriggerUIUpdate();
  }
  ((MissionBase*)self)->FUN_00c472e0();
  ((MissionBase*)self)->FUN_00c471c0();
}

// @ 0x00c631b0
void __fastcall M_ReturnForRewards(void* self, int _e) {
  if (*(int*)((char*)self + 0x1f0) != 0) return;
  (*(void(__thiscall*)(void*))((*(void***)self)[0x6c/4]))(self);
  if (*(int*)((char*)self + 0x1f0) != 1) {
    *(int*)((char*)self + 0x1f0) = 1;
    ((MissionBase*)self)->TriggerUIUpdate();
  }
  ((MissionBase*)self)->FUN_00c472e0();
  ((MissionBase*)self)->FUN_00c471c0();
}

// @ 0x00c63330
void __fastcall M_C63330(void* self, int _e) {
  (*(void(__thiscall*)(void*))((*(void***)self)[0]))(self);  // 0xc2e4e0
  if (*(int*)((char*)self + 0x1f0) != 0) return;
  (*(void(__thiscall*)(void*))((*(void***)self)[0x6c/4]))(self);
  if (*(int*)((char*)self + 0x1f0) != 1) {
    *(int*)((char*)self + 0x1f0) = 1;
    ((MissionBase*)self)->TriggerUIUpdate();
  }
  ((MissionBase*)self)->FUN_00c472e0();
  ((MissionBase*)self)->FUN_00c471c0();
}

// @ 0x00c63570
void __fastcall M_GetProgressDisplayText(void* self, int _e, void* out) {
  int v = *(int*)((char*)self + 0x1f8);
  if (v >= 0) WStr_Format(out, L"%d/%d", *(int*)((char*)self + 0x1f4), v);
  else        WStr_Format(out, L"%d/?", *(int*)((char*)self + 0x1f4));
}

// @ 0x00c63740
uint32_t __fastcall M_GetTagString(void* self, int _e, int key, void* out) {
  if (key == (int)0xaae66a73) {
    WStr_Format(out, (const wchar_t*)0x13f01bc, *(int*)((char*)self + 0x1f4));
    return 1;
  }
  if (key == (int)0xc74ba481) {
    return 1;
  }
  return ((uint32_t(__thiscall*)(void*, int, void*))0)(self, key, out);
}

// @ 0x00c63a10
void FUN_00c63a10() { FUN_00ebb720(0, 0); }

// @ 0x00c639d0 / 0x00c63a20 / 0x00c639a0 interface adjustors
void* __fastcall M_C639d0(void* self, int _e, void* id) {
  if (id == (void*)0x76c67df) return self;
  if (id == (void*)0x1186577) return self ? (char*)self + 0x34 : 0;
  if (id == (void*)0x7a309fb) return self;
  return (void*)FUN_00b18460();
}
void* __fastcall M_C63a20(void* self, int _e, void* id) {
  if (id == (void*)0x771ad6a) return self;
  if (id == (void*)0x1186577) return self ? (char*)self + 0x34 : 0;
  if (id == (void*)0x7a309fb) return self;
  return (void*)FUN_00b18460();
}
void* __fastcall M_C639a0(void* self, int _e, void* id) {
  if (id == (void*)0x1186577) return self ? (char*)self + 0x34 : 0;
  if (id != (void*)0x7a309fb) return (void*)FUN_00b18460();
  return self;
}

// @ 0x00c62880
void* __fastcall cMissionUseTool_ctor(void* self, int _e) {
  ((MissionBase*)self)->BaseCtor();
  *(int*)((char*)self + 0x1f0) = 0;
  *(void**)self = (void*)0x14709a0;
  *(void**)((char*)self + 4) = (void*)0x1470960;
  *(void**)((char*)self + 0x34) = (void*)0x1470950;
  *(int*)((char*)self + 0x1f4) = 0;
  *(int*)((char*)self + 0x1f8) = 0;
  *(int*)((char*)self + 0x1fc) = 0;
  *(int*)((char*)self + 0x208) = 0;
  *(int*)((char*)self + 0x20c) = 0;
  *(int*)((char*)self + 0x210) = 0;
  return self;
}

// @ 0x00c62930
void* __fastcall cMissionUseTool_dtor(void* self, int _e, uint8_t del) {
  void* p = *(void**)((char*)self + 0x208);
  if (p && *(int*)((char*)p - 4) != 0) operator_delete__(p);
  p = *(void**)((char*)self + 0x1f4);
  if (p && *(int*)((char*)p - 4) != 0) operator_delete__(p);
  ((MissionBase*)self)->BaseDtor();
  if (del & 1) operator_delete__(self);
  return self;
}

// ---- partial / stubbed ------------------------------------------------
void __fastcall M_C62990(void* self, int _e, int a, void* b) { (void)self;(void)a;(void)b; }
void __fastcall M_InitUseTool(void* self, int _e) { (void)self; }
bool __fastcall M_C62b30(void* self, int _e) { (void)self; return false; }
float  __fastcall M_C62ff0(void* self, int _e, int a, void* b) { (void)self;(void)a;(void)b; return 0.0f; }
int    __fastcall M_C631f0(void* self, int _e, int a) { (void)self;(void)a; return 3; }
bool __fastcall M_InitWar(void* self, int _e) { (void)self; return false; }
void __fastcall M_GetUIShort(void* self, int _e, void* out) { (void)self;(void)out; }
int    __fastcall M_GetNumCities(void* self, int _e) { (void)self; return 0; }
void   __fastcall M_C637b0(void* self, int _e, int a, void* b) { (void)self;(void)a;(void)b; }
