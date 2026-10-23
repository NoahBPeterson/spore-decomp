// Slice s00dc67d0: SP::VehicleTree opportunity-target behaviour-tree nodes and vehicle helpers.
//   DefendCityOrder_Tick / GetBestOpportunityTarget / IsOpportunityTarget drive the "defend the city"
//   behavior of a vehicle, plus the node create/destroy thunks and a few vehicle spot helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

#define PV(n) virtual void pad##n();
#define NOINLINE __declspec(noinline)
#define D(x) (*(int*)(((char*)this) + (x)))

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    float Length() const { return (float)sqrt(x * x + y * y + z * z); }
};

// ---------------------------------------------------------------------------------------------
// Common interfaces
// ---------------------------------------------------------------------------------------------

struct cSpatialObject {
    // slots: 0x00-0x28 (11 dwords), then GetPosition
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vector3& GetPosition();                          // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14)
    PV(15)
    virtual bool Vf58();                                           // +0x58
    // 0x5c..0xb4 must be 23 slots (0x16)
    PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d) PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24)
    PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c) PV(2d)
    virtual void* IsType(uint32_t typeID);                         // +0xb8
    virtual void Vbc();                                            // +0xbc
    virtual void Vc0();                                            // +0xc0
    virtual void Vc4(int a, float f);                              // +0xc4
    PV(32) PV(33) PV(34) PV(35) PV(36)
    virtual void Vdc(void* out);                                   // +0xdc
    PV(38)
    virtual void Ve4(const Vector3& v, float f);                   // +0xe4
    PV(3b)
    virtual void Vec();                                            // +0xec
};

struct cGameData {
    PV(00) PV(01)
    virtual cSpatialObject* GetSpatial();                          // +0x08
    PV(03)
    virtual uint32_t GetOwnerID();                                 // +0x10
    PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13)
    virtual void SetAttackTarget(cGameData* target);               // +0x50
    float GetRange();                                              // 0x00bfc400
};

// A noun with a type cast at +0x5c (the "interactable/entity" interface).
struct cInteractable {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f)
    PV(10) PV(11) PV(12)
    virtual uint32_t GetPoliticalID();                             // +0x4c
    PV(14) PV(15)
    virtual void* CastType(uint32_t typeID);                       // +0x5c
};

struct cGameDataObj {
    PV(00) PV(01) PV(02)
    virtual void* Cast(uint32_t typeID);                           // +0x0c
};

struct Info {
    cGameDataObj* mpObject;                                        // +0x00
    uint32_t dpad04[3];
};

struct cCulturalTarget {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsDestroyed();                                    // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a)
    PV(1b) PV(1c) PV(1d) PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(2a) PV(2b) PV(2c) PV(2d) PV(2e) PV(2f) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38)
    PV(39) PV(3a) PV(3b) PV(3c) PV(3d) PV(3e) PV(3f)
    char pad4[0x100 - 4];
    cSpatialObject mSpatial;                                       // +0x100
};

struct cCity {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsDestroyed();                                    // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a)
    PV(1b) PV(1c) PV(1d) PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(2a) PV(2b) PV(2c) PV(2d) PV(2e) PV(2f) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38)
    PV(39) PV(3a) PV(3b) PV(3c) PV(3d) PV(3e) PV(3f) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
    PV(48) PV(49) PV(4a) PV(4b) PV(4c) PV(4d) PV(4e) PV(4f) PV(50) PV(51) PV(52) PV(53)
    virtual const Vector3& GetPosition();                          // +0x2c
};

// cSpatialObject shim: cCity is not a cSpatialObject but exposes GetPosition at +0x2c.
struct cCitySpatial {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vector3& GetPosition();                          // +0x2c
};

struct cCulturalTargetSpatial {
    char pad[0x120];
    cCitySpatial mSpatial;                                         // +0x120
};

// ---------------------------------------------------------------------------------------------
// Vehicles
// ---------------------------------------------------------------------------------------------

struct EntityVector { void** mpBegin; void** mpEnd; };

struct cVehicleBase {
    virtual void AddRef();
    virtual void Release();
    PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f)
    PV(10) PV(11) PV(12)
    virtual uint32_t GetPoliticalID();                             // +0x4c
    uint32_t dpad04[(0x34 - 4) / 4];
    cSpatialObject mLoco;                                          // +0x34
};

// view of the object returned by cSpatialObject::IsType(0x137e8e0): a mover with a
// min/max radial band at +0x7c / +0x80 used by the pop-to-valid-spot scan.
struct cMoverLike {
    uint32_t pad00[(0x7c) / 4];
    float    m7c;                                                  // +0x7c
    float    m80;                                                  // +0x80
};

struct cVehicle : cVehicleBase {
    uint32_t pad38[(0x2a4 - 0x34 - sizeof(cSpatialObject)) / 4];
    uint8_t  mFlags2a4;                                            // +0x2a4
    uint32_t pad2a5[(0x508 - 0x2a4 - 1) / 4];
    cGameData mGameData;                                           // +0x508
    uint32_t pad50c[(0xaf0 - 0x508 - sizeof(cGameData)) / 4];
    int      mAf0;                                                 // +0xaf0
    uint32_t padAf4[(0xb1c - 0xaf0 - 4) / 4];
    int      mB1c;                                                 // +0xb1c
    int      mState;                                               // +0xb20
    uint32_t padB24[(0xb7c - 0xb20 - 4) / 4];
    void*    mB7c;                                                 // +0xb7c
    Vector3  mPos;                                                 // +0xb80
    uint32_t padB8c[(0xd04 - 0xb80 - sizeof(Vector3)) / 4];
    void*    mD04;                                                 // +0xd04

    EntityVector* GetHostiles();                                   // 0x00c9e860
    const Vector3& GetPosition();                                  // 0x00c9e880 -> +0xb80
    bool CanOccupyTerrain(const Vector3* pos);                     // 0x00c9e960
    void FUN_00c9ec40(int a);                                      // 0x00c9ec40
    cSpatialObject* GetTarget();                                   // 0x00c9fee0
    Info* FUN_00ca71d0();                                          // 0x00ca71d0
    void FUN_00ca7250(const char* msg);                            // 0x00ca7250
    void FUN_00caa900();                                           // 0x00caa900
    void FUN_00ca80e0(int id);                                     // 0x00ca80e0
    void FUN_00ca03a0(void* p);                                    // 0x00ca03a0
    void FUN_00ca33b0(void* p);                                    // 0x00ca33b0
    void FUN_00cabe70();                                           // 0x00cabe70
    void FUN_00c420d0(void* out);                                   // 0x00c420d0 (list at +0x278 from loco)
};

// object with a release/refcount slot at +0x60 / +0x64 used for the tree node's held object
struct cRefObj {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    virtual void AddRef();                                         // +0x60
    virtual void Release();                                        // +0x64
    // 0x68 .. 0xb8 -> 21 slots
    PV(1a) PV(1b) PV(1c) PV(1d) PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24)
    PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c) PV(2d) PV(2e)
    virtual void Vbc();                                            // +0xbc
    virtual void Vc0();                                            // +0xc0
};

struct cEntityBase {
    virtual void AddRef();
    PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07)
    virtual uint32_t GetTypeID();                                  // +0x20
};

// ---------------------------------------------------------------------------------------------
// Community / misc helpers
// ---------------------------------------------------------------------------------------------

struct cCommunity {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d) PV(1e) PV(1f)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c) PV(2d) PV(2e) PV(2f)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(3a) PV(3b) PV(3c) PV(3d) PV(3e) PV(3f)
    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(4a) PV(4b) PV(4c) PV(4d) PV(4e) PV(4f)
    PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(5a) PV(5b) PV(5c) PV(5d) PV(5e) PV(5f)
    PV(60) PV(61) PV(62) PV(63) PV(64) PV(65) PV(66) PV(67) PV(68) PV(69) PV(6a) PV(6b) PV(6c) PV(6d) PV(6e) PV(6f)
    PV(70) PV(71) PV(72) PV(73) PV(74) PV(75) PV(76) PV(77) PV(78)
    virtual void Release();                                        // +0x64 (heuristic - shared with cRefObj family)
    void* Front();                                                 // 0x00bfec10
    void  Deactivate();                                            // 0x00bfe4d0
    void  FUN_00bff290(void* v);                                   // 0x00bff290
};

struct cNounManager {
    void RemoveNoun(void* noun);                                   // 0x00b225d0
    void* GetEmpire(uint32_t id);                                  // 0x00b25f40
};
cNounManager* __cdecl NounManager();                               // 0x00b3d300

struct cRelationshipManager {
    int FUN_00d00a70(uint32_t a, uint32_t b, int c);               // 0x00d00a70
    bool FUN_00ae2e20(uint32_t a, uint32_t b);                     // 0x00ae2e20
};
cRelationshipManager* __cdecl SP_RelationshipManager();            // 0x00b3d2c0

struct cActionCircleSlot {                                         // 0x18 bytes
    uint32_t m0;
    uint32_t m4;
    uint32_t m8;
    Vector3  mPos;
};

struct cActionCircle {
    uint32_t pad0[0x50 / 4];
    cActionCircleSlot* mpBegin;                                    // +0x50
    cActionCircleSlot* mpEnd;                                      // +0x54
    void FUN_00afafd0();                                           // 0x00afafd0
};

struct cTicker {
    double RandomDoubleUniform();                                  // 0x009360d0
};
extern char g_1601760;                                             // 0x01601760

// ---------------------------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------------------------

extern Vector3 g_169fa68;                                          // 0x0169fa68 (Vector3)
extern char    g_1654c10;                                          // 0x01654c10 (game-mode object)
void* __cdecl SP_GetCurrentGameMode();                             // 0x00b5b800
void __cdecl operator delete(void*);                               // 0x00f47380
void Start3dSoundByName(void* name, void* sys, float x, float y, float z);   // 0x00571f80
void KillSetiEffects(void* space, void* a, void* sys);             // 0x00435ed0
void* __cdecl EA_Audio_GetSystemAT();                              // 0x00a206f0
int  __cdecl FUN_008e7f80(void* self);                             // 0x008e7f80 (GetDamageState)
int  __cdecl PlayIdleAnim(void* creature, int a, int b);           // 0x00bc96a0
void* __cdecl FUN_00c420d0(void* loco);                            // 0x00c420d0
void* __cdecl FUN_00dc6680(void* a, void* b, void* c);             // 0x00dc6680 (FindClosestVehicle)
void* __cdecl FUN_00afa070(cActionCircleSlot* slot, uint32_t id);  // 0x00afa070 (thiscall slot)

// virtual-slot invoker helper (avoids void* arithmetic in the call sites)
inline void* VCall1(void* obj, int slot)
{
    void** vt = *(void***)obj;
    return ((void* (__thiscall*)(void*))vt[slot / 4])(obj);
}
// call the virtual at byte-slot `slot` on `obj`, discarding the result.
inline void VCall0(void* obj, int slot)
{
    void** vt = *(void***)obj;
    ((void(__thiscall*)(void*))vt[slot / 4])(obj);
}
// fetch the function pointer for the virtual at byte-slot `slot`.
inline void* VFn(void* obj, int slot)
{
    void** vt = *(void***)obj;
    return vt[slot / 4];
}

// minimal refcounted interface: AddRef at +0x00, Release at +0x04.
struct cRefBase {
    virtual void AddRef();
    virtual void Release();
};

// vehicle-to-remove list
extern char* g_sVehiclesToRemoveBegin;                             // 0x016a0058
extern char* g_sVehiclesToRemoveEnd;                               // 0x016a005c

// ---------------------------------------------------------------------------------------------
// Declared callees
// ---------------------------------------------------------------------------------------------

bool IsValidFireTarget(cGameData* mine, cGameData* theirs);        // 0x00dc4e20
bool FUN_00bfcc40(void* self, uint32_t id);                        // 0x00bfcc40
bool FUN_00c0c0e0(void* self);                                     // 0x00c0c0e0
bool FUN_00bd3550(void* self, void* vehicle);                      // 0x00bd3550
bool FUN_00bda6a0(void* a, void* b);                               // 0x00bda6a0
void* FUN_00bd81a0(void* self);                                    // 0x00bd81a0
void* FUN_00cb45b0(void* target);                                  // 0x00cb45b0
void  FUN_00dc4d00(void* self, cSpatialObject* t);                 // 0x00dc4d00
void  FUN_00dc4610(void* self);                                    // 0x00dc4610
void* FUN_00bdca30(void* self, void* out, float a);                // 0x00bdca30
int   FUN_00cabe70(void* self);                                    // 0x00cabe70
void  FUN_00ca80e0(void* self, int id);                            // 0x00ca80e0
void  FUN_00c9ec40(void* self, int a);                             // 0x00c9ec40
void  FUN_00bff290(void* self, void* v);                           // 0x00bff290
void  FUN_00ca33b0(void* self, void* p);                           // 0x00ca33b0

// ---------------------------------------------------------------------------------------------
// Anonymous-namespace opportunity-target helpers
// ---------------------------------------------------------------------------------------------

// @ 0x00dc67d0
NOINLINE bool IsOpportunityTarget(cVehicle* self, void* target, void* cmp, bool flag3, bool flag4)
{
    if (!IsValidFireTarget(self ? &self->mGameData : 0, (cGameData*)target))
        return false;
    if (!target)
        return false;
    void* h = ((cInteractable*)target)->CastType(0x17f243b);
    if (!h)
        return false;
    uint32_t owner = self->mGameData.GetOwnerID();
    bool inv = FUN_00bfcc40(target, owner);
    void* e2 = ((cInteractable*)target)->CastType(0x137e8e0);
    void* best = h;
    if (e2) {
        if (flag3 && !inv)
            return false;
        if (cmp) {
            if (((cInteractable*)e2)->GetPoliticalID() != ((cInteractable*)cmp)->GetPoliticalID())
                return false;
        }
        uint32_t mine = ((cInteractable*)self)->GetPoliticalID();
        uint32_t theirs = ((cInteractable*)h)->GetPoliticalID();
        if (SP_RelationshipManager()->FUN_00d00a70(mine, theirs, 1) <= 1)
            return true;
        if (inv)
            return true;
    }
    void* h2 = ((cInteractable*)target)->CastType(0x436f315);
    if (h2) {
        if (self->mState == 1 && FUN_00bd3550(h2, self))
            return false;
        if (flag3 && !inv)
            return false;
        if (cmp) {
            if (((cInteractable*)h2)->GetPoliticalID() != ((cInteractable*)cmp)->GetPoliticalID())
                return false;
        }
        uint32_t mine = ((cInteractable*)self)->GetPoliticalID();
        uint32_t theirs = ((cInteractable*)h)->GetPoliticalID();
        if (SP_RelationshipManager()->FUN_00ae2e20(mine, theirs))
            return true;
        if (inv)
            return true;
    }
    void* t3 = ((cInteractable*)target)->CastType(0xce9f6639);
    if (t3 && FUN_00c0c0e0(t3)) {
        if (!flag4 && inv)
            return true;
    }
    return false;
}

// @ 0x00dc69a0
NOINLINE void* GetBestOpportunityTarget(cVehicle* self, void* a1, void* a2, void* a3, char a4)
{
    EntityVector* v = self->GetHostiles();
    for (void** it = v->mpBegin; it != v->mpEnd; ++it) {
        void* cur = *it;
        if (IsOpportunityTarget(self, cur, a1, (bool)a2, (bool)a3)) {
            if (!a4)
                return cur;
            bool ok = (*(bool(__thiscall**)(cGameData*, void*))VFn(&self->mGameData, 0x40))(
                          &self->mGameData, cur);
            if (ok)
                return cur;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// VehicleTree node entry points
// ---------------------------------------------------------------------------------------------

// @ 0x00dc6a20
void RemoveVehicles()
{
    while (g_sVehiclesToRemoveBegin != g_sVehiclesToRemoveEnd) {
        void* n = *(void**)(g_sVehiclesToRemoveEnd - 4);
        NounManager()->RemoveNoun(n);
        g_sVehiclesToRemoveEnd = g_sVehiclesToRemoveEnd - 4;
        void* p = *(void**)g_sVehiclesToRemoveEnd;
        if (p)
            ((cRefBase*)p)->Release();
    }
}

// @ 0x00dc6a70
bool DefendCityOrder_Tick(cVehicle* self, int, int, int, int, float* timer, cCity* defended, float delta)
{
    float t = *timer + delta;
    *timer = t;
    if (t <= 3.0f)
        return true;
    *timer = 0.0f;
    Info* info = self->FUN_00ca71d0();
    if (!info->mpObject)
        goto destroyed;
    {
        cGameDataObj* obj = info->mpObject;
        void* ord = obj->Cast(0xee9b2232);
        if (!ord)
            goto destroyed;
        if ((*(bool(__thiscall**)(void*))VFn(ord, 0x2c))(ord))
            goto destroyed;
        if (((cInteractable*)ord)->GetPoliticalID() != ((cInteractable*)self)->GetPoliticalID())
            goto destroyed;
        {
            void* list = FUN_00bd81a0(ord);
            void* v = FUN_00cb45b0(self->GetTarget());
            void* best = 0;
            if (v && IsValidFireTarget(&self->mGameData, (cGameData*)v) && FUN_00bda6a0(list, &v))
                best = v;
            const Vector3& mp = self->mLoco.GetPosition();
            float bestDist = 3.402823466e+38F;
            void** p = *(void***)list;
            void** end = ((void***)list)[1];
            for (; p != end; ++p) {
                void* cand = *p;
                if (IsOpportunityTarget(self, cand, 0, false, false)) {
                    cSpatialObject* sp = ((cGameData*)cand)->GetSpatial();
                    const Vector3& tp = sp->GetPosition();
                    float d = (mp - tp).Length();
                    if (d < bestDist) {
                        bestDist = d;
                        best = cand;
                    }
                }
            }
            FUN_00dc4d00(self, best ? ((cGameData*)best)->GetSpatial() : 0);
            self->mGameData.SetAttackTarget((cGameData*)best);
            if (self->GetTarget() != 0)
                return true;
            const Vector3& dp = ((cCitySpatial*)((char*)defended + 0x120))->GetPosition();
            const Vector3& sp2 = self->mLoco.GetPosition();
            if ((sp2 - dp).Length() <= *(float*)0x13f1f04)
                return true;
            Vector3 tmp;
            tmp.x = 1.0f;
            tmp.y = 0.0f;
            tmp.z = 0.0f;
            void* r = FUN_00bdca30(&tmp, &self->mLoco, (float)self->mState);
            ((void(__thiscall*)(cSpatialObject*, void*, float))VFn(&self->mLoco, 0xe4))(
                &self->mLoco, r, 1.0f);
        }
    }
    return true;
destroyed:
    self->FUN_00ca7250("(44) DC: defended city destroyed");
    self->FUN_00caa900();
    return false;
}

struct NodeState6ce0 {
    uint32_t mState;                                               // +0x00
    cCommunity* mpCommunity;                                       // +0x04
    cRefObj* mpObj;                                                // +0x08
};

// @ 0x00dc6ce0
void Node6ce0(cVehicle* self, int, int, int, int, NodeState6ce0* st)
{
    if (st->mState == 4)
        self->FUN_00ca80e0(0xe);
    if (st->mState == 7)
        self->FUN_00ca80e0(0x11);
    if (st->mpCommunity) {
        if (st->mpCommunity->Front() == self && *(int*)((char*)st->mpCommunity + 0x1ec) == 1)
            st->mpCommunity->Deactivate();
        st->mpCommunity->FUN_00bff290(self);
    }
    self->FUN_00c9ec40(1);
    cRefBase* o = (cRefBase*)st->mpObj;
    if (o)
        o->Release();
    cRefBase* c = (cRefBase*)st->mpCommunity;
    if (c)
        c->Release();
}

// @ 0x00dc6d60
float Node6d60(cVehicle* self, int, int, uint32_t flags)
{
    cGameData* t = (cGameData*)GetBestOpportunityTarget(self, 0, 0, 0, 0);
    if (!t)
        return 0.0f;
    cSpatialObject* sp = t->GetSpatial();
    const Vector3& tp = sp->GetPosition();
    float dist = (self->GetPosition() - tp).Length();
    if (dist < self->mGameData.GetRange())
        return 1.0f;
    if ((self->mFlags2a4 & 6) != 0)
        return 0.0f;
    float extra = (flags & 0x100) ? 60.0f : 0.0f;
    if (dist > self->mGameData.GetRange() + extra)
        return 1.0f;
    return 0.0f;
}

// @ 0x00dc6e30
bool Node6e30(cVehicle* self, int, int, int, int)
{
    cGameData* t = (cGameData*)GetBestOpportunityTarget(self, 0, 0, 0, 0);
    if (t) {
        cSpatialObject* sp = t->GetSpatial();
        void* old = self->mB7c;
        if (sp != old) {
            if (sp)
                sp->Vbc();
            self->mB7c = sp;
            if (old)
                ((cSpatialObject*)old)->Vc0();
        }
        self->mGameData.SetAttackTarget(t);
        return true;
    }
    FUN_00cabe70(self);
    return false;
}

struct NodeState7080 {
    cRefObj* mpObj;                                                // +0x00
    Vector3  mPos;                                                 // +0x04
    float    mf10;                                                 // +0x10
};

// @ 0x00dc7080
bool Node7080(cVehicle* self, int, int, int, int, NodeState7080* st)
{
    if (st)
        st->mpObj = 0;
    st->mf10 = 0.0f;
    cSpatialObject* sp = self->GetTarget();
    cRefObj* p = sp ? (cRefObj*)sp->IsType(0x13f94d4) : 0;
    cRefObj* old = st->mpObj;
    if (p != old) {
        if (p)
            p->AddRef();
        st->mpObj = p;
        if (old)
            old->Release();
    }
    if (!st->mpObj)
        return false;
    st->mPos = g_169fa68;
    if (SP_GetCurrentGameMode() == &g_1654c10)
        FUN_00dc4610(self);
    return true;
}

// @ 0x00dc7130
void Node7130(int, int, int, int, int, cRefObj** pp)
{
    if (pp && *pp)
        (*pp)->Release();
}

struct NodeState7150 {
    float mf0;                                                     // +0x00
    bool  mb4;                                                     // +0x04
};

// @ 0x00dc7150
bool Node7150(cVehicle* self, int, NodeState7150* st)
{
    st->mf0 = 0.0f;
    st->mb4 = false;
    self->mLoco.Vc4(0, 0.0f);
    {
        struct BigTemp {
            uint32_t m0;
            uint32_t m4;
            uint32_t m8;
            uint32_t mc;
            uint32_t m10;
            float    m14;
            float    m18;
            float    m1c;
            float    m20;
            float    m24;
            float    m28;
            float    m2c;
            uint32_t m30;
            uint32_t m34;
            uint32_t m38;
            uint32_t m3c;
            uint32_t m40;
            uint32_t m44;
            uint32_t m48;
            uint32_t m4c;
            uint32_t m50;
            uint32_t m54;
            uint8_t  m5c;
            uint8_t  m5d;
            uint8_t  m5e;
            uint8_t  m5f;
            float    m60;
            float    m64;
            float    m68;
            uint32_t m6c;
            float    m70;
            float    m74;
            float    m78;
            float    m7c;
            uint32_t m80;
        } temp;
        temp.m0 = 0;
        temp.m4 = 0;
        temp.m8 = 0;
        temp.mc = 0;
        temp.m10 = 0;
        temp.m14 = 0.0f;
        temp.m18 = 0.0f;
        temp.m1c = 0.0f;
        temp.m20 = g_169fa68.x;
        temp.m24 = g_169fa68.y;
        temp.m28 = g_169fa68.z;
        temp.m2c = *(float*)0x1485720;
        temp.m30 = 0;
        temp.m34 = 0;
        temp.m38 = 0;
        temp.m3c = 0;
        temp.m40 = 0;
        temp.m44 = 0;
        temp.m48 = 0;
        temp.m4c = 0;
        temp.m50 = 0;
        temp.m54 = 0;
        temp.m5c = 0;
        temp.m5d = 0;
        temp.m5e = 0;
        temp.m5f = 0;
        temp.m60 = 0.0f;
        temp.m64 = 0.0f;
        temp.m68 = 0.0f;
        temp.m6c = 0;
        temp.m70 = *(float*)0x13ec4b4;
        temp.m74 = 0.0f;
        temp.m78 = *(float*)0x147c3a0;
        temp.m7c = 0.0f;
        temp.m80 = 0;
        self->mLoco.Vdc(&temp);
        uint32_t* p0 = (uint32_t*)temp.m0;
        if (p0 && *(int*)((char*)p0 - 4) != 0)
            operator delete(p0);
    }
    void* mode = SP_GetCurrentGameMode();
    if (mode == &g_1654c10) {
        const Vector3& p = self->mLoco.GetPosition();
        void* sys = EA_Audio_GetSystemAT();
        void* h = sys ? VCall1(sys, 0x20) : 0;
        Start3dSoundByName(*(void**)(&((void**)0x147c438)[self->mState]), h, p.x, p.y, p.z);
    } else {
        if (((cSpatialObject*)&self->mLoco)->Vf58()) {
            void* sys = EA_Audio_GetSystemAT();
            void* h = sys ? VCall1(sys, 0x20) : 0;
            KillSetiEffects((void*)self->mState, ((void**)0x147c42c)[self->mState], h);
        }
    }
    if (self->mD04)
        self->FUN_00ca03a0((void*)0x2481db4);
    return true;
}

struct NodeState7300 {
    uint32_t mState;                                               // +0x00
    cCommunity* mpCommunity;                                       // +0x04
};

// @ 0x00dc7300
void Node7300(cVehicle* self, int, int, int, int, NodeState7300* st)
{
    if (st->mState == 4)
        self->FUN_00ca80e0(0xe);
    if (st->mState == 6)
        self->FUN_00ca80e0(0x11);
    if (st->mpCommunity)
        st->mpCommunity->FUN_00bff290(self);
    self->FUN_00c9ec40(1);
    cRefBase* c = (cRefBase*)st->mpCommunity;
    if (c)
        c->Release();
}

// @ 0x00dc7350
bool Node7350(int, int, int, int, int, void** pp)
{
    if (pp)
        *pp = 0;
    return true;
}

// @ 0x00dc7370
void Node7370(int, int, int, int, int, cRefBase** pp)
{
    if (pp && *pp)
        (*pp)->Release();
}

// @ 0x00dc7390
bool Node7390(cVehicle* self)
{
    int r = PlayIdleAnim((void*)(self->mAf0 + 8), 0x2000, 0);
    if (r == 0 || !(1.52587890625e-05f <= *(float*)(r + 8))) {
        self->mGameData.SetAttackTarget(0);
        return false;
    }
    void* c = 0;
    cSpatialObject* tgt = self->GetTarget();
    if (tgt)
        c = tgt->IsType(0x13f94d4);
    if (!c || FUN_008e7f80(c) == 2) {
        uint32_t owner = self->mGameData.GetOwnerID();
        void* list = 0;
        FUN_00c420d0(&list);
        void** p = *(void***)list;
        void** end = ((void***)list)[1];
        void* chosen = 0;
        for (; p != end; ++p) {
            void* o = *p;
            cSpatialObject* isDone = o ? (cSpatialObject*)((cGameData*)o)->GetSpatial() : 0;
            bool done = 0;
            if (isDone)
                done = (*(bool(__thiscall**)(void*))VFn(isDone, 0x2c))(isDone);
            if (done || !o)
                continue;
            cSpatialObject* c2 = (cSpatialObject*)((cInteractable*)o)->CastType(0x13f94d4);
            if (!c2)
                continue;
            cGameData* gd = ((cGameData*)c2)->GetSpatial() ? (cGameData*)c2 : 0;
            (void)gd;
            if ((*(uint32_t(__thiscall**)(void*))VFn(c2, 0x10))(c2) != owner)
                continue;
            if (!chosen || ((cTicker*)&g_1601760)->RandomDoubleUniform() < 0.5)
                chosen = c2;
        }
        if (chosen) {
            cSpatialObject* sp = ((cGameData*)chosen)->GetSpatial();
            void* old = self->mB7c;
            if (sp != old) {
                if (sp)
                    ((cRefObj*)sp)->Vbc();
                self->mB7c = sp;
                if (old)
                    ((cRefObj*)old)->Vc0();
            }
        }
    }
    return true;
}

// @ 0x00dc7510
void Node7510(cVehicle* self, int, int, int, int, cRefObj** pp)
{
    if (pp && *pp)
        (*pp)->Vc0();
    self->mLoco.Vec();
}

struct RemoveList {
    uint32_t pad0[0x10 / 4];
    void** mpBegin;                                                // +0x10
    void** mpEnd;                                                  // +0x14
};
// @ 0x00dc7540
void __fastcall Node7540(RemoveList* self)
{
    if (self->mpBegin != self->mpEnd) {
        do {
            void* n = self->mpEnd[-1];
            NounManager()->RemoveNoun(n);
            self->mpEnd = self->mpEnd - 1;
            cRefBase* p = (cRefBase*)*self->mpEnd;
            if (p)
                p->Release();
        } while (self->mpBegin != self->mpEnd);
    }
}

struct SpotHolder {
    void**   mpBegin;                                              // +0x00
    void**   mpEnd;                                                // +0x04
    uint32_t pad08[(0x60 - 0x08) / 4];
    void*    m60;                                                  // +0x60 (spatial whose position is the anchor)
};

// @ 0x00dc7590
void __cdecl PopToNearestValidSpot(SpotHolder* self, cActionCircle* circle, bool flag)
{
    if (flag)
        circle->FUN_00afafd0();
    if (self->mpBegin == self->mpEnd)
        return;

    cSpatialObject* loco = (cSpatialObject*)self->m60;
    const Vector3& p = loco->GetPosition();
    float px = p.x, py = p.y, pz = p.z;
    void* mover = *self->mpBegin;
    cMoverLike* veh = (cMoverLike*)(mover ? ((cSpatialObject*)mover)->IsType(0x137e8e0) : 0);

    int n = (int)((char*)circle->mpEnd - (char*)circle->mpBegin) / 0x18;
    if (n > 0) {
        char* slot = (char*)circle->mpBegin;
        do {
            Vector3 sp;
            sp.x = *(float*)(slot + 0xc);
            sp.y = *(float*)(slot + 0x10);
            sp.z = *(float*)(slot + 0x14);
            if (!((cVehicle*)veh)->CanOccupyTerrain(&sp)) {
                FUN_00afa070((cActionCircleSlot*)slot, 1);
            } else {
                float d = (px - sp.x) * (px - sp.x) + (py - sp.y) * (py - sp.y) + (pz - sp.z) * (pz - sp.z);
                d = (float)sqrt(d);
                if (veh->m80 < d || d < veh->m7c)
                    FUN_00afa070((cActionCircleSlot*)slot, 2);
            }
            slot += 0x18;
        } while (--n);
    }
}

struct RefHolder76e0 {
    void*    mpIndirect;                                           // +0x00 (pointer to the held object)
    uint32_t pad04[0x54 / 4];
    cRefObj* mp58;                                                 // +0x58
};
// @ 0x00dc76e0
void Node76e0(RefHolder76e0* self)
{
    cRefObj* p = *(cRefObj**)self->mpIndirect;
    cRefObj* old = self->mp58;
    if (p != old) {
        if (p)
            p->Vbc();
        self->mp58 = p;
        if (old)
            old->Vc0();
    }
}

// @ 0x00dc7780
extern "C" void* __cdecl SP_FindClosestVehicleWrap(void* a, void* b)
{
    return FUN_00dc6680(a, b, 0);
}

struct BufHolder {
    uint32_t pad0[2];
    void*    mp8;                                                  // +0x08
};
// @ 0x00dc77a0
void Node77a0(cVehicle* self, int, int, int, int, BufHolder* h)
{
    if (h) {
        void* p = h->mp8;
        if (p && *(int*)((char*)p - 4) != 0)
            operator delete(p);
    }
    self->mLoco.Vec();
}
