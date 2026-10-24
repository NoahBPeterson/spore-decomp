// slice s00a7d5e0: ref-counted element copy helpers, a transform-vector rotation, two quad-plane
// transform builders, and the Swarm quad collider setup at 0x00a7d8a0 (preserved from the earlier
// slice). Quad setup takes a corner plus two edge vectors, builds the four corners and unit normal,
// assigns the source transform, moves points/normal through the world transform (rotation if flag
// 2, uniform scale, translation), recomputes the plane offset and records the dominant normal axis
// (0, 1 or 2) at +0x78.  Class and member names are coined.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
  Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

static inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
static inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
static inline float Dot(const Vector3& a, const Vector3& b) { return a.z * b.z + a.y * b.y + a.x * b.x; }

struct Matrix3 {
  Vector3 row[3];
  void CopyFrom(const Matrix3* src);        // 0x0041cb40
};

// PDB cSPTransform: flags, modification count, translation, scale, rotation (size 0x38)
struct cSPTransform {
  uint16_t mFlags;
  uint16_t mModificationCount;
  Vector3 mTranslation;
  float mScale;
  Matrix3 mRotation;
  void operator=(const cSPTransform& o);    // 0x00537dc0
  void RotateVector(Vector3* v);            // 0x00a7d6b0
  void Invert();                            // 0x00a7d770
  void TransformInversePoint(Vector3* p);   // 0x007cda70
};

static inline Vector3 Rotate(const Matrix3& m, const Vector3& v) {
  return Vector3(m.row[0].x * v.x + m.row[1].x * v.y + m.row[2].x * v.z,
                 m.row[0].y * v.x + m.row[1].y * v.y + m.row[2].y * v.z,
                 m.row[0].z * v.x + m.row[1].z * v.y + m.row[2].z * v.z);
}

// Quad (corner, edge u, edge v) referenced from the owner at +0x40.
struct QuadSource {
  Vector3 corner, u, v;
};
struct QuadOwner {
  uint8_t pad[0x40];
  QuadSource* mpQuad;
};

struct QuadPlane {
  Vector3 normal;          // +0x00
  float d;                 // +0x0c
  Vector3 pt[4];           // +0x10
  cSPTransform transform;  // +0x40
  int axis;                // +0x78 dominant normal axis
};

static __forceinline void TransformPoint(const cSPTransform* t, Vector3& p) {
  if (t->mFlags & 2)
    p = Rotate(t->mRotation, p);
  p = p * t->mScale;
  p = t->mTranslation + p;
}

// @ 0x00a7d8a0
void __stdcall BuildQuadPlane(QuadOwner* owner, cSPTransform* xf, const cSPTransform* src, QuadPlane* out) {
  const QuadSource* q = owner->mpQuad;
  Vector3 v = q->v;
  Vector3 u = q->u;
  out->pt[0] = q->corner;
  out->pt[1] = out->pt[0] + u;
  out->pt[2] = out->pt[1] + v;
  out->pt[3] = out->pt[0] + v;
  float nz = v.y * u.x - u.y * v.x;
  float ny = u.z * v.x - v.z * u.x;
  float nx = v.z * u.y - v.y * u.z;
  // Accumulate the length-squared in double (x87 here, /arch:SSE has no SSE2) so the
  // squares are summed in the original's nz, ny, nx order; /fp:fast otherwise reassociates
  // the plain float expression into nx, ny, nz and lands 1 ulp off.
  double sum = (double)nz * nz;
  sum = sum + (double)ny * ny;
  sum = sum + (double)nx * nx;
  float inv = (float)(1.0 / sqrt(sum + 1e-8f));
  out->normal = Vector3(inv * nx, ny * inv, nz * inv);
  out->transform = *src;
  TransformPoint(xf, out->pt[0]);
  TransformPoint(xf, out->pt[1]);
  TransformPoint(xf, out->pt[2]);
  TransformPoint(xf, out->pt[3]);
  if (xf->mFlags & 2)
    out->normal = Rotate(xf->mRotation, out->normal);
  out->d = -Dot(out->normal, out->pt[0]);
  float ax = fabsf(out->normal.x), ay = fabsf(out->normal.y), az = fabsf(out->normal.z);
  int axis;
  if (ax <= ay) {
    if (ay > az)
      axis = 1;
    else
      axis = 2;
  } else {
    if (ax > az)
      axis = 0;
    else
      axis = 2;
  }
  out->axis = axis;
}

// ---------------------------------------------------------------------------------------------------
// Ref-counted 0x18-byte element copy helpers used by the order/transform vectors around this module.
// ---------------------------------------------------------------------------------------------------

struct RefTarget {
  void* mpVtable;                    // +0x00
  void AddRef() { ((void (__thiscall*)(RefTarget*))((void**)mpVtable)[1])(this); }
  void Release() { ((void (__thiscall*)(RefTarget*))((void**)mpVtable)[0])(this); }
};

struct RefElement {
  RefTarget* mpObject;               // +0x00
  uint32_t mData[5];                 // +0x04 .. +0x17
};

// @ 0x00a7d5e0
RefElement* __cdecl CopyRefElements(const RefElement* first, const RefElement* last, RefElement* dst) {
  while (first != last) {
    if (dst) {
      RefTarget* pObject = first->mpObject;
      dst->mpObject = pObject;
      if (pObject)
        pObject->AddRef();
      dst->mData[0] = first->mData[0];
      dst->mData[1] = first->mData[1];
      dst->mData[2] = first->mData[2];
      dst->mData[3] = first->mData[3];
      dst->mData[4] = first->mData[4];
    }
    ++first;
    ++dst;
  }
  return dst;
}

// @ 0x00a7d640
RefElement* __cdecl CopyRefElementsBackward(const RefElement* first, const RefElement* last, RefElement* dstEnd) {
  while (last != first) {
    --last;
    --dstEnd;
    RefTarget* pNew = last->mpObject;
    RefTarget* pOld = dstEnd->mpObject;
    if (pNew != pOld) {
      if (pNew)
        pNew->AddRef();
      dstEnd->mpObject = pNew;
      if (pOld)
        pOld->Release();
    }
    dstEnd->mData[0] = last->mData[0];
    dstEnd->mData[1] = last->mData[1];
    dstEnd->mData[2] = last->mData[2];
    dstEnd->mData[3] = last->mData[3];
    dstEnd->mData[4] = last->mData[4];
  }
  return dstEnd;
}

// @ 0x00a7d6b0
void cSPTransform::RotateVector(Vector3* v) {
  if (!(mFlags & 2))
    return;
  Vector3 r;
  r.x = mRotation.row[1].x * v->y;
  r.x += mRotation.row[2].x * v->z;
  r.x += mRotation.row[0].x * v->x;
  r.y = mRotation.row[0].y * v->x;
  r.y += mRotation.row[1].y * v->y;
  r.y += mRotation.row[2].y * v->z;
  r.z = mRotation.row[0].z * v->x;
  r.z += mRotation.row[1].z * v->y;
  r.z += mRotation.row[2].z * v->z;
  *v = r;
}

// ---------------------------------------------------------------------------------------------------
// Quad-plane transforms.  The source object carries flags at +0x00 and a one-element quad vector at
// +0x40/+0x44.  The output carries a transform followed by the plane normal and offset.
// ---------------------------------------------------------------------------------------------------

struct QuadPlaneElement {
  Vector3 mNormal;                   // +0x00
  float mD;                          // +0x0c
};

struct QuadPlaneSource {
  uint32_t mFlags;                   // +0x00
  uint8_t pad04[0x40 - 0x04];
  QuadPlaneElement* mpBegin;         // +0x40
  QuadPlaneElement* mpEnd;           // +0x44
};

struct QuadOutput {
  cSPTransform mTransform;           // +0x00
  Vector3 mNormal;                   // +0x38
  float mD;                          // +0x44
};

struct cPlane {
  cSPTransform mTransform;           // +0x00
  Vector3 mOrigin;                   // +0x38
  float mD;                          // +0x44
};

extern Vector3 g_zeroVector;         // 0x0167764c
extern Matrix3 g_identityMatrix;     // 0x016776f8
extern float g_one;                  // 0x01485720
extern float g_projectionEpsilon;    // 0x013f11c8

// @ 0x00a7df80
void __stdcall BuildQuadOutput(const QuadPlaneSource* src, const cSPTransform* xf,
                               const cSPTransform* altXf, QuadOutput* out) {
  if ((src->mFlags >> 6) & 1) {
    out->mTransform = *xf;
    out->mTransform.Invert();
  } else if ((src->mFlags >> 7) & 1) {
    out->mTransform = *altXf;
  } else {
    cSPTransform identity;
    identity.mTranslation = g_zeroVector;
    identity.mFlags = 0;
    identity.mModificationCount = 0;
    identity.mScale = g_one;
    identity.mRotation.CopyFrom(&g_identityMatrix);
    out->mTransform = identity;
  }
  QuadPlaneElement* p = src->mpBegin;
  if (p != src->mpEnd) {
    out->mNormal = p->mNormal;
    out->mD = p->mD;
  } else {
    out->mNormal = g_zeroVector;
    out->mD = g_one;
  }
}

// @ 0x00a7e080
bool __stdcall ProjectPoint(float offset, void* unused1, Vector3* pPoint, Vector3* pNormal,
                            cPlane* pPlane, void* unused2) {
  cSPTransform* xf = &pPlane->mTransform;
  Vector3 p = *pPoint;

  if (xf->mScale != g_one || (xf->mFlags & 6) != 0) {
    if (xf->mFlags & 2) {
      Vector3 r;
      r.x = xf->mRotation.row[1].x * p.y + xf->mRotation.row[2].x * p.z + xf->mRotation.row[0].x * p.x;
      r.y = xf->mRotation.row[0].y * p.x + xf->mRotation.row[1].y * p.y + xf->mRotation.row[2].y * p.z;
      r.z = xf->mRotation.row[0].z * p.x + xf->mRotation.row[1].z * p.y + xf->mRotation.row[2].z * p.z;
      p = r;
    }
    p = p * xf->mScale;
    p = xf->mTranslation + p;
  }

  Vector3 rel(p.x - pPlane->mOrigin.x,
              p.y - pPlane->mOrigin.y,
              p.z - pPlane->mOrigin.z + g_projectionEpsilon);
  float dist = sqrtf(rel.x * rel.x + rel.y * rel.y + rel.z * rel.z);
  float d = pPlane->mD + offset;
  if (d <= dist)
    return false;

  float inv = g_one / dist;
  Vector3 n = rel * inv;
  Vector3 projected = pPlane->mOrigin + n * d;
  xf->TransformInversePoint(&projected);
  *pPoint = projected;

  if (xf->mFlags & 2) {
    Vector3 r;
    r.x = xf->mRotation.row[1].x * n.y + xf->mRotation.row[2].x * n.z + xf->mRotation.row[0].x * n.x;
    r.y = xf->mRotation.row[0].y * n.x + xf->mRotation.row[1].y * n.y + xf->mRotation.row[2].y * n.z;
    r.z = xf->mRotation.row[0].z * n.x + xf->mRotation.row[1].z * n.y + xf->mRotation.row[2].z * n.z;
    *pNormal = r;
  } else {
    *pNormal = n;
  }
  return true;
}
