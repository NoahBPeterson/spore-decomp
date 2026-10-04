// EASTL vector<T> template instantiations (assign, reserve, push_back, resize, size) and a few
// small helpers around 0x00474bd0..0x00475bd0. Built /Od /Ob1 (frame pointer, all locals in memory).
// External helpers are declared with the calling convention seen at the call sites; the
// original callees are other functions in the binary (masked relocations).
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

struct DefaultRefCounted { void Release(); };
void operator_delete_array(void* p);                       // operator delete[]
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
void DestroyElem();                                   // 0x4c0b80 (fastcall, element in ecx)
void FreeVec48(void* v);                              // 0x476e60
void FreeVecD8(void* v);                              // 0x476f20

struct Vec48 { char* mpBegin; char* mpEnd; ~Vec48(); };
struct VecD8 { char* mpBegin; char* mpEnd; ~VecD8(); };

// @ 0x00474f30
void Vec48_dtor(Vec48* v)
{
    char* end = v->mpEnd;
    for (char* e = v->mpBegin; e < end; e += 0x48) {
        for (char* q = *(char**)(e + 0xc); q < *(char**)(e + 0x10); q += 4) {}
        DestroyElem();
    }
    FreeVec48(v);
}

// @ 0x00474fb0
void VecD8_dtor(VecD8* v)
{
    char* end = v->mpEnd;
    for (char* e = v->mpBegin; e < end; e += 0xd8) {
        for (char* q = *(char**)(e + 0x10); q < *(char**)(e + 0x14); q += 4) {}
        DestroyElem();
    }
    FreeVecD8(v);
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
struct Vec16 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void resize(uint n);
};
struct Releasable { virtual void v0(); virtual void Release(); };
void Init16Tmp();                                      // 0x46f1f0 (ctor of fill-temp)
void Fill16(char* pos, uint count, void* tmp);         // 0x47aa40
void Erase16(char* first, char* last);                 // 0x4772a0

// @ 0x004751a0
void Vec16::resize(uint n)
{
    char tmp[12];
    Releasable* ref;
    if ((uint)((mpEnd - mpBegin) >> 4) < n) {
        Init16Tmp();
        Fill16(mpEnd, n - (uint)((mpEnd - mpBegin) >> 4), tmp);
        if (ref) ref->Release();
    } else {
        Erase16(mpBegin + n * 0x10, mpEnd);
    }
}

// @ 0x00475240
int Vec32_size(Vec48* v) { return (v->mpEnd - v->mpBegin) >> 5; }

// ---- vector<T(0x20)>::resize / reserve ------------------------------------------------------
struct Vec32 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    char mAllocator[4];
    void resize(uint n);
    void reserve(uint n);
};
void Init32Tmp();                                      // 0x46f1f0
void Fill32(char* pos, uint count, void* tmp);         // 0x47ae60
void Erase32(char* first, char* last);                 // 0x477380
void Move32(char* first, char* last, char* dst);       // 0x42a730

// @ 0x00475260
void Vec32::resize(uint n)
{
    uint tmp[4];
    Releasable* ref;
    if ((uint)((mpEnd - mpBegin) >> 5) < n) {
        tmp[0] = 0; tmp[1] = 0; tmp[2] = 0; tmp[3] = 0xe;
        Init32Tmp();
        Fill32(mpEnd, n - (uint)((mpEnd - mpBegin) >> 5), tmp);
        if (ref) ref->Release();
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
struct Vec8c {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    int size();
    void push_back_default();
    void push_back(void* v);
};
void* Construct8c();                                   // 0x46f1b0
void DoInsert8c(char* pos, void* v);                   // 0x477460
void Fixup8c();                                        // 0x41f940
void Copy8c(void* src);                                // 0x42cba0

// @ 0x00475410
int Vec8c::size() { return (mpEnd - mpBegin) / 0x8c; }

// @ 0x00475430
void Vec8c::push_back_default()
{
    if (mpEnd < mpCapacity) {
        char* p = mpEnd;
        mpEnd += 0x8c;
        if (p) Construct8c();
    } else {
        void* tmp = Construct8c();
        DoInsert8c(mpEnd, tmp);
        Fixup8c();
    }
}

// @ 0x004754e0
void Vec8c::push_back(void* v)
{
    if (mpEnd < mpCapacity) {
        char* p = mpEnd;
        mpEnd += 0x8c;
        if (p) Copy8c(v);
    } else {
        DoInsert8c(mpEnd, v);
    }
}

// @ 0x00475550
void Uninit4(void* a, void* b, uint* c);               // 0x477820 stdcall-ish helper
void* Wrap4(void* out, void* in, uint* pv)
{
    Uninit4(out, in, (uint*)*pv);
    return out;
}

// @ 0x004755a0
struct RangeRef {
    int mCount;
    uint mpBegin;
    ushort mA, mB;
    int* mpObj;
    RangeRef* Init(Vec48* range, int* obj);
};
RangeRef* RangeRef::Init(Vec48* range, int* obj)
{
    mCount = (int)(range->mpEnd - range->mpBegin) >> 2;
    mpBegin = (uint)range->mpBegin;
    mA = 4;
    mB = 4;
    mpObj = obj;
    if (mpObj) (*(void (**)())(*(int**)mpObj)[0])();
    return this;
}

// ---- vector<8-byte T>::push_back ------------------------------------------------------------
struct Vec8 {
    uint* mpBegin; uint* mpEnd; uint* mpCapacity;
    void push_backA(uint* v);
    void push_backB(uint* v);
};
void DoInsert8A(uint* pos, uint* v);                   // 0x478390
void DoInsert8B(uint* pos, uint* v);                   // 0x4786e0

// @ 0x00475670
void Vec8::push_backA(uint* v)
{
    if (mpEnd < mpCapacity) {
        uint* p = mpEnd;
        mpEnd += 2;
        if (p) { p[0] = v[0]; p[1] = v[1]; }
    } else {
        DoInsert8A(mpEnd, v);
    }
}

// @ 0x00475800
void Vec8::push_backB(uint* v)
{
    if (mpEnd < mpCapacity) {
        uint* p = mpEnd;
        mpEnd += 2;
        if (p) { p[0] = v[0]; p[1] = v[1]; }
    } else {
        DoInsert8B(mpEnd, v);
    }
}

// ---- fixed vector<bool-ish 8 byte> reserve --------------------------------------------------
struct VecBits {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    char mAllocator[4];
    void reserve(uint n);
};
void* DoInsertValue(void* dst, void* src, int bytes);  // vector<bool,fixed_vector_allocator<1,16,1,0,1>>::DoInsertValue

// @ 0x004756f0
void VecBits::reserve(uint n)
{
    if ((uint)((mpCapacity - mpBegin) >> 3) < n) {
        void* pNew = n ? Alloc(mAllocator, n << 3, 8, 0) : 0;
        DoInsertValue(pNew, mpBegin, (int)(mpEnd - mpBegin));
        if (mpBegin && *(int*)(mpBegin - 4) != 0)
            operator_delete_array(mpBegin);
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
