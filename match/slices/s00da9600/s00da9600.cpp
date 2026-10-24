// Slice s00da9600 - citizen / tribe-AI decision cluster.
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

#define F10 float

// vtable-call signature typedefs (all thiscall)
typedef float* (__thiscall *TFV)(void*);
typedef float  (__thiscall *TFF)(void*);
typedef int    (__thiscall *TFI)(void*);
typedef void*  (__thiscall *TFVU)(void*, u32);
typedef char   (__thiscall *TFCFF)(void*, float, float);
typedef u32    (__thiscall *TFU)(void*);
typedef char   (__thiscall *TFCI)(void*, int, float, float);
typedef void*  (__thiscall *TFVP)(void*);                       // GetAny / FUN_00d997e0
typedef void*  (__thiscall *TFVST)(void*);                      // FUN_00c420d0 (ecx = self+0xc0)
typedef s32    (__thiscall *TFI3)(void*, void*, void*, u32);    // FUN_00d00a70 (ecx = relmgr)
typedef s32    (__thiscall *TCi_p)(void*);
typedef void*  (__thiscall *TCp_p)(void*);
typedef s32    (__thiscall *TCi_pu)(void*, u32);
typedef float  (__thiscall *TCf_p)(void*);
typedef s32    (__thiscall *TClookup)(void*, u32, void*);        // FUN_00af0bd0 (ecx = mgr)

// ---- external callees (address in comment) ------------------------------
float  __cdecl FUN_00c0b9c0(void* self);              // 0x00c0b9c0 (thiscall)
float  __cdecl FUN_00bfc490(void* self);              // 0x00bfc490 (thiscall)
void*  __cdecl FUN_00c22f50(void* self);              // 0x00c22f50 GetTribe (thiscall)
s32    __cdecl FUN_00c22dc0(void* self);              // 0x00c22dc0 (thiscall)
s32    __cdecl FUN_00c22dd0(void* self);              // 0x00c22dd0 (thiscall)
s32    __cdecl FUN_00c0b780(void* self);              // 0x00c0b780 (thiscall)
s32    __cdecl FUN_00c0b7a0(void* self);              // 0x00c0b7a0 (thiscall)
s32    __cdecl FUN_00c0d560(void* self, float a, float b); // 0x00c0d560 (thiscall)
void*  __cdecl FUN_00c420d0();                       // 0x00c420d0 (thiscall: ecx = self+0xc0)
void*  __cdecl FUN_00d99470(void* a);                 // 0x00d99470
void*  __cdecl FUN_00d994c0(void* a);                 // 0x00d994c0
void*  __cdecl FUN_00d99420(void* a, u32 b);          // 0x00d99420
void*  __cdecl FUN_00d996e0(void* a, void* b);        // 0x00d996e0
void*  __cdecl FUN_00d997e0(void* self);              // 0x00d997e0 behavior_stimuli::GetAny (thiscall)
void*  __cdecl FUN_00d999d0(void* a);                 // 0x00d999d0 WatchMemoryBlock
s32    __cdecl FUN_00c8f730(void* self, u32 a);       // 0x00c8f730 (thiscall)
void   __cdecl FUN_00c8f470(void* self, u32 a, u32 b, u32 c, void* d); // 0x00c8f470 SetStimuli (thiscall)
s32    __cdecl FUN_00c8f6e0(void* self, u32 a);       // 0x00c8f6e0 GetToolOfType (thiscall)
void*  __cdecl FUN_00c8fe20(void* self);              // 0x00c8fe20 GetClosestWater (thiscall)
void   __cdecl FUN_00c24680(u32 a, u32 b, float c, u32 d, u32 e, u32 f); // 0x00c24680
void*  __cdecl FUN_00bc96a0(void* self, u32 a, u32 b); // 0x00bc96a0 Play (thiscall)
void   __cdecl FUN_00bc97f0(u32 a, u32 b, void* c, void* d); // 0x00bc97f0
void   __cdecl FUN_00bc98f0(void* self, u32 a, u32 b); // 0x00bc98f0 ClearAll (thiscall)
float  __cdecl FUN_00da82f0(void* tribe, u32 key);    // 0x00da82f0
float  __cdecl FUN_00da83b0(void* tribe, void* a);    // 0x00da83b0
s32    __cdecl FUN_00d00a70(void* a, void* b, u32 c);  // 0x00d00a70
char   __cdecl FUN_00da6b10(void* a, void* b);        // 0x00da6b10
void*  __cdecl FUN_00af13b0(void* a, u32 b, void* c);  // 0x00af13b0 CreateLayoutManager
s32    __cdecl FUN_00af0bd0(void* a, u32 b, void* c);  // 0x00af0bd0 LayoutMgr::LookupB
void*  __cdecl FUN_00b3d2c0(void);                    // 0x00b3d2c0 RelationshipManager
void*  __cdecl FUN_00b5b800(void);                    // 0x00b5b800 SP::GetCurrentGameMode
void*  __cdecl FUN_00ffbe50(void);                    // 0x00ffbe50 SP::GetUFOSimulator
void*  __cdecl FUN_00a1ad60(void* self);              // 0x00a1ad60 GetPlayerInventory (thiscall)
s32    __cdecl FUN_00c38990(void* self, u32 a);       // 0x00c38990 (thiscall)
void   __cdecl FUN_00c238b0(void* self);              // 0x00c238b0 UpdateCreatureToolInteractions
void*  __cdecl FUN_010407c0(void);                    // 0x010407c0 SP::GetSpaceRelationshipTuning
s32    __cdecl FUN_00b1fbf0(void* self);              // 0x00b1fbf0 (thiscall) predicate

extern u32 DAT_01654c02;

// ======================================================================
// 0x00da9600 - SP::TRIBE_AREA_INTRUDERS_Decide.
// ======================================================================

// @ 0x00da9600
F10 __cdecl FUN_00da9600(void* p) {
  int* piVar2 = (int*)FUN_00c22f50(p);
  if (piVar2 == 0) return 0.0f;

  int pi48 = piVar2[0x48];
  float* pfVar3 = ((TFV)(*(void***)pi48)[0x2c / 4])((void*)pi48);
  F10 fVar13 = ((TFF)(*(void***)piVar2)[0x60 / 4])((void*)piVar2);
  int iVar4 = ((TFI)(*(void***)piVar2)[0x4c / 4])((void*)piVar2);

  int* piTmp = (int*)FUN_00c420d0();
  int* piEnd = (int*)piTmp[1];
  int* piCur = (int*)*piTmp;
  if (piCur != piEnd) {
    do {
      void* uVar6;
      if ((void*)*piCur == 0) {
        uVar6 = 0;
      } else {
        void* obj = (void*)*piCur;
        uVar6 = (void*)((TFVU)(*(void***)obj)[0xb8 / 4])(obj, 0xce9f6639);
      }
      int* piVar7 = (int*)FUN_00d99470(uVar6);
      if (piVar7 != 0) {
        int iVar8 = ((TFI)(*(void***)piVar7)[0x4c / 4])((void*)piVar7);
        if (iVar8 != iVar4) {
          char cVar1 = (char)FUN_00c0d560(piVar7, 1.0f, 0.0f);
          if (cVar1 == 0) {
            cVar1 = ((TFCFF)(*(void***)p)[0xc0 / 4])(p, 1.0f, 0.0f);
            if (cVar1 == 0) goto LAB_00da97b3;
          }
          void* puVar9 = ((TFV)(*(void***)piVar7)[0x20 / 4])((void*)piVar7);
          float fVar14;
          if (puVar9 == (void*)0x018eb45e) {
            int pi30 = piVar7[0x30];
            float* pfVar10 = ((TFV)(*(void***)pi30)[0x2c / 4])((void*)pi30);
            fVar14 = ((pfVar10[1] - pfVar3[1]) * (pfVar10[1] - pfVar3[1]) +
                      (*pfVar10 - *pfVar3) * (*pfVar10 - *pfVar3)) +
                     (pfVar10[2] - pfVar3[2]) * (pfVar10[2] - pfVar3[2]);
          } else {
            void* puVar11 = ((TFV)(*(void***)piVar7)[0x20 / 4])((void*)piVar7);
            if (puVar11 != (void*)0x018eb4b7) goto LAB_00da97b3;
            char cVar2 = (char)FUN_00da6b10(p, piVar7);
            if (cVar2 == 0) goto LAB_00da97b3;
            int pi30 = piVar7[0x30];
            float* pfVar10 = ((TFV)(*(void***)pi30)[0x2c / 4])((void*)pi30);
            fVar14 = ((pfVar10[2] - pfVar3[2]) * (pfVar10[2] - pfVar3[2]) +
                      (pfVar10[1] - pfVar3[1]) * (pfVar10[1] - pfVar3[1])) +
                     (*pfVar10 - *pfVar3) * (*pfVar10 - *pfVar3);
          }
          // LAB_00da97a8:
          if (fVar14 < fVar13 * fVar13) {
            void* pcVar12 = FUN_00c22f50(p);
            FUN_00c8f470(pcVar12, 0, 0x4000, 0x40a00000, piVar7);
            break;
          }
        }
      }
    LAB_00da97b3:
      piCur = piCur + 1;
      if (piCur == piEnd) return 0.0f;
    } while (1);
  }
  return 0.0f;
}

// ======================================================================
// 0x00da9800.
// ======================================================================

// @ 0x00da9800
F10 __cdecl FUN_00da9800(void* p) {
  F10 fVar11 = (F10)FUN_00c0b9c0(p);
  if (fVar11 < (F10)1.5258789e-05f) return 0.0f;
  fVar11 = (F10)FUN_00bfc490((char*)p + 0x5a8);
  if (fVar11 * (F10)100.0f >= (F10)*(float*)0x01687a14) return 0.0f;

  int iVar7 = (int)FUN_00c22f50(p);
  float* pfVar8 = ((TFV)(*(void***)(iVar7 + 0x120))[0x2c / 4])((void*)(iVar7 + 0x120));
  float* pfVar9 = ((TFV)(*(void***)((char*)p + 0xc0))[0x2c / 4])((char*)p + 0xc0);
  float fVar1 = *pfVar9;
  float fVar2 = *pfVar8;
  float fVar3 = pfVar9[1];
  float fVar4 = pfVar8[1];
  float fVar5 = pfVar9[2];
  float fVar6 = pfVar8[2];
  int* piVar10 = (int*)FUN_00c22f50(p);
  F10 fVar13 = (F10)((TFF)(*(void***)piVar10)[0x60 / 4])((void*)piVar10);
  if (((fVar5 - fVar6) * (fVar5 - fVar6) + (fVar1 - fVar2) * (fVar1 - fVar2)) +
      (fVar3 - fVar4) * (fVar3 - fVar4) < fVar13 * fVar13) {
    return 1.0f;
  }
  return 0.0f;
}

// ======================================================================
// 0x00da9900.
// ======================================================================

// @ 0x00da9900
F10 __cdecl FUN_00da9900(void* p) {
  float fStack_4 = 0.0f;
  void* mgr = FUN_00af13b0(p, 2, &fStack_4);
  if ((char)((TClookup)FUN_00af0bd0)(mgr, 2, &fStack_4) == 0) return 0.0f;
  void* tribe = FUN_00c22f50(p);
  F10 fVar2 = (F10)FUN_00da82f0(tribe, 0x4611758);
  if (fVar2 < (F10)fStack_4) return 1.0f;
  return 0.0f;
}

// ======================================================================
// 0x00da9a00 - SP::TRIBE_SCHEDULED_FORAGE_Decide.
// ======================================================================

// @ 0x00da9a00
F10 __cdecl FUN_00da9a00(void* p, u32, u32, u8 param_4, void* stim, u8* outflag) {
  void* gm = FUN_00b5b800();
  if (gm == (void*)0x01654c02) return 0.0f;

  float fStack_4 = 0.0f;
  if ((char)FUN_00c0b7a0(p) == 0) return 0.0f;

  void* mgr = FUN_00af13b0(p, 4, &fStack_4);
  if ((char)((TClookup)FUN_00af0bd0)(mgr, 4, &fStack_4) == 0) return 0.0f;

  void* tribe = FUN_00c22f50(p);
  F10 fVar5 = (F10)FUN_00da82f0(tribe, 0x569236e);
  int iVar4 = FUN_00c22dc0(p);
  if (iVar4 == 7) goto LAB_00da9a97;
  if ((param_4 & 1) == 0) {
    iVar4 = FUN_00c8f6e0(tribe, 7);
    if (iVar4 == 0 && (float)fVar5 < fStack_4) goto LAB_00da9a97;
  }
  return 0.0f;

LAB_00da9a97:
  if ((param_4 & 1) == 0) {
    if (stim != 0) {
      FUN_00d997e0(stim);
    }
    *(int*)((char*)stim + 0x18) = 1;
    *outflag = 1;
  }
  return 1.0f;
}

// ======================================================================
// 0x00da9ad0.
// ======================================================================

// @ 0x00da9ad0
F10 __cdecl FUN_00da9ad0(void* p, u32, u32, u8 param_4) {
  void* gm = FUN_00b5b800();
  if (gm == (void*)0x01654c02) return 0.0f;

  float fStack_4 = 0.0f;
  void* tribe = FUN_00c22f50(p);
  if ((char)FUN_00b1fbf0(tribe) == 0) return 0.0f;

  float* pfVar4 = (float*)FUN_00c8fe20(tribe);
  if (*pfVar4 == *(float*)0x0169f3b8 &&
      pfVar4[1] == *(float*)0x0169f3bc &&
      pfVar4[2] == *(float*)0x0169f3c0) {
    return 0.0f;
  }

  void* mgr = FUN_00af13b0(p, 5, &fStack_4);
  if ((char)((TClookup)FUN_00af0bd0)(mgr, 5, &fStack_4) == 0) return 0.0f;

  if (FUN_00c22dc0(p) == 8) goto LAB_00da9bb0;
  if ((param_4 & 1) != 0) return 0.0f;
  if (FUN_00c8f6e0(tribe, 8) != 0) return 0.0f;
  {
    void* q = (void*)*(u32*)0x0169ef30;
    u32 uVar8 = ((TFU)(*(void***)q)[0x1c / 4])(q);
    F10 fVar6 = (F10)FUN_00da83b0(tribe, (void*)uVar8);
    if (fVar6 >= (F10)fStack_4) return 0.0f;
  }
LAB_00da9bb0:
  {
    u32 q = *(u32*)0x0169ef30;
    float fv = *(float*)0x0147c218;
    FUN_00c24680(0, 0x800, fv, q, 0, 0);
  }
  {
    void* e = (char*)p + 0xb4c;
    void* played = FUN_00bc96a0((void*)(*(u32*)e + 8), 0, 0x800);
    *(u32*)((char*)played + 0x14) = 1;
    FUN_00bc98f0((void*)(*(u32*)e + 8), 1, 0);
  }
  return 1.0f;
}

// ======================================================================
// 0x00da9c10 - SP::TRIBE_SCHEDULED_HUNT_Decide.
// ======================================================================

// @ 0x00da9c10
F10 __cdecl FUN_00da9c10(void* p, u32, u32, u8 param_4) {
  if ((char)((TCi_p)FUN_00c0b780)(p) == 0) return 0.0f;
  void* gm = FUN_00b5b800();
  if (gm == (void*)0x01654c02) return 0.0f;

  void* fStack = 0;
  void* mgr = FUN_00af13b0(p, 3, &fStack);
  if ((char)((TClookup)FUN_00af0bd0)(mgr, 3, &fStack) == 0) return 0.0f;

  if (((TCi_p)FUN_00c22dd0)(p) == 1) goto LAB_00da9c93;
  {
    void* tribe = ((TCp_p)FUN_00c22f50)(p);
    char cVar2 = (char)((TCi_pu)FUN_00c8f730)(tribe, 1);
    if ((param_4 & 1) == 0 && cVar2 != 0) {
      F10 fVar5 = (F10)FUN_00da82f0(tribe, 0x5218bb3);
      if (fVar5 < (F10)(float)(int)fStack) goto LAB_00da9c93;
    }
  }
  return 0.0f;
LAB_00da9c93:
  return 1.0f;
}

// ======================================================================
// 0x00da9ca0.
// ======================================================================

// @ 0x00da9ca0
F10 __cdecl FUN_00da9ca0(int* p) {
  if (*(int*)(p[0x2d3] + 0x1d8) == 0x5218bb3) return 0.0f;

  void* uVar8 = FUN_00bc96a0((void*)(p[0x2d3] + 8), 0, 0x80);
  int iVar9 = (int)FUN_00d999d0(uVar8);
  if (iVar9 != 0 && *(char*)(iVar9 + 0xb5e) == 0) {
    int i0 = *(int*)(iVar9 + 0xc0);
    float* pfVar10 = ((TFV)(*(void***)i0)[0x2c / 4])((void*)i0);
    int p30 = p[0x30];
    float* pfVar11 = ((TFV)(*(void***)p30)[0x2c / 4])((void*)p30);
    float fVar1 = *pfVar11;
    float fVar2 = *pfVar10;
    float fVar3 = pfVar11[1];
    float fVar4 = pfVar10[1];
    float fVar5 = pfVar11[2];
    float fVar6 = pfVar10[2];
    F10 fVar12 = (F10)((TFF)(*(void***)i0)[0x74 / 4])((void*)i0);
    F10 fVar13 = (F10)((TFF)(*(void***)p30)[0x74 / 4])((void*)p30);
    float dist = (float)fVar12;
    F10 d = (F10)(
        (float)sqrtf(
            ((fVar5 - fVar6) * (fVar5 - fVar6) + (fVar3 - fVar4) * (fVar3 - fVar4)) +
            (fVar1 - fVar2) * (fVar1 - fVar2)) -
        (fVar13 + (float)dist));
    char cVar7 = (char)FUN_00c0d560((void*)iVar9, 1.0f, (float)d);
    if (cVar7 == 0) {
      cVar7 = ((TFCI)(*(void***)p)[0xc0 / 4])(p, iVar9, 1.0f, (float)d);
      if (cVar7 == 0) return 0.0f;
    }
    return 1.0f;
  }
  return 0.0f;
}

// ======================================================================
// 0x00da9db0 - SP::TRIBE_STEAL_BABY_Activate.
// ======================================================================

// @ 0x00da9db0
F10 __cdecl FUN_00da9db0(int* p, double param_2, u32 param_3, u32, u32, int in20) {
  char cVarA = (*(char(__thiscall**)(void*))(*(void***)p[0x30] + 0x48 / 4))((void*)p[0x30]);
  if ((cVarA == 0) && ((param_3 & 0x300) != 0)) return 0.0f;
  if (*(int*)(in20 + 0xd) == -1) return 0.0f;
  u32 uVar3 = *(int*)(in20 + 0x2d) + 1;
  if (uVar3 >= 6) return 0.0f;

  int iVar5 = p[0x2d3];
  int iVar4 = uVar3 * 0xac;
  double dVar1 = *(double*)(iVar4 + 0x1f0 + iVar5);
  char cVarB = (*(char(__thiscall**)(void*))(*(void***)p[0x30] + 0x58 / 4))((void*)p[0x30]);
  if (cVarB != 0 &&
      !(*(int*)(iVar4 + 0x1e0 + iVar5) == *(int*)(p[0x2d3] + 0x1d0) && 10.0 < param_2 - dVar1)) {
    return 0.0f;
  }

  FUN_00b3d2c0();
  int iVarBase = ((TFI)(*(void***)p)[0x4c / 4])((void*)p);
  int* piVar6 = (int*)FUN_00c420d0();
  int* piVar10 = (int*)*piVar6;
  piVar6 = (int*)piVar6[1];
  if (piVar10 != piVar6) {
    do {
      int* piVar7;
      if ((void*)*piVar10 != 0 &&
          (piVar7 = (int*)((TFVU)(*(void***)(void*)*piVar10)[0xb8 / 4])((void*)*piVar10, 0x4f176642),
           piVar7 != 0) &&
          ((iVar4 = ((TFI)(*(void***)piVar7)[0x4c / 4])((void*)piVar7), iVar4 == iVarBase) ||
           (iVar4 = FUN_00d00a70((void*)iVarBase, (void*)iVar4, 1), 2 < iVar4))) {
        int iVar4b = (int)FUN_00bc96a0((void*)(piVar7[0x2d3] + 8), 0, 0x80);
        if (iVar4b != 0) {
          void* uVar8 = FUN_00d999d0((void*)iVar4b);
          int* piVar7b = (int*)FUN_00d994c0(uVar8);
          if (piVar7b == 0 ||
              ((TFI)(*(void***)piVar7b)[0x4c / 4])((void*)piVar7b) != iVarBase) {
            FUN_00bc97f0(0, 0x80, *(void**)(iVar4b + 8), *(void**)(iVar4b + 0x2c));
            break;
          }
        }
      }
      piVar10 = piVar10 + 1;
      if (piVar10 == piVar6) return 0.0f;
    } while (1);
  }
  return 0.0f;
}

// ======================================================================
// 0x00da9f40.
// ======================================================================

// @ 0x00da9f40
F10 __cdecl FUN_00da9f40(int* p, u32, u32, u32 param_4) {
  char cVar1 = (*(char(__thiscall**)(void*))(*(void***)p[0x30] + 0x48 / 4))((void*)p[0x30]);
  if ((cVar1 == 0) && ((param_4 & 0x300) == 0)) return 0.0f;

  FUN_00b3d2c0();
  int iVar2 = ((TFI)(*(void***)p)[0x4c / 4])((void*)p);
  int* piVar3 = (int*)FUN_00c420d0();
  int* piVar8 = (int*)*piVar3;
  piVar3 = (int*)piVar3[1];
  if (piVar8 != piVar3) {
    do {
      int* piVar4;
      if ((void*)*piVar8 != 0 &&
          (piVar4 = (int*)((TFVU)(*(void***)(void*)*piVar8)[0xb8 / 4])((void*)*piVar8, 0x4f176642),
           piVar4 != 0) &&
          (((TFI)(*(void***)piVar4)[0x4c / 4])((void*)piVar4) == iVar2 ||
           FUN_00d00a70((void*)iVar2, (void*)((TFI)(*(void***)piVar4)[0x4c / 4])((void*)piVar4), 1) > 2)) {
        int iVar5 = (int)FUN_00bc96a0((void*)(piVar4[0x2d3] + 8), 0, 0x80);
        if (iVar5 != 0) {
          void* uVar6 = FUN_00d999d0((void*)iVar5);
          int* piVar7 = (int*)FUN_00d994c0(uVar6);
          if (piVar7 == 0 ||
              ((TFI)(*(void***)piVar7)[0x4c / 4])((void*)piVar7) != iVar2) {
            iVar5 = (int)FUN_00bc96a0((void*)(piVar4[0x2d3] + 8), 0, 0x80);
            if (iVar5 != 0) {
              FUN_00bc97f0(0, 0x80, *(void**)(iVar5 + 8), *(void**)(iVar5 + 0x2c));
              break;
            }
          }
        }
      }
      piVar8 = piVar8 + 1;
      if (piVar8 == piVar3) return 0.0f;
    } while (1);
  }
  return 0.0f;
}

// ======================================================================
// 0x00daa070.
// ======================================================================

// @ 0x00daa070
F10 __cdecl FUN_00daa070(void* p, u32, u32, u32 param_4) {
  if ((param_4 & 2) == 0) return 0.0f;

  int* piVar8 = (int*)FUN_00c22f50(p);
  int iVar9 = ((TFI)(*(void***)piVar8)[0xac / 4])((void*)piVar8);

  int q0 = *(int*)(iVar9 + 0x34);
  float* pfVar10 = ((TFV)(*(void***)q0)[0x2c / 4])((void*)(iVar9 + 0x34));
  int p0 = *(int*)((char*)p + 0xc0);
  float* pfVar11 = ((TFV)(*(void***)p0)[0x2c / 4])((char*)p + 0xc0);
  float fVar2 = *pfVar11;
  float fVar3 = *pfVar10;
  float fVar4 = pfVar11[1];
  float fVar5 = pfVar10[1];
  float fVar6 = pfVar11[2];
  float fVar7 = pfVar10[2];
  F10 fVar12 = (F10)((TFF)(*(void***)q0)[0x70 / 4])((void*)(iVar9 + 0x34));
  F10 fVar13 = (F10)((TFF)(*(void***)p0)[0x70 / 4])((char*)p + 0xc0);
  float diff = (float)((float)fVar12 - (float)fVar13);
  if (diff * diff < ((fVar6 - fVar7) * (fVar6 - fVar7) + (fVar4 - fVar5) * (fVar4 - fVar5)) +
                        (fVar2 - fVar3) * (fVar2 - fVar3)) {
    FUN_00c238b0(p);
  }
  u32* puVar1 = (u32*)(*(int*)((char*)p + 0xb4c) + 0x5fc);
  *puVar1 = *puVar1 & 0xffffff7f;
  return 0.0f;
}

// ======================================================================
// 0x00daa170.
// ======================================================================

// @ 0x00daa170
F10 __cdecl FUN_00daa170(int* p, u32, u32, u32, void* stim, u8* outflag) {
  int* piVar5 = 0;
  void* pvVar1 = 0;
  void* pvVar2 = 0;
  void* pvVar3 = 0;
  int iVar4 = (int)FUN_00bc96a0((void*)(p[0x2d3] + 8), 0x400000, 0);
  if (iVar4 != 0) {
    piVar5 = (int*)FUN_00d999d0((void*)iVar4);
    if (piVar5 != 0) {
      int iVar6 = ((TFI)(*(void***)piVar5)[0x4c / 4])((void*)piVar5);
      if (iVar6 != -1) {
        pvVar1 = *(void**)(iVar4 + 0xc);
        pvVar2 = *(void**)(iVar4 + 0x10);
        pvVar3 = *(void**)(iVar4 + 0x14);
        int pq = piVar5[0x30];
        float* pfVar7 = ((TFV)(*(void***)pq)[0x2c / 4])((void*)pq);
        float fVar11 = (float)(int)pvVar3 - pfVar7[2];
        float fVar10 = (float)(int)pvVar2 - pfVar7[1];
        float fVar9 = (float)(int)pvVar1 - *pfVar7;
        if ((fVar11 * fVar11 + fVar10 * fVar10) + fVar9 * fVar9 <= 1.0f) {
          FUN_00b3d2c0();
          int iVar4b = ((TFI)(*(void***)p)[0x4c / 4])((void*)p);
          if (iVar4b == iVar6) goto LAB_00daa278;
          if (FUN_00d00a70((void*)iVar4b, (void*)iVar6, 1) > 2) goto LAB_00daa278;
          if (FUN_00d00a70((void*)iVar6, (void*)iVar4b, 1) > 2) goto LAB_00daa278;
        }
      }
    }
  }
  FUN_00bc98f0((void*)(p[0x2d3] + 8), 0x400000, 0);
  return 0.0f;

LAB_00daa278:
  if (stim != 0) {
    FUN_00d997e0(stim);
  }
  *outflag = 1;
  *(void**)((char*)stim + 0x0) = pvVar1;
  *(int**)((char*)stim + 0x4) = piVar5 + 0x16a;
  *(void**)((char*)stim + 0x8) = pvVar2;
  *(void**)((char*)stim + 0xc) = pvVar3;
  FUN_00bc98f0((void*)(p[0x2d3] + 8), 0x400000, 0);
  return 1.0f;
}

// ======================================================================
// 0x00daa2f0.
// ======================================================================

// @ 0x00daa2f0
F10 __cdecl FUN_00daa2f0(int param_1, u32, u32, u32, void* stim, u8* outflag) {
  int iVar8 = (int)FUN_010407c0();
  if (*(char*)(iVar8 + 0x4c) == 0) return 0.0f;

  iVar8 = (int)FUN_00ffbe50();
  if (iVar8 == 0) return 0.0f;
  void* pcVar9 = FUN_00ffbe50();
  iVar8 = (int)FUN_00a1ad60(pcVar9);
  if (iVar8 == 0) return 0.0f;
  char cVar7 = (char)FUN_00c38990((void*)iVar8, 1);
  if (cVar7 != 0) return 0.0f;

  int q0 = *(int*)(iVar8 + 0x34);
  float* pfVar10 = ((TFV)(*(void***)q0)[0x2c / 4])((void*)(iVar8 + 0x34));
  int p0 = *(int*)(param_1 + 0xc0);
  float* pfVar11 = ((TFV)(*(void***)p0)[0x2c / 4])((void*)(param_1 + 0xc0));
  float fVar1 = *pfVar11;
  float fVar2 = *pfVar10;
  float fVar3 = pfVar11[1];
  float fVar4 = pfVar10[1];
  float fVar5 = pfVar11[2];
  float fVar6 = pfVar10[2];
  int iVar12 = (int)FUN_010407c0();
  float r = *(float*)(iVar12 + 0x44);
  if (((fVar5 - fVar6) * (fVar5 - fVar6) + (fVar3 - fVar4) * (fVar3 - fVar4)) +
      (fVar1 - fVar2) * (fVar1 - fVar2) >= r * r) {
    return 0.0f;
  }
  if (stim != 0) {
    FUN_00d997e0(stim);
  }
  *outflag = 1;
  *(int*)((char*)stim + 0x4) = iVar8 + 0x508;
  iVar8 = (int)FUN_010407c0();
  *(void**)((char*)stim + 0xc) = (void*)(int)*(float*)(iVar8 + 0x44);
  return 1.0f;
}

// ======================================================================
// 0x00daa420 - SP::cUFOAbductionEvent::ShouldDeactivate.
// ======================================================================

// @ 0x00daa420
F10 __cdecl FUN_00daa420(int param_1, u32, u32, u32, void* stim, u8* outflag, int in20) {
  if (stim != 0) {
    FUN_00d997e0(stim);
  }
  *outflag = 1;
  void* uVar6 = FUN_00d99420((void*)(*(int*)(param_1 + 0xb4c) + 0x1d0), *(u32*)(in20 + 0x2d));
  FUN_00d996e0(uVar6, stim);
  float fVar5 = (float)(int)*(void**)((char*)stim + 0xc);
  if ((int)*(void**)((char*)stim + 0xc) < 0) {
    fVar5 = fVar5 + 4.2949673e+09f;
  }
  int* piVar4 = *(int**)((char*)stim + 0x4);
  int iVar7;
  if (piVar4 == 0) {
    iVar7 = 0;
  } else {
    iVar7 = (*(int(__thiscall**)(void*, u32))(*(void***)piVar4 + 0x5c / 4))(piVar4, 0xb033b403);
  }
  int q0 = *(int*)(iVar7 + 0x34);
  float* pfVar8 = ((TFV)(*(void***)q0)[0x2c / 4])((void*)(iVar7 + 0x34));
  float fVar1 = *pfVar8;
  float fVar2 = pfVar8[1];
  float fVar3 = pfVar8[2];
  int p0 = *(int*)(param_1 + 0xc0);
  pfVar8 = ((TFV)(*(void***)p0)[0x2c / 4])((void*)(param_1 + 0xc0));
  if (((pfVar8[2] - fVar3) * (pfVar8[2] - fVar3) + (pfVar8[1] - fVar2) * (pfVar8[1] - fVar2)) +
      (*pfVar8 - fVar1) * (*pfVar8 - fVar1) < (fVar5 * 0.5f) * (fVar5 * 0.5f)) {
    return 1.0f;
  }
  return 0.0f;
}
