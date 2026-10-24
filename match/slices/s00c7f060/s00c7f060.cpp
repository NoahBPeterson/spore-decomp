// Slice s00c7f060 - cSimPlanetLowLOD terraform / planet-style cluster.
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

#define F10 float

#include <math.h>

// vtable-call signature typedefs (all thiscall)
typedef void   (__thiscall *TFv)(void*);
typedef void   (__thiscall *TFvi)(void*, int);
typedef void   (__thiscall *TFvp)(void*, void*);
typedef s32    (__thiscall *TFi)(void*);
typedef u32    (__thiscall *TFu)(void*);
typedef u8     (__thiscall *TFb)(void*);
typedef void*  (__thiscall *TFp)(void*);
typedef float* (__thiscall *TFfp)(void*);
typedef void*  (__thiscall *TFpu)(void*, u32);
typedef u8     (__thiscall *TFbup)(void*, u32, void*);

// ---- external callees ----------------------------------------------------
void*  __cdecl FUN_00b3d350(void);   // 0x00b3d350 SP::PlanetModel
void*  __cdecl FUN_00b3d440(void);   // 0x00b3d440
void   __cdecl FUN_00f929c0(int a, s32 b, s32 c, s32 d, void* e, void* f); // 0x00f929c0
s32    __fastcall FUN_00b7e3e0(void* self, void* dummy, void* a); // 0x00b7e3e0 (thiscall)
void*  __cdecl FUN_00feb9f0(void);   // 0x00feb9f0 SP::GetMissionManager
void*  __cdecl FUN_00fedd50(void* self); // 0x00fedd50 cSPMissionManager::GetMissionList (thiscall)
void*  __cdecl FUN_00970b30(void* self); // 0x00970b30 cSPMission::GetTargetPlanet (thiscall)
void*  __cdecl FUN_01021260(void);   // 0x01021260
u8     __cdecl FUN_01044640(void);   // 0x01044640
void   __cdecl FUN_01041c50(void* a, u32 b, int c); // 0x01041c50
void*  __cdecl FUN_00fc1fa0(int a);  // 0x00fc1fa0 SP::GetTerraformRadius
void   __cdecl FUN_00fc20e0(void* out, float a, float b); // 0x00fc20e0 TerraBlend
void*  __cdecl FUN_01049a10(void);   // 0x01049a10
void*  __cdecl FUN_00b3d430(void);   // 0x00b3d430 SP::TerraformingManager
void*  __cdecl FUN_01049dd0(void* self); // 0x01049dd0 GetBullseyeTimeScale (thiscall)
void*  __cdecl FUN_01049d30(void* self); // 0x01049d30 GetBullseyeMarbleMass (thiscall)
void*  __cdecl FUN_01049e20(void* self); // 0x01049e20 GetBullseyeMarbleDragCoeff (thiscall)
void*  __cdecl FUN_01049d80(void* self); // 0x01049d80 GetBullseyeMarbleDamping (thiscall)
void*  __cdecl FUN_01049b00(void* self); // 0x01049b00 GetWaterDivergenceRate (thiscall)
void*  __cdecl FUN_01049b50(void* self); // 0x01049b50 GetAtmosphereDivergenceRate (thiscall)
void*  __cdecl FUN_01049ba0(void* self); // 0x01049ba0 GetBullseyeSteepnessPower (thiscall)
void*  __cdecl FUN_01049c90(void* self); // 0x01049c90 GetFloraBullseyeRadius (thiscall)
void*  __cdecl FUN_01049ce0(void* self); // 0x01049ce0 GetFloraBullseyeForceScalar (thiscall)
s32    __cdecl FUN_00bbc670(void* self, void* a); // 0x00bbc670 TerraformingManager::F670 (thiscall, returns count)
float  __cdecl FUN_011e08f0(float base, float exp); // 0x011e08f0 _CIpow (x87 st0/st1)
s32    __cdecl FUN_00b8dab0(void* self); // 0x00b8dab0
void*  __cdecl FUN_00b8de30(void* self); // 0x00b8de30 BioProtectorSort::operator()
void*  __cdecl FUN_00b1fdb0(void* self); // 0x00b1fdb0 cGameNounManager::GetAvatar
void*  __cdecl FUN_00b3d2a0(void);   // 0x00b3d2a0 SP::StarManager
void*  __cdecl FUN_00885c90(void* self); // 0x00885c90
void*  __cdecl FUN_00c7eaf0(void* self, void* key); // 0x00c7eaf0 (thiscall)
void   __cdecl FUN_00705250(void* dst, void* src, void* out); // 0x00705250 copy
void   __cdecl FUN_00f47380(void* p); // 0x00f47380 operator_delete_array
void   __cdecl FUN_009a9600(void* p); // 0x009a9600 DoNukeSubtree (thiscall ecx=p)
struct HtC { void DoFreeNodes(void* a, void* b); }; // FUN_007611f0 _ht_DoFreeNodes (thiscall)
struct FindC { void* Find(void* key); };            // FUN_00c7eaf0 (thiscall, ecx=container)
struct MMC { void* GetMissionList(); };             // FUN_00fedd50 (thiscall, ecx=mission manager)
struct MissionC { void* GetTargetPlanet(); };       // FUN_00970b30 (thiscall, ecx=mission)
struct NukeC { void DoNukeSubtree(void* node); };   // FUN_009a9600 DoNukeSubtree (thiscall)
struct GonzagoC { void Dtor(); };                   // FUN_00b638b0 ~cGonzagoTimer (thiscall)
struct GameDataC { void Dtor(); };                  // FUN_00b184c0 ~cGameData (thiscall)
void   __cdecl FUN_00b638b0(void* self); // 0x00b638b0 cGonzagoTimer::~cGonzagoTimer
void   __cdecl FUN_00571db0(void* a, void* b, void* c, void* d, void* e); // 0x00571db0 RemoveHandler
void   __cdecl FUN_00b184c0(void* self); // 0x00b184c0 cGameData::~cGameData

// ---- modeled thiscall targets -------------------------------------------
struct AMdC { u8 F24(u32 key, void* out); };  // property-list vtable slot 0x24
struct TuneC {
  float GetBullseyeTimeScale();
  float GetBullseyeMarbleMass();
  float GetBullseyeMarbleDragCoeff();
  float GetBullseyeMarbleDamping();
  float GetWaterDivergenceRate();
  float GetAtmosphereDivergenceRate();
  float GetBullseyeSteepnessPower();
  float GetFloraBullseyeRadius();
  float GetFloraBullseyeForceScalar();
};
struct TerraMgrC { u8 F670(void* a); void* F870(void* out, int i, u32 key, void* planet); }; // FUN_00bbc670 / FUN_00bbc870

// ======================================================================
// 0x00c7f060
// ======================================================================
// @ 0x00c7f060
void __fastcall FUN_00c7f060(void* self) {
  float fTop;
  void* pm = FUN_00b3d350();
  if (*(void**)((char*)pm + 0x24) == 0) return;
  {
    void* obj = *(void**)((char*)pm + 0x24);
    float* f = (float*)((TFp)(*(void***)obj)[0xc / 4])(obj);
    fTop = f[0x3c / 4];
    {
      s32 i7 = 0, i9 = 0, i8 = 0;
      float* pu = (float*)((char*)self + 0x50);
      for (;;) {
        float a, b;
        FUN_00f929c0(2, i7, i9, i8, &a, &b);
        if (pu == 0) break;
        if (fTop <= a) {
          if (fTop <= b) pu[0] = 2.0f;
          else pu[0] = 1.0f;
        } else {
          pu[0] = 3.0f;
        }
        i9++;
        pu = (float*)((char*)pu + 0x54);
        if (i9 < 4) continue;
        i9 = 0;
        i8++;
        if (i8 < 4) continue;
        i8 = 0;
        i7++;
        if (i7 >= 6) break;
      }
    }
  }
  {
    void* mgr = FUN_00b3d440();
    void* it = *(void**)((char*)mgr + 0x1e5f0);
    if (it == *(void**)((char*)mgr + 0x1e5f4)) return;
    void* end = *(void**)((char*)mgr + 0x1e5f4);
    float* pf = (float*)((char*)it + 0x10);
    do {
      float* pv = pf - 2;
      if (FUN_00b7e3e0(pv, 0, 0) == 0) {
        float fx = pv[0];
        float fy = pf[-1];
        float fz = pf[0];
        float ax = fx < 0 ? -fx : fx;
        float ay = fy < 0 ? -fy : fy;
        float az = fz < 0 ? -fz : fz;
        s32 i8, i4, i5;
        if (az < ax || az < ay) {
          if (ay < ax) {
            i8 = (s32)((fy / fx + 1.0f) * 2.0f);
            i4 = (s32)((fz / ax + 1.0f) * 2.0f);
            i5 = 2;
            if (fx < 0.0f) i5 = 3;
          } else {
            i8 = (s32)((fz / fy + 1.0f) * 2.0f);
            i4 = (s32)((fx / ay + 1.0f) * 2.0f);
            i5 = (fy < 0.0f) ? 5 : 4;
          }
        } else {
          i8 = (s32)((fx / fz + 1.0f) * 2.0f);
          i4 = (s32)((fy / az + 1.0f) * 2.0f);
          i5 = (fz < 0.0f) ? 1 : 0;
        }
        if (i8 == 4) i8 = 3;
        if (i4 == 4) i4 = 3;
        *(s32*)((char*)self + (i4 + i5 * 4) * 4 * 0x54 + i8 * 0x54 + 0x50) = 3;
      }
      it = (char*)it + 0x19a8;
      pf = (float*)((char*)pf + 0x19a8);
    } while (it != end);
  }
}

// ======================================================================
// 0x00c7f300 - coordinate-match predicate (3-float key vs 3-entry table)
// ======================================================================
// @ 0x00c7f300
u8 __fastcall FUN_00c7f300(void* self, void* dummy, u32* key, float x, float y, float z) {
  (void)dummy;
  if (x == *(float*)0x1694bac) {
    if (y == *(float*)0x1694bb0) {
      if (z == *(float*)0x1694bb4) goto done;
    }
  }
  if (*key != 0) {
    u32* kp = key;
    void* e = ((FindC*)((char*)self + 0x50))->Find(&x);
    u32 k0 = kp[0];
    s32 i = 0;
    s32* p = (s32*)((char*)e + 0xc);
    do {
      if (p[-2] == (s32)k0 && p[-1] == (s32)kp[1] && p[0] == (s32)kp[2] && p[1] > 0)
        return 1;
      i++;
      p += 4;
    } while (i < 3);
  }
done:
  return 0;
}

// ======================================================================
// 0x00c7f390
// ======================================================================
// @ 0x00c7f390
void __cdecl FUN_00c7f390(void) {
  void* mm = FUN_00feb9f0();
  void* list = ((MMC*)mm)->GetMissionList();
  s32 n = (*(s32*)((char*)list + 4) - *(s32*)list) >> 2;
  s32 i = 0;
  if (n > 0) {
    for (;;) {
      void* m = *(void**)((char*)(*(void**)list) + i * 4);
      void* tp = ((MissionC*)m)->GetTargetPlanet();
      void* ap = FUN_01021260();
      if (tp == ap && m != 0) {
        void* o = ((TFpu)(*(void***)m)[0xc / 4])(m, 0x35988ee);
        if (o != 0 && ((*(u32*)((char*)o + 0x130) >> 3) & 1)) break;
      }
      i++;
      if (i >= n) return;
    }
    if (FUN_01044640() != 0) {
      FUN_01041c50((void*)0x1473368, 0x9fc86b19, 1);
    }
  }
}

// ======================================================================
// 0x00c7f430 - coordinate-match predicate, 2-entry table
// ======================================================================
// @ 0x00c7f430
u8 __fastcall FUN_00c7f430(void* self, void* dummy, s32* keyword, float* coords) {
  (void)dummy;
  float x = coords[0];
  if (x == *(float*)0x1694bac) {
    float y = coords[1];
    if (y == *(float*)0x1694bb0) {
      float z = coords[2];
      if (z == *(float*)0x1694bb4) goto done;
    }
  }
  if (*keyword != 0) {
    s32* kp = keyword;
    void* e = ((FindC*)((char*)self + 0x50))->Find(coords);
    s32 k0 = kp[0];
    s32 i = 0;
    s32* p = (s32*)((char*)e + 0x3c);
    do {
      if (p[-2] == k0 && p[-1] == kp[1] && p[0] == kp[2] && p[1] > 0) return 1;
      i++;
      p += 4;
    } while (i < 2);
  }
done:
  return 0;
}

// ======================================================================
// 0x00c7f4c0
// ======================================================================
// @ 0x00c7f4c0
s32 __fastcall FUN_00c7f4c0(void* self, void* dummy, s32* key) {
  (void)dummy;
  s32 result = 0;
  char* cell = (char*)self + 0x50;
  s32 i4 = 0, i3 = 0, i8 = 0;
  for (;;) {
    if (cell == 0) return result;
    s32 i2 = 0;
    s32* p = (s32*)(cell + 0x3c);
    do {
      if (p[-2] == key[0] && p[-1] == key[1] && p[0] == key[2]) {
        if (i2 == 0) result = 1;
        else if (i2 == 1) result = 2;
        break;
      }
      i2++;
      p += 4;
    } while (i2 < 2);
    i4++;
    cell += 0x54;
    if (i4 > 3) {
      i3++;
      i4 = 0;
      if (i3 > 3) {
        i8++;
        i3 = 0;
        if (i8 > 5) return result;
      }
    }
  }
}

// ======================================================================
// 0x00c7f560
// ======================================================================
// @ 0x00c7f560
void** __fastcall FUN_00c7f560(void* self, void* dummy, void** out, u32* key) {
  (void)dummy;
  void* node = *(void**)((char*)self + 0xc);
  void* best = (char*)self + 4;
  if (node != 0) {
    do {
      u32* p = (u32*)node;
      u8 less;
      if (p[4] != key[0]) less = (u8)(p[4] < key[0]);
      else if (p[6] != key[2]) less = (u8)(p[6] < key[2]);
      else less = (u8)(p[5] < key[1]);
      if (!less) {
        best = node;
        node = *(void**)((char*)node + 4);
      } else {
        node = *(void**)((char*)node);
      }
    } while (node != 0);
  }
  *out = best;
  return out;
}

// ======================================================================
// 0x00c7f5b0 - SP::cSimPlanetLowLOD::CalculateTerraformForces
// ======================================================================
// @ 0x00c7f5b0
void* __fastcall FUN_00c7f5b0(void* self, void* dummy, void* out, void* planet, float* coords) {
  float* pf = (float*)out;
  void* pm = FUN_01049a10();
  void* tm = FUN_00b3d430();
  s32 r = FUN_00bbc670(tm, planet);
  float dx = coords[0] - *(float*)0x1471064;
  float dy = coords[1] - *(float*)0x1471064;
  float len2 = dx * dx + dy * dy;
  float len;
  if (len2 <= 1.5258789e-05f) {
    len = 0.0f;
    dx = 0.0f;
    dy = 0.0f;
  } else {
    len = sqrtf(len2);
    dx = (1.0f / len) * dx;
    dy = (1.0f / len) * dy;
  }
  float wdr = ((TuneC*)pm)->GetWaterDivergenceRate();
  float adr = ((TuneC*)pm)->GetAtmosphereDivergenceRate();
  float steep = (float)pow((double)len, (double)((TuneC*)pm)->GetBullseyeSteepnessPower());
  float force = (dx * (wdr * dx) + dy * (adr * dy)) * steep;
  float flRadius = ((TuneC*)pm)->GetFloraBullseyeRadius();
  float flScalar = ((TuneC*)pm)->GetFloraBullseyeForceScalar();
  s32 counts[3];
  counts[0] = 0; counts[1] = 0; counts[2] = 0;
  {
    void* mgr = FUN_00b3d430();
    if (mgr != 0) {
      s32 i = 1;
      s32* c = counts;
      do {
        s32* p;
        p = (s32*)((TerraMgrC*)mgr)->F870(&len, i, 0x6d60a1cc, planet);
        if (p[0] != *(s32*)0x1694bb8 || p[1] != *(s32*)0x1694bbc || p[2] != *(s32*)0x1694bc0)
          (*c)++;
        p = (s32*)((TerraMgrC*)mgr)->F870(&len, i, 0x29c388a, planet);
        if (p[0] != *(s32*)0x1694bb8 || p[1] != *(s32*)0x1694bbc || p[2] != *(s32*)0x1694bc0)
          (*c)++;
        p = (s32*)((TerraMgrC*)mgr)->F870(&len, i, 0x3a8be428, planet);
        if (p[0] != *(s32*)0x1694bb8 || p[1] != *(s32*)0x1694bbc || p[2] != *(s32*)0x1694bc0)
          (*c)++;
        i++;
        c++;
      } while (i < 4);
    }
  }
  if (r > 0) {
    s32 i = 0;
    do {
      s32 cnt = counts[i];
      if (cnt > 0) {
        float radius = *(float*)FUN_00fc1fa0(i + 1) - flRadius;
        if (radius < len) {
          float hi = radius + flRadius;
          float mid = len;
          if (mid <= radius) mid = radius;
          if (hi <= mid) mid = hi;
          float t = (mid - radius) / (hi - radius);
          force = force - (((3.0f - t * 2.0f) * t) * t) * ((float)cnt * flScalar);
        }
      }
      i++;
    } while (i < r);
  }
  pf[0] = force * dx;
  pf[1] = force * dy;
  float lc = 0.0f;
  {
    u32 sel;
    void* p = pm ? *(void**)((char*)pm + 0x24) : 0;
    if (p != 0 && ((AMdC*)p)->F24(0x5a72fa9, &sel)) {
      if (*(u16*)((char*)sel + 0x12) == 0xd) {
        if ((*(u32*)((char*)sel + 0x10) & 0x30) != 0) sel = *(u32*)sel;
        lc = *(float*)sel;
      }
    }
  }
  float py = 0.0f;
  {
    u32 sel;
    void* p = pm ? *(void**)((char*)pm + 0x24) : 0;
    if (p != 0 && ((AMdC*)p)->F24(0x5a72fad, &sel)) {
      if (*(u16*)((char*)sel + 0x12) == 0xd) {
        if ((*(u32*)((char*)sel + 0x10) & 0x30) != 0) sel = *(u32*)sel;
        py = *(float*)sel;
      }
    }
  }
  float pz = 0.0f;
  {
    u32 sel;
    void* p = pm ? *(void**)((char*)pm + 0x24) : 0;
    if (p != 0 && ((AMdC*)p)->F24(0x5a72fb0, &sel)) {
      if (*(u16*)((char*)sel + 0x12) == 0xd) {
        if ((*(u32*)((char*)sel + 0x10) & 0x30) != 0) sel = *(u32*)sel;
        pz = *(float*)sel;
      }
    }
  }
  u32 flags = *(u32*)((char*)planet + 0x2c);
  if (((flags >> 0xc) & 1) == 0) {
    if (((flags >> 0xd) & 1) != 0) {
      pf[0] = pf[0] - ((coords[0] * pz + py) * coords[0] + lc);
    }
  } else {
    pf[0] = ((1.0f - coords[0]) * pz + py) * (1.0f - coords[0]) + lc + pf[0];
  }
  if (FUN_00b8dab0(planet) == 5) {
    void* av = FUN_00b1fdb0(FUN_00b8de30(planet));
    void* sm = FUN_00b3d2a0();
    if (av == FUN_00885c90(sm)) {
      if (*(float*)((char*)planet + 0xb0) > *(float*)0x1471064) {
        pf[1] = ((1.0f - coords[1]) * pz + py) * (1.0f - coords[1]) + lc + pf[1];
        return out;
      }
      pf[1] = pf[1] - (coords[1] * pz + py) * coords[1] - lc;
    }
  }
  return out;
}

// ======================================================================
// 0x00c7fab0 - SP::cSimPlanetLowLOD::StepBullseyePhysics
// ======================================================================
// @ 0x00c7fab0
void __fastcall FUN_00c7fab0(void* self, void* dummy, s32 dt) {
  (void)dummy;
  void* target = *(void**)((char*)self + 0x4c);
  void* tune = FUN_01049a10();
  void* obj = *(void**)((char*)target + 0x13c);
  float timeScale = ((TuneC*)tune)->GetBullseyeTimeScale();
  float dtf = (float)dt;
  float t = (dtf * timeScale) * *(float*)0x13f9428;
  float mass = ((TuneC*)tune)->GetBullseyeMarbleMass();
  float coords[2];
  coords[0] = *(float*)((char*)obj + 0xb4);
  coords[1] = *(float*)((char*)obj + 0xb0);
  float fx, fy;
  FUN_00c7f5b0(self, 0, &fx, obj, coords);
  float invMass = 1.0f / mass;
  float nvx = (fx * invMass) * t + *(float*)((char*)self + 0x1fd8);
  float nvy = (fy * invMass) * t + *(float*)((char*)self + 0x1fd4);
  *(float*)((char*)self + 0x1fd8) = nvx;
  *(float*)((char*)self + 0x1fd4) = nvy;
  if (*(float*)((char*)obj + 0xb4) >= *(float*)0x1486cd8 && nvx > 0.0f) {
    *(float*)((char*)self + 0x1fd8) = 0.0f;
  }
  if (*(float*)((char*)obj + 0xb4) <= *(float*)0x13f9428 && nvx <= 0.0f && nvx != 0.0f) {
    *(float*)((char*)self + 0x1fd8) = 0.0f;
  }
  if (*(float*)((char*)obj + 0xb0) >= *(float*)0x1486cd8 && nvy > 0.0f) {
    *(float*)((char*)self + 0x1fd4) = 0.0f;
  }
  if (*(float*)((char*)obj + 0xb0) <= *(float*)0x13f9428 && nvy <= 0.0f && nvy != 0.0f) {
    *(float*)((char*)self + 0x1fd4) = 0.0f;
  }
  {
    float cur = *(float*)((char*)self + 0x1fd4);
    float absCur = cur < 0 ? -cur : cur;
    float drag = ((TuneC*)tune)->GetBullseyeMarbleDragCoeff();
    *(float*)((char*)self + 0x1fd4) = cur - ((drag * cur) * absCur) * t;
  }
  {
    float cur = *(float*)((char*)self + 0x1fd8);
    float absCur = cur < 0 ? -cur : cur;
    float drag = ((TuneC*)tune)->GetBullseyeMarbleDragCoeff();
    *(float*)((char*)self + 0x1fd8) = cur - ((drag * cur) * absCur) * t;
  }
  *(float*)((char*)obj + 0xb0) = t * *(float*)((char*)self + 0x1fd4) + *(float*)((char*)obj + 0xb0);
  *(float*)((char*)obj + 0xb4) = *(float*)((char*)self + 0x1fd8) * t + *(float*)((char*)obj + 0xb4);
  {
    float base = 1.0f - ((TuneC*)tune)->GetBullseyeMarbleDamping();
    float p = FUN_011e08f0(base, t);
    *(float*)((char*)self + 0x1fd4) *= p;
  }
  {
    float base = 1.0f - ((TuneC*)tune)->GetBullseyeMarbleDamping();
    float p = FUN_011e08f0(base, t);
    *(float*)((char*)self + 0x1fd8) *= p;
  }
  {
    float v = *(float*)((char*)obj + 0xb0);
    if (v <= 0.0f) v = 0.0f;
    if (v >= 1.0f) v = 1.0f;
    *(float*)((char*)obj + 0xb0) = v;
  }
  {
    float v = *(float*)((char*)obj + 0xb4);
    if (v <= 0.0f) v = 0.0f;
    if (v >= 1.0f) v = 1.0f;
    *(float*)((char*)obj + 0xb4) = v;
  }
  if (*(float*)((char*)obj + 0xb8) >= 0.0f) {
    float out[2];
    out[0] = *(float*)((char*)obj + 0xb4);
    FUN_00fc20e0(out, *(float*)((char*)obj + 0xb0), out[0]);
    float cur = *(float*)((char*)obj + 0xb8);
    if (out[0] >= cur) cur = out[0];
    if (out[1] <= cur) cur = out[1];
    *(float*)((char*)obj + 0xb8) = cur;
  }
}

// ======================================================================
// 0x00c7fdd0
// ======================================================================
// @ 0x00c7fdd0
void __fastcall FUN_00c7fdd0(void* self, void* dummy) {
  (void)dummy;
  *(void**)self = (void*)0x14733a8;
  *(void**)((char*)self + 4) = (void*)0x1473398;
  *(void**)((char*)self + 0x34) = (void*)0x1473388;
  {
    NukeC* tree = (NukeC*)((char*)self + 0x20a0);
    void* node = ((void**)((char*)self + 0x20a0))[3];
    tree->DoNukeSubtree(node);
  }
  {
    char* ht = (char*)self + 0x2080;
    ((HtC*)ht)->DoFreeNodes(*(void**)(ht + 4), *(void**)(ht + 8));
    *(void**)(ht + 0xc) = 0;
    if (*(u32*)(ht + 8) > 1) FUN_00f47380(*(void**)(ht + 4));
  }
  {
    char* ht = (char*)self + 0x2060;
    ((HtC*)ht)->DoFreeNodes(*(void**)(ht + 4), *(void**)(ht + 8));
    *(void**)(ht + 0xc) = 0;
    if (*(u32*)(ht + 8) > 1) FUN_00f47380(*(void**)(ht + 4));
  }
  ((GonzagoC*)((char*)self + 0x2038))->Dtor();
  ((GonzagoC*)((char*)self + 0x2010))->Dtor();
  ((GonzagoC*)((char*)self + 0x1ff0))->Dtor();
  {
    void* h = *(void**)((char*)self + 0x38);
    if (h != 0) {
      void* a = *(void**)((char*)self + 0x3c);
      void* b = *(void**)((char*)self + 0x40);
      void* c = *(void**)((char*)self + 0x44);
      void* d = *(void**)((char*)self + 0x48);
      *(void**)((char*)self + 0x38) = 0;
      FUN_00571db0(h, a, b, c, d);
    }
  }
  *(void**)((char*)self + 0x34) = (void*)0x13eb394;
  ((GameDataC*)self)->Dtor();
}

// ======================================================================
// 0x00c7ff00 - SP::cSPFilterResults::~cSPFilterResults
// ======================================================================
// @ 0x00c7ff00
void __fastcall FUN_00c7ff00(void* self, void* dummy) {
  (void)dummy;
  {
    char* ht = (char*)self + 0x28;
    ((HtC*)ht)->DoFreeNodes(*(void**)(ht + 4), *(void**)(ht + 8));
    *(void**)(ht + 0xc) = 0;
    if (*(u32*)(ht + 8) > 1) FUN_00f47380(*(void**)(ht + 4));
  }
  {
    char* ht = (char*)self + 8;
    ((HtC*)ht)->DoFreeNodes(*(void**)(ht + 4), *(void**)(ht + 8));
    *(void**)(ht + 0xc) = 0;
    if (*(u32*)(ht + 8) > 1) FUN_00f47380(*(void**)(ht + 4));
  }
}

// ======================================================================
// 0x00c7ff60
// ======================================================================
// @ 0x00c7ff60
void* __fastcall FUN_00c7ff60(void* self, void* dummy, void* p) {
  (void)dummy;
  u32 next = (u32)p + 0x10;
  u32 end = *(u32*)((char*)self + 4);
  if (next < end) {
    FUN_00705250((void*)next, (void*)end, p);
  }
  *(u32*)((char*)self + 4) -= 0x10;
  return p;
}
