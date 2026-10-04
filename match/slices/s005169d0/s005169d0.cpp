// s005169d0: random/table helpers, FastMemCopy, nSPSkinner::cMeshAORender (ambient-occlusion
// mesh draw) and a small ref-counted job class.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);   // 0x011e0744 (static thunk)
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}

// ---------------------------------------------------------------- random / table helpers
struct RandomOwner {
    char pad[0x54];
    uint32_t mSeed;     // +0x54
    float RandomFloat();
};

// @ 0x005169D0  linear congruential generator, returns [0.5, 1.5)
float RandomOwner::RandomFloat()
{
    uint64_t next = (uint64_t)mSeed * 0x41c64e6d + 0x3039;
    mSeed = (uint32_t)next;
    return (float)(int)(next >> 16) * 2.3283064e-10f + 0.5f;
}

// @ 0x00516A20  linear interpolation into a table of n samples, t in [0,1]
float SampleTable(const float* values, int n, float t)
{
    int i = 0;
    if (t >= 0.0f && --n > 0) {
        t = (float)n * t;
        i = (int)t;
        if (t > (float)i && n > i)
            return (t - i) * (values[i + 1] - values[i]) + values[i];
        i = n;
    }
    return values[i];
}

namespace {

// @ 0x00516AC0  `anonymous namespace'::FastMemCopy: MMX non-temporal block copy
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

} // namespace

// keeps the internal-linkage function emitted in this standalone TU (its real callers live elsewhere)
void* FastMemCopyRef = (void*)&FastMemCopy;

// ---------------------------------------------------------------- shared types
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
class RefCountTemplate {
public:
    RefCountTemplate() : mRefCount(0) {}
    virtual ~RefCountTemplate() {}
    virtual int AddRef();
    virtual int Release();
    T mRefCount;
};

template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount()
    {
        if (mpObject)
            mpObject->Release();
    }
    AutoRefCount& operator=(T* pObject)
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

namespace ResourceMan {
struct Key {
    uint32_t mnInstanceID;
    uint32_t mnTypeID;
    uint32_t mnGroupID;
    Key(uint32_t instance, uint32_t type, uint32_t group) : mnInstanceID(instance), mnTypeID(type), mnGroupID(group) {}
};
struct IResource {
    virtual int AddRef();
    virtual int Release();
};
struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual bool GetResource(const Key& key, IResource** ppResource);   // +0x14
};
IResourceManager* GetManager();     // 0x0067dcd0
} // namespace ResourceMan

} // namespace EA

namespace SP {

class cStaticBuffer {
public:
    virtual ~cStaticBuffer();
    virtual int AddRef();
    virtual int Release();
    int GetVertexBuffer(int nVertices, void** ppVertices, int* pStride);   // 0x007a47c0
    void Unlock();                                                         // 0x007a4650
    void Flush();                                                          // 0x007a4710
};

class cStaticBufferDraw {
public:
    cStaticBuffer* mpBuffer;
    static cStaticBufferDraw* spInstance;                                  // 0x015ddc84 (EA::SingletonBase)
    void Begin(uint32_t material, int primitive, int a, int b);            // 0x007a4420
    void Draw(void* pContext, uint32_t material);                          // 0x007a3e60
    int GetVertexBuffer(int nVertices, void** ppVertices, int* pStride) { return mpBuffer->GetVertexBuffer(nVertices, ppVertices, pStride); }
    void Unlock() { mpBuffer->Unlock(); }
    void End(cStaticBuffer** ppBuffer)
    {
        mpBuffer->Flush();
        *ppBuffer = mpBuffer;
        mpBuffer = 0;
    }
};

struct cMaterial { uint32_t pad; uint32_t mID; };
class cMaterialManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual cMaterial* GetMaterial(uint32_t id);   // +0x28
};
cMaterialManager* MaterialManager();               // 0x0067dd70

class cIDynamicDraw {
public:
    cIDynamicDraw() {}
    virtual void Dispatch(uint32_t a, uint32_t b, void* pContext) = 0;
    virtual bool GetBoundingBox(BoundingBox& box, float& radius) = 0;
};
class cDynamicDrawBase : public cIDynamicDraw {
public:
    cDynamicDrawBase() {}
    virtual void Dispatch(uint32_t a, uint32_t b, void* pContext);
};
class cDynamicDrawBaseRC : public cDynamicDrawBase, public EA::RefCountTemplate<int> {
public:
    cDynamicDrawBaseRC() {}
    virtual void Dispatch(uint32_t a, uint32_t b, void* pContext);
};

} // namespace SP

// mesh data (see s00513930 MeshData)
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

class cMeshAORender : public SP::cDynamicDrawBaseRC {
public:
    cMeshAORender();
    ~cMeshAORender();
    virtual void Dispatch(uint32_t a, uint32_t b, void* pContext);
    virtual bool GetBoundingBox(BoundingBox& box, float& radius);
    void Load(uint32_t instance, uint32_t group);
    void Unload();
    void Rebuild();

    EA::AutoRefCount<SP::cStaticBuffer> mStaticBuffer;          // +0x0c
    EA::AutoRefCount<EA::ResourceMan::IResource> mResource;     // +0x10
};

// @ 0x00516BA0
cMeshAORender::cMeshAORender() {}

// @ 0x00516C30
cMeshAORender::~cMeshAORender() {}

// @ 0x00516CA0
void cMeshAORender::Load(uint32_t instance, uint32_t group)
{
    SetupResource(this, instance, group);
    EA::ResourceMan::Key key(instance, 0xe6bce5, group);
    EA::ResourceMan::GetManager()->GetResource(key, &mResource);
}

// @ 0x00516D30
void cMeshAORender::Unload()
{
    ReleaseResourceData(mResource.get());
    mResource = 0;
}

// @ 0x00516DA0
void cMeshAORender::Dispatch(uint32_t a, uint32_t b, void* pContext)
{
    if (!mStaticBuffer.get())
        return;
    SP::cMaterial* pMaterial = SP::MaterialManager()->GetMaterial(0x320adfd3);
    if (!pMaterial)
        return;
    ((SP::cStaticBufferDraw*)mStaticBuffer.operator->())->Draw(pContext, pMaterial->mID);
}

// @ 0x00516E10
bool cMeshAORender::GetBoundingBox(BoundingBox& box, float& radius)
{
    box.mMin = Vector3(-1.0f, -1.0f, 0.0f);
    box.mMax = Vector3(1.0f, 1.0f, 1.0f);
    radius = 2.0f;
    return false;
}

struct Vector3f { float x, y, z; };
struct Vector2f { float x, y; };

// @ 0x00516EB0  nSPSkinner::cMeshAORender::Rebuild
// Builds a static vertex buffer (position, normal, white color, uv: 0x24 bytes/vertex) from the
// skinner mesh. Local names are chosen for /Od slot order:
//   bucket = vertex write pointer, n24 = normals, where = uv indices, base = normal indices,
//   t32 = mesh, other = vertex stride, p38 = position indices, b = material, end = indices done,
//   g = index count, t26 = uvs, alloc = positions, t36 = vertices locked this pass.
void cMeshAORender::Rebuild()
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
    SP::cMaterial* b;
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

} // namespace nSPSkinner

// ---------------------------------------------------------------- job scheduling
struct JobDesc {
    int mPriority;          // +0x00
    int m04;
    bool mb08;
    uint32_t m0c[8];
    JobDesc();
};

// @ 0x00517240
JobDesc::JobDesc()
{
    mPriority = 1;
    m04 = 0;
    mb08 = true;
    m0c[0] = 0; m0c[1] = 0; m0c[2] = 0; m0c[3] = 0;
    m0c[4] = 0; m0c[5] = 0; m0c[6] = 0; m0c[7] = 0;
}

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

// @ 0x005173A0
cJobBase::cJobBase() : mbDone(false) {}

// @ 0x005172C0
void cJobBase::Schedule()
{
    if (!mbDone) {
        JobDesc desc;
        desc.mPriority = 10;
        JobManager()->AddJob(this, 0, &desc);
    }
}

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

class cAOBakeJob : public cJobBase {
public:
    cAOBakeJob(SimpleVector<int>* pItems, bool b);
    virtual bool Step();
    SimpleVector<int>* mpItems;    // +0x10
    uint32_t m14[6];               // +0x14
    bool mb2c;                     // +0x2c
};

// @ 0x00517310
cAOBakeJob::cAOBakeJob(SimpleVector<int>* pItems, bool b)
{
    mpItems = pItems;
    m14[0] = 0; m14[1] = 0; m14[2] = 0; m14[3] = 0; m14[4] = 0; m14[5] = 0;
    mb2c = b;
    mbDone = pItems->empty();
    ScratchSlots<2>();
}
