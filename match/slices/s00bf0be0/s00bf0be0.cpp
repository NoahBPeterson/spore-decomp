// Slice s00bf0be0: SP::cCivilization gameplay helpers (17 functions, 0x00bf0be0-0x00bf1b4e).
// Vehicle/city queries, the serialization "Write" override, the relationship/superweapon AI steps
// and the superweapon cooldown helpers.
//
// Layouts are the retail (2017-era ModAPI) offsets: mCities +0x9c, mVehicles +0xb0 (both
// eastl::vector<AutoRefCount<T>>); only begin/end are read. The migrated PDB header's relaid
// offsets (mCities 0x88, mVehicles 0x9c) do not apply to retail.
// Flags: /O2 /MD /Gy /TP /arch:SSE (movss/comiss/cvtsi2ss; x87 only for call results, no EH frame).
#include "types.h"

// ---------------------------------------------------------------- helpers / interfaces

struct Vec3 { float x, y, z; };

struct RandomLCG { uint32_t RandomUint32Uniform(uint32_t limit); };   // 0x00a68fb0
extern RandomLCG sMathRandom;                                          // 0x01601760

struct SPTimer
{
    unsigned __int64 GetElapsedTime();   // 0x00bc3190
    void Restart();                      // 0x00bc3130
    bool IsRunning();                    // 0x00feba90
    uint32_t pad00[0x20 / 4];            // the object is 0x20 bytes (array stride)
};

struct TimerOwner { int FUN_0104bde0(); };                 // 0x0104bde0 (ret, int)

// Refcounted object head. The virtual declarations only shape the vtable (they cost no storage);
// the data members are placed at their retail offsets by explicit padding. Slot 0x0c = Cast,
// 0x2c = IsDestroyed, 0x4c = GetPoliticalID. Only the first slot is reachable through this view's
// own methods, but cCivilization needs GetPoliticalID, so we declare up to that slot.
class RCObject
{
public:
    virtual int   AddRef();                                  // +0x00
    virtual int   Release();                                 // +0x04
    virtual void  v08();                                     // +0x08
    virtual void* Cast(unsigned type);                       // +0x0c
    virtual void  v10(); virtual void  v14(); virtual void  v18(); virtual void  v1c();
    virtual void  v20(); virtual void  v24(); virtual void  v28();
    virtual bool  IsDestroyed();                             // +0x2c
    virtual void  v30(); virtual void  v34(); virtual void  v38(); virtual void  v3c();
    virtual void  v40(); virtual void  v44(); virtual void  v48();
    virtual int   GetPoliticalID();                          // +0x4c
};

// The spatial position/kind provider seen at +0x34 of a city/vehicle and at +0x120 of a city and of
// the +0x454 object. Only the vptr matters here.
struct SpatialSub { void* vptr; };                       // slots 0x2c = GetPosition, 0x50 = v50

class cCivilization;

// ---- a city/vehicle-style noun ----
// Declared with its own 0x34-byte head (vptr + padding) so mSpatial34 lands at +0x34 as in retail.
class cNounEntity
{
public:
    void**     mvptr;                        // +0x00
    uint32_t   pad04[(0x34 - 0x04) / 4];     // +0x04..0x33
    SpatialSub mSpatial34;                   // +0x34
    uint32_t   pad38[(0x120 - 0x38) / 4];    // +0x38..0x11f
    SpatialSub mSpatial120;                  // +0x120
    uint32_t   pad124[(0xb1c - 0x124) / 4];  // +0x124..0xb1b
    int        mFieldB1C;                    // +0xb1c
    int        mKindB20;                     // +0xb20

    // Functions at fixed addresses, declared as members of the placeholder class so cl emits
    // `call rel32` with `this` already in ecx (docs/codegen.md 11 / matching.md).
    int   GetCreatureCount();                // 0x00bd8120
    int   GetVehicleSpecialty();             // 0x00bd81d0
    cCivilization* FUN_00bd9bf0();           // 0x00bd9bf0 (GetCivilization)
    cNounEntity*   FUN_00bd84e0();           // 0x00bd84e0
    bool  FUN_00bdb200(void* ctx);           // 0x00bdb200 (ret 4)
    int   FUN_00bd7fc0(int pid);             // 0x00bd7fc0 (ret 4)
    void  FUN_00be9850(int pid, float v);    // 0x00be9850 (ret 8)
    int   FUN_00c9fee0();                    // 0x00c9fee0 (ret)
};

// ---- the civilization (retail layout, ModAPI offsets) ----
class cCivilization : public RCObject
{
public:
    void  FUN_00bf0be0(void* noun);                       // 0x00bf0be0
    int   FUN_00bf0c60(int spec, int continent, int flag, int zero);  // 0x00bf0c60
    int   FUN_00bf0cf0(int continent, int flag, int zero);            // 0x00bf0cf0
    int   FUN_00bf0d10(cNounEntity* v);                   // 0x00bf0d10
    bool  FUN_00bf0db0(void* c);                          // 0x00bf0db0
    int   Write(void* stream) const;                      // 0x00bf0e00
    int   FUN_00bf0f10();                                 // 0x00bf0f10
    int   FUN_00bf0f40();                                 // 0x00bf0f40
    void  UpdateCityMusicPosition();                      // 0x00bf0f90
    void  FUN_00bf1070();                                 // 0x00bf1070
    void  FUN_00bf1170();                                 // 0x00bf1170
    void  FUN_00bf1270();                                 // 0x00bf1270
    void  FUN_00bf14b0();                                 // 0x00bf14b0
    __declspec(noinline) bool  SuperweaponOnCooldown(int w);   // 0x00bf1790
    __declspec(noinline) float GetSuperweaponCooldown(int w);  // 0x00bf17f0
    float FUN_00bf1880(float which);                      // 0x00bf1880
    bool  FUN_00bf19c0(cCivilization* civ);               // 0x00bf19c0
    int   FUN_00bf01f0(int a, int b);                     // 0x00bf01f0 (ret 8)
    int   FUN_00bf0130(int flag);                         // 0x00bf0130 (ret 4)
    void  FUN_00bf0a60(void* noun);                       // 0x00bf0a60 (ret 4)
    int   FUN_00bfdf80();                                 // 0x00bfdf80 (ret)

    // data (retail offsets). The 4 bytes before pad50 are the inherited vptr.
    uint32_t  pad50[(0x9c - 0x04) / 4];       // +0x04..0x9b
    cNounEntity** mCitiesBegin;               // +0x9c
    cNounEntity** mCitiesEnd;                 // +0xa0
    uint32_t  mCitiesCap;                     // +0xa4
    uint32_t  padA8[(0xb0 - 0xa8) / 4];       // +0xa8..0xaf
    cNounEntity** mVehiclesBegin;             // +0xb0
    cNounEntity** mVehiclesEnd;               // +0xb4
    uint32_t  mVehiclesCap;                   // +0xb8
    uint32_t  padBC[(0xc4 - 0xbc) / 4];       // +0xbc
    float     mPrimaryColor[3];               // +0xc4 (r,g,b)
    uint32_t  padD0[(0x208 - 0xd0) / 4];      // +0xd0..0x207
    SPTimer   mTimer208;                      // +0x208
    SPTimer   mTimer228;                      // +0x228
    uint32_t  pad248[(0x274 - 0x248) / 4];    // +0x248..0x273
    void*     mpCityMusic;                    // +0x274
    uint32_t  pad278[(0x2f8 - 0x278) / 4];    // +0x278..0x2f7
    void*     mp2f8;                          // +0x2f8
    uint32_t  pad2fc;                         // +0x2fc
    SPTimer   mTimer300;                      // +0x300
    uint32_t  pad320[(0x454 - 0x320) / 4];    // +0x320..0x453
    void*     mp454;                          // +0x454
    uint32_t  pad458[(0x46c - 0x458) / 4];    // +0x458..0x46b
    cCivilization* mNemesisCiv;               // +0x46c
    TimerOwner** mpField470;                  // +0x470 (one timer owner per superweapon)
    uint32_t  pad474[(0x490 - 0x474) / 4];    // +0x474..0x48f
    SPTimer*  mSuperweaponCooldown;           // +0x490 (array of SPTimer, stride 0x20)
    uint32_t  pad494[(0x4b8 - 0x494) / 4];    // +0x494..0x4b7
    int       mForceMinDiploCount;            // +0x4b8
    int       pad4bc;                         // +0x4bc
    int       mMilitaryCaptureCount;          // +0x4c0
    int       mReligiousCaptureCount;         // +0x4c4
    int       mEconomicCaptureCount;          // +0x4c8
};

// ---- the city-music object at +0x274 ----
class CityMusic
{
public:
    virtual void u00(); virtual void u04(); virtual void u08(); virtual void u0c();
    virtual void u10(); virtual void u14(); virtual void u18(); virtual void u1c();
    virtual void u20(); virtual void u24(); virtual void u28();
    virtual void v2c(unsigned v);             // +0x2c
    virtual void v30(void* v);                // +0x30
};

// ---- the +0x454 object ----
class Obj454
{
public:
    void**     mvptr;                        // +0x00
    uint32_t   pad04[(0x120 - 0x04) / 4];
    SpatialSub mSpatial120;                  // +0x120
};

// ---------------------------------------------------------------- free functions / singletons

struct NounList   { cCivilization** begin; cCivilization** end; };// 0x00b25ca0
struct NounMgr
{
    cCivilization*  GetPlayerCivilization();  // 0x00b25fb0
    void*           GetCurrentTerrainSphere();// 0x00f67d90
    NounList*       GetCivList();             // 0x00b25ca0 (returns ptr to {begin,end})
};
NounMgr* NounManager();                       // 0x00b3d300

struct RelMgr
{
    int   FUN_00ae2e20(int a, int b);                       // 0x00ae2e20
    void  FUN_00d01b80(int a, int b, int c);                // 0x00d01b80 (ret 0xc)
    float CalculateRelationshipAbsolute(int a, int b, int c);// 0x00d05a20 (ret 0xc, float in st0)
};
RelMgr* RelationshipManager();                            // 0x00b3d2c0

int GetPlayerEmpireOrMinus1();                            // 0x00b1f9d0
int GetCurrentGameMode();                                 // 0x00b5b800
int FUN_00c9fee0(void* e);                                // 0x00c9fee0

struct PlanetMdl
{
    int   GetContinent(const Vec3* p);                    // 0x00b88590
};
PlanetMdl* PlanetModel();                                 // 0x00b3d350

struct CommMgr
{
    int  FUN_00ae9390();                                  // 0x00ae9390
    void ShowCommEvent(int a, void* ctx, int id1, int id2, int e, int f); // 0x00aeb760 (ret 0x18)
};
CommMgr* CommManager();                                   // 0x00b3d4a0

// The Atlantic var-list serializer built on the stack by Write.
struct cVarListSerializer
{
    cVarListSerializer(cCivilization* self, unsigned h, unsigned id);   // 0x00692f90 (ret 0xc)
    int  Serialize(void* stream);                                       // 0x00692900 (ret 4)
    uint32_t pad00[0xa18 / 4 - 2];
};

extern unsigned g_civAttributes;                          // 0x0156faa8
extern int g_civUpdateCounter;                            // 0x0168cb50
extern float g_civConst1;                                 // 0x01485378
extern int   g_civSuperweaponMode;                        // 0x01654c04

// stream objects used by Write (slots 0x18 / 0x20 only).
class Writer
{
public:
    virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
    virtual void w10(); virtual void w14();
    virtual void* v18();                     // +0x18
};
class Stream
{
public:
    virtual void o00(); virtual void o04(); virtual void o08(); virtual void o0c();
    virtual void o10(); virtual void o14();
    virtual void o18();
    virtual void o1c();
    virtual Writer* v20();                   // +0x20
};

// The comm-context source: FUN_01021260() returns an object whose +0x13c is a star-record reference
// whose slot-free accessor 0x00ce6950 returns its +0x184 field.
class StarCtx
{
public:
    uint32_t pad00[0x184 / 4];
    void*    mField184;                      // +0x184
};

// Business object reached through FUN_00ca71d0.
class NounInfo
{
public:
    void*    mpObject;                       // +0x00
    uint32_t pad04[3];                       // +0x04..0x0f
    int      mKind;                          // +0x10
};

// The serializer sub-object embedded in cCivilization at +0x3c (cSerializable host).
struct SubObject3c { int Serialize(void* stream); };              // 0x00b6e2d0 (ret 4)
int WriteGameData(void* civ, void* stream);                       // 0x00b18590 (ret 4)

// Business object reached through the Cast() calls in FUN_00bf19c0.
class Cty2
{
public:
    void**     mvptr;                        // +0x00
    uint32_t   pad04[(0xb20 - 0x04) / 4];
    int        mKindB20;                     // +0xb20
    cCivilization* GetCiv();                 // 0x00bd9bf0
    cNounEntity*   FUN_00bd84e0();           // 0x00bd84e0
};
// Placeholder host classes for the remaining fixed-address callees.
struct Sphere     { int   FUN_00c75420(); };                      // 0x00c75420
struct LivingUniverse { StarCtx* mpCtx; };                        // +0x13c
struct WTextRef   { void* p; };
LivingUniverse* FUN_01021260();                                   // 0x01021260
void  AutoRefCountAssignWText(WTextRef* dst, void* p);            // 0x00b5f950
int   FUN_00c75420(void* sphere);                                 // 0x00c75420
int   FUN_00ca71d0(void* self);                                   // 0x00ca71d0
void* GetSystemAT();                                              // 0x00a206f0
int   EA_IO_WriteUint32(void* s, const void* v, int a, int b);    // 0x0093aa70
void* FUN_00befee0(cCivilization* civ, const Vec3* pos, int b);   // 0x00befee0 (ret 8)

// vtable-slot helper for the spatial subobjects: two instructions, exactly the original shape.
typedef void* (__fastcall* VFP)(void*);
typedef int   (__fastcall* VFI)(void*);
typedef char  (__fastcall* VFC)(void*);
static inline const Vec3* GetPos(SpatialSub* s) { return (const Vec3*)((VFP)((*(void***)s)[0x2c / 4]))(s); }
static inline int         Slot50(SpatialSub* s) { return ((VFC)((*(void***)s)[0x50 / 4]))(s); }
static inline int         Slot08(SpatialSub* s) { return ((VFI)((*(void***)s)[0x08 / 4]))(s); }
// IsDestroyed is vtable slot 0x2c on anything with a vptr.
static inline int         Slot2c(void* o) { return ((VFI)((*(void***)o)[0x2c / 4]))(o); }

// ==================================================================== bodies

// @ 0x00bf0be0
void cCivilization::FUN_00bf0be0(void* noun)
{
    NounList* list = NounManager()->GetCivList();
    cCivilization** it = list->begin;
    cCivilization** end = list->end;
    for (; it != end; ++it)
        (*it)->FUN_00bf0a60(noun);

    void* old = mp2f8;
    if (noun != old) {
        if (noun) ((RCObject*)noun)->AddRef();
        mp2f8 = noun;
        if (old) ((RCObject*)old)->Release();
    }
    mTimer300.Restart();
}

// @ 0x00bf0c60
int cCivilization::FUN_00bf0c60(int spec, int continent, int flag, int zero)
{
    cNounEntity** end = mVehiclesEnd;
    cNounEntity** it = mVehiclesBegin;
    int count = 0;
    for (; it != end; ++it) {
        cNounEntity* v = *it;
        if (v->mKindB20 != spec) continue;
        if (continent != -1 && PlanetModel()->GetContinent(GetPos(&v->mSpatial34)) != continent) continue;
        if (flag != -1 && v->mFieldB1C != flag) continue;
        if (zero && Slot50(&v->mSpatial34) != 1) continue;
        ++count;
    }
    return count;
}

// @ 0x00bf0cf0
int cCivilization::FUN_00bf0cf0(int continent, int flag, int zero)
{
    return FUN_00bf0c60(continent, flag, zero, 1);
}

// @ 0x00bf0d10
int cCivilization::FUN_00bf0d10(cNounEntity* v)
{
    cNounEntity** it = mVehiclesBegin;
    cNounEntity** end = mVehiclesEnd;
    int count = 0;
    while (it != end) {
        int x = Slot08(&v->mSpatial120);
        if ((*it)->FUN_00c9fee0() == x) ++count;
        ++it;
    }
    return count;
}

// @ 0x00bf0db0
bool cCivilization::FUN_00bf0db0(void* c)
{
    int n = (int)(mCitiesEnd - mCitiesBegin);
    for (int i = 0; i < n; ++i)
        if (mCitiesBegin[i]->FUN_00bdb200(c)) return true;
    return false;
}

// @ 0x00bf0e00
int cCivilization::Write(void* stream) const
{
    // bl = SP_WriteGameData(this, stream)  (0x00b18590, thiscall, ret 4)
    int bl = WriteGameData((void*)this, stream);
    // al = serializer embedded at this+0x3c -> Serialize(stream)  (0x00b6e2d0, ret 4)
    int al = ((SubObject3c*)((char*)this + 0x3c))->Serialize(stream);
    int ok = 0;
    if (al && bl) ok = 1;

    Stream* s = (Stream*)stream;
    void* w = s->v20()->v18();
    EA_IO_WriteUint32(w, &mPrimaryColor[0], 1, 0);
    EA_IO_WriteUint32(w, &mPrimaryColor[1], 1, 0);
    EA_IO_WriteUint32(w, &mPrimaryColor[2], 1, 0);

    cVarListSerializer ser((cCivilization*)this, g_civAttributes, 0x1a80d26);
    if (ser.Serialize(stream)) ok = 1;
    return ok;
}

// @ 0x00bf0f10
int cCivilization::FUN_00bf0f10()
{
    int total = 0;
    cNounEntity** end = mCitiesEnd;
    for (cNounEntity** it = mCitiesBegin; it != end; ++it)
        total += (*it)->GetCreatureCount();
    return total;
}

// @ 0x00bf0f40
int cCivilization::FUN_00bf0f40()
{
    int n = (int)mCitiesEnd - (int)mCitiesBegin;
    if (n & 0xfffffffc) {
        cNounEntity* c = *mCitiesBegin;
        if (c != 0) {
            switch (c->GetVehicleSpecialty()) {
            case 0: return 0;
            case 1: return 2;
            case 2: return 1;
            default: return -1;
            }
        }
    }
    return 0;
}

// @ 0x00bf0f90
void cCivilization::UpdateCityMusicPosition()
{
    void* sys = GetSystemAT();
    if (mpCityMusic == 0) return;
    if (mCitiesBegin == mCitiesEnd) return;
    if (sys == 0) return;

    const Vec3* p = (const Vec3*)((VFP)((*(void***)sys)[0x10 / 4]))(sys);
    Vec3 pos;
    pos.x = p->x;
    pos.y = p->y;
    pos.z = p->z;

    AutoRefCountAssignWText((WTextRef*)&mp454, FUN_00befee0(this, &pos, 0));
    Obj454* o = (Obj454*)mp454;
    if (o == 0) return;

    CityMusic* mus = (CityMusic*)mpCityMusic;
    mus->v30((void*)GetPos(&o->mSpatial120));
    if (GetCurrentGameMode() == g_civSuperweaponMode)
        mus->v2c(Slot08(&o->mSpatial120));
}

// @ 0x00bf1070
void cCivilization::FUN_00bf1070()
{
    cCivilization* self = this;
    if (mForceMinDiploCount > 0) --mForceMinDiploCount;

    int pid = GetPoliticalID();
    int player = GetPlayerEmpireOrMinus1();
    if (pid != player)
        RelationshipManager()->CalculateRelationshipAbsolute(pid, player, 0);

    NounList* l1 = NounManager()->GetCivList();
    int civCount = ((int)l1->end - (int)l1->begin) >> 2;
    if (++g_civUpdateCounter < civCount + 1) return;

    g_civUpdateCounter = 0;
    NounList* list = NounManager()->GetCivList();
    cCivilization** it = list->begin;
    cCivilization** end = list->end;
    for (; it != end; ++it) {
        cCivilization* o = *it;
        if (o == self) continue;
        int e = GetPlayerEmpireOrMinus1();
        int opid = o->GetPoliticalID();
        if (opid != e)
            RelationshipManager()->CalculateRelationshipAbsolute(pid, opid, 0);
    }
}

// @ 0x00bf1170
void cCivilization::FUN_00bf1170()
{
    if (((char*)this)[0x8a]) return;
    cCivilization* p = NounManager()->GetPlayerCivilization();
    if (p != 0 && !((char*)p)[0x8d]) return;

    NounList* list = NounManager()->GetCivList();
    int n = (int)(list->end - list->begin) >> 2;
    for (int i = 0; i < n; ++i) {
        cCivilization* o = list->begin[i];
        if (o == this) continue;
        if (((char*)o)[0x89]) continue;
        int m = (int)(o->mCitiesEnd - o->mCitiesBegin) >> 2;
        for (int j = 0; j < m; ++j) {
            cNounEntity* c = o->mCitiesBegin[j];
            int pid = GetPoliticalID();
            if (c->FUN_00bd7fc0(pid))
                c->FUN_00be9850(pid, 0.0f);
        }
    }
}

// @ 0x00bf1270
void cCivilization::FUN_00bf1270()
{
    if (((int)(mCitiesEnd - mCitiesBegin) & 0xfffffffc) <= 4) return;
    cNounEntity* first = *mCitiesBegin;
    if (first == 0) return;
    if (((char*)this)[0x8a]) return;

    cCivilization* p = NounManager()->GetPlayerCivilization();
    if (p == 0 || !((char*)p)[0x8d]) return;

    int player = GetPlayerEmpireOrMinus1();
    if (!RelationshipManager()->FUN_00ae2e20(GetPoliticalID(), player)) return;

    NounList* list = NounManager()->GetCivList();
    int n = (int)(list->end - list->begin) >> 2;
    cCivilization* best = 0;
    int bestScore = 0;
    for (int i = 0; i < n; ++i) {
        cCivilization* o = list->begin[i];
        if (o == this) continue;
        if (((char*)o)[0x8a]) continue;
        if (((char*)o)[0x89]) continue;
        if (((int)(o->mCitiesEnd - o->mCitiesBegin) & 0xfffffffc) <= 4) continue;
        if (!o->FUN_00bf0db0((void*)GetPlayerEmpireOrMinus1())) continue;
        if (!RelationshipManager()->FUN_00ae2e20(o->GetPoliticalID(), GetPoliticalID())) continue;
        int r = sMathRandom.RandomUint32Uniform(100);
        if (o->mNemesisCiv == this) r += 100;
        if (r > bestScore) { bestScore = r; best = o; }
    }
    if (best == 0) return;
    cNounEntity* target = best->mCitiesBegin[0];
    if (target == 0) return;
    if (mTimer208.GetElapsedTime() <= 50000) return;
    if (CommManager()->FUN_00ae9390()) { mTimer208.Restart(); return; }
    unsigned lim = 1;
    int t = FUN_00c75420(NounManager()->GetCurrentTerrainSphere());
    if (t == 0) lim = 12; else if (t == 1) lim = 9; else if (t == 2) lim = 6;
    if (sMathRandom.RandomUint32Uniform(lim) == 0) {
        CommMgr* cm = CommManager();
        LivingUniverse* lu = FUN_01021260();
        int cc = (int)lu->mpCtx->mField184;
        cm->ShowCommEvent((int)first, target, 0xdbf385bf, 0x1aa5bff0, cc, 0);
    }
    mTimer208.Restart();
}

// @ 0x00bf14b0
void cCivilization::FUN_00bf14b0()
{
    if (((int)(mCitiesEnd - mCitiesBegin) & 0xfffffffc) <= 4) return;
    cNounEntity* first = *mCitiesBegin;
    if (first == 0) return;
    if (((char*)this)[0x8a]) return;

    cCivilization* p = NounManager()->GetPlayerCivilization();
    if (p == 0) return;
    if (!((char*)p)[0x8d]) return;
    if (((int)(p->mCitiesEnd - p->mCitiesBegin) & 0xfffffffc) <= 4) return;

    if (RelationshipManager()->FUN_00ae2e20(GetPoliticalID(), GetPlayerEmpireOrMinus1())) return;
    RelationshipManager()->FUN_00d01b80(GetPoliticalID(), GetPlayerEmpireOrMinus1(), (int)0x0526e4f8);

    NounList* list = NounManager()->GetCivList();
    int n = (int)(list->end - list->begin) >> 2;
    cCivilization* best = 0;
    int bestScore = 0;
    int mode = 0;
    for (int i = 0; i < n; ++i) {
        cCivilization* o = list->begin[i];
        if (o == this) continue;
        if (((char*)o)[0x8a]) continue;
        if (((char*)o)[0x89]) continue;
        if (((int)(o->mCitiesEnd - o->mCitiesBegin) & 0xfffffffc) <= 4) continue;
        if (!RelationshipManager()->FUN_00ae2e20(o->GetPoliticalID(), GetPoliticalID())) continue;
        if (!RelationshipManager()->FUN_00ae2e20(o->GetPoliticalID(), GetPlayerEmpireOrMinus1())) continue;
        if (!o->FUN_00bf0130(mode) && !FUN_00bf0130(mode)) continue;
        int r = sMathRandom.RandomUint32Uniform(100);
        if (o->mNemesisCiv == this) r += 100;
        if (r > bestScore) { bestScore = r; best = o; }
    }
    if (best == 0) return;
    cNounEntity* target = best->mCitiesBegin[0];
    if (target == 0) return;
    if (mTimer228.GetElapsedTime() <= 60000) return;
    if (CommManager()->FUN_00ae9390()) { mTimer228.Restart(); return; }
    unsigned lim = 1;
    int t = FUN_00c75420(NounManager()->GetCurrentTerrainSphere());
    if (t == 0) lim = 16; else if (t == 1) lim = 12; else if (t == 2) lim = 8;
    if (sMathRandom.RandomUint32Uniform(lim) == 0) {
        CommMgr* cm = CommManager();
        LivingUniverse* lu = FUN_01021260();
        int cc = (int)lu->mpCtx->mField184;
        cm->ShowCommEvent((int)first, target, 0xdbf385bf, 0x18371572, cc, 0);
    }
    mTimer228.Restart();
}

// @ 0x00bf1790
bool cCivilization::SuperweaponOnCooldown(int w)
{
    SPTimer* t = mSuperweaponCooldown + w;
    if (t->IsRunning()) {
        unsigned __int64 limit = (unsigned __int64)(unsigned)(mpField470[w])->FUN_0104bde0();
        return t->GetElapsedTime() < limit;
    }
    return false;
}

// @ 0x00bf17f0
float cCivilization::GetSuperweaponCooldown(int w)
{
    if (!SuperweaponOnCooldown(w)) return 0.0f;
    float elapsed = (float)(mSuperweaponCooldown + w)->GetElapsedTime();
    float total = (float)mpField470[w]->FUN_0104bde0();
    return elapsed / total;
}

// @ 0x00bf1880
float cCivilization::FUN_00bf1880(float which)
{
    float a = (float)mMilitaryCaptureCount;
    float b = (float)mReligiousCaptureCount;
    float c = (float)mEconomicCaptureCount;
    float m = (b > a) ? b : a;
    if (c > m) m = c;
    if (m == g_civConst1) {
        a = (float)FUN_00bf01f0(0, 0);
        b = (float)FUN_00bf01f0(1, 0);
        c = (float)FUN_00bf01f0(2, 0);
        m = (b > a) ? b : a;
        if (c > m) m = c;
    }
    if (m == g_civConst1) return 0.0f;
    if (which == (float)0x0a35d0f5) return a / m;
    if (which == (float)0x3360727f) return c / m;
    if (which == (float)0x6aeb96a1) return b / m;
    return which;
}

// @ 0x00bf19c0
bool cCivilization::FUN_00bf19c0(cCivilization* civ)
{
    for (cNounEntity** it = mVehiclesBegin; it != mVehiclesEnd; ++it) {
        cNounEntity* v = *it;
        if (v == 0) continue;
        int k = v->mKindB20;
        if (k != 0 && k != 1) continue;

        NounInfo* ni = (NounInfo*)FUN_00ca71d0(v);
        if (ni->mKind == 1) {
            if (ni->mpObject == 0) continue;
            void* c = ((RCObject*)ni->mpObject)->Cast(0x0403df5f);
            if (c == 0) continue;
            if (((cCivilization*)c)->FUN_00bfdf80() == (int)civ) return 0;
            continue;
        }

        NounInfo* n2 = (NounInfo*)FUN_00ca71d0(v);
        int twoOrThree = (n2->mKind == 2 && n2->mpObject != 0);
        if (!twoOrThree) {
            NounInfo* n3 = (NounInfo*)FUN_00ca71d0(v);
            if (n3->mKind != 3) continue;
            if (n3->mpObject == 0) continue;
        }

        NounInfo* n4 = (NounInfo*)FUN_00ca71d0(v);
        if (n4->mpObject == 0) continue;
        Cty2* city = (Cty2*)((RCObject*)n4->mpObject)->Cast(0xee9b2232);
        if (city != 0 && !Slot2c(city) && city->GetCiv() == civ) return 0;

        NounInfo* n5 = (NounInfo*)FUN_00ca71d0(v);
        if (n5->mpObject == 0) continue;
        cNounEntity* ent = (cNounEntity*)((RCObject*)n5->mpObject)->Cast(0x03d5c477);
        if (ent == 0) continue;
        RCObject* sub = (RCObject*)Slot08(&ent->mSpatial34);
        if (sub == 0) continue;
        RCObject* c2 = (RCObject*)sub->Cast(0xee9b2232);
        if (c2 == 0) continue;
        if (!Slot2c(c2) && ent->FUN_00bd84e0()->FUN_00bd9bf0() == civ) return 0;
    }
    return true;
}


// Cl otherwise inlines and drops members that no other translation unit references; naming their
// addresses here keeps one out-of-line copy of each so the slice's symbols are emitted.
static bool (cCivilization::*const g_keep1)(int) = &cCivilization::SuperweaponOnCooldown;
static float (cCivilization::*const g_keep2)(int) = &cCivilization::GetSuperweaponCooldown;
void* const g_s00bf0be0_keep[] = { (void*)&g_keep1, (void*)&g_keep2 };
