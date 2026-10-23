// Slice s008590d0 -- IJG libjpeg 6a Huffman entropy decoder (progressive and
// baseline), compiled verbatim from upstream jdhuff.c as C.
//
// @ 0x008599f0  jpeg_make_d_derived_tbl
// @ 0x00859bb0  jpeg_fill_bit_buffer
// @ 0x00859cc0  jpeg_huff_decode
// @ 0x00859db0  process_restart
//
// See jdcolor.cpp for the retail-patched jpeglib.h and the flag set.
#define JPEG_INTERNALS
#include "../../../work/third_party/src/jpeg-6a/jinclude.h"
#include "jpeglib.h"
#include "../../../work/third_party/src/jpeg-6a/jdhuff.c"
