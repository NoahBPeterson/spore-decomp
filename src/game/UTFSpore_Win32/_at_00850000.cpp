// src/game/UTFSpore_Win32/_at_00850000.cpp -- migrated from slice(s) s0085d930, s0085cb00, s0085ad60, s008571b0, s008544e0, s00852860, s0084faf0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_00850000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern void jinit_memory_mgr(void*);       // 0x008639f0
extern void FUN_00854e70(void*);           // 0x00854e70
extern void* jpeg_alloc_node(void* cinfo, int n, int size);

// ---- items of slice s0084faf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void jinit_memory_mgr(void*);       // 0x008639f0
extern void FUN_00854e70(void*);           // 0x00854e70
extern void* jpeg_alloc_node(void* cinfo, int n, int size);
// ---- items of slice s0084faf0 end

// ---- items of slice s00852860 begin (TODO(rewrite): local stubs, replace by canonical classes)
#ifndef NULL
#define NULL 0
#endif
extern "C" void* memset(void*, int, unsigned);
extern "C" void* memcpy(void*, const void*, unsigned);
extern "C" const int jpeg_natural_order[];   // 0x0141e880
typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef short          JCOEF;
typedef unsigned int   JDIMENSION;
typedef unsigned char  JOCTET;
typedef int            boolean;
#define FALSE 0
#define TRUE  1
#define NUM_QUANT_TBLS 4
#define NUM_HUFF_TBLS  4
#define MAX_COMPS_IN_SCAN 4
#define MAX_COMPONENTS 10
#define DCTSIZE 8
#define DCTSIZE2 64
#define JPOOL_IMAGE 1
#define M_DQT 0xDB
#define M_DHT 0xC4
#define JERR_CANT_SUSPEND        0x16
#define JERR_HUFF_CLEN_OVERFLOW  0x26
#define JERR_NO_HUFF_TABLE       0x31
#define JERR_NO_QUANT_TABLE      0x33
#define JERR_BAD_BUFFER_MODE     0x04
typedef enum { JBUF_PASS_THRU = 0, JBUF_SAVE_SOURCE, JBUF_CRANK_DEST,
               JBUF_SAVE_AND_PASS } J_BUF_MODE;
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
#define ERREXIT(c, code) \
    do { (c)->err->msg_code = (code); (*(c)->err->error_exit)((void*)(c)); } while (0)
#define ERREXIT1(c, code, p1) \
    do { (c)->err->msg_code = (code); (c)->err->msg_parm.i[0] = (p1); \
         (*(c)->err->error_exit)((void*)(c)); } while (0)
#define MEMZERO(target, size) memset((void*)(target), 0, (unsigned)(size))
#define INLINE __forceinline
#define ASSIGN_STATE(dest, src) ((dest) = (src))
void jpeg_make_c_derived_tbl(j_compress_ptr, struct JHUFF_TBL*, c_derived_tbl**); // 0x00852300
struct JHUFF_TBL* jpeg_alloc_huff_table(void*);                                   // 0x00854f00
boolean emit_bits(working_state* state, unsigned int code, int size);             // 0x00852400
boolean encode_mcu_huff(j_compress_ptr, JCOEF***);                                // 0x00852700
void  finish_pass_huff(j_compress_ptr);
void  htest_one_block(JCOEF* block, int last_dc_val, long* dc_counts, long* ac_counts);
boolean encode_mcu_gather(j_compress_ptr, JCOEF***);
void  jpeg_gen_optimal_table(j_compress_ptr, struct JHUFF_TBL*, long* freq);
void  finish_pass_gather(j_compress_ptr);
void  start_pass_huff(j_compress_ptr, boolean);
void  jinit_huff_encoder(j_compress_ptr);
void  process_data_simple_main(j_compress_ptr, UINT8**, JDIMENSION*, JDIMENSION);
void  start_pass_main(j_compress_ptr, J_BUF_MODE);
void  emit_marker(j_compress_ptr, int);
void  emit_2bytes(j_compress_ptr, int);
void  emit_4bytes(j_compress_ptr, int);
int   emit_dqt(j_compress_ptr, int);
void  emit_dht(j_compress_ptr, int, boolean);
void  emit_byte(j_compress_ptr, int);
INLINE void emit_byte(j_compress_ptr cinfo, int val)
{
    struct jpeg_destination_mgr* dest = cinfo->dest;

    *(dest->next_output_byte)++ = (JOCTET)val;
    if (--dest->free_in_buffer == 0) {
        if (!(*dest->empty_output_buffer)((void*)cinfo))
            ERREXIT(cinfo, JERR_CANT_SUSPEND);
    }
}
// ---- items of slice s00852860 end

// ---- items of slice s008544e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cTerrainExport;
struct cJob {
    void** mVtbl;                    // +0x00
    int    m04;
    int    m08;
    int    m0C;
    int    m10;
    int    m14;                      // error code
    int    m18;                      // error arg0
    int    m1C;                      // error arg1
    int    m20;                      // error arg2
    void   Error() { ((void(__thiscall*)(cJob*))mVtbl[0])(this); }
};
struct cSlot {
    void* pfn0;                      // +0x00 = 0x00854b60
    void* pfn4;                      // +0x04 = 0x00854d10
    void* pfn8;                      // +0x08 = 0x00854d40
    int   m0C;                       // +0x0c
    int   m10;                       // +0x10
    int   m14;                       // +0x14  state
    int   m18;                       // +0x18  progress
    int   m1C;                       // +0x1c  total
    int   m20;                       // +0x20  extra counter
};
struct cLevel {
    int  m00;
    int  m04;
    int  m08;
    int  m0C;
    int  m10;
    int  m14;
    int  m18;
    int  m1C;
    int  m20;
    int  m24;
    int  m28;
    int  m2C;
    int  m30;
    int  m34;
    int  m38;
    int  m3C;
    int  m40;
    int  m44;
    int  m48;
};
struct cTerrainExport
{
    cJob*  mJob;                     // +0x000  (vtable-bearing error reporter)
    void** mAllocVtbl;               // +0x004  allocator vtable: slots called as Ty(this,...)
    void*  m008;                     // +0x008  optional progress sink
    int    m00C;                     // +0x00c
    int    m010;                     // +0x010
    int    m014;                     // +0x014
    int    m018;                     // +0x018
    int    m01C;                     // +0x01c
    int    m020;                     // +0x020
    int    m024;                     // +0x024
    int    m028;                     // +0x028
    int    m02C;                     // +0x02c
    int    m030;                     // +0x030
    int    m034;                     // +0x034  level count
    int    m038;                     // +0x038
    int    m03C;                     // +0x03c  base pointer for level stride
    int    m040;                     // +0x040
    int    m044[23];                 // +0x044 .. +0x09f
    int    m0A0;                     // +0x0a0  job count
    int*   m0A4;                     // +0x0a4  per-job descriptor array (0x24 bytes each)
    int    m0A8;                     // +0x0a8
    int    m0AC;                     // +0x0ac
    int    m0B0;                     // +0x0b0
    int    m0B4;                     // +0x0b4
    int    m0B8;                     // +0x0b8
    int    m0BC;                     // +0x0bc
    int    m0C0;                     // +0x0c0
    int    m0C4;                     // +0x0c4
    int    m0C8;                     // +0x0c8
    int    m0CC;                     // +0x0cc
    int    m0D0;                     // +0x0d0
    int    m0D4;                     // +0x0d4
    int    m0D8;                     // +0x0d8
    int    m0DC;                     // +0x0dc
    int    m0E0;                     // +0x0e0
    int    m0E4;                     // +0x0e4
    int    m0E8;                     // +0x0e8
    int    m0EC;                     // +0x0ec  level count in use
    cLevel* m0F0[4];                 // +0x0f0  per-level pointers (max 4)
    int    m100;                     // +0x100
    int    m104;                     // +0x104
    int    m108;                     // +0x108  running count
    void*  m10C[10];                 // +0x10c  filled level table (+0x10c..+0x133)
    int    m134;                     // +0x134
    int    m138;                     // +0x138
    int    m13C;                     // +0x13c
    int    m140;                     // +0x140
    cSlot* m144;                     // +0x144  slot block (vtbl-carrier)
    void*  m148;                     // +0x148
    int    m14C;                     // +0x14c
    int    m150;                     // +0x150
    void*  m154;                     // +0x154  fn-pointer table (slots at +8/+0xc)
    void*  m158;                     // +0x158
    void*  m15C;                     // +0x15c
    void*  m160;                     // +0x160
    void*  m164;                     // +0x164  fn-pointer table (slot at +8)

    // __thiscall vtable members of the export object
    void FUN_008544e0();
    void FUN_008548a0();
    void FUN_00854990();
};
int __cdecl jdiv_round_up(int a, int b);           // lib_jpeg::jdiv_round_up @ 0x866850
void FUN_00854b60(cTerrainExport* p);
void FUN_00854d10(cTerrainExport* p);
void FUN_00854d40(cTerrainExport* p);
void FUN_00854e70(cTerrainExport* p);
__declspec(noinline) void* FUN_00854ed0(cTerrainExport* p);
__declspec(noinline) void* FUN_00854f00(cTerrainExport* p);
void FUN_00854f30(cTerrainExport* p, int a1, int* a2, int a3, int a4);
void FUN_00855150(cTerrainExport* p);
void FUN_008552d0(cTerrainExport* p);
struct BlobTab { int v[0x40]; };
struct BlobSrc {
    int  h0, h1, h2, h3;             // +0x00 header dwords
    unsigned char b;                 // +0x10 header byte
    unsigned char pad[3];
    BlobTab tab;                     // +0x14 table (0x100 bytes)
};
static __forceinline void FillBlob(cTerrainExport* p, int* slot, BlobSrc* src)
{
    if (*slot == 0)
        *slot = (int)FUN_00854f00(p);
    {
        int* buf = (int*)*slot;
        buf[0] = src->h0;
        buf[1] = src->h1;
        buf[2] = src->h2;
        buf[3] = src->h3;
        *(unsigned char*)(buf + 4) = src->b;
    }
    *(BlobTab*)((char*)*slot + 0x11) = src->tab;
    *(int*)((char*)*slot + 0x114) = 0;
}
extern BlobSrc g141d010;
extern BlobSrc g141d050;
extern BlobSrc g141d030;
extern BlobSrc g141d10c;
// ---- items of slice s008544e0 end

// ---- items of slice s008571b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
unsigned int __stdcall gwrite(void* context, void* buffer, unsigned int size);
// ---- items of slice s008571b0 end

// ---- items of slice s0085ad60 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Reader;
typedef int  (*OpenFn)(Reader*, void*);
typedef void (*WriteFn)(Reader*, void*, uint32_t*, uint32_t, uint32_t, uint32_t, uint32_t);
struct Ctx
{
    void    (*error)(Reader*);          // +0x00
    void    (*report)(Reader*, int32_t); // +0x04
    uint8_t   pad08[0x0c];
    int32_t   code;                     // +0x14
    int32_t   a18, a1c, a20, a24;       // +0x18
};
struct Stream
{
    uint8_t*  p;                        // +0x00
    int32_t   n;                        // +0x04
    uint8_t   pad08[4];
    int32_t (*refill)(Reader*);         // +0x0c
    void    (*skip)(Reader*, int32_t);  // +0x10
};
struct State                               // 0x50 bytes
{
    void*     step;                     // +0x00
    void*     work;                     // +0x04
    void*     buf[8];                   // +0x08
    uint8_t   pad28[8];
    int32_t   started;                  // +0x30
    uint32_t  pos;                      // +0x34
    void*     slot[2];                  // +0x38
    int32_t   index;                    // +0x40
    int32_t   phase;                    // +0x44
    uint32_t  limit;                    // +0x48
    int32_t   count;                    // +0x4c
};
struct Surf                                // 0x54-byte surface record
{
    uint32_t  id;                       // +0x00
    uint32_t  index;                    // +0x04
    uint32_t  x;                        // +0x08
    uint32_t  y;                        // +0x0c
    uint32_t  w;                        // +0x10
    uint32_t  h;                        // +0x14
    uint32_t  pad18[3];                 // +0x18
    int32_t   row;                      // +0x24
    uint32_t  span;                     // +0x28
    uint32_t  pad2c[2];                 // +0x2c
    uint32_t  level;                    // +0x34
};
struct Reader
{
    Ctx*      ctx;                      // +0x00
    struct Alloc* alloc;                // +0x04
    uint8_t   pad08[0x0c];
    Stream*   stream;                   // +0x14
    uint8_t   pad18[8];
    int32_t   count;                    // +0x20
    int32_t   counter;                  // +0x24
    uint8_t   pad28[0xac];
    uint8_t   pad_d4[4];                // +0xd4
    Surf*     surfs;                    // +0xd8
    uint8_t   padext[0x460];            // +0xdc
    int32_t   size;                     // +0x53c
    int32_t   limit;                    // +0x540
    uint8_t   pad544[0x5c];             // +0x544
    int32_t   stateCode;                // +0x5a0
    uint8_t   pad5a4[4];
    State*    state;                    // +0x5a8
    struct OpenIface* open;             // +0x5ac
    struct WriteIface* write;           // +0x5b0
    uint8_t   pad5b4[4];
    struct Header* header;              // +0x5b8
    uint8_t   pad5bc[8];
    struct PrePass* prepass;            // +0x5c4
};
struct Alloc
{
    void*   (*make)(Reader*, int32_t, uint32_t);              // +0x00
    void*   (*make1)(Reader*, int32_t, uint32_t);             // +0x04
    void*   (*alloc)(Reader*, int32_t, uint32_t, uint32_t);   // +0x08
};
struct OpenIface
{
    uint8_t   pad00[0x0c];
    int32_t (*open)(Reader*, void*);    // +0x0c
};
struct WriteIface
{
    uint8_t   pad00[4];
    WriteFn   write;                    // +0x04
};
struct PrePass
{
    uint8_t   pad00[8];
    int32_t   flag;                     // +0x08
};
struct Header
{
    uint8_t   pad00[0x50];
    int32_t   state;                    // +0x50
};
void FUN_0085aaa0(Reader* o);           // 0x0085aaa0
void FUN_0085acc0(Reader* o);           // 0x0085acc0
void FUN_0085abe0(Reader* o);           // 0x0085abe0
void FUN_0085a9f0();                    // 0x0085a9f0
// ---- items of slice s0085ad60 end

// ---- items of slice s0085cb00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void f_00865450(void *);
extern "C" void f_00866700(void *);
extern "C" void f_008594d0(void);
extern "C" void f_0085ee50(void *);
extern "C" void f_00859980(void *);
extern "C" void f_0085e5c0(void);
extern "C" void f_0085a390(void);
extern "C" void Fn_0085c960(void);
extern "C" void Fn_0085b760(void);
extern "C" void Fn_0085d480(void);
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            i32;
extern "C" i32  Fn_00866850(i32 a, i32 b);              // lib_jpeg::jdiv_round_up
extern "C" void Fn_00866880(void *in, i32 src_row, void *out, i32 dst_row,
                            i32 num_rows, u32 rowsize); // lib_jpeg::jcopy_sample_rows
extern "C" void f_011e073e(void *dst, i32 val, unsigned size);
extern "C" void f_0085e900(void *, i32);
extern "C" void f_00858f80(void *, i32);
extern "C" void f_0085afd0(void *, i32);
struct ErrMgr {
    void (*fn)(void *);
    char pad[0x10];
    i32  msg_code;
    i32  parm;
};
struct MemMgr {
    void *(*alloc_small)(void *cinfo, i32 pool_id, u32 size);
    void *(*alloc_large)(void *cinfo, i32 pool_id, u32 size);
};
struct Entropy {
    void (*fn00)(void *);
    void (*fn04)(void *, i32 *);
    void (*fn08)(void *);
    void (*fn0c)(void *);
    void (*fn10)(void *);
    void (*fn14)(void *);
    void (*fn18)(void *);
    void (*fn1c)(void *);
    void (*fn20)(void *);
    void (*fn24)(void *);
    void (*fn28)(void *);
    void (*fn2c)(void *);
    void (*fn30)(void *);
    void (*fn34)(void *);
    void (*fn38)(void *);
    void (*fn3c)(void *);
    void (*fn40)(void *);
    void (*fn44)(void *);
    void (*fn48)(void *, i32 *);
    void (*fn4c)(void *);
    i32  f50;
    i32  f54;
    i32  f58;
    i32  f5c;
};
struct Master {
    void (*fn00)(void *);
    void (*fn04)(void *);
    void (*fn08)(void *);
    void (*fn0c)(void *, i32, i32 *, void **);
    u8  *buf10;
    u8  *buf14;
    u8  *buf18;
    u8  *buf1c;
    u8  *buf20;
    i32  f24;
    u32  f28;
    i32  f2c;
};
struct ScanInfo {
    i32 f00, f04, f08, f0c, f10, f14, f18;
};
struct Comp {
    u8  pad0[0x08];
    i32 f08;
    i32 f0c;
    u8  pad10[0x08];
    i32 f18;
    u8  pad1c[0x08];
    i32 f24;
    i32 f28;
    i32 f2c;
    u8  pad30[0x24];
};
struct CInfo {
    ErrMgr  *err;   // +0x00
    MemMgr  *mem;   // +0x04
    void    *f08;   // +0x08
    i32      f0c;   // +0x0c
    i32      f10;   // +0x10
    i32      f14;   // +0x14
    i32      f18;   // +0x18
    i32      f1c;   // +0x1c
    i32      f20;   // +0x20
    i32      f24;   // +0x24
    i32      f28;   // +0x28
    i32      f2c;   // +0x2c
    i32      f30;   // +0x30
    i32      f34;   // +0x34
    i32      f38;   // +0x38
    i32      f3c;   // +0x3c
    i32      f40;   // +0x40
    i32      f44;   // +0x44
    i32      f48;   // +0x48
    i32      f4c;   // +0x4c
    i32      f50;   // +0x50
    i32      f54;   // +0x54
    i32      f58;   // +0x58
    i32      f5c;   // +0x5c
    i32      f60;   // +0x60
    i32      f64;   // +0x64
    i32      f68;   // +0x68
    i32      f6c;   // +0x6c
    i32      f70;   // +0x70
    i32      f74;   // +0x74
    i32      f78;   // +0x78
    i32      f7c;   // +0x7c
    i32      f80;   // +0x80
    i32      f84;   // +0x84
    i32      f88;   // +0x88
    i32      f8c;   // +0x8c
    i32      f90;   // +0x90
    char     pad94[0x44];  // 0x94..0xd8
    Comp    *comps;        // +0xd8
    i32      fdc;          // +0xdc
    i32      fe0;          // +0xe0
    char     pad114[0x114 - 0xe4];
    i32      f114;         // +0x114
    char     pad118[0x12c - 0x118];
    i32      f12c;         // +0x12c
    char     pad130[0x534 - 0x130];
    i32      f534;         // +0x534
    i32      f538;         // +0x538
    i32      f53c;         // +0x53c
    i32      f540;         // +0x540
    u8      *table_base;   // +0x544
    i32      f548;         // +0x548
    char     pad54c[0x5a0 - 0x54c];
    i32      f5a0;         // +0x5a0
    void    *f5a4;         // +0x5a4
    void    *f5a8;         // +0x5a8
    void    *f5ac;         // +0x5ac
    void    *f5b0;         // +0x5b0
    void    *f5b4;         // +0x5b4
    Entropy *ent;          // +0x5b8
    void    *f5bc;         // +0x5bc
    void    *f5c0;         // +0x5c0
    Master  *master;       // +0x5c4
    void    *f5c8;         // +0x5c8
    void    *f5cc;         // +0x5cc
};
#define VTFN(p, i) (*(void **)((u8 *)(p) + (i)))
#define C(p) ((CInfo *)(p))
void FUN_0085d830(void *);
extern "C" void Fn_0085c330(void *, i32, void *, u32);
extern "C" void Fn_0085c5b0(void *, i32 *);
extern "C" void Fn_0085b9e0(void *, i32 *);
// ---- items of slice s0085cb00 end

// ---- items of slice s0085d930 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int FUN_0085d8b0(void);                                   // 0x0085d8b0
extern "C" const int gHuffLimit_141d308[];    // 0x0141d308  per-length escape threshold
extern "C" const int gHuffOffset_141d348[];   // 0x0141d348  per-length escape base
extern "C" const int gOutMap_141e880[];       // 0x0141e880  output index per decoded position
extern "C" void FUN_008599f0(int param_1, int table, void* out);  // 0x008599f0
typedef unsigned int  uint;
typedef unsigned short wchar16;
void FUN_0085e2d0();
struct StreamDesc {                  // Ctx.mpDesc
    char  _pad00[0x04];
    void* mpfnDecode;                // +0x04  decoder entry installed per stream
    int  mBitBuf;                    // +0x08  pending bit accumulator
    int  mBitCount;                  // +0x0c  bits available in mBitBuf
    int  mField10;                   // +0x10  (handed to the bit-refill helper)
    int  mRepeat;                    // +0x14  remaining run-length repeats
    int  mAcc0;                      // +0x18  per-channel delta accumulator 0
    int  mAcc1;                      // +0x1c  per-channel delta accumulator 1
    int  mAcc2;                      // +0x20  per-channel delta accumulator 2
    int  mAcc3;                      // +0x24  per-channel delta accumulator 3
    int  mPending;                   // +0x28  remaining elements for this pass
    int** mppTables;                 // +0x2c  huffman decode table per stream
};
struct StreamState {                 // Ctx.mpStream
    char _pad00[0x08];
    int  mField08;                   // +0x08
    int  mpBuffer;                   // +0x0c  element buffer
    int  mCapacity;                  // +0x10  elements per buffer slot
    int  mBase;                      // +0x14  ring base offset
    int  mCount;                     // +0x18  elements currently buffered
};
struct StreamObject {                // entry of Ctx.mpStreamTab (+0x54c)
    char _pad00[0x04];
    int  mIndex;                     // +0x04  sample-table slot index
    char _pad08[0x14 - 0x08];
    int  mField14;                   // +0x14  decode mode (plain streams)
    int  mField18;                   // +0x18  decode mode (interlaced streams)
};
struct StreamInner {                 // object at Ctx.mpInner (+0x00)
    void* mpfnError;                 // +0x00  called as (int ctx)
    void* mpNotify;                  // +0x04  called as (int ctx, int code)
    char  _pad08[0x14 - 0x08];
    int   mErrorCode;                // +0x14
    int   mField18;                  // +0x18  error argument 0
    int   mField1c;                  // +0x1c  error argument 1
    int   mField20;                  // +0x20  error argument 2
    int   mField24;                  // +0x24  error argument 3
};
struct StreamCtx {
    StreamInner* mpInner;            // +0x00  error/report sub-object
    void*        mpVtbl;             // +0x04
    char         _pad08[0x14 - 0x08];
    int*         mpSrcPair;          // +0x14  { mSrcLo, mSrcHi }
    char         _pad18[0x20 - 0x18];
    int          mCapacity;          // +0x20
    char         _pad24[0x74 - 0x24];
    int          mField74;           // +0x74
    char         _pad78[0xa0 - 0x78];
    int*         mpSampleTable;      // +0xa0  0x100-byte sample/predictor slots
    void**       mpTablesB4;         // +0xb4  per-mode tables (plain streams)
    void**       mpTablesC4;         // +0xc4  per-mode tables (interlaced streams)
    char         _padc8[0x114 - 0xc8];
    int          mField114;          // +0x114
    char         _pad118[0x548 - 0x118];
    int          mChannelCount;      // +0x548  number of streams
    void**       mpStreamTab;        // +0x54c  per-channel stream objects
    char         _pad550[0x564 - 0x550];
    int          mElemCount;         // +0x564
    int*         mChannelIds;        // +0x568  per-output channel index
    char         _pad56c[0x590 - 0x56c];
    int          mField590;          // +0x590
    int          mField594;          // +0x594
    int          mField598;          // +0x598
    int          mBitIndex;          // +0x59c
    int          mSrcState;          // +0x5a0
    char         _pad5a4[0x5b0 - 0x5a4];
    StreamState* mpStream;           // +0x5b0
    char         _pad5b4[0x5bc - 0x5b4];
    StreamDesc*  mpDesc;             // +0x5bc
    void*        mpDecoder;          // +0x5c4
    void*        mpSink;             // +0x5cc
};
struct BitReader {                   // scratch block passed to FUN_00859bb0
    int        mSrc0;                // +0x00
    int        mSrc1;                // +0x04
    int        mSrc2;                // +0x08
    int        mBitBuf;              // +0x0c  out
    int        mBitCount;            // +0x10  out
    StreamCtx* mpCtx;                // +0x14  back-reference
    void*      mpField18;            // +0x18  &StreamDesc::mField10
};
extern "C" int FUN_00859bb0(BitReader* st, int buf, int count, int mode);  // 0x00859bb0
extern "C" int FUN_00859cc0(BitReader* st, int buf, int count, int table, unsigned sym);  // 0x00859cc0
// ---- items of slice s0085d930 end

// @ 0x008502a0
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

// @ 0x008503f0
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

// @ 0x00850510
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

// @ 0x008505f0
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

// @ 0x00852930
void htest_one_block(JCOEF* block, int last_dc_val, long* dc_counts, long* ac_counts)
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

// @ 0x00852aa0
void jpeg_gen_optimal_table(j_compress_ptr cinfo, struct JHUFF_TBL* htbl, long* freq)
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

// @ 0x008530b0
void process_data_simple_main(j_compress_ptr cinfo, UINT8** input_buf, JDIMENSION* in_row_ctr, JDIMENSION in_rows_avail)
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

// @ 0x00853240
void emit_marker(j_compress_ptr cinfo, int mark)
{
    emit_byte(cinfo, 0xFF);
    emit_byte(cinfo, mark);
}

// @ 0x008532b0
void emit_2bytes(j_compress_ptr cinfo, int value)
{
    emit_byte(cinfo, (value >> 8) & 0xFF);
    emit_byte(cinfo, value & 0xFF);
}

// @ 0x00853320
void emit_4bytes(j_compress_ptr cinfo, int value)
{
    emit_byte(cinfo, (value >> 24) & 0xFF);
    emit_byte(cinfo, (value >> 16) & 0xFF);
    emit_byte(cinfo, (value >> 8) & 0xFF);
    emit_byte(cinfo, value & 0xFF);
}

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

// @ 0x008544e0
void cTerrainExport::FUN_008544e0()
{
    int i;
    int local_a30[10];
    unsigned int auStack_a08[16 * 0x40];

    if (m0A0 < 1) {
        cJob* j = mJob;
        j->m14 = 0x11;
        j->m18 = 0;
        j->Error();
    }

    int* pj = m0A4;
    if (pj[5] == 0 && pj[6] == 0x3f) {
        m0DC = 0;
        if (m034 >= 1) {
            int n = m034;
            for (i = 0; i < n; i++)
                local_a30[i] = 0;
        }
    } else {
        m0DC = 1;
        if (m034 >= 1) {
            int n = m034 & 0xffffff;
            for (i = 0; i < (n << 6); i++)
                auStack_a08[i] = 0xffffffff;
        }
    }

    int job = 1;
    if (m0A0 < 1)
        goto done;
    do {
        int cnt = pj[0];
        if (cnt < 1 || cnt > 4) {
            cJob* j = mJob;
            j->m14 = 0x18;
            j->m18 = cnt;
            j->m1C = 4;
            j->Error();
        }
        for (i = 0; i < cnt; i++) {
            int lv = pj[i + 1];
            if (lv < 0 || m034 <= lv) {
                cJob* j = mJob;
                j->m14 = 0x11;
                j->m18 = job;
                j->Error();
            }
            if (i > 0 && lv <= pj[i]) {
                cJob* j = mJob;
                j->m14 = 0x11;
                j->m18 = job;
                j->Error();
            }
        }

        unsigned int u5 = (unsigned int)pj[5];
        int u6 = pj[6];
        unsigned int u2 = (unsigned int)pj[7];
        unsigned int u3 = (unsigned int)pj[8];

        if (m0DC == 0) {
            if (u5 != 0 || u6 != 0x3f || u2 != 0 || u3 != 0) {
                cJob* j = mJob;
                j->m14 = 0xf;
                j->m18 = job;
                j->Error();
            }
            int c2 = cnt;
            int* pp = pj;
            if (c2 > 0) {
                do {
                    int lv = pp[1];
                    if (local_a30[lv] != 0) {
                        cJob* j = mJob;
                        j->m14 = 0x11;
                        j->m18 = job;
                        j->Error();
                    }
                    c2--;
                    local_a30[lv] = 1;
                    pp++;
                } while (c2 != 0);
            }
        } else {
            if (u5 > 0x3f || (int)u6 < (int)u5 ||
                u6 > 0x3f || u2 > 0xd || (int)u3 < 0 || u3 > 0xd) {
                cJob* j = mJob;
                j->m14 = 0xf;
                j->m18 = job;
                j->Error();
            }
            if (u5 == 0) {
                if (u6 != 0) {
                    cJob* j = mJob;
                    j->m14 = 0xf;
                    j->m18 = job;
                    j->Error();
                }
            } else if (cnt != 1) {
                cJob* j = mJob;
                j->m14 = 0xf;
                j->m18 = job;
                j->Error();
            }
            int c3 = cnt;
            int* pp = pj;
            if (c3 > 0) {
                do {
                    pp++;
                    unsigned int* row = auStack_a08 + (*pp) * 0x40;
                    unsigned int k = u5;
                    if (u5 != 0 && (int)*row < 0) {
                        cJob* j = mJob;
                        j->m14 = 0xf;
                        j->m18 = job;
                        j->Error();
                    }
                    for (; (int)k <= u6; k++) {
                        if ((int)row[k] < 0) {
                            if (u2 != 0) {
                                cJob* j = mJob;
                                j->m14 = 0xf;
                                j->m18 = job;
                                j->Error();
                            }
                        } else if (u2 != row[k] || u3 != u2 - 1) {
                            cJob* j = mJob;
                            j->m14 = 0xf;
                            j->m18 = job;
                            j->Error();
                        }
                        row[k] = u3;
                    }
                    c3--;
                } while (c3 != 0);
            }
        }

        job++;
        pj += 9;
    } while (job <= m0A0);

done:
    i = 0;
    if (m0DC == 0) {
        if (m034 > 0) {
            do {
                if (local_a30[i] == 0) {
                    cJob* j = mJob;
                    j->m14 = 0x2c;
                    j->Error();
                }
                i++;
            } while (i < m034);
        }
    } else if (m034 > 0) {
        unsigned int* row = auStack_a08;
        do {
            if ((int)*row < 0) {
                cJob* j = mJob;
                j->m14 = 0x2c;
                j->Error();
            }
            i++;
            row += 0x40;
        } while (i < m034);
    }
}

// @ 0x008548a0
void cTerrainExport::FUN_008548a0()
{
    if (m0A4 != 0) {
        int* q = (int*)((char*)m0A4 + ((cSlot*)m144)->m20 * 0x24);
        m0EC = q[0];
        if (q[0] > 0) {
            cLevel** dst = m0F0;
            int* src = q + 1;
            int i = 0;
            do {
                *dst = (cLevel*)(*src * 0x54 + m03C);
                src++;
                i++;
                dst++;
            } while (i < q[0]);
        }
        m134 = q[5];
        m138 = q[6];
        m13C = q[7];
        m140 = q[8];
        return;
    }
    if (m034 > 4) {
        cJob* j = mJob;
        j->m14 = 0x18;
        j->m18 = m034;
        j->m1C = 4;
        j->Error();
    }
    int n = m034;
    m0EC = n;
    if (n > 0) {
        cLevel** dst = m0F0;
        int off = 0;
        int i = 0;
        do {
            *dst = (cLevel*)(m03C + off);
            off += 0x54;
            i++;
            dst++;
        } while (i < n);
    }
    m134 = 0;
    m138 = 0x3f;
    m13C = 0;
    m140 = 0;
}

// @ 0x00854990
void cTerrainExport::FUN_00854990()
{
    int e = m0EC;
    if (e == 1) {
        cLevel* lv = m0F0[0];
        m100 = lv->m1C;
        m104 = lv->m20;
        unsigned int a = (unsigned int)lv->m0C;
        unsigned int b = (unsigned int)lv->m20;
        unsigned int quo = b / a;
        unsigned int rem = b % a;
        lv->m34 = 1;
        lv->m38 = 1;
        lv->m3C = 1;
        lv->m40 = 8;
        lv->m44 = 1;
        if (rem == 0)
            rem = a;
        lv->m48 = (int)rem;
        m108 = 1;
        m10C[0] = 0;
        (void)quo;
    } else {
        if (e < 1 || e > 4) {
            cJob* j = mJob;
            j->m14 = 0x18;
            j->m18 = e;
            j->m1C = 4;
            j->Error();
        }
        m100 = jdiv_round_up(m018, m0E0 * 8);
        m104 = jdiv_round_up(m01C, m0E4 * 8);
        m108 = 0;
        if (e > 0) {
            int idx = 0;
            for (int i = 0; i < e; i++) {
                cLevel* lv = m0F0[i];
                unsigned int w = (unsigned int)lv->m08;
                lv->m40 = (int)(w * 8);
                unsigned int rem = (unsigned int)lv->m1C % w;
                unsigned int c = (unsigned int)lv->m0C;
                int prod = (int)(c * w);
                lv->m34 = (int)w;
                lv->m38 = (int)c;
                lv->m3C = prod;
                if (rem == 0)
                    rem = w;
                lv->m44 = (int)rem;
                unsigned int rem2 = (unsigned int)lv->m20 % c;
                if (rem2 == 0)
                    rem2 = c;
                lv->m48 = (int)rem2;
                if (m108 + prod > 10) {
                    cJob* j = mJob;
                    j->m14 = 0xb;
                    j->Error();
                }
                for (int k = prod; k > 0; k--) {
                    m10C[m108] = (void*)idx;
                    m108 = m108 + 1;
                }
                idx++;
            }
        }
    }
    if (m0C4 > 0) {
        int v = m100 * m0C4;
        if (v >= 0xffff)
            v = 0xffff;
        m0C0 = v;
    }
}

// @ 0x00854b60
void FUN_00854b60(cTerrainExport* p)
{
    cSlot* s = (cSlot*)p->m144;
    int st = s->m14;

    if (st == 0) {
        p->FUN_008548a0();
        p->FUN_00854990();
        if (p->m0A8 == 0) {
            ((void(__cdecl*)(cTerrainExport*))p->m158)(p);
            ((void(__cdecl*)(cTerrainExport*))p->m15C)(p);
            ((void(__cdecl*)(cTerrainExport*, int))p->m14C)(p, 0);
        }
        ((void(__cdecl*)(cTerrainExport*))p->m160)(p);
        ((void(__cdecl*)(cTerrainExport*, int))p->m164)(p, p->m0B0);
        ((void(__cdecl*)(cTerrainExport*, int))p->m150)(p, s->m1C < 2 ? 3 : 2);
        ((void(__cdecl*)(cTerrainExport*, int))p->m148)(p, 0);
        s->m0C = (p->m0B0 == 0);
    } else if (st == 1) {
        p->FUN_008548a0();
        p->FUN_00854990();
        if (p->m134 != 0 || p->m13C == 0 || p->m0AC != 0) {
            ((void(__cdecl*)(cTerrainExport*, int))p->m164)(p, 1);
            ((void(__cdecl*)(cTerrainExport*, int))p->m150)(p, 2);
            s->m0C = 0;
            goto tail;
        }
        s->m18 = s->m18 + 1;
        s->m14 = 2;
    } else if (st != 2) {
        cJob* j = p->mJob;
        j->m14 = 0x2f;
        j->Error();
        goto tail;
    }

    if (p->m0B0 == 0) {
        p->FUN_008548a0();
        p->FUN_00854990();
    }
    ((void(__cdecl*)(cTerrainExport*, int))p->m164)(p, 0);
    ((void(__cdecl*)(cTerrainExport*, int))p->m150)(p, 2);
    if (s->m20 == 0)
        ((void(__cdecl*)(cTerrainExport*))((void**)p->m154)[2])(p);
    ((void(__cdecl*)(cTerrainExport*))((void**)p->m154)[3])(p);
    s->m0C = 0;

tail:
    s->m10 = (s->m18 == s->m1C - 1);
    if (p->m008 != 0) {
        *(int*)((char*)p->m008 + 0xc) = s->m18;
        *(int*)((char*)p->m008 + 0x10) = s->m1C;
    }
}

// @ 0x00854d10
void FUN_00854d10(cTerrainExport* p)
{
    ((cSlot*)p->m144)->m0C = 0;
    void* a = p->m154;
    void* f2 = *(void**)((char*)a + 8);
    ((void(__cdecl*)(cTerrainExport*))f2)(p);
    void* b = p->m154;
    void* f3 = *(void**)((char*)b + 0xc);
    ((void(__cdecl*)(cTerrainExport*))f3)(p);
}

// @ 0x00854d40
void FUN_00854d40(cTerrainExport* p)
{
    cSlot* s = (cSlot*)p->m144;
    void* base = p->m164;
    void* f = *(void**)((char*)base + 8);
    ((void(__cdecl*)(cTerrainExport*))f)(p);

    switch (s->m14) {
    case 0:
        s->m14 = 2;
        if (p->m0B0 != 0)
            goto tail18;
        goto tail20;
    case 1:
        s->m18 = s->m18 + 1;
        s->m14 = 2;
        return;
    case 2:
        if (p->m0B0 == 0)
            goto tail20;
        s->m20 = s->m20 + 1;
        s->m18 = s->m18 + 1;
        s->m14 = 1;
        return;
    default:
        goto tail18;
    }
tail20:
    s->m20 = s->m20 + 1;
tail18:
    s->m18 = s->m18 + 1;
}

// @ 0x00854e70
void FUN_00854e70(cTerrainExport* p)
{
    void** vt = (void**)p->mAllocVtbl;
    void* fn = vt[9];
    ((void(__cdecl*)(cTerrainExport*, int))fn)(p, 1);
    p->m010 = (p->m00C != 0) ? 200 : 100;
}

// @ 0x00854f00
__declspec(noinline) void* FUN_00854f00(cTerrainExport* p)
{
    void** vt = (void**)p->mAllocVtbl;
    void* fn = vt[0];
    void* r = ((void*(__cdecl*)(cTerrainExport*, int, int))fn)(p, 0, 0x118);
    *(int*)((char*)r + 0x114) = 0;
    return r;
}

// @ 0x00854f30
void FUN_00854f30(cTerrainExport* p, int a1, int* a2, int a3, int a4)
{
    if (p->m010 != 100) {
        cJob* j = p->mJob;
        j->m14 = 0x12;
        j->m18 = p->m010;
        j->Error();
    }
    int* slots = &p->m040;
    if (slots[a1] == 0)
        slots[a1] = (int)FUN_00854ed0(p);

    unsigned short* out = (unsigned short*)slots[a1];
    int* src = a2;
    int off = 0;
    do {
        int v;
        v = (src[0] * a3 + 0x32) / 100;
        if (v < 1) v = 1;
        else if (v > 0x7fff) v = 0x7fff;
        if (a4 != 0 && v > 0xff) v = 0xff;
        out[off + 0] = (unsigned short)v;

        v = (src[1] * a3 + 0x32) / 100;
        if (v < 1) v = 1;
        else if (v > 0x7fff) v = 0x7fff;
        if (a4 != 0 && v > 0xff) v = 0xff;
        out[off + 1] = (unsigned short)v;

        v = (src[2] * a3 + 0x32) / 100;
        if (v < 1) v = 1;
        else if (v > 0x7fff) v = 0x7fff;
        if (a4 != 0 && v > 0xff) v = 0xff;
        out[off + 2] = (unsigned short)v;

        v = (src[3] * a3 + 0x32) / 100;
        if (v < 1) v = 1;
        else if (v > 0x7fff) v = 0x7fff;
        if (a4 != 0 && v > 0xff) v = 0xff;
        out[off + 3] = (unsigned short)v;

        off += 4;
        src += 4;
    } while (off < 0x40);

    slots[a1] = slots[a1];
    ((int*)slots[a1])[0x80 / 4] = 0;
}

// @ 0x00855150
void FUN_00855150(cTerrainExport* p)
{
    FillBlob(p, &p->m040 + 4, &g141d010);
    FillBlob(p, &p->m040 + 8, &g141d050);
    FillBlob(p, &p->m040 + 5, &g141d030);
    FillBlob(p, &p->m040 + 9, &g141d10c);
}

// @ 0x008552d0
void FUN_008552d0(cTerrainExport* p)
{
    FillBlob(p, &p->m0B0 + 1, &g141d010);
    FillBlob(p, &p->m0B0 + 5, &g141d050);
    FillBlob(p, &p->m0B0 + 2, &g141d030);
    FillBlob(p, &p->m0B0 + 6, &g141d10c);
}

// @ 0x00857820
void __cdecl FUN_00857820(int* param_1, unsigned param_2, int param_3)
{
    if (param_2 == 0xfe) {
        *(int*)(param_1[0x16e] + 0xc) = param_3;
        return;
    }
    if (param_2 - 0xe0U <= 0xf) {
        *(int*)(param_1[0x16e] - 0x370 + param_2 * 4) = param_3;
        return;
    }
    *(int*)(*param_1 + 0x14) = 0x43;
    *(int*)(*param_1 + 0x18) = param_2;
    (*(void(__cdecl**)(int*))*param_1)(param_1);
}

// @ 0x00857f20
int __cdecl FUN_00857f20(int* param_1)
{
    int* puVar1 = (int*)param_1[5];
    int iVar2 = gwrite((void*)puVar1[5], (void*)puVar1[6], 0x1000);
    if (iVar2 != 0x1000) {
        *(int*)(*param_1 + 0x14) = 0x24;
        (*(void(__cdecl**)(int*))*param_1)(param_1);
    }
    *puVar1 = puVar1[6];
    puVar1[1] = 0x1000;
    return 1;
}

// @ 0x00857f70
void __cdecl FUN_00857f70(int* param_1)
{
    int iVar1 = param_1[5];
    int iVar2 = 0x1000 - *(int*)(iVar1 + 4);
    if (iVar2 != 0) {
        int iVar3 = gwrite((void*)*(int*)(iVar1 + 0x14), (void*)*(int*)(iVar1 + 0x18), iVar2);
        if (iVar3 != iVar2) {
            *(int*)(*param_1 + 0x14) = 0x24;
            (*(void(__cdecl**)(int*))*param_1)(param_1);
        }
    }
}

// @ 0x00857ff0
void __cdecl FUN_00857ff0(int param_1)
{
    *(int*)(*(int*)(param_1 + 0x14) + 0x24) = 1;
}

// @ 0x00858130
void __cdecl FUN_00858130(int param_1)
{
    int iVar1 = *(int*)(param_1 + 0x5ac);
    *(int*)(param_1 + 0x94) = 0;
    if (1 < *(int*)(param_1 + 0x548)) {
        *(int*)(iVar1 + 0x1c) = 1;
        *(int*)(iVar1 + 0x14) = 0;
        *(int*)(iVar1 + 0x18) = 0;
        return;
    }
    int iVar2 = *(int*)(param_1 + 0x540) - 1;
    if (iVar2 != 0) {
        *(int*)(iVar1 + 0x1c) = *(int*)(*(int*)(param_1 + 0x54c) + 0xc);
        *(int*)(iVar1 + 0x14) = 0;
        *(int*)(iVar1 + 0x18) = 0;
        return;
    }
    *(int*)(iVar1 + 0x1c) = *(int*)(*(int*)(param_1 + 0x54c) + 0x48);
    *(int*)(iVar1 + 0x14) = 0;
    *(int*)(iVar1 + 0x18) = 0;
}

// @ 0x0085ad60
void FUN_0085ad60(Reader* o, uint32_t a2, uint32_t a3, uint32_t a4)
{
    State* s = o->state;
    if (s->started == 0)
    {
        if (o->open->open(o, (uint8_t*)s + 8) == 0)
            return;
        s->started = 1;
    }
    uint32_t n = (uint32_t)o->size;
    o->write->write(o, (uint8_t*)s + 8, &s->pos, n, a2, (uint32_t)a3, a4);
    if (s->pos >= n)
    {
        s->started = 0;
        s->pos     = 0;
    }
}

// @ 0x0085ade0
void FUN_0085ade0(Reader* o, uint32_t a2, uint32_t* a3, uint32_t a4)
{
    State* s = o->state;
    if (s->started == 0)
    {
        OpenFn open = o->open->open;
        if (open(o, s->slot[s->index]) == 0)
            return;
        ++s->count;
        s->started = 1;
    }
    switch (s->phase)
    {
    case 0:
        break;
    case 1:
        goto send;
    case 2:
    {
        o->write->write(o, s->slot[s->index], &s->pos, s->limit, a2, (uint32_t)a3, a4);
        if (s->pos < s->limit)
            return;
        s->phase = 0;
        if (*a3 >= a4)
            return;
        break;
    }
    default:
        return;
    }

    s->pos   = 0;
    s->limit = (uint32_t)(o->size - 1);
    if (s->count == o->limit)
        FUN_0085acc0(o);
    s->phase = 1;

send:
    o->write->write(o, s->slot[s->index], &s->pos, s->limit, a2, (uint32_t)a3, a4);
    if (s->pos < s->limit)
        return;
    if (s->count == 1)
        FUN_0085abe0(o);
    s->index   ^= 1;
    s->started = 0;
    s->pos     = (uint32_t)(o->size + 1);
    s->limit   = (uint32_t)(o->size + 2);
    s->phase   = 2;
}

// @ 0x0085af20
void FUN_0085af20(Reader* o, uint32_t a2, uint32_t a3, uint32_t a4)
{
    WriteFn w = o->write->write;
    w(o, 0, 0, 0, a2, (uint32_t)a3, a4);
}

// @ 0x0085af50
void FUN_0085af50(Reader* o, int32_t mode)
{
    State* s = o->state;
    switch (mode)
    {
    case 0:
        if (o->prepass->flag != 0)
        {
            s->work = (void*)FUN_0085ade0;
            FUN_0085aaa0(o);
            s->index   = 0;
            s->phase   = 0;
            s->count   = 0;
            s->pos     = 0;
            s->started = 0;
            return;
        }
        s->pos     = 0;
        s->started = 0;
        s->work    = (void*)FUN_0085ad60;
        return;
    case 2:
        s->work = (void*)FUN_0085af20;
        return;
    default:
        o->ctx->code = 4;
        o->ctx->error(o);
        return;
    }
}

// @ 0x0085afd0
void FUN_0085afd0(Reader* o, int32_t a2)
{
    State* s = (State*)o->alloc->make(o, 1, 0x50);
    o->state = s;
    s->step  = (void*)FUN_0085af50;
    if (a2 != 0)
    {
        o->ctx->code = 4;
        o->ctx->error(o);
    }
    int32_t extra;
    if (o->prepass->flag == 0)
        extra = o->size;
    else
    {
        if (o->size < 2)
        {
            o->ctx->code = 0x2e;
            o->ctx->error(o);
        }
        FUN_0085a9f0();
        extra = o->size + 2;
    }
    if (o->count > 0)
    {
        int32_t*  r = (int32_t*)((uint8_t*)o->surfs + 0x24);
        uint8_t** b = (uint8_t**)((uint8_t*)s + 8);
        for (int32_t i = 0; i < o->count; ++i)
        {
            *b = (uint8_t*)o->alloc->alloc(o, 1,
                                           (uint32_t)(r[-2] * r[0]),
                                           (uint32_t)((r[-6] * r[0]) / o->size * extra));
            ++b;
            r += 0x15;
        }
    }
}

// @ 0x0085b9e0
int32_t FUN_0085b9e0(Reader* o)
{
    Stream* st = o->stream;
    uint8_t* p = st->p;
    int32_t  n = st->n;

    if (n == 0)
    {
        if (st->refill(o) == 0)
            return 0;
        p = st->p;
        n = st->n;
    }
    uint8_t b1 = *p++;
    --n;
    if (n == 0)
    {
        if (st->refill(o) == 0)
            return 0;
        p = st->p;
        n = st->n;
    }
    uint8_t b2 = *p++;
    --n;
    int32_t len = (int32_t)((uint32_t)b1 << 8 | (uint32_t)b2) - 2;

    if (len < 0xc)
    {
        o->ctx->code = 0x4d;
        o->ctx->a18  = len;
        o->ctx->report(o, 1);
    }
    else
    {
        uint8_t sig[12];
        for (int32_t i = 0; i < 12; ++i)
        {
            if (n == 0)
            {
                if (st->refill(o) == 0)
                    return 0;
                p = st->p;
                n = st->n;
            }
            sig[i] = *p++;
            --n;
        }
        int32_t rest = len - 0xc;
        if (sig[0] == 'A' && sig[1] == 'd' && sig[2] == 'o' && sig[3] == 'b' && sig[4] == 'e')
        {
            Ctx* c = o->ctx;
            c->a18 = (int32_t)((uint32_t)sig[5] << 8 | (uint32_t)sig[6]);
            c->a1c = (int32_t)((uint32_t)sig[7] << 8 | (uint32_t)sig[8]);
            c->a20 = (int32_t)((uint32_t)sig[9] << 8 | (uint32_t)sig[10]);
            c->a24 = (int32_t)sig[11];
            c->code = 0x4b;
            c->report(o, 1);
            *(int32_t*)((uint8_t*)o + 0x124) = 1;
            *(uint8_t*)((uint8_t*)o + 0x128) = sig[11];
        }
        else
        {
            o->ctx->code = 0x4d;
            o->ctx->a18  = len;
            o->ctx->report(o, 1);
        }
        len = rest;
    }
    st->p = p;
    st->n = n;
    if (len > 0)
        st->skip(o, len);
    return 1;
}

// @ 0x0085cb00
void FUN_0085cb00(void *param_1)
{
    CInfo *c = C(param_1);
    i32 z = 0;
    *(i32 *)((u8 *)c + 0xd8) = z;
    *(i32 *)((u8 *)c + 0x90) = z;
    *(i32 *)((u8 *)c + 0x5a0) = z;
    Entropy *e1 = c->ent;
    e1->f50 = z;
    Entropy *e2 = c->ent;
    e2->f54 = z;
    Entropy *e3 = c->ent;
    e3->f5c = z;
}

// @ 0x0085cb40
void FUN_0085cb40(void *param_1)
{
    CInfo *c = C(param_1);
    Entropy *e = (Entropy *)c->mem->alloc_small(param_1, 0, 0x60);
    c->ent = e;
    e->fn00 = (void (*)(void *))&FUN_0085cb00;
    e->fn04 = (void (*)(void *, i32 *))&Fn_0085c5b0;
    e->fn08 = (void (*)(void *))&Fn_0085c960;
    e->fn0c = (void (*)(void *))&Fn_0085c330;
    for (i32 off = 0x10; off < 0x50; off += 4)
        *(void **)((u8 *)e + off) = (void *)&Fn_0085c330;
    e->fn10 = (void (*)(void *))&Fn_0085b760;
    e->fn48 = (void (*)(void *, i32 *))&Fn_0085b9e0;
    i32 z = 0;
    Entropy *e1 = c->ent;
    *(i32 *)((u8 *)c + 0xd8) = z;
    *(i32 *)((u8 *)c + 0x90) = z;
    *(i32 *)((u8 *)c + 0x5a0) = z;
    e1->f50 = z;
    Entropy *e2 = c->ent;
    e2->f54 = z;
    Entropy *e3 = c->ent;
    e3->f5c = z;
}

// @ 0x0085cbf0
i32 __fastcall FUN_0085cbf0(void *unused, void *param_2)
{
    (void)unused;
    CInfo *c = C(param_2);
    if (c->f4c != 0) return 0;
    if (c->f12c != 0) return 0;
    if (c->f24 != 3) return 0;
    if (c->f20 != 3) return 0;
    if (c->f28 != 2) return 0;
    if (c->f78 != 3) return 0;
    u8 *s = (u8 *)c->comps;
    if (*(i32 *)(s + 0x08) != 2) return 0;
    if (*(i32 *)(s + 0x5c) != 1) return 0;
    if (*(i32 *)(s + 0xb0) != 1) return 0;
    if (*(i32 *)(s + 0x0c) > 2) return 0;
    if (*(i32 *)(s + 0x60) != 1) return 0;
    if (*(i32 *)(s + 0xb4) != 1) return 0;
    if (*(i32 *)(s + 0x24) != c->f53c) return 0;
    if (*(i32 *)(s + 0x78) != c->f53c) return 0;
    if (*(i32 *)(s + 0xcc) != c->f53c) return 0;
    return 1;
}

// @ 0x0085cc70
void FUN_0085cc70(void *param_1)
{
    CInfo *c = C(param_1);
    if (c->f10 != 0xca) {
        c->err->msg_code = 0x12;
        c->err->parm = c->f10;
        c->err->fn(param_1);
    }
    i32 eax = c->f2c;
    u32 ecx = (u32)c->f30;
    i32 r2;
    if ((u32)(eax * 8) <= ecx) {
        c->f70 = Fn_00866850(c->f18, 8);
        r2 = Fn_00866850(c->f1c, 8);
        c->f53c = 1;
    } else if ((u32)(eax * 4) <= ecx) {
        c->f70 = Fn_00866850(c->f18, 4);
        r2 = Fn_00866850(c->f1c, 4);
        c->f53c = 2;
    } else if ((u32)(eax * 2) <= ecx) {
        c->f70 = Fn_00866850(c->f18, 2);
        r2 = Fn_00866850(c->f1c, 2);
        c->f53c = 4;
    } else {
        c->f70 = c->f18;
        r2 = c->f1c;
        c->f53c = 8;
    }
    c->f74 = r2;
    i32 ncomp = c->f20;
    if (ncomp > 0) {
        u8 *cc = (u8 *)c->comps + 0xc;
        for (i32 i = 0; i < ncomp; i++) {
            i32 a = c->f53c;
            i32 v = a;
            if (a < 8) {
                do {
                    if (c->f534 * a < *(i32 *)(cc - 4) * v * 2) break;
                    if (c->f538 * a < *(i32 *)(cc) * v * 2) break;
                    v *= 2;
                } while (v < 8);
            }
            *(i32 *)(cc + 0x18) = v;
            cc += 0x54;
        }
    }
    if (ncomp > 0) {
        u8 *cc = (u8 *)c->comps + 0x24;
        for (i32 i = 0; i < ncomp; i++) {
            *(i32 *)(cc + 4) = Fn_00866850(
                *(i32 *)(cc - 0x1c) * *(i32 *)(cc) * c->f18, c->f534 * 8);
            *(i32 *)(cc + 8) = Fn_00866850(
                *(i32 *)(cc - 0x18) * c->f1c * *(i32 *)(cc), c->f538 * 8);
            cc += 0x54;
        }
    }
    switch (c->f28) {
    case 1: c->f78 = 1; break;
    case 2:
    case 3: c->f78 = 3; break;
    case 4:
    case 5: c->f78 = 4; break;
    default: c->f78 = c->f20; break;
    }
    i32 v = (c->f54 == 0) ? c->f78 : 1;
    c->f7c = v;
    if (FUN_0085cbf0(param_1, c) == 0)
        c->f80 = 1;
    else
        c->f80 = c->f538;
}

// @ 0x0085cea0
void FUN_0085cea0(void *param_1)
{
    CInfo *c = C(param_1);
    u8 *d = (u8 *)c->mem->alloc_small(param_1, 1, 0x580);
    u8 *base = d + 0x100;
    c->table_base = base;
    f_011e073e(d, 0, 0x100);
    for (i32 i = 0; i <= 0xff; i++)
        base[i] = (u8)i;
    f_011e073e(base + 0x100, 0xff, 0x180);
    f_011e073e(base + 0x280, 0, 0x180);
    u8 *dst = base + 0x400;
    u8 *src = base;
    __movsd((unsigned long *)dst, (unsigned long *)src, 0x20);
}

// @ 0x0085cf30
void FUN_0085cf30(void *param_1)
{
    CInfo *c = C(param_1);
    ScanInfo *s = (ScanInfo *)c->f5a4;
    FUN_0085cc70(param_1);
    FUN_0085cea0(param_1);
    s->f0c = 0;
    s->f10 = FUN_0085cbf0(param_1, c);
    s->f14 = 0;
    s->f18 = 0;
    if (c->f54 == 0 || c->f40 == 0) {
        c->f64 = 0;
        c->f68 = 0;
        c->f6c = 0;
    }
    i32 one = 1;
    if (c->f54 == 0) goto Lcfdd;
    if (c->f44 != 0) {
        c->err->msg_code = 0x2e;
        c->err->fn(param_1);
    }
    if (c->f78 == 3) {
        if (c->f88 != 0) {
            c->f68 = one;
            goto Lcfaa;
        }
        if (c->f5c == 0) goto Lcfa7;
        c->f6c = one;
        goto Lcfaa;
    }
    c->f68 = 0;
    c->f6c = 0;
    c->f88 = 0;
Lcfa7:
    c->f64 = one;
Lcfaa:
    if (c->f64 != 0) {
        f_00865450(param_1);
        s->f14 = (i32)c->f5cc;
    }
    if (c->f6c != 0 || c->f68 != 0) {
        f_00866700(param_1);
        s->f18 = (i32)c->f5cc;
    }
Lcfdd:
    if (c->f44 == 0) {
        if (s->f10 == 0) {
            f_008594d0();
            f_0085ee50(param_1);
        } else {
            FUN_0085d830(param_1);
        }
        f_0085e900(param_1, c->f6c);
    }
    f_00859980(param_1);
    if (c->fe0 == 0) {
        if (c->fdc == 0)
            f_0085a390();
        else
            f_0085e5c0();
    } else {
        c->err->msg_code = 1;
        c->err->fn(param_1);
    }
    i32 t;
    if (*(i32 *)((u8 *)c->f5b4 + 0x10) == 0 && c->f40 == 0)
        t = 0;
    else
        t = one;
    f_00858f80(param_1, t);
    if (c->f44 == 0)
        f_0085afd0(param_1, 0);
    ((void (*)(void *))VTFN(c->f08, 0x18))(param_1);
    ((void (*)(void *))VTFN(c->f5b4, 8))(param_1);
    if (c->f08 != 0 && c->f40 == 0 &&
        *(i32 *)((u8 *)c->f5b4 + 0x10) != 0) {
        i32 n = c->f20;
        if (c->fdc != 0)
            n = n * 3 + 2;
        u8 *o = (u8 *)c->f08;
        *(i32 *)(o + 4) = 0;
        *(i32 *)(o + 8) = c->f540 * n;
        *(i32 *)(o + 0xc) = 0;
        *(i32 *)(o + 0x10) = (c->f6c != 0 ? 1 : 0) + 2;
        *(i32 *)((u8 *)s + 0xc) = *(i32 *)((u8 *)s + 0xc) + 1;
    }
}

// @ 0x0085d100
void FUN_0085d100(void *param_1)
{
    CInfo *c = C(param_1);
    ScanInfo *s = (ScanInfo *)c->f5a4;
    if (s->f08 == 0) {
        if (c->f54 != 0 && c->f88 == 0) {
            if (c->f5c != 0 && c->f6c != 0) {
                c->f5cc = (void *)s->f18;
                s->f08 = 1;
            } else if (c->f64 != 0) {
                c->f5cc = (void *)s->f14;
            } else {
                c->err->msg_code = 0x2d;
                c->err->fn(param_1);
            }
        }
        ((void (*)(void *))VTFN(c->f5c0, 0))(param_1);
        ((void (*)(void *))VTFN(c->f5ac, 8))(param_1);
        if (c->f44 == 0) {
            if (s->f10 == 0)
                ((void (*)(void *))VTFN(c->f5c8, 0))(param_1);
            ((void (*)(void *))VTFN(c->master, 0))(param_1);
            if (c->f54 != 0)
                ((void (*)(void *, i32))VTFN(c->f5cc, 0))(param_1, s->f08);
            i32 sel = -(s->f08 != 0) & 3;
            ((void (*)(void *, i32))VTFN(c->f5b0, 0))(param_1, sel);
            ((void (*)(void *, i32))VTFN(c->f5a8, 0))(param_1, 0);
        }
    } else {
        s->f08 = 0;
        ((void (*)(void *, i32))VTFN(c->f5cc, 0))(param_1, 0);
        ((void (*)(void *, i32))VTFN(c->f5b0, 0))(param_1, 2);
        ((void (*)(void *, i32))VTFN(c->f5a8, 0))(param_1, 2);
    }
    if (c->f08 != 0) {
        u8 *o = (u8 *)c->f08;
        *(i32 *)(o + 0xc) = s->f0c;
        *(u32 *)(o + 0x10) = (u32)((s->f08 != 0) + 1) + (u32)s->f0c;
        if (c->f40 != 0 && *(i32 *)((u8 *)c->f5b4 + 0x14) == 0)
            *(i32 *)(o + 0x10) += (c->f6c != 0 ? 1 : 0) + 1;
    }
}

// @ 0x0085d260
void FUN_0085d260(void *param_1)
{
    CInfo *c = C(param_1);
    ScanInfo *s = (ScanInfo *)c->f5a4;
    if (c->f54 != 0)
        ((void (*)(void *))VTFN(c->f5cc, 8))(param_1);
    s->f0c = s->f0c + 1;
}

// @ 0x0085d290
void FUN_0085d290(void *param_1)
{
    CInfo *c = C(param_1);
    ScanInfo *p = (ScanInfo *)c->mem->alloc_large(param_1, 1, 0x1c);
    c->f5a4 = p;
    p->f00 = (i32)(size_t)&FUN_0085d100;
    p->f04 = (i32)(size_t)&FUN_0085d260;
    p->f08 = 0;
    return FUN_0085cf30(param_1);
}

// @ 0x0085d2d0
void FUN_0085d2d0(void *param_1)
{
    CInfo *c = C(param_1);
    Master *m = c->master;
    m->buf10 = (u8 *)c->mem->alloc_small(param_1, 1, 0x400);
    m->buf14 = (u8 *)c->mem->alloc_small(param_1, 1, 0x400);
    m->buf18 = (u8 *)c->mem->alloc_small(param_1, 1, 0x400);
    m->buf1c = (u8 *)c->mem->alloc_small(param_1, 1, 0x400);
    i32 i3 = 0;
    i32 t_sp = 0x5b6900;
    i32 t_di = 0xff1daf00;
    i32 t_dx = 0xff4d0b80;
    i32 t_cx = 0x2c8d00;
    do {
        *(i32 *)(i3 + (i32)m->buf10) = t_dx >> 16;
        *(i32 *)(i3 + (i32)m->buf14) = t_di >> 16;
        *(i32 *)(i3 + (i32)m->buf18) = t_sp;
        *(i32 *)(i3 + (i32)m->buf1c) = t_cx;
        t_sp -= 0xb6d2;
        t_cx -= 0x581a;
        t_dx += 0x166e9;
        t_di += 0x1c5a2;
        i3 += 4;
    } while (t_cx >= (i32)0xffd4cb1a);
}

// @ 0x0085d3a0
void FUN_0085d3a0(void *param_1)
{
    CInfo *c = C(param_1);
    Master *m = c->master;
    m->f24 = 0;
    m->f2c = c->f74;
}

// @ 0x0085d3c0
void FUN_0085d3c0(void *param_1, i32 param_2, i32 *param_3, i32 param_4, i32 param_5, i32 *param_6, i32 param_7)
{
    (void)param_4;
    CInfo *c = C(param_1);
    Master *m = c->master;
    u32 n;
    if (m->f24 != 0) {
        Fn_00866880((void *)&m->buf20, 0,
                                    (void *)(param_5 + *param_6 * 4), 0, 1, m->f28);
        n = 1;
        m->f24 = 0;
    } else {
        n = 2;
        if ((u32)m->f2c < 2) n = (u32)m->f2c;
        i32 i2 = *param_6;
        if ((u32)(param_7 - i2) < n) n = (u32)(param_7 - i2);
        void *stk[2];
        stk[0] = *(void **)(param_5 + i2 * 4);
        if (n < 2) {
            stk[1] = (void *)&m->buf20;
            m->f24 = 1;
        } else {
            stk[1] = *(void **)(param_5 + 4 + i2 * 4);
        }
        m->fn0c(param_1, param_2, param_3, stk);
    }
    *param_6 += n;
    m->f2c -= n;
    if (m->f24 == 0)
        (*param_3)++;
}

// @ 0x0085d4c0
void FUN_0085d4c0(void *param_1, i32 *param_2, i32 param_3, void **param_4)
{
    CInfo *c = C(param_1);
    Master *m = c->master;
    i32 t10 = (i32)m->buf10;
    i32 t14 = (i32)m->buf14;
    i32 t18 = (i32)m->buf18;
    i32 t1c = (i32)m->buf1c;
    u8 *p17 = *(u8 **)(param_2[0] + param_3 * 4);
    u8 *p15 = *(u8 **)(param_2[1] + param_3 * 4);
    u8 *p12 = *(u8 **)(param_2[2] + param_3 * 4);
    u8 *out = (u8 *)*param_4;
    u32 n = (u32)c->f70 >> 1;
    for (; n != 0; n--) {
        u8 b1 = *p12;
        u8 b2 = *p15;
        p15++;
        p12++;
        i32 v5 = *(i32 *)(t10 + b1 * 4);
        i32 v3 = *(i32 *)(t1c + b2 * 4);
        i32 v7 = *(i32 *)(t18 + b1 * 4);
        u32 u = *p17;
        i32 v6 = *(i32 *)(t14 + b2 * 4);
        out[0] = *(u8 *)(v5 + t1c * 0 + u + (i32)c->table_base);
        (void)v5;
        out[0] = *(u8 *)(v5 + u + (i32)c->table_base);
        v3 = (v3 + v7) >> 16;
        out[1] = *(u8 *)(v3 + u + (i32)c->table_base);
        out[2] = *(u8 *)(u + v6 + (i32)c->table_base);
        u = p17[1];
        out[3] = *(u8 *)(v5 + u + (i32)c->table_base);
        out[4] = *(u8 *)(v3 + u + (i32)c->table_base);
        out[5] = *(u8 *)(u + v6 + (i32)c->table_base);
        p17 += 2;
        out += 6;
    }
    if (*(u8 *)((u8 *)c + 0x70) & 1) {
        i32 v3 = *(i32 *)(t1c + *p15 * 4);
        i32 v7 = *(i32 *)(t18 + *p12 * 4);
        u32 u = *p17;
        i32 v6 = *(i32 *)(t14 + *p15 * 4);
        out[0] = *(u8 *)(*(i32 *)(t10 + *p12 * 4) + u + (i32)c->table_base);
        out[1] = *(u8 *)(u + ((v3 + v7) >> 16) + (i32)c->table_base);
        out[2] = *(u8 *)(u + v6 + (i32)c->table_base);
    }
}

// @ 0x0085d610
void FUN_0085d610(void *param_1, i32 *param_2, i32 param_3, void **param_4)
{
    CInfo *c = C(param_1);
    Master *m = c->master;
    i32 t10 = (i32)m->buf10;
    i32 t14 = (i32)m->buf14;
    i32 t18 = (i32)m->buf18;
    i32 t1c = (i32)m->buf1c;
    u8 **row0 = (u8 **)(param_2[0] + param_3 * 8);
    u8 *p7 = row0[0];
    u8 *p8 = row0[1];
    u8 *p14 = *(u8 **)(param_2[1] + param_3 * 4);
    u8 *p13 = (u8 *)*param_4;
    u8 *p17 = (u8 *)param_4[1];
    u8 *p12 = *(u8 **)(param_2[2] + param_3 * 4);
    u32 n = (u32)c->f70 >> 1;
    for (; n != 0; n--) {
        u8 b2 = *p14;
        p14++;
        i32 v9 = *(i32 *)(t10 + *p12 * 4);
        i32 v18 = *(i32 *)(t1c + b2 * 4);
        i32 v10 = *(i32 *)(t18 + *p12 * 4);
        i32 v11 = *(i32 *)(t14 + b2 * 4);
        u32 u = *p7;
        p13[0] = *(u8 *)(u + v9 + (i32)c->table_base);
        v18 = (v18 + v10) >> 16;
        p13[1] = *(u8 *)(u + v18 + (i32)c->table_base);
        p13[2] = *(u8 *)(u + v11 + (i32)c->table_base);
        u = p7[1];
        p13[3] = *(u8 *)(u + v9 + (i32)c->table_base);
        p13[4] = *(u8 *)(u + v18 + (i32)c->table_base);
        p13[5] = *(u8 *)(u + v11 + (i32)c->table_base);
        u = *p8;
        p17[0] = *(u8 *)(u + v9 + (i32)c->table_base);
        p17[1] = *(u8 *)(u + v18 + (i32)c->table_base);
        p17[2] = *(u8 *)(u + v11 + (i32)c->table_base);
        u = p8[1];
        p7 += 2;
        p8 += 2;
        p17[3] = *(u8 *)(u + v9 + (i32)c->table_base);
        p17[4] = *(u8 *)(u + v18 + (i32)c->table_base);
        p13 += 6;
        p17[5] = *(u8 *)(u + v11 + (i32)c->table_base);
        p17 += 6;
        p12++;
    }
    if (*(u8 *)((u8 *)c + 0x70) & 1) {
        i32 v3 = *(i32 *)(t10 + *p12 * 4);
        i32 v19 = *(i32 *)(t1c + *p14 * 4);
        i32 v6 = *(i32 *)(t18 + *p12 * 4);
        i32 v5 = *(i32 *)(t14 + *p14 * 4);
        u32 u = *p7;
        p13[0] = *(u8 *)(v3 + u + (i32)c->table_base);
        v19 = (v19 + v6) >> 16;
        p13[1] = *(u8 *)(v19 + u + (i32)c->table_base);
        p13[2] = *(u8 *)(u + v5 + (i32)c->table_base);
        u = *p8;
        p17[0] = *(u8 *)(v3 + u + (i32)c->table_base);
        p17[1] = *(u8 *)(v19 + u + (i32)c->table_base);
        p17[2] = *(u8 *)(u + v5 + (i32)c->table_base);
    }
}

// @ 0x0085d830
void FUN_0085d830(void *param_1)
{
    CInfo *c = C(param_1);
    Master *m = (Master *)c->mem->alloc_small(param_1, 1, 0x30);
    c->master = m;
    m->fn00 = (void (*)(void *))&FUN_0085d3a0;
    m->fn08 = 0;
    i32 n = c->f78 * c->f70;
    m->f28 = (u32)n;
    if (c->f538 == 2) {
        m->fn04 = (void (*)(void *))&FUN_0085d3c0;
        m->fn0c = (void (*)(void *, i32, i32 *, void **))&FUN_0085d610;
        m->buf20 = (u8 *)c->mem->alloc_large(param_1, 1, (u32)n);
        return FUN_0085d2d0(param_1);
    }
    m->buf20 = 0;
    m->fn04 = (void (*)(void *))&Fn_0085d480;
    m->fn0c = (void (*)(void *, i32, i32 *, void **))&FUN_0085d4c0;
    return FUN_0085d2d0(param_1);
}

// @ 0x0085d8b0
i32 FUN_0085d8b0(void *param_1)
{
    CInfo *c = C(param_1);
    u8 *v = (u8 *)c->f5bc;
    i32 *cnt = (i32 *)((u8 *)c->ent + 0x5c);
    i32 t = *(i32 *)(v + 0xc);
    *cnt += (t + ((t >> 31) & 7)) >> 3;
    *(i32 *)(v + 0xc) = 0;
    if (((i32 (*)(void *))VTFN(c->ent, 8))(param_1) == 0)
        return 0;
    for (i32 i = 0; i < c->f548; i++)
        *(i32 *)(v + 0x18 + i * 4) = 0;
    *(i32 *)(v + 0x14) = 0;
    *(i32 *)(v + 0x28) = c->f114;
    *(i32 *)(v + 0x10) = 0;
    return 1;
}

// @ 0x0085d930
int __cdecl FUN_0085d930(int param_1, int param_2)
{
    StreamCtx*  ctx  = (StreamCtx*)param_1;
    StreamDesc* desc = ctx->mpDesc;

    const int shift = ctx->mBitIndex;

    if (ctx->mField114 != 0 && desc->mPending == 0 && FUN_0085d8b0() == 0)
        return 0;

    BitReader st;
    st.mSrc0     = ctx->mpSrcPair[0];
    st.mSrc1     = ctx->mpSrcPair[1];
    st.mSrc2     = ctx->mSrcState;
    st.mpCtx     = ctx;
    st.mpField18 = &desc->mField10;

    int bitCount = desc->mBitCount;
    int bitBuf   = desc->mBitBuf;
    const int savedRepeat = desc->mRepeat;

    int acc[4];
    acc[0] = desc->mAcc0;
    acc[1] = desc->mAcc1;
    acc[2] = desc->mAcc2;
    acc[3] = desc->mAcc3;

    const int elemCount = ctx->mElemCount;
    for (int i = 0; i < elemCount; ++i) {
        short* out = (short*)(size_t)((int*)param_2)[i];
        int    ch  = ctx->mChannelIds[i];                       // ctx+0x568
        int*   stream = (int*)ctx->mpStreamTab[ch];             // ctx+0x54c
        int*   table  = (int*)desc->mppTables[stream[5]];       // desc+0x2c + idx*4

        unsigned sym;
        if (bitCount < 8) {
            if (FUN_00859bb0(&st, bitBuf, bitCount, 0) == 0)
                return 0;
            bitCount = st.mBitCount;
            bitBuf   = st.mBitBuf;
        }
        if (bitCount < 8) {
            sym = (unsigned)FUN_00859cc0(&st, bitBuf, bitCount, (int)(size_t)table, 1);
            bitCount = st.mBitCount;
            bitBuf   = st.mBitBuf;
            if ((int)sym < 0)
                return 0;
        } else {
            unsigned v = (unsigned)(bitBuf >> ((bitCount - 8) & 0x1f)) & 0xff;
            int n = table[0x35 + v];
            if (n == 0) {
                sym = (unsigned)FUN_00859cc0(&st, bitBuf, bitCount, (int)(size_t)table, 9);
                bitCount = st.mBitCount;
                bitBuf   = st.mBitBuf;
                if ((int)sym < 0)
                    return 0;
            } else {
                sym = ((unsigned char*)table)[0x4d4 + v];
                bitCount -= n;
            }
        }

        unsigned delta = 0;
        if (sym != 0) {
            if (bitCount < (int)sym) {
                if (FUN_00859bb0(&st, bitBuf, bitCount, (int)sym) == 0)
                    return 0;
                bitCount = st.mBitCount;
                bitBuf   = st.mBitBuf;
            }
            bitCount -= (int)sym;
            delta = ((1u << sym) - 1u) & (unsigned)(bitBuf >> (bitCount & 0x1f));
            if ((int)delta < gHuffLimit_141d308[sym])
                delta = (unsigned)(gHuffOffset_141d348[sym] + (int)delta);
        }

        acc[ch] += (int)delta;
        *out = (short)(acc[ch] << (shift & 0x1f));
    }

    ctx->mpSrcPair[0] = st.mSrc0;
    ctx->mpSrcPair[1] = st.mSrc1;
    ctx->mSrcState    = st.mSrc2;
    desc->mPending   -= 1;
    desc->mBitCount   = bitCount;
    desc->mRepeat     = savedRepeat;
    desc->mAcc0       = acc[0];
    desc->mBitBuf     = bitBuf;
    desc->mAcc1       = acc[1];
    desc->mAcc2       = acc[2];
    desc->mAcc3       = acc[3];
    return 1;
}

// @ 0x0085db80
int __cdecl FUN_0085db80(int param_1, int* param_2)
{
    StreamCtx*  ctx  = (StreamCtx*)param_1;
    StreamDesc* desc = ctx->mpDesc;

    const int limit = ctx->mField594;
    const int shift = ctx->mBitIndex;

    if (ctx->mField114 != 0 && desc->mPending == 0 && FUN_0085d8b0() == 0)
        return 0;

    if (desc->mRepeat != 0) {                  // still inside a run
        desc->mPending -= 1;
        desc->mRepeat  -= 1;
        return 1;
    }

    int idx = ctx->mField590;

    BitReader st;
    st.mSrc0     = ctx->mpSrcPair[0];
    st.mSrc1     = ctx->mpSrcPair[1];
    st.mSrc2     = ctx->mSrcState;
    st.mpCtx     = ctx;
    st.mpField18 = &desc->mField10;

    int             bitBuf   = desc->mBitBuf;
    int             bitCount = desc->mBitCount;
    int*            table    = (int*)desc->mppTables[4];  // descriptor table set, slot 4 (desc+0x3c)
    unsigned char*  bytes    = (unsigned char*)table;
    short*          outBase  = (short*)(size_t)*param_2;
    int             run      = 0;

    for (;;) {
        if (limit < idx)
            break;

        unsigned sym;
        if (bitCount < 8) {
            if (FUN_00859bb0(&st, bitBuf, bitCount, 0) == 0)
                return 0;
            bitCount = st.mBitCount;
            bitBuf   = st.mBitBuf;
        }
        if (bitCount < 8) {
            sym = (unsigned)FUN_00859cc0(&st, bitBuf, bitCount, (int)(size_t)table, 1);
            bitCount = st.mBitCount;
            bitBuf   = st.mBitBuf;
            if ((int)sym < 0)
                return 0;
        } else {
            unsigned v = (unsigned)(bitBuf >> ((bitCount - 8) & 0x1f)) & 0xff;
            int n = table[0x35 + v];                      // table[0xd4/4 + v]
            if (n == 0) {
                sym = (unsigned)FUN_00859cc0(&st, bitBuf, bitCount, (int)(size_t)table, 9);
                bitCount = st.mBitCount;
                bitBuf   = st.mBitBuf;
                if ((int)sym < 0)
                    return 0;
            } else {
                sym = bytes[0x4d4 + v];
                bitCount -= n;
            }
        }

        int      hi = (int)sym >> 4;
        unsigned lo = sym & 0xfu;

        if (lo == 0) {
            if (hi == 0xf) {                              // long zero run
                idx += 0xf;
                if (++idx > limit)
                    break;
                continue;
            }
            run = 1 << (hi & 0x1f);
            if (hi != 0) {
                if (bitCount < hi) {
                    if (FUN_00859bb0(&st, bitBuf, bitCount, hi) == 0)
                        return 0;
                    bitCount = st.mBitCount;
                    bitBuf   = st.mBitBuf;
                }
                bitCount -= hi;
                run += (bitBuf >> (bitCount & 0x1f)) & (run - 1);
            }
            run -= 1;
            break;
        }

        idx += hi;
        if (bitCount < (int)lo) {
            if (FUN_00859bb0(&st, bitBuf, bitCount, (int)lo) == 0)
                return 0;
            bitCount = st.mBitCount;
            bitBuf   = st.mBitBuf;
        }
        bitCount -= (int)lo;
        unsigned val = ((1u << lo) - 1u) & (unsigned)(bitBuf >> (bitCount & 0x1f));
        if ((int)val < gHuffLimit_141d308[lo])
            val = (unsigned)(gHuffOffset_141d348[lo] + (int)val);
        outBase[gOutMap_141e880[idx]] = (short)(val << (shift & 0x1f));
        if (++idx > limit)
            break;
    }

    ctx->mpSrcPair[0] = st.mSrc0;
    ctx->mpSrcPair[1] = st.mSrc1;
    ctx->mSrcState    = st.mSrc2;
    desc->mPending   -= 1;
    desc->mBitBuf     = bitBuf;
    desc->mBitCount   = bitCount;
    desc->mRepeat     = run;
    return 1;
}

// @ 0x0085ddd0
int __cdecl FUN_0085ddd0(int param_1, int param_2)
{
    StreamCtx*  ctx  = (StreamCtx*)param_1;
    int*        outs = (int*)param_2;

    const int   shift = ctx->mBitIndex;
    StreamDesc* desc  = ctx->mpDesc;

    if (ctx->mField114 != 0 && desc->mPending == 0 && FUN_0085d8b0() == 0)
        return 0;

    BitReader st;
    st.mSrc0 = ctx->mpSrcPair[0];
    st.mSrc1 = ctx->mpSrcPair[1];
    st.mSrc2 = ctx->mSrcState;
    st.mpCtx = ctx;
    st.mpField18 = &desc->mField10;

    int buf   = desc->mBitBuf;
    int count = desc->mBitCount;
    const wchar16 mask = (wchar16)(1 << (shift & 0x1f));

    for (int i = 0; i < ctx->mElemCount; ++i) {
        wchar16* out = (wchar16*)outs[i];
        if (count < 1) {
            if (FUN_00859bb0(&st, buf, count, 1) == 0)
                return 0;
            buf   = st.mBitBuf;
            count = st.mBitCount;
        }
        count -= 1;
        if ((buf >> (count & 0x1f)) & 1)
            *out |= mask;
    }

    ctx->mpSrcPair[0] = st.mSrc0;
    ctx->mpSrcPair[1] = st.mSrc1;
    ctx->mSrcState    = st.mSrc2;
    desc->mPending   -= 1;
    desc->mBitBuf     = buf;
    desc->mBitCount   = count;
    return 1;
}

// @ 0x0085ded0
int __cdecl FUN_0085ded0(int param_1, int* param_2)
{
    StreamCtx*  ctx  = (StreamCtx*)param_1;
    StreamDesc* desc = ctx->mpDesc;

    const int      limit    = ctx->mField594;
    const unsigned mask     = 1u << (ctx->mBitIndex & 0x1f);
    const unsigned signMask = (unsigned)(-(int)mask);

    if (ctx->mField114 != 0 && desc->mPending == 0 && FUN_0085d8b0() == 0)
        return 0;

    BitReader st;
    st.mSrc0     = ctx->mpSrcPair[0];
    st.mSrc1     = ctx->mpSrcPair[1];
    st.mSrc2     = ctx->mSrcState;
    st.mpCtx     = ctx;
    st.mpField18 = &desc->mField10;

    int    bitBuf   = desc->mBitBuf;
    int    bitCount = desc->mBitCount;
    short* outBase  = (short*)(size_t)*param_2;
    int*   table    = (int*)desc->mppTables[4];   // +0x3c

    int pass   = desc->mRepeat;                   // +0x14  remaining passes
    int idx    = ctx->mField590;
    int nFixed = 0;
    int fixed[65];

    unsigned delta;
    int      run;

    if (pass != 0)
        goto filterPass;

    for (; idx <= limit; ++idx) {
        unsigned sym;
        if (bitCount < 8) {
            if (FUN_00859bb0(&st, bitBuf, bitCount, 0) == 0)
                goto fail;
            bitCount = st.mBitCount;
            bitBuf   = st.mBitBuf;
        }
        if (bitCount < 8) {
            sym = (unsigned)FUN_00859cc0(&st, bitBuf, bitCount, (int)(size_t)table, 1);
            bitCount = st.mBitCount;
            bitBuf   = st.mBitBuf;
            if ((int)sym < 0)
                goto fail;
        } else {
            unsigned v = (unsigned)(bitBuf >> ((bitCount - 8) & 0x1f)) & 0xff;
            int n = table[0x35 + v];
            if (n == 0) {
                sym = (unsigned)FUN_00859cc0(&st, bitBuf, bitCount, (int)(size_t)table, 9);
                bitCount = st.mBitCount;
                bitBuf   = st.mBitBuf;
                if ((int)sym < 0)
                    goto fail;
            } else {
                sym = ((unsigned char*)table)[0x4d4 + v];
                bitCount -= n;
            }
        }

        run   = (int)sym >> 4;
        delta = 0;
        if ((sym & 0xfu) == 0) {
            if (run != 0xf) {                     // start of a filtered pass
                pass = 1 << (run & 0x1f);
                if (run == 0)
                    goto filterPass;
                if (bitCount < run) {
                    if (FUN_00859bb0(&st, bitBuf, bitCount, run) == 0)
                        goto fail;
                    bitCount = st.mBitCount;
                    bitBuf   = st.mBitBuf;
                }
                bitCount -= run;
                pass += (bitBuf >> (bitCount & 0x1f)) & (pass - 1);
                goto filterPass;
            }
            // run == 0xf: plain zero run, falls through with delta == 0
        } else {
            if ((sym & 0xfu) != 1) {              // corrupt stream
                StreamInner* inner = ctx->mpInner;
                inner->mErrorCode = 0x72;
                (*(void(__cdecl**)(int, int))(&inner->mpNotify))(param_1, -1);
            }
            if (bitCount < 1) {
                if (FUN_00859bb0(&st, bitBuf, bitCount, 1) == 0)
                    goto fail;
                bitCount = st.mBitCount;
                bitBuf   = st.mBitBuf;
            }
            bitCount -= 1;
            delta = ((bitBuf >> (bitCount & 0x1f)) & 1) ? mask : signMask;
        }

        do {
            short* p = outBase + gOutMap_141e880[idx];
            if (*p == 0) {
                if (--run < 0)
                    break;
            } else {
                if (bitCount < 1) {
                    if (FUN_00859bb0(&st, bitBuf, bitCount, 1) == 0)
                        goto fail;
                    bitCount = st.mBitCount;
                    bitBuf   = st.mBitBuf;
                }
                bitCount -= 1;
                if (((bitBuf >> (bitCount & 0x1f)) & 1) && (mask & (unsigned)*p) == 0) {
                    if (*p < 0)
                        *p = (short)(*p + (short)signMask);
                    else
                        *p = (short)(*p + (short)mask);
                }
            }
            ++idx;
        } while (idx <= limit);

        if (delta != 0) {
            int slot = gOutMap_141e880[idx];
            outBase[slot] = (short)delta;
            fixed[nFixed++] = slot;
        }
    }
    goto done;

filterPass:
    if (pass != 0) {
        for (; idx <= limit; ++idx) {
            short* p = outBase + gOutMap_141e880[idx];
            if (*p != 0) {
                if (bitCount < 1) {
                    if (FUN_00859bb0(&st, bitBuf, bitCount, 1) == 0)
                        goto fail;
                    bitCount = st.mBitCount;
                    bitBuf   = st.mBitBuf;
                }
                bitCount -= 1;
                if (((bitBuf >> (bitCount & 0x1f)) & 1) && (mask & (unsigned)*p) == 0) {
                    unsigned d = ((int)*p < 0) ? signMask : mask;
                    *p = (short)(*p + (short)d);
                }
            }
        }
        pass -= 1;
    }

done:
    ctx->mpSrcPair[0] = st.mSrc0;
    ctx->mpSrcPair[1] = st.mSrc1;
    ctx->mSrcState    = st.mSrc2;
    desc->mPending   -= 1;
    desc->mBitCount   = bitCount;
    desc->mBitBuf     = bitBuf;
    desc->mRepeat     = pass;
    return 1;

fail:
    for (; 0 < nFixed; --nFixed)
        outBase[fixed[nFixed]] = 0;
    return 0;
}

// @ 0x0085e2d0
void __cdecl FUN_0085e2d0(int param_1)
{
    StreamCtx*  ctx  = (StreamCtx*)param_1;
    StreamDesc* desc = ctx->mpDesc;
    StreamInner* inner = ctx->mpInner;

    const bool interlaced = ctx->mField590 != 0;
    bool bad = false;
    bool ok;

    if (interlaced) {
        if (ctx->mField594 < ctx->mField590 || 0x3f < ctx->mField594)
            bad = true;
        ok = ctx->mChannelCount == 1;
    } else {
        ok = ctx->mField594 == 0;
    }
    if (!ok)
        bad = true;
    if (ctx->mField598 != 0 && ctx->mBitIndex != ctx->mField598 - 1)
        bad = true;

    if (0xd < ctx->mBitIndex || bad) {
        inner->mErrorCode = 0xe;
        inner->mField18 = ctx->mField590;
        inner->mField1c = ctx->mField594;
        inner->mField20 = ctx->mField598;
        inner->mField24 = ctx->mBitIndex;
        (*(void(__cdecl**)(int))inner)((int)(size_t)param_1);
    }

    const int count = ctx->mChannelCount;
    if (0 < count) {
        void** ppStream = ctx->mpStreamTab;
        for (int i = 0; i < count; ++i) {
            StreamObject* stream = (StreamObject*)ppStream[i];
            const int slot = stream->mIndex;
            int* piVal = (int*)((char*)ctx->mpSampleTable + slot * 0x100);
            if (interlaced && *piVal < 0) {
                inner->mErrorCode = 0x6f;
                inner->mField18 = slot;
                inner->mField1c = 0;
                ((void(__cdecl*)(int, int))inner->mpNotify)((int)(size_t)param_1, -1);
            }
            int idx = ctx->mField590;
            if (idx <= ctx->mField594) {
                do {
                    const int val = piVal[idx];
                    if (ctx->mField598 != (val & ((val < 0) - 1))) {
                        inner->mErrorCode = 0x6f;
                        inner->mField18 = slot;
                        inner->mField1c = idx;
                        ((void(__cdecl*)(int, int))inner->mpNotify)((int)(size_t)param_1, -1);
                    }
                    piVal[idx] = ctx->mBitIndex;
                    ++idx;
                } while (idx <= ctx->mField594);
            }
        }
    }

    if (ctx->mField598 == 0) {
        if (interlaced)
            desc->mpfnDecode = (void*)&FUN_0085db80;
        else
            desc->mpfnDecode = (void*)&FUN_0085d930;
    } else if (interlaced) {
        desc->mpfnDecode = (void*)&FUN_0085ded0;
    } else {
        desc->mpfnDecode = (void*)&FUN_0085ddd0;
    }

    if (0 < count) {
        int*  puStack = &desc->mAcc0;              // desc+0x18
        void** ppStream = ctx->mpStreamTab;
        for (int i = 0; i < count; ++i) {
            StreamObject* stream = (StreamObject*)ppStream[i];
            if (interlaced) {
                const unsigned mode = (unsigned)stream->mField18;
                if (3 < mode || ctx->mpTablesC4[mode] == 0) {
                    inner->mErrorCode = 0x31;
                    inner->mField18 = (int)mode;
                    (*(void(__cdecl**)(int))inner)((int)(size_t)param_1);
                }
                int** slot = &desc->mppTables[mode];
                FUN_008599f0((int)(size_t)param_1, (int)(size_t)ctx->mpTablesC4[mode], slot);
                desc->mppTables[4] = *slot;
            } else if (ctx->mField598 == 0) {
                const unsigned mode = (unsigned)stream->mField14;
                if (3 < mode || ctx->mpTablesB4[mode] == 0) {
                    inner->mErrorCode = 0x31;
                    inner->mField18 = (int)mode;
                    (*(void(__cdecl**)(int))inner)((int)(size_t)param_1);
                }
                FUN_008599f0((int)(size_t)param_1, (int)(size_t)ctx->mpTablesB4[mode], &desc->mppTables[mode]);
            }
            *puStack = 0;
            ++puStack;
        }
    }

    desc->mBitCount = 0;
    desc->mBitBuf   = 0;
    desc->mField10  = 0;
    desc->mRepeat   = 0;
    desc->mPending  = ctx->mField114;
}

// @ 0x0085e630
void __cdecl FUN_0085e630(int param_1, int param_2, int param_3, int param_4, int param_5, int* param_6, int param_7)
{
    int* piVar4 = param_6;
    int iVar3 = param_1;
    int iVar2 = *(int*)(param_1 + 0x5b0);
    uint uVar5 = param_7 - *param_6;
    if (uVar5 > *(uint*)(iVar2 + 0x10)) {
        uVar5 = *(uint*)(iVar2 + 0x10);
    }
    int local = 0;
    (*(void(__cdecl**)(int, int, int, int, int, int*, uint))(*(int*)(param_1 + 0x5c4) + 4))(
        iVar3, param_2, param_3, param_4, *(int*)(iVar2 + 0xc), &local, uVar5);
    (*(void(__cdecl**)(int, int, int, int))(*(int*)(iVar3 + 0x5cc) + 4))(
        iVar3, *(int*)(iVar2 + 0xc), param_5 + *piVar4 * 4, local);
    *piVar4 = *piVar4 + local;
}

// @ 0x0085e6b0
void __cdecl FUN_0085e6b0(int param_1, int param_2, int param_3, int param_4, int param_5, int* param_6)
{
    int iVar2 = *(int*)(param_1 + 0x5b0);
    uint* puVar1 = (uint*)(iVar2 + 0x18);
    if (*(int*)(iVar2 + 0x18) == 0) {
        int uVar4 = (*(int(__cdecl**)(int, int, int, int, int))(*(int*)(param_1 + 4) + 0x1c))(
            param_1, *(int*)(iVar2 + 8), *(int*)(iVar2 + 0x14), *(int*)(iVar2 + 0x10), 1);
        *(int*)(iVar2 + 0xc) = uVar4;
    }
    uint uVar3 = *puVar1;
    (*(void(__cdecl**)(int, int, int, int, int, uint*, int))(*(int*)(param_1 + 0x5c4) + 4))(
        param_1, param_2, param_3, param_4, *(int*)(iVar2 + 0xc), puVar1, *(int*)(iVar2 + 0x10));
    if (*puVar1 > uVar3) {
        int iVar5 = *puVar1 - uVar3;
        (*(void(__cdecl**)(int, int, int, int))(*(int*)(param_1 + 0x5cc) + 4))(
            param_1, *(int*)(iVar2 + 0xc) + uVar3 * 4, 0, iVar5);
        *param_6 = *param_6 + iVar5;
    }
    if (*puVar1 >= *(uint*)(iVar2 + 0x10)) {
        *(int*)(iVar2 + 0x14) = *(int*)(iVar2 + 0x14) + *(uint*)(iVar2 + 0x10);
        *puVar1 = 0;
    }
}

// @ 0x0085e760
void __cdecl FUN_0085e760(int param_1, int param_2, int param_3, int param_4, int param_5, int* param_6, int param_7)
{
    int iVar1 = *(int*)(param_1 + 0x5b0);
    if (*(int*)(iVar1 + 0x18) == 0) {
        int uVar2 = (*(int(__cdecl**)(int, int, int, int, int))(*(int*)(param_1 + 4) + 0x1c))(
            param_1, *(int*)(iVar1 + 8), *(int*)(iVar1 + 0x14), *(int*)(iVar1 + 0x10), 0);
        *(int*)(iVar1 + 0xc) = uVar2;
    }
    uint uVar4 = *(int*)(iVar1 + 0x10) - *(int*)(iVar1 + 0x18);
    uint uVar3 = param_7 - *param_6;
    if (uVar4 > uVar3) {
        uVar4 = uVar3;
    }
    uVar3 = *(int*)(param_1 + 0x74) - *(int*)(iVar1 + 0x14);
    if (uVar4 > uVar3) {
        uVar4 = uVar3;
    }
    (*(void(__cdecl**)(int, int, int, uint))(*(int*)(param_1 + 0x5cc) + 4))(
        param_1, *(int*)(iVar1 + 0xc) + *(int*)(iVar1 + 0x18) * 4, param_5 + *param_6 * 4, uVar4);
    *param_6 = *param_6 + uVar4;
    *(int*)(iVar1 + 0x18) = *(int*)(iVar1 + 0x18) + uVar4;
    if (*(uint*)(iVar1 + 0x18) >= *(uint*)(iVar1 + 0x10)) {
        *(int*)(iVar1 + 0x14) = *(int*)(iVar1 + 0x14) + *(uint*)(iVar1 + 0x10);
        *(int*)(iVar1 + 0x18) = 0;
    }
}
