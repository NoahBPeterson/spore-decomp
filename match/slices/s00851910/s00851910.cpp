// Slice s00851910 - IJG libjpeg 6a:
//   jcdctmgr.c  : forward_DCT, forward_DCT_float, jinit_forward_dct
//   jchuff.c    : jpeg_make_c_derived_tbl, emit_bits, encode_one_block,
//                 emit_restart, encode_mcu_huff
//
// The retail image statically links IJG libjpeg 6a (string "6a  7-Feb-96"); the
// code below is the upstream 6a source, built with /O2 /arch:SSE /MD /Gy /TC
// /GS- /fp:fast.  jconfig.h next to this file is the project's jconfig.vc.
//
// jcdctmgr.c and jchuff.c were separate upstream translation units; their
// statics are reproduced here with the same TU-local linkage because cl 15.00
// passes parameters of static functions in registers, which the slice's call
// sites rely on.

#define JPEG_INTERNALS
#include "../../../work/third_party/src/jpeg-6a/jinclude.h"
#include "../../../work/third_party/src/jpeg-6a/jpeglib.h"
#include "../../../work/third_party/src/jpeg-6a/jdct.h"
#include "../../../work/third_party/src/jpeg-6a/jchuff.h"


/* ------------------------------------------------------------------ jcdctmgr.c -- */

/* Private subobject for this module */

typedef struct {
  struct jpeg_forward_dct pub;	/* public fields */

  /* Pointer to the DCT routine actually in use */
  forward_DCT_method_ptr do_dct;

  /* The actual post-DCT divisors --- not identical to the quant table
   * entries, because of scaling (especially for an unnormalized DCT).
   * Each table is given in normal array order.
   */
  DCTELEM * divisors[NUM_QUANT_TBLS];

#ifdef DCT_FLOAT_SUPPORTED
  /* Same as above for the floating-point case. */
  float_DCT_method_ptr do_float_dct;
  FAST_FLOAT * float_divisors[NUM_QUANT_TBLS];
#endif
} my_fdct_controller;

typedef my_fdct_controller * my_fdct_ptr;


/* Helper outside this slice (start_pass_fdctmgr is referenced by jinit_forward_dct
 * but lives in another VA range): upstream jcdctmgr.c body. */
METHODDEF(void)
start_pass_fdctmgr (j_compress_ptr cinfo)
{
  my_fdct_ptr fdct = (my_fdct_ptr) cinfo->fdct;
  int ci, qtblno, i;
  jpeg_component_info *compptr;
  JQUANT_TBL * qtbl;
  DCTELEM * dtbl;

  for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
       ci++, compptr++) {
    qtblno = compptr->quant_tbl_no;
    /* Make sure specified quantization table is present */
    if (qtblno < 0 || qtblno >= NUM_QUANT_TBLS ||
	cinfo->quant_tbl_ptrs[qtblno] == NULL)
      ERREXIT1(cinfo, JERR_NO_QUANT_TABLE, qtblno);
    qtbl = cinfo->quant_tbl_ptrs[qtblno];
    /* Compute divisors for this quant table */
    /* We may do this more than once for same table, but it's not a big deal */
    switch (cinfo->dct_method) {
#ifdef DCT_ISLOW_SUPPORTED
    case JDCT_ISLOW:
      /* For LL&M IDCT method, divisors are equal to raw quantization
       * coefficients multiplied by 8 (to counteract scaling).
       */
      if (fdct->divisors[qtblno] == NULL) {
	fdct->divisors[qtblno] = (DCTELEM *)
	  (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				      DCTSIZE2 * SIZEOF(DCTELEM));
      }
      dtbl = fdct->divisors[qtblno];
      for (i = 0; i < DCTSIZE2; i++) {
	dtbl[i] = ((DCTELEM) qtbl->quantval[i]) << 3;
      }
      break;
#endif
#ifdef DCT_IFAST_SUPPORTED
    case JDCT_IFAST:
      {
	/* For AA&N IDCT method, divisors are equal to quantization
	 * coefficients scaled by scalefactor[row]*scalefactor[col], where
	 *   scalefactor[0] = 1
	 *   scalefactor[k] = cos(k*PI/16) * sqrt(2)    for k=1..7
	 * We apply a further scale factor of 8.
	 */
#define CONST_BITS 14
	static const INT16 aanscales[DCTSIZE2] = {
	  /* precomputed values scaled up by 14 bits */
	  16384, 22725, 21407, 19266, 16384, 12873,  8867,  4520,
	  22725, 31521, 29692, 26722, 22725, 17855, 12299,  6270,
	  21407, 29692, 27969, 25172, 21407, 16819, 11585,  5906,
	  19266, 26722, 25172, 22654, 19266, 15137, 10426,  5315,
	  16384, 22725, 21407, 19266, 16384, 12873,  8867,  4520,
	  12873, 17855, 16819, 15137, 12873, 10114,  6967,  3552,
	   8867, 12299, 11585, 10426,  8867,  6967,  4799,  2446,
	   4520,  6270,  5906,  5315,  4520,  3552,  2446,  1247
	};
	SHIFT_TEMPS

	if (fdct->divisors[qtblno] == NULL) {
	  fdct->divisors[qtblno] = (DCTELEM *)
	    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
					DCTSIZE2 * SIZEOF(DCTELEM));
	}
	dtbl = fdct->divisors[qtblno];
	for (i = 0; i < DCTSIZE2; i++) {
	  dtbl[i] = (DCTELEM)
	    DESCALE(MULTIPLY16V16((INT32) qtbl->quantval[i],
				  (INT32) aanscales[i]),
		    CONST_BITS-3);
	}
      }
      break;
#endif
#ifdef DCT_FLOAT_SUPPORTED
    case JDCT_FLOAT:
      {
	/* For float AA&N IDCT method, divisors are equal to quantization
	 * coefficients scaled by scalefactor[row]*scalefactor[col], where
	 *   scalefactor[0] = 1
	 *   scalefactor[k] = cos(k*PI/16) * sqrt(2)    for k=1..7
	 * We apply a further scale factor of 8.
	 * What's actually stored is 1/divisor so that the inner loop can
	 * use a multiplication rather than a division.
	 */
	FAST_FLOAT * fdtbl;
	int row, col;
	static const double aanscalefactor[DCTSIZE] = {
	  1.0, 1.387039845, 1.306562965, 1.175875602,
	  1.0, 0.785694958, 0.541196100, 0.275899379
	};

	if (fdct->float_divisors[qtblno] == NULL) {
	  fdct->float_divisors[qtblno] = (FAST_FLOAT *)
	    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
					DCTSIZE2 * SIZEOF(FAST_FLOAT));
	}
	fdtbl = fdct->float_divisors[qtblno];
	i = 0;
	for (row = 0; row < DCTSIZE; row++) {
	  for (col = 0; col < DCTSIZE; col++) {
	    fdtbl[i] = (FAST_FLOAT)
	      (1.0 / (((double) qtbl->quantval[i] *
		       aanscalefactor[row] * aanscalefactor[col] * 8.0)));
	    i++;
	  }
	}
      }
      break;
#endif
    default:
      ERREXIT(cinfo, JERR_NOT_COMPILED);
      break;
    }
  }
}


/*
 * Perform forward DCT on one or more blocks of a component.
 *
 * The input samples are taken from the sample_data[] array starting at
 * position start_row/start_col, and moving to the right for any additional
 * blocks. The quantized coefficients are returned in coef_blocks[].
 */

// @ 0x00851910
METHODDEF(void)
forward_DCT (j_compress_ptr cinfo, jpeg_component_info * compptr,
	     JSAMPARRAY sample_data, JBLOCKROW coef_blocks,
	     JDIMENSION start_row, JDIMENSION start_col,
	     JDIMENSION num_blocks)
/* This version is used for integer DCT implementations. */
{
  /* This routine is heavily used, so it's worth coding it tightly. */
  my_fdct_ptr fdct = (my_fdct_ptr) cinfo->fdct;
  forward_DCT_method_ptr do_dct = fdct->do_dct;
  DCTELEM * divisors = fdct->divisors[compptr->quant_tbl_no];
  DCTELEM workspace[DCTSIZE2];	/* work area for FDCT subroutine */
  JDIMENSION bi;

  sample_data += start_row;	/* fold in the vertical offset once */

  for (bi = 0; bi < num_blocks; bi++, start_col += DCTSIZE) {
    /* Load data into workspace, applying unsigned->signed conversion */
    { register DCTELEM *workspaceptr;
      register JSAMPROW elemptr;
      register int elemr;

      workspaceptr = workspace;
      for (elemr = 0; elemr < DCTSIZE; elemr++) {
	elemptr = sample_data[elemr] + start_col;
#if DCTSIZE == 8		/* unroll the inner loop */
	*workspaceptr++ = GETJSAMPLE(*elemptr++) - CENTERJSAMPLE;
	*workspaceptr++ = GETJSAMPLE(*elemptr++) - CENTERJSAMPLE;
	*workspaceptr++ = GETJSAMPLE(*elemptr++) - CENTERJSAMPLE;
	*workspaceptr++ = GETJSAMPLE(*elemptr++) - CENTERJSAMPLE;
	*workspaceptr++ = GETJSAMPLE(*elemptr++) - CENTERJSAMPLE;
	*workspaceptr++ = GETJSAMPLE(*elemptr++) - CENTERJSAMPLE;
	*workspaceptr++ = GETJSAMPLE(*elemptr++) - CENTERJSAMPLE;
	*workspaceptr++ = GETJSAMPLE(*elemptr++) - CENTERJSAMPLE;
#else
	{ register int elemc;
	  for (elemc = DCTSIZE; elemc > 0; elemc--) {
	    *workspaceptr++ = GETJSAMPLE(*elemptr++) - CENTERJSAMPLE;
	  }
	}
#endif
      }
    }

    /* Perform the DCT */
    (*do_dct) (workspace);

    /* Quantize/descale the coefficients, and store into coef_blocks[] */
    { register DCTELEM temp, qval;
      register int i;
      register JCOEFPTR output_ptr = coef_blocks[bi];

      for (i = 0; i < DCTSIZE2; i++) {
	qval = divisors[i];
	temp = workspace[i];
	/* Divide the coefficient value by qval, ensuring proper rounding.
	 * Since C does not specify the direction of rounding for negative
	 * quotients, we have to force the dividend positive for portability.
	 *
	 * In most files, at least half of the output values will be zero
	 * (at default quantization settings, more like three-quarters...)
	 * so we should ensure that this case is fast.  On many machines,
	 * a comparison is enough cheaper than a divide to make a special test
	 * a win.  Since both inputs will be nonnegative, we need only test
	 * for a < b to discover whether a/b is 0.
	 * If your machine's division is fast enough, define FAST_DIVIDE.
	 */
#ifdef FAST_DIVIDE
#define DIVIDE_BY(a,b)	a /= b
#else
#define DIVIDE_BY(a,b)	if (a >= b) a /= b; else a = 0
#endif
	if (temp < 0) {
	  temp = -temp;
	  temp += qval>>1;	/* for rounding */
	  DIVIDE_BY(temp, qval);
	  temp = -temp;
	} else {
	  temp += qval>>1;	/* for rounding */
	  DIVIDE_BY(temp, qval);
	}
	output_ptr[i] = (JCOEF) temp;
      }
    }
  }
}


#ifdef DCT_FLOAT_SUPPORTED

// @ 0x00851c90
METHODDEF(void)
forward_DCT_float (j_compress_ptr cinfo, jpeg_component_info * compptr,
		   JSAMPARRAY sample_data, JBLOCKROW coef_blocks,
		   JDIMENSION start_row, JDIMENSION start_col,
		   JDIMENSION num_blocks)
/* This version is used for floating-point DCT implementations. */
{
  /* This routine is heavily used, so it's worth coding it tightly. */
  my_fdct_ptr fdct = (my_fdct_ptr) cinfo->fdct;
  float_DCT_method_ptr do_dct = fdct->do_float_dct;
  FAST_FLOAT * divisors = fdct->float_divisors[compptr->quant_tbl_no];
  FAST_FLOAT workspace[DCTSIZE2]; /* work area for FDCT subroutine */
  JDIMENSION bi;

  sample_data += start_row;	/* fold in the vertical offset once */

  for (bi = 0; bi < num_blocks; bi++, start_col += DCTSIZE) {
    /* Load data into workspace, applying unsigned->signed conversion */
    { register FAST_FLOAT *workspaceptr;
      register JSAMPROW elemptr;
      register int elemr;

      workspaceptr = workspace;
      for (elemr = 0; elemr < DCTSIZE; elemr++) {
	elemptr = sample_data[elemr] + start_col;
#if DCTSIZE == 8		/* unroll the inner loop */
	*workspaceptr++ = (FAST_FLOAT)(GETJSAMPLE(*elemptr++) - CENTERJSAMPLE);
	*workspaceptr++ = (FAST_FLOAT)(GETJSAMPLE(*elemptr++) - CENTERJSAMPLE);
	*workspaceptr++ = (FAST_FLOAT)(GETJSAMPLE(*elemptr++) - CENTERJSAMPLE);
	*workspaceptr++ = (FAST_FLOAT)(GETJSAMPLE(*elemptr++) - CENTERJSAMPLE);
	*workspaceptr++ = (FAST_FLOAT)(GETJSAMPLE(*elemptr++) - CENTERJSAMPLE);
	*workspaceptr++ = (FAST_FLOAT)(GETJSAMPLE(*elemptr++) - CENTERJSAMPLE);
	*workspaceptr++ = (FAST_FLOAT)(GETJSAMPLE(*elemptr++) - CENTERJSAMPLE);
	*workspaceptr++ = (FAST_FLOAT)(GETJSAMPLE(*elemptr++) - CENTERJSAMPLE);
#else
	{ register int elemc;
	  for (elemc = DCTSIZE; elemc > 0; elemc--) {
	    *workspaceptr++ = (FAST_FLOAT)
	      (GETJSAMPLE(*elemptr++) - CENTERJSAMPLE);
	  }
	}
#endif
      }
    }

    /* Perform the DCT */
    (*do_dct) (workspace);

    /* Quantize/descale the coefficients, and store into coef_blocks[] */
    { register FAST_FLOAT temp;
      register int i;
      register JCOEFPTR output_ptr = coef_blocks[bi];

      for (i = 0; i < DCTSIZE2; i++) {
	/* Apply the quantization and scaling factor */
	temp = workspace[i] * divisors[i];
	/* Round to nearest integer.
	 * Since C does not specify the direction of rounding for negative
	 * quotients, we have to force the dividend positive for portability.
	 * The maximum coefficient size is +-16K (for 12-bit data), so this
	 * code should work for either 16-bit or 32-bit ints.
	 */
	output_ptr[i] = (JCOEF) ((int) (temp + (FAST_FLOAT) 16384.5) - 16384);
      }
    }
  }
}

#endif /* DCT_FLOAT_SUPPORTED */


/*
 * Initialize FDCT manager.
 */

// @ 0x00852260
GLOBAL(void)
jinit_forward_dct (j_compress_ptr cinfo)
{
  my_fdct_ptr fdct;
  int i;

  fdct = (my_fdct_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				SIZEOF(my_fdct_controller));
  cinfo->fdct = (struct jpeg_forward_dct *) fdct;
  fdct->pub.start_pass = start_pass_fdctmgr;

  switch (cinfo->dct_method) {
#ifdef DCT_ISLOW_SUPPORTED
  case JDCT_ISLOW:
    fdct->pub.forward_DCT = forward_DCT;
    fdct->do_dct = jpeg_fdct_islow;
    break;
#endif
#ifdef DCT_IFAST_SUPPORTED
  case JDCT_IFAST:
    fdct->pub.forward_DCT = forward_DCT;
    fdct->do_dct = jpeg_fdct_ifast;
    break;
#endif
#ifdef DCT_FLOAT_SUPPORTED
  case JDCT_FLOAT:
    fdct->pub.forward_DCT = forward_DCT_float;
    fdct->do_float_dct = jpeg_fdct_float;
    break;
#endif
  default:
    ERREXIT(cinfo, JERR_NOT_COMPILED);
    break;
  }

  /* Mark divisor tables unallocated */
  for (i = 0; i < NUM_QUANT_TBLS; i++) {
    fdct->divisors[i] = NULL;
#ifdef DCT_FLOAT_SUPPORTED
    fdct->float_divisors[i] = NULL;
#endif
  }
}


/* -------------------------------------------------------------------- jchuff.c -- */

/* Expanded entropy encoder object for Huffman encoding.
 *
 * The savable_state subrecord contains fields that change within an MCU,
 * but must not be updated permanently until we complete the MCU.
 */

typedef struct {
  INT32 put_buffer;		/* current bit-accumulation buffer */
  int put_bits;			/* # of bits now in it */
  int last_dc_val[MAX_COMPS_IN_SCAN]; /* last DC coef for each component */
} savable_state;

/* This macro is to work around compilers with missing or broken
 * structure assignment.  You'll need to fix this code if you have
 * such a compiler and you change MAX_COMPS_IN_SCAN.
 */

#ifndef NO_STRUCT_ASSIGN
#define ASSIGN_STATE(dest,src)  ((dest) = (src))
#else
#if MAX_COMPS_IN_SCAN == 4
#define ASSIGN_STATE(dest,src)  \
	((dest).put_buffer = (src).put_buffer, \
	 (dest).put_bits = (src).put_bits, \
	 (dest).last_dc_val[0] = (src).last_dc_val[0], \
	 (dest).last_dc_val[1] = (src).last_dc_val[1], \
	 (dest).last_dc_val[2] = (src).last_dc_val[2], \
	 (dest).last_dc_val[3] = (src).last_dc_val[3])
#endif
#endif


typedef struct {
  struct jpeg_entropy_encoder pub; /* public fields */

  savable_state saved;		/* Bit buffer & DC state at start of MCU */

  /* These fields are NOT loaded into local working state. */
  unsigned int restarts_to_go;	/* MCUs left in this restart interval */
  int next_restart_num;		/* next restart number to write (0-7) */

  /* Pointers to derived tables (these workspaces have image lifespan) */
  c_derived_tbl * dc_derived_tbls[NUM_HUFF_TBLS];
  c_derived_tbl * ac_derived_tbls[NUM_HUFF_TBLS];

#ifdef ENTROPY_OPT_SUPPORTED	/* Statistics tables for optimization */
  long * dc_count_ptrs[NUM_HUFF_TBLS];
  long * ac_count_ptrs[NUM_HUFF_TBLS];
#endif
} huff_entropy_encoder;

typedef huff_entropy_encoder * huff_entropy_ptr;

/* Working state while writing an MCU.
 * This struct contains all the fields that are needed by subroutines.
 */

typedef struct {
  JOCTET * next_output_byte;	/* => next byte to write in buffer */
  size_t free_in_buffer;	/* # of byte spaces remaining in buffer */
  savable_state cur;		/* Current bit buffer & DC state */
  j_compress_ptr cinfo;		/* dump_buffer needs access to this */
} working_state;


/*
 * Compute the derived values for a Huffman table.
 * Note this is also used by jcphuff.c.
 */

// @ 0x00852300
GLOBAL(void)
jpeg_make_c_derived_tbl (j_compress_ptr cinfo, JHUFF_TBL * htbl,
			 c_derived_tbl ** pdtbl)
{
  c_derived_tbl *dtbl;
  int p, i, l, lastp, si;
  char huffsize[257];
  unsigned int huffcode[257];
  unsigned int code;

  /* Allocate a workspace if we haven't already done so. */
  if (*pdtbl == NULL)
    *pdtbl = (c_derived_tbl *)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  SIZEOF(c_derived_tbl));
  dtbl = *pdtbl;
  
  /* Figure C.1: make table of Huffman code length for each symbol */
  /* Note that this is in code-length order. */

  p = 0;
  for (l = 1; l <= 16; l++) {
    for (i = 1; i <= (int) htbl->bits[l]; i++)
      huffsize[p++] = (char) l;
  }
  huffsize[p] = 0;
  lastp = p;
  
  /* Figure C.2: generate the codes themselves */
  /* Note that this is in code-length order. */
  
  code = 0;
  si = huffsize[0];
  p = 0;
  while (huffsize[p]) {
    while (((int) huffsize[p]) == si) {
      huffcode[p++] = code;
      code++;
    }
    code <<= 1;
    si++;
  }
  
  /* Figure C.3: generate encoding tables */
  /* These are code and size indexed by symbol value */

  /* Set any codeless symbols to have code length 0;
   * this allows emit_bits to detect any attempt to emit such symbols.
   */
  MEMZERO(dtbl->ehufsi, SIZEOF(dtbl->ehufsi));

  for (p = 0; p < lastp; p++) {
    dtbl->ehufco[htbl->huffval[p]] = huffcode[p];
    dtbl->ehufsi[htbl->huffval[p]] = huffsize[p];
  }
}


/* Outputting bytes to the file */

/* Emit a byte, taking 'action' if must suspend. */
#define emit_byte(state,val,action)  \
	{ *(state)->next_output_byte++ = (JOCTET) (val);  \
	  if (--(state)->free_in_buffer == 0)  \
	    if (! dump_buffer(state))  \
	      { action; } }

LOCAL(boolean)
dump_buffer (working_state * state)
/* Empty the output buffer; return TRUE if successful, FALSE if must suspend */
{
  struct jpeg_destination_mgr * dest = state->cinfo->dest;

  if (! (*dest->empty_output_buffer) (state->cinfo))
    return FALSE;
  /* After a successful buffer dump, must reset buffer pointers */
  state->next_output_byte = dest->next_output_byte;
  state->free_in_buffer = dest->free_in_buffer;
  return TRUE;
}


/* Outputting bits to the file */

/* Only the right 24 bits of put_buffer are used; the valid bits are
 * left-justified in this part.  At most 16 bits can be passed to emit_bits
 * in one call, and we never retain more than 7 bits in put_buffer
 * between calls, so 24 bits are sufficient.
 */

// @ 0x00852400
INLINE
LOCAL(boolean)
emit_bits (working_state * state, unsigned int code, int size)
/* Emit some bits; return TRUE if successful, FALSE if must suspend */
{
  /* This routine is heavily used, so it's worth coding tightly. */
  register INT32 put_buffer = (INT32) code;
  register int put_bits = state->cur.put_bits;

  /* if size is 0, caller used an invalid Huffman table entry */
  if (size == 0)
    ERREXIT(state->cinfo, JERR_HUFF_MISSING_CODE);

  put_buffer &= (((INT32) 1)<<size) - 1; /* mask off any extra bits in code */
  
  put_bits += size;		/* new number of bits in buffer */
  
  put_buffer <<= 24 - put_bits; /* align incoming bits */

  put_buffer |= state->cur.put_buffer; /* and merge with old buffer contents */
  
  while (put_bits >= 8) {
    int c = (int) ((put_buffer >> 16) & 0xFF);
    
    emit_byte(state, c, return FALSE);
    if (c == 0xFF) {		/* need to stuff a zero byte? */
      emit_byte(state, 0, return FALSE);
    }
    put_buffer <<= 8;
    put_bits -= 8;
  }

  state->cur.put_buffer = put_buffer; /* update state variables */
  state->cur.put_bits = put_bits;

  return TRUE;
}


LOCAL(boolean)
flush_bits (working_state * state)
{
  if (! emit_bits(state, 0x7F, 7)) /* fill any partial byte with ones */
    return FALSE;
  state->cur.put_buffer = 0;	/* and reset bit-buffer to empty */
  state->cur.put_bits = 0;
  return TRUE;
}


/* Encode a single block's worth of coefficients */

// @ 0x008524f0
LOCAL(boolean)
encode_one_block (working_state * state, JCOEFPTR block, int last_dc_val,
		  c_derived_tbl *dctbl, c_derived_tbl *actbl)
{
  register int temp, temp2;
  register int nbits;
  register int k, r, i;
  
  /* Encode the DC coefficient difference per section F.1.2.1 */
  
  temp = temp2 = block[0] - last_dc_val;

  if (temp < 0) {
    temp = -temp;		/* temp is abs value of input */
    /* For a negative input, want temp2 = bitwise complement of abs(input) */
    /* This code assumes we are on a two's complement machine */
    temp2--;
  }
  
  /* Find the number of bits needed for the magnitude of the coefficient */
  nbits = 0;
  while (temp) {
    nbits++;
    temp >>= 1;
  }
  
  /* Emit the Huffman-coded symbol for the number of bits */
  if (! emit_bits(state, dctbl->ehufco[nbits], dctbl->ehufsi[nbits]))
    return FALSE;

  /* Emit that number of bits of the value, if positive, */
  /* or the complement of its magnitude, if negative. */
  if (nbits)			/* emit_bits rejects calls with size 0 */
    if (! emit_bits(state, (unsigned int) temp2, nbits))
      return FALSE;

  /* Encode the AC coefficients per section F.1.2.2 */
  
  r = 0;			/* r = run length of zeros */
  
  for (k = 1; k < DCTSIZE2; k++) {
    if ((temp = block[jpeg_natural_order[k]]) == 0) {
      r++;
    } else {
      /* if run length > 15, must emit special run-length-16 codes (0xF0) */
      while (r > 15) {
	if (! emit_bits(state, actbl->ehufco[0xF0], actbl->ehufsi[0xF0]))
	  return FALSE;
	r -= 16;
      }

      temp2 = temp;
      if (temp < 0) {
	temp = -temp;		/* temp is abs value of input */
	/* This code assumes we are on a two's complement machine */
	temp2--;
      }
      
      /* Find the number of bits needed for the magnitude of the coefficient */
      nbits = 1;		/* there must be at least one 1 bit */
      while ((temp >>= 1))
	nbits++;
      
      /* Emit Huffman symbol for run length / number of bits */
      i = (r << 4) + nbits;
      if (! emit_bits(state, actbl->ehufco[i], actbl->ehufsi[i]))
	return FALSE;

      /* Emit that number of bits of the value, if positive, */
      /* or the complement of its magnitude, if negative. */
      if (! emit_bits(state, (unsigned int) temp2, nbits))
	return FALSE;
      
      r = 0;
    }
  }

  /* If the last coef(s) were zero, emit an end-of-block code */
  if (r > 0)
    if (! emit_bits(state, actbl->ehufco[0], actbl->ehufsi[0]))
      return FALSE;

  return TRUE;
}


/*
 * Emit a restart marker & resynchronize predictions.
 */

// @ 0x00852640
LOCAL(boolean)
emit_restart (working_state * state, int restart_num)
{
  int ci;

  if (! flush_bits(state))
    return FALSE;

  emit_byte(state, 0xFF, return FALSE);
  emit_byte(state, JPEG_RST0 + restart_num, return FALSE);

  /* Re-initialize DC predictions to 0 */
  for (ci = 0; ci < state->cinfo->comps_in_scan; ci++)
    state->cur.last_dc_val[ci] = 0;

  /* The restart counter is not updated until we successfully write the MCU. */

  return TRUE;
}


/*
 * Encode and output one MCU's worth of Huffman-compressed coefficients.
 */

// @ 0x00852700
METHODDEF(boolean)
encode_mcu_huff (j_compress_ptr cinfo, JBLOCKROW *MCU_data)
{
  huff_entropy_ptr entropy = (huff_entropy_ptr) cinfo->entropy;
  working_state state;
  int blkn, ci;
  jpeg_component_info * compptr;

  /* Load up working state */
  state.next_output_byte = cinfo->dest->next_output_byte;
  state.free_in_buffer = cinfo->dest->free_in_buffer;
  ASSIGN_STATE(state.cur, entropy->saved);
  state.cinfo = cinfo;

  /* Emit restart marker if needed */
  if (cinfo->restart_interval) {
    if (entropy->restarts_to_go == 0)
      if (! emit_restart(&state, entropy->next_restart_num))
	return FALSE;
  }

  /* Encode the MCU data blocks */
  for (blkn = 0; blkn < cinfo->blocks_in_MCU; blkn++) {
    ci = cinfo->MCU_membership[blkn];
    compptr = cinfo->cur_comp_info[ci];
    if (! encode_one_block(&state,
			   MCU_data[blkn][0], state.cur.last_dc_val[ci],
			   entropy->dc_derived_tbls[compptr->dc_tbl_no],
			   entropy->ac_derived_tbls[compptr->ac_tbl_no]))
      return FALSE;
    /* Update last_dc_val */
    state.cur.last_dc_val[ci] = MCU_data[blkn][0][0];
  }

  /* Completed MCU, so update state */
  cinfo->dest->next_output_byte = state.next_output_byte;
  cinfo->dest->free_in_buffer = state.free_in_buffer;
  ASSIGN_STATE(entropy->saved, state.cur);

  /* Update restart-interval state too */
  if (cinfo->restart_interval) {
    if (entropy->restarts_to_go == 0) {
      entropy->restarts_to_go = cinfo->restart_interval;
      entropy->next_restart_num++;
      entropy->next_restart_num &= 7;
    }
    entropy->restarts_to_go--;
  }

  return TRUE;
}


/* Retain the TU-local encoder chain (upstream jchuff.c's jinit_huff_encoder stores
 * this address; without that helper cl would discard the unreferenced statics). */
void (* const volatile s00851910_keep_encode_mcu) (j_compress_ptr, JBLOCKROW *) =
  encode_mcu_huff;
