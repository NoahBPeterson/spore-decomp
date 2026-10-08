// Slice s00e9b2b0: SP::cSPUFOGfx::UpdateHitEffects (0x00e9b2b0), fastcall(this).
// Walks mRunningCollisionEffects (16-byte entries: offset in UFO space + AutoRefCount<cIVisualEffect>),
// erases entries whose effect has stopped, and for the rest places the effect at
// ufoPos + rotate(ufoOrientation, offset) facing away from the UFO centre, via SetSourceTransform.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

#pragma warning(disable: 4100)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};
struct Quaternion { float x, y, z, w; };
struct Matrix3 {
    Vector3 row[3];
    Matrix3() {}
};

extern const Vector3 kZeroVec;                  // 0x016c6934
extern const Matrix3 kIdentityMat;              // 0x016c6910
extern const Vector3 kUpAxis;                   // 0x015a8afc

const Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quaternion* q);                          // 0x0059c190 (cdecl)
Quaternion* QuaternionFromFacingAndUp(Quaternion* out, const Vector3* facing, const Vector3* up); // 0x0069b600 (cdecl)

struct Transform {
    int16_t mnFlags;
    int16_t mnTransformCount;
    Vector3 mOffset;
    float mfScale;
    Matrix3 mRotation;
    __forceinline Transform() : mnFlags(0), mnTransformCount(0), mOffset(kZeroVec), mfScale(1.0f)
    {
        Vector3 a(kIdentityMat.row[0]);
        mRotation.row[0] = a;
        Vector3 b(kIdentityMat.row[1]);
        mRotation.row[1] = b;
        Vector3 c(kIdentityMat.row[2]);
        mRotation.row[2] = c;
    }
    Transform& SetOffset(const Vector3& v) { mOffset = v; mnFlags |= 4; mnTransformCount++; return *this; }
    Transform& SetRotation(const Matrix3& r) { mRotation = r; mnFlags |= 2; mnTransformCount++; return *this; }
};

struct cIVisualEffect {
    virtual int AddRef();
    virtual int Release();
    virtual void Start(int hardStart);
    virtual int Stop(int hardStop);
    virtual bool IsRunning();                   // +0x10
    virtual void SetRigidTransform(const Transform& t);
    virtual void SetSourceTransform(const Transform& t);   // +0x18
};

struct UFOCollisionEffectInfo {
    Vector3 mOffset;                            // +0x00, offset from the UFO centre
    cIVisualEffect* mpEffect;                   // +0x0c
    ~UFOCollisionEffectInfo() { cIVisualEffect* p = mpEffect; if (p) p->Release(); }
};
// eastl::copy_impl<0, random_access_iterator_tag>::do_copy<Info*, Info*>(first, last, dest), 0x00e99140
UFOCollisionEffectInfo* DoCopy(UFOCollisionEffectInfo* first, UFOCollisionEffectInfo* last, UFOCollisionEffectInfo* dest);

struct cLocomotiveIface {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual const Vector3* GetPosition();       // +0x2c
    virtual const Quaternion* GetOrientation(); // +0x30
};

struct cSPGameDataUFO {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual int GetEmpireID();                  // +0x4c
    uint32_t pad04[(0x34 - 4) / 4];
    cLocomotiveIface mLoco;                     // +0x34
};

struct cSpatialObject {
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
    virtual void v2c(); virtual void v2d();
    virtual void* Cast(uint32_t typeID);        // +0xb8
};

// Rotate v by unit quaternion q (expanded rotation-matrix form used by the original).
__forceinline Vector3 Rotate(const Quaternion* q, const Vector3& v)
{
    float x = q->x, y = q->y, z = q->z, w = q->w;
    Vector3 r;
    r.x = ((w * y + z * x) * v.z + (y * x - w * z) * v.y) * 2.0f + (1.0f - (z * z + y * y) * 2.0f) * v.x;
    r.y = ((w * z + y * x) * v.x + (z * y - w * x) * v.z) * 2.0f + (1.0f - (z * z + x * x) * 2.0f) * v.y;
    r.z = ((z * x - w * y) * v.x + (w * x + z * y) * v.y) * 2.0f + (1.0f - (y * y + x * x) * 2.0f) * v.z;
    return r;
}

class cSPUFOGfx {
public:
    uint32_t pad00[3];
    cSpatialObject* mpObject;                   // +0x0c
    uint32_t pad10[(0xc0 - 0x10) / 4];
    UFOCollisionEffectInfo* mpEffectsBegin;     // +0xc0
    UFOCollisionEffectInfo* mpEffectsEnd;       // +0xc4

    void erase(UFOCollisionEffectInfo* position)
    {
        if (position + 1 < mpEffectsEnd)
            DoCopy(position + 1, mpEffectsEnd, position);
        --mpEffectsEnd;
        mpEffectsEnd->~UFOCollisionEffectInfo();
    }
    unsigned size() const { return (unsigned)(mpEffectsEnd - mpEffectsBegin); }
    void UpdateHitEffects();                    // 0x00e9b2b0
};

// @ 0x00e9b2b0
void cSPUFOGfx::UpdateHitEffects()
{
    cSPGameDataUFO* ufo = mpObject ? (cSPGameDataUFO*)mpObject->Cast(0xb033b403) : 0;

    unsigned i = 0;
    while (i < size()) {
        if (!mpEffectsBegin[i].mpEffect->IsRunning()) {
            erase(mpEffectsBegin + i);
        } else {
            Transform t;
            cLocomotiveIface* loco = &ufo->mLoco;
            const Vector3* ufoPos = loco->GetPosition();
            const Quaternion* q = loco->GetOrientation();

            Vector3 rotated = Rotate(q, mpEffectsBegin[i].mOffset);
            Vector3 pos(ufoPos->x + rotated.x, ufoPos->y + rotated.y, ufoPos->z + rotated.z);
            t.SetOffset(pos);

            Vector3 up = Rotate(q, kUpAxis);
            Vector3 facing(pos.x - ufoPos->x, pos.y - ufoPos->y, pos.z - ufoPos->z);
            Quaternion orient;
            QuaternionFromFacingAndUp(&orient, &facing, &up);
            Matrix3 mat;
            t.SetRotation(*Matrix3FromQuaternion(&mat, &orient));

            mpEffectsBegin[i].mpEffect->SetSourceTransform(t);
            ++i;
        }
    }
}
