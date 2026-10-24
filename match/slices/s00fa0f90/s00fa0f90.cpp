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

void* __cdecl operator new(unsigned size, const char* name, int a, int b,
                           const char* file, int line);                  // 0x00f473a0

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
    virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
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

extern int g_TerrainInitCount;                  // 0x016c9e64
extern bool g_TerrainStaticsReady;              // 0x016c9e60
extern uint32_t g_TerrainPoolParam;             // 0x016c9e74
extern cDirectPropertyList* g_AppProperties;    // 0x015fd918
extern uint32_t g_SharedResourceID;             // 0x015b1120
extern const char kImpostorRenderTargetName[];  // 0x01490dfc

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

// ---- shared helpers used by the terrain sphere's impostor scratch data ------------------------

void __cdecl EastlDeallocate(void* p);          // 0x00f47380

// A 0x110-byte record with its primary allocation at +0 and an embedded alternative buffer at +0x10.
struct ImpostorRecord110 {
    void* mpData;                               // +0x000
    uint32_t mPad04[3];                         // +0x004
    void* mpInline;                             // +0x010
    uint32_t mPad14[(0x110 - 0x014) / 4];       // +0x014
};

// @ 0x00fa1b10
void* __cdecl DestroyImpostorRange(ImpostorRecord110* first, ImpostorRecord110* last,
                                   ImpostorRecord110* out)
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

// ---- vector<Rec20> insert(count) --------------------------------------------------------------
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

extern const char kAllocTagSimulator[];         // 0x013f09b4
extern const char kEastlAllocFile[];            // 0x013ebb38

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

// ---- 16-byte sort records and the eastl introsort helpers ------------------------------------
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
