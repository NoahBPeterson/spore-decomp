// Slice s00852860 -- libjpeg 6a Huffman encoder, compression-master init and
// main-controller + marker-emitter helpers, linked into SporeApp.exe.
//
// The up-front Huffman/main-controller/master routines are ordinary cdecl
// bodies and are reconstructed from the IJG 6a sources (jchuff.c, jcmainct.c,
// jcinit.c).  The marker helpers (emit_byte/emit_2bytes/emit_4bytes, emit_dqt,
// emit_dht) were built with whole-program optimisation and receive cinfo in a
// fixed register (ESI/EAX); they are rewritten with ordinary explicit
// arguments -- complete and faithful, not byte-exact.
//
// Flags: /O2 /MD /Gy /TP /GS-
//
// Struct offsets confirmed from the binary:
//   +0x000 err   +0x004 mem   +0x014 dest
//   +0x034 num_components   +0x03c comp_info
//   +0x040 quant_tbl_ptrs[4] +0x050 dc_huff_tbl_ptrs[4] +0x060 ac_huff_tbl_ptrs[4]
//   +0x0a0 num_scans  +0x0a8 raw_data_in  +0x0ac arith_code
//   +0x0b0 optimize_coding  +0x0c0 restart_interval  +0x0c8 write_JFIF_header
//   +0x0d4 write_Adobe_marker  +0x0dc progressive_mode
//   +0x0e0 max_h_samp_factor  +0x0e4 max_v_samp_factor
//   +0x0e8 total_iMCU_rows  +0x0ec comps_in_scan  +0x0f0 cur_comp_info[4]
//   +0x100 MCUs_per_row  +0x108 blocks_in_MCU  +0x10c MCU_membership[10]
//   +0x144 master +0x148 main +0x14c prep +0x150 coef +0x154 marker
//   +0x158 cconvert +0x15c downsample +0x160 fdct +0x164 entropy
//   +0x168 cinematic/AVI1 marker flag (set to 1 by jpeg_CreateCompress)
//   +0x16c spare (sizeof(jpeg_compress_struct) == 0x170)
//
// huff_entropy_encoder layout (size 0x6c):
//   +0x00 pub.start_pass  +0x04 pub.encode_mcu  +0x08 pub.finish_pass
//   +0x0c saved.put_buffer  +0x10 saved.put_bits  +0x14 saved.last_dc_val[4]
//   +0x24 restarts_to_go  +0x28 next_restart_num
//   +0x2c dc_derived_tbls[4] +0x3c ac_derived_tbls[4]
//   +0x4c dc_count_ptrs[4]   +0x5c ac_count_ptrs[4]
#include "types.h"

typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef unsigned int   UINT32;
typedef short          JCOEF;
typedef unsigned int   JDIMENSION;
typedef unsigned char  JOCTET;
typedef int            boolean;

#define FALSE 0
#define TRUE  1
#define NULL 0

#define NUM_QUANT_TBLS 4
#define NUM_HUFF_TBLS  4
#define MAX_COMPS_IN_SCAN 4
#define MAX_COMPONENTS 10
#define DCTSIZE 8
#define DCTSIZE2 64
#define JPOOL_IMAGE 1

#define M_SOI 0xD8
#define M_DQT 0xDB
#define M_DHT 0xC4

// jerror.h message codes
#define JERR_CANT_SUSPEND        0x16
#define JERR_HUFF_CLEN_OVERFLOW  0x26
#define JERR_NO_HUFF_TABLE       0x31
#define JERR_NO_QUANT_TABLE      0x33
#define JERR_BAD_BUFFER_MODE     0x04

typedef enum { JBUF_PASS_THRU = 0, JBUF_SAVE_SOURCE, JBUF_CRANK_DEST,
               JBUF_SAVE_AND_PASS } J_BUF_MODE;

// --------------------------------------------------------------- libjpeg types
struct jpeg_error_mgr {
    void (*error_exit)(void* cinfo);           // +0x00
    void* emit_message;                        // +0x04
    void* output_message;                      // +0x08
    void* format_message;                      // +0x0c
    void* reset_error_mgr;                     // +0x10
    int   msg_code;                            // +0x14
    union { int i[8]; char s[80]; } msg_parm;  // +0x18
};

struct jpeg_memory_mgr {
    void*  (*alloc_small)(void*, int, unsigned);             // +0x00
    void*  (*alloc_large)(void*, int, unsigned);             // +0x04
    void** (*alloc_sarray)(void*, int, unsigned, unsigned);  // +0x08
    void** (*alloc_barray)(void*, int, unsigned, unsigned);  // +0x0c
    void*  (*request_virt_sarray)(void*, int, int, unsigned, unsigned, unsigned);
    void*  (*request_virt_barray)(void*, int, int, unsigned, unsigned, unsigned);
    void   (*realize_virt_arrays)(void*);                    // +0x18
    void*  (*access_virt_sarray)(void*, void*, unsigned, unsigned, int);
    void*  (*access_virt_barray)(void*, void*, unsigned, unsigned, int);
    void   (*free_pool)(void*, int);
    void   (*self_destruct)(void*);
    long   max_memory_to_use;
};

struct jpeg_destination_mgr {
    JOCTET* next_output_byte;                  // +0x00
    unsigned free_in_buffer;                   // +0x04
    void   (*init_destination)(void*);         // +0x08
    int    (*empty_output_buffer)(void*);      // +0x0c
    void   (*term_destination)(void*);         // +0x10
};

struct JQUANT_TBL {
    UINT16 quantval[64];                       // +0x00
    boolean sent_table;                        // +0x80
};

struct JHUFF_TBL {
    UINT8 bits[17];                            // +0x00
    UINT8 huffval[256];                        // +0x11
    boolean sent_table;                        // +0x114
};

struct jpeg_component_info {
    int component_id;                          // +0x00
    int component_index;                       // +0x04
    int h_samp_factor;                         // +0x08
    int v_samp_factor;                         // +0x0c
    int quant_tbl_no;                          // +0x10
    int dc_tbl_no;                             // +0x14
    int ac_tbl_no;                             // +0x18
    JDIMENSION width_in_blocks;                // +0x1c
    JDIMENSION height_in_blocks;               // +0x20
    JDIMENSION downsampled_width;              // +0x24
    JDIMENSION downsampled_height;             // +0x28
    int component_needed;                      // +0x2c
    int MCU_width;                             // +0x30
    int MCU_height;                            // +0x34
    int MCU_blocks;                            // +0x38
    int MCU_sample_width;                      // +0x3c
    int last_col_width;                        // +0x40
    int last_row_height;                       // +0x44
    struct JQUANT_TBL* quant_table;            // +0x48
    void* dct_table;                           // +0x4c
    int pad_50;                                // +0x50
};

struct jpeg_compress_struct;

struct jpeg_c_main_controller {
    void (*start_pass)(struct jpeg_compress_struct*, J_BUF_MODE);           // +0x00
    void (*process_data)(struct jpeg_compress_struct*, UINT8**,
                         JDIMENSION*, JDIMENSION);                         // +0x04
};

struct jpeg_c_prep_controller {
    void (*start_pass)(struct jpeg_compress_struct*, J_BUF_MODE);           // +0x00
    void (*pre_process_data)(struct jpeg_compress_struct*, UINT8**, JDIMENSION*,
                             JDIMENSION, UINT8***, JDIMENSION*, JDIMENSION); // +0x04
};

struct jpeg_c_coef_controller {
    void (*start_pass)(struct jpeg_compress_struct*, J_BUF_MODE);           // +0x00
    boolean (*compress_data)(struct jpeg_compress_struct*, UINT8***);       // +0x04
};

struct jpeg_marker_writer {
    void (*write_any_marker)(struct jpeg_compress_struct*, int,
                             const JOCTET*, unsigned);                      // +0x00
    void (*write_file_header)(struct jpeg_compress_struct*);                // +0x04
    void (*write_frame_header)(struct jpeg_compress_struct*);               // +0x08
    void (*write_scan_header)(struct jpeg_compress_struct*);                // +0x0c
    void (*write_file_trailer)(struct jpeg_compress_struct*);               // +0x10
    void (*write_tables_only)(struct jpeg_compress_struct*);                // +0x14
};

struct c_derived_tbl;

struct jpeg_entropy_encoder {
    void    (*start_pass)(struct jpeg_compress_struct*, boolean);           // +0x00
    boolean (*encode_mcu)(struct jpeg_compress_struct*, JCOEF***);          // +0x04
    void    (*finish_pass)(struct jpeg_compress_struct*);                   // +0x08
};

struct jpeg_compress_struct {
    struct jpeg_error_mgr*   err;              // +0x000
    struct jpeg_memory_mgr*  mem;              // +0x004
    void*                    progress;         // +0x008
    int                      is_decompressor;  // +0x00c
    int                      global_state;     // +0x010
    struct jpeg_destination_mgr* dest;         // +0x014
    JDIMENSION image_width;                    // +0x018
    JDIMENSION image_height;                   // +0x01c
    int        input_components;               // +0x020
    int        in_color_space;                 // +0x024
    double     input_gamma;                    // +0x028
    int        data_precision;                 // +0x030
    int        num_components;                 // +0x034
    int        jpeg_color_space;               // +0x038
    struct jpeg_component_info* comp_info;     // +0x03c
    struct JQUANT_TBL* quant_tbl_ptrs[NUM_QUANT_TBLS]; // +0x040
    struct JHUFF_TBL*  dc_huff_tbl_ptrs[NUM_HUFF_TBLS]; // +0x050
    struct JHUFF_TBL*  ac_huff_tbl_ptrs[NUM_HUFF_TBLS]; // +0x060
    UINT8 arith_dc_L[16];                      // +0x070
    UINT8 arith_dc_U[16];                      // +0x080
    UINT8 arith_ac_K[16];                      // +0x090
    int num_scans;                             // +0x0a0
    const void* scan_info;                     // +0x0a4
    boolean raw_data_in;                       // +0x0a8
    boolean arith_code;                        // +0x0ac
    boolean optimize_coding;                   // +0x0b0
    boolean CCIR601_sampling;                  // +0x0b4
    int smoothing_factor;                      // +0x0b8
    int dct_method;                            // +0x0bc
    unsigned int restart_interval;             // +0x0c0
    int restart_in_rows;                       // +0x0c4
    boolean write_JFIF_header;                 // +0x0c8
    UINT8 density_unit;                        // +0x0cc
    UINT16 X_density;                          // +0x0d0
    UINT16 Y_density;                          // +0x0d2
    boolean write_Adobe_marker;                // +0x0d4
    JDIMENSION next_scanline;                  // +0x0d8
    boolean progressive_mode;                  // +0x0dc
    int max_h_samp_factor;                     // +0x0e0
    int max_v_samp_factor;                     // +0x0e4
    JDIMENSION total_iMCU_rows;                // +0x0e8
    int comps_in_scan;                         // +0x0ec
    struct jpeg_component_info* cur_comp_info[MAX_COMPS_IN_SCAN]; // +0x0f0
    JDIMENSION MCUs_per_row;                   // +0x100
    JDIMENSION MCU_rows_in_scan;               // +0x104
    int blocks_in_MCU;                         // +0x108
    int MCU_membership[10];                    // +0x10c
    int Ss, Se, Ah, Al;                        // +0x134
    struct jpeg_comp_master* master;           // +0x144
    struct jpeg_c_main_controller* main;       // +0x148
    struct jpeg_c_prep_controller* prep;       // +0x14c
    struct jpeg_c_coef_controller* coef;       // +0x150
    struct jpeg_marker_writer* marker;         // +0x154
    struct jpeg_color_converter* cconvert;     // +0x158
    struct jpeg_downsampler* downsample;       // +0x15c
    struct jpeg_forward_dct* fdct;             // +0x160
    struct jpeg_entropy_encoder* entropy;      // +0x164
    boolean avi1_markers;                      // +0x168
    int     pad_16c;                           // +0x16c
};

typedef jpeg_compress_struct* j_compress_ptr;

struct c_derived_tbl {
    struct JHUFF_TBL* pub;                     // +0x00
    int   ehufco[256];                         // +0x04
    char  ehufsi[256];                         // +0x404
};

typedef struct {
    int put_buffer;                            // +0x00
    int put_bits;                              // +0x04
    int last_dc_val[MAX_COMPS_IN_SCAN];        // +0x08
} savable_state;

typedef struct {
    JOCTET* next_output_byte;                  // +0x00
    unsigned free_in_buffer;                   // +0x04
    savable_state cur;                         // +0x08
    j_compress_ptr cinfo;                      // +0x20
} working_state;

struct huff_entropy_encoder {
    struct jpeg_entropy_encoder pub;           // +0x00
    savable_state saved;                       // +0x0c
    unsigned int restarts_to_go;               // +0x24
    int next_restart_num;                      // +0x28
    c_derived_tbl* dc_derived_tbls[NUM_HUFF_TBLS]; // +0x2c
    c_derived_tbl* ac_derived_tbls[NUM_HUFF_TBLS]; // +0x3c
    long* dc_count_ptrs[NUM_HUFF_TBLS];        // +0x4c
    long* ac_count_ptrs[NUM_HUFF_TBLS];        // +0x5c
};

typedef struct {
    struct jpeg_c_main_controller pub;         // +0x00
    JDIMENSION cur_iMCU_row;                   // +0x08
    JDIMENSION rowgroup_ctr;                   // +0x0c
    boolean suspended;                         // +0x10
    J_BUF_MODE pass_mode;                      // +0x14
    UINT8** buffer[MAX_COMPONENTS];            // +0x18
} my_main_controller;

typedef my_main_controller* my_main_ptr;

// -------------------------------------------------------------------- macros
#define ERREXIT(c, code) \
    do { (c)->err->msg_code = (code); (*(c)->err->error_exit)((void*)(c)); } while (0)
#define ERREXIT1(c, code, p1) \
    do { (c)->err->msg_code = (code); (c)->err->msg_parm.i[0] = (p1); \
         (*(c)->err->error_exit)((void*)(c)); } while (0)
#define MEMZERO(target, size) memset((void*)(target), 0, (unsigned)(size))

#define INLINE __forceinline
#define ASSIGN_STATE(dest, src) ((dest) = (src))

extern "C" void* memset(void*, int, unsigned);
extern "C" void* memcpy(void*, const void*, unsigned);

// data tables shared with the rest of the JPEG library
extern "C" const int jpeg_natural_order[];   // 0x0141e880

// ---------------------------------------------------------------- out of slice
void jpeg_make_c_derived_tbl(j_compress_ptr, struct JHUFF_TBL*, c_derived_tbl**); // 0x00852300
struct JHUFF_TBL* jpeg_alloc_huff_table(void*);                                   // 0x00854f00
boolean emit_bits(working_state* state, unsigned int code, int size);             // 0x00852400
boolean encode_mcu_huff(j_compress_ptr, JCOEF***);                                // 0x00852700
void jinit_c_master_control(j_compress_ptr, boolean);                             // 0x00854db0
void jinit_color_converter(j_compress_ptr);                                       // 0x00851400
void jinit_downsampler(j_compress_ptr);                                           // 0x008575b0
void jinit_c_prep_controller(j_compress_ptr, boolean);                            // 0x00856cf0
void jinit_forward_dct(j_compress_ptr);                                           // 0x00852260
void jinit_phuff_encoder(j_compress_ptr);                                         // 0x00856750
void jinit_c_coef_controller(j_compress_ptr, boolean);                            // 0x00850e30
void jinit_marker_writer(j_compress_ptr);                                         // 0x00854290

// forward declarations
void  finish_pass_huff(j_compress_ptr);
void  htest_one_block(JCOEF* block, int last_dc_val, long* dc_counts, long* ac_counts);
boolean encode_mcu_gather(j_compress_ptr, JCOEF***);
void  jpeg_gen_optimal_table(j_compress_ptr, struct JHUFF_TBL*, long* freq);
void  finish_pass_gather(j_compress_ptr);
void  start_pass_huff(j_compress_ptr, boolean);
void  jinit_huff_encoder(j_compress_ptr);
void  jinit_compress_master(j_compress_ptr);
void  process_data_simple_main(j_compress_ptr, UINT8**, JDIMENSION*, JDIMENSION);
void  start_pass_main(j_compress_ptr, J_BUF_MODE);
void  jinit_c_main_controller(j_compress_ptr, boolean);
void  emit_marker(j_compress_ptr, int);
void  emit_2bytes(j_compress_ptr, int);
void  emit_4bytes(j_compress_ptr, int);
int   emit_dqt(j_compress_ptr, int);
void  emit_dht(j_compress_ptr, int, boolean);
void  emit_byte(j_compress_ptr, int);

// ================================================================ 0x00852860
// jchuff.c finish_pass_huff
// @ 0x00852860
void finish_pass_huff(j_compress_ptr cinfo)
{
    huff_entropy_encoder* entropy = (huff_entropy_encoder*)cinfo->entropy;
    working_state state;

    state.next_output_byte = cinfo->dest->next_output_byte;
    state.free_in_buffer = cinfo->dest->free_in_buffer;
    ASSIGN_STATE(state.cur, entropy->saved);
    state.cinfo = cinfo;

    if (!emit_bits(&state, 0x7F, 7))
        ERREXIT(cinfo, JERR_CANT_SUSPEND);
    state.cur.put_buffer = 0;
    state.cur.put_bits = 0;

    cinfo->dest->next_output_byte = state.next_output_byte;
    cinfo->dest->free_in_buffer = state.free_in_buffer;
    ASSIGN_STATE(entropy->saved, state.cur);
}

// ================================================================ 0x00852930
// jchuff.c htest_one_block
// @ 0x00852930
void htest_one_block(JCOEF* block, int last_dc_val, long* dc_counts,
                     long* ac_counts)
{
    int temp;
    int nbits;
    int k, r;

    temp = block[0] - last_dc_val;
    if (temp < 0)
        temp = -temp;

    nbits = 0;
    while (temp) {
        nbits++;
        temp >>= 1;
    }

    dc_counts[nbits]++;

    r = 0;
    for (k = 1; k < DCTSIZE2; k++) {
        if ((temp = block[jpeg_natural_order[k]]) == 0) {
            r++;
        } else {
            while (r > 15) {
                ac_counts[0xF0]++;
                r -= 16;
            }

            if (temp < 0)
                temp = -temp;

            nbits = 1;
            while ((temp >>= 1))
                nbits++;

            ac_counts[(r << 4) + nbits]++;
            r = 0;
        }
    }

    if (r > 0)
        ac_counts[0]++;
}

// ================================================================ 0x008529d0
// jchuff.c encode_mcu_gather
// @ 0x008529d0
boolean encode_mcu_gather(j_compress_ptr cinfo, JCOEF*** MCU_data)
{
    huff_entropy_encoder* entropy = (huff_entropy_encoder*)cinfo->entropy;
    int blkn, ci;
    struct jpeg_component_info* compptr;

    if (cinfo->restart_interval) {
        if (entropy->restarts_to_go == 0) {
            for (ci = 0; ci < cinfo->comps_in_scan; ci++)
                entropy->saved.last_dc_val[ci] = 0;
            entropy->restarts_to_go = cinfo->restart_interval;
        }
        entropy->restarts_to_go--;
    }

    for (blkn = 0; blkn < cinfo->blocks_in_MCU; blkn++) {
        ci = cinfo->MCU_membership[blkn];
        compptr = cinfo->cur_comp_info[ci];
        htest_one_block(MCU_data[blkn][0], entropy->saved.last_dc_val[ci],
                        entropy->dc_count_ptrs[compptr->dc_tbl_no],
                        entropy->ac_count_ptrs[compptr->ac_tbl_no]);
        entropy->saved.last_dc_val[ci] = MCU_data[blkn][0][0];
    }

    return TRUE;
}

// ================================================================ 0x00852aa0
// jchuff.c jpeg_gen_optimal_table
// @ 0x00852aa0
void jpeg_gen_optimal_table(j_compress_ptr cinfo, struct JHUFF_TBL* htbl,
                            long* freq)
{
#define MAX_CLEN 32
    UINT8 bits[MAX_CLEN + 1];
    int codesize[257];
    int others[257];
    int c1, c2;
    int p, i, j;
    long v;

    MEMZERO(bits, sizeof(bits));
    MEMZERO(codesize, sizeof(codesize));
    for (i = 0; i < 257; i++)
        others[i] = -1;

    freq[256] = 1;

    for (;;) {
        c1 = -1;
        v = 1000000000L;
        for (i = 0; i <= 256; i++) {
            if (freq[i] && freq[i] <= v) {
                v = freq[i];
                c1 = i;
            }
        }

        c2 = -1;
        v = 1000000000L;
        for (i = 0; i <= 256; i++) {
            if (freq[i] && freq[i] <= v && i != c1) {
                v = freq[i];
                c2 = i;
            }
        }

        if (c2 < 0)
            break;

        freq[c1] += freq[c2];
        freq[c2] = 0;

        codesize[c1]++;
        while (others[c1] >= 0) {
            c1 = others[c1];
            codesize[c1]++;
        }

        others[c1] = c2;

        codesize[c2]++;
        while (others[c2] >= 0) {
            c2 = others[c2];
            codesize[c2]++;
        }
    }

    for (i = 0; i <= 256; i++) {
        if (codesize[i]) {
            if (codesize[i] > MAX_CLEN)
                ERREXIT(cinfo, JERR_HUFF_CLEN_OVERFLOW);

            bits[codesize[i]]++;
        }
    }

    for (i = MAX_CLEN; i > 16; i--) {
        while (bits[i] > 0) {
            j = i - 2;
            while (bits[j] == 0)
                j--;

            bits[i] -= 2;
            bits[i - 1]++;
            bits[j + 1] += 2;
            bits[j]--;
        }
    }

    while (bits[i] == 0)
        i--;

    bits[i]--;

    memcpy(htbl->bits, bits, sizeof(htbl->bits));

    p = 0;
    for (i = 1; i <= MAX_CLEN; i++) {
        for (j = 0; j <= 255; j++) {
            if (codesize[j] == i)
                htbl->huffval[p++] = (UINT8)j;
        }
    }

    htbl->sent_table = FALSE;
}

// ================================================================ 0x00852cf0
// jchuff.c finish_pass_gather
// @ 0x00852cf0
void finish_pass_gather(j_compress_ptr cinfo)
{
    huff_entropy_encoder* entropy = (huff_entropy_encoder*)cinfo->entropy;
    int ci, dctbl, actbl;
    struct jpeg_component_info* compptr;
    struct JHUFF_TBL** htblptr;
    boolean did_dc[NUM_HUFF_TBLS], did_ac[NUM_HUFF_TBLS];

    MEMZERO(did_dc, sizeof(did_dc));
    MEMZERO(did_ac, sizeof(did_ac));

    for (ci = 0; ci < cinfo->comps_in_scan; ci++) {
        compptr = cinfo->cur_comp_info[ci];
        dctbl = compptr->dc_tbl_no;
        actbl = compptr->ac_tbl_no;
        if (!did_dc[dctbl]) {
            htblptr = &cinfo->dc_huff_tbl_ptrs[dctbl];
            if (*htblptr == NULL)
                *htblptr = jpeg_alloc_huff_table((void*)cinfo);
            jpeg_gen_optimal_table(cinfo, *htblptr,
                                   entropy->dc_count_ptrs[dctbl]);
            did_dc[dctbl] = TRUE;
        }
        if (!did_ac[actbl]) {
            htblptr = &cinfo->ac_huff_tbl_ptrs[actbl];
            if (*htblptr == NULL)
                *htblptr = jpeg_alloc_huff_table((void*)cinfo);
            jpeg_gen_optimal_table(cinfo, *htblptr,
                                   entropy->ac_count_ptrs[actbl]);
            did_ac[actbl] = TRUE;
        }
    }
}

// ================================================================ 0x00852df0
// jchuff.c start_pass_huff
// @ 0x00852df0
void start_pass_huff(j_compress_ptr cinfo, boolean gather_statistics)
{
    huff_entropy_encoder* entropy = (huff_entropy_encoder*)cinfo->entropy;
    int ci, dctbl, actbl;
    struct jpeg_component_info* compptr;

    if (gather_statistics) {
        entropy->pub.encode_mcu = encode_mcu_gather;
        entropy->pub.finish_pass = finish_pass_gather;
    } else {
        entropy->pub.encode_mcu = encode_mcu_huff;
        entropy->pub.finish_pass = finish_pass_huff;
    }

    for (ci = 0; ci < cinfo->comps_in_scan; ci++) {
        compptr = cinfo->cur_comp_info[ci];
        dctbl = compptr->dc_tbl_no;
        actbl = compptr->ac_tbl_no;
        if (dctbl < 0 || dctbl >= NUM_HUFF_TBLS ||
            (cinfo->dc_huff_tbl_ptrs[dctbl] == NULL && !gather_statistics))
            ERREXIT1(cinfo, JERR_NO_HUFF_TABLE, dctbl);
        if (actbl < 0 || actbl >= NUM_HUFF_TBLS ||
            (cinfo->ac_huff_tbl_ptrs[actbl] == NULL && !gather_statistics))
            ERREXIT1(cinfo, JERR_NO_HUFF_TABLE, actbl);
        if (gather_statistics) {
            if (entropy->dc_count_ptrs[dctbl] == NULL)
                entropy->dc_count_ptrs[dctbl] = (long*)
                    (*cinfo->mem->alloc_small)((void*)cinfo, JPOOL_IMAGE,
                                               257 * sizeof(long));
            MEMZERO(entropy->dc_count_ptrs[dctbl], 257 * sizeof(long));
            if (entropy->ac_count_ptrs[actbl] == NULL)
                entropy->ac_count_ptrs[actbl] = (long*)
                    (*cinfo->mem->alloc_small)((void*)cinfo, JPOOL_IMAGE,
                                               257 * sizeof(long));
            MEMZERO(entropy->ac_count_ptrs[actbl], 257 * sizeof(long));
        } else {
            jpeg_make_c_derived_tbl(cinfo, cinfo->dc_huff_tbl_ptrs[dctbl],
                                    &entropy->dc_derived_tbls[dctbl]);
            jpeg_make_c_derived_tbl(cinfo, cinfo->ac_huff_tbl_ptrs[actbl],
                                    &entropy->ac_derived_tbls[actbl]);
        }
        entropy->saved.last_dc_val[ci] = 0;
    }

    entropy->saved.put_buffer = 0;
    entropy->saved.put_bits = 0;

    entropy->restarts_to_go = cinfo->restart_interval;
    entropy->next_restart_num = 0;
}

// ================================================================ 0x00852f90
// jchuff.c jinit_huff_encoder
// @ 0x00852f90
void jinit_huff_encoder(j_compress_ptr cinfo)
{
    huff_entropy_encoder* entropy;
    int i;

    entropy = (huff_entropy_encoder*)
        (*cinfo->mem->alloc_small)((void*)cinfo, JPOOL_IMAGE,
                                   sizeof(huff_entropy_encoder));
    cinfo->entropy = (struct jpeg_entropy_encoder*)entropy;
    entropy->pub.start_pass = start_pass_huff;

    for (i = 0; i < NUM_HUFF_TBLS; i++) {
        entropy->dc_derived_tbls[i] = entropy->ac_derived_tbls[i] = NULL;
        entropy->dc_count_ptrs[i] = entropy->ac_count_ptrs[i] = NULL;
    }
}

// ================================================================ 0x00852ff0
// jcinit.c jinit_compress_master
// @ 0x00852ff0
void jinit_compress_master(j_compress_ptr cinfo)
{
    jinit_c_master_control(cinfo, FALSE);

    if (!cinfo->raw_data_in) {
        jinit_color_converter(cinfo);
        jinit_downsampler(cinfo);
        jinit_c_prep_controller(cinfo, FALSE);
    }
    jinit_forward_dct(cinfo);
    if (cinfo->arith_code) {
        ERREXIT(cinfo, 1 /* JERR_ARITH_NOTIMPL */);
    } else {
        if (cinfo->progressive_mode)
            jinit_phuff_encoder(cinfo);
        else
            jinit_huff_encoder(cinfo);
    }

    jinit_c_coef_controller(cinfo,
                            (cinfo->num_scans > 1 || cinfo->optimize_coding));
    jinit_c_main_controller(cinfo, FALSE);

    jinit_marker_writer(cinfo);

    (*cinfo->mem->realize_virt_arrays)((void*)cinfo);

    (*cinfo->marker->write_file_header)(cinfo);
}

// ================================================================ 0x008530b0
// jcmainct.c process_data_simple_main
// @ 0x008530b0
void process_data_simple_main(j_compress_ptr cinfo, UINT8** input_buf,
                              JDIMENSION* in_row_ctr, JDIMENSION in_rows_avail)
{
    my_main_ptr main = (my_main_ptr)cinfo->main;

    while (main->cur_iMCU_row < cinfo->total_iMCU_rows) {
        if (main->rowgroup_ctr < DCTSIZE)
            (*cinfo->prep->pre_process_data)(cinfo, input_buf, in_row_ctr,
                                             in_rows_avail, main->buffer,
                                             &main->rowgroup_ctr,
                                             (JDIMENSION)DCTSIZE);

        if (main->rowgroup_ctr != DCTSIZE)
            return;

        if (!(*cinfo->coef->compress_data)(cinfo, main->buffer)) {
            if (!main->suspended) {
                (*in_row_ctr)--;
                main->suspended = TRUE;
            }
            return;
        }
        if (main->suspended) {
            (*in_row_ctr)++;
            main->suspended = FALSE;
        }
        main->cur_iMCU_row++;
        main->rowgroup_ctr = 0;
    }
}

// ================================================================ 0x00853160
// jcmainct.c start_pass_main
// @ 0x00853160
void start_pass_main(j_compress_ptr cinfo, J_BUF_MODE pass_mode)
{
    my_main_ptr main = (my_main_ptr)cinfo->main;

    if (cinfo->raw_data_in)
        return;

    main->cur_iMCU_row = 0;
    main->rowgroup_ctr = 0;
    main->suspended = FALSE;
    main->pass_mode = pass_mode;

    switch (pass_mode) {
    case JBUF_PASS_THRU:
        main->pub.process_data = process_data_simple_main;
        break;
    default:
        ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
        break;
    }
}

// ================================================================ 0x008531b0
// jcmainct.c jinit_c_main_controller
// @ 0x008531b0
void jinit_c_main_controller(j_compress_ptr cinfo, boolean need_full_buffer)
{
    my_main_ptr main;
    int ci;
    struct jpeg_component_info* compptr;

    main = (my_main_ptr)
        (*cinfo->mem->alloc_small)((void*)cinfo, JPOOL_IMAGE,
                                   sizeof(my_main_controller));
    cinfo->main = (struct jpeg_c_main_controller*)main;
    main->pub.start_pass = start_pass_main;

    if (cinfo->raw_data_in)
        return;

    if (need_full_buffer) {
        ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
    } else {
        for (ci = 0, compptr = cinfo->comp_info;
             ci < cinfo->num_components; ci++, compptr++) {
            main->buffer[ci] = (UINT8**)(*cinfo->mem->alloc_sarray)
                ((void*)cinfo, JPOOL_IMAGE,
                 compptr->width_in_blocks * DCTSIZE,
                 (JDIMENSION)(compptr->v_samp_factor * DCTSIZE));
        }
    }
}

// ================================================================ 0x00853240
// jcmarker.c emit_marker (cinfo in ESI in the original)
// @ 0x00853240
void emit_marker(j_compress_ptr cinfo, int mark)
{
    emit_byte(cinfo, 0xFF);
    emit_byte(cinfo, mark);
}

// ================================================================ 0x008532b0
// jcmarker.c emit_2bytes (cinfo in ESI, value in EBX in the original)
// @ 0x008532b0
void emit_2bytes(j_compress_ptr cinfo, int value)
{
    emit_byte(cinfo, (value >> 8) & 0xFF);
    emit_byte(cinfo, value & 0xFF);
}

// ================================================================ 0x00853320
// jcmarker.c emit_4bytes (cinfo in ESI, value in EBX in the original)
// @ 0x00853320
void emit_4bytes(j_compress_ptr cinfo, int value)
{
    emit_byte(cinfo, (value >> 24) & 0xFF);
    emit_byte(cinfo, (value >> 16) & 0xFF);
    emit_byte(cinfo, (value >> 8) & 0xFF);
    emit_byte(cinfo, value & 0xFF);
}

// ================================================================ 0x008533f0
// jcmarker.c emit_dqt (cinfo in EAX in the original).  Returns precision.
// @ 0x008533f0
int emit_dqt(j_compress_ptr cinfo, int index)
{
    struct JQUANT_TBL* qtbl = cinfo->quant_tbl_ptrs[index];
    int prec;
    int i;

    if (qtbl == NULL)
        ERREXIT1(cinfo, JERR_NO_QUANT_TABLE, index);

    prec = 0;
    for (i = 0; i < DCTSIZE2; i++) {
        if (qtbl->quantval[i] > 255)
            prec = 1;
    }

    if (!qtbl->sent_table) {
        emit_marker(cinfo, M_DQT);

        emit_2bytes(cinfo, prec ? DCTSIZE2 * 2 + 1 + 2 : DCTSIZE2 + 1 + 2);

        emit_byte(cinfo, index + (prec << 4));

        for (i = 0; i < DCTSIZE2; i++) {
            unsigned int qval = qtbl->quantval[jpeg_natural_order[i]];
            if (prec)
                emit_byte(cinfo, qval >> 8);
            emit_byte(cinfo, qval & 0xFF);
        }

        qtbl->sent_table = TRUE;
    }

    return prec;
}

// ================================================================ 0x008535d0
// jcmarker.c emit_dht (cinfo in EAX in the original)
// @ 0x008535d0
void emit_dht(j_compress_ptr cinfo, int index, boolean is_ac)
{
    struct JHUFF_TBL* htbl;
    int length, i;

    if (!cinfo->avi1_markers)
        return;

    if (is_ac) {
        htbl = cinfo->ac_huff_tbl_ptrs[index];
        index += 0x10;
    } else {
        htbl = cinfo->dc_huff_tbl_ptrs[index];
    }

    if (htbl == NULL)
        ERREXIT1(cinfo, JERR_NO_HUFF_TABLE, index);

    if (!htbl->sent_table) {
        emit_marker(cinfo, M_DHT);

        length = 0;
        for (i = 1; i <= 16; i++)
            length += htbl->bits[i];

        emit_2bytes(cinfo, length + 2 + 1 + 16);
        emit_byte(cinfo, index);

        for (i = 1; i <= 16; i++)
            emit_byte(cinfo, htbl->bits[i]);

        for (i = 0; i < length; i++)
            emit_byte(cinfo, htbl->huffval[i]);

        htbl->sent_table = TRUE;
    }
}

// ================================================================ emit_byte
// jcmarker.c emit_byte, inlined by every caller above in the original.
INLINE void emit_byte(j_compress_ptr cinfo, int val)
{
    struct jpeg_destination_mgr* dest = cinfo->dest;

    *(dest->next_output_byte)++ = (JOCTET)val;
    if (--dest->free_in_buffer == 0) {
        if (!(*dest->empty_output_buffer)((void*)cinfo))
            ERREXIT(cinfo, JERR_CANT_SUSPEND);
    }
}
