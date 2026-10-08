// Slice s00b43d50: swept-sphere contact against a collision shape (0x00b43d50, 1893 bytes).
//
// `a` is a moving sphere (radius = mRadius * mScale) whose motion this step is the segment
// A..B (Collider::GetSegment 0x00b42370).  `b` is the other collider.  If the distance from b's
// center to the segment is more than the radii sum, nothing happens.  If b is a flat mesh-like
// shape (type 2, or type 0/1 with the flag byte at +0x71 of its impl set; hull from
// GetHull 0x00b3d6a0 with at least 3 points), the segment is brought into b's local frame
// (scale forced to 1), flattened to z = 0, and the polygon outline is searched for the edge
// nearest to either end; the contact is pushed out along that edge's normal (flipped when the
// end point lies inside the polygon) and written as a single point to the manifest.  Otherwise
// (sphere/capsule-like b) the contact is along the line from the closest point of the segment
// to b's center.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (as s00b3fe40: scalar SSE, sqrt in x87).
#include "types.h"
#include <float.h>
#include <math.h>

// SSE max(0, b) helper of the module (maxss with SSE NaN semantics: a NaN in b yields b).
__forceinline float MaxZero(float b)
{
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, b
        movss b, xmm0
    }
    return b;
}

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};

struct BoundingBox {
    Vector3 lower, upper;
    BoundingBox();  // 0x00576b40 (FLT_MAX / -FLT_MAX)
};

// Contact output (same layout as s00b3fe40).
struct ContactManifold {
    Vector3 mPoints[16];   // +0x000
    Vector3 mPointsB[16];  // +0x0c0
    int mCount;            // +0x180
    Vector3 mNormal;       // +0x184
    float mf190;           // +0x190
    Vector3 mPenetration;  // +0x194
};

struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3 mTranslation;  // +0x04
    float mScale;          // +0x10
    float mRotation[9];    // +0x14
    cSPTransform();                          // 0x00409930
    void BackTransformPoint(Vector3* p);     // 0x004ff6d0
    void TransformVector(Vector3* v);        // 0x0049d640
};

struct Polyline {
    uint8_t pad[0x4c];
    Vector3* mpBegin;  // +0x4c
    Vector3* mpEnd;    // +0x50
};

struct ColliderImpl {
    uint8_t pad[0x71];
    uint8_t mbHasHull;  // +0x71
};

struct Collider {
    uint32_t pad0;
    int mType;                 // +0x04
    uint8_t pad1[0x08];
    float mScale;              // +0x10
    uint8_t pad2[0x2c];
    ColliderImpl* mpImpl;      // +0x40
    uint8_t pad3[0xf0];
    float mRadius;             // +0x134

    void GetSegment(Vector3* a, Vector3* b);       // 0x00b42370
    void GetCenter(Vector3* out);                  // 0x00b3d9c0
    float GetRadius();                             // 0x00b3d630
    Polyline* GetHull();                           // 0x00b3d6a0
    void GetTransform(cSPTransform* out);          // 0x00b3f6c0
    void AddToBoundingBox(BoundingBox* box);       // 0x00b3f420
};

float PointSegmentDistance(const Vector3* p, const Vector3* a, const Vector3* b);          // 0x00698b30
Vector3* ClosestOnSegment(Vector3* out, const Vector3* p, const Vector3* a, const Vector3* b);  // 0x00698e00
bool PointInsidePolygon(const Vector3* verts, int count, const Vector3* p);                // 0x0069a050
Vector3* normalized_safe(Vector3* out, const Vector3* in);                                 // 0x00449c20

// @ 0x00b43d50
void SweptSphereContact(Collider* a, Collider* b, ContactManifold* out)
{
    Vector3 segA, segB;
    a->GetSegment(&segA, &segB);
    float radiusA = a->mRadius * a->mScale;
    Vector3 center;
    b->GetCenter(&center);
    float sumR = b->GetRadius() + radiusA;
    float dist = PointSegmentDistance(&center, &segA, &segB);
    if (!(sumR >= dist))
        return;

    if (b->mType == 0 || b->mType == 1) {
        if (!b->mpImpl->mbHasHull)
            goto simple;
    }
    {
        Polyline* hull = b->GetHull();
        if (hull && (unsigned)(hull->mpEnd - hull->mpBegin) >= 3) {
            cSPTransform xform;
            b->GetTransform(&xform);
            xform.mScale = 1.0f;
            Vector3 pa = segA;
            Vector3 pb = segB;
            xform.mModificationCount++;
            xform.BackTransformPoint(&pa);
            xform.BackTransformPoint(&pb);
            const float* pz = &pb.z;
            if (pa.z <= pb.z)
                pz = &pa.z;
            {
                float lowBound = MaxZero(*pz - radiusA);
                BoundingBox box;
                b->AddToBoundingBox(&box);
                if (lowBound > box.upper.z - box.lower.z)
                    return;
            }

            pa.z = 0.0f;
            pb.z = 0.0f;
            Vector3 prev = hull->mpBegin[0];
            int count = hull->mpEnd - hull->mpBegin;
            int bestIndex = 0;
            int bestEnd = 0;
            float bestDist = FLT_MAX;
            for (int i = 1; i < count; i++) {
                const Vector3* cur = &hull->mpBegin[i];
                float da = PointSegmentDistance(&pa, &prev, cur);
                float db = PointSegmentDistance(&pb, &prev, cur);
                if (bestDist > da) {
                    bestEnd = 0;
                    bestDist = da;
                    bestIndex = i;
                } else if (db < bestDist) {
                    bestEnd = 1;
                    bestDist = db;
                    bestIndex = i;
                }
                prev = *cur;
            }
            if (bestIndex == 0)
                return;

            const Vector3* seg = &hull->mpBegin[bestIndex];
            Vector3 tmp;
            Vector3 dir;
            const Vector3* ep;
            if (bestEnd == 0) {
                Vector3* q = ClosestOnSegment(&tmp, &pa, seg - 1, seg);
                dir.x = q->x - pa.x;
                dir.y = q->y - pa.y;
                dir.z = q->z - pa.z;
                Vector3* nn = normalized_safe(&tmp, &dir);
                dir.x = nn->x;
                dir.y = nn->y;
                dir.z = nn->z;
                ep = &pa;
            } else {
                Vector3* q = ClosestOnSegment(&tmp, &pb, seg - 1, seg);
                dir.x = q->x - pb.x;
                dir.y = q->y - pb.y;
                dir.z = q->z - pb.z;
                Vector3* nn = normalized_safe(&tmp, &dir);
                dir.x = nn->x;
                dir.y = nn->y;
                dir.z = nn->z;
                ep = &pb;
            }
            bool inside = PointInsidePolygon(hull->mpBegin, (int)(hull->mpEnd - hull->mpBegin), ep);
            float depth;
            if (inside) {
                dir.x = dir.x * -1.0f;
                dir.y = dir.y * -1.0f;
                dir.z = dir.z * -1.0f;
                depth = bestDist;
            } else {
                depth = radiusA - bestDist;
            }
            if (0.0f > depth)
                return;
            xform.TransformVector(&dir);
            float push = radiusA - depth;
            const Vector3* base = bestEnd ? &segB : &segA;
            out->mPoints[0].x = base->x + dir.x * push;
            out->mPoints[0].y = base->y + dir.y * push;
            out->mPoints[0].z = base->z + dir.z * push;
            out->mPointsB[0] = out->mPoints[0];
            out->mNormal = dir;
            out->mCount = 1;
            out->mPenetration.x = out->mNormal.x * depth;
            out->mPenetration.y = out->mNormal.y * depth;
            out->mPenetration.z = out->mNormal.z * depth;
            out->mf190 = 0.0f;
            return;
        }
    }
simple:
    {
        Vector3 q;
        ClosestOnSegment(&q, &center, &segA, &segB);
        float vx = center.x - q.x;
        float vy = center.y - q.y;
        float vz = center.z - q.z;
        out->mCount = 1;
        float inv = (float)(1.0 / sqrt((double)(vx * vx + (vy * vy + vz * vz)) + 1e-8f));
        float pen = sumR - dist;
        float t = radiusA - pen;
        float nx = vx * inv;
        float ny = vy * inv;
        float nz = vz * inv;
        out->mPoints[0].z = nz * t + center.z;
        out->mPoints[0].x = nx * t + center.x;
        out->mPoints[0].y = ny * t + center.y;
        out->mPointsB[0] = out->mPoints[0];
        out->mNormal.x = nx;
        out->mNormal.y = ny;
        out->mNormal.z = nz;
        out->mPenetration.x = out->mNormal.x * pen;
        out->mPenetration.y = out->mNormal.y * pen;
        out->mPenetration.z = out->mNormal.z * pen;
        out->mf190 = 0.0f;
    }
}
