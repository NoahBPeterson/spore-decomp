// 0x00add1a0 (unnamed) walks two hash tables of attached objects and re-places each one.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// For every entry of table 1 (+0xb0) and then table 2 (+0x90): copy the entry (a weak handle with
// a local offset), and
//   - handle gone or no longer alive          -> erase the entry from the table;
//   - entry has no flag or no target id       -> skip it;
//   - otherwise ask the owner (0x00adb2a0) for the target's placement, take its position and
//     rotation (from the placement's parent object when it has one), and
//       * position == the "nowhere" constant  -> detach the handle (vslot 0xc) and erase the entry,
//       * else build a Transform (offset = position + rotation * entry offset, rotation) and hand
//         it to the object (vslot 0x18).
// Returns whether table 2 is empty.
#include "types.h"

#define VFUNC(obj, off) ((*(void***)(obj))[(off) / 4])

struct Vec3 {
  float x, y, z;
  Vec3() {}
  Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct M33 {
  float m[9];
  M33() {}
  M33(const M33& o);                           // 0x0041cb40
};

// Transform (ModAPI layout, 0x38 bytes)
struct Transform {
  int16_t flags;
  int16_t count;
  Vec3 offset;
  float scale;
  M33 rot;
  Transform();
  void SetOffset(const Vec3& v) { offset = v; flags |= 4; ++count; }
  void SetRotation(const M33& r) { rot = r; flags |= 2; ++count; }
};

extern Vec3 g_TransformOffset;    // 0x0167a5a4
extern M33 g_TransformRot;        // 0x0167a5b0
extern Vec3 g_PlacementPos;       // 0x0167a548
extern Vec3 g_Nowhere;            // 0x0156649c
extern float g_One;               // 0x01485720

inline Transform::Transform() : rot(g_TransformRot)
{
  flags = 0;
  count = 0;
  offset = g_TransformOffset;
  scale = g_One;
}

struct Obj {
  virtual void v0();
  virtual int Release();
  virtual void v8();
  virtual void Detach(int n);                  // 0x0c
  virtual bool IsAlive();                      // 0x10
  virtual void v14();
  virtual void SetTransform(const Transform* t);   // 0x18
};

// what the owner tells us about a target
struct Placement {
  Vec3 pos;                // +0x00
  float rot[4];            // +0x0c
  float scl[4];            // +0x1c
  void* parent;            // +0x2c
  Placement() {
    pos.x = g_PlacementPos.x;
    pos.y = g_PlacementPos.y;
    pos.z = g_PlacementPos.z;
    rot[0] = rot[1] = rot[2] = rot[3] = 0.0f;
    scl[0] = scl[1] = scl[2] = scl[3] = g_One;
    parent = 0;
  }
};
inline const Vec3* ParentPos(void* p) { return ((const Vec3*(__thiscall*)(void*))VFUNC(p, 0x2c))(p); }
inline const float* ParentRot(void* p) { return ((const float*(__thiscall*)(void*))VFUNC(p, 0x30))(p); }

M33* __cdecl QuatToMatrix(M33* out, const float* q);   // 0x004a9b40

struct Entry {
  uint32_t a, b;
  Obj* obj;                // +8
  Vec3 local;              // +0xc
  uint32_t pad[5];
  bool flag;               // +0x24
  uint32_t pad2;
  int targetId;            // +0x2c
  uint32_t pad3[1];
  Entry(const Entry& src);                       // 0x00ad7ca0
  ~Entry() { if (obj) obj->Release(); }
};

struct Node {
  uint32_t key;
  Entry value;
  Node* next;              // +0x38
};

struct Iter {
  Node* node;
  Node** bucket;
  Iter(Node* n, Node** b) : node(n), bucket(b) {}
  Iter(const Iter& o) : node(o.node), bucket(o.bucket) {}
};

struct Table {
  uint32_t alloc;
  Node** buckets;          // +4
  uint32_t nBuckets;       // +8
  uint32_t nElements;      // +0xc
  Iter erase(Iter pos);                          // 0x00adc9f0
};

struct Owner {
  char pad[0x90];
  Table t2;                // +0x90
  char pad2[0x10];
  Table t1;                // +0xb0
  void GetPlacement(int id, Placement* out);     // 0x00adb2a0
  bool Update();
};

template<bool kRelease> static __forceinline void Pass(Owner* owner, Table* tbl)
{
  Node** bucket = tbl->buckets;
  Node* node = *bucket;
  if (!node) {
    do { ++bucket; } while (!*bucket);
    node = *bucket;
  }
  while (node != tbl->buckets[tbl->nBuckets]) {
    Entry e(node->value);
    if (!e.obj || !e.obj->IsAlive()) {
      Iter r = tbl->erase(Iter(node, bucket));
      node = r.node;
      bucket = r.bucket;
    } else if (!e.flag || !e.targetId) {
      node = node->next;
      while (!node) { ++bucket; node = *bucket; }
    } else {
      Placement pl;
      owner->GetPlacement(e.targetId, &pl);
      const Vec3* pos = pl.parent ? ParentPos(pl.parent) : &pl.pos;
      const float* q = pl.parent ? ParentRot(pl.parent) : pl.rot;
      M33 R;
      M33 tmpM;
      R = *QuatToMatrix(&tmpM, q);
      if (kRelease && pl.parent) {
        ((float(__thiscall*)(void*))VFUNC(pl.parent, 0x70))(pl.parent);
        if (pl.parent)
          ((void(__thiscall*)(void*))VFUNC(pl.parent, 0x68))(pl.parent);
      }
      if (pos->x == g_Nowhere.x && pos->y == g_Nowhere.y && pos->z == g_Nowhere.z) {
        Obj* o = e.obj;
        o->Detach(1);
        e.obj = 0;
        o->Release();
        Iter r = tbl->erase(Iter(node, bucket));
        node = r.node;
        bucket = r.bucket;
      } else {
        Transform t;
        const float ox = e.local.x, oy = e.local.y, oz = e.local.z;
        Vec3 np;
        np.x = pos->x + ((R.m[0] * ox + R.m[6] * oz) + R.m[3] * oy);
        np.y = pos->y + ((R.m[7] * oz + R.m[4] * oy) + R.m[1] * ox);
        np.z = pos->z + ((R.m[8] * oz + R.m[5] * oy) + R.m[2] * ox);
        t.SetOffset(np);
        t.SetRotation(R);
        e.obj->SetTransform(&t);
        node = node->next;
        while (!node) { ++bucket; node = *bucket; }
      }
      if (pl.parent)
        ((void(__thiscall*)(void*))VFUNC(pl.parent, 0xc0))(pl.parent);
    }
  }
}

// @ 0x00add1a0
bool Owner::Update()
{
  Pass<true>(this, &t1);
  Pass<false>(this, &t2);
  return t2.nElements == 0;
}
