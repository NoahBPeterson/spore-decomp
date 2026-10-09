// Slice s00c88e30 -- SP::cSpatialObject methods (retail layout).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(const cSPVector3& o) { x = o.x; y = o.y; z = o.z; }
    cSPVector3& operator=(const cSPVector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Quat { float x, y, z, w; };
struct BBox { Vec3 mn; Vec3 mx; };
struct Matrix3 { float m[9]; };
struct Transform {
    uint16_t flags;
    uint16_t version;
    Vec3     pos;
    float    scale;
    Matrix3  rot;
};

// Runtime-initialised globals (addresses kept for equivalence mapping).
extern Vec3    g_vec1695248;   // 0x01695248
extern Quat    g_quat157a1c8;  // 0x0157a1c8
extern cSPVector3 g_vec1695294;   // 0x01695294
extern cSPVector3 g_vec16952a0;   // 0x016952a0
extern Matrix3 g_mat16952ac;   // 0x016952ac
extern void*   g_vtable1473758[]; // 0x01473758
extern uint32_t g_init1695310; // 0x01695310
extern Vec3    g_vec1695304;   // 0x01695304

// cdecl free helpers (call targets are relocation-masked).
void*         FUN_0059aed0(void* out, void* key, void* owner);  // 0x0059aed0
unsigned char FUN_0059ab70(void* v);                            // 0x0059ab70
void*         FUN_00b3d3c0(void);                               // 0x00b3d3c0
struct Mgr { void Fn(void* p); };                               // 0x00b76ef0 (thiscall ret 4)
void          Matrix3FromQuaternion(Matrix3* m, Quat* q);       // 0x0059c190
void          FUN_007c4180(Vec3* out, Vec3* in);                // 0x007c4180
void          Matrix3_Assign(Matrix3* m, Matrix3* src);         // 0x0041cb40
void          BoundingBox_TransformBy(BBox* b, Matrix3* m);     // 0x00409dd0
float*        GetPropertyAsFloat(void* prop);                   // 0x0041ea70
void          SPUIHelpers_GetMainWindowArea(float* out);        // 0x00805ea0
struct AutoRef { void Assign(int a); };                         // 0x00478db0 (thiscall ret 4)
void*         App();                                            // 0x0067dd10
float*        cViewer_GetCameraLocationInfo(void* viewer, Vec3* out, int a, int b, int c); // 0x007c3d30

struct IUnk {
    virtual void AddRef();
    virtual void Release();
};

struct cSO;

#define VT(slot) (*(void***)this)[(slot) / 4]

// cSpatialObject (retail layout, size ~0xcc).
struct cSO {
    void**   vt;            // +0x00
    Vec3     mPosition;     // +0x04
    Quat     mOrientation;  // +0x10
    BBox     mLocalExtents; // +0x20
    BBox     mWorldExtents; // +0x38
    uint32_t mFlags;        // +0x50
    uint32_t m54;           // +0x54
    uint32_t m58;           // +0x58
    float    m5c;           // +0x5c
    float    m60;           // +0x60
    float    f64;           // +0x64
    float    f68;           // +0x68
    uint8_t  b6c, b6d, b6e, b6f, b70, b71, b72, b73, b74, b75, b76, b77, b78;
    uint8_t  pad79[3];      // +0x79
    float    f7c;           // +0x7c
    float    f80;           // +0x80
    float    f84;           // +0x84
    float    f88;           // +0x88
    float    f8c;           // +0x8c
    uint32_t m90, m94, m98; // +0x90
    void*    mp9c;          // +0x9c  (mpModel)
    void*    mpA0;          // +0xa0  (mpModelWorld)
    uint8_t  bA4, bA5, bA6, bA7;
    uint32_t mA8, mAC, mB0;
    float    fB4;
    uint32_t mB8, mBC;
    void*    mpC0;          // +0xc0
    void*    mpC4;          // +0xc4
    uint32_t mC8;           // +0xc8

    bool funcE30();
    void func78h(cSPVector3* out);
    void GetCommunityName(cSPVector3* out);
    void SetLocalExtents(float* e, float scale);
    bool func9C();
    void func93F0(float* a, float* b);
    cSO();
    void LocalToWorldTransform(Transform* out);
    void SetModel(int a1, void* b);
    void funcA4h();
    bool func7Ch(int a2, int a3, char a4, float* out);
};

// @ 0x00c88e30
bool cSO::funcE30()
{
    void* viewer = (void*)((void*(__thiscall*)(void*))VT(0x58))(App());
    Vec3 camLoc;
    cViewer_GetCameraLocationInfo(viewer, &camLoc, 0, 0, 0);
    Vec3* pos = (Vec3*)((void*(__thiscall*)(cSO*))VT(0x2c))(this);
    float px = pos->x;
    float py = pos->y;
    float pz = pos->z;
    if ((g_init1695310 & 1) == 0) {
        g_init1695310 |= 1;
        g_vec1695304 = g_vec1695248;
    }
    float fVar5 = sqrtf(px * px + (py * py + pz * pz)) - 10.0f;
    float fVar6 = sqrtf(camLoc.x * camLoc.x + (camLoc.z * camLoc.z + camLoc.y * camLoc.y)) - 10.0f;
    if (fVar5 < fVar6)
        fVar6 = fVar5;
    float dz = pz - camLoc.z;
    float dy = py - camLoc.y;
    float c2z = camLoc.z - g_vec1695304.z;
    float c2y = camLoc.y - g_vec1695304.y;
    float dx = px - camLoc.x;
    float c2x = camLoc.x - g_vec1695304.x;
    float dp = (dx * c2x + dz * c2z) + dy * c2y;
    float dd = (dz * dz + dy * dy) + dx * dx;
    float disc = dp * dp - (((c2x * c2x + c2z * c2z) + c2y * c2y) - fVar6 * fVar6) * dd;
    if (disc >= 0.0f) {
        float root = sqrtf(disc);
        if (root - dp >= 0.0f && -dp - root <= dd)
            return true;
    }
    return false;
}

// @ 0x00c89020
void cSO::func78h(cSPVector3* out)
{
    void* owner = (void*)((void*(__thiscall*)(cSO*))VT(0x30))(this);
    cSPVector3 v;
    cSPVector3* r = (cSPVector3*)FUN_0059aed0(&v, (void*)0x01695294, owner);
    cSPVector3 tmp = *r;
    if (FUN_0059ab70(&tmp))
        *out = tmp;
    else
        *out = g_vec1695294;
}

// @ 0x00c890c0
void cSO::GetCommunityName(cSPVector3* out)
{
    void* owner = (void*)((void*(__thiscall*)(cSO*))VT(0x30))(this);
    cSPVector3 v;
    cSPVector3* r = (cSPVector3*)FUN_0059aed0(&v, (void*)0x016952a0, owner);
    cSPVector3 tmp = *r;
    if (FUN_0059ab70(&tmp))
        *out = tmp;
    else
        *out = g_vec16952a0;
}

// @ 0x00c89160
void cSO::SetLocalExtents(float* e, float scale)
{
    mLocalExtents.mx.x = e[3];
    mLocalExtents.mx.y = e[4];
    mLocalExtents.mx.z = e[5];
    mLocalExtents.mn.x = e[0];
    mLocalExtents.mn.y = e[1];
    mLocalExtents.mn.z = e[2];
    mWorldExtents.mx.x = e[3];
    mWorldExtents.mx.y = e[4];
    mWorldExtents.mx.z = e[5];
    mWorldExtents.mn.x = e[0];
    mWorldExtents.mn.y = e[1];
    mWorldExtents.mn.z = e[2];

    mWorldExtents.mn.x *= scale;
    mWorldExtents.mn.y *= scale;
    mWorldExtents.mn.z *= scale;
    mWorldExtents.mx.x *= scale;
    mWorldExtents.mx.y *= scale;
    mWorldExtents.mx.z *= scale;
    f64 = scale;
    f7c = scale;

    float cz = (mWorldExtents.mx.z + mWorldExtents.mn.z) * 0.5f;
    float cx = (mWorldExtents.mx.x + mWorldExtents.mn.x) * 0.5f;
    float cy = (mWorldExtents.mx.y + mWorldExtents.mn.y) * 0.5f;
    float hz = mWorldExtents.mx.z - cz;
    float hx = mWorldExtents.mx.x - cx;
    float hy = mWorldExtents.mx.y - cy;
    float nhx = mWorldExtents.mn.x - cx;
    float nhy = mWorldExtents.mn.y - cy;
    float nhz = mWorldExtents.mn.z - cz;
    float lenA = sqrtf(hz * hz + hx * hx + hy * hy);
    float lenB = sqrtf(nhz * nhz + nhx * nhx + nhy * nhy);

    void* m = mp9c;
    if (m != 0 && mpA0 != 0) {
        float v = ((float(__thiscall*)(void*, void*))(*(void***)mpA0)[0x5c / 4])(mpA0, m);
        m5c = v * scale;
    } else if (mFlags & 0x40) {
        m5c = *(float*)((char*)m + 0x6c) * scale;
    } else {
        m5c = (lenA > lenB) ? lenA : lenB;
    }

    float lenC = sqrtf(hx * hx + hy * hy);
    float lenD = sqrtf(nhx * nhx + nhy * nhy);
    m60 = (lenC > lenD) ? lenC : lenD;

    if (m != 0) {
        void* p = *(void**)((char*)m + 0x90);
        if (p != 0) {
            void** vt = *(void***)p;
            void* prop = 0;
            char ok = ((char(__thiscall*)(void*, unsigned int, void**))(vt[0x24 / 4]))(p, 0x0579ef6c, &prop);
            if (ok && *(unsigned short*)((char*)prop + 0x12) == 0xd) {
                float* f = GetPropertyAsFloat(prop);
                m60 = *f;
            }
        }
    }
}

// @ 0x00c893b0
bool cSO::func9C()
{
    void* m = mp9c;
    if (m != 0) {
        unsigned int v = ((unsigned int*)m)[1];
        if (mFlags & 0x8000) {
            bool b14 = (v >> 14) & 1;
            bool b18 = (v >> 18) & 1;
            if (b14 && !b18)
                return true;
        } else {
            return (v >> 14) & 1;
        }
    }
    return false;
}

// @ 0x00c893f0
void cSO::func93F0(float* A, float* B)
{
    float dx = mLocalExtents.mx.x - mLocalExtents.mn.x;
    float dy = mLocalExtents.mx.y - mLocalExtents.mn.y;
    float dz = mLocalExtents.mx.z - mLocalExtents.mn.z;

    ((void(__thiscall*)(cSO*, float))VT(0x40))(this, 1.0f);

    float sLo = 1.0f;
    float sHi = 1.0f;
    if (dx > B[0]) { float t = B[0] / dx; if (t < sLo) sLo = t; }
    if (A[0] > dx) { float t = A[0] / dx; if (t > sHi) sHi = t; }
    if (dy > B[1]) { float t = B[1] / dy; if (t < sLo) sLo = t; }
    if (A[1] > dy) { float t = A[1] / dy; if (t > sHi) sHi = t; }
    if (dz > B[2]) { float t = B[2] / dz; if (t < sLo) sLo = t; }
    if (A[2] > dz) { float t = A[2] / dz; if (t > sHi) sHi = t; }

    if (sLo != 1.0f) {
        ((void(__thiscall*)(cSO*, float))VT(0x40))(this, sLo);
        return;
    }
    if (sHi != 1.0f) {
        for (int i = 0; i < 3; ++i) {
            float d[3]; d[0] = dx; d[1] = dy; d[2] = dz;
            if (d[i] * sHi > B[i]) {
                sHi = 1.0f;
                break;
            }
        }
        ((void(__thiscall*)(cSO*, float))VT(0x40))(this, sHi);
    }
}

// @ 0x00c89630
cSO::cSO()
{
    vt = g_vtable1473758;
    mPosition.x = g_vec1695248.x;
    mPosition.y = g_vec1695248.y;
    mPosition.z = g_vec1695248.z;
    mOrientation.x = g_quat157a1c8.x;
    mOrientation.y = g_quat157a1c8.y;
    mOrientation.z = g_quat157a1c8.z;
    mOrientation.w = g_quat157a1c8.w;
    mLocalExtents.mn.x = -0.5f;
    mLocalExtents.mn.y = -0.5f;
    mLocalExtents.mn.z = 0.0f;
    mLocalExtents.mx.x = 0.5f;
    mLocalExtents.mx.y = 0.5f;
    mLocalExtents.mx.z = 1.0f;
    mWorldExtents.mn.x = -0.5f;
    mWorldExtents.mn.y = -0.5f;
    mWorldExtents.mn.z = 0.0f;
    mWorldExtents.mx.x = 0.5f;
    mWorldExtents.mx.y = 0.5f;
    mWorldExtents.mx.z = 1.0f;
    mFlags = 0;
    m54 = 0;
    m58 = 0;
    m5c = 1.0f;
    m60 = 1.0f;
    f64 = 1.0f;
    f68 = 0.0f;
    b6c = 0; b6d = 0; b6e = 0;
    b6f = 1; b70 = 1; b71 = 1;
    b72 = 0; b73 = 0;
    b74 = 1; b75 = 1; b76 = 1; b77 = 1;
    b78 = 0;
    f7c = 1.0f;
    f80 = 12.0f;
    f84 = 5.0f;
    f88 = 0.0f;
    f8c = 1.0f;
    m90 = 0; m94 = 0; m98 = 0;
    mp9c = 0;
    mpA0 = 0;
    bA4 = 0; bA5 = 1; bA6 = 1; bA7 = 0;
    mA8 = 0;
    mAC = 0;
    mB0 = 1;
    fB4 = 0.0f;
    mB8 = 0;
    mA8 |= 2;
    mBC = 0;
    mpC0 = 0;
    mpC4 = 0;
    mC8 = 0;
}

// @ 0x00c897e0
void cSO::LocalToWorldTransform(Transform* out)
{
    out->rot = g_mat16952ac;
    out->scale = 1.0f;
    out->pos = g_vec1695248;
    out->flags = 0;
    out->version = 0;
    Vec3* pos = (Vec3*)((void*(__thiscall*)(cSO*))VT(0x2c))(this);
    out->pos = *pos;
    out->flags |= 4;
    out->version++;
    Quat* q = (Quat*)((void*(__thiscall*)(cSO*))VT(0x30))(this);
    Matrix3 m;
    Matrix3FromQuaternion(&m, q);
    out->flags |= 2;
    out->version++;
    out->rot = m;
}

// @ 0x00c89890
void cSO::SetModel(int a1, void* b)
{
    ((void(__thiscall*)(cSO*))VT(0xa4))(this);
    ((AutoRef*)&mp9c)->Assign(a1);
    void* old = mpA0;
    if (b != old) {
        if (b != 0)
            ((IUnk*)b)->AddRef();
        mpA0 = b;
        if (old != 0)
            ((IUnk*)old)->Release();
    }
}

// @ 0x00c898f0
void cSO::funcA4h()
{
    void* pMVar3 = mp9c;
    if (pMVar3 == 0)
        return;
    ((Mgr*)FUN_00b3d3c0())->Fn(pMVar3);
    pMVar3 = mp9c;
    {
        void* iface = *(void**)pMVar3;
        ((void(__thiscall*)(void*, void*, int))(*(void***)iface)[0x16c / 4])(iface, pMVar3, 0);
    }
    pMVar3 = mp9c;
    void* pOwner = *(void**)((char*)pMVar3 + 0x64);
    if (pOwner != 0) {
        *(void**)((char*)pMVar3 + 0x64) = 0;
        ((IUnk*)pOwner)->Release();
    }
    pMVar3 = mp9c;
    if (pMVar3 != 0) {
        mp9c = 0;
        int rc = *(int*)((char*)pMVar3 + 0x40);
        if (rc > 1) {
            *(int*)((char*)pMVar3 + 0x40) = rc - 1;
        } else {
            void* iface = *(void**)pMVar3;
            unsigned char b = (unsigned char)(((((unsigned int)*(int*)((char*)pMVar3 + 4)) >> 31) & 1) ? 1 : 0);
            ((void(__thiscall*)(void*, void*, unsigned int))(*(void***)iface)[0x170 / 4])(iface, pMVar3, b);
        }
    }
    if (mpA0 != 0) {
        void* p = mpA0;
        mpA0 = 0;
        ((IUnk*)p)->Release();
    }
    mFlags &= 0xffffff8f;
}

// @ 0x00c899a0
bool cSO::func7Ch(int a2, int a3, char a4, float* out)
{
    BBox box;
    box.mn.x = -0.5f;
    box.mn.y = -0.5f;
    box.mn.z = 0.0f;
    box.mx.x = 0.5f;
    box.mx.y = 0.5f;
    box.mx.z = 1.0f;

    bool computed;
    BBox* pB;
    if ((mFlags & 0x10) != 0 && (mFlags & 0x20) == 0) {
        computed = false;
        pB = &box;
    } else {
        computed = true;
        pB = (BBox*)((void*(__thiscall*)(cSO*))VT(0x68))(this);
    }
    float fStack_54 = pB->mx.z * 0.9f;
    Vec3* pos = (Vec3*)((void*(__thiscall*)(cSO*))VT(0x2c))(this);
    float fVar1 = pos->x, fVar2 = pos->y, fVar3 = pos->z;
    if (a4 == 0) {
        if (!computed) {
            BBox* p = (BBox*)((void*(__thiscall*)(cSO*, void*))VT(0x6c))(this, &box);
            box.mn.x = (p->mn.x + p->mx.x) * 0.5f;
            box.mn.y = (p->mx.y + p->mn.y) * 0.5f;
            box.mn.z = (p->mx.z + p->mn.z) * 0.5f;
        } else {
            Transform t;
            Matrix3_Assign(&t.rot, &g_mat16952ac);
            t.pos = g_vec1695248;
            t.flags = 0;
            t.version = 0;
            t.scale = 1.0f;
            LocalToWorldTransform(&t);
            BoundingBox_TransformBy(&box, &t.rot);
            box.mn.z = (box.mx.z + box.mn.z) * 0.5f;
            box.mn.x = (fStack_54 + box.mn.x) * 0.5f;
        }
    } else {
        float inv = 1.0f / sqrtf(fVar1 * fVar1 + (fVar2 * fVar2 + fVar3 * fVar3));
        box.mn.z = (fStack_54 * fVar3) * inv + fVar3;
        box.mn.x = (fVar2 * inv) * inv + fVar2;
        box.mn.y = (fVar3 * inv) * inv + fVar3;
    }
    void* viewer = (void*)((void*(__thiscall*)(void*))VT(0x58))(App());
    (void)viewer; (void)a2; (void)a3;
    Vec3 t2;
    FUN_007c4180(&t2, (Vec3*)&box.mn.x);
    (void)t2;
    (void)out;
    return false;
}
