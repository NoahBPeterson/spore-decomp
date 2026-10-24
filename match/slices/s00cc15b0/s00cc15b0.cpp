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
    uint32_t pad04[(0x114 - 4) / 4];
    void* mp114;                                              // +0x114
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
    uint32_t pad10[2];                                        // +0x10 (allocator tail, size 0x14)
    sp_vector_cities& operator=(const sp_vector_cities& x);   // 0x01011cc0
    cCity** erase(cCity** first, cCity** last);               // 0x00e25bd0
};
struct GameDataVector { int pad; sp_vector_cities vec; };     // vector at +4
typedef void (__cdecl *GameDataFn)();
struct cAvatar;
struct cGameNounManager {
    GameDataVector* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d, const void* tag);   // 0x00b21340 (ret 0x14)
    void* FUN_00ace2c0();                                     // 0x00ace2c0
    cAvatar* GetAvatar();                                     // 0x00b1fdb0
};
cGameNounManager* NounManager();                              // 0x00b3d300
void __cdecl FUN_00cd7d10();
void __cdecl FUN_00d3d420();
void __cdecl FUN_00acdff0();
void __cdecl FUN_00accbb0();
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

// ---------------------------------------------------------------------------
// Helpers for 0x00cc15b0 (SP::GetBestCityTarget) and 0x00cc1890
// (cDefaultToolProjectile::FireGravityWave).
// ---------------------------------------------------------------------------

// Ref-counted object: slot 0 = AddRef, slot 1 = Release (EA::AutoRefCount target).
struct cRefObj {
    virtual void AddRef();                                    // +0x00
    virtual void Release();                                   // +0x04
};

// Combatant subobject (state at +0x34, polymorphic at +0x120 of its owner).
struct cCombatant : cRefObj {
    VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual void TriggerWave(float strength, int empireID, int a, const void* b, int c);   // +0x18
    VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    virtual const Vector3& GetPosition();                     // +0x2c
    VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17)
    VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22)
    virtual void* LookupAttachment(const void* key);          // +0x5c
    int GetState();                                           // 0x008e7f80: [this+0x34]
};

// Object returned by cCombatant::LookupAttachment.
struct cAttachment : cRefObj {
    VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17)
    VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25)
    VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30) VSLOT(31) VSLOT(32)
    virtual void* GetTribe();                                 // +0x84
    void* GetTribeField();                                    // 0x00bce5c0: [this+0x688]
};

// City game-data object: tag at +0x38, combatant at +0x120, float at +0x158.
struct cCityObj : cRefObj {
    VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13)
    virtual int GetTag();                                     // +0x38
    VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22)
    VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30)
    VSLOT(31) VSLOT(32) VSLOT(33) VSLOT(34) VSLOT(35) VSLOT(36) VSLOT(37) VSLOT(38)
    VSLOT(39) VSLOT(40) VSLOT(41) VSLOT(42)
    virtual cCityObj* GetOwnerObj();                          // +0xac
    uint32_t pad04[(0x120 - 4) / 4];
    cCombatant mCombatant;                                    // +0x120
    uint32_t pad124[(0x158 - 0x124) / 4];
    float m158;                                               // +0x158
};

// Ground/population game-data object with a combatant subobject at +0x588.
struct cGroundObj : cRefObj {
    uint32_t pad04[(0x588 - 4) / 4];
    cCombatant mCombatant;                                    // +0x588
};

// Small vector with 32 inline elements (Vec2b).
struct Vec2b {
    cRefObj** mpBegin;                                        // +0x00
    cRefObj** mpEnd;                                          // +0x04
    cRefObj** mpCap;                                          // +0x08
    uint32_t  mPad0c;                                         // +0x0c
    cRefObj** mpInline;                                       // +0x10
    cRefObj*  mpBuf[32];                                      // +0x18
    Vec2b() { mpBegin = mpBuf; mpEnd = mpBuf; mpCap = mpBuf + 32; mpInline = mpBuf; }
    ~Vec2b();                                                 // 0x008e2b20 (Vec2b::Free)
    cRefObj** erase(cRefObj** first, cRefObj** last);         // 0x00e25bd0
};

// Heap ref vector (out-of-line destructor).
struct RefVector {
    cRefObj** mpBegin;                                        // +0x00
    cRefObj** mpEnd;                                          // +0x04
    cRefObj** mpCap;                                          // +0x08
    uint32_t  pad0c;                                          // +0x0c
    uint32_t  pad10[2];                                       // +0x10 (size 0x14)
    void Construct(uint32_t count, const void* src);          // 0x00b93c60 (ret 8)
    ~RefVector();                                             // 0x00ae6970
    cRefObj** erase(cRefObj** first, cRefObj** last);         // 0x00e25bd0
};

// Heap ref vector with no destructor (the caller releases and frees it).
struct RefVec {
    cRefObj** mpBegin;                                        // +0x00
    cRefObj** mpEnd;                                          // +0x04
    cRefObj** mpCap;                                          // +0x08
    uint32_t  pad0c;                                          // +0x0c
    uint32_t  pad10[2];                                       // +0x10 (size 0x14)
    void Construct(uint32_t count, const void* src);          // 0x00b93c60 (ret 8)
};

struct cTribeMemberList {
    cRefObj**   mpBegin;                                      // +0x00
    cRefObj**   mpEnd;                                        // +0x04
    cRefObj**   mpCap;                                        // +0x08
    const char* mAllocName;                                   // +0x0c
};

struct cCity {
    void* GetCityHall();                                      // 0x00bd9b40: [this+0x320]
};
struct cTribe : cCity {
    cTribeMemberList* GetMembers();                           // 0x00c8e810: this+0x340
    void CopyMembers(Vec2b* out);                             // 0x00be5700 (ret 4)
};

struct RandomLCG { uint32_t RandomUint32Uniform(uint32_t n); };   // 0x00a68fb0
RandomLCG* const gRandomLCG = (RandomLCG*)0x01601760;

struct cAvatar {
    void FUN_00ffa900(cCityObj* city, int id);                // 0x00ffa900 (ret 8)
};

struct cToolExtra {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8)
    VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16)
    VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24)
    VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30) VSLOT(31) VSLOT(32)
    VSLOT(33) VSLOT(34) VSLOT(35) VSLOT(36) VSLOT(37) VSLOT(38) VSLOT(39) VSLOT(40)
    VSLOT(41) VSLOT(42) VSLOT(43) VSLOT(44) VSLOT(45)
    virtual void* Lookup(const void* key);                    // +0xb8
};
struct cToolThing {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3)
    virtual int GetID();                                      // +0x10
};

cGameNounManager* SpaceGameGet();                             // 0x01002bd0
int __cdecl GetPlayerEmpireID();                              // 0x01021090
void* __cdecl EAlloc(uint32_t size, const char* name, int a, int b, const char* file, int line);   // 0x00f473a0
void __cdecl EFree(void* p);                                  // 0x00f47380
cRefObj** __cdecl CopyRefs(cRefObj*** out, cRefObj** first, cRefObj** last, cRefObj** dest, uint32_t dummy);   // 0x00829110

// @ 0x00cc15b0
cCombatant* __cdecl GetBestCityTarget(cTribe* tribe, cCombatant* combatant)
{
    if (combatant != 0 && combatant->GetState() != 2) {
        cAttachment* a = (cAttachment*)combatant->LookupAttachment((const void*)0x0436f315);
        if (a != 0 && a->GetTribeField() == tribe)
            return combatant;
        cAttachment* b = (cAttachment*)combatant->LookupAttachment((const void*)0x0e9cb8ba);
        if (b != 0 && b->GetTribe() == tribe)
            return combatant;
    }

    Vec2b candidates;
    tribe->CopyMembers(&candidates);
    while (candidates.mpBegin != candidates.mpEnd) {
        uint32_t count = (uint32_t)(candidates.mpEnd - candidates.mpBegin);
        uint32_t index = gRandomLCG->RandomUint32Uniform(count);
        cGroundObj* obj = (cGroundObj*)candidates.mpBegin[index];
        cCombatant* cand = obj ? &obj->mCombatant : 0;
        if (cand->GetState() == 0)
            return cand;

        cRefObj* last = candidates.mpEnd[-1];
        cRefObj* old = candidates.mpBegin[index];
        if (last != old) {
            if (last)
                last->AddRef();
            candidates.mpBegin[index] = last;
            if (old)
                old->Release();
        }
        candidates.erase(candidates.mpBegin + (count - 1), candidates.mpEnd);
    }

    cTribeMemberList* members = tribe->GetMembers();
    RefVector list;
    list.Construct((uint32_t)(members->mpEnd - members->mpBegin), &members->mAllocName);
    cRefObj** cursor = list.mpBegin;
    CopyRefs(&cursor, members->mpBegin, members->mpEnd, list.mpBegin, 0.0f);
    list.mpEnd = cursor;

    while (list.mpBegin != list.mpEnd) {
        uint32_t count = (uint32_t)(list.mpEnd - list.mpBegin);
        uint32_t index = gRandomLCG->RandomUint32Uniform(count);
        cCityObj* obj = (cCityObj*)list.mpBegin[index];
        if (obj->GetTag() != 0x1007ae63 && obj->mCombatant.GetState() == 0)
            return &obj->mCombatant;

        cRefObj* old = list.mpBegin[index];
        cRefObj* last = list.mpEnd[-1];
        if (last != old) {
            if (last)
                last->AddRef();
            list.mpBegin[index] = last;
            if (old)
                old->Release();
        }
        list.erase(list.mpBegin + (count - 1), list.mpEnd);
    }

    void* hall = tribe->GetCityHall();
    if (hall != 0)
        return &((cCityObj*)hall)->mCombatant;
    return 0;
}

// @ 0x00cc1890
void cDefaultToolProjectile::FireGravityWave(cSPVector3 pos, cSPVector3 dir)
{
    int id;
    cToolExtra* extra = (cToolExtra*)mpTool->mp114;
    if (extra != 0) {
        cToolThing* thing = (cToolThing*)extra->Lookup((const void*)0x013f94d4);
        if (thing != 0)
            id = thing->GetID();
        else
            id = -1;
    } else {
        id = -1;
    }

    cAvatar* avatar = SpaceGameGet()->GetAvatar();
    cGameNounManager* nm = NounManager();
    sp_vector_cities* cities =
        &nm->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00acdff0, FUN_00b1e500,
                               (const void*)0x018c43e8)->vec;

    RefVec list;
    list.Construct((uint32_t)(cities->mpEnd - cities->mpBegin), &cities->mAllocName);
    cRefObj** cursor = list.mpBegin;
    CopyRefs(&cursor, (cRefObj**)cities->mpBegin, (cRefObj**)cities->mpEnd, list.mpBegin,
             *(const uint32_t*)&pos.x);
    list.mpEnd = cursor;

    int itemCount = (int)(cursor - list.mpBegin);
    for (int i = 0; i < itemCount; ++i) {
        cCityObj* city = (cCityObj*)list.mpBegin[i];
        const Vector3& p = city->mCombatant.GetPosition();
        float dx = p.x - pos.x;
        float dy = p.y - pos.y;
        float dz = p.z - pos.z;
        float inv = 1.0f / (float)sqrt((dx * dx + dz * dz) + dy * dy + 1e-8f);
        float dot = (inv * dx) * dir.x + dir.z * (dz * inv) + dir.y * (dy * inv);
        if (dot > 0.0f)
            avatar->FUN_00ffa900(city, id);
    }

    nm = NounManager();
    cities = &nm->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00accbb0, FUN_00b1e500,
                                    (const void*)0x018c6d19)->vec;

    cRefObj** wave = 0;
    int waveCount = (int)(cities->mpEnd - cities->mpBegin);
    if (waveCount != 0)
        wave = (cRefObj**)EAlloc((uint32_t)waveCount * 4, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    cRefObj** wcursor = wave;
    CopyRefs(&wcursor, (cRefObj**)cities->mpBegin, (cRefObj**)cities->mpEnd, wave,
             *(const uint32_t*)&pos.x);

    int waveSize = (int)(wcursor - wave);
    for (int i = 0; i < waveSize; ++i) {
        cCityObj* city = (cCityObj*)wave[i];
        const Vector3& p = city->mCombatant.GetPosition();
        float dx = p.x - pos.x;
        float dy = p.y - pos.y;
        float dz = p.z - pos.z;
        float inv = 1.0f / (float)sqrt((dx * dx + dz * dz) + dy * dy + 1e-8f);
        float dot = (inv * dx) * dir.x + (dy * inv) * dir.y + (dz * inv) * dir.z;
        if (dot > 0.0f) {
            cCityObj* owner = city->GetOwnerObj();
            owner->mCombatant.TriggerWave(owner->m158, GetPlayerEmpireID(), 0,
                                          (const void*)0x0169a414, 0);
        }
    }

    for (cRefObj** p = wave; p < wcursor; ++p) {
        if (*p)
            (*p)->Release();
    }
    if (wave != 0 && ((uint32_t*)wave)[-1] != 0)
        EFree(wave);
    for (cRefObj** p = list.mpBegin; p < list.mpEnd; ++p) {
        if (*p)
            (*p)->Release();
    }
    if (list.mpBegin != 0 && ((uint32_t*)list.mpBegin)[-1] != 0)
        EFree(list.mpBegin);
}
