// Slice s00fbe7d0: SP::cTerrainStateMgr::Initialize (0x00fbe7d0, 1629 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same module as the other cTerrainStateMgr slices; no EH, no cookie).
//
// Loads the planet's terrain state parameters from its property list (mpPlanetProps, +0x5b0):
// water/fog/atmosphere floats and colours (each one only when the property exists and has the
// expected type), the Vector3/Vector4/Vector2 colour tables, and finally the five vector-valued
// array properties (4 Vector3 tables, 3 Vector2 tables and 1 more Vector3 table) which are
// assigned into the manager's eastl vectors.
// Member offsets are the retail ones (see s00fc03c0 for the same class).
#include "types.h"

struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(const Vector2& v) : x(v.x), y(v.y) {}
};
struct Vector3 { float x, y, z; };
struct Vector4 { float x, y, z, w; };

// App::Property (0x14 bytes): type at +0x12.
struct Property {
    uint32_t pad00[4];
    uint16_t pad10;
    uint16_t mnType;
    float* GetFloat();                        // 0x0041ea70
};
struct cPropertyList {
    virtual void AddRef();
    virtual void Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20();
    virtual bool GetProperty(uint32_t id, Property** out);   // +0x24
};

bool GetPropertyAsVector2(cPropertyList* list, uint32_t id, Vector2* out);                          // 0x006a10c0
bool GetPropertyAsVector3(cPropertyList* list, uint32_t id, Vector3* out);                          // 0x006a1110
bool GetPropertyAsVector4(cPropertyList* list, uint32_t id, Vector4* out);                          // 0x006a1160
bool GetPropertyArrayVector2(cPropertyList* list, uint32_t id, int* count, Vector2** data);         // 0x006a0920
bool GetPropertyArrayVector3(cPropertyList* list, uint32_t id, int* count, Vector3** data);         // 0x006a0990

template <class T> struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
};

struct AssignTag { AssignTag() {} };   // eastl tag type with a user constructor (nothing is stored)

// eastl::vector<Vector3, sp_vector_allocator> (20 bytes) and the Vector2 flavour.
struct Vector3Array {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator[2];
    void DoAssign(Vector3* first, Vector3* last, AssignTag tag);   // 0x0056fee0
    void assign(Vector3* first, Vector3* last) { DoAssign(first, last, AssignTag()); }
};
struct Vector2Array {
    Vector2* mpBegin;
    Vector2* mpEnd;
    Vector2* mpCapacity;
    uint32_t mAllocator[2];
    void DoAssign(Vector2* first, Vector2* last, AssignTag tag);   // 0x00fbdf80
    void assign(Vector2* first, Vector2* last) { DoAssign(first, last, AssignTag()); }
};

extern uint32_t gTerrainVector3ArrayIDs[4];   // 0x014911c0

class cTerrainStateMgr {
public:
    uint32_t pad000[0xb4 / 4];
    Vector4 m0b4;                  // +0x0b4
    uint32_t pad0c4;
    Vector3 m0c8;                  // +0x0c8
    Vector3 m0d4;                  // +0x0d4
    Vector3 m0e0;                  // +0x0e0
    Vector3 m0ec;                  // +0x0ec
    Vector3 m0f8;                  // +0x0f8
    Vector3 m104;                  // +0x104
    Vector4 m110;                  // +0x110
    float m120;                    // +0x120
    float m124;                    // +0x124
    Vector2Array m128;             // +0x128
    Vector2 m13c;                  // +0x13c
    float m144;                    // +0x144
    float m148;                    // +0x148
    float m14c;                    // +0x14c
    float m150;                    // +0x150
    float m154;                    // +0x154
    Vector3Array m158[4];          // +0x158
    Vector2Array m1a8;             // +0x1a8
    Vector3Array m1bc;             // +0x1bc
    Vector2Array m1d0;             // +0x1d0
    uint32_t pad1e4;
    float m1e8;                    // +0x1e8
    float m1ec;                    // +0x1ec
    float m1f0;                    // +0x1f0
    uint32_t pad1f4;
    float m1f8;                    // +0x1f8
    float m1fc;                    // +0x1fc
    float m200;                    // +0x200
    float m204;                    // +0x204
    float m208;                    // +0x208
    uint32_t pad20c[4];
    Vector3 m21c;                  // +0x21c
    Vector3 m228;                  // +0x228
    Vector3 m234;                  // +0x234
    Vector3 m240;                  // +0x240
    Vector3 m24c;                  // +0x24c
    Vector3 m258;                  // +0x258
    uint32_t pad264[(0x5b0 - 0x264) / 4];
    AutoRefCount<cPropertyList> mpPlanetProps;   // +0x5b0

    void Initialize();
};

// Reads a float property when it exists and has the float type (inline in the original).
inline void ReadFloat(cPropertyList* list, uint32_t id, float& dst)
{
    Property* prop;
    if (list && list->GetProperty(id, &prop) && prop->mnType == 0xd)
        dst = *prop->GetFloat();
}

// @ 0x00fbe7d0
void cTerrainStateMgr::Initialize()
{
    Vector2 range;

    ReadFloat(mpPlanetProps.mpObject, 0x257035a, m1f8);
    ReadFloat(mpPlanetProps.mpObject, 0x2570386, m1fc);
    ReadFloat(mpPlanetProps.mpObject, 0x2570391, m200);
    ReadFloat(mpPlanetProps.mpObject, 0x257039b, m204);
    ReadFloat(mpPlanetProps.mpObject, 0x25703a4, m208);

    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x25703ad, &m21c);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x25703b9, &m228);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x25703c1, &m234);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x25703cc, &m240);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x25703d6, &m24c);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x25703e1, &m258);

    ReadFloat(mpPlanetProps.mpObject, 0x23227bd, m1ec);
    ReadFloat(mpPlanetProps.mpObject, 0x60ae1385, m1f0);
    ReadFloat(mpPlanetProps.mpObject, 0x1c387e7, m120);
    ReadFloat(mpPlanetProps.mpObject, 0x1c387f2, m124);

    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x87c2473f, &m0c8);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x7cb9e01a, &m0e0);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0xdafa9ed3, &m0f8);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x1331b443, &m0d4);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0xe5ac96bc, &m0ec);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x1ce679bf, &m104);
    GetPropertyAsVector4(mpPlanetProps.mpObject, 0x54b6d2b6, &m110);
    GetPropertyAsVector4(mpPlanetProps.mpObject, 0x31e1d79, &m0b4);

    ReadFloat(mpPlanetProps.mpObject, 0xa14ad299, m0b4.w);

    if (GetPropertyAsVector2(mpPlanetProps, 0x10ebd9e, &range)) {
        m13c.x = range.x;
        m13c.y = range.y;
    }

    ReadFloat(mpPlanetProps.mpObject, 0x17eda5f, m148);
    ReadFloat(mpPlanetProps.mpObject, 0x17eda6b, m144);
    ReadFloat(mpPlanetProps.mpObject, 0x2c66e2c5, m14c);
    ReadFloat(mpPlanetProps.mpObject, 0x2c66e2c6, m150);
    ReadFloat(mpPlanetProps.mpObject, 0x58d751bc, m154);
    ReadFloat(mpPlanetProps.mpObject, 0x6b3936a8, m1e8);

    int count;
    Vector3* pVec3;
    Vector2* pVec2;
    for (int i = 0; i < 4; ++i) {
        if (GetPropertyArrayVector3(mpPlanetProps, gTerrainVector3ArrayIDs[i], &count, &pVec3))
            m158[i].assign(pVec3, pVec3 + count);
    }

    if (GetPropertyArrayVector2(mpPlanetProps, 0xecdf0df2, &count, &pVec2))
        m1a8.assign(pVec2, pVec2 + count);
    if (GetPropertyArrayVector3(mpPlanetProps, 0x8e35c36e, &count, &pVec3))
        m1bc.assign(pVec3, pVec3 + count);
    if (GetPropertyArrayVector2(mpPlanetProps, 0x57a0c0c2, &count, &pVec2))
        m1d0.assign(pVec2, pVec2 + count);
    if (GetPropertyArrayVector2(mpPlanetProps, 0x7578caba, &count, &pVec2))
        m128.assign(pVec2, pVec2 + count);
}
