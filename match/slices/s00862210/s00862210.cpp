// Slice s00862210 - libjpeg (IJG 6a) jpeg_idct_4x4 (jidctred.c), 0x00862210.
//
// The retail image statically links IJG libjpeg; this is the upstream function (reduced-size 4x4
// inverse DCT: 8x8 coefficient block -> 4x4 samples) built with the library flags.
// jconfig.h next to this file is the project's jconfig.vc (third_party/jpeg-6a/jconfig.h).
#define JPEG_INTERNALS
#include "../../../work/third_party/src/jpeg-6a/jinclude.h"
#include "../../../work/third_party/src/jpeg-6a/jpeglib.h"
#include "../../../work/third_party/src/jpeg-6a/jdct.h"

/* The retail jpeg_decompress_struct is not the stock 6a layout: it carries a 1024-byte
 * comment buffer (+0x130) and a trailing read_dht flag, so sample_range_limit sits at +0x544
 * (stock 6a: +0x140).  Only that member is used here. */
struct retail_decompress_struct {
  char pad_to_range_limit[0x544];
  JSAMPLE * sample_range_limit;   /* +0x544 */
};
typedef struct retail_decompress_struct * retail_decompress_ptr;

/* Scaling is the same as in jidctint.c. */

#if BITS_IN_JSAMPLE == 8
#define CONST_BITS  13
#define PASS1_BITS  2
#else
#define CONST_BITS  13
#define PASS1_BITS  1		/* lose a little precision to avoid overflow */
#endif

/* Some C compilers fail to reduce "FIX(constant)" at compile time, thus
 * causing a lot of useless floating-point operations at run time.
 * To get around this we use the following pre-calculated constants.
 * If you change CONST_BITS you may want to add appropriate values.
 * (With a reasonable C compiler, you can just rely on the FIX() macro...)
 */

#if CONST_BITS == 13
#define FIX_0_211164243  ((INT32)  1730)	/* FIX(0.211164243) */
#define FIX_0_509795579  ((INT32)  4176)	/* FIX(0.509795579) */
#define FIX_0_601344887  ((INT32)  4926)	/* FIX(0.601344887) */
#define FIX_0_720959822  ((INT32)  5906)	/* FIX(0.720959822) */
#define FIX_0_765366865  ((INT32)  6270)	/* FIX(0.765366865) */
#define FIX_0_850430095  ((INT32)  6967)	/* FIX(0.850430095) */
#define FIX_0_899976223  ((INT32)  7373)	/* FIX(0.899976223) */
#define FIX_1_061594337  ((INT32)  8697)	/* FIX(1.061594337) */
#define FIX_1_272758580  ((INT32)  10426)	/* FIX(1.272758580) */
#define FIX_1_451774981  ((INT32)  11893)	/* FIX(1.451774981) */
#define FIX_1_847759065  ((INT32)  15137)	/* FIX(1.847759065) */
#define FIX_2_172734803  ((INT32)  17799)	/* FIX(2.172734803) */
#define FIX_2_562915447  ((INT32)  20995)	/* FIX(2.562915447) */
#define FIX_3_624509785  ((INT32)  29692)	/* FIX(3.624509785) */
#else
#define FIX_0_211164243  FIX(0.211164243)
#define FIX_0_509795579  FIX(0.509795579)
#define FIX_0_601344887  FIX(0.601344887)
#define FIX_0_720959822  FIX(0.720959822)
#define FIX_0_765366865  FIX(0.765366865)
#define FIX_0_850430095  FIX(0.850430095)
#define FIX_0_899976223  FIX(0.899976223)
#define FIX_1_061594337  FIX(1.061594337)
#define FIX_1_272758580  FIX(1.272758580)
#define FIX_1_451774981  FIX(1.451774981)
#define FIX_1_847759065  FIX(1.847759065)
#define FIX_2_172734803  FIX(2.172734803)
#define FIX_2_562915447  FIX(2.562915447)
#define FIX_3_624509785  FIX(3.624509785)
#endif


/* Multiply an INT32 variable by an INT32 constant to yield an INT32 result.
 * For 8-bit samples with the recommended scaling, all the variable
 * and constant values involved are no more than 16 bits wide, so a
 * 16x16->32 bit multiply can be used instead of a full 32x32 multiply.
 * For 12-bit samples, a full 32-bit multiplication will be needed.
 */

#if BITS_IN_JSAMPLE == 8
#define MULTIPLY(var,const)  MULTIPLY16C16(var,const)
#else
#define MULTIPLY(var,const)  ((var) * (const))
#endif


/* Dequantize a coefficient by multiplying it by the multiplier-table
 * entry; produce an int result.  In this module, both inputs and result
 * are 16 bits or less, so either int or short multiply will work.
 */

#define DEQUANTIZE(coef,quantval)  (((ISLOW_MULT_TYPE) (coef)) * (quantval))


/*
 * Perform dequantization and inverse DCT on one block of coefficients,
 * producing a reduced-size 4x4 output block.
 */

GLOBAL(void)
jpeg_idct_4x4 (retail_decompress_ptr cinfo, jpeg_component_info * compptr,
	       JCOEFPTR coef_block,
	       JSAMPARRAY output_buf, JDIMENSION output_col)
{
  INT32 tmp0, tmp2, tmp10, tmp12;
  INT32 z1, z2, z3, z4;
  JCOEFPTR inptr;
  ISLOW_MULT_TYPE * quantptr;
  int * wsptr;
  JSAMPROW outptr;
  JSAMPLE *range_limit = IDCT_range_limit(cinfo);
  int ctr;
  int workspace[DCTSIZE*4];	/* buffers data between passes */
  SHIFT_TEMPS

  /* Pass 1: process columns from input, store into work array. */

  inptr = coef_block;
  quantptr = (ISLOW_MULT_TYPE *) compptr->dct_table;
  wsptr = workspace;
  for (ctr = DCTSIZE; ctr > 0; inptr++, quantptr++, wsptr++, ctr--) {
    /* Don't bother to process column 4, because second pass won't use it */
    if (ctr == DCTSIZE-4)
      continue;
    if ((inptr[DCTSIZE*1] | inptr[DCTSIZE*2] | inptr[DCTSIZE*3] |
	 inptr[DCTSIZE*5] | inptr[DCTSIZE*6] | inptr[DCTSIZE*7]) == 0) {
      /* AC terms all zero; we need not examine term 4 for 4x4 output */
      int dcval = DEQUANTIZE(inptr[DCTSIZE*0], quantptr[DCTSIZE*0]) << PASS1_BITS;
      
      wsptr[DCTSIZE*0] = dcval;
      wsptr[DCTSIZE*1] = dcval;
      wsptr[DCTSIZE*2] = dcval;
      wsptr[DCTSIZE*3] = dcval;
      
      continue;
    }
    
    /* Even part */
    
    tmp0 = DEQUANTIZE(inptr[DCTSIZE*0], quantptr[DCTSIZE*0]);
    tmp0 <<= (CONST_BITS+1);
    
    z2 = DEQUANTIZE(inptr[DCTSIZE*2], quantptr[DCTSIZE*2]);
    z3 = DEQUANTIZE(inptr[DCTSIZE*6], quantptr[DCTSIZE*6]);

    tmp2 = MULTIPLY(z2, FIX_1_847759065) + MULTIPLY(z3, - FIX_0_765366865);
    
    tmp10 = tmp0 + tmp2;
    tmp12 = tmp0 - tmp2;
    
    /* Odd part */
    
    z1 = DEQUANTIZE(inptr[DCTSIZE*7], quantptr[DCTSIZE*7]);
    z2 = DEQUANTIZE(inptr[DCTSIZE*5], quantptr[DCTSIZE*5]);
    z3 = DEQUANTIZE(inptr[DCTSIZE*3], quantptr[DCTSIZE*3]);
    z4 = DEQUANTIZE(inptr[DCTSIZE*1], quantptr[DCTSIZE*1]);
    
    tmp0 = MULTIPLY(z1, - FIX_0_211164243) /* sqrt(2) * (c3-c1) */
	 + MULTIPLY(z2, FIX_1_451774981) /* sqrt(2) * (c3+c7) */
	 + MULTIPLY(z3, - FIX_2_172734803) /* sqrt(2) * (-c1-c5) */
	 + MULTIPLY(z4, FIX_1_061594337); /* sqrt(2) * (c5+c7) */
    
    tmp2 = MULTIPLY(z1, - FIX_0_509795579) /* sqrt(2) * (c7-c5) */
	 + MULTIPLY(z2, - FIX_0_601344887) /* sqrt(2) * (c5-c1) */
	 + MULTIPLY(z3, FIX_0_899976223) /* sqrt(2) * (c3-c7) */
	 + MULTIPLY(z4, FIX_2_562915447); /* sqrt(2) * (c1+c3) */

    /* Final output stage */
    
    wsptr[DCTSIZE*0] = (int) DESCALE(tmp10 + tmp2, CONST_BITS-PASS1_BITS+1);
    wsptr[DCTSIZE*3] = (int) DESCALE(tmp10 - tmp2, CONST_BITS-PASS1_BITS+1);
    wsptr[DCTSIZE*1] = (int) DESCALE(tmp12 + tmp0, CONST_BITS-PASS1_BITS+1);
    wsptr[DCTSIZE*2] = (int) DESCALE(tmp12 - tmp0, CONST_BITS-PASS1_BITS+1);
  }
  
  /* Pass 2: process 4 rows from work array, store into output array. */

  wsptr = workspace;
  for (ctr = 0; ctr < 4; ctr++) {
    outptr = output_buf[ctr] + output_col;
    /* It's not clear whether a zero row test is worthwhile here ... */

#ifndef NO_ZERO_ROW_TEST
    if ((wsptr[1] | wsptr[2] | wsptr[3] | wsptr[5] | wsptr[6] |
	 wsptr[7]) == 0) {
      /* AC terms all zero */
      JSAMPLE dcval = range_limit[(int) DESCALE((INT32) wsptr[0], PASS1_BITS+3)
				  & RANGE_MASK];
      
      outptr[0] = dcval;
      outptr[1] = dcval;
      outptr[2] = dcval;
      outptr[3] = dcval;
      
      wsptr += DCTSIZE;		/* advance pointer to next row */
      continue;
    }
#endif
    
    /* Even part */
    
    tmp0 = ((INT32) wsptr[0]) << (CONST_BITS+1);
    
    tmp2 = MULTIPLY((INT32) wsptr[2], FIX_1_847759065)
	 + MULTIPLY((INT32) wsptr[6], - FIX_0_765366865);
    
    tmp10 = tmp0 + tmp2;
    tmp12 = tmp0 - tmp2;
    
    /* Odd part */
    
    z1 = (INT32) wsptr[7];
    z2 = (INT32) wsptr[5];
    z3 = (INT32) wsptr[3];
    z4 = (INT32) wsptr[1];
    
    tmp0 = MULTIPLY(z1, - FIX_0_211164243) /* sqrt(2) * (c3-c1) */
	 + MULTIPLY(z2, FIX_1_451774981) /* sqrt(2) * (c3+c7) */
	 + MULTIPLY(z3, - FIX_2_172734803) /* sqrt(2) * (-c1-c5) */
	 + MULTIPLY(z4, FIX_1_061594337); /* sqrt(2) * (c5+c7) */
    
    tmp2 = MULTIPLY(z1, - FIX_0_509795579) /* sqrt(2) * (c7-c5) */
	 + MULTIPLY(z2, - FIX_0_601344887) /* sqrt(2) * (c5-c1) */
	 + MULTIPLY(z3, FIX_0_899976223) /* sqrt(2) * (c3-c7) */
	 + MULTIPLY(z4, FIX_2_562915447); /* sqrt(2) * (c1+c3) */

    /* Final output stage */
    
    outptr[0] = range_limit[(int) DESCALE(tmp10 + tmp2,
					  CONST_BITS+PASS1_BITS+3+1)
			    & RANGE_MASK];
    outptr[3] = range_limit[(int) DESCALE(tmp10 - tmp2,
					  CONST_BITS+PASS1_BITS+3+1)
			    & RANGE_MASK];
    outptr[1] = range_limit[(int) DESCALE(tmp12 + tmp0,
					  CONST_BITS+PASS1_BITS+3+1)
			    & RANGE_MASK];
    outptr[2] = range_limit[(int) DESCALE(tmp12 - tmp0,
					  CONST_BITS+PASS1_BITS+3+1)
			    & RANGE_MASK];
    
    wsptr += DCTSIZE;		/* advance pointer to next row */
  }
}


/*
 * Perform dequantization and inverse DCT on one block of coefficients,
 * producing a reduced-size 2x2 output block.
 */

// @ 0x008628a0
GLOBAL(void)
jpeg_idct_2x2 (retail_decompress_ptr cinfo, jpeg_component_info * compptr,
	       JCOEFPTR coef_block,
	       JSAMPARRAY output_buf, JDIMENSION output_col)
{
  INT32 tmp0, tmp10, z1;
  JCOEFPTR inptr;
  ISLOW_MULT_TYPE * quantptr;
  int * wsptr;
  JSAMPROW outptr;
  JSAMPLE *range_limit = IDCT_range_limit(cinfo);
  int ctr;
  int workspace[DCTSIZE*2];	/* buffers data between passes */
  SHIFT_TEMPS

  /* Pass 1: process columns from input, store into work array. */

  inptr = coef_block;
  quantptr = (ISLOW_MULT_TYPE *) compptr->dct_table;
  wsptr = workspace;
  for (ctr = DCTSIZE; ctr > 0; inptr++, quantptr++, wsptr++, ctr--) {
    /* Don't bother to process columns 2,4,6 */
    if (ctr == DCTSIZE-2 || ctr == DCTSIZE-4 || ctr == DCTSIZE-6)
      continue;
    if ((inptr[DCTSIZE*1] | inptr[DCTSIZE*3] |
	 inptr[DCTSIZE*5] | inptr[DCTSIZE*7]) == 0) {
      /* AC terms all zero; we need not examine terms 2,4,6 for 2x2 output */
      int dcval = DEQUANTIZE(inptr[DCTSIZE*0], quantptr[DCTSIZE*0]) << PASS1_BITS;
      
      wsptr[DCTSIZE*0] = dcval;
      wsptr[DCTSIZE*1] = dcval;
      
      continue;
    }
    
    /* Even part */
    
    z1 = DEQUANTIZE(inptr[DCTSIZE*0], quantptr[DCTSIZE*0]);
    tmp10 = z1 << (CONST_BITS+2);
    
    /* Odd part */

    z1 = DEQUANTIZE(inptr[DCTSIZE*7], quantptr[DCTSIZE*7]);
    tmp0 = MULTIPLY(z1, - FIX_0_720959822); /* sqrt(2) * (c7-c5+c3-c1) */
    z1 = DEQUANTIZE(inptr[DCTSIZE*5], quantptr[DCTSIZE*5]);
    tmp0 += MULTIPLY(z1, FIX_0_850430095); /* sqrt(2) * (-c1+c3+c5+c7) */
    z1 = DEQUANTIZE(inptr[DCTSIZE*3], quantptr[DCTSIZE*3]);
    tmp0 += MULTIPLY(z1, - FIX_1_272758580); /* sqrt(2) * (-c1+c3-c5-c7) */
    z1 = DEQUANTIZE(inptr[DCTSIZE*1], quantptr[DCTSIZE*1]);
    tmp0 += MULTIPLY(z1, FIX_3_624509785); /* sqrt(2) * (c1+c3+c5+c7) */

    /* Final output stage */
    
    wsptr[DCTSIZE*0] = (int) DESCALE(tmp10 + tmp0, CONST_BITS-PASS1_BITS+2);
    wsptr[DCTSIZE*1] = (int) DESCALE(tmp10 - tmp0, CONST_BITS-PASS1_BITS+2);
  }
  
  /* Pass 2: process 2 rows from work array, store into output array. */

  wsptr = workspace;
  for (ctr = 0; ctr < 2; ctr++) {
    outptr = output_buf[ctr] + output_col;
    /* It's not clear whether a zero row test is worthwhile here ... */

#ifndef NO_ZERO_ROW_TEST
    if ((wsptr[1] | wsptr[3] | wsptr[5] | wsptr[7]) == 0) {
      /* AC terms all zero */
      JSAMPLE dcval = range_limit[(int) DESCALE((INT32) wsptr[0], PASS1_BITS+3)
				  & RANGE_MASK];
      
      outptr[0] = dcval;
      outptr[1] = dcval;
      
      wsptr += DCTSIZE;		/* advance pointer to next row */
      continue;
    }
#endif
    
    /* Even part */
    
    tmp10 = ((INT32) wsptr[0]) << (CONST_BITS+2);
    
    /* Odd part */

    tmp0 = MULTIPLY((INT32) wsptr[7], - FIX_0_720959822) /* sqrt(2) * (c7-c5+c3-c1) */
	 + MULTIPLY((INT32) wsptr[5], FIX_0_850430095) /* sqrt(2) * (-c1+c3+c5+c7) */
	 + MULTIPLY((INT32) wsptr[3], - FIX_1_272758580) /* sqrt(2) * (-c1+c3-c5-c7) */
	 + MULTIPLY((INT32) wsptr[1], FIX_3_624509785); /* sqrt(2) * (c1+c3+c5+c7) */

    /* Final output stage */
    
    outptr[0] = range_limit[(int) DESCALE(tmp10 + tmp0,
					  CONST_BITS+PASS1_BITS+3+2)
			    & RANGE_MASK];
    outptr[1] = range_limit[(int) DESCALE(tmp10 - tmp0,
					  CONST_BITS+PASS1_BITS+3+2)
			    & RANGE_MASK];
    
    wsptr += DCTSIZE;		/* advance pointer to next row */
  }
}


/*
 * Perform dequantization and inverse DCT on one block of coefficients,
 * producing a reduced-size 1x1 output block.
 */

// @ 0x00862d20
GLOBAL(void)
jpeg_idct_1x1 (retail_decompress_ptr cinfo, jpeg_component_info * compptr,
	       JCOEFPTR coef_block,
	       JSAMPARRAY output_buf, JDIMENSION output_col)
{
  int dcval;
  ISLOW_MULT_TYPE * quantptr;
  JSAMPLE *range_limit = IDCT_range_limit(cinfo);
  SHIFT_TEMPS

  /* We hardly need an inverse DCT routine for this: just take the
   * average pixel value, which is one-eighth of the DC coefficient.
   */
  quantptr = (ISLOW_MULT_TYPE *) compptr->dct_table;
  dcval = DEQUANTIZE(coef_block[0], quantptr[0]);
  dcval = (int) DESCALE((INT32) dcval, 3);

  output_buf[0][output_col] = range_limit[dcval & RANGE_MASK];
}


/* ==================================================================== *
 * jmemsys.h / jmemmgr.c private types (Spore's libjpeg 6a).            *
 * ==================================================================== */

#ifndef MAX_ALLOC_CHUNK
#define MAX_ALLOC_CHUNK  1000000000L
#endif

#define MIN_SLOP  50

#ifndef ALIGN_TYPE
#define ALIGN_TYPE  double
#endif

#define JERR_OUT_OF_MEMORY   53
#define JERR_BAD_POOL_ID     12
#define JERR_WIDTH_OVERFLOW  69
#define JERR_TFILE_CREATE    62
#define JERR_TFILE_READ      63
#define JERR_TFILE_SEEK      64
#define JERR_TFILE_WRITE     65

/* ERREXIT: record the message code and invoke the error handler. */
#define ERREXIT(cinfo, code)  \
  ((cinfo)->err->msg_code = (code), \
   (*(cinfo)->err->error_exit) ((j_common_ptr) (cinfo)))

/* ERREXIT1: same, recording one integer message parameter. */
#define ERREXIT1(cinfo, code, p1)  \
  ((cinfo)->err->msg_code = (code), \
   (cinfo)->err->msg_parm.i[0] = (p1), \
   (*(cinfo)->err->error_exit) ((j_common_ptr) (cinfo)))

typedef union small_pool_struct * small_pool_ptr;
typedef union small_pool_struct {
  struct {
    small_pool_ptr next;	/* next in list of pools */
    size_t bytes_used;		/* how many bytes already used within pool */
    size_t bytes_left;		/* bytes still available in this pool */
  } hdr;
  double dummy;			/* ensure alignment */
} small_pool_hdr;

typedef union large_pool_struct * large_pool_ptr;
typedef union large_pool_struct {
  struct {
    large_pool_ptr next;	/* next in list of pools */
    size_t bytes_used;		/* how many bytes already used within pool */
    size_t bytes_left;		/* bytes still available in this pool */
  } hdr;
  double dummy;			/* ensure alignment */
} large_pool_hdr;

struct jvirt_sarray_control;
struct jvirt_barray_control;

typedef struct {
  struct jpeg_memory_mgr pub;	/* public fields */

  small_pool_ptr small_list[JPOOL_NUMPOOLS];
  large_pool_ptr large_list[JPOOL_NUMPOOLS];

  struct jvirt_sarray_control * virt_sarray_list;
  struct jvirt_barray_control * virt_barray_list;

  long total_space_allocated;
  JDIMENSION last_rowsperchunk;
} my_memory_mgr;

typedef my_memory_mgr * my_mem_ptr;

#define TEMP_NAME_LENGTH   64

typedef struct backing_store_struct * backing_store_ptr;

typedef struct backing_store_struct {
  /* Methods for reading/writing/closing this backing-store object */
  void (*read_backing_store) (j_common_ptr cinfo, backing_store_ptr info,
			      void * buffer_address,
			      long file_offset, long byte_count);
  void (*write_backing_store) (j_common_ptr cinfo, backing_store_ptr info,
			       void * buffer_address,
			       long file_offset, long byte_count);
  void (*close_backing_store) (j_common_ptr cinfo, backing_store_ptr info);

  /* Private fields for system-dependent backing-store management */
  FILE * temp_file;		/* stdio reference to temp file */
  char temp_name[TEMP_NAME_LENGTH]; /* name of temp file */
} backing_store_info;

/* Imported helpers defined in the jmemmgr.c object (other slices). */
extern void * jpeg_get_small (j_common_ptr cinfo, size_t sizeofobject);  // 0x00862d70
extern void FAR * jpeg_get_large (j_common_ptr cinfo, size_t sizeofobject); // 0x00863040

/* jmemmgr.c internals this object calls. */
/* out_of_memory is a METHODDEF in jmemmgr.c and is inlined at each call site;
 * define it here so cl produces the same inlined error path. */
METHODDEF(void)
out_of_memory (j_common_ptr cinfo, int which)
{
  ERREXIT1(cinfo, JERR_OUT_OF_MEMORY, which);
}
extern void FAR * alloc_large (j_common_ptr cinfo, int pool_id, size_t sizeofobject);

#define jpeg_free_small(cinfo, object, sizeofobject)  /* nothing */


/* ------------------------------------------------------------------ *
 * jmemansi.c                                                          *
 * ------------------------------------------------------------------ */

// @ 0x00862d80
GLOBAL(long)
jpeg_mem_available (j_common_ptr cinfo, long min_bytes_needed,
		    long max_bytes_needed, long already_allocated)
{
  return cinfo->mem->max_memory_to_use - already_allocated;
}


// @ 0x00862d90
METHODDEF(void)
read_backing_store (j_common_ptr cinfo, backing_store_ptr info,
		    void FAR * buffer_address,
		    long file_offset, long byte_count)
{
  if (fseek(info->temp_file, file_offset, SEEK_SET))
    ERREXIT(cinfo, JERR_TFILE_SEEK);
  if (JFREAD(info->temp_file, buffer_address, byte_count)
      != (size_t) byte_count)
    ERREXIT(cinfo, JERR_TFILE_READ);
}


// @ 0x00862e00
METHODDEF(void)
write_backing_store (j_common_ptr cinfo, backing_store_ptr info,
		     void FAR * buffer_address,
		     long file_offset, long byte_count)
{
  if (fseek(info->temp_file, file_offset, SEEK_SET))
    ERREXIT(cinfo, JERR_TFILE_SEEK);
  if (JFWRITE(info->temp_file, buffer_address, byte_count)
      != (size_t) byte_count)
    ERREXIT(cinfo, JERR_TFILE_WRITE);
}


// @ 0x00862e70
METHODDEF(void)
close_backing_store (j_common_ptr cinfo, backing_store_ptr info)
{
  fclose(info->temp_file);
  /* Since this implementation uses tmpfile() to create the file,
   * no explicit file deletion is needed.
   */
}


// @ 0x00862e80
GLOBAL(void)
jpeg_open_backing_store (j_common_ptr cinfo, backing_store_ptr info,
			 long total_bytes_needed)
{
  if ((info->temp_file = tmpfile()) == NULL)
    ERREXITS(cinfo, JERR_TFILE_CREATE, "");
  info->read_backing_store = read_backing_store;
  info->write_backing_store = write_backing_store;
  info->close_backing_store = close_backing_store;
}


/* ------------------------------------------------------------------ *
 * jmemmgr.c                                                           *
 * ------------------------------------------------------------------ */

static const size_t first_pool_slop[JPOOL_NUMPOOLS] =
{
	1600,			/* first PERMANENT pool */
	16000			/* first IMAGE pool */
};

static const size_t extra_pool_slop[JPOOL_NUMPOOLS] =
{
	0,			/* additional PERMANENT pools */
	5000			/* additional IMAGE pools */
};


// @ 0x00862ef0
METHODDEF(void *)
alloc_small (j_common_ptr cinfo, int pool_id, size_t sizeofobject)
/* Allocate a "small" object */
{
  my_mem_ptr mem = (my_mem_ptr) cinfo->mem;
  small_pool_ptr hdr_ptr, prev_hdr_ptr;
  char * data_ptr;
  size_t odd_bytes, min_request, slop;

  /* Check for unsatisfiable request (do now to ensure no overflow below) */
  if (sizeofobject > (size_t) (MAX_ALLOC_CHUNK-SIZEOF(small_pool_hdr)))
    out_of_memory(cinfo, 1);	/* request exceeds malloc's ability */

  /* Round up the requested size to a multiple of SIZEOF(ALIGN_TYPE) */
  odd_bytes = sizeofobject % SIZEOF(ALIGN_TYPE);
  if (odd_bytes > 0)
    sizeofobject += SIZEOF(ALIGN_TYPE) - odd_bytes;

  /* See if space is available in any existing pool */
  if (pool_id < 0 || pool_id >= JPOOL_NUMPOOLS)
    ERREXIT1(cinfo, JERR_BAD_POOL_ID, pool_id);	/* safety check */
  prev_hdr_ptr = NULL;
  hdr_ptr = mem->small_list[pool_id];
  while (hdr_ptr != NULL) {
    if (hdr_ptr->hdr.bytes_left >= sizeofobject)
      break;			/* found pool with enough space */
    prev_hdr_ptr = hdr_ptr;
    hdr_ptr = hdr_ptr->hdr.next;
  }

  /* Time to make a new pool? */
  if (hdr_ptr == NULL) {
    /* min_request is what we need now, slop is what will be leftover */
    min_request = sizeofobject + SIZEOF(small_pool_hdr);
    if (prev_hdr_ptr == NULL)	/* first pool in class? */
      slop = first_pool_slop[pool_id];
    else
      slop = extra_pool_slop[pool_id];
    /* Don't ask for more than MAX_ALLOC_CHUNK */
    if (slop > (size_t) (MAX_ALLOC_CHUNK-min_request))
      slop = (size_t) (MAX_ALLOC_CHUNK-min_request);
    /* Try to get space, if fail reduce slop and try again */
    for (;;) {
      hdr_ptr = (small_pool_ptr) jpeg_get_small(cinfo, min_request + slop);
      if (hdr_ptr != NULL)
	break;
      slop /= 2;
      if (slop < MIN_SLOP)	/* give up when it gets real small */
	out_of_memory(cinfo, 2); /* jpeg_get_small failed */
    }
    mem->total_space_allocated += min_request + slop;
    /* Success, initialize the new pool header and add to end of list */
    hdr_ptr->hdr.next = NULL;
    hdr_ptr->hdr.bytes_used = 0;
    hdr_ptr->hdr.bytes_left = sizeofobject + slop;
    if (prev_hdr_ptr == NULL)	/* first pool in class? */
      mem->small_list[pool_id] = hdr_ptr;
    else
      prev_hdr_ptr->hdr.next = hdr_ptr;
  }

  /* OK, allocate the object from the current pool */
  data_ptr = (char *) (hdr_ptr + 1); /* point to first data byte in pool */
  data_ptr += hdr_ptr->hdr.bytes_used; /* point to place for object */
  hdr_ptr->hdr.bytes_used += sizeofobject;
  hdr_ptr->hdr.bytes_left -= sizeofobject;

  return (void *) data_ptr;
}


// @ 0x00863100
METHODDEF(JSAMPARRAY)
alloc_sarray (j_common_ptr cinfo, int pool_id,
	      JDIMENSION samplesperrow, JDIMENSION numrows)
/* Allocate a 2-D sample array */
{
  my_mem_ptr mem = (my_mem_ptr) cinfo->mem;
  JSAMPARRAY result;
  JSAMPROW workspace;
  JDIMENSION rowsperchunk, currow, i;
  long ltemp;

  /* Calculate max # of rows allowed in one allocation chunk */
  ltemp = (MAX_ALLOC_CHUNK-SIZEOF(large_pool_hdr)) /
	  ((long) samplesperrow * SIZEOF(JSAMPLE));
  if (ltemp <= 0)
    ERREXIT(cinfo, JERR_WIDTH_OVERFLOW);
  if (ltemp < (long) numrows)
    rowsperchunk = (JDIMENSION) ltemp;
  else
    rowsperchunk = numrows;
  mem->last_rowsperchunk = rowsperchunk;

  /* Get space for row pointers (small object) */
  result = (JSAMPARRAY) alloc_small(cinfo, pool_id,
				    (size_t) (numrows * SIZEOF(JSAMPROW)));

  /* Get the rows themselves (large objects) */
  currow = 0;
  while (currow < numrows) {
    rowsperchunk = MIN(rowsperchunk, numrows - currow);
    workspace = (JSAMPROW) alloc_large(cinfo, pool_id,
	(size_t) ((size_t) rowsperchunk * (size_t) samplesperrow
		  * SIZEOF(JSAMPLE)));
    for (i = rowsperchunk; i > 0; i--) {
      result[currow++] = workspace;
      workspace += samplesperrow;
    }
  }

  return result;
}


// @ 0x008631b0
METHODDEF(JBLOCKARRAY)
alloc_barray (j_common_ptr cinfo, int pool_id,
	      JDIMENSION blocksperrow, JDIMENSION numrows)
/* Allocate a 2-D coefficient-block array */
{
  my_mem_ptr mem = (my_mem_ptr) cinfo->mem;
  JBLOCKARRAY result;
  JBLOCKROW workspace;
  JDIMENSION rowsperchunk, currow, i;
  long ltemp;

  /* Calculate max # of rows allowed in one allocation chunk */
  ltemp = (MAX_ALLOC_CHUNK-SIZEOF(large_pool_hdr)) /
	  ((long) blocksperrow * SIZEOF(JBLOCK));
  if (ltemp <= 0)
    ERREXIT(cinfo, JERR_WIDTH_OVERFLOW);
  if (ltemp < (long) numrows)
    rowsperchunk = (JDIMENSION) ltemp;
  else
    rowsperchunk = numrows;
  mem->last_rowsperchunk = rowsperchunk;

  /* Get space for row pointers (small object) */
  result = (JBLOCKARRAY) alloc_small(cinfo, pool_id,
				     (size_t) (numrows * SIZEOF(JBLOCKROW)));

  /* Get the rows themselves (large objects) */
  currow = 0;
  while (currow < numrows) {
    rowsperchunk = MIN(rowsperchunk, numrows - currow);
    workspace = (JBLOCKROW) alloc_large(cinfo, pool_id,
	(size_t) ((size_t) rowsperchunk * (size_t) blocksperrow
		  * SIZEOF(JBLOCK)));
    for (i = rowsperchunk; i > 0; i--) {
      result[currow++] = workspace;
      workspace += blocksperrow;
    }
  }

  return result;
}

/* The three functions above are METHODDEF (static) in jmemmgr.c and are only
 * referenced from jinit_memory_mgr, which lives outside this slice.  This
 * table (not in the original) keeps their definitions emitted and stops cl
 * from inlining alloc_small into the two callers. */
void * const alloc_mgr_keepalive[] = {
  (void *) alloc_small,
  (void *) alloc_sarray,
  (void *) alloc_barray
};
