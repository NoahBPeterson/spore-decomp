// src/game/SPGonzago/SPMissionUseTool.cpp -- migrated from slice(s) s00c62880 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionUseTool.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPMission.h"

// ---- items of slice s00c62880 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
static inline void FreeWStringPtr(void* p) {
  if (p && *(int*)((char*)p - 4) != 0)
    ((void(__cdecl*)(void*))0x00f47380)(p);
}
// ---- items of slice s00c62880 end

// @ 0x00c62a80
void __fastcall M_InitUseTool(void* self, int _e)
{
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
bool __fastcall M_C62b30(void* self, int _e)
{
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
