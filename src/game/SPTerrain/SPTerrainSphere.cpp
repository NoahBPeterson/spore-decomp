// src/game/SPTerrain/SPTerrainSphere.cpp -- migrated from slice(s) s00fab2b0, s00faa5c0, s00fa9d20, s00fa75f0, s00fa5610, s00fa3860, s00fa0f90, s00f986f0 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainSphere.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

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
// ---- items of slice s00f986f0 end

// ---- items of slice s00fa0f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile*, long);
extern "C" long __cdecl _InterlockedIncrement(long volatile*);
extern int g_TerrainInitCount;                  // 0x016c9e64
extern bool g_TerrainStaticsReady;              // 0x016c9e60
extern uint32_t g_TerrainPoolParam;             // 0x016c9e74
extern uint32_t g_SharedResourceID;             // 0x015b1120
#pragma intrinsic(_InterlockedExchange, _InterlockedExchangeAdd, _InterlockedIncrement)
void* __cdecl operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
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
    virtual void v0(); virtual void v1();
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
    virtual void v0(); virtual void v1();
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
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual bool AddHandler(void* handler, uint32_t messageID);   // slot 8 (+0x20)
};
cMessageServer* MessageServer();    // 0x0067dcc0
struct cResourceSource {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual AtomicRefCounted* Get(uint32_t id, int a, int b);     // slot 8 (+0x20)
};
cResourceSource* GetResourceSource();   // 0x0067dd60
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
struct cTerrainSphere {
    uint32_t pad0[2];
    uint32_t mHandlerBase;                  // +0x008 (IHandler subobject)
    uint32_t pad0c[(0x2c - 0x0c) / 4];
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
    uint32_t pad880[(0x8a0 - 0x880) / 4];
    JobPtr<cITerrainGenerationStep> mpImpostorJob;   // +0x8a0
    int mImpostorJobState;                  // +0x8a4
    uint32_t pad8a8[(0x8e4 - 0x8a8) / 4];
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
};
// ---- items of slice s00fa0f90 end

// ---- items of slice s00fa3860 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kPi;                // 0x015b1190
extern const float kLerpBase[3];       // 0x015b11ac..0x015b11b4
extern char gSpecialMode;                 // 0x01654c10
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
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasProperty(uint32_t id);                       // +0x1c
    virtual bool GetPropertyAlt(uint32_t id, Property*& result); // +0x20
    virtual bool GetProperty(uint32_t id, Property*& result);    // +0x24
};
bool GetPropertyAsKey(cPropertyList* list, uint32_t id, ResKey* value);           // 0x006a1250
bool GetPropertyAsVector2(cPropertyList* list, uint32_t id, Vector2* value);      // 0x006a10c0
bool GetPropertyAsVector3(cPropertyList* list, uint32_t id, Vector3* value);      // 0x006a1110
bool GetPropertyAsColorRGB(cPropertyList* list, uint32_t id, float* rgb);         // 0x006a11b0
bool GetFloatProperty(cPropertyList* list, uint32_t id, float* value);            // 0x0040cf10
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
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void* GetCurrentMode();   // +0x38
};
IApp* App();                          // 0x0067dd10
struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18();
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
struct cTerrainSphere_s00fa_3860 {
    char pad0[0x20c];
    LightInfo* mpLight;                   // +0x20c
    void ApplyModelFootprint(const Transform* modelXform, cPropertyList* props, void* a3, float* faceBoxes, bool bDecal);  // 0x00fa3c10 (cTerrainSphere::ApplyModelFootprint)
    void DrawFootprint(Transform* xform, float z, cImage* img, const Vector2* off, bool flag, float* faceBoxes, void* a3);   // 0x00f9d5c0
    void DrawResource(Transform* xform, float z, void* res, void* a3);                                                // 0x00fa01e0
    cTerrainSphereDecal* CreateDecal(void* res, Transform* xform, float z, int layer);                                // 0x00fa2920
};
// ---- items of slice s00fa3860 end

// ---- items of slice s00fa5610 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_ZeroX;                                   // 0x016c9e8c
extern float g_ZeroY;                                   // 0x016c9e90
extern float g_ZeroZ;                                   // 0x016c9e94
extern float g_Ident[9];                                // 0x016c9f24 (3x3 block to 0x016c9f44)
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
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property_s00fa_5610** out);       // +0x24
    bool GetDescription(uint32_t id);                            // 0x006a25a0 (ret 4)
    float GetFloatProperty(uint32_t id);                         // 0x006a2710 (ret 4)
};
extern cDirectPropertyList_s00fa_5610* sAppProperties;                      // 0x015fd918
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
struct cViewer_s00fa_5610 { void GetTransform(SPTransform* out); };          // 0x007c40f0 (ret 4)
struct cTerrainInfo { char pad[0x34]; float radius; };
bool QuadDetailTest(cQuad* q, void* terrain, float* outDist);    // 0x00f97960 (stdcall, ret 0xc)
void SortQuads(QContainer* first, QContainer* last, bool flag);  // 0x00fa2660 (cdecl)
class cTerrainSphere_s00fa_5610 {
public:
    virtual void vfn0(); virtual void vfn1(); virtual void vfn2();
    virtual cTerrainInfo* GetInfo();                             // +0xc
    void UpdateQuadsPostCamera(void* camera);                    // 0x00fa5610

    char pad0[0x118 - 4];
    cQuad* faceRoots[6];             // +0x118
    cQuad* atmoRoots[6];             // +0x130
    char pad1[0x190 - 0x148];
    QCVector renderQuads;            // +0x190
    QCVector faceRootArray;          // +0x1a4
    QCVector atmoRootArray;          // +0x1b8
    char pad2[0x1e8 - 0x1cc];
    bool flagA;                      // +0x1e8
    char pad3[0x30c - 0x1e9];
    char decalState[0x8e4 - 0x30c];  // +0x30c
    cViewer_s00fa_5610* viewer;                 // +0x8e4
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
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void SetProperty(uint32_t id, Variant_s00fa_a5c0* v);              // +0x14
};
template <class T> struct RecVec { T* mBegin; T* mEnd; T* mCap; Allocator_s00fa_a5c0 mAlloc;
    int size() const { return mEnd - mBegin; } };
struct cTerrainSphere_s00fa_a5c0 {
    char pad00[0x28];
    IConfigSink* mSink;                         // +0x28
    char pad2c[0x770 - 0x2c];
    RecVec<cRelevelI> mRelevelA;                 // +0x770
    char pad780[4];
    RecVec<cRelevelI> mRelevelB;                 // +0x784
    char pad794[4];
    RecVec<cRelevel_s00fa_a5c0> mRelevelC;                 // +0x798
    void SetModels();                           // 0x00fa96d0
    void SaveModifications();
};
template <class R> static __forceinline void AppendRelevels(KeyVector_s00fa_a5c0& keys, XformVector_s00fa_a5c0& xf, const RecVec<R>& v)
{
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        keys.push_back(v.mBegin[i].mKey);
        xf.push_back(v.mBegin[i].mTransform);
    }
}
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

// @ 0x00fab2b0
namespace SP {
static void AddRibbonQuad(cRibbonPolyList* lists, const cSPVector3_s00fa_b2b0* pos, const cSPTexCoord* tc, const float* alpha, const cRibbonPolyInfo* info)
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
