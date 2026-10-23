// SP::cTerrainSphereQuad terrain-quad methods, range 0x00fb6630-0x00fb7640
//
// Retail rewrite of the 2008 dev-build cTerrainSphereQuad ribbon code.  The quad owns two
// eastl::vector caches -- mRibbonPolys (+0x18c, element stride 0x110) fed by
// AddPolysInRect/SetPolysInRect and mRibbonVerts (+0x1a0, element stride 0x30) consumed by the
// render device.  RebuildVertices (0x00fb6630) refills the vertex cache from the polygons via
// BuildRibbonVerts (0x00fb50d0, defined in the neighbouring slice); the four Dispatch* methods
// (0x00fb66d0 / 0x00fb6850 / 0x00fb6cd0 / 0x00fb6e00) bind raster states and call the device.
// Layouts follow the retail offsets seen in the binary.
#include "types.h"
#include <new>

struct cSPVector2 { float x, y; };

// ---------------------------------------------------------------------------
// rw::graphics state objects (external translation units)
// ---------------------------------------------------------------------------
class CompiledState { public: void Dispatch(); };                     // 0x11ee580

class RasterState
{
public:
    void*    mpState;   // +0x00
    uint32_t mStage;    // +0x04
    uint32_t mValue;    // +0x08
    uint32_t mOld;      // +0x0c
    RasterState();                                                // 0xfaed90
    void Assign(void* st, uint32_t stage, uint32_t value);         // 0xfc27e0
    void Clear();                                                 // 0xfc2830
    ~RasterState() { Clear(); }
};

class cTextureInstance { public: void* GetRaster(); };                 // 0x46f260

struct DispatchStats
{
    char pad00[0x20];
    int  mField20;   // +0x20 accumulated vertex count
    int  mField24;   // +0x24 accumulated primitive count
    int  mField28;   // +0x28 batch count
};

// ---------------------------------------------------------------------------
// ribbon geometry element types
// ---------------------------------------------------------------------------
struct cRibbonFaceVertex { char pad[0x14]; };

struct cRibbonFacePoly                                       // 0x110 bytes
{
    cRibbonFaceVertex* mpBegin;         // +0x00  fixed_vector<cRibbonFaceVertex,7>
    cRibbonFaceVertex* mpEnd;           // +0x04
    uint32_t           mVecPad[0x27];   // +0x08 .. +0xa3 (rest of the fixed_vector)
    float              mTopV;           // +0xa4
    uint32_t           mPadA8;          // +0xa8
    int                mRibbonID;       // +0xac
    float              mMinX;           // +0xb0
    float              mMinY;           // +0xb4
    float              mMaxX;           // +0xb8
    float              mMaxY;           // +0xbc
    uint32_t           mPatch[0x14];    // +0xc0
    cRibbonFacePoly(const cRibbonFacePoly&);   // 0xfa9840 (out of line)
};

struct cRibbonUnmorphedVert { uint32_t mPad[0x0c]; };        // 0x30 bytes

// eastl::copy / UninitializedCopy / DestructElements / CopyIntoSlot (out of line in retail)
cRibbonFacePoly* VectorCopy(cRibbonFacePoly* first, cRibbonFacePoly* last, cRibbonFacePoly* dest);            // 0xfb65b0
cRibbonFacePoly* VectorCopyBackward(cRibbonFacePoly* first, cRibbonFacePoly* last, cRibbonFacePoly* destEnd); // 0xfb65f0
cRibbonFacePoly* CopyIntoSlot(cRibbonFacePoly** slot, cRibbonFacePoly* first, cRibbonFacePoly* last,
                              cRibbonFacePoly* dest);                                                        // 0xfb6690
cRibbonFacePoly* UninitializedCopy(cRibbonFacePoly* first, cRibbonFacePoly* last, cRibbonFacePoly* dest);     // 0xfa9b10
cRibbonFacePoly* DestructElements(cRibbonFacePoly* first, cRibbonFacePoly* last, cRibbonFacePoly* dest);      // 0xfa1b10
void*            EAAllocate(uint32_t bytes, const char* name, int a3, int a4, int tag, int line);             // 0xf473a0
void             EAFree(void* p);                                                                             // 0xf47380

// eastl::vector<cRibbonFacePoly, sp_vector_allocator> -- the quad's ribbon polygon cache.
struct PolyVector
{
    cRibbonFacePoly* mpBegin;
    cRibbonFacePoly* mpEnd;
    cRibbonFacePoly* mpCapacity;
    uint32_t         mAllocator;

    PolyVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}

    int size() const            { return (int)(mpEnd - mpBegin); }
    int capacity_count() const  { return (int)(mpCapacity - mpBegin); }

    void  reserve(int n);                                                       // 0xfb7310
    void  DestructRange(cRibbonFacePoly* first, cRibbonFacePoly* last);          // 0xfa2620
    void  DoInsertValue(cRibbonFacePoly* pos, const cRibbonFacePoly& v);         // 0xfab0e0
    cRibbonFacePoly* DoAllocate(int n, cRibbonFacePoly* first, cRibbonFacePoly* last); // 0xfb6f50
    __declspec(noinline) void  insert(cRibbonFacePoly* pos, const cRibbonFacePoly* first,
                                      const cRibbonFacePoly* last, const PolyVector& tag); // 0xfb6fb0
    __declspec(noinline) PolyVector& operator=(const PolyVector& other);         // 0xfb71c0

    void push_back(const cRibbonFacePoly& v)
    {
        if (mpEnd < mpCapacity)
            ::new ((void*)mpEnd++) cRibbonFacePoly(v);
        else
            DoInsertValue(mpEnd, v);
    }

    // eastl::vector::erase -- copy the tail down, destroy the vacated elements,
    // then walk the end pointer back by the erased element count.
    void erase(cRibbonFacePoly* first, cRibbonFacePoly* last)
    {
        cRibbonFacePoly* newEnd = VectorCopy(last, mpEnd, first);
        DestructRange(newEnd, mpEnd);
        mpEnd -= (last - first);
    }
};

// eastl::vector<cRibbonUnmorphedVert, sp_vector_allocator> -- the quad's vertex cache.
struct VertVector
{
    cRibbonUnmorphedVert* mpBegin;
    cRibbonUnmorphedVert* mpEnd;
    cRibbonUnmorphedVert* mpCapacity;
    uint32_t              mAllocator;

    void erase(cRibbonUnmorphedVert* first, cRibbonUnmorphedVert* last);   // 0x9c69f0
};

// ---------------------------------------------------------------------------
// cTerrainSphere / quad
// ---------------------------------------------------------------------------
struct cTerrainSphereInfo;

class cTerrainSphere
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* GetMapSet();                 // +0x0c
    virtual cTerrainSphereInfo* GetInfo();     // +0x10
    uint32_t GetQuadKeyA(int face);            // 0xf98260
    uint32_t GetQuadKeyB(int face);            // 0xf98270
    uint32_t GetQuadKeyC(int face);            // 0xf98280
    uint32_t GetQuadKeyX(int face);            // 0xf96910
    uint32_t GetQuadKeyY();                    // 0xf96a00
};

class cTerrainSphereQuad
{
public:
    cTerrainSphere*      mSphere;          // +0x000
    cTerrainSphereQuad*  mParent;          // +0x004
    cTerrainSphereQuad*  mChildren[4];     // +0x008
    int                  mChunkRes;        // +0x018
    int                  mFace;            // +0x01c
    cSPVector2           mFaceMin;         // +0x020
    cSPVector2           mFaceMax;         // +0x028
    float                mFaceScale;       // +0x030
    char                 mPad34[0x6c - 0x34];
    bool                 mAtmosphereQuad;  // +0x06c
    char                 mPad6d[0x90 - 0x6d];
    bool                 mDirtyVertices;   // +0x090
    bool                 mDirtyIndices;    // +0x091
    char                 mPad92[0x94 - 0x92];
    void*                mVertexBuffer;    // +0x094
    int                  mNumA;            // +0x098
    int                  mNumB;            // +0x09c
    int                  mNumC;            // +0x0a0
    char                 mPadA4[0x18c - 0xa4];
    PolyVector           mRibbonPolys;     // +0x18c (0x10 bytes)
    uint32_t             mPad19c;          // +0x19c
    VertVector           mRibbonVerts;     // +0x1a0

    void RebuildVertices();                                        // 0xfb6630
    int  DispatchA(int viewer, DispatchStats* stats, int);         // 0xfb66d0
    int  DispatchB(int viewer, DispatchStats* stats, int idx, int); // 0xfb6850
    int  DispatchC(int viewer, DispatchStats* stats, int);         // 0xfb6cd0
    int  DispatchD(int viewer, DispatchStats* stats, int);         // 0xfb6e00
    void SetRibbonGeometryOnChildren();                            // 0xfb75b0
    void AddRibbonGeometryToChildren(const PolyVector& polys);     // 0xfb7640

    bool RebuildHeightVB();                                        // 0xfb0e00
    bool RebuildAtmosphereVertices();                              // 0xfaf220
    void SetupShaderData(int viewer);                              // 0xfb1780
    void RebuildIndices();                                         // 0xfb43b0
    void DispatchMesh(void* vb, void* ib, int start, int count);    // 0xfaef10
    void BuildRibbonVerts(const PolyVector& polys);                // 0xfb50d0 (other slice)
};

// free cdecl helpers -- separate out-of-line functions in retail (call sites exist),
// so keep the compiler from auto-inlining them into the callers.
__declspec(noinline) void AddPolysInRect(const PolyVector& src, float minX, float minY, float maxX, float maxY, PolyVector& dst); // 0xfb73d0
__declspec(noinline) void SetPolysInRect(const PolyVector& src, float minX, float minY, float maxX, float maxY, PolyVector& dst); // 0xfb7530

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------
struct CachedQuadState { int mIndex; int mFace; };
extern CachedQuadState sCachedQuad;       // 0x15b1538 (mIndex +0x00, mFace +0x04)
#define sCachedIndex sCachedQuad.mIndex
#define sCachedFace  sCachedQuad.mFace
extern void* g_pIndexBuffer;              // 0x16c9e34
extern cTextureInstance* g_pTextureInstance;   // 0x16c9f58
extern uint32_t g_ribbonEps;              // 0x14910f4 (1.52587890625e-05f)

void* GetTerrainManager();                // 0x16c8eac -> 0xf48a60

// ===========================================================================
// @ 0x00fb6630
void cTerrainSphereQuad::RebuildVertices()
{
    if (mAtmosphereQuad)
    {
        if (RebuildAtmosphereVertices())
            mDirtyVertices = false;
        return;
    }
    if (!RebuildHeightVB())
        return;
    mRibbonVerts.erase(mRibbonVerts.mpBegin, mRibbonVerts.mpEnd);
    BuildRibbonVerts(mRibbonPolys);
    mDirtyVertices = false;
}

// ===========================================================================
// @ 0x00fb66d0
int cTerrainSphereQuad::DispatchA(int viewer, DispatchStats* stats, int)
{
    if (mDirtyVertices)
        RebuildVertices();
    if (mDirtyIndices)
        RebuildIndices();
    if (mNumA <= 0)
        return 0;

    SetupShaderData(viewer);
    GetTerrainManager();
    RasterState rasters[8];

    if (sCachedIndex != 0 || mFace != sCachedFace)
    {
        sCachedFace = mFace;
        sCachedIndex = 0;
        void* mgr = GetTerrainManager();
        void* slot = *(void**)((char*)mgr + 0x5c);
        if (slot)
        {
            void* st = *(void**)((char*)slot + 4);
            if (st)
            {
                char* vr = (char*)mSphere->GetInfo() + 0x2f4;
                rasters[0].Assign(st, 0, mSphere->GetQuadKeyB(mFace));
                rasters[1].Assign(st, 1, *(uint32_t*)*(void**)(vr + 0xc));
                rasters[2].Assign(st, 2, mSphere->GetQuadKeyX(mFace));
                rasters[3].Assign(st, 3, *(uint32_t*)g_pTextureInstance);
                ((CompiledState*)st)->Dispatch();
            }
        }
    }

    DispatchMesh(*(void**)mVertexBuffer, *(void**)((char*)mVertexBuffer + 4), 0, mNumA);
    stats->mField20 += *(int*)((char*)*(void**)mVertexBuffer + 0xc);
    stats->mField24 += mNumA;
    stats->mField28++;
    return 0;
}

// ===========================================================================
// @ 0x00fb6850
int cTerrainSphereQuad::DispatchB(int viewer, DispatchStats* stats, int idx, int)
{
    if (mDirtyVertices)
        RebuildVertices();
    if (mDirtyIndices)
        RebuildIndices();
    if (mNumB <= 0)
        return 0;

    SetupShaderData(viewer);
    GetTerrainManager();
    RasterState rasters[8];

    if (sCachedIndex != idx || mFace != sCachedFace)
    {
        sCachedFace = mFace;
        sCachedIndex = idx;
        void* mgr = GetTerrainManager();
        void* slot = *(void**)((char*)mgr + 0x5c + idx * 4);
        if (slot)
        {
            void* st = *(void**)((char*)slot + 4);
            if (st)
            {
                char* vr = (char*)mSphere->GetInfo() + 0x2f4;
                switch (idx)
                {
                case 0:
                    rasters[0].Assign(st, 0, mSphere->GetQuadKeyB(mFace));
                    rasters[1].Assign(st, 1, *(uint32_t*)*(void**)(vr + 0xc));
                    rasters[2].Assign(st, 2, mSphere->GetQuadKeyX(mFace));
                    rasters[3].Assign(st, 3, *(uint32_t*)g_pTextureInstance);
                    break;
                case 1:
                    rasters[0].Assign(st, 0, mSphere->GetQuadKeyB(mFace));
                    rasters[1].Assign(st, 1, mSphere->GetQuadKeyA(mFace));
                    rasters[2].Assign(st, 2, mSphere->GetQuadKeyX(mFace));
                    break;
                case 2:
                    rasters[0].Assign(st, 0, mSphere->GetQuadKeyA(mFace));
                    rasters[1].Assign(st, 1, *(uint32_t*)*(void**)(vr + 4));
                    rasters[2].Assign(st, 2, *(uint32_t*)*(void**)(vr + 0));
                    rasters[3].Assign(st, 3, *(uint32_t*)*(void**)(vr + 8));
                    rasters[4].Assign(st, 4, *(uint32_t*)g_pTextureInstance);
                    rasters[5].Assign(st, 5, mSphere->GetQuadKeyY());
                    break;
                case 3:
                    rasters[0].Assign(st, 0, mSphere->GetQuadKeyB(mFace));
                    rasters[1].Assign(st, 1, mSphere->GetQuadKeyA(mFace));
                    rasters[2].Assign(st, 2, *(uint32_t*)*(void**)(vr + 0x18));
                    rasters[3].Assign(st, 3, *(uint32_t*)*(void**)(vr + 0x10));
                    rasters[4].Assign(st, 4, *(uint32_t*)*(void**)(vr + 4));
                    rasters[5].Assign(st, 5, *(uint32_t*)*(void**)(vr + 0x14));
                    rasters[6].Assign(st, 6, *(uint32_t*)*(void**)(vr + 8));
                    rasters[7].Assign(st, 7, *(uint32_t*)g_pTextureInstance);
                    break;
                case 4:
                    rasters[0].Assign(st, 0, mSphere->GetQuadKeyB(mFace));
                    rasters[1].Assign(st, 1, mSphere->GetQuadKeyA(mFace));
                    rasters[2].Assign(st, 2, *(uint32_t*)*(void**)(vr + 0x10));
                    rasters[3].Assign(st, 3, *(uint32_t*)*(void**)(vr + 0x1c));
                    rasters[4].Assign(st, 4, *(uint32_t*)*(void**)(vr + 0x24));
                    rasters[5].Assign(st, 5, *(uint32_t*)*(void**)(vr + 0x20));
                    rasters[6].Assign(st, 6, *(uint32_t*)g_pTextureInstance);
                    break;
                case 5:
                    rasters[0].Assign(st, 0, *(uint32_t*)g_pTextureInstance);
                    rasters[1].Assign(st, 1, *(uint32_t*)*(void**)(vr + 0x30));
                    break;
                case 6:
                case 7:
                case 8:
                case 9:
                    rasters[0].Assign(st, 0, mSphere->GetQuadKeyB(mFace));
                    rasters[1].Assign(st, 1, 0);
                    rasters[2].Assign(st, 2, (uint32_t)g_pTextureInstance->GetRaster());
                    break;
                case 10:
                {
                    uint32_t arr[5];
                    arr[0] = 0;
                    arr[1] = mSphere->GetQuadKeyA(mFace);
                    arr[2] = mSphere->GetQuadKeyB(mFace);
                    arr[3] = mSphere->GetQuadKeyC(mFace);
                    arr[4] = mSphere->GetQuadKeyX(mFace);
                    rasters[0].Assign(st, 0, arr[*(int*)((char*)GetTerrainManager() + 8)]);
                    break;
                }
                default:
                    break;
                }
                ((CompiledState*)st)->Dispatch();
            }
        }
    }

    DispatchMesh(*(void**)mVertexBuffer, *(void**)((char*)mVertexBuffer + 4), mNumC - mNumB, mNumB);
    stats->mField20 += *(int*)((char*)*(void**)mVertexBuffer + 0xc);
    stats->mField24 += mNumB;
    stats->mField28++;
    return 0;
}

// ===========================================================================
// @ 0x00fb6cd0
int cTerrainSphereQuad::DispatchC(int viewer, DispatchStats* stats, int)
{
    if (mDirtyVertices)
        RebuildVertices();
    if (mDirtyIndices)
        RebuildIndices();

    SetupShaderData(viewer);
    RasterState rasters[8];

    if (sCachedIndex != 5 || mFace != sCachedFace)
    {
        sCachedFace = mFace;
        sCachedIndex = 5;
        void* mgr = GetTerrainManager();
        void* slot = *(void**)((char*)mgr + 0x70);
        if (slot)
        {
            void* st = *(void**)((char*)slot + 4);
            if (st)
            {
                char* vr = (char*)mSphere->GetInfo() + 0x2f4;
                rasters[0].Assign(st, 0, *(uint32_t*)g_pTextureInstance);
                rasters[1].Assign(st, 1, *(uint32_t*)*(void**)(vr + 0x30));
                ((CompiledState*)st)->Dispatch();
            }
        }
    }

    DispatchMesh(*(void**)mVertexBuffer, g_pIndexBuffer, 0, *(int*)((char*)g_pIndexBuffer + 8));
    stats->mField20 += *(int*)((char*)*(void**)mVertexBuffer + 0xc);
    stats->mField24 += *(int*)((char*)g_pIndexBuffer + 8);
    stats->mField28++;
    return 0;
}

// ===========================================================================
// @ 0x00fb6e00
int cTerrainSphereQuad::DispatchD(int viewer, DispatchStats* stats, int)
{
    if (mDirtyVertices)
        RebuildVertices();
    if (mDirtyIndices)
        RebuildIndices();

    SetupShaderData(viewer);
    RasterState rasters[8];

    if (sCachedIndex != 1 || mFace != sCachedFace)
    {
        sCachedFace = mFace;
        sCachedIndex = 1;
        void* mgr = GetTerrainManager();
        void* slot = *(void**)((char*)mgr + 0x60);
        if (slot)
        {
            void* st = *(void**)((char*)slot + 4);
            if (st)
            {
                (void)mSphere->GetInfo();
                rasters[0].Assign(st, 0, mSphere->GetQuadKeyB(mFace));
                rasters[1].Assign(st, 1, mSphere->GetQuadKeyA(mFace));
                rasters[2].Assign(st, 2, mSphere->GetQuadKeyX(mFace));
                ((CompiledState*)st)->Dispatch();
            }
        }
    }

    DispatchMesh(*(void**)mVertexBuffer, *(void**)((char*)mVertexBuffer + 4), 0, mNumC);
    stats->mField20 += *(int*)((char*)*(void**)mVertexBuffer + 0xc);
    stats->mField24 += mNumC;
    stats->mField28++;
    return 0;
}

// ===========================================================================
// @ 0x00fb6fb0
void PolyVector::insert(cRibbonFacePoly* position, const cRibbonFacePoly* first,
                        const cRibbonFacePoly* last, const PolyVector&)
{
    if (first == last)
        return;

    const int n = (int)(last - first);
    const int nAfter = (int)(mpEnd - position);

    if (n <= (int)(mpCapacity - mpEnd))
    {
        if (n >= nAfter)
        {
            // Fill the tail with the surviving suffix, then copy the leading run down.
            cRibbonFacePoly* oldEnd = mpEnd;
            UninitializedCopy((cRibbonFacePoly*)position, oldEnd, position + n);
            VectorCopy((cRibbonFacePoly*)first, (cRibbonFacePoly*)first + nAfter, position);
            UninitializedCopy((cRibbonFacePoly*)first + nAfter, (cRibbonFacePoly*)last, oldEnd);
            mpEnd += n;
        }
        else
        {
            cRibbonFacePoly* pOldEnd = mpEnd;
            UninitializedCopy(pOldEnd - n, pOldEnd, pOldEnd);
            mpEnd = pOldEnd + n;
            VectorCopyBackward(position, pOldEnd - n, mpEnd);
            VectorCopy((cRibbonFacePoly*)first, (cRibbonFacePoly*)last, position);
        }
        return;
    }

    // Not enough room: reallocate.
    const int oldSize = (int)(mpEnd - mpBegin);
    int newCap = oldSize * 2;
    if (newCap == 0)
        newCap = 1;
    const int total = oldSize + n;
    const int cap = (newCap < total) ? total : newCap;

    cRibbonFacePoly* newBuf = 0;
    if (cap)
        newBuf = (cRibbonFacePoly*)EAAllocate((uint32_t)cap * 0x110u, "Simulator", 0, 0, 0x13ebb38, 0xd1);

    cRibbonFacePoly* newEnd = UninitializedCopy(mpBegin, position, newBuf);
    DestructElements(mpBegin, position, newBuf);

    cRibbonFacePoly* slot = newEnd;
    CopyIntoSlot(&slot, (cRibbonFacePoly*)first, (cRibbonFacePoly*)last, newEnd);

    cRibbonFacePoly* tailEnd = UninitializedCopy(position, mpEnd, slot);
    DestructElements(position, mpEnd, slot);

    if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
        EAFree(mpBegin);

    mpEnd = tailEnd;
    mpBegin = newBuf;
    mpCapacity = newBuf + cap;
}

// ===========================================================================
// @ 0x00fb71c0
PolyVector& PolyVector::operator=(const PolyVector& other)
{
    if (this == &other)
        return *this;

    const int n = other.size();

    if (capacity_count() < n)
    {
        cRibbonFacePoly* newBuf = DoAllocate(n, other.mpBegin, other.mpEnd);
        DestructRange(mpBegin, mpEnd);
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            EAFree(mpBegin);
        mpBegin = newBuf;
        mpEnd = newBuf + n;
        mpCapacity = newBuf + n;
        return *this;
    }

    if (size() < n)
    {
        VectorCopy(other.mpBegin, other.mpBegin + size(), mpBegin);
        cRibbonFacePoly* slot = mpEnd;
        CopyIntoSlot(&slot, other.mpBegin + size(), other.mpEnd, mpEnd);
        mpEnd = mpBegin + n;
        return *this;
    }

    cRibbonFacePoly* newEnd = VectorCopy(other.mpBegin, other.mpEnd, mpBegin);
    DestructRange(newEnd, mpEnd);
    mpEnd = mpBegin + n;
    return *this;
}

// ===========================================================================
// @ 0x00fb73d0
void AddPolysInRect(const PolyVector& src, float minX, float minY, float maxX, float maxY, PolyVector& dst)
{
    dst.reserve(src.size() + dst.size());

    const float eps = 1.52587890625e-05f;
    const float loX = minX - eps;
    const float loY = minY - eps;
    const float hiX = maxX + eps;
    const float hiY = maxY + eps;

    for (int i = 0; i < src.size(); i++)
    {
        const cRibbonFacePoly& p = src.mpBegin[i];
        if (hiX >= p.mMinX && p.mMaxX >= loX && hiY >= p.mMinY && p.mMaxY >= loY)
            dst.push_back(p);
    }
}

// ===========================================================================
// @ 0x00fb7530
void SetPolysInRect(const PolyVector& src, float minX, float minY, float maxX, float maxY, PolyVector& dst)
{
    dst.erase(dst.mpBegin, dst.mpEnd);
    AddPolysInRect(src, minX, minY, maxX, maxY, dst);
}

// ===========================================================================
// @ 0x00fb75b0
void cTerrainSphereQuad::SetRibbonGeometryOnChildren()
{
    mRibbonVerts.erase(mRibbonVerts.mpBegin, mRibbonVerts.mpEnd);
    BuildRibbonVerts(mRibbonPolys);

    if (mChildren[0] && mRibbonPolys.mpBegin != mRibbonPolys.mpEnd)
    {
        for (int i = 0; i < 4; i++)
        {
            cTerrainSphereQuad* child = mChildren[i];
            SetPolysInRect(mRibbonPolys, child->mFaceMin.x, child->mFaceMin.y,
                           child->mFaceMax.x, child->mFaceMax.y, child->mRibbonPolys);
            child->SetRibbonGeometryOnChildren();
        }
    }
}

// ===========================================================================
// @ 0x00fb7640
void cTerrainSphereQuad::AddRibbonGeometryToChildren(const PolyVector& polys)
{
    BuildRibbonVerts(polys);

    if (mChildren[0] && mRibbonPolys.mpBegin != mRibbonPolys.mpEnd)
    {
        PolyVector local;
        for (int i = 0; i < 4; i++)
        {
            cTerrainSphereQuad* child = mChildren[i];
            SetPolysInRect(polys, child->mFaceMin.x, child->mFaceMin.y,
                           child->mFaceMax.x, child->mFaceMax.y, local);
            child->mRibbonPolys.insert(child->mRibbonPolys.mpEnd, local.mpBegin, local.mpEnd, polys);
            child->AddRibbonGeometryToChildren(local);
        }
        local.DestructRange(local.mpBegin, local.mpEnd);
        if (local.mpBegin && *(int*)((char*)local.mpBegin - 4) != 0)
            EAFree(local.mpBegin);
    }
}
