// Slice s00fa0f90: SP::cTerrainSphere::Initialize (0x00fa0f90, 1726 bytes; the PDB anchor calls it GetConfig).
// Creates the terrain sphere's runtime objects: vertex format, decal manager, viewer, state manager,
// optional weather manager, quad buffer pool, the 12 root quads (6 faces x 2 layers), message
// handler registrations, the impostor job and the shared atomic-refcounted resource at +0x308.
// Retail layout: only the fields this function touches are declared (the rest is padding).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (movss/xorps float math, x87 float copies, no EH frame).
#include "types.h"

extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile*, long);
extern "C" long __cdecl _InterlockedIncrement(long volatile*);
#pragma intrinsic(_InterlockedExchange, _InterlockedExchangeAdd, _InterlockedIncrement)

void* __cdecl operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0

// ---- small helper types ----------------------------------------------------------------

struct Vec4 {
    float x, y, z, w;
};

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

// Object with an atomic refcount at +8 (the shared resource stored at +0x308).
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

// Primary-base refcounted job (AddRef = slot 0, Release = slot 1); an interface, so its
// constructor stores no vptr.
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

// Reference-counted via a secondary base at +8 (AddRef = slot 2, Release = slot 3).
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

struct cTerrainSphere;

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

extern int g_TerrainInitCount;                  // 0x016c9e64
extern bool g_TerrainStaticsReady;              // 0x016c9e60
extern uint32_t g_TerrainPoolParam;             // 0x016c9e74
extern cDirectPropertyList* g_AppProperties;    // 0x015fd918
extern uint32_t g_SharedResourceID;             // 0x015b1120

// Intrusive-pointer fields assigned with the usual AddRef-new / Release-old protocol.
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

// ---- the function ----------------------------------------------------------------------

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
