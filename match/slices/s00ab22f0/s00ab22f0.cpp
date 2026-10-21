// SporeApp.exe frozen batch "gold4" — slice s00ab22f0 (11 functions)
// cRibbonEffect and friends.
#include "types.h"

typedef unsigned int uint;

// ---------------------------------------------------------------- vtable helpers
template <class T, int Off, class A, class B>
static inline void vcallA2(T* p, A a, B b) {
    typedef void (T::*PMF)(A, B);
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn;
    (p->*f)(a, b);
}
template <class T, int Off>
static inline int vcallR(T* p) {
    typedef int (T::*PMF)();
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn;
    return (p->*f)();
}

// ---------------------------------------------------------------- externals
int   FUN_00ab22f0(void* self, int value);   // 0x00ab22f0 (thiscall)
struct Obj { void Fn(int); };                // 0x00ab22f0 as __thiscall
void  operator_delete_arr(void* p);          // 0x00f47380  ??3@YAXPAX@Z
void  FUN_007cda70(void* a);                 // 0x007cda70

extern "C" {
extern float DAT_01565620;   // 0x01565620
extern float DAT_01679474;   // 0x01679474
extern float DAT_01679478;   // 0x01679478
extern float DAT_0167947c;   // 0x0167947c
}

// The object notified at +0x14 is a plain interface whose vtable carries the
// 2-argument Cmd at slot 0x24 and a 0-argument query at 0x30.
struct IObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void Cmd(int a, int b);
    virtual void v28(); virtual void v2c();
    virtual int  Query();
};

struct Notice {
    void*  vtbl;          // +0x00
    uint8_t pad04[0x24 - 4];
    IObj*  mObj;          // +0x24

    void NotifySet(int value);   // 0x00ab2890
};

// cRibbonEffect layout (partial), offsets straight from the disassembly.
struct Ribbon {
    uint8_t pad00[0x0c];
    uint8_t mEnabled;     // +0x0c
    uint8_t mValue;       // +0x0d
    uint8_t pad0e[0x124 - 0x0e];
    int     mIndex;       // +0x124

    void Enable(int dummy);      // 0x00ab3060
    void Disable(int dummy);     // 0x00ab3090
    void SetValue(int value);    // 0x00ab30d0
};

// @ 0x00ab3060
void Ribbon::Enable(int)
{
    IObj* p;
    if (this->mEnabled == 0) {
        this->mEnabled = 1;
    }
    if (this->mIndex >= 0) {
        p = *(IObj**)((char*)this + 0x14);
        vcallA2<IObj, 0x24>(p, this->mIndex, this->mValue);
    }
}

// @ 0x00ab3090
void Ribbon::Disable(int)
{
    IObj* p;
    if (this->mEnabled != 0) {
        this->mEnabled = 0;
        if (this->mIndex >= 0) {
            p = *(IObj**)((char*)this + 0x14);
            vcallA2<IObj, 0x24>(p, this->mIndex, 0);
        }
    }
}

// @ 0x00ab30d0
void Ribbon::SetValue(int value)
{
    IObj* p;
    this->mValue = (uint8_t)value;
    if (this->mEnabled != 0) {
        if (this->mIndex >= 0) {
            p = *(IObj**)((char*)this + 0x14);
            vcallA2<IObj, 0x24>(p, this->mIndex, value);
        }
    }
}

// @ 0x00ab2890
void Notice::NotifySet(int value)
{
    IObj* p;
    int   idx;
    *(int*)((char*)this + 0x1c) = value;
    p = this->mObj;
    idx = vcallR<IObj, 0x30>(p);
    ((Obj*)((char*)this - 8))->Fn(idx);
}

// @ 0x00ab2910
int FUN_00ab2910()
{
    int v = 1;
    *(int*)0x01675ed0 = 0x00aae8c0;
    *(int*)0x01675ed8 = 0x00ab17e0;
    *(int*)0x01675edc = 0x00ab28c0;
    *(int*)0x01675ee4 = 0x00aa8d30;
    *(int*)0x01675ee8 = v;
    *(int*)0x01675eec = v;
    return v;
}

// -------------------------------------------------------------- fixed arrays
// eastl fixed-vector "<1,16,1,0,1>" buffers are heap blocks with a 4-byte
// element count immediately before the data pointer.
static inline void release_block(void* p)
{
    if (p != 0 && *(int*)((char*)p - 4) != 0) {
        operator_delete_arr(p);
    }
}

struct Big {
    uint8_t pad00[0xd4];
    void Destroy();               // 0x00ab2950
};

// @ 0x00ab2950
void Big::Destroy()
{
    char* s = (char*)this;
    release_block(*(void**)(s + 0xd4));
    release_block(*(void**)(s + 0xc0));
    release_block(*(void**)(s + 0xac));
    release_block(*(void**)(s + 0x98));
    release_block(*(void**)(s + 0x84));
    release_block(*(void**)(s + 0x70));
    release_block(*(void**)(s + 0x5c));
    release_block(*(void**)(s + 0x48));
    release_block(*(void**)(s + 0x28));
    release_block(*(void**)(s + 0x14));
    *(int*)s = 0x013ef094;
}

// ------------------------------------------------------------- IO interfaces
struct IRead {
    virtual void r00(); virtual void r04(); virtual void r08(); virtual void r0c();
    virtual void r10(); virtual void r14(); virtual void r18(); virtual void r1c();
    virtual void r20(); virtual void r24(); virtual void r28(); virtual void r2c();
    virtual void ReadBytes(void* dst, int n);   // 0x30
};

void  EA_IO_ReadInt32(IRead* stream, void* dst, int count, int flag);  // 0x0093a780
void  EA_IO_ReadBool (IRead* stream, void* dst, int count, int flag);  // 0x0093a800
void  FUN_007d27d0(IRead* stream, void* dst);                          // 0x007d27d0
void  FUN_007ed920(IRead* stream, void* dst);                          // 0x007ed920
void  FUN_00a85b00(IRead* stream, void* dst);                          // 0x00a85b00

// @ 0x00ab2ea0
void FUN_00ab2ea0(int, IRead* stream, char* dst)
{
    EA_IO_ReadInt32(stream, &stream, 1, 0);
    *(uint*)(dst + 8) = (uint)stream & 0x3fff;
    ((IRead*)stream)->ReadBytes(dst + 0xc, 8);
    FUN_007d27d0((IRead*)stream, dst + 0x14);
    FUN_007d27d0((IRead*)stream, dst + 0x28);
    EA_IO_ReadInt32((IRead*)stream, dst + 0x3c, 1, 0);
    EA_IO_ReadInt32((IRead*)stream, dst + 0x40, 1, 0);
    EA_IO_ReadInt32((IRead*)stream, dst + 0x44, 1, 0);
    FUN_007ed920((IRead*)stream, dst + 0x48);
    FUN_007d27d0((IRead*)stream, dst + 0x5c);
    FUN_007ed920((IRead*)stream, dst + 0x70);
    FUN_007d27d0((IRead*)stream, dst + 0x84);
    FUN_007ed920((IRead*)stream, dst + 0x98);
    FUN_007d27d0((IRead*)stream, dst + 0xac);
    FUN_007d27d0((IRead*)stream, dst + 0xc0);
    FUN_007d27d0((IRead*)stream, dst + 0xd4);
    EA_IO_ReadInt32((IRead*)stream, dst + 0xe8, 1, 0);
    EA_IO_ReadInt32((IRead*)stream, dst + 0xec, 1, 0);
    FUN_00a85b00((IRead*)stream, dst + 0xf0);
    EA_IO_ReadInt32((IRead*)stream, dst + 0x110, 1, 0);
    EA_IO_ReadInt32((IRead*)stream, dst + 0x114, 1, 0);
    EA_IO_ReadInt32((IRead*)stream, dst + 0x118, 1, 0);
    ((IRead*)stream)->ReadBytes(dst + 0x120, 0xc);
    EA_IO_ReadInt32((IRead*)stream, dst + 0x12c, 1, 0);
    EA_IO_ReadInt32((IRead*)stream, dst + 0x130, 1, 0);
    EA_IO_ReadBool ((IRead*)stream, dst + 0x138, 1, 0);
    EA_IO_ReadBool ((IRead*)stream, dst + 0x140, 1, 0);
    EA_IO_ReadInt32((IRead*)stream, dst + 0x148, 1, 0);
}

// @ 0x00ab26a0
void FUN_00ab26a0(void* self, void* a2, void* a3)
{
    char* s = (char*)self;
    char* p2 = (char*)a2;
    char* p3 = (char*)a3;
    int      v;
    int      flags;
    uint32_t u1, u2, r1, r2;
    int      stack20[8];
    int      loc18;
    int      loc8, loc4;

    *(void**)(s + 0x24) = a2;
    *(int*)(s + 0x28) = ((int(*)(void*))(*(void***)p2)[0x2c / 4])(p2);

    {
        float f = DAT_01565620;
        *(float*)(s + 0x98) = f;
        *(float*)(s + 0x9c) = f;
        *(float*)(s + 0xa0) = f;
        uint32_t nf = *(uint32_t*)&f ^ 0x80000000u;
        *(uint32_t*)(s + 0xa4) = nf;
        *(uint32_t*)(s + 0xa8) = nf;
        *(uint32_t*)(s + 0xac) = nf;
    }
    ((Obj*)(s - 8))->Fn((int)a3);

    {
        char* ia = (char*)((void*(*)(void*))(*(void***)a3)[0x14 / 4])(a3);
        char* ib = (char*)((void*(*)(void*))(*(void***)p2)[0x20 / 4])(a2);
        if (ib == 0) return;

        // 8-dword context block copied out of the object at +0x1c + 0x110
        {
            int* src = (int*)(*(int*)(s + 0x1c) + 0x110);
            for (int i = 0; i < 8; ++i) stack20[i] = src[i];
        }
        u1 = *(uint*)(s + 0x1d0);
        u2 = *(uint*)(s + 0x1d4);
        if ((u1 & u2) != 0xffffffffu) {
            stack20[0] = (int)u1;
            stack20[1] = (int)u2;
        }
        loc8 = 0;
        loc4 = 0;
        flags = *(int*)(*(int*)(s + 0x1c) + 8);
        if ((((uint)flags >> 0x15) & 1) == 0) {
            if (*(uint8_t*)((char*)stack20 + 9) == 0x0f) {
                r1 = *(uint*)(s + 0x1d0);
                r2 = *(uint*)(s + 0x1d4);
                if ((((uint)loc8 & (uint)loc4) != 0xffffffffu) &&
                    ((r1 & r2) != 0xffffffffu)) {
                    stack20[0] = *(int*)(*(int*)(s + 0x1c) + 0x110);
                    stack20[1] = *(int*)(*(int*)(s + 0x1c) + 0x114);
                    loc8 = (int)r1;
                    loc4 = (int)r2;
                }
                loc8 = ((int(*)(void*, int, int))(*(void***)ia)[0x24 / 4])(ia, stack20[0], stack20[1]);
            }
            v = *(int*)(s + 0x22c);
            ((void(*)(void*, int*, int))(*(void***)ib)[0x18 / 4])((char*)s - 8, stack20, v);
        } else {
            if (*(uint8_t*)((char*)stack20 + 9) == 0x0f) {
                loc8 = ((int(*)(void*, int, int))(*(void***)ia)[0x24 / 4])(ia, loc8, loc4);
            }
            v = *(int*)(s + 0x228);
            ((void(*)(void*, int*, int))(*(void***)ib)[0x2c / 4])((char*)s - 8, stack20, v);
        }
        ((void(*)(void*, uint32_t, int))(*(void***)ia)[0x10 / 4])(
            ia, *(uint32_t*)(s + 0x1d4) & 0xff, (int)(s + 0x230));
        *(uint8_t*)(s + 0x234) = (uint8_t)*(uint32_t*)&DAT_01565620;
    }
}

// --------------------------------------------------------- property refresh
// A "resource" interface: slot 0 AddRef, 4 Release, 8 Init, 0x1c a bool query,
// 0x8c a 2-argument lookup.
struct IRes {
    virtual void AddRef();
    virtual void Release();
    virtual void Init();
    virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual int  Query();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88();
    virtual void* Lookup(uint32_t a, uint32_t b);   // 0x8c
};

static inline void swapres(IRes*& field, IRes* got)
{
    IRes* old = field;
    if (got != old) {
        if (got != 0) got->AddRef();
        field = got;
        if (old != 0) old->Release();
    }
}

void  FUN_00a8d020(void* a, void* b);                    // 0x00a8d020
void  FUN_00a7fc10(void* ctx, void* a, void* b, float* c, float* d, void* e); // 0x00a7fc10
void  FUN_004c10e0(void* dst, int n, void* val);         // 0x004c10e0
void  FUN_004c10e0_blk(void* dst, void* src);            // 0x011e0744 (eastl vector insert)
void  ScaleCurve3(void* dst, const void* src);           // 0x007ed1b0 (EA::Swarm::ScaleCurve)
void  SimpleVectorFloat_PushBack(void* dst, const float* v);  // 0x00455660
void  FUN_00a6c7a0(void* a, int b, void* c, void* d, void* e); // 0x00a6c7a0

extern "C" {
extern float DAT_01470f1c;   // 0x01470f1c
extern float DAT_014595f8;   // 0x014595f8
extern float DAT_014595f4;   // 0x014595f4
extern float DAT_016795bc;   // 0x016795bc
extern float DAT_016795c0;   // 0x016795c0
extern float DAT_016795c4;   // 0x016795c4
}
void  FUN_007cda70(void* a);                             // 0x007cda70 (redundant)

// @ 0x00ab22f0
void FUN_00ab22f0(void* self, IRes* ctx)
{
    char* s = (char*)self;
    float* fsrc;
    float  loc8;
    int    n, i;

    {
        float* pf = (float*)(*(int*)(s + 0x24) + 0x7c);
        loc8 = 1e-06f;
        fsrc = pf;
        if (*pf <= 1e-06f) fsrc = &loc8;
        *(double*)(s + 0x58) = (double)(1.0f / *fsrc);
    }
    *(int*)(s + 0x188) = *(int*)(*(int*)(s + 0x24) + 0x1dc);
    *(int*)(s + 0x18c) = *(int*)(*(int*)(s + 0x24) + 0x1e0);
    *(uint*)(s + 0x184) = *(uint8_t*)(*(int*)(s + 0x24) + 0x135);
    if ((*(uint8_t*)(*(int*)(s + 0x24) + 0xb) & 1) == 0) {
        *(float*)(s + 0x8c) = DAT_01679474;
        *(float*)(s + 0x90) = DAT_01679478;
        *(float*)(s + 0x94) = DAT_0167947c;
        *(float*)(s + 0x98) = 0.0f;
    } else {
        *(int*)(s + 0x8c) = *(int*)(*(int*)(s + 0x24) + 0x234);
        *(int*)(s + 0x90) = *(int*)(*(int*)(s + 0x24) + 0x238);
        *(int*)(s + 0x94) = *(int*)(*(int*)(s + 0x24) + 0x23c);
        FUN_007cda70(s + 0x8c);
        *(float*)(s + 0x98) = 1.0f;
    }

    {
        int   cc = *(int*)(s + 0x24);
        int*  vec = (int*)(cc + 0x4c);
        *(int*)(s + 0x1cc) = *(int*)(cc + 0x58);
        *(int*)(s + 0x1d0) = vec[4];
        *(int*)(s + 0x1d4) = vec[5];
        *(int*)(s + 0x1c0) = vec[0];
        *(int*)(s + 0x1c4) = vec[1];
        *(int*)(s + 0x1c8) = vec[2];
        {
            int* pv = (int*)(cc + 0x88);
            int  cnt = (pv[1] - pv[0]) >> 2;
            float best = *(float*)pv[0];
            for (i = 1; (uint)i < (uint)cnt; ++i) {
                float v = ((float*)pv[0])[i];
                if (v > best) best = v;
            }
            *(float*)(s + 0xb8) = best;
        }
    }

    {
        char* cc = (char*)(*(int*)(s + 0x24));
        uint32_t f1 = *(uint32_t*)(cc + 0x1e8);
        uint32_t f2 = *(uint32_t*)(cc + 0x1ec);
        if ((f1 & f2) != 0xffffffffu) {
            IRes* got = (IRes*)ctx->Lookup(f1, f2);
            swapres(*(IRes**)(s + 0x1b0), got);
        }
        f1 = *(uint32_t*)(cc + 0x1f0);
        f2 = *(uint32_t*)(cc + 0x1f4);
        if ((f1 & f2) != 0xffffffffu) {
            IRes* got = (IRes*)ctx->Lookup(f1, f2);
            swapres(*(IRes**)(s + 0x1b4), got);
        }
        f1 = *(uint32_t*)(cc + 0x1f8);
        f2 = *(uint32_t*)(cc + 0x1fc);
        if ((f1 & f2) != 0xffffffffu) {
            IRes* got = (IRes*)ctx->Lookup(f1, f2);
            swapres(*(IRes**)(s + 0x1b8), got);
        }
        {
            IRes* r;
            r = *(IRes**)(s + 0x1b0);
            if (r != 0) { r->Init(); *(uint8_t*)(s + 0x1bc) = (uint8_t)r->Query(); }
            r = *(IRes**)(s + 0x1b4);
            if (r != 0) { r->Init(); *(uint8_t*)(s + 0x1bd) = (uint8_t)r->Query(); }
            r = *(IRes**)(s + 0x1b8);
            if (r != 0) { r->Init(); *(uint8_t*)(s + 0x1be) = (uint8_t)r->Query(); }
        }
        FUN_00a8d020(*(void**)(s + 0x1e4), *(void**)(s + 0x1e8));

        {
            char* c2 = (char*)(*(int*)(s + 0x24));
            float l8[2];
            if (*(int*)(c2 + 0x1ac) != *(int*)(c2 + 0x1b0)) {
                l8[0] = 0.0f; l8[1] = 0.0f;
                FUN_00a7fc10(ctx, c2 + 0x1ac, s + 0x1e4, l8, l8 + 1, s + 0x210);
                *(uint8_t*)(s + 0x1f8) = 0;
                void* pend = *(void**)(s + 0x200);
                int   base = *(int*)(s + 0x1fc);
                if ((uint)((int)pend - base) < (uint)(int)l8[0]) {
                    uint32_t val = 0;
                    FUN_004c10e0(pend, (base - (int)pend) + (int)l8[0], &val);
                    return;
                }
                void* ins = (void*)(base + (int)l8[0]);
                FUN_004c10e0_blk(ins, pend);
                *(int*)(s + 0x200) = (int)ins + (*(int*)(s + 0x200) - (int)pend);
                return;
            }
            {
                void* pend = *(void**)(s + 0x200);
                void* base = *(void**)(s + 0x1fc);
                FUN_004c10e0_blk(base, pend);
                *(int*)(s + 0x200) = (int)base + (*(int*)(s + 0x200) - (int)pend);
                *(uint8_t*)(s + 0x210) = 0;
            }
        }
    }
}

// @ 0x00ab2a50
void* FUN_00ab2a50(void* self)
{
    int* p = (int*)self;
    float one = 1.0f;
    float zero = 0.0f;

    p[1] = 0;
    p[0] = 0x014595fc;
    p[2] = 0;
    p[5] = 0; p[6] = 0; p[7] = 0;
    p[10] = 0; p[0xb] = 0; p[0xc] = 0;
    p[3] = 0x40000000; p[4] = 0x40000000;
    p[0xf] = 0; p[0x10] = 0; p[0x11] = 0; p[0x12] = 0; p[0x13] = 0; p[0x14] = 0;
    p[0x17] = 0; p[0x18] = 0; p[0x19] = 0;
    p[0x1c] = 0; p[0x1d] = 0; p[0x1e] = 0;
    p[0x21] = 0; p[0x22] = 0; p[0x23] = 0;
    p[0x26] = 0; p[0x27] = 0; p[0x28] = 0;
    p[0x2b] = 0; p[0x2c] = 0; p[0x2d] = 0;
    p[0x30] = 0; p[0x31] = 0; p[0x32] = 0;
    p[0x35] = 0; p[0x36] = 0; p[0x37] = 0;
    p[0x3b] = 0x3d872b02; p[0x3a] = 0x32;
    *(uint8_t*)(p + 0x3e) = 0;
    *(uint8_t*)((char*)p + 0xf9) = 0;
    *(uint8_t*)((char*)p + 0xfa) = 0;
    *(uint8_t*)((char*)p + 0xfb) = 0;
    p[0x40] = 0;
    p[0x3c] = -1; p[0x3d] = -1; p[0x42] = -1; p[0x43] = -1;
    *(uint16_t*)(p + 0x3f) = 0;
    p[0x45] = (int)0xc479c000; p[0x44] = -1;
    p[0x46] = 0; p[0x47] = 0x3f800000;
    p[0x48] = *(int*)&DAT_016795bc;
    p[0x49] = *(int*)&DAT_016795c0;
    p[0x4a] = *(int*)&DAT_016795c4;
    p[0x4b] = 0; p[0x4c] = 0;
    p[0x4e] = -1; p[0x4f] = -1; p[0x50] = -1; p[0x51] = -1;
    p[0x52] = 0;
    p[2] |= 0x88;

    // vector<Vector3> appends of {1,1,1} into the slots at 0x4c, 0x74, 0x9c, 0xc4
    {
        int* v;
        v = p + 0x13; if (*v < p[0x14]) { int* d = (int*)*v; p[0x13] = (int)(d + 3); if (d) { d[0] = 0x3f800000; d[1] = 0x3f800000; d[2] = 0x3f800000; } }
        else { float tmp[3] = {1.0f,1.0f,1.0f}; ScaleCurve3(v, tmp); }
        v = p + 0x1d; if (*v < p[0x1e]) { int* d = (int*)*v; p[0x1d] = (int)(d + 3); if (d) { d[0] = 0x3f800000; d[1] = 0x3f800000; d[2] = 0x3f800000; } }
        else { float tmp[3] = {1.0f,1.0f,1.0f}; ScaleCurve3(v, tmp); }
        v = p + 0x18; if (*v < p[0x19]) { int* d = (int*)*v; p[0x18] = (int)(d + 1); if (d) { d[0] = 0x3f800000; } }
        else { SimpleVectorFloat_PushBack(v, &one); }
        v = p + 0x22; if (*v < p[0x23]) { int* d = (int*)*v; p[0x22] = (int)(d + 1); if (d) { d[0] = 0x3f800000; } }
        else { SimpleVectorFloat_PushBack(v, &one); }
        v = p + 0x27; if (*v < p[0x28]) { int* d = (int*)*v; p[0x27] = (int)(d + 3); if (d) { d[0] = 0x3f800000; d[1] = 0x3f800000; d[2] = 0x3f800000; } }
        else { float tmp[3] = {1.0f,1.0f,1.0f}; ScaleCurve3(v, tmp); }
        v = p + 0x2c; if (*v < p[0x2d]) { int* d = (int*)*v; p[0x2c] = (int)(d + 3); if (d) { d[0] = 0x3f800000; d[1] = 0x3f800000; d[2] = 0x3f800000; } }
        else { float tmp[3] = {1.0f,1.0f,1.0f}; ScaleCurve3(v, tmp); }
        v = p + 0x36; if (*v < p[0x37]) { int* d = (int*)*v; p[0x36] = (int)(d + 1); if (d) { d[0] = 0x3f800000; } }
        else { SimpleVectorFloat_PushBack(v, &one); }
        v = p + 0x31; if (*v < p[0x32]) { int* d = (int*)*v; p[0x31] = (int)(d + 1); if (d) { d[0] = 0x3f800000; } }
        else { SimpleVectorFloat_PushBack(v, &one); }
    }
    return self;
}

// @ 0x00ab3100
int FUN_00ab3100(char* self, int param_2, int param_3, int param_4, float param_5,
                 int param_6, int param_7, int param_8, int param_9, int param_10,
                 int param_11, int param_12, int param_13, int param_14,
                 int param_15, int param_16, int param_17, int param_18,
                 int param_19, int param_20, int param_21)
{
    char* ctx = *(char**)(self + 0x14);
    int   n = *(int*)(ctx + 0x110);
    float scale;
    float off;
    uint8_t b1, b2;
    char* dst;
    int   base;

    if (n < 1) {
        n = *(int*)(self + 0x38);
        scale = 1.0f / (float)n;
        off = (float)param_3 * scale;
    } else if (n == 1) {
        scale = 1.0f;
        off = 0.0f;
    } else {
        param_3 = param_3 % n;
        scale = 1.0f / (float)n;
        off = (float)param_3 * scale;
    }

    b1 = *(uint8_t*)(self + 0x12d);
    b2 = *(uint8_t*)(self + 0x12e);
    base = (uint)*(uint8_t*)(self + 0x12c) + param_2;
    off = *(float*)(ctx + 0x11c) * off + *(float*)(self + 0x40);

    dst = (char*)base;
    *(int*)(dst) = param_9;
    *(int*)(dst + 4) = param_10;
    *(int*)(dst + 8) = param_11;
    *(int*)(dst + param_4) = param_6;
    *(int*)(dst + param_4 + 4) = param_7;
    *(int*)(dst + param_4 + 8) = param_8;
    *(int*)(dst + param_4 * 2) = param_12;
    *(int*)(dst + param_4 * 2 + 4) = param_13;
    *(int*)(dst + param_4 * 2 + 8) = param_14;
    *(int*)(dst + param_4 * 3) = param_15;
    *(int*)(dst + param_4 * 3 + 4) = param_16;
    *(int*)(dst + param_4 * 3 + 8) = param_17;

    {
        char* u = (char*)((uint)b2 + param_2);
        *(float*)u = off;
        *(float*)(u + 4) = param_5;
        *(float*)(u + param_4) = off;
        u += param_4;
        *(float*)(u + 4) = param_5 + 0.5f;
        *(float*)(u + param_4) = off + scale;
        *(float*)(u + 4 + param_4) = param_5 + 0.5f;
        char* w = u + param_4 * 2;
        *(float*)w = off + scale;
        *(float*)(w + 4) = param_5;
    }
    {
        char* u = (char*)((uint)b1 + param_2);
        *(int*)u = param_19;
        *(int*)(u + param_4) = param_18;
        u += param_4 * 2;
        *(int*)u = param_20;
        *(int*)(u + param_4) = param_21;
    }
    return param_2 + param_4 * 4;
}


