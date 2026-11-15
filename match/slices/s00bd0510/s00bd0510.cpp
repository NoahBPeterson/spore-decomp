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

// ============================================================================
// Simulator building class family: the shared cBuilding destructor body, the
// cBuildingCityHall / cBuildingHouse destructors, and their helpers.
// ============================================================================
namespace SP_BLD {

typedef unsigned char  u8b;
typedef unsigned short u16b;
typedef unsigned int   u32b;

// A 0x20-byte cGonzagoTimer (POD, constructed / destroyed by its ctor / dtor).
struct Timer { u32b mData[8]; };

// eastl::basic_string<wchar_t> as stored inside a building (16 bytes).
struct WString16 {
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    void*    mpPool;       // +0x0c
};

// The growable coordinate array kept at +0x1f8 (11 dwords = 0x2c bytes).
struct CoordArray {
    u32b  mInline[6];      // +0x00 .. +0x17
    u32b* mpCurrent;       // +0x18
    u32b* mpUnused1c;      // +0x1c
    u32b* mpCapacity;      // +0x20
    u32b* mpUnused24;      // +0x24
    u32b* mpUnused28;      // +0x28
};

// rw::math::fpu::Matrix33 (nine floats).
struct Matrix3f { float m[9]; };

// Non-primary base subobject view: only the vtable pointer matters here.
struct VtblView { void* mpVtbl; };   // +0x00

// ---------------------------------------------------------------------------
// cBuilding: one flat layout covering the six base subobjects and the tail.
// (Same offsets as the cBuilding in slice s00bd1820.)
// ---------------------------------------------------------------------------
struct cBuilding {
    void* mpVtbl0;           // +0x000  cBuilding vtable
    void* mpVtbl1;           // +0x004  DefaultRefCounted half vtable
    char  mData08[0x34 - 0x08];      // +0x008 .. +0x033
    void* mpVtblSpatial;     // +0x034  cSpatialObject subobject vtable
    char  mData38[0x108 - 0x38];     // +0x038 .. +0x107
    void* mpVtblInteraction; // +0x108  cInteractionTarget subobject vtable
    char  mData10c[0x120 - 0x10c];   // +0x10c .. +0x11f
    void* mpVtblCombatant;   // +0x120  cCombatant subobject vtable
    char  mData124[0x1e8 - 0x124];   // +0x124 .. +0x1e7
    void* mpVtblPlaceable;   // +0x1e8  cPlaceableStructure subobject vtable
    u32b  mF1ec;             // +0x1ec
    u32b  mF1f0;             // +0x1f0
    u8b   mF1f4;             // +0x1f4
    char  mF1f5[3];          // +0x1f5 .. +0x1f7
    CoordArray mCoords;      // +0x1f8
    u32b  mF224;             // +0x224
    u32b  mF228;             // +0x228
    u32b  mF22c;             // +0x22c
    u8b   mF230;             // +0x230
    char  mF231[0x238 - 0x231];      // +0x231 .. +0x237
    Timer mTimer1;           // +0x238
    Timer mTimer2;           // +0x258
    WString16 mName;         // +0x278 (begin / end / capacity / pool)
    u8b   mF288;             // +0x288
    u8b   mF289;             // +0x289
    char  mF28a[2];          // +0x28a .. +0x28b
    u32b  mF28c;             // +0x28c
    u32b  mF290;             // +0x290
    u32b  mF294;             // +0x294
    u32b  mF298;             // +0x298
    u32b  mF29c;             // +0x29c
    u32b  mF2a0;             // +0x2a0  array allocation (refcount at -4)
    u32b  mF2a4;             // +0x2a4
    u32b  mF2a8;             // +0x2a8
    char  mF2ac[8];          // +0x2ac .. +0x2b3
    u32b  mF2b4;             // +0x2b4  array allocation
    u32b  mF2b8;             // +0x2b8
    u32b  mF2bc;             // +0x2bc
    char  mF2c0[8];          // +0x2c0 .. +0x2c7
    u32b  mF2c8;             // +0x2c8  array allocation
    u32b  mF2cc;             // +0x2cc
    u32b  mF2d0;             // +0x2d0
    char  mF2d4[8];          // +0x2d4 .. +0x2db
    u32b  mF2dc;             // +0x2dc  array allocation
    u32b  mF2e0;             // +0x2e0
    u32b  mF2e4;             // +0x2e4
    char  mF2e8[8];          // +0x2e8 .. +0x2ef
    u8b   mF2f0;             // +0x2f0
    char  mF2f1[3];          // +0x2f1 .. +0x2f3
    u32b  mF2f4;             // +0x2f4  array allocation
    u32b  mF2f8;             // +0x2f8
    u32b  mF2fc;             // +0x2fc
    char  mF300[8];          // +0x300 .. +0x307
    u32b  mF308;             // +0x308  array allocation
    u32b  mF30c;             // +0x30c
    u32b  mF310;             // +0x310
    char  mF314[0x320 - 0x314];      // +0x314 .. +0x31f
    Timer mTimer3;           // +0x320
    u8b   mF340;             // +0x340
    char  mF341[0x344 - 0x341];      // +0x341 .. +0x343
    char  mTail344[8];       // +0x344
    char  mF34c[0x358 - 0x34c];      // +0x34c .. +0x357
    Timer mTimerHit;         // +0x358
    char  mF378[0x388 - 0x378];      // +0x378 .. +0x387
    u16b  mF388;             // +0x388
    u16b  mF38a;             // +0x38a
    float mF38c;             // +0x38c
    float mF390;             // +0x390
    float mF394;             // +0x394
    float mF398;             // +0x398
    Matrix3f mMatrix;        // +0x39c
    char  mF3c0[0x3d8 - 0x3c0];      // +0x3c0 .. +0x3d7
    u32b  mF3d8;             // +0x3d8  pointer whose -4 dword is a refcount

    void Dtor();             // 0x00bd0dd0  ~cBuilding body
};

// Derived buildings share the flat layout; only the vtable pointers differ.
struct cBuildingCityHall : cBuilding {
    void Dtor();             // 0x00bd1100  ~cBuildingCityHall body
};
struct cBuildingHouse : cBuilding {
    void* Delete(u8b flags); // 0x00bd1450  scalar deleting destructor
};

// vtable storage placeholders (relocation-masked by chk).
extern char cBuilding_vtable0[];              // 0x014670b8
extern char cBuilding_vtable1[];              // 0x014670a4
extern char cBuilding_vtable2[];              // 0x01466fe0
extern char cBuilding_vtable3[];              // 0x01466fc0
extern char cBuilding_vtable4[];              // 0x01466f58
extern char cBuilding_vtable5[];              // 0x01466f30
extern char cPlaceableStructure_baseVtable[]; // 0x01466c14
extern char cBuildingCityHall_vtable0[];      // 0x014672f0
extern char cBuildingCityHall_vtable1[];      // 0x014672dc
extern char cBuildingCityHall_vtable2[];      // 0x01467218
extern char cBuildingCityHall_vtable3[];      // 0x014671f8
extern char cBuildingCityHall_vtable4[];      // 0x01467190
extern char cBuildingCityHall_vtable5[];      // 0x01467168
extern char cBuildingHouse_vtable0[];         // 0x01467768
extern char cBuildingHouse_vtable1[];         // 0x01467754
extern char cBuildingHouse_vtable2[];         // 0x01467690
extern char cBuildingHouse_vtable3[];         // 0x01467670
extern char cBuildingHouse_vtable4[];         // 0x01467608
extern char cBuildingHouse_vtable5[];         // 0x014675e0

// Destructor / sub-destructor helpers.
void dtor_cGonzagoTimer(void* p);                 // 0x00b638b0
void Func_004aa120(void* p);                      // 0x004aa120  deque<T>::~deque
void dtor_cCombatant(void* p);                    // 0x00bfcd00
void dtor_cInteractionTarget(void* p);            // 0x00ac0520
void dtor_cSpatialObject(void* p);                // 0x00c8a420
void dtor_cGameData(void* p);                     // 0x00b184c0
void operator_delete__(void* p);                  // 0x00f47380
void Func_00bcddc0(void* p);                      // 0x00bcddc0  cGameData::RemoveOwner

// Release an array allocation whose count is stored in its preceding dword.
static void FreeArray(void* p)
{
    if (p != 0 && ((int*)p)[-1] != 0)
        operator_delete__(p);
}

// @ 0x00bd0dd0
// Simulator::cBuilding::~cBuilding (blanket destructor body).
void cBuilding::Dtor()
{
    cBuilding* self = this;
    self->mpVtbl0 = (void*)&cBuilding_vtable0;
    self->mpVtbl1 = (void*)&cBuilding_vtable1;
    self->mpVtblSpatial = (void*)&cBuilding_vtable2;
    self->mpVtblInteraction = (void*)&cBuilding_vtable3;
    self->mpVtblCombatant = (void*)&cBuilding_vtable4;
    self->mpVtblPlaceable = (void*)&cBuilding_vtable5;

    dtor_cGonzagoTimer(&self->mTimer3);

    FreeArray((void*)self->mF308);
    FreeArray((void*)self->mF2f4);
    FreeArray((void*)self->mF2dc);
    FreeArray((void*)self->mF2c8);
    FreeArray((void*)self->mF2b4);
    FreeArray((void*)self->mF2a0);

    {
        wchar_t* pBegin = self->mName.mpBegin;
        int nBytes = (int)((char*)self->mName.mpCapacity - (char*)pBegin);
        if ((nBytes & ~1) > 2 && pBegin != 0)
            operator_delete__(pBegin);
    }

    dtor_cGonzagoTimer(&self->mTimer2);
    dtor_cGonzagoTimer(&self->mTimer1);
    Func_004aa120(&self->mCoords);

    if (self->mF1f0 != 0) {
        void* p = (void*)self->mF1f0;
        (*(void (__thiscall**)(void*))(*(void***)p)[1])(p);
    }
    if (self->mF1ec != 0) {
        void* p = (void*)self->mF1ec;
        (*(void (__thiscall**)(void*))(*(void***)p)[1])(p);
    }

    self->mpVtblPlaceable = (void*)&cPlaceableStructure_baseVtable;
    dtor_cCombatant(&self->mpVtblCombatant);
    dtor_cInteractionTarget(&self->mpVtblInteraction);
    dtor_cSpatialObject(&self->mpVtblSpatial);
    dtor_cGameData(self);
}

// @ 0x00bd1100
// Simulator::cBuildingCityHall::~cBuildingCityHall (blanket destructor body).
void cBuildingCityHall::Dtor()
{
    cBuildingCityHall* self = this;
    self->mpVtbl0 = (void*)&cBuildingCityHall_vtable0;
    self->mpVtbl1 = (void*)&cBuildingCityHall_vtable1;
    self->mpVtblSpatial = (void*)&cBuildingCityHall_vtable2;
    self->mpVtblInteraction = (void*)&cBuildingCityHall_vtable3;
    self->mpVtblCombatant = (void*)&cBuildingCityHall_vtable4;
    self->mpVtblPlaceable = (void*)&cBuildingCityHall_vtable5;

    Func_00bcddc0(self);

    dtor_cGonzagoTimer(&self->mTimerHit);

    if (self->mTail344 != 0) {
        void* p = self->mTail344;
        (*(void (__thiscall**)(void*))(*(void***)p)[1])(p);
    }

    cBuilding* self2 = this;
    self2->Dtor();
}

// @ 0x00bd1450
// Simulator::cBuildingHouse scalar deleting destructor.
void* cBuildingHouse::Delete(u8b flags)
{
    cBuildingHouse* self = this;
    self->mpVtbl0 = (void*)&cBuildingHouse_vtable0;    self->mpVtbl1 = (void*)&cBuildingHouse_vtable1;
    self->mpVtblSpatial = (void*)&cBuildingHouse_vtable2;
    self->mpVtblInteraction = (void*)&cBuildingHouse_vtable3;
    self->mpVtblCombatant = (void*)&cBuildingHouse_vtable4;
    self->mpVtblPlaceable = (void*)&cBuildingHouse_vtable5;

    cBuildingHouse* base = self;
    base->Dtor();

    if ((flags & 1) != 0)
        operator_delete__(self);
    return self;
}

// ============================================================================
// cPropertyInfo<float>: a live property binding (value + owning property list).
// ============================================================================
struct PropertyList;   // SP::cPropertyList

// vtable view of a property list: only the GetPropertyOwner slot at +0x2c is used.
struct PropertyListVtbl {
    char mSlots00[0x2c];
    bool (__thiscall* GetPropertyOwner)(void* pSelf, int a, PropertyList** pOut);  // +0x2c
};

struct PropertyInfoF {
    float   mValue;        // +0x00  the property value
    void*   mpObject;      // +0x04  AutoRefCount<SP::cPropertyList>::mpObject
    uint32_t mPropertyID;  // +0x08
    uint32_t mModCount;    // +0x0c

    PropertyInfoF* Ctor(void* pOwner, uint32_t id, float value);  // 0x00bd0ce0
    void Set(PropertyList* pList);                                // 0x0075e6d0
};

struct PropertyManagerObj {
    char mSlots00[0x2c];
    bool (__thiscall* GetPropertyOwner2)(void* pSelf, int a, int b, PropertyList** pOut);  // +0x2c
};

void* SP_PropertyManager();                                   // 0x0067de30

// @ 0x00bd0ce0
// SP::cPropertyInfo<float>::cPropertyInfo - bind the value to a named property.
PropertyInfoF* PropertyInfoF::Ctor(void* pOwner, uint32_t id, float value)
{
    mValue = value;
    mpObject = 0;
    mPropertyID = id;
    mModCount = 0;

    PropertyManagerObj* mgr = (PropertyManagerObj*)SP_PropertyManager();
    if (mpObject != 0) {
        void* p = mpObject;
        mpObject = 0;
        (*(void (__thiscall**)(void*))(*(void***)p)[1])(p);
    }
    if (((bool (__thiscall*)(void*, void*, int, PropertyList**))
         (*(void***)mgr)[0x2c / 4])(mgr, pOwner, 0, (PropertyList**)&mpObject))
        Set(*(PropertyList**)&mpObject);
    return this;
}

// ============================================================================
// eastl::vector<SP::cStarRecord_*> / deque helpers used by the building save code.
// The storage is a begin/end pair of element pointers at +0x18 / +0x20.
// ============================================================================
typedef unsigned int cStarRecordPtr;   // a cStarRecord_* slot, held as a word

struct StarRecordVec {
    char     mData00[0x18];     // +0x00 .. +0x17
    cStarRecordPtr* mpBegin;    // +0x18
    cStarRecordPtr* mpCapacity; // +0x1c
    cStarRecordPtr* mpEnd;      // +0x20
    void Clear();                                   // 0x00996460 (deque clear)
    cStarRecordPtr* PushBack(const cStarRecordPtr& value);   // 0x00502dd0
};

// An eastl::deque<T, allocator, 64> view: two 12-byte iterators (begin at +0x08,
// end at +0x14) followed by the node map {begin, end, capacity} at +0x20.
struct Deque64 {
    char mData00[0x08];
    cStarRecordPtr* mBeginCurrent;   // +0x08
    cStarRecordPtr** mBeginNode;     // +0x0c
    cStarRecordPtr* mBeginNodeEnd;   // +0x10
    cStarRecordPtr* mEndCurrent;     // +0x14
    cStarRecordPtr** mEndNode;       // +0x18
    cStarRecordPtr* mEndNodeEnd;     // +0x1c
    cStarRecordPtr** mMapBegin;      // +0x20
    cStarRecordPtr** mMapEnd;        // +0x24
    cStarRecordPtr** mMapCapacity;   // +0x28
};

// A byte-stream writer/reader view (EA::IO); the object's vtable provides the
// GetWriter (+0x20) / GetReader (+0x20) accessors and the Read/Write slots.
struct IOSerial {
    void* mpVtbl;   // +0x00
};

// eastl::basic_string<char> (16 bytes).
struct Str8 {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    void* mpPool;       // +0x0c
    Str8& assign(const char* pFirst, const char* pLast);   // 0x00454cb0
};

// The lazy-initialised three-dword singleton at 0x0168b64c.
extern unsigned int gSingletonFlag;     // 0x0168b660 (byte flag)
extern unsigned int gSingleton[3];      // 0x0168b64c
extern "C" void Fn_013c3180();          // 0x013c3180 (atexit handler)
extern "C" int __cdecl atexit(void (__cdecl*)());

// The property name table (built once, using Str8::assign).
extern const char gBuildingNameStr[];   // 0x0146715c "Building"
extern const char gBuildingNameStrEnd[]; // 0x01467164

// Globals used by the turret-weapon configuration.
extern void* gAppNameTag;               // 0x01654c05 (compared value)
extern float gTurretHealthDefault;      // 0x013ec5b4
extern char  gTurretWeaponA[];          // 0x057e291e
extern char  gTurretWeaponB[];          // 0x057e2933
extern char  gTurretWeaponC[];          // 0x057e293d
char gTurretWeaponA[21] = "space_turret_weaponA";  // placeholder name, VA is authoritative
char gTurretWeaponB[16] = "space_turret_b";
char gTurretWeaponC[16] = "space_turret_c";

void* GetCurrentGameMode();                              // 0x00b5b800
void  StarManager(void* pEmpireId);                      // 0x00b3d2a0
void* GetEmpireByID(void* pEmpireId);                    // 0x00ba9370
struct cSPSpaceCombatTuning;
cSPSpaceCombatTuning* GetSpaceCombatTuning(void* pTuning); // 0x01029940
bool  FUN_0075e620(void* pProp);                         // 0x0075e620
PropertyInfoF* FUN_00bd0ce0(void* a, uint32_t id, float v); // 0x00bd0ce0
void  enableWeapon(char* pName, void* pTuning, void* pOut); // 0x00c3a220

// A ref-counted object accessor used by the property getters.
struct PropObject {
    void* mpVtbl;       // +0x00
};

// The two-argument property-getter trampolines.
struct PropBinder {
    void* mpVtbl;       // +0x00
};

// The deque<...,64> at +0x200 of the building: begin/end iterators plus the
// node-map walker and the currently-owned node block.
struct StarRecordDequeOwner {
    char  mData00[0x200];
    cStarRecordPtr*  mpCurrent;   // +0x200  iterator current
    cStarRecordPtr*  mpNodeBase;  // +0x204  allocation of the current node
    cStarRecordPtr*  mpNodeEnd;   // +0x208  end of the current node
    char  mData20c[4];            // +0x20c
    cStarRecordPtr** mpNodeMap;   // +0x210  node-map cursor (end marker)
    cStarRecordPtr*  mpEnd;       // end-of-deque iterator (compared against)
};

// The turret-owning building subobject (cBuildingHouse tail region).
struct TurretOwner {
    char  mData00[0x5b4];
    float mF5b4;                  // +0x5b4  turret health
    char  mF5b8[0x5c0 - 0x5b8];
    float mF5c0;                  // +0x5c0  turret health (mirror)
    char  mF5c4[0x688 - 0x5c4];
    void* mF688;                  // +0x688  owning empire object
    char  mF68c[0x694 - 0x68c];
    char  mF694;                  // +0x694  weapon-enable slot C
    char  mF695[0x698 - 0x695];
    char  mF698;                  // +0x698  weapon-enable slot A
    char  mF699[0x69c - 0x699];
    char  mF69c;                  // +0x69c  weapon-enable slot B
    char  mF69d[0x6a8 - 0x69d];
    void* mpTurretTuning;         // +0x6a8

    void ConfigureTurretWeapons(void* pTuning);   // 0x00bd15a0
};

// Space-combat tuning object (turret health source).
struct cSPSpaceCombatTuning {
    float GetTurretHealth();      // 0x0102a780
};

// @ 0x00bd0ce0 repeated note: done above.

// @ 0x00bd1060
// Assign the literal "Building" to a byte string.
void __stdcall SetBuildingName(Str8* pStr)
{
    pStr->assign(gBuildingNameStr, gBuildingNameStrEnd);
}

// @ 0x00bd1690
// Lazy initialiser returning the three-dword singleton.
unsigned int* __cdecl GetBuildingSingleton()
{
    if ((gSingletonFlag & 1) == 0) {
        gSingletonFlag |= 1;
        gSingleton[0] = 0;
        gSingleton[1] = 0;
        gSingleton[2] = 0;
        atexit(Fn_013c3180);
    }
    return gSingleton;
}

// @ 0x00bd1780
// Trampoline: query a nested object's +0xc vtable slot, then bind it via arg1.
bool __cdecl PropGetA(PropBinder* pBinder, PropObject** ppObj)
{
    unsigned int value = 0;
    if (*ppObj != 0) {
        void* p = (char*)*ppObj + 0xc;
        value = ((unsigned int (__thiscall*)(void*, unsigned int))
                 (*(void***)p)[0xc / 4])(p, 0x179c807);
    }
    ((void (__thiscall*)(void*, unsigned int))
     (*(void***)pBinder)[0x2c / 4])(pBinder, value);
    return true;
}

// @ 0x00bd17b0
// Trampoline: query a nested object's +0x5c vtable slot, then bind it via arg1.
bool __cdecl PropGetB(PropBinder* pBinder, PropObject** ppObj)
{
    unsigned int value = 0;
    if (*ppObj != 0) {
        value = ((unsigned int (__thiscall*)(void*, unsigned int))
                 (*(void***)*ppObj)[0x5c / 4])(*ppObj, 0x179c807);
    }
    ((void (__thiscall*)(void*, unsigned int))
     (*(void***)pBinder)[0x2c / 4])(pBinder, value);
    return true;
}

// ---------------------------------------------------------------------------
// The save/load helpers operate on the deque of cStarRecord_* held by the
// cBuilding tail.  The object layout is the eastl deque<...,64> view below.
// ---------------------------------------------------------------------------

// The save writer passed to the stream owner: vtable +0x20 returns the byte
// writer, +0x1c flushes, +0x18 returns the underlying IO stream.
struct SaveWriter {
    void* mpVtbl;   // +0x00
};

// The IO object returned by the writer's +0x18 slot (a raw byte stream).
struct ByteStream {
    void* mpVtbl;   // +0x00
};

extern "C" void EA_IO_WriteUint32(void* pStream, const void* pValue,
                                  int nCount, int a4);        // 0x0093aa70
extern "C" void EA_IO_ReadInt32(void* pStream, void* pOut,
                                int nCount, int a4);          // 0x0093a780
void deque7027PushBack(Deque64* pDeque, cStarRecordPtr* pValue);  // 0x00502dd0
void deque7027Clear(Deque64* pDeque);                         // 0x00996460

// Total element count of the deque<...,64> (the (nodes-1)*64 + partial sums).
static int Deque64Size(Deque64* pDeque)
{
    int nHeadSlots = (int)((char*)pDeque->mBeginNodeEnd - (char*)pDeque->mBeginCurrent) >> 2;
    int nTailNodes = ((int)((char*)pDeque->mMapEnd - (char*)pDeque->mEndCurrent) >> 2) - 1;
    int nMidSlots = (int)((char*)pDeque->mEndNode - (char*)pDeque->mBeginNode) >> 2;
    return nTailNodes * 64 + nHeadSlots + nMidSlots;
}

// @ 0x00bd0bb0
// Write the deque of cStarRecord_* to the save stream (count then elements).
void __fastcall WriteStarRecordDeque(SaveWriter* pWriter, void* /*edx*/,
                                     Deque64* pDeque)
{
    int nCount = Deque64Size(pDeque);

    ByteStream* (__thiscall* getWriter)(void*) =
        (ByteStream* (__thiscall*)(void*))(*(void***)pWriter)[0x20 / 4];
    ByteStream* pStream = getWriter(pWriter);
    void* pRaw = ((void* (__thiscall*)(ByteStream*))
                  (*(void***)pStream)[0x18 / 4])(pStream);
    EA_IO_WriteUint32(pRaw, &nCount, 1, 0);

    cStarRecordPtr* pCur = pDeque->mBeginCurrent;
    cStarRecordPtr** pNode = pDeque->mBeginNode;
    cStarRecordPtr* pNodeEnd = pDeque->mBeginNodeEnd;
    cStarRecordPtr* pEnd = pDeque->mEndCurrent;

    while (pCur != pEnd) {
        ByteStream* pStream2 = getWriter(pWriter);
        void* pRaw2 = ((void* (__thiscall*)(ByteStream*))
                       (*(void***)pStream2)[0x18 / 4])(pStream2);
        cStarRecordPtr value = *pCur;
        EA_IO_WriteUint32(pRaw2, &value, 1, 0);

        ++pCur;
        if (pCur == pNodeEnd) {
            pCur = (cStarRecordPtr*)pNode[1];
            ++pNode;
            pNodeEnd = pCur + 64;
        }
    }

    ((void (__thiscall*)(SaveWriter*))
     (*(void***)pWriter)[0x1c / 4])(pWriter);
}

// @ 0x00bd0c80
// Walk the deque<...,64> iterator (no-op body) and report success.
bool __fastcall IsStarRecordDequeEmpty(void* /*ecx*/, void* /*edx*/,
                                       Deque64* pDeque)
{
    cStarRecordPtr* pCur = pDeque->mBeginCurrent;
    cStarRecordPtr** pNode = pDeque->mBeginNode;
    cStarRecordPtr* pNodeEnd = pDeque->mBeginNodeEnd;

    while (pCur != pDeque->mEndCurrent) {
        ++pCur;
        if (pCur == pNodeEnd) {
            pCur = (cStarRecordPtr*)pNode[1];
            ++pNode;
            pNodeEnd = pCur + 64;
        }
    }
    return true;
}

// @ 0x00bd1080
// Pop the front element of the deque<...,64> at +0x200 of the object, freeing
// the old node block when the iterator has run off the end of the node.
cStarRecordPtr __fastcall PopStarRecord(StarRecordDequeOwner* self)
{
    cStarRecordPtr* pCur = self->mpCurrent;
    if (pCur == self->mpEnd)
        return 0;

    cStarRecordPtr value = *pCur;
    if (pCur + 1 != self->mpNodeEnd) {
        self->mpCurrent = pCur + 1;
        return value;
    }

    if (self->mpNodeBase != 0)
        operator_delete__(self->mpNodeBase);

    cStarRecordPtr** pNode = self->mpNodeMap;
    ++pNode;
    self->mpNodeMap = pNode;
    cStarRecordPtr* pNodeBase = *pNode;
    self->mpNodeBase = pNodeBase;
    self->mpNodeEnd = pNodeBase + 64;
    self->mpCurrent = self->mpNodeBase;
    return value;
}

// @ 0x00bd15a0
// Configure the space-stage turret weapons of this building and pick the turret
// health for the given tuning parameter.
void TurretOwner::ConfigureTurretWeapons(void* pTuning)
{
    bool bOwnsTemp = false;
    PropertyInfoF* pTemp = 0;

    mpTurretTuning = pTuning;
    enableWeapon(gTurretWeaponA, pTuning, &mF698);
    enableWeapon(gTurretWeaponB, pTuning, &mF69c);
    enableWeapon(gTurretWeaponC, pTuning, &mF694);

    float value;
    if (GetCurrentGameMode() == gAppNameTag) {
        void* pEmpireId = ((void* (__thiscall*)(void*))
                           (*(void***)mF688)[0x4c / 4])(mF688);
        StarManager(pEmpireId);
        if (GetEmpireByID(pEmpireId) != 0) {
            cSPSpaceCombatTuning* pTune = GetSpaceCombatTuning(pTuning);
            value = pTune->GetTurretHealth();
            goto store;
        }
    }

    bOwnsTemp = true;
    pTemp = FUN_00bd0ce0((void*)0xa4c2f6bd, 0xc5291fee, gTurretHealthDefault);
    FUN_0075e620((void*)pTemp);
    value = pTemp->mValue;

store:
    mF5b4 = value;
    mF5c0 = value;
    if (bOwnsTemp && pTemp != 0) {
        void* pObj = pTemp->mpObject;
        if (pObj != 0)
            (*(void (__thiscall**)(void*))(*(void***)pObj)[1])(pObj);
    }
}

// @ 0x00bd16d0
// Read the deque of cStarRecord_* out of the save stream (clear, count, then
// elements pushed back through the deque grow helper).
void __fastcall ReadStarRecordDeque(SaveWriter* pWriter, void* /*edx*/,
                                    Deque64* pDeque)
{
    deque7027Clear(pDeque);

    unsigned int nCount = 0;
    ByteStream* pStream = ((ByteStream* (__thiscall*)(void*))
                           (*(void***)pWriter)[0x20 / 4])(pWriter);
    void* pRaw = ((void* (__thiscall*)(ByteStream*))
                  (*(void***)pStream)[0x18 / 4])(pStream);
    EA_IO_ReadInt32(pRaw, &nCount, 1, 0);

    for (unsigned int i = 0; i < nCount; ++i) {
        ByteStream* pStream2 = ((ByteStream* (__thiscall*)(void*))
                                (*(void***)pWriter)[0x20 / 4])(pWriter);
        void* pRaw2 = ((void* (__thiscall*)(ByteStream*))
                       (*(void***)pStream2)[0x18 / 4])(pStream2);
        cStarRecordPtr value = 0;
        EA_IO_ReadInt32(pRaw2, &value, 1, 0);

        cStarRecordPtr* pCur = pDeque->mEndCurrent;
        cStarRecordPtr* pNext = pCur + 1;
        if (pNext != pDeque->mEndNodeEnd) {
            pDeque->mEndCurrent = pNext;
            if (pCur != 0)
                *pCur = value;
        } else {
            deque7027PushBack(pDeque, &value);
        }
    }

    ((void (__thiscall*)(SaveWriter*))
     (*(void***)pWriter)[0x1c / 4])(pWriter);
}

}  // namespace SP_BLD

