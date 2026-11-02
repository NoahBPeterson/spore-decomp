// src/game/SPGonzago/_at_00b50000.cpp -- migrated from slice(s) s00b5b540, s00b5a750, s00b5a260, s00b56fe0, s00b55680, s00b547b0, s00b537f0, s00b51b00, s00b509b0, s00b4fd80 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00b50000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void* g_vtblFB0;         // 0x01461390
extern const float kOne;       // 0x01485720 = 1.0f
extern const float kHalf;      // 0x01471064 = 0.5f
extern const float kMilli;     // 0x013f9428 = 0.001f
extern const float kFloatMax;  // 0x014612d8 = FLT_MAX
#include <math.h>
#include "SP/cPlanetModel.h"
#include "EA/Allocator/ZoneObject.h"
#include "SP/cResourceBase.h"
#include <intrin.h>
#include <new.h>
#include <new>
#include "SP/cITerrainSphere.h"
#include "SP/cModelManager.h"
#include <stddef.h>

// ---- items of slice s00b4fd80 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char uchar;
extern void* g_vtblFB0;         // 0x01461390
struct HkVec { char d[0x10]; };
struct HkObj { void setTransformedPos(const void* a, HkVec* out); };  // 0x01081360
struct Obj500E0 {
    void F(const void* a, HkObj* b);   // 0x00b500e0
};
struct Variant8 { uchar flag; float v; };
struct IVarInvoke {
virtual void i0();
virtual void i1();
virtual void i2();
virtual void i3();
virtual void i4();
virtual void i5();
virtual void i6();
virtual void i7();
    virtual void i8();
    virtual void Invoke(unsigned a, unsigned b, Variant8 t, unsigned c);  // +0x24
};
struct Obj50170 {
    void F(unsigned a, unsigned b, unsigned c);   // 0x00b50170
};
struct S24 { float a, b, c, d; int e; float f; };
struct Obj501A0 { float a, b, c, d; int e; float f; S24& operator=(const S24& src); };
struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };
struct FaceUV { float u, v; int face; };
extern const float kOne;       // 0x01485720 = 1.0f
extern const float kHalf;      // 0x01471064 = 0.5f
extern const float kMilli;     // 0x013f9428 = 0.001f
extern const float kFloatMax;  // 0x014612d8 = FLT_MAX
extern const Vec3  kZeroVec;   // 0x0167ecf4 = {0,0,0}
struct TerrainMapU16 {
    float GetFloat(FaceUV* uv);                        // 0x00f8d620
};
struct PlanetModel {
    Vec3* GetNormalAt(Vec3* out, const Vec3* at);                        // 0x00b7e3b0
    Vec3* __thiscall FUN_00b82060(const Vec3* b, const Vec3* a, const Vec3* dir);     // 0x00b82060
    Vec3* __thiscall FUN_00b82110(const FaceUV* uv, const Vec3* a, const Vec3* dir);  // 0x00b82110
};
static __forceinline void DirToCubeInto(FaceUV& r, const Vec3& v)
{
    float ax = fabsf(v.x);
    float ay = fabsf(v.y);
    float az = fabsf(v.z);
    if (az < ax || az < ay) {
        if (ay < ax) {
            r.u = (v.y / v.x + kOne) * kHalf;
            r.v = (v.z / ax + kOne) * kHalf;
            if (v.x < 0.0f) r.face = 3; else r.face = 2;
        } else {
            r.u = (v.z / v.y + kOne) * kHalf;
            r.v = (v.x / ay + kOne) * kHalf;
            if (v.y < 0.0f) r.face = 5; else r.face = 4;
        }
    } else {
        r.u = (v.x / v.z + kOne) * kHalf;
        r.v = (v.y / az + kOne) * kHalf;
        if (v.z < 0.0f) r.face = 1; else r.face = 0;
    }
}
struct RayHitSink {
    virtual void Hit(unsigned id, const Vec4* normal);   // +0x00
    float mMaxT;                                         // +0x04
};
struct Obj501D0 {
    char pad00[0x34];
    PlanetModel*    mPlanet;   // +0x34
    char pad38[4];
    TerrainMapU16*  mMap;      // +0x3c
    char pad40[0x0c];
    float           mBase;     // +0x4c
    float           mScale;    // +0x50
    void F(const Vec4* seg, unsigned id, char checkHeight, float margin, RayHitSink* sink);
};
struct SVec { float a, b, c, d; int e; float f; };
struct Obj50780 {
    char pad0[4];
    float mDist;      // +0x04
    uchar mFlag;      // +0x08
    char pad9[3];
    SVec* mDst;       // +0x0c
    void F(unsigned param2, SVec* src);   // 0x00b50780
};
struct Obj507D0 { void F(unsigned param2, unsigned param3, uchar* out); };  // 0x00b507d0
struct SweptSphere {
    Vec4  mStart;    // +0x00
    Vec4  mEnd;      // +0x10
    float mExtra0;   // +0x20
    float mExtra1;   // +0x24
    float mUnused0;  // +0x28
    float mUnused1;  // +0x2c
    float mRadius;   // +0x30
    float mParam;    // +0x34
};
struct SweptSphereOut {
    Vec4  mStart;    // +0x00
    Vec4  mEnd;      // +0x10
    float mExtra0;   // +0x20
    float mExtra1;   // +0x24
};
struct IHitInvoke {
virtual void h0();
virtual void h1();
virtual void h2();
virtual void h3();
virtual void h4();
virtual void h5();
virtual void h6();
virtual void h7();
    virtual void h8();
    virtual void Invoke(SweptSphereOut* out, unsigned id, char one, float param, unsigned extra);  // +0x24
};
struct Obj50820 {
    void F(const SweptSphere* in, unsigned id, unsigned extra);
};
// ---- items of slice s00b4fd80 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern const Vec3  kZeroVec;   // 0x0167ecf4 = {0,0,0}

// ---- items of slice s00b509b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_bodyF;                                           // 0x1488874
extern float g_t0, g_t1, g_t2, g_t3, g_t4, g_t5, g_t6, g_t7, g_t8, g_t9;
extern const char g_ehFile[];                                   // 0x13ebb38
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(_p, __COUNTER__)();
#define VP4 VP VP VP VP
struct RefObj {
    virtual int AddRef();
    virtual int Release();
};
struct UV { float u, v; int face; };
struct TerrainMapF {
    float GetFloat(UV* uv);                                     // 0x00f8d620
};
struct TerrainMapV {
    void GetVector4(Vec4* out, UV* uv);                         // 0x00f89e50
};
struct PlanetModelT {
    char pad[0xf0];
    u8   hasWater;                                              // 0xf0
    float GetWaterHeight();                                     // 0xb7e390
};
struct Plane { float x, y, z, w; };
struct PlaneList {
    Plane* data;                                                // 0
    int    count;                                               // 4
    float  maxDist;                                             // 8
};
struct TerrainSampler {
    char pad0[0x34];
    PlanetModelT* planet;                                       // 0x34
    TerrainMapV*  normals;                                      // 0x38
    TerrainMapF*  heights;                                      // 0x3c
    char pad1[0x4c - 0x40];
    float bias;                                                 // 0x4c
    float scale;                                                // 0x50

    void ProjectPlanes(PlaneList* in, Plane* out);              // 0xb509b0
};
extern Vec3 g_normalBias;                                       // 0x1569b1c
typedef short s16;
class hkMemory { public:
    VP4
    virtual void* allocateChunk(int size, int type);            // 0x10
    virtual void  deallocateChunk(void* p, int size, int type); // 0x14
};
extern hkMemory* g_hkMemory;                                    // 0x16e4178
class hkReferencedObject_s00b5_09b0 { public:
    virtual ~hkReferencedObject_s00b5_09b0() {}
    u16 memSize;                                                // +4
    s16 refCount;                                               // +6
    void addReference() { if (memSize) ++refCount; }
    void removeReference() {
        if (memSize) {
            --refCount;
            if (refCount == 0)
                delete this;
        }
    }
    static void operator delete(void* p) {
        g_hkMemory->deallocateChunk(p, ((hkReferencedObject_s00b5_09b0*)p)->memSize, 0x24);
    }
};
struct RCObj {
    virtual ~RCObj() {}
    int rc;
    void Release() {
        int n = (*(volatile int*)&rc += -1);
        if (n == 0) {
            rc = 1;
            delete this;
        }
    }
};
struct AutoRC {
    RCObj* p;
    ~AutoRC() { if (p) p->Release(); }
};
struct HkOwner : hkReferencedObject_s00b5_09b0 {
    char pad[0x30];
    AutoRC a;                                                   // 0x38
    AutoRC b;                                                   // 0x3c
    HkOwner();
};
struct cResourceBase {
    virtual int AddRef();
    virtual int Release();
    virtual ~cResourceBase() {}
    long rc;                                                    // 4
    long f8, fc, f10;
    cResourceBase() {
        _InterlockedExchange(&rc, 0);
        f8 = 0; fc = 0; f10 = 0;
    }
};
struct cHavokResource : cResourceBase {
    RCObj* p14;                                                 // 0x14 owned, deleted through slot 0
    int*   arr;                                                 // 0x18 owned array (count cookie at -4)
    int    f1c, f20, f24, f28;
    cHavokResource() {
        p14 = 0; arr = 0; f1c = 0; f20 = 0;
    }
    virtual ~cHavokResource();
};
void* __cdecl operator_new(unsigned, const char*, int, int, int, int);
inline void* operator new(unsigned n, const char* name, int a, int b, int c, int d) {
    return operator_new(n, name, a, b, c, d);
}
inline void operator delete(void*, const char*, int, int, int, int) {}
struct ZoneObject {
    static void* operator new(unsigned n, const char* name, int a, int b, int c, int d);   // 0x926020
    static void operator delete(void*, const char*, int, int, int, int) {}
};
struct ZoneRC : ZoneObject {
    virtual int AddRef();
    virtual int Release();
    long rc;
    ZoneRC() { _InterlockedExchange(&rc, 0); }
};
struct cHavokResourceFactory : ZoneRC {
    virtual int Release();
};
struct ResMan {
    VP VP VP
    virtual bool Get(u32 key, RefObj** out, int a, int b, int c, int d);   // 0xc
    VP4 VP4 VP4 VP
    virtual void AddFactory(int kind, cHavokResourceFactory* f, int c);    // 0x44
};
ResMan* __cdecl GetResMan();                                    // 0x67dcd0
struct NodeA {                                                  // 0xa0 bytes
    u32 key[3];
    u32 pad0;
    char value[0x10];                                           // +0x10 (returned by FindNear)
    float f;                                                    // +0x20
    char pad1[0x90 - 0x24];
    NodeA* next;                                                // +0x90
    NodeA(const void* v);                                       // 0xb4d980
};
struct Cursor {
    char pad0[8];
    NodeA* end;                                                 // 8
    char pad1[4];
    NodeA* cur;                                                 // 0x10
    NodeA** bucket;                                             // 0x14
};
class hkStreamReader : public hkReferencedObject_s00b5_09b0 { public:};
class hkMemoryStreamReader : public hkStreamReader { public:
    char pad[0x1c - 8];
    hkMemoryStreamReader(const void* buf, int size, int mode);  // 0x10801d0
    static void* operator new(unsigned n) {
        void* p = g_hkMemory->allocateChunk((int)n, 0x17);
        ((hkReferencedObject_s00b5_09b0*)p)->memSize = (u16)n;
        return p;
    }
    static void operator delete(void* p) {
        g_hkMemory->deallocateChunk(p, ((hkReferencedObject_s00b5_09b0*)p)->memSize, 0x17);
    }
};
class hkBinaryPackfileReader : public hkReferencedObject_s00b5_09b0 { public:
    char pad[0x6c - 8];
    hkBinaryPackfileReader();                                   // 0x112b6c0
    virtual void p1();
    virtual void loadEntireFile(hkStreamReader* r);             // 0x8
    VP4 VP VP
    virtual hkReferencedObject_s00b5_09b0* getContents();                  // 0x24
    static void* operator new(unsigned n) {
        void* p = g_hkMemory->allocateChunk((int)n, 6);
        ((hkReferencedObject_s00b5_09b0*)p)->memSize = (u16)n;
        return p;
    }
    static void operator delete(void* p) {
        g_hkMemory->deallocateChunk(p, ((hkReferencedObject_s00b5_09b0*)p)->memSize, 6);
    }
};
struct HkResData : RefObj {
    char pad[0x14];
    int* begin;                                                 // 0x18
    int* end;                                                   // 0x1c
};
struct ResObj : RefObj {
    VP
    virtual RefObj* Query(u32 id);                              // 0xc
};
struct hkShape_s00b5_09b0;
hkShape_s00b5_09b0* __cdecl GetShapeFromPackfile(hkBinaryPackfileReader* pk);   // 0xb63fb0
void __cdecl BuildShapeBody(hkShape_s00b5_09b0* shape, float scale, void* dst);   // 0x1127680
__declspec(align(16)) struct ShapeInit {
    RefObj* out;                                                // 0
    u32 a, b;                                                   // 4, 8
    hkShape_s00b5_09b0* shape;                                             // 0xc
    float one;                                                  // 0x10
    int kind;                                                   // 0x14
    hkReferencedObject_s00b5_09b0* contents;                               // 0x18
    u32 pad1c;
    float f20, f24;
    u32 p28, p2c;
    float f30, f34, f38, f3c, f40, f44, f48, f4c, f50, f54, f58, f5c, f60, f64, f68, f6c;
    u32 z70;
};
struct ShapeHolder {
    char pad[0x20];
    char dst[1];                                                // 0x20
    void Prepare(ShapeInit* s);                                 // 0xb4f610
};
__declspec(align(16)) struct hkVector4 { float x, y, z, w; };
struct hkShape2 : hkReferencedObject_s00b5_09b0 {
    u32 pad[(0x60 - 8) / 4];
    hkShape2(void* planetModel);                                // 0xb4ffb0
    static void* operator new(unsigned n) {
        void* p = g_hkMemory->allocateChunk((int)n, 0x24);
        ((hkReferencedObject_s00b5_09b0*)p)->memSize = (u16)n;
        return p;
    }
};
class hkRigidBodyCinfo { public:
    u32 filter;                                                 // 0
    hkShape2* shape;                                            // 4
    u32 pad0[(0x94 - 8) / 4];
    float v[4];                                                 // 0x94 (hkVector4 scale: 1,1,1,0)
    u32 pad1[(0xac - 0xa4) / 4];
    float f;                                                    // 0xac
    u8 motion;                                                  // 0xb0
    u8 m1, m2, m3;
    u32 pad2[2];
    hkRigidBodyCinfo();                                         // 0x1087ed0
};
class hkRigidBody_s00b5_09b0 { public:
    void setPosition(const hkVector4& p);                       // 0x1087820
    void addProperty(u32 key, unsigned __int64 value);          // 0x10825a0
};
class hkWorld_s00b5_09b0 { public:
    void* addEntity(hkRigidBody_s00b5_09b0* b, int mode);                  // 0x1082ee0
    void updateCollisionFilterOnWorld(int a, int b);            // 0x10869e0
};
struct PlanetModelB { char pad[0x24]; };
PlanetModelB* __cdecl GetPlanetModel();                         // 0xb3d350
hkRigidBody_s00b5_09b0* __cdecl CreateRigidBody(hkRigidBodyCinfo* info);   // 0xb4d880
extern hkWorld_s00b5_09b0*     g_hkWorld;                                  // 0x167ecd0
extern hkRigidBody_s00b5_09b0* g_planetBody;                               // 0x167ecd4
struct PropSet;
u8    __cdecl GetPropBool (PropSet* p, u32 id, u8 def);       // 0x64f350
float __cdecl GetPropFloat(PropSet* p, u32 id, float def);      // 0x4e1c70
extern u8 g_b0, g_b1, g_b2;                                     // 0x167ecd9 / ecda / ecd8
struct PlanetBodyData { char pad[0x34]; PlanetModelB* planet; char pad2[4]; void* mapOwner; };
struct PlanetMapOwner { VP VP VP virtual void* GetMap(); };
struct PlanetModelC { char pad[0x24]; PlanetMapOwner* owner; };
struct MapObj { char pad[8]; void* ptr; };
struct PlanetWatcher {
    char pad[0x30];
    u8 created;                                                 // 0x30
    void Update();                                              // 0xb515e0
};
void __cdecl RebuildPlanetBody();                               // 0xb4f7f0
struct NodeS { u32 first, b; NodeS* next; };
struct IterS { NodeS* node; NodeS** bucket; };
struct TblS {
    char pad0[0xc];
    int count;                                                  // 0xc
    char pad1[0x1c - 0x10];
    NodeS* freeList;                                            // 0x1c
    char pad2[0x24 - 0x20];
    NodeS* poolBegin;                                           // 0x24
    NodeS* poolEnd;                                             // 0x28
    char pad3[0x30 - 0x2c];
    NodeS* inlineNode;                                          // 0x30
    IterS* erase(IterS* out, NodeS* node, NodeS** bucket);      // 0xb51640
};
struct RangeOut { NodeA* first; NodeA** firstBucket; NodeA* last; NodeA** lastBucket; };
struct RehashResult { bool need; u32 newCount; };
struct RehashPolicy { void GetRehashRequired(RehashResult* out, u32 buckets, u32 count, u32 add); };   // 0x921440
void* __cdecl operator_new_a(unsigned n, unsigned align, int a, const char* name, int b, int c, const char* file, int line);   // 0xf473d0
void* __cdecl operator_new_b(unsigned n, const char* name, int a, int b, const char* file, int line);   // 0xf473a0
struct TblA {
    char pad0[4];
    NodeA** buckets;                                            // 4
    u32 bucketCount;                                            // 8
    int count;                                                  // 0xc
    RehashPolicy policy;                                        // 0x10
    NodeA* DoFindNode(NodeA* head, const void* key, u32 code);  // 0xb4fae0
    void DoRehash(u32 n);                                       // 0xb4fa20
    RangeOut* equal_range(RangeOut* out, const u32* key);       // 0xb51780
    void* DoInsertValue(void* out, const void* v, int tag);     // 0xb51840
};
struct IterA { NodeA* node; NodeA** bucket; };
struct NodeB { u32 key[4]; NodeB* next; };                      // 0x14 bytes
struct InsertOut { NodeB* node; NodeB** bucket; u8 inserted; };
struct TblB {
    char pad0[4];
    NodeB** buckets;                                            // 4
    u32 bucketCount;                                            // 8
    int count;                                                  // 0xc
    RehashPolicy policy;                                        // 0x10
    void DoRehash(u32 n);                                       // 0xb4fb20
    InsertOut* DoInsertKey(InsertOut* out, const u32* key, int tag);   // 0xb51930
};
// ---- items of slice s00b509b0 end

// ---- items of slice s00b51b00 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32_s00b5_1b00;
typedef unsigned char  u8_s00b5_1b00;
#define G0  virtual void z00();
#define G1  G0  virtual void z01();
#define G2  G1  virtual void z02();
#define G3  G2  virtual void z03();
#define G4  G3  virtual void z04();
#define G5  G4  virtual void z05();
#define G6  G5  virtual void z06();
#define G7  G6  virtual void z07();
#define G8  G7  virtual void z08();
#define G9  G8  virtual void z09();
#define G10 G9  virtual void z10();
#define G11 G10 virtual void z11();
#define G12 G11 virtual void z12();
#define G13 G12 virtual void z13();
#define G14 G13 virtual void z14();
#define G15 G14 virtual void z15();
#define G16 G15 virtual void z16();
#define G17 G16 virtual void z17();
#define G18 G17 virtual void z18();
#define G19 G18 virtual void z19();
#define G20 G19 virtual void z20();
#define G21 G20 virtual void z21();
#define G22 G21 virtual void z22();
#define G23 G22 virtual void z23();
#define G24 G23 virtual void z24();
#define G25 G24 virtual void z25();
#define G26 G25 virtual void z26();
#define G27 G26 virtual void z27();
#define G28 G27 virtual void z28();
#define G29 G28 virtual void z29();
#define G30 G29 virtual void z30();
#define G31 G30 virtual void z31();
#define G32 G31 virtual void z32();
#define G33 G32 virtual void z33();
#define G34 G33 virtual void z34();
#define G35 G34 virtual void z35();
#define G36 G35 virtual void z36();
#define G37 G36 virtual void z37();
#define G38 G37 virtual void z38();
#define G39 G38 virtual void z39();
#define G40 G39 virtual void z40();
#define G41 G40 virtual void z41();
#define G42 G41 virtual void z42();
#define G43 G42 virtual void z43();
#define G44 G43 virtual void z44();
#define G45 G44 virtual void z45();
struct V10 { G9  virtual float* f2c(); };          // slot 11 (0x2c)
struct V30 { G11 virtual float* f30(); };          // slot 12 (0x30)
struct V38 { G13 virtual void   f38(void*); };     // slot 14 (0x38)
struct V3C { G14 virtual void   f3c(void*); };     // slot 15 (0x3c)
struct VB8 { G45 virtual int    fB8(u32_s00b5_1b00); };       // slot 46 (0xb8)
struct VOB { G2  virtual void   f0c(void*, float, void*); }; // slot 3 (0xc)
struct Ext {
    void  FUN_00921260(u32_s00b5_1b00, u32_s00b5_1b00, u32_s00b5_1b00, u32_s00b5_1b00, u32_s00b5_1b00);   // eastl::fixed_pool_base::init
    u32_s00b5_1b00   FUN_00921360(u32_s00b5_1b00);
    void  FUN_00921440(void*, u32_s00b5_1b00, u32_s00b5_1b00, u32_s00b5_1b00);
    u32_s00b5_1b00   FUN_00c763d0(u32_s00b5_1b00);
    int*  FUN_00b51780(void*, u32_s00b5_1b00);
    void  FUN_00833840(void*, void*);
    void  FUN_00645ed0(void*, void*);
    void  FUN_00b4f930(void*, void*, void*);
    void  FUN_00b4f8a0(void*, void*, void*);
    u32_s00b5_1b00   FUN_00b576d0(void*);
    void  FUN_00b4fbd0(u32_s00b5_1b00);
    void  FUN_007611f0(void*, u32_s00b5_1b00);
    void  FUN_00c41d60(void*);
};
struct Body {
    void FUN_01087820(void*);
    void FUN_01087840(void*);
    void FUN_0108dde0(void*);
};
void __cdecl FUN_00f47380(void*);
int* __cdecl FUN_00b51e30(int*, unsigned);
void __cdecl FUN_00b51e80(unsigned, float);
void __cdecl FUN_00b51040(void*, float);
void __cdecl FUN_00b520a0();
int  __cdecl FUN_00b521f0(void*);
unsigned __cdecl FUN_00b52230(void*, void*);
void __cdecl FUN_00b523e0(void*, void*);
char __cdecl FUN_0059ab70(void*);
void __cdecl FUN_00b4dfe0(void*, void*, void*);
void __cdecl FUN_00b4e0c0(void*, void*, void*);
void __cdecl FUN_00b54000(void*, void*);
struct Big {
    int   M_b51b00(unsigned a0, int a1, int a2, int a3, int a4, int a5, int* a6);
    void** M_b51bb0(void** out, int* key);
    int   M_b51c20(int* key);
    int** M_b51cc0(int** out, int* node, int** slot);
    void  M_b51d50(float dt);
    void  M_b51df0(unsigned a, unsigned b);
    void  M_b51ee0();
    void  M_b52020(int* p);
    int** M_b52120(int** out, int* key, int* extra);   // returns `out` in eax (both paths)
    u32_s00b5_1b00   FUN_00c763d0(u32_s00b5_1b00);
};
// ---- items of slice s00b51b00 end

// ---- items of slice s00b537f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int  FUN_00b53940(void*);
extern "C" void FUN_00b4d8e0(void*, int);
extern "C" void FUN_00b4e1d0(void*, int);
extern "C" void FUN_00b658c0(void*, void*);
extern "C" void operator_delete(void*);
extern "C" int  gEmptyString16;
extern "C" int  eastl_sprintf(void* s, const char* fmt, ...);
extern int* g_1569c9c;
extern int  g_1569ca0;
extern int* g_arr12;   // 0x1569cbc
extern int  g_cnt12;   // 0x1569cc0
extern "C" void   FUN_00b3d350();                       // 0x00b3d350  SP::PlanetModel()
extern "C" void*  FUN_010c05d0(const float* v, float f);// 0x010c05d0  hkBoxShape::hkBoxShape
extern "C" void*  FUN_010bfeb0(void* self, const void* shape, const float* v); // 0x010bfeb0
extern "C" void*  FUN_01083320(void* world, void* phantom);  // 0x01083320 hkWorld::addPhantom
extern "C" void   FUN_0109ae60(void* self);             // 0x0109ae60 removeReference
extern "C" void   FUN_010c2570(void* collector);        // 0x010c2570 hkAllCdPointCollector::sortPoints
extern "C" void   FUN_01083400(void* world, void* phantom);  // 0x01083400 hkWorld::removePhantom
extern "C" char   DAT_01569aba;                         // 0x01569aba  symmetry enabled flag
extern "C" float  DAT_015ba104;                         // 0x015ba104  box hull thickness
extern "C" float  DAT_01471064;                         // 0x01471064  one half
extern "C" float  DAT_01461294;                         // 0x01461294
extern "C" void*  HKMEM_S_INSTANCE;                     // 0x016e4178  hkMemory::s_instance
extern "C" void* HKWORLD_S_INSTANCE;    // (declared above)
extern "C" int*  FUN_00496140(int* out, int which);   // 0x00496140  D961::Find
extern "C" void* FUN_00921340(int a);                 // 0x00921340
extern "C" const float F_013f0620;                    // 0x013f0620
extern "C" const float F_01470f1c;                    // 0x01470f1c
typedef unsigned int uint;
struct __declspec(align(16)) Vec4_s00b5_37f0 { float x, y, z, w; };
struct EIt { void* node; void* pad; };
struct HT {
    int    f00;          // +0
    void** buckets;      // +4
    int    bucketCount;  // +8
    EIt find(const uint& k) const;
};
struct hkBool_s00b5_37f0 { char b; };
struct CObj {
virtual void* m00();
virtual void* m01();
virtual void* m02();
virtual void* m03();
virtual void* m04();
virtual void* m05();
virtual void* m06();
virtual void* m07();
virtual void* m08();
virtual void* m09();
virtual void* m10();
    virtual void* m11();                 // 0x2c
    virtual void* m12();                 // 0x30
    virtual void* m13();
    virtual void  m14(const void*);      // 0x38
virtual void* m15();
virtual void* m16();
virtual void* m17();
virtual void* m18();
virtual void* m19();
virtual void* m20();
virtual void* m21();
virtual void* m22();
virtual void* m23();
    virtual void  m24(const void*);      // 0x60
    virtual void* m25();
    virtual void* m26();                 // 0x68
    virtual void* m27();
    virtual float m28();                 // 0x70
virtual void* m29();
virtual void* m30();
virtual void* m31();
virtual void* m32();
virtual void* m33();
virtual void* m34();
virtual void* m35();
virtual void* m36();
virtual void* m37();
virtual void* m38();
virtual void* m39();
virtual void* m40();
virtual void* m41();
virtual void* m42();
virtual void* m43();
virtual void* m44();
    virtual void* m45();
    virtual int   m46(int);              // 0xb8
    // non-virtual thiscall externals (not defined here)
    float  getMass();
    void   setMotionType(int, int, int);
    void   setPosition(const void*);
    void   setLinearVelocity(const void*);
    void   setTranslation(const void*);
    hkBool_s00b5_37f0 isActive();
    void   activate();
    void   d1df0(void*, void*);
    void   d3d0(const void*);
    void   d530(const void*, int);
    void   d7e0(const void*);
    int    d2e0();
    void   d570(const void*);
    void   d8ae0();
};
extern HT HT_167ed58, HT_16801a8, HT_1682a48, HT_16852e8, HT_1569cb8;
extern CObj* g_167ecdc;
struct EIt12 { int a, b, c; };
struct S12   { uint key; int b, c; };
struct HT12  { EIt12 find(const uint& k) const; void** add(const S12* k); };
struct ObjB  { void d770(); };
extern HT12 g_ht12;    // 0x1569cb8
extern "C" void* FUN_00b51e80_s00b5_37f0(S12*, float);
extern "C" void*  FUN_0108c750(void* self, void* shape, const void* xform, uint info); // 0x0108c750
extern "C" void   FUN_0107db10(void* mem, uint size, uint align);  // 0x0107db10 deallocateChunk
extern "C" void*  TlsGetValue_fn(uint idx);             // [0x13cc2bc] kernel32!TlsGetValue
struct HkMemory {
virtual void* v00();
virtual void* v01();
virtual void* v02();
virtual void* v03();
    virtual void* alloc(uint size, uint align);          // +0x10
};
struct HkBodyKey {
virtual void* k00();
virtual void* k01();
virtual void* k02();
    virtual void* match(const void* key);                // +0x0c
};
struct EditEntity {
    char  _pad00[0x1c];
    void* mShape;        // +0x1c  fallback collideable shape
    char  _pad20[0x58 - 0x20];
    void* mBodyTransform; // +0x58  body transform (shape at +0x10)
    int*  Find(int* out, int which);        // 0x00496140
};
struct HkPhantomQuery {
virtual void* q00();
virtual void* q01();
virtual void* q02();
virtual void* q03();
virtual void* q04();
virtual void* q05();
virtual void* q06();
virtual void* q07();
virtual void* q08();
virtual void* q09();
virtual void* q10();
virtual void* q11();
    virtual void  query(const void* a, void* collector, int flag);   // +0x30
};
struct HkPointCollector {
    char  _pad00[0x08];
    void* mVtable;       // +0x08
    float mRadius;       // +0x0c
    void* mPoints;       // +0x10
    int   mCount;        // +0x14
    char  _pad18[0x1c - 0x18];
    int   mCapacity;     // +0x1c
};
struct HkCdPoint {
    float mPos[3];       // +0x00 contact position
    char  _pad0c[0x28 - 0x0c];
    void* mBody;         // +0x28
    char  _pad2c[0x30 - 0x2c];
};
struct FixedPool {
    void* mpHead;                                             // +0x00
    void  FUN_00921260(void* mem, uint size, int a, int b, int c);  // 0x00921260 init
    uint  FUN_009213c0(void* p);                              // 0x009213c0
};
struct C54640 {
    char  _pad0[0x08];
    uint  m08;                    // +0x08
    void* m0c;                    // +0x0c
    float m10;                    // +0x10
    float m14;                    // +0x14
    float m18;                    // +0x18
    char  _pad1[0x34 - 0x1c];
    char  m34[0x10];              // +0x34
    char  m44[0x43c - 0x44];
    char  m43c[0xc00];            // +0x43c  pool storage
    char  m103c[0x04];            // +0x103c
    int   FUN_00b54640(int a2);
    void  FUN_00b516d0(void* a, void* b, void* c, void* d, void* e, void* f,
                       void* g);                                 // 0x00b516d0
    void  FUN_00b5d220(uint n);                                  // 0x00b5d220
    void  FUN_00b53410(int a, int* b, int c, int* d);            // 0x00b53410
};
// ---- items of slice s00b537f0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
extern "C" void FUN_00b537f0(CObj* p, int a2, char a3, char a4);  // 0x00b537f0 (stays in the slice: not this object's)

// ---- items of slice s00b547b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl FUN_00b51bb0(void* out, const void* key);              // 0x00b51bb0
extern "C" void __cdecl FUN_00b52120(void* dst, void* a, uint32_t flags);      // 0x00b52120
extern "C" uint8_t* DAT_0167ed44;   // list begin (0x0167ed44)
extern "C" uint8_t* DAT_0167ed48;   // list end   (0x0167ed48)
extern "C" void* __cdecl FUN_00b3d310(...);                    // 0x00b3d310 (variadic)
extern "C" void  __cdecl FUN_00b51840(void* a, void* b, uint32_t c);  // 0x00b51840 (ecx=global)
extern "C" void* __cdecl FUN_00b51780(void* a, void* b);       // 0x00b51780
extern "C" char  __cdecl SP_GetPropertyAsKey(void* info, uint32_t key, void* out); // 0x006a1250
extern "C" void  __cdecl FUN_00b4d540(void* dst);              // 0x00b4d540
extern "C" char  __cdecl FUN_00b510b0(void* a, void* b);       // 0x00b510b0
extern "C" int   __cdecl FUN_00b4f660(int a, float s, void* v, int b);  // 0x00b4f660
extern "C" void  __cdecl FUN_00b4d3f0(void* dst);            // 0x00b4d3f0
extern "C" void  __cdecl FUN_00b4d5d0(void* dst, int shape, float s, int kind, int a, int b); // 0x00b4d5d0
extern "C" void  __cdecl FUN_01127680(int shape, float s, void* out);   // hkInertiaTensorComputer
extern "C" int   __cdecl FUN_00b64a00(int id, float s);        // 0x00b64a00
extern "C" void  __cdecl FUN_01081bb0(float s);                // 0x01081bb0 (hkMatrix3::mul)
extern "C" float DAT_0167ecf4, DAT_0167ecf8, DAT_0167ecfc;     // default caps axis extents
extern "C" float DAT_01481064;                                 // 0.5f
struct EastlFixedPool {
    void*    mpHead;        // +0x00
    uint32_t mnBegin;       // +0x04
    uint32_t mnBlockSize;   // +0x08
    uint32_t mnEnd;         // +0x0c
    uint32_t mnBase;        // +0x10
    uint32_t mnAlign;       // +0x14
    void init(void* begin, uint32_t size, uint32_t block, uint32_t align, uint32_t flags); // 0x00921260 (thiscall)
};
struct PoolScratch {
    uint32_t m0, m4, m8;
    uint32_t calc(void* list);      // 0x009213c0
};
class cPoolHolderA {
public:
    uint32_t pad00[2];                  // +0x00
    uint32_t mnCapacity;                // +0x08
    void*    mpBucketList;              // +0x0c
    uint32_t m10;                       // +0x10
    uint32_t m14;                       // +0x14
    uint32_t m18;                       // +0x18
    uint8_t  pad1c[0x34 - 0x1c];        // +0x1c
    uint32_t mArenaHead;                // +0x34
    uint8_t  pad38[0x43c - 0x38];       // +0x38
    uint8_t  mPoolBuf[0xc00];           // +0x43c
    uint32_t mArenaEnd;                 // +0x103c
    cPoolHolderA* Init(int a2, int a3);                 // thiscall, ret 8
    void* RegisterPool(void* p, int a2, const int* r1, const int* r2, int v, const int* r3, EastlFixedPool* pool); // 0x00b516d0
    void Resize(uint32_t n);                            // 0x00b5d220
};
class cPoolHolderB {
public:
    uint32_t pad00[2];                  // +0x00
    uint32_t mnCapacity;                // +0x08
    void*    mpBucketList;              // +0x0c
    uint32_t m10;                       // +0x10
    uint32_t m14;                       // +0x14
    uint32_t m18;                       // +0x18
    uint8_t  pad1c[0x34 - 0x1c];        // +0x1c
    uint32_t mArenaHead;                // +0x34
    uint8_t  pad38[0x43c - 0x38];       // +0x38
    uint8_t  mPoolBuf[0x1000];          // +0x43c
    uint32_t mArenaEnd;                 // +0x143c
    cPoolHolderB* Init(int a2, int a3);
    void* RegisterPool(void* p, int a2, const int* r1, const int* r2, int v, const int* r3, EastlFixedPool* pool); // 0x00b51a50
    void Resize(uint32_t n);                            // 0x00b4fbd0
};
class cPoolHolderC {
public:
    uint32_t pad00[2];                  // +0x00
    uint32_t mnCapacity;                // +0x08
    void*    mpBucketList;              // +0x0c
    uint32_t m10;                       // +0x10
    uint32_t m14;                       // +0x14
    uint32_t m18;                       // +0x18
    uint32_t mArenaHead;                // +0x34
    uint8_t  pad38[0x5c - 0x38];        // +0x38
    uint8_t  mPoolBuf[0x80];            // +0x5c
    uint32_t mArenaEnd;                 // +0xdc
    cPoolHolderC* Init(int a2, int a3);
    void* RegisterPool(void* p, int a2, const int* r1, const int* r2, int v, const int* r3, EastlFixedPool* pool); // 0x00b51b00
    void Resize(uint32_t n);                            // 0x00b4fbd0
};
struct SPKeyPair { uint32_t lo; uint32_t hi; };
class cPairMapInner {
public:
    uint32_t m00;                  // +0x00
    uint32_t* mpTable;             // +0x04
    int32_t  mnIndex;              // +0x08
    uint32_t* Lookup(const SPKeyPair* key);     // 0x00b54a40 (thiscall, ret 4), returns slot+8
};
struct LookupRec { uint32_t m00, m04, m08; };   // &local_18
class cPairMap {
public:
    void      Insert(uint32_t a, uint32_t b, float c);   // 0x00b54b40 (thiscall, ret 0xc)
    uint8_t   pad[0x1858];
    cPairMapInner mInner;                       // +0x1858
};
struct SPListObj { void Destroy(); };  // 0x00b51ee0 (thiscall, no args)
struct SPListEntry { int32_t mnType; SPListObj* mpObj; };  // 8 bytes
extern "C" int   __cdecl FUN_00b51040_s00b5_47b0(void* a, float s);       // 0x00b51040
struct CmdNode {
    int32_t m00, m04, m08, m0c, m10, m14, m18;
    void*   mpBack;             // +0x1c
};
struct CmdLink {
    int32_t m00;
    int32_t m04;
    void*   mpField8;           // +0x08
};
struct CmdChain { void Unlink(); };                 // 0x00b4d770 (thiscall)
struct CmdTail  { void Run(); };                    // 0x00b545b0 (thiscall)
struct Build830 { uint8_t b[0x84]; void* Build(int a, int b2); }; // 0x00b4f830 (thiscall)
struct ReqRec {                       // &local_110
    void*    mpA;                     // +0x00  (= uVar1)
    uint32_t m04;                     // +0x04  (= local_1b0)
    uint32_t m08;                     // +0x08  (= local_1ac)
};
struct Key3 { uint32_t a, b, c; };    // &local_1a0
struct ShapeObj {                     // param_1
    int32_t m00, m04, m08, m0c, m10, m14, m18, m1c, m20;
    float   f24;                      // +0x24
    uint8_t pad28[0x70 - 0x28];
    float   f70, f74, f78, f7c, f80, f84;   // +0x70..+0x87
    uint8_t pad88[0x90 - 0x88];
    void*   mpInfo;                   // +0x90
};
struct ShapeReq {                     // param_3
    int32_t mpShape;                  // +0x00
    int32_t m04;                      // +0x04
    int32_t mnFlags;                  // +0x08
    int32_t m0c, m10, m14;
    uint8_t mbFlag;                   // +0x18
};
struct ExtRec { float x, y, z, w; };  // &local_1cc
struct WorkRec {                      // generic HK working record
    uint8_t b[0x140];
};
// ---- items of slice s00b547b0 end

// ---- items of slice s00b55680 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ListObject {
    virtual void v0();                  // slot 0 (+0x00)
    virtual void v1();                  // slot 1 (+0x04)
    virtual int  GetType();             // slot 2 (+0x08)  returns 0xe for the wrapper kind
    uint16_t mField04;                  // +0x04
    uint16_t mField06;                  // +0x06
    void*    mValue;                    // +0x08
    uint32_t mField0C;                  // +0x0c
    ListObject* mChild;                 // +0x10
};
struct CellUpdateArg {
    uint32_t mPad[0x1c / 4];            // +0x00..0x1b
    ListObject* mpObject;               // +0x1c
};
struct SPListEntry_s00b5_5680 {
    int32_t mnType;                     // +0x00
    void*   mpObj;                      // +0x04
};
struct SPListVec {
    SPListEntry_s00b5_5680* mpBegin;               // +0x00
    SPListEntry_s00b5_5680* mpEnd;                 // +0x04
    SPListEntry_s00b5_5680* mpCap;                 // +0x08
    void Realloc(SPListEntry_s00b5_5680* at, const SPListEntry_s00b5_5680* v); // 0x00b534c0
    void push_back(const SPListEntry_s00b5_5680& v)
    {
        if (mpEnd < mpCap) {
            SPListEntry_s00b5_5680* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            Realloc(mpEnd, &v);
        }
    }
};
extern "C" SPListVec g_167ed44;         // 0x0167ed44
// ---- items of slice s00b55680 end

// ---- items of slice s00b56fe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
struct PropPair { int v; int w; };
struct HkRelativePtr {
    char m_pad00[0xc];
    HkRelativePtr* m_next;  // +0xc
    int m_offset;           // +0x10
    char m_pad14[0x4];
    uint8_t m_isRelative;   // +0x18
};
struct HkPtrPair {
    HkRelativePtr* m_first;   // +0x0
    HkRelativePtr* m_second;  // +0x4
    char m_pad08[0x14];
    uint32_t m_flag;          // +0x1c
};
static inline void* ResolveHkPtr(HkRelativePtr* p)
{
    if (p->m_isRelative == 1)
        return (char*)p + p->m_offset;
    return 0;
}
struct HkPtrConverter {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14(void** out, int count, HkPtrPair* pair);
    void Convert(HkPtrPair* pair);
};
void* __cdecl opnew_f473a0(void* allocator, const char* name, int a, int b,
                           const char* file, unsigned size);  // 0x00f473a0
void __cdecl opdel_f47380(void* p);                          // 0x00f47380
struct HkNodeData {
    uint32_t m_a;   // +0x0
    uint32_t m_b;   // +0x4
    uint32_t m_c;   // +0x8
};
struct HkPoolNode {
    union {
        HkPoolNode* m_next;  // +0x0 (free-list link)
        uint32_t m_a;        // +0x0 (payload copy)
    };
    uint32_t m_b;            // +0x4
    uint32_t m_c;            // +0x8
    uint32_t m_flags;        // +0xc
    char m_tail[0xd1 - 0x10];
};
struct HkNodePool {
    char m_pad00[0x1c];
    HkPoolNode* m_freeList;  // +0x1c
    char m_pad20[0xc];
    void* m_allocator;       // +0x2c
    void __thiscall AddNode(const HkNodeData* data);
};
struct AllocVec {
    void* m_allocator;     // +0x00
    void* m_begin;         // +0x04
    uint32_t m_capacity;   // +0x08
    uint32_t m_size;       // +0x0c
    char m_pad10[0xc];
    void* m_freeList;      // +0x1c
    char m_pad20[0x4];
    void* m_poolBegin;     // +0x24
    void* m_poolEnd;       // +0x28
    char m_pad2c[0x4];
    void* m_empty;         // +0x30

    void __thiscall Deallocate(void* begin, uint32_t capacity);  // 0x00a42fe0
    void Clear();
};
void AllocVec::Clear()
{
    Deallocate(m_begin, m_capacity);
    void* p = m_begin;
    m_size = 0;
    if (m_capacity > 1 && p != m_empty) {
        if (p >= m_poolBegin && p < m_poolEnd) {
            *(void**)p = m_freeList;
            m_freeList = p;
        } else {
            opdel_f47380(p);
        }
    }
}
struct HkContainerOwner {
    void* m_vptr;          // +0x00
    AllocVec m_vec2;       // +0x04
    char m_gap[0x1858 - 0x04 - sizeof(AllocVec)];
    AllocVec m_vec1;       // +0x1858
    void Destroy();
};
struct HkValueRange {
    uint32_t m_lo;  // +0x0
    uint32_t m_hi;  // +0x4
};
struct HkRangeSource {
    char m_pad00[0x8];
    uint32_t m_lo;  // +0x8
    uint32_t m_hi;  // +0xc
};
struct HkRefMap {
    char m_pad00[0x34];
    uint32_t* FindRef(HkValueRange* range);  // 0x00b577d0
    void Erase(HkValueRange* range);         // 0x00b51c20
};
struct HkRefOwner {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14(HkValueRange* range, int a, int b);
    HkRefMap m_map;    // +0x04
    void Remove(HkRangeSource* range);
};
uint32_t g_167ecdc_s00b5_6fe0;  // 0x0167ecdc
void* __cdecl FUN_00b53940_s00b5_6fe0(void* obj);  // 0x00b53940
struct HkWorld {
    void AddPair(void* a, void* b, float t);  // 0x00b54b40
    void RemovePhantom(void* phantom);        // 0x01083400
};
struct HkHashIter {
    void* m_node;    // +0x0
    void* m_bucket;  // +0x4
};
struct HkHashTable {
    void* m_allocator;       // +0x00
    void** m_buckets;        // +0x04
    uint32_t m_bucketCount;  // +0x08
    uint32_t m_size;         // +0x0c
    char m_pad10[0xc];
    void* m_freeList;        // +0x1c
    char m_pad20[0x4];
    void* m_poolBegin;       // +0x24
    void* m_poolEnd;         // +0x28
    char m_pad2c[0x4];
    void* m_empty;           // +0x30

    uint32_t* FindRef(HkValueRange* key);                  // 0x00b577d0
    HkHashIter* Find(HkHashIter* out, HkValueRange* key);   // 0x00b51bb0
    void Erase(HkValueRange* key);                          // 0x00b51c20
    void Begin(HkHashIter* out);                            // 0x00594410
    void DoFreeNodes(void** buckets, uint32_t count);       // 0x00a1b6c0
};
struct HkBody {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void* v20();  // +0x20

    char m_pad04[0x8];
    void* m_handle;       // +0x0c
    char m_pad10[0x88 - 0x10];
    uint32_t m_field88;   // +0x88

    PropPair* getProp(PropPair* out, int key);  // 0x00496140
};
struct HkSelectOwner {
    char m_pad00[0x4];
    HkRefMap m_refs;      // +0x04
    char m_gap[0x1858 - 0x4 - sizeof(HkRefMap)];
    HkHashTable m_table;  // +0x1858
    void Select(HkPtrPair* pair);
};
void* g_18c6de8 = 0;  // 0x018c6de8
// ---- items of slice s00b56fe0 end

// ---- items of slice s00b5a260 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct HKWorldCinfo {
    uint8_t pad0[0x10];
    float   f10, f14, f18, f1c;     // +0x10
    uint8_t pad20[0x48];
    float   f68, f6c, f70;          // +0x68
    uint8_t pad74[0x20];
    uint8_t b94, b95;               // +0x94
    uint8_t pad96[0x10];

    void __thiscall ctor();                       // 0x010880e0
    void __thiscall setBroadPhaseWorldSize(float);  // 0x010881d0
};
struct hkBool_s00b5_a260 {
    uint8_t v;
    hkBool_s00b5_a260(int x) { v = (uint8_t)x; }
};
struct hkWorld_s00b5_a260 {
    uint8_t pad00[0x80];
    void*   field80;                // +0x80
    hkWorld_s00b5_a260* __thiscall CreateWorld(const HKWorldCinfo*, u32);      // 0x010840e0
    void __thiscall setCollisionFilter(void*, hkBool_s00b5_a260, int, int);    // 0x01086f80
};
struct hkGroupFilter {
    hkGroupFilter* __thiscall ctor();                    // 0x010c3cb0
    void __thiscall FUN_010c3c60(int, int);              // 0x010c3c60
    void __thiscall enableCollisionsBetween(int, int);   // 0x010c3c20
};
typedef void* (__thiscall *VFnR1)(void*);
typedef void* (__thiscall *VFnR2)(void*, int);
typedef void* (__thiscall *VFnAlloc)(void*, int, int);
void  FUN_00b530e0(void*, void*);            // 0x00b530e0
void* FUN_006abeb0(int);                     // 0x006abeb0  factory(size)
void  CreateHavokEntityForObject(void*, void*, void*, void*);  // 0x00b56090
void  registerAllAgents(void*);              // 0x010c25a0
void  FUN_00b54890(void*, void*, void*);     // 0x00b54890
void  FUN_00b54970(void*, void*, void*);     // 0x00b54970
void  FUN_010834f0(void*, void*);            // 0x010834f0
#define DAT_0167ecd0 (*(void**)0x0167ecd0)      // hkWorld*
#define DAT_0167ecdc (*(void**)0x0167ecdc)      // editor callback object
#define DAT_016e4178 (*(void**)0x016e4178)      // hkMemory::s_instance
#define DAT_01569a94 (*(uint8_t*)0x01569a94)
#define DAT_01569a98 (*(float*)0x01569a98)
#define DAT_01569a9c (*(float*)0x01569a9c)
#define DAT_01569aa0 (*(float*)0x01569aa0)
#define DAT_0156b6ec (*(float*)0x0156b6ec)
#define DAT_013eb95c (*(float*)0x013eb95c)
struct Map14c8 {
    void*   head;       // +0x00
    int*    table;      // +0x04
    int     count;      // +0x08
    int* __thiscall FUN_00b41b30(void* out, void* key);   // 0x00b41b30
};
struct HavokSystem {
    uint8_t pad00[0x20];
    int     busy20;             // 0x20
    uint8_t pad24[0x0c];
    uint8_t b30;                // 0x30
    uint8_t pad31[0x2f];
    void**  begin;              // 0x60
    void**  end;                // 0x64
    uint8_t pad68[0x1460];
    Map14c8 map;                // 0x14c8

    void __thiscall FUN_00b5a260(void* p2, void* p3);
    void __thiscall FUN_00b5a2d0();
    void __thiscall FUN_00b5a390();
    void __thiscall FUN_00b5a410();
    int  __thiscall FUN_00b532f0(void* u);                // 0x00b532f0
};
// ---- items of slice s00b5a260 end

// ---- items of slice s00b5a750 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool sRebuildBuildingBodies;      // 0x0167ece0
extern bool sRebuildPlanetBodies;        // 0x0167ecdb
extern bool sUseModelCollision;          // 0x0167ecda
extern float sCollisionScaleA;           // 0x01569b0c
extern float sCollisionScaleB;           // 0x01569b10
extern float sPhantomHeight;             // 0x01569ad0
extern float sPhantomRadius;             // 0x01569ad4
extern float sTreePhantomExtraHeight;    // 0x01569ae4
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16
struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
struct Matrix3 {
    float m[3][3];
    Matrix3& Assign(const Matrix3& other);                                   // 0x0041cb40
};
__forceinline Vector3 operator*(const Vector3& v, const Matrix3& m)
{
    Vector3 r;
    r.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0];
    r.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1];
    r.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2];
    return r;
}
namespace rw {
namespace math {
namespace fpu {
Quaternion QuaternionFromMatrix33(const Matrix3& m, float tolerance);         // 0x00472b80
}
}
}
Quaternion QuaternionFromMatrix(const Matrix3& m);                            // 0x0046d660
struct cSPTransform_s00b5_a750 {
    u16 mFlags;                        // 0x00
    u16 mPad;
    Vector3 mPosition;                 // 0x04
    float mScale;                      // 0x10
    Matrix3 mRotation;                 // 0x14
    cSPTransform_s00b5_a750(const cSPTransform_s00b5_a750& other);                                 // 0x0040ce80
    cSPTransform_s00b5_a750& operator=(const cSPTransform_s00b5_a750& other);                      // 0x00537dc0
};
struct __declspec(align(16)) hkVector4_s00b5_a750 {
    float x, y, z, w;
    void set(float ax, float ay, float az, float aw) { x = ax; y = ay; z = az; w = aw; }
};
struct __declspec(align(16)) hkQuaternion_s00b5_a750 { hkVector4_s00b5_a750 m_vec; };
struct __declspec(align(16)) hkRotation_s00b5_a750 {
    hkVector4_s00b5_a750 m_col0, m_col1, m_col2;
    void set(const hkQuaternion_s00b5_a750& q);                                         // 0x010824a0
};
struct __declspec(align(16)) hkTransform_s00b5_a750 { hkRotation_s00b5_a750 m_rotation; hkVector4_s00b5_a750 m_translation; };
class hkMemory_s00b5_a750 {
public:
    PV4
    virtual void* allocateChunk(int nbytes, int cl);                         // 0x10
    static hkMemory_s00b5_a750* s_instance;                                             // 0x016e4178
    static hkMemory_s00b5_a750& getInstance() { return *s_instance; }
};
class hkReferencedObject_s00b5_a750 {
public:
    virtual ~hkReferencedObject_s00b5_a750();                                           // 0x00 (scalar deleting)
    u16 m_memSizeAndFlags;                                                   // 0x04
    u16 m_referenceCount;                                                    // 0x06
    __forceinline void removeReference()
    {
        if (m_memSizeAndFlags != 0)
        {
            --m_referenceCount;
            if (m_referenceCount == 0)
                delete this;
        }
    }
};
class hkShape_s00b5_a750 : public hkReferencedObject_s00b5_a750 {
public:
    void* operator new(size_t nbytes)
    {
        hkReferencedObject_s00b5_a750* b = (hkReferencedObject_s00b5_a750*)hkMemory_s00b5_a750::getInstance().allocateChunk((int)nbytes, 0x24);
        b->m_memSizeAndFlags = (u16)nbytes;
        return b;
    }
    void operator delete(void*) {}
};
class hkCapsuleShape : public hkShape_s00b5_a750 {
public:
    hkCapsuleShape(const hkVector4_s00b5_a750& vertexA, const hkVector4_s00b5_a750& vertexB, float radius);   // 0x010c2730
    u8 pad[0x30 - 8];
};
class hkSphereShape : public hkShape_s00b5_a750 {
public:
    hkSphereShape(float radius);                                             // 0x010c3770
    u8 pad[0x10 - 8];
};
class hkWorldObject_s00b5_a750 : public hkReferencedObject_s00b5_a750 {
public:
    void* m_world;                                                           // 0x08
    void* m_userData;                                                        // 0x0c
    void addProperty(u32 key, unsigned __int64 value);                       // 0x010825a0
    void removeReference();                                                  // 0x0109ae60 (out of line here)
};
class hkRigidBody_s00b5_a750 : public hkWorldObject_s00b5_a750 {
public:
    void setRotation(const hkQuaternion_s00b5_a750& q);                                 // 0x01087840
    void setPosition(const hkVector4_s00b5_a750& p);                                    // 0x01087820
    void setMotionType(int motionType, int activation, int collisionFilterUpdate);   // 0x01087520
};
class hkPhantom_s00b5_a750 : public hkWorldObject_s00b5_a750 {};
class hkSimpleShapePhantom : public hkPhantom_s00b5_a750 {
public:
    void* operator new(size_t nbytes)
    {
        hkReferencedObject_s00b5_a750* b = (hkReferencedObject_s00b5_a750*)hkMemory_s00b5_a750::getInstance().allocateChunk((int)nbytes, 0x2e);
        b->m_memSizeAndFlags = (u16)nbytes;
        return b;
    }
    void operator delete(void*) {}
    hkSimpleShapePhantom(const hkShape_s00b5_a750* shape, const hkTransform_s00b5_a750& transform, u32 collisionFilterInfo);   // 0x0108c750
    u8 pad[0x130 - 0x10];
};
class hkBool_s00b5_a750 { public: char m_bool; };
class hkWorld_s00b5_a750 {
public:
    hkRigidBody_s00b5_a750* addEntity(hkRigidBody_s00b5_a750* entity, int activation);             // 0x01082ee0
    hkBool_s00b5_a750 removeEntity(hkRigidBody_s00b5_a750* entity);                                // 0x01083110
    hkPhantom_s00b5_a750* addPhantom(hkPhantom_s00b5_a750* phantom);                               // 0x01083320
};
class hkRigidBodyCinfo_s00b5_a750 { public:
    u32 m_collisionFilterInfo;                                               // 0x00
    hkShape_s00b5_a750* m_shape;                                                        // 0x04
    u8 pad08[0x9c - 8];
    float m_friction;                                                        // 0x9c
    float m_restitution;                                                     // 0xa0
    u8 pada4[0xb0 - 0xa4];
    u8 m_motionType;                                                         // 0xb0
    u8 padb1[0xc0 - 0xb1];
    hkRigidBodyCinfo_s00b5_a750();                                                      // 0x01087ed0
};
namespace SP {
namespace Havok {
hkRigidBody_s00b5_a750* CreateRigidBody_s00b5_a750(hkRigidBodyCinfo_s00b5_a750* info);                        // 0x00b4d880
}
}
struct Property {
    u8 pad[0x12];
    u16 mType;                                                               // 0x12
    bool* GetBool();                                                         // 0x0041e920
};
class PropertyList {
public:
    PV8 PV
    virtual bool GetProperty(u32 id, Property*& result);                     // 0x24
};
bool GetBoolProperty(PropertyList* list, u32 id, bool& value);               // 0x00407190
bool GetPropertyAsUint32(PropertyList* list, u32 id, u32& value);            // 0x004af210
struct cModel { u8 pad[0x40]; int mRefCount; };                              // 0x40
struct cModelPtr {
    cModel* mpModel;
    cModelPtr() : mpModel(0) {}
    cModelPtr(cModel* p) : mpModel(p) { if (p) p->mRefCount++; }
    ~cModelPtr();                                                            // 0x005765e0
    cModelPtr& operator=(cModel* p);                                         // 0x00478db0
};
class cModelResource {
public:
    virtual void AddRef();                                                   // 0x00
    virtual void Release();                                                  // 0x04
    PV
    virtual cModel* Load(u32 key, u32 flags, int);                           // 0x0c
};
class cModelManager_s00b5_a750 {
public:
    PV4 PV2 PV
    virtual cModelResource* GetResource(u32 id);                             // 0x1c
};
cModelManager_s00b5_a750* ModelManager();                                               // 0x0067dd80
class cGonzagoModelWorld {
public:
    PV2 PV
    virtual cModel* FindModelAt(float x, float z, int);                      // 0x0c
};
cGonzagoModelWorld* GonzagoModelWorld();                                     // 0x00b3d520
struct cCollisionRequest {
    void* mpOwner;                                                           // 0x00
    float mA;                                                                // 0x04
    float mB;                                                                // 0x08
    u32 pad0c[3];
    bool mFlag;                                                              // 0x18
};
struct cCollisionShape { u8 pad[0xc]; hkShape_s00b5_a750* mpShape; };
cCollisionShape* GetCollisionShape(void* owner, float scale, cCollisionRequest* request);   // 0x00b54c40
struct cPlanetObjectData { u8 pad[8]; Vector3 mPosition; };                   // 0x08
struct cPlanetObject {
    u32 pad00;
    u32 mFlags;                                                              // 0x04
    cSPTransform_s00b5_a750 mTransform;                                                 // 0x08
    u8 pad[0x6c - 0x08 - sizeof(cSPTransform_s00b5_a750)];
    float mRadius;                                                           // 0x6c
    u8 pad70[0x90 - 0x70];
    PropertyList* mpPropList;                                                // 0x90 (also the data with the position at +8)
};
class cCityObject {
public:
    PV8 PV2 PV
    virtual bool IsDestroyed();                                              // 0x2c
    u8 pad04[0x34 - 4];
    u8 mObjectFlags;                                                         // 0x34
    u8 pad35[0x38 - 0x35];
    Vector3 mPosition;                                                       // 0x38
    float mRadius;                                                           // 0x44
    u32 pad48;
    float mHeight;                                                           // 0x4c
    u8 pad50[0x60 - 0x50];
    u32 mID;                                                                 // 0x60
    u8 pad64[0x6c - 0x64];
    u32 mModelKey;                                                           // 0x6c
    u8 pad70[0x88 - 0x70];
    int mType;                                                               // 0x88

    cSPTransform_s00b5_a750* GetTransform();                                            // 0x00b73e70
};
struct cModelInfo_s00b5_a750 { u8 pad[4]; u32 mModelKey; u8 pad08[0x20 - 8]; u32 mFlags; };   // size 0x24
struct cModelInfoList { cModelInfo_s00b5_a750* mpBegin; cModelInfo_s00b5_a750* mpEnd; };
struct cModelInfoOwner { u8 pad[0x17c]; cModelInfoList mList; };
cModelInfoOwner* ModelInfoOwner();                                           // 0x00b3d3b0
struct CityNode { u32 key[2]; cCityObject* mpObject; u32 pad; CityNode* mpNext; };
struct CityIterator {
    CityNode* mpNode;
    CityNode** mpBucket;
    void increment()
    {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
};
struct CityMap {
    u32 pad;
    CityNode** mpBucketArray;                                                // 0x04
    u32 mnBucketCount;                                                       // 0x08
    CityIterator begin();                                                    // 0x00594410
    CityNode* endNode() { return mpBucketArray[mnBucketCount]; }
};
class cCityObjects {
public:
    CityMap* GetObjectMap();                                                 // 0x00ad2800
    Vector3* SnapToSurface(const Vector3& position);                         // 0x00b74f40
};
cCityObjects* CityObjects();                                                 // 0x00b3d3c0
struct cTerrainInfo { u8 pad[0x20]; int mWaterMode; };
cTerrainInfo* TerrainInfo();                                                 // 0x00b3d310
class cITerrainSphere_s00b5_a750 {
public:
    PV32 PV8 PV4
    virtual int GetPlanetObjects(cPlanetObject**& objects);                  // 0xb0
};
class cPlanetModel_s00b5_a750 {
public:
    u8 pad[0x24];
    cITerrainSphere_s00b5_a750* mpISphere;                                              // 0x24
    void BuildSurfaceOrientation(Quaternion& orientation, const cSPTransform_s00b5_a750& transform);   // 0x00b7f190
};
cPlanetModel_s00b5_a750* PlanetModel();                                                 // 0x00b3d350
struct BodyNode { u32 mKey; hkRigidBody_s00b5_a750* mpBody; BodyNode* mpNext; };
struct BodyIterator { BodyNode* mpNode; BodyNode** mpBucket; };
struct BodyMap {
    u32 pad00;
    BodyNode** mpBucketArray;                                                // 0x04
    u32 mnBucketCount;                                                       // 0x08
    u32 mnElementCount;                                                      // 0x0c
    u32 mRehashPolicy[3];                                                    // 0x10
    void* mpPoolHead;                                                        // 0x1c
    void* mpPoolNext;                                                        // 0x20
    void* mpPoolBegin;                                                       // 0x24
    void* mpPoolEnd;                                                         // 0x28
    u32 mnNodeSize;                                                          // 0x2c
    BodyNode** mpBucketBuffer;                                               // 0x30
    u8 mBuffers[0x1440 - 0x34];

    BodyMap(const BodyMap& other);                                           // 0x00b54640
    void DoFreeNodes(BodyNode** buckets, u32 n);                             // 0x00a1b6c0
    BodyIterator find(const u32& key);                                       // 0x00645ed0
    BodyIterator erase(BodyIterator it);                                     // 0x00b51640
    hkRigidBody_s00b5_a750*& operator[](const u32& key);                                // 0x00b54750
    BodyNode* endNode() { return mpBucketArray[mnBucketCount]; }
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    ~BodyMap()
    {
        clear();
        if (mnBucketCount > 1 && mpBucketArray != mpBucketBuffer)
        {
            if (mpBucketArray >= mpPoolBegin && mpBucketArray < mpPoolEnd)
            {
                *(void**)mpBucketArray = mpPoolHead;
                mpPoolHead = mpBucketArray;
            }
            else
                operator delete[](mpBucketArray);
        }
    }
};
struct IntNode { IntNode* mpNodeRight; IntNode* mpNodeLeft; IntNode* mpNodeParent; u32 mColor; int mValue; };
struct true_type_tag {};
struct InsertResult { IntNode* mpNode; bool mbInserted; };
struct IntSet {
    u32 pad;
    IntNode mAnchor;                                                         // 0x04 (root = mAnchor.mpNodeParent)
    InsertResult DoInsertValue(const int& value, true_type_tag);             // 0x00b54ab0
    InsertResult insert(const int& value) { return DoInsertValue(value, true_type_tag()); }
    IntNode* find(const int& key)
    {
        IntNode* pCurrent = mAnchor.mpNodeParent;
        IntNode* pRangeEnd = &mAnchor;
        while (pCurrent)
        {
            if (pCurrent->mValue < key)
                pCurrent = pCurrent->mpNodeRight;
            else
            {
                pRangeEnd = pCurrent;
                pCurrent = pCurrent->mpNodeLeft;
            }
        }
        if (pRangeEnd != &mAnchor && !(key < pRangeEnd->mValue))
            return pRangeEnd;
        return &mAnchor;
    }
};
struct BodyVector {
    hkRigidBody_s00b5_a750** mpBegin;
    hkRigidBody_s00b5_a750** mpEnd;
    bool empty() const { return mpBegin == mpEnd; }
    void push_back(hkRigidBody_s00b5_a750* const& value);                               // 0x0062dee0
};
struct PhantomVector {
    void push_back(hkSimpleShapePhantom* const& value);                      // 0x00c072f0
};
extern hkWorld_s00b5_a750* sWorld;                  // 0x0167ecd0
extern Vector3 sZeroVector;              // 0x0167ecf4
extern BodyMap sBuildingBodies;          // 0x01683e98
extern BodyVector sPlanetBodies;         // 0x01569b68
extern PhantomVector sPlanetPhantoms;    // 0x01569c00
extern IntSet sProcessedPlanetObjects;   // 0x01686738
extern u32 sModelLoadFlags;              // 0x01569b54
extern u32 sHutModelLoadFlags;           // 0x01569b64
// ---- items of slice s00b5a750 end

// ---- items of slice s00b5b540 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00b5b6f0(int);
extern "C" void FUN_00b5b730();
extern "C" void  FUN_004cd3c0(void*);
extern int* g_1686a18;   // vector begin
extern int* g_1686a1c;   // vector end
extern int* g_1686a20;   // vector capacity
extern "C" void* FUN_011e0744(void* dst, const void* src, unsigned n);  // 0x011e0744 memmove
extern int g_1686a24;                                                  // vector allocator
struct SPVector_00b96600 { void FUN_00b96600(void* pos, const void* key); };  // 0x00B96600
static inline void* g_vt(void* p) { return *(void**)p; }
static inline void* g_vfn(void* p, int off) { return *(void**)((char*)g_vt(p) + off); }
struct EastlIntVector
{
    int* mpBegin;      // +0x00
    int* mpEnd;        // +0x04
    int* mpCapacity;   // +0x08

    EastlIntVector(int count, void* allocator);   // 0x00b93c60
    void resize(int size);                        // 0x00b98ea0
    void swap(EastlIntVector* other);             // 0x00ebf480
};
struct EastlBlockHeader { int mOwner; };
static inline int eastl_block_owner(void* p)
{
    return ((EastlBlockHeader*)p)[-1].mOwner;
}
// ---- items of slice s00b5b540 end

// @ 0x00b500e0
void __thiscall Obj500E0::F(const void* a, HkObj* b)
{
    float s = *(float*)((char*)this + 0x50) + *(float*)((char*)this + 0x4c);
    if (s != *(float*)((char*)this + 0x30)) {
        *(float*)((char*)this + 0x20) = s;
        *(float*)((char*)this + 0x24) = s;
        *(float*)((char*)this + 0x28) = s;
        *(float*)((char*)this + 0x2c) = 0.0f;
        float n = s * -1.0f;
        *(float*)((char*)this + 0x10) = n;
        *(float*)((char*)this + 0x14) = n;
        *(float*)((char*)this + 0x18) = n;
        *(float*)((char*)this + 0x1c) = 0.0f;
        *(float*)((char*)this + 0x30) = s;
    }
    HkObj* va = (HkObj*)a;
    va->setTransformedPos(a, (HkVec*)((char*)this + 0x10));
    b->setTransformedPos(a, (HkVec*)((char*)this + 0x20));
}

// @ 0x00b50170
void __thiscall Obj50170::F(unsigned a, unsigned b, unsigned c)
{
    Variant8 t;
    t.flag = 0;
    t.v = 0.0f;
    ((IVarInvoke*)this)->Invoke(a, b, t, c);
}

// @ 0x00b501a0
S24& __thiscall Obj501A0::operator=(const S24& src)
{
    a = src.a;
    b = src.b;
    c = src.c;
    d = src.d;
    e = src.e;
    f = src.f;
    return *(S24*)this;
}

// @ 0x00b501d0
void __thiscall Obj501D0::F(const Vec4* seg, unsigned id, char checkHeight, float margin, RayHitSink* sink)
{
    Vec3 a;
    a.x = seg[0].x;
    a.y = seg[0].y;
    a.z = seg[0].z;
    Vec3 b;
    b.x = seg[1].x;
    b.y = seg[1].y;
    b.z = seg[1].z;
    Vec3 delta;
    delta.x = b.x - a.x;
    delta.y = b.y - a.y;
    delta.z = b.z - a.z;

    FaceUV uv;
    DirToCubeInto(uv, a);
    float terrainA = (float)((double)mMap->GetFloat(&uv) * (double)mScale + (double)mBase);
    DirToCubeInto(uv, b);
    mMap->GetFloat(&uv);

    Vec3 hit;
    hit = kZeroVec;
    float lenA = sqrtf(a.z * a.z + (a.y * a.y + a.x * a.x));
    float t;
    if (checkHeight != 0 && terrainA > lenA) {
        if (lenA - margin < sqrtf(b.y * b.y + (b.z * b.z + b.x * b.x))) return;
        t = 0.0f;
        hit = a;
    } else {
        float lenD = sqrtf(delta.y * delta.y + (delta.z * delta.z + delta.x * delta.x));
        float dist;
        if (lenD <= kMilli) {
            hit = b;
            dist = sqrtf(delta.z * delta.z + delta.y * delta.y + delta.x * delta.x);
        } else {
            float inv = kOne / lenD;
            delta.x *= inv;
            delta.y *= inv;
            delta.z *= inv;
            Vec3* r;
            if (*(char*)((char*)mPlanet + 0xf0) == 0)
                r = mPlanet->FUN_00b82060(&b, &a, &delta);
            else
                r = mPlanet->FUN_00b82110(&uv, &a, &delta);
            hit = *r;
            if (hit.x == kZeroVec.x && hit.y == kZeroVec.y && hit.z == kZeroVec.z) return;
            float hx = hit.x - a.x;
            float hy = hit.y - a.y;
            float hz = hit.z - a.z;
            dist = sqrtf(hz * hz + hy * hy + hx * hx);
        }
        if (lenD < dist) return;
        t = dist / lenD;
        if (t == kFloatMax) return;
        if ((*(const unsigned*)&t & 0x7fffffffu) > 0x7f800000u) return;  // NaN: original's jbe takes
    }
    if (t < sink->mMaxT) {
        Vec3 normal;
        mPlanet->GetNormalAt(&normal, &hit);
        Vec4 n;
        n.x = normal.x;
        n.y = normal.y;
        n.z = normal.z;
        n.w = 0.0f;
        sink->Hit(id, &n);
    }
}

// @ 0x00b50780
void __thiscall Obj50780::F(unsigned param2, SVec* src)
{
    (void)param2;
    if (mDist > src->f) {
        float nf = src->f;
        SVec* dst = mDst;
        mDist = nf;
        dst->a = src->a;
        dst->b = src->b;
        dst->c = src->c;
        dst->d = src->d;
        dst->e = src->e;
        dst->f = src->f;
        mFlag = 1;
    }
}

// @ 0x00b507d0
void __thiscall Obj507D0::F(unsigned param2, unsigned param3, uchar* out)
{
    (void)param2;
    struct Tmp { void* vt; uchar flag; float v; };
    Tmp t;
    t.vt = &g_vtblFB0;
    t.flag = 0;
    t.v = *(float*)((char*)this + 0x14);
    ((IVarInvoke*)this)->Invoke(param3, 0, *(Variant8*)((char*)&t + 4), 0);
    *out = t.flag;
}

// @ 0x00b50820
void __thiscall Obj50820::F(const SweptSphere* in, unsigned id, unsigned extra)
{
    SweptSphereOut out;
    out.mExtra0 = in->mExtra0;
    out.mExtra1 = in->mExtra1;
    float lenA = sqrtf(in->mStart.z * in->mStart.z + in->mStart.y * in->mStart.y
                     + in->mStart.x * in->mStart.x);
    float invA = kOne / lenA;
    float scaleA = lenA - in->mRadius;
    float lenB = sqrtf(in->mEnd.y * in->mEnd.y + in->mEnd.z * in->mEnd.z
                     + in->mEnd.x * in->mEnd.x);
    float invB = kOne / lenB;
    float scaleB = lenB - in->mRadius;

    out.mStart.x = (in->mStart.x * invA) * scaleA;
    out.mStart.y = (in->mStart.y * invA) * scaleA;
    out.mStart.z = (in->mStart.z * invA) * scaleA;
    out.mStart.w = (in->mStart.w * invA) * scaleA;
    out.mEnd.x = (in->mEnd.x * invB) * scaleB;
    out.mEnd.y = (in->mEnd.y * invB) * scaleB;
    out.mEnd.z = (in->mEnd.z * invB) * scaleB;
    out.mEnd.w = (in->mEnd.w * invB) * scaleB;

    ((IHitInvoke*)this)->Invoke(&out, id, 1, in->mParam, extra);
}

// @ 0x00b509b0
void TerrainSampler::ProjectPlanes(PlaneList* in, Plane* out)
{
    int count = in->count;   // read once (the original counts down a copy)
    for (int i = 0; i < count; ++i) {
        float maxd = in->maxDist;
        Plane* p = &in->data[i];
        float px = p->x, py = p->y, pz = p->z;
        float inv = 1.0f / sqrtf(px * px + (py * py + pz * pz) + 1e-08f);
        float uy = py * inv;
        float ux = inv * px;
        float uz = pz * inv;
        float ax = fabsf(px), ay = fabsf(py), az = fabsf(pz);
        UV uv;
        if (az < ax || az < ay) {
            if (ay < ax) {
                uv.u = (py / px + 1.0f) * 0.5f;
                uv.v = (pz / ax + 1.0f) * 0.5f;
                uv.face = 2;
                if (px < 0.0f) uv.face = 3;
            } else {
                uv.u = (pz / py + 1.0f) * 0.5f;
                uv.v = (px / ay + 1.0f) * 0.5f;
                if (py < 0.0f) uv.face = 5; else uv.face = 4;
            }
        } else {
            uv.u = (px / pz + 1.0f) * 0.5f;
            uv.v = (py / az + 1.0f) * 0.5f;
            if (pz < 0.0f) uv.face = 1; else uv.face = 0;
        }
        float h = heights->GetFloat(&uv) * scale + bias;
        float h2 = h;
        if (planet->hasWater) {
            float wh = planet->GetWaterHeight();
            const float* pf = &h;
            if (wh > h) pf = &wh;    // unordered keeps h, as the original's ja
            h2 = *pf;
        }
        Vec3 n;
        if (!planet->hasWater || !(planet->GetWaterHeight() > h2)) {   // unordered -> normal path (jbe)
            Vec4 v;
            normals->GetVector4(&v, &uv);
            float nx = v.x * 2.0f - g_normalBias.x;
            float ny = v.y * 2.0f - g_normalBias.y;
            float nz = v.z * 2.0f - g_normalBias.z;
            float ninv = 1.0f / sqrtf((nx * nx + nz * nz) + ny * ny + 1e-08f);
            n.x = ninv * nx;
            n.y = ny * ninv;
            n.z = nz * ninv;
        } else {
            n.x = ux; n.y = uy; n.z = uz;
        }
        float d = ((n.y * py + n.z * pz) + n.x * px) + -((n.x * (ux * h2) + n.z * (uz * h2)) + n.y * (uy * h2)) - p->w;
        if (d < maxd) {      // NaN d takes the FLT_MAX path, as in the original (comiss maxd,d; jbe)
            out[i].x = n.x; out[i].y = n.y; out[i].z = n.z;
        } else {
            d = 3.40282e+38f;
        }
        out[i].w = d;
    }
}

// @ 0x00b50de0
HkOwner::HkOwner()
{ a.p = 0; b.p = 0; }

// @ 0x00b50e80
int __stdcall GetResourceTypes(u32* out, u32 n)
{
    if (out && n >= 1)
        *out = 0x448ae7e2;
    return 1;
}

// @ 0x00b50ea0
bool __stdcall IsResourceType(u32 a, u32 b)
{
    if (a == 0x448ae7e2 && b == 0x448ae7e2)
        return true;
    return false;
}

// @ 0x00b50ef0
cHavokResource::~cHavokResource()
{
    if (p14) delete p14;
    if (arr && arr[-1] != 0)
        ::operator delete(arr);
}

// @ 0x00b50ff0
void RegisterHavokResourceFactory()
{
    cHavokResourceFactory* f = new ("Simulator/cHavokResourceFactory", 0, 0, 0, 0) cHavokResourceFactory();
    GetResMan()->AddFactory(1, f, 0);
}

// @ 0x00b51040
void* __cdecl FindNear(Cursor* c, float x)
{
    NodeA* n = c->cur;
    if (n != c->end) {
        do {
            if (fabs((double)n->f - (double)x) <= 1.5258789e-05f)
                return &n->value;
            n = c->cur->next;
            c->cur = n;
            while (!n) {
                c->bucket += 1;
                n = *c->bucket;
                c->cur = n;
            }
            n = c->cur;
        } while (n != c->end);
    }
    return 0;
}

// @ 0x00b510b0
bool __cdecl LoadHavokShape(u32 key, ShapeHolder* holder)
{
    RefObj* res = 0;
    ResMan* mgr = GetResMan();
    {
        RefObj* old = res;
        if (old) {
            res = 0;
            old->Release();
        }
    }
    if (mgr->Get(key, &res, 0, 0, 0, 0) && res) {
        HkResData* hr = (HkResData*)((ResObj*)res)->Query(0x532dc8b);
        if (hr) {
            hr->AddRef();
            hkMemoryStreamReader* rd = new hkMemoryStreamReader(hr->begin, (int)(hr->end - hr->begin), 2);
            hkBinaryPackfileReader* pk = new hkBinaryPackfileReader();
            pk->loadEntireFile(rd);
            hkReferencedObject_s00b5_09b0* contents = pk->getContents();
            if (contents->memSize)
                ++contents->refCount;
            hkShape_s00b5_09b0* shape = GetShapeFromPackfile(pk);
            delete pk;
            if (rd)
                delete rd;
            hr->Release();
            if (shape) {
                ShapeInit s;
                s.a = 0; s.b = 0;
                s.z70 = 0;
                s.one = 1.0f;
                s.contents = contents;
                s.out = 0;
                s.shape = shape;
                s.kind = 2;
                s.f20 = 0.0f; s.f24 = 0.0f;
                s.f3c = 0.0f; s.f38 = 0.0f; s.f34 = 0.0f; s.f30 = 0.0f;
                s.f40 = 0.0f; s.f44 = 0.0f; s.f48 = 0.0f; s.f4c = 0.0f; s.f50 = 0.0f; s.f54 = 0.0f;
                s.f58 = 0.0f; s.f5c = 0.0f; s.f60 = 0.0f; s.f64 = 0.0f; s.f68 = 0.0f; s.f6c = 0.0f;
                holder->Prepare(&s);
                BuildShapeBody(shape, 1.0f, holder->dst);
                if (s.out)
                    s.out->Release();
                return true;
            }
        }
    }
    if (res)
        res->Release();
    return false;
}

// @ 0x00b512f0
void CreatePlanetBody()
{
    if (g_hkWorld && !g_planetBody && GetPlanetModel()) {
        hkRigidBodyCinfo info;
        hkShape2* shape = new hkShape2(GetPlanetModel());
        info.v[1] = 1.0f;
        info.v[0] = 1.0f;
        info.v[2] = 1.0f;
        info.v[3] = 0.0f;
        info.shape = shape;
        info.motion = 7;
        info.filter = 1;
        info.f = g_bodyF;
        hkRigidBody_s00b5_09b0* body = CreateRigidBody(&info);
        info.shape->removeReference();
        g_planetBody = body;
        hkVector4 zero;
        zero.x = 0.0f; zero.y = 0.0f; zero.z = 0.0f; zero.w = 0.0f;
        body->setPosition(zero);
        g_planetBody->addProperty(0, 1);
        g_planetBody->addProperty(1, (u32)GetPlanetModel());
        g_hkWorld->addEntity(body, 1);
        g_hkWorld->updateCollisionFilterOnWorld(0, 1);
    }
}

// @ 0x00b51460
void __cdecl LoadPlanetTuning(PropSet* p)
{
    g_b0 = GetPropBool(p, 0xdaeb0c3, g_b0);
    g_t0 = GetPropFloat(p, 0x48ae581d, g_t0);
    g_t1 = GetPropFloat(p, 0x35a44d51, g_t1);
    g_t2 = GetPropFloat(p, 0x45d6c96b, g_t2);
    g_t3 = GetPropFloat(p, 0x68e23f96, g_t3);
    g_b1 = GetPropBool(p, 0x99d89285, g_b1);
    g_t4 = GetPropFloat(p, 0x85f3d491, g_t4);
    g_t5 = GetPropFloat(p, 0x7161041a, g_t5);
    g_t6 = GetPropFloat(p, 0xd339bde9, g_t6);
    g_t7 = GetPropFloat(p, 0x9a1e6eb8, g_t7);
    g_t8 = GetPropFloat(p, 0xd55b5929, g_t8);
    g_t9 = GetPropFloat(p, 0x14750a09, g_t9);
    g_b2 = GetPropBool(p, 0x3ac2d33a, g_b2);
}

// @ 0x00b515e0
void PlanetWatcher::Update()
{
    if (g_hkWorld) {
        if (g_planetBody) {
            PlanetBodyData* d = *(PlanetBodyData**)((char*)g_planetBody + 0x1c);
            bool diff = d->planet != GetPlanetModel();
            if (!diff) {
                PlanetModelC* pm = (PlanetModelC*)GetPlanetModel();
                PlanetMapOwner* ow = pm->owner;
                MapObj* m = (MapObj*)ow->GetMap();
                diff = d->mapOwner != m->ptr;
            }
            if (diff)
                RebuildPlanetBody();
            if (g_planetBody)
                return;
        }
        CreatePlanetBody();
        created = 1;
    }
}

// @ 0x00b51640
IterS* TblS::erase(IterS* out, NodeS* node, NodeS** bucket)
{
    NodeS* nx = node->next;
    out->bucket = bucket;
    out->node = nx;
    while (!nx) {
        out->bucket += 1;
        nx = *out->bucket;
        out->node = nx;
    }
    NodeS* cur = *bucket;
    if (cur == node) {
        *bucket = cur->next;
    } else {
        NodeS* prev = cur;
        cur = cur->next;
        while (cur != node) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = cur->next;
    }
    if (node != inlineNode) {
        if (node >= poolBegin && node < poolEnd) {
            *(NodeS**)node = freeList;
            freeList = node;
            --count;
            return out;
        }
        ::operator delete(node);
    }
    --count;
    return out;
}

// @ 0x00b51780
RangeOut* TblA::equal_range(RangeOut* out, const u32* key)
{
    u32 c3 = key[2];
    u32 code = key[0] ^ c3;
    u32 idx = code % bucketCount;
    NodeA** b = &buckets[idx];
    NodeA* n = DoFindNode(buckets[idx], key, code);
    if (n) {
        NodeA* e = n->next;
        while (e && key[0] == e->key[0] && key[1] == e->key[1] && c3 == e->key[2])
            e = e->next;
        NodeA** pb = b;
        if (!e) {
            pb = b + 1;
            if (!*pb) {
                do { ++pb; } while (!*pb);
            }
            e = *pb;
        }
        out->first = n;
        out->firstBucket = b;
        out->last = e;
        out->lastBucket = pb;
        return out;
    }
    NodeA* endn = buckets[bucketCount];
    NodeA** endb = &buckets[bucketCount];
    out->first = endn;
    out->firstBucket = endb;
    out->last = endn;
    out->lastBucket = endb;
    return out;
}

// @ 0x00b51840
void* TblA::DoInsertValue(void* outp, const void* vp, int tag)
{
    IterA* out = (IterA*)outp;
    const u32* v = (const u32*)vp;
    RehashResult rr;
    policy.GetRehashRequired(&rr, bucketCount, count, 1);
    if (rr.need)
        DoRehash(rr.newCount);
    u32 code = v[2] ^ v[0];
    u32 idx = code % bucketCount;
    NodeA* nn = (NodeA*)operator_new_a(0xa0, 0x10, 0, "Simulator", 0, 0, g_ehFile, 0xe5);
    if (nn)
        new (nn) NodeA(vp);
    nn->next = 0;
    NodeA* head = buckets[idx];
    NodeA* found = DoFindNode(head, vp, code);
    if (!found) {
        nn->next = head;
        buckets[idx] = nn;
    } else {
        nn->next = found->next;
        found->next = nn;
    }
    ++count;
    out->node = nn;
    out->bucket = buckets + idx;
    return out;
}

// @ 0x00b51930
InsertOut* TblB::DoInsertKey(InsertOut* out, const u32* key, int tag)
{
    u32 code = key[0] ^ key[2];
    u32 idx = code % bucketCount;
    NodeB** b = &buckets[idx];
    NodeB* p = *b;
    for (; p; p = p->next) {
        if (key[0] == p->key[0] && key[1] == p->key[1] && key[2] == p->key[2])
            break;
    }
    if (!p) {
        RehashResult rr;
        policy.GetRehashRequired(&rr, bucketCount, count, 1);
        NodeB* nn = (NodeB*)operator_new_b(0x14, "Simulator", 0, 0, g_ehFile, 0xd1);
        if (nn) {
            nn->key[0] = key[0];
            nn->key[1] = key[1];
            nn->key[2] = key[2];
            nn->key[3] = key[3];
        }
        nn->next = 0;
        if (rr.need) {
            idx = code % rr.newCount;
            DoRehash(rr.newCount);
        }
        nn->next = buckets[idx];
        buckets[idx] = nn;
        ++count;
        out->node = nn;
        out->inserted = 1;
        out->bucket = &buckets[idx];
        return out;
    }
    out->node = p;
    out->inserted = 0;
    out->bucket = b;
    return out;
}

// @ 0x00b51b00
int Big::M_b51b00(unsigned a0, int a1, int a2, int a3, int a4, int a5, int* a6)
{
    char* self = (char*)this;
    unsigned n = (unsigned)a6[0];

    *(int*)(self + 8) = 0;
    *(int*)(self + 0xc) = 0;
    *(float*)(self + 0x10) = 1.0f;
    *(float*)(self + 0x14) = *(float*)0x1470f1c;
    *(int*)(self + 0x18) = 0;

    *(int*)(self + 0x1c) = 0;
    ((Ext*)(self + 0x1c))->FUN_00921260(n, 0x80, 0x10, 4, 0);
    *(unsigned*)(self + 0x24) = n;
    *(unsigned*)(self + 0x28) = n + 0x80;
    *(int*)(self + 0x2c) = 0x10;
    *(int*)(self + 0x30) = a6[5];

    if (a0 < 2) {
        *(int*)(self + 0xc) = 0;
        *(int*)(self + 0x18) = 0;
        *(int*)(self + 8) = 1;
        *(unsigned*)(self + 4) = 0x154df28u;
        return (int)(size_t)this;
    }

    unsigned u = ((Ext*)(self + 0x10))->FUN_00921360(a0);
    *(unsigned*)(self + 8) = u;
    u = FUN_00c763d0(u);
    *(unsigned*)(self + 4) = u;
    return (int)(size_t)this;
}

// @ 0x00b51bb0
void** Big::M_b51bb0(void** out, int* key)
{
    char* self = (char*)this;
    int** buckets = *(int***)(self + 4);
    unsigned nBucket = *(unsigned*)(self + 8);

    unsigned idx = (unsigned)(key[0] + key[1]) % nBucket;
    int** slot = &buckets[idx];
    int* node = *slot;
    for (; node != 0; node = *(int**)((char*)node + 0xc)) {
        if (key[0] == node[0] && key[1] == node[1])
            break;
    }
    if (node == 0) {
        slot = &buckets[nBucket];
        node = *slot;
    }
    out[0] = node;
    out[1] = slot;
    return out;
}

// @ 0x00b51c20
int Big::M_b51c20(int* key)
{
    char* self = (char*)this;
    int** buckets = *(int***)(self + 4);
    unsigned nBucket = *(unsigned*)(self + 8);
    int cnt0 = *(int*)(self + 0xc);
    int* sentinel = *(int**)(self + 0x30);

    unsigned idx = (unsigned)(key[0] + key[1]) % nBucket;
    int** slot = &buckets[idx];

    if (*slot != 0) {
        int* node = *slot;
        while (node != 0 && !(key[0] == node[0] && key[1] == node[1])) {
            slot = (int**)((char*)node + 0xc);
            node = *slot;
        }
        while (*slot != 0) {
            node = *slot;
            if (key[0] != node[0] || key[1] != node[1])
                break;
            *slot = *(int**)((char*)node + 0xc);
            if (node != sentinel) {
                if (node < *(int**)(self + 0x24) || node >= *(int**)(self + 0x28)) {
                    FUN_00f47380(node);
                } else {
                    node[0] = *(int*)(self + 0x1c);
                    *(int**)(self + 0x1c) = node;
                }
            }
            (*(int*)(self + 0xc))--;
        }
    }
    return cnt0 - *(int*)(self + 0xc);
}

// @ 0x00b51cc0
int** Big::M_b51cc0(int** out, int* node, int** slot)
{
    char* self = (char*)this;
    int* sentinel = *(int**)(self + 0x30);

    int* nxt = *(int**)((char*)node + 0xc);
    out[1] = (int*)slot;
    out[0] = nxt;
    while (nxt == 0) {
        slot++;
        nxt = *slot;
        out[0] = nxt;
    }

    if (*slot == node) {
        *slot = *(int**)((char*)node + 0xc);
    } else {
        int* prev = *slot;
        int* cur = *(int**)((char*)prev + 0xc);
        while (cur != node) {
            prev = cur;
            cur = *(int**)((char*)cur + 0xc);
        }
        *(int**)((char*)prev + 0xc) = *(int**)((char*)cur + 0xc);
    }

    if (node != sentinel) {
        if (node < *(int**)(self + 0x24) || node >= *(int**)(self + 0x28)) {
            FUN_00f47380(node);
        } else {
            node[0] = *(int*)(self + 0x1c);
            *(int**)(self + 0x1c) = node;
        }
    }
    (*(int*)(self + 0xc))--;
    return out;
}

// @ 0x00b51d50
void Big::M_b51d50(float dt)
{
    char* self = (char*)this;
    Big* t = (Big*)(self + 0x1858);

    int** buckets = *(int***)(self + 0x185c);
    unsigned nBucket = *(unsigned*)(self + 0x1860);

    int** pi = buckets;
    int* node = *pi;
    if (node == 0) {
        do {
            pi++;
            node = *pi;
        } while (node == 0);
    }
    int* end = *(int**)((char*)buckets + nBucket * 4);

    while (node != end) {
        float v = *(float*)((char*)node + 8) - dt;
        *(float*)((char*)node + 8) = v;
        if (0.0f < v) {
            node = *(int**)((char*)node + 0xc);
            while (node == 0) {
                pi++;
                node = *pi;
            }
        } else {
            int* r[2];
            t->M_b51cc0((int**)r, node, pi);
            node = r[0];
            pi = (int**)r[1];
        }
    }
}

// @ 0x00b51df0
void Big::M_b51df0(unsigned a, unsigned b)
{
    char* self = (char*)this;
    Big* t = (Big*)(self + 0x1858);

    unsigned lo = a, hi = b;
    if (b < a) {
        lo = b;
        hi = a;
    }
    int pair[2];
    pair[0] = (int)lo;
    pair[1] = (int)hi;
    t->M_b51c20(pair);
}

// @ 0x00b51e30
int* __cdecl FUN_00b51e30(int* out, unsigned a)
{
    int local[4];
    int* p = ((Ext*)0x1569c98)->FUN_00b51780(local, a);
    out[0] = p[0];
    out[1] = p[1];
    out[2] = p[2];
    out[3] = p[3];
    out[4] = 0;
    out[5] = 0;
    out[4] = out[0];
    out[5] = out[1];
    return out;
}

// @ 0x00b51e80
void __cdecl FUN_00b51e80(unsigned a1, float a2)
{
    int local[4];
    int* p = ((Ext*)0x1569c98)->FUN_00b51780(local, a1);
    int s[6];
    s[0] = p[0];
    s[1] = p[1];
    s[2] = p[2];
    s[3] = p[3];
    s[4] = s[0];
    s[5] = s[1];
    FUN_00b51040(s, a2);
}

// @ 0x00b51ee0
void Big::M_b51ee0()
{
    char* self = (char*)this;
    int* p18 = *(int**)(self + 0x18);
    int* ref;
    short s;

    if (p18 != 0) {
        ref = p18;
        s = *(short*)((char*)p18 + 6);
    } else {
        ref = *(int**)(self + 0xc);
        s = (ref == 0) ? 0 : *(short*)((char*)ref + 6);
    }
    bool last = (s == 1);

    if (p18 != 0) {
        if (*(short*)((char*)p18 + 4) != 0) {
            (*(short*)((char*)p18 + 6))--;
            if (*(short*)((char*)p18 + 6) == 0) {
                void** vt = *(void***)p18;
                ((void(__thiscall*)(int*, int))vt[0])(p18, 1);
            }
        }
        if (last) {
            *(int**)(self + 0x18) = 0;
            *(int**)(self + 0xc) = 0;
        }
    } else {
        int* p0c = *(int**)(self + 0xc);
        if (*(short*)((char*)p0c + 4) != 0) {
            (*(short*)((char*)p0c + 6))--;
            if (*(short*)((char*)p0c + 6) == 0) {
                void** vt = *(void***)p0c;
                ((void(__thiscall*)(int*, int))vt[0])(p0c, 1);
            }
        }
        if (last)
            *(int**)(self + 0xc) = 0;
    }

    int* p70 = *(int**)(self + 0x70);
    if (p70 != 0) {
        int* r18 = *(int**)((char*)p70 + 0x18);
        short s2;
        if (r18 != 0) {
            s2 = *(short*)((char*)r18 + 6);
        } else {
            int* r0c = *(int**)((char*)p70 + 0xc);
            s2 = (r0c == 0) ? 0 : *(short*)((char*)r0c + 6);
        }
        ((Big*)p70)->M_b51ee0();
        if (s2 == 1)
            *(int**)(self + 0x70) = 0;
    }

    if (last) {
        int it[6];
        FUN_00b51e30(it, (unsigned)(size_t)this);
        int* node = (int*)it[4];
        int* end = (int*)it[2];
        int* slot = (int*)it[3];
        while (*(float*)((char*)node + 0x20) != *(float*)(self + 0x10)) {
            node = *(int**)((char*)node + 0x90);
            while (node == 0) {
                slot++;
                node = (int*)*slot;
            }
            if (node == end)
                return;
        }
        if (node != end && *(float*)((char*)node + 0x20) == *(float*)(self + 0x10))
            ((Ext*)0x1569c98)->FUN_00b4f8a0(it, node, slot);
    }
}

// @ 0x00b52020
void Big::M_b52020(int* p)
{
    int it[2];
    int key[2];
    key[0] = p[0];
    key[1] = 0;

    ((Ext*)0x1569cb8)->FUN_00833840(it, key);

    int base = *(int*)0x1569cbc;
    int count = *(int*)0x1569cc0;
    if (it[0] != *(int*)(base + count * 4)) {
        ((Big*)(*(int**)(it[0] + 0xc)))->M_b51ee0();
        ((Ext*)0x1569cb8)->FUN_00b4f930(it, (void*)it[0], (void*)it[1]);
    }
}

// @ 0x00b520a0
void __cdecl FUN_00b520a0()
{
    int** tbl = *(int***)0x1569cbc;
    int count = *(int*)0x1569cc0;

    int** pi = &tbl[0];
    int* node = *pi;
    if (node == 0) {
        pi = &tbl[1];
        node = *pi;
        while (node == 0) {
            pi++;
            node = *pi;
        }
    }
    int* end = tbl[count];

    while (node != end) {
        ((Big*)(*(int**)((char*)node + 0xc)))->M_b51ee0();
        node = *(int**)((char*)node + 0x10);
        while (node == 0) {
            pi++;
            node = *pi;
        }
    }
    ((Ext*)0x1569cb8)->FUN_007611f0(tbl, (u32_s00b5_1b00)count);
    *(int*)0x1569cc4 = 0;
}

// @ 0x00b52120
int** Big::M_b52120(int** out, int* key, int* extra)
{
    (void)extra;
    char* self = (char*)this;
    unsigned key0 = (unsigned)key[0];
    unsigned key1 = (unsigned)key[1];
    unsigned sum = key0 + key1;

    int** buckets = *(int***)(self + 4);
    unsigned nBucket = *(unsigned*)(self + 8);
    unsigned idx = sum % nBucket;
    int** slot = &buckets[idx];

    int* node = *slot;
    while (node != 0) {
        if (key0 == (unsigned)node[0] && key1 == (unsigned)node[1]) {
            out[0] = node;
            *((char*)out + 8) = 0;
            out[1] = (int*)slot;
            return out;
        }
        node = *(int**)((char*)node + 0xc);
    }

    int rb[2];
    ((Ext*)(self + 0x10))->FUN_00921440(rb, nBucket, (u32_s00b5_1b00)*(int*)(self + 0xc), 1);
    int* nn = (int*)(size_t)((Ext*)self)->FUN_00b576d0(key);
    if (*(char*)&rb[0] != 0) {
        unsigned nb = (unsigned)rb[1];
        idx = sum % nb;
        ((Ext*)self)->FUN_00b4fbd0(nb);
    }

    *(int**)((char*)nn + 0xc) = buckets[idx];
    buckets[idx] = nn;
    (*(int*)(self + 0xc))++;
    out[0] = nn;
    out[1] = (int*)&buckets[idx];
    *((char*)out + 8) = 1;
    return out;
}

// @ 0x00b521f0
int __cdecl FUN_00b521f0(void* a)
{
    int it[2];
    void* key = a;
    ((Ext*)0x16852e8)->FUN_00645ed0(it, &key);
    int base = *(int*)0x16852ec;
    int count = *(int*)0x16852f0;
    if (it[0] != *(int*)(base + count * 4))
        return *(int*)(it[0] + 4);
    return 0;
}

// @ 0x00b52230
unsigned __cdecl FUN_00b52230(void* a1, void* a2)
{
    int* esi = (int*)a1;
    int* edi = (int*)a2;

    if (edi == 0) {
        int it[2];
        void* key = a1;
        ((Ext*)0x16801a8)->FUN_00645ed0(it, &key);
        int base = *(int*)0x16801ac;
        int count = *(int*)0x16801b0;
        if (it[0] == *(int*)(base + count * 4))
            return 0;
        edi = *(int**)(it[0] + 4);
        if (edi == 0)
            return 0;
    }

    if (esi != 0) {
        int ebx = ((VB8*)esi)->fB8(0x116dd1b);
        if (ebx != 0 && *(char*)((char*)edi + 0x9a) == 0) {
            int p58 = *(int*)((char*)edi + 0x58);
            float v[3];
            v[0] = *(float*)(p58 + 0xd0);
            v[1] = *(float*)(p58 + 0xd4);
            v[2] = *(float*)(p58 + 0xd8);
            void* src = FUN_0059ab70(v) ? (void*)v : (void*)0x167ecf4;
            ((Ext*)(size_t)ebx)->FUN_00c41d60(src);
        }
    }

    float q[4];
    {
        int p58 = *(int*)((char*)edi + 0x58);
        q[0] = *(float*)(p58 + 0x80);
        q[1] = *(float*)(p58 + 0x84);
        q[2] = *(float*)(p58 + 0x88);
        q[3] = *(float*)(p58 + 0x8c);
    }
    float* s = ((V30*)esi)->f30();
    if (!(q[0] == s[0] && q[1] == s[1] && q[2] == s[2] && q[3] == s[3]))
        ((V3C*)esi)->f3c(q);

    float q3[3];
    FUN_00b4dfe0(esi, edi, q3);
    float* t = ((V10*)esi)->f2c();
    if (!(t[0] == q3[0] && t[1] == q3[1] && t[2] == q3[2]))
        ((V38*)esi)->f38(q3);

    return *(u8_s00b5_1b00*)((char*)esi + 0x74);
}

// @ 0x00b523e0
void __cdecl FUN_00b523e0(void* a1, void* a2)
{
    int* ebx = (int*)a1;
    int* esi = (int*)a2;

    if (esi == 0) {
        int it[2];
        void* key = a1;
        ((Ext*)0x16801a8)->FUN_00645ed0(it, &key);
        int base = *(int*)0x16801ac;
        int count = *(int*)0x16801b0;
        if (it[0] == *(int*)(base + count * 4))
            return;
        esi = *(int**)(it[0] + 4);
        if (esi == 0)
            return;
    }

    char flag = 0;
    float v[4];
    FUN_00b4e0c0(ebx, esi, v);
    int p58 = *(int*)((char*)esi + 0x58);
    float dx = fabsf(v[0] - *(float*)(p58 + 0x40));
    float dy = fabsf(v[1] - *(float*)(p58 + 0x44));
    float dz = fabsf(v[2] - *(float*)(p58 + 0x48));
    if (dx > 0.001f || dy > 0.001f || dz > 0.001f) {
        ((Body*)esi)->FUN_01087820(v);
        flag = 1;
    }

    float q[4];
    float* r = ((V30*)ebx)->f30();
    q[0] = r[0];
    q[1] = r[1];
    q[2] = r[2];
    q[3] = r[3];
    int p58b = *(int*)((char*)esi + 0x58);
    float ax = fabsf(q[0] - *(float*)(p58b + 0x80));
    float ay = fabsf(q[1] - *(float*)(p58b + 0x84));
    float az = fabsf(q[2] - *(float*)(p58b + 0x88));
    char c = flag;
    if (ax > 0.001f || ay > 0.001f || az > 0.001f) {
        ((Body*)esi)->FUN_01087840(q);
        c = 1;
    }

    if (*(char*)0x1569ab8 != 0 && c != 0 &&
        (*(int*)((char*)ebx + 0x50) & 0x2000) != 0) {
        int iv = FUN_00b521f0(ebx);
        if (iv != 0) {
            int obj = *(int*)((char*)esi + 0x1c);
            float ftmp = *(float*)0x1569ab4;
            ((VOB*)obj)->f0c((void*)(*(int*)((char*)esi + 0x58) + 0x10), ftmp, v);
            ((Body*)iv)->FUN_0108dde0(v);
            FUN_00b54000(ebx, (void*)iv);
        }
    }
}

// @ 0x00b53940
extern "C" int FUN_00b53940(void* p)
{
    if (p != 0 && ((CObj*)p)->m46(0x116dd1b) != 0) {
        EIt it = HT_167ed58.find((uint)p);
        if (it.node != HT_167ed58.buckets[HT_167ed58.bucketCount]) {
            int v = *(int*)((char*)it.node + 4);
            if (v != 0)
                return ((CObj*)v)->d2e0();
        }
    } else {
        EIt it = HT_16801a8.find((uint)p);
        if (it.node != HT_16801a8.buckets[HT_16801a8.bucketCount])
            return *(int*)((char*)it.node + 4);
    }
    return 0;
}

// @ 0x00b539e0
extern "C" void FUN_00b539e0(void* p)
{
    uint k = (uint)p;
    EIt it = HT_1682a48.find(k);
    if (it.node != HT_1682a48.buckets[HT_1682a48.bucketCount])
        FUN_00b4e1d0(p, *(int*)((char*)it.node + 4));
    if (p == 0)
        { FUN_00b523e0(p, 0); return; }
    int e = ((CObj*)p)->m46(0x116dd1b);
    if (e == 0)
        { FUN_00b523e0(p, 0); return; }
    EIt it2 = HT_167ed58.find(k);
    if (it2.node == HT_167ed58.buckets[HT_167ed58.bucketCount])
        return;
    if (*(int*)((char*)it2.node + 4) == 0)
        return;
    FUN_00b537f0((CObj*)e, *(int*)((char*)it2.node + 4), 1, 1);
}

// @ 0x00b53aa0
extern "C" void FUN_00b53aa0(int* p, void* out)
{
    char* s4;
    char* s3;
    int   ecx;
    int   id;
    switch (p[5]) {
    case 1:  s4 = (char*)0x01461318; break;   // "@center"
    case 2:  s4 = (char*)0x01461320; break;   // "  @base"
    default: s4 = (char*)0x01461328; break;   // "   @???"
    }
    ecx = p[6];
    if (ecx != 0)
        s3 = (char*)0x0146130c;               // " resource"
    else
        s3 = (p[0x1c] == 0) ? (char*)0x014612f4 /* "generated" */
                            : (char*)0x01461300 /* "   cloned" */;
    if (ecx != 0)
        id = (int)*(short*)((char*)ecx + 6);
    else {
        ecx = p[3];
        if (ecx != 0)
            id = (int)*(short*)((char*)ecx + 6);
        else
            id = 0;
    }
    eastl_sprintf(out, "[%3d](%08x!%08x, %6.3f, %s, %s) <%08x>",
                  id, p[2], p[0], (double)*(float*)&p[4], s3, s4, (int)p);
}

// @ 0x00b53b20
extern "C" void FUN_00b53b20(void)
{
    int* base = g_1569c9c;
    int* it = base;
    int v = *it;
    if (v == 0) {
        do { it++; } while (*it == 0);
        v = *it;
    }
    int end = base[g_1569ca0];
    while (v != end) {
        char* buf[3];
        buf[0] = (char*)&gEmptyString16;
        buf[1] = (char*)&gEmptyString16;
        buf[2] = (char*)0x01667bad;
        FUN_00b53aa0((int*)(v + 0x10), buf);
        if (1 < buf[2] - buf[0] && buf[0] != 0)
            operator_delete(buf[0]);
        v = *(int*)(v + 0x90);
        while (v == 0) { it++; v = *it; }
    }
}

// @ 0x00b53bc0
extern "C" char FUN_00b53bc0(CObj* p, float* a2, float* a3, float* a4, char a5)
{
    FUN_00b3d350();                                     // SP::PlanetModel()
    EditEntity* ent = (EditEntity*)FUN_00b53940(p);
    if (ent == 0)
        return 0;

    float dir[4];                                       // local_1f0..local_1e4
    dir[0] = a2[0]; dir[1] = a2[1]; dir[2] = a2[2]; dir[3] = 0.0f;
    float origin[3];                                    // local_200..local_1f8
    origin[0] = a3[0]; origin[1] = a3[1]; origin[2] = a3[2];

    void* shape;                                        // local_1e0 result
    if (DAT_01569aba != 0) {
        float* bb = (float*)p->m26();                   // body AABB
        float size[4];                                  // +0x60
        size[0] = bb[3] - bb[0];
        size[1] = bb[4] - bb[1];
        size[2] = bb[5] - bb[2];
        size[3] = 0.0f;

        void* boxMem = ((HkMemory*)HKMEM_S_INSTANCE)->alloc(0x20, 0x24);
        *(unsigned short*)((char*)boxMem + 4) = 0x20;
        void* box = FUN_010c05d0(size, DAT_015ba104);   // hkBoxShape

        float offset[4];                                // +0x20
        offset[0] = 0.0f; offset[1] = 0.0f; offset[2] = 0.0f; offset[3] = 0.0f;
        int fbuf[1];
        int* found = ent->Find(fbuf, 6);
        if (*found != 0) {
            float* bb2 = (float*)p->m26();
            offset[0] = (bb2[3] + bb2[0]) * DAT_01471064;
            offset[1] = (bb2[4] + bb2[1]) * DAT_01471064;
            offset[2] = (bb2[5] + bb2[2]) * DAT_01471064;
            offset[3] = 0.0f;
        }
        void* convMem = ((HkMemory*)HKMEM_S_INSTANCE)->alloc(0x30, 0x24);
        *(unsigned short*)((char*)convMem + 4) = 0x30;
        shape = FUN_010bfeb0(convMem, box, offset);     // hkConvexTranslateShape
        if (*(unsigned short*)((char*)box + 4) != 0 &&
            (*(unsigned short*)((char*)box + 6) -= 1) == 0)
            (**(void (***)(int))box)(1);
    } else {
        shape = ent->mShape;                            // +0x1c fallback
    }

    void* phMem = ((HkMemory*)HKMEM_S_INSTANCE)->alloc(0x130, 0x2e);
    *(unsigned short*)((char*)phMem + 4) = 0x130;
    void* phantom = FUN_0108c750(phMem, shape, (void*)((char*)ent->mBodyTransform + 0x10),
                                 a5 != 0 ? 7u : 4u);
    FUN_01083320(HKWORLD_S_INSTANCE, phantom);
    FUN_0109ae60(phantom);

    float sweep[4];                                     // hkVector4 at +0x70
    sweep[0] = origin[0]; sweep[1] = origin[1]; sweep[2] = origin[2]; sweep[3] = 0.0f;

    char collectorMem[0x2c];                            // hkAllCdPointCollector at +0x90
    HkPointCollector* coll = (HkPointCollector*)collectorMem;
    coll->mVtable = (void*)0x013ef55c;
    coll->mRadius = DAT_01461294;
    coll->mPoints = collectorMem + 0x24;                // local point array
    coll->mCount = 0;
    coll->mCapacity = 0x80000008;

    ((HkPhantomQuery*)phantom)->query(dir, sweep, 0);   // virtual slot 12

    char hit = 0;
    if (coll->mCount > 0) {
        int other = p != 0 ? p->m46(0x17f243b) : 0;
        FUN_010c2570(coll);                             // sortPoints
        for (int i = 0, off = 0; i < coll->mCount; ++i, off += 0x30) {
            if (hit != 0)
                break;
            HkCdPoint* pt = (HkCdPoint*)((char*)coll->mPoints + off);
            int id = *(int*)((char*)pt->mBody + 0x10);
            int rbuf[1];
            int* f = FUN_00496140(rbuf, 0);
            void* cand = (*f == 3) ? *(void**)((char*)pt->mBody + id + 0xc) : 0;
            if (cand != (void*)other && (cand == 0 || ((HkBodyKey*)cand)->match((void*)0xce9f6639) == 0)) {
                if (a4 != 0) {
                    a4[0] = pt->mPos[0];
                    a4[1] = pt->mPos[1];
                    a4[2] = pt->mPos[2];
                }
                hit = 1;
            }
        }
    }

    FUN_01083400(HKWORLD_S_INSTANCE, phantom);
    if (DAT_01569aba != 0 && *(unsigned short*)((char*)shape + 4) != 0 &&
        (*(unsigned short*)((char*)shape + 6) -= 1) == 0)
        (**(void (***)(int))shape)(1);

    ((HkPointCollector*)collectorMem)->mVtable = (void*)0x013ef55c;
    {
        uint cap = ((HkPointCollector*)collectorMem)->mCapacity;
        if ((int)cap >= 0) {
            TlsGetValue_fn(0);
            FUN_0107db10(collectorMem + 0x18, (cap & 0x3fffffff) * 0x30, 0x14);
        }
    }
    return hit;
}

// @ 0x00b54200
extern "C" char FUN_00b54200(void* p)
{
    char r = 0;
    CObj* o = (CObj*)FUN_00b53940(p);
    if (o != 0) {
        o->setMotionType(1, 1, 0);
        r = 1;
    }
    return r;
}

// @ 0x00b54300
extern "C" void FUN_00b54300(void* a, void* b)
{
    if (g_167ecdc == 0)
        return;
    int x = FUN_00b53940(a);
    int y = FUN_00b53940(b);
    if (x != 0 && y != 0)
        g_167ecdc->d1df0((void*)x, (void*)y);
}

// @ 0x00b54340
extern "C" void FUN_00b54340(void* p, float* v, char a3)
{
    if (p != 0 && *((char*)p + 0x71) == 0) {
        int e = FUN_00b53940(p);
        if (e != 0)
            ((CObj*)e)->setMotionType(1, 1, 0);
    }
    {
        uint k = (uint)p;
        EIt it = HT_167ed58.find(k);
        if (it.node != HT_167ed58.buckets[HT_167ed58.bucketCount] &&
            *(int*)((char*)it.node + 4) != 0) {
            int e = ((CObj*)*(int*)((char*)it.node + 4))->d2e0();
            if (e != 0) {
                Vec4_s00b5_37f0 vv;
                vv.x = v[0]; vv.y = v[1]; vv.z = v[2]; vv.w = 0.0f;
                if (a3 != 0) {
                    float m = ((CObj*)(*(int*)((char*)e + 0x58)))->getMass();
                    vv.x *= m; vv.y *= m; vv.z *= m; vv.w *= m;
                }
                ((CObj*)e)->d570(&vv);
            }
            return;
        }
    }
    {
        int e = FUN_00b53940(p);
        if (e != 0) {
            Vec4_s00b5_37f0 vv;
            vv.x = v[0]; vv.y = v[1]; vv.z = v[2]; vv.w = 0.0f;
            if (a3 != 0) {
                float m = ((CObj*)(*(int*)((char*)e + 0x58)))->getMass();
                vv.x *= m; vv.y *= m; vv.z *= m; vv.w *= m;
            }
            ((CObj*)e)->activate();
            ((CObj*)(*(int*)((char*)e + 0x58)))->m24(&vv);
        }
    }
}

// @ 0x00b544c0
extern "C" void FUN_00b544c0(void* a, int b)
{
    *(uint*)((char*)a + 0x50) &= 0xffffff7fu;
    if (b == 0) {
        b = FUN_00b53940(a);
        if (b == 0)
            return;
    }
    FUN_00b4d8e0(a, b);
}

// @ 0x00b544f0
extern "C" void FUN_00b544f0(void* a, int b)
{
    *(uint*)((char*)a + 0x50) |= 0x80u;
    if (b == 0) {
        b = FUN_00b53940(a);
        if (b == 0)
            return;
    }
    FUN_00b4d8e0(a, b);
}

// @ 0x00b54520
extern "C" bool FUN_00b54520(void* p)
{
    CObj* e = (CObj*)FUN_00b53940(p);
    if (e != 0 && e->isActive().b != 0) {
        Vec4_s00b5_37f0 v;
        FUN_00b658c0(&v, e);
        float s = v.x * v.x;
        s = s + v.y * v.y;
        s = s + v.z * v.z;
        return s > 1.52587890625e-05f;
    }
    return false;
}

// @ 0x00b545b0
extern "C" bool __stdcall FUN_00b545b0(S12* p)
{
    EIt12 it = g_ht12.find(p->key);
    int n = g_cnt12;
    if (it.a != g_arr12[n])
        return true;
    it = *(EIt12*)p;
    it.b = 0;
    void* r = FUN_00b51e80_s00b5_37f0((S12*)&it, 1.0f);
    if (r != 0) {
        ((ObjB*)r)->d770();
        *(void**)g_ht12.add((S12*)&it) = r;
    } else {
        return false;
    }
    return true;
}

// @ 0x00b54640
int C54640::FUN_00b54640(int a2)
{
    char pool[0x18];
    FixedPool* fp = (FixedPool*)pool;
    fp->mpHead = 0;
    fp->FUN_00921260(m43c, 0xc00, 0xc, 4, 0);

    char* hdr = pool + 0x08;                       // {begin, end, cap, tail} descriptor
    *(void**)(hdr + 0x00) = m43c;
    *(void**)(hdr + 0x04) = m43c + 0xc00;
    *(int*)(hdr + 0x08) = 0x0c;
    *(void**)(hdr + 0x0c) = m34;

    void* v = FUN_00921340(0x101);
    FUN_00b516d0(v, &a2, &a2, &a2, &a2, &a2, pool);

    *(float*)(pool + 0) = F_013f0620;
    *(float*)(pool + 4) = F_01470f1c;
    m10 = F_013f0620;
    m14 = F_01470f1c;
    *(void**)(hdr + 0x00) = 0;
    m18 = 0.0f;

    uint n = fp->FUN_009213c0(m0c);
    if (n > m08) FUN_00b5d220(n);

    int* p5 = *(int**)(a2 + 4);
    int* e = p5 + *(int*)(a2 + 8);
    int v1 = *e;
    int v6 = *p5;
    if (v6 == 0) {
        do { p5 = p5 + 1; v6 = *p5; } while (v6 == 0);
    }
    FUN_00b53410(v6, p5, v1, e);
    return (int)this;
}

// @ 0x00b547b0
cPoolHolderA* cPoolHolderA::Init(int a2, int a3)
{
    EastlFixedPool pool;
    PoolScratch scratch;
    pool.mpHead = 0;
    pool.init(&mPoolBuf[0], 0xc00, 0xc, 4, 0);
    pool.mnBegin = (uint32_t)&mArenaHead;
    pool.mnBlockSize = 0xc;
    pool.mnEnd = (uint32_t)&mArenaEnd;
    pool.mnBase = (uint32_t)&mPoolBuf[0];
    void* p = FUN_00921340(0x101);
    RegisterPool(p, a2, &a3, &a3, a3, &a3, &pool);
    m10 = 0x461c4000;
    m14 = 0x40000000;
    m18 = 0;
    uint32_t n = scratch.calc(mpBucketList);
    if (mnCapacity < n)
        Resize(n);
    return this;
}

// @ 0x00b54890
cPoolHolderB* cPoolHolderB::Init(int a2, int a3)
{
    EastlFixedPool pool;
    PoolScratch scratch;
    pool.mpHead = 0;
    pool.init(&mPoolBuf[0], 0x1000, 0x10, 4, 0);
    pool.mnBegin = (uint32_t)&mArenaHead;
    pool.mnBlockSize = 0x10;
    pool.mnEnd = (uint32_t)&mArenaEnd;
    pool.mnBase = (uint32_t)&mPoolBuf[0];
    void* p = FUN_00921340(0x101);
    RegisterPool(p, a2, &a3, &a3, a3, &a3, &pool);
    m10 = 0x461c4000;
    m14 = 0x40000000;
    m18 = 0;
    uint32_t n = scratch.calc(mpBucketList);
    if (mnCapacity < n)
        Resize(n);
    return this;
}

// @ 0x00b54970
cPoolHolderC* cPoolHolderC::Init(int a2, int a3)
{
    EastlFixedPool pool;
    PoolScratch scratch;
    pool.mpHead = 0;
    pool.init(&mPoolBuf[0], 0x80, 0x10, 4, 0);
    pool.mnBegin = (uint32_t)&mArenaHead;
    pool.mnBlockSize = 0x10;
    pool.mnEnd = (uint32_t)&mArenaEnd;
    pool.mnBase = (uint32_t)&mPoolBuf[0];
    void* p = FUN_00921340(9);
    RegisterPool(p, a2, &a3, &a3, a3, &a3, &pool);
    m10 = 0x461c4000;
    m14 = 0x40000000;
    m18 = 0;
    uint32_t n = scratch.calc(mpBucketList);
    if (mnCapacity < n)
        Resize(n);
    return this;
}

// @ 0x00b54a40
uint32_t* cPairMapInner::Lookup(const SPKeyPair* key)
{
    LookupRec local;
    FUN_00b51bb0(&local, key);
    if (local.m00 == mpTable[mnIndex]) {
        local.m00 = key->lo;
        local.m04 = key->hi;
        uint32_t flags = 0;
        local.m08 = 0;
        FUN_00b52120(&local, &local, flags);
    }
    return (uint32_t*)(local.m00 + 8);
}

// @ 0x00b54b40
void cPairMap::Insert(uint32_t a, uint32_t b, float c)
{
    SPKeyPair key;
    uint32_t lo = a, hi = b;
    if (hi < lo) {
        lo = b;
        hi = a;
    }
    key.lo = lo;
    key.hi = hi;
    uint32_t* r = mInner.Lookup(&key);
    *(float*)r = c;
}

// @ 0x00b54b80
void FUN_00b54b80(void)
{
    int n = ((int)(DAT_0167ed48 - DAT_0167ed44)) >> 3;
    if (n > 0) {
        SPListEntry* base = (SPListEntry*)DAT_0167ed44;
        for (int i = 0; i < n; i++) {
            int t = base[i].mnType;
            if (t - 1 == 0) {
                base[i].mpObj->Destroy();
                base = (SPListEntry*)DAT_0167ed44;
            }
        }
        int m = ((int)(DAT_0167ed48 - (uint8_t*)base)) >> 3;
        DAT_0167ed48 = DAT_0167ed48 + (-m) * 8;
    }
}

// @ 0x00b54be0
int* __cdecl FUN_00b54be0(int* param_1, int param_2)
{
    Build830 scratch;
    char flag = 0;
    void* u = scratch.Build(param_2, param_2);
    FUN_00b51840(param_1, u, (uint32_t)flag);
    CmdNode* node = (CmdNode*)*param_1;
    ((CmdLink*)node->mpBack)->mpField8 = &node->m10;
    void* o = FUN_00b3d310();
    if (((char*)o)[0x25] != 0) {
        void* o2 = FUN_00b3d310(param_2);
        ((CmdTail*)o2)->Run();
    }
    return param_1;
}

// @ 0x00b54c40
void* __cdecl FUN_00b54c40(ShapeObj* param_1, float param_2, ShapeReq* param_3)
{
    ExtRec ext;
    Key3   key;
    ReqRec req;
    WorkRec work;

    uint32_t endZ = *(uint32_t*)((uint8_t*)param_1->mpInfo + 0x10);
    uint32_t cenY = *(uint32_t*)((uint8_t*)param_1->mpInfo + 8);
    uint32_t cenZ = *(uint32_t*)((uint8_t*)param_1->mpInfo + 0xc);
    bool built = false;
    uint32_t m1b0 = 0;
    uint32_t m1b4 = cenY;
    ExtRec* pf = (ExtRec*)FUN_00b51780(&key, &m1b4);
    ext = *pf; ext.w = pf->w;
    uint32_t extcx = (uint32_t)&ext.x;
    (void)extcx;
    int r = FUN_00b51040_s00b5_47b0(&ext, param_2);
    req.mpA = (void*)r;
    if (r != 0)
        goto LAB_54e9f;
    r = FUN_00b51040_s00b5_47b0(&ext, 1.0f);
    if (r == 0) {
        key.a = 0; key.b = 0; key.c = 0;
        char c = (char)SP_GetPropertyAsKey(param_1->mpInfo, 0x532d802, &key);
        if (c != 0) {
            FUN_00b4d540(&work);
            c = FUN_00b510b0(&key, &work);
            if (c != 0) {
                req.m04 = m1b0;
                req.m08 = cenZ;
                req.mpA = (void*)cenY;
                int* p = FUN_00b54be0((int*)&work, (int)&req);
                r = (int)(p + 4);
                built = true;
                if (r != 0)
                    goto LAB_54e9f;
            }
        }
        if (param_3 == 0)
            return (void*)(uint32_t)r;
        ext.x = DAT_0167ecf4; ext.y = DAT_0167ecf8; ext.z = DAT_0167ecfc;
        if (param_3->mnFlags == 1) {
            ext.x = (param_1->f70 + param_1->f7c) * DAT_01481064;
            ext.y = (param_1->f80 + param_1->f74) * DAT_01481064;
            ext.z = (param_1->f84 + param_1->f78) * DAT_01481064;
        }
        int shape = FUN_00b4f660(param_3->mpShape, 1.0f, &ext, param_3->m04);
        if (shape == 0)
            return (void*)(uint32_t)r;
        FUN_00b4d5d0(&m1b4, shape, 1.0f, param_3->mnFlags, 0, 0);
        if (param_3->mbFlag != 0)
            FUN_01127680(shape, 1.0f, &work);
        int* p = FUN_00b54be0((int*)&work, 0);
        r = (int)(p + 4);
        built = true;
        if (r == 0)
            return (void*)(uint32_t)r;
    }
LAB_54e9f:
    if (param_2 != 1.0f) {
        int s2 = FUN_00b64a00(*(int*)((uint8_t*)r + 0xc), param_2);
        int ret = r;
        if (s2 != 0) {
            FUN_00b4d5d0(&m1b4, s2, param_2, *(int*)((uint8_t*)r + 0x14), r, 0);
            if (0.0f < *(float*)((uint8_t*)r + 0x24)) {
                FUN_00b4d3f0((uint8_t*)r + 0x20);
                float s = (param_2 * param_2) * param_2;
                FUN_01081bb0(s);
            }
            int* p = FUN_00b54be0((int*)&work, 0);
            ret = (int)(p + 4);
            if (!built) {
                ((CmdChain*)(void*)ret)->Unlink();
                return (void*)(uint32_t)ret;
            }
        }
        return (void*)(uint32_t)ret;
    }
    if (built)
        return (void*)(uint32_t)r;
LAB_54eb5:
    return (void*)(uint32_t)r;
}

// @ 0x00b56010
void __stdcall FUN_00b56010(CellUpdateArg* arg)
{
    ListObject* obj = arg->mpObject;
    if (obj->GetType() == 0xe)
        obj = obj->mChild;

    void* value = obj->mValue;
    if (value) {
        if (obj->mField04 != 0)
            obj->mField06++;

        SPListEntry_s00b5_5680 entry;
        entry.mpObj = value;
        entry.mnType = 1;
        g_167ed44.push_back(entry);
    }
}

// @ 0x00b57680
void HkPtrConverter::Convert(HkPtrPair* pair)
{
    void* first = ResolveHkPtr(pair->m_first);
    void* second = ResolveHkPtr(pair->m_second);
    void* local[2];
    local[0] = first;
    local[1] = second;
    v14(local, 1, pair);
}

// @ 0x00b576d0
void HkNodePool::AddNode(const HkNodeData* data)
{
    HkPoolNode* node = m_freeList;
    if (node != 0)
        m_freeList = node->m_next;
    else {
        void* allocator = m_allocator;
        node = (HkPoolNode*)opnew_f473a0(allocator, "Simulator", 0, 0,
                                         (const char*)0x013ebb38, 0xd1);
    }
    if (node != 0) {
        node->m_a = data->m_a;
        node->m_b = data->m_b;
        node->m_c = data->m_c;
    }
    node->m_flags = 0;
}

// @ 0x00b57720
void HkContainerOwner::Destroy()
{
    m_vec1.Clear();
    m_vec2.Clear();
    m_vptr = (void*)0x013f8990;
}

// @ 0x00b57840
void HkSelectOwner::Select(HkPtrPair* pair)
{
    HkRelativePtr* firstNode = pair->m_first;
    HkRelativePtr* firstRoot = firstNode;
    for (HkRelativePtr* n = firstNode->m_next; n != 0; n = n->m_next)
        firstRoot = n;
    HkBody* a = (HkBody*)ResolveHkPtr(firstRoot);

    HkRelativePtr* secondNode = pair->m_second;
    HkRelativePtr* secondRoot = secondNode;
    for (HkRelativePtr* n = secondNode->m_next; n != 0; n = n->m_next)
        secondRoot = n;
    HkBody* b = (HkBody*)ResolveHkPtr(secondRoot);

    if ((uint32_t)b < (uint32_t)a) {
        HkBody* t = a;
        a = b;
        b = t;
    }

    HkValueRange key;
    key.m_lo = (uint32_t)a;
    key.m_hi = (uint32_t)b;

    uint32_t* ref = m_refs.FindRef(&key);
    ++*ref;

    void* endNode = m_table.m_buckets[m_table.m_bucketCount];
    HkHashIter it;
    m_table.Find(&it, &key);
    if (it.m_node != endNode) {
        pair->m_flag = 1;
        return;
    }

    void* handleA = a->m_handle;
    if (handleA == 0)
        return;
    void* handleB = b->m_handle;
    if (handleB == 0)
        return;

    PropPair pa;
    PropPair pb;
    int typeA = a->getProp(&pa, 0)->v;
    int typeB = b->getProp(&pb, 0)->v;

    HkBody* a3 = 0;
    HkBody* a2 = 0;
    HkBody* b3 = 0;
    HkBody* b2 = 0;
    if (typeA == 3)
        a3 = a;
    else if (typeA == 2)
        a2 = a;
    if (typeB == 3)
        b3 = b;
    else if (typeB == 2)
        b2 = b;

    HkBody* chosen;
    if (a3 != 0 && a3->v20() == &g_18c6de8) {
        chosen = b2;
    } else if (b3 != 0 && b3->v20() == &g_18c6de8) {
        chosen = a2;
    } else {
        return;
    }

    if (chosen == 0)
        return;
    if (chosen->m_field88 - 1 > 1)
        return;
    pair->m_flag = 1;
}

// @ 0x00b579b0
void HkRefOwner::Remove(HkRangeSource* range)
{
    uint32_t lo = range->m_lo;
    uint32_t hi = range->m_hi;
    if (hi < lo) {
        uint32_t t = lo;
        lo = hi;
        hi = t;
    }
    HkValueRange key;
    key.m_lo = lo;
    key.m_hi = hi;
    uint32_t* ref = m_map.FindRef(&key);
    *ref -= 1;
    int count = (int)*ref;
    if (count == 0) {
        v14(&key, 0, 0);
        m_map.Erase(&key);
        return;
    }
    if (count < 0) {
        *ref = 0;
        m_map.Erase(&key);
    }
}

// @ 0x00b57bf0
void __cdecl FUN_00b57bf0(void* a, void* b, float t)
{
    if (g_167ecdc_s00b5_6fe0 == 0)
        return;
    void* ra = FUN_00b53940_s00b5_6fe0(a);
    void* rb = FUN_00b53940_s00b5_6fe0(b);
    if (ra != 0 && rb != 0)
        ((HkWorld*)g_167ecdc_s00b5_6fe0)->AddPair(ra, rb, t);
}

// @ 0x00b5a260
void __thiscall HavokSystem::FUN_00b5a260(void* p2, void* p3)
{
    if (DAT_0167ecd0 != 0) {
        FUN_00b530e0(p2, p3);
        if (busy20 == 0) {
            void* sub = (p2 != 0) ? ((VFnR2)(*(void***)p2)[0xb8 / 4])(p2, 0x17f243b) : 0;
            void* u = ((VFnR1)(*(void***)sub)[0x20 / 4])(sub);
            int i = FUN_00b532f0(u);
            if (i != 0)
                CreateHavokEntityForObject(sub, p2, p3, (void*)i);
        }
    }
}

// @ 0x00b5a2d0
void __thiscall HavokSystem::FUN_00b5a2d0()
{
    if (DAT_0167ecd0 != 0) {
        void** it  = begin;
        void** fin = end;
        if (it != fin) {
            do {
                void* p = *it;
                void* sub = (p != 0) ? ((VFnR2)(*(void***)p)[0xb8 / 4])(p, 0x17f243b) : 0;
                FUN_00b530e0(p, p);
                if (busy20 == 0) {
                    void* u = ((VFnR1)(*(void***)sub)[0x20 / 4])(sub);
                    void* buf[2];
                    int* r = map.FUN_00b41b30(buf, &u);
                    if (*r != map.table[map.count]) {
                        int leaf = *r + 4;
                        if (leaf != 0)
                            CreateHavokEntityForObject(sub, p, p, (void*)leaf);
                    }
                }
                ++it;
            } while (it != fin);
        }
    }
}

// @ 0x00b5a410
void __thiscall HavokSystem::FUN_00b5a410()
{
    HKWorldCinfo cinfo;
    uint8_t      buf[4];

    cinfo.ctor();
    cinfo.f10 = 0.0f;
    cinfo.f14 = 0.0f;
    cinfo.f18 = 0.0f;
    cinfo.f1c = 0.0f;
    cinfo.b94 = 1;
    cinfo.b95 = DAT_01569a94;
    cinfo.setBroadPhaseWorldSize(DAT_0156b6ec * DAT_013eb95c);
    cinfo.f70 = DAT_01569aa0;
    cinfo.f68 = DAT_01569a98;
    cinfo.f6c = DAT_01569a9c;

    void** memvt = *(void***)DAT_016e4178;
    void* block = ((VFnAlloc)memvt[0x10 / 4])(DAT_016e4178, 0x2f0, 0x2c);
    *(uint16_t*)((uint8_t*)block + 4) = 0x2f0;
    DAT_0167ecd0 = ((hkWorld_s00b5_a260*)block)->CreateWorld(&cinfo, 0x765c);
    registerAllAgents(*(void**)((uint8_t*)DAT_0167ecd0 + 0x80));

    void* raw = ((VFnAlloc)memvt[0x10 / 4])(DAT_016e4178, 0x9c, 0x24);
    *(uint16_t*)((uint8_t*)raw + 4) = 0x9c;
    hkGroupFilter* filter = ((hkGroupFilter*)raw)->ctor();
    filter->FUN_010c3c60(-2, -2);
    filter->enableCollisionsBetween(4, 4);
    filter->enableCollisionsBetween(4, 1);
    filter->enableCollisionsBetween(4, 2);
    filter->enableCollisionsBetween(4, 7);
    filter->enableCollisionsBetween(4, 8);
    filter->enableCollisionsBetween(4, 9);
    filter->enableCollisionsBetween(4, 5);
    filter->enableCollisionsBetween(4, 3);
    filter->enableCollisionsBetween(1, 4);
    filter->enableCollisionsBetween(1, 5);
    filter->enableCollisionsBetween(2, 2);
    filter->enableCollisionsBetween(2, 4);
    filter->enableCollisionsBetween(2, 7);
    filter->enableCollisionsBetween(2, 8);
    filter->enableCollisionsBetween(7, 4);
    filter->enableCollisionsBetween(7, 2);
    filter->enableCollisionsBetween(8, 8);
    filter->enableCollisionsBetween(8, 4);
    filter->enableCollisionsBetween(8, 5);
    filter->enableCollisionsBetween(8, 2);
    filter->enableCollisionsBetween(8, 3);
    filter->enableCollisionsBetween(9, 4);
    filter->enableCollisionsBetween(9, 5);
    filter->enableCollisionsBetween(10, 10);
    filter->enableCollisionsBetween(10, 4);
    filter->enableCollisionsBetween(10, 5);
    filter->enableCollisionsBetween(10, 2);
    filter->enableCollisionsBetween(10, 3);
    filter->enableCollisionsBetween(6, 8);
    filter->enableCollisionsBetween(6, 9);
    filter->enableCollisionsBetween(11, 3);
    filter->enableCollisionsBetween(11, 2);
    filter->enableCollisionsBetween(12, 1);
    filter->enableCollisionsBetween(12, 8);
    filter->enableCollisionsBetween(12, 9);
    filter->enableCollisionsBetween(3, 4);
    filter->enableCollisionsBetween(3, 8);
    filter->enableCollisionsBetween(5, 4);
    filter->enableCollisionsBetween(5, 1);
    filter->enableCollisionsBetween(5, 8);
    filter->enableCollisionsBetween(5, 9);
    ((hkWorld_s00b5_a260*)DAT_0167ecd0)->setCollisionFilter(filter, hkBool_s00b5_a260(1), 0, 1);

    void* obj = FUN_006abeb0(0x196c);
    if (obj != 0) {
        *(void**)obj = (void*)0x14614f4;
        FUN_00b54890((void*)((uint8_t*)obj + 4), buf, buf);
        FUN_00b54970((void*)((uint8_t*)obj + 0x1858), buf, buf);
    }
    DAT_0167ecdc = obj;
    FUN_010834f0(DAT_0167ecd0, obj);
}

// @ 0x00b5a750
void RebuildStaticCollision()
{
    if (!sRebuildBuildingBodies)
        return;
    sRebuildBuildingBodies = false;
    if (TerrainInfo()->mWaterMode != 0)
        return;

    BodyMap oldBodies(sBuildingBodies);
    sBuildingBodies.clear();

    hkRigidBodyCinfo_s00b5_a750 info;
    info.m_restitution = 0.0f;
    info.m_friction = 0.1f;
    info.m_motionType = 7;
    info.m_shape = 0;
    info.m_collisionFilterInfo = 7;

    cModelInfoList* modelInfos = &ModelInfoOwner()->mList;
    cCityObjects* cityObjects = CityObjects();
    CityMap* objectMap = cityObjects->GetObjectMap();
    CityIterator it = objectMap->begin();
    CityNode* end = objectMap->endNode();
    for (; it.mpNode != end; it.increment())
    {
        cCityObject* object = it.mpNode->mpObject;
        if (object->IsDestroyed())
            continue;
        if (object->mType == 3 && (object->mObjectFlags & 1))
            continue;
        if (object->mType == 4)
            continue;

        u32* key = &object->mID;
        BodyIterator found = oldBodies.find(*key);
        if (found.mpNode != oldBodies.endNode())
        {
            sBuildingBodies[*key] = found.mpNode->mpBody;
            oldBodies.erase(found);
            continue;
        }

        float height = object->mHeight;
        hkShape_s00b5_a750* shape = 0;
        cSPTransform_s00b5_a750* transform = object->GetTransform();
        Vector3 up = { 0.0f, 0.0f, height * 0.5f };
        Vector3 offset = up * transform->mRotation;
        if (sUseModelCollision && object->mType == 3 && object->mModelKey != 0)
        {
            cModelInfo_s00b5_a750* modelInfo = modelInfos->mpBegin;
            for (; modelInfo != modelInfos->mpEnd; modelInfo++)
                if (modelInfo->mModelKey == object->mModelKey)
                    break;
            if (modelInfo != modelInfos->mpEnd && !((modelInfo->mFlags >> 1) & 1))
            {
                cModelResource* resource = ModelManager()->GetResource(0xeb9968);
                if (resource)
                    resource->AddRef();
                u32 flags;
                if (object->mType == 3)
                    flags = sHutModelLoadFlags;
                else
                    flags = (sModelLoadFlags & 0xffff62ff) | 0x6200;
                {
                    cModelPtr model(resource->Load(object->mModelKey, flags, 0));
                    cCollisionRequest request;
                    request.mpOwner = model.mpModel;
                    request.mA = sCollisionScaleA;
                    request.mB = sCollisionScaleB;
                    request.mFlag = false;
                    cCollisionShape* collision = GetCollisionShape(model.mpModel, object->GetTransform()->mScale, &request);
                    if (collision && collision->mpShape)
                    {
                        shape = collision->mpShape;
                        offset = sZeroVector;
                    }
                }
                resource->Release();
                if (shape)
                    goto haveShape;
            }
        }
        {
            float halfHeight = object->mHeight * 0.5f;
            if (halfHeight > object->mRadius)
            {
                float d = halfHeight - object->mRadius;
                Vector3 top = { sZeroVector.x, sZeroVector.y, d };
                Vector3 bottom = { sZeroVector.x, sZeroVector.y, -d };
                hkVector4_s00b5_a750 vertexB;
                vertexB.set(bottom.x, bottom.y, bottom.z, 0.0f);
                hkVector4_s00b5_a750 vertexA;
                vertexA.set(top.x, top.y, top.z, 0.0f);
                shape = new hkCapsuleShape(vertexA, vertexB, object->mRadius);
            }
            else
                shape = new hkSphereShape(object->mRadius);
        }
    haveShape:
        info.m_shape = shape;
        hkRigidBody_s00b5_a750* body = SP::Havok::CreateRigidBody_s00b5_a750(&info);
        shape->removeReference();

        Quaternion q = rw::math::fpu::QuaternionFromMatrix33(transform->mRotation, 0.0f);
        float invLength = (float)(1.0 / sqrt((double)q.w * q.w + (double)q.z * q.z + (double)q.y * q.y + (double)q.x * q.x));
        hkQuaternion_s00b5_a750 rotation;
        rotation.m_vec.set(invLength * q.x, invLength * q.y, invLength * q.z, invLength * q.w);
        body->setRotation(rotation);
        hkVector4_s00b5_a750 position;
        position.set(object->mPosition.x + offset.x, object->mPosition.y + offset.y,
                     object->mPosition.z + offset.z, 0.0f);
        body->setPosition(position);
        body->m_userData = object;
        body->addProperty(0, 2);
        body->addProperty(1, (u32)&object);
        body->addProperty(5, (__int64)((object->mType == 3) + 10));
        body->setMotionType(7, 1, 0);
        sWorld->addEntity(body, 1);
        sBuildingBodies[object->mID] = body;
        body->removeReference();
    }

    if (sPlanetBodies.empty() || sRebuildPlanetBodies)
    {
        sRebuildPlanetBodies = false;
        cPlanetModel_s00b5_a750* planet = PlanetModel();
        ModelManager()->GetResource(0x3fbae24);
        cPlanetObject** planetObjects;
        int count;
        if (planet && planet->mpISphere)
            count = planet->mpISphere->GetPlanetObjects(planetObjects);
        else
            count = 0;
        for (int i = 0; i < count; i++)
        {
            if (sProcessedPlanetObjects.find(i) != &sProcessedPlanetObjects.mAnchor)
                continue;
            cPlanetObject* planetObject = planetObjects[i];
            if (!planetObject)
            {
                sProcessedPlanetObjects.insert(i);
                continue;
            }
            if (!((planetObject->mFlags >> 14) & 1))
            {
                sRebuildBuildingBodies = true;
                sRebuildPlanetBodies = true;
                continue;
            }

            Vector3 position = ((cPlanetObjectData*)planetObject->mpPropList)->mPosition;
            cModelPtr found;
            Vector3* snapped = cityObjects->SnapToSurface(position);
            if (snapped)
            {
                position = *snapped;
                found = GonzagoModelWorld()->FindModelAt(position.x, position.z, 0);
                cPlanetObject* foundObject = (cPlanetObject*)found.mpModel;
                if (!foundObject)
                {
                    sProcessedPlanetObjects.insert(i);
                    continue;
                }
                if (!((foundObject->mFlags >> 14) & 1) || ((foundObject->mFlags >> 18) & 1))
                {
                    sRebuildBuildingBodies = true;
                    sRebuildPlanetBodies = true;
                    continue;
                }
                foundObject->mTransform = planetObject->mTransform;
                planetObject = foundObject;
            }

            sProcessedPlanetObjects.insert(i);
            {
                Property* prop;
                if (planetObject->mpPropList && planetObject->mpPropList->GetProperty(0x37575e5, prop) &&
                    prop->mType == 1 && !*prop->GetBool())
                    continue;
            }

            cSPTransform_s00b5_a750 transform(planetObject->mTransform);
            float phantomHeight = sPhantomHeight;
            float phantomRadius = sPhantomRadius;
            bool bPhantom = false;
            GetBoolProperty(planetObject->mpPropList, 0x3f6d22a, bPhantom);
            u32 objectType = 0;
            if (GetPropertyAsUint32(planetObject->mpPropList, 0x4ce873a, objectType) && objectType == 0x4fc5ab9d)
            {
                phantomRadius = planetObject->mRadius;
                phantomHeight = phantomRadius + sTreePhantomExtraHeight;
            }
            else if (!bPhantom)
            {
                // fixed rigid body from the object's collision model
                cCollisionRequest request;
                request.mpOwner = planetObject;
                request.mA = sCollisionScaleA;
                request.mB = sCollisionScaleB;
                request.mFlag = false;
                cCollisionShape* collision = GetCollisionShape(planetObject, planetObject->mTransform.mScale, &request);
                if (!collision)
                    continue;
                hkShape_s00b5_a750* shape = collision->mpShape;
                if (!shape)
                    continue;
                info.m_shape = shape;
                hkRigidBody_s00b5_a750* body = SP::Havok::CreateRigidBody_s00b5_a750(&info);
                shape->removeReference();
                Matrix3 rotation;
                rotation.Assign(transform.mRotation);
                Quaternion q = QuaternionFromMatrix(rotation);
                hkQuaternion_s00b5_a750 hq;
                hq.m_vec.set(q.x, q.y, q.z, q.w);
                body->setRotation(hq);
                hkVector4_s00b5_a750 bodyPosition;
                bodyPosition.set(transform.mPosition.x, transform.mPosition.y, transform.mPosition.z, 0.0f);
                body->setPosition(bodyPosition);
                body->m_userData = 0;
                body->addProperty(0, 2);
                body->addProperty(1, 0);
                body->addProperty(5, 0xb);
                body->setMotionType(7, 1, 0);
                sWorld->addEntity(body, 1);
                body->removeReference();
                sPlanetBodies.push_back(body);
                continue;
            }

            // capsule phantom standing on the planet surface
            Quaternion orientation;
            planet->BuildSurfaceOrientation(orientation, transform);
            hkVector4_s00b5_a750 base;
            base.set(0.0f, 0.0f, 0.0f, 0.0f);
            hkVector4_s00b5_a750 top;
            top.set(0.0f, 0.0f, phantomHeight, 0.0f);
            hkShape_s00b5_a750* capsule = new hkCapsuleShape(base, top, phantomRadius);
            hkQuaternion_s00b5_a750 hq;
            hq.m_vec.set(orientation.x, orientation.y, orientation.z, orientation.w);
            hkTransform_s00b5_a750 phantomTransform;
            phantomTransform.m_translation.set(transform.mPosition.x, transform.mPosition.y, transform.mPosition.z, 0.0f);
            phantomTransform.m_rotation.set(hq);
            hkSimpleShapePhantom* phantom = new hkSimpleShapePhantom(capsule, phantomTransform, 10);
            phantom->m_userData = planetObject;
            phantom->addProperty(0, 4);
            sWorld->addPhantom(phantom);
            phantom->removeReference();
            capsule->removeReference();
            sPlanetPhantoms.push_back(phantom);
        }
    }

    // bodies of objects that are gone
    {
        BodyNode** bucket = oldBodies.mpBucketArray;
        BodyNode* node = *bucket;
        while (node == 0)
            node = *++bucket;
        BodyNode* endNode = oldBodies.mpBucketArray[oldBodies.mnBucketCount];
        while (node != endNode)
        {
            if (node->mpBody)
                ((hkWorld_s00b5_a750*)node->mpBody->m_world)->removeEntity(node->mpBody);
            node->mpBody = 0;
            node = node->mpNext;
            while (node == 0)
                node = *++bucket;
        }
    }
}

// @ 0x00b5b540
bool FUN_00b5b540(int* a, int* b, int, int p4)
{
    int* s = (int*)((int(__thiscall*)(void*))g_vfn(a, 0x10))(a);
    b[2] = s[0];
    b[3] = p4;
    b[4] = s[2];
    int r = ((int(__thiscall*)(void*, unsigned))g_vfn(b, 0xc))(b, 0x532dc8b);
    if (!r) return false;
    int* t = (int*)((int(__thiscall*)(void*))g_vfn(a, 0x18))(a);
    unsigned u = ((unsigned(__thiscall*)(void*))g_vfn(t, 0x1c))(t);
    FUN_004cd3c0((void*)u);
    int q = ((int(__thiscall*)(void*, int, unsigned))g_vfn(t, 0x30))(t, *(int*)(r + 0x18), u);
    return q != -1;
}

// @ 0x00b5b6f0
void FUN_00b5b6f0(int v)
{
    int* p = g_1686a1c;
    if (p < g_1686a20)
    {
        g_1686a1c = p + 1;
        if (p) *p = v;
    }
    else
    {
        ((SPVector_00b96600*)0x1686a18)->FUN_00b96600(g_1686a1c, &v);
    }
}

// @ 0x00b5b730
void FUN_00b5b730(void)
{
    int* begin = g_1686a18;
    int* end   = g_1686a1c;

    // erase(begin, end): nothing to move, then reset the end pointer
    FUN_011e0744(begin, end, 0);
    g_1686a1c += begin - end;
    if (g_1686a1c - g_1686a18 > 0)
        ((EastlIntVector*)&g_1686a18)->resize(0);

    // rebuild the (now empty) vector through a copy, then swap the stale
    // buffer into the temporary so releasing it frees the old allocation
    EastlIntVector tmp((int)(g_1686a1c - g_1686a18), &g_1686a24);
    tmp.mpEnd = (int*)FUN_011e0744(tmp.mpBegin, g_1686a18,
                                   (unsigned)((char*)g_1686a1c - (char*)g_1686a18))
              + (g_1686a1c - g_1686a18);
    ((EastlIntVector*)&g_1686a18)->swap(&tmp);
    if (tmp.mpBegin && eastl_block_owner(tmp.mpBegin))
        FUN_00f47380(tmp.mpBegin);
}
