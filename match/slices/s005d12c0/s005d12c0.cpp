// slice s005d12c0 -- SP::cSpine75 (SPEditor spine): vertebra-coordinate copies,
// limb teardown / rebuild and photo-type / collision-filter bookkeeping.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <new>
#include "types.h"

typedef unsigned char uchar;

extern "C" void* memcpy(void* dst, const void* src, unsigned int n);  // 0x011e0744

// Global float constants referenced by this region.
extern "C" const float F_013ec488;  // 0x013ec488  -0.5f
extern "C" const float F_013f8950;  // 0x013f8950   0.25f
extern "C" const float F_01471064;  // 0x01471064   0.5f
extern "C" const float F_01485720;  // 0x01485720   1.0f

namespace SP {

// ---------------------------------------------------------------------------
// Element copies of the vertebra-coordinate vector.

// 0x14-byte sub-object with an out-of-line copy constructor / assignment (0x005d1240).
struct Sub24 {
  int mW[5];
  Sub24(const Sub24& other);
  Sub24& operator=(const Sub24& other);
};

// 0x24-byte element: 4 leading words + a 0x14-byte Sub24.
struct Elem24 {
  int mA;
  float mB;
  float mC;
  float mD;
  Sub24 mSub;
  Elem24(const Elem24& other) : mA(other.mA), mB(other.mB), mC(other.mC), mD(other.mD), mSub(other.mSub) {}
};

// 0x14-byte element of the spine's vertebra-coordinate vector.
struct Rec20 {
  int mW[5];
};

// Random-access iterator over Rec20 (passed and returned by value).
struct Rec20Iter {
  Rec20* mpNode;
  Rec20Iter() {}
  Rec20Iter(Rec20* p) : mpNode(p) {}
};

// copy_Rec20: cdecl element copy for the Rec20 vector (0x00951bf0).
Rec20* copy_Rec20(const Rec20* first, const Rec20* last, Rec20* dest);  // 0x00951bf0

// CopyE20: initialise a trailing range of Rec20 (0x005cf7a0).  Four by-value
// iterators plus a hidden return slot at the original call site.
Rec20Iter CopyE20(Rec20Iter a, Rec20Iter b, Rec20Iter c, Rec20Iter d);  // 0x005cf7a0

// ---------------------------------------------------------------------------
// Helper types.

struct Vec2 { float x; float y; };

// A [begin,end) pair of floats.
struct FloatSpan { const float* mpBegin; const float* mpEnd; };

struct cSPEditorBlock;
struct cSPEditorLimbJoint;
struct cSPEditorLimbStructure;
struct hkWorld;

// eastl::vector<BlockRef>: 3 pointers + allocator tag.
struct BlockVector {
  cSPEditorBlock** mpBegin;     // +0x00
  cSPEditorBlock** mpEnd;       // +0x04
  cSPEditorBlock** mpCapacity;  // +0x08
  unsigned mAllocator[2];       // +0x0c
};

// Ref-counted editor block.  Slots 1 and 2 of the vtable are AddRef / Release.
struct cSPEditorBlock {
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  char pad04[0x1d8 - 0x04];
  float mScale;           // +0x1d8
  char pad1dc[0x340 - 0x1dc];
  BlockVector mChildren;  // +0x340
  char pad354[0xdc0 - 0x354];
  float mFieldDC0;        // +0xdc0
  float mFieldDC4;        // +0xdc4
  unsigned mFlags;        // +0xdc8
};

// eastl::fixed_vector<BlockRef, 8>: inline 8-element buffer.
struct FixedBlockVector : BlockVector {
  unsigned mOverflow;     // +0x14
  void* mBuffer[8];       // +0x18
  FixedBlockVector() {
    mpBegin = mpEnd = (cSPEditorBlock**)mBuffer;
    mpCapacity = mpBegin + 8;
    mOverflow = 0;
  }
  FixedBlockVector& operator=(const BlockVector& src);  // 0x00453f20
};

// cSPEditorLimbStructure: heap-allocated limb (0x54 bytes).
struct cSPEditorLimbStructure {
  cSPEditorLimbStructure();                                       // 0x00488850
  cSPEditorLimbJoint* BuildLimb(cSPEditorBlock*, cSPEditorLimbJoint*, bool);  // 0x004891a0
  void Release();                                                 // 0x00488980
  void Destroy();                                                 // 0x00488900
};

// eastl::vector<cSPEditorLimbStructure*>.
struct LimbVector {
  cSPEditorLimbStructure** mpBegin;     // +0x00
  cSPEditorLimbStructure** mpEnd;       // +0x04
  cSPEditorLimbStructure** mpCapacity;  // +0x08
  void Grow(cSPEditorLimbStructure** pos, cSPEditorLimbStructure** value);  // 0x00630b30
};

// eastl::vector<unsigned int>.
struct U32Vector {
  unsigned* mpBegin;     // +0x00
  unsigned* mpEnd;       // +0x04
  unsigned* mpCapacity;  // +0x08
  void DoInsertValueI(unsigned* pos, const unsigned& value);  // 0x004558a0
};

// Red-black tree node base and the photo-type map built on it.
struct RTreeNodeBase {
  RTreeNodeBase* mpNodeRight;   // +0x00
  RTreeNodeBase* mpNodeLeft;    // +0x04
  RTreeNodeBase* mpNodeParent;  // +0x08
  int mnColor;                  // +0x0c
};

struct PhotoTypeInfo {
  void* mp0;   // +0x00
  void* mp4;   // +0x04
  int mInt8;   // +0x08
  int mIntC;   // +0x0c
};

struct ValNode : RTreeNodeBase {
  unsigned mKey;          // +0x10
  PhotoTypeInfo mValue;   // +0x14
};

struct PhotoTypeMap {
  int mField00;             // +0x00
  RTreeNodeBase mAnchor;    // +0x04
  int mField14;             // +0x14
  int mField18;             // +0x18
  PhotoTypeInfo& At(const unsigned& key);   // 0x00632e90
  PhotoTypeInfo* Find(unsigned key);
};

inline PhotoTypeInfo* PhotoTypeMap::Find(unsigned key)
{
  ValNode* node = (ValNode*)mAnchor.mpNodeParent;
  RTreeNodeBase* parent = &mAnchor;
  while (node) {
    if (node->mKey < key) {
      node = (ValNode*)node->mpNodeRight;
    } else {
      parent = node;
      node = (ValNode*)node->mpNodeLeft;
    }
  }
  if (parent == &mAnchor || key < ((ValNode*)parent)->mKey)
    parent = &mAnchor;
  if (parent == &mAnchor) return 0;
  return &At(key);
}

// The spine (cSpine75) and the Havok bodies it drives.
struct HavokBody {
  char pad00[0x38];
  int mHandle;   // +0x38
};

struct hkWorld {
  void updateCollisionFilterOnWorld(int a, int b);        // 0x010869e0
  void removeConstraint(uchar* out, void* constraint);    // 0x01086e90
};

// ---------------------------------------------------------------------------
// Free helpers.

void FUN_00f47380(void* p);                                             // 0x00f47380  operator delete
void* FUN_00f473a0(unsigned size, const char* name, int, int, int, int);  // 0x00f473a0  operator new
int FUN_005efd70(int i);                                                // 0x005efd70
float FUN_004a5b70(float scale);                                        // 0x004a5b70  GetExactSkinRadiusFromVertebra
cSPEditorBlock* FUN_004a5970(cSPEditorBlock* block);                    // 0x004a5970  next block
void FUN_004a0020(cSPEditorBlock* head, LimbVector* limbs, bool flag);  // 0x004a0020  EditorUtils::GetAllLimbs

// ---------------------------------------------------------------------------
// cSpine75.
//
// Field map (offsets read by the functions below):
//   +0x00  mpCoordsBegin     (+0x04 end, +0x08 cap)   Rec20 vector
//   +0x14  mpWorld
//   +0x34  mField34          +0x38 mHandle38          +0x74 mField74
//   +0x88  mField88  +0x8c mField8c  +0x90 mField90  +0x94 mField94  +0x98 mField98
//   +0xc5  mFieldC5
//   +0xcc  mMap              (PhotoTypeMap, 0x1c bytes)
//   +0xe8  mpBlockHead       +0xec mpBlockTail
//   +0x108 mLimbs            (LimbVector)
//   +0x11c mField11c
//   +0x120 mpCurve120        +0x124 mpCurve124
struct cSpine75 {
  Rec20* mpCoordsBegin;          // +0x00
  Rec20* mpCoordsEnd;            // +0x04
  Rec20* mpCoordsCap;            // +0x08
  char pad0c[0x14 - 0x0c];       // +0x0c
  hkWorld* mpWorld;              // +0x14
  char pad18[0x34 - 0x18];       // +0x18
  int mField34;                  // +0x34
  int mHandle38;                 // +0x38
  char pad3c[0x74 - 0x3c];       // +0x3c
  int mField74;                  // +0x74
  char pad78[0x88 - 0x78];       // +0x78
  float mField88;                // +0x88
  float mField8c;                // +0x8c
  float mField90;                // +0x90
  float mField94;                // +0x94
  float mField98;                // +0x98
  char pad9c[0xc5 - 0x9c];       // +0x9c
  bool mFieldC5;                 // +0xc5
  char padc6[0xcc - 0xc6];       // +0xc6
  PhotoTypeMap mMap;             // +0xcc
  cSPEditorBlock* mpBlockHead;   // +0xe8
  cSPEditorBlock* mpBlockTail;   // +0xec
  char padf0[0x108 - 0xf0];      // +0xf0
  LimbVector mLimbs;             // +0x108
  char pad114[0x11c - 0x114];    // +0x114
  float mField11c;               // +0x11c
  void* mpCurve120;              // +0x120
  void* mpCurve124;              // +0x124

  cSpine75* RecordBlockCoordinates(const cSpine75& other);                   // 0x005d12c0
  Rec20* FUN_005d0e40(unsigned n, const Rec20* first, const Rec20* last);    // 0x005d0e40
  void FUN_005d14a0();                                                       // 0x005d14a0
  void FUN_005d1530();                                                       // 0x005d1530
  bool FUN_005d1640();                                                       // 0x005d1640
  void FUN_005d1780(const FloatSpan* xs, const FloatSpan* ys);               // 0x005d1780
  void RepinArea(float lo, float hi, int a4);                                // 0x005d19e0
  void FUN_005d1ba0();                                                       // 0x005d1ba0
  void FUN_005d1d40();                                                       // 0x005d1d40
  void FUN_005d1e70();                                                       // 0x005d1e70
  void SetFlag(bool enable, int unused);                                     // 0x005d1600
  void EnableBody();                                                         // 0x005d1530
  void DisableBody();                                                        // 0x005d14a0
  Vec2* NearestParam(Vec2* out, cSPEditorBlock* block);                      // 0x005cf110
  void Extrude(cSPEditorBlock* block, float t, float s, int a4);             // 0x005cf4f0
};

// ---------------------------------------------------------------------------
// Element copies (kept verbatim from the canonical slice).

// @ 0x005d13f0
Elem24* CopyElem24(Elem24* first, Elem24* last, Elem24* dest)
{
  if (first != last) {
    do {
      if (dest) {
        dest->mA = first->mA;
        dest->mB = first->mB;
        dest->mC = first->mC;
        dest->mD = first->mD;
        new ((void*)&dest->mSub) Sub24(first->mSub);
      }
      ++first;
      ++dest;
    } while (first != last);
  }
  return dest;
}

// @ 0x005d1450
Elem24* RelocateElem24Backward(Elem24* first, Elem24* last, Elem24* dest)
{
  if (last == first) return dest;
  do {
    --last;
    --dest;
    dest->mA = last->mA;
    dest->mB = last->mB;
    dest->mC = last->mC;
    dest->mD = last->mD;
    dest->mSub = last->mSub;
  } while (last != first);
  return dest;
}

// ---------------------------------------------------------------------------
// The nine reconstructed functions.

// @ 0x005d12c0  cSpine75::RecordBlockCoordinates
cSpine75* cSpine75::RecordBlockCoordinates(const cSpine75& other)
{
  if (&other != this) {
    unsigned n = (unsigned)(other.mpCoordsEnd - other.mpCoordsBegin);
    if (n > (unsigned)(mpCoordsCap - mpCoordsBegin)) {
      Rec20* buf = FUN_005d0e40(n, other.mpCoordsBegin, other.mpCoordsEnd);
      if (mpCoordsBegin && ((int*)mpCoordsBegin)[-1]) {
        FUN_00f47380(mpCoordsBegin);
      }
      mpCoordsCap = buf + n;
      mpCoordsBegin = buf;
      mpCoordsEnd = buf + n;
    } else {
      unsigned sz = (unsigned)(mpCoordsEnd - mpCoordsBegin);
      if (n > sz) {
        copy_Rec20(other.mpCoordsBegin, other.mpCoordsBegin + sz, mpCoordsBegin);
        Rec20Iter res = CopyE20(Rec20Iter(other.mpCoordsBegin + sz),
                                Rec20Iter(other.mpCoordsEnd),
                                Rec20Iter(mpCoordsEnd),
                                Rec20Iter(other.mpCoordsEnd));
        (void)res;
        mpCoordsEnd = mpCoordsBegin + n;
      } else {
        copy_Rec20(other.mpCoordsBegin, other.mpCoordsEnd, mpCoordsBegin);
        mpCoordsEnd = mpCoordsBegin + n;
      }
    }
  }
  return this;
}

// @ 0x005d14a0  cSpine75::DisableBody
void cSpine75::FUN_005d14a0()
{
  int n = (int)(mLimbs.mpEnd - mLimbs.mpBegin);
  for (int i = 0; i < n; ++i) {
    mLimbs.mpBegin[i]->Release();
    cSPEditorLimbStructure* limb = mLimbs.mpBegin[i];
    if (limb) {
      limb->Destroy();
      FUN_00f47380(limb);
    }
    mLimbs.mpBegin[i] = 0;
  }
  cSPEditorLimbStructure** s = mLimbs.mpEnd;
  cSPEditorLimbStructure** d = mLimbs.mpBegin;
  memcpy(d, s, (unsigned)((char*)mLimbs.mpEnd - (char*)s));
  mLimbs.mpEnd -= (s - d);
}

// @ 0x005d1530  cSpine75::EnableBody
void cSpine75::FUN_005d1530()
{
  FUN_005d14a0();
  int i = 0;
  LimbVector limbs;
  limbs.mpBegin = 0;
  limbs.mpEnd = 0;
  limbs.mpCapacity = 0;
  FUN_004a0020(mpBlockHead, &limbs, false);
  int n = (int)(limbs.mpEnd - limbs.mpBegin);
  for (i = 0; i < n; ++i) {
    void* mem = FUN_00f473a0(0x54, "Editor", 0, 0, 0, 0);
    cSPEditorLimbStructure* limb;
    if (mem) limb = new (mem) cSPEditorLimbStructure();
    else limb = 0;
    limb->BuildLimb((cSPEditorBlock*)limbs.mpBegin[i], 0, false);
    if (mLimbs.mpEnd < mLimbs.mpCapacity) {
      cSPEditorLimbStructure** slot = mLimbs.mpEnd;
      mLimbs.mpEnd = slot + 1;
      if (slot) *slot = limb;
    } else {
      mLimbs.Grow(mLimbs.mpEnd, &limb);
    }
  }
  if (limbs.mpBegin && ((int*)limbs.mpBegin)[-1]) {
    FUN_00f47380(limbs.mpBegin);
  }
}

// @ 0x005d1600  cSpine75::SetFlag
void cSpine75::SetFlag(bool enable, int)
{
  if (enable) {
    if (!mFieldC5) {
      EnableBody();
      mFieldC5 = true;
    }
  } else {
    if (mFieldC5) {
      DisableBody();
      mFieldC5 = false;
    }
  }
}

// @ 0x005d1640  cSpine75::FUN_005d1640
bool cSpine75::FUN_005d1640()
{
  if (!mpCurve120 || !mpCurve124) return false;
  cSPEditorBlock* block = mpBlockHead;
  while (block) {
    FixedBlockVector children;
    children = block->mChildren;
    int n = (int)(children.mpEnd - children.mpBegin);
    for (int i = 0; i < n; ++i) {
      cSPEditorBlock* child = children.mpBegin[i];
      if (child) child->AddRef();
      if (!((child->mFlags >> 7) & 1)) {
        Vec2 res;
        NearestParam(&res, child);
        child->mFieldDC0 = res.x;
        child->mFieldDC4 = res.y;
      }
      child->Release();
    }
    block = FUN_004a5970(block);
    for (cSPEditorBlock** it = children.mpBegin; it < children.mpEnd; ++it) {
      if (*it) (*it)->Release();
    }
    if (children.mpBegin && ((int*)children.mpBegin)[-1]) {
      FUN_00f47380(children.mpBegin);
    }
  }
  return true;
}

// @ 0x005d1780  cSpine75::FUN_005d1780
void cSpine75::FUN_005d1780(const FloatSpan* xs, const FloatSpan* ys)
{
  U32Vector blocks;
  blocks.mpBegin = 0;
  blocks.mpEnd = 0;
  blocks.mpCapacity = 0;
  if (!mpCurve120 || !mpCurve124) return;
  int count = (int)(xs->mpEnd - xs->mpBegin);
  float lo = xs->mpBegin[0];
  float hi = xs->mpBegin[count - 1];
  cSPEditorBlock* block = mpBlockHead;
  while (block) {
    FixedBlockVector children;
    children = block->mChildren;
    int n = (int)(children.mpEnd - children.mpBegin);
    for (int i = 0; i < n; ++i) {
      cSPEditorBlock* child = children.mpBegin[i];
      if (child) child->AddRef();
      if (!((child->mFlags >> 7) & 1) && lo <= child->mFieldDC0 && child->mFieldDC0 < hi) {
        unsigned val = (unsigned)child;
        if (blocks.mpEnd < blocks.mpCapacity) {
          unsigned* slot = blocks.mpEnd;
          blocks.mpEnd = slot + 1;
          if (slot) *slot = val;
        } else {
          blocks.DoInsertValueI(blocks.mpEnd, val);
        }
      }
      child->Release();
    }
    block = FUN_004a5970(block);
    for (cSPEditorBlock** it = children.mpBegin; it < children.mpEnd; ++it) {
      if (*it) (*it)->Release();
    }
    if (children.mpBegin && ((int*)children.mpBegin)[-1]) {
      FUN_00f47380(children.mpBegin);
    }
  }
  int nb = (int)(blocks.mpEnd - blocks.mpBegin);
  for (int i = 0; i < nb; ++i) {
    cSPEditorBlock* b = (cSPEditorBlock*)blocks.mpBegin[i];
    float v = b->mFieldDC0;
    int k = 0;
    while (v > xs->mpBegin[k + 1]) ++k;
    float ny = (v - xs->mpBegin[k]) / (xs->mpBegin[k + 1] - xs->mpBegin[k]) *
                   (ys->mpBegin[k + 1] - ys->mpBegin[k]) + ys->mpBegin[k];
    float oldY = b->mFieldDC4;
    b->mFieldDC0 = ny;
    b->mFieldDC4 = oldY;
  }
  if (blocks.mpBegin && ((int*)blocks.mpBegin)[-1]) {
    FUN_00f47380(blocks.mpBegin);
  }
}

// @ 0x005d19e0  cSpine75::RepinArea
void cSpine75::RepinArea(float lo, float hi, int a4)
{
  U32Vector blocks;
  blocks.mpBegin = 0;
  blocks.mpEnd = 0;
  blocks.mpCapacity = 0;
  if (!mpCurve120 || !mpCurve124) return;
  cSPEditorBlock* block = mpBlockHead;
  while (block) {
    FixedBlockVector children;
    children = block->mChildren;
    int n = (int)(children.mpEnd - children.mpBegin);
    for (int i = 0; i < n; ++i) {
      cSPEditorBlock* child = children.mpBegin[i];
      if (child) child->AddRef();
      if (!((child->mFlags >> 7) & 1) && lo <= child->mFieldDC0 && child->mFieldDC0 <= hi) {
        unsigned val = (unsigned)child;
        if (blocks.mpEnd < blocks.mpCapacity) {
          unsigned* slot = blocks.mpEnd;
          blocks.mpEnd = slot + 1;
          if (slot) *slot = val;
        } else {
          blocks.DoInsertValueI(blocks.mpEnd, val);
        }
      }
      child->Release();
    }
    block = FUN_004a5970(block);
    for (cSPEditorBlock** it = children.mpBegin; it < children.mpEnd; ++it) {
      if (*it) (*it)->Release();
    }
    if (children.mpBegin && ((int*)children.mpBegin)[-1]) {
      FUN_00f47380(children.mpBegin);
    }
  }
  int nb = (int)(blocks.mpEnd - blocks.mpBegin);
  for (int i = 0; i < nb; ++i) {
    cSPEditorBlock* b = (cSPEditorBlock*)blocks.mpBegin[i];
    Extrude(b, b->mFieldDC0, b->mFieldDC4, a4);
  }
  if (blocks.mpBegin && ((int*)blocks.mpBegin)[-1]) {
    FUN_00f47380(blocks.mpBegin);
  }
}

// @ 0x005d1ba0  cSpine75::FUN_005d1ba0
void cSpine75::FUN_005d1ba0()
{
  cSPEditorBlock* block = mpBlockHead;
  while (block && block != mpBlockTail) {
    PhotoTypeInfo* v1 = mMap.Find((unsigned)block);
    cSPEditorBlock* next = FUN_004a5970(block);
    PhotoTypeInfo* v2 = mMap.Find((unsigned)next);
    if (v2) {
      float t = ((next->mScale + block->mScale) * F_01471064) / mField98;
      if (t < 0.0f) t = 0.0f;
      if (1.0f < t) t = 1.0f;
      float s = (mField94 - mField90) * (1.0f - t) + mField90;
      float* xf = *(float**)((char*)v1->mp4 + 0xc);
      xf[3] = mField88 * s;
      xf[4] = mField8c * s;
    }
    block = next;
  }
}

// @ 0x005d1d40  cSpine75::FUN_005d1d40
void cSpine75::FUN_005d1d40()
{
  int i = 0;
  cSPEditorBlock* block = mpBlockHead;
  while (block) {
    PhotoTypeInfo* v = mMap.Find((unsigned)block);
    v->mIntC = i;
    int r = FUN_005efd70(i);
    float rad = FUN_004a5b70(block->mScale);
    float f = mField11c;
    int rounded = (int)((rad * F_013ec488) / ((f + f) * F_013f8950 + f));
    unsigned packed = ((unsigned)((mField34 << 11) | r) << 5) |
                      (unsigned)((mField74 - rounded) << 10) | 2u;
    ((HavokBody*)v->mp0)->mHandle = (int)packed;
    ++i;
    block = FUN_004a5970(block);
  }
  mpWorld->updateCollisionFilterOnWorld(0, 1);
}

// @ 0x005d1e70  cSpine75::FUN_005d1e70
void cSpine75::FUN_005d1e70()
{
  if (mHandle38) {
    cSPEditorBlock* block = mpBlockHead;
    while (block) {
      PhotoTypeInfo* v = mMap.Find((unsigned)block);
      if (v->mp4) {
        uchar out;
        mpWorld->removeConstraint(&out, v->mp4);
        v->mp4 = 0;
      }
      block = FUN_004a5970(block);
    }
    uchar out2;
    mpWorld->removeConstraint(&out2, (void*)mHandle38);
  }
  mHandle38 = 0;
}

}  // namespace SP
