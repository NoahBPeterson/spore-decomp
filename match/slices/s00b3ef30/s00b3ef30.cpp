// slice s00b3ef30 -- SP::cSpatialProxy transform / integration helpers.
//
// Retail build: VS2008 era (cl 15).  The group is a state machine over a
// "proxy" object: *(this+4) selects how the transform is derived (0/1 -> ask
// the wrapped cSpatialObject through its vtable, 2 -> synthesise from the
// wrapped object's local matrix, anything else -> a fixed default).  The
// bounding-box getters end with the same (v-c)*scale+c shrink toward the box
// centre, so that tail is factored into ScaleBox().
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast

#include "types.h"

// ---------------------------------------------------------------------------
// small math types
// ---------------------------------------------------------------------------
struct Vector3 { float x, y, z; };

struct Quaternion { float x, y, z, w; };

struct Matrix33
{
    float m[9];
    void Assign(const Matrix33& src);       // 0x0041cb40
    void FromMatrix(const void* src);       // 0x0040ce80
};

struct cSPBoundingBox
{
    Vector3 mMin;                           // +0x00
    Vector3 mMax;                           // +0x0c
    void Extend(const Vector3* v);          // 0x0041bd50
    void Transform(const void* m);          // 0x00409dd0
};

// The out-parameter of GetTransform()/the transform handed to the bounding-box
// Transform(): flags/modcount word, local position, scale, rotation.
struct cSPTransform
{
    uint16_t mFlags;                        // +0x00
    uint16_t mModCount;                     // +0x02
    Vector3  mPos;                          // +0x04
    float    mScale;                        // +0x10
    Matrix33 mRot;                          // +0x14
    cSPTransform() {}                       // default ctor
    cSPTransform(const cSPTransform& src);  // 0x0040ce80 (out of line)
};

struct cSPTransformOps
{
    cSPTransformOps* Assign(const void* p); // 0x00537dc0
};

// The wrapped spatial object (*(this+0x40)); only the non-virtual entry points
// we call are modelled here.
struct cSpatialObject
{
    cSPTransform* FUN_00b73e70();           // 0x00b73e70
    void  LocalToWorldTransform(cSPTransform* out);  // 0x00c897e0
};

struct cSpatialProxy;

struct cSpatialDB
{
    cSpatialProxy* Find(int id);            // 0x00b721d0
};

struct cSpatialProxy
{
    Quaternion* GetQuaternion(Quaternion* out);          // 0x00b3f300
    Matrix33*   GetMatrix(Matrix33* out);                // 0x00b3f3a0
    void        GetBoundingBox(cSPBoundingBox* out);     // 0x00b3f420
    void        GetTransform(cSPTransform* out);         // 0x00b3f6c0
    cSPBoundingBox* GetScaledBoundingBox(cSPBoundingBox* out); // 0x00b3f730
    void        Integrate();                             // 0x00b3f940
    void        IntegrateCollide(float* p2, float* p3);  // 0x00b3faa0
    int         FUN_00b3ef30(void* obj, int count, void* vec, int idx,
                             void* b, int* outCount);    // 0x00b3ef30
    char        FUN_00b3eb90(void* buf, int idx, void* b, int* outCount,
                             float* v, float f);         // 0x00b3eb90
    float       TimeScale();                             // 0x00b3dcd0
    void        GetPosition(float* out);                 // 0x00b3d9c0
    bool        IsValid();                               // 0x00b3d5f0
};

// ---------------------------------------------------------------------------
// external callees / data
// ---------------------------------------------------------------------------
Matrix33&   Matrix3FromQuaternion(Matrix33& out, const Quaternion& q);        // 0x0059c190
Quaternion& QuaternionFromMatrix33(Quaternion& out, const Matrix33& m, float w); // 0x00472b80
void        FUN_00b3d8d0(float* out, void* a, void* b, float x, float y, float z);
bool        FUN_0059ab70(float* v);
void        eastl_vector_insert(void* vec, void* pos, int size);              // 0x011e0744

extern void*    DAT_0167eb70;
extern float    DAT_015696d8;
extern float    DAT_015696dc;
extern float    DAT_015696e0;
extern float    DAT_015696e4;
extern uint8_t  DAT_0167ec08;
extern float    DAT_0167ec2c;
extern float    DAT_0167ec30;
extern float    DAT_0167ec34;
extern float    DAT_0167ec38;
extern float    DAT_0167ec3c;
extern float    DAT_0167ec40;
extern float    DAT_0167ec44;
extern float    DAT_0167ec48;
extern float    DAT_0167ec4c;
extern float    DAT_0167eb8c;
extern float    DAT_0167eb90;
extern float    DAT_0167eb94;
extern float    DAT_01461150;   // FLT_MAX
extern float    DAT_01461154;   // 1.5258789e-05f
extern float    DAT_013f51ac;   // -FLT_MAX
extern float    DAT_01485720;   // 1.0f
extern float    DAT_01471064;   // 0.5f
extern float    DAT_013eb8b0;   // sign mask

// ---------------------------------------------------------------------------
// shared bounding-box shrink tail (inlined into both getters)
// ---------------------------------------------------------------------------
static void ScaleBox(cSPBoundingBox* out, float s)
{
    float cx = (out->mMin.x + out->mMax.x) * 0.5f;
    float cy = (out->mMin.y + out->mMax.y) * 0.5f;
    float cz = (out->mMin.z + out->mMax.z) * 0.5f;
    out->mMin.x = (out->mMin.x - cx) * s + cx;
    out->mMin.y = (out->mMin.y - cy) * s + cy;
    out->mMin.z = (out->mMin.z - cz) * s + cz;
    out->mMax.x = (out->mMax.x - cx) * s + cx;
    out->mMax.y = (out->mMax.y - cy) * s + cy;
    out->mMax.z = (out->mMax.z - cz) * s + cz;
}

// ---------------------------------------------------------------------------
// 0x00b3ef30
// ---------------------------------------------------------------------------
// @ 0x00b3ef30
int cSpatialProxy::FUN_00b3ef30(void* obj, int count, void* vec, int idx,
                                void* b, int* outCount)
{
    *outCount = 0;
    if (count < 3)
        return 0;

    float l1a0, l19c, l198;
    FUN_00b3d8d0(&l1a0, obj, (char*)obj + 0xc,
                 *(float*)((char*)obj + 0x18),
                 *(float*)((char*)obj + 0x1c),
                 *(float*)((char*)obj + 0x20));

    char buf[384];
    eastl_vector_insert(buf, vec, idx * 0xc);

    int i = 0;
    if (count > 0)
    {
        int off = (count * 3 - 3) * 4;
        float* p = (float*)((char*)obj + 8);
        do
        {
            float f1 = *(float*)(off + 4 + (char*)obj);
            float f2 = *(float*)(off + 8 + (char*)obj);
            float f7 = p[-2] - *(float*)(off + (char*)obj);
            float f8 = p[0] - f2;
            float f9 = p[-1] - f1;
            float l18c = l198 * f9 - l19c * f8;
            float l188 = f8 * l1a0 - l198 * f7;
            float l184 = l19c * f7 - f9 * l1a0;
            char ok = FUN_00b3eb90(buf, idx, b, outCount, &l18c,
                                   (l188 * f1 + l18c * *(float*)(off + (char*)obj)) + l184 * f2);
            if (!ok)
                return 0;
            idx = *outCount;
            eastl_vector_insert(buf, b, idx * 0xc);
            off = (-8 - (int)obj) + (int)p;
            i++;
            p += 3;
        } while (i < count);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00b3f260 -- copy 0x3c-byte records into a caller buffer.
// ---------------------------------------------------------------------------
struct Elem3c
{
    float   f0, f1, f2, f3;                             // +0x00
    void*   p;                                          // +0x10
    float   f4, f5, f6, f7, f8, f9, f10, f11, f12;      // +0x14
    uint8_t b;                                          // +0x38
    uint8_t pad[3];
};

// @ 0x00b3f260
void FUN_00b3f260(Elem3c** out, Elem3c* first, Elem3c* last, Elem3c* dst)
{
    Elem3c* d = dst;
    *out = d;
    for (; first != last; ++first, ++d)
    {
        if (d != 0)
        {
            d->f0 = first->f0;
            d->f1 = first->f1;
            d->f2 = first->f2;
            d->f3 = first->f3;
            d->p = first->p;
            d->f4 = first->f4;
            d->f5 = first->f5;
            d->f6 = first->f6;
            d->f7 = first->f7;
            d->f8 = first->f8;
            d->f9 = first->f9;
            d->f10 = first->f10;
            d->f11 = first->f11;
            d->f12 = first->f12;
            d->b = first->b;
        }
    }
    *out = d;
}

// ---------------------------------------------------------------------------
// 0x00b3f300 -- GetQuaternion
// ---------------------------------------------------------------------------
// @ 0x00b3f300
Quaternion* cSpatialProxy::GetQuaternion(Quaternion* out)
{
    int state = *(int*)((char*)this + 4);
    Quaternion* q;
    switch (state)
    {
    case 0:
    {
        void* obj = *(void**)((char*)this + 0x40);
        q = (*(Quaternion* (__thiscall**)(void*))(*(char**)obj + 0x30))(obj);
        break;
    }
    case 1:
    {
        void* obj = *(void**)((char*)this + 0x40);
        q = (*(Quaternion* (__thiscall**)(void*))(*(char**)obj + 0x30))(obj);
        break;
    }
    case 2:
    {
        cSPTransform* m = ((cSpatialObject*)*(void**)((char*)this + 0x40))->FUN_00b73e70();
        Quaternion local;
        q = &QuaternionFromMatrix33(local, m->mRot, 0.0f);
        break;
    }
    default:
        out->x = DAT_015696d8;
        out->y = DAT_015696dc;
        out->z = DAT_015696e0;
        out->w = DAT_015696e4;
        return out;
    }
    out->x = q->x;
    out->y = q->y;
    out->z = q->z;
    out->w = q->w;
    return out;
}

// ---------------------------------------------------------------------------
// 0x00b3f3a0 -- GetMatrix
// ---------------------------------------------------------------------------
// @ 0x00b3f3a0
Matrix33* cSpatialProxy::GetMatrix(Matrix33* out)
{
    int state = *(int*)((char*)this + 4);
    switch (state)
    {
    case 0:
    {
        void* obj = *(void**)((char*)this + 0x40);
        Quaternion* q = (*(Quaternion* (__thiscall**)(void*))(*(char**)obj + 0x30))(obj);
        Matrix3FromQuaternion(*out, *q);
        return out;
    }
    case 1:
    {
        void* obj = *(void**)((char*)this + 0x40);
        Quaternion* q = (*(Quaternion* (__thiscall**)(void*))(*(char**)obj + 0x30))(obj);
        Matrix3FromQuaternion(*out, *q);
        return out;
    }
    case 2:
    {
        cSPTransform* m = ((cSpatialObject*)*(void**)((char*)this + 0x40))->FUN_00b73e70();
        cSPTransform local(*m);
        out->Assign(local.mRot);
        return out;
    }
    default:
        out->Assign(*(Matrix33*)&DAT_0167ec08);
        return out;
    }
}

// ---------------------------------------------------------------------------
// 0x00b3f420 -- GetBoundingBox
// ---------------------------------------------------------------------------
// @ 0x00b3f420
void cSpatialProxy::GetBoundingBox(cSPBoundingBox* out)
{
    int state = *(int*)((char*)this + 4);
    if (state == 0 || state == 1)
    {
        void* obj = *(void**)((char*)this + 0x40);
        cSPBoundingBox* b = (*(cSPBoundingBox* (__thiscall**)(void*))(*(char**)obj + 0x68))(obj);
        out->mMax = b->mMax;
        out->mMin = b->mMin;
    }
    else if (state == 2)
    {
        void* obj = *(void**)((char*)this + 0x40);
        float v = *(float*)((char*)obj + 0x44);
        Vector3 a;
        a.x = v * DAT_0167ec2c;
        a.y = v * DAT_0167ec30;
        a.z = v * DAT_0167ec34;
        out->Extend(&a);
        a.x = -a.x; a.y = -a.y; a.z = -a.z;
        out->Extend(&a);

        float v2 = *(float*)((char*)obj + 0x44);
        Vector3 b;
        b.x = v2 * DAT_0167ec44;
        b.y = v2 * DAT_0167ec48;
        b.z = v2 * DAT_0167ec4c;
        out->Extend(&b);
        b.x = -b.x; b.y = -b.y; b.z = -b.z;
        out->Extend(&b);

        float v3 = *(float*)((char*)obj + 0x4c);
        Vector3 c;
        c.x = v3 * DAT_0167ec38;
        c.y = v3 * DAT_0167ec3c;
        c.z = v3 * DAT_0167ec40;
        out->Extend(&c);
    }
    ScaleBox(out, *(float*)((char*)this + 0x14));
}

// ---------------------------------------------------------------------------
// 0x00b3f6c0 -- GetTransform
// ---------------------------------------------------------------------------
// @ 0x00b3f6c0
void cSpatialProxy::GetTransform(cSPTransform* out)
{
    int state = *(int*)((char*)this + 4);
    switch (state)
    {
    case 0:
        ((cSpatialObject*)*(void**)((char*)this + 0x40))->LocalToWorldTransform(out);
        break;
    case 1:
        ((cSpatialObject*)*(void**)((char*)this + 0x40))->LocalToWorldTransform(out);
        break;
    case 2:
    {
        cSPTransform* r = ((cSpatialObject*)*(void**)((char*)this + 0x40))->FUN_00b73e70();
        ((cSPTransformOps*)out)->Assign(r);
        uint8_t* p = (uint8_t*)((char*)*(void**)((char*)this + 0x40) + 0x34);
        if (*p & 4)
        {
            ++out->mModCount;
            out->mScale = 1.0f;
        }
        break;
    }
    }
}

// ---------------------------------------------------------------------------
// 0x00b3f730 -- GetScaledBoundingBox
// ---------------------------------------------------------------------------
// @ 0x00b3f730
cSPBoundingBox* cSpatialProxy::GetScaledBoundingBox(cSPBoundingBox* out)
{
    out->mMin.x = DAT_01461150;
    out->mMin.y = DAT_01461150;
    out->mMin.z = DAT_01461150;
    out->mMax.x = DAT_013f51ac;
    out->mMax.y = DAT_013f51ac;
    out->mMax.z = DAT_013f51ac;

    int state = *(int*)((char*)this + 4);
    if (state == 0 || state == 1)
    {
        void* obj = *(void**)((char*)this + 0x40);
        cSPBoundingBox* b = (*(cSPBoundingBox* (__thiscall**)(void*))(*(char**)obj + 0x6c))(obj);
        out->mMax = b->mMax;
        out->mMin = b->mMin;
    }
    else if (state == 2)
    {
        GetBoundingBox(out);
        cSPTransform local;
        local.mFlags = 0;
        local.mModCount = 0;
        local.mPos.x = DAT_0167eb8c;
        local.mPos.y = DAT_0167eb90;
        local.mPos.z = DAT_0167eb94;
        local.mScale = DAT_01485720;
        local.mRot.Assign(*(Matrix33*)&DAT_0167ec08);
        GetTransform(&local);
        out->Transform(&local);
        return out;
    }
    ScaleBox(out, *(float*)((char*)this + 0x14));
    return out;
}

// ---------------------------------------------------------------------------
// 0x00b3f940 -- Integrate
// ---------------------------------------------------------------------------
// @ 0x00b3f940
void cSpatialProxy::Integrate()
{
    float v = TimeScale();
    if (v > 0.0f)
    {
        float vx = *(float*)((char*)this + 0x44) * v;
        float vy = *(float*)((char*)this + 0x48) * v;
        float vz = *(float*)((char*)this + 0x4c) * v;
        *(float*)((char*)this + 0x1c) = *(float*)((char*)this + 0x1c) + vx;
        *(float*)((char*)this + 0x20) = *(float*)((char*)this + 0x20) + vy;
        *(float*)((char*)this + 0x24) = *(float*)((char*)this + 0x24) + vz;

        float px = *(float*)((char*)this + 0x50);
        float py = *(float*)((char*)this + 0x54);
        float pz = *(float*)((char*)this + 0x58);

        *(float*)((char*)this + 0x2c) =
            ((*(float*)((char*)this + 0xa8) * px + *(float*)((char*)this + 0xb4) * py) +
             *(float*)((char*)this + 0xc0) * pz) + *(float*)((char*)this + 0x2c);
        *(float*)((char*)this + 0x30) =
            ((*(float*)((char*)this + 0xac) * px + *(float*)((char*)this + 0xb8) * py) +
             *(float*)((char*)this + 0xc4) * pz) + *(float*)((char*)this + 0x30);
        *(float*)((char*)this + 0x28) =
            *(float*)((char*)this + 0x28) +
            ((*(float*)((char*)this + 0xb0) * py + *(float*)((char*)this + 0xbc) * pz) +
             *(float*)((char*)this + 0xa4) * px);

        *(Vector3*)((char*)this + 0x44) = *(Vector3*)&DAT_0167eb8c;
        *(Vector3*)((char*)this + 0x50) = *(Vector3*)&DAT_0167eb8c;
    }
}

// ---------------------------------------------------------------------------
// 0x00b3faa0 -- IntegrateCollide
// ---------------------------------------------------------------------------
// @ 0x00b3faa0
void cSpatialProxy::IntegrateCollide(float* p2, float* p3)
{
    float v = TimeScale();
    if (v > DAT_01461154 && *(uint32_t*)((char*)this + 4) <= 1)
    {
        float f5 = p3[0];
        float f1 = p3[2];
        *(float*)((char*)this + 0x20) = *(float*)((char*)this + 0x20) + p3[1] * v;
        *(float*)((char*)this + 0x1c) = *(float*)((char*)this + 0x1c) + f5 * v;
        *(float*)((char*)this + 0x24) = *(float*)((char*)this + 0x24) + f1 * v;

        float lc, l8, l4;
        GetPosition(&lc);

        float dy = p2[1] - l8;
        float dx = p2[0] - lc;
        float dz = p2[2] - l4;
        lc = p3[2] * dy - p3[1] * dz;
        l8 = p3[0] * dz - p3[2] * dx;
        l4 = p3[1] * dx - p3[0] * dy;

        if (FUN_0059ab70(&lc))
        {
            *(float*)((char*)this + 0x28) =
                ((*(float*)((char*)this + 0xbc) * l4 + *(float*)((char*)this + 0xb0) * l8) +
                 *(float*)((char*)this + 0xa4) * lc) + *(float*)((char*)this + 0x28);
            *(float*)((char*)this + 0x2c) =
                *(float*)((char*)this + 0x2c) +
                ((*(float*)((char*)this + 0xc0) * l4 + *(float*)((char*)this + 0xb4) * l8) +
                 *(float*)((char*)this + 0xa8) * lc);
            *(float*)((char*)this + 0x30) =
                *(float*)((char*)this + 0x30) +
                ((*(float*)((char*)this + 0xc4) * l4 + *(float*)((char*)this + 0xb8) * l8) +
                 *(float*)((char*)this + 0xac) * lc);
        }
        *(uint8_t*)((char*)this + 0x36) = 1;
    }
}

// ---------------------------------------------------------------------------
// 0x00b3fc80 -- pair collision check
// ---------------------------------------------------------------------------
// @ 0x00b3fc80
int FUN_00b3fc80(void* self)
{
    cSpatialDB* db = (cSpatialDB*)((char*)DAT_0167eb70 + 0x3c);
    cSpatialProxy* a = db->Find(*(int*)((char*)self + 4));
    cSpatialProxy* b = db->Find(*(int*)((char*)self + 8));
    if (a == 0 || b == 0)
        return 0;

    int state = *(int*)((char*)a + 4);
    if (state == 0 || state == 1)
    {
        if (*(uint8_t*)(*(int*)((char*)a + 0x40) + 0x75) == 0)
            return 0;
        if (*(uint8_t*)(*(int*)((char*)a + 0x40) + 0x70) == 0 &&
            *(uint8_t*)((char*)a + 0x35) == 0)
            return 0;
    }
    else if (state != 2)
    {
        return 0;
    }

    if (!b->IsValid())
        return 0;

    float s = *(float*)((char*)DAT_0167eb70 + 0xb0) - DAT_01485720;
    float old = *(float*)((char*)self + 0x28);
    float t1 = (*(float*)((char*)b + 0x24) - *(float*)((char*)a + 0x24)) * s;
    float t2 = (*(float*)((char*)b + 0x20) - *(float*)((char*)a + 0x20)) * s;
    float t3 = (*(float*)((char*)b + 0x1c) - *(float*)((char*)a + 0x1c)) * s;
    float m = ((((*(float*)((char*)self + 0x20) * t1 +
                  *(float*)((char*)self + 0x1c) * t2) +
                 *(float*)((char*)self + 0x18) * t3) +
                *(float*)((char*)self + 0x34)) * *(float*)((char*)self + 0x30)) + old;
    if (m < 0.0f)
        m = 0.0f;
    *(float*)((char*)self + 0x28) = m;

    float d = m - old;
    Vector3 n;
    n.x = *(float*)((char*)self + 0x18) * d;
    n.y = *(float*)((char*)self + 0x1c) * d;
    n.z = *(float*)((char*)self + 0x20) * d;
    if (0.0f <= ((*(float*)((char*)self + 0x20) * n.z +
                  *(float*)((char*)self + 0x1c) * n.y) +
                 n.x * *(float*)((char*)self + 0x18)))
    {
        Vector3 neg;
        neg.x = -n.x;
        neg.y = -n.y;
        neg.z = -n.z;
        a->IntegrateCollide((float*)((char*)self + 0xc), (float*)&neg);
        b->IntegrateCollide((float*)((char*)self + 0xc), (float*)&n);
    }
    return 1;
}
