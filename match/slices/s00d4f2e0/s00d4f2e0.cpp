// Slice s00d4f2e0 -- SP::cNightPredatorEvent::TriggerEvent (0x00d4f2e0, 1540 bytes, __thiscall).
// Flags: /O2 /MD /Gy /TP /arch:SSE (/EHsc not needed: no unwinding objects).
//
// Drama event "night predator": finds (or creates, type 0x01be418e / key 0xc21f9669) the predator herd
// at the avatar's creature, places it at a point `dist` metres ahead of the creature (towards the
// closest water if there is any), drops it on the planet surface, and then spawns its herd members
// one by one at a surface transform whose "up" is the planet normal and whose forward is the
// tangential component of the camera/forward axis, `dist` behind the avatar.  Each spawned creature
// gets flag 0x10000 in its brain record.
#include "types.h"
#include <math.h>

inline void* operator new(unsigned int, void* p) { return p; }

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    __forceinline Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Quat { float x, y, z, w; };

struct Matrix3 {  // rw::math::fpu::Matrix33Template<float,0>, size 0x24
    Vec3 xAxis, yAxis, zAxis;
    Matrix3() {}
    Matrix3(const Matrix3& other);  // 0x0041cb40 (out of line copy ctor)
};

struct cSPTransform {  // size 0x38
    uint16_t mFlags;              // +0x00
    uint16_t mModificationCount;  // +0x02
    Vec3 mTranslation;            // +0x04
    float mScale;                 // +0x10
    Matrix3 mRotation;            // +0x14
    cSPTransform& operator=(const cSPTransform& other);  // 0x00537dc0
};

extern const Vec3 gDefaultTranslation;   // 0x0169e440
extern const Vec3 gForwardAxis;          // 0x0169e4a4
extern const Matrix3 gIdentity;          // 0x0169e4b0

Vec3* RotateByQuat(Vec3* out, const Vec3* v, const Quat* q);   // 0x0059aed0 (cdecl)
Vec3* normalized_safe(Vec3* out, const Vec3* v);               // 0x00449c20 (cdecl)
Vec3* FUN_0108db30();                                          // cdecl, no args: the reference "side" axis
Matrix3* QuatToMatrix(Matrix3* out, const Quat* q);            // 0x004a9b40 (cdecl)

// ---- avatar and its position component (slot 11 = GetPosition) --------------------------------------
struct cAvatarComp {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual const Vec3* GetPosition();            // slot 11 (+0x2c)
};
struct cNearNoun;
struct cAvatar {
    char pad[0xc0];
    cAvatarComp mComp;                            // +0xc0
    cNearNoun* GetCreature();                     // 0x00c04590
};

// ---- the herd ----------------------------------------------------------------------------------------
struct cGameData {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7();
    virtual int GetTypeId();                      // slot 8 (+0x20)
};
struct cHerd : cGameData {
    char pad04[0x3c];
    void** mHerdBegin;                            // +0x40
    void** mHerdEnd;                              // +0x44
    char pad48[0xa4 - 0x48];
    uint32_t mSpeciesKey;                         // +0xa4
    char padA8[0xf4 - 0xa8];
    uint32_t mTargetHerdSize;                     // +0xf4
    char padF8[0x124 - 0xf8];
    int mActivateBrainLevel;                      // +0x124
    void SetPosition(const Vec3* pos);            // 0x00c6ba20 (ret 4)
};

// ---- creature -----------------------------------------------------------------------------------------
struct cOrientComp {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11();
    virtual const Quat* GetOrientation();         // slot 12 (+0x30)
};
struct cOrientHolder {
    char pad[0x34];
    cOrientComp mOrient;                          // +0x34
};
struct cGizmo {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void ApplyTo(cSPTransform* out, cSPTransform* in, cSPTransform* ref);   // slot 4 (+0x10), ret 0xc
};
struct cNearNoun {
    char pad[0x160];
    cOrientHolder* mpHolder;                      // +0x160
    const Vec3* GetPosition();                    // 0x00c6acc0
};

// ---- planet / noun manager ---------------------------------------------------------------------------
struct cPlanetModel {
    bool FindClosestWater(const Vec3* pos, float radius, Vec3* outWater);   // 0x00b8bb70 (ret 0xc)
    Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* dir);           // 0x00b815a0 (ret 8)
    Quat* BuildSurfaceOrientation(Quat* out, const Vec3* pos);              // 0x00b7f190 (ret 8)
    Vec3* FUN_00b82970(Vec3* out, const Vec3* pos, int flag);               // 0x00b82970 (ret 0xc)
};
cPlanetModel* PlanetModel();                                                // 0x00b3d350

struct cGameNounManager {
    cAvatar* GetAvatar();                                                   // 0x00b1fdb0
    cGameData* CreateNoun(uint32_t type, uint32_t key, int a, const Vec3* pos, int b);   // 0x00b23650 (ret 0x14)
};
cGameNounManager* NounManager();                                            // 0x00b3d300

struct cGizmoMgr {
    cGizmo* Create(int n);                                                  // 0x00ac84d0 (ret 4)
};
cGizmoMgr* GetGizmoMgr();                                                   // 0x00b3d480 (cdecl)

struct cBrainRecord { char pad[0x5fc]; uint32_t mFlags; };                  // +0x5fc
struct cSpawned { char pad[0xb4c]; cBrainRecord* mpBrain; };                // +0xb4c
cSpawned* SpawnMember(const Vec3* pos, uint32_t key, int a, cHerd* herd, int b, int c);   // 0x00c099e0 (cdecl)

// ---- app / property list --------------------------------------------------------------------------------
struct cLookup {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void* Find(uint32_t key);             // slot 3 (+0x0c)
};
struct cAppSub2 {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
    virtual cLookup* GetLookup();                 // slot 14 (+0x38)
};
struct cAppSub {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual cAppSub2* GetSub();                   // slot 20 (+0x50)
};
struct cApp {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual cAppSub2* GetSub();                   // slot 20 (+0x50)
};
cApp* App();                                      // 0x0067dd10

struct Property {
    char pad[0x12];
    uint16_t mType;                               // +0x12
    float* GetFloat();                            // 0x0041ea70
};
struct cPropList {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
    virtual bool GetProperty(uint32_t id, Property** out);   // slot 9 (+0x24)
};

struct cNightPredatorEvent {
    char pad00[0x40];
    cPropList* mpConfig;                          // +0x40
    cHerd* FindHerd(int a, uint32_t key);         // 0x00d4cf10 (ret 8)
    void FUN_00d4edd0(int a, cHerd* herd);        // 0x00d4edd0 (ret 8)
    void TriggerEvent();                          // 0x00d4f2e0
};

// @ 0x00D4F2E0
void cNightPredatorEvent::TriggerEvent()
{
    float tmpBuf[4];
    Vec3& tmpA = *(Vec3*)tmpBuf;
    cAvatar* avatar = NounManager()->GetAvatar();
    cNearNoun* creature = avatar->GetCreature();

    cLookup* lookup = App()->GetSub()->GetLookup();
    if (!lookup)
        return;
    if (!lookup->Find(0x2a7ecd2))
        return;

    cHerd* herd = FindHerd(0, 0x52aa6117);
    if (!herd) {
        Vec3 pos = *creature->GetPosition();
        cGameData* d = NounManager()->CreateNoun(0x1be418e, 0xc21f9669, 0, &pos, 0);
        if (!d)
            return;
        herd = (d->GetTypeId() == 0x1be418e) ? (cHerd*)d : 0;
        herd->mActivateBrainLevel = -1;
        FUN_00d4edd0(0, herd);
    }

    float dist = 50.0f;
    cPropList* props = mpConfig;
    if (props) {
        Property* prop;
        if (props->GetProperty(0x3551d2ea, &prop) && prop->mType == 0xd)
            dist = *prop->GetFloat();
    }

    Vec3 fwd = *RotateByQuat(&tmpA, &gForwardAxis, creature->mpHolder->mOrient.GetOrientation());
    Vec3 water;
    if (PlanetModel()->FindClosestWater(creature->GetPosition(), dist, &water)) {
        const Vec3* p = creature->GetPosition();
        Vec3 d(p->x - water.x, p->y - water.y, p->z - water.z);
        fwd = *normalized_safe(&tmpA, &d);
    }
    fwd.x = fwd.x * dist;
    fwd.y = fwd.y * dist;
    fwd.z = fwd.z * dist;

    const Vec3* base = creature->GetPosition();
    Vec3 spawn(fwd.x + base->x, base->y + fwd.y, base->z + fwd.z);
    Vec3 surf;
    PlanetModel()->DirectionToSurfacePosition(&surf, &spawn);
    herd->SetPosition(&surf);

    cGizmo* gizmo = GetGizmoMgr()->Create(1);

    // planet normal at the avatar and the tangential part of the reference side axis
    const Vec3* ap = avatar->mComp.GetPosition();
    float ax = ap->x;
    float nInv = 1.0f / sqrtf((ax * ax + ap->y * ap->y + ap->z * ap->z) + 1e-8f);
    Vec3 up;
    up.x = nInv * ax;
    up.y = ap->y * nInv;
    up.z = ap->z * nInv;

    const Vec3* side = FUN_0108db30();
    float dot = (up.y * side->y + up.z * side->z) + up.x * side->x;
    Vec3 w;
    w.x = side->x - up.x * dot;
    w.y = side->y - up.y * dot;
    w.z = side->z - up.z * dot;
    float wInv = 1.0f / sqrtf((w.x * w.x + w.z * w.z + w.y * w.y) + 1e-8f);
    Vec3 off((wInv * w.x) * dist, (w.y * wInv) * dist, (w.z * wInv) * dist);

    const Vec3* bp = avatar->mComp.GetPosition();
    Vec3 pos2(bp->x - off.x, bp->y - off.y, bp->z - off.z);

    cSPTransform xf1;
    xf1.mFlags = 0;
    xf1.mModificationCount = 0;
    new (&xf1.mTranslation) Vec3(gDefaultTranslation);
    xf1.mScale = 1.0f;
    new (&xf1.mRotation) Matrix3(gIdentity);

    cSPTransform xf2;
    new (&xf2.mTranslation) Vec3(gDefaultTranslation);
    xf2.mModificationCount = 0;
    xf2.mFlags = 0;
    xf2.mScale = 1.0f;
    new (&xf2.mRotation) Matrix3(gIdentity);

    Matrix3 m;
    xf1.mRotation = *QuatToMatrix(&m, PlanetModel()->BuildSurfaceOrientation((Quat*)&tmpA, &pos2));
    xf1.mFlags |= 2;
    xf1.mModificationCount += 1;
    xf1.mTranslation = *PlanetModel()->FUN_00b82970(&tmpA, &pos2, 0);
    xf1.mFlags |= 4;
    xf1.mModificationCount += 1;
    xf2 = xf1;

    uint32_t count = (uint32_t)(herd->mHerdEnd - herd->mHerdBegin);
    uint32_t key = herd->mSpeciesKey;
    if (count < herd->mTargetHerdSize) {
        do {
            gizmo->ApplyTo(&xf1, &xf2, &xf1);
            cSpawned* s = SpawnMember(&xf2.mTranslation, key, 1, herd, 0, 1);
            s->mpBrain->mFlags |= 0x10000;
            count++;
        } while (count < herd->mTargetHerdSize);
    }
}
