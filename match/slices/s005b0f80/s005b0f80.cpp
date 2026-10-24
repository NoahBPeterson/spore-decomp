// slice s005b0f80 — SP::cSPEditorManipulationObject base (ctor, AsInterface, OnMouseDown,
// OnMouseMove) and the ray/sphere gathering helpers used by the editor manipulation objects.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "math.h"
#include "types.h"

// ---- helper types ---------------------------------------------------------
struct cSPEditorBlock;
struct cSPEditorModel;

// BBox returned by cSPEditorBlock::GetBBox (min.xyz then max.xyz).
struct BBox {
  float mnx, mny, mnz;   // +0x00
  float mxx, mxy, mxz;   // +0x0c
};

// vtable carrier for the object stored at cSPEditorBlock::mField3EC.
struct BlockVtblObject {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(void* out);
};

// cSPEditorModel (only the members touched by these functions).
struct cSPEditorModel {
  char  pad_00[0x28];
  void* mSpine;                       // +0x28
  float FUN_004adaa0();               // 0x4adaa0
};

// cSPEditorBlock (only the members touched by these functions).
struct cSPEditorBlock {
  char pad_00[0x28];
  cSPEditorModel* mModel;             // +0x28
  char pad_2c[0x48 - 0x2c];
  float mPosX, mPosY, mPosZ;          // +0x48
  char pad_54[0x340 - 0x54];
  uint32_t* mChildBegin;              // +0x340
  uint32_t* mChildEnd;                // +0x344
  char pad_348[0x3e0 - 0x348];
  void* mField3E0;                    // +0x3e0
  BlockVtblObject* mField3EC;         // +0x3ec
  float* mField3F0;                   // +0x3f0
  char pad_3f4[0xdc8 - 0x3f4];
  uint32_t mFlagsDC8;                 // +0xdc8
  float F_43f250();                   // 0x43f250
  float F4d0();                       // 0x43f4d0
  BBox  GetBBox(int a, bool b, int c); // 0x44ae00
};

// SPVector<unsigned int> (eastl-style, 3 words).
struct SPVectorU {
  uint32_t* mb;                        // +0x0 begin
  uint32_t* me;                        // +0x4 end
  uint32_t* mc;                        // +0x8 capacity
  void DoInsertValueI(uint32_t* pos, const uint32_t* value); // 0x4558a0
};

// ---- external callees -----------------------------------------------------
bool __cdecl IntersectRaySphere(const float* origin, const float* dir, const float* point,
                                float t, float* tOut);                     // 0x5a9c40
int  __cdecl FUN_011e0810(void);                                          // 0x11e0810
void* __cdecl SP_EditorUtils_FindRootSpine(cSPEditorModel* model);        // 0x4a5a70
void* __cdecl FUN_004a5970(void* block);                                  // 0x4a5970
float __cdecl SP_EditorUtils_GetSkinRadius(void* block);                  // 0x4a5c40
void __cdecl FUN_00f47380(void* p);                                       // 0xf47380 (operator delete)

// ---- globals --------------------------------------------------------------
extern float g_13f5c90;                                  // 0x13f5c90 (0.45f)
extern float g_1471064;                                  // 0x1471064 (0.5f)
extern float g_1477fbc;                                  // 0x1477fbc (~200.0f)
extern float g_14853e0;                                  // 0x14853e0 (4.0f)
extern float g_13f6a28;                                  // 0x13f6a28 (-4.0f)
extern float g_1485378;                                  // 0x1485378 (0.0f)
extern float g_15e97f8, g_15e97fc, g_15e9800;            // 0x15e97f8.. (direction)
extern float g_1488874;                                  // 0x1488874
extern float g_15e9874, g_15e9878, g_15e987c;            // 0x15e9874.. (direction)

// @ 0x005b0f80
struct MObj {
  virtual ~MObj() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  char pad_7;
  float mDeadZoneSize;   // +0x8
  float mInitialX;       // +0xc
  float mInitialY;       // +0x10
  MObj();
  void* AsInterface(int typeID);
  void OnMouseDown(int a1, float a2, float a3, int a4);
  bool OnMouseMove(float a1, float a2, int a3);
};
MObj::MObj()
    : mChangedObject(false), mUseDeadZone(true), mMovedOutsideDeadZone(false),
      mDeadZoneSize(2.0f), mInitialX(0.0f), mInitialY(0.0f) {}

// Base vtable layout of cSPEditorManipulationObject — just enough to name the
// dispatches at +0x18 (OnMouseDown) and +0x20 (OnMouseMove) without disturbing
// the byte-exact MObj constructor above.
struct MObjVtbl {
  virtual void v00();
  virtual void v04();
  virtual void v08();
  virtual void v0c();
  virtual void v10();
  virtual void v14();
  virtual void BaseOnMouseDown(int a1, float a2, float a3, int a4);  // +0x18
  virtual void v1c();
  virtual bool BaseOnMouseMove(float a1, float a2, int a3);          // +0x20
};

// @ 0x005b0fb0
void* MObj::AsInterface(int typeID) {
  void* result = this;
  if (typeID != 0xee3f516e)
    result = 0;
  return result;
}

// @ 0x005b0fd0
void MObj::OnMouseDown(int a1, float a2, float a3, int a4) {
  mInitialX = a2;
  mInitialY = a3;
  mMovedOutsideDeadZone = false;
  ((MObjVtbl*)this)->BaseOnMouseDown(a1, a2, a3, a4);
}

// @ 0x005b1010
bool MObj::OnMouseMove(float a1, float a2, int a3) {
  if (mUseDeadZone) {
    if (mMovedOutsideDeadZone == false &&
        mDeadZoneSize < sqrtf((a1 - mInitialX) * (a1 - mInitialX) +
                              (a2 - mInitialY) * (a2 - mInitialY)))
      mMovedOutsideDeadZone = true;
  }
  if (mUseDeadZone != false && mMovedOutsideDeadZone == false)
    return true;
  return ((MObjVtbl*)this)->BaseOnMouseMove(a1, a2, a3);
}

// @ 0x005b1080
struct S80 {
  float m0, m1, m2, m3, m4, m5;   // +0x0..+0x14
  bool  m18;                      // +0x18
  void Set(float a, float b, float c, float d, float e, float f);
  S80(float a, float b, float c, float d, float e, float f);
};
S80::S80(float a, float b, float c, float d, float e, float f)
    : m0(a), m1(b), m2(c), m3(d), m4(e), m5(f), m18(false) {}
void S80::Set(float a, float b, float c, float d, float e, float f) {
  S80* self = this;
  self->m0 = a; self->m1 = b; self->m2 = c; self->m3 = d; self->m4 = e; self->m5 = f;
  self->m18 = false;
}

// @ 0x005b10d0
struct Sd0 {
  float mOriginX, mOriginY, mOriginZ;   // +0x00
  float mDirX, mDirY, mDirZ;            // +0x0c
  bool  mHasBest;                       // +0x18
  char  pad_19[3];
  union { float mBestX; uint32_t mBestXBits; };     // +0x1c
  union { float mBestY; uint32_t mBestYBits; };     // +0x20
  union { float mBestZ; uint32_t mBestZBits; };     // +0x24
  union { float mBestDist; uint32_t mBestDistBits; }; // +0x28
  __declspec(noinline) void Consider(float x, float y, float z);
  __declspec(noinline) void FUN_005b1130(float a, float b, float c, float t);
  __declspec(noinline) void FUN_005b11e0(float px, float py, float pz, float dx, float dy, float dz, bool b);
  __declspec(noinline) void FUN_005b1310(float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9);
  __declspec(noinline) void FUN_005b15e0(cSPEditorBlock* block, cSPEditorBlock* other);
  __declspec(noinline) void FUN_005b1870(cSPEditorBlock* block, cSPEditorBlock* other,
                    float p3, float p4, float p5, float p6, float p7, float p8);
};
void Sd0::Consider(float x, float y, float z) {
  float dx = mOriginX - x;
  float dy = mOriginY - y;
  float dz = mOriginZ - z;
  float d = sqrtf(dx * dx + dy * dy + dz * dz);
  if (!mHasBest || d < mBestDist) {
    // The retail code copies the arguments with integer loads/stores (it leaves
    // eax = the z bits on return), so store the argument bit patterns instead
    // of using float moves.
    mBestXBits = *(uint32_t*)&x;
    mBestYBits = *(uint32_t*)&y;
    mHasBest = true;
    mBestDist = d;
    mBestZBits = *(uint32_t*)&z;
  }
}

// @ 0x005b1130
void Sd0::FUN_005b1130(float a, float b, float c, float t) {
  float local[3];
  local[0] = a;
  local[1] = b;
  local[2] = c;
  if (IntersectRaySphere(&mOriginX, &mDirX, local, t, &t)) {
    float px = mOriginX + mDirX * t;
    float py = mOriginY + mDirY * t;
    float pz = mOriginZ + mDirZ * t;
    Consider(px, py, pz);
  }
}

// @ 0x005b11e0
void Sd0::FUN_005b11e0(float px, float py, float pz, float dx, float dy, float dz, bool b) {
  if (!b || g_13f5c90 < fabsf(mDirZ * dz + mDirY * dy + mDirX * dx)) {
    float denom = mDirZ * dz + mDirY * dy + mDirX * dx;
    if (denom != g_1485378) {
      // Keep the retail association: inner = (py*dy + pz*dz) + px*dx and
      // outer = (mOriginZ*dz + mOriginY*dy) + mOriginX*dx; reassociating the
      // sums changes the last bit of the resulting t.
      float inner = (py * dy + pz * dz) + px * dx;
      float outer = (mOriginZ * dz + mOriginY * dy) + mOriginX * dx;
      float t = -((outer - inner) / denom);
      if (t >= g_1485378) {
        Consider(mOriginX + t * mDirX, mOriginY + t * mDirY, mOriginZ + t * mDirZ);
      }
    }
  }
}

// @ 0x005b1310
void Sd0::FUN_005b1310(float p2, float p3, float p4, float p5, float p6, float p7, float p8,
                       float p9) {
  int n = FUN_011e0810();
  if (n > 0) {
    float ox = mOriginX;
    float oy = mOriginY;
    float oz = mOriginZ;
    for (int i = 1; i <= n; i++) {
      float f = (float)i / (float)n;
      float f13 = oy - ((p7 - p3) * f + p3);
      float f12 = ox - ((p6 - p2) * f + p2);
      float f10 = oz - ((p8 - p4) * f + p4);
      float f11 = (p9 - p5) * f + p5;
      float f7 = mDirY * f13 + mDirZ * f10 + mDirX * f12;
      float f9 = mDirX * mDirX + mDirY * mDirY + mDirZ * mDirZ;
      float disc = f7 * f7 - (((f10 * f10 + f13 * f13) + f12 * f12) - f11 * f11) * f9;
      if (disc >= 0.0f) {
        float s = sqrtf(disc);
        float t0 = -f7 - s;
        if (0.0f <= s - f7) {
          float t = (t0 > 0.0f) ? t0 / f9 : 0.0f;
          float cx = ox + mDirX * t;
          float cy = oy + mDirY * t;
          float cz = oz + mDirZ * t;
          float e1 = ox - cx;
          float e2 = oy - cy;
          float e3 = oz - cz;
          float dist = sqrtf(e1 * e1 + (e2 * e2 + e3 * e3));
          if (mHasBest == false || dist < mBestDist) {
            mBestX = cx;
            mBestY = cy;
            mBestZ = cz;
            mHasBest = true;
            mBestDist = dist;
          }
        }
      }
    }
  }
}

// @ 0x005b15e0
void Sd0::FUN_005b15e0(cSPEditorBlock* block, cSPEditorBlock* other) {
  if (((block->mFlagsDC8 >> 0xb) & 1) == 0) {
    if (block != other) {
      BBox bb = block->GetBBox(1, 0, 0);
      float cx = block->mPosX + (bb.mxx + bb.mnx) * 0.5f;
      float cy = block->mPosY + (bb.mxy + bb.mny) * 0.5f;
      float cz = block->mPosZ + (bb.mxz + bb.mnz) * 0.5f;
      BBox bb2 = block->GetBBox(1, 0, 0);
      float rad = sqrtf(bb2.mnx * bb2.mnx + (bb2.mny * bb2.mny + bb2.mnz * bb2.mnz)) * 0.5f;
      FUN_005b1130(cx, cy, cz, rad);
    }
  } else if (block != other) {
    cSPEditorBlock* ob3e0 = (cSPEditorBlock*)other->mField3E0;
    if (block != ob3e0) {
      int count = (int)(block->mChildEnd - block->mChildBegin) >> 2;
      int i = 0;
      bool found = false;
      if (0 < count) {
        do {
          cSPEditorBlock* ch = (cSPEditorBlock*)block->mChildBegin[i];
          if (ch == other || ch == ob3e0) {
            found = true;
            break;
          }
          i = i + 1;
        } while (i < count);
      }
      float L[3];
      if (found) {
        block->mField3EC->v24(L);
        float f = block->F_43f250();
        FUN_005b1130(L[0], L[1], L[2], f);
      } else {
        block->mField3EC->v24(L);
        float E[3];
        E[0] = block->mField3F0[3];
        E[1] = block->mField3F0[4];
        E[2] = block->mField3F0[5];
        float f6 = block->F_43f250();
        float f7 = block->F4d0();
        FUN_005b1310(L[0], L[1], L[2], f6, E[0], E[1], E[2], f7);
      }
    }
  }
  {
    int count = (int)(block->mChildEnd - block->mChildBegin) >> 2;
    int i = 0;
    if (0 < count) {
      do {
        FUN_005b15e0((cSPEditorBlock*)block->mChildBegin[i], other);
        i = i + 1;
      } while (i < count);
    }
  }
}

// @ 0x005b1870
void Sd0::FUN_005b1870(cSPEditorBlock* block, cSPEditorBlock* other,
                       float p3, float p4, float p5, float p6, float p7, float p8) {
  SPVectorU vec;
  vec.mb = 0;
  vec.me = 0;
  vec.mc = 0;
  void* cur = SP_EditorUtils_FindRootSpine(block->mModel);
  while (cur != 0) {
    if (vec.me < vec.mc) {
      uint32_t* pos = vec.me;
      vec.me = pos + 1;
      if (pos != 0)
        *pos = (uint32_t)cur;
    } else {
      vec.DoInsertValueI(vec.me, (const uint32_t*)&cur);
    }
    cur = FUN_004a5970(cur);
  }
  int count = (int)(vec.me - vec.mb) >> 2;
  int i = 0;
  if (0 < count) {
    do {
      cSPEditorBlock* b = (cSPEditorBlock*)vec.mb[i];
      int cc = (int)(b->mChildEnd - b->mChildBegin) >> 2;
      int j = 0;
      if (0 < cc) {
        do {
          FUN_005b15e0((cSPEditorBlock*)b->mChildBegin[j], other);
          j = j + 1;
        } while (j < cc);
      }
      BBox bb = b->GetBBox(0, 0, 0);
      float rad = SP_EditorUtils_GetSkinRadius(b);
      float cx = (bb.mxx + bb.mnx) * 0.5f;
      float cy = (bb.mxy + bb.mny) * 0.5f;
      float cz = (bb.mxz + bb.mnz) * 0.5f;
      FUN_005b1310(cx, cy, cz, rad, cx, cy, g_1477fbc, rad);
      FUN_005b1310(cx, cy, cz, rad, cx, cy, 0.0f, rad * 0.5f);
      i = i + 1;
    } while (i < count);
  }
  FUN_005b11e0(0.0f, 0.0f, g_1488874, g_15e97f8, g_15e97fc, g_15e9800, false);
  if (block->mModel != 0) {
    float f = block->mModel->FUN_004adaa0();
    FUN_005b11e0(0.0f, f * g_14853e0, 0.0f,
                 -g_15e9874, -g_15e9878, -g_15e987c, true);
    FUN_005b11e0(0.0f, f * g_13f6a28, 0.0f,
                 g_15e9874, g_15e9878, g_15e987c, true);
    FUN_005b11e0(p3 + p6 * f * g_14853e0, p4 + p7 * f * g_14853e0, p5 + p8 * f * g_14853e0,
                 -p6, -p7, -p8, true);
  }
  if (vec.mb != 0 && ((int*)vec.mb)[-1] != 0) {
    FUN_00f47380(vec.mb);
  }
}

// @ 0x005b1c80
int __cdecl FUN_005b1c80(const float* a, const float* b) {
  return !(a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3]);
}

// @ 0x005b1cd0
void __cdecl FUN_005b1cd0(float* out, const float* a, const float* b, float t) {
  float dot = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
  if (dot > 0.0f) {
    out[0] = a[0] + (b[0] - a[0]) * t;
    out[1] = a[1] + (b[1] - a[1]) * t;
    out[2] = a[2] + (b[2] - a[2]) * t;
    out[3] = a[3] + (b[3] - a[3]) * t;
  } else {
    float nt = -t;
    out[0] = a[0] + (a[0] + b[0]) * nt;
    out[1] = a[1] + (a[1] + b[1]) * nt;
    out[2] = a[2] + (a[2] + b[2]) * nt;
    out[3] = a[3] + (a[3] + b[3]) * nt;
  }
}