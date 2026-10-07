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
