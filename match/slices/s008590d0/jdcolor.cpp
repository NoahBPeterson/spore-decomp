// Slice s008590d0 -- IJG libjpeg 6a decompression colour-conversion module.
//
// @ 0x008590d0  build_ycc_rgb_table
// @ 0x008591a0  ycc_rgb_convert
// @ 0x008592c0  null_convert
// @ 0x00859350  grayscale_convert
// @ 0x00859380  ycck_cmyk_convert
// @ 0x008594d0  jinit_color_deconverter
//
// Vendored third-party translation unit (jdcolor.c) compiled verbatim as C
// (/TC) with the retail libjpeg flags, one wrapper per source file.  Six of the
// eleven functions in this slice live here; the rest are in jdhuff.cpp /
// jddctmgr.cpp.
//
// The retail build of IJG 6a uses a PATCHED jpeglib.h: the retail
// jpeg_decompress_struct inserts a 1024-byte comment buffer plus a 4-byte flag
// after CCIR601_sampling, so everything from max_h_samp_factor on is shifted by
// +0x404 vs stock 6a (cconvert at +0x5c8, marker at +0x5b8, unread_marker at
// +0x5a0, sample_range_limit at +0x544, ...); the error manager's msg_parm union
// is 80 bytes; and a trailing read_dht flag was appended.  The local jpeglib.h
// is that retail header (shared with slices s00858190 / s0085bb90); it is
// force-included first so that its JPEGLIB_H guard makes the unmodified header
// shipped next to jdcolor.c a no-op.
//
// Flags: /O2 /arch/SSE /MD /Gy /TC /GS-  (see manifest.txt)
#define JPEG_INTERNALS
#include "../../../work/third_party/src/jpeg-6a/jinclude.h"
#include "jpeglib.h"
#include "../../../work/third_party/src/jpeg-6a/jdcolor.c"
