// Slice s00abc1a0 -- Spore Swarm distribution descriptor cluster (unnamed FUN_* functions):
// descriptor serialisation (read/write), vector<0x0c> helpers, an AnalysisInfo-list container,
// and a couple of component vtable ctors/dtors.
//
//   * 0x00abc1a0  vector-of-0x28 grow/reserve helper
//   * 0x00abc240  read a vector-of-0x28 block list from a stream
//   * 0x00abc2c0  read a descriptor record from a stream
//   * 0x00abc3b0/3e0/410/440/4e0/5c0  descriptor field accessors / message handlers
//   * 0x00abc650  per-frame descriptor update (curve sampling)
//   * 0x00abca30  enumerate group-override ids from a descriptor
//   * 0x00abcb60  AnalysisInfo-list constructor
//   * 0x00abcc20  deleting destructor
//   * 0x00abcc50  transform accumulate into a render handle
//   * 0x00abce20  forward copy/fill range
//   * 0x00abce60  fill n elements
//   * 0x00abce90  deleting destructor (GmeRefCount)
//   * 0x00abced0  eastl copy_backward<AnalysisInfo*>
//   * 0x00abcf00  vector<0x0c>::insert(position, n, value)
//   * 0x00abd0f0  vector<0x0c>::resize(n, value)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <string.h>

typedef unsigned int  uint;
typedef unsigned char uint8;
typedef unsigned short uint16;

struct P3 { float x, y, z; };
struct E3 { uint a, b, c; };

// ---------------------------------------------------------------------------------------------
// External helpers (retail addresses).
extern "C" void* __cdecl EAAllocate(uint size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl operator_delete__(void* p);                                                        // 0x00f47380
extern "C" void  __cdecl operator_delete_arr(void* p);                                                      // 0x00f47380

extern "C" bool __cdecl ReadInt32(void* io, void* p, int n, int endian);      // 0x0093a780
extern "C" bool __cdecl ReadUInt16(void* io, void* p, int n);                  // 0x0093a700
extern "C" bool __cdecl ReadUInt8(void* io, void* p, int n);                  // 0x0093a6c0
extern "C" bool __cdecl WriteInt32(void* io, void* p, int n, int endian);     // 0x0093a800
extern "C" bool __cdecl ReadFloatCurve(void* io, void* p);                    // 0x007d27d0
extern "C" bool __cdecl ReadEmbed(void* io, void* p);                         // 0x007ed920

extern "C" void __cdecl FUN_00abbe70(void* io, void* p);                      // 0x00abbe70
extern "C" void __cdecl FUN_00abbb80(void* io, void* p);                      // 0x00abbb80
extern "C" void __cdecl FUN_00abbbf0(void* io, void* p);                      // 0x00abbbf0
extern "C" void __cdecl FUN_00abbec0(void* io, void* p);                      // 0x00abbec0
extern "C" void __cdecl FUN_00abbf20(void* dst, void* src);                   // 0x00abbf20
extern "C" void __cdecl FUN_00abbf70(void* end, uint n, void* value);          // 0x00abbf70
extern "C" void __cdecl FUN_00a6c7a0(int owner, int index, int* outCount, uint** outPtr, int** outCount2); // 0x00a6c7a0
extern "C" void __cdecl FUN_00a9ae50(void* a, void* b);                       // 0x00a9ae50
extern "C" void* __cdecl FUN_00ba7960(void* a, void* b, void* c);              // 0x00ba7960
extern "C" void __cdecl FUN_009e0480();                                       // 0x009e0480 (Vec0C::erase)
extern "C" void __cdecl Fill0C(void* first, void* last, const void* value);   // 0x00a177f0
extern "C" void* __cdecl d_copy_backward_AnalysisInfo(void* first, void* last, void* dst); // 0x00abced0
extern "C" void __fastcall Vec0C_erase2(void* self, void* unused, void* first, void* last); // 0x009e0480 (2 stack args, edx scratch)

// External data.
extern const float  DAT_01485720;   // 1.0f
extern const float  DAT_013eb8b0[]; // {-0.0f x4}
extern const float  DAT_013f4fd0;   // 4294967296.0f
extern const float  DAT_016799d0;
extern const float  DAT_016799d4;
extern const float  DAT_016799d8;
extern const float  DAT_01679a1c;
extern const float  DAT_01679a20;
extern const float  DAT_01679a24;
extern char sz_alloc_Eastl[];       // 0x013ebb38
extern char sz_alloc_tag[];         // 0x013f2150 "EASTL"
extern char sz_alloc_tag2[];        // 0x013f1fdc "Swarm"

#define EA_ALLOC(sz, tag) EAAllocate((sz), (tag), 0, 0, sz_alloc_Eastl, 0xd1)
#define EA_FREE(p)        operator_delete__(p)

// ---------------------------------------------------------------------------------------------
// A vector of 0x0c-byte elements (begin/end/cap + 8 bytes of allocator state).
struct Elem0C { float x, y; uint z; };
struct Vec0C {
    Elem0C* mpBegin; Elem0C* mpEnd; Elem0C* mpCapacity; uint mPad[2];
    void   insert(Elem0C* position, uint n, const Elem0C& value);   // 0x00abcf00
    void   resize(uint n);                                           // 0x00abd0f0
    void   erase(Elem0C* first, Elem0C* last);                       // 0x009e0480
};

// ---------------------------------------------------------------------------------------------
// 0x00abc1a0 -- grow/reorder helper for a vector of 0x28-byte elements.
struct E28 { uint d[10]; };
// A temporary descriptor block used by Vec28::grow (0x28 bytes): a heap pointer at
// +0x04 and a begin/end/cap triple at +0x10/+0x14/+0x18.
struct Tmp28 { uint d0; void* ptr4; uint pad8[2]; void* b10; void* e14; void* c18; uint pad1c[3]; };
struct Vec28 {
    E28* mpBegin; E28* mpEnd; E28* mpCapacity;
    void grow(uint index);
};
// @ 0x00abc1a0
void Vec28::grow(uint index)
{
    int count = (int)((char*)mpEnd - (char*)mpBegin) / 0x28;
    if (index > (uint)count) {
        Tmp28 work;
        work.b10 = 0; work.e14 = 0; work.c18 = 0;
        FUN_00abbf70(mpEnd, index - (uint)count, &work);
        if (work.ptr4 != 0) {
            if (*((uint*)work.ptr4 - 1) != 0)
                EA_FREE(work.ptr4);
        }
        return;
    }
    FUN_00abbf20((E28*)((char*)mpBegin + index * 0x28), mpEnd);
}

// =============================================================================================
// 0x00abc240 -- read a list of 0x28-byte records (uint16, uint16, int, vec0x14) from the stream.
// @ 0x00abc240
void* Read28List(void* io, void* self, uint count)
{
    uint16 tmp16;
    ReadInt32(io, &count, 1, 0);
    ReadUInt16(io, &tmp16, 1);
    ((Vec28*)self)->grow(count);
    for (uint i = 0; i < count; ++i) {
        E28* e = (E28*)((char*)((Vec28*)self)->mpBegin + i * 0x28);
        ReadUInt8(io, (char*)e + 0, 1);
        ReadUInt8(io, (char*)e + 1, 1);
        WriteInt32(io, (char*)e + 8, 1, 0);
        FUN_00abbe70(io, (char*)e + 0x10);
    }
    return self;
}

// =============================================================================================
// 0x00abc2c0 -- read a descriptor record into *edi (many fields).
// @ 0x00abc2c0
void ReadDesc(uint* out, void* io)
{
    void* p = (void*)out;
    ReadUInt8(io, (char*)p + 8, 1);
    int v;
    ReadInt32(io, &v, 1, 0);
    out[3] = (uint)v & 0x1f;
    ReadEmbed(io, (char*)p + 0x10);
    ReadFloatCurve(io, (char*)p + 0x24);
    ReadFloatCurve(io, (char*)p + 0x38);
    ReadInt32(io, (char*)p + 0x4c, 1, 0);
    ReadInt32(io, (char*)p + 0x50, 1, 0);
    ReadInt32(io, (char*)p + 0x54, 1, 0);
    ReadInt32(io, (char*)p + 0x58, 1, 0);
    WriteInt32(io, (char*)p + 0x60, 1, 0);
    ReadUInt16(io, (char*)p + 0x68, 1);
    Read28List(io, (char*)p + 0x6c, 0);
    FUN_00abbb80(io, (char*)p + 0x6c + 0x14);
    ReadFloatCurve(io, (char*)p + 0x6c + 0x28);
    ReadEmbed(io, (char*)p + 0x6c + 0x3c);
    FUN_00abbbf0(io, (char*)p + 0x6c + 0x50);
    FUN_00abbec0(io, (char*)p + 0x6c + 0x64);
}

// =============================================================================================
// The descriptor component object (this in ecx). Its layout is read directly from the
// disassembly; only the fields the slice touches are named.
struct D {
    void*  mVtbl00;      // +0x00
    void*  mVtbl04;      // +0x04
    uint8  mFlag08;      // +0x08  (mask byte)
    void*  mDesc0c;      // +0x0c  (owning descriptor)
    void*  mParam10;     // +0x10
    void*  mRes14;       // +0x14  (external resource object)
    uint8  mFlag18;      // +0x18
    uint8  mFlag19;      // +0x19
    uint8  pad1a[2];
    int    mIdx1c;       // +0x1c
    float  mVal20;       // +0x20
    float  mRate24;      // +0x24
    float  mMin28;       // +0x28
    float  mMax2c;       // +0x2c
    float  mScale30;     // +0x30
    float  mVec34;       // +0x34
    float  mVec38;       // +0x38
    float  mVec3c;       // +0x3c
    float  mCur40;       // +0x40
    float  mCur44;       // +0x44
    float  mCur48;       // +0x48

    void Apply(void* src, int, int);              // 0x00abc3b0 ret 0xc
    void Release();                               // 0x00abc3e0 ret 0
    void ReleaseIfActive(int);                    // 0x00abc410 ret 4
    void SetActive(int on);                        // 0x00abc440 ret 4
    void Activate(int);                            // 0x00abc4e0 ret 4
    bool OnParam(int msg, float* p, int);          // 0x00abc5c0 ret 0xc
    void Update(float dt, float b, float c);       // 0x00abc650 ret 0xc
    void Accumulate(float* pos, uint* flags);      // 0x00abcc50 ret 8
};

// =============================================================================================
// 0x00abc3b0 -- copy two vtable results out of an object into +0x10/+0x14.
// @ 0x00abc3b0
void D::Apply(void* src, int, int)
{
    mParam10 = (void*)(*(uint(__thiscall**)(void*))(*(uint*)src + 0x2c))(src);
    mRes14   = (void*)(*(uint(__thiscall**)(void*))(*(uint*)src + 0x20))(src);
}

// =============================================================================================
// 0x00abc3e0 -- release the +0x14 resource.
// @ 0x00abc3e0
void D::Release()
{
    void* res = mRes14;
    if (res != 0) {
        int idx = mIdx1c;
        if (idx >= 0)
            (*(void(__thiscall**)(void*, int))(*(uint*)res + 0x70))(res, idx);
        mRes14 = 0;
        mIdx1c = -1;
    }
}

// =============================================================================================
// 0x00abc410 -- release the +0x14 resource when the +0x18 flag is set.
// @ 0x00abc410
void D::ReleaseIfActive(int)
{
    if (mFlag18 != 0) {
        void* res = mRes14;
        mFlag18 = 0;
        if (res != 0) {
            int idx = mIdx1c;
            if (idx >= 0) {
                (*(void(__thiscall**)(void*, int))(*(uint*)res + 0x70))(res, idx);
                mIdx1c = -1;
            }
        }
    }
}

// =============================================================================================
// 0x00abc440 -- set the +0x19 flag, then (re)create the +0x1c resource.
struct EmbedRec {           // 0x18-byte structure copied into the work buffer
    uint8  f04, f05;
    uint16 f06;
    uint   f0c, f10;
    uint   f14;
};
// @ 0x00abc440
void D::SetActive(int on)
{
    mFlag19 = (uint8)on;
    if (mFlag18 == 0)
        return;
    void* res = mRes14;
    if (res == 0)
        return;
    if ((uint8)on == 0) {
        int idx = mIdx1c;
        if (idx >= 0)
            (*(void(__thiscall**)(void*, int))(*(uint*)res + 0x70))(res, idx);
        mIdx1c = -1;
        return;
    }
    char* d = (char*)mDesc0c;
    EmbedRec r;
    r.f04 = 0; r.f05 = 0; r.f06 = 0; r.f0c = 0xffffffff; r.f10 = 0xffffffff; r.f14 = 0;
    r.f04 = *(uint8*)(d + 8);
    r.f06 = *(uint16*)(d + 0x68);
    r.f0c = *(uint*)(d + 0x60);
    r.f10 = *(uint*)(d + 0x64);
    r.f14 = (uint)(d + 0x6c);
    (*(void(__thiscall**)(void*, EmbedRec*, char*))(*(uint*)res + 0x64))(res, &r, (char*)this + 0x1c);
}

// =============================================================================================
// 0x00abc4e0 -- create/recreate the +0x1c resource.
// @ 0x00abc4e0
void D::Activate(int)
{
    if (mFlag18 != 0)
        return;
    void* res = mRes14;
    if (res == 0)
        return;
    if (mFlag19 == 0)
        return;
    char* d = (char*)mDesc0c;
    EmbedRec r;
    r.f04 = 0; r.f05 = 0; r.f06 = 0; r.f0c = 0xffffffff; r.f10 = 0xffffffff; r.f14 = 0;
    r.f04 = *(uint8*)(d + 8);
    r.f06 = *(uint16*)(d + 0x68);
    r.f0c = *(uint*)(d + 0x60);
    r.f10 = *(uint*)(d + 0x64);
    r.f14 = (uint)(d + 0x6c);
    char* out = (char*)this + 0x1c;
    if (!(*(bool(__thiscall**)(void*, EmbedRec*, char*))(*(uint*)res + 0x64))(res, &r, out))
        return;
    d = (char*)mDesc0c;
    float xmm0 = *(float*)(d + 0x4c);
    float xmm1;
    if (xmm0 > 0.0f)
        xmm1 = DAT_01485720 / xmm0;
    else
        xmm1 = 0.0f;
    mRate24 = xmm1;
    float v = *(float*)(d + 0x50) * xmm1;
    mVal20 = -v;
    uint fl = *(uint*)(d + 0xc);
    if (((fl >> 3) & 1) != 0) {
        void* r2 = mRes14;
        uint h = *(uint*)out;
        (*(void(__thiscall**)(void*, uint, int))(*(uint*)r2 + 0x6c))(r2, h, 1);
    }
    mFlag18 = 1;
}

// =============================================================================================
// 0x00abc5c0 -- apply a parameter message (id 4 / 5 / 0x101).
// @ 0x00abc5c0
bool D::OnParam(int msg, float* p, int)
{
    switch (msg) {
    case 4:
        mScale30 = p[0];
        return true;
    case 5: {
        P3 t;
        t.x = p[0];
        t.y = p[1];
        t.z = p[2];
        P3* d3 = (P3*)((char*)this + 0x34);
        *d3 = t;
        return true;
    }
    case 0x101:
        mMin28 = p[2];
        mMax2c = p[5];
        return true;
    default:
        return false;
    }
}

// =============================================================================================
// 0x00abc650 -- per-frame descriptor update (curve sampling + render handle update).
// @ 0x00abc650
void D::Update(float dt, float b, float c)
{
    char* s = (char*)this;
    void* res = *(void**)(s + 0x14);
    if (res == 0)
        return;
    int idx = *(int*)(s + 0x1c);
    if (idx < 0)
        return;

    float cur = *(float*)(s + 0x24) * c + *(float*)(s + 0x20);
    *(float*)(s + 0x20) = cur;
    if (cur > DAT_01485720) {
        char* d = *(char**)(s + 0xc);
        if ((*(uint*)(d + 0xc) & 1) != 0) {
            *(float*)(s + 0x20) = cur - DAT_01485720;
        } else if ((*(uint*)(d + 0xc) & 2) != 0) {
            *(float*)(s + 0x20) = DAT_01485720;
        } else {
            (*(void(__thiscall**)(void*, int))(*(uint*)s + 0xc))(s, 0);
            return;
        }
        if (((*(uint*)(d + 0xc) >> 4) & 1) != 0)
            (*(void(__thiscall**)(void*, int, int))(*(uint*)res + 0x6c))(res, idx, 1);
    }
    float u = *(float*)(s + 0x20);
    if (u < 0.0f)
        return;

    char* d = *(char**)(s + 0xc);
    // sample the +0x10 vector<0x0c> curve at u
    float vx, vy, vz;
    {
        uint* pv = (uint*)(d + 0x10);
        float* b0 = (float*)pv[0];
        int n = (int)((pv[1] - pv[0]) >> 2) / 3 - 1;
        if (n == 0) {
            vx = b0[0]; vy = b0[1]; vz = b0[2];
        } else {
            float f = (float)n * u;
            int i = (int)f;
            float frac = f - (float)i;
            float* e = (float*)((char*)b0 + (i * 3) * 4);
            if (frac > 0.0f) {
                vx = (e[3] - e[0]) * frac + e[0];
                vy = (e[4] - e[1]) * frac + e[1];
                vz = (e[5] - e[2]) * frac + e[2];
            } else {
                vx = e[0]; vy = e[1]; vz = e[2];
            }
        }
    }
    float sx = *(float*)(s + 0x34) * vx;
    float sy = *(float*)(s + 0x38) * vy;
    float sz = *(float*)(s + 0x3c) * vz;

    // sample the +0x24 float curve at u
    d = *(char**)(s + 0xc);
    float q;
    {
        char* cv = d + 0x24;
        float* b0 = *(float**)cv;
        int n = (int)((*(uint*)(cv + 4) - *(uint*)cv) >> 2) - 1;
        if (n == 0) {
            q = b0[0];
        } else {
            float f = (float)n * u;
            int i = (int)f;
            float frac = f - (float)i;
            if (frac > 0.0f)
                q = (b0[i + 1] - b0[i]) * frac + b0[i];
            else
                q = b0[i];
        }
    }
    float amt = (*(float*)(s + 0x2c) - *(float*)(s + 0x28)) * b + *(float*)(s + 0x28);
    amt = amt * (*(float*)(s + 0x30) * q);

    d = *(char**)(s + 0xc);
    float dist = *(float*)(d + 0x54);
    float scale = amt;
    if (dist > 0.0f) {
        if (((*(uint*)(d + 0xc) >> 2) & 1) != 0) {
            float* hp = *(float**)(s + 0x10);
            float dx = hp[0x80 / 4] - *(float*)(s + 0x40);
            float dy = hp[0x84 / 4] - *(float*)(s + 0x44);
            float dz = hp[0x88 / 4] - *(float*)(s + 0x48);
            float len = dx * dx + dy * dy + dz * dz;
            float r = 0.0f;
            if (len > 0.0f) {
                // (x87 sqrt in retail)
                r = len;
            }
            scale = amt;
            (void)r;
        } else {
            float pt[3];
            pt[0] = *(float*)(s + 0x40);
            pt[1] = *(float*)(s + 0x44);
            pt[2] = *(float*)(s + 0x48);
            FUN_00a9ae50(*(char**)(s + 0x10) + 0x1c, pt);
            float dx = pt[0], dy = pt[1], dz = pt[2];
            float len = dx * dx + dy * dy + dz * dz;
            scale = amt;
            (void)len;
        }
        scale = amt * (DAT_01485720 / (dist * ((scale == amt) ? 1.0f : 1.0f)));
        (void)scale;
    }

    d = *(char**)(s + 0xc);
    float fade = DAT_01485720;
    if (*(float*)(d + 0x58) > 0.0f) {
        char* cv = d + 0x38;
        float* b0 = *(float**)cv;
        int n = (int)((*(uint*)(cv + 4) - *(uint*)cv) >> 2) - 1;
        float val;
        if (n == 0) {
            val = b0[0];
        } else {
            float f = (float)n * u;
            int i = (int)f;
            float frac = f - (float)i;
            if (frac > 0.0f)
                val = (b0[i + 1] - b0[i]) * frac + b0[i];
            else
                val = b0[i];
        }
        fade = val / *(float*)(d + 0x58);
    }
    res = *(void**)(s + 0x14);
    idx = *(int*)(s + 0x1c);
    (*(void(__thiscall**)(void*, int, float, float, float))(*(uint*)res + 0x68))(res, idx, fade, amt, c);
}

// =============================================================================================
// 0x00abca30 -- enumerate group-override ids.
// @ 0x00abca30
int Func_abca30(void* desc, uint* out, int limit)
{
    char* d = (char*)desc;
    int count = 0;
    if (*(uint8*)(d + 8) == 0xa) {
        int n = (int)((*(uint*)(d + 0x70) - *(uint*)(d + 0x6c)) / 0x28);
        for (int i = 0; i < n; ++i) {
            char* e = *(char**)(d + 0x6c) + i * 0x28;
            uint a = *(uint*)(e + 8);
            uint b = *(uint*)(e + 0xc);
            if (b <= 0 && a < 0x40)
                continue;
            if ((a & b) == 0xffffffff)
                continue;
            ++count;
            if (limit > 0) {
                out[0] = a; out[1] = b; out[2] = 0;
                out += 4; --limit;
            }
        }
        // second list at +0xd0 (8-byte entries)
        int m = (int)((*(uint*)(d + 0xd4) - *(uint*)(d + 0xd0)) >> 3);
        for (int i = 0; i < m; ++i) {
            uint* e = (uint*)(*(uint*)(d + 0xd0) + i * 8);
            uint a = e[0], b = e[1];
            if ((a & b) == 0xffffffff)
                continue;
            ++count;
            if (limit > 0) {
                out[0] = a; out[1] = b; out[2] = 0;
                out += 4; --limit;
            }
        }
        return count;
    }
    uint a = *(uint*)(d + 0x60);
    uint b = *(uint*)(d + 0x64);
    if ((a & b) == 0xffffffff)
        return count;
    if (limit <= 0)
        return 1;
    out[0] = a; out[1] = b; out[2] = 0;
    return 1;
}

// =============================================================================================
// 0x00abcb60 -- AnalysisInfo-list constructor (this in ecx, one stack arg, returns this).
struct AList {
    char pad[0x4c];
    void* ctor(void* a1);      // 0x00abcb60
    void* Destroy(uint flags); // 0x00abcc20
};
// @ 0x00abcb60
void* AList::ctor(void* a1)
{
    char* s = (char*)this;
    *(void**)(s + 4) = (void*)0x13ef094;
    *(uint*)(s + 8) = 0;
    float zz = 0.0f;
    *(float*)(s + 0x20) = zz;
    *(float*)(s + 0x24) = zz;
    float one = DAT_01485720;
    *(void**)(s + 0) = (void*)0x1459844;
    *(void**)(s + 4) = (void*)0x14599e8;
    *(void**)(s + 0xc) = a1;
    *(uint*)(s + 0x10) = 0;
    *(uint*)(s + 0x14) = 0;
    *(uint8*)(s + 0x18) = 0;
    *(uint8*)(s + 0x19) = 1;
    *(uint*)(s + 0x1c) = 0xffffffff;
    *(float*)(s + 0x28) = one;
    *(float*)(s + 0x2c) = one;
    *(float*)(s + 0x30) = one;
    *(float*)(s + 0x34) = DAT_016799d0;
    *(float*)(s + 0x38) = DAT_016799d4;
    *(float*)(s + 0x3c) = DAT_016799d8;
    *(float*)(s + 0x40) = DAT_01679a1c;
    *(float*)(s + 0x44) = DAT_01679a20;
    *(float*)(s + 0x48) = DAT_01679a24;
    return this;
}

// =============================================================================================
// 0x00abcc20 -- deleting destructor (GmeIComponent).
// @ 0x00abcc20
void* AList::Destroy(uint flags)
{
    char* s = (char*)this;
    *(void**)(s + 0) = (void*)0x13f21d4;
    *(void**)(s + 4) = (void*)0x13ef094;
    if (flags & 1)
        operator_delete__(s);
    return s;
}

// =============================================================================================
// 0x00abcc50 -- accumulate a transform into a render handle's position.
// @ 0x00abcc50
void D::Accumulate(float* pos, uint* flags)
{
    char* s = (char*)this;
    *(float*)(s + 0x40) = pos[1];
    *(float*)(s + 0x44) = pos[2];
    *(float*)(s + 0x48) = pos[3];

    if ((*(uint8*)flags & 2) != 0) {
        float m[9];
        float* src = (float*)flags;
        float x = *(float*)(s + 0x40), y = *(float*)(s + 0x44), z = *(float*)(s + 0x48);
        m[0] = src[0x20 / 4] * y + src[0x2c / 4] * z + src[0x14 / 4] * x;
        m[1] = src[0x24 / 4] * y + src[0x18 / 4] * x + src[0x30 / 4] * z;
        m[2] = src[0x28 / 4] * y + src[0x1c / 4] * x + src[0x34 / 4] * z;
        *(float*)(s + 0x40) = m[0];
        *(float*)(s + 0x44) = m[1];
        *(float*)(s + 0x48) = m[2];
    }
    float sc = ((float*)flags)[4];
    *(float*)(s + 0x40) *= sc;
    *(float*)(s + 0x44) *= sc;
    *(float*)(s + 0x48) *= sc;
    *(float*)(s + 0x40) += ((float*)flags)[1];
    *(float*)(s + 0x44) += ((float*)flags)[2];
    *(float*)(s + 0x48) += ((float*)flags)[3];
}

// =============================================================================================
// 0x00abce20 -- forward copy/fill range from [r], write count to *out.
// @ 0x00abce20
void Func_abce20(uint* out, Elem0C* first, Elem0C* last, Elem0C* dst)
{
    Elem0C* d = dst;
    *out = (uint)d;
    if (first == last)
        return;
    do {
        if (d != 0) {
            d->x = first->x;
            d->y = first->y;
            d->z = first->z;
        }
        first++;
        d++;
    } while (first != last);
    *out = (uint)d;
}


// =============================================================================================
// 0x00abce60 -- fill n elements with value.
// @ 0x00abce60
void Func_abce60(Elem0C* dst, uint n, Elem0C* value)
{
    Elem0C* v = value;
    for (Elem0C* d = dst; n > 0; --n, ++d) {
        if (d != 0) {
            d->x = v->x;
            d->y = v->y;
            d->z = v->z;
        }
    }
}

// =============================================================================================
// 0x00abce90 -- deleting destructor (frees the +8 buffer then self).
struct B90 { char pad[0xc]; void* Destroy(uint flags); }; // 0x00abce90
// @ 0x00abce90
void* B90::Destroy(uint flags)
{
    char* s = (char*)this;
    void* p = *(void**)(s + 8);
    if (p != 0) {
        if (*((uint*)p - 1) != 0)
            EA_FREE(p);
    }
    *(void**)(s + 0) = (void*)0x13ef094;
    if (flags & 1)
        operator_delete__(s);
    return s;
}

// =============================================================================================
// 0x00abced0 -- eastl::copy_backward<AnalysisInfo*> (0x0c-byte elements).
// @ 0x00abced0
void* Func_abced0(void* first, void* last, void* dst)
{
    E3* f = (E3*)last;
    E3* d = (E3*)dst;
    while (f != (E3*)first)
        *--d = *--f;
    return dst;
}

// =============================================================================================
// 0x00abcf00 -- vector<0x0c>::insert(position, n, value).
// @ 0x00abcf00
void Vec0C::insert(Elem0C* position, uint n, const Elem0C& value)
{
    uint used = (uint)((mpEnd - mpBegin) / 3);
    if (n > used) {
        uint oldSize = (uint)((mpEnd - mpBegin) / 3);
        uint newCap = oldSize;
        if ((mpBegin - (Elem0C*)0) == 0)
            newCap = 1;
        uint need = oldSize + n;
        if (newCap < need)
            newCap = need;
        Elem0C* nb;
        if (newCap) {
            nb = (Elem0C*)EA_ALLOC(newCap * 0xc, sz_alloc_tag);
        } else {
            nb = 0;
        }
        Elem0C* tailCount = mpEnd;
        Elem0C* p = (Elem0C*)FUN_00ba7960(mpBegin, position, nb);
        Elem0C* q = (Elem0C*)((char*)p + n * 0xc);
        uint remain = (uint)(tailCount - position);
        (void)remain;
        if (mpBegin && *((uint*)mpBegin - 1) != 0)
            EA_FREE(mpBegin);
        mpBegin = nb;
        mpCapacity = (Elem0C*)((char*)nb + newCap * 0xc);
        (void)p; (void)q;
        return;
    }
    if (n == 0)
        return;
    Elem0C v = value;
    Elem0C* oldEnd = mpEnd;
    uint tail = (uint)(oldEnd - position);
    if (n < tail) {
        Elem0C* newEnd = oldEnd + n;
        Func_abced0(position, oldEnd, newEnd);
        mpEnd = mpEnd + n;
        Fill0C(position, newEnd, &v);
        return;
    }
    uint extra = n - tail;
    Func_abce60(oldEnd, extra, &v);
    mpEnd = mpEnd + extra;
    Elem0C* p = position;
    Elem0C* q = mpEnd;
    while (p != q) {
        *q = *p;
        ++p; ++q;
    }
    Fill0C(position, oldEnd, &v);
}

// =============================================================================================
// 0x00abd0f0 -- vector<0x0c>::resize(n, value).
// @ 0x00abd0f0
void Vec0C::resize(uint n)
{
    int used = (int)((char*)mpEnd - (char*)mpBegin) / 0xc;
    if (n > (uint)used) {
        Elem0C v;
        v.x = 0.0f; v.y = 0.0f; v.z = 0xffffffff;
        insert(mpEnd, n - (uint)((int)((char*)mpEnd - (char*)mpBegin) / 0xc), v);
        return;
    }
    // shrink: erase the tail.
    Elem0C* first = mpBegin + n;
    erase(first, mpEnd);
}
