// Slice s0071f410: SP mesh index-array (cEltArrayRef) stream helpers,
// eastl::vector<SP::cMDSection> insert / resize / range-assign, and the
// SP::cMeshData (0x58) deserializer.  Optimized module:
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast.
#include "types.h"
#include <string.h>
#include <intrin.h>

typedef unsigned int size_t_;

extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

// ---------------------------------------------------------------------------
// Allocation (EASTL sp_vector_allocator)
// ---------------------------------------------------------------------------
void* operator new(size_t_ n, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);            // 0x00f473a0
void  operator delete[](void* p);                          // 0x00f47380
#define ALLOC(n) operator new((n), "Graphics", 0, 0, \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL\\allocator.h", 0xd1)

// ---------------------------------------------------------------------------
// Ref counted buffer (EA::RefCountTemplate<EA::Thread::AtomicInt<int>>)
// ---------------------------------------------------------------------------
struct IRefCount {
    virtual int AddRef();       // slot 0
    virtual int Release();      // slot 1
};

// SP::cEltArrayRef / SP::cIndexArrayRef (0x10)
struct cEltArrayRef {
    int            mNumElts;    // +0x00
    unsigned char* mData;       // +0x04
    unsigned short mEltSize;    // +0x08
    unsigned short mEltStride;  // +0x0a
    IRefCount*     mDataRC;     // +0x0c
};

// ---------------------------------------------------------------------------
// Containers (retail layouts)
// ---------------------------------------------------------------------------
struct cMDSection;

template <typename T>
struct sp_vector {
    T* mpBegin;          // +0x0
    T* mpEnd;            // +0x4
    T* mpCapacity;       // +0x8
    uint32_t mAlloc[2];  // +0xc  sp_vector_allocator
    sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    int size() const { return (int)(mpEnd - mpBegin); }
};

// SP::cMDElementArray (0x20)
struct cMDElementArray { uint32_t m[8]; };

// SP::cMDPrimitive (0x14)
struct cMDPrimitive { int mPrimType, mSection, mStart, mEnd, mSubset; };

// SP::cMeshData (retail 0x58, vtable 0x013eb8d0)
struct cMeshData {
    void*   mVtbl;                            // +0x00
    int     mRefCount;                        // +0x04
    sp_vector<cMDElementArray> mEltArrays;    // +0x08
    sp_vector<cMDSection>      mSections;     // +0x1c
    sp_vector<cMDPrimitive>    mPrimitives;   // +0x30
    sp_vector<void*>           mAttachments;  // +0x44
};

char Obj13_e290(void* stream, void* self);                        // 0x0071e290
char Obj13_e320(void* stream, void* self);                        // 0x0071e320

// ---------------------------------------------------------------------------
// cIndexArrayRef ctor / copy ctor / copy-assign helpers (out of scope, kept verbatim).
// ---------------------------------------------------------------------------
void Obj15_Init(void* p);                                  // 0x00720070
void Obj15_Assign(void* src, void* dst, int flag);         // 0x0071fce0

// Small record: dword at +0, 16-bit at +8.
struct Obj15 {
    uint32_t m0;        // +0x0
    uint32_t m4;        // +0x4
    uint16_t m8;        // +0x8
};

// 0x18-byte Text::Vertex3D (6 dwords).
struct Vertex3D {
    uint32_t m[6];
};

// @ 0x00720190
void Obj15_ctor(uint32_t a, uint16_t b, Obj15* out)
{
    out->m0 = a;
    out->m8 = b;
    Obj15_Init(out);
}

// @ 0x007201b0
void Obj15_copy(const Obj15* src, Obj15* dst)
{
    dst->m0 = src->m0;
    dst->m8 = src->m8;
    Obj15_Init(dst);
}

// @ 0x007201d0
void Obj15_copyAssign(const Obj15* src, Obj15* dst)
{
    dst->m0 = src->m0;
    dst->m8 = src->m8;
    Obj15_Init(dst);
    Obj15_Assign((void*)src, dst, 0);
}

// @ 0x00720250
void CopyVertex3D(Vertex3D* first, Vertex3D* last, Vertex3D* dest)
{
    while (first != last) {
        *dest = *first;
        ++first;
        ++dest;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00720010
// cEltArrayRef buffer allocation: refcounted header (vtbl/refcount) + payload.
// ---------------------------------------------------------------------------
void* AllocEltBuffer(int n)
{
    if (n > 0) {
        if (n < 4)
            n = 4;
        int* p = (int*)operator new(n + 0xc, "Graphics", 0, 0, 0, 0);
        if (p) {
            p[0] = 0x13eb938;
            p[1] = 0x13ef094;
            _InterlockedExchange((volatile long*)&p[2], 0);
            p[0] = 0x140d02c;
            p[1] = 0x14188c0;
            return p;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00720070
// cEltArrayRef::Init: allocate the backing buffer and swap in the new ref.
// ---------------------------------------------------------------------------
void Obj15_Init(void* p)
{
    cEltArrayRef* self = (cEltArrayRef*)p;
    if (self->mNumElts > 0) {
        int n = self->mNumElts;
        n *= self->mEltSize;
        int* b = (int*)AllocEltBuffer(n);
        self->mData = (unsigned char*)b + 0xc;
        IRefCount* old = self->mDataRC;
        if ((IRefCount*)b != old) {
            if (b)
                ((IRefCount*)b)->AddRef();
            self->mDataRC = (IRefCount*)b;
            if (old)
                old->Release();
        }
        self->mEltStride = self->mEltSize;
    } else {
        self->mData = 0;
        IRefCount* b = self->mDataRC;
        if (b) {
            self->mDataRC = 0;
            b->Release();
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x0071fce0
// cEltArrayRef::AppendElements: copy src's elements into dst at dstIdx.
// ---------------------------------------------------------------------------
void Obj15_Assign(void* srcv, void* dstv, int dstIdx)
{
    cEltArrayRef* src = (cEltArrayRef*)srcv;
    cEltArrayRef* dst = (cEltArrayRef*)dstv;
    if (src->mNumElts == 0)
        return;
    char* d = (char*)dst->mData + dst->mEltStride * dstIdx;
    char* s = (char*)src->mData;
    if (src->mEltSize == src->mEltStride && dst->mEltSize == dst->mEltStride) {
        memcpy(d, s, src->mEltSize * src->mNumElts);
        return;
    }
    for (int i = 0; i < src->mNumElts; ++i) {
        memcpy(d, s, src->mEltSize);
        d += dst->mEltStride;
        s += src->mEltStride;
    }
}

// ---------------------------------------------------------------------------
// @ 0x0071ff50
// Fill `count` element indices with (base + i), one case per element width.
// ---------------------------------------------------------------------------
void FillEltIndices(int count, cEltArrayRef* dst, int start, int base)
{
    switch (dst->mEltSize) {
    case 1:
        for (int i = 0; i < count; ++i)
            *(char*)((char*)dst->mData + dst->mEltStride * (start + i)) = (char)(base + i);
        break;
    case 2:
        for (int i = 0; i < count; ++i)
            *(short*)((char*)dst->mData + dst->mEltStride * (start + i)) = (short)(base + i);
        break;
    case 4:
        for (int i = 0; i < count; ++i)
            *(int*)((char*)dst->mData + dst->mEltStride * (start + i)) = base + i;
        break;
    }
}

// ---------------------------------------------------------------------------
// @ 0x0071fd60
// Copy src[sIdx, eIdx) into dst at *out, stride aware; *out advances by count.
// ---------------------------------------------------------------------------
void CopyEltRange(cEltArrayRef* src, int sIdx, int eIdx, cEltArrayRef* dst, int* out)
{
    int n = eIdx - sIdx;
    char* s = (char*)src->mData + src->mEltStride * sIdx;
    char* d = (char*)dst->mData + dst->mEltStride * *out;
    if (src->mEltSize == src->mEltStride && dst->mEltSize == dst->mEltStride) {
        memcpy(d, s, src->mEltSize * n);
        *out += n;
        return;
    }
    for (int i = 0; i < n; ++i) {
        memcpy(d, s, src->mEltSize);
        d += dst->mEltStride;
        s += src->mEltStride;
    }
    *out += n;
}

// ---------------------------------------------------------------------------
// @ 0x0071fe10
// Copy src's elements into dst at dstIdx, masked to the src format and offset
// by `add` (a per-width case; the equal-stride fast path is a plain memcpy).
// ---------------------------------------------------------------------------
void CopyEltArrayAdd(cEltArrayRef* src, cEltArrayRef* dst, int dstIdx, int add)
{
    if (add == 0 && src->mEltSize == dst->mEltSize && src->mEltSize == src->mEltStride &&
        dst->mEltSize == dst->mEltStride) {
        memcpy((char*)dst->mData + dst->mEltStride * dstIdx, src->mData,
               src->mEltSize * src->mNumElts);
        return;
    }
    const int* mask = (const int*)0x140d018;
    switch (dst->mEltSize) {
    case 1:
        for (int i = 0; i < src->mNumElts; ++i)
            *(char*)((char*)dst->mData + dst->mEltStride * (dstIdx + i)) =
                (char)(((uint8_t)mask[src->mEltSize] & *(const uint8_t*)((char*)src->mData + src->mEltStride * i)) + add);
        break;
    case 2:
        for (int i = 0; i < src->mNumElts; ++i)
            *(short*)((char*)dst->mData + dst->mEltStride * (dstIdx + i)) =
                (short)(((uint16_t)mask[src->mEltSize] & *(const uint16_t*)((char*)src->mData + src->mEltStride * i)) + add);
        break;
    case 4:
        for (int i = 0; i < src->mNumElts; ++i)
            *(int*)((char*)dst->mData + dst->mEltStride * (dstIdx + i)) =
                (mask[src->mEltSize] & *(const int*)((char*)src->mData + src->mEltStride * i)) + add;
        break;
    }
}

// ===========================================================================
// SP::cMDSection machinery (retail 0x8c)
// ===========================================================================
struct cMDFormatEntry { short mElts; short mIndices; };

template <typename T, int N>
struct fixed_vector_base {
    T*       mpBegin;      // +0x00
    T*       mpEnd;        // +0x04
    T*       mpCapacity;   // +0x08
    uint32_t mOverflow;    // +0x0c
    void*    mpPoolBegin;  // +0x10
    uint32_t mUnused;      // +0x14
    uint32_t mBuffer[(sizeof(T) * N) / 4];   // +0x18
    fixed_vector_base()
    {
        mpBegin = mpEnd = (T*)mBuffer;
        mpPoolBegin = mBuffer;
        mpCapacity = (T*)mBuffer + N;
    }
};

struct AutoRefBuf {
    IRefCount* mp;
    AutoRefBuf& operator=(IRefCount* p)
    {
        if (p != mp) {
            IRefCount* old = mp;
            if (p)
                p->AddRef();
            mp = p;
            if (old)
                old->Release();
        }
        return *this;
    }
    AutoRefBuf& operator=(const AutoRefBuf& x) { return operator=(x.mp); }
};

// Assignment-loop view of a cMDSection (0x8c).
struct FixedIdVec {
    cMDFormatEntry* mpBegin; cMDFormatEntry* mpEnd; cMDFormatEntry* mpCap;
    void DoAssign(cMDFormatEntry* first, cMDFormatEntry* last, void* owner);   // 0x0042cd50
    void erase(cMDFormatEntry* first, cMDFormatEntry* last)
    {
        cMDFormatEntry* d = first;
        for (cMDFormatEntry* s = last; s != mpEnd; ++s, ++d)
            *d = *s;
        mpEnd -= (last - first);
    }
};
struct FixedEntryVec {
    char* mpBegin; char* mpEnd; char* mpCap;
    void Erase(char* first, char* last);                                       // 0x004772a0
    void DoAssign(char* first, char* last, void* owner);                       // 0x0042d020
};
struct SectionCopy {
    int        mF0;      // +0x00
    int        mF4;      // +0x04
    short      mS8;      // +0x08
    short      mSA;      // +0x0a
    AutoRefBuf mRef;     // +0x0c
    int        mF10;     // +0x10
    FixedIdVec mFormat;  // +0x14
    char       pad_20[0x44 - 0x20];
    FixedEntryVec mEltIndices;   // +0x44
    char       pad_50[0x8c - 0x50];
};

// SP::cMDSection (retail 0x8c): mVertIndices(0x10) + mNumVertices(4) + mFormat(0x30) + mEltIndices(0x48)
struct cMDSection {
    cEltArrayRef mVertIndices;                                                // +0x00
    int          mNumVertices;                                                // +0x10
    fixed_vector_base<cMDFormatEntry, 6> mFormat;                             // +0x14
    fixed_vector_base<cEltArrayRef, 3>   mEltIndices;                         // +0x44
    cMDSection() : mNumVertices(0) {}
    ~cMDSection();                                                            // 0x0041f940
    cMDSection(const cMDSection& o);                                          // 0x0042cba0
};

// ---------------------------------------------------------------------------
// @ 0x0071f410
// cMDSection range assignment (eastl::copy with cMDSection::operator=).
// ---------------------------------------------------------------------------
void CopySections(cMDSection* first, cMDSection* last, cMDSection* dest)
{
    for (; first != last; ++first, ++dest) {
        SectionCopy* d = (SectionCopy*)dest;
        SectionCopy* s = (SectionCopy*)first;
        d->mF0 = s->mF0;
        d->mF4 = s->mF4;
        d->mS8 = s->mS8;
        d->mSA = s->mSA;
        d->mRef = s->mRef.mp;
        d->mF10 = s->mF10;
        if (&d->mFormat != &s->mFormat) {
            d->mFormat.erase(d->mFormat.mpBegin, d->mFormat.mpEnd);
            d->mFormat.DoAssign(s->mFormat.mpBegin, s->mFormat.mpEnd, dest);
        }
        if (&d->mEltIndices != &s->mEltIndices) {
            d->mEltIndices.Erase(d->mEltIndices.mpBegin, d->mEltIndices.mpEnd);
            d->mEltIndices.DoAssign(s->mEltIndices.mpBegin, s->mEltIndices.mpEnd, dest);
        }
    }
}

// ===========================================================================
// eastl::vector<SP::cMDSection> helpers (out of line, live in this module)
// ===========================================================================
cMDSection* UninitCopySections(cMDSection* first, cMDSection* last, cMDSection* dst);    // 0x007192a0
void DestroySectionRange(cMDSection* first, cMDSection* last, cMDSection* dst);          // 0x00716380
void FillSectionRange(cMDSection* dst, unsigned n, const cMDSection& v, cMDSection* ref); // 0x0071f280
void MoveSectionRange(cMDSection* ref, cMDSection* first, cMDSection* last,
                      cMDSection* end, cMDSection* dst);                                 // 0x0071f200
void AssignSectionRange(cMDSection* first, cMDSection* last, void* tmp);                 // 0x0071f300
cMDSection* CopyBackwardSections(cMDSection* first, cMDSection* last, cMDSection* end);  // 0x00719890

struct SectionVec {
    cMDSection* mpBegin;     // +0x00
    cMDSection* mpEnd;       // +0x04
    cMDSection* mpCapacity;  // +0x08
    void DoInsertValues(cMDSection* position, unsigned n, const cMDSection& value);
    void erase(cMDSection* first, cMDSection* last);   // 0x0071f520
    void resize(unsigned n);
    int size() const { return (int)(mpEnd - mpBegin); }
};

// ---------------------------------------------------------------------------
// @ 0x0071f590
// eastl::vector<cMDSection>::DoInsertValues(position, n, value).
// ---------------------------------------------------------------------------
void SectionVec::DoInsertValues(cMDSection* position, unsigned n, const cMDSection& value)
{
    if ((unsigned)(mpCapacity - mpEnd) < n) {
        unsigned count = (unsigned)(mpEnd - mpBegin);
        unsigned cap = count ? 2 * count : 1;
        unsigned need = count + n;
        if (need < cap)
            need = cap;
        cMDSection* newBuf = need ? (cMDSection*)ALLOC(need * sizeof(cMDSection)) : 0;
        cMDSection* oldEnd = mpEnd;
        cMDSection* oldBeg = mpBegin;
        cMDSection* mid = UninitCopySections(oldBeg, position, newBuf);
        DestroySectionRange(oldBeg, position, newBuf);
        FillSectionRange(mid, n, value, mid);
        cMDSection* afterFill = mid + n;
        cMDSection* pos = mpEnd;
        UninitCopySections(pos, oldEnd, afterFill);
        DestroySectionRange(pos, oldEnd, afterFill);
        if (oldBeg && ((int*)oldBeg)[-1] != 0)
            operator delete[](oldBeg);
        mpEnd = afterFill;
        mpBegin = newBuf;
        mpCapacity = newBuf + need;
    } else if (n != 0) {
        cMDSection temp(value);
        cMDSection* end = mpEnd;
        unsigned old = (unsigned)(mpEnd - position);
        if (n < old) {
            cMDSection* cut = end - n;
            MoveSectionRange(&temp, cut, end, end, 0);
            cMDSection* oldPos = position;
            mpEnd += n;
            CopyBackwardSections(position, cut, end);
            AssignSectionRange(oldPos, oldPos + n, 0);
        } else {
            FillSectionRange(end, n - old, temp, position);
            cMDSection* oldPos = position;
            mpEnd += (n - old);
            MoveSectionRange(0, position, end, mpEnd, position);
            mpEnd += old;
            AssignSectionRange(oldPos, end, 0);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x0071f7e0
// eastl::vector<cMDSection>::resize(n): append default cMDSections or erase.
// ---------------------------------------------------------------------------
void SectionVec::resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin)) {
        cMDSection value;
        DoInsertValues(mpEnd, n - (unsigned)(mpEnd - mpBegin), value);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// ---------------------------------------------------------------------------
// @ 0x0071f8f0
// SP::cMeshData (0x58) deserializer: format tag 3/4, elt arrays, sections
// (with vertex index count, index format table, element index arrays) then
// primitives; returns the fresh cMeshData through *out.
// ---------------------------------------------------------------------------
extern "C" char FUN_0093a780(void* s, void* buf, int n, int pad);   // ReadInt32
extern "C" char FUN_0093a700(void* s, void* buf, int n, int pad);   // ReadUInt16
extern "C" char FUN_0093a6c0(void* s, void* buf, int n);            // ReadBytes
extern "C" char FUN_0093a890(void* s, int size, int count);         // HasRoom

void  FUN_00475260(cMeshData* md, int n);         // vector<cMDElementArray>::resize
void  FUN_004751a0(void* md, int n);              // vector<cEltArrayRef>::resize
void  FUN_0071ef50(void* v, int n);               // vector<int>::resize
void  MeshDataCtor(cMeshData* md);                // 0x0040d160
void  AutoRefCountDtor(cMeshData* md);            // 0x00472520

bool MeshDataLoad(void* stream, cMeshData** out)
{
    unsigned short format = 0;
    if (!FUN_0093a700(stream, &format, 1, 0) || (unsigned)(format - 3) > 1)
        return false;

    cMeshData* md = (cMeshData*)operator new(0x58, "Graphics", 0, 0, 0, 0);
    if (md) {
        MeshDataCtor(md);
    } else {
        md = 0;
    }
    if (md)
        _InterlockedIncrement((volatile long*)&md->mRefCount);

    int nEltArrays;
    if (!FUN_0093a780(stream, &nEltArrays, 1, 0) ||
        !FUN_0093a890(stream, 0x10, nEltArrays)) {
        AutoRefCountDtor(md);
        return false;
    }
    FUN_00475260(md, nEltArrays);
    for (int i = 0; i < nEltArrays; ++i) {
        cMDElementArray* ea = &md->mEltArrays.mpBegin[i];
        unsigned int v;
        if (!FUN_0093a6c0(stream, &v, 4))
            goto fail;
        ea->m[0] = v & 0xff;
        ea->m[1] = (v >> 8) & 0xff;
        ea->m[2] = (v >> 16) & 0xff;
        ea->m[3] = v >> 24;
        if (format < 4) {
            if (!Obj13_e320(stream, (char*)ea + 0x10))
                goto fail;
        } else {
            if (!Obj13_e290(stream, (char*)ea + 0x10))
                goto fail;
        }
    }

    int nSections;
    if (!FUN_0093a780(stream, &nSections, 1, 0) ||
        !FUN_0093a890(stream, nSections, 1))
        goto fail;

    ((SectionVec*)&md->mSections)->resize((unsigned)nSections);
    for (int i = 0; i < nSections; ++i) {
        cMDSection* sec = &md->mSections.mpBegin[i];
        if (format < 4) {
            if (!Obj13_e320(stream, sec))
                goto fail;
        } else {
            if (!Obj13_e290(stream, sec))
                goto fail;
        }
        if (!FUN_0093a780(stream, &sec->mNumVertices, 1, 0))
            goto fail;
        unsigned char nIdx;
        if (!FUN_0093a6c0(stream, &nIdx, 1))
            goto fail;
        if (!FUN_0093a890(stream, 4, nIdx))
            goto fail;
        FUN_0071ef50(&sec->mFormat, nIdx);
        if (!FUN_0093a700(stream, sec->mFormat.mpBegin,
                          ((char*)sec->mFormat.mpEnd - (char*)sec->mFormat.mpBegin) >> 1,
                          0))
            goto fail;
        if (!FUN_0093a6c0(stream, &nIdx, 1))
            goto fail;
        FUN_004751a0(&sec->mEltIndices, nIdx);
        for (int j = 0; j < nIdx; ++j) {
            cEltArrayRef* ref = (cEltArrayRef*)((char*)sec->mEltIndices.mpBegin + j * 0x10);
            if (format < 4) {
                if (!Obj13_e320(stream, ref))
                    goto fail;
            } else {
                if (!Obj13_e290(stream, ref))
                    goto fail;
            }
        }
    }

    int nPrims;
    if (!FUN_0093a780(stream, &nPrims, 1, 0) ||
        !FUN_0093a890(stream, 0x14, nPrims))
        goto fail;
    ((SectionVec*)&md->mPrimitives)->resize((unsigned)nPrims);
    if (!FUN_0093a6c0(stream, md->mPrimitives.mpBegin, nPrims * 0x14))
        goto fail;

    *out = md;
    _InterlockedIncrement((volatile long*)&md->mRefCount);
    AutoRefCountDtor(md);
    return true;

fail:
    AutoRefCountDtor(md);
    return false;
}

// ---------------------------------------------------------------------------
// Remaining out-of-slice skeletons (kept verbatim).
// ---------------------------------------------------------------------------
// @ 0x007200f0
void Obj15_200f0(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }
// @ 0x00720200
void Obj15_20200(void* a, void* b) { (void)a; (void)b; }
