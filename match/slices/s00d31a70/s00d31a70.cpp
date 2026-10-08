// @ 0x00d31a70  SP::cCreatureModeInputStrategy::UpdateAvatarGoal
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (same as the neighbouring UpdateAvatarGoalKeyboard)
//
// Works out where the creature-stage avatar should walk and sends it there.
//  - keyboard mode (a == false): the goal starts at the avatar's position and is pushed
//    2.5 m along the camera's forward/right vectors for each held move key.
//  - mouse mode (a == true): the goal is the clicked ground point (the pick position source,
//    refined by a ray cast against the world when the click hits a game-data object).
// If the goal differs from the "no goal" sentinel the avatar is clamped to a maximum stride,
// either stopped (request move + ack effect, returns true) when it is already there, or sent
// on with MoveToPoint(AndFacing)AtSpeed.  Returns whether a goal was issued.
#include "types.h"
#include <math.h>

namespace SP {

#define VFUNC(obj, off) ((*(void***)(obj))[(off) / 4])

struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

Vector3* __cdecl normalized_safe(Vector3* out, const Vector3* in);   // 0x00449c20

struct cLocomotionRequest {
  uint32_t mData[0x1c];
  cLocomotionRequest();                                        // 0x00ac9850
  ~cLocomotionRequest();                                       // 0x007a41a0
};

class cLocomotiveObject {
public:
  virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0c();
  virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1c();
  virtual void vf20(); virtual void vf24(); virtual void vf28();
  virtual const Vector3& GetPosition();              // 0x2c
  virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3c();
  virtual void vf40(); virtual void vf44(); virtual void vf48(); virtual void vf4c();
  virtual void vf50(); virtual void vf54(); virtual void vf58(); virtual void vf5c();
  virtual void vf60(); virtual void vf64(); virtual void vf68(); virtual void vf6c();
  virtual void vf70();
  virtual float GetRadius();                         // 0x74
  virtual void vf78(); virtual void vf7c(); virtual void vf80(); virtual void vf84();
  virtual void vf88(); virtual void vf8c(); virtual void vf90(); virtual void vf94();
  virtual void vf98(); virtual void vf9c(); virtual void vfa0(); virtual void vfa4();
  virtual void vfa8(); virtual void vfac(); virtual void vfb0(); virtual void vfb4();
  virtual void vfb8(); virtual void vfbc(); virtual void vfc0(); virtual void vfc4();
  virtual void vfc8(); virtual void vfcc(); virtual void vfd0(); virtual void vfd4();
  virtual void vfd8();
  virtual void RequestMove(const cLocomotionRequest& request);   // 0xdc
};

struct cBehaviorTreeData {
  char pad[0x1c8];
  uint64_t mFlags;   // +0x1c8
};

struct cCreatureAnimal {
  void PlayAnimation(uint64_t flags, float range, int a, int b, int c, int d);    // 0x00c03190
  void MoveToPointAndFacingAtSpeed(int mode, const Vector3* p, const Vector3* d, float s0, float s1);  // 0x00c1c5c0
  void MoveToPointFacing(int mode, const Vector3* p, const Vector3* d, float s0, float s1);            // 0x00c1c080

  char pad0[0xc0];
  cLocomotiveObject mLoco;            // +0xc0
  char padc4[0xb4c - 0xc4];
  cBehaviorTreeData* mpBehavior;      // +0xb4c
  char padb50[0xb5e - 0xb50];
  bool mbDead;                        // +0xb5e
};

struct cGameNounManager { cCreatureAnimal* GetAvatar(); };   // 0x00b1fdb0
struct cGameInputManager {
  bool IsKeyDown(int key) { return ((bool(__thiscall*)(void*, int))VFUNC(this, 0x18))(this, key); }
};

// position source (0x00b3d240): +0x3c = pick position, +0x30 = picked object
struct cPickedThing {
  void* Cast(uint32_t id) { return ((void*(__thiscall*)(void*, uint32_t))VFUNC(this, 0x0c))(this, id); }
};
struct cPosSource {
  Vector3* GetPickPosition(Vector3* out, int n) { return ((Vector3*(__thiscall*)(void*, Vector3*, int))VFUNC(this, 0x3c))(this, out, n); }
  cPickedThing* GetPicked() { return ((cPickedThing*(__thiscall*)(void*))VFUNC(this, 0x30))(this); }
};
struct cViewer {
  void GetCameraRayPoints(Vector3* origin, Vector3* end);   // 0x007c46f0
};
struct cRenderThing { cViewer* GetViewer() { return ((cViewer*(__thiscall*)(void*))VFUNC(this, 0x1c))(this); } };
struct cAppObj { cRenderThing* GetRender() { return ((cRenderThing*(__thiscall*)(void*))VFUNC(this, 0x50))(this); } };

struct cRayQuery {              // 0x16 bytes as built on the stack
  uint32_t a, b, c, d, e;
  uint8_t mode, flag;
};
struct cRayCaster {             // vtable slot 0x44: cast a ray, return fraction of the segment hit
  bool Cast(Vector3* p0, Vector3* p1, void* ignore, float* t, cRayQuery* q) {
    return ((bool(__thiscall*)(void*, Vector3*, Vector3*, void*, float*, cRayQuery*))VFUNC(this, 0x44))(this, p0, p1, ignore, t, q);
  }
};
struct cRaySubobject {          // subobject at +0x34 of the 0x52aa6122 component
  cRayCaster* GetCaster() { return ((cRayCaster*(__thiscall*)(void*))VFUNC(this, 0xb0))(this); }
  void* GetIgnore() { return ((void*(__thiscall*)(void*))VFUNC(this, 0xac))(this); }
};
struct cRayComponent { char pad[0x34]; cRaySubobject sub; };

struct cSPTimer { uint64_t GetElapsedTime(); };   // 0x00bc3190

cGameNounManager* NounManager();              // 0x00b3d300
cGameInputManager* GameInputManager();        // 0x00b3d250
cPosSource* PosSource();                      // 0x00b3d240
cAppObj* App();                               // 0x0067dd10
void* __cdecl interface_cast_IID(void* obj, uint32_t iid);   // 0x00ac80d0
void GetCameraMoveVectors(Vector3* forward, Vector3* right);   // 0x00d2ee70
bool IsStrafeLeftDown();                      // 0x00d2eab0
bool IsStrafeRightDown();                     // 0x00d2eaf0
void SetAvatarMoveTarget(cCreatureAnimal* avatar, const Vector3* target);   // 0x00d2ec50
namespace { void SpawnAcknowledgementEffect(uint64_t flags, int a); }       // 0x00d2f940

extern bool g_bAutoRun;                  // 0x0169e37c
extern const Vector3 g_NoGoal;           // 0x0169e17c
extern float g_StopMaxDistance;          // 0x01582ba8
extern float g_MoveGoalMinDist;          // 0x01582bac
extern float g_MoveGoalMaxDist;          // 0x01582bb0
extern uint32_t g_ClickMoveTimeMs;       // 0x01582bc8
extern float g_StopRadiusCap;            // 0x01582bd0
extern float g_MaxRayLength;             // 0x013ec5b4 (1000.0)
extern float g_StepLength;               // 0x01486114 (2.5)
extern float g_HalfFactor;               // 0x01471064 (0.5)
const float kFloatMax = 3.4028234663852886e+38f;

class cCreatureModeInputStrategy {
public:
  bool UpdateAvatarGoal(bool a, bool b);       // 0x00d31a70
  void SpawnMovementGoalEffect(const Vector3* goal);   // 0x00d30fb0

  char pad0[0xa0];
  cSPTimer mMouseDownTimer;    // +0xa0
  char pada4[0xc0 - 0xa4];
  bool mbUpdateAvatarGoals;    // +0xc0
};

// @ 0x00d31a70
bool cCreatureModeInputStrategy::UpdateAvatarGoal(bool mouseMode, bool spawnEffect)
{
  cCreatureAnimal* avatar = NounManager()->GetAvatar();
  Vector3 forward, right;
  GetCameraMoveVectors(&forward, &right);

  bool issued = false;
  if (avatar->mbDead || !mbUpdateAvatarGoals)
    return issued;

  Vector3 goal = g_NoGoal;
  bool applyMoveTarget = true;
  bool moveKeys = false;

  if (!mouseMode) {
    goal = avatar->mLoco.GetPosition();
    cGameInputManager* input = GameInputManager();
    if (IsStrafeLeftDown() || IsStrafeRightDown() ||
        (input->IsKeyDown(2) && !input->IsKeyDown(1)))
      moveKeys = true;
    else
      moveKeys = false;
    if (IsStrafeLeftDown()) {
      goal.x = goal.x - right.x * g_StepLength;
      goal.y = goal.y - right.y * g_StepLength;
      goal.z = goal.z - right.z * g_StepLength;
    }
    if (IsStrafeRightDown()) {
      goal.x = right.x * g_StepLength + goal.x;
      goal.y = right.y * g_StepLength + goal.y;
      goal.z = right.z * g_StepLength + goal.z;
    }
    if (GameInputManager()->IsKeyDown(2)) {
      goal.x = goal.x - forward.x * g_StepLength;
      goal.y = goal.y - forward.y * g_StepLength;
      goal.z = goal.z - forward.z * g_StepLength;
    }
    if (GameInputManager()->IsKeyDown(1) || g_bAutoRun) {
      goal.x = forward.x * g_StepLength + goal.x;
      goal.y = forward.y * g_StepLength + goal.y;
      goal.z = forward.z * g_StepLength + goal.z;
    }
  } else {
    Vector3 tmp;
    goal = *PosSource()->GetPickPosition(&tmp, 1);

    cPickedThing* picked = PosSource()->GetPicked();
    if (picked) {
      cPickedThing* obj = (cPickedThing*)picked->Cast(0x17f243b);
      if (obj && ((uint32_t(__thiscall*)(void*))VFUNC(obj, 0x20))(obj) == 0x52aa6122) {
        cRayComponent* comp = (cRayComponent*)interface_cast_IID(obj, 0x52aa6122);
        cRayCaster* caster = comp->sub.GetCaster();
        void* ignore = comp->sub.GetIgnore();
        if (caster && ignore) {
          float t = 0.0f;
          Vector3 origin, end;
          App()->GetRender()->GetViewer()->GetCameraRayPoints(&origin, &end);
          Vector3 delta(end.x - origin.x, end.y - origin.y, end.z - origin.z);
          float len = sqrtf((delta.z * delta.z + delta.y * delta.y) + delta.x * delta.x);
          if (len > g_MaxRayLength) {
            float f = g_MaxRayLength / len;
            end.x = delta.x * f + origin.x;
            end.y = delta.y * f + origin.y;
            end.z = delta.z * f + origin.z;
          }
          cRayQuery q;
          q.a = q.b = q.c = q.d = q.e = 0;
          q.mode = 3;
          q.flag = 1;
          if (caster->Cast(&origin, &end, ignore, &t, &q)) {
            goal.x = (end.x - origin.x) * t + origin.x;
            goal.y = (end.y - origin.y) * t + origin.y;
            goal.z = (end.z - origin.z) * t + origin.z;
            applyMoveTarget = false;
          }
        }
      }
    }
    const Vector3& apos = avatar->mLoco.GetPosition();
    float dx = goal.x - apos.x, dy = goal.y - apos.y, dz = goal.z - apos.z;
    float dist = sqrtf((dz * dz + dy * dy) + dx * dx);
    float r = avatar->mLoco.GetRadius();
    if (dist < r * g_HalfFactor)
      return false;
  }

  if (goal.x != g_NoGoal.x || goal.y != g_NoGoal.y || goal.z != g_NoGoal.z) {
    Vector3 pos = avatar->mLoco.GetPosition();
    Vector3 delta(goal.x - pos.x, goal.y - pos.y, goal.z - pos.z);
    Vector3 dir = delta;
    float len = sqrtf(delta.x * delta.x + (delta.y * delta.y + delta.z * delta.z));
    if (len > g_StopMaxDistance) {
      float f = g_StopMaxDistance / len;
      goal.x = delta.x * f + pos.x;
      goal.y = delta.y * f + pos.y;
      goal.z = delta.z * f + pos.z;
      pos = goal;
    } else {
      float speed = avatar->mLoco.GetRadius();
      const float* m = &g_StopRadiusCap;
      if (!(speed > g_StopRadiusCap))
        m = &speed;
      if (len < *m) {
        cLocomotionRequest req;
        avatar->mLoco.RequestMove(req);
        if ((avatar->mpBehavior->mFlags & 0x10801) == 0) {
          avatar->PlayAnimation(0x100000, kFloatMax, 0, 0, 0, 0);
          SpawnAcknowledgementEffect(0x100000, 0);
        }
        return true;
      }
      if (mMouseDownTimer.GetElapsedTime() > (uint64_t)g_ClickMoveTimeMs) {
        float speed2 = avatar->mLoco.GetRadius();
        const float* m2 = &len;
        if (!(len > speed2))
          m2 = &speed2;
        Vector3 n;
        Vector3* nd = normalized_safe(&n, &dir);
        goal.x = nd->x * *m2 + pos.x;
        goal.y = nd->y * *m2 + pos.y;
        goal.z = nd->z * *m2 + pos.z;
      }
    }
    if (applyMoveTarget)
      SetAvatarMoveTarget(avatar, &goal);

    bool newAutoRun = g_bAutoRun && !mouseMode;
    if (!mouseMode && moveKeys) {
      Vector3 face = forward;
      avatar->MoveToPointFacing(2, &goal, &face, g_MoveGoalMinDist, g_MoveGoalMaxDist);
    } else {
      Vector3 face;
      normalized_safe(&face, &dir);
      avatar->MoveToPointAndFacingAtSpeed(2, &goal, &face, g_MoveGoalMinDist, g_MoveGoalMaxDist);
    }
    if ((avatar->mpBehavior->mFlags & 0x10801) == 0) {
      avatar->PlayAnimation(0x100000, kFloatMax, 1, 0, 0, 0);
      SpawnAcknowledgementEffect(0x100000, 0);
    }
    g_bAutoRun = newAutoRun;
    issued = true;
  }
  if (mouseMode && issued && spawnEffect)
    SpawnMovementGoalEffect(&goal);
  return issued;
}

}  // namespace SP
