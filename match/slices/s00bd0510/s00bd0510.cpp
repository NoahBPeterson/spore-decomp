// Slice s00bd0510 -- creature combat hook: the TakeHit wrapper of the space-stage creature combatant.
// It filters the hit (dead / invulnerable / friendly), reports "fought enemy" to the relationship manager,
// plays a hit effect, calls cCombatant::TakeHit, and on the killing blow (or a random 1/3 chance) spawns
// debris-like particles at a random point of the bounding box.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

#define VPAD(n) virtual void vpad##n()

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct RawVec3 { float x, y, z; };
struct Mat3 { float m[9]; };
struct BBox { float minx, miny, minz, maxx, maxy, maxz; };

// The 2.0-unit lift / 4.0 scale effect message (ctor at 00434040).
struct XformMsg {
    uint16_t flags;
    uint16_t count;
    RawVec3 pos;
    float scale;                 // +0x10
    uint32_t pad14[3];
    Mat3 rot;                    // +0x20
    XformMsg();
};

struct cIVisualEffect {
    VPAD(0);
    virtual void Release();                              // +0x04
    virtual void Func8(int a);                           // +0x08
    VPAD(3); VPAD(4); VPAD(5);
    virtual void Apply(XformMsg* m);                     // +0x18
};

template <class T> struct AutoRefCount {
    T* mp;
    AutoRefCount() : mp(0) {}
    ~AutoRefCount() { if (mp) mp->Release(); }
    T** AsPPTypeParam();                                 // 00a16f40
};

struct EffectsMgr {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    virtual bool CreateEffect(uint32_t id, int a, cIVisualEffect** out);   // +0x2c
};
struct SoundMgr {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20);
    VPAD(21); VPAD(22); VPAD(23);
    virtual void Play(uint32_t id, const Vec3* pos, const Vec3* dir);      // +0x60
};

// Secondary base at +0x34 of the creature: transform/locomotion interface.
struct cSpatial {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    virtual Vec3* GetPosition();                         // +0x2c
    VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17);
    virtual bool IsVisible();                            // +0x48
    VPAD(19); VPAD(20); VPAD(21); VPAD(22);
    virtual Vec3* GetFacing(Vec3* out);                  // +0x5c
    VPAD(24); VPAD(25);
    virtual BBox* GetBounds();                           // +0x68
    VPAD(27); VPAD(28); VPAD(29); VPAD(30); VPAD(31); VPAD(32); VPAD(33); VPAD(34); VPAD(35); VPAD(36);
    virtual void SetTarget(const Vec3* v);               // +0x94
};

struct FlagTarget { uint8_t pad[0x8e]; uint8_t mFlag8e; void SetFlag8e(); };   // 00bef880
struct Combatant;
// Primary object at -0x588 of the combatant.
struct Creature {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    virtual bool IsDead();                               // +0x2c
    VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18);
    virtual int GetOwnerEmpire();                        // +0x4c
    FlagTarget* GetFlagTarget();                         // 00bccf20
};

// The thing that hit us.
struct HitSource {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20);
    VPAD(21); VPAD(22);
    virtual int Cast(uint32_t id);                       // +0x5c
};
struct Inventory { uint32_t pad[0x508 / 4]; };

struct cSPTimer {
    bool IsRunning();                                    // 00feba90
    uint64_t GetElapsedTime();                           // 00bc3190
    void Restart();                                      // 00bc3130
};

struct GameSim { void* GetPlayerInventory(); void Func_ffd830(void* owner); }; // 00a1ad60 / 00ffd830

struct Extra { uint8_t pad[0x150]; uint8_t mData[1]; void* GetData(); };   // 00ba6430
struct Parent {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20);
    VPAD(21); VPAD(22); VPAD(23); VPAD(24); VPAD(25); VPAD(26);
    virtual Extra* Get6c();                              // +0x6c
    uint8_t pad[0x6e8 - 0x70];
    cSPTimer mTimer6e8;
    void ClearAggro();                                   // 00bd9e50
    void Func_bdbf10();                                  // 00bdbf10
    void Func_be2070(Creature* c, int a);                // 00be2070 (ret 8)
};

struct SpawnMgr { uint8_t pad[0xbc]; struct Spawner* mpSpawner; };
struct Spawner { void Spawn(int a, int b, int owner, Vec3 pos, Vec3 dir); };   // 00d5cfd0 (ret 0x24)

struct RelMgr { float RecordFoughtEnemyEvent(int a, int b, uint32_t c, float d); };   // 00d06270 (ret 0x10)
struct NounMgr { int GetPlayerEmpireOrMinus1(); };       // 00b1f9d0

// globals / free functions
int GetCurrentGameMode();                                // 00b5b800
int GetPlayerEmpireID();                                 // 01021090
GameSim* GetUFOSimulator();                              // 00ffbe50
void* FUN_00ae3370(HitSource* s);                        // 00ae3370
EffectsMgr* GetEffectsManager();                         // 0067ddd0
SoundMgr* GetSoundMgr();                                 // 00b3d240
SpawnMgr* GetSpawnMgr();                                 // 00b3d480
RelMgr* GetRelationshipManager();                        // 00b3d2c0
NounMgr* GetNounManager();                               // 00b3d300
Vec3* normalized_safe(Vec3* out, const Vec3* v);         // 00449c20
Mat3* Matrix3FromFacingAndUp(Mat3* out, const Vec3* facing, const Vec3* up);   // 0069b440
float RandomRange(float r);                             // 0059da80
extern Vec3 g168b66c;
__forceinline int RoundF(float x) { __asm { cvtss2si eax, x } }

struct Combatant {
    uint8_t pad00[0xd4];
    cSPTimer mTimerD8;                                   // +0xd8
    uint8_t padd8[0x100 - 0xd8 - 1];
    Parent* mpParent;                                    // +0x100
    uint8_t pad104[0x128 - 0x104];
    cSPTimer mStunTimer;                                 // +0x128

    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6();
    virtual void OnHitSource(HitSource* s);              // +0x1c

    int GetDamageState();                                // 008e7f80
    void TakeHit(float dmg, int attacker, int type, uint32_t extra, HitSource* src);   // 00bfcdd0
    void AddStun(int ms);                                // 00bfc640
    void Hit(float dmg, int attacker, int type, uint32_t extra, HitSource* src);       // 00bd0510
};

// @ 0x00bd0510
void Combatant::Hit(float dmg, int attacker, int type, uint32_t extra, HitSource* src)
{
    Creature* self = (Creature*)((char*)this - 0x588);
    if (self->IsDead())
        return;
    if (type == 0xb || type == 0xe) {
        AddStun(RoundF(dmg * 1000.0f));
        return;
    }
    if (src && src->Cast(0x436f315))
        return;

    bool countable = type != 0xc && type != 0xa && type != 0x10 && type != 4 && type != 0xf;

    if (GetCurrentGameMode() == 0x1654c05) {
        void* u = FUN_00ae3370(src);
        if (u && *(int*)((char*)u + 0x714) == 3)
            attacker = GetPlayerEmpireID();
        if (countable) {
            void* inv = GetUFOSimulator()->GetPlayerInventory();
            Inventory* pi = inv ? (Inventory*)((char*)inv + 0x508) : 0;
            if ((void*)src == (void*)pi) {
                int o = self->GetOwnerEmpire();
                if (o != GetPlayerEmpireID())
                    GetUFOSimulator()->Func_ffd830(mpParent);
            }
        }
    }
    if (countable) {
        if (attacker == GetPlayerEmpireID())
            mpParent->Func_bdbf10();
        OnHitSource(src);
        FlagTarget* ft = self->GetFlagTarget();
        if (ft)
            ft->SetFlag8e();
        if (attacker != -1 && GetCurrentGameMode() == 0x1654c04 && dmg > 0.0f &&
            self->GetOwnerEmpire() != attacker) {
            GetRelationshipManager()->RecordFoughtEnemyEvent(self->GetOwnerEmpire(), attacker, 0x526e501, 1.0f);
            if (attacker == GetNounManager()->GetPlayerEmpireOrMinus1()) {
                bool skip = false;
                if (mStunTimer.IsRunning() && mStunTimer.GetElapsedTime() <= 5000)
                    skip = true;
                if (!skip) {
                    cSpatial* sp = (cSpatial*)((char*)this - 0x554);
                    if (sp->IsVisible()) {
                        AutoRefCount<cIVisualEffect> fx;
                        if (GetEffectsManager()->CreateEffect(0x69a49c25, 0, fx.AsPPTypeParam())) {
                            XformMsg msg;
                            float h = sp->GetBounds()->maxz + 2.0f;
                            Vec3 tmp;
                            Vec3* n = normalized_safe(&tmp, sp->GetPosition());
                            float ox = n->x * h, oy = n->y * h, oz = n->z * h;
                            Vec3* p = sp->GetPosition();
                            Vec3 np(p->x + ox, p->y + oy, p->z + oz);
                            msg.flags |= 4;
                            msg.count += 1;
                            msg.pos = *(RawVec3*)&np;
                            Vec3 fwd;
                            Mat3 mt;
                            msg.rot = *Matrix3FromFacingAndUp(&mt, sp->GetFacing(&fwd), sp->GetPosition());
                            msg.flags |= 2;
                            msg.count += 2;
                            msg.scale = 4.0f;
                            fx.mp->Apply(&msg);
                            fx.mp->Func8(0);
                        }
                        mStunTimer.Restart();
                    }
                }
            }
        }
    }

    int before = GetDamageState();
    TakeHit(dmg, attacker, type, extra, src);
    bool killed = false;
    if (GetDamageState() == 2 && before != 2) {
        killed = true;
        Vec3 fwd;
        cSpatial* sp = (cSpatial*)((char*)this - 0x554);
        SoundMgr* sm = GetSoundMgr();
        sm->Play(0x4c9bc66, sp->GetPosition(), sp->GetFacing(&fwd));
        mpParent->mTimer6e8.Restart();
        mpParent->ClearAggro();
        if (GetCurrentGameMode() == 0x1654c04) {
            mTimerD8.Restart();
            sp->SetTarget((const Vec3*)mpParent->Get6c()->GetData());
        } else {
            mpParent->Func_be2070(self, 0);
        }
    }

    cSpatial* sp = (cSpatial*)((char*)this - 0x554);
    if (!sp->IsVisible())
        return;
    int lo, hi;
    if (killed) {
        lo = 2; hi = 5;
    } else {
        if (type != 0) return;
        if (0.33f <= RandomRange(1.0f)) return;
        lo = 1; hi = 2;
    }
    BBox* b = sp->GetBounds();
    float dx = b->maxx - b->minx;
    float dy = b->maxy - b->miny;
    float dz = b->maxz - b->minz;
    BBox* b2 = sp->GetBounds();
    float rx = RandomRange(1.0f) * dx + b2->minx;
    BBox* b3 = sp->GetBounds();
    float ry = RandomRange(1.0f) * dy + b3->miny;
    float rz = RandomRange(1.0f) * dz;
    Vec3 q = *sp->GetPosition();
    Vec3 tmp;
    Vec3* n = normalized_safe(&tmp, &q);
    Vec3 pos(rx * n->x + q.x, q.y + n->y * ry, q.z + n->z * rz);
    Spawner* spw = GetSpawnMgr()->mpSpawner;
    spw->Spawn(lo, hi, self->GetOwnerEmpire(), pos, g168b66c);
}
