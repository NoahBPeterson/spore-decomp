// Slice s008680d0 -- third-party C library block (link order).
//   lib_zlib: updatewindow (068db0) [inflate.c],
//             deflate_slow (0680d0) [deflate.c],      -> s008680d0_deflate.c
//             deflateInit2_ (0685e0) [deflate.c]      -> s008680d0_deflate.c
//             inflate_table (06a3f0) [inftrees.c]
//   lib_png : png_sig_cmp (06a8c0) [png.c],
//             png_default_error (06aff0), png_default_warning (06b110) [pngerror.c]
// Flags: /O2 /arch:SSE /MD /Gy /TC /GS-
// deflate_slow/deflateInit2_ need the whole upstream deflate.c TU in one file: their
// out-of-line calls to fill_window/longest_match/longest_match_fast/flush_pending use
// cl's TU-local register-argument convention for statics, which only reproduces when
// the callees and their other call sites are in the same translation unit.

typedef unsigned char Byte;
typedef unsigned char Bytef;
typedef unsigned int  uInt;
typedef unsigned long uLong;
typedef void* voidpf;
typedef char* charf;
typedef unsigned char png_byte;
typedef unsigned char* png_bytep;
typedef const char* png_const_charp;

typedef struct { char _raw[0x20]; } FILE;
#define stderr (&__iob_func()[2])

typedef struct z_stream_s {
    Bytef*   next_in;
    uInt     avail_in;
    uLong    total_in;
    Bytef*   next_out;
    uInt     avail_out;
    uLong    total_out;
    char*    msg;
    void*    state;
    voidpf (*zalloc)(voidpf, uInt, uInt);
    void   (*zfree)(voidpf, voidpf);
    voidpf   opaque;
    int      data_type;
    uLong    adler;
    uLong    reserved;
} z_stream;
typedef z_stream* z_streamp;

typedef unsigned short ush;
typedef unsigned char  uch;
typedef unsigned short Pos;
typedef unsigned int   IPos;
typedef unsigned long  ulg;

#define MIN_MATCH  3
#define MAX_MATCH  258
#define MIN_LOOKAHEAD (MAX_MATCH+MIN_MATCH+1)
#define MAX_DIST(s)  ((s)->w_size-MIN_LOOKAHEAD)

#define LENGTH_CODES 29
#define LITERALS 256
#define L_CODES (LITERALS+1+LENGTH_CODES)
#define D_CODES 30
#define BL_CODES 19
#define HEAP_SIZE (2*L_CODES+1)

typedef struct ct_data_s {
    union { ush freq; ush code; } fc;
    union { ush dad; ush len; } dl;
} ct_data;

typedef struct static_tree_desc_s {
    const ct_data* static_tree;
    const int* extra_bits;
    int extra_base;
    int elems;
    int max_length;
} static_tree_desc;

typedef struct tree_desc_s {
    ct_data* dyn_tree;
    int max_code;
    const static_tree_desc* stat_desc;
} tree_desc;

struct internal_state {
    z_streamp strm;      /* 0x00 */
    int status;          /* 0x04 */
    Bytef* pending_buf;  /* 0x08 */
    ulg pending_buf_size;/* 0x0c */
    Bytef* pending_out;  /* 0x10 */
    int pending;         /* 0x14 */
    int wrap;            /* 0x18 */
    void* gzhead;        /* 0x1c */
    uLong gzindex;       /* 0x20 */
    Byte method;         /* 0x24 */
    int last_flush;      /* 0x28 */
    uInt w_size;         /* 0x2c */
    uInt w_bits;         /* 0x30 */
    uInt w_mask;         /* 0x34 */
    Bytef* window;       /* 0x38 */
    ulg window_size;     /* 0x3c */
    Pos* prev;           /* 0x40 */
    Pos* head;           /* 0x44 */
    uInt ins_h;          /* 0x48 */
    uInt hash_size;      /* 0x4c */
    uInt hash_bits;      /* 0x50 */
    uInt hash_mask;      /* 0x54 */
    uInt hash_shift;     /* 0x58 */
    long block_start;    /* 0x5c */
    uInt match_length;   /* 0x60 */
    IPos prev_match;     /* 0x64 */
    int match_available; /* 0x68 */
    uInt strstart;       /* 0x6c */
    uInt match_start;    /* 0x70 */
    uInt lookahead;      /* 0x74 */
    uInt prev_length;    /* 0x78 */
    uInt max_chain_length;/* 0x7c */
    uInt max_lazy_match; /* 0x80 */
    int level;           /* 0x84 */
    int strategy;        /* 0x88 */
    uInt good_match;     /* 0x8c */
    int nice_match;      /* 0x90 */
    ct_data dyn_ltree[HEAP_SIZE];        /* 0x94 */
    ct_data dyn_dtree[2*D_CODES+1];      /* 0x1494 */
    ct_data bl_tree[2*BL_CODES+1];       /* 0x1564 */
    tree_desc l_desc;                    /* 0x15a0 */
    tree_desc d_desc;                    /* 0x15b4 */
    tree_desc bl_desc;                   /* 0x15c8 */
    ush bl_count[16];                    /* 0x15dc */
    int heap[2*L_CODES+1];               /* 0x15fc */
    int heap_len;                        /* 0x1690 */
    int heap_max;                        /* 0x1694 */
    uch depth[2*L_CODES+1];              /* 0x1458 */
    uch* l_buf;                          /* 0x1698 */
    uInt lit_bufsize;                    /* 0x169c */
    uInt last_lit;                       /* 0x16a0 */
    ush* d_buf;                          /* 0x16a4 */
    ulg opt_len;                         /* 0x16a8 */
    ulg static_len;                      /* 0x16ac */
    uInt matches;                        /* 0x16b0 */
    int last_eob_len;                    /* 0x16b4 */
    ush bi_buf;                          /* 0x16b8 */
    int bi_valid;                        /* 0x16bc */
};
typedef struct internal_state deflate_state;

struct inflate_state {
    int mode;                 /* 0x00 */
    int last;                 /* 0x04 */
    int wrap;                 /* 0x08 */
    int havedict;             /* 0x0c */
    int flags;                /* 0x10 */
    unsigned dmax;            /* 0x14 */
    unsigned long check;      /* 0x18 */
    unsigned long total;      /* 0x1c */
    void* head;               /* 0x20 */
    unsigned wbits;           /* 0x24 */
    unsigned wsize;           /* 0x28 */
    unsigned whave;           /* 0x2c */
    unsigned write;           /* 0x30 */
    unsigned char* window;    /* 0x34 */
    unsigned long hold;       /* 0x38 */
    unsigned bits;            /* 0x3c */
    unsigned length;          /* 0x40 */
    unsigned offset;          /* 0x44 */
    unsigned extra;           /* 0x48 */
    void* lencode;            /* 0x4c */
    void* distcode;           /* 0x50 */
    unsigned lenbits;         /* 0x54 */
    unsigned distbits;        /* 0x58 */
    unsigned ncode;           /* 0x5c */
    unsigned nlen;            /* 0x60 */
    unsigned ndist;           /* 0x64 */
    unsigned have;            /* 0x68 */
    unsigned short* next;     /* 0x6c */
    unsigned short lens[320]; /* 0x70 */
    unsigned short work[288]; /* 0x2f0 */
    unsigned short codes[2048];/* 0x530 */
};
typedef struct inflate_state inflate_state;

typedef struct {
    unsigned char op;
    unsigned char bits;
    unsigned short val;
} code;

typedef enum { CODES, LENS, DISTS } codetype;

typedef enum {
    need_more,      /* block not completed, need more input or more output */
    block_done,     /* block flush performed */
    finish_started, /* finish started, need only more output at next deflate */
    finish_done     /* finish done, accept no more input or output */
} block_state;

#define ENOUGH 2048
#define MAXD 592

#define Z_DEFLATED   8
#define Z_FIXED      4
#define Z_DEFAULT_COMPRESSION (-1)
#define Z_STREAM_ERROR (-2)
#define Z_MEM_ERROR    (-4)
#define Z_VERSION_ERROR (-6)
#define MAX_MEM_LEVEL 9
extern const char* z_errmsg[10];
#define Z_NEED_NEG(x) (-(x))

#define Z_NO_FLUSH      0
#define Z_HUFFMAN_ONLY  2
#define Z_RLE           3
#define Z_FILTERED      1
#define Z_FINISH        4
#define Z_NIL           0
#define TOO_FAR 4096

#define UPDATE_HASH(s,h,c) (h = (((h)<<(s)->hash_shift) ^ (c)) & (s)->hash_mask)

#define INSERT_STRING(s, str, match_head) \
   (UPDATE_HASH(s, (s)->ins_h, (s)->window[(str) + (MIN_MATCH-1)]), \
    match_head = (s)->prev[(str) & (s)->w_mask] = (s)->head[(s)->ins_h], \
    (s)->head[(s)->ins_h] = (Pos)(str))

#define _tr_tally_lit(s, c, flush) { \
    uch cc = (c); \
    (s)->d_buf[(s)->last_lit] = 0; \
    (s)->l_buf[(s)->last_lit++] = cc; \
    (s)->dyn_ltree[cc].fc.freq++; \
    flush = ((s)->last_lit == (s)->lit_bufsize-1); \
}
#define _tr_tally_dist(s, distance, length, flush) { \
    uch len = (uch)(length); \
    ush dist = (ush)(distance); \
    (s)->d_buf[(s)->last_lit] = dist; \
    (s)->l_buf[(s)->last_lit++] = len; \
    dist--; \
    (s)->dyn_ltree[_length_code[len]+LITERALS+1].fc.freq++; \
    (s)->dyn_dtree[d_code(dist)].fc.freq++; \
    flush = ((s)->last_lit == (s)->lit_bufsize-1); \
}
#define d_code(dist) ((dist) < 256 ? _dist_code[dist] : _dist_code[256+((dist)>>7)])

#define FLUSH_BLOCK_ONLY(s, eof) { \
   _tr_flush_block(s, (s)->block_start >= 0L ? \
                   (Bytef*)&(s)->window[(unsigned)(s)->block_start] : \
                   (Bytef*)0, \
                (ulg)((long)(s)->strstart - (s)->block_start), \
                (eof)); \
   (s)->block_start = (long)(s)->strstart; \
   flush_pending((s)->strm); \
}

/* FLUSH_BLOCK (deflate.c): with the avail_out check of FLUSH_BLOCK_ONLY. */
#define FLUSH_BLOCK(s, eof) { \
   FLUSH_BLOCK_ONLY(s, eof); \
   if ((s)->strm->avail_out == 0) return need_more; \
}

#ifdef __cplusplus
extern "C" {
#endif
    voidpf __cdecl zcalloc(voidpf opaque, uInt items, uInt size);
    void   __cdecl zcfree(voidpf opaque, voidpf ptr);
    int    __cdecl deflateReset(z_streamp strm);
    int    __cdecl deflateEnd(z_streamp strm);
    uInt   __cdecl longest_match(deflate_state* s, IPos cur_match);
    uInt   __cdecl longest_match_fast(deflate_state* s, IPos cur_match);
    void   __cdecl _tr_flush_block(deflate_state* s, Bytef* buf, ulg stored_len, int eof);
    void   __cdecl fill_window(deflate_state* s);
    void   __cdecl flush_pending(z_streamp strm);
    __declspec(dllimport) void* __cdecl memcpy(void* dst, const void* src, unsigned int size);
    __declspec(dllimport) int   __cdecl memcmp(const void* a, const void* b, unsigned int n);
    __declspec(dllimport) FILE* __cdecl __iob_func(void);
    __declspec(dllimport) int   __cdecl fprintf(FILE* stream, const char* fmt, ...);
    __declspec(dllimport) __declspec(noreturn) void __cdecl longjmp(void* env, int val);
#ifdef __cplusplus
}
#endif

extern const ush _length_code[256];
extern const uch _dist_code[512];

/* ===========================================================================
 * inflate.c -- updatewindow
 */
// @ 0x00868db0
static int updatewindow(z_streamp strm, unsigned out)
{
    inflate_state* state;
    unsigned copy, dist;

    state = (inflate_state*)strm->state;

    if (state->window == 0) {
        state->window = (unsigned char*)
                        strm->zalloc(strm->opaque, 1U << state->wbits,
                                     sizeof(unsigned char));
        if (state->window == 0) return 1;
    }

    if (state->wsize == 0) {
        state->wsize = 1U << state->wbits;
        state->write = 0;
        state->whave = 0;
    }

    copy = out - strm->avail_out;
    if (copy >= state->wsize) {
        memcpy(state->window, strm->next_out - state->wsize, state->wsize);
        state->write = 0;
        state->whave = state->wsize;
    } else {
        dist = state->wsize - state->write;
        if (dist > copy) dist = copy;
        memcpy(state->window + state->write, strm->next_out - copy, dist);
        copy -= dist;
        if (copy) {
            memcpy(state->window, strm->next_out - copy, copy);
            state->write = copy;
            state->whave = state->wsize;
        } else {
            state->write += dist;
            if (state->write == state->wsize) state->write = 0;
            if (state->whave < state->wsize) state->whave += dist;
        }
    }
    return 0;
}

/* ===========================================================================
 * inftrees.c -- inflate_table
 */
// @ 0x0086a3f0
int inflate_table(codetype type, unsigned short* lens, unsigned codes,
                  code** table, unsigned* bits, unsigned short* work)
{
    unsigned len;
    unsigned sym;
    unsigned min, max;
    unsigned root;
    unsigned curr;
    unsigned drop;
    int left;
    unsigned used;
    unsigned huff;
    unsigned incr;
    unsigned fill;
    unsigned low;
    unsigned mask;
    code thisent;
    code* next;
    const unsigned short* base;
    const unsigned short* extra;
    int end;
    unsigned short count[16];
    unsigned short offs[16];
    static const unsigned short lbase[31] = {
        3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31,
        35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0};
    static const unsigned short lext[31] = {
        16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 18,
        19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 16, 201, 196};
    static const unsigned short dbase[32] = {
        1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193,
        257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145,
        8193, 12289, 16385, 24577, 0, 0};
    static const unsigned short dext[32] = {
        16, 16, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22,
        23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 64, 64};

    for (len = 0; len <= 15; len++)
        count[len] = 0;
    for (sym = 0; sym < codes; sym++)
        count[lens[sym]]++;

    root = *bits;
    for (max = 15; max >= 1; max--)
        if (count[max] != 0) break;
    if (root > max) root = max;
    if (max == 0) {
        thisent.op = (unsigned char)64;
        thisent.bits = (unsigned char)1;
        thisent.val = (unsigned short)0;
        *(*table)++ = thisent;
        *(*table)++ = thisent;
        *bits = 1;
        return 0;
    }
    for (min = 1; min <= 15; min++)
        if (count[min] != 0) break;
    if (root < min) root = min;

    left = 1;
    for (len = 1; len <= 15; len++) {
        left <<= 1;
        left -= count[len];
        if (left < 0) return -1;
    }
    if (left > 0 && (type == CODES || max != 1))
        return -1;

    offs[1] = 0;
    for (len = 1; len < 15; len++)
        offs[len + 1] = offs[len] + count[len];

    for (sym = 0; sym < codes; sym++)
        if (lens[sym] != 0) work[offs[lens[sym]]++] = (unsigned short)sym;

    switch (type) {
    case CODES:
        base = extra = work;
        end = 19;
        break;
    case LENS:
        base = lbase - 257;
        extra = lext - 257;
        end = 256;
        break;
    default:
        base = dbase;
        extra = dext;
        end = -1;
    }

    huff = 0;
    sym = 0;
    len = min;
    next = *table;
    curr = root;
    drop = 0;
    low = (unsigned)(-1);
    used = 1U << root;
    mask = used - 1;

    if (type == LENS && used >= ENOUGH - MAXD)
        return 1;

    for (;;) {
        thisent.bits = (unsigned char)(len - drop);
        if ((int)(work[sym]) < end) {
            thisent.op = (unsigned char)0;
            thisent.val = work[sym];
        } else if ((int)(work[sym]) > end) {
            thisent.op = (unsigned char)(extra[work[sym]]);
            thisent.val = base[work[sym]];
        } else {
            thisent.op = (unsigned char)(32 + 64);
            thisent.val = 0;
        }

        incr = 1U << (len - drop);
        fill = 1U << curr;
        min = fill;
        do {
            fill -= incr;
            next[(huff >> drop) + fill] = thisent;
        } while (fill != 0);

        incr = 1U << (len - 1);
        while (huff & incr)
            incr >>= 1;
        if (incr != 0) {
            huff &= incr - 1;
            huff += incr;
        } else
            huff = 0;

        sym++;
        if (--(count[len]) == 0) {
            if (len == max) break;
            len = lens[work[sym]];
        }

        if (len > root && (huff & mask) != low) {
            if (drop == 0)
                drop = root;

            next += min;

            curr = len - drop;
            left = (int)(1 << curr);
            while (curr + drop < max) {
                left -= count[curr + drop];
                if (left <= 0) break;
                curr++;
                left <<= 1;
            }

            used += 1U << curr;
            if (type == LENS && used >= ENOUGH - MAXD)
                return 1;

            low = huff & mask;
            (*table)[low].op = (unsigned char)curr;
            (*table)[low].bits = (unsigned char)root;
            (*table)[low].val = (unsigned short)(next - *table);
        }
    }

    thisent.op = (unsigned char)64;
    thisent.bits = (unsigned char)(len - drop);
    thisent.val = (unsigned short)0;
    while (huff != 0) {
        if (drop != 0 && (huff & mask) != low) {
            drop = 0;
            len = root;
            next = *table;
            thisent.bits = (unsigned char)len;
        }

        next[huff >> drop] = thisent;

        incr = 1U << (len - 1);
        while (huff & incr)
            incr >>= 1;
        if (incr != 0) {
            huff &= incr - 1;
            huff += incr;
        } else
            huff = 0;
    }

    *table += used;
    *bits = root;
    return 0;
}

/* ===========================================================================
 * png.c -- png_sig_cmp
 */
// @ 0x0086a8c0
int png_sig_cmp(png_bytep sig, unsigned start, unsigned num_to_check)
{
    unsigned char png_signature[8] = {137, 80, 78, 71, 13, 10, 26, 10};
    if (num_to_check > 8)
        num_to_check = 8;
    else if (num_to_check < 1)
        return (-1);

    if (start > 7)
        return (-1);

    if (start + num_to_check > 8)
        num_to_check = 8 - start;

    return ((int)(memcmp(&sig[start], &png_signature[start], num_to_check)));
}

/* ===========================================================================
 * pngerror.c -- png_default_error / png_default_warning
 */
typedef struct png_struct_def {
    unsigned int flags;
} png_struct_def;
typedef png_struct_def* png_structp;

// @ 0x0086aff0
static void png_default_error(png_structp png_ptr, png_const_charp error_message)
{
    if (*error_message == '#') {
        int offset;
        char error_number[16];
        for (offset = 0; offset < 15; offset++) {
            error_number[offset] = *(error_message + offset + 1);
            if (*(error_message + offset) == ' ')
                break;
        }
        if ((offset > 1) && (offset < 15)) {
            error_number[offset - 1] = '\0';
            fprintf(__iob_func() + 2, "libpng error no. %s: %s\n",
                    error_number, error_message + offset);
        } else {
            fprintf(__iob_func() + 2, "libpng error: %s, offset=%d\n",
                    error_message, offset);
        }
    } else {
        fprintf(__iob_func() + 2, "libpng error: %s\n", error_message);
    }

    if (png_ptr) {
        longjmp(png_ptr, 1);
    }
}

// @ 0x0086b110
static void png_default_warning(png_structp png_ptr, png_const_charp warning_message)
{
    if (*warning_message == '#') {
        int offset;
        char warning_number[16];
        for (offset = 0; offset < 15; offset++) {
            warning_number[offset] = *(warning_message + offset + 1);
            if (*(warning_message + offset) == ' ')
                break;
        }
        if ((offset > 1) && (offset < 15)) {
            warning_number[offset - 1] = '\0';
            fprintf(__iob_func() + 2, "libpng warning no. %s: %s\n",
                    warning_number, warning_message + offset);
        } else {
            fprintf(__iob_func() + 2, "libpng warning: %s\n", warning_message);
        }
    } else {
        fprintf(__iob_func() + 2, "libpng warning: %s\n", warning_message);
    }
    png_ptr = png_ptr;
}

/* ---------------------------------------------------------------------------
 * Stand-in callers: keep the TU-local (static) helpers referenced so cl emits
 * them, and pin their register conventions (params 1/2/3 -> eax/edx/ecx).
 * These are not part of the slice; they only shape the codegen of the
 * functions above.
 */
void slice_s008680d0_slow(z_streamp strm, int flush)
{
    deflate_slow((deflate_state*)strm->state, flush);
}

void slice_s008680d0_window(z_streamp strm, unsigned out)
{
    updatewindow(strm, out);
}

void slice_s008680d0_err(void* png_ptr, const char* msg)
{
    png_default_error((png_structp)png_ptr, msg);
    png_default_warning((png_structp)png_ptr, msg);
}
