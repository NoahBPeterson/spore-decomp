// Slice s008561e0 - IJG libjpeg 6a: jcphuff.c (progressive Huffman entropy encoder),
// jcprepct.c (compression preprocessing controller) and jcsample.c (downsampler).
//
// The retail image statically links IJG libjpeg 6a (string "6a  7-Feb-96"); the code below
// is the upstream 6a source, built with the library flags /O2 /arch:SSE /MD /Gy /TC.
// jconfig.h next to this file is the project's jconfig.vc (third_party/jpeg-6a/jconfig.h).
//
// The static helpers of jcphuff.c/jcprepct.c/jcsample.c are reproduced here because cl 15.00
// passes the parameters of TU-local statics in registers (codegen.md 6.3): the call sites in
// the slice's functions only come out right when the callee bodies are visible in this TU.

#define JPEG_INTERNALS
#define CONTEXT_ROWS_SUPPORTED
#include "../../../work/third_party/src/jpeg-6a/jinclude.h"
#include "../../../work/third_party/src/jpeg-6a/jpeglib.h"
#include "../../../work/third_party/src/jpeg-6a/jchuff.h"


/* ------------------------------------------------------------------ jcphuff.c -- */

/* Expanded entropy encoder object for progressive Huffman encoding. */

typedef struct {
  struct jpeg_entropy_encoder pub; /* public fields */

  /* Mode flag: TRUE for optimization, FALSE for actual data output */
  boolean gather_statistics;

  /* Bit-level coding status.
   * next_output_byte/free_in_buffer are local copies of cinfo->dest fields.
   */
  JOCTET * next_output_byte;	/* => next byte to write in buffer */
  size_t free_in_buffer;	/* # of byte spaces remaining in buffer */
  INT32 put_buffer;		/* current bit-accumulation buffer */
  int put_bits;			/* # of bits now in it */
  j_compress_ptr cinfo;		/* link to cinfo (needed for dump_buffer) */

  /* Coding status for DC components */
  int last_dc_val[MAX_COMPS_IN_SCAN]; /* last DC coef for each component */

  /* Coding status for AC components */
  int ac_tbl_no;		/* the table number of the single component */
  unsigned int EOBRUN;		/* run length of EOBs */
  unsigned int BE;		/* # of buffered correction bits before MCU */
  char * bit_buffer;		/* buffer for correction bits (1 per char) */

  unsigned int restarts_to_go;	/* MCUs left in this restart interval */
  int next_restart_num;		/* next restart number to write (0-7) */

  /* Pointers to derived tables (these workspaces have image lifespan).
   * Since any one scan codes only DC or only AC, we only need one set
   * of tables, not one for DC and one for AC.
   */
  c_derived_tbl * derived_tbls[NUM_HUFF_TBLS];

  /* Statistics tables for optimization; again, one set is enough */
  long * count_ptrs[NUM_HUFF_TBLS];
} phuff_entropy_encoder;

typedef phuff_entropy_encoder * phuff_entropy_ptr;

#define MAX_CORR_BITS  1000	/* Max # of correction bits I can buffer */

/* The other progressive MCU encoders and finish_pass_phuff live in the same retail object
 * (real VAs) and are only stored as function pointers here. */
/* 0x00855e00 */ boolean encode_mcu_DC_first (j_compress_ptr cinfo, JBLOCKROW *MCU_data);
/* 0x00855f50 */ boolean encode_mcu_AC_first (j_compress_ptr cinfo, JBLOCKROW *MCU_data);
/* 0x00856120 */ boolean encode_mcu_DC_refine (j_compress_ptr cinfo, JBLOCKROW *MCU_data);
/* 0x00856450 */ void finish_pass_phuff (j_compress_ptr cinfo);


/* Emit a byte */
#define emit_byte(entropy,val)  \
	{ *(entropy)->next_output_byte++ = (JOCTET) (val);  \
	  if (--(entropy)->free_in_buffer == 0)  \
	    dump_buffer(entropy); }

static void dump_buffer (phuff_entropy_ptr entropy)
/* Empty the output buffer; we do not support suspension in this module. */
{
  struct jpeg_destination_mgr * dest = entropy->cinfo->dest;

  if (! (*dest->empty_output_buffer) (entropy->cinfo))
    ERREXIT(entropy->cinfo, JERR_CANT_SUSPEND);
  /* After a successful buffer dump, must reset buffer pointers */
  entropy->next_output_byte = dest->next_output_byte;
  entropy->free_in_buffer = dest->free_in_buffer;
}


static void emit_bits (phuff_entropy_ptr entropy, unsigned int code, int size)
/* Emit some bits, unless we are in gather mode */
{
  /* This routine is heavily used, so it's worth coding tightly. */
  register INT32 put_buffer = (INT32) code;
  register int put_bits = entropy->put_bits;

  /* if size is 0, caller used an invalid Huffman table entry */
  if (size == 0)
    ERREXIT(entropy->cinfo, JERR_HUFF_MISSING_CODE);

  if (entropy->gather_statistics)
    return;			/* do nothing if we're only getting stats */

  put_buffer &= (((INT32) 1)<<size) - 1; /* mask off any extra bits in code */

  put_bits += size;		/* new number of bits in buffer */

  put_buffer <<= 24 - put_bits; /* align incoming bits */

  put_buffer |= entropy->put_buffer; /* and merge with old buffer contents */

  while (put_bits >= 8) {
    int c = (int) ((put_buffer >> 16) & 0xFF);

    emit_byte(entropy, c);
    if (c == 0xFF) {		/* need to stuff a zero byte? */
      emit_byte(entropy, 0);
    }
    put_buffer <<= 8;
    put_bits -= 8;
  }

  entropy->put_buffer = put_buffer; /* update variables */
  entropy->put_bits = put_bits;
}


static void flush_bits (phuff_entropy_ptr entropy)
{
  emit_bits(entropy, 0x7F, 7); /* fill any partial byte with ones */
  entropy->put_buffer = 0;     /* and reset bit-buffer to empty */
  entropy->put_bits = 0;
}


/*
 * Emit (or just count) a Huffman symbol.
 */

static void emit_symbol (phuff_entropy_ptr entropy, int tbl_no, int symbol)
{
  if (entropy->gather_statistics)
    entropy->count_ptrs[tbl_no][symbol]++;
  else {
    c_derived_tbl * tbl = entropy->derived_tbls[tbl_no];
    emit_bits(entropy, tbl->ehufco[symbol], tbl->ehufsi[symbol]);
  }
}


/*
 * Emit bits from a correction bit buffer.
 */

static void emit_buffered_bits (phuff_entropy_ptr entropy, char * bufstart,
				unsigned int nbits)
{
  if (entropy->gather_statistics)
    return;			/* no real work */

  while (nbits > 0) {
    emit_bits(entropy, (unsigned int) (*bufstart), 1);
    bufstart++;
    nbits--;
  }
}


/*
 * Emit any pending EOBRUN symbol.
 */

static void emit_eobrun (phuff_entropy_ptr entropy)
{
  register int temp, nbits;

  if (entropy->EOBRUN > 0) {	/* if there is any pending EOBRUN */
    temp = entropy->EOBRUN;
    nbits = 0;
    while ((temp >>= 1))
      nbits++;

    emit_symbol(entropy, entropy->ac_tbl_no, nbits << 4);
    if (nbits)
      emit_bits(entropy, entropy->EOBRUN, nbits);

    entropy->EOBRUN = 0;

    /* Emit any buffered correction bits */
    emit_buffered_bits(entropy, entropy->bit_buffer, entropy->BE);
    entropy->BE = 0;
  }
}


/*
 * Emit a restart marker & resynchronize predictions.
 */

static void emit_restart (phuff_entropy_ptr entropy, int restart_num)
{
  int ci;

  emit_eobrun(entropy);

  if (! entropy->gather_statistics) {
    flush_bits(entropy);
    emit_byte(entropy, 0xFF);
    emit_byte(entropy, JPEG_RST0 + restart_num);
  }

  if (entropy->cinfo->Ss == 0) {
    /* Re-initialize DC predictions to 0 */
    for (ci = 0; ci < entropy->cinfo->comps_in_scan; ci++)
      entropy->last_dc_val[ci] = 0;
  } else {
    /* Re-initialize all AC-related fields to 0 */
    entropy->EOBRUN = 0;
    entropy->BE = 0;
  }
}


// ---------------------------------------------------------------------------
// @ 0x008561e0
/*
 * MCU encoding for AC successive approximation refinement scan.
 */

static boolean
encode_mcu_AC_refine (j_compress_ptr cinfo, JBLOCKROW *MCU_data)
{
  phuff_entropy_ptr entropy = (phuff_entropy_ptr) cinfo->entropy;
  register int temp;
  register int r, k;
  int EOB;
  char *BR_buffer;
  unsigned int BR;
  int Se = cinfo->Se;
  int Al = cinfo->Al;
  JBLOCKROW block;
  int absvalues[DCTSIZE2];

  entropy->next_output_byte = cinfo->dest->next_output_byte;
  entropy->free_in_buffer = cinfo->dest->free_in_buffer;

  /* Emit restart marker if needed */
  if (cinfo->restart_interval)
    if (entropy->restarts_to_go == 0)
      emit_restart(entropy, entropy->next_restart_num);

  /* Encode the MCU data block */
  block = MCU_data[0];

  /* It is convenient to make a pre-pass to determine the transformed
   * coefficients' absolute values and the EOB position.
   */
  EOB = 0;
  for (k = cinfo->Ss; k <= Se; k++) {
    temp = (*block)[jpeg_natural_order[k]];
    /* We must apply the point transform by Al.  For AC coefficients this
     * is an integer division with rounding towards 0.  To do this portably
     * in C, we shift after obtaining the absolute value.
     */
    if (temp < 0)
      temp = -temp;		/* temp is abs value of input */
    temp >>= Al;		/* apply the point transform */
    absvalues[k] = temp;	/* save abs value for main pass */
    if (temp == 1)
      EOB = k;			/* EOB = index of last newly-nonzero coef */
  }

  /* Encode the AC coefficients per section G.1.2.3, fig. G.7 */

  r = 0;			/* r = run length of zeros */
  BR = 0;			/* BR = count of buffered bits added now */
  BR_buffer = entropy->bit_buffer + entropy->BE; /* Append bits to buffer */

  for (k = cinfo->Ss; k <= Se; k++) {
    if ((temp = absvalues[k]) == 0) {
      r++;
      continue;
    }

    /* Emit any required ZRLs, but not if they can be folded into EOB */
    while (r > 15 && k <= EOB) {
      /* emit any pending EOBRUN and the BE correction bits */
      emit_eobrun(entropy);
      /* Emit ZRL */
      emit_symbol(entropy, entropy->ac_tbl_no, 0xF0);
      r -= 16;
      /* Emit buffered correction bits that must be associated with ZRL */
      emit_buffered_bits(entropy, BR_buffer, BR);
      BR_buffer = entropy->bit_buffer; /* BE bits are gone now */
      BR = 0;
    }

    /* If the coef was previously nonzero, it only needs a correction bit.
     * NOTE: a straight translation of the spec's figure G.7 would suggest
     * that we also need to test r > 15.  But if r > 15, we can only get here
     * if k > EOB, which implies that this coefficient is not 1.
     */
    if (temp > 1) {
      /* The correction bit is the next bit of the absolute value. */
      BR_buffer[BR++] = (char) (temp & 1);
      continue;
    }

    /* Emit any pending EOBRUN and the BE correction bits */
    emit_eobrun(entropy);

    /* Count/emit Huffman symbol for run length / number of bits */
    emit_symbol(entropy, entropy->ac_tbl_no, (r << 4) + 1);

    /* Emit output bit for newly-nonzero coef */
    temp = ((*block)[jpeg_natural_order[k]] < 0) ? 0 : 1;
    emit_bits(entropy, (unsigned int) temp, 1);

    /* Emit buffered correction bits that must be associated with this code */
    emit_buffered_bits(entropy, BR_buffer, BR);
    BR_buffer = entropy->bit_buffer; /* BE bits are gone now */
    BR = 0;
    r = 0;			/* reset zero run length */
  }

  if (r > 0 || BR > 0) {	/* If there are trailing zeroes, */
    entropy->EOBRUN++;		/* count an EOB */
    entropy->BE += BR;		/* concat my correction bits to older ones */
    /* We force out the EOB if we risk either:
     * 1. overflow of the EOB counter;
     * 2. overflow of the correction bit buffer during the next MCU.
     */
    if (entropy->EOBRUN == 0x7FFF || entropy->BE > (MAX_CORR_BITS-DCTSIZE2+1))
      emit_eobrun(entropy);
  }

  cinfo->dest->next_output_byte = entropy->next_output_byte;
  cinfo->dest->free_in_buffer = entropy->free_in_buffer;

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


// ---------------------------------------------------------------------------
// @ 0x008564a0
/*
 * Finish up a statistics-gathering pass and create the new Huffman tables.
 */

static void
finish_pass_gather_phuff (j_compress_ptr cinfo)
{
  phuff_entropy_ptr entropy = (phuff_entropy_ptr) cinfo->entropy;
  boolean is_DC_band;
  int ci, tbl;
  jpeg_component_info * compptr;
  JHUFF_TBL **htblptr;
  boolean did[NUM_HUFF_TBLS];

  /* Flush out buffered data (all we care about is counting the EOB symbol) */
  emit_eobrun(entropy);

  is_DC_band = (cinfo->Ss == 0);

  /* It's important not to apply jpeg_gen_optimal_table more than once
   * per table, because it clobbers the input frequency counts!
   */
  MEMZERO(did, SIZEOF(did));

  for (ci = 0; ci < cinfo->comps_in_scan; ci++) {
    compptr = cinfo->cur_comp_info[ci];
    if (is_DC_band) {
      if (cinfo->Ah != 0)	/* DC refinement needs no table */
	continue;
      tbl = compptr->dc_tbl_no;
    } else {
      tbl = compptr->ac_tbl_no;
    }
    if (! did[tbl]) {
      if (is_DC_band)
        htblptr = & cinfo->dc_huff_tbl_ptrs[tbl];
      else
        htblptr = & cinfo->ac_huff_tbl_ptrs[tbl];
      if (*htblptr == NULL)
        *htblptr = jpeg_alloc_huff_table((j_common_ptr) cinfo);
      jpeg_gen_optimal_table(cinfo, *htblptr, entropy->count_ptrs[tbl]);
      did[tbl] = TRUE;
    }
  }
}


// ---------------------------------------------------------------------------
// @ 0x00856580
/*
 * Initialize for a Huffman-compressed scan using progressive JPEG.
 */

static void
start_pass_phuff (j_compress_ptr cinfo, boolean gather_statistics)
{
  phuff_entropy_ptr entropy = (phuff_entropy_ptr) cinfo->entropy;
  boolean is_DC_band;
  int ci, tbl;
  jpeg_component_info * compptr;

  entropy->cinfo = cinfo;
  entropy->gather_statistics = gather_statistics;

  is_DC_band = (cinfo->Ss == 0);

  /* We assume jcmaster.c already validated the scan parameters. */

  /* Select execution routines */
  if (cinfo->Ah == 0) {
    if (is_DC_band)
      entropy->pub.encode_mcu = encode_mcu_DC_first;
    else
      entropy->pub.encode_mcu = encode_mcu_AC_first;
  } else {
    if (is_DC_band)
      entropy->pub.encode_mcu = encode_mcu_DC_refine;
    else {
      entropy->pub.encode_mcu = encode_mcu_AC_refine;
      /* AC refinement needs a correction bit buffer */
      if (entropy->bit_buffer == NULL)
	entropy->bit_buffer = (char *)
	  (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				      MAX_CORR_BITS * SIZEOF(char));
    }
  }
  if (gather_statistics)
    entropy->pub.finish_pass = finish_pass_gather_phuff;
  else
    entropy->pub.finish_pass = finish_pass_phuff;

  /* Only DC coefficients may be interleaved, so cinfo->comps_in_scan = 1
   * for AC coefficients.
   */
  for (ci = 0; ci < cinfo->comps_in_scan; ci++) {
    compptr = cinfo->cur_comp_info[ci];
    /* Initialize DC predictions to 0 */
    entropy->last_dc_val[ci] = 0;
    /* Make sure requested tables are present */
    /* (In gather mode, tables need not be allocated yet) */
    if (is_DC_band) {
      if (cinfo->Ah != 0)	/* DC refinement needs no table */
	continue;
      tbl = compptr->dc_tbl_no;
      if (tbl < 0 || tbl >= NUM_HUFF_TBLS ||
	  (cinfo->dc_huff_tbl_ptrs[tbl] == NULL && !gather_statistics))
	ERREXIT1(cinfo,JERR_NO_HUFF_TABLE, tbl);
    } else {
      entropy->ac_tbl_no = tbl = compptr->ac_tbl_no;
      if (tbl < 0 || tbl >= NUM_HUFF_TBLS ||
          (cinfo->ac_huff_tbl_ptrs[tbl] == NULL && !gather_statistics))
        ERREXIT1(cinfo,JERR_NO_HUFF_TABLE, tbl);
    }
    if (gather_statistics) {
      /* Allocate and zero the statistics tables */
      /* Note that jpeg_gen_optimal_table expects 257 entries in each table! */
      if (entropy->count_ptrs[tbl] == NULL)
	entropy->count_ptrs[tbl] = (long *)
	  (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				      257 * SIZEOF(long));
      MEMZERO(entropy->count_ptrs[tbl], 257 * SIZEOF(long));
    } else {
      /* Compute derived values for Huffman tables */
      /* We may do this more than once for a table, but it's not expensive */
      if (is_DC_band)
        jpeg_make_c_derived_tbl(cinfo, cinfo->dc_huff_tbl_ptrs[tbl],
				& entropy->derived_tbls[tbl]);
      else
        jpeg_make_c_derived_tbl(cinfo, cinfo->ac_huff_tbl_ptrs[tbl],
				& entropy->derived_tbls[tbl]);
    }
  }

  /* Initialize AC stuff */
  entropy->EOBRUN = 0;
  entropy->BE = 0;

  /* Initialize bit buffer to empty */
  entropy->put_buffer = 0;
  entropy->put_bits = 0;

  /* Initialize restart stuff */
  entropy->restarts_to_go = cinfo->restart_interval;
  entropy->next_restart_num = 0;
}


// ---------------------------------------------------------------------------
// @ 0x00856750
/*
 * Module initialization routine for progressive Huffman entropy encoding.
 */

void
jinit_phuff_encoder (j_compress_ptr cinfo)
{
  phuff_entropy_ptr entropy;
  int i;

  entropy = (phuff_entropy_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				SIZEOF(phuff_entropy_encoder));
  cinfo->entropy = (struct jpeg_entropy_encoder *) entropy;
  entropy->pub.start_pass = start_pass_phuff;

  /* Mark tables unallocated */
  for (i = 0; i < NUM_HUFF_TBLS; i++) {
    entropy->derived_tbls[i] = NULL;
    entropy->count_ptrs[i] = NULL;
  }
  entropy->bit_buffer = NULL;	/* needed only in AC refinement scan */
}


/* ------------------------------------------------------------------ jcprepct.c -- */

/* Private buffer controller object */

typedef struct {
  struct jpeg_c_prep_controller pub; /* public fields */

  /* Downsampling input buffer.  This buffer holds color-converted data
   * until we have enough to do a downsample step.
   */
  JSAMPARRAY color_buf[MAX_COMPONENTS];

  JDIMENSION rows_to_go;	/* counts rows remaining in source image */
  int next_buf_row;		/* index of next row to store in color_buf */

#ifdef CONTEXT_ROWS_SUPPORTED	/* only needed for context case */
  int this_row_group;		/* starting row index of group to process */
  int next_buf_stop;		/* downsample when we reach this index */
#endif
} my_prep_controller;

typedef my_prep_controller * my_prep_ptr;


/* Expand an image vertically from height input_rows to height output_rows,
 * by duplicating the bottom row.
 */

static void
expand_bottom_edge (JSAMPARRAY image_data, JDIMENSION num_cols,
		    int input_rows, int output_rows)
{
  register int row;

  for (row = input_rows; row < output_rows; row++) {
    jcopy_sample_rows(image_data, input_rows-1, image_data, row,
		      1, num_cols);
  }
}


// ---------------------------------------------------------------------------
// @ 0x00856790
/*
 * Initialize for a processing pass.
 */

static void
start_pass_prep (j_compress_ptr cinfo, J_BUF_MODE pass_mode)
{
  my_prep_ptr prep = (my_prep_ptr) cinfo->prep;

  if (pass_mode != JBUF_PASS_THRU)
    ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);

  /* Initialize total-height counter for detecting bottom of image */
  prep->rows_to_go = cinfo->image_height;
  /* Mark the conversion buffer empty */
  prep->next_buf_row = 0;
#ifdef CONTEXT_ROWS_SUPPORTED
  /* Preset additional state variables for context mode.
   * These aren't used in non-context mode, so we needn't test which mode.
   */
  prep->this_row_group = 0;
  /* Set next_buf_stop to stop after two row groups have been read in. */
  prep->next_buf_stop = 2 * cinfo->max_v_samp_factor;
#endif
}


// ---------------------------------------------------------------------------
// @ 0x008567e0
/*
 * Process some data in the simple no-context case.
 *
 * Preprocessor output data is counted in "row groups".  A row group
 * is defined to be v_samp_factor sample rows of each component.
 * Downsampling will produce this much data from each max_v_samp_factor
 * input rows.
 */

static void
pre_process_data (j_compress_ptr cinfo,
		  JSAMPARRAY input_buf, JDIMENSION *in_row_ctr,
		  JDIMENSION in_rows_avail,
		  JSAMPIMAGE output_buf, JDIMENSION *out_row_group_ctr,
		  JDIMENSION out_row_groups_avail)
{
  my_prep_ptr prep = (my_prep_ptr) cinfo->prep;
  int numrows, ci;
  JDIMENSION inrows;
  jpeg_component_info * compptr;

  while (*in_row_ctr < in_rows_avail &&
	 *out_row_group_ctr < out_row_groups_avail) {
    /* Do color conversion to fill the conversion buffer. */
    inrows = in_rows_avail - *in_row_ctr;
    numrows = cinfo->max_v_samp_factor - prep->next_buf_row;
    numrows = (int) MIN((JDIMENSION) numrows, inrows);
    (*cinfo->cconvert->color_convert) (cinfo, input_buf + *in_row_ctr,
				       prep->color_buf,
				       (JDIMENSION) prep->next_buf_row,
				       numrows);
    *in_row_ctr += numrows;
    prep->next_buf_row += numrows;
    prep->rows_to_go -= numrows;
    /* If at bottom of image, pad to fill the conversion buffer. */
    if (prep->rows_to_go == 0 &&
	prep->next_buf_row < cinfo->max_v_samp_factor) {
      for (ci = 0; ci < cinfo->num_components; ci++) {
	expand_bottom_edge(prep->color_buf[ci], cinfo->image_width,
			   prep->next_buf_row, cinfo->max_v_samp_factor);
      }
      prep->next_buf_row = cinfo->max_v_samp_factor;
    }
    /* If we've filled the conversion buffer, empty it. */
    if (prep->next_buf_row == cinfo->max_v_samp_factor) {
      (*cinfo->downsample->downsample) (cinfo,
					prep->color_buf, (JDIMENSION) 0,
					output_buf, *out_row_group_ctr);
      prep->next_buf_row = 0;
      (*out_row_group_ctr)++;
    }
    /* If at bottom of image, pad the output to a full iMCU height.
     * Note we assume the caller is providing a one-iMCU-height output buffer!
     */
    if (prep->rows_to_go == 0 &&
	*out_row_group_ctr < out_row_groups_avail) {
      for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
	   ci++, compptr++) {
	expand_bottom_edge(output_buf[ci],
			   compptr->width_in_blocks * DCTSIZE,
			   (int) (*out_row_group_ctr * compptr->v_samp_factor),
			   (int) (out_row_groups_avail * compptr->v_samp_factor));
      }
      *out_row_group_ctr = out_row_groups_avail;
      break;			/* can exit outer loop without test */
    }
  }
}


// ---------------------------------------------------------------------------
// @ 0x008569e0
#ifdef CONTEXT_ROWS_SUPPORTED

/*
 * Process some data in the context case.
 */

static void
pre_process_context (j_compress_ptr cinfo,
		     JSAMPARRAY input_buf, JDIMENSION *in_row_ctr,
		     JDIMENSION in_rows_avail,
		     JSAMPIMAGE output_buf, JDIMENSION *out_row_group_ctr,
		     JDIMENSION out_row_groups_avail)
{
  my_prep_ptr prep = (my_prep_ptr) cinfo->prep;
  int numrows, ci;
  int buf_height = cinfo->max_v_samp_factor * 3;
  JDIMENSION inrows;

  while (*out_row_group_ctr < out_row_groups_avail) {
    if (*in_row_ctr < in_rows_avail) {
      /* Do color conversion to fill the conversion buffer. */
      inrows = in_rows_avail - *in_row_ctr;
      numrows = prep->next_buf_stop - prep->next_buf_row;
      numrows = (int) MIN((JDIMENSION) numrows, inrows);
      (*cinfo->cconvert->color_convert) (cinfo, input_buf + *in_row_ctr,
					 prep->color_buf,
					 (JDIMENSION) prep->next_buf_row,
					 numrows);
      /* Pad at top of image, if first time through */
      if (prep->rows_to_go == cinfo->image_height) {
	for (ci = 0; ci < cinfo->num_components; ci++) {
	  int row;
	  for (row = 1; row <= cinfo->max_v_samp_factor; row++) {
	    jcopy_sample_rows(prep->color_buf[ci], 0,
			      prep->color_buf[ci], -row,
			      1, cinfo->image_width);
	  }
	}
      }
      *in_row_ctr += numrows;
      prep->next_buf_row += numrows;
      prep->rows_to_go -= numrows;
    } else {
      /* Return for more data, unless we are at the bottom of the image. */
      if (prep->rows_to_go != 0)
	break;
      /* When at bottom of image, pad to fill the conversion buffer. */
      if (prep->next_buf_row < prep->next_buf_stop) {
	for (ci = 0; ci < cinfo->num_components; ci++) {
	  expand_bottom_edge(prep->color_buf[ci], cinfo->image_width,
			     prep->next_buf_row, prep->next_buf_stop);
	}
	prep->next_buf_row = prep->next_buf_stop;
      }
    }
    /* If we've gotten enough data, downsample a row group. */
    if (prep->next_buf_row == prep->next_buf_stop) {
      (*cinfo->downsample->downsample) (cinfo,
					prep->color_buf,
					(JDIMENSION) prep->this_row_group,
					output_buf, *out_row_group_ctr);
      (*out_row_group_ctr)++;
      /* Advance pointers with wraparound as necessary. */
      prep->this_row_group += cinfo->max_v_samp_factor;
      if (prep->this_row_group >= buf_height)
	prep->this_row_group = 0;
      if (prep->next_buf_row >= buf_height)
	prep->next_buf_row = 0;
      prep->next_buf_stop = prep->next_buf_row + cinfo->max_v_samp_factor;
    }
  }
}


// ---------------------------------------------------------------------------
// @ 0x00856bd0
/*
 * Create the wrapped-around downsampling input buffer needed for context mode.
 */

static void
create_context_buffer (j_compress_ptr cinfo)
{
  my_prep_ptr prep = (my_prep_ptr) cinfo->prep;
  int rgroup_height = cinfo->max_v_samp_factor;
  int ci, i;
  jpeg_component_info * compptr;
  JSAMPARRAY true_buffer, fake_buffer;

  /* Grab enough space for fake row pointers for all the components;
   * we need five row groups' worth of pointers for each component.
   */
  fake_buffer = (JSAMPARRAY)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				(cinfo->num_components * 5 * rgroup_height) *
				SIZEOF(JSAMPROW));

  for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
       ci++, compptr++) {
    /* Allocate the actual buffer space (3 row groups) for this component.
     * We make the buffer wide enough to allow the downsampler to edge-expand
     * horizontally within the buffer, if it so chooses.
     */
    true_buffer = (*cinfo->mem->alloc_sarray)
      ((j_common_ptr) cinfo, JPOOL_IMAGE,
       (JDIMENSION) (((long) compptr->width_in_blocks * DCTSIZE *
		      cinfo->max_h_samp_factor) / compptr->h_samp_factor),
       (JDIMENSION) (3 * rgroup_height));
    /* Copy true buffer row pointers into the middle of the fake row array */
    MEMCOPY(fake_buffer + rgroup_height, true_buffer,
	    3 * rgroup_height * SIZEOF(JSAMPROW));
    /* Fill in the above and below wraparound pointers */
    for (i = 0; i < rgroup_height; i++) {
      fake_buffer[i] = true_buffer[2 * rgroup_height + i];
      fake_buffer[4 * rgroup_height + i] = true_buffer[i];
    }
    prep->color_buf[ci] = fake_buffer + rgroup_height;
    fake_buffer += 5 * rgroup_height; /* point to space for next component */
  }
}

#endif /* CONTEXT_ROWS_SUPPORTED */


// ---------------------------------------------------------------------------
// @ 0x00856cf0
/*
 * Initialize preprocessing controller.
 */

void
jinit_c_prep_controller (j_compress_ptr cinfo, boolean need_full_buffer)
{
  my_prep_ptr prep;
  int ci;
  jpeg_component_info * compptr;

  if (need_full_buffer)		/* safety check */
    ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);

  prep = (my_prep_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				SIZEOF(my_prep_controller));
  cinfo->prep = (struct jpeg_c_prep_controller *) prep;
  prep->pub.start_pass = start_pass_prep;

  /* Allocate the color conversion buffer.
   * We make the buffer wide enough to allow the downsampler to edge-expand
   * horizontally within the buffer, if it so chooses.
   */
  if (cinfo->downsample->need_context_rows) {
    /* Set up to provide context rows */
#ifdef CONTEXT_ROWS_SUPPORTED
    prep->pub.pre_process_data = pre_process_context;
    create_context_buffer(cinfo);
#else
    ERREXIT(cinfo, JERR_NOT_COMPILED);
#endif
  } else {
    /* No context, just make it tall enough for one row group */
    prep->pub.pre_process_data = pre_process_data;
    for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
	 ci++, compptr++) {
      prep->color_buf[ci] = (*cinfo->mem->alloc_sarray)
	((j_common_ptr) cinfo, JPOOL_IMAGE,
	 (JDIMENSION) (((long) compptr->width_in_blocks * DCTSIZE *
			cinfo->max_h_samp_factor) / compptr->h_samp_factor),
	 (JDIMENSION) cinfo->max_v_samp_factor);
    }
  }
}


/* ------------------------------------------------------------------ jcsample.c -- */

/* Pointer to routine to downsample a single component */
typedef JMETHOD(void, downsample1_ptr,
		(j_compress_ptr cinfo, jpeg_component_info * compptr,
		 JSAMPARRAY input_data, JSAMPARRAY output_data));

/* Private subobject */

typedef struct {
  struct jpeg_downsampler pub;	/* public fields */

  /* Downsampling method pointers, one per component */
  downsample1_ptr methods[MAX_COMPONENTS];
} my_downsampler;

typedef my_downsampler * my_downsample_ptr;


/* Expand a component horizontally from width input_cols to width output_cols,
 * by duplicating the rightmost samples.
 */

static void
expand_right_edge (JSAMPARRAY image_data, int num_rows,
		   JDIMENSION input_cols, JDIMENSION output_cols)
{
  register JSAMPROW ptr;
  register JSAMPLE pixval;
  register int count;
  int row;
  int numcols = (int) (output_cols - input_cols);

  if (numcols > 0) {
    for (row = 0; row < num_rows; row++) {
      ptr = image_data[row] + input_cols;
      pixval = ptr[-1];		/* don't need GETJSAMPLE() here */
      for (count = numcols; count > 0; count--)
	*ptr++ = pixval;
    }
  }
}


// ---------------------------------------------------------------------------
// @ 0x00856df0
/*
 * Do downsampling for a whole row group (all components).
 *
 * In this version we simply downsample each component independently.
 */

void
sep_downsample (j_compress_ptr cinfo,
		JSAMPIMAGE input_buf, JDIMENSION in_row_index,
		JSAMPIMAGE output_buf, JDIMENSION out_row_group_index)
{
  my_downsample_ptr downsample = (my_downsample_ptr) cinfo->downsample;
  int ci;
  jpeg_component_info * compptr;
  JSAMPARRAY in_ptr, out_ptr;

  for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
       ci++, compptr++) {
    in_ptr = input_buf[ci] + in_row_index;
    out_ptr = output_buf[ci] + (out_row_group_index * compptr->v_samp_factor);
    (*downsample->methods[ci]) (cinfo, compptr, in_ptr, out_ptr);
  }
}


// ---------------------------------------------------------------------------
// @ 0x00856e80
/*
 * Downsample pixel values of a single component.
 * One row group is processed per call.
 * This version handles arbitrary integral sampling ratios, without smoothing.
 * Note that this version is not actually used for customary sampling ratios.
 */

void
int_downsample (j_compress_ptr cinfo, jpeg_component_info * compptr,
		JSAMPARRAY input_data, JSAMPARRAY output_data)
{
  int inrow, outrow, h_expand, v_expand, numpix, numpix2, h, v;
  JDIMENSION outcol, outcol_h;	/* outcol_h == outcol*h_expand */
  JDIMENSION output_cols = compptr->width_in_blocks * DCTSIZE;
  JSAMPROW inptr, outptr;
  INT32 outvalue;

  h_expand = cinfo->max_h_samp_factor / compptr->h_samp_factor;
  v_expand = cinfo->max_v_samp_factor / compptr->v_samp_factor;
  numpix = h_expand * v_expand;
  numpix2 = numpix/2;

  /* Expand input data enough to let all the output samples be generated
   * by the standard loop.  Special-casing padded output would be more
   * efficient.
   */
  expand_right_edge(input_data, cinfo->max_v_samp_factor,
		    cinfo->image_width, output_cols * h_expand);

  inrow = 0;
  for (outrow = 0; outrow < compptr->v_samp_factor; outrow++) {
    outptr = output_data[outrow];
    for (outcol = 0, outcol_h = 0; outcol < output_cols;
	 outcol++, outcol_h += h_expand) {
      outvalue = 0;
      for (v = 0; v < v_expand; v++) {
	inptr = input_data[inrow+v] + outcol_h;
	for (h = 0; h < h_expand; h++) {
	  outvalue += (INT32) GETJSAMPLE(*inptr++);
	}
      }
      *outptr++ = (JSAMPLE) ((outvalue + numpix2) / numpix);
    }
    inrow += v_expand;
  }
}


// ---------------------------------------------------------------------------
// @ 0x00856ff0
/*
 * Downsample pixel values of a single component.
 * This version handles the special case of a full-size component,
 * without smoothing.
 */

void
fullsize_downsample (j_compress_ptr cinfo, jpeg_component_info * compptr,
		     JSAMPARRAY input_data, JSAMPARRAY output_data)
{
  /* Copy the data */
  jcopy_sample_rows(input_data, 0, output_data, 0,
		    cinfo->max_v_samp_factor, cinfo->image_width);
  /* Edge-expand */
  expand_right_edge(output_data, cinfo->max_v_samp_factor,
		    cinfo->image_width, compptr->width_in_blocks * DCTSIZE);
}


// ---------------------------------------------------------------------------
// @ 0x00857040
/*
 * Downsample pixel values of a single component.
 * This version handles the common case of 2:1 horizontal and 1:1 vertical,
 * without smoothing.
 *
 * A note about the "bias" calculations: when rounding fractional values to
 * integer, we do not want to always round 0.5 up to the next integer.
 * If we did that, we'd introduce a noticeable bias towards larger values.
 * Instead, this code is arranged so that 0.5 will be rounded up or down at
 * alternate pixel locations (a simple ordered dither pattern).
 */

void
h2v1_downsample (j_compress_ptr cinfo, jpeg_component_info * compptr,
		 JSAMPARRAY input_data, JSAMPARRAY output_data)
{
  int outrow;
  JDIMENSION outcol;
  JDIMENSION output_cols = compptr->width_in_blocks * DCTSIZE;
  register JSAMPROW inptr, outptr;
  register int bias;

  /* Expand input data enough to let all the output samples be generated
   * by the standard loop.  Special-casing padded output would be more
   * efficient.
   */
  expand_right_edge(input_data, cinfo->max_v_samp_factor,
		    cinfo->image_width, output_cols * 2);

  for (outrow = 0; outrow < compptr->v_samp_factor; outrow++) {
    outptr = output_data[outrow];
    inptr = input_data[outrow];
    bias = 0;			/* bias = 0,1,0,1,... for successive samples */
    for (outcol = 0; outcol < output_cols; outcol++) {
      *outptr++ = (JSAMPLE) ((GETJSAMPLE(*inptr) + GETJSAMPLE(inptr[1])
			      + bias) >> 1);
      bias ^= 1;		/* 0=>1, 1=>0 */
      inptr += 2;
    }
  }
}
