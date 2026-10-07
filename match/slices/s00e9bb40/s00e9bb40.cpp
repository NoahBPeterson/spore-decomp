// Slice s00e9bb40: the single function in this slice is
//   0x00E9BB40  SP::cSPUFOGfx::CreateHitEffects   (2543 bytes, __thiscall, ret)
//
// Drains the UFO game data's queued collisions (intrusive list at +0x770). For each
// collision (position + type):
//   - "up" = the UFO's orientation applied to the constant axis at 0x15a8afc (0,1,0);
//   - picks a hit effect id from one of two 11-entry tables (by type), the second table
//     when the UFO's +0x714 field is non-zero (shielded);
//   - type 1 (ground hit): plays effect 0x3d6f334 at the collision point, oriented by the
//     planet surface normal there (OrthogonalVector when the hit position is ~perpendicular
//     to the normal);
//   - when the selected id is non-zero: creates it, stores its offset in UFO-local space,
//     orients it facing from the UFO toward the hit, starts it and appends it
//     ({offset, effect}) to the view's hit-effect vector at +0xc0.
// Build flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the original has no EH frame).
#include "types.h"

#pragma warning(disable: 4100)

inline void* operator new(unsigned int, void* p) throw() { return p; }
inline void operator delete(void*, void*) throw() {}

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    static const Vector3 ZERO;     // 0x016c6934
};
struct Quaternion { float x, y, z, w; };
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& o)
    {
        m[0] = o.m[0]; m[1] = o.m[1]; m[2] = o.m[2];
        m[3] = o.m[3]; m[4] = o.m[4]; m[5] = o.m[5];
        m[6] = o.m[6]; m[7] = o.m[7]; m[8] = o.m[8];
    }
    static const Matrix3 IDENTITY; // 0x016c6910
};

extern const Vector3 kUFOUpAxis;   // 0x015a8afc  (0, 1, 0)

// q applied to v (quaternion -> rotation matrix, times v), inlined in the original.
inline Vector3 RotateByQuaternion(const Quaternion& q, const Vector3& v)
{
    float xx = q.x * q.x;
    float yy = q.y * q.y;
    float xy = q.y * q.x;
    float yz = q.z * q.y;
    float yw = q.y * q.w;
    float zz = q.z * q.z;
    float zw = q.z * q.w;
    float zx = q.z * q.x;
    float xw = q.x * q.w;
    return Vector3(
        ((xy - zw) * v.y + (yw + zx) * v.z) * 2.0f + (1.0f - (zz + yy) * 2.0f) * v.x,
        ((yz - xw) * v.z + (zw + xy) * v.x) * 2.0f + (1.0f - (zz + xx) * 2.0f) * v.y,
        ((xw + yz) * v.y + (zx - yw) * v.x) * 2.0f + (1.0f - (yy + xx) * 2.0f) * v.z);
}

// rot * v, summed z-first as in the original.
inline Vector3 MulMatrix(const Matrix3& r, const Vector3& v)
{
    return Vector3(r.m[2] * v.z + r.m[1] * v.y + r.m[0] * v.x,
                   r.m[5] * v.z + r.m[4] * v.y + r.m[3] * v.x,
                   r.m[8] * v.z + r.m[7] * v.y + r.m[6] * v.x);
}

const Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quaternion* q);                    // 0x0059c190
const Matrix3* Matrix3FromFacingAndUp(Matrix3* out, const Vector3* facing, const Vector3* up); // 0x0069b440
const Quaternion* QuaternionFromFacingAndUp(Quaternion* out, const Vector3* facing, const Vector3* up); // 0x0069b600
Vector3 OrthogonalVector(const Vector3& v);                                                  // 0x006985b0

struct Transform {
    int16_t mnFlags;
    int16_t mnTransformCount;
    Vector3 mOffset;
    float mfScale;
    Matrix3 mRotation;
    __forceinline Transform() : mnFlags(0), mnTransformCount(0), mOffset(Vector3::ZERO), mfScale(1.0f)
    {
        mRotation = Matrix3(Matrix3::IDENTITY);
    }
    Transform& SetOffset(const Vector3& v) { mOffset = v; mnFlags |= 4; mnTransformCount++; return *this; }
    Transform& SetRotation(const Matrix3& r) { mRotation = r; mnFlags |= 2; mnTransformCount++; return *this; }
};

struct IVisualEffect {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual void Start(int hardStart) = 0;
    virtual int Stop(int hardStop) = 0;
    virtual int IsRunning() = 0;
    virtual void SetRigidTransform(const Transform& t) = 0;
    virtual void SetSourceTransform(const Transform& t) = 0;
};

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    T** AsPPTypeParam()
    {
        if (mpObject) {
            T* const p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};

struct IEffectsManager {
    virtual bool Initialize() = 0;
    virtual bool Dispose() = 0;
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual void SetResources(void*) = 0;
    virtual void* Resources() = 0;
    virtual void SetRenderer(void*) = 0;
    virtual void* Renderer() = 0;
    virtual void SetDecalManager(void*, int) = 0;
    virtual void* DecalManager(int) = 0;
    virtual bool HasVisualEffect(uint32_t instanceID, uint32_t groupID) const = 0;
    virtual bool CreateVisualEffect(uint32_t instanceID, uint32_t groupID, IVisualEffect** dst) = 0;
};
namespace SP { IEffectsManager* EffectsManager(); }   // 0x0067ddd0

struct cPlanetModel {
    Vector3 GetSurfaceNormal(const Vector3& pos);       // 0x00b7e3b0 (sret, ret 8)
};
namespace SP { cPlanetModel* PlanetModel(); }         // 0x00b3d350

using namespace SP;

// The locomotive/spatial interface embedded at +0x34 of the UFO game data.
struct cLocomotiveIface {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3* GetPosition();           // +0x2c
    virtual const Quaternion* GetOrientation();     // +0x30
};

namespace SP {

struct cSPGameDataUFO {
    char pad00[0x34];
    cLocomotiveIface mLoco;                             // +0x34
    char pad38[0x714 - 0x38];
    int mbShielded;                                     // +0x714
    bool HasCollisions();                               // 0x00c38260 (list at +0x770 not empty)
    int GetNextCollision(Vector3* pos);                 // 0x00c3c4d0
};

struct cGameObject {
    // vtable slot 0xb8: Cast(id)
    virtual void* v00(); virtual void* v01(); virtual void* v02(); virtual void* v03();
    virtual void* v04(); virtual void* v05(); virtual void* v06(); virtual void* v07();
    virtual void* v08(); virtual void* v09(); virtual void* v10(); virtual void* v11();
    virtual void* v12(); virtual void* v13(); virtual void* v14(); virtual void* v15();
    virtual void* v16(); virtual void* v17(); virtual void* v18(); virtual void* v19();
    virtual void* v20(); virtual void* v21(); virtual void* v22(); virtual void* v23();
    virtual void* v24(); virtual void* v25(); virtual void* v26(); virtual void* v27();
    virtual void* v28(); virtual void* v29(); virtual void* v30(); virtual void* v31();
    virtual void* v32(); virtual void* v33(); virtual void* v34(); virtual void* v35();
    virtual void* v36(); virtual void* v37(); virtual void* v38(); virtual void* v39();
    virtual void* v40(); virtual void* v41(); virtual void* v42(); virtual void* v43();
    virtual void* v44(); virtual void* v45();
    virtual void* Cast(uint32_t typeID);                // +0xb8
};

struct HitEffect {
    Vector3 mOffset;
    AutoRefCount<IVisualEffect> mpEffect;
};

struct HitEffectVector {
    HitEffect* mpBegin;
    HitEffect* mpEnd;
    HitEffect* mpCapacity;
    void DoInsertValue(HitEffect* pos, const HitEffect& value);   // 0x00e9b030
    void push_back(const HitEffect& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) HitEffect(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

struct EffectID { uint32_t instanceID; uint32_t groupID; };

class cSPUFOGfx {
public:
    void CreateHitEffects();
    char pad00[0xc];
    cGameObject* mpObject;                              // +0x0c
    char pad10[0xc0 - 0x10];
    HitEffectVector mHitEffects;                        // +0xc0
};

void cSPUFOGfx::CreateHitEffects()
{
    cGameObject* object = mpObject;
    cSPGameDataUFO* ufo = object ? (cSPGameDataUFO*)object->Cast(0xb033b403) : 0;
    while (ufo->HasCollisions()) {
        Vector3 hitPos;
        int type = ufo->GetNextCollision(&hitPos);
        Vector3 up = RotateByQuaternion(*ufo->mLoco.GetOrientation(), kUFOUpAxis);

        EffectID hullEffects[11] = {
            { 0, 0 }, { 0x3d6f33c, 0 }, { 0x5131c8c, 0 }, { 0x5131c8f, 0 },
            { 0x5131c93, 0 }, { 0x5131c94, 0 }, { 0x5131c96, 0 }, { 0x5131c98, 0 },
            { 0x5131c9a, 0 }, { 0x5131c9c, 0 }, { 0x5131c9d, 0 },
        };
        EffectID shieldEffects[11] = {
            { 0, 0 }, { 0x693320c, 0 }, { 0x693320d, 0 }, { 0x693320e, 0 },
            { 0x693320f, 0 }, { 0x6933210, 0 }, { 0x6933211, 0 }, { 0x6933212, 0 },
            { 0x6933213, 0 }, { 0x6933214, 0 }, { 0x6933215, 0 },
        };
        EffectID id;
        if (ufo->mbShielded == 0)
            id = hullEffects[type];
        else
            id = shieldEffects[type];

        if (type == 1) {
            Vector3 normal = PlanetModel()->GetSurfaceNormal(hitPos);
            AutoRefCount<IVisualEffect> effect;
            if (EffectsManager()->CreateVisualEffect(0x3d6f334, 0, effect.AsPPTypeParam())) {
                Vector3 facingUp = hitPos;
                if ((float)fabs(hitPos.x * normal.x + normal.z * hitPos.z + normal.y * hitPos.y) < 1.5258789e-05f)
                    facingUp = OrthogonalVector(normal);
                Transform t;
                t.SetOffset(hitPos);
                Matrix3 rot;
                t.SetRotation(*Matrix3FromFacingAndUp(&rot, &normal, &facingUp));
                effect->SetSourceTransform(t);
                effect->Start(0);
            }
        }

        if (id.instanceID != 0 || id.groupID != 0) {
            HitEffect hit;
            if (EffectsManager()->CreateVisualEffect(id.instanceID, id.groupID, hit.mpEffect.AsPPTypeParam())) {
                const Vector3& pos = *ufo->mLoco.GetPosition();
                Matrix3 tmp;
                Matrix3 orient;
                orient = *Matrix3FromQuaternion(&tmp, ufo->mLoco.GetOrientation());
                hit.mOffset = MulMatrix(orient, hitPos - pos);
                Transform t;
                t.SetOffset(pos);
                Vector3 facing = hitPos - pos;
                Quaternion q;
                QuaternionFromFacingAndUp(&q, &facing, &up);
                t.SetRotation(*Matrix3FromQuaternion(&tmp, &q));
                hit.mpEffect->SetSourceTransform(t);
                hit.mpEffect->Start(0);
                mHitEffects.push_back(hit);
            }
        }
    }
}

} // namespace SP
