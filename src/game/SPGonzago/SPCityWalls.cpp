// src/game/SPGonzago/SPCityWalls.cpp -- migrated from slice(s) s00beb6d0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCityWalls.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cSpatialObject.h"
#include "SP/cVarListSerializer.h"
#include "cSPVector3.h"
#include "SP/cCityTerritory.h"
#include "SP/cCityWalls.h"
#include <math.h>

// ---- items of slice s00beb6d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct SpVector {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint8_t  mAllocator[8];
};
struct ISub34 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual Vector3* v2c();                       // 0x2c  position
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
    virtual void v5c(void* arg);                  // 0x5c
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual float v70();                          // 0x70
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
    virtual void v90();
    virtual void v94(void* arg);                  // 0x94
};
struct cCityWalls {
    void*    vtbl_a;             // 0x000
    void*    vtbl_b;             // 0x004
    uint8_t  pad_008[0x2c - 8];
    void*    vfptr_rc;           // 0x02c
    uint8_t  pad_030[0x34 - 0x30];
    uint8_t  sub34[1];           // 0x034  cSpatialObject
    uint8_t  pad_035[0x10c - 0x35];
    uint32_t field_10c;          // 0x10c
    SpVector mDockSlots;         // 0x110
    SpVector field_124;          // 0x124
    uint8_t  pad_138[0x198 - 0x138];
    SpVector field_198;          // 0x198
    uint8_t  pad_1ac[0x254 - 0x1ac];
    uint32_t field_254;          // 0x254
    float    mInnerRadius;       // 0x258
    float    mOuterRadius;       // 0x25c
    float    field_260;          // 0x260
    uint32_t field_264;          // 0x264  cCity*
    uint8_t  pad_268[0x344 - 0x268];
    uint32_t mStyle;             // 0x344
    uint8_t  pad_348[0x354 - 0x348];
    uint32_t field_354;          // 0x354

    ISub34* Sub() const { return (ISub34*)sub34; }
    ISub34* CitySub() const { return (ISub34*)(field_264 + 0x120); }

    void    FUN_00bec060();                       // 0x00bec060
    uint32_t PointInsideWall(const Vector3& p);            // 0x00bec0f0
    uint32_t PointInsideInnerWall(const Vector3& p);       // 0x00bec140
    Vector3 GetCenter();                                  // 0x00bec190
    Vector3 GetInnerGatePosition(int idx);                // 0x00bec1c0
    Vector3 GetGatePosition(int idx);                     // 0x00bec2d0
    Vector3* RequestGatePosition(Vector3* out, int idx, int kind);  // 0x00bec460
    Vector3* FindNearestPosition(Vector3* out, const Vector3* ref, int kind); // 0x00bec660
    void    UpdateGatePosition(int idx);                  // 0x00bec790
    bool GetIsWallBuilt();                                // 0x00bec860
};
// ---- items of slice s00beb6d0 end

// @ 0x00bec140
uint32_t cCityWalls::PointInsideInnerWall(const Vector3& p)
{
    Vector3* c = Sub()->v2c();
    float dx = p.x - c->x;
    float dy = p.y - c->y;
    float dz = p.z - c->z;
    if ((float)sqrt((double)(dx * dx + dy * dy + dz * dz)) < mInnerRadius)
        return true;
    return false;
}
