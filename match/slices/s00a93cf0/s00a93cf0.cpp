// match/slices/s00a93cf0/s00a93cf0.cpp
// Slice s00a93cf0 -- Simulator::cCreatureAbility state cluster (0x00a93cf0 .. 0x00a94b70).
//
// The class is a game component (GmeIComponent) that also implements a refcount
// interface: the ctor at 0x00a94470 writes three vtable words at +0/+4/+8 and the
// dtor at 0x00a947b0 restores the two base vtables.  `this` arrives in ecx for
// every function here, so the whole set is modelled as __thiscall members of one
// stub struct carrying the retail field offsets and the vtable slots the
// disassembly addresses.  Callees without a name are declared (never defined) so a
// real `call rel32` is emitted; each callee's calling convention is taken from
// its own `ret N` / the caller's `add esp,N`.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "s00a93cf0.h"

// ---------------------------------------------------------------------------
// Callees (free).  Conventions read off each callee's own `ret N`.
// ---------------------------------------------------------------------------
void __cdecl FUN_0093a780(void* io, void* dst, int a, int b);   // 0x0093a780 ret-c
void __cdecl FUN_0093a700(void* io, void* dst, int a, int b);   // 0x0093a700 ret-c
void __cdecl FUN_0093a6c0(void* io, void* dst, int a);          // 0x0093a6c0 ret-c
void __cdecl FUN_007d27d0(void* io, void* dst);                 // 0x007d27d0 ret-c
void __cdecl FUN_007ed920(void* io, void* dst);                 // 0x007ed920 ret-c
void __cdecl FUN_00a85b00(void* io, void* dst);                 // 0x00a85b00 ret-c
void __cdecl FUN_00a6c7a0(void* a, int b, void* c, void* d, void* e); // 0x00a6c7a0 ret-c
float __cdecl FUN_007cdb90(void* a);                            // 0x007cdb90 float10 ret-c
void  __cdecl FUN_00f47380(void* p);                            // 0x00f47380 operator delete

// 0x00620230 -- intrusive list dtor, reached as `lea ecx,[this+0x14]; call` (ret 0).
struct IntrusiveList {
    void FUN_00620230();                                        // 0x00620230
};

// 0x0041cb40 -- rw::math::fpu::Matrix33Template<float,0>::Matrix33Template<float,0>(src).
// Reached as `push src; lea ecx,[obj]; call` -> __thiscall with a stack arg, ret 4.
struct MatCtor { void FUN_0041cb40(void* src); };

// 0x00537dc0 -- cSPTransformOps::Assign(PBX) reached as `push src; mov ecx,this; call` -> ret 4.
struct TransformOps { void* FUN_00537dc0(void* src); };

// I/O object passed as the first argument to the (de)serialisers.  Its vtable slot
// +0x30 is called thiscall-style with (dst,size) on the stack and cleans up (ret 8).
struct IoObj {
    void FUN_0041cb00();                                        // vtable +0x00 placeholder
    void FUN_0041cb00b();                                       // vtable +0x04 placeholder
    void FUN_0041cb00c();                                       // vtable +0x08 placeholder
    void FUN_0041cb00d();                                       // vtable +0x0c placeholder
    void FUN_0041cb00e();                                       // vtable +0x10 placeholder
    void FUN_0041cb00f();                                       // vtable +0x14 placeholder
    void FUN_0041cb00g();                                       // vtable +0x18 placeholder
    void FUN_0041cb00h();                                       // vtable +0x1c placeholder
    void FUN_0041cb00i();                                       // vtable +0x20 placeholder
    void FUN_0041cb00j();                                       // vtable +0x24 placeholder
    void FUN_0041cb00k();                                       // vtable +0x28 placeholder
    void FUN_0041cb00l();                                       // vtable +0x2c placeholder
    void FUN_00a93d30(void* dst, int size);                     // vtable +0x30 read raw (ret 8)
};

// ---------------------------------------------------------------------------
// Sub-objects reached through a component's vtable slot +0x20.  Slots +0x10,
// +0x14, +0x18, +0x1c, +0x24 and +0x74 are used by this cluster.
// ---------------------------------------------------------------------------
struct SubObj {
    void FUN_0041cb40();                                        // vtable +0x00 placeholder
    void FUN_0041cb44();                                        // vtable +0x04
    void FUN_0041cb48();                                        // vtable +0x08
    void FUN_0041cb4c();                                        // vtable +0x0c
    void FUN_0041cb50();                                        // vtable +0x10
    void FUN_0041cb54();                                        // vtable +0x14
    void FUN_0041cb58();                                        // vtable +0x18
    void FUN_0041cb5c();                                        // vtable +0x1c
    void FUN_0041cb60();                                        // vtable +0x20
    void FUN_0041cb64();                                        // vtable +0x24
    void FUN_0041cb68();                                        // vtable +0x28
    void FUN_0041cb6c();                                        // vtable +0x2c
};

typedef void (__cdecl* AbilityHook)(void* self, void* arg, void* out);

// vtable-slot read: VS(obj,off) == *(void**)(*(char**)obj + off)
#define VS(obj, off) (*(void**)(*(char**)(obj) + (off)))

extern float g_167889c;
extern float g_16788a0;
extern float g_16788a4;
extern float g_1678860;
extern float g_1678864;
extern float g_1485720;
extern u32   g_1678948;
extern float g_1565198;                                        // 3.4e38 marker
extern float g_13eb8b0[4];                                     // sign-mask vector
extern float g_13f11c8;                                        // tiny epsilon
extern u32   g_1454410[2];                                     // -1.0 double
extern AbilityHook g_16787b0[8];                               // per-state hook table

// ===========================================================================
// The stub class shared by all 14 members.  Every retail field offset the
// disassembly touches is named so the emitted accesses line up; the anonymous
// float runs (m28/m2c/m30..., m5c/m60/m64, m8c..m90, ...) carry the exact
// offsets the ctor initialises.  The retail record stores its 64-bit members
// at 4-byte-aligned offsets (e.g. +0x2c/+0x3c), so packing is 4.
// ===========================================================================
#pragma pack(push, 4)
struct CAbil {
    void*  vt0;                                                // +0x00
    void*  vt1;                                                // +0x04
    void*  vt2;                                                // +0x08
    u8     m0c;                                                // +0x0c
    u8     m0d;                                                // +0x0d
    u8     m0e;                                                // +0x0e
    char   pad0f[0x10 - 0x0f];
    u8     m10;                                                // +0x10
    u8     m11;                                                // +0x11
    u8     m12;                                                // +0x12
    char   pad13[0x14 - 0x13];
    void*  m14;                                                // +0x14 (intrusive list head)
    void*  m18;                                                // +0x18
    void*  m1c;                                                // +0x1c ability descriptor
    void*  m20;                                                // +0x20 owner component
    void*  m24;                                                // +0x24
    void*  m28;                                                // +0x28
    float  m2c;                                                // +0x2c  (pair-zeroed with m30)
    float  m30;                                                // +0x30
    u8     m34;                                                // +0x34
    char   pad35[0x38 - 0x35];
    u8     m38;                                                // +0x38
    char   pad39[0x3c - 0x39];
    float  m3c;                                                // +0x3c  (pair-zeroed with m40)
    float  m40;                                                // +0x40
    void*  m44;                                                // +0x44
    void*  m48;                                                // +0x48
    u32    m4c;                                                // +0x4c
    double m50;                                                // +0x50 (a float at +0x54 aliases its high half)
    float  m58;                                                // +0x58
    float  m5c;                                                // +0x5c
    float  m60;                                                // +0x60
    float  m64;                                                // +0x64
    float  m68;                                                // +0x68
    float  m6c;                                                // +0x6c
    float  m70;                                                // +0x70
    float  m74;                                                // +0x74
    float  m78;                                                // +0x78
    float  m7c;                                                // +0x7c
    float  m80;                                                // +0x80
    float  m84;                                                // +0x84
    float  m88;                                                // +0x88
    float  m8c;                                                // +0x8c
    // cSPTransform at +0x90 (0x38 bytes): vector @+0x90..9c, matrix @+0xa8.
    u8     m90_0;                                              // +0x90 flags
    char   pad91[0x94 - 0x91];
    float  m94;                                                // +0x94
    float  m98;                                                // +0x98
    float  m9c;                                                // +0x9c
    float  ma0;                                                // +0xa0
    float  ma4;                                                // +0xa4
    u64    ma8;                                                // +0xa8 matrix (0x30)
    u64    mb0;
    u64    mb8;
    u64    mc0;
    // cSPTransform at +0xc8 (0x38 bytes)
    u8     mc8_0;                                              // +0xc8 flags
    char   padc9[0xcc - 0xc9];
    float  mcc;                                                // +0xcc
    float  md0;                                                // +0xd0
    float  md4;                                                // +0xd4
    float  md8;                                                // +0xd8
    float  mdc;                                                // +0xdc
    u64    me0;                                                // +0xe0 matrix (0x30)
    u64    me8;
    u64    mf0;
    u64    mf8;
    float  m100;                                               // +0x100
    float  m104;                                               // +0x104
    float  m108;                                               // +0x108
    float  m10c;                                               // +0x10c
    u16    m110;                                               // +0x110
    u16    m112;                                               // +0x112
    float  m114;                                               // +0x114
    float  m118;                                               // +0x118
    float  m11c;                                               // +0x11c
    float  m120;                                               // +0x120
    float  m124;                                               // +0x124
    float  m128;                                               // +0x128
    float  m12c;                                               // +0x12c
    float  m130;                                               // +0x130
    float  m134;                                               // +0x134
    float  m138;                                               // +0x138
    float  m13c;                                               // +0x13c
    float  m140;                                               // +0x140
    float  m144;                                               // +0x144
    float  m148;                                               // +0x148
    float  m14c;                                               // +0x14c
    float  m150;                                               // +0x150
    float  m154;                                               // +0x154
    float  m158;                                               // +0x158
    float  m15c;                                               // +0x15c
    float  m160;                                               // +0x160
    float  m164;                                               // +0x164
    float  m168;                                               // +0x168
    float  m16c;                                               // +0x16c
    float  m170;                                               // +0x170
    float  m174;                                               // +0x174
    float  m178;                                               // +0x178
    i32    m17c;                                               // +0x17c lo word of the 64-bit key
    i32    m180;                                               // +0x180 hi word of the 64-bit key
    i32    m184;                                               // +0x184 handle; -1 == none
    u8     m188;                                               // +0x188
    char   pad189[0x18c - 0x189];
    u8     m18c;                                               // +0x18c
    char   pad18d[0x190 - 0x18d];
    u8     m190;                                               // +0x190

    // ---- members -------------------------------------------------------
    void  FUN_00a93cf0(IoObj* io, void* mgr, CAbil* obj);      // 0x00a93cf0
    void  FUN_00a93ea0();                                      // 0x00a93ea0
    int   FUN_00a93ee0(int id, int* a, int count);             // 0x00a93ee0
    void  FUN_00a94030(char v);                                // 0x00a94030
    void  FUN_00a940a0(void* p);                               // 0x00a940a0
    void  FUN_00a94130(int p);                                 // 0x00a94130
    int   FUN_00a94220(int id, int* src, int n);               // 0x00a94220
    int   __declspec(noinline) FUN_00a943a0();                 // 0x00a943a0
    CAbil* FUN_00a94470(void* owner);                          // 0x00a94470
    CAbil* FUN_00a947b0(u8 freeIt);                            // 0x00a947b0
    void  FUN_00a94800(void* owner, void* mgr);                // 0x00a94800
    void  FUN_00a94940(void* t0, void* t1);                    // 0x00a94940
    void  FUN_00a94b70(void* desc);                            // 0x00a94b70
};
#pragma pack(pop)

// The two bases the ctor/dtor write directly, so the vtable stores emit the
// expected immediates.
struct GmeRefCount   { virtual void r0(); };
struct GmeIComponent { virtual void c0(); virtual void c1(); };

// ===========================================================================
// 0x00a93cf0 -- deserialiser for the whole ability record.
//   io   : the EA::IO stream object (first arg, ecx-supplied `this` is unused)
//   mgr  : second argument
//   obj  : destination record
// ===========================================================================
// @ 0x00a93cf0
void CAbil::FUN_00a93cf0(IoObj* io, void* mgr, CAbil* obj)
{
    char* o = (char*)obj;
    int tmp;
    FUN_0093a780(io, &tmp, 1, 0);
    *(i32*)(o + 0x184) = tmp & 0x7ff;

    io->FUN_00a93d30(o + 0xc, 8);
    FUN_0093a780(io, o + 0x14, 1, 0);
    io->FUN_00a93d30(o + 0x18, 8);
    io->FUN_00a93d30(o + 0x20, 8);
    io->FUN_00a93d30(o + 0x28, 0xc);
    io->FUN_00a93d30(o + 0x34, 0xc);
    io->FUN_00a93d30(o + 0x40, 8);
    io->FUN_00a93d30(o + 0x48, 0xc);
    io->FUN_00a93d30(o + 0x54, 0xc);
    FUN_007d27d0(io, o + 0x60);
    FUN_0093a780(io, o + 0x74, 1, 0);
    FUN_0093a700(io, o + 0x78, 1, 0);
    FUN_0093a780(io, o + 0x7c, 1, 0);
    FUN_007d27d0(io, o + 0x80);
    FUN_007ed920(io, o + 0x94);
    FUN_007d27d0(io, o + 0xa8);
    FUN_00a85b00(io, o + 0xc0);
    FUN_0093a6c0(io, o + 0xe0, 1);
    io->FUN_00a93d30(o + 0xe4, 0xc);
    FUN_0093a780(io, o + 0xf0, 1, 0);
    FUN_0093a780(io, o + 0xf4, 1, 0);
    FUN_0093a780(io, o + 0xf8, 1, 0);
    io->FUN_00a93d30(o + 0xfc, 0xc);
    FUN_0093a780(io, o + 0x108, 1, 0);
    (void)mgr;
}

// ===========================================================================
// 0x00a93ea0
// ===========================================================================
// @ 0x00a93ea0
void CAbil::FUN_00a93ea0()
{
    if (m0c != 0) {
        ((void (__thiscall*)(void*, int))*(void**)((char*)vt0 + 0xc))(this, 1);
    }
    if (m184 >= 0) {
        void* p = ((void* (__thiscall*)(void*))VS(m20, 0x20))(m20);
        ((void (__thiscall*)(void*, int))VS(p, 0x1c))(p, m184);
    }
    m1c = 0;
    m20 = 0;
}
// ===========================================================================
// 0x00a93ee0
// ===========================================================================
// @ 0x00a93ee0
int CAbil::FUN_00a93ee0(int id, int* a, int count)
{
    if (id != 1) {
        return 0;
    }
    if (count >= 2 && a[1] != *(unsigned char*)((char*)m1c + 0xe0)) {
        return 1;
    }

    int v = *a;
    if (m17c != v || m180 != (v >> 31)) {
        m17c = v;
        m180 = v >> 31;
        if (m184 >= 0) {
            void* pL = ((void* (__thiscall*)(void*))VS(m20, 0x20))(m20);
            ((void (__thiscall*)(void*, int))VS(pL, 0x1c))(pL, m184);

            unsigned key = (unsigned)m17c;
            unsigned hi  = (unsigned)m180;
            struct Words { unsigned w[8]; };
            Words words;
            words = *(const Words*)((char*)m1c + 0xc0);
            if ((key & hi) != 0xffffffffu) {
                words.w[0] = key;
                words.w[1] = hi;
            }
            ((char*)&words)[8] = 0;
            if (((char*)&words)[9] == 0x0f) {
                void* q = ((void* (__thiscall*)(void*))VS(m20, 0x30))(m20);
                void* r = ((void* (__thiscall*)(void*))VS(q, 0x14))(q);
                ((char*)&words)[8] = ((char  (__thiscall*)(void*, char, unsigned, unsigned))
                        VS(r, 0x24))(r, ((char*)&words)[8], words.w[0], words.w[1]);
            }
            char ok = ((char (__thiscall*)(void*, void*, void*, int*))
                       VS(pL, 0x18))(pL, (char*)this - 4, &words, &m184);
            if (!ok) {
                ((void (__thiscall*)(void*, char, void*))
                 VS(pL, 0x10))(pL, ((char*)&words)[8], &m188);
                m18c = ((char*)&words)[8];
                m184 = -1;
            }
        }
    }
    return 1;
}

// ===========================================================================
// 0x00a94030
// ===========================================================================
// @ 0x00a94030
void CAbil::FUN_00a94030(char v)
{
    m0e = v;
    if (v != 0) {
        *(i32*)((char*)this + 0x100) = *(i32*)((char*)this + 0x94);
        *(i32*)((char*)this + 0x104) = *(i32*)((char*)this + 0x98);
        *(i32*)((char*)this + 0x108) = *(i32*)((char*)this + 0x9c);
    }
    if (m0c != 0 && m184 >= 0) {
        void* p = ((void* (__thiscall*)(void*))VS(m20, 0x20))(m20);
        ((void (__thiscall*)(void*, int, char))VS(p, 0x24))(p, m184, m0e);
    }
}

// ===========================================================================
// 0x00a940a0
// ===========================================================================
// @ 0x00a940a0
void CAbil::FUN_00a940a0(void* p)
{
    AbilityHook h = g_16787b0[m190];
    if (h != 0) {
        h(this, p, &m18c);
    }
    m110 = (u16)(m110 + 1);
}

// ===========================================================================
// 0x00a940e0 -- 3-argument __cdecl getter: forwards (arg1+0xc0) into
// FUN_00a6c7a0 with two 4-byte result slots and returns the second.
// ===========================================================================
// @ 0x00a940e0
int __cdecl FUN_00a940e0(void* a, void* b, void* c, void* d)
{
    int out = 0;
    FUN_00a6c7a0((char*)b + 0xc0, 0, &out, &c, &d);
    return out;
}

// ===========================================================================
// 0x00a94130
// ===========================================================================
// @ 0x00a94130
void CAbil::FUN_00a94130(int p)
{
    double zero = 0.0;
    unsigned f;
    if (p == 0
        || *(u16*)((char*)m1c + 0x78) == 0
        || ((f = *(u32*)((char*)m1c + 8)), (f >> 2) & 1)
        || ((f >> 10) & 1)) {

        if (m0c == 0 || m0d != 0) {
            m0d = 0;
            m0c = 1;
        }
        *(double*)((char*)this + 0x3c) = zero;
        *(double*)((char*)this + 0x2c) = zero;
        *(i32*)((char*)this + 0x100) = *(i32*)((char*)this + 0x94);
        *(i32*)((char*)this + 0x104) = *(i32*)((char*)this + 0x98);
        *(i32*)((char*)this + 0x108) = *(i32*)((char*)this + 0x9c);
        m44 = 0;
        *(float*)((char*)this + 0x54) = 0.0f;

        float neg = *(float*)((char*)m1c + 0x18);
        if (neg >= 0.0f) {
            m64 = FUN_007cdb90((char*)m1c + 0x18);
        } else {
            float n2 = *(float*)((char*)m1c + 0x20);
            if (n2 >= 0.0f) {
                m64 = FUN_007cdb90((char*)m1c + 0x20);
            } else {
                m64 = 0.0f;
            }
        }
        m34 = (p != 0);
        if (m184 >= 0) {
            void* q = ((void* (__thiscall*)(void*))VS(m20, 0x20))(m20);
            ((void (__thiscall*)(void*, int, char))VS(q, 0x24))(q, m184, m0e);
        }
    }
}

// ===========================================================================
// 0x00a94220 -- property dispatch (jump table on the property id).
// ===========================================================================
// @ 0x00a94220
int CAbil::FUN_00a94220(int id, int* src, int n)
{
    if (id < 0xf) {
        switch (id) {
        case 0:  m128 = *(float*)src; return 1;
        case 1:  m134 = *(float*)src; return 1;
        case 2:  m130 = *(float*)src; return 1;
        case 3:  m12c = *(float*)src; return 1;
        case 4:  m138 = *(float*)src; return 1;
        case 5:
            m13c = *(float*)&src[0];
            m140 = *(float*)&src[1];
            m144 = *(float*)&src[2];
            return 1;
        case 0xe:
            if (m184 >= 0) {
                void* p = ((void* (__thiscall*)(void*))VS(m20, 0x20))(m20);
                return ((int (__thiscall*)(void*, int, int, int, int, int*))
                        VS(p, 0x74))(p, 0, m184, 0, n, src);
            }
            break;
        default:
            break;
        }
    } else if (id == 0x101) {
        m110 = (u16)src[0];
        m118 = *(float*)&src[1];
        m120 = *(float*)&src[2];
        m114 = *(float*)&src[3];
        m11c = *(float*)&src[4];
        m124 = *(float*)&src[5];
        return 1;
    }
    return 0;
}

// ===========================================================================
// 0x00a943a0
// ===========================================================================
// @ 0x00a943a0
int CAbil::FUN_00a943a0()
{
    void* o = m20;
    float* pf = (float*)((char*)o + 0x74);
    float eps = g_13f11c8;
    float local = eps;
    if (!(*(float*)((char*)o + 0x74) > eps)) {
        pf = &local;
    }
    m50 = 1.0 / (double)*pf;

    *(i32*)((char*)this + 0x170) = *(i32*)((char*)o + 0x54);
    *(i32*)((char*)this + 0x174) = *(i32*)((char*)o + 0x58);
    *(i32*)((char*)this + 0x178) = *(i32*)((char*)o + 0x5c);
    *(i32*)((char*)this + 0x164) = *(i32*)((char*)o + 0x48);
    *(i32*)((char*)this + 0x168) = *(i32*)((char*)o + 0x4c);
    *(i32*)((char*)this + 0x16c) = *(i32*)((char*)o + 0x50);

    void* s = m20;
    m84 = **(float**)((char*)s + 0x80);
    unsigned cnt = (unsigned)((*(int*)((char*)s + 0x84) - *(int*)((char*)s + 0x80)) >> 2);
    unsigned i = 1;
    if (cnt > i) {
        do {
            float v = (*(float**)((char*)s + 0x80))[i];
            if (v > m84) {
                m84 = v;
            }
            i++;
        } while (i < (unsigned)((*(int*)((char*)s + 0x84) - *(int*)((char*)s + 0x80)) >> 2));
    }
    return cnt;
}

// ===========================================================================
// 0x00a94470 -- constructor.  Two base subobjects are initialised, then the
// whole 0x194-byte record is filled with the retail default values.
// ===========================================================================
// @ 0x00a94470
CAbil* CAbil::FUN_00a94470(void* owner)
{
    double zero = 0.0;
    GmeRefCount*   rc = (GmeRefCount*)(void*)this;
    GmeIComponent* cp = (GmeIComponent*)(void*)this;
    void** vp = (void**)this;

    vp[2] = (void*)0x13ef094;
    vp[3] = 0;
    vp[1] = (void*)0x13f21d4;
    vp[2] = (void*)0x13f2194;
    vp[0] = (void*)0x1458714;
    vp[1] = (void*)0x14586d8;
    vp[2] = (void*)0x14586d4;
    (void)rc; (void)cp;

    *(u8*)((char*)this + 0x10) = 0;
    *(u8*)((char*)this + 0x11) = 0;
    *(&m12) = 1;

    void* self = (char*)this + 0x14;
    *(void**)((char*)self + 4) = self;
    *(void**)(char*)self = self;

    *(double*)((char*)this + 0x30) = zero;
    *(double*)((char*)this + 0x40) = zero;
    m50 = *(double*)g_1454410;
    m58 = 0.0f;
    m1c = 0;
    m20 = owner;
    m24 = 0;
    m28 = 0;
    m38 = 0;
    m48 = 0;

    m5c = g_167889c;
    m60 = g_16788a0;
    m64 = g_16788a4;

    m68 = 0.0f;
    m6c = 0.0f;
    m70 = 0.0f;
    m74 = 0.0f;
    m78 = 0.0f;
    m7c = 0.0f;
    m80 = 0.0f;
    m84 = 0.0f;

    m88 = g_167889c;
    m8c = g_16788a0;
    m90_0 = 0;                            // +0x90 low byte
    *(float*)((char*)this + 0x94) = g_16788a4;
    m98 = g_167889c;
    m9c = g_16788a0;
    ma0 = g_16788a4;
    ma4 = g_1485720;

    ((MatCtor*)((char*)this + 0xa8))->FUN_0041cb40(&g_1678948);

    *(u16*)((char*)this + 0xcc) = 0;
    *(u16*)((char*)this + 0xce) = 0;
    *(float*)((char*)this + 0xd0) = g_167889c;
    *(float*)((char*)this + 0xd4) = g_16788a0;
    *(float*)((char*)this + 0xd8) = g_16788a4;
    *(float*)((char*)this + 0xdc) = g_1485720;

    ((MatCtor*)((char*)this + 0xe0))->FUN_0041cb40(&g_1678948);

    *(float*)((char*)this + 0x104) = g_167889c;
    *(float*)((char*)this + 0x108) = g_16788a0;
    *(float*)((char*)this + 0x10c) = g_16788a4;

    *(u16*)((char*)this + 0x110) = 0;
    *(u16*)((char*)this + 0x112) = 0;

    *(float*)((char*)this + 0x114) = g_1678860;
    *(float*)((char*)this + 0x118) = g_1678864;
    *(float*)((char*)this + 0x11c) = g_1678860;
    *(float*)((char*)this + 0x120) = g_1678864;
    *(float*)((char*)this + 0x124) = g_1678860;
    *(float*)((char*)this + 0x128) = g_1678864;

    float cv = g_1485720;
    *(float*)((char*)this + 0x12c) = cv;
    *(float*)((char*)this + 0x130) = cv;
    *(float*)((char*)this + 0x134) = cv;
    *(float*)((char*)this + 0x138) = cv;
    *(float*)((char*)this + 0x13c) = cv;
    *(float*)((char*)this + 0x140) = cv;
    *(float*)((char*)this + 0x144) = cv;
    *(float*)((char*)this + 0x148) = cv;
    *(float*)((char*)this + 0x14c) = cv;
    *(float*)((char*)this + 0x150) = cv;
    *(float*)((char*)this + 0x154) = cv;
    *(float*)((char*)this + 0x158) = cv;
    *(float*)((char*)this + 0x15c) = cv;
    *(float*)((char*)this + 0x160) = cv;

    *(float*)((char*)this + 0x164) = 0.0f;
    *(float*)((char*)this + 0x168) = 0.0f;
    *(float*)((char*)this + 0x16c) = 0.0f;
    *(float*)((char*)this + 0x170) = 0.0f;
    *(float*)((char*)this + 0x174) = 0.0f;
    *(float*)((char*)this + 0x178) = 0.0f;

    m180 = -1;
    m184 = -1;
    *(i32*)((char*)this + 0x188) = -1;
    *(u16*)((char*)this + 0x17c) = 0;
    m190 = 0;
    return this;
}

// ===========================================================================
// 0x00a947b0 -- destructor.
// ===========================================================================
// @ 0x00a947b0
CAbil* CAbil::FUN_00a947b0(u8 freeIt)
{
    vt0 = (void*)0x1458714;
    vt1 = (void*)0x14586d8;
    vt2 = (void*)0x14586d4;
    ((IntrusiveList*)(void*)((char*)this + 0x14))->FUN_00620230();
    vt1 = (void*)0x13f21d4;
    vt2 = (void*)0x13ef094;
    if (freeIt & 1) {
        FUN_00f47380(this);
    }
    return this;
}

// ===========================================================================
// 0x00a94800
// ===========================================================================
// @ 0x00a94800
void CAbil::FUN_00a94800(void* owner, void* mgr)
{
    m20 = owner;
    m24 = ((void* (__thiscall*)(void*))VS(owner, 0x2c))(owner);

    float big = g_1565198;
    float nbig = -big;
    m68 = big;
    m6c = big;
    m70 = big;
    m74 = nbig;
    m78 = nbig;
    m7c = nbig;

    ((CAbil*)((char*)this - 4))->FUN_00a943a0();

    void* p = ((void* (__thiscall*)(void*))VS(owner, 0x20))(owner);
    if (p != 0) {
        unsigned key = (unsigned)m17c;
        unsigned hi  = (unsigned)m180;
        unsigned words[8];
        unsigned* src = (unsigned*)((char*)m1c + 0xc0);
        for (int i = 0; i < 8; i++) {
            words[i] = src[i];
        }
        if ((key & hi) != 0xffffffffu) {
            words[0] = key;
            words[1] = hi;
        }
        char flag = 0;
        if (((char*)words)[9] == 0x0f) {
            void* q = ((void* (__thiscall*)(void*))VS(mgr, 0x14))(mgr);
            flag = ((char  (__thiscall*)(void*, unsigned, unsigned, char))
                    VS(q, 0x24))(q, words[0], words[1], 0);
        }
        ((void (__thiscall*)(void*, void*, unsigned*, int*))
         VS(p, 0x18))(p, (char*)this - 4, words, &m184);
        ((void (__thiscall*)(void*, char, void*))
         VS(p, 0x10))(p, flag, &m188);
        m18c = flag;
    }
}

// ===========================================================================
// 0x00a94940 -- copy two cSPTransforms in, derive the world position, and (when
// the transform is "instanced") accumulate the delta into the two stored
// positions.
// ===========================================================================
// @ 0x00a94940
void CAbil::FUN_00a94940(void* t0, void* t1)
{
    ((TransformOps*)(void*)((char*)this + 0x90))->FUN_00537dc0(t0);
    void* dst = (char*)this + 0xc8;
    ((TransformOps*)dst)->FUN_00537dc0(t1);

    float py0 = m84, py1 = m88, py2 = m8c;   // saved previous position (xmm3/4/5)

    float x = *(float*)((char*)this + 0x94);
    float y = *(float*)((char*)this + 0x98);
    float z = *(float*)((char*)this + 0x9c);
    m84 = x; m88 = y; m8c = z;

    void* mc8p = (char*)this + 0xc8;
    if ((*(u8*)mc8p & 2) != 0) {
        // rotate the local vector by the 3x3 matrix at mc8+0x14
        float* M = (float*)((char*)mc8p + 0x14);
        float ox = m84, oy = m88, oz = m8c;
        float nx = M[3] * oy + M[6] * oz + ox * M[0];
        float ny = M[1] * ox + M[4] * oy + M[7] * oz;
        float nz = M[2] * ox + M[5] * oy + M[8] * oz;
        m84 = nx; m88 = ny; m8c = nz;
    }

    float s = *(float*)((char*)mc8p + 0x10);
    m84 = m84 * s;
    m88 = m88 * s;
    m8c = m8c * s;

    float tx = *(float*)((char*)mc8p + 4);
    float ty = *(float*)((char*)mc8p + 8);
    float tz = *(float*)((char*)mc8p + 0xc);
    m84 = tx + m84;
    m88 = ty + m88;
    m8c = tz + m8c;

    float dx = m84 - py0;
    float dy = m88 - py1;
    float dz = m8c - py2;

    float chk = m68;
    if (chk != g_1565198 && chk != -g_1565198) {
        m68 = chk + dx;
        m6c = m6c + dy;
        m70 = m70 + dz;
        m74 = m74 + dx;
        m78 = m78 + dy;
        m7c = m7c + dz;
    }
}

// ===========================================================================
// 0x00a94b70
// ===========================================================================
// @ 0x00a94b70
void CAbil::FUN_00a94b70(void* desc)
{
    m1c = desc;
    ((CAbil*)((char*)this - 4))->FUN_00a943a0();
}
