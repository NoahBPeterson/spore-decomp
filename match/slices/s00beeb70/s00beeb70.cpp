// Slice s00beeb70: FUN_00beeb70, vehicle/object (re)initialisation from its owning city.
//
// Assigns the owner city (intrusive pointer at +0x264), copies the city's locator position and
// orientation into the object's own locator (+0x34), picks a model/type id from the city's vehicle
// specialty when none is given, registers the 8 hard-coded offset points of the global table at
// 0x01469150 in the point vector (+0x15c), then rotates four fixed offset vectors by the
// locator's quaternion, scales them by mScale (+0x25c), adds the locator position, projects
// them onto the planet surface and stores them in the 4-point record array (+0x198).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE  (movss scalar math, no EH frame)
//
// The batch claimed with this slice (0x00bef4e0 .. 0x00befc00) is the object bookkeeping that
// hangs off the same class (RecomputeGameData + the two checked Locator setters), the small
// SP::cCivilization helpers (money, level, state, timers, flag bytes, species profile), the
// Object::Cast / relationship classification helpers and the two cCultureSet serializer wrappers.
// Those two are the only entries built with /GS- (they hold a 0xa14-byte serializer by value).
#include "types.h"

extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);   // thunk 0x011e073e
#pragma function(memset)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct Quaternion { float x, y, z, w; };

extern Vector3 g_PointOffsets[8];   // 0x01469150
extern float g_C478;   // 0x0168c478
extern float g_C47C;   // 0x0168c47c
extern float g_C480;   // 0x0168c480
extern float g_C484;   // 0x0168c484
extern float g_C488;   // 0x0168c488
extern float g_C48C;   // 0x0168c48c

// eastl::vector<Vector3, sp allocator>, 0x14 bytes
struct SpVector {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator[2];
    void DoInsertValue(Vector3* pos, const Vector3& v);   // 0x004b5ad0
    Vector3& push_back()
    {
        if (mpEnd < mpCapacity)
            ++mpEnd;
        else {
            Vector3 tmp;
            DoInsertValue(mpEnd, tmp);
        }
        return mpEnd[-1];
    }
};

struct Locator {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3* GetPosition();                       // 0x2c
    virtual const Quaternion* GetOrientation();                 // 0x30
    virtual void v34();
    virtual void SetPosition(const Vector3* p);                 // 0x38
    virtual void SetOrientation(const Quaternion* q);           // 0x3c

    void SetPositionRaw(const Vector3* p);                      // 0x00c88670
    void SetOrientationRaw(const Quaternion* q);                // 0x00c886d0
    void SetPositionIfChanged(const Vector3* p);                // 0x00bef540
    void SetOrientationIfChanged(const Quaternion* q);          // 0x00bef590
};
class cVehicleLike;

struct IntrusiveObj {
    virtual void AddRef();
    virtual void Release();
};

struct cCity : IntrusiveObj {
    uint32_t pad04[0x47];
    Locator  mLocator;      // +0x120
    int      GetVehicleSpecialty();          // 0x00bd81d0 (reads +0x540)
    const Vector3* FUN_00bd99e0();           // 0x00bd99e0
};

struct cPlanetModel {
    Vector3 DirectionToSurfacePosition(const Vector3& dir);   // 0x00b815a0
    Vector3 FUN_00b81630(const Vector3& pos);                  // 0x00b81630
};
cPlanetModel* PlanetModel();    // 0x00b3d350 (cdecl)
int FUN_00bebc90(int a, int b); // 0x00bebc90 (cdecl)

struct Rec4 {
    Vector3 p[8];
};

// Rotates (vx,vy,vz) by q and scales it by s.
__forceinline Vector3 RotateScaled(const Quaternion& q, const float* ps, float vx, float vy, float vz)
{
    float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
    float xy = q.y * q.x, xz = q.z * q.x, yz = q.z * q.y;
    float wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;
    float rx = (((xy - wz) * vy + (wy + xz) * vz) * 2.0f + (1.0f - (zz + yy) * 2.0f) * vx) * *ps;
    float ry = (((yz - wx) * vz + (wz + xy) * vx) * 2.0f + (1.0f - (zz + xx) * 2.0f) * vy) * *ps;
    float rz = (((wx + yz) * vy + (xz - wy) * vx) * 2.0f + (1.0f - (yy + xx) * 2.0f) * vz) * *ps;
    return Vector3(rx, ry, rz);
}
__forceinline Vector3 AddPos(const Locator& loc, const Vector3& o)
{
    const Vector3* p = const_cast<Locator&>(loc).GetPosition();
    return Vector3(p->x + o.x, p->y + o.y, p->z + o.z);
}

class cVehicleLike {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void SetModel(int id);   // 0x60

    uint32_t pad04[0xa];            // 0x04..0x2c
    uint32_t mOwnerPtr;             // +0x2c   (used by SetGameDataOwner2)
    uint32_t mOwnerId;              // +0x30
    Locator  mLocator;              // +0x34 (embedded object, own vptr)
    uint32_t pad38[0x49];           // to 0x15c
    SpVector mPoints;               // +0x15c
    uint32_t pad170[10];
    Rec4*    mpRecs;                // +0x198
    uint32_t pad19c[0x22];          // to 0x224
    Vector3  mV224;                 // +0x224 source of the copy below
    Vector3  mV230;                 // +0x230 copy target
    uint32_t pad23c[0x20];          // to 0x25c
    float    mScale;                // +0x25c
    uint32_t pad260;
    IntrusiveObj* mpCity;           // +0x264
    Vector3  mV268;                 // +0x268
    uint32_t mBlock274[49];         // +0x274 .. 0x338
    Vector3  mPos;                  // +0x338
    uint32_t pad344[2];
    int      mSpecialtyArg;         // +0x34c

    void SetGameDataOwner2(cCity* city);    // 0x00b18550
    void FUN_00bee150();                    // 0x00bee150
    void FUN_00bee200();                    // 0x00bee200
    void FUN_00becc80();                    // 0x00becc80
    void FUN_00beccf0();                    // 0x00beccf0
    Vector3* FUN_00becb10(Vector3* out, const Vector3* src);   // 0x00becb10

    void Init(cCity* city, int model);      // 0x00beeb70
    void RecomputeGameData();               // 0x00bef4e0
};

// @ 0x00beeb70
void cVehicleLike::Init(cCity* city, int model)
{
    if (city != mpCity) {
        IntrusiveObj* old = mpCity;
        if (city)
            city->AddRef();
        mpCity = city;
        if (old)
            old->Release();
    }
    SetGameDataOwner2(city);
    mPos = *city->mLocator.GetPosition();
    mLocator.SetPosition(&mPos);
    mLocator.SetOrientation(city->mLocator.GetOrientation());
    mV268 = *city->FUN_00bd99e0();
    if (model == 0)
        model = FUN_00bebc90(city->GetVehicleSpecialty(), mSpecialtyArg);
    SetModel(model);

    for (int i = 0; i < 8; ++i) {
        Vector3& r = mPoints.push_back();
        Vector3 t(g_PointOffsets[i]);
        r = t;
    }
    FUN_00bee150();

    const Quaternion* qp = mLocator.GetOrientation();
    Quaternion q;
    q.x = qp->x; q.y = qp->y; q.z = qp->z; q.w = qp->w;
    Vector3 o0 = RotateScaled(q, &mScale, g_C478, g_C47C, g_C480);
    mpRecs->p[0] = PlanetModel()->DirectionToSurfacePosition(AddPos(mLocator, o0));
    Vector3 o1 = RotateScaled(q, &mScale, g_C484, g_C488, g_C48C);
    mpRecs->p[1] = PlanetModel()->DirectionToSurfacePosition(AddPos(mLocator, o1));
    Vector3 o2 = RotateScaled(q, &mScale, -g_C484, -g_C488, -g_C48C);
    mpRecs->p[2] = PlanetModel()->DirectionToSurfacePosition(AddPos(mLocator, o2));
    Vector3 o3 = RotateScaled(q, &mScale, -g_C478, -g_C47C, -g_C480);
    mpRecs->p[3] = PlanetModel()->FUN_00b81630(AddPos(mLocator, o3));
    mpRecs->p[4] = mpRecs->p[2];
    mpRecs->p[5] = mpRecs->p[1];
    memset(mBlock274, 0, sizeof(mBlock274));
}

// ---------------------------------------------------------------------------------------------
// Object bookkeeping that hangs off the same vehicle/object class (0x00bef4e0), and the small
// civilization/relationship helpers at 0x00bef5f0 .. 0x00befc00.
extern const float g_invisibleFloorHeight;   // 0x0168c478 (first of the 6 offset floats above)

// @ 0x00bef4e0
void cVehicleLike::RecomputeGameData()
{
    FUN_00bee150();
    FUN_00bee200();
    FUN_00becc80();
    Vector3 tmp;
    Vector3* v = FUN_00becb10(&tmp, &mV224);
    mV230 = *v;
    FUN_00beccf0();
}

// @ 0x00bef540
void Locator::SetPositionIfChanged(const Vector3* p)
{
    const Vector3* cur = GetPosition();
    if (p->x == cur->x && p->y == cur->y && p->z == cur->z)
        return;
    SetPositionRaw(p);
    reinterpret_cast<cVehicleLike*>((char*)this - 0x34)->RecomputeGameData();
}

// @ 0x00bef590
void Locator::SetOrientationIfChanged(const Quaternion* q)
{
    const Quaternion* cur = GetOrientation();
    if (q->x == cur->x && q->y == cur->y && q->z == cur->z && q->w == cur->w)
        return;
    SetOrientationRaw(q);
    reinterpret_cast<cVehicleLike*>((char*)this - 0x34)->RecomputeGameData();
}

namespace SP {

// 0x48-byte game timer (lives inline in the civilization record).
struct cSPTimer {
    char mData[0x48];
    void Restart();                     // 0x00bc3130
    uint64_t GetElapsedTime();          // 0x00bc3190
};

struct cGameNounManager;

// The player's civilization record (money, tutorial/level progress, timers and the 12 flag
// bytes counted by CountFlags).
class cCivilization {
public:
    char     pad000[0x89];
    uint8_t  mUnlimitedMoney;        // +0x89  no-bankruptcy cheat
    char     pad08a[0x0e];
    float    mMoney;                 // +0x98
    char     pad09c[0x6c];
    cSPTimer mTimer108;              // +0x108
    char     pad150[0x118];
    uint32_t mSpeciesKey[0xc];       // +0x268 species/archetype key
    int      mLevel;                 // +0x298 civ level
    char     pad29c[0xd4];
    uint8_t  mFlag370;               // +0x370
    char     pad371[0x07];
    cSPTimer mTimer378;              // +0x378
    uint8_t  mFlag3c0;               // +0x3c0
    char     pad3c1[0x07];
    cSPTimer mTimer3c8;              // +0x3c8
    char     pad410[0x24];
    int      mState434;              // +0x434
    int      mId438;                 // +0x438
    int      mValue43c;              // +0x43c
    int      mValue440;              // +0x440
    int      mValue444;              // +0x444
    float    mValue448;              // +0x448
    char     pad44c[0x38];
    uint8_t  mFlags484[0x28];        // +0x484 flag bytes
    float    mCredit4ac;             // +0x4ac
    float    mDebt4b0;               // +0x4b0

    float GetMoney();                        // 0x00bef6d0
    void  SpendMoney(float amount);          // 0x00bef710
    void  RaiseLevel(int level);             // 0x00bef770
    bool  IsBelowTopState();                 // 0x00bef7e0
    void  SetState(int id, int state);       // 0x00bef800
    void  RestartTimer378();                 // 0x00bef830
    void  RestartTimer3c8();                 // 0x00bef850
    bool  IsTimer108Elapsed();               // 0x00bef8a0
    void  ResetValues();                     // 0x00bef5f0
    uint8_t GetFlag484(int index);           // 0x00bef970
    int   CountFlags();                      // 0x00befab0
    void* GetSpeciesProfile();               // 0x00bef950
};

struct cGameNounManager {
    char pad000[0x10];
    cCivilization* GetPlayerCivilization();    // 0x00b25fb0
};

cGameNounManager* NounManager();                 // 0x00b3d300

class cCivModeStrategy {
public:
    void CheckEvents();                          // 0x00cf9ba0
    void DoNext(int id, int flag);               // 0x00cfa990
};
cCivModeStrategy* GetCivModeStrategy();          // 0x00cf74c0

}  // namespace SP

struct cSPEditorSpeciesManager {
    const void* GetProfile();                    // 0x004df550
};
struct cSpeciesKey {
    cSPEditorSpeciesManager* Lookup(const void* key);   // 0x00401090
};

// @ 0x00bef5f0
void SP::cCivilization::ResetValues()
{
    mValue43c = -1;
    mValue440 = 0;
    mValue444 = 0;
    mValue448 = 0.0f;
}

// 0x00d00a70 ?ClampClassify@cRelationshipManager@@QAEHPAX00@Z
struct cRelationshipManager {
    int ClampClassify(void* a, void* b, int c);
    bool ClassifyIsHigh(void* a, void* b);       // 0x00bef620
};

// @ 0x00bef620
bool cRelationshipManager::ClassifyIsHigh(void* a, void* b)
{
    return ClampClassify(a, b, 1) >= 4;
}

// @ 0x00bef640
int __cdecl FUN_00bef640(int type)
{
    switch (type) {
    case 0:
        return 0;
    case 1:
        return 2;
    case 2:
        return 1;
    default:
        return 5;
    }
}

struct Object {
    void* FUN_00b18460(int type);                // 0x00b18460 dynamic cast for other types
    void* Cast(int type);                        // 0x00bef670
};

// @ 0x00bef670
void* Object::Cast(int type)
{
    Object* self = this;
    if (type == (int)0x901f1362 || type == (int)0xee3f516e)
        return self;
    if (type == (int)0x5593a1a)
        return self ? (void*)((char*)self + 0x3c) : 0;
    return self->FUN_00b18460(type);
}

// @ 0x00bef6d0
float SP::cCivilization::GetMoney()
{
    float money = mMoney;
    if (!mUnlimitedMoney)
        money = (mCredit4ac + money) + mDebt4b0;
    return money;
}

// @ 0x00bef710
void SP::cCivilization::SpendMoney(float amount)
{
    mMoney -= amount;
    if (!mUnlimitedMoney && mMoney < 0.0f) {
        mMoney = (mCredit4ac + mMoney) + mDebt4b0;
        mCredit4ac = 0.0f;
        mDebt4b0 = 0.0f;
    }
}

// @ 0x00bef770
void SP::cCivilization::RaiseLevel(int level)
{
    if (mLevel >= level)
        return;
    mLevel = level;
    if (this == SP::NounManager()->GetPlayerCivilization())
        SP::GetCivModeStrategy()->CheckEvents();
    if (mLevel < 4)
        return;
    if (this != SP::NounManager()->GetPlayerCivilization())
        return;
    SP::GetCivModeStrategy()->DoNext(0x3120767d, 1);
}

// @ 0x00bef7e0
bool SP::cCivilization::IsBelowTopState()
{
    return (uint32_t)mState434 <= 4u;
}

// @ 0x00bef800
void SP::cCivilization::SetState(int id, int state)
{
    if (id == mId438 && (state == 1 || state == 2))
        mState434 = state;
}

// @ 0x00bef830
void SP::cCivilization::RestartTimer378()
{
    mFlag370 = 1;
    mTimer378.Restart();
}

// @ 0x00bef850
void SP::cCivilization::RestartTimer3c8()
{
    mFlag3c0 = 1;
    mTimer3c8.Restart();
}

// @ 0x00bef8a0
bool SP::cCivilization::IsTimer108Elapsed()
{
    uint64_t t = mTimer108.GetElapsedTime();
    uint32_t hi = (uint32_t)(t >> 32);
    uint32_t lo = (uint32_t)t;
    if (hi > 0)
        return true;
    if (lo <= 120000u)
        return false;
    return true;
}

// @ 0x00bef950
void* SP::cCivilization::GetSpeciesProfile()
{
    cSpeciesKey* key = reinterpret_cast<cSpeciesKey*>(mSpeciesKey);
    const void* profile = key->Lookup(key)->GetProfile();
    return (void*)profile;
}

// @ 0x00bef970
uint8_t SP::cCivilization::GetFlag484(int index)
{
    return mFlags484[index];
}

// @ 0x00bef980
int __stdcall FUN_00bef980(int type)
{
    switch (type) {
    case (int)0x8226d0:   return 1;
    case (int)0x45cdf1a:  return 3;
    case (int)0x756d422:  return 10;
    case (int)0x3221e759: return 6;
    case (int)0x8a91f1e:  return 7;
    case (int)0x2cdbd6a1: return 0;
    case (int)0x36213c6a: return 2;
    case (int)0x4a78672c: return 11;
    case (int)0xfd05ab6d: return 4;
    case (int)0x81299805: return 5;
    case (int)0xc0617b2f: return 9;
    case (int)0xfc716a94: return 8;
    default:              return -1;
    }
}

// @ 0x00bef920
int __cdecl FUN_00bef920(int type)
{
    switch (type) {
    case 0:
        return 0;
    case 1:
        return 2;
    case 2:
        return 1;
    default:
        return -1;
    }
}

// @ 0x00befa50
int __stdcall FUN_00befa50(int type)
{
    switch (type) {
    case 0:
    case 6:
    case 11:
        return 2;
    case 1:
    case 4:
    case 7:
        return 4;
    case 2:
    case 5:
    case 8:
        return 6;
    default:
        return 1;
    }
}

// @ 0x00befab0
int SP::cCivilization::CountFlags()
{
    int n0 = 0, n1 = 0, n2 = 0, n3 = 0;
    for (int i = 0; i < 3; ++i) {
        n0 += mFlags484[i * 4 + 0] != 0;
        n1 += mFlags484[i * 4 + 1] != 0;
        n2 += mFlags484[i * 4 + 2] != 0;
        n3 += mFlags484[i * 4 + 3] != 0;
    }
    return n0 + (n3 + n2 + n1);
}

extern char g_smDataSerializerList_cCultureSet[];   // 0x0156fa30

// 0xa14-byte key/value list serializer used by the cCultureSet accessors below.
struct cVarListSerializer {
    char mData[0xa14];
    cVarListSerializer(void* context, const void* list, int id);   // 0x00692f90
    void Read(void* dest);                                          // 0x00693e10
    void Serialize(void* dest);                                     // 0x00692900
};

// @ 0x00befbc0
void* __cdecl FUN_00befbc0(void* dest, void* context)
{
    cVarListSerializer s(context, g_smDataSerializerList_cCultureSet, 0x1a80d26);
    s.Read(dest);
    return dest;
}

// @ 0x00befc00
void* __cdecl FUN_00befc00(void* dest, void* context)
{
    cVarListSerializer s(context, g_smDataSerializerList_cCultureSet, 0x1a80d26);
    s.Serialize(dest);
    return dest;
}
