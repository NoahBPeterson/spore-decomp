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
extern int  gwrite(void* out, void* buf, unsigned len);  // 0x0087d510 __stdcall
extern void* galloc(int size);                           // 0x0087d4a0 __stdcall
extern int  gfree(void* p);                              // 0x0087d4c0 __stdcall
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
//
// The retail ABI passes the output stream in the named parameter and the
// cinfo struct as an extra stack argument (`ret 0x10`); the default argument
// keeps the one-parameter mangled name while still naming both.
// ===========================================================================
void EncodeMcuHuff(int* stream, int* cinfo = 0)
{
    int height    = cinfo[5];        // +0x14
    int width     = cinfo[4];        // +0x10
    int num_comps = cinfo[9];        // +0x24
    int data_prec = cinfo[0x10e];    // +0x438
    int prec;

    if (cinfo[7] < 9) {
        prec = 8;
    } else if (data_prec < 2 && cinfo[0x10f] < 6 && cinfo[0x110] < 6 &&
               cinfo[0x111] < 6) {
        prec = 0x10;
    } else if (data_prec == 0) {
        prec = 0x18;
    } else {
        prec = 0x20;
    }

    int iVar5 = 0;
    int iVar1 = 0x20;
    unsigned char bVar10 = (unsigned char)(((prec > 8) ? 1 : 0) + 1);
    int ok_flag = (num_comps != 0);
    int alpha = ok_flag;

    unsigned char buf[0x400];
    if (prec < 9) {
        iVar5 = CheckUniformRun(num_comps, buf, (unsigned char*)cinfo + 0x28);
        if (iVar5 != 0) {
            bVar10 = 3;
            alpha = 0;
        }
    }
    if (cinfo[0x10b] != 0)          // +0x42c
        bVar10 |= 8;

    if (alpha) {
        if (cinfo[0x10f] == 5 && cinfo[0x110] == 5 && cinfo[0x111] == 5 &&
            data_prec < 2) {
            int k = 0;
            iVar1 = 0x10;
            if (num_comps > 0) {
                unsigned char* p = (unsigned char*)(cinfo + 0xa + cinfo[8]);
                do {
                    unsigned short uVar4 = 0xff;
                    if (data_prec != 0)
                        uVar4 = (unsigned short)(*p >> 7);
                    *(unsigned short*)(buf + k * 2) =
                        (unsigned short)((((unsigned short)(*p >> 3) | (uVar4 << 5)) << 5 |
                                          (unsigned short)(p[-1] >> 3)) << 5 |
                                         (unsigned short)(p[-2] >> 3));
                    ++k;
                    p += 4;
                } while (k < num_comps);
            }
        } else if (data_prec == 8) {
            int k = 0;
            iVar1 = 0x20;
            if (num_comps > 0) {
                unsigned char* p = (unsigned char*)(cinfo + 0xa + cinfo[8]);
                do {
                    buf[k * 4]     = p[-2];
                    buf[k * 4 + 1] = p[-1];
                    buf[k * 4 + 2] = p[0];
                    buf[k * 4 + 3] = p[1];
                    ++k;
                    p += 4;
                } while (k < num_comps);
            }
        } else {
            iVar1 = 0x18;
            if (num_comps > 0) {
                unsigned char* q = buf + 1;
                unsigned char* p = (unsigned char*)(cinfo + 0xa + cinfo[8]);
                int left = num_comps;
                do {
                    q[-1] = p[-2];
                    q[0]  = p[-1];
                    q[1]  = p[0];
                    p += 4;
                    q += 3;
                } while (--left != 0);
            }
        }
    }

    // build the 0x12-byte JPEG scan header in a local image of the retail frame
    unsigned char hdr[0x12];
    hdr[0]  = 0;
    hdr[1]  = (unsigned char)alpha;
    hdr[2]  = bVar10;
    *(unsigned short*)(hdr + 3) = (unsigned short)prec;
    *(unsigned short*)(hdr + 5) = (unsigned short)height;
    *(unsigned short*)(hdr + 7) = (unsigned short)width;
    *(unsigned short*)(hdr + 9) = (unsigned short)num_comps;
    hdr[0xb] = (unsigned char)iVar1;
    *(unsigned short*)(hdr + 0xc) = *(unsigned short*)((char*)cinfo + 0x450);
    *(unsigned short*)(hdr + 0xe) = (unsigned short)cinfo[8];
    *(unsigned short*)(hdr + 0x10) = (unsigned short)-(short)*(short*)((char*)cinfo + 0x454);

    int res = gwrite(*(void**)((char*)stream + 0x10), hdr, 0x12);
    int count = 0;

    if (res != 0 && iVar5 == 0) {
        int n = (iVar1 * num_comps + ((iVar1 * num_comps >> 0x1f) & 7)) >> 3;
        if (n != 0)
            res = gwrite(*(void**)((char*)stream + 0x10), buf, n);
    }

    void* mem = galloc(((prec * width + ((prec * width) >> 0x1f & 7)) >> 3) * 3 + 0x10);
    if (mem != 0) {
        count = 0;
        while (count < height) {
            bool stop = (res == 0);
            res = 0;
            if (stop)
                break;
            unsigned outSize = EmitSamples(mem, width, prec, 0, cinfo[0x10b],
                                           data_prec, buf);
            res = gwrite(*(void**)((char*)stream + 0x10), mem, (int)outSize);
            ++count;
        }
        gfree(mem);
    }
    (void)iVar1;
    return;
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
    cinfo[0x5a] = 1;
    *(double*)(cinfo + 10) = 1.0;
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
        if ((uint32_t)cinfo[0x3a] > 0) {
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
void output_pass_setup(int* cinfo, int a2, uint32_t a3 = 0)
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
    if (a3 > room)
        a3 = room;
    int lines = 0;
    ((void (*)(int*, int, int*, uint32_t))*(int*)(cinfo[0x52] + 4))(
        cinfo, a2, &lines, a3);
    cinfo[0x36] += lines;
}
