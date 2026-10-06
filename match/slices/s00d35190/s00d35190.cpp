// @ 0x00d35190  SP::cCreatureModeInputStrategy::HandleMessage   (real name, PDB anchor)
// Flags: /O2 /MD /Gy /TP /arch:SSE  (no /EHsc: the local vector has no unwind frame).
//
// Creature-stage message handler (5422 B).  It is the override of the message
// handler interface that lives at +0x48 in the retail object, so MSVC passes
// `this` = that sub-object and reaches the strategy's own members at negative
// offsets (`[esi+0xc]` = mbEnabled at +0x54 of the full object).  The class
// below reproduces that layout with two bases.
//
// The body is a dispatcher over ~45 hashed message ids: banning / tribe-tool
// UI modes first (GameInputManager mode 2 / 3), then avatar commands: target
// selection (camera-cone pick or nearest creature), brain-level cheats,
// heal / damage cheats, spawning a creature of the avatar's species, the
// click-to-move goal, and the creature-mode strategy notifications.
#include "types.h"
#include <math.h>

#pragma warning(disable : 4238)  // address of a temporary (Variant fallback below)

namespace SP {

struct Vector3 { float x, y, z; };

#define VFUNC(obj, off) ((*(void***)(obj))[(off) / 4])

// ---------------------------------------------------------------------------
// EA::Variant (0x14 bytes): only the conditional-temporary path is used.
// ---------------------------------------------------------------------------
struct Variant {
  uint32_t mValue[4];
  uint16_t mFlags;   // +0x10
  uint16_t mTypeId;  // +0x12
  Variant(const uint32_t& v);             // 0x005bf350
  ~Variant() { if (mFlags & 4) Destruct(false); }
  void Destruct(bool reset);              // 0x0093db80
  const uint32_t* GetUInt32() const;      // 0x005727b0
};

// ---------------------------------------------------------------------------
// Game objects (retail offsets; vtable slots from the ModAPI headers).
// ---------------------------------------------------------------------------
struct Model { char pad[0x8c]; float mf8c; };

struct cSpatialObject {
  const Vector3& GetPosition() { return ((const Vector3&(__thiscall*)(void*))VFUNC(this, 0x2c))(this); }
  Model* GetModel() { return ((Model*(__thiscall*)(void*))VFUNC(this, 0xac))(this); }
};

struct cGameData {
  uint32_t GetPoliticalID() { return ((uint32_t(__thiscall*)(void*))VFUNC(this, 0x4c))(this); }
};

struct cCombatant {
  cSpatialObject* ToSpatialObject() { return ((cSpatialObject*(__thiscall*)(void*))VFUNC(this, 0x8))(this); }
  cGameData* ToGameData() { return ((cGameData*(__thiscall*)(void*))VFUNC(this, 0xc))(this); }
  int TakeDamage(float damage, uint32_t attackerPID, int type, const Vector3& dir, cCombatant* attacker) {
    return ((int(__thiscall*)(void*, float, uint32_t, int, const Vector3&, cCombatant*))VFUNC(this, 0x18))(
        this, damage, attackerPID, type, dir, attacker);
  }
  float GetMaxHitPoints() { return ((float(__thiscall*)(void*))VFUNC(this, 0x58))(this); }
  int GetCombatState();          // 0x008e7f80
  bool IsInvulnerable();         // 0x00bfc480
  void PartialRepair(float f);   // 0x00bfd1a0
};

struct MoveGoal {               // locomotion request (ctor 0x00ad29d0 / 0x00ac9850, dtor 0x007a41a0)
  uint32_t mData[0x1c];
  MoveGoal(const Vector3& target, float minDist, float maxDist);
  MoveGoal();
  ~MoveGoal();
};

struct cLocomotiveObject {
  const Vector3& GetPosition() { return ((const Vector3&(__thiscall*)(void*))VFUNC(this, 0x2c))(this); }
  Vector3 GetDirection() {
    Vector3 r;
    ((Vector3*(__thiscall*)(void*, Vector3*))VFUNC(this, 0x5c))(this, &r);
    return r;
  }
  void RequestMove(const MoveGoal& g) { ((void(__thiscall*)(void*, const MoveGoal&))VFUNC(this, 0xdc))(this, g); }
  bool IsIdle() { return ((bool(__thiscall*)(void*))VFUNC(this, 0xf8))(this); }
  const Vector3& GetVelocity();  // 0x00d20610
};

struct cBehaviorTreeData {
  char pad0[8];
  struct Sub { void Notify(uint64_t flags, float range, int x); } mSub;   // +0x08 (0x00bc97f0)
  char pad9[0x1c8 - 0x9];
  uint64_t mFlags;   // +0x1c8
};

struct cCreatureAnimal {
  uint32_t GetPoliticalID() { return ((uint32_t(__thiscall*)(void*))VFUNC(this, 0x4c))(this); }
  void SetCreatureTarget(cCombatant* target, bool b, int intention) {
    ((void(__thiscall*)(void*, cCombatant*, bool, int))VFUNC(this, 0x84))(this, target, b, intention);
  }
  int GetCurrentBrainLevel() { return ((int(__thiscall*)(void*))VFUNC(this, 0xd8))(this); }
  void SetCurrentBrainLevel(int l) { ((void(__thiscall*)(void*, int))VFUNC(this, 0xdc))(this, l); }
  void SetFlagE8(int v) { ((void(__thiscall*)(void*, int))VFUNC(this, 0xe8))(this, v); }

  cCombatant* GetTarget();                                         // 0x00c0ee60
  void PlayAnimation(uint64_t flags, float range, int a, int b, int c, int d);   // 0x00c03190
  cCreatureAnimal* GetSpeciesTemplate();                           // 0x00c04590
  float GetHealth();                                               // 0x00c0b9c0
  void SetHealth(float h);                                         // 0x00c0b9d0
  bool IsInWater();                                                // 0x00c0c120
  void ReturnToIdle(int v);                                        // 0x00c14750
  void SetupFromTemplate(int v);                                   // 0x00c6ace0
  void FinishSetup();                                              // 0x00c6b540

  char pad0[0x88];
  uint32_t m88;                       // +0x88
  char pad8c[0xc0 - 0x8c];
  cLocomotiveObject mLoco;            // +0xc0
  char padc1[0xf0 - 0xc1];
  uint32_t mf0;                       // +0xf0
  char padf4[0x110 - 0xf4];
  uint32_t mf110;                     // +0x110
  char pad114[0x137 - 0x114];
  bool mb137;                         // +0x137
  char pad138[0x5a8 - 0x138];
  cCombatant mCombatant;              // +0x5a8
  char pad5a9[0xb20 - 0x5a9];
  void* mpSpeciesProfile;             // +0xb20
  char padb24[0xb28 - 0xb24];
  char mb28[0x24];                    // +0xb28
  cBehaviorTreeData* mpBehavior;      // +0xb4c
  char padb50[0xb58 - 0xb50];
  uint32_t mGeneralFlags;             // +0xb58
  bool mbB5C;                         // +0xb5c
  bool mbB5D;
  bool mbDead;                        // +0xb5e
  char padb5f[0x1124 - 0xb5f];
  char mNearbyCreatures[0x10];        // +0x1124
};

// Iterator over cCreatureAnimal::mNearbyCreatures.
struct NearbyIterator {
  void** mpCur;
  void** mpEnd;
  NearbyIterator(void* container, char* tag);   // 0x00b41a40
  void Next();                                  // 0x00b3d850
};

struct ObjectRefVector {   // eastl::vector<AutoRefCount<cSpatialObject>, sp_vector_allocator>
  cSpatialObject** mpBegin;
  cSpatialObject** mpEnd;
  cSpatialObject** mpCapacity;
  uint32_t mAllocator;
  ObjectRefVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~ObjectRefVector();   // 0x00ad92d0
};

struct TargetSortCompare {   // 0x1c-byte functor, ctor 0x00d2f380
  uint32_t mData[7];
  TargetSortCompare(const Vector3& camPos, const Vector3& camDir, float range);
};
void SortTargets(cSpatialObject** first, cSpatialObject** last, TargetSortCompare cmp);   // 0x00d34fc0

struct cSPTimer {
  bool IsRunning();             // 0x00feba90
  void Start();                 // 0x00bc30f0
  void Stop();                  // 0x00bc3170
  uint64_t GetElapsedTime();    // 0x00bc3190
  uint32_t mData[8];
};

// Message argument interfaces.
struct IMessageArgs {
  void* GetArg(int i) { return ((void*(__thiscall*)(void*, int))VFUNC(this, 0x1c))(this, i); }
};
struct IMessageData {
  IMessageArgs* GetArgs() { return ((IMessageArgs*(__thiscall*)(void*))VFUNC(this, 0x10))(this); }
};
struct cGameDataRef { void* GetObject(); };   // 0x00bd6a60

struct cGameInputManager {
  int GetMode() { return ((int(__thiscall*)(void*))VFUNC(this, 0x34))(this); }
  void SetMode(int m) { ((void(__thiscall*)(void*, int))VFUNC(this, 0x38))(this, m); }
};
struct cMessageServer {
  void Post(uint32_t id, int a, int b) { ((void(__thiscall*)(void*, uint32_t, int, int))VFUNC(this, 0x14))(this, id, a, b); }
};
struct cViewer {
  void GetCameraLocationInfo(Vector3* pos, Vector3* right, Vector3* up, Vector3* forward);   // 0x007c3d30
};
struct cRenderer { cViewer* GetViewer() { return ((cViewer*(__thiscall*)(void*))VFUNC(this, 0x1c))(this); } };
struct cApp { cRenderer* GetRenderer() { return ((cRenderer*(__thiscall*)(void*))VFUNC(this, 0x50))(this); } };
struct cSpatialQuery {
  void FindObjects(const Vector3& center, float radius, ObjectRefVector* out, int a, int b, int c) {
    ((void(__thiscall*)(void*, const Vector3&, float, ObjectRefVector*, int, int, int))VFUNC(this, 0x48))(
        this, center, radius, out, a, b, c);
  }
};
struct cGameNounManager {
  cCreatureAnimal* GetAvatar();                                                         // 0x00b1fdb0
  cCreatureAnimal* CreateCreature(const Vector3& pos, void* species, int a, int b, int c, int d);  // 0x00b23940
};
struct cPlanetModel { Vector3 MakeRandomWorldPosition(const Vector3& pos, float minR, float maxR); };   // 0x00b81780
struct cPosseSimulator { char pad[0x18]; int mState; void Disband(int v); };  // 0x00d52e40
struct cSettingsFlags { char pad[0x6c]; uint32_t mFlags; };
struct cUIRefCounted { void Release() { ((void(__thiscall*)(void*))VFUNC(this, 0xc0))(this); } };
struct cUIRefPtr { cUIRefCounted* mp; void Assign(void* p); };   // 0x00c70110
struct cCanvas { bool IsVisible(); void SetVisible(bool v); };   // 0x00801400 / 0x008013d0
struct cCamManager { void Unlock(int v); };                      // 0x00e3e350 target object
struct cUIManagerA { void Reset(); };                            // 0x00ad7dc0
struct cHintManager { void ShowHint(int a, uint32_t id, int b); };  // 0x00e3e350
struct cGameModeMgr { void Leave(uint32_t id); };                // 0x00b1e410
struct cTutorial { void Select(void* animal); void Tag(int k, void* where, void* animal); };  // 0x00ba4f30 / 0x00ba48b0
struct cCinematic { void Stop(int v); };                         // 0x00e190c0
struct cEditorLauncher { void Launch(int v) { ((void(__thiscall*)(void*, int))VFUNC(this, 0x28))(this, v); } };
struct cSubStrategy { void Exit(int v); };                       // 0x00d2c200
struct cUIRolloverTarget { void Activate() { ((void(__thiscall*)(void*))VFUNC(this, 0x48))(this); } };

class cCreatureModeStrategy {
public:
  static cCreatureModeStrategy* Instance();                 // 0x00d38840
  static cCreatureModeStrategy* spInstance;                 // 0x0169e294
  static void NotifyEvent(float value);                     // 0x00d2e8a0
  void NotifyWantToGoToEditor(int v);                       // 0x00d3c6a0
  void SignalCreatureEvent(uint32_t id);                    // 0x00d3cdc0
  void PostKillMessage(uint32_t id, void* data);            // 0x00d39360
  char pad[0x68];
  cSubStrategy* mpSub;   // +0x68
};

struct cUIBanningContent {
  static void EndBanMode(int v);                  // 0x00dd1840
  static void ShowConfirmationDialog(void* obj);  // 0x00dd1aa0
};
struct cSPUISpace { static void KillSetiEffects(uint32_t id, int state); };   // 0x00435ed0

cGameInputManager* GameInputManager();        // 0x00b3d250
cGameNounManager* NounManager();              // 0x00b3d300
cPlanetModel* PlanetModel();                  // 0x00b3d350
cMessageServer* MessageServer();              // 0x0067dcc0
cApp* App();                                  // 0x0067dd10
uint32_t GetCurrentGameMode();                // 0x00b5b800
cUIManagerA* UIManagerA();                    // 0x00b3d4d0
cHintManager* HintManager();                  // 0x00b3d410
cGameModeMgr* GameModeManager();              // 0x00b3d320
cSpatialQuery* SpatialQuery();                // 0x00b3d240
cTutorial* Tutorial();                        // 0x00b3d4c0
cCinematic* CinematicManager();               // 0x00b3d3f0
cCanvas* MainCanvas();                        // 0x0067cab0
cEditorLauncher* EditorLauncher();            // 0x00d37cb0
cSettingsFlags* CreatureSettings();           // 0x00d51660
cPosseSimulator* PosseSimulatorInstance();    // 0x00d539d0
Vector3 normalized_safe(const Vector3& v);    // 0x00449c20
float Dot3(const Vector3& a, const Vector3& b);   // 0x00455cc0
int GetRecorderState();                       // 0x00435e90

void* interface_cast_IID(void* obj, uint32_t iid);          // 0x00ac80d0
cCreatureAnimal* interface_cast_Animal(void* obj);           // 0x00ac8960
cUIRolloverTarget* interface_cast_Rollover(void* obj);       // 0x00ac86f0
cUIRefCounted* interface_cast_Selectable(void* obj);         // 0x00ac8710
cCombatant* CombatantFromObject(cSpatialObject* obj);        // 0x00cb45b0
bool IsSelectableTarget(cCombatant* c);                      // 0x00d30f60
cCreatureAnimal* AnimalFromCombatant(cCombatant* c);         // 0x00ae33b0
float GetCurrentDNA();                                       // 0x00d2e350
int IsHUDHidden();                                           // 0x00d2e490
void SetHUDHidden(int hidden, int animate);                  // 0x00d2e4a0
void ToggleDebugDisplay();                                   // 0x00b676a0
void TribeToolEndMode(int v);                                // 0x00e09a50
void TribeToolConfirm(void* obj);                            // 0x00e09bf0
void SetAvatarMoveTarget(cCreatureAnimal* avatar, const Vector3& target);   // 0x00d2ec50
namespace { void SpawnAcknowledgementEffect(uint64_t flags, int a); }       // 0x00d2f940

// Globals.
extern bool g_bAutoRunLocked;          // 0x0169e170
extern bool g_bShowAvatarGoal;         // 0x0169e37e
extern bool g_bFreeCamera;             // 0x0169e37c
extern int g_CheatEventKind;           // 0x0169e370
extern cUIRefPtr g_pSelectedUI;        // 0x0168e814
extern float g_TargetPickRange;        // 0x01582d20
extern int g_TargetPickMaxCount;       // 0x01582d1c
extern uint32_t g_ClickMoveTimeMs;     // 0x01582bc8
extern float g_MoveGoalMinDist;        // 0x01582bac
extern float g_MoveGoalMaxDist;        // 0x01582bb0
extern float g_DNAReward[4];           // 0x01582e38
extern const Vector3 g_KillDamageDir;  // 0x0169e17c
extern const Vector3 g_SetiDamageDir;  // 0x0169e220

const float kFloatMax = 3.4028234663852886e+38f;

// ---------------------------------------------------------------------------
// The strategy (retail layout).
// ---------------------------------------------------------------------------
struct cInputStrategyBase {        // cInputStrategy + cSPUICursorStrategy + IWinProc
  virtual void InputStrategy0();
  uint32_t mBase[0x11];
};
struct IMessageHandler {           // at +0x48
  virtual bool HandleMessage(uint32_t messageID, IMessageData* pMessage) = 0;
};

class cCreatureModeInputStrategy : public cInputStrategyBase, public IMessageHandler {
public:
  virtual bool HandleMessage(uint32_t messageID, IMessageData* pMessage);

  void BeginBanMode();                         // 0x00d2eb70
  void BeginTribeToolMode();                   // 0x00d2ebc0
  void ToggleAutoRun();                        // 0x00d32330
  void UpdateAvatarGoal(bool a, bool b);       // 0x00d31a70
  void SetRolloverObject(void* obj);           // 0x00d32fd0

  uint32_t m4c, m50;
  bool mbEnabled;              // +0x54
  char pad55[0xa0 - 0x55];
  cSPTimer mMouseDownTime;     // +0xa0
  bool mbMoveOnRelease;        // +0xc0
  bool mbMouseMoved;           // +0xc1
  char padc2[0x104 - 0xc2];
  bool mbHoldingObject;        // +0x104
  bool mbReleaseHeld;          // +0x105
};

inline float Clamp(float v, float lo, float hi) {
  float r = v < lo ? lo : v;
  return hi < r ? hi : r;
}

// Picks a target in front of the camera (creature game mode) or the nearest
// creature of another species, and makes the avatar target it.
static __forceinline bool PickTarget(cCreatureAnimal* avatar);

// @ 0x00d35190
bool cCreatureModeInputStrategy::HandleMessage(uint32_t messageID, IMessageData* pMessage)
{
  if (messageID == 0x477f66c) {
    UIManagerA()->Reset();
    cCreatureModeStrategy::Instance()->mpSub->Exit(0);
    HintManager()->ShowHint(1, 0x1654c02, 1);
    if (mbHoldingObject) {
      mbReleaseHeld = true;
      return true;
    }
    GameModeManager()->Leave(0x1654c02);
    return true;
  }
  if (messageID == 0xd33b6aa2) {
    mMouseDownTime.Stop();
    return true;
  }
  if (!mbEnabled)
    return true;

  // Banning mode.
  if (messageID == 0x44eaa93) {
    BeginBanMode();
    return true;
  }
  if (GameInputManager()->GetMode() == 2) {
    if (messageID == 0x452e0ca) {
      cUIBanningContent::EndBanMode(1);
      GameInputManager()->SetMode(0);
    } else if (messageID == 0xb332763d) {
      cGameDataRef* ref = (cGameDataRef*)pMessage->GetArgs()->GetArg(0);
      if (ref) {
        void* obj = ref->GetObject();
        if (obj)
          cUIBanningContent::ShowConfirmationDialog(obj);
      }
    } else if (messageID == 0xf3327645) {
      BeginBanMode();
    }
    return true;
  }

  // Tribe-tool mode.
  if (messageID == 0x620222b) {
    BeginTribeToolMode();
    return true;
  }
  if (GameInputManager()->GetMode() == 3) {
    if (messageID == 0x620271c) {
      TribeToolEndMode(0);
      GameInputManager()->SetMode(0);
    } else if (messageID == 0x62663dc) {
      cGameDataRef* ref = (cGameDataRef*)pMessage->GetArgs()->GetArg(0);
      if (ref) {
        void* obj = ref->GetObject();
        if (obj)
          TribeToolConfirm(obj);
      }
    } else if (messageID == 0x62663dd) {
      BeginTribeToolMode();
    }
    return true;
  }

  cCreatureAnimal* avatar = NounManager()->GetAvatar();
  if (avatar->mbDead)
    return true;

  // Message arguments: picked object and an optional integer.
  cGameDataRef* picked;
  const Variant* pValue = 0;
  IMessageArgs* args;
  if (pMessage != 0 && (args = pMessage->GetArgs()) != 0) {
    picked = (cGameDataRef*)args->GetArg(0);
    pValue = (const Variant*)args->GetArg(1);
    args->GetArg(2);
  } else {
    picked = 0;
  }
  uint32_t value = *(pValue ? pValue : &Variant(0))->GetUInt32();

  if ((CreatureSettings()->mFlags >> 4) & 1) {
    if (messageID == 0x1c41da1) {
      avatar->SetFlagE8(1);
      cPosseSimulator* posse = PosseSimulatorInstance();
      if (posse)
        posse->Disband(1);
      avatar->SetCreatureTarget(0, false, 0);
    }
    return true;
  }

  switch (messageID) {
  case 0x1c0e5ee: {   // DNA cheat
    float dna = GetCurrentDNA();
    cCreatureModeStrategy::NotifyEvent(dna * 1.1f + 50.0f - dna);
    return true;
  }

  case 0x19edcf3:     // start moving with the mouse
    avatar->mbB5C = false;
    if (!mMouseDownTime.IsRunning()) {
      mMouseDownTime.Start();
      mbMouseMoved = false;
    }
    UpdateAvatarGoal(true, false);
    g_bShowAvatarGoal = true;
    return true;

  case 0x19d5174:     // auto-run
    if (g_bAutoRunLocked) {
      ToggleAutoRun();
      g_bShowAvatarGoal = false;
    } else {
      UpdateAvatarGoal(true, true);
      g_bShowAvatarGoal = true;
    }
    return true;

  case 0x1c0e6e7: {   // brain level up cheat
    int maxLevel = 4;
    int level = avatar->GetCurrentBrainLevel() + 1;
    avatar->SetCurrentBrainLevel(maxLevel < level ? maxLevel : level);
    cPosseSimulator* posse = PosseSimulatorInstance();
    if (posse)
      posse->mState = 3;
    return true;
  }

  case 0x1c38e3b:     // rollover
    SetRolloverObject(picked ? picked->GetObject() : 0);
    return true;

  case 0x1c41da1:     // cancel / deselect
    if (avatar->GetTarget() != 0) {
      avatar->SetCreatureTarget(0, false, 0);
    } else if (GameInputManager()->GetMode() == 0) {
      MessageServer()->Post(0x64eb18e, 0, 0);
    }
    return true;

  case 0x1c6d8ad: {   // heal cheat
    cCreatureAnimal* creature = avatar;
    if (picked) {
      void* obj = picked->GetObject();
      if (obj) {
        cCreatureAnimal* c = (cCreatureAnimal*)interface_cast_IID(obj, 0x18eb45e);
        if (c)
          creature = c;
      }
    }
    if (creature && creature->mpSpeciesProfile) {
      creature->mCombatant.PartialRepair(20.0f);
      creature->SetHealth(creature->GetHealth() + 20.0f);
    }
    return true;
  }

  case 0x248d179:
    cCreatureModeStrategy::Instance()->NotifyWantToGoToEditor(1);
    return true;

  case 0x274847c: {   // select / deselect UI object
    if (!picked)
      return true;
    void* obj = picked->GetObject();
    if (!obj)
      return true;
    cUIRefCounted* p = interface_cast_Selectable(obj);
    if (!p)
      return true;
    if (g_pSelectedUI.mp == p) {
      cUIRefCounted* old = g_pSelectedUI.mp;
      if (old) {
        g_pSelectedUI.mp = 0;
        old->Release();
      }
    } else {
      g_pSelectedUI.Assign(p);
    }
    return true;
  }

  case 0x2c4bfda: {   // toggle HUD canvas
    bool visible = MainCanvas()->IsVisible();
    MainCanvas()->SetVisible(!visible);
    return true;
  }

  case 0x2c4bfde:
    mbMouseMoved = (value == 0);
    return true;

  case 0x3c7560d:
    avatar->PlayAnimation(0x0004000000000000ULL, kFloatMax, 2, 0, 0, 0);
    SpawnAcknowledgementEffect(0x0004000000000000ULL, 0);
    return true;

  case 0x4fe41c0: {   // SETI zap of the picked creature
    if (!picked)
      return true;
    void* obj = picked->GetObject();
    if (!obj)
      return true;
    cCreatureAnimal* c = (cCreatureAnimal*)interface_cast_IID(obj, 0x18eb45e);
    if (!c || !c->mpSpeciesProfile)
      return true;
    cSPUISpace::KillSetiEffects(0x65f6559d, GetRecorderState());
    cCombatant* combatant = &c->mCombatant;
    combatant->TakeDamage(combatant->GetMaxHitPoints() * 0.25f, (uint32_t)-1, 2, g_SetiDamageDir, 0);
    return true;
  }

  case 0x65fa504:
    ToggleDebugDisplay();
    return true;

  case 0x64d50e0: {   // target the picked creature
    if (!picked)
      return true;
    cCreatureAnimal* c = interface_cast_Animal(picked->GetObject());
    if (!c)
      return true;
    Tutorial()->Select(c);
    avatar->SetCreatureTarget(&c->mCombatant, false, 0);
    avatar->mpBehavior->mSub.Notify(0x100000, kFloatMax, 0);
    return true;
  }

  case 0x51893a3:     // pick a target
    if (PickTarget(avatar))
      avatar->mpBehavior->mSub.Notify(0x100000, kFloatMax, 0);
    return true;

  case 0x13cdf6fa:
    SetHUDHidden(IsHUDHidden() == 0, 1);
    return true;

  case 0x50e6232d: {
    if (!picked)
      return true;
    void* obj = picked->GetObject();
    if (!obj)
      return true;
    cUIRolloverTarget* r = interface_cast_Rollover(obj);
    if (r)
      r->Activate();
    return true;
  }

  case 0x53c4bde7:
    g_bFreeCamera = !g_bFreeCamera;
    if (g_bFreeCamera)
      ToggleAutoRun();
    return true;

  case 0x716b83ff: {  // kill cheat: everything of another kind within 10 m
    char tag;
    for (NearbyIterator it(avatar->mNearbyCreatures, &tag); it.mpCur != it.mpEnd; it.Next()) {
      cCreatureAnimal* c = interface_cast_Animal(((void**)*it.mpCur)[2]);
      if (c && !c->mbDead && !((c->mGeneralFlags >> 8) & 1)) {
        const Vector3& a = avatar->mLoco.GetPosition();
        const Vector3& b = c->mLoco.GetPosition();
        float dx = b.x - a.x, dy = b.y - a.y, dz = b.z - a.z;
        if (100.0f > dz * dz + dy * dy + dx * dx) {
          c->mCombatant.TakeDamage(1000.0f, 0, 2, g_KillDamageDir, 0);
          if (c->mCombatant.GetCombatState() == 2) {
            struct { cCreatureAnimal* killer; cCreatureAnimal* victim; int x; } msg = { avatar, c, 0 };
            cCreatureModeStrategy::spInstance->PostKillMessage(0xd335362c, &msg);
          }
        }
      }
    }
    return true;
  }

  case 0x940666d2:
    CinematicManager()->Stop(0);
    return true;

  case 0x915a6a39: {  // tag every creature within 10 m
    char tag;
    for (NearbyIterator it(avatar->mNearbyCreatures, &tag); it.mpCur != it.mpEnd; it.Next()) {
      cCreatureAnimal* c = interface_cast_Animal(((void**)*it.mpCur)[2]);
      if (c && !c->mbDead && !((c->mGeneralFlags >> 8) & 1)) {
        const Vector3& a = avatar->mLoco.GetPosition();
        const Vector3& b = c->mLoco.GetPosition();
        float dx = b.x - a.x, dy = b.y - a.y, dz = b.z - a.z;
        if (100.0f > dz * dz + dy * dy + dx * dx) {
          c->mGeneralFlags |= 0x80;
          Tutorial()->Tag(3, c->mb28, c);
        }
      }
    }
    EditorLauncher()->Launch(0);
    return true;
  }

  case 0xb0ee272f: {  // spawn a creature of the avatar's species nearby
    NounManager();
    Vector3 pos = PlanetModel()->MakeRandomWorldPosition(avatar->mLoco.GetPosition(), 3.0f, 6.0f);
    cCreatureAnimal* c = NounManager()->CreateCreature(pos, avatar->mpSpeciesProfile, 1, 0, 0, 0);
    if (c) {
      cCreatureAnimal* t = avatar->GetSpeciesTemplate();
      c->m88 = t->m88;
      c->mf0 = t->mf0;
      c->SetupFromTemplate(1);
      c->FinishSetup();
    }
    return true;
  }

  case 0xd34b9713:    // max brain cheat
    avatar->SetCurrentBrainLevel(4);
    g_CheatEventKind = 4;
    cCreatureModeStrategy::NotifyEvent(g_DNAReward[0] + g_DNAReward[1] + g_DNAReward[2] + g_DNAReward[3]);
    return true;

  case 0xd02dcc68: {  // mouse released
    cSPTimer* timer = &mMouseDownTime;
    if (timer->GetElapsedTime() > g_ClickMoveTimeMs && mbMoveOnRelease) {
      cLocomotiveObject* loco = &avatar->mLoco;
      const Vector3& pos = loco->GetPosition();
      Vector3 dir = loco->GetDirection();
      float dist = avatar->IsInWater() ? 4.5f : 2.0f;
      Vector3 target;
      target.x = dir.x * dist + pos.x;
      target.y = pos.y + dir.y * dist;
      target.z = pos.z + dir.z * dist;
      SetAvatarMoveTarget(avatar, target);

      float cosA = Dot3(loco->GetDirection(), loco->GetVelocity());
      cosA = Clamp(cosA, -1.0f, 1.0f);
      float turn = Clamp(acosf(cosA) * 1.4285715f, 0.0f, 1.0f);
      float d = turn * 1.1f + 0.4f;
      loco->RequestMove(MoveGoal(target, d + g_MoveGoalMinDist, d + g_MoveGoalMaxDist));
      if (!avatar->mb137 && !(avatar->mf110 & 0x1000))
        loco->RequestMove(MoveGoal());
      if ((avatar->mpBehavior->mFlags & 0x10801) == 0) {
        avatar->PlayAnimation(0x100000, kFloatMax, 0, 0, 0, 0);
        SpawnAcknowledgementEffect(0x100000, 0);
      }
    } else if (value > 0) {
      avatar->mbB5C = false;
      UpdateAvatarGoal(true, true);
      if (!avatar->mLoco.IsIdle())
        avatar->ReturnToIdle(1);
    }
    g_bShowAvatarGoal = !g_bAutoRunLocked;
    timer->Stop();
    mbMouseMoved = true;
    return true;
  }
  }
  return true;
}

// Body of message 0x51893a3: returns false when nothing was targeted.
static __forceinline bool PickTarget(cCreatureAnimal* avatar)
{
  cCombatant* target = 0;
  cCreatureAnimal* targetAnimal = 0;
  cCreatureAnimal* nearest = 0;
  const Vector3& avatarPos = avatar->mLoco.GetPosition();

  if (GetCurrentGameMode() == 0x1654c10) {
    // Creature game: pick the best enemy in the camera cone.
    float bestScore = kFloatMax;
    float bestForward = kFloatMax;
    cCombatant* bestBehind = 0;
    cCombatant* cur = avatar->GetTarget();
    Vector3 camPos, camRight, camUp, camForward;
    App()->GetRenderer()->GetViewer()->GetCameraLocationInfo(&camPos, &camRight, &camUp, &camForward);
    float curForward;
    if (cur) {
      const Vector3& p = cur->ToSpatialObject()->GetPosition();
      Vector3 d;
      d.x = p.x - camPos.x;
      d.y = p.y - camPos.y;
      d.z = p.z - camPos.z;
      Vector3 n = normalized_safe(d);
      curForward = n.y * camForward.y + n.z * camForward.z + camForward.x * n.x;
    }

    ObjectRefVector objs;
    SpatialQuery()->FindObjects(camPos, g_TargetPickRange, &objs, 1, 0, 0);
    SortTargets(objs.mpBegin, objs.mpEnd, TargetSortCompare(camPos, camRight, g_TargetPickRange));

    int count = (int)(objs.mpEnd - objs.mpBegin);
    int found = 0;
    for (int i = 0; i < count; ++i) {
      if (found >= g_TargetPickMaxCount)
        break;
      cSpatialObject* obj = objs.mpBegin[i];
      if (!obj->GetModel())
        continue;
      if (obj->GetModel()->mf8c > 0.0f)
        continue;
      cCombatant* c = CombatantFromObject(obj);
      if (!IsSelectableTarget(c))
        continue;
      if (c == &avatar->mCombatant)
        continue;
      cGameData* data = c->ToGameData();
      uint32_t myPID = avatar->GetPoliticalID();
      if (data->GetPoliticalID() == myPID)
        continue;
      if (c->GetCombatState() == 2)
        continue;
      if (c->IsInvulnerable())
        continue;
      if (c == cur)
        continue;
      cCreatureAnimal* an = AnimalFromCombatant(c);
      if (an && ((an->mGeneralFlags >> 8) & 1))
        continue;
      ++found;

      const Vector3& p = obj->GetPosition();
      Vector3 d;
      d.x = p.x - camPos.x;
      d.y = p.y - camPos.y;
      d.z = p.z - camPos.z;
      Vector3 n = normalized_safe(d);
      if (cur && cur->ToSpatialObject()->GetModel() && cur->ToSpatialObject()->GetModel()->mf8c == 0.0f) {
        // Cycle: the next target further along the camera axis.
        float fwd = n.x * camForward.x + n.y * camForward.y + n.z * camForward.z;
        if (bestForward > fwd) {
          bestForward = fwd;
          bestBehind = c;
        }
        if (fwd > curForward && bestScore > fwd) {
          target = c;
          bestScore = fwd;
        }
      } else {
        float score = camRight.x * n.x + camRight.y * n.y + camRight.z * n.z;
        if (target == 0 || score > bestScore) {
          target = c;
          bestScore = score;
        }
      }
    }
    if (target == 0) {
      if (bestBehind)
        target = bestBehind;
      else if (cur)
        target = cur;
    }
    if (target)
      targetAnimal = AnimalFromCombatant(target);
  } else {
    // Other modes: nearest creature of another species.
    float bestDist = kFloatMax;
    char tag;
    for (NearbyIterator it(avatar->mNearbyCreatures, &tag); it.mpCur != it.mpEnd; it.Next()) {
      cCreatureAnimal* c = interface_cast_Animal(((void**)*it.mpCur)[2]);
      if (c && !c->mbDead && !((c->mGeneralFlags >> 8) & 1) && c->mpSpeciesProfile != avatar->mpSpeciesProfile) {
        const Vector3& p = c->mLoco.GetPosition();
        float dx = p.x - avatarPos.x, dy = p.y - avatarPos.y, dz = p.z - avatarPos.z;
        float d2 = dx * dx + dz * dz + dy * dy;
        if (nearest == 0 || bestDist > d2) {
          nearest = c;
          bestDist = d2;
        }
      }
    }
    if (!nearest)
      return false;
    target = &nearest->mCombatant;
    targetAnimal = nearest;
  }

  if (!target)
    return false;
  if (target == avatar->GetTarget())
    return false;
  if (targetAnimal)
    Tutorial()->Select(targetAnimal);
  avatar->SetCreatureTarget(target, true, 0);
  if (targetAnimal && GetCurrentGameMode() != 0x1654c10)
    cCreatureModeStrategy::Instance()->SignalCreatureEvent(0x533535db);
  return true;
}

} // namespace SP

