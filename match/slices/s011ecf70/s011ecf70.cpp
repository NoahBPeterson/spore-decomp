// Spore / SporeApp.exe -- gold4 batch, slice s011ecf70 (26 functions)
// 0x011ecf70 .. 0x011edcf0
//
// Mix of rw::core::stdc integer-to-string helpers, rw::core::thread semaphore
// primitives, and two smaller utility objects (StreamName, a HANDLE holder).

typedef unsigned char  byte;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;
typedef int            BOOL;
typedef void*          HANDLE;
typedef unsigned long  DWORD;
typedef long           LONG;

// --- kernel32 imports used by the semaphore code -----------------------------
extern "C" {
    extern HANDLE (__stdcall *CreateSemaphoreA)(void* sa, LONG max, LONG initial, const char* name);
    DWORD  __stdcall WaitForSingleObject(HANDLE h, DWORD ms);
    BOOL   __stdcall ReleaseSemaphore(HANDLE h, LONG count, LONG* prev);
    extern BOOL (__stdcall *CloseHandle)(HANDLE h);
    LONG   __stdcall InterlockedIncrement(volatile LONG* p);
    LONG   __stdcall InterlockedDecrement(volatile LONG* p);
    LONG   __stdcall InterlockedExchange(volatile LONG* p, LONG v);
    LONG   __stdcall InterlockedExchangeAdd(volatile LONG* p, LONG v);
    LONG   __stdcall InterlockedCompareExchange(volatile LONG* p, LONG exch, LONG comp);
}
extern "C" int __cdecl strncpy_s_dummy(void);

// --- rw::core::stdc ----------------------------------------------------------
namespace rw { namespace core { namespace stdc {

char* ConvertU32ToA(char* buf, int value);                         // 0x011ecf70
char* ConvertI64ToA_rec(char* buf, int lo, int hi);               // 0x011ecfa0
char* ConvertU32ToBase(char* buf, uint value, uint base);         // 0x011ecff0
char* ConvertU64ToBase(char* buf, int lo, int hi, uint base, uint a5); // 0x011ed020
char* ConvertU32ToHexUpper(char* buf, uint value);                // 0x011ed070
char* ConvertU32ToHexLower(char* buf, uint value);                // 0x011ed0b0
char* ConvertIToA(uint value, char* buf, uint base);              // 0x011ed0f0
char* ConvertI64ToA(int lo, int hi, char* buf, int base, int a5); // 0x011ed190
char* ConvertU32ToStr(uint value, char* buf, int asHex);          // 0x011ed230
ushort* CopyAtoW(ushort* dst, const char* src);                   // 0x011ed270
uint*  Memset32(uint* dst, uint value, uint size);                // 0x011ed2a0

} } }

// --- rw::core::thread --------------------------------------------------------
namespace rw { namespace core { namespace thread {

struct RwSemaphoreData {
    HANDLE mhSemaphore;    // +0x00
    LONG   mnCount;        // +0x04
    LONG   mnCancelCount;  // +0x08
    byte   mbIntraProcess; // +0x0c
};

class Semaphore { public:
    RwSemaphoreData mSemaphoreData;
    byte Init(const void* p);        // 0x011ed400
    uint Wait(uint* pTimeout);       // 0x011ed470
    uint Post(int count);            // 0x011ed520
    Semaphore* ctor0(int a2, char a3);               // 0x011ed5d0
};

DWORD GetThreadTime(void);                                        // 0x011ec7f0
void  RwSemaphoreData_UpdateCancelCount(RwSemaphoreData* d, int n); // 0x011ed350
void __fastcall CloseHandleIfSet(HANDLE* h);                      // 0x011ed3f0

} } }

// --- misc --------------------------------------------------------------------
int   StringCopyBounded(char* dst, const char* src);              // 0x011e8b20
char* BuildStateLookupShader(char* p);                            // 0x011fa000
void* ArenaIdToObject(void* arena, uint id);                      // 0x011e2300
void  FixupThing1(void* a, char* b);                              // 0x011f2e10
ushort MapShaderHandle(void* arena, ushort h);                    // 0x011f42c0

// ---------------------------------------------------------------------------
// 0x011ecf70: rw::core::stdc::ConvertU32ToA
// ---------------------------------------------------------------------------
// @ 0x011ecf70
char* rw::core::stdc::ConvertU32ToA(char* buf, int value)
{
    if (value > 0) {
        char* p = ConvertU32ToA(buf, value / 10);
        *p = (char)(value % 10) + '0';
        return p + 1;
    }
    return buf;
}

// ---------------------------------------------------------------------------
// 0x011ecfa0: rw::core::stdc::ConvertI64ToA_rec
// ---------------------------------------------------------------------------
// @ 0x011ecfa0
extern "C" long long __cdecl _alldvrm_helper(int lo, int hi, int d, int a4);

char* rw::core::stdc::ConvertI64ToA_rec(char* buf, int lo, int hi)
{
    if (hi < 0)
        return buf;
    if (hi == 0 && (uint)lo <= 0)
        return buf;
    long long q = _alldvrm_helper(lo, hi, 10, 0);
    char* p = ConvertI64ToA_rec(buf, (int)q, (int)(q >> 32));
    *p = (char)((q >> 32) & 0xff) + '0';
    return p + 1;
}

// ---------------------------------------------------------------------------
// 0x011ecff0: rw::core::stdc::ConvertU32ToBase
// ---------------------------------------------------------------------------
// @ 0x011ecff0
char* rw::core::stdc::ConvertU32ToBase(char* buf, uint value, uint base)
{
    if (value > 0) {
        char* p = ConvertU32ToBase(buf, value / base, base);
        *p = (char)(value % base) + '0';
        return p + 1;
    }
    return buf;
}

// ---------------------------------------------------------------------------
// 0x011ed020: rw::core::stdc::ConvertU64ToBase
// ---------------------------------------------------------------------------
// @ 0x011ed020
extern "C" long long __cdecl _aulldvrm_helper(int lo, int hi, uint d, uint a4);

char* rw::core::stdc::ConvertU64ToBase(char* buf, int lo, int hi, uint base, uint a5)
{
    if (lo == 0 && hi == 0)
        return buf;
    long long q = _aulldvrm_helper(lo, hi, base, 0);
    char* p = ConvertU64ToBase(buf, (int)q, (int)(q >> 32), base, a5);
    *p = (char)((q >> 32) & 0xff) + '0';
    return p + 1;
}

// ---------------------------------------------------------------------------
// 0x011ed070: rw::core::stdc::ConvertU32ToHexUpper
// ---------------------------------------------------------------------------
// @ 0x011ed070
char* rw::core::stdc::ConvertU32ToHexUpper(char* buf, uint value)
{
    if (value > 0) {
        char* p = ConvertU32ToHexUpper(buf, value >> 4);
        if (((byte)value & 0xf) < 10) {
            *p = ((byte)value & 0xf) + 0x30;
            return p + 1;
        }
        *p = ((byte)value & 0xf) + 0x37;
        return p + 1;
    }
    return buf;
}

// ---------------------------------------------------------------------------
// 0x011ed0b0: rw::core::stdc::ConvertU32ToHexLower
// ---------------------------------------------------------------------------
// @ 0x011ed0b0
char* rw::core::stdc::ConvertU32ToHexLower(char* buf, uint value)
{
    if (value > 0) {
        char* p = ConvertU32ToHexLower(buf, value >> 4);
        if (((byte)value & 0xf) < 10) {
            *p = ((byte)value & 0xf) + 0x30;
            return p + 1;
        }
        *p = ((byte)value & 0xf) + 0x57;
        return p + 1;
    }
    return buf;
}

// ---------------------------------------------------------------------------
// 0x011ed0f0: rw::core::stdc::ConvertIToA
// ---------------------------------------------------------------------------
// @ 0x011ed0f0
char* rw::core::stdc::ConvertIToA(uint value, char* buf, uint base)
{
    char* start = buf;
    int v = (int)value;
    if (v < 0 && base == 10) {
        if (value == 0x80000000u) {
            StringCopyBounded(buf, "-2147483648");
            return buf;
        }
        *buf++ = '-';
        v = -v;
    }
    if (v == 0) {
        *buf = '0';
        buf[1] = 0;
        return start;
    }
    if (base == 10) {
        if (v > 0) {
            char* q = ConvertU32ToA(buf, v / 10);
            *q = (char)(v % 10) + '0';
            q[1] = 0;
        }
    } else {
        if (v > 0) {
            char* q = ConvertU32ToBase(buf, (uint)v / base, base);
            *q++ = (char)((uint)v % base) + '0';
            buf = q;
        }
    }
    *buf = 0;
    return start;
}

// ---------------------------------------------------------------------------
// 0x011ed190: rw::core::stdc::ConvertI64ToA
// ---------------------------------------------------------------------------
// @ 0x011ed190
char* rw::core::stdc::ConvertI64ToA(int lo, int hi, char* buf, int base, int a5)
{
    char* start = buf;
    if (hi < 1 && (hi < 0 || (uint)lo >= 0x80000000u) && base == 10 && a5 == 0) {
        if (lo == 0 && hi == (int)0x80000000) {
            StringCopyBounded(buf, "-9223372036854775808");
            return buf;
        }
        *buf++ = '-';
        uint u = (uint)lo;
        uint h = (uint)hi;
        uint n = -(u + (h != 0));
        hi = -(int)(h + (u != 0));
        lo = (int)n;
        (void)hi;
    }
    if (lo == 0 && hi == 0) {
        *buf = '0';
        buf[1] = 0;
        return start;
    }
    if (base == 10 && a5 == 0) {
        char* q = ConvertI64ToA_rec(buf, lo, hi);
        *q = 0;
        return start;
    }
    char* q = ConvertU64ToBase(buf, lo, hi, (uint)base, (uint)a5);
    *q = 0;
    return start;
}

// ---------------------------------------------------------------------------
// 0x011ed230: rw::core::stdc::ConvertU32ToStr
// ---------------------------------------------------------------------------
// @ 0x011ed230
char* rw::core::stdc::ConvertU32ToStr(uint value, char* buf, int asHex)
{
    if (value == 0) {
        *buf = '0';
        buf[1] = 0;
        return buf;
    }
    if (asHex == 0) {
        char* q = ConvertU32ToHexUpper(buf, value);
        *q = 0;
        return buf;
    }
    char* q = ConvertU32ToHexLower(buf, value);
    *q = 0;
    return buf;
}

// ---------------------------------------------------------------------------
// 0x011ed270: rw::core::stdc::CopyAtoW
// ---------------------------------------------------------------------------
// @ 0x011ed270
ushort* rw::core::stdc::CopyAtoW(ushort* dst, const char* src)
{
    ushort* start = dst;
    byte bVar1 = (byte)*src;
    while (bVar1 != 0) {
        src++;
        *dst = (ushort)((uint)bVar1 & 0xff);
        dst++;
        bVar1 = (byte)*src;
    }
    *dst = 0;
    return start;
}

// ---------------------------------------------------------------------------
// 0x011ed2a0: rw::core::stdc::Memset32
// ---------------------------------------------------------------------------
// @ 0x011ed2a0
uint* rw::core::stdc::Memset32(uint* dst, uint value, uint size)
{
    uint n = size;
    while ((int)(n - 0x20) >= 0) {
        dst[0] = value; dst[1] = value; dst[2] = value; dst[3] = value;
        dst[4] = value; dst[5] = value; dst[6] = value; dst[7] = value;
        dst += 8;
        n -= 0x20;
    }
    while ((int)(n - 8) >= 0) {
        dst[0] = value;
        dst[1] = value;
        dst += 2;
        n -= 8;
    }
    if (n == 0)
        return dst;
    if (n >= 4) {
        *dst = value;
        dst++;
        n -= 4;
    }
    if (n >= 2) {
        *(ushort*)dst = (ushort)value;
        value >>= 16;
        dst = (uint*)((char*)dst + 2);
        n -= 2;
    }
    if (n != 0) {
        *(byte*)dst = (byte)value;
        dst = (uint*)((char*)dst + 1);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// 0x011ed350: rw::core::thread::RwSemaphoreData::UpdateCancelCount
// ---------------------------------------------------------------------------
// @ 0x011ed350
void rw::core::thread::RwSemaphoreData_UpdateCancelCount(RwSemaphoreData* d, int n)
{
    if (n <= 0)
        return;
    LONG cur = d->mnCount;
    if (cur >= 0)
        goto tail;
    for (;;) {
        LONG want = cur + n;
        if (want > 0)
            want = 0;
        LONG got = InterlockedCompareExchange(&d->mnCount, want, cur);
        if (got == cur) {
            n = n + (got - want);
            break;
        }
        cur = got;
        if (got >= 0)
            break;
    }
tail:
    if (n > 0)
        InterlockedExchangeAdd(&d->mnCancelCount, n);
}

// ---------------------------------------------------------------------------
// 0x011ed3f0: HANDLE holder destructor
// ---------------------------------------------------------------------------
// @ 0x011ed3f0
void __fastcall rw::core::thread::CloseHandleIfSet(HANDLE* h)
{
    if (*h != 0)
        CloseHandle(*h);
}

// ---------------------------------------------------------------------------
// 0x011ed400: rw::core::thread::Semaphore::Init
// ---------------------------------------------------------------------------
// @ 0x011ed400
byte rw::core::thread::Semaphore::Init(const void* p)
{
    const char* pp = (const char*)p;
    byte result = 0;
    if (p != 0) {
        if (mSemaphoreData.mhSemaphore == 0) {
            int c = *(const int*)pp;
            mSemaphoreData.mnCount = c;
            if (c < 0)
                mSemaphoreData.mnCount = 0;
            byte intra = *(const byte*)(pp + 4);
            mSemaphoreData.mbIntraProcess = intra;
            if (intra == 0) {
                const char* nm = pp + 5;
                const char* name = (*nm != 0) ? nm : 0;
                mSemaphoreData.mhSemaphore =
                    CreateSemaphoreA(0, 0x3fffffff, mSemaphoreData.mnCount, name);
            } else {
                mSemaphoreData.mhSemaphore = CreateSemaphoreA(0, 0x3fffffff, 0, 0);
            }
            result = mSemaphoreData.mhSemaphore != 0;
        }
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x011ed470: rw::core::thread::Semaphore::Wait
// ---------------------------------------------------------------------------
// @ 0x011ed470
uint rw::core::thread::Semaphore::Wait(uint* pTimeout)
{
    uint t = *pTimeout;
    if (t != 0xffffffffu && t != 0) {
        DWORD now = GetThreadTime();
        t = (now < *pTimeout) ? (*pTimeout - now) : 0;
    }
    if (mSemaphoreData.mbIntraProcess == 0) {
        DWORD r = WaitForSingleObject(mSemaphoreData.mhSemaphore, t);
        if (r != 0)
            return (r != 0x102) - 2;
        return (uint)InterlockedDecrement(&mSemaphoreData.mnCount);
    }
    LONG v = InterlockedDecrement(&mSemaphoreData.mnCount);
    if (v < 0) {
        DWORD r = WaitForSingleObject(mSemaphoreData.mhSemaphore, t);
        if (r != 0) {
            RwSemaphoreData_UpdateCancelCount(&mSemaphoreData, 1);
            return 0xfffffffeu;
        }
    }
    uint u = (uint)mSemaphoreData.mnCount;
    return u & (uint)(((int)u < 1) - 1);
}

// ---------------------------------------------------------------------------
// 0x011ed520: rw::core::thread::Semaphore::Post
// ---------------------------------------------------------------------------
// @ 0x011ed520
uint rw::core::thread::Semaphore::Post(int count)
{
    if (count <= 0)
        return (uint)mSemaphoreData.mnCount;
    if (mSemaphoreData.mbIntraProcess != 0) {
        if (mSemaphoreData.mnCancelCount > 0 && mSemaphoreData.mnCount < 0) {
            LONG ex = InterlockedExchange(&mSemaphoreData.mnCancelCount, 0);
            RwSemaphoreData_UpdateCancelCount(&mSemaphoreData, ex);
        }
        LONG prev = InterlockedExchangeAdd(&mSemaphoreData.mnCount, count);
        if (prev < 0) {
            if (-prev <= count)
                count = -prev;
            ReleaseSemaphore(mSemaphoreData.mhSemaphore, count, 0);
        }
        uint u = (uint)mSemaphoreData.mnCount;
        return u & (uint)(((int)u < 1) - 1);
    }
    InterlockedExchangeAdd(&mSemaphoreData.mnCount, count);
    if (ReleaseSemaphore(mSemaphoreData.mhSemaphore, count, 0) == 0) {
        InterlockedExchangeAdd(&mSemaphoreData.mnCount, -count);
        return 0xffffffffu;
    }
    return (uint)mSemaphoreData.mnCount;
}

// ---------------------------------------------------------------------------
// 0x011ed5d0: rw::core::thread::Semaphore::ctor0
// ---------------------------------------------------------------------------
// @ 0x011ed5d0
rw::core::thread::Semaphore* rw::core::thread::Semaphore::ctor0(int a2, char a3)
{
    int local[6];
    mSemaphoreData.mhSemaphore = 0;
    mSemaphoreData.mnCount = 0;
    mSemaphoreData.mnCancelCount = 0;
    mSemaphoreData.mbIntraProcess = 1;
    if (a2 == 0 && a3 != 0) {
        char* b = (char*)local;
        *(int*)b = 0;
        b[4] = 1;
        b[5] = 0;
        Init(b);
        return this;
    }
    Init((const void*)a2);
    return this;
}

// --- rw::graphics::EmbeddedState --------------------------------------------
namespace rw { namespace graphics {

class EmbeddedState { public:
    char  pad00[8];
    uint  m_softStateDirty;   // +0x08
    char  pad0c[8];
    uint  m_hardStateDelta;   // +0x14
    // helper: 16-byte aligned base = (this + 0x2b) & ~0xf
    void* alignedBase() { return (void*)(((uint)this + 0x2b) & 0xfffffff0u); }
    void  SetMaterialColor(const void* src);         // 0x011eda00
    void* GetMaterialColor();                        // 0x011eda90
    void  GetDeviceState(uint key, uint value);      // 0x011edab0
    void  D3D9SetTransform(const float* m, int slot);// 0x011edc10
    uint  SetVertexDescriptor();                     // 0x011edcd0
    int   D3D9GetShaderData(short key);              // 0x011edcf0
};

} }

extern "C" {
    void  __fastcall EmbeddedState_DestroyShader(void* p);           // 0x011f3130
    void  __fastcall EmbeddedState_Fixup(void* a, char* b);          // 0x011f2e10
    void* __fastcall Arena_IdToObject(void* arena, uint id);         // 0x011e2300
}

// __cdecl, C++ linkage (also declared above)
ushort MapShaderHandle(void* arena, ushort h);                       // 0x011f42c0

// ---------------------------------------------------------------------------
// 0x011ed690: rw::graphics::EmbeddedState fixup
// ---------------------------------------------------------------------------
// @ 0x011ed690
void EmbeddedStateFixup(char* state, void* arena)
{
    if (*(void**)(state + 0x18) != 0) {
        *(void**)(state + 0x18) = BuildStateLookupShader(*(char**)(state + 0x18));
    }
    uint flags = *(uint*)(state + 8);
    char* p = (char*)(((uint)(state + 0x2b)) & 0xfffffff0u);
    if (flags != 0) {
        if (flags & 1) {
            if (flags & 2)
                p += 4;
            else
                p += 0x40;
        }
        if (flags & 0x100000) {
            EmbeddedState_Fixup(p, (char*)arena);
            p += (*(ushort*)(p + 0xc) + 2) * 0xc;
        }
        if (flags & 8) {
            for (;;) {
                char* e = p;
                uint h = *(ushort*)e;
                p += 8;
                if (h == 0)
                    break;
                void* obj;
                if (*(ushort*)(e + 4) != 0) {
                    uint n = *(ushort*)(e + 2);
                    uint sz = *(ushort*)(e + 4);
                    void** slot = (void**)((char*)0x16fa600 + h * 32);
                    if (*slot != 0)
                        ((void(*)(void*, char*))*slot)(arena, p + n);
                    p += n + sz;
                } else {
                    *((ushort*)e) = MapShaderHandle(arena, (ushort)h);
                    void* o = Arena_IdToObject(arena, *(uint*)p);
                    if (o == 0)
                        o = *(void**)((char*)0x16fa5f4 + h * 32);
                    *(void**)p = o;
                    p += 4;
                }
            }
        }
        flags = *(uint*)(state + 8);
        if (flags & 0x10)
            p += 0x10;
        if (flags & 0x20)
            p += 0xc;
        if ((flags & 0x3fc0) != 0) {
            int i = 6;
            do {
                uint bit = 1u << i;
                if (bit > (flags & 0x3fc0))
                    break;
                if (flags & bit) {
                    void* o = Arena_IdToObject(arena, *(uint*)p);
                    if (o != 0) {
                        *(void**)p = o;
                        p += 4;
                    }
                }
                i++;
            } while ((uint)(i - 6) < 8);
        }
        if (flags & 0x8000)
            p += 0x11;
        if (flags & 0xf0000) {
            if (flags & 0x10000)
                p += 4;
            if (flags & 0xe0000) {
                if (flags & 0x20000)
                    p += 0xc;
                if (flags & 0x40000)
                    p += 4;
                if (flags & 0x80000)
                    p += 4;
            }
        }
    }
}

// ---------------------------------------------------------------------------
// 0x011ed910: rw::graphics::EmbeddedState soft-state shader cleanup
// ---------------------------------------------------------------------------
// @ 0x011ed910
void __fastcall EmbeddedStateCleanupShaders(char* state)
{
    uint flags = *(uint*)(state + 8);
    char* p = (char*)(((uint)(state + 0x2b)) & 0xfffffff0u);
    if (flags & 1) {
        if (flags & 2)
            p += 4;
        else
            p += 0x40;
    }
    if (flags & 0x100000) {
        char* old = p;
        p = p + (*(ushort*)(p + 0xc) + 2) * 0xc;
        EmbeddedState_DestroyShader(old);
    }
    if (*(byte*)(state + 8) & 8) {
        char* e = p;
        ushort h = *(ushort*)e;
        p += 8;
        if (h != 0) {
            for (;;) {
                if (*(ushort*)(e + 4) <= 0) {
                    p += 4;
                } else {
                    p = p + *(ushort*)(e + 2);
                    if (*(void**)((char*)0x16f65a8 + h * 4) == p) {
                        *(void**)((char*)0x16f65a8 + h * 4) = 0;
                        *(uint*)0x16f9110 |= 8;
                        uint idx = h >> 5;
                        *(uint*)((char*)0x16f89f8 + idx * 4) |= 1u << (h & 0x1f);
                    }
                    p = p + *(ushort*)(e + 4);
                }
                e = p;
                h = *(ushort*)e;
                p += 8;
                if (h == 0)
                    break;
            }
        }
    }
}

// ---------------------------------------------------------------------------
// 0x011eda00: rw::graphics::EmbeddedState::SetMaterialColor
// ---------------------------------------------------------------------------
// @ 0x011eda00
void rw::graphics::EmbeddedState::SetMaterialColor(const void* src)
{
    uint flags = m_softStateDirty;
    char* p = (char*)alignedBase();
    if (flags & 1) {
        if (flags & 2)
            p += 4;
        else
            p += 0x40;
    }
    if (flags & 0x100000)
        p += ((ushort*)p)[6] * 0xc + 0x18;
    if (flags & 8) {
        char* e = p;
        p += 8;
        while (*(ushort*)e != 0) {
            if (*(unsigned short*)(e + 4) > 0)
                p = (char*)(p + *(unsigned short*)(e + 4) + *(unsigned short*)(e + 2));
            else
                p += 4;
            e = p;
            p += 8;
        }
    }
    const uint* s = (const uint*)src;
    *(uint*)(p + 0) = s[0];
    *(uint*)(p + 4) = s[1];
    *(uint*)(p + 8) = s[2];
    *(uint*)(p + 0xc) = s[3];
}

// ---------------------------------------------------------------------------
// 0x011eda90: rw::graphics::EmbeddedState::GetMaterialColor
// ---------------------------------------------------------------------------
// @ 0x011eda90
void* rw::graphics::EmbeddedState::GetMaterialColor()
{
    byte b = *(byte*)((char*)this + 8);
    char* p = (char*)alignedBase();
    if (b & 2)
        p = *(char**)p;
    return p;
}

// ---------------------------------------------------------------------------
// 0x011edab0: rw::graphics::EmbeddedState::GetDeviceState
// ---------------------------------------------------------------------------
// @ 0x011edab0
void rw::graphics::EmbeddedState::GetDeviceState(uint key, uint value)
{
    uint flags = m_softStateDirty;
    char* p = (char*)alignedBase();
    if (flags != 0) {
        if (flags & 1) {
            if (flags & 2)
                p += 4;
            else
                p += 0x40;
        }
        if (flags & 0x100000)
            p += ((ushort*)p)[6] * 0xc + 0x18;
        if (flags & 8) {
            char* e = p;
            p += 8;
            if (*(ushort*)e != 0) {
                do {
                    ushort sz = *(ushort*)(e + 4);
                    if (sz != 0)
                        p = p + sz + *(ushort*)(e + 2);
                    else
                        p += 4;
                    e = p;
                    p += 8;
                } while (*(ushort*)e != 0);
            }
        }
        if (flags & 0x10)
            p += 0x10;
        if (flags & 0x20)
            p += 0xc;
        if (flags & 0x3fc0) {
            int i = 6;
            do {
                uint bit = 1u << i;
                if (bit > (flags & 0x3fc0))
                    break;
                if (flags & bit)
                    p += 4;
                i++;
            } while ((uint)(i - 6) < 8);
        }
        if ((flags & 0x8000) != 0)
            p += 0x11;
        if (flags & 0xf0000) {
            if (flags & 0x10000)
                p += 4;
            if (flags & 0xe0000) {
                if (flags & 0x20000)
                    p += 0xc;
                if (flags & 0x40000)
                    p += 4;
                if (flags & 0x80000)
                    p += 4;
            }
        }
    }
    uint hd = m_hardStateDelta;
    if (hd != 0) {
        if (hd & 0x20000)
            p += 0x1c;
        if (hd & 0x40000)
            p += 0x44;
        if (hd & 0x80000)
            p += 0x44;
    }
    p += 4;
    for (;;) {
        int k = *(int*)p;
        p += 4;
        for (;;) {
            if (k == (int)key) {
                *(uint*)p = value;
                return;
            }
            k = *(int*)(p + 4);
            p += 8;
            if (k == -1)
                break;
        }
        if (*(int*)p == -1)
            return;
    }
}

// ---------------------------------------------------------------------------
// 0x011edc10: rw::graphics::EmbeddedState::D3D9SetTransform
// ---------------------------------------------------------------------------
// @ 0x011edc10
void rw::graphics::EmbeddedState::D3D9SetTransform(const float* m, int slot)
{
    uint flags = m_softStateDirty;
    float* p = (float*)alignedBase();
    m_softStateDirty = (flags & 0x8fffffffu) | ((uint)slot << 28);
    if (flags & 2) {
        *(void**)p = (void*)m;
        return;
    }
    for (int i = 0; i < 4; i++) {
        p[i * 4 + 0] = m[i * 4 + 0];
        p[i * 4 + 1] = m[i * 4 + 1];
        p[i * 4 + 2] = m[i * 4 + 2];
        p[i * 4 + 3] = (i == 3) ? 1.0f : 0.0f;
    }
}

// ---------------------------------------------------------------------------
// 0x011edcd0: rw::graphics::EmbeddedState::SetVertexDescriptor
// ---------------------------------------------------------------------------
// @ 0x011edcd0
uint rw::graphics::EmbeddedState::SetVertexDescriptor()
{
    uint p = (uint)alignedBase();
    uint flags = m_softStateDirty;
    if (flags & 1) {
        if (flags & 2)
            return p + 4;
        p += 0x40;
    }
    return p;
}

// ---------------------------------------------------------------------------
// 0x011edcf0: rw::graphics::EmbeddedState::D3D9GetShaderData
// ---------------------------------------------------------------------------
// @ 0x011edcf0
int rw::graphics::EmbeddedState::D3D9GetShaderData(short key)
{
    uint uVar1 = m_softStateDirty;
    int iVar2 = 0;
    short* psVar3 = (short*)(((uint)this + 0x2b) & 0xfffffff0u);
    if (uVar1 & 1) {
        if (uVar1 & 2)
            psVar3 = psVar3 + 2;
        else
            psVar3 = psVar3 + 0x20;
    }
    if (uVar1 & 0x100000) {
        psVar3 = psVar3 + ((ushort)psVar3[6] + 2) * 6;
    }
    short sVar5 = *psVar3;
    if (sVar5 != 0) {
        for (;;) {
            int* piVar4 = (int*)(psVar3 + 4);
            if (key == sVar5) {
                if ((ushort)psVar3[2] != 0)
                    return (int)piVar4 + (ushort)psVar3[1];
                return *piVar4;
            }
            if (psVar3[2] == 0)
                psVar3 = psVar3 + 6;
            else
                psVar3 = (short*)((int)piVar4 + (uint)(ushort)psVar3[1] + (uint)(ushort)psVar3[2]);
            sVar5 = *psVar3;
            if (sVar5 == 0)
                return iVar2;
        }
    }
    return iVar2;
}

// ---------------------------------------------------------------------------
// 0x011ed3b0: StreamName::set
// ---------------------------------------------------------------------------
// @ 0x011ed3b0
extern "C" char* (__cdecl *strncpy)(char* dst, const char* src, unsigned n);

struct StreamName {
    uint  m_id;         // +0x00
    char  m_type;       // +0x04
    char  m_name[16];   // +0x05
    StreamName* set(int id, char type, const char* name);
};

// ---------------------------------------------------------------------------
// 0x011ed3b0: StreamName::set
// ---------------------------------------------------------------------------
// @ 0x011ed3b0
StreamName* StreamName::set(int id, char type, const char* name)
{
    m_id = id;
    m_type = type;
    if (name != 0) {
        strncpy(m_name, name, 0xf);
        m_name[0xf] = 0;
        return this;
    }
    m_name[0] = 0;
    return this;
}
