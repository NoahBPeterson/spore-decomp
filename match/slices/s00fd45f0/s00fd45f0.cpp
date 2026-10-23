// Slice s00fd45f0 -- On2 VP6 decoder setup: frame header, buffer management and
// Huffman table construction.
//
//  0x00fd45f0  read the frame header / initialise the bit reader
//  0x00fd4780  header read wrapper (bool result)
//  0x00fd47a0  zero-filled allocation wrapper
//  0x00fd47c0  release all decoder buffers
//  0x00fd4880  allocate the decoder buffers
//  0x00fd49b0  release the coefficient scan buffers
//  0x00fd4a20  allocate the coefficient scan buffers
//  0x00fd4ad0  recompute geometry / scan tables for the current size
//  0x00fd4cb0  build a canonical Huffman table (128 leaves)
//  0x00fd4e50  expand a 64-entry Huffman lookup table
//  0x00fd4ed0  multiply two 64-entry int16 matrices element-wise
//
// FUN_00fd45f0 receives the decoder object in ESI (whole-program register ABI);
// the reconstruction below passes it as an ordinary argument.

typedef unsigned char byte;

extern "C" unsigned int FUN_00fd4560(int* br, int n);            // 0x00fd4560
extern "C" void     vp6_bitreader_init(void* br, const void* buf); // 0x00fd29d0
extern "C" unsigned int FUN_00fcefe0(void* br, int n);           // 0x00fcefe0
extern "C" int      FUN_00fcef00(void* br, int n);               // 0x00fcef00
extern "C" void     FUN_00fd61f0(void* p);                       // 0x00fd61f0
extern "C" int      FUN_00fd5fc0(int a, int* b);                 // 0x00fd5fc0
extern "C" void     thunk_FUN_00fd29b0(void* p);                 // 0x00fd29b0
extern "C" void*    vp6_alloc(int size);                         // 0x00fd2980

extern "C" const int DAT_01492cf0[];   // frame type -> flags
extern "C" const int DAT_01492b68[];   // scan table pairs (24 ints)

int  FUN_00fd45f0(void* d);
int  FUN_00fd4880(int* p);
int  FUN_00fd4a20(int* p, int extra);
int  FUN_00fd4ad0(int* p);

// @ 0x00fd45f0
int FUN_00fd45f0(void* d)
{
    int* br = (int*)((char*)d + 0xfc);
    unsigned int b4, u6, u8;

    *(byte*)((char*)d + 0x3b62) = (byte)FUN_00fd4560(br, 1);
    b4 = FUN_00fd4560(br, 6);
    u6 = FUN_00fd4560(br, 1);
    *(unsigned int*)((char*)d + 0x328) = u6 & 0xff;

    if (*(char*)((char*)d + 0x3b62) == 0) {
        byte b5 = (byte)FUN_00fd4560(br, 5);
        *(byte*)((char*)d + 0x14c) = b5;
        if (b5 > 7)
            return 0;
        FUN_00fd4560(br, 2);
        u6 = FUN_00fd4560(br, 1);
        *(unsigned int*)((char*)d + 0x160) = u6 & 0xff;
        vp6_bitreader_init((char*)d + 0x10c, (void*)(*br + 4));
        *(unsigned int*)((char*)d + 0xf8) = FUN_00fd4560(br, 0x10);
        u6 = FUN_00fcefe0((char*)d + 0x10c, 8);
        u8 = FUN_00fcefe0((char*)d + 0x10c, 8);
        FUN_00fcefe0((char*)d + 0x10c, 8);
        FUN_00fcefe0((char*)d + 0x10c, 8);
        FUN_00fcefe0((char*)d + 0x10c, 2);
        if ((int)((u6 & 0xff) * 2) != *(int*)((char*)d + 0x178) ||
            (int)((u8 & 0xff) * 2) != *(int*)((char*)d + 0x17c)) {
            *(unsigned int*)((char*)d + 0x150) = (u8 & 0xff) * 0x10;
            *(unsigned int*)((char*)d + 0x154) = (u6 & 0xff) * 0x10;
            FUN_00fd4ad0((int*)d);
        }
    }
    else {
        vp6_bitreader_init((char*)d + 0x10c, (void*)(*br + 3));
        *(unsigned int*)((char*)d + 0xf8) = FUN_00fd4560(br, 0x10);
        *(unsigned int*)((char*)d + 0x32c) = FUN_00fcef00((char*)d + 0x10c, 0x80);
    }

    *(unsigned int*)((char*)d + 0x238c) = FUN_00fcef00((char*)d + 0x10c, 0x80);

    {
        int* dst = *(int**)((char*)d + 0xf4);
        dst[0] = (int)(b4 & 0xff);
        dst[1] = DAT_01492cf0[b4 & 0xff];
        FUN_00fd61f0(dst);
    }
    return 1;
}

// @ 0x00fd4780
int FUN_00fd4780(void* d)
{
    if (FUN_00fd45f0(d) == 0)
        return 0;
    return 1;
}

// @ 0x00fd47a0
__declspec(noinline) void* FUN_00fd47a0(int size, int zero)
{
    (void)zero;
    return vp6_alloc(size);
}

// @ 0x00fd47c0
__declspec(noinline) void FUN_00fd47c0(int* p)
{
    if (p[0] != 0)
        thunk_FUN_00fd29b0((void*)p[0]);
    p[0] = 0;
    p[1] = 0;
    if (p[0x34] != 0)
        thunk_FUN_00fd29b0((void*)p[0x34]);
    p[0x34] = 0;
    p[0x31] = 0;
    if (p[0x35] != 0)
        thunk_FUN_00fd29b0((void*)p[0x35]);
    p[0x35] = 0;
    p[0x32] = 0;
    if (p[0x36] != 0)
        thunk_FUN_00fd29b0((void*)p[0x36]);
    p[0x36] = 0;
    p[0x33] = 0;
    if (p[0xd7] != 0)
        thunk_FUN_00fd29b0((void*)p[0xd7]);
    p[0xd7] = 0;
    p[0xd6] = 0;
    if (p[0xd5] != 0)
        thunk_FUN_00fd29b0((void*)p[0xd5]);
    p[0xd5] = 0;
    p[0xd4] = 0;
}

// @ 0x00fd4880
__declspec(noinline) int FUN_00fd4880(int* p)
{
    int v;

    FUN_00fd47c0(p);
    v = (int)FUN_00fd47a0(800, 0);
    p[0] = v;
    if (v == 0) {
        FUN_00fd47c0(p);
        return 0;
    }
    p[1] = (int)(((unsigned int)v + 0x1f) & 0xffffffe0);
    v = (int)FUN_00fd47a0((p[0x5f] + 10) * 0x10, 0);
    p[0x34] = v;
    if (v == 0) {
        FUN_00fd47c0(p);
        return 0;
    }
    p[0x31] = (int)(((unsigned int)v + 0x1f) & 0xffffffe0);
    v = (int)FUN_00fd47a0((((unsigned int)p[0x5f] >> 1) + 10) * 0x10, 0);
    p[0x35] = v;
    if (v == 0) {
        FUN_00fd47c0(p);
        return 0;
    }
    p[0x32] = (int)(((unsigned int)v + 0x1f) & 0xffffffe0);
    v = (int)FUN_00fd47a0((((unsigned int)p[0x5f] >> 1) + 10) * 0x10, 0);
    p[0x36] = v;
    if (v == 0) {
        FUN_00fd47c0(p);
        return 0;
    }
    p[0x33] = (int)(((unsigned int)v + 0x1f) & 0xffffffe0);
    v = (int)FUN_00fd47a0(p[0x69] + 0x20, 0);
    p[0xd5] = v;
    if (v == 0) {
        FUN_00fd47c0(p);
        return 0;
    }
    p[0xd4] = (int)(((unsigned int)v + 0x1f) & 0xffffffe0);
    v = (int)FUN_00fd47a0(p[0x69] * 4 + 0x20, 0);
    p[0xd7] = v;
    if (v == 0) {
        FUN_00fd47c0(p);
        return 0;
    }
    p[0xd6] = (int)(((unsigned int)v + 0x1f) & 0xffffffe0);
    return 1;
}

// @ 0x00fd49b0
__declspec(noinline) void FUN_00fd49b0(int* p)
{
    if (p[0x6c] != 0)
        thunk_FUN_00fd29b0((void*)p[0x6c]);
    if (p[0x6d] != 0)
        thunk_FUN_00fd29b0((void*)p[0x6d]);
    if (p[0x6e] != 0)
        thunk_FUN_00fd29b0((void*)p[0x6e]);
    p[0x6c] = 0;
    p[0x6d] = 0;
    p[0x6e] = 0;
    p[0x6f] = 0;
    p[0x70] = 0;
    p[0x71] = 0;
}

// @ 0x00fd4a20
__declspec(noinline) int FUN_00fd4a20(int* p, int extra)
{
    int v;

    FUN_00fd49b0(p);
    v = (int)FUN_00fd47a0(extra + 0x20 + p[0x56], 0);
    p[0x6c] = v;
    if (v == 0) {
        FUN_00fd49b0(p);
        return 0;
    }
    p[0x6f] = (int)(((unsigned int)v + 0x1f) & 0xffffffe0);
    v = (int)FUN_00fd47a0(extra + 0x20 + p[0x56], 0);
    p[0x6d] = v;
    if (v == 0) {
        FUN_00fd49b0(p);
        return 0;
    }
    p[0x70] = (int)(((unsigned int)v + 0x1f) & 0xffffffe0);
    v = (int)FUN_00fd47a0(extra + 0x20 + p[0x56], 0);
    p[0x6e] = v;
    if (v == 0) {
        FUN_00fd49b0(p);
        return 0;
    }
    p[0x71] = (int)(((unsigned int)v + 0x1f) & 0xffffffe0);
    return 1;
}

// @ 0x00fd4ad0
int FUN_00fd4ad0(int* p)
{
    unsigned int u4 = (unsigned int)p[0x55];   // +0x154 height
    unsigned int u3 = (unsigned int)p[0x54];   // +0x150 width
    unsigned int u8, u7, u2;
    int i5, ih, iw;
    unsigned int off;
    int* o;

    u8 = u3 * u4;
    p[0x5d] = (int)(u8 >> 2);                  // +0x174
    p[0x5f] = (int)(u3 >> 3);                  // +0x17c
    i5 = (int)(u3 + 0x60);
    p[0x5e] = (int)(u4 >> 3);                  // +0x178
    u7 = (u4 + 0x60) * (unsigned int)i5;
    p[0x57] = i5 / 2;                          // +0x15c
    u2 = u7 >> 2;
    p[0x56] = i5;                              // +0x158
    p[0x61] = (int)u2;                         // +0x184
    p[0x67] = (int)(u2 + u7);                  // +0x19c
    p[0x60] = (int)u7;                         // +0x180
    p[0x66] = (int)u7;                         // +0x198
    ih = ((u4 & 0xf) != 0) + 6 + (int)(u4 >> 4);
    p[0x6a] = ih;                              // +0x1a8
    p[0x5c] = (int)u8;                         // +0x170
    p[0x62] = 0;                               // +0x188
    p[0x63] = (int)u8;                         // +0x18c
    iw = ((u3 & 0xf) != 0) + 6 + (int)(u3 >> 4);
    p[0x6b] = iw;                              // +0x1ac
    p[0x64] = (int)((u8 >> 2) + u8);           // +0x190
    p[0x65] = 0;                               // +0x194
    p[0x69] = iw * ih;                         // +0x1a4

    off = 0;
    o = (int*)((char*)p + 0x2ec);
    do {
        const int* t = (const int*)((const char*)DAT_01492b68 + off);
        o[-1] = t[0] * p[0x6b] + t[1];
        o[0]  = t[2] * p[0x6b] + t[3];
        o[1]  = t[4] * p[0x6b] + t[5];
        o[2]  = t[6] * p[0x6b] + t[7];
        o[3]  = t[8] * p[0x6b] + t[9];
        o[4]  = t[10] * p[0x6b] + t[11];
        off += 0x30;
        o += 6;
    } while (off < 0x60);

    FUN_00fd5fc0(p[0x52], p + 0x54);             // +0x148, +0x150
    if (FUN_00fd4880(p) != 0) {
        if (FUN_00fd4a20(p, (int)(u7 + u2 * 2)) != 0)
            return 1;
        FUN_00fd47c0(p);
    }
    return 0;
}

// @ 0x00fd4cb0
void FUN_00fd4cb0(void* param_1, int* param_2, int param_3)
{
    int t[192];
    int local_308 = param_3 - 1;
    int local_304 = 0;
    int local_30c;
    int i, iv8, iv3, iv6, iv7, iv2;
    int* pi;
    byte* pu;

    if (param_3 > 0) {
        for (i = 0; i < param_3; i++) {
            t[i * 3 + 2] = ((i * 2 ^ t[i * 3 + 2]) & 0xfe ^ t[i * 3 + 2]) | 1;
            if (param_2[i] == 0)
                param_2[i] = 1;
            t[i * 3 + 1] = param_2[i];
            t[i * 3 + 0] = -1;
        }
    }

    iv8 = 1;
    local_30c = param_3;
    i = 0;
    if (param_3 > 1) {
        pi = t;
        do {
            pi += 3;
            i = local_304;
            iv3 = iv8;
            if (local_304 != -1) {
                iv6 = local_304;
                do {
                    iv7 = i;
                    i = iv7;
                    if (pi[1] <= t[iv7 * 3 + 1])
                        break;
                    i = t[iv7 * 3];
                    iv6 = iv7;
                } while (i != -1);
                if (i != local_304) {
                    t[iv6 * 3] = iv8;
                    iv3 = local_304;
                }
            }
            local_304 = iv3;
            *pi = i;
            iv8++;
            i = local_304;
        } while (iv8 < param_3);
    }

    if (t[i * 3] != -1) {
        pi = t + param_3 * 3;
        pu = (byte*)param_1 + 8 + local_308 * 0xc;
        do {
            iv8 = t[i * 3];
            iv3 = t[i * 3 + 1];
            iv7 = t[iv8 * 3 + 1] + iv3;
            *(int*)(pu - 0x14) = t[i * 3 + 2];
            *(int*)(pu - 0x10) = t[iv8 * 3 + 2];
            local_308--;
            pi[1] = iv7;
            *pi = -1;
            pu[-0xc] = (byte)((iv3 << 8) / iv7);
            pi[2] = ((local_308 & 0x7f) * 2) | (pi[2] & 0xffffff00);
            iv8 = t[iv8 * 3];
            iv3 = iv8;
            i = local_30c;
            iv6 = iv8;
            if (iv8 != -1) {
                do {
                    iv2 = iv3;
                    iv3 = iv2;
                    if (iv7 <= t[iv2 * 3 + 1])
                        break;
                    iv3 = t[iv2 * 3];
                    iv6 = iv2;
                } while (iv3 != -1);
                if (iv3 != iv8) {
                    t[iv6 * 3] = local_30c;
                    i = iv8;
                }
            }
            local_30c++;
            *pi = iv3;
            pi += 3;
            pu -= 0xc;
        } while (t[i * 3] != -1);
    }
}

// @ 0x00fd4e50
void FUN_00fd4e50(const unsigned int* tree, unsigned short* out)
{
    int i;
    int k;

    for (i = 0; i < 64; i++) {
        unsigned int v = 0;
        unsigned int s = 0;
        int n = 6;

        do {
            n--;
            s++;
            v = (v >> 1) & 0x7f;
            if (((i >> n) & 1) == 0)
                v = tree[v * 3 + 0];
            else
                v = tree[v * 3 + 1];
        } while ((v & 1) == 0 && n > 0);

        out[i] = (unsigned short)(((((v >> 1) & 0x7f) | (s << 11)) * 2) | (v & 1));
    }
}

// @ 0x00fd4ed0
void FUN_00fd4ed0(const short* a, const short* b, int* o)
{
    o[0x00] = (int)a[0] * (int)b[0];
    o[0x01] = (int)a[1] * (int)b[1];
    o[0x08] = (int)a[2] * (int)b[2];
    o[0x10] = (int)a[3] * (int)b[3];
    o[0x09] = (int)a[4] * (int)b[4];
    o[0x02] = (int)a[5] * (int)b[5];
    o[0x03] = (int)a[6] * (int)b[6];
    o[0x0a] = (int)a[7] * (int)b[7];
    o[0x11] = (int)a[8] * (int)b[8];
    o[0x18] = (int)a[9] * (int)b[9];
    o[0x20] = (int)a[10] * (int)b[10];
    o[0x19] = (int)a[11] * (int)b[11];
    o[0x12] = (int)a[12] * (int)b[12];
    o[0x0b] = (int)a[13] * (int)b[13];
    o[0x04] = (int)a[14] * (int)b[14];
    o[0x05] = (int)a[15] * (int)b[15];
    o[0x0c] = (int)a[16] * (int)b[16];
    o[0x13] = (int)a[17] * (int)b[17];
    o[0x1a] = (int)a[18] * (int)b[18];
    o[0x21] = (int)a[19] * (int)b[19];
    o[0x28] = (int)a[20] * (int)b[20];
    o[0x30] = (int)a[21] * (int)b[21];
    o[0x29] = (int)a[22] * (int)b[22];
    o[0x22] = (int)a[23] * (int)b[23];
    o[0x1b] = (int)a[24] * (int)b[24];
    o[0x14] = (int)a[25] * (int)b[25];
    o[0x0d] = (int)a[26] * (int)b[26];
    o[0x06] = (int)a[27] * (int)b[27];
    o[0x07] = (int)a[28] * (int)b[28];
    o[0x0e] = (int)a[29] * (int)b[29];
    o[0x15] = (int)a[30] * (int)b[30];
    o[0x1c] = (int)a[31] * (int)b[31];
    o[0x23] = (int)a[32] * (int)b[32];
    o[0x2a] = (int)a[33] * (int)b[33];
    o[0x31] = (int)a[34] * (int)b[34];
    o[0x38] = (int)a[35] * (int)b[35];
    o[0x39] = (int)a[36] * (int)b[36];
    o[0x32] = (int)a[37] * (int)b[37];
    o[0x2b] = (int)a[38] * (int)b[38];
    o[0x24] = (int)a[39] * (int)b[39];
    o[0x1d] = (int)a[40] * (int)b[40];
    o[0x16] = (int)a[41] * (int)b[41];
    o[0x0f] = (int)a[42] * (int)b[42];
    o[0x17] = (int)a[43] * (int)b[43];
    o[0x1e] = (int)a[44] * (int)b[44];
    o[0x25] = (int)a[45] * (int)b[45];
    o[0x2c] = (int)a[46] * (int)b[46];
    o[0x33] = (int)a[47] * (int)b[47];
    o[0x3a] = (int)a[48] * (int)b[48];
    o[0x3b] = (int)a[49] * (int)b[49];
    o[0x34] = (int)a[50] * (int)b[50];
    o[0x2d] = (int)a[51] * (int)b[51];
    o[0x26] = (int)a[52] * (int)b[52];
    o[0x1f] = (int)a[53] * (int)b[53];
    o[0x27] = (int)a[54] * (int)b[54];
    o[0x2e] = (int)a[55] * (int)b[55];
    o[0x35] = (int)a[56] * (int)b[56];
    o[0x3c] = (int)a[57] * (int)b[57];
    o[0x3d] = (int)a[58] * (int)b[58];
    o[0x36] = (int)a[59] * (int)b[59];
    o[0x2f] = (int)a[60] * (int)b[60];
    o[0x37] = (int)a[61] * (int)b[61];
    o[0x3e] = (int)a[62] * (int)b[62];
    o[0x3f] = (int)a[63] * (int)b[63];
}
