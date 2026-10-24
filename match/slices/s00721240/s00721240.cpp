// cTextureChart hash containers and chart helpers (retail offsets from disasm).
#include "types.h"
#include <string.h>
#include <math.h>
#include <xmmintrin.h>

extern "C" void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int a, int b,
                                                  const char* file, int line);
extern "C" void  __cdecl op_new_array(void* dst, int zero, uint32_t size);
extern "C" void  __cdecl qsort(void* base, uint32_t n, uint32_t sz, int (__cdecl* cmp)(const void*, const void*));
extern "C" uint32_t __stdcall HashVec(const float* v);   // 0x00720590 (callee pops its arg: ret 4)
extern "C" int   __cdecl ComparePairs(const void* a, const void* b);
extern float g_chartMinX, g_chartMinY;

struct FChartNode { float kx, ky, kz; int f0c; FChartNode* next; };  // 0x14
struct IChartNode { int k0, k1, k2; int f0c; IChartNode* next; };    // 0x14
struct HashFind { void* pNode; void* pSlot; };                       // out pair written by Find*

struct ChartHash {
    char      pad00[4];
    void**    mBuckets;   // +0x04
    uint32_t  mCapacity;  // +0x08
    uint32_t  mCount;     // +0x0c
    char      state[0x30];
    void GrowF(uint32_t newSize);
    void FindF(int* out, float* key);
    void InsertF(int* out, float* key);
    void FindI(int* out, int* key);
    void InsertI(int* out, int* key);
};

struct Chart68 {
    char  p0[0x14];
    void* v14;   // +0x14
    char  p1[0x1c];
    void* v34;   // +0x34
    char  p2[0x10];
    void* v48;   // +0x48
    char  p3[0x1c];
};

struct TwoVtbl { void* vt0; void* vt1; char pad[4]; void* p0c; };

struct ChartRef;
struct ChartVec { char pad[0xc]; void** begin; void** end; ChartRef* MakeChartRef(ChartRef* out); };
struct ChartRef {
    int  mNumElts;             // +0x00
    void* mData;               // +0x04
    unsigned short mEltSize;   // +0x08
    unsigned short mEltStride; // +0x0a
    void* mOwner;              // +0x0c
};

struct HeapVec2 { void* mpBegin; void* mpEnd; void* mpCap; int pad[2]; };
struct cHeap2 { HeapVec2 mHeapEntries; void HeapifyDown(int i); };
struct FaceVec2 { void* mpBegin; void* mpEnd; void* mpCap; int pad[2]; };
struct CMeshClusterer2 {
    char pad_00[0x48];
    FaceVec2 mFaceClusters;  // +0x48
    char pad_5c[0x14];
    cHeap2 mEdgeHeap;        // +0x70
    float mMaxError;         // +0x84
    int mNumClusters;        // +0x88
    int mCostType;           // +0x8c
    void CollapseEdges();
    void MergeEdgeLists(int a, int b);
};

// @ 0x00721240
void __cdecl SortFloatsByDist(void* v)
{
    float* p = *(float**)v;
    int n = (((int*)v)[1] - (int)p) >> 3;
    int minIdx = 0;
    float minv = *p;
    if (1 < n) {
        int i = 1;
        if (3 < n - 1) {
            float* q = p + 6;
            do {
                if (q[-4] < minv) { minIdx = i; minv = q[-4]; }
                if (q[-2] < minv) { minIdx = i + 1; minv = q[-2]; }
                if (*q < minv) { minIdx = i + 2; minv = *q; }
                if (q[2] < minv) { minIdx = i + 3; minv = q[2]; }
                i += 4;
                q += 8;
            } while (i < n - 3);
        }
        if (i < n) {
            float* q = p + i * 2;
            do {
                if (*q < minv) { minIdx = i; minv = *q; }
                i++;
                q += 2;
            } while (i < n);
        }
    }
    float tmp0 = p[0];
    float tmp1 = p[1];
    p[0] = p[minIdx * 2];
    p[1] = p[minIdx * 2 + 1];
    p[minIdx * 2] = tmp0;
    p[minIdx * 2 + 1] = tmp1;
    g_chartMinX = (*(float**)v)[0];
    g_chartMinY = (*(float**)v)[1];
    qsort((char*)*(float**)v + 8, n - 1, 8, ComparePairs);
}

// @ 0x00721340
void __cdecl ChartSolve(int verts, int n, int* a, int* b, float* out)
{
    float* v = (float*)verts;
    out[0] = 1.0f;
    out[1] = 0.0f;
    int idx[4];
    float d[8];
    idx[0] = a[0];
    idx[1] = b[0];
    idx[2] = a[1];
    idx[3] = b[1];
    for (int k = 0; k < 4; k++) {
        int j = (idx[k] + 1) % n;
        d[k * 2]     = v[j * 2]     - v[idx[k] * 2];
        d[k * 2 + 1] = v[j * 2 + 1] - v[idx[k] * 2 + 1];
    }
    float ax = 0.0f, ay = 1.0f;
    float bx = 1.0f, by = 0.0f;
    float best = 3.4028234663852886e+38f;
    float dy23 = v[idx[3] * 2 + 1] - v[idx[2] * 2 + 1];
    float dx01 = v[idx[1] * 2]     - v[idx[0] * 2];
    float maxd = dy23 > dx01 ? dy23 : dx01;
    for (;;) {
        if (!(ay > 0.0f)) {
            int* volatile keep = &idx[0];
            (void)keep;
            return;
        }
        int i;
        for (i = 0; i < 4; i++) {
            double len = sqrt((double)d[i * 2] * d[i * 2] + (double)d[i * 2 + 1] * d[i * 2 + 1]);
            if (len <= maxd * 0.0001)
                break;
            volatile float flen = (float)len;
            float finv;
            _mm_store_ss(&finv, _mm_div_ss(_mm_set_ss(1.0f), _mm_load_ss((const float*)&flen)));
            float inv = finv;
            d[i * 2]     *= inv;
            d[i * 2 + 1] *= inv;
        }
        if (i == 4) {
            float v0 = -(d[0] * ax + d[1] * ay);
            float v1 =   d[2] * ax + d[3] * ay;
            float v2 =   d[4] * bx + d[5] * by;
            float v3 = -(d[6] * bx + d[7] * by);
            int m;
            if (v0 > v1) {
                if (v0 > v2)
                    m = (v0 > v3) ? 0 : 3;
                else
                    m = (v2 > v3) ? 2 : 3;
            } else {
                if (v1 > v2)
                    m = (v1 > v3) ? 1 : 3;
                else
                    m = (v2 > v3) ? 2 : 3;
            }
            switch (m) {
            case 0:
                ax = -d[0]; ay = -d[1];
                bx = -d[1]; by =  d[0];
                break;
            case 1:
                ax =  d[2]; ay =  d[3];
                bx =  d[3]; by = -d[2];
                break;
            case 2:
                ax = -d[5]; ay =  d[4];
                bx =  d[4]; by =  d[5];
                break;
            default:
                ax =  d[7]; ay = -d[6];
                bx = -d[6]; by = -d[7];
                break;
            }
            float p1 = (v[idx[1] * 2] - v[idx[0] * 2]) * bx
                     + (v[idx[1] * 2 + 1] - v[idx[0] * 2 + 1]) * by;
            float p2 = (v[idx[3] * 2] - v[idx[2] * 2]) * ax
                     + (v[idx[3] * 2 + 1] - v[idx[2] * 2 + 1]) * ay;
            float prod = p1 * p2;
            if (prod < best) {
                best = prod;
                if (p1 < p2) {
                    out[0] = bx; out[1] = by;
                } else {
                    out[0] = ax; out[1] = ay;
                }
            }
            i = m;
        }
        int j = (idx[i] + 1) % n;
        int j2 = (j + 1) % n;
        d[i * 2]     = v[j2 * 2]     - v[j * 2];
        d[i * 2 + 1] = v[j2 * 2 + 1] - v[j * 2 + 1];
        idx[i] = j;
        if (!(bx > 0.0f)) {
            int* volatile keep = &idx[i];
            (void)keep;
            return;
        }
    }
}

// @ 0x007217c0
ChartRef* ChartVec::MakeChartRef(ChartRef* out)
{
    ChartVec* this_ = this;
    void** begin = this_->begin;
    out->mNumElts = (int)((char*)this_->end - (char*)begin) / 0xc;
    out->mEltStride = 0xc;
    out->mData = begin;
    out->mEltSize = 0xc;
    out->mOwner = this_;
    return out;
}

// @ 0x00721850
void ChartHash::GrowF(uint32_t newSize)
{
    uint32_t size = newSize * 4;
    char* dst = (char*)EASTL_allocator_allocate(size + 4, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    op_new_array(dst, 0, size);
    *(int*)(size + (int)dst) = -1;
    uint32_t i = 0;
    if (mCapacity != 0) {
        do {
            FChartNode* n = (FChartNode*)mBuckets[i];
            while (n != 0) {
                uint32_t h = HashVec(&n->kx) % newSize;
                mBuckets[i] = n->next;
                n->next = *(FChartNode**)(dst + h * 4);
                *(FChartNode**)(dst + h * 4) = n;
                n = (FChartNode*)mBuckets[i];
            }
            i++;
        } while (i < mCapacity);
    }
    if (mCapacity > 1)
        EASTL_allocator_deallocate(mBuckets);
    mBuckets = (void**)dst;
    mCapacity = newSize;
}

// @ 0x00721910
void __stdcall DestroyChartRange(Chart68* first, Chart68* last)
{
    for (; first < last; first++) {
        if (first->v48 != 0 && ((int*)first->v48)[-1] != 0)
            EASTL_allocator_deallocate(first->v48);
        if (first->v34 != 0 && ((int*)first->v34)[-1] != 0)
            EASTL_allocator_deallocate(first->v34);
        if (first->v14 != 0 && ((int*)first->v14)[-1] != 0)
            EASTL_allocator_deallocate(first->v14);
    }
}

// @ 0x00721980
void* __cdecl DeleteTwoVtbl(TwoVtbl* this_, uint32_t flags)
{
    if (this_->p0c != 0 && ((int*)this_->p0c)[-1] != 0)
        EASTL_allocator_deallocate(this_->p0c);
    if (flags & 1)
        EASTL_allocator_deallocate(this_);
    return this_;
}

// @ 0x007219f0
void ChartHash::FindF(int* out, float* key)
{
    uint32_t h = HashVec(key) % mCapacity;
    FChartNode** slot = (FChartNode**)&mBuckets[h];
    FChartNode* n = *slot;
    if (n != 0) {
        do {
            if (key[0] == n->kx && key[1] == n->ky && key[2] == n->kz)
                goto found;
            n = n->next;
        } while (n != 0);
    }
    slot = (FChartNode**)&mBuckets[mCapacity];
    n = *slot;
found:
    HashFind r;
    r.pNode = n;
    r.pSlot = slot;
    *(HashFind*)out = r;
}

// @ 0x00721a80
void ChartHash::InsertF(int* out, float* key)
{
    uint32_t h = HashVec(key);
    uint32_t cap = mCapacity;
    uint32_t b = h % cap;
    FChartNode** slot = (FChartNode**)&mBuckets[b];
    FChartNode* n = *slot;
    while (n != 0) {
        if (key[0] == n->kx && key[1] == n->ky && key[2] == n->kz) {
            out[0] = (int)n;
            *((unsigned char*)out + 8) = 0;
            out[1] = (int)slot;
            return;
        }
        n = n->next;
    }
    FChartNode* nn = (FChartNode*)EASTL_allocator_allocate(0x14, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (nn != 0) {
        nn->kx = key[0]; nn->ky = key[1]; nn->kz = key[2]; nn->f0c = *(int*)((char*)key + 0xc);
    }
    nn->next = 0;
    b = h % mCapacity;
    slot = (FChartNode**)&mBuckets[b];
    nn->next = *slot;
    *slot = nn;
    mCount++;
    out[0] = (int)nn;
    *((unsigned char*)out + 8) = 1;
    out[1] = (int)slot;
}

// @ 0x00721bb0
void ChartHash::FindI(int* out, int* key)
{
    uint32_t h = (uint32_t)(key[0] ^ key[1] ^ key[2]) % mCapacity;
    IChartNode** slot = (IChartNode**)&mBuckets[h];
    IChartNode* n = *slot;
    while (n != 0) {
        if (n->k0 == key[0] && n->k1 == key[1] && n->k2 == key[2])
            goto found;
        n = n->next;
    }
    slot = (IChartNode**)&mBuckets[mCapacity];
    n = *slot;
found:
    HashFind r;
    r.pNode = n;
    r.pSlot = slot;
    void* volatile keep = memcpy(out, &r, sizeof(r));   // pair copy; keeps memcpy's destination (out) in eax
    (void)keep;
}

// @ 0x00721c30
void ChartHash::InsertI(int* out, int* key)
{
    uint32_t h = (uint32_t)(key[0] ^ key[1] ^ key[2]);
    uint32_t cap = mCapacity;
    uint32_t b = h % cap;
    IChartNode** slot = (IChartNode**)&mBuckets[b];
    IChartNode* n = *slot;
    while (n != 0) {
        if (n->k0 == key[0] && n->k1 == key[1] && n->k2 == key[2]) {
            out[0] = (int)n;
            *((unsigned char*)out + 8) = 0;
            out[1] = (int)slot;
            return;
        }
        n = n->next;
    }
    IChartNode* nn = (IChartNode*)EASTL_allocator_allocate(0x14, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (nn != 0) {
        nn->k0 = key[0]; nn->k1 = key[1]; nn->k2 = key[2]; nn->f0c = key[3];
    }
    nn->next = 0;
    b = h % mCapacity;
    slot = (IChartNode**)&mBuckets[b];
    nn->next = *slot;
    *slot = nn;
    mCount++;
    out[0] = (int)nn;
    *((unsigned char*)out + 8) = 1;
    out[1] = (int)slot;
}

// @ 0x00721d80
void* __cdecl CopyChart68(void* dst, void* src)
{
    unsigned char* d = (unsigned char*)dst;
    unsigned char* s = (unsigned char*)src;
    for (int i = 0; i < 0x50; i += 4)
        *(int*)(d + i) = *(int*)(s + i);
    return dst;
}

// @ 0x00722010
void __cdecl InitChartHash(ChartHash* this_)
{
    this_->mBuckets = 0;
    this_->mCapacity = 0;
    this_->mCount = 0;
}

// @ 0x007220c0
void __cdecl FreeChartThing(ChartHash* this_)
{
    if (this_->mBuckets != 0 && ((int*)this_->mBuckets)[-1] != 0)
        EASTL_allocator_deallocate(this_->mBuckets);
}

// @ 0x007221c0
void CMeshClusterer2::CollapseEdges()
{
    while (((char*)mEdgeHeap.mHeapEntries.mpEnd - (char*)mEdgeHeap.mHeapEntries.mpBegin) > 0) {
        float me = mMaxError;
        void* top = mEdgeHeap.mHeapEntries.mpBegin ? *(void**)mEdgeHeap.mHeapEntries.mpBegin : 0;
        if (!(me < 0.0f) && top && *(float*)top <= me && me != *(float*)top)
            break;
        void* e = 0;
        if (mEdgeHeap.mHeapEntries.mpEnd != mEdgeHeap.mHeapEntries.mpBegin) {
            e = *(void**)mEdgeHeap.mHeapEntries.mpBegin;
            *(int*)((char*)e + 4) = -1;
            *(void**)mEdgeHeap.mHeapEntries.mpBegin = *(void**)((char*)mEdgeHeap.mHeapEntries.mpEnd - 4);
            *(int*)(*(int*)mEdgeHeap.mHeapEntries.mpBegin + 4) = 0;
            mEdgeHeap.mHeapEntries.mpEnd = (char*)mEdgeHeap.mHeapEntries.mpEnd - 4;
            mEdgeHeap.HeapifyDown(0);
        }
        int i9 = *(int*)((char*)e + 8);
        int i12 = *(int*)((char*)e + 0xc);
        if (i9 != i12) {
            char* fc = (char*)mFaceClusters.mpBegin;
            char* a = fc + i9 * 0x28;
            char* b = fc + i12 * 0x28;
            for (int k = 0; k < 3; k++) {
                *(float*)(a + k * 4 + 0xc) += *(float*)(b + k * 4 + 0xc);
                *(float*)(a + k * 4) += *(float*)(b + k * 4);
            }
            *(float*)(a + 0x18) += *(float*)(b + 0x18);
            MergeEdgeLists(i9, i12);
            *(int*)(b + 0x20) = i9;
            mNumClusters--;
        }
    }
}

// @ 0x007222f0
void* __cdecl Insert34Vec(void* v, void* pos, void* val)
{
    (void)v; (void)pos; (void)val;
    return 0;
}
