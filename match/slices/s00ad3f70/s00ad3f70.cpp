// Slice s00ad3f70 -- SPAppStateManager.obj, the scripted editor-action family of s00ad33d0.
// FUN_00ad3f70 (cdecl): the per-frame update of the "add actor" action (action data type 0x055113D6).
//   arrive == false: only reports whether the actor's simulator entry is still disabled (or true
//                    when the action is flagged "don't wait").
//   arrive == true : computes the actor's position and facing from the action target, creates its
//                    simulator entry, records it in the vignette context (type 0x055116DA, created
//                    on first use) and, in the tribal stage, recruits tribe members (existing ones
//                    first, then newly created ones) until the entry's member count is reached.
// Class/member names are Claude-coined from usage.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (same module as s00ad33d0 / s00ad4b60).
#include "types.h"

// ---------------------------------------------------------------- RenderWare vector value type
namespace rw { namespace math { namespace fpu {
template <class T, int Aligned> class Vector3Template {
public:
    T x, y, z;
    Vector3Template() {}
    Vector3Template(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
    Vector3Template(const Vector3Template& v) : x(v.x), y(v.y), z(v.z) {}
};
} } }

struct cSPVector3 : public rw::math::fpu::Vector3Template<float, 0> {
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : rw::math::fpu::Vector3Template<float, 0>(ax, ay, az) {}
    cSPVector3(const cSPVector3& v) : rw::math::fpu::Vector3Template<float, 0>(v) {}
    cSPVector3(const rw::math::fpu::Vector3Template<float, 0>& v) : rw::math::fpu::Vector3Template<float, 0>(v) {}
    cSPVector3& operator=(const rw::math::fpu::Vector3Template<float, 0>& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

inline bool operator!=(const cSPVector3& a, const cSPVector3& b)
{
    return a.x != b.x || a.y != b.y || a.z != b.z;
}

struct cSPQuaternion {
    float x, y, z, w;
};

extern cSPVector3 kInvalidPosition;     // 0x0167A4BC
extern cSPVector3 g_167a53c;            // 0x0167A53C  the local axis the default facing is taken from
extern char g_145a6f4[];                // 0x0145A6F4  allocation tag of the vignette context

cSPVector3* normalized_safe(cSPVector3* out, const cSPVector3* v);                                  // 0x00449C20
rw::math::fpu::Vector3Template<float, 0> RotateVector(const cSPVector3* axis, const cSPQuaternion* q) // 0x0059AED0
{
    float qx = q->x, qy = q->y, qz = q->z, qw = q->w;
    float vx = axis->x, vy = axis->y, vz = axis->z;
    return rw::math::fpu::Vector3Template<float, 0>(
        ((qw * qy + qz * qx) * vz + (qy * qx - qw * qz) * vy) * 2.0f + (1.0f - (qz * qz + qy * qy) * 2.0f) * vx,
        ((qw * qz + qy * qx) * vx + (qz * qy - qw * qx) * vz) * 2.0f + (1.0f - (qz * qz + qx * qx) * 2.0f) * vy,
        ((qz * qx - qw * qy) * vx + (qw * qx + qz * qy) * vy) * 2.0f + (1.0f - (qy * qy + qx * qx) * 2.0f) * vz);
}

void* EAAllocate(unsigned int size, const char* tag, int a, int b, int c, int d);                   // 0x00F473A0
inline void* operator new(unsigned int, void* p) { return p; }

namespace SP {
enum eGameMode { kGameModeDummy };
eGameMode GetCurrentGameMode();                                                                      // 0x00B5B800
}

// ---------------------------------------------------------------- game objects
struct cSpatialObject;   // the object's spatial part (at +0xC0 of a creature)

struct cGameObject {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual unsigned int GetNounID();                                // +0x20
};

struct cTribe;
struct cCitizen : cGameObject {
    unsigned char pad_04[0x24 - 0x04];
    int mID;                                                         // +0x24
    unsigned char pad_28[0xC0 - 0x28];
    unsigned char mSpatial[0xB5E - 0xC0];                            // +0xC0 (cSpatialObject)
    bool mbBusy;                                                     // +0xB5E
    bool IsAvailable();                                              // 0x00C0B770
    cTribe* GetTribe();                                              // 0x00C22F50
    cSpatialObject* Spatial() { return (cSpatialObject*)mSpatial; }
};

struct cCitizenList {
    cCitizen** mpBegin;
    cCitizen** mpEnd;
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    cCitizen* operator[](unsigned int i) const { return mpBegin[i]; }
};

struct cTribe {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual cCitizenList* GetMembers();                              // +0x90
    cCitizen* CreateCitizen(int count);                              // 0x00C8E5A0
    void AddMember(cCitizen* citizen);                               // 0x00C96E80
};

// The object the action targets; the noun cast reaches its game data (type 0x017F243B).
struct cTargetObject {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4();
    virtual cGameObject* Cast(unsigned int typeID);                  // +0xB8
};

cGameObject* object_cast(cGameObject* p, unsigned int nounID);      // 0x00AC80D0

struct cActionTarget {
    unsigned char pad_00[0x2C];
    cTargetObject* mpObject;                                         // +0x2C
    cActionTarget();                                                 // 0x00AD7940
    explicit cActionTarget(cSpatialObject* object);                  // 0x00AD7A30
    ~cActionTarget();                                                // 0x00AD7AD0
    const cSPVector3* GetPosition();                                 // 0x00AD7B50
    const cSPQuaternion* GetOrientation();                           // 0x00AD7B70
    float GetScaleB();                                               // 0x00AD7B10
    float GetScaleA();                                               // 0x00AD7B30
};

struct cCinematicManager {
    unsigned char pad_00[0x148];
    unsigned int mContextKey;                                        // +0x148
    unsigned char pad_14c[0x1A8 - 0x14C];
    unsigned int mEntryFlag;                                         // +0x1A8
    bool LookupTarget(unsigned int id, cActionTarget* out);          // 0x00ADB2A0
    bool LookupObject(unsigned int id, struct cXformObject** out);   // 0x00ADB1B0
    void* FindContext(unsigned int type, unsigned int key);          // 0x00ADB250
    void AddContext(unsigned int type, void* context, unsigned int key);   // 0x00ADC890
    bool IsInScene(cSpatialObject* object);                          // 0x00ADB360
    void PostAction(int id, const cActionTarget& target, unsigned int key);  // 0x00AE09B0
    void PushAction(cCitizen* citizen, unsigned int key);            // 0x00AE0A80
};
cCinematicManager* CinematicManager();                               // 0x00B3D4D0

struct cIdMap {
    unsigned int& operator[](const unsigned int& key);              // 0x00AD3DA0
};

struct cVignetteData {
    unsigned char pad_00[0x10];
    cIdMap mActors;                                                  // +0x10
};

struct cVignetteContext {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual cVignetteData* Cast(unsigned int typeID);                // +0x0C
    unsigned char pad_04[0x30 - 0x04];
    cVignetteContext();                                              // 0x00AD3E00
};

struct cSimRegistry {
    int CreateEntry(int kind, int arg, const cSPVector3* pos, const cSPVector3* dir);   // 0x00BC64A0
    void SetFlag(int id, unsigned int flag);                         // 0x00BC3E20
    unsigned int GetMemberCount(int id);                             // 0x00BC3DB0
    bool AddMember(int id, cCitizen* citizen, int flag);             // 0x00BC4900
    unsigned char IsDisabled(int id);                                // 0x00BC3DF0
};
cSimRegistry* SimRegistry();                                         // 0x00B3D4E0

struct cTribeTools {
    void RegisterEntry(int id);                                      // 0x00AC86B0
};
cTribeTools* TribeTools();                                           // 0x00B3D480

struct cSceneManager {
    void Remove(cSpatialObject* object);                             // 0x00B45410
};
cSceneManager* SceneManager();                                       // 0x00B3D310

struct cPlanetModel {
    cSPQuaternion GetSurfaceOrientation(const cSPVector3& pos);     // 0x00B7F190
    cSPVector3 ClampToSurface(const cSPVector3& src);                // 0x00B81630
    cSPVector3 ProjectToSurface(const cSPVector3& src, int flag);    // 0x00B82B40
    bool FindGround(const cSPVector3* from, float radius, cSPVector3* out, float scale, bool flag, int arg);   // 0x00B88770
};
cPlanetModel* PlanetModel();                                         // 0x00B3D350

// ---------------------------------------------------------------- the position resolver (same module)
// ComputeTargetPosition (0x00AD2AE0) is defined in this module (reconstructed in slice s00ad2ae0, where
// it is matched). It is repeated here because the original caller below was compiled with its body in
// view: the compiler's callee summary then knows that `offset` is only read (handed on to the rotation
// below, whose body is in view as well), so the caller's offset vectors die after the two calls and
// share their stack slots with later temporaries, while `out` escapes.
struct cSPMatrix3 { float m[3][3]; };
struct cXformMsg {
    unsigned short a, b;
    cSPVector3 mPosition;                                            // +0x04
    float mScale;                                                    // +0x10
    cSPMatrix3 mMatrix;                                              // +0x14
    cXformMsg();                                                     // 0x00434040
};
struct cXformObject {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void GetTransform(cXformMsg* msg);                       // +0x20
};
struct cTransformable {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const cSPVector3* GetPosition();                         // +0x2C
    virtual const cSPQuaternion* GetOrientation();                   // +0x30
};
struct cTribeAux {
    unsigned char pad_00[0x34];
    cTransformable mTransform;                                       // +0x34
};
struct cTribeBase {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8();
    virtual cTribeAux* GetAux();                                     // +0xAC
};
struct cTribeWithTransform {
    unsigned char pad_00[0x120];
    cTransformable mTransform;                                       // +0x120
};
struct cCitizenOwner {
    cTribeBase* GetTribe();                                          // 0x00C22F50
};
struct cCitizenHome {
    cTribeWithTransform* GetTribe();                                 // 0x00C22F50
    cTribeWithTransform* GetCity();                                  // 0x00C23E40
};
struct cHerd {
    const cSPVector3* GetPosition();                                 // 0x00C6ACC0
};
struct cHerdMember {
    cHerd* GetHerd();                                                // 0x00C04590
};
cSPQuaternion QuaternionFromMatrix(const cSPMatrix3& m);            // 0x0046D660
cSPMatrix3* Matrix3FromFacingAndUp(cSPMatrix3* dst, const cSPVector3& facing, const cSPVector3& up);   // 0x0069B440

inline void ScaleBy(cSPVector3& v, float s)
{
    v.x = v.x * s;
    v.y = v.y * s;
    v.z = s * v.z;
}

cSPVector3* ComputeTargetPosition(cSPVector3& dst, cActionTarget& target, int mode, unsigned int id,
                                  int kind, const cSPVector3& offset)
{
    cSPVector3* out = &dst;
    cPlanetModel* planet = PlanetModel();
    out->x = kInvalidPosition.x;
    out->y = kInvalidPosition.y;
    out->z = kInvalidPosition.z;

    cGameObject* obj = target.mpObject ? target.mpObject->Cast(0x17f243b) : 0;
    if (!obj) {
        cActionTarget named;
        if (CinematicManager()->LookupTarget(id, &named))
            obj = named.mpObject ? named.mpObject->Cast(0x17f243b) : 0;
    }

    cSPVector3 v(offset);
    if (kind == 1)
        ScaleBy(v, target.GetScaleA());
    else if (kind == 2)
        ScaleBy(v, target.GetScaleB());

    switch (mode) {
    case 0:
        *out = offset;
        return out;
    case 1: {
        const cSPVector3* pos = target.GetPosition();
        cSPVector3 r = RotateVector(&v, target.GetOrientation());
        out->x = pos->x + r.x;
        out->y = r.y + pos->y;
        out->z = r.z + pos->z;
        *out = planet->ProjectToSurface(*out, 0);
        return out;
    }
    case 2: {
        cXformObject* ref = 0;
        if (!CinematicManager()->LookupObject(id, &ref))
            return out;
        cXformMsg msg;
        ref->GetTransform(&msg);
        cSPQuaternion q = QuaternionFromMatrix(msg.mMatrix);
        cSPVector3 r = RotateVector(&offset, &q);
        out->x = r.x + msg.mPosition.x;
        out->y = r.y + msg.mPosition.y;
        out->z = r.z + msg.mPosition.z;
        *out = planet->ProjectToSurface(*out, 0);
        return out;
    }
    case 3: {
        cGameObject* o = object_cast(obj, 0x18eb45e);
        cHerd* herd = ((cHerdMember*)o)->GetHerd();
        cSPQuaternion q = planet->GetSurfaceOrientation(*herd->GetPosition());
        cSPVector3 r = RotateVector(&v, &q);
        const cSPVector3* pos = herd->GetPosition();
        out->x = pos->x + r.x;
        out->y = r.y + pos->y;
        out->z = r.z + pos->z;
        *out = planet->ProjectToSurface(*out, 0);
        return out;
    }
    case 4: {
        cGameObject* o = object_cast(obj, 0x18eb4b7);
        cTribeAux* aux = ((cCitizenOwner*)o)->GetTribe()->GetAux();
        cSPVector3 r = RotateVector(&v, aux->mTransform.GetOrientation());
        const cSPVector3* pos = aux->mTransform.GetPosition();
        out->x = r.x + pos->x;
        out->y = r.y + pos->y;
        out->z = r.z + pos->z;
        *out = planet->ClampToSurface(*out);
        return out;
    }
    case 5: {
        cGameObject* o = object_cast(obj, 0x18eb4b7);
        cTribeWithTransform* tribe = ((cCitizenHome*)o)->GetTribe();
        cSPVector3 r = RotateVector(&v, tribe->mTransform.GetOrientation());
        const cSPVector3* pos = tribe->mTransform.GetPosition();
        out->x = r.x + pos->x;
        out->y = r.y + pos->y;
        out->z = r.z + pos->z;
        *out = planet->ClampToSurface(*out);
        return out;
    }
    case 6: {
        cGameObject* o = object_cast(obj, 0x18eb4b7);
        cTribeWithTransform* city = ((cCitizenHome*)o)->GetCity();
        cSPVector3 r = RotateVector(&v, city->mTransform.GetOrientation());
        const cSPVector3* pos = city->mTransform.GetPosition();
        out->x = pos->x + r.x;
        out->y = r.y + pos->y;
        out->z = r.z + pos->z;
        *out = planet->ClampToSurface(*out);
        return out;
    }
    case 7:
    case 8: {
        cActionTarget named;
        if (CinematicManager()->LookupTarget(id, &named)) {
            cSPVector3 r = RotateVector(&v, named.GetOrientation());
            const cSPVector3* pos = named.GetPosition();
            out->x = pos->x + r.x;
            out->y = r.y + pos->y;
            out->z = r.z + pos->z;
            *out = planet->ProjectToSurface(*out, 0);
        }
        return out;
    }
    case 9:
    case 10: {
        cActionTarget named;
        if (CinematicManager()->LookupTarget(id, &named)) {
            *out = *named.GetPosition();
            if (planet->FindGround(named.GetPosition(), 100.0f, out, 1.0f, mode == 9, 0)) {
                const cSPVector3* tp = named.GetPosition();
                cSPVector3 d(tp->x - out->x, tp->y - out->y, tp->z - out->z);
                cSPVector3 facing, up;
                normalized_safe(&facing, &d);
                normalized_safe(&up, out);
                cSPMatrix3 m;
                Matrix3FromFacingAndUp(&m, facing, up);
                cSPQuaternion q = QuaternionFromMatrix(m);
                cSPVector3 r = RotateVector(&v, &q);
                out->x = out->x + r.x;
                out->y = r.y + out->y;
                out->z = r.z + out->z;
                *out = planet->ProjectToSurface(*out, 0);
            }
        }
        return out;
    }
    }
    return out;
}

// ---------------------------------------------------------------- the action
struct cAddActorData {
    unsigned char pad_00[0x0C];
    unsigned int mTargetID;                                          // +0x0C
    int mActorKey;                                                   // +0x10
    int mKind;                                                       // +0x14
    int pad_18;
    int mArg;                                                        // +0x1C
    cSPVector3 mOffsetA;                                             // +0x20
    cSPVector3 mOffsetB;                                             // +0x2C
    int mPlacementA, mArgA;                                          // +0x38, +0x3C
    int mPlacementB, mArgB;                                          // +0x40, +0x44
    bool mbDontWait;                                                 // +0x48
    unsigned char pad_49[3];
    int mArgC;                                                       // +0x4C
    int mEntryID;                                                    // +0x50
};
struct cAction {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual cAddActorData* Cast(unsigned int typeID);                // +0x0C
};

enum {
    kTribeGame = 0x1654C02,
    kCivGame = 0x1654C04,
    kSpaceGame = 0x1654C05,
};

// @ 0x00AD3F70
int UpdateAddActorAction(cAction* pAction, bool bArrive)
{
    cAddActorData* data = pAction ? pAction->Cast(0x055113D6) : 0;
    if (!data)
        return 1;

    if (bArrive) {
        cSPVector3 offsetA(data->mOffsetA.x, data->mOffsetA.y, data->mOffsetA.z);
        cSPVector3 offsetB(data->mOffsetB.x, data->mOffsetB.y, data->mOffsetB.z);
        cActionTarget target;
        if (SP::GetCurrentGameMode() != kCivGame && SP::GetCurrentGameMode() != kSpaceGame) {
            unsigned int targetID = data->mTargetID;
            if (!CinematicManager()->LookupTarget(targetID, &target))
                return 1;
        }

        cSPVector3 pos, facingPos;
        ComputeTargetPosition(pos, target, data->mPlacementA, data->mArgA, data->mArgC, offsetA);
        ComputeTargetPosition(facingPos, target, data->mPlacementB, data->mArgB, data->mArgC, offsetB);

        cSPVector3 dir = kInvalidPosition;
        if (facingPos != kInvalidPosition && facingPos != pos) {
            cSPVector3 delta(facingPos.x - pos.x, facingPos.y - pos.y, facingPos.z - pos.z);
            cSPVector3 n;
            dir = *normalized_safe(&n, &delta);
        } else {
            cSPQuaternion q = PlanetModel()->GetSurfaceOrientation(pos);
            dir = RotateVector(&g_167a53c, &q);
        }

        unsigned int key = CinematicManager()->mContextKey;
        cVignetteContext* context = (cVignetteContext*)CinematicManager()->FindContext(0x055116DA, key);
        if (!context) {
            void* p = EAAllocate(sizeof(cVignetteContext), g_145a6f4, 0, 0, 0, 0);
            context = p ? new (p) cVignetteContext : 0;
            CinematicManager()->AddContext(0x055116DA, context, key);
        }
        cSimRegistry* registry = SimRegistry();
        cVignetteData* vignette = context ? context->Cast(0x055116DA) : 0;
        int entry = registry->CreateEntry(data->mKind, data->mArg, &pos, &dir);
        data->mEntryID = entry;
        vignette->mActors[data->mActorKey] = entry;
        registry->SetFlag(data->mEntryID, CinematicManager()->mEntryFlag);

        switch (SP::GetCurrentGameMode()) {
        case kCivGame:
        case kSpaceGame: {
            cTribeTools* tools = TribeTools();
            tools->RegisterEntry(data->mEntryID);
            break;
        }
        case kTribeGame: {
            // C-style: the members index is declared (and zeroed) with the block's locals, then reset by the
            // loop below. Its first mention here, before `members`, is what orders the two reloads at the
            // members loop's back edge (the compiler numbers register candidates by first mention).
            unsigned int i = 0;
            cCinematicManager* cinematics = CinematicManager();
            cSceneManager* scene = SceneManager();
            cGameObject* object = target.mpObject ? target.mpObject->Cast(0x017F243B) : 0;
            cTribe* tribe;
            if (object && object->GetNounID() == 0x018C6D19) {
                tribe = (cTribe*)object;
            } else {
                cCitizen* citizen = (cCitizen*)object_cast(object, 0x018EB4B7);
                if (!citizen)
                    return 1;
                tribe = citizen->GetTribe();
                cSpatialObject* spatial = citizen->Spatial();
                unsigned int key = CinematicManager()->mContextKey;
                int id = citizen->mID;
                cinematics->PostAction(id, cActionTarget(spatial), key);
                registry->AddMember(data->mEntryID, citizen, 1);
                scene->Remove(spatial);
                if (!tribe)
                    return 1;
            }

            unsigned int needed = registry->GetMemberCount(data->mEntryID);
            cCitizenList& members = *tribe->GetMembers();
            unsigned int count = members.size();
            for (i = 0; needed > 0 && i < count; ++i) {
                cCitizen* citizen = members[i];
                if (citizen->IsAvailable() && !citizen->mbBusy &&
                    !cinematics->IsInScene(citizen->Spatial())) {
                    cSpatialObject* spatial = citizen->Spatial();
                    unsigned int key = CinematicManager()->mContextKey;
                    int id = citizen->mID;
                    cinematics->PostAction(id, cActionTarget(spatial), key);
                    registry->AddMember(data->mEntryID, citizen, 1);
                    scene->Remove(spatial);
                    --needed;
                }
            }
            for (;;) {
                if (needed <= 0)
                    break;
                cCitizen* citizen = tribe->CreateCitizen(1);
                if (!citizen)
                    return 1;
                tribe->AddMember(citizen);
                cSpatialObject* spatial = citizen->Spatial();
                unsigned int key = CinematicManager()->mContextKey;
                int id = citizen->mID;
                cinematics->PostAction(id, cActionTarget(spatial), key);
                cinematics->PushAction(citizen, CinematicManager()->mContextKey);
                registry->AddMember(data->mEntryID, citizen, 1);
                scene->Remove(spatial);
                --needed;
            }
            break;
        }
        }
    }

    if (data->mbDontWait)
        return 1;
    return SimRegistry()->IsDisabled(data->mEntryID) != 0;
}
