// nSPCreatureAnim::creature_static_data / creature_instance_data helpers (slice s009b3180).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2
#include "types.h"

extern const float DAT_013fe14c;  // 0.375f
extern const float DAT_0141b034;  // 0.625f

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

// @ 0x009B3970  PARTIAL
void __fastcall FUN_009b3970(void* self) { (void)self; }

// @ 0x009B39E0  PARTIAL
void __fastcall FUN_009b39e0(void* self) { (void)self; }

// @ 0x009B3B20  PARTIAL
void __fastcall FUN_009b3b20(void* self) { (void)self; }

// @ 0x009B3C10  PARTIAL
void __fastcall FUN_009b3c10(void* self) { (void)self; }

// @ 0x009B3CD0  PARTIAL
void __fastcall FUN_009b3cd0(void* self) { (void)self; }
