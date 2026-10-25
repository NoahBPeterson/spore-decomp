// cTextureChart hash containers and chart helpers (retail offsets from disasm).
#include "types.h"
#include <string.h>
#include <math.h>
#include <xmmintrin.h>

extern "C" void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int a, int b,
                                                  const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl op_new_array(void* dst, int zero, uint32_t size);
extern "C" void* __cdecl MoveCopy34(void* first, void* last, void* dest); // 0x00720dd0
extern "C" void  __cdecl UninitCopy8(void** outEnd, const void* first, const void* last,
                                     void* dest, const void* tag); // 0x00479c00
extern char vtbl_13ef094[];          // 0x013ef094
extern char vtbl_13eb938[];          // 0x013eb938
extern char vtbl_140d0c8[];          // 0x0140d0c8
extern float g_chartInitZero;        // 0x013eb1bc
extern const char kEastlAllocName[]; // 0x013eb8a4  "Graphics"
extern const char kEastlAllocFile[]; // 0x013ebb38  ".../EASTL/allocator.h"
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

struct TwoVtbl {
    void* vt0;     // +0x00
    void* vt1;     // +0x04
    void* pad08;   // +0x08
    void* p0c;     // +0x0c
    void* DeleteObject(uint32_t flags);
};

// 8-byte element of the vector at chart+0x50 (begin/end/cap at +0x50/+0x54/+0x58).
struct ChartElem8 { uint32_t x; uint32_t y; };
struct ChartVec8 {
    ChartElem8* mpBegin;    // +0x00
    ChartElem8* mpEnd;      // +0x04
    ChartElem8* mpCap;      // +0x08
    void Allocate(uint32_t n, const void* tag);   // 0x006a40a0
};
struct ChartCopy {
    uint32_t m00;                                                      // +0x00
    float    m04, m08, m0c, m10, m14, m18, m1c;                        // +0x04..+0x1c
    float    m20, m24, m28, m2c, m30, m34;                             // +0x20..+0x34
    uint32_t m38, m3c, m40, m44, m48, m4c;                             // +0x38..+0x4c
    ChartVec8 mTail;                                                   // +0x50
    const void* mAlloc;                                                // +0x5c
    void* CopyFrom(ChartCopy* src);
};

// Virtual interfaces whose calls the destructor at 0x7220c0 performs.
struct RefObj {
    virtual void slot0();     // vtable +0x00
    virtual void Release();   // vtable +0x04
};
struct RefCounted {
    virtual void* DestroyObject(uint32_t flags);   // vtable +0x00
    uint32_t mRefCount;                            // +0x04
};
struct BigVec {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCap;        // +0x08
    void DestroyRange(void* first, void* last);   // 0x00721810
};
// Owner initialised by 0x722010 and torn down by 0x7220c0.
struct BigObj {
    void*       mpVtbl;    // +0x00
    void*       m04;       // +0x04
    RefCounted* mRef8;     // +0x08
    BigVec      mVec;      // +0x0c
    uint32_t    pad18;     // +0x18  (left untouched by the initialiser)
    uint32_t    pad1c;     // +0x1c
    void*       m20;       // +0x20
    void*       m24;       // +0x24
    uint16_t    m28;       // +0x28
    uint16_t    m2a;       // +0x2a
    RefObj*     m2c;       // +0x2c
    void*       m30;       // +0x30
    void*       m34;       // +0x34
    void*       m38;       // +0x38
    uint16_t    m3c;       // +0x3c
    uint16_t    m3e;       // +0x3e
    RefObj*     m40;       // +0x40
    void*       m44;       // +0x44
    void*       m48;       // +0x48
    void*       m4c;       // +0x4c
    void*       m50;       // +0x50
    uint32_t    pad54;     // +0x54  (left untouched)
    uint32_t    pad58;     // +0x58
    void*       m5c;       // +0x5c
    void*       m60;       // +0x60
    void*       m64;       // +0x64
    uint32_t    pad68;     // +0x68  (left untouched)
    uint32_t    pad6c;     // +0x6c
    void*       m70;       // +0x70
    void*       m74;       // +0x74
    void*       m78;       // +0x78
    uint32_t    pad7c;     // +0x7c  (left untouched)
    uint32_t    pad80;     // +0x80
    float       m84;       // +0x84
    void*       m88;       // +0x88
    void*       m8c;       // +0x8c
    BigObj* InitFields();
    void FreeObject();
};

// 0x34-byte element of the vector inserted by 0x7222f0.
struct Elem34 {
    uint32_t w[13];
    void CopyConstruct(const Elem34& src);   // 0x006de7f0
};
struct Vec34 {
    Elem34* mpBegin;   // +0x00
    Elem34* mpEnd;     // +0x04
    Elem34* mpCap;     // +0x08
    void Insert(Elem34* pos, const Elem34* val);
};

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
void* TwoVtbl::DeleteObject(uint32_t flags)
{
    if (p0c != 0 && ((int*)p0c)[-1] != 0)
        EASTL_allocator_deallocate(p0c);
    vt1 = vtbl_13ef094;
    vt0 = vtbl_13eb938;
    if (flags & 1)
        EASTL_allocator_deallocate(this);
    return this;
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
void* ChartCopy::CopyFrom(ChartCopy* src)
{
    const ChartCopy& s = *src;
    m00 = s.m00;
    m04 = s.m04;
    m08 = s.m08;
    m0c = s.m0c;
    m10 = s.m10;
    m14 = s.m14;
    m18 = s.m18;
    m1c = s.m1c;
    m20 = s.m20;
    m24 = s.m24;
    m28 = s.m28;
    m2c = s.m2c;
    m30 = s.m30;
    m34 = s.m34;
    m38 = s.m38;
    m3c = s.m3c;
    m40 = s.m40;
    m44 = s.m44;
    m48 = s.m48;
    m4c = s.m4c;
    uint32_t n = (uint32_t)(((char*)s.mTail.mpEnd - (char*)s.mTail.mpBegin) >> 3);
    mTail.Allocate(n, &s.mAlloc);
    void* outEnd;
    UninitCopy8(&outEnd, s.mTail.mpBegin, s.mTail.mpEnd, mTail.mpBegin, src);
    mTail.mpEnd = (ChartElem8*)outEnd;
    return this;
}

// @ 0x00722010
BigObj* BigObj::InitFields()
{
    m04 = 0;
    mpVtbl = vtbl_140d0c8;
    mRef8 = 0;
    mVec.mpBegin = 0;
    mVec.mpEnd = 0;
    mVec.mpCap = 0;
    m20 = 0;
    m24 = 0;
    m28 = 4;
    m2a = 4;
    m2c = 0;
    m30 = 0;
    m34 = 0;
    m38 = 0;
    m3c = 4;
    m3e = 4;
    m40 = 0;
    m44 = 0;
    m48 = 0;
    m4c = 0;
    m50 = 0;
    m5c = 0;
    m60 = 0;
    m64 = 0;
    m70 = 0;
    m74 = 0;
    m78 = 0;
    m88 = 0;
    m8c = 0;
    m84 = g_chartInitZero;
    return this;
}

// @ 0x007220c0
void BigObj::FreeObject()
{
    if (m70 != 0 && ((int*)m70)[-1] != 0)
        EASTL_allocator_deallocate(m70);
    if (m5c != 0 && ((int*)m5c)[-1] != 0)
        EASTL_allocator_deallocate(m5c);
    if (m48 != 0 && ((int*)m48)[-1] != 0)
        EASTL_allocator_deallocate(m48);
    if (m40 != 0)
        m40->Release();
    if (m2c != 0)
        m2c->Release();
    mVec.DestroyRange(mVec.mpBegin, mVec.mpEnd);
    if (mVec.mpBegin != 0 && ((int*)mVec.mpBegin)[-1] != 0)
        EASTL_allocator_deallocate(mVec.mpBegin);
    if (mRef8 != 0) {
        if (--mRef8->mRefCount == 0) {
            mRef8->mRefCount = 1;
            mRef8->DestroyObject(1);
        }
    }
    mpVtbl = vtbl_13ef094;
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
void Vec34::Insert(Elem34* pos, const Elem34* val)
{
    if (mpEnd != mpCap) {
        const Elem34* v = val;
        if (v >= pos && v < mpEnd)
            ++v;
        if (mpEnd != 0)
            mpEnd->CopyConstruct(mpEnd[-1]);
        Elem34* s = mpEnd - 1;
        Elem34* d = mpEnd;
        while (s != pos) {
            --s;
            --d;
            *d = *s;
        }
        *pos = *v;
        mpEnd++;
    } else {
        uint32_t count = (uint32_t)(mpEnd - mpBegin);
        uint32_t newCap;
        if (count != 0)
            newCap = count * 2;
        else
            newCap = 1;
        Elem34* newBuf = newCap == 0 ? 0 :
            (Elem34*)EASTL_allocator_allocate(newCap * 0x34, kEastlAllocName, 0, 0,
                                              kEastlAllocFile, 0xd1);
        Elem34* out = (Elem34*)MoveCopy34(mpBegin, pos, newBuf);
        if (out != 0)
            out->CopyConstruct(*val);
        ++out;
        Elem34* end = (Elem34*)MoveCopy34(pos, mpEnd, out);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            EASTL_allocator_deallocate(mpBegin);
        mpCap = newBuf + newCap;
        mpEnd = end;
        mpBegin = newBuf;
    }
}
