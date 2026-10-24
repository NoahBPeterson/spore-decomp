// Slice s00d463a0 - cCreatureTriggerSystem / cCreatureModeStrategy trigger data.
// Reconstructed from annotated disassembly + Ghidra decompiles.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef          short s16;
typedef          char  s8;
typedef unsigned long long u64;
typedef          long long s64;

#include <math.h>

// ---- vtable-call signature typedefs (all thiscall) -----------------------
typedef void   (__thiscall *TFv)(void*);
typedef void   (__thiscall *TFv1)(void*, s32);
typedef void   (__thiscall *TFv2)(void*, s32, void*);
typedef u8     (__thiscall *TFb)(void*);
typedef u8     (__thiscall *TFbkey)(void*, u32, void*);
typedef void*  (__thiscall *TFp)(void*);
typedef u32    (__thiscall *TFu)(void*);
typedef float  (__thiscall *TFf)(void*);
typedef u8     (__thiscall *TFbeff)(void*, void*, s32, void*);
typedef u8     (__thiscall *TFbmsg)(void*, u32, void*);
typedef void   (__thiscall *TFmsg)(void*, void*);
typedef void   (__thiscall *TFmsgv)(void*, s32);

// ---- external callees ----------------------------------------------------
void  __cdecl FUN_0093a780(void* stream, void* out, s32 count, s32 flag); // 0x0093a780 EA::IO::ReadInt32
void* __cdecl FUN_00f473a0(void* alloc, const char* name, s32 a, s32 b, const char* file, s32 line); // 0x00f473a0 operator_new
void  __cdecl FUN_00f47380(void* p);          // 0x00f47380 operator_delete_array
void* __cdecl FUN_00b3d300(void);             // 0x00b3d300 SP::NounManager
void* __cdecl FUN_00b3d3e0(void);             // 0x00b3d3e0 SP::EventLog
void* __cdecl FUN_00d67dd0(void);             // 0x00d67dd0 SP::EffectsManagerPtr
void* __cdecl FUN_00b18e00(void* strat);      // 0x00b18e00
void  __cdecl FUN_00d2e8a0(float f);          // 0x00d2e8a0 cCreatureModeStrategy::NotifyEvent
void  __cdecl FUN_00f924e0(void* self, float f); // 0x00f924e0 (thiscall)
void  __cdecl FUN_00ac9480(void* dst, void* src); // 0x00ac9480
void  __cdecl FUN_0059c190(void* out, u32 quat);  // 0x0059c190 Matrix3FromQuaternion
void  __cdecl FUN_00571d40(void* msgsub, u32 v);  // 0x00571d40
void  __cdecl FUN_00434040(void* msg);            // 0x00434040 XformMsg::XformMsg (thiscall ecx=msg)
void* __cdecl FUN_00921340(u32 n);            // 0x00921340
u32   __cdecl FUN_00d46af0(void* a, void* b, void* c); // 0x00d46af0
void  __cdecl FUN_00d46a10(void* out, void* a, void* b, void* c, void* d); // 0x00d46a10
void  __stdcall FUN_00d47160(void* pos, void* val);  // 0x00d47160

// ---- modeled objects -----------------------------------------------------

// property object returned by the container lookup (slot 0x24)
struct PropC {
  u32 m00;
  u32 m04;
  u32 m08;
  u32 m0C;
  u16 m10;
  u16 mType;   // +0x12
  u32*   GetUInt();
  u8*    GetBool();
  s32*   GetInt();
  float* GetFloat();
};

// cCreatureTriggerSystem::cTriggersInfo (0x2c bytes)
struct TrigInfo {
  void* mRef0;    // +0x00
  u32   mField4;  // +0x04
  u8    mField8;  // +0x08
  u8    mPad09;
  u8    mPad0A;
  u8    mPad0B;
  u32   mFieldC;  // +0x0c
  u32   mField10; // +0x10
  float mField14; // +0x14
  float mField18; // +0x18
  u32   mField1C; // +0x1c
  u32   mField20; // +0x20
  u8    mField24; // +0x24
  u8    mPad25;
  u8    mPad26;
  u8    mPad27;
  void* mRef28;   // +0x28
};

// eastl-style vector of cTriggersInfo with inline storage
struct TrigVec {
  TrigInfo* mBegin;  // +0x00
  TrigInfo* mEnd;    // +0x04
  TrigInfo* mCap;    // +0x08
  u32       mPadC;   // +0x0c
  u32       mPad10;  // +0x10
  u32       mCount;  // +0x14
  TrigVec*  Assign(TrigVec* src);                          // 0x00d47020
  TrigInfo* Grow(s32 n, TrigInfo* first, TrigInfo* last);  // 0x00d46bd0
  void      DestroyRange(TrigInfo* first, TrigInfo* last); // 0x00d3b320
};

// big trigger owner object (0x188 bytes) built by FUN_00d47320 / FUN_00d47380
struct BigC {
  void*    f0;      // +0x00
  void*    f4;      // +0x04
  TrigVec  vec;     // +0x08
  u8       buf[0x160]; // +0x20 inline element storage
  u8       f180;    // +0x180
  u8       f181[3];
  u32      f184;    // +0x184
  BigC*    CopyCtor(void* src);                       // 0x00d47320
};

// cCreatureModeStrategy slot-0x44 grid of {float, SpVector<UVector3>}
struct UVec3 { u32 x, y, z; };
struct SpVec3 {
  UVec3* mBegin;  // +0x00
  UVec3* mEnd;    // +0x04
  UVec3* mCap;    // +0x08
  u32    mPadC;   // +0x0c
  u32    mPad10;  // +0x10
  void   Resize(s32 n);   // 0x00473810
};
struct GridEntry {
  float  mValue; // +0x00
  SpVec3 mVec;   // +0x04
};
struct GridVec {
  GridEntry* mBegin; // +0x00
  GridEntry* mEnd;   // +0x04
  GridEntry* mCap;   // +0x08
  u32        mPadC;  // +0x0c
  u32        mPad10; // +0x10
  void       Resize(s32 n);  // 0x00d45710
};

// cVarListSerializer (0xa14 bytes); only the two used entry points.
struct cVarListSerializer {
  u8   mData[0xa14];
  void Ctor(void* obj, void* list, u32 sig);  // 0x00692f90
  u8   Serialize(void* stream);               // 0x00693e10
};

// object owning the fixed_pool / hash map (FUN_00d46610)
struct HashMapC {
  u8    pad00[8];
  u32   mField08;  // +0x08
  u32   mField0C;  // +0x0c
  float mField10;  // +0x10
  float mField14;  // +0x14
  u32   mField18;  // +0x18
  u8    pad1C[0x18];
  u32   mField34;       // +0x34 embedded object (address only)
  u8    pad38[0x100];
  u8    mPool138[0x6200]; // +0x138 fixed pool storage
  u32   mField6338;     // +0x6338 embedded object (address only)
  void  Construct(void* a0, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6); // FUN_00d3b260
  void  Grow(u32 n);          // FUN_00d39c30
};
struct FixedPoolLocal {
  void* mpHead;  // +0x00
  u32   x04;     // +0x04
  void* p08;     // +0x08
  void* p0C;     // +0x0c
  u32   x10;     // +0x10
  void* p14;     // +0x14
};
struct FixedPoolC {
  void* mpHead;
  void Init(void* mem, u32 poolSize, u32 elemSize, u32 align, u32 flags); // 0x00921260
};
struct PoolAllocC {
  u32 Size(u32 v);   // 0x009213c0
};

// noun-manager/avatar models
struct NounMgrC {
  void* GetAvatar();  // 0x00b1fdb0
};
struct AvatarC {
  u8 pad[0xb5e];
  u8 fB5E;            // +0xb5e
};

// fake eastl string16 scratch (begin/end/cap) used by EvaluateTrigger
struct EaStr16 {
  u16* mBegin;
  u16* mEnd;
  u16* mCap;
};

// XformMsg receiver for the effect transform
struct XformMsgC {
  u8  pad00[8];
  u16 mFlags;   // +0x08
  u16 mPad0A;
  u16 mCount;   // +0x0a
  u8  pad0C[0x10];
  u32 mMatrix[9]; // +0x1c
};

struct GlobInstC {
  u8     pad[0xbc];
  void** mBegin;  // +0xbc
  void** mEnd;    // +0xc0
};

struct EventLogC {
  void PostFeedbackEvent(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5); // 0x00dd8640
};

__forceinline void* GetStream(void* reader) {
  void* o = ((TFp)(*(void***)reader)[0x20 / 4])(reader);
  return ((TFp)(*(void***)o)[0x18 / 4])(o);
}

// ======================================================================
// 0x00d463a0 - SP::cCreatureModeStrategy::Read
// ======================================================================
// @ 0x00d463a0
u8 __fastcall FUN_00d463a0(void* self, void* dummy, void* reader) {
  (void)dummy;
  u32 version = 0;
  FUN_0093a780(GetStream(reader), &version, 1, 0);
  cVarListSerializer ser;
  ser.Ctor((char*)self - 8, (void*)0x15833f0, 0x1a80d26);
  if (version != 0x12191ca) return 0;
  if (!ser.Serialize(reader)) return 0;
  u32 count = 0;
  FUN_0093a780(GetStream(reader), &count, 1, 0);
  GridVec* gv = (GridVec*)((char*)self + 0x44);
  gv->Resize((s32)count);
  u32 ver = ((TFu)(*(void***)reader)[0x3c / 4])(reader);
  if (ver < 0x1e0001) {
    for (u32 i = 0; i < count; i++) {
      char* e = (char*)gv->mBegin + i * 0x18;
      SpVec3* v = (SpVec3*)(e + 4);
      *(float*)e = 1.0f;
      u32 n = 0;
      FUN_0093a780(GetStream(reader), &n, 1, 0);
      v->Resize((s32)n);
      for (u32 j = 0; j < n; j++) {
        FUN_0093a780(GetStream(reader), (char*)v->mBegin + j * 0xc, 3, 0);
      }
    }
  } else {
    for (u32 i = 0; i < count; i++) {
      char* e = (char*)gv->mBegin + i * 0x18;
      SpVec3* v = (SpVec3*)(e + 4);
      u32 n = 0;
      u32 val = 0;
      FUN_0093a780(GetStream(reader), &n, 1, 0);
      FUN_0093a780(GetStream(reader), &val, 1, 0);
      v->Resize((s32)n);
      *(u32*)e = val;
      for (u32 j = 0; j < n; j++) {
        FUN_0093a780(GetStream(reader), (char*)v->mBegin + j * 0xc, 3, 0);
      }
    }
  }
  return 1;
}

// ======================================================================
// 0x00d46610 - eastl::fixed_hash_map<...>::fixed_hash_map
// ======================================================================
// @ 0x00d46610
void* __fastcall FUN_00d46610(HashMapC* self, void* dummy, void* a0, void* a1) {
  (void)dummy;
  FixedPoolLocal local;
  void* pool = self->mPool138;
  local.mpHead = 0;
  ((FixedPoolC*)&local)->Init(pool, 0x6200, 0x188, 4, 0);
  local.p08 = pool;
  local.p0C = (char*)pool + 0x6200;
  local.x10 = 0x188;
  local.p14 = &self->mField34;
  void* alloc = FUN_00921340(0x40);
  void* pa1 = &a1;
  self->Construct(alloc, a0, pa1, pa1, a1, pa1, &local);
  self->mField10 = 10000.0f;
  self->mField14 = 2.0f;
  self->mField18 = 0;
  u32 n = ((PoolAllocC*)&local)->Size(self->mField0C);
  if (self->mField08 < n) self->Grow(n);
  return self;
}

// ======================================================================
// 0x00d466f0
// ======================================================================
// @ 0x00d466f0
u8 __fastcall FUN_00d466f0(void* self, void* dummy, void* unused) {
  (void)dummy;
  (void)unused;
  void* nm = FUN_00b3d300();
  AvatarC* av = (AvatarC*)((NounMgrC*)nm)->GetAvatar();
  if (av != 0 && av->fB5E == 0) return 1;
  ((TFv)(*(void***)self)[0x14 / 4])(self);
  return 0;
}

// ======================================================================
// 0x00d46730 - cCreatureTriggerSystem::ReadTrigger
// ======================================================================
// @ 0x00d46730
void __stdcall FUN_00d46730(TrigInfo* info) {
  void* prop;

  if (info->mRef0 != 0 && ((TFbkey)(*(void***)info->mRef0)[0x24 / 4])(info->mRef0, 0xb10f785d, &prop) &&
      ((PropC*)prop)->mType == 10)
    info->mField4 = *((PropC*)prop)->GetUInt();

  if (info->mRef0 != 0 && ((TFbkey)(*(void***)info->mRef0)[0x24 / 4])(info->mRef0, 0xe3771a50, &prop) &&
      ((PropC*)prop)->mType == 1)
    info->mField8 = *((PropC*)prop)->GetBool();

  if (info->mRef0 != 0 && ((TFbkey)(*(void***)info->mRef0)[0x24 / 4])(info->mRef0, 0xbc6f60af, &prop) &&
      ((PropC*)prop)->mType == 10)
    info->mFieldC = *((PropC*)prop)->GetUInt();

  if (info->mRef0 != 0 && ((TFbkey)(*(void***)info->mRef0)[0x24 / 4])(info->mRef0, 0x1ebc78bf, &prop) &&
      ((PropC*)prop)->mType == 9)
    info->mField10 = *((PropC*)prop)->GetInt();

  if (info->mRef0 != 0 && ((TFbkey)(*(void***)info->mRef0)[0x24 / 4])(info->mRef0, 0xef91ad29, &prop) &&
      ((PropC*)prop)->mType == 0xd)
    info->mField14 = *((PropC*)prop)->GetFloat();

  if (info->mRef0 != 0 && ((TFbkey)(*(void***)info->mRef0)[0x24 / 4])(info->mRef0, 0x2e65b70f, &prop) &&
      ((PropC*)prop)->mType == 0xd)
    info->mField18 = *((PropC*)prop)->GetFloat();

  info->mField18 = info->mField18 * info->mField18;

  if (info->mRef0 != 0 && ((TFbkey)(*(void***)info->mRef0)[0x24 / 4])(info->mRef0, 0x80d91e9e, &prop) &&
      ((PropC*)prop)->mType == 10)
    info->mField1C = *((PropC*)prop)->GetUInt();

  if (info->mRef0 != 0 && ((TFbkey)(*(void***)info->mRef0)[0x24 / 4])(info->mRef0, 0xd411d542, &prop) &&
      ((PropC*)prop)->mType == 10)
    info->mField20 = *((PropC*)prop)->GetUInt();

  info->mField24 = 0;
  if (info->mRef28 != 0) {
    ((TFv1)(*(void***)info->mRef28)[0xc / 4])(info->mRef28, 0);
    void* p = info->mRef28;
    if (p != 0) {
      info->mRef28 = 0;
      ((TFv)(*(void***)p)[4 / 4])(p);
    }
  }
}

// ======================================================================
// 0x00d46900 - cTriggersInfo copy constructor
// ======================================================================
// @ 0x00d46900
TrigInfo* __fastcall FUN_00d46900(TrigInfo* self, void* dummy, TrigInfo* src) {
  (void)dummy;
  self->mRef0 = src->mRef0;
  if (self->mRef0 != 0) ((TFv)(*(void***)self->mRef0)[0])(self->mRef0);
  self->mField4 = src->mField4;
  self->mField8 = src->mField8;
  self->mFieldC = src->mFieldC;
  self->mField10 = src->mField10;
  self->mField14 = src->mField14;
  self->mField18 = src->mField18;
  self->mField1C = src->mField1C;
  self->mField20 = src->mField20;
  self->mField24 = src->mField24;
  self->mRef28 = src->mRef28;
  if (self->mRef28 != 0) ((TFv)(*(void***)self->mRef28)[0])(self->mRef28);
  return self;
}

// ======================================================================
// 0x00d46970 - cTriggersInfo assignment
// ======================================================================
// @ 0x00d46970
TrigInfo* __fastcall FUN_00d46970(TrigInfo* self, void* dummy, TrigInfo* src) {
  (void)dummy;
  if (src->mRef0 != self->mRef0) {
    void* n = src->mRef0;
    void* o = self->mRef0;
    if (n != 0) ((TFv)(*(void***)n)[0])(n);
    self->mRef0 = n;
    if (o != 0) ((TFv)(*(void***)o)[4 / 4])(o);
  }
  self->mField4 = src->mField4;
  self->mField8 = src->mField8;
  self->mFieldC = src->mFieldC;
  self->mField10 = src->mField10;
  self->mField14 = src->mField14;
  self->mField18 = src->mField18;
  self->mField1C = src->mField1C;
  self->mField20 = src->mField20;
  self->mField24 = src->mField24;
  {
    void* n = src->mRef28;
    if (n != self->mRef28) {
      void* o = self->mRef28;
      if (n != 0) ((TFv)(*(void***)n)[0])(n);
      self->mRef28 = n;
      if (o != 0) ((TFv)(*(void***)o)[4 / 4])(o);
    }
  }
  return self;
}

// ======================================================================
// 0x00d46a90 - destroy cTriggersInfo range
// ======================================================================
// @ 0x00d46a90
void* __cdecl FUN_00d46a90(void* a, void* b, void* out) {
  while (a != b) {
    TrigInfo* e = (TrigInfo*)a;
    void* p = e->mRef28;
    if (p != 0) ((TFv1)(*(void***)p)[0xc / 4])(p, 0);
    p = e->mRef28;
    if (p != 0) ((TFv)(*(void***)p)[4 / 4])(p);
    p = e->mRef0;
    if (p != 0) ((TFv)(*(void***)p)[4 / 4])(p);
    a = (char*)a + 0x2c;
    out = (char*)out + 0x2c;
  }
  return out;
}

// ======================================================================
// 0x00d46c30 - cCreatureTriggerSystem::EvaluateTrigger
// ======================================================================
// @ 0x00d46c30
u8 __cdecl FUN_00d46c30(TrigInfo* info, void* strat, void* creature) {
  if (info->mField24 != 0) return 0;
  if (((TFb)(*(void***)strat)[0x2c / 4])(strat)) return 0;

  switch (info->mField4) {
    case 0: {
      float f = ((char*)creature ? *(float*)((char*)creature + 0x5e0) : 0.0f) + info->mField14;
      void* c = (char*)creature + 0x5a8;
      float hi = ((TFf)(*(void***)c)[0x58 / 4])(c);
      f = (f > 0.0f) ? f : 0.0f;
      f = (f < hi) ? f : hi;
      FUN_00f924e0(c, f);
      *(float*)(*(u32*)0x169e3e8 + 0x2c) = (float)fabs(info->mField14);
      break;
    }
    case 2:
      FUN_00d2e8a0(info->mField14);
      *(float*)(*(u32*)0x169e3e8 + 0x2c) = info->mField14;
      break;
    case 3: {
      int local[3];
      local[0] = (int)creature;
      local[1] = 0;
      local[2] = (int)info->mField14;
      GlobInstC* gi = *(GlobInstC**)0x169e294;
      for (void** p = gi->mBegin; p != gi->mEnd; p++) {
        void* obj = *p;
        ((TFbmsg)(*(void***)obj)[0x18 / 4])(obj, 0xd3353635, local);
      }
      *(float*)(*(u32*)0x169e3e8 + 0x2c) = info->mField14;
      break;
    }
    case 4:
      FUN_00f924e0((char*)creature + 0x5a8, 0.0f);
      break;
    case 5: {
      int local[3];
      local[0] = (int)creature;
      local[1] = 0;
      local[2] = 0;
      GlobInstC* gi = *(GlobInstC**)0x169e294;
      for (void** p = gi->mBegin; p != gi->mEnd; p++) {
        void* obj = *p;
        ((TFbmsg)(*(void***)obj)[0x18 / 4])(obj, 0xd335363a, local);
      }
      break;
    }
    case 6: {
      s32 local[3];
      local[0] = (s32)creature;
      local[1] = 0;
      local[2] = (s32)info->mField14;
      GlobInstC* gi = *(GlobInstC**)0x169e294;
      for (void** p = gi->mBegin; p != gi->mEnd; p++) {
        void* obj = *p;
        ((TFbmsg)(*(void***)obj)[0x18 / 4])(obj, 0x5371f11, local);
      }
      break;
    }
    default:
      return 0;
  }

  if (info->mField1C != 0) {
    void* ref = 0;
    void* em = FUN_00d67dd0();
    if (ref != 0) {
      void* o = ref;
      ref = 0;
      ((TFv)(*(void***)o)[4 / 4])(o);
    }
    u8 ok = ((TFbeff)(*(void***)em)[0x2c / 4])(em, (void*)info->mField1C, 0, &ref);
    if (ok) {
      if (info->mRef28 != 0)
        ((TFv1)(*(void***)info->mRef28)[0xc / 4])(info->mRef28, 0);
      FUN_00ac9480(&info->mRef28, &ref);
      void* obj = FUN_00b18e00(strat);
      if (obj == 0) obj = (creature != 0) ? (void*)((char*)creature + 0xc0) : 0;
      XformMsgC msg;
      FUN_00434040(&msg);
      u32 q1 = ((TFu)(*(void***)obj)[0x2c / 4])(obj);
      FUN_00571d40((char*)&msg + 4, q1);
      u32 q2 = ((TFu)(*(void***)obj)[0x30 / 4])(obj);
      u32 mat[9];
      FUN_0059c190(mat, q2);
      for (s32 i = 0; i < 9; i++) msg.mMatrix[i] = mat[i];
      msg.mFlags |= 2;
      msg.mCount++;
      ((TFmsg)(*(void***)ref)[0x18 / 4])(ref, &msg);
      ((TFmsgv)(*(void***)ref)[8 / 4])(ref, 0);
    }
    if (ref != 0) ((TFv)(*(void***)ref)[4 / 4])(ref);
  }

  if (info->mField20 != 0) {
    EventLogC* log = (EventLogC*)FUN_00b3d3e0();
    log->PostFeedbackEvent(info->mField20, 0x68dd6929, 0, 0, 1, 0);
  }

  s32 v = (s32)info->mField10;
  if (v > 0) {
    info->mField10 = (u32)(v - 1);
    if (v == 1) info->mField24 = 1;
  }

  {
    u16 strbuf[8];
    u16* sBegin = strbuf;
    u16* sEnd = strbuf;
    u16* sCap = strbuf;
    sBegin[0] = 0;
    if ((((u32)sEnd - (u32)sBegin) & 0xfffffffe) > 2 && sBegin != 0 && sBegin != sCap)
      FUN_00f47380(sBegin);
  }
  return 1;
}

// ======================================================================
// 0x00d47020 - TrigVec::Assign
// ======================================================================
// @ 0x00d47020
TrigVec* __fastcall FUN_00d47020(TrigVec* self, void* dummy, TrigVec* src) {
  (void)dummy;
  if (src == self) return self;
  s32 n = (s32)(((char*)src->mEnd - (char*)src->mBegin) / 0x2c);
  if ((s32)(((char*)self->mCap - (char*)self->mBegin) / 0x2c) < n) {
    TrigInfo* nb = self->Grow(n, src->mBegin, src->mEnd);
    self->DestroyRange(self->mBegin, self->mEnd);
    if (self->mBegin != 0 && *(s32*)((char*)self->mBegin - 4) != 0)
      FUN_00f47380(self->mBegin);
    self->mEnd = (TrigInfo*)((char*)nb + n * 0x2c);
    self->mBegin = nb;
    self->mCap = (TrigInfo*)((char*)nb + n * 0x2c);
    return self;
  }
  s32 size = (s32)(((char*)self->mEnd - (char*)self->mBegin) / 0x2c);
  if (size < n) {
    FUN_00d46af0(src->mBegin, (char*)src->mBegin + size * 0x2c, self->mBegin);
    void* tmp[8];
    FUN_00d46a10(tmp, (char*)src->mBegin + size * 0x2c, src->mEnd, self->mEnd, src->mEnd);
    self->mEnd = (TrigInfo*)((char*)self->mBegin + n * 0x2c);
    return self;
  }
  TrigInfo* end = (TrigInfo*)FUN_00d46af0(src->mBegin, src->mEnd, self->mBegin);
  self->DestroyRange(end, self->mEnd);
  self->mEnd = (TrigInfo*)((char*)self->mBegin + n * 0x2c);
  return self;
}

// ======================================================================
// 0x00d472a0 - TrigVec::push_back (default element)
// ======================================================================
// @ 0x00d472a0
void __fastcall FUN_00d472a0(TrigVec* self, void* dummy) {
  (void)dummy;
  TrigInfo* e = self->mEnd;
  if (e < self->mCap) {
    self->mEnd = (TrigInfo*)((char*)e + 0x2c);
    if (e != 0) {
      e->mRef0 = 0;
      e->mRef28 = 0;
    }
    return;
  } else {
    TrigInfo tmp;
    tmp.mRef0 = 0;
    tmp.mRef28 = 0;
    FUN_00d47160(e, &tmp);
    void* r28 = tmp.mRef28;
    if (r28 != 0) {
      ((TFv1)(*(void***)r28)[0xc / 4])(r28, 0);
      ((TFv)(*(void***)r28)[4 / 4])(r28);
    }
    void* r0 = tmp.mRef0;
    if (r0 != 0) ((TFv)(*(void***)r0)[4 / 4])(r0);
  }
}

// ======================================================================
// 0x00d47320 - BigC copy constructor (from BigC)
// ======================================================================
// @ 0x00d47320
BigC* __fastcall FUN_00d47320(BigC* self, void* dummy, BigC* src) {
  (void)dummy;
  self->f0 = src->f0;
  self->f4 = src->f4;
  if (self->f4 != 0) ((TFv)(*(void***)self->f4)[0])(self->f4);
  TrigVec* v = &self->vec;
  char* buf = (char*)v + 0x18;
  v->mBegin = (TrigInfo*)buf;
  v->mEnd = (TrigInfo*)buf;
  v->mCount = 0;
  v->mCap = (TrigInfo*)(buf + 0x160);
  v->Assign(&src->vec);
  self->f180 = src->f180;
  return self;
}

// ======================================================================
// 0x00d47380 - BigC copy constructor (from raw trigger pair)
// ======================================================================
// @ 0x00d47380
BigC* __fastcall FUN_00d47380(BigC* self, void* dummy, void* p2, void* p3) {
  (void)dummy;
  self->f0 = *(void**)p2;
  self->f4 = *(void**)p3;
  if (self->f4 != 0) ((TFv)(*(void***)self->f4)[0])(self->f4);
  TrigVec* v = &self->vec;
  char* buf = (char*)v + 0x18;
  v->mBegin = (TrigInfo*)buf;
  v->mEnd = (TrigInfo*)buf;
  v->mCount = 0;
  v->mCap = (TrigInfo*)(buf + 0x160);
  v->Assign((TrigVec*)((char*)p3 + 4));
  self->f180 = *(u8*)((char*)p3 + 0x17c);
  return self;
}

// ======================================================================
// 0x00d473e0 - BigC pool allocation / construction
// ======================================================================
// @ 0x00d473e0
void* __fastcall FUN_00d473e0(void* self, void* dummy, u32 arg) {
  (void)dummy;
  BigC* obj = *(BigC**)((char*)self + 0x1c);
  if (obj != 0) {
    *(void**)((char*)self + 0x1c) = *(void**)obj;
  } else {
    obj = (BigC*)FUN_00f473a0(*(void**)((char*)self + 0x2c), (const char*)0x13f09b4, 0, 0,
                               (const char*)0x13ebb38, 0xd1);
  }
  if (obj != 0) {
    obj->CopyCtor((void*)arg);
  }
  obj->f184 = 0;
  return obj;
}

// ======================================================================
// 0x00d47510 - trigger map lookup / insert
// ======================================================================
// @ 0x00d47510
struct HashMap2C {
  u8     pad0[4];
  void** mBuckets;  // +0x04
  u32    mIndex;    // +0x08
  void   FindLocal(void* out, void* key);  // 0x00d46b70
  void   Insert(void* a, void* b, void* c); // 0x00d47430
};

// source temp used by the map insert path (f0, vector with inline storage, flag)
struct SrcTrig {
  void*   f0;        // +0x00
  TrigVec vec;       // +0x04
  u8      buf[0x160];// +0x1c inline element storage
  u8      flag;      // +0x17c
};

int __fastcall FUN_00d47510(HashMap2C* self, void* dummy, void* param) {
  (void)dummy;
  int local[3];
  self->FindLocal(local, param);
  if (local[0] != (int)self->mBuckets[self->mIndex]) return local[0] + 4;

  SrcTrig src;
  src.f0 = 0;
  src.vec.mBegin = (TrigInfo*)src.buf;
  src.vec.mEnd = (TrigInfo*)src.buf;
  src.vec.mCap = (TrigInfo*)(src.buf + 0x160);
  src.vec.mCount = 0;
  src.flag = 0;

  BigC dst;
  BigC* built = FUN_00d47380(&dst, 0, param, &src);
  self->Insert(&src, built, (void*)(u32)(local[0] & 0xffffff00));

  int result = local[0] + 4;
  dst.vec.DestroyRange(dst.vec.mBegin, dst.vec.mEnd);
  if (dst.vec.mBegin != 0 && *(s32*)((char*)dst.vec.mBegin - 4) != 0)
    FUN_00f47380(dst.vec.mBegin);
  if (dst.f4 != 0) ((TFv)(*(void***)dst.f4)[4 / 4])(dst.f4);
  src.vec.DestroyRange(src.vec.mBegin, src.vec.mEnd);
  if (src.vec.mBegin != 0 && *(s32*)((char*)src.vec.mBegin - 4) != 0)
    FUN_00f47380(src.vec.mBegin);
  if (src.f0 != 0) ((TFv)(*(void***)src.f0)[4 / 4])(src.f0);
  return result;
}
