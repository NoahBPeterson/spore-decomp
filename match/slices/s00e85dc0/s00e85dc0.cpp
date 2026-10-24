// @ 0x00e85dc0  shape-matching goal positions (no symbol; free cdecl function)
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (scalar SSE math with reassociated sums).
//
// One step of meshless shape matching (Mueller et al. 2005) over n particles:
//   c   = mass-weighted centre of the current positions        (0x00e853c0)
//   Apq = sum_i m_i (x_i - c)(s * q_i)^T                         (q_i = rest offsets)
//   Apq is decomposed with Jacobi sweeps into R (eigenvectors) and D (0x00e851c0)
//   T   = beta * (Apq * Aqq) / s^2 + (1 - beta) * R              (written to *pT)
//   g_i = (s * q_i) * T + c                                      (goal positions)
// Matrices are row-major 3x3; points are row vectors multiplied on the left.
#include "types.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

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
    return Matrix3(m.r[0] * r[0].x + m.r[1] * r[0].y + m.r[2] * r[0].z,
                   m.r[0] * r[1].x + m.r[1] * r[1].y + m.r[2] * r[1].z,
                   m.r[0] * r[2].x + m.r[1] * r[2].y + m.r[2] * r[2].z);
  }
};

// a b^T
inline Matrix3 Outer(const Vector3& a, const Vector3& b) { return Matrix3(b * a.x, b * a.y, b * a.z); }
// row vector times matrix
inline Vector3 operator*(const Vector3& v, const Matrix3& m) {
  return Vector3(v.x * m.r[0].x + v.y * m.r[1].x + v.z * m.r[2].x,
                 v.x * m.r[0].y + v.y * m.r[1].y + v.z * m.r[2].y,
                 v.x * m.r[0].z + v.y * m.r[1].z + v.z * m.r[2].z);
}

extern const Vector3 kZeroVector;   // 0x016c4584

void ComputeCenterOfMass(int n, const Vector3* positions, const float* masses, Vector3* center);   // 0x00e853c0
void JacobiDecompose(const Matrix3& m, Matrix3& eigenvectors, Matrix3& diagonal);                 // 0x00e851c0

// @ 0x00e85dc0
void ComputeShapeMatchGoals(int n, const Vector3* restOffsets, const float* masses, const Matrix3& Aqq,
                            const Vector3* positions, float scale, float beta, Vector3* goals,
                            Matrix3& R, Matrix3& T)
{
  float invScale = 1.0f / scale;
  Vector3 center = kZeroVector;
  ComputeCenterOfMass(n, positions, masses, &center);

  Matrix3 Apq[3];   // the original clears 0x6c bytes; only the first matrix is used
  memset(Apq, 0, sizeof(Apq));
  for (int i = 0; i < n; i++) {
    Vector3 q = positions[i] - center;
    Vector3 p = restOffsets[i] * scale;
    Apq[0] = Apq[0] + Outer(q, p) * masses[i];
  }

  Matrix3 D;
  JacobiDecompose(Apq[0], R, D);
  Matrix3 M = Apq[0] * Aqq * invScale * invScale;
  T = M * beta + R * (1.0f - beta);

  for (int i = 0; i < n; i++)
    goals[i] = (restOffsets[i] * scale) * T + center;
}

// ---------------------------------------------------------------------------
// Sphere-tree slab allocator and helpers (0x00e86880 .. 0x00e86bb0).
// ---------------------------------------------------------------------------
void* __cdecl FUN_00f473a0(size_t size, const char* name, int a, int b, int c, int d); // 0xf473a0
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

// @ 0x00e86880
Node* FUN_00e86880(SphereTree* tree, const Vector3* pos, float f, int data)
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
void FUN_00e868f0(SphereTree* tree, const Vector3* pos, float f, int data)
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
void FUN_00e86bb0(const Vector3* a, float ra, const Vector3* b, float rb,
                  Vector3* out, float* outRadius)
{
  float dx = b->x - a->x;
  float dy = b->y - a->y;
  float dz = b->z - a->z;
  float dist = sqrtf(dx * dx + dy * dy + dz * dz);

  if (dist + ra < rb) {
    out->x = b->x;
    out->y = b->y;
    out->z = b->z;
    *outRadius = rb;
    return;
  }
  if (dist + rb < ra) {
    out->x = a->x;
    out->y = a->y;
    out->z = a->z;
    *outRadius = ra;
    return;
  }

  *outRadius = (dist + ra + rb) * 0.5f;
  if (dist < 1.5258789e-05f) {
    out->x = (a->x + b->x) * 0.5f;
    out->y = (a->y + b->y) * 0.5f;
    out->z = (a->z + b->z) * 0.5f;
    return;
  }

  float inv = 1.0f / dist;
  float d = rb - ra;
  out->x = (a->x + b->x + (inv * dx) * d) * 0.5f;
  out->y = (a->y + b->y + (inv * dy) * d) * 0.5f;
  out->z = (a->z + b->z + (inv * dz) * d) * 0.5f;
}
