// Slice s00476dd0: eastl::vector<T> copy/realloc/erase/insert helpers and small copy loops.
// Built /Od /Ob1 /MD /Gy /TP.
#include "types.h"

typedef unsigned int uint;
void* EASTL_Allocate(void* alloc, uint bytes, uint align, uint flags);   // @ 0x0042dee0
void  EASTL_allocator_deallocate(void* p);                               // @ 0x00f47380

// refcounted member: the vtable slot the original releases through is slot 1 (+0x4)
struct Counted;
struct CountedVtbl {
    void* mpSlot0;                                  // +0x0
    void (*mpRelease)(Counted* p);                  // +0x4
};
struct Counted {
    CountedVtbl* mpVtbl;                            // +0x0
    void Release() { mpVtbl->mpRelease(this); }     // virtual slot 1
};

// dword stored immediately before an EASTL allocation block
struct AllocPrefix { uint32_t mDebugFill; };

// DoAssign's third argument is an empty iterator-category tag passed by value. The original
// /Od build passes an uninitialised one-byte local (0xcc, the harness stack fill pattern);
// the callee never reads it.
struct FwdTag { unsigned char mKind; };

// receiver stubs (the originals take `this` in ECX)
struct AllocOwner { void* ReallocRefs4(uint n, void* first, void* last); };
struct Elem7c {
    void Destroy7c();                                  // @ 0x0041f2d0
};
struct Range7c { void DestroyRange7c(char* first, char* last); };

// ---- generic 4-byte value ---------------------------------------------------------------
typedef uint I4;

// ---- vtable-bearing 16/32-byte elements ------------------------------------------------
struct V16 {
    char pad[0xc];
    Counted* mpRef;                                    // +0xc refcounted member
    V16& Assign(const V16& src);                       // @ 0x00424f70
};
struct V32 {
    V16 m0;                                            // +0x00
    V16 m1;                                            // +0x10 (refcounted ptr at +0x1c)
    V32& Assign(const V32& src);                       // @ 0x00424f10
};
struct Vec16 {
    V16* mpBegin; V16* mpEnd; V16* mpCapacity;
    V16* EraseV16(V16* first, V16* last);
    void Assign(const V16* first, const V16* last, FwdTag tag);   // @ 0x0042d020
};
struct Vec32 { V32* mpBegin; V32* mpEnd; V32* mpCapacity; V32* EraseV32(V32* first, V32* last); };

// ---- 4-byte vector embedded in Big8c ----------------------------------------------------
struct VecI4 {
    I4* mpBegin; I4* mpEnd; I4* mpCapacity;
    void Erase(I4* first, I4* last);                             // @ 0x004ce270
    void Assign(const I4* first, const I4* last, FwdTag tag);     // @ 0x0042cd50
};

// ---- 0x8c-byte element ------------------------------------------------------------------
struct Big8c {
    V16 m0;             // +0x00 refcounted 16-byte member
    uint32_t m10;       // +0x10
    VecI4 vec14;        // +0x14 vector of 4-byte values
    char pad20[0x24];   // +0x20
    Vec16 vec44;        // +0x44 vector of 16-byte values
    char pad50[0x3c];   // +0x50
    Big8c* Assign(const Big8c& src);                // @ 0x00477700 (assignment)
    Big8c* CopyConstruct(const Big8c& src);         // @ 0x0042cba0 (copy ctor)
};
struct VecBig8c {
    Big8c* mpBegin; Big8c* mpEnd; Big8c* mpCapacity;
    char mAllocator_0c;                             // +0xc allocator object (address only)
    void* InsertValue(Big8c* position, const Big8c& value);
};

// ---- helpers ----------------------------------------------------------------------------
void CopyRangeRef(void* out, void* first, void* last, void* dst, char flag);  // @ 0x0042e860
void MoveV16(V16* p);                                // @ 0x00424f70
void MoveV32(V32* p);                                // @ 0x00424f10
void Vec16EraseHelper(V16* p);                       // @ 0x00424f70
Big8c* UninitializedCopyBig8c(Big8c* first, Big8c* last, Big8c* dest);   // @ 0x0047b310
void Vec3Scale(float* out, const float* scale, const float* vec);         // @ 0x0041de40

// ---- 3x3 float matrix -------------------------------------------------------------------
struct Mat33 { float r[3][3]; };

// @ 0x00476dd0
void* AllocOwner::ReallocRefs4(uint n, void* first, void* last)
{
    void* buf = n ? EASTL_Allocate((char*)this + 0xc, n << 2, 4, 0) : 0;
    CopyRangeRef(buf, first, last, buf, 0);
    return buf;
}

// @ 0x00476fe0
void IntInsert(int* mpBegin, int* mpEnd, int* mpCapacity, int* position, const int& value)
{
    if (mpEnd != mpCapacity) {
        int* pEnd = mpEnd;
        if (pEnd) *pEnd = *(pEnd - 1);
        int* p = pEnd;
        int* q = pEnd - 1;
        while (q != position) { *--p = *--q; }
        *position = value;
    }
}

// @ 0x00477200
I4* CopyDestruct4(I4* first, I4* last, I4* dest)
{
    I4* result = dest;
    for (I4* p = first; p != last; ++p, ++result) {
        if (result) *result = *p;
    }
    for (I4* q = first; q != last; ++q) {}
    return result;
}

// @ 0x004772a0
V16* Vec16::EraseV16(V16* first, V16* last)
{
    V16* newEnd = first;
    for (V16* q = last; q != mpEnd; ++q, ++newEnd)
        MoveV16(newEnd);                         // move-construct
    for (V16* r = newEnd; r < mpEnd; ++r)
        if (r->mpRef) r->mpRef->Release();
    mpEnd -= (last - first);
    return first;
}

// @ 0x00477380
V32* Vec32::EraseV32(V32* first, V32* last)
{
    V32* newEnd = first;
    for (V32* q = last; q != mpEnd; ++q, ++newEnd)
        newEnd->Assign(*q);                      // move the tail down one slot
    for (V32* r = newEnd; r < mpEnd; ++r) {
        Counted* ref = r->m1.mpRef;              // +0x1c
        if (ref)
            ref->mpVtbl->mpRelease(ref);
    }
    mpEnd -= (last - first);
    return first;
}

// @ 0x00477460  (the original leaves its last stored value in eax: new mpEnd, or `this` when it grew)
void* VecBig8c::InsertValue(Big8c* position, const Big8c& value)
{
    if (mpEnd != mpCapacity) {
        const Big8c* v = &value;
        if (v >= position && v < mpEnd)
            v = (const Big8c*)((const char*)v + sizeof(Big8c));
        if (mpEnd)
            mpEnd->CopyConstruct(*(mpEnd - 1));
        Big8c* dst = mpEnd;
        Big8c* src = mpEnd - 1;
        while (src != position) {
            --src;
            --dst;
            dst->Assign(*src);
        }
        position->Assign(*v);
        ++mpEnd;
        return mpEnd;
    }
    uint oldSize = (uint)(mpEnd - mpBegin);
    uint newSize = oldSize ? oldSize * 2 : 1;
    Big8c* pNew = (Big8c*)EASTL_Allocate(&mAllocator_0c, newSize * sizeof(Big8c), 4, 0);
    Big8c* p = UninitializedCopyBig8c(mpBegin, position, pNew);
    if (p)
        p->CopyConstruct(value);
    ++p;
    p = UninitializedCopyBig8c(position, mpEnd, p);
    Big8c* oldBegin = mpBegin;
    if (oldBegin && ((const AllocPrefix*)oldBegin - 1)->mDebugFill != 0)
        EASTL_allocator_deallocate(oldBegin);
    mpBegin = pNew;
    mpEnd = p;
    mpCapacity = pNew + newSize;
    return this;
}

// @ 0x00477700
Big8c* Big8c::Assign(const Big8c& src)
{
    m0.Assign(src.m0);
    m10 = src.m10;
    FwdTag tag;
    tag.mKind = 0xcc;                            // unused by DoAssign; matches the original's uninitialised tag
    if (&vec14 != &src.vec14) {
        vec14.Erase(vec14.mpBegin, vec14.mpEnd);
        vec14.Assign(src.vec14.mpBegin, src.vec14.mpEnd, tag);
    }
    if (&vec44 != &src.vec44) {
        vec44.EraseV16(vec44.mpBegin, vec44.mpEnd);
        vec44.Assign(src.vec44.mpBegin, src.vec44.mpEnd, tag);
    }
    return this;
}

// @ 0x004777e0
void Range7c::DestroyRange7c(char* first, char* last)
{
    for (; first < last; first += 0x7c)
        ((Elem7c*)first)->Destroy7c();
}

// @ 0x00477820
Mat33* ExtractMatrix33(Mat33* out, const Mat33* src, float scale)
{
    float row2[3];
    float row1[3];
    float row0[3];
    Vec3Scale(row2, &scale, src->r[2]);
    Vec3Scale(row1, &scale, src->r[1]);
    Vec3Scale(row0, &scale, src->r[0]);
    for (int i = 0; i < 3; ++i) {
        out->r[0][i] = row0[i];
        out->r[1][i] = row1[i];
        out->r[2][i] = row2[i];
    }
    return out;
}
