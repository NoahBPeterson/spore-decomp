// Slice s00d32fd0 -- 0x00d32fd0 SP::cCreatureModeInputStrategy::SetRolloverObject-style object command handler
// (the interact-with-object dispatcher of the creature-stage input strategy; the dev PDB's caller-scored
// candidate name is HandleSimulationCommon).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same as the sibling slices s00d31a70 / s00d35190).
//
// Classifies the clicked object (FUN_00d30830 returns a command id), ignores ids 0..2 and 4, then looks
// up the avatar and, for every command, makes the avatar target / animate towards the object and spawns
// the acknowledgement effect:  6 attack-ish, 7/8/0xd food, 9 combatant, 0xa/0xb/0xc social actions,
// 0xf/0x11 selection, 0x10/0x13 etc., 0x14 callout message box, 0x1b move to a planet position, 0x1c
// hold-to-move handling (timer + UpdateAvatarGoal).
#include "types.h"

#pragma warning(disable : 4238)

namespace SP {

struct Vector3 { float x, y, z; };

#define VFUNC(obj, off) ((*(void***)(obj))[(off) / 4])

const float kFloatMax = 3.4028234663852886e+38f;   // 0x147a5f0

struct cAnimReq { int p[3]; int mC; int m10; };     // returned by PlayAnimation / Notify

struct cSPTimer {
  bool IsRunning();   // 0x00feba90
  void Start();       // 0x00bc30f0
  uint32_t mData[8];
};

struct cPosInterface {
  const Vector3& GetPosition() { return ((const Vector3&(__thiscall*)(void*))VFUNC(this, 0x2c))(this); }
};

struct cBehaviorTreeData {
  char pad0[8];
  struct Sub { cAnimReq* Notify(uint64_t flags, float range, void* who); } mSub;   // +0x08 (0x00bc97f0)
  char pad9[0x1d8 - 0x9];
  int m1d8;
};

struct cCreatureAnimal {
  void SetCreatureTarget(void* target, int b, int intention) {
    ((void(__thiscall*)(void*, void*, int, int))VFUNC(this, 0x84))(this, target, b, intention);
  }
  cAnimReq* PlayAnimation(uint64_t flags, float range, int a, int b, void* c, int d);   // 0x00c03190
  cAnimReq* PlayAnimEx(uint64_t a, uint64_t b, float f, int c0, int c1, int c2, int c3, void* who, int d);   // 0x00c0bf10
  int GetRecentIndex();            // 0x00c0f780
  int GetRecentValue(int idx);     // 0x00c0f8a0
  int GetSelA();                   // 0x00c0dac0
  int GetSelB();                   // 0x00c0db10
  void MoveToPointAndFacingAtSpeed(int mode, const Vector3* p, const Vector3* d, float s0, float s1);   // 0x00c1c5c0

  char pad0[0xc0];
  cPosInterface mLoco;             // +0xc0
  char padc4[0xb4c - 0xc4];
  cBehaviorTreeData* mpBehavior;   // +0xb4c
  char padb50[0xb58 - 0xb50];
  uint32_t mGeneralFlags;          // +0xb58
  bool mbB5C;                      // +0xb5c
  char padb5d[0xe70 - 0xb5d];
  int mE70;
  int mE74;
};

struct cObjB {   // object cast with id 0x2c9cc91
  char pad[0x164];
  int m164;
  char pad168[4];
  int m16c;
  void* Lookup();   // 0x00b058a0
};

struct cObjC {   // object cast with id 0x18ebadc
  char pad[0x34];
  cPosInterface sub34;
  char pad38[0x780 - 0x38];
  char m780[16];
};

struct cPlanet {
  bool Has(void* p);    // 0x00c74400
  void Add(void* p);    // 0x00c74470
};
struct cPlanetModel { Vector3* Project(Vector3* out, const Vector3* pos); };   // 0x00b81630

struct cGameNounManager { cCreatureAnimal* GetAvatar(); };   // 0x00b1fdb0
struct cTutorial { void Select(void* animal); };             // 0x00ba4f30
struct cGameTimeManager { uint32_t pad[0x48 / 4]; uint32_t mFlags; };
struct cCreatureModeStrategy {
  static cCreatureModeStrategy* Instance();        // 0x00d38840
  void SignalCreatureEvent(uint32_t id);           // 0x00d3cdc0
};
struct cPickHelper { int Pick(cCreatureAnimal* who, void* target, char* outFlag); };   // 0x00f1a320
struct cPickOwner { char pad[0x78]; cPickHelper* mpHelper; };
struct cWinTextRef { void Assign(void* p); };      // 0x00b5f950
struct cViewer {};
struct cRenderThing { cViewer* GetViewer() { return ((cViewer*(__thiscall*)(void*))VFUNC(this, 0x1c))(this); } };
struct cAppObj { cRenderThing* GetRender() { return ((cRenderThing*(__thiscall*)(void*))VFUNC(this, 0x50))(this); } };

cGameNounManager* NounManager();              // 0x00b3d300
cTutorial* Tutorial();                        // 0x00b3d4c0
uint32_t GetCurrentGameMode();                // 0x00b5b800
cGameTimeManager* GameTimeManager();          // 0x00b3d380
cPlanetModel* PlanetModel();                  // 0x00b3d350
cPlanet* GetActivePlanet();                   // 0x01021260
cAppObj* App();                               // 0x0067dd10
void normalized_safe(Vector3* out, const Vector3* in);   // 0x00449c20

int  __cdecl ClassifyObject(void* obj);                 // 0x00d30830
bool __cdecl IsPickedEntityBusy(void* ent);             // 0x00f0a690
void __cdecl ReleasePickedEntity(void* ent);            // 0x00f0a750
void* __cdecl interface_cast_IID(void* obj, uint32_t iid);   // 0x00ac80d0
void* __cdecl object_cast_Food(void* p);                // 0x00ae6740
int  __cdecl GetCreatureTypeId(int v);                  // 0x00c0c360 (v -> value)
void __cdecl ShowObjectInfo(int v);                     // 0x00d49920
void* __cdecl GetHelpText(void* obj);                   // 0x00b1fc00
void __cdecl CalloutMessageBox(void* a, void* b);       // 0x00809db0
void* __cdecl GetCameraThing(void* v);                  // 0x00b60a50
namespace { void SpawnAcknowledgementEffect(uint64_t flags, void* obj); }   // 0x00d2f940


extern cPickOwner* g_pPickOwner;      // 0x016c7aa4
extern cWinTextRef g_HelpTextRef;     // 0x01582d10
extern char g_CalloutA[];             // 0x01582d00
extern char g_CalloutB[];             // 0x01582d0c
extern bool g_bShowAvatarGoal;        // 0x0169e37e

class cCreatureModeInputStrategy {
public:
  void InteractWithObject(void* obj);   // 0x00d32fd0
  void UpdateAvatarGoal(bool a, bool b);   // 0x00d31a70

  char pad0[0xa0];
  cSPTimer mMouseDownTime;   // +0xa0
  bool mbMoveOnRelease;      // +0xc0
  bool mbMouseMoved;         // +0xc1
  char padc2[0x106 - 0xc2];
  bool mbHoldMove;           // +0x106
};

static const uint32_t kCreatureMode = 0x1654c10;

// @ 0x00d32fd0
void cCreatureModeInputStrategy::InteractWithObject(void* obj)
{
  int cmd = ClassifyObject(obj);
  if (cmd >= 0) {
    if (cmd < 3) return;
    if (cmd == 4) return;
  }

  cCreatureAnimal* avatar = NounManager()->GetAvatar();

  void* target;        // the object cast to the 0x17f243b interface
  cCreatureAnimal* who;   // the same object when it is an animal (type id 0x18eb45e), else 0
  if (obj == 0) {
    target = 0;
    who = 0;
  } else {
    target = ((void*(__thiscall*)(void*, uint32_t))VFUNC(obj, 0x0c))(obj, 0x17f243b);
    who = 0;
    if (target != 0 && ((uint32_t(__thiscall*)(void*))VFUNC(target, 0x20))(target) == 0x18eb45e) {
      who = (cCreatureAnimal*)target;
      Tutorial()->Select(target);
    }
  }

  if (GetCurrentGameMode() == kCreatureMode && target != 0) {
    uint32_t timeFlags = GameTimeManager()->mFlags;
    if (IsPickedEntityBusy(target) && (timeFlags & 1) == 0) {
      ReleasePickedEntity(target);
      return;
    }
  }

  int anim;   // animation id shared by the "generic acknowledge" commands
  switch (cmd) {
  case 6:
    avatar->SetCreatureTarget(0, 0, 0);
    avatar->PlayAnimation(0x0004000000000000ULL, kFloatMax, 1, 0, 0, 0);
    SpawnAcknowledgementEffect(0x0004000000000000ULL, 0);
    return;
  case 7:
    avatar->SetCreatureTarget(object_cast_Food(target), 0, 0);
    if (GetCurrentGameMode() != kCreatureMode)
      cCreatureModeStrategy::Instance()->SignalCreatureEvent(0x533535db);
    avatar->mpBehavior->mSub.Notify(0x100000, kFloatMax, 0);
    return;
  case 8:
    avatar->SetCreatureTarget(object_cast_Food(target), 1, 0);
    avatar->PlayAnimation(0x40000, kFloatMax, 0, 0, target, 0);
    SpawnAcknowledgementEffect(0x40000, target);
    return;
  case 9:
    avatar->SetCreatureTarget(who ? (void*)((char*)who + 0x5a8) : 0, 0, 0);
    avatar->PlayAnimation(8, kFloatMax, 0, 0, who, 0);
    SpawnAcknowledgementEffect(8, who);
    who->mpBehavior->mSub.Notify(8, 5.0f, avatar);
    return;
  case 10:
    if (avatar->mpBehavior->m1d8 == 0x13fefca7) {
      avatar->mpBehavior->mSub.Notify(0x4000000000000000ULL, kFloatMax, target);
      return;
    }
    avatar->PlayAnimation(0x4000000000000000ULL, kFloatMax, 0, 0, target, 0);
    SpawnAcknowledgementEffect(0x4000000000000000ULL, target);
    return;
  case 11: {
    cAnimReq* r = avatar->PlayAnimation(0x0004000000000000ULL, 30.0f, 7, 0, who, 0);
    if (r) r->m10 = who->GetRecentIndex();
    SpawnAcknowledgementEffect(0x0004000000000000ULL, who);
    return;
  }
  case 12: {
    int recent;
    int value = 0;
    if (GetCurrentGameMode() == kCreatureMode)
      recent = g_pPickOwner->mpHelper->Pick(avatar, target, 0);
    else
      recent = avatar->GetRecentIndex();
    if (recent != -1) value = avatar->GetRecentValue(recent);
    cAnimReq* r = avatar->PlayAnimation(0x0004000000000000ULL, kFloatMax, 6, value, target, 0);
    if (r) r->m10 = recent;
    SpawnAcknowledgementEffect(0x0004000000000000ULL, target);
    if (who != 0) {
      cAnimReq* r2;
      if (((who->mGeneralFlags >> 8) & 1) == 0) {
        r2 = who->mpBehavior->mSub.Notify(0x0004000000000000ULL, 30.0f, avatar);
        who->mpBehavior->mSub.Notify(0x0000800000000000ULL, kFloatMax, (void*)GetCreatureTypeId(value));
      } else {
        r2 = who->PlayAnimEx(0x0004000000000000ULL, 0x4004000020030030ULL, kFloatMax, 0x100000, 0, 0, 0, avatar, 0);
      }
      if (r2) {
        r2->mC = 7;
        r2->m10 = recent;
      }
    }
    return;
  }
  case 13:
    avatar->SetCreatureTarget(object_cast_Food(target), 1, 0);
    anim = 3;
    break;
  case 15: {
    int sel = avatar->GetSelA();
    if (GetCurrentGameMode() == kCreatureMode) {
      int other = avatar->mE74;
      if (other != -1) sel = other;
    }
    ShowObjectInfo(sel);
    SpawnAcknowledgementEffect(0x10000, target);
    return;
  }
  case 16:
    avatar->PlayAnimation(0x10000, kFloatMax, 0, 0, target, 0);
    SpawnAcknowledgementEffect(0x10000, target);
    return;
  case 17: {
    int sel = avatar->GetSelB();
    if (GetCurrentGameMode() == kCreatureMode) {
      int other = avatar->mE70;
      if (other != -1) sel = other;
    }
    ShowObjectInfo(sel);
    SpawnAcknowledgementEffect(0x10, target);
    return;
  }
  case 19:
    avatar->SetCreatureTarget(0, 0, 0);
    avatar->PlayAnimation(0x0000800000000000ULL, kFloatMax, 0, 0, target, 0);
    SpawnAcknowledgementEffect(0x0000800000000000ULL, target);
    return;
  case 20: {
    void* text = GetHelpText(target);
    if (text) {
      g_HelpTextRef.Assign(text);
      CalloutMessageBox(g_CalloutB, g_CalloutA);
    }
    return;
  }
  case 21:
    avatar->PlayAnimation(0x80, kFloatMax, 0, 0, target, 1);
    SpawnAcknowledgementEffect(0x80, target);
    return;
  case 22:
    avatar->SetCreatureTarget(0, 0, 0);
    anim = 3;
    break;
  case 23: {
    avatar->SetCreatureTarget(0, 0, 0);
    cObjB* ob = (cObjB*)interface_cast_IID(target, 0x2c9cc91);
    if (ob->m16c == 0) {
      void* found = ob->Lookup();
      if (found) {
        cAnimReq* r = avatar->PlayAnimation(0x20, kFloatMax, 0, 0, found, 0);
        if (r) {
          r->m10 = ob->m164;
          avatar->mbB5C = false;
          SpawnAcknowledgementEffect(0x20, ob);
          return;
        }
      }
    } else {
      avatar->PlayAnimation(0x20, kFloatMax, 0, 0, ob, 0);
    }
    avatar->mbB5C = false;
    SpawnAcknowledgementEffect(0x20, ob);
    return;
  }
  case 24:
    avatar->SetCreatureTarget(0, 0, 0);
    anim = 2;
    break;
  case 25:
    avatar->SetCreatureTarget(0, 0, 0);
    anim = 4;
    break;
  case 26:
    avatar->SetCreatureTarget(0, 0, 0);
    anim = 5;
    break;
  case 27: {
    cObjC* oc = (cObjC*)interface_cast_IID(target, 0x18ebadc);
    cPlanet* planet = GetActivePlanet();
    if (!planet->Has(oc->m780)) planet->Add(oc->m780);
    avatar->SetCreatureTarget(0, 0, 0);
    const Vector3& avatarPos = avatar->mLoco.GetPosition();
    Vector3 projected;
    const Vector3& ret = *PlanetModel()->Project(&projected, &oc->sub34.GetPosition());
    Vector3 dir;
    dir.x = ret.x - avatarPos.x;
    dir.y = ret.y - avatarPos.y;
    dir.z = ret.z - avatarPos.z;
    Vector3 facing;
    normalized_safe(&facing, &dir);
    avatar->MoveToPointAndFacingAtSpeed(2, &avatar->mLoco.GetPosition(), &facing, 1.0f, 2.0f);
    return;
  }
  case 28:
    avatar->mbB5C = false;
    if (mbHoldMove) {
      if (!mMouseDownTime.IsRunning()) {
        mMouseDownTime.Start();
        mbMouseMoved = false;
        void* app = App();
        void* render = ((void*(__thiscall*)(void*))VFUNC(app, 0x50))(app);
        void* cam = GetCameraThing(((void*(__thiscall*)(void*))VFUNC(render, 0x38))(render));
        if (cam) *((char*)cam + 0x315) = 1;
      }
    }
    UpdateAvatarGoal(true, true);
    g_bShowAvatarGoal = mbHoldMove;
    return;
  }
  avatar->PlayAnimation(0x0004000000000000ULL, kFloatMax, anim, 0, target, 0);
  SpawnAcknowledgementEffect(0x0004000000000000ULL, target);
}

}  // namespace SP
