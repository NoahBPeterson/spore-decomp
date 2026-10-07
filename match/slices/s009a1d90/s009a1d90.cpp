// Slice s009a1d90 (bfs4 #34): animation instance time advance.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int uint;
extern const float g_one;     // 0x01485720  1.0f

struct U64Pair { uint a; uint b; };
struct AnimData { char pad[0x144]; uint mNumRecords; void* mpRecords; };
struct Vec8b {
  U64Pair* mpBegin;    // +0
  U64Pair* mpEnd;      // +4
  U64Pair* mpCap;      // +8
  void resize(uint n);                               // 0x009a1770 (slice s009a0d60)
};
extern "C" void FUN_009a1670(int* obj, float f, char p3, char p4, uint p5, uint p6, uint p7, uint p8);  // cdecl, 0x009a1670

// ===========================================================================
// advance an animation instance to time t, returning the phase (0x009a1d90)
// ===========================================================================
extern "C" double FUN_0099bfe0(float f);             // fractional part (slice s0099bf80)
extern int g_animSerial;                             // 0x0166b260
#pragma warning(disable:4035)
__forceinline int FloorToInt(float f) {
  __asm {
    movss    xmm0, f
    cvtss2si eax, xmm0
    cvtsi2ss xmm1, eax
    mov      ecx, eax
    sub      ecx, 1
    ucomiss  xmm0, xmm1
    cmovb    eax, ecx
  }
}
struct AnimInst2 {
  AnimData* mpData;     // +0x000
  char pad0[4];
  uint* mpMask;         // +0x008  (4 uints)
  char pad1[0xa0];
  uint8_t mActive;      // +0x0ac
  uint8_t mLoop;        // +0x0ad
  char pad2[2];
  double mTime;         // +0x0b0
  double mDuration;     // +0x0b8
  int mNumLoops;        // +0x0c0
  uint mLastLoop;       // +0x0c4
  Vec8b mTimes;         // +0x0c8
};
// @ 0x009a1d90
float FUN_009a1d90(AnimInst2* a, float t, char p3, char p4) {
  if (a->mpData == 0 || a->mActive == 0) return 0.0f;
  a->mTimes.resize(0);
  a->mTime = (double)t;
  float ratio = (float)((double)t / a->mDuration);
  if (a->mDuration <= (double)t) {
    uint k = (uint)FloorToInt(ratio);
    if (k > a->mLastLoop) {
      a->mLastLoop = k;
      if (a->mLoop == 0) goto noloop;
      *(int*)((char*)a->mpData + 0x12c) = g_animSerial;
      g_animSerial = g_animSerial + 1;
      a->mNumLoops = a->mNumLoops + 1;
    }
  }
  if (a->mLoop != 0) {
    t = (float)FUN_0099bfe0(ratio);
  } else {
noloop:
    t = ratio;
  }
  uint* m = a->mpMask;
  float scale = (*(float*)((char*)a->mpData + 0x120) - g_one) * t;
  FUN_009a1670((int*)a, scale, p3, p4, m[0], m[1], m[2], m[3]);
  return t;
}
