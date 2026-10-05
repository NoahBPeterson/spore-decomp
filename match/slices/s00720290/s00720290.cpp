// SP::cMeshClusterer internals and EASTL copy helpers (retail offset layout derived from disasm).
#include "types.h"

// ---- external helpers (callees are masked relocations) ----
extern "C" void  __cdecl EASTL_allocator_deallocate(void* p);
extern "C" void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int a, int b,
                                                  const char* file, int line);
extern "C" void* __cdecl operator_new(uint32_t size, const char* name, int a, int b,
                                      const char* file, int line);
extern "C" void  __cdecl op_new_array(void* dst, int zero, uint32_t size);
extern "C" float __cdecl sqrtf(float x);

// ================= 0x28 face/cluster vertex record helpers =================
struct Vec3 { float x, y, z; };

struct cFaceCluster {
    Vec3 mSumAreaPoint;      // +0x00
    Vec3 mSumAreaNormal;     // +0x0c
    float mArea;             // +0x18
    int mFirstEdge;          // +0x1c
    int mParentCluster;      // +0x20
    void* mPreviousDE;       // +0x24
};                           // 0x28

struct cHeapEntry { float mCost; int mHeapIndex; };
struct cDualEdge {
    float mCost;             // +0x00
    int mHeapIndex;          // +0x04
    int mClusters[2];        // +0x08
    int mNextEdges[2];       // +0x10
};                           // 0x18

// vector flavour with 0x14 stride (retail): {begin,end,cap,..}
struct FaceVec { cFaceCluster* mpBegin; cFaceCluster* mpEnd; cFaceCluster* mpCap; int pad[2]; };
struct DualVec { cDualEdge* mpBegin; cDualEdge* mpEnd; cDualEdge* mpCap; int pad[2]; };
struct HeapVec { cHeapEntry** mpBegin; cHeapEntry** mpEnd; cHeapEntry** mpCap; int pad[2]; };
struct cHeap {
    HeapVec mHeapEntries;    // +0x00
    void HeapifyDown(int i);
    void HeapifyUp(int i);
};

struct cMeshClusterer {
    char pad_00[0x48];
    FaceVec mFaceClusters;   // +0x48
    DualVec mDualEdges;      // +0x5c
    cHeap mEdgeHeap;         // +0x70
    float mMaxError;         // +0x84
    int mNumClusters;        // +0x88
    int mCostType;           // +0x8c
    void CalcError(cFaceCluster* a, cFaceCluster* b, float* out);
    void MergeEdgeLists(int param_2, int param_3);
};

// ================= Mesh adjacency builder (offsets from disasm) =================
struct Pair16 { int first, second; };
struct Rec18 {
    int*   f0;   // +0x00  int array (in)
    Pair16* f1;  // +0x04  pair array
    int*   f2;   // +0x08  int array
    int    f3;   // +0x0c
    int    f4;   // +0x10
    int    f5;   // +0x14  group modulus
};
struct MeshAdj {
    Pair16* mPairs;      // +0x00
    char    pad04[0x10];
    Rec18*  mRecords;    // +0x14
    char    pad18[0x10];
    int     mCount;      // +0x28
    int     mCounter;    // +0x2c
    char    pad30[4];
    bool (__cdecl *mCb)(Rec18*, int*, int*, void*);  // +0x34
    void*   mCbArg;      // +0x38
    bool    mFlag;       // +0x3c
    void AddTri(int a, int n, int c, int* in, Pair16* out, int d);
    void LinkRec(int node, int pos, int val);
    void Build();
};

// ================= hash table (grow) =================
struct HashTable {
    char     pad00[4];
    void**   mBuckets;   // +0x04
    uint32_t mCount;     // +0x08
    void Grow(uint32_t newSize);
};

// ================= 0x68-stride element owner (free helpers) =================
struct Element68 {
    char  pad00[0x14];
    void* v14;           // +0x14
    char  pad18[0x1c];
    void* v34;           // +0x34
    char  pad38[0x10];
    void* v48;           // +0x48
    char  pad4c[0x1c];
    void Dtor();
};

// @ 0x00720290
void MeshAdj::AddTri(int a, int n, int c, int* in, Pair16* out, int d)
{
    Rec18* rec = &mRecords[a];
    rec->f0 = in;
    rec->f1 = out;
    rec->f2 = 0;
    rec->f3 = d;
    rec->f4 = c;
    rec->f5 = n;

    int counter = 0;
    int i6 = 0;
    if (c > 0) {
        do {
            int mod = rec->f5;
            i6 = counter + 1;
            int i7 = i6;
            if (i6 % mod == 0)
                i7 = i6 - mod;

            int idx = in[counter];
            out->first = -1;
            out->second = -1;

            Pair16* p = &mPairs[idx];
            int node = p->first;
            int lnk = p->second;

            bool inserted = false;
            while (node >= 0) {
                Rec18* q = &mRecords[node];
                if (q->f0[lnk] == in[i7] && (mFlag || a == node)) {
                    bool ok = true;
                    if (mCb != 0) {
                        int a2 = a;
                        int i72 = i7;
                        ok = mCb(mRecords, &node, &a2, mCbArg);
                    }
                    if (ok) {
                        int p0 = q->f1[lnk].first;
                        int p1 = q->f1[lnk].second;
                        p->first  = p0;
                        p->second = p1;
                        out->first = node;
                        out->second = lnk;
                        q->f1[lnk].first  = a;
                        q->f1[lnk].second = counter;
                        inserted = true;
                        break;
                    }
                }
                p = &q->f1[lnk];
                node = p->first;
                lnk  = p->second;
            }
            if (!inserted) {
                int idx2 = in[i7];
                out->first  = mPairs[idx2].first;
                out->second = mPairs[idx2].second;
                mPairs[idx2].first  = a;
                mPairs[idx2].second = counter;
            }
            out++;
            counter = i6;
        } while (i6 < c);
    }
}

// @ 0x00720470
void MeshAdj::LinkRec(int node, int pos, int val)
{
    Rec18* r = &mRecords[node];
    int mod = r->f5;
    pos = pos + 1;
    if (pos % mod == 0)
        pos = pos - mod;
    r->f2[pos] = val;
    Pair16* p = &r->f1[pos];
    if (p->first >= 0)
        LinkRec(p->first, p->second, val);
}

// @ 0x007204c0
void MeshAdj::Build()
{
    for (int i = 0; i < mCount; i++) {
        int node = mPairs[i].first;
        int idx  = mPairs[i].second;
        while (node >= 0) {
            Rec18* rec = &mRecords[node];
            if (rec->f2 != 0) {
                int c = mCounter++;
                int mod = rec->f5;
                int pos = idx + 1;
                if (pos % mod == 0)
                    pos = pos - mod;
                rec->f2[pos] = c;
                Pair16* q = &rec->f1[pos];
                if (q->first >= 0)
                    LinkRec(q->first, q->second, c);
            }
            Pair16* e = &mRecords[node].f1[idx];
            node = e->first;
            idx  = e->second;
            e->first = -1;
            e->second = -1;
        }
    }
}

// @ 0x00720590
uint32_t __cdecl HashVec(const float* v)
{
    int key[3];
    float f0 = *(float*)v + 192.0f;
    float f1 = *(float*)((const char*)v + 4) + 192.0f;
    float f2 = *(float*)((const char*)v + 8) + 192.0f;
    key[0] = (*(int*)&f0) + (int)0xBCC00000;
    key[1] = (*(int*)&f1) + (int)0xBCC00000;
    key[2] = (*(int*)&f2) + (int)0xBCC00000;
    uint32_t h = 0x811C9DC5;
    unsigned char* q = (unsigned char*)key;
    unsigned char* e = (unsigned char*)(key + 3);
    do {
        h *= 0x1000193;
        h ^= *q;
        q++;
    } while (q < e);
    return h;
}

// @ 0x00720620
void cHeap::HeapifyDown(int i)
{
    cHeapEntry** begin = mHeapEntries.mpBegin;
    int count = (int)(mHeapEntries.mpEnd - mHeapEntries.mpBegin);
    int child = i * 2 + 1;
    if (child < count) {
        do {
            int right = child + 1;
            if (right < count) {
                cHeapEntry* l = begin[child];
                cHeapEntry* r = begin[right];
                if (l->mCost > r->mCost)
                    child = right;
            }
            cHeapEntry* e = begin[child];
            cHeapEntry* p = begin[i];
            if (p->mCost <= e->mCost)
                return;
            int t = e->mHeapIndex;
            e->mHeapIndex = p->mHeapIndex;
            p->mHeapIndex = t;
            begin = mHeapEntries.mpBegin;
            cHeapEntry* t2 = begin[child];
            begin[child] = begin[i];
            begin[i] = t2;
            i = child;
            child = i * 2 + 1;
            count = (int)(mHeapEntries.mpEnd - mHeapEntries.mpBegin);
        } while (child < count);
    }
}

// @ 0x007206b0
void cHeap::HeapifyUp(int i)
{
    int parent = (i - 1) >> 1;
    if (parent < 0)
        return;
    do {
        cHeapEntry* e = mHeapEntries.mpBegin[parent];
        cHeapEntry* p = mHeapEntries.mpBegin[i];
        if (e->mCost <= p->mCost)
            return;
        int t = p->mHeapIndex;
        p->mHeapIndex = e->mHeapIndex;
        e->mHeapIndex = t;
        cHeapEntry* t2 = mHeapEntries.mpBegin[i];
        mHeapEntries.mpBegin[i] = mHeapEntries.mpBegin[parent];
        mHeapEntries.mpBegin[parent] = t2;
        i = parent;
        parent = (i - 1) >> 1;
    } while (parent >= 0);
}

// @ 0x00720700
void cMeshClusterer::CalcError(cFaceCluster* a, cFaceCluster* b, float* out)
{
    float sumNx = a->mSumAreaNormal.x + b->mSumAreaNormal.x;
    float sumNy = a->mSumAreaNormal.y + b->mSumAreaNormal.y;
    float sumNz = a->mSumAreaNormal.z + b->mSumAreaNormal.z;
    float sumArea = a->mArea + b->mArea;
    float nsum = sumNx * sumNx + sumNy * sumNy + sumNz * sumNz;
    float la = sqrtf(a->mSumAreaNormal.x * a->mSumAreaNormal.x
                   + a->mSumAreaNormal.y * a->mSumAreaNormal.y
                   + a->mSumAreaNormal.z * a->mSumAreaNormal.z);
    float lb = sqrtf(b->mSumAreaNormal.x * b->mSumAreaNormal.x
                   + b->mSumAreaNormal.y * b->mSumAreaNormal.y
                   + b->mSumAreaNormal.z * b->mSumAreaNormal.z);
    float ls = sqrtf(nsum);
    if (ls < 1e-08f) {
        *out = 1000.0f;
        return;
    }
    if (la < 1e-08f || lb < 1e-08f) {
        *out = 0.0f;
        return;
    }
    float dot_ab = a->mSumAreaNormal.x * b->mSumAreaNormal.x
                 + a->mSumAreaNormal.y * b->mSumAreaNormal.y
                 + a->mSumAreaNormal.z * b->mSumAreaNormal.z;
    if (mCostType == 1) {
        *out = 1.0f - dot_ab / (lb * la);
        return;
    }
    if (mCostType != 2) {
        float da = (a->mSumAreaNormal.x * sumNx + a->mSumAreaNormal.y * sumNy
                  + a->mSumAreaNormal.z * sumNz) / (la * ls);
        float db = (b->mSumAreaNormal.x * sumNx + b->mSumAreaNormal.y * sumNy
                  + b->mSumAreaNormal.z * sumNz) / (lb * ls);
        *out = (((2.0f - da) - db) / ls) * sumArea;
        return;
    }
    {
        float r = dot_ab / (lb * la);
        *out = r;
        if (sumArea < 0.1f)
            *out = (r / 0.1f) * sumArea;
    }
}

// @ 0x00720920
void __cdecl MinMaxIndices(const float* const* v, int* minOut, int* maxOut)
{
    *maxOut = 0; maxOut[1] = 0;
    *minOut = 0; minOut[1] = 0;
    const float* p = v[0];
    int n = (int)((const char*)v[1] - (const char*)p) >> 3;
    float minX = p[0], minY = p[1];
    float maxX = minX, maxY = minY;
    for (int i = 1; i < n; i++) {
        float x = p[i * 2];
        float y = p[i * 2 + 1];
        if (x < minX) { minX = x; minOut[0] = i; }
        else if (x > maxX) { maxX = x; maxOut[0] = i; }
        if (y < minY) { minY = y; minOut[1] = i; }
        else if (y > maxY) { maxY = y; maxOut[1] = i; }
    }
}

// @ 0x00720b10
void Element68::Dtor()
{
    if (v48 != 0 && ((int*)v48)[-1] != 0)
        EASTL_allocator_deallocate(v48);
    if (v34 != 0 && ((int*)v34)[-1] != 0)
        EASTL_allocator_deallocate(v34);
    if (v14 != 0 && ((int*)v14)[-1] != 0)
        EASTL_allocator_deallocate(v14);
}

// @ 0x00720b60
void HashTable::Grow(uint32_t newSize)
{
    uint32_t size = newSize * 4;
    if (size == -4 && 0) {}
    char* dst = (char*)EASTL_allocator_allocate(size + 4, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    op_new_array(dst, 0, size);
    *(int*)(size + (int)dst) = -1;
    uint32_t i = 0;
    if (mCount != 0) {
        do {
            void* p = mBuckets[i];
            while (p != 0) {
                int* node = (int*)p;
                uint32_t h = (node[2] ^ node[1] ^ node[0]) % newSize;
                mBuckets[i] = (void*)node[4];
                node[4] = *(int*)(dst + h * 4);
                *(int**)(dst + h * 4) = node;
                p = mBuckets[i];
            }
            i++;
        } while (i < mCount);
    }
    if (mCount > 1)
        EASTL_allocator_deallocate(mBuckets);
    mBuckets = (void**)dst;
    mCount = newSize;
}

// @ 0x00720c20
Element68* __cdecl DestroyRange68(Element68* first, Element68* last, Element68* dst)
{
    if (first == last)
        return dst;
    do {
        if (first->v48 != 0 && ((int*)first->v48)[-1] != 0)
            EASTL_allocator_deallocate(first->v48);
        if (first->v34 != 0 && ((int*)first->v34)[-1] != 0)
            EASTL_allocator_deallocate(first->v34);
        if (first->v14 != 0 && ((int*)first->v14)[-1] != 0)
            EASTL_allocator_deallocate(first->v14);
        first += 1;
        dst += 1;
    } while (first != last);
    return dst;
}

// @ 0x00720c90
void __cdecl UninitCopyFace28(cFaceCluster** out, const cFaceCluster* first,
                              const cFaceCluster* last, cFaceCluster* dst)
{
    *out = dst;
    while (first != last) {
        if (dst != 0) {
            dst->mSumAreaPoint.x = first->mSumAreaPoint.x;
            dst->mSumAreaPoint.y = first->mSumAreaPoint.y;
            dst->mSumAreaPoint.z = first->mSumAreaPoint.z;
            dst->mSumAreaNormal.x = first->mSumAreaNormal.x;
            dst->mSumAreaNormal.y = first->mSumAreaNormal.y;
            dst->mSumAreaNormal.z = first->mSumAreaNormal.z;
            dst->mFirstEdge = first->mFirstEdge;
            dst->mParentCluster = first->mParentCluster;
            dst->mPreviousDE = first->mPreviousDE;
        }
        first++;
        dst++;
    }
    *out = dst;
}

// @ 0x00720d10
void __cdecl FillFace28(cFaceCluster* dst, uint32_t n, const cFaceCluster* src)
{
    if (n == 0)
        return;
    do {
        if (dst != 0) {
            dst->mSumAreaPoint.x = src->mSumAreaPoint.x;
            dst->mSumAreaPoint.y = src->mSumAreaPoint.y;
            dst->mSumAreaPoint.z = src->mSumAreaPoint.z;
            dst->mSumAreaNormal.x = src->mSumAreaNormal.x;
            dst->mSumAreaNormal.y = src->mSumAreaNormal.y;
            dst->mSumAreaNormal.z = src->mSumAreaNormal.z;
            dst->mFirstEdge = src->mFirstEdge;
            dst->mParentCluster = src->mParentCluster;
            dst->mPreviousDE = src->mPreviousDE;
        }
        n--;
        dst++;
    } while (n != 0);
}

// @ 0x00720d70
void __cdecl UninitCopyDual18(cDualEdge** out, const cDualEdge* first,
                              const cDualEdge* last, cDualEdge* dst)
{
    *out = dst;
    while (first != last) {
        if (dst != 0)
            *dst = *first;
        first++;
        dst++;
    }
    *out = dst;
}

// @ 0x00720dd0
void* __cdecl MoveCopy34(void* first, void* last, void* dst)
{
    if (first == last)
        return dst;
    do {
        unsigned char* s = (unsigned char*)first;
        unsigned char* d = (unsigned char*)dst;
        if (dst != 0) {
            *(int*)(d + 0x00) = *(int*)(s + 0x00);
            *(int*)(d + 0x04) = *(int*)(s + 0x04);
            *(float*)(d + 0x08) = *(float*)(s + 0x08);
            *(int*)(d + 0x0c) = *(int*)(s + 0x0c);
            *(float*)(d + 0x10) = *(float*)(s + 0x10);
            *(float*)(d + 0x14) = *(float*)(s + 0x14);
            *(float*)(d + 0x18) = *(float*)(s + 0x18);
            *(float*)(d + 0x1c) = *(float*)(s + 0x1c);
            *(float*)(d + 0x20) = *(float*)(s + 0x20);
            *(float*)(d + 0x24) = *(float*)(s + 0x24);
            *(float*)(d + 0x28) = *(float*)(s + 0x28);
            *(int*)(d + 0x2c) = *(int*)(s + 0x2c);
            *(float*)(d + 0x30) = *(float*)(s + 0x30);
        }
        first = (unsigned char*)first + 0x34;
        dst = (unsigned char*)dst + 0x34;
    } while (first != last);
    return dst;
}

// @ 0x00720ea0
void* __cdecl CopyFace28(void* first, void* last, void* dst)
{
    if (first == last)
        return dst;
    do {
        unsigned char* s = (unsigned char*)first;
        unsigned char* d = (unsigned char*)dst;
        if (dst != 0) {
            *(float*)(d + 0x00) = *(float*)(s + 0x00);
            *(float*)(d + 0x04) = *(float*)(s + 0x04);
            *(float*)(d + 0x08) = *(float*)(s + 0x08);
            *(float*)(d + 0x0c) = *(float*)(s + 0x0c);
            *(float*)(d + 0x10) = *(float*)(s + 0x10);
            *(float*)(d + 0x14) = *(float*)(s + 0x14);
            *(float*)(d + 0x18) = *(float*)(s + 0x18);
            *(int*)(d + 0x1c) = *(int*)(s + 0x1c);
            *(int*)(d + 0x20) = *(int*)(s + 0x20);
            *(int*)(d + 0x24) = *(int*)(s + 0x24);
        }
        first = (unsigned char*)first + 0x28;
        dst = (unsigned char*)dst + 0x28;
    } while (first != last);
    return dst;
}

// @ 0x00720f40
void cMeshClusterer::MergeEdgeLists(int param_2, int param_3)
{
    cFaceCluster* faceBase = mFaceClusters.mpBegin;
    cFaceCluster* fa = &faceBase[param_2];
    cFaceCluster* fb = &faceBase[param_3];

    int e = fa->mFirstEdge;
    while (e >= 0) {
        int count = (int)(mDualEdges.mpEnd - mDualEdges.mpBegin);
        int q = e / count;
        int r = e % count;
        cDualEdge* de = &mDualEdges.mpBegin[r];
        int nxt = de->mNextEdges[q];
        faceBase[de->mClusters[q ^ 1]].mPreviousDE = 0;
        e = nxt;
    }

    int* plink = &fa->mFirstEdge;
    e = *plink;
    while (e >= 0) {
        int count = (int)(mDualEdges.mpEnd - mDualEdges.mpBegin);
        int q = e / count;
        int r = e % count;
        cDualEdge* de = &mDualEdges.mpBegin[r];
        e = de->mNextEdges[q];
        if (de->mHeapIndex < 0) {
            *plink = e;
        } else {
            int other = de->mClusters[q ^ 1];
            faceBase[other].mPreviousDE = de;
            CalcError(fa, &faceBase[other], (float*)de);
            int hi = de->mHeapIndex;
            plink = &de->mNextEdges[q];
            if (hi >= 1) {
                cHeapEntry* par = mEdgeHeap.mHeapEntries.mpBegin[(hi - 1) >> 1];
                if (par->mCost > de->mCost || par->mCost == de->mCost)
                    mEdgeHeap.HeapifyDown(hi);
                else
                    mEdgeHeap.HeapifyUp(hi);
            } else {
                mEdgeHeap.HeapifyDown(hi);
            }
        }
    }

    e = fb->mFirstEdge;
    *plink = e;
    int* plink2 = plink;
    while (e >= 0) {
        int count = (int)(mDualEdges.mpEnd - mDualEdges.mpBegin);
        int q = e / count;
        int r = e % count;
        cDualEdge* de = &mDualEdges.mpBegin[r];
        int hi = de->mHeapIndex;
        e = de->mNextEdges[q];
        int* pe = &de->mNextEdges[q];
        if (hi < 0) {
            *plink = e;
        } else if (faceBase[de->mClusters[q ^ 1]].mPreviousDE == 0) {
            de->mClusters[q] = param_2;
            CalcError(fa, &faceBase[de->mClusters[q ^ 1]], (float*)de);
            hi = de->mHeapIndex;
            plink = pe;
            plink2 = pe;
            if (hi >= 1) {
                cHeapEntry* par = mEdgeHeap.mHeapEntries.mpBegin[(hi - 1) >> 1];
                if (par->mCost > de->mCost || par->mCost == de->mCost)
                    mEdgeHeap.HeapifyDown(hi);
                else
                    mEdgeHeap.HeapifyUp(hi);
            } else {
                mEdgeHeap.HeapifyDown(hi);
            }
        } else {
            cHeapEntry** arr = mEdgeHeap.mHeapEntries.mpBegin;
            arr[hi] = arr[(int)(mEdgeHeap.mHeapEntries.mpEnd - arr) - 1];
            int hi2 = de->mHeapIndex;
            arr[hi2]->mHeapIndex = hi2;
            mEdgeHeap.mHeapEntries.mpEnd = (cHeapEntry**)((char*)mEdgeHeap.mHeapEntries.mpEnd - 4);
            mEdgeHeap.HeapifyDown(hi);
            de->mHeapIndex = -1;
            *plink2 = e;
            plink = plink2;
        }
    }
    *plink = -1;
}
