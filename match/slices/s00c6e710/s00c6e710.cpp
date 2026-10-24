// Slice s00c6e710 (batch gold6, worker 44). Region 0x00c6e710-0x00c6f660.
// Simulator::cGameData / SP::cHerd / cObjectInstanceInventoryItem cluster:
// cHerd::SetupEggs, cGameData::SetDefinitionID / cHerd::InitFromDefinition,
// a herd-slot placement helper, the inventory-item ctor/dtor and its
// serialize/deserialize + object-reference helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef          short s16;
typedef          char  s8;

// ---- external callees (address in comment) ------------------------------
void* __cdecl operator_new(u32 size, const char* file, int, int, int, int); // 0xf473a0
void  __cdecl operator_delete_array(void*);      // 0x00f47380
void* __cdecl SP_NounManager();                  // 0x00b3d300 SP::NounManager()
void* __cdecl SP_PlanetModel();                  // 0x00b3d350 SP::PlanetModel()
void* __cdecl FUN_00b3d300();                    // 0x00b3d300 (alias)
void* __cdecl FUN_00b3d350();                    // 0x00b3d350 (alias)
void* __cdecl FUN_00b20c60(void* self, u32 id);  // 0x00b20c60 cGameNounManager::CreateNoun
void  __cdecl FUN_00b225d0(void* self, void* noun); // 0x00b225d0 cGameNounManager::RemoveNoun
void* __cdecl FUN_00b20e40(void* self, void*, void*); // 0x00b20e40 cGameNounManager::CreateDebugNoun
void* __cdecl FUN_00b5f950(void* self, void*);    // 0x00b5f950 AutoRefCount::operator=<IWinText>
void  __cdecl FUN_00b06d90(void* self, u32 n);    // 0x00b06d90 RefVec::resize
void  __cdecl FUN_00babb70(void* end, u32 n, void* value); // 0x00babb70 vector::insert(end,n,value)
void* __cdecl FUN_00e25bd0(void* a, void* b);     // 0x00e25bd0 eastl::vector::erase
float __cdecl FUN_00c6a180(float x);              // 0x00c6a180 herd-scale helper
void  __cdecl FUN_00b18400(void* self, int, void*, void*, void*); // 0x00b18400 cGameData::Init
void* __cdecl FUN_00b9a750(u32 id, void* a, int b, int c, void* out); // 0x00b9a750 create-object helper
void* __cdecl FUN_00401090(u32 a, u32 b);         // 0x00401090 GetSetting9
void* __cdecl FUN_004e0050(void* self, u32 a);    // 0x004e0050 SpeciesManager::GetSpeciesArchetype
void* __cdecl FUN_00c6e200(void* self, void*, int); // 0x00c6e200 cHerd::UpdateFromArchetype
void  __cdecl FUN_004e3e10(void* self, void* value); // 0x004e3e10 vector<Key>::DoInsertValue
float __cdecl FUN_00b7ef70(void* self, void* pos);  // 0x00b7ef70 cPlanetModel::GetRadiusAt
float __cdecl FUN_00b7f250(void* self, void* out, void* dir, void* up); // 0x00b7f250 BuildSurfaceOrientation2
float __cdecl FUN_00b7f190(void* self, void* out, void* pos); // 0x00b7f190 BuildSurfaceOrientation
void* __cdecl FUN_00b81780(void* self, void* out, void* pos, void* , void* ); // 0x00b81780 MakeRandomWorldPosition
float __cdecl FUN_00b82970(void* self, void* pos);  // 0x00b82970 cPlanetModel::SnapB
void* __cdecl FUN_00d539d0();                     // 0x00d539d0 SP::cPosseSimulator::Instance
s32   __cdecl FUN_00d52df0(void* self);           // 0x00d52df0 posse max-eggs
float __cdecl FUN_007dcb00(float* out, float* a, float* b); // 0x007dcb00 mat3 mul
float __cdecl FUN_0059aed0(void* a, void* b, void* c);      // 0x0059aed0 mat4 mul
void* __cdecl FUN_00c87660(void* self);           // 0x00c87660 cSPSpaceInventoryItem ctor
void* __cdecl FUN_00c87770(void* self);           // 0x00c87770 cSPSpaceInventoryItem dtor
bool  __cdecl FUN_00c87580(void* self);           // 0x00c87580 serialize helper
bool  __cdecl FUN_00c879a0(void* self);           // 0x00c879a0 deserialize helper
bool  __cdecl FUN_00e3aa70(void* stream, const u32* value, int count, int); // 0x00e3aa70 IO::WriteUint32
bool  __cdecl FUN_00e3a780(void* stream, void* out, int count, int);        // 0x00e3a780 IO::ReadInt32
void* __cdecl FUN_00692f90(void* self, void* a, void* b, int c); // 0x00692f90 cVarListSerializer ctor
bool  __cdecl FUN_00692900(void* self, void* stream);            // 0x00692900 Serialize (write)
bool  __cdecl FUN_00693e10(void* self, void* stream);            // 0x00693e10 Serialize (read)

// ---- globals (named via typed accessors) -------------------------------
extern u32   DAT_016dc794;   // (unused placeholder)
extern float DAT_01485720;   // _HK_REAL_ONE = 1.0f
extern float DAT_01485378;   // _HK_REAL_ZERO = 0.0f
extern float DAT_0140f334;   // 64.0f
extern float DAT_0140e968;   // 0.015625f
extern float DAT_01471064;   // 0.5f
extern float DAT_01486374;   // 0.8f
extern float DAT_01693eac;   // 2*pi / segment
extern float DAT_01486110;   // MakeRandomWorldPosition radius
extern float DAT_01470f1c;   // MakeRandomWorldPosition angle
extern float DAT_01485378b;  // (alias)
extern float DAT_015778b4;   // half-segment sweep
extern float DAT_015778b8, DAT_015778bc, DAT_015778c0; // row0 basis
extern float DAT_015778c4, DAT_015778c8, DAT_015778cc; // row1 basis
extern u8    DAT_014718b8[4]; // axis-permutation table (bytes)
extern u32   DAT_01693ea0;    // up-vector seed
extern u32   DAT_016dd0c0;    // (unused)

// ======================================================================
// 0x00c6e710 - SP::cHerd::SetupEggs. Maintains the herd's noun vector
// (mNouns at +0x54..+0x58) to hold exactly `count` alive egg nouns.
// `this` in ecx, one stack arg (count); `ret 4`.
// ======================================================================

// @ 0x00c6e710
void __fastcall FUN_00c6e710(void* self, void* /*edx*/, u32 count) {
  char* p = (char*)self;
  void* mgr = SP_NounManager();
  s32 cur = (s32)(*(u32**)(p + 0x58) - *(u32**)(p + 0x54)) >> 2;
  u32 i = count;
  (void)cur;

  if (cur < (s32)count) {
    char* arche = *(char**)(p + 0xa4);
    float scale = FUN_00c6a180(
        *(float*)(arche + 0x554) * *(float*)(arche + 0x554) +
        *(float*)(arche + 0x558) * *(float*)(arche + 0x558) +
        *(float*)(arche + 0x55c) * *(float*)(arche + 0x55c));
    (void)scale;
    FUN_00b06d90(p + 0x54, count);
    if (cur < (s32)count) {
      u32 idx = (u32)cur;
      do {
        char* noun = (char*)FUN_00b20c60(mgr, 0x02a034cd);
        if (noun != 0) {
          ((void(__thiscall*)(void*))(*(void***)noun)[0 / 4])(noun);
        }
        // +0x1f4 = ref to owning herd
        void* oldHerd = *(void**)(noun + 0x1f4);
        if (p != oldHerd) {
          ((void(__thiscall*)(void*))(*(void***)p)[0 / 4])(p);
          *(void**)(noun + 0x1f4) = p;
          if (oldHerd != 0) {
            ((void(__thiscall*)(void*))(*(void***)oldHerd)[4 / 4])(oldHerd);
          }
        }
        // +0x220 = egg scale; +0x34 = transform whose vtable slot 0x40 sets it
        *(float*)(noun + 0x220) = scale;
        ((void(__thiscall*)(void*, float))(*(void***)(noun + 0x34))[0x40 / 4])(noun + 0x34, scale);
        u32* vec = *(u32**)(p + 0x54);
        void* oldSlot = (void*)vec[idx];
        if (noun != oldSlot) {
          ((void(__thiscall*)(void*))(*(void***)noun)[0 / 4])(noun);
          vec[idx] = (u32)noun;
          if (oldSlot != 0) {
            ((void(__thiscall*)(void*))(*(void***)oldSlot)[4 / 4])(oldSlot);
          }
        }
        ((void(__thiscall*)(void*))(*(void***)noun)[4 / 4])(noun);
        cur++;
        idx++;
      } while (cur < (s32)count);
      return;
    }
  } else if ((s32)count < cur) {
    do {
      char* noun = *(char**)(*(u32**)(p + 0x54) + i * 4);
      // +0x1f4 herd-ref, +0x218 secondary ref
      void* r1 = *(void**)(noun + 0x1f4);
      if (r1 != 0) {
        *(u32*)(noun + 0x1f4) = 0;
        ((void(__thiscall*)(void*))(*(void***)r1)[4 / 4])(r1);
      }
      void* r2 = *(void**)(noun + 0x218);
      if (r2 != 0) {
        *(u32*)(noun + 0x218) = 0;
        ((void(__thiscall*)(void*))(*(void***)r2)[4 / 4])(r2);
      }
      FUN_00b225d0(mgr, noun);
      i++;
    } while ((s32)i < cur);
    u32* vec = *(u32**)(p + 0x54);
    u32* end = *(u32**)(p + 0x58);
    if ((u32)((end - vec) >> 2) < count) {
      u32 n = count - (u32)((end - vec) >> 2);
      u32 zero = 0;
      FUN_00babb70(end, n, &zero);
      return;
    }
    FUN_00e25bd0(vec + count, end);
  }
}

// ======================================================================
// 0x00c6e8f0 - Simulator::cGameData::SetDefinitionID (PDB candidate
// SP::cHerd::InitFromDefinition). `this` in ecx, three stack args
// (definition view, key vector, owner); `ret 0xc`.
// ======================================================================

// @ 0x00c6e8f0
u8 __fastcall FUN_00c6e8f0(void* self, void* /*edx*/,
                           void* def, void* keys, char* owner) {
  char* p = (char*)self;
  float p0, p1, p2;
  float* src = (float*)((owner != 0) ? owner : (p + 0x34));
  p0 = src[0]; p1 = src[1]; p2 = src[2];
  float a0 = (p0 < 0.0f) ? -p0 : p0;
  float a1 = (p1 < 0.0f) ? -p1 : p1;
  float a2 = (p2 < 0.0f) ? -p2 : p2;

  // Choose the dominant axis and quantise the other two into [0,127].
  s32 q0, q1; u32 axis;
  if (a0 >= a2 && a1 >= a2) {
    q0 = (s32)((p0 / p2 + 1.0f) * 64.0f);
    q1 = (s32)((p1 / p2 + 1.0f) * 64.0f);
    axis = (p2 < 0.0f) ? 1u : 0u;
  } else if (a0 >= a1) {
    q0 = (s32)((p2 / p1 + 1.0f) * 64.0f);
    q1 = (s32)((p0 / a1 + 1.0f) * 64.0f);
    axis = (p1 < 0.0f) ? 5u : 4u;
  } else {
    q0 = (s32)((p1 / p0 + 1.0f) * 64.0f);
    q1 = (s32)((p2 / a0 + 1.0f) * 64.0f);
    axis = (p0 < 0.0f) ? 3u : 2u;
  }
  if (q0 == 0x80) q0 = 0x7f;
  if (q1 == 0x80) q1 = 0x7f;

  // Turn the quantised pair back into a unit direction on the chosen axis.
  u32 off = (axis >> 1) * 4;
  const u8* perm = DAT_014718b8 + off;
  float c0 = (float)q0;
  float c1 = (float)q1;
  float v = (c0 + 0.5f) * 0.015625f - 1.0f;
  float w = (c1 + 0.5f) * 0.015625f - 1.0f;
  float inv = 1.0f / (float)sqrtf(v * v + w * w + 1.0f);
  float sgn = (axis & 1) ? -v : v;
  float dir[4];
  dir[perm[0]] = sgn * inv;
  dir[perm[1]] = w * inv;
  dir[perm[2]] = sgn;
  (void)sgn;
  // Re-normalise the two quantised components by the unit length.
  dir[0] = v * inv;
  dir[1] = w * inv;

  // Scale the orientation vector by the planet radius at that direction.
  float local[3];
  local[0] = dir[0];
  local[1] = dir[1];
  local[2] = dir[2];
  void* pm = FUN_00b3d350();
  float radius = FUN_00b7ef70(pm, local);
  local[0] = local[0] * radius;
  local[1] = local[1] * radius;
  local[2] = local[2] * radius;

  extern u8 FUN_00b18400_ret(void);
  u8 ok = ((u8(__thiscall*)(void*, void*, void*, void*))FUN_00b18400)(
      self, def, keys, local);
  if (ok == 0) return ok;

  void* defv = def;
  *(float*)(p + 0x34) = local[0];
  *(float*)(p + 0x38) = local[1];
  *(float*)(p + 0x3c) = local[2];
  *(u32*)(p + 0x8c) = 0;
  *(u32*)(p + 0xf0) = 0;

  char* k = (char*)keys;
  if (k != 0) {
    *(u32*)(p + 0xf4) = *(u32*)(k + 0xc);
    *(u32*)(p + 0x15c) = *(u32*)(k + 0x10);
    if (*(u32*)(k + 0x14) == 0 && defv != 0) {
      void* nm = FUN_00b3d300();
      void* dbg = FUN_00b20e40(nm, defv, local);
      FUN_00b5f950(p + 0x160, dbg);
    }
    *(u32*)(p + 0x8c) = *(u32*)k;
    if (*(float*)(k + 0x18) > 0.0f) *(float*)(p + 0x150) = *(float*)(k + 0x18);
    if (*(float*)(k + 0x1c) > 0.0f) *(float*)(p + 0x154) = *(float*)(k + 0x1c);
    if (*(float*)(k + 0x20) > 0.0f) *(float*)(p + 0x158) = *(float*)(k + 0x20);
    if (*(float*)(k + 0x24) > 0.0f) *(float*)(p + 0x108) = *(float*)(k + 0x24);
    u32 v0 = *(u32*)(k + 0x28);
    u32 v1 = *(u32*)(k + 0x2c);
    *(u32*)(p + 0x120) = v0;
    *(u32*)(p + 0x124) = v1;
    if (v0 == 0 && v1 == 0) *(u32*)(p + 0x124) = 5;
  }

  // Build the object from the definition view.
  u32 defArg = *(u32*)((char*)def + 8);
  u32 idA = *(u32*)(p + 0x8c);
  u8 localFlag = 0;
  void* obj = FUN_00b9a750(idA, (void*)defArg, 0, 0, &localFlag);
  *(void**)(p + 0xa4) = obj;
  void* arch = FUN_004e0050(FUN_00401090(defArg, 0), 0);
  FUN_00c6e200(self, arch, 0);
  if (*(void**)(p + 0xa4) == 0) return 0;

  char* o = *(char**)(p + 0xa4);
  *(u32*)(p + 0x98) = *(u32*)(o + 0x504);
  *(u32*)(p + 0x9c) = *(u32*)(o + 0x508);
  *(u32*)(p + 0xa0) = *(u32*)(o + 0x50c);
  *(u32*)(p + 0x88) = *(u32*)((char*)def + 8);
  ((void(__thiscall*)(void*))(*(void***)p)[0x54 / 4])(p);
  void* dbg = *(void**)(p + 0x160);
  *(u8*)(p + 0x218) = 0;
  if (dbg != 0) *(u8*)((char*)dbg + 0xa9) = 0;

  // Append the archetype key list to the mKeys vector at +0xa8.
  char* src2 = *(char**)(p + 0xa4);
  u32* beg = *(u32**)(p + 0xa8);
  u32* end = *(u32**)(p + 0xac);
  src2 += 0x504;
  if ((u32)end < *(u32*)(p + 0xb0)) {
    *(u32*)(p + 0xac) = (u32)(end + 3);
    if (end != 0) {
      end[0] = *(u32*)(src2 + 0);
      end[1] = *(u32*)(src2 + 4);
      end[2] = *(u32*)(src2 + 8);
    }
  } else {
    FUN_004e3e10(p + 0xa8, src2);
  }
  (void)beg;

  char* keyList = (char*)keys;
  u32 n = (u32)((*(u32**)(keyList + 0x3c8) - *(u32**)(keyList + 0x3c4)) >> 2);
  u32 idx = 0;
  if (n > 0) {
    do {
      u32 kA = *(u32*)(p + 0x88);
      u32 kB = *(u32*)(p + 0x8c);
      u8 flag2 = 0;
      void* obj2 = FUN_00b9a750(kB, (void*)kA, (int)(idx + 1), *(u32*)(p + 0xa4), &flag2);
      if (obj2 == 0) {
        *(u8*)(p + 0x85) = 0;
        break;
      }
      u32* e2 = *(u32**)(p + 0xac);
      char* s3 = (char*)obj2 + 0x504;
      if ((u32)e2 < *(u32*)(p + 0xb0)) {
        *(u32*)(p + 0xac) = (u32)(e2 + 3);
        if (e2 != 0) {
          e2[0] = *(u32*)(s3 + 0);
          e2[1] = *(u32*)(s3 + 4);
          e2[2] = *(u32*)(s3 + 8);
        }
      } else {
        FUN_004e3e10(p + 0xa8, s3);
      }
      idx++;
    } while (idx < n);
  }
  return 1;
}

// ======================================================================
// 0x00c6ee40 - herd "eggs visible" toggle + placement. `this` in ecx,
// two stack args (bool visible, float* pos); `ret 8`.
// ======================================================================

// @ 0x00c6ee40
void __fastcall FUN_00c6ee40(void* self, void* /*edx*/, u8 visible, float* pos) {
  char* p = (char*)self;
  float* bp = pos;
  if (visible == *(u8*)(p + 0x198)) return;
  SP_NounManager();
  *(u8*)(p + 0x198) = visible;
  *(u8*)(p + 0xfc) = 1;
  if (*(u8*)(p + 0x84) == 0) {
    if (visible == 0) { FUN_00c6e710(p, 0, 0); return; }
    FUN_00c6e710(p, 0, 1);
    char* t = *(char**)(p + 0x54);
    char* n0 = *(char**)(t);
    *(u32*)(n0 + 0x1e8) = 0;
    *(u8*)(n0 + 0x1ec) = 1;
    ((void(__thiscall*)(void*, float*))(*(void***)(n0 + 0x34))[0x38 / 4])(n0 + 0x34, bp);
    char* dbg = *(char**)(p + 0x160);
    if (dbg == 0) {
      float d[3];
      void* pm = (void*)FUN_00b3d350();
      FUN_00b7f190(pm, d, bp);
      ((void(__thiscall*)(void*, float*))(*(void***)(n0 + 0x34))[0x3c / 4])(n0 + 0x34, d);
      return;
    }
    void* v = ((void*(__thiscall*)(void*))(*(void***)(dbg + 0x34))[0x30 / 4])(dbg + 0x34);
    ((void(__thiscall*)(void*, void*))(*(void***)(n0 + 0x34))[0x3c / 4])(n0 + 0x34, v);
    return;
  }
  if (visible == 0) { FUN_00c6e710(p, 0, 0); return; }

  s32 adv = FUN_00d52df0(FUN_00d539d0());
  s32 total = adv + 1;
  FUN_00c6e710(p, 0, (u32)total);

  // Two rotation matrices around the sweep angle, multiplied into bp.
  float sweep = DAT_015778b4 * 0.5f;
  float sn = (float)sinf(sweep);
  float cs = (float)cosf(sweep);
  float row0a[3] = { sn, sn * DAT_015778bc, sn * DAT_015778b8 };
  (void)row0a;
  float M0[9];
  M0[0] = cs;
  M0[1] = sn * DAT_015778b8;
  M0[2] = sn * DAT_015778bc;
  M0[3] = sn * DAT_015778c0;
  M0[4] = 0.0f;
  (void)cs;
  float M1[9];
  float sn2 = (float)sinf(sweep);
  float cs2 = (float)cosf(sweep);
  M1[0] = cs2;
  M1[1] = sn2 * DAT_015778c4;
  M1[2] = sn2 * DAT_015778c8;
  M1[3] = sn2 * DAT_015778cc;
  float tmp[9];
  FUN_007dcb00(tmp, M0, M1);
  float p3[3];
  FUN_0059aed0(p3, bp, tmp);
  float up[3];
  float pm2 = (void*)FUN_00b3d350() ? 0.0f : 0.0f;
  (void)pm2;
  void* pl = (void*)FUN_00b3d350();
  FUN_00b7f250(pl, up, bp, p3);

  float axis[3];
  FUN_0059aed0(axis, &DAT_01693ea0, up);
  float inv = 1.0f /
      (float)sqrtf(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
  axis[0] *= inv; axis[1] *= inv; axis[2] *= inv;
  float invp = 1.0f /
      (float)sqrtf(bp[0] * bp[0] + bp[1] * bp[1] + bp[2] * bp[2]);
  float upn[3] = { bp[0] * invp, bp[1] * invp, bp[2] * invp };

  s32 i = 0;
  s32 ringCount = 1;
  s32 ringIdx = 0;
  s32 seg = 6;
  if (total <= 0) return;
  do {
    float base[3] = { bp[0], bp[1], bp[2] };
    if (i > 0) {
      s32 act = seg;
      if (seg <= ringIdx) {
        ringCount++;
        act = seg + 6;
        ringIdx = 0;
      }
      float r = (float)ringCount * DAT_01486374;
      float ang = ((float)ringIdx * DAT_01693eac / (float)act) * DAT_01471064;
      float sa = (float)sinf(ang);
      float ca = (float)cosf(ang);
      float upscaled[3] = { upn[0] * sa, upn[1] * sa, upn[2] * sa };
      (void)ca;
      float tmpv[3];
      FUN_0059aed0(tmpv, axis, upscaled);
      base[0] += tmpv[0] * r;
      base[1] += tmpv[1] * r;
      base[2] += tmpv[2] * r;
      ringIdx++;
      seg = act;
    }
    void* pl2 = (void*)FUN_00b3d350();
    float rnd[3];
    FUN_00b81780(pl2, rnd, base, (void*)0x40000000, (void*)0x40a00000);
    float delta[3] = { rnd[0] - base[0], rnd[1] - base[1], rnd[2] - base[2] };
    float ori[9];
    FUN_00b7f250(pl2, ori, base, delta);
    char* noun = *(char**)(*(u32**)(p + 0x54) + i * 4);
    *(u32*)(noun + 0x1e8) = 0;
    *(u8*)(noun + 0x1ec) = 1;
    FUN_00b82970((void*)FUN_00b3d350(), base);
    ((void(__thiscall*)(void*, float*))(*(void***)(noun + 0x34))[0x38 / 4])(noun + 0x34, base);
    ((void(__thiscall*)(void*, float*))(*(void***)(noun + 0x34))[0x3c / 4])(noun + 0x34, ori);
    i++;
  } while (i < total);
}

// ======================================================================
// 0x00c6f3d0 - cObjectInstanceInventoryItem constructor (this in ecx).
// ======================================================================

// @ 0x00c6f3d0
void* __fastcall FUN_00c6f3d0(void* self, void* /*edx*/) {
  char* p = (char*)self;
  ((void*(__thiscall*)(void*))FUN_00c87660)(self);   // base ctor
  *(u32*)(p + 0x00) = 0x01472008;     // vtbl cObjectInstanceInventoryItem
  *(u32*)(p + 0x08) = 0x01472000;
  *(u32*)(p + 0x0c) = 0x01471fdc;
  *(u32*)(p + 0x7c) = 0;              // mObject
  *(u8*)(p + 0x1c) = 1;              // mbIsUnique
  *(u32*)(p + 0x14) = 8;             // mItemType = ObjectInstance
  return self;
}

// ======================================================================
// 0x00c6f470 - serialize: version tag then cVarListSerializer round trip.
// `this` in ecx, one stack arg; `ret 4`.
// ======================================================================

// @ 0x00c6f470
u8 __fastcall FUN_00c6f470(void* self, void* /*edx*/, void* stream) {
  char* p = (char*)self;
  char* a = (char*)((void*(__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
  u32 tag = 0x073905ae;
  void* s = ((void*(__thiscall*)(void*))(*(void***)a)[0x18 / 4])(a);
  FUN_00e3aa70(s, &tag, 1, 0);
  u8 ok = ((u8(__thiscall*)(void*, void*))FUN_00c87580)(self, stream);
  u32 ser[645];   // cVarListSerializer, 0xa14 bytes
  ((void*(__thiscall*)(void*, void*, void*, int))FUN_00692f90)(
      ser, p - 0xc, (void*)0x01578618, 0x1a80d26);
  u8 ok2 = ((u8(__thiscall*)(void*, void*))FUN_00692900)(ser, stream);
  return (ok2 != 0 && ok != 0);
}

// ======================================================================
// 0x00c6f500 - deserialize counterpart of 0x00c6f470; `ret 4`.
// ======================================================================

// @ 0x00c6f500
u8 __fastcall FUN_00c6f500(void* self, void* /*edx*/, void* stream) {
  char* p = (char*)self;
  char* a = (char*)((void*(__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
  void* s = ((void*(__thiscall*)(void*))(*(void***)a)[0x18 / 4])(a);
  u32 tag;
  FUN_00e3a780(s, &tag, 1, 0);
  u8 ok = ((u8(__thiscall*)(void*, void*))FUN_00c879a0)(self, stream);
  u32 ser[645];   // cVarListSerializer, 0xa14 bytes
  ((void*(__thiscall*)(void*, void*, void*, int))FUN_00692f90)(
      ser, p - 0xc, (void*)0x01578618, 0x1a80d26);
  u8 ok2 = ((u8(__thiscall*)(void*, void*))FUN_00693e10)(ser, stream);
  return (ok2 != 0 && ok != 0);
}

// ======================================================================
// 0x00c6f590 - cObjectInstanceInventoryItem virtual destructor. `this`
// in ecx, u8 delete-flag on the stack; `ret 4`.
// ======================================================================

// @ 0x00c6f590
void* __fastcall FUN_00c6f590(void* self, void* /*edx*/, u32 flags) {
  char* p = (char*)self;
  *(u32*)(p + 0x00) = 0x01472008;
  *(u32*)(p + 0x08) = 0x01472000;
  *(u32*)(p + 0x0c) = 0x01471fdc;
  void* obj = *(void**)(p + 0x7c);
  if (obj != 0) {
    ((void(__thiscall*)(void*))(*(void***)obj)[4 / 4])(obj);
  }
  ((void*(__thiscall*)(void*))FUN_00c87770)(self);
  if (flags & 1) {
    operator_delete_array(self);
  }
  return self;
}

// ======================================================================
// 0x00c6f5e0 - set the referenced cGameData object, clearing its
// "destroyed" flag. `this` in ecx, one stack arg; `ret 4`.
// ======================================================================

// @ 0x00c6f5e0
void __fastcall FUN_00c6f5e0(void* self, void* /*edx*/, void* obj) {
  char* p = (char*)self;
  void* old = *(void**)(p + 0x7c);
  if (obj != old) {
    if (obj != 0) {
      ((void(__thiscall*)(void*))(*(void***)obj)[0 / 4])(obj);
    }
    *(void**)(p + 0x7c) = obj;
    if (old != 0) {
      ((void(__thiscall*)(void*))(*(void***)old)[4 / 4])(old);
    }
  }
  if (obj != 0) {
    char* gd = (char*)((void*(__thiscall*)(void*, u32))(*(void***)obj)[0xc / 4])(
        obj, 0x01186577);
    if (gd != 0) {
      *(u8*)(gd + 0x75) = 0;
      u32* q = (u32*)((void*(__thiscall*)(void*))(*(void***)gd)[0xac / 4])(gd);
      if (q != 0) {
        q[1] &= ~1u;
        ((void(__thiscall*)(void*, int))(*(void***)q)[0x16c / 4])(q, 0);
      }
    }
  }
  *(u32*)(p + 0x10) = 1;
}

// ======================================================================
// 0x00c6f660 - clear the referenced cGameData object, releasing the ref.
// `this` in ecx, no stack args.
// ======================================================================

// @ 0x00c6f660
void* __fastcall FUN_00c6f660(void* self, void* /*edx*/) {
  char* p = (char*)self;
  void* result = 0;
  if (*(void**)(p + 0x7c) != 0) {
    if (*(void**)(p + 0x7c) != 0) {
      void* obj = *(void**)(p + 0x7c);
      char* gd = (char*)((void*(__thiscall*)(void*, u32))(*(void***)obj)[0xc / 4])(
          obj, 0x01186577);
      if (gd != 0) {
        *(u8*)(gd + 0x75) = 1;
        u32* q = (u32*)((void*(__thiscall*)(void*))(*(void***)gd)[0xac / 4])(gd);
        if (q != 0) {
          q[1] |= 1u;
          ((void(__thiscall*)(void*, int))(*(void***)q)[0x16c / 4])(q, 1);
        }
      }
    }
    result = *(void**)(p + 0x7c);
    *(u32*)(p + 0x7c) = 0;
    if (result != 0) {
      ((void(__thiscall*)(void*))(*(void***)result)[4 / 4])(result);
    }
    *(u32*)(p + 0x10) = 0;
  }
  return result;
}
