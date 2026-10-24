// Slice s01063a10 (batch gold6, worker 44). Region 0x01063a10-0x01064760.
// SP::cSPUIRares badge/feed panel cluster: DoMessage handler, feed refreshers,
// window wiring and enable/disable helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef          short s16;
typedef          char  s8;

// ---- external callees (address in comment) ------------------------------
void* __cdecl FUN_01002bd0();                          // 0x01002bd0 SP::SpaceGameGet
void* __cdecl FUN_00bfc5f0(void* self);                // 0x00bfc5f0 cGameData::SetGameDataOwner2
s32   __cdecl FUN_00fe4150(void* self, void* noun);    // 0x00fe4150 cSPBadgeManager::GetBadgeState
void* __cdecl FUN_00fe41c0(void* self, void* noun);    // 0x00fe41c0 cSPBadgeManager::GetReplacement
void* __cdecl FUN_00fe47a0(void* self, void* noun, void* a);  // 0x00fe47a0 GetBadgeDescription
void* __cdecl FUN_00fe4830(void* self, void* noun, void* a);  // 0x00fe4830 GetBadgeHintActionString
void* __cdecl FUN_00fe49a0(void* self, void* noun, void* a);  // 0x00fe49a0
void* __cdecl FUN_00fe5520(void* self, void* a, void* b);     // 0x00fe5520 GetBadgeImageKey
float __cdecl FUN_00fe6690(void* self, void* noun);    // 0x00fe6690
void* __cdecl FUN_00fe6800(void* self, void* noun, void* a);  // 0x00fe6800
u8    __cdecl FUN_00fe46a0(void* self, void* noun);    // 0x00fe46a0
u8    __cdecl FUN_00fe4180(void* self, void* noun);    // 0x00fe4180 DoInsertValue
void* __cdecl FUN_00a206f0();                          // 0x00a206f0 EA::Audio::GetSystemAT
void* __cdecl FUN_00e36650(void* self, u32 id, int b); // 0x00e36650 FindWindowByID (layout)
void  __cdecl FUN_00e369f0(void* self);                // 0x00e369f0
void  __cdecl FUN_00e365a0(void* self, void* a);       // 0x00e365a0
void  __cdecl FUN_00e36620(void* self);                // 0x00e36620
void* __cdecl FUN_00e0a780(void* self, u32 id, u32 n); // 0x00e0a780
void  __cdecl FUN_00e0a640(void* self);                // 0x00e0a640
void  __cdecl FUN_00e0a4c0(void* self, void* a);       // 0x00e0a4c0
void* __cdecl FUN_00e09c90(void* self, u32 idx);       // 0x00e09c90
void  __cdecl FUN_00e18a30(void* self);                // 0x00e18a30
void  __cdecl FUN_00e18860(void* self, void* a);       // 0x00e18860
void  __cdecl FUN_00e18890(void* self, void* a);       // 0x00e18890
void* __cdecl FUN_00e18600(void* self, void* a, void* b);  // 0x00e18600
void  __cdecl FUN_00e186d0(void* self, void* a, void* b, void* c, void* d);  // 0x00e186d0
void* __cdecl FUN_008105b0(void);                     // 0x008105b0 cSPUILayout::FindWindowByID (2-arg thiscall)
void* __cdecl FUN_008105b0x(void);                    // 0x008105b0 cSPUILayout::FindWindowByID (3-arg thiscall)
void* __cdecl FUN_005ca960(void* self);                // 0x005ca960 interface_cast
void* __cdecl FUN_00575ea0(void* self);                // 0x00575ea0 GetDefaultIconDrawable
void* __cdecl FUN_00b3d3f0();                          // 0x00b3d3f0 returns pointer in eax
void  __cdecl FUN_00e30a60(void* self, void* a);       // 0x00e30a60
void  __cdecl FUN_00e30e20(void* a, void* b, u32 c, void* d, void* e);  // 0x00e30e20
s32   __cdecl FUN_00febe90(void* self);                // 0x00febe90
void* __cdecl FUN_00feb9f0();                          // 0x00feb9f0 SP::GetMissionManager
void  __cdecl FUN_00fe3cc0(void* self, void* a);       // 0x00fe3cc0
void  __cdecl FUN_00809db0(void* a, void* b);          // 0x00809db0 UI::CalloutMessageBox
void* __cdecl FUN_00b3d300();                          // 0x00b3d300 SP::NounManager
void* __cdecl FUN_00f67d90(void* self);                // 0x00f67d90 cTerrainEditor::GetCurrentTerrainSphere
u8    __cdecl FUN_00c772c0(void* self, u32 id);        // 0x00c772c0
void  __cdecl FUN_00c77bf0(void* self, u32 id);        // 0x00c77bf0
void  __cdecl FUN_0067caf0(u32 a, u32 b, u32 c, void* d, void* e,
                           float f, float g, void* h, void* i, void* j);  // 0x0067caf0
void  __cdecl FUN_0067aaf0(u32 a, u32 b, u32 c, void* d, void* e,
                           float f, float g, void* h, void* i, void* j);  // 0x0067aaf0
void* __cdecl FUN_0067dcc0();                          // 0x0067dcc0 MessageServer
void* __cdecl FUN_00662960(void* self, void* a);       // 0x00662960 FeedList::Find
void  __cdecl FUN_00662c10(void* self, void* a);       // 0x00662c10
void  __cdecl FUN_00662920(void* self, int b);         // 0x00662920
void  __cdecl FUN_00663350(void* self, void* a);       // 0x00663350
void  __cdecl FUN_00663860(void* a, void* b, void* c, int d, void* e);  // 0x00663860
void  __cdecl FUN_00666630(void* self, void* a, void* b);  // 0x00666630 CFeed::Reserve
void  __cdecl FUN_006666c0(void* self, void* a);       // 0x006666c0 CItem::Refresh
void* __cdecl FUN_004558a0(void* a, void* b, u32 n);   // 0x004558a0 VectorInsertU32
void* __cdecl FUN_00f14120(void* self, void* fmt, ...); // 0x00f14120
void* __cdecl FUN_010634b0(void* self, void* a, float b);  // 0x010634b0
void  __cdecl FUN_010635d0(void* self);                // 0x010635d0
void  __cdecl FUN_01063740(void* self, void* a);       // 0x01063740
void* __cdecl FUN_00f473a0(u32 size, const char* name, int, int, int, int);  // operator new
void  __cdecl FUN_00f47380(void* p);                   // operator delete[]
void* __cdecl FUN_006b5770(void* self, u32 a, u32 b, void* c);  // 0x006b5770 cString ctor
void* __cdecl FUN_006b55c0(void* self);                // 0x006b55c0 cString::GetText
void* __cdecl FUN_006b5240(void* self);                // 0x006b5240 cString dtor
void* __cdecl FUN_0082a040(void* self);                // 0x0082a040 ScrollFrameVertical ctor
u8    __cdecl FUN_0082a140(void* self, int a, u32 b, u32 c);  // 0x0082a140 SFV::Create
float __cdecl FUN_0082a4e0(void* self);                // 0x0082a4e0 SFV::GetScrollOffset
void* __cdecl FUN_00663040(void* self);                // 0x00663040 cSPUIFeedList ctor
void  __cdecl FUN_00807cb0(void* a, void* b, int c);   // 0x00807cb0
void* __cdecl FUN_00435ed0(void* a, u32 b);            // 0x00435ed0 KillSetiEffects
void  __cdecl FUN_00571db0(void* a, void* b, void* c, void* d, void* e);  // 0x00571db0 RemoveHandler
void __fastcall FUN_01063a10(void* self, void* edx, void* arg1);

// ======================================================================
// 0x01063a10 - SP::cSPUIRares badge-detail refresh. thiscall, ret 4.
// ======================================================================

// @ 0x01063a10
void __fastcall FUN_01063a10(void* self, void* /*edx*/, void* arg1) {
  char* p = (char*)self;
  char* noun = (char*)arg1;

  char* game = (char*)FUN_01002bd0();
  char* badges = (char*)FUN_00bfc5f0(game);

  void* ki = (*(void* (__thiscall**)(void*))(*(void***)noun + 0x1c / 4))(noun);
  char* key = (char*)ki;
  char* key2 = key;
  char* used = key;
  if (FUN_00fe4150(badges, key) == 2) {
    if (FUN_00fe41c0(badges, key) != 0) {
      key2 = (char*)FUN_00fe41c0(badges, key);
      used = key2;
    }
  }

  void* audio1 = FUN_00a206f0();
  void* soundKey = 0;
  if (audio1 != 0) {
    soundKey = (*(void* (__thiscall**)(void*))(*(void***)audio1 + 0x20 / 4))(audio1);
  }

  void* audio = FUN_00a206f0();
  if (audio != 0) {
    (*(void(__thiscall**)(void*, u32))(*(void***)audio + 0x38 / 4))(audio, 0x3475365);
    (*(void(__thiscall**)(void*, u32, u32))(*(void***)audio + 0x40 / 4))(
        audio, 0x3475381, 0x8821b509);
    (*(void(__thiscall**)(void*, u32, void*))(*(void***)audio + 0x40 / 4))(
        audio, 0x3475385, soundKey);
    (*(void(__thiscall**)(void*))(*(void***)audio + 0x58 / 4))(audio);
  }

  void* s1 = (void*)0x01667bac;
  void* s2 = (void*)0x01667bac;
  void* s3 = (void*)0x01667bae;
  (void)s2; (void)s3;
  FUN_00fe47a0(badges, used, &s1);

  char* layout = p + 0x128;
  void* win = FUN_00e36650(layout, 0x51a37b8, 1);
  char* w = (char*)win;
  (*(void(__thiscall**)(void*, void*))(*(void***)w + 0x80 / 4))(w, s1);

  float* r = (float*)(*(void* (__thiscall**)(void*))(*(void***)w + 0x38 / 4))(w);
  float h1 = r[2] - r[0];
  void* txt = (*(void* (__thiscall**)(void*, u32))(*(void***)w + 0xc / 4))(w, 0xf15f4bd);
  (*(void(__thiscall**)(void*, int))(*(void***)txt + 0x14 / 4))(txt, 0);

  r = (float*)(*(void* (__thiscall**)(void*))(*(void***)w + 0x38 / 4))(w);
  float cur = r[2] - r[0];
  float* lim = (float*)(p + 0x188);
  float use = (*lim > cur) ? *lim : cur;
  (*(void(__thiscall**)(void*, float, float))(*(void***)w + 0x74 / 4))(
      w, use, r[3] - r[1]);

  void* win2 = FUN_00e36650(layout, 0x5fd4ce0, 1);
  char* w2 = (char*)win2;
  float* r2 = (float*)(*(void* (__thiscall**)(void*))(*(void***)w2 + 0x38 / 4))(w2);
  float h2 = (r2[2] - r2[0]) + h1 - cur;
  (*(void(__thiscall**)(void*, float, float))(*(void***)w2 + 0x74 / 4))(
      w2, h2, r2[3] - r2[1]);

  FUN_00fe4830(badges, key, &s1);
  void* win3 = FUN_00e36650(layout, 0x51a37b9, 1);
  char* w3 = (char*)win3;
  (*(void(__thiscall**)(void*, void*))(*(void***)w3 + 0x80 / 4))(w3, s1);
  void* txt3 = (*(void* (__thiscall**)(void*, u32))(*(void***)w3 + 0xc / 4))(w3, 0xf15f4bd);
  (*(void(__thiscall**)(void*, int))(*(void***)txt3 + 0x14 / 4))(txt3, 1);

  FUN_00fe49a0(badges, key, &s1);
  void* win4 = FUN_00e36650(layout, 0x657e618, 1);
  char* w4 = (char*)win4;
  (*(void(__thiscall**)(void*, void*))(*(void***)w4 + 0x80 / 4))(w4, s1);

  FUN_00fe6800(badges, key, &s1);
  void* win5 = FUN_00e36650(layout, 0x5fca1a8, 1);
  char* w5 = (char*)win5;
  (*(void(__thiscall**)(void*, void*))(*(void***)w5 + 0x80 / 4))(w5, s1);

  void* win6 = FUN_00e36650(layout, 0x5fca190, 1);
  char* w6 = (char*)win6;
  void* sub = (*(void* (__thiscall**)(void*))(*(void***)w6 + 0x10 / 4))(w6);
  float* r6 = (float*)(*(void* (__thiscall**)(void*))(*(void***)sub + 0x38 / 4))(sub);
  float h6 = r6[2] - r6[0];

  float ratio = FUN_00fe6690(badges, key);
  u8 flag = FUN_00fe4180(badges, key);
  u8 flag2 = FUN_00fe46a0(badges, key);
  int enabled;
  if ((0.0f < ratio && ratio < 1.0f) || (flag != 0 && flag2 == 0)) {
    enabled = 1;
  } else {
    enabled = 0;
  }

  r6 = (float*)(*(void* (__thiscall**)(void*))(*(void***)w6 + 0x38 / 4))(w6);
  (*(void(__thiscall**)(void*, float, float))(*(void***)w6 + 0x74 / 4))(
      w6, (float)enabled * h6, r6[3] - r6[1]);

  void* win7 = FUN_00e36650(layout, 0x5fca1f0, 1);
  FUN_010634b0(win7, used, ratio);
  FUN_00e369f0(layout);
  FUN_00e365a0(layout, arg1);
}

// ======================================================================
// 0x01063dc0 - SP::cSPUIRares::DoMessage. thiscall, ret 8.
// ======================================================================

// @ 0x01063dc0
u32 __fastcall FUN_01063dc0(void* self, void* /*edx*/, void* msg, void* arg2) {
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

// ======================================================================
// 0x01063f70 - SP::cSPUIRares::RefreshWindows. thiscall.
// ======================================================================

// @ 0x01063f70
void __fastcall FUN_01063f70(void* self, void* /*edx*/) {
  char* p = (char*)self;
  if (*(s32*)(*(char**)(p + 0x1a8) + 0x17c) == 0x62146e6d) {
    void* w1 = ((void* (__thiscall*)(void*, u32, int))FUN_008105b0)(
        *(void**)(p + 0x18), 0x5fc9978, 1);
    (*(void(__thiscall**)(void*, int, int))(*(void***)w1 + 0x7c / 4))(w1, 1, 0);
    void* w2 = ((void* (__thiscall*)(void*, u32, int))FUN_008105b0)(
        *(void**)(p + 0x18), 0x5f00928, 1);
    (*(void(__thiscall**)(void*, int, int))(*(void***)w2 + 0x7c / 4))(w2, 1, 1);
    return;
  }
  u32 local_8;
  void* local_4 = 0;
  ((void(__thiscall*)(void*, void**, u32*))FUN_00666630)(
      *(void**)(p + 0x1a8), &local_4, &local_8);
  if (local_4 == (void*)1) {
    ((void(__thiscall*)(void*, void*))FUN_01063740)(p, *(void**)local_8);
  }
}

// ======================================================================
// 0x01064000 - SP::cSPUIRares::OnMessage. thiscall, ret 8.
// ======================================================================

// @ 0x01064000
u8 __fastcall FUN_01064000(void* self, void* /*edx*/, s32 tag, void* arg2) {
  char* p = (char*)self;
  if (tag == (s32)0xb3d53f95) {
    char* p19c = *(char**)(p + 0x19c);
    void* noun = *(void**)(p19c + 0x17c);
    char* mgr = (char*)FUN_00b3d3f0();
    FUN_00e30a60(*(void**)(mgr + 0x5c), noun);
    char* nd = *(char**)((char*)arg2 + 0x10);
    char* old = *(char**)(p + 0x19c);
    if (nd != old) {
      if (nd != 0) {
        (*(void(__thiscall**)(char*))(*(void***)nd + 0))(nd);
      }
      *(char**)(p + 0x19c) = nd;
      if (old != 0) {
        (*(void(__thiscall**)(char*))(*(void***)old + 1))(old);
      }
    }
    FUN_01063f70(p - 0xc, 0);
    return 1;
  }
  return (u8)(u32)FUN_00e18600(p, (void*)tag, arg2);
}

// ======================================================================
// 0x01064080 - SP::cSPUIRares::RefreshFeed. thiscall.
// ======================================================================

// @ 0x01064080
// SP::cSPUIRares::RefreshFeed - rebuild the badge feed list from the player
// tribe's badge inventory, wiring each row's icon/tooltip/visibility.
void __fastcall FUN_01064080(void* self, void* /*edx*/) {
  char* p = (char*)self;
  char* game = (char*)FUN_01002bd0();
  char* tribe = (char*)FUN_00bfc5f0(game);

  char* feed = (char*)((s32(__thiscall*)(void*, u32))FUN_00662960)(
      *(void**)(p + 0x1a4), 0x62146e6d);
  if (feed == 0) return;

  // Feed source: count + begin pointer of the tribe's badge-noun list.
  s32 cnt;
  u32* base;
  ((void(__thiscall*)(void*, s32*, u32**))FUN_00666630)(feed, &cnt, &base);

  // Selected nouns accumulate into a local eastl-style vector.
  u32* sel = 0;        // begin                 [esp+0x3c]
  u32* selEnd = 0;     // end                   [esp+0x40]
  u32* selCap = 0;     // allocation end        [esp+0x44]
  s32 kept = 0;        // count of active rows  [esp+0x2c]
  s32 i = 0;           // loop counter          [esp+0x20]
  if (cnt > 0) {
    s32 off = 0;
    do {
      u32 noun = *(u32*)((char*)base + off);
      s32 st = FUN_00fe4150(tribe, (void*)noun);
      u32* cur = sel;
      switch (st) {
        case 0:
        case 1:
          ++kept;
          if (FUN_00fe46a0(tribe, (void*)noun) == 0) break;
          if (cur < selCap) {
            sel = cur + 1;
            if (cur != 0) *cur = noun;
          } else {
            FUN_004558a0(&selEnd, &noun, 4);
            sel = selEnd;
          }
          break;
        case 2:
        case 3:
          if (cur < selCap) {
            sel = cur + 1;
            if (cur != 0) *cur = noun;
          } else {
            FUN_004558a0(&selEnd, &noun, 4);
            sel = selEnd;
          }
          break;
      }
      off += 0xc;
      ++i;
    } while (i < cnt);
  }

  u32 nsel = (u32)(sel - selEnd >= 0 ? sel - selEnd : 0);
  s32 nrows = ((char*)sel - (char*)selEnd) >> 2;
  (void)nsel;
  u8 anyInv = 0;
  if (FUN_00e0a780(p + 0x44, 0x15b8f70, nsel) != 0) {
    u32 defIcon = (u32)(u32*)FUN_00575ea0(tribe);
    for (s32 k = 0; k < nrows; ++k) {
      u32 noun = selEnd[k];
      void* repl = FUN_00fe41c0(tribe, (void*)noun);
      u8 isDefault = (noun == defIcon) ? 1 : 0;
      s32 st = FUN_00fe4150(tribe, (void*)noun);
      u8 isState3 = (st == 3) ? 1 : 0;
      float ratio;
      if (isState3) ratio = 0.0f;
      else ratio = FUN_00fe6690(tribe, (void*)noun);
      u8 owned = FUN_00fe4180(tribe, (void*)repl);
      u8 hidden2 = FUN_00fe46a0(tribe, (void*)noun);

      u8 show;
      if ((0.0f < ratio && ratio < 1.0f) || (owned != 0 && hidden2 == 0)) show = 1;
      else show = 0;

      u32 useRep;
      if (owned == 0 || hidden2 != 0) useRep = noun;
      else useRep = (u32)repl;

      // If the noun is present in the tree view's noun set, re-apply
      // default rows and raise an inventory message.
      char* tvRoot = *(char**)(tribe + 0x34);
      if (tvRoot != tribe + 0x34) {
        char* it = tvRoot;
        while (*(u32*)(it + 8) != useRep) {
          it = *(char**)it;
          if (it == tribe + 0x34) break;
        }
        if (it != tribe + 0x34) {
          u32 key = *(u32*)(feed + 0x14);
          anyInv = 1;
          char* mgr = (char*)FUN_00b3d3f0();
          FUN_00e30e20(mgr, (void*)noun, key, (void*)0xf45f7d78, 0);
        }
      }

      void* layout = FUN_00e09c90(p + 0x44, (u32)k);
      char* w = (char*)((void* (__thiscall*)(void*, u32, int))FUN_008105b0)(
          layout, 0x5ee04c0, 1);
      (*(void(__thiscall**)(char*, u32))(*(void***)w + 0x50 / 4))(w, noun);
      (*(void(__thiscall**)(char*, u32))(*(void***)w + 0x54 / 4))(
          w, isState3 ? 0x51aff90 : 0);
      (*(void(__thiscall**)(char*, int, int))(*(void***)w + 0x7c / 4))(
          w, 2, (owned == 0 || isState3) ? 0 : 1);
      char* icon = (char*)(*(void* (__thiscall**)(char*, u32))(*(void***)w + 0xc / 4))(
          w, 0x8ed27e7a);
      (*(void(__thiscall**)(char*, int, s32))(*(void***)icon + 0x28 / 4))(
          icon, 4, kept);
      const void* imgKey;
      if (isState3) imgKey = (const void*)0x15b8f94;
      else imgKey = (const void*)(u32)FUN_00fe5520(tribe, (void*)useRep, 0);
      FUN_00807cb0(w, (void*)imgKey, 0);

      char* w2 = (char*)((void* (__thiscall*)(void*, u32, int))FUN_008105b0)(
          layout, 0x63a8048, 1);
      if (w2 != 0) {
        (*(void(__thiscall**)(char*, u32))(*(void***)w2 + 0x5c / 4))(
            w2, 0xffffff00);
      }

      char* w3 = (char*)((void* (__thiscall*)(void*, u32, int))FUN_008105b0)(
          layout, 0x5fca190, 1);
      char* sub = (char*)(*(void* (__thiscall**)(char*))(*(void***)w3 + 0x10 / 4))(w3);
      if (isDefault) {
        float* r = (float*)(*(void* (__thiscall**)(char*))(*(void***)w3 + 0x38 / 4))(w3);
        float width = r[2] - r[0];
        float* r2 = (float*)(*(void* (__thiscall**)(char*))(*(void***)w3 + 0x38 / 4))(w3);
        (*(void(__thiscall**)(char*, float, float))(*(void***)w3 + 0x74 / 4))(
            w3, width * ratio, r2[3] - r2[1]);
      }
      (*(void(__thiscall**)(char*, int, int))(*(void***)sub + 0x7c / 4))(
          sub, 1, isDefault ? 1 : 0);

      char* w4 = (char*)((void* (__thiscall*)(void*, u32, int))FUN_008105b0)(
          layout, 0x5fca1f0, 1);
      if (isState3) {
        (*(void(__thiscall**)(char*, int, int))(*(void***)w4 + 0x7c / 4))(w4, 1, 0);
      } else {
        FUN_010634b0(w4, (void*)useRep, (float)show);
      }
    }
  }

  // Publish the feed pointer and refresh the list item's text.
  if (*(void**)(p + 0x1a8) == 0 && feed != *(char**)(p + 0x1a8)) {
    (*(void(__thiscall**)(char*))(*(void***)feed + 0))(feed);
    char* old = *(char**)(p + 0x1a8);
    *(char**)(p + 0x1a8) = feed;
    if (old != 0) {
      (*(void(__thiscall**)(char*))(*(void***)old + 1))(old);
    }
  }
  {
    u16 buf[64];
    buf[0] = 0;
    FUN_00f14120(buf, (void*)0x146e428, kept, cnt);
    FUN_006666c0(feed, buf);
    if (anyInv) {
      char* icon = *(char**)(feed + 0xa0);
      (*(void(__thiscall**)(char*, u32))(*(void***)icon + 0x50 / 4))(
          icon, *(u32*)(feed + 0x17c));
      char* mgr = (char*)FUN_00b3d3f0();
      FUN_00e30e20(mgr, (void*)*(u32*)(feed + 0x17c),
                   *(u32*)(p + 0x14), (void*)0x2c765c39, 0);
    }
  }
  (void)sel; (void)selCap;
}

// ======================================================================
// 0x01064560 - SP::cSPUIRares::Show. thiscall, ret 4.
// ======================================================================

// @ 0x01064560
void __fastcall FUN_01064560(void* self, void* /*edx*/, void* arg1) {
  char* p = (char*)self;
  if (*(u8*)(p + 0x40) != 0) return;

  ((void(__thiscall*)(void*, void*))FUN_00e18860)(p, arg1);
  u32 str[3];
  ((void(__thiscall*)(void*, u32, u32, void*))FUN_006b5770)(str, 0xf5e156f8, 0x6038551, 0);
  void* txt = ((void* (__thiscall*)(void*))FUN_006b55c0)(str);
  ((void(__thiscall*)(void*, void*))FUN_00e18890)(p, txt);

  *(u8*)(p + 0x40) = 1;
  ((void(__thiscall*)(void*))FUN_010635d0)(p);
  ((void(__thiscall*)(void*))FUN_01064080)(p);
  ((void(__thiscall*)(void*, void*))FUN_00662c10)(*(void**)(p + 0x1a4), *(void**)(p + 0x1a8));
  ((void(__thiscall*)(void*))FUN_01063f70)(p);
  ((void(__thiscall*)(void*, int))FUN_00662920)(*(void**)(p + 0x1a4), 1);

  char* h = p + 0xc;
  void* srv = FUN_0067dcc0();
  *(void**)(p + 0x190) = srv;
  *(void**)(p + 0x194) = h;
  *(u32*)(p + 0x198) = 0x01400244;
  *(u32*)(p + 0x19c) = 1;
  *(u32*)(p + 0x1a0) = 0;
  if (srv != 0 && h != 0) {
    (*(void(__thiscall**)(void*, char*, u32))(*(void***)srv + 0x24 / 4))(
        srv, h, 0xb3d53f95);
  }

  char* sphere = (char*)((void* (__thiscall*)(void*))FUN_00f67d90)(FUN_00b3d300());
  if (sphere != 0) {
    if (((u8 (__thiscall*)(void*, u32))FUN_00c772c0)(sphere, 0x65e5039) == 0) {
      ((void(__thiscall*)(void*, u32))FUN_00c77bf0)(sphere, 0x65e5039);
      FUN_0067caf0(0x38536a10, 0x00b1b104, 0x3629f036, (void*)0x015b8fa0, 0,
                   -1.0f, -1.0f, 0, 0, 0);
      FUN_0067aaf0(0x38536a10, 0x00b1b104, 0x3629f036, (void*)0x015b8fa0, 0,
                   -1.0f, -1.0f, 0, 0, 0);
    }
  }
  ((void(__thiscall*)(void*))FUN_006b5240)(str);
}

// ======================================================================
// 0x010646f0 - SP::cSPUIRares::Hide. thiscall.
// ======================================================================

// @ 0x010646f0
void __fastcall FUN_010646f0(void* self, void* /*edx*/) {
  char* p = (char*)self;
  if (*(u8*)(p + 0x40) == 0) return;

  void* handler = *(void**)(p + 0xbc);
  if (handler != 0) {
    *(void**)(p + 0xbc) = 0;
    FUN_00571db0(handler, *(void**)(p + 0xc0), *(void**)(p + 0xc4),
                 *(void**)(p + 0xc8), *(void**)(p + 0xcc));
  }
  ((void(__thiscall*)(void*, int))FUN_00662920)(*(void**)(p + 0xd0), 0);
  ((void(__thiscall*)(void*))FUN_00e0a640)(p + 0x48);
  *(u8*)(p + 0x40) = 0;
  ((void(__thiscall*)(void*))FUN_00e18a30)(p);
}

// ======================================================================
// 0x01064760 - SP::cSPUIRares::OnCreate. thiscall, ret 16.
// ======================================================================

// @ 0x01064760
void __fastcall FUN_01064760(void* self, void* /*edx*/, void* a2, void* a3,
                             void* a4, void* a5) {
  char* p = (char*)self;
  ((void(__thiscall*)(void*, void*, void*, void*, void*))FUN_00e186d0)(
      p, a2, a3, a4, a5);
  *(u8*)(p + 0x40) = 0;
  *(u32*)(p + 0x44) = 0;

  u32 local_10 = 0;
  float local_c = 0.0f;
  u32 local_8 = 0;
  (void)local_c; (void)local_8;

  void* w = ((void* (__thiscall*)(void*, u32, int, void*))FUN_008105b0)(
      *(void**)(p + 0x18), 0x5f00928, 1, &local_10);
  ((void(__thiscall*)(void*, void*))FUN_00e0a4c0)(p + 0x48, w);

  char* sfv = (char*)FUN_00f473a0(0x48, "UI/cSPUIScrollFrameVertical", 0, 0, 0, 0);
  sfv = sfv ? (char*)FUN_0082a040(sfv) : 0;
  char* oldS = *(char**)(p + 0xb8);
  if (sfv != oldS) {
    if (sfv != 0) (*(void(__thiscall**)(char*))(*(void***)sfv + 0))(sfv);
    *(char**)(p + 0xb8) = sfv;
    if (oldS != 0) (*(void(__thiscall**)(char*))(*(void***)oldS + 1))(oldS);
  }

  ((u8 (__thiscall*)(void*, u32, int, int))FUN_0082a140)(
      *(void**)(p + 0xb8), 0xaef7d6ba, 1, 0);
  void* win = ((void* (__thiscall*)(void*, u32, int, void*))FUN_008105b0)(
      *(void**)(p + 0x18), 0x51a37b9, 1, &local_10);
  char* wc = (char*)win;
  if (wc != 0) {
    (*(void(__thiscall**)(char*))(*(void***)wc + 0))(wc);
    char* sfv2 = *(char**)(p + 0xb8);
    char* own = *(char**)(sfv2 + 0x10);
    char* other = *(char**)(sfv2 + 0x18);
    char* sub = (char*)(*(void* (__thiscall**)(char*))(*(void***)wc + 0x10 / 4))(wc);
    (*(void(__thiscall**)(char*, char*))(*(void***)sub + 0xd8 / 4))(sub, own);
    float* r = (float*)(*(void* (__thiscall**)(char*))(*(void***)wc + 0x38 / 4))(wc);
    local_10 = *(u32*)&r[0];
    local_c = r[2];
    local_8 = *(u32*)&r[3];
    float off = FUN_0082a4e0(*(void**)(p + 0xb8));
    local_c += off;
    (*(void(__thiscall**)(char*, void*))(*(void***)own + 0x6c / 4))(own, &local_10);
    (*(void(__thiscall**)(char*, char*))(*(void***)sub + 0xdc / 4))(sub, wc);
    (*(void(__thiscall**)(char*, char*))(*(void***)(char*)a2 + 0xd8 / 4))((char*)a2, wc);
    (*(void(__thiscall**)(char*, int, int))(*(void***)wc + 0x70 / 4))(wc, 0, 0);
    (void)other;
  }

  char* fl = (char*)FUN_00f473a0(0x6c, "UI/cSPUIFeedList", 0, 0, 0, 0);
  fl = fl ? (char*)FUN_00663040(fl) : 0;
  char* oldF = *(char**)(p + 0xd0);
  if (fl != oldF) {
    if (fl != 0) (*(void(__thiscall**)(char*))(*(void***)fl + 0))(fl);
    *(char**)(p + 0xd0) = fl;
    if (oldF != 0) (*(void(__thiscall**)(char*))(*(void***)oldF + 1))(oldF);
  }

  char* fl2 = *(char**)(p + 0xd0);
  void* ww = ((void* (__thiscall*)(void*, u32, int, void*))FUN_008105b0)(
      *(void**)(p + 0x18), 0x5f00660, 1, &local_10);
  ((void(__thiscall*)(void*, u32, int, int))FUN_00663860)(fl2, 0xee896903, 1, 0);
  (void)ww;
  ((void(__thiscall*)(void*, int))FUN_00663350)(fl2, 0);
  ((void(__thiscall*)(void*, int))FUN_00662920)(fl2, 0);
  if (wc != 0) {
    (*(void(__thiscall**)(char*))(*(void***)wc + 1))(wc);
  }
}
