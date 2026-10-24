// Slice s00b16620: FUN_00b16620 (cdecl), "does the moving shape `q` touch the spatial object
// `obj`?" Cheap bounding-sphere reject, then the shape's reference point and its 9 sample
// points are tested against the object's local-space box (the object's transform inverted).
// When `out` is given it receives the push-out direction scaled by how deep the shape
// sits (ray from outside the box back along the direction, box slab test at 0x00698880).
// Class and field names are Claude-coined from usage.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };          // plain POD: copies go through integer registers
struct Matrix3 {
    float m[9];
    void Assign(const Matrix3* src);     // 0x0041CB40 (thiscall ret 4)
};

extern Vec3 kTransformOrigin;            // 0x0167BDB4
extern Matrix3 kIdentity;                // 0x0167BE00

// Local-to-world transform of a spatial object (0x38 bytes).
struct PartTransform {
    union {
        uint32_t flags;                  // bit 1: has rotation
        struct { uint16_t flagsLo, flagsHi; };
    };
    Vec3 pos;                            // +0x04
    float scale;                         // +0x10
    Matrix3 mat;                         // +0x14
    PartTransform()
    {
        pos.x = kTransformOrigin.x;
        pos.y = kTransformOrigin.y;
        flagsHi = 0;
        pos.z = kTransformOrigin.z;
        flagsLo = 0;
        scale = 1.0f;
        mat.Assign(&kIdentity);
    }
    void Invert();                       // 0x0040EFA0
};

#define V(n) virtual void v##n()
struct cSpatialObject {
    V(00); V(04); V(08); V(0c); V(10); V(14); V(18); V(1c); V(20); V(24); V(28);
    virtual const Vec3* GetPosition();                               // +0x2C
    V(30); V(34); V(38); V(3c); V(40); V(44); V(48); V(4c); V(50); V(54); V(58); V(5c);
    V(60); V(64);
    virtual const float* GetBounds();                                // +0x68 (min[3], max[3])
    V(6c);
    virtual float GetRadius();                                       // +0x70
    uint32_t pad_04[(0x50 - 0x04) / 4];
    uint32_t mFlags;                                                 // +0x50
    void LocalToWorldTransform(PartTransform* out);                  // 0x00C897E0
};

struct cShape {
    Vec3 pts[9];                         // +0x00; pts[4] (+0x30) is the reference point
};
struct cQuery {
    Vec3 mDir;                           // +0x00
    uint8_t pad_0c[0x48 - 0x0C];
    cShape* mpShape;                     // +0x48
    uint8_t pad_4c[0xCC - 0x4C];
    float mRadius;                       // +0xCC
};

Vec3* normalized_safe(Vec3* dst, const Vec3* src);                   // 0x00449C20 (cdecl)
bool RayBoxHit(const Vec3* origin, const Vec3* dir, const float* box, float* tOut);   // 0x00698880 (cdecl)

// @ 0x00B16620
bool TestShapeHitsObject(cQuery* q, cSpatialObject* obj, Vec3* out)
{
    uint32_t objFlags = obj->mFlags;
    if ((objFlags & 0x10) && !(objFlags & 0x20))
        return false;

    const float* b0 = obj->GetBounds();
    float half = (b0[5] - b0[2]) * 0.5f;
    const Vec3* oc = obj->GetPosition();
    cShape* shape = q->mpShape;
    Vec3 d, p, e, nd;
    float t;
    d.x = shape->pts[4].x - (oc->x + half);
    d.y = shape->pts[4].y - (oc->y + half);
    d.z = shape->pts[4].z - (oc->z + half);
    float r = obj->GetRadius() * 2.0f + q->mRadius;
    float rr = r * r;
    float d2 = (d.x * d.x + d.z * d.z) + d.y * d.y;
    if (!(rr > d2))
        return false;

    const float* box = obj->GetBounds();
    PartTransform T;
    obj->LocalToWorldTransform(&T);
    T.Invert();
    bool rot = (T.flags & 2) != 0;

    // reference direction of the query, into the object's space
    float ax = q->mDir.x, ay = q->mDir.y, az = q->mDir.z;
    if (rot) {
        float nx = (T.mat.m[6] * az + T.mat.m[3] * ay) + T.mat.m[0] * ax;
        float ny = (ax * T.mat.m[1] + ay * T.mat.m[4]) + az * T.mat.m[7];
        float nz = (ax * T.mat.m[2] + ay * T.mat.m[5]) + az * T.mat.m[8];
        ax = nx; ay = ny; az = nz;
    }
    p.x = T.pos.x + T.scale * ax;
    p.y = T.pos.y + ay * T.scale;
    p.z = T.pos.z + az * T.scale;
    if (box[0] <= p.x && p.x <= box[3] && box[1] <= p.y && p.y <= box[4] && box[2] <= p.z && p.z <= box[5]) {
        if (out) {
            const Vec3* c = obj->GetPosition();
            d.x = shape->pts[4].x - c->x;
            d.y = shape->pts[4].y - c->y;
            d.z = shape->pts[4].z - c->z;
            *out = *normalized_safe(&nd, &d);
            float vx = out->x, vy = out->y, vz = out->z;
            if (rot) {
                float nx = (vx * T.mat.m[0] + vz * T.mat.m[6]) + vy * T.mat.m[3];
                float ny = (vx * T.mat.m[1] + vy * T.mat.m[4]) + vz * T.mat.m[7];
                float nz = (vx * T.mat.m[2] + vy * T.mat.m[5]) + vz * T.mat.m[8];
                vx = nx; vy = ny; vz = nz;
            }
            float ex = box[3] - box[0], ey = box[4] - box[1], ez = box[5] - box[2];
            float len = sqrtf((ez * ez + ey * ey) + ex * ex);
            e.x = vx * len + p.x;
            e.y = vy * len + p.y;
            e.z = vz * len + p.z;
            nd.x = -vx; nd.y = -vy; nd.z = -vz;
            if (RayBoxHit(&e, &nd, box, &t)) {
                float s = len - t;
                out->x = s * out->x;
                out->y = out->y * s;
                out->z = out->z * s;
            }
        }
        return true;
    }

    for (int i = 8; i >= 0; --i) {
        const Vec3& sp = shape->pts[i];
        float sx = sp.x, sy = sp.y, sz = sp.z;
        if (rot) {
            float nx = (sx * T.mat.m[0] + sz * T.mat.m[6]) + sy * T.mat.m[3];
            float ny = (sx * T.mat.m[1] + sy * T.mat.m[4]) + sz * T.mat.m[7];
            float nz = (sx * T.mat.m[2] + sy * T.mat.m[5]) + sz * T.mat.m[8];
            sx = nx; sy = ny; sz = nz;
        }
        p.x = T.pos.x + T.scale * sx;
        p.y = T.pos.y + sy * T.scale;
        p.z = T.pos.z + sz * T.scale;
        if (box[0] <= p.x && p.x <= box[3] && box[1] <= p.y && p.y <= box[4] && box[2] <= p.z && p.z <= box[5]) {
            if (!out)
                return true;
            const Vec3* c = obj->GetPosition();
            float dx = shape->pts[4].x - c->x;
            float dz = shape->pts[4].z - c->z;
            float dy = shape->pts[4].y - c->y;
            float inv = 1.0f / sqrtf(((dx * dx + dz * dz) + dy * dy) + 1e-8f);
            out->x = inv * dx;
            out->y = dy * inv;
            out->z = dz * inv;
            float vx = out->x, vy = out->y, vz = out->z;
            if (rot) {
                float nx = (vx * T.mat.m[0] + vz * T.mat.m[6]) + vy * T.mat.m[3];
                float ny = (vx * T.mat.m[1] + vy * T.mat.m[4]) + vz * T.mat.m[7];
                float nz = (vx * T.mat.m[2] + vy * T.mat.m[5]) + vz * T.mat.m[8];
                vx = nx; vy = ny; vz = nz;
            }
            float ex = box[3] - box[0], ey = box[4] - box[1], ez = box[5] - box[2];
            float len = sqrtf((ez * ez + ey * ey) + ex * ex);
            e.x = vx * len + p.x;
            e.y = vy * len + p.y;
            e.z = vz * len + p.z;
            nd.x = -vx; nd.y = -vy; nd.z = -vz;
            if (!RayBoxHit(&e, &nd, box, &t))
                return true;
            float s = len - t;
            out->x = s * out->x;
            out->y = out->y * s;
            out->z = out->z * s;
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00B16DC0 / 0x00B16E50: the camera-frame bookkeeping that goes with the shape
// query above.  The first fills a small view snapshot from the active viewer,
// the second slides/reflects the query's working point and direction against a
// path of points kept in an inline vector.  Class and field names are
// Claude-coined from usage.
// ---------------------------------------------------------------------------

// vec3 vector: 3 pointers + size/capacity, inline storage lives in its owner.
template <class T>
struct SpVector {
    T* mpBegin;                       // +0x00
    T* mpEnd;                         // +0x04
    T* mpEndCapacity;                 // +0x08
    uint32_t mSize;                   // +0x0c
    uint32_t mCapacity;               // +0x10
    T* erase(T* first, T* last);      // 0x0050F740
};

namespace SP {
class cViewer {
public:
    // out: position, direction, up, right
    void GetCameraLocationInfo(Vec3* pos, Vec3* dir, Vec3* up, Vec3* right) const;   // 0x007C3D30
    float FUN_007c3c90() const;                                                     // 0x007C3C90
    void FUN_007c40c0(float* a, float* b);                                          // 0x007C40C0
};
}

// Snapshot of the camera state, rebuilt by cCameraFrame::Initialize.
struct cCameraFrame {
    Vec3 mV00;                        // +0x00 camera position
    Vec3 mV0c;                        // +0x0c camera direction
    Vec3 mV18;                        // +0x18 camera up
    Vec3 mV24;                        // +0x24 camera right
    float mF30;                       // +0x30 viewer query 0x7c3c90
    float mF34;                       // +0x34 viewer query 0x7c40c0 arg 1
    float mF38;                       // +0x38 viewer query 0x7c40c0 arg 2
    Vec3 mDir;                        // +0x3c default direction (transform origin)
    SpVector<Vec3> mPoints;           // +0x48 inline point vector
    int mFlag5c;                      // +0x5c
    Vec3 mInline[9];                  // +0x60 inline storage of mPoints
    float mFcc;                       // +0xcc
    uint32_t mD0;                     // +0xd0
    uint32_t mD4;                     // +0xd4

    cCameraFrame* Initialize(SP::cViewer* viewer);   // 0x00B16DC0
};

// @ 0x00B16DC0
cCameraFrame* cCameraFrame::Initialize(SP::cViewer* viewer)
{
    mDir.x = kTransformOrigin.x;
    mDir.y = kTransformOrigin.y;
    mDir.z = kTransformOrigin.z;
    mPoints.mpBegin = mInline;
    mPoints.mpEnd = mInline;
    mFlag5c = 0;
    mPoints.mpEndCapacity = mPoints.mpBegin + 9;
    mD0 = 0;
    mD4 = 0;
    mFcc = 0.0f;
    viewer->GetCameraLocationInfo(&mV00, &mV0c, &mV18, &mV24);
    mF30 = viewer->FUN_007c3c90();
    viewer->FUN_007c40c0(&mF34, &mF38);
    return this;
}

// --- the queried object's provider chain (vtable slots reached by fixed offset)
struct cDirSource {                   // embedded in cProvider at +0x120
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vec3* GetDirection();          // +0x2c
};

struct cProvider {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68();
    virtual void* GetSub();                      // +0x6c
    uint32_t pad004[0x47];                       // +0x04 .. +0x120
    cDirSource mDirSource;                       // +0x120
};

struct cShapeSource {                 // embedded in cSubHolder at +0x34
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64();
    virtual void* GetShapeData();                // +0x68
};

struct cSubHolder {
    uint32_t pad000[0x0d];                       // +0x00 .. +0x34
    cShapeSource mSource;                        // +0x34
};

struct cShapeData {
    uint32_t pad000[3];                          // +0x00 .. +0x0c
    Vec3 mVec;                                   // +0x0c
};

class cPlanetModel;                              // SP::cPlanetModel
cPlanetModel* SP_PlanetModel();                  // 0x00B3D350
class cPlanetModel {
public:
    float GetRadiusAt(const void* coords);       // 0x00B7EF70
};

// Input descriptor of one query update: a point and a case id 1..4.
struct cShapeInput {
    Vec3 mPos;                        // +0x00
    int mType;                        // +0x0c
};

// The shape query state moved by FUN_00b16e50.
struct cShapeQuery {
    Vec3 mPos;                        // +0x00 working point
    uint32_t pad0c[6];                // +0x0c .. +0x24
    Vec3 mNormal;                     // +0x24 unit normal
    uint32_t pad30[3];                // +0x30 .. +0x3c
    Vec3 mDir;                        // +0x3c query direction
    SpVector<Vec3> mPoints;           // +0x48 path points
    uint8_t pad5c[0x78];              // +0x5c .. +0xd4
    cProvider* mpProvider;            // +0xd4

};

void FUN_00b16e50(cShapeQuery* self, const cShapeInput* in);   // 0x00B16E50

// @ 0x00B16E50
void FUN_00b16e50(cShapeQuery* self, const cShapeInput* in)
{
    SpVector<Vec3>* vec = &self->mPoints;
    const Vec3* src = self->mpProvider->mDirSource.GetDirection();
    void* sub = self->mpProvider->GetSub();
    cShapeData* data = (cShapeData*)((cSubHolder*)sub)->mSource.GetShapeData();

    Vec3 dir;
    float inv = 1.0f / sqrtf(src->x * src->x + (src->y * src->y + src->z * src->z));
    dir.x = src->x * inv;
    dir.y = src->y * inv;
    dir.z = src->z * inv;

    float fExtra = data->mVec.z;
    float radius = SP_PlanetModel()->GetRadiusAt(self);

    Vec3 pos = self->mPos;
    Vec3* pts = vec->mpBegin;
    Vec3 diff;
    diff.x = pos.x - pts[6].x;
    diff.y = pos.y - pts[6].y;
    diff.z = pos.z - pts[6].z;
    float dist = sqrtf(diff.x * diff.x + (diff.y * diff.y + diff.z * diff.z));
    bool moved = self->mDir.x != kTransformOrigin.x ||
                 self->mDir.y != kTransformOrigin.y ||
                 self->mDir.z != kTransformOrigin.z;

    switch (in->mType) {
    case 1: {
        Vec3 d;
        d.x = in->mPos.x - pts[8].x;
        d.y = in->mPos.y - pts[8].y;
        d.z = in->mPos.z - pts[8].z;
        float t = sqrtf(d.x * d.x + (d.y * d.y + d.z * d.z));
        float nx = self->mNormal.x * t, ny = self->mNormal.y * t, nz = self->mNormal.z * t;
        self->mPos.x = pos.x - nx;
        self->mPos.y = pos.y - ny;
        self->mPos.z = pos.z - nz;
        if (moved) {
            self->mDir.x = self->mDir.x - nx;
            self->mDir.y = self->mDir.y - ny;
            self->mDir.z = self->mDir.z - nz;
        }
        break;
    }
    case 2: {
        Vec3 d;
        d.x = in->mPos.x - pts[6].x;
        d.y = in->mPos.y - pts[6].y;
        d.z = in->mPos.z - pts[6].z;
        float t = sqrtf(d.x * d.x + (d.y * d.y + d.z * d.z));
        float nx = self->mNormal.x * t, ny = self->mNormal.y * t, nz = self->mNormal.z * t;
        self->mPos.x = pos.x + nx;
        self->mPos.y = pos.y + ny;
        self->mPos.z = pos.z + nz;
        if (moved) {
            self->mDir.x = self->mDir.x + nx;
            self->mDir.y = self->mDir.y + ny;
            self->mDir.z = self->mDir.z + nz;
        }
        break;
    }
    case 3: {
        float t = dist + radius + fExtra;
        Vec3* n = normalized_safe(&dir, &self->mPos);
        self->mPos.x = n->x * t;
        self->mPos.y = n->y * t;
        self->mPos.z = n->z * t;
        break;
    }
    case 4: {
        Vec3 v;
        v.x = in->mPos.x - pos.x;
        v.y = in->mPos.y - pos.y;
        v.z = in->mPos.z - pos.z;
        float dot = v.x * dir.x + v.y * dir.y + v.z * dir.z;
        dir.x = v.x - dir.x * dot;
        dir.y = v.y - dir.y * dot;
        dir.z = v.z - dir.z * dot;

        Vec3 e8, e6;
        e8.x = pts[8].x - in->mPos.x;
        e8.y = pts[8].y - in->mPos.y;
        e8.z = pts[8].z - in->mPos.z;
        float d8 = sqrtf(e8.x * e8.x + (e8.y * e8.y + e8.z * e8.z));
        e6.x = pts[6].x - in->mPos.x;
        e6.y = pts[6].y - in->mPos.y;
        e6.z = pts[6].z - in->mPos.z;
        float d6 = sqrtf(e6.x * e6.x + (e6.y * e6.y + e6.z * e6.z));

        float md = d8 > d6 ? d8 : d6;
        if (md > 0.0f) {
            Vec3* n = normalized_safe(&v, &dir);
            self->mPos.x = pos.x - n->x * md;
            self->mPos.y = pos.y - n->y * md;
            self->mPos.z = pos.z - n->z * md;
        }
        break;
    }
    }
    vec->erase(vec->mpBegin, vec->mpEnd);
}
