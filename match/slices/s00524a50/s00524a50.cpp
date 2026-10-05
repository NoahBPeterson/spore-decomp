// nSPSkinner::cPaintSystem::BuildMeshJobCallback (unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE).
// One block of the source model is appended per job invocation; the job's slot is advanced and the
// callback reschedules itself through SP::cJob::Continuation.
#include "types.h"

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}

// ---------------------------------------------------------------- vector helpers
struct sp_vector_allocator {
    uint32_t mFlags[2];
};

template <typename T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
};

struct VectorU32 : VectorBase<uint32_t> {
    typedef uint32_t size_type;
    void resize(size_type n, const uint32_t& value);   // 0x004746c0
    void resize(size_type n);                          // 0x004cd3c0
    uint32_t* erase(uint32_t* first, uint32_t* last);  // 0x004769b0
    void clear() { erase(mpBegin, mpEnd); }
    uint32_t& operator[](size_type i) { return mpBegin[i]; }
};

struct cSPVector2 {
    float x, y;
    float& operator[](int i) { return (&x)[i]; }
};
struct VectorVec2 : VectorBase<cSPVector2> {
    typedef uint32_t size_type;
    cSPVector2& operator[](size_type i) { return mpBegin[i]; }
};

// 0x0c-byte element (used by the cMesh +8 array)
struct ElemC {
    uint32_t data[3];
};
struct VectorElemC : VectorBase<ElemC> {
    typedef uint32_t size_type;
};

// ---------------------------------------------------------------- refcount bases
struct DefaultRefCounted {
    void* vtbl;
    int mnRefCount;
    void AddRef();
    void Release();
};

// ---------------------------------------------------------------- rig model
struct cRigBlock {              // 0x8c bytes
    int16_t mParent;            // +0x00
    int16_t pad02;
    int16_t mNext;              // +0x04
    uint16_t pad06;
    uint16_t mFlags;            // +0x08
    uint8_t pad0a;
    uint8_t mType;              // +0x0b
    uint32_t pad0c[0x20];
};
struct cRigModel : DefaultRefCounted {
    uint32_t pad08[0x24];
    VectorBase<cRigBlock> mBlocks;      // +0x98
};
struct cMeshData : DefaultRefCounted {};

// ---------------------------------------------------------------- source
struct cSkinnerFactory;
struct cSkinnerSource {
    uint32_t pad00[2];
    cRigModel* mpModel;                 // +0x08
    VectorBase<void*> mCoords;          // +0x0c  (indexed by block slot)
    uint32_t pad1c[6];
    cSkinnerFactory* mpFactory;         // +0x34
    uint32_t pad38[0x16];
    VectorBase<cSPVector2> mTexRects;   // +0x90  (0x10-byte rects)
    uint32_t padA0[1];
    VectorBase<cMeshData*> mMeshData;   // +0xa4
};

// ---------------------------------------------------------------- mesh / result aggregate
struct cMeshAORenderObj {
    uint32_t pad00[2];
    VectorU32 mVerts;                   // +0x08
};

struct cMesh : DefaultRefCounted {      // retail size 0x1d0
    VectorElemC m08;                    // +0x08
    uint32_t pad18[6];
    VectorVec2 mTexCoords;              // +0x30
    uint32_t pad40[6];
    VectorU32 mVertexIndices;           // +0x58
    uint32_t pad6c[5];
    VectorU32 mTexIndices;              // +0x80
    uint32_t pad94[0x3f];
    VectorU32 m190;                     // +0x190
    uint32_t pad1a0[1];
    VectorU32 m1a4;                     // +0x1a4
    void Prepare();                     // 0x00509450
    void Reset();                       // 0x00508400
};

struct cSkinnerResult : DefaultRefCounted {
    VectorElemC m08;                                    // +0x08
    uint32_t pad18[0x10];
    VectorU32 m58;                                      // +0x58
    uint32_t pad6c[0x1e];
    VectorBase<cMeshAORenderObj*> mE4;                  // +0xe4
    uint32_t padf4[7];
    VectorU32 m110;                                     // +0x110
    uint32_t pad120[0x1c];
    VectorU32 m190;                                     // +0x190
    void AddMesh(cMesh* src);                           // 0x0050c6c0
    void Finish();                                      // 0x0050c3b0
};

// ---------------------------------------------------------------- job / message
struct cJob;
namespace SP { struct cJob; }
struct SPcJob {
    uint32_t pad00[7];
    int mSlot;                          // +0x1c
    uint32_t pad20[2];
    bool Continuation(void* cb, void* data);   // 0x0068f9f0
};

struct SkinMsg {
    uint32_t pad00[4];
    int16_t mType;                      // +0x12
    char* GetBool();                    // 0x0041e920
};
struct MsgHandler {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8();
    virtual bool HandleMessage(uint32_t id, void** pMsg);   // +0x24
};

struct BuildMeshContext {
    uint32_t pad00[4];
    cSkinnerResult* mpResult;           // +0x10
    uint32_t pad14[3];
    cSkinnerSource* mpSource;           // +0x20
    uint32_t pad24[0x17];
    VectorU32 m80;                      // +0x80
    uint32_t pad90[0x1d];
    cMesh* mpMesh;                      // +0x104
};

// ---------------------------------------------------------------- externals
bool LoadSkinnerMesh(cMeshData* data, cMesh* mesh);            // 0x0052a700
void ReportBlockError(cRigBlock* block, const char* msg);      // 0x00563de0

// @ 0x00524a50 ?BuildMeshJobCallback@cPaintSystem@nSPSkinner@@SAXPAVcJob@SP@@PAX@Z
bool __cdecl BuildMeshJobCallback(SPcJob* job, BuildMeshContext* ctx)
{
    cSkinnerSource* src = ctx->mpSource;
    cMesh* mesh = ctx->mpMesh;
    cSkinnerResult* result = ctx->mpResult;
    cRigBlock* blocks = src->mpModel->mBlocks.mpBegin;
    int nBlocks = (int)src->mpModel->mBlocks.size();
    int slot = job->mSlot;
    while (slot < nBlocks && (blocks[slot].mFlags & 1))
        slot++;
    uint32_t nFirst = 0;
    for (int k = 0; k < slot; k++) {
        if (!(blocks[k].mFlags & 1))
            nFirst++;
    }
    if (slot >= nBlocks) {
        result->Finish();
        ctx->m80.clear();
        ctx->m80.resize((uint32_t)(result->m08.size()), (uint32_t)-1);
        for (uint32_t i = 0; i < result->m58.size(); i++)
            ctx->m80.mpBegin[result->m58.mpBegin[i]] = i;
        return true;
    }
    cRigBlock* pBlock = &blocks[slot];
    cMeshData* meshData = src->mMeshData.mpBegin[slot];
    if (meshData == 0 || !LoadSkinnerMesh(meshData, mesh))
        ReportBlockError(pBlock, "contains an invalid mesh");
    mesh->Prepare();
    bool bBad = false;
    bool bShift = false;
    for (uint32_t i = 0; i < mesh->mTexCoords.size(); i++) {
        cSPVector2& uv = mesh->mTexCoords[i];
        if (uv[0] < 0.0f || uv[0] > 1.0f || uv[1] < -1.0f || uv[1] > 1.0f)
            bBad = true;
        else if (uv[1] < 0.0f)
            bShift = true;
    }
    if (bShift && !bBad) {
        for (uint32_t i = 0; i < mesh->mTexCoords.size(); i++) {
            cSPVector2& uv = mesh->mTexCoords[i];
            uv[1] += 1.0f;
            if (uv[1] < 0.0f || uv[1] > 1.0f)
                bBad = true;
        }
    }
    if (bBad) {
        ReportBlockError(pBlock, "contains out-of-bounds texture coordinates");
        mesh->mTexIndices.clear();
    } else {
        cSPVector2* rect = &src->mTexRects.mpBegin[slot * 2];
        for (uint32_t i = 0; i < mesh->mTexCoords.size(); i++) {
            cSPVector2& uv = mesh->mTexCoords[i];
            float x0 = rect[0].x;
            float dx = rect[1].x - x0;
            uv[0] = x0 + dx * uv[0];
            float y0 = rect[0].y;
            float dy = rect[1].y - y0;
            uv[1] = y0 + dy * uv[1];
        }
    }
    if (mesh->mVertexIndices.empty())
        ReportBlockError(pBlock, "is not in a recognized format -- please make sure the maya material exports tangents");
    else if (mesh->mTexIndices.empty())
        ReportBlockError(pBlock, "does not have any texture coordinates");
    else if (mesh->mTexIndices.size() != mesh->mVertexIndices.size())
        ReportBlockError(pBlock, "does not have a texture coordinate at every vertex");
    else {
        uint32_t key = 0;
        int16_t cur = pBlock->mParent;
        while (cur != -1) {
            if (blocks[cur].mType == 5) {
                key |= (uint32_t)cur << 8;
                break;
            }
            cur = blocks[cur].mNext;
        }
        if (pBlock->mType == 3) {
            key |= 2;
            key |= (uint32_t)pBlock->mParent << 16;
        } else {
            key |= 4;
            cur = pBlock->mParent;
            while (cur != -1) {
                if (blocks[cur].mType == 5 || blocks[cur].mType == 3) {
                    key |= (uint32_t)cur << 16;
                    break;
                }
                cur = blocks[cur].mNext;
            }
        }
        char bKey = 0;
        MsgHandler* handler = (MsgHandler*)src->mCoords.mpBegin[slot];
        if (handler != 0) {
            SkinMsg* pMsg = 0;
            if (handler->HandleMessage(0x317a429d, (void**)&pMsg) && pMsg->mType == 1)
                bKey = *pMsg->GetBool();
        }
        if (bKey != 0)
            key |= 0x40;
        mesh->m1a4.resize((uint32_t)(mesh->m08.size()), key);
        uint32_t nTri = mesh->mVertexIndices.size() / 3;
        uint32_t nBase = result->m110.size();
        result->AddMesh(mesh);
        cMeshAORenderObj* pObj = result->mE4.mpBegin[nFirst];
        pObj->mVerts.resize(nTri);
        for (uint32_t i = 0; i < nTri; i++)
            pObj->mVerts.mpBegin[i] = i + nBase;
        uint32_t notFirst = ~nFirst;
        result->m110.resize(nBase + nTri, notFirst);
        result->m190.resize(nBase + nTri, key);
    }
    mesh->Reset();
    job->mSlot = slot + 1;
    return job->Continuation((void*)&BuildMeshJobCallback, ctx);
}
