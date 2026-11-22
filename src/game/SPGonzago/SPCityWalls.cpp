// src/game/SPGonzago/SPCityWalls.cpp -- migrated from slice(s) s0132ea70, s00beb6d0 by tools/migrate/rewrite.py
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
#include <string.h>

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

// ---- items of slice s0132ea70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_name_mCenterAxis[];   // 0x014691f0
extern "C" char g_name_mpCity[];        // 0x01467e44
extern "C" char g_name_mpDock[];        // 0x014691e8
extern "C" char g_name_mWallSize[];     // 0x014691dc
extern "C" char g_name_mStyle[];        // 0x014691d4
extern "C" char g_name_mLevel[];        // 0x014691cc
extern "C" char g_name_mAppliedStamp[]; // 0x014691bc
extern "C" char g_name_mWallOffset[];   // 0x014691b0
extern "C" char g_fn692ca0[];   // 0x00692ca0 (shared: entries 0-2 f20)
extern "C" char e0_f24[];   // 0x00b6e3a0
extern "C" char e0_f28[];   // 0x00ac88c0
extern "C" char e0_f2c[];   // 0x006930f0
extern "C" char e0_f30[];   // 0x00695010
extern "C" char e0_f34[];   // 0x00b1fbf0
extern "C" char e0_f38[];   // 0x00acbba0
extern "C" char e1_f24[];   // 0x00ae9e00
extern "C" char e1_f28[];   // 0x00bca960
extern "C" char e1_f2c[];   // 0x00c2e4e0
extern "C" char e1_f30[];   // 0x00692fb0
extern "C" char e1_f34[];   // 0x00b6f550
extern "C" char e1_f38[];   // 0x00ac8050
extern "C" char e2_f24[];   // 0x00bed160
extern "C" char e2_f28[];   // 0x00bca960
extern "C" char e2_f2c[];   // 0x00c2e4e0
extern "C" char e2_f30[];   // 0x00692fb0
extern "C" char e2_f34[];   // 0x00b6f550
extern "C" char e2_f38[];   // 0x00ac8050
extern "C" char e3_f20[];   // 0x00572810
extern "C" char e3_f24[];   // 0x00572840
extern "C" char e3_f28[];   // 0x00692ff0
extern "C" char e3_f2c[];   // 0x00694ee0
extern "C" char e3_f30[];   // 0x00b1fbf0
extern "C" char e3_f34[];   // 0x0057cde0
extern "C" char e3_f38[];   // 0x00572810
extern "C" char e4_f20[];   // 0x00572810
extern "C" char e4_f24[];   // 0x00572840
extern "C" char e4_f28[];   // 0x00693090
extern "C" char e4_f2c[];   // 0x00694f00
extern "C" char e4_f30[];   // 0x00b1fbf0
extern "C" char e4_f34[];   // 0x00675ca0
extern "C" char e4_f38[];   // 0x00572810
extern "C" char e5_f20[];   // 0x00572810
extern "C" char e5_f24[];   // 0x00572840
extern "C" char e5_f28[];   // 0x00693090
extern "C" char e5_f2c[];   // 0x00694f00
extern "C" char e5_f30[];   // 0x00b1fbf0
extern "C" char e5_f34[];   // 0x00675ca0
extern "C" char e5_f38[];   // 0x00572810
extern "C" char e6_f20[];   // 0x00ac8750
extern "C" char e6_f24[];   // 0x00ac8780
extern "C" char e6_f28[];   // 0x00693090
extern "C" char e6_f2c[];   // 0x00694fa0
extern "C" char e6_f30[];   // 0x00b1fbf0
extern "C" char e6_f34[];   // 0x0057ce00
extern "C" char e6_f38[];   // 0x00ac8750
extern "C" char e7_f20[];   // 0x00572810
extern "C" char e7_f24[];   // 0x00572840
extern "C" char e7_f28[];   // 0x00692ff0
extern "C" char e7_f2c[];   // 0x00694ee0
extern "C" char e7_f30[];   // 0x00b1fbf0
extern "C" char e7_f34[];   // 0x0057cde0
extern "C" char e7_f38[];   // 0x00572810
typedef unsigned char      u8;
typedef unsigned int       u32;
struct cSerializerDesc {
    const char* mpName;                 // 0x00
    u32         mTag;                   // 0x04
    u32         mSize;                  // 0x08
    u8          mPad0c[0x18 - 0x0c];    // 0x0c (uninitialized in original)
    void*       mpField18;              // 0x18
    void*       mpField1c;              // 0x1c
    void*       mpFn20;                 // 0x20
    void*       mpFn24;                 // 0x24
    void*       mpFn28;                 // 0x28
    void*       mpFn2c;                 // 0x2c
    void*       mpFn30;                 // 0x30
    void*       mpFn34;                 // 0x34
    void*       mpFn38;                 // 0x38
};
extern "C" cSerializerDesc g_serializerDescs[8];   // 0x156f588
#define DESC_ENTRY(idx, name, tag, size, f20, f24, f28, f2c, f30, f34, f38)  \
    {                                                                        \
        u32 local[15];                                                       \
        local[0] = (u32)(name);                                              \
        local[1] = (tag);                                                    \
        local[6] = 0;                                                        \
        local[7] = 0;                                                        \
        local[8] = defaultOffset;                                            \
        local[9] = (u32)(f24);                                               \
        local[10] = (u32)(f28);                                              \
        local[11] = (u32)(f2c);                                              \
        local[12] = (u32)(f30);                                              \
        local[13] = (u32)(f34);                                              \
        local[14] = (u32)(f38);                                              \
        local[2] = (size);                                                   \
        memcpy(&g_serializerDescs[idx], local, 0x3c);                        \
    }
// ---- items of slice s0132ea70 end

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

// @ 0x0132ea70
void __cdecl InitSerializerDescs()
{
    u32 defaultOffset = (u32)g_fn692ca0;
    DESC_ENTRY(0, g_name_mCenterAxis, 0x02f1a511, 0x338, g_fn692ca0, e0_f24, e0_f28, e0_f2c, e0_f30, e0_f34, e0_f38)
    DESC_ENTRY(1, g_name_mpCity, 0x02f1a512, 0x264, g_fn692ca0, e1_f24, e1_f28, e1_f2c, e1_f30, e1_f34, e1_f38)
    DESC_ENTRY(2, g_name_mpDock, 0x06567f8d, 0x10c, g_fn692ca0, e2_f24, e2_f28, e2_f2c, e2_f30, e2_f34, e2_f38)
    DESC_ENTRY(3, g_name_mWallSize, 0x0474ea17, 0x254, e3_f20, e3_f24, e3_f28, e3_f2c, e3_f30, e3_f34, e3_f38)
    DESC_ENTRY(4, g_name_mStyle, 0x0474ea18, 0x344, e4_f20, e4_f24, e4_f28, e4_f2c, e4_f30, e4_f34, e4_f38)
    DESC_ENTRY(5, g_name_mLevel, 0x0474ea19, 0x348, e5_f20, e5_f24, e5_f28, e5_f2c, e5_f30, e5_f34, e5_f38)
    DESC_ENTRY(6, g_name_mAppliedStamp, 0x04dacb55, 0x350, e6_f20, e6_f24, e6_f28, e6_f2c, e6_f30, e6_f34, e6_f38)
    DESC_ENTRY(7, g_name_mWallOffset, 0x050793d5, 0x34c, e7_f20, e7_f24, e7_f28, e7_f2c, e7_f30, e7_f34, e7_f38)
}
