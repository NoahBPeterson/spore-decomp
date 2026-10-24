// Slice s00859e20 -- IJG libjpeg 6a Huffman entropy decoder, compiled verbatim
// from upstream jdhuff.c as C (same wrapper and retail-patched jpeglib.h as
// slices s008590d0 / s00858190 / s0085bb90).
//
// Byte-exact functions of this translation unit (see manifest.txt):
// @ 0x00859e20
// 00859e20 decode_mcu
// @ 0x0085a250
// 0085a250 start_pass_huff_decoder
// @ 0x0085a390
// 0085a390 jinit_huff_decoder
//
// jdhuff.c's first four functions (jpeg_make_d_derived_tbl, jpeg_fill_bit_buffer,
// jpeg_huff_decode, process_restart) belong to slice s008590d0 and are compiled
// there; they are emitted by this include too, which is harmless (one object per
// source file, symbols are only looked up by name).
#define JPEG_INTERNALS
#include "../../../work/third_party/src/jpeg-6a/jinclude.h"
#include "jpeglib.h"
#include "../../../work/third_party/src/jpeg-6a/jdhuff.c"
