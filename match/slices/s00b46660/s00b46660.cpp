// Per-frame integration of a surface-bound mover (planet surface movement), mode 0 = free, mode 1 = on surface.
#include <math.h>
#include "types.h"

struct Vec3f { float x, y, z; };
struct Vec4f { float x, y, z, w; };

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern Vec3f g_ZeroVec;                 // 0x0167eb8c

class cPlanetModel {
public:
    float GetWaterHeight();                                      // 0x00b7e390
    float GetScale();                                            // 0x00b7e490
    Vec3f* ProjectToTangent(Vec3f* out, Vec3f* pos);             // 0x00b7e3b0 (ret 8)
    Vec3f* DirectionToSurfacePosition(Vec3f* out, Vec3f* dir);   // 0x00b815a0 (ret 8)
    Vec4f* OrientationAt(Vec4f* out, Vec3f* pos, Vec3f* up);     // 0x00b7f1f0 (ret 0xc)
    float GetRadiusAt(Vec3f* pos);                               // 0x00b7ef70 (ret 4)
};

// Target object at this+0x40; vtable slots as used here.
class cMoverTarget {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual Vec3f* GetPosition();                 // +0x2c
    virtual Vec3f* GetUp();                       // +0x30
    virtual void v0d();
    virtual void SetPosition(Vec3f* p);           // +0x38
    virtual void SetOrientation(Vec4f* q);        // +0x3c
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
    virtual void v30(); virtual void v31();
    virtual float GetRotateFactor();              // +0xc8
    void SetVelocityDir(Vec3f* v);                // 0x00c41d60 (ret 4)
    void SetAngularDir(Vec3f* v);                 // 0x00c41d90 (ret 4)
    char pad[0x48];
    uint32_t flags;                               // +0x50
};

cPlanetModel* PlanetModel();                      // 0x00b3d350
Vec3f* Normalize(Vec3f* out, Vec3f* in);          // 0x00436ce0 (cdecl)
float Dot3(Vec3f* v);                             // 0x004885d0 (v . v)
float VectorLength(Vec3f* v);                     // 0x0040ae50
Vec4f* QuatDelta(Vec4f* out, Vec4f* w, Vec4f* q); // 0x007dcb00 (cdecl)
Vec4f* QuatNormalize(Vec4f* out, Vec4f* q);       // 0x00799320 (cdecl)
void ApplyPlanetCorrection(Vec3f* pos, cMoverTarget* obj);   // 0x00b444c0 (cdecl)

class cSurfaceMover {
public:
    virtual void vfn0();
    float GetSpeed();                             // 0x00b3dcd0
    void GetOrientation(Vec4f* out);              // 0x00b3f300 (ret 4)
    void Update(float dt);                        // 0x00b46660

    int mode;                                     // +4
    char pad0[0x14];
    Vec3f vel;                                    // +0x1c
    Vec3f angVel;                                 // +0x28
    char onSurface;                               // +0x34
    char flag35;                                  // +0x35
    char active;                                  // +0x36
    char pad3;
    char pad4[8];
    cMoverTarget* obj;                            // +0x40
};

// @ 0x00b46660
void cSurfaceMover::Update(float dt)
{
    if (!(1.5258789e-05f < GetSpeed()))
        return;
    if (!active)
        return;
    switch (mode) {
    case 0:
        if (vel.x != g_ZeroVec.x || vel.y != g_ZeroVec.y || vel.z != g_ZeroVec.z) {
            Vec3f* pv = &vel;
            obj->SetVelocityDir(pv);
            obj->SetAngularDir(&angVel);
            Vec4f q;
            GetOrientation(&q);
            Vec4f w = { angVel.x, angVel.y, angVel.z, 0.0f };
            Vec4f tmp;
            Vec4f* d = QuatDelta(&tmp, &w, &q);
            q.x = (d->x * 0.5f) * dt + q.x;
            q.y = q.y + (d->y * 0.5f) * dt;
            q.z = q.z + (d->z * 0.5f) * dt;
            q.w = q.w + (d->w * 0.5f) * dt;
            Vec4f tmp2;
            Vec4f* n = QuatNormalize(&tmp2, &q);
            q.x = n->x; q.y = n->y; q.z = n->z; q.w = n->w;
            if (obj->GetRotateFactor() == 0.0f)
                obj->SetOrientation(&q);
            Vec3f* p = obj->GetPosition();
            Vec3f tgt;
            tgt.x = pv->x * dt + p->x;
            tgt.y = pv->y * dt + p->y;
            tgt.z = pv->z * dt + p->z;
            ApplyPlanetCorrection(&tgt, obj);
        }
        break;
    case 1: {
        Vec3f* pv = &vel;
        if (pv->x != g_ZeroVec.x || pv->y != g_ZeroVec.y || pv->z != g_ZeroVec.z) {
            cPlanetModel* planet = PlanetModel();
            float scale = planet->GetScale();
            if (onSurface) {
                Vec3f t1, n1, t2;
                planet->ProjectToTangent(&t1, obj->GetPosition());
                Normalize(&n1, &t1);
                Vec3f* p = Normalize(&t2, obj->GetPosition());
                float px = p->x * scale, py = p->y * scale, pz = p->z * scale;
                float step = ((-n1.z * pz + -n1.y * py) + -n1.x * px) * dt;
                float step2 = step * step;
                if (Dot3(pv) < step2) {
                    pv->x = g_ZeroVec.x;
                    vel.y = g_ZeroVec.y;
                    vel.z = g_ZeroVec.z;
                    angVel.x = g_ZeroVec.x;
                    angVel.y = g_ZeroVec.y;
                    angVel.z = g_ZeroVec.z;
                    active = 0;
                } else {
                    Vec3f t3;
                    Vec3f* nv = Normalize(&t3, pv);
                    float nx = -nv->x, ny = -nv->y, nz = -nv->z;
                    pv->x = pv->x + nx * step;
                    vel.y = ny * step + vel.y;
                    vel.z = nz * step + vel.z;
                }
            } else {
                float len = VectorLength(obj->GetPosition());
                if (len > 1.5258789e-05f) {
                    Vec3f* p = obj->GetPosition();
                    float inv = 1.0f / len;
                    pv->x = ((inv * p->x) * scale) * dt + pv->x;
                    vel.y = ((p->y * inv) * scale) * dt + vel.y;
                    vel.z = ((p->z * inv) * scale) * dt + vel.z;
                } else {
                    onSurface = 1;
                }
            }
            Vec4f q;
            GetOrientation(&q);
            Vec4f w = { angVel.x, angVel.y, angVel.z, 0.0f };
            Vec4f tmp;
            Vec4f* d = QuatDelta(&tmp, &w, &q);
            q.x = (d->x * 0.5f) * dt + q.x;
            q.y = q.y + (d->y * 0.5f) * dt;
            q.z = q.z + (d->z * 0.5f) * dt;
            q.w = q.w + (d->w * 0.5f) * dt;
            Vec4f tmp2;
            Vec4f* n = QuatNormalize(&tmp2, &q);
            q.x = n->x; q.y = n->y; q.z = n->z; q.w = n->w;
            obj->SetOrientation(&q);
            Vec3f* p = obj->GetPosition();
            Vec3f tgt;
            tgt.x = pv->x * dt + p->x;
            tgt.y = vel.y * dt + p->y;
            tgt.z = vel.z * dt + p->z;
            Vec3f surf;
            obj->SetPosition(planet->DirectionToSurfacePosition(&surf, &tgt));
            cMoverTarget* o = obj;
            Vec4f ori;
            o->SetOrientation(planet->OrientationAt(&ori, o->GetPosition(), o->GetUp()));
            obj->flags &= 0xfffffffe;
            if (!onSurface) {
                Vec3f* pos = obj->GetPosition();
                float wh = planet->GetWaterHeight();
                float rad = planet->GetRadiusAt(pos);
                float* m = &wh;
                if (!(wh > rad)) m = &rad;
                onSurface = (float)fabs(*m - VectorLength(pos)) < 1.5258789e-05f;
            }
        }
        break;
    }
    }
}

// ============================================================================
// Per-frame mover driver and the small surface-mover helpers.
// ============================================================================

// Registry object the mover iterator lives on (global pointer at 0x0167eb70).
struct cMoverIterator {
    int   GetPriority();          // 0x00e31100 UTCWin::IWinProc::GetPriority
    void* Next(int* pKey);        // 0x00b72230
};

struct cMoverRegistry {
    char           mPad00[0x3c];
    cMoverIterator mIter;         // +0x3c
};

extern cMoverRegistry* g_pMoverRegistry;   // 0x0167eb70

// The two target flags tested by the driver (+0x70 / +0x75 of the target object).
struct cMoverTargetFlags {
    char mPad00[0x70];
    unsigned char mFlag70;        // +0x70
    char mPad71[0x75 - 0x71];
    unsigned char mFlag75;        // +0x75
};

// ----------------------------------------------------------------------------
// @ 0x00b46d10
// Walk every mover of the registry and update the active ones.
void Fn_00b46d10(float dt)
{
    int key = g_pMoverRegistry->mIter.GetPriority();
    cMoverIterator* pIter = &g_pMoverRegistry->mIter;
    void* pNext = pIter->Next(&key);
    while (pNext != 0) {
        cSurfaceMover* pMover = (cSurfaceMover*)pNext;
        bool bUpdate = false;
        int nType = pMover->mode;
        switch (nType) {
        case 0: {
            cMoverTargetFlags* pFlags = (cMoverTargetFlags*)pMover->obj;
            if (pFlags->mFlag75 != 0 &&
                (pFlags->mFlag70 != 0 || pMover->flag35 != 0))
                bUpdate = true;
            break;
        }
        case 1: {
            cMoverTargetFlags* pFlags = (cMoverTargetFlags*)pMover->obj;
            if (pFlags->mFlag75 != 0 &&
                (pFlags->mFlag70 != 0 || pMover->flag35 != 0))
                bUpdate = true;
            break;
        }
        case 2:
            bUpdate = true;
            break;
        }
        if (bUpdate)
            pMover->Update(dt);
        pIter = &g_pMoverRegistry->mIter;
        pNext = pIter->Next(&key);
    }
}

// ----------------------------------------------------------------------------
// Curve point stored at +0x14 of cCurve.
struct cCurvePoint {
    char mData[0x3c];
    void CopyFrom(cCurvePoint* pOther);   // 0x00ac1ff0
};

struct cCurve {
    void AssignFrom(cCurve* pOther);      // 0x00b45c10
    char  mPad00[0x14];
    cCurvePoint mPoint;                   // +0x14
    float mF50;                           // +0x50
    float mF54;                           // +0x54
    float mF58;                           // +0x58
    unsigned int mF5c;                    // +0x5c
    float mF60;                           // +0x60
    float mF64;                           // +0x64
    float mF68;                           // +0x68
    float mF6c;                           // +0x6c
    unsigned int mF70;                    // +0x70
    cCurve* Assign(cCurve* pOther);       // 0x00b46d90
};

// ----------------------------------------------------------------------------
// @ 0x00b46d90
// Copy-assign a curve: shared base, the curve point, then the tail fields.
cCurve* cCurve::Assign(cCurve* pOther)
{
    AssignFrom(pOther);
    mPoint.CopyFrom(&pOther->mPoint);
    mF50 = pOther->mF50;
    mF54 = pOther->mF54;
    mF58 = pOther->mF58;
    mF5c = pOther->mF5c;
    mF60 = pOther->mF60;
    mF64 = pOther->mF64;
    mF68 = pOther->mF68;
    mF6c = pOther->mF6c;
    mF70 = pOther->mF70;
    return this;
}

// ----------------------------------------------------------------------------
// A 3-float vector with the model-world clear helper.
struct cVecHolder {
    float x, y, z;
    void Clear();                 // 0x00743b50 cModelWorld::VecClear
};

extern char gF5cObject[];         // 0x0154df28

struct cHolder {
    char        mPad00[0x08];
    cVecHolder  mVec1;            // +0x08
    char        mPad14[0x24 - 0x14];
    unsigned int mF24;            // +0x24
    unsigned int mF28;            // +0x28
    unsigned int mF2c;            // +0x2c
    char        mPad30[0x3c - 0x30];
    cVecHolder  mVec2;            // +0x3c
    char        mPad48[0x5c - 0x48];
    void*       mpF5c;            // +0x5c
    unsigned int mF60;            // +0x60
    unsigned int mF64;            // +0x64
    float       mF68;             // +0x68
    float       mF6c;             // +0x6c
    unsigned int mF70;            // +0x70
    char        mPad74[0x78 - 0x74];
    unsigned int mF78;            // +0x78
    unsigned int mF7c;            // +0x7c
    unsigned int mF80;            // +0x80
    char        mPad84[0x90 - 0x84];
    unsigned int mF90;            // +0x90
    unsigned int mF94;            // +0x94
    unsigned int mF98;            // +0x98
    cHolder* Init();              // 0x00b46ff0
};

// ----------------------------------------------------------------------------
// @ 0x00b46ff0
// Reset the holder's vectors and tail fields.
cHolder* cHolder::Init()
{
    mVec1.Clear();
    mF24 = 0;
    mF28 = 0;
    mF2c = 0;
    mVec2.Clear();
    mF68 = 1.0f;
    _ReadWriteBarrier();
    mF6c = 2.0f;
    _ReadWriteBarrier();
    mF64 = 0;
    mF70 = 0;
    mF60 = 1;
    mpF5c = (void*)&gF5cObject;
    _ReadWriteBarrier();
    mF78 = 0;
    mF7c = 0;
    mF80 = 0;
    mF90 = 0;
    mF94 = 0;
    mF98 = 0;
    return this;
}

void Fn_00b452b0();               // 0x00b452b0

struct cSwitchHolder {
    char         mPad00[0x3c];
    int          mState;          // +0x3c
    void Cleanup();               // 0x00b47060
};

// ----------------------------------------------------------------------------
// @ 0x00b47060
// Flush the current states that need it, then mark the holder idle.
void cSwitchHolder::Cleanup()
{
    if (mState == -1)
        return;
    switch (mState) {
    case 0x1654c00:
    case 0x1654c01:
    case 0x1654c02:
    case 0x1654c04:
    case 0x1654c05:
    case 0x1654c10:
        Fn_00b452b0();
        break;
    }
    mState = -1;
}

extern "C" int* Fn_00b41ea0(int* pBegin, int* pEnd, int* pValue, unsigned char flag); // 0x00b41ea0

struct cRange {
    int* mpBegin;                 // +0x00
    int* mpEnd;                   // +0x04
    char mPad08[0x14 - 0x08];
    unsigned char mF14;           // +0x14
    int* Find(int* pValue);       // 0x00b47570
};

// ----------------------------------------------------------------------------
// @ 0x00b47570
// Bounded search; returns the found slot or the end pointer.
int* cRange::Find(int* pValue)
{
    int* pEnd = mpEnd;
    int* p = Fn_00b41ea0(mpBegin, pEnd, pValue, mF14);
    if (p == pEnd || *pValue < *p)
        return pEnd;
    if (p == p + 2)               // redundant sentinel guard present in the original
        return pEnd;
    return p;
}

class cRandomLCG {
public:
    unsigned RandomUint32Uniform(unsigned n);   // 0x00a68fb0
};

void Fn_010216a0(int* pA, int* pB);   // 0x010216a0

// ----------------------------------------------------------------------------
// @ 0x00b475b0
// In-place random shuffle of a pointer array [pBegin, pEnd).
void Fn_00b475b0(int* pBegin, int* pEnd, cRandomLCG* pRandom)
{
    for (int* p = pBegin + 1; p < pEnd; ++p) {
        unsigned n = (unsigned)(p - pBegin) + 1;
        unsigned idx = pRandom->RandomUint32Uniform(n);
        int* pOther = pBegin + idx;
        Fn_010216a0(p, pOther);
    }
}

// ============================================================================
// Aim-slope update (00b46df0) and the collision registrar / slab test.
// ============================================================================

extern char gAimConst;                 // 0x0167ec2c
extern int  g_nAimFlag;                // 0x0167ecd0

// Object carrying the orientation slots used by the aim-slope update.
class cAimObject {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual Vec4f* GetOrientation();              // +0x30
    virtual void v0d(); virtual void v0e();
    virtual void SetOrientation(Vec4f* pQ);       // +0x3c
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16();
    virtual void GetTargetOrientation(Vec4f* pOut); // +0x5c
};

extern "C" void  __stdcall Fn_00d58510(Vec3f* pOut, cAimObject* pObj, float fValue); // 0x00d58510
extern "C" Vec3f* __cdecl  Fn_0059aed0(Vec3f* pOut, const void* pConst, const Vec3f* pIn); // 0x0059aed0
extern "C" Vec4f* __stdcall Slerp(Vec4f* pOut, const Vec4f* pA, const Vec4f* pB, float t); // 0x005b2500
extern "C" bool  __cdecl  Fn_00b3d550(Vec4f* pQuat);  // 0x00b3d550

// ----------------------------------------------------------------------------
// @ 0x00b46df0
// Slerp the object's orientation toward its aim target by the requested amount.
float __stdcall Fn_00b46df0(cAimObject* pObj, float fA2, float fA3, float fA4, float fA5)
{
    Vec3f vIn;
    Vec3f vRef;
    Vec4f qTarget;
    Vec4f qNew;

    Fn_00d58510(&vIn, pObj, fA2);
    pObj->GetTargetOrientation(&qTarget);
    Fn_0059aed0(&vRef, &gAimConst, &vIn);

    float fDot = qTarget.x * vRef.x + qTarget.y * vRef.y + qTarget.z * vRef.z;
    float fCos = fDot;
    if (fCos > 1.0f) fCos = 1.0f;
    if (fCos < 0.0f) fCos = 0.0f;

    float fProd = fCos * fA4;
    float fAngle = (float)acos(fCos);

    // Bail out on a non-finite angle.
    union { float f; unsigned int u; } bits;
    bits.f = fAngle;
    if ((bits.u & 0x7fffffffu) != 0) {
        unsigned int e = (bits.u + 0xff800000u) & 0x7f800000u;
        if (e >= 0x7f000000u)
            return fProd;
    }

    float t;
    if (fAngle > 0.0f) {
        float fT = (fA3 * fA5) / fAngle;
        t = (fT > 1.0f) ? 1.0f : fT;
    } else {
        t = 1.0f;
    }

    Vec4f* pCur = pObj->GetOrientation();
    Slerp(&qNew, pCur, &qTarget, t);
    if (Fn_00b3d550(&qNew))
        pObj->SetOrientation(&qNew);

    return fProd;
}

// ----------------------------------------------------------------------------
// Objects and containers used by the registrar (00b470b0).
class cStoredObject {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d(); virtual void AddRef();   // +0xbc
    virtual void Release();                                          // +0xc0
};

class cRegistrarObject {
public:
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual void* GetByTag(unsigned int nTag);    // +0x0c
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual unsigned int GetId();                 // +0x20
};

struct cRecordList {
    void Append(void** ppRecord);                 // 0x00b45ab0
};

struct cMoverOwner {
    char          mPad00[0x60];
    cStoredObject** mpBegin;                      // +0x60
    cStoredObject** mpEnd;                        // +0x64
    char          mPad68[0x47c - 0x68];
    cRecordList   mRecordList;                    // +0x47c
    void Register(cRegistrarObject* pObj);        // 0x00b470b0
};

extern "C" void __cdecl Fn_00b43710(void* pObj);              // 0x00b43710
extern "C" void __cdecl Fn_00b530e0(void* pObj, void* pRec);  // 0x00b530e0

// ----------------------------------------------------------------------------
// @ 0x00b470b0
// Register or unregister the object in the owner's object list.
void cMoverOwner::Register(cRegistrarObject* pObj)
{
    if (pObj->GetId() == 0x3ed8573u) {
        Fn_00b43710((pObj->GetId() == 0x3ed8573u) ? (void*)pObj : 0);
        return;
    }

    cStoredObject* pStored = (cStoredObject*)pObj->GetByTag(0x1186577u);
    if (pStored)
        pStored->AddRef();
    void* pRec = pObj->GetByTag(0x116dd1bu);

    if (pStored) {
        if (pRec == 0) {
            mRecordList.Append((void**)&pStored);
        } else {
            int nCount = (int)(mpEnd - mpBegin);
            for (int i = 0; i < nCount; ++i) {
                if (mpBegin[i] == (cStoredObject*)pRec) {
                    cStoredObject* pLast = mpBegin[nCount - 1];
                    cStoredObject* pFound = mpBegin[i];
                    if (pLast != pFound) {
                        if (pLast)
                            pLast->AddRef();
                        mpBegin[i] = pLast;
                        if (pFound)
                            pFound->Release();
                    }
                    --mpEnd;
                    cStoredObject* pRemoved = *mpEnd;
                    if (pRemoved)
                        pRemoved->Release();
                    break;
                }
            }
        }

        Fn_00b43710(pStored);
        if (g_nAimFlag)
            Fn_00b530e0(pStored, pRec);
        pStored->Release();
    }
}

// ----------------------------------------------------------------------------
// Slab helpers for the collision test (00b47200).
struct cSlabBox {
    void Compute(float* pDir, float* pLo, float* pHi);   // 0x00b425b0
};

struct cSlabTester {
    char mFlag;                                   // +0x00
    bool Clip(void* pBoxA, void* pBoxB, float* pNormal, float* pV,
              float fDistance, float* pBest, unsigned char* pMask,
              float* pMin, float* pMax, float* pNegDir, float* pPosDir);
};

// ----------------------------------------------------------------------------
// @ 0x00b47200
// Intersect the moving slab against the two helper boxes and update the bounds.
bool cSlabTester::Clip(void* pBoxA, void* pBoxB, float* pNormal, float* pV,
                       float fDistance, float* pBest, unsigned char* pMask,
                       float* pMin, float* pMax, float* pNegDir, float* pPosDir)
{
    float fLo1, fHi1;
    float fLo2, fHi2;
    ((cSlabBox*)pBoxA)->Compute(pV, &fHi1, &fLo1);
    ((cSlabBox*)pBoxB)->Compute(pV, &fHi2, &fLo2);

    float tNear = (fHi2 - fLo2) - fLo1 - fHi1;
    float tFar = (fHi2 + fLo2) + fLo1 - fHi1;
    bool bHit = (tNear > 0.0f) || (tFar > 0.0f);

    if (mFlag != 0 && ((*pMask = *pMask & (bHit ? 1 : 0)), *pMask != 0)) {
        float fScale = (fabsf(tNear) < fabsf(tFar)) ? tNear : tFar;
        fScale = -(fScale / fDistance);
        float vx = pV[0] * fScale;
        float vy = pV[1] * fScale;
        float vz = pV[2] * fScale;
        if (vx * vx + vy * vy + vz * vz <
            pBest[0] * pBest[0] + pBest[1] * pBest[1] + pBest[2] * pBest[2]) {
            pBest[0] = vx;
            pBest[1] = vy;
            pBest[2] = vz;
        }
    }

    float fDot = pNormal[0] * pV[0] + pNormal[1] * pV[1] + pNormal[2] * pV[2];
    if (fabsf(fDot) < 1.5258789e-05f)
        return bHit;

    float fSign = -1.0f;
    float fInv = 1.0f / fDot;
    float fA = -(fInv * tNear);
    float fB = -(fInv * tFar);
    float fMin = fA;
    float fMax = fB;
    if (fB < fA) {
        fSign = 1.0f;
        fMin = fB;
        fMax = fA;
    }

    float fCurMax = *pMax;
    if (fCurMax != 1e20f && fMin > fCurMax)
        return false;
    if (*pMin != -1e20f && *pMin > fMax)
        return false;

    if (fMax < fCurMax || fCurMax == 1e20f) {
        *pMax = fMax;
        float vx = pV[0] * fSign;
        float vy = pV[1] * fSign;
        float vz = pV[2] * fSign;
        pPosDir[0] = vx;
        pPosDir[1] = vy;
        pPosDir[2] = vz;
    }
    if (*pMin < fMin || *pMin == -1e20f) {
        *pMin = fMin;
        fSign = -fSign;
        float vx = pV[0] * fSign;
        float vy = pV[1] * fSign;
        float vz = pV[2] * fSign;
        pNegDir[0] = vx;
        pNegDir[1] = vy;
        pNegDir[2] = vz;
    }
    return true;
}
