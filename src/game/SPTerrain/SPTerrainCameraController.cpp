// src/game/SPTerrain/SPTerrainCameraController.cpp -- migrated from slice(s) s00b10200, s00b0f270 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainCameraController.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>

// unnamed retail callees and globals (address in the comment)
extern const float g_zero;      // 0x13eb1bc = 0.0f
extern const float g_one;       // 0x1485720 = 1.0f
extern const float g_pi;        // 0x1567dc8
extern float g_edgeX;           // 0x167bc14
extern float g_edgeY;           // 0x167bc18
extern float g_kClamp;          // 0x167bd10
extern float acosf(float);

// ---- items of slice s00b0f270 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
typedef void* (__thiscall *tc1_t)(void*, int);
static inline void* vt1(void* p, int slot, int a) { return ((tc1_t*)(*(void***)p))[slot](p, a); }
extern const float g_zero;      // 0x13eb1bc = 0.0f
extern const float g_one;       // 0x1485720 = 1.0f
extern const float g_pi;        // 0x1567dc8
extern float g_edgeX;           // 0x167bc14
extern float g_edgeY;           // 0x167bc18
extern float g_kClamp;          // 0x167bd10
extern float acosf(float);
void* SP_GameInputManager();          // 0xb3d250
void* FUN_0067cab0(int id);           // 0x67cab0
struct CCursorAttachmentLayout { void IsSomething(); void SetEnabled(bool); };
namespace SP {
class cTerrainCameraController { public:
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
}
namespace SP {
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
}
using SP::cTerrainCameraController;
using SP::Spring1f;
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
// ---- items of slice s00b0f270 end

// ---- items of slice s00b10200 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned int g_167bd6c;   // +0x167bd6c lazy flag
extern float g_167bd60, g_167bd64, g_167bd68;
extern unsigned int g_167bd7c;   // +0x167bd7c lazy flag
extern float g_167bd70, g_167bd74, g_167bd78;
extern float g_kMinInterpTime;   // +0x1488874 = 0.1
extern "C" void* DebugDrawGrid_00f48aa0(void*);          // SP::cDistGrid::DebugDrawGrid
extern "C" float FUN_00f987f0(void*);
extern "C" float GetHeightAt_00f927c0(void*, void*);
extern "C" float FUN_007f2590(const char*);
extern "C" void FUN_007f25c0(const char*, float);
extern "C" void FUN_00b0f270(void*, int, int, int, int, int, int);
struct cTerrainCameraController_s00b1_0200
{
    char  pad_00[0x18];
    bool  m18;              // +0x18
    char  pad_19[0xb];
    float m24;              // +0x24
    float m28;              // +0x28
    char  pad_2c[4];
    float m30;              // +0x30
    char  pad_34[0x54 - 0x34];
    float m54, m58, m5c;    // +0x54..+0x5c
    char  pad_60[0x6c - 0x60];
    float m6c, m70, m74;    // +0x6c..+0x74
    char  pad_78[0xfc - 0x78];
    bool  mfc, mfd;         // +0xfc,+0xfd
    char  pad_fe[0x108 - 0xfe];
    float m108, m10c, m110, m114, m118, m11c;   // +0x108..+0x11c
    bool  m120, m121;
    char  pad_122[0x124 - 0x122];
    float m124, m128;                            // +0x124,+0x128
    float m12c, m130, m134, m138, m13c, m140;   // +0x12c..+0x140
    bool  m144, m145;
    char  pad_146[0x148 - 0x146];
    float m148, m14c;                            // +0x148,+0x14c
    float m150, m154, m158, m15c, m160, m164;   // +0x150..+0x164
    char  pad_168[0x290 - 0x168];
    float m290;                                  // +0x290
    float m294, m298, m29c, m2a0, m2a4;          // +0x294..+0x2a4
    char  pad_2a8[0x2ac - 0x2a8];
    float m2ac, m2b0, m2b4;                      // +0x2ac..+0x2b4
    char  pad_2b8[0x304 - 0x2b8];
    bool  m304;             // +0x304
    char  pad_305[0x35c - 0x305];

    float* FUN_00b10200();                               // @ 0x00b10200
    float* FUN_00b10260();                               // @ 0x00b10260
    void   FUN_00b102c0();                               // @ 0x00b102c0
    void   FUN_00b10340(float, float, float);            // @ 0x00b10340
    void   FUN_00b10470(float);                          // @ 0x00b10470
    void   FUN_00b104c0(float);                          // @ 0x00b104c0
    void   FUN_00b10540(float, float, float);            // @ 0x00b10540
    void   FUN_00b10760(float, float, float);            // @ 0x00b10760
    void   ReloadZoomProgram();                          // @ 0x00b108b0
    void   FUN_00b10a90(float);                          // @ 0x00b10a90
    void   FUN_00b10c40(bool);                           // @ 0x00b10c40
};
extern float g_zero_s00b1_0200;             // +0x1485378 = 0.0
static inline void* g_vt(void* p) { return *(void**)p; }
static inline void* g_vfn(void* p, int off) { return *(void**)((char*)g_vt(p) + off); }
template<class R> static inline R vcall0(void* p, int off)
{ return ((R(__thiscall*)(void*))g_vfn(p, off))(p); }
// ---- items of slice s00b10200 end

// @ 0x00b0f270
void SP::cTerrainCameraController::RunCameraScript(int, int, int, int, int)
{
  // incomplete skeleton: long straight-line sequence of VarMap::SetVar/GetVar.
}

// @ 0x00b0f720
void SP::cTerrainCameraController::SetFloats5(float a, float b, float c, float d, float e)
{
  m278 = a;
  m27c = b;
  m280 = c;
  m284 = d;
  m288 = e;
}

// @ 0x00b0f770
void SP::cTerrainCameraController::ClampSpread()
{
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
float SP::cTerrainCameraController::InterpByAngle()
{
  float dot = m54 * m6c + m58 * m70 + m5c * m74;
  if (dot < g_zero) dot = g_zero;
  if (dot > g_one) dot = g_one;
  float ang = acosf(dot) / g_pi;
  if (ang < g_zero) ang = g_zero;
  if (ang > g_one) ang = g_one;
  return (m378 - m374) * ang + m374;
}

// @ 0x00b0f930
void __stdcall SetEdgeDistance(float* p)
{
  g_edgeX = p[0];
  g_edgeY = p[1];
}

// @ 0x00b0f950
void SP::cTerrainCameraController::SetToggle(int b)
{
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
bool SP::cTerrainCameraController::KeysHeld()
{
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
void SP::Spring1f::Set(float v, bool force)
{
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

// @ 0x00b0fae0
void Spring3f::Set(float* v, bool force)
{
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

// @ 0x00b0fbe0
void SP::Spring1f::Reset(float v)
{
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

// @ 0x00b0fc40
float BezierEval(float* a, float* b, float* c, float* d, float p5, float p6)
{
  float f1 = ((*a * 2.0f - *c * 2.0f) + (*d + *b) * p5) / (p5 * p5 * p5);
  float f2 = *b;
  float f3 = p6;
  return f3 * (((*d - ((p5 * p5) * f1 * 3.0f + f2)) / (p5 + p5) + f1 * f3) * f3 + f2) + *a;
}

// @ 0x00b0fd00
void RotateTowards(float* out, float* a, float* b, float t)
{
  (void)out; (void)a; (void)b; (void)t;
}

// @ 0x00b0fe90
bool SP::cTerrainCameraController::HandleMouse(float, float, int)
{
  return false;
}

// @ 0x00b10200
float* cTerrainCameraController_s00b1_0200::FUN_00b10200()
{
    if ((g_167bd6c & 1) == 0)
        g_167bd6c |= 1;
    float s = m28;
    float x = m54, y = m58, z = m5c;
    g_167bd60 = x * s;
    g_167bd64 = y * s;
    g_167bd68 = z * s;
    return &g_167bd60;
}

// @ 0x00b10260
float* cTerrainCameraController_s00b1_0200::FUN_00b10260()
{
    if ((g_167bd7c & 1) == 0)
        g_167bd7c |= 1;
    float s = m30;
    g_167bd70 = m6c * s;
    g_167bd74 = m70 * s;
    g_167bd78 = m74 * s;
    return &g_167bd70;
}

// @ 0x00b102c0
void cTerrainCameraController_s00b1_0200::FUN_00b102c0()
{
    void* grid = DebugDrawGrid_00f48aa0(this);
    if (!grid) return;
    float a = FUN_00f987f0(grid);
    void* set = vcall0<void*>(grid, 0xc);
    float b = GetHeightAt_00f927c0(set, &m6c);
    float v = a;
    if (!(a <= b)) v = b;
    float h = m2b4 + v;
    if (h != m30)
    {
        m30 = h;
        m24 = m28;
        m18 = true;
    }
}

// @ 0x00b104c0
void cTerrainCameraController_s00b1_0200::FUN_00b104c0(float v)
{
    float x = v > g_kMinInterpTime ? v : g_kMinInterpTime;
    m114 = x;
    m110 = x;
    m10c = x;
    m108 = x;
    m118 = x * g_zero_s00b1_0200;
    m11c = x * g_zero_s00b1_0200;
    mfc = false;
    mfd = false;
    m304 = true;
}

// @ 0x00b10540
void cTerrainCameraController_s00b1_0200::FUN_00b10540(float d, float p, float y)
{
    if (fabsf(m154 - d) > g_kMinInterpTime * 1.52587890625e-05f)
    {
        float old = m15c;
        m15c = d; m158 = d; m154 = d; m150 = d;
        m160 = d * 0.0f;
        m164 = d * 0.0f;
        m144 = m145 = false;
        if (old != m15c) { m15c = old; m150 = m154; m144 = true; }
    }
    if (fabsf(m130 - p) > g_kMinInterpTime * 1.52587890625e-05f)
    {
        float old = m138;
        float v = p;
        if (v <= m2ac) v = m2ac;
        if (v >= m2b0) v = m2b0;
        m138 = v; m134 = v; m130 = v; m12c = v;
        m13c = v * 0.0f;
        m140 = v * 0.0f;
        m120 = m121 = false;
        if (old != m138) { m138 = old; m12c = m130; m120 = true; }
    }
    if (fabsf(m10c - y) > 0.0f)
    {
        float old = m114;
        float v = y > g_kMinInterpTime ? y : g_kMinInterpTime;
        m114 = v; m110 = v; m10c = v; m108 = v;
        m118 = v * 0.0f;
        m11c = v * 0.0f;
        mfc = mfd = false;
        if (old != m114) { m114 = old; m108 = m10c; mfc = true; }
    }
    m304 = true;
}

// @ 0x00b10760
void cTerrainCameraController_s00b1_0200::FUN_00b10760(float d, float p, float y)
{
    m15c = d; m158 = d; m154 = d; m150 = d;
    m160 = d * 0.0f;
    m164 = d * 0.0f;
    m144 = m145 = false;

    float v = p;
    if (v <= m2ac) v = m2ac;
    if (v >= m2b0) v = m2b0;
    m138 = v; m134 = v; m130 = v; m12c = v;
    m13c = v * 0.0f;
    m140 = v * 0.0f;
    m120 = m121 = false;

    float x = y > g_kMinInterpTime ? y : g_kMinInterpTime;
    m114 = x; m110 = x; m10c = x; m108 = x;
    m118 = x * 0.0f;
    m11c = x * 0.0f;
    mfc = mfd = false;
    m304 = true;
}

// @ 0x00b108b0
void cTerrainCameraController_s00b1_0200::ReloadZoomProgram()
{
    // Reloads the zoom program from the config VarMap: distance / pitch and the
    // three mouse sensitivities, then sets up the interpolation targets.
    if (!*(int*)((char*)this + 0x314)) return;
    FUN_00b0f270(this, 0, 0, 0, 0, 0, 0);
    float dist = FUN_007f2590("default_distance");
    float dd = dist > g_kMinInterpTime ? dist : g_kMinInterpTime;
    m29c = dd;
    FUN_007f25c0("distance", m29c);
    FUN_007f25c0("height_above_water", m2a4);
    FUN_00b0f270(this, 0, 0, 0, 0, 0, 0);
    float pitch = FUN_007f2590("pitch") * 0.017453292f;
    m294 = pitch;
    m298 = FUN_007f2590("mouse_rotate_sensitivity_x") * 0.017453292f;
    m2a0 = FUN_007f2590("mouse_rotate_sensitivity_y") * 0.17453292f;
    m2a4 = FUN_007f2590("mouse_scroll_sensitivity");
}
