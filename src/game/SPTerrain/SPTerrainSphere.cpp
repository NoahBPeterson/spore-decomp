// src/game/SPTerrain/SPTerrainSphere.cpp -- migrated from slice(s) s00fac5c0, s00fabd60, s00fa9300, s00fa86c0, s00fa6480, s00fa47b0, s00fa1bc0, s00f9fef0, s00f9df20, s00f9d080, s00f9c470, s00f9b620, s00f9a610, s00f977c0, s00f955f0, s00fab2b0, s00faa5c0, s00fa9d20, s00fa75f0, s00fa5610, s00fa3860, s00fa0f90, s00f986f0 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainSphere.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_16ca0d8[];
extern "C" char g_16ca404[];

#include "game/types.h"
#include <math.h>
#include "SP/cDirectPropertyList.h"
#include "SP/cTerrainSphere.h"
#include "SP/cTerrainSphereImpostorJob.h"
#include "SP/cTerrainSphereQuad.h"
#include "SP/cTerrainStateMgr.h"
#include "SP/cViewer.h"
#include "SP/cWeatherManager.h"
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cTerrainSphereDecal.h"
#include <intrin.h>
#include "SP/cFrustumCull.h"
#include <new>
#include <string.h>
#include <xmmintrin.h>
#include "EA/ResourceMan/Key.h"
#include "SP/cTerrainMapSet.h"
#include "EA/LimitStopwatch.h"
#include "cSPTransform.h"
#include "rw/graphics/CompiledState.h"
#include "rw/graphics/Raster.h"
#include "SP/cSPEditorPhysicsWorld.h"
#include <stddef.h>
#include "cSPVector3.h"
#include "cSPColorRGBA.h"
#include "SP/cTerrainSphereLight.h"
#include "rw/graphics/GlobalState.h"
#include "SP/cJob.h"
#include "SP/cITerrainSphere.h"
#include "SP/cJobManager.h"
#include "sse_helpers.h"

// ---- items of slice s00f986f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
union W {
    uint32_t u;
    float f;
};
struct Vec4 {
    float x, y, z, w;
};
inline Vec4 operator-(const Vec4& a, const Vec4& b)
{
    Vec4 r = {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
    return r;
}
inline Vec4 operator*(const Vec4& a, float s)
{
    Vec4 r = {a.x * s, a.y * s, a.z * s, a.w * s};
    return r;
}
inline Vec4 operator+(const Vec4& a, const Vec4& b)
{
    Vec4 r = {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
    return r;
}
#define VSLOTS10(n) \
    virtual void pad##n##0(); virtual void pad##n##1(); virtual void pad##n##2(); \
    virtual void pad##n##3(); virtual void pad##n##4(); virtual void pad##n##5(); \
    virtual void pad##n##6(); virtual void pad##n##7(); virtual void pad##n##8(); \
    virtual void pad##n##9();
struct SkyState {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual char* GetRecord();  // vtable +0x10
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    VSLOTS10(1) VSLOTS10(2) VSLOTS10(3) VSLOTS10(4) VSLOTS10(5) VSLOTS10(6)
    virtual uint32_t* GetLightVector();  // vtable +0x118

    void Update();
};
#define SRC(off) (*(W*)(rec + (off)))
struct Vec3 {
    float x, y, z;
};
struct cTerrainMapSet_s00f9_86f0 {
    char  pad00[0x34];      // +0x00..0x33
    float mRadius34;        // +0x34
    float mRadius38;        // +0x38
    float mRadius3c;        // +0x3c
    float GetHeightAt(Vec3* p);   // 0xf927c0
};
struct TerrainModelObj {
    void** vtbl;            // +0x00
};
struct TerrainModel {
    TerrainModelObj* mpObj;     // +0x00
    unsigned char mFlags;       // +0x04
    char pad05[3];              // +0x05..0x07
    unsigned short mFlags2;     // +0x08
    unsigned short mCounter;    // +0x0a
    float x;                    // +0x0c
    float y;                    // +0x10
    float z;                    // +0x14
};
struct ConeBlock {
    unsigned mConeCos;      // +0x00 (object +0x638)
    unsigned mConeA;        // +0x04 (object +0x63c)
    unsigned mConeB;        // +0x08 (object +0x640)
    unsigned mConeC;        // +0x0c (object +0x644)
    unsigned mBlockA[4];    // +0x10 (object +0x648)
    unsigned mBlockD[4];    // +0x20 (object +0x658)
    unsigned mBlockC[4];    // +0x30 (object +0x668)
    unsigned mBlockB[4];    // +0x40 (object +0x678)
    unsigned mBlockG[4];    // +0x50 (object +0x688)
    unsigned mBlockF[4];    // +0x60 (object +0x698)
    unsigned mBlockE[4];    // +0x70 (object +0x6a8)
    unsigned mConeInvB;     // +0x80 (object +0x6b8)
    unsigned mConeInvA;     // +0x84 (object +0x6bc)
    unsigned mConeNB;       // +0x88 (object +0x6c0)
    unsigned mConeNA;       // +0x8c (object +0x6c4)
};
struct TerrainSphere {
    char pad000[0x2c];              // +0x000..0x02b
    cTerrainMapSet_s00f9_86f0* mMap;           // +0x02c
    char pad030[0x2b8 - 0x030];     // +0x030..0x2b7
    void** mDecalBegin;             // +0x2b8
    void** mDecalEnd;               // +0x2bc
    char pad2c0[0x32c - 0x2c0];     // +0x2c0..0x32b
    float mConeX;                   // +0x32c
    float mConeY;                   // +0x330
    float mConeZ;                   // +0x334
    char pad338[0x434 - 0x338];     // +0x338..0x433
    float mTrail[24];               // +0x434..0x493
    char pad494[0x638 - 0x494];     // +0x494..0x637
    ConeBlock mCone;                // +0x638..0x6c7
    char pad6c8[0x7d8 - 0x6c8];     // +0x6c8..0x7d7
    TerrainModel** mModels;         // +0x7d8
    TerrainModel** mModelsEnd;      // +0x7dc
    char pad7e0[0x8ac - 0x7e0];     // +0x7e0..0x8ab
    unsigned char mFlag8ac;         // +0x8ac
    char pad8ad[0xa2c - 0x8ad];     // +0x8ad..0xa2b
    Vec4 mTarget;                   // +0xa2c..0xa3b
};
typedef void (__thiscall* RemoveDecalFn)(void* self, int index);
typedef char* (__thiscall* GetRecordFn)(void* self);
typedef void (__thiscall* PinModelFn)(TerrainModelObj* self, TerrainModel* m, int arg);
// ---- items of slice s00f986f0 end

// ---- items of slice s00fa0f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile*, long);
extern "C" long __cdecl _InterlockedIncrement(long volatile*);
extern int g_TerrainInitCount;                  // 0x016c9e64
extern bool g_TerrainStaticsReady;              // 0x016c9e60
extern uint32_t g_TerrainPoolParam;             // 0x016c9e74
extern uint32_t g_SharedResourceID;             // 0x015b1120
extern const char kAllocTagSimulator[];         // 0x013f09b4
extern const char kEastlAllocFile[];            // 0x013ebb38
#pragma intrinsic(_InterlockedExchange, _InterlockedExchangeAdd, _InterlockedIncrement)
void* __cdecl operator new(unsigned size, const char* name, int a, int b,
                           const char* file, int line);                  // 0x00f473a0
inline void Clear(Vec4& v)
{
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;
    v.w = 0.0f;
}
struct Vec2 {
    float x, y;
    Vec2(float ax, float ay) : x(ax), y(ay) {}
};
struct AtomicRefCounted {
    void* vftable;
    uint32_t mField4;
    volatile long mnRefCount;

    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    int Release()
    {
        _InterlockedExchangeAdd(&mnRefCount, -1);
        if (_InterlockedExchangeAdd(&mnRefCount, 0) < 1) {
            _InterlockedIncrement(&mnRefCount);
            return 1;
        }
        return _InterlockedExchangeAdd(&mnRefCount, 0);
    }
};
struct __declspec(novtable) cITerrainGenerationStep {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
struct RefCountVTemplate {          // EA::RefCountVTemplate<int> at +4 of the job
    virtual void v0();
    int mRefCount;
    RefCountVTemplate() : mRefCount(0) {}
};
struct cTerrainSphereImpostorJob : cITerrainGenerationStep, RefCountVTemplate {
    uint32_t mField0C;
    uint32_t mPad10[2];
    int mField18;
    int mField1C;
    uint32_t mPad20;
    bool mField24;
    cTerrainSphereImpostorJob()
    {
        mField0C = 0;
        mField18 = -1;
        mField1C = -1;
        mField24 = false;
    }
    int AddRef();
    int Release();
    void v0();
};
struct cRefBaseAt8 {
virtual void v0();
virtual void v1();
    virtual void AddRef();
    virtual void Release();
};
struct cTerrainSphere;
struct cWeatherManager {
    uint32_t pad0[2];
    cRefBaseAt8 mRefBase;           // +0x08
    uint32_t padTail[(0x1a0 - 0x0c) / 4];
    cWeatherManager();              // 0x00fc6640
    void Init(cTerrainSphere* owner);   // 0x00fc5900
};
struct cDecalManagerImpl {          // 0xc bytes, vtable 0x01490720
virtual void v0();
virtual void v1();
    virtual void AddRef();          // slot 2 (+8)
    volatile long mRefCount;
    cTerrainSphere* mpOwner;
    cDecalManagerImpl(cTerrainSphere* owner)
    {
        _InterlockedExchange(&mRefCount, 0);
        mpOwner = owner;
    }
};
struct cViewer {                    // 0x174 bytes
    uint32_t mPad[0x174 / 4];
    cViewer();                      // 0x007c3f70
    void Init(int arg);             // 0x007c4dd0
};
struct cTerrainPlanetData {
    uint32_t pad0[6];
    uint32_t mField18;              // +0x18
    uint32_t pad1c[(0x34 - 0x1c) / 4];
    float mField34;                 // +0x34
    float mField38;                 // +0x38
    float mField3C;                 // +0x3c
};
struct cTerrainShaderBlock {
    uint32_t pad0[7];
    uint32_t mField1C;
    uint32_t mField20;
    uint32_t pad24;
    uint32_t mField28;
};
struct cTerrainStateMgr {           // 0xc40 bytes
    uint32_t pad0[0x344 / 4];
    cTerrainShaderBlock* mpBlock;   // +0x344
    uint32_t padTail[(0xc40 - 0x348) / 4];
    cTerrainStateMgr(cTerrainSphere* owner);    // 0x00fbe130
    void Init(int arg);                          // 0x00fc04b0
};
struct cQuadBuffersPool {           // 0x10 bytes
    uint32_t mPad[4];
    cQuadBuffersPool();             // 0x00faed90
    void Init(uint32_t a, int b);   // 0x00faeda0
};
struct cTerrainSphereQuad {         // 0x1b8 bytes
    uint32_t mPad[0x1b8 / 4];
    cTerrainSphereQuad();           // 0x00fb4c90
    void Init(cTerrainSphere* owner, int a, int face, const Vec2* offset, const Vec2* scale, int layer);   // 0x00fb4e10
};
struct cMessageServer {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual bool AddHandler(void* handler, uint32_t messageID);   // slot 8 (+0x20)
};
cMessageServer* MessageServer();    // 0x0067dcc0
struct cResourceSource {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual AtomicRefCounted* Get(uint32_t id, int a, int b);     // slot 8 (+0x20)
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
    virtual void* CreateTexture(void* source, uint32_t flags, int width, int height,
                                int mip, int format, int a, int b); // slot 15 (+0x3c)
};
cResourceSource* GetResourceSource();   // 0x0067dd60
struct cRenderTargetHandle {
    uint32_t mRaster;                       // +0x00
    uint32_t mRectId;                       // +0x04
};

struct cRenderManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual cRenderTargetHandle* CreateRenderTarget(cRenderTargetHandle* out,
                                                    int width, int height,
                                                    int format, int mip,
                                                    int flags, int zero); // slot 4 (+0x10)
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17();
    virtual void InitializeRenderTarget(uint32_t raster, uint32_t rectId,
                                        const char* name);            // slot 18 (+0x48)
};
cRenderManager* RenderManager();        // 0x0067dda0

struct cDirectPropertyList {
    int GetIntProperty(uint32_t id);        // 0x006a2660
    float GetFloatProperty(uint32_t id);    // 0x006a2710
};
void* CreateVertexFormat(const char* desc, int size, int flags);                // 0x00f672f0 (cdecl)
void UpdateShaderState(uint32_t a, uint32_t b, uint32_t c, uint32_t d);         // 0x00f922b0 (cdecl)
extern cDirectPropertyList* g_AppProperties;    // 0x015fd918
template<class T> struct JobPtr {
    T* mp;
    JobPtr& operator=(T* p)
    {
        T* old = mp;
        if (p != old) {
            if (p)
                p->AddRef();
            mp = p;
            if (old)
                old->Release();
        }
        return *this;
    }
};
struct WeatherPtr {
    cWeatherManager* mp;
    WeatherPtr& operator=(cWeatherManager* p)
    {
        cWeatherManager* old = mp;
        if (p != old) {
            if (p)
                p->mRefBase.AddRef();
            mp = p;
            if (old)
                old->mRefBase.Release();
        }
        return *this;
    }
};
struct SharedPtr {
    AtomicRefCounted* mp;
    SharedPtr& operator=(AtomicRefCounted* p)
    {
        AtomicRefCounted* old = mp;
        if (p != old) {
            if (p)
                p->AddRef();
            mp = p;
            if (old)
                old->Release();
        }
        return *this;
    }
};
extern const char kImpostorRenderTargetName[];  // 0x01490dfc
struct TextureRef {                        // 4-byte intrusive texture handle
    void* mp;
    void Set(void* texture);                // 0x00576650
};
struct cTerrainSphere {
    uint32_t pad0[2];
    uint32_t mHandlerBase;                  // +0x008 (IHandler subobject)
    uint32_t pad0c[(0x18 - 0x0c) / 4];
    uint32_t mImpostorSource18;             // +0x018
    uint32_t mImpostorSource1C;             // +0x01c
    uint32_t mImpostorFlags20;              // +0x020
    uint32_t pad24[(0x2c - 0x24) / 4];
    cTerrainPlanetData* mpPlanet;           // +0x02c
    uint32_t pad30[(0x118 - 0x30) / 4];
    cTerrainSphereQuad* mQuadsA[6];         // +0x118
    cTerrainSphereQuad* mQuadsB[6];         // +0x130
    uint32_t pad148[(0x1d4 - 0x148) / 4];
    int mIntProp;                           // +0x1d4
    float mFloatProp0;                      // +0x1d8
    float mFloatProp1;                      // +0x1dc
    float mFloatProp2;                      // +0x1e0
    uint32_t pad1e4[(0x20c - 0x1e4) / 4];
    cTerrainStateMgr* mpStateMgr;           // +0x20c
    WeatherPtr mpWeather;                   // +0x210
    uint32_t pad214[(0x308 - 0x214) / 4];
    SharedPtr mpShared;                     // +0x308
    uint32_t pad30c[(0x360 - 0x30c) / 4];
    float mFloat360;                        // +0x360
    float mFloat364;                        // +0x364
    uint32_t pad368[(0x434 - 0x368) / 4];
    Vec4 mVecA[6];                          // +0x434
    Vec4 mVecB[6];                          // +0x494
    bool mFlag4F4;                          // +0x4f4
    uint32_t pad4f8[(0x820 - 0x4f8) / 4];
    Vec4 mVecC[6];                          // +0x820
    uint32_t pad880;                        // +0x880
    TextureRef mpImpostorDiffuseTexture;    // +0x884
    TextureRef mpImpostorSpecTexture;       // +0x888
    TextureRef mpImpostorNormalTexture;     // +0x88c
    TextureRef mpImpostorScatterTexture;    // +0x890
    uint32_t pad894;                        // +0x894
    void* mpImpostorRaster;                 // +0x898
    uint32_t mImpostorRectId;               // +0x89c
    JobPtr<cITerrainGenerationStep> mpImpostorJob;   // +0x8a0
    int mImpostorJobState;                  // +0x8a4
    uint32_t mImpostorFace;                 // +0x8a8
    uint32_t pad8ac[(0x8e4 - 0x8ac) / 4];
    cViewer* mpViewer;                      // +0x8e4
    uint32_t pad8e8[(0x924 - 0x8e8) / 4];
    cDecalManagerImpl* mpDecalManager;      // +0x924
    void* mpVertexFormat;                   // +0x928
    uint32_t pad92c[(0xa4c - 0x92c) / 4];
    cQuadBuffersPool* mpQuadPool;           // +0xa4c

    bool Initialize(bool createWeather);
    void UpdateControlMapParams();          // 0x00f99d20
    void InitializeVBInfoArray();           // 0x00f99680
    void InitFace(int face);                // 0x00f9c010
    void InitStatics();                     // 0x00fa0400
    void AddGeometryChangeMessage(int a, int b);    // 0x00fa0560
    void GenerateImpostor(unsigned int face);       // 0x00fa1650
};
void __cdecl EastlDeallocate(void* p);          // 0x00f47380
struct ImpostorRecord110 {
    void* mpData;                               // +0x000
    uint32_t mPad04[3];                         // +0x004
    void* mpInline;                             // +0x010
    uint32_t mPad14[(0x110 - 0x014) / 4];       // +0x014
};
struct Rec20 {
    float w0;                                   // +0x00
    float w1;                                   // +0x04
    float w2;                                   // +0x08
    float w3;                                   // +0x0c
    float w4;                                   // +0x10
    Rec20() {}
    Rec20(const Rec20& other)
    {
        w0 = other.w0;
        w1 = other.w1;
        w2 = other.w2;
        w3 = other.w3;
        w4 = other.w4;
    }
};
void __cdecl CopyUninitialized20(Rec20*& out, Rec20* first, Rec20* last,
                                 Rec20* dest, Rec20* position);                          // 0x00f9f8f0
void __cdecl FillCount20(Rec20* dest, unsigned count, const Rec20* value);               // 0x00f9aee0
void __cdecl CopyBackward20(Rec20* first, Rec20* last, Rec20* dest);                     // 0x00c50ad0
void __cdecl FillRange20(Rec20* first, Rec20* last, const Rec20* value);                 // 0x00f96e70
Rec20* __cdecl Copy20(Rec20* first, Rec20* last, Rec20* dest);                           // 0x00f9b050
struct Rec20Vector {
    Rec20* begin;                               // +0x00
    Rec20* end;                                 // +0x04
    Rec20* cap;                                 // +0x08
    uint32_t mPad0C;                            // +0x0c
    Rec20 mInline;                              // +0x10
    void insert(Rec20* pos, unsigned count, Rec20* value);
};
struct SortRec16 {
    uint32_t w0;                                // +0x00
    uint32_t w1;                                // +0x04
    uint32_t key;                               // +0x08
    uint32_t w3;                                // +0x0c
};
struct SortLess16 {
    uint32_t mPad;
    bool operator()(const SortRec16& a, const SortRec16& b) const
    {
        return a.key < b.key;
    }
};
SortRec16* __cdecl PartitionElem16(SortRec16* first, SortRec16* last, SortRec16 pivot,
                                   SortLess16 compare);          // 0x00fa0670
void __cdecl SortElem16Pass(SortRec16* first, SortRec16* last, SortRec16* end,
                            SortLess16 compare);                 // 0x00fa06e0
template <typename It, typename Compare>
inline It MedianElem16(It a, It b, It c, Compare compare)
{
    if (compare(*a, *b)) {
        if (compare(*b, *c))
            return b;
        if (compare(*a, *c))
            return c;
        return a;
    }
    if (compare(*a, *c))
        return a;
    if (compare(*b, *c))
        return c;
    return b;
}
// ---- items of slice s00fa0f90 end

// ---- items of slice s00fa3860 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kPi;                // 0x015b1190
extern const float kLerpBase[3];       // 0x015b11ac..0x015b11b4
extern char gSpecialMode;                 // 0x01654c10
extern int g_lightIdCounter;                       // 0x15b14e4
extern unsigned g_rasterStageDirty;               // 0x16fa3a8
extern void** g_ppRaster16c9f58;                  // 0x16c9f58
extern int g_rasterCur16f9674;                    // 0x16f9674
extern void* g_rasterTable16f9650[17];            // 0x16f9650
extern unsigned g_16f9554;                        // 0x16f9554
extern int g_16fa1c4;                             // 0x16fa1c4
extern int g_16fa1c8;                             // 0x16fa1c8
extern int g_16fa1d4;                             // 0x16fa1d4
extern int g_16fa1d8;                             // 0x16fa1d8
extern int g_16fa1dc;                             // 0x16fa1dc
extern unsigned g_16fa3a0;                        // 0x16fa3a0
extern int g_16f9480;                             // 0x16f9480
extern int g_15b1200;                             // 0x15b1200
extern int g_15b1208;                             // 0x15b1208
extern int g_15b1210;                             // 0x15b1210
struct Vector3 { float x, y, z; };
struct Vector2 { float x, y; };
struct ResKey { uint32_t instance, type, group; };
struct Transform {
    int16_t mnFlags;
    int16_t mnTransformCount;
    float mOffset[3];
    float mfScale;
    float mRotation[9];

    Transform(const Transform& src);   // 0x0040ce80
    void RotateY(float angle);         // 0x004099b0
    __forceinline void ScaleBy(float s)
    {
        mfScale = mfScale * s;
        mnFlags |= 1;
        mnTransformCount += 1;
    }
};
struct Property {
    char pad0[0x12];
    uint16_t mnType;                   // +0x12
    const bool* GetBool();             // 0x0041e920
    const float* GetFloat();           // 0x0041ea70
};
class cPropertyList {
public:
    virtual int AddRef();
    virtual int Release();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual bool HasProperty(uint32_t id);                       // +0x1c
    virtual bool GetPropertyAlt(uint32_t id, Property*& result); // +0x20
    virtual bool GetProperty(uint32_t id, Property*& result);    // +0x24
};
bool GetPropertyAsKey(cPropertyList* list, uint32_t id, ResKey* value);           // 0x006a1250
bool GetPropertyAsVector2(cPropertyList* list, uint32_t id, Vector2* value);      // 0x006a10c0
bool GetPropertyAsVector3(cPropertyList* list, uint32_t id, Vector3* value);      // 0x006a1110
bool GetPropertyAsColorRGB(cPropertyList* list, uint32_t id, float* rgb);         // 0x006a11b0
bool GetFloatProperty(cPropertyList* list, uint32_t id, float* value);            // 0x0040cf10
static __forceinline void ReleaseRef_s00fa_3860(void* o)
{
    volatile long* c = (volatile long*)((char*)o + 8);
    _InterlockedExchangeAdd(c, -1);
    long n = _InterlockedExchangeAdd(c, 0);
    if (n < 1) _InterlockedExchangeAdd(c, 1);
    else _InterlockedExchangeAdd(c, 0);
}
static __forceinline void ReleaseRef(void* o)
{
    volatile long* c = (volatile long*)((char*)o + 8);
    _InterlockedExchangeAdd(c, -1);
    long n = _InterlockedExchangeAdd(c, 0);
    if (n < 1) _InterlockedExchangeAdd(c, 1);
    else _InterlockedExchangeAdd(c, 0);
}
static __forceinline void AddRef(void* o)
{
    _InterlockedExchangeAdd((volatile long*)((char*)o + 8), 1);
}
struct cImage;
struct cImgRes {
    cImage* mpImage;
    void GetImageResource(void* resource);   // 0x00576650
};
struct IApp {
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
    virtual void* GetCurrentMode();   // +0x38
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
    virtual void* v50();              // +0x50
};
IApp* App();                          // 0x0067dd10
struct IResourceManager {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void* GetResource(ResKey key, int type);   // +0x1c
};
IResourceManager* GetResourceManager();   // 0x0067dd60
struct cTerrainSphereDecal {
    char pad0[0x40];
    float r, g, b, a;                     // +0x40 color / alpha
    bool GetBBoxForFace(int face, float* box);   // 0x00fad140
};
struct LightInfo {
    char pad[0x59c];
    float color[3];                       // +0x59c
};
template<class T> struct SPVector {
    T* begin;                              // +0x00
    T* end;                                // +0x04
    T* cap;                                // +0x08
    void DoInsertKey4(T* pos, const T& val);   // 0x00b96600
};
struct Entry8 { void* obj; void* pad; };
struct SphereLightGroup {
    void* begin;                           // +0x00
    void* end;                             // +0x04
    void* cap;                             // +0x08
    int   pad0;                            // +0x0c
    int   pad1;                            // +0x10
};
struct SphereGroupEntry { char pad0[0xb8]; unsigned mFlags; };
struct Rec20_s00fa_3860 { unsigned w0, w1, w2, w3, w4; };
struct cTerrainSphere_s00fa_3860 {
    char pad0[0x20c];
    LightInfo* mpLight;                   // +0x20c
    char pad210[0x08];                    // +0x210
    SphereLightGroup mGroups[4];          // +0x218 (4 * 0x14)
    char pad268[0x50];                    // +0x268
    SPVector<unsigned> mVec2b8;           // +0x2b8 (free index list)
    char pad2c4[0x08];                    // +0x2c4
    int* mCur2cc;                         // +0x2cc
    int* mCur2d0;                         // +0x2d0
    char pad2d4[0x0c];                    // +0x2d4
    SPVector<unsigned> mVec2e0;           // +0x2e0 (owned object pointers)
    char pad2ec[0x08];                    // +0x2ec
    SPVector<unsigned> mVec2f4;           // +0x2f4 (sphere-light pointers)
    char pad300[0x484];                   // +0x300
    char* mRecBase;                       // +0x784 (0xac-byte terrain records)
    char* mRecEnd;                        // +0x788
    char pad78c[0x124];                   // +0x78c
    SPVector<Entry8> mVec8b0;             // +0x8b0
    char pad8bc[0x08];                    // +0x8bc
    SPVector<Entry8> mVec8c4;             // +0x8c4
    char pad8d0[0x0c];                    // +0x8d0
    void* mpFaceQuads;                    // +0x8dc

    void ApplyModelFootprint(const Transform* modelXform, cPropertyList* props, void* a3, float* faceBoxes, bool bDecal);  // 0x00fa3c10 (cTerrainSphere::ApplyModelFootprint)
    void DrawFootprint(Transform* xform, float z, cImage* img, const Vector2* off, bool flag, float* faceBoxes, void* a3);   // 0x00f9d5c0
    void DrawResource(Transform* xform, float z, void* res, void* a3);                                                // 0x00fa01e0
    cTerrainSphereDecal* CreateDecal(void* res, Transform* xform, float z, int layer);                                // 0x00fa2920

    void FUN_00fa3b30();                          // 0x00fa3b30
    int  FUN_00fa3ba0();                          // 0x00fa3ba0
    void FUN_00fa42e0(void* key);                 // 0x00fa42e0
    void FUN_00fa4360(void* key);                 // 0x00fa4360
    void Relevel(void* a2, char flag);            // 0x00fa43e0
    void FUN_00fa44d0(int key);                   // 0x00fa44d0
    int  FUN_00fa45c0(Vector3* p2, Vector3* p3, float p4);   // 0x00fa45c0
    void FUN_00fa4660(int key);                   // 0x00fa4660
    void DrawLayerRTT(void* viewer, void* a3);    // 0x00fa3860
    void FUN_00fa29b0(int key);                   // 0x00fa29b0
    void FUN_00f9e3a0();                          // 0x00f9e3a0
    void FUN_00f998f0();                          // 0x00f998f0
    void DrawAtmoQuads(void* viewer, void* a3);   // 0x00f98530
    void RefractionMapRender(void* viewer, void* a3);   // 0x00fa2a20
};
struct cSPColorRGBA_s00fa_3860 { float r, g, b, a; };
struct cViewer_s00fa_3860 {
    void SetClearColor(const cSPColorRGBA_s00fa_3860& c);   // 0x007c3c20
    void Clear(unsigned mask);                   // 0x007c3c50
    bool Copy(cViewer_s00fa_3860* src, bool a, bool b);     // 0x007c50b0
    void SetRaster(int* raster, bool a);         // 0x007c4be0
    void SetTarget(void* raster);                // 0x007c3cb0
};
struct cDirectPropertyList_s00fa_3860 {
    bool GetDescription(uint32_t id) const;      // 0x006a25a0
};
struct cTerrainSphereLight {
    int   mId;             // +0x00
    Vector3 mVec1;         // +0x04
    Vector3 mVec2;         // +0x10
    float mScalar;         // +0x1c
    unsigned char mFlag20; // +0x20
};
struct SphereChild {
    int   mKey;            // +0x00
    char  pad004[0x1ac];   // +0x04
    int   mField1b0;       // +0x1b0
    int   mField1b4;       // +0x1b4
    void* mField1b8;       // +0x1b8
    void FUN_00fa23d0(cTerrainSphereLight* light);   // 0x00fa23d0
    void FUN_00f9f1a0();                             // 0x00f9f1a0
};
struct ReleasedObj {
    virtual void v00();
    virtual void v04();
};
struct PropertyMgr {
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
    virtual bool v2c(void* a, void* b, void** out);
};
struct DelMgr {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual void v10();
    virtual void v14(void* a, void* b);
};
struct TerrainRec {
    char   pad000[0x38];   // +0x00
    float  mFaceBoxes[0x18];   // +0x38
    void*  mField98;       // +0x98
    void*  mFieldA0;       // +0xa0
    unsigned mFlags;       // +0xa4
    char   pad0a8[4];      // +0xa8
};
struct VecRec20 {
    Rec20_s00fa_3860* begin;          // +0x00
    Rec20_s00fa_3860* end;            // +0x04
    Rec20_s00fa_3860* cap;            // +0x08
    void FUN_00fa1840(Rec20_s00fa_3860* pos, unsigned n, void* local);   // 0x00fa1840
    void resize(unsigned n);
};
void* PropertyManager_s00fa_3860();                           // 0x0067de30
void* FUN_0067dda0();                              // 0x0067dda0
void* AllocNamed(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void  FreeNamed(void* p);                          // 0x00f47380
void  FUN_00f9ae80(void* a, void* b, void* c);     // 0x00f9ae80
Rec20_s00fa_3860* copy_Rec20(const Rec20_s00fa_3860* a, const Rec20_s00fa_3860* b, Rec20_s00fa_3860* c);   // 0x00951bf0
struct TerrainVt {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual void* v10();              // +0x10
};
struct ModeVt {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void* v1c();              // +0x1c
};
struct FaceQuadVt {
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
    virtual void* vA0();              // +0xa0
};
struct FaceDrawVt {
virtual void v00();
virtual void v04();
virtual void v08();
    virtual void v0c(int a, int b, void** c, void* d);   // +0x0c
};
struct MgrVt {
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
    virtual void v60(int* a, int* b, int* c, void* d);   // +0x60
};
struct SphereData {
    char  pad0[0x42c];
    float mColor[3];                  // +0x42c
};
struct RasterView {
    char pad0[0x12];
    char mLayerIndex;                 // +0x12
};
extern cDirectPropertyList_s00fa_3860* gAppProperties;       // 0x15fd918
extern cViewer_s00fa_3860 g_viewer16c9f60;                   // 0x16c9f60
extern cViewer_s00fa_3860 g_viewer16ca0d8;                   // 0x16ca0d8
void* FUN_0067ddb0();                             // 0x0067ddb0
void  D3D9Sync();                                 // 0x011f21a0
// ---- items of slice s00fa3860 end

// ---- items of slice s00fa5610 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_ZeroX;                                   // 0x016c9e8c
extern float g_ZeroY;                                   // 0x016c9e90
extern float g_ZeroZ;                                   // 0x016c9e94
extern float g_Ident[9];                                // 0x016c9f24 (3x3 block to 0x016c9f44)
extern uint32_t* g_16f6ee0;                                      // 0x016f6ee0 (pointer to state flags)
extern void* g_16c9e68;                                          // 0x016c9e68
extern void* g_16c9f5c;                                          // 0x016c9f5c
extern bool g_15b14e8;                                           // 0x015b14e8
struct Vec3f { float x, y, z; };
struct cQuad {
    char pad0[8];
    cQuad* children[4];            // +8
    char pad1[0x34 - 0x18];
    Vec3f centre;                  // +0x34
    char pad2[0x64 - 0x40];
    float lodKey;                  // +0x64
    char pad3[0x70 - 0x68];
    Vec3f sphereCentre;            // +0x70
    float sphereRadius;            // +0x7c
    void Refine();                 // 0x00fb77b0
    void MarkChild();              // 0x00fb5090
};
struct QItem { cQuad* quad; uint32_t flags; };
struct QContainer { cQuad* quad; float lod; uint32_t key; uint32_t zero; };
struct QuadStack {                 // global at 0x016ca24c
    QItem* mpBegin;
    QItem* mpEnd;
    QItem* mpCapacity;
    void DoInsertValue(QItem* pos, const QItem& v);     // 0x00b534c0 (ret 8)
    void push_back(const QItem& v)
    {
        if (mpEnd < mpCapacity) {
            QItem* p = mpEnd++;
            ::new ((void*)p) QItem(v);
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};
extern QuadStack g_QuadStack;   // 0x016ca24c
struct QCVector {                  // eastl::vector<QContainer, sp_vector_allocator>, 0x14 bytes
    QContainer* mpBegin;
    QContainer* mpEnd;
    QContainer* mpCapacity;
    uint32_t alloc[2];
    void DoInsertValue(QContainer* pos, const QContainer& v);   // 0x00c19d10 (ret 8)
    void push_back(const QContainer& v)
    {
        if (mpEnd < mpCapacity) {
            QContainer* p = mpEnd++;
            ::new ((void*)p) QContainer(v);
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
    void clear()
    {
        QContainer* first = mpBegin;
        QContainer* last = mpEnd;
        CopyRange(last, last, first);
        mpEnd += (first - last);
    }
    static void* CopyRange(QContainer* a, QContainer* b, QContainer* c);   // 0x00705250 (cdecl)
};
struct Property_s00fa_5610 {
    char pad[0x12];
    short type;
    float* GetFloat();             // 0x0041ea70
};
struct cDirectPropertyList_s00fa_5610 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool GetProperty(uint32_t id, Property_s00fa_5610** out);       // +0x24
    bool GetDescription(uint32_t id);                            // 0x006a25a0 (ret 4)
    float GetFloatProperty(uint32_t id);                         // 0x006a2710 (ret 4)
};
extern cDirectPropertyList_s00fa_5610* sAppProperties;                      // 0x015fd918
void FUN_00f96b40();                                             // 0x00f96b40
void FUN_00f96c60();                                             // 0x00f96c60
void FUN_00f9e280();                                             // 0x00f9e280
void FUN_00f9e350();                                             // 0x00f9e350
struct cFrustumCull {
    uint32_t buf[0x3b];
    cFrustumCull(void* camera);                                  // 0x006ffe00 (ret 4)
    void SetNear(float f);                                       // 0x006ffa80 (ret 4)
    uint32_t FrustumTestSphere(const Vec3f* centre, const float* radius, uint32_t flags);   // 0x00700120
};
struct SPTransform {
    short a, b;
    Vec3f pos;
    float scale;
    float rot[9];
    SPTransform() : a(0), b(0), scale(1.0f)
    {
        pos.x = g_ZeroX; pos.y = g_ZeroY; pos.z = g_ZeroZ;
        for (int i = 0; i < 9; ++i) rot[i] = g_Ident[i];
    }
};
struct cViewer_s00fa_5610 {  // 0x007c40f0 / 0x007c3c50
    void GetTransform(SPTransform* out);
    void Clear(unsigned mask);
};
struct cTerrainInfo { char pad[0x34]; float radius; };
bool QuadDetailTest(cQuad* q, void* terrain, float* outDist);    // 0x00f97960 (stdcall, ret 0xc)
void SortQuads(QContainer* first, QContainer* last, bool flag);  // 0x00fa2660 (cdecl)
struct RefObj {
    virtual void AddRef();              // +0x00
    virtual void Release();             // +0x04
};
struct ResRef {
    uint32_t mVtbl;                     // +0x00
    uint32_t mPad;                      // +0x04
    volatile long mRefCount;            // +0x08
    void AddRef() { _InterlockedIncrement(&mRefCount); }
    void Release()
    {
        _InterlockedExchangeAdd(&mRefCount, -1);
        long n = _InterlockedExchangeAdd(&mRefCount, 0);
        if (n < 1)
            _InterlockedExchangeAdd(&mRefCount, 1);
        else
            _InterlockedExchangeAdd(&mRefCount, 0);
    }
};
bool GetPropertyAsKey(cDirectPropertyList_s00fa_5610* list, uint32_t id, ResKey* out);   // 0x006a1250
bool GetPropertyAsVector3(cDirectPropertyList_s00fa_5610* list, uint32_t id, Vec3f* out); // 0x006a1110
PropertyMgr* PropertyManager_s00fa_5610();                        // 0x0067de30
struct IResMgr {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void* v1c(ResKey key, int d);               // +0x1c
};
IResMgr* GetResourceManager_s00fa_5610();                          // 0x0067dd60
struct RefVec {
    ResRef** mpBegin;
    ResRef** mpEnd;
    ResRef** mpCapacity;
    uint32_t mAlloc[2];
    void Add(ResRef** value);                                 // 0x00420660 (ret 4)
    void DoInsertValue(ResRef** pos, const ResRef** value);   // 0x00425a80 (ret 8)
    __forceinline void push_back(ResRef* v)
    {
        ResRef** e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e) {
                *e = v;
                if (v)
                    v->AddRef();
            }
        } else {
            DoInsertValue(e, (const ResRef**)&v);
        }
    }
};
struct ObjSlot { ResRef* mp; void Release(); };
struct ModelKeyVec {
    ResKey* mpBegin;
    ResKey* mpEnd;
    ResKey* mpCapacity;
    uint32_t mAlloc[2];
    void DoCopy(ResKey* last, ResKey* first);         // 0x0050f740 (ret 8)
};
struct PtrRefVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    uint32_t mAlloc[2];
    void DoDestroyValues(void** first, void** last);   // 0x5f3680 (ret 8)
};
void* DoXformCopy(void* a, void* b, void* c);       // 0x00f339d0 (cdecl, 3 args)
void* DoPtrCopyRefs(void* a, void* b, void* c);     // 0x005f4e10 (cdecl, 3 args)
struct Entry8_s00fa_5610 { RefObj* mObj; void* mParam; };
struct Entry8Vec {
    Entry8_s00fa_5610* mpBegin;
    Entry8_s00fa_5610* mpEnd;
    Entry8_s00fa_5610* mpCapacity;
    void Add(Entry8_s00fa_5610* pos, const Entry8_s00fa_5610* value);       // 0x00fa2440 (ret 8)
    void push_back(const Entry8_s00fa_5610& v)
    {
        Entry8_s00fa_5610* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e) {
                e->mObj = v.mObj;
                if (e->mObj)
                    e->mObj->AddRef();
                e->mParam = v.mParam;
            }
        } else {
            Add(mpEnd, &v);
        }
    }
};
struct TerrainRec_s00fa_5610 {
    char  pad000[0x38];
    float mFaceBoxes[0x18];           // +0x38
    void* mField98;                   // +0x98
    uint32_t mField9c;                // +0x9c
    void* mFieldA0;                   // +0xa0
    uint32_t mFlags;                  // +0xa4
    char  pad0a8[0x04];
};
class cTerrainSphere_s00fa_5610 {
public:
virtual void vfn0();
virtual void vfn1();
virtual void vfn2();
    virtual cTerrainInfo* GetInfo();                             // +0xc
    void UpdateQuadsPostCamera(void* camera);                    // 0x00fa5610

    char pad0[0x110 - 4];
    bool mStaticRTTValid;            // +0x110
    char pad114[0x118 - 0x111];
    cQuad* faceRoots[6];             // +0x118
    cQuad* atmoRoots[6];             // +0x130
    char pad1[0x190 - 0x148];
    QCVector renderQuads;            // +0x190
    QCVector faceRootArray;          // +0x1a4
    QCVector atmoRootArray;          // +0x1b8
    char pad2[0x1e8 - 0x1cc];
    bool flagA;                      // +0x1e8
    char pad3[0x30c - 0x1e9];
    char decalState[0x20];           // +0x30c (QuadDetailTest terrain state)

    // Offsets touched by the gold7 group; the members between them are padding.
    char pad32c_770[0x770 - 0x32c];  // +0x32c .. +0x76c (raster decal state at +0x32c)
    TerrainRec_s00fa_5610* mRecBase_770;        // +0x770
    TerrainRec_s00fa_5610* mRecEnd_770;         // +0x774
    void* pad778[3];                 // +0x778 .. +0x784
    TerrainRec_s00fa_5610* mRecBase_784;        // +0x784
    TerrainRec_s00fa_5610* mRecEnd_784;         // +0x788
    char pad78c_7ac[0x7ac - 0x78c];
    int mCount_7ac;                  // +0x7ac
    ResKey* mModelKeys;              // +0x7b0 (ModelKeyVec begin..cap here)
    ResKey* mModelKeysEnd;           // +0x7b4
    ResKey* mModelKeysCap;           // +0x7b8
    uint32_t mAlloc7bc[2];           // +0x7bc
    void* mModelXforms;              // +0x7c4 (TransformVec begin..cap here)
    void* mModelXformsEnd;           // +0x7c8
    void* mModelXformsCap;           // +0x7cc
    uint32_t mAlloc7d0[2];           // +0x7d0
    void** mModelPtrs;               // +0x7d8 (PtrRefVec begin..cap here)
    void** mModelPtrsEnd;            // +0x7dc
    void** mModelPtrsCap;            // +0x7e0
    uint32_t mAlloc7e4[2];           // +0x7e4
    char pad7ec_8b0[0x8b0 - 0x7ec];
    Entry8_s00fa_5610* mEntries8b0;             // +0x8b0
    Entry8_s00fa_5610* mEntries8b0End;          // +0x8b4
    Entry8_s00fa_5610* mEntries8b0Cap;          // +0x8b8
    char pad8bc_8c4[0x8c4 - 0x8bc];
    Entry8_s00fa_5610* mEntries8c4;             // +0x8c4
    Entry8_s00fa_5610* mEntries8c4End;          // +0x8c8
    Entry8_s00fa_5610* mEntries8c4Cap;          // +0x8cc
    char pad8d0_8dc[0x8dc - 0x8d0];
    void* mpFaceQuads;               // +0x8dc
    char pad8e0[0x8e4 - 0x8e0];
    cViewer_s00fa_5610* viewer;                 // +0x8e4

    void DrawLayerRTT(void** a1, void* a2, void* a3);         // 0x00fa5cc0
    void ClearModels();                                       // 0x00fa5e40
    void RequestModelFootprint(cDirectPropertyList_s00fa_5610* list, PtrRefVec* out);   // 0x00fa5ee0
    void AddPaintDecalsFromModels(void* param);               // 0x00fa6130
    void AddEntry8b0(RefObj* obj, void* param);               // 0x00fa6320
    void AddEntry8c4(RefObj* obj, void* param);               // 0x00fa63d0

    void ApplyModelFootprint(const void* xform, void* props, void* a3, float* faceBoxes, bool bDecal);   // 0x00fa3c10

    // Fixed-RTT helpers (this-relative, callee cleans the stack arguments).
    void FUN_00fa3860(void* a, void* b);                      // 0x00fa3860
    void FUN_00f9c470(void* a, void* b);                      // 0x00f9c470
    void FUN_00f9df20(void* a, void* b, void* c, void* d);    // 0x00f9df20
    void FUN_00f998f0();                                      // 0x00f998f0
};
// ---- items of slice s00fa5610 end

// ---- items of slice s00fa75f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl operator new(unsigned int size, const char* name, int a, int b, int c, int d);
void* __cdecl AllocEA(unsigned int size, int flags, int a, const char* name, int b, int c, const char* file, int line); // 0xf473d0
void __cdecl FreeArray(void* p);                                                                                         // 0xf47380
struct FVec {            // eastl::vector<float> body (begin/end/capacity)
    float* b;
    float* e;
    float* c;
    void Swap(FVec* other);   // 0xf8f8a0
};
struct ImgBase {
    virtual void Dtor(int del);   // slot 0: scalar deleting destructor
    uint32_t pad[3];
    FVec v;                       // +0x10
    uint32_t pad2[2];
    ImgBase();                    // 0xf8ee70
    void Init(int n);             // 0xf92250
    void Assign(ImgBase* src);    // 0xf88360
    void Finish();                // 0xf918d0
    void Fini();                  // 0xf8f970 (stack-image destructor)
    void CubeEdge(int face, int x, int y, float* data, const float* w, float scale);   // 0xf87d20
};
struct Img : ImgBase {
    Img() {}
    virtual void Dtor(int del);
};
struct Ctx {                      // object at Cls+0x2c
    uint32_t pad0[2];
    Img* A;                       // +0x08  packed u16 source
    Img* B;                       // +0x0c  packed byte source
    Img* out;                     // +0x10  packed output
    uint32_t pad1[7];
    Img* C;                       // +0x24
    Img* D;                       // +0x28
    Img* E;                       // +0x2c
    Img* F;                       // +0x30
};
struct O2 { uint32_t pad[10]; uint8_t* tbl; };          // +0x28
struct O1 { uint32_t pad[0xcb]; O2* o2; };              // +0x32c
struct O210 {
    void Use(Img* h);   // 0xfc42a0
};
struct Cls {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual void v6();  virtual void v7();
    virtual void v8();  virtual void v9();  virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18();
    virtual bool Query(int what);                       // slot 0x4c
    uint32_t pad0[10];
    Ctx* ctx;                                           // +0x2c
    uint32_t pad1[0x77];
    O1* o1;                                             // +0x20c
    O210* o210;                                         // +0x210
    uint32_t pad2[0x4e];
    float f34c, f350, f354, f358, f35c;

    void BuildTerrain(const float* rects);              // @ 0xfa75f0
};
static inline int FloorI(float x) {
    int i = _mm_cvt_ss2si(_mm_set_ss(x));
    if (x < (float)i) --i;
    return i;
}
// ---- items of slice s00fa75f0 end

// ---- items of slice s00fa9d20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memset(void* dst, int c, unsigned int n);
namespace EA {
namespace ResourceMan {
 struct Key_s00fa_9d20 { uint32_t instance, type, group; }; 
}
}
typedef EA::ResourceMan::Key_s00fa_9d20 Key_s00fa_9d20;
struct Allocator { const char* mpName; uint32_t mExtra; };
struct Vector3_s00fa_9d20 {
    float x, y, z;
    Vector3_s00fa_9d20() {}
    Vector3_s00fa_9d20(const Vector3_s00fa_9d20& v) { x = v.x; y = v.y; z = v.z; }
};
struct Matrix3I { Vector3_s00fa_9d20 row0, row1, row2; };
struct cSPTransform_s00fa_9d20 {
    uint16_t mFlags, mModCount;
    float mTx, mTy, mTz, mScale;
    Matrix3I mRot;
};
struct Rect { float l, t, r, b; };
struct Property_s00fa_9d20 {
    void* mpData;
    uint32_t pad04[3];
    uint16_t mnFlags;                       // +0x10
    uint16_t mnType;                        // +0x12
    const void* GetData() const { return (mnFlags & 0x30) ? mpData : (const void*)this; }
};
struct PropList {
    virtual void AddRef();                  // +0
    virtual void Release();                 // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property_s00fa_9d20*& out);   // +0x24
};
struct PropMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, PropList** out);   // +0x2c
};
struct PropListRef {                        // intrusive ref holder
    PropList* p;
    PropListRef() : p(0) {}
    ~PropListRef() { if (p) p->Release(); }
    PropList** AsPP() { if (p) { PropList* o = p; p = 0; o->Release(); } return &p; }
};
PropMgr* PropertyManager();                                                 // 0x0067de30
bool GetPropertyAsVector3(PropList* l, uint32_t id, Vector3_s00fa_9d20& out);          // 0x006a1110
bool GetPropertyAsVector2(PropList* l, uint32_t id, Vector2& out);          // 0x006a10c0
struct AppProperties { bool GetDescription(uint32_t id); };                  // 0x006a25a0
extern AppProperties* sAppProperties_s00fa_9d20;                                        // 0x015fd918
void __cdecl FreeBlock(void* p);                                             // 0x00f47380 (operator_delete__)
uint32_t __cdecl MakeRelevelExtra(const cSPTransform_s00fa_9d20* t, const Key_s00fa_9d20* k);     // 0x00f96390
struct cRelevel {
    cSPTransform_s00fa_9d20 mTransform;                // +0x00
    Rect mBounds[6];                        // +0x38
    Key_s00fa_9d20 mKey;                               // +0x98
    uint32_t mFlagsAndBits;                 // +0xa4
    uint32_t mExtra;                        // +0xa8
    cRelevel() {}
    __forceinline cRelevel(const cSPTransform_s00fa_9d20& t, const Key_s00fa_9d20& k)
    {
        mTransform.mFlags = t.mFlags; mTransform.mModCount = t.mModCount;
        mTransform.mTx = t.mTx; mTransform.mTy = t.mTy; mTransform.mTz = t.mTz; mTransform.mScale = t.mScale;
        mTransform.mRot.row0 = Vector3_s00fa_9d20(t.mRot.row0);
        mTransform.mRot.row1 = Vector3_s00fa_9d20(t.mRot.row1);
        mTransform.mRot.row2 = Vector3_s00fa_9d20(t.mRot.row2);
        mKey = k;
        mFlagsAndBits = 0;
        mExtra = MakeRelevelExtra(&t, &k);
        memset(mBounds, 0, sizeof(mBounds));
    }
    cRelevel(const cRelevel& o);                                                // 0x00f9b1e0
    cRelevel(const Key_s00fa_9d20& k, const cSPTransform_s00fa_9d20& t, int bFlag);                  // 0x00f9b2b0
};
cRelevel* __cdecl CopyRelevels(cRelevel* first, cRelevel* last, cRelevel* dest);   // 0x00f9f770
struct RelevelVector {
    cRelevel* mBegin; cRelevel* mEnd; cRelevel* mCap; Allocator mAlloc;
    void DoInsertValue(cRelevel* pos, const cRelevel& v);                      // 0x00fa47b0
    __forceinline void push_back(const cRelevel& v)
    {
        if (mEnd < mCap) ::new (mEnd++) cRelevel(v);
        else DoInsertValue(mEnd, v);
    }
    __forceinline void clear()
    {
        cRelevel* first = mBegin;
        cRelevel* last = mEnd;
        CopyRelevels(last, mEnd, first);
        mEnd -= (last - first);
    }
};
struct KeyVector {
    Key_s00fa_9d20* mBegin; Key_s00fa_9d20* mEnd; Key_s00fa_9d20* mCap; Allocator mAlloc;
    KeyVector() : mBegin(0), mEnd(0), mCap(0) {}
    Key_s00fa_9d20* erase(Key_s00fa_9d20* first, Key_s00fa_9d20* last);                                          // 0x0050f740
    ~KeyVector() { if (mBegin && ((int*)mBegin)[-1]) FreeBlock(mBegin); }
};
struct XformVector {
    cSPTransform_s00fa_9d20* mBegin; cSPTransform_s00fa_9d20* mEnd; cSPTransform_s00fa_9d20* mCap; Allocator mAlloc;
    XformVector() : mBegin(0), mEnd(0), mCap(0) {}
    ~XformVector() { if (mBegin && ((int*)mBegin)[-1]) FreeBlock(mBegin); }
};
void __cdecl ReadKeyArray(PropList* p, uint32_t id, int type, KeyVector* dst);           // 0x00f34d40
void __cdecl ReadTransformArray(PropList* p, uint32_t id, int type, XformVector* dst);   // 0x00fa9040
struct cTerrainStateMgr_s00fa_9d20 {
    bool HasWaterSettings();                                // 0x00fb89f0
    void SetWaterSettings(float a, float b, int c);         // 0x00fbddb0 (ret 0xc)
    void SetTileRange(float a, float b);                    // 0x00fbd880 (ret 8)
    void SetScaleA(uint32_t v);                             // 0x00fbaf10
    void SetScaleB(uint32_t v);                             // 0x00fbaf50
    void SetVec2(Vector2* v);                               // 0x00fb7bd0
    void UpdateFromDefinition(PropList* def);               // 0x00fbc130
};
struct cTerrainMapSet { void SetValue(float v); };          // 0x00963760
struct cTerrainSphere_s00fa_9d20 {
    virtual void vfn0();
    char pad04[0x18 - 4];
    Key_s00fa_9d20 mKey;                               // +0x18
    char pad24[4];
    PropList* mpDefinition;                 // +0x28
    cTerrainMapSet* mpMapSet;               // +0x2c
    char pad30[0x20c - 0x30];
    cTerrainStateMgr_s00fa_9d20* mpStateMgr;           // +0x20c
    char pad210[0x770 - 0x210];
    RelevelVector mRelevelA;                // +0x770
    RelevelVector mRelevelB;                // +0x784
    RelevelVector mRelevelC;                // +0x798
    char pad7ac[0x814 - 0x7ac];
    uint32_t mCamOffsetY;                   // +0x814
    void ClearModels();                     // 0x00fa5e40
    void SetModels();                       // 0x00fa96d0
    void SetDefinition(PropList* def);  // 0x00fa9d20 (cTerrainSphere::SetDefinition)
};
static __forceinline bool GetTyped(PropList* l, uint32_t id, int type, Property_s00fa_9d20*& p)
{
    return l && l->GetProperty(id, p) && p->mnType == type;
}
// ---- items of slice s00fa9d20 end

// ---- items of slice s00faa5c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int gTerrainMapJobFlags;                     // 0x016c9e64
extern void TerrainMapJobCallback();                // 0x00fa9830
extern int   g16c9e7c[3];                                       // 0x016c9e7c
extern float g16c9e8c;                                          // 0x016c9e8c
extern void __cdecl FUN_00fbf570(int arg, float radius, int count);             // 0x00fbf570
#pragma intrinsic(_InterlockedExchange)
namespace EA {
namespace ResourceMan {
 struct Key_s00fa_a5c0 { uint32_t instance, type, group; }; 
}
}
typedef EA::ResourceMan::Key_s00fa_a5c0 Key_s00fa_a5c0;
struct Allocator_s00fa_a5c0 { const char* mpName; };
struct Vector3_s00fa_a5c0 {
    float x, y, z;
    Vector3_s00fa_a5c0() {}
    Vector3_s00fa_a5c0(const Vector3_s00fa_a5c0& v) { x = v.x; y = v.y; z = v.z; }
};
struct Matrix3 {
    Vector3_s00fa_a5c0 row0, row1, row2;
    Matrix3() {}
    Matrix3& Assign(const Matrix3& m);          // 0x0041cb40
};
struct Matrix3I_s00fa_a5c0 { Vector3_s00fa_a5c0 row0, row1, row2; };
struct cSPTransformI {                              // transform as copied by the +0x770/+0x784 loops
    uint16_t mFlags, mModCount;
    float mTx, mTy, mTz, mScale;
    Matrix3I_s00fa_a5c0 mRot;
};
struct cSPTransform_s00fa_a5c0 {
    uint16_t mFlags, mModCount;
    float mTx, mTy, mTz, mScale;
    Matrix3 mRot;
    cSPTransform_s00fa_a5c0() {}
    __forceinline cSPTransform_s00fa_a5c0(const cSPTransform_s00fa_a5c0& o) {
        mFlags = o.mFlags; mModCount = o.mModCount;
        mTx = o.mTx; mTy = o.mTy; mTz = o.mTz; mScale = o.mScale;
        mRot.Assign(o.mRot);
    }
    __forceinline cSPTransform_s00fa_a5c0(const cSPTransformI& o) {
        mFlags = o.mFlags; mModCount = o.mModCount;
        mTx = o.mTx; mTy = o.mTy; mTz = o.mTz; mScale = o.mScale;
        mRot.row0 = Vector3_s00fa_a5c0(o.mRot.row0);
        mRot.row1 = Vector3_s00fa_a5c0(o.mRot.row1);
        mRot.row2 = Vector3_s00fa_a5c0(o.mRot.row2);
    }
};
struct cRelevelI {                                  // same record as cRelevel, other transform flavour
    cSPTransformI mTransform; Rect mBounds[6]; Key_s00fa_a5c0 mKey; uint32_t mFlagsAndBits; uint32_t mExtra;
};
struct cRelevel_s00fa_a5c0 {                                   // 0xac bytes in the retail layout
    cSPTransform_s00fa_a5c0 mTransform;                        // +0x00
    Rect mBounds[6];                                // +0x38
    Key_s00fa_a5c0 mKey;                                       // +0x98
    uint32_t mFlagsAndBits;                         // +0xa4
    uint32_t mExtra;                                // +0xa8
};
struct KeyVector_s00fa_a5c0 {
    Key_s00fa_a5c0* mBegin; Key_s00fa_a5c0* mEnd; Key_s00fa_a5c0* mCap; Allocator_s00fa_a5c0 mAlloc;
    KeyVector_s00fa_a5c0() : mBegin(0), mEnd(0), mCap(0) {}
    void Reserve(int n);                            // 0x0041e4d0 (Vec3Vec_Reserve, 12-byte elements)
    void DoInsertValue(Key_s00fa_a5c0* pos, const Key_s00fa_a5c0& v);     // 0x004e3e10
    Key_s00fa_a5c0* erase(Key_s00fa_a5c0* first, Key_s00fa_a5c0* last);              // 0x0050f740
    __forceinline void push_back(const Key_s00fa_a5c0& v) {
        if (mEnd < mCap) ::new (mEnd++) Key_s00fa_a5c0(v);
        else DoInsertValue(mEnd, v);
    }
    ~KeyVector_s00fa_a5c0() { if (mBegin && ((int*)mBegin)[-1]) FreeBlock(mBegin); }
};
struct XformVector_s00fa_a5c0 {
    cSPTransform_s00fa_a5c0* mBegin; cSPTransform_s00fa_a5c0* mEnd; cSPTransform_s00fa_a5c0* mCap; Allocator_s00fa_a5c0 mAlloc;
    XformVector_s00fa_a5c0() : mBegin(0), mEnd(0), mCap(0) {}
    void Reserve(int n);                            // 0x00b04c50
    void DoInsertValue(cSPTransform_s00fa_a5c0* pos, const cSPTransform_s00fa_a5c0& v);   // 0x00423960
    void DoInsertValue(cSPTransform_s00fa_a5c0* pos, const cSPTransformI& v);  // same function; the record is passed by address
    template <class U> __forceinline void push_back(const U& v) {
        if (mEnd < mCap) ::new (mEnd++) cSPTransform_s00fa_a5c0(v);
        else DoInsertValue(mEnd, v);
    }
    void erase(cSPTransform_s00fa_a5c0* first, cSPTransform_s00fa_a5c0* last) { mEnd = mEnd - (last - first); }
    ~XformVector_s00fa_a5c0() { if (mBegin && ((int*)mBegin)[-1]) FreeBlock(mBegin); }
};
struct Variant_s00fa_a5c0 {
    uint32_t data[4]; uint16_t flags; uint16_t type;
    Variant_s00fa_a5c0() { flags = 0; type = 0; }
    void Set(int a, int b, void* ptr, int elemSize, int count);     // 0x0093dd80
    void Destruct(int);                                             // 0x0093db80
    ~Variant_s00fa_a5c0() { if (flags & 4) Destruct(0); }
};
struct IConfigSink {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void SetProperty(uint32_t id, Variant_s00fa_a5c0* v);              // +0x14
};
template <class T> struct RecVec { T* mBegin; T* mEnd; T* mCap; Allocator_s00fa_a5c0 mAlloc;
    int size() const { return mEnd - mBegin; } };
struct cTerrainSphereVBase {
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
    virtual bool v4c(int level);                                // +0x4c
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
    virtual void v80();                                         // +0x80
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
virtual void vc4();
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
    virtual bool vd8();                                         // +0xd8
};
struct TerrainConfig_s00fa_a5c0;
struct cTerrainSphereQuad_s00fa_a5c0;
struct cTerrainSphereRegion;
struct cJob_s00fa_a5c0;
struct cTerrainSphere_s00fa_a5c0 : cTerrainSphereVBase {
    char pad00[0x24];                           // +0x00 (vftable pointer)
    IConfigSink* mSink;                         // +0x28
    TerrainConfig_s00fa_a5c0* mConfig;                     // +0x2c
    char pad30[0xfc - 0x30];
    int mFieldFC;                               // +0xfc
    char pad100[0x110 - 0x100];
    uint8_t mFlag110;                           // +0x110  "outside the cull range"
    uint8_t mFlag111;                           // +0x111
    char pad112[0x114 - 0x112];
    int mCounter114;                            // +0x114
    cTerrainSphereQuad_s00fa_a5c0* mQuads[6];              // +0x118
    char pad130[0x1d0 - 0x130];
    int mField1d0;                              // +0x1d0
    char pad1d4[0x20c - 0x1d4];
    int mField20c;                              // +0x20c
    cTerrainSphereRegion* mField210;            // +0x210
    char pad214[0x30c - 0x214];
    float mCenterX;                             // +0x30c
    float mCenterY;                             // +0x310
    float mCenterZ;                             // +0x314
    char pad318[0x33d - 0x318];
    uint8_t mFlag33d;                           // +0x33d
    char pad33e[0x360 - 0x33e];
    float mField360;                            // +0x360
    float mField364;                            // +0x364
    char pad368[1];
    uint8_t mFlag369;                           // +0x369
    char pad36a[2];
    int mField36c;                              // +0x36c
    uint8_t mFlag370;                           // +0x370
    char pad371[3];
    float mRects[6 * 6 * 4];                    // +0x374  per-level quad rects, 4 floats each
    char pad5b4[0x770 - 0x5b4];
    RecVec<cRelevelI> mRelevelA;                 // +0x770
    char pad780[4];
    RecVec<cRelevelI> mRelevelB;                 // +0x784
    char pad794[4];
    RecVec<cRelevel_s00fa_a5c0> mRelevelC;                 // +0x798
    char pad7a8[0x81c - 0x7a8];
    cJob_s00fa_a5c0* mJob;                                 // +0x81c
    char pad820[0x828 - 0x820];
    float mRegions[6][4];                       // +0x828  region of each of the 6 quads
    char pad888[0xa48 - 0x888];
    int mFieldA48;                              // +0xa48  countdown
    void SetModels();                           // 0x00fa96d0
    void SaveModifications();  // 0x00faa5c0 (cTerrainSphere::SaveModifications)
    void AddToEffectsSystem();                  // 0x00f977c0
    void UpdateQuadsPostCamera(int arg);        // 0x00fa5610
    void UpdatePostCamera(int arg1, int arg2);  // 0x00faad80
    void FUN_00f9b8c0(int* a, int* b, int flag, int zero, float radius);   // 0x00f9b8c0
    void FUN_00f96370();                        // 0x00f96370
    void FUN_00f96f90();                        // 0x00f96f90
    void FUN_00f9ba40(int arg);                 // 0x00f9ba40
};
template <class R> static __forceinline void AppendRelevels(KeyVector_s00fa_a5c0& keys, XformVector_s00fa_a5c0& xf, const RecVec<R>& v)
{
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        keys.push_back(v.mBegin[i].mKey);
        xf.push_back(v.mBegin[i].mTransform);
    }
}
struct cJob_s00fa_a5c0 {
    void* mpFunction;                               // +0x00
    void* mpUserData;                               // +0x04
    char  pad08[0x10];
    int   mPriority;                                // +0x18
    void SetObject(void* obj);                      // 0x0068f9b0
    int  Release();                                 // 0x00690120
    int  GetStatus();                               // 0x006909b0
};
struct cJobManager {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
    virtual bool CanRegister(void* owner);          // +0x10
};
cJobManager* GetJobManager();                       // 0x0068f4d0
struct cILayerI {
    virtual void l0();                              // +0x00 (register callback)
    virtual int Release();                          // +0x04
};
struct IEventModifierI {
virtual void e0();
virtual void e1();
virtual void e2();
virtual void e3();
};
struct cTerrainMapJobBase {
    long   mRefCount;                               // +0x08
    cJob_s00fa_a5c0** mpOwner;                                 // +0x0c
    __forceinline cTerrainMapJobBase(cJob_s00fa_a5c0** owner)
    {
        _InterlockedExchange(&mRefCount, 0);
        mpOwner = owner;
    }
};
struct cTerrainMapJobInfo : cILayerI, IEventModifierI, cTerrainMapJobBase {
    int    mFlags;                                  // +0x10
    __forceinline cTerrainMapJobInfo(cJob_s00fa_a5c0** owner) : cTerrainMapJobBase(owner)
    {
        mFlags = gTerrainMapJobFlags;
    }
    virtual void l0();                              // registers the callback
};
void* AllocJobInfo(size_t size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
struct cQuadElem {                                   // 0x110-byte element
    void*    mpBegin;                                // +0x00
    void*    mpEnd;                                  // +0x04
    void*    mpCap;                                  // +0x08
    uint32_t mPad0c;                                 // +0x0c
    void*    mpInline;                               // +0x10
    uint32_t mPad14;                                 // +0x14
    char     mBuf[0x8c];                             // +0x18
    char     mTail[0x110 - 0xa4];                    // +0xa4
    cQuadElem()
    {
        void* p = mBuf;
        mpInline = p;
        mpEnd = p;
        mpBegin = p;
        mpCap = (char*)p + 0x8c;
    }
    ~cQuadElem()
    {
        if (mpBegin && mpBegin != mpInline)
            FreeBlock(mpBegin);
    }
};
struct cQuadVec {
    cQuadElem* mBegin; cQuadElem* mEnd; cQuadElem* mCap;
    void DoInsertValue(cQuadElem* pos, const cQuadElem& v);   // 0x00fab0e0
    void Append();
};
struct TerrainConfig_s00fa_a5c0 {
    char  pad00[0x34];
    float m34;                                  // +0x34  cull radius bias
    float m38;                                  // +0x38  cell scale
    float m3c;                                  // +0x3c  cell size
    float m40;                                  // +0x40  cell size bias
    char  pad44[0x50 - 0x44];
    float m50;                                  // +0x50
    float m54;                                  // +0x54
};
struct cModelManagerNodeVBase;
struct cModelManagerVBase {
virtual void m000();
virtual void m004();
virtual void m008();
virtual void m00c();
virtual void m010();
virtual void m014();
virtual void m018();
    virtual cModelManagerNodeVBase* v1c(int name);              // +0x1c
};
struct cModelManagerNodeVBase {
virtual void n000();
virtual void n004();
virtual void n008();
virtual void n00c();
virtual void n010();
virtual void n014();
virtual void n018();
virtual void n01c();
virtual void n020();
virtual void n024();
virtual void n028();
virtual void n02c();
virtual void n030();
virtual void n034();
virtual void n038();
virtual void n03c();
virtual void n040();
virtual void n044();
virtual void n048();
virtual void n04c();
virtual void n050();
virtual void n054();
virtual void n058();
virtual void n05c();
virtual void n060();
virtual void n064();
virtual void n068();
virtual void n06c();
virtual void n070();
virtual void n074();
virtual void n078();
virtual void n07c();
virtual void n080();
virtual void n084();
virtual void n088();
virtual void n08c();
virtual void n090();
virtual void n094();
virtual void n098();
virtual void n09c();
virtual void n0a0();
virtual void n0a4();
virtual void n0a8();
virtual void n0ac();
virtual void n0b0();
virtual void n0b4();
virtual void n0b8();
virtual void n0bc();
virtual void n0c0();
virtual void n0c4();
virtual void n0c8();
virtual void n0cc();
virtual void n0d0();
virtual void n0d4();
virtual void n0d8();
virtual void n0dc();
virtual void n0e0();
virtual void n0e4();
virtual void n0e8();
virtual void n0ec();
virtual void n0f0();
virtual void n0f4();
virtual void n0f8();
virtual void n0fc();
virtual void n100();
virtual void n104();
virtual void n108();
virtual void n10c();
virtual void n110();
virtual void n114();
virtual void n118();
virtual void n11c();
virtual void n120();
virtual void n124();
virtual void n128();
virtual void n12c();
virtual void n130();
virtual void n134();
virtual void n138();
virtual void n13c();
virtual void n140();
virtual void n144();
virtual void n148();
virtual void n14c();
virtual void n150();
virtual void n154();
virtual void n158();
    virtual void v15c(int a, void* b, float c);                 // +0x15c
};
cModelManagerVBase* ModelManager_s00fa_a5c0();                             // 0x0067dd80
struct cTerrainSphereQuad_s00fa_a5c0 {
    void TraverseSubdivided(int level, const float* rect);      // 0x00fb0d20
    void MarkVerticesDirty(int level, const float* rect);       // 0x00faf140
    void MarkIndicesDirty(int level, const float* rect);        // 0x00faf400
};
struct cTerrainSphereRegion {
    void FUN_00fc7b30(int arg);                                 // 0x00fc7b30
};
// ---- items of slice s00faa5c0 end

// ---- items of slice s00fab2b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPVector2_s00fa_b2b0
{
    float x, y;
    cSPVector2_s00fa_b2b0& operator=(const cSPVector2_s00fa_b2b0& v) { x = v.x; y = v.y; return *this; }
};
struct cSPTexCoord { float u, v; };
struct cSPVector3_s00fa_b2b0
{
    float x, y, z;
    cSPVector3_s00fa_b2b0() {}
    cSPVector3_s00fa_b2b0(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};
struct cCubeMapCoord_s00fa_b2b0 { cSPVector2_s00fa_b2b0 uv; int face; };
namespace SP {
struct cBrushVertex             // 0x1c (dev PDB)
{
    cSPVector3_s00fa_b2b0 mPosition;
    cSPTexCoord mUV;
    float      mIntensity;
    float      mSize;
};
}
namespace SP {
struct cRibbonFaceVertex_s00fa_b2b0        // 0x14 (dev PDB)
{
    cSPVector2_s00fa_b2b0  mPos;
    cSPTexCoord mTC;
    float      mAlpha;
};
}
namespace SP {
struct cRibbonPolyInfo
{
    float mTopV;
    float mLengthV;
    int   mRibbonID;
};
}
namespace SP {
struct cRibbonFacePoly
{
    cRibbonFaceVertex_s00fa_b2b0*  mpBegin;        // +0x00 fixed_vector<cRibbonFaceVertex,7,true>
    cRibbonFaceVertex_s00fa_b2b0*  mpEnd;          // +0x04
    cRibbonFaceVertex_s00fa_b2b0*  mpCapacity;     // +0x08
    uint32_t            mOverflowAllocator; // +0x0c
    cRibbonFaceVertex_s00fa_b2b0*  mpPoolBegin;    // +0x10
    uint32_t            mVecPad;        // +0x14
    cRibbonFaceVertex_s00fa_b2b0   mBuffer[7];     // +0x18
    cRibbonPolyInfo     mInfo;          // +0xa4
    uint32_t            mPad[4];        // +0xb0 bounds (written by ComputeBounds)
    cRibbonFaceVertex_s00fa_b2b0   mPatch[4];      // +0xc0 bilinear patch (written by BuildPatch)

    void resize(int n);                 // fixed_vector::resize, 0x00fa4730
    void ComputeBounds();               // 0x00fafda0 (name guessed)
    void BuildPatch();                  // 0x00faff10 (name guessed)

    cRibbonFaceVertex_s00fa_b2b0& operator[](int i) { return mpBegin[i]; }
};
}
namespace SP {
struct cRibbonPolyList
{
    cRibbonFacePoly* mpBegin;
    cRibbonFacePoly* mpEnd;
    cRibbonFacePoly* mpCapacity;
    uint32_t         mAllocator[2];

    void push_back();                   // 0x00fab230 (default-constructed element)
    cRibbonFacePoly& back() { return *(mpEnd - 1); }
};
}
namespace SP {
void ClipBrushPoly(cBrushVertex* verts, int* numVerts, const cSPVector3_s00fa_b2b0* plane);
}
namespace SP {
extern cSPVector3_s00fa_b2b0 gCubeFacePlanes[6][4];   // 0x016d6fa8: 4 edge planes per cube face
}
namespace SP {
extern uint8_t    gCubeFaceAxes[3][4];     // 0x01490418: {0,1,2}, {2,0,1}, {1,2,0}
}
namespace SP {
static __forceinline cCubeMapCoord_s00fa_b2b0 ToCubeMapCoord(const cSPVector3_s00fa_b2b0& p)
{
    cCubeMapCoord_s00fa_b2b0 c;
    float x = p.x;
    float y = p.y;
    float z = p.z;
    float ax = fabsf(x);
    float ay = fabsf(y);
    float az = fabsf(z);
    if (az >= ax && az >= ay)
    {
        c.uv.x = (x / z + 1.0f) * 0.5f;
        c.uv.y = (y / az + 1.0f) * 0.5f;
        c.face = (z >= 0.0f) ? 0 : 1;
    }
    else if (ay >= ax)
    {
        c.uv.x = (z / y + 1.0f) * 0.5f;
        c.uv.y = (x / ay + 1.0f) * 0.5f;
        c.face = (y >= 0.0f) ? 4 : 5;
    }
    else
    {
        c.uv.x = (y / x + 1.0f) * 0.5f;
        c.uv.y = (z / ax + 1.0f) * 0.5f;
        c.face = (x >= 0.0f) ? 2 : 3;
    }
    return c;
}
}
namespace SP {
static __forceinline cSPVector3_s00fa_b2b0 Normalized(const cSPVector3_s00fa_b2b0& v)
{
    float x = v.x;
    float inv = 1.0f / sqrtf(x * x + v.y * v.y + v.z * v.z);
    return cSPVector3_s00fa_b2b0(inv * x, v.y * inv, inv * v.z);
}
}
// ---- items of slice s00fab2b0 end

// ---- items of slice s00f955f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchangeAdd)
namespace SP {
int*  Sub_67ddd0();                           // 0x0067ddd0
}
namespace SP {
int   Sub_6f24a0(void* a, int b);             // 0x006f24a0
}
namespace SP {
void  Sub_f47380(void* p);                    // 0x00f47380
}
namespace SP {
unsigned Sub_932e50(void* data, int len, unsigned seed); // 0x00932e50
}
namespace SP {
int   Sub_97ef00(void* self);                 // 0x0097ef00
}
namespace SP {
int   Sub_fb7bb0(void* self);                 // 0x00fb7bb0
}
namespace SP {
int   Sub_fb7bc0(void* self);                 // 0x00fb7bc0
}
namespace SP {
extern int   g_16c9f50;      // 0x016c9f50
}
namespace SP {
extern const float K_1div3;  // 0x013ec4d0   (1/255 scaled)
}
namespace SP {
extern const float K_140;    // 0x0140f334
}
class cTerrainOverlay {
public:
    cTerrainOverlay();
    void* dtor(unsigned flags);   // 0x00f962b0
    char  Reset();
    char  Start();
    char  ClearSlot();            // 0x00f964a0
    void  ToggleFlag();           // 0x00f96370

    void* mpVtbl;        // +0x00
    char  mFlag04;       // +0x04
    char  mFlag05;       // +0x05
    uint8_t mPad06[2];   // +0x06
    int   mVal08;        // +0x08
    uint8_t mPad0c[0x88 - 0x0c]; // +0x0c
    void* mpAlloc88;     // +0x88
    int   mVal8c;        // +0x8c
    int   mVal90;        // +0x90
    int   mVal94;        // +0x94
    int   mVal98;        // +0x98
    uint8_t mPad9c[0x36c - 0x9c]; // +0x9c
    int   mVal36c;       // +0x36c
};
struct cTerrainSphere_s00f9_55f0 {
    void RemoveFromEffectsSystem();   // 0x00f96520
};
struct cDynCast {
    void* Cast(unsigned id);          // 0x00f964f0
};
struct cGridTool {
    void* GetExtents(int* a, int* b, int* c);  // 0x00f967d0
};
// ---- items of slice s00f955f0 end

// ---- items of slice s00f977c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_16ca590[4];        // 0x016ca590
extern uint32_t g_16ca5a0;           // 0x016ca5a0  static-init guard
extern uint32_t g_16f65a0;           // 0x016f65a0  active vertex descriptor
extern uint32_t g_16c9e78;           // 0x016c9e78  wanted vertex descriptor
extern uint32_t g_16f9110;           // 0x016f9110  soft-state-dirty flags
extern uint8_t  g_16ca3d4[];         // 0x016ca3d4  terrain-editor rect-id table
extern void*    g_sAppProps;         // 0x015fd918  SP::App::sAppProperties
extern const float  C_1485720;       // 0x01485720 = 1.0f
extern const float  C_1471064;       // 0x01471064 effect scale
extern const float  C_13f9428;       // 0x013f9428 lod epsilon
extern const float  C_15b118c;       // 0x015b118c fov scale
extern const float  C_13ec4b8;       // 0x013ec4b8 1e-08f
extern const float  C_13eb1bc;       // 0x013eb1bc -1.0f
extern "C" int __stdcall QueryPerformanceCounter_imp(long long* out);  // IAT 0x013cc2b8
#undef V
void*  __cdecl FUN_0067ddd0();                       // 0x0067ddd0  SP::EffectsManager
void   __cdecl FUN_00fb9aa0(float a, float b, float c);                 // 0x00fb9aa0
uint32_t* __cdecl FUN_00fb9ad0(uint32_t* out);       // 0x00fb9ad0
float  __cdecl FUN_00fb8a00(void* mapset);           // 0x00fb8a00
float  __fastcall FUN_00fb8a00_fastcall(void* self);  // 0x00fb8a00 (alias: this function calls it with the thiscall-style getter spelling)
uint32_t __cdecl GetTerraformPlanetType(float r);    // 0x00fc1fd0
void   __cdecl FUN_00777ae0(uint32_t shader, const void* data, int zero); // 0x00777ae0
typedef void (__thiscall *tq2)(void*, void*, uint32_t, uint32_t);
typedef void (__thiscall *tq3)(void*, void*, uint32_t, uint32_t, uint32_t);
typedef void (__thiscall *tq4)(void*, uint32_t, uint32_t, int);
void   __cdecl FUN_00fb66d0x();
void   __cdecl FUN_00fb6850x();
void   __cdecl FUN_00fb6cd0x();
void   __cdecl FUN_00fb6e00x();
int    __cdecl rw_VertexDescriptor_AreEqual(const void* a, const void* b); // 0x011f2e70
void   __fastcall rw_VertexDescriptor_SetActive(void* self);             // 0x011f2bc0
void   __fastcall FUN_007c3c10(void* self);           // 0x007c3c10
bool   __fastcall FUN_007c4fd0(void* self);           // 0x007c4fd0
void*  __cdecl FUN_00f48a70();                       // 0x00f48a70  TerrainEditor / Compositor
bool   __cdecl FUN_00f678a0();                       // 0x00f678a0
bool   __cdecl FUN_00fad140(void* decal, int face, float* box);   // 0x00fad140
bool   __cdecl FUN_00fad550(void* decal, int face, uint32_t a);    // 0x00fad550
bool   __cdecl FUN_00f6a960(void* src, const uint32_t* rectId, int face,
                            float l, float t, float r, float b,
                            int a, int c, float one, float one2, void* g);
uint32_t* __cdecl FUN_00700120(void* frustum, const void* a, const void* b, int c);
typedef uint32_t (__fastcall *tFrust)(void* self, void* pad, const void* a, const void* b, int c);
float  __cdecl FUN_00f63e10(float x);                // 0x00f63e10 sqrt helper used by the quad test
bool  __cdecl GetDescription(void* list, uint32_t id);                 // 0x006a25a0
struct cPropertyList_s00f9_77c0 {
    bool GetDescription(uint32_t id);        // 0x006a25a0 __thiscall ret 4
};
struct cViewer_s00f9_77c0 {
    void  SetRaster(const void* a, int b);   // vtable +0x34
    bool  Update();                          // 0x007c3c10 -> bool
};
struct cStopwatch {
    uint32_t m00, m04, m08, m0c, m10, m14;
};
struct cLimitStopwatch : cStopwatch {
    long long mnEndTime;                     // +0x18
    void Construct(int n, bool b);           // 0x93a560
    void SetTimeLimit(uint32_t ms, bool b);  // 0x93a480
};
struct ViewFrame {
    uint32_t m00, m04;
    uint8_t  m08;
    uint8_t  pad09[3];
    uint8_t  m0c, m0d, m0e, m0f;
    uint8_t  pad10[0x30 - 0x10];
    float    m30;                            // +0x30
    float    m34;                            // +0x34
    float    m38;                            // +0x38
    float    m3c;                            // +0x3c
    uint8_t  pad40[0x64 - 0x40];
    float    m64;                            // +0x64 lod result
    float    m68;                            // +0x68 bearing
    uint8_t  pad6c[0x88 - 0x6c];
    float    m88;                            // +0x88
    float    m8c;                            // +0x8c
    uint8_t  pad90[0x1d4 - 0x90];
    int32_t  m1d4;                           // +0x1d4
    uint8_t  pad1d8[0x2f4 - 0x1d8];
    void*    mStreams[14];                   // +0x2f4
};
struct AppHeader {                           // object at [0x15fd918]+0x3c
    uint8_t pad[0x84];
    float m84, m88, m8c;
};
struct PlanetHeader {                        // object at this+0x2c
    uint8_t pad[0x34];
    float m34, m38, m3c;
};
struct StateMgr {
    void FUN_00fb9aa0(float a, float b, float c);            // 0x00fb9aa0 (thiscall)
};
struct QuadEntry {
    void*    mpObj;         // +0x00
    float    mKey;          // +0x04
    uint32_t pad08;
    uint32_t mFlags;        // +0x0c
};
struct cView {
    uint32_t pad0[0x218 / 4];
    struct Block {
        void*    mBegin;                  // +0x00
        void*    mEnd;                    // +0x04
        uint8_t  pad08[0x14 - 8];
    } mBlocks[4];                         // +0x218, stride 0x14
};
struct Raster {
    uint8_t pad0[0xb8];
    uint32_t mB8;
};
#define V(n) virtual void v##n();
struct cTerrainSphere_s00f9_77c0 {
    V(0) V(1) V(2) V(3)
    virtual ViewFrame* GetViewFrame();                       // +0x10 (slot 4)
    virtual cView* GetView();                                // +0x14 (slot 5)

    void AddToEffectsSystem();                               // 0x00f977c0
    bool QuadDetailTest(const ViewFrame* frame, const float* verts, float* outDist);  // 0x00f97960
    bool AreRastersReady();                                  // 0x00f97c30
    void ReleaseRasters();                                   // 0x00f97d00
    bool RenderJobPass(uint32_t arg);                        // 0x00f97e60
    void DrawSkyQuads(uint32_t a, uint32_t b);               // 0x00f97f50
    void RenderWater(uint32_t a, uint32_t b);                // 0x00f98020
    void DrawWaterQuads(uint32_t a, uint32_t b);             // 0x00f98170
    void RenderAtmosphere(uint32_t a, uint32_t b);           // 0x00f981d0
    void DrawAtmoQuads(uint32_t a, uint32_t b);              // 0x00f98530
    bool UpdateAboveRaster(int face, const float* rect, uint32_t a3, uint32_t a4); // 0x00f98290
    void MergeFaceBox(int face, float l, float t, float r, float b);               // 0x00f98620
    uint32_t GetQuadKeyA(int idx);                           // 0x00f98260
    uint32_t GetQuadKeyB(int idx);                           // 0x00f98270
    uint32_t GetQuadKeyC(int idx);                           // 0x00f98280

    uint8_t  pad04[0x08 - 0x04];
    uint32_t m08;                                            // +0x008
    uint8_t  pad0c[0x2c - 0x0c];
    void*    mpPlanet;                                       // +0x02c
    uint8_t  pad30[0xfc - 0x30];
    cViewer_s00f9_77c0* mpRenderJob;                                    // +0x0fc
    uint8_t  pad100[0x108 - 0x100];
    uint8_t  mSingleStep;                                    // +0x108
    uint8_t  pad109[3];
    float    mTimeLimitMs;                                   // +0x10c
    uint8_t  pad110[0x111 - 0x110];
    uint8_t  mFlag111;                                       // +0x111
    uint8_t  pad112[0x148 - 0x112];
    void**   mArr148;                                        // +0x148
    uint8_t  pad14c[0x160 - 0x14c];
    void**   mArr160;                                        // +0x160
    uint8_t  pad164[0x178 - 0x164];
    void**   mArr178;                                        // +0x178
    uint8_t  pad17c[0x190 - 0x17c];
    QuadEntry* mpQuadBegin;                                  // +0x190
    QuadEntry* mpQuadEnd;                                    // +0x194
    uint8_t  pad198[0x1a4 - 0x198];
    QuadEntry* mpQuad2Begin;                                 // +0x1a4
    QuadEntry* mpQuad2End;                                   // +0x1a8
    uint8_t  pad1ac[0x1b8 - 0x1ac];
    QuadEntry* mpQuad3Begin;                                 // +0x1b8
    QuadEntry* mpQuad3End;                                   // +0x1bc
    uint8_t  pad1c0[0x1d4 - 0x1c0];
    int32_t  m1d4;                                           // +0x1d4
    uint8_t  pad1d8[0x20c - 0x1d8];
    void*    mpStateMgr;                                     // +0x20c
    uint8_t  pad210[0x360 - 0x210];
    float    m360;                                           // +0x360
    float    m364;                                           // +0x364
    uint8_t  pad368[0x434 - 0x368];
    float    mFaceBox[6][4];                                 // +0x434
    uint8_t  pad494[0x8e4 - (0x434 + 6 * 16)];
    cViewer_s00f9_77c0* mpViewer;                                       // +0x8e4
    uint8_t  pad8e8[0x92c - 0x8e8];
    uint8_t  mFrustum[0x3c];                                 // +0x92c
};
// ---- items of slice s00f977c0 end

// ---- items of slice s00f9a610 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kOne;        // 0x01485720 == 1.0f
extern const float kTwo;        // 0x01470f1c == 2.0f
extern const float kBig;        // 0x01465544 == 500.0f
extern void* vtbl_01490908;     // 0x01490908
extern void* vtbl_01490904;     // 0x01490904
extern void* vtbl_01490940;     // 0x01490940
extern void* vtbl_0149093c;     // 0x0149093c
extern float g_DAT_16c9e8c;     // 0x016c9e8c
extern float g_DAT_16c9e90;     // 0x016c9e90
extern float g_DAT_16c9e94;     // 0x016c9e94
extern float g_DAT_16c9f24;     // 0x016c9f24
void* __cdecl MemZero(void* p, int value, unsigned int size);       // 0x011e073e (CRT memset thunk)
struct float3 {
    float x, y, z;
};
struct Rect_s00f9_a610 {
    float left, top, right, bottom;
};
struct IRefObj32 {
    virtual void AddRef();      // +0x00
    virtual void Release();     // +0x04
};
struct IRefCounted2 {
    virtual void Destroy(int a);   // +0x00
    int mRefCount;                 // +0x04
};
struct IFaceGrid {
    void FlushRect(void* a, int face, Rect_s00f9_a610* r);   // 0x00f92ff0 (ret 0xc)
};
struct cPlanetData2 {
    uint8_t pad0[8];
    void*      mp08;            // +0x08
    uint8_t pad0c[0x58 - 0x0c];
    IFaceGrid* mp58;            // +0x58
};
struct ElemA {                  // position at +0x04
    int      key;               // +0x00
    float3   pos;               // +0x04
    uint8_t  pad10[0x20 - 0x10];
    uint8_t  flag20;            // +0x20
};
struct ElemB {                  // position at +0x10
    int      key;               // +0x00
    uint8_t  pad04[0x10 - 0x04];
    float3   pos;               // +0x10
    uint8_t  pad1c[0x20 - 0x1c];
    uint8_t  flag20;            // +0x20
};
struct ElemC {                  // scalar at +0x1c
    int      key;               // +0x00
    uint8_t  pad04[0x1c - 0x04];
    float    val;               // +0x1c
    uint8_t  flag20;            // +0x20
};
struct RefPair {
    IRefObj32* p;               // +0x00
    int        x;               // +0x04
};
struct cViewer2 {
    uint8_t pad[0x178];
    uint8_t mX178[0x10];        // +0x178
    float   mF188;              // +0x188
    bool Update();              // 0x007c4fd0
    void Clear(uint32_t f);     // 0x007c3c50
    void Reset();               // 0x007c3c10
};
struct IMaterialMgr {
    virtual void v0();          // +0x00
    uint8_t pad[0x28 - 4];
    virtual void* Get(uint32_t id);   // +0x28
};
IMaterialMgr* __cdecl MaterialManager();                  // 0x0067dd70
bool __cdecl FUN_006ddcc0(int a, int b, void* c, void* d);   // 0x006ddcc0
void __cdecl FUN_006ddd80(int a, void* b, int c, void* d);    // 0x006ddd80
struct cSPTransform_s00f9_a610 {
    uint8_t pad[0x178];
    void BackTransformPoint(float3* p);   // 0x004ff6d0 (ret 4)
};
uint32_t __cdecl ColorRGBAToU32(float* rgba);             // 0x????????
struct cTerrainSphereDecal_s00f9_a610 {
    bool GetBBoxForFace(uint32_t face, float* out);       // 0x???????? 0x00fad140
};
void __cdecl SetShaderParam(int id, void* a, int b);      // 0x00777ae0 (ret 0xc)
void __cdecl SkyStateUpdate(void* self);                  // 0x00f98970
void __cdecl FUN_00f992e0();                              // 0x00f992e0
void* __cdecl GetManager67b();                            // 0x0067dd50
struct Variant {
    int  mTypeId;    // +0x00
    int  mFlags;     // +0x04
    uint8_t pad8[8];
};
void __cdecl Variant_Destruct(Variant* v, int a);         // EA::Variant::Destruct
bool __cdecl SP_GetPropertyAsVector3(void* props, uint32_t id, float* out);  // SP::GetPropertyAsVector3
void __cdecl FUN_006a3570(void* v);                       // 0x006a3570
void __cdecl FUN_00fbd880(float a, float b);              // 0x00fbd880
void __cdecl FUN_00fbaf10(uint32_t a);                    // 0x00fbaf10
void __cdecl FUN_00fbaf50(float a);                       // 0x00fbaf50
struct IPropListC {
    virtual void v0();   // +0x00
    uint8_t pad[0x14 - 4];
    virtual void Set(uint32_t id, Variant* v);   // +0x14
    virtual void Del(uint32_t id);               // +0x18
};
struct vtbl_GmeRefCount { int f; };
extern vtbl_GmeRefCount vtbl_GmeRefCount0;    // 0x013ef094
struct cTerrainSphere141 {
    uint8_t  pad0[0x2c];
    cPlanetData2* mpPlanet;         // +0x2c
    uint8_t  pad30[0x2f4 - 0x30];
    uint8_t* mpArr2f4;              // +0x2f4
    uint8_t* mpArr2f8;              // +0x2f8
    uint8_t  pad2fc[0x308 - 0x2fc];
    int      mF308;                 // +0x308
    uint8_t  pad30c[0x36c - 0x30c];
    int      mFaceBase;             // +0x36c
    uint8_t  pad370[4];
    Rect_s00f9_a610     mRects[24];            // +0x374

    void FUN_00f9a610();                                   // 0x00f9a610
    void FUN_00f9a680(int key, const float3* v);           // 0x00f9a680
    void FUN_00f9a6f0(int key, const float3* v);           // 0x00f9a6f0
    void FUN_00f9a760(int key, float v);                   // 0x00f9a760
    void RenderLightingRegion(void* a, void* b);           // 0x00f9a7c0
    bool FUN_00f9abc0(float* dir);                         // 0x00f9abc0
};
void __cdecl FUN_00f96eb0(int base, int a, int idx, void* p5, void* p6, void* p7, void* p8, void* p9);
struct CGmeRefCount {
    uint32_t      mF0;          // +0x00
    void*         mVtbl4;       // +0x04
    uint8_t       pad8[0x18 - 0x8];
    IRefCounted2* mp18;         // +0x18
    IRefCounted2* mp1c;         // +0x1c
    void* Destroy(uint8_t flags);
    void  Destroy2();
};
struct CGmeRefCount2 {
    void*         mVtbl0;       // +0x00
    void*         mVtbl4;       // +0x04
    uint32_t      mF8;          // +0x08
    float         mFC;          // +0x0c
    float         mF10;         // +0x10
    float         mF14;         // +0x14
    IRefCounted2* mp18;         // +0x18
    IRefCounted2* mp1c;         // +0x1c
    void Construct(float a, float b, float c, IRefCounted2* p5, IRefCounted2* p6);
};
struct Matrix33 { uint8_t pad[0x30]; };
struct cSPTransform2 {
    uint16_t mFlags;            // +0x00
    uint16_t mModCount;         // +0x02
    float    mTrans[3];         // +0x04
    float    mScale;            // +0x10
    Matrix33 mRot;              // +0x14
    uint8_t  pad44[0x98 - 0x44];
    float    mF98;              // +0x98
    float    mF9c;              // +0x9c
    float    mFa0;              // +0xa0
    float    mFa4;              // +0xa4
    float    mFa8;              // +0xa8
    cSPTransform2* Init(const cSPTransform2* src);
    cSPTransform2* CopyFrom(const float* pos, const cSPTransform2* src, bool flag);
};
void __cdecl Matrix3_Assign(Matrix33* dst, float* src);   // 0x0041cb40
void* __cdecl cSPTransformOps_Assign(void* dst, const void* src);  // 0x00537dc0
void* __cdecl FUN_00f96390(void* a, void* b);            // 0x00f96390
struct cSkyThing {
    virtual void v0();
    uint8_t pad[0x94 - 4];
    virtual bool IsVisible(void* mgr);   // +0x94
};
struct cLightingSet {
    cSkyThing* mpVtbl0;         // +0x00
    uint8_t pad[0x6e0 - 4];
    void FUN_00f9b350();
};
struct cLightSet400 {
    uint8_t pad[0x28];
    IPropListC* mpProps;        // +0x28
    uint8_t pad2c[0x814 - 0x2c];
    int     mCount814;          // +0x814
    void FUN_00f9b400(float sel, unsigned int a, unsigned int b);
};
// ---- items of slice s00f9a610 end

// ---- items of slice s00f9b620 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_sAppProperties;      // 0x015fd918
extern float g_fHalf;               // 0x01471064 == 0.5f
extern float g_fColorScale;         // 0x013eecd4 == 1/255
extern uint32_t g_imgIdsA[];        // 0x014904ac
extern uint32_t g_imgIdsB[];        // 0x0149047c
extern uint32_t g_imgIdsC[];        // 0x01490494
extern void* g_imgMgr;              // 0x015b11f0
extern float g_dat15b1194;          // 0x015b1194
extern float g_dat15b1198;          // 0x015b1198
extern float g_dat15b119c;          // 0x015b119c
extern void* g_dat016c9e68;         // 0x016c9e68
extern void* g_dat016c9e40;         // 0x016c9e40
extern int   g_dat016c9e44[];       // 0x016c9e44
extern uint32_t g_colorMap[2];      // 0x015b1218
void*  __cdecl SP_TerrainEditor();                        // 0x00f48a70
void*  __cdecl SP_App();                                  // 0x0067dd10
void*  __cdecl SP_ModelManager();                         // 0x0067dd80
void*  __cdecl SP_EffectsManager();                       // 0x0067ddd0
void*  __cdecl SP_MaterialManager();                      // 0x0067dd70
void*  __cdecl FUN_0067dd60();                            // 0x0067dd60
void*  __cdecl FUN_0067ddc0();                            // 0x0067ddc0
void   __cdecl FUN_006dde30(int a, int b, void* c);       // 0x006dde30
void   __cdecl FUN_006ddef0(void* a);                     // 0x006ddef0
void   __cdecl FUN_00777ae0(int id, void* a, int b);      // 0x00777ae0
void   __cdecl FUN_006b4b60(void* a, void* b, int c, int d); // 0x006b4b60
void*  __cdecl SP_GetSaveArea(uint32_t id);                // 0x006b1f90
void   __cdecl FUN_00f97750(void* self);                  // 0x00f97750
void   __cdecl FUN_00f96c60();                            // 0x00f96c60
void   __stdcall FUN_00f986f0(int i);                     // 0x00f986f0
void   __cdecl rw_D3D9Sync();                             // 0x011f21a0
void   __cdecl FUN_006ddd80(int a, void* b, uint32_t c, void* d); // 0x006ddd80
void*  __cdecl FUN_0067dda0();                             // 0x0067dda0 (RTT manager)
void   __cdecl FUN_00f96920(const uint8_t* data, int w, int h, float u, float v,
                            float* outB, float* outG, float* outR, float* outA); // 0x00f96920
struct TerrainEditor {
    void  Init(void* a);        // 0x00f67a60
    void  Reset();              // 0x00f67da0
    void  SetValue(float v);    // 0x00f67540
    bool  IsEditing();          // 0x00f678a0
};
bool __cdecl GetPropertyAsVector3(void* list, uint32_t id, float* out);  // 0x006a1110
bool __cdecl ListGetDescription(void* list, uint32_t id);                // 0x006a25a0
struct Prop { uint32_t* GetUInt(); };                                    // 0x0041ea00 (__thiscall)
struct Variant_s00f9_b620 {                                                         // 0x14 bytes
    uint32_t m0, m1, m2, m3;    // +0x00
    uint16_t mFlags;            // +0x10
    uint16_t mType;             // +0x12
    void SetInt(void* v);       // 0x00427fd0 (__thiscall)
    void Destruct(int a);       // 0x0093db80 (__thiscall)
};
bool     __cdecl Property_GetBool(void* prop);                           // 0x0041e920
int      __cdecl Property_GetInt(void* prop);                            // 0x0041e990
struct Matrix44 { float m[16]; void Ctor(void* src); };                 // 0x0045dca0 (__thiscall)
void     __cdecl GetImageResource(void* dst, void* src);                 // 0x00576650
struct ImgSlot { void GetImageResource(void* src); };                    // __thiscall form
typedef void  (__thiscall *Tv0)(void*);
typedef void  (__thiscall *Tv1)(void*, int);
typedef void* (__thiscall *Tp0)(void*);
typedef void* (__thiscall *Tp1)(void*, uint32_t);
typedef void* (__thiscall *Tvp)(void*);
typedef void  (__thiscall *Tv1p)(void*, void*);
typedef void  (__thiscall *Tv3)(void*, uint32_t, uint32_t, void*);
#define VTO(p, off) (*(void***)(p))[(off) / 4]
struct cDirectPropertyList_s00f9_b620 {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void Set(uint32_t id, void* v);     // +0x14
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual bool Get(uint32_t id, void* out);   // +0x24
};
struct IResourceMgr {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void* GetModel(uint32_t id);        // +0x1c (ModelManager)
};
struct IEffectMgr {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void* v10();
    virtual void* Get(uint32_t id);             // +0x54
};
struct IImgMgr {
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
    virtual void* v3c(void* a, void* b, int c, int d, int e, int f, int g, int h);  // +0x3c
};
struct cTerrainQuad {
    void BufferDrawRibbonGeometry(void* a);     // 0x00fb0100
};
struct cViewer_s00f9_b620 {
    void Copy(void* other, int a, int b);       // 0x007c50b0
    bool Update();                              // 0x007c4fd0
    void Reset();                               // 0x007c3c10
    void SetZoom(float f);                      // 0x007c4ba0
    void SetTexture(void* p);                   // 0x007c3cb0
};
struct Sync94 { void Sync(void* a); };          // 0x006ffe00 (this = cTS142+0x92c)
struct TerrainMapSet;
struct ColorMap;
struct RasterRes;
struct RasterObj;
struct ViewFrame_s00f9_b620;
struct ColorMap {
    void*     mpVtbl;      // +0x00
    uint8_t   pad04[0x08 - 0x04];
    uint32_t  mFaceSize;   // +0x08
    uint32_t  mModCount;   // +0x0c
    uint32_t* mpData;      // +0x10
};
struct TerrainMapSet {
    void*      mpVtbl;     // +0x00
    uint8_t    pad04[0x08 - 0x04];
    ColorMap*  mMaps[11];  // +0x08 .. +0x33 (kMapColor == 3)
};
struct RasterRes {
    uint8_t  pad00[0x0c];
    uint16_t mWidth;       // +0x0c
    uint16_t mHeight;      // +0x0e
    bool Lock(int a, int b, void** out);   // 0x011ef750 (ret 0xc)
    void Unlock(void** out);               // 0x011ef880 (ret 4)
};
struct RasterObj {
    RasterRes* mpRes;      // +0x00
    uint32_t   mFlags;     // +0x04 (bit 0 = resident)
};
struct ViewFrame_s00f9_b620 {
    uint8_t    pad00[0x2f4];
    RasterObj* mStreams[14];   // +0x2f4
};
extern cViewer_s00f9_b620 g_renderViewer;      // 0x016ca410
struct cTS142 {
    uint8_t  pad0[0x28];
    cDirectPropertyList_s00f9_b620* mpProps;   // +0x28
    TerrainMapSet* mpMapSet;        // +0x2c
    float    mScale;                // +0x30
    uint8_t  pad34[0x74 - 0x34];
    uint8_t  mSub74[0x30];          // +0x74
    uint8_t  padA4[0xb8 - 0xa4];
    uint8_t  mSubB8[0x44];          // +0xb8
    void*    mpFC;                  // +0xfc
    uint8_t  pad100[0x108 - 0x100];
    uint8_t  mByte108;              // +0x108
    uint8_t  pad109[0x10c - 0x109];
    float    mF10c;                 // +0x10c
    uint8_t  pad110[0x148 - 0x110];
    void*    mImg148[6];            // +0x148 .. +0x160
    void*    mImg160[6];            // +0x160 .. +0x178
    void*    mImg178[6];            // +0x178 .. +0x190
    void*    mpDecalBegin;          // +0x190
    void*    mpDecalEnd;            // +0x194
    uint8_t  pad198[0x1d0 - 0x198];
    int      mDecalIdMode;          // +0x1d0
    uint8_t  pad1d4[0x1ec - 0x1d4];
    float    mF1EC[8];              // +0x1ec .. +0x208
    uint8_t* mp20c;                 // +0x20c
    uint8_t  pad210[0x30c - 0x210];
    float    mMat30c[10];           // +0x30c .. +0x334
    uint8_t  pad334[0x4f8 - 0x334];
    uint8_t  mShader4f8[0x1d0];     // +0x4f8
    uint8_t  pad6c8[0x814 - 0x6c8];
    int      mF814;                 // +0x814
    int      mF818;                 // +0x818
    uint8_t  pad81c[0x8d8 - 0x81c];
    int      mF8d8;                 // +0x8d8
    uint8_t  pad8dc[0x8e4 - 0x8dc];
    cViewer_s00f9_b620* mpViewer;              // +0x8e4
    uint8_t  pad8e8[0x92c - 0x8e8];
    uint8_t  mMat92c[0x40];         // +0x92c

    void FUN_00f9b620(uint32_t a, uint32_t b, uint32_t c, float* p5, float* p6, float* p7);
    void FUN_00f9b7f0();
    void FUN_00f9b8c0(int a, int b, int flag, uint8_t f5, float f6);
    void FUN_00f9ba40(void* mtx);
    void FUN_00f9bb50();
    void FUN_00f9bc40(uint32_t a, uint32_t b);
    void FUN_00f9bd00(void* p2, uint32_t a, uint32_t b);
    void FUN_00f9bee0(void* p2);
    void FUN_00f9c010(int idx);
    void FUN_00f9c0d0(int face, void* renderStats);

    // sibling cTerrainSphere methods (defined in other slices)
    void FUN_00f97f50(uint32_t a, uint32_t b);
    void FUN_00f98530(void* viewer, uint32_t a);
    void FUN_00f98020(uint32_t a, uint32_t b);   // RenderWater
    void FUN_00f98170(uint32_t a, uint32_t b);
    void FUN_00f981d0(uint32_t a, uint32_t b);   // RenderAtmosphere
    void FUN_00f98970();                          // 0x00f98970 (SkyState::Update)
    void FUN_00f998f0();
};
struct Sub20c {
    uint8_t pad[0x28];
    void*   mp28;       // +0x28
    uint8_t pad2c[0x30 - 0x2c];
    float   mScale;     // +0x30
    uint8_t pad34[0x1f4 - 0x34];
    void*   mp1f4;      // +0x1f4
    uint8_t pad1f8[0x20c - 0x1f8];
    void*   mp20c;      // +0x20c
    uint8_t pad210[0x334 - 0x210];
    void*   mp334;      // +0x334
};
struct Sub334 {
    uint8_t pad[0x28];
    uint32_t* mp28;     // +0x28
};
static inline void EnsureRaster(RasterObj* r)
{
    if ((r->mFlags & 1) == 0) {
        void* mgr = FUN_0067dd60();
        ((Tv1p)VTO(mgr, 0x34))(mgr, r);
    }
}
// ---- items of slice s00f9b620 end

// ---- items of slice s00f9c470 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int*   g_p16c9f5c;         // 0x016c9f5c
extern const float g_e8c;         // 0x016c9e8c
extern const float g_e90;         // 0x016c9e90
extern const float g_e94;         // 0x016c9e94
extern const float g_f24;         // 0x016c9f24
extern const float g_f28;         // 0x016c9f28
extern const float g_f2c;         // 0x016c9f2c
extern const float g_f30;         // 0x016c9f30
extern const float g_f34;         // 0x016c9f34
extern const float g_f38;         // 0x016c9f38
extern const float g_f3c;         // 0x016c9f3c
extern const float g_f40;         // 0x016c9f40
extern const float g_f44;         // 0x016c9f44
extern const float g_8d4;         // 0x016ca584
extern const float g_8d8;         // 0x016ca588
extern const float g_8dc;         // 0x016ca58c
extern const float g_1c8;         // 0x015b11c8
extern const float g_1cc;         // 0x015b11cc
extern const float g_1d0;         // 0x015b11d0
extern const float g_1d4;         // 0x015b11d4
extern uint8_t g_faceRecs[6 * 0x40];  // 0x015b1340
extern const float kEps;          // 0x014904d0 = 1.5258789e-05f
struct Quat { float x, y, z, w; };
struct Mat33 { float m0, m1, m2, m3, m4, m5, m6, m7, m8; };
void*  __cdecl FUN_0067dd50();                                    // 0x0067dd50
Mat33* __cdecl Matrix3FromQuaternion(Mat33* out, const Quat* q);  // 0x0059c190
void*  __cdecl QuaternionFromMatrix33(Quat* out, const Mat33* m, float eps); // 0x00472b80
float* __cdecl FUN_0046d660(float* out, const float* m);          // 0x0046d660
Vec3*  __cdecl OrthogonalVector(Vec3* out, const Vec3* in);       // 0x006985b0
float* __cdecl normalized_safe(float* out, const float* in);      // 0x00449c20
struct cTerrainMapSet_s00f9_c470 {
    float GetHeightAt(const void* pos);      // 0x00f927c0
};
struct cPropList {
    bool GetDescription(uint32_t id);        // 0x006a25a0
};
struct cViewerS {
    void Clear(uint32_t layer);              // 0x007c3c50
    void SetBasis(void* basis);              // 0x007c4d00
};
struct Basis3 {
    uint32_t flags;      // +0x00
    Vec4     vec;        // +0x04
    Mat33    mat;        // +0x14
    void Normalize(const void* rec);         // 0x006b92d0
};
struct AppArg { void* p0; void* p1; void* p2; void* p3; };
typedef void* (__thiscall *FnV)(void*);
typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnCall)(void*, int, int, int, void*, int, int);
struct cTS143 {
    Quat BuildSurfaceOrientation(const Vec3& a, const Vec3& b);              // 0x00f9c660
    Quat BuildSurfaceOrientationV(const Vec3& up, const Quat& q);            // 0x00f9c960
    Quat BuildPitchedSurfaceOrientation(const Vec3* pos, const Quat* q, float pitch); // 0x00f9cc50
};
// ---- items of slice s00f9c470 end

// ---- items of slice s00f9d080 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vector2_s00f9_d080 { float x, y; };
}
namespace SP {
struct Vector3_s00f9_d080 { float x, y, z; };
}
namespace SP {
struct Quaternion { float x, y, z, w; };
}
namespace SP {
struct Matrix33_s00f9_d080 { Vector3_s00f9_d080 xAxis, yAxis, zAxis; };   // 9 floats
}
namespace SP {
Matrix33_s00f9_d080&   Matrix3FromQuaternion(Matrix33_s00f9_d080& out, const Quaternion& q);                // 0x0059c190
}
namespace SP {
Quaternion* QuaternionFromMatrix33(Quaternion* out, const Matrix33_s00f9_d080& m, float w);       // 0x00472b80
}
namespace SP {
int*        CoordToIndex(int* out, int size, float* uv);                               // 0x00684bf0
}
namespace SP {
void*       GetImageResource_s00f9_d080(void* out, void* stream);                                 // 0x00576650
}
namespace SP {
void*       MemSet(void* dst, int v, unsigned n);                                      // 0x011e073e (memset)
}
namespace SP {
void*       MaterialManager_s00f9_d080();                                                         // 0x0067dd70
}
namespace SP {
void        ShaderCall(int id, void* data, int flag);                                  // 0x00777ae0
}
namespace SP {
float       SceneQueryA(void* scene);                                                  // 0x00fb7b90
}
namespace SP {
void        RasterStageUpdate(int face);                                               // 0x007c3cb0 (this=0x016c9f60)
}
namespace SP {
bool        RasterViewerUpdate();                                                      // 0x007c4fd0 (this=0x016c9f60)
}
namespace SP {
void        RasterFlushStage();                                                        // 0x007c3c10 (this=0x016c9f60)
}
namespace SP {
class cTerrainMapSet_s00f9_d080;
}
namespace SP {
class cTerrainEditor {
 public:
  float GetRandom01();                                                                 // 0x00f678d0
  void  BuildDecal(const Vector3_s00f9_d080* pos, const Quaternion* orient, float size, void* decal,
                   void* target, void* arg6, uint32_t arg7, uint32_t arg8, void* rects,
                   uint32_t arg10);                                                    // 0x00f6c940
};
}
namespace SP {
cTerrainEditor* TerrainEditor();                                                       // 0x00f48a70
}
namespace SP {
class cTerrainMapSet_s00f9_d080 { public:
  float GetHeightAt(const Vector3_s00f9_d080& v) const;                                           // 0x00f927c0
};
}
namespace SP {
static const uint32_t kDecalTargetTemplate[17] = {
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3f800000,
  0x00000007, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000,
};
}
namespace SP {
static const uint32_t kFaceUVTable[6][12] = {
  { 0x3f800000, 0xbf800000, 0x3f800000, 0x3f800000, 0xbf800000, 0xbf800000,
    0x3f800000, 0x3f800000, 0xbf800000, 0x3f800000, 0x3f800000, 0x3f800000 },
  { 0xbf800000, 0xbf800000, 0xbf800000, 0xbf800000, 0xbf800000, 0x3f800000,
    0xbf800000, 0x3f800000, 0x3f800000, 0xbf800000, 0x3f800000, 0xbf800000 },
  { 0xbf800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000,
    0x3f800000, 0x3f800000, 0xbf800000, 0xbf800000, 0x3f800000, 0xbf800000 },
  { 0xbf800000, 0xbf800000, 0xbf800000, 0x3f800000, 0xbf800000, 0xbf800000,
    0x3f800000, 0xbf800000, 0x3f800000, 0xbf800000, 0xbf800000, 0x3f800000 },
  { 0xbf800000, 0xbf800000, 0x3f800000, 0x3f800000, 0xbf800000, 0x3f800000,
    0x3f800000, 0x3f800000, 0x3f800000, 0xbf800000, 0x3f800000, 0x3f800000 },
  { 0x3f800000, 0xbf800000, 0xbf800000, 0xbf800000, 0xbf800000, 0xbf800000,
    0xbf800000, 0x3f800000, 0xbf800000, 0x3f800000, 0x3f800000, 0xbf800000 },
};
}
namespace SP {
extern uint32_t g_rasterStageDirty;             // 0x016fa3a8
}
namespace SP {
extern void*    g_rasterSlots[17];              // 0x016f9650
}
namespace SP {
extern uint8_t  g_scatterDescFlag;             // 0x016ca5a4
}
namespace SP {
extern char*    g_appProps;                    // 0x015fd918
}
namespace SP {
class cTerrainSphere_s00f9_d080 {
 public:
virtual void  v00();
virtual void v04();
virtual void v08();
  virtual void* GetQuadContainer();                                                    // +0x0c
  virtual void* GetScene();                                                            // +0x10
virtual void  v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void  v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void  v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void  v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void  v54();
virtual void v58();
virtual void v5c();
virtual void v60();
  virtual void  v64();

  char  pad00[0x2c];
  cTerrainMapSet_s00f9_d080* mpMapSet;                                                            // +0x2c
  char  pad30[0x928 - 0x30];
  void* mpScatterRaster;                                                               // +0x928

  Quaternion BuildSurfaceNormalOrientation(const Vector3_s00f9_d080& pos, const Quaternion& baseQuat,
                                           float pitch) const;
  void DrawFootprint(void* xform, float z, void* img, const Vector2_s00f9_d080* off, bool flag,
                     void* faceBoxes, void* a3);
  void UpdateScatterTexture(int face, void* raster, const Vector3_s00f9_d080& dir, void* stats);  // 0x00f9d9b0 (SP::cTerrainSphere::UpdateScatterTexture)
};
}
// ---- items of slice s00f9d080 end

// ---- items of slice s00f9df20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_16fa3a8;          // 0x016fa3a8 raster stage dirty bits
extern uint32_t g_16f9674;          // 0x016f9674
extern uint8_t g_15b11a0[];          // 0x015b11a0
extern uint32_t g_15b1150[];       // 0x015b1150
extern uint32_t g_15b115c[];       // 0x015b115c
extern uint32_t g_15b1168[];       // 0x015b1168
extern uint32_t* g_16c9e44[6];     // 0x016c9e44
extern uint8_t g_1490418[];         // 0x01490418
extern void __cdecl SetTexture(int slot, uint32_t h);             // 0x006dd2e0
extern bool __cdecl LockDraw(int a, int b, float** out, void* info);   // 0x006ddcc0
extern void __cdecl IssueDraw(int a, uint32_t b);                 // 0x006ddd10
extern uint32_t g_15b11f0;                                          // 0x015b11f0
extern uint32_t g_15b14c8;                                          // 0x015b14c8
extern const float k_13ec4d8;                                       // 0x013ec4d8
extern const float g_16c9e8c;                                       // 0x016c9e8c
extern const float g_16c9e90;                                       // 0x016c9e90
extern const float g_16c9e94;                                       // 0x016c9e94
extern const float g_16c9f24;                                       // 0x016c9f24
extern const float g_hkRealOne;                                     // 0x01485720 (_HK_REAL_ONE)
extern const float g_15b14c0;                                       // 0x015b14c0
extern const float g_15b14c4;                                       // 0x015b14c4
extern uint8_t     g_16ca5a5;                                       // 0x016ca5a5
extern void __cdecl IssueScatterShader(uint32_t id, uint32_t a, uint32_t b);   // 0x00777ae0
extern "C" float __cdecl sqrtf(float);
extern "C" float __cdecl fabsf(float);
extern const float g_1471064;                                       // 0x01471064
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)
#pragma intrinsic(sqrtf, fabsf)
struct Raster_s00f9_df20;
struct Viewer;
struct LazyRes {
    Raster_s00f9_df20* p;
    uint32_t flags;
    uint32_t Get();     // 0x0046f260 (out-of-line: resolve, then return p)
};
struct ResMgr {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
    virtual void Resolve(LazyRes* h);      // slot 13 (+0x34)
    virtual void v14();
    virtual void* CreateTexture(uint32_t id, uint32_t global, uint32_t width, uint32_t height,
                                uint32_t flag, uint32_t format, uint32_t mip, uint32_t extra);   // slot 15 (+0x3c)
};
extern ResMgr* __cdecl GetResMgr();        // 0x0067dd60
static inline Raster_s00f9_df20* ResolveRaster(LazyRes* h)
{
    if (!(h->flags & 1)) {
        GetResMgr()->Resolve(h);
    }
    return h->p;
}
struct Raster_s00f9_df20 {
    char pad[0x12];
    uint8_t m_face;
    uint32_t Fill(int zero);                                                  // 0x011f0000
    void FillSpriteTexture(uint32_t pixels, uint32_t bytes, int zero);        // 0x011f0440
    int Lock(int mode, int zero, uint32_t* out);                              // 0x011ef750
    void Unlock(uint32_t* info);                                              // 0x011ef880
};
struct Viewer {
    void SetRaster(LazyRes* r, int flag);   // 0x007c4be0
    bool Update();                          // 0x007c4fd0
    void Finish();                          // 0x007c3c10
};
struct CompiledState { void Dispatch(); };  // 0x011ee580
struct Material { uint32_t pad; CompiledState* cs; };
struct MaterialManager_s00f9_df20 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual Material* GetMaterial(uint32_t key);   // slot 10 (+0x28)
};
extern MaterialManager_s00f9_df20* __cdecl GetMaterialManager();   // 0x0067dd70
struct AppIface2 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual uint32_t Get();    // slot 7 (+0x1c)
};
struct AppIface {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
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
    virtual AppIface2* Get();  // slot 20 (+0x50)
};
extern AppIface* __cdecl GetApp();                      // 0x0067dd10
struct ShConst {
    float v[60];
    void Zero();                                        // 0x0077d170
    void Set(int idx, float x, float y, float z, float w);   // 0x0077ca20
};
struct CfgBlock {          // terrain state + 0x2f4
    uint32_t pad0;
    uint32_t* p4;         // +0x04
    uint32_t pad1[2];
    uint32_t* p10;        // +0x10
    uint32_t pad2;
    LazyRes* h18;          // +0x18
    uint32_t pad3[2];
    LazyRes* h24;          // +0x24
    uint32_t* p28;        // +0x28
};
struct CamObj {            // result of Terrain::GetCam (+0x34..+0x3c)
    char pad[0x34];
    float x, y, z;
};
struct StateObj {
    char pad[0x2f4];
    CfgBlock cfg;          // +0x2f4
    float GetF();          // 0x00fb8a00
    float GetG();          // 0x00fb88d0
    void Compute(float* out);   // 0x00fb9ad0
};
struct TerrainParams {
    char pad[0x42c];
    float a, b, c;         // +0x42c
    void Setup(uint32_t h, float f, int n);   // 0x00fbf570
};
struct Terrain {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual CamObj* GetCam();         // slot 3 (+0xc)
    virtual StateObj* GetState();     // slot 4 (+0x10)
    uint32_t pad0[0x51];
    uint32_t* arrA[6];               // +0x148
    uint32_t* arrB[6];               // +0x160
    uint32_t pad1[0x25];
    TerrainParams* params;            // +0x20c
    uint32_t pad2[0x1a0];
    LazyRes* hTex;                    // +0x890
    uint32_t pad3[4];
    int lastFace;                     // +0x8a4
    void UpdateScatterTexture(int face, Raster_s00f9_df20* dst, const void* data, uint32_t arg);   // 0x00f9d9b0
    void RefreshA();                  // 0x00f98970
};
struct PlanetPass {
    uint32_t pad0[3];
    Terrain* terrain;      // +0x0c
    int mode;              // +0x10
    int face;              // +0x14
    LazyRes raster;        // +0x18
    Viewer* viewer;        // +0x20
    void Run(uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00f9e4d0
};
extern LazyRes* g_16c9f54;          // 0x016c9f54
static inline Vec3f MkV(float x, float y, float z) { Vec3f r; r.x = x; r.y = y; r.z = z; return r; }
static inline void SetV(float* v, float x, float y, float z) { *(Vec3f*)v = MkV(x, y, z); }
static inline void PutF(float* d, float v) { union { float f; uint32_t u; } t; t.f = v; *(uint32_t*)d = t.u; }
struct cScatterResource {
    void*    mpImage;                                               // +0x00 raw image handle
    uint32_t mFlags;                                                // +0x04
    volatile long mnRefCount;                                       // +0x08
    __forceinline int Release()
    {
        _InterlockedDecrement(&mnRefCount);
        if (_InterlockedExchangeAdd(&mnRefCount, 0) < 1) {
            _InterlockedIncrement(&mnRefCount);
            return 1;
        }
        return _InterlockedExchangeAdd(&mnRefCount, 0);
    }
};
struct cScatterViewer {
    void Destroy();                                                 // 0x007c3ba0
    bool Init(bool flag);                                           // 0x007c4dd0
    void Clear(uint32_t color) const;                               // 0x007c3cc0
    void SetImage(void* pImage);                                    // 0x007c3cb0
    void SetClearColor(const struct cSPColorRGBA_s00f9_df20& color);           // 0x007c3c20
    void SetViewAngleY(float angle);                                // 0x007c53d0
    void SetQuad(uint16_t* pQuad);                                  // 0x007c4a60
    void GetTransform(struct cSPTransform_s00f9_df20* pOut);                    // 0x007c40f0
};
struct cImageSlot {
    cScatterResource* mpResource;                                   // +0x00
    void GetImageResource(void* pTexture);                          // 0x00576650
};
struct cSPColorRGBA_s00f9_df20 { float r, g, b, a; };
struct cViewQuad {
    uint32_t x;                                                     // +0x00
    uint32_t y;                                                     // +0x04
    uint32_t width;                                                 // +0x08
    uint32_t height;                                                // +0x0c
};
extern cScatterResource* g_pScatterTex1;                            // 0x016c9f54
extern cScatterResource* g_pScatterTex1b;                           // 0x016c9f58
extern cScatterResource* g_pScatterTex2;                            // 0x016c9f5c
extern cScatterViewer   g_scatterViewer1;                           // 0x016c9f60
extern cScatterViewer   g_scatterViewer2;                           // 0x016ca260
struct cScatterProbe {
    virtual void AddRef();                                          // +0x00
    virtual void Release();                                         // +0x04
    virtual void SetActive(int a);                                  // +0x08
};
struct cScatterMgr {
    virtual void AddRef();                                          // +0x00
    virtual void Release();                                         // +0x04
    virtual void GetProbe(uint32_t id, int a, void** ppOut);        // +0x08
    virtual void V0c(int a);                                        // +0x0c
virtual void V10();
virtual void V14();
virtual void V18();
    virtual void V1c(void* p);                                      // +0x1c
    virtual void V20();
    virtual void V24(int a);                                        // +0x24
virtual void V28();
virtual void V2c();
virtual void V30();
virtual void V34();
virtual void V38();
virtual void V3c();
virtual void V40();
virtual void V44();
virtual void V48();
virtual void V4c();
virtual void V50();
virtual void V54();
virtual void V58();
virtual void V5c();
virtual void V60();
virtual void V64();
virtual void V68();
virtual void V6c();
virtual void V70();
virtual void V74();
    virtual void V78(int a);                                        // +0x78
virtual void V7c();
virtual void V80();
    virtual void V84(uint32_t a, uint32_t b);                       // +0x84
};
struct cEffectsMgrIface {
virtual void V00();
virtual void V04();
virtual void V08();
virtual void V0c();
virtual void V10();
virtual void V14();
virtual void V18();
virtual void V1c();
virtual void V20();
virtual void V24();
virtual void V28();
virtual void V2c();
virtual void V30();
virtual void V34();
virtual void V38();
virtual void V3c();
virtual void V40();
virtual void V44();
virtual void V48();
    virtual void* V4c(uint32_t id, int a);                          // +0x4c
};
cEffectsMgrIface* EffectsManagerPtr();                              // 0x0067ddd0
cScatterMgr* FUN_006eea10();                                        // 0x006eea10
struct cAppHost {
virtual void V00();
virtual void V04();
virtual void V08();
virtual void V0c();
virtual void V10();
virtual void V14();
virtual void V18();
virtual void V1c();
virtual void V20();
virtual void V24();
virtual void V28();
virtual void V2c();
virtual void V30();
virtual void V34();
virtual void V38();
virtual void V3c();
virtual void V40();
virtual void V44();
virtual void V48();
virtual void V4c();
    virtual uint32_t V50();                                         // +0x50
};
cAppHost* GetAppHost();                                             // 0x0067dd10
template <class T> struct ip {
    T* p;
    ip& operator=(T* o)
    {
        if (o != p) {
            T* const pTemp = p;
            int d1, d2, d3;
            if (o) o->AddRef();
            p = o;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    T* operator->() const { return p; }
    T** AsOutParam() { if (p) { T* t = p; p = 0; t->Release(); } return &p; }
};
struct cScatterHost {
    uint8_t       pad00[0x8d8];
    ip<cScatterMgr>   mpSensorMgr;                                  // +0x8d8
    ip<cScatterMgr>   mpEffectMgr;                                  // +0x8dc
    ip<cScatterProbe> mpProbe;                                      // +0x8e0
    void RebuildEffects();
};
extern cImageSlot g_imageSlot2;                                     // 0x016c9f5c
struct cScatterSphere {
    void InitScatterTexture2();                                     // 0x00f9e280
};
struct cSPMatrix3_s00f9_df20 {
    float m[9];                                                     // +0x00 (0x24 bytes)
    cSPMatrix3_s00f9_df20* Assign(const void* pSrc);                           // 0x0041cb40
};
struct cSPTransform_s00f9_df20 {                                               // 0x38 bytes
    uint16_t   mFlags;                                              // +0x00
    uint16_t   mFlags2;                                             // +0x02
    Vec3f      mOffset;                                             // +0x04
    float      mScale;                                              // +0x10
    cSPMatrix3_s00f9_df20 mRotation;                                           // +0x14
    cSPTransform_s00f9_df20()
    {
        mFlags = 0;
        mFlags2 = 0;
        mOffset.x = g_16c9e8c;
        mOffset.y = g_16c9e90;
        mOffset.z = g_16c9e94;
        mScale = g_hkRealOne;
        mRotation.Assign(&g_16c9f24);
    }
    cSPTransform_s00f9_df20& operator=(const cSPTransform_s00f9_df20& other);             // 0x00537dc0
};
struct cTerrainSphere7 {
    uint8_t      pad00[0x8e8];
    cSPTransform_s00f9_df20 mScatterXform;                                     // +0x8e8
    int32_t      mScatterState;                                     // +0x920
    void UpdateScatterTexture(int face, Raster_s00f9_df20* pRaster, const void* pData, uint32_t arg);   // 0x00f9d9b0
    void UpdateScatter(cScatterViewer* pViewer, Raster_s00f9_df20* pRaster, const void* pData, uint32_t arg);
};
struct cSPVector3_s00f9_df20 { float x, y, z; };
struct cTerrainEditorObj {
    void FUN_00f67560();                                            // 0x00f67560
};
cTerrainEditorObj* __cdecl TerrainEditor_s00f9_df20();                         // 0x00f48a70
struct cProperty {
    uint8_t    pad00[0x12];
    uint16_t   mType;                                               // +0x12
    uint32_t*  GetUInt();                                           // 0x0041ea00
};
struct cPropertyList_s00f9_df20 {
virtual void V00();
virtual void V04();
virtual void V08();
virtual void V0c();
virtual void V10();
virtual void V14();
virtual void V18();
virtual void V1c();
    virtual void V20();
    virtual bool V24(uint32_t id, cProperty** ppOut);               // +0x24
};
bool __cdecl GetPropertyAsVector3(const cPropertyList_s00f9_df20* pList, uint32_t id, cSPVector3_s00f9_df20* pOut);   // 0x006a1110
struct cTerraformParams {
    uint8_t pad00[0x50];
    float   mValues[2];                                             // +0x50
};
struct cPlanetLike {
    void BuildHeightHistogram();                                    // 0x00fbb1a0
    float HeightToRatio(float height);                              // 0x00fbd8b0
    void FUN_00fb9420(float a, float b, float* pOut);               // 0x00fb9420
    void RefreshTerraformValues();                                  // 0x00fbdee0
};
struct cTerrainSphere8 {
    uint8_t           pad00[0x28];
    cPropertyList_s00f9_df20*    mpPropList;                                   // +0x28
    cTerraformParams* mpParams;                                     // +0x2c
    uint8_t           pad30[0x20c - 0x30];
    cPlanetLike*      mpPlanet;                                     // +0x20c
    void FUN_00f9a610();                                            // 0x00f9a610
    void RefreshTerraform();
};
extern cImageSlot g_imageSlot1;                                     // 0x016c9f54
extern cImageSlot g_imageSlot1b;                                    // 0x016c9f58
// ---- items of slice s00f9df20 end

// ---- items of slice s00f9fef0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_rttHandles[6];        // 0x016c9e44
extern unsigned g_rttNames[6][2];       // 0x016ca3d4
extern unsigned char g_rttActive;       // 0x016c9e60
extern void* g_pRTT0;                   // 0x016c9f58
extern void* g_pRTT1;                   // 0x016c9f5c
extern unsigned g_texTerrain;           // 0x016c9e40
extern void* g_pSomeTex;                // 0x016c9e6c
extern unsigned g_colorMap[2];          // 0x015b1218
extern void* g_viewerObj;               // 0x016ca410 (a cViewer)
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement, _InterlockedExchange)
struct AtomicRef {
    char pad00[8];
    volatile long mnRefCount;
    int Release()
    {
        _InterlockedDecrement(&mnRefCount);
        if (_InterlockedExchangeAdd(&mnRefCount, 0) < 1) {
            _InterlockedIncrement(&mnRefCount);
            return 1;
        }
        return _InterlockedExchangeAdd(&mnRefCount, 0);
    }
};
void* __cdecl EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
void* __cdecl operator_new_arr(void* dst, unsigned int zero, unsigned int size);            // 0x011e073e
struct ServiceObj {
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
    virtual void Release(void* p);   // +0x34
};
ServiceObj* FUN_0067dd60_s00f9_fef0();          // 0x0067dd60
ServiceObj* FUN_0067dd50_s00f9_fef0();          // 0x0067dd50
ServiceObj* FUN_0067dda0_s00f9_fef0();          // 0x0067dda0
struct TexInst {
    uint32_t* mpData;   // +0x00
    uint32_t  mFlags;   // +0x04
};
char __cdecl CopyImageRectToSurface(void* data, int other, int face, const float* rect);    // 0x00f9f200
char __cdecl FUN_00f9f360(void* data, int other, int face, const float* rect);              // 0x00f9f360
char __cdecl FUN_00f9f4c0(void* data, int other, int face, const float* rect);              // 0x00f9f4c0
struct TerrainSphereLike {
    char pad00[0x2c];
    void* mpSurfaces;            // +0x2c -> +8 / +0xc / +0x10 are the three surfaces
    char pad30[0x148 - 0x30];
    TexInst* mFacesB[6];         // +0x148
    TexInst* mFacesA[6];         // +0x160
    TexInst* mFacesC[6];         // +0x178

    bool CopyFaceA(int face, const float* rect);
    bool CopyFaceB(int face, const float* rect);
    bool CopyFaceC(int face, const float* rect);
};
struct SurfaceHolder {
    char pad0[8];
    void* mSurface8;
    void* mSurfaceC;
    void* mSurface10;
};
struct DirtyFlag {
    char pad000[0x368];
    unsigned char mDirtyBits[2];
    char pad36a[2];
    int  miDirty;                // +0x36c, current buffer index
    char pad370[0x6d8 - 0x370];
    char mBuffer[0x80];          // +0x6d8

    char& Flag0() { return *(char*)(miDirty + (char*)this + 0x368); }
    char& Flag1() { return *(char*)((char*)this - miDirty + 0x369); }

    void InitBuffer();           // 0x00fa0dc0
    void SetFlag(bool which);    // 0x00fa0e10
    void Dirty(unsigned char bits);    // 0x00fa0e40
    bool TestFlag(unsigned char bits); // 0x00fa0e60
};
struct VtblHolder {
    virtual void v00();
    virtual void v04();
    virtual void v08(int);   // +0x08
};
struct AutoRefLike {
    VtblHolder* mpObject;      // +0x00 (so +0x10 in JobHolder)
    volatile long mnRef;       // +0x04 (so +0x14 in JobHolder)

    int Release();
    int ReleaseObject();
};
struct JobHolder {
    char pad00[0x10];
    AutoRefLike mObj;          // +0x10

    int Release();             // 0x00fa0f10
};
int AutoRefLike::Release()
{
    AutoRefLike& self = *this;
    long v = _InterlockedDecrement(&self.mnRef);
    if (v == 0) {
        _InterlockedExchange(&self.mnRef, 1);
        if (&self)
            self.mpObject->v08(1);
    }
    return v;
}
void __cdecl QuaternionFromDirections(Quat* out, const Vec3* a, const Vec3* b);  // 0x00698180
extern const Vec3 kUpDir;                 // 0x016ca404
extern const Quat kDefaultQuat;           // 0x015b11c8
struct TerrainSphereQ {
    Quat BuildSurfaceOrientationFromDir(const Vec3& dir) const;                   // 0x00fa0130
    Quat BuildSurfaceOrientation(const Vec3& dir, const Quat& q) const;           // 0x00f9c960
};
struct Elem16 {
    uint32_t w0, w1, key, w3;    // key at +8 (unsigned)
};
void __cdecl FUN_00f9f7b0(Elem16* first, Elem16* last, unsigned key);   // 0x00f9f7b0
void __cdecl FUN_00f9f810(Elem16* first, Elem16* last, unsigned key);   // 0x00f9f810
void __cdecl FUN_00f9af30(Elem16* first, int a, int n, int b,
                          Elem16 tmp, unsigned key); // 0x00f9af30
struct RTTMgr {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void FreeRTT(unsigned a, unsigned b);   // +0x14
};
struct ViewerObject {
    void Shutdown();                    // cViewer::Shutdown  0x007c3ba0
};
extern ViewerObject g_viewer;           // 0x016ca410
void FUN_00f9e1f0();                    // 0x00f9e1f0

void FUN_00762a00(void* p);             // 0x00762a00
struct RTTVtbl2 {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual unsigned* CreateTex(unsigned* out, unsigned w, unsigned h, int fmt, int a, int b, int c); // +0x10
    virtual void v14();
    virtual unsigned MakeTexFromRes(unsigned a, unsigned b);   // +0x18
    virtual unsigned MakeTexFromRes2(unsigned a, unsigned b);  // +0x1c
    virtual void pad20();
    virtual void pad24();
    virtual void pad28();
    virtual void pad2c();
    virtual void pad30();
    virtual void pad34();
    virtual void pad38();
    virtual void pad3c();
    virtual void pad40();
    virtual void pad44();
    virtual void SetName(unsigned a, unsigned b, const char* name);  // +0x48
};
struct RTTMgr2 { RTTVtbl2* mpVtbl; };
bool __cdecl ViewerInit(void* viewer, bool b);              // 0x007c4dd0
void __cdecl ViewerClear(void* viewer, unsigned a);         // 0x007c3cc0
void __cdecl ViewerSetTex(void* viewer, unsigned a);        // 0x007c3cb0
void __cdecl ViewerSetRect(void* viewer, unsigned short* p); // 0x007c4a60
struct MsgVtbl {
    void* mSlot00;                                   // +0x00
    int   (__thiscall* mAddRef)(void* self);         // +0x04
    void  (__thiscall* mRelease)(void* self);        // +0x08
    void* mSlot0c;                                   // +0x0c
};
struct MsgObj {
    MsgVtbl* mpVtbl;    // +0x00
    volatile long mRef; // +0x04
    int f08;            // +0x08
    char pad0c[4];
    int f10;            // +0x10
    char pad14[0x1c];
    MsgVtbl* mpVtbl30;  // +0x30
    char pad34[4];
    int f38;            // +0x38
};
struct GeomHandlerOps {
    void FUN_00f99f20(void* a2, int a3, int a4, void* a5);
};
struct AppVtbl {
    void* mpad00[0x78 / 4];                                             // +0x00 .. +0x74
    int  (__thiscall* mRegisterId)(void* self, unsigned id);            // +0x78
};
struct AppObj { AppVtbl* mpVtbl; };
struct GeomChangeMsg {
    int            mKind;       // +0x00  (always 1)
    int            mReserved04; // +0x04
    bool           mFlag08;     // +0x08
    char           mPad09;
    char           mPad0a;
    char           mPad0b;
    int            mReserved0c; // +0x0c
    int            mReserved10; // +0x10
    int            mEventKind;  // +0x14  (0x03d5bf9a)
    MsgObj*        mpMessage;   // +0x18
    int            mReserved1c; // +0x1c
    int            mReserved20; // +0x20
    int            mReserved24; // +0x24
    int            mReserved28; // +0x28
    int            mReserved2c; // +0x2c
    struct GeomHandler* mpHandler;  // +0x30
    AppObj*        mpApp;       // +0x34
};
struct HandlerVtbl {
    void*     mpad00[4];                                                // +0x00 .. +0x0c
    unsigned (__thiscall* mSend)(void* self, int a, GeomChangeMsg* m);  // +0x10
};
struct GeomHandler { HandlerVtbl* mpVtbl; };
struct GeomMsgOwner {
    char pad000[0x898];
    int  mChangeState;        // +0x898 (handed to the handler)
    char pad89c[0x8a0 - 0x89c];
    GeomHandler* mpHandler;   // +0x8a0
    int          mMsgId;      // +0x8a4

    void AddGeometryChangeMessage(int a2, int a3);   // 0x00fa0560
};
unsigned __cdecl GetImageResourceImpl(void* dst, unsigned id);   // 0x00576650
void*    __cdecl TerrainEditorImpl(void* a, void* b, void* c, void* d, void* e, void* f,
                                   int, int, int, int);          // 0x00f48a70
void*    __cdecl DecalBoxBuilderImpl(void* a, void* b, void* c, void* d, void* e, void* f,
                                     int, int, int, int);        // 0x00f6c940
void*    __cdecl QuaternionFromMatrix33(void* out, const void* m, int a);  // 0x00472b80
struct ImageResHeader {                    // 0x78-byte block used by GetImageResource
    char pad000[0x78];
};
struct BuilderParam {                      // 0x7c-byte block
    char pad000[0x7c];
};
inline void RelPtr(void* p) { if (p) ((AtomicRef*)((char*)p + 8))->Release(); }
inline void VirtualRelease(void* p, int slot, int arg)
{
    if (!p) return;
    void** vt = *(void***)p;
    ((void(__thiscall*)(void*, int))vt[slot])(p, arg);
}
struct TerrainSphereRes { void Dtor(); };
namespace SP {
struct cDirectPropertyList_s006a_22a0 {
    bool GetDescription(unsigned id) const;                 // 0x006a25a0
};
}
namespace SP {
struct cTerrainSphere_s00f9_fef0 {
    void InitializeStaticRTTTextures();                     // 0x00f96b40
};
}
namespace SP {
void* ModelManager();                                       // 0x0067dd80
}
void* EffectsManagerPtr_s00f9_fef0();                                  // 0x0067ddd0
void __cdecl FUN_00f9e3a0(void* self);                      // 0x00f9e3a0
struct RegVtbl {
    void* mpad00[0x4c / 4];      // +0x00 .. +0x48
    void* mpfnAddEntry;          // +0x4c
    void* mpad50;                // +0x50
    void* mpad54;                // +0x54
    void* mpfnFindEntry;         // +0x58
};
struct RegObj { RegVtbl* mpVtbl; };
struct ModelMgrVtbl {
    void* mpad00[0x1c / 4];                                    // +0x00 .. +0x18
    void* (__thiscall* mGetInstance)(void* self, void* key);    // +0x1c
};
struct ModelMgrObj { ModelMgrVtbl* mpVtbl; };
struct ModelInstVtbl {
    void* mpad00[0x134 / 4];                                    // +0x00 .. +0x130
    void  (__thiscall* mSetActive)(void* self, int a);          // +0x134
    void* mpad38;                                               // +0x138
    void* (__thiscall* mGetHandle)(void* self, int a, int b);   // +0x13c
};
struct ModelInstObj { ModelInstVtbl* mpVtbl; };
struct EffectMgrVtbl {
    void* mpad00[0x54 / 4];                                    // +0x00 .. +0x50
    void* (__thiscall* mGetInstance)(void* self, void* key);    // +0x54
};
struct EffectMgrObj { EffectMgrVtbl* mpVtbl; };
struct EffectInstVtbl {
    void* mpad00[3];                                           // +0x00 .. +0x08
    void  (__thiscall* mApply)(void* self, int a);              // +0x0c
};
struct EffectInstObj { EffectInstVtbl* mpVtbl; };
struct TerrainSphereReg {
    char pad00[4];
    void Register(RegObj* obj);   // 0x00f9fef0
};
// ---- items of slice s00f9fef0 end

// ---- items of slice s00fa1bc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_011e073e(void* dst, int zero, unsigned size);   // 0x011e073e memset thunk
extern float g_Float016c9e98[4];        // 0x016c9e98 .. 0x016c9ea4
extern float g_Float016c9e8c[3];        // 0x016c9e8c .. 0x016c9e94
extern float g_Float015b117c[4];        // 0x015b117c .. 0x015b1188
extern int   g_TerrainSphereCount;      // 0x016c9e88
extern "C" void* __cdecl FUN_011e0744(void* dst, const void* src, unsigned size);  // 0x011e0744 memcpy
extern "C" void  __cdecl FUN_00f47380(void* p);                                     // 0x00f47380 operator delete
extern "C" void* __cdecl FUN_00f473a0(unsigned size, const char* name, int a, int b,
                                      const char* file, int line);                   // 0x00f473a0 allocator new
extern "C" void* __cdecl FUN_00f9f8f0(const void* a, const void* b, const void* c,
                                      const void* d, const void* e);                 // 0x00f9f8f0
extern "C" void* __cdecl FUN_00951bf0(const void* first, const void* last, void* dst); // 0x00951bf0 copy_Rec20

struct IBase0 { virtual void v0(); };
struct IBase1 { virtual void v0(); };
struct IBase2 { virtual void v0(); };
struct IBase3 { virtual void v0(); };
struct ResourceBase {            // refcounted resource at +0x10
    virtual void v0();
    volatile long mnRefCount;
    uint32_t mField18, mField1C, mField20;
    ResourceBase()
    {
        _InterlockedExchange(&mnRefCount, 0);
        mField18 = 0;
        mField1C = 0;
        mField20 = 0;
    }
};
struct ResourceBaseB : ResourceBase {   // one derived level that only re-stores the vptr and +0x24
    uint32_t mField24;
    ResourceBaseB() { mField24 = 0; }
    virtual void v0();
};
struct GenSteps0 {
    uint32_t mPad[0x44 / 4];
    void Init();    // 0x00fc17e0
};
struct GenSteps1 {
    uint32_t mPad[0x44 / 4];
    void Init();    // 0x00fc18c0
};
struct GenSteps2 {
    uint32_t mPad[0x44 / 4];
    void Init();    // 0x00fc16b0
};
struct AllocTag {
    AllocTag() {}
};
struct Matrix3_s00fa_1bc0 {
    float m[9];
    void Assign(const Matrix3_s00fa_1bc0* src);    // 0x0041cb40 (thiscall, ret 4)
};
struct Obj7C4 {                         // 0x14 bytes, built by 0x006a5ea0 (thiscall, ret 8)
    uint32_t mPad[5];
    void Init(int zero, const AllocTag& tag);   // 0x006a5ea0
};
struct cTerrainSphere_s00fa_1bc0;
extern cTerrainSphere_s00fa_1bc0* g_pTerrainSphere;    // 0x016c9e5c
extern Matrix3_s00fa_1bc0 g_IdentityMatrix;        // 0x016c9f24
struct cSPTransform_s00fa_1bc0;
extern "C" void* __cdecl DecalVecMoveBack_00f9aff0(void* first, void* last, void* dst);  // 0x00f9aff0 (alias: the module defines FUN_00f9aff0 with RefPair types)
extern "C" void* __cdecl DecalVecCopyRange_00f9adf0(void* first, void* pos, void* dst);   // 0x00f9adf0 (alias, see above)
extern "C" void  __cdecl DecalVecDestroyRange_00f9ae40(void* first, void* pos, void* dst);// 0x00f9ae40
extern "C" void* __cdecl DecalVecMoveDown_00f9ae80(void* first, void* last, void* dst);   // 0x00f9ae80 (alias, see above)

struct RefCounted {                     // 8-byte smart-pointer target (slot 0 = addref)
    virtual void AddRef();              // slot 0
    virtual void Release();             // slot 4
};
struct DecalPtr {                       // element of the decal smart-pointer vector (8 bytes)
    RefCounted* mPtr;                   // +0
    uint32_t    mField4;                // +4
};
struct DecalPtrVec {                    // SPVector<smart_ptr> at offset 0 of its owner
    DecalPtr* mBegin;                   // +0
    DecalPtr* mEnd;                     // +4
    DecalPtr* mCapacity;                // +8
    void Insert(DecalPtr* pos, DecalPtr* value);        // 0x00fa2440
    DecalPtr* EraseRange(DecalPtr* first, DecalPtr* last); // 0x00fa25c0
};
struct LayerVec {                       // SPVector<uint> slot, 0x14-byte stride
    uint32_t* mBegin;                   // +0
    uint32_t* mEnd;                     // +4
    uint32_t* mCapacity;                // +8
    uint32_t  mPad[2];                  // +0xc
    void AppendKey4(uint32_t* pos, const uint32_t& v);      // 0x00b96600
    void AppendValueI(uint32_t* pos, const uint32_t& v);    // 0x004558a0
};
struct cTerrainSphereDecal_s00fa_1bc0 {            // 0x12c bytes; only the refcount is read here
    virtual void Destroy(int flags);    // slot 0
    virtual void Release();             // slot 4
    uint32_t mRef;                      // +4
    cTerrainSphereDecal_s00fa_1bc0* InitDecal();   // 0x00fad730 (returns this)
    void SetupDecal(uint32_t index, uint32_t a, cTerrainSphere_s00fa_1bc0* sphere,
                    const cSPTransform_s00fa_1bc0* xform, float f, bool flag);   // 0x00faec70
    void Unlink();                      // 0x00fadac0
};
struct cTerrainSphere_s00fa_1bc0 : IBase0, IBase1, IBase2, IBase3, ResourceBaseB {
    uint32_t mF28, mF2C;
    GenSteps0 mSteps0;                  // +0x30
    GenSteps1 mSteps1;                  // +0x74
    GenSteps2 mSteps2;                  // +0xb8
    uint32_t mFC, mF100, mF104;
    bool mF108;
    float mF10C;
    bool mF110, mF111;
    uint32_t mF114;
    uint32_t mA118[12];                 // +0x118 .. +0x147
    uint32_t mF148[21];                 // +0x148 .. +0x198
    uint32_t mPad19C[2];
    uint32_t mF1A4[3];
    uint32_t mPad1B0[2];
    uint32_t mF1B8;                     // +0x1b8
    uint32_t* mListBegin;               // +0x1bc
    uint32_t* mListEnd;                 // +0x1c0
    uint32_t* mListCapacity;            // +0x1c4
    uint32_t mPad1C8;                   // +0x1c8
    uint32_t mF1CC, mF1D0;              // +0x1cc, +0x1d0
    union { uint32_t d; uint8_t b; } mF1D4;     // +0x1d4 (dword init, byte dirty store)
    float mF1D8, mF1DC, mF1E0, mF1E4;
    bool mF1E8;
    float mF1EC[8];                     // +0x1ec .. +0x208
    union {
        struct {                        // constructor view: individually zeroed vectors
            uint32_t mF20C[6];
            uint32_t mPad224[2];
            uint32_t mF22C[3];
            uint32_t mPad238[2];
            uint32_t mF240[3];
            uint32_t mPad24C[2];
            uint32_t mF254[3];
            uint32_t mPad260[2];
            uint32_t mF268[3];
            uint32_t mPad274[2];
            uint32_t mF27C[3];
            uint32_t mPad288[2];
            uint32_t mF290[3];
            uint32_t mPad29C[2];
            uint32_t mF2A4[3];
            uint32_t mPad2B0[2];
        };
        struct {                        // layer view used by the decal code
            uint32_t mPad20C[3];        // +0x20c .. +0x217
            LayerVec mDecalLayer[4];    // +0x218, stride 0x14
            LayerVec mFreeLayer[4];     // +0x268, stride 0x14
        };
    };
    uint32_t mF2B8[3];
    uint32_t mPad2C4[2];
    uint32_t mF2CC[3];
    uint32_t mPad2D8[2];
    uint32_t mF2E0[3];
    uint32_t mPad2EC[2];
    uint32_t mF2F4[3];
    uint32_t mPad300[2];
    uint32_t mF308;
    float mF30C[12];                    // +0x30c .. +0x338
    bool mF33C, mF33D;
    uint32_t mF340, mF344;
    bool mF348;
    float mF34C[5];                     // +0x34c .. +0x35c
    float mF360, mF364;
    bool mF368, mF369;
    uint32_t mF36C;
    bool mF370;
    Vec4 mVec[18];                      // +0x374 .. +0x493
    uint32_t mPad494[(0x4f4 - 0x494) / 4];
    bool mF4F4, mF4F5;
    uint32_t mPad4F6[(0x6d8 - 0x4f8) / 4];
    uint32_t mMemset6D8[0x80 / 4];      // +0x6d8
    uint32_t mF758[3];
    uint32_t mPad764[2];
    bool mF76C;
    uint32_t mF770[3];
    uint32_t mPad77C[2];
    uint32_t mF784[3];
    uint32_t mPad790[2];
    uint32_t mF798[3];
    uint32_t mPad7A4[2];
    uint32_t mF7AC, mF7B0, mF7B4, mF7B8;
    uint32_t mPad7BC[2];
    Obj7C4 mObj7C4;
    uint32_t mF7D8[3];
    uint32_t mPad7E4[2];
    uint32_t mF7EC[3];
    uint32_t mPad7F8[2];
    uint32_t mF800[3];
    uint32_t mPad80C[2];
    uint32_t mF814[3];
    uint32_t mPad820[(0x880 - 0x820) / 4];
    bool mF880;
    uint32_t mF884[5];
    int mF898, mF89C;
    uint32_t mF8A0;
    int mF8A4;
    uint32_t mF8A8;
    bool mF8AC;
    uint32_t mF8B0[3];
    uint32_t mPad8BC[2];
    uint32_t mF8C4[3];
    uint32_t mPad8D0[2];
    uint32_t mF8D8[4];
    uint16_t mF8E8, mF8EA;
    float mF8EC[3];
    float mF8F8;
    Matrix3_s00fa_1bc0 mMat8FC;
    int mF920;
    uint32_t mF924, mF928;
    uint32_t mPad92C[(0xa1c - 0x92c) / 4];
    float mFA1C[7];
    float mFA38[4];
    uint32_t mFA48, mFA4C;

    cTerrainSphere_s00fa_1bc0();
    void InitSubObjects();              // 0x00f97130
    void RemoveListEntry(uint32_t value);                       // 0x00fa23d0
    uint32_t AllocDecalIndex(uint32_t layer);                   // 0x00fa27d0
    void FreeDecalIndex(uint32_t packed);                       // 0x00fa2850
    cTerrainSphereDecal_s00fa_1bc0* NewDecal(uint32_t a, const cSPTransform_s00fa_1bc0* xform, float f);   // 0x00fa28b0
    cTerrainSphereDecal_s00fa_1bc0* NewDecalLayer(uint32_t a, const cSPTransform_s00fa_1bc0* xform,
                                       float f, uint32_t layer);                     // 0x00fa2920
    void ReleaseDecal(uint32_t packed);                         // 0x00fa29b0
    virtual void v0();
};
struct Rec20_s00fa_1bc0 {                          // 0x14-byte response-curve element
    uint32_t m[5];
};
struct Rec20Vector_s00fa_1bc0 {
    Rec20_s00fa_1bc0*   mBegin;                    // +0
    Rec20_s00fa_1bc0*   mEnd;                      // +4
    Rec20_s00fa_1bc0*   mCapacity;                 // +8
    uint32_t mPad0C;                    // +0xc
    Rec20_s00fa_1bc0*   mInline;                   // +0x10
    Rec20_s00fa_1bc0*   Realloc(uint32_t n, const Rec20_s00fa_1bc0* first, const Rec20_s00fa_1bc0* last);   // 0x00fa1b60
    void     assign(const Rec20_s00fa_1bc0* first, const Rec20_s00fa_1bc0* last, const Rec20_s00fa_1bc0& value);
};
struct DecalArrayElem {                 // 0x110-byte array element (own + inline buffers)
    void*    mPtr;                      // +0
    uint32_t mPad04[3];                 // +4
    void*    mAlt;                      // +0x10
    uint32_t mPad14[(0x110 - 0x14) / 4];
};
// ---- items of slice s00fa1bc0 end

// ---- items of slice s00fa47b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cRelevel_s00fa_47b0;
void*     __cdecl EAAllocate(unsigned n, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void      __cdecl EADeallocate(void* p);                                                               // 0x00f47380 (operator delete)
cRelevel_s00fa_47b0* __cdecl RelevelUninitCopy(const cRelevel_s00fa_47b0* first, const cRelevel_s00fa_47b0* last, cRelevel_s00fa_47b0* dest);      // 0x00f9f730
cRelevel_s00fa_47b0* __cdecl RelevelCopyBackward(const cRelevel_s00fa_47b0* first, const cRelevel_s00fa_47b0* last, cRelevel_s00fa_47b0* dest);    // 0x00f9f8b0
cRelevel_s00fa_47b0* __cdecl CopyRelevels_s00fa_47b0(cRelevel_s00fa_47b0* first, cRelevel_s00fa_47b0* last, cRelevel_s00fa_47b0* dest);                       // 0x00f9f770
void      __cdecl FUN_00f9f620(void* dest, const void* src);                                           // 0x00f9f620 cRelevel::operator=
void FUN_007c3ba0(void*);                                     // 0x007c3ba0
void FUN_007c4000(void*);                                     // 0x007c4000
int  FUN_00692400(void*, int);                                // 0x00692400 SP::cJob::Cancel
int  FUN_00690120(void*);                                     // 0x00690120 SP::cJob::GetStatus
void FUN_00f92b90(void*);                                     // 0x00f92b90
void FUN_00fc7950(void*);                                     // 0x00fc7950
void FUN_00fb3e20(void*);                                     // 0x00fb3e20
void FUN_00fb4340(void*);                                     // 0x00fb4340
void FUN_00fbe4f0(void*);                                     // 0x00fbe4f0
void FUN_00fbd650(void*);                                     // 0x00fbd650
void FUN_00fadac0(void*);                                     // 0x00fadac0
void FUN_00fa4660(void*, void*);                              // 0x00fa4660
void FUN_00fa44d0(void*, void*);                              // 0x00fa44d0
void FUN_00fa29b0(void*, uint32_t);                           // 0x00fa29b0 cTerrainSphere::RemoveDecal
void FUN_00faeec0(void*);                                     // 0x00faeec0
void FUN_00c2e4e0(void*);                                     // 0x00c2e4e0
void FUN_00fc6d10(void*);                                     // 0x00fc6d10
void* FUN_00f67d90(void*);                                     // 0x00f67d90 cTerrainEditor::GetCurrentTerrainSphere
void FUN_00f67a60(void*, int);                                // 0x00f67a60
void FUN_00fae800(void*);                                     // 0x00fae800
void FUN_00facfc0(void*);                                     // 0x00facfc0
int  FUN_00fad140(void*, int, void*);                         // 0x00fad140 cTerrainSphereDecal::GetBBoxForFace
void FUN_004558a0(void*, uint32_t*, const uint32_t*);         // 0x004558a0 SP::SimpleVector<uint>::DoInsertValue
void FUN_00533500(void*, void*, void*);                       // 0x00533500 vector<T*> deallocate
void FUN_005f3680(void*, void*, void*);                       // 0x005f3680 vector<AutoRefCount<cMWModel>>::DoDestroyValues
int  FUN_00fa45c0(const void*, const void*, float);           // 0x00fa45c0
void FUN_00f9a680(void*, int, void*);                         // 0x00f9a680
void FUN_00f9a760(void*, int, float);                         // 0x00f9a760
void FUN_00f9a6f0(void*, int, void*);                         // 0x00f9a6f0
void*     __cdecl FUN_0067dcc0();                             // 0x0067dcc0 SP::MessageServer
void*     __cdecl FUN_00f48aa0();                             // 0x00f48aa0 SP::GetActiveTerrainSphere
void      __cdecl FUN_00f48af0(void*);                        // 0x00f48af0
void*     __cdecl FUN_00f9ae80_s00fa_47b0(void*, void*, void*);          // 0x00f9ae80
void*     __cdecl FUN_005f4e10(void*, void*, void*);          // 0x005f4e10 eastl::copy_impl do_copy
void      __cdecl FUN_00f672b0(void*);                        // 0x00f672b0
typedef void (__thiscall *TC0)(void*);
typedef void* (__thiscall *TC0p)(void*);
typedef int  (__thiscall *TC0i)(void*);
typedef int  (__thiscall *TC1i)(void*, int);
typedef void (__thiscall *TC1u)(void*, uint32_t);
typedef void (__thiscall *TC1p)(void*, void*);
typedef void (__thiscall *TC2u)(void*, uint32_t, uint32_t);
typedef void (__thiscall *TC2pp)(void*, void*, void*);
typedef void (__thiscall *TC2ppc)(void*, uint32_t*, const uint32_t*);
typedef int  (__thiscall *TC2ip)(void*, int, void*);
typedef void (__thiscall *TC3)(void*, void*, uint32_t, int);
typedef int  (__thiscall *TC3f)(void*, const void*, const void*, float);
#define VT0(obj, idx)          ((TC0)(*(void***)(obj))[idx])(obj)
#define VT1i(obj, idx, a)      ((TC1i)(*(void***)(obj))[idx])(obj, a)
#define VT3(obj, idx, a, b, c) ((TC3)(*(void***)(obj))[idx])(obj, a, b, c)
#define ATOMREL8(p)                                                                                  \
  do {                                                                                               \
    volatile long* _r = (volatile long*)((char*)(p) + 8);                                            \
    _InterlockedExchangeAdd(_r, -1);                                                                 \
    long _v = _InterlockedExchangeAdd(_r, 0);                                                        \
    if (_v < 1) _InterlockedExchangeAdd(_r, 1); else _InterlockedExchangeAdd(_r, 0);                 \
  } while (0)
struct Key     { uint32_t instance, type, group; };
struct Matrix3I_s00fa_47b0 { Vector3 row0, row1, row2; };
struct cSPTransform_s00fa_47b0 {
  uint16_t mFlags, mModCount;
  float mTx, mTy, mTz, mScale;
  Matrix3I_s00fa_47b0 mRot;
};
struct cRelevel_s00fa_47b0 {
  cSPTransform_s00fa_47b0 mTransform;   // +0x00
  Rect mBounds[6];           // +0x38
  Key  mKey;                 // +0x98
  uint32_t mFlagsAndBits;    // +0xa4
  uint32_t mExtra;           // +0xa8
  cRelevel_s00fa_47b0(const cRelevel_s00fa_47b0&) throw();
  cRelevel_s00fa_47b0& operator=(const cRelevel_s00fa_47b0&) throw();
};
struct SPAllocator {
  const char* mpName;
  uint32_t mExtra;
  void* allocate(size_t n) {
    return EAAllocate(n, "Simulator", 0, 0,
                      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                      0xd1);
  }
  void deallocate(void* p) {
    if (p && ((int*)p)[-1] != 0) EADeallocate(p);
  }
};
struct RelevelVector_s00fa_47b0 {
  cRelevel_s00fa_47b0* mpBegin;
  cRelevel_s00fa_47b0* mpEnd;
  cRelevel_s00fa_47b0* mpCapacity;
  SPAllocator mAllocator;
  typedef size_t size_type;
  cRelevel_s00fa_47b0* DoAllocate(size_type n) { return n ? (cRelevel_s00fa_47b0*)mAllocator.allocate(n * sizeof(cRelevel_s00fa_47b0)) : 0; }
  void DoFree(cRelevel_s00fa_47b0* p, size_type) { mAllocator.deallocate(p); }
  void DoInsertValue(cRelevel_s00fa_47b0* position, const cRelevel_s00fa_47b0& value);
};
class cTerrainSphere_s00fa_47b0 {
 public:
  void Shutdown();
  void UpdateDecalNode(void* node);
  void DestroyDecalNode(void* node);
  bool RemoveRelevel(uint32_t key, unsigned char removeDecals);
  void ReleaseManaged();
  void FlushManaged();
  bool EraseRelevel(uint32_t key);
};
#define PTR(off)   (*(void**)((char*)this + (off)))
#define INTV(off)  (*(int*)((char*)this + (off)))
#define BYTEV(off) (*(unsigned char*)((char*)this + (off)))
// ---- items of slice s00fa47b0 end

// ---- items of slice s00fa6480 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl EAAllocate(unsigned n, const char* name, int a, int b, int c, int d); // 0x00f473a0
void  __cdecl FUN_00f9f100();                       // 0x00f9f100 cTerrainSphereLightingRegion ctor
void  __cdecl FUN_00f9f950();                       // 0x00f9f950 cLightDecal ctor
void* __cdecl FUN_00f9ada0(void*, void*);           // 0x00f9ada0 direction-through-transform helper
char  __cdecl FUN_00f9abc0();                       // 0x00f9abc0 region overlap predicate
void* __cdecl FUN_00f9b2b0();                       // 0x00f9b2b0 cRelevel builder
void  __cdecl FUN_00f9b1e0();                       // 0x00f9b1e0 cRelevel copy ctor
void  __cdecl FUN_00f9f770(void*, void*, void*);    // 0x00f9f770 CopyRelevels(first,last,dest)
void  __cdecl FUN_00fa47b0();                       // 0x00fa47b0 RelevelVector::DoInsertValue
void  __cdecl FUN_00fa6a00();                       // 0x00fa6a00 relevel push_back
void  __cdecl FUN_00fa3c10();                       // 0x00fa3c10 ApplyModelFootprint
void  __cdecl FUN_00f9a7c0();                      // 0x00f9a7c0 RenderLightingRegion
void  __cdecl FUN_00a730c0();                       // 0x00a730c0 vector<T*>::resize
void  __cdecl FUN_00473270();                       // 0x00473270 vector reserve helper
void* __cdecl FUN_0067dd80();                       // 0x0067dd80 SP::ModelManager
void  __cdecl FUN_00537dc0();                       // 0x00537dc0 cSPTransformOps::Assign
void  __cdecl FUN_0041cb40();                       // 0x0041cb40 Matrix3 copy
void  __cdecl FUN_00576650();                       // 0x00576650 GetImageResource
bool* __cdecl FUN_0041e920();                       // 0x0041e920 Property::GetBool
int*  __cdecl FUN_0041e990();                       // 0x0041e990 Property::GetInt
void* __cdecl FUN_00fa28b0();                       // 0x00fa28b0 decal factory (effect,xform,scale)
void* __cdecl FUN_00fa2920();                       // 0x00fa2920 decal factory w/ belt index
void  __cdecl FUN_00fa23d0();                       // 0x00fa23d0 remove node from region
void* __cdecl FUN_00b96600();                       // 0x00b96600 vector<T*> slow push_back
void  __cdecl FUN_006ba870();                       // 0x006ba870 XForm2::Apply
void  __cdecl FUN_007c4dd0();                       // 0x007c4dd0 cViewer::Init
void  __cdecl FUN_007c3cc0();                       // 0x007c3cc0 cViewer::Clear
void  __cdecl FUN_007c3cb0();                       // 0x007c3cb0 cViewer::SetTexture
void  __cdecl FUN_007c3c20();                       // 0x007c3c20 cViewer::SetClearColor
void  __cdecl FUN_007c4a60();                       // 0x007c4a60 cViewer::SetViewport
bool  __cdecl FUN_006a0ae0(void*, uint32_t, void*, void*); // 0x006a0ae0 vector reserve wrapper
void  __cdecl PinModelsToTerrain_00f99520();        // 0x00f99520 PinModelsToTerrain (alias: the module defines FUN_00f99520 with other types)
void  __cdecl SetDirty_00fbaf10();                  // 0x00fbaf10 (alias, see above)
void  __cdecl SetDirty_00fbaf50();                  // 0x00fbaf50
typedef void  (__thiscall *TV0)(void*);
typedef void* (__thiscall *TV0p)(void*);
typedef bool* (__thiscall *TV0bp)(void*);
typedef int*  (__thiscall *TV0ip)(void*);
typedef void  (__thiscall *TV1)(void*, void*);
typedef void  (__thiscall *TV1i)(void*, int);
typedef void  (__thiscall *TV1u)(void*, uint32_t);
typedef void* (__thiscall *TV1p)(void*, void*);
typedef char  (__thiscall *TV1c)(void*, void*);
typedef void  (__thiscall *TV2)(void*, void*, void*);
typedef char  (__thiscall *TV2c)(void*, uint32_t, void**);
typedef char  (__thiscall *TV3c)(void*, void*, int, void*);
typedef void* (__thiscall *TV3pi)(void*, void*, void*, int);
typedef void* (__thiscall *TV3pf)(void*, void*, void*, float);
typedef void* (__thiscall *TV4pf)(void*, void*, void*, float, int);
typedef void  (__thiscall *TV5pb)(void*, void*, void*, void*, void*, int);
typedef void* (__thiscall *TVo7)(void*, void*, int, int, int, int, int, int);
typedef void  (__thiscall *TV3n)(void*, uint32_t, uint32_t, const char*);
typedef void* (__thiscall *TV3ui)(void*, uint32_t, uint32_t, void*);
struct Matrix3_s00fa_6480 { float m[9]; };
struct XForm2 {                          // SP::cSPTransform, 0x38 bytes
  uint16_t mFlags, mModCount;
  float mX, mY, mZ, mScale;
  Matrix3_s00fa_6480 mM;
};
struct Color4 { float r, g, b, a; };
class cTerrainSphere_s00fa_6480 {
 public:
  void* AddLightingRegion(void* param);
  void  UpdateLightingRegions(void* param);
  void* CreateDecal(int type, void* def, void* xform, float scale);
  uint32_t AddModelFootprint(const void* xform, void* props);
  void  ClearRelevels();
  void  ReleaseBackgroundModels();
  void  AddModelsAndEffects();
  uint32_t AddPlayerModification(void* a, void* b, void* c);  // 0x00fa7220 (cTerrainSphere::AddPlayerModification)
  void  ClearPlayerModifications();
};
#define SELF      ((char*)this)
#define PTRV(off) (*(void**)(SELF + (off)))
#define INTV_s00fa_6480(off) (*(int*)(SELF + (off)))
#define U8V(off)  (*(uint8_t*)(SELF + (off)))
struct ReserveOut { void* mData; int mCount; };
// ---- items of slice s00fa6480 end

// ---- items of slice s00fa86c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedIncrement)
#pragma intrinsic(_InterlockedDecrement)
struct cProperty_s00fa_86c0;
struct cTerrainMapU32;
struct cTerrainLevelInfo;
struct cSPTransform_s00fa_86c0;
struct cRelevelEntry;
struct cFootprintEntry;
struct Allocator_s00fa_86c0 { const char* mpName; };
struct cProperty_s00fa_86c0 {
    virtual void v00() {}
    virtual void Release() {}                       // +0x04
    virtual void v08() {} virtual void v0c() {}
    virtual void v10() {} virtual void v14() {} virtual void v18() {} virtual void v1c() {}
    virtual void v20() {}
    virtual bool v24(void* context, cProperty_s00fa_86c0** ioProperty);   // +0x24
    char pad04[4];
    int mCount;                                     // +0x08
    char pad0c[4];
    uint16_t mFlags;                                // +0x10
    uint16_t mId;                                   // +0x12
};
struct PropertyManager_s00fa_86c0 {
    virtual void v00() {} virtual void v04() {} virtual void v08() {} virtual void v0c() {}
    virtual void v10() {} virtual void v14() {} virtual void v18() {} virtual void v1c() {}
    virtual void v20() {} virtual void v24() {} virtual void v28() {}
    virtual bool GetProperty(int key1, int key2, cProperty_s00fa_86c0** out);   // +0x2c
};
namespace SP {
 PropertyManager_s00fa_86c0* PropertyManager_s00fa_86c0();   // 0x0067de30
}
void** FUN_006f43e0(void** first, void** last, void** dest);   // 0x006f43e0 (copy dispatch)
struct TextureVec {
    void** mpBegin;         // +0x00
    void** mpEnd;           // +0x04
    void** mpCapacity;      // +0x08
    Allocator_s00fa_86c0 mAlloc;       // +0x0c
    void reserve(unsigned count);                // 0x004e0880
    void DestroyRange(void** first, void** last);  // 0x0070f520
    // erase(begin, end): move nothing, destroy the range, then drop it off the end
    void clear() {
        void** first = mpBegin;
        void** last = mpEnd;
        void** newEnd = FUN_006f43e0(last, mpEnd, first);
        DestroyRange(newEnd, mpEnd);
        mpEnd -= (last - first);
    }
};
struct PropRef {
    cProperty_s00fa_86c0* mpProperty;
    PropRef() : mpProperty(0) {}
    void reset() {
        cProperty_s00fa_86c0* p = mpProperty;
        if (p) {
            mpProperty = 0;
            p->Release();
        }
    }
};
struct cRelevelEntry {
    char pad00[0x98];
    int mPropertyKeyA;      // +0x98
    char pad9c[4];
    int mPropertyKeyB;      // +0xa0
    char padA4[8];
};
struct cFootprintEntry {
    int mKey;               // +0x00
    int mUnused;            // +0x04
    int mKey2;              // +0x08
};
struct cTerrainLevelInfo {
    char pad00[8];
    int mCount;             // +0x08
};
struct cTerrainMapU32 {
    void BlendMapEdges();   // 0x00f8fe60
};
struct TerrainConfig {
    char pad00[8];
    cTerrainLevelInfo* mpLevel;   // +0x08
    cTerrainMapU32* mpMap;        // +0x0c
    char pad10[0x24];
    float mF34;                   // +0x34  cull radius bias
    float mF38;                   // +0x38  cell scale
};
struct cDecalManager {
    int CreateDecal(int a, int b, int c, float d);   // 0x00fa6a50
};
struct Vector4 {
    float x, y, z, w;
    Vector4() {}
    Vector4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};
int FUN_00f8b2b0(cTerrainLevelInfo* level, cTerrainMapU32* map, int index,
                 float f34, float f38, float width,
                 float x0, float y0, float x1, float y1);          // 0x00f8b2b0
struct RefObj_s00fa_86c0 {
    virtual void Destroy(int del);
    volatile long mnRefCount;                                   // +0x04
};
struct cJob_s00fa_86c0 {
    void* fn;                       // +0x00
    unsigned arg;                   // +0x04
    char pad[0x10];
    int flag;                       // +0x18
    int Release();                  // 0x00690120
    void Queue();                   // 0x006909b0
};
struct IRef {
    virtual void AddRef();
    virtual void Release();
};
struct IMeshBuilder : IRef {
    virtual void s2(), s3(), s4(), s5(), s6(), s7(), s8(), s9(), s10(), s11();
    virtual void s12(), s13(), s14(), s15(), s16(), s17(), s18(), s19(), s20(), s21();
    virtual void s22(), s23(), s24(), s25(), s26(), s27(), s28(), s29(), s30(), s31();
    virtual void s32(), s33(), s34(), s35(), s36(), s37(), s38(), s39(), s40(), s41();
    virtual void s42();
    virtual RefObj_s00fa_86c0* GetMesh();                                  // +0xac
};
struct LockInfo { void* data; int a, b, c, d, e, f; };
struct Tex {
    char pad[0x12];
    unsigned char level;                                        // +0x12
    int  Lock(int mode, int zero, LockInfo* out);               // 0x011ef750
    void Unlock(LockInfo* info);                                // 0x011ef880
};
struct TexObj { Tex* tex; unsigned flags; };
struct ImpostorState {
    void Reset();                                               // 0x00f99ff0
};
struct cTerrainSphere_s00fa_86c0 {
    virtual void v00() {} virtual void v04() {} virtual void v08() {} virtual void v0c() {}
    virtual void v10() {} virtual void v14() {} virtual void v18() {} virtual void v1c() {}
    virtual void v20() {} virtual void v24() {} virtual void v28() {} virtual void v2c() {}
    virtual void v30() {} virtual void v34() {} virtual void v38() {} virtual void v3c() {}
    virtual void v40() {} virtual void v44() {} virtual void v48() {}
    virtual bool v4c(int level);                    // +0x4c
    char pad04[4];
    cDecalManager* mDecalManager;                   // +0x08
    char pad0c[0x0c];                               // +0x0c
    unsigned keyInstance;                           // +0x18
    unsigned keyType;                               // +0x1c
    unsigned keyGroup;                              // +0x20
    char pad24[8];                                  // +0x24
    TerrainConfig* mConfig;                         // +0x2c
    char pad30[0x740];
    cRelevelEntry* mpRelevelBegin;                  // +0x770
    cRelevelEntry* mpRelevelEnd;                    // +0x774
    char pad778[0x34];
    int mExtraCount;                                // +0x7ac
    cFootprintEntry* mpExtra;                       // +0x7b0
    char pad7b4[0x6c];
    float mRects[6][4];                             // +0x820
    char pad880[4];                                 // +0x880
    TexObj* faceTex[3];                             // +0x884
    void* res3;                                     // +0x890
    cJob_s00fa_86c0* mJob;                          // +0x894
    unsigned f898;                                  // +0x898
    unsigned f89c;                                  // +0x89c
    ImpostorState* mImpostorState;                  // +0x8a0
    unsigned f8a4;                                  // +0x8a4
    unsigned f8a8;                                  // +0x8a8

    void RequestModelFootprint(cProperty_s00fa_86c0* property, TextureVec& out);  // 0x00fa5ee0
    void BuildTerrain(const uint8_t* data);                            // 0x00fa75f0
    void CollectFootprintTextures(TextureVec& out);                    // 0x00fa86c0
    void GenerateImpostorUpdate(int a, int b);                         // 0x00fa8850
    int  CreateDecal(int a, int b, int c, float d);                    // 0x00fa9140
    void DoDeferredUpdate();                                           // 0x00fa9170
    void BuildImpostorMesh(IMeshBuilder* b, const wchar_t* name, float scale, int flag);  // 0x00f9a040
    void PostImpostorStep(int a, int b);                                                  // 0x00fa0560
};
struct cSPTransform_s00fa_86c0 { char mData[0x38]; };
cSPTransform_s00fa_86c0* FUN_00f339d0(const cSPTransform_s00fa_86c0* first, const cSPTransform_s00fa_86c0* last,
                           cSPTransform_s00fa_86c0* dest);                  // 0x00f339d0
struct TransformVec {
    cSPTransform_s00fa_86c0* mpBegin;      // +0x00
    cSPTransform_s00fa_86c0* mpEnd;        // +0x04
    cSPTransform_s00fa_86c0* mpCapacity;   // +0x08
    Allocator_s00fa_86c0 mAlloc;           // +0x0c
    void resize(unsigned count);   // 0x0041e3b0
};
struct Rec20_s00fa_86c0 { char mData[0x14]; };
Rec20_s00fa_86c0* FUN_00951bf0_s00fa_86c0(const Rec20_s00fa_86c0* first, const Rec20_s00fa_86c0* last, Rec20_s00fa_86c0* dest);  // 0x00951bf0
struct ResponseCurve {
    Rec20_s00fa_86c0* mpBegin;         // +0x00
    Rec20_s00fa_86c0* mpEnd;           // +0x04
    Rec20_s00fa_86c0* mpCapacity;      // +0x08
    Allocator_s00fa_86c0 mAlloc;       // +0x0c
    void DoAssign(const Rec20_s00fa_86c0* first, const Rec20_s00fa_86c0* last, const void* owner);  // 0x00fa26e0
    ResponseCurve& Assign(const ResponseCurve& other);                        // 0x00fa90e0
};
// ---- items of slice s00fa86c0 end

// ---- items of slice s00fa9300 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_vtbl_BehaviorMessage;          // 0x013eb90c
extern void* g_vtbl_SlotMessage;              // 0x013eb844
extern const unsigned char kFacePerm[12];     // 0x0149040c
struct cTerrainSphere_s00fa_9300;
struct cTerrainSphereQuad_s00fa_9300;
struct cJob;
struct PropList;
namespace EA {
namespace ResourceMan {
 struct Key_s00fa_9300 { uint32_t instance, type, group; }; 
}
}
typedef EA::ResourceMan::Key_s00fa_9300 Key_s00fa_9300;
extern cTerrainSphere_s00fa_9300* g_pTerrainSphere_s00fa_9300;      // 0x016c9e5c
struct cMessageServer_s00fa_9300 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
    virtual void Post3(uint32_t id, void* msg, int a);                 // +0x14
    virtual void Post4(uint32_t id, void* msg, int a, int b);          // +0x18
};
cMessageServer_s00fa_9300* MessageServer_s00fa_9300();              // 0x0067dcc0
struct cTerrainEditor_s00fa_9300 {
    bool IsModeA();                           // 0x00f678a0
    bool IsModeB();                           // 0x00f678c0
};
cTerrainEditor_s00fa_9300* TerrainEditor_s00fa_9300();              // 0x00f48a70
struct cJob { int Release(); };
struct RectT_s00fa_9300 {
    float mLeft, mTop, mRight, mBottom;
    bool Test();                              // 0x0064e6b0
};
struct cSPTransform_s00fa_9300 {
    uint16_t mFlags, mModCount;
    float mOffset[3];
    float mScale;
    float mRotation[9];
};
struct KeyVec { Key_s00fa_9300* mpBegin; Key_s00fa_9300* mpEnd; Key_s00fa_9300* mpCapacity; uint32_t mAlloc[2]; void resize(uint32_t n); };          // 0x004548d0
struct XformVec { cSPTransform_s00fa_9300* mpBegin; cSPTransform_s00fa_9300* mpEnd; cSPTransform_s00fa_9300* mpCapacity; uint32_t mAlloc[2]; void resize(uint32_t n); };  // 0x0041e3b0
struct cTerrainPlanetData_s00fa_9300 {
    uint32_t pad[0x34 / 4];
    float mF34;                               // +0x34
};
struct SlotMessage {
    void* volatile mpVftable;                 // +0x00
    uint32_t mRefCount;                       // +0x04
    uint32_t mData08;                         // +0x08
    uint32_t mData0C;                         // +0x0c
    uint32_t mData10;                         // +0x10
    uint32_t mData14;                         // +0x14
    uint32_t mData18;                         // +0x18
    uint32_t mData1C;                         // +0x1c
    uint32_t mData20;                         // +0x20
    uint32_t mData24;                         // +0x24
    uint32_t mData28;                         // +0x28
    uint32_t mData2C;                         // +0x2c
    uint32_t mMessageId;                      // +0x30
    uint32_t mData34;                         // +0x34
    uint32_t mData38;                         // +0x38
    uint32_t mData3C;                         // +0x3c
    SlotMessage* Construct(unsigned int a);   // 0x00421c80
};
inline void MsgRelease(SlotMessage* m)
{
    (*(void(__thiscall**)(SlotMessage*))(*(uint32_t volatile*)m + 8))(m);
}
struct SlotMessageRef {                       // intrusive holder for a SlotMessage (stack slot)
    SlotMessage* mpObject;
    SlotMessage* Set(SlotMessage* p);         // 0x00572620
};
struct Elem20 { uint32_t w[5]; };
struct S20 { uint32_t v[5]; };
struct U32x3 { uint32_t a, b, c; };
struct Tail50 { uint32_t d[15]; S20 s; };
struct Blob110 {
    Elem20* mpBegin;                          // +0x00
    Elem20* mpEnd;                            // +0x04
    Elem20* mpCapacity;                       // +0x08
    uint32_t mField0C;                        // +0x0c
    Elem20* mpInline;                         // +0x10
    uint32_t mField14;                        // +0x14
    Elem20 mBuffer[7];                        // +0x18 .. +0xa4
    U32x3 mU;                                 // +0xa4
    float mB0, mB4, mB8, mBC;                 // +0xb0 .. +0xbc
    Tail50 mTail;                             // +0xc0 .. +0x110
    Blob110(const Blob110& o);
    Blob110& operator=(const Blob110& o);
    void AssignRange(const Elem20* first, const Elem20* last, const Blob110* src);   // 0x00fa26e0
    void AssignFrom(const Blob110& o);                                               // 0x00fa90e0
};
struct cITerrainSphere {
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
    virtual void FaceBegin(int a);            // +0x44
    virtual void FaceState(int a);            // +0x48
    virtual bool FaceVisible(int a);          // +0x4c
};
struct cTerrainSphere_s00fa_9300 : cITerrainSphere {
    uint8_t mF04[0x24];                       // +0x04 .. +0x28
    PropList* mpDefinition;                   // +0x28
    cTerrainPlanetData_s00fa_9300* mpPlanet;             // +0x2c
    uint8_t mPad30[0x118 - 0x30];
    cTerrainSphereQuad_s00fa_9300* mQuadsA[6];           // +0x118
    cTerrainSphereQuad_s00fa_9300* mQuadsB[6];           // +0x130
    uint8_t mPad148[0x33c - 0x148];
    uint8_t mF33C;                            // +0x33c
    uint8_t mF33D;                            // +0x33d
    uint8_t mPad33E[0x368 - 0x33e];
    uint8_t mF368;                            // +0x368
    uint8_t mF369;                            // +0x369
    uint8_t mPad36A[0x36c - 0x36a];
    uint32_t mF36C;                           // +0x36c (0/1)
    uint8_t mF370;                            // +0x370
    uint8_t mPad371[0x374 - 0x371];
    Vec4 mVec[18];                            // +0x374 .. +0x493
    Vec4 mRectB[6];                           // +0x494 .. +0x4f3
    uint8_t mPad4F4[0x770 - 0x4f4];
    uint8_t mRelevelA[0x14];                  // +0x770
    uint8_t mRelevelB[0x14];                  // +0x784
    uint8_t mRelevelC[0x14];                  // +0x798
    int mNumModels;                           // +0x7ac
    KeyVec mModelKeys;                        // +0x7b0
    XformVec mModelTransforms;                // +0x7c4
    uint8_t mPad7D8[0x814 - 0x7d8];
    uint32_t mCamOffsetY;                     // +0x814
    uint8_t mPad818[0x81c - 0x818];
    cJob* mBackgroundJob;                     // +0x81c
    Vec4 mFaceRect[6];                        // +0x820 .. +0x87f
    uint8_t mF880;                            // +0x880
    uint8_t mPad881[0x8a0 - 0x881];
    cJob* mpImpostorJob;                      // +0x8a0
    int mImpostorJobState;                    // +0x8a4
    uint8_t mPad8A8[0xa48 - 0x8a8];
    int mState;                               // +0xa48

    bool HandleMessage(uint32_t msgId, SlotMessage* msg);
    void SetModels();  // 0x00fa96d0 (cTerrainSphere::SetModels)
    void GenerateImpostorUpdate(void* a, void* b);           // 0x00fa8850
    void PinModelsToTerrain();                               // 0x00f99520
    void FinishBackgroundMap();                              // 0x00fa9170
    void ResetFaceState(int a);                              // 0x00f99ba0
    void ResetQuads();                                       // 0x00f96f90
    void ResetQuadsCaller();                                 // 0x00fa9b50
    void FaceSub0(int i, void* v);                           // 0x00fa0010
    void FaceSub1(int i, void* v);                           // 0x00fa0070
    void FaceSub2(int i, void* v);                           // 0x00fa00d0
};
struct cTerrainSphereQuad_s00fa_9300 {
    void FaceSubA(int i, void* v);            // 0x00faf140
    void FaceSubB(int i, void* v);            // 0x00faf400
    void FaceSubC(int i, void* v);            // 0x00fb0d20
};
struct TerrainSphereHandler {
    uint8_t mPad00[0x24];
    cTerrainPlanetData_s00fa_9300* mpPlanet;             // +0x24 (= sphere+0x2c)
    uint8_t mPad28[0x368 - 0x28];
    uint8_t mF368;                            // +0x368 (sphere+0x370)
    uint8_t mPad369[0x814 - 0x369];
    cJob* mBackgroundJob;                     // +0x814 (sphere+0x81c)
    Vec4 mFaceRect[6];                        // +0x818 (sphere+0x820)
    uint8_t mPad878[0x898 - 0x878];
    cJob* mpImpostorJob;                      // +0x898 (sphere+0x8a0)
    uint8_t mPad89C[0xa40 - 0x89c];
    int mState;                               // +0xa40 (sphere+0xa48)

    cTerrainSphere_s00fa_9300* Sphere() { return (cTerrainSphere_s00fa_9300*)((char*)this - 8); }
    bool HandleMessage(uint32_t msgId, SlotMessage* msg);
};
void GetPropertyAsKeyArray(PropList* list, uint32_t id, uint32_t* count, Key_s00fa_9300** out);              // 0x006a0ae0
void GetPropertyAsTransformArray(PropList* list, uint32_t id, uint32_t* count, cSPTransform_s00fa_9300** o); // 0x006a0c30
void CopyTransforms(const cSPTransform_s00fa_9300* first, const cSPTransform_s00fa_9300* last, cSPTransform_s00fa_9300* dest);     // 0x00f339d0
struct cTerrainBackgroundMapJob {
    uint8_t mPad00[0xc];
    cTerrainSphere_s00fa_9300* mpSphere;                 // +0x0c
    uint32_t mF10;                            // +0x10
    bool Update(int a);                       // 0x00fa9790 (ret 4)
};
// ---- items of slice s00fa9300 end

// ---- items of slice s00fabd60 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPVector2_s00fa_bd60
{
    float x, y;
    cSPVector2_s00fa_bd60& operator=(const cSPVector2_s00fa_bd60& v) { x = v.x; y = v.y; return *this; }
};
struct cSPVector3_s00fa_bd60
{
    float x, y, z;
    cSPVector3_s00fa_bd60() {}
    cSPVector3_s00fa_bd60(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};
struct cCubeMapCoord_s00fa_bd60 { cSPVector2_s00fa_bd60 uv; int face; };
namespace SP {
struct cBrushVertex_s00fa_bd60             // 0x1c (dev PDB)
{
    cSPVector3_s00fa_bd60 mPosition;
    cSPTexCoord mUV;
    float      mIntensity;
    float      mSize;
};
}
namespace SP {
struct cRibbonFaceVertex_s00fa_bd60        // 0x14 (dev PDB)
{
    cSPVector2_s00fa_bd60  mPos;
    cSPTexCoord mTC;
    float      mAlpha;
};
}
namespace SP {
struct cRibbonFacePoly_s00fa_bd60
{
    cRibbonFaceVertex_s00fa_bd60*  mpBegin;        // +0x00 fixed_vector<cRibbonFaceVertex,7,true>
    cRibbonFaceVertex_s00fa_bd60*  mpEnd;          // +0x04
    cRibbonFaceVertex_s00fa_bd60*  mpCapacity;     // +0x08
    uint32_t            mOverflowAllocator; // +0x0c
    cRibbonFaceVertex_s00fa_bd60*  mpPoolBegin;    // +0x10
    uint32_t            mVecPad;        // +0x14
    cRibbonFaceVertex_s00fa_bd60   mBuffer[7];     // +0x18
    cRibbonPolyInfo     mInfo;          // +0xa4
    uint32_t            mPad[4];        // +0xb0 bounds (written by ComputeBounds)
    cRibbonFaceVertex_s00fa_bd60   mPatch[4];      // +0xc0 bilinear patch (written by BuildPatch)

    void resize(int n);                 // fixed_vector::resize, 0x00fa4730
    void ComputeBounds();               // 0x00fafda0 (name guessed)
    void BuildPatch();                  // 0x00faff10 (name guessed)

    cRibbonFaceVertex_s00fa_bd60& operator[](int i) { return mpBegin[i]; }
};
}
namespace SP {
struct cRibbonPolyList_s00fa_bd60
{
    cRibbonFacePoly_s00fa_bd60* mpBegin;
    cRibbonFacePoly_s00fa_bd60* mpEnd;
    cRibbonFacePoly_s00fa_bd60* mpCapacity;
    uint32_t         mAllocator[2];

    void push_back();                   // 0x00fab230 (default-constructed element)
    cRibbonFacePoly_s00fa_bd60& back() { return *(mpEnd - 1); }
};
}
namespace SP {
void ClipBrushPoly(cBrushVertex_s00fa_bd60* verts, int* numVerts, const cSPVector3_s00fa_bd60* plane);   // 0x00fc2c70
}
namespace SP {
extern cSPVector3_s00fa_bd60 gCubeFacePlanes_s00fa_bd60[6][4];   // 0x016d6fa8: 4 edge planes per cube face
}
namespace SP {
static __forceinline cCubeMapCoord_s00fa_bd60 ToCubeMapCoord_s00fa_bd60(const cSPVector3_s00fa_bd60& p)
{
    cCubeMapCoord_s00fa_bd60 c;
    float x = p.x;
    float y = p.y;
    float z = p.z;
    float ax = fabsf(x);
    float ay = fabsf(y);
    float az = fabsf(z);
    if (az >= ax && az >= ay)
    {
        c.uv.x = (x / z + 1.0f) * 0.5f;
        c.uv.y = (y / az + 1.0f) * 0.5f;
        c.face = (z >= 0.0f) ? 0 : 1;
    }
    else if (ay >= ax)
    {
        c.uv.x = (z / y + 1.0f) * 0.5f;
        c.uv.y = (x / ay + 1.0f) * 0.5f;
        c.face = (y >= 0.0f) ? 4 : 5;
    }
    else
    {
        c.uv.x = (y / x + 1.0f) * 0.5f;
        c.uv.y = (z / ax + 1.0f) * 0.5f;
        c.face = (x >= 0.0f) ? 2 : 3;
    }
    return c;
}
}
namespace SP {
static __forceinline cSPVector3_s00fa_bd60 Normalized_s00fa_bd60(const cSPVector3_s00fa_bd60& v)
{
    float x = v.x;
    float inv = 1.0f / sqrtf(x * x + v.y * v.y + v.z * v.z);
    return cSPVector3_s00fa_bd60(inv * x, v.y * inv, inv * v.z);
}
}
namespace SP {
void __cdecl EASTL_allocator_deallocate(void* p);   // 0x00f47380
}
namespace SP {
struct cRibbonPathPoint         // 0x24
{
    float x, y, z;
    float mPad[6];
};
}
namespace SP {
struct cRibbonPath
{
    uint32_t           mPad;
    cRibbonPathPoint*  mpBegin;     // +0x04
    cRibbonPathPoint*  mpEnd;       // +0x08
};
}
namespace SP {
struct cFaceQuad
{
    void AddRibbonPolys(cRibbonPolyList_s00fa_bd60* list);     // 0x00fb7920 (name guessed)
};
}
namespace SP {
struct cLocalPolyList : cRibbonPolyList_s00fa_bd60
{
    cLocalPolyList() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    ~cLocalPolyList()
    {
        for (cRibbonFacePoly_s00fa_bd60* p = mpBegin; p < mpEnd; ++p)
        {
            if (p->mpBegin && p->mpBegin != p->mpPoolBegin)
                EASTL_allocator_deallocate(p->mpBegin);
        }
        if (mpBegin && ((int*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
    }
};
}
namespace SP {
struct cRibbonBuilder
{
    char       mPad[0x118];
    cFaceQuad* mFaceQuads[6];       // +0x118

    void BuildRibbon(int ribbonID, cRibbonPath* path);
};
}
// ---- items of slice s00fabd60 end

// ---- items of slice s00fac5c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void FreeArr(void* p);                  // 0x00f47380, operator delete[] (cdecl)
struct Point {                                  // 0x24 bytes
    float x, y, z;                              // +0x0
    float scale;                                // +0xc
    float pad[5];
};
struct Strand {
    uint32_t pad0;
    Point* mpBegin;                             // +0x4
    Point* mpEnd;                               // +0x8
};
struct BuildElem {
    void* mpData;                               // +0x0
    uint32_t pad[3];
    void* mpInline;                             // +0x10
    uint32_t rest[(0x110 - 0x14) / 4];
};
struct FaceBuilder {
    BuildElem* mpBegin;
    BuildElem* mpEnd;
    BuildElem* mpCapacity;
    uint32_t mAlloc[2];

    void Init() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    void Destroy()
    {
        BuildElem* last = mpEnd;
        for (BuildElem* p = mpBegin; p < last; ++p) {
            void* d = p->mpData;
            if (d != 0 && d != p->mpInline) FreeArr(d);
        }
        BuildElem* b = mpBegin;
        if (b != 0 && ((int*)b)[-1] != 0) FreeArr(b);
    }
    // 0x00fab2b0: eax = pos[4][3], stack = uv[4][2], alpha[4], info{len, segLen, strand}.
    // (The original passes pos in EAX; here it is the first stack argument.)
    void AddQuad(const float* pos, const float* uv, const float* alpha, const float* info);
};
struct FaceTree {
    char pad[8];
    void Clear();                               // 0x00fb7720
    void Flush(FaceBuilder* b);                 // 0x00fb78f0 (ret 4)
};
struct SPVectorU32 {
    uint32_t* mpBegin;                          // +0x0
    uint32_t* mpEnd;                            // +0x4
    uint32_t* mpCap;                            // +0x8

    void DoInsertValue(uint32_t* pWhere, const uint32_t& value);   // 0x004558a0
};
struct StrandMesh {
    void** mpVtbl;                              // +0x0
    char pad0[0x118 - 4];                       // +0x4
    FaceTree* mFaces[6];                        // +0x118
    char pad1[0x2b8 - 0x130];
    Strand** mpStrands;                         // +0x2b8
    Strand** mpStrandsEnd;                      // +0x2bc
    Strand** mpStrandsCap;                      // +0x2c0
    char pad2[0x2cc - 0x2c4];                   // +0x2c4
    SPVectorU32 mFree;                          // +0x2cc

    void Build();
    int StrandCount() { return mpStrandsEnd - mpStrands; }
    uint32_t AllocStrandIndex();                // 0x00fa3ba0
    void BuildRibbon(uint32_t index, Strand* p);   // 0x00fabd60
    uint32_t AddStrand(Strand* p);              // 0x00facef0
    void RemoveStrand(uint32_t index);          // 0x00facf20
};
struct Vertex3DVec {
    void* mpBegin;                              // +0x0
    void* mpEnd;                                // +0x4
    void* mpCap;                                // +0x8

    void CopyUninit(void* pBegin, void* pEnd);  // 0x00b85500
};
struct DecalRecord {
    void* mpOwner;                              // +0x0
    Vertex3DVec mVertices;                      // +0x4
};
struct FaceQuad {
    void AddDecal(void* pOwner);                // 0x00fb4a50
    void RemoveDecal(void* pOwner);             // 0x00fb3660
};
struct QuadMesh {
    char pad[0x118];
    FaceQuad* mFaces[6];                        // +0x118
};
struct DecalHost {
    char pad0[0x78];                            // +0x0
    QuadMesh* mpMesh;                           // +0x78
    char pad1[0xb8 - 0x7c];                     // +0x7c
    uint32_t mFlags;                            // +0xb8

    void AttachDecal();                         // 0x00facfc0
    void DetachDecal();                         // 0x00fad000
};
static const float kEps_s00fa_c5c0 = 1e-8f;
// ---- items of slice s00fac5c0 end

// @ 0x00f96370
void cTerrainOverlay::ToggleFlag()
{
    int idx = mVal36c;
    *((char*)this + idx + 0x368) = 0;
    mVal36c = 1 - mVal36c;
}

// @ 0x00f96390
unsigned HashTerrainDesc(void* desc, void* out)
{
    char* d = (char*)desc;
    int v4, v8, v12;
    if ((d[0] >> 2) & 1) {
        v4 = (int)*(float*)(d + 4);
        v8 = (int)*(float*)(d + 8);
        v12 = (int)*(float*)(d + 0xc);
    } else {
        v4 = v8 = v12 = 0;
    }
    int v16;
    if (*(float*)(d + 0x10) < 1.0f)
        v16 = (int)(*(float*)(d + 0x10) * SP::K_1div3);
    else
        v16 = 0;

    int arr[9];
    if ((d[0] >> 1) & 1) {
        for (int i = 0; i < 9; ++i)
            arr[i] = (int)(*(float*)(d + 0x14 + i * 4) * SP::K_1div3);
    } else {
        for (int i = 0; i < 9; ++i)
            arr[i] = 0;
    }
    (void)v16;

    unsigned h = SP::Sub_932e50(&v4, 0x34, 0x811c9dc5);
    return SP::Sub_932e50(out, 0x0c, h);
}

// @ 0x00f964a0
char cTerrainOverlay::ClearSlot()
{
    mVal08 = 0;
    return 1;
}

// 0x00f964b0 (byte-exact lifted version: match/slices/s00f964b0/s00f964b0.cpp)
int __fastcall ReleaseRef_s00f9_55f0(int* self)
{
    int* p = (int*)((char*)self + 4);
    int old;
    old = _InterlockedExchangeAdd((long volatile*)p, -1);
    if (old - 1 == 0) {
        *(int*)((char*)self + 4) = 1;
        SP::Sub_f47380(self);
    }
    return old;
}

// @ 0x00f964f0
void* cDynCast::Cast(unsigned id)
{
    if (id == 0x479dcb2)
        return (char*)this - 0x10;
    if (id == 0x2269ed1 || id == 0xee3f516e) {
        if (this != 0)
            return this;
    }
    return 0;
}

// 0x00f96520 (byte-exact lifted version: match/slices/s00f96520/s00f96520.cpp)
void cTerrainSphere_s00f9_55f0::RemoveFromEffectsSystem()
{
    int* mgr = SP::Sub_67ddd0();
    SP::Sub_6f24a0((void*)SP::g_16c9f50, 0);
    void** vt = (void**)*mgr;
    typedef void (__thiscall *Fn78)(void*, int, int, unsigned);
    typedef void (__thiscall *Fn88)(void*, int, int, unsigned);
    typedef void (__thiscall *Fn20)(void*, int, int);
    Fn78 f78 = (Fn78)vt[0x78/4];
    Fn88 f88 = (Fn88)vt[0x88/4];
    Fn20 f20 = (Fn20)vt[0x20/4];

    f78(mgr, 0, 0, 0x2e892928);
    f78(mgr, 0, 0, 0x2e892929);
    f78(mgr, 0, 0, 0x2e89292a);
    f78(mgr, 0, 0, 0x2e89292b);
    f78(mgr, 0, 0, 0x03598109);

    f88(mgr, 0, 0, 0x00f86c22);
    f88(mgr, 0, 0, 0x00f86c06);
    f88(mgr, 0, 0, 0x00f86c19);
    f88(mgr, 0, 0, 0x016f280b);
    f88(mgr, 0, 0, 0x01acdb9c);
    f88(mgr, 0, 0, 0x01acdb88);
    f88(mgr, 0, 0, 0x01acdb92);
    f88(mgr, 0, 0, 0x01acdba5);
    f88(mgr, 0, 0, 0x01c8a626);
    f88(mgr, 0, 0, 0x01c8a610);
    f88(mgr, 0, 0, 0x01c8a61e);
    f88(mgr, 0, 0, 0x01c8a62f);
    f88(mgr, 0, 0, 0x0276b1e8);
    f88(mgr, 0, 0, 0x02c9c762);
    f88(mgr, 0, 0, 0x02c9c763);
    f88(mgr, 0, 0, 0x02c9c764);
    f88(mgr, 0, 0, 0x02c9c765);
    f88(mgr, 0, 0, 0x02c9c766);
    f88(mgr, 0, 0, 0x02c9c767);
    f88(mgr, 0, 0, 0x02e831a1);
    f88(mgr, 0, 0, 0x02e831af);
    f88(mgr, 0, 0, 0x02f7dcd2);

    f20(mgr, 0, -1);
    f20(mgr, 0, 7);
    f20(mgr, 0, 8);
}

struct cGridBounds {
    float GetC();      // 0x0097ef00
    int GetMinB();     // 0x00fb7bb0
    int GetMinC();     // 0x00fb7bc0
};

// @ 0x00f967d0
void* cGridTool::GetExtents(int* a, int* b, int* c)
{
    cGridBounds* bounds = *(cGridBounds**)((char*)this + 0x20c);
    *a = SseFloorToInt(bounds->GetC() * SP::K_140);
    *b = ((cGridBounds*)*(void**)((char*)this + 0x20c))->GetMinB();
    int minC = ((cGridBounds*)*(void**)((char*)this + 0x20c))->GetMinC();
    *c = minC;
    return (void*)minC;
}

// @ 0x00f977c0
void cTerrainSphere_s00f9_77c0::AddToEffectsSystem()
{
    void* mgr = FUN_0067ddd0();
    typedef void* (__thiscall *TGet)(void*, uint32_t, int);
    TGet get = (TGet)(*(void***)mgr)[0x7c / 4];
    void* found = get(mgr, 0x2e892928, 0);
    if (!found)
        return;

    PlanetHeader* planet = (PlanetHeader*)mpPlanet;
    float f34 = planet->m34;
    float f38 = planet->m38;
    float f3c = planet->m3c;

    StateMgr* sm = (StateMgr*)mpStateMgr;
    sm->FUN_00fb9aa0(f34, f38, f3c * f38);

    float dist = f34 * C_1471064;
    float add = f3c * C_1471064;

    void* e;
    e = get(mgr, 0x2e892928, 0);
    *(float*)((char*)e + 0x0c) = dist;
    *(float*)((char*)e + 0x10) = add;
    *(float*)((char*)e + 0x14) = -dist;
    e = get(mgr, 0x2e892929, 0);
    *(float*)((char*)e + 0x0c) = dist;
    *(float*)((char*)e + 0x10) = add;
    *(float*)((char*)e + 0x14) = dist;
    e = get(mgr, 0x2e89292b, 0);
    *(float*)((char*)e + 0x10) = add;
    *(float*)((char*)e + 0x14) = dist;
    *(float*)((char*)e + 0x0c) = dist;
    e = get(mgr, 0x2e89292a, 0);
    *(float*)((char*)e + 0x0c) = dist + add;
    e = get(mgr, 0x3598109, 0);
    *(float*)((char*)e + 0x0c) = f38;
    e = get(mgr, 0x4fe7337, 0);
    *(float*)((char*)e + 0x0c) = f38;
    m360 = f34;
    m364 = f3c;
    mFlag111 = 0;
}

// @ 0x00f97960
bool cTerrainSphere_s00f9_77c0::QuadDetailTest(const ViewFrame* frame, const float* verts, float* outDist)
{
    cPropertyList_s00f9_77c0* props = (cPropertyList_s00f9_77c0*)g_sAppProps;
    if (props->GetDescription(0x2fbb4880))
        return true;

    float resf = (float)(int)(0x200 / m1d4);

    float f88 = frame->m88;
    float f8c = frame->m8c;
    float fx = frame->m34;
    float fy = frame->m38;
    float fz = frame->m3c;
    float f30 = frame->m30;

    AppHeader* app = (AppHeader*)(*(uint8_t**)&g_sAppProps)[0x3c];
    float t84 = app->m84;
    float t88 = app->m88;
    float t8c = app->m8c;

    float scale = (f8c + f88);
    float dx = verts[0] - fx * scale * C_1471064;
    float dy = verts[1] - fy * scale * C_1471064;
    float dz = verts[2] - fz * scale * C_1471064;
    *outDist = sqrtf(dz * dz + dy * dy + dx * dx);

    if (f30 < C_1485720 / resf + C_13f9428)
        goto tail;

    {
        float lim = (float)(sqrt(2.0) * C_15b118c * f30);
        float len = sqrtf(verts[0] * verts[0] + verts[1] * verts[1] + verts[2] * verts[2]) + C_13ec4b8;
        float lo = len < f88 ? f88 : len;
        if (f8c < lo)
            lo = f8c;
        float d = (verts[1] * fy + verts[2] * fz + verts[0] * fx) / len;
        if (d <= C_13eb1bc)
            d = C_13eb1bc;
        if (C_1485720 <= d)
            d = C_1485720;
        float ang = FUN_00f63e10(d);
        float w = ang - lim;
        if (!(0.0f < w))
            w = 0.0f;
        float band = (len - lo) * t8c;
        float lod = sqrtf(w * lo * (w * lo) + band * band) / f30;
        const_cast<ViewFrame*>(frame)->m68 = lod;
        if (lod < t84)
            return false;
    }
tail:
    {
        ViewFrame* vf = const_cast<ViewFrame*>(frame);
        float f64 = C_1485720;
        if (vf->m04) {
            float v = (t84 - *(float*)((char*)vf->m04 + 0x68)) / t88;
            f64 = v < 0.0f ? 0.0f : (C_1485720 < v ? C_1485720 : v);
        }
        vf->m64 = f64;
    }
    return true;
}

// @ 0x00f97e60
bool cTerrainSphere_s00f9_77c0::RenderJobPass(uint32_t arg)
{
    cViewer_s00f9_77c0* job = mpRenderJob;
    if (!mSingleStep) {
        if (!job)
            return true;
        long long ms = (long long)mTimeLimitMs;
        cLimitStopwatch sw;
        sw.Construct(4, false);
        sw.SetTimeLimit((uint32_t)ms, true);
        long long now;
        for (;;) {
            QueryPerformanceCounter_imp(&now);
            if ((int)(sw.mnEndTime - now) < 0)
                break;
            if (!mpRenderJob)
                break;
            if (!job->Update())
                return false;
        }
        return true;
    }
    if (job && !job->Update())
        return false;
    return true;
}

// @ 0x00f97f50
void cTerrainSphere_s00f9_77c0::DrawSkyQuads(uint32_t a, uint32_t b)
{
    uint32_t n = (uint32_t)(mpQuadEnd - mpQuadBegin);
    if ((int)n <= 0)
        return;
    int off = 0;
    uint32_t cnt = n;
    do {
        char* e = (char*)mpQuadBegin + off;
        void* obj = *(void**)e;
        float key = *(float*)(e + 0x04);
        uint32_t* flags = (uint32_t*)(e + 0x0c);
        if (((cPropertyList_s00f9_77c0*)g_sAppProps)->GetDescription(0x63ae57a)) {
            uint32_t hit = 0;
            if (b & 0x6000000)
                hit = (uint32_t)((tFrust)(void*)&FUN_00700120)(mFrustum, 0, (char*)obj + 0x70,
                                             (char*)obj + 0x7c, 0);
            *flags = hit;
        } else {
            *flags = 0;
        }
        if (!(*flags & 0x40)) {
            *(float*)((char*)obj + 0x64) = key;
            ((tq2)(void*)&FUN_00fb66d0x)(obj, mpViewer, a, b);
        }
        off += 0x10;
    } while (--cnt);
}

// @ 0x00f98020
void cTerrainSphere_s00f9_77c0::RenderWater(uint32_t a, uint32_t b)
{
    if ((g_16ca5a0 & 1) == 0)
        g_16ca5a0 |= 1;

    cPropertyList_s00f9_77c0* props = (cPropertyList_s00f9_77c0*)g_sAppProps;

    uint32_t buf[4];
    FUN_00fb9ad0(buf);
    g_16ca590[0] = buf[0];
    g_16ca590[1] = buf[1];
    g_16ca590[2] = buf[2];
    g_16ca590[3] = buf[3];

    FUN_00777ae0(0x250, g_16ca590, 0);
    FUN_00777ae0(0x255, (const void*)1, 0);

    uint32_t type;
    uint32_t t = GetTerraformPlanetType(FUN_00fb8a00(GetViewFrame()));
    if (t & 1)
        type = 2;
    else if (t == 2)
        type = 4;
    else
        type = (t == 4 ? 1 : 0) + 2;

    if (props->GetDescription(0xab73e4f9)) {
        uint32_t n = (uint32_t)(mpQuadEnd - mpQuadBegin);
        if ((int)n > 0) {
            int off = 0;
            uint32_t cnt = n;
            do {
                char* e = (char*)mpQuadBegin + off;
                if (!(*(uint32_t*)(e + 0x0c) & 0x40))
                    ((tq3)(void*)&FUN_00fb6850x)(*(void**)e, mpViewer, a, type, b);
                off += 0x10;
            } while (--cnt);
        }
    }
    FUN_00777ae0(0x255, 0, 0);
    FUN_00777ae0(0x250, 0, 0);
}

// @ 0x00f981d0
void cTerrainSphere_s00f9_77c0::RenderAtmosphere(uint32_t a, uint32_t b)
{
    uint32_t want = g_16c9e78;
    uint32_t have = g_16f65a0;
    if (!have || !rw_VertexDescriptor_AreEqual((void*)have, (void*)want))
        g_16f9110 |= 0x100000;
    g_16f65a0 = want;
    rw_VertexDescriptor_SetActive((void*)want);

    uint32_t n = (uint32_t)(mpQuad3End - mpQuad3Begin);
    if ((int)n > 0) {
        QuadEntry*& base = mpQuad3Begin;
        int off = 0;
        uint32_t cnt = n;
        do {
            char* e = (char*)base; e += off;
            ((tq2)(void*)&FUN_00fb6cd0x)(*(void**)e, mpViewer, a, b);
            off += 0x10;
        } while (--cnt);
    }
}

// @ 0x00f98290
bool cTerrainSphere_s00f9_77c0::UpdateAboveRaster(int face, const float* rect, uint32_t a3, uint32_t a4)
{
    float l = rect[0], t = rect[1], r = rect[2], b = rect[3];
    cView* view = GetView();
    for (int fi = 0; fi < 4; ++fi) {
        cView::Block* blk = &view->mBlocks[fi];
        uint32_t cnt = (uint32_t)(((char*)blk->mEnd - (char*)blk->mBegin) >> 2);
        for (uint32_t i = 0; i < cnt; ++i) {
            void** slot = (void**)((char*)blk->mBegin + i * 4);
            if (!*slot)
                continue;
            Raster* raster = (Raster*)*slot;
            if (!((raster->mB8 >> 3) & 1))
                continue;
            float box[4];
            if (!FUN_00fad140(raster, face, box))
                continue;
            if (!(r < box[0] && t > box[2] && l < box[3] && b > box[1]))
                continue;
            if (t > box[0]) t = box[0];
            if (l > box[2]) l = box[2];
            if (r < box[3]) r = box[3];
            if (b < box[1]) b = box[1];
        }
    }
    if (l != t && r != b) {
        void* editor = FUN_00f48a70();
        uint32_t* rectId = (uint32_t*)(g_16ca3d4 + face * 8);
        float one = C_1485720;
        if (!FUN_00f6a960(editor, rectId, face, l, t, r, b, 0, 0, one, one, (void*)a4))
            return false;
    }
    if (!FUN_00f678a0()) {
        for (int fi = 0; fi < 4; ++fi) {
            cView::Block* blk = &view->mBlocks[fi];
            uint32_t cnt = (uint32_t)(((char*)blk->mEnd - (char*)blk->mBegin) >> 2);
            for (uint32_t i = 0; i < cnt; ++i) {
                void** slot = (void**)((char*)blk->mBegin + i * 4);
                if (!*slot)
                    continue;
                Raster* raster = (Raster*)*slot;
                if (!((raster->mB8 >> 3) & 1))
                    continue;
                float box[4];
                if (!FUN_00fad140(raster, face, box))
                    continue;
                if (!(l < box[2] && r < box[3] && t > box[0] && b > box[1]))
                    continue;
                if (!FUN_00fad550(raster, face, a4))
                    return false;
            }
        }
    }
    return true;
}

// @ 0x00f98530
void cTerrainSphere_s00f9_77c0::DrawAtmoQuads(uint32_t a, uint32_t b)
{
    if (((cPropertyList_s00f9_77c0*)g_sAppProps)->GetDescription(0x4badc321)) {
        if (!FUN_007c4fd0(this))
            return;
        uint32_t n = (uint32_t)(mpQuadEnd - mpQuadBegin);
        if ((int)n > 0) {
            int off = 0;
            uint32_t cnt = n;
            do {
                char* e = (char*)mpQuadBegin + off;
                *(float*)((char*)*(void**)e + 0x64) = *(float*)(e + 0x04);
                ((tq4)(void*)&FUN_00fb6e00x)(*(void**)e, a, b, 0);
                off += 0x10;
            } while (--cnt);
        }
    } else {
        if (!FUN_007c4fd0(this))
            return;
        uint32_t n = (uint32_t)(mpQuad2End - mpQuad2Begin);
        if ((int)n > 0) {
            int off = 0;
            uint32_t cnt = n;
            do {
                char* e = (char*)mpQuad2Begin + off;
                *(float*)((char*)*(void**)e + 0x64) = *(float*)(e + 0x04);
                ((tq4)(void*)&FUN_00fb6e00x)(*(void**)e, a, b, 0);
                off += 0x10;
            } while (--cnt);
        }
    }
    FUN_007c3c10(this);
}

// @ 0x00f98620
void cTerrainSphere_s00f9_77c0::MergeFaceBox(int face, float l, float t, float r, float b)
{
    float* p = mFaceBox[face];
    if (p[0] == p[2] || p[1] == p[3]) {
        p[0] = l;
        p[1] = t;
        p[2] = r;
        p[3] = b;
    } else {
        float v, w;
        v = p[0]; w = l;
        if (!(w > v)) v = w;
        p[0] = v;
        v = p[1]; w = t;
        if (!(w > v)) v = w;
        p[1] = v;
        v = p[2]; w = r;
        if (!(v > w)) v = w;
        p[2] = v;
        v = p[3]; w = b;
        if (!(v > w)) v = w;
        p[3] = v;
    }
}

// @ 0x00f986f0
int __fastcall FUN_00f986f0(TerrainSphere* self, void* dummy, int index)
{
    Vec4 zero = {0.0f, 0.0f, 0.0f, 0.0f};
    if (index < 0) {
        for (int i = 0; i < 6; ++i) {
            self->mTrail[i * 4 + 0] = zero.x;
            self->mTrail[i * 4 + 1] = zero.y;
            self->mTrail[i * 4 + 2] = zero.z;
            self->mTrail[i * 4 + 3] = zero.w;
        }
        return index;
    } else {
        float* p = &self->mTrail[index * 4];
        p[0] = zero.x;
        p[1] = zero.y;
        p[2] = zero.z;
        p[3] = zero.w;
        return (int)p;
    }
}

// @ 0x00f987f0
float __fastcall FUN_00f987f0(TerrainSphere* self, void* dummy)
{
    cTerrainMapSet_s00f9_86f0* m = self->mMap;
    return m->mRadius3c * m->mRadius38 + m->mRadius34;
}

// @ 0x00f98800
void __fastcall FUN_00f98800(TerrainSphere* self, void* dummy, Vec3* out, Vec3* dir)
{
    float h = self->mMap->GetHeightAt(dir);
    float inv = (float)(1.0 / sqrt((double)dir->x * dir->x + (double)dir->y * dir->y + (double)dir->z * dir->z + 1e-8));
    float x = dir->x;
    float y = dir->y;
    float z = dir->z;
    float rx = x * inv;
    float ry = y * inv;
    float rz = z * inv;
    out->x = rx * h;
    out->y = ry * h;
    out->z = rz * h;
}

// @ 0x00f98890
void __fastcall FUN_00f98890(TerrainSphere* self, void* dummy, int unused, Vec3* p, float w)
{
    Vec4 v = {p->x, p->y, p->z, w};
    self->mTarget = v;
}

// @ 0x00f988f0
void __fastcall FUN_00f988f0(TerrainSphere* self, void* dummy, int id)
{
    void** p = self->mDecalBegin;
    for (int i = 0; i < (int)((char*)self->mDecalEnd - (char*)self->mDecalBegin) >> 2; ++i, ++p) {
        void* e = *p;
        if (e != 0 && *(int*)e == id) {
            ((RemoveDecalFn)(*(void***)self)[0xc0 / 4])(self, i);
            return;
        }
    }
}

// @ 0x00f98970
void SkyState::Update()
{
    W* d = (W*)this;
    char* rec = GetRecord();

    d[0x142].u = SRC(0x42c).u;
    d[0x143].u = SRC(0x430).u;
    d[0x144].u = SRC(0x434).u;
    d[0x145].u = SRC(0x438).u;
    d[0x146].u = SRC(0x43c).u;
    d[0x147].u = SRC(0x440).u;
    d[0x148].u = SRC(0x444).u;
    d[0x149].u = SRC(0x448).u;
    uint32_t* light = GetLightVector();
    d[0x14a].u = light[0];
    d[0x14b].u = light[1];
    d[0x14c].u = light[2];
    d[0x14d].u = light[3];
    d[0x14e].u = SRC(0x4bc).u;
    d[0x14f].u = SRC(0x4c0).u;
    d[0x150].u = SRC(0x4c4).u;
    d[0x151].u = SRC(0x4c8).u;
    d[0x152].u = SRC(0x4cc).u;
    d[0x153].u = SRC(0x4d0).u;
    d[0x154].u = SRC(0x4d4).u;
    d[0x155].u = SRC(0x4d8).u;
    d[0x156].u = SRC(0x4dc).u;
    d[0x157].u = SRC(0x4e0).u;
    d[0x158].u = SRC(0x4e4).u;
    d[0x159].u = SRC(0x4e8).u;
    d[0x15a].u = SRC(0x4ec).u;
    d[0x15b].u = SRC(0x4f0).u;
    d[0x15c].u = SRC(0x4f4).u;
    d[0x15d].u = SRC(0x4f8).u;
    d[0x15e].u = SRC(0x34c).u;
    d[0x15f].u = SRC(0x350).u;
    d[0x160].u = SRC(0x354).u;
    d[0x161].u = SRC(0x358).u;
    d[0x16a].u = SRC(0x35c).u;
    d[0x16b].u = SRC(0x360).u;
    d[0x16c].u = SRC(0x364).u;
    d[0x16d].u = SRC(0x368).u;
    d[0x166].u = SRC(0x36c).u;
    d[0x167].u = SRC(0x370).u;
    d[0x168].u = SRC(0x374).u;
    d[0x169].u = SRC(0x378).u;
    d[0x162].u = SRC(0x37c).u;
    d[0x163].u = SRC(0x380).u;
    d[0x164].u = SRC(0x384).u;
    d[0x165].u = SRC(0x388).u;
    d[0x176].u = SRC(0x38c).u;
    d[0x177].u = SRC(0x390).u;
    d[0x178].u = SRC(0x394).u;
    d[0x179].u = SRC(0x398).u;
    d[0x172].u = SRC(0x39c).u;
    d[0x173].u = SRC(0x3a0).u;
    d[0x174].u = SRC(0x3a4).u;
    d[0x175].u = SRC(0x3a8).u;
    d[0x16e].u = SRC(0x3ac).u;
    d[0x16f].u = SRC(0x3b0).u;
    d[0x170].u = SRC(0x3b4).u;
    d[0x171].u = SRC(0x3b8).u;

    const float kDegToRad = 0.017453292f;
    float c1 = cosf(SRC(0x3c0).f * kDegToRad);
    float c2 = cosf(SRC(0x3c4).f * kDegToRad);
    float c3 = cosf(SRC(0x3c8).f * kDegToRad);
    float invA = 1.0f / (c2 - c3);
    float c0 = cosf(SRC(0x3bc).f * kDegToRad);
    d[0x13e].u = d[0xcb].u;
    float invB = 1.0f / (c0 - c1);
    d[0x13f].u = d[0xcc].u;
    d[0x140].u = d[0xcd].u;
    d[0x141].f = c2;
    d[0x17a].f = invB;
    d[0x17b].f = invA;
    d[0x17c].f = -(invB * c1);
    d[0x17d].f = -(invA * c3);

    for (int i = 0; i < 16; ++i)
        d[0x17e + i].u = SRC(0x47c + i * 4).u;

    d[0x1b2].u = d[0x146].u;
    d[0x1b3].u = d[0x147].u;
    d[0x1b4].u = d[0x148].u;
    d[0x1b5].u = d[0x149].u;

    d[0x14e].f = d[0x287].f + d[0x14e].f;
    d[0x149].f = d[0x288].f + d[0x149].f;
    d[0x1b5].f = d[0x1b5].f + d[0x288].f;
    d[0x15a].f = d[0x15a].f - d[0x289].f;
    d[0x156].f = d[0x28a].f + d[0x156].f;
    d[0x157].f = d[0x28b].f + d[0x157].f;
    d[0x159].f = d[0x28c].f + d[0x159].f;
    d[0x150].f = d[0x28d].f + d[0x150].f;

    float blend = d[0x291].f;
    if (blend < 1.0f) {
        float inv = 1.0f - blend;
        const Vec4& target = *(const Vec4*)&d[0x28e];
        static const int srcOff[6] = {0x35c, 0x36c, 0x37c, 0x38c, 0x39c, 0x3ac};
        static const int dstIdx[6] = {0x16a, 0x166, 0x162, 0x176, 0x172, 0x16e};
        for (int g = 0; g < 6; ++g) {
            const Vec4& a = *(const Vec4*)(rec + srcOff[g]);
            Vec4 r = a + (target - a) * inv;
            *(Vec4*)&d[dstIdx[g]] = r;
        }
    }
}

// @ 0x00f992e0
void __fastcall FUN_00f992e0(TerrainSphere* self, void* dummy)
{
    char* rec = ((GetRecordFn)(*(void***)self)[0x10 / 4])(self);
    char* r = rec + 0x2f4;
    const float kDegToRad = 0.017453292f;

    float c1 = (float)cos(*(float*)(r + 0xcc) * kDegToRad);
    float c2 = (float)cos(*(float*)(r + 0xd0) * kDegToRad);
    float c3 = (float)cos(*(float*)(r + 0xd4) * kDegToRad);
    float invA = 1.0f / (c2 - c3);
    float c0 = (float)cos(*(float*)(r + 0xc8) * kDegToRad);

    float cx = self->mConeX;
    self->mCone.mConeCos = *(unsigned*)&cx;
    float invB = 1.0f / (c0 - c1);
    float cy = self->mConeY;
    self->mCone.mConeA = *(unsigned*)&cy;
    float cz = self->mConeZ;
    self->mCone.mConeB = *(unsigned*)&cz;
    self->mCone.mConeC = *(unsigned*)&c2;
    self->mCone.mConeInvB = *(unsigned*)&invB;
    self->mCone.mConeInvA = *(unsigned*)&invA;
    float nb = -(invB * c1);
    self->mCone.mConeNB = *(unsigned*)&nb;
    float na = -(invA * c3);
    self->mCone.mConeNA = *(unsigned*)&na;

    self->mCone.mBlockA[0] = *(unsigned*)(r + 0x58);
    self->mCone.mBlockA[1] = *(unsigned*)(r + 0x5c);
    self->mCone.mBlockA[2] = *(unsigned*)(r + 0x60);
    self->mCone.mBlockA[3] = *(unsigned*)(r + 0x64);
    self->mCone.mBlockB[0] = *(unsigned*)(r + 0x68);
    self->mCone.mBlockB[1] = *(unsigned*)(r + 0x6c);
    self->mCone.mBlockB[2] = *(unsigned*)(r + 0x70);
    self->mCone.mBlockB[3] = *(unsigned*)(r + 0x74);
    self->mCone.mBlockC[0] = *(unsigned*)(r + 0x78);
    self->mCone.mBlockC[1] = *(unsigned*)(r + 0x7c);
    self->mCone.mBlockC[2] = *(unsigned*)(r + 0x80);
    self->mCone.mBlockC[3] = *(unsigned*)(r + 0x84);
    self->mCone.mBlockD[0] = *(unsigned*)(r + 0x88);
    self->mCone.mBlockD[1] = *(unsigned*)(r + 0x8c);
    self->mCone.mBlockD[2] = *(unsigned*)(r + 0x90);
    self->mCone.mBlockD[3] = *(unsigned*)(r + 0x94);
    self->mCone.mBlockE[0] = *(unsigned*)(r + 0x98);
    self->mCone.mBlockE[1] = *(unsigned*)(r + 0x9c);
    self->mCone.mBlockE[2] = *(unsigned*)(r + 0xa0);
    self->mCone.mBlockE[3] = *(unsigned*)(r + 0xa4);
    self->mCone.mBlockF[0] = *(unsigned*)(r + 0xa8);
    self->mCone.mBlockF[1] = *(unsigned*)(r + 0xac);
    self->mCone.mBlockF[2] = *(unsigned*)(r + 0xb0);
    self->mCone.mBlockF[3] = *(unsigned*)(r + 0xb4);
    self->mCone.mBlockG[0] = *(unsigned*)(r + 0xb8);
    self->mCone.mBlockG[1] = *(unsigned*)(r + 0xbc);
    self->mCone.mBlockG[2] = *(unsigned*)(r + 0xc0);
    self->mCone.mBlockG[3] = *(unsigned*)(r + 0xc4);
}

// @ 0x00f99520
void __fastcall FUN_00f99520(TerrainSphere* self, void* dummy)
{
    cTerrainMapSet_s00f9_86f0* map = self->mMap;
    float radius = map->mRadius3c * map->mRadius38 + map->mRadius34;
    int count = (int)((char*)self->mModelsEnd - (char*)self->mModels) >> 2;

    for (int i = 0; i < count; ++i) {
        TerrainModel* m = self->mModels[i];
        if (m == 0)
            continue;
        if ((m->mFlags & 1) == 0)
            continue;

        Vec3 v;
        v.x = m->x;
        v.y = m->y;
        v.z = m->z;
        float len = (float)sqrt((double)v.x * v.x + (double)v.y * v.y + (double)v.z * v.z);

        int arg;
        if (len <= 1e-6) {
            arg = 0;
        } else {
            float h = self->mMap->GetHeightAt(&v);
            if (self->mFlag8ac == 0 && h < radius) {
                arg = 0;
            } else {
                float s = h / len;
                v.x *= s;
                v.y *= s;
                v.z *= s;
                m->x = v.x;
                m->y = v.y;
                m->z = v.z;
                m->mFlags2 |= 4;
                m->mCounter += 1;
                arg = 1;
            }
        }
        ((PinModelFn)(*(void***)m->mpObj)[0x16c / 4])(m->mpObj, m, arg);
    }
}

// @ 0x00f9a610
void cTerrainSphere141::FUN_00f9a610()
{
    void* a = mpPlanet->mp08;
    for (int i = 0; i < 6; i++) {
        Rect_s00f9_a610& r = mRects[6 + i - 6 * mFaceBase];
        if (r.left != r.right && r.top != r.bottom)
            mpPlanet->mp58->FlushRect(a, i, &r);
    }
}

// @ 0x00f9a680
void cTerrainSphere141::FUN_00f9a680(int key, const float3* v)
{
    int n = (int)(mpArr2f8 - mpArr2f4) >> 2;
    int i = 0;
    if (n <= 0)
        return;
    uint8_t** arr = *(uint8_t** volatile*)&mpArr2f4;
    uint8_t** p = arr;
    do {
        if (*(int*)*p == key) {
            ((ElemA*)arr[i])->pos = *v;
            ((ElemA*)((uint8_t**)mpArr2f4)[i])->flag20 = 1;
            return;
        }
        ++i;
        ++p;
    } while (i < n);
}

// @ 0x00f9a6f0
void cTerrainSphere141::FUN_00f9a6f0(int key, const float3* v)
{
    int n = (int)(mpArr2f8 - mpArr2f4) >> 2;
    int i = 0;
    if (n <= 0)
        return;
    uint8_t** arr = *(uint8_t** volatile*)&mpArr2f4;
    uint8_t** p = arr;
    do {
        if (*(int*)*p == key) {
            ((ElemB*)arr[i])->pos = *v;
            ((ElemB*)((uint8_t**)mpArr2f4)[i])->flag20 = 1;
            return;
        }
        ++i;
        ++p;
    } while (i < n);
}

// @ 0x00f9a760
void cTerrainSphere141::FUN_00f9a760(int key, float v)
{
    int n = (int)(mpArr2f8 - mpArr2f4) >> 2;
    if (n <= 0)
        return;
    uint8_t** p = (uint8_t**)mpArr2f4;
    int i = 0;
    while (*(int*)*p != key) {
        i++;
        p++;
        if (n <= i)
            return;
    }
    ElemC* e = (ElemC*)((uint8_t**)mpArr2f4)[i];
    e->val = v;
    ((ElemC*)((uint8_t**)mpArr2f4)[i])->flag20 = 1;
}

// @ 0x00f9a7c0
void cTerrainSphere141::RenderLightingRegion(void* a, void* b)
{
    // 'this' is unused; `a` is the lighting-region object, `b` is passed through unchanged.
    uint8_t* region = (uint8_t*)a;
    cViewer2* viewer = (cViewer2*)(region + 4);

    region[0x1d4] = 0;
    int n = (*(int*)(region + 0x1c0) - *(int*)(region + 0x1bc)) >> 2;
    if (n == 0) {
        if (viewer->Update()) {
            viewer->Clear(7);
            viewer->Reset();
            return;
        }
        return;
    }
    if (!viewer->Update())
        return;
    viewer->Clear(7);
    IMaterialMgr* mm = MaterialManager();
    void* mat = mm->Get(0x44558011);
    void* buf = 0;
    void* extra = 0;
    if (!FUN_006ddcc0(3, n * 4, &buf, &extra)) {
        viewer->Reset();
        return;
    }
    MemZero(buf, 0, 0x70);
    if (n > 0) {
        float3 nrm[4];
        nrm[0].x = 0.0f; nrm[0].y = 0.0f; nrm[0].z = 0.0f;
        nrm[1].x = 1.0f; nrm[1].y = 0.0f; nrm[1].z = 0.0f;
        nrm[2].x = 1.0f; nrm[2].y = 1.0f; nrm[2].z = 0.0f;
        nrm[3].x = 0.0f; nrm[3].y = 1.0f; nrm[3].z = 0.0f;
        int off = 0;
        for (int i = 0; i < n; i++) {
            uint8_t* e = *(uint8_t**)(*(int*)(region + 0x1bc) + i * 4);
            float3 p;
            p.x = *(float*)(e + 4);
            p.y = *(float*)(e + 8);
            p.z = *(float*)(e + 0xc);
            ((cSPTransform_s00f9_a610*)(region + 0x178))->BackTransformPoint(&p);
            float u = p.x * kTwo - kOne;
            float w = p.y * kTwo - kOne;
            uint8_t* v = (uint8_t*)buf + off;
            *(float*)(v + 0x00) = u; *(float*)(v + 0x04) = w; *(float*)(v + 0x08) = 0.0f;
            *(float*)(v + 0x1c) = u; *(float*)(v + 0x20) = w; *(float*)(v + 0x24) = 0.0f;
            *(float*)(v + 0x38) = u; *(float*)(v + 0x3c) = w; *(float*)(v + 0x40) = 0.0f;
            *(float*)(v + 0x54) = u; *(float*)(v + 0x58) = w; *(float*)(v + 0x5c) = 0.0f;

            float h = (*(float*)(e + 0x1c) / *(float*)(region + 0x188)) * kTwo;
            *(float*)(v + 0x00) += -h;
            *(float*)(v + 0x04) +=  h;
            *(float*)(v + 0x1c) +=  h;
            *(float*)(v + 0x20) +=  h;
            *(float*)(v + 0x38) +=  h;
            *(float*)(v + 0x3c) += -h;
            *(float*)(v + 0x54) += -h;
            *(float*)(v + 0x58) += -h;

            *(float3*)(v + 0x10) = nrm[0];
            *(float3*)(v + 0x2c) = nrm[1];
            *(float3*)(v + 0x48) = nrm[2];
            *(float3*)(v + 0x64) = nrm[3];

            float rgba[3];
            rgba[0] = *(float*)(e + 0x10);
            rgba[1] = *(float*)(e + 0x14);
            rgba[2] = *(float*)(e + 0x18);
            uint32_t c = ColorRGBAToU32(rgba);
            *(uint32_t*)(v + 0x0c) = c;
            *(uint32_t*)(v + 0x28) = c;
            *(uint32_t*)(v + 0x44) = c;
            *(uint32_t*)(v + 0x60) = c;
            off += 0x70;
        }
    }
    FUN_006ddd80(3, mat, mF308, b);
    viewer->Reset();
}

// @ 0x00f9abc0
bool cTerrainSphere141::FUN_00f9abc0(float* dir)
{
    float x = dir[0];
    float y = dir[1];
    float z = dir[2];
    float ax = fabsf(x);
    float ay = fabsf(y);
    float az = fabsf(z);
    float u, v;
    uint32_t face;
    if (az < ax || az < ay) {
        if (ay < ax) {
            u = (y / x + kOne) * 0.5f;
            v = (z / ax + kOne) * 0.5f;
            face = 2;
            if (x < 0.0f)
                face = 3;
        } else {
            u = (z / y + kOne) * 0.5f;
            v = (x / ay + kOne) * 0.5f;
            face = (y < 0.0f) ? 5 : 4;
        }
    } else {
        u = (x / z + kOne) * 0.5f;
        v = (y / az + kOne) * 0.5f;
        face = (z < 0.0f) ? 1 : 0;
    }
    uint32_t* self = (uint32_t*)this;
    int* list = (int*)(self[0x74] + 0x218 + (*self >> 0x18) * 0x14);
    uint32_t idx = *self & 0xffffff;
    cTerrainSphereDecal_s00f9_a610* dec;
    if (idx < (uint32_t)((list[1] - *list) >> 2))
        dec = *(cTerrainSphereDecal_s00f9_a610**)(*list + idx * 4);
    else
        dec = 0;
    float bb[4];
    if (!dec->GetBBoxForFace(face, bb))
        return false;
    if (bb[0] < u && u < bb[2] && bb[1] < v && v < bb[3])
        return true;
    return false;
}

// @ 0x00f9ada0
void FUN_00f9ada0(float* dst, const float* src)
{
    float inv = 1.0f / sqrtf(src[0] * src[0] + src[1] * src[1] + src[2] * src[2]);
    dst[0] = src[0] * inv;
    dst[1] = src[1] * inv;
    dst[2] = src[2] * inv;
}

// @ 0x00f9adf0
RefPair* FUN_00f9adf0(RefPair* first, RefPair* last, RefPair* dst)
{
    if (first != last) {
        do {
            if (dst) {
                IRefObj32* p = first->p;
                dst->p = p;
                if (p)
                    p->AddRef();
                dst->x = first->x;
            }
            first++;
            dst++;
        } while (first != last);
    }
    return dst;
}

// @ 0x00f9ae80
RefPair* FUN_00f9ae80(RefPair* first, RefPair* last, RefPair* dst)
{
    if (first != last) {
        do {
            IRefObj32* a = first->p;
            IRefObj32* b = dst->p;
            if (a != b) {
                if (a)
                    a->AddRef();
                dst->p = a;
                if (b)
                    b->Release();
            }
            dst->x = first->x;
            first++;
            dst++;
        } while (first != last);
    }
    return dst;
}

// @ 0x00f9aee0
void FUN_00f9aee0(float* p, unsigned int n, const float* src)
{    struct Vec3 {
        float x, y, z;
        Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
    };
    struct Vec2 {
        float u, v;
        Vec2(const Vec2& o) { u = o.u; v = o.v; }
    };
    struct S {
        Vec3 pos;
        Vec2 uv;
        S(const S& o) : pos(o.pos), uv(o.uv) {}
    };
    S* d = (S*)p;
    const S* s = (const S*)src;
    for (; n > 0; --n, ++d)
        ::new ((void*)d) S(*s);
}

// @ 0x00f9af30
void __cdecl FUN_00f9af30(int base, int a, int n, int i, void* p5, void* p6, void* p7, void* p8, void* p9)
{
    int child;
    for (;;) {
        int l = i * 2;
        child = l + 2;
        if (n <= child)
            break;
        if (*(unsigned*)(child * 0x10 + 8 + base) < *(unsigned*)(child * 0x10 + base - 8))
            child = l + 1;
        int src = child * 0x10 + base;
        int dst = i * 0x10 + base;
        *(int*)(dst + 0)  = *(int*)(src + 0);
        *(int*)(dst + 4)  = *(int*)(src + 4);
        *(int*)(dst + 8)  = *(int*)(src + 8);
        *(int*)(dst + 12) = *(int*)(src + 12);
        i = child;
    }
    if (child == n) {
        int src = child * 0x10 - 0x10 + base;
        int dst = i * 0x10 + base;
        *(int*)(dst + 0)  = *(int*)(src + 0);
        *(int*)(dst + 4)  = *(int*)(src + 4);
        *(int*)(dst + 8)  = *(int*)(src + 8);
        *(int*)(dst + 12) = *(int*)(src + 12);
        i = child - 1;
    }
    FUN_00f96eb0(base, a, i, p5, p6, p7, p8, p9);
}

// @ 0x00f9aff0
RefPair* FUN_00f9aff0(RefPair* first, RefPair* last, RefPair* dst)
{
    if (last != first) {
        do {
            IRefObj32* a = (last - 1)->p;
            IRefObj32* b = (dst - 1)->p;
            last--;
            dst--;
            if (a != b) {
                if (a)
                    a->AddRef();
                dst->p = a;
                if (b)
                    b->Release();
            }
            dst->x = last->x;
        } while (last != first);
    }
    return dst;
}

// @ 0x00f9b050
float* FUN_00f9b050(float* first, float* last, float* dst)
{    for (; first != last; first += 5) {
        if (dst) {
            dst[0] = first[0];
            dst[1] = first[1];
            dst[2] = first[2];
            dst[3] = first[3];
            dst[4] = first[4];
        }
        dst += 5;
    }
    return dst;}

// @ 0x00f9b0a0
void* CGmeRefCount::Destroy(uint8_t flags)
{
    IRefCounted2* p = mp18;
    if (p) {
        int rc = p->mRefCount;
        p->mRefCount = rc - 1;
        if (rc - 1 == 0) {
            p->mRefCount = 1;
            _ReadWriteBarrier();
            p->Destroy(1);
        }
    }
    mVtbl4 = &vtbl_GmeRefCount0;
    if (flags & 1)
        operator delete(this);
    return this;
}

// @ 0x00f9b0f0
void CGmeRefCount2::Construct(float a, float b, float c, IRefCounted2* p5, IRefCounted2* p6)
{
    mVtbl4 = &vtbl_GmeRefCount0;
    mF8 = 0;
    mFC = a;
    mF10 = b;
    mVtbl0 = &vtbl_01490908;
    mVtbl4 = &vtbl_01490904;
    mF14 = c;
    mp18 = p5;
    if (p5)
        p5->mRefCount++;
    mVtbl0 = &vtbl_01490940;
    mVtbl4 = &vtbl_0149093c;
    mp1c = p6;
    if (p6)
        p6->mRefCount++;
}

// @ 0x00f9b170
void CGmeRefCount::Destroy2()
{
    IRefCounted2* p = mp1c;
    if (p) {
        int rc = p->mRefCount;
        p->mRefCount = rc - 1;
        if (rc - 1 == 0) {
            p->mRefCount = 1;
            _ReadWriteBarrier();
            p->Destroy(1);
        }
    }
    p = mp18;
    if (p) {
        int rc = p->mRefCount;
        p->mRefCount = rc - 1;
        if (rc - 1 == 0) {
            p->mRefCount = 1;
            _ReadWriteBarrier();
            p->Destroy(1);
        }
    }
    mVtbl4 = &vtbl_GmeRefCount0;
}

// @ 0x00f9b1e0
cSPTransform2* cSPTransform2::Init(const cSPTransform2* src)
{
    mModCount = 0;
    mFlags = 0;
    mTrans[0] = g_DAT_16c9e8c;
    mTrans[1] = g_DAT_16c9e90;
    mTrans[2] = g_DAT_16c9e94;
    mScale = kOne;
    Matrix3_Assign(&mRot, &g_DAT_16c9f24);
    mF98 = 0.0f;
    mF9c = 0.0f;
    mFa0 = 0.0f;
    cSPTransformOps_Assign(this, src);
    mF98 = src->mF98;
    mF9c = src->mF9c;
    mFa0 = src->mFa0;
    mFa4 = src->mFa4;
    memcpy((uint8_t*)this + 0x38, (const uint8_t*)src + 0x38, 0x60);
    mFa8 = src->mFa8;
    return this;
}

// @ 0x00f9b2b0
cSPTransform2* cSPTransform2::CopyFrom(const float* pos, const cSPTransform2* src, bool flag)
{
    mFlags = src->mFlags;
    mModCount = src->mModCount;
    mTrans[0] = src->mTrans[0];
    mTrans[1] = src->mTrans[1];
    mTrans[2] = src->mTrans[2];
    mScale = src->mScale;
    Matrix3_Assign(&mRot, (float*)&src->mRot);
    mF98 = pos[0];
    mF9c = pos[1];
    mFa0 = pos[2];
    mFa4 = flag ? 0x4000000 : 0;
    mFa8 = (float)(int)FUN_00f96390((void*)src, (void*)pos);
    MemZero((uint8_t*)this + 0x38, 0, 0x60);
    return this;
}

// @ 0x00f9b350
void cLightingSet::FUN_00f9b350()
{
    void* mgr = GetManager67b();
    if (mpVtbl0->IsVisible(mgr)) {
        SkyStateUpdate(this);
        SetShaderParam(0x305, (uint8_t*)this + 0x4f8, 0);
        SetShaderParam(0x306, (uint8_t*)this + 0x6c8, 0);
        FUN_00f992e0();
        SetShaderParam(0x24c, (uint8_t*)this + 0x638, 0);
        SetShaderParam(0x24d, (uint8_t*)this + 0x6d8, 0);
        return;
    }
    SetShaderParam(0x305, 0, 0);
    SetShaderParam(0x306, 0, 0);
    SetShaderParam(0x24c, 0, 0);
}

// @ 0x00f9b400
void cLightSet400::FUN_00f9b400(float sel, unsigned int a, unsigned int b)
{
    float f = 0.0f;
    if ((unsigned int)((int)sel - 1) < 0x40) {
        float v[4];
        v[0] = kOne;
        v[1] = kOne;
        v[2] = kBig;
        float fi = (float)(int)sel;
        if ((int)sel < 0) fi += 4294967296.0f;
        f = (fi - 0.5f) * 0.015625f;
        if (SP_GetPropertyAsVector3(mpProps, 0x3a23f99, v)) {
            Variant var;
            var.mTypeId = 0;
            var.mFlags = 0;
            v[0] = fi;
            v[1] = fi;
            FUN_006a3570(v);
            mpProps->Set(0x3a23f9a, &var);
            if (var.mFlags & 4)
                Variant_Destruct(&var, 0);
            mCount814++;
        }
    } else {
        if (sel != 0.0f) {
            goto after;
        }
        float v[4];
        v[0] = kOne;
        v[1] = kOne;
        v[2] = kBig;
        SP_GetPropertyAsVector3(mpProps, 0x3a23f99, v);
        mpProps->Del(0x3a23f9a);
        f = (v[0] - 0.5f) * 0.015625f;
        mCount814++;
    }
    FUN_00fbd880(f, f);
after:
    if (a < 0x10) {
        Variant var;
        var.mTypeId = 0;
        var.mFlags = 0;
        *(unsigned int*)&var = a;   // operator=<unsigned int>
        mpProps->Set(0x536250c, &var);
        if (var.mFlags & 4)
            Variant_Destruct(&var, 0);
        FUN_00fbaf10(a);
    }
    if (b < 0x10) {
        Variant var;
        var.mFlags = 0;
        var.mTypeId = 0;
        *(unsigned int*)&var = b;
        mpProps->Set(0x536250d, &var);
        if (var.mFlags & 4)
            Variant_Destruct(&var, 0);
        FUN_00fbaf50(sel);
    }
}

// @ 0x00f9b620
void cTS142::FUN_00f9b620(uint32_t a, uint32_t b, uint32_t c, float* p5, float* p6, float* p7)
{
    if (a < 0x40) {
        Sub334* s = (Sub334*)((Sub20c*)mp20c)->mp334;
        uint32_t v = s->mp28[a];
        p5[0] = (float)((v >> 16) & 0xff) * g_fColorScale;
        p5[1] = (float)((v >> 8) & 0xff) * g_fColorScale;
        p5[2] = (float)(v & 0xff) * g_fColorScale;
    }
    float scale = ((Sub20c*)mp20c)->mScale;
    if (b < 0x10) {
        uint8_t* i = (uint8_t*)((Sub20c*)mp20c)->mp20c;
        int n = *(int*)(i + 0x1c) - 1;
        float f = (float)(uint32_t)n;
        f = f * scale;
        int r = (int)floorf(f);
        if (f < (float)r)
            r = r - 1;
        uint32_t v = *(uint32_t*)(*(int*)(i + 0x28) +
                       ((*(uint32_t*)(i + 0x20) >> 1) * *(int*)(i + 0x1c) + r) * 4);
        p6[0] = (float)((v >> 16) & 0xff) * g_fColorScale;
        p6[1] = (float)((v >> 8) & 0xff) * g_fColorScale;
        p6[2] = (float)(v & 0xff) * g_fColorScale;
    }
    if (c < 0x10) {
        uint8_t* i = (uint8_t*)((Sub20c*)mp20c)->mp1f4;
        int n = *(int*)(i + 0x1c) - 1;
        float f = (float)(uint32_t)n;
        f = f * scale;
        int r = (int)floorf(f);
        if (f < (float)r)
            r = r - 1;
        uint32_t v = *(uint32_t*)(*(int*)(i + 0x28) + r * 4);
        p7[0] = (float)((v >> 16) & 0xff) * g_fColorScale;
        p7[1] = (float)((v >> 8) & 0xff) * g_fColorScale;
        p7[2] = (float)(v & 0xff) * g_fColorScale;
    }
}

// @ 0x00f9b7f0
void cTS142::FUN_00f9b7f0()
{
    if (mpProps == 0)
        return;
    uint32_t val = 0;
    void* prop = 0;
    if (mpProps->Get(0x3ad556a, &prop) && *(int16_t*)((uint8_t*)prop + 0x12) == 10)
        val = *((Prop*)prop)->GetUInt();
    if (val == (uint32_t)mF814)
        return;
    ((Tv0)VTO(this, 0x80))(this);
    Variant_s00f9_b620 var;
    var.mType = 10;
    var.mFlags = 2;
    var.SetInt(&mF814);
    mpProps->Set(0x3ad556a, &var);
    if (var.mFlags & 4)
        var.Destruct(0);
    FUN_006b4b60(mpProps, SP_GetSaveArea(0x31389b5), 0, 0);
}

// @ 0x00f9b8c0
void cTS142::FUN_00f9b8c0(int a, int b, int flag, uint8_t f5, float f6)
{
    TerrainEditor* ed = (TerrainEditor*)SP_TerrainEditor();
    ed->Init(this);
    ed->Reset();
    *(uint32_t*)((uint8_t*)ed + 0x160) = 0;
    float v[3] = { g_fHalf, g_fHalf, g_fHalf };
    GetPropertyAsVector3(mpProps, 0x3a23f98, v);
    ed->SetValue(v[0]);
    if (!((TerrainEditor*)SP_TerrainEditor())->IsEditing()) {
        if ((uint8_t)flag != 0) {
            mByte108 = f5;
            mF10c = f6;
            mpFC = mSub74;
            goto call;
        }
        mpFC = mSub74;
    } else {
        mByte108 = 0;
        if (g_sAppProperties) {
            int pr = 0;
            if (((cDirectPropertyList_s00f9_b620*)g_sAppProperties)->Get(0x31989aaf, &pr) &&
                *(int16_t*)((uint8_t*)pr + 0x12) == 1)
                mByte108 = (uint8_t)Property_GetBool((void*)pr);
        }
        int iv = 10;
        if (g_sAppProperties) {
            int pr = 0;
            if (((cDirectPropertyList_s00f9_b620*)g_sAppProperties)->Get(0xab52b057, &pr) &&
                *(int16_t*)((uint8_t*)pr + 0x12) == 9)
                iv = Property_GetInt((void*)pr);
        }
        mF10c = (float)iv;
        mpFC = mSubB8;
    }
call:
    ((Tv0)VTO(mpFC, 8))(mpFC);
    if (mpFC != mSub74)
        mF818 = mF814;
    else {
        FUN_00f97750(this);
        mF818 = mF814;
    }
}

// @ 0x00f9ba40
void cTS142::FUN_00f9ba40(void* mtx)
{
    if (mtx == 0) {
        void* app = SP_App();
        void* x = ((Tp0)VTO(app, 0x50))(app);
        mtx = ((Tp0)VTO(x, 0x1c))(x);
    }
    Matrix44 local;
    local.Ctor(mtx);
    float u3 = g_dat15b119c;
    float u4 = g_dat15b1198;
    float u5 = g_dat15b1194;
    Sub20c* s = (Sub20c*)mp20c;
    if (s != 0) {
        u5 = *(float*)((uint8_t*)s + 0x46c);
        u4 = *(float*)((uint8_t*)s + 0x470);
        u3 = *(float*)((uint8_t*)s + 0x474);
    }
    mMat30c[0] = local.m[12];   // wAxis.x
    mMat30c[1] = local.m[13];
    mMat30c[2] = local.m[14];
    *(uint32_t*)&mMat30c[3] = 0x3f800000;
    mMat30c[4] = local.m[4];    // yAxis.x
    mMat30c[5] = local.m[5];
    mMat30c[6] = local.m[6];
    mMat30c[7] = local.m[7];
    *(float*)((uint8_t*)this + 0x32c) = u5;
    *(float*)((uint8_t*)this + 0x330) = u4;
    *(float*)((uint8_t*)this + 0x334) = u3;
}

// @ 0x00f9bb50
void cTS142::FUN_00f9bb50()
{
    float* p = (float*)((uint8_t*)this + 0x498);
    for (int i = 0; i < 6; i++) {
        float a0 = p[-0x19];    // left
        float a2 = p[-0x18];    // top
        float a1 = p[-0x17];    // right
        float a3 = p[-0x16];    // bottom
        if (a0 != a1 && a2 != a3 && 0.0f < a1 && (a0 < 1.0f && 0.0f < a3) && a2 < 1.0f) {
            float x0 = p[-1];
            float y0 = p[0];
            float x1 = p[1];
            float y1 = p[2];
            if (x0 == x1 || y0 == y1) {
                p[-1] = a0; p[0] = a2; p[1] = a1; p[2] = a3;
            } else {
                float r = a0;
                if (a0 > x0) r = x0;
                p[-1] = r;
                r = y0;
                if (a2 <= r) r = a2;
                p[0] = r;
                r = x1;
                if (r <= a1) r = a1;
                p[1] = r;
                r = y1;
                if (r <= a3) r = a3;
                p[2] = r;
            }
        }
        FUN_00f986f0(i);
        p += 4;
    }
}

// @ 0x00f9bc40
void cTS142::FUN_00f9bc40(uint32_t a, uint32_t b)
{
    FUN_00f98970();
    FUN_00777ae0(0x305, (uint8_t*)this + 0x4f8, 0);
    uint32_t id = 0xbacbe342;
    if (mDecalIdMode == 0)
        id = 0x2a6214d0;
    else if (mDecalIdMode == 1)
        id = 0x4a621add;
    IImgMgr* mm = (IImgMgr*)SP_MaterialManager();
    void* mat = ((Tp1)VTO(mm, 0x28))(mm, id);
    FUN_006dde30(2, 4, mat);
    int n = (int)((uint8_t*)mpDecalEnd - (uint8_t*)mpDecalBegin) >> 4;
    if (n > 0) {
        int off = 0;
        do {
            if ((((uint8_t*)mpDecalBegin)[off + 0xc] & 0x40) == 0)
                (*(cTerrainQuad**)((uint8_t*)mpDecalBegin + off))->BufferDrawRibbonGeometry((void*)a);
            off += 0x10;
            n--;
        } while (n != 0);
    }
    FUN_006ddef0((void*)a);
}

// @ 0x00f9bd00
void cTS142::FUN_00f9bd00(void* p2, uint32_t a, uint32_t b)
{
    cDirectPropertyList_s00f9_b620* props = (cDirectPropertyList_s00f9_b620*)g_sAppProperties;
    mpViewer->Copy(*(void**)p2, 0, 0);
    uint32_t u3 = b & 0x4000000;
    if (u3 != 0 || (b & 0x2000000) != 0)
        ((Sync94*)((uint8_t*)this + 0x92c))->Sync((uint8_t*)mpViewer + 0xc0);
    if (!mpViewer->Update())
        return;
    void* mgr = SP_ModelManager();
    void* obj = ((Tp1)VTO(mgr, 0x1c))(mgr, 0x3fbae24);
    if (obj != 0) {
        void* g = FUN_0067ddc0();
        uint32_t u = (uint32_t)(uintptr_t)((Tp1)VTO(obj, 0x144))(obj, 0);
        ((Tv1)VTO(g, 0x50))(g, (int)u);
        props = (cDirectPropertyList_s00f9_b620*)g_sAppProperties;
    }
    rw_D3D9Sync();
    FUN_00f98970();
    FUN_00777ae0(0x305, (uint8_t*)this + 0x4f8, 0);
    if (ListGetDescription(props, 0xc0b97e13))
        FUN_00f97f50(a, b);
    if (ListGetDescription(props, 0xddca437d))
        FUN_00f98530(mpViewer, a);
    if (ListGetDescription(props, 0xab73e4f9))
        FUN_00f98020(a, b);
    if (ListGetDescription(props, 0x5016cc22) && (b & 0x1000000) == 0 && a == 0)
        FUN_00f98170(a, b);
    if (ListGetDescription(props, 0x5dee2437) && (b & 0x1000000) == 0 && a == 0)
        FUN_00f9bc40(a, b);
    if (ListGetDescription(props, 0x4f4edc94) && (b & 0x3000000) == 0) {
        if (a != 0) {
            mpViewer->Reset();
            mpViewer->SetZoom(1.0f);
            if (!mpViewer->Update())
                return;
        }
        FUN_00f981d0(a, b);
    }
    mpViewer->Reset();
}

// @ 0x00f9bee0
void cTS142::FUN_00f9bee0(void* p2)
{
    void* self;
    if (this != 0)
        self = (uint8_t*)this + 4;
    else
        self = 0;
    if (((Tp1)VTO(p2, 0x58))(p2, 8) != self)
        return;
    if (g_dat016c9e68 != 0)
        FUN_00f96c60();
    if (mF8d8 != 0)
        FUN_00f998f0();
    IEffectMgr* em = (IEffectMgr*)SP_EffectsManager();
    void* e = ((Tp1)VTO(em, 0x54))(em, 0x3fbae24);
    ((Tv1)VTO(e, 0xc))(e, 3);
    ((Tv1)VTO(p2, 0x50))(p2, 10);
    IResourceMgr* mm = (IResourceMgr*)SP_ModelManager();
    void* m = ((Tp1)VTO(mm, 0x1c))(mm, 0x3fbae24);
    ((Tv1)VTO(m, 0x134))(m, 0);
    ((Tv1)VTO(p2, 0x50))(p2, 8);
    ((Tv1)VTO(p2, 0x50))(p2, 7);
    ((Tv1)VTO(p2, 0x50))(p2, 0x21);
    FUN_00777ae0(0x301, 0, 0);
    FUN_00777ae0(0x304, 0, 0);
    FUN_00777ae0(0x305, 0, 0);
    FUN_00777ae0(0x306, 0, 0);
    FUN_00777ae0(0x24b, 0, 0);
    FUN_00777ae0(0x23d, 0, 0);
    FUN_00777ae0(0x24c, 0, 0);
    FUN_00777ae0(0x24d, 0, 0);
}

// @ 0x00f9c010
void cTS142::FUN_00f9c010(int idx)
{
    IImgMgr* m = (IImgMgr*)FUN_0067dd60();
    void* a = m->v3c((void*)g_imgIdsA[idx], g_imgMgr, 0x200, 0x200, 1, 8, 0x15, 0);
    ((ImgSlot*)((uint8_t*)this + 0x148 + idx * 4))->GetImageResource(a);
    void* b = m->v3c((void*)g_imgIdsB[idx], g_imgMgr, 0x200, 0x200, 1, 8, 0x51, 0);
    ((ImgSlot*)((uint8_t*)this + 0x160 + idx * 4))->GetImageResource(b);
    void* c = m->v3c((void*)g_imgIdsC[idx], g_imgMgr, 0x100, 0x100, 1, 8, 0x32, 0);
    ((ImgSlot*)((uint8_t*)this + 0x178 + idx * 4))->GetImageResource(c);
}

// @ 0x00f9c0d0
void cTS142::FUN_00f9c0d0(int face, void* renderStats)
{
    void* mm = SP_MaterialManager();
    void* mat = ((Tp1)VTO(mm, 0x28))(mm, 0x78a45ffb);
    g_renderViewer.SetTexture(g_dat016c9e40);
    if (g_renderViewer.Update()) {
        void* buf = 0;
        void* extra = 0;
        if (FUN_006ddcc0(3, 4, &buf, &extra)) {
            memset(buf, 0, 0x70);
            float* m = (float*)buf;
            m[4] = 0.0f; m[5] = 0.0f; m[6] = 0.0f;
            m[0xb] = 1.0f; m[0xc] = 0.0f; m[0xd] = 0.0f;
            m[0x12] = 1.0f; m[0x13] = 1.0f; m[0x14] = 0.0f;
            m[0x19] = 0.0f; m[0x1a] = 1.0f; m[0x1b] = 0.0f;
            m[0] = -1.0f; m[1] = 1.0f; m[2] = 0.0f;
            m[7] = 1.0f; m[8] = 1.0f; m[9] = 0.0f;
            m[0xe] = 1.0f; m[0xf] = -1.0f; m[0x10] = 0.0f;
            m[0x15] = -1.0f; m[0x16] = -1.0f; m[0x17] = 0.0f;
            FUN_006ddd80(3, mat, g_dat016c9e44[face], renderStats);
        }
        g_renderViewer.Reset();
    }
    TerrainEditor* ed = (TerrainEditor*)SP_TerrainEditor();
    if (ed->IsEditing())
        return;

    ColorMap* colorMap = (ColorMap*)mpMapSet->mMaps[3];
    uint32_t faceSize = colorMap->mFaceSize;
    uint32_t* faceData = colorMap->mpData + (uint32_t)face * faceSize * faceSize;
    void* rtt = FUN_0067dda0();
    ((Tv3)VTO(rtt, 0x30))(rtt, g_colorMap[0], g_colorMap[1], faceData);
    colorMap->mModCount++;

    ViewFrame_s00f9_b620* frame = (ViewFrame_s00f9_b620*)((Tvp)VTO(this, 0x10))(this);
    RasterObj** streams = frame->mStreams;
    RasterObj* r = streams[13];
    EnsureRaster(r);
    int w = r->mpRes->mWidth;
    r = streams[13];
    EnsureRaster(r);
    int h = r->mpRes->mHeight;
    r = streams[13];
    EnsureRaster(r);
    void* locked = 0;
    if (r->mpRes->Lock(1, 0, &locked)) {
        FUN_00f96920((const uint8_t*)locked, w, h, FUN_00fb8a00_fastcall(mp20c), 0.0f,
                     &mF1EC[0], &mF1EC[1], &mF1EC[2], &mF1EC[3]);
        FUN_00f96920((const uint8_t*)locked, w, h, FUN_00fb8a00_fastcall(mp20c), 1.0f,
                     &mF1EC[4], &mF1EC[5], &mF1EC[6], &mF1EC[7]);
        r = streams[13];
        EnsureRaster(r);
        r->mpRes->Unlock(&locked);
    }
}

// @ 0x00f9c470
void __stdcall FUN_00f9c470(int param_1, int param_2)
{
    void* appProps = g_sAppProperties;
    int i = 0;
    if (param_1 == 0) {
        void* app = SP_App();
        void* v = ((FnV)(*(void***)app)[0x50 / 4])(app);
        ((FnVoid)(*(void***)v)[0x1c / 4])(v);
    }
    int target = *g_p16c9f5c;
    bool has = ((cPropList*)appProps)->GetDescription(0x8a3a24da);
    int p2 = param_2;
    const uint8_t* rec = g_faceRecs;
    do {
        *(uint8_t*)(target + 0x12) = (uint8_t)i;
        ((cViewerS*)0x16ca260)->Clear(7);
        float mm[9] = { g_f24, g_f28, g_f2c, g_f30, g_f34, g_f38, g_f3c, g_f40, g_f44 };
        Basis3 s;
        s.flags = 0;
        s.vec.x = g_e8c; s.vec.y = g_e90; s.vec.z = g_e94; s.vec.w = 1.0f;
        memcpy(&s.mat, mm, sizeof(mm));
        s.Normalize(rec);
        ((cViewerS*)0x16ca260)->SetBasis(&s);
        AppArg a;
        a.p0 = (void*)0x16ca260; a.p1 = 0; a.p2 = 0; a.p3 = 0;
        void* o = FUN_0067dd50();
        int v7, v8;
        if (has) { v7 = 0x12; v8 = 0x12; } else { v7 = 5; v8 = 5; }
        ((FnCall)(*(void***)o)[0x40 / 4])(o, p2, v7, v8, &a, 0, 0);
        rec += 0x40;
        ++i;
    } while ((int)rec < 0x15b14c0);
}

// @ 0x00f9c660
Quat cTS143::BuildSurfaceOrientation(const Vec3& a, const Vec3& b)
{
    float ax = a.x;
    Quat out;
    if ((a.y * a.y + a.z * a.z) + ax * ax < kEps) goto degenerate;
    {
        float bx = b.x;
        if ((bx * bx + b.y * b.y) + b.z * b.z < kEps) goto degenerate;
        float inv = 1.0f / sqrtf((a.y * a.y + a.z * a.z) + ax * ax);
        float x1 = ax * inv;
        float z1 = inv * a.z;
        float y1 = inv * a.y;
        Vec3 na; na.x = x1; na.y = y1; na.z = z1;
        float c0 = b.y * z1 - b.z * y1;
        float c1 = b.z * x1 - bx * z1;
        float c2 = y1 * bx - b.y * x1;
        float len = sqrtf(c0 * c0 + (c2 * c2 + c1 * c1));
        if (len < kEps) {
            Vec3 ortho;
            Vec3* o = OrthogonalVector(&ortho, &na);
            float* p = normalized_safe((float*)&ortho, (const float*)o);
            c0 = p[0]; c1 = p[1]; c2 = p[2];
        } else {
            float f = 1.0f / len;
            c0 *= f; c1 *= f; c2 *= f;
        }
        float d0 = c2 * y1 - c1 * z1;
        float d1 = z1 * c0 - c2 * x1;
        float d2 = c1 * x1 - y1 * c0;
        float dl = sqrtf(d2 * d2 + (d1 * d1 + d0 * d0));
        if (dl < kEps) goto degenerate;
        float f = 1.0f / dl;
        Mat33 M;
        M.m0 = c0;    M.m1 = c1;    M.m2 = c2;
        M.m3 = d0 * f; M.m4 = d1 * f; M.m5 = d2 * f;
        M.m6 = x1;    M.m7 = y1;    M.m8 = z1;
        FUN_0046d660((float*)&out, (const float*)&M);
        return out;
    }
degenerate:
    out.x = g_1c8; out.y = g_1cc; out.z = g_1d0; out.w = g_1d4;
    return out;
}

// @ 0x00f9c960
Quat cTS143::BuildSurfaceOrientationV(const Vec3& a, const Quat& q)
{
    Mat33 M;
    Matrix3FromQuaternion(&M, &q);
    float ax = a.x, ay = a.y, az = a.z;
    float inv = 1.0f / sqrtf((ax * ax + ay * ay) + az * az);
    float x1 = ax * inv;
    float y1 = ay * inv;
    float z1 = az * inv;
    float f4 = (M.m3 * g_8d8 + M.m6 * g_8dc) + M.m0 * g_8d4;
    float f5 = M.m7 * g_8dc + (M.m1 * g_8d4 + M.m4 * g_8d8);
    float f6 = (M.m5 * g_8d8 + M.m2 * g_8d4) + M.m8 * g_8dc;
    if (0.999f < fabsf(f4 * x1 + (f6 * z1 + f5 * y1))) {
        return q;
    }
    float e0 = f5 * z1 - f6 * y1;
    float e1 = f6 * x1 - f4 * z1;
    float e2 = y1 * f4 - f5 * x1;
    float t = 1.0f / sqrtf(e1 * e1 + (e2 * e2 + e0 * e0));
    float e0n = e0 * t;
    float e1n = e1 * t;
    float e2n = e2 * t;
    float g0 = e2n * y1 - e1n * z1;
    float g1 = e1n * x1 - y1 * e0n;
    float g2 = e0n * z1 - e2n * x1;
    float u = 1.0f / sqrtf(g2 * g2 + (g1 * g1 + g0 * g0));
    Mat33 M2;
    M2.m0 = e0n; M2.m1 = e1n; M2.m2 = e2n;
    M2.m3 = g0 * u; M2.m4 = g2 * u; M2.m5 = g1 * u;
    M2.m6 = x1; M2.m7 = y1; M2.m8 = z1;
    Quat out;
    QuaternionFromMatrix33(&out, &M2, 0.0f);
    return out;
}

// @ 0x00f9cc50
Quat cTS143::BuildPitchedSurfaceOrientation(const Vec3* pos, const Quat* q, float pitch)
{
    Mat33 M;
    Matrix3FromQuaternion(&M, q);
    float px = pos->x, py = pos->y, pz = pos->z;
    float p70 = px + M.m3 * pitch;
    float p68 = M.m5 * pitch + pz;
    float p6c = py + M.m4 * pitch;
    Vec3 v; v.x = p70; v.y = p6c; v.z = p68;
    float h = (*(cTerrainMapSet_s00f9_c470**)((uint8_t*)this + 0x2c))->GetHeightAt(&v);
    float inv = 1.0f / sqrtf((p70 * p70 + (p68 * p68 + p6c * p6c)) + 1e-08f);
    float q6c = (p6c * inv) * h - py;
    float q70 = (inv * p70) * h - px;
    float q68 = (p68 * inv) * h - pz;
    float f8 = (M.m1 * pitch + py) - py;
    float f6 = (M.m0 * pitch + px) - px;
    float f7 = (M.m2 * pitch + pz) - pz;
    float c58 = f8 * q68 - f7 * q6c;
    float c54 = f7 * q70 - q68 * f6;
    float c50 = q6c * f6 - f8 * q70;
    float len1 = (c58 * c58 + c50 * c50) + c54 * c54;
    if (kEps <= len1) {
        float g7 = c50 * q6c - c54 * q68;
        float g9 = q68 * c58 - c50 * q70;
        float g8 = c54 * q70 - q6c * c58;
        float len2 = (g7 * g7 + g8 * g8) + g9 * g9;
        if (kEps <= len2) {
            float a = 1.0f / sqrtf(len1);
            float n50 = c50 * a;
            float n58 = a * c58;
            float n54 = c54 * a;
            float b = 1.0f / sqrtf(len2);
            float m0 = b * g7;
            float m1 = g9 * b;
            float m2 = g8 * b;
            float c = 1.0f / sqrtf(q6c * q6c + (q68 * q68 + q70 * q70));
            float r6c = q6c * c;
            float r70 = c * q70;
            float r68 = q68 * c;
            Mat33 M2;
            M2.m0 = m0;  M2.m1 = m1;  M2.m2 = m2;
            M2.m3 = r70; M2.m4 = r6c; M2.m5 = r68;
            M2.m6 = n58; M2.m7 = n54; M2.m8 = n50;
            Quat tmp;
            QuaternionFromMatrix33(&tmp, &M2, 0.0f);
            return tmp;
        }
    }
    return *q;
}

// @ 0x00f9d080
namespace SP {
Quaternion cTerrainSphere_s00f9_d080::BuildSurfaceNormalOrientation(const Vector3_s00f9_d080& pos, const Quaternion& baseQuat, float pitch) const
{
    Matrix33_s00f9_d080 mat;
    Matrix3FromQuaternion(mat, baseQuat);

    cTerrainMapSet_s00f9_d080* mapSet = mpMapSet;
    float h0 = mapSet->GetHeightAt(pos);

    float invLen = 1.0f / sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + 1e-08f);
    float px = (pos.x * invLen) * h0;
    float py = h0 * (pos.y * invLen);
    float pz = (pos.z * invLen) * h0;

    Vector3_s00f9_d080 A;
    A.x = mat.yAxis.x * pitch + px;
    A.y = mat.yAxis.y * pitch + py;
    A.z = mat.yAxis.z * pitch + pz;
    Vector3_s00f9_d080 B;
    B.x = mat.xAxis.x * pitch + px;
    B.y = mat.xAxis.y * pitch + py;
    B.z = mat.xAxis.z * pitch + pz;

    float hA = mapSet->GetHeightAt(A);
    float ilA = 1.0f / sqrtf(A.x * A.x + A.y * A.y + A.z * A.z + 1e-08f);
    float dAx = (ilA * A.x) * hA - px;
    float dAy = (A.y * ilA) * hA - py;
    float dAz = (A.z * ilA) * hA - pz;

    float hB = mapSet->GetHeightAt(B);
    float ilB = 1.0f / sqrtf(B.x * B.x + B.y * B.y + B.z * B.z + 1e-08f);
    float dBx = (ilB * B.x) * hB - px;
    float dBy = (B.y * ilB) * hB - py;
    float dBz = (B.z * ilB) * hB - pz;

    float c0 = dBy * dAz - dBz * dAy;
    float c1 = dBz * dAx - dAz * dBx;
    float c2 = dAy * dBx - dBy * dAx;
    float len2 = (c2 * c2 + c1 * c1) + c0 * c0;

    if (1.5258789e-05f <= len2) {
        float e0 = c2 * dAy - c1 * dAz;
        float e1 = dAz * c0 - c2 * dAx;
        float e2 = c1 * dAx - dAy * c0;
        float len2b = (e2 * e2 + e1 * e1) + e0 * e0;
        if (1.5258789e-05f <= len2b) {
            float n0 = 1.0f / sqrtf(len2);
            float nz = c2 * n0;
            float ny = c1 * n0;
            float nx = n0 * c0;
            float m0 = 1.0f / sqrtf(len2b);
            float ex = e0 * m0;
            float ey = e1 * m0;
            float ez = e2 * m0;
            float s0 = 1.0f / sqrtf(dAx * dAx + dAy * dAy + dAz * dAz);
            float sx = s0 * dAx;
            float sy = dAy * s0;
            float sz = dAz * s0;

            Matrix33_s00f9_d080 out;
            out.xAxis.x = ex;  out.xAxis.y = ey;  out.xAxis.z = ez;
            out.yAxis.x = sx;  out.yAxis.y = sy;  out.yAxis.z = sz;
            out.zAxis.x = nx;  out.zAxis.y = ny;  out.zAxis.z = nz;

            Quaternion q;
            QuaternionFromMatrix33(&q, out, 0.0f);
            return q;
        }
    }
    return baseQuat;
}
}  // namespace SP

// @ 0x00f9d5c0
namespace SP {
void cTerrainSphere_s00f9_d080::DrawFootprint(void* xform, float z, void* img, const Vector2_s00f9_d080* off, bool flag, void* faceBoxes, void* a3)
{
    // image resource holder (0x78 bytes): [0]=refcount/type, [4]=no-image flag, [8]=1.0f
    char imageRes[0x78];
    MemSet(imageRes, 0, 0x78);
    GetImageResource_s00f9_d080(imageRes, img);
    imageRes[4] = (img == 0) ? 1 : 0;
    imageRes[8] = 1.0f;
    imageRes[5] = 0;
    imageRes[6] = 0;
    *(uint32_t*)(imageRes + 0x3c) = 0;

    float fVar8 = off->x;
    float height;
    int face;

    if (fVar8 == 0.0f && off->y == 0.0f) {
        // pick the cube face from the direction packed into the transform
        float dx = *(float*)((char*)xform + 4);
        float dy = *(float*)((char*)xform + 8);
        float dz = *(float*)((char*)xform + 0xc);
        int map = *(int*)((char*)mpMapSet + 8);
        float ax = fabsf(dx), ay = fabsf(dy), az = fabsf(dz);
        float u, v;
        face = 3;
        if (az < ax || az < ay) {
            if (ay < ax) {
                u = (dy / dx + 1.0f) * 0.5f;
                v = (dz / ax + 1.0f) * 0.5f;
                face = (dx < 0.0f) ? 3 : 2;
            } else {
                u = (dz / dy + 1.0f) * 0.5f;
                v = (dx / ay + 1.0f) * 0.5f;
                face = (dy < 0.0f) ? 5 : 4;
            }
        } else {
            u = (dx / az + 1.0f) * 0.5f;
            v = (dy / az + 1.0f) * 0.5f;
            face = (dz < 0.0f) ? 1 : 0;
        }
        int idx[3];
        CoordToIndex(idx, map, &u);
        int sz = *(int*)(map + 8);
        unsigned short* heights = *(unsigned short**)(map + 0x10);
        int i = ((idx[2] * sz + idx[1]) * sz + idx[0]);
        height = (float)(int)(heights[i] - 0x8000) * 3.051851e-05f;
        if (flag) {
            cTerrainEditor* ed = TerrainEditor();
            float r = (ed->GetRandom01() + ed->GetRandom01()) - 1.0f + 0.03f;
            if (r <= height)
                r = height;
            height = r;
        }
        (void)face;
    } else {
        face = 4;
        float a = fVar8;
        float b = off->y;
        float delta = 0.0f;
        if (flag) {
            cTerrainEditor* ed = TerrainEditor();
            delta = (ed->GetRandom01() + ed->GetRandom01()) - 1.0f;
        }
        fVar8 = delta + a;
        height = delta + b;
        (void)face;
    }

    // decal-target descriptor (0x7c bytes)
    char target[0x7c];
    MemSet(target, 0, 0x7c);
    memcpy(target + 4, kDecalTargetTemplate, sizeof(kDecalTargetTemplate));
    target[0] = 0;
    target[1] = 0;
    *(uint32_t*)(target + 0x48) = 0;
    *(uint32_t*)(target + 0x54) = 0;

    float size = *(float*)((char*)xform + 0x10);

    Quaternion q;
    QuaternionFromMatrix33(&q, *(Matrix33_s00f9_d080*)((char*)xform + 0x14), 0.0f);

    cTerrainEditor* ed = TerrainEditor();
    ed->BuildDecal((const Vector3_s00f9_d080*)((char*)xform + 4), &q, size, imageRes, target, a3, 0, 0,
                   faceBoxes, 0);
    (void)z;
    (void)height;
}
}  // namespace SP

// @ 0x00f9d9b0
namespace SP {
void cTerrainSphere_s00f9_d080::UpdateScatterTexture(int face, void* raster, const Vector3_s00f9_d080& dir, void* stats)
{
    *(char*)((char*)raster + 0x12) = (char)face;

    void** mm = (void**)MaterialManager_s00f9_d080();
    void* vtbl = *mm;
    int (*getMaterial)(void*, uint32_t) = (int (*)(void*, uint32_t)) * (void**)((char*)vtbl + 0x28);
    int* mat = (int*)getMaterial(mm, 0x1a856cf3);
    if (*(int*)((char*)mat + 4) == 0)
        return;

    // Shader descriptor.  In the original the fields live in a stack block; the
    // 0x00fb7b90 float query sits at scratch+0x00 and the raster lock buffer at
    // scratch+0x2c (0x100 bytes cleared).
    char scratch[0x12c];
    float* d = (float*)scratch;                 // scratch offsets == original +0x10
    MemSet(scratch + 0x2c, 0, 0x100);

    void* scene1 = GetScene();
    void* scene2 = GetScene();
    d[0] = SceneQueryA(scene2);
    float* fs = (float*)((char*)scene1 + 0x2f4);

    d[1] = fs[0x108 / 4];
    d[2] = fs[0x118 / 4];
    d[3] = fs[0x128 / 4];
    d[4] = 0.0f;
    if (g_scatterDescFlag != 0) {
        float c = (d[0] - 0.5f) * 2.0f;
        d[10] = 0.0f;                            // original +0x38
        d[5] = c;                                // original +0x24
        d[0] = (c >= 0.0f) ? c : 0.0f;           // original +0x10
    }
    d[11] = d[1];  d[12] = d[2];  d[13] = d[3];  d[14] = 0.0f;
    d[15] = (fs[0x108 / 4] * fs[0x10c / 4]) * 10.0f;
    d[16] = (fs[0x120 / 4] * fs[0x11c / 4]) * 10.0f;
    d[17] = (fs[0x130 / 4] * fs[0x12c / 4]) * 10.0f;
    d[18] = 0.0f;
    for (int i = 0; i < 11; ++i)
        d[19 + i] = fs[(0xd8 + 4 * i) / 4];
    d[30] = fs[0x104 / 4];                       // original +0x88
    d[7] = 0.0f;
    d[6] = 0.0f;
    d[8] = 1.0f;
    d[9] = d[0];                                 // original +0x34
    d[31] = 0.0f;                                // original +0x8c
    d[32] = 0.0f;                                // original +0x90
    d[33] = 1.0f;                                // original +0x94
    d[34] = d[9];                                // original +0x98

    ShaderCall(0x206, scratch + 0x2c, 0);

    uint32_t bit = 1;
    for (int i = 0; i < 17; ++i) {
        if (g_rasterSlots[i] == raster) {
            g_rasterStageDirty |= bit;
            g_rasterSlots[i] = 0;
        }
        bit <<= 1;
    }

    RasterStageUpdate(face);
    if (!RasterViewerUpdate())
        return;

    // Acquire the scatter raster's lock buffer (vtable +0xc), fill the 4 quad
    // corners with the per-face UV block, then commit (vtable +0x10).
    void* rast = mpScatterRaster;
    void* lock = 0;
    void* rv = *(void**)rast;
    bool ok = ((bool (*)(void*, void**, int, int, int)) * (void**)((char*)rv + 0x8))(
        rast, &lock, 0x1c, 4, 0);
    if (ok) {
        char* dst = (char*)lock;
        MemSet(dst, 0, 0x70);

        float(*c)[7] = (float(*)[7])dst;         // 4 corners, 0x1c bytes apart
        if (*(int*)(*(int*)(g_appProps + 0x3c) + 0x110) == 0) {
            const float unit[4][3] = { { -1.0f, -1.0f, 0.0f }, { 1.0f, -1.0f, 0.0f },
                                       { -1.0f,  1.0f, 0.0f }, { 1.0f,  1.0f, 0.0f } };
            for (int i = 0; i < 4; ++i) { c[i][0] = unit[i][0]; c[i][1] = unit[i][1]; c[i][2] = unit[i][2]; }
        } else {
            const float wide[4][3] = { { -1.03125f, -0.96875f, 0.0f }, { 0.96875f, -0.96875f, 0.0f },
                                       { -1.03125f,  1.03125f, 0.0f }, { 0.96875f,  1.03125f, 0.0f } };
            for (int i = 0; i < 4; ++i) { c[i][0] = wide[i][0]; c[i][1] = wide[i][1]; c[i][2] = wide[i][2]; }
        }

        const uint32_t* uv = kFaceUVTable[face];
        c[0][4] = *(const float*)&uv[0];
        c[0][5] = *(const float*)&uv[1];
        c[0][6] = *(const float*)&uv[2];
        c[1][4] = *(const float*)&uv[3];
        c[1][5] = *(const float*)&uv[4];
        c[1][6] = *(const float*)&uv[5];
        c[2][4] = *(const float*)&uv[9];
        c[2][5] = *(const float*)&uv[10];
        c[2][6] = *(const float*)&uv[11];
        c[3][4] = *(const float*)&uv[6];
        c[3][5] = *(const float*)&uv[7];
        c[3][6] = *(const float*)&uv[8];

        ((void (*)(void*, void*, void*)) * (void**)((char*)rv + 0xc))(rast, mat, stats);
        ((void (*)(void*)) * (void**)((char*)rv + 0x10))(rast);
    }
    RasterFlushStage();
    (void)stats;
    (void)dir;
}
}  // namespace SP

// @ 0x00f9df20
void cTerrainSphere7::UpdateScatter(cScatterViewer* pViewer, Raster_s00f9_df20* pRaster, const void* pData, uint32_t arg)
{
    if (g_16ca5a5) {
        if (mScatterState == 6) {
            cSPTransform_s00f9_df20 xform;
            pViewer->GetTransform(&xform);

            float dx = xform.mOffset.x - mScatterXform.mOffset.x;
            float dy = xform.mOffset.y - mScatterXform.mOffset.y;
            float dz = xform.mOffset.z - mScatterXform.mOffset.z;

            float dist = sqrtf(dz * dz + dy * dy + dx * dx);
            float lenOld = sqrtf(mScatterXform.mOffset.z * mScatterXform.mOffset.z
                                 + mScatterXform.mOffset.y * mScatterXform.mOffset.y
                                 + mScatterXform.mOffset.x * mScatterXform.mOffset.x);
            float lenNew = sqrtf(xform.mOffset.z * xform.mOffset.z
                                 + xform.mOffset.y * xform.mOffset.y
                                 + xform.mOffset.x * xform.mOffset.x);

            if (dist > g_15b14c4 || fabsf(lenOld - lenNew) > g_15b14c0)
                mScatterState = -1;
            else
                mScatterState = 0;
            mScatterXform = xform;
        }
        if (mScatterState == -1) {
            mScatterState = 0;
            while (mScatterState < 6) {
                UpdateScatterTexture(mScatterState, pRaster, pData, arg);
                ++mScatterState;
            }
        } else {
            int32_t face = mScatterState;
            mScatterState = face + 1;
            UpdateScatterTexture(face, pRaster, pData, arg);
        }
    } else {
        for (int face = 0; face < 6; ++face)
            UpdateScatterTexture(face, pRaster, pData, arg);
    }
    IssueScatterShader(0x206, 0, 0);
}

// @ 0x00f9e120
void SP::cTerrainSphere::InitScatterTexture()
{
    FUN_0067dda0();
    g_imageSlot1.GetImageResource(
        GetResMgr()->CreateTexture(0x7df39217u, g_15b11f0, 0x20, 0x20, 1, 0x1009, 0x15, 0));
    g_imageSlot1b.GetImageResource(
        GetResMgr()->CreateTexture(0x3090ff70u, g_15b11f0, 0x20, 0x20, 1, 0x1009, 0x15, 0));

    g_scatterViewer1.Init(true);
    g_scatterViewer1.Clear(0);
    g_scatterViewer1.SetImage(g_pScatterTex1b->mpImage);

    cViewQuad quad;
    quad.x = 0;
    quad.y = 0;
    quad.width = 0x20;
    quad.height = 0x20;
    g_scatterViewer1.SetQuad((uint16_t*)&quad);
}

// @ 0x00f9e1f0
void ShutdownScatterTexture1()
{
    cScatterResource* pTex = g_pScatterTex1;
    if (pTex) {
        g_pScatterTex1 = 0;
        pTex->Release();
    }
    g_scatterViewer1.Destroy();
    cScatterResource* pImage = g_pScatterTex1b;
    if (pImage) {
        g_pScatterTex1b = 0;
        pImage->Release();
    }
}

// @ 0x00f9e280
void cScatterSphere::InitScatterTexture2()
{
    FUN_0067dda0();
    ResMgr* res = GetResMgr();
    g_imageSlot2.GetImageResource(
        res->CreateTexture(0x7ef570ccu, g_15b11f0, g_15b14c8, g_15b14c8, 1, 0x1009, 0x15, 0));

    g_scatterViewer2.Init(false);
    g_scatterViewer2.SetImage(g_pScatterTex2->mpImage);

    cSPColorRGBA_s00f9_df20 clearColor;
    clearColor.r = 0.0f;
    clearColor.g = 0.0f;
    clearColor.b = 0.0f;
    clearColor.a = 0.0f;
    g_scatterViewer2.SetClearColor(clearColor);
    g_scatterViewer2.SetViewAngleY(k_13ec4d8);

    cViewQuad quad;
    quad.x = 0;
    quad.y = 0;
    quad.width = g_15b14c8;
    quad.height = g_15b14c8;
    g_scatterViewer2.SetQuad((uint16_t*)&quad);
}

// @ 0x00f9e350
void ShutdownScatterTexture2()
{
    g_scatterViewer2.Destroy();
    cScatterResource* pImage = g_pScatterTex2;
    if (pImage) {
        g_pScatterTex2 = 0;
        pImage->Release();
    }
}

// @ 0x00f9e3a0
void cScatterHost::RebuildEffects()
{
    mpSensorMgr = (cScatterMgr*)EffectsManagerPtr()->V4c(0xd0a45522u, 0);
    mpEffectMgr = FUN_006eea10();
    mpEffectMgr->V78(7);
    mpEffectMgr->V84((unsigned)g_16ca0d8, GetAppHost()->V50());
    mpSensorMgr->V1c(mpEffectMgr.p);
    mpSensorMgr->V24(2);
    mpSensorMgr->GetProbe(0x8ebc7a73u, 0, (void**)mpProbe.AsOutParam());
    if (mpProbe.p)
        mpProbe->SetActive(0);
    mpSensorMgr->V0c(0);
}

// @ 0x00f9e4d0
void PlanetPass::Run(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    terrain->lastFace = -1;
    if (!viewer) {
        return;
    }
    if (mode == 3) {
        g_16fa3a8 |= 0x200;
        g_16f9674 = 0;
        uint32_t h = GetApp()->Get()->Get();
        terrain->params->Setup(h, 100.0f, 3);
        terrain->RefreshA();
        Raster_s00f9_df20* dst = ResolveRaster(g_16c9f54);
        for (int f = 0; f < 6; ++f) {
            terrain->UpdateScatterTexture(f, dst, g_15b11a0, d);
        }
        for (int i = 0; i < 6; ++i) {
            Raster_s00f9_df20* src = ResolveRaster(terrain->hTex);
            uint32_t info;
            src->m_face = (uint8_t)i;
            if (src->Lock(2, 0, &info)) {
                dst->m_face = (uint8_t)i;
                uint32_t n = dst->Fill(0);
                dst->FillSpriteTexture(info, n, 0);
                src->Unlock(&info);
            }
        }
        return;
    }

    viewer->SetRaster(&raster, 1);
    uint32_t tex[5];
    tex[0] = tex[1] = tex[2] = tex[3] = tex[4] = 0;
    uint32_t type = GetTerraformPlanetType(terrain->GetState()->GetF());
    CfgBlock* cfg = &terrain->GetState()->cfg;
    Material* mat;
    if (type & 1) {
        mat = GetMaterialManager()->GetMaterial(g_15b1150[mode]);
        switch (mode) {
        case 0:
            tex[0] = *g_16c9e44[face];
            tex[1] = *terrain->arrB[face];
            tex[2] = *cfg->p28;
            break;
        case 1:
            tex[0] = *terrain->arrB[face];
            break;
        case 2:
            tex[0] = *terrain->arrA[face];
            tex[1] = *terrain->arrB[face];
            break;
        }
    } else if (type == 2) {
        mat = GetMaterialManager()->GetMaterial(g_15b115c[mode]);
        switch (mode) {
        case 0:
            tex[0] = *g_16c9e44[face];
            tex[1] = *terrain->arrB[face];
            tex[2] = cfg->h24->Get();
            break;
        case 1:
            tex[0] = *terrain->arrB[face];
            break;
        case 2:
            tex[0] = *terrain->arrA[face];
            tex[1] = *terrain->arrB[face];
            break;
        }
    } else if (type == 4) {
        mat = GetMaterialManager()->GetMaterial(g_15b1168[mode]);
        switch (mode) {
        case 0:
            tex[0] = *g_16c9e44[face];
            tex[1] = *terrain->arrB[face];
            tex[2] = cfg->h18->Get();
            tex[3] = *cfg->p10;
            tex[4] = *cfg->p4;
            break;
        case 1:
            tex[0] = *terrain->arrB[face];
            tex[1] = cfg->h18->Get();
            break;
        case 2:
            tex[0] = *terrain->arrA[face];
            break;
        }
    } else {
        return;
    }

    bool flipX = false, flipY = false, alt = false;
    switch (face) {
    case 0: flipX = true; alt = false; flipY = true; break;
    case 1:
    case 2:
    case 3: flipX = false; flipY = false; alt = false; break;
    case 4: flipX = true; flipY = false; alt = true; break;
    case 5: flipX = false; alt = true; flipY = true; break;
    }

    float sgn = (face & 1) ? -1.0f : 1.0f;
    float sv[3];
    sv[0] = sgn; sv[1] = 1.0f; sv[2] = sgn;
    const uint8_t* ax = &g_1490418[(face >> 1) * 4];
    int i0 = ax[0], i1 = ax[1], i2 = ax[2];
    TerrainParams* tp = terrain->params;
    float p0 = sv[i0], p1 = sv[i1], p2 = sv[i2];
    float q[3];
    q[0] = tp->a; q[1] = tp->b; q[2] = tp->c;
    float out4[4];
    terrain->GetState()->Compute(out4);
    ShConst sh;
    sh.Zero();
    CamObj* cam = terrain->GetCam();
    float cx = cam->x, cy = cam->y, cz = cam->z;
    sh.Set(0, cx, cy, cz, terrain->GetState()->GetG());
    sh.Set(1, q[0], q[1], q[2], 0.0f);
    sh.Set(2, (float)i0, (float)i1, (float)i2, 0.0f);
    sh.Set(3, p0, p1, p2, 0.0f);
    sh.Set(4, out4[0], out4[1], out4[2], out4[3]);

    if (viewer->Update()) {
        float* vb;
        uint32_t lockInfo;
        if (LockDraw(2, 4, &vb, &lockInfo)) {
            memset(vb, 0, 0x60);
            PutF(vb + 4, 0.0f); PutF(vb + 5, 0.0f);
            PutF(vb + 10, 1.0f); PutF(vb + 11, 0.0f);
            PutF(vb + 16, 1.0f); PutF(vb + 17, 1.0f);
            PutF(vb + 22, 0.0f); PutF(vb + 23, 1.0f);
            if (alt) {
                SetV(vb + 0, 1.0f, 1.0f, 0.2f);
                SetV(vb + 6, 1.0f, -1.0f, 0.2f);
                SetV(vb + 12, -1.0f, -1.0f, 0.2f);
                SetV(vb + 18, -1.0f, 1.0f, 0.2f);
            } else {
                SetV(vb + 0, 1.0f, 1.0f, 0.2f);
                SetV(vb + 6, -1.0f, 1.0f, 0.2f);
                SetV(vb + 12, -1.0f, -1.0f, 0.2f);
                SetV(vb + 18, 1.0f, -1.0f, 0.2f);
            }
            if (flipX) {
                vb[0] = -vb[0]; vb[6] = -vb[6]; vb[12] = -vb[12]; vb[18] = -vb[18];
            }
            if (flipY) {
                vb[1] = -vb[1]; vb[7] = -vb[7]; vb[13] = -vb[13]; vb[19] = -vb[19];
            }
            mat->cs->Dispatch();
            SetTexture(0, tex[0]);
            SetTexture(1, tex[1]);
            SetTexture(2, tex[2]);
            SetTexture(3, tex[3]);
            SetTexture(4, tex[4]);
            IssueDraw(3, d);
        }
        viewer->Finish();
    }
}

// @ 0x00f9eda0
void cTerrainSphere8::RefreshTerraform()
{
    TerrainEditor_s00f9_df20()->FUN_00f67560();
    mpPlanet->BuildHeightHistogram();

    cSPVector3_s00f9_df20 v;
    v.x = g_1471064;
    v.y = g_1471064;
    v.z = g_1471064;
    GetPropertyAsVector3(mpPropList, 0x3a23f98u, &v);

    float ratio = mpPlanet->HeightToRatio(v.x);
    float dest[2];
    float* pValues = mpParams->mValues;
    dest[0] = pValues[0];
    dest[1] = pValues[1];
    mpPlanet->FUN_00fb9420(v.x, ratio, dest);

    FUN_00f9a610();

    cPropertyList_s00f9_df20* pList = mpPropList;
    if (pList) {
        cProperty* pProp;
        if (pList->V24(0xd2f669ecu, &pProp)
            && pProp->mType == 0xa
            && *pProp->GetUInt() != 1)
            return;
    }
    mpPlanet->RefreshTerraformValues();
}

// @ 0x00f9fef0
void TerrainSphereReg::Register(RegObj* obj)
{
    void* self = this;
    void* handle = (self == 0) ? 0 : (char*)self + 4;

    void* found = ((void* (__thiscall*)(void*, int))obj->mpVtbl->mpfnFindEntry)(obj, 8);
    if (found != handle) {
        SP::cDirectPropertyList_s006a_22a0* props =
            *(SP::cDirectPropertyList_s006a_22a0**)0x015fd918;   // _sAppProperties
        bool cVar2 = props->GetDescription(0x201a4e50);
        bool cVar3 = props->GetDescription(0xe13ce337);
        if (cVar2) {
            ((SP::cTerrainSphere_s00f9_fef0*)props)->InitializeStaticRTTTextures();
            if (cVar3)
                FUN_00f9e3a0(self);
        }
        void* add = obj->mpVtbl->mpfnAddEntry;
        ((void (__thiscall*)(void*, void*, int, int))add)(obj, handle, 7, 0);
        ((void (__thiscall*)(void*, void*, int, int))add)(obj, handle, 8, 0);
        ((void (__thiscall*)(void*, void*, int, int))add)(obj, handle, 0x21, 0);
        ModelMgrObj* mm = (ModelMgrObj*)SP::ModelManager();
        ModelInstObj* mi = (ModelInstObj*)mm->mpVtbl->mGetInstance(mm, (void*)0x03fbae24);
        void* h = mi->mpVtbl->mGetHandle(mi, 10, 0);
        ((void (__thiscall*)(void*, void*))add)(obj, h);
        mi->mpVtbl->mSetActive(mi, 1);
        EffectMgrObj* em = (EffectMgrObj*)EffectsManagerPtr_s00f9_fef0();
        EffectInstObj* ei = (EffectInstObj*)em->mpVtbl->mGetInstance(em, (void*)0x03fbae24);
        ((void (__thiscall*)(void*, int))ei->mpVtbl->mApply)(ei, 0);
    }
}

// @ 0x00fa0010
bool TerrainSphereLike::CopyFaceA(int face, const float* rect)
{
    if (!mpSurfaces)
        return false;
    void* other = ((SurfaceHolder*)mpSurfaces)->mSurface8;
    if (!other)
        return false;
    TexInst* t = mFacesA[face];
    if (!(t->mFlags & 1))
        FUN_0067dd60_s00f9_fef0()->Release(t);
    void* data = (void*)t->mpData;
    bool ok = CopyImageRectToSurface(data, (int)other, face, rect) != 0;
    return ok;
}

// @ 0x00fa0070
bool TerrainSphereLike::CopyFaceB(int face, const float* rect)
{
    if (!mpSurfaces)
        return false;
    void* other = ((SurfaceHolder*)mpSurfaces)->mSurfaceC;
    if (!other)
        return false;
    TexInst* t = mFacesB[face];
    if (!(t->mFlags & 1))
        FUN_0067dd60_s00f9_fef0()->Release(t);
    void* data = (void*)t->mpData;
    bool ok = FUN_00f9f360(data, (int)other, face, rect) != 0;
    return ok;
}

// @ 0x00fa00d0
bool TerrainSphereLike::CopyFaceC(int face, const float* rect)
{
    if (!mpSurfaces)
        return false;
    void* other = ((SurfaceHolder*)mpSurfaces)->mSurface10;
    if (!other)
        return false;
    TexInst* t = mFacesC[face];
    if (!(t->mFlags & 1))
        FUN_0067dd60_s00f9_fef0()->Release(t);
    void* data = (void*)t->mpData;
    bool ok = FUN_00f9f4c0(data, (int)other, face, rect) != 0;
    return ok;
}

// @ 0x00fa0130
Quat TerrainSphereQ::BuildSurfaceOrientationFromDir(const Vec3& dir) const
{
    if (dir.x * dir.x + dir.y * dir.y + dir.z * dir.z > 1.0f) {
        Quat q;
        QuaternionFromDirections(&q, &kUpDir, &dir);
        return BuildSurfaceOrientation(dir, q);
    }
    return kDefaultQuat;
}

// @ 0x00fa01e0
void __cdecl BuildDecalBox(void* xform /*arg0*/, void* data /*arg1*/, unsigned id /*arg2*/, void* a3 /*arg3*/)
{
    ImageResHeader res;
    BuilderParam    bp;
    Quat   q;
    unsigned v[4];

    operator_new_arr(&res, 0, 0x78);
    GetImageResourceImpl(&res, id);
    v[0] = (id == 0);
    v[1] = 0x3f800000;
    v[2] = (unsigned)data;
    v[3] = 0;

    operator_new_arr(&bp, 0, 0x7c);
    memcpy(&bp, (const void*)0x01490428, 0x44);

    QuaternionFromMatrix33(&q, (const char*)xform + 0x14, 0);

    TerrainEditorImpl((char*)xform + 4, &q, v, &res, &bp, a3, 0, 0, 0, 0);
    DecalBoxBuilderImpl((char*)xform + 4, &q, v, &res, &bp, a3, 0, 0, 0, 0);

    if (v[0] != 0)
        ((AtomicRef*)(v[0] + 8))->Release();
}

// @ 0x00fa0360
void ShutdownRTTSphere()
{
    if (!g_rttActive)
        return;
    RTTMgr* mgr = (RTTMgr*)FUN_0067dda0_s00f9_fef0();
    if (g_pRTT0)
        FUN_00f9e1f0();
    if (g_pRTT1)
        FUN_00f9e350();
    unsigned* h = g_rttHandles;
    unsigned* n = (unsigned*)g_rttNames;
    do {
        mgr->FreeRTT(n[0], n[1]);
        *h = 0;
        n += 2;
        ++h;
    } while ((int)n < (int)g_16ca404);
    mgr->FreeRTT(g_colorMap[0], g_colorMap[1]);
    g_texTerrain = 0;
    g_viewer.Shutdown();
    FUN_00762a00(g_pSomeTex);
}

// @ 0x00fa0400
void InitRTTSphere()
{
    RTTMgr2* mgr = (RTTMgr2*)FUN_0067dda0_s00f9_fef0();
    for (int i = 0; i < 6; ++i) {
        unsigned out[2];
        g_rttHandles[i] = 0;
        mgr->mpVtbl->CreateTex(out, 0x100, 0x100, 0x15, 0, -1, 0);
        g_rttNames[i][0] = out[0];
        g_rttNames[i][1] = out[1];
        mgr->mpVtbl->SetName(out[0], out[1], "TerrainRTTs");
        g_rttHandles[i] = mgr->mpVtbl->MakeTexFromRes2(out[0], out[1]);
    }
    {
        unsigned out[2];
        mgr->mpVtbl->CreateTex(out, 0x100, 0x100, 0x15, 0, 0x956a72c0, 0);
        g_colorMap[0] = out[0];
        g_colorMap[1] = out[1];
        mgr->mpVtbl->SetName(out[0], out[1], "TerrainColorMap");
        g_texTerrain = mgr->mpVtbl->MakeTexFromRes(out[0], out[1]);
    }
    ViewerInit(g_viewerObj, true);
    ViewerClear(g_viewerObj, 0);
    ViewerSetTex(g_viewerObj, g_texTerrain);
    unsigned short v[4];
    v[0] = 0; v[1] = 0; v[2] = 0x100; v[3] = 0x100;
    ViewerSetRect(g_viewerObj, v);
}

// @ 0x00fa0560
void GeomMsgOwner::AddGeometryChangeMessage(int a2, int a3)
{
    if (!mpHandler)
        return;
    MsgObj* p = (MsgObj*)EAAllocate(0x40, "Terrain/Sphere/kMessageTerrainGeometryChange", 0, 0, 0, 0);
    if (p) {
        p->mpVtbl30 = 0;
        p->mpVtbl = (MsgVtbl*)0x013eb90c;
        _InterlockedExchange((volatile long*)&p->mRef, 0);
        p->mpVtbl = (MsgVtbl*)0x013eb844;
        p->f38 = 0;
        p->mpVtbl->mAddRef(p);
    } else {
        p = 0;
    }
    p->mpVtbl30 = (MsgVtbl*)0x0182c582;
    p->f08 = a2;
    p->f10 = a3;

    GeomChangeMsg msg;
    msg.mKind = 1;
    msg.mReserved04 = 0;
    msg.mReserved0c = 0;
    msg.mReserved10 = 0;
    msg.mFlag08 = false;
    msg.mReserved1c = 0;
    msg.mReserved20 = 0;
    msg.mReserved24 = 0;
    msg.mReserved28 = 0;
    msg.mReserved2c = 0;
    msg.mEventKind = 0x03d5bf9a;
    msg.mpMessage = p;

    ((GeomHandlerOps*)mpHandler)->FUN_00f99f20(this, a3, a2, &mChangeState);
    msg.mpHandler = mpHandler;
    msg.mpApp = (AppObj*)FUN_0067dd50_s00f9_fef0();
    unsigned id = msg.mpHandler->mpVtbl->mSend(msg.mpHandler, 0, &msg);
    mMsgId = msg.mpApp->mpVtbl->mRegisterId(msg.mpApp, id);
    p->mpVtbl->mRelease(p);
}

// @ 0x00fa0670
Elem16* __cdecl PartitionElem16(Elem16* lo, Elem16* hi, void* a2, void* a4, unsigned key)
{
    for (;; lo = lo + 1) {
        while (lo->key < key)
            lo = lo + 1;
        hi = hi - 1;
        while (key < hi->key)
            hi = hi - 1;
        if (lo >= hi)
            return lo;
        Elem16 tmp = *lo;
        *lo = *hi;
        *hi = tmp;
    }
}

// @ 0x00fa06e0
void __cdecl SortElem16Pass(Elem16* first, Elem16* last, Elem16* end, unsigned key)
{
    FUN_00f9f7b0(first, last, key);
    for (Elem16* p = last; p < end; ++p) {
        if (p->key < first->key) {
            Elem16 tmp = *p;
            *p = *first;
            FUN_00f9af30(first, 0, (int)(last - first), 0, tmp, key);
        }
    }
    FUN_00f9f810(first, last, key);
}

// @ 0x00fa0780
void TerrainSphereRes::Dtor()
{
    char* p = (char*)this;
    *(void**)(p + 0x00) = (void*)0x01490be8;
    *(void**)(p + 0x04) = (void*)0x01490bd4;
    *(void**)(p + 0x08) = (void*)0x01490bc4;
    *(void**)(p + 0x0c) = (void*)0x01490ba0;
    *(void**)(p + 0x10) = (void*)0x01490b8c;
    _InterlockedDecrement((volatile long*)0x016c9e88);
    _InterlockedExchange((volatile long*)0x016c9e5c, 0);

    VirtualRelease(*(void**)(p + 0x28), 1, 1);
    VirtualRelease(*(void**)(p + 0x214), 1, 1);

    RelPtr(*(void**)(p + 0x2c));
    RelPtr(*(void**)(p + 0x308));

    *(void**)(p + 0x30) = (void*)0x01490b80;
    *(void**)(p + 0x74) = (void*)0x01490b80;
    *(void**)(p + 0xb8) = (void*)0x01490b80;

    for (int i = 0; i < 6; ++i)
        RelPtr(*(void**)(p + 0x178 - i * 4));
    for (int i = 0; i < 6; ++i)
        RelPtr(*(void**)(p + 0x190 - i * 4));
    for (int i = 0; i < 6; ++i)
        RelPtr(*(void**)(p + 0x160 - i * 4));

    *(void**)(p + 0x00) = (void*)0x013eb938;
    *(void**)(p + 0x04) = (void*)0x013eb394;
}

// @ 0x00fa0dc0
void DirtyFlag::InitBuffer()
{
    operator_new_arr(&mBuffer[0], 0, 0x80);
}

// @ 0x00fa0e10
void DirtyFlag::SetFlag(bool which)
{
    if (which)
        Flag0() = 0;
    else
        Flag1() = 0;
}

// @ 0x00fa0e40
void DirtyFlag::Dirty(unsigned char bits)
{
    mDirtyBits[1 - miDirty] |= bits;
}

// @ 0x00fa0e60
bool DirtyFlag::TestFlag(unsigned char bits)
{
    return (Flag0() & bits) != 0;
}

// 0x00fa0f10 (byte-exact lifted version: match/slices/s00fa0f10/s00fa0f10.cpp)
int JobHolder::Release()
{
    return (mObj).Release();
}

struct ImpostorTextureDesc {
    uint32_t mSource;                       // +0x00
    uint32_t mProperty;                     // +0x04
    uint32_t mFlags;                        // +0x08
};

// @ 0x00fa1650
void cTerrainSphere::GenerateImpostor(unsigned int face)
{
    if (mImpostorRectId == 0xffffffffu) {
        cRenderTargetHandle target;
        RenderManager()->CreateRenderTarget(&target, 0x80, 0x80, 0x15, 1, -1, 0);
        mpImpostorRaster = (void*)target.mRaster;
        mImpostorRectId = target.mRectId;
        RenderManager()->InitializeRenderTarget(target.mRaster, target.mRectId,
                                                kImpostorRenderTargetName);
        if (mImpostorRectId == 0xffffffffu)
            return;
    }

    mImpostorFace = face;

    ImpostorTextureDesc desc[4] = {
        { mImpostorSource18, 0x2f4e681c, (mImpostorFlags20 & 0xe6ff28ff) | 0x6002800 },
        { mImpostorSource18, 0x2f4e681c, (mImpostorFlags20 & 0xe0ff28ff) | 0x2800 },
        { mImpostorSource18, 0x2f4e681c, (mImpostorFlags20 & 0xe4ff28ff) | 0x4002800 },
        { mImpostorSource18, 0x2f4e681c, (mImpostorFlags20 & 0xe5ff28ff) | 0x5002800 },
    };

    cResourceSource* source = GetResourceSource();
    mpImpostorDiffuseTexture.Set(source->CreateTexture((void*)desc[1].mSource, desc[1].mFlags,
                                                       0x80, 0x80, 1, 0x1008, 0x15, 0));
    source = GetResourceSource();
    mpImpostorSpecTexture.Set(source->CreateTexture((void*)desc[2].mSource, desc[2].mFlags,
                                                    0x80, 0x80, 1, 0x1008, 0x15, 0));
    source = GetResourceSource();
    mpImpostorNormalTexture.Set(source->CreateTexture((void*)desc[3].mSource, desc[3].mFlags,
                                                      0x80, 0x80, 1, 0x1008, 0x15, 0));
    source = GetResourceSource();
    mpImpostorScatterTexture.Set(source->CreateTexture((void*)desc[0].mSource, desc[0].mFlags,
                                                       0x20, 0x20, 1, 0x1008, 0x15, 0));

    AddGeometryChangeMessage(0, 0);
}

// @ 0x00fa0f90
bool cTerrainSphere::Initialize(bool createWeather)
{
    g_TerrainInitCount++;
    mpVertexFormat = CreateVertexFormat("V3FC4BT3F", 0x10, 0);

    cDirectPropertyList* props = g_AppProperties;
    mIntProp = props->GetIntProperty(0xe8172372);
    mFloatProp0 = props->GetFloatProperty(0x54046ee);
    mFloatProp1 = props->GetFloatProperty(0x144ca94f);
    mFloatProp2 = props->GetFloatProperty(0x54046fa);

    mpDecalManager = new("Terrain/Sphere/DecalManager", 0, 0, 0, 0) cDecalManagerImpl(this);
    mpDecalManager->AddRef();

    mpViewer = new("Terrain/Sphere/mTerrainViewer", 0, 0, 0, 0) cViewer;
    mpViewer->Init(0);

    Clear(mVecB[0]); Clear(mVecC[0]); Clear(mVecA[0]);
    Clear(mVecB[1]); Clear(mVecC[1]); Clear(mVecA[1]);
    Clear(mVecB[2]); Clear(mVecC[2]); Clear(mVecA[2]);
    Clear(mVecB[3]); Clear(mVecC[3]); Clear(mVecA[3]);
    Clear(mVecB[4]); Clear(mVecC[4]); Clear(mVecA[4]);
    Clear(mVecB[5]); Clear(mVecC[5]); Clear(mVecA[5]);

    if (!mpStateMgr) {
        mpStateMgr = new("Terrain/Sphere/cTerrainStateMgr", 0, 0, 0, 0) cTerrainStateMgr(this);
        mpStateMgr->Init(1);
    }
    cTerrainShaderBlock* block = mpStateMgr->mpBlock;
    UpdateShaderState(mpPlanet->mField18, block->mField28, block->mField1C, block->mField20);
    cTerrainPlanetData* planet = mpPlanet;
    mFloat360 = planet->mField34;
    mFloat364 = planet->mField3C * planet->mField38;
    UpdateControlMapParams();

    if (!mpWeather.mp && createWeather) {
        mpWeather = new("Terrain/Sphere/cWeatherManager", 0, 0, 0, 0) cWeatherManager;
        mpWeather.mp->Init(this);
    }

    for (int i = 0; i < 6; i++)
        InitFace(i);

    if (!g_TerrainStaticsReady) {
        InitStatics();
        InitializeVBInfoArray();
        g_TerrainStaticsReady = true;
    }

    mpQuadPool = new("Terrain/cQuadBuffersPool", 0, 0, 0, 0) cQuadBuffersPool;
    mpQuadPool->Init(g_TerrainPoolParam, mIntProp);

    for (int i = 0; i < 6; i++) {
        {
            mQuadsA[i] = new("Terrain/Sphere/cTerrainSphereQuad", 0, 0, 0, 0) cTerrainSphereQuad;
            Vec2 scale(1.0f, 1.0f);
            Vec2 offset(0.0f, 0.0f);
            mQuadsA[i]->Init(this, 0, i, &offset, &scale, 1);
        }
        {
            mQuadsB[i] = new("Terrain/Sphere/cTerrainSphereQuad", 0, 0, 0, 0) cTerrainSphereQuad;
            Vec2 scale(1.0f, 1.0f);
            Vec2 offset(0.0f, 0.0f);
            mQuadsB[i]->Init(this, 0, i, &offset, &scale, 2);
        }
    }

    cMessageServer* server = MessageServer();
    server->AddHandler(&mHandlerBase, 0x87d5f9bf);
    server->AddHandler(&mHandlerBase, 0x3d5bf9a);
    server->AddHandler(&mHandlerBase, 0x44edd9a);
    server->AddHandler(&mHandlerBase, 0x44edd9c);

    mpImpostorJob = new("Terrain/Sphere/cTerrainSphereImpostorJob", 0, 0, 0, 0) cTerrainSphereImpostorJob;
    mImpostorJobState = -1;
    mFlag4F4 = false;

    mpShared = GetResourceSource()->Get(g_SharedResourceID, 0, 0);
    return true;
}

// @ 0x00fa1840
void Rec20Vector::insert(Rec20* pos, unsigned count, Rec20* value)
{
    if (count <= (unsigned)(cap - end)) {
        if (count > 0) {
            const Rec20 temp(*value);
            const unsigned after = (unsigned)(end - pos);
            Rec20* const oldEnd = end;
            if (count < after) {
                CopyUninitialized20(value, oldEnd - count, oldEnd, oldEnd, pos);
                end += count;
                CopyBackward20(pos, oldEnd - count, oldEnd);
                FillRange20(pos, pos + count, &temp);
            } else {
                FillCount20(oldEnd, count - after, &temp);
                end += count - after;
                CopyUninitialized20(pos, pos, oldEnd, end, pos);
                end += after;
                FillRange20(pos, oldEnd, &temp);
            }
        }
    } else {
        const unsigned oldSize = (unsigned)(end - begin);
        const unsigned grow = oldSize > 0 ? 2 * oldSize : 1;
        const unsigned newCap = grow > oldSize + count ? grow : oldSize + count;

        Rec20* const newBegin = newCap != 0
            ? (Rec20*)operator new(newCap * sizeof(Rec20), kAllocTagSimulator,
                                   0, 0, kEastlAllocFile, 0xd1)
            : 0;
        Rec20* newEnd = Copy20(begin, pos, newBegin);
        FillCount20(newEnd, count, value);
        newEnd = Copy20(pos, end, newEnd + count);

        if (begin != 0 && begin != &mInline)
            EastlDeallocate(begin);
        begin = newBegin;
        end = newEnd;
        cap = newBegin + newCap;
    }
}

// @ 0x00fa1a30
void __cdecl QuickSort16(SortRec16* first, SortRec16* last, int depth, SortLess16 compare)
{
    while ((last - first) > 28 && depth > 0) {
        SortRec16* const cut = PartitionElem16(
            first, last,
            *MedianElem16(first, first + (last - first) / 2, last - 1, compare),
            compare);
        QuickSort16(cut, last, --depth, compare);
        last = cut;
    }
    if (depth == 0)
        SortElem16Pass(first, last, last, compare);
}

// @ 0x00fa1b10
void* __cdecl DestroyImpostorRange(ImpostorRecord110* first, ImpostorRecord110* last, ImpostorRecord110* out)
{
    if (first != last) {
        do {
            void* p = first->mpData;
            if (p != 0 && p != first->mpInline)
                EastlDeallocate(p);
            ++first;
            ++out;
        } while (first != last);
    }
    return out;
}

// @ 0x00fa1bc0
cTerrainSphere_s00fa_1bc0::cTerrainSphere_s00fa_1bc0()
{
    mF28 = 0;
    mSteps0.Init();
    mF2C = 0;
    mSteps1.Init();
    mSteps2.Init();
    mF10C = 5.0f;
    mFC = 0;
    mF100 = 0;
    mF104 = 0;
    mF108 = true;
    mF110 = false;
    mF111 = false;
    mF114 = 0;
    mF148[0] = 0;
    mF148[1] = 0;
    mF148[2] = 0;
    mF148[3] = 0;
    mF148[4] = 0;
    mF148[5] = 0;
    mF148[6] = 0;
    mF148[7] = 0;
    mF148[8] = 0;
    mF148[9] = 0;
    mF148[10] = 0;
    mF148[11] = 0;
    mF148[12] = 0;
    mF148[13] = 0;
    mF148[14] = 0;
    mF148[15] = 0;
    mF148[16] = 0;
    mF148[17] = 0;
    mF148[18] = 0;
    mF148[19] = 0;
    mF148[20] = 0;
    mF1A4[0] = 0;
    mF1A4[1] = 0;
    mF1A4[2] = 0;
    mF1B8 = 0;
    mListBegin = 0;
    mListEnd = 0;
    mF1CC = 0;
    mF1D0 = 4;
    mF1D4.d = 16;
    mF1D8 = 25.0f;
    mF1DC = 100.0f;
    mF1E0 = 1.0f;
    mF1E4 = 1.0f;
    mF1E8 = true;
    mF1EC[0] = 1.0f;
    mF1EC[1] = 1.0f;
    mF1EC[2] = 1.0f;
    mF1EC[3] = 1.0f;
    mF1EC[4] = 1.0f;
    mF1EC[5] = 1.0f;
    mF1EC[6] = 1.0f;
    mF1EC[7] = 1.0f;
    mF20C[0] = 0;
    mF20C[1] = 0;
    mF20C[2] = 0;
    mF20C[3] = 0;
    mF20C[4] = 0;
    mF20C[5] = 0;
    mF22C[0] = 0;
    mF22C[1] = 0;
    mF22C[2] = 0;
    mF240[0] = 0;
    mF240[1] = 0;
    mF240[2] = 0;
    mF254[0] = 0;
    mF254[1] = 0;
    mF254[2] = 0;
    mF268[0] = 0;
    mF268[1] = 0;
    mF268[2] = 0;
    mF27C[0] = 0;
    mF27C[1] = 0;
    mF27C[2] = 0;
    mF290[0] = 0;
    mF290[1] = 0;
    mF290[2] = 0;
    mF2A4[0] = 0;
    mF2A4[1] = 0;
    mF2A4[2] = 0;
    mF2B8[0] = 0;
    mF2B8[1] = 0;
    mF2B8[2] = 0;
    mF2CC[0] = 0;
    mF2CC[1] = 0;
    mF2CC[2] = 0;
    mF2E0[0] = 0;
    mF2E0[1] = 0;
    mF2E0[2] = 0;
    mF2F4[0] = 0;
    mF2F4[1] = 0;
    mF2F4[2] = 0;
    mF308 = 0;
    mF30C[0] = g_Float016c9e98[0];
    mF30C[1] = g_Float016c9e98[1];
    mF30C[2] = g_Float016c9e98[2];
    mF30C[3] = g_Float016c9e98[3];
    mF30C[4] = g_Float016c9e98[0];
    mF30C[5] = g_Float016c9e98[1];
    mF30C[6] = g_Float016c9e98[2];
    mF30C[7] = g_Float016c9e98[3];
    mF30C[8] = g_Float016c9e98[0];
    mF30C[9] = g_Float016c9e98[1];
    mF30C[10] = g_Float016c9e98[2];
    mF30C[11] = g_Float016c9e98[3];
    mF34C[0] = 1.0f;
    mF34C[1] = 1.0f;
    mF34C[2] = 1.0f;
    mF34C[3] = 1.0f;
    mF34C[4] = 1.0f;
    mF33C = false;
    mF33D = false;
    mF340 = 0;
    mF344 = 0;
    mF348 = false;
    mF360 = -1.0f;
    mF364 = -1.0f;
    mF36C = 0;
    mF370 = false;
    mF4F4 = false;
    mF4F5 = true;
    mF758[0] = 0;
    mF758[1] = 0;
    mF758[2] = 0;
    mF76C = false;
    mF770[0] = 0;
    mF770[1] = 0;
    mF770[2] = 0;
    mF784[0] = 0;
    mF784[1] = 0;
    mF784[2] = 0;
    mF798[0] = 0;
    mF798[1] = 0;
    mF798[2] = 0;
    mF7AC = 0;
    AllocTag tag;
    mF7B0 = 0;
    mF7B8 = 0;
    mF7B4 = 0;
    mObj7C4.Init(0, tag);
    mF7D8[0] = 0;
    mF7D8[1] = 0;
    mF7D8[2] = 0;
    mF7EC[0] = 0;
    mF7EC[1] = 0;
    mF7EC[2] = 0;
    mF800[0] = 0;
    mF800[1] = 0;
    mF800[2] = 0;
    mF814[0] = 0;
    mF814[1] = 0;
    mF814[2] = 0;
    mF880 = false;
    mF884[0] = 0;
    mF884[1] = 0;
    mF884[2] = 0;
    mF884[3] = 0;
    mF884[4] = 0;
    mF898 = -1;
    mF89C = -1;
    mF8A0 = 0;
    mF8A4 = -1;
    mF8A8 = 0;
    mF8AC = false;
    mF8B0[0] = 0;
    mF8B0[1] = 0;
    mF8B0[2] = 0;
    mF8C4[0] = 0;
    mF8C4[1] = 0;
    mF8C4[2] = 0;
    mF8D8[0] = 0;
    mF8D8[1] = 0;
    mF8D8[2] = 0;
    mF8D8[3] = 0;
    mF8EA = 0;
    mF8E8 = 0;
    mF8EC[0] = g_Float016c9e8c[0];
    mF8EC[1] = g_Float016c9e8c[1];
    mF8EC[2] = g_Float016c9e8c[2];
    mF8F8 = 1.0f;
    mMat8FC.Assign(&g_IdentityMatrix);
    mF920 = -1;
    mF924 = 0;
    mF928 = 0;
    ++g_TerrainSphereCount;
    mFA1C[0] = 0.0f;
    mFA1C[1] = 0.0f;
    mFA1C[2] = 0.0f;
    mFA1C[3] = 0.0f;
    mFA1C[4] = 0.0f;
    mFA1C[5] = 0.0f;
    mFA1C[6] = 0.0f;
    mFA38[0] = g_Float015b117c[0];
    mFA38[1] = g_Float015b117c[1];
    mFA38[2] = g_Float015b117c[2];
    mFA38[3] = g_Float015b117c[3];
    mFA48 = 0;
    mFA4C = 0;
    g_pTerrainSphere = this;
    FUN_011e073e(mMemset6D8, 0, 0x80);
    InitSubObjects();
    for (int i = 0; i < 6; ++i) {
        mVec[i].x = 0.0f; mVec[i].y = 0.0f; mVec[i].z = 0.0f; mVec[i].w = 0.0f;
        mVec[i + 6].x = 0.0f; mVec[i + 6].y = 0.0f; mVec[i + 6].z = 0.0f; mVec[i + 6].w = 0.0f;
        mA118[i] = 0;
        mA118[i + 6] = 0;
    }
    Clear(mVec[12]);
    Clear(mVec[13]);
    Clear(mVec[14]);
    Clear(mVec[15]);
    Clear(mVec[16]);
    Clear(mVec[17]);
    mF344 = 0;
    mF368 = false;
    mF369 = false;
    mF36C = 0;
}

// @ 0x00fa23d0
void cTerrainSphere_s00fa_1bc0::RemoveListEntry(uint32_t value)
{
    int n = (int)(mListEnd - mListBegin);
    if (n <= 0)
        return;
    int i = 0;
    while (mListBegin[i] != value) {
        if (++i >= n)
            return;
    }
    uint32_t* dst = mListBegin + i;
    uint32_t* src = dst + 1;
    if (src < mListEnd)
        FUN_011e0744(dst, src, (unsigned)((char*)mListEnd - (char*)src));
    --mListEnd;
    mF1D4.b = 1;
}

// @ 0x00fa2440
void DecalPtrVec::Insert(DecalPtr* pos, DecalPtr* value)
{
    DecalPtr* e = mEnd;
    if (e != mCapacity) {
        if (value >= pos && value < e)
            ++value;
        if (e) {
            RefCounted* p = e[-1].mPtr;
            e->mPtr = p;
            if (p)
                p->AddRef();
            e->mField4 = e[-1].mField4;
        }
        DecalVecMoveBack_00f9aff0(pos, e - 1, e);
        RefCounted* src = value->mPtr;
        RefCounted* old = pos->mPtr;
        if (src != old) {
            if (src)
                src->AddRef();
            pos->mPtr = src;
            if (old)
                old->Release();
        }
        pos->mField4 = value->mField4;
        mEnd = e + 1;
        return;
    }

    int n = (int)(e - mBegin);
    int cap;
    if (n == 0)
        cap = 1;
    else {
        cap = n * 2;
        if (cap == 0) {
            n = 0;
            goto alloc_done;
        }
    }
    n = (int)FUN_00f473a0((unsigned)(cap * 8), "Simulator", 0, 0,
                          (const char*)0x013ebb38, 0xd1);
alloc_done:
    {
        DecalPtr* oldBegin = mBegin;
        DecalPtr* p = (DecalPtr*)DecalVecCopyRange_00f9adf0(oldBegin, pos, (DecalPtr*)n);
        DecalVecDestroyRange_00f9ae40(oldBegin, pos, (DecalPtr*)n);
        if (p) {
            RefCounted* src = value->mPtr;
            p->mPtr = src;
            if (src)
                src->AddRef();
            p->mField4 = value->mField4;
        }
        DecalPtr* oldEnd = mEnd;
        DecalPtr* q = (DecalPtr*)DecalVecCopyRange_00f9adf0(pos, oldEnd, p + 1);
        DecalVecDestroyRange_00f9ae40(pos, oldEnd, p + 1);
        if (mBegin && ((int*)mBegin)[-1] != 0)
            FUN_00f47380(mBegin);
        mBegin = (DecalPtr*)n;
        mEnd = q;
        mCapacity = (DecalPtr*)n + cap;
    }
}

// @ 0x00fa25c0
DecalPtr* DecalPtrVec::EraseRange(DecalPtr* first, DecalPtr* last)
{    DecalPtr* oldEnd = mEnd;
    DecalPtr* const pos = (DecalPtr*)DecalVecMoveDown_00f9ae80(last, oldEnd, first);
    DecalPtr* e = mEnd;
    for (DecalPtr* p = pos; p < e; ++p) {
        RefCounted* o = p->mPtr;
        if (o)
            o->Release();
    }
    mEnd -= last - first;
    return first;}

// @ 0x00fa2620
void __stdcall FUN_00fa2620(DecalArrayElem* first, DecalArrayElem* last)
{
    for (; first < last; ++first) {
        void* p = first->mPtr;
        if (p != 0 && p != first->mAlt)
            FUN_00f47380(p);
    }
}

// @ 0x00fa26e0
void Rec20Vector_s00fa_1bc0::assign(const Rec20_s00fa_1bc0* first, const Rec20_s00fa_1bc0* last, const Rec20_s00fa_1bc0& value)
{
    uint32_t n = (uint32_t)(last - first);
    if ((uint32_t)(mCapacity - mBegin) < n) {
        Rec20_s00fa_1bc0* buf = Realloc(n, first, last);
        if (mBegin && mBegin != mInline)
            FUN_00f47380(mBegin);
        mBegin = buf;
        mEnd = buf + n;
        mCapacity = buf + n;
        return;
    }
    uint32_t have = (uint32_t)(mEnd - mBegin);
    if (n <= have) {
        mEnd = (Rec20_s00fa_1bc0*)FUN_00951bf0(first, last, mBegin);
        return;
    }
    Rec20_s00fa_1bc0* mid = (Rec20_s00fa_1bc0*)first + have;
    FUN_00951bf0(first, mid, mBegin);
    FUN_00f9f8f0(&value, mid, last, mEnd, last);
    mEnd = (Rec20_s00fa_1bc0*)last;
}

// @ 0x00fa27d0
uint32_t cTerrainSphere_s00fa_1bc0::AllocDecalIndex(uint32_t layer)
{
    LayerVec& dec = mDecalLayer[layer];
    LayerVec& fr = mFreeLayer[layer];
    if (fr.mBegin == fr.mEnd) {
        uint32_t n = (uint32_t)(dec.mEnd - dec.mBegin);
        uint32_t zero = 0;
        uint32_t* p = dec.mEnd;
        if (p < dec.mCapacity) {
            dec.mEnd = p + 1;
            if (p)
                *p = zero;
        } else
            dec.AppendKey4(p, zero);
        return n;
    }
    uint32_t idx = fr.mEnd[-1];
    --fr.mEnd;
    return idx;
}

// @ 0x00fa2850
void cTerrainSphere_s00fa_1bc0::FreeDecalIndex(uint32_t packed)
{
    uint32_t layer = (uint32_t)((int32_t)packed >> 24);
    uint32_t idx = packed & 0xffffff;
    mDecalLayer[layer].mBegin[idx] = 0;
    LayerVec& fr = mFreeLayer[layer];
    uint32_t* p = fr.mEnd;
    uint32_t v = idx;
    if (p < fr.mCapacity) {
        fr.mEnd = p + 1;
        if (p)
            *p = v;
    } else
        fr.AppendValueI(p, v);
}

// @ 0x00fa28b0
cTerrainSphereDecal_s00fa_1bc0* cTerrainSphere_s00fa_1bc0::NewDecal(uint32_t a, const cSPTransform_s00fa_1bc0* xform, float f)
{
    uint32_t idx = AllocDecalIndex(0);
    cTerrainSphereDecal_s00fa_1bc0* p = (cTerrainSphereDecal_s00fa_1bc0*)FUN_00f473a0(
        300, "Terrain/Sphere/cTerrainSphereDecal", 0, 0, 0, 0);
    cTerrainSphereDecal_s00fa_1bc0* d;
    if (p != 0)
        d = p->InitDecal();
    else
        d = 0;
    ++d->mRef;
    d->SetupDecal(idx, a, this, xform, f, false);
    mDecalLayer[0].mBegin[idx] = (uint32_t)d;
    return d;
}

// @ 0x00fa2920
cTerrainSphereDecal_s00fa_1bc0* cTerrainSphere_s00fa_1bc0::NewDecalLayer(uint32_t a, const cSPTransform_s00fa_1bc0* xform, float f, uint32_t layer)
{
    uint32_t idx = AllocDecalIndex(layer);
    uint32_t packed = (layer << 24) | idx;
    cTerrainSphereDecal_s00fa_1bc0* p = (cTerrainSphereDecal_s00fa_1bc0*)FUN_00f473a0(
        300, "Terrain/Sphere/cTerrainSphereDecal", 0, 0, 0, 0);
    cTerrainSphereDecal_s00fa_1bc0* d;
    if (p != 0)
        d = p->InitDecal();
    else
        d = 0;
    ++d->mRef;
    d->SetupDecal(packed, a, this, xform, f, true);
    mDecalLayer[layer].mBegin[idx] = (uint32_t)d;
    return d;
}

// @ 0x00fa29b0
void cTerrainSphere_s00fa_1bc0::ReleaseDecal(uint32_t packed)
{
    uint32_t layer = packed >> 24;
    uint32_t idx = packed & 0xffffff;
    LayerVec& dec = mDecalLayer[layer];
    if (idx < (uint32_t)(dec.mEnd - dec.mBegin)) {
        cTerrainSphereDecal_s00fa_1bc0* d = (cTerrainSphereDecal_s00fa_1bc0*)dec.mBegin[idx];
        if (d) {
            d->Unlink();
            int ref = d->mRef - 1;
            d->mRef = ref;
            if (ref == 0) {
                d->mRef = 1;
                d->Destroy(1);
            }
            FreeDecalIndex(packed);
        }
    }
}

// @ 0x00fa3860
void cTerrainSphere_s00fa_3860::DrawLayerRTT(void* viewer, void* a3)
{
    cDirectPropertyList_s00fa_3860* props = gAppProperties;
    bool b = props->GetDescription(0x1cb22fe0);
    if (b) {
        void* raster = *g_ppRaster16c9f58;
        g_rasterStageDirty |= 0x200;
        g_rasterCur16f9674 = 0;
        unsigned bit = 1;
        for (void** p = g_rasterTable16f9650; p < g_rasterTable16f9650 + 17; p++) {
            if (*p == raster) {
                g_rasterStageDirty |= bit;
                *p = 0;
            }
            bit = (bit << 1) | (bit >> 31);
        }
        SphereData* d = (SphereData*)((TerrainVt*)this)->v10();
        const float* c = d->mColor;
        float r = c[0];
        float g = c[1];
        float bch = c[2];
        cSPColorRGBA_s00fa_3860 col;
        col.r = r;
        col.g = g;
        col.b = bch;
        col.a = 0.0f;
        g_viewer16c9f60.SetClearColor(col);
        for (int i = 0; i < 6; i++) {
            ((RasterView*)raster)->mLayerIndex = (char)i;
            g_viewer16c9f60.SetTarget(raster);
            g_viewer16c9f60.Clear(1);
        }
        g_rasterCur16f9674 = *(int*)g_ppRaster16c9f58;
        g_rasterStageDirty |= 0x200;
        g_16f9554 |= 0x73;
        g_16fa1c4 = 3;
        g_16fa1c8 = 3;
        g_16fa1d8 = 2;
        g_16fa1d4 = 2;
        g_16fa1dc = 2;
    }
    if (viewer == 0) {
        IApp* app = App();
        void* m = app->v50();
        viewer = ((ModeVt*)m)->v1c();
    }
    g_viewer16ca0d8.Copy((cViewer_s00fa_3860*)viewer, false, false);
    g_viewer16ca0d8.SetRaster(&g_15b1200, true);
    SphereData* d2 = (SphereData*)((TerrainVt*)this)->v10();
    const float* c2 = d2->mColor;
    float r2 = c2[0];
    float g2 = c2[1];
    float b2 = c2[2];
    cSPColorRGBA_s00fa_3860 col2;
    col2.r = r2;
    col2.g = g2;
    col2.b = b2;
    col2.a = 0.0f;
    g_viewer16ca0d8.SetClearColor(col2);
    g_viewer16ca0d8.Clear(7);
    b = props->GetDescription(0x2be0cf8e);
    if (b)
        DrawAtmoQuads(&g_viewer16ca0d8, a3);
    b = props->GetDescription(0xe13ce337);
    if (b) {
        if (mpFaceQuads == 0)
            FUN_00f9e3a0();
        g_16fa3a0 |= 2;
        void* local = &g_viewer16ca0d8;
        g_16f9480 = 7;
        D3D9Sync();
        void* q = ((FaceQuadVt*)mpFaceQuads)->vA0();
        ((FaceDrawVt*)q)->v0c(0, 0x12, &local, a3);
        g_16fa3a0 |= 2;
        g_16f9480 = 0xf;
    } else {
        if (mpFaceQuads != 0)
            FUN_00f998f0();
    }
    b = props->GetDescription(0x3dcdb1d1);
    if (b)
        RefractionMapRender(&g_viewer16ca0d8, a3);
    b = gAppProperties->GetDescription(0x552b4af);
    if (b) {
        void* m = FUN_0067ddb0();
        ((MgrVt*)m)->v60(&g_15b1200, &g_15b1208, &g_15b1210, a3);
    }
}

// @ 0x00fa3b30
void cTerrainSphere_s00fa_3860::FUN_00fa3b30()
{
    int i = 0;
    SphereLightGroup* g = mGroups;
    do {
        unsigned n = (unsigned)((unsigned*)g->end - (unsigned*)g->begin);
        unsigned j = 0;
        if (n != 0) {
            do {
                unsigned* slot = (unsigned*)g->begin + j;
                unsigned elem = *slot;
                if (elem != 0) {
                    unsigned flags = ((SphereGroupEntry*)elem)->mFlags;
                    if ((flags >> 3) & 1)
                        FUN_00fa29b0((i << 0x18) | j);
                }
                j++;
            } while (j < (unsigned)((unsigned*)g->end - (unsigned*)g->begin));
        }
        i++;
        g++;
    } while (i < 4);
}

// @ 0x00fa3ba0
int cTerrainSphere_s00fa_3860::FUN_00fa3ba0()
{
    if (mCur2cc == mCur2d0) {
        SPVector<unsigned>& v = mVec2b8;
        unsigned* p = v.end;
        int idx = (int)(v.end - v.begin);
        unsigned local = 0;
        if (p < v.cap) {
            v.end = p + 1;
            if (p)
                *p = 0;
            return idx;
        }
        v.DoInsertKey4(p, local);
        return idx;
    }
    int val = mCur2d0[-1];
    mCur2d0--;
    return val;
}

// @ 0x00fa3c10
void cTerrainSphere_s00fa_3860::ApplyModelFootprint(const Transform* modelXform, cPropertyList* props, void* a3, float* faceBoxes, bool bDecal)
{
    ResKey key = { 0, 0, 0 };
    bool bFootprintDone = false;
    bool bSpecial = (App()->GetCurrentMode() == (void*)&gSpecialMode);

    Vector3 fp = { 10.0f, 0.0f, 0.1f };
    if (!bSpecial && GetPropertyAsVector3(props, 0x3b28c1d, &fp)) {
        float width = fp.x;
        float angle = fp.y * kPi * 2.0f;
        float z = fp.z;
        Transform xform(*modelXform);
        bool flag = bSpecial;
        if (props) {
            Property* p;
            if (props->GetProperty(0x589e78c, p) && p->mnType == 1)
                flag = *p->GetBool();
        }
        Vector2 off = { 0.0f, 0.0f };
        GetPropertyAsVector2(props, 0x3b28c1e, &off);
        xform.RotateY(angle);
        xform.ScaleBy(width);
        cImgRes img;
        img.mpImage = 0;
        cImage* image = 0;
        if (GetPropertyAsKey(props, 0x442151e, &key)) {
            void* res = GetResourceManager()->GetResource(key, 2);
            img.GetImageResource(res);
            image = img.mpImage;
        }
        DrawFootprint(&xform, z, image, &off, flag, faceBoxes, a3);
        bFootprintDone = true;
        if (image) ReleaseRef(image);
    }

    Vector3 fp2 = { 10.0f, 0.0f, 0.1f };
    if (!bSpecial && GetPropertyAsKey(props, 0x3b28c1b, &key)) {
        GetPropertyAsVector3(props, 0x3b28c1c, &fp2);
        void* res = GetResourceManager()->GetResource(key, 2);
        if (res) {
            AddRef(res);
            float angle = fp2.y * kPi * 2.0f;
            float z = fp2.z;
            Transform xform(*modelXform);
            xform.RotateY(angle);
            xform.ScaleBy(fp2.x);
            DrawResource(&xform, z, res, a3);
            ReleaseRef(res);
        }
    }

    if (bDecal && GetPropertyAsKey(props, 0x3abc381, &key)) {
        Vector3 dv = { 10.0f, 0.0f, 1.0f };
        GetPropertyAsVector3(props, 0x3abc382, &dv);
        void* res = GetResourceManager()->GetResource(key, 2);
        if (res) {
            Transform xform(*modelXform);
            xform.ScaleBy(dv.x);   // scale first, as in the original
            float angle = dv.y * kPi * 2.0f;
            xform.RotateY(angle);
            cTerrainSphereDecal* decal = CreateDecal(res, &xform, 0.0f, 0);

            if (faceBoxes && !bFootprintDone) {
                for (int face = 0; face < 6; face++) {
                    float box[4];
                    if (decal->GetBBoxForFace(face, box)) {
                        faceBoxes[face * 4 + 0] = box[0];
                        faceBoxes[face * 4 + 1] = box[1];
                        faceBoxes[face * 4 + 2] = box[2];
                        faceBoxes[face * 4 + 3] = box[3];
                    }
                    else {
                        faceBoxes[face * 4 + 0] = 0.0f;
                        faceBoxes[face * 4 + 1] = 0.0f;
                        faceBoxes[face * 4 + 2] = 0.0f;
                        faceBoxes[face * 4 + 3] = 0.0f;
                    }
                }
            }

            float col[3] = { 1.0f, 1.0f, 1.0f };
            if (GetPropertyAsColorRGB(props, 0x3abc383, col)) {
                decal->r = col[0];
                decal->g = col[1];
                decal->b = col[2];
            }
            if (props) {
                Property* p;
                if (props->GetProperty(0x3abc384, p) && p->mnType == 0xd)
                    decal->a = *p->GetFloat();
                if (props->GetProperty(0x3abc385, p) && p->mnType == 1 && *p->GetBool() && mpLight) {
                    float t = 1.0f;
                    GetFloatProperty(props, 0x3abc386, &t);
                    LightInfo* li = mpLight;
                    decal->r = ((li->color[0] - kLerpBase[0]) * t + kLerpBase[0]) * decal->r;
                    decal->g = decal->g * ((li->color[1] - kLerpBase[1]) * t + kLerpBase[1]);
                    decal->b = decal->b * ((li->color[2] - kLerpBase[2]) * t + kLerpBase[2]);
                }
            }
        }
    }
}

// @ 0x00fa42e0
void cTerrainSphere_s00fa_3860::FUN_00fa42e0(void* key)
{
    int n = (int)(mVec8b0.end - mVec8b0.begin);
    if (n <= 0)
        return;
    Entry8* base = mVec8b0.begin;
    int idx = 0;
    Entry8* p = base;
    while (p->obj != key) {
        idx++;
        p++;
        if (idx >= n)
            return;
    }
    p = base + idx;
    if (p + 1 < mVec8b0.end)
        FUN_00f9ae80(p + 1, mVec8b0.end, p);
    mVec8b0.end = mVec8b0.end - 1;
    void* o = mVec8b0.end->obj;
    if (o)
        ((ReleasedObj*)o)->v04();
}

// @ 0x00fa4360
void cTerrainSphere_s00fa_3860::FUN_00fa4360(void* key)
{
    int n = (int)(mVec8c4.end - mVec8c4.begin);
    if (n <= 0)
        return;
    Entry8* base = mVec8c4.begin;
    int idx = 0;
    Entry8* p = base;
    while (p->obj != key) {
        idx++;
        p++;
        if (idx >= n)
            return;
    }
    p = base + idx;
    if (p + 1 < mVec8c4.end)
        FUN_00f9ae80(p + 1, mVec8c4.end, p);
    mVec8c4.end = mVec8c4.end - 1;
    void* o = mVec8c4.end->obj;
    if (o)
        ((ReleasedObj*)o)->v04();
}

// @ 0x00fa43e0
void cTerrainSphere_s00fa_3860::Relevel(void* a2, char flag)
{
    PropertyMgr* pm = (PropertyMgr*)PropertyManager_s00fa_3860();
    int count = (int)((mRecEnd - mRecBase) / 0xac);
    void* cur = 0;
    if (count <= 0)
        return;
    int off = 0;
    do {
        TerrainRec* rec = (TerrainRec*)(mRecBase + off);
        if (((rec->mFlags >> 0x1b) & 1) != 0 || flag != 0) {
            if (cur) {
                void* old = cur;
                cur = 0;
                ((ReleasedObj*)old)->v04();
            }
            void* out;
            bool ok = pm->v2c(rec->mField98, rec->mFieldA0, &out);
            cur = out;
            if (ok) {
                ApplyModelFootprint((const Transform*)rec, (cPropertyList*)out, a2, rec->mFaceBoxes, false);
                rec->mFlags &= 0xf7ffffff;
                cur = out;
            }
        }
        off += 0xac;
        count--;
    } while (count != 0);
    if (cur)
        ((ReleasedObj*)cur)->v04();
}

// @ 0x00fa44d0
void cTerrainSphere_s00fa_3860::FUN_00fa44d0(int key)
{
    int n = (int)(mVec2e0.end - mVec2e0.begin);
    if (n <= 0)
        return;
    SphereChild** base = (SphereChild**)mVec2e0.begin;
    int idx = 0;
    SphereChild** p = base;
    while ((*p)->mKey != key) {
        idx++;
        p++;
        if (idx >= n)
            return;
    }
    SphereChild* obj = *p;
    unsigned* dst = mVec2e0.begin + idx;
    unsigned* src = dst + 1;
    unsigned* end = mVec2e0.end;
    if (src < end)
        memcpy(dst, src, (char*)end - (char*)src);
    mVec2e0.end = end - 1;
    FUN_00fa29b0(obj->mKey);
    obj->mKey = 0;
    void* r = obj->mField1b8;
    if (r) {
        obj->mField1b8 = 0;
        ReleaseRef_s00fa_3860(r);
    }
    DelMgr* dm = (DelMgr*)FUN_0067dda0();
    dm->v14((void*)obj->mField1b0, (void*)obj->mField1b4);
    obj->FUN_00f9f1a0();
    FreeNamed(obj);
}

// @ 0x00fa45c0
int cTerrainSphere_s00fa_3860::FUN_00fa45c0(Vector3* p2, Vector3* p3, float p4)
{
    cTerrainSphereLight* l = (cTerrainSphereLight*)AllocNamed(0x24, "Terrain/Sphere/cTerrainSphereLight", 0, 0, 0, 0);
    int id = g_lightIdCounter;
    l->mId = id;
    g_lightIdCounter = id + 1;
    l->mVec1 = *p2;
    l->mVec2 = *p3;
    l->mScalar = p4;
    l->mFlag20 = 1;
    SPVector<unsigned>* v = &mVec2f4;
    unsigned* p = v->end;
    unsigned lu = (unsigned)l;
    if (p < v->cap) {
        v->end = p + 1;
        if (p)
            *p = (unsigned)l;
        return l->mId;
    }
    v->DoInsertKey4(p, lu);
    return ((cTerrainSphereLight*)lu)->mId;
}

// @ 0x00fa4660
void cTerrainSphere_s00fa_3860::FUN_00fa4660(int key)
{
    int n = (int)(mVec2f4.end - mVec2f4.begin);
    if (n <= 0)
        return;
    unsigned* base = mVec2f4.begin;
    int idx = 0;
    unsigned* p = base;
    cTerrainSphereLight* light;
    while ((light = (cTerrainSphereLight*)*p)->mId != key) {
        idx++;
        p++;
        if (idx >= n)
            return;
    }
    int cnt = (int)(mVec2e0.end - mVec2e0.begin);
    for (int i = 0; i < cnt; i++)
        ((SphereChild*)(void*)mVec2e0.begin[i])->FUN_00fa23d0(light);
    unsigned* dst = mVec2f4.begin + idx;
    unsigned* src = dst + 1;
    unsigned* end = mVec2f4.end;
    if (src < end)
        memcpy(dst, src, (char*)end - (char*)src);
    mVec2f4.end = end - 1;
    FreeNamed(light);
}

// @ 0x00fa4730
void VecRec20::resize(unsigned n)
{
    Rec20_s00fa_3860* e = end;
    unsigned count = (unsigned)(e - begin);
    if (n > count) {
        Rec20_s00fa_3860 local;
        FUN_00fa1840(e, n - count, &local);
        return;
    }
    Rec20_s00fa_3860* dst = begin + n;
    copy_Rec20(e, e, dst);
    end -= (e - dst);
}

// @ 0x00fa47b0
void RelevelVector_s00fa_47b0::DoInsertValue(cRelevel_s00fa_47b0* position, const cRelevel_s00fa_47b0& value)
{
  if (mpEnd != mpCapacity) {
    const cRelevel_s00fa_47b0* pValue = &value;
    if ((pValue >= position) && (pValue < mpEnd)) ++pValue;
    ::new ((void*)mpEnd) cRelevel_s00fa_47b0(*(mpEnd - 1));
    RelevelCopyBackward(position, mpEnd - 1, mpEnd);
    *position = *pValue;
    ++mpEnd;
  } else {
    const size_type nPosSize = size_type(position - mpBegin);
    const size_type nPrevSize = size_type(mpEnd - mpBegin);
    const size_type nNewSize = nPrevSize ? (2 * nPrevSize) : 1;
    cRelevel_s00fa_47b0* const pNewData = DoAllocate(nNewSize);
    cRelevel_s00fa_47b0* pNewEnd = RelevelUninitCopy(mpBegin, position, pNewData);
    ::new (pNewEnd) cRelevel_s00fa_47b0(value);
    pNewEnd = RelevelUninitCopy(position, mpEnd, ++pNewEnd);
    DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
    mpBegin = pNewData;
    mpEnd = pNewEnd;
    mpCapacity = pNewData + nNewSize;
  }
}

// @ 0x00fa48d0
void cTerrainSphere_s00fa_47b0::Shutdown()
{
  if (PTR(0x8e4)) {
    ((TC0)FUN_007c3ba0)(PTR(0x8e4));
    if (PTR(0x8e4)) {
      void* v = PTR(0x8e4);
      ((TC0)FUN_007c4000)(v);
      EADeallocate(v);
    }
    PTR(0x8e4) = 0;
  }
  if (PTR(0x81c)) {
    ((TC1i)FUN_00692400)(PTR(0x81c), 1);
    if (PTR(0x81c)) {
      void* v = PTR(0x81c);
      PTR(0x81c) = 0;
      ((TC0i)FUN_00690120)(v);
    }
    BYTEV(0x370) = 0;
  }
  if (PTR(0x8a0)) {
    void* p = PTR(0x8a0);
    if (p) { PTR(0x8a0) = 0; VT0(p, 1); }
    if (PTR(0x8a4) != (void*)-1) {
      void* s = FUN_0067dd50();
      ((TC1u)(*(void***)s)[31])(s, (uint32_t)(uintptr_t)PTR(0x8a4));
    }
    PTR(0x8a4) = (void*)-1;
  }
  if (PTR(0x89c) != (void*)-1) {
    void* s = FUN_0067dda0();
    ((TC2u)(*(void***)s)[5])(s, (uint32_t)(uintptr_t)PTR(0x898), (uint32_t)(uintptr_t)PTR(0x89c));
  }
  PTR(0x89c) = (void*)-1;
  PTR(0x898) = (void*)-1;
  if (PTR(0x894)) {
    ((TC1i)FUN_00692400)(PTR(0x894), 1);
    if (PTR(0x894)) {
      void* v = PTR(0x894);
      PTR(0x894) = 0;
      ((TC0i)FUN_00690120)(v);
    }
  }
  {
    void* eff = FUN_0067ddd0();
    int r = ((TC1i)(*(void***)eff)[9])(eff, -1);
    if (r == (int)(uintptr_t)PTR(0x924)) VT0(this, 41);
  }
  VT0(PTR(0x924), 1);
  VT0(PTR(0x924), 3);
  PTR(0x924) = 0;
  {
    void* te = FUN_00f48a70();
    if (((TC0p)FUN_00f67d90)(te) == this) {
      void* te2 = FUN_00f48a70();
      ((TC1i)FUN_00f67a60)(te2, 0);
    }
  }
  if (FUN_00f48aa0() == this) FUN_00f48af0(0);
  VT0(this, 43);
  if (PTR(0x210)) {
    ((TC0)FUN_00fc7950)(PTR(0x210));
    if (PTR(0x210)) {
      void* p = PTR(0x210);
      PTR(0x210) = 0;
      VT0((char*)p + 8, 3);
    }
  }
  if (PTR(0x2c)) {
    ((TC0)FUN_00f92b90)(PTR(0x2c));
    if (PTR(0x2c)) {
      void* p = PTR(0x2c);
      PTR(0x2c) = 0;
      int* rc = (int*)((char*)p + 4);
      if (--*rc == 0) { *rc = 1; VT1i(p, 0, 1); }
    }
  }
  {
    void** a = (void**)((char*)this + 0x118);
    void** b = (void**)((char*)this + 0x130);
    void** c = (void**)((char*)this + 0x148);
    void** d = (void**)((char*)this + 0x160);
    void** e = (void**)((char*)this + 0x178);
    for (int i = 0; i < 6; ++i) {
      if (a[i]) {
        ((TC0)FUN_00fb3e20)(a[i]);
        if (a[i]) { ((TC0)FUN_00fb4340)(a[i]); EADeallocate(a[i]); }
        a[i] = 0;
      }
      if (b[i]) {
        ((TC0)FUN_00fb3e20)(b[i]);
        if (b[i]) { ((TC0)FUN_00fb4340)(b[i]); EADeallocate(b[i]); }
        b[i] = 0;
      }
      if (c[i]) { void* p = c[i]; c[i] = 0; ATOMREL8(p); }
      if (d[i]) { void* p = d[i]; d[i] = 0; ATOMREL8(p); }
      if (e[i]) { void* p = e[i]; e[i] = 0; ATOMREL8(p); }
    }
  }
  if (PTR(0x20c)) {
    ((TC0)FUN_00fbe4f0)(PTR(0x20c));
    if (PTR(0x20c)) { void* p = PTR(0x20c); ((TC0)FUN_00fbd650)(p); EADeallocate(p); }
    PTR(0x20c) = 0;
  }
  for (int f = 0; f < 4; ++f) {
    char* lst = (char*)this + 0x218 + f * 0x14;
    void** lb = *(void***)lst;
    int n = (int)((*(char**)(lst + 4) - (char*)lb) >> 2);
    for (int j = 0; j < n; ++j) {
      void* p = lb[j];
      if (!p) continue;
      ((TC0)FUN_00fadac0)(p);
      int* rc = (int*)((char*)p + 4);
      if (--*rc == 0) { *rc = 1; VT1i(p, 0, 1); }
      lb[j] = 0;
    }
    FUN_011e0744(lb, *(void**)(lst + 4), 0);
    *(char**)(lst + 4) = (char*)*(char**)(lst + 4) - n * 4;
    char* fl = (char*)this + 0x268 + f * 0x14;
    void* fb = *(void**)fl;
    void* fe = *(void**)(fl + 4);
    FUN_011e0744(fb, fe, 0);
    *(char**)(fl + 4) = (char*)fe - ((char*)fe - (char*)fb);
  }
  {
    void* ms = FUN_0067dcc0();
    VT3(ms, 11, (char*)this + 8, 0x87d5f9bf, 0xffffd8f1);
    VT3(ms, 11, (char*)this + 8, 0x03d5bf9a, 0xffffd8f1);
    VT3(ms, 11, (char*)this + 8, 0x044edd9a, 0xffffd8f1);
    VT3(ms, 11, (char*)this + 8, 0x044edd9c, 0xffffd8f1);
  }
  {
    void* begin = PTR(0x8b0);
    void* end = PTR(0x8b4);
    void* r = FUN_00f9ae80_s00fa_47b0(end, end, begin);
    for (char* p = (char*)r; p < (char*)PTR(0x8b4); p += 8) {
      void* q = *(void**)p;
      if (q) VT0(q, 1);
    }
    long len = (char*)end - (char*)begin;
    PTR(0x8b4) = (char*)end - (len >> 3) * 8;
  }
  {
    void* begin = PTR(0x8c4);
    void* end = PTR(0x8c8);
    void* r = FUN_00f9ae80_s00fa_47b0(end, end, begin);
    for (char* p = (char*)r; p < (char*)PTR(0x8c8); p += 8) {
      void* q = *(void**)p;
      if (q) VT0(q, 1);
    }
    long len = (char*)end - (char*)begin;
    PTR(0x8c8) = (char*)end - (len >> 3) * 8;
  }
  if (PTR(0x308)) { void* p = PTR(0x308); PTR(0x308) = 0; ATOMREL8(p); }
  while (PTR(0x2f4) != PTR(0x2f8)) {
    ((TC1p)FUN_00fa4660)(this, **(void***)PTR(0x2f4));
  }
  while (PTR(0x2e0) != PTR(0x2e4)) {
    ((TC1p)FUN_00fa44d0)(this, **(void***)PTR(0x2e0));
  }
  ((TC1p)(*(void***)this)[36])(this, FUN_0067dd50());
  FUN_00f672b0(PTR(0x928));
  PTR(0x928) = 0;
  ((TC0)FUN_00faeec0)(PTR(0xa4c));
  if (PTR(0xa4c)) { void* q = PTR(0xa4c); ((TC0)FUN_00c2e4e0)(q); EADeallocate(q); }
  PTR(0xa4c) = 0;
}

// @ 0x00fa4e90
void cTerrainSphere_s00fa_47b0::UpdateDecalNode(void* node)
{
  char* e = (char*)node;
  if (*(int*)(e + 0x68) == 4) {
    int handle = *(int*)(e + 0x6c);
    if (handle == -1) {
      Vector3 v;
      v.x = *(float*)(e + 4);
      v.y = *(float*)(e + 8);
      v.z = *(float*)(e + 0xc);
      int h = ((TC3f)FUN_00fa45c0)(this, &v, e + 0x38, *(float*)(e + 0x10));
      *(int*)(e + 0x6c) = h;
      *(uint16_t*)(e + 0x70) = *(uint16_t*)(e + 2);
      return;
    }
    if (*(uint16_t*)(e + 0x70) != *(uint16_t*)(e + 2)) {
      Vector3 v;
      v.x = *(float*)(e + 4);
      v.y = *(float*)(e + 8);
      v.z = *(float*)(e + 0xc);
      ((TC2ip)FUN_00f9a680)(this, handle, &v);
      ((void(__thiscall*)(void*, int, float))FUN_00f9a760)(this, handle, *(float*)(e + 0x10));
    }
    ((TC2ip)FUN_00f9a6f0)(this, handle, e + 0x38);
    *(uint16_t*)(e + 0x70) = *(uint16_t*)(e + 2);
    return;
  }
  if (*(int*)(e + 0x68) == 5) return;
  char* b = e - 8;
  if (*(int*)(b + 0x7c) == 0) return;
  if (*(int*)(b + 0x70) == 9) {
    void* q = *(void**)(b + 0x128);
    if ((*(unsigned char*)((char*)q + 4) & 1) == 0) return;
  }
  if ((*(uint32_t*)(b + 0xb8) >> 3) & 1) return;
  ((TC0)FUN_00fae800)(b);
  if ((*(uint32_t*)(b + 0xb8) >> 4) & 1) return;
  ((TC0)FUN_00facfc0)(b);
}

// @ 0x00fa4fc0
void cTerrainSphere_s00fa_47b0::DestroyDecalNode(void* node)
{
  char* n = (char*)node;
  int type = *(int*)(n + 0x68);
  if (type == 4) {
    ((TC1p)FUN_00fa4660)(this, *(void**)(n + 0x6c));
    EADeallocate(n);
    return;
  }
  if (type == 5) {
    ((TC1p)FUN_00fa44d0)(this, *(void**)(n + 0x6c));
    EADeallocate(n);
    return;
  }
  char* b = n - 8;
  int rc = *(int*)(b + 4);
  rc += -1;
  *(int*)(b + 4) = rc;
  if (rc == 0) {
    *(int*)(b + 4) = 1;
    void** vt = *(void***)b;
    ((TC1i)vt[0])(b, 1);
  }
  if (*(int*)(b + 0x7c) != 0) {
    ((TC1u)FUN_00fa29b0)(this, *(uint32_t*)(b + 0x74));
  }
}

// @ 0x00fa5040
bool cTerrainSphere_s00fa_47b0::RemoveRelevel(uint32_t key, unsigned char removeDecals)
{
  cRelevel_s00fa_47b0* rb = (cRelevel_s00fa_47b0*)PTR(0x784);
  int count = (int)((cRelevel_s00fa_47b0*)PTR(0x788) - rb);
  int idx = -1;
  if (count != 0) {
    unsigned i = 0;
    cRelevel_s00fa_47b0* p = rb;
    do {
      if (*(uint32_t*)((char*)p + 0xa8) == key) { idx = (int)i; break; }
      p = (cRelevel_s00fa_47b0*)((char*)p + 0xac);
      ++i;
    } while (i < (unsigned)count);
  }
  if (idx != -1) {
    if (removeDecals) {
      for (int f = 0; f < 4; ++f) {
        void** lb = *(void***)((char*)this + 0x218 + f * 0x14);
        int n = (int)((*(char**)((char*)this + 0x218 + f * 0x14 + 4) - (char*)lb) >> 2);
        for (int j = n - 1; j >= 0; --j) {
          void* d = lb[j];
          if (!d) continue;
          if (((*(uint32_t*)((char*)d + 0xb8) >> 3) & 1) == 0) continue;
          for (int face = 0; face < 6; ++face) {
            float box[4];
            if (!((TC2ip)FUN_00fad140)(d, face, box)) continue;
            float* r = (float*)((char*)this + 0x784 + idx * 0xac + face * 0x10 + 0x38);
            if (box[2] > r[0] && r[2] > box[0] && box[3] > r[1] && r[3] > box[1]) {
              ((TC1u)FUN_00fa29b0)(this, (uint32_t)((f << 24) | j));
              break;
            }
          }
        }
      }
    }
    cRelevel_s00fa_47b0* bend = (cRelevel_s00fa_47b0*)PTR(0x788);
    cRelevel_s00fa_47b0* pc = (cRelevel_s00fa_47b0*)((char*)rb + idx * 0xac);
    cRelevel_s00fa_47b0* pn = (cRelevel_s00fa_47b0*)((char*)pc + 0xac);
    if (pn < bend) {
      while (pn != bend) {
        FUN_00f9f620((char*)pn - 0xac, pn);
        pn = (cRelevel_s00fa_47b0*)((char*)pn + 0xac);
      }
    }
    INTV(0x788) -= 0xac;
    return true;
  }
  cRelevel_s00fa_47b0* wb = (cRelevel_s00fa_47b0*)PTR(0x770);
  int wcount = (int)((cRelevel_s00fa_47b0*)PTR(0x774) - wb);
  int widx = -1;
  if (wcount != 0) {
    unsigned i = 0;
    cRelevel_s00fa_47b0* p = wb;
    do {
      if (*(uint32_t*)((char*)p + 0xa8) == key) { widx = (int)i; break; }
      p = (cRelevel_s00fa_47b0*)((char*)p + 0xac);
      ++i;
    } while (i < (unsigned)wcount);
  }
  if (widx == -1) return false;
  if (removeDecals) {
    for (int f = 0; f < 4; ++f) {
      void** lb = *(void***)((char*)this + 0x218 + f * 0x14);
      int n = (int)((*(char**)((char*)this + 0x218 + f * 0x14 + 4) - (char*)lb) >> 2);
      for (int j = n - 1; j >= 0; --j) {
        void* d = lb[j];
        if (!d) continue;
        if (((*(uint32_t*)((char*)d + 0xb8) >> 3) & 1) == 0) continue;
        for (int face = 0; face < 6; ++face) {
          float box[4];
          if (!((TC2ip)FUN_00fad140)(d, face, box)) continue;
          float* r = (float*)((char*)this + 0x770 + widx * 0xac + face * 0x10 + 0x38);
          if (box[2] > r[0] && r[2] > box[0] && box[3] > r[1] && r[3] > box[1]) {
            uint32_t packed = (uint32_t)((f << 24) | j);
            int ff = (int)(packed >> 24);
            uint32_t jj = packed & 0xffffff;
            void** dl = *(void***)((char*)this + 0x218 + ff * 0x14);
            int dn = (int)((*(char**)((char*)this + 0x218 + ff * 0x14 + 4) - (char*)dl) >> 2);
            if (jj < (uint32_t)dn) {
              void* dd = dl[jj];
              if (dd) {
                ((TC0)FUN_00fadac0)(dd);
                int* rc = (int*)((char*)dd + 4);
                if (--*rc == 0) { *rc = 1; ((TC1i)(*(void***)dd)[0])(dd, 1); }
                dl[jj] = 0;
                char* fl = (char*)this + 0x268 + ff * 0x14;
                uint32_t* fe = *(uint32_t**)(fl + 4);
                if (fe < *(uint32_t**)(fl + 8)) {
                  *(uint32_t**)(fl + 4) = fe + 1;
                  if (fe) *fe = jj;
                } else {
                  uint32_t local = jj;
                  ((TC2ppc)FUN_004558a0)(fl, fe, &local);
                }
              }
            }
            break;
          }
        }
      }
    }
  }
  cRelevel_s00fa_47b0* wend = (cRelevel_s00fa_47b0*)PTR(0x774);
  cRelevel_s00fa_47b0* wc = (cRelevel_s00fa_47b0*)((char*)wb + widx * 0xac);
  cRelevel_s00fa_47b0* wn = (cRelevel_s00fa_47b0*)((char*)wc + 0xac);
  if (wn < wend) {
    while (wn != wend) {
      FUN_00f9f620((char*)wn - 0xac, wn);
      wn = (cRelevel_s00fa_47b0*)((char*)wn + 0xac);
    }
  }
  INTV(0x774) -= 0xac;
  return true;
}

// @ 0x00fa5490
void cTerrainSphere_s00fa_47b0::FlushManaged()
{
  if (PTR(0x210) && *(unsigned char*)((char*)PTR(0x210) + 0xac)) {
    ((TC0)FUN_00fc6d10)(PTR(0x210));
  }
  if (!BYTEV(0x76c)) return;
  ReleaseManaged();
  {
    void** v = (void**)((char*)this + 0x800);
    int n = (int)((*(char**)((char*)this + 0x804) - (char*)v[0]) >> 2);
    for (int i = 0; i < n; ++i) {
      void* p = ((void**)v[0])[i];
      if (p) ((TC1i)(*(void***)p)[3])(p, 1);
    }
    ((TC2pp)FUN_00533500)(v, v[0], v[1]);
  }
  {
    void** v = (void**)((char*)this + 0x7d8);
    int n = (int)((*(char**)((char*)this + 0x7dc) - (char*)v[0]) >> 2);
    for (int i = 0; i < n; ++i) {
      void* p = ((void**)v[0])[i];
      if (p) ((TC1i)(*(void***)p)[91])(p, 0);
    }
    void* res = FUN_005f4e10(v[1], v[1], v[0]);
    ((TC2pp)FUN_005f3680)(v, res, v[1]);
    int cnt = (int)(((char*)v[1] - (char*)v[0]) >> 2);
    v[1] = (char*)v[1] - cnt * 4;
  }
  BYTEV(0x76c) = 0;
}

// @ 0x00fa5580
bool cTerrainSphere_s00fa_47b0::EraseRelevel(uint32_t key)
{
  int count = (int)((cRelevel_s00fa_47b0*)PTR(0x79c) - (cRelevel_s00fa_47b0*)PTR(0x798));
  for (int i = 0; i < count; ++i) {
    if (((cRelevel_s00fa_47b0*)PTR(0x798))[i].mExtra == key) {
      cRelevel_s00fa_47b0* cur = (cRelevel_s00fa_47b0*)PTR(0x798) + i;
      if (cur + 1 < (cRelevel_s00fa_47b0*)PTR(0x79c)) CopyRelevels_s00fa_47b0(cur + 1, (cRelevel_s00fa_47b0*)PTR(0x79c), cur);
      INTV(0x79c) -= 0xac;
      return true;
    }
  }
  return false;
}

// @ 0x00fa5610
void cTerrainSphere_s00fa_5610::UpdateQuadsPostCamera(void* camera)
{
    renderQuads.clear();
    faceRootArray.clear();
    atmoRootArray.clear();

    cDirectPropertyList_s00fa_5610* props = sAppProperties;
    flagA = props->GetDescription(0x563886c);
    bool markChildren = props->GetDescription(0x563886d);

    cFrustumCull cull((char*)camera + 0xc0);
    Property_s00fa_5610* prop;
    if (props && props->GetProperty(0x13d7382, &prop) && prop->type == 0xd) {
        float f = *prop->GetFloat();
        cull.SetNear(f);
    }

    for (int i = 0; i < 6; ++i) {
        QItem it = { faceRoots[i], 0 };
        g_QuadStack.push_back(it);
    }

    bool useDistCull = sAppProperties->GetDescription(0x541a775);
    float maxCamDist = sAppProperties->GetFloatProperty(0x62f89dc);
    float cullDist = sAppProperties->GetFloatProperty(0x63fe1bc);
    float facing = sAppProperties->GetFloatProperty(0x541ac31);
    float radiusScale = GetInfo()->radius;

    SPTransform xf;
    viewer->GetTransform(&xf);
    if (maxCamDist < sqrtf(xf.pos.z * xf.pos.z + (xf.pos.y * xf.pos.y + xf.pos.x * xf.pos.x)))
        useDistCull = false;

    while (g_QuadStack.mpBegin != g_QuadStack.mpEnd) {
        QItem item = g_QuadStack.mpEnd[-1];
        --g_QuadStack.mpEnd;
        cQuad* q = item.quad;
        bool test = true;
        if (useDistCull) {
            float vz = q->centre.z * radiusScale - xf.pos.z;
            float vx = q->centre.x * radiusScale - xf.pos.x;
            float vy = q->centre.y * radiusScale - xf.pos.y;
            if ((vx * vx + vz * vz) + vy * vy > cullDist * cullDist) {
                float nx = -vx, nz = -vz, ny = -vy;
                float inv = 1.0f / sqrtf((nx * nx + nz * nz + ny * ny) + 1e-08f);
                float dot = ((nz * inv) * q->centre.z + (ny * inv) * q->centre.y) + (inv * nx) * q->centre.x;
                if (facing > dot)
                    test = false;
            }
        }
        if (!test)
            continue;
        uint32_t fl = cull.FrustumTestSphere(&q->sphereCentre, &q->sphereRadius, item.flags);
        if (fl & 0x40)
            continue;
        float dist;
        if (!QuadDetailTest(q, decalState, &dist)) {
            if (q->children[0] == 0)
                q->Refine();
            if (q->children[0] != 0) {
                cQuad** pc = q->children;
                for (int i = 4; i; --i) {
                    QItem ci = { *pc, fl };
                    g_QuadStack.push_back(ci);
                    ++pc;
                }
            }
            if (q->children[0] != 0)
                continue;
        }
        float lod = q->lodKey;
        uint32_t bits;
        memcpy(&bits, &dist, 4);
        QContainer c = { q, lod, (uint32_t)((int)bits >> 31) ^ (bits | 0x80000000u), 0 };
        renderQuads.push_back(c);
        if (markChildren && q->children[0] != 0) {
            cQuad** pc = q->children;
            for (int i = 4; i; --i) {
                if ((*pc)->children[0] != 0)
                    (*pc)->MarkChild();
                ++pc;
            }
        }
    }
    SortQuads(renderQuads.mpBegin, renderQuads.mpEnd, false);

    for (int i = 0; i < 6; ++i) {
        QContainer a = { faceRoots[i], 1.0f, 0, 0 };
        faceRootArray.push_back(a);
        QContainer b = { atmoRoots[i], 1.0f, 0, 0 };
        atmoRootArray.push_back(b);
    }
}

// 0x00fa5cc0 (byte-exact lifted version: match/slices/s00fa5cc0/s00fa5cc0.cpp)
void cTerrainSphere_s00fa_5610::DrawLayerRTT(void** a1, void* a2, void*)
{
    cDirectPropertyList_s00fa_5610* props = sAppProperties;
    bool bBase = props->GetDescription(0x201a4e50);
    bool bRefl = props->GetDescription(0xf1a9135a);
    bool bSecond = props->GetDescription(0x797fcd8c);

    *g_16f6ee0 &= ~2u;
    if (bBase) {
        if (g_16c9e68 == 0)
            FUN_00f96b40();
        if (!mStaticRTTValid) {
            FUN_00fa3860(*a1, a2);
            *g_16f6ee0 |= 2u;
        }
    } else {
        if (mpFaceQuads)
            FUN_00f998f0();
        if (g_16c9e68 != 0)
            FUN_00f96c60();
    }
    *g_16f6ee0 &= ~8u;
    if (bRefl) {
        if (g_16c9f5c == 0)
            FUN_00f9e280();
        if (!mStaticRTTValid) {
            FUN_00f9c470(*a1, a2);
            *g_16f6ee0 |= 8u;
        }
    } else {
        if (g_16c9f5c != 0)
            FUN_00f9e350();
    }
    if (g_15b14e8 && (bRefl || bBase))
        ((cViewer_s00fa_5610*)*a1)->Clear(6);

    if (bSecond) {
        uint32_t bit = 0x200;
        g_rasterStageDirty |= bit;
        g_rasterCur16f9674 = 0;
        FUN_00f9df20(*a1, *g_ppRaster16c9f58, pad32c_770, a2);
        g_rasterCur16f9674 = (int)*g_ppRaster16c9f58;
        g_rasterStageDirty |= bit;
        g_16f9554 |= 0x73;
        int three = 3;
        g_16fa1c4 = three;
        g_16fa1c8 = three;
        int two = 2;
        g_16fa1d8 = two;
        g_16fa1d4 = two;
        g_16fa1dc = two;
    }
}

// @ 0x00fa5e40
void cTerrainSphere_s00fa_5610::ClearModels()
{
    ModelKeyVec* keys = (ModelKeyVec*)((char*)this + 0x7b0);

    mCount_7ac = 0;
    keys->DoCopy(keys->mpBegin, keys->mpEnd);

    char* xfBegin = (char*)mModelXforms;
    char* xfEnd = (char*)mModelXformsEnd;
    DoXformCopy(xfEnd, xfEnd, xfBegin);
    // clear(): the element count is negated and scaled back, so the end returns to begin.
    int xfCount = (int)(xfEnd - xfBegin) / -0x38;
    mModelXformsEnd = (char*)mModelXformsEnd + xfCount * 0x38;

    PtrRefVec* ptr = (PtrRefVec*)((char*)this + 0x7d8);
    void** ptrBegin = ptr->mpBegin;
    void** ptrEnd = ptr->mpEnd;
    void* copied = DoPtrCopyRefs(ptrEnd, ptrEnd, ptrBegin);
    ptr->DoDestroyValues((void**)copied, ptr->mpEnd);
    int ptrCount = (int)((char*)ptrEnd - (char*)ptrBegin) >> 2;
    ptr->mpEnd = (void**)((char*)ptr->mpEnd - ptrCount * 4);
}

// @ 0x00fa5ee0
void cTerrainSphere_s00fa_5610::RequestModelFootprint(cDirectPropertyList_s00fa_5610* list, PtrRefVec* out)
{
    Vec3f scale = { 10.0f, 0.0f, 0.1f };
    ResKey key = { 0, 0, 0 };

    if (GetPropertyAsVector3(list, 0x3b28c1d, &scale)) {
        if (GetPropertyAsKey(list, 0x442151e, &key)) {
            IResMgr* mgr = GetResourceManager_s00fa_5610();
            ResRef* obj = (ResRef*)mgr->v1c(key, 0);
            if (obj) {
                obj->AddRef();
                ((RefVec*)out)->Add(&obj);
                ((ObjSlot*)&obj)->Release();
            }
        }
    }
    if (GetPropertyAsKey(list, 0x3b28c1b, &key)) {
        IResMgr* mgr = GetResourceManager_s00fa_5610();
        ResRef* obj = (ResRef*)mgr->v1c(key, 0);
        if (obj) {
            obj->AddRef();
            ((RefVec*)out)->push_back(obj);
            obj->Release();
        }
    }
    if (GetPropertyAsKey(list, 0x3abc381, &key)) {
        IResMgr* mgr = GetResourceManager_s00fa_5610();
        ResRef* obj = (ResRef*)mgr->v1c(key, 0);
        if (obj) {
            obj->AddRef();
            ((RefVec*)out)->push_back(obj);
            obj->Release();
        }
    }
}

// @ 0x00fa6130
void cTerrainSphere_s00fa_5610::AddPaintDecalsFromModels(void* param)
{
    PropertyMgr* mgr = PropertyManager_s00fa_5610();
    RefObj* list = 0;
    for (int i = 0; i < mCount_7ac; ++i) {
        if (list) {
            RefObj* old = list;
            list = 0;
            old->Release();
        }
        ResKey* rec = &mModelKeys[i];
        if (mgr->v2c((void*)rec->instance, (void*)rec->group, (void**)&list)) {
            ApplyModelFootprint((char*)mModelXforms + i * 0x38, list, param, 0, true);
        }
    }
    int n = (int)((char*)mRecEnd_770 - (char*)mRecBase_770) / 0xac;
    for (int i = 0; i < n; ++i) {
        if (list) {
            RefObj* old = list;
            list = 0;
            old->Release();
        }
        TerrainRec_s00fa_5610* rec = (TerrainRec_s00fa_5610*)((char*)mRecBase_770 + i * 0xac);
        if (mgr->v2c(rec->mField98, rec->mFieldA0, (void**)&list)) {
            ApplyModelFootprint(rec, list, param, rec->mFaceBoxes, true);
        }
    }
    n = (int)((char*)mRecEnd_784 - (char*)mRecBase_784) / 0xac;
    for (int i = 0; i < n; ++i) {
        if (list) {
            RefObj* old = list;
            list = 0;
            old->Release();
        }
        TerrainRec_s00fa_5610* rec = (TerrainRec_s00fa_5610*)((char*)mRecBase_784 + i * 0xac);
        if (mgr->v2c(rec->mField98, rec->mFieldA0, (void**)&list)) {
            ApplyModelFootprint(rec, list, param, rec->mFaceBoxes, true);
            rec->mFlags &= 0xf7ffffff;
        }
    }
    if (list)
        list->Release();
}

// @ 0x00fa6320
void cTerrainSphere_s00fa_5610::AddEntry8b0(RefObj* obj, void* param)
{
    RefObj* local = 0;
    if (obj) {
        obj->AddRef();
        local = obj;
    }
    Entry8_s00fa_5610 e = { local, param };
    ((Entry8Vec*)&mEntries8b0)->push_back(e);
    if (e.mObj)
        e.mObj->Release();
}

// @ 0x00fa63d0
void cTerrainSphere_s00fa_5610::AddEntry8c4(RefObj* obj, void* param)
{
    RefObj* local = 0;
    if (obj) {
        obj->AddRef();
        local = obj;
    }
    Entry8_s00fa_5610 e = { local, param };
    ((Entry8Vec*)&mEntries8c4)->push_back(e);
    if (e.mObj)
        e.mObj->Release();
}

// @ 0x00fa6480
void* cTerrainSphere_s00fa_6480::AddLightingRegion(void* param)
{
  char* region = (char*)EAAllocate(0x1d8, "Terrain/Sphere/cTerrainSphereLightingRegion", 0, 0, 0, 0);
  region = region ? (char*)((TV0p)FUN_00f9f100)(region) : 0;
  *(uint8_t*)(region + 0x1d4) = 1;
  *(void**)(region + 0x1d0) = this;

  void* mgr = FUN_0067dda0();
  int prev = *(int*)0x15b14ec;
  *(int*)0x15b14ec = prev + 1;
  uint32_t ids[2];
  uint32_t* pr = (uint32_t*)((TVo7)((void**)*(void***)mgr)[4])(mgr, ids, 0x80, 0x80, 0x15, 0, prev, 0);
  uint32_t id0 = pr[0];
  uint32_t id1 = pr[1];
  *(uint32_t*)(region + 0x1b0) = id0;
  *(uint32_t*)(region + 0x1b4) = id1;
  ((TV3n)((void**)*(void***)mgr)[18])(mgr, id0, id1, "TerrainDecalLightingRegion");
  if (*(uint32_t*)(region + 0x1b4) != 0xffffffffu) {
    int imgId = (int)(intptr_t)((TV3ui)((void**)*(void***)mgr)[7])(mgr, id0, id1, 0);
    ((TV1i)FUN_00576650)(region + 0x1b8, imgId);
  }

  char* viewer = region + 4;
  ((TV1u)FUN_007c4dd0)(viewer, 1);
  ((TV1u)FUN_007c3cc0)(viewer, 0);
  char* img = *(char**)(region + 0x1b8);
  if ((img[4] & 1) == 0) {
    void* o = FUN_0067dd60();
    ((TV1)((void**)*(void***)o)[13])(o, img);
  }
  ((TV1i)FUN_007c3cb0)(viewer, *(int*)img);
  Color4 col;
  col.r = 0.0f; col.g = 0.0f; col.b = 0.0f; col.a = *(float*)0x1485720;
  ((TV1)FUN_007c3c20)(viewer, &col);
  int rect[4] = {0, 0, 0x80, 0x80};
  ((TV1)FUN_007c4a60)(viewer, rect);

  char* p = (char*)((TV3pf)FUN_00fa28b0)(this, img, param, 0.0f);
  *(int*)region = *(int*)(p + 0x74);
  *(uint32_t*)(p + 0xb8) |= 2;
  float f = *(float*)(p + 0x114);
  *(int*)(p + 0x70) = 0;
  Matrix3_s00fa_6480 M;
  M.m[0] = *(float*)(p + 0x108); M.m[1] = *(float*)(p + 0x10c); M.m[2] = *(float*)(p + 0x110);
  M.m[3] = *(float*)(p + 0x118); M.m[4] = *(float*)(p + 0x11c); M.m[5] = *(float*)(p + 0x120);
  M.m[6] = *(float*)(p + 0xf8);  M.m[7] = *(float*)(p + 0xfc);  M.m[8] = *(float*)(p + 0x100);
  XForm2* x = (XForm2*)(region + 0x178);
  x->mScale *= f;
  x->mX *= f;
  x->mY *= f;
  x->mZ *= f;
  x->mFlags |= 1;
  ++x->mModCount;
  ((TV1)FUN_006ba870)(x, &M);
  x->mFlags |= 4;
  ++x->mModCount;
  x->mX = *(float*)(p + 0xec);
  x->mY = *(float*)(p + 0xf0);
  x->mZ = *(float*)(p + 0xf4);

  int n = (int)((*(char**)(SELF + 0x2f8) - *(char**)(SELF + 0x2f4)) >> 2);
  for (int i = 0; i < n; ++i) {
    char* node = *(char**)(*(char**)(SELF + 0x2f4) + i * 4);
    if (((TV1c)FUN_00f9abc0)(region, node + 4)) {
      void** e = *(void***)(region + 0x1c0);
      if (e < *(void***)(region + 0x1c4)) {
        *(void***)(region + 0x1c0) = e + 1;
        if (e) *e = node;
      } else {
        void* tmp = node;
        ((TV2)FUN_00b96600)(region + 0x1bc, e, &tmp);
      }
      *(uint8_t*)(region + 0x1d4) = 1;
    }
  }
  void** e2 = *(void***)(SELF + 0x2e4);
  if (e2 < *(void***)(SELF + 0x2e8)) {
    *(void***)(SELF + 0x2e4) = e2 + 1;
    if (e2) *e2 = region;
  } else {
    void* tmp = region;
    ((TV2)FUN_00b96600)(SELF + 0x2e0, e2, &tmp);
  }
  return *(void**)region;
}

// @ 0x00fa6870
void SP::cTerrainSphere::UpdateLightingRegions(SP::cRenderStats * param)
{
  int n = (int)((*(char**)(SELF + 0x2f8) - *(char**)(SELF + 0x2f4)) >> 2);
  for (int i = 0; i < n; ++i) {
    char* node = *(char**)(*(char**)(SELF + 0x2f4) + i * 4);
    if (node[0x20] == 0) continue;
    int m = (int)((*(char**)(SELF + 0x2e4) - *(char**)(SELF + 0x2e0)) >> 2);
    for (int j = 0; j < m; ++j) {
      char* r = *(char**)(*(char**)(SELF + 0x2e0) + j * 4);
      char c = ((TV1c)FUN_00f9abc0)(r, node + 4);
      int rn = (int)((*(char**)(r + 0x1c0) - *(char**)(r + 0x1bc)) >> 2);
      bool found = false;
      for (int k = 0; k < rn; ++k) {
        if (*(void**)(*(char**)(r + 0x1bc) + k * 4) == node) { found = true; break; }
      }
      if (c == 0) {
        if (found) ((TV1)FUN_00fa23d0)(r, node);
      } else if (!found) {
        void** e = *(void***)(r + 0x1c0);
        if (e < *(void***)(r + 0x1c4)) {
          *(void***)(r + 0x1c0) = e + 1;
          if (e) *e = node;
        } else {
          void* tmp = node;
          ((TV2)FUN_00b96600)(r + 0x1bc, e, &tmp);
        }
        *(uint8_t*)(r + 0x1d4) = 1;
      }
    }
    node[0x20] = 0;
  }
  int m2 = (int)((*(char**)(SELF + 0x2e4) - *(char**)(SELF + 0x2e0)) >> 2);
  for (int i = 0; i < m2; ++i) {
    char* r = *(char**)(*(char**)(SELF + 0x2e0) + i * 4);
    if (r[0x1d4]) ((TV2)FUN_00f9a7c0)(this, r, param);
  }
}

// @ 0x00fa6a50
void* cTerrainSphere_s00fa_6480::CreateDecal(int type, void* def, void* xform, float scale)
{
  if (INTV_s00fa_6480(0x2c) == 0) return 0;
  if (type == 4) {
    char* o = (char*)EAAllocate(0x74, "Terrain/Sphere/cLightDecal", 0, 0, 0, 0);
    o = o ? (char*)((TV0p)FUN_00f9f950)(o) : 0;
    *(int*)(o + 0x68) = 4;
    ((TV1p)FUN_00537dc0)(o, xform);
    *(float*)(o + 0x48) = scale;
    *(int*)(o + 0x6c) = -1;
    *(uint16_t*)(o + 0x70) = 0;
    return o;
  }
  if (type == 5) {
    char* o = (char*)EAAllocate(0x74, "Terrain/Sphere/cLightDecal", 0, 0, 0, 0);
    o = o ? (char*)((TV0p)FUN_00f9f950)(o) : 0;
    *(int*)(o + 0x68) = 5;
    ((TV1p)FUN_00537dc0)(o, xform);
    *(float*)(o + 0x48) = scale;
    void* r = AddLightingRegion(xform);
    *(int*)(o + 0x6c) = (int)(intptr_t)r;
    *(uint16_t*)(o + 0x70) = *(uint16_t*)(o + 2);
    return o;
  }
  uint32_t k0 = *(uint32_t*)def;
  uint32_t k1 = *(uint32_t*)((char*)def + 4);
  void* eff = FUN_0067dd60();
  void* res = ((TV3ui)((void**)*(void***)eff)[8])(eff, k0, k1, 0);
  if (res == 0) {
    eff = FUN_0067dd60();
    res = ((TV3ui)((void**)*(void***)eff)[8])(eff, k0, 0x40010000u, 0);
    if (res == 0) return 0;
  }
  bool bl = ((*(uint8_t*)((char*)def + 0xa) & 4) != 0) || (type == 3);
  int16_t sc = *(int16_t*)((char*)def + 0xc);
  int idx = (int)(float)sc;
  if ((float)sc < (float)idx) --idx;
  if (idx < 0) idx = 0; else if (idx >= 4) idx = 3;
  char* out;
  if (bl) out = (char*)((TV4pf)FUN_00fa2920)(this, res, xform, scale, 3 - idx);
  else    out = (char*)((TV3pf)FUN_00fa28b0)(this, res, xform, scale);
  *(int*)(out + 0x70) = type;
  uint8_t b = *(uint8_t*)((char*)def + 0xa);
  if (b & 1) *(uint32_t*)(out + 0xb8) |= 2;
  else       *(uint32_t*)(out + 0xb8) &= 0xfffffffd;
  if (!(b & 2)) *(uint32_t*)(out + 0xb8) |= 4;
  else          *(uint32_t*)(out + 0xb8) &= 0xfffffffb;
  if (type != 3) *(int*)(out + 4) += 1;
  return out + 8;
}

// @ 0x00fa6c60
uint32_t cTerrainSphere_s00fa_6480::AddModelFootprint(const void* xform, void* props_)
{
  if (!props_) return 0;
  char* props = (char*)props_;

  XForm2 lx;
  lx.mFlags = *(const uint16_t*)xform;
  lx.mModCount = *(const uint16_t*)((const char*)xform + 2);
  lx.mX = *(const float*)((const char*)xform + 4);
  lx.mY = *(const float*)((const char*)xform + 8);
  lx.mZ = *(const float*)((const char*)xform + 0xc);
  lx.mScale = *(const float*)((const char*)xform + 0x10);
  ((TV1)FUN_0041cb40)(&lx.mM, (void*)((const char*)xform + 0x14));

  void* prop = 0;
  char c = ((TV2c)((void**)*(void***)props)[9])(props, 0x589e78cu, &prop);
  if (c && *(int16_t*)((char*)prop + 0x12) == 1) {
    bool* b = ((TV0bp)FUN_0041e920)(prop);
    if (*b) {
      float* v = (float*)FUN_00f9ada0(&lx.mM, &prop);
      void* d = ((TV0p)((void**)*(void***)this)[3])(this);
      float f = *(float*)((char*)d + 0x3c) * *(float*)((char*)d + 0x38) + *(float*)((char*)d + 0x34) + *(float*)0x13eb95c;
      float vx = v[0] * f, vy = v[1] * f, vz = v[2] * f;
      lx.mFlags |= 4;
      ++lx.mModCount;
      lx.mX = vx; lx.mY = vy; lx.mZ = vz;
    }
  }

  void* prop2 = 0;
  char c2 = ((TV2c)((void**)*(void***)props)[9])(props, 0xc5ae63edu, &prop2);
  if (c2 && *(int16_t*)((char*)prop2 + 0x12) == 1) {
    bool* b2 = ((TV0bp)FUN_0041e920)(prop2);
    if (*b2) {
      char rel[0xac];
      void* r = ((TV3pi)FUN_00f9b2b0)(rel, (char*)props + 8, &lx, 1);
      ((TV1p)FUN_00fa6a00)(SELF + 0x784, r);
      char* e = *(char**)(SELF + 0x788) - 0xac;
      ((TV5pb)FUN_00fa3c10)(this, &lx, props, 0, e + 0x38, 1);
      *(uint32_t*)(e + 0xa4) &= 0xf7ffffff;
      uint32_t key = *(uint32_t*)(e + 0xa8);
      INTV_s00fa_6480(0x814) += 1;
      INTV_s00fa_6480(0x818) += 1;
      return key;
    }
  }

  char rel2[0xac];
  void* r2 = ((TV3pi)FUN_00f9b2b0)(rel2, (char*)props + 8, &lx, 0);
  char* end = *(char**)(SELF + 0x774);
  if (end < *(char**)(SELF + 0x778)) {
    *(char**)(SELF + 0x774) = end + 0xac;
    if (end) ((TV1p)FUN_00f9b1e0)(end, r2);
  } else {
    ((TV2)FUN_00fa47b0)(SELF + 0x770, end, r2);
  }
  char* e2 = *(char**)(SELF + 0x774) - 0xac;
  ((TV5pb)FUN_00fa3c10)(this, &lx, props, 0, e2 + 0x38, 1);
  uint32_t key2 = *(uint32_t*)(e2 + 0xa8);
  INTV_s00fa_6480(0x814) += 1;
  INTV_s00fa_6480(0x818) += 1;
  return key2;
}

// @ 0x00fa6ec0
void cTerrainSphere_s00fa_6480::ClearRelevels()
{
  char* b0 = *(char**)(SELF + 0x770);
  char* e0 = *(char**)(SELF + 0x774);
  FUN_00f9f770(e0, e0, b0);
  int d0 = (int)(e0 - b0);
  INTV_s00fa_6480(0x774) -= (d0 / 0xac) * 0xac;
  _ReadWriteBarrier();

  char* b1 = *(char**)(SELF + 0x784);
  char* e1 = *(char**)(SELF + 0x788);
  FUN_00f9f770(e1, e1, b1);
  int d1 = (int)(e1 - b1);
  INTV_s00fa_6480(0x788) -= (d1 / 0xac) * 0xac;
  _ReadWriteBarrier();

  INTV_s00fa_6480(0x814) += 1;
}

// @ 0x00fa6f40
void cTerrainSphere_s00fa_6480::ReleaseBackgroundModels()
{
  ReserveOut ro = {0, 0};
  void* mgr = 0;
  char ok = FUN_006a0ae0(PTRV(0x28), 0x3abb0afu, &ro, &mgr);
  if (!ok) return;
  void* eff = FUN_0067ddd0();
  mgr = ((TV1p)((void**)*(void***)eff)[21])(eff, (void*)0x3fbae24);
  ((TV1i)FUN_00a730c0)(SELF + 0x7ec, ro.mCount);
  for (int i = 0, off = 0; i < ro.mCount; ++i, off += 0xc) {
    char** slot = (char**)(*(char**)(SELF + 0x7ec) + i * 4);
    char* e = *slot;
    if (e) {
      *slot = 0;
      ((TV0)((void**)*(void***)e)[1])(e);
    }
    char r = ((TV3c)((void**)*(void***)mgr)[2])(mgr, *(char**)((char*)ro.mData + off), 0, slot);
    if (r) {
      char* e2 = *(char**)(*(char**)(SELF + 0x7ec) + i * 4);
      ((TV1)((void**)*(void***)e2)[2])(e2, 0);
    }
  }
}

// @ 0x00fa7010
void cTerrainSphere_s00fa_6480::AddModelsAndEffects() {
  if (U8V(0x76c)) return;
  ReleaseBackgroundModels();

  ReserveOut ro = {0, 0};
  void* mgr = 0;
  char ok = FUN_006a0ae0(PTRV(0x28), 0x40539d4u, &ro, &mgr);
  if (ok) {
    void* eff = FUN_0067ddd0();
    mgr = ((TV1p)((void**)*(void***)eff)[21])(eff, (void*)0x3fbae24);
    ((TV1i)FUN_00a730c0)(SELF + 0x800, ro.mCount);
    for (int i = 0, off = 0; i < ro.mCount; ++i, off += 0xc) {
      char** slot = (char**)(*(char**)(SELF + 0x800) + i * 4);
      char* e = *slot;
      if (e) {
        *slot = 0;
        ((TV0)((void**)*(void***)e)[1])(e);
      }
      char r = ((TV3c)((void**)*(void***)mgr)[2])(mgr, *(char**)((char*)ro.mData + off), 0, slot);
      if (r) {
        char* e2 = *(char**)(*(char**)(SELF + 0x800) + i * 4);
        ((TV1)((void**)*(void***)e2)[2])(e2, 0);
      }
    }
  }

  if (INTV_s00fa_6480(0x7ac) == 0) {
    U8V(0x76c) = 1;
    return;
  }
  void* mm = FUN_0067dd80();
  mm = ((TV1p)((void**)*(void***)mm)[7])(mm, (void*)0x3fbae24);
  char* vec = SELF + 0x7d8;
  if (*(void**)(vec) == *(void**)(vec + 4)) ((TV1i)FUN_00473270)(vec, INTV_s00fa_6480(0x7ac));
  for (int i = 0; i < INTV_s00fa_6480(0x7ac); ++i) {
    char* model = *(char**)(SELF + 0x7b0) + i * 0xc;
    char** slot = (char**)(*(char**)(SELF + 0x7d8) + i * 4);
    char* nv = (char*)((TV3c)((void**)*(void***)mm)[3])(mm, *(void**)model, 0, *(void**)(model + 8));
    char* old = *slot;
    if (nv != old) {
      if (nv) *(int*)(nv + 0x40) += 1;
      *slot = nv;
      if (old) {
        int rc = *(int*)(old + 0x40);
        if (rc < 2) {
          ((TV1u)((void**)*(void***)old)[92])(old, (uint32_t)(*(uint32_t*)(old + 4) >> 31));
        } else {
          *(int*)(old + 0x40) = rc - 1;
        }
      }
    }
    char* cur = *(char**)(*(char**)(SELF + 0x7d8) + i * 4);
    if (cur) {
      ((TV1p)FUN_00537dc0)(cur + 8, *(char**)(SELF + 0x7c4) + i * 0x38);
      *(uint32_t*)(cur + 4) |= 0x20;
    }
  }
  ((TV0)PinModelsToTerrain_00f99520)(this);
  U8V(0x76c) = 1;
}

// @ 0x00fa7220
uint32_t cTerrainSphere_s00fa_6480::AddPlayerModification(void* a, void* b, void* c)
{
  char* local = 0;
  void* eff = FUN_0067ddd0();
  void* mgr = ((TV1p)((void**)*(void***)eff)[21])(eff, (void*)0x3fbae24);
  if (local) {
    char* p = local;
    local = 0;
    ((TV0)((void**)*(void***)p)[1])(p);
  }
  char ok = ((TV3c)((void**)*(void***)mgr)[2])(mgr, b, (int)(intptr_t)c, &local);
  if (!ok) {
    if (local) { char* p = local; ((TV0)((void**)*(void***)p)[1])(p); }
    return 0;
  }
  ((TV1)((void**)*(void***)local)[6])(local, a);
  ((TV1i)((void**)*(void***)local)[2])(local, 0);

  int n = 0x32;
  void* sp = *(void**)0x15fd918;
  if (sp) {
    void* prop = 0;
    if (((TV2c)((void**)*(void***)sp)[9])(sp, 0x3a8b697u, &prop) &&
        *(int16_t*)((char*)prop + 0x12) == 9) {
      n = *((TV0ip)FUN_0041e990)(prop);
    }
  }

  char* b7 = *(char**)(SELF + 0x798);
  char* e7 = *(char**)(SELF + 0x79c);
  int cnt = (int)(e7 - b7) / 0xac;
  if (cnt == n) {
    if (b7 + 0xac < e7) FUN_00f9f770(b7 + 0xac, e7, b7);
    INTV_s00fa_6480(0x79c) -= 0xac;
  }

  char src[0x38] = {0};
  char rel[0xac];
  void* r = ((TV3pi)FUN_00f9b2b0)(rel, src, a, 0);
  char* end = *(char**)(SELF + 0x79c);
  if (end < *(char**)(SELF + 0x7a0)) {
    *(char**)(SELF + 0x79c) = end + 0xac;
    if (end) ((TV1p)FUN_00f9b1e0)(end, r);
  } else {
    ((TV2)FUN_00fa47b0)(SELF + 0x798, end, r);
  }
  uint32_t key = *(uint32_t*)(*(char**)(SELF + 0x79c) - 4);
  INTV_s00fa_6480(0x814) += 1;
  INTV_s00fa_6480(0x818) += 1;
  if (local) { char* p = local; ((TV0)((void**)*(void***)p)[1])(p); }
  return key;
}

// @ 0x00fa73c0
void cTerrainSphere_s00fa_6480::ClearPlayerModifications() {
  char* b = *(char**)(SELF + 0x798);
  char* e = *(char**)(SELF + 0x79c);
  FUN_00f9f770(e, e, b);
  int d = (int)(e - b);
  INTV_s00fa_6480(0x79c) -= (d / 0xac) * 0xac;
  _ReadWriteBarrier();

  ((TV1u)((void**)*(void***)PTRV(0x28))[6])(PTRV(0x28), 0x536250cu);
  ((TV1u)((void**)*(void***)PTRV(0x28))[6])(PTRV(0x28), 0x536250du);
  ((TV1u)((void**)*(void***)PTRV(0x28))[6])(PTRV(0x28), 0x3a23f9au);

  ((TV1i)SetDirty_00fbaf10)(PTRV(0x20c), 0);
  ((TV1i)SetDirty_00fbaf50)(PTRV(0x20c), 0);
  INTV_s00fa_6480(0x814) += 1;
}

// @ 0x00fa75f0
void Cls::BuildTerrain(const float* rects)
{
    Ctx* x = ctx;
    Img* outImg = x->out;
    if (!outImg) return;
    Img* A = x->A; Img* B = x->B; Img* C = x->C; Img* D = x->D; Img* E = x->E; Img* F = x->F;
    const __m128 zero = _mm_setzero_ps();
    const uint32_t k16 = 0xffff, kone = 0x3f800000;
    const __m128 m16 = _mm_set1_ps(*(const float*)&k16);
    const __m128 one = _mm_set1_ps(1.0f);
    const __m128 four = _mm_set1_ps(4.0f);
    const __m128 half = _mm_set1_ps(0.5f);
    const __m128 two = _mm_set1_ps(2.0f);

    if (!o210 || !Query(4)) {
        // plain path: 2x2 box of the u16 map into C, rescaled and clamped at 0
        const float* r = rects;
        for (int fo = 0; fo < 0x600; fo += 0x100, r += 4) {
            int a = FloorI(r[0] * 256.0f);
            int b = FloorI(r[2] * 256.0f);
            int c = FloorI(r[1] * 256.0f);
            int d = FloorI(r[3] * 256.0f);
            int k0 = a >> 2, k1 = b >> 2;
            char* src = (char*)A->v.b + (fo + c) * 0x800;
            char* dst = (char*)C->v.b + (fo + c) * 0x400;
            if (c < d) {
                for (int n = d - c; n; --n) {
                    if (k0 < k1) {
                        const char* q = src + 0x402 + k0 * 16;
                        float* o = (float*)(dst + k0 * 16);
                        for (int m = k1 - k0; m; --m) {
                            __m128 p0 = _mm_or_ps(_mm_and_ps(_mm_load_ps((const float*)(q - 0x402)), m16), one);
                            __m128 p1 = _mm_or_ps(_mm_and_ps(_mm_loadu_ps((const float*)(q - 0x400)), m16), one);
                            __m128 p3 = _mm_or_ps(_mm_and_ps(_mm_loadu_ps((const float*)q), m16), one);
                            __m128 p2 = _mm_or_ps(_mm_and_ps(_mm_load_ps((const float*)(q - 2)), m16), one);
                            __m128 s = _mm_add_ps(_mm_add_ps(p0, p1), _mm_add_ps(p2, p3));
                            s = _mm_mul_ps(_mm_sub_ps(s, four), _mm_set1_ps(64.0009765625f));
                            _mm_store_ps(o, _mm_max_ps(_mm_sub_ps(s, one), zero));
                            q += 16; o += 4;
                        }
                    }
                    dst += 0x400; src += 0x800;
                }
            }
        }
    } else {
        // detailed path: build 6x256x256 from A, downsample to 64x64 (H64), add lat map, normalise
        for (int fb = 0, ob = 0; fb < 0x300000; fb += 0x80000, ob += 0x40000) {
            const char* src = (const char*)A->v.b + fb + 0x402;
            float* o = (float*)((char*)C->v.b + ob);
            for (int row = 0x100; row; --row) {
                const char* q = src;
                for (int n = 0x40; n; --n) {
                    __m128 p0 = _mm_or_ps(_mm_and_ps(_mm_load_ps((const float*)(q - 0x402)), m16), one);
                    __m128 p1 = _mm_or_ps(_mm_and_ps(_mm_loadu_ps((const float*)(q - 0x400)), m16), one);
                    __m128 p3 = _mm_or_ps(_mm_and_ps(_mm_loadu_ps((const float*)q), m16), one);
                    __m128 p2 = _mm_or_ps(_mm_and_ps(_mm_load_ps((const float*)(q - 2)), m16), one);
                    __m128 s = _mm_add_ps(_mm_add_ps(p0, p1), _mm_add_ps(p2, p3));
                    _mm_store_ps(o, _mm_mul_ps(_mm_sub_ps(s, four), _mm_set1_ps(32.00048828125f)));
                    q += 16; o += 4;
                }
                src += 0x800;
            }
        }

        Img* H = new ("Terrain/Sphere/Height64", 0, 0, 0, 0) Img();
        H->Init(0x40);
        {
            const float* cp = (const float*)((char*)C->v.b + 0x800);
            float* o = H->v.b;
            for (int row = 0x180; row; --row) {
                const float* p = cp;
                for (int n = 0x10; n; --n) {
                    for (int i = 0; i < 4; ++i) {
                        const float* e = p + 4 * i;
                        o[i] = ((((e[-0x200 + 3] + e[-0x100 + 3]) + (e[0x100 + 3] + e[3])) +
                                 ((e[-0x200 + 2] + e[-0x100 + 2]) + (e[0x100 + 2] + e[2]))) +
                                (((e[-0x200 + 1] + e[-0x100 + 1]) + (e[0x100 + 1] + e[1])) +
                                 ((e[-0x200] + e[-0x100]) + (e[0x100] + e[0])))) * 0.0625f;
                    }
                    o += 4; p += 0x10;
                }
                cp += 0x400;
            }
        }

        Img* L = new ("Terrain/Sphere/LatMap", 0, 0, 0, 0) Img();
        L->Init(0x40);
        {
            static const uint8_t axes[3][4] = { {0, 1, 2, 0}, {1, 2, 0, 0}, {2, 0, 1, 0} };
            float* lf = L->v.b;
            float v[4];
            for (int face = 0; face < 6; ++face) {
                const uint8_t* t = axes[face >> 1];
                int odd = face & 1;
                float* col = lf;
                for (unsigned u = 0; u < 0x40; ++u) {
                    float fx = (((float)(int)u + 0.5f) * 0.015625f) * 2.0f - 1.0f;
                    float* o = col;
                    for (unsigned w = 0; w < 0x40; ++w) {
                        float fy = (((float)(int)w + 0.5f) * 0.015625f) * 2.0f - 1.0f;
                        float inv = 1.0f / sqrtf((fy * fy + fx * fx) + 1.0f);
                        float sinv = odd ? -inv : inv;
                        v[t[0]] = sinv * fx;
                        v[t[1]] = inv * fy;
                        v[t[2]] = sinv;
                        float z = v[2] * v[2];
                        if (z < 0.0f) z = 0.0f;
                        else if (z > 1.0f) z = 1.0f;
                        *o = z;
                        o += 0x40;
                    }
                    col += 1;
                }
                lf += 0x1000;
            }
        }

        {
            __m128* h = (__m128*)H->v.b;
            __m128* l = (__m128*)L->v.b;
            __m128 mx = _mm_set1_ps(-3.402823466e+38f);
            __m128 mn = _mm_set1_ps(3.402823466e+38f);
            for (int i = 0; i < 0x180 * 0x10; ++i) {
                __m128 s = _mm_add_ps(l[i], h[i]);
                h[i] = s;
                mx = _mm_max_ps(s, mx);
                mn = _mm_min_ps(s, mn);
            }
            mx = _mm_max_ps(_mm_shuffle_ps(mx, mx, 0xb1), mx);
            mx = _mm_max_ps(_mm_shuffle_ps(mx, mx, 0x1b), mx);
            mn = _mm_min_ps(_mm_shuffle_ps(mn, mn, 0xb1), mn);
            mn = _mm_min_ps(_mm_shuffle_ps(mn, mn, 0x1b), mn);
            __m128 rc = _mm_rcp_ps(_mm_sub_ps(mx, mn));
            for (int i = 0; i < 0x180 * 0x10; ++i)
                h[i] = _mm_mul_ps(_mm_sub_ps(h[i], mn), rc);
        }
        L->Dtor(1);
        {
            __m128* c = (__m128*)C->v.b;
            for (int i = 0; i < 6 * 0x100 * 0x40; ++i)
                c[i] = _mm_max_ps(_mm_mul_ps(_mm_sub_ps(c[i], half), two), zero);
        }
        o210->Use(H);
        H->Dtor(1);
    }

    // B (bytes) -> D: mean of squared normalised samples, scaled by f350
    {
        const float* r = rects;
        for (int fo = 0; fo < 0x600; fo += 0x100, r += 4) {
            int a = FloorI(r[0] * 256.0f);
            int b = FloorI(r[2] * 256.0f);
            int c = FloorI(r[1] * 256.0f);
            int d = FloorI(r[3] * 256.0f);
            char* src = (char*)B->v.b + ((fo + c) << 12);
            char* dst = (char*)D->v.b + ((fo + c) << 10);
            int k0 = a >> 2, k1 = b >> 2;
            const __m128 sc = _mm_set1_ps(f350);
            if (c < d) {
                for (int n = d - c; n; --n) {
                    if (k0 < k1) {
                        const char* q = src + (k0 << 5) + 0x12;
                        float* o = (float*)(dst + (k0 << 4));
                        for (int m = k1 - k0; m; --m) {
                            const uint32_t k8 = 0xff;
                            const __m128 mm = _mm_set1_ps(*(const float*)&k8);
                            const __m128 cc = _mm_set1_ps(65793.0078125f);
                            __m128 s0 = _mm_sub_ps(_mm_or_ps(_mm_and_ps(_mm_loadu_ps((const float*)(q - 0x10)), mm), one), one);
                            s0 = _mm_sub_ps(_mm_mul_ps(s0, cc), one); s0 = _mm_mul_ps(s0, s0);
                            __m128 t0 = _mm_add_ps(_mm_shuffle_ps(s0, s0, 0xb1), s0);
                            __m128 s1 = _mm_sub_ps(_mm_or_ps(_mm_and_ps(_mm_loadu_ps((const float*)q), mm), one), one);
                            s1 = _mm_sub_ps(_mm_mul_ps(s1, cc), one); s1 = _mm_mul_ps(s1, s1);
                            __m128 t1 = _mm_add_ps(_mm_shuffle_ps(s1, s1, 0xb1), s1);
                            __m128 s2 = _mm_sub_ps(_mm_or_ps(_mm_and_ps(_mm_loadu_ps((const float*)(q + 0x7f0)), mm), one), one);
                            s2 = _mm_sub_ps(_mm_mul_ps(s2, cc), one); s2 = _mm_mul_ps(s2, s2);
                            __m128 t2 = _mm_add_ps(_mm_shuffle_ps(s2, s2, 0xb1), s2);
                            __m128 s3 = _mm_sub_ps(_mm_or_ps(_mm_and_ps(_mm_loadu_ps((const float*)(q + 0x800)), mm), one), one);
                            s3 = _mm_sub_ps(_mm_mul_ps(s3, cc), one); s3 = _mm_mul_ps(s3, s3);
                            __m128 t3 = _mm_add_ps(_mm_shuffle_ps(s3, s3, 0xb1), s3);
                            __m128 hi = _mm_shuffle_ps(t2, t3, 0xdd);
                            __m128 lo = _mm_shuffle_ps(t0, t1, 0xdd);
                            __m128 res = _mm_mul_ps(_mm_add_ps(hi, lo), _mm_set1_ps(0.25f));
                            _mm_store_ps(o, _mm_mul_ps(res, sc));
                            q += 0x20; o += 4;
                        }
                    }
                    dst += 0x400; src += 0x1000;
                }
            }
        }
    }

    // E = D * f354 + C * f34c
    {
        const float* r = rects;
        for (int fo = 0; fo < 0x600; fo += 0x100, r += 4) {
            int a = FloorI(r[0] * 256.0f);
            int b = FloorI(r[2] * 256.0f);
            int c = FloorI(r[1] * 256.0f);
            int d = FloorI(r[3] * 256.0f);
            int off = (fo + c) << 10;
            char* eP = (char*)E->v.b + off;
            char* dP = (char*)D->v.b + off;
            char* cP = (char*)C->v.b + off;
            int k0 = a >> 2, k1 = b >> 2;
            const __m128 w0 = _mm_set1_ps(f34c);
            const __m128 w1 = _mm_set1_ps(f354);
            if (c < d) {
                for (int n = d - c; n; --n) {
                    for (int k = k0; k < k1; ++k) {
                        __m128 dv = _mm_load_ps((const float*)(dP + k * 16));
                        __m128 cv = _mm_load_ps((const float*)(cP + k * 16));
                        _mm_store_ps((float*)(eP + k * 16), _mm_add_ps(_mm_mul_ps(dv, w1), _mm_mul_ps(w0, cv)));
                    }
                    eP += 0x400; dP += 0x400; cP += 0x400;
                }
            }
        }
    }

    F->Assign(E);

    // add 256x256 byte detail table to every face of F
    {
        const uint8_t* tbl = o1->o2->tbl;
        float scale = f35c;
        float* p = F->v.b;
        for (int face = 6; face; --face) {
            for (unsigned y = 0; (int)y < 0x100; ++y) {
                for (unsigned xx = 0; (int)xx < 0x100; ++xx) {
                    *p = ((float)tbl[(xx & 0xff) + (y & 0xff) * 0x100] * 0.007843137718737125f - 1.0f) * scale + *p;
                    ++p;
                }
            }
        }
    }

    // 3x3 blur of F into scratch image S, then fix the cube-face edges
    Img S;
    S.Init(0x100);
    {
        const __m128 wr0 = _mm_set1_ps(0.125f), wmid = _mm_set1_ps(0.25f), wr2 = _mm_set1_ps(0.125f);
        const __m128 sr0 = _mm_set1_ps(0.0625f), smid = _mm_set1_ps(0.125f), sr2 = _mm_set1_ps(0.0625f);
        static const float edgeW[4] = { 0.0625f, 0.125f, 0.0625f, 0.125f };
        for (int face = 0, fo = 0; fo < 0x180000; fo += 0x40000, ++face) {
            char* src = (char*)F->v.b + fo;
            char* dst = (char*)S.v.b + fo + 0x400;
            for (int row = 0xfe; row; --row) {
                __m128 prev = zero;
                __m128 r0 = _mm_load_ps((const float*)src);
                __m128 rm = _mm_load_ps((const float*)(src + 0x400));
                __m128 r2 = _mm_load_ps((const float*)(src + 0x800));
                __m128 cur = _mm_add_ps(_mm_add_ps(_mm_mul_ps(rm, smid), _mm_mul_ps(r0, sr0)), _mm_mul_ps(r2, sr2));
                const char* nx = src + 0x410;
                for (int n = 0x40; n; --n) {
                    __m128 c2 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(rm, wmid), _mm_mul_ps(r0, wr0)), _mm_mul_ps(r2, wr2));
                    __m128 nm = _mm_load_ps((const float*)nx);
                    __m128 n0 = _mm_load_ps((const float*)(nx - 0x400));
                    __m128 n2 = _mm_load_ps((const float*)(nx + 0x400));
                    __m128 next = _mm_add_ps(_mm_add_ps(_mm_mul_ps(nm, smid), _mm_mul_ps(n0, sr0)), _mm_mul_ps(n2, sr2));
                    __m128 t = _mm_shuffle_ps(cur, next, 0x0d);
                    __m128 right = _mm_shuffle_ps(cur, t, 0xd9);
                    __m128 left = _mm_shuffle_ps(prev, cur, 0x8f);
                    left = _mm_shuffle_ps(left, cur, 0x98);
                    _mm_store_ps((float*)dst, _mm_add_ps(_mm_add_ps(right, left), c2));
                    r0 = n0; rm = nm; r2 = n2;
                    nx += 16; dst += 16;
                    prev = cur; cur = next;
                }
                src += 0x400;
            }
            for (int i = 0; i < 0x100; ++i) {
                F->CubeEdge(face, i, 0, S.v.b, edgeW, 1.0f);
                F->CubeEdge(face, i, 0xff, S.v.b, edgeW, 1.0f);
                F->CubeEdge(face, 0, i, S.v.b, edgeW, 1.0f);
                F->CubeEdge(face, 0xff, i, S.v.b, edgeW, 1.0f);
            }
        }
    }

    // F.data <- blurred data (via a temporary copy of F's old buffer)
    {
        int n = (int)(F->v.e - F->v.b);
        FVec t;
        void* mem = n ? AllocEA(n * 4, 0x80, 0, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xe5) : 0;
        t.b = (float*)mem;
        t.c = (float*)((char*)mem + n * 4);
        int bytes = (int)((char*)F->v.e - (char*)F->v.b);
        void* endp = memcpy(mem, F->v.b, bytes);
        t.e = (float*)((char*)endp + (bytes >> 2) * 4);
        F->v.Swap(&S.v);
        S.v.Swap(&t);
        if (mem) FreeArray(mem);
    }

    // pack F (6 x 256 x 256 floats) into the 8-bit output image
    {
        const __m128 k0 = _mm_set1_ps(3.039836883544922e-05f);
        const __m128 k1 = _mm_set1_ps(0.007781982421875f);
        const uint32_t u_ff = 0xff, u_ff00 = 0xff00, u_hi = 0xffff0000;
        const __m128 mask_lo = _mm_set1_ps(*(const float*)&u_ff);
        const __m128 mask_mid = _mm_set1_ps(*(const float*)&u_ff00);
        const __m128 mask_hi = _mm_set1_ps(*(const float*)&u_hi);
        float* o = outImg->v.b;
        const char* f = (const char*)F->v.b;
        for (int face = 6; face; --face) {
            for (int row = 0x100; row; --row) {
                const float* p = (const float*)f;
                for (int n = 0x10; n; --n) {
                    __m128 c0 = _mm_min_ps(_mm_max_ps(_mm_load_ps(p), zero), one);
                    __m128 c1 = _mm_min_ps(_mm_max_ps(_mm_load_ps(p + 4), zero), one);
                    __m128 c2 = _mm_min_ps(_mm_max_ps(_mm_load_ps(p + 8), zero), one);
                    __m128 c3 = _mm_min_ps(_mm_max_ps(_mm_load_ps(p + 12), zero), one);
                    __m128 pa = _mm_shuffle_ps(c0, c1, 0x44), pc = _mm_shuffle_ps(c0, c1, 0xee);
                    __m128 pb = _mm_shuffle_ps(c2, c3, 0x44), pd = _mm_shuffle_ps(c2, c3, 0xee);
                    __m128 l0 = _mm_and_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(pa, pb, 0x88), k0), one), mask_lo);
                    __m128 l1 = _mm_and_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(pa, pb, 0xdd), k1), one), mask_mid);
                    __m128 l3 = _mm_and_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(pc, pd, 0xdd), k1), one), mask_mid);
                    __m128 l2 = _mm_and_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(pc, pd, 0x88), k0), one), mask_lo);
                    _mm_store_ps(o, _mm_or_ps(l3, l2));
                    __m128 m = _mm_loadu_ps((const float*)((char*)o - 2));
                    _mm_store_ps(o, _mm_or_ps(_mm_and_ps(m, mask_hi), _mm_or_ps(l1, l0)));
                    p += 16; o += 4;
                }
                f += 0x400;
            }
        }
    }
    outImg->Finish();
    S.Fini();
}

// @ 0x00fa86c0
void cTerrainSphere_s00fa_86c0::CollectFootprintTextures(TextureVec& out)
{
    PropertyManager_s00fa_86c0* pm = SP::PropertyManager_s00fa_86c0();
    int total = (int)(mpRelevelEnd - mpRelevelBegin) + mExtraCount;
    PropRef prop;
    out.clear();
    out.reserve(total * 3);

    for (int i = 0; i < mExtraCount; ++i) {
        prop.reset();
        cFootprintEntry* entry = mpExtra + i;
        if (pm->GetProperty(entry->mKey, entry->mKey2, &prop.mpProperty))
            RequestModelFootprint(prop.mpProperty, out);
    }

    int numRelevel = (int)(mpRelevelEnd - mpRelevelBegin);
    for (int i = 0; i < numRelevel; ++i) {
        prop.reset();
        cRelevelEntry* record = mpRelevelBegin + i;
        if (pm->GetProperty(record->mPropertyKeyA, record->mPropertyKeyB, &prop.mpProperty))
            RequestModelFootprint(prop.mpProperty, out);
    }

    if (prop.mpProperty)
        prop.mpProperty->Release();
}

// @ 0x00fa9040
bool GetPropertyTransforms(cProperty_s00fa_86c0* property, void* context, uint16_t id, TransformVec& out)
{
    if (property != 0 && property->v24(context, &property) &&
        property->mId == id && (property->mFlags & 0x10) != 0) {
        uint16_t kind = property->mFlags & 0x30;
        int count;
        const cSPTransform_s00fa_86c0* src;
        if (kind != 0) {
            count = property->mCount;
            src = (const cSPTransform_s00fa_86c0*)*(void**)property;   // the value's leading dword
        } else {
            count = (property->mId != 0);
            src = (property->mId != 0) ? (const cSPTransform_s00fa_86c0*)property : 0;
        }
        out.resize(count);
        FUN_00f339d0(src, src + count, out.mpBegin);
        return true;
    }
    return false;
}

// @ 0x00fa90e0
ResponseCurve& ResponseCurve::Assign(const ResponseCurve& other)
{
    if (this != &other) {
        Rec20_s00fa_86c0* first = mpBegin;
        Rec20_s00fa_86c0* last = mpEnd;
        FUN_00951bf0_s00fa_86c0(last, mpEnd, first);
        mpEnd -= (last - first);
        DoAssign(other.mpBegin, other.mpEnd, &other);
    }
    return *this;
}

// @ 0x00fa9140
int cTerrainSphere_s00fa_86c0::CreateDecal(int a, int b, int c, float d)
{
    if (mDecalManager)
        return mDecalManager->CreateDecal(a, b, c, d);
    return 0;
}

// @ 0x00fa9170
void cTerrainSphere_s00fa_86c0::DoDeferredUpdate()
{
    if (!v4c(1))
        return;

    static Vector4 sUnitRect(0.0f, 0.0f, 1.0f, 1.0f);

    TerrainConfig* config = mConfig;
    float f34 = config->mF34;
    cTerrainMapU32* map = config->mpMap;
    cTerrainLevelInfo* level = config->mpLevel;
    float f38 = config->mF38;

    bool anyVisible = false;
    for (int i = 0; i < 6; ++i) {
        if (mRects[i][0] != mRects[i][2] && mRects[i][1] != mRects[i][3] &&
            sUnitRect.x < mRects[i][2] && mRects[i][0] < sUnitRect.z &&
            sUnitRect.y < mRects[i][3] && mRects[i][1] < sUnitRect.w) {
            anyVisible = true;
            float width = (float)(unsigned)level->mCount * 0.0009765625f * 50.0f;
            FUN_00f8b2b0(level, map, i, f34, f38, width,
                         mRects[i][0], mRects[i][1], mRects[i][2], mRects[i][3]);
        }
    }
    if (anyVisible)
        map->BlendMapEdges();

    BuildTerrain((const uint8_t*)&mRects[0][0]);
}

// @ 0x00fa9300
bool cTerrainSphere_s00fa_9300::HandleMessage(uint32_t msgId, SlotMessage* msg)
{
    TerrainSphereHandler* h = (TerrainSphereHandler*)((char*)this + 8);
    if (g_pTerrainSphere_s00fa_9300 == 0)
        return false;
    switch (msgId) {
    case 0x44edd9c:
        h->mState = 1;
        return true;
    case 0x3d5bf9a:
        if (h->mpImpostorJob == 0) {
            h->mState = -1;
            return false;
        }
        if (!TerrainEditor_s00fa_9300()->IsModeA() && !TerrainEditor_s00fa_9300()->IsModeB()) {
            h->mState = -1;
            return false;
        }
        GenerateImpostorUpdate((void*)msg->mData08, (void*)msg->mData10);
        return true;
    case 0x44edd9a:
        h->mState = -1;
        return false;
    case 0x87d5f9bf:
        break;
    default:
        return false;
    }

    if (h->mBackgroundJob) {
        cJob* j = h->mBackgroundJob;
        h->mBackgroundJob = 0;
        j->Release();
    }
    *(uint8_t*)((char*)this + 0x370) = 0;
    if (h->mState != 0)
        return false;
    if (msg->mData10 != (uint32_t)g_TerrainInitCount)
        return false;
    if ((cTerrainSphere_s00fa_9300*)msg->mData08 != this)
        return false;
    if (mpPlanet == 0)
        return false;

    float f = mpPlanet->mF34 * 3.1415927410125732f * 0.5f;
    int count = 0;
    for (int i = 0; i < 6; i++)
        if (((RectT_s00fa_9300*)&mFaceRect[i])->Test())
            count++;

    for (uint32_t i = 0; i < 6; i++) {
        Vec4* p = &mFaceRect[i];
        if (FaceVisible(1)) {
            float dx = p->z - p->x;
            float dy = p->w - p->y;
            float n0 = ((p->x + p->z) * 0.5f) * 2.0f - 1.0f;
            float n1 = ((p->y + p->w) * 0.5f) * 2.0f - 1.0f;
            float inv = 1.0f / sqrtf(n0 * n0 + n1 * n1 + 1.0f);
            float s = (i & 1) ? -inv : inv;
            float sz = sqrtf(dx * dx + dy * dy) * f * 0.5f;
            float v[3];
            unsigned k = i >> 1;
            v[kFacePerm[k * 4 + 0]] = s * n0;
            v[kFacePerm[k * 4 + 1]] = inv * n1;
            v[kFacePerm[k * 4 + 2]] = s;
            if (p->x != p->z && p->y != p->w) {
                PinModelsToTerrain();
                if (sz > 0.0f) {
                    SlotMessage* m = (SlotMessage*)operator new(0x40, "App", 0, 0, 0, 0);
                    m = m ? m->Construct(0) : 0;
                    SlotMessageRef ref;
                    ref.Set(m);
                    m = ref.mpObject;
                    m->mMessageId = 0x182c582;
                    *(float*)&m->mData08 = v[0];
                    *(float*)&m->mData10 = v[1];
                    *(float*)&m->mData18 = v[2];
                    *(float*)&m->mData20 = sz;
                    m->mData28 = msg->mData10;
                    m->mData2C = count;
                    MessageServer_s00fa_9300()->Post4(0x182c582, m, 0, 0);
                }
                FaceSub0(i, p);
                FaceSub1(i, p);
                FaceSub2(i, p);
            }
        }
        mRectB[i].x = 0.0f;
        mRectB[i].y = 0.0f;
        mRectB[i].z = 1.0f;
        mRectB[i].w = 1.0f;
        p->x = 0.0f;
        p->y = 0.0f;
        p->z = 0.0f;
        p->w = 0.0f;
    }
    FaceBegin(1);
    return true;
}

// @ 0x00fa96d0
void cTerrainSphere_s00fa_9300::SetModels()
{    if (mpDefinition == 0)
        return;
    Key_s00fa_9300* keys;
    GetPropertyAsKeyArray(mpDefinition, 0x3a90c57, (uint32_t*)&mNumModels, &keys);
    KeyVec* kv = (KeyVec*)((char*)this + 0x7b0);
    kv->resize(mNumModels);
    ((XformVec*)((char*)this + 0x7c4))->resize(mNumModels);
    {
        uint32_t count = mNumModels;
        Key_s00fa_9300* end = keys + count;
        Key_s00fa_9300* src = keys;
        Key_s00fa_9300* dest = kv->mpBegin;
        while (src != end) {
            dest->instance = src->instance;
            dest->type = src->type;
            dest->group = src->group;
            ++src;
            ++dest;
        }
    }
    uint32_t n = mNumModels;
    cSPTransform_s00fa_9300* xf;
    GetPropertyAsTransformArray(mpDefinition, 0x3a90c5f, &n, &xf);
    CopyTransforms(xf, xf + mNumModels, ((XformVec*)((char*)this + 0x7c4))->mpBegin);}

// @ 0x00fa9790
bool cTerrainBackgroundMapJob::Update(int a)
{
    (void)a;
    mpSphere->FinishBackgroundMap();
    SlotMessage* m = (SlotMessage*)operator new(0x40, "Terrain/Sphere/kMessageEndBackgroundMapGeneration", 0, 0, 0, 0);
    if (m != 0) {
        m->mMessageId = 0;
        m->mpVftable = &g_vtbl_BehaviorMessage;
        _InterlockedExchange((long volatile*)&m->mRefCount, 0);
        m->mpVftable = &g_vtbl_SlotMessage;
        m->mData38 = 0;
        (*(void(__thiscall**)(SlotMessage*))(*(uint32_t volatile*)m + 4))(m);
    }
    m->mMessageId = 0x87d5f9bf;
    m->mData08 = (uint32_t)mpSphere;
    m->mData10 = mF10;
    MessageServer_s00fa_9300()->Post4(0x87d5f9bf, m, 0, 0);
    MsgRelease(m);
    return true;
}

// @ 0x00fa9840
Blob110::Blob110(const Blob110& o)
{
    mpInline = mBuffer;
    mpEnd = mBuffer;
    mpBegin = mBuffer;
    mpCapacity = (Elem20*)((char*)mBuffer + 0x8c);
    AssignRange(o.mpBegin, o.mpEnd, &o);
    mU = o.mU;
    mB0 = o.mB0;
    mB4 = o.mB4;
    mB8 = o.mB8;
    mBC = o.mBC;
    float* t = (float*)&mTail;
    const float* s = (const float*)&o.mTail;
    t[0] = s[0];   t[1] = s[1];   t[2] = s[2];   t[3] = s[3];   t[4] = s[4];
    t[5] = s[5];   t[6] = s[6];   t[7] = s[7];   t[8] = s[8];   t[9] = s[9];
    t[10] = s[10]; t[11] = s[11]; t[12] = s[12]; t[13] = s[13]; t[14] = s[14];
    t[15] = s[15]; t[16] = s[16]; t[17] = s[17]; t[18] = s[18]; t[19] = s[19];
}

// @ 0x00fa99c0
Blob110& Blob110::operator=(const Blob110& o)
{
    AssignFrom(o);
    mU.a = o.mU.a;
    mU.b = o.mU.b;
    mU.c = o.mU.c;
    mB0 = o.mB0;
    mB4 = o.mB4;
    mB8 = o.mB8;
    mBC = o.mBC;
    mTail.d[0] = o.mTail.d[0];
    mTail.d[1] = o.mTail.d[1];
    mTail.d[2] = o.mTail.d[2];
    mTail.d[3] = o.mTail.d[3];
    mTail.d[4] = o.mTail.d[4];
    mTail.d[5] = o.mTail.d[5];
    mTail.d[6] = o.mTail.d[6];
    mTail.d[7] = o.mTail.d[7];
    mTail.d[8] = o.mTail.d[8];
    mTail.d[9] = o.mTail.d[9];
    mTail.d[10] = o.mTail.d[10];
    mTail.d[11] = o.mTail.d[11];
    mTail.d[12] = o.mTail.d[12];
    mTail.d[13] = o.mTail.d[13];
    mTail.d[14] = o.mTail.d[14];
    mTail.s = o.mTail.s;
    return *this;
}

// @ 0x00fa9b50
void cTerrainSphere_s00fa_9300::ResetQuadsCaller()
{
    mF370 = 1;
    ResetFaceState(-1);
    FaceState(7);
    *(uint8_t*)((char*)this + 0x368 + mF36C) = 0;
    mF36C = 1 - mF36C;
    uint32_t idx = mF36C;
    for (int i = 0; i < 6; i++) {
        Vec4 t = mVec[i + idx * 6];
        mFaceRect[i] = t;
        mQuadsA[i]->FaceSubA(i, &t);
        mQuadsA[i]->FaceSubB(i, &t);
    }
    ResetQuads();
    mF33D = 0;
    FinishBackgroundMap();
    Vec4 u = {0.0f, 0.0f, 1.0f, 1.0f};
    for (int i = 0; i < 6; i++)
        mQuadsA[i]->FaceSubC(i, &u);

    SlotMessage* m = (SlotMessage*)operator new(0x40, "App", 0, 0, 0, 0);
    if (m != 0) {
        m->mMessageId = 0;
        m->mpVftable = &g_vtbl_BehaviorMessage;
        _InterlockedExchange((long volatile*)&m->mRefCount, 0);
        m->mpVftable = &g_vtbl_SlotMessage;
        m->mData38 = 0;
        (*(void(__thiscall**)(SlotMessage*))(*(uint32_t volatile*)m + 4))(m);
    }
    m->mMessageId = 0x87d5f9bf;
    m->mData08 = (uint32_t)this;
    m->mData10 = (uint32_t)g_TerrainInitCount;
    if (mF880) {
        MessageServer_s00fa_9300()->Post3(0x87d5f9bf, m, 0);
        MsgRelease(m);
    } else {
        MessageServer_s00fa_9300()->Post4(0x87d5f9bf, m, 0, 0);
        MsgRelease(m);
    }
}

// @ 0x00fa9d20
void cTerrainSphere_s00fa_9d20::SetDefinition(PropList* def)
{
    PropList* old = mpDefinition;
    if (def != old) {
        if (def) def->AddRef();
        mpDefinition = def;
        if (old) old->Release();
    }
    mKey.instance = ((int*)def)[2];
    mKey.type = 0x11989b7;
    mKey.group = ((int*)def)[4];

    ClearModels();
    mRelevelC.clear();
    mRelevelA.clear();
    mRelevelB.clear();
    mCamOffsetY = 0;

    if (mpDefinition) {
        SetModels();
        KeyVector keys;
        XformVector xf;
        ReadKeyArray(mpDefinition, 0x3ad5568, 0x20, &keys);
        ReadTransformArray(mpDefinition, 0x3ad5569, 0x38, &xf);
        int n = keys.mEnd - keys.mBegin;
        cSPTransform_s00fa_9d20* t = xf.mBegin;
        Key_s00fa_9d20* k = keys.mBegin;
        if (n != 0) {
            do {
                cRelevel r(*t, *k);
                mRelevelC.push_back(r);
                ++t; ++k;
            } while (--n != 0);
        }
        keys.erase(keys.mBegin, keys.mEnd);
        xf.mEnd = xf.mEnd - (xf.mEnd - xf.mBegin);

        ReadKeyArray(mpDefinition, 0x43b29e1, 0x20, &keys);
        ReadTransformArray(mpDefinition, 0x43b29e2, 0x38, &xf);
        n = keys.mEnd - keys.mBegin;
        t = xf.mBegin;
        k = keys.mBegin;
        if (n != 0) do {
            PropListRef list;
            Property_s00fa_9d20* prop;
            if (PropertyManager()->GetPropertyList(k->instance, k->group, list.AsPP())) {
                if (GetTyped(list.p, 0xc5ae63ed, 1, prop) && *(const char*)prop->GetData() != 0) {
                    mRelevelB.push_back(cRelevel(*k, *t, 1));
                } else {
                    cRelevel r(*t, *k);
                    mRelevelA.push_back(r);
                }
            }
            ++t; ++k;
        } while (--n != 0);

        Property_s00fa_9d20* prop;
        if (GetTyped(mpDefinition, 0x3ad556a, 10, prop))
            mCamOffsetY = *(const uint32_t*)prop->GetData();

        Vector3_s00fa_9d20 v;
        if (GetPropertyAsVector3(mpDefinition, 0x3a23f98, v)) {
            if (!mpStateMgr->HasWaterSettings())
                mpStateMgr->SetWaterSettings(v.z, v.y, 0);
        }
        if (GetPropertyAsVector3(mpDefinition, 0x3a23f9a, v) || GetPropertyAsVector3(mpDefinition, 0x3a23f99, v)) {
            if (v.x > 0.0f && v.x <= 64.0f && v.y > 0.0f && v.y <= 64.0f)
                mpStateMgr->SetTileRange((v.x - 0.5f) * 0.015625f, (v.y - 0.5f) * 0.015625f);
            mpMapSet->SetValue(v.z);
        }
        if (GetTyped(mpDefinition, 0x536250c, 10, prop))
            mpStateMgr->SetScaleA(*(const uint32_t*)prop->GetData());
        if (GetTyped(mpDefinition, 0x536250d, 10, prop))
            mpStateMgr->SetScaleB(*(const uint32_t*)prop->GetData());
        Vector2 v2;
        if (GetPropertyAsVector2(mpDefinition, 0x536250e, v2))
            mpStateMgr->SetVec2(&v2);
        bool flag = false;
        if (GetTyped(mpDefinition, 0x5408a6c, 1, prop))
            flag = *(const bool*)prop->GetData();
        bool desc = sAppProperties_s00fa_9d20->GetDescription(0x5408a93);
        bool arg = flag & desc;
        ((void (__thiscall*)(cTerrainSphere_s00fa_9d20*, bool))(*(void***)this)[0xe0 / 4])(this, arg);
    }
    mpStateMgr->UpdateFromDefinition(def);
}

// @ 0x00faa5c0
void cTerrainSphere_s00fa_a5c0::SaveModifications()
{
    if (mSink) {
        KeyVector_s00fa_a5c0 keys;
        XformVector_s00fa_a5c0 xf;
        keys.Reserve(mRelevelC.size());
        xf.Reserve(mRelevelC.size());
        AppendRelevels(keys, xf, mRelevelC);
        Variant_s00fa_a5c0 vKeys;
        vKeys.Set(0x20, 0x98, keys.mBegin, 0xc, keys.mEnd - keys.mBegin);
        Variant_s00fa_a5c0 vXf;
        int nXf = xf.mEnd - xf.mBegin;
        vXf.Set(0x38, 0x98, xf.mBegin, 0x38, nXf);
        mSink->SetProperty(0x3ad5568, &vKeys);
        mSink->SetProperty(0x3ad5569, &vXf);
        keys.erase(keys.mBegin, keys.mEnd);
        xf.mEnd = xf.mEnd - nXf;

        keys.Reserve(mRelevelA.size() + mRelevelB.size());
        xf.Reserve(mRelevelA.size() + mRelevelB.size());
        AppendRelevels(keys, xf, mRelevelA);
        AppendRelevels(keys, xf, mRelevelB);
        Variant_s00fa_a5c0 vKeys2;
        vKeys2.Set(0x20, 0x98, keys.mBegin, 0xc, keys.mEnd - keys.mBegin);
        Variant_s00fa_a5c0 vXf2;
        vXf2.Set(0x38, 0x98, xf.mBegin, 0x38, xf.mEnd - xf.mBegin);
        mSink->SetProperty(0x43b29e1, &vKeys2);
        mSink->SetProperty(0x43b29e2, &vXf2);
        SetModels();
    }
}

// @ 0x00faacd0
bool __cdecl CreateTerrainMapJob(cTerrainSphere_s00fa_a5c0* unused, cJob_s00fa_a5c0** out)
{
    if (GetJobManager()->CanRegister(out)) {
        void* info = AllocJobInfo(
            sizeof(cTerrainMapJobInfo), "Terrain/Sphere/cTerrainMapJobInfo", 0, 0, 0, 0);
        if (info) {
            ::new (info) cTerrainMapJobInfo(out);
            cILayerI* layer = (cILayerI*)info;
            layer->l0();
        } else {
            info = 0;
        }
        (*out)->SetObject(info);
        (*out)->mpFunction = (void*)&TerrainMapJobCallback;
        (*out)->mpUserData = info;
        (*out)->mPriority = (int)0x80000000;
        if (info)
            ((cILayerI*)info)->Release();
        return true;
    }
    return false;
}

// @ 0x00faad80
void cTerrainSphere_s00fa_a5c0::UpdatePostCamera(int arg1, int arg2)
{
    if (mFieldA48 != 0) {
        if (mFieldA48 > 0 && --mFieldA48 == 0) {
            v80();
            FUN_00f9b8c0(&arg1, &arg1, mFieldFC != 0, 0, 10.0f);
        }
        return;
    }
    if (mFieldFC != 0)
        return;

    if (mField360 != mConfig->m34 ||
        mField364 != mConfig->m3c * mConfig->m38 ||
        mFlag111 != 0) {
        AddToEffectsSystem();
        float vals[3];
        vals[0] = mConfig->m3c * mConfig->m38 + mConfig->m34;
        vals[1] = mConfig->m50;
        vals[2] = mConfig->m54;
        float* radius = (vals[0] > vals[1]) ? &vals[0] : &vals[1];
        ModelManager_s00fa_a5c0()->v1c(0x3fbae24)->v15c(0, &g16c9e8c, *radius);
    }

    cTerrainSphere_s00fa_a5c0* base = (cTerrainSphere_s00fa_a5c0*)((char*)this - mField36c);
    mFlag33d = (mFlag33d != 0) || ((base->mFlag369 & 7) != 0);
    v10();
    g16c9e7c[0] = 0;
    g16c9e7c[1] = 0;
    g16c9e7c[2] = 0;
    int count = mField20c;
    ++mCounter114;
    if (count != 0) {
        int n = mField1d0;
        FUN_00fbf570(arg2, 100.0f, (n != 4) ? n : 0);
    }

    if (mFlag33d != 0 && mFlag370 == 0 && vd8()) {
        FUN_00f96370();
        for (int i = 0; i < 6; ++i) {
            const float* src = &mRects[(i + 6 * mField36c) * 4];
            float rect[4];
            rect[0] = src[0];
            rect[1] = src[1];
            rect[2] = src[2];
            rect[3] = src[3];
            mRegions[i][0] = rect[0];
            mRegions[i][1] = rect[1];
            mRegions[i][2] = rect[2];
            mRegions[i][3] = rect[3];
            if (v4c(8)) {
                rect[0] = 0.0f;
                rect[1] = 0.0f;
                rect[2] = 1.0f;
                rect[3] = 1.0f;
            }
            cTerrainSphereQuad_s00fa_a5c0* quad = mQuads[i];
            quad->TraverseSubdivided(i, rect);
            quad->MarkVerticesDirty(i, rect);
            quad->MarkIndicesDirty(i, rect);
        }
        FUN_00f96f90();
        mFlag370 = 1;
        if (mJob) {
            cJob_s00fa_a5c0* old = mJob;
            mJob = 0;
            old->Release();
        }
        CreateTerrainMapJob(this, &mJob);
        mJob->GetStatus();
        mFlag33d = 0;
    }

    FUN_00f9ba40(arg2);
    {
        float dx = mCenterX, dy = mCenterY, dz = mCenterZ;
        float dist = sqrtf(dx * dx + dy * dy + dz * dz) - mConfig->m34;
        float limit = (mConfig->m40 + mConfig->m3c) * mConfig->m38 - 1.0f;
        mFlag110 = (limit > dist);
    }
    UpdateQuadsPostCamera(arg2);
    cTerrainSphereRegion* region = mField210;
    if (region)
        region->FUN_00fc7b30(arg2);
}

// @ 0x00fab230
void cQuadVec::Append()
{
    if (mEnd < mCap) {
        cQuadElem* p = mEnd++;
        ::new (p) cQuadElem();
    } else {
        cQuadElem tmp;
        DoInsertValue(mEnd, tmp);
    }
}

// @ 0x00fab2b0
namespace SP {
static __declspec(noinline) void AddRibbonQuad(cRibbonPolyList* lists, const cSPVector3_s00fa_b2b0* pos, const cSPTexCoord* tc, const float* alpha, const cRibbonPolyInfo* info)
{
    cCubeMapCoord_s00fa_b2b0 c0 = ToCubeMapCoord(pos[0]);
    cCubeMapCoord_s00fa_b2b0 c1 = ToCubeMapCoord(pos[1]);
    cCubeMapCoord_s00fa_b2b0 c2 = ToCubeMapCoord(pos[2]);
    cCubeMapCoord_s00fa_b2b0 c3 = ToCubeMapCoord(pos[3]);

    if (c0.face == c1.face && c0.face == c2.face && c0.face == c3.face)
    {
        cRibbonPolyList& list = lists[c0.face];
        list.push_back();
        cRibbonFacePoly& poly = list.back();
        poly.resize(4);
        poly[0].mPos = c0.uv;
        poly[0].mTC = tc[0];
        poly[0].mAlpha = alpha[0];
        poly[1].mPos = c1.uv;
        poly[1].mTC = tc[1];
        poly[1].mAlpha = alpha[1];
        poly[2].mPos = c2.uv;
        poly[2].mTC = tc[2];
        poly[2].mAlpha = alpha[2];
        poly[3].mPos = c3.uv;
        poly[3].mTC = tc[3];
        poly[3].mAlpha = alpha[3];
        poly.mInfo = *info;
        poly.ComputeBounds();
        poly.BuildPatch();
        return;
    }

    cRibbonPolyList* list = lists;
    for (int face = 0; face < 6; ++face, ++list)
    {
        cBrushVertex verts[16];
        int numVerts = 4;
        verts[0].mPosition = Normalized(pos[0]);
        verts[0].mUV = tc[0];
        verts[0].mIntensity = alpha[0];
        verts[1].mPosition = Normalized(pos[1]);
        verts[1].mUV = tc[1];
        verts[1].mIntensity = alpha[1];
        verts[2].mPosition = Normalized(pos[2]);
        verts[2].mUV = tc[2];
        verts[2].mIntensity = alpha[2];
        verts[3].mPosition = Normalized(pos[3]);
        verts[3].mUV = tc[3];
        verts[3].mIntensity = alpha[3];

        for (int i = 0; i < 4; ++i)
        {
            if (numVerts == 0)
                break;
            ClipBrushPoly(verts, &numVerts, &gCubeFacePlanes[face][i]);
        }

        if (numVerts > 2)
        {
            list->push_back();
            cRibbonFacePoly& poly = list->back();
            poly.resize(numVerts);

            const uint8_t* axes = gCubeFaceAxes[face >> 1];
            float sign = (face & 1) ? -1.0f : 1.0f;
            float flip[3];
            flip[0] = sign;
            flip[1] = 1.0f;
            flip[2] = sign;
            float s0 = flip[axes[0]];
            float s1 = flip[axes[1]];
            float s2 = flip[axes[2]];

            float p[3];
            for (int j = 0; j < numVerts; ++j)
            {
                p[axes[0]] = verts[j].mPosition.x * s0;
                p[axes[1]] = s1 * verts[j].mPosition.y;
                p[axes[2]] = verts[j].mPosition.z * s2;
                float inv = 1.0f / p[2];
                cSPVector2_s00fa_b2b0 uv;
                uv.x = (inv * p[0] + 1.0f) * 0.5f;
                uv.y = (inv * p[1] + 1.0f) * 0.5f;
                poly[j].mPos = uv;
                poly[j].mTC = verts[j].mUV;
                poly[j].mAlpha = verts[j].mIntensity;
            }
            poly.mInfo = *info;
            poly.ComputeBounds();
            poly.BuildPatch();
        }
    }
}
}  // namespace SP

// @ 0x00fabd60
namespace SP {
void cRibbonBuilder::BuildRibbon(int ribbonID, cRibbonPath* path)
{
    cLocalPolyList lists[6];
    float runLen = 0.0f;
    int count = (int)(path->mpEnd - path->mpBegin);
    float prevCx = 0, prevCy = 0, prevCz = 0, prevOx = 0, prevOy = 0, prevOz = 0;

    for (int i = 0; i < count; ++i)
    {
        const cRibbonPathPoint* p = &path->mpBegin[i];
        const cRibbonPathPoint* pv = (i != 0) ? p - 1 : p;
        const cRibbonPathPoint* nx = (i != count - 1) ? p + 1 : p;

        float pvX = p->z * pv->y - p->y * pv->z;
        float pvY = p->x * pv->z - p->z * pv->x;
        float pvZ = p->y * pv->x - p->x * pv->y;
        float s0 = 1.0f / sqrtf(pvX * pvX + pvZ * pvZ + pvY * pvY + 1e-08f);
        float n0x = s0 * pvX;
        float n0y = pvY * s0;
        float n0z = pvZ * s0;

        float nxX = p->y * nx->z - p->z * nx->y;
        float nxY = p->z * nx->x - p->x * nx->z;
        float nxZ = p->x * nx->y - p->y * nx->x;
        float s1 = 1.0f / sqrtf(nxX * nxX + nxY * nxY + nxZ * nxZ + 1e-08f);

        float cosA;
        if (i == 0 || i == count - 1)
        {
            cosA = -1.0f;
        }
        else
        {
            float dnx = nx->x - p->x;
            float dny = nx->y - p->y;
            float dnz = nx->z - p->z;
            float dpx = pv->x - p->x;
            float dpy = pv->y - p->y;
            float dpz = pv->z - p->z;
            cosA = (dpx * dnx + (dpy * dny + dpz * dnz)) /
                   (sqrtf(dpz * dpz + dpy * dpy + dpx * dpx) * sqrtf(dnz * dnz + dny * dny + dnx * dnx));
            if (cosA <= -1.0f) cosA = -1.0f;
            if (cosA >= 0.999f) cosA = 0.999f;
        }

        float bx = s1 * nxX + n0x;
        float by = s1 * nxY + n0y;
        float bz = s1 * nxZ + n0z;

        float sp = 1.0f / sqrtf(p->y * p->y + (p->x * p->x + p->z * p->z));
        float cx = p->x * sp * 500.0f;
        float cy = sp * p->y * 500.0f;
        float cz = sp * p->z * 500.0f;

        float miter = sqrtf(2.0f / (1.0f - cosA));
        float sb = 1.0f / sqrtf(by * by + (bz * bz + bx * bx));
        float ox = sb * bx * miter * 6.0f;
        float oy = by * sb * miter * 6.0f;
        float oz = bz * sb * miter * 6.0f;

        if (i > 0)
        {
            float dx = cx - prevCx;
            float dy = cy - prevCy;
            float dz = cz - prevCz;
            float corners[12];
            corners[0] = prevCx - prevOx;
            corners[1] = prevCy - prevOy;
            corners[2] = prevCz - prevOz;
            corners[3] = prevOx + prevCx;
            corners[4] = prevOy + prevCy;
            corners[5] = prevOz + prevCz;
            corners[6] = ox + cx;
            corners[7] = oy + cy;
            corners[8] = oz + cz;
            corners[9] = cx - ox;
            corners[10] = cy - oy;
            corners[11] = cz - oz;
            float alpha[4];
            alpha[0] = (i == 1) ? 0.0f : 1.0f;
            alpha[1] = (i == 1) ? 0.0f : 1.0f;
            alpha[2] = (i == count - 1) ? 0.0f : 1.0f;
            alpha[3] = (i == count - 1) ? 0.0f : 1.0f;
            float startLen = runLen;
            runLen = sqrtf(dz * dz + (dy * dy + dx * dx)) + runLen;
            cSPTexCoord tc[4];
            tc[0].u = -1.0f; tc[0].v = startLen;
            tc[1].u = 1.0f;  tc[1].v = startLen;
            tc[2].u = 1.0f;  tc[2].v = runLen;
            tc[3].u = -1.0f; tc[3].v = runLen;
            cRibbonPolyInfo info;
            info.mTopV = runLen;
            info.mLengthV = sqrtf((dz * dz + dy * dy) + dx * dx);
            info.mRibbonID = ribbonID;
            AddRibbonQuad((cRibbonPolyList*)lists, (const cSPVector3_s00fa_b2b0*)corners, tc, alpha, &info);
        }
        prevCx = cx; prevCy = cy; prevCz = cz;
        prevOx = ox; prevOy = oy; prevOz = oz;
    }

    for (int f = 0; f < 6; ++f)
    {
        if (mFaceQuads[f])
            mFaceQuads[f]->AddRibbonPolys(&lists[f]);
    }
}
}  // namespace SP

// @ 0x00fac5c0
void StrandMesh::Build()
{
    for (int f = 0; f < 6; ++f) {
        if (mFaces[f] != 0) mFaces[f]->Clear();
    }
    FaceBuilder builders[6];
    { FaceBuilder* q = builders; int c = 5; do { q->Init(); ++q; } while (--c >= 0); }

    for (unsigned s = 0; s < (unsigned)StrandCount(); ++s) {
        if (mpStrands[s] == 0) continue;
        int n = (mpStrands[s]->mpEnd - mpStrands[s]->mpBegin);
        float len = 0.0f;
        float prevPos[3], prevOff[3];
        for (int i = 0; i < n; ++i) {
            float scale = mpStrands[s]->mpBegin[i].scale;
            const Point* cur = &mpStrands[s]->mpBegin[i];
            const Point* prv = cur;
            if (i != 0) prv = &mpStrands[s]->mpBegin[i - 1];
            const Point* nxt = cur;
            if (i != n - 1) nxt = &mpStrands[s]->mpBegin[i + 1];

            // normal before the point: prv x cur
            float a0 = prv->y * cur->z - prv->z * cur->y;
            float a2 = prv->x * cur->y - prv->y * cur->x;
            float a1 = prv->z * cur->x - prv->x * cur->z;
            float ia = 1.0f / sqrtf((a1 * a1 + (a2 * a2 + a0 * a0)) + kEps_s00fa_c5c0);
            float na0 = a0 * ia, na1 = a1 * ia, na2 = a2 * ia;
            // normal after the point: cur x nxt
            float b0 = nxt->z * cur->y - nxt->y * cur->z;
            float b1 = nxt->x * cur->z - nxt->z * cur->x;
            float b2 = nxt->y * cur->x - nxt->x * cur->y;
            float ib = 1.0f / sqrtf((b2 * b2 + (b1 * b1 + b0 * b0)) + kEps_s00fa_c5c0);

            float dot;
            if (i == 0 || i == n - 1) {
                dot = -1.0f;
            } else {
                float p0 = prv->x - cur->x, p1 = prv->y - cur->y, p2 = prv->z - cur->z;
                float q0 = nxt->x - cur->x, q1 = nxt->y - cur->y, q2 = nxt->z - cur->z;
                dot = (p0 * q0 + (p1 * q1 + p2 * q2)) /
                      (sqrtf(p0 * p0 + (p1 * p1 + p2 * p2)) * sqrtf((q2 * q2 + q1 * q1) + q0 * q0));
                if (dot <= -1.0f) dot = -1.0f;
                if (0.999f <= dot) dot = 0.999f;
            }

            // miter direction
            float m0 = ib * b0 + na0;
            float m1 = b2 * ib + na2;
            float m2 = b1 * ib + na1;
            float ip = 1.0f / sqrtf(cur->x * cur->x + (cur->y * cur->y + cur->z * cur->z));
            float px = (ip * cur->x) * 500.0f;
            float py = (ip * cur->y) * 500.0f;
            float pz = (ip * cur->z) * 500.0f;
            float k = sqrtf(2.0f / (1.0f - dot));
            float im = 1.0f / sqrtf(m2 * m2 + (m1 * m1 + m0 * m0));
            float ox = (((im * m0) * k) * 6.0f) * scale;
            float oy = (((m2 * im) * k) * 6.0f) * scale;
            float oz = (((m1 * im) * k) * 6.0f) * scale;

            if (i > 0) {
                float pos[12], uv[8], alpha[4], info[3];
                pos[0] = prevPos[0] - prevOff[0];
                pos[1] = prevPos[1] - prevOff[1];
                pos[2] = prevPos[2] - prevOff[2];
                pos[3] = prevOff[0] + prevPos[0];
                pos[4] = prevPos[1] + prevOff[1];
                pos[5] = prevPos[2] + prevOff[2];
                pos[6] = ox + px;
                pos[7] = oy + py;
                pos[8] = oz + pz;
                pos[9] = px - ox;
                pos[10] = py - oy;
                pos[11] = pz - oz;
                float dx = px - prevPos[0], dy = py - prevPos[1], dz = pz - prevPos[2];
                float newLen = sqrtf(dz * dz + dy * dy + dx * dx) + len;
                uv[0] = -1.0f; uv[1] = len;
                uv[2] = 1.0f;  uv[3] = len;
                uv[4] = 1.0f;  uv[5] = newLen;
                uv[6] = -1.0f; uv[7] = newLen;
                alpha[0] = alpha[1] = (i == 1) ? 0.0f : 1.0f;
                alpha[2] = alpha[3] = (i == n - 1) ? 0.0f : 1.0f;
                len = newLen;
                info[0] = len;
                info[1] = sqrtf((dz * dz + dy * dy) + dx * dx);
                ((uint32_t*)info)[2] = s;
                builders[0].AddQuad(pos, uv, alpha, info);
            }
            prevPos[0] = px; prevPos[1] = py; prevPos[2] = pz;
            prevOff[0] = ox; prevOff[1] = oy; prevOff[2] = oz;
        }
    }

    for (int f = 0; f < 6; ++f) {
        if (mFaces[f] != 0) mFaces[f]->Flush(&builders[f]);
    }
    for (int k = 5; k >= 0; --k) builders[k].Destroy();
}

// @ 0x00facef0
uint32_t StrandMesh::AddStrand(Strand* p)
{
    uint32_t index = AllocStrandIndex();
    mpStrands[index] = p;
    BuildRibbon(index, p);
    return index;
}

// @ 0x00facf20
void StrandMesh::RemoveStrand(uint32_t index)
{
    DecalRecord* p = (*(DecalRecord* (__thiscall*)(StrandMesh*, uint32_t))((char*)mpVtbl + 0xc4))(this, index);
    if (p != 0) {
        p->mVertices.CopyUninit(p->mVertices.mpBegin, p->mVertices.mpEnd);
        void* pBegin = p->mVertices.mpBegin;
        if (pBegin != 0 && ((int*)pBegin)[-1] != 0)
            FreeArr(pBegin);
        FreeArr(p);
    }
    mpStrands[index] = 0;
    if (mFree.mpEnd < mFree.mpCap)
        *mFree.mpEnd++ = index;
    else
        mFree.DoInsertValue(mFree.mpEnd, index);
    Build();
}

// @ 0x00facfc0
void DecalHost::AttachDecal()
{
    for (int face = 0; face < 6; ++face)
        mpMesh->mFaces[face]->AddDecal(this);
    mFlags |= 0x10;
}
