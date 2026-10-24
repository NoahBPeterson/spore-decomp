// match/slices/s00c15310/s00c15310.cpp
// Object file: SPGonzago/SPCreatureBase.obj.
// Functions: Simulator::cCreatureBase::func64h and helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2
//
// Many of these routines operate on a `cCreatureBase`-derived object whose
// retail layout extends well past the canonical header, so the object is
// modelled with local role+offset stub structs (every field named by role).

typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  ulong;
typedef unsigned int   SIZE_T;

struct Vec3 { float x, y, z; };
struct Float4 { float x, y, z, w; };

// ---------------------------------------------------------------------------
// A ref-counted object: slot 0 is AddRef, slot 1 is Release.
// ---------------------------------------------------------------------------
struct RefCnt {
  virtual void  AddRef();               // 0x00
  virtual void  Release();              // 0x04
  virtual void  pad08();
  virtual void  pad0c();
  virtual void  pad10();
  virtual void  pad14();
  virtual void  pad18();
  virtual void  pad1c();
  virtual void  pad20();
  virtual void  pad24();
  virtual void  pad28();
  virtual void  pad2c();
  virtual void  pad30();
  virtual void  pad34();
  virtual void  pad38();
  virtual void  pad3c();
  virtual void  pad40();
  virtual void  pad44();
  virtual void  pad48();
  virtual void  pad4c();
  virtual void  pad50();
  virtual void  pad54();
  virtual void  pad58();
  virtual void  pad5c();
  virtual void  pad60();
  virtual void  pad64();
  virtual void  pad68();
  virtual void  pad6c();
  virtual void  pad70();
  virtual void  pad74();
  virtual void  pad78();
  virtual void  pad7c();
  virtual void  pad80();
  virtual void  pad84();
  virtual void  pad88();
  virtual void  pad8c();
  virtual void  pad90();
  virtual void  pad94();
  virtual void  pad98();
  virtual void  pad9c();
  virtual void  pada0();
  virtual void  padA4();
  virtual void  padA8();
  virtual void  padAc();
  virtual void  padB0();
  virtual void  padB4();
  virtual void  padB8();
  virtual void  padBc();
};

// ---------------------------------------------------------------------------
// The spatial subobject embedded at creature+0xc0.  Slots used:
//   0x5c GetBounds (Vec3*), 0x6c GetBox (Vec3*), 0x74 GetRadius (float)
// ---------------------------------------------------------------------------
struct SpatSub {
  virtual void  pad00(); virtual void  pad04(); virtual void  pad08(); virtual void  pad0c();
  virtual void  pad10(); virtual void  pad14(); virtual void  pad18(); virtual void  pad1c();
  virtual void  pad20(); virtual void  pad24(); virtual void  pad28(); virtual void  pad2c();
  virtual void  pad30(); virtual void  pad34(); virtual void  pad38(); virtual void  pad3c();
  virtual void  pad40(); virtual void  pad44(); virtual void  pad48(); virtual void  pad4c();
  virtual void  pad50(); virtual void  pad54(); virtual void  pad58();
  virtual Vec3* GetBounds(Vec3* out);              // 0x5c
  virtual void  pad60();
  virtual void  pad64(); virtual void  pad68();
  virtual Vec3* GetBox(Vec3* out);                 // 0x6c
  virtual void  pad70();
  virtual float GetRadius();                       // 0x74
};

// ---------------------------------------------------------------------------
// cSPCreatureAbility: +0x9c holds a refresh-scale float.
// ---------------------------------------------------------------------------
struct cCreatureAbility {
  u8   pad000[0x9c];
  float mF_9c;                                     // 0x9c
};

// ---------------------------------------------------------------------------
// An element of the ability-state vector (stride 0x10): +0x04 is a float.
// ---------------------------------------------------------------------------
struct cAbilityState {
  u32   mU32_00;                                   // 0x00
  float mF_04;                                     // 0x04
  u32   mU32_08;                                   // 0x08
  u32   mU32_0c;                                   // 0x0c
};

// A minimal std::vector-like block: mpBegin/end are raw pointers.
struct AbilityStates {
  cAbilityState* mpBegin;                          // 0x00
  cAbilityState* mpEnd;                            // 0x04
};

// ---------------------------------------------------------------------------
// The vtable of the class, with the primary virtuals used by this slice.
// ---------------------------------------------------------------------------
struct BaseVtbl {
  virtual void* Slot0c(u32);                       // 0x0c
  virtual void  Slot18(void*);                     // 0x18
  virtual void  Slot1c(void*);                     // 0x1c
  virtual void* Slot20();                          // 0x20
  virtual void* Slot24(u32 propId, void* out);     // 0x24
  virtual u32   Slot2c(void* p);                   // 0x2c
  virtual void  Slot60();                          // 0x60
  virtual void  Slot64();                          // 0x64
  virtual Vec3* Slot6c(Vec3* out);                 // 0x6c
  virtual void  Slot70();
  virtual float Slot74();                          // 0x74
  virtual void  Slotb0();                          // 0xb0
  virtual u32   Slotb0_count();                    // 0xb0
  virtual u32   Slotb4(u32);                       // 0xb4
  virtual void* Slotb8(u32);                       // 0xb8
  virtual void  Slotbc();                          // 0xbc
  virtual void  Slotc0();                          // 0xc0
};

// ---------------------------------------------------------------------------
// The main creature object.  Only the offsets touched in this slice are named.
// ---------------------------------------------------------------------------
struct cSPCreatureBase {
  BaseVtbl* mpVtbl;                                // 0x000
  u8        pad004[0xc0 - 0x04];
  SpatSub   mSpatial;                              // 0x0c0
  u8        pad0c4[0x1e4 - 0xc4];
  float     mF_1e4;                                // 0x1e4
  u8        pad1e8[0x4cc - 0x1e8];
  RefCnt*   mpRefA_4cc;                            // 0x4cc
  u8        pad4d0[0xb54 - 0x4d0];
  void*     mpAnimWorld_b54;                       // 0xb54 (anim world)
  u32       mFlags_b58;                            // 0xb58 (bit 9 tested)
  u8        padB5c[0xbf8 - 0xb5c];
  // mRechargingAbilityBits: a 3-word bitset at 0xbf8
  u32       mRechargeBits_bf8[3];                  // 0xbf8
  u32       mAbilityDirty_c04[3];                  // 0xc04
  u8        padC10[0xc28 - 0xc10];
  void*     mpAbilityStates_c28;                   // 0xc28 (vector block ptr)
  u8        padC2c[0xe40 - 0xc2c];
  u8*       mNeighborBegin_e40;                    // 0xe40
  u8*       mNeighborEnd_e44;                      // 0xe44
  u8        padE48[0xe58 - 0xe48];
  float     mWaveF_e58;                            // 0xe58
  u8        padE5c[0xeb0 - 0xe5c];
  // Slot 0 of the 4x0x34-byte body-effect slot block at 0xeb0. Slot 1 begins
  // at 0xee4 (aliasing mFlags_ee4 below), slots 2..3 follow it.
  u8        mBodyBlock_eb0[0x34];                   // 0xeb0
  u32       mFlags_ee4;                            // 0xee4

  void __thiscall func64h(s32 a2, float a3);       // 0xc15310
  float FUN_00c15920();                            // 0xc15920
  float FUN_00c15970();                            // 0xc15970
  void  FUN_00c15470(s32 a2, RefCnt* a3, u8 a4);   // 0xc15470
  u8    FUN_00c159c0(u32 a2, u32 a3, u8 a4);       // 0xc159c0
  void* FUN_00c15bd0(u32 a2, u8 a3, u32 a4);       // 0xc15bd0
  u8    FUN_00c15d50(u32 a2, u32 a3, u32 a4);      // 0xc15d50
  void  FUN_00c15dc0(float a2);                    // 0xc15dc0
};

// A message object used by ApplyWave.
struct SlotMessageVtbl {
  virtual void  pad00(); virtual void  pad04(); virtual void  pad08();
  virtual void  pad0c(); virtual void  pad10();
  virtual void  Dispatch(void* a, u32 b, u32 c);  // 0x14
};

// free helpers, declared after the struct
void __cdecl FUN_00c16090(u32* a1, u32* a2, u32* a3);       // 0xc16090
u8   __cdecl FUN_00c160c0(void* a1);                        // 0xc160c0
SlotMessageVtbl* __cdecl MessageServer();                   // 0x67dcc0
void __cdecl SlotMessage_Destruct(void* p);                 // 0x421cf0
u8   __cdecl EA_IO_WriteUint32(void* stream, u32* val, s32 count, s32 a4); // 0x93aa70
u8   __cdecl EA_StreamWrite(void* stream, s32 val, s32 a3); // 0x93a9a0
void* __cdecl FUN_00c15e50_impl(void* a1, void* a2);        // 0xc15e50
u8   __cdecl FUN_00c16100_impl(void* a1);                   // 0xc16100
float __cdecl FUN_00c161f0_impl(cSPCreatureBase* self, float a2); // 0xc161f0
u32  __cdecl FUN_00c0f620_();                               // 0xc0f620
u32  __cdecl FUN_00c0dfb0_();                               // 0xc0dfb0
u8   __cdecl FUN_00c11f50(cSPCreatureBase*, u32, u32, u32, u32); // 0xc11f50
void __cdecl FUN_00c14f70(cSPCreatureBase*, u32, u32, u32);      // 0xc14f70
void* __cdecl EffectsManager();                                  // 0x67ddd0

// ---------------------------------------------------------------------------
// An entry in the neighbor/attachment vector (stride 0x24) at +0xe40..+0xe44.
// The fields touched:
//   +0x04 (a type/id), +0x18 bool, +0x20 target object ptr, +0x24 float
// ---------------------------------------------------------------------------
struct tEntry {
  u32   mId_00;                                    // 0x00
  u32   mType_04;                                  // 0x04
  u8    pad08[0x18 - 0x08];
  u8    mbFlag18;                                  // 0x18
  u8    pad19[0x20 - 0x19];
  RefCnt* mpObj_20;                                // 0x20
  float mF_24;                                     // 0x24
};

// ---------------------------------------------------------------------------
// A body-effect/part object.  Slot 4 releases, 8 is a refresh, 0x18 sets a
// Matrix3 transform, 0x14/0x2c are generic.
// ---------------------------------------------------------------------------
struct BodyEffectVtbl {
  virtual void  pad00(); virtual void  pad04(); virtual void  pad08();
  virtual void  pad0c(); virtual void  pad10(); virtual void  pad14();
  virtual void  SetMatrix(void* m);                // 0x18
  virtual void  pad1c(); virtual void  pad20(); virtual void  pad24();
  virtual void  pad28();
  virtual void  Slot2c();                          // 0x2c
};

struct BodyEffect {
  BodyEffectVtbl* mpVtbl;                          // 0x00
  float           mF_04;                           // 0x04
  u8              pad08[0x2c - 0x08];
  void*           mpMatrix_2c;                     // 0x2c
};

// ---------------------------------------------------------------------------
// A generic vtable-bearing object for the many raw slots used below.
// ---------------------------------------------------------------------------
struct ObjVtbl {
  virtual void  Slot00(); virtual void  Slot04(); virtual void  Slot08();
  virtual void* Slot0c(u32); virtual void  Slot10(); virtual void  Slot14();
  virtual void  Slot18(); virtual void  Slot1c();
  virtual void* Slot20();  virtual void  Slot24(); virtual void  Slot28();
  virtual u8    Slot2c();  virtual void  Slot30(); virtual void  Slot34();
  virtual void  Slot38();  virtual void  Slot3c(); virtual void  Slot40();
  virtual void  Slot44();  virtual void  Slot48(); virtual void  Slot4c();
  virtual void  Slot50();  virtual void  Slot54(); virtual void  Slot58();
  virtual Vec3* Slot5c(Vec3* out);                 // 0x5c
  virtual void  Slot60();  virtual void  Slot64();
  virtual Vec3* Slot6c(Vec3* out);                 // 0x6c
  virtual void  Slot70();
  virtual float Slot74();                          // 0x74
  virtual void  Slot78();  virtual void  Slot7c();
  virtual void  Slot80();  virtual void  Slot84(); virtual void  Slot88();
  virtual void  Slot8c();  virtual void  Slot90(); virtual void  Slot94();
  virtual void  Slot98();  virtual void  Slot9c(); virtual void  SlotA0();
  virtual void  SlotA4();  virtual void  SlotA8(); virtual void  SlotAc();
  virtual void  SlotB0();  virtual void  SlotB4();
  virtual void* SlotB8(u32);  virtual void  SlotBc();
  virtual void  SlotC0();
};

// ---------------------------------------------------------------------------
// Callees (address in comment).
// ---------------------------------------------------------------------------
// globals (unnamed retail data referenced by address)
extern float gF_15826c;        // 0x15826c
extern float gF_158270;        // 0x158270
extern float gF_169e280;       // 0x169e280
extern float gF_169e284;       // 0x169e284
extern float gF_1485720;       // 0x1485720 (_HK_REAL_ONE)
extern float gF_1471064;       // 0x1471064
extern float gF_146a32c;       // 0x146a32c (float sentinel, ~3.4e38)
extern float gF_13ec48c;       // 0x13ec48c
extern u8    gB_15716d0[];     // 0x15716d0
extern float gF_168d964[];     // 0x168d964 (Matrix3 template)
extern float gF_168d988[];     // 0x168d988
extern float gF_168d910[];     // 0x168d910
void*  __cdecl FUN_00b3d310();                        // 0xb3d310
int    __cdecl FUN_00c06000(void*);                   // 0xc06000
int    __fastcall FUN_00c06000_tc(void* thisptr, int dummy); // 0xc06000 (ecx=this)
int*   __cdecl FUN_00c70110(void*);                   // 0xc70110
void   __cdecl FUN_00c13db0(u32, void*);              // 0xc13db0
u8     __cdecl FUN_00c15150(void*, u32);              // 0xc15150 (cdecl shim, unused)
u8     __fastcall FUN_00c15150_tc(void* thisobj, int dummy, void* a1, u32 a2); // 0xc15150
void   __cdecl FUN_00c0f620();                        // 0xc0f620
void   __cdecl FUN_00c0fae0(void*);                   // 0xc0fae0
void   __cdecl FUN_00c0dfb0();                        // 0xc0dfb0
void   __cdecl FUN_00c0f490(void*);                   // 0xc0f490
void   __cdecl FUN_00c0ca00(Vec3*, Vec3*, float, void*, void*); // 0xc0ca00
u32    __cdecl FUN_00c0de60(cSPCreatureBase*, u32, u32);   // 0xc0de60
void*  __cdecl FUN_00ae66d0(u32);                     // 0xae66d0
void*  __cdecl FUN_00b21000(void*, void*);            // 0xb21000
u8     __cdecl FUN_0064f350(void*, u32, u32);         // 0x64f350
void*  __cdecl NounManager(void*);                    // 0xb3d300
void   __cdecl FUN_00b453a0(void*);                   // 0xb453a0
void   __cdecl FUN_00b54200(void*);                   // 0xb54200
void   __cdecl FUN_00d7d220(void*, void*);            // 0xd7d220
void   __cdecl FUN_00d7d2c0(void*, void*);            // 0xd7d2c0
void   __cdecl FUN_00c12640(float);                   // 0xc12640
void*  __cdecl FUN_0099c1a0(Vec3* out, void* quat, Vec3* in);  // 0x99c1a0
void*  __cdecl FUN_0099c0b0(void* out, void* a, void* b);      // 0x99c0b0
void   __cdecl FUN_0046d660(void* out, void* in);              // 0x46d660
void   __cdecl FUN_005f4e80(void* out, Vec3* euler);           // 0x5f4e80
float* __cdecl FUN_0041ea70(void* prop);                       // 0x41ea70
void   __cdecl FUN_0041cb40(void* out, void* src);             // 0x41cb40
void*  __cdecl FUN_0069b440(void* out, void* facing, void* up); // 0x69b440
void*  __cdecl FUN_009cab60(u32 a1, s32 a2);                   // 0x9cab60
void*  __cdecl FUN_00c15150_(void* a1, u32 a2);                // unused
void   __cdecl FUN_00d998d0();                         // unused here
void*  __cdecl cSPGetCurrentGameMode(u32);            // 0xb5b800
void*  __cdecl FUN_00b3d320(void*);                    // 0xb3d320
void*  __cdecl FUN_00b1daf0(void*);                    // 0xb1daf0
void   __cdecl FUN_00c0f960();                         // unused

// The EffectsManager singleton.
struct EffectsMgr {
  virtual void  pad0();
  virtual void  pad1();
  virtual void  pad2();
  virtual void  pad3();
  virtual void  pad4();
  virtual void  pad5();
  virtual void  pad6();
  virtual void  pad7();
  virtual void  pad8();
  virtual void  pad9();
  virtual void  padA();
  virtual u8    Slot2c(u32 a, u32 b, void** out);      // 0x2c
};

// ---------------------------------------------------------------------------
// Simulator::cCreatureBase vtable slot 0xb0 returns the ability count; the
// vtable of an ability holder returns the count.
// ---------------------------------------------------------------------------
struct cSPCreatureBaseVtbl {
  virtual void  pad00(); virtual void  pad04(); virtual void  pad08(); virtual void  pad0c();
  virtual void  pad10(); virtual void  pad14(); virtual void  pad18(); virtual void  pad1c();
  virtual void  pad20(); virtual void  pad24(); virtual void  pad28(); virtual void  pad2c();
  virtual void  pad30(); virtual void  pad34(); virtual void  pad38(); virtual void  pad3c();
  virtual void  pad40(); virtual void  pad44(); virtual void  pad48(); virtual void  pad4c();
  virtual void  pad50(); virtual void  pad54(); virtual void  pad58(); virtual void  pad5c();
  virtual void  pad60(); virtual void  pad64(); virtual void  pad68(); virtual void  pad6c();
  virtual void  pad70(); virtual void  pad74(); virtual void  pad78(); virtual void  pad7c();
  virtual void  pad80(); virtual void  pad84(); virtual void  pad88(); virtual void  pad8c();
  virtual void  pad90(); virtual void  pad94(); virtual void  pad98(); virtual void  pad9c();
  virtual void  padA0(); virtual void  padA4(); virtual void  padA8(); virtual void  padAc();
  virtual u32   GetAbilitiesCount();                    // 0xb0 (this slice)
  virtual cCreatureAbility* GetAbility(u32);            // 0xb4
  virtual void* Slotb8(u32);                            // 0xb8
};

struct SimCreature {
  cSPCreatureBaseVtbl* mpVtbl;                          // 0x000
};

// @ 0x00c15310
void __thiscall cSPCreatureBase::func64h(s32 a2, float a3)
{
  (void)a2;
  // Refresh ability-recharge timers.
  u32 n = 0;
  u32* pBits = this->mRechargeBits_bf8;
  do {
    if (pBits[0] != 0) {
      SimCreature* pSim = (SimCreature*)this;
      u32 count = pSim->mpVtbl->GetAbilitiesCount();
      u32 words[3];
      words[0] = pBits[0];
      words[1] = pBits[1];
      words[2] = pBits[2];
      u32 idx = 0;
      // first: check recharging words for set bits
      for (;;) {
        if (words[idx] != 0)
          break;
        idx++;
        if (idx >= 3) goto checkDirty;
      }
      while (idx < count) {
        if (idx < 0x58) {
          u32 bit = 1u << (idx & 0x1f);
          u32 wi = idx >> 5;
          if ((words[wi] & bit) == 0) { idx++; continue; }
          cAbilityState* pStates = (cAbilityState*)this->mpAbilityStates_c28;
          u32 clearMask = ~bit;
          words[wi] &= clearMask;
          if (pStates[idx].mF_04 >= 1.0f) {
            pStates[idx].mF_04 = 1.0f;
            this->mRechargeBits_bf8[wi] &= clearMask;
          } else {
            cCreatureAbility* pAb = ((SimCreature*)this)->mpVtbl->GetAbility(idx);
            u32 delta = (u32)((1.0f / pAb->mF_9c) * (float)count);
            pStates[idx].mF_04 = (float)delta + pStates[idx].mF_04;
          }
        }
        idx++;
      }
    }
    n++;
    pBits++;
  } while (n < 3);

checkDirty:
  n = 0;
  u32* pDirty = this->mAbilityDirty_c04;
  do {
    if (pDirty[0] != 0) {
      FUN_00c12640(a3);
      return;
    }
    n++;
    pDirty++;
  } while (n < 3);
}

// Copies `a1..a2` (exclusive) into a3 region, one u32 at a time, downward.
// @ 0x00c16090
void __cdecl FUN_00c16090(u32* a1, u32* a2, u32* a3)
{
  while (a2 != a1) {
    a2--;
    a3--;
    *a3 = *a2;
  }
}

// @ 0x00c160c0
u8 __cdecl FUN_00c160c0(void* a1)
{
  void** ppSlot = (void**)((u8*)a1 + 0x3c);
  if (*ppSlot == 0)
    return 0;
  void* p = ((ObjVtbl*)*ppSlot)->Slot0c(0xce9f6639);
  if (p == 0)
    return 0;
  if (a1 == 0)
    return 0;
  u8* pBase = (u8*)*(u32*)0x15716d0 + (u32)a1;
  return FUN_00c15150_tc(p, 0, pBase, 1);
}

// @ 0x00c15920
float cSPCreatureBase::FUN_00c15920()
{
  s32 saved = (s32)(u32)(this->mpRefA_4cc);
  s32 cur = FUN_00c06000_tc(FUN_00b3d310(), 0);
  if (saved == cur && ((this->mFlags_ee4 >> 5) & 1) == 0)
    return this->mF_1e4 * gF_15826c + gF_169e280;
  return gF_146a32c;
}

// @ 0x00c15970
float cSPCreatureBase::FUN_00c15970()
{
  s32 saved = (s32)(u32)(this->mpRefA_4cc);
  s32 cur = FUN_00c06000_tc(FUN_00b3d310(), 0);
  if (saved == cur && ((this->mFlags_ee4 >> 5) & 1) == 0)
    return this->mF_1e4 * gF_158270 + gF_169e284;
  return gF_146a32c;
}

// Number of entries in the neighbor vector (stride 0x24).
static inline u32 neighborCount(cSPCreatureBase* p)
{
  return (u32)((p->mNeighborEnd_e44 - p->mNeighborBegin_e40) / 0x24);
}

// @ 0x00c15d50
u8 cSPCreatureBase::FUN_00c15d50(u32 a2, u32 a3, u32 a4)
{
  u32 n = neighborCount(this);
  if (n == 0)
    return 0;
  tEntry* p = (tEntry*)(this->mNeighborBegin_e40 + 0x20);
  for (u32 i = 0; i < n; i++) {
    if (p->mpObj_20 == (RefCnt*)a2)
      return this->FUN_00c15bd0(i, (u8)a3, a4) != 0;
    p = (tEntry*)((u8*)p + 0x24);
  }
  return 0;
}

// @ 0x00c15bd0
void* cSPCreatureBase::FUN_00c15bd0(u32 a2, u8 a3, u32 a4)
{
  (void)a4;
  RefCnt* pSaved = 0;
  u32 n = neighborCount(this);
  if (a2 < n) {
    tEntry* p = (tEntry*)(this->mNeighborBegin_e40 + a2 * 0x24);
    RefCnt* pObj = p->mpObj_20;
    if (pObj != 0) {
      ((ObjVtbl*)pObj)->SlotBc();          // 0xbc
      pSaved = pObj;
    }
    FUN_00c0fae0(p);
    if (pSaved != 0) {
      u8 r = FUN_00c15150_tc(this, 0, pSaved, 1);
      if (r == 0) {
        ((u32*)pSaved)[0x14] &= 0xfffffffb;      // +0x50
        ((u8*)pSaved)[0x70] = 1;
        ((u8*)pSaved)[0x71] = 0;
        if (((u8*)pSaved)[0x75] != 0) {
          void* q = FUN_00b3d310();
          if (q != 0) {
            FUN_00b3d310();
            FUN_00b453a0(q);
            FUN_00b54200(pSaved);
          }
        }
      }
      FUN_00d7d2c0(pSaved, this);
    }
  }
  if (a3 != 0) {
    u32 i = a2 + 1;
    if (i < neighborCount(this)) {
      u32 off = i * 0x24;
      do {
        if (i < neighborCount(this)) {
          tEntry* p = (tEntry*)(this->mNeighborBegin_e40 + off);
          if (p->mpObj_20 != 0 || p->mType_04 != 0) {
            FUN_00c13db0(a2, (void*)i);
            break;
          }
        }
        i++;
        off += 0x24;
      } while (i < neighborCount(this));
    }
  }
  if (pSaved != 0)
    ((ObjVtbl*)pSaved)->SlotC0();          // 0xc0
  return pSaved;
}

// @ 0x00c15dc0
void cSPCreatureBase::FUN_00c15dc0(float a2)
{
  float cur = this->mWaveF_e58;
  float dec = a2;
  if (cur < dec)
    dec = cur;
  this->mWaveF_e58 = cur - dec;
  if (((this->mFlags_b58 >> 9) & 1) != 0) {
    u8 msg[0x40];
    *(u32*)(msg + 0x30) = 0x7c7a52e;
    *(u32*)(msg + 0x00) = 0x13eb90c;
    u32 zero = 0;
    *(volatile u32*)(msg + 0x04) = zero;
    *(u32*)(msg + 0x00) = 0x13eb844;
    *(u32*)(msg + 0x38) = 0;
    *(float*)(msg + 0x08) = dec;
    SlotMessageVtbl* vt = (SlotMessageVtbl*)MessageServer();
    if (vt != 0) {
      vt->Dispatch(msg, 0, 0);
      SlotMessage_Destruct(msg);
    }
  }
}

// A generic IO stream object.
struct IOStreamVtbl {
  virtual void  pad00(); virtual void  pad04(); virtual void  pad08();
  virtual void  pad0c(); virtual void  pad10(); virtual void  pad14();
  virtual void* Slot18();                     // 0x18
  virtual void  Slot1c();                     // 0x1c
  virtual void* Slot20();                     // 0x20
  virtual void  pad24(); virtual void  pad28();
  virtual void* Slot2c(u32);                  // 0x2c
};
struct IOStream { IOStreamVtbl* mpVtbl; };
void __cdecl FUN_00c15f60_impl(IOStream* a1, void* a2);    // 0xc15f60

// The serialized record (stride 0x24) written by FUN_00c15e50.
struct SerRecord {
  u32   mU32_00;                              // 0x00
  u32   mU32_04;                              // 0x04
  u32   mU32_08;                              // 0x08
  u32   mU32_0c;                              // 0x0c
  u32   mU32_10;                              // 0x10
  u8    mB_14[0x18 - 0x14];
  u8    mbFlag18;                             // 0x18
};

// @ 0x00c15e50
void* __cdecl FUN_00c15e50_impl(void* a1, SerRecord* a2)
{
  u32 u = 0;
  if (*(void**)((u8*)a2 + 0x20) != 0)
    u = (u32)(SIZE_T)((ObjVtbl*)*(void**)((u8*)a2 + 0x20))->SlotB8(0x179c807);
  IOStream* s = (IOStream*)a1;
  s->mpVtbl->Slot2c(u);
  void* p;
  p = s->mpVtbl->Slot20();
  u32 v = a2->mU32_00;
  ((ObjVtbl*)p)->Slot18();  // stream writer slot
  EA_IO_WriteUint32(p, &v, 1, 0);
  p = s->mpVtbl->Slot20();
  v = a2->mU32_08;
  EA_IO_WriteUint32(p, &v, 1, 0);
  p = s->mpVtbl->Slot20();
  v = a2->mU32_04;
  EA_IO_WriteUint32(p, &v, 1, 0);
  p = s->mpVtbl->Slot20();
  v = a2->mU32_10;
  EA_IO_WriteUint32(p, &v, 1, 0);
  p = s->mpVtbl->Slot20();
  u32 b = (a2->mbFlag18 != 0) ? 1 : 0;
  EA_StreamWrite(p, (s32)&b, 1);
  return (void*)a1;
}

// @ 0x00c15f60
void __cdecl FUN_00c15f60_impl(IOStream* a1, void* a2)
{
  SerRecord* pBegin = (SerRecord*)(*(void**)a2);
  SerRecord* pEnd   = (SerRecord*)(*((void**)a2 + 1));
  u32 count = (u32)(((u8*)pEnd - (u8*)pBegin) / 0x24);
  void* p = a1->mpVtbl->Slot20();
  ((ObjVtbl*)p)->Slot18();
  EA_IO_WriteUint32(p, &count, 1, 0);
  for (SerRecord* it = pBegin; it != pEnd; it = (SerRecord*)((u8*)it + 0x24))
    FUN_00c15e50_impl(a1, it);
  a1->mpVtbl->Slot1c();
}

// @ 0x00c16100
u8 __cdecl FUN_00c16100_impl(void* a1)
{
  void** ppBase = (void**)a1;
  void** ppSlot = (void**)((u8*)a1 + 0x3c);
  if (*ppSlot == 0)
    return 0;
  void* p = ((ObjVtbl*)*ppSlot)->Slot0c(0xce9f6639);
  if (p == 0)
    return 0;
  ObjVtbl* po = (ObjVtbl*)p;
  if (po->Slot2c() != 0)                       // returns bool (char)
    return 0;
  if (((u8*)p)[0x135] == 0)
    return 0;
  s32 i = (s32)(SIZE_T)*ppBase;
  s32 end = (s32)(SIZE_T)ppBase[1] + i;
  u8 acc = 0;
  for (; i < end; i++) {
    void* pAnimWorld = *((void**)((u8*)p + 0xb54));
    if (pAnimWorld == 0)
      continue;
    void* pPart = (void*)FUN_009cab60(*((u32*)((u8*)pAnimWorld + 0x17c)), i);
    if (pPart == 0)
      continue;
    u8 b = 0;
    u32* p90 = *(u32**)((u8*)pPart + 0x90);
    if (p90 != 0)
      b = (u8)((p90[1] >> 0xf) & 1);
    if (*(u32*)((u8*)pPart + 0xa4) != 0) {
      u32* q = *(u32**)((u8*)pPart + 0xa4);
      if (q != 0) {
        void* r = ((ObjVtbl*)q)->Slot0c(0x1186577);
        if (r != 0)
          b |= *(u8*)((u8*)r + 0x75);
      }
    }
    acc |= b;
    if (b == 0)
      FUN_00c15150_tc(p, 0, (void*)i, 1);
  }
  return acc;
}

// Game-mode property manager (slot 0x24 reads a property).
struct PropsMgrVtbl {
  virtual void  pad00(); virtual void  pad04(); virtual void  pad08();
  virtual void  pad0c(); virtual void  pad10(); virtual void  pad14();
  virtual void  pad18(); virtual void  pad1c();
  virtual void  pad20();
  virtual u8    GetProperty(u32 id, void* out);   // 0x24
};

// A property object: +0x12 is a type tag (0xd == float), read via GetFloat.
struct Property {
  u8    pad00[0x12];
  u16   mType_12;                                 // 0x12
};

// @ 0x00c161f0
float __cdecl FUN_00c161f0_impl(cSPCreatureBase* self, float a2)
{
  void* gm = cSPGetCurrentGameMode(1);
  void* mgr = FUN_00b3d320(gm);
  PropsMgrVtbl* pm = (PropsMgrVtbl*)FUN_00b1daf0(mgr);

  float f1 = 0.5f;   // local to [esp+4]
  float f2 = 0.5f;   // local to [esp+8]
  float f3 = 0.5f;   // third prop

  if (pm != 0) {
    Property* prop = 0;
    if (pm->GetProperty(0x7422b3b, &prop) && prop->mType_12 == 0xd)
      f1 = *FUN_0041ea70(prop);
    Property* prop2 = 0;
    if (pm->GetProperty(0x7422b41, &prop2) && prop2->mType_12 == 0xd)
      f2 = *FUN_0041ea70(prop2);
    Property* prop3 = 0;
    if (pm->GetProperty(0x7422b47, &prop3) && prop3->mType_12 == 0xd)
      f3 = *FUN_0041ea70(prop3);
  }

  float local_10 = 100.0f;
  float v = f3 * a2;                    // xmm0
  float prod = v * f2 * f1;             // xmm4
  if (prod > self->mWaveF_e58)
    f1 = ((1.0f / f1) / f2) * self->mWaveF_e58;
  float clamp = f1;                     // xmm0 holds the clamp here
  float waveArg = clamp * f2 * f1;
  (void)local_10;
  self->FUN_00c15dc0(waveArg);
  return a2 - f1;
}

// @ 0x00c159c0
u8 cSPCreatureBase::FUN_00c159c0(u32 a2, u32 a3, u8 a4)
{
  u8 cVar1 = 0;
  if ((u32)((this->mNeighborEnd_e44 - this->mNeighborBegin_e40) / 0x24) <= a3)
    return 0;
  tEntry* pEntry = (tEntry*)(this->mNeighborBegin_e40 + a3 * 0x24);
  RefCnt* pObj = pEntry->mpObj_20;
  if (pObj != 0) {
    if (a4 == 0) {
      // fall through to the assign label
    } else {
      u32 r = FUN_00c0f620_();
      FUN_00c13db0(a3, (void*)r);
    }
  }
  {
    u8 doAssign = (pObj == 0) ? 1 : (a4 == 0);
    if (doAssign) {
      FUN_00c70110((void*)a2);
      cVar1 = 1;
    }
  }
  {
    tEntry* pe = (tEntry*)(this->mNeighborBegin_e40 + a3 * 0x24);
    u32 v = pe->mId_00;
    if (v == 0xffffffff)
      return cVar1;
    if (cVar1 != 0) {
      cVar1 = (u8)FUN_00c11f50(this, v, 0, a2, a2);
      if (cVar1 != 0) {
        u32 pGrasp = FUN_00c0dfb0_();
        void* pAnimWorld = this->mpAnimWorld_b54;
        u32* pArr = *(u32**)((u8*)pAnimWorld + 0x17c);
        u32 item = *(u32*)(*(u32*)((u8*)pArr + 0x2e4) + v * 700);
        FUN_00c0de60(this, item, pGrasp);
        return 1;
      }
    }
    return 0;
  }
}

// An ability record returned by SimCreature::GetAbility.
struct AbilityObj {
  u8  pad00[0x88];
  u32 mpEffect_88;      // 0x88 (parent effect object)
  u32 mEffectId_8c;     // 0x8c (effect resource id passed to EffectsMgr)
};

// The 0x34-byte body-effect entry stored in the block at creature+0xeb0.
struct BodyEntry {
  u8      mB_00;                          // 0x00
  u8      mB_01;                          // 0x01
  u8      pad02[0x04 - 0x02];
  u32     mU32_04;                        // 0x04
  float   mF_08;                          // 0x08
  float   mF_0c;                          // 0x0c
  float   mF_10;                          // 0x10
  float   mF_14;                          // 0x14
  float   mF_18;                          // 0x18
  float   mF_1c;                          // 0x1c
  u32     mU32_20;                        // 0x20
  float   mF_24;                          // 0x24
  RefCnt* mpTarget_28;                    // 0x28
  BodyEffect* mpEffect_2c;                // 0x2c
  u8      pad30[0x34 - 0x30];
};

// @ 0x00c15470
void cSPCreatureBase::FUN_00c15470(s32 a2, RefCnt* a3, u8 a4)
{
  u32 count = ((SimCreature*)this)->mpVtbl->GetAbilitiesCount();
  if ((u32)a2 >= count)
    return;
  BodyEntry* pBase = (BodyEntry*)this->mBodyBlock_eb0;
  u32 idx = 0;
  BodyEntry* e = pBase;
  for (; idx < 4; idx++) {
    if (e->mU32_04 == 0)
      break;
    e = (BodyEntry*)((u8*)e + 0x34);
  }
  if (idx == 4) {
    FUN_00c0f490(pBase);
    this->mAbilityDirty_c04[0] |= 2;
    e = pBase;
  } else {
    this->mAbilityDirty_c04[idx >> 5] |= (1u << (idx & 0x1f));
  }
  if (pBase == 0)
    return;
  void* pAbilityRaw = ((SimCreature*)this)->mpVtbl->GetAbility(a2);
  AbilityObj* pAbility = (AbilityObj*)pAbilityRaw;
  u32 pBoneless = (u32)(SIZE_T)pAbility;
  e->mU32_04 = 1;
  e->mU32_20 = a2;
  RefCnt* pOld = e->mpTarget_28;
  if (pOld != a3) {
    if (a3 != 0)
      ((ObjVtbl*)a3)->Slot60();
    e->mpTarget_28 = a3;
    if (pOld != 0)
      ((ObjVtbl*)pOld)->Slot64();
  }
  e->mB_00 = a4;
  u8* pSpat = (u8*)&this->mSpatial;
  e->mF_24 = 0.0f;
  Vec3 box[2];
  Vec3* pb = this->mSpatial.GetBox(box);
  float midX = (pb[1].x + pb[0].x) * 0.5f;
  float midY = (pb[1].y + pb[0].y) * 0.5f;
  float midZ = (pb[1].z + pb[0].z) * 0.5f;
  if (a2 == -1) {
    e->mF_24 = -this->mSpatial.GetRadius();
  } else {
    void* pAnimWorld = this->mpAnimWorld_b54;
    u32 pArr = *(u32*)((u8*)pAnimWorld + 0x17c);
    Vec3 t;
    FUN_0099c1a0(&t, (void*)(pArr + 0x3c), (Vec3*)(*(u32*)(pArr + 0x2e4) + a2 * 700 + 0x10));
    midX = t.x + *(float*)(pArr + 0x18);
    midY = t.y + *(float*)(pArr + 0x1c);
    midZ = t.z + *(float*)(pArr + 0x20);
    FUN_00c15150_tc(this, 0, (void*)(pAbility->mpEffect_88 + (u32)(SIZE_T)e), 0);
    FUN_00c14f70(this, (u32)(SIZE_T)pAbility, pAbility->mpEffect_88,
                 pAbility->mpEffect_88 + (u32)(SIZE_T)e);
  }
  e->mF_08 = midX;
  e->mF_0c = midY;
  e->mF_10 = midZ;
  e->mB_01 = 1;
  if (a3 == 0) {
    e->mF_14 = 1.0f;
    e->mF_18 = 1.0f;
    e->mF_1c = 1.0f;
  } else {
    Vec3 b2[2];
    Vec3* pb2 = this->mSpatial.GetBox(b2);
    float c0 = (pb2[1].x + pb2[0].x) * 0.5f;
    float c1 = (pb2[1].y + pb2[0].y) * 0.5f;
    float c2 = (pb2[1].z + pb2[0].z) * 0.5f;
    Vec3 c = { c0, c1, c2 };
    FUN_00c0ca00(&c, &c, 0.0f, &e->mF_14, gF_168d910);
  }
  EffectsMgr* mgr = (EffectsMgr*)(void*)EffectsManager();
  BodyEffect* pEff = e->mpEffect_2c;
  BodyEffect** ppEff = &e->mpEffect_2c;
  if (pEff != 0) {
    *ppEff = 0;
    ((ObjVtbl*)pEff)->Slot04();
  }
  u8 ok = mgr->Slot2c(pAbility->mEffectId_8c, 0, (void**)ppEff);
  (void)pSpat; (void)pBoneless;
  if (ok != 0) {
    Vec3 fwd = { e->mF_14, e->mF_18, e->mF_1c };
    float len2 = fwd.x * fwd.x + fwd.y * fwd.y + fwd.z * fwd.z;
    float inv = 1.0f / len2;
    Vec3 norm = { fwd.x * inv, fwd.y * inv, fwd.z * inv };
    Vec3 up = { midX, midY, midZ };
    Vec3 out;
    FUN_0069b440(&out, &norm, &up);
    ((ObjVtbl*)(*ppEff))->Slot18();
    ((ObjVtbl*)(*ppEff))->Slot08();
  }
}
