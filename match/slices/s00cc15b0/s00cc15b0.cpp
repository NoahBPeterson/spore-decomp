// Slice s00cc15b0: SP::cDefaultToolProjectile::UpdateBombPhase1 (0x00cc1c30), retail layout from
// the Spore ModAPI (cDefaultToolProjectile, size 0x5f0; this = full object).
//
// Per-frame update of a space-tool "bomb" projectile (gravitation wave / peace bomb / cash
// infusion / planet conversion). Phase timer: on the first call it restarts the timer and
// copies the game's wave-front target list (cities) into mWaveFrontTargetCities. While the
// timer is under 20 s it creates the looping visual effect once (oriented from the position's
// outward direction; a 0xb damage type also registers the effect with the nearest game-data
// target), then each frame moves a point from the planet surface along the outward direction
// by radius * (1 - cos(t * 0.05 * pi)) * 0.5 * 2.3 and asks the tool-specific handler for the
// current wave (selected by the tool's resource key) to fire from there. At 20 s the effect is
// stopped and released, mBombPhase becomes 2 and the target list is cleared. Always returns true.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl cos(double);
#pragma intrinsic(sqrt, cos)

struct cSPVector3;
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    __forceinline float SquaredLength() const { return x * x + y * y + z * z; }
    __forceinline float Length() const { return (float)sqrt(SquaredLength()); }
    __forceinline cSPVector3 Normalized() const;
    __forceinline cSPVector3 NormalizedSafe() const;   // inlined SP::normalized_safe (epsilon 1e-8)
};
struct cSPVector3 : Vector3 {
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) { x = ax; y = ay; z = az; }
    cSPVector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
    cSPVector3(const cSPVector3& o) { x = o.x; y = o.y; z = o.z; }
    cSPVector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    cSPVector3 operator-() const { return cSPVector3(-x, -y, -z); }
    cSPVector3 operator*(float s) const { return cSPVector3(x * s, y * s, z * s); }
    cSPVector3 operator+(const Vector3& o) const { return cSPVector3(x + o.x, y + o.y, z + o.z); }
};
__forceinline cSPVector3 Vector3::Normalized() const
{
    float len = Length();
    float inv = 1.0f / len;
    return cSPVector3(x * inv, y * inv, z * inv);
}
__forceinline cSPVector3 Vector3::NormalizedSafe() const
{
    float sq = SquaredLength() + 1e-8f;
    float len = (float)sqrt(sq);
    float inv = 1.0f / len;
    return cSPVector3(x * inv, y * inv, z * inv);
}
struct Matrix3 { float m[9]; };

// 0x006985b0 SP::OrthogonalVector / 0x0069b440 SP::Matrix3FromFacingAndUp (both cdecl, sret)
cSPVector3 OrthogonalVector(const Vector3& v);                // 0x006985b0
Matrix3 Matrix3FromFacingAndUp(const Vector3& facing, const Vector3& up);   // 0x0069b440

// Transform-update message (ctor 0x00434040, 0x38 bytes).
struct XformMsg {
    uint16_t flags;
    uint16_t count;
    Vector3  pos;
    float    scale;
    Matrix3  rot;
    XformMsg();
    void SetPosition(const Vector3& v) { pos = v; flags |= 4; ++count; }
    void SetRotation(const Matrix3& m) { rot = m; flags |= 2; ++count; }
};

#define VSLOT(n) virtual void _v##n();

struct IVisualEffect {
    VSLOT(0)
    virtual int Release();                                    // +0x04
    virtual void Start(int flags);                            // +0x08
    virtual void Stop(int flags);                             // +0x0c
    VSLOT(4) VSLOT(5)
    virtual void SetTransform(const XformMsg& xf);            // +0x18
};
struct cEffectsManager {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    virtual bool CreateVisualEffect(uint32_t id, int flags, IVisualEffect** out);   // +0x2c
};
cEffectsManager* EffectsManager();                            // 0x0067ddd0

// Spatial subobject at +0x34 (cLocomotiveObject): GetPosition at +0x2c.
struct cLocomotiveObject {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    virtual const Vector3& GetPosition();                     // +0x2c
};

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    bool operator==(const ResourceKey& o) const
    {
        return instanceID == o.instanceID && typeID == o.typeID && groupID == o.groupID;
    }
};
extern const ResourceKey kGravitationWaveTool;    // 0x0169a8f0
extern const ResourceKey kPeaceBombTool;          // 0x0169a8e4
extern const ResourceKey kCashInfusionTool;       // 0x0169a89c
extern const ResourceKey kPlanetConversionTool;   // 0x0169a908
bool __cdecl IsToolKey(const ResourceKey* key, const ResourceKey* ref);   // 0x004eb930

struct cSpaceToolData {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual const ResourceKey* GetToolKey();                  // +0x18
    uint32_t GetEffectID();                                   // 0x0104bf10
};

struct cSPTimer {
    uint32_t mData[8];
    bool IsRunning();                                         // 0x00feba90
    void Restart();                                           // 0x00bc3130
    uint64_t GetElapsedTime();                                // 0x00bc3190
};

struct cCity;
struct sp_vector_cities {
    cCity** mpBegin; cCity** mpEnd; cCity** mpCapacity; const char* mAllocName;
    sp_vector_cities& operator=(const sp_vector_cities& x);   // 0x01011cc0
    cCity** erase(cCity** first, cCity** last);               // 0x00e25bd0
};
struct GameDataVector { int pad; sp_vector_cities vec; };     // vector at +4
typedef void (__cdecl *GameDataFn)();
struct cGameNounManager {
    GameDataVector* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d, const void* tag);   // 0x00b21340 (ret 0x14)
    void* FUN_00ace2c0();                                     // 0x00ace2c0
};
cGameNounManager* NounManager();                              // 0x00b3d300
void __cdecl FUN_00cd7d10();
void __cdecl FUN_00d3d420();
void __cdecl FUN_00acdff0();
void __cdecl FUN_00b1e500();
// game-data type tag 0x018c43e8 lives in the .bind section: passed as a raw address

extern float gPi;                                             // 0x0157d364
struct cPlanetModel {
    float GetRadius();                                        // 0x00b7e4d0
};
cPlanetModel* PlanetModel();                                  // 0x00b3d350

struct cBombTarget { void FUN_00bda120(IVisualEffect* effect); };   // 0x00bda120
struct EmptyTag {};
cBombTarget* __cdecl FUN_00ac9310(void* container, const Vector3* pos, EmptyTag tag);   // 0x00ac9310

struct cDefaultToolProjectile {
    uint32_t pad00[0x34 / 4];
    cLocomotiveObject mLocomotive;                            // 0x34 (vptr only)
    uint32_t pad38[(0x518 - 0x38) / 4];
    cSpaceToolData* mpTool;                                   // 0x518
    uint32_t pad51c[(0x538 - 0x51c) / 4];
    int mDamageType;                                          // 0x538
    uint32_t pad53c[(0x544 - 0x53c) / 4];
    int mBombPhase;                                           // 0x544
    cSPTimer mPhaseTimer;                                     // 0x548
    uint32_t pad568[(0x5cc - 0x568) / 4];
    IVisualEffect* mpEffect;                                  // 0x5cc
    uint32_t pad5d0[(0x5dc - 0x5d0) / 4];
    sp_vector_cities mWaveFrontTargetCities;                  // 0x5dc

    bool UpdateBombPhase1();
    void FireGravityWave(cSPVector3 pos, cSPVector3 dir);           // 0x00cc1890
    void FirePeaceBomb(cSPVector3 pos, cSPVector3 dir);             // 0x00cc0700
    void FireCashInfusion(cSPVector3 pos, cSPVector3 dir);          // 0x00cbc3c0
    void FirePlanetConversion(cSPVector3 pos, cSPVector3 dir);      // 0x00cbc7f0
};

// @ 0x00cc1c30
bool cDefaultToolProjectile::UpdateBombPhase1()
{
    cSPTimer* timer = &mPhaseTimer;
    if (!timer->IsRunning()) {
        timer->Restart();
        cGameNounManager* nm = NounManager();
        mWaveFrontTargetCities =
            nm->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00acdff0, FUN_00b1e500, (const void*)0x018c43e8)->vec;
    }
    float t = (float)timer->GetElapsedTime() * 0.001f;
    if (20.0f > t) {
        if (mpEffect == 0) {
            uint32_t effectID = mpTool->GetEffectID();
            cEffectsManager* effects = EffectsManager();
            if (mpEffect) {
                IVisualEffect* e = mpEffect;
                mpEffect = 0;
                e->Release();
            }
            if (effects->CreateVisualEffect(effectID, 0, &mpEffect)) {
                XformMsg xf;
                xf.SetPosition(mLocomotive.GetPosition());
                Vector3 up = mLocomotive.GetPosition().Normalized();
                Vector3 facing = OrthogonalVector(up).Normalized();
                xf.SetRotation(Matrix3FromFacingAndUp(facing, up));
                mpEffect->SetTransform(xf);
                mpEffect->Start(0);
                if (mDamageType == 0xb) {
                    const Vector3& p = mLocomotive.GetPosition();
                    void* container = NounManager()->FUN_00ace2c0();
                    cBombTarget* target = FUN_00ac9310(container, &p, EmptyTag());
                    if (target)
                        target->FUN_00bda120(mpEffect);
                }
            }
        }

        float wave = (1.0f - (float)cos(t * 0.05f * gPi)) * 0.5f;
        cSPVector3 down = -mLocomotive.GetPosition().NormalizedSafe();
        float depth = PlanetModel()->GetRadius() * wave * 2.3f;
        cSPVector3 offset = down * depth;
        const Vector3& p1 = mLocomotive.GetPosition();
        cSPVector3 pos(p1.x + offset.x, p1.y + offset.y, p1.z + offset.z);
        cSPVector3 dir = -down;

        const ResourceKey* key = mpTool->GetToolKey();
        if (*key == kGravitationWaveTool) {
            FireGravityWave(pos, dir);
            return true;
        }
        if (*key == kPeaceBombTool) {
            FirePeaceBomb(pos, dir);
            return true;
        }
        if (*key == kCashInfusionTool) {
            FireCashInfusion(pos, dir);
            return true;
        }
        if (IsToolKey(key, &kPlanetConversionTool)) {
            FirePlanetConversion(pos, dir);
            return true;
        }
    } else {
        if (mpEffect) {
            mpEffect->Stop(0);
            IVisualEffect* e = mpEffect;
            mpEffect = 0;
            if (e)
                e->Release();
        }
        mBombPhase = 2;
        mWaveFrontTargetCities.erase(mWaveFrontTargetCities.mpBegin, mWaveFrontTargetCities.mpEnd);
    }
    return true;
}
