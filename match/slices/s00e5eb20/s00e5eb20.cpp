// Slice s00e5eb20 (hk2 slice 31). SP::sCellIsOutOfRange at 0x00e5f8c0.
#include "types.h"

extern char g_16b3c04[];   // gspCellGame pointer global
extern float kCellOOR_AC;  // 0x14856bc
extern float kOne;         // 0x1485720
extern float kScale;       // 0x13f6a20
extern float kLevelSize[]; // 0x1483bd0

namespace SP {
  int   __fastcall sGetSourceLevel(void* unused, int level);   // 0xe4ee60, level in EDX
  float __cdecl    sGetBoxSizeMultiplier2(int idx, unsigned flag);  // 0xe51ff0
  char  __cdecl    sBlockIsInRange(int* box);                  // 0xe5f810
}

struct cLookup36c { void* Get(int id); };  // 0xb721d0, thiscall, ret 4

static __forceinline int FloorF(float v) {
  int i;
  __asm { movss xmm0, v
          cvtss2si eax, xmm0
          mov i, eax }
  if (v < (float)i) i = i - 1;
  return i;
}

namespace SP {
bool sCellIsOutOfRange(char* self) {
  const int idx = *(int*)(self + 0x358);
  if (idx == -1)
    return false;
  char* game = *(char**)g_16b3c04;
  char* levelObj = *(char**)(game + 0x5190);
  void* unused;
  const int lvl = sGetSourceLevel(unused, *(int*)(levelObj + 0x1c));
  if (idx + 1 < lvl) {
    *(float*)(self + 0xb4) = 0.0f;
    *(float*)(self + 0xac) = kCellOOR_AC;
    return false;
  }
  cLookup36c* lk = (cLookup36c*)(game + 0x1c);
  if (lk->Get(*(int*)(self + 0x36c)) != 0)
    return false;
  int box[4];
  box[0] = *(int*)(self + 0x35c) != *(int*)(game + 0x40fc);
  box[1] = idx;
  const float mult = sGetBoxSizeMultiplier2(idx, (unsigned)box[0]);
  volatile float denom = (mult * kScale) * (kLevelSize[idx] / *(float*)(game + 0x514c));
  const float inv = kOne / denom;
  box[2] = FloorF(*(float*)(self + 0x4c) * inv);
  box[3] = FloorF(*(float*)(self + 0x50) * inv);
  return sBlockIsInRange(box) == 0;
}
}
