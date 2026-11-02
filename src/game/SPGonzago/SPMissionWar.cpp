// src/game/SPGonzago/SPMissionWar.cpp -- migrated from slice(s) s00c62880 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionWar.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPMission.h"

// ---- items of slice s00c62880 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl WStr_Format(void*, const wchar_t*, ...);          // 0x41e050
static inline void** Vt(void* p){ return *(void***)p; }
struct MissionBase {
  void BaseCtor();       // 0xc48e90 cGenericPressureEvent ctor
  void BaseDtor();       // 0xc47680 cSPMission dtor
  bool Init();           // 0xc4ad50
  bool IsActive();       // 0xc44c80
  void GetText(int key, void* out);   // 0xc487d0
  void TriggerUIUpdate();             // 0xc47d80
  void FUN_00c472e0();               // 0xc472e0
  void FUN_00c471c0();               // 0xc471c0
  void SetSerializer();              // 0xc2e4e0
};
struct WString12 { void* mBegin; void* mEnd; void* mCap; };
struct MissionWar {
  uint8_t pad00[0x78];
  uint32_t mKey78;                 // +0x78
  uint8_t pad7c[0x14];
  void* mEmpire90;                 // +0x90
  uint8_t pad94[0xb8];
  WString12 mCachedText;           // +0x14c
  uint8_t pad158[0x98];
  int mState;                      // +0x1f0
  int mProgress;                   // +0x1f4
  int mProgressMax;                // +0x1f8
  uint8_t mFlag;                   // +0x1fc
  uint8_t pad1fd[0x13];
};
struct TextOpts {
  int mField00;                    // +0x00
  int mField04;                    // +0x04
  int mField08;                    // +0x08
  int mField0c;                    // +0x0c
  int mField10;                    // +0x10
  int mField14;                    // +0x14
  int mField18;                    // +0x18
  int mField1c;                    // +0x1c
  int mField20;                    // +0x20
  int mField24;                    // +0x24
  int mField28;                    // +0x28
  int mField2c;                    // +0x2c
  int mField30;                    // +0x30
  int mField34;                    // +0x34
  int mField38;                    // +0x38
  int mField3c;                    // +0x3c
  int mField40;                    // +0x40
};
// ---- items of slice s00c62880 end

// @ 0x00c62ed0
void __fastcall M_GetUIMedium(void* self, int _e, void* out)
{
  if (!((MissionBase*)self)->IsActive()) return;
  switch (*(int*)((char*)self + 0x1f0)) {
    case 0: ((MissionBase*)self)->GetText(0xd79a86a8, out); return;
    case 1: ((MissionBase*)self)->GetText(0x81128ae1, out); return;
    case 2: ((MissionBase*)self)->GetText(0xbb0eec72, out); return;
    case 3: ((MissionBase*)self)->GetText(0xa6f2b74a, out); return;
  }
}

// @ 0x00c62f60
void __fastcall M_GetUILong(void* self, int _e, void* out)
{
  if (!((MissionBase*)self)->IsActive()) return;
  switch (*(int*)((char*)self + 0x1f0)) {
    case 0: ((MissionBase*)self)->GetText(0x247d8d51, out); return;
    case 1: ((MissionBase*)self)->GetText(0xba93258e, out); return;
    case 2: ((MissionBase*)self)->GetText(0xd22abb35, out); return;
    case 3: ((MissionBase*)self)->GetText(0x1ec90679, out); return;
  }
}

// @ 0x00c62ff0
float __fastcall M_C62ff0(void* self, int _e, int a, void* b)
{
  MissionWar* w = (MissionWar*)self;

  float score = ((float(__stdcall*)(int, void*))0x00c44d00)(a, b);
  if (!(score > 0.0f)) return score;

  void* obj = ((void*(__thiscall*)(void*))0x00b8de30)((void*)a);
  void* avatar = ((void*(__thiscall*)(void*))0x00b1fdb0)(obj);
  void* starMgr = ((void*(__cdecl*)())0x00b3d2a0)();
  void* empire = ((void*(__thiscall*)(void*, void*))0x00ba9370)(starMgr, avatar);

  if (!empire || empire == w->mEmpire90 || empire == ((void*(__cdecl*)())0x01021300)())
    return 0.0f;

  void* relMgr = ((void*(__cdecl*)())0x00b3d2c0)();
  void* owner = ((void*(__thiscall*)(void*))0x00c451e0)(self);
  float rel = ((float(__thiscall*)(void*, int, int, int))0x00d00a10)(
      relMgr, *(int*)((char*)empire + 0x84), *(int*)((char*)owner + 0x84), 0);
  if (rel > 0.0f) return 0.0f;

  if (w->mKey78 == 0xb19b8de3 &&
      ((int(__thiscall*)(void*))0x00c317a0)(empire) > 0)
    return 0.0f;

  obj = ((void*(__thiscall*)(void*))0x00b8de30)((void*)a);
  void* cities = ((void*(__thiscall*)(void*))0x00bba790)(obj);
  int count = 0;
  for (void** p = *(void***)cities; p != *(void***)((char*)cities + 4); p++) {
    if (((char(__cdecl*)(void*, void*, int))0x00c70150)(*p, empire, 0))
      count++;
  }
  if (count > 1) return 0.0f;

  if (w->mFlag) {
    void* global = ((void*(__cdecl*)())0x00b3d430)();
    char flag = ((char(__thiscall*)(void*, void*))0x00bbe5c0)(global, (void*)a);
    int result = 0;
    if (flag) {
      int home = ((int(__thiscall*)(void*))0x00c31730)(empire);
      if (home != a) result = 1;
    }
    return (float)result;
  }
  return 1.0f;
}

// @ 0x00c63130
void __fastcall M_FailureCityDestroyed(void* self, int _e)
{
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
void __fastcall M_OnTimerExpire(void* self, int _e)
{
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
void __fastcall M_ReturnForRewards(void* self, int _e)
{
  if (*(int*)((char*)self + 0x1f0) != 0) return;
  (*(void(__thiscall*)(void*))((*(void***)self)[0x6c/4]))(self);
  if (*(int*)((char*)self + 0x1f0) != 1) {
    *(int*)((char*)self + 0x1f0) = 1;
    ((MissionBase*)self)->TriggerUIUpdate();
  }
  ((MissionBase*)self)->FUN_00c472e0();
  ((MissionBase*)self)->FUN_00c471c0();
}

// @ 0x00c631f0
int __fastcall M_C631f0(void* self, int _e, int a)
{
  MissionWar* w = (MissionWar*)self;

  int result = ((int(__thiscall*)(void*, int))0x00c478b0)(self, a);
  if (result != 3) return result;
  if (w->mState != 0) return result;
  if (((void*(__cdecl*)())0x01021080)() != 0) return result;

  void* target = ((void*(__thiscall*)(void*))0x00970b30)(self);
  if (((void*(__cdecl*)())0x01021260)() != target) return result;

  if (w->mFlag) {
    int count = ((int(__thiscall*)(void*))0x00c710c0)(target);
    char any = 0;
    for (int i = 0; i < count; i++) {
      void* city = ((void*(__thiscall*)(void*, int))0x00c71030)(target, i);
      void** begin = *(void***)((char*)city + 0x3c);
      void** end = *(void***)((char*)city + 0x40);
      for (void** p = begin; p != end; p++) {
        if (((int(__thiscall*)(void*))0x00ff0760)(*p) > 0)
          any = 1;
      }
    }
    if (!any) ((void(__thiscall*)(void*))0x00c631b0)(self);
    return count;
  }

  void* empire = ((void*(__thiscall*)(void*))0x00c452a0)(self);
  void* target2 = ((void*(__thiscall*)(void*))0x00970b30)(self);
  char ok = ((char(__thiscall*)(void*, void*, int))0x00c70b20)(target2, empire, 0);
  if (!ok) ((void(__thiscall*)(void*))0x00c631b0)(self);
  return result;
}

// @ 0x00c63330
void __fastcall M_C63330(void* self, int _e)
{
  ((MissionBase*)self)->SetSerializer();  // 0xc2e4e0
  if (*(int*)((char*)self + 0x1f0) != 0) return;
  (*(void(__thiscall*)(void*))((*(void***)self)[0x6c/4]))(self);
  if (*(int*)((char*)self + 0x1f0) != 1) {
    *(int*)((char*)self + 0x1f0) = 1;
    ((MissionBase*)self)->TriggerUIUpdate();
  }
  ((MissionBase*)self)->FUN_00c472e0();
  ((MissionBase*)self)->FUN_00c471c0();
}

// @ 0x00c63380
bool __fastcall M_InitWar(void* self, int _e)
{
  MissionWar* w = (MissionWar*)self;

  if (!((MissionBase*)self)->Init()) return false;

  void* list = *(void**)((char*)self + 0x180);
  if (list) {
    void* prop = 0;
    char ok = ((char(__thiscall*)(void*, int, void**))Vt(list)[0x24/4])(list, 0x149a5cfc, &prop);
    if (ok && *(uint16_t*)((char*)prop + 0x12) == 1) {
      char* b = (char*)((void*(__cdecl*)())0x0041e920)();
      w->mFlag = (uint8_t)*b;
    }
  }

  w->mProgressMax = -1;
  w->mProgress = 0;

  int key = ((int(__thiscall*)(void*))0x00c45b40)(self);
  if (key != 0x2ca33bdb) {
    void* v = ((void*(__thiscall*)(void*, int))0x00c474b0)(self, key);
    if (v) ((void(__thiscall*)(void*, void*))0x00c47180)(self, v);
  }

  void* target = ((void*(__thiscall*)(void*))0x00970b30)(self);
  if (!target) {
    TextOpts opts = {};
    ((void(__thiscall*)(void*))0x00ba7bd0)(&opts);
    opts.mField04 = 0x20;
    opts.mField08 = 0x20;
    if (w->mFlag) opts.mField10 &= ~1;

    void* owner = ((void*(__thiscall*)(void*))0x00c451e0)(self);
    if (!owner) {
      ((void(__thiscall*)(void*))0x00ba8220)(&opts);
      return false;
    }

    void* picked = ((void*(__thiscall*)(void*, void*))0x00c47e20)(self, &opts);
    if (!picked) {
      ((void(__thiscall*)(void*))0x00ba8220)(&opts);
      return false;
    }
    ((void(__thiscall*)(void*, void*))0x00c47180)(self, picked);
    ((void(__thiscall*)(void*))0x00ba8220)(&opts);
  }

  void* planet = ((void*(__thiscall*)(void*))0x00970b30)(self);
  void* empire = ((void*(__thiscall*)(void*))0x00c71e30)(planet);
  ((void(__thiscall*)(void*, void*))0x00c45250)(self, empire);

  char active = ((char(__thiscall*)(void*))Vt(self)[0x128/4])(self);
  if (!active) return false;

  ((void(__thiscall*)(void*))0x00c4a0c0)(self);
  return true;
}

// @ 0x00c634a0
void __fastcall M_GetUIShort(void* self, int _e, void* out)
{
  MissionWar* w = (MissionWar*)self;

  if (w->mCachedText.mBegin != w->mCachedText.mEnd) {
    if (out != &w->mCachedText)
      ((void(__thiscall*)(void*, void*, void*))0x00423650)(
          out, w->mCachedText.mBegin, w->mCachedText.mEnd);
    return;
  }

  int key;
  switch (w->mState) {
    case 0:
      if (w->mFlag ||
          ((void*(__cdecl*)())0x01021080)() != 0 ||
          ((void*(__cdecl*)())0x01021260)() != ((void*(__thiscall*)(void*))0x00970b30)(self)) {
        key = 0xaad9c0b3;
      } else {
        key = 0xacf04d34;
      }
      break;
    case 1: key = 0x4e1f8fa8; break;
    case 2: key = 0x119c6317; break;
    case 3: key = 0xb4dfecf;  break;
    default: goto cache_text;
  }

  ((void(__thiscall*)(void*, int, void*))0x00c487d0)(self, key, out);

cache_text:
  if (out != &w->mCachedText) {
    WString12* src = (WString12*)out;
    ((void(__thiscall*)(void*, void*, void*))0x00423650)(
        &w->mCachedText, src->mBegin, src->mEnd);
  }
}

// @ 0x00c63570
void __fastcall M_GetProgressDisplayText(void* self, int _e, void* out)
{
  int v = *(int*)((char*)self + 0x1f8);
  if (v >= 0) WStr_Format(out, L"%d/%d", *(int*)((char*)self + 0x1f4), v);
  else        WStr_Format(out, L"%d/?", *(int*)((char*)self + 0x1f4));
}

// @ 0x00c635c0
int __fastcall M_GetNumCities(void* self, int _e)
{
  void* empire = ((void*(__thiscall*)(void*))0x00c452a0)(self);
  ((void*(__thiscall*)(void*))0x00970b30)(self);

  if (((void*(__cdecl*)())0x01021080)() == 0) {
    void* target = ((void*(__thiscall*)(void*))0x00970b30)(self);
    if (((void*(__cdecl*)())0x01021260)() != target)
      goto branch_b;
    void* nm = ((void*(__cdecl*)())0x00b3d300)();
    void* res = ((void*(__thiscall*)(void*, int, int, int, int, int))0x00b21340)(
        nm, 0xcd7d10, 0xd3d420, 0xacdff0, 0xb1e500, 0x18c43e8);
    void** begin = *(void***)((char*)res + 4);
    void** end = *(void***)((char*)res + 8);
    int count = 0;
    int empireId = *(int*)((char*)empire + 0x84);
    for (void** p = begin; p != end; p++) {
      void* city = *p;
      void* owner = ((void*(__thiscall*)(void*))0x00bd9bf0)(city);
      if (owner) {
        owner = ((void*(__thiscall*)(void*))0x00bd9bf0)(city);
        if (((int(__thiscall*)(void*))Vt(owner)[0x4c/4])(owner) == empireId) {
          int a = ((int(__thiscall*)(void*))0x00bd9bb0)(city);
          int b = ((int(__thiscall*)(void*))0x00bd9b70)(city);
          if (a + b > 0) count++;
        }
      }
    }
    return count;
  }

branch_b:
  void* planet = ((void*(__thiscall*)(void*))0x00970b30)(self);
  void* vec = ((void*(__thiscall*)(void*))0x00c71000)(planet);
  void** begin = *(void***)vec;
  void** end = *(void***)((char*)vec + 4);
  if (begin == end) return -1;

  int count = 0;
  int empireId = *(int*)((char*)empire + 0x84);
  for (void** p = begin; p != end; p++) {
    void* city = *p;
    if (((int(__thiscall*)(void*))0x00ff0420)(city) == empireId) {
      void* tv = ((void*(__thiscall*)(void*))0x005c65e0)(city);
      void** tb = *(void***)tv;
      void** te = *(void***)((char*)tv + 4);
      for (void** q = tb; q != te; q++) {
        int a = ((int(__thiscall*)(void*))0x00ff0870)(*q);
        int b = ((int(__thiscall*)(void*))0x00ff0760)(*q);
        if (a + b > 0) count++;
      }
    }
  }
  return count;
}

// @ 0x00c63740
uint32_t __fastcall M_GetTagString(void* self, int _e, int key, void* out)
{
  if (key == (int)0xaae66a73) {
    WStr_Format(out, (const wchar_t*)0x13f01bc, *(int*)((char*)self + 0x1f4));
    return 1;
  }
  if (key == (int)0xc74ba481) {
    int n = ((int(__thiscall*)(void*))0x00c635c0)(self);
    if (n >= 0) {
      WStr_Format(out, (const wchar_t*)0x13f01bc, n);
    } else {
      ((void(__thiscall*)(void*, const wchar_t*))0x005c3d90)(out, (const wchar_t*)0x1459c40);
    }
    return 1;
  }
  return ((uint32_t(__thiscall*)(void*, int, void*))0x00c491c0)(self, key, out);
}
