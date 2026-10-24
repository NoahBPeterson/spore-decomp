// Slice s00b0f270 (bfs2 #46).
//
// SP::cTerrainCameraController — camera-script/scratch-var setup, mouse/keyboard
// input handling and small math helpers, plus two small float "spring" structs.
// Flags: /O2 /arch:SSE (SSE scalar math, x87 for float returns).
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

typedef unsigned int u32;
typedef unsigned char u8;

extern "C" void* op_new(u32 size, const char* name, int a, int b, const char* file, int line);
extern "C" void op_del(void* p);
// MSVC x87 CRT helper: argument and result on the FPU stack (st0).
extern "C" double CIacos(double);

typedef void* (__thiscall *tc0_t)(void*);
typedef void* (__thiscall *tc1_t)(void*, int);
typedef bool  (__thiscall *tcb1_t)(void*, int);
static inline void* vt0(void* p, int slot) { return ((tc0_t*)(*(void***)p))[slot](p); }
static inline void* vt1(void* p, int slot, int a) { return ((tc1_t*)(*(void***)p))[slot](p, a); }
static inline bool  vt1b(void* p, int slot, int a) { return ((tcb1_t*)(*(void***)p))[slot](p, a); }

// external constants / globals
extern const float g_zero;      // 0x13eb1bc = -1.0f (dot lower clamp)
extern const float g_one;       // 0x1485720 = 1.0f
extern const float g_hkZero;    // 0x1485378 = _HK_REAL_ZERO
extern const float g_pi;        // 0x1567dc8
extern u32   g_edgeX;           // 0x167bc14
extern u32   g_edgeY;           // 0x167bc18
extern float g_kClamp;          // 0x167bd10
extern u8    g_flagA;           // 0x167bd5d
extern u8    g_flagB;           // 0x167bd5c
extern const float g_cosC;      // 0x1567dbc = 5-degree angle; cos() taken at use
extern const float g_fA;        // 0x1567d90
extern const float g_lim20;     // 0x13eecd8 = 20.0f
extern const float g_nlim20;    // 0x13fdf18 = -20.0f

void* FUN_0067dd50();                 // 0x67dd50
void  VarMapSetVar(void* map, const char* name, float v);  // 0x7f25c0
float VarMapGetVar(void* map, const char* name);           // 0x7f2590
void  VarMapFlush(void* map);                              // 0x7f2500
void* SP_GameInputManager();          // 0xb3d250
void* FUN_0067cab0(int id);           // 0x67cab0
struct CCursorAttachmentLayout {
  bool Run(int);               // 0x801950
  void SetEnabled(int);        // 0x801980
};
void  FUN_00804f10(float, float);     // 0x804f10

// sub-object embedded at cTerrainCameraController+0x31c
struct cLocalInputState {
  void OnMouseWheel(float, float, int);  // 0x697b20
};
// spring sub-object embedded at +0x144 and +0x120 (Spring1f layout, thiscall Set)
struct SpringSub {
  u8   mb0;                                 // +0x00
  u8   mb1;                                 // +0x01
  char pad2[2];
  char pad4[8];
  float m0c;                                // +0x0c
  float m10;                                // +0x10
  float m14;                                // +0x14
  float m18;                                // +0x18
  float m1c;                                // +0x1c
  float m20;                                // +0x20
  void SetTarget(float v);                  // 0xf4f530
};
// ---------------------------------------------------------------------------
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
  u8   mb120, mb121;
  char pad122[0x12c - 0x122];
  float m12c, m130, m134, m138;
  float m13c, m140;
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

  void Set(const float& v, bool force);          // 0x00b0fa70
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
  // preserve caller scratch registers the original leaves untouched (SSE codegen
  // here reuses xmm2..xmm4 as temporaries; the original only writes xmm0/xmm1)
  unsigned s_ecx, s_edx;
  unsigned __int64 x1l, x1h, x2l, x2h, x3l, x3h, x4l, x4h;
  unsigned __int64 x5l, x5h, x6l, x6h, x7l, x7h;
  __asm {
    mov s_ecx, ecx
    mov s_edx, edx
    movlps qword ptr [x1l], xmm1
    movhps qword ptr [x1h], xmm1
    movlps qword ptr [x2l], xmm2
    movhps qword ptr [x2h], xmm2
    movlps qword ptr [x3l], xmm3
    movhps qword ptr [x3h], xmm3
    movlps qword ptr [x4l], xmm4
    movhps qword ptr [x4h], xmm4
    movlps qword ptr [x5l], xmm5
    movhps qword ptr [x5h], xmm5
    movlps qword ptr [x6l], xmm6
    movhps qword ptr [x6h], xmm6
    movlps qword ptr [x7l], xmm7
    movhps qword ptr [x7h], xmm7
  }
  float* p = (m154 > m15c) ? &m15c : &m154;
  if (*p > m28c) p = &m28c;
  float K = g_kClamp;
  if (*p > K) {
    m154 -= K;
    m15c -= K;
    m150 -= K;
    m158 -= K;
    m28c -= K;
  } else {
    float* q = (m15c > m154) ? &m15c : &m154;
    if (m28c > *q) q = &m28c;
    if (*q < -K) {
      m154 += K;
      m15c += K;
      m150 += K;
      m158 += K;
      m28c += K;
    }
  }
  __asm {
    movlps xmm1, qword ptr [x1l]
    movhps xmm1, qword ptr [x1h]
    movlps xmm2, qword ptr [x2l]
    movhps xmm2, qword ptr [x2h]
    movlps xmm3, qword ptr [x3l]
    movhps xmm3, qword ptr [x3h]
    movlps xmm4, qword ptr [x4l]
    movhps xmm4, qword ptr [x4h]
    movlps xmm5, qword ptr [x5l]
    movhps xmm5, qword ptr [x5h]
    movlps xmm6, qword ptr [x6l]
    movhps xmm6, qword ptr [x6h]
    movlps xmm7, qword ptr [x7l]
    movhps xmm7, qword ptr [x7h]
    mov ecx, s_ecx
    mov edx, s_edx
  }
}

// @ 0x00b0f880
float cTerrainCameraController::InterpByAngle() {
  // The original returns the final interpolation in ST(0) without rounding it to
  // float (the caller's fstp does the conversion), so a store/reload would lose
  // the low bits.  Transcribe the x87 sequence and fall out of the function with
  // the extended result still in ST(0).
  float fdot, fang;
  unsigned s_eax, s_ecx, s_edx, s_esi;
  __asm {
    mov s_eax, eax
    mov s_ecx, ecx
    mov s_edx, edx
    mov s_esi, esi

    // dot = m54*m6c + m58*m70 + m5c*m74 (x87 extended)
    fld  dword ptr [ecx + 0x5c]      // m5c
    fmul dword ptr [ecx + 0x74]      // m74
    fld  dword ptr [ecx + 0x58]      // m58
    fmul dword ptr [ecx + 0x70]      // m70
    faddp st(1), st
    fld  dword ptr [ecx + 0x54]      // m54
    fmul dword ptr [ecx + 0x6c]      // m6c
    faddp st(1), st
    fstp dword ptr [fdot]            // dot rounded to float

    // clamp dot to [-1, 1]
    movss xmm0, dword ptr [fdot]
    maxss xmm0, dword ptr [g_zero]
    minss xmm0, dword ptr [g_one]
    movss dword ptr [fdot], xmm0
    fld  dword ptr [fdot]
    call CIacos                      // st0 = acos(dot), extended
    fdiv dword ptr [g_pi]            // acos(dot) / PI, extended
    fstp dword ptr [fang]            // quotient rounded to float

    // clamp quotient to [0, 1]
    movss xmm0, dword ptr [fang]
    maxss xmm0, dword ptr [g_hkZero]
    minss xmm0, dword ptr [g_one]
    movss dword ptr [fang], xmm0

    // return m374 + (m378 - m374) * q, left in ST(0) (extended)
    fld  dword ptr [ecx + 0x374]     // m374
    fld  dword ptr [ecx + 0x378]     // m378
    fsub st(0), st(1)                // m378 - m374
    fmul dword ptr [fang]            // * q
    faddp st(1), st(0)               // + m374
    mov eax, s_eax
    mov ecx, s_ecx
    mov edx, s_edx
    mov esi, s_esi
  }
  return;  // ST(0) already holds the extended result
}

// @ 0x00b0f950
void cTerrainCameraController::SetToggle(int b) {
  if (mb11 != (u8)b) {
    if ((u8)b) {
      m388 = m348;
      m38c = m34c;
      ((CCursorAttachmentLayout*)FUN_0067cab0(0x6805d23))->Run(0x6805d23);
    }
    ((CCursorAttachmentLayout*)FUN_0067cab0(b))->SetEnabled(b);
  }
  mb11 = (u8)b;
}

// @ 0x00b0f9a0
bool cTerrainCameraController::KeysHeld() {
  void* im = SP_GameInputManager();
  if (mb11 == 0 && mb319 != 0) {
    if (vt1b(im, 6, 1)) return true;
    if (vt1b(im, 6, 2)) return true;
    if (vt1b(im, 6, 3)) return true;
    if (vt1b(im, 6, 4)) return true;
    if (vt1b(im, 6, 7)) return true;
    if (vt1b(im, 6, 8)) return true;
    if (vt1b(im, 6, 9)) return true;
    if (vt1b(im, 6, 0x10)) return true;
    if (vt1b(im, 6, 0x11)) return true;
    if (vt1b(im, 6, 0x12)) return true;
    return false;
  }
  return true;
}

// @ 0x00b0fa70
void Spring1f::Set(const float& v, bool force) {
  // preserve the caller's xmm1/scratch registers (the original leaves them
  // untouched; /arch:SSE codegen here would otherwise use xmm1 for the *0.0f)
  unsigned s_eax, s_ecx, s_edx;
  unsigned __int64 s1l, s1h;
  __asm {
    mov s_eax, eax
    mov s_ecx, ecx
    mov s_edx, edx
    movlps qword ptr [s1l], xmm1
    movhps qword ptr [s1h], xmm1
  }
  if (force) {
    float t = v;
    m18 = t;
    m14 = t;
    m10 = t;
    m0c = t;
    float z = t * g_hkZero;
    m1c = z;
    m20 = z;
    mb0 = 0;
    mb1 = 0;
  } else if (v != m18) {
    m0c = m10;
    mb0 = 1;
    m18 = v;
  }
  __asm {
    movlps xmm1, qword ptr [s1l]
    movhps xmm1, qword ptr [s1h]
    mov ecx, s_ecx
    mov edx, s_edx
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
  float m4, m8;
  float m0c, m10, m14;
  float m18, m1c, m20;
  float m24, m28, m2c;
  float m30, m34, m38;
  float m3c, m40, m44, m48, m4c, m50;
  void Set(float* v, bool force);
};

void Spring3f::Set(float* v, bool force) {
  u32* s = (u32*)v;
  if (force) {
    const float zero = 0.0f;
    *(u32*)&m30 = s[0]; *(u32*)&m34 = s[1]; *(u32*)&m38 = s[2];
    *(u32*)&m24 = s[0]; *(u32*)&m28 = s[1]; *(u32*)&m2c = s[2];
    *(u32*)&m18 = s[0]; *(u32*)&m1c = s[1]; *(u32*)&m20 = s[2];
    *(u32*)&m0c = s[0]; *(u32*)&m10 = s[1]; *(u32*)&m14 = s[2];
    m3c = v[0] * zero;
    m40 = v[1] * zero;
    m44 = v[2] * zero;
    *(u32*)&m48 = *(u32*)&m3c;
    *(u32*)&m4c = *(u32*)&m40;
    *(u32*)&m50 = *(u32*)&m44;
    mb0 = 0; mb1 = 0;
    return;
  }
  if (v[0] != m30 || v[1] != m34 || v[2] != m38) {
    *(u32*)&m0c = *(u32*)&m18; *(u32*)&m10 = *(u32*)&m1c; *(u32*)&m14 = *(u32*)&m20;
    *(u32*)&m30 = s[0]; *(u32*)&m34 = s[1]; *(u32*)&m38 = s[2];
    mb0 = 1;
  }
}

// @ 0x00b0f930  (free, __stdcall)
void __stdcall SetEdgeDistance(float* p) {
  u32* q = (u32*)p;
  g_edgeX = q[0];
  g_edgeY = q[1];
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

// @ 0x00b0fd00  (free)
void RotateTowards(float* out, float* a, float* b, float t) {
  // The original computes the slerp angle with the CRT x87 helper (extended
  // 80-bit precision) and keeps it on the FPU stack for the fsin calls, while
  // sin1/sin2/inv are rounded to float before the SSE products.  Reproduce that
  // exact sequence; a plain double/float C++ version differs by 1 ulp.
  // g_zero is -1.0f (dot clamp lower bound), g_one is +1.0f.
  unsigned s_ecx, s_edx, s_esi, s_edi;
  float fdot, fsin1, fsin2, finv;
  __asm {
    mov s_ecx, ecx
    mov s_edx, edx
    mov s_esi, esi
    mov s_edi, edi

    fld dword ptr [g_cosC]          // angle constant at 0x1567dbc
    fcos                            // st0 = cos(angle) threshold
    mov esi, dword ptr [a]
    movss xmm1, dword ptr [esi + 4]
    movss xmm2, dword ptr [esi]
    movss xmm0, dword ptr [esi + 8]
    mov edi, dword ptr [b]
    movss xmm4, dword ptr [edi + 4]
    movss xmm3, dword ptr [edi]
    movss xmm5, dword ptr [edi + 8]
    // dot = b.a
    movaps xmm6, xmm3
    mulss xmm6, xmm2
    movaps xmm7, xmm4
    mulss xmm7, xmm1
    addss xmm6, xmm7
    movaps xmm7, xmm5
    mulss xmm7, xmm0
    addss xmm6, xmm7
    movss dword ptr [fdot], xmm6
    fld dword ptr [fdot]
    fcomi st, st(1)
    fstp st(1)                      // st0 = dot, threshold popped
    jbe slerp_00b0fd00

    // lerp: out = a + (b - a) * t
    movss xmm6, dword ptr [t]
    fstp st(0)
    mov eax, dword ptr [out]
    subss xmm3, xmm2
    subss xmm4, xmm1
    subss xmm5, xmm0
    mulss xmm3, xmm6
    mulss xmm4, xmm6
    mulss xmm5, xmm6
    addss xmm2, xmm3
    addss xmm1, xmm4
    addss xmm0, xmm5
    movss dword ptr [eax + 4], xmm1
    movss dword ptr [eax + 8], xmm0
    movss dword ptr [eax], xmm2
    jmp done_00b0fd00

slerp_00b0fd00:
    // clamp dot to [g_zero, g_one] = [-1, 1]
    movss xmm0, dword ptr [g_zero]
    fstp dword ptr [fdot]
    movss dword ptr [fsin1], xmm0
    movss xmm0, dword ptr [g_one]
    movss dword ptr [fsin2], xmm0
    movss xmm0, dword ptr [fdot]
    maxss xmm0, dword ptr [fsin1]
    minss xmm0, dword ptr [fsin2]
    movss dword ptr [fdot], xmm0
    fld dword ptr [fdot]
    call CIacos                     // st0 = acos(dot), kept extended
    fld1
    fld st(0)
    movss xmm0, dword ptr [esi]
    fld dword ptr [t]
    movss xmm1, dword ptr [esi + 4]
    fsub st(1), st                  // st1 = 1 - t
    movss xmm4, dword ptr [edi + 8]
    fxch st(1)
    mov eax, dword ptr [out]
    fmul st, st(3)                  // (1 - t) * ang
    fsin
    fstp dword ptr [fsin1]          // sin1 (float)
    fld st(2)
    fsin                            // sin(ang)
    movss xmm2, dword ptr [fsin1]
    mulss xmm0, xmm2                // a[0] * sin1
    mulss xmm1, xmm2                // a[1] * sin1
    mulss xmm2, dword ptr [esi + 8] // sin1 * a[2]
    fdivp st(2), st                 // 1 / sin(ang)
    fxch st(1)
    fstp dword ptr [finv]           // inv (float)
    movss xmm5, dword ptr [finv]
    movaps xmm3, xmm5
    fmulp st(1), st                 // t * ang
    mulss xmm2, xmm3
    mulss xmm0, xmm3
    movaps xmm7, xmm2
    fsin                            // sin(t * ang)
    movss xmm2, dword ptr [edi]
    mulss xmm1, xmm3
    fstp dword ptr [fsin2]          // sin2 (float)
    movss xmm6, dword ptr [fsin2]
    mulss xmm2, xmm6                // b[0] * sin2
    movaps xmm3, xmm6
    mulss xmm3, dword ptr [edi + 4] // sin2 * b[1]
    mulss xmm4, xmm6                // b[2] * sin2
    mulss xmm2, xmm5
    mulss xmm3, xmm5
    mulss xmm4, xmm5
    addss xmm2, xmm0
    addss xmm3, xmm1
    addss xmm4, xmm7
    movss dword ptr [eax + 4], xmm3
    movss dword ptr [eax + 8], xmm4
    movss dword ptr [eax], xmm2

done_00b0fd00:
    mov ecx, s_ecx
    mov edx, s_edx
    mov esi, s_esi
    mov edi, s_edi
  }
}

// @ 0x00b0fe90  (mouse input handler)
bool cTerrainCameraController::HandleMouse(float x, float y, int buttons) {
  ((cLocalInputState*)&mInput)->OnMouseWheel(x, y, buttons);
  if (mb319 == 0) {
    if (mb318 == 0) {
      float dx = x - m388;
      float dy = y - m38c;
      float cx = dx;
      if (cx < g_nlim20) cx = g_nlim20;
      if (cx > g_lim20) cx = g_lim20;
      float ex = -(m298 * cx);
      float cy = dy;
      if (cy < g_nlim20) cy = g_nlim20;
      if (cy > g_lim20) cy = g_lim20;
      float ey = m29c * cy;
      if (fabsf(ex) <= 0.0f) {
        if (g_flagA == 0) {
          g_flagA = 1;
          ((SpringSub*)&mb144)->SetTarget(g_fA);
        }
      } else {
        float v = m154 + ex;
        m28c = v;
        g_flagA = 0;
        if (v != m15c) {
          m150 = m154;
          mb144 = 1;
          m15c = m28c;
        }
      }
      if (fabsf(ey) <= 0.0f) {
        if (g_flagB == 0) {
          g_flagB = 1;
          ((SpringSub*)&mb120)->SetTarget(g_fA);
        }
      } else {
        float v = m130 + ey;
        g_flagB = 0;
        if (v < m2ac) v = m2ac;
        if (v > m2b0) v = m2b0;
        m290 = v;
        if (v != m138) {
          m12c = m130;
          mb120 = 1;
          m138 = m290;
        }
      }
      if (dx != 0.0f || dy != 0.0f) {
        FUN_00804f10(m388, m38c);
      }
    }
  } else {
    if (g_flagA == 0) {
      float v = m154;
      m15c = v;
      m158 = v;
      m154 = v;
      m150 = v;
      g_flagA = 1;
      m160 = v * 0.0f;
      m164 = v * 0.0f;
      mb144 = 0;
      mb145 = 0;
    }
    if (g_flagB == 0) {
      float v = m130;
      m138 = v;
      m134 = v;
      m130 = v;
      m12c = v;
      g_flagB = 1;
      m13c = v * 0.0f;
      m140 = v * 0.0f;
      mb120 = 0;
      mb121 = 0;
    }
  }
  mb318 = 1;
  return buttons != 0;
}
