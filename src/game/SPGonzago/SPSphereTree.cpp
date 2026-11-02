// src/game/SPGonzago/SPSphereTree.cpp -- migrated from slice(s) s00e85dc0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSphereTree.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/SphereTreeNode.h"
#include "cSPVector3.h"
#include "SP/MemoryPool.h"
#include "SP/cSPSphereTree.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

// ---- items of slice s00e85dc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
  Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
  Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
  Vector3 operator*(float f) const { return Vector3(x * f, y * f, z * f); }
};
struct Matrix3 {
  Vector3 r[3];
  Matrix3() {}
  Matrix3(const Vector3& r0, const Vector3& r1, const Vector3& r2) { r[0] = r0; r[1] = r1; r[2] = r2; }
  Matrix3 operator+(const Matrix3& m) const { return Matrix3(r[0] + m.r[0], r[1] + m.r[1], r[2] + m.r[2]); }
  Matrix3 operator*(float f) const { return Matrix3(r[0] * f, r[1] * f, r[2] * f); }
  __forceinline Matrix3 operator*(const Matrix3& m) const {
    // Retail sums the three terms of row i starting at column (i+1)%3: row 0 (y,z,x),
    // row 1 (z,x,y), row 2 (x,y,z).  Parenthesise to keep that rounding order.
    return Matrix3(
        Vector3((r[0].y * m.r[1].x + r[0].z * m.r[2].x) + r[0].x * m.r[0].x,
                (r[0].y * m.r[1].y + r[0].z * m.r[2].y) + r[0].x * m.r[0].y,
                (r[0].y * m.r[1].z + r[0].z * m.r[2].z) + r[0].x * m.r[0].z),
        Vector3((r[1].z * m.r[2].x + r[1].x * m.r[0].x) + r[1].y * m.r[1].x,
                (r[1].z * m.r[2].y + r[1].x * m.r[0].y) + r[1].y * m.r[1].y,
                (r[1].z * m.r[2].z + r[1].x * m.r[0].z) + r[1].y * m.r[1].z),
        Vector3((r[2].x * m.r[0].x + r[2].y * m.r[1].x) + r[2].z * m.r[2].x,
                (r[2].x * m.r[0].y + r[2].y * m.r[1].y) + r[2].z * m.r[2].y,
                (r[2].x * m.r[0].z + r[2].y * m.r[1].z) + r[2].z * m.r[2].z));
  }
};
inline Vector3 operator*(const Vector3& v, const Matrix3& m) {
  // Keep the original's per-component summation order: (x*col0 + z*col2) + y*col1
  // for x, (z*col2 + x*col0) + y*col1 for y, and (y*col1 + z*col2) + x*col0 for z.
  return Vector3(v.x * m.r[0].x + v.z * m.r[2].x + v.y * m.r[1].x,
                 v.z * m.r[2].y + v.x * m.r[0].y + v.y * m.r[1].y,
                 v.y * m.r[1].z + v.z * m.r[2].z + v.x * m.r[0].z);
}
void* __cdecl FUN_00f473a0(size_t size, const char* name, int a, int b, int c, int d); // 0xf473a0
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
// ---- items of slice s00e85dc0 end

// @ 0x00e86a50
namespace SP {
SphereTree* SphereTreeCreate()
{
  int handle = ((SimulatorGlobal*)0x016c45b4)->FUN_00b72160();
  SphereTree* tree = ((SimulatorGlobal*)0x016c45b4)->FUN_00b72210(handle);
  SpherePool* pool = (SpherePool*)FUN_00f473a0(0x18, "Simulator", 0, 0, 0, 0);
  if (pool != 0) {
    pool->stride = 0x1c;
    pool->capacity = 0x2000;
    pool->base = (char*)malloc(0x38000);
    pool->count = 0;
    pool->end = 0;
    pool->freeHead = 0;
    tree->pool = pool;
    return tree;
  }
  tree->pool = pool;
  return tree;
}
}  // namespace SP
