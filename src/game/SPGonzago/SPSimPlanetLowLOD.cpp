// src/game/SPGonzago/SPSimPlanetLowLOD.cpp -- migrated from slice(s) s00c829e0, s00c81ab0, s00c7ff90, s00c7f060 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSimPlanetLowLOD.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include "SP/cPlanet.h"
#include "SP/cSimPlanetLowLOD.h"
#include "SP/cTerrainDistributeInfo.h"

// ---- items of slice s00c7f060 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef void*  (__thiscall *TFp)(void*);
typedef void*  (__thiscall *TFpu)(void*, u32);
void*  __cdecl FUN_00b3d350(void);   // 0x00b3d350 SP::PlanetModel
void*  __cdecl FUN_00b3d440(void);   // 0x00b3d440
void   __cdecl FUN_00f929c0(int a, s32 b, s32 c, s32 d, void* e, void* f); // 0x00f929c0
s32    __fastcall FUN_00b7e3e0(void* self, void* dummy, void* a); // 0x00b7e3e0 (thiscall)
void*  __cdecl FUN_00feb9f0(void);   // 0x00feb9f0 SP::GetMissionManager
void*  __cdecl FUN_01021260(void);   // 0x01021260
u8     __cdecl FUN_01044640(void);   // 0x01044640
void   __cdecl FUN_01041c50(void* a, u32 b, int c); // 0x01041c50
void*  __cdecl FUN_00fc1fa0(int a);  // 0x00fc1fa0 SP::GetTerraformRadius
void   __cdecl FUN_00fc20e0(void* out, float a, float b); // 0x00fc20e0 TerraBlend
void*  __cdecl FUN_01049a10(void);   // 0x01049a10
void*  __cdecl FUN_00b3d430(void);   // 0x00b3d430 SP::TerraformingManager
s32    __cdecl FUN_00bbc670(void* self, void* a); // 0x00bbc670 TerraformingManager::F670 (thiscall, returns count)
float  __cdecl FUN_011e08f0(float base, float exp); // 0x011e08f0 _CIpow (x87 st0/st1)
s32    __cdecl FUN_00b8dab0(void* self); // 0x00b8dab0
void*  __cdecl FUN_00b8de30(void* self); // 0x00b8de30 BioProtectorSort::operator()
void*  __cdecl FUN_00b1fdb0(void* self); // 0x00b1fdb0 cGameNounManager::GetAvatar
void*  __cdecl FUN_00b3d2a0(void);   // 0x00b3d2a0 SP::StarManager
void*  __cdecl FUN_00885c90(void* self); // 0x00885c90
void   __cdecl FUN_00705250(void* dst, void* src, void* out); // 0x00705250 copy
void   __cdecl FUN_00f47380(void* p); // 0x00f47380 operator_delete_array
struct HtC { void DoFreeNodes(void* a, void* b); }; // FUN_007611f0 _ht_DoFreeNodes (thiscall)
struct FindC { void* Find(void* key); };            // FUN_00c7eaf0 (thiscall, ecx=container)
struct MMC { void* GetMissionList(); };             // FUN_00fedd50 (thiscall, ecx=mission manager)
struct MissionC { void* GetTargetPlanet(); };       // FUN_00970b30 (thiscall, ecx=mission)
struct NukeC { void DoNukeSubtree(void* node); };   // FUN_009a9600 DoNukeSubtree (thiscall)
struct GonzagoC { void Dtor(); };                   // FUN_00b638b0 ~cGonzagoTimer (thiscall)
struct GameDataC { void Dtor(); };                  // FUN_00b184c0 ~cGameData (thiscall)
void   __cdecl FUN_00571db0(void* a, void* b, void* c, void* d, void* e); // 0x00571db0 RemoveHandler
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
// ---- items of slice s00c7f060 end

// ---- items of slice s00c7ff90 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
struct tSpeciesKey {
    uint32_t mField0;                                    // +0x00
    uint32_t mField4;                                    // +0x04
    uint32_t mField8;                                    // +0x08
};
class cSpeciesList {
public:
    uint8_t       pad000[0xbc];                          // +0x000 .. +0x0bb
    tSpeciesKey*  mpBegin;                               // +0x0bc
    tSpeciesKey*  mpEnd;                                 // +0x0c0
};
class cPlantSpecies;
class cTerrainDistributeInfo_s00c7_ff90;
class cPlantSpeciesManager {
public:
    cPlantSpecies* GetSpeciesFromID(tSpeciesKey* pKey);   // 0x00b90410
};
class cTerrainDistributeInfo_s00c7_ff90 {
public:
    void SetInfoFromProps();                             // 0x00b2bbe0
};
class cPlanet_s00c7_ff90 {
public:
    void PushKeyBC(tSpeciesKey* pKey);                   // 0x00c73270

    uint8_t        pad000[0x13c];                        // +0x000 .. +0x13b
    cSpeciesList*  mpSpeciesList;                        // +0x13c
};
extern cPlantSpeciesManager* __cdecl           FUN_00b3d420();   // 0x00b3d420
extern cTerrainDistributeInfo_s00c7_ff90* __cdecl         FUN_00b3d3b0();   // 0x00b3d3b0
namespace SP {
class cSpeciesKeyTable {
public:
    __declspec(noinline) int32_t* FUN_00c80110(tSpeciesKey* pKey); // 0x00c80110
};
}
namespace SP {
class cSimPlanetLowLOD_s00c7_ff90 {
public:
    cSimPlanetLowLOD_s00c7_ff90();
    void FUN_00c80180();
    void FUN_00c805b0();
    void FUN_00c80680();
    void FUN_00c80780();
    bool AddPlantSpecies(tSpeciesKey* pKey);  // 0x00c809d0 (SP::cSimPlanetLowLOD::AddPlantSpecies)
    void FUN_00c80a80();

    uint8_t            pad000[0x4c];                     // +0x000 .. +0x04b
    cPlanet_s00c7_ff90*           mpPlanet;                         // +0x04c
    uint8_t            pad050[0x2060 - 0x50];            // +0x050 .. +0x205f
    cSpeciesKeyTable   mSpeciesTable;                    // +0x2060
};
}
// ---- items of slice s00c7ff90 end

// ---- items of slice s00c81ab0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl SP_PlanetModel();                        // 0x00b3d350 SP::PlanetModel
void  __cdecl FUN_00b3d450();                          // 0x00b3d450
void  __cdecl FUN_00b3d420(void* a);                   // 0x00b3d420
void  __cdecl FUN_00b3d3b0(void* a);                   // 0x00b3d3b0 (also 0-arg overload)
void  __cdecl FUN_00b2bbe0();                          // 0x00b2bbe0
void* __cdecl FUN_00b90410(void* cell);                // 0x00b90410
s32   __cdecl FUN_00b8f860();                          // 0x00b8f860
u32   __cdecl FUN_00b2a750(u32 a);                     // 0x00b2a750
s32   __cdecl FUN_00401090(void* key);                 // 0x00401090 GetSetting9
void* __cdecl FUN_004df550(void* key);                 // 0x004df550 GetProfile (thiscall, ecx=key)
void  __cdecl FUN_00c7ff60(void* p);                   // 0x00c7ff60 (thiscall, ecx=p)
void  __cdecl FUN_00c805b0(void* self, void* pos, void* vec, u32 a); // 0x00c805b0 (thiscall)
u8    __cdecl FUN_00c772c0(void* self, void* id);      // 0x00c772c0 (thiscall, bool)
void* __cdecl FUN_00b3d300();                          // 0x00b3d300 SP::NounManager
u32   __cdecl FUN_00936090();                          // 0x00936090 SetSeed (thiscall)
u32   __cdecl FUN_00a68fb0(void* self, u32 n);         // 0x00a68fb0 RandomUint32Uniform
double __cdecl FUN_a68fd0(void* self);                 // 0x00a68fd0 RandomDoubleUniform
void __fastcall FUN_00c81f40(void* self, void* /*edx*/, void* arg);
void __fastcall FUN_00c821b0(void* self, void* /*edx*/, void* a, void* b, int c, void* d);
// ---- items of slice s00c81ab0 end

// ---- items of slice s00c829e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cPlanet_s00c8_29e0;
}
namespace SP {
struct tPlanetKey {
    int32_t mIndex;                                      // +0x00
};
}
namespace SP {
struct tPlanetEntry {
    uint8_t pad000[0xa0];                                // +0x000 .. +0x09f
    bool    mFieldA0;                                    // +0x0a0
    bool    mFieldA1;                                    // +0x0a1
};
}
namespace SP {
class cPlanetEntryTable {
public:
    tPlanetEntry* FUN_00ba4e60(tPlanetKey* pKey);        // 0x00ba4e60
};
}
namespace SP {
extern void* __cdecl GetUniverseContext();               // 0x01021080
}
namespace SP {
class cSimPlanetLowLOD_s00c8_29e0 {
public:
    void FUN_00c829e0();
    __declspec(noinline) void FUN_00c82d50(cPlanet_s00c8_29e0* pPlanet, bool bValue);
    void FUN_00c82ea0();
    void FUN_00c82f00();
    void FUN_00c82f80();
    void FUN_00c83050(cPlanet_s00c8_29e0* pOld, cPlanet_s00c8_29e0* pNew, bool bValue);
    void FUN_00c83090(tPlanetKey key, bool bValue);
    bool FUN_00c830b0(tPlanetKey key);
    void FUN_00c830d0(tPlanetKey key, bool bValue);
    void UpdateBackgroundPlanet(cPlanet_s00c8_29e0* pPlanet, bool bValue); // 0x00c817e0

    uint8_t            pad000[0x4c];                     // +0x0000 .. +0x004b
    cPlanet_s00c8_29e0*           mpPlanet;                         // +0x004c
    uint8_t            pad050[0x11c0 - 0x50];            // +0x0050 .. +0x11bf
    cPlanetEntryTable  mEntryTable;                      // +0x11c0
};
}
// ---- items of slice s00c829e0 end

// @ 0x00c7f060
void __fastcall FUN_00c7f060(void* self)
{
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

// @ 0x00c7f300
u8 __fastcall FUN_00c7f300(void* self, void* dummy, u32* key, float x, float y, float z)
{
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

// @ 0x00c7f390
void __cdecl FUN_00c7f390(void)
{
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

// @ 0x00c7f430
u8 __fastcall FUN_00c7f430(void* self, void* dummy, s32* keyword, float* coords)
{
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

// @ 0x00c7f4c0
s32 __fastcall FUN_00c7f4c0(void* self, void* dummy, s32* key)
{
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

// @ 0x00c7f560
void** __fastcall FUN_00c7f560(void* self, void* dummy, void** out, u32* key)
{
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

// @ 0x00c7f5b0
void* __fastcall FUN_00c7f5b0(void* self, void* dummy, void* out, void* planet, float* coords)
{
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

// @ 0x00c7fab0
void __fastcall FUN_00c7fab0(void* self, void* dummy, s32 dt)
{
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

// @ 0x00c7fdd0
void __fastcall FUN_00c7fdd0(void* self, void* dummy)
{
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

// @ 0x00c7ff00
void __fastcall FUN_00c7ff00(void* self, void* dummy)
{
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

// @ 0x00c7ff60
void* __fastcall FUN_00c7ff60(void* self, void* dummy, void* p)
{
  (void)dummy;
  u32 next = (u32)p + 0x10;
  u32 end = *(u32*)((char*)self + 4);
  if (next < end) {
    FUN_00705250((void*)next, (void*)end, p);
  }
  *(u32*)((char*)self + 4) -= 0x10;
  return p;
}

// @ 0x00c7ff90
void __fastcall cSimPlanetLowLODCtorSTUB(void* this_, int unused)
{
    (void)this_;
}

// @ 0x00c80110
__declspec(noinline) int32_t* __thiscall SP::cSpeciesKeyTable::FUN_00c80110(tSpeciesKey* pKey)
{
    return (int32_t*)pKey;
}

// @ 0x00c80180
void __thiscall SP::cSimPlanetLowLOD_s00c7_ff90::FUN_00c80180()
{
}

// @ 0x00c805b0
void __thiscall SP::cSimPlanetLowLOD_s00c7_ff90::FUN_00c805b0()
{
}

// @ 0x00c80680
void __thiscall SP::cSimPlanetLowLOD_s00c7_ff90::FUN_00c80680()
{
}

// @ 0x00c80780
void __thiscall SP::cSimPlanetLowLOD_s00c7_ff90::FUN_00c80780()
{
}

// @ 0x00c809d0
bool __thiscall SP::cSimPlanetLowLOD_s00c7_ff90::AddPlantSpecies(tSpeciesKey* pKey)
{
    cSpeciesList* pList = mpPlanet->mpSpeciesList;
    int32_t count = (int32_t)(pList->mpEnd - pList->mpBegin);
    tSpeciesKey* pEntry = pList->mpBegin;
    for (int32_t i = 0; i < count; ++i) {
        if (pEntry->mField0 == pKey->mField0 &&
            pEntry->mField4 == pKey->mField4 &&
            pEntry->mField8 == pKey->mField8)
            return false;
        ++pEntry;
    }
    if (!FUN_00b3d420()->GetSpeciesFromID(pKey))
        return false;
    if (count >= 9)
        return false;
    mpPlanet->PushKeyBC(pKey);
    *mSpeciesTable.FUN_00c80110(pKey) = 0;
    FUN_00b3d3b0()->SetInfoFromProps();
    return true;
}

// @ 0x00c80a80
void __thiscall SP::cSimPlanetLowLOD_s00c7_ff90::FUN_00c80a80()
{
}

// @ 0x00c81ab0
u32 __fastcall FUN_00c81ab0(void* self, void* /*edx*/, void* arg1, float* pos, char flag)
{
  char* p = (char*)self;
  int* key = (int*)arg1;              // species/resource key (3 dwords)
  float x = pos[0];
  float y = pos[1];
  float z = pos[2];

  // Early-out: exact match against the "invalid position" sentinel.
  if (x == *(float*)0x01694bac) {
    if (y == *(float*)0x01694bb0) {
      if (z == *(float*)0x01694bb4) {
        return 1;
      }
    }
  }
  // Early-out: key equals sentinel.
  if (key[0] == *(int*)0x01694bb8 && key[1] == *(int*)0x01694bbc &&
      key[2] == *(int*)0x01694bc0) {
    return 1;
  }

  // iVar15 = cell array base (mCubeSim at +0x4c, +0x13c -> array).
  int* arr = *(int**)(*(int*)(p + 0x4c) + 0x13c);
  int lo = arr[0xbc / 4];
  int hi = arr[0xc0 / 4];
  int cubeCount = (hi - lo) / 12;

  float ax = (float)fabs(x);
  float ay = (float)fabs(y);
  float az = (float)fabs(z);

  int local_20, local_1c, local_18;
  if (az < ax || az < ay) {
    if (ay < ax) {
      local_20 = (int)((y / x + 1.0) * 2.0);
      local_1c = (int)((z / ax + 1.0) * 2.0);
      local_18 = (x < 0.0f) ? 3 : 2;
    } else {
      local_20 = (int)((z / y + 1.0) * 2.0);
      local_1c = (int)((x / ay + 1.0) * 2.0);
      local_18 = (y < 0.0f) ? 5 : 4;
    }
  } else {
    local_20 = (int)((x / z + 1.0) * 2.0);
    local_1c = (int)((y / az + 1.0) * 2.0);
    local_18 = (z < 0.0f) ? 1 : 0;
  }
  if (local_20 == 4) local_20 = 3;
  if (local_1c == 4) local_1c = 3;

  int* dens = &arr[(local_1c + local_18 * 4) * 4 + local_20];

  int* vec = 0;
  int* vecEnd = 0;
  u32 vecCap = 0;
  ((void(__thiscall*)(void*, void*, void*, u32))FUN_00c805b0)(p + 0x50, pos, &vec, 0);
  if ((u32)((char*)vecEnd - (char*)vec) / 16 < 3) {
    ((void(__thiscall*)(void*, void*, void*, u32))FUN_00c805b0)(p + 0x50, pos, &vec, 1);
  }
  if (vec != vecEnd && vec[0] == local_20 && vec[1] == local_1c &&
      vec[2] == local_18 && (int*)vec[3] == dens) {
    ((void(__thiscall*)(void*))FUN_00c7ff60)(vec);
  }
  int* first = vec;
  FUN_00c821b0(p, 0, dens, key, 1, 0);  // SetPlantDensity
  if (*dens < 3 && first != vecEnd) {
    int* dens2 = (int*)first[3];
    ((void(__thiscall*)(void*))FUN_00c7ff60)(first);
    FUN_00c821b0(p, 0, dens2, key, 1, 0);
    first = vec;
  }

  FUN_00b3d3b0(0);
  FUN_00b2bbe0();
  FUN_00b3d420(key);
  u32 ret = 0;
  char* cell = (char*)FUN_00b90410(key);
  if (cell != 0) {
    u32 kind = 0;
    s32 k = FUN_00b8f860();
    if (k == 0x29c388a) kind = 2;
    else if (k == 0x3a8be428) kind = 4;
    else if (k == 0x6d60a1cc) kind = 1;
    FUN_00b3d3b0((void*)kind);
    ret = FUN_00b2a750(kind);
  }

  if (flag != 0) {
    int n = *(int*)((char*)arr + 0xc0) - *(int*)((char*)arr + 0xbc);
    u32 cnt = (u32)(n / 12);
    if ((u32)((hi - lo) / 12) < cnt && (cnt % 3 == 0) &&
        (*(u32*)((char*)arr + 0x2c) & 0x800) == 0) {
      *(u32*)(p + 0x1f8) = 1;   // mExtinctionInfoMap field
      char* nm = (char*)FUN_00b3d300();
      void* sphere = (void*)0;
      (void)nm; (void)sphere;
      // UI feedback event path.
      FUN_00c772c0(nm, (void*)0x541a716);
    }
  }
  if (first != 0 && first[-1] != 0) {
    FUN_00f47380(first);
  }
  return ret;
}

// @ 0x00c81f40
void __fastcall FUN_00c81f40(void* self, void* /*edx*/, void* arg)
{
  char* p = (char*)self;
  int* key = (int*)arg;
  if (key[0] == 1) return;

  int* arr = *(int**)(*(int*)(p + 0x4c) + 0x13c);
  int n = (*(int*)((char*)arr + 0xc0) - *(int*)((char*)arr + 0xbc)) / 12;
  if (n == 0) return;

  FUN_00b3d420(0);
  u32 r6 = FUN_00a68fb0((void*)0x01694c00, 3);
  u32 r7 = FUN_00a68fb0((void*)0x01694c00, 3);
  u32 r8 = FUN_00a68fb0((void*)0x01694c00, 3);

  int vecA = *(int*)((char*)arr + 0x114) - *(int*)((char*)arr + 0x110);
  int vecB = *(int*)((char*)arr + 0xfc) - *(int*)((char*)arr + 0xf8);
  if ((vecA >> 2) == n && (vecB >> 2) == n) {
    double d15 = FUN_a68fd0((void*)0x01694c04);
    double d16 = FUN_a68fd0((void*)0x01694c04);
    double d17 = FUN_a68fd0((void*)0x01694c04);
    for (int i = 0; i < n; ++i) {
      char* cell = (char*)(*(int*)((char*)arr + 0xbc) + i * 12);
      float fv = *(float*)(*(int*)((char*)arr + 0x110) + i * 4);
      int  iv = *(int*)(*(int*)((char*)arr + 0xf8) + i * 4);
      float sc = *(float*)((char*)arr + 0x10c);
      FUN_00b90410(cell);
      s32 k = FUN_00b8f860();
      double dv = d16; u32 rv = r7;
      if (k == 0x29c388a) { /* default */ }
      else if (k == 0x3a8be428) { dv = d17; rv = r8; }
      else if (k == 0x6d60a1cc) { dv = d15; rv = r6; }
      else continue;
      if (iv == (int)rv && (float)dv < fv * sc) {
        FUN_00c821b0(p, 0, key, cell, 1, 0);
      }
    }
    return;
  }

  int la = 0, lb = 0, lc = 0;
  for (int i = 0; i < n; ++i) {
    char* cell = (char*)(*(int*)((char*)arr + 0xbc) + i * 12);
    FUN_00b90410(cell);
    s32 k = FUN_00b8f860();
    int hit = 0;
    if (k == 0x29c388a) { hit = (la == (int)r7); ++la; }
    else if (k == 0x3a8be428) { hit = (lb == (int)r8); ++lb; }
    else if (k == 0x6d60a1cc) { hit = (lc == (int)r6); ++lc; }
    if (hit) {
      FUN_00c821b0(p, 0, key, cell, 1, 0);
    }
  }
}

// @ 0x00c82870
void __fastcall FUN_00c82870(void* self, void* /*edx*/)
{
  char* p = (char*)self;
  int* pm = *(int**)((char*)SP_PlanetModel() + 0x24);
  if (pm == 0) {
    ((u32(__thiscall*)(void*, u32))FUN_00936090)((void*)0x01694c00, 0);
    ((u32(__thiscall*)(void*, u32))FUN_00936090)((void*)0x01694c04, 0);
  } else {
    u32 s = (*(u32(__thiscall**)(int*))(*(int**)pm + 0x18 / 4))(pm);
    ((u32(__thiscall*)(void*, u32))FUN_00936090)((void*)0x01694c00, s);
    s = (*(u32(__thiscall**)(int*))(*(int**)pm + 0x18 / 4))(pm);
    ((u32(__thiscall*)(void*, u32))FUN_00936090)((void*)0x01694c04, s);
  }

  char* cell = p + 0x50;
  if (cell != 0) {
    int outer = 0, mid = 0, inner = 0;
    do {
      ((void(__thiscall*)(void*, void*))FUN_00c81f40)(p, cell);
      ++inner; cell += 0x54;
      if (inner > 3) {
        ++mid; inner = 0;
        if (mid > 3) {
          ++outer; mid = 0;
          if (outer > 5) break;
        }
      }
    } while (cell != 0);
  }
}

// @ 0x00c82900
void __fastcall FUN_00c82900(void* self, void* /*edx*/, void* arg)
{
  char* p = (char*)self;
  int* arr;
  int* begin;
  int* end;
  int count;
  int off;
  int cA;
  int cB;
  u32 r6;
  u32 r3;

  FUN_00b3d450();
  r6 = ((u32(__thiscall*)(void*, u32))FUN_00a68fb0)((void*)0x01601760, 6);
  r3 = ((u32(__thiscall*)(void*, u32))FUN_00a68fb0)((void*)0x01601760, 3);

  arr = *(int**)(*(int*)(p + 0x4c) + 0x13c);
  begin = *(int**)((char*)arr + 0xd0);
  end = *(int**)((char*)arr + 0xd4);
  count = (int)((char*)end - (char*)begin) / 12;

  off = 0;
  cA = 0;
  cB = 0;
  if (count > 0) {
    do {
      char* key = (char*)((char*)begin + off);
      int kk = FUN_00401090(key);
      void* prof = FUN_004df550((void*)kk);
      if (prof != 0) {
        int hit;
        if (*(int*)((char*)prof + 0x608) != 0) {
          hit = (cA == (int)r3);
          ++cA;
        } else {
          hit = (cB == (int)r6);
          ++cB;
        }
        if (hit) {
          FUN_00c821b0(p, 0, key, arg, 1, 0);
        }
      }
      off += 0xc;
      --count;
    } while (count != 0);
  }
}

// @ 0x00c829e0
void __thiscall SP::cSimPlanetLowLOD_s00c8_29e0::FUN_00c829e0()
{
}

// @ 0x00c82ea0
void __thiscall SP::cSimPlanetLowLOD_s00c8_29e0::FUN_00c82ea0()
{
}

// @ 0x00c82f80
void __thiscall SP::cSimPlanetLowLOD_s00c8_29e0::FUN_00c82f80()
{
}

// @ 0x00c83050
void __thiscall SP::cSimPlanetLowLOD_s00c8_29e0::FUN_00c83050(SP::cPlanet_s00c8_29e0* pOld, SP::cPlanet_s00c8_29e0* pNew, bool bValue)
{
    if (pOld == pNew) {
        if (!SP::GetUniverseContext()) {
            FUN_00c82d50(pNew, bValue);
            return;
        }
    }
    UpdateBackgroundPlanet(pNew, bValue);
}

// @ 0x00c83090
void __thiscall SP::cSimPlanetLowLOD_s00c8_29e0::FUN_00c83090(SP::tPlanetKey key, bool bValue)
{
    mEntryTable.FUN_00ba4e60(&key)->mFieldA0 = bValue;
}

// @ 0x00c830b0
bool __thiscall SP::cSimPlanetLowLOD_s00c8_29e0::FUN_00c830b0(SP::tPlanetKey key)
{
    return mEntryTable.FUN_00ba4e60(&key)->mFieldA1;
}

// @ 0x00c830d0
void __thiscall SP::cSimPlanetLowLOD_s00c8_29e0::FUN_00c830d0(SP::tPlanetKey key, bool bValue)
{
    mEntryTable.FUN_00ba4e60(&key)->mFieldA1 = bValue;
}
