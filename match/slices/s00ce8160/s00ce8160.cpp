// Slice s00ce8160 (batch gold6, worker 44). Region 0x00ce8160-0x00ce90a0.
// SP::cCityInputStrategy action-menu cluster plus small minimap/icon helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef          short s16;
typedef          char  s8;

// ---- external callees (address in comment) ------------------------------
void* __cdecl SP_NounManager();                      // 0x00b3d300 SP::NounManager
void* __cdecl SP_PlanetModel();                      // 0x00b3d350 SP::PlanetModel
void* __cdecl SP_EventLog();                         // 0x00b3d3e0 SP::EventLog
void* __cdecl FUN_00b3d400();                        // 0x00b3d400 mission card panel accessor
void* __cdecl SP_GetGameTerrainCursor();             // 0x00b30d70
s32   __cdecl FUN_00458a40(void* rgb);               // 0x00458a40 SP::ColorRGBToU32
void  __cdecl FUN_00b7d390(void* self);              // 0x00b7d390
void  __cdecl FUN_00b7d2e0(void* self, void* str);   // 0x00b7d2e0
void  __cdecl FUN_00b7c890(u32 id, u32 color);       // 0x00b7c890
void  __cdecl FUN_00b7cc60(void* self, void* a, int b);// 0x00b7cc60
void* __cdecl FUN_00b7c890_a();                      // (unused)
void* __cdecl SP_cSPUIEventLogDummy();               // (unused)
void  __cdecl FUN_00dd8da0(void* self, u8 v);        // 0x00dd8da0 SP::cSPUIEventLog::SetVisibility
void  __cdecl FUN_00e14c10(void* self, u8 v);        // 0x00e14c10 cUIMissionCardPanel::SetCardsVisibility
void  __cdecl FUN_00e01350(void* self, u8 v);        // 0x00e01350 cSPUIGlobalUI::SetVisibility
void* __cdecl FUN_00e012b0(void* self, u32 id);      // 0x00e012b0 cSPUIGlobalUI::FindWindowByID
void  __cdecl FUN_00e0f9c0(void* self, void* obj, int a, int b); // 0x00e0f9c0 cSPUIMinimapWin::RemoveIcon
void  __cdecl FUN_00e10580(void* self, void* obj, void* data, int a, int b); // 0x00e10580 cSPUIMinimapWin::AddIcon
void* __cdecl FUN_0067ddd0();                        // 0x0067ddd0 SP::EffectsManager
void* __cdecl FUN_00b3d230();                        // 0x00b3d230
u8    __cdecl FUN_00b5c980(void* self);              // 0x00b5c980
void* __cdecl FUN_00bd9bf0(void* self);              // 0x00bd9bf0 SP::cCity::GetCivilization
float __cdecl FUN_00bf06d0(void* self);              // 0x00bf06d0 city_music_index
float __cdecl FUN_00bef6d0(void* self);              // 0x00bef6d0 SP::cCivilization::GetMoney
s32   __cdecl FUN_00b1f9d0(void* self);              // 0x00b1f9d0 GetPlayerEmpireOrMinus1
void* __cdecl FUN_00b25fb0(void* self);              // 0x00b25fb0 GetPlayerCivilization
void* __cdecl FUN_00b25f40(void* self, u32 id);      // 0x00b25f40 FindNounByID
u8    __cdecl FUN_00bf19c0(void* self, void* a);     // 0x00bf19c0
u8    __cdecl FUN_00bdb200(void* self, s32 a);       // 0x00bdb200
u8    __cdecl FUN_00bd7fc0(void* self, s32 a);       // 0x00bd7fc0
s32   __cdecl FUN_00bf01f0(void* self, s32 a, s32 b);// 0x00bf01f0 count_specialty_cities
u8    __cdecl FUN_00bd7e20(void* self);              // 0x00bd7e20
s32   __cdecl FUN_00bdb280(void* self, s32 a);       // 0x00bdb280
u8    __cdecl FUN_00ca8340(void* self, void* a);     // 0x00ca8340
void* __cdecl FUN_00fa0e00(void* self);              // 0x00fa0e00 cCity::GetPositionPtr
u8    __cdecl FUN_00c9fe40(void* self, void* a);     // 0x00c9fe40
u8    __cdecl FUN_00c74550(void* self, void* a);     // 0x00c74550
u8    __cdecl FUN_00c73f10(void* self, void* a);     // 0x00c73f10 cPlanet::IsSpeciesScanned
void* __cdecl FUN_01021260();                        // 0x01021260 GetActivePlanet
void* __cdecl FUN_00ce6950(void* self);              // 0x00ce6950 cStarRecordRef::GetCommContext
void* __cdecl FUN_00b3d4f0(void* self);              // 0x00b3d4f0
void* __cdecl FUN_00e30d20(void* self);              // 0x00e30d20
void* __cdecl FUN_00ba4e60(void* self, void* a);     // 0x00ba4e60
void* __cdecl FUN_00ba4520(void* self, void* a);     // 0x00ba4520
void* __cdecl FUN_00ba57a0(void* self, s32 a);       // 0x00ba57a0
void* __cdecl FUN_00a206f0();                        // 0x00a206f0 EA::Audio::GetSystemAT
void  __cdecl FUN_00ad92d0(void* self);              // 0x00ad92d0 vector dtor
void  __cdecl FUN_00f47380(void* p);                 // 0x00f47380 operator_delete_array
void* __cdecl FUN_006b5770(void* self, u32 a, u32 b, const void* wstr); // cString::cString
void* __cdecl FUN_006b55c0(void* self, u32 a, u32 b); // cString::GetText / IsMaxValue
void* __cdecl FUN_006b5240(void* self);               // cString::~cString / c_str
void* __cdecl FUN_00f473a0(u32 size, const char*, int, int, int, int); // operator new
void* __cdecl FUN_00b6f310(void* self);              // 0x00b6f310
void* __cdecl FUN_00b81780(void* self, void* out, void* a, void* b, void* c); // 0x00b81780 MakeRandomWorldPosition
void* __cdecl FUN_00bfc490(void* self);              // 0x00bfc490
void  __cdecl FUN_00ce8f70(void* obj, void* win);
void* __cdecl FUN_00f67d90(void* self);              // 0x00f67d90 cTerrainEditor::GetCurrentTerrainSphere
u8    __cdecl WStrAppend(void* self, const void* a, const void* b); // 0x00429580
void  __cdecl WStrSprintf(void* self, const void* fmt, void* a);    // 0x0041e050
void  __cdecl FUN_00435ed0(void* a, void* b, u32 c); // 0x00435ed0 KillSetiEffects
void  __fastcall FUN_00ce8160(void* self, void* edx);
u8    __fastcall FUN_00ce8370(void* self, void* edx, void* arg);
u8    __fastcall FUN_00ce87c0(void* self, void* edx, void* arg);

// ======================================================================
// 0x00ce8db0 - cCityInputStrategy::GetPieMenuWindow-ish tiny accessor.
// this in ecx, no stack args.
// ======================================================================

// @ 0x00ce8db0
void* __fastcall FUN_00ce8db0(void* self, void* /*edx*/) {
  char* p = (char*)self;
  void* g = *(void**)(p + 0x64);
  if (g != 0) {
    return ((void*(__thiscall*)(void*, u32))FUN_00e012b0)(g, 0x5e66e88);
  }
  return 0;
}

// ======================================================================
// 0x00ce8d80 - forward a noun id to the effects/sound UI. this in ecx.
// ======================================================================

// @ 0x00ce8d80
void __fastcall FUN_00ce8d80(void* self, void* /*edx*/) {
  char* p = (char*)self;
  char* m = (char*)FUN_0067ddd0();
  char* a = (char*)((void*(__thiscall*)(void*))(*(void***)m)[0x5c / 4])(m);
  char* b = (char*)((void*(__thiscall*)(void*))(*(void***)a)[0x20 / 4])(a);
  ((void(__thiscall*)(void*, void*))(*(void***)b)[0x1c / 4])(
      b, *(void**)(p + 4));
}

// ======================================================================
// 0x00ce90a0 - add/update an icon for the object via the minimap window.
// this in ecx, one stack arg.
// ======================================================================

// @ 0x00ce90a0
void __fastcall FUN_00ce90a0(void* self, void* /*edx*/, void* obj) {
  char* p = (char*)self;
  void* win = *(void**)(p + 0xf0);
  if (win != 0) {
    FUN_00ce8f70(obj, win);
  }
}

// ======================================================================
// 0x00ce8f70 - SP::AddOrUpdateNodeIcon. this in ecx, one stack arg.
// ======================================================================

// @ 0x00ce8f70
void __cdecl FUN_00ce8f70(void* obj, void* win) {
  char* o = (char*)obj;
  ((void(__thiscall*)(void*, void*, int, int))FUN_00e0f9c0)(win, o, 1, 0);

  struct IconData {
    u32 color;   // +0
    float x;     // +4
    float y;     // +8
    float z;     // +0xc
    u32 flags;   // +0x10
    u32 pad;     // +0x14
    u32 pad2;    // +0x18
    u32 pad3;    // +0x1c
    void* ref;   // +0x20
  } icon;
  icon.color = 0xff808080;
  icon.x = 0.0f;
  icon.y = 0.0f;
  icon.z = 0.0f;
  icon.flags = 0x4000;
  icon.pad = 0;
  icon.pad2 = 0;
  icon.pad3 = 0;
  icon.ref = 0;

  s32 id = ((s32(__thiscall*)(void*))(*(void***)o)[0x4c / 4])(o);
  if (id != -1) {
    void* nm = SP_NounManager();
    char* noun = (char*)FUN_00b25f40(nm, (u32)id);
    if (noun != 0) {
      icon.color = (u32)FUN_00b6f310(noun + 0x3c);
    }
  }

  float s = *(float*)0x013eecd8;
  ((void(__thiscall*)(void*))(*(void***)(o + 0x34))[0x2c / 4])(o + 0x34);
  (void)s;
  void* pm = SP_PlanetModel();
  FUN_00b81780(pm, &icon.x, (void*)0x41a00000, (void*)0x41a00000, 0);

  char* oldRef = (char*)icon.ref;
  if (o != oldRef) {
    ((void(__thiscall*)(void*))(*(void***)o)[0 / 4])(o);
    icon.ref = o;
    if (oldRef != 0) {
      ((void(__thiscall*)(void*))(*(void***)oldRef)[4 / 4])(oldRef);
    }
  }
  FUN_00e10580(win, o, &icon, 0, 0);
  void* r = icon.ref;
  if (r != 0) {
    ((void(__thiscall*)(void*))(*(void***)r)[4 / 4])(r);
  }
}

// ======================================================================
// 0x00ce8ee0 - show/hide the city input strategy UI. this in ecx,
// one stack arg (bool visible); ret 4.
// ======================================================================

// @ 0x00ce8ee0
void __fastcall FUN_00ce8ee0(void* self, void* /*edx*/, u8 visible) {
  char* p = (char*)self;
  void* gui = *(void**)(p + 0x64);
  if (gui != 0) {
    ((void(__thiscall*)(void*, u8))FUN_00e01350)(gui, visible);
  }
  char* win = *(char**)(p + 0xf0);
  if (win != 0) {
    char* inner = win + 4;
    ((void(__thiscall*)(void*, int, u8))(*(void***)inner)[0x7c / 4])(inner, 1, visible);
  }
  char* it = p + 0x6c;
  int n = 4;
  do {
    char* slot = *(char**)it;
    if (slot != 0) {
      u32 cnt = (u32)((s32)(*(u32*)(slot + 0xa8) - *(u32*)(slot + 0xa4)) >> 3);
      if (cnt > 0 || visible != 0) {
        ((void(__thiscall*)(void*, u8))(*(void***)slot)[0xc0 / 4])(slot, visible);
      }
    }
    it += 4;
    n--;
  } while (n != 0);
  ((void(__thiscall*)(void*, u8))FUN_00dd8da0)(SP_EventLog(), visible);
  char* pp = (char*)FUN_00b3d400();
  if (pp != 0) {
    ((void(__thiscall*)(void*, u8))FUN_00e14c10)((void*)FUN_00b3d400(), visible);
  }
}

// ======================================================================
// 0x00ce8de0 - add/update a city icon on the minimap. this in ecx,
// one stack arg (city); ret 4.
// ======================================================================

// @ 0x00ce8de0
void __fastcall FUN_00ce8de0(void* self, void* /*edx*/, char* city) {
  char* p = (char*)self;
  void* win = *(void**)(p + 0xf0);
  if (win == 0) return;

  struct IconData {
    u32 color;   // +0
    float x;     // +4
    float y;     // +8
    float z;     // +0xc
    u32 flags;   // +0x10
    u32 pad;     // +0x14
    u32 pad2;    // +0x18
    void* ref;   // +0x1c
  } icon;
  icon.color = 0;
  icon.x = 0.0f;
  icon.y = 0.0f;
  icon.z = 0.0f;
  icon.flags = 1;
  icon.pad = 0;
  icon.pad2 = 0;
  icon.ref = 0;

  ((void(__thiscall*)(void*, void*, int, int))FUN_00e0f9c0)(win, city, 1, 0);
  icon.flags = 1;

  char* comp = city + 0x120;
  u8 c = ((u8(__thiscall*)(void*))(*(void***)comp)[0x58 / 4])(comp);
  if (c != 0) icon.flags |= 8;

  float* pos = (float*)((void*(__thiscall*)(void*))(*(void***)comp)[0x2c / 4])(comp);
  icon.x = pos[0];
  icon.y = pos[1];
  icon.z = pos[2];
  void* civ = FUN_00bd9bf0(city);
  icon.color = (u32)FUN_00b6f310((char*)civ + 0x3c);

  char* oldRef = (char*)icon.ref;
  if (city != oldRef) {
    ((void(__thiscall*)(void*))(*(void***)city)[0 / 4])(city);
    icon.ref = city;
    if (oldRef != 0) {
      ((void(__thiscall*)(void*))(*(void***)oldRef)[4 / 4])(oldRef);
    }
  }
  ((void(__thiscall*)(void*, void*, void*, int, int))FUN_00e10580)(win, city, &icon, 0, 0);
  void* r = icon.ref;
  if (r != 0) {
    ((void(__thiscall*)(void*))(*(void***)r)[4 / 4])(r);
  }
}

// ======================================================================
// 0x00ce8d00 - pie-menu branch helper. this in ecx, two stack args
// (int* cmd, int owner); ret 8.
// ======================================================================

// @ 0x00ce8d00
void __fastcall FUN_00ce8d00(void* self, void* /*edx*/, void* cmd, void* owner) {
  char* o = (char*)owner;
  float r = ((float(__thiscall*)(void*))FUN_00bfc490)(o + 0x508);
  void* self2 = cmd;
  void** vtbl = *(void***)self2;
  if (r < *(float*)0x013ef74c) {
    ((void(__thiscall*)(void*, int, int))vtbl[0x84 / 4])(self2, 0, 2);
  } else if (o[0xbcc] != 0) {
    ((void(__thiscall*)(void*, int, int))vtbl[0x84 / 4])(self2, 0, 1);
  } else {
    ((void(__thiscall*)(void*, int, int))vtbl[0x84 / 4])(self2, 0, 0);
  }
}

// ======================================================================
// 0x00ce8160 - SP::cCityInputStrategy::PrepareCityNPCPieMenu. this in ecx.
// ======================================================================

// @ 0x00ce8160
void __fastcall FUN_00ce8160(void* self, void* /*edx*/) {
  char* p = (char*)self;

  // Five cString temporaries built from loc keys + wide literals.
  char s0[20], s1[20], s2[20], s3[20], s4[20];
  ((void(__thiscall*)(void*, u32, u32, const void*))FUN_006b5770)(
      s4, 0xbeb528cb, 0x4d194fe, (const void*)0x01477bc8);  // "!!!Give Gift"
  ((void(__thiscall*)(void*, u32, u32, const void*))FUN_006b5770)(
      s3, 0xbeb528cb, 0x4d1956a, (const void*)0x01477bb0);  // "!!!Buy City"
  ((void(__thiscall*)(void*, u32, u32, const void*))FUN_006b5770)(
      s2, 0xbeb528cb, 0x52ecbe1, (const void*)0x01477b68);
  ((void(__thiscall*)(void*, u32, u32, const void*))FUN_006b5770)(
      s1, 0xbeb528cb, 0x52ecbe2, (const void*)0x01477b20);
  ((void(__thiscall*)(void*, u32, u32, const void*))FUN_006b5770)(
      s0, 0xbeb528cb, 0x4d29b0c, (const void*)0x01477b04);  // "!!!Contact"

  const void* txt = (const void*)((void*(__thiscall*)(void*, u32, u32))FUN_006b55c0)(
      s0, 0x46ee610, 0);
  FUN_00b7d2e0(*(void**)(p + 0x5c), (void*)txt);

  void* nm = SP_NounManager();
  s32 empire = FUN_00b1f9d0(nm);
  char* city = *(char**)(p + 0x10c);
  s32 id = ((s32(__thiscall*)(void*))(*(void***)city)[0x84 / 4])(city);
  char* veh = (char*)id;
  void* nm2 = SP_NounManager();
  void* civ = FUN_00b25fb0(nm2);
  void* cityCiv = FUN_00bd9bf0(veh);
  u8 b = FUN_00bf19c0(civ, cityCiv);
  if (b != 0) {
    const void* t2 = (const void*)((void*(__thiscall*)(void*, u32, u32))FUN_006b55c0)(
        s4, 0x51b4174, 0);
    FUN_00b7d2e0(*(void**)(p + 0x5c), (void*)t2);
  }

  u8 c1 = FUN_00bdb200(veh, empire);
  bool go274 = false;
  if (c1 == 0 || *(s32*)(veh + 0x75c) != empire) {
    u8 c2 = FUN_00bd7fc0(veh, empire);
    if (c2 != 0) {
      go274 = true;
    } else {
      u8 c3 = FUN_00bdb200(veh, empire);
      if (c3 != 0) goto done;
      void* nm3 = SP_NounManager();
      void* civ2 = FUN_00b25fb0(nm3);
      s32 n = FUN_00bf01f0(civ2, 2, 0);
      if (n < 1) goto done;
      const void* t3 = (const void*)((void*(__thiscall*)(void*, u32, u32))FUN_006b55c0)(
          s1, 0x37e95bb, 0);
      FUN_00b7d2e0(*(void**)(p + 0x5c), (void*)t3);
      goto color;
    }
  } else {
    go274 = true;
  }
  if (go274) {
    u8 c4 = FUN_00bd7fc0(veh, empire);
    if (c4 != 0) {
      const void* t4 = (const void*)((void*(__thiscall*)(void*, u32, u32))FUN_006b55c0)(
          s3, 0x37e95bb, 0);
      FUN_00b7d2e0(*(void**)(p + 0x5c), (void*)t4);
      goto done;
    }
    const void* t5 = (const void*)((void*(__thiscall*)(void*, u32, u32))FUN_006b55c0)(
        s2, 0x37e95bb, 0);
    FUN_00b7d2e0(*(void**)(p + 0x5c), (void*)t5);
  }
color:
  {
    u32 rgb[3];
    rgb[0] = *(u32*)0x01485720;
    rgb[1] = 0;
    rgb[2] = 0;
    u32 col = (u32)FUN_00458a40(rgb);
    FUN_00b7c890(0x37e95bb, col);
  }
done:
  ((void(__thiscall*)(void*))FUN_006b5240)(s4);
  ((void(__thiscall*)(void*))FUN_006b5240)(s3);
  ((void(__thiscall*)(void*))FUN_006b5240)(s2);
  ((void(__thiscall*)(void*))FUN_006b5240)(s1);
  ((void(__thiscall*)(void*))FUN_006b5240)(s0);
}

// ======================================================================
// 0x00ce8370 - SP::cCityInputStrategy::PrepareVehicleVsCityMenu. this in
// ecx, one stack arg; ret 4.
// ======================================================================

// @ 0x00ce8370
u8 __fastcall FUN_00ce8370(void* self, void* /*edx*/, void* arg) {
  char* p = (char*)self;
  char* param2 = (char*)arg;

  u32 vec[3];
  vec[0] = 0; vec[1] = 0; vec[2] = 0;
  char* tc = (char*)SP_GetGameTerrainCursor();
  ((void(__thiscall*)(void*, void*, u32))(*(void***)tc)[0x60 / 4])(tc, vec, 0x137e8e0);
  char* beg = (char*)vec[0];
  char* end = (char*)vec[1];
  if (beg == end) {
    FUN_00ad92d0(vec);
    return 0;
  }
  s32 counts[10];
  for (int k = 0; k < 10; k++) counts[k] = 0;
  char* veh = 0;
  if (param2 != 0) {
    veh = (char*)((void*(__thiscall*)(void*, u32))(*(void***)param2)[0xc / 4])(param2, 0xe9cb8ba);
  }
  p[0x10c] = (char)veh;
  (void)veh;

  s32 best = -1;
  for (char* it = beg; it != end; it += 4) {
    char* sp = *(char**)it;
    char* noun = 0;
    if (sp != 0) {
      noun = (char*)((void*(__thiscall*)(void*, u32))(*(void***)sp)[0xb8 / 4])(sp, 0x137e8e0);
    }
    s32 idx = *(s32*)(noun + 0xb20);
    counts[idx]++;
    char* v = *(char**)(p + 0x10c);
    s32 pid = ((s32(__thiscall*)(void*))(*(void***)v)[0x84 / 4])(v);
    u8 ok = FUN_00ca8340(noun, (void*)pid);
    if (ok != 0) {
      if (*(s32*)(noun + 0xb1c) == 1) {
        char* v2 = *(char**)(p + 0x10c);
        s32 cid = ((s32(__thiscall*)(void*))(*(void***)v2)[0x84 / 4])(v2);
        float* pos = (float*)FUN_00fa0e00((void*)cid);
        if (pos[0] == *(float*)0x0169b490 &&
            pos[1] == *(float*)0x0169b494 &&
            pos[2] == *(float*)0x0169b498) {
          goto next;
        }
      }
      counts[idx + 5]++;
    }
  next:
    s32 last = ((s32(__thiscall*)(void*))(*(void***)noun)[0x4c / 4])(noun);
    best = last;
  }

  char* v3 = *(char**)(p + 0x10c);
  char* rec = (char*)((void*(__thiscall*)(void*))(*(void***)v3)[0x30 / 4])(v3);
  char* city = 0;
  if (rec != 0) {
    city = (char*)((void*(__thiscall*)(void*, u32))(*(void***)rec)[0xc / 4])(rec, 0xee9b2232);
  }
  u8 anySet = 1;
  char cs[20];
  (void)cs;

  if (counts[0] != 0) {
    if (counts[5] == 0) {
      ((void(__thiscall*)(void*, u32, u32, const void*))FUN_006b5770)(
          cs, 0xbeb528cb, 0x563ce33, (const void*)0x01477d90);
      const void* t = (const void*)((void*(__thiscall*)(void*, u32, u32))FUN_006b55c0)(cs, 0x37e95b9, 0);
      FUN_00b7d2e0(*(void**)(p + 0x5c), (void*)t);
      u32 rgb[3]; rgb[0] = *(u32*)0x01485720; rgb[1] = 0; rgb[2] = 0;
      FUN_00b7c890(0x37e95b9, (u32)FUN_00458a40(rgb));
    } else {
      ((void(__thiscall*)(void*, u32, u32, const void*))FUN_006b5770)(
          cs, 0xbeb528cb, 0x4d18ff4, (const void*)0x01477d70);
      const void* t = (const void*)((void*(__thiscall*)(void*, u32, u32))FUN_006b55c0)(cs, 0x37e95b9, 0);
      FUN_00b7d2e0(*(void**)(p + 0x5c), (void*)t);
    }
    ((void(__thiscall*)(void*))FUN_006b5240)(cs);
    anySet = 0;
  }
  if (counts[1] != 0) {
    if (counts[6] == 0) {
      ((void(__thiscall*)(void*, u32, u32, const void*))FUN_006b5770)(
          cs, 0xbeb528cb, 0x563ce86, (const void*)0x01477d30);
      const void* t = (const void*)((void*(__thiscall*)(void*, u32, u32))FUN_006b55c0)(cs, 0x37e95ba, 0);
      FUN_00b7d2e0(*(void**)(p + 0x5c), (void*)t);
      u32 rgb[3]; rgb[0] = *(u32*)0x01485720; rgb[1] = 0; rgb[2] = 0;
      FUN_00b7c890(0x37e95ba, (u32)FUN_00458a40(rgb));
    } else {
      u8 c = FUN_00bd7e20(city);
      if (c == 0) {
        ((void(__thiscall*)(void*, u32, u32, const void*))FUN_006b5770)(
            cs, 0xbeb528cb, 0x6776ca9, (const void*)0x01477c90);
      } else {
        ((void(__thiscall*)(void*, u32, u32, const void*))FUN_006b5770)(
            cs, 0xbeb528cb, 0x4d19085, (const void*)0x01477d10);
      }
      const void* t = (const void*)((void*(__thiscall*)(void*, u32, u32))FUN_006b55c0)(cs, 0x37e95ba, 0);
      FUN_00b7d2e0(*(void**)(p + 0x5c), (void*)t);
    }
    ((void(__thiscall*)(void*))FUN_006b5240)(cs);
    anySet = 0;
  }
  if (counts[2] != 0) {
    if (counts[7] == 0) {
      ((void(__thiscall*)(void*, u32, u32, const void*))FUN_006b5770)(
          cs, 0xbeb528cb, 0x563cec2, (const void*)0x01477c40);
      const void* t = (const void*)((void*(__thiscall*)(void*, u32, u32))FUN_006b55c0)(cs, 0x37e95bc, 0);
      FUN_00b7d2e0(*(void**)(p + 0x5c), (void*)t);
      u32 rgb[3]; rgb[0] = *(u32*)0x01485720; rgb[1] = 0; rgb[2] = 0;
      FUN_00b7c890(0x37e95bc, (u32)FUN_00458a40(rgb));
    } else {
      s32 r = FUN_00bdb280(city, best);
      if (r == 0) {
        ((void(__thiscall*)(void*, u32, u32, const void*))FUN_006b5770)(
            cs, 0xbeb528cb, 0x4d1912c, (const void*)0x01477c0c);
        const void* t = (const void*)((void*(__thiscall*)(void*, u32, u32))FUN_006b55c0)(cs, 0x37e95bc, 0);
        FUN_00b7d2e0(*(void**)(p + 0x5c), (void*)t);
      } else {
        ((void(__thiscall*)(void*, u32, u32, const void*))FUN_006b5770)(
            cs, 0xbeb528cb, 0x4d19177, (const void*)0x01477be4);
        const void* t = (const void*)((void*(__thiscall*)(void*, u32, u32))FUN_006b55c0)(cs, 0x37e95bd, 0);
        FUN_00b7d2e0(*(void**)(p + 0x5c), (void*)t);
      }
      anySet = 0;
    }
    ((void(__thiscall*)(void*))FUN_006b5240)(cs);
  }

  for (char* it = beg; it != end; it += 4) {
    char* sp = *(char**)it;
    if (sp != 0) {
      ((void(__thiscall*)(void*))(*(void***)sp)[0xc0 / 4])(sp);
    }
  }
  FUN_00ad92d0(vec);
  return (u8)(anySet ? 0 : 1);
}
// ======================================================================
// 0x00ce87c0 - FUN_00ce87c0. this in ecx, one stack arg; ret 4.
// ======================================================================

// @ 0x00ce87c0
u8 __fastcall FUN_00ce87c0(void* self, void* /*edx*/, void* arg) {
  char* p = (char*)self;
  char* param2 = (char*)arg;
  ((void(__thiscall*)(void*))FUN_00b7d390)(*(void**)(p + 0x68));

  u32 vec[3];
  vec[0] = 0; vec[1] = 0; vec[2] = 0;
  char* tc = (char*)SP_GetGameTerrainCursor();
  ((void(__thiscall*)(void*, void*, u32))(*(void***)tc)[0x60 / 4])(tc, vec, 0x137e8e0);
  char* beg = (char*)vec[0];
  char* end = (char*)vec[1];
  if (beg == end) {
    FUN_00ad92d0(vec);
    return 0;
  }
  p[0x11c] = (char)param2;
  s32 counts[6];
  for (int k = 0; k < 6; k++) counts[k] = 0;
  s32 last = 0;
  for (char* it = beg; it != end; it += 4) {
    char* sp = *(char**)it;
    char* noun = 0;
    if (sp != 0) {
      noun = (char*)((void*(__thiscall*)(void*, u32))(*(void***)sp)[0xb8 / 4])(sp, 0x137e8e0);
    }
    u8 c = FUN_00c9fe40(noun, *(void**)(p + 0x11c));
    if (c != 0) {
      counts[*(s32*)(noun + 0xb20)]++;
    }
    last = ((s32(__thiscall*)(void*))(*(void***)noun)[0x4c / 4])(noun);
  }
  void* nm = SP_NounManager();
  char* city = (char*)FUN_00b25f40(nm, (u32)last);
  u8 anySet = 1;

  if (counts[2] != 0) {
    s32 id = ((s32(__thiscall*)(void*))(*(void***)param2)[0x4c / 4])(param2);
    if (id != -1 && last != id) {
      u32 strbuf[3];
      strbuf[0] = 0x01667bac;
      strbuf[1] = 0x01667bac;
      strbuf[2] = 0x01667bae;
      float price = (float)FUN_00bf06d0(param2);
      char cs[20];
      ((void(__thiscall*)(void*, u32, u32, const void*))FUN_006b5770)(
          cs, 0xbeb528cb, 0x6a56b8f, (const void*)0x01477de0);
      const void* txt = (const void*)((void*(__thiscall*)(void*, u32, u32))FUN_006b55c0)(cs, 0x37e95bb, 0);
      WStrAppend(strbuf, txt, txt);
      char out[40];
      out[0] = 0;
      out[1] = 0;
      WStrSprintf(out, (const void*)0x01477dd0, (void*)0);
      WStrAppend(strbuf, out, out);

      FUN_00b7d2e0(*(void**)(p + 0x68), (void*)strbuf[0]);
      void* nm2 = SP_NounManager();
      void* civ = FUN_00b25fb0(nm2);
      float money = (float)FUN_00bef6d0(civ);
      if (money < price) {
        u32 rgb[3]; rgb[0] = *(u32*)0x01485720; rgb[1] = 0; rgb[2] = 0;
        FUN_00b7c890(0x51b40a4, (u32)FUN_00458a40(rgb));
      }
      anySet = 0;
      ((void(__thiscall*)(void*))FUN_006b5240)(cs);
    }
  }

  for (char* it = beg; it != end; it += 4) {
    char* sp = *(char**)it;
    if (sp != 0) {
      ((void(__thiscall*)(void*))(*(void***)sp)[0xc0 / 4])(sp);
    }
  }
  FUN_00ad92d0(vec);
  return (u8)(anySet ? 0 : 1);
}

// ======================================================================
// 0x00ce8ab0 - SP::cCityInputStrategy::ShowMenu. this in ecx, two stack
// args; ret 8.
// ======================================================================

// @ 0x00ce8ab0
s32 __fastcall FUN_00ce8ab0(void* self, void* /*edx*/, void* a, s32 b) {
  char* p = (char*)self;
  char* param2 = (char*)a;

  if (p[0x135] != 0) return 0;

  if (param2 != 0) {
    ((void(__thiscall*)(void*, u32))(*(void***)param2)[0xc / 4])(param2, 0x01186577);
  }

  if (b == 6) {
    char* veh = 0;
    if (param2 != 0) {
      veh = (char*)((void*(__thiscall*)(void*, u32))(*(void***)param2)[0xc / 4])(param2, 0x1007ae63);
    }
    void* planet = FUN_01021260();
    if (veh != 0) {
      void* v = (void*)((void*(__thiscall*)(void*))(*(void***)(veh + 0x34))[0x98 / 4])(veh + 0x34);
      u8 scanned = FUN_00c73f10(planet, v);
      if (scanned == 0) {
        void* ctx = FUN_00ce6950((char*)planet + 0x13c);
        void* nm = SP_NounManager();
        void* ts = FUN_00f67d90(nm);
        void* r = FUN_00ba4e60((char*)ts + 0x11c0, ctx);
        void* v2 = (void*)((void*(__thiscall*)(void*))(*(void***)(veh + 0x34))[0x98 / 4])(veh + 0x34);
        u8* slot = (u8*)FUN_00ba4520((char*)r + 0x20, v2);
        *slot = 1;
        void* x = FUN_00ba57a0(veh, 1);
        FUN_00e30d20(FUN_00b3d4f0(x));
      }
      s32 id = ((s32(__thiscall*)(void*))(*(void***)veh)[0x4c / 4])(veh);
      void* planet2 = FUN_01021260();
      FUN_00c74550(planet2, &id);
    }
    u32 vec[3];
    vec[0] = 0; vec[1] = 0; vec[2] = 0;
    char* tc = (char*)SP_GetGameTerrainCursor();
    ((void(__thiscall*)(void*, void*))(*(void***)tc)[0x5c / 4])(tc, vec);
    ((void(__thiscall*)(void*))FUN_00b7d390)(*(void**)(p + 0x5c));
    p[0x110] = (char)veh;
    p[0x10c] = (char)veh;
    if (vec[0] != vec[1]) {
      FUN_00ce8370(p, 0, param2);
    }
    FUN_00ce8160(p, 0);
    void* gui = FUN_00b3d230();
    u8 c = FUN_00b5c980(gui);
    if (c != 0) {
      ((void(__thiscall*)(void*, u32, u32, const void*))FUN_006b5770)(
          vec, 0, 0, 0);
      FUN_00b7d2e0(*(void**)(p + 0x5c), (void*)0x01477ad0);
    }
    void* veh2 = *(void**)(p + 0x10c);
    s32 r2 = veh2 ? ((s32(__thiscall*)(void*))(*(void***)veh2)[0x84 / 4])(veh2) : 0;
    if (r2 != 0) r2 += 0x120;
    FUN_00b7cc60(*(void**)(p + 0x5c), (void*)r2, 1);
    FUN_00ad92d0(vec);
  } else if (b == 0xb) {
    if (param2 != 0) {
      char* obj = (char*)((void*(__thiscall*)(void*, u32))(*(void***)param2)[0xc / 4])(param2, 0x403df5f);
      if (obj != 0 && FUN_00ce87c0(p, 0, obj) != 0) {
        FUN_00b7cc60(*(void**)(p + 0x68), obj + 0x34, 1);
        return 0;
      }
    }
    void* audio = FUN_00a206f0();
    void* s = 0;
    if (audio != 0) {
      s = (void*)((void*(__thiscall*)(void*))(*(void***)audio)[0x20 / 4])(audio);
    }
    FUN_00435ed0(audio, s, 0x594303b7);
    return 1;
  }
  return 0;
}
