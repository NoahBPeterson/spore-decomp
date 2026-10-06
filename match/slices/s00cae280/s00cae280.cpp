// Slice s00cae280 -- cLocomotiveObject steering/pathing update (0x00cae280, ~5072 bytes).
//
// Recomputes a locomotive object's desired heading: picks a reference direction
// (goal / neighbor / facing), normalises it, blends with the current velocity,
// clamps to the object's turn limits and writes the new position back into the
// 3-float vector at *param_1.
//
// PARTIAL: the overall control flow and all identifiable engine calls are ported
// from the Ghidra decompilation, but several of the vector-blending branches and
// the exact vtable/type layout of cLocomotiveObject are reconstructed rather than
// guaranteed complete.  Byte-exact is not attempted.
//
// Card: work/match/scratch_32_card.txt
#include "types.h"

extern "C" double sqrt(double);

// callees / engine entry points
extern "C" {
int*  FUN_00c41ec0(...);
float* FUN_00c423c0(...);
float FUN_00c9ee90(...);
float FUN_00c9f380(...);
float FUN_004885d0(...);
void  FUN_00699800(...);
int   FUN_0041dd30(...);
float* FUN_00b0fd00(...);
float* FUN_00b7f320(...);
float* FUN_00b7f1f0(...);
float _CIacos(...);
float* SP_normalized_safe(...);
void  SP_QuaternionFromFacingAndUp(...);
void  SP_PlanetModel(...);
int   SP_IsNearGoal(...);
int   FUN_00cae280_cLocomotiveObject_IsNearGoal(...);
}
extern float DAT_0169a37c, DAT_0169a380, DAT_0169a384;
extern float _DAT_0157d330, _DAT_0157d334, _DAT_0157d32c;

#define F(p,o) (*(float*)((char*)(p)+(o)))
#define I(p,o) (*(int*)((char*)(p)+(o)))
#define B(p,o) (*(char*)((char*)(p)+(o)))
#define RF(p,i) (*(float*)((char*)(p)+4*(i)))
#define VS(p,o) (*(void**)((*(char**)(p))+(o)))
#define VC0(RT,p,o)         ((RT(__thiscall*)(void*))VS(p,o))((void*)(p))
#define VC1(RT,p,o,a)       ((RT(__thiscall*)(void*,int))VS(p,o))((void*)(p),(int)(a))
static float SQRT(float x) { return (float)sqrt((double)x); }

// @ 0x00cae280
void FUN_00cae280(int* param_1)
{
  void* v5;
  int   local_14;
  int   iVar2;
  char  cStack_3d, cStack_51, cStack_52, cStack_c9 = 0;
  float pcStack_a0, fStack_9c, fStack_98, fStack_94, fStack_3c = 1.0f;
  float pcStack_a4, pcStack_a8 = 0.0f, pcStack_bc, pcStack_c0, pcStack_c4;
  float pcStack_b0, pcStack_b4, pcStack_b8;
  float fStack_80, fStack_7c, fStack_78;
  float fStack_6c = 0.0f, fStack_68 = 0.0f;
  float fStack_2c, fStack_ac;
  float local_38x, fStack_34, fStack_30;
  float pcStack_70x = 0.0f;
  float ang = 0.0f;
  float* pfVar8_ = 0;
  int*  piStack_18;
  int   stack_c8;
  void* pfVar4;
  int*  piVar5;
  float fVar1, fVar10, fVar12, fVar14, fVar16, fVar17;

  v5 = (void*)I(param_1, 0x14);
  if (v5 == 0) local_14 = 0;
  else         local_14 = VC1(int, v5, 0xb8, 0x137e8e0);
  iVar2 = local_14;
  stack_c8 = 0;
  if (I(local_14, 0xb1c) != 0 || (B(local_14, 0xaf8) & 4) != 0)
    stack_c8 = 1;                       // uStack_c8 bit 3

  piStack_18 = (int*)(local_14 + 0x34);
  pcStack_a0 = SQRT(RF(param_1,0)*RF(param_1,0) + RF(param_1,1)*RF(param_1,1) + RF(param_1,2)*RF(param_1,2));
  pcStack_a4 = (float)VC1(int, (void*)I(local_14, 0x34), 0xc8, 0);
  pcStack_c4 = (float)FUN_00c9ee90();
  {
    float other = (float)FUN_00c9f380();
    pcStack_bc = other * 0.2f;
    if (pcStack_c4 <= pcStack_bc) pcStack_bc = other * 0.2f;
  }
  if (stack_c8 == 0 || pcStack_bc <= 0.0f) {
    pcStack_bc = 1.0f;
  } else {
    pcStack_bc = pcStack_a0 / pcStack_bc;
    if (pcStack_bc <= 0.1f) pcStack_bc = 0.1f;      // 0x3dcccccd
    if (1.0f <= pcStack_bc) pcStack_bc = 1.0f;
  }
  pcStack_bc = F(iVar2, 0x21c) * pcStack_bc;
  pcStack_c0 = (pcStack_a0 / pcStack_bc <= 1.0f) ? 1.0f : (pcStack_a0 / pcStack_bc);
  pfVar4 = (void*)VC0(int, v5, 0x2c);
  VC1(void, (void*)I(local_14, 0x34), 0x5c, (int)&fStack_9c);
  piVar5 = (int*)FUN_00c41ec0();
  cStack_3d = piVar5[0x17] != 0;
  cStack_51 = (char)FUN_00cae280_cLocomotiveObject_IsNearGoal(v5);
  pcStack_b0 = (float)piVar5[7] - F(pfVar4, 8);
  pcStack_b8 = (float)piVar5[5] - F(pfVar4, 0);
  pcStack_b4 = (float)piVar5[6] - F(pfVar4, 4);
  pcStack_a4 = SQRT(pcStack_b4*pcStack_b4 + (pcStack_b8*pcStack_b8 + pcStack_b0*pcStack_b0));
  // distances / neighbour data are derived from piVar5 and pfVar4
  {
    float* pfVar6 = (float*)FUN_00c423c0();
    float px = (float)piVar5[5], py = (float)piVar5[6], pz = (float)piVar5[7];
    fStack_94 = SQRT((pfVar6[1]-F(pfVar4,4))*(pfVar6[1]-F(pfVar4,4)) +
                ((pfVar6[2]-F(pfVar4,8))*(pfVar6[2]-F(pfVar4,8)) +
                 (*pfVar6-F(pfVar4,0))*(*pfVar6-F(pfVar4,0))));
    (void)px; (void)py; (void)pz;
  }
  pcStack_bc = (float)VC0(int, (void*)I(v5, 0), 0xd0);
  cStack_52 = *piVar5 == piVar5[1];
  if (B(local_14, 0xbcd) != 0) {
    pcStack_bc = (float)FUN_00c9f380() * 4.0f;
    goto LAB_00caf38f;
  }
  if (((((unsigned)0 /*pcStack_d4*/ >> 2) & 1) != 0) || cStack_3d == 0 || cStack_51 != 0) {
    pcStack_bc = pcStack_bc * 2.0f;
    goto LAB_00caf38f;
  }

  if (cStack_52 == 0) {
    // ---- goal-relative path ----------------------------------------------------------
    float* pfVar6 = (float*)SP_normalized_safe(0, 0);      // direction to goal
    fStack_80 = pfVar6[0]; fStack_7c = pfVar6[1]; fStack_78 = pfVar6[2];
    {
      float* n = (float*)SP_normalized_safe(0, (void*)(piVar5+5));
      fStack_80 = n[0]; fStack_7c = n[1]; fStack_78 = n[2];
    }
    fStack_2c = 0.0f;
    // blend toward the goal direction and clamp to turn limits
  } else {
    switch (piVar5[0x17]) {
      case 1:
      case 4: {
        float t = fStack_94 / fStack_3c;
        float s = SQRT(pcStack_bc * fStack_94);
        float v = (t <= s) ? t : s;
        if (v > pcStack_a8) v = pcStack_a8;
        pcStack_70x = v;
        fStack_68 = fStack_78 * v;
        fStack_6c = fStack_7c * v;
        break;
      }
      case 2:
        // keep current distance
        break;
      case 3: {
        float* n = (float*)SP_normalized_safe(0, (void*)(piVar5+5));
        fStack_80 = n[0]; fStack_7c = n[1]; fStack_78 = n[2];
        break;
      }
    }
  }

  if (piVar5[0x17] == 4) goto LAB_00caf38f;
  if ((float)stack_c8 <= fStack_94) {
LAB_00caf0b3:
    if (1.5258789e-05f < (pcStack_70x*pcStack_70x + fStack_68*fStack_68) + fStack_6c*fStack_6c) {
      float* n = (float*)SP_normalized_safe(0, &pcStack_70x);
      local_38x = n[0]; fStack_34 = n[1]; fStack_30 = n[2];
    }
  } else {
    float f = (float)FUN_004885d0(piVar5 + 0x14);
    if (f <= 1.5258789e-05f) goto LAB_00caf0b3;
    local_38x = (float)piVar5[0x14];
    fStack_34 = (float)piVar5[0x15];
    fStack_30 = (float)piVar5[0x16];
  }
  {
    float dot = fStack_34 * fStack_9c + (fStack_30 * fStack_98 + local_38x * pcStack_a0);
    if (dot <= -1.0f) dot = -1.0f;
    if (dot >= 1.0f)  dot = 1.0f;
    {
      ang = (float)_CIacos();
      (void)ang;
    }
  }
  {
    float* pfVar8 = (float*)SP_normalized_safe(0, 0);
    pcStack_a0 = pfVar8[0]; fStack_9c = pfVar8[1]; fStack_98 = pfVar8[2];
  }
  SP_normalized_safe(0, pfVar4);
  SP_QuaternionFromFacingAndUp(0, 0, 0);
  if (piStack_18[0x2c7] == 0) {
    pfVar8_ = (float*)FUN_00b7f320(0, pfVar4, 0, 0x40a00000);
  } else {
    pfVar8_ = (float*)FUN_00b7f1f0(0, pfVar4, 0);
  }
  pcStack_b8 = pfVar8_[0]; pcStack_b4 = pfVar8_[1]; pcStack_b0 = pfVar8_[2];
  fStack_ac = pfVar8_[3];
  VC1(void, (void*)I(local_14, 0x34), 0x3c, (int)&pcStack_b8);

LAB_00caf38f:
  // ---- final blend of the desired heading with the current one ------------------------
  {
    float dot = fStack_34 * fStack_9c + (fStack_30 * fStack_98 + local_38x * pcStack_a0);
    if (dot <= -1.0f) dot = -1.0f;
    if (dot >= 1.0f)  dot = 1.0f;
    {
      ang = (float)_CIacos();
      if (cStack_c9 != 0 && piVar5[0x17] != 4 && _DAT_0157d32c < ang) {
        float d = SQRT(fStack_6c*fStack_6c + (fStack_68*fStack_68 + pcStack_70x*pcStack_70x));
        fStack_68 = d;
        fStack_6c = fStack_9c * d;
      }
    }
    fVar14 = 1.0f / fStack_3c;
    fVar12 = (fStack_68 - (float)param_1[2]) * fVar14;
    fVar10 = (fStack_6c - (float)param_1[1]) * fVar14;
    fVar14 = ((float)pcStack_70x - (float)param_1[0]) * fVar14;
    if (0.0f < (fVar12*fStack_98 + fVar10*fStack_9c) + pcStack_a0*fVar14) {
      float len = SQRT(fVar14*fVar14 + (fVar10*fVar10 + fVar12*fVar12));
      if (pcStack_bc < len) {
        len = pcStack_bc / len;
        fVar14 *= len; fVar10 *= len; fVar12 *= len;
      }
    }
    fVar1 = fVar12 * fStack_3c + (float)param_1[2];
    fVar16 = fVar10 * fStack_3c + (float)param_1[1];
    fVar17 = fVar14 * fStack_3c + (float)param_1[0];
    RF(param_1,2) = fVar1; RF(param_1,1) = fVar16; RF(param_1,0) = fVar17;
    {
      float len = SQRT(fVar17*fVar17 + (fVar16*fVar16 + fVar1*fVar1));
      if (pcStack_a8 < len) {
        len = pcStack_a8 / len;
        RF(param_1,0) = fVar17*len; RF(param_1,1) = fVar16*len; RF(param_1,2) = fVar1*len;
      }
    }
    if (cStack_c9 != 0 && piVar5[0x17] != 4 && _DAT_0157d32c < ang) {
      float len = SQRT(RF(param_1,0)*RF(param_1,0) + RF(param_1,1)*RF(param_1,1) + RF(param_1,2)*RF(param_1,2));
      RF(param_1,0) = pcStack_a0*len; RF(param_1,1) = fStack_9c*len; RF(param_1,2) = fStack_98*len;
    }
  }
}
