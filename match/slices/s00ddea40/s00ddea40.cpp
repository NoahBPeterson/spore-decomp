// Slice s00ddea40: 0x00DDEA40 (fastcall/thiscall, no stack args, 2240 bytes; the card's 2703 includes
// the unrelated next function at 0x00DDF300).
//
// Loads a set of camera/view tuning parameters: sets compiled-in defaults (members at +0x18..+0x3c,
// a few globals at 0x015a3000..0x015a30ac and 0x016a10c4/0x016a10dc), then overrides each from the
// owner's property list (this+0x10) when the property exists / is a float. Angle properties are
// converted from degrees to radians (x 0.017453292).
#include "types.h"

#pragma warning(disable: 4100 4700 4701 4244)

struct Property {
    void* mpData;        // +0x00
    uint32_t pad04;
    int mnItemCount;     // +0x08
    uint32_t pad0c;
    uint16_t mnFlags;    // +0x10 (0x30 = array)
    uint16_t mnType;     // +0x12

    float* GetFloat();   // 0x0041ea70
    void* GetItems()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
};

extern const float kDefaultFloatValue;  // 0x015d1168

__forceinline const float* GetValueFloat(Property* p)
{
    return (p->mnType == 0xd || p->mnType == 0x10) ? (const float*)p->GetItems() : &kDefaultFloatValue;
}

class cPropertyList {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void SetProperty(uint32_t id, const Property* p);
    virtual int RemoveProperty(uint32_t id);
    virtual bool HasProperty(uint32_t id);                       // 0x1c
    virtual bool GetPropertyAlt(uint32_t id, Property*& result); // 0x20
    virtual bool GetProperty(uint32_t id, Property*& result);    // 0x24
    virtual Property* GetPropertyObject(uint32_t id);            // 0x28
};

struct Vector3 { float x, y, z; };
inline Vector3 MakeVector3(float x, float y, float z) { Vector3 v; v.x = x; v.y = y; v.z = z; return v; }
struct Vector2 { float x, y; };

#pragma warning(disable : 4035)   // result returned in eax
inline int FloatToInt(float f)
{
    __asm cvtss2si eax, f
}

extern float gF3000;  // 0x015a3000
extern float gF3004;  // 0x015a3004
extern float gF3008;  // 0x015a3008
extern float gF300c;  // 0x015a300c
extern float gF3010;  // 0x015a3010
extern float gF3014;  // 0x015a3014
extern float gF3018;  // 0x015a3018
extern float gF301c;  // 0x015a301c
extern float gF3020;  // 0x015a3020
extern float gF3024;  // 0x015a3024
extern float gF3028;  // 0x015a3028
extern float gF302c;  // 0x015a302c
extern float gF3030;  // 0x015a3030
extern Vector3 gV3048;  // 0x015a3048
extern Vector3 gV3054;  // 0x015a3054
extern int gI3060;  // 0x015a3060
extern float gF3064;  // 0x015a3064
extern float gF306c;  // 0x015a306c
extern float gF3070;  // 0x015a3070
extern float gF3078;  // 0x015a3078
extern float gF307c;  // 0x015a307c
extern float gF3080;  // 0x015a3080
extern float gF3084;  // 0x015a3084
extern float gF3088;  // 0x015a3088
extern float gF3094;  // 0x015a3094
extern float gF30ac;  // 0x015a30ac
extern Vector2 gV308c;  // 0x015a308c
extern float gF16a10c4;  // 0x016a10c4
extern float gF16a10dc;  // 0x016a10dc

class cViewConfig {
public:
    void LoadDefaultsAndProperties();

    char pad00[0x10];
    cPropertyList* mpPropList;     // +0x10
    float f14;                     // +0x14
    float f18;                     // +0x18
    float f1c;                     // +0x1c
    char pad20[8];
    float f28;                     // +0x28
    float f2c;                     // +0x2c
    int   n30;                     // +0x30
    float f34;                     // +0x34
    float f38;                     // +0x38
    float f3c;                     // +0x3c
};

// "if the property exists, read its float value" (the inlined GetPropertyAsFloat)
#define HAS_FLOAT(id) (mpPropList->HasProperty(id))

static __forceinline bool ReadFloat(cPropertyList* list, uint32_t id, float& out)
{
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 0xd) {
        out = *prop->GetFloat();
        return true;
    }
    return false;
}

void cViewConfig::LoadDefaultsAndProperties()
{
    float a, b, x, y;
    f34 = 0.001f;
    f28 = f2c = 1.0f;
    n30 = FloatToInt(20.0f);
    gV3048 = MakeVector3(0.0f, 0.0f, -100.0f);
    gF3064 = 0.01f;
    gV3054 = MakeVector3(0.0f, 0.0f, -100.0f);
    gI3060 = FloatToInt(20.0f);
    f18 = f1c = 1.0f;

    if (mpPropList->HasProperty(0x4a2f63fe))
        f18 = *GetValueFloat(mpPropList->GetPropertyObject(0x4a2f63fe));
    if (mpPropList->HasProperty(0xa8fa45ba))
        f1c = *GetValueFloat(mpPropList->GetPropertyObject(0xa8fa45ba));
    if (mpPropList->HasProperty(0x15e688f))
        f14 = *GetValueFloat(mpPropList->GetPropertyObject(0x15e688f));
    if (mpPropList->HasProperty(0xc7c4fb)) {
        gF3088 = *GetValueFloat(mpPropList->GetPropertyObject(0xc7c4fb));
        gF3094 = *GetValueFloat(mpPropList->GetPropertyObject(0xc7c4fb));
    }
    if (mpPropList->HasProperty(0xc7c4fc)) {
        Vector2 v = gV308c;
        v.y = *GetValueFloat(mpPropList->GetPropertyObject(0xc7c4fc)) * 0.017453292f;
        gV308c = v;
    }
    if (mpPropList->HasProperty(0xc7c4fd)) {
        Vector2 v = gV308c;
        v.x = *GetValueFloat(mpPropList->GetPropertyObject(0xc7c4fd)) * 0.017453292f;
        gV308c = v;
    }
    if (mpPropList->HasProperty(0xfe243b))
        a = *GetValueFloat(mpPropList->GetPropertyObject(0xfe243b)) * 0.017453292f;
    b = a;
    if (mpPropList->HasProperty(0xfe243f))
        b = *GetValueFloat(mpPropList->GetPropertyObject(0xfe243f)) * 0.017453292f;
    gF307c = b;
    gF3078 = a;
    gF30ac = 0.0f;

    ReadFloat(mpPropList, 0x6712adaa, gF3000);
    ReadFloat(mpPropList, 0x1fa53607, gF3004);
    ReadFloat(mpPropList, 0xa62b9ae7, gF3008);
    ReadFloat(mpPropList, 0xef6ba08a, gF16a10dc);
    ReadFloat(mpPropList, 0x117596fe, gF300c);
    ReadFloat(mpPropList, 0x1f5e6d86, gF3010);
    ReadFloat(mpPropList, 0x8d59f19f, gF3014);
    ReadFloat(mpPropList, 0x334db042, gF3018);
    ReadFloat(mpPropList, 0x3510083b, gF301c);
    ReadFloat(mpPropList, 0x327c1cab, gF3020);
    ReadFloat(mpPropList, 0x1102b20, f38);
    ReadFloat(mpPropList, 0x1102b2f, f3c);

    gF3080 = 800.0f;
    gF3084 = 1000.0f;

    ReadFloat(mpPropList, 0x12d3da88, x);
    ReadFloat(mpPropList, 0x6755710f, y);
    gF3070 = y * 0.017453292f;
    gF306c = x * 0.017453292f;

    ReadFloat(mpPropList, 0x23970b2e, gF3024);
    ReadFloat(mpPropList, 0xaa8d130b, gF3028);
    ReadFloat(mpPropList, 0xab7ecaa, gF302c);
    ReadFloat(mpPropList, 0x23e13c2e, gF3030);
    ReadFloat(mpPropList, 0xb7cc369a, gF16a10c4);
}
