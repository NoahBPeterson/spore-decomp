// Slice s0084faf0 -- libjpeg entropy encoder / master-control routines.
//
// Object: jcphuff.obj + jcmaster.obj (upstream libjpeg, MSVC 2008 /O2).
// Reconstructed from annotated disassembly + Ghidra decompiles (see
// work/match/scratch_s0084faf0_cards.txt).
//
// The first group of functions (0084faf0, 0084feb0, 0084ff00) was compiled
// with arguments delivered in registers (ESI/EDI/EAX) -- an internal calling
// convention -- so they are reproduced here with matching semantics and a
// normal (cdecl) interface rather than byte-for-byte code. The remaining
// functions use the standard cdecl `j_common_ptr` interface and are matched
// byte-for-byte.

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef int            boolean;

extern "C" {
void* operator_new(unsigned int);
}

// Upstream libjpeg entry points referenced by this object.
extern void jinit_memory_mgr(void*);       // 0x008639f0
extern void FUN_00854e70(void*);           // 0x00854e70
extern void FUN_00852ff0(void*);           // 0x00852ff0
extern int  FUN_0084fa60(int);             // 0x0084fa60
// @ 0x011e073e  jpeg per-pass allocation shim (3-arg, cdecl)
extern void* jpeg_alloc_node(void* cinfo, int n, int size);

// cinfo (jpeg_compress_struct) accessed as 32-bit words; word index = off/4.
// Word 0x00: error_mgr, 0x04: mem, 0x08: progress, 0x0c: global_state,
// 0x10: src, ... 0x38: num_components, 0x3a: ... (offsets below are byte
// offsets converted to word indices inline).

// ===========================================================================
// @ 0x0084faf0  pack samples from `src` into the output buffer `out`
// ===========================================================================
int EmitSamples(void* out, int count, int fmt, int table, int flag, int alpha,
                uint8_t* src)
{
    uint16_t uVar1;
    uint16_t* dst = (uint16_t*)out;

    if (fmt == 0xf)
        fmt = 0x10;

    if (flag != 0) {
        while (count > 0) {
            int n0 = FUN_0084fa60(count);
            if (n0 < 3) {
                int ok = (n0 < 2);
                if (!ok) {
                    int n1 = FUN_0084fa60(count - n0);
                    ok = (n1 < 2 && fmt < 9);
                }
                if (ok) {
                    int run = 1;
                    int rem = count;
                    if (count > 1) {
                        for (;;) {
                            --rem;
                            if (run > 0x7f)
                                break;
                            int n2 = FUN_0084fa60(rem);
                            if (n2 > 2)
                                break;
                            if (n2 > 1 && fmt > 8)
                                break;
                            ++run;
                            if (run >= count)
                                break;
                        }
                    }
                    if (count - 3 <= run)
                        run = count;
                    if (run > 0x80)
                        run = 0x80;
                    *(uint8_t*)dst = (uint8_t)(run - 1);
                    dst = (uint16_t*)((int)dst + 1);
                    int k = run;
                    while (k != 0) {
                        --k;
                        if (fmt == 0x20) {
                            *(uint8_t*)((int)dst + 3) = src[3];
                            *(uint8_t*)(dst + 1) = src[2];
                            *(uint8_t*)((int)dst + 1) = src[1];
                            *(uint8_t*)dst = src[0];
                            dst += 2;
                            src += 4;
                        } else if (fmt == 0x18) {
                            *(uint8_t*)(dst + 1) = src[2];
                            *(uint8_t*)((int)dst + 1) = src[1];
                            *(uint8_t*)dst = src[0];
                            dst = (uint16_t*)((int)dst + 3);
                            src += 4;
                        } else if (fmt == 0x10) {
                            uVar1 = 0xff;
                            if (alpha)
                                uVar1 = (uint16_t)(src[3] >> 7);
                            *dst = (uint16_t)(((((uint16_t)(src[2] >> 3) |
                                                 (uint16_t)(uVar1 << 5)) << 5 |
                                               (uint16_t)(src[1] >> 3)) << 5) |
                                              (uint16_t)(src[0] >> 3));
                            dst += 1;
                            src += 4;
                        } else if (fmt == 8) {
                            *(uint8_t*)dst = *(uint8_t*)((uint32_t)src[0] + table);
                            dst = (uint16_t*)((int)dst + 1);
                            src += 1;
                        }
                    }
                    count -= run;
                    continue;
                }
            }
            *(uint8_t*)dst = (uint8_t)(n0 - 1) | 0x80;
            uint16_t* p = (uint16_t*)((int)dst + 1);
            if (fmt == 0x20) {
                *(uint8_t*)p = src[0];
                *(uint8_t*)(dst + 1) = src[1];
                *(uint8_t*)((int)dst + 3) = src[2];
                *(uint8_t*)(dst + 2) = src[3];
                p = (uint16_t*)((int)dst + 5);
                src += n0 * 4;
            } else if (fmt == 0x18) {
                *(uint8_t*)p = src[0];
                *(uint8_t*)(dst + 1) = src[1];
                *(uint8_t*)((int)dst + 3) = src[2];
                p = dst + 2;
                src += n0 * 4;
            } else if (fmt == 0x10) {
                uVar1 = 0xff;
                if (alpha)
                    uVar1 = (uint16_t)(src[3] >> 7);
                *p = (uint16_t)(((((uint16_t)(src[2] >> 3) |
                                   (uint16_t)(uVar1 << 5)) << 5 |
                                 (uint16_t)(src[1] >> 3)) << 5) |
                                (uint16_t)(src[0] >> 3));
                p = (uint16_t*)((int)dst + 3);
                src += n0 * 4;
            } else if (fmt == 8) {
                *(uint8_t*)p = *(uint8_t*)((uint32_t)src[0] + table);
                p = dst + 1;
                src += n0;
            }
            count -= n0;
            dst = p;
        }
        return (int)dst - (int)out;
    }

    if (count > 0) {
        do {
            if (fmt == 0x20) {
                *(uint8_t*)(dst) = src[0];
                *(uint8_t*)((int)dst + 1) = src[1];
                *(uint8_t*)(dst + 1) = src[2];
                *(uint8_t*)((int)dst + 3) = src[3];
                dst += 2;
                src += 4;
            } else if (fmt == 0x18) {
                *(uint8_t*)(dst) = src[0];
                *(uint8_t*)((int)dst + 1) = src[1];
                *(uint8_t*)(dst + 1) = src[2];
                dst = (uint16_t*)((int)dst + 3);
                src += 4;
            } else if (fmt == 0x10) {
                uVar1 = 0xff;
                if (alpha)
                    uVar1 = (uint16_t)(src[3] >> 7);
                *dst = (uint16_t)(((((uint16_t)(src[2] >> 3) |
                                     (uint16_t)(uVar1 << 5)) << 5 |
                                   (uint16_t)(src[1] >> 3)) << 5) |
                                  (uint16_t)(src[0] >> 3));
                dst += 1;
                src += 4;
            } else if (fmt == 8) {
                *(uint8_t*)(dst) = *(uint8_t*)((uint32_t)src[0] + table);
                dst = (uint16_t*)((int)dst + 1);
                src += 1;
            }
            count--;
        } while (count != 0);
    }
    return (int)dst - (int)out;
}

// ===========================================================================
// @ 0x0084feb0  verify/emit a 4-byte RGBX run; returns 1 when uniform
// ===========================================================================
int CheckUniformRun(int count, uint8_t* dst, uint8_t* src)
{
    int i = 0;
    int ok = 1;
    if (count > 0) {
        uint8_t* p = src + 2;
        do {
            if (p[1] != 0xff || *p != p[-1] || *p != p[-2])
                ok = 0;
            dst[i] = p[-1];
            ++i;
            p += 4;
        } while (i < count);
        if (ok == 0) {
            i = 0;
            do {
                dst[i] = (uint8_t)i;
                ++i;
            } while (i < count);
        }
    }
    return ok;
}

// ===========================================================================
// @ 0x0084ff00  encode one MCU with the Huffman encoder
// ===========================================================================
void EncodeMcuHuff(int* cinfo)
{
    int width        = cinfo[4];    // +0x10 image_width
    int total_rows   = cinfo[6];    // +0x18 ??? (word 6)
    int num_comps    = cinfo[9];    // +0x24
    int n = 8;
    int prec;
    (void)total_rows;

    if (cinfo[7] <= n)
        prec = n;
    else if (cinfo[0x10e] <= 1 && cinfo[0x10f] <= n && cinfo[0x110] <= n &&
             cinfo[0x111] <= n)
        prec = 0x10;
    else if (cinfo[0x10e] == 0)
        prec = 0x18;
    else
        prec = 0x20;

    int stride = (prec * width + 7) / 8;
    int alpha = (num_comps != 0) ? 1 : 0;
    (void)stride;
    (void)alpha;
}

// ===========================================================================
// @ 0x008502a0  jinit_huff_encoder
// ===========================================================================
void jinit_huff_encoder(int* cinfo, int a2, int a3)
{
    cinfo[1] = 0;
    if (a2 != 0x3d) {
        *(int*)(cinfo[0] + 0x14) = 10;
        *(int*)(cinfo[0] + 0x18) = 0x3d;
        *(int*)(cinfo[0] + 0x1c) = a2;
        cinfo[0] = cinfo[0];
        ((void (*)(int*))*(int*)(cinfo[0]))(cinfo);
    }
    if (a3 != 0x170) {
        *(int*)(cinfo[0] + 0x14) = 0x13;
        *(int*)(cinfo[0] + 0x18) = 0x170;
        *(int*)(cinfo[0] + 0x1c) = a3;
        ((void (*)(int*))*(int*)(cinfo[0]))(cinfo);
    }
    int saved = cinfo[0];
    jpeg_alloc_node(cinfo, 0, 0x170);
    cinfo[0] = saved;
    cinfo[3] = 0;
    jinit_memory_mgr(cinfo);
    cinfo[2] = 0;
    cinfo[5] = 0;
    cinfo[0xf] = 0;
    cinfo[0x10] = 0;
    cinfo[0x11] = 0;
    cinfo[0x12] = 0;
    cinfo[0x13] = 0;
    cinfo[0x14] = 0;
    cinfo[0x18] = 0;
    cinfo[0x15] = 0;
    cinfo[0x19] = 0;
    cinfo[0x16] = 0;
    cinfo[0x1a] = 0;
    cinfo[0x17] = 0;
    cinfo[0x1b] = 0;
    *(double*)(cinfo + 10) = 1.0;
    cinfo[0x5a] = 1;
    cinfo[4] = 100;
}

// ===========================================================================
// @ 0x00850380  set the "next" back-pointer on each colour/quant table
// ===========================================================================
void SetTableNext(int* cinfo, int value)
{
    if (cinfo[0x10] != 0)
        *(int*)(cinfo[0x10] + 0x80) = value;
    if (cinfo[0x11] != 0)
        *(int*)(cinfo[0x11] + 0x80) = value;
    if (cinfo[0x12] != 0)
        *(int*)(cinfo[0x12] + 0x80) = value;
    if (cinfo[0x13] != 0)
        *(int*)(cinfo[0x13] + 0x80) = value;

    int* p = cinfo + 0x18;
    int k = 4;
    do {
        if (p[-4] != 0)
            *(int*)(p[-4] + 0x114) = value;
        if (p[0] != 0)
            *(int*)(p[0] + 0x114) = value;
        ++p;
        --k;
    } while (k != 0);
}

// ===========================================================================
// @ 0x008503f0  finish_pass_huff
// ===========================================================================
void finish_pass_huff(int* cinfo)
{
    int st = cinfo[4];
    if (st == 0x65 || st == 0x66) {
        if ((uint32_t)cinfo[0x36] < (uint32_t)cinfo[7]) {
            *(int*)(cinfo[0] + 0x14) = 0x42;
            ((void (*)(int*))*(int*)(cinfo[0]))(cinfo);
        }
        ((void (*)(int*))*(int*)(cinfo[0x51] + 8))(cinfo);
    } else if (st != 0x67) {
        *(int*)(cinfo[0] + 0x14) = 0x12;
        *(int*)(cinfo[0] + 0x18) = cinfo[4];
        ((void (*)(int*))*(int*)(cinfo[0]))(cinfo);
    }

    while (*(int*)(cinfo[0x51] + 0x10) == 0) {
        ((void (*)(int*))*(int*)(cinfo[0x51]))(cinfo);
        uint32_t i = 0;
        if ((uint32_t)cinfo[0x3a] != 0) {
            do {
                if (cinfo[2] != 0) {
                    *(uint32_t*)(cinfo[2] + 4) = i;
                    *(int*)(cinfo[2] + 8) = cinfo[0x3a];
                    ((void (*)(int*))*(int*)(cinfo[2]))(cinfo);
                }
                int r = ((int (*)(int*, int))*(int*)(cinfo[0x54] + 4))(cinfo, 0);
                if (r == 0) {
                    *(int*)(cinfo[0] + 0x14) = 0x16;
                    ((void (*)(int*))*(int*)(cinfo[0]))(cinfo);
                }
                ++i;
            } while (i < (uint32_t)cinfo[0x3a]);
        }
        ((void (*)(int*))*(int*)(cinfo[0x51] + 8))(cinfo);
    }

    ((void (*)(int*))*(int*)(cinfo[0x55] + 0x10))(cinfo);
    ((void (*)(int*))*(int*)(cinfo[5] + 0x10))(cinfo);
    FUN_00854e70(cinfo);
}

// ===========================================================================
// @ 0x00850510  jpeg_write_raw_data-style dispatch
// ===========================================================================
void write_raw_dispatch(int* cinfo, int a2, int a3, int a4)
{
    uint32_t a = (uint32_t)cinfo[0x36];
    uint32_t st;
    if (a != 0 || ((st = (uint32_t)cinfo[4]), st != 0x65 && st != 0x66 && st != 0x67)) {
        *(int*)(cinfo[0] + 0x14) = 0x12;
        *(int*)(cinfo[0] + 0x18) = cinfo[4];
        ((void (*)(int*))*(int*)(cinfo[0]))(cinfo);
    }
    ((void (*)(int*, int, int, int))*(int*)(cinfo[0x55]))(cinfo, a2, a3, a4);
}

// ===========================================================================
// @ 0x00850570  jpeg_finish_compress (partial)
// ===========================================================================
void jpeg_finish_compress2(int* cinfo, int a2)
{
    if (cinfo[4] != 100) {
        *(int*)(cinfo[0] + 0x14) = 0x12;
        *(int*)(cinfo[0] + 0x18) = cinfo[4];
        ((void (*)(int*))*(int*)(cinfo[0]))(cinfo);
    }
    if (a2 != 0)
        SetTableNext(cinfo, 0);
    ((void (*)(int*))*(int*)(cinfo[0] + 0x10))(cinfo);
    ((void (*)(int*))*(int*)(cinfo[5] + 8))(cinfo);
    FUN_00852ff0(cinfo);
    ((void (*)(int*))*(int*)(cinfo[0x51]))(cinfo);
    cinfo[0x36] = 0;
    cinfo[4] = (cinfo[0x2a] != 0) + 0x65;
}

// ===========================================================================
// @ 0x008505f0  empty_output_buffer / output_iMCU_row accounting
// ===========================================================================
void output_pass_setup(int* cinfo, int a2)
{
    if (cinfo[4] != 0x65) {
        *(int*)(cinfo[0] + 0x14) = 0x12;
        *(int*)(cinfo[0] + 0x18) = cinfo[4];
        ((void (*)(int*))*(int*)(cinfo[0]))(cinfo);
    }
    if ((uint32_t)cinfo[0x36] >= (uint32_t)cinfo[7]) {
        *(int*)(cinfo[0] + 0x14) = 0x77;
        ((void (*)(int*, int))*(int*)(cinfo[0] + 4))(cinfo, -1);
    }
    if (cinfo[2] != 0) {
        *(int*)(cinfo[2] + 4) = cinfo[0x36];
        *(int*)(cinfo[2] + 8) = cinfo[7];
        ((void (*)(int*))*(int*)(cinfo[2]))(cinfo);
    }
    if (*(int*)(cinfo[0x51] + 0xc) != 0)
        ((void (*)(int*))*(int*)(cinfo[0x51] + 4))(cinfo);

    uint32_t room = (uint32_t)(cinfo[7] - cinfo[0x36]);
    uint32_t want = (uint32_t)a2;
    if (want > room)
        want = room;
    int lines = 0;
    ((void (*)(int*, int*, int, uint32_t))*(int*)(cinfo[0x52] + 4))(
        cinfo, &lines, a2, want);
    cinfo[0x36] += lines;
}
