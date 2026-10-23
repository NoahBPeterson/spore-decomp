// Slice s00865150 - libjpeg colour-quantiser internals (SporeApp.exe)
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
//
// This is the libjpeg 6a 1-pass quantiser (jquant1.c) plus the 2-pass
// histogram helper set (jquant2.c) that Spore's JPEG decoder links in.
// Several routines are built with whole-program optimisation and receive
// pointers in fixed registers (EAX/ECX/ESI/EDI); they are rewritten here
// with ordinary explicit arguments: complete and faithful, not byte-exact.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;
typedef int            boolean;

#define NULL 0
#define FALSE 0
#define TRUE  1

#define MAXJSAMPLE 255
#define JPOOL_IMAGE 1

// --------------------------------------------------------------- libjpeg types
struct jpeg_error_mgr {
    void (*error_exit)(void*);                 // 0x00
    void (*emit_message)(void*, int);          // 0x04
    void (*output_message)(void*);             // 0x08
    void (*format_message)(void*, char*);      // 0x0c
    void (*reset_error_mgr)(void*);            // 0x10
    int   msg_code;                            // 0x14
    union { int i[8]; char s[80]; } msg_parm;  // 0x18
};

struct jpeg_memory_mgr {
    void*   (*alloc_small)(void*, int, unsigned);              // 0x00
    void*   (*alloc_large)(void*, int, unsigned);              // 0x04
    void**  (*alloc_sarray)(void*, int, unsigned, unsigned);   // 0x08
    void**  (*alloc_barray)(void*, int, unsigned, unsigned);   // 0x0c
};

struct jpeg_decompress_struct {
    struct jpeg_error_mgr*  err;       // 0x00
    struct jpeg_memory_mgr* mem;       // 0x04
    int pad_08[0x14];                  // 0x08..0x57
    int dither_mode;                   // 0x58
    int pad_5c[1];                     // 0x5c
    int desired_number_of_colors;      // 0x60
    int pad_64[3];                     // 0x64..0x6f
    int output_width;                  // 0x70
    int pad_74[1];                     // 0x74
    int out_color_components;          // 0x78
    int pad_7c[2];                     // 0x7c..0x83
    int actual_number_of_colors;       // 0x84
    u8** colormap;                     // 0x88
    int pad_8c[0x12e];                 // 0x8c..0x543
    u8* sample_range_limit;            // 0x544
    int pad_548[0x21];                 // 0x548..0x5cb
    void* cquantize;                   // 0x5cc
};

struct cquantize_s {
    void (*start_pass)(void*);                      // 0x00
    void (*color_quantize)(void*, u8**, u8**, int);  // 0x04
    void (*finish_pass)(void*);                     // 0x08
    void (*new_color_map)(void*);                   // 0x0c
    u8** sv_colormap;                               // 0x10
    int  sv_actual;                                 // 0x14
    u8** colorindex;                                // 0x18
    int  is_padded;                                 // 0x1c
    int  Ncolors[4];                                // 0x20
    int  row_index;                                 // 0x30
    int  odither[4];                                // 0x34
    short* fserrors[3];                             // 0x44
    int  pad_50[1];                                 // 0x50
    int  direction;                                 // 0x54
};

// ------------------------------------------------------------------ runtime
extern "C" void FUN_008668f0(void* p, int n);           // jzero_far

// helper routines that live in other slices
struct jpeg_decompress_struct;
extern "C" void FUN_00864a20(struct jpeg_decompress_struct* cinfo);  // create_colormap
extern "C" void FUN_00864b90(struct jpeg_decompress_struct* cinfo);  // create_colorindex
extern "C" void FUN_00864d60(struct jpeg_decompress_struct* cinfo);  // create_odither_tables
extern "C" void FUN_00864db0(struct jpeg_decompress_struct*, u8**, u8**, int);
extern "C" void FUN_00864e60(struct jpeg_decompress_struct*, u8**, u8**, int);
extern "C" void FUN_00864f10(struct jpeg_decompress_struct*, u8**, u8**, int);
extern "C" void FUN_00865020(struct jpeg_decompress_struct*, u8**, u8**, int);
extern "C" int  FUN_00865950(struct jpeg_decompress_struct*, int*, int, int); // median_cut

// forward declarations
void FUN_00865150(struct jpeg_decompress_struct*, u8**, u8**, int);
void FUN_00865300(struct jpeg_decompress_struct*);
void FUN_00865340(struct jpeg_decompress_struct*);
void FUN_00865450(struct jpeg_decompress_struct*);
void FUN_008654f0(struct jpeg_decompress_struct*, u8**, u8**, int);
void FUN_00865570(struct jpeg_decompress_struct*, int*);
void FUN_00865ad0(int*, struct jpeg_decompress_struct*, int);
void FUN_00865c50(struct jpeg_decompress_struct*, int);
int  FUN_00865ce0(struct jpeg_decompress_struct*, int, int, int, u8*);
void FUN_00865ec0(struct jpeg_decompress_struct*, int, int, int, int, u8*, u8*);
void FUN_00866040(int, struct jpeg_decompress_struct*, int, int);
void FUN_00866160(struct jpeg_decompress_struct*, u8**, u8**, int);

// ================================================================ 0x00865150
// jquant1.c quantize_fs_dither: Floyd-Steinberg error diffusion.
// @ 0x00865150
void FUN_00865150(struct jpeg_decompress_struct* cinfo, u8** input_buf,
                  u8** output_buf, int num_rows)
{
    struct cquantize_s* cq = (struct cquantize_s*)cinfo->cquantize;
    short** fserrors = (short**)((char*)cq + 0x44);
    int width = cinfo->output_width;
    u8* range_limit = cinfo->sample_range_limit;
    int comps = cinfo->out_color_components;

    if (num_rows <= 0)
        return;

    do {
        int ci;

        FUN_008668f0(*output_buf, width);
        ci = 0;
        if (comps > 0) {
            short** errp = fserrors;
            do {
                u8*   outptr = *output_buf;
                u8*   inptr  = *input_buf + ci;
                short* err   = *errp;
                u8*   cmap   = cq->sv_colormap[ci];
                u8*   cidx   = cq->colorindex[ci];
                int   dir, step;
                int   prev, next, carry;
                int   col;

                if (cq->direction == 0) {
                    dir = 1;
                    step = comps;
                } else {
                    outptr += width - 1;
                    inptr  += (width - 1) * comps;
                    dir = -1;
                    err += width + 1;
                    step = -comps;
                }

                prev = 0;
                next = 0;
                carry = 0;
                for (col = width; col != 0; col--) {
                    int cur = range_limit[inptr[0] + ((err[dir] + prev + 8) >> 4)];
                    int pixcode, diff;

                    inptr += step;
                    pixcode = cidx[cur];
                    *outptr += (u8)pixcode;
                    diff = cur - cmap[pixcode];

                    next += diff * 3;
                    err[0] = (short)next;
                    next = carry + diff * 5;
                    carry = diff;
                    prev = diff * 7;

                    outptr += dir;
                    err += dir;
                }
                err[0] = (short)next;
                errp++;
                ci++;
            } while (ci < comps);
        }
        output_buf++;
        input_buf++;
        cq->direction = (cq->direction == 0);
        num_rows--;
    } while (num_rows != 0);
}

// ================================================================ 0x00865300
// Allocate the three Floyd-Steinberg error rows (output_width+2 shorts each).
// The original receives cinfo in ESI (whole-program convention).
// @ 0x00865300
void FUN_00865300(struct jpeg_decompress_struct* cinfo)
{
    struct cquantize_s* cq = (struct cquantize_s*)cinfo->cquantize;
    int size = cinfo->output_width * 2 + 4;
    short** p = (short**)((char*)cq + 0x44);
    int i = 0;

    if (cinfo->out_color_components > 0) {
        do {
            *p = (short*)(*cinfo->mem->alloc_large)(cinfo, 1, size);
            i++;
            p++;
        } while (i < cinfo->out_color_components);
    }
}

// ================================================================ 0x00865340
// jquant1.c start_pass_1_quant: select the colour-quantise routine.
// @ 0x00865340
void FUN_00865340(struct jpeg_decompress_struct* cinfo)
{
    struct cquantize_s* cq = (struct cquantize_s*)cinfo->cquantize;
    int mode;

    cinfo->colormap = cq->sv_colormap;
    cinfo->actual_number_of_colors = cq->sv_actual;
    mode = cinfo->dither_mode;

    if (mode == 0) {
        if (cinfo->out_color_components == 3)
            cq->color_quantize = (void (*)(void*, u8**, u8**, int))FUN_00864e60;
        else
            cq->color_quantize = (void (*)(void*, u8**, u8**, int))FUN_00864db0;
        return;
    }
    if (mode == 1) {
        if (cinfo->out_color_components == 3)
            cq->color_quantize = (void (*)(void*, u8**, u8**, int))FUN_00865020;
        else
            cq->color_quantize = (void (*)(void*, u8**, u8**, int))FUN_00864f10;
        cq->row_index = 0;
        if (cq->is_padded == 0)
            FUN_00864b90(cinfo);
        if (cq->odither[0] == 0)
            FUN_00864d60(cinfo);
        return;
    }
    if (mode == 2) {
        cq->color_quantize = (void (*)(void*, u8**, u8**, int))FUN_00865150;
        cq->direction = 0;
        if (cq->fserrors[0] == NULL)
            FUN_00865300(cinfo);
        {
            int size = cinfo->output_width * 2 + 4;
            short** p = (short**)((char*)cq + 0x44);
            int i = 0;
            if (cinfo->out_color_components > 0) {
                do {
                    FUN_008668f0(p[i], size);
                    i++;
                } while (i < cinfo->out_color_components);
            }
        }
        return;
    }

    cinfo->err->msg_code = 0x2f;
    (*cinfo->err->error_exit)(cinfo);
}

// ================================================================ 0x00865450
// jquant1.c jinit_1pass_quantizer.
// @ 0x00865450
void FUN_00865450(struct jpeg_decompress_struct* cinfo)
{
    struct cquantize_s* cq =
        (struct cquantize_s*)(*cinfo->mem->alloc_small)(cinfo, 1, 0x58);

    cinfo->cquantize = cq;
    cq->start_pass = (void (*)(void*))FUN_00865340;
    cq->finish_pass = (void (*)(void*))0x00c2e4e0;
    cq->new_color_map = (void (*)(void*))0x00865430;
    cq->fserrors[0] = NULL;
    cq->odither[0] = 0;

    if (cinfo->out_color_components > 4) {
        cinfo->err->msg_code = 0x36;
        cinfo->err->msg_parm.i[0] = 4;
        (*cinfo->err->error_exit)(cinfo);
    }
    if (cinfo->desired_number_of_colors > 0x100) {
        cinfo->err->msg_code = 0x38;
        cinfo->err->msg_parm.i[0] = 0x100;
        (*cinfo->err->error_exit)(cinfo);
    }

    FUN_00864a20(cinfo);
    FUN_00864b90(cinfo);

    if (cinfo->dither_mode == 2)
        FUN_00865300(cinfo);
}

// ================================================================ 0x008654f0
// jquant2.c prescan_quantize: build the 3-D colour histogram.
// @ 0x008654f0
void FUN_008654f0(struct jpeg_decompress_struct* cinfo, u8** input_buf,
                  u8** output_buf, int num_rows)
{
    struct cquantize_s* cq = (struct cquantize_s*)cinfo->cquantize;
    short** hist = (short**)((char*)cq + 0x18);
    int width = cinfo->output_width;
    int row = 0;

    if (num_rows <= 0)
        return;

    do {
        u8* ptr = input_buf[row];
        int col = width;
        if (width != 0) {
            do {
                int idx = (ptr[1] >> 2) * 0x20 + (ptr[2] >> 3);
                short* cell = (short*)((char*)hist[ptr[0] >> 3] + idx * 2);
                (*cell)++;
                if (*cell == 0)
                    *cell = -1;
                ptr += 3;
                col--;
            } while (col != 0);
        }
        row++;
    } while (row < num_rows);
}

// ================================================================ 0x00865570
// jquant2.c update_box: shrink a colour box to the nonzero histogram cells.
// The original receives cinfo in ECX (whole-program convention).
// @ 0x00865570
void FUN_00865570(struct jpeg_decompress_struct* cinfo, int* box)
{
    struct cquantize_s* cq = (struct cquantize_s*)cinfo->cquantize;
    short** hist = (short**)((char*)cq + 0x18);
    int c0min = box[0], c0max = box[1];
    int c1min = box[2], c1max = box[3];
    int c2min = box[4], c2max = box[5];
    int i, j, k, found, count;

    /* minimum c0 */
    found = 0;
    for (i = c0min; i <= c0max && !found; i++) {
        short* row = hist[i];
        for (j = c1min; j <= c1max && !found; j++) {
            short* p = (short*)((char*)row + (j * 0x20 + c2min) * 2);
            for (k = c2min; k <= c2max; k++) {
                if (*p++ != 0) {
                    box[0] = i;
                    c0min = i;
                    found = 1;
                    break;
                }
            }
        }
    }
    /* maximum c0 */
    found = 0;
    for (i = c0max; i >= c0min && !found; i--) {
        short* row = hist[i];
        for (j = c1min; j <= c1max && !found; j++) {
            short* p = (short*)((char*)row + (j * 0x20 + c2min) * 2);
            for (k = c2min; k <= c2max; k++) {
                if (*p++ != 0) {
                    box[1] = i;
                    c0max = i;
                    found = 1;
                    break;
                }
            }
        }
    }
    /* minimum c1 */
    if (c1min < c1max) {
        found = 0;
        for (j = c1min; j <= c1max && !found; j++) {
            for (i = c0min; i <= c0max && !found; i++) {
                short* p = (short*)((char*)hist[i] + (j * 0x20 + c2min) * 2);
                for (k = c2min; k <= c2max; k++) {
                    if (*p++ != 0) {
                        box[2] = j;
                        c1min = j;
                        found = 1;
                        break;
                    }
                }
            }
        }
        /* maximum c1 */
        found = 0;
        for (j = c1max; j >= c1min && !found; j--) {
            for (i = c0min; i <= c0max && !found; i++) {
                short* p = (short*)((char*)hist[i] + (j * 0x20 + c2min) * 2);
                for (k = c2min; k <= c2max; k++) {
                    if (*p++ != 0) {
                        box[3] = j;
                        c1max = j;
                        found = 1;
                        break;
                    }
                }
            }
        }
    }
    /* minimum c2 */
    if (c2min < c2max) {
        found = 0;
        for (k = c2min; k <= c2max && !found; k++) {
            for (i = c0min; i <= c0max && !found; i++) {
                short* p = (short*)((char*)hist[i] + (c1min * 0x20 + k) * 2);
                for (j = c1min; j <= c1max; j++) {
                    if (*p != 0) {
                        box[4] = k;
                        c2min = k;
                        found = 1;
                        break;
                    }
                    p += 0x20;
                }
            }
        }
        /* maximum c2 */
        found = 0;
        for (k = c2max; k >= c2min && !found; k--) {
            for (i = c0min; i <= c0max && !found; i++) {
                short* p = (short*)((char*)hist[i] + (c1min * 0x20 + k) * 2);
                for (j = c1min; j <= c1max; j++) {
                    if (*p != 0) {
                        box[5] = k;
                        c2max = k;
                        found = 1;
                        break;
                    }
                    p += 0x20;
                }
            }
        }
    }

    box[6] = (c2max - c2min) * 8 * ((c2max - c2min) * 8)
           + (c1max - c1min) * 0xc * ((c1max - c1min) * 0xc)
           + (c0max - c0min) * 0x10 * ((c0max - c0min) * 0x10);

    count = 0;
    for (i = c0min; i <= c0max; i++) {
        for (j = c1min; j <= c1max; j++) {
            short* p = (short*)((char*)hist[i] + (j * 0x20 + c2min) * 2);
            for (k = c2min; k <= c2max; k++) {
                if (*p++ != 0)
                    count++;
            }
        }
    }
    box[7] = count;
}

// ================================================================ 0x00865ad0
// jquant2.c compute_color: average colour of one box.
// The original receives the box pointer in EAX (whole-program convention).
// @ 0x00865ad0
void FUN_00865ad0(int* box, struct jpeg_decompress_struct* cinfo, int idx)
{
    struct cquantize_s* cq = (struct cquantize_s*)cinfo->cquantize;
    short** hist = (short**)((char*)cq + 0x18);
    u8** colormap = cinfo->colormap;
    int c0min = box[0], c0max = box[1];
    int c1min = box[2], c1max = box[3];
    int c2min = box[4], c2max = box[5];
    int count = 0, sum0 = 0, sum1 = 0, sum2 = 0;
    int i, j, k;

    for (i = c0min; i <= c0max; i++) {
        int w0 = i * 8 + 4;
        for (j = c1min; j <= c1max; j++) {
            short* p = (short*)((char*)hist[i] + (j * 0x20 + c2min) * 2);
            int w1 = j * 4 + 2;
            for (k = c2min; k <= c2max; k++) {
                int v = *p++;
                int w2 = k * 8 + 4;
                if (v != 0) {
                    sum0 += w0 * v;
                    sum1 += w1 * v;
                    count += v;
                    sum2 += w2 * v;
                }
            }
        }
    }

    if (count != 0) {
        int half = count >> 1;
        colormap[0][idx] = (u8)((sum0 + half) / count);
        colormap[1][idx] = (u8)((sum1 + half) / count);
        colormap[2][idx] = (u8)((sum2 + half) / count);
    }
}

// ================================================================ 0x00865c50
// jquant2.c select_colors: median-cut the histogram and build the colormap.
// The original receives cinfo in EDI (whole-program convention).
// @ 0x00865c50
void FUN_00865c50(struct jpeg_decompress_struct* cinfo, int desired)
{
    int* box = (int*)(*cinfo->mem->alloc_small)(cinfo, 1, desired * 0x20);
    int n, i;

    box[0] = 0;
    box[1] = 0x1f;
    box[2] = 0;
    box[3] = 0x3f;
    box[4] = 0;
    box[5] = 0x1f;

    FUN_00865570(cinfo, box);
    n = FUN_00865950(cinfo, box, 1, desired);

    i = 0;
    if (n > 0) {
        do {
            FUN_00865ad0(box, cinfo, i);
            i++;
            box += 8;
        } while (i < n);
    }

    cinfo->actual_number_of_colors = n;
    cinfo->err->msg_code = 0x5f;
    cinfo->err->msg_parm.i[0] = n;
    (*cinfo->err->emit_message)(cinfo, 1);
}

// ================================================================ 0x00865ce0
// jquant2.c find_nearby_colors: list colormap entries near a colour point.
// The original receives cinfo in EAX and the green coordinate in ECX.
// @ 0x00865ce0
int FUN_00865ce0(struct jpeg_decompress_struct* cinfo, int green, int red,
                 int blue, u8* out)
{
    int n = cinfo->actual_number_of_colors;
    u8* cm0 = cinfo->colormap[0];
    u8* cm1 = cinfo->colormap[1];
    u8* cm2 = cinfo->colormap[2];
    int ghi = green + 0x1c;
    int gmid = (green + ghi) >> 1;
    int rmid = (red * 2 + 0x18) >> 1;
    int bmid = (blue * 2 + 0x18) >> 1;
    int errs[256];
    int idx, minv, nout;

    minv = 0x7fffffff;
    idx = 0;
    if (n > 0) {
        do {
            int v0 = cm0[idx];
            int d0, gres, redres, bres, dist;
            int rlo;

            if (v0 < red) {
                int t = (v0 - red) * 2;
                d0 = t * t;
                rlo = red + 0x18;
            } else {
                int hi = red + 0x18;
                if (hi < v0) {
                    int t = (v0 - hi) * 2;
                    d0 = t * t;
                    rlo = red;
                } else {
                    d0 = 0;
                    if (rmid < v0)
                        rlo = red;
                    else
                        rlo = red + 0x18;
                }
            }
            redres = (v0 - rlo) * 2;

            {
                int v1 = cm1[idx];
                if (v1 < green) {
                    int t = (v1 - green) * 3;
                    d0 += t * t;
                    gres = v1 - ghi;
                } else {
                    if (ghi < v1) {
                        int t = (v1 - ghi) * 3;
                        d0 += t * t;
                        gres = v1 - green;
                    } else if (v1 <= gmid) {
                        gres = v1 - ghi;
                    } else {
                        gres = v1 - green;
                    }
                }
            }
            {
                int v2 = cm2[idx];
                int vhi = blue + 0x18;
                if (v2 < blue) {
                    d0 += (v2 - blue) * (v2 - blue);
                    bres = v2 - vhi;
                } else if (vhi < v2) {
                    d0 += (v2 - vhi) * (v2 - vhi);
                    bres = v2 - blue;
                } else if (v2 <= bmid) {
                    bres = v2 - vhi;
                } else {
                    bres = v2 - blue;
                }
            }
            dist = redres * redres + gres * 3 * gres * 3 + bres * bres;
            errs[idx] = d0;
            if (dist < minv)
                minv = dist;
            idx++;
        } while (idx < n);
    }

    nout = 0;
    for (idx = 0; idx < n; idx++) {
        if (errs[idx] <= minv) {
            out[nout] = (u8)idx;
            nout++;
        }
    }
    return nout;
}

// ================================================================ 0x00865ec0
// jquant2.c find_best_colors: fill the 3x8x4 inverse-map lattice.
// @ 0x00865ec0
void FUN_00865ec0(struct jpeg_decompress_struct* cinfo, int c0, int c1,
                  int c2, int ncolors, u8* list, u8* out)
{
    int colorlist[128];
    int i;

    for (i = 0; i < 128; i++)
        colorlist[i] = 0x7fffffff;

    if (ncolors > 0) {
        int idx = 0;
        do {
            u8 color = list[idx];
            u8** cmap = cinfo->colormap;
            int gdiff = c1 - cmap[1][color];
            int bdiff = c2 - cmap[2][color];
            int rdiff = (c0 - cmap[0][color]) * 2;
            int dist = bdiff * bdiff + (gdiff * 3) * (gdiff * 3) + rdiff * rdiff;
            int stepB = (bdiff + 4) * 0x10;
            int stepR = (rdiff + 8) * 0x20;
            int* p = colorlist;
            u8*  o = out;
            int  outer = 3;
            int  d = dist;

            do {
                int inner = 7;
                int v = d;
                int sg = (gdiff * 9 + 0x12) * 8;
                do {
                    int v1, v2, v3;
                    if (v < p[0]) { p[0] = v; o[0] = color; }
                    v1 = v + stepB;
                    if (v1 < p[1]) { p[1] = v1; o[1] = color; }
                    v2 = v1 + stepB + 0x80;
                    if (v2 < p[2]) { p[2] = v2; o[2] = color; }
                    v3 = v2 + stepB + 0x100;
                    if (v3 < p[3]) { p[3] = v3; o[3] = color; }
                    v += sg;
                    sg += 0x120;
                    p += 4;
                    o += 4;
                    inner--;
                } while (inner >= 0);
                d += stepR;
                stepR += 0x200;
                outer--;
            } while (outer >= 0);
            idx++;
        } while (idx < ncolors);
    }
}

// ================================================================ 0x00866040
// jquant2.c fill_inverse_cmap: build the inverse colormap for one histogram cell.
// The original receives the green coordinate in EAX (whole-program convention).
// @ 0x00866040
void FUN_00866040(int green, struct jpeg_decompress_struct* cinfo,
                  int red, int blue)
{
    struct cquantize_s* cq = (struct cquantize_s*)cinfo->cquantize;
    short** hist = (short**)((char*)cq + 0x18);
    int r2 = (red >> 2) * 0x20 + 4;
    int b2 = (blue >> 2) * 0x20 + 4;
    int g2 = ((green >> 3) * 0x20) + 2;
    u8 list[256];
    u8 best[128];
    int n;
    short** prow;
    int roff;
    u8* pb;
    int outer;

    n = FUN_00865ce0(cinfo, g2, r2, b2, list);
    FUN_00865ec0(cinfo, r2, g2, b2, n, list, best);

    prow = hist + (red >> 2);
    roff = ((green >> 3) * 0x100 + (blue >> 2) * 4);
    pb = best;
    outer = 4;
    do {
        short* p = (short*)((char*)prow[0] + roff * 2);
        int inner = 8;
        do {
            p[0] = (short)(pb[0] + 1);
            p[1] = (short)(pb[1] + 1);
            p[2] = (short)(pb[2] + 1);
            p[3] = (short)(pb[3] + 1);
            pb += 4;
            p = (short*)((char*)p + 0x40);
            inner--;
        } while (inner != 0);
        prow++;
        outer--;
    } while (outer != 0);
}

// ================================================================ 0x00866160
// jquant2.c pass2_no_dither: map each pixel through the inverse colormap.
// @ 0x00866160
void FUN_00866160(struct jpeg_decompress_struct* cinfo, u8** input_buf,
                  u8** output_buf, int num_rows)
{
    struct cquantize_s* cq = (struct cquantize_s*)cinfo->cquantize;
    short** hist = (short**)((char*)cq + 0x18);
    int width = cinfo->output_width;
    int row = 0;

    if (num_rows <= 0)
        return;

    do {
        u8* inptr  = input_buf[row];
        u8* outptr = output_buf[row];
        int col = width;
        if (width != 0) {
            do {
                int r = inptr[0];
                int g = inptr[1];
                int b = inptr[2];
                short* cell;
                inptr += 3;
                cell = (short*)((char*)hist[r >> 3]
                                + ((g >> 2) * 0x20 + (b >> 3)) * 2);
                if (*cell == 0)
                    FUN_00866040(g >> 2, cinfo, r >> 3, b >> 3);
                *outptr++ = (u8)(*cell - 1);
                col--;
            } while (col != 0);
        }
        row++;
    } while (row < num_rows);
}
