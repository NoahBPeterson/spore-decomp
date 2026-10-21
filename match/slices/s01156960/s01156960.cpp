// Slice s01156960 (0x01156960 - 0x01157a60): RenderWare4 audio core (rw::audio).
//
// Two objects live here:
//   * the MIX voice mixer helpers (MIX_setlowpass / MIX_sethighpass /
//     MIX_filteradd) which hang filter-state blocks off a 0x5c-byte voice
//     record in the global mixer voice array at 0x016e8174, and
//   * the EALayer3 bit-stream decoder object (bit reader + MPEG-2/2.5 LSF
//     scalefactor/quantiser header parse).  Its layout is identical to the
//     CSubbandDecoder in slice s011586f0, which calls ReadBits/FUN_01157460
//     across the slice boundary.
//
// Built with VC .NET 2003 (cl 13.10) + /GL /LTCG.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE

#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed   short i16;

// ---------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------

// 0x016e61a8 : rw::audio::core::System singleton (thiscall allocator host).
struct System {
    void* Alloc(int size, const char* name, int align, int flags);  // 0x112c820
    void  Free(void* p, int flags);                                 // 0x112c850
};
extern "C" System* g_system;      // 0x016e61a8
// 0x016e8174 : mixer voice array (0x5c bytes per voice).
extern "C" char g_mixvoices;      // 0x016e8174
// 0x016f16f4 : audio library free function pointer.
extern "C" void (*g_pFreeFn)(void*);   // 0x016f16f4
// 0x016e7c74 : MPEG-2 LSF scalefactor band-index short table.
extern "C" i16 g_bandTable[];     // 0x016e7c74
// 0x014ce7f4 / 0x014ce814 / 0x014ce834 : allocator tag strings; 0x014ce868 the
// class vftable.  Referenced only by their address.
extern "C" char g_strLowpass[];   // 0x014ce7f4
extern "C" char g_strHighpass[];  // 0x014ce814
extern "C" char g_strUserFilter[];// 0x014ce834
// 0x014ce868 : the class vftable (stored by the deleting destructor).
#define g_vftableAddr ((void*)0x014ce868)

// ---------------------------------------------------------------------------
// Callees (defined in other slices; declarations only)
// ---------------------------------------------------------------------------

// 0x0112c820 / 0x0112c850 : the audio System::Alloc / System::Free pair.  Both
// are __thiscall with the singleton in ECX, loaded from 0x016e61a8 at every use.
void  FUN_01168640(void* p);                                    // 0x1168640
void  FUN_01168670(void* p, void* params);                      // 0x1168670
void  FUN_01168580(void* p);                                    // 0x1168580
void  FUN_011685b0(void* p, void* params);                      // 0x11685b0
void  FUN_011596d0(void* dst, void* src);                       // 0x11596d0
void  FUN_01159710(void* dst, void* src);                       // 0x1159710
int   FUN_011684c0(const void* p, int n);                       // 0x11684c0
extern "C" void* (__cdecl* g_pMemcpy)(void*, const void*, unsigned int);  // 0x015c3848
void  SNDMEMI_alloc(void* p, int size);                         // 0x113ec90
void  FUN_0113fca0(void* p);                                    // 0x113fca0
void* __cdecl operator_new_arr(void* p, int a, int b);          // 0x11e073e

// ===========================================================================
//  MIX_setlowpass  (0x01156960)
// ===========================================================================
// @ 0x01156960
extern "C" void MIX_setlowpass(int voice, float cutoff)
{
    char* v = (char*)&g_mixvoices + voice * 0x5c;
    if (cutoff < *(float*)0x01485720) {
        if (*(void**)(v + 0x54) == 0) {
            char* st = (char*)g_system->Alloc(0x28, g_strLowpass, 0x10, 0);
            *(void**)(v + 0x54) = st;
            *(u32*)(st + 4) = 0;
            *(u16*)(st + 0x18) = 0x28;
            st[0x1a] = 0;
            FUN_01168640(st);
            FUN_011596d0(v + 0x40, *(void**)(v + 0x54));
        }
        float sr = *(float*)((char*)g_system + 0xc0);
        int params[3];
        params[0] = (int)(sr * cutoff) << 7;
        params[1] = (int)sr << 8;
        params[2] = 0x100;
        FUN_01168670(*(void**)(v + 0x54), params);
        return;
    }
    if (*(void**)(v + 0x54) != 0) {
        FUN_01159710(v + 0x40, *(void**)(v + 0x54));
        g_system->Free(*(void**)(v + 0x54), 0);
        *(void**)(v + 0x54) = 0;
    }
}

// ===========================================================================
//  MIX_sethighpass  (0x01156a60)
// ===========================================================================
// @ 0x01156a60
extern "C" void MIX_sethighpass(int voice, int cutoff)
{
    char* v = (char*)&g_mixvoices + voice * 0x5c;
    if (cutoff > 0) {
        if (*(void**)(v + 0x58) == 0) {
            char* st = (char*)g_system->Alloc(0x58, g_strHighpass, 0x10, 0);
            *(void**)(v + 0x58) = st;
            *(u32*)(st + 4) = 0;
            *(u16*)(st + 0x18) = 0x50;
            st[0x1a] = 0;
            FUN_01168580(st);
            FUN_011596d0(v + 0x40, *(void**)(v + 0x58));
        }
        int params[2];
        params[0] = cutoff << 8;
        params[1] = (int)(*(float*)((char*)g_system + 0xc0)) << 8;
        FUN_011685b0(*(void**)(v + 0x58), params);
        return;
    }
    if (*(void**)(v + 0x58) != 0) {
        FUN_01159710(v + 0x40, *(void**)(v + 0x58));
        g_system->Free(*(void**)(v + 0x58), 0);
        *(void**)(v + 0x58) = 0;
    }
}

// ===========================================================================
//  MIX_filteradd  (0x01156b40)
// ===========================================================================
// @ 0x01156b40
extern "C" void MIX_filteradd(int voice, int unused, int* desc)
{
    char* v = (char*)&g_mixvoices + voice * 0x5c;
    char* st = (char*)g_system->Alloc(desc[1], g_strUserFilter, 0x10, 0);
    ((void (__cdecl*)(void*, int, int))desc[3])(st, desc[0], unused);
    *(u16*)(st + 0x18) = *(u16*)((char*)desc + 8);
    *(u32*)st = desc[4];
    *(u32*)(st + 4) = desc[5];
    st[0x1a] = 0;
    FUN_011596d0(v + 0x40, st);
}

// ===========================================================================
//  EALayer3 decoder object
// ===========================================================================
//
// Layout read off the disassembly; identical to slice s011586f0's view.
//   0x00 vftable            0x30 mBitsLeft (bit buffer)   0x1bc mpStreamBase
//   0x14 mPos               0x34 mBitCount                 0x1c0 mBytesLeft
//   0x24 mpRead             0x48 mBands                   0x1c4 mTotalSamples
//   0x54 mpFlags[]          0x58 mEntries[16] (0x18 each) 0x1c8 mFrameSamples
//                                                          0x1cc mFrameOffset
//                                                          0x1d0 mPendingSamples
//                                                          0x1d4 mRequestStream

struct BandEntry {            // 0x30 bytes at this+0x58
    u16  sf;                  // +0x00
    u16  u02;                 // +0x02
    u16  u04;                 // +0x04
    u8   b06;                 // +0x06
    u8   b07;                 // +0x07
    u8   b08;                 // +0x08
    u8   b09;                 // +0x09
    u8   b0a;                 // +0x0a
    u8   b0b;                 // +0x0b
    u8   b0c;                 // +0x0c
    u8   b0d;                 // +0x0d
    u8   b0e;                 // +0x0e
    u8   b0f;                 // +0x0f
    u8   b10;                 // +0x10
    u8   b11;                 // +0x11
    u8   b12;                 // +0x12
    u8   b13;                 // +0x13
    u32  u14;                 // +0x14
    u8   pad18[0x18];
};

class Codec {
public:
    u8   m00[0x24];
    u8*  mRead;              // +0x24
    u8   m28[0x30 - 0x28];
    u32  mBits;              // +0x30
    int  mCnt;               // +0x34

    // ---- bit reader: refill the 32-bit buffer to at least n bits --------
    void Refill(int n)
    {
        while (mCnt < n) {
            u8 b = *mRead;
            u32 term = (u32)b << (0x18 - mCnt);
            mBits |= term;
            mCnt = mCnt + 8;
            mRead = mRead + 1;
        }
    }

// @ 0x01157370
    void AlignBits()
    {
        while (mCnt < 0x18) {
            u8 b = *mRead;
            mBits |= (u32)b << (0x18 - mCnt);
            mCnt = mCnt + 8;
            mRead = mRead + 1;
        }
    }

// @ 0x011573b0
    u32 ReadBits(int n)
    {
        while (mCnt < n) {
            u8 b = *mRead;
            mBits |= (u32)b << (0x18 - mCnt);
            mCnt = mCnt + 8;
            mRead = mRead + 1;
        }
        u32 v = mBits;
        mBits = v << n;
        mCnt -= n;
        return v >> (0x20 - n);
    }
    int  FUN_01156dd0();                 // 0x01156dd0
    int  FUN_01156d70(int a, int b, int c);
    int  FUN_01156df0(int out, int n);
    int  FUN_01157430();
    int  FUN_01157460(int x);
    int  FUN_01163dc0();                 // 0x1163dc0
};

// The decoder's vtable, viewed as an interface so the frame-decode path can make
// its virtual pull calls (slots at +0x08 / +0x10 / +0x18).
struct CodecVt {
    virtual void slot0();
    virtual void slot1();
    virtual int  slot2(int a, int b);    // +0x08
    virtual void slot3();
    virtual void slot4(int a);           // +0x10
    virtual void slot5();
    virtual int  slot6();                // +0x18
};

// @ 0x01156dd0
int Codec::FUN_01156dd0()
{
    *(u32*)((char*)this + 0x1c0) = 0;
    *(u32*)((char*)this + 0x1c4) = 0;
    *(u32*)((char*)this + 0x1c8) = 0;
    *((u8*)this + 0x1d4) = 1;
    return 0;
}

// @ 0x01156d70
int Codec::FUN_01156d70(int a, int b, int c)
{
    int f = *(int*)((char*)this + 0x1c4);
    if (f < 0) {
        if (*(int*)((char*)this + 0x1c0) > 0)
            return -1;
    } else if (f != 0) {
        return -1;
    }
    if (b < 10)
        return -2;
    *(int*)((char*)this + 0x1c0) = b;
    *(int*)((char*)this + 0x1c4) = c;
    *(int*)((char*)this + 0x1bc) = a;
    *(u32*)((char*)this + 0x1c8) = 0;
    return 0;
}

// @ 0x01157430
int Codec::FUN_01157430()
{
    void* p = *(void**)((char*)this + 0x1b8);
    *(void**)this = g_vftableAddr;
    if (p != 0)
        g_pFreeFn(p);
    return FUN_01163dc0();
}

// ===========================================================================
//  FUN_01156bb0  (MPEG header walker, cdecl)
// ===========================================================================
// @ 0x01156bb0
extern "C" int FUN_01156bb0(int* s)
{
    u8* pb = (u8*)*s;
    while (*pb == 0xfc) {
        *s = *s + 1;
        pb = (u8*)*s;
    }
    u32 v = *pb;
    s[1] = (int)v;
    if (v == 0xff)
        return 0;
    *s = (int)(pb + 1);
    if (v != 0xfd && v != 0xfe) {
        u32 w = pb[1];
        s[4] = (int)w;
        if (w == 0xff) {
            s[4] = FUN_011684c0((char*)*s, 4);
            *s = *s + 4;
        }
        *s = *s + 1;
        s[3] = *s;
        if ((u32)s[4] < 5)
            s[2] = FUN_011684c0((void*)*s, s[4]);
        *s = *s + s[4];
    }
    return 1;
}

// ===========================================================================
//  FUN_01156c40  (init header + scalefactor index, cdecl)
// ===========================================================================
// @ 0x01156c40
extern "C" void FUN_01156c40(void* self, int a, u8* b, char* c, int* d)
{
    char* v = (char*)c;                    // param_4
    SNDMEMI_alloc(b, 4);
    SNDMEMI_alloc(v, 100);
    SNDMEMI_alloc(d, 0x1c);
    FUN_0113fca0(v);

    int hdr[0x33];
    hdr[0] = a + 8;
    hdr[4] = 1;
    hdr[8] = 0xbb80;
    hdr[9] = 0;
    hdr[0x30] = 10;
    u8* packet = (u8*)hdr;

    if (FUN_01156bb0(hdr) != 0) {
        int* q = (int*)(v + 0x54);
        for (;;) {
            int t = hdr[3];
            if (t < 0x2b) {
                if (t == 0x14) {
                    q[-4] = hdr[5];
                    q[0] = hdr[6];
                    q += 1;
                }
            } else if ((u32)(t - 0x80) < 0x2e) {
                hdr[4 + (t - 0x80)] = hdr[5];
            } else if (t == 0xfe) {
                break;
            }
            if (FUN_01156bb0(hdr) == 0)
                break;
        }
    }
    b[2] = (u8)hdr[4];
    b[3] = (u8)hdr[0x30];
    *(u16*)b = (u16)hdr[8];
    *d = hdr[9];
    v[6] = 2;
    if (b[2] != 0) {
        u16* dst = (u16*)(v + 8);
        int i = 0;
        do {
            *dst = g_bandTable[i + (u32)b[2] * 6];
            i += 1;
            dst += 1;
        } while (i < (int)(u32)b[2]);
    }
}

// ===========================================================================
//  FUN_01157460  (band header parse)
// ===========================================================================
// @ 0x01157460
int Codec::FUN_01157460(int x)
{
    char* base = (char*)this;
    u8 nbands = *(u8*)(base + 0x48);
    if (*(char*)(base + 0x3b) == 0) {
        if (x == 1) {
            AlignBits();
            int i = 0;
            if (nbands != 0) {
                do {
                    char* e = (char*)*(void**)(base + 0x54) + 4 + i * 4;
                    u32 bits = *(u32*)(base + 0x30);
                    e[0] = (u8)(bits >> 0x1f);
                    e[1] = (u8)(bits >> 0x1e) & 1;
                    e[2] = (u8)(bits >> 0x1d) & 1;
                    e[3] = (u8)(bits >> 0x1c) & 1;
                    *(u32*)(base + 0x30) = bits << 4;
                    *(int*)(base + 0x34) += -4;
                    i += 1;
                } while (i < (int)(u32)nbands);
            }
        }
        int bi = 0;
        if (nbands == 0)
            return 1;
        BandEntry* e = (BandEntry*)(base + 0x58 + x * 0x18);
        do {
            u32 bits;
            e->sf = (u16)ReadBits(0xc);
            Refill(0x18);
            bits = *(u32*)(base + 0x30);
            e->u02 = (u16)(bits >> 0x17);
            e->b06 = (u8)(bits >> 0xf);
            e->u04 = (u16)((bits >> 0xb) & 0xf);
            e->b07 = (u8)(bits >> 10) & 1;
            *(u32*)(base + 0x30) = bits << 0x16;
            *(int*)(base + 0x34) += -0x16;
            Refill(0x18);
            bits = *(u32*)(base + 0x30);
            if (e->b07 == 0) {
                e->b0c = (u8)(bits >> 0x1b);
                e->b0d = (u8)(bits >> 0x16) & 0x1f;
                e->b0e = (u8)(bits >> 0x11) & 0x1f;
                e->b0a = (u8)(bits >> 0xd) & 0xf;
                e->b0b = (u8)(bits >> 10) & 7;
                e->b08 = 0;
            } else {
                e->b08 = (u8)(bits >> 0x1e);
                e->b09 = (u8)(bits >> 0x1d) & 1;
                e->b0c = *(u8*)(base + 0x33) & 0x1f;
                e->b0d = (u8)(bits >> 0x13) & 0x1f;
                e->b10 = *(u8*)(base + 0x32) & 7;
                e->b11 = (u8)(bits >> 0xd) & 7;
                e->b12 = (u8)(bits >> 10) & 7;
                if (e->b08 == 0)
                    return 0;
                if (e->b08 == 2 && e->b09 == 0) {
                    e->b0a = 8;
                    e->b0b = 0x14 - e->b0a;
                } else {
                    e->b0a = 7;
                    e->b0b = 0x14 - e->b0a;
                }
            }
            bits = *(u32*)(base + 0x30);
            e->b0e = (u8)(bits >> 9) & 1;
            e->b06 = (u8)((bits >> 8) & 1);
            e->b0f = (u8)(bits >> 7) & 1;
            *(u32*)(base + 0x30) = bits << 0x19;
            *(int*)(base + 0x34) += -0x19;
            bi += 1;
            e = (BandEntry*)((char*)e + 0x30);
        } while (bi < (int)(u32)nbands);
        return 1;
    }
    int i = 0;
    if (nbands != 0) {
        char* p = base + 0x5e;
        do {
            *(u16*)(p - 6) = (u16)ReadBits(0xc);
            *(u16*)(p - 4) = (u16)ReadBits(9);
            *p = (u8)ReadBits(8);
            *(u16*)(p - 2) = (u16)ReadBits(9);
            p[1] = (u8)ReadBits(1);
            if (p[1] == 0) {
                p[6] = (u8)ReadBits(5);
                p[7] = (u8)ReadBits(5);
                p[8] = (u8)ReadBits(5);
                p[4] = (u8)ReadBits(4);
                p[5] = (u8)ReadBits(3);
                p[2] = 0;
            } else {
                p[2] = (u8)ReadBits(2);
                p[3] = (u8)ReadBits(1);
                p[6] = (u8)ReadBits(5);
                p[7] = (u8)ReadBits(5);
                p[0xa] = (u8)ReadBits(3);
                p[0xb] = (u8)ReadBits(3);
                p[0xc] = (u8)ReadBits(3);
                if (p[2] == 0)
                    return 0;
                if (p[2] == 2 && p[3] == 0) {
                    p[4] = 8;
                } else {
                    p[4] = 7;
                    p[5] = 0xd;
                }
            }
            *(u32*)(p + 0xe) = ReadBits(1);
            p[9] = (u8)ReadBits(1);
            i += 1;
            p += 0x30;
        } while (i < (int)(u32)nbands);
    }
    return 1;
}


// ===========================================================================
//  FUN_01156df0  (decode one EALayer3 frame)
// ===========================================================================
// `out` is an array of mBands output pointers (one per channel/interleave slot);
// each channel's block is memcpy'd out from the 0x240-float-stride stream buffer.
// @ 0x01156df0
int Codec::FUN_01156df0(int out, int n)
{
    char* base = (char*)this;
    int* p = (int*)this;
    int total = p[0x1c4 / 4];              // mTotalSamples
    if (total >= 0) {
        if (total == 0)
            return 0;
        if (total < n)
            n = total;
    }
    int done = 0;
    int off = 0;                            // running output element offset
    for (;;) {
        if (n < 1)
            return done;
        if (p[0x1c8 / 4] == 0) {            // mFrameSamples
            if (p[0x1c0 / 4] == 0)          // mBytesLeft
                return done;
            int cnt = p[0x1bc / 4] + 1;     // mpStream + 1
            if (*((u8*)base + 0x1d4) != 0) {
                ((CodecVt*)this)->slot2(cnt, 0);
                p[0x1d0 / 4] = 0x451;
                *((u8*)base + 0x1d4) = 0;
            } else {
                ((CodecVt*)this)->slot4(cnt);
            }
            int r = ((CodecVt*)this)->slot6();
            if (r < 0 && p[0x1b8 / 4] != 0)
                operator_new_arr((void*)p[0x1b8 / 4], 0, p[3]);
            p[0x1c0 / 4] += -1 - p[5];
            p[0x1bc / 4] += p[5] + 1;
            u32 frame = (u32)p[3] / ((u32)*((u8*)base + 0x48) * 4);
            char* sp = (char*)p[0x1bc / 4];
            p[0x1cc / 4] = 0;
            p[0x1c8 / 4] = (int)frame;
            if (*sp == (char)0xee) {
                u8 c0 = sp[1];
                u8 c1 = sp[2];
                p[0x1bc / 4] = (int)(sp + 2);
                int v0 = (int)(i16)(u16)((c0 << 8) | c1);
                u8 c2 = sp[4];
                u8 c3 = sp[3];
                p[0x1bc / 4] = (int)(sp + 4);
                int nsamp = (int)(i16)(u16)((c3 << 8) | c2);
                float* dst = (float*)(p[0x1b8 / 4] + ((int)frame - v0) * 4);
                int got = 0;
                if (*((u8*)base + 0x48) == 2) {
                    if (nsamp > 3) {
                        int it = ((u32)(nsamp - 4) >> 2) + 1;
                        got = it * 4;
                        do {
                            char* q;
                            q = (char*)p[0x1bc / 4];
                            dst[0] = (float)(int)(i16)(u16)((q[1] << 8) | q[2]);
                            q = (char*)p[0x1bc / 4];
                            dst[0x240] = (float)(int)(i16)(u16)((q[3] << 8) | q[4]);
                            p[0x1bc / 4] += 4;
                            q = (char*)p[0x1bc / 4];
                            dst[1] = (float)(int)(i16)(u16)((q[1] << 8) | q[2]);
                            q = (char*)p[0x1bc / 4];
                            dst[0x241] = (float)(int)(i16)(u16)((q[3] << 8) | q[4]);
                            p[0x1bc / 4] += 4;
                            q = (char*)p[0x1bc / 4];
                            dst[2] = (float)(int)(i16)(u16)((q[1] << 8) | q[2]);
                            q = (char*)p[0x1bc / 4];
                            dst[0x242] = (float)(int)(i16)(u16)((q[3] << 8) | q[4]);
                            p[0x1bc / 4] += 4;
                            q = (char*)p[0x1bc / 4];
                            dst[3] = (float)(int)(i16)(u16)((q[1] << 8) | q[2]);
                            q = (char*)p[0x1bc / 4];
                            dst[0x243] = (float)(int)(i16)(u16)((q[3] << 8) | q[4]);
                            p[0x1bc / 4] += 4;
                            dst += 4;
                            it -= 1;
                        } while (it != 0);
                    }
                    if (got < nsamp) {
                        int rem = nsamp - got;
                        do {
                            char* q;
                            q = (char*)p[0x1bc / 4];
                            dst[0] = (float)(int)(i16)(u16)((q[1] << 8) | q[2]);
                            q = (char*)p[0x1bc / 4];
                            dst[0x240] = (float)(int)(i16)(u16)((q[3] << 8) | q[4]);
                            p[0x1bc / 4] += 4;
                            dst += 1;
                            rem -= 1;
                        } while (rem != 0);
                    }
                } else {
                    if (nsamp > 3) {
                        int it = ((u32)(nsamp - 4) >> 2) + 1;
                        got = it * 4;
                        do {
                            char* q;
                            q = (char*)p[0x1bc / 4];
                            dst[0] = (float)(int)(i16)(u16)((q[1] << 8) | q[2]);
                            p[0x1bc / 4] = (int)(q + 2);
                            q = (char*)p[0x1bc / 4];
                            dst[1] = (float)(int)(i16)(u16)((q[1] << 8) | q[2]);
                            p[0x1bc / 4] = (int)(q + 2);
                            q = (char*)p[0x1bc / 4];
                            dst[2] = (float)(int)(i16)(u16)((q[1] << 8) | q[2]);
                            p[0x1bc / 4] = (int)(q + 2);
                            q = (char*)p[0x1bc / 4];
                            dst[3] = (float)(int)(i16)(u16)((q[1] << 8) | q[2]);
                            p[0x1bc / 4] = (int)(q + 2);
                            dst += 4;
                            it -= 1;
                        } while (it != 0);
                    }
                    if (got < nsamp) {
                        int rem = nsamp - got;
                        do {
                            char* q;
                            q = (char*)p[0x1bc / 4];
                            dst[0] = (float)(int)(i16)(u16)((q[1] << 8) | q[2]);
                            p[0x1bc / 4] = (int)(q + 2);
                            dst += 1;
                            rem -= 1;
                        } while (rem != 0);
                    }
                }
                p[0x1c0 / 4] += (int)((u32)*((u8*)base + 0x48) * nsamp * -2 - 5);
                p[0x1bc / 4] = (int)(sp + (u32)*((u8*)base + 0x48) * nsamp * 2 + 5);
            }
        }
        int pend = p[0x1d0 / 4];
        if (pend > 0) {
            int fs = p[0x1c8 / 4];
            if (fs <= pend) {
                p[0x1d0 / 4] = pend - fs;
                p[0x1c8 / 4] = 0;
            } else {
                p[0x1cc / 4] += pend;
                p[0x1c8 / 4] = fs - pend;
                p[0x1d0 / 4] = 0;
            }
        }
        int fs = p[0x1c8 / 4];
        if (fs > 0) {
            int cnt = fs;
            if (cnt > n)
                cnt = n;
            int k = 0;
            if (*((u8*)base + 0x48) != 0) {
                do {
                    void* dstv = (void*)(*(int*)(out + k * 4) + off * 4);
                    void* srcv = (void*)(p[0x1b8 / 4] + (p[0x1cc / 4] + k * 0x240) * 4);
                    g_pMemcpy(dstv, srcv, (u32)cnt * 4);
                    k += 1;
                } while (k < (int)(u32)*((u8*)base + 0x48));
            }
            p[0x1cc / 4] += cnt;
            p[0x1c8 / 4] -= cnt;
            if (p[0x1c4 / 4] >= 0)
                p[0x1c4 / 4] -= cnt;
            off += cnt;
            n -= cnt;
            done += cnt;
        }
        if (n < 1)
            return done;
    }
}
