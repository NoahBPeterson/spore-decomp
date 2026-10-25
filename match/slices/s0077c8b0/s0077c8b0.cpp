// Slice s0077c8b0: RenderWare shader-constant helpers / small containers (region 0x77c8b0-0x77d7f0).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <string.h>
#include <intrin.h>
#include <xmmintrin.h>

// ---- D3D9 device -------------------------------------------------------------------------
extern void* g_pDevice;   // 0x16f89d0
struct D3D9Vtbl { void* slots[112]; };
typedef void (__stdcall *PFN_SetConstF)(void* self, unsigned reg, const float* data, unsigned count);
#define SETVS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[94]))((dev), (reg), (data), (n)))
#define SETPS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[109]))((dev), (reg), (data), (n)))

extern void* FUN_011f1120();
extern float  g_one;                        // 0x1485720

// 0x00777ae0  shader-constant dirty/notify helper. The last argument is a by-value 1-byte tag
// (only its low byte is read): retail passes the flag dword straight off its stack slot, so the
// upper three bytes are leftovers, and they must not be part of the compare.
struct ChangedFlag { unsigned char value; };
void __cdecl FUN_00777ae0(int code, void* obj, ChangedFlag changed);

// @ 0x0077c970
struct GfxConst {
    void FUN_0077c970(float a, float b, float c, float d);
    void FUN_0077ca20(unsigned idx, float a, float b, float c, float d);
    int  FUN_0077cad0(short id);
    int  FUN_0077cb10(unsigned a, unsigned b);
};

struct ImgElt { void GetImageResource(unsigned arg); };  // 0x00576650

void GfxConst::FUN_0077c970(float a, float b, float c, float d) {
    float* p = (float*)this;
    bool changed = false;
    if (p[0] != a || p[1] != b || p[2] != c || p[3] != d)
        changed = true;
    p[0] = a;
    p[1] = b;
    p[2] = c;
    p[3] = d;
    ChangedFlag cf;
    cf.value = changed ? 1 : 0;
    FUN_00777ae0(0x20c, this, cf);
}

// @ 0x0077ca20
void GfxConst::FUN_0077ca20(unsigned idx, float a, float b, float c, float d) {
    float* q = (float*)((char*)this + (idx & 0xffff) * 0x10);
    bool changed = false;
    if (q[0] != a || q[1] != b || q[2] != c || q[3] != d)
        changed = true;
    q[0] = a;
    q[1] = b;
    q[2] = c;
    q[3] = d;
    ChangedFlag cf;
    cf.value = changed ? 1 : 0;
    FUN_00777ae0(0x206, this, cf);
}

// @ 0x0077cad0
int GfxConst::FUN_0077cad0(short id) {
    int n = (*(int*)((char*)this + 0xc) - *(int*)((char*)this + 8)) >> 2;
    if (n > 0) {
        int* q = *(int**)((char*)this + 8);
        int i = 0;
        do {
            if (*(short*)(*q + 4) == id)
                return i;
            ++i;
            ++q;
        } while (i < n);
    }
    return -1;
}

// @ 0x0077cb10
int GfxConst::FUN_0077cb10(unsigned a, unsigned b) {
    int n1 = *(int*)((char*)this + 0xc) + 1;
    char* elem = (char*)this + n1 * 0x10;
    *(unsigned*)elem = a;
    ((ImgElt*)(elem + 4))->GetImageResource(b);
    *(int*)((char*)this + 0xc) += 1;
    return *(int*)((char*)this + 0xc) - 1;
}

// ---- global shader-constant sources ------------------------------------------------------
extern int*   g_16f6f00;   // 0x16f6f00
extern float* g_16f6e60;   // 0x16f6e60
extern void*  g_16f6ebc;   // 0x16f6ebc
extern void*  g_16f6e64;   // 0x16f6e64
extern float* g_16f6ec8;   // 0x16f6ec8
extern void*  g_16f6dd0;   // 0x16f6dd0
extern float* g_lights0;   // 0x16f8914
extern float  g_1632e28, g_1632e2c, g_1632e30, g_1632e34;  // 0x1632e28

// @ 0x0077c8b0  normalized camera direction + distance
void __cdecl FUN_0077c8b0(unsigned reg, unsigned p2, int isVS) {
    if (g_16f6f00 == 0)
        return;
    int obj = (int)FUN_011f1120();
    float x = *(float*)(obj + 0x30);
    float y = *(float*)(obj + 0x34);
    float z = *(float*)(obj + 0x38);
    float len2 = x * x + (y * y + z * z);
    float inv = 1.0f / (float)sqrt(len2 + 1e-08f);
    float len = (float)sqrt(len2);
    float v[4];
    v[0] = x * inv;
    v[1] = y * inv;
    v[2] = z * inv;
    v[3] = len;
    if (isVS)
        SETVS(g_pDevice, reg, v, 1);
    else
        SETPS(g_pDevice, reg, v, 1);
}

// @ 0x0077d130
float* __fastcall FUN_0077d130(float* p) {
    p[0] = g_1632e28;
    p[1] = g_1632e2c;
    p[2] = g_1632e30;
    p[3] = g_1632e34;
    return p;
}

// @ 0x0077d170
float* __fastcall FUN_0077d170(float* p) {
    __m128 z = _mm_setzero_ps();
    _mm_store_ss(p + 0, z);
    _mm_store_ss(p + 4, z);
    _mm_store_ss(p + 1, z);
    _mm_store_ss(p + 2, z);
    _mm_store_ss(p + 3, z);
    _mm_store_ss(p + 5, z);
    _mm_store_ss(p + 6, z);
    _mm_store_ss(p + 7, z);
    _mm_store_ss(p + 8, z);
    _mm_store_ss(p + 9, z);
    _mm_store_ss(p + 10, z);
    _mm_store_ss(p + 11, z);
    _mm_store_ss(p + 12, z);
    _mm_store_ss(p + 13, z);
    _mm_store_ss(p + 14, z);
    _mm_store_ss(p + 15, z);
    return p;
}

// ---- remaining slice-53 functions (see nonmatching.txt / partial.txt) --------------------

extern void* g_vtbl_13ef094;  // 0x13ef094
extern void* g_vtbl_140e878;  // 0x140e878

// @ 0x0077d1d0  constructor: install vftable, clear refcount (atomic), install final vftable;
// returns 'this' (the original leaves ecx copied to eax for the caller at 0x40bc5e).
struct CtorObj { void* vtbl; volatile long refcount; int field2; int field3; int field4; };
CtorObj* __fastcall FUN_0077d1d0(CtorObj* p) {
    p->vtbl = &g_vtbl_13ef094;
    _InterlockedExchange(&p->refcount, 0);
    p->vtbl = &g_vtbl_140e878;
    p->field2 = 0;
    p->field3 = 0;
    p->field4 = 0;
    return p;
}

// ---- allocator / container helpers --------------------------------------------------------
extern "C" void* __cdecl FUN_00f473d0(unsigned size, unsigned align, unsigned a, const char* name,
                                      unsigned b, unsigned c, const char* file, unsigned line); // 0x00f473d0
extern "C" void* __cdecl FUN_00f473a0(unsigned size, const char* name, int a, int b,
                                      const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl FUN_00f47380(void* p); // 0x00f47380
extern const char kAllocName[]; // 0x013eb8a4  "Graphics"
extern const char kAllocFile[]; // 0x013ebb38  ".../EASTL/allocator.h"

extern "C" void* __cdecl FUN_00706ab0(const void* first, const void* last, void* dst);      // 0x00706ab0
extern "C" void* __cdecl FUN_0047c1c0(const void* first, const void* last, void* dest);     // 0x0047c1c0
extern "C" void  __cdecl FUN_0047cae0(void* dst, unsigned n, const void* value, void* pos);  // 0x0047cae0
extern "C" void  __cdecl FUN_0047a500(void** out, const void* first, const void* last,
                                      void* dest, const void* pos);                          // 0x0047a500
extern "C" void  __cdecl FUN_00edba80(void* first, void* last, void* destEnd);              // 0x00edba80
extern "C" void  __cdecl FUN_00898580(void* dst, const void* last, const void* value);       // 0x00898580

extern "C" void  __cdecl FUN_011fca60(float* out, const float* in);                         // 0x011fca60
extern "C" void  __cdecl FUN_0045eac0(void* out, const void* in, void* parent);             // 0x0045eac0
extern "C" void  __fastcall FUN_007779e0(void* self, void* unused, void* dst);               // 0x007779e0
extern "C" void* __fastcall FUN_0040d010(void* self, void* unused);                          // 0x0040d010
extern void* g_16f85ac; // 0x16f85ac

// ---- 0x0077cb40 fadeDistance -------------------------------------------------------------
// Reads the current fade vector, then:
//   w == 0    -> pick the lit (3,3,2,1) or shadowed (0.3,0.3,0.3,1) colour from the first light
//   w == 0.5  -> take the global distance
//   otherwise -> fade the colour by the camera-to-object distance against the range
//                (global[1], global[2]) and scale by global[0].
// @ 0x0077cb40
void __cdecl FUN_0077cb40(unsigned reg, unsigned p2, int isVS) {
    float v[4];
    v[0] = g_16f6e60[0];
    v[1] = g_16f6e60[1];
    v[2] = g_16f6e60[2];
    v[3] = g_16f6e60[3];
    float* fade = (float*)g_16f6ebc;
    if (v[3] == 0.0f) {
        float lit[4];
        lit[0] = 3.0f;
        lit[1] = 3.0f;
        lit[2] = 2.0f;
        lit[3] = 1.0f;
        float shadow[4];
        shadow[0] = 0.3f;
        shadow[1] = 0.3f;
        shadow[2] = 0.3f;
        shadow[3] = 1.0f;
        float in[4];
        in[0] = g_lights0[8];
        in[1] = g_lights0[9];
        in[2] = g_lights0[10];
        in[3] = g_lights0[11];
        float out[4];
        FUN_011fca60(out, in);
        if (out[2] <= 0.2f) {
            v[0] = shadow[0];
            v[1] = shadow[1];
            v[2] = shadow[2];
            v[3] = shadow[3];
        } else {
            v[0] = lit[0];
            v[1] = lit[1];
            v[2] = lit[2];
            v[3] = lit[3];
        }
    } else if (v[3] == 0.5f) {
        v[3] = fade ? fade[0] : 1.0f;
    } else if (fade) {
        float m[16];
        FUN_007779e0(FUN_011f1120(), 0, m);
        float dist = (float)sqrt(m[12] * m[12] + (m[13] * m[13] + m[14] * m[14]));
        float k = (dist - fade[1]) / (fade[2] - fade[1]);
        k = k < 0.0f ? 0.0f : k;
        k = k > 1.0f ? 1.0f : k;
        v[3] = (k * 0.975f + 0.025f) * fade[0];
    } else {
        v[3] = 1.0f;
    }
    if (isVS)
        SETVS(g_pDevice, reg, v, 1);
    else
        SETPS(g_pDevice, reg, v, 1);
}

// ---- 0x0077cd50 interpProbe --------------------------------------------------------------
// Samples the probe ring at t = time * rate.  Without interpolation the live entry is uploaded
// directly; with interpolation the two neighbouring entries are lerped over all 0x110 bytes.
static __forceinline int FloorToInt(float x) {
    int i = _mm_cvtss_si32(_mm_set_ss(x));
    if (x < (float)i)
        --i;
    return i;
}
static __forceinline int CeilToInt(float x) {
    int i = _mm_cvtss_si32(_mm_set_ss(x));
    if ((float)i < x)
        ++i;
    return i;
}
// @ 0x0077cd50
void __cdecl FUN_0077cd50(unsigned reg, unsigned count, int isVS) {
    int* base = (int*)g_16f6e64;
    if (base == 0)
        return;
    int n = base[0];
    float t = (float)base[1] * *g_16f6ec8;
    int i0 = FloorToInt(t);
    float* cur = (float*)((char*)base + 0xc + (i0 % n) * 0x110);
    const float* data = cur;
    float lerped[4 * 16 + 4];
    if (((unsigned char*)base)[8]) {
        int i1 = CeilToInt(t);
        const float* next = (const float*)((char*)base + 0xc + (i1 % n) * 0x110);
        float frac = t - (float)i0;
        float inv = 1.0f - frac;
        for (int i = 0; i < 4 * 16 + 4; ++i)
            lerped[i] = cur[i] * inv + next[i] * frac;
        data = lerped;
    }
    if (isVS)
        SETVS(g_pDevice, reg, data, count);
    else
        SETPS(g_pDevice, reg, data, count);
}

// ---- 0x0077d200 transformBasis -----------------------------------------------------------
// Expands the active Matrix44Affine to a full affine 4x4, concatenates the object transform,
// transposes the first three columns and uploads them as three vec4 constants.
// @ 0x0077d200
void __cdecl FUN_0077d200(unsigned reg, unsigned p2, int isVS) {
    if (g_16f6dd0 == 0)
        return;
    const float* src = (const float*)g_16f85ac;
    float in[16];
    in[0] = src[0];
    in[1] = src[1];
    in[2] = src[2];
    in[3] = 0.0f;
    in[4] = src[4];
    in[5] = src[5];
    in[6] = src[6];
    in[7] = 0.0f;
    in[8] = src[8];
    in[9] = src[9];
    in[10] = src[10];
    in[11] = 0.0f;
    in[12] = src[12];
    in[13] = src[13];
    in[14] = src[14];
    in[15] = 1.0f;
    float out[16];
    FUN_0045eac0(out, in, g_16f6dd0);
    float data[12];
    for (int j = 0; j < 3; ++j) {
        for (int i = 0; i < 4; ++i)
            data[j * 4 + i] = out[i * 4 + j];
    }
    if (isVS)
        SETVS(g_pDevice, reg, data, 3);
    else
        SETPS(g_pDevice, reg, data, 3);
}

// ---- 0x0077d450 CopyWire -----------------------------------------------------------------
// Reference-counted object at +8 of every 16-byte element.  The release sequence is retail's
// (decrement, re-read, bump back to 1 when the count reached zero).
struct WireRef {
    unsigned char pad0[8];
    volatile long refcount;      // +8
};
struct WireElem {
    unsigned      field0;        // +0
    WireRef*      ref;           // +4
    unsigned char b0;            // +8
    unsigned char b1;            // +9
    unsigned char b2;            // +0xa
    unsigned char b3;            // +0xb
    unsigned char flag;          // +0xc
    unsigned char pad1[3];       // +0xd
};
struct WireObj {
    unsigned  header;            // +0
    WireElem  elems[6];          // +4, stride 0x10
    WireObj* CopyWire(const WireObj* src);
};
// @ 0x0077d450
WireObj* WireObj::CopyWire(const WireObj* src) {
    this->header = src->header;
    for (int i = 0; i < 6; ++i) {
        const WireElem* s = &src->elems[i];
        WireElem* d = &this->elems[i];
        d->field0 = s->field0;
        WireRef* op = d->ref;
        WireRef* np = s->ref;
        if (np != op) {
            if (np)
                _InterlockedIncrement(&np->refcount);
            d->ref = np;
            if (op) {
                _InterlockedDecrement(&op->refcount);
                if (_InterlockedExchangeAdd(&op->refcount, 0) < 1)
                    _InterlockedIncrement(&op->refcount);
                else
                    _InterlockedExchangeAdd(&op->refcount, 0);
            }
        }
        d->b0 = s->b0;
        d->b1 = s->b1;
        d->b2 = s->b2;
        d->b3 = s->b3;
        d->flag = s->flag;
    }
    return this;
}

// ---- 0x0077d510 vector<Vector4>::DoInsertValues -----------------------------------------
struct Vec4 { float x, y, z, w; };
struct Vec4Vector {
    Vec4* begin;        // +0
    Vec4* end;          // +4
    Vec4* cap;          // +8
    unsigned pad0;      // +0xc
    Vec4* fixedBuf;     // +0x10
    void DoInsertValues(Vec4* pos, unsigned n, const Vec4* value);
};
// @ 0x0077d510
void Vec4Vector::DoInsertValues(Vec4* pos, unsigned n, const Vec4* value) {
    Vec4* end = this->end;
    unsigned freeSlots = (unsigned)((char*)this->cap - (char*)end) >> 4;
    if (n > freeSlots) {
        Vec4* begin = this->begin;
        unsigned oldCount = (unsigned)((char*)end - (char*)begin) >> 4;
        unsigned newCap = oldCount * 2;
        if (oldCount == 0)
            newCap = 1;
        if (newCap <= oldCount + n)
            newCap = oldCount + n;
        Vec4* buf = newCap ? (Vec4*)FUN_00f473a0(newCap * 16, kAllocName, 0, 0, kAllocFile, 0xd1) : 0;
        Vec4* mid = (Vec4*)FUN_0047c1c0(begin, pos, buf);
        FUN_0047cae0(mid, n, value, pos);
        Vec4* newEnd = (Vec4*)FUN_0047c1c0(pos, end, mid + n);
        if (begin && begin != this->fixedBuf)
            FUN_00f47380(begin);
        this->begin = buf;
        this->end = newEnd;
        this->cap = buf + newCap;
        return;
    }
    if (n == 0)
        return;
    Vec4 tmp = *value;
    unsigned after = (unsigned)((char*)end - (char*)pos) >> 4;
    if (n >= after) {
        unsigned extra = n - after;
        FUN_0047cae0(end, extra, &tmp, pos);
        Vec4* oldEnd = end;
        this->end = end + extra;
        void* scratch;
        FUN_0047a500(&scratch, pos, oldEnd, this->end, pos);
        this->end += after;
        FUN_00898580(pos, oldEnd, &tmp);
    } else {
        Vec4* split = end - n;
        void* scratch;
        FUN_0047a500(&scratch, split, end, end, pos);
        this->end = end + n;
        FUN_00edba80(pos, split, end);
        FUN_00898580(pos, pos + n, &tmp);
    }
}

// ---- 0x0077d6c0 allocate + uninitialised vec4 copy ---------------------------------------
// @ 0x0077d6c0
void* __stdcall FUN_0077d6c0(unsigned n, const void* first, const void* last) {
    void* p = n ? FUN_00f473d0(n << 4, 0x10, 0, kAllocName, 0, 0, kAllocFile, 0xe5) : 0;
    FUN_00706ab0(first, last, p);
    return p;
}

// ---- 0x0077d710 two-kind descriptor factory ---------------------------------------------
struct DescObj {
    unsigned       field0;   // +0
    unsigned short kind;     // +4
    unsigned short size;     // +6
    void*          data;     // +8
};
struct KindObj {
    void*          vtbl;     // +0
    unsigned short kind;     // +4
    unsigned short size;     // +6
    void*          payload;  // +8, points at +0xc
};
// Retail wraps the 0x20d path in an FS:0 exception frame with a functor that destroys the
// half-built object; plain C++ does not emit that frame, so the bytes cannot match.
// @ 0x0077d710
void* __cdecl FUN_0077d710(DescObj* desc) {
    unsigned short kind = desc->kind;
    if (kind == 0x200)
        return 0;
    if (kind != 0x20d) {
        KindObj* obj = (KindObj*)FUN_00f473a0((unsigned)desc->size + 0xc, kAllocName, 0, 0, 0, 0);
        if (obj) {
            obj->payload = 0;
            obj->vtbl = &g_vtbl_13ef094;
            obj->kind = kind;
            obj->size = desc->size;
        }
        obj->payload = (char*)obj + 0xc;
        memcpy((char*)obj + 0xc, desc->data, desc->size);
        return obj;
    }
    void* src = desc->data;
    KindObj* obj = (KindObj*)FUN_00f473a0(0x70, kAllocName, 0, 0, 0, 0);
    if (obj)
        obj = (KindObj*)FUN_0040d010(obj, 0);
    ((WireObj*)((char*)obj + 0xc))->CopyWire((const WireObj*)src);
    return obj;
}
