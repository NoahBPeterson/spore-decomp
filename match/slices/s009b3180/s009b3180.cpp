// nSPCreatureAnim::creature_static_data / creature_instance_data helpers (slice s009b3180).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2
#include "types.h"
#include <xmmintrin.h>
#include <math.h>

extern const float DAT_013fe14c;  // 0.375f
extern const float DAT_0141b034;  // 0.625f

extern const float DAT_01550d50;  // 10.0f
extern const float DAT_01550d4c;  // 2.3f
extern const float DAT_01550d54;  // 2.3f
extern const float DAT_0144725c;  // 0.1745f
extern const float DAT_014471f8;  // pi
extern const float DAT_01447260;  // 0.2269f
extern const float DAT_01485378;  // 0.0f
extern const float DAT_01471064;  // 0.5f
extern const float DAT_01485720;  // 1.0f
extern float DAT_0166c270;
extern uint32_t DAT_0166c274;
extern float DAT_0166c27c;
extern float DAT_0166c278;
extern uint32_t DAT_0166c280;
extern const __m128 DAT_013eb8b0;  // all-lane sign mask

namespace nSPCreatureAnim {

struct creature_instance_data;

// @ 0x009B33F0
float __cdecl GetAnimationBlend(int obj) {
  float* p = (float*)obj;
  return ((float*)((char*)p + 0x438))[0] * 0.375f +
         ((float*)((char*)p + 0x434))[0] * 0.625f;
}

// @ 0x009B3430
char __stdcall FUN_009b3430(int a, int b) {
  return ((b - a) >> 3) + 1 >= 4;
}

// @ 0x009B3460
int __cdecl FUN_009b3460(int obj) {
  int i = *(int*)(*(int*)(obj + 0x214) + 0x210);
  if (i == 0) {
    i = FUN_009b3460(*(int*)(obj + 0x214));
    *(int*)(obj + 0x210) = i;
    return i;
  }
  *(int*)(obj + 0x210) = i;
  return i;
}

// @ 0x009B3920
struct TargetFrame {
  char pad_000[0x1644];
  float posA[3];  // +0x1644
  float posB[4];  // +0x1650
  void Set(const float* a, const float* b);
};

void TargetFrame::Set(const float* a, const float* b) {
  posA[0] = a[0];
  posA[1] = a[1];
  posA[2] = a[2];
  posB[0] = b[0];
  posB[1] = b[1];
  posB[2] = b[2];
  posB[3] = b[3];
}

// @ 0x009B3BC0
void __cdecl FUN_009b3bc0(int obj) {
  float* p = (float*)(obj + 0x118);
  for (int i = 0; i < 9; i++)
    p[i] = 0.0f;
}

// @ 0x009B3C80
struct Transform30 {
  int a;         // +0x00
  int b;         // +0x04
  float f[10];   // +0x08
  Transform30& operator=(const Transform30& src);
};

Transform30& Transform30::operator=(const Transform30& src) {
  a = src.a;
  b = src.b;
  f[0] = src.f[0];
  f[1] = src.f[1];
  f[2] = src.f[2];
  f[3] = src.f[3];
  f[4] = src.f[4];
  f[5] = src.f[5];
  f[6] = src.f[6];
  f[7] = src.f[7];
  f[8] = src.f[8];
  f[9] = src.f[9];
  return *this;
}

// @ 0x009B3AB0
struct CopyBlock {
  int a[4];       // +0x00
  float f[10];    // +0x10
  char c;         // +0x38
  CopyBlock& operator=(const CopyBlock& src);
};

CopyBlock& CopyBlock::operator=(const CopyBlock& src) {
  a[0] = src.a[0];
  a[1] = src.a[1];
  a[2] = src.a[2];
  a[3] = src.a[3];
  f[0] = src.f[0];
  f[1] = src.f[1];
  f[2] = src.f[2];
  f[3] = src.f[3];
  f[4] = src.f[4];
  f[5] = src.f[5];
  f[6] = src.f[6];
  f[7] = src.f[7];
  f[8] = src.f[8];
  f[9] = src.f[9];
  c = src.c;
  return *this;
}

}  // namespace nSPCreatureAnim

// --- larger functions in the slice (partial; see partial.txt) ---

// @ 0x009B3180  PARTIAL: creature_body_static_data::Clear
void __fastcall FUN_009b3180(void* self) { (void)self; }

// @ 0x009B3490  PARTIAL
void __fastcall FUN_009b3490(void* self) { (void)self; }

// @ 0x009B3850  PARTIAL: creature_instance_data::ComposeGaitFileName
void __fastcall FUN_009b3850(void* self) { (void)self; }

// @ 0x009B3970
float FUN_009b3970(__m128 v)
{
  float t = _mm_cvtss_f32(v) / DAT_01550d50;
  float L;
  if (t > DAT_01485720)
    L = DAT_01485720;
  else if (t > 0.0f)
    L = t;
  else
    L = 0.0f;
  if (!(DAT_0166c274 & 1)) {
    DAT_0166c270 = DAT_0144725c;
    DAT_0166c274 |= 1;
  }
  return (1.0 - pow(1.0f - L, DAT_01550d4c)) * DAT_0166c270;
}

// @ 0x009B39E0
__m128 FUN_009b39e0(float x)
{
  if (!(DAT_0166c280 & 1)) {
    DAT_0166c27c = DAT_014471f8;
    DAT_0166c280 |= 1;
  }
  float t = _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(fabsf(x)), _mm_set_ss(DAT_0166c27c)));
  float L;
  if (t > DAT_01485720)
    L = DAT_01485720;
  else if (t > 0.0f)
    L = t;
  else
    L = 0.0f;
  if (!(DAT_0166c280 & 2)) {
    DAT_0166c278 = DAT_01447260;
    DAT_0166c280 |= 2;
  }
  volatile float Lv = L;   // the retail reloads the clamp result with an x87 fld
  float r = (float)((1.0 - pow(1.0f - Lv, DAT_01550d54)) * DAT_0166c278);
  __m128 out = _mm_set_ss(r);
  if (x > DAT_01485378)
    out = _mm_xor_ps(out, DAT_013eb8b0);
  // The retail body leaves the static-init flag word in eax (it is the last value written to
  // eax before the pow call and the pow helper preserves it); C cannot express that state.
  __asm { mov eax, dword ptr [DAT_0166c280] }
  return out;
}

// @ 0x009B3B20  PARTIAL
void __fastcall FUN_009b3b20(void* self) { (void)self; }

// @ 0x009B3C10
float FUN_009b3c10(float b, float c)
{
  float w = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(c), _mm_set_ss(DAT_01471064)));
  if (b > w) {
    int n = _mm_cvtt_ss2si(_mm_div_ss(_mm_add_ss(_mm_set_ss(w), _mm_set_ss(b)), _mm_set_ss(c)));
    return b - (float)n * c;
  }
  if (b > -w)
    return b;
  int n = _mm_cvtt_ss2si(_mm_div_ss(_mm_sub_ss(_mm_set_ss(b), _mm_set_ss(w)), _mm_set_ss(c)));
  return b - (float)n * c;
}

// @ 0x009B3CD0  PARTIAL
void __fastcall FUN_009b3cd0(void* self) { (void)self; }
