// Slice s004f9570: force-field grid accessors (unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast).
#include "types.h"

struct Vector3 {
    float x, y, z;
    const float& operator[](int i) const { return ((const float*)this)[i]; }
};

struct FieldAccumulator { void Add(const void* c); };

// 128-byte structure-of-arrays of spherical fields.
struct SphereFields {
    float mX[4];
    float mY[4];
    float mZ[4];
    float mRadiusSq[4];
    float mInvRadiusSq[4];
    float mStrength[4];
    float mScaledStrength[4];
    uint32_t mId[4];
    void Apply(const Vector3& position, FieldAccumulator* acc);   // 0x004f8420
};

// Used by the original inline helpers: reproduce the unused stack slots that the declined
// inlined callees left in the /Od frame.
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

// The element count lives two dwords before the returned pointer (sp_vector header).
inline uint32_t Count(SphereFields* p) { const uint32_t* q = (const uint32_t*)p; return q[-2]; }

struct ForceGrid {
    char pad00[0x20];
    Vector3 mV20;                 // 0x20
    Vector3 mV2c;                 // 0x2c
    Vector3 mV38;                 // 0x38
    char pad44[0x08];             // 0x44..0x4b
    int mField4c;                 // 0x4c
    int mField50;                 // 0x50
    SphereFields** mppTable;      // 0x54

    SphereFields* GetField(const Vector3& position);              // 0x004f8f70
    void Apply(const Vector3& position, FieldAccumulator* acc);
    bool GetBounds(Vector3* pMin, Vector3* pMax);
    Vector3* GetVec38(Vector3* out);
};

// @ 0x004f9570
void ForceGrid::Apply(const Vector3& position, FieldAccumulator* acc)
{
    SphereFields* p = GetField(position);
    if (p) {
        ScratchSlots<23>();
        uint32_t n = Count(p);
        for (uint32_t i = 0; i < n; ++i)
            (p + i)->Apply(position, acc);
    }
}

// @ 0x004f95e0
bool ForceGrid::GetBounds(Vector3* pMin, Vector3* pMax)
{
    *pMin = mV20;
    *pMax = mV2c;
    return (*pMin)[0] <= (*pMax)[0];
}

// @ 0x004f9660
Vector3* ForceGrid::GetVec38(Vector3* out)
{
    const Vector3& v = mV38;
    out->x = v.x;
    out->y = v.y;
    out->z = v.z;
    return out;
}
