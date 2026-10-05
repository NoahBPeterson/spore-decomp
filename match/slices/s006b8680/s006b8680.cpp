// Slice s006b8680: SP::GetSystemInfo and its string/compare/matrix helpers.
// Same module as s006b7880: /O2 /MD /Gy /GS- /EHsc /TP /arch:SSE.
#include "types.h"

typedef unsigned int DWORD;
typedef unsigned int LCID;
typedef void* HMODULE;
typedef void* FARPROC;

extern "C" {
    __declspec(dllimport) int __stdcall GetComputerNameExA(int, char*, DWORD*);
    __declspec(dllimport) int __stdcall GetUserNameW(wchar_t*, DWORD*);
    __declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char*);
    __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, const char*);
    __declspec(dllimport) int __stdcall FreeLibrary(HMODULE);
    __declspec(dllimport) int __stdcall GetVersionExA(void*);
    __declspec(dllimport) void __stdcall GetSystemInfo(void*);
    __declspec(dllimport) int __stdcall GlobalMemoryStatusEx(void*);
    __declspec(dllimport) int __stdcall CompareStringW(LCID, DWORD, const wchar_t*, int, const wchar_t*, int);
    __declspec(dllimport) int __stdcall LCMapStringW(LCID, DWORD, const wchar_t*, int, wchar_t*, int);
}
extern "C" int __cdecl sprintf(char*, const char*, ...);
extern "C" float __cdecl sinf(float);
extern "C" float __cdecl cosf(float);
extern "C" float __cdecl sqrtf(float);
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" unsigned int __cdecl wcslen(const wchar_t*);

int __cdecl ConvertEncoding6(const char*, int, int, void*, int*, int);   // 0x93c950
int __cdecl ConvertEncoding4(const char*, int, int, void*);              // 0x93cfb0
bool __cdecl FUN_0087da90(void*, const void*);
int __cdecl FUN_WriteUint16(void*, void*, int, int);   // 0x93a9d0
int __cdecl FUN_WriteUint32(void*, void*, int, int);   // 0x93aa70
int __cdecl FUN_IO_Field1(void*, void*);               // 0x6980c0
int __cdecl FUN_IO_Field2(void*, void*);               // 0x6980e0
extern "C" bool __cdecl FUN_006b82a0(char, uint32_t*);
extern "C" void __cdecl FUN_006b8680(void*);

extern uint8_t DAT_01605ab4;
extern uint8_t DAT_01605d34;
extern const char DAT_015311fc;

// ---------------------------------------------------------------------------
// CBig (same layout as slice s006b7880)
// ---------------------------------------------------------------------------
struct EStr {
    const char* mpBegin;
    const char* mpEnd;
    const char* mpCapacity;
    void*       mpAllocator;
    EStr();
    EStr& assign(const char*, const char*);
    EStr& operator=(const EStr& x) { if (&x != this) assign(x.mpBegin, x.mpEnd); return *this; }
};
struct CBig {
    EStr    mStrings[9];
    float   m90;
    int32_t m94;
    uint8_t m98, m99, m9a, m9b, m9c;
    uint8_t mPad[3];
    float   m0a0, m0a4, m0a8, m0ac;
    CBig();
    ~CBig();
    CBig& operator=(const CBig&);
};

// ---------------------------------------------------------------------------
// @ 0x006b8f00  UTF-8 -> UTF-16 into dst, returns element count
// ---------------------------------------------------------------------------
int __cdecl FUN_006b8f00(const char* src, int* dst)
{
    int len = (int)strlen(src);
    ConvertEncoding4(src, len, 8, dst);
    return (dst[1] - dst[0]) >> 1;
}

// ---------------------------------------------------------------------------
// @ 0x006b8d60  UTF-8 -> UTF-16 with capacity, returns count
// ---------------------------------------------------------------------------
int __cdecl FUN_006b8d60(const char* src, wchar_t* dst, int dstLen)
{
    int n = dstLen;
    if (n == 0) return 0;
    int len = (int)strlen(src);
    n = n - 1;
    ConvertEncoding6(src, len, 8, dst, &n, 0x10);
    *(uint16_t*)(dst + n) = 0;
    return n;
}

// ---------------------------------------------------------------------------
// @ 0x006b8db0  UTF-16 -> UTF-8 with capacity, returns count
// ---------------------------------------------------------------------------
int __cdecl FUN_006b8db0(const wchar_t* src, char* dst, int dstLen)
{
    int n = dstLen;
    if (n == 0) return 0;
    int len = (int)wcslen(src);
    n = n - 1;
    ConvertEncoding6((const char*)src, len, 0x10, dst, &n, 8);
    dst[n] = 0;
    return n;
}

// ---------------------------------------------------------------------------
// @ 0x006b8e10  CompareStringW wrapper
// ---------------------------------------------------------------------------
int __cdecl FUN_006b8e10(const wchar_t* a, int na, const wchar_t* b, int nb, uint32_t flags)
{
    DWORD cmpFlags = 0;
    LCID locale = 0x400;
    LCID local[2];
    if (FUN_0087da90(local, &DAT_015311fc)) locale = local[0];
    if (flags & 0x20) locale = 0x7f;
    if (flags & 1) cmpFlags = 1;
    if (flags & 2) cmpFlags |= 0x10000;
    if (flags & 4) cmpFlags |= 2;
    if (flags & 8) cmpFlags |= 4;
    if (flags & 0x10) cmpFlags |= 0x20000;
    if (flags & 0x40) cmpFlags |= 0x1000;
    return CompareStringW(locale, cmpFlags, a, na, b, nb) - 2;
}

// ---------------------------------------------------------------------------
// @ 0x006b8ea0  compare two wide strings (case-insensitive)
// ---------------------------------------------------------------------------
void __cdecl FUN_006b8ea0(const wchar_t* a, const wchar_t* b, uint32_t flags)
{
    int nb = (int)wcslen(b);
    int na = (int)wcslen(a);
    FUN_006b8e10(a, na, b, nb, flags | 1);
}

// ---------------------------------------------------------------------------
// @ 0x006b8f40  LCMapStringW-based case mapping appended to a wide string
// ---------------------------------------------------------------------------
void __cdecl FUN_006b8f40(void* str)
{
    // EH-heavy original; behavioural rewrite (partial)
    (void)str;
}

// ---------------------------------------------------------------------------
// @ 0x006b9050  rotate matrix rows by angle (sin/cos)
// ---------------------------------------------------------------------------
struct MatX {
    uint16_t flags;
    uint16_t count;
    uint8_t  pad[0xc];
    float    m10;
    float    r14, r18, r1c, r20, r24, r28, r2c, r30, r34;
    void Rotate(float a);
};
void MatX::Rotate(float a)
{
    float s = sinf(a);
    float c = cosf(a);
    float v14 = r14, v18 = r18, v1c = r1c;
    float v20 = r20, v24 = r24, v28 = r28;
    float v2c = r2c, v30 = r30, v34 = r34;
    r2c = v2c * c + v14 * s;
    r30 = v30 * c + v18 * s;
    r34 = v34 * c + v1c * s;
    flags |= 2;
    count = (uint16_t)(count + 1);
    r14 = v14 * -s + v20 * c;
    r18 = v18 * -s + v24 * c;
    r1c = v1c * -s + v28 * c;
}

// ---------------------------------------------------------------------------
// @ 0x006b9190 / @ 0x006b9230  serialize / deserialize a rotation struct
// ---------------------------------------------------------------------------
struct RotSerial {
    uint16_t flags;
    uint16_t count;
    float    m4, m8, mc, m10, m14, m18;
    uint32_t Save(void* io);
    uint32_t Load(void* io);
};
uint32_t RotSerial::Save(void* io)
{
    bool b = (m10 != 1.0f);
    if (b) flags |= 1;
    else   flags &= 0xfffe;
    uint32_t local = flags | 8;
    FUN_WriteUint16(io, &local, 1, 0);
    if (flags & 1) {
        uint32_t v = *(uint32_t*)&m10;
        FUN_WriteUint32(io, &v, 1, 0);
    }
    if (flags & 2) FUN_IO_Field1(io, &m14);
    if (flags & 4) FUN_IO_Field2(io, &m4);
    return (uint32_t)io;
}
uint32_t RotSerial::Load(void* io)
{
    (void)io;
    return 0;
}
uint32_t __cdecl FUN_006b9190(RotSerial* p, void* io) { return p->Save(io); }
uint32_t __cdecl FUN_006b9230(RotSerial* p, void* io) { return p->Load(io); }

// ---------------------------------------------------------------------------
// @ 0x006b92d0  normalize 3x3 basis
// ---------------------------------------------------------------------------
struct Basis3 {
    uint16_t f0;
    uint16_t f2;
    float    f4;
    float    f8;
    float    m10;
    float    row0[3];   // 0x14
    float    row1[3];   // 0x20
    float    row2[3];   // 0x2c
    void Normalize(const float* src);
    void Build(float* out);
};
void Basis3::Normalize(const float* src)
{
    row0[0] = src[0]; row0[1] = src[1]; row0[2] = src[2];
    row1[0] = src[4]; row1[1] = src[5]; row1[2] = src[6];
    row2[0] = src[8]; row2[1] = src[9]; row2[2] = src[10];
    f4 = src[12];
    *(float*)((char*)this + 8) = src[13];
    *(float*)((char*)this + 0xc) = src[14];
    float l0 = sqrtf(row0[0]*row0[0] + row0[1]*row0[1] + row0[2]*row0[2]);
    float l1 = sqrtf(row1[0]*row1[0] + row1[1]*row1[1] + row1[2]*row1[2]);
    float l2 = sqrtf(row2[0]*row2[0] + row2[1]*row2[1] + row2[2]*row2[2]);
    float i0 = 1.0f / l0, i1 = 1.0f / l1, i2 = 1.0f / l2;
    row0[0]*=i0; row0[1]*=i0; row0[2]*=i0;
    row1[0]*=i1; row1[1]*=i1; row1[2]*=i1;
    row2[0]*=i2; row2[1]*=i2; row2[2]*=i2;
    m10 = (l2 + l1 + l0) * 0.33333334f;
}

// ---------------------------------------------------------------------------
// @ 0x006b9440  build matrix from basis
// ---------------------------------------------------------------------------
void Basis3::Build(float* out)
{
    float s = m10;
    out[0] = row0[0] * s; out[1] = row0[1] * s; out[2] = row0[2] * s;
    out[4] = row1[0] * s; out[5] = row1[1] * s; out[6] = row1[2] * s;
    out[8] = row2[0] * s; out[9] = row2[1] * s; out[10] = row2[2] * s;
    out[12] = f4; out[13] = f8; out[14] = 1.0f;
    out[3] = 0.0f; out[7] = 0.0f; out[11] = 0.0f; out[15] = 1.0f;
}

// ---------------------------------------------------------------------------
// @ 0x006b8ca0
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_006b8ca0(uint32_t drive)
{
    if (DAT_01605ab4 == 0) {
        CBig temp;
        FUN_006b8680(&temp);
        temp.~CBig();
    }
    if (DAT_01605d34 != 0) return 0x64e4c607;
    uint32_t h = 0x811c9dc5;
    char c = FUN_006b82a0((char)drive, &h);
    return -(uint32_t)(c != 0) & h;
}

// ---------------------------------------------------------------------------
// @ 0x006b8680  SP::GetSystemInfo
// ---------------------------------------------------------------------------
void __cdecl FUN_006b8680(void* out)
{
    // full system-info construction rewrite (partial)
    (void)out;
}
