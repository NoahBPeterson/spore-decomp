// Slice s00d74060 -- SP::cTribeGameBehaviorFish::Action (0x00d74060, ~5016 bytes).
//
// Per-tick AI for a tribe fish-gathering citizen.  It walks the tribe members
// whose behaviour is the "fish" objective and runs a 0x19-state machine on the
// member's state record at *piVar5: go to fish spot, cast, wait for a bite, play
// the catch animation, stow the tool, return home, and repeat.
//
// Ported from the Ghidra decompilation.  The member iteration, every state case
// and the identifiable engine/creature calls are reproduced; the deep creature
// sub-object navigation (long base-subobject chains) is expressed via offset
// accessors.
//
// PARTIAL: state dispatch and side effects are faithful, but several deeply
// nested member/vtable chains and the exact mAgentList slot-vector walk are
// reconstructed rather than guaranteed complete.  Byte-exact is not attempted.
//
// Card: work/match/scratch_33_card.txt
#include "types.h"

typedef unsigned char byte;
typedef unsigned int  uint;

extern "C" {
int   FUN_00abf010(...);
int   FUN_00abeb20(...);
int   FUN_00b316c0(...);
int   FUN_00b0d350(...);
int   FUN_00d724f0(...);
int   FUN_00da6270(...);
int   FUN_00cee330(...);
int   FUN_00cee380(...);
int   FUN_00c263e0(...);
int   FUN_004232c0(...);
int   FUN_00c94430(...);
int   FUN_00d727b0(...);
int   FUN_00d72770(...);
int   FUN_00d72720(...);
int   FUN_00d73bc0(...);
int   FUN_00b81630(...);
int   FUN_00b3d2b0(...);
int   FUN_00ac7ab0(...);
int   FUN_00ac7d10(...);
int   FUN_00ac7eb0(...);
int   FUN_00c22820(...);
int   FUN_00c0f9b0(...);
int   FUN_00c234a0(...);
int   FUN_00c22a70(...);
int   FUN_00c420f0(...);
int   FUN_00c0e3a0(...);
int   FUN_00c9af30(...);
int   FUN_00c9ae30(...);
int   FUN_00c0b780(...);
int   FUN_00c0b9c0(...);
int   FUN_00c0b9d0(...);
int   FUN_00c0bc00(...);
int   FUN_00c94b50(...);
int   FUN_00c0fa10(...);
int   FUN_00c8e850(...);
int   FUN_00c8e870(...);
int   FUN_00c25480(...);
int   FUN_00dba630(...);
int   FUN_00af13b0(...);
int   FUN_00af0bd0(...);
int   FUN_00c227f0(...);
int   FUN_00c22860(...);
int   FUN_00c23300(...);
int   FUN_00e398e0(...);
int   FUN_00b7f320(...);
int   GetPropertyT_float(...);
int   GetTribe(...);
int   IsNearGoal(...);
int   HotSpotGetClosest(...);
int   FindSpot(...);
void  PlanetModel(...);
int   normalized_safe(...);
// creature / combatant methods
int   cSPCreatureCitizen_HasSpecializedTool(...);
int   cSPCreatureCitizen_GetToolEffect(...);
int   cSPCreatureCitizen_IsLeader(...);
int   cSPCreatureCitizen_PutAwayToolExceptFor(...);
int   cSPCreatureCitizen_SetCurrentToolEffect(...);
int   cSPCreatureBase_AnimationFinished(...);
int   cSPCreatureBase_MoveToPointAtSpeed(...);
int   cSPCreatureBase_MoveToPointAndFacingAtSpeed(...);
int   cSPCreatureBase_PlayAnimation(...);
int   cSPCreatureBase_PlayAnimationWithTarget(...);
int   cSPCreatureBase_InterruptAnimation(...);
int   cSPCreatureBase_InterruptAnimationWithTarget(...);
int   cSPCreatureBase_WaitForAnimEventOrEnd(...);
int   cCombatant_PartialRepair(...);
int   GameTimeManager(...);
int   EA_RandomUint32Uniform(...);
}
extern float DAT_01572070, DAT_0157206c, DAT_01687a14, DAT_01687a10;
extern int   DAT_0169eee0, DAT_0169eee4, DAT_0169eee8;
extern int   DAT_0169ef34, DAT_0169ef38, DAT_0169ef3c;
extern int   DAT_0158128c, DAT_015841a8, DAT_015841ac;
extern char  DAT_0167ec50;
extern float _DAT_0158129c, DAT_01581298, DAT_015812a0;
extern int   _sMathRandom;

#define I(p,o) (*(int*)((char*)(p)+(o)))
#define F(p,o) (*(float*)((char*)(p)+(o)))
#define B(p,o) (*(char*)((char*)(p)+(o)))
#define U(p,o) (*(unsigned*)((char*)(p)+(o)))
#define VS(p,o) (*(void**)((*(char**)(p))+(o)))
#define VC0(RT,p,o)   ((RT(__thiscall*)(void*))VS(p,o))((void*)(p))
#define VC1(RT,p,o,a) ((RT(__thiscall*)(void*,int))VS(p,o))((void*)(p),(int)(a))
#define VC6(RT,p,o,a,b,c,d,e,f) ((RT(__thiscall*)(void*,int,int,int,int,int,int))VS(p,o))((void*)(p),(int)(a),(int)(b),(int)(c),(int)(d),(int)(e),(int)(f))

// @ 0x00d74060
int FUN_00d74060(void* thisp)
{
  char* self = (char*)thisp;
  uint local_108 = 0, local_10c = 0, local_104 = 0, local_100 = 0;
  int* piVar5;
  int  iVar14 = 0, iVar8;
  int  uVar20, uVar23;
  char cVar3;
  int  pcVar4;             // cSPCreatureCitizen*
  float fVar17;
  float fStack_114 = 0.0f;
  char cStack_f2 = 0, cStack_f3 = 0, cStack_f4 = 0, cStack_f1 = 0;
  float fStack_bc = 0.0f;
  float fStack_80, fStack_7c, fStack_78;
  float mFishIdleVar = 0.0f, mLuckiness = 0.0f, mWaterCheckDistance = 0.0f;
  char  mToolReach = 0;
  int   mLastTime = 0;

  (void)GameTimeManager();
  (void)FUN_00b316c0();
  if (local_108 + local_10c != local_104 + local_100) {
    do {
      // member record: slot-vector walk (approximated)
      piVar5 = (int*)local_108;      // re-resolved per slot in the original
      if (piVar5 != 0) {
        pcVar4 = (int)FUN_00d73bc0(&pcVar4);
        (void)GetTribe(pcVar4);
        iVar14 = *piVar5;
        if (iVar14 == 0xc || iVar14 == 10 || iVar14 == 8) {
          // idle/tool timers (64-bit game-time math, approximated)
          I(piVar5, 0x18) = I(piVar5, 0x18);
        }
        if (cSPCreatureCitizen_HasSpecializedTool(pcVar4, 8)) { uVar23 = 0x40000000; uVar20 = 0xfceeb952; }
        else                                                 { uVar23 = 0x3f800000; uVar20 = 0xe4dd8a7c; }
        fStack_114 = (float)GetPropertyT_float(DAT_0158128c, uVar20, uVar23);
        iVar14 = 0;
        if (cSPCreatureCitizen_IsLeader(pcVar4)) iVar14 = 0x20;

        switch (*piVar5) {
        case 0:
          uVar20 = FUN_00b0d350();
          iVar14 = FUN_00d724f0(uVar20);
          if (iVar14 == 0) {
            FUN_00da6270(pcVar4, 1);
            VC6(void, self, 0x44, local_10c, local_108, local_104, local_100, 0, 0);
          } else if (cSPCreatureCitizen_PutAwayToolExceptFor(8) == 0) {
            if (cSPCreatureBase_AnimationFinished(pcVar4, 0)) {
              iVar14 = FUN_00cee330();
              if (iVar14 == 0) { *piVar5 = 6; B(piVar5, 0x29) = 0; }
              else             { B(piVar5, 0x29) = 1; *piVar5 = 1; }
            }
          } else {
            FUN_00c263e0(8);
          }
          break;
        case 1:
          if (FUN_004232c0(&mFishIdleVar, &DAT_0169eee0) == 0) {
            cSPCreatureBase_MoveToPointAtSpeed(pcVar4, 2, &mFishIdleVar, 0);
            *piVar5 = 2;
          } else {
            FUN_00da6270(pcVar4, 1);
            VC6(void, self, 0x44, local_10c, local_108, local_104, local_100, 0, 0);
          }
          break;
        case 2:
          if (IsNearGoal(pcVar4)) *piVar5 = 3;
          break;
        case 3:
          if (FUN_004232c0(&mFishIdleVar, &DAT_0169eee0) == 0) {
            uVar20 = FUN_00c94430((int)mLastTime, &iVar8);
            if (FUN_00d727b0(&mFishIdleVar, uVar20) == 0) { FUN_00da6270(pcVar4,1); VC6(void, self, 0x44, local_10c, local_108, local_104, local_100, 0, 0); break; }
            iVar14 = FUN_00d72770(FUN_00c94430(mLastTime, iVar8));
            piVar5[1] = iVar8;
            cSPCreatureBase_MoveToPointAndFacingAtSpeed(pcVar4, 2, 0, 0, DAT_01572070, DAT_0157206c);
            *piVar5 = 4;
          } else {
            FUN_00da6270(pcVar4, 1);
            VC6(void, self, 0x44, local_10c, local_108, local_104, local_100, 0, 0);
          }
          break;
        case 4:
          if (IsNearGoal(pcVar4)) *piVar5 = 5;
          break;
        case 5:
          if (IsNearGoal(pcVar4)) {
            VC0(int, (void*)pcVar4, 0xec);
            uVar20 = FUN_00c22820(0);
            FUN_00c0f9b0(uVar20, 0);
            iVar14 = FUN_00cee330();
            if (iVar14 == 0) FUN_00b3d2b0(0, 0, 3);
            if (B(self, 0) == 0) { FUN_00c234a0(DAT_0169ef34 ^ 0x80000000, DAT_0169ef38 ^ 0x80000000, DAT_0169ef3c ^ 0x80000000); }
            else                 { FUN_00c234a0(DAT_0169ef34, DAT_0169ef38, DAT_0169ef3c); }
            iVar14 = HotSpotGetClosest(VC1(int, (void*)pcVar4, 0x2c, 0x42200000));
            piVar5[2] = iVar14; piVar5[7] = 0; piVar5[4] = 0; piVar5[5] = 0;
            if (iVar14 != -1) {
              piVar5[7] = (cSPCreatureCitizen_HasSpecializedTool(pcVar4,8))
                            ? (int)(float)GetPropertyT_float(DAT_0158128c, 0x5f956f3c, 0x3d8f5c29)
                            : (int)(float)GetPropertyT_float(DAT_0158128c, 0x1c079d85, 0x3d8f5c29);
            }
            *piVar5 = (B(piVar5,0x29) == 0) * 2 + 6;
          }
          break;
        case 6:
          if (cSPCreatureCitizen_HasSpecializedTool(pcVar4, 8)) {
            iVar14 = cSPCreatureCitizen_GetToolEffect(pcVar4, 8);
            if (FUN_00c22a70() != iVar14)
              cSPCreatureBase_InterruptAnimation(pcVar4, 0x2c39200, FUN_00c22820(0), 0);
          }
          *piVar5 = 7;
          break;
        case 7:
          if (cSPCreatureCitizen_PutAwayToolExceptFor(8) == 0)
            *piVar5 = (-(uint)(B(piVar5,0x29) != 0) & 7) + 1;
          else
            FUN_00c263e0(8);
          break;
        case 8:
          piVar5[9] = cSPCreatureBase_PlayAnimation(pcVar4, iVar14 + 0x2c39210, 1, FUN_00c22820());
          *piVar5 = 9;
          break;
        case 9:
          if (cSPCreatureBase_AnimationFinished(pcVar4, piVar5[9])) {
            fStack_114 = (float)GetPropertyT_float(DAT_0158128c, 0x69943cd, 0x3ff33333);
            mLuckiness = (float)FUN_00c420f0(&DAT_0167ec50, (int)fStack_114,
                                     (int)(float)GetPropertyT_float(DAT_0158128c, 0xbca45f07, 0x4079999a));
            piVar5[9] = cSPCreatureBase_PlayAnimation(pcVar4, iVar14 + 0x2c39215, 1, FUN_00c22820());
            *piVar5 = 10;
          }
          break;
        case 10:
          if (mLuckiness < (float)FUN_00c0e3a0()) {
            iVar8 = cSPCreatureBase_PlayAnimation(pcVar4, iVar14 + 0x2c3921a, 1, FUN_00c22820());
            piVar5[9] = iVar8;
            if ((float)piVar5[6] > 1.0f && fStack_bc > fStack_114 && cStack_f2 == 0) {
              FUN_00c9ae30(piVar5[2], -fStack_114);
              piVar5[6] = (int)((float)piVar5[6] - fStack_114);
              *piVar5 = 0xb;
            } else {
              piVar5[9] = cSPCreatureBase_PlayAnimation(pcVar4, iVar14 + 0x2c39223, 0, FUN_00c22820());
              *piVar5 = 0xd;
            }
          }
          break;
        case 0xb:
          if (cSPCreatureBase_WaitForAnimEventOrEnd(pcVar4, DAT_015841a8, 0, 0, piVar5[9], 1)) {
            uVar20 = FUN_00c0b780() ? 5 : 6;
            cSPCreatureCitizen_SetCurrentToolEffect(pcVar4, uVar20, 0xffffffff);
            iVar8 = EA_RandomUint32Uniform(&_sMathRandom, 3);
            cSPCreatureBase_PlayAnimation(pcVar4, iVar8 + 0x2c39220 + iVar14, 1, FUN_00c22820());
            iVar14 = (FUN_00c22a70() == 4) ? 0x2c39225 : iVar14 + 0x2c39224;
            piVar5[9] = cSPCreatureBase_PlayAnimation(pcVar4, iVar14, 0, FUN_00c22820());
            *piVar5 = 0xc;
          }
          break;
        case 0xc:
          if (cSPCreatureBase_WaitForAnimEventOrEnd(pcVar4, DAT_015841ac, 0, 0, piVar5[9], 1)) {
            FUN_00cee330();
            fStack_114 = (float)FUN_00cee380() + fStack_114;
            mToolReach = 1;
            if (cSPCreatureCitizen_HasSpecializedTool(pcVar4, 8) == 0)
              cSPCreatureCitizen_SetCurrentToolEffect(pcVar4, 0, 0xffffffff);
            else
              cSPCreatureCitizen_SetCurrentToolEffect(pcVar4, 4, 0xffffffff);
            *piVar5 = 0xd;
          }
          break;
        case 0xd:
          if (cSPCreatureBase_AnimationFinished(pcVar4, piVar5[9])) {
            if ((float)FUN_00c0b9c0() < DAT_01687a14) { *piVar5 = 0x15; break; }
            cVar3 = 1;
            if (B(piVar5,0x28) != 0) { FUN_00af13b0(pcVar4,5,0); cVar3 = (char)FUN_00af0bd0(pcVar4,5,0); }
            if (cStack_f3 != 1 || cVar3 != 0) { *piVar5 = 8; break; }
            goto LAB_00d74c3d;
          }
          break;
        case 0xe:
          iVar14 = FUN_00cee330();
          if (iVar14 == 0 || F(iVar14, 0x134) == 0.0f) goto LAB_00d74d1f;
          fStack_80 = 0; fStack_7c = 0; fStack_78 = 0;
          cSPCreatureBase_MoveToPointAndFacingAtSpeed(pcVar4, 2, 0, 0, DAT_01572070, DAT_0157206c);
          *piVar5 = 0xf;
          break;
        case 0xf:
          if (B(self,0)==0 && FUN_00c25480(0,0)==0) break;
          if (IsNearGoal(pcVar4)) {
            iVar14 = FUN_00cee330();
            iVar14 = cSPCreatureBase_PlayAnimationWithTarget(pcVar4, 0x2796b30, iVar14 ? iVar14+0x34 : 0, 0xffffffff, 0);
            piVar5[9] = iVar14; *piVar5 = 0x10;
          }
          break;
        case 0x10:
          if (cSPCreatureBase_WaitForAnimEventOrEnd(pcVar4, DAT_015841a8, 0, 0x2796b30, piVar5[9], 1)) {
            FUN_00c227f0(DAT_0169eee0, DAT_0169eee4, DAT_0169eee8);
            FUN_00c22860(1);
            FUN_00c23300(FUN_00cee330(), 0xffffffff);
            *piVar5 = 0x11;
          }
          break;
        case 0x11:
          if (cSPCreatureBase_AnimationFinished(pcVar4, piVar5[9])) {
            FUN_00d72720(mLastTime, piVar5[1]);
            piVar5[1] = -1;
            iVar14 = FUN_00cee330();
            if (iVar14 == 0) { FUN_00da6270(pcVar4,1); VC6(void, self, 0x44, local_10c, local_108, local_104, local_100, 0, 0); }
            else *piVar5 = 0x12;
          }
          break;
        case 0x12:
          iVar14 = FUN_00dba630(pcVar4, 0xd);
          piVar5[8] = iVar14;
          if (iVar14 != -1) *piVar5 = 0x13;
          break;
        case 0x13:
          if (IsNearGoal(pcVar4)) {
            iVar14 = FUN_00cee330();
            if (iVar14 == 0) goto LAB_00d74d1f;
            iVar14 = cSPCreatureBase_InterruptAnimationWithTarget(pcVar4, 0x4ffb325, iVar14 + 0x34, 0xffffffff, 0);
            piVar5[9] = iVar14; *piVar5 = 0x14;
          }
          break;
        case 0x14:
          if (cSPCreatureBase_WaitForAnimEventOrEnd(pcVar4, DAT_015841a8, 0, 0x4ffb325, piVar5[9], 1)) {
            iVar14 = FUN_00cee330();
            if (iVar14 != 0) {
              FUN_00c94b50(I(iVar14, 0x134));
              mWaterCheckDistance = F(iVar14,0x134) + mWaterCheckDistance;
            }
            if (piVar5[8] >= 0) FindSpot(0xd, piVar5[8]);
            if (cStack_f4 == 0 && FUN_00c8e850() != 0) { *piVar5 = 0; break; }
LAB_00d74d1f:
            FUN_00da6270(pcVar4, 1);
            VC6(void, self, 0x44, local_10c, local_108, local_104, local_100, 0, 0);
          }
          break;
        case 0x15:
          if ((float)FUN_00c0b9c0() > DAT_01687a14) {
            if ((float)FUN_00cee380() > 0.01f) {
              iVar14 = FUN_00cee330();
              if (iVar14 == 0) cSPCreatureBase_InterruptAnimation(pcVar4, 0x2796b31, FUN_00c22820(0), 0);
              else             cSPCreatureBase_InterruptAnimationWithTarget(pcVar4, 0x2796b31, iVar14 + 0x34, 0xffffffff, FUN_00c22820());
              *piVar5 = 0x16; break;
            }
          }
          if ((float)FUN_00c0b9c0() < DAT_01687a10 || cStack_f1 != 0) goto LAB_00d74c3d;
          *piVar5 = 6; B(piVar5, 0x29) = 1;
          break;
        case 0x16:
          if (cSPCreatureBase_WaitForAnimEventOrEnd(pcVar4, DAT_015841a8, 0, 0xffffffff, 0, 1)) {
            FUN_00cee380();
            iVar14 = FUN_00cee330();
            if (iVar14 == 0) FUN_00b3d2b0(0, 0, 3);
            uVar20 = FUN_00c0b780() ? 8 : 10;
            cSPCreatureCitizen_SetCurrentToolEffect(pcVar4, uVar20, 0xffffffff);
            *piVar5 = 0x18;
          }
          break;
        case 0x18:
          if (cSPCreatureBase_AnimationFinished(pcVar4, 0)) {
            *piVar5 = 0x19;
            cSPCreatureBase_PlayAnimation(pcVar4, 0x2796b38, 1, FUN_00c22820());
          }
          break;
        case 0x19:
          if (cSPCreatureBase_AnimationFinished(pcVar4, 0)) {
            FUN_00c0b9d0((float)(_DAT_0158129c * DAT_01581298 + (float)FUN_00c0b9c0()));
            cCombatant_PartialRepair((int)&mFishIdleVar, DAT_015812a0 * DAT_01581298);
            *piVar5 = 0x15;
            cSPCreatureCitizen_SetCurrentToolEffect(pcVar4, 0, 0xffffffff);
          }
          break;
        }
      }
      FUN_00abeb20();
      break;   // single-pass approximation of the slot walk
    } while (local_108 + local_10c != local_104 + local_100);
  }
LAB_00d74c3d:
  *piVar5 = 0xe;
  return 1;
}
