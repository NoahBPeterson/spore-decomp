// slice s009b5ce0 -- FUN_009b6450: ray cast against the oriented boxes of a creature's parts.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <float.h>

namespace RC {

struct BoxShape {
  char pad[0x138];
  float mHalfExtent[3];   // +0x138
};

// One part record (700 bytes).
struct Part {
  BoxShape* mpShape;      // +0x00
  char pad04[0xc];
  float mCenter[3];       // +0x10
  float mQuat[4];         // +0x1c: x y z w
  char pad2c[700 - 0x2c];
};

struct Owner {
  char pad00[0x18];
  float mPos[3];          // +0x18
  char pad24[0x3c - 0x24];
  float mQuat[4];         // +0x3c: x y z w
  char pad4c[0x70 - 0x4c];
  float mScale;           // +0x70
  char pad74[0x2e4 - 0x74];
  Part* mpPartsBegin;     // +0x2e4
  Part* mpPartsEnd;       // +0x2e8
};

}  // namespace RC

// Ray vs one oriented box; fills tOut and the box-local normal.
bool BoxRayTest(const float* org, const float* dir, const float* center, const float* rot3x3,
                float ex, float ey, float ez, float* tOut, float* normalOut);  // 0x00a02530
// Rotates a vector by a quaternion; returns out.
float* QuaternionVectorTransform(float* out, const float* quat, const float* v);  // 0x0099c1a0

using namespace RC;

// @ 0x009b6450
bool RayCastParts(const float* org, const float* dir, Owner* obj, unsigned* pIndex, float* pT, float* pHit,
                  float* pNormal)
{
  float bestT = FLT_MAX;
  float bestN[3] = {0.0f, 0.0f, 0.0f};
  float dx = org[0] - obj->mPos[0];
  float qd = obj->mQuat[3];
  float qc = obj->mQuat[2];
  float qb = obj->mQuat[1];
  float dy = org[1] - obj->mPos[1];
  float dz = org[2] - obj->mPos[2];
  float qa = obj->mQuat[0];
  float lo[3];
  float ld[3];
  unsigned bestIdx = 0xffffffff;

  lo[0] = (((qc * qa + -(qb * qd)) * dz + (qb * qa - -(qc * qd)) * dy) + (-(qc * qc) + -(qb * qb)) * dx) * 2.0f + dx;
  lo[1] = (((qc * qb - -(qa * qd)) * dz + (-(qc * qc) + -(qa * qa)) * dy) + (qb * qa + -(qc * qd)) * dx) * 2.0f + dy;
  lo[2] = (((-(qb * qb) + -(qa * qa)) * dz + (qc * qb + -(qa * qd)) * dy) + (qc * qa - -(qb * qd)) * dx) * 2.0f + dz;

  float e0 = dir[0], e1 = dir[1], e2 = dir[2];
  qb = obj->mQuat[1];
  qd = obj->mQuat[3];
  qa = obj->mQuat[0];
  qc = obj->mQuat[2];
  ld[0] = (((-(qc * qc) + -(qb * qb)) * e0 + (qc * qa + -(qb * qd)) * e2) + (qb * qa - -(qc * qd)) * e1) * 2.0f + e0;
  ld[1] = (((-(qc * qc) + -(qa * qa)) * e1 + (qb * qa + -(qc * qd)) * e0) + (qc * qb - -(qa * qd)) * e2) * 2.0f + e1;
  ld[2] = (((qc * qa - -(qb * qd)) * e0 + (-(qb * qb) + -(qa * qa)) * e2) + (qc * qb + -(qa * qd)) * e1) * 2.0f + e2;

  unsigned i = 0;
  if ((obj->mpPartsEnd - obj->mpPartsBegin) != 0) {
    do {
      Part* part = &obj->mpPartsBegin[i];
      float t = FLT_MAX;
      float n[3] = {0.0f, 0.0f, 0.0f};
      BoxShape* shape = part->mpShape;
      float qz = part->mQuat[2];
      float qy = part->mQuat[1];
      float qx = part->mQuat[0];
      float s2 = obj->mScale * 2.0f;
      float ex = s2 * shape->mHalfExtent[0];
      float ey = shape->mHalfExtent[1] * s2;
      float qyz = qz * qy;
      float ez = shape->mHalfExtent[2] * s2;
      float qw = part->mQuat[3];
      float qwy = qw * qy;
      float m[9];
      m[0] = 1.0f - (qz * qz + qy * qy) * 2.0f;
      m[1] = (qy * qx - qw * qz) * 2.0f;
      m[2] = (qwy + qz * qx) * 2.0f;
      m[3] = (qw * qz + qy * qx) * 2.0f;
      m[4] = 1.0f - (qz * qz + qx * qx) * 2.0f;
      m[5] = (qyz - qw * qx) * 2.0f;
      m[6] = (qz * qx - qwy) * 2.0f;
      m[7] = (qw * qx + qyz) * 2.0f;
      m[8] = 1.0f - (qy * qy + qx * qx) * 2.0f;
      if (BoxRayTest(lo, ld, part->mCenter, m, ex, ey, ez, &t, n) && t < bestT && 0.0f <= t) {
        bestT = t;
        bestIdx = i;
        float tmp[3];
        float* r = QuaternionVectorTransform(tmp, obj->mQuat, n);
        bestN[0] = r[0];
        bestN[1] = r[1];
        bestN[2] = r[2];
      }
      ++i;
    } while (i < (unsigned)(obj->mpPartsEnd - obj->mpPartsBegin));
    if (bestIdx != 0xffffffff) {
      if (pT) *pT = bestT;
      if (pNormal) {
        pNormal[0] = bestN[0];
        pNormal[1] = bestN[1];
        pNormal[2] = bestN[2];
      }
      if (pHit) {
        float h1 = dir[1];
        float h2 = dir[2];
        float o1 = org[1];
        float o2 = org[2];
        pHit[0] = dir[0] * bestT + org[0];
        pHit[1] = h1 * bestT + o1;
        pHit[2] = h2 * bestT + o2;
      }
      if (pIndex) *pIndex = bestIdx;
      return true;
    }
  }
  return false;
}

// =====================================================================
// nSPCreatureAnim::AddExtraBonesAsNecessary and its helpers.
// The class layout below is the retail one seen through these six
// functions; PDB names are only used where the retail offsets agree.
// =====================================================================
namespace CA {

typedef unsigned int  u32;
typedef unsigned char u8;

struct Vec3 { float x, y, z; };

// nSPCreatureAnim::creature_part_caps (PDB, size 0xa0).
struct PartCaps {
  u32 NameFOURCCs[32];          // +0x00
  u8  Values[32];               // +0x80
};

// One entry of the +0x2e4 bone-mesh list (stride 0x2bc).  mpShape points at
// the part record described by CreaturePart.
struct BoneMesh {
  void* mpShape;                // +0x00
  char  pad04[0x0c];
  Vec3  mCenter;                // +0x10
  float mQuat[4];               // +0x1c
  char  pad2c[0x2bc - 0x2c];
};

// One entry of the +0x384 part list (stride 0x468).
struct CreaturePart {
  char  pad000[0x10c];
  Vec3  mA;                     // +0x10c local offset
  Vec3  mB;                     // +0x118 local offset
  char  pad124[0x150 - 0x124];
  u32   m150;                   // +0x150 capability flags of this part
  u32   m154;                   // +0x154 capability flags inherited from children
  PartCaps mCaps;               // +0x158
  void* m1f8;                   // +0x1f8 own spine constraint
  u32   m1fc;                   // +0x1fc next part index (0 == root)
  u32   m200;                   // +0x200
  u32   m204;                   // +0x204 first child index
  u32   m208;                   // +0x208 child count
  u32   m20c;                   // +0x20c
  u32   m210;                   // +0x210 traversal state
  CreaturePart* m214;           // +0x214 next part in the state chain
  CreaturePart* m218;           // +0x218 child array (stride 0x468)
  char  pad21c[0x464 - 0x21c];
  u8    m464;                   // +0x464
};

// One entry of the +0x3cc reference list (stride 8).
struct PartRef {
  CreaturePart* mPart;          // +0x00
  u32           mExtra;         // +0x04
};

// The object at +0x1688 that owns the workspace transform callback.
class WorkspaceSource {
public:
  u8    mUseOrigin;             // +0x00
  char  pad01[3];
  void* mCallback;              // +0x04
  void* mContext;               // +0x08
  Vec3* rotateInto(Vec3* out, const Vec3* v, int zero);   // 0x009a49d0
};

// One animation-bone record produced by the +0x15b8 pool (stride 0x108).
struct BoneRecord {
  char pad00[0x58];
  u32  mIndex;                  // +0x58
  char pad5c[0x108 - 0x5c];
  void finish();                // 0x009cf3c0
};

// The pool object embedded at +0x15b8.
struct BonePool {
  u32          addPart(void* owner, const Vec3* local, const Vec3* world);  // 0x009d7d10
  BoneRecord** storage();                                                   // 0x00a09f50
  char pad00[0x88];
};

// Constants read by the transform helpers.
extern float kWorkspaceDirEps;   // 0x014471fc  1e-6f
extern float kWorkspaceMinSq;    // 0x013eb960  0.01f
extern float kWorkspaceOne;      // 0x01485720  1.0f
extern float kOne;               // 0x01485720  1.0f

// Number of extra bones requested by the last script call.
extern int gExtraBoneCount;      // 0x01550d58

u32  FUN_009b3460(CreaturePart* part);                       // 0x009b3460
u32  FUN_009d7d10(BonePool* pool, void* owner, const Vec3* local, const Vec3* world);  // 0x009d7d10

// The owning creature record.
struct Creature {
  char  pad00[0x04];
  void* m04;                    // +0x04
  char  pad08[0x18 - 0x08];
  Vec3  m18;                    // +0x18
  char  pad24[0x70 - 0x24];
  float m70;                    // +0x70
  char  pad74[0x2e4 - 0x74];
  BoneMesh* mpBonesBegin;       // +0x2e4
  BoneMesh* mpBonesEnd;         // +0x2e8
  char  pad2ec[0x384 - 0x2ec];
  CreaturePart* mpPartsBegin;   // +0x384
  CreaturePart* mpPartsEnd;     // +0x388
  char  pad38c[0x3ac - 0x38c];
  u32   m3ac;                   // +0x3ac
  u32   m3b0;                   // +0x3b0
  char  pad3b4[0x3cc - 0x3b4];
  PartRef* mpRefsBegin;         // +0x3cc
  PartRef* mpRefsEnd;           // +0x3d0
  char  pad3d4[0x15b8 - 0x3d4];
  BonePool mPool;               // +0x15b8
  u32   m1640;                  // +0x1640
  char  pad1644[0x1688 - 0x1644];
  WorkspaceSource* mpSource;    // +0x1688

  Vec3* get_workspace_origin(Vec3* out, u32 unused);        // 0x009b61f0
  float set_workspace_dir(const Vec3* dir, Vec3* out);      // 0x009b6220
  Vec3* workspace_origin_for(Vec3* out, const Vec3* v);     // 0x009b62c0
  void  update_part_states();                               // 0x009b6360
};

void FUN_009b5ce0(Creature* c);                             // 0x009b5ce0
void FUN_009b5f90(u32 index, Creature* c);                  // 0x009b5f90

}  // namespace CA

using namespace CA;

// @ 0x009b61f0
Vec3* Creature::get_workspace_origin(Vec3* out, u32 unused)
{
  float* o = &out->x;
  const Vec3* c = &mpBonesBegin->mCenter;
  o[0] = c->x;
  o[1] = c->y;
  o[2] = c->z;
  return out;
}

// @ 0x009b6220
float Creature::set_workspace_dir(const Vec3* dir, Vec3* out)
{
  float result = 0.0f;
  WorkspaceSource* src = mpSource;
  if (src && src->mCallback) {
    if (src->mUseOrigin ||
        dir->x * dir->x + dir->y * dir->y + dir->z * dir->z > kWorkspaceDirEps) {
      result = ((float (__cdecl*)(void*, void*, const Vec3*, Vec3*, int, int))
                src->mCallback)(src->mContext, m04, dir, out, 0, 0);
      return result;
    }
  }
  if (out) {
    out->x = 0.0f;
    out->y = 0.0f;
    out->z = kWorkspaceOne;
  }
  return result;
}

// @ 0x009b62c0
Vec3* Creature::workspace_origin_for(Vec3* out, const Vec3* v)
{
  out->x = 0.0f;
  out->y = 0.0f;
  out->z = kWorkspaceOne;
  if (!v)
    v = &m18;
  WorkspaceSource* src = mpSource;
  if (src && src->mUseOrigin) {
    if (v->x * v->x + v->y * v->y + v->z * v->z > kWorkspaceMinSq) {
      Vec3 tmp;
      *out = *src->rotateInto(&tmp, v, 0);
    }
  }
  return out;
}

// @ 0x009b5ce0
void FUN_009b5ce0(Creature* c)
{
  u32 numParts = (u32)(c->mpPartsEnd - c->mpPartsBegin);
  u32 numRefs  = (u32)(c->mpRefsEnd - c->mpRefsBegin);
  int firstIdx = -1;
  int lastIdx  = -1;
  int bestIdx  = -1;
  bool viaRefs = true;

  if (numRefs != 0) {
    u32 i = 0;
    do {
      CreaturePart* part = c->mpRefsBegin[i].mPart;
      if (part->m1f8 == 0)
        bestIdx = (int)i;
      u32 n = part->m208;
      if (n > 0) {
        CreaturePart* child = part->m218;
        u32 k = 0;
        do {
          u32 flags = child->m150;
          if ((flags & 2) && !(flags & 8)) {
            if (firstIdx == -1)
              firstIdx = (int)i;
            lastIdx = (int)i;
          }
          child += 1;
          ++k;
        } while (k < n);
      }
      ++i;
    } while (i < numRefs);

    if (firstIdx != -1) {
      if (firstIdx > bestIdx)
        firstIdx = bestIdx;
      else if (lastIdx < bestIdx)
        lastIdx = bestIdx;
    }
    if (firstIdx == lastIdx)
      viaRefs = false;
  }

  if (viaRefs) {
    if (lastIdx > firstIdx) {
      /* nothing to mark */
    } else {
      int i = firstIdx;
      do {
        c->mpRefsBegin[i].mPart->m210 = 0x200;
        ++i;
      } while (i <= lastIdx);
    }
  } else {
    u32 n = (u32)gExtraBoneCount;
    c->mpPartsBegin->m210 = 0x200;
    if (n != 0) {
      int off = 0;
      u32 k = 0;
      do {
        int fwd = bestIdx + off;
        if ((u32)fwd < numRefs)
          ((PartRef*)((char*)c->mpRefsBegin + off * 8))->mPart->m210 = 0x200;
        int bwd = bestIdx - off;
        if ((u32)bwd < numRefs)
          ((PartRef*)((char*)c->mpRefsBegin - off * 8))->mPart->m210 = 0x200;
        ++off;
        ++k;
      } while (k < n);
    }
  }

  if (numParts > 0) {
    u32 off = 0;
    u32 i = 0;
    do {
      CreaturePart* p = (CreaturePart*)((char*)c->mpPartsBegin + off);
      if (p->m150 & 0x20) {
        CreaturePart* q = p;
        for (;;) {
          CreaturePart* nxt = q->m214;
          q->m210 = 0x200000;
          if (nxt->m210 != 0x200)
            break;
          q = nxt;
        }
      }
      off += 0x468;
      ++i;
    } while (i < numParts);
  }

  if (numRefs > 0) {
    u32 i = 0;
    do {
      CreaturePart* p = c->mpRefsBegin[i].mPart;
      if (p->m210 == 0)
        p->m210 = 0x10000;
      ++i;
    } while (i < numRefs);
  }

  if (numParts > 0) {
    u32 off = 0;
    u32 i = 0;
    do {
      CreaturePart* p = (CreaturePart*)((char*)c->mpPartsBegin + off);
      if (p->m210 == 0 && (p->m150 & 2))
        p->m210 = p->m464 ? 0x400000 : 0x100;
      off += 0x468;
      ++i;
    } while (i < numParts);
  }

  if (numParts > 1) {
    u32 off = 0x468;
    u32 i = 1;
    do {
      CreaturePart* p = (CreaturePart*)((char*)c->mpPartsBegin + off);
      if (p->m210 == 0) {
        CreaturePart* nxt = p->m214;
        u32 v = nxt->m210;
        p->m210 = v ? v : FUN_009b3460(nxt);
      }
      off += 0x468;
      ++i;
    } while (i < numParts);
  }
}

// @ 0x009b5f90
void FUN_009b5f90(u32 index, Creature* c)
{
  for (;;) {
    if (index == 0)
      return;
    CreaturePart* part = c->mpPartsBegin + index;

    if (part->m208 > 0) {
      CreaturePart* parent = c->mpPartsBegin + part->m204;
      u32 n = part->m208;
      u32 hits = 0;
      do {
        if (*(u8*)&parent->m154 & 2)
          ++hits;
        parent += 1;
        --n;
      } while (n != 0);
      if (hits > 1)
        return;
    }

    PartCaps* caps = &part->mCaps;
    u32* names = caps->NameFOURCCs;
    u32 ci = 0;
    for (;;) {
      u32 v = names[ci];
      if (v == 0x626d696c) {          // 'limb'
        caps->Values[ci] = 1;
        break;
      }
      if (v == 0) {
        names[ci] = 0x626d696c;
        caps->Values[ci] = 1;
        break;
      }
      if (++ci >= 32)
        break;
    }

    part->m154 = 0;
    part->m150 = 0;
    u32* nm = caps->NameFOURCCs;
    for (u32 k = 0; k < 32; ++k) {
      u32 v = nm[k];
      if (v == 0)
        break;
      u32 f;
      switch (v) {
        case 0x626d696c: f = 2;    break;   // 'limb'
        case 0x6e697073: f = 8;    break;   // 'spin'
        case 0x70737267: f = 0x40; break;   // 'grsp'
        case 0x7274736e: f = 0x80; break;   // 'nstr'
        case 0x74667370: f = 0x10; break;   // 'psft'
        case 0x746f6f66: f = 4;    break;   // 'foot'
        case 0x746f6f72: f = 1;    break;   // 'root'
        case 0x74756f6d: f = 0x20; break;   // 'mout'
        default:         f = 0;    break;
      }
      part->m150 |= f;
      if (caps->Values[k] != 0)
        part->m154 |= f;
    }

    u32 si = 0;
    for (;;) {
      u32 v = names[si];
      if (v == 0x6e697073) {          // 'spin'
        caps->Values[si] = 0;
        break;
      }
      if (v == 0) {
        names[si] = 0x6e697073;
        caps->Values[si] = 0;
        break;
      }
      if (++si >= 32)
        break;
    }

    part->m154 = 0;
    part->m150 = 0;
    u32* nm2 = caps->NameFOURCCs;
    for (u32 k = 0; k < 32; ++k) {
      u32 v = nm2[k];
      if (v == 0)
        break;
      u32 f;
      switch (v) {
        case 0x626d696c: f = 2;    break;   // 'limb'
        case 0x6e697073: f = 8;    break;   // 'spin'
        case 0x70737267: f = 0x40; break;   // 'grsp'
        case 0x7274736e: f = 0x80; break;   // 'nstr'
        case 0x74667370: f = 0x10; break;   // 'psft'
        case 0x746f6f66: f = 4;    break;   // 'foot'
        case 0x746f6f72: f = 1;    break;   // 'root'
        case 0x74756f6d: f = 0x20; break;   // 'mout'
        default:         f = 0;    break;
      }
      part->m150 |= f;
      if (caps->Values[k] != 0)
        part->m154 |= f;
    }

    index = part->m1fc;
  }
}

// @ 0x009b6360
void Creature::update_part_states()
{
  u32 count = (u32)(mpBonesEnd - mpBonesBegin);
  if (count == 0)
    return;

  u32 off = 0;
  for (u32 i = 0; i < count; ++i) {
    BoneMesh* bm = (BoneMesh*)((char*)mpBonesBegin + off);
    CreaturePart* part = (CreaturePart*)bm->mpShape;
    if (part->m150 & 4) {
      Vec3 local;
      local.x = part->mA.x * m70;
      local.y = part->mA.y * m70;
      local.z = part->mA.z * m70;
      u32 id = mPool.addPart(this, &local, &part->mB);
      m1640 = id + 1;
      BoneRecord* rec = (BoneRecord*)((char*)*mPool.storage() + id * 0x108);
      rec->mIndex = i;
      rec->finish();
    }
    off += 0x2bc;
  }
}
