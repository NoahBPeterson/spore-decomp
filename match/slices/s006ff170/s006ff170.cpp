// Slice s006ff170: vertex-shader fragment-record serialization and plane/clip test helpers.
// Region 0x6ff170-0x6ffdf8. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-.
#include "types.h"
#include <string.h>

// ---- external callees -------------------------------------------------------------------
extern "C" void FUN_0047d240();                               // 0x0047d240 thiscall(void*, int) string set-capacity
extern "C" void FUN_006fc540();                               // 0x006fc540 thiscall(void*, unsigned) vector set-capacity
extern "C" void FUN_006ff100();                               // 0x006ff100 cVertexFragmentInfo::operator=
extern "C" void FUN_006fe830();                               // 0x006fe830 cVertexFragmentInfo::~cVertexFragmentInfo
void __cdecl FUN_00777720(void* p, unsigned n, void* out);
unsigned __cdecl FUN_00777740(void* p);
void __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380

// EA::IO stream primitives (names from symbols/slices/s006fc540.txt)
int __cdecl FUN_0093a9a0(void* io, const void* p, int n);        // 0x0093a9a0 write block
int __cdecl FUN_0093aa70(void* io, const void* p, int n, int f); // 0x0093aa70 write uint32
int __cdecl FUN_0093a9d0(void* io, const void* p, int n, int f); // 0x0093a9d0 write uint16
int __cdecl FUN_0093a6c0(void* io, void* p, int n);              // 0x0093a6c0 read block
int __cdecl FUN_0093a780(void* io, void* p, int n, int f);       // 0x0093a780 read uint32
int __cdecl FUN_0093a700(void* io, void* p, int n, int f);       // 0x0093a700 read uint16

// ---- globals ----------------------------------------------------------------------------
extern unsigned char g_1628c38;    // 0x1628c38 clip-disable flag
extern int  g_planeIndices[6];     // 0x1534e4c
extern char g_vertexFragTable;     // 0x1624710, 256 SP::cVertexFragmentInfo records of 0x44

// ---- vertex-shader fragment table (vector at 0x1628c20, 0x130-byte records) --------------
extern char*      g_vs_begin;      // 0x1628c20
extern char*      g_vs_end;        // 0x1628c24
extern unsigned   g_15345b0;       // 0x15345b0 record-count high-water mark
extern void*      g_16f89d0;       // 0x16f89d0 d3d9 device

void __cdecl FUN_006ff060(void* vec, unsigned n);   // 0x006ff060 Vec130::Resize
void __cdecl FUN_006fc480(void* vec, unsigned n);   // 0x006fc480 vector<cFragmentDecl>::resize
void __cdecl FUN_004c10e0();                        // 0x004c10e0 vector<u8>::DoInsertValues
void* __cdecl FUN_00f473a0(unsigned n, const char* name, int flags, unsigned dbg,
                           const char* file, int line);   // 0x00f473a0 EA::Allocate
void __cdecl FUN_00f47380(void* p);                       // 0x00f47380 operator delete[]

// 0x130-byte vertex-fragment record; the +0x2c and +0xac arrays each hold 0x20 entries.
struct FragElem {                   // 0x1c
    char*    mpBegin;               // +0x00
    char*    mpEnd;                 // +0x04
    char*    mpCap;                 // +0x08
    unsigned mField0C;              // +0x0c
    unsigned short mField10;        // +0x10
    unsigned short mField12;        // +0x12
    unsigned short mField14;        // +0x14
    unsigned short mField16;        // +0x16
    unsigned mField18;              // +0x18
};
struct VsRecord {                   // 0x130
    unsigned char mBlob[0x20];      // +0x00 opaque 0x20-byte block
    void*         mpShader;         // +0x20 vertex-shader object (0x777720 / 0x777740)
    unsigned      mField24;         // +0x24
    int           mCount;           // +0x28
    FragElem*     mpElems[0x20];    // +0x2c
    unsigned      mFieldAC[0x20];   // +0xac
    int           mField12C;        // +0x12c
};

// EA::Allocator::StackAllocator arena that owns the per-record FragElem arrays.
struct StackAllocator {
    unsigned  mnDefaultBlockSize;   // +0x00
    void*     mpCurrentBlock;       // +0x04
    char*     mpCurrentBlockEnd;    // +0x08
    char*     mpCurrentObjectBegin; // +0x0c
    char*     mpCurrentObjectEnd;   // +0x10
    bool AllocateNewBlock(unsigned size);   // 0x00928ba0
    // Bump-allocate `n` bytes out of the current block, growing the chain if it does not fit.
    __forceinline void* Allocate(unsigned n) {
        n = (n + 7) & ~7u;
        if (mpCurrentBlockEnd - mpCurrentObjectBegin - (int)n < 0) {
            if (!AllocateNewBlock(n)) return 0;
        }
        char* p = mpCurrentObjectBegin;
        mpCurrentObjectBegin = p + n;
        mpCurrentObjectEnd = p + n;
        return p;
    }
};
extern StackAllocator g_fragAllocator;      // 0x1628b98

// Local growable byte buffer (eastl::vector<unsigned char>) used as the shader-blob scratch.
struct VecU8 {
    unsigned char* mpBegin;         // +0x00
    unsigned char* mpEnd;           // +0x04
    unsigned char* mpCap;           // +0x08
    unsigned char* erase(unsigned char* first, unsigned char* last) {
        memcpy(first, last, (unsigned)(mpEnd - last));
        mpEnd -= last - first;
        return first;
    }
    void resize(unsigned n) {
        unsigned size = (unsigned)(mpEnd - mpBegin);
        if (n <= size) {
            erase(mpBegin + n, mpEnd);
        } else {
            unsigned char v = 0;
            ((void(__thiscall*)(void*, unsigned char*, unsigned, const void*))FUN_004c10e0)
                (this, mpEnd, (unsigned)(mpBegin - mpEnd) + n, &v);
        }
    }
    ~VecU8() {
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            FUN_00f47380(mpBegin);
    }
};

// EA::IO writer overloads: by-value parameters give the 4-byte stack temporaries the
// original stream calls take by address.
struct IO {
    int Put(unsigned short v) { return FUN_0093a9d0(this, &v, 1, 0); }
    int Put(unsigned v)       { return FUN_0093aa70(this, &v, 1, 0); }
    int Put(const unsigned* p, int n) { return FUN_0093aa70(this, p, n, 0); }
    int Write(const void* p, int n)   { return FUN_0093a9a0(this, p, n); }
};

// ---- cVertexFragmentInfo record (0x44 bytes), as read back by 0x006ff750 ---------------
struct EStr {                       // 0x10 eastl::basic_string<char>
    char* mpBegin;                  // +0x00
    char* mpEnd;                    // +0x04
    char* mpCap;                    // +0x08
    int   mField0C;                 // +0x0c
    void append(unsigned n, char c);   // 0x0047bf30 eastl::basic_string::append
    // eastl::basic_string::resize(n, 0), inlined: shrink in place, else grow by appending.
    void resize(unsigned n) {
        unsigned size = (unsigned)(mpEnd - mpBegin);
        if (n < size) {
            char* ne = mpBegin + n;
            if (ne != mpEnd) {
                memmove(ne, mpEnd, 1);
                mpEnd = ne;
            }
        } else if (size < n) {
            append(n - size, 0);
        }
    }
};
struct CFragDeclBase {              // 0x1c element of the record's region vector
    EStr           mName;           // +0x00
    unsigned short mField10;        // +0x10
    unsigned short mField12;        // +0x12
    unsigned short mField14;        // +0x14
    unsigned short mField16;        // +0x16
    unsigned       mField18;        // +0x18
};
struct RegionVec {                  // 0x14
    CFragDeclBase* mpBegin;         // +0x00
    CFragDeclBase* mpEnd;           // +0x04
    CFragDeclBase* mpCap;           // +0x08
    int            mField0C;        // +0x0c
    int            mField10;        // +0x10
};
extern RegionVec g_regionsUnused;   // (resize is called via 0x006fc480 on the record's field)
struct VsTableRec {                 // 0x44 SP::cVertexFragmentInfo
    unsigned    mField00;           // +0x00
    EStr        mName;              // +0x04
    EStr        mUniform;           // +0x14
    RegionVec   mRegions;           // +0x24
    unsigned    mField38;           // +0x38
    unsigned    mField3C;           // +0x3c
    unsigned char mField40;         // +0x40
    unsigned char mField41;         // +0x41
    unsigned char mField42;         // +0x42
    unsigned char mPad43;           // +0x43
};
extern VsTableRec g_fragTable[0x100];   // 0x1624710

// A heap (or shared empty) string filled with spaces, used for the flags&2 payload.
static void* AllocGraphics(unsigned n) {
    return FUN_00f473a0(n, "Graphics", 0, 0, "allocator.h", 0xd1);
}
struct TempString {
    char* mpBegin;                  // +0x00
    char* mpEnd;                    // +0x04
    void assignFill(unsigned n) {
        if (n + 1 <= 1) {
            mpBegin = (char*)0x01667bac;
            mpEnd   = (char*)0x01667bad;
        } else {
            mpBegin = (char*)AllocGraphics(n + 1);
            mpEnd   = mpBegin + n + 1;
        }
        memset(mpBegin, 0x20, n);
        mpBegin[n] = 0;
    }
    ~TempString() {
        if (mpEnd - mpBegin > 1 && mpBegin != 0)
            FUN_00f47380(mpBegin);
    }
};

// Resize a record/element string to exactly n bytes, then stream n bytes into it.
static void ReadIntoEStr(void* io, EStr& s, unsigned n) {
    s.resize(n);
    FUN_0093a6c0(io, s.mpBegin, (int)n);
}

// ---- cVertexFragmentInfo record (0x44 bytes) --------------------------------------------
namespace {
struct EString {                    // 0x0c
    char* begin;                    // +0x00
    char* end;                      // +0x04
    char* cap;                      // +0x08
    EString() : begin((char*)0x01667bac), end((char*)0x01667bac), cap((char*)0x01667bad) {}
};
struct CFragVec {                   // 0x14
    void* mpBegin;                  // +0x00
    void* mpEnd;                    // +0x04
    void* mpCap;                    // +0x08
    void* mField0C;                 // +0x0c
    void* mField10;                 // +0x10
    CFragVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
};
struct cVertexFragmentInfo {        // 0x44
    int           f00;              // +0x00
    EString       name;             // +0x04
    int           pad10;            // +0x10 (left uninitialised, as in retail)
    EString       uni;              // +0x14
    int           pad20;            // +0x20 (left uninitialised, as in retail)
    CFragVec      vec;              // +0x24
    int           f38;              // +0x38
    int           f3c;              // +0x3c
    unsigned char b40;              // +0x40
    unsigned char b41;              // +0x41
    unsigned char b42;              // +0x42
    cVertexFragmentInfo() : f00(0), f38(0), f3c(0), b40(0), b41(0), b42(0) {}
    // Real member functions defined in another TU: C++ linkage, so cl must assume they may
    // throw and therefore emits the retail __ehhandler frame around the temporary.
    cVertexFragmentInfo& operator=(const cVertexFragmentInfo& o);   // 0x006ff100
    ~cVertexFragmentInfo();                                         // 0x006fe830
};
} // namespace

// @ 0x006ff170  -- vertex-shader fragment-record serializer: writes the whole 0x1628c20
// vector, one 0x130-byte record at a time (opaque blob, shader blob, element list, lanes).
void __cdecl FUN_006ff170(void* stream) {
    IO* io = (IO*)stream;
    io->Put(0u);
    unsigned count = (unsigned)((g_vs_end - g_vs_begin) / 0x130);
    io->Put(count);
    VecU8 buf;
    buf.mpBegin = 0;
    buf.mpEnd = 0;
    buf.mpCap = 0;
    if ((int)count > 0) {
        unsigned off = 0;
        unsigned n = count;
        do {
            VsRecord* r = (VsRecord*)(g_vs_begin + off);
            io->Write(r->mBlob, 0x20);
            if (r->mpShader == 0) {
                io->Put(0u);
            } else {
                unsigned sz = FUN_00777740(r->mpShader);
                buf.resize(sz);
                FUN_00777720(r->mpShader, (int)sz, buf.mpBegin);
                io->Put(sz);
                io->Write(buf.mpBegin, (int)sz);
            }
            io->Put((unsigned)r->mCount);
            for (int i = 0; i < r->mCount; ++i) {
                FragElem* e = r->mpElems[i];
                io->Put(e->mField10);
                io->Put(e->mField12);
                io->Put(e->mField14);
                io->Put(e->mField16);
                io->Put(e->mField18);
            }
            io->Put(r->mFieldAC, r->mCount);
            io->Put((unsigned)r->mField12C);
            off += 0x130;
        } while (--n != 0);
    }
}

// @ 0x006ff3f0  -- vertex-shader fragment-record deserializer: exact mirror of 0x006ff170,
// rebuilding the 0x1628c20 vector and bump-allocating each record's element list.
void __cdecl FUN_006ff3f0(void* stream) {
    IO* io = (IO*)stream;
    unsigned version;
    unsigned count;
    FUN_0093a780(io, &version, 1, 0);
    FUN_0093a780(io, &count, 1, 0);
    ((void(__thiscall*)(void*, unsigned))FUN_006ff060)(&g_vs_begin, count);
    if ((int)(count + 0x10) > (int)g_15345b0)
        g_15345b0 = count + 0x10;
    VecU8 buf;
    buf.mpBegin = 0;
    buf.mpEnd = 0;
    buf.mpCap = 0;
    unsigned n = (unsigned)((g_vs_end - g_vs_begin) / 0x130);
    if ((int)n > 0) {
        unsigned off = 0;
        do {
            VsRecord* r = (VsRecord*)(g_vs_begin + off);
            FUN_0093a6c0(io, r->mBlob, 0x20);
            unsigned sz;
            FUN_0093a780(io, &sz, 1, 0);
            r->mpShader = 0;
            if (sz != 0) {
                buf.resize(sz);
                FUN_0093a6c0(io, buf.mpBegin, (int)sz);
                void* dev = g_16f89d0;
                void** vtbl = *(void***)dev;
                ((void(__cdecl*)(void*, void*, void**))vtbl[0x16c / 4])
                    (dev, buf.mpBegin, &r->mpShader);
            }
            FUN_0093a780(io, &r->mCount, 1, 0);
            {
                char* base = (char*)g_fragAllocator.Allocate((unsigned)r->mCount * 0x1c);
                int cnt = r->mCount;
                if (cnt > 0) {
                    int i = 0;
                    FragElem* e = (FragElem*)base;
                    FragElem** slot = r->mpElems;
                    do {
                        FUN_0093a700(io, &e->mField10, 1, 0);
                        FUN_0093a700(io, &e->mField12, 1, 0);
                        FUN_0093a700(io, &e->mField14, 1, 0);
                        FUN_0093a700(io, &e->mField16, 1, 0);
                        FUN_0093a780(io, &e->mField18, 1, 0);
                        *slot = e;
                        ++slot;
                        ++e;
                        ++i;
                    } while (i < cnt);
                }
            }
            FUN_0093a780(io, r->mFieldAC, r->mCount, 0);
            FUN_0093a780(io, &r->mField12C, 1, 0);
            off += 0x130;
        } while (--n != 0);
    }
}

// @ 0x006ff680  -- SP::ClearVSFragment: default cVertexFragmentInfo assigned into a table slot,
// the temporary destroyed, then the slot's string/vector members reset.
void __cdecl FUN_006ff680(int idx) {
    cVertexFragmentInfo* dst = (cVertexFragmentInfo*)(&g_vertexFragTable + (unsigned)idx * 0x44);
    {
        cVertexFragmentInfo tmp;    // default constructor inlined (empty-string sentinels)
        *dst = tmp;
    }
    ((void(__thiscall*)(void*, int))FUN_0047d240)((char*)dst + 4, 0);
    ((void(__thiscall*)(void*, int))FUN_0047d240)((char*)dst + 0x14, 0);
    ((void(__thiscall*)(void*, unsigned))FUN_006fc540)((char*)dst + 0x24, 0);
}

// @ 0x006ff750  -- SP::cVertexFragmentInfo table reader: fills the 255-entry global table at
// 0x1624710 from the stream (scalars, two strings, region vector, optional flags payload).
void __cdecl FUN_006ff750(void* stream) {
    IO* io = (IO*)stream;
    VsTableRec* rec = &g_fragTable[1];
    for (; rec < &g_fragTable[0x100]; ++rec) {
        FUN_0093a780(io, &rec->mField38, 1, 0);
        FUN_0093a780(io, &rec->mField3C, 1, 0);
        FUN_0093a6c0(io, &rec->mField41, 1);
        FUN_0093a6c0(io, &rec->mField42, 1);
        FUN_0093a6c0(io, &rec->mField40, 1);
        FUN_0093a780(io, &rec->mField00, 1, 0);

        unsigned n1;
        if (FUN_0093a780(io, &n1, 1, 0) != 0)
            ReadIntoEStr(io, rec->mName, n1);
        unsigned n2;
        if (FUN_0093a780(io, &n2, 1, 0) != 0)
            ReadIntoEStr(io, rec->mUniform, n2);

        unsigned cnt;
        FUN_0093a780(io, &cnt, 1, 0);
        ((void(__thiscall*)(void*, unsigned))FUN_006fc480)(&rec->mRegions, cnt);
        if ((int)cnt > 0) {
            unsigned k = cnt;
            CFragDeclBase* e = rec->mRegions.mpBegin;
            do {
                unsigned ln;
                if (FUN_0093a780(io, &ln, 1, 0) != 0)
                    ReadIntoEStr(io, e->mName, ln);
                FUN_0093a700(io, &e->mField10, 1, 0);
                FUN_0093a700(io, &e->mField12, 1, 0);
                FUN_0093a700(io, &e->mField14, 1, 0);
                FUN_0093a700(io, &e->mField16, 1, 0);
                FUN_0093a780(io, &e->mField18, 1, 0);
                ++e;
            } while (--k != 0);
        }

        if ((rec->mField00 & 2) != 0) {
            unsigned hl;
            FUN_0093a780(io, &hl, 1, 0);
            TempString s;
            s.assignFill(hl);
            FUN_0093a6c0(io, s.mpBegin, (int)hl);
        }
    }
}

// @ 0x006ffa80
struct VertexCtx {
    void SubClip(float d);
    int  TestClip1(const float* a, const float* b);
    int  TestClip2(const float* p, float t);
};

void VertexCtx::SubClip(float d) {
    *(float*)((char*)this + 0x0c) -= d;
    *(float*)((char*)this + 0x34) -= d;
    *(float*)((char*)this + 0x5c) -= d;
    *(float*)((char*)this + 0x84) -= d;
    *(float*)((char*)this + 0xac) -= d;
    *(float*)((char*)this + 0xd4) -= d;
}

// @ 0x006ffaf0
int VertexCtx::TestClip1(const float* a, const float* b) {
    char* self = (char*)this;
    if (g_1628c38 != 0)
        return 0x180;
    float local[6];
    local[0] = a[0];
    local[1] = a[1];
    local[2] = a[2];
    local[3] = b[0];
    local[4] = b[1];
    local[5] = b[2];
    unsigned char found = 0;
    for (unsigned off = 0; off < 0x18; off += 4) {
        int i = g_planeIndices[off / 4];
        float* pf = (float*)(self + i * 0x28);
        int i0 = *(int*)((char*)pf + 0x10);
        int i1 = *(int*)((char*)pf + 0x18);
        int i2 = *(int*)((char*)pf + 0x20);
        float dot = ((pf[2] * local[i2] + pf[1] * local[i1]) + pf[0] * local[i0]) + pf[3];
        if ((*(unsigned int*)&dot & 0x80000000) == 0) {
            found = 1;
            break;
        }
    }
    return (-(unsigned)(found != 0) & 0xfffffec0) + 0x180;
}

// @ 0x006ffbd0
int VertexCtx::TestClip2(const float* p, float t) {
    char* self = (char*)this;
    if (g_1628c38 != 0)
        return 0x180;
    float x = p[0];
    float y = p[1];
    float z = p[2];
    unsigned char found = 0;
    for (unsigned off = 0; off < 0x18; off += 4) {
        int i = g_planeIndices[off / 4];
        float* pf = (float*)(self + i * 0x28);
        float dot = ((pf[2] * z + pf[1] * y) + pf[0] * x) + pf[3];
        if (dot >= t) {
            found = 1;
            break;
        }
    }
    return (-(unsigned)(found != 0) & 0xfffffec0) + 0x180;
}

// @ 0x006ffc60
void __stdcall FUN_006ffc60(int* p) {
    float* pf = (float*)p;
    unsigned int mask = 0;
    if (0.0f <= pf[0]) mask |= 1;
    if (0.0f <= pf[1]) mask |= 2;
    if (0.0f <= pf[2]) mask |= 4;
    switch (mask) {
    case 0: p[4]=3; p[5]=0; p[6]=4; p[7]=1; p[8]=5; p[9]=2; break;
    case 1: p[4]=0; p[5]=3; p[6]=4; p[7]=1; p[8]=5; p[9]=2; break;
    case 2: p[4]=3; p[5]=0; p[6]=1; p[7]=4; p[8]=5; p[9]=2; break;
    case 3: p[4]=0; p[5]=3; p[6]=1; p[7]=4; p[8]=5; p[9]=2; break;
    case 4: p[4]=3; p[5]=0; p[6]=4; p[7]=1; p[8]=2; p[9]=5; break;
    case 5: p[4]=0; p[5]=3; p[6]=4; p[7]=1; p[8]=2; p[9]=5; break;
    case 6: p[4]=3; p[5]=0; p[6]=1; p[7]=4; p[8]=2; p[9]=5; break;
    case 7: p[4]=0; p[5]=3; p[6]=1; p[7]=4; p[8]=2; p[9]=5; break;
    }
}

// @ 0x006ffdc0
float* __cdecl FUN_006ffdc0(float* dst, const float* src) {
    float* d = dst;
    const float* s = src;
    int n = 4;
    do {
        d[0] = s[0];
        d[1] = s[4];
        d[2] = s[8];
        d[3] = s[12];
        ++s;
        d += 4;
    } while (--n);
    return dst;
}
