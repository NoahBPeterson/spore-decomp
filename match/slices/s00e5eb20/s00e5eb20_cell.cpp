// Slice s00e5eb20, second TU: SP cell game helpers (SPCellGame.obj).
// Retail module: /O2 /MD /Gy /TP /arch:SSE /fp:fast, no /EHsc (there is no EH funclet in this region).
#include "types.h"
#include <math.h>
#pragma intrinsic(sqrt)

struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };

// ---- retail data (absolute addresses; chk.py masks the relocations) ------------------------
extern const float gKSignMask;      // 0x013eb8b0  sign bit
extern const float gKAxisX;         // 0x015a7c34  0.0f
extern const float gKAxisY;         // 0x015a7c38  1.0f
extern const float gKAxisZ;         // 0x015a7c3c  0.0f
extern const Vector3 gKUp;          // 0x015a7c40  (0,0,0)
extern const Vector3 gKSpawnPos;    // 0x015a7d3c  (100,100,100)
extern const float gKEpsilon;       // 0x013ec4b8  1e-8f
extern const float gKPi;            // 0x015a7c24
extern float       gKTwoPi;         // 0x016b3dd0  runtime-initialised
extern const float gKZero;          // 0x01485378  0.0f
extern const float gKOne;           // 0x01485720  1.0f
extern const float gKOneSpawn;      // 0x015a8438  1.0f
extern const float gKHalf;          // 0x01471064  0.5f
extern const float gKTwo;           // 0x01470f1c  2.0f
extern const float gKFive;          // 0x01486110  5.0f
extern const float gKTen;           // 0x01473c70  10.0f
extern const float gKEight;         // 0x01483f64  8.0f
extern const float gKBoxScale;      // 0x013f6a20  0.85f
extern const float gKLevelSize[];   // 0x01483bd0
extern const int   gKLevelTable[];  // 0x01483c14  (7 ints per level entry)
extern float       gCellBox[6];     // 0x016b3c88
extern float       gCellBgBox[6];   // 0x016b3ca0

struct cObjectPool;
struct cCellGame;
struct cCellGfx;
struct cCell;
struct cAttachment;
struct cLayerCatalog;
struct cHandleRef;
struct cAdvectMap;

extern cCellGame* gspCellGame;      // 0x016b3c04
extern cCellGfx*  gspCellGfx;       // 0x016b3c0c
extern int        gCell516c;        // 0x016b3c10  pool-0x54 handle used by the spawn path

// ---- engine helpers referenced by this TU ------------------------------------------------
namespace SP {
void  __cdecl sCellSetPosition(cCell* cell, const Vector3* pos);             // 0x00e5e590
void  __cdecl sCellSetOrientation(cCell* cell, const Quaternion* orient);    // 0x00e5e850
float __cdecl sGetBoxSizeMultiplier2(int level, unsigned flags);             // 0x00e51ff0
void  __cdecl sCellGetFacing(float* out, const cCell* cell);                 // 0x00e5eb20 (own TU)
}

void  __cdecl normalized_safe(Vector3* out, const Vector3* in);              // 0x00449c20
float __cdecl RaySphereIntersect(const float* ray, const Vector3* center,
                                 const Vector3* up);                         // 0x006994a0
Vector3 __cdecl operator*(const Vector3& v, const Quaternion& q);            // 0x0059aed0
void  __cdecl QuaternionFromFacingAndUp(Quaternion* out, const Vector3* facing,
                                        const Vector3* up);                  // 0x0069b600
float __cdecl FUN_01041cd0(float lo, float hi, float t);                     // 0x01041cd0
void  __cdecl FUN_00e56870();                                                // 0x00e56870
int   __cdecl FUN_00e58ef0(int* level, float* a, float* b, float* c);        // 0x00e58ef0
int   __cdecl FUN_00e58e30();                                                // 0x00e58e30
void  __cdecl LoadAdvectMap(int level, cAdvectMap** out);                    // 0x00e4cc50
void  __cdecl PreloadAdvectMap(int level);                                   // 0x00e4ced0
cLayerCatalog* __cdecl FUN_00e4ce40(cHandleRef* ref);                        // 0x00e4ce40

// ---- layouts ----------------------------------------------------------------------------
struct cObjectPool {
  char mReserved[0x38];
  void* GetSafe(int handle);      // 0x00b721d0  thiscall
  void* Get(int handle);          // 0x00b72210  thiscall
  int   Alloc();                  // 0x00b72160  thiscall
};

struct cLevelInfo {
  char mReserved[0x1c];
  int  mStage;                    // +0x1c
};

struct cCellGame {
  cAdvectMap* mpAdvectMap;        // +0x0000
  float       mLevelScale;        // +0x0004
  char        mReserved08[4];
  float       mAdvect0c;          // +0x000c
  float       mAdvect10;          // +0x0010
  float       mAdvect14;          // +0x0014
  float       mAdvect18;          // +0x0018
  cObjectPool mCells;             // +0x001c
  cObjectPool mPool54;            // +0x0054
  cObjectPool mAttachPool;        // +0x008c
  char        mReservedC4[0x4114 - 0xc4];
  int         mField4114;         // +0x4114
  char        mReserved4118[0x411c - 0x4118];
  int         mPlayerCell;        // +0x411c
  char        mReserved4120[0x514c - 0x4120];
  float       mCellSize;          // +0x514c
  char        mReserved5150[0x516c - 0x5150];
  int         mCell516c;          // +0x516c
  char        mReserved5170[0x5190 - 0x5170];
  cLevelInfo* mpLevelInfo;        // +0x5190
  char        mReserved5194[0x51db - 0x5194];
  char        mFlag51db;          // +0x51db
};

struct cCellGfx {
  char  mReserved00[0x80];
  float mField80;                 // +0x80
  char  mReserved84[0xe0 - 0x84];
  int   mFieldE0;                 // +0xe0
  char  mReservedE4[0xf4 - 0xe4];
  float mFieldF4;                 // +0xf4
};

struct cCell {
  int        mHandle;             // +0x000
  char       mFlag04;             // +0x004
  char       mReserved05[3];
  float      mTargetX;            // +0x008
  float      mTargetY;            // +0x00c
  float      mTargetZ;            // +0x010
  Quaternion mQuat;               // +0x014
  char       mReserved24[0x4c - 0x24];
  Vector3    mPosition;           // +0x04c
  float      mRadius;             // +0x058
  float      mOrient[9];          // +0x05c
  char       mReserved80[0x16c - 0x80];
  char       mFlag16c;            // +0x16c
  char       mReserved16d[0x170 - 0x16d];
  int        mOwner;              // +0x170
  char       mReserved174[0x178 - 0x174];
  char       mFlag178;            // +0x178
  char       mReserved179[0x17b - 0x179];
  char       mFlag17b;            // +0x17b
  char       mFlag17c;            // +0x17c
  char       mReserved17d[0x18c - 0x17d];
  int        mMode;               // +0x18c
  char       mReserved190[0x1ac - 0x190];
  char       mFlag1ac;            // +0x1ac
  char       mReserved1ad[0x36c - 0x1ad];
  int        mAttachSlot;         // +0x36c
  int        mAttachHandle;       // +0x370
};

struct cSPTransform {
  char mReserved[0x38];
  void Assign(const void* src);   // 0x00537dc0  thiscall, ret 4
};

struct cAttachment {
  int          mReserved0;
  int          mField4;           // +0x04
  int          mField8;           // +0x08
  int          mFieldC;           // +0x0c
  cSPTransform mTransform;        // +0x10
  char         mFlag48;           // +0x48
};

struct cHandleRef {
  cHandleRef();                   // 0x00743b50
  ~cHandleRef();                  // 0x00e82130
  int mValue;
};

struct cLayerCatalog {
  char mReserved[0xdc];
  int  mCount;                    // +0xdc
};

struct cAdvectMap {
  virtual void Destroy();         // slot 0
  virtual void Release();         // slot 1  (0x01c)
  char mReserved4[4];
  int  mLevel;                    // +0x08
};

struct cCellSpawnParams {
  char  mReserved[0x1c];
  float mField1c;                 // +0x1c
};

struct cBlock {
  int mFlags;                     // +0x00
  int mIdx;                       // +0x04
  int mRow;                       // +0x08
  int mCol;                       // +0x0c
};

struct cBlockRef {
  int mFlags;                     // +0x00
  int mIdx;                       // +0x04
  int mX;                         // +0x08
  int mY;                         // +0x0c
  int mPad10;                     // +0x10
};

static __forceinline int FloorF(float v) {
  int i;
  __asm { movss xmm0, v
          cvtss2si eax, xmm0
          mov i, eax }
  if (v < (float)i) i = i - 1;
  return i;
}

static __forceinline int CeilF(float v) {
  int i;
  __asm { movss xmm0, v
          cvtss2si eax, xmm0
          mov i, eax }
  if ((float)i < v) i = i + 1;
  return i;
}

namespace SP {

// @ 0x00e5ec10
static bool sCellBeginSpawn(int handle) {
  cObjectPool& cells = gspCellGame->mCells;
  cCell* cell = (cCell*)cells.GetSafe(handle);
  if (!cell)
    return false;
  gspCellGame->mFlag51db = 1;
  cell->mFlag178 = 1;
  cell->mFlag17c = 1;
  cell->mFlag17b = 1;
  cell->mMode = 0x2b;
  cell->mFlag1ac = 0;
  sCellSetPosition(cell, &gKSpawnPos);
  return true;
}

// @ 0x00e5ec70
static bool sCellSpawn44(int handle, float dist) {
  cObjectPool& cells = gspCellGame->mCells;
  cCell* cell = (cCell*)cells.GetSafe(handle);
  if (!cell)
    return false;
  int n;
  {
    cHandleRef ref;
    n = FUN_00e4ce40(&ref)->mCount;
  }
  if (n == 0) {
    cObjectPool& pool54 = gspCellGame->mPool54;
    void* found = pool54.GetSafe(gCell516c);
    if (gKOneSpawn > dist && found == 0)
      FUN_00e56870();
  }
  cell->mFlag178 = 1;
  cell->mFlag17c = 1;
  cell->mFlag17b = 1;
  cell->mMode = 0x2c;
  cell->mFlag1ac = 0;
  sCellSetPosition(cell, &gKSpawnPos);
  return true;
}

// @ 0x00e5ed20
void __cdecl sCellSetOrientationHandle(int handle, const Quaternion* orient) {
  cObjectPool& cells = gspCellGame->mCells;
  cCell* cell = (cCell*)cells.GetSafe(handle);
  if (cell)
    sCellSetOrientation(cell, orient);
}

// @ 0x00e5ed50
bool __cdecl sCellOrientToward(int handle, const float* from, const Quaternion* orient,
                               float num, float den) {
  cObjectPool& cells = gspCellGame->mCells;
  cCell* cell = (cCell*)cells.GetSafe(handle);
  if (!cell)
    return false;
  cell->mFlag178 = 1;
  switch (cell->mMode) {
  case 0x28:
    if (cell->mHandle != gspCellGame->mPlayerCell)
      break;
  case 0x00:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x30:
    cell->mMode = 0x2f;
  }
  Vector3 axis;
  axis.x = -gKAxisX;
  axis.y = -gKAxisY;
  axis.z = -gKAxisZ;
  const Vector3 dir = axis * *orient;
  const float u = gKOne - num / den;
  const float nz = from[2] + (-dir.z - from[2]) * u;
  const float ny = from[1] + (-dir.y - from[1]) * u;
  const float nx = from[0] + (-dir.x - from[0]) * u;
  const float s = (float)(1.0 / sqrt((double)(ny * ny + nz * nz + nx * nx)));
  Vector3 facing;
  facing.x = -(nx * s);
  facing.y = -(ny * s);
  facing.z = -(nz * s);
  Quaternion quat;
  QuaternionFromFacingAndUp(&quat, &facing, &gKUp);
  sCellSetOrientation(cell, &quat);
  return true;
}

// @ 0x00e5ef40
float __cdecl sCellRayAngle(cCell* cell) {
  float dir[3];
  sCellGetFacing(dir, cell);
  Vector3 axis;
  axis.x = -gKAxisX;
  axis.y = -gKAxisY;
  axis.z = -gKAxisZ;
  const Vector3 rot = axis * cell->mQuat;
  float d = RaySphereIntersect(dir, &rot, &gKUp);
  if (d >= gKPi)
    d -= gKTwoPi;
  return d;
}

// @ 0x00e5f010
void __cdecl sCellPullToward(int handleA, int handleB, float dist, char skipDistCheck) {
  cObjectPool& cells = gspCellGame->mCells;
  cCell* a = (cCell*)cells.GetSafe(handleA);
  cCell* b = (cCell*)cells.GetSafe(handleB);
  if (!b || !a)
    return;
  Vector3 delta;
  delta.x = a->mPosition.x - b->mPosition.x;
  delta.y = a->mPosition.y - b->mPosition.y;
  delta.z = a->mPosition.z - b->mPosition.z;
  if (skipDistCheck == 0 &&
      dist < (float)sqrt((double)(delta.z * delta.z + delta.x * delta.x + delta.y * delta.y))) {
    Vector3 dir;
    normalized_safe(&dir, &delta);
    Vector3 pos;
    pos.x = b->mPosition.x + dir.x * dist;
    pos.y = b->mPosition.y + dir.y * dist;
    pos.z = b->mPosition.z + dir.z * dist;
    sCellSetPosition(a, &pos);
  }
}

// @ 0x00e5f160
bool __cdecl sCellSetTargetAndCamera(int handleA, int handleB, cCellSpawnParams* params,
                                     float speed) {
  cCell* a;
  {
    cObjectPool& cells = gspCellGame->mCells;
    a = (cCell*)cells.GetSafe(handleA);
  }
  if (!a) {
    if (params->mField1c > gKEight)
      params->mField1c = gKEight;
  }
  cCell* b;
  {
    cObjectPool& cells = gspCellGame->mCells;
    b = (cCell*)cells.GetSafe(handleB);
  }
  cCell* cam = (cCell*)gspCellGame->mCells.GetSafe(gspCellGame->mCell516c);
  if (cam) {
    gspCellGfx->mFieldE0 = gspCellGame->mCell516c;
    gspCellGfx->mFieldF4 = gKFive;
    gspCellGfx->mField80 = gKTen;
    if (b) {
      const float dx = b->mPosition.x - cam->mPosition.x;
      const float dy = b->mPosition.y - cam->mPosition.y;
      const float dz = b->mPosition.z - cam->mPosition.z;
      const float s =
          (float)(1.0 / sqrt((double)(dz * dz + dy * dy + dx * dx + gKEpsilon)));
      b->mTargetY = b->mPosition.y + dy * s * gKTen;
      b->mTargetX = b->mPosition.x + dx * s * gKTen;
      b->mTargetZ = b->mPosition.z + dz * s * gKTen;
      Vector3 pos;
      pos.x = b->mPosition.x + dx * s * gKTwo * speed;
      pos.y = b->mPosition.y + dy * s * gKTwo * speed;
      pos.z = b->mPosition.z + dz * s * gKTwo * speed;
      sCellSetPosition(b, &pos);
    }
  }
  cCell* player = (cCell*)gspCellGame->mCells.GetSafe(gspCellGame->mPlayerCell);
  if (player) {
    player->mOwner = handleA;
    player->mFlag178 = 1;
    player->mFlag17c = 1;
    player->mFlag17b = 1;
    player->mFlag16c = 1;
    player->mFlag04 = 1;
  }
  return true;
}

// @ 0x00e5f360
void __cdecl sRecalcAdvectMap() {
  int level;
  float f1, f2, f3;
  const int want = FUN_00e58ef0(&level, &f1, &f2, &f3);
  const int cur = FUN_00e58e30();
  if (want) {
    gspCellGame->mLevelScale = gKLevelSize[level] / gspCellGame->mCellSize;
    gspCellGame->mAdvect0c = f1 * gKTwo;
    gspCellGame->mAdvect10 = f2 * gKTwo;
    gspCellGame->mAdvect14 = f3;
    gspCellGame->mAdvect18 = 0.0f;
  }
  cAdvectMap* map = gspCellGame->mpAdvectMap;
  if (map == 0 || map->mLevel != want) {
    if (map) {
      gspCellGame->mpAdvectMap = 0;
      map->Release();
    }
    LoadAdvectMap(want, &gspCellGame->mpAdvectMap);
  }
  if (want != cur)
    PreloadAdvectMap(cur);
}

// @ 0x00e5f450
int __cdecl sAttach(int type, int index, int parent, const void* xform, char flag) {
  const int handle = gspCellGame->mAttachPool.Alloc();
  if (handle == 0)
    return 0;
  cCell* cell;
  {
    cObjectPool& cells = gspCellGame->mCells;
    cell = (cCell*)cells.Get(parent);
  }
  cell->mAttachSlot = type;
  cell->mAttachHandle = handle;
  cAttachment* att;
  {
    cObjectPool& attachPool = gspCellGame->mAttachPool;
    att = (cAttachment*)attachPool.Get(handle);
  }
  att->mField4 = type;
  att->mField8 = index;
  att->mFieldC = parent;
  att->mTransform.Assign(xform);
  att->mFlag48 = flag;
  return handle;
}

// @ 0x00e5f4d0
static void sPull(int handle, float dist, float from, float to, const Vector3* target) {
  if (dist == 0.0f)
    return;
  cObjectPool& cells = gspCellGame->mCells;
  cCell* cell = (cCell*)cells.Get(handle);
  const float t = FUN_01041cd0(0.0f, to, from);
  const float cx = cell->mPosition.x;
  const float cy = cell->mPosition.y;
  const float cz = cell->mPosition.z;
  Vector3 pos;
  pos.x = cx + (target->x - cx) * t;
  pos.y = cy + (target->y - cy) * t;
  pos.z = cz + (target->z - cz) * t;
  sCellSetPosition(cell, &pos);
}

// @ 0x00e5f590
bool __cdecl sCellIsBehind(cCell* cell, const float* point) {
  float dir[3];
  sCellGetFacing(dir, cell);
  const float dx = point[0] - cell->mPosition.x;
  const float dy = point[1] - cell->mPosition.y;
  const float dz = point[2] - cell->mPosition.z;
  float dot = dx * dir[0];
  dot += dy * dir[1];
  dot += dz * dir[2];
  if (dot < 0.0f)
    return true;
  return false;
}

// @ 0x00e5f610
static void sCalcBoxExtents(int flags, int level, int* p1, int* p2, int* p3, int* p4) {
  float v1, v2, v3, v4;
  if (flags == 0) {
    const float m2 = (gCellBox[4] + gCellBox[1]) * gKHalf;
    const float m1 = (gCellBox[5] + gCellBox[2]) * gKHalf;
    const float m3 = (gCellBox[3] + gCellBox[0]) * gKHalf;
    const float u1 = gCellBox[3] - gCellBox[0];
    const float u2 = gCellBox[4] - gCellBox[1];
    (void)m1;
    v1 = m3 - u1;
    v2 = m2 - u2;
    v3 = u1 + m3;
    v4 = u2 + m2;
  } else {
    v1 = gCellBgBox[0];
    v2 = gCellBgBox[1];
    v3 = gCellBgBox[3];
    v4 = gCellBgBox[4];
  }
  const float scale = (gKLevelSize[level] / gspCellGame->mCellSize) *
                      (sGetBoxSizeMultiplier2(level, flags) * gKBoxScale);
  const float inv = gKOne / scale;
  *p1 = FloorF(inv * v1);
  *p2 = FloorF(inv * v2);
  *p3 = CeilF(inv * v3);
  *p4 = CeilF(inv * v4);
}

// @ 0x00e5f810
bool __cdecl sBlockIsInRange(const cBlock* box) {
  const int stage = gspCellGame->mpLevelInfo->mStage;
  int lo;
  if (stage == 1000) {
    lo = gKLevelTable[147];
  } else {
    int n = 0;
    if (stage >= 0) {
      const int* p = gKLevelTable + 8;
      do {
        p += 7;
        ++n;
      } while (stage >= *p);
    }
    lo = gKLevelTable[n * 7];
  }
  if (box->mIdx + 1 < lo || box->mIdx > lo + 5)
    return false;
  int o1, o2, o3, o4;
  sCalcBoxExtents(box->mFlags, box->mIdx, &o1, &o2, &o3, &o4);
  const int row = box->mRow;
  const int col = box->mCol;
  return o1 <= row && row < o3 && o2 <= col && col < o4;
}

// @ 0x00e5fa00
static int sBlockExtentFill(int a, int b, int flags, cBlockRef* out) {
  const int level = a + b;
  cBlockRef* rec = out;
  int o0, o1, o2, o3;
  sCalcBoxExtents(flags, level, &o0, &o1, &o2, &o3);
  for (int i = o0; i < o2; ++i) {
    for (int j = o1; j < o3; ++j) {
      rec->mX = i;
      rec->mY = j;
      rec->mIdx = level;
      rec->mFlags = flags;
      ++rec;
    }
  }
  return (o2 - o0) * (o3 - o1);
}

// Keeps the register-convention statics above emitted (they are called once each here).
bool __cdecl sCellHelpersAnchor(int handle, float dist, int flags, int level,
                                cCellSpawnParams* params, int handleB, const Vector3* target) {
  bool r = sCellBeginSpawn(handle);
  r = sCellSpawn44(handle, dist) || r;
  sPull(handle, dist, dist, dist, target);
  int p1, p2, p3, p4;
  sCalcBoxExtents(flags, level, &p1, &p2, &p3, &p4);
  cBlockRef refs[256];
  r = sBlockExtentFill(flags, level, p1, refs) != 0 || r;
  return sCellSetTargetAndCamera(handle, handleB, params, dist) || r;
}

}  // namespace SP
