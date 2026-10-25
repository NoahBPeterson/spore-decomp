// Slice s0110ad70: hkBoxBoxCollisionDetection feature validation routines.
// Flags: /O2 /MD /Gy /TP /fp:fast /GS- (no /EHsc, no /arch:SSE: retail is x87).
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// cached feature-pair list (built by the intersection check)
// ---------------------------------------------------------------------------
struct FeaturePairList {
  unsigned char mPairs[8][4];   // +0x00  {feature, signs, pad, pad}
  unsigned char mField20;       // +0x20
  unsigned char mCount;         // +0x21
  char          mPad22[0x26];   // +0x22

  void FUN_010ec500();          // 0x010ec500
};

// a single feature pair (hkFeatureContactPoint)
struct FeaturePair {
  unsigned char mFeature[2];    // +0x00
  unsigned short mPad;          // +0x02
};

// one entry of the separating-distance table; the engine parks a sentinel
// value in the entries it has already consumed.
union DepthSlot {
  float    mFloat;
  unsigned mBits;
};

// per-pair validation buffer (hkFeaturePointCache)
struct __declspec(align(16)) FeaturePointCache {
  float mFeatures[12];   // +0x00  [0..3] = A side, [4..7] = B side
  float mScale;          // +0x30
  float mResult;         // +0x34
  int   mIndex;          // +0x38
  int   mSubIndex;       // +0x3c
};

// scratch contact point (hkProcessCdPoint)
struct ProcessCdPoint {
  float mPoint[3];    // +0x00  contact position
  float mDistance;    // +0x0c
  float mPlane[4];    // +0x10  contact normal
};

// contact point handed back to the caller
struct CdPoint {
  float mPoint[3];    // +0x00
  float mDistance;    // +0x0c
  float mPlane[4];    // +0x10
};

struct CollisionInput {
  char mData[0x10];   // +0x00
};

struct BoxBoxDetector {
  char           mPad00[0x60];   // +0x00
  float          mPlaneA[4];     // +0x60
  float          mPlaneB[4];     // +0x70
  CollisionInput mInput;         // +0x80
  float          mThreshA[4];    // +0x90
  float          mThreshB[4];    // +0xa0
  char           mPadB0[0x30];   // +0xb0
  DepthSlot      mDepth[5][4];   // +0xe0

  void FUN_010d93e0();                                   // 0x010d93e0
  int  FUN_01109460(CollisionInput* in);                 // 0x01109460
  void FUN_0110a0d0(FeaturePointCache* d, int id);       // 0x0110a0d0
  void FUN_0110a2b0(FeaturePointCache* d, int id);       // 0x0110a2b0
  void FUN_0110a4b0(FeaturePointCache* d);               // 0x0110a4b0
  void FUN_0110a600(void* res, FeaturePointCache* d);    // 0x0110a600
  void FUN_01108a10(ProcessCdPoint* cp, FeaturePair* fp,
                    FeaturePointCache* d);               // 0x01108a10
  void FUN_01108b80(ProcessCdPoint* cp, FeaturePair* fp,
                    FeaturePointCache* d);               // 0x01108b80
  void FUN_01108c30(ProcessCdPoint* cp, FeaturePair* fp,
                    FeaturePointCache* d);               // 0x01108c30

  int  FUN_0110ad70(FeaturePairList* list, unsigned char* out,
                    FeaturePointCache* d);
  void FUN_0110b260(unsigned char* out, CdPoint* result);
};

// hkPackSigns1 and hkPackSigns2 are not callable from reconstructed source:
// hkPackSigns1 reads one vector through esi and a scale on the stack, and
// hkPackSigns2 takes one vector through ecx and one through eax, writing the
// packed pair through esi.  Their arithmetic is reproduced verbatim here.
static unsigned char PackSigns1(const float* dir, float scale)
{
  DepthSlot bits;
  bits.mFloat = scale;

  unsigned char s0 = dir[0] < 0.0f;
  unsigned char s1 = dir[1] < 0.0f;
  unsigned char s2 = dir[2] < 0.0f;

  return (unsigned char)((s0 << 7) | (s1 << 6) | (s2 << 5) |
                         ((bits.mBits >> 28) & 8));
}

static unsigned short PackSigns2(const float* dirA, const float* dirB,
                                 int a, int b)
{
  unsigned char s0 = dirA[0] < 0.0f;
  unsigned char s1 = dirA[1] < 0.0f;
  unsigned char s2 = dirA[2] < 0.0f;
  unsigned char s3 = dirB[0] < 0.0f;
  unsigned char s4 = dirB[1] < 0.0f;
  unsigned char s5 = dirB[2] < 0.0f;

  unsigned char lo = (unsigned char)(((s2 << 1) | (s1 << 2) |
                                      (s0 * (unsigned char)0xf8)) | 1) << 4;
  unsigned char hi = (unsigned char)(~((s5 << 1) | (s4 << 2) |
                                      (s3 * (unsigned char)0xf8)) & 0xe) << 4;

  return (unsigned short)(((hi + (unsigned char)b) * 256) +
                          (unsigned char)(lo + (unsigned char)a));
}

// ---------------------------------------------------------------------------
// pick the largest remaining separating distance; entries already tried have
// been overwritten with the sentinel, so each pass selects the next one.
// ---------------------------------------------------------------------------
#define CONSIDER(level, sub, value)                                  \
  if (best < mDepth[level][sub].mFloat) {                            \
    id = value;                                                      \
    best = mDepth[level][sub].mFloat;                                \
  }

// @ 0x0110ad70
int BoxBoxDetector::FUN_0110ad70(FeaturePairList* list, unsigned char* out,
                                 FeaturePointCache* d)
{
  int counter = 8;
  do {
    float best = mDepth[0][0].mFloat;
    int id = 0;
    CONSIDER(0, 0, 0)
    CONSIDER(0, 1, 1)
    CONSIDER(0, 2, 2)
    CONSIDER(1, 0, 4)
    CONSIDER(1, 1, 5)
    CONSIDER(1, 2, 6)
    CONSIDER(2, 0, 8)
    CONSIDER(2, 1, 9)
    CONSIDER(2, 2, 10)
    CONSIDER(3, 0, 12)
    CONSIDER(3, 1, 13)
    CONSIDER(3, 2, 14)
    CONSIDER(4, 0, 16)
    CONSIDER(4, 1, 17)

    if (best < mDepth[4][2].mFloat) {
      id = 18;
      d->mIndex = (id - 8) >> 2;
      d->mSubIndex = (id - 8) & 3;
      FUN_0110a4b0(d);
      unsigned short packed = PackSigns2(d->mFeatures, d->mFeatures + 4,
                                         d->mIndex, d->mSubIndex);
      *out = (unsigned char)packed;
      out[1] = (unsigned char)(packed >> 8);
      d->mIndex = *out;
      d->mSubIndex = out[1];
      for (int i = list->mCount - 1; i >= 0; --i) {
        if (list->mPairs[i][0] == *out && list->mPairs[i][1] == out[1])
          return 1;
      }
      char res[4];
      FUN_0110a600(res, d);
      if (res[0] != 0)
        return 2;
    } else if (id <= 2) {
      *out = (unsigned char)id;
      FUN_0110a0d0(d, id);
      unsigned char signs = PackSigns1(d->mFeatures + 4, d->mScale);
      out[1] = signs;
      for (int i = list->mCount - 1; i >= 0; --i) {
        if (list->mPairs[i][0] == *out && list->mPairs[i][1] == signs)
          return 1;
      }
      float a0 = fabsf(d->mFeatures[0]);
      float a1 = fabsf(d->mFeatures[1]);
      float a2 = fabsf(d->mFeatures[2]);
      float a3 = fabsf(d->mFeatures[3]);
      unsigned mask = (unsigned)(((a0 < mThreshA[0]) * -8) |
                                 ((a1 < mThreshA[1]) << 2) |
                                 ((a2 < mThreshA[2]) << 1) |
                                 (a3 < mThreshA[3]));
      if ((mask & 0xe) == 0xe) {
        d->mResult = d->mFeatures[d->mIndex] * d->mScale - mPlaneA[d->mIndex];
        return 2;
      }
    } else if (id <= 6) {
      *out = (unsigned char)id;
      FUN_0110a2b0(d, id - 4);
      unsigned char signs = PackSigns1(d->mFeatures, d->mScale);
      out[1] = signs;
      for (int i = list->mCount - 1; i >= 0; --i) {
        if (list->mPairs[i][0] == *out && list->mPairs[i][1] == signs)
          return 1;
      }
      float a0 = fabsf(d->mFeatures[4]);
      float a1 = fabsf(d->mFeatures[5]);
      float a2 = fabsf(d->mFeatures[6]);
      float a3 = fabsf(d->mFeatures[7]);
      unsigned mask = (unsigned)(((a0 < mThreshB[0]) * -8) |
                                 ((a1 < mThreshB[1]) << 2) |
                                 ((a2 < mThreshB[2]) << 1) |
                                 (a3 < mThreshB[3]));
      if ((mask & 0xe) == 0xe) {
        d->mResult = -(d->mFeatures[d->mIndex] * d->mScale) -
                     mPlaneA[d->mIndex];
        return 2;
      }    } else {
      d->mIndex = (id - 8) >> 2;
      d->mSubIndex = (id - 8) & 3;
      FUN_0110a4b0(d);
      unsigned short packed = PackSigns2(d->mFeatures, d->mFeatures + 4,
                                         d->mIndex, d->mSubIndex);
      *out = (unsigned char)packed;
      out[1] = (unsigned char)(packed >> 8);
      d->mIndex = *out;
      d->mSubIndex = out[1];
      for (int i = list->mCount - 1; i >= 0; --i) {
        if (list->mPairs[i][0] == *out && list->mPairs[i][1] == out[1])
          return 1;
      }
      char res[4];
      FUN_0110a600(res, d);
      if (res[0] != 0)
        return 2;
    }

    mDepth[id >> 2][id & 3].mBits = 0xff7fffee;
  } while (--counter > 0);
  return 0;
}

#undef CONSIDER

// @ 0x0110b260
void BoxBoxDetector::FUN_0110b260(unsigned char* out, CdPoint* result)
{
  FeaturePairList    list;
  FeaturePointCache  data;
  ProcessCdPoint     cp;
  FeaturePair        pair;
  unsigned char      ok = 0;

  list.FUN_010ec500();
  pair.mPad = 0;
  FUN_010d93e0();

  if (FUN_01109460(&mInput) == 0) {
    if (FUN_0110ad70(&list, pair.mFeature, &data) != 2) {
      *out = 0;
      return;
    }
    ok = 1;
    int id = data.mIndex;
    if (id <= 2)
      FUN_01108a10(&cp, &pair, &data);
    else if (id <= 6)
      FUN_01108b80(&cp, &pair, &data);
    else
      FUN_01108c30(&cp, &pair, &data);

    float dist;
    if (pair.mFeature[0] > 2) {
      float depth = -cp.mPlane[3];
      cp.mPoint[0] = cp.mPlane[0] * depth + cp.mPoint[0];
      cp.mPoint[1] = cp.mPlane[1] * depth + cp.mPoint[1];
      cp.mPoint[2] = cp.mPlane[2] * depth + cp.mPoint[2];
      dist = depth * cp.mPlane[3] + cp.mDistance;
    } else {
      dist = cp.mDistance;
    }

    result->mPlane[0] = cp.mPlane[0];
    result->mPlane[1] = cp.mPlane[1];
    result->mPlane[2] = cp.mPlane[2];
    result->mPlane[3] = cp.mPlane[3];
    result->mDistance = dist;
    result->mPoint[0] = cp.mPoint[0];
    result->mPoint[1] = cp.mPoint[1];
    result->mPoint[2] = cp.mPoint[2];
    result->mPlane[3] = cp.mPlane[3];
  }
  *out = ok;
}
