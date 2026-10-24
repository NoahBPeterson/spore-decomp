// Slice s00b9b090: FUN_00b9b090 (~2.7 KB, __cdecl), planet-spot placement for a list of
// spawn definitions.
//
// For every definition instance id in `ids` it loads the property list (group 0x302a1c9).
// Lists that carry 0xd50059a5 and 0x100e7b1c are rolled against their spawn chance
// (0x4934caca, default 1.0). It then reads the tuning values (Vector2 ranges, floats, bools,
// an int), lets FUN_00b97720 pick a start position, nudges it with the spot grid at
// 0x0156c060, and places a random number of objects (FUN_00b94090) around it, walking the
// planet surface with MakeRandomWorldPosition. If the list has 0xbb64b481, FUN_00b9aa10
// handles that key array around the original centre. Returns how many objects were placed.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same module as s00b9d820: movss, fcomi, no EH).
#include "types.h"

// ---------------------------------------------------------------------------------------
// Math
struct Vector2 {
    float x, y;
    __forceinline Vector2() {}
    __forceinline Vector2(const Vector2& o) : x(o.x), y(o.y) {}
};
struct Vector3 {
    float x, y, z;
    __forceinline Vector3() {}
    __forceinline Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Quaternion { float x, y, z, w; };
struct Matrix3 {
    float m[3][3];
    Matrix3& operator=(const Matrix3& other);   // 0x0041cb40 (out of line)
};

__forceinline Vector3 operator*(const Vector3& v, const Matrix3& m)
{
    Vector3 r;
    r.x = m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[0][0] * v.x;
    r.y = m.m[1][1] * v.y + m.m[2][1] * v.z + m.m[0][1] * v.x;
    r.z = m.m[1][2] * v.y + m.m[2][2] * v.z + m.m[0][2] * v.x;
    return r;
}

Matrix3 Matrix3FromAxisAngle(const Vector3& axis, float angle);   // 0x00453b20
Vector3 OrthogonalVector(const Vector3& v);                        // 0x006985b0
Quaternion QuaternionFromFacingAndUp(const Vector3& facing, const Vector3& up);   // 0x0069b600

// float -> int rounding (the module's asm helper)
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

// ---------------------------------------------------------------------------------------
// Random
class RandomLinearCongruential {
public:
    double RandomDoubleUniform();   // 0x009360d0
};
extern RandomLinearCongruential g_Random;   // 0x016888e8

__forceinline double RandomDoubleUniform(double limit)
{
    double value = g_Random.RandomDoubleUniform() * limit;
    if (value >= limit) return limit;
    if (value < 0.0) return 0.0;
    return value;
}

float RandomFloatRange(float lo, float hi);   // 0x00b906a0

extern float g_SpotMaxTwist;   // 0x01688948

// ---------------------------------------------------------------------------------------
// Ref-counted pointer
template<class T> struct RefPtr {
    T* mp;
    __forceinline RefPtr() : mp(0) {}
    __forceinline ~RefPtr() { if (mp) mp->Release(); }
    __forceinline T* get() const { return mp; }
    __forceinline T* operator->() const { return mp; }
    __forceinline operator T*() const { return mp; }
};

// ---------------------------------------------------------------------------------------
// Properties
extern uint32_t g_DefaultUInt32;   // 0x015d1164
extern bool     g_DefaultBool;     // 0x015d115d
Vector2* GetDefaultVector2();      // 0x006bb5d0

struct Property {
    void*    mpData;   // +0x0
    uint32_t pad04;
    int      mnCount;  // +0x8
    uint32_t pad0c;
    uint16_t mnFlags;  // +0x10
    uint16_t mnType;   // +0x12

    float*    GetValueFloat();    // 0x0041ea70
    bool*     GetValueBool();     // 0x0041e920
    uint32_t* GetValueUInt32();   // 0x0041ea00

    __forceinline void* GetDataPtr()
    {
        return (mnFlags & 0x30) ? mpData : (mnType ? this : 0);
    }
    __forceinline uint32_t* GetUInt32Value()
    {
        if (mnType == 0xa || mnType == 0x10)
            return (uint32_t*)GetDataPtr();
        return &g_DefaultUInt32;
    }
    __forceinline bool* GetBoolValue()
    {
        if (mnType == 1 || mnType == 0x10)
            return (bool*)GetDataPtr();
        return &g_DefaultBool;
    }
    __forceinline Vector2* GetVector2Value()
    {
        if (mnType == 0x30 || mnType == 0x10)
            return (Vector2*)GetDataPtr();
        return GetDefaultVector2();
    }
    __forceinline int GetItemCount()
    {
        return (mnFlags & 0x30) ? mnCount : (mnType != 0);
    }
    __forceinline void* GetItems()
    {
        return (mnFlags & 0x30) ? mpData : (mnType ? this : 0);
    }
};

class PropertyList {
public:
    virtual int  AddRef();
    virtual int  Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasProperty(uint32_t id);                       // 0x1c
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& out);       // 0x24
    virtual Property* GetPropertyObject(uint32_t id);            // 0x28
};
typedef RefPtr<PropertyList> PropertyListPtr;

__forceinline bool GetFloat(PropertyList* list, uint32_t id, float& value)
{
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 0xd) {
        value = *prop->GetValueFloat();
        return true;
    }
    return false;
}
__forceinline bool GetBool(PropertyList* list, uint32_t id, bool& value)
{
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 1) {
        value = *prop->GetValueBool();
        return true;
    }
    return false;
}
__forceinline bool GetUInt32(PropertyList* list, uint32_t id, uint32_t& value)
{
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 0xa) {
        value = *prop->GetValueUInt32();
        return true;
    }
    return false;
}

class IPropManager {
public:
    virtual int  AddRef();
    virtual int  Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst);  // 0x2c
};

float GetPropertyFloat(PropertyList* list, uint32_t id, float defaultValue);   // 0x004e1c70

// ---------------------------------------------------------------------------------------
// Managers
class cPlanetModel {
public:
    float   GetWaterHeight();                                                  // 0x00b7e390
    Vector3 GetSurfaceNormal(const Vector3& pos);                              // 0x00b7e3b0
    Vector3 MakeRandomWorldPosition(const Vector3& pos, float minDist, float maxDist);   // 0x00b81780
    Vector3 DirectionToSurfacePosition(const Vector3& dir);                     // 0x00b815a0
};

class cSpotGrid {
public:
    void AdjustPosition(Vector3& pos, float a, float b, float c);   // 0x00b90ea0
};
extern cSpotGrid g_SpotGrid;   // 0x0156c060

IPropManager* PropertyManager();   // 0x0067de30
void*         NounManager();       // 0x00b3d300
cPlanetModel* PlanetModel();       // 0x00b3d350

bool FUN_00b97720(Vector3* outPos, const void* context, bool flag,
                  float a0, float a1, float b0, float b1, float c, float waterLo, float waterHi,
                  float d0, float d1, float e, int flags, uint32_t* outInfo, uint32_t count, bool flag2);
bool FUN_00b94090(const Vector3& pos, const Quaternion& orientation, uint32_t typeA, uint32_t typeB,
                  uint32_t instanceID, int unused, uint32_t extra);
void FUN_00b9aa10(const Vector3& center, void* items, int count, uint32_t instanceID);

// @ 0x00b9b090
int FUN_00b9b090(const void* context, uint32_t* ids, uint32_t count, uint32_t instanceOverride,
                 uint32_t extra)
{
    int placed = 0;
    IPropManager* propManager = PropertyManager();
    NounManager();
    cPlanetModel* planet = PlanetModel();
    float waterHeight = planet->GetWaterHeight();

    for (uint32_t i = 0; i < count; i++) {
        PropertyListPtr list;
        if (propManager->GetPropertyList(ids[i], 0x302a1c9, list) &&
            list->HasProperty(0xd50059a5) && list->HasProperty(0x100e7b1c)) {
            float chance = GetPropertyFloat(list, 0x4934caca, 1.0f);
            if (!(g_Random.RandomDoubleUniform() > chance)) {
                uint32_t typeB = *list->GetPropertyObject(0xd50059a5)->GetUInt32Value();
                uint32_t typeA = *list->GetPropertyObject(0x100e7b1c)->GetUInt32Value();
                bool flag = *list->GetPropertyObject(0x54f1ce40)->GetBoolValue();

                float f44 = 0.0f;
                float f1c = 0.0f;
                float f24 = 0.0f;
                float f18 = 0.0f;
                bool b10 = false;
                bool b20 = false;
                bool b40 = false;
                float f40 = 0.0f;
                uint32_t u = 0;
                bool b2 = false;

                Vector2 countRange = *list->GetPropertyObject(0x678d47a2)->GetVector2Value();
                Vector2 stepRange  = *list->GetPropertyObject(0xe4ad4e84)->GetVector2Value();
                Vector2 rangeC     = *list->GetPropertyObject(0x94b1298e)->GetVector2Value();
                Vector2 rangeD     = *list->GetPropertyObject(0xebc9f3ba)->GetVector2Value();
                GetFloat(list, 0xc75c3509, f44);
                Vector2 heightRange = *list->GetPropertyObject(0x440a932b)->GetVector2Value();
                Vector2 rangeF      = *list->GetPropertyObject(0x00d7e2d7)->GetVector2Value();
                GetFloat(list, 0x24a02634, f1c);
                GetFloat(list, 0xcbb8d102, f24);
                GetFloat(list, 0x561c98ac, f18);
                GetBool(list, 0x80cd38c6, b10);
                GetBool(list, 0x3a509d24, b20);
                GetBool(list, 0x835025da, b40);
                GetFloat(list, 0x173b0bb7, f40);
                GetUInt32(list, 0x8915e39f, u);
                GetBool(list, 0x5c0c06f, b2);

                float heightLo = heightRange.x + waterHeight;
                float heightHi = heightRange.y + waterHeight;
                uint32_t num = RoundToInt(RandomFloatRange(countRange.x, countRange.y));

                int flags = 0;
                if (b10) flags = 0x10;
                if (b20) flags |= 0x20;
                if (b40) flags |= 0x40;

                Vector3 pos;
                uint32_t info;
                if (FUN_00b97720(&pos, context, flag, rangeC.x, rangeC.y, rangeD.x, rangeD.y, f44,
                                 heightLo, heightHi, rangeF.x, rangeF.y, f40, flags, &info, u, b2)) {
                    if (num > 1) {
                        if (f1c > 1.5258789e-05f && stepRange.y > f1c) f1c = stepRange.y;
                        if (f24 > 1.5258789e-05f && stepRange.y > f24) f24 = stepRange.y;
                        if (f18 > 1.5258789e-05f && stepRange.y > f18) f18 = stepRange.y;
                    }
                    g_SpotGrid.AdjustPosition(pos, f1c, f24, f18);
                    Vector3 center = pos;

                    for (uint32_t k = 0; k < num; k++) {
                        Vector3 up = planet->GetSurfaceNormal(pos);
                        Vector3 facing = OrthogonalVector(up);
                        Matrix3 rot;
                        rot = Matrix3FromAxisAngle(up, (float)RandomDoubleUniform(g_SpotMaxTwist));
                        facing = facing * rot;
                        Quaternion orientation;
                        orientation = QuaternionFromFacingAndUp(facing, up);
                        uint32_t instanceID = instanceOverride;
                        if (instanceID == 0) instanceID = ids[i];
                        bool ok = FUN_00b94090(pos, orientation, typeA, typeB, instanceID, 0, extra);
                        pos = planet->MakeRandomWorldPosition(pos, stepRange.x, stepRange.y);
                        if (ok) placed++;
                    }
                    if (num > 0 && list->HasProperty(0xbb64b481)) {
                        Property* prop = list->GetPropertyObject(0xbb64b481);
                        FUN_00b9aa10(center, prop->GetItems(), prop->GetItemCount(), ids[i]);
                    }
                }
            }
        }
    }
    return placed;
}

// =======================================================================================
// FUN_00b9bb40: place one city described by a CityInfo (called by 0xb9c5b0 through the
// wrapper's +0x30 pointer).  Removes the old noun, rebuilds the surface position and the
// city object, and either registers a spawn marker + starts the city effect (in civ mode,
// or when the old city was already placed) or feeds a zeroed marker to the spawn callback.
// =======================================================================================

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }
void* operator new(size_t size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);

// 3x3 matrix whose out-of-line copy constructor is 0x0041cb40; assignment is the implicit
// memberwise copy (the retail code copies the 36 bytes inline).
struct Matrix3Copy {
    float m[3][3];
    __forceinline Matrix3Copy() {}
    Matrix3Copy(const Matrix3Copy& other);   // 0x0041cb40
};

// Quaternion with the float-wise copy constructor the retail build used (movss copies).
struct QuatSP {
    float x, y, z, w;
    __forceinline QuatSP() {}
    __forceinline QuatSP(const QuatSP& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};

extern Vector3     g_ZeroVector;         // 0x0168889c
extern Matrix3Copy g_IdentityMatrix3;    // 0x01688958
extern float       g_DefaultSurface[4];  // 0x0156bfe0

struct cSPTransform {
    uint16_t    mFlags;              // +0x00
    uint16_t    mModificationCount;  // +0x02
    Vector3     mTranslation;        // +0x04
    float       mScale;              // +0x10
    Matrix3Copy mRotation;           // +0x14

    __forceinline cSPTransform()
        : mFlags(0), mModificationCount(0), mTranslation(g_ZeroVector), mScale(1.0f),
          mRotation(g_IdentityMatrix3)
    {
    }
    __forceinline void SetTranslation(Vector3 v)
    {
        mTranslation = v;
        mFlags |= 4;
        mModificationCount++;
    }
    __forceinline void SetRotation(const Matrix3Copy& m)
    {
        mRotation = m;
        mFlags |= 2;
        mModificationCount++;
    }
};

Matrix3Copy* QuaternionToMatrixSP(Matrix3Copy* dst, const QuatSP* q);   // 0x004a9b40

// Marker payload (cGameplayMarkerView::tMarker): +0x34 is reused here for the city object.
struct tMarker {
    int     mId;            // +0x00
    Vector3 mPosition;      // +0x04
    void*   mpUnk10;        // +0x10
    void*   mpOrientation;  // +0x14
    void*   mpArgument;     // +0x18
    int     mUnk1c;         // +0x1c
    float   mSurface[4];    // +0x20
    int     mStyle;         // +0x30
    void*   mpCity;         // +0x34
    int     mUnk38;         // +0x38
};

void FUN_00b90c50(tMarker* marker);   // 0x00b90c50

struct CityInfo {
    int        mPoliticalID;   // +0x00
    Vector3    mPosition;      // +0x04
    QuatSP     mOrientation;   // +0x10
    int        mContinent;     // +0x20
    bool       mbPlaced;       // +0x24
    bool       mb25;           // +0x25
    uint8_t    pad26[2];       // +0x26
    int        mTerrainKind;   // +0x28
    uint32_t   pad2c;          // +0x2c
    bool       mb30;           // +0x30
    bool       mbNearWater;    // +0x31
    uint8_t    pad32[2];       // +0x32
    int        mStyle;         // +0x34
    void*      mpNoun;         // +0x38
    int        mEmpireID;      // +0x3c

    void* GetNoun();           // 0x00a1ad10  (returns this->mpNoun)
    void  SetNoun(void* p);    // 0x00ae38f0  (ref-counted assignment)
};

struct cGameNounManager { void RemoveNoun(void* noun); };   // 0x00b225d0

// Vtable-only views used for the ownership probe in the prologue.
#define VIRT(n) virtual void v##n();
struct INounVtbl {
    VIRT(00) VIRT(04) VIRT(08) VIRT(0c) VIRT(10) VIRT(14) VIRT(18) VIRT(1c)
    VIRT(20) VIRT(24) VIRT(28) VIRT(2c) VIRT(30) VIRT(34) VIRT(38) VIRT(3c)
    VIRT(40) VIRT(44) VIRT(48) VIRT(4c) VIRT(50) VIRT(54) VIRT(58) VIRT(5c)
    VIRT(60) VIRT(64) VIRT(68) VIRT(6c) VIRT(70) VIRT(74) VIRT(78) VIRT(7c)
    VIRT(80) VIRT(84) VIRT(88) VIRT(8c) VIRT(90) VIRT(94) VIRT(98) VIRT(9c)
    VIRT(a0) VIRT(a4) VIRT(a8)
    virtual void* GetSub();   // +0xac
};
struct ISubVtbl {
    VIRT(00) VIRT(04) VIRT(08) VIRT(0c) VIRT(10) VIRT(14) VIRT(18) VIRT(1c)
    VIRT(20) VIRT(24) VIRT(28) VIRT(2c) VIRT(30) VIRT(34) VIRT(38) VIRT(3c)
    VIRT(40) VIRT(44)
    virtual bool Check();     // +0x48
};
#undef VIRT

class cCivModeStrategy { public: void CheckEvents(); };   // 0x00cf9ba0
cCivModeStrategy* GetCivModeStrategy();                   // 0x00cf74c0

struct cTriggerMgr { uint8_t pad[0x2c]; int mMode; };
cTriggerMgr* GetTriggerMgr();                             // 0x00b3d4d0

struct IManager {
    virtual void f0(); virtual void f4(); virtual void f8(); virtual void fc();
    virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1c();
    virtual void f20(); virtual void f24(); virtual void f28();
    virtual bool GetEntry(uint32_t key, int a, void* value);   // +0x2c
};
IManager* EffectsManager();                               // 0x0067ddd0

struct IEffect {
    virtual void f0();             // +0x00
    virtual void Release();        // +0x04
    virtual void SetFlag0(int);    // +0x08
    virtual void fc();             // +0x0c
    virtual void f10();            // +0x10
    virtual void f14();            // +0x14
    virtual void SetTransform(void*);  // +0x18
};

class SimSingleton {
public:
    uint8_t pad[0xc8];
    SimSingleton();   // 0x00ae5c30
    tMarker* AddMarker(void* callback, int empire, const Vector3* pos, int kind,
                       uint32_t typeID, CityInfo* info, const QuatSP* orient, int flag);   // 0x00ae49d0
    static SimSingleton* sInstance;   // 0x0167a60c
    __forceinline static SimSingleton* Get()
    {
        if (!sInstance)
            sInstance = new("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
        return sInstance;
    }
};

void*       FUN_00b998a0(CityInfo* info);   // 0x00b998a0 (create the city object)
uint32_t    FUN_00bef920(int terrainKind);  // 0x00bef920
uint32_t    FUN_00bebc90(int a, int style); // 0x00bebc90

// @ 0x00b9bb40
void FUN_00b9bb40(CityInfo* info)
{
    bool flag = false;
    void* noun = info->GetNoun();
    if (noun) {
        void* sub = ((INounVtbl*)noun)->GetSub();
        if (sub && ((ISubVtbl*)((char*)sub + 0x34))->Check())
            flag = true;
        ((cGameNounManager*)NounManager())->RemoveNoun(noun);
        info->SetNoun(0);
    }

    uint32_t type = FUN_00bebc90(FUN_00bef920(info->mTerrainKind), info->mStyle);
    int kind = info->mbNearWater ? ((info->mb25 == 0) + 2) : (info->mb25 == 0);

    Vector3 pos = info->mPosition;
    info->mPosition = PlanetModel()->DirectionToSurfacePosition(pos);
    QuatSP orient = info->mOrientation;

    void* city = FUN_00b998a0(info);

    GetCivModeStrategy()->CheckEvents();
    int mode = GetTriggerMgr()->mMode;
    if (mode == 1 || mode == 2 || flag) {
        Vector3 markerPos = info->mPosition;
        tMarker* marker = SimSingleton::Get()->AddMarker(
            (void*)FUN_00b90c50, info->mEmpireID, &markerPos, kind, type, info, &orient, 0);
        marker->mpCity = city;

        IManager* mgr = EffectsManager();
        void* effect = 0;
        if (effect != 0) {
            effect = 0;
            ((IEffect*)effect)->Release();
        }
        if (mgr->GetEntry(0x74bc5e71, 0, &effect)) {
            cSPTransform transform;
            transform.SetTranslation(info->mPosition);
            Matrix3Copy rot;
            transform.SetRotation(*QuaternionToMatrixSP(&rot, &orient));
            ((IEffect*)effect)->SetTransform(&transform);
            ((IEffect*)effect)->SetFlag0(0);
        }
        if (effect != 0)
            ((IEffect*)effect)->Release();
    } else {
        tMarker marker;
        marker.mId = -1;
        marker.mPosition.x = 0.0f;
        marker.mPosition.y = 0.0f;
        marker.mPosition.z = 0.0f;
        marker.mpUnk10 = 0;
        marker.mpOrientation = 0;
        marker.mpArgument = 0;
        marker.mUnk1c = 0;
        marker.mSurface[0] = g_DefaultSurface[0];
        marker.mSurface[1] = g_DefaultSurface[1];
        marker.mSurface[2] = g_DefaultSurface[2];
        marker.mSurface[3] = g_DefaultSurface[3];
        marker.mStyle = 0;
        marker.mpCity = city;
        marker.mUnk38 = 0;
        FUN_00b90c50(&marker);
    }
}
