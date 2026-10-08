// Slice s00719e10: SP::cMeshBuilder methods (BeginMesh/ClearMeshInfo/etc.) and the
// eastl::vector<T28>::resize instance. Optimized module with SSE:
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast.
#include "types.h"
#include <intrin.h>

typedef unsigned int size_t;

void* __cdecl xmemcpy(void* d, const void* s, size_t n);      // 0x011e0744
void SpFree(void* p);                                        // 0x00f47380
void* SpAlloc(unsigned size, const char* area, int a, int b, const char* file, int line); // 0x00f473a0

struct cSPVector2 { float x, y; };
struct cSPVector3 { float x, y, z; };
struct tMDUByte4 { unsigned char a, b, c, d; };
struct Float4 { float x, y, z, w; };

// sp_vector: 3 pointers + a 4-byte allocator (16 bytes total).
template <typename T>
struct spvec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAlloc[1];
    spvec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~spvec() { if (mpBegin && ((uint32_t*)mpBegin)[-1]) SpFree(mpBegin); }
    void clear();
    void erase(T* first, T* last);
    void resize(uint32_t n);
    void DoInsertValue(T* position, const T& value);
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity) {
            if (mpEnd)
                *mpEnd = value;
            ++mpEnd;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};
template <typename T>
struct spvec1 { spvec<T> v; uint32_t mAfter; };

// 0x28-byte element: two 16-byte vectors at +0 and +0x14 (scalars at +0x10, +0x24).
struct T28 {
    int* mB0; int* mE0; int* mC0; uint32_t mA0;   // +0x00
    uint32_t mX;                                  // +0x10
    int* mB1; int* mE1; int* mC1; uint32_t mA1;   // +0x14
    uint32_t mY;                                  // +0x24
    T28() { mB0 = 0; mE0 = 0; mC0 = 0; mB1 = 0; mE1 = 0; mC1 = 0; }
    ~T28() throw() { if (mB1 && ((uint32_t*)mB1)[-1]) SpFree(mB1);
                     if (mB0 && ((uint32_t*)mB0)[-1]) SpFree(mB0); }
};
struct Vec28 {
    T28* mpBegin; T28* mpEnd; T28* mpCapacity; uint32_t mAlloc[1];
    void insert(T28* position, uint32_t n, const T28& value);   // 0x00719a00
    void erase(T28* first, T28* last);                          // 0x007199b0
    void resize(uint32_t n);
};

// One index list of the mesh builder (eastl::vector<unsigned,sp_vector_allocator>), 0x14 bytes.
struct UVec {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; uint32_t mAlloc; uint32_t mAfter;
    void DoInsertValue(uint32_t* position, const uint32_t& value);   // 0x004558a0 (ret 8)
    void push_back(const uint32_t& value)
    {
        if (mpEnd < mpCapacity) {
            uint32_t* p = mpEnd++;
            if (p)
                *p = value;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
    void clear()
    {
        uint32_t* first = mpBegin;
        uint32_t* last = mpEnd;
        xmemcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd = mpEnd - (last - first);
    }
};

// 0xd0-byte element (fills cMeshBuilder::mSections): one section = one distinct attribute mask.
struct T140 {
    uint32_t mMask;          // +0x00  which attribute streams are present (bit0 position .. bit7 colour 1)
    int      mCount;         // +0x04  number of vertices emitted so far
    UVec     mAttr[8];       // +0x08  position, normal, 4x texcoord, 2x colour index streams
    UVec     mUnk;           // +0xa8
    UVec     mIndices;       // +0xbc  triangle/line index list
    T140(); ~T140(); T140(const T140&);
};

// One draw batch (0x14 bytes) of cMeshBuilder::mV2.
struct Batch {
    int      mType;          // +0x00  primitive type (4 = triangle list)
    uint32_t mSection;       // +0x04
    int      mStart;         // +0x08  first index in the section's index list
    int      mEnd;           // +0x0c  -1 while open
    int      mExtra;         // +0x10
};

// Simple non-atomic refcounted base for the AutoRefCount<> field.
struct RefCounted {
    void** mpVtbl;      // +0x0
    long   mnRefCount;  // +0x4
    int Release()
    {
        if (_InterlockedExchangeAdd(&mnRefCount, -1) == 1) {
            mnRefCount = 1;
            ((void (__thiscall*)(RefCounted*, int))mpVtbl[0])(this, 1);
            return 0;
        }
        return mnRefCount;
    }
};

struct cMeshBuilder {
    char pad_00[0x8];
    spvec1<cSPVector3> mPositions;                   // +0x08
    spvec1<cSPVector3> mNormals;                     // +0x1c
    spvec1<cSPVector2> mTexCoords[4];                // +0x30
    spvec1<tMDUByte4>  mColors[2];                   // +0x80
    spvec1<int>        mV0;                          // +0xa8
    spvec1<int>        mV1;                          // +0xbc
    spvec1<T140>       mSections;                    // +0xd0
    spvec1<Batch>      mV2;                          // +0xe4   draw batches (0x14-byte element)
    spvec1<uint64_t>   mV3;                          // +0xf8   (8-byte element)
    spvec1<int>        mV4;                          // +0x10c
    spvec1<int>        mV5;                          // +0x120
    spvec1<int>        mV6;                          // +0x134
    RefCounted*        mMeshData;                    // +0x148
    uint32_t           mKey;                         // +0x14c
    bool               mInMesh;                      // +0x150
    char pad_151[3];
    int                mPrimType;                    // +0x154  current primitive type (4 list, 9 polygon)
    int                m158;                         // +0x158
    int                m15c;                         // +0x15c
    int                m160;                         // +0x160
    int                m164;                         // +0x164
    int                m168;                         // +0x168
    int                m16c;                         // +0x16c
    int                m170;                         // +0x170
    int                m174;                         // +0x174
    int                m178;                         // +0x178
    int                m17c;                         // +0x17c
    int                m180;                         // +0x180
    int                m184;                         // +0x184
    UVec               mPrim[8];                     // +0x188  per-vertex attribute indices of the current primitive
                                                     //         (position, normal, 4x texcoord, 2x colour)

    void BeginMesh();
    void EndPrimitive();
    void ClearMeshInfo();
};

int  cMeshBuilder_ClearChildVec(cMeshBuilder* self, int a, void* b);   // 0x00717820
void ClearAnimatedBabyVec(uint32_t a, uint32_t b);                     // 0x009c69f0

// ===========================================================================
// @ 0x0071a930
void Vec28::resize(uint32_t n)
{
    if (n > (uint32_t)(mpEnd - mpBegin)) {
        T28 v;
        insert(mpEnd, n - (uint32_t)(mpEnd - mpBegin), v);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x0071aa20
void cMeshBuilder::BeginMesh()
{
    mInMesh = true;
    if (mMeshData == 0)
        ClearMeshInfo();
    if (mMeshData != 0) {
        RefCounted* p = mMeshData;
        mMeshData = 0;
        p->Release();
    }
    mKey = 0x9f84a565;
    m164 = (int)(mSections.v.mpEnd - mSections.v.mpBegin);
    m168 = (int)(mPositions.v.mpEnd - mPositions.v.mpBegin);
    m16c = (int)(mNormals.v.mpEnd - mNormals.v.mpBegin);
    m170 = (int)(mTexCoords[0].v.mpEnd - mTexCoords[0].v.mpBegin);
    m174 = (int)(mTexCoords[1].v.mpEnd - mTexCoords[1].v.mpBegin);
    m178 = (int)(mTexCoords[2].v.mpEnd - mTexCoords[2].v.mpBegin);
    m17c = (int)(mTexCoords[3].v.mpEnd - mTexCoords[3].v.mpBegin);
    m180 = (int)(mColors[0].v.mpEnd - mColors[0].v.mpBegin);
    m184 = (int)(mColors[1].v.mpEnd - mColors[1].v.mpBegin);
    m158 = -1;
    m15c = -1;
    m160 = -1;
}

// @ 0x0071a650
void cMeshBuilder::ClearMeshInfo()
{
    mV0.v.clear();
    mV1.v.clear();
    mV2.v.clear();
    mV3.v.clear();
    for (int i = 0; i < 4; ++i)
        mTexCoords[i].v.clear();
    for (int i = 0; i < 2; ++i)
        mColors[i].v.clear();
    ClearAnimatedBabyVec((uint32_t)(size_t)mV4.v.mpEnd, (uint32_t)(size_t)mV5.v.mpEnd);
    mV5.v.erase(mV5.v.mpBegin, mV5.v.mpEnd);
    mV6.v.erase(mV6.v.mpBegin, mV6.v.mpEnd);
    mV2.v.erase(mV2.v.mpBegin, mV2.v.mpEnd);
    mV6.v.erase(mV6.v.mpBegin, mV6.v.mpEnd);
    mV2.v.erase(mV2.v.mpBegin, mV2.v.mpEnd);
    mV3.v.erase(mV3.v.mpBegin, mV3.v.mpEnd);
}

// @ 0x0071ab60
void cMeshBuilder_Transform(cMeshBuilder* self, uint32_t param)
{
    self->mV5.v.resize(param);
    Float4 m[3];
    float* p = (float*)m;
    for (int i = 0; i < 12; ++i)
        p[i] = 0.0f;
    m[0].x = 1.0f;
    m[1].y = 1.0f;
    m[2].z = 1.0f;
    cMeshBuilder_ClearChildVec(self, param, m);
}

// bitset<11>::test(pos): out-of-range positions read as 0.
static __forceinline bool TestBit11(unsigned mask, unsigned pos)
{
    return pos < 11 && (mask & (1u << pos)) != 0;
}

static __forceinline void SetBit(unsigned& mask, unsigned bit, bool on)
{
    if (on)
        mask |= bit;
    else
        mask &= ~bit;
}

static __forceinline bool IsSingle(const UVec& v)
{
    return (((char*)v.mpEnd - (char*)v.mpBegin) & ~3) == 4;
}

// @ 0x00719e10
// Flush the current primitive (per-vertex attribute index lists in mPrim[]) into the section that
// matches the set of present attributes, then triangulate (polygon type 9 -> fan) or append the
// vertices, open a new draw batch when the type/section/extra changed, and clear the lists.
void cMeshBuilder::EndPrimitive()
{
    unsigned mask = (mPrim[0].mpBegin != mPrim[0].mpEnd);
    SetBit(mask, 2, mPrim[1].mpBegin != mPrim[1].mpEnd);
    SetBit(mask, 4, mPrim[2].mpBegin != mPrim[2].mpEnd);
    SetBit(mask, 8, mPrim[3].mpBegin != mPrim[3].mpEnd);
    SetBit(mask, 0x10, mPrim[4].mpBegin != mPrim[4].mpEnd);
    SetBit(mask, 0x20, mPrim[5].mpBegin != mPrim[5].mpEnd);
    SetBit(mask, 0x40, mPrim[6].mpBegin != mPrim[6].mpEnd);
    SetBit(mask, 0x80, mPrim[7].mpBegin != mPrim[7].mpEnd);

    // find (or create) the section for this attribute mask, searching from the mesh's first section
    uint32_t secIdx = (uint32_t)m164;
    if (secIdx < (uint32_t)(mSections.v.mpEnd - mSections.v.mpBegin)) {
        T140* s = mSections.v.mpBegin + secIdx;
        do {
            if (s->mMask == mask)
                break;
            ++secIdx;
            ++s;
        } while (secIdx < (uint32_t)(mSections.v.mpEnd - mSections.v.mpBegin));
    }
    int zero = 0;
    if (secIdx == (uint32_t)(mSections.v.mpEnd - mSections.v.mpBegin)) {
        mSections.v.resize(secIdx + 1);
        mSections.v.mpBegin[secIdx].mMask = mask;
        mSections.v.mpBegin[secIdx].mCount = zero;
    }
    uint32_t secOffset = secIdx * 0xd0;
    T140* sec = mSections.v.mpBegin + secIdx;

    // append the indices of every vertex of the primitive to the section's attribute streams
    uint32_t vi = zero;
    if ((uint32_t)(mPrim[0].mpEnd - mPrim[0].mpBegin) != 0) {
        do {
            if (IsSingle(mPrim[0])) {
                uint32_t v = m168 + mPrim[0].mpBegin[0];
                sec->mAttr[0].push_back(v);
            } else if (mask & 1) {
                uint32_t v = mPrim[0].mpBegin[vi] + m168;
                sec->mAttr[0].push_back(v);
            }
            if (IsSingle(mPrim[1])) {
                uint32_t v = m16c + mPrim[1].mpBegin[0];
                sec->mAttr[1].push_back(v);
            } else if ((mask >> 1) & 1) {
                uint32_t v = mPrim[1].mpBegin[vi] + m16c;
                sec->mAttr[1].push_back(v);
            }
            int* texBase = &m170;
            for (int k = 0; k < 4; ++k) {
                const UVec& src = mPrim[2 + k];
                uint32_t v;
                if (IsSingle(src))
                    v = texBase[k] + src.mpBegin[0];
                else if (TestBit11(mask, k + 2))
                    v = src.mpBegin[vi] + texBase[k];
                else
                    continue;
                sec->mAttr[2 + k].push_back(v);
            }
            int* colBase = &m180;
            for (int k = 0; k < 2; ++k) {
                const UVec& src = mPrim[6 + k];
                uint32_t v;
                if (IsSingle(src))
                    v = colBase[k] + src.mpBegin[0];
                else if (TestBit11(mask, k + 6))
                    v = src.mpBegin[vi] + colBase[k];
                else
                    continue;
                sec->mAttr[6 + k].push_back(v);
            }
            ++vi;
        } while (vi < (uint32_t)(mPrim[0].mpEnd - mPrim[0].mpBegin));
    }

    // vertices of the primitive are numbered from the section's previous vertex count
    uint32_t first = (uint32_t)sec->mCount;
    sec->mCount = (int)(sec->mAttr[0].mpEnd - sec->mAttr[0].mpBegin);

    if (mPrimType == 9) {
        // polygon: triangulate as a fan
        uint32_t cur = (uint32_t)m160;
        if (secIdx != cur || m158 != m15c || mV2.v.mpEnd[-1].mType != 4) {
            if ((int)cur >= 0)
                mV2.v.mpEnd[-1].mEnd = (int)(mSections.v.mpBegin[cur].mIndices.mpEnd - mSections.v.mpBegin[cur].mIndices.mpBegin);
            Batch nb;
            nb.mType = 4;
            nb.mSection = secIdx;
            nb.mStart = (int)(mSections.v.mpBegin[secIdx].mIndices.mpEnd - mSections.v.mpBegin[secIdx].mIndices.mpBegin);
            nb.mEnd = -1;
            nb.mExtra = m158;
            mV2.v.push_back(nb);
        }
        uint32_t prev = first + 1;
        uint32_t next = first + 2;
        uint32_t k = 2;
        uint32_t n = (uint32_t)(mPrim[0].mpEnd - mPrim[0].mpBegin);
        if (n > 2) {
            do {
                uint32_t a = first;
                uint32_t b = prev;
                uint32_t c = next;
                sec->mIndices.push_back(a);
                sec->mIndices.push_back(b);
                sec->mIndices.push_back(c);
                ++k;
                ++next;
                prev = c;
            } while (k < (uint32_t)(mPrim[0].mpEnd - mPrim[0].mpBegin));
        }
    } else {
        if (mV2.v.mpBegin == mV2.v.mpEnd || mV2.v.mpEnd[-1].mType != 4 || mPrimType != 4
            || secIdx != (uint32_t)m160 || m158 != m15c) {
            if (m160 >= 0)
                mV2.v.mpEnd[-1].mEnd = (int)(mSections.v.mpBegin[m160].mIndices.mpEnd - mSections.v.mpBegin[m160].mIndices.mpBegin);
            Batch nb;
            nb.mType = mPrimType;
            nb.mSection = secIdx;
            nb.mStart = (int)(mSections.v.mpBegin[secIdx].mIndices.mpEnd - mSections.v.mpBegin[secIdx].mIndices.mpBegin);
            nb.mEnd = -1;
            nb.mExtra = m158;
            mV2.v.push_back(nb);
        }
        int n = (int)(mPrim[0].mpEnd - mPrim[0].mpBegin);
        uint32_t idx = first;
        if (n > 0) {
            do {
                uint32_t v = idx;
                sec->mIndices.push_back(v);
                ++idx;
                --n;
            } while (n != 0);
        }
    }

    mPrim[0].clear();
    mPrim[1].clear();
    for (int k = 0; k < 4; ++k)
        mPrim[2 + k].clear();
    for (int k = 0; k < 2; ++k)
        mPrim[6 + k].clear();
    m15c = m158;
    m160 = (int)secIdx;
    mPrimType = 0;
}
