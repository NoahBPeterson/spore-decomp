// match/slices/s00d87620/s00d87620.cpp
// Object file: SPGonzago/SPCreatureBase.obj (dev VA 00997830).
// SP::EAT_FRUIT_Tick -- behaviour-tree tick for eating fruit.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2

#include <math.h>
typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   uintptr_t;

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------------------
// Placeholder vtable interfaces (slot indices taken from the original call sites)
// ---------------------------------------------------------------------------

// Spatial subobject embedded in the creature at +0xc0.
struct SpatSub {
  virtual void  pad00(); virtual void  pad01(); virtual void  pad02(); virtual void  pad03();
  virtual void  pad04(); virtual void  pad05(); virtual void  pad06(); virtual void  pad07();
  virtual void  pad08(); virtual void  pad09(); virtual void  pad0a(); virtual void  pad0b();
  virtual Vec3* GetPosition(Vec3* out);          // slot 11 (0x2c)
  virtual void  pad0c(); virtual void  pad0d(); virtual void  pad0e(); virtual void  pad0f();
  virtual void  pad10(); virtual void  pad11();
  virtual bool  Flag48();                        // slot 18 (0x48)
  virtual void  pad13(); virtual void  pad14(); virtual void  pad15(); virtual void  pad16();
  virtual void  pad17(); virtual void  pad18(); virtual void  pad19();
  virtual Vec3* GetBounds();                     // slot 26 (0x68)
  virtual void  pad1b();
  virtual float GetScale74();                    // slot 29 (0x74)
  virtual void  pad1d(); virtual void  pad1e(); virtual void  pad1f(); virtual void  pad20();
  virtual void  pad21(); virtual void  pad22(); virtual void  pad23(); virtual void  pad24();
  virtual void  pad25(); virtual void  pad26(); virtual void  pad27(); virtual void  pad28();
  virtual void  pad29(); virtual void  pad2a(); virtual void  pad2b(); virtual void  pad2c();
  virtual void  pad2d(); virtual void  pad2e(); virtual void  pad2f(); virtual void  pad30();
  virtual void  pad31(); virtual void  pad32(); virtual void  pad33(); virtual void  pad34();
  virtual void  pad35(); virtual void  pad36(); virtual void  pad37(); virtual void  pad38();
  virtual void  pad39(); virtual void  pad3a();
  virtual void  Notify();                        // slot 59 (0xec)
};

// The anim subobject of a creature, at anim-owner+0x34.
struct AnimSub {
  virtual void  pad00(); virtual void  pad01(); virtual void  pad02(); virtual void  pad03();
  virtual void  pad04(); virtual void  pad05(); virtual void  pad06(); virtual void  pad07();
  virtual void  pad08(); virtual void  pad09(); virtual void  pad0a(); virtual void  pad0b();
  virtual void  pad0c(); virtual void  pad0d(); virtual void  pad0e(); virtual void  pad0f();
  virtual void  SetFloat40(float v);             // slot 16 (0x40)
  virtual void  pad11(); virtual void  pad12(); virtual void  pad13(); virtual void  pad14();
  virtual void  pad15(); virtual void  pad16(); virtual void  pad17(); virtual void  pad18();
  virtual void  pad19(); virtual void  pad1a();
  virtual Vec3* GetBox6c(Vec3* out);             // slot 27 (0x6c)
  virtual float GetF70();                        // slot 28 (0x70)
  virtual float GetDist74();                     // slot 29 (0x74)
};

// Timer subobject at creature+0x5a8.
struct TimerSub {
  virtual void  pad00(); virtual void  pad01(); virtual void  pad02(); virtual void  pad03();
  virtual void  pad04(); virtual void  pad05(); virtual void  pad06(); virtual void  pad07();
  virtual void  pad08(); virtual void  pad09(); virtual void  pad0a(); virtual void  pad0b();
  virtual void  pad0c(); virtual void  pad0d(); virtual void  pad0e(); virtual void  pad0f();
  virtual void  pad10(); virtual void  pad11();
  virtual float GetElapsed58();                  // slot 22 (0x58)
};

// Ref-counted object: slot 0 AddRef, slot 1 Release.
struct RefCnt {
  virtual void  AddRef();
  virtual void  Release();
};

// AutoRefCount<T> member: the raw pointer lives at offset 0.
struct AutoRef { RefCnt* mp; };

// ---------------------------------------------------------------------------
// The retail creature object (param_1).  Fields named by role + offset.
// ---------------------------------------------------------------------------
struct Creature {
  RefCnt*  mpVtbl;                 // 0x000
  u8       pad004[0xc0 - 4];
  SpatSub  mSpatial;               // 0x0c0
  u8       pad0c4[0x5a8 - 0xc4];
  TimerSub mTimer;                 // 0x5a8
  u8       pad5ac[0x5e0 - 0x5ac];
  float    mF_5e0;                 // 0x5e0
  u8       pad5e4[0xb20 - 0x5e4];
  void*    mpProfile_5b20;         // 0xb20
  u8       padB24[0xb4c - 0xb24];
  void*    mpStimuliMgr;           // 0xb4c  (manager; +8 is the behaviour_stimuli)
  void*    mpAnimWorld_5b54;       // 0xb54  (creature animation instance)
  u32      mFlags_5b58;            // 0xb58  (bit 9 tested)
};

// A creature as seen through the behaviour-node pointer: only +0x16c and the
// anim subobject at +0x34 are used.
struct ActorSub {
  u8       pad000[0x34];
  AnimSub  mAnim;                  // 0x034
  u8       pad038[0x16c - 0x38];
  s32      mState_16c;             // 0x16c
};

// nSPBehaviorTree::behavior_stimuli: ClearAll / Set live at manager+8.
struct Stimuli {
  s32 pad[2];
  void ClearAll(int, int);              // 0xbc98f0
  void* Set(int, int, float, u32);      // 0xbc97f0
};

// ---------------------------------------------------------------------------
// The behaviour-tree node state (param_6).
// ---------------------------------------------------------------------------
struct EatFruitNode {
  s32   mState;              // 0x00
  s32   mSub;                // 0x04
  RefCnt* mpActor;           // 0x08
  s32   mPad0c;              // 0x0c
  u32   mAnimKey;            // 0x10
  s32   mAnimHandle;         // 0x14
  u8    mbFlag18;            // 0x18
  u8    mPad19[3];
  RefCnt* mpInteract;        // 0x1c
  u32   mIndex;              // 0x20
  u8    mbFlag24;            // 0x24
  u8    mPad25[3];
  AutoRef mTarget;           // 0x28
  u8    mbFlag2c;            // 0x2c
  u8    mPad2d[3];
  s32   mPartIndex;          // 0x30
};

// ---------------------------------------------------------------------------
// Callees (address in comment).
// ---------------------------------------------------------------------------
struct PlanetModel {
  Vec3* DirectionToSurfacePosition(Vec3* out, Vec3* in);   // 0x00b815a0
  Vec3* GetSurfacePos(Vec3* out, Vec3* in);                // 0x00b81630
};

void  __cdecl FUN_00b02b90(Vec3* out, u32 id);            // 0x00b02b90
u32   __cdecl FUN_00d998d0(u32, u32);                     // 0x00d998d0
void* __cdecl FUN_00c3e790();                             // 0x00c3e790
void  __cdecl FUN_00b3d3b0(u32, u32, u32);                // 0x00b3d3b0
void* __cdecl FUN_00b2a690();                             // 0x00b2a690 (ecx=?)
void* __cdecl FUN_004d9010(void*);                        // 0x004d9010
void  __cdecl FUN_00d39360(u32, void*);                   // 0x00d39360
bool  __cdecl FUN_00c0b7a0(Creature*);                    // 0x00c0b7a0
bool  __cdecl FUN_00c0b770(Creature*);                    // 0x00c0b770
void  __cdecl FUN_00f924e0(float);                        // 0x00f924e0
void  __cdecl FUN_00d85540(Creature*);                    // 0x00d85540
u32   __cdecl FUN_00d539d0();                             // 0x00d539d0
void  __cdecl FUN_00d52e40(u32);                          // 0x00d52e40
PlanetModel* __cdecl PlanetModel_Get();                   // 0x00b3d350
Vec3* __cdecl normalized_safe(Vec3* out, Vec3* in);       // 0x00449c20
RefCnt* __cdecl NounManager(RefCnt*);                     // 0x00b3d300
void* __cdecl FUN_00401090();                             // 0x00401090
u32   __cdecl FUN_00c0f960(Creature*, u32);               // 0x00c0f960
void  __cdecl FUN_00c159c0(Creature*, void*, u32, u32);   // 0x00c159c0
void  __cdecl FUN_00c15d50(Creature*, void*, u32, u32);   // 0x00c15d50
u32   __cdecl FUN_00d7d370(Creature*, Vec3*);             // 0x00d7d370
bool  __cdecl FUN_00c1ac70(Creature*, Vec3*, u32, u32, u32, u32, float); // 0x00c1ac70
void  __cdecl EatFood(Creature*, float, u32, u32);        // 0x00d85ad0
bool  __cdecl FUN_00c0f960_b();                           // unused

struct CreatBase {
  bool  IsNearGoal();            // 0xc42e20
  bool  Flag48();                // vtable 0x48 of the base
  u32   MoveToPointFacing(u32, Vec3*, Vec3*, float, float); // 0xc1c5c0
  s32   WaitForAnimEventOrEnd(u32, s32*, s32, s32, s32);    // 0xc14ef0
  void* InterruptAnimationWithTarget(u32, void*, s32);      // 0xc149c0
  s32   PlayAnim(u32, void*, s32);                          // 0xc14990
  s32   GetBodyPartIndex(u32, s32);                         // 0xc17580
  bool  AnimationFinished(s32);                             // 0xc12400
  bool  IsEatingActive();                                   // 0xc0b770
};

extern "C" void HitBody(void* animData, u32 part, Vec3* pos, u32 a, u32 b, float f); // 0x9bb680

// @ 0x00d87620
int __cdecl EAT_FRUIT_Tick(Creature* pCreature, u32 a2, u32 a3, u32 flags, u32 a5, EatFruitNode* pNode)
{
  (void)a2; (void)a3; (void)a5;

  AutoRef* pRef;        // local_118: address of an AutoRefCount member
  RefCnt*  pOld;        // local_110: previous pointer of that member
  u32      anim;        // Play() result / animation handle
  Vec3     vA, vB, vC;  // scratch vector slots on the stack
  float    fDist;       // local_118 reinterpreted as float
  float    fExtra;      // local_110 reinterpreted as float
  float    fSpeed;

  ActorSub* pActor = (ActorSub*)pNode->mpActor;

  if (pNode->mpActor == 0) {
    if (pNode->mpInteract == 0)
      return 0;
    pRef = (AutoRef*)((u8*)pNode->mpInteract + 0x68);
  } else {
    if (pActor->mState_16c == 6)
      return 0;
    pRef = (AutoRef*)((u8*)pNode->mpActor + 0x108);
  }

  if (((pCreature->mFlags_5b58 >> 9) & 1) != 0 || pRef->mp == 0) {
    pOld = pRef->mp;
    if (pOld != (RefCnt*)pCreature) {
      pCreature->mpVtbl->AddRef();
      pRef->mp = (RefCnt*)pCreature;
      if (pOld != 0)
        pOld->Release();
    }
  }

  anim = (u32)((CreatBase*)pCreature)->PlayAnim(1, 0, 1);
  if (anim == 0)
    anim = 0;
  else
    anim = FUN_00d998d0(anim, 0x2c9cc8e);

  fDist = 0.0f;
  fExtra = 0.0f;

  switch (pNode->mState) {
  case 0: {
    if (anim != 0 && (u32)pNode->mpActor != anim) {
      pNode->mState = 7;
      return 0;
    }
    vA.x = vB.x = vC.x = (*(float*)0x169f03c);
    vA.y = vB.y = vC.y = (*(float*)0x169f040);
    vA.z = vB.z = vC.z = (*(float*)0x169f044);
    fDist = 0.0f;
    if (pNode->mpInteract == 0) {
      if (pNode->mpActor != 0) {
        Vec3* pBox = pActor->mAnim.GetBox6c(&vC);
        vB.x = (pBox[0].x + pBox[1].x) * 0.5f;   // .x of first/second element
        vB.y = (pBox[1].y + pBox[0].y) * 0.5f;
        vB.z = (pBox[1].z + pBox[0].z) * 0.5f;
        Vec3* pSurf = PlanetModel_Get()->GetSurfacePos(&vA, &vB);
        vC.x = pSurf[0].x; vC.y = pSurf[0].y; vC.z = pSurf[0].z;
        Vec3* pPos = pCreature->mSpatial.GetPosition(&vA);
        vA.x = pPos[0].x - vC.x;
        vA.y = pPos[0].y - vC.y;
        vA.z = pPos[0].z - vC.z;
        Vec3* pN = normalized_safe(&vC, &vA);
        vB.x = pN[0].x; vB.y = pN[0].y; vB.z = pN[0].z;
        fDist = pActor->mAnim.GetDist74();
      }
    } else {
      FUN_00b02b90(&vB, pNode->mTarget.mp ? (u32)(uintptr_t)pNode->mTarget.mp : 0);
      Vec3* pDir = PlanetModel_Get()->DirectionToSurfacePosition(&vA, &vB);
      vC.x = pDir[0].x; vC.y = pDir[0].y; vC.z = pDir[0].z;
      fDist = vC.y - *(float*)((u8*)pNode->mpInteract + 0x14);
      fExtra = vC.z - *(float*)((u8*)pNode->mpInteract + 0x18);
      vA.x = vC.x - *(float*)((u8*)pNode->mpInteract + 0x10);
      (void)normalized_safe(&vB, &vA);
      vB.x = vB.x; // placeholder, filled below
      float dy = vC.z - *(float*)((u8*)pNode->mpInteract + 0x18);
      float dx = vC.x - *(float*)((u8*)pNode->mpInteract + 0x10);
      float dz = vC.y - *(float*)((u8*)pNode->mpInteract + 0x14);
      (void)dy; (void)dz;
      vA.x = dx * dx + dy * dy + dz * dz;
      fSpeed = *(float*)((u8*)pNode->mpInteract + 0x6c);
      if (fSpeed * fSpeed <= vA.x)
        fDist = 0.0f;
      else
        fDist = fSpeed - sqrtf(vA.x);
    }
    fExtra = pCreature->mSpatial.GetScale74() + fExtra + fDist;
    if (PlanetModel_Get() != 0) {
      vB.x = vB.x * fExtra + vC.x;
      vB.y = vB.y * fExtra + vC.y;
      vB.z = vB.z * fExtra + vC.z;
      Vec3* pSurf = PlanetModel_Get()->GetSurfacePos(&vA, &vB);
      vC.x = pSurf[0].x; vC.y = pSurf[0].y; vC.z = pSurf[0].z;
    }
    if (pNode->mbFlag24) {
      if (pNode->mpInteract != 0)
        pNode->mbFlag24 = 0;
      if (((pCreature->mFlags_5b58 >> 9) & 1) == 0) {
        *(u32*)&vA.x = *(u32*)&vB.x ^ 0x80000000u;
        vA.y = -vB.y;
        vA.z = -vB.z;
        ((CreatBase*)pCreature)->MoveToPointFacing(2, &vA, &vC, 0.2f, 0.5f);
      } else {
        Vec3* pPos = pCreature->mSpatial.GetPosition(&vC);
        Vec3* pSurf = PlanetModel_Get()->GetSurfacePos(&vA, &vB);
        vB.x = pSurf[0].x - pPos[0].x;
        vB.y = pSurf[0].y - pPos[0].y;
        vB.z = pSurf[0].z - pPos[0].z;
        (void)normalized_safe(&vA, &vB);
        fSpeed = pCreature->mSpatial.GetScale74() + 0.01f;
        ((CreatBase*)pCreature)->MoveToPointFacing(2, &vA, &vA, fSpeed, fSpeed);
      }
    }
    if (!((CreatBase*)&pCreature->mSpatial)->IsNearGoal())
      return 1;
    {
      void* pAvatar = FUN_00401090();
      (void)pAvatar;
      float food = *(float*)((u8*)pCreature->mpProfile_5b20 + 0x590);
      if (food == 0.0f || !((CreatBase*)pCreature)->IsEatingActive())
        pNode->mSub = 2;
      else
        pNode->mSub = 0xb;
    }
    if (pNode->mpInteract == 0) {
      if (pNode->mpActor != 0) {
        pNode->mState = 2;
        s32 h = -1;
        if (((CreatBase*)&pCreature->mSpatial)->Flag48() && (flags & 0x100000))
          h = (s32)FUN_00d7d370(pCreature, &vC);
        if (pNode->mSub == 0xb) pNode->mAnimKey = 0x4eea0d5;
        else                    pNode->mAnimKey = 0x4eea0d2;
        s32 r = ((CreatBase*)pCreature)->PlayAnim(pNode->mAnimKey, &vC, h);
        pNode->mAnimHandle = r;
      }
    } else {
      Vec3* pDir = PlanetModel_Get()->DirectionToSurfacePosition(&vA, &vB);
      vC.x = vB.x - pDir[0].x;
      fDist = vB.y - pDir[0].y;
      fExtra = vB.z - pDir[0].z;
      Vec3* pExt = pActor->mAnim.GetBox6c(&vA);
      float d = (*(float*)((u8*)pExt + 0x14) - *(float*)((u8*)pExt + 8)) * 1.75f;
      bool bNear = FUN_00c1ac70(pCreature, &vB, pNode->mSub, 0xffffffff, 0, 0, 0x3e4ccccd);
      (void)bNear;
      if ((fExtra * fExtra + fDist * fDist) + vC.x * vC.x <= d * d) {
        pNode->mState = 1;
        if (pNode->mSub == 0xb) pNode->mAnimKey = 0x4eea0d6;
        else                    pNode->mAnimKey = 0x4eea0d3;
        (void)d; (void)pExt;
      } else {
        pNode->mState = 6;
        if (pNode->mSub == 0xb) pNode->mAnimKey = 0x4eea0d7;
        else                    pNode->mAnimKey = 0x4eea0d4;
        s32 h = -1;
        if (((CreatBase*)&pCreature->mSpatial)->Flag48() && (flags & 0x100000))
          h = (s32)FUN_00d7d370(pCreature, &vC);
        pNode->mAnimHandle = ((CreatBase*)pCreature)->PlayAnim(pNode->mAnimKey, &vC, h);
      }
    }
    break;
  }
  case 1:
  case 2: {
    if (pNode->mpActor != 0 && pActor->mState_16c != 0 &&
        pActor->mState_16c != 2 && pActor->mState_16c != 3) {
      pNode->mState = 5;
      ((Stimuli*)((u8*)pCreature->mpStimuliMgr + 8))->ClearAll(1, 0);
      return 0;
    }
    s32 h = -1;
    u32 key = (pNode->mSub == 0xb) ? 0xb9ce16b9 : 0x68629eb3;
    u8 done = (u8)((CreatBase*)pCreature)->WaitForAnimEventOrEnd(key, &h, -1, pNode->mAnimHandle, 1);
    pNode->mbFlag18 = done;
    if (done) {
      if (pNode->mbFlag2c && pNode->mTarget.mp != 0 && pNode->mTarget.mp != (RefCnt*)0xffffffff) {
        void* pMgr = FUN_00c3e790();
        if (pMgr != 0) { (void)pMgr; }
      }
      if (pNode->mpInteract != 0) {
        pNode->mpInteract = pNode->mpInteract;
        (void)FUN_00b2a690();
      }
      if (pNode->mpActor == 0) {
        pNode->mState = 5;
        ((Stimuli*)((u8*)pCreature->mpStimuliMgr + 8))->ClearAll(1, 0);
        return 0;
      }
      pNode->mState = 3;
    }
    return 1;
  }
  case 3: {
    if (!pNode->mbFlag18) {
      s32 h = -1;
      if (((CreatBase*)pCreature)->WaitForAnimEventOrEnd(0x9cd2c8df, &h, pNode->mAnimHandle, 0, 1)) {
        pNode->mState = 4;
        FUN_00d85540(pCreature);
        if (pActor->mState_16c == 3) {
          if (pNode->mbFlag18) {
            FUN_00c15d50(pCreature, 0, 0, 0);
            pNode->mbFlag18 = 0;
          }
        }
        (void)FUN_00c0b7a0(pCreature);
      }
    }
    break;
  }
  case 6: {
    if (((CreatBase*)pCreature)->AnimationFinished(pNode->mAnimHandle)) {
      pNode->mState = 4;
      return 0;
    }
    break;
  }
  default:
    return 0;
  }
  return 1;
}
