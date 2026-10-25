// src/game/SPGonzago/SPCityCivGameMenus.cpp -- migrated from slice(s) s00ce8160 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCityCivGameMenus.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00ce8160 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
typedef          int   s32;
void* __cdecl SP_NounManager();                      // 0x00b3d300 SP::NounManager
void* __cdecl SP_GetGameTerrainCursor();             // 0x00b30d70
s32   __cdecl FUN_00458a40(void* rgb);               // 0x00458a40 SP::ColorRGBToU32
void  __cdecl FUN_00b7d2e0(void* self, void* str);   // 0x00b7d2e0
void  __cdecl FUN_00b7c890(u32 id, u32 color);       // 0x00b7c890
void* __cdecl FUN_00bd9bf0(void* self);              // 0x00bd9bf0 SP::cCity::GetCivilization
s32   __cdecl FUN_00b1f9d0(void* self);              // 0x00b1f9d0 GetPlayerEmpireOrMinus1
void* __cdecl FUN_00b25fb0(void* self);              // 0x00b25fb0 GetPlayerCivilization
u8    __cdecl FUN_00bf19c0(void* self, void* a);     // 0x00bf19c0
u8    __cdecl FUN_00bdb200(void* self, s32 a);       // 0x00bdb200
u8    __cdecl FUN_00bd7fc0(void* self, s32 a);       // 0x00bd7fc0
s32   __cdecl FUN_00bf01f0(void* self, s32 a, s32 b);// 0x00bf01f0 count_specialty_cities
u8    __cdecl FUN_00bd7e20(void* self);              // 0x00bd7e20
s32   __cdecl FUN_00bdb280(void* self, s32 a);       // 0x00bdb280
u8    __cdecl FUN_00ca8340(void* self, void* a);     // 0x00ca8340
void* __cdecl FUN_00fa0e00(void* self);              // 0x00fa0e00 cCity::GetPositionPtr
void  __cdecl FUN_00ad92d0(void* self);              // 0x00ad92d0 vector dtor
void* __cdecl FUN_006b5770(void* self, u32 a, u32 b, const void* wstr); // cString::cString
void* __cdecl FUN_006b55c0(void* self, u32 a, u32 b); // cString::GetText / IsMaxValue
void* __cdecl FUN_006b5240(void* self);               // cString::~cString / c_str
void  __fastcall FUN_00ce8160(void* self, void* edx);
u8    __fastcall FUN_00ce8370(void* self, void* edx, void* arg);
// ---- items of slice s00ce8160 end

// @ 0x00ce8160
void __fastcall FUN_00ce8160(void* self, void* /*edx*/)
{
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

// @ 0x00ce8370
u8 __fastcall FUN_00ce8370(void* self, void* /*edx*/, void* arg)
{
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
