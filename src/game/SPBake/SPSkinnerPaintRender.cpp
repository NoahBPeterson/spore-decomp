// src/game/SPBake/SPSkinnerPaintRender.cpp -- migrated from slice(s) s0051c470, s0051afd0, s0051a350, s00519640, s00518f10, s005182f0, s00517430, s005169d0, s00425a80 by tools/migrate/rewrite.py
// Object file: SPBake/SPSkinnerPaintRender.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <new>
#include <intrin.h>
#include "EA/Audio/FactoryBinarySampleData.h"
#include "SP/cDynamicDrawBase.h"
#include "SP/cDynamicDrawBaseRC.h"
#include "SP/cIDynamicDraw.h"
#include "SP/cMaterial.h"
#include "SP/cMaterialManager.h"
#include "nSPSkinner/cMeshAORender.h"
#include "SP/cStaticBuffer.h"
#include "nSPSkinner/cPaintList.h"
#include "nSPSkinner/cPaintRenderJob.h"
#include "nSPSkinner/cRTTBuffer.h"
#include "nSPSkinner/cPaintCopyIdentityJob.h"
#include "nSPSkinner/cPaintDifferentiateJob.h"
#include "nSPSkinner/cPaintDilateJob.h"
#include "nSPSkinner/cPaintSplatJob.h"
#include "cSkinpaintTextureExtractor.h"
#include "rw/graphics/Raster.h"

// ---- items of slice s00425a80 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Allocator { const char* mpName; };
void* __cdecl AllocatorAllocate(Allocator* alloc, uint32_t size, uint32_t align, uint32_t offset);  // FUN_0042dee0
void  __cdecl AllocatorDeallocate(void* block);                                                    // EASTL_allocator_deallocate
struct AtomicRefCounted {
    int mVtbl;
    int mPad;
    long mRefCount;
    inline void AddRef() { _InterlockedIncrement(&mRefCount); }
    void Release();                                  // 0x402420
};
struct RefPtr {
    AtomicRefCounted* mp;
    inline RefPtr(const RefPtr& x) throw() : mp(x.mp) { if (mp) mp->AddRef(); }
    inline RefPtr& operator=(const RefPtr& x) {
        AtomicRefCounted* p = x.mp;
        if (p != mp) {
            AtomicRefCounted* old = mp;
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
};
RefPtr* __cdecl CopyBackwardRef(RefPtr* first, RefPtr* last, RefPtr* resultEnd);   // FUN_0042eb20
inline RefPtr* copy_backward_ref(RefPtr* first, RefPtr* last, RefPtr* resultEnd)
{
    const bool bInputIsPointer = false;
    const bool bOutputIsPointer = false;
    return CopyBackwardRef(first, last, resultEnd);
}
struct RefPtrVec {
    RefPtr* mpBegin;
    RefPtr* mpEnd;
    RefPtr* mpCapacity;
    Allocator mAllocator;

    inline RefPtr* DoAllocate(uint32_t n) {
        return n ? (RefPtr*)AllocatorAllocate(&mAllocator, n * sizeof(RefPtr), 4, 0) : 0;
    }
    inline void deallocate(void* p, uint32_t n) {
        if (((uint32_t*)p)[-1]) {
            void* q = p;
            AllocatorDeallocate(q);
        }
    }
    inline void DoFree(RefPtr* p, uint32_t n) {
        if (p)
            deallocate(p, n * sizeof(RefPtr));
    }
    void DoInsertValue(RefPtr* position, const RefPtr& value);
};
inline RefPtr* uninitialized_copy_ref(RefPtr* first, RefPtr* last, RefPtr* result)
{
    const bool bIsPod = true;
    RefPtr* p = (RefPtr*)memcpy(result, first, (uint32_t)((char*)last - (char*)first)) + (last - first);
    const bool bB = true;
    return p;
}
// ---- items of slice s00425a80 end

// ---- items of slice s005169d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);   // 0x011e0744 (static thunk)
#pragma intrinsic(_InterlockedExchange)
struct Vector3 {
    float x, y, z;
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};
struct BoundingBox {
    Vector3 mMin;
    Vector3 mMax;
};
namespace EA {
template <typename T>
class RefCountTemplate_s0051_69d0 {
public:
    RefCountTemplate_s0051_69d0() : mRefCount(0) {}
    virtual ~RefCountTemplate_s0051_69d0() {}
    virtual int AddRef();
    virtual int Release();
    T mRefCount;
};
}
namespace EA {
template <typename T>
class AutoRefCount_s0051_69d0 {
public:
    T* mpObject;
    AutoRefCount_s0051_69d0() : mpObject(0) {}
    ~AutoRefCount_s0051_69d0()
    {
        if (mpObject)
            mpObject->Release();
    }
    AutoRefCount_s0051_69d0& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    T** operator&()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    void Reset()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
};
}
namespace EA {
namespace ResourceMan {
struct Key_s0051_69d0 {
    uint32_t mnInstanceID;
    uint32_t mnTypeID;
    uint32_t mnGroupID;
    Key_s0051_69d0(uint32_t instance, uint32_t type, uint32_t group) : mnInstanceID(instance), mnTypeID(type), mnGroupID(group) {}
};
}
}
namespace EA {
namespace ResourceMan {
struct IResource {
    virtual int AddRef();
    virtual int Release();
};
}
}
namespace EA {
namespace ResourceMan {
struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual bool GetResource(const Key_s0051_69d0& key, IResource** ppResource);   // +0x14
};
}
}
namespace EA {
namespace ResourceMan {
IResourceManager* GetManager();     // 0x0067dcd0
}
}
namespace SP {
class cStaticBuffer_s0051_69d0 {
public:
    virtual ~cStaticBuffer_s0051_69d0();
    virtual int AddRef();
    virtual int Release();
    int GetVertexBuffer(int nVertices, void** ppVertices, int* pStride);   // 0x007a47c0
    void Unlock();                                                         // 0x007a4650
    void Flush();                                                          // 0x007a4710
};
}
namespace SP {
class cStaticBufferDraw {
public:
    cStaticBuffer_s0051_69d0* mpBuffer;
    static cStaticBufferDraw* spInstance;                                  // 0x015ddc84 (EA::SingletonBase)
    void Begin(uint32_t material, int primitive, int a, int b);            // 0x007a4420
    void Draw(void* pContext, uint32_t material);                          // 0x007a3e60
    int GetVertexBuffer(int nVertices, void** ppVertices, int* pStride) { return mpBuffer->GetVertexBuffer(nVertices, ppVertices, pStride); }
    void Unlock() { mpBuffer->Unlock(); }
    void End(cStaticBuffer_s0051_69d0** ppBuffer)
    {
        mpBuffer->Flush();
        *ppBuffer = mpBuffer;
        mpBuffer = 0;
    }
};
}
namespace SP {
struct cMaterial_s0051_69d0 { uint32_t pad; uint32_t mID; };
}
namespace SP {
class cMaterialManager_s0051_69d0 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual cMaterial_s0051_69d0* GetMaterial(uint32_t id);   // +0x28 0x00712c20
};
}
namespace SP {
cMaterialManager_s0051_69d0* MaterialManager();               // 0x0067dd70
}
namespace SP {
class cIDynamicDraw_s0051_69d0 {
public:
    cIDynamicDraw_s0051_69d0() {}
    virtual void Dispatch(uint32_t a, uint32_t b, void* pContext) = 0;
    virtual bool GetBoundingBox(BoundingBox& box, float& radius) = 0;
};
}
namespace SP {
class cDynamicDrawBase_s0051_69d0 : public cIDynamicDraw_s0051_69d0 {
public:
    cDynamicDrawBase_s0051_69d0() {}
    virtual void Dispatch(uint32_t a, uint32_t b, void* pContext);
};
}
namespace SP {
class cDynamicDrawBaseRC_s0051_69d0 : public cDynamicDrawBase_s0051_69d0, public EA::RefCountTemplate_s0051_69d0<int> {
public:
    cDynamicDrawBaseRC_s0051_69d0() {}
    virtual void Dispatch(uint32_t a, uint32_t b, void* pContext);
};
}
template <typename T> struct SimpleVector {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator[2];
    bool empty() const;            // 0x00526430 (folded)
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct MeshData {
    uint32_t pad0[2];
    SimpleVector<float> mPositions;        // +0x08 (Vector3)
    SimpleVector<float> mNormals;          // +0x1c (Vector3)
    SimpleVector<float> mUVs;              // +0x30 (Vector2)
    SimpleVector<float> mColors;           // +0x44
    SimpleVector<int> mPositionIndices;    // +0x58
    SimpleVector<int> mNormalIndices;      // +0x6c
    SimpleVector<int> mUVIndices;          // +0x80
    SimpleVector<int> mOpposite;           // +0x94
};
struct SkinnerModel {
    char pad[0x10];
    MeshData* mpMesh;                     // +0x10
};
struct SkinnerContext {
    char pad[0xc];
    SkinnerModel* mpModel;                // +0x0c
    MeshData* mpMesh;                     // +0x10
    SkinnerModel* GetModel() const { SkinnerModel* p = mpModel; return p; }
    MeshData* GetMesh() const { MeshData* p = mpMesh; return p; }
};
SkinnerContext* GetSkinnerContext();      // 0x00401080
inline SkinnerContext* SkinnerCtx() { return GetSkinnerContext(); }
void SetupResource(void* self, uint32_t instance, uint32_t group);   // 0x007544e0
void ReleaseResourceData(EA::ResourceMan::IResource* p);             // 0x006ad050
namespace nSPSkinner {
class cMeshAORender_s0051_69d0 : public SP::cDynamicDrawBaseRC_s0051_69d0 {
public:
    cMeshAORender_s0051_69d0();
    ~cMeshAORender_s0051_69d0();
    virtual void Dispatch(uint32_t a, uint32_t b, void* pContext);
    virtual bool GetBoundingBox(BoundingBox& box, float& radius);
    void Load(uint32_t instance, uint32_t group);
    void Unload();
    void Rebuild();  // 0x00516eb0 (nSPSkinner::cMeshAORender::Rebuild)

    EA::AutoRefCount_s0051_69d0<SP::cStaticBuffer_s0051_69d0> mStaticBuffer;          // +0x0c
    EA::AutoRefCount_s0051_69d0<EA::ResourceMan::IResource> mResource;     // +0x10
};
}
namespace nSPSkinner {
struct Vector3f { float x, y, z; };
}
namespace nSPSkinner {
struct Vector2f { float x, y; };
}
struct JobDesc {
    int mPriority;          // +0x00
    int m04;
    bool mb08;
    uint32_t m0c[8];
    JobDesc();
};
class cJobBase;
class IJobManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void v64(); virtual void v68(); virtual void v6c(); virtual void v70();
    virtual void AddJob(cJobBase* pJob, int flags, JobDesc* pDesc);    // +0x74
};
IJobManager* JobManager();        // 0x0067dd50
class IAppSystem {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40();
    virtual bool IsMultiCore();   // +0x44
};
IAppSystem* AppSystem();          // 0x0067dd00
namespace EA {
struct AtomicInt32 {
    volatile long mValue;
    AtomicInt32(long v) { SetValue(v); }
    void SetValue(long v) { _InterlockedExchange(&mValue, v); }
};
}
namespace EA {
class AtomicRefCount {
public:
    AtomicRefCount() : mRefCount(0) {}
    virtual ~AtomicRefCount() {}
    virtual int AddRef();
    virtual int Release();
    AtomicInt32 mRefCount;
};
}
class IJob {
public:
    IJob() {}
    virtual void Run(int a, int b, int c, int d) = 0;
};
class IJob2 : public IJob {
public:
    IJob2() {}
    virtual void Run(int a, int b, int c, int d);
};
class cJobBase : public IJob2, public EA::AtomicRefCount {
public:
    cJobBase();
    virtual void Run(int a, int b, int c, int d);
    virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual bool Step();           // +0x14
    void Schedule();
    bool mbDone;                   // +0x0c
};
// ---- items of slice s005169d0 end

// ---- items of slice s00517430 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_softStateUpdated;                     // 016f9110
#pragma intrinsic(_InterlockedExchangeAdd)
struct Raster;
struct cTextureInstance {
    Raster* mRaster;
    unsigned char mFlags;
    unsigned char pad5[3];
    volatile long mRefCount;
};
struct ResMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual cTextureInstance* Get(unsigned key, int a, int b);      // +0x20
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void Load(cTextureInstance* t);                          // +0x34
};
ResMgr* GetResMgr();                                // 0067dd60
void __fastcall AtomicRefCounted_Release(cTextureInstance* t);      // 00402420 (thiscall)
struct VertexDescriptor {};
struct VBDesc { char pad[0xf]; unsigned char stride; };    // [vb->+0]->+0xf = vertex stride
struct VertexBuffer {
    VBDesc* desc;                                   // +0
    void* d3dvb;                                    // +4
    unsigned count;                                 // +8 (vertices already consumed / offset)
    unsigned capacity;                              // +0xc
    void* Lock(int flags, int offsetBytes, int sizeBytes);     // 011f3620
    void Unlock();                                  // 011f36a0
};
struct IDevice;
struct IDeviceVtbl {
    void* pad0[81];
    long (__stdcall* DrawPrimitive)(IDevice*, int type, unsigned start, unsigned primCount);   // +0x144
    void* pad1[18];
    long (__stdcall* SetStreamSource)(IDevice*, unsigned stream, void* vb, unsigned off, unsigned stride); // +0x190
};
struct IDevice { const IDeviceVtbl* vtbl; };
struct StreamSlot { void* vb; unsigned off; unsigned stride; };
struct ShaderObj { char pad[0x14]; void (__cdecl* fn14)(int); };
extern const VertexDescriptor* g_vertexDescriptor;      // 016f65a0
extern IDevice* g_d3d9Device;                           // 016f89d0
extern StreamSlot g_streams[];                          // 016f9138
extern ShaderObj* g_shader;                             // 016f6568
int  __cdecl VertexDescriptor_AreEqual(const VertexDescriptor* a, const VertexDescriptor* b);   // 011f2e70
void __fastcall ApplyVertexDescriptor(const VertexDescriptor* vd);                              // 011f2bc0 (thiscall)
void __cdecl D3D9Sync();                                // 011f21a0
struct CompiledState { void Dispatch(); };              // 011ee580
struct Vec4 {
    float x, y, z, w;
    Vec4(float a, float b, float c, float d) { x = a; y = b; z = c; w = d; }
};
struct cRTTBuffer_s0051_7430 {
    void* mCamera;                                  // +0
    unsigned material;                              // +4
    unsigned writemask;                             // +8
    Vec4 params[3];                                 // +0xc
    Raster* textures[2];                            // +0x3c
    int maxparam;                                   // +0x44
    int maxtexture;                                 // +0x48
    unsigned vtxcount;                              // +0x4c
    char pad50[0x14];
    void Begin();                                   // 00528e90
    void SetWriteMask(int a, int b, int c, int d);  // 00529280 (StateBits::Set)
    CompiledState* PrepareState();                  // 005293a0 0x005293a0
    void BeginDraw();                               // 00529bf0 0x00529bf0
    void SetParam(int i, const Vec4& v)
    {
        if (maxparam <= i)
            maxparam = i + 1;
        params[i] = v;
    }
    void SetTexture(int i, Raster* r)
    {
        if (r != 0 && maxtexture <= i)
            maxtexture = i + 1;
        textures[i] = r;
    }
};
struct RenderState {
    char pad0[0x10];
    cRTTBuffer_s0051_7430* rttA;                               // +0x10
    cRTTBuffer_s0051_7430* rttB;                               // +0x14
    char pad18[0x1c];
    const VertexDescriptor* vdesc;                  // +0x34
    VertexBuffer* vb;                               // +0x38
};
struct RenderMgr {                                  // FUN_00401080 result
    char pad0[0xc];
    RenderState* state;                             // +0xc
};
RenderMgr* GetRenderMgr();                          // 00401080
namespace nSPSkinner {
struct cPaintBatch {                                // cPaintList::Batch, size 0x18
    int mFirstVertex;                               // +0
    int mVertices;                                  // +4
    unsigned char mBlendModes[3];                   // +8
    unsigned char mIdentityPass;                    // +0xb
    cTextureInstance* mBrush[3];                    // +0xc
};
}
namespace nSPSkinner {
struct BatchVec {                                   // eastl::vector<Batch> payload at list+0x14
    cPaintBatch* mpBegin;
    cPaintBatch* mpEnd;
    cPaintBatch* begin() { return mpBegin; }
    int size() const { return (int)(mpEnd - mpBegin); }
};
}
namespace nSPSkinner {
struct cPaintList_s0051_7430 {
    char* mVerticesBegin;                           // +0 (28-byte vertices)
    char pad4[0x10];
    BatchVec mBatches;                              // +0x14
};
}
namespace nSPSkinner {
static inline Raster* ResolveRaster(cTextureInstance* t)
{
    if (!(t->mFlags & 1))
        GetResMgr()->Load(t);
    return t->mRaster;
}
}
namespace nSPSkinner {
class cPaintRenderJob_s0051_7430 {
public:
    char padBase[0x10];
    cPaintList_s0051_7430* mPaintList;                         // +0x10
    int mStage;                                     // +0x14
    int mVBStart;                                   // +0x18
    int mVBCount;                                   // +0x1c
    int mVBBatches;                                 // +0x20
    int mBatchIdx;                                  // +0x24
    int mLockFailCount;                             // +0x28
    bool mSkipIdentity;                             // +0x2c
    bool RenderInternal();                          // 0x00517430
};
}
// ---- items of slice s00517430 end

// ---- items of slice s005182f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kOne;                               // 0x01485720
extern const float kZero;                              // 0x01485378
extern const float kConst6110;                         // 0x01486110
extern const float kConstB95C;                         // 0x013eb95c
void* SP_AppSystem();                                  // 0x0067dd00
void* GetSingleton();                                  // 0x00401080
float GetFloatProperty(uint32_t prop);                 // 0x006a2710
class cRTTBuffer_s0051_82f0 {
public:
    uint32_t pad0;           // 0x00
    uint32_t material;       // 0x04
    uint32_t pad1;           // 0x08
    float params[12];        // 0x0c: three 16-byte parameter vectors
    uint32_t textures[2];    // 0x3c
    int maxparam;            // 0x44
    int maxtexture;          // 0x48
    uint8_t pad2[0x58 - 0x4c];
    int width;               // 0x58
    int height;              // 0x5c
    uint32_t texture;        // 0x60

    void Setup();                                          // 0x00528e90
    void Set(int a, int b, int c, int d);                  // 0x00529280
    int Reserve(int n);                                    // 0x00529520
    void Tri(float* a, float* b, float* c, uint32_t col);  // 0x005295b0
    void Flush();                                          // 0x00529690
    void vertex(float* a, float* b, int flags);            // 0x005296b0
    void BeginDraw();                                      // 0x00529bf0
    void SwapWith(cRTTBuffer_s0051_82f0* o);                          // 0x00518b00
};
namespace nSPSkinner {
class cPaintRenderJob_s0051_82f0 {
public:
    uint8_t pad0[0x14];
    int mStage;   // 0x14
    bool RenderInternal();   // 0x00517430
    bool Render();           // 0x005182f0
};
}
namespace nSPSkinner {
class cFieldSwap {
public:
    uint32_t f0;                 // 0x00
    uint8_t pad1[0x50 - 0x04];
    uint32_t f50, f54;           // 0x50, 0x54
    uint32_t f58, f5c, f60;      // 0x58, 0x5c, 0x60

    void SwapWith(cFieldSwap* o);   // 0x00518b00
};
}
namespace nSPSkinner {
template <class T> inline void swapv(T& a, T& b) { T t = a; a = b; b = t; }
}
namespace nSPSkinner {
class cPaintCopyIdentityJob_s0051_82f0 {
public:
    bool Render();   // 0x00518bf0
};
}
namespace nSPSkinner {
class cPaintDifferentiateJob_s0051_82f0 {
public:
    bool Render();   // 0x00518cf0
};
}
namespace nSPSkinner {
struct cDilateMesh {
    uint8_t pad0[0x30];
    float* verts;             // 0x30 (8 bytes per vertex)
    uint8_t pad1[0x58 - 0x34];
    uint32_t* idxBegin;       // 0x58
    uint32_t* idxEnd;         // 0x5c
    uint8_t pad2[0x80 - 0x60];
    uint32_t* indices;        // 0x80
};
}
namespace nSPSkinner {
struct cDilateVec { char* begin; char* end; };
}
namespace nSPSkinner {
struct cDilateModel { uint8_t pad[0x98]; cDilateVec parts; };   // 0x98
}
namespace nSPSkinner {
struct cDilateObj { uint8_t pad[8]; cDilateModel* model; };
}
namespace nSPSkinner {
struct cDilateSingleton {
    uint8_t pad0[0xc];
    char* table;              // 0xc
    cDilateMesh* mesh;        // 0x10
    uint8_t pad1[0x20 - 0x14];
    cDilateObj* obj;          // 0x20
};
}
namespace nSPSkinner {
inline const int& MinRef(const int& a, const int& b) { return (a < b) ? a : b; }
}
namespace nSPSkinner {
class cPaintDilateJob_s0051_82f0 {
public:
    uint8_t pad0[0x10];
    int mComponent;   // 0x10
    int mPasses;      // 0x14
    int mStage;       // 0x18
    bool Render();   // 0x005183c0
};
}
// ---- items of slice s005182f0 end

// ---- items of slice s00518f10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_1485720;    // 0x01485720
extern float g_1485378;    // 0x01485378
void* GetPaintSystem();                                        // 0x00401080
int   FUN_0041d870(void* state);                               // 0x0041d870
int   InitVerbCollection(void* p);                             // 0x004bb860
void* SP_PropertyManager();                                    // 0x0067de30
void  GetFloatProperty(void* obj, uint32_t key, float* out);   // 0x0040cf10
void  RTTBuffer_Begin(void* self);                             // 0x00528e90
void  RTTBuffer_SetParams(void* self, int a, int b, int c, int d);   // 0x00529280
void* GetTextureHandle(void* self);                            // 0x00525aa0
void  RTTBuffer_Draw(void* self, uint32_t color, float* a, float* b); // 0x005296b0
void  RTTBuffer_BeginDraw(void* self);                         // 0x00529bf0
namespace nSPSkinner {
struct cRTTBuffer_s0051_8f10 {                 // size 0x64
    uint32_t mCamera;               // +0x00
    uint32_t material;              // +0x04
    uint32_t writemask;             // +0x08
    float    params[12];            // +0x0c  (cSPVector4 params[3])
    void*    textures[2];           // +0x3c
    int      maxparam;              // +0x44
    int      maxtexture;            // +0x48
    uint32_t vtxcount;              // +0x4c
    uint32_t pad50;                 // +0x50
    uint32_t mWidth;                // +0x58
    uint32_t mHeight;               // +0x5c
    void*    mTexture;              // +0x60
};
}
namespace nSPSkinner {
struct cPaintAmbOccJob_s0051_8f10 {
    virtual bool Render();          // +0x00
};
}
struct ResultObj {
    uint32_t pad00[0x39];
    void**   mE4begin;              // +0xe4
    void**   mE4end;                // +0xe8
};
struct RigBlock {                   // 0x8c bytes
    uint32_t pad00[2];
    uint16_t mFlags;                // +0x08
    uint16_t pad0a;
    uint8_t  pad0c[0x80];
};
struct ModelObj {
    uint8_t  pad00[0x18];
    void*    mEditorModel;          // +0x18
    uint8_t  pad1c[0x7c];           // to 0x98
    RigBlock* mBlocksBegin;         // +0x98
    RigBlock* mBlocksEnd;           // +0x9c
};
struct SkinObj {                    // SP::cSkinObject
    uint32_t pad00[2];
    ModelObj* mpModel;              // +0x08
    void**    mBlockProps;          // +0x0c
};
struct AOVert {
    uint32_t pad00[0x16];
    float x0;                       // +0x58
    float x1;                       // +0x5c
    float y0;                       // +0x60
    float y1;                       // +0x64
};
struct PropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetProperty(int key, float def, void* it);   // +0x2c
};
struct PropIterator {
    virtual void v0();
    virtual void Release();         // +0x04
};
inline int RoundToInt(float f) { return (int)(f + 0.5f); }
// ---- items of slice s00518f10 end

// ---- items of slice s00519640 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* _sAppProperties;                             // 0x015df0f0 vicinity
int   GetPaintSystem_s0051_9640();                                   // 0x00401080
void  RTTBuffer_Draw(void* self, void* a, void* b, uint32_t color); // 0x005296b0
void  Vector3_CopyCtor(void* dst, const void* src);       // 0x004098a0
void* FUN_00446ff0();                                     // 0x00446ff0
void* FUN_006bb640();                                     // 0x006bb640
void* FUN_0067dd60();                                     // 0x0067dd60
struct DirectPropertyList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9();
    virtual float GetFloatProperty(unsigned key);          // +0x28
};
struct SplatObj {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool Has(int key);                             // +0x1c
    virtual void v8(); virtual void v9();
    virtual void* GetByKey(int key);                       // +0x28
};
struct TexFactory {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void* Create(const void* p, int a, int b, int type);  // +0x1c
    virtual void v8();
    virtual bool Valid(const void* p, int a, int b);        // +0x24
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void Release(void* p);                          // +0x34
};
namespace nSPSkinner {
struct cRTTBuffer_s0051_9640 {                 // size 0x64
    uint32_t mCamera;               // +0x00
    uint32_t material;              // +0x04
    uint32_t writemask;             // +0x08
    float    params[12];            // +0x0c  (cSPVector4 params[3])
    void*    textures[2];           // +0x3c
    int      maxparam;              // +0x44
    int      maxtexture;            // +0x48
    uint32_t vtxcount;              // +0x4c
    uint32_t pad50;                 // +0x50
    uint32_t mWidth;                // +0x58
    uint32_t mHeight;               // +0x5c
    void*    mTexture;              // +0x60
};
}
namespace nSPSkinner {
struct cPaintSplatJob_s0051_9640 {             // size 0x18
    uint32_t pad00[3];
    bool     mComplete;             // +0x0c
    uint8_t  pad0d[3];
    int      mStage;                // +0x10
    int      mBlock;                // +0x14
    virtual bool Render();  // 0x00519640 (nSPSkinner::cPaintSplatJob::Render)
};
}
// ---- items of slice s00519640 end

// ---- items of slice s0051a350 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_splatVtblDerived;
extern void* g_splatVtblBase;
int   GetPaintSystem_s0051_a350();                                              // 0x00401080
void  FUN_004c6ae0(void* dst, char* a, int n, char* b);              // 0x004c6ae0
void  FUN_00552750();                                                // 0x00552750
void  FUN_0051d1e0(void* p);                                         // 0x0051d1e0
void  FUN_0051d140();                                                // 0x0051d140
void  FUN_00402420();                                                // 0x00402420
struct SubObj { void FUN_0051d0d0(); };
void  FUN_0051d180(void* p);                                         // 0x0051d180
void  FUN_004259e0(void* a, void* b);                                // 0x004259e0
void  SP_cJob_GetStatus(void* job);                                  // 0x00690120
char  SP_GetPropertyAsKey(void* prop, int key, void* out);
struct Factory {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual void* Create(int a, int b, int c, int type);           // +0x1c
    virtual void* v8(int key, int a, int b);                       // +0x20
    virtual bool  Valid(void* p, int a, int b);                    // +0x24
virtual void v10();
virtual void v11();
virtual void v12();
    virtual void  Release(void* p);                                // +0x34
virtual void v14();
virtual void v15();
    virtual void* CreateBuf(int a, int b, int c, int d, int e, int f); // +0x40
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
    virtual void v21();
    virtual int   Make(void* a, int b, int c);                     // +0x58
};
namespace nSPSkinner {
struct cRTTBuffer_s0051_a350 {                 // size 0x64
    uint32_t mCamera; uint32_t material; uint32_t writemask;
    float    params[12];
    void*    textures[2];
    int      maxparam;
    int      maxtexture;
    uint32_t vtxcount; uint32_t pad50;
    uint32_t mWidth; uint32_t mHeight; void* mTexture;
};
}
namespace nSPSkinner {
struct cPaintSplatAlphaJob_s0051_a350 {        // size 0x18
    uint32_t pad00[3];
    bool     mComplete;
    uint8_t  pad0d[3];
    int      mStage;                // +0x10
    int      mBlock;                // +0x14
    virtual bool Render();  // 0x0051a350 (nSPSkinner::cPaintSplatAlphaJob::Render)
};
}
struct RefSlot {                          // reference slot at SkinJob+0x8
    void* mpFirst;                        // +0x0
    void* mpSecond;                       // +0x4
    void  CopyFrom(void* first, void* second);   // 0x004259e0 (thiscall)
    void  Push(void* value);              // 0x0051d1e0 (thiscall)
};
struct HashIter {                         // eastl hashtable iterator (8 bytes)
    void* mpNode;                         // +0x0
    void* mpBucket;                       // +0x4
    void  Increment();                    // 0x0051d140 (thiscall)
    void  IncrementBucket();              // 0x00552750 (thiscall)
};
struct SkinJob {
    void* FUN_0051a8a0();
    void  FUN_0051a930();
    void  FUN_0051a9a0(int a2, char a3, char a4, int a5, int a6, int a7, int a8,
                       char a9, char a10, char a11);
    void  FUN_0051aaa0();
    void  FUN_0051ab50(char deep);
};
struct ImgObj {                          // refcounted image (vtable slot 1 = Release)
    virtual void v0();
    virtual void Release();
    char pad04[0x1c - 4];
    int  mW;                             // +0x1c
    int  mH;                             // +0x20
    char pad24[4];
    char* mpPixels;                      // +0x28 (4 bytes per pixel, channel at +1)
};
template<class T> struct ARCRef {        // AutoRefCount with virtual Release in slot 1
    T* p;
    ARCRef() : p(0) {}
    ~ARCRef() { if (p) p->Release(); }
    void** AsPPVoidParam();              // 0x0041d870
};
struct RasterObj {
    void SetMipLevelData(void* data, int level);   // 0x011f0270
};
struct TexObj {                          // atomic refcounted texture: Raster* at +0, flags +4, count +8
    RasterObj* mpRaster;
    uint32_t mFlags;
    volatile long mnRefCount;
    int Release();                       // 0x00402420 (AtomicRefCounted::Release)
};
struct TexRefAuto {
    TexObj* p;
    TexRefAuto() : p(0) {}
    ~TexRefAuto() { if (p) p->Release(); }
};
struct ByteBuf {                         // 3-pointer byte vector
    char* mpBegin; char* mpEnd; char* mpCap;
    ByteBuf(int n, char* tag);           // 0x00423be0
    ~ByteBuf();                          // 0x0041e5d0
};
struct Svc40 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
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
virtual void v20();
virtual void v21();
    virtual void* Make(void** pp, int a, int b); };               // +0x58 on the 0x0067dd40 object
struct Svc60 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
    virtual void ReleaseTex(TexObj* t);                            // +0x34
virtual void v14();
virtual void v15();
    virtual TexObj* CreateBuf(int w, int h, int a, int b, int c, int d);   // +0x40
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
    virtual void Make(void* r); };                                 // +0x58 on the 0x0067dd60 object
Svc40* FUN_0067dd40_t();                 // 0x0067dd40
Svc60* FUN_0067dd60_t();                 // 0x0067dd60
// ---- items of slice s0051a350 end

// ---- items of slice s0051afd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
namespace Skinner {
struct cPaintSystem {
    uint32_t pad[0x7c / 4];
    bool mbField7C;                       // +0x7c
    bool IsField7C() { return mbField7C; }
};
}
namespace Skinner {
cPaintSystem* GetPaintSystem_s0051_afd0();           // 0x00401080
}
namespace Skinner {
struct Texture {
    uint32_t vt;
    uint8_t mFlags;                       // +0x04, bit 0: loaded
    uint8_t GetFlags() { return mFlags; }
};
}
namespace Skinner {
struct TexturePtr {
    Texture* mpObject;
    Texture* get() const { return mpObject; }
    Texture* operator->() const { return mpObject; }
};
}
namespace Skinner {
struct TextureVector {                    // eastl::fixed_vector<TexturePtr, 192>
    TexturePtr* mpBegin;
    TexturePtr* mpEnd;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    TexturePtr& operator[](uint32_t n) { return mpBegin[n]; }
};
}
namespace Skinner {
struct ILayer {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual void v2() = 0;
    virtual void v3() = 0;
    virtual void Initialize() = 0;        // +0x10
    virtual bool Execute() = 0;
};
}
namespace Skinner {
struct IRefAtomic {
    virtual void r0();
    int mnRefCount;
};
}
namespace Skinner {
class cSkinPainterJob : public ILayer, public IRefAtomic {
public:
    cSkinPainterJob();                    // 0x005173a0
    bool mHasFinished;                    // +0x0c
};
}
namespace Skinner {
class cSkinPainterJobApplyBrushes : public cSkinPainterJob {
public:
    cSkinPainterJobApplyBrushes(int a, bool b);   // 0x00517310
    int AddRef(); int Release(); void v2(); void v3(); void Initialize(); bool Execute();
    int field_10, field_14, field_18, field_1C, field_20, field_24, field_28;
    bool field_2C;
};
}
namespace Skinner {
class cSkinPainterJobPaintParts : public cSkinPainterJob {
public:
    cSkinPainterJobPaintParts() : mStage(0), mRigblockIndex(0) {}
    int AddRef(); int Release(); void v2(); void v3(); void Initialize(); bool Execute();
    int mStage;
    int mRigblockIndex;
};
}
namespace Skinner {
class cSkinPainterJobAmbientOcclusion : public cSkinPainterJob {
public:
    cSkinPainterJobAmbientOcclusion() {}
    int AddRef(); int Release(); void v2(); void v3(); void Initialize(); bool Execute();
};
}
namespace Skinner {
class cSkinPainterJobColorDilateRepeat : public cSkinPainterJob {
public:
    cSkinPainterJobColorDilateRepeat(int a) : field_10(a), mNumSteps(8), field_18(0) {}
    int AddRef(); int Release(); void v2(); void v3(); void Initialize(); bool Execute();
    int field_10;
    int mNumSteps;
    int field_18;
};
}
namespace Skinner {
class cSkinPainterJobCopyTex1AlphaToTex0 : public cSkinPainterJob {
public:
    cSkinPainterJobCopyTex1AlphaToTex0() {}
    int AddRef(); int Release(); void v2(); void v3(); void Initialize(); bool Execute();
};
}
namespace Skinner {
class cSkinPainterJobCopyRigblocksTintMaskAlpha : public cSkinPainterJob {
public:
    cSkinPainterJobCopyRigblocksTintMaskAlpha() : mRigblockIndex(0) {}
    int AddRef(); int Release(); void v2(); void v3(); void Initialize(); bool Execute();
    int mRigblockIndex;
};
}
namespace Skinner {
class cSkinPainterJobBumpToNormal : public cSkinPainterJob {
public:
    cSkinPainterJobBumpToNormal() {}
    int AddRef(); int Release(); void v2(); void v3(); void Initialize(); bool Execute();
};
}
namespace Skinner {
struct IUnmanagedMessageListener { virtual void m0(); };
}
namespace Skinner {
struct IMessageRC { virtual void n0(); };
}
namespace Skinner {
class cSkinPainterJobExtractTexture : public IUnmanagedMessageListener, public IMessageRC, public cSkinPainterJob {
public:
    // 0x0051c470 (nonmatching in slice s0051c470). The real ctor is defined inline in the header but
    // cl /Ob1 declines to inline it; its reserved frame leaves a 6-dword hole in this caller's /Od frame
    // (blocks 11 and 13). This stand-in body only reproduces that frame; the real body lives at 0x51c470.
    cSkinPainterJobExtractTexture(int mode, uint32_t instanceID, uint32_t groupID, bool b1, int n,
                                  bool b2, bool b3)
        : mInstanceID(instanceID), mGroupID(groupID), field_20(0), field_24(n), field_28(b2),
          field_29(b3), field_2A(b1), field_2C(0), field_30(0)
    {
        uint32_t frame[6];
        frame[0] = mode;
    }
    uint32_t mInstanceID;                 // +0x18
    uint32_t mGroupID;                    // +0x1c
    void* field_20;                       // +0x20 RenderWare::Raster*
    int field_24;                         // +0x24
    bool field_28, field_29, field_2A;    // +0x28
    int field_2C;                         // +0x2c
    int field_30;                         // +0x30
    uint32_t mMessageListenerData[(0x48 - 0x34) / 4];
    int AddRef(); int Release(); void v2(); void v3(); void Initialize(); bool Execute();
};
}
namespace Skinner {
template <class T>
struct intrusive_ptr {
    T* mpObject;
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    intrusive_ptr& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
}
namespace Skinner {
class cSkinPainterPipeline {
public:
    void ExecutePipeline();

    uint32_t vt;                                     // +0x000
    int mnRefCount;                                  // +0x004
    TextureVector mTextures;                         // +0x008 fixed_vector<TexturePtr, 192>
    uint32_t mTexturesRest[(0x320 - 0x10) / 4];
    uint32_t mTextureInstanceID;                     // +0x320
    uint32_t mTextureGroupID;                        // +0x324
    uint32_t field_328;                              // +0x328
    int field_32C;                                   // +0x32c
    intrusive_ptr<cSkinPainterJob> mpCurrentJob;     // +0x330
    int field_334;                                   // +0x334
    int field_338;                                   // +0x338
    int mCurrentStage;                               // +0x33c
    int field_340;                                   // +0x340
    int field_344;                                   // +0x344
    bool field_348;                                  // +0x348
    bool field_349;
    bool field_34A;
    bool field_34B;
    bool field_34C;
    bool field_34D;
    bool field_34E;
};
}
namespace Skinner {
#define RUN_JOB(NEWJOB)                                         \
    do {                                                        \
        if (mpCurrentJob.get() == 0) {                          \
            mpCurrentJob = NEWJOB;                              \
            mpCurrentJob->Initialize();                         \
        }                                                       \
        if (mpCurrentJob->mHasFinished) {                       \
            mpCurrentJob = 0;                                   \
        } else {                                                \
            return;                                             \
        }                                                       \
    } while (0)
}
// ---- items of slice s0051afd0 end

// ---- items of slice s0051c470 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_vtblSkinnerPaintSystem;   // 0x013eb394
extern void* g_vtblLocaleChange;         // 0x013eb918
extern void* g_vtblSimCreatureAbility;   // 0x013ef094
extern void* g_vtblEditorResource;       // 0x013eb938
extern void* g_vtblPaintA;               // 0x013f1b80
extern void* g_vtblPaintB;               // 0x013f1b74
extern void* g_vtblPaintC;               // 0x013f1b5c
extern void* g_vtblPaintD;               // 0x013f1b58
extern "C" void* SP_MessageServer();                              // 0x0067dcc0
int   GetPaintSystem_s0051_c470();                                   // 0x00401080
void* EA_alloc(unsigned size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void* BakeSprites_ctor(void* p);                          // 0x007b00f0
void  EASTL_allocator_deallocate(void* p);                // 0x00f47380
struct RefCounted {
    uint32_t mvtbl; uint32_t pad04; uint32_t pad08;
    volatile long mnRefCount;              // +0x0c
    int AddRef();
};
struct BaseEditor { void dtor(); };
struct PaintSystem {
    PaintSystem(int kind, void* a, void* b, char c, void* d, char e, char f);
    void dtor();
};
struct EditorResource { void* deleting_dtor(unsigned flags); };
struct ServiceObj {                    // FUN_0067dd60 result
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
    virtual void v20();
    virtual void SetTexture(void* tex, int a);                       // +0x54
    virtual void SetInstance(int inst, int a, int b, int c);         // +0x58
};
struct Connector { void Init(void* server, void* owner, void* id, int n); };   // 0x004db620
ServiceObj* FUN_0067dd60_s0051_c470();                                       // 0x0067dd60
struct SkinTexExtractorB {
    char pad00[0xc];
    char mFlag;                        // +0x0c
    char pad0d[0x18 - 0x0d];
    int  mInstance;                    // +0x18
    char pad1c[0x2c - 0x1c];
    Connector mConn;                   // +0x2c
    void Init();
};
// ---- items of slice s0051c470 end

// @ 0x00425a80
void RefPtrVec::DoInsertValue(RefPtr* position, const RefPtr& value)
{
    if (mpEnd != mpCapacity) {
        const RefPtr* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) RefPtr(*(mpEnd - 1));
        copy_backward_ref(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        RefPtr* const pNewData = DoAllocate(nNewSize);
        RefPtr* pNewEnd = uninitialized_copy_ref(mpBegin, position, pNewData);
        ::new(pNewEnd) RefPtr(value);
        ++pNewEnd;
        pNewEnd = uninitialized_copy_ref(position, mpEnd, pNewEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00516ac0
void FastMemCopy(void* dst, const void* src, unsigned int n)
{
    if (((uint32_t)dst | (uint32_t)src) & 7) {
        memcpy(dst, src, n);
        return;
    }
    __asm {
        mov     edx, n
        mov     esi, src
        mov     edi, dst
        mov     ecx, edx
        and     ecx, 0xffffe000
        jz      tail
        shr     ecx, 3
        lea     esi, [esi + ecx*8]
        lea     edi, [edi + ecx*8]
        neg     ecx
    blockloop:
        mov     eax, 0x40
        add     ecx, 0x400
    prefetchloop:
        mov     ebx, [esi + ecx*8 - 0x40]
        mov     ebx, [esi + ecx*8 - 0x80]
        sub     ecx, 0x10
        dec     eax
        jnz     prefetchloop
        mov     eax, 0x80
    copyloop:
        movq    mm0, [esi + ecx*8]
        movq    mm1, [esi + ecx*8 + 8]
        movq    mm2, [esi + ecx*8 + 0x10]
        movq    mm3, [esi + ecx*8 + 0x18]
        movq    mm4, [esi + ecx*8 + 0x20]
        movq    mm5, [esi + ecx*8 + 0x28]
        movq    mm6, [esi + ecx*8 + 0x30]
        movq    mm7, [esi + ecx*8 + 0x38]
        movntq  [edi + ecx*8], mm0
        movntq  [edi + ecx*8 + 8], mm1
        movntq  [edi + ecx*8 + 0x10], mm2
        movntq  [edi + ecx*8 + 0x18], mm3
        movntq  [edi + ecx*8 + 0x20], mm4
        movntq  [edi + ecx*8 + 0x28], mm5
        movntq  [edi + ecx*8 + 0x30], mm6
        movntq  [edi + ecx*8 + 0x38], mm7
        add     ecx, 8
        dec     eax
        jnz     copyloop
        or      ecx, ecx
        jnz     blockloop
        emms
    tail:
        mov     ecx, edx
        and     ecx, 0x1ffc
        shr     ecx, 2
        rep     movsd
        mov     ecx, edx
        and     ecx, 3
        rep     movsb
        sfence
    }
}

// @ 0x00516ba0
namespace nSPSkinner {
cMeshAORender_s0051_69d0::cMeshAORender_s0051_69d0()
{}
}  // namespace nSPSkinner

// @ 0x00516c30
namespace nSPSkinner {
cMeshAORender_s0051_69d0::~cMeshAORender_s0051_69d0()
{}
}  // namespace nSPSkinner

// @ 0x00516ca0
namespace nSPSkinner {
void cMeshAORender_s0051_69d0::Load(uint32_t instance, uint32_t group)
{
    SetupResource(this, instance, group);
    EA::ResourceMan::Key_s0051_69d0 key(instance, 0xe6bce5, group);
    EA::ResourceMan::GetManager()->GetResource(key, &mResource);
}
}  // namespace nSPSkinner

// @ 0x00516d30
namespace nSPSkinner {
void cMeshAORender_s0051_69d0::Unload()
{
    ReleaseResourceData(mResource.get());
    mResource = 0;
}
}  // namespace nSPSkinner

// @ 0x00516da0
namespace nSPSkinner {
void cMeshAORender_s0051_69d0::Dispatch(uint32_t a, uint32_t b, void* pContext)
{
    if (!mStaticBuffer.get())
        return;
    SP::cMaterial_s0051_69d0* pMaterial = SP::MaterialManager()->GetMaterial(0x320adfd3);
    if (!pMaterial)
        return;
    ((SP::cStaticBufferDraw*)mStaticBuffer.operator->())->Draw(pContext, pMaterial->mID);
}
}  // namespace nSPSkinner

// @ 0x00516e10
namespace nSPSkinner {
bool cMeshAORender_s0051_69d0::GetBoundingBox(BoundingBox& box, float& radius)
{
    box.mMin = Vector3(-1.0f, -1.0f, 0.0f);
    box.mMax = Vector3(1.0f, 1.0f, 1.0f);
    radius = 2.0f;
    return false;
}
}  // namespace nSPSkinner

// @ 0x00516eb0
namespace nSPSkinner {
void cMeshAORender_s0051_69d0::Rebuild()
{
    const Vector3f* n24;
    uint8_t* bucket;
    const int* where;
    MeshData* t32;
    const int* base;
    int other;
    const int* p38;
    int g;
    int end;
    SP::cMaterial_s0051_69d0* b;
    const Vector2f* t26;
    int t36;
    const Vector3f* alloc;

    mStaticBuffer = 0;
    if (!GetSkinnerContext())
        return;
    b = SP::MaterialManager()->GetMaterial(0x320adfd3);
    t32 = SkinnerCtx()->GetMesh();
    if (!b || !t32 || t32->mPositionIndices.empty())
        return;
    SP::cStaticBufferDraw::spInstance->Begin(b->mID, 2, 4, 0);
    g = t32->mPositionIndices.size();
    end = 0;
    alloc = (const Vector3f*)t32->mPositions.mpBegin;
    n24 = (const Vector3f*)t32->mNormals.mpBegin;
    p38 = t32->mPositionIndices.mpBegin;
    base = t32->mNormalIndices.mpBegin;
    t26 = (const Vector2f*)t32->mUVs.mpBegin;
    where = t32->mUVIndices.mpBegin;
    while (end < g) {
        t36 = SP::cStaticBufferDraw::spInstance->GetVertexBuffer(g - end, (void**)&bucket, &other);
        if (other == 0x24 && t36 > 0) {
            for (int idx = end, pBegin = end + t36; idx < pBegin; ++idx) {
                *(Vector3f*)bucket = alloc[p38[idx]];
                bucket += sizeof(Vector3f);
                *(Vector3f*)bucket = n24[base[idx]];
                bucket += sizeof(Vector3f);
                bucket[3] = 0xff;
                bucket[2] = 0xff;
                bucket[1] = 0xff;
                bucket[0] = 0xff;
                bucket += 4;
                *(uint64_t*)bucket = *(const uint64_t*)&t26[where[idx]];   // uv, copied as one 8-byte value
                bucket += sizeof(Vector2f);
            }
            SP::cStaticBufferDraw::spInstance->Unlock();
            end += t36;
        }
    }
    SP::cStaticBufferDraw::spInstance->End(&mStaticBuffer);
}
}  // namespace nSPSkinner

// @ 0x00517160
void cJobBase::Run(int, int, int, int)
{
    SkinnerModel* pModel = SkinnerCtx()->GetModel();
    if (pModel && pModel->mpMesh) {
        int nSteps = AppSystem()->IsMultiCore() ? 4 : 1;
        for (int i = 0; !mbDone && i < nSteps; ++i)
            mbDone = Step();
        if (!mbDone) {
            JobDesc desc;
            desc.mPriority = 10;
            JobManager()->AddJob(this, 0, &desc);
        }
    } else {
        mbDone = true;
    }
}

// @ 0x005172c0
void cJobBase::Schedule()
{
    if (!mbDone) {
        JobDesc desc;
        desc.mPriority = 10;
        JobManager()->AddJob(this, 0, &desc);
    }
}

// @ 0x005173a0
cJobBase::cJobBase()
: mbDone(false) {}

// @ 0x00517430
namespace nSPSkinner {
bool cPaintRenderJob_s0051_7430::RenderInternal()
{
    cPaintList_s0051_7430* list;
    RenderState* rs;
    rs = GetRenderMgr()->state;
    list = mPaintList;
    if (!((unsigned)mBatchIdx < (unsigned)list->mBatches.size()))
        return true;

    if (mStage == 0) {
        int total = 0;
        cPaintBatch* p = list->mBatches.begin() + mBatchIdx;
        int n = list->mBatches.size() - mBatchIdx;
        while (n > 0) {
            int nv = p->mVertices;
            if (total + nv > 0x8ca0)
                break;
            total += nv;
            n--;
            p++;
        }
        mVBBatches = (int)(p - (list->mBatches.begin() + mBatchIdx));
        int first = list->mBatches.begin()[mBatchIdx].mFirstVertex;
        mVBStart = first & ~1;
        mVBCount = (first & 1) + total;

        VertexBuffer* vb = rs->vb;
        int count = mVBCount;
        if (count == 0)
            count = vb->capacity;
        unsigned char stride = vb->desc->stride;
        void* dst = vb->Lock(6, vb->count * stride, stride * count);
        VertexBuffer* locked = 0;
        if (dst)
            locked = vb;
        if (locked) {
            mLockFailCount = 0;
            FastMemCopy(dst, list->mVerticesBegin + mVBStart * 0x1c, mVBCount * 0x1c);
            rs->vb->Unlock();
        } else {
            mLockFailCount = mLockFailCount + 1;
            if (mLockFailCount > 5)
                return true;
            return false;
        }
    } else {
        const VertexDescriptor* vd = rs->vdesc;
        if (!g_vertexDescriptor || !VertexDescriptor_AreEqual(g_vertexDescriptor, vd))
            g_softStateUpdated |= 0x100000;
        g_vertexDescriptor = vd;
        ApplyVertexDescriptor(g_vertexDescriptor);

        IDevice* dev = g_d3d9Device;
        StreamSlot* slots = g_streams;
        void* vbp = rs->vb->d3dvb;
        unsigned vcount = rs->vb->count;
        dev->vtbl->SetStreamSource(dev, 0, vbp, vcount * 0x1c, 0x1c);
        slots[0].vb = vbp;
        slots[0].off = rs->vb->count * 0x1c;
        slots[0].stride = 0x1c;
        for (int s = 1; s < 4; s++) {
            if (slots[s].vb != 0) {
                dev->vtbl->SetStreamSource(dev, s, 0, 0, 0);
                slots[s].vb = 0;
                slots[s].off = 0;
                slots[s].stride = 0;
            }
        }

        int st = mStage - 1;
        cRTTBuffer_s0051_7430* buf;
        if (st == 0)
            buf = rs->rttA;
        else
            buf = rs->rttB;
        buf->Begin();
        if (st == 0)
            buf->SetWriteMask(1, 1, 1, 0);
        else if (st == 1)
            buf->SetWriteMask(1, 0, 0, 0);
        else if (st == 2)
            buf->SetWriteMask(0, 0, 1, 0);
        else
            buf->SetWriteMask(0, 1, 0, 0);

        cTextureInstance* defTex = GetResMgr()->Get(0xbd77bb98, 0, 0);
        if (defTex)
            _InterlockedExchangeAdd(&defTex->mRefCount, 1);

        cPaintBatch* cur = list->mBatches.begin() + mBatchIdx;
        cPaintBatch* end = cur + mVBBatches;
        for (; cur < end; cur++) {
            cTextureInstance* dt = defTex;
            if (!(dt->mFlags & 1))
                GetResMgr()->Load(dt);
            Raster* tex0 = dt->mRaster;
            Raster* tex1 = 0;

            if (st == 0 && cur->mIdentityPass != 1) {
                if (cur->mBrush[0])
                    tex0 = ResolveRaster(cur->mBrush[0]);
                if (tex0) {
                    switch (cur->mBlendModes[0]) {
                    case 2: buf->material = 0x262bf86f; break;
                    case 3: buf->material = 0x28fedd44; break;
                    case 4: buf->material = 0x7d02141c; break;
                    case 5: buf->material = 0xd1663766; break;
                    default: buf->material = 0xae08f862;
                    }
                }
            } else if (st == 1) {
                if (cur->mBrush[1])
                    tex0 = ResolveRaster(cur->mBrush[1]);
                if (cur->mBrush[2])
                    tex1 = ResolveRaster(cur->mBrush[2]);
                if (tex1 == 0) {
                    if (tex0) {
                        switch (cur->mBlendModes[1]) {
                        case 2: buf->material = 0xb9ac2ae2; break;
                        case 3: buf->material = 0xc6ced15d; break;
                        case 4: buf->material = 0x4db46b47; break;
                        case 5: buf->material = 0x1b675065; break;
                        default: buf->material = 0x5ce94d87;
                        }
                    }
                } else {
                    switch (cur->mBlendModes[1]) {
                    case 2: buf->material = 0x9a88e7b3; break;
                    case 3: buf->material = 0x9d5bcc90; break;
                    case 4: buf->material = 0xf605e298; break;
                    case 5: buf->material = 0x059c333a; break;
                    default: buf->material = 0x408e6ca6;
                    }
                    buf->SetParam(0, Vec4(1.0f, 0.0f, 0.0f, 0.0f));
                }
            } else if (st == 2) {
                if (cur->mBrush[1])
                    tex0 = ResolveRaster(cur->mBrush[1]);
                if (cur->mBrush[2])
                    tex1 = ResolveRaster(cur->mBrush[2]);
                if (tex1 == 0) {
                    if (tex0) {
                        switch (cur->mBlendModes[2]) {
                        case 2: buf->material = 0x9ecf875f; break;
                        case 3: buf->material = 0x81f1ebb4; break;
                        case 4: buf->material = 0x162c01ec; break;
                        case 5: buf->material = 0xb6fb2576; break;
                        default: buf->material = 0x1b481432;
                        }
                    }
                } else {
                    switch (cur->mBlendModes[2]) {
                    case 2: buf->material = 0x9a88e7b3; break;
                    case 3: buf->material = 0x9d5bcc90; break;
                    case 4: buf->material = 0xf605e298; break;
                    case 5: buf->material = 0x059c333a; break;
                    default: buf->material = 0x408e6ca6;
                    }
                    buf->SetParam(0, Vec4(0.0f, 0.0f, 1.0f, 0.0f));
                }
            } else if (st == 3 && cur->mIdentityPass != 0) {
                if (cur->mBrush[0])
                    tex0 = ResolveRaster(cur->mBrush[0]);
                if (tex0) {
                    if (cur->mIdentityPass == 1) {
                        switch (cur->mBlendModes[0]) {
                        case 2: buf->material = 0x262bf86f; break;
                        case 3: buf->material = 0x28fedd44; break;
                        case 4: buf->material = 0x7d02141c; break;
                        case 5: buf->material = 0xd1663766; break;
                        default: buf->material = 0xae08f862;
                        }
                    } else {
                        buf->material = 0x82d83269;
                    }
                }
            } else {
                tex0 = 0;
            }

            if (tex0) {
                int firstVert = cur->mFirstVertex - mVBStart;
                unsigned verts = cur->mVertices;
                cPaintBatch* nx = cur;
                for (;;) {
                    cPaintBatch* nn = nx + 1;
                    if (!(nn < end))
                        break;
                    if (nx->mBrush[0] != nn->mBrush[0] || nx->mBrush[1] != nn->mBrush[1] ||
                        nx->mBrush[2] != nn->mBrush[2])
                        break;
                    if (nx->mBlendModes[st] != nn->mBlendModes[st])
                        break;
                    if (st == 0 && nn->mIdentityPass == 1)
                        break;
                    if (st == 3 && nn->mIdentityPass == 0)
                        break;
                    verts += nn->mVertices;
                    nx = nn;
                }
                cur = nx;
                buf->SetTexture(0, tex0);
                buf->SetTexture(1, tex1);
                CompiledState* cs = buf->PrepareState();
                cs->Dispatch();
                D3D9Sync();
                if (g_vertexDescriptor != rs->vdesc) {
                    const VertexDescriptor* vd2 = rs->vdesc;
                    if (!g_vertexDescriptor || !VertexDescriptor_AreEqual(g_vertexDescriptor, vd2))
                        g_softStateUpdated |= 0x100000;
                    g_vertexDescriptor = vd2;
                    ApplyVertexDescriptor(g_vertexDescriptor);
                }
                void (__cdecl* fn)(int) = g_shader->fn14;
                fn(0);
                g_softStateUpdated = 0;
                if (verts != 0 && verts <= rs->vb->capacity)
                    dev->vtbl->DrawPrimitive(dev, 4, firstVert, verts / 3);
            }
        }
        buf->SetWriteMask(1, 1, 1, 1);
        buf->BeginDraw();
        if (defTex)
            AtomicRefCounted_Release(defTex);
    }

    mStage = mStage + 1;
    if (mStage == 4 && mSkipIdentity)
        mStage = mStage + 1;
    if (mStage > 4) {
        mStage = 0;
        mBatchIdx = mBatchIdx + mVBBatches;
        if (mBatchIdx == list->mBatches.size())
            return true;
    }
    return false;
}
}  // namespace nSPSkinner

// @ 0x005182f0
namespace nSPSkinner {
bool cPaintRenderJob_s0051_82f0::Render()
{
    int* app = (int*)SP_AppSystem();
    char ok = ((char(__thiscall*)(void*))(*(void**)(*app + 0x44)))(app);
    if (ok == 0) {
        if ((mStage == 0) && RenderInternal())
            return true;
        if ((mStage == 2) && RenderInternal())
            return true;
        if ((mStage == 3) && RenderInternal())
            return true;
        return RenderInternal();
    }
    for (int i = 0;; ++i) {
        if ((i > 0xb) && (mStage == 0))
            return false;
        if (RenderInternal())
            break;
    }
    return true;
}
}  // namespace nSPSkinner

// @ 0x005183c0
namespace nSPSkinner {
bool cPaintDilateJob_s0051_82f0::Render()
{
    float f4 = kZero, f8 = kZero;
    float d4 = kZero, d8 = kZero, dc = kZero;
    uint8_t c0[4] = { 0, 0, 0, 0xff };
    uint32_t col0 = *(uint32_t*)c0;
    uint8_t c1[4] = { 0, 0, 0, 0 };
    uint32_t col1 = *(uint32_t*)c1;

    cDilateSingleton* sing = (cDilateSingleton*)GetSingleton();
    cRTTBuffer_s0051_82f0* buf = *(cRTTBuffer_s0051_82f0**)(sing->table + 0x10 + mComponent * 4);

    if (mStage == 0) {
        buf->Setup();
        buf->Set(0, 0, 0, 1);
        buf->material = 0xf8b396;
        buf->Reserve(2);
        float p0[2] = { kZero, kZero };
        buf->Tri(p0, &f4, &d4, col1);
        float p1[2] = { kOne, kZero };
        buf->Tri(p1, &f4, &d4, col1);
        float p2[2] = { kOne, kOne };
        buf->Tri(p2, &f4, &d4, col1);
        float p3[2] = { kOne, kOne };
        buf->Tri(p3, &f4, &d4, col1);
        float p4[2] = { kZero, kOne };
        buf->Tri(p4, &f4, &d4, col1);
        float p5[2] = { kZero, kZero };
        buf->Tri(p5, &f4, &d4, col1);
        buf->Flush();

        cDilateMesh* mesh = ((cDilateSingleton*)GetSingleton())->mesh;
        cDilateObj* obj = ((cDilateSingleton*)GetSingleton())->obj;
        char* partsBegin = obj->model->parts.begin;
        int nParts = (obj->model->parts.end - obj->model->parts.begin) / 0x8c;
        (void)partsBegin; (void)nParts;
        uint32_t i = 0;
        uint32_t remaining = (uint32_t)(mesh->idxEnd - mesh->idxBegin) / 3;
        while (remaining != 0) {
            int got = buf->Reserve(remaining);
            uint32_t end = got * 3 + i;
            for (; i < end; ++i)
                buf->Tri((float*)((char*)mesh->verts + mesh->indices[i] * 8),
                         (float*)((char*)mesh->verts + mesh->indices[i] * 8), &d4, col0);
            remaining -= got;
            buf->Flush();
        }
        buf->Set(1, 1, 1, 1);
        buf->BeginDraw();
        mStage = 1;
        return false;
    }

    int* app = (int*)SP_AppSystem();
    char ok = ((char(__thiscall*)(void*))(*(void**)(*app + 0x44)))(app);
    int cap = (ok != 0) ? 8 : 2;
    int rem = mPasses - mStage + 1;
    int n = MinRef(rem, cap);
    cRTTBuffer_s0051_82f0* cur = buf;
    cDilateSingleton* sing2 = (cDilateSingleton*)GetSingleton();
    cRTTBuffer_s0051_82f0* dst = *(cRTTBuffer_s0051_82f0**)(sing2->table + 0x18);

    for (int i = 0; i < n; ++i) {
        dst->Setup();
        dst->material = 0xfa2f3df4;
        float invW = 1.0f / (float)buf->width;
        float invH = 1.0f / (float)buf->height;
        float q0 = invW, q1 = invH, q2 = kZero, q3 = kZero;
        if (dst->maxparam <= 0)
            dst->maxparam = 1;
        dst->params[0] = q0; dst->params[1] = q1;
        dst->params[2] = q2; dst->params[3] = q3;
        uint32_t raster = buf->texture;
        if ((raster != 0) && (dst->maxtexture < 1))
            dst->maxtexture = 1;
        dst->textures[0] = raster;
        float r0 = kOne, r1 = kOne;
        float s0 = kZero, s1 = kZero;
        dst->vertex(&s0, &r0, -1);
        dst->BeginDraw();
        dst->SwapWith(buf);
    }
    if (buf != cur) {
        dst->Setup();
        dst->material = 0xa0468560;
        uint32_t raster = buf->texture;
        if ((raster != 0) && (dst->maxtexture < 1))
            dst->maxtexture = 1;
        dst->textures[0] = raster;
        float r0 = kOne, r1 = kOne;
        float s0 = kZero, s1 = kZero;
        dst->vertex(&s0, &r0, -1);
        dst->BeginDraw();
        dst->SwapWith(buf);
    }
    mStage = mStage + n;
    return mStage > mPasses;
}
}  // namespace nSPSkinner

// @ 0x00518b00
namespace nSPSkinner {
void cFieldSwap::SwapWith(cFieldSwap* o)
{
    swapv(*(uint64_t*)((char*)this + 0x50), *(uint64_t*)((char*)o + 0x50));
    swapv(*(uint32_t*)((char*)this + 0x60), *(uint32_t*)((char*)o + 0x60));
    swapv(*(uint32_t*)((char*)this + 0x58), *(uint32_t*)((char*)o + 0x58));
    swapv(*(uint32_t*)((char*)this + 0x5c), *(uint32_t*)((char*)o + 0x5c));
    swapv(*(uint32_t*)this, *(uint32_t*)o);
}
}  // namespace nSPSkinner

// @ 0x00518bf0
namespace nSPSkinner {
bool cPaintCopyIdentityJob_s0051_82f0::Render()
{
    int iVar1 = (int)GetSingleton();
    cRTTBuffer_s0051_82f0* buf = *(cRTTBuffer_s0051_82f0**)(*(int*)(iVar1 + 0xc) + 0x10);
    int iVar2 = (int)GetSingleton();
    int p = *(int*)(*(int*)(iVar2 + 0xc) + 0x14);

    buf->Setup();
    buf->Set(0, 0, 0, 1);
    buf->material = 0x58653eac;

    uint32_t raster = *(uint32_t*)(p + 0x60);
    if ((raster != 0) && ((int)buf->maxtexture < 1))
        buf->maxtexture = 1;
    buf->textures[0] = raster;

    float a0 = kOne, a1 = kOne;
    float b0 = kZero, b1 = kZero;
    buf->vertex(&b0, &a0, -1);
    buf->Set(1, 1, 1, 1);
    buf->BeginDraw();
    return true;
}
}  // namespace nSPSkinner

// @ 0x00518cf0
namespace nSPSkinner {
bool cPaintDifferentiateJob_s0051_82f0::Render()
{
    uint32_t prop = 0x0c19db33;
    float val = GetFloatProperty(prop);
    if (val == kZero)
        val = kConst6110;

    float f4 = kZero, f8 = kZero;
    float d4 = kZero, d8 = kZero, dc = kZero;

    uint8_t c0[4] = { 0, 0, 0, 0xff };
    uint32_t col0 = *(uint32_t*)c0;
    uint8_t c1[4] = { 0, 0, 0, 0 };
    uint32_t col1 = *(uint32_t*)c1;

    int s = (int)GetSingleton();
    cRTTBuffer_s0051_82f0* buf = *(cRTTBuffer_s0051_82f0**)(*(int*)(s + 0xc) + 0x18);
    int ctx = *(int*)(*(int*)(s + 0xc) + 0x14);

    buf->Setup();
    buf->material = 0x9e74d163;

    uint32_t raster = *(uint32_t*)(ctx + 0x60);
    if ((raster != 0) && ((int)buf->maxtexture < 1))
        buf->maxtexture = 1;
    buf->textures[0] = raster;

    float invW = 1.0f / (float)*(int*)(ctx + 0x58);
    float invH = 1.0f / (float)*(int*)(ctx + 0x5c);

    float q0 = invW;
    float q1 = invH;
    float q2 = val / kConstB95C;
    float q3 = kZero;

    if ((int)buf->maxtexture <= 0)
        buf->maxtexture = 1;
    float* dst = (float*)((char*)buf + 0xc + 0);
    dst[0] = q0; dst[1] = q1; dst[2] = q2; dst[3] = q3;

    float r0 = kOne, r1 = kOne;
    float s0 = kZero, s1 = kZero;
    buf->vertex(&s0, &r0, -1);
    buf->BeginDraw();
    return true;
}
}  // namespace nSPSkinner

// @ 0x00518f10
bool nSPSkinner::cPaintAmbOccJob_s0051_8f10::Render()
{
    void* ps = GetPaintSystem();
    ResultObj* result = *(ResultObj**)((char*)ps + 0x10);
    void* mat = *(void**)((char*)ps + 0xc);
    nSPSkinner::cRTTBuffer_s0051_8f10* comp0 = *(nSPSkinner::cRTTBuffer_s0051_8f10**)((char*)mat + 0x10);
    nSPSkinner::cRTTBuffer_s0051_8f10* comp1 = *(nSPSkinner::cRTTBuffer_s0051_8f10**)((char*)mat + 0x14);
    SkinObj* skin = *(SkinObj**)((char*)ps + 0x20);
    ModelObj* model = skin->mpModel;
    RigBlock* blocks = model->mBlocksBegin;
    int nBlocks = (int)((char*)model->mBlocksEnd - (char*)model->mBlocksBegin) / 0x8c;

    float fParam0 = g_1485720;
    float fParam1 = g_1485378;
    uint32_t defBits = 0x40200100;
    float fDefault = *(float*)&defBits;

    int r = InitVerbCollection(model->mEditorModel);
    int key = (r == 0x438f6347) ? 0xf01f7f52 : 0xf1cf8a9d;
    void* pIter = 0;
    int it = FUN_0041d870(&pIter);
    PropertyManager* pm = (PropertyManager*)SP_PropertyManager();
    if (pm->GetProperty(key, fDefault, (void*)it)) {
        GetFloatProperty(pIter, 0x26cabbf, &fParam0);
        GetFloatProperty(pIter, 0x26dc91e, &fParam1);
    }
    for (int i = 0; i < 2; i++) {
        nSPSkinner::cRTTBuffer_s0051_8f10* cur;
        if (i == 0) {
            cur = comp0;
            RTTBuffer_Begin(cur);
            RTTBuffer_SetParams(cur, 1, 1, 1, 0);
        } else {
            cur = comp1;
            RTTBuffer_Begin(cur);
            RTTBuffer_SetParams(cur, 1, 0, 0, 0);
        }
        cur->material = 0xbc487ecb;
        if (cur->maxparam < 1)
            cur->maxparam = 1;
        cur->params[0] = fParam0;
        cur->params[1] = fParam1;
        cur->params[2] = g_1485378;
        cur->params[3] = g_1485378;
        void* tex = GetTextureHandle(ps);
        if (tex != 0 && cur->maxtexture < 1)
            cur->maxtexture = 1;
        cur->textures[0] = tex;

        int ai = 0;
        int count = (int)(((char*)result->mE4end - (char*)result->mE4begin) / 4);
        for (int j = 0; j < nBlocks; j++) {
            RigBlock* block = (RigBlock*)((char*)blocks + j * 0x8c);
            void* bp = skin->mBlockProps[j];
            if ((block->mFlags & 1) == 0) {
                float c = g_1485720;
                GetFloatProperty(bp, 0xd669e3c7, &c);
                if (c < 0.0f)
                    c = 0.0f;
                c = c * 255.0f;
                if (c > 255.0f)
                    c = 255.0f;
                uint32_t ci = (uint32_t)RoundToInt(c);
                uint32_t color = (ci << 24) | (ci << 16) | (ci << 8) | ci;
                AOVert* p = (AOVert*)result->mE4begin[ai];
                ai++;
                float va[2]; va[0] = p->x0; va[1] = p->y0;
                float vb[2]; vb[0] = p->x1; vb[1] = p->y1;
                RTTBuffer_Draw(cur, color, va, vb);
            }
        }
        while (ai < count) {
            AOVert* p = (AOVert*)result->mE4begin[ai];
            ai++;
            float va[2]; va[0] = p->x0; va[1] = p->y0;
            float vb[2]; vb[0] = p->x1; vb[1] = p->y1;
            RTTBuffer_Draw(cur, 0xffffffffu, va, vb);
        }
        RTTBuffer_SetParams(cur, 1, 1, 1, 1);
        RTTBuffer_BeginDraw(cur);
    }
    if (pIter != 0)
        ((PropIterator*)pIter)->Release();
    return true;
}

// @ 0x00519640
bool nSPSkinner::cPaintSplatJob_s0051_9640::Render()
{
    int ps1 = GetPaintSystem_s0051_9640();
    int mat = *(int*)(ps1 + 0xc);
    cRTTBuffer_s0051_9640* buf0 = *(cRTTBuffer_s0051_9640**)(mat + 0x10);
    cRTTBuffer_s0051_9640* buf1 = *(cRTTBuffer_s0051_9640**)(mat + 0x14);
    int ps2 = GetPaintSystem_s0051_9640();
    int skin = *(int*)(ps2 + 0x20);
    int blocks = *(int*)(*(int*)(skin + 8) + 0x98);
    int nBlocks = (*(int*)(*(int*)(skin + 8) + 0x9c) - *(int*)(*(int*)(skin + 8) + 0x98)) / 0x8c;

    if (mStage == 1)
        mStage = 2;
    if (mStage < 4) {
        if (mStage < 2)
            RTTBuffer_Begin(buf0);
        else
            RTTBuffer_Begin(buf1);

        float c4c, c48, c44, c40, c3c, c38, c34, c30, c2c, c28, c24, c20;
        c40 = 0.0f; c30 = 0.0f; c20 = 0.0f;
        Vector3_CopyCtor(&c4c, (char*)0x15df0f0 + 0);
        Vector3_CopyCtor(&c3c, (char*)0x15df0f0 + 0xc);
        Vector3_CopyCtor(&c2c, (char*)0x15df0f0 + 0x18);

        float fGloss = ((DirectPropertyList*)_sAppProperties)->GetFloatProperty(0x1c76d9b5);
        if (fGloss == 0.0f)
            fGloss = 1.0f;

        int drawn = 0;
        while (mBlock < nBlocks && drawn < 10) {
            if ((*(uint16_t*)(blocks + 8 + mBlock * 0x8c) & 1) == 0) {
                drawn++;
                uint32_t* rect = (uint32_t*)(mBlock * 0x10 + *(int*)(skin + 0x90));
                float uv0[2]; uv0[0] = (float)rect[0]; uv0[1] = (float)rect[1];
                float uv1[2]; uv1[0] = (float)rect[2]; uv1[1] = (float)rect[3];

                SplatObj* prop = *(SplatObj**)(*(int*)(skin + 0xc) + mBlock * 4);
                int* texA = 0;
                int* texB = 0;
                int* texC = 0;
                bool haveA = false, haveB = false, haveC = false;

                {
                    if (mStage == 0 && (haveA = prop->Has(0x2424655))) {
                        void* o = prop->GetByKey(0x2424655);
                        void* v;
                        if (*(int16_t*)((char*)o + 0x12) == 0x20 || *(int16_t*)((char*)o + 0x12) == 0x10)
                            v = FUN_00446ff0();
                        else
                            v = FUN_006bb640();
                        TexFactory* f = (TexFactory*)FUN_0067dd60();
                        if (f->Valid(v, ((int*)v)[1], ((int*)v)[2])) {
                            f = (TexFactory*)FUN_0067dd60();
                            texA = (int*)f->Create(v, ((int*)v)[1], ((int*)v)[2], 6);
                        }
                    }
                    if ((mStage == 0 || mStage == 1) && (haveB = prop->Has(0x2424657))) {
                        void* o = prop->GetByKey(0x2424657);
                        void* v;
                        if (*(int16_t*)((char*)o + 0x12) == 0x20 || *(int16_t*)((char*)o + 0x12) == 0x10)
                            v = FUN_00446ff0();
                        else
                            v = FUN_006bb640();
                        TexFactory* f = (TexFactory*)FUN_0067dd60();
                        if (f->Valid(v, ((int*)v)[1], ((int*)v)[2])) {
                            f = (TexFactory*)FUN_0067dd60();
                            texB = (int*)f->Create(v, ((int*)v)[1], ((int*)v)[2], 6);
                        }
                    }
                    if ((mStage == 2 || mStage == 3) && (haveC = prop->Has(0x2424656))) {
                        void* o = prop->GetByKey(0x2424656);
                        void* v;
                        if (*(int16_t*)((char*)o + 0x12) == 0x20 || *(int16_t*)((char*)o + 0x12) == 0x10)
                            v = FUN_00446ff0();
                        else
                            v = FUN_006bb640();
                        TexFactory* f = (TexFactory*)FUN_0067dd60();
                        if (f->Valid(v, ((int*)v)[1], ((int*)v)[2])) {
                            f = (TexFactory*)FUN_0067dd60();
                            texC = (int*)f->Create(v, ((int*)v)[1], ((int*)v)[2], 6);
                        }
                    }
                }
                (void)haveA; (void)haveB; (void)haveC;

                if (mStage == 0 && texA != 0 && texB != 0) {
                    RTTBuffer_SetParams(buf0, 1, 1, 1, 0);
                    buf0->material = 0xd9ec39bc;
                    if (buf0->maxparam < 1) buf0->maxparam = 1;
                    buf0->params[0] = c4c; buf0->params[1] = c48; buf0->params[2] = c44; buf0->params[3] = c40;
                    if (buf0->maxparam < 2) buf0->maxparam = 2;
                    buf0->params[4] = c3c; buf0->params[5] = c38; buf0->params[6] = c34; buf0->params[7] = c30;
                    if (buf0->maxparam < 3) buf0->maxparam = 3;
                    buf0->params[8] = c2c; buf0->params[9] = c28; buf0->params[10] = c24; buf0->params[11] = c20;
                    if ((texA[1] & 1) == 0)
                        ((TexFactory*)FUN_0067dd60())->Release(texA);
                    void* raster = (void*)*texA;
                    if (raster != 0 && buf0->maxtexture < 1) buf0->maxtexture = 1;
                    buf0->textures[0] = raster;
                    if ((texB[1] & 1) == 0)
                        ((TexFactory*)FUN_0067dd60())->Release(texB);
                    raster = (void*)*texB;
                    if (raster != 0 && buf0->maxtexture < 2) buf0->maxtexture = 2;
                    buf0->textures[1] = raster;
                    RTTBuffer_Draw(buf0, uv0, uv1, 0xffffffff);
                }
                if (mStage == 1 && texB != 0) {
                    RTTBuffer_SetParams(buf0, 0, 0, 0, 1);
                    buf0->material = 0xa91b6551;
                    if (buf0->maxparam < 1) buf0->maxparam = 1;
                    buf0->params[0] = 1.0f; buf0->params[1] = 1.0f; buf0->params[2] = 1.0f; buf0->params[3] = 1.0f;
                    if ((texB[1] & 1) == 0)
                        ((TexFactory*)FUN_0067dd60())->Release(texB);
                    void* raster = (void*)*texB;
                    if (raster != 0 && buf0->maxtexture < 1) buf0->maxtexture = 1;
                    buf0->textures[0] = raster;
                    buf0->textures[1] = 0;
                    RTTBuffer_Draw(buf0, uv0, uv1, 0xffffffff);
                }
                if (mStage == 2 && texC != 0) {
                    float f = *(float*)(mat + 0x30);
                    RTTBuffer_SetParams(buf1, 1, 0, 0, 0);
                    buf1->material = 0x3815422;
                    if (buf1->maxparam < 1) buf1->maxparam = 1;
                    buf1->params[0] = f; buf1->params[1] = f; buf1->params[2] = f; buf1->params[3] = 1.0f;
                    if ((texC[1] & 1) == 0)
                        ((TexFactory*)FUN_0067dd60())->Release(texC);
                    void* raster = (void*)*texC;
                    if (raster != 0 && buf1->maxtexture < 1) buf1->maxtexture = 1;
                    buf1->textures[0] = raster;
                    RTTBuffer_Draw(buf1, uv0, uv1, 0xffffffff);
                }
                if (mStage == 3 && texC != 0) {
                    float f = *(float*)(mat + 0x2c) * fGloss;
                    RTTBuffer_SetParams(buf1, 0, 0, 1, 0);
                    buf1->material = 0x968e3fff;
                    if (buf1->maxparam < 1) buf1->maxparam = 1;
                    buf1->params[0] = f; buf1->params[1] = f; buf1->params[2] = f; buf1->params[3] = 1.0f;
                    if ((texC[1] & 1) == 0)
                        ((TexFactory*)FUN_0067dd60())->Release(texC);
                    void* raster = (void*)*texC;
                    if (raster != 0 && buf1->maxtexture < 1) buf1->maxtexture = 1;
                    buf1->textures[0] = raster;
                    RTTBuffer_Draw(buf1, uv0, uv1, 0xffffffff);
                }
            }
            mBlock = mBlock + 1;
        }
        if (mStage < 2)
            RTTBuffer_BeginDraw(buf0);
        else
            RTTBuffer_BeginDraw(buf1);
        if (nBlocks <= mBlock) {
            mBlock = 0;
            mStage = mStage + 1;
        }
    }
    return mStage == 4;
}

// @ 0x0051a350
bool nSPSkinner::cPaintSplatAlphaJob_s0051_a350::Render()
{
    nSPSkinner::cRTTBuffer_s0051_a350* buf;
    {
        int ps = GetPaintSystem_s0051_a350();
        int mat = *(int*)(ps + 0xc);
        buf = *(nSPSkinner::cRTTBuffer_s0051_a350**)(mat + 0x10);
    }
    int ps2 = GetPaintSystem_s0051_a350();
    int skin = *(int*)(ps2 + 0x20);
    int blocks = *(int*)(*(int*)(skin + 8) + 0x98);
    int nBlocks = (*(int*)(*(int*)(skin + 8) + 0x9c) - *(int*)(*(int*)(skin + 8) + 0x98)) / 0x8c;
    RTTBuffer_Begin(buf);
    int drawn = 0;
    while (mBlock < nBlocks && drawn < 10) {
        if ((*(uint16_t*)(blocks + 8 + mBlock * 0x8c) & 1) == 0) {
            int prop[3]; prop[0] = 0; prop[1] = 0; prop[2] = 0;
            if (SP_GetPropertyAsKey(*(void**)(*(int*)(skin + 0xc) + mBlock * 4), 0x2424657, prop)) {
                int* tex = (int*)((Factory*)FUN_0067dd60())->Create(prop[0], prop[1], prop[2], 6);
                if (tex != 0) {
                    uint32_t* rect = (uint32_t*)(mBlock * 0x10 + *(int*)(skin + 0x90));
                    float uv0[2]; uv0[0] = (float)rect[0]; uv0[1] = (float)rect[1];
                    float uv1[2]; uv1[0] = (float)rect[2]; uv1[1] = (float)rect[3];
                    RTTBuffer_SetParams(buf, 0, 0, 0, 1);
                    buf->material = 0xa91b6551;
                    if (buf->maxparam < 1) buf->maxparam = 1;
                    buf->params[0] = 1.0f; buf->params[1] = 1.0f; buf->params[2] = 1.0f; buf->params[3] = 1.0f;
                    if ((tex[1] & 1) == 0)
                        ((Factory*)FUN_0067dd60())->Release(tex);
                    void* raster = (void*)*tex;
                    if (raster != 0 && buf->maxtexture < 1) buf->maxtexture = 1;
                    buf->textures[0] = raster;
                    buf->textures[1] = 0;
                    RTTBuffer_Draw(buf, uv0, uv1, 0xffffffff);
                    drawn++;
                }
            }
        }
        mBlock = mBlock + 1;
    }
    RTTBuffer_BeginDraw(buf);
    return nBlocks <= mBlock;
}

// @ 0x0051a6a0
void FUN_0051a6a0(TexObj** out)
{
    ARCRef<ImgObj> img;
    Svc40* s1 = FUN_0067dd40_t();
    Svc60* s2 = FUN_0067dd60_t();
    void** pp = img.AsPPVoidParam();
    s2->Make(s1->Make(pp, 0, 0));
    int n = img.p->mW * img.p->mH;
    char tag;
    ByteBuf buf(n, &tag);
    char zero = 0;
    char* iter;
    FUN_004c6ae0(&iter, buf.mpBegin, n, &zero);
    buf.mpEnd = buf.mpBegin + n;
    int count = img.p->mW * img.p->mH;
    for (int i = 0; i < count; i++)
        buf.mpBegin[i] = img.p->mpPixels[i * 4 + 1];
    TexRefAuto tex;
    tex.p = FUN_0067dd60_t()->CreateBuf(img.p->mW, img.p->mH, 1, 8, 0x32, 4);
    if (tex.p != 0)
        _InterlockedExchangeAdd(&tex.p->mnRefCount, 1);
    char* data = buf.mpBegin;
    if ((tex.p->mFlags & 1) == 0)
        FUN_0067dd60_t()->ReleaseTex(tex.p);
    tex.p->mpRaster->SetMipLevelData(data, 0);
    TexObj* moved = tex.p;
    tex.p = 0;
    *out = moved;
}

// @ 0x0051a8a0
void* SkinJob::FUN_0051a8a0()
{
    *(void**)this = &g_splatVtblBase;
    *(int*)((char*)this + 4) = 0;
    *(void**)this = &g_splatVtblDerived;
    ((SubObj*)((char*)this + 8))->FUN_0051d0d0();
    *(int*)((char*)this + 0x330) = 0;
    *(int*)((char*)this + 0x334) = 0;
    return this;
}

// @ 0x0051a930
void SkinJob::FUN_0051a930()
{
    void* self = this;
    *(void**)self = &g_splatVtblDerived;
    if (*(void**)((char*)self + 0x334) != 0)
        SP_cJob_GetStatus(*(void**)((char*)self + 0x334));
    if (*(void**)((char*)self + 0x330) != 0)
        (*(Factory**)((char*)self + 0x330))->v1();
    FUN_0051d180((char*)self + 8);
    *(void**)self = &g_splatVtblBase;
}

// @ 0x0051a9a0
void SkinJob::FUN_0051a9a0(int a2, char a3, char a4, int a5, int a6, int a7, int a8, char a9, char a10, char a11)
{
    void* self = this;
    *(int*)((char*)self + 0x33c) = 0;
    ((RefSlot*)((char*)self + 8))->CopyFrom(*(void**)((char*)self + 8), *(void**)((char*)self + 0xc));
    *(int*)((char*)self + 0x340) = 0;
    *(int*)((char*)self + 0x344) = 0;
    *(int*)((char*)self + 0x338) = a2;
    *(char*)((char*)self + 0x348) = a3;
    *(char*)((char*)self + 0x349) = a4;
    int ps = GetPaintSystem_s0051_a350();
    *(char*)((char*)self + 0x34a) = *(char*)(ps + 0x7e);
    *(int*)((char*)self + 0x320) = a5;
    *(int*)((char*)self + 0x324) = a6;
    *(int*)((char*)self + 0x328) = a7;
    *(int*)((char*)self + 0x32c) = a8;
    *(char*)((char*)self + 0x34b) = a9;
    *(char*)((char*)self + 0x34c) = a10;
    *(char*)((char*)self + 0x34d) = a11;
    *(char*)((char*)self + 0x34e) = 0;
    ((SkinJob*)self)->FUN_0051ab50(a3);
}

// @ 0x0051aaa0
void SkinJob::FUN_0051aaa0()
{
    void* self = this;
    if (*(void**)((char*)self + 0x330) != 0) {
        *(char*)((char*)*(void**)((char*)self + 0x330) + 0xc) = 1;
        void* p = *(void**)((char*)self + 0x330);
        *(void**)((char*)self + 0x330) = 0;
        if (p != 0)
            ((Factory*)p)->v1();
    }
    ((RefSlot*)((char*)self + 8))->CopyFrom(*(void**)((char*)self + 8), *(void**)((char*)self + 0xc));
    *(int*)((char*)self + 0x33c) = -1;
}

// @ 0x0051ab50
void SkinJob::FUN_0051ab50(char deep)
{
    void* self = this;
    int ps = GetPaintSystem_s0051_a350();
    int mat = *(int*)(ps + 0xc);
    int ps2 = GetPaintSystem_s0051_a350();
    int skin = *(int*)(ps2 + 0x20);
    if (mat != 0 && skin != 0) {
        int blocks = *(int*)(*(int*)(skin + 8) + 0x98);
        int base = mat + 0x3c;
        RefSlot* slot = (RefSlot*)((char*)self + 8);
        HashIter it;
        it.mpBucket = *(void**)(base + 4);
        it.mpNode = *(void**)it.mpBucket;
        if (it.mpNode == 0)
            it.IncrementBucket();
        for (;;) {
            void* endNode = *(void**)(*(int*)(base + 4) + *(int*)(base + 8) * 4);
            if (it.mpNode == endNode)
                break;
            for (int i = 0; i < 3; i++) {
                if (*(int*)((char*)it.mpNode + 4 + i * 4) != 0)
                    slot->Push((char*)it.mpNode + 4 + i * 4);
            }
            it.Increment();
        }
        int tex = (int)((Factory*)FUN_0067dd60())->v8((int)0xbd77bb98, 0, 0);
        if (tex != 0)
            *(int*)(tex + 8) = *(int*)(tex + 8) + 1;
        slot->Push(&tex);
        if (tex != 0)
            ((AtomicRefCounted*)tex)->Release();
        if (deep != 0) {
            int nBlocks = (*(int*)(*(int*)(skin + 8) + 0x9c) - *(int*)(*(int*)(skin + 8) + 0x98)) / 0x8c;
            for (int j = 0; j < nBlocks; j++) {
                if ((*(uint16_t*)(blocks + 8 + j * 0x8c) & 1) == 0) {
                    int propKey = *(int*)(*(int*)(skin + 0xc) + j * 4);
                    int prop[3]; prop[0] = 0; prop[1] = 0; prop[2] = 0;
                    if (SP_GetPropertyAsKey((void*)propKey, 0x2424655, prop)) {
                        int t = (int)((Factory*)FUN_0067dd60())->Create(prop[0], prop[1], prop[2], 4);
                        if (t != 0) *(int*)(t + 8) = *(int*)(t + 8) + 1;
                        slot->Push(&t);
                        if (t != 0) ((AtomicRefCounted*)t)->Release();
                    }
                    if (SP_GetPropertyAsKey((void*)propKey, 0x2424657, prop)) {
                        int t = (int)((Factory*)FUN_0067dd60())->Create(prop[0], prop[1], prop[2], 4);
                        if (t != 0) *(int*)(t + 8) = *(int*)(t + 8) + 1;
                        slot->Push(&t);
                        if (t != 0) ((AtomicRefCounted*)t)->Release();
                    }
                    if (SP_GetPropertyAsKey((void*)propKey, 0x2424656, prop)) {
                        int t = (int)((Factory*)FUN_0067dd60())->Create(prop[0], prop[1], prop[2], 4);
                        if (t != 0) *(int*)(t + 8) = *(int*)(t + 8) + 1;
                        slot->Push(&t);
                        if (t != 0) ((AtomicRefCounted*)t)->Release();
                    }
                }
            }
        }
    }
}

// @ 0x0051afd0
namespace Skinner {
void cSkinPainterPipeline::ExecutePipeline()
{
    cPaintSystem* pPaintSystem = GetPaintSystem_s0051_afd0();
    field_344++;

    switch (mCurrentStage) {
    case 0:
        mCurrentStage = 1;
    case 1:
        mCurrentStage = 2;
    case 2:
        for (int i = 0, n = mTextures.size(); i < n; i++) {
            if (mTextures[i].get() != 0 && (mTextures[i]->GetFlags() & 1) == 0) {
                field_340++;
                return;
            }
        }
        mCurrentStage = 3;
    case 3:
        RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobApplyBrushes(field_338, !field_349));
        mCurrentStage = 4;
    case 4:
        if (field_348)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobPaintParts());
        mCurrentStage = 5;
    case 5:
        if (field_348 && field_34A && !pPaintSystem->IsField7C())
            return;
        mCurrentStage = 6;
    case 6:
        if (field_348 && field_34A)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobAmbientOcclusion());
        mCurrentStage = 7;
    case 7:
        if (field_348 && !field_34E)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobColorDilateRepeat(0));
        mCurrentStage = 8;
    case 8:
        if (field_348 && !field_34E)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobColorDilateRepeat(1));
        mCurrentStage = 9;
    case 9:
        if (field_348 && field_349)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobCopyTex1AlphaToTex0());
        mCurrentStage = 10;
    case 10:
        if (field_348)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobCopyRigblocksTintMaskAlpha());
        mCurrentStage = 11;
    case 11:
        if (mTextureGroupID)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobExtractTexture(
                0, mTextureInstanceID, mTextureGroupID, field_34D, field_32C, false, field_34C));
        mCurrentStage = 12;
    case 12:
        if (field_328)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobBumpToNormal());
        mCurrentStage = 13;
    case 13:
        if (field_328)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobExtractTexture(
                2, mTextureInstanceID, field_328, field_34D, -1, field_34B, field_34C));
        mCurrentStage = 14;
    default:
        if (mCurrentStage != -1)
            mCurrentStage = -1;
    }
}
}  // namespace Skinner

// @ 0x0051c470
PaintSystem::PaintSystem(int kind, void* a, void* b, char c, void* d, char e, char f)
{
    *(void**)this = &g_vtblSkinnerPaintSystem;
    *(void**)((char*)this + 4) = &g_vtblLocaleChange;
    ((BaseEditor*)((char*)this + 8))->dtor();   // inlined base ctor
    *(void**)this = &g_vtblPaintA;
    *(void**)((char*)this + 4) = &g_vtblPaintB;
    *(void**)((char*)this + 8) = &g_vtblPaintC;
    *(void**)((char*)this + 0xc) = &g_vtblPaintD;
    *(void**)((char*)this + 0x18) = a;
    *(void**)((char*)this + 0x1c) = b;
    *(int*)((char*)this + 0x20) = 0;
    *(void**)((char*)this + 0x24) = d;
    *(char*)((char*)this + 0x28) = e;
    *(char*)((char*)this + 0x29) = f;
    *(char*)((char*)this + 0x2a) = c;
    *(int*)((char*)this + 0x2c) = 0;
    *(int*)((char*)this + 0x30) = 0;
    *(int*)((char*)this + 0x34) = 0;
    *(int*)((char*)this + 0x38) = 0;
    *(int*)((char*)this + 0x3c) = 0;
    *(int*)((char*)this + 0x40) = 0;
    *(int*)((char*)this + 0x44) = 0;
    *(int*)((char*)this + 0x48) = 0;
    int ps = GetPaintSystem_s0051_c470();
    int mat = *(int*)(ps + 0xc);
    void* mem = EA_alloc(0x20, "Skinner", 0, 0, 0, 0);
    void* bs = 0;
    if (mem != 0)
        bs = BakeSprites_ctor(mem);
    void** slot = (void**)((char*)this + 0x30);
    if (bs != *slot) {
        void* old = *slot;
        if (bs != 0)
            (*(void(__thiscall**)(void*))(((void**)*(void**)bs)[0]))(bs);
        *slot = bs;
        if (old != 0)
            (*(void(__thiscall**)(void*))((*(void***)old)[1]))(old);
    }
    if (mat != 0 && *(int*)(mat + 0x10 + kind * 4) != 0)
        *(void**)((char*)this + 0x20) = *(void**)(*(int*)(mat + 0x10 + kind * 4) + 0x60);
}

// @ 0x0051c620
int RefCounted::AddRef()
{
    return (int)_InterlockedIncrement(&mnRefCount);
}

// @ 0x0051c640
void SkinTexExtractorB::Init()
{
    int hole;
    mConn.Init(SP_MessageServer(), (char*)this - 8, (void*)0x150cad8, 3);
    if (mInstance != 0) {
        ServiceObj* svc = FUN_0067dd60_s0051_c470();
        svc->SetInstance(mInstance, 0, 1, 0);
    } else {
        mFlag = 1;
    }
}

// @ 0x0051d090
void* EditorResource::deleting_dtor(unsigned flags)
{
    *(void**)((char*)this + 4) = &g_vtblSimCreatureAbility;
    *(void**)this = &g_vtblEditorResource;
    if ((flags & 1) != 0)
        EASTL_allocator_deallocate(this);
    return this;
}
