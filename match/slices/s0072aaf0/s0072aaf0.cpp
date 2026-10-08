// Slice s0072aaf0 — SP::cTriToRegionMap and mesh streaming helpers.
//   AddRegion reconstructed; the rest are partial.
#include "types.h"
#include <intrin.h>
#include <string.h>

void operator_delete(void* p);   // 0x00f47380

extern "C" {
    void* FUN_00f473a0(unsigned size, const char* name, int f, int df, const char* file, int line);
    void  FUN_007409d0(void* pos, void* value);
    void  FUN_0072a1a0();
    void  FUN_0072aa80();
}

struct TriRegionEntry {
    int mRegionId;   // +0
    int mBegin;      // +4
    int mEnd;        // +8
};

struct TriRegionVec {
    TriRegionEntry* mpBegin;
    TriRegionEntry* mpEnd;
    TriRegionEntry* mpCap;
};

struct cTriToRegionMap {
    TriRegionVec mRegions;
    void AddRegion(int begin, int end, int id);
};

// @ 0x0072b560  SP::cTriToRegionMap::AddRegion
void cTriToRegionMap::AddRegion(int param_2, int param_3, int param_4)
{
    if (param_4 != -1) {
    if (param_2 != param_3) {
        TriRegionEntry* p   = mRegions.mpBegin;
        TriRegionEntry* end = mRegions.mpEnd;
        int n = ((int)end - (int)p) / 0xc;
        int i = 0;
        if (0 < n) {
            do {
                if (p->mRegionId == param_4) {
                    if (p->mBegin == param_3) {
                        p->mBegin = param_2;
                        return;
                    }
                    if (p->mEnd == param_2) {
                        p->mEnd = param_3;
                        return;
                    }
                }
                i++;
                p++;
            } while (i < n);
        }

        TriRegionEntry tmp;
        tmp.mBegin = param_2;
        tmp.mEnd = param_3;
        tmp.mRegionId = param_4;
        if (end < mRegions.mpCap) {
            mRegions.mpEnd = end + 1;
            if (end != 0) {
                end->mRegionId = param_4;
                end->mBegin = param_2;
                end->mEnd = param_3;
                return;
            }
        } else {
            FUN_007409d0(end, &tmp);
        }
    }
    }
}

// @ 0x0072ac10  (PARTIAL)
void FUN_0072ac10(void* a, void* b)
{
    (void)a; (void)b;
}

// @ 0x0072ac60  (PARTIAL: refcounted ctor with EH)
void FUN_0072ac60(void* a, int b)
{
    (void)a; (void)b;
}

// @ 0x0072aaf0  (PARTIAL: vector insert with EH)
void FUN_0072aaf0(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// @ 0x0072ace0  SP::StreamMeshToRw
// Streams one SourceMesh (vertex elements, sub-meshes, primitive groups) into RenderWare:
// per sub-mesh it builds a vertex descriptor from the usable elements, then for every
// primitive group of that sub-mesh draws the triangles in index-buffer-sized chunks.
struct IRefObject {                       // virtual AddRef/Release (slots 0/1)
    virtual int AddRef();
    virtual int Release();
};

void operator_delete__(void* p) throw();  // 0x00f47380

template <typename T>
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    int size() const { return (int)(mpEnd - mpBegin); }
};

template <typename T, int N>
struct fixed_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mOverflow;
    T* mpPoolBegin;
    uint32_t mPad;
    T mBuffer[N];

    fixed_vector() {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + N;
        mpPoolBegin = mBuffer;
    }
    ~fixed_vector() {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator_delete__(mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    void DoInsertValue(T* position, const T& value);
    void push_back(const T& value) {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            if (p) *p = value;
        } else
            DoInsertValue(mpEnd, value);
    }
};

extern const uint32_t kIndexMasks[];     // 0x0140d15c
struct DataAccessor {
    int         mCount;                  // +0x0
    char*       mpData;                  // +0x4
    uint16_t    mFormat;                 // +0x8  (element byte size / index width)
    uint16_t    mStride;                 // +0xa
    IRefObject* mpOwner;                 // +0xc

    DataAccessor() : mCount(0), mpData(0), mFormat(4), mStride(4), mpOwner(0) {}
    ~DataAccessor() { if (mpOwner) mpOwner->Release(); }
    __forceinline DataAccessor& operator=(const DataAccessor& x) {
        IRefObject* p = x.mpOwner;
        mCount = x.mCount;
        mpData = x.mpData;
        mFormat = x.mFormat;
        mStride = x.mStride;
        if (p != mpOwner) {
            if (p) p->AddRef();
            IRefObject* old = mpOwner;
            mpOwner = p;
            if (old) old->Release();
        }
        return *this;
    }
    uint32_t Index(int i) const { return *(uint32_t*)(mpData + mStride * i) & kIndexMasks[mFormat]; }
};

struct MeshElement {                     // 0x20
    int          mSemantic;              // +0x00
    int          mSemanticIndex;         // +0x04
    int          mDataType;              // +0x08
    int          mStream;                // +0x0c
    DataAccessor mData;                  // +0x10
};
struct ElementRef { int16_t mElement; int16_t mIndexTable; };
struct SubMesh {                         // 0x8c
    DataAccessor         mIndices;       // +0x00
    int                  mVertexCount;   // +0x10
    vector<ElementRef>   mElements;      // +0x14
    uint32_t             pad24[8];       // +0x24
    vector<DataAccessor> mIndexTables;   // +0x44
    uint32_t             pad54[14];      // +0x54
};
struct PrimitiveGroup {                  // 0x14
    int mPrimType;
    int mSubMesh;
    int mStart;
    int mEnd;
    int mMaterial;
};
struct SourceMesh {
    uint32_t                pad0[2];
    MeshElement*            mpElements;  // +0x08
    uint32_t                padC[4];
    vector<SubMesh>         mSubMeshes;  // +0x1c
    uint32_t                pad2C;
    vector<PrimitiveGroup>  mPrims;      // +0x30
};

struct VertexElement { uint16_t stream, offset; uint8_t type, method, usage, usageIndex; int rwDecl; };
struct VertexDescription {
    void*    pNextParent;
    void*    pNextSibling;
    void*    pDXDecl;
    uint16_t elementsCount;
    uint8_t  lockFlags;                  // +0x0e
    uint8_t  stride;                     // +0x0f
    int      elementsUsed;
    int      elementsHash;
    VertexElement elements[1];           // +0x18
    void Finalize();                     // 0x011f3220
};
struct BuildState {
    void SetField1230(int a, int b);                       // 0x011f9c10
    void D3D9SetVertexDescriptor(VertexDescription* d, int flags);   // 0x011f9e20
};
struct ShaderDataItem {
    char pad[8];
    void Push();                                           // 0x007789d0
};
struct EmbeddedState {
    char pad00[8];
    uint32_t mSoftStateDirty;                              // +0x08
    int* D3D9GetShaderData(int id);                        // 0x011edcf0
    void Dispatch();                                       // 0x011ee580
};
struct Material { int pad; EmbeddedState* mpState; };
struct IMaterialManager {
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1c();
    virtual void f20(); virtual void f24();
    virtual Material* GetMaterial(uint32_t id);            // +0x28
};
struct ShaderMapEntry { int key; ShaderDataItem* value; };
struct ShaderMap { ShaderMapEntry* mpBegin; ShaderMapEntry* mpEnd; };
struct DrawStats { char pad[0x20]; int mVerts; int pad24; int mBatches; };

extern int  FindElement(SourceMesh* mesh, int semantic, int index, int a, int b);  // 0x0071ddc0
extern VertexDescription* CreateVertexDescriptor(int n);                          // 0x00761650
extern BuildState* CreateVertexBuffer(unsigned flags, int b);                     // 0x007616f0
extern void* CreateCompiledState(BuildState* bs);                                 // 0x007617a0
extern IMaterialManager* MaterialManager();                                       // 0x0067dd70
extern int  ToD3DDeclType(int type);                                              // 0x00729560
extern int  ToRwDecl(int semantic, int index);                                    // 0x007295f0
extern void DestroyBuildState(BuildState* p);                                     // 0x00761150
extern void DestroyVertexDescriptor(VertexDescription* p);                        // 0x00761130
extern void ReleaseObject(void* p);                                               // 0x00761170
extern void CompiledStateBegin(void* cs, void* unused);                           // 0x011fd7b0
extern void* LockIndexSpan(int n);                                                // 0x011fd7e0
extern void UnlockIndexSpan();                                                    // 0x011fd820
extern void IndexSpanEnd();                                                       // 0x011fd7d0
extern void PushShaderDataNull();                                                 // 0x00777bf0
extern void SetShaderData(EmbeddedState* s);                                      // 0x00777b50
extern void PopShaderData();                                                      // 0x00777c10
extern void SetVertexDescriptor(VertexDescription* d);                            // 0x007611a0
extern int  VertexDescriptorAreEqual(VertexDescription* a, VertexDescription* b); // 0x011f2e70
extern void D3D9Sync();                                                           // 0x011f21a0
extern const int kRwPrimTypes[];         // 0x01536f0c
extern int gActivePrimType;              // 0x016f85a8
extern VertexDescription* gActiveVertexDesc;   // 0x016f65a0
extern unsigned gSoftStateUpdated;       // 0x016f9110
struct VDescRefresh { void Refresh(); };  // 0x011f2bc0 (thiscall)

// @ 0x0072ace0  SP::StreamMeshToRw
namespace SP {
void StreamMeshToRw(SourceMesh* mesh, DrawStats* stats, ShaderDataItem* extraPush,
                    ShaderMap* shaderMap, int materialId, EmbeddedState* state)
{
    DataAccessor materials;
    EmbeddedState* defaultState = 0;
    if (state) {
        defaultState = state;
    } else if (materialId) {
        defaultState = MaterialManager()->GetMaterial(materialId)->mpState;
    } else {
        bool lookup = true;
        int idx = FindElement(mesh, 0x15, 0, 6, 0xe);
        if (idx >= 0) {
            materials = mesh->mpElements[idx].mData;
            if (materials.mpData)
                lookup = false;
        }
        if (lookup)
            defaultState = MaterialManager()->GetMaterial((uint32_t)0x9f84a565)->mpState;
    }

    int numSubMeshes = mesh->mSubMeshes.size();
    for (int subIdx = 0; subIdx < numSubMeshes; ++subIdx) {
        SubMesh* sub = &mesh->mSubMeshes.mpBegin[subIdx];
        fixed_vector<int, 16> rwDecls;
        fixed_vector<int, 16> d3dTypes;
        fixed_vector<ElementRef, 16> refs;

        int numRefs = sub->mElements.size();
        for (int j = 0; j < numRefs; ++j) {
            MeshElement* e = &mesh->mpElements[mesh->mSubMeshes.mpBegin[subIdx].mElements.mpBegin[j].mElement];
            int d3d = ToD3DDeclType(e->mDataType);
            int rw = ToRwDecl(e->mSemantic, e->mSemanticIndex);
            if (rw != -1 && d3d != -1 && e->mStream < 4) {
                rwDecls.push_back(rw);
                d3dTypes.push_back(d3d);
                refs.push_back(sub->mElements.mpBegin[j]);
            }
        }
        if (rwDecls.mpBegin == rwDecls.mpEnd)
            continue;

        int numElems = rwDecls.size();
        VertexDescription* vd = CreateVertexDescriptor(numElems);
        vd->lockFlags |= 2;
        for (int k = 0; k < rwDecls.size(); ++k) {
            vd->elements[k].rwDecl = rwDecls.mpBegin[k];
            vd->elements[k].type = (uint8_t)d3dTypes.mpBegin[k];
        }
        vd->Finalize();
        BuildState* bs = CreateVertexBuffer(0x80000002, 0);
        bs->SetField1230(4, 0);
        bs->D3D9SetVertexDescriptor(vd, 0);
        void* compiled = CreateCompiledState(bs);
        DestroyBuildState(bs);

        int numPrims = mesh->mPrims.size();
        for (int pi = 0; pi < numPrims; ++pi) {
            PrimitiveGroup* prim = &mesh->mPrims.mpBegin[pi];
            if (prim->mSubMesh != subIdx)
                continue;
            EmbeddedState* mat = defaultState;
            if (materials.mpData)
                mat = MaterialManager()->GetMaterial(*(uint32_t*)(materials.mpData + materials.mStride * prim->mMaterial))->mpState;
            int primType = kRwPrimTypes[prim->mPrimType];
            int scratch;
            CompiledStateBegin(compiled, &scratch);
            PushShaderDataNull();
            SetShaderData(mat);
            mat->Dispatch();
            if (shaderMap && mat && (mat->mSoftStateDirty & 8)) {
                int* data = mat->D3D9GetShaderData(0x20f);
                if (data) {
                    ShaderMapEntry* first = shaderMap->mpBegin;
                    ShaderMapEntry* last = shaderMap->mpEnd;
                    int n = (int)(last - first);
                    while (n > 0) {
                        int half = n >> 1;
                        if (first[half].key < *data) {
                            first += half + 1;
                            n -= half + 1;
                        } else
                            n = half;
                    }
                    if (first == last || *data < first->key)
                        first = last;
                    else if (first == first + 1)
                        first = last;
                    if (first != last && first->value)
                        first->value->Push();
                }
            }
            if (extraPush)
                extraPush->Push();
            gActivePrimType = primType;
            if (!gActiveVertexDesc || !VertexDescriptorAreEqual(gActiveVertexDesc, vd))
                gSoftStateUpdated |= 0x100000;
            gActiveVertexDesc = vd;
            ((VDescRefresh*)vd)->Refresh();
            SetVertexDescriptor(vd);
            D3D9Sync();

            int maxChunk = 0x8000 / vd->stride;
            int remaining = prim->mEnd - prim->mStart;
            int cur = prim->mStart;
            while (remaining > 0) {
                int chunk = ((remaining < maxChunk ? remaining : maxChunk) / 3) * 3;
                char* dst = (char*)LockIndexSpan(chunk);
                if (dst) {
                    int end = cur + chunk;
                    if (sub->mIndexTables.mpBegin == sub->mIndexTables.mpEnd) {
                        for (int k = cur; k < end; ++k) {
                            uint32_t idx = sub->mIndices.Index(k);
                            int nref = refs.size();
                            for (int j = 0; j < nref; ++j) {
                                MeshElement* e = &mesh->mpElements[refs.mpBegin[j].mElement];
                                int size = e->mData.mFormat;
                                memcpy(dst, e->mData.mpData + e->mData.mStride * idx, size);
                                dst += size;
                            }
                        }
                    } else {
                        for (int k = cur; k < end; ++k) {
                            uint32_t idx = sub->mIndices.Index(k);
                            int nref = refs.size();
                            for (int j = 0; j < nref; ++j) {
                                MeshElement* e = &mesh->mpElements[refs.mpBegin[j].mElement];
                                uint32_t tidx = sub->mIndexTables.mpBegin[refs.mpBegin[j].mIndexTable].Index(idx);
                                int size = e->mData.mFormat;
                                memcpy(dst, e->mData.mpData + e->mData.mStride * tidx, size);
                                dst += size;
                            }
                        }
                    }
                    UnlockIndexSpan();
                }
                stats->mVerts += chunk;
                stats->mBatches++;
                remaining -= chunk;
                cur += chunk;
            }
            PopShaderData();
            IndexSpanEnd();
        }
        DestroyVertexDescriptor(vd);
        ReleaseObject(compiled);
    }
}
} // namespace SP
