// Slice s00b0f270 (bfs2 #46).
//
// SP::cTerrainCameraController — camera-script/scratch-var setup, mouse/keyboard
// input handling and small math helpers, plus two small float "spring" structs.
// Flags: /O2 /arch:SSE (SSE scalar math, x87 for float returns).
#include "types.h"

typedef unsigned int u32;
typedef unsigned char u8;

extern "C" void* op_new(u32 size, const char* name, int a, int b, const char* file, int line);
extern "C" void op_del(void* p);

typedef void* (__thiscall *tc0_t)(void*);
typedef void* (__thiscall *tc1_t)(void*, int);
static inline void* vt0(void* p, int slot) { return ((tc0_t*)(*(void***)p))[slot](p); }
static inline void* vt1(void* p, int slot, int a) { return ((tc1_t*)(*(void***)p))[slot](p, a); }

// external constants / globals
extern const float g_zero;      // 0x13eb1bc = 0.0f
extern const float g_one;       // 0x1485720 = 1.0f
extern const float g_pi;        // 0x1567dc8
extern float g_edgeX;           // 0x167bc14
extern float g_edgeY;           // 0x167bc18
extern float g_kClamp;          // 0x167bd10
extern u8    g_flagA;           // 0x167bd5d
extern u8    g_flagB;           // 0x167bd5c

extern float acosf(float);

void* FUN_0067dd50();                 // 0x67dd50
void  VarMapSetVar(void* map, const char* name, float v);  // 0x7f25c0
float VarMapGetVar(void* map, const char* name);           // 0x7f2590
void  VarMapFlush(void* map);                              // 0x7f2500
void* SP_GameInputManager();          // 0xb3d250
void* FUN_0067cab0(int id);           // 0x67cab0
struct CCursorAttachmentLayout { void IsSomething(); void SetEnabled(bool); };
void  FUN_00f4f530(void* p, float v); // 0xf4f530
void  FUN_00804f10(float, float);     // 0x804f10

// ---------------------------------------------------------------------------
namespace SP {

struct cTerrainCameraController {
  char pad00[0x11];
  u8   mb11;                                // +0x11
  char pad12[0x54 - 0x12];
  float m54, m58, m5c;                      // +0x54..0x5c
  char pad60[0x6c - 0x60];
  float m6c, m70, m74;                      // +0x6c..0x74
  char pad78[0x114 - 0x78];
  float m114;
  char pad118[0x120 - 0x118];
  u8   mb120;
  char pad121[0x12c - 0x121];
  float m12c, m130, m134, m138;
  char pad13c[0x144 - 0x13c];
  u8   mb144, mb145;
  char pad146[0x150 - 0x146];
  float m150, m154, m158, m15c, m160, m164;
  char pad168[0x169 - 0x168];
  u8   mb169;
  char pad16a[0x274 - 0x16a];
  float m274, m278, m27c, m280, m284, m288, m28c, m290;
  char pad294[0x298 - 0x294];
  float m298, m29c;
  char pad2a0[0x2ac - 0x2a0];
  float m2ac, m2b0;
  char pad2b4[0x2b8 - 0x2b4];
  float m2b8, m2bc, m2c0, m2c4, m2c8;
  char pad2cc[0x318 - 0x2cc];
  u8   mb318, mb319;
  char pad31a[0x31c - 0x31a];
  char mInput[0x2c];                        // +0x31c
  float m348, m34c;
  char pad350[0x368 - 0x350];
  float m368, m36c, m370, m374, m378, m37c;
  char pad380[0x388 - 0x380];
  float m388, m38c;

  void RunCameraScript(int, int, int, int, int);        // 0x00b0f270
  void SetFloats5(float, float, float, float, float);   // 0x00b0f720
  void ClampSpread();                                   // 0x00b0f770
  float InterpByAngle();                                // 0x00b0f880
  void SetToggle(int);                                  // 0x00b0f950
  bool KeysHeld();                                      // 0x00b0f9a0
  bool HandleMouse(float, float, int);                  // 0x00b0fe90
};

// small 1-float spring/smoother
struct Spring1f {
  u8  mb0, mb1;
  char pad2[2];
  float m4, m8;
  float m0c, m10, m14, m18, m1c, m20;
  float m24, m28, m2c;
  float m30, m34, m38;
  float m3c, m40, m44, m48, m4c, m50;

  void Set(float v, bool force);          // 0x00b0fa70
  void Reset(float v);                    // 0x00b0fbe0
};

}  // namespace SP

using SP::cTerrainCameraController;
using SP::Spring1f;

// @ 0x00b0f720
void cTerrainCameraController::SetFloats5(float a, float b, float c, float d, float e) {
  m278 = a;
  m27c = b;
  m280 = c;
  m284 = d;
  m288 = e;
}

// @ 0x00b0f770
void cTerrainCameraController::ClampSpread() {
  float a = m154, b = m15c, c = m28c;
  float mn = a < b ? a : b;
  if (c < mn) mn = c;
  float K = g_kClamp;
  if (mn > K) {
    m154 -= K;
    m15c -= K;
    m150 -= K;
    m158 -= K;
    m28c -= K;
    return;
  }
  float mx = a > b ? a : b;
  if (c > mx) mx = c;
  if (mx < -K) {
    m154 += K;
    m15c += K;
    m150 += K;
    m158 += K;
    m28c += K;
  }
}

// @ 0x00b0f880
float cTerrainCameraController::InterpByAngle() {
  float dot = m54 * m6c + m58 * m70 + m5c * m74;
  if (dot < g_zero) dot = g_zero;
  if (dot > g_one) dot = g_one;
  float ang = acosf(dot) / g_pi;
  if (ang < g_zero) ang = g_zero;
  if (ang > g_one) ang = g_one;
  return (m378 - m374) * ang + m374;
}

// @ 0x00b0f950
void cTerrainCameraController::SetToggle(int b) {
  if (mb11 != (u8)b) {
    if ((u8)b) {
      m388 = m348;
      m38c = m34c;
      ((CCursorAttachmentLayout*)FUN_0067cab0(0x6805d23))->IsSomething();
    }
    ((CCursorAttachmentLayout*)FUN_0067cab0(b))->SetEnabled(b != 0);
  }
  mb11 = (u8)b;
}

// @ 0x00b0f9a0
bool cTerrainCameraController::KeysHeld() {
  void* im = SP_GameInputManager();
  if (mb11 == 0 && mb319 != 0) {
    if (vt1(im, 6, 1)) return true;
    if (vt1(im, 6, 2)) return true;
    if (vt1(im, 6, 3)) return true;
    if (vt1(im, 6, 4)) return true;
    if (vt1(im, 6, 7)) return true;
    if (vt1(im, 6, 8)) return true;
    if (vt1(im, 6, 9)) return true;
    if (vt1(im, 6, 0x10)) return true;
    if (vt1(im, 6, 0x11)) return true;
    if (vt1(im, 6, 0x12)) return true;
    return false;
  }
  return true;
}

// @ 0x00b0fa70
void Spring1f::Set(float v, bool force) {
  if (force) {
    m18 = v;
    m14 = v;
    m10 = v;
    m0c = v;
    m1c = v * 0.0f;
    m20 = v * 0.0f;
    mb0 = 0;
    mb1 = 0;
    return;
  }
  if (v != m18) {
    m0c = m10;
    m18 = v;
    mb0 = 1;
  }
}

// @ 0x00b0fbe0
void Spring1f::Reset(float v) {
  m8 = v;
  m48 = m48 * 0.0f;
  m4c = m4c * 0.0f;
  m50 = m50 * 0.0f;
  m24 = m30;
  m28 = m34;
  m4 = 0;
  m2c = m38;
  mb0 = 0;
}

// @ 0x00b0fae0  (3-float spring)
struct Spring3f {
  u8  mb0, mb1;
  char pad2[2];
  float m0c, m10, m14;
  float m18, m1c, m20;
  float m24, m28, m2c;
  float m30, m34, m38;
  float m3c, m40, m44, m48, m4c, m50;
  void Set(float* v, bool force);
};

void Spring3f::Set(float* v, bool force) {
  if (force) {
    m30 = v[0]; m34 = v[1]; m38 = v[2];
    m24 = v[0]; m28 = v[1]; m2c = v[2];
    m18 = v[0]; m1c = v[1]; m20 = v[2];
    m0c = v[0]; m10 = v[1]; m14 = v[2];
    m3c = v[0] * 0.0f;
    m40 = v[1] * 0.0f;
    m44 = v[2] * 0.0f;
    m48 = m3c; m4c = m40; m50 = m44;
    mb0 = 0; mb1 = 0;
    return;
  }
  if (v[0] != m30 || v[1] != m34 || v[2] != m38) {
    m0c = m18; m10 = m1c; m14 = m20;
    m30 = v[0]; m34 = v[1]; m38 = v[2];
    mb0 = 1;
  }
}

// @ 0x00b0f930  (free, __stdcall)
void __stdcall SetEdgeDistance(float* p) {
  g_edgeX = p[0];
  g_edgeY = p[1];
}

// @ 0x00b0fc40  (free)
float BezierEval(float* a, float* b, float* c, float* d, float p5, float p6) {
  float f1 = ((*a * 2.0f - *c * 2.0f) + (*d + *b) * p5) / (p5 * p5 * p5);
  float f2 = *b;
  float f3 = p6;
  return f3 * (((*d - ((p5 * p5) * f1 * 3.0f + f2)) / (p5 + p5) + f1 * f3) * f3 + f2) + *a;
}

// @ 0x00b0f270  (giant; see partial.txt)
void cTerrainCameraController::RunCameraScript(int, int, int, int, int) {
  // incomplete skeleton: long straight-line sequence of VarMap::SetVar/GetVar.
}

// @ 0x00b0fd00  (giant x87 rotation; see partial.txt)
void RotateTowards(float* out, float* a, float* b, float t) {
  (void)out; (void)a; (void)b; (void)t;
}

// @ 0x00b0fe90  (mouse input handler; see partial.txt)
bool cTerrainCameraController::HandleMouse(float, float, int) {
  return false;
}
