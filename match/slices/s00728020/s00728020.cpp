// Slice s00728020 — SP::cMeshSimplifier mesh-clustering entry points.
//   00728020 Simplify            (reconstructed)
//   other functions              (partial skeletons)
#include <math.h>
#include "types.h"

// Per-mesh record, stride 0x8c.
struct MeshRec { char pad[0x8c]; };
struct MeshCtx {
    char     pad0[0x1c];
    MeshRec* begin;   // +0x1c
    MeshRec* end;     // +0x20
};

extern "C" {
    void FUN_00726c20(void* p, float f, int one, void* p4);   // 0x726c20
    void FUN_00725130(void* p);                               // 0x725130
    void FUN_00735a90(void* p);                               // 0x735a90
    void FUN_00737ef0(void* p);                               // 0x737ef0
    void FUN_00921df0(void* ms);                              // EA::Thread::ThreadSleep
}

// @ 0x00728020  SP::cMeshSimplifier::Simplify
void FUN_00728020(MeshCtx* ctx, float f, int mode, void* p4)
{
    if (ctx->end - ctx->begin != 0) {
        FUN_00726c20(ctx, f, 1, p4);
        int z = 0;
        FUN_00921df0(&z);
        FUN_00725130(ctx);
        z = 0;
        FUN_00921df0(&z);
        FUN_00735a90(ctx);
        z = 0;
        FUN_00921df0(&z);
        FUN_00737ef0(ctx);
        z = 0;
        FUN_00921df0(&z);
    }
}

// ---------------------------------------------------------------------------
// shared shapes for the mesh-join job / clusterer
// ---------------------------------------------------------------------------
extern "C" {
void  FUN_00733070(int n, void* alloc);
void  FUN_0047c800(void** srcPtr, void* begin, void* end, void* dst, void* src);
void  FUN_004d04f0(void* dst, void* end, void* src);
void  FUN_00723af0(void* dst, void* end, void* src);
void  FUN_0041eb80();
void  FUN_007269b0(void* end, unsigned count, void* temp);
void  FUN_00726960(void* begin, void* end);
void* operator_new(unsigned size, const char* name, int a, int b, const char* file, int line);
void  FUN_006c1570(void* vec, void* value);
void  FUN_00720070(void* p);
void* FUN_00722a80(void* a, void* b, void* c);
void  FUN_00721810(void* a, void* b);
void  FUN_00424f70(void* p);
void  FUN_007366e0(void* mesh);
void  FUN_00735470(void* mesh);
void  FUN_00723d60(void* mesh);
void  FUN_0071ec20(void* mesh, void* out, int a, int b, int c);
void  FUN_00724100(void* self);
void  FUN_007221c0(void* self);
int   FUN_006a2660(void* props, int id);
void  FUN_00723930(void* p);
void  FUN_00723a70(void* dst, void* src);
void  FUN_00723cb0(void* pos, void* oldEnd, void* newEnd);
void* FUN_00723c20(void* begin, void* pos, void* dst);
void  FUN_00720c20(void* begin, void* pos, void* dst);
void  FUN_00723840(void* self, unsigned n);
}

struct V3 { float x, y, z; };

struct Elem68 {
    char mData[0x68];
    void Destroy() { FUN_00723930(this); }
    void CopyCtor(void* src) { FUN_00723a70(this, src); }
    void Init()
    {
        int* p = (int*)mData;
        p[0] = -1;
        p[1] = 0; p[2] = 0;
        p[3] = -1; p[4] = -1;
        p[5] = 0; p[6] = 0; p[7] = 0;
        p[10] = 0; p[11] = 0;
        ((unsigned char*)mData)[0x30] = 0;
        p[13] = 0; p[14] = 0; p[15] = 0;
        p[18] = 0; p[19] = 0; p[20] = 0;
        p[23] = -1; p[24] = 0; p[25] = 0;
    }
};

struct Vec68 {
    Elem68* mpBegin;   // +0x00
    Elem68* mpEnd;     // +0x04
    Elem68* mpCap;     // +0x08
    void Insert(Elem68* pos, Elem68* value);
};

struct cClusterInfo20 {
    int mNumFaces;     // +0x00
    V3  mNormal;       // +0x04
    V3  mCenter;       // +0x10
    float mArea;       // +0x1c
    int mFirstFace;    // +0x20
    int mLastFace;     // +0x24
    int mIndex;        // +0x28
    char pad2c[0x38];
};

struct cFaceCluster20 {
    V3  mSumPoint;     // +0x00
    V3  mSumNormal;    // +0x0c
    float mArea;       // +0x18
    int mFirstEdge;    // +0x1c
    int mParent;       // +0x20
    void* mPrevDE;     // +0x24
};

struct ClusterVec {
    cClusterInfo20* mpBegin;   // +0x00
    cClusterInfo20* mpEnd;     // +0x04
    cClusterInfo20* mpCap;     // +0x08
    int pad0c[2];
    void Resize(unsigned n);
};

struct FaceVec {
    cFaceCluster20* mpBegin;   // +0x00
    cFaceCluster20* mpEnd;     // +0x04
    cFaceCluster20* mpCap;     // +0x08
    int pad0c[2];
};

struct cMeshClusterer20 {
    char pad00[8];
    void* mpMesh;                 // +0x08
    ClusterVec mClusterInfo;      // +0x0c
    char pad20[0x10];
    int mClusterFaceCount;        // +0x30
    char pad34[0x14];
    FaceVec mFaceClusters;        // +0x48
    char pad5c[0x14];
    char mEdgeHeap[0x14];         // +0x70
    float mMaxError;              // +0x84
    int mSectionCount;            // +0x88
    int mMaxClusterCount;         // +0x8c

    void CreateClusterInfo();
    void Cluster(void* meshData, int n);
};

struct UVGenJobInfo {
    void* mVtbl0;        // +0x00
    void* mVtbl1;        // +0x04
    int   mRefCount;     // +0x08
    void* mField0C;      // +0x0c
    void* mField10;      // +0x10
    void* mField14;      // +0x14
    void* mField18;      // +0x18
    void* mField1C;      // +0x1c
    int   mField20;      // +0x20
    void* mField24;      // +0x24
    int   mField28;      // +0x28
    int   mField2C;      // +0x2c
    void* mField30;      // +0x30
    void* mField34;      // +0x34
    void* mField38;      // +0x38
    void* mField3C;      // +0x3c
    void* mField40;      // +0x40

    UVGenJobInfo* Init(void* src, int mode, void* p4, void* p5);
    void Destroy();
};

// @ 0x007280b0
UVGenJobInfo* UVGenJobInfo::Init(void* src, int mode, void* p4, void* p5)
{
    int* s = (int*)src;
    mVtbl0 = 0;
    mVtbl1 = 0;
    mRefCount = 0;
    FUN_00733070((s[1] - s[0]) >> 2, (char*)src + 0xc);
    FUN_0047c800((void**)&src, *(void**)src, ((void**)src)[1], mField0C, src);
    mField10 = src;
    mField20 = mode;
    mField24 = 0;
    mField28 = 0;
    mField2C = 0;
    mField38 = 0;
    mField3C = 0;
    mField40 = 0;
    int count = (int)((char*)mField10 - (char*)mField0C) >> 2;
    if (p4)
        FUN_004d04f0(p4, (char*)p4 + count * 4, src);
    if (p5)
        FUN_00723af0(p5, (char*)p5 + count * 0x38, src);
    return this;
}

// @ 0x007281d0
void __fastcall FUN_007281d0(UVGenJobInfo* self)
{
    if (self->mField38 && *((int*)self->mField38 - 1) != 0)
        FUN_00723930(self->mField38);
    if (self->mField24 && *((int*)self->mField24 - 1) != 0)
        FUN_00723930(self->mField24);
    FUN_0041eb80();
    self->mVtbl1 = 0;
    self->mVtbl0 = 0;
}

// @ 0x00728330
void ClusterVec::Resize(unsigned n)
{
    int count = (int)(mpEnd - mpBegin);
    if ((unsigned)count < n) {
        cClusterInfo20 temp;
        FUN_007269b0(mpEnd, n - count, &temp);
    } else {
        FUN_00726960(mpBegin + n, mpEnd);
    }
}

// @ 0x00728400
void Vec68::Insert(Elem68* pos, Elem68* value)
{
    if (mpEnd != mpCap) {
        if (pos <= value && value < mpEnd)
            ++value;
        if (mpEnd)
            FUN_00723930(mpEnd - 1);
        FUN_00723cb0(pos, mpEnd - 1, mpEnd);
        FUN_00723a70(value, value);
        ++mpEnd;
        return;
    }

    int cap = (int)(mpEnd - mpBegin);
    cap = (cap == 0) ? 1 : cap * 2;
    Elem68* buf = (Elem68*)operator_new(cap * 0x68, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    Elem68* mid = (Elem68*)FUN_00723c20(mpBegin, pos, buf);
    FUN_00720c20(mpBegin, pos, buf);
    if (mid)
        FUN_00723930(value);
    Elem68* newEnd = (Elem68*)FUN_00723c20(pos, mpEnd, mid + 1);
    FUN_00720c20(pos, mpEnd, mid + 1);
    if (mpBegin && *((int*)mpBegin - 1) != 0)
        FUN_00723930(mpBegin);
    mpBegin = buf;
    mpEnd = newEnd;
    mpCap = buf + cap;
}

// @ 0x007285a0
void cMeshClusterer20::CreateClusterInfo()
{
    mClusterInfo.Resize(mSectionCount);
    int faceCount = (int)(mFaceClusters.mpEnd - mFaceClusters.mpBegin);
    mClusterFaceCount = faceCount;

    for (int i = 0; i < faceCount; ++i) {
        int root = i;
        while (root >= 0 && root < faceCount) {
            int p = mFaceClusters.mpBegin[root].mParent;
            if (p == root || p < 0 || p >= faceCount)
                break;
            root = p;
        }
        if (root < 0 || root >= faceCount)
            continue;

        cFaceCluster20& f = mFaceClusters.mpBegin[root];
        cClusterInfo20& ci = mClusterInfo.mpBegin[root];
        if (ci.mNumFaces == 0) {
            if (f.mArea <= 1e-08f) {
                ci.mNormal.x = 0.0f;
                ci.mNormal.y = 0.0f;
                ci.mNormal.z = 0.0f;
                ci.mCenter = f.mSumPoint;
            } else {
                float inv = 1.0f / sqrtf(f.mSumNormal.x * f.mSumNormal.x +
                                                   f.mSumNormal.y * f.mSumNormal.y +
                                                   f.mSumNormal.z * f.mSumNormal.z + 1e-08f);
                ci.mNormal.x = f.mSumNormal.x * inv;
                ci.mNormal.y = f.mSumNormal.y * inv;
                ci.mNormal.z = f.mSumNormal.z * inv;
                ci.mCenter.x = f.mSumPoint.x / f.mArea;
                ci.mCenter.y = f.mSumPoint.y / f.mArea;
                ci.mCenter.z = f.mSumPoint.z / f.mArea;
                ci.mArea = f.mArea;
            }
        }
        ++ci.mNumFaces;
        mFaceClusters.mpBegin[i].mParent = root + faceCount;
    }

    for (int i = 1; i < mSectionCount; ++i) {
        cClusterInfo20& ci = mClusterInfo.mpBegin[i];
        ci.mFirstFace = ci.mFirstFace + ci.mLastFace;
        ci.mLastFace = ci.mFirstFace;
    }

    FUN_00720070(&mClusterFaceCount);

    for (int i = 0; i < faceCount; ++i) {
        int root = mFaceClusters.mpBegin[i].mParent - faceCount;
        if (root >= 0 && root < mSectionCount) {
            cClusterInfo20& ci = mClusterInfo.mpBegin[root];
            int n = ci.mIndex++;
            (void)n;
        }
    }
}

// @ 0x007289a0
void __fastcall FUN_007289a0(Vec68* vec)
{
    if (vec->mpEnd < vec->mpCap) {
        Elem68* p = vec->mpEnd++;
        if (p)
            p->Init();
        return;
    }

    Elem68 temp;
    temp.Init();
    vec->Insert(vec->mpEnd, &temp);
}

// @ 0x00728af0
void cMeshClusterer20::Cluster(void* meshData, int n)
{
    mMaxClusterCount = FUN_006a2660(*(void**)0x15fd918, 0x5b56990);

    int count = (int)(mClusterInfo.mpEnd - mClusterInfo.mpBegin);
    void* mid = FUN_00722a80(mClusterInfo.mpEnd, mClusterInfo.mpEnd, mClusterInfo.mpBegin);
    FUN_00721810(mid, mClusterInfo.mpEnd);
    mClusterInfo.mpEnd += count;

    mClusterFaceCount = 0;
    char temp[0x14];
    FUN_00424f70(temp);

    if (meshData != mpMesh) {
        mpMesh = meshData;
    }
    mSectionCount = n;

    if (mpMesh) {
        FUN_007366e0(mpMesh);
        FUN_00735470(mpMesh);
        FUN_00723d60(mpMesh);
        FUN_0071ec20(mpMesh, temp, 0x16, 0xf, 0xe);
        FUN_00724100(this);
        FUN_007221c0(this);
        if (mMaxError != 0.0f) {
            CreateClusterInfo();
        }
    }
}
