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
#include <math.h>
#include <string.h>

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

// eastl float / Vector3 vectors (20 bytes: begin/end/capacity + 8 allocator bytes).
struct FloatVector {
    float* mpBegin;                            // +0x00
    float* mpEnd;                              // +0x04
    float* mpCapacity;                         // +0x08
    uint32_t mAllocator[2];                    // +0x0c
    void VectorPushBack(const float* value);   // 0x00455660
    void erase(float* first, float* last);     // 0x0050f740
    void Resize(int count, uint32_t* alloc);   // 0x004aa350
    void operator=(const FloatVector& src);    // 0x0050d4e0
};
struct Vector3Vector {
    Vector3* mpBegin;                          // +0x00
    Vector3* mpEnd;                            // +0x04
    Vector3* mpCapacity;                       // +0x08
    uint32_t mAllocator[2];                    // +0x0c
    void DoInsertValue(Vector3* pos, const Vector3* value);   // 0x004b5ad0
    void erase(Vector3* first, Vector3* last);                 // 0x0050f740
    void operator=(const Vector3Vector& src);                 // 0x00473500
};

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
    uint8_t m264;                  // +0x264  ramp-dirty flag
    uint8_t pad265[3];
    float m268;                    // +0x268
    float m26c;                    // +0x26c
    float m270;                    // +0x270
    float m274;                    // +0x274
    float m278;                    // +0x278
    float m27c;                    // +0x27c
    float m280;                    // +0x280
    float m284;                    // +0x284
    float m288;                    // +0x288
    float m28c;                    // +0x28c
    float m290;                    // +0x290
    float m294;                    // +0x294
    FloatVector m298;              // +0x298
    Vector3Vector m2ac;            // +0x2ac
    uint32_t pad2c0[5];
    float m2d4;                    // +0x2d4
    uint32_t pad2d8[5];
    float m2ec;                    // +0x2ec
    float m2f0;                    // +0x2f0
    uint32_t pad2f4[(0x3cc - 0x2f4) / 4];
    float m3cc;                    // +0x3cc
    float m3d0;                    // +0x3d0
    float m3d4;                    // +0x3d4
    uint32_t pad3d8[(0x42c - 0x3d8) / 4];
    float m42c;                    // +0x42c
    float m430;                    // +0x430
    float m434;                    // +0x434
    uint32_t pad438[(0x5b0 - 0x438) / 4];
    AutoRefCount<cPropertyList> mpPlanetProps;   // +0x5b0

    void Initialize();
    void FUN_00fbee30();                         // 0x00fbee30
    void FUN_00fbf1c0(Vector3Vector* in, int unused);            // 0x00fbf1c0
    Vector3Vector* FUN_00fbf430(Vector3Vector* out, char build); // 0x00fbf430
    FloatVector* FUN_00fbf3d0(FloatVector* out); // 0x00fbf3d0
    void UpdateLightColors(float phase, bool flag);              // 0x00fbc770
    void ExportRampTextureEx();                                  // 0x00fbbc00
};

// Owner object touched at the end of FUN_00fbf1c0 (reached through mOwner, this[0]).
struct cRampOwner {
    uint32_t pad000[0x494 / 4];
    float m494; float m498; float m49c; float m4a0; float m4a4; float m4a8;
    float m4ac; float m4b0; float m4b4; float m4b8; float m4bc; float m4c0;
    float m4c4; float m4c8; float m4cc; float m4d0; float m4d4; float m4d8;
    float m4dc; float m4e0; float m4e4; float m4e8; float m4ec; float m4f0;
};

extern const float g_16d6710;                  // 0x016d6710  base sample point
extern const float g_16d6714;                  // 0x016d6714
extern const float g_16d6718;                  // 0x016d6718
extern const float g_1432214;                  // 0x01432214  1/31
extern const float g_1471064;                  // 0x01471064
extern const float g_1485720;                  // 0x01485720  _HK_REAL_ONE

// Returns a colour-ramp sample for `phase` (0..1) into `out`.
Vector3* FUN_00fb8dd0(cTerrainStateMgr* self, Vector3* out, float phase);  // 0x00fb8dd0
Vector3* FUN_00fb8fc0(Vector3* out, float x, float y, float z, float a, float b);  // 0x00fb8fc0
Vector3* FUN_00fb90b0(Vector3* out, float x, float y, float z, float a, float b);  // 0x00fb90b0
void FUN_00fb9ad0(Vector3* out);               // 0x00fb9ad0
void FUN_00fb9ca0(Vector3* out);               // 0x00fb9ca0
void FUN_00fb9500(int flag);                   // 0x00fb9500
void FUN_004aa350(FloatVector* out, int count, uint32_t* alloc);   // 0x004aa350

// @ 0x00fbee30
void cTerrainStateMgr::FUN_00fbee30()
{
    Vector3 sample;
    Vector3 out;

    FUN_00fb9ad0(&sample);                     // 0x00fb9ad0
    m268 = sample.x;
    m26c = sample.y;
    m270 = sample.z;
    FUN_00fb9ca0(&sample);                     // 0x00fb9ca0
    m274 = sample.x;
    m278 = sample.y;
    m27c = sample.z;
    FUN_00fb9500(1);                           // 0x00fb9500
    m280 = m42c;
    m284 = m430;
    m288 = m434;
    UpdateLightColors(g_1471064, true);        // 0x00fbc770
    m28c = m3cc;
    m290 = m3d0;
    m294 = m3d4;

    Vector3 base;
    base.x = g_16d6710;
    base.y = g_16d6714;
    base.z = g_16d6718;

    FloatVector scalars;
    scalars.mpBegin = 0;
    scalars.mpEnd = 0;
    scalars.mpCapacity = 0;
    Vector3Vector points;
    points.mpBegin = 0;
    points.mpEnd = 0;
    points.mpCapacity = 0;

    for (int i = 0; i < 0x20; ++i) {
        float t = (float)i * g_1432214;
        FUN_00fb8dd0(this, &out, g_1485720 - t);   // 0x00fb8dd0
        float dx = base.x - out.x;
        float dy = base.y - out.y;
        float dz = base.z - out.z;
        float dist = sqrtf((dx * dx) + (dy * dy) + (dz * dz));
        if (m2f0 < dist) {
            scalars.VectorPushBack(&t);             // 0x00455660
            points.DoInsertValue(points.mpEnd, &out);   // 0x004b5ad0
            base = out;
        }
    }

    if (((char*)scalars.mpEnd - (char*)scalars.mpBegin & 0xfffffffc) == 0) {
        float zero = 0.0f;
        scalars.VectorPushBack(&zero);              // 0x00455660
        Vector3* p = FUN_00fb8dd0(this, &out, g_1485720);   // 0x00fb8dd0
        points.DoInsertValue(points.mpEnd, p);      // 0x004b5ad0
        float one = g_1485720;
        scalars.VectorPushBack(&one);               // 0x00455660
        p = FUN_00fb8dd0(this, &out, 0.0f);         // 0x00fb8dd0
        points.DoInsertValue(points.mpEnd, p);      // 0x004b5ad0
    }

    m298 = scalars;                                 // 0x0050d4e0
    m2ac = points;                                  // 0x00473500
}

// @ 0x00fbf1c0
void cTerrainStateMgr::FUN_00fbf1c0(Vector3Vector* in, int unused)
{
    if (m264) {
        m2ac.erase(m2ac.mpEnd, m2ac.mpCapacity);    // 0x0050f740
        int n = (int)((char*)in->mpEnd - (char*)in->mpBegin) / 0xc;
        for (int i = 0; i < n; ++i) {
            Vector3* v = &in->mpBegin[i];
            Vector3 sample;
            Vector3* p = FUN_00fb8fc0(&sample, v->x, v->y, v->z, m2d4, m2ec);   // 0x00fb8fc0
            m2ac.DoInsertValue(m2ac.mpEnd, p);      // 0x004b5ad0
        }
        // The ramp scalars share the argument vector's storage.
        m298.mpBegin = (float*)in->mpBegin;
        m298.mpEnd = (float*)in->mpEnd;
        m298.mpCapacity = (float*)in->mpCapacity;
        ExportRampTextureEx();                      // 0x00fbbc00
        cRampOwner* o = *(cRampOwner**)this;        // +0x00 owner
        o->m494 = 0.0f;  o->m4a4 = 0.0f;  o->m498 = 0.0f;
        o->m49c = g_1485720; o->m4a0 = g_1485720; o->m4a8 = 0.0f;
        o->m4ac = g_1485720; o->m4b0 = g_1485720; o->m4b4 = 0.0f;
        o->m4b8 = 0.0f; o->m4bc = g_1485720; o->m4c0 = g_1485720;
        o->m4c4 = 0.0f; o->m4c8 = 0.0f; o->m4cc = g_1485720;
        o->m4d0 = g_1485720; o->m4d4 = 0.0f; o->m4d8 = 0.0f;
        o->m4dc = g_1485720; o->m4e0 = g_1485720; o->m4e4 = 0.0f;
        o->m4e8 = 0.0f; o->m4ec = g_1485720; o->m4f0 = g_1485720;
    }
}

// @ 0x00fbf430
Vector3Vector* cTerrainStateMgr::FUN_00fbf430(Vector3Vector* out, char build)
{
    if (!build) {
        *out = m2ac;                                // 0x00473500
        return out;
    }
    Vector3Vector tmp;
    tmp.mpBegin = 0;
    tmp.mpEnd = 0;
    tmp.mpCapacity = 0;
    for (int i = 0; i < (int)((char*)m2ac.mpEnd - (char*)m2ac.mpBegin) / 0xc; ++i) {
        Vector3* v = &m2ac.mpBegin[i];
        Vector3 sample;
        Vector3* p = FUN_00fb90b0(&sample, v->x, v->y, v->z, m2d4, m2ec);   // 0x00fb90b0
        tmp.DoInsertValue(tmp.mpEnd, p);            // 0x004b5ad0
    }
    *out = tmp;                                     // 0x00473260
    return out;
}

// @ 0x00fbf3d0
#pragma function(memcpy)
FloatVector* cTerrainStateMgr::FUN_00fbf3d0(FloatVector* out)
{
    out->Resize((int)((char*)m298.mpEnd - (char*)m298.mpBegin) >> 2, m298.mAllocator);
    int bytes = (int)((char*)m298.mpEnd - (char*)m298.mpBegin);
    float* src = m298.mpBegin;
    memcpy(out->mpBegin, src, bytes);
    out->mpEnd = out->mpBegin + (bytes >> 2);
    return out;
}

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
