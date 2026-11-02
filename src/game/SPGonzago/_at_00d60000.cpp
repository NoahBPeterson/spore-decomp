// src/game/SPGonzago/_at_00d60000.cpp -- migrated from slice(s) s00d6f1c0, s00d65250, s00d61c20, s00d60ce0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00d60000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCity.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cCityVisualizer.h"
#include <math.h>
#include "SP/cLocomotiveObject.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cBehaviorTreeData.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureBase.h"

// ---- items of slice s00d60ce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
template <class T> static inline T& F(void* p, int off) { return *(T*)((char*)p + off); }
template <class R, class A, class B, class C> static inline R VC3(void* o, int slot, A a, B b, C c) {
    typedef R(__thiscall * Fn)(void*, A, B, C);
    return ((Fn)(*(void***)o)[slot])(o, a, b, c);
}
struct Creature { void FUN_00c227c0(); };               // 0x00c227c0
typedef unsigned char u8;
struct Node {
    char pad0[0x6c];
    u32  mFlags;                // +0x6c
    int  Parent();              // 0x00ff0420
};
Node* GetActiveNode();          // 0x00d51660
struct CreatureB {
    void FUN_00c0b370(int a);       // 0x00c0b370
    void UpdateLocomotion(int m);   // 0x00c14750
};
struct StimSetB {
    void ClearAll(int type, int flags);   // 0x00bc98f0
};
struct AvatarN { int Get(); };            // 0x00c04590
struct NounMgr { AvatarN* GetAvatar(); }; // 0x00b1fdb0
NounMgr* NounManagerB();                  // 0x00b3d300
// ---- items of slice s00d60ce0 end

// ---- items of slice s00d61c20 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int            s32;
typedef float          f32;
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct Vec3 { f32 x, y, z; };
extern const f32 g_f13ec4b8;   // 0x013ec4b8  1.0e-8f  (normalise epsilon)
extern const f32 g_f13f08e4;   // 0x013f08e4  1.25f
extern const f32 g_f1470f1c;   // 0x01470f1c  2.0f
struct cBehaviorTreeData;
struct HomeInfo;
struct cPlanetModel;
class cSPCreatureBase;
struct cAvatar {
    void* FUN_00d51660();                     // 0x00d51660 lazy cDramaManager singleton
};
struct cDramaManager {
    char mPad00[0x6c];
    u32  mMode6c;                             // +0x6c  bit 4 = "idle actives allowed"
};
struct cGameNounManager {
    cAvatar* GetAvatar();                     // 0x00b1fdb0
};
cGameNounManager* __cdecl NounManager();                  // 0x00b3d300
void*             __cdecl FUN_00d51660();                 // 0x00d51660
cSPCreatureBase*  __cdecl FUN_00d99500(void* owner);      // 0x00d99500 (ret 4 -> cdecl, 1 arg)
cPlanetModel*     __cdecl PlanetModel();                  // 0x00b3d350 (0 args)
struct AnimPlayRes {
    char mPad00[0xc];
    u32  mAnimId;                             // +0x0c
};
struct Stimuli {
    AnimPlayRes* Play(u32 lo, u32 hi);        // 0x00bc96a0 (ret 8)
    void         ClearAll(u32 lo, u32 hi);    // 0x00bc98f0 (ret 8)
};
struct cBehaviorTreeData {
    char    mPad00[8];
    Stimuli mStimuli;                         // +0x08
    char    mPad09[0x1d8 - 9];
    u32     mKey1d8;                          // +0x1d8
    char    mPad1dc[0x600 - 0x1dc];
    void*   mPtr600;                          // +0x600
};
struct Loco {                                 // embedded at cSPCreatureBase+0xc0
    PV8 PV2 PV
    virtual Vec3* GetPosition();              // vtable +0x2c
    PV8 PV2 PV
    virtual Vec3* GetDirection(Vec3* out);    // vtable +0x5c
    PV4 PV
    virtual f32   GetFootprintRadius();       // vtable +0x74

    bool IsNearGoal();                        // 0x00c42e20
};
struct HomeInfo {
    char mPad000[0x104];
    s32  m104;                                // +0x104
    char mPad108[0x164 - 0x108];
    void* mOwner;                             // +0x164  (the "owner" creature)
};
class cSPCreatureBase {
public:
    PV8 PV8 PV8 PV8 PV                        // vtable 0x00 .. 0x80
    virtual void v84(void*, int, int);        // vtable +0x84

    char  mPad04[0xc0 - 4];                   // +0x04
    Loco  mLoco;                              // +0xc0
    char  mPadc4[0xb4c - 0xc4];               // +0xc4
    cBehaviorTreeData* mpBTree;               // +0xb4c
    char  mPadb50[0xb58 - 0xb50];             // +0xb50
    u32   mFlagsB58;                          // +0xb58
    char  mPadb5c[0xf90 - 0xb5c];             // +0xb5c
    u8    mFlagF90;                           // +0xf90

    void*   FUN_00c0b370(s32 id);             // 0x00c0b370 (ret 4)
    HomeInfo* FUN_00c04590();                 // 0x00c04590
    cSPCreatureBase* GetTargetAsCreature();   // 0x00c0ee70
    u32     PlayAnimation(u32 id, int a, int b);   // 0x00c12190 (ret 0x0c)
    bool    AnimationFinished(u32 id);        // 0x00c12400 (ret 4)
    void    MoveToPointAtSpeed(int a, const Vec3* p, f32 s0, f32 s1);  // 0x00c1c1d0 (ret 0x10)
};
struct cPlanetModel {
    void DirectionToSurfacePosition(Vec3* out, const Vec3* pos);              // 0x00b815a0 (ret 8)
    void MakeRandomWorldPosition(Vec3* out, const Vec3* center, f32 minR, f32 maxR);  // 0x00b81780 (ret 0x10)
};
// ---- items of slice s00d61c20 end

// ---- items of slice s00d65250 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRef {
  virtual void AddRef();      // +0x00
  virtual void Release();     // +0x04
  void* Get(IRef** out);      // 0x00c04590
};
struct ListNode {
  ListNode* mpNext;           // +0x00
  ListNode* mpPrev;           // +0x04
  IRef* mpObject;             // +0x08
};
struct IntrusiveList {
  ListNode mHead;             // +0x00 (sentinel)
  uint32_t mPad0c[3];         // +0x0c
  ListNode* mpFree;           // +0x18

  void Remove(IRef** object);
};
struct Manager {
  uint8_t mPad00[0x168];
  IntrusiveList mList;        // +0x168
};
struct FreeListAlloc {
  uint8_t mPad00[0x10];       // +0x00
  void* mpFree;               // +0x10
  bool AddCore(void* core, uint32_t count);
};
struct PoolBlock {
  uint32_t mPad00[2];         // +0x00
  IRef* mpObject;             // +0x08
};
struct Pool {
  uint8_t mPad00[8];          // +0x00
  FreeListAlloc mAlloc;       // +0x08

  void* Alloc(IRef** object);
};
typedef int (__thiscall* FnI)(void*);
void   FUN_00d99ac0(void* a, void* b, int c);          // 0x00d99ac0
void   FUN_00c14750(int flag);                         // 0x00c14750
void*  FUN_00d99500(uint32_t handle);                  // 0x00d99500
void*  FUN_00b3d2a0(void* x);                          // 0xb3d2a0
struct AimResult {
  uint8_t mValid;             // +0x00
  uint8_t mPad01[3];
  int mField04;               // +0x04
  int mField08;               // +0x08
  int mField0c;               // +0x0c
};
// ---- items of slice s00d65250 end

// ---- items of slice s00d6f1c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
struct cBehaviorStimuli {
    uint8_t pad000[8];                                  // +0x00 .. +0x07

    void ClearAll(uint32_t mask, uint32_t flags);        // 0x00bc98f0
};
}
namespace SP {
struct cBehaviorTree {
    uint8_t        pad000[8];                           // +0x00 .. +0x07
    cBehaviorStimuli mStimuli;                          // +0x08
};
}
namespace SP {
class cAvatar_s00d6_f1c0 {
public:
    uint8_t  pad000[0x5a8];                             // +0x000 .. +0x5a7
    uint32_t mTargetHandle;                             // +0x5a8
};
}
namespace SP {
class cGameNounManager_s00d6_f1c0 {
public:
    cAvatar_s00d6_f1c0* GetAvatar();                               // 0x00b1fdb0
};
}
namespace SP {
cGameNounManager_s00d6_f1c0* __cdecl NounManager_s00d6_f1c0();                 // 0x00b3d300
}
namespace SP {
class cBehaviorActor {
public:
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
    virtual void v080();
    virtual void PushTargetAction(void* pTarget, int mode, int flags); // +0x84

    uint8_t        pad004[0xb48];                       // +0x004 .. +0xb4b
    cBehaviorTree* mpBehavior;                          // +0xb4c
};
}
// ---- items of slice s00d6f1c0 end

// @ 0x00d61b20
void FUN_00d61b20(Creature* c)
{
    VC3<void, int, int, int>(c, 33, 0, 0, 0);
    ((CreatureB*)c)->UpdateLocomotion(0);
}

// @ 0x00d61b50
float FUN_00d61b50(int v)
{
    Node* n = GetActiveNode();
    if (((u8)(n->mFlags >> 4) & 1) != 0 && n->Parent() == v)
        return 1.0f;
    return 0.0f;
}

// @ 0x00d61b80
void FUN_00d61b80(CreatureB* c, int a2, int a3, int a4, int a5, int* out)
{
    c->FUN_00c0b370(-1);
    ((StimSetB*)(F<char*>(c, 0xb4c) + 8))->ClearAll(0, 0x10);
    out[2] = -1;
}

// @ 0x00d61bb0
float FUN_00d61bb0()
{
    Node* n = GetActiveNode();
    if (((u8)(n->mFlags >> 4) & 1) != 0 && n->Parent() != 0)
        return 1.0f;
    return 0.0f;
}

// @ 0x00d61be0
float FUN_00d61be0(void* a1)
{
    AvatarN* avatar = NounManagerB()->GetAvatar();
    Node* n = GetActiveNode();
    if (((u8)(n->mFlags >> 4) & 1) != 0) {
        int x = avatar->Get();
        int y = ((AvatarN*)a1)->Get();
        if (y == x)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00d61c20
bool __cdecl FUN_00d61c20(cSPCreatureBase* c, int, int, int, int, int* st)
{
    cGameNounManager* nouns = NounManager();
    nouns->GetAvatar();
    cDramaManager* dm = (cDramaManager*)FUN_00d51660();
    if (((u8)(dm->mMode6c >> 4) & 1) == 0)
        return false;
    switch (*st) {
    case 0:
        if (c->mLoco.IsNearGoal())
            *st = 1;
        break;
    case 1: {
        AnimPlayRes* r = c->mpBTree->mStimuli.Play(0, 0x10);
        if (r != 0)
            c->PlayAnimation(r->mAnimId, 1, -1);
        c->mpBTree->mStimuli.ClearAll(0, 0x10);
        return true;
    }
    default:
        break;
    }
    return true;
}

// @ 0x00d61cb0
void __cdecl FUN_00d61cb0(cSPCreatureBase* c)
{
    c->FUN_00c0b370(-1);
    c->mpBTree->mStimuli.ClearAll(0, 0x10);
}

// @ 0x00d61d90
f32 __cdecl FUN_00d61d90(cSPCreatureBase* c)
{
    HomeInfo* h = c->FUN_00c04590();
    void** ownerSlot = &h->mOwner;
    void* owner = *ownerSlot;
    if (FUN_00d99500(owner) == 0)
        return 0.0f;
    return 1.0f;
}

// @ 0x00d61e00
f32 __cdecl FUN_00d61e00(cSPCreatureBase* c)
{
    HomeInfo* h = c->FUN_00c04590();
    void** ownerSlot = &h->mOwner;
    cSPCreatureBase* owner = (cSPCreatureBase*)*ownerSlot;
    if (owner != 0) {
        void* r = owner->mpBTree->mPtr600;
        if (r != 0 && *(u32*)((char*)r + 8) == 0x2d852e6)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00d61e40
bool __cdecl FUN_00d61e40(cSPCreatureBase* c, int, int, int, int, int* st)
{
    HomeInfo* h = c->FUN_00c04590();
    void** ownerSlot = &h->mOwner;
    cSPCreatureBase* owner = (cSPCreatureBase*)*ownerSlot;

    f32 r = c->mLoco.GetFootprintRadius() * g_f13f08e4;
    f32 len = sqrtf(r * ((f32)c->FUN_00c04590()->m104 * r));
    f32 back = owner->mLoco.GetFootprintRadius() + len;

    Vec3 dirTmp;
    Vec3* dir = owner->mLoco.GetDirection(&dirTmp);
    f32 inv = 1.0f / sqrtf(dir->x * dir->x + dir->y * dir->y + dir->z * dir->z + g_f13ec4b8);
    Vec3 n;
    n.x = dir->x * inv;
    n.y = dir->y * inv;
    n.z = dir->z * inv;

    Vec3 want;
    Vec3* pos = owner->mLoco.GetPosition();
    want.x = pos->x - n.x * back;
    want.y = pos->y - n.y * back;
    want.z = pos->z - n.z * back;

    Vec3 surf;
    PlanetModel()->DirectionToSurfacePosition(&surf, &want);

    Vec3 rnd;
    PlanetModel()->MakeRandomWorldPosition(&rnd, &surf, 0.0f, len);

    cSPCreatureBase* tc = owner->GetTargetAsCreature();
    c->v84(tc != 0 ? (void*)((char*)tc + 0x5a8) : 0, 1, 0);
    c->MoveToPointAtSpeed(2, &rnd, 1.0f, g_f1470f1c);

    st[0] = 0;
    st[1] = 0;
    return true;
}

// @ 0x00d65250
void IntrusiveList::Remove(IRef** object)
{
  ListNode* node = mHead.mpNext;
  while (node != &mHead) {
    IRef* obj = node->mpObject;
    node = node->mpNext;
    if (obj == *object) {
      ListNode* curr = node->mpPrev;
      curr->mpPrev->mpNext = curr->mpNext;
      curr->mpNext->mpPrev = curr->mpPrev;
      if (curr->mpObject != 0)
        curr->mpObject->Release();
      curr->mpNext = mpFree;
      mpFree = curr;
    }
  }
}

// @ 0x00d652a0
void* Pool::Alloc(IRef** object)
{
  FreeListAlloc* alloc = &mAlloc;
  void* block;
  for (;;) {
    if (alloc->mpFree != 0) {
      block = alloc->mpFree;
      alloc->mpFree = *(void**)block;
      break;
    }
    if (!alloc->AddCore(0, 0)) {
      block = 0;
      break;
    }
  }

  PoolBlock* b = (PoolBlock*)block;
  if ((int*)b + 2 != 0) {
    IRef* o = *object;
    b->mpObject = o;
    if (o != 0)
      o->AddRef();
  }
  return block;
}

// @ 0x00d652f0
void FUN_00d652f0(IRef* object)
{
  if (object != 0)
    object->AddRef();

  Manager* mgr = (Manager*)object->Get(&object);
  mgr->mList.Remove(&object);

  if (object != 0)
    object->Release();
}

// @ 0x00d65330
uint32_t FUN_00d65330(int* self, uint32_t arg2, uint32_t arg3, int arg4, uint32_t arg5, AimResult* out)
{
  void* ctx = FUN_00b3d2a0(0);
  int* world = (int*)((uint8_t*)ctx + 0x164);
  void* handle = FUN_00d99500((uint32_t)world);
  if (handle == 0)
    return 0;

  int* anchor = (int*)((uint8_t*)world + 0xc0);
  out->mValid = 0;
  int* pos = (int*)((FnI)(*(void***)anchor)[0x2c / 4])(anchor);
  *(int*)&out->mField04 = pos[0];
  *(int*)&out->mField08 = pos[1];
  *(int*)&out->mField0c = pos[2];

  char ok = (char)((FnI)(*(void***)((uint8_t*)self[0x30] + 0))[0xf8 / 4])((void*)self[0x30]);
  if (ok == 0)
    FUN_00c14750(1);

  FUN_00d99ac0(anchor, self + 0x30, 1);

  float* a = (float*)((FnI)(*(void***)anchor)[0x2c / 4])(anchor);
  int* list = (int*)((uint8_t*)ctx + 0x168);
  (void)list;
  (void)a;
  (void)arg2; (void)arg3; (void)arg4; (void)arg5;
  return 0;
}

// @ 0x00d65850
bool __fastcall FUN_00d65850(int* self)
{
  int* p = *(int**)(*(int**)(*(int**)((uint8_t*)self + 0x28) + 0xb4c) + 0x600);
  bool result = false;
  if (p != 0)
    result = p[2] == 0x060995fc;
  return result;
}

// @ 0x00d6f590
namespace SP {
void __fastcall FUN_00d6f590(cBehaviorActor* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00d6f760
namespace SP {
void __cdecl FUN_00d6f760(cBehaviorActor* pActor)
{
    pActor->PushTargetAction(0, 0, 0);
    pActor->mpBehavior->mStimuli.ClearAll(0, 0x80);
}
}  // namespace SP

// @ 0x00d6f790
namespace SP {
bool __cdecl FUN_00d6f790(cBehaviorActor* pActor, int p1, int p2, int p3, int p4, int32_t* pOut)
{
    (void)p1;
    (void)p2;
    (void)p3;
    (void)p4;
    cAvatar_s00d6_f1c0* pAvatar = NounManager_s00d6_f1c0()->GetAvatar();
    uint32_t* pTarget = pAvatar ? &pAvatar->mTargetHandle : 0;
    pActor->PushTargetAction(pTarget, 1, 0);
    pOut[0] = 0;
    pOut[1] = 0;
    return true;
}
}  // namespace SP
