// src/game/SPGonzago/SPUIBadges.cpp -- migrated from slice(s) s01063a10 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIBadges.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s01063a10 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef          int   s32;
void* __cdecl FUN_01002bd0();                          // 0x01002bd0 SP::SpaceGameGet
void* __cdecl FUN_00bfc5f0(void* self);                // 0x00bfc5f0 cGameData::SetGameDataOwner2
void* __cdecl FUN_00a206f0();                          // 0x00a206f0 EA::Audio::GetSystemAT
void  __cdecl FUN_00e36620(void* self);                // 0x00e36620
void* __cdecl FUN_008105b0(void);                     // 0x008105b0 cSPUILayout::FindWindowByID (2-arg thiscall)
void* __cdecl FUN_005ca960(void* self);                // 0x005ca960 interface_cast
void* __cdecl FUN_00575ea0(void* self);                // 0x00575ea0 GetDefaultIconDrawable
void* __cdecl FUN_00b3d3f0();                          // 0x00b3d3f0 returns pointer in eax
void  __cdecl FUN_00e30a60(void* self, void* a);       // 0x00e30a60
s32   __cdecl FUN_00febe90(void* self);                // 0x00febe90
void* __cdecl FUN_00feb9f0();                          // 0x00feb9f0 SP::GetMissionManager
void  __cdecl FUN_00fe3cc0(void* self, void* a);       // 0x00fe3cc0
void  __cdecl FUN_00809db0(void* a, void* b);          // 0x00809db0 UI::CalloutMessageBox
void* __cdecl FUN_00435ed0(void* a, u32 b);            // 0x00435ed0 KillSetiEffects
void __fastcall FUN_01063a10(void* self, void* edx, void* arg1);
// ---- items of slice s01063a10 end

// @ 0x01063dc0
u32 __fastcall FUN_01063dc0(void* self, void* /*edx*/, void* msg, void* arg2)
{
  char* p = (char*)self;
  char* m = (char*)msg;
  (void)arg2;

  void* tag = *(void**)(m + 8);
  if (tag == (void*)0x287259f6) {
    void* kind = (*(void* (__thiscall**)(void*))(*(void***)*(void**)m + 0x20 / 4))(*(void**)m);
    void* id = (*(void* (__thiscall**)(void*))(*(void***)*(void**)m + 0x1c / 4))(*(void**)m);
    if (kind != (void*)0x51aff90) {
      return 0;
    }
    void* audio = FUN_00a206f0();
    if (audio != 0) {
      (*(void(__thiscall**)(void*))(*(void***)audio + 0x20 / 4))(audio);
    }
    FUN_00435ed0(audio, 0x806318da);
    char* game = (char*)FUN_01002bd0();
    char* tribe = (char*)FUN_00bfc5f0(game);
    if (tribe == 0) {
      return 0;
    }
    if (*(void**)(m + 0x14) == 0) {
      FUN_00fe3cc0(tribe, 0);
      return 0;
    }
    void* mm = FUN_00feb9f0();
    s32 lvl = FUN_00febe90(mm);
    if (lvl < 3) {
      void* icon = FUN_00575ea0(tribe);
      if (icon != 0) {
        void* w = ((void* (__thiscall*)(void*, u32, int))FUN_008105b0)(*(void**)(p + 0x10), (u32)icon, 1);
        void* btn = FUN_005ca960(w);
        if (btn != 0) {
          (*(void(__thiscall**)(void*, int, int))(*(void***)btn + 0x28 / 4))(btn, 4, 0);
        }
      }
      FUN_00fe3cc0(tribe, id);
      return 0;
    }
    {
      u32 box[3];
      box[0] = 0x29bcd888;
      box[1] = 0x00b1b104;
      box[2] = 0xf5f6fde8;
      FUN_00809db0(0, box);
    }
    void* w = FUN_005ca960(*(void**)m);
    if (w != 0) {
      (*(void(__thiscall**)(void*, int, int))(*(void***)w + 0x28 / 4))(w, 4, 0);
    }
    return 0;
  }
  if (tag == (void*)0x1c) {
    FUN_00e36620(p + 0x120);
    return 0;
  }
  if (tag == (void*)0x1b) {
    void* kind = (*(void* (__thiscall**)(void*))(*(void***)*(void**)m + 0x20 / 4))(*(void**)m);
    void* id = (*(void* (__thiscall**)(void*))(*(void***)*(void**)m + 0x1c / 4))(*(void**)m);
    if (kind == (void*)0x51aff90 || kind == (void*)0x5fce2d8) {
      char* obj = (char*)FUN_00b3d3f0();
      FUN_00e30a60(*(void**)(obj + 0x5c), id);
      FUN_01063a10(p - 8, 0, *(void**)m);
    }
  }
  return 0;
}
