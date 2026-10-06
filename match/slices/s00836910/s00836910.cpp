// Slice s00836910 (w2g7 #39), 32-bit MSVC 2008 SP1.
// anonymous-namespace cDataURI (data: URI parser) + fixed-buffer string helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

void* __cdecl operator_new6(uint32_t, const void*, int, int, const char*, int);
void  __cdecl operator_delete__(void*);
void  __cdecl VectorBool_DoInsertValue(void*, const void*, uint32_t);
void  __cdecl memmove_1(void*, const void*, uint32_t);   // 0x13cc480 msvcr90!memmove
void  __cdecl WideFixedBuf_append(void*, void*, void*);  // 0x42f9d0
void  __cdecl BinaryAssign(void*, void*, uint32_t);      // 0x672750
void  __cdecl CodecReset(void*, int);                    // 0x6726f0
void  __cdecl CodecReset2(void*, int);                   // 0x8366e0
extern char g_eastlTag[];

// ---------------------------------------------------------------------------
// generic fixed-buffer string (3 pointers + allocator + SSO buffer ptr + data)
// ---------------------------------------------------------------------------
struct RawFixed {
    int a, b, c, d, e;   // +0 begin, +4 end, +8 capacity, +0xc alloc, +0x10 buffer
    void Init(const RawFixed& other);                 // 0x836850
    void Assign(const void* first, const void* last); // 0x836910
    void AppendRange(const void* first, const void* last); // 0x45f430
    void AssignStr(const wchar_t* first, const wchar_t* last); // 0x672750
    RawFixed* AssignCStr(const wchar_t* s);           // 0x8369e0
    RawFixed* SubstrInto(RawFixed* dst, uint32_t pos, uint32_t len); // 0x836a30
    void Swap(RawFixed& other);                       // 0x836a90
    void Reserve(uint32_t n);                         // 0x837020
    void Reserve2(uint32_t n);                        // 0x837230
    void AppendN(uint32_t count, uint8_t c);          // 0x837270
    void Resize(uint32_t n);                          // 0x837310
};

// ---------------------------------------------------------------------------
// EA::WideFixedBuf<N> (SSO fixed buffer wide string)
// ---------------------------------------------------------------------------
template <int N>
struct FixedString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    wchar_t* mpBuffer;
    wchar_t  mData[N];

    FixedString() {
        wchar_t* buf = mData;
        mpBuffer = buf;
        mpEnd = buf;
        mpBegin = buf;
        mpCapacity = buf + N;
        *buf = 0;
    }
    ~FixedString() {
        if ((((int)((char*)mpCapacity - (char*)mpBegin) & -2) > 2) && mpBegin &&
            mpBegin != mpBuffer) {
            operator_delete__(mpBegin);
        }
    }
};

// ---------------------------------------------------------------------------
// cDataURI
// ---------------------------------------------------------------------------
struct cDataURI {
    int mEncoding;              // +0
    FixedString<32> mScheme;    // +4
    FixedString<1024> mValue;   // +0x58
    bool mbBase64;              // +0x86c

    cDataURI(int p);
    ~cDataURI();
    __declspec(noinline) void init(int p);
};

// @ 0x00836990
cDataURI::~cDataURI() {}

// @ 0x008371e0
cDataURI::cDataURI(int p) {
    init(p);
}

// @ 0x00836910  FixedString::Assign-from-range (DoInsertValue tail-shift)
void RawFixed::Assign(const void* first, const void* last) {
    uint8_t* begin = (uint8_t*)a;
    uint8_t* end = (uint8_t*)b;
    uint32_t size = (uint32_t)((const uint8_t*)last - (const uint8_t*)first);
    if ((uint32_t)(end - begin) < size) {
        VectorBool_DoInsertValue(begin, first, (uint32_t)(end - begin));
        AppendRange((const uint8_t*)first + (b - a), last);
    } else {
        VectorBool_DoInsertValue(begin, first, size);
        uint8_t* newEnd = begin + size;
        if (newEnd != end) {
            memmove_1(newEnd, end, 1);
            b += (int)(newEnd - end);
        }
    }
}

// @ 0x00836850  copy ctor helper
void RawFixed::Init(const RawFixed& other) {
    a = 0; b = 0; c = 0;
    d = other.d;
    uint32_t size = (uint32_t)(other.b - other.a);
    Reserve(size + 1);
    uint8_t* dst = (uint8_t*)a;
    VectorBool_DoInsertValue(dst, (void*)other.a, size);
    b = (int)(dst + (other.b - other.a));
    *(uint8_t*)b = 0;
}

// @ 0x00836a90
void RawFixed::Swap(RawFixed& other) {
    if (this + 3 == &other + 3) {
        int t;
        t = a; a = other.a; other.a = t;
        t = b; b = other.b; other.b = t;
        t = c; c = other.c; other.c = t;
        return;
    }
    RawFixed tmp;
    tmp.Init(*this);
    if (&other != this) this->Assign((void*)other.a, (void*)other.b);
    if (&tmp != &other) other.Assign((void*)tmp.a, (void*)tmp.b);
    if (((tmp.c - tmp.a) > 1) && tmp.a && tmp.a != tmp.e) operator_delete__((void*)tmp.a);
}

// @ 0x008369e0
static unsigned int CharStrlen(const wchar_t* p) {
    const wchar_t* e = p;
    while (*e) ++e;
    return (unsigned int)(e - p);
}

RawFixed* RawFixed::AssignCStr(const wchar_t* s) {
    wchar_t* begin = (wchar_t*)a;
    if (begin == s) return this;
    if (begin != (wchar_t*)b) {
        *begin = 0;
        b = a;
    }
    AssignStr(s, s + CharStrlen(s));
    return this;
}

// @ 0x00836a30  substring into a 256 fixed string
RawFixed* RawFixed::SubstrInto(RawFixed* dst, uint32_t pos, uint32_t len) {
    wchar_t* begin = (wchar_t*)a;
    uint32_t size = (uint32_t)((wchar_t*)b - begin);
    uint32_t avail = size - pos;
    uint32_t n = (avail < len) ? avail : len;
    wchar_t* d = (wchar_t*)dst;
    dst->e = (int)(d + 10);
    dst->c = (int)(d + 0x100);
    dst->b = (int)(d + 10);
    dst->a = (int)(d + 10);
    *d = 0;
    dst->AppendRange(begin + pos, begin + pos + n);
    return dst;
}

// @ 0x00837020
void RawFixed::Reserve(uint32_t n) {
    if (n != 0xffffffffu && (uint32_t)(b - a) < n) {
        uint8_t* m = (uint8_t*)operator_new6(n, g_eastlTag, 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        uint32_t size = (uint32_t)(b - a);
        VectorBool_DoInsertValue(m, (void*)a, size);
        m[size] = 0;
        int old = a;
        if ((((c - old) > 1) && old) && old != e) operator_delete__((void*)old);
        a = (int)m;
        b = (int)(m + size);
        c = (int)(m + n);
        return;
    }
    if (n < (uint32_t)(b - a)) {
        Resize(n);
    }
    RawFixed tmp;
    tmp.Init(*this);
    Swap(tmp);
    if ((((tmp.c - tmp.a) > 1) && tmp.a) && tmp.a != tmp.e) operator_delete__((void*)tmp.a);
}

// @ 0x00837230
template <typename T> static const T& max_alt(const T& a, const T& b) { return a < b ? b : a; }

void RawFixed::Reserve2(uint32_t n) {
    uint32_t size = (uint32_t)(b - a);
    uint32_t need = max_alt(n, size) + 1;
    if (need > (uint32_t)(c - a)) {
        Reserve(need);
    }
}

// @ 0x00837270
void RawFixed::AppendN(uint32_t count, uint8_t ch) {
    uint32_t size = (uint32_t)(b - a);
    uint32_t cap = (uint32_t)(c - a);
    uint32_t need = size + count;
    if (need > cap - 1) {
        uint32_t ncap = cap - 1;
        ncap = (ncap < 9) ? 8 : ncap * 2;
        uint32_t chosen = (need < ncap) ? need : ncap;
        uint32_t cap2 = (size < chosen) ? size : chosen;
        if (cap < cap2 + 1) {
            Reserve(cap2 + 1);
        }
    }
    if (count != 0) {
        uint8_t* dst = (uint8_t*)b;
        for (uint32_t i = 0; i + 1 < count; ++i) dst[1 + i] = ch;
        *dst = ch;
        b = (int)(dst + count);
        *(uint8_t*)b = 0;
    }
}

// @ 0x00837310
void RawFixed::Resize(uint32_t n) {
    uint8_t* src = (uint8_t*)b;
    uint32_t size = (uint32_t)(src - (uint8_t*)a);
    if (n < size) {
        uint8_t* dst = (uint8_t*)a + n;
        if (dst != src) {
            memmove_1(dst, src, 1);
            b = (int)(dst + (b - (int)src));
        }
    } else if (size < n) {
        AppendN(n - size, 0);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00836d50  cDataURI::init (approximation)
// ---------------------------------------------------------------------------
void cDataURI::init(int p) {
    mbBase64 = false;
    CodecReset(&mValue, 0);
    CodecReset2(&mScheme, 0);
    mEncoding = 0;
    (void)p;
}

// ---------------------------------------------------------------------------
// @ 0x00836bd0 / @ 0x00837360  (partial)
// ---------------------------------------------------------------------------
int FUN_00836bd0(int p1, int p2) { (void)p1; (void)p2; return 0; }
int* FUN_00837360(int* a, void* b, uint32_t c, void* d, int e, char f) {
    (void)b; (void)c; (void)d; (void)e; (void)f;
    a[0] = 0; a[1] = 0; a[2] = 0;
    return a;
}