// src/game/SPGonzago/_at_00e80000.cpp -- migrated from slice(s) s00e8d0e0, s00e8b7a0, s00e86d40, s00e85dc0, s00e855e0, s00e84850, s00e819b0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00e80000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "SP/cGonzagoTimer.h"
#include "SP/cSpatialObject.h"

// unnamed retail callees and globals (address in the comment)
extern int* gListSentinel;        // 0x016b44f0
extern int* gField_15fd918;               // 0x015fd918

// ---- items of slice s00e819b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int* gListSentinel;        // 0x016b44f0
int   FUN_00f473a0(int sz, const char* name, int a, int b, int c, int d);  // operator new
struct C006a17e0 { void FUN_006a17e0(int a, int b); };
extern int* gField_15fd918;               // 0x015fd918
// ---- items of slice s00e819b0 end

// ---- items of slice s00e84850 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
class cHeaderPart {
public:
    uint32_t mFlags;                                     // +0x00
};
class cLinkBody {
public:
    uint8_t mPayload[0x10];                              // +0x000
};
class cUIElement : public cHeaderPart, public cLinkBody {
public:
    void FUN_00812d90();                                 // 0x00812d90
};
class cWindow {
public:
    virtual void v000();                                 // +0x00
    virtual cLinkBody* GetLink();                        // +0x04
};
extern cWindow* __cdecl WindowManager();                 // 0x0067caa0
// ---- items of slice s00e84850 end

// ---- items of slice s00e855e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 {
    float x, y, z;
};
void __cdecl ComputeCenterOfMass(int n, const Vector3* positions, const float* masses,
                                 Vector3* center);
void* __cdecl FUN_011e073e(void* dst, int value, unsigned size);
// ---- items of slice s00e855e0 end

// ---- items of slice s00e85dc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s00e8_5dc0 {
  float x, y, z;
  Vector3_s00e8_5dc0() {}
  Vector3_s00e8_5dc0(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
  Vector3_s00e8_5dc0(const Vector3_s00e8_5dc0& v) : x(v.x), y(v.y), z(v.z) {}
  Vector3_s00e8_5dc0 operator+(const Vector3_s00e8_5dc0& v) const { return Vector3_s00e8_5dc0(x + v.x, y + v.y, z + v.z); }
  Vector3_s00e8_5dc0 operator-(const Vector3_s00e8_5dc0& v) const { return Vector3_s00e8_5dc0(x - v.x, y - v.y, z - v.z); }
  Vector3_s00e8_5dc0 operator*(float f) const { return Vector3_s00e8_5dc0(x * f, y * f, z * f); }
};
struct Matrix3 {
  Vector3_s00e8_5dc0 r[3];
  Matrix3() {}
  Matrix3(const Vector3_s00e8_5dc0& r0, const Vector3_s00e8_5dc0& r1, const Vector3_s00e8_5dc0& r2) { r[0] = r0; r[1] = r1; r[2] = r2; }
  Matrix3 operator+(const Matrix3& m) const { return Matrix3(r[0] + m.r[0], r[1] + m.r[1], r[2] + m.r[2]); }
  Matrix3 operator*(float f) const { return Matrix3(r[0] * f, r[1] * f, r[2] * f); }
  __forceinline Matrix3 operator*(const Matrix3& m) const {
    // Retail sums the three terms of row i starting at column (i+1)%3: row 0 (y,z,x),
    // row 1 (z,x,y), row 2 (x,y,z).  Parenthesise to keep that rounding order.
    return Matrix3(
        Vector3_s00e8_5dc0((r[0].y * m.r[1].x + r[0].z * m.r[2].x) + r[0].x * m.r[0].x,
                (r[0].y * m.r[1].y + r[0].z * m.r[2].y) + r[0].x * m.r[0].y,
                (r[0].y * m.r[1].z + r[0].z * m.r[2].z) + r[0].x * m.r[0].z),
        Vector3_s00e8_5dc0((r[1].z * m.r[2].x + r[1].x * m.r[0].x) + r[1].y * m.r[1].x,
                (r[1].z * m.r[2].y + r[1].x * m.r[0].y) + r[1].y * m.r[1].y,
                (r[1].z * m.r[2].z + r[1].x * m.r[0].z) + r[1].y * m.r[1].z),
        Vector3_s00e8_5dc0((r[2].x * m.r[0].x + r[2].y * m.r[1].x) + r[2].z * m.r[2].x,
                (r[2].x * m.r[0].y + r[2].y * m.r[1].y) + r[2].z * m.r[2].y,
                (r[2].x * m.r[0].z + r[2].y * m.r[1].z) + r[2].z * m.r[2].z));
  }
};
inline Matrix3 Outer(const Vector3_s00e8_5dc0& a, const Vector3_s00e8_5dc0& b) { return Matrix3(b * a.x, b * a.y, b * a.z); }
inline Vector3_s00e8_5dc0 operator*(const Vector3_s00e8_5dc0& v, const Matrix3& m) {
  // Keep the original's per-component summation order: (x*col0 + z*col2) + y*col1
  // for x, (z*col2 + x*col0) + y*col1 for y, and (y*col1 + z*col2) + x*col0 for z.
  return Vector3_s00e8_5dc0(v.x * m.r[0].x + v.z * m.r[2].x + v.y * m.r[1].x,
                 v.z * m.r[2].y + v.x * m.r[0].y + v.y * m.r[1].y,
                 v.y * m.r[1].z + v.z * m.r[2].z + v.x * m.r[0].z);
}
extern const Vector3_s00e8_5dc0 kZeroVector;   // 0x016c4584
void ComputeCenterOfMass(int n, const Vector3_s00e8_5dc0* positions, const float* masses, Vector3_s00e8_5dc0* center);   // 0x00e853c0
void JacobiDecompose(const Matrix3& m, Matrix3& eigenvectors, Matrix3& diagonal);                 // 0x00e851c0
void __cdecl FUN_00f47380(void* p);                                                     // 0xf47380
struct NodePos {
  int x, y, z;
};
struct Node {
  union {
    NodePos pos;              // +0x00
    Node* freeNext;
  };
  float f;                    // +0x0c
  Node* parent;               // +0x10
  Node* next;                 // +0x14
  union {
    Node* right;              // +0x18
    int data;
  };
};
struct SpherePool {
  int count;                  // +0x00
  int end;                    // +0x04
  Node* freeHead;             // +0x08
  char* base;                 // +0x0c
  int stride;                 // +0x10
  int capacity;               // +0x14
};
struct SphereTree {
  int field00;                // +0x00
  SpherePool* pool;           // +0x04
  Node* root;                 // +0x08
  Node* head;                 // +0x0c
};
struct SimEntry {
  int key;                    // +0x00
  void* value;                // +0x04
  int field08;                // +0x08
  int field0c;                // +0x0c
};
struct SimulatorGlobal {
  int FUN_00b72160();
  SphereTree* FUN_00b72210(int);
  void FUN_00b72080(int a, int b);
  SimEntry* FUN_00b72230(int* key);
  void FUN_00b72260(int key);
  void FUN_00b720e0();
  int FUN_00e31100();
};
static __forceinline void FreeSphereNode(SphereTree* tree, Node* node)
{
  SpherePool* pool = tree->pool;
  pool->count--;
  node->freeNext = pool->freeHead;
  pool->freeHead = node;
}
// ---- items of slice s00e85dc0 end

// ---- items of slice s00e86d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kHalf;          // 0x01471064 (0.5f)
typedef unsigned char      u8;
struct EffRec {
    union {
        float   mCenter[3];  // +0x00  bounding-sphere centre
        EffRec* mpFreeNext;  // +0x00  free-list link (overlaps mCenter[0])
    };
    float   mRadius;         // +0x0c  bounding-sphere radius
    EffRec* mParent;         // +0x10  parent / free-list link
    EffRec* mChildA;         // +0x14  tree child A
    EffRec* mChildB;         // +0x18  tree child B
};
struct EffPool {
    int     mCount;          // +0x00  live records
    int     mNextUnused;     // +0x04  next never-used slot index
    EffRec* mpFreeList;      // +0x08  free list (linked through +0x14)
    u8*     mpBase;          // +0x0c
    int     mStride;         // +0x10
    int     mCapacity;       // +0x14
};
struct EffTree {
    EffRec*   mpRoot;        // +0x00
    EffPool*  mpPool;        // +0x04
    EffRec*   mpPending;     // +0x08  list of records to insert (linked through +0x10)
    EffRec*   mpToRemove;    // +0x0c  list of records to remove (linked through +0x14)
};
void  FUN_00e86930(EffTree* t, EffRec* n);                                      // 0x00e86930
void  FUN_00e86bb0(const float* a, float aR, const float* b, float bR,
                   float* out, float* outR);                                    // 0x00e86bb0
bool  IntersectRaySphere(const float* a, const float* b, const float* c,
                         float r, float* out);                                  // 0x005a9c40
struct cEffectWindow {
    int   GetPriority();                                  // 0x00e31100
    void* Remove(int* key);                               // 0x00b72230
};
extern cEffectWindow g_EffectWindow;                      // 0x016c45b4
// ---- items of slice s00e86d40 end

// ---- items of slice s00e8b7a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_vtbl_014863cc[];   // 0x014863cc  SP::cCreatureView vftable
typedef unsigned int   u32;
typedef int            i32;
class cCombatSub {
public:
    void** mpVtbl;              // +0x00
    u32  FUN_008e7f80();        // 0x008e7f80
    bool FUN_00bfc600();        // 0x00bfc600
};
class cCreature {
public:
    void** mpVtbl;              // +0x00
    char pad04[0x34 - 0x04];
    void** mpVtbl34;            // +0x34  polymorphic sub-object (slot 0x74 = a float)
    char pad38[0x6e - 0x38];
    u8   m6e;                   // +0x6e
    char pad6f[0x84 - 0x6f];
    u32  m84;                   // +0x84
    char pad88[0xc0 - 0x88];
    void** mpVtblC0;            // +0xc0  animation sub-object (slot 0x8c)
    char padC4[0x330 - 0xc4];
    u32  m330;                  // +0x330
    char pad334[0x588 - 0x334];
    cCombatSub mCombat;         // +0x588
    char pad58c[0x684 - 0x58c];
    i32  m684;                  // +0x684
    char pad688[0xb58 - 0x688];
    u32  mFlagsB58;             // +0xb58
    char padB5c[0xb5e - 0xb5c];
    u8   mB5e;                  // +0xb5e
    char padB5f[0xb61 - 0xb5f];
    u8   mB61;                  // +0xb61
    u8   mB62;                  // +0xb62
    char padB63[0xf90 - 0xb63];
    u8   mF90;                  // +0xf90

    // direct (non-virtual) members -------------------------------------------
    bool FUN_00c8b220(u32 a, u32 b, u32 c, u32 d);   // 0x00c8b220
    void FUN_00c88a00(u32 a, float f);               // 0x00c88a00
    void FUN_00c8a020(u32 a, float f);               // 0x00c8a020
    void FUN_00c88a30(u32 a, void* b);               // 0x00c88a30
    void* FUN_00c14e70(u32 id);                      // 0x00c14e70
    void FUN_00c17350(u32 id, u32 b);                // 0x00c17350
    void FUN_00c1d400(u32 a, u32 b);                 // 0x00c1d400
    void FUN_00c1d460(u32 a, u32 b);                 // 0x00c1d460
    bool FUN_00c0b780();                             // 0x00c0b780
    bool FUN_00c0b7a0();                             // 0x00c0b7a0
    bool FUN_00c0c0e0();                             // 0x00c0c0e0
    void FUN_00c201a0(bool v, u32 a, u32 b);         // 0x00c201a0
};
class cEffect {
public:
    char pad00[0x88];
    u32  m88;                   // +0x88
    void Release();             // 0x00a05270
};
namespace SP {
class cCreatureView {
public:
    void** mpVtbl;              // +0x00
    u32    m04;                 // +0x04
    u32    m08;                 // +0x08
    cCreature* mpCreature;      // +0x0c
    cEffect*   mpOverhead;      // +0x10
    u8     mb14;                // +0x14
    char   pad15[0x18 - 0x15];
    void*  mp18;                // +0x18

    cCreatureView();                                    // 0x00e8bc80
    void FUN_00e8bca0(cCreature* p);                    // 0x00e8bca0
    void FUN_00e8bd70(bool b);                          // 0x00e8bd70
    bool FUN_00e8bda0();                                // 0x00e8bda0
    void FUN_00e8bdc0();                                // 0x00e8bdc0
    void UpdateInteractionEffects();                    // 0x00e8be60
    void UpdateMotiveEffects();                         // 0x00e8bf20
    void FUN_00e8c030();                                // 0x00e8c030
    cCreatureView* FUN_00e8c0c0(u8 f);                  // 0x00e8c0c0
    void CreatureCitizenUpdate(cCreature* p);           // 0x00e8c070
};
}
// ---- items of slice s00e8b7a0 end

// ---- items of slice s00e8d0e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gVtableNest;
struct Vec3 {
    float mX;
    float mY;
    float mZ;
};
struct ModelKey {
    uint32_t mType;
    uint32_t mInstance;
    uint32_t mGroup;
};
struct cMethodTable {
    void* mSlots[0x80];
};
class cSpatialObject {
public:
    void* mpMethods;                            // 0x00
    union {
        uint32_t mFlags;                        // 0x04
        uint8_t mFlagByte;                      // 0x04
    };

    void* GetComponent(uint32_t nKey) {
        return ((void* (*)(void*, uint32_t))((cMethodTable*)mpMethods)->mSlots[0xb8 >> 2])(this, nKey);
    }
};
class cAnimatingCreature {
public:
    uint8_t mPad000[0x80];                      // 0x000
    float mfEffectValue;                        // 0x080
};
struct Frame {
    cMethodTable* mpMethods;                    // 0x00
    uint32_t mFlags;                            // 0x04
    uint8_t mPad08[0x38];                       // 0x08
    int mnRefCount;                             // 0x40
};
class cSpatialObjectView {
public:
    cSpatialObjectView();

    void* mpVftable;                            // 0x00
    uint32_t mPad04[5];                         // 0x04
    Vec3 mColor;                                // 0x18
    ModelKey mKey;                              // 0x24
    void* mpPad30;                              // 0x30
    cAnimatingCreature* mpAnimated;             // 0x34
    cSpatialObject* mpObject;                   // 0x38
    Frame* mpFrame;                             // 0x3c
};
class cNestView : public cSpatialObjectView {
public:
    cNestView();
    void SetupNestModelKey();
};
// ---- items of slice s00e8d0e0 end

// @ 0x00e82340
int __stdcall FUN_00e82340(int* param_1)
{
    int iVar2 = FUN_00f473a0(0x18,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0, 0, 0, 0xd1);
    if ((int*)(iVar2 + 8) != 0) {
        *(int*)(iVar2 + 8) = *param_1;
        *(int*)(iVar2 + 0xc) = param_1[1];
        int* puVar1 = (int*)param_1[2];
        *(int**)(iVar2 + 0x10) = puVar1;
        if (puVar1 != 0)
            (*(void(**)(void))(*puVar1))();
        *(int*)(iVar2 + 0x14) = param_1[3];
    }
    return iVar2;
}

// @ 0x00e82420
int* FUN_00e82420(int param_1, int param_2)
{
    int* puVar1 = gListSentinel;
    int* puVar2 = (int*)*gListSentinel;
    for (;;) {
        if (puVar2 == gListSentinel) {
        add:
            struct { int a; int b; int c; int d; } local;
            local.c = param_2;
            local.d = 0;
            local.a = param_1;
            local.b = 0;
            puVar2 = (int*)FUN_00e82340((int*)&local);
            *puVar2 = (int)puVar1;
            puVar2[1] = puVar1[1];
            *(int**)puVar1[1] = puVar2;
            puVar1[1] = (int)puVar2;
            return puVar2 + 2;
        }
        if (puVar2[2] == param_1 && puVar2[3] == param_2) {
            if (puVar2 + 2 != 0)
                return puVar2 + 2;
        }
        puVar2 = (int*)*puVar2;
    }
}

// @ 0x00e82490
void FUN_00e82490()
{
    int* p = (int*)FUN_00f473a0(0xc, 0, 0, 0, 0, 0);
    if (p != 0) {
        *p = (int)p;
        p[1] = (int)p;
        gListSentinel = p;
        return;
    }
    gListSentinel = 0;
}

// @ 0x00e82500
void FUN_00e82500(int a)
{
    ((C006a17e0*)gField_15fd918)->FUN_006a17e0(0x28, a);
}

// @ 0x00e85190
void __cdecl FUN_00e85190()
{
    cLinkBody* pLink = WindowManager()->GetLink();
    cUIElement* pElement = pLink ? (cUIElement*)pLink : 0;
    pElement->FUN_00812d90();
}

// @ 0x00e851c0
void __cdecl JacobiDecompose()
{
}

// @ 0x00e853c0
void __cdecl ComputeCenterOfMass()
{
}

// @ 0x00e855e0
void FUN_00e855e0(float* a, int n)
{
    int last = n - 1;
    int r = 0;
    if (last < 0) {
        last = 0;
        r = n - 1;
    }
    if (r > last)
        return;

    for (; r <= last; ++r) {
        const float d = a[r * n + r];

        if (fabsf(d) < 1e-8f) {
            // defective pivot: clear the r-th row and the r-th column
            for (int k = 0; k < n; ++k) {
                a[k * n + r] = 0.0f;   // column r
                a[r * n + k] = 0.0f;   // row r
            }
        } else {
            const float inv = 1.0f / d;
            a[r * n + r] = inv;

            // row pass: negate the scaled off-diagonal elements of row r
            for (int c = 0; c < n; ++c) {
                if (c != r)
                    a[r * n + c] = -(a[r * n + c] * inv);
            }

            // column pass: scale the off-diagonal elements of column r
            for (int k = 0; k < n; ++k) {
                if (k != r)
                    a[k * n + r] = a[k * n + r] * inv;
            }

            // rank-1 update of the remaining submatrix
            for (int j = 0; j < n; ++j) {
                if (j == r)
                    continue;
                const float f = a[r * n + j] / inv;
                for (int i = 0; i < n; ++i) {
                    if (i != r)
                        a[i * n + j] += f * a[i * n + r];
                }
            }
        }
    }
}

// @ 0x00e85a60
void FUN_00e85a60(int n, const Vector3* pts, const float* masses, Vector3* centred, Vector3* centre, float* aqq)
{
    ComputeCenterOfMass(n, pts, masses, centre);

    // shift the particles into centre-relative coordinates
    for (int i = 0; i < n; ++i) {
        centred[i].x = pts[i].x - centre->x;
        centred[i].y = pts[i].y - centre->y;
        centred[i].z = pts[i].z - centre->z;
    }

    FUN_011e073e(aqq, 0, 0x144);

    // aqq = sum_i m_i * q_i q_i^T for the centred particles, laid out row-major as
    //   [ xx xy xz ]
    //   [ xy yy yz ]
    //   [ xz yz zz ]
    for (int i = 0; i < n; ++i) {
        const float x = centred[i].x;
        const float y = centred[i].y;
        const float z = centred[i].z;
        const float w = masses[i];

        aqq[0] += x * x * w;
        aqq[1] += x * y * w;
        aqq[2] += x * z * w;
        aqq[3] += x * y * w;
        aqq[4] += y * y * w;
        aqq[5] += y * z * w;
        aqq[6] += x * z * w;
        aqq[7] += y * z * w;
        aqq[8] += z * z * w;
    }

    FUN_00e855e0(aqq, 3);
}

// @ 0x00e85dc0
void ComputeShapeMatchGoals(int n, const Vector3_s00e8_5dc0* restOffsets, const float* masses, const Matrix3& Aqq, const Vector3_s00e8_5dc0* positions, float scale, float beta, Vector3_s00e8_5dc0* goals, Matrix3& R, Matrix3& T)
{
  float invScale = 1.0f / scale;
  Vector3_s00e8_5dc0 center = kZeroVector;
  ComputeCenterOfMass(n, positions, masses, &center);

  Matrix3 Apq[3];   // the original clears 0x6c bytes; only the first matrix is used
  memset(Apq, 0, sizeof(Apq));
  for (int i = 0; i < n; i++) {
    Vector3_s00e8_5dc0 q = positions[i] - center;
    Vector3_s00e8_5dc0 p = restOffsets[i] * scale;
    Apq[0] = Apq[0] + Outer(q, p) * masses[i];
  }

  Matrix3 D;
  JacobiDecompose(Apq[0], R, D);
  Matrix3 M = Apq[0] * Aqq * invScale * invScale;
  T = M * beta + R * (1.0f - beta);

  for (int i = 0; i < n; i++)
    goals[i] = (restOffsets[i] * scale) * T + center;
}

// @ 0x00e86880
Node* FUN_00e86880(SphereTree* tree, const Vector3_s00e8_5dc0* pos, float f, int data)
{
  SpherePool* pool = tree->pool;
  int index = pool->count;
  Node* node;
  if (index == pool->capacity) {
    node = 0;
  } else {
    if (index == pool->end) {
      node = (Node*)(pool->base + pool->stride * index);
      pool->end++;
    } else {
      node = pool->freeHead;
      pool->freeHead = node->freeNext;
    }
    pool->count = index + 1;
  }
  node->pos = *(const NodePos*)pos;
  node->f = f;
  node->next = 0;
  node->data = data;
  return node;
}

// @ 0x00e868f0
void FUN_00e868f0(SphereTree* tree, const Vector3_s00e8_5dc0* pos, float f, int data)
{
  Node* node = FUN_00e86880(tree, pos, f, data);
  node->parent = 0;
  node->next = tree->head;
  tree->head = node;
}

// @ 0x00e86930
void FUN_00e86930(SphereTree* tree, Node* node)
{
  Node* parent = node->parent;
  Node* sibling = parent->next;
  if (sibling == node)
    sibling = parent->right;
  Node* grand = parent->parent;
  Node** link = (grand->next == parent) ? &grand->next : &grand->right;
  FreeSphereNode(tree, parent);
  *link = sibling;
  sibling->parent = grand;
  node->parent = 0;
}

// @ 0x00e86980
void FUN_00e86980(SphereTree* tree, Node* node)
{
  if (tree->root == node) {
    SpherePool* pool = tree->pool;
    tree->root = 0;
    pool->count--;
    node->freeNext = pool->freeHead;
    pool->freeHead = node;
    return;
  }

  Node* parent = node->parent;
  if (parent == 0) {
    Node* cur = tree->head;
    Node* prev = 0;
    while (cur != 0) {
      if (cur == node)
        break;
      prev = cur;
      cur = cur->next;
    }
    if (prev != 0)
      prev->next = cur->next;
    else
      tree->head = cur->next;
    FreeSphereNode(tree, node);
    return;
  }

  if (parent == tree->root) {
    Node* sibling = parent->next;
    if (sibling == node)
      sibling = parent->right;
    tree->root = sibling;
    sibling->parent = 0;
    FreeSphereNode(tree, node->parent);
    FreeSphereNode(tree, node);
    return;
  }

  FUN_00e86930(tree, node);
  FreeSphereNode(tree, node);
}

// @ 0x00e86ad0
void FUN_00e86ad0()
{
  ((SimulatorGlobal*)0x016c45b4)->FUN_00b72080(0x10, 2);
}

// @ 0x00e86ae0
void FUN_00e86ae0()
{
  int priority = ((SimulatorGlobal*)0x016c45b4)->FUN_00e31100();
  SimEntry* e = ((SimulatorGlobal*)0x016c45b4)->FUN_00b72230(&priority);
  while (e != 0) {
    SpherePool* pool = (SpherePool*)e->value;
    if (pool != 0) {
      free(pool->base);
      FUN_00f47380(pool);
    }
    ((SimulatorGlobal*)0x016c45b4)->FUN_00b72260(e->key);
    e = ((SimulatorGlobal*)0x016c45b4)->FUN_00b72230(&priority);
  }
  ((SimulatorGlobal*)0x016c45b4)->FUN_00b720e0();
}

// @ 0x00e86b60
void FUN_00e86b60()
{
  int priority = ((SimulatorGlobal*)0x016c45b4)->FUN_00e31100();
  SimEntry* e = ((SimulatorGlobal*)0x016c45b4)->FUN_00b72230(&priority);
  while (e != 0) {
    Node* node = (Node*)e->value;
    node->pos.x = 0;
    node->pos.y = 0;
    node->pos.z = 0;
    e->field08 = 0;
    e->field0c = 0;
    e = ((SimulatorGlobal*)0x016c45b4)->FUN_00b72230(&priority);
  }
}

// @ 0x00e86bb0
void FUN_00e86bb0(const Vector3_s00e8_5dc0* a, float ra, const Vector3_s00e8_5dc0* b, float rb, Vector3_s00e8_5dc0* out, float* outRadius)
{
  float delta[3];
  delta[0] = b->x - a->x;
  delta[1] = b->y - a->y;
  delta[2] = b->z - a->z;
  float sq = (delta[0] * delta[0] + delta[1] * delta[1]) + delta[2] * delta[2];
  float dist = sqrtf(sq);
  float sum = dist + ra;

  if (sum < rb) {
    *out = *b;
    *outRadius = rb;
    return;
  }
  if (dist + rb < ra) {
    *out = *a;
    *outRadius = ra;
    return;
  }

  *outRadius = (sum + rb) * 0.5f;
  if (dist < 1.5258789e-05f) {
    float mx = a->x + b->x;
    float my = a->y + b->y;
    float mz = a->z + b->z;
    out->x = mx * 0.5f;
    out->y = my * 0.5f;
    out->z = mz * 0.5f;
    return;
  }

  float inv = 1.0f / dist;
  float d = rb - ra;
  float cx = a->x + b->x;
  float cy = a->y + b->y;
  float cz = a->z + b->z;
  float tx = (inv * delta[0]) * d;
  float ty = (inv * delta[1]) * d;
  float tz = (inv * delta[2]) * d;
  out->x = (cx + tx) * 0.5f;
  out->y = (cy + ty) * 0.5f;
  out->z = (cz + tz) * 0.5f;
}

// @ 0x00e86d40
EffRec* treePush(EffTree* t, EffRec* a, EffRec* b)
{
    EffPool* p = t->mpPool;
    EffRec* n;
    if (p->mCount == p->mCapacity) {
        n = 0;
    } else {
        if (p->mCount == p->mNextUnused) {
            n = (EffRec*)(p->mpBase + p->mCount * p->mStride);
            p->mCount++;
            p->mNextUnused++;
        } else {
            n = p->mpFreeList;
            p->mpFreeList = n->mpFreeNext;
            p->mCount++;
        }
    }

    FUN_00e86bb0(a->mCenter, a->mRadius, b->mCenter, b->mRadius, n->mCenter, &n->mRadius);
    n->mChildA = a;
    n->mRadius *= 1.1f;
    a->mParent = n;
    n->mChildB = b;
    b->mParent = n;
    return n;
}

// @ 0x00e86dc0
EffRec* treeNearest(const float* pos, float radius, EffRec* n)
{
    EffRec* childA = n->mChildA;
    if (childA == 0)
        return n;
    float px = pos[0], py = pos[1], pz = pos[2];
    for (;;) {
        EffRec* childB = n->mChildB;
        float a0 = childA->mCenter[0] - px;
        float a1 = childA->mCenter[1] - py;
        float a2 = childA->mCenter[2] - pz;
        float b0 = childB->mCenter[0] - px;
        float b1 = childB->mCenter[1] - py;
        float b2 = childB->mCenter[2] - pz;
        float da = a1 * a1 + a0 * a0 + a2 * a2;
        float db = b2 * b2 + b1 * b1 + b0 * b0;
        if (db > da)
            n = childA;
        else
            n = childB;
        childA = n->mChildA;
        if (childA == 0)
            return n;
    }
}

// @ 0x00e86e80
void treeRefit(EffRec* n)
{
    while (true) {
        EffRec* a = n->mChildA;
        float dx = a->mCenter[0] - n->mCenter[0];
        float dy = a->mCenter[1] - n->mCenter[1];
        float dz = a->mCenter[2] - n->mCenter[2];
        if (sqrtf(dx * dx + (dy * dy + dz * dz)) + a->mRadius <= n->mRadius) {
            EffRec* b = n->mChildB;
            float ex = b->mCenter[0] - n->mCenter[0];
            float ey = b->mCenter[1] - n->mCenter[1];
            float ez = b->mCenter[2] - n->mCenter[2];
            if (sqrtf((ez * ez + ey * ey) + ex * ex) + b->mRadius <= n->mRadius)
                break;
        }
        FUN_00e86bb0(n->mChildA->mCenter, n->mChildA->mRadius,
                     n->mChildB->mCenter, n->mChildB->mRadius,
                     n->mCenter, &n->mRadius);
        n = n->mParent;
        if (n == 0)
            return;
    }
}

// @ 0x00e86f70
void treeInsert(EffTree* t)
{
    while (t->mpToRemove != 0) {
        EffRec* n = t->mpToRemove;
        t->mpToRemove = n->mChildA;
        n->mChildA = 0;
        EffRec* root = t->mpPending;
        if (root == 0) {
            t->mpPending = n;
            n->mParent = 0;
        } else if (root->mChildA == 0) {
            n = treePush(t, n, root);
            t->mpPending = n;
            n->mParent = 0;
        } else {
            EffRec* best = treeNearest(n->mCenter, n->mRadius, root);
            EffRec* parent = best->mParent;
            EffRec** slot;
            if (parent->mChildA == best)
                slot = &parent->mChildA;
            else
                slot = &parent->mChildB;
            n = treePush(t, n, best);
            *slot = n;
            n->mParent = parent;
            treeRefit(parent);
        }
    }
}

// @ 0x00e87000
void treeInsertPending()
{
    int key = g_EffectWindow.GetPriority();
    EffRec* n;
    while ((n = (EffRec*)g_EffectWindow.Remove(&key)) != 0)
        treeInsert((EffTree*)n);
}

// @ 0x00e87040
void treeRemove(EffTree* t, EffRec* n, const float* pos, float radius)
{
    memcpy(n->mCenter, pos, sizeof(float) * 3);
    n->mRadius = radius;
    EffRec* old = n->mParent;
    if (old == 0)
        return;
    float dx = n->mCenter[0] - old->mCenter[0];
    float dy = n->mCenter[1] - old->mCenter[1];
    float dz = n->mCenter[2] - old->mCenter[2];
    if (!(old->mRadius < sqrtf(dx * dx + dy * dy + dz * dz) + radius))
        return;

    if (old == t->mpPending) {
        EffRec* sib = old->mChildA;
        if (sib == n)
            sib = old->mChildB;
        EffPool* p = t->mpPool;
        p->mCount--;
        old->mpFreeNext = p->mpFreeList;
        p->mpFreeList = old;
        t->mpPending = sib;
        sib->mParent = 0;
        n->mParent = 0;
        n->mChildA = t->mpToRemove;
        t->mpToRemove = n;
        return;
    }
    FUN_00e86930(t, n);
    n->mParent = 0;
    n->mChildA = t->mpToRemove;
    t->mpToRemove = n;
}

// @ 0x00e87100
void collectSphereRec(EffRec* n, const float* a, const float* b, void** out, int* count, int max, float segLen)
{
    int i = *count;
    if (i == max)
        return;
    float dx = n->mCenter[0] - a[0];
    float dy = n->mCenter[1] - a[1];
    float dz = n->mCenter[2] - a[2];
    if (!(dx * dx + dy * dy + dz * dz <= n->mRadius * n->mRadius)) {
        float hit;
        if (!IntersectRaySphere(a, b, n->mCenter, n->mRadius, &hit))
            return;
        if (hit > segLen)
            return;
    }
    if (n->mChildA == 0) {
        out[i] = n->mChildB;
        *count = i + 1;
        return;
    }
    EffRec** p = &n->mChildA;
    for (int k = 2; k != 0; k--) {
        collectSphereRec(*p, a, b, out, count, max, segLen);
        p++;
    }
}

// @ 0x00e87200
int collectSphere(EffTree* t, const float* a, const float* b, void** out, int max, float segLen)
{
    if (t->mpToRemove != 0)
        treeInsert(t);
    if (t->mpPending == 0)
        return 0;
    int count = 0;
    collectSphereRec(t->mpPending, a, b, out, &count, max, segLen);
    return count;
}

// @ 0x00e87260
int collectSphereBFS(EffTree* t, float* pos, float radius, void** out, int max, EffRec** out2)
{
    if (t->mpToRemove != 0)
        treeInsert(t);
    EffRec* root = t->mpPending;
    if (root == 0)
        return 0;

    EffRec* queue[256];
    queue[0] = root;
    int n = 1;
    int k = 0;
    for (;;) {
        EffRec* node = queue[n - 1];
        n--;
        float dx = pos[0] - node->mCenter[0];
        float dy = pos[1] - node->mCenter[1];
        float dz = pos[2] - node->mCenter[2];
        float r = node->mRadius + radius;
        if (dx * dx + dy * dy + dz * dz < r * r) {
            if (node->mChildA == 0) {
                out[k] = node->mChildB;
                if (out2 != 0)
                    out2[k] = node;
                k++;
                if (k == max)
                    break;
            } else {
                queue[n] = node->mChildA;
                n++;
                queue[n] = node->mChildB;
                n++;
            }
        }
        if (n <= 0)
            break;
    }
    return k;
}

// @ 0x00e87360
int collectCylinder(EffTree* t, const float* a, const float* b, float r1, float r2, void** out, int max)
{
    if (t->mpToRemove != 0)
        treeInsert(t);
    if (t->mpPending == 0)
        return 0;

    float mid[3];
    mid[0] = a[0] + b[0] * kHalf;
    mid[1] = a[1] + b[1] * kHalf;
    mid[2] = a[2] + b[2] * kHalf;

    EffRec* list[513];
    int count = collectSphereBFS(t, mid, sqrtf(r2 * r2 + r1 * r1), out, max, list + 1);
    for (int i = 0; i < count; i++) {
        EffRec* node = list[i + 1];
        float nr = node->mRadius;
        float d = (node->mCenter[2] - a[2]) * b[2]
                + (node->mCenter[1] - a[1]) * b[1]
                + (node->mCenter[0] - a[0]) * b[0];
        float e0 = (node->mCenter[2] - a[2]) - b[2] * d;
        float e1 = (node->mCenter[1] - a[1]) - b[1] * d;
        float e2 = (node->mCenter[0] - a[0]) - b[0] * d;
        if (!(d < -nr) && !(nr + r1 < d) && nr + r2 >= sqrtf(e2 * e2 + (e1 * e1 + e0 * e0)))
            continue;
        out[i] = out[count - 1];
        list[i + 1] = list[count];
        count--;
        i--;
    }
    return count;
}

// @ 0x00e8bc80
SP::cCreatureView::cCreatureView()
{
    m08 = 0;
    m04 = 0;
    mpVtbl = g_vtbl_014863cc;
    mpCreature = 0;
    mpOverhead = 0;
    mb14 = 1;
    mp18 = 0;
}

// @ 0x00e8ded0
cNestView::cNestView()
{
    mColor.mX = 1.0f;
    mColor.mY = 1.0f;
    mpVftable = &gVtableNest;
    mColor.mZ = 1.0f;
}
