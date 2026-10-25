// EASTL vector<T> template instantiations (assign, reserve, push_back, resize, size) and a few
// small helpers around 0x00474bd0..0x00475bd0. Built /Od /Ob1 (frame pointer, all locals in memory).
// External helpers are declared with the calling convention seen at the call sites; the
// original callees are other functions in the binary (masked relocations).
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

template <int N> inline void ScratchSlots() { uint s[N]; }

struct DefaultRefCounted { void Release(); };
void operator_delete_array(void* p);                       // operator delete[] // 0x00f47380
void operator_delete_alloc(void* p, void* a, void* alloc, uint n);

struct Allocator;
void* Alloc(void* alloc, uint bytes, uint align, uint flags);   // @ 0x0042dee0 (thiscall on allocator)

// ---- vector<DefaultRefCounted*>: operator= --------------------------------------------------
struct RefVec {
    DefaultRefCounted** mpBegin;
    DefaultRefCounted** mpEnd;
    DefaultRefCounted** mpCapacity;
    RefVec& assign(const RefVec& x);
    DefaultRefCounted** DoAllocateCopy(uint n, DefaultRefCounted** first, DefaultRefCounted** last); // 0x476dd0
};
void CopyNode(DefaultRefCounted** p);                     // 0x4e4350 (ref-counted pointer copy)
void UninitCopy(void* out, DefaultRefCounted** first, DefaultRefCounted** last, DefaultRefCounted** dst, uchar t); // 0x42e860

// @ 0x00474bd0
RefVec& RefVec::assign(const RefVec& x)
{
    if (&x != this) {
        const uint n = (uint)(x.mpEnd - x.mpBegin);
        if ((uint)(mpCapacity - mpBegin) < n) {
            DefaultRefCounted** pNew = DoAllocateCopy(n, x.mpBegin, x.mpEnd);
            for (DefaultRefCounted** p = mpBegin; p < mpEnd; ++p)
                if (*p) (*p)->Release();
            if (mpBegin) operator_delete_array(mpBegin);
            mpBegin = pNew;
            mpCapacity = mpBegin + n;
        } else if ((uint)(mpEnd - mpBegin) < n) {
            DefaultRefCounted** dst = mpBegin;
            DefaultRefCounted** mid = x.mpBegin + (mpEnd - mpBegin);
            for (DefaultRefCounted** s = x.mpBegin; s != mid; ++s) { CopyNode(s); ++dst; }
            char tmp[4];
            UninitCopy(tmp, mid, x.mpEnd, mpEnd, 0);
        } else {
            DefaultRefCounted** dst = mpBegin;
            for (DefaultRefCounted** s = x.mpBegin; s != x.mpEnd; ++s) { CopyNode(s); ++dst; }
            for (DefaultRefCounted** p = dst; p < mpEnd; ++p)
                if (*p) (*p)->Release();
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// ---- vector<T(0x48)> and vector<T(0xd8)> destructors ---------------------------------------
struct Vec3Ptr { uint mpBegin, mpEnd; };
struct ElemRange {
    void Destroy();   // 0x4c0b80 (thiscall, range member in ecx)
};

struct Vec48 {
    char* mpBegin; char* mpEnd;
    ~Vec48();
    void Free();   // 0x476e60
};
struct VecD8 {
    char* mpBegin; char* mpEnd;
    ~VecD8();
    void Free();   // 0x476f20
};

// @ 0x00474f30
Vec48::~Vec48()
{
    char* end = mpEnd;
    for (char* e = mpBegin; e < end; e += 0x48) {
        for (char* q = *(char**)(e + 0xc); q < *(char**)(e + 0x10); q += 4) {}
        ((ElemRange*)(e + 0xc))->Destroy();
    }
    Free();
}

// @ 0x00474fb0
VecD8::~VecD8()
{
    char* end = mpEnd;
    for (char* e = mpBegin; e < end; e += 0xd8) {
        for (char* q = *(char**)(e + 0x10); q < *(char**)(e + 0x14); q += 4) {}
        ((ElemRange*)(e + 0x10))->Destroy();
    }
    Free();
}

// ---- fixed_vector<int> reserve / push_back --------------------------------------------------
struct FixedVecInt {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    char mAllocator[4];       // +0x0c
    int* mpFixedBuffer;       // +0x10
    void reserve(uint n);
    void push_back(const int& v);
    void DoInsertValue(int* pos, const int& v);        // 0x476fe0
};
void CopyInts(int* first, int* last, int* dst);        // 0x477200

// @ 0x00475040
void FixedVecInt::reserve(uint n)
{
    if ((uint)(mpCapacity - mpBegin) < n) {
        int* pNew = n ? (int*)Alloc(mAllocator, n << 2, 2, 0) : 0;
        CopyInts(mpBegin, mpEnd, pNew);
        if (mpBegin && mpBegin != mpFixedBuffer)
            operator_delete_alloc(mpBegin, pNew, this, (uint)(mpCapacity - mpBegin));
        int* old = mpBegin;
        mpBegin = pNew;
        mpEnd = pNew + (mpEnd - old);
        mpCapacity = mpBegin + n;
    }
}

// @ 0x00475130
void FixedVecInt::push_back(const int& v)
{
    if (mpEnd < mpCapacity) {
        int* p = mpEnd;
        mpEnd = p + 1;
        if (p) *p = v;
    } else {
        DoInsertValue(mpEnd, v);
    }
}

// ---- vector<T(0x10)>::resize ----------------------------------------------------------------
// ---- shared 0x10-byte stream descriptor and its 0x20-byte vector element -------------------
struct IRefObj {                       // ref-counted object: slot 0 = AddRef, slot 1 = Release
    virtual int AddRef();
    virtual int Release();
};
struct IndexVec;                       // 4-byte-element vector (StreamIndex pairs), +0x98 in the caller

struct StreamDesc {                    // 0x10 bytes (the "Desc" of s0046e450)
    int mCount;                        // +0x0
    void* mpData;                      // +0x4
    unsigned short mStride;            // +0x8
    unsigned short mStride2;           // +0xa
    IRefObj* mpOwner;                  // +0xc
    StreamDesc() { init0(); }
    StreamDesc* init0();                                            // 0x46f1f0
    StreamDesc* init(int count, void* data, IRefObj* owner, int);   // 0x46f140
    StreamDesc* initFromVec(const IndexVec* v, IRefObj* owner, int); // 0x4755a0
};

struct Vec16 {
    StreamDesc* mpBegin; StreamDesc* mpEnd; StreamDesc* mpCapacity;
    void resize(uint n);
    void Fill(StreamDesc* pos, uint count, const StreamDesc* v);   // 0x47aa40
    void Erase(StreamDesc* first, StreamDesc* last);               // 0x4772a0
};

// @ 0x004751a0
void Vec16::resize(uint n)
{
    if (n > (uint)(mpEnd - mpBegin)) {
        StreamDesc tmp;
        ScratchSlots<15>();
        Fill(mpEnd, n - (uint)(mpEnd - mpBegin), &tmp);
        if (tmp.mpOwner) tmp.mpOwner->Release();
    } else {
        Erase(mpBegin + n, mpEnd);
    }
}

// ---- vector<T(0x20)>::resize / reserve ------------------------------------------------------
struct StreamElem {                    // 0x20 bytes
    int mUsage;                        // +0x0
    int mIndex;                        // +0x4
    int mType;                         // +0x8
    int mSlot;                         // +0xc
    StreamDesc mDesc;                  // +0x10
    StreamElem() : mUsage(0), mIndex(0), mType(0), mSlot(14) {}
};

struct Vec32 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    char mAllocator[4];
    void resize(uint n);
    void reserve(uint n);
    int size() const;
    void Fill32(char* pos, uint count, const StreamElem* v);       // 0x47ae60
    void Erase32(char* first, char* last);                         // 0x477380
};
void Move32(char* first, char* last, char* dst);       // 0x42a730

// @ 0x00475240
int Vec32::size() const { return (mpEnd - mpBegin) >> 5; }

// @ 0x00475260
void Vec32::resize(uint n)
{
    if (n > (uint)((mpEnd - mpBegin) >> 5)) {
        StreamElem tmp;
        ScratchSlots<14>();
        Fill32(mpEnd, n - (uint)((mpEnd - mpBegin) >> 5), &tmp);
        if (tmp.mDesc.mpOwner) tmp.mDesc.mpOwner->Release();
    } else {
        Erase32(mpBegin + n * 0x20, mpEnd);
    }
}

// @ 0x00475320
void Vec32::reserve(uint n)
{
    if ((uint)((mpCapacity - mpBegin) >> 5) < n) {
        char* pNew = n ? (char*)Alloc(mAllocator, n << 5, 4, 0) : 0;
        Move32(mpBegin, mpEnd, pNew);
        if (mpBegin && *(int*)(mpBegin - 4) != 0)
            operator_delete_alloc(mpBegin, pNew, this, (uint)((mpCapacity - mpBegin) >> 5));
        char* old = mpBegin;
        mpBegin = pNew;
        mpEnd = pNew + ((mpEnd - old) >> 5) * 0x20;
        mpCapacity = mpBegin + n * 0x20;
    }
}

// ---- vector<T(0x8c)> -----------------------------------------------------------------------
// The 0x8c-byte element type carries three __thiscall operations (construct in place,
// post-insert fixup, copy from an existing element); modelling them as members puts the
// element in ecx exactly like the original call sites.
struct Elem8c {
    char mData[0x8c];
    void* Construct();                 // 0x46f1b0
    void Fixup();                      // 0x41f940
    void* CopyFrom(void* src);         // 0x42cba0
};
struct Vec8c {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    int size();
    void push_back_default();
    void push_back(void* v);
    void DoInsert(char* pos, void* v);     // 0x477460 (thiscall on the vector)
};

// @ 0x00475410
int Vec8c::size() { return (mpEnd - mpBegin) / 0x8c; }

// @ 0x00475430
void Vec8c::push_back_default()
{
    Elem8c tmp;
    if (mpEnd < mpCapacity) {
        Elem8c* p = (Elem8c*)mpEnd;
        mpEnd += 0x8c;
        void* r = p ? p->Construct() : 0;
    } else {
        DoInsert(mpEnd, tmp.Construct());
        tmp.Fixup();
    }
}

// @ 0x004754e0
void Vec8c::push_back(void* v)
{
    if (mpEnd < mpCapacity) {
        Elem8c* p = (Elem8c*)mpEnd;
        mpEnd += 0x8c;
        void* r = p ? p->CopyFrom(v) : 0;
    } else {
        DoInsert(mpEnd, v);
    }
}

// @ 0x00475550
void Uninit4(void* a, void* b, float c);               // 0x477820 (cdecl, 3 args; 3rd is a float)
void* Wrap4(void* out, void* in, float* pv)
{
    Uninit4(out, in, *pv);
    return out;
}

struct StreamIndex { short mStream; short mSub; };     // 4 bytes
struct IndexVec {                                      // 4-byte-element vector
    StreamIndex* mpBegin; StreamIndex* mpEnd; StreamIndex* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    StreamIndex* begin() const { return mpBegin; }
};

// @ 0x004755a0
StreamDesc* StreamDesc::initFromVec(const IndexVec* v, IRefObj* owner, int)
{
    mCount = v->size();
    StreamIndex* p = v->begin();
    mpData = p;
    mStride = 4;
    mStride2 = 4;
    IRefObj*& r = mpOwner;
    r = owner;
    if (r) r->AddRef();
    return this;
}

// ---- vector<8-byte T>::push_back ------------------------------------------------------------
struct Pair8 { uint a, b; };
struct Vec8 {
    uint* mpBegin; uint* mpEnd; uint* mpCapacity;
    void push_backA(uint* v);
    void push_backB(uint* v);
    void DoInsertA(uint* pos, uint* v);    // 0x478390 (thiscall on the vector)
    void DoInsertB(uint* pos, uint* v);    // 0x4786e0 (thiscall on the vector)
};

// @ 0x00475670
void Vec8::push_backA(uint* v)
{
    uint* p;
    uint* snap;
    if (mpEnd < mpCapacity) {
        snap = mpEnd;
        mpEnd += 2;
        p = snap;
        p ? (*(float*)p = *(float*)v,
             *(float*)(p + 1) = *(float*)(v + 1), p) : 0;
    } else {
        DoInsertA(mpEnd, v);
    }
}

// @ 0x00475800
void Vec8::push_backB(uint* v)
{
    uint* p;
    uint* snap;
    if (mpEnd < mpCapacity) {
        snap = mpEnd;
        mpEnd += 2;
        p = snap;
        p ? (*(unsigned long long*)p = *(unsigned long long*)v, p) : 0;
    } else {
        DoInsertB(mpEnd, v);
    }
}

// ---- fixed vector<bool-ish 8 byte> reserve --------------------------------------------------
struct VecBits {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    char mAllocator[4];
    void reserve(uint n);
};
void* DoInsertValue(void* dst, void* src, int bytes);  // vector<bool,fixed_vector_allocator<1,16,1,0,1>>::DoInsertValue // 0x011e0744

// @ 0x004756f0
void VecBits::reserve(uint n)
{
    if ((uint)((mpCapacity - mpBegin) >> 3) < n) {
        void* pNew = n ? Alloc(mAllocator, n << 3, 8, 0) : 0;
        DoInsertValue(pNew, mpBegin, (int)(mpEnd - mpBegin));
        if (mpBegin && *(int*)(mpBegin - 4) != 0)
            operator_delete_array(mpBegin); // 0x00f47380
        char* old = mpBegin;
        mpBegin = (char*)pNew;
        mpEnd = (char*)pNew + ((mpEnd - old) >> 3) * 8;
        mpCapacity = mpBegin + n * 8;
    }
}

// @ 0x00475880
struct Struct29c {
    char pad[0x158];
    uint a[64];          // 0x158 (32 pairs)
    uint b[16];          // 0x258 (8 pairs)
    uint c;              // 0x298
    Struct29c* Clear();
};
Struct29c* Struct29c::Clear()
{
    int i = 0x20;
    uint* p = a;
    while (--i, -1 < i) { p[0] = 0; p[1] = 0; p += 2; }
    int j = 8;
    uint* q = b;
    while (--j, -1 < j) { q[0] = 0; q[1] = 0; q += 2; }
    c = 0;
    return this;
}

// ---- eastl::string pieces -------------------------------------------------------------------
extern ushort gEmptyString;                            // 0x01667bac (shared empty buffer)
int Vsnprintf8(char* dst, uint cap, const char* fmt, void* args);
void* operator_new_eastl(uint size, const char* name, int flags, int dbg, const char* file, int line);

namespace eastl {
struct basic_string {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    basic_string& append_sprintf_va_list(const char* fmt, void* args);
    void RangeInitialize(uint n);
    void set_capacity(uint n);                         // 0x478930
};

// @ 0x00475930
basic_string& basic_string::append_sprintf_va_list(const char* fmt, void* args)
{
    const int nPrevLength = (int)(mpEnd - mpBegin);
    int n;
    if ((ushort*)mpBegin == &gEmptyString)
        n = Vsnprintf8(mpEnd, 0, fmt, args);
    else
        n = Vsnprintf8(mpEnd, (uint)(mpCapacity - mpEnd), fmt, args);

    if (n < (int)(mpCapacity - mpEnd)) {
        if (n < 0) {
            uint a = (uint)(mpEnd - mpBegin) * 2;
            uint b = 7;
            uint nCap = (a < 8) ? b : a;     // max(2*size, 8)-1 style growth
            for (; n < 0 && nCap < 1000000; nCap <<= 1) {
                set_capacity(nCap);
                n = Vsnprintf8(mpBegin + nPrevLength, (nCap + 1) - nPrevLength, fmt, args);
            }
        }
    } else {
        set_capacity(nPrevLength + n);
        n = Vsnprintf8(mpBegin + nPrevLength, n + 1, fmt, args);
    }
    if (-1 < n)
        mpEnd = mpBegin + nPrevLength + n;
    return *this;
}

// @ 0x00475ab0
void basic_string::RangeInitialize(uint n)
{
    if (n < 2) {
        mpBegin = (char*)&gEmptyString;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    } else {
        mpBegin = (char*)operator_new_eastl(n, "Editor", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        mpEnd = mpBegin;
        mpCapacity = mpBegin + n;
    }
}
}

// @ 0x00475bd0
int InsertBits(void* first, int last, void* vec)
{
    void* r = DoInsertValue(vec, first, last - (int)first);
    return (int)r + (last - (int)first);
}
// --- equivalence checker address annotations
    void DoInsertValue(...); // 0x011e0744
    void operator_delete_array(...); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct DefaultRefCounted {
    void Release(); // 0x00453540
};
}
