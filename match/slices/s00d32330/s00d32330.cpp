// @ 0x00d32330  SP::cCreatureModeInputStrategy::UpdateAvatarGoalKeyboard   (PDB caller-scored name)
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (cvtsi2ss + float-reassociated sums need /fp:fast; no /EHsc: the navigation-goal locals get no unwind frame).
//
// Keyboard (WASD) steering of the creature-stage avatar.  Every frame, while the
// window has focus and WASD goals are allowed, the move keys (1-6), auto-run and
// mouse-at-screen-edge turning build a desired direction from the camera's
// forward/right vectors; it is blended into the persistent keyboard goal
// direction, projected onto the planet tangent plane at the avatar, rotated
// around the local up axis by the turn keys, and handed to UpdateAvatarGoal.
// When no key is held any more, the avatar gets one last short move request
// along its velocity (clamped to 50 m) and the goal direction decays.
#include "types.h"
#include <math.h>

namespace SP {

#define VFUNC(obj, off) ((*(void***)(obj))[(off) / 4])

struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
  void Set(const Vector3& v) { x = v.x; y = v.y; z = v.z; }
  Vector3 operator-() const { return Vector3(-x, -y, -z); }
  Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
  Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
  Vector3 operator*(float f) const { return Vector3(x * f, y * f, z * f); }
  friend Vector3 operator*(float f, const Vector3& v) { return Vector3(v.x * f, v.y * f, v.z * f); }
  Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
  Vector3& operator*=(float f) { x *= f; y *= f; z *= f; return *this; }
};
inline float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

struct Quaternion {
  float x, y, z, w;
  Quaternion() {}
  Quaternion(const Quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
};

Vector3 Normalize(const Vector3& v);                           // 0x00436ce0
Vector3 normalized_safe(const Vector3& v);                     // 0x00449c20
Quaternion AxisAngle(const Vector3& axis, float angle);        // 0x0059b060
Quaternion Normalize(const Quaternion& q);                     // 0x00799320
Vector3 Rotate(const Vector3& v, const Quaternion& q);         // 0x0059aed0

// ---------------------------------------------------------------------------
// Locomotion requests (0x70 bytes; dtor 0x007a41a0).
// ---------------------------------------------------------------------------
struct cLocomotionRequest {
  uint32_t mData[0x1c];
  cLocomotionRequest();                                        // 0x00ac9850
  ~cLocomotionRequest();                                       // 0x007a41a0
};
struct tNavigationGoal : cLocomotionRequest {
  tNavigationGoal(const Vector3& target, const Vector3& dir, float minDist, float maxDist);   // 0x00ad2a50
};

// Retail cLocomotiveObject vtable (slots from ModAPI cSpatialObject / cLocomotiveObject).
class cLocomotiveObject {
public:
  virtual void vf00();
  virtual void vf04();
  virtual void vf08();
  virtual void vf0c();
  virtual void vf10();
  virtual void vf14();
  virtual void vf18();
  virtual void vf1c();
  virtual void vf20();
  virtual void vf24();
  virtual void vf28();
  virtual const Vector3& GetPosition();              // 0x2c
  virtual void vf30();
  virtual void vf34();
  virtual void vf38();
  virtual void vf3c();
  virtual void vf40();
  virtual void vf44();
  virtual void vf48();
  virtual void vf4c();
  virtual void vf50();
  virtual void vf54();
  virtual void vf58();
  virtual Vector3 GetDirection();                     // 0x5c
  virtual void vf60();
  virtual void vf64();
  virtual void vf68();
  virtual void vf6c();
  virtual void vf70();
  virtual void vf74();
  virtual void vf78();
  virtual void vf7c();
  virtual void vf80();
  virtual void vf84();
  virtual void vf88();
  virtual void vf8c();
  virtual void vf90();
  virtual void vf94();
  virtual void vf98();
  virtual void vf9c();
  virtual void vfa0();
  virtual void vfa4();
  virtual void vfa8();
  virtual void vfac();
  virtual void vfb0();
  virtual void vfb4();
  virtual void vfb8();
  virtual void vfbc();
  virtual void vfc0();
  virtual void vfc4();
  virtual float GetDesiredSpeed();                    // 0xc8
  virtual float GetStandardSpeed();                   // 0xcc
  virtual void vfd0();
  virtual void vfd4();
  virtual void vfd8();
  virtual void RequestMove(const cLocomotionRequest& request);   // 0xdc
  const Vector3& GetVelocity();                       // 0x00d20610
};

struct cBehaviorTreeData {
  char pad[0x1c8];
  uint64_t mFlags;   // +0x1c8
};

struct cCombatant;

struct cCreatureAnimal {
  void SetCreatureTarget(cCombatant* target, bool b, int intention) {
    ((void(__thiscall*)(void*, cCombatant*, bool, int))VFUNC(this, 0x84))(this, target, b, intention);
  }
  cCreatureAnimal* GetTargetAsCreature();                                         // 0x00c0ee70
  void PlayAnimation(uint64_t flags, float range, int a, int b, int c, int d);    // 0x00c03190

  char pad0[0xc0];
  cLocomotiveObject mLoco;            // +0xc0
  char padc4[0x110 - 0xc4];
  uint32_t mf110;                     // +0x110
  char pad114[0x137 - 0x114];
  bool mb137;                         // +0x137
  char pad138[0xb4c - 0x138];
  cBehaviorTreeData* mpBehavior;      // +0xb4c
  char padb50[0xb5c - 0xb50];
  bool mbB5C;                         // +0xb5c
  bool mbB5D;
  bool mbDead;                        // +0xb5e
};

struct cGameNounManager { cCreatureAnimal* GetAvatar(); };   // 0x00b1fdb0
struct cGameInputManager {
  bool IsKeyDown(int key) { return ((bool(__thiscall*)(void*, int))VFUNC(this, 0x18))(this, key); }
};
struct cConfigManager {
  void* GetProperty(uint32_t id) { return ((void*(__thiscall*)(void*, uint32_t))VFUNC(this, 0x30))(this, id); }
};
struct cWindowInfo {
  int mWidth;        // +0x00
  int mHeight;       // +0x04
  int mMouseX;       // +0x08
  int mMouseY;       // +0x0c
  bool mbActive;     // +0x10
};
struct cRenderWindow {
  const cWindowInfo* GetInfo() { return ((const cWindowInfo*(__thiscall*)(void*))VFUNC(this, 0x1c))(this); }
};

class cCreatureModeStrategy {
public:
  static cCreatureModeStrategy* Instance();   // 0x00d38840
};

cGameNounManager* NounManager();              // 0x00b3d300
cGameInputManager* GameInputManager();        // 0x00b3d250
cConfigManager* ConfigManager();              // 0x0067dd30
cRenderWindow* RenderWindow();                // 0x0067dd50
enum { kGameSpace = 0x01654c05, kScenarioMode = 0x01654c10 };   // game mode ids (relocated in the original)
uint32_t GetCurrentGameMode();                // 0x00b5b800
bool IsWindowFocused();                       // 0x00805180
bool IsModifierKeyDown(int key);              // 0x008d2fb0
void GetCameraMoveVectors(Vector3* forward, Vector3* right);   // 0x00d2ee70
bool IsStrafeLeftDown();                      // 0x00d2eab0
bool IsStrafeRightDown();                     // 0x00d2eaf0
void SetAvatarMoveTarget(cCreatureAnimal* avatar, const Vector3& target);   // 0x00d2ec50
namespace { void SpawnAcknowledgementEffect(uint64_t flags, int a); }       // 0x00d2f940

extern bool g_bMouseCaptured;            // 0x0169e22c
extern bool g_bAutoRun;                  // 0x0169e37c
extern bool g_bLastAutoRun;              // 0x0169e37d
extern bool g_bKeyboardTurning;          // 0x0169e37f
extern bool g_bKeyboardMoving;           // 0x0169e380
extern char g_KeyboardGoalActive;        // 0x0169e381
extern Vector3 g_KeyboardGoalDir;        // 0x0169e388
extern float g_TurnSpeed;                // 0x01582bb4
extern float g_TurnSpeedSpace;           // 0x01582bb8
extern float g_TurnSpeedAtRest;          // 0x01582bc4
extern float g_TurnSlowdownFactor;       // 0x01582bc0
extern float g_StopLookAhead;            // 0x01582bbc
extern float g_StopMaxDistance;          // 0x01582ba8
extern float g_MoveGoalMinDist;          // 0x01582bac
extern float g_MoveGoalMaxDist;          // 0x01582bb0

const float kFloatMax = 3.4028234663852886e+38f;
const float kDegToRad = 0.017453292f;
const float kGoalBlend = 0.6f;

// 0x00d2f2a0: same-TU static helper (the avatar arrives in eax).  Turn speed
// in scenario mode: g_TurnSpeedAtRest when standing, easing exponentially down
// to g_TurnSpeed once the avatar moves at a quarter of its top speed.
static float GetScenarioTurnSpeed(cCreatureAnimal* avatar)
{
  cLocomotiveObject* loco = &avatar->mLoco;
  const Vector3& v = loco->GetVelocity();
  float speed = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
  float standard = loco->GetStandardSpeed();
  float desired = loco->GetDesiredSpeed();
  const float& top = standard > desired ? standard : desired;
  float threshold = fabsf(top) * g_TurnSlowdownFactor;
  if (speed > threshold)
    return g_TurnSpeed;
  float ratio = g_TurnSpeedAtRest / g_TurnSpeed;
  float k = (1.0f - ratio) / (expf(threshold) - 1.0f);
  return g_TurnSpeed * ((ratio - k) + k * expf(speed));
}

class cCreatureModeInputStrategy {
public:
  void UpdateAvatarGoalKeyboard();
  void UpdateAvatarGoal(bool a, bool b);       // 0x00d31a70

  char pad0[0xc0];
  bool mbUpdateAvatarGoals;    // +0xc0
  bool mbAllowWASDGoals;       // +0xc1
};

// @ 0x00d32330
void cCreatureModeInputStrategy::UpdateAvatarGoalKeyboard()
{
  cCreatureAnimal* avatar = NounManager()->GetAvatar();
  cCreatureModeStrategy::Instance();
  cGameInputManager* input = GameInputManager();
  if (!avatar || avatar->mbDead || !mbUpdateAvatarGoals)
    return;

  // Turning when the mouse touches the left or right screen edge.
  const cWindowInfo* window = RenderWindow()->GetInfo();
  int mouseX = window->mMouseX;
  int halfWidth = window->mWidth / 2;
  float edge = (float)(mouseX > halfWidth ? window->mWidth - mouseX : mouseX) * 0.5f;
  bool active = g_bMouseCaptured || window->mbActive;
  bool edgeTurn;
  if (ConfigManager()->GetProperty(0x636ec26) && active && edge <= 1.0f && edge >= 0.0f &&
      !input->IsKeyDown(0x16) && !input->IsKeyDown(0x20))
    edgeTurn = true;
  else
    edgeTurn = false;

  Vector3 forward, right;
  GetCameraMoveVectors(&forward, &right);

  if (IsWindowFocused() && mbAllowWASDGoals &&
      (input->IsKeyDown(1) || input->IsKeyDown(2) || input->IsKeyDown(3) || input->IsKeyDown(4) ||
       input->IsKeyDown(5) || input->IsKeyDown(6) || edgeTurn || g_bAutoRun)) {
    avatar->mbB5C = false;
    if (avatar->GetTargetAsCreature())
      avatar->GetTargetAsCreature();
    g_bKeyboardTurning = false;
    g_bKeyboardMoving = false;

    Vector3 move(0.0f, 0.0f, 0.0f);
    if (input->IsKeyDown(1)) {
      move.Set(forward);
      g_bKeyboardMoving = true;
      g_bAutoRun = false;
    }
    if (input->IsKeyDown(2)) {
      move += -forward;
      g_bKeyboardMoving = true;
      g_bAutoRun = false;
    }
    if (IsStrafeLeftDown()) {
      move += -right;
      g_bKeyboardMoving = true;
    }
    if (IsStrafeRightDown()) {
      move += right;
      g_bKeyboardMoving = true;
    }
    if (g_bAutoRun) {
      move += forward;
      g_bKeyboardMoving = true;
    }
    if (g_bKeyboardMoving && move.x * move.x + move.y * move.y + move.z * move.z > 1e-6) {
      move.Set(g_KeyboardGoalDir * kGoalBlend + Normalize(move) * (1.0f - kGoalBlend));
      g_KeyboardGoalDir = Normalize(move);
    } else {
      g_bKeyboardMoving = false;
      g_KeyboardGoalDir = forward;
    }

    float angle = 0.0f;
    float turnSpeed = g_TurnSpeed;
    uint32_t mode = GetCurrentGameMode();
    switch (mode) {
    case kGameSpace:
      turnSpeed = g_TurnSpeedSpace;
      break;
    case kScenarioMode:
      turnSpeed = GetScenarioTurnSpeed(avatar);
      break;
    }

    if (!IsModifierKeyDown(0x3ea) && GameInputManager()->IsKeyDown(3)) {
      angle = turnSpeed * kDegToRad;
      g_bKeyboardTurning = true;
    }
    if (!IsModifierKeyDown(0x3ea) && GameInputManager()->IsKeyDown(4)) {
      angle -= turnSpeed * kDegToRad;
      g_bKeyboardTurning = true;
    }
    if (edgeTurn) {
      float turn = turnSpeed * (mouseX > halfWidth ? -1.0f : 1.0f);
      if (turn != 0.0f) {
        angle += turn * kDegToRad;
        g_bKeyboardTurning = true;
      }
    }

    bool strafing = IsStrafeLeftDown() || IsStrafeRightDown();
    if (g_bKeyboardTurning && !strafing) {
      Vector3 up = Normalize(avatar->mLoco.GetPosition());
      g_KeyboardGoalDir = Normalize(g_KeyboardGoalDir - up * Dot(up, g_KeyboardGoalDir));
      Quaternion q = Normalize(AxisAngle(up, angle));
      g_KeyboardGoalDir.Set(Rotate(g_KeyboardGoalDir, q));
    } else {
      Vector3 up = Normalize(avatar->mLoco.GetPosition());
      g_KeyboardGoalDir = Normalize(g_KeyboardGoalDir - up * Dot(up, g_KeyboardGoalDir));
      g_bKeyboardTurning = false;
    }
    g_KeyboardGoalDir = Normalize(g_KeyboardGoalDir);
    g_KeyboardGoalActive = 1;
    UpdateAvatarGoal(false, true);

    if (avatar->GetTargetAsCreature() && avatar->GetTargetAsCreature()->mbDead)
      avatar->SetCreatureTarget(0, false, 0);
  } else {
    if (g_KeyboardGoalActive == 1 && !g_bLastAutoRun) {
      // Keys released: one last short move along the current velocity.
      cLocomotiveObject* loco = &avatar->mLoco;
      Vector3 target = loco->GetPosition();
      target += g_StopLookAhead * normalized_safe(loco->GetVelocity());
      SetAvatarMoveTarget(avatar, target);

      const Vector3& pos = loco->GetPosition();
      Vector3 delta = target - pos;
      float dist = sqrtf(Dot(delta, delta));
      if (dist > g_StopMaxDistance) {
        target = delta * (g_StopMaxDistance / dist) + pos;
        SetAvatarMoveTarget(avatar, target);
      }

      tNavigationGoal goal(target, loco->GetDirection(), g_MoveGoalMinDist, g_MoveGoalMaxDist);
      bool autoRun = g_bAutoRun;
      loco->RequestMove(goal);
      if ((avatar->mpBehavior->mFlags & 0x10801) == 0) {
        avatar->PlayAnimation(0x100000, kFloatMax, 1, 0, 0, 0);
        SpawnAcknowledgementEffect(0x100000, 0);
      }
      g_bAutoRun = autoRun;
      if (!avatar->mb137 && !(avatar->mf110 & 0x1000))
        loco->RequestMove(cLocomotionRequest());
    }
    g_KeyboardGoalDir.Set(g_KeyboardGoalDir * 0.4f);
    g_KeyboardGoalActive = 0;
  }
  g_bLastAutoRun = g_bAutoRun;
}

}  // namespace SP
