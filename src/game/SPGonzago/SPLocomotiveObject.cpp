// src/game/SPGonzago/SPLocomotiveObject.cpp -- migrated from slice(s) s00c44610, s00c44080, s00c44040, s00c43f20, s00c43e40, s00c43de0, s00c43cc0, s00c43c10, s00c43810, s00c43790, s00c436a0, s00c41dc0, s00c41360, s00c432e0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPLocomotiveObject.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cLocomotiveObject.h"
#include <math.h>
#include <intrin.h>
#include "SP/cIObjectDatabaseIStream.h"
#include "SP/cObjectDatabase.h"
#include "EA/COM/IRefCount.h"
#include "SP/cVarListSerializer.h"
#include "SP/cEmpire.h"
#include "SP/cMarker.h"
#include "SP/cPlanet.h"
#include "SP/cPropertyList.h"
#include "SP/cSPMission.h"
#include "SP/cStarManager.h"
#include "SP/cStarRecord.h"

// ---- items of slice s00c432e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cSpatialVector {
    void* mpBegin;                                           // +0x00
    void* mpEnd;                                             // +0x04
    void* mpCapacity;                                        // +0x08
    void erase(void* first, void* last);                     // 0x00b48e40
};
}
namespace SP {
struct cUIntVector {
    uint32_t* mpBegin;                                       // +0x00
    uint32_t* mpEnd;                                         // +0x04
    uint32_t* mpCapacity;                                    // +0x08
    void DoInsertKey4(uint32_t* pos, const uint32_t* value); // 0x00b96600
};
}
namespace SP {
struct cSubD4 {
    void Reset();                                            // 0x00ac5330
};
}
namespace SP {
struct cLocomotiveObject_s00c4_32e0 {
    uint32_t       mPad00[0xd4 / 4];                         // +0x00 .. +0xd3
    cSubD4         mSubD4;                                   // +0xd4
    uint32_t       mPadD8[0x1a0 / 4];                        // +0xd8 .. +0x277
    cSpatialVector mNeighbors;                               // +0x278
    uint32_t       mPad284[0x20c / 4];                       // +0x284 .. +0x48f
    cUIntVector    mVectors;                                 // +0x490
    uint32_t       mPad49c[0x30 / 4];                        // +0x49c .. +0x4cb
    void*          mpField4cc;                               // +0x4cc

    void Shutdown();  // 0x00c43f90 (SP::cLocomotiveObject::Shutdown)
    void InsertUnique(uint32_t value);
};
}
extern "C" void __fastcall FUN_00c8b2e0(void*);                             // 0x00c8b2e0
// ---- items of slice s00c432e0 end

// ---- items of slice s00c41360 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_OneThird;                     // 0x013f26dc (0.33333334f)
extern float g_HkRealZero;                   // 0x01485378 (0.0f)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
struct PodVec3 {    // trivially copyable (integer-register copies)
    float x, y, z;
};
struct cCityWalls {
    char pad[0x25c];
    float mOuterRadius;                               // +0x25c
    const PodVec3& GetWallPosition(Vector3& out, const Vector3& towards, int flag);   // 0xbec660 (sret)
    const PodVec3& RequestPosition(Vector3& out, int mode);                           // 0xbec2d0 (sret)
};
struct cSpatialObject {
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
    virtual const Vector3& GetPosition();             // +0x2c
};
struct cCity {
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
virtual void v2c();
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
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
    virtual cCityWalls* GetCityWalls();               // +0x6c
    char pad04[0x120 - 4 - 4 * 0];
    cSpatialObject mSpatial;                          // +0x120 (secondary base)
};
struct cRandomGlobal { float RandomDouble(); };        // 0x009360d0 (thiscall)
struct cRoad
{
    void RemoveInt(int value);

    char    pad04[0x118 - 0x04];    // +0x04 (after vptr)
    bool    mbFlag118;              // +0x118
    cCity*  mpCity1;                // +0x11c
    cCity*  mpCity2;                // +0x120
    int     mRoadType;              // +0x124
    char    pad128[0x13c - 0x128];
    float   mF13c;                  // +0x13c
    char    pad140[0x1a8 - 0x140];
    Vector3 mV1a8;                  // +0x1a8
    Vector3 mV1b4;                  // +0x1b4
    float   mF1c0;                  // +0x1c0
    float   mF1c4;                  // +0x1c4
    char    pad1c8[0x1f4 - 0x1c8];
    void*   mBegin1f4;              // +0x1f4
    void*   mEnd1f8;                // +0x1f8
    char    pad1fc[0x208 - 0x1fc];
    Vector3 mV208;                  // +0x208
    char    pad214[0x250 - 0x214];
    int     mF250;                  // +0x250
    float   mF254;                  // +0x254
    char    pad258[0x260 - 0x258];
    float   mF260;                  // +0x260
    char    pad264[0x26c - 0x264];
    float   mF26c;                  // +0x26c
    int     mF270;                  // +0x270
    char    pad274[0x278 - 0x274];
    Vector3 mV278;                  // +0x278
    char    pad284[0x490 - 0x284];
    int*    mpIntBegin490;          // +0x490
    int*    mpIntEnd494;            // +0x494
    char    pad498[0x4b8 - 0x498];
    Vector3 mV4b8;                  // +0x4b8

virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
    virtual const Vector3& GetPosition();              // +0x2c
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
    virtual char Action58();                           // +0x58
virtual void v59();
virtual void v60();
virtual void v61();
virtual void v62();
virtual void v63();
virtual void v64();
virtual void v65();
virtual void v66();
virtual void v67();
virtual void v68();
virtual void v69();
virtual void v70();
virtual void v71();
virtual void v72();
virtual void v73();
virtual void v74();
virtual void v75();
virtual void v76();
virtual void v77();
virtual void v78();
virtual void v79();
virtual void v80();
virtual void v81();
virtual void v82();
virtual void v83();
virtual void v84();
virtual void v85();
    virtual void* LookupById(uint32_t id);             // +0xb8
    virtual void v87();
    virtual void Chain(uint32_t a, uint32_t b);        // +0xc4

    float DistSqToPos();                               // 0x00c422c0
    bool  WithinRadius(float r);                       // 0x00c42210
};
struct cRoadTail
{
    uint8_t* mpBegin;               // +0x00
    uint8_t* mpEnd;                 // +0x04
    uint8_t  pad08[0x14 - 0x08];
    uint8_t  mDefault[0x3c];        // +0x14
};
int __cdecl FUN_00c42310(int* param_1)
{
    if (param_1 == 0)
        return 0;
    int* p = (int*)(*(int(__thiscall**)(int*, uint32_t))(*param_1 + 0xb8))(param_1, 0x17f243b);
    if (p == 0)
        return 0;
    char c = (*(char(__thiscall**)(int*))(*p + 0x2c))(p);
    if (c == 0)
        return 0;
    return 1;
}
struct IdLookupTarget
{
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
    virtual char  Test();                              // +0x2c
};
struct IdLookupSource
{
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
    virtual IdLookupTarget* Lookup(uint32_t id);       // +0xb8
    IdLookupTarget* Find(uint32_t id) { return Lookup(id); }
};
struct EntityRef
{
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
    virtual void* BuildEffect(float scale, const Vector3* pos, int a, void* fn, void* id);  // +0x2c
};
struct AvatarHolder2
{
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
    virtual void AddEffect(void* effect);              // +0x48
};
AvatarHolder2* __cdecl GetAvatarHolder2b();            // 0x00b3d240
void __cdecl EffectCallback0(void* a);                 // 0x00d9a9c0
// ---- items of slice s00c41360 end

// ---- items of slice s00c41dc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; };
float SegmentDistance(const Vec3* p, const Vec3* a, const Vec3* b);
// ---- items of slice s00c41dc0 end

// ---- items of slice s00c436a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
extern float gDefaultDstX;   // 0x0168e7e4
}
namespace SP {
extern float gDefaultDstY;   // 0x0168e7e8
}
namespace SP {
extern float gDefaultDstZ;   // 0x0168e7ec
}
namespace SP {
struct Waypoint;
}
namespace SP {
struct RequestVec3 { float x, y, z; };
}
namespace SP {
struct LocRequest {
    Waypoint*     mpBegin;                 // +0x00  waypoint vector
    Waypoint*     mpEnd;                   // +0x04
    Waypoint*     mpCapacity;              // +0x08
    char          pad0c[0x14 - 0x0c];
    RequestVec3   mDst;                    // +0x14  current waypoint destination
    float         mGoalStopDistance;       // +0x20
    int           mWaypointType;           // +0x24  next waypoint type
    char          pad28[0x4c - 0x28];
    unsigned char mWaypointFlags;          // +0x4c  next waypoint flags
    char          pad4d[0x50 - 0x4d];
    RequestVec3   mFacing;                 // +0x50  reference direction
    int           mType;                   // +0x5c  (0 none, 1/3 follow, 2 hold)
    float         mAcceptableStopDistance; // +0x60
    float         mField64;                // +0x64  (alignment threshold)
    float         mPrevDistance;           // +0x68
    float         mElapsed;                // +0x6c
    int           mField70;                // +0x70

    ~LocRequest()   // the waypoint vector's block is freed through its array cookie
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
};
}
namespace SP {
class cLocomotiveObjectRetail {
public:
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
virtual void v2c();
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
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
    virtual void vc0();
    virtual void SetDesiredSpeed(float speed, int flag);   // +0xc4
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
    virtual void vd8();
    virtual void SetGoal(const LocRequest& goal);          // +0xdc

    char         mPad04[0x270 - 0x04];
    unsigned int mMoveStatusFlags;                         // +0x270
};
}
// ---- items of slice s00c436a0 end

// ---- items of slice s00c43790 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
struct ISpatialObject {
    PV(0)  PV(1)  PV(2)  PV(3)
    PV(4)  PV(5)  PV(6)  PV(7)
    PV(8)  PV(9)  PV(10) PV(11)
    PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23)
    PV(24) PV(25) PV(26) PV(27)
    PV(28) PV(29) PV(30) PV(31)
    PV(32) PV(33) PV(34) PV(35)
    PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42) PV(43)
    PV(44) PV(45)

    virtual void* AsInterface(unsigned int id);
};
struct IStreamInner {
    PV(0) PV(1) PV(2)
    PV(3) PV(4) PV(5)

    virtual void* GetWriter();
};
struct IStreamWrite {
    PV(0) PV(1) PV(2) PV(3)
    PV(4) PV(5) PV(6)

    virtual void EndSequence();
    virtual IStreamInner* GetStream();

    PV(9) PV(10)

    virtual void WriteObject(void* object);
};
struct SpatialObjectVector {
    ISpatialObject** mpBegin;
    ISpatialObject** mpEnd;
    ISpatialObject** mpCapacity;
};
bool __cdecl WriteUint32(
    void* stream,
    const unsigned int* value,
    unsigned int count,
    int flags
);
__forceinline void WriteCount(
    IStreamInner* inner,
    unsigned int count
)
{
    void* writer = inner->GetWriter();
    WriteUint32(writer, &count, 1, 0);
}
// ---- items of slice s00c43790 end

// ---- items of slice s00c43810 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef bool (__cdecl* Pred)(void* p);
void** remove_copy_if(void** first, void** last, void** dest, Pred pred); // 0x00c43270
// ---- items of slice s00c43810 end

// ---- items of slice s00c43c10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_1574258[];
namespace SP {
struct IOStream;
}
namespace SP {
struct cVarListSerializer_s00c4_3c10 {
    uint32_t mStorage[0xa14 / 4];   // not a char array: a byte array would arm /GS
};
}
namespace SP {
struct cRefCounted {
    virtual int AddRef();
    virtual int Release();
};
}
namespace SP {
struct cObjectDatabase_s00c4_3c10;
}
namespace SP {
struct cObjectDatabaseVt {
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0c();
virtual void vf10();
virtual void vf14();
    virtual IOStream* GetStream();                                 // slot 6, +0x18
};
}
namespace SP {
struct cObjectDatabase_s00c4_3c10 : cObjectDatabaseVt {};
}
namespace SP {
struct cIObjectDatabaseIStream_s00c4_3c10 {
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0c();
virtual void vf10();
virtual void vf14();
virtual void vf18();
virtual void vf1c();
    virtual cObjectDatabase_s00c4_3c10* GetDatabase();                        // slot 8, +0x20
};
}
namespace SP {
struct cLocomotiveObject_s00c4_3c10 {
    uint32_t mPad00[0x4cc / 4];                                    // +0x00 .. +0x4cb
    cRefCounted* mpRef4cc;                                         // +0x4cc

    bool Read(cIObjectDatabaseIStream_s00c4_3c10& stream);
};
}
namespace SP {
bool __cdecl ReadInt32(void* pStream, int32_t* pValue, unsigned int count, int endian); // 0x93a780
}
namespace SP {
void FUN_00c88b00();                                               // 0xc88b00 cSpatialObject::Read (this, stream)
}
namespace SP {
void FUN_00692f90();                                               // 0x692f90 cVarListSerializer ctor (this, obj, data, sig)
}
namespace SP {
bool FUN_00693e10();                                               // 0x693e10 cVarListSerializer::Serialize (this, stream)
}
namespace SP {
void* __cdecl FUN_00b3d310();                                      // 0xb3d310
}
namespace SP {
void* __cdecl FUN_00c14350();                                      // 0xc14350 (context arrives in ecx)
}
// ---- items of slice s00c43c10 end

// ---- items of slice s00c43cc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_szSimulator[];   // 0x013f09b4 "Simulator"
extern char g_szAllocatorH[];  // 0x013ebb38 ".../EASTL/allocator.h"
struct Elem16_s00c4_3cc0 {
    float a;
    float b;
    float c;
    uint32_t d;
};
struct Vec16_s00c4_3cc0 {
    Elem16_s00c4_3cc0* mpBegin;
    Elem16_s00c4_3cc0* mpEnd;
    Elem16_s00c4_3cc0* mpCapacity;
    uint32_t mPad0c;
    Elem16_s00c4_3cc0* mpInline;

    uint32_t Insert(Elem16_s00c4_3cc0* pos, const Elem16_s00c4_3cc0* pValue);
};
void* __cdecl operator_new(uint32_t size, const char* pName, int a, int b,
                           const char* pFile, uint32_t line);            // 0x00f473a0
void __cdecl operator_delete(void* pBlock);                              // 0x00f47380
void* __cdecl FUN_00ba7920(void* pFirst, const void* pMiddle, void* pDest); // 0x00ba7920 uninitialized move
void __cdecl FUN_00edba80(void* pFirst, const void* pLast, void* pDest);    // 0x00edba80 copy_backward
// ---- items of slice s00c43cc0 end

// ---- items of slice s00c43de0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Base14 {
    char m00[0x14];
    Base14& operator=(const Base14& o); // 0x00c1b790
};
struct Int15 { int m[15]; };
struct LocoCopy : Base14 {
    Int15 mArr;                 // +0x14
    int m50, m54, m58, m5c;
    float m60, m64, m68, m6c;
    int m70;
    LocoCopy& operator=(const LocoCopy& o);
};
// ---- items of slice s00c43de0 end

// ---- items of slice s00c43e40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int    FUN_01021080();                       // 0x01021080
extern "C" void*  FUN_00b3d290();                       // 0x00b3d290
struct Vector3_s00c4_3e40 {
    float x;
    float y;
    float z;
};
inline bool operator==(const Vector3_s00c4_3e40& a, const Vector3_s00c4_3e40& b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}
inline bool operator!=(const Vector3_s00c4_3e40& a, const Vector3_s00c4_3e40& b)
{
    return !(a == b);
}
struct cGoalData {
    uint32_t m00[5];                 // +0x00 .. +0x13
    Vector3_s00c4_3e40  mPos;                   // +0x14
    uint32_t m20[15];                // +0x20 .. +0x5b
    int32_t  m5c;                    // +0x5c
    uint32_t m60[5];                 // +0x60 .. +0x73

    cGoalData& operator=(const cGoalData& o); // 0x00c43de0
};
struct cPathGraph {
    void release(void* node);        // 0x00ac4ef0
};
struct cGoalCache {
    cGoalCache(const cGoalData& goal); // 0x00b46d90
    ~cGoalCache();
};
extern "C" bool   FUN_0059ab70(const Vector3_s00c4_3e40* pPos);    // 0x0059ab70
extern Vector3_s00c4_3e40    kNoGoalPosition;                      // 0x0168e7e4
struct cLocomotiveObject {
    uint8_t  m00[0xd4];              // +0x000 .. +0x0d3
    uint32_t mPath;                  // +0x0d4
    uint8_t  mD8[0x1a0 - 0xd8];      // +0x0d8 .. +0x19f
    float    mSpeed;                 // +0x1a0
    uint8_t  mA4[0x1f4 - 0x1a4];     // +0x1a4 .. +0x1f3
    cGoalData mGoal;                 // +0x1f4
    uint8_t  m268[0x270 - 0x268];    // +0x268 .. +0x26f
    uint32_t mFlags;                 // +0x270
    uint8_t  m274[0x4cc - 0x274];    // +0x274 .. +0x4cb
    uint8_t* mpOwner;                // +0x4cc

    void SetGoal(cGoalData* pGoal);
};
// ---- items of slice s00c43e40 end

// ---- items of slice s00c43f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Elem16 {
    float x, y, z;
    int w;
};
struct Vec16 {
    Elem16* mpBegin;
    Elem16* mpEnd;
    Elem16* mpCapacity;
    void Slow(Elem16* pos, const Elem16* v); // 0x00c43cc0
    Elem16* FUN_00c43f20(Elem16* pos, const Elem16* v);
};
// ---- items of slice s00c43f20 end

// ---- items of slice s00c44040 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memmove_rw(void* dst, void* src, unsigned n); // 0x011e0744
struct Vec {
    char mPad00[0x490];
    int* mpBegin; // +0x490
    int* mpEnd;   // +0x494
    void FUN_00c44040();
};
// ---- items of slice s00c44040 end

// ---- items of slice s00c44080 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kMinForceLength;
extern const float kGoalPointRadiusSq;
extern const float kUnitMagnitude;
typedef unsigned char  u8;
struct cMarker {
    float mx;     // +0x00
    float my;     // +0x04
    float mz;     // +0x08
    int   mFlag;  // +0x0c
};
struct cMarkerVector {            // eastl::vector<cMarker> layout
    cMarker* mpBegin;             // +0x00
    cMarker* mpEnd;               // +0x04
    cMarker* mpCapacity;          // +0x08

    // eastl::vector::insert(position, value) (0x00c43f20): appends in place when
    // the position is the end, otherwise falls through to DoInsertValue.
    void Insert(cMarker* position, const cMarker& value);
    // eastl::vector::DoInsertValue(position, value) (0x00c43cc0): shifts/grows.
    void DoInsertValue(cMarker* position, const cMarker& value);

    // eastl::vector::push_back's spare-capacity path is inlined in AddMarker
    // below; when the vector is full it calls DoInsertValue as well.
};
struct cMarkerOwner {
    u8 mPad0000[0xf0];
    cMarkerVector mMarkers;       // +0x0f0

    void AddMarker(const float* pos, bool front);
};
struct Vector3_s00c4_4080 {
    float x;
    float y;
    float z;
};
struct tNavigationWaypointStub {
    Vector3_s00c4_4080 position;        // +0x00
    float   radius;          // +0x0c
    int     flags;           // +0x10
    Vector3_s00c4_4080 avoid0;          // +0x14
    Vector3_s00c4_4080 avoid1;          // +0x20
    Vector3_s00c4_4080 avoid2;          // +0x2c
    int     m38;             // +0x38
};
struct tNavigationGoalStub {
    void*   mpPathBegin;             // +0x00  eastl::vector<tNavigationWaypoint>
    void*   mpPathEnd;               // +0x04
    void*   mpPathCap;               // +0x08
    u8      mPad0c[0x14 - 0x0c];
    tNavigationWaypointStub nextWaypoint;  // +0x14
    Vector3_s00c4_4080 facing;                  // +0x50
    int     movementMode;            // +0x5c
    float   acceptableStopDistance;  // +0x60
    float   stopFacing;              // +0x64
    float   cachedDistanceToGoal;    // +0x68
    float   noProgressTime;          // +0x6c
    int     movementFlags;           // +0x70
    tNavigationGoalStub& operator=(tNavigationGoalStub const&);  // 0x00c43de0
};
struct tForceDataStub {
    int     forceType;       // +0x00  tForceData::eForceType
    int     forcePriority;   // +0x04  tForceData::eForcePriority
    Vector3_s00c4_4080 dir;             // +0x08
    float   magnitude;       // +0x14
    u8      mPad18[0x2c - 0x18];
};
struct ForceVectorStub {
    tForceDataStub* mpBegin;
    tForceDataStub* mpEnd;
    tForceDataStub* mpCap;

    void DoInsertValue(tForceDataStub* position, tForceDataStub const& value);  // 0x00b47600
    void Erase(tForceDataStub* first, tForceDataStub* last);                    // 0x00fea240
};
struct tSteeringDataStub {
    Vector3_s00c4_4080            curPosition;  // +0x00
    tNavigationGoalStub goal;        // +0x0c
    void*              pEntity;      // +0x80
    ForceVectorStub    forces;       // +0x84
    tSteeringDataStub() throw();     // 0x00c433f0
    ~tSteeringDataStub() throw();    // 0x013c3900
};
void ChoosePair(const Vector3_s00c4_4080* v, Vector3_s00c4_4080 p, Vector3_s00c4_4080* out0, Vector3_s00c4_4080* out1);
bool SegmentsNear(const Vector3_s00c4_4080* a1, const Vector3_s00c4_4080* a2, const Vector3_s00c4_4080* b1,
                  const Vector3_s00c4_4080* b2, Vector3_s00c4_4080* out);
void* GetGameManager();
struct cRoadStub {
    void* mpVtable;                  // +0x00
    u8 mPad04[0x1f4 - 0x04];
    tNavigationGoalStub mGoal;       // +0x1f4
    u8 mPad268[0x490 - 0x268];
    void** mpFnBegin;                // +0x490  sp_fixed_vector<void (*)(tSteeringData&), 4>
    void** mpFnEnd;                  // +0x494

    Vector3_s00c4_4080 const& GetPosition();                    // vtable slot 11, 0x00c41e00-ish
    Vector3_s00c4_4080 GetSteeringDirection();                  // vtable slot 23 (returns by value)
    Vector3_s00c4_4080* GetGoalPosition();                      // 0x00c42de0
    bool IsWithinGoalRadius(float radius);           // 0x00c42210
    Vector3_s00c4_4080 EvaluateForces(tSteeringDataStub& sd);   // 0x00c42710
    Vector3_s00c4_4080 ExecuteSteeringFunctions();
};
static inline Vector3_s00c4_4080 const& RoadGetPosition(cRoadStub* self)
{
    return ((Vector3_s00c4_4080 const& (__thiscall*)(cRoadStub*))(*(void***)self)[11])(self);
}
static inline Vector3_s00c4_4080 RoadGetSteeringDirection(cRoadStub* self)
{
    Vector3_s00c4_4080 out;
    ((Vector3_s00c4_4080* (__thiscall*)(cRoadStub*, Vector3_s00c4_4080*))(*(void***)self)[23])(self, &out);
    return out;
}
// ---- items of slice s00c44080 end

// ---- items of slice s00c44610 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00b49a50();
extern float g_GoalDistanceThreshold;  // 0x01574244
struct cCreatureBase {
    uint8_t  mPadB58[0xb58];                                 // +0x000 .. +0xb57
    uint32_t mFlagsB58;                                      // +0xb58
    uint8_t  mPadB5C[0xb64 - 0xb5c];                         // +0xb5c .. +0xb63
    uint8_t  mFlagB64;                                       // +0xb64 (via 0x00c0b700)

    // The +0xb58 bit 9 test comes out as `shr ecx,9; test cl,1` when the masked bit is
    // carried through a bool temporary, as an inlined accessor returning bool does.
    bool IsSteeringBlocked() const { return (mFlagsB58 >> 9) & 1; }

    bool GetFlagB64();                                       // 0x00c0b700
};
struct cLocomotiveObject_s00c4_4610 {
    uint8_t  mPad000[0x190];                                 // +0x000 .. +0x18f
    Vec3     mGoalPosition;                                  // +0x190
    uint8_t  mbGoalFlag;                                     // +0x19c

    float DistanceSquaredToGoal();                           // 0x00c422c0
    bool  HasId(uint32_t id);                                // 0x00c426e0
    void  RemoveId(uint32_t id);                             // 0x00c42140
    void  InsertUnique(uint32_t id);                         // 0x00c43fe0
    void  UpdateSteeringForMovementStyle();                  // 0x00c44610
};
extern Vec3  kZeroGoalPosition;        // 0x0168e7e4 / 0x0168e7e8 / 0x0168e7ec
// ---- items of slice s00c44610 end

// @ 0x00c41dc0
void ChoosePair(const Vec3* v, Vec3 p, Vec3* out0, Vec3* out1)
{
    int index = 0;
    float d0 = SegmentDistance(&p, &v[0], &v[1]);
    float d1 = SegmentDistance(&p, &v[1], &v[2]);
    if (d0 > d1) {
        index = 1;
        d0 = d1;
    }
    if (d0 > SegmentDistance(&p, &v[2], &v[0]))
        index = 2;

    switch (index) {
    case 0:
        *out0 = v[0];
        *out1 = v[1];
        break;
    case 1:
        *out0 = v[1];
        *out1 = v[2];
        break;
    default:
        *out0 = v[2];
        *out1 = v[0];
        break;
    }
}

// @ 0x00c41ed0
int __fastcall FUN_00c41ed0(cRoad* this_, float a, float b)
{
    if (!(b * b >= a)) {
        if (this_->mF260 > g_HkRealZero) {
            if (this_->mF254 * this_->mF254 >= a)
                return 1;
        }
        return 0;
    }
    return 1;
}

// @ 0x00c420f0
float __cdecl FUN_00c420f0(cRandomGlobal* r, float a, float b)
{
    float r1 = r->RandomDouble();
    float r2 = r->RandomDouble();
    float r3 = r->RandomDouble();
    return (r3 + r2 + r1) * (b - a) * g_OneThird + a;
}

// @ 0x00c42140
void cRoad::RemoveInt(int value)
{
    unsigned i = 0;
    unsigned n = (unsigned)(mpIntEnd494 - mpIntBegin490);
    if (n <= 0) return;
    int* p = *(int* volatile*)&mpIntBegin490;
    do {
        if (value == *p) goto found;
        _ReadWriteBarrier();
        ++i;
        ++p;
    } while (i < (unsigned)(mpIntEnd494 - mpIntBegin490));
    return;
found:
    _ReadWriteBarrier();
    mpIntBegin490[i] = mpIntBegin490[mpIntEnd494 - mpIntBegin490 - 1];
    mpIntEnd494 -= 1;
}

// @ 0x00c421f0
int* __fastcall FUN_00c421f0(cRoad* this_)
{
    void* b = this_->mBegin1f4;
    if (b == this_->mEnd1f8)
        return (int*)&this_->mV208;
    _ReadWriteBarrier();
    return (int*)((uint32_t)this_->mEnd1f8 - 0x3c);
}

// @ 0x00c42210
bool __fastcall FUN_00c42210(cRoad* this_, float r)
{
    if (this_->mF250 == 0)
        return true;
    Vector3 p;
    if (this_->mBegin1f4 == this_->mEnd1f8)
    {
        p.x = this_->mV208.x;
        p.y = this_->mV208.y;
        p.z = this_->mV208.z;
    }
    else
    {
        float* q = (float*)((uint8_t*)this_->mEnd1f8 - 0x3c);
        p.x = q[0];
        p.y = q[1];
        p.z = q[2];
    }
    const Vector3& c = this_->GetPosition();
    float dx = p.x - c.x;
    float dy = p.y - c.y;
    float dz = p.z - c.z;
    return sqrtf(dz * dz + dx * dx + dy * dy) < r;
}

// @ 0x00c422c0
float __fastcall FUN_00c422c0(cRoad* this_)
{
    if (this_->mF250 == 0)
        return 0.0f;
    const Vector3& pos = this_->GetPosition();
    float dx = this_->mV208.x - pos.x;
    float dy = this_->mV208.y - pos.y;
    float dz = this_->mV208.z - pos.z;
    return dz * dz + dx * dx + dy * dy;
}

// @ 0x00c42310
int __cdecl FUN_00c42310(IdLookupSource* param_1)
{
    if (param_1 != 0)
    {
        IdLookupTarget* t = param_1->Find(0x17f243b);
        if (t != 0)
        {
            if (t->Test() != 0)
                return 1;
        }
    }
    return 0;
}

// @ 0x00c42350
void __fastcall FUN_00c42350(cRoad* this_)
{
    if (this_->mF26c == g_HkRealZero)
        return;
    AvatarHolder2* holder = GetAvatarHolder2b();
    void* id = 0;
    (void)id;
    void* effectId = ((IdLookupSource*)this_)->Find(0x17f243b);
    void* effect = ((EntityRef*)this_)->BuildEffect(this_->mF26c, &this_->mV278,
                                                    0, (void*)EffectCallback0, effectId);
    holder->AddEffect(effect);
}

// @ 0x00c423c0
int* __fastcall FUN_00c423c0(cRoadTail* t)
{
    uint8_t* e = t->mpEnd;
    if (t->mpBegin == e)
        return (int*)t->mDefault;
    return (int*)(e - 0x3c);
}

// @ 0x00c436a0
namespace SP {
void cLocomotiveObject::ClearGoalAndStop()
{
    cLocomotiveObjectRetail* loco = (cLocomotiveObjectRetail*)this;
    {
        LocRequest goal;
        goal.mpBegin = 0;
        goal.mpEnd = 0;
        goal.mpCapacity = 0;
        goal.mDst.x = gDefaultDstX;
        goal.mDst.y = gDefaultDstY;
        goal.mDst.z = gDefaultDstZ;
        goal.mGoalStopDistance = 1.0f;
        goal.mWaypointType = 0;
        goal.mWaypointFlags = 0;
        goal.mFacing.x = 0.0f;
        goal.mFacing.y = 0.0f;
        goal.mFacing.z = 0.0f;
        goal.mType = 0;
        goal.mAcceptableStopDistance = 2.0f;
        goal.mField64 = 0.9f;
        goal.mPrevDistance = 3.402823466e+38f;
        goal.mElapsed = 0.0f;
        goal.mField70 = 0;
        loco->SetGoal(goal);
    }
    loco->SetDesiredSpeed(0.0f, 1);
    loco->mMoveStatusFlags = 0;
}
}  // namespace SP

// @ 0x00c43790
void __cdecl WriteSTLSequenceT( IStreamWrite* stream, SpatialObjectVector* objects )
{
    unsigned int count =
        (unsigned int)(objects->mpEnd - objects->mpBegin);

    IStreamInner* inner = stream->GetStream();

    WriteCount(inner, count);

    ISpatialObject** current = objects->mpBegin;
    ISpatialObject** end = objects->mpEnd;

    while (current != end) {
        ISpatialObject* object = *current;
        void* value = 0;

        if (object) {
            value = object->AsInterface(0x0179C807);
        }

        stream->WriteObject(value);
        ++current;
    }

    stream->EndSequence();
}

// @ 0x00c43810
void** FUN_00c43810(void** first, void** last, Pred pred)
{
    while (first != last) {
        if (pred(*first))
            break;
        ++first;
    }
    if (first != last) {
        void** next = first;
        return remove_copy_if(++next, last, first, pred);
    }
    return first;
}

// @ 0x00c43c10
namespace SP {
bool cLocomotiveObject_s00c4_3c10::Read(cIObjectDatabaseIStream_s00c4_3c10& stream)
{
    int version;
    IOStream* pStream = stream.GetDatabase()->GetStream();
    ReadInt32(pStream, &version, 1, 0);

    ((void (__thiscall*)(cLocomotiveObject_s00c4_3c10*, cIObjectDatabaseIStream_s00c4_3c10*))FUN_00c88b00)(this, &stream);

    cVarListSerializer_s00c4_3c10 serializer;
    ((void (__thiscall*)(cVarListSerializer_s00c4_3c10*, void*, void*, unsigned int))FUN_00692f90)(
        &serializer, this, (void*)g_1574258, 0x1a80d26u);

    bool ok = ((bool (__thiscall*)(cVarListSerializer_s00c4_3c10*, cIObjectDatabaseIStream_s00c4_3c10*))FUN_00693e10)(
        &serializer, &stream);

    cRefCounted* pNew = (cRefCounted*)((void* (__thiscall*)(void*))FUN_00c14350)(FUN_00b3d310());
    cRefCounted* pOld = mpRef4cc;
    if (pNew != pOld) {
        if (pNew)
            pNew->AddRef();
        mpRef4cc = pNew;
        if (pOld)
            pOld->Release();
    }
    return ok;
}
}  // namespace SP

// @ 0x00c43cc0
uint32_t Vec16_s00c4_3cc0::Insert(Elem16_s00c4_3cc0* pos, const Elem16_s00c4_3cc0* pValue)
{
    Elem16_s00c4_3cc0* const end = mpEnd;
    if (end != mpCapacity)
    {
        const Elem16_s00c4_3cc0* value = pValue;
        if (value >= pos && value < end)
            value = value + 1;
        if (end)
        {
            Elem16_s00c4_3cc0* const last = end - 1;
            end->a = last->a;
            end->b = last->b;
            end->c = last->c;
            end->d = last->d;
        }
        FUN_00edba80(pos, mpEnd - 1, mpEnd);
        *(uint32_t*)&pos->a = *(const uint32_t*)&value->a;
        uint32_t b = *(const uint32_t*)&value->b;
        *(uint32_t*)&pos->b = b;
        *(uint32_t*)&pos->c = *(const uint32_t*)&value->c;
        *(uint32_t*)&pos->d = *(const uint32_t*)&value->d;
        mpEnd = mpEnd + 1;
        return b;
    }
    else
    {
        uint32_t n = (uint32_t)(int)(mpEnd - mpBegin);
        if (n > 0)
            n = n * 2;
        else
            n = 1;
        Elem16_s00c4_3cc0* pNew;
        if (n)
            pNew = (Elem16_s00c4_3cc0*)operator_new(n << 4, g_szSimulator, 0, 0,
                                                    g_szAllocatorH, 0xd1);
        else
            pNew = 0;
        Elem16_s00c4_3cc0* const begin = mpBegin;
        Elem16_s00c4_3cc0* p = (Elem16_s00c4_3cc0*)FUN_00ba7920(begin, pos, pNew);
        if (p)
        {
            p->a = pValue->a;
            p->b = pValue->b;
            p->c = pValue->c;
            p->d = pValue->d;
        }
        Elem16_s00c4_3cc0* oldEnd = mpEnd;
        p = (Elem16_s00c4_3cc0*)FUN_00ba7920(pos, oldEnd, p + 1);
        if (mpBegin != 0 && mpBegin != mpInline)
            operator_delete(mpBegin);
        mpEnd = p;
        mpCapacity = pNew + n;
        mpBegin = pNew;
    }
}

// @ 0x00c43de0
LocoCopy& LocoCopy::operator=(const LocoCopy& o)
{
    Base14::operator=(o);
    mArr = o.mArr;
    m50 = o.m50;
    m54 = o.m54;
    m58 = o.m58;
    m5c = o.m5c;
    m60 = o.m60;
    m64 = o.m64;
    m68 = o.m68;
    m6c = o.m6c;
    m70 = o.m70;
    return *this;
}

// @ 0x00c43e40
void cLocomotiveObject::SetGoal(cGoalData* pGoal)
{
    bool bApply = FUN_01021080() != 0 || pGoal->m5c == 0
                  || (pGoal->mPos != kNoGoalPosition && FUN_0059ab70(&pGoal->mPos));

    if (bApply) {
        if (mFlags & 4) {
            ((cPathGraph*)FUN_00b3d290())->release(&mPath);
            mFlags &= ~4u;
        }
        mGoal = *pGoal;
        if (mpOwner)
            mpOwner[4] = 1;
        mSpeed = 0.0f;
        return;
    }
    static cGoalCache sCache(*pGoal);
}

// @ 0x00c43f20
Elem16* Vec16::FUN_00c43f20(Elem16* pos, const Elem16* v)
{
    Elem16* end = mpEnd;
    int index = (int)(pos - mpBegin);
    if (pos == end && end != mpCapacity) {
        Elem16* snap = end;
        mpEnd = end + 1;
        if (snap) {
            snap->x = v->x;
            snap->y = v->y;
            snap->z = v->z;
            snap->w = v->w;
        }
        return mpBegin + index;
    }
    Slow(pos, v);
    return mpBegin + index;
}

// @ 0x00c43f90
namespace SP {
void cLocomotiveObject_s00c4_32e0::Shutdown()
{
    void* previous = mpField4cc;
    if (previous) {
        mpField4cc = 0;
        ((void (__thiscall*)(void*))((void**)*(void**)previous)[0x04 / 4])(previous);
    }
    mNeighbors.erase(mNeighbors.mpBegin, mNeighbors.mpEnd);
    mSubD4.Reset();
    FUN_00c8b2e0(this);
}
}  // namespace SP

// @ 0x00c43fe0
namespace SP {
void cLocomotiveObject_s00c4_32e0::InsertUnique(uint32_t value)
{
    uint32_t* it = mVectors.mpBegin;
    uint32_t* last = mVectors.mpEnd;
    while (it != last && *it != value)
        ++it;
    if (it == last) {
        if (last != mVectors.mpCapacity) {
            mVectors.mpEnd = last + 1;
            if (last)
                *last = value;
        } else {
            mVectors.DoInsertKey4(last, &value);
        }
    }
}
}  // namespace SP

// @ 0x00c44040
void Vec::FUN_00c44040()
{
    int* begin = mpBegin;
    int* end = mpEnd;
    memmove_rw(begin, end, (unsigned)((char*)mpEnd - (char*)end));
    mpEnd -= end - begin;
}

// @ 0x00c44080
Vector3_s00c4_4080 cRoadStub::ExecuteSteeringFunctions()
{
    static tSteeringDataStub sd;

    sd.curPosition = RoadGetPosition(this);
    sd.goal = mGoal;
    sd.pEntity = this;
    sd.forces.Erase(sd.forces.mpBegin, sd.forces.mpEnd);

    if (mGoal.movementMode != 0) {
        tNavigationWaypointStub const& wp = mGoal.nextWaypoint;
        float dx = wp.position.x - sd.curPosition.x;
        float dy = wp.position.y - sd.curPosition.y;
        float dz = wp.position.z - sd.curPosition.z;
        float distSq = dz * dz + dx * dx + dy * dy;

        // Already standing at the stop point facing the right way: no steering needed.
        if (mGoal.movementMode == 3 && distSq <= wp.radius * wp.radius)
            return mGoal.facing;

        tForceDataStub force;
        force.forcePriority = 1;
        if (sd.forces.mpEnd < sd.forces.mpCap) {
            tForceDataStub* p = sd.forces.mpEnd++;
            if (p)
                p->forcePriority = 1;
        } else {
            sd.forces.DoInsertValue(sd.forces.mpEnd, force);
        }
        tForceDataStub* f = sd.forces.mpEnd - 1;
        f->forcePriority = 1;

        if (wp.flags != 0 && distSq <= kGoalPointRadiusSq) {
            Vector3_s00c4_4080 goalPos = *GetGoalPosition();
            Vector3_s00c4_4080 avoid[3];
            avoid[0] = wp.avoid0;
            avoid[1] = wp.avoid1;
            avoid[2] = wp.avoid2;
            Vector3_s00c4_4080 out0;
            Vector3_s00c4_4080 out1;
            ChoosePair(avoid, sd.curPosition, &out0, &out1);

            // The next waypoint on the goal path wins over the goal destination itself.
            Vector3_s00c4_4080 dest;
            if (mGoal.mpPathBegin == mGoal.mpPathEnd)
                dest = goalPos;
            else
                dest = *(Vector3_s00c4_4080*)((char*)mGoal.mpPathEnd - 0x3c);

            f->forceType = 4;
            f->magnitude = kUnitMagnitude;
            if (SegmentsNear(&goalPos, &out1, &out0, &sd.curPosition, &dest))
                f->dir = dest;
            else
                f->dir = goalPos;
        } else {
            f->forceType = 4;
            f->dir = *GetGoalPosition();
            f->magnitude = kUnitMagnitude;
        }
    }

    if (mGoal.movementMode != 3 || !IsWithinGoalRadius(mGoal.nextWaypoint.radius)) {
        void** p = mpFnBegin;
        void** end = mpFnEnd;
        while (p != end) {
            ((void (__cdecl*)(tSteeringDataStub&))*p)(sd);
            ++p;
        }
    }

    // Nothing produced a force: steer straight along the current heading.
    if (sd.forces.mpBegin == sd.forces.mpEnd) {
        tForceDataStub force;
        force.forcePriority = 1;
        if (sd.forces.mpEnd < sd.forces.mpCap) {
            tForceDataStub* p = sd.forces.mpEnd++;
            if (p)
                p->forcePriority = 1;
        } else {
            sd.forces.DoInsertValue(sd.forces.mpEnd, force);
        }
        tForceDataStub* f = sd.forces.mpEnd - 1;
        f->forceType = 2;
        f->dir = RoadGetSteeringDirection(this);
    }

    int retried = 0;
    for (;;) {
        Vector3_s00c4_4080 result = EvaluateForces(sd);
        if (*(int*)((char*)GetGameManager() + 0x20) == 0)
            return result;
        float length = sqrtf(result.x * result.x + result.z * result.z + result.y * result.y);
        if (length >= kMinForceLength)
            return result;

        // Nothing left to prune: coast along the current heading at the minimum speed.
        if (sd.forces.mpBegin == sd.forces.mpEnd) {
            Vector3_s00c4_4080 dir = RoadGetSteeringDirection(this);
            Vector3_s00c4_4080 scaled;
            scaled.x = dir.x * kMinForceLength;
            scaled.y = dir.y * kMinForceLength;
            scaled.z = dir.z * kMinForceLength;
            return scaled;
        }

        tForceDataStub* it = sd.forces.mpBegin;
        int count = (int)(sd.forces.mpEnd - sd.forces.mpBegin);
        int i = 0;
        for (; i < count; ++i, ++it) {
            if (it->forcePriority == retried)
                break;
        }
        if (i != count) {
            *it = *(sd.forces.mpEnd - 1);
            --sd.forces.mpEnd;
            continue;
        }
        if (retried != 0)
            return result;
        retried = 1;
    }
}

// @ 0x00c44610
void cLocomotiveObject_s00c4_4610::UpdateSteeringForMovementStyle()
{
    if (!this)
        return;

    typedef void* (__thiscall* tQuery)(void*, uint32_t);
    cCreatureBase* creature =
        (cCreatureBase*)((tQuery)(*(void***)this)[0xb8 / 4])(this, 0xce9f6639);
    if (!creature)
        return;

    if (creature->IsSteeringBlocked())
        return;

    if (creature->GetFlagB64()) {
        if (this->DistanceSquaredToGoal() > g_GoalDistanceThreshold) {
            if (this->HasId((int)FUN_00b49a50))
                return;
            this->InsertUnique((int)FUN_00b49a50);
            return;
        }
    }

    if (this->HasId((int)FUN_00b49a50)) {
        this->RemoveId((int)FUN_00b49a50);
        this->mbGoalFlag = 0;
        this->mGoalPosition = kZeroGoalPosition;
    }
}

// @ 0x00c446d0
void cMarkerOwner::AddMarker(const float* pos, bool front)
{
    // The coordinates and the flag are also kept in their own locals: retail
    // loads them into xmm0..xmm2/edx and keeps them live across the branch, so
    // the push_back fast path below can fill the new element straight from
    // those registers while the same values are already stored in the
    // temporary that the two out-of-line paths pass by reference.
    float x = pos[0];
    float y = pos[1];
    float z = pos[2];
    int   flag = front ? 1 : 0;
    cMarker marker = { x, y, z, flag };

    cMarkerVector& v = mMarkers;      // takes the vector's address once
    if (front) {
        v.Insert(v.mpBegin, marker);
    } else if (v.mpEnd < v.mpCapacity) {
        // eastl::vector::push_back, spare-capacity path
        cMarker* p = v.mpEnd++;
        if (p) {
            p->mx = x;
            p->my = y;
            p->mz = z;
            p->mFlag = flag;
        }
    } else {
        v.DoInsertValue(v.mpEnd, marker);
    }
}
