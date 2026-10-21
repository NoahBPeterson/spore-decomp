// Slice s0116b1c0 -- RenderWare 4 audio core (rw::audio): the MPEG/EALayer3 synthesis filter
// (Dct32 transform driver) and the seven pull-decoder "reader" objects built on the bus/channel
// mix API.  Neighbouring slice s0116c170 covers 0x0116c170.. (same object, VC .NET 2003 + /LTCG).
//
// Object file built by VC .NET 2003 (cl 13.10) with /GL + /LTCG.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---------------------------------------------------------------------------
// Externs / callees
// ---------------------------------------------------------------------------
extern "C" void  SNDMEMI_alloc(void* p, int size);       // 0x113ec90
extern "C" void  F_0113f8f0(int bus, int ch, int n);     // 0x113f8f0  bus release
extern "C" int   F_0113f780(int bus, int ch, int* out, int* count); // 0x113f780  bus acquire
extern "C" int   F_01140a00(int ch);                     // 0x1140a00  resolve channel
extern "C" int   F_01140a20(int ch);                     // 0x1140a20  channel index
extern "C" void* FUN_011402c0(int size);                 // 0x11402c0  operator new(size, tag)
extern "C" int   FUN_01158b90(int ch);                   // 0x1158b90  per-channel alloc size
extern "C" void  FUN_011741b0(void* p);                  // 0x11741b0  operator delete
extern "C" void  FUN_0116bda0(void);                     // 0x116bda0  reader tell (entry point)
extern "C" void  FUN_0116bec0(void);                     // 0x116bec0  reader tell (reverse variant)

// 0x016e817c : int16 -> float conversion routine (set at run time)
extern "C" void (__cdecl* g_converter_16e817c)(int, void*, void*);  // 0x16e817c

// 0x013eb8b0 : -0.0f (only its sign bit is used, by the DCT-II sign fold)
extern "C" float g_negZero_13eb8b0;                      // 0x13eb8b0

// 0x011765b0 / 0x01175ca0 : __thiscall constructors that take the object in ECX and return
// it, modelled as member functions of an opaque type.
struct Obj11765b0  { Obj11765b0*  Init(); };             // 0x11765b0
struct Obj1175ca0  { Obj1175ca0*  Init(); };             // 0x1175ca0

// ---------------------------------------------------------------------------
// The bus/channel object a reader pulls through (+0x1c, +0x28 or +0x34 of the reader).
// Every method is a __thiscall on the object; only the argument shapes differ.
// ---------------------------------------------------------------------------
struct Bus {
    int   ReadA(int* out, int n);                        // 0x1175da0  ret 8
    int   ReadB(int* out, int n);                        // 0x1175f80  ret 8
    void  Write(int pos, int bytes, int samples);        // 0x1175f50  ret 0xc
    void* Get3(void* out);                               // 0x1175d50  copies 3 dwords, ret 4
    void  Put(void* in, int a);                          // 0x1175d70  ret 8
    int   Num(int a);                                    // 0x1175d90  ret 4
    void  Set(int a, int b, int c);                      // 0x1175ce0  ret 0xc
    void  PutF(void* in);                                // 0x11761f0  ret 4
    void* GetF(void* out);                               // 0x11761d0  ret 4
};

// ---------------------------------------------------------------------------
// Reader object (0x5c bytes).  +0x00 holds the object's own read entry point and +0x04 the
// close entry point (both plain cdecl functions that take the reader first); the rest are the
// bus/channel window the decoders pull through.  The meaning of the middle fields differs
// between the seven variants, so several of them are union-like.
// ---------------------------------------------------------------------------
struct Reader {
    int  (*pfnRead)(Reader*, int, int*);    // +0x00
    void (*pfnClose)(Reader*);              // +0x04
    int  f08;                               // +0x08
    int  f0c;                               // +0x0c
    int  f10;                               // +0x10  sample-window base
    int  f14;                               // +0x14  end of the window
    int  f18;                               // +0x18
    int  f1c;                               // +0x1c  bus object / scratch pointer
    int  f20;                               // +0x20  pull cursor / write count
    int  f24;                               // +0x24  start of the readable window
    int  f28;                               // +0x28  end of the readable window / bus object
    int  f2c;                               // +0x2c  available / duplex count
    int  f30;                               // +0x30  mode (2 = the "N of M" variant)
    int  f34;                               // +0x34  duplex source / bus object
    u8   f38;                               // +0x38  channel index
    u8   f39[3];
    int  f3c;                               // +0x3c  mid/side stereo state
    int  f40;                               // +0x40  frame counter
    int  f44;                               // +0x44  current frame
    int  f48;                               // +0x48  frames available
    float f4c;                              // +0x4c
    float f50;                              // +0x50
    int  f54;                               // +0x54
    int  f58;                               // +0x58
};

struct Patch {                  // argument block of the initialisers
    int f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24;
};

// Entry points installed into +0x00 / +0x04 below (defined further down).
int  Reader_Pull_116b4b0(Reader* r, int n, int* buf);
void Reader_Close_116b6a0(Reader* r);
int  Reader_Pull_116b740(Reader* r, int n, int* buf);
void Reader_Close_116b7a0(Reader* r);
int  Reader_Pull_116b880(Reader* r, int n, int* buf);
int  Reader_Pull_116b9d0(Reader* r, int n, int* buf);
void Reader_Close_116bb00(Reader* r);
int  Reader_Pull_116bba0(Reader* r, int n, int* buf);
int  Reader_Pull_116be60(Reader* r, int n, int* buf);
int  Reader_Pull_116bf40(Reader* r, int n, int* buf);
int  Reader_Pull_116c060(Reader* r, int n, int* buf);
int  Reader_Pull_116c0f0(Reader* r, int n, int* buf);

// ---------------------------------------------------------------------------
// 0x01169f50  Dct32 -- 32-point DCT, defined in another part of this object.
// ---------------------------------------------------------------------------
extern "C" void Dct32(float* a, float* b);

// ===========================================================================
// 0x0116b1c0  synthesis-filter transform: 18 blocks x (17 complex legs + 1 real leg).
// ===========================================================================
// @ 0x0116b1c0
void FilterTransform(Reader* r, u32 ch, float* out)
{
    u8 n = (u8)((r->f38 - 1) & 0xf);
    r->f38 = n;
    int even = n & 1;
    int odd  = even ^ 1;
    int off  = n + odd;

    float* base = (float*)(odd * 0x480 + (int)ch * 0x900 + r->f10);
    int    stride = off * 2;
    float* src  = base;
    float* dst  = out;
    float* coef = (float*)((char*)&g_negZero_13eb8b0 - off * 4);

    Dct32(base, coef);          // fills the 16 coefficient windows at coef[0x20*k]

    for (int k = 0; k < 16; k++, coef += 0x20, src += 0x10, dst++) {
        float acc = coef[0] * src[0];
        acc -= coef[1] * src[1];
        acc += coef[2] * src[2];
        acc -= coef[3] * src[3];
        acc += coef[4] * src[4];
        acc -= coef[5] * src[5];
        acc += coef[6] * src[6];
        acc -= coef[7] * src[7];
        acc += coef[8] * src[8];
        acc -= coef[9] * src[9];
        acc += coef[10] * src[10];
        acc -= coef[11] * src[11];
        acc += coef[12] * src[12];
        acc -= coef[13] * src[13];
        acc += coef[14] * src[14];
        acc -= coef[15] * src[15];
        *dst = acc;
    }

    {   // last (real) leg of the first 16
        float acc = coef[0x22] * src[0x12] + coef[0x20] * src[0x10];
        acc += coef[0x24] * src[0x14];
        acc += coef[0x26] * src[0x16];
        acc += coef[0x28] * src[0x18];
        acc += coef[0x2a] * src[0x1a];
        acc += coef[0x2c] * src[0x1c];
        acc += coef[0x2e] * src[0x1e];
        dst[1] = acc;
        coef += off * 2;
        dst  += 2;
    }

    for (int k = 0; k < 15; k++, coef -= 0x20, src -= 0x10, dst++) {
        float acc = -(coef[-1] * src[0]);
        acc -= coef[-2]  * src[1];
        acc -= coef[-3]  * src[2];
        acc -= coef[-4]  * src[3];
        acc -= coef[-5]  * src[4];
        acc -= coef[-6]  * src[5];
        acc -= coef[-7]  * src[6];
        acc -= coef[-8]  * src[7];
        acc -= coef[-9]  * src[8];
        acc -= coef[-10] * src[9];
        acc -= coef[-11] * src[10];
        acc -= coef[-12] * src[11];
        acc -= coef[-13] * src[12];
        acc -= coef[-14] * src[13];
        acc -= coef[-15] * src[14];
        acc -= src[15] * coef[0];
        *dst = acc;
    }
}

// ===========================================================================
// 0x0116b4b0  reader pull (the plain, unlooped variant)
// ===========================================================================
// @ 0x0116b4b0
int Reader_Pull_116b4b0(Reader* r, int n, int* buf)
{
    int total = 0;
    if (r->f28 != 0) {
        F_0113f8f0(r->f24, r->f38, r->f28);
        r->f28 = 0;
    }
    while (n > 0) {
        int scratch[4];
        int got = ((Bus*)r->f34)->ReadA(scratch, n);
        r->f2c += (u16)got;
        r->f28 += got;
        total += got;
        buf += got;
        if (got >= n) {
            n -= got;
            continue;
        }
        n -= got;
        int avail;
        r->f1c = F_0113f780(r->f24, r->f38, &r->f20, &avail);
        if (r->f1c == 0) {
            if (n > 0 && r->f28 != 0)
                SNDMEMI_alloc(buf, n * 4);
            r->f20 = 0;
            return total;
        }
        r->f2c = 0;
        Bus* bus = (Bus*)r->f34;
        float f[3];
        int   flag;
        if (r->f30 > 1) {
            bus->Get3(f);
            if (avail == 0) {
                f[1] = 0.0f;
                f[2] = 1.0f;
            } else {
                f[2] = 0.0f;
            }
            flag = 1;
        } else {
            bus->Get3(f);
            if (avail == 0) {
                f[1] = 1.0f;
            } else {
                f[1] = 0.0f;
            }
            flag = 0;
        }
        bus->Put(f, 0);
        bus->Num(flag);
        bus->Write(r->f1c + 1, r->f20 * 4, r->f20);
    }
    return total;
}

// ===========================================================================
// 0x0116b6a0  reader close: release the bus window (tail call)
// ===========================================================================
// @ 0x0116b6a0
void Reader_Close_116b6a0(Reader* r)
{
    if (r->f34 != 0) {
        FUN_011741b0((void*)r->f34);
        return;
    }
    return;
}

// ===========================================================================
// 0x0116b6c0  reader initialiser (plain variant)
// ===========================================================================
// @ 0x0116b6c0
void Reader_Init_116b6c0(Reader* r, Patch* p)
{
    r->pfnRead  = &Reader_Pull_116b4b0;
    r->f24      = FUN_01158b90(F_01140a00(p->f18));
    r->f38      = (u8)F_01140a20(p->f18);
    r->f1c      = 0;
    *(short*)&r->f2c = 0;
    r->f30      = p->f20;
    r->f20      = p->f0c;
    r->pfnClose = &Reader_Close_116b6a0;
    void* d = FUN_011402c0(0xd68);
    if (d != 0) {
        r->f28 = 0;
        r->f34 = (int)((Obj1175ca0*)d)->Init();
    } else {
        r->f28 = 0;
        r->f34 = 0;
    }
}

// ===========================================================================
// 0x0116b740  reader pull (fixed-size duplex variant)
// ===========================================================================
// @ 0x0116b740
int Reader_Pull_116b740(Reader* r, int n, int* buf)
{
    if ((unsigned)r->f20 >= (unsigned)r->f1c)
        return -1;
    int scratch[4];
    int got = ((Bus*)r->f28)->ReadA(scratch, n);
    r->f20 += got;
    buf += got;
    if (got < n)
        SNDMEMI_alloc(buf, (n - got) * 4);
    return 1;
}

// ===========================================================================
// 0x0116b7a0  reader close (fixed-size duplex variant)
// ===========================================================================
// @ 0x0116b7a0
void Reader_Close_116b7a0(Reader* r)
{
    if (r->f28 != 0) {
        FUN_011741b0((void*)r->f28);
        return;
    }
    return;
}

// ===========================================================================
// 0x0116b7c0  reader initialiser (fixed-size duplex variant)
// ===========================================================================
// @ 0x0116b7c0
void Reader_Init_116b7c0(Reader* r, Patch* p)
{
    r->pfnRead  = &Reader_Pull_116b740;
    r->f1c      = p->f0c;
    r->f20      = 0;
    r->f24      = p->f20;
    p->f24      = (int)&FUN_0116bda0;
    r->pfnClose = &Reader_Close_116b7a0;
    void* d = FUN_011402c0(0xd68);
    r->f28 = (d != 0) ? (int)((Obj1175ca0*)d)->Init() : 0;
    Bus* bus = (Bus*)r->f28;
    float f[3];
    bus->Get3(f);
    f[2] = 1.0f;
    bus->Put(f, 0);
    bus->Num(r->f24 > 1 ? 1 : 0);
    bus->Set(p->f00, r->f1c * 4, r->f1c);
}

// ===========================================================================
// 0x0116b880  reader pull (frame-window variant)
// ===========================================================================
// @ 0x0116b880
int Reader_Pull_116b880(Reader* r, int n, int* buf)
{
    while (n > 0) {
        int scratch[4];
        int got = ((Bus*)r->f1c)->ReadA(scratch, n);
        r->f20 += got;
        n    -= got;
        buf  += got;
        if (got < n) {
            Bus* bus = (Bus*)r->f1c;
            r->f20 = r->f24;
            float f[3];
            f[0] = 0.0f;
            f[1] = 0.0f;
            f[2] = 1.0f;
            bus->Put(f, 0);
            int cnt = r->f28 - r->f24;
            bus->Write(r->f2c, cnt * 4 + 4, cnt + 1);
        }
    }
    return 1;
}

// ===========================================================================
// 0x0116b920  reader initialiser (frame-window variant)
// ===========================================================================
// @ 0x0116b920
void Reader_Init_116b920(Reader* r, Patch* p)
{
    r->pfnRead  = &Reader_Pull_116b880;
    r->pfnClose = &Reader_Close_116bb00;
    r->f2c      = p->f04;
    r->f20      = 0;
    r->f24      = p->f10;
    r->f28      = p->f14;
    void* d = FUN_011402c0(0xd68);
    r->f1c = (d != 0) ? (int)((Obj1175ca0*)d)->Init() : 0;
    Bus* bus = (Bus*)r->f1c;
    float f[3];
    bus->Get3(f);
    f[2] = 1.0f;
    bus->Put(f, 0);
    bus->Set(p->f00, r->f24 * 4, r->f24);
    p->f24 = (int)&FUN_0116bda0;
}

// ===========================================================================
// 0x0116b9d0  reader pull (short-block variant)
// ===========================================================================
// @ 0x0116b9d0
int Reader_Pull_116b9d0(Reader* r, int n, int* buf)
{
    int total = 0;
    int flag  = 0;
    if (r->f34 != 0) {
        F_0113f8f0(r->f30, r->f38, r->f34);
        r->f34 = 0;
    }
    if (n < 1)
        return total;
    for (;;) {
        int scratch[4];
        int got = ((Bus*)r->f1c)->ReadB(scratch, n);
        r->f28 += got;
        r->f34 += got;
        buf   += got;
        total += got;
        if (got >= n) {
            n -= got;
        } else {
            n -= got;
            int avail;
            short* s = (short*)F_0113f780(r->f30, r->f38, &r->f24, &avail);
            r->f20 = (int)s;
            if (s == 0) {
                if (n > 0 && r->f34 != 0)
                    SNDMEMI_alloc(buf, n * 4);
                return total;
            }
            if (r->f2c <= 1)
                flag = 1;
            if (flag != 0) {
                float f[2];
                f[0] = (float)(int)s[0];
                f[1] = (float)(int)s[1];
                ((Bus*)r->f1c)->PutF(f);
                r->f20 += 4;
            }
            r->f28 = 0;
            ((Bus*)r->f1c)->Write(r->f20, r->f24 * 4, r->f24);
        }
        if (n < 1)
            return total;
    }
}

// ===========================================================================
// 0x0116bb00  reader close (short-block variant)
// ===========================================================================
// @ 0x0116bb00
void Reader_Close_116bb00(Reader* r)
{
    if (r->f1c != 0) {
        FUN_011741b0((void*)r->f1c);
        return;
    }
    return;
}

// ===========================================================================
// 0x0116bb20  reader initialiser (short-block variant)
// ===========================================================================
// @ 0x0116bb20
void Reader_Init_116bb20(Reader* r, Patch* p)
{
    r->pfnRead  = &Reader_Pull_116b9d0;
    r->pfnClose = &Reader_Close_116bb00;
    r->f30      = FUN_01158b90(F_01140a00(p->f18));
    r->f38      = (u8)F_01140a20(p->f18);
    r->f2c      = p->f20;
    r->f20      = 0;
    r->f24      = p->f0c;
    r->f28      = 0;
    r->f34      = 0;
    void* d = FUN_011402c0(0xa8);
    r->f1c = (d != 0) ? (int)((Obj11765b0*)d)->Init() : 0;
}

// ===========================================================================
// 0x0116bba0  reader pull (mid/side stereo pair variant)
// ===========================================================================
// @ 0x0116bba0
int Reader_Pull_116bba0(Reader* r, int n, int* buf)
{
    int total = 0;
    Bus* bus = (Bus*)r->f1c;
    if (r->f30 <= 1) {
        if (r->f40 == 0) {
            int f = r->f44 / 0x1c;
            bus->Write(r->f34, f * 0x70, f * 0x1c);
            r->f40 = 1;
        }
        for (;;) {
            int scratch[4];
            int got = bus->ReadB(scratch, n);
            r->f20 += got;
            total  += got;
            buf    += got;
            if (got >= n) {
                n -= got;
                if (n == 0)
                    return total;
                continue;
            }
            int cur = r->f44;
            n -= got;
            int tail = cur % 0x1c;
            int cnt  = (r->f48 - cur) + 1 + tail;
            r->f20 = cur - tail;
            bus->Write(((cur - tail) / 0x1c) * 0xf + r->f34, cnt * 4, cnt);
            if (r->f3c == 0) {
                r->pfnClose(r);
                float f[2];
                bus->GetF(f);
                r->f4c = f[0];
                r->f50 = f[1];
                got = bus->ReadB(scratch, n);
                buf   += got;
                total += got;
                r->f20 += got;
                r->f3c = 1;
                n -= got;
                if (n == 0)
                    return total;
                continue;
            }
            float f[2];
            f[0] = r->f4c;
            f[1] = r->f50;
            r->pfnClose(r);
            bus->PutF(f);
            r->f20 += 4;
            n -= 0;
            if (n == 0)
                return total;
        }
    } else {
        while (n > 0) {
            int scratch[4];
            int got = bus->ReadB(scratch, n);
            r->f20 += got;
            n      -= got;
            total  += got;
            buf    += got;
            if (got < n) {
                int cnt = r->f28 - r->f24;
                r->f20 = r->f24;
                bus->Write(r->f2c, cnt * 4 + 4, cnt + 1);
            }
        }
    }
    return total;
}

// ===========================================================================
// 0x0116bdb0  reader initialiser (mid/side stereo pair variant)
// ===========================================================================
// @ 0x0116bdb0
void Reader_Init_116bdb0(Reader* r, Patch* p)
{
    r->pfnRead  = &Reader_Pull_116bba0;
    r->pfnClose = &Reader_Close_116bb00;
    r->f2c      = p->f04;
    r->f20      = 0;
    r->f30      = p->f20;
    r->f24      = p->f10;
    r->f28      = p->f14;
    void* d = FUN_011402c0(0xa8);
    r->f1c = (d != 0) ? (int)((Obj11765b0*)d)->Init() : 0;
    p->f24 = (int)&FUN_0116bda0;
    if (r->f30 <= 1) {
        r->f34 = p->f00;
        *(int*)&r->f38 = p->f0c;
        r->f3c = 0;
        r->f40 = 0;
        r->f44 = p->f10;
        r->f48 = p->f14;
    } else {
        ((Bus*)r->f1c)->Write(p->f00, r->f24 * 4, r->f24);
    }
}

// ===========================================================================
// 0x0116be60  reader pull (reverse/duplex variant)
// ===========================================================================
// @ 0x0116be60
int Reader_Pull_116be60(Reader* r, int n, int* buf)
{
    if (r->f28 >= r->f24)
        return -1;
    int scratch[4];
    int got = ((Bus*)r->f1c)->ReadB(scratch, n);
    r->f28 += got;
    buf += got;
    if (got < n) {
        SNDMEMI_alloc(buf, (n - got) * 4);
        got = n;
    }
    return got;
}

// ===========================================================================
// 0x0116bed0  reader initialiser (reverse/duplex variant)
// ===========================================================================
// @ 0x0116bed0
void Reader_Init_116bed0(Reader* r, Patch* p)
{
    r->pfnRead  = &Reader_Pull_116be60;
    r->pfnClose = &Reader_Close_116bb00;
    r->f20      = p->f00;
    r->f24      = p->f0c;
    r->f28      = 0;
    void* d = FUN_011402c0(0xa8);
    r->f1c = (d != 0) ? (int)((Obj11765b0*)d)->Init() : 0;
    p->f24 = (int)&FUN_0116bec0;
    ((Bus*)r->f1c)->Write(r->f20, r->f24 * 4, r->f24);
}

// ===========================================================================
// 0x0116bf40  reader pull (bus-resident variant)
// ===========================================================================
// @ 0x0116bf40
int Reader_Pull_116bf40(Reader* r, int n, int* buf)
{
    if (r->f2c != 0) {
        F_0113f8f0(r->f28, (u8)r->f30, r->f2c);
        r->f2c = 0;
    }
    while (n > 0) {
        if (r->f24 >= r->f20) {
            int avail;
            r->f1c = F_0113f780(r->f28, (u8)r->f30, &r->f1c, &avail);
            if (r->f1c == 0) {
                if (r->f2c != 0)
                    SNDMEMI_alloc(buf, n * 4);
                break;
            }
            r->f20 = avail;
            r->f24 = 0;
        }
        int cnt = r->f20 - r->f24;
        if (n < cnt)
            cnt = n;
        ((void (__cdecl*)(int, void*, void*))g_converter_16e817c)(
            cnt, (void*)(r->f1c + r->f24 * 2), buf);
        r->f24 += cnt;
        r->f2c += cnt;
        n   -= cnt;
        buf  = (int*)((char*)buf + cnt * 4);
    }
    return r->f2c;
}

// ===========================================================================
// 0x0116c010  reader initialiser (bus-resident variant)
// ===========================================================================
// @ 0x0116c010
void Reader_Init_116c010(Reader* r, Patch* p)
{
    r->pfnRead = &Reader_Pull_116bf40;
    r->f28     = FUN_01158b90(F_01140a00(p->f18));
    *(u8*)&r->f30 = (u8)F_01140a20(p->f18);
    r->f1c     = 0;
    r->f20     = -1;
    r->f24     = 0;
    r->f2c     = 0;
}

// ===========================================================================
// 0x0116c060  reader pull (plain output variant)
// ===========================================================================
// @ 0x0116c060
int Reader_Pull_116c060(Reader* r, int n, int* buf)
{
    while (n > 0) {
        int cnt = (r->f28 - r->f20) + 1;
        if (n < cnt)
            cnt = n;
        ((void (__cdecl*)(int, void*, void*))g_converter_16e817c)(
            cnt, (void*)(r->f1c + r->f20 * 2), buf);
        r->f20 += cnt;
        n   -= cnt;
        buf  = (int*)((char*)buf + cnt * 4);
        if (r->f20 > r->f28)
            r->f20 = r->f24;
    }
    return 1;
}

// ===========================================================================
// 0x0116c0c0  reader initialiser (plain output variant)
// ===========================================================================
// @ 0x0116c0c0
void Reader_Init_116c0c0(Reader* r, Patch* p)
{
    r->pfnRead = &Reader_Pull_116c060;
    r->f1c     = p->f00;
    r->f20     = 0;
    r->f24     = p->f10;
    r->f28     = p->f14;
    p->f24     = (int)&FUN_0116bda0;
}

// ===========================================================================
// 0x0116c0f0  reader pull (windowed variant)
// ===========================================================================
// @ 0x0116c0f0
int Reader_Pull_116c0f0(Reader* r, int n, int* buf)
{
    unsigned start = (unsigned)r->f20;
    unsigned end   = (unsigned)r->f24;
    if (start >= end)
        return -1;
    r->f20 = start + n;
    if ((unsigned)r->f20 < end) {
        ((void (__cdecl*)(int, void*, void*))g_converter_16e817c)(
            n, (void*)(r->f1c + start * 2), buf);
        return 1;
    }
    int cnt = end - start;
    ((void (__cdecl*)(int, void*, void*))g_converter_16e817c)(
        cnt, (void*)(r->f1c + start * 2), buf);
    SNDMEMI_alloc((int*)((char*)buf + cnt * 4), (n - cnt) * 4);
    return 1;
}
