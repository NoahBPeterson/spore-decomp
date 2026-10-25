// Slice s00c62880 — SP::cSPMissionWar / cMissionWar mission helpers.
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int);
void  __cdecl operator_delete__(void*);
void  __cdecl WStr_Format(void*, const wchar_t*, ...);          // 0x41e050
void  __cdecl FUN_00ebb720(int, int);                           // 0xebb720
struct NounIdHelper { void* Dispatch(void* id); };                // 0xb18460
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
  void SetSerializer();              // 0xc2e4e0
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

// @ 0x00c63a10
void FUN_00c63a10() { FUN_00ebb720(0, 0); }

// interface adjustors (`ret 4`, id at [esp+4], this in ecx) — member functions are __thiscall
struct Adj {
  void* Adjust0(void* id);
  void* Adjust1(void* id);
  void* Adjust2(void* id);
};

// @ 0x00c639d0 interface adjustor
void* Adj::Adjust1(void* id) {
  if (id == (void*)0x76c67df || id == (void*)0x7a309fb) return this;
  if (id == (void*)0x1186577) return this ? (char*)this + 0x34 : 0;
  return ((NounIdHelper*)this)->Dispatch(id);
}
// @ 0x00c63a20 interface adjustor
void* Adj::Adjust2(void* id) {
  if (id == (void*)0x771ad6a || id == (void*)0x7a309fb) return this;
  if (id == (void*)0x1186577) return this ? (char*)this + 0x34 : 0;
  return ((NounIdHelper*)this)->Dispatch(id);
}
// @ 0x00c639a0 interface adjustor
void* Adj::Adjust0(void* id) {
  if (id == (void*)0x1186577) return this ? (char*)this + 0x34 : 0;
  if (id == (void*)0x7a309fb) return this;
  return ((NounIdHelper*)this)->Dispatch(id);
}

// @ 0x00c62880
void* __fastcall cMissionUseTool_ctor(void* self, int _e) {
  ((MissionBase*)self)->BaseCtor();
  *(int*)((char*)self + 0x1f0) = 0;
  *(void**)self = (void*)0x1470970;
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

// ---- mission helpers --------------------------------------------------
struct WString12 { void* mBegin; void* mEnd; void* mCap; };
struct CString16 { uint8_t mData[0x10]; };

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

struct MissionUseTool {
  uint8_t pad00[0x1f4];
  void* mTargetBegin;              // +0x1f4
  void* mTargetEnd;                // +0x1f8
  void* mTargetCap;                // +0x1fc
  uint8_t pad200[8];
  uint8_t* mBytesBegin;            // +0x208
  uint8_t* mBytesEnd;              // +0x20c
  uint8_t* mBytesCap;              // +0x210
};

struct Key12 { uint32_t mKey; uint32_t mPad1; uint32_t mPad2; };
struct KeyVec { Key12* mBegin; Key12* mEnd; Key12* mCap; };
struct ByteVec { uint8_t* mBegin; uint8_t* mEnd; uint8_t* mCap; };

struct PropListResult {
  void* mBegin;                    // +0x00
  uint8_t pad04[4];
  int mCount;                      // +0x08
  uint8_t pad0c[4];
  uint16_t mFlags;                 // +0x10
  uint16_t mInlineCount;           // +0x12
};

struct PickOpts {
  int mField00;                    // +0x00
  int mField04;                    // +0x04
  int mField08;                    // +0x08
  int mField0c;                    // +0x0c
  int mField10;                    // +0x10
  int mField14;                    // +0x14
  uint8_t mFlag18;                 // +0x18
  uint8_t mFlag19;                 // +0x19
  uint8_t mFlag1a;                 // +0x1a
  uint8_t mFlag1b;                 // +0x1b
  int mField1c;                    // +0x1c
  int mField20;                    // +0x20
  int mField24;                    // +0x24
  int mField28;                    // +0x28
  void* mPtr2c;                    // +0x2c
  int mField30;                    // +0x30
  int mField34;                    // +0x34
  int mField38;                    // +0x38
  int mField3c;                    // +0x3c
  void* mPtr40;                    // +0x40
  int mField44;                    // +0x44
  int mField48;                    // +0x48
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

struct MsgData {
  uint8_t pad00[8];
  void* mPtr08;                    // +0x08
  uint8_t pad0c[4];
  void* mPtr10;                    // +0x10
};

static inline void FreeWStringPtr(void* p) {
  if (p && *(int*)((char*)p - 4) != 0)
    ((void(__cdecl*)(void*))0x00f47380)(p);
}

// @ 0x00c62990
uint32_t __fastcall M_C62990(void* self, int _e, int key, void* out) {
  if (key == (int)0x581c7d4c) {
    void* obj = ((void*(__cdecl*)())0x00c62710)();
    if (obj) {
      void* pm = ((void*(__cdecl*)())0x0067de30)();
      void* list = 0;
      ((void(__thiscall*)(void*, void*, int, void**))Vt(pm)[0x2c/4])(pm, obj, 0x30608f0b, &list);

      CString16 cstr;
      ((void(__thiscall*)(void*))0x006b5060)(&cstr);
      ((void(__cdecl*)(void*, int, void*))0x006a1360)(list, 0x3068d95d, &cstr);

      const wchar_t* text = ((const wchar_t*(__thiscall*)(void*))0x006b55c0)(&cstr);
      WString12 local = { 0, 0, 0 };
      ((void(__thiscall*)(void*, const wchar_t*))0x00579a90)(&local, text);

      if (out != &local)
        ((void(__thiscall*)(void*, void*, void*))0x00423650)(out, local.mBegin, local.mEnd);

      int bytes = (int)((char*)local.mEnd - (char*)local.mBegin) & ~1;
      if (bytes > 2 && local.mBegin)
        ((void(__cdecl*)(void*))0x00f47380)(local.mBegin);

      ((void(__thiscall*)(void*))0x006b5240)(&cstr);
      return 1;
    }
  }
  return ((uint32_t(__thiscall*)(void*, int, void*))0x00c491c0)(self, key, out);
}

// @ 0x00c62a80
void __fastcall M_InitUseTool(void* self, int _e) {
  void* list = *(void**)((char*)self + 0x180);
  PropListResult* r = (PropListResult*)((void*(__thiscall*)(void*, uint32_t))Vt(list)[0x28/4])(list, 0xc924ebff);

  uint16_t flags = r->mFlags & 0x30;
  void* src = (flags & 0x30) ? r->mBegin : (r->mInlineCount ? (void*)r : 0);
  int count = flags ? r->mCount : (r->mInlineCount ? 1 : 0);

  KeyVec* vec = (KeyVec*)((char*)self + 0x1f4);
  for (int i = 0; i < count; i++) {
    Key12 key;
    key.mKey = *(uint32_t*)src;
    key.mPad1 = 0;
    key.mPad2 = 0;
    if (vec->mEnd < vec->mCap) {
      *vec->mEnd = key;
      vec->mEnd++;
    } else {
      ((void(__thiscall*)(KeyVec*, Key12*, const Key12*))0x004e3e10)(vec, vec->mEnd, &key);
    }
    src = (char*)src + 0xc;
  }
}

// @ 0x00c62b30
bool __fastcall M_C62b30(void* self, int _e) {
  if (!((MissionBase*)self)->Init()) return false;

  ((void(__thiscall*)(void*))Vt(self)[0x16c/4])(self);
  ((void(__thiscall*)(void*))0x00c62a80)(self);

  MissionUseTool* u = (MissionUseTool*)self;
  int count = (int)((char*)u->mTargetEnd - (char*)u->mTargetBegin) / 0xc;
  ByteVec* bv = (ByteVec*)((char*)self + 0x208);
  for (int i = 0; i < count; i++) {
    uint8_t zero = 0;
    if (bv->mEnd < bv->mCap) {
      *bv->mEnd = zero;
      bv->mEnd++;
    } else {
      ((void(__thiscall*)(ByteVec*, uint8_t*, const uint8_t*))0x00426730)(bv, bv->mEnd, &zero);
    }
  }

  void* target = ((void*(__thiscall*)(void*))0x00970b30)(self);
  if (!target) {
    PickOpts opts = {};
    opts.mField04 = 0x3f;
    opts.mField08 = 0x3f;
    opts.mField0c = 0x38;
    opts.mField10 = 0x0f;
    opts.mField14 = 0x0f;
    opts.mFlag18 = 0;
    opts.mFlag19 = 0;
    opts.mFlag1a = 0;
    opts.mFlag1b = 1;
    opts.mField24 = 7;
    opts.mField28 = 3;

    void* picked = ((void*(__thiscall*)(void*, void*))0x00c47e20)(self, &opts);
    if (!picked) {
      FreeWStringPtr(opts.mPtr2c);
      FreeWStringPtr(opts.mPtr40);
      return false;
    }
    ((void(__thiscall*)(void*, void*))0x00c47180)(self, picked);
    FreeWStringPtr(opts.mPtr2c);
    FreeWStringPtr(opts.mPtr40);
  }

  ((void(__thiscall*)(void*))0x00c4a0c0)(self);
  ((void(__thiscall*)(void*))Vt(self)[0x170/4])(self);
  return true;
}

// @ 0x00c62ff0
float __fastcall M_C62ff0(void* self, int _e, int a, void* b) {
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

// @ 0x00c631f0
int __fastcall M_C631f0(void* self, int _e, int a) {
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

// @ 0x00c63380
bool __fastcall M_InitWar(void* self, int _e) {
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
void __fastcall M_GetUIShort(void* self, int _e, void* out) {
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

// @ 0x00c635c0
int __fastcall M_GetNumCities(void* self, int _e) {
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

// @ 0x00c637b0
void __fastcall M_C637b0(void* self, int _e, int msg, void* data) {
  MissionWar* w = (MissionWar*)((char*)self - 0x34);
  MsgData* d = (MsgData*)data;

  if (msg == 0x2489766) {
    ((void(__thiscall*)(void*))0x00c47d80)(w);
  } else if (msg == 0x248975f) {
    void* planet = d->mPtr10;
    if (planet == ((void*(__thiscall*)(void*))0x00970b30)(w)) {
      if (w->mProgressMax == -1)
        w->mProgressMax = ((int(__thiscall*)(void*))0x00c635c0)(w);
      if (!w->mFlag) {
        char tmp[16] = { 0 };
        ((void(__thiscall*)(void*, int, void*))0x0057ed80)(tmp, 0x1470d50, data);
        void* game = ((void*(__cdecl*)())0x01002bd0)();
        ((void(__thiscall*)(void*, int, int, int, int, int, int))0x0100a7c0)(
            game, 0x5fa70d2, 1, 0, 0, 0, 0);
      }
    }
    ((void(__thiscall*)(void*))0x00c47d80)(w);
  } else if (msg == 0x2489760) {
    void* planet = d->mPtr08;
    if (planet == ((void*(__thiscall*)(void*))0x00970b30)(w))
      ((void(__thiscall*)(void*))0x00c44f20)(w);
    ((void(__thiscall*)(void*))0x00c47d80)(w);
  } else if (msg == 0x3337cbb && w->mState == 0) {
    void* target = ((void*(__thiscall*)(void*))0x00970b30)(w);
    if (((void*(__cdecl*)())0x01021260)() == target && d->mPtr08) {
      void* obj = d->mPtr08;
      void* v = ((void*(__thiscall*)(void*, int))Vt(obj)[0xc/4])(obj, 0xee9b2232);
      if (v) {
        if (w->mFlag) {
          ((void(__thiscall*)(void*))0x00c63130)(w);
        } else {
          void* empire = ((void*(__thiscall*)(void*))0x00c452a0)(w);
          int empireId = *(int*)((char*)empire + 0x84);
          if (((int(__thiscall*)(void*))Vt(v)[0x4c/4])(v) == empireId) {
            w->mProgress++;
            void* nm = ((void*(__cdecl*)())0x00b3d300)();
            void* vec = ((void*(__thiscall*)(void*))0x00ace2c0)(nm);
            void** begin = *(void***)vec;
            void** end = *(void***)((char*)vec + 4);
            char other = 0;
            for (void** p = begin; p != end; p++) {
              void* o = *p;
              if (o != v &&
                  ((int(__thiscall*)(void*))Vt(o)[0x4c/4])(o) == empireId) {
                other = 1;
                break;
              }
            }
            if (!other) ((void(__thiscall*)(void*))0x00c631b0)(w);
            ((void(__thiscall*)(void*))0x00c47d80)(w);
          }
        }
      }
    }
  }

  ((void(__thiscall*)(void*, int, void*))0x00c4a6b0)(self, msg, data);
}
