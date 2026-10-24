// Slice s00c31960 (batch gold6, worker 44). Region 0x00c31960-0x00c3297b.
// SP::cEmpire cluster: turret health / weaponry value, tribute cap helpers,
// random enemy/ally pickers, ally membership checks, heap push/sift sorts by
// distance-to-home (civ cities), GetUFOKey, InitRelationship, property key test.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef          short s16;
typedef          char  s8;
typedef unsigned long long u64;
typedef          long long s64;

// thiscall function-pointer typedefs
typedef float  (__thiscall *TFF)(void*);
typedef float* (__thiscall *TFV)(void*);
typedef int    (__thiscall *TFI)(void*);
typedef void*  (__thiscall *TFVP)(void*);
typedef char   (__thiscall *TFC)(void*);
typedef char   (__thiscall *TFCU)(void*, u32);
typedef u8     (__thiscall *TFBU)(void*, u32);
typedef s32    (__thiscall *TFIP)(void*);

// ---- external callees (address in comment) ------------------------------
float  __cdecl FUN_00c317a0(void* self);               // 0x00c317a0 cEmpire::GetWeaponryLevel (thiscall)
void*  __cdecl FUN_00c31730(void* self);               // 0x00c31730 cEmpire::GetHomePlanet (thiscall)
void*  __stdcall FUN_01029940(u32 level);              // 0x01029940 SP::GetSpaceCombatTuning
float  __cdecl FUN_0102a780(void* self);               // 0x0102a780 GetTurretHealth (thiscall)
u32    __cdecl FUN_00a68fb0(void* self, u32 n);        // 0x00a68fb0 RandomUint32Uniform (ecx=0x1601760)
void*  __cdecl FUN_01002bd0(void);                     // 0x01002bd0 SP::SpaceGameGet
s32    __cdecl FUN_00c702f0(u32 key);                 // 0x00c702f0
u32    __cdecl FUN_005c65e0(void* self);               // 0x005c65e0 SP::cCivData::GetCities (thiscall)
char   __cdecl FUN_00c31080(void* a, void* b);         // 0x00c31080
void*  __cdecl FUN_01021300(void);                     // 0x01021300
void*  __cdecl FUN_00b3d300(u32 id);                   // 0x00b3d300 SP::NounManager
void*  __cdecl FUN_00f67d90(void* self);               // 0x00f67d90 cTerrainEditor::GetCurrentTerrainSphere (thiscall)
char   __cdecl FUN_00c7a890(void* self);               // 0x00c7a890
char   __cdecl FUN_00c7bc20(void* self, u32 a);        // 0x00c7bc20
s32    __cdecl FUN_01021090(void);                     // 0x01021090 GetPlayerEmpireID
void*  __cdecl FUN_00b3d2c0(void);                     // 0x00b3d2c0 SP::RelationshipManager
void*  __cdecl FUN_00b3d2a0(void);                     // 0x00b3d2a0 SP::StarManager
float  __cdecl FUN_00d01b80(void* self, u32 a, u32 b, u32 c); // 0x00d01b80 (thiscall ecx=relmgr)
void   __cdecl FUN_00d06240(void* self, u32 a, u32 b, u32 c, float f); // 0x00d06240 RecordEvent (thiscall)
void*  __cdecl FUN_00ba9370(void* self, u32 id);       // 0x00ba9370 cStarManager::GetEmpireByID (thiscall)
void*  __cdecl FUN_00baf700(void* self);               // 0x00baf700 (thiscall)
void*  __cdecl FUN_00885c90(void* self);               // 0x00885c90 (thiscall)
char   __cdecl FUN_00d01b50(void* self, u32 a, u32 b); // 0x00d01b50 (thiscall ecx=relmgr)
char   __cdecl FUN_00d01fb0(void* self, u32 a, u32 b); // 0x00d01fb0 (thiscall ecx=relmgr)
void*  __cdecl FUN_00bc3170(void* self);               // 0x00bc3170 (thiscall)
s32    __cdecl FUN_00ba6d80(void* self, u32 a);        // 0x00ba6d80 BannerList helper (thiscall)
void*  __cdecl FUN_0106ac90(void* self, u32 a);        // 0x0106ac90 (thiscall)
void*  __cdecl FUN_00ce6950(void* self);               // 0x00ce6950 GetCommContext (thiscall)
void*  __cdecl FUN_00b3d4a0(u32 a, void* b);           // 0x00b3d4a0 CommManager
void   __cdecl FUN_00aeaa80(void* self, u32 a, u32 b, u32 c); // 0x00aeaa80 SpaceTool::RemoveMatching2 (thiscall)
void*  __cdecl FUN_0067de30(void);                     // 0x0067de30 SP::PropertyManager
char   __cdecl FUN_00410370(void* a, u32 b, void* c);  // 0x00410370 TryGetUIntProperty
void*  __cdecl FUN_00fd9c60(void);                     // 0x00fd9c60
float  __cdecl FUN_0102f660(void* self, void* a);      // 0x0102f660 (thiscall)
void*  __cdecl FUN_005bf0e0(void* a, void* b);         // 0x005bf0e0 GetEditorPropertyList
char   __cdecl FUN_006a1250(void* a, u32 b, void* c);  // 0x006a1250 SP::GetPropertyAsKey

// helper to read a vtable slot 0..n
#define VT(obj, off) (*(void***)(obj))[(off) / 4]

// ======================================================================
// 0x00c31960 - turret health getter (lazy init).
// ======================================================================

// @ 0x00c31960
float __fastcall FUN_00c31960(void* self, void* dummy) {
  (void)dummy;
  if (0.0f >= *(float*)((char*)self + 0xec)) {
    s32 lvl = ((TFIP)FUN_00c317a0)(self);
    void* tuning = FUN_01029940((u32)lvl);
    *(float*)((char*)self + 0xec) = ((TFF)FUN_0102a780)(tuning);
  }
  return *(float*)((char*)self + 0xec);
}

// ======================================================================
// 0x00c31990 - weaponry value (bit6 of mFlags at +0x50).
// ======================================================================

// @ 0x00c31990
float __fastcall FUN_00c31990(void* self, void* dummy) {
  (void)dummy;
  if (((*(u32*)((char*)self + 0x50) >> 6) & 1) == 0) {
    s32 v = ((TFIP)FUN_00c317a0)(self) + 1;
    return (float)v + (float)v;
  }
  s32 sum = 0;
  void* home = FUN_00c31730(self);
  void* sg = FUN_01002bd0();
  int* end = (int*)(*(int*)((char*)sg + 0x30) + 0x2c);
  int* cur = (int*)*end;
  int* last = (int*)end[1];
  while (cur != last) {
    if ((void*)*cur != home) {
      sum += FUN_00c702f0((u32)*cur);
    }
    cur++;
  }
  return (float)sum * 0.125f;
}

// ======================================================================
// 0x00c31a00 - add tribute points (clamped 0..99999999).
// ======================================================================

// @ 0x00c31a00
void __fastcall FUN_00c31a00(void* self, void* dummy, s32 amount) {
  (void)dummy;
  if (99999999 - *(s32*)((char*)self + 0xd0) < amount) {
    *(s32*)((char*)self + 0xd0) = 99999999;
  } else {
    *(s32*)((char*)self + 0xd0) += amount;
  }
  s32 v = *(s32*)((char*)self + 0xd0);
  if (v < 0) {
    v = 0;
    *(s32*)((char*)self + 0xd0) = v;
    return;
  }
  if (v > 99999999) v = 99999999;
  *(s32*)((char*)self + 0xd0) = v;
}

// ======================================================================
// 0x00c31a60 - set tribute points (clamped 0..99999999).
// ======================================================================

// @ 0x00c31a60
void __fastcall FUN_00c31a60(void* self, void* dummy, s32 v) {
  (void)dummy;
  if (v < 0) {
    v = 0;
  } else if (v > 99999999) {
    v = 99999999;
  }
  *(s32*)((char*)self + 0xd0) = v;
}

// ======================================================================
// 0x00c31a90 - SP::cEmpire::GetRandomEnemy.
// ======================================================================

// @ 0x00c31a90
void* __fastcall FUN_00c31a90(void* self, void* dummy, u8 filter) {
  (void)dummy;
  int n = (int)((*(int*)((char*)self + 0x60) - *(int*)((char*)self + 0x5c)) >> 2);
  if (n <= 0) return 0;
  u32 idx = FUN_00a68fb0((void*)0x01601760, (u32)n);
  int* begin = (int*)*(int*)((char*)self + 0x5c);
  void* cand = (void*)begin[idx];
  if (filter != 0) {
    int i = 0;
    while (((*(u32*)((char*)cand + 0x50) >> 6) & 1) != 0) {
      if (i == n) return 0;
      i++;
      idx = (idx + 1) & (u32)(-((s32)(idx + 1) >= n));
      cand = (void*)begin[idx];
    }
    if (i == n) return 0;
  }
  return cand;
}

// ======================================================================
// 0x00c31b10 - is empire id in mEnemies (+0x5c..0x60).
// ======================================================================

// @ 0x00c31b10
bool __fastcall FUN_00c31b10(void* self, void* dummy, s32 id) {
  (void)dummy;
  int n = (int)((*(int*)((char*)self + 0x60) - *(int*)((char*)self + 0x5c)) >> 2);
  if (n > 0) {
    int* p = (int*)*(int*)((char*)self + 0x5c);
    int i = 0;
    while (*(s32*)((char*)(void*)*p + 0x84) != id) {
      i++;
      p++;
      if (i >= n) return false;
    }
    return true;
  }
  return false;
}

// ======================================================================
// 0x00c31b50 - SP::cEmpire::GetRandomAlly.
// ======================================================================

// @ 0x00c31b50
void* __fastcall FUN_00c31b50(void* self, void* dummy, u8 filter) {
  (void)dummy;
  int n = (int)((*(int*)((char*)self + 0x74) - *(int*)((char*)self + 0x70)) >> 2);
  if (n <= 0) return 0;
  u32 idx = FUN_00a68fb0((void*)0x01601760, (u32)n);
  int* begin = (int*)*(int*)((char*)self + 0x70);
  void* cand = (void*)begin[idx];
  if (filter != 0) {
    if (cand == FUN_01021300()) {
      if (n < 2) return 0;
      cand = (void*)begin[(idx + 1) & (u32)(-((s32)(idx + 1) >= n))];
    }
  }
  return cand;
}

// ======================================================================
// 0x00c31bc0 - is ptr in mAllies (+0x70..0x74).
// ======================================================================

// @ 0x00c31bc0
bool __fastcall FUN_00c31bc0(void* self, void* dummy, void* target) {
  (void)dummy;
  void* end = (void*)*(int*)((char*)self + 0x74);
  void* p = (void*)*(int*)((char*)self + 0x70);
  while (p != end && *(void**)p != target) p = (char*)p + 4;
  return p != end;
}

// ======================================================================
// 0x00c31bf0 - is empire id in mAllies (+0x70..0x74).
// ======================================================================

// @ 0x00c31bf0
bool __fastcall FUN_00c31bf0(void* self, void* dummy, s32 id) {
  (void)dummy;
  int n = (int)((*(int*)((char*)self + 0x74) - *(int*)((char*)self + 0x70)) >> 2);
  int i = 0;
  if (n > 0) {
    int* p = (int*)*(int*)((char*)self + 0x70);
    do {
      if (*(s32*)((char*)(void*)*p + 0x84) == id) return 1;
      i++;
      p++;
    } while (i < n);
  }
  return 0;
}

// ======================================================================
// 0x00c31ca0 - list contains self sentinel check (always 1).
// ======================================================================

// @ 0x00c31ca0
u8 __cdecl FUN_00c31ca0(u32, void* list) {
  void* p = *(void**)list;
  while (p != list) p = *(void**)p;
  return 1;
}

// ======================================================================
// 0x00c31d50 - insertion sort by distance-to-home.
// ======================================================================

// @ 0x00c31d50
void __cdecl FUN_00c31d50(void** first, void** last, float px, float py, float pz) {
  void** piVar9 = first;
  if (first != last) {
    while (1) {
      piVar9 = piVar9 + 1;
      if (piVar9 == last) break;
      void* pcVar4 = *piVar9;
      void** piVar8 = piVar9;
      if (pcVar4 != 0) {
        (*(void(__thiscall**)(void*))VT(pcVar4, 0))(pcVar4);
      }
      for (; piVar8 != first; piVar8 = piVar8 - 1) {
        void* pcVar5 = piVar8[-1];
        float* c4 = (float*)FUN_005c65e0(pcVar4);
        float f1 = c4[0], f2 = c4[1], f3 = c4[2];
        float* c5 = (float*)FUN_005c65e0(pcVar5);
        if (((c5[2] - pz) * (c5[2] - pz) + (c5[1] - py) * (c5[1] - py)) +
            (c5[0] - px) * (c5[0] - px) <=
            ((f3 - pz) * (f3 - pz) + (f1 - px) * (f1 - px)) +
            (f2 - py) * (f2 - py)) break;
        void* piVar6 = piVar8[-1];
        void* piVar7 = *piVar8;
        if (piVar6 != piVar7) {
          if (piVar6 != 0) {
            (*(void(__thiscall**)(void*))VT(piVar6, 0))(piVar6);
          }
          *piVar8 = piVar6;
          if (piVar7 != 0) {
            (*(void(__thiscall**)(void*))(VT(piVar7, 4)))(piVar7);
          }
        }
      }
      void* pcVar5 = *piVar8;
      if (pcVar4 != pcVar5) {
        if (pcVar4 != 0) {
          (*(void(__thiscall**)(void*))VT(pcVar4, 0))(pcVar4);
        }
        *piVar8 = pcVar4;
        if (pcVar5 != 0) {
          (*(void(__thiscall**)(void*))VT(pcVar5, 0))(pcVar5);
        }
      }
      if (pcVar4 != 0) {
        (*(void(__thiscall**)(void*))(VT(pcVar4, 4)))(pcVar4);
      }
    }
  }
}

// ======================================================================
// 0x00c31ed0 - insertion sort by distance-to-home.
// ======================================================================

// @ 0x00c31ed0
void __cdecl FUN_00c31ed0(void** first, void** last, float px, float py, float pz) {
  void** p = first;
  for (; p != last; p = p + 1) {
    void* pcVar4 = *p;
    void** piVar9 = p;
    if (pcVar4 != 0) {
      (*(void(__thiscall**)(void*))VT(pcVar4, 0))(pcVar4);
    }
    while (1) {
      void* pcVar5 = piVar9[-1];
      float* c4 = (float*)FUN_005c65e0(pcVar4);
      float f1 = c4[0], f2 = c4[1], f3 = c4[2];
      float* c5 = (float*)FUN_005c65e0(pcVar5);
      if (((c5[2] - pz) * (c5[2] - pz) + (c5[1] - py) * (c5[1] - py)) +
          (c5[0] - px) * (c5[0] - px) <=
          ((f3 - pz) * (f3 - pz) + (f1 - px) * (f1 - px)) +
          (f2 - py) * (f2 - py)) break;
      void* piVar6 = piVar9[-1];
      void* piVar7 = *piVar9;
      if (piVar6 != piVar7) {
        if (piVar6 != 0) {
          (*(void(__thiscall**)(void*))VT(piVar6, 0))(piVar6);
        }
        *piVar9 = piVar6;
        if (piVar7 != 0) {
          (*(void(__thiscall**)(void*))VT(piVar7, 4))(piVar7);
        }
      }
      piVar9 = piVar9 - 1;
    }
    void* pcVar5 = *piVar9;
    if (pcVar4 != pcVar5) {
      if (pcVar4 != 0) {
        (*(void(__thiscall**)(void*))VT(pcVar4, 0))(pcVar4);
      }
      *piVar9 = pcVar4;
      if (pcVar5 != 0) {
        (*(void(__thiscall**)(void*))VT(pcVar5, 4))(pcVar5);
      }
    }
    if (pcVar4 != 0) {
      (*(void(__thiscall**)(void*))VT(pcVar4, 4))(pcVar4);
    }
  }
}

// ======================================================================
// 0x00c32030 - pick nearest of two by distance-to-home.
// ======================================================================

// @ 0x00c32030
void** __cdecl FUN_00c32030(void** pa, void** pb, void** pc, float px, float py, float pz) {
  void* cb0 = *pb;
  float* cA = (float*)FUN_005c65e0(*pa);
  float f1 = cA[0], f2 = cA[1], f3 = cA[2];
  float* cB = (float*)FUN_005c65e0(cb0);
  if (((cB[2] - pz) * (cB[2] - pz) + (cB[1] - py) * (cB[1] - py)) + (cB[0] - px) * (cB[0] - px) <=
      ((f3 - pz) * (f3 - pz) + (f2 - py) * (f2 - py)) + (f1 - px) * (f1 - px)) {
    if (FUN_00c31080(*pa, *pc)) return pa;
    if (FUN_00c31080(*pb, *pc)) return pb;
  } else {
    if (FUN_00c31080(*pb, *pc)) return pb;
    if (FUN_00c31080(*pa, *pc)) return pb;
    return pa;
  }
  return 0;
}

// ======================================================================
// 0x00c32160 - eastl::promote_heap by distance-to-home.
// ======================================================================

// @ 0x00c32160
void __cdecl FUN_00c32160(void** base, s32 holeIndex, s32 length, void* cmp, float px, float py, float pz) {
  s32 parent = (holeIndex - 1) >> 1;
  while (holeIndex > length) {
    float* cA = (float*)FUN_005c65e0(base[parent]);
    float f1 = cA[0], f2 = cA[1], f3 = cA[2];
    float* cB = (float*)FUN_005c65e0((void*)cmp);
    if (((cB[2] - pz) * (cB[2] - pz) + (cB[1] - py) * (cB[1] - py)) + (cB[0] - px) * (cB[0] - px) <=
        ((f3 - pz) * (f3 - pz) + (f1 - px) * (f1 - px)) + (f2 - py) * (f2 - py)) break;
    void* t = base[holeIndex];
    void* v = base[parent];
    if (v != t) {
      if (v != 0) (*(void(__thiscall**)(void*))VT(v, 0))(v);
      base[holeIndex] = v;
      if (t != 0) (*(void(__thiscall**)(void*))VT(t, 4))(t);
    }
    holeIndex = parent;
    parent = (holeIndex - 1) >> 1;
  }
  void* cur = base[holeIndex];
  if ((void*)cmp != cur) {
    if (cmp != 0) (*(void(__thiscall**)(void*))VT(cmp, 0))((void*)cmp);
    base[holeIndex] = (void*)cmp;
    if (cur != 0) (*(void(__thiscall**)(void*))VT(cur, 4))(cur);
  }
  if (cmp != 0) (*(void(__thiscall**)(void*))VT(cmp, 4))((void*)cmp);
}

// ======================================================================
// 0x00c322c0 - test bit in +0xc4 mask.
// ======================================================================

// @ 0x00c322c0
u8 __fastcall FUN_00c322c0(void* self, void* dummy, u32 bit) {
  (void)dummy;
  u32 mask = 1u << (bit & 0x1f);
  u32 v = *(u32*)((char*)self + 0xc4) & mask;
  return (u8)(v != 0);
}

// ======================================================================
// 0x00c322f0 - SP::cPlayer::InitRelationship.
// ======================================================================

// @ 0x00c322f0
void __fastcall FUN_00c322f0(void* self, void* dummy, s32 arg) {
  (void)dummy;
  void* ren = FUN_00b3d300(*(u32*)((char*)self + 0x84));
  void* sphere = ((TFVP)FUN_00f67d90)(ren);
  if (FUN_00c7a890(sphere) != 0) return;
  ren = FUN_00b3d300(*(u32*)((char*)self + 0x84));
  sphere = ((TFVP)FUN_00f67d90)(ren);
  FUN_00c7bc20(sphere, 1);
  s32 player = FUN_01021090();
  if (*(s32*)((char*)self + 0x84) == player) return;
  void* rel = FUN_00b3d2c0();
  float a = FUN_00d01b80(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x5b6fcc9);
  float b = FUN_00d01b80(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x5b6fcd4);
  if (0.0f < a) return;
  if (0.0f < b) return;
  FUN_00d06240(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x5b6fcc9, 1.0f);
  FUN_00d06240(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x5b6fcd4, 1.0f);
  void* sm = FUN_00b3d2a0();
  void* emp = FUN_00ba9370(sm, *(u32*)((char*)self + 0x84));
  void* sm2 = FUN_00b3d2a0();
  void* rec = FUN_00baf700(sm2);
  void* props = (*(void*(__thiscall**)(void*, u32))VT(rec, 0x28))(rec, 0x5ff85b4);
  float* fp;
  if ((*(u8*)((char*)props + 0x10) & 0x30) == 0) {
    fp = (float*)(-(u32)(*(s16*)((char*)props + 0x12) != 0) & (u32)props);
  } else {
    fp = (float*)*(void**)props;
  }
  (void)emp;
  s32 mode = *(s32*)((char*)FUN_01021300() + 0x58);
  float fv;
  switch (mode) {
    case 9:  fv = fp[0]; break;
    case 10: fv = fp[1]; break;
    case 11: fv = fp[2]; break;
    case 12: fv = fp[3]; break;
    case 13: fv = fp[4]; break;
    case 14: fv = fp[5]; break;
    case 15: fv = fp[6]; break;
    case 16: fv = fp[7]; break;
    default: goto after;
  }
  if (0.0f < fv &&
      FUN_00d01b80(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x5ff85b2) == 0.0f) {
    FUN_00d06240(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x5ff85b2, fv);
  }
  if (fv < 0.0f &&
      FUN_00d01b80(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x5ff85b3) == 0.0f) {
    FUN_00d06240(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x5ff85b3, -fv);
  }
after:
  if (FUN_01002bd0() != 0) {
    void* sg = FUN_01002bd0();
    if (((TFBU)FUN_00c322c0)(sg, 7) != 0 &&
        FUN_00d01b80(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x601df2a) == 0.0f) {
      FUN_00d06240(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x601df2a, 1.0f);
    }
  }
  if (arg != 1 && FUN_00b3d2a0() != 0) {
    void* sm3 = FUN_00b3d2a0();
    void* other = FUN_00885c90(sm3);
    if (*(s32*)((char*)self + 0x84) != (s32)other &&
        FUN_00d01b50(rel, (u32)other, (u32)player) != 0 &&
        FUN_00d01fb0(rel, (u32)other, (u32)player) != 0) {
      FUN_00d01b80(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x601df2a);
      FUN_00d06240(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x68b2938, 1.0f);
    }
  }
}

// ======================================================================
// 0x00c32610 - SP::cEmpire::EndDemandForTribute.
// ======================================================================

// @ 0x00c32610
void __fastcall FUN_00c32610(void* self, void* dummy) {
  (void)dummy;
  FUN_00bc3170((char*)self + 0x128);
  s32 player = FUN_01021090();
  void* rel = FUN_00b3d2c0();
  FUN_00d06240(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x594afff, 1.0f);
  s32 ufo = *(s32*)((char*)self + 0xb0);
  s32 idx;
  if (ufo == -1) {
    idx = 0;
  } else {
    void* sm = FUN_00b3d2a0();
    idx = FUN_00ba6d80(sm, (u32)ufo);
  }
  void* sg = FUN_01002bd0();
  FUN_0106ac90((char*)sg + 0x14, (u32)idx);
  void* home = FUN_00c31730(self);
  void* ctx = FUN_00ce6950(home);
  void* cm = FUN_00b3d4a0(*(u32*)((char*)self + 0x84), ctx);
  FUN_00aeaa80(cm, 0x95bbbbfc, 0x7fc02fbc, (u32)ctx);
}

// ======================================================================
// 0x00c326b0 - SP::cEmpire::GetUFOKey.
// ======================================================================

// @ 0x00c326b0
void* __fastcall FUN_00c326b0(void* self, void* dummy) {
  (void)dummy;
  char* out = (char*)self + 0xb8;
  if (*(s32*)out != 0) return out;
  void* sm = FUN_00b3d2a0();
  void* player = FUN_00885c90(sm);
  if ((s32)player != *(s32*)((char*)self + 0x84)) {
    void* x = FUN_00fd9c60();
    FUN_0102f660((void*)*(u32*)((char*)x + 0x160), out);
    return out;
  }
  void* held = 0;
  void* pm = FUN_0067de30();
  void* pk = held;
  if (held != 0) {
    held = 0;
    (*(void(__thiscall**)(void*))VT(pk, 4))(pk);
  }
  (*(void(__thiscall**)(void*, u32, u32, void**))VT(pm, 0x2c))(pm, 0x280852f1, 0x2ae0c7e, &held);
  if (held != 0) {
    u32 uval = 0;
    FUN_00410370(held, 0x4ea8a07, &uval);
    *(u32*)out = uval;
    *(u32*)(out + 4) = (u32)0x476a98c7;
    *(u32*)(out + 8) = (u32)0x40656200;
  } else {
    void* x = FUN_00fd9c60();
    FUN_0102f660((void*)*(u32*)((char*)x + 0x160), out);
  }
  if (held != 0) {
    (*(void(__thiscall**)(void*))VT(held, 4))(held);
  }
  return out;
}

// ======================================================================
// 0x00c327a0 - remove enemy by id (swap-remove).
// ======================================================================

// @ 0x00c327a0
void __fastcall FUN_00c327a0(void* self, void* dummy, s32 id) {
  (void)dummy;
  int n = (int)((*(int*)((char*)self + 0x60) - *(int*)((char*)self + 0x5c)) >> 2);
  int i = 0;
  if (n > 0) {
    int* p = (int*)*(int*)((char*)self + 0x5c);
    while (*(s32*)((char*)(void*)*p + 0x84) != id) {
      i++;
      p++;
      if (i >= n) return;
    }
    if (i != n - 1) {
      int* base = (int*)*(int*)((char*)self + 0x5c);
      int* oldv = (int*)base[i];
      int* newv = (int*)base[n - 1];
      if (newv != oldv) {
        if (newv != 0) (*(void(__thiscall**)(void*))VT(newv, 0))(newv);
        base[i] = (int)newv;
        if (oldv != 0) (*(void(__thiscall**)(void*))VT(oldv, 4))(oldv);
      }
    }
    *(int*)((char*)self + 0x60) -= 4;
    int* tailp = (int*)*(int*)((char*)self + 0x60);
    if (*tailp != 0) {
      (*(void(__thiscall**)(void*))VT(*tailp, 4))((void*)*tailp);
    }
  }
}

// ======================================================================
// 0x00c32830 - remove ally by id (swap-remove).
// ======================================================================

// @ 0x00c32830
void __fastcall FUN_00c32830(void* self, void* dummy, s32 id) {
  (void)dummy;
  int n = (int)((*(int*)((char*)self + 0x74) - *(int*)((char*)self + 0x70)) >> 2);
  int i = 0;
  if (n > 0) {
    int* p = (int*)*(int*)((char*)self + 0x70);
    while (*(s32*)((char*)(void*)*p + 0x84) != id) {
      i++;
      p++;
      if (i >= n) return;
    }
    if (i != n - 1) {
      int* base = (int*)*(int*)((char*)self + 0x70);
      int* oldv = (int*)base[i];
      int* newv = (int*)base[n - 1];
      if (newv != oldv) {
        if (newv != 0) (*(void(__thiscall**)(void*))VT(newv, 0))(newv);
        base[i] = (int)newv;
        if (oldv != 0) (*(void(__thiscall**)(void*))VT(oldv, 4))(oldv);
      }
    }
    *(int*)((char*)self + 0x74) -= 4;
    int* tailp = (int*)*(int*)((char*)self + 0x74);
    if (*tailp != 0) {
      (*(void(__thiscall**)(void*))VT(*tailp, 4))((void*)*tailp);
    }
  }
}

// ======================================================================
// 0x00c328c0 - test property key (3 u32 map key at +0xc4).
// ======================================================================

// @ 0x00c328c0
u8 __fastcall FUN_00c328c0(void* self, void* dummy, u32* key) {
  (void)dummy;
  u32 a = *(u32*)((char*)self + 0xc4);
  u32 b = *(u32*)((char*)self + 0xc8);
  u32 c = *(u32*)((char*)self + 0xcc);
  u32* held = 0;
  for (;;) {
    if (a == key[0] && b == key[1] && c == key[2]) {
      if (held != 0) (*(void(__thiscall**)(void*))VT(held, 4))(held);
      return 1;
    }
    if (held != 0) {
      u32* tmp = held;
      held = 0;
      (*(void(__thiscall**)(void*))VT(tmp, 4))(tmp);
    }
    if (FUN_005bf0e0(&a, &held) == 0) break;
    if (FUN_006a1250(held, 0xd8a4bc9, &a) == 0) break;
  }
  if (held != 0) (*(void(__thiscall**)(void*))VT(held, 4))(held);
  return 0;
}
