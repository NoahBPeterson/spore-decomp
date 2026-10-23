// Slice s00fcf130 -- MPEG-audio layer-3 Huffman / scalefactor bitstream reader.
//
//  0x00fcf130  bit reader refill (range coder step)
//  0x00fcf1b0  accumulate one Huffman-coded value into a coefficient pair
//  0x00fcf230  table-driven Huffman symbol decode (3-register entry, see note)
//  0x00fcf330  granule side-info: scalefactor counts / big-values
//  0x00fcf600  read 2-bit + 2-bit window-switching selector
//  0x00fcf660  decode one Huffman table selector (region 0/1)
//  0x00fcf770  decode the two granule short-block subblock gains
//  0x00fcf9a0  pick the Huffman table for one sf band (count/difference state)
//  0x00fcfab0  dequantise one sf band through the sample-format dispatch table
//  0x00fcfbb0  dequantise a whole granule in the current sample format
//  0x00fcfc70  decode one granule's side info and dequantise it
//
// The original module was built with a whole-program optimiser that passes
// FUN_00fcf230's table base in EAX and its table pointer in EBX; the readable
// reconstruction below passes them as ordinary arguments.

typedef unsigned char byte;
#include <string.h>

// ---------------------------------------------------------------- bit readers
// Reader A (+0x04 range, +0x08 value, +0x0c bits, +0x10 pos, +0x14 buf)
struct BitReaderA {
    int    m_00;
    unsigned m_04;
    unsigned m_08;
    int    m_0c;
    int    m_10;
    byte*  m_14;
};

// Reader B (+0x00 bits, +0x04 bit buffer, +0x08 byte cursor)
struct BitReader {
    int    m_00;
    unsigned m_04;
    byte*  m_08;
};

// ------------------------------------------------------------------ externals
extern "C" int  FUN_00fcef00(int reader, int bit);          // 0xfcef00  get bit
extern "C" int  FUN_00fcef80(int reader);                    // 0xfcef80  get bit
extern "C" int  FUN_00fcf080(BitReader* r, int n);           // 0xfcf080  get n bits
extern "C" int  FUN_00fcf0e0(BitReader* r);                  // 0xfcf0e0  get 1 bit
extern "C" byte FUN_00fd36c0(int p, short* dst, int flag,
                             byte* a4, byte* a5);            // 0xfd36c0  plain PCM

extern "C" int  DAT_014921f0[];      // Huffman symbol value table
extern "C" int  DAT_01492220[];      // sf-band group base table
extern "C" int  DAT_014923a8[];      // sf-band type table (byte view in places)
extern "C" int  DAT_01492cc8[];      // sample-format flags
extern "C" byte DAT_014931f0[];      // sf-band -> pcm format table

extern "C" void (*DAT_016d9580)(int, int, int, int, int, int, int);
extern "C" void (*DAT_016d9584)(int, int, int, int, int);
extern "C" void (*DAT_016d9684)(int, int, int);
extern "C" void (*DAT_016d968c)(int, int, int, int);
extern "C" void (*DAT_016d9690)(int, int, int, int);
extern "C" void (*DAT_016d95ac)(int, int, int);
extern "C" void (*DAT_016d958c)(int, int, int);
extern "C" void (*DAT_016d941c)(int, int, int);

// @ 0x00fcf130
bool FUN_00fcf130(BitReaderA* s, int n)
{
    unsigned range = s->m_04;
    unsigned value = s->m_08;
    int      bits  = s->m_0c;
    unsigned inc   = (((range - 1) * (unsigned)n) >> 8) + 1;
    bool     ok;

    if ((inc << 24) <= value) {
        range -= inc;
        value -= inc << 24;
        ok = true;
    }
    else {
        range = inc;
        ok = false;
    }

    while (range < 0x80) {
        range += range;
        value += value;
        if (--bits == 0) {
            value |= s->m_14[s->m_10];
            s->m_10 = s->m_10 + 1;
            bits = 8;
        }
    }

    s->m_04 = range;
    s->m_08 = value;
    s->m_0c = bits;
    return ok;
}

// @ 0x00fcf1b0
void FUN_00fcf1b0(int p, int band, int coeffs, int reader, int prev)
{
    byte  b  = ((byte*)DAT_014923a8)[*(int*)(p + 0x14)];
    int   acc = 0;
    int   hits = 0;

    if ((unsigned short)b == *(unsigned short*)(prev + 8)) {
        acc = *(short*)(prev + 0xa);
        hits = 1;
    }
    if ((unsigned short)b == *(unsigned short*)(reader + 8)) {
        acc += *(short*)(reader + 0xa);
        hits++;
    }

    short v;
    if (hits == 0)
        v = *(short*)(coeffs + b * 2);
    else if (hits == 2)
        v = (short)(((((unsigned)acc & 0xffff) >> 0xf) + (unsigned)acc) >> 1);
    else
        v = (short)acc;

    short* dst = (short*)(*(int*)(p + 4) + band * 0x80);
    *dst = (short)(*dst + v);
    *(short*)(coeffs + b * 2) = *dst;
}

// @ 0x00fcf230
int FUN_00fcf230(int table, BitReader* r, int groups)
{
    int      bits = r->m_00;
    unsigned idx  = ((1u << (bits & 0x1f)) - 1) & r->m_04;

    if (bits < 6)
        idx = ((unsigned)r->m_08[0] | (idx << 8)) >> ((bits + 2) & 0x1f);
    else
        idx = idx >> ((bits - 6) & 0x1f);

    r->m_00 -= (int)(*(unsigned short*)(table + idx * 2) >> 0xc);
    if (r->m_00 < 0) {
        byte* q = r->m_08;
        r->m_04 = ((unsigned)q[0] << 24) | ((unsigned)q[1] << 16) |
                  ((unsigned)q[2] << 8) | (unsigned)q[3];
        r->m_08 = q + 4;
        r->m_00 += 0x20;
    }

    unsigned code = *(unsigned short*)(table + idx * 2);
    if (code & 1)
        return (int)((code >> 1) & 0x1f);

    unsigned sel = code & 0x3e;
    unsigned bit;
    for (;;) {
        if (r->m_00 == 0) {
            byte* q = r->m_08;
            r->m_04 = ((unsigned)q[0] << 24) | ((unsigned)q[1] << 16) |
                      ((unsigned)q[2] << 8) | (unsigned)q[3];
            r->m_08 = q + 4;
            r->m_00 = 0x1f;
            bit = (unsigned)(q[0] >> 7);
        }
        else {
            int nb = r->m_00 - 1;
            r->m_00 = nb;
            bit = (r->m_04 >> nb) & 1;
        }
        sel = (sel >> 1) & 0x7f;
        sel = *(unsigned*)(groups + (bit != 0 ? 4 : 0) + sel * 0xc);
        if (sel & 1)
            break;
    }
    return (int)((sel >> 1) & 0x7f);
}

// @ 0x00fcf330
byte FUN_00fcf330(int p, short* out, int ch)
{
    BitReader* r = (BitReader*)(p + 0x13c);
    int* count = (int*)(p + 0x3790 + ch * 4);
    int  n = *count;
    byte ret;
    int  k = 0;

    if (n > 0) {
        *count = n - 1;
        ret = 0;
    }
    else {
        int base = p + 0x2390 + ch * 0x80;
        int tbl  = p + 0x368 + ch * 0x90;
        int i = FUN_00fcf230(base, r, tbl);

        if (i == 0xb)
            return *(byte*)(p + 0x268);

        if (i == 0) {
            int x = FUN_00fcf080(r, 2) + 1;
            if (x == 3) {
                *count = FUN_00fcf080(r, 1) + 2;
                ret = 0;
            }
            else {
                if (x == 4) {
                    if (FUN_00fcf0e0(r) != 0) {
                        *count = FUN_00fcf080(r, 6) + 10;
                        ret = 0;
                        goto next;
                    }
                    x = FUN_00fcf080(r, 2) + 7;
                }
                *count = x - 1;
                ret = 0;
            }
        }
        else {
            unsigned val = (unsigned)DAT_014921f0[i];
            if (i > 4) {
                int neb = (i > 9) ? 11 : i - 4;
                val += (unsigned)FUN_00fcf080(r, neb);
            }
            int sgn = FUN_00fcf0e0(r);
            *out = (short)((-sgn ^ (int)val) + sgn);
            ret = (val > 1) ? 2 : 1;
            k = ret;
        }
    }

next:
    {
        int* count2 = (int*)(p + 0x3798 + ch * 4);
        int  m = *count2;
        if (m > 0) {
            *count2 = m - 1;
            return *(byte*)(p + 0x268);
        }
    }

    int i = 1;
    for (;;) {
        int row = DAT_01492220[i] + 6 * (ch + k * 2);
        int v = FUN_00fcf230(p + 0x2490 + row * 0x80, r, p + 0x500 + row * 0x90);

        if (v == 0xb) {
            if (i != 1)
                return *(byte*)(p + 0x267 + i);
            int x = FUN_00fcf080(r, 2) + 1;
            if (x == 3)
                x = FUN_00fcf080(r, 2) + 3;
            else if (x == 4) {
                if (FUN_00fcf0e0(r) != 0)
                    x = FUN_00fcf080(r, 6) + 0xb;
                else
                    x = FUN_00fcf080(r, 2) + 7;
            }
            *(int*)(p + 0x3798 + ch * 4) = x - 1;
            return *(byte*)(p + 0x267 + i);
        }

        if (v == 0) {
            int g = (i >= 6) ? 1 : 0;
            int j = FUN_00fcf230(p + 0x3690 + g * 0x80, r, p + 0x21b0 + g * 0xa8);
            if (j < 8)
                k += j;
            else
                k += FUN_00fcf080(r, 6) + 8;
            ret = 0;
        }
        else {
            unsigned val = (unsigned)DAT_014921f0[v];
            if (v > 4) {
                int neb = (v > 9) ? 11 : v - 4;
                val += (unsigned)FUN_00fcf080(r, neb);
            }
            unsigned bit;
            if (r->m_00 != 0) {
                int nb = r->m_00 - 1;
                r->m_00 = nb;
                bit = (r->m_04 >> nb) & 1;
            }
            else {
                byte* q = r->m_08;
                r->m_04 = ((unsigned)q[0] << 24) | ((unsigned)q[1] << 16) |
                          ((unsigned)q[2] << 8) | (unsigned)q[3];
                r->m_08 = q + 4;
                r->m_00 = 0x1f;
                bit = (unsigned)(q[0] >> 7);
            }
            out[*(byte*)(p + 0x1e8 + i)] = (short)((-(int)bit ^ (int)val) + (int)bit);
            ret = (val > 1) ? 2 : 1;
        }

        i++;
        if (i >= 0x40)
            break;
    }
    return *(byte*)(p + 0x267 + i);
}

// @ 0x00fcf600
int FUN_00fcf600(int p)
{
    int a = FUN_00fcef80(p + 0x10c);
    int b = FUN_00fcef80(p + 0x10c);

    switch (b + a * 2) {
    case 1:  return 2;
    case 2:  return 3;
    case 3:  return 4;
    default: return 0;
    }
}

// @ 0x00fcf660
int FUN_00fcf660(int p, int gr, int ch)
{
    int   r = p + 0x10c;
    int   band = ch * 10 + gr;
    byte* q;

    if (FUN_00fcef00(r, *(byte*)(p + 0x3812 + band)) != 0)
        return gr;

    q = (byte*)(p + 0x383a + band * 9);
    if (FUN_00fcef00(r, q[0]) != 0) {
        if (FUN_00fcef00(r, q[2]) == 0) {
            if (FUN_00fcef00(r, q[5]) != 0)
                return 7;
            return 1;
        }
        if (FUN_00fcef00(r, q[6]) != 0)
            return FUN_00fcef00(r, q[8]) + 8;
        return FUN_00fcef00(r, q[7]) + 5;
    }

    if (FUN_00fcef00(r, q[1]) != 0)
        return FUN_00fcef00(r, q[4]) + 3;
    return FUN_00fcef00(r, q[3]) * 2;
}

// @ 0x00fcf770
void FUN_00fcf770(int p, short* out, int gr)
{
    int r  = p + 0x10c;
    int s0 = 0;
    int s1 = 0;

    if (gr == 2) {
        if (*(int*)(p + 0x50) < 2) {
            s0 = *(short*)(p + 0x48);
            s1 = *(short*)(p + 0x4a);
        }
    }
    else if (*(int*)(p + 0x5c) < 2) {
        s0 = *(short*)(p + 0x54);
        s1 = *(short*)(p + 0x56);
    }

    for (int i = 0; i < 2; i++) {
        int v;
        if (FUN_00fcef00(r, *(byte*)(p + 0x37a2 + i)) == 0) {
            int base = i * 7 + p;
            if (FUN_00fcef00(r, *(byte*)(base + 0x37a4)) == 0) {
                if (FUN_00fcef00(r, *(byte*)(p + (i + 0x7f3) * 7)) == 0) {
                    v = FUN_00fcef00(r, *(byte*)(base + 0x37a6));
                }
                else {
                    v = FUN_00fcef00(r, *(byte*)(base + 0x37a7)) + 2;
                }
            }
            else {
                if (FUN_00fcef00(r, *(byte*)(base + 0x37a8)) == 0) {
                    v = FUN_00fcef00(r, *(byte*)(base + 0x37a9)) + 4;
                }
                else {
                    v = FUN_00fcef00(r, *(byte*)(base + 0x37aa)) + 6;
                }
            }
        }
        else {
            int b = p + i * 8;
            v = FUN_00fcef00(r, *(byte*)(b + 0x37b2)) +
                FUN_00fcef00(r, *(byte*)(b + 0x37b3)) * 2 +
                FUN_00fcef00(r, *(byte*)(b + 0x37b4)) * 4;
            v += FUN_00fcef00(r, *(byte*)(b + 0x37b9)) * 0x80;
            v += FUN_00fcef00(r, *(byte*)(b + 0x37b8)) * 0x40;
            v += FUN_00fcef00(r, *(byte*)(b + 0x37b7)) * 0x20;
            v += FUN_00fcef00(r, *(byte*)(b + 0x37b6)) * 0x10;
            if (v & 0xf0)
                v += FUN_00fcef00(r, *(byte*)(b + 0x37b5)) * 8;
            else
                v += 8;
        }

        if (v != 0) {
            if (FUN_00fcef00(r, *(byte*)(p + 0x37a0 + i)) != 0)
                v = -v;
        }

        if (i == 0)
            out[0] = (short)(s0 + v);
        else
            out[1] = (short)(v + s1);
    }
}

// @ 0x00fcf9a0
void FUN_00fcf9a0(int p, int pos, int ch, byte sel, int* out)
{
    int idx = *(int*)(p + 0x1ac) * pos + ch;
    int found = 0;
    int flag = 1;
    int diffs = 0;
    int i;

    for (i = 0; i < 0xc; i++) {
        int j = *(int*)(p + 0x2e8 + i * 4) + idx;
        if (DAT_014923a8[*(char*)(*(int*)(p + 0x350) + j)] == (int)sel) {
            int t = *(int*)(*(int*)(p + 0x358) + j * 4);
            if (t != 0) {
                flag = 2;
                found = t;
                break;
            }
        }
    }

    for (i = i + 1; i < 0xc; i++) {
        int j = *(int*)(p + 0x2e8 + i * 4) + idx;
        if (DAT_014923a8[*(char*)(*(int*)(p + 0x350) + j)] == (int)sel) {
            int t = *(int*)(*(int*)(p + 0x358) + j * 4);
            if (t != found) {
                if (t != 0) {
                    flag = 0;
                    break;
                }
            }
        }
    }

    if (sel != 1) {
        *(int*)(p + 0x5c) = i;
        *(int*)(p + 0x54) = i;
        *(int*)(p + 0x58) = diffs;
    }
    else {
        *out = flag;
        *(int*)(p + 0x50) = i;
        *(int*)(p + 0x48) = i;
        *(int*)(p + 0x4c) = diffs;
    }
}

// @ 0x00fcfab0
void FUN_00fcfab0(int p, int dst, int ch)
{
    unsigned mask  = (unsigned)*(int*)(p + 0x78);
    int      shift = *(int*)(p + 0x74);
    int      step  = *(int*)(p + 0x7c);
    int      base;

    base = *(int*)(p + 0x1c4);
    if (DAT_014923a8[*(int*)(p + 0x14)] == 2)
        base = *(int*)(p + 0x1c0);

    int x = *(short*)(p + 0x30 + ch * 4);
    int y = *(short*)(p + 0x32 + ch * 4);
    unsigned xm = (unsigned)x & mask;
    unsigned ym = (unsigned)y & mask;

    base += ((((y >> 31) & (int)mask) + y) >> shift) * step;
    base += (((x >> 31) & (int)mask) + x) >> shift;
    base += *(int*)(p + 0x68);

    int diff = 0;
    if (xm != 0) {
        if (*(short*)(p + 0x30 + ch * 4) > 0)
            diff = 1;
        else
            diff = -1;
    }
    if (ym != 0) {
        if (*(short*)(p + 0x32 + ch * 4) > 0)
            diff += step;
        else
            diff -= step;
    }

    if (diff == 0) {
        (*DAT_016d941c)(base, dst, step);
        return;
    }

    if (ch < 4) {
        xm = xm * 2;
        ym = ym * 2;
    }
    (*DAT_016d9580)(base, diff + base, dst, step, (int)xm, (int)ym, 0);
}

// @ 0x00fcfbb0
void FUN_00fcfbb0(int p, int ch)
{
    int fmt = *(int*)(p + 0x14);

    if (fmt == 0) {
        (*DAT_016d9584)(*(int*)(p + 0x1dc),
                        *(int*)(p + 0x1bc) + *(int*)(p + 0x68),
                        *(int*)(p + 0x1c4) + *(int*)(p + 0x68),
                        *(int*)(p + 0x1cc), *(int*)(p + 0x6c));
        return;
    }

    if (DAT_01492cc8[fmt] != 0) {
        FUN_00fcfab0(p, *(int*)(p + 0x1dc), ch);
        (*DAT_016d968c)(*(int*)(p + 0x1dc), *(int*)(p + 0x1cc),
                        *(int*)(p + 0x1bc) + *(int*)(p + 0x68),
                        *(int*)(p + 0x6c));
        return;
    }

    if (fmt != 5) {
        (*DAT_016d9690)(*(int*)(p + 0x1dc),
                        *(int*)(p + 0x1bc) + *(int*)(p + 0x68),
                        *(int*)(p + 0x1cc), *(int*)(p + 0x6c));
        return;
    }

    (*DAT_016d9584)(*(int*)(p + 0x1dc),
                    *(int*)(p + 0x1bc) + *(int*)(p + 0x68),
                    *(int*)(p + 0x1c0) + *(int*)(p + 0x68),
                    *(int*)(p + 0x1cc), *(int*)(p + 0x6c));
}

// @ 0x00fcfc70
void FUN_00fcfc70(int p, int gr, int ch)
{
    int    off = gr * 0x80;
    int    band;
    byte   flags;
    int    fmt;

    if (*(int*)(p + 0x238c) == 0)
        flags = FUN_00fd36c0(p, (short*)(*(int*)(p + 4) + off),
                             *(int*)(p + 0x70) != 0,
                             (byte*)*(int*)(p + 8), (byte*)*(int*)(p + 0xc));
    else
        flags = FUN_00fcf330(p, (short*)(*(int*)(p + 4) + off),
                             *(int*)(p + 0x70) != 0);

    FUN_00fcf1b0(p, gr, *(int*)(p + 0x10), *(int*)(p + 8), *(int*)(p + 0xc));

    *(int*)(*(int*)(p + 0xc) + 4) = *(int*)(p + 0x18 + gr * 4);
    *(int*)(*(int*)(p + 8) + 4) = *(int*)(*(int*)(p + 0xc) + 4);
    *(short*)(*(int*)(p + 0xc) + 0xa) = *(short*)(off + *(int*)(p + 4));
    *(short*)(*(int*)(p + 8) + 0xa) = *(short*)(*(int*)(p + 0xc) + 0xa);
    *(short*)(*(int*)(p + 0xc) + 8) = *(unsigned short*)(&DAT_014923a8[*(int*)(p + 0x14)]);
    *(short*)(*(int*)(p + 8) + 8) = *(short*)(*(int*)(p + 0xc) + 8);

    fmt = DAT_014931f0[gr];
    if (flags < 3 && *(short*)(*(int*)(p + 4) + 2 + off) == 0) {
        (*DAT_016d958c)(*(int*)(p + 4) + off,
                        *(int*)(*(int*)(p + 0xf4) + 0x50 + fmt * 4),
                        *(int*)(p + 0x1cc));
        *(short*)(off + *(int*)(p + 4)) = 0;
        FUN_00fcfbb0(p, gr);
        return;
    }

    if (flags < 0xb) {
        int* d;
        (*DAT_016d95ac)(*(int*)(p + 4) + off,
                        *(int*)(*(int*)(p + 0xf4) + 0x50 + fmt * 4),
                        *(int*)(p + 0x1cc));
        d = (int*)(*(int*)(p + 4) + off);
        d[0] = 0;
        d[1] = 0;
        d[2] = 0;
        d[3] = 0;
        d[4] = 0;
        d[5] = 0;
        d[8] = 0;
        d[9] = 0;
        d[12] = 0;
        d[13] = 0;
        *(short*)(d + 16) = 0;
        FUN_00fcfbb0(p, gr);
        return;
    }

    (*DAT_016d9684)(*(int*)(p + 4) + off,
                    *(int*)(*(int*)(p + 0xf4) + 0x50 + fmt * 4),
                    *(int*)(p + 0x1cc));
    memset((void*)(*(int*)(p + 4) + off), 0, 0x80);
    FUN_00fcfbb0(p, gr);
}
