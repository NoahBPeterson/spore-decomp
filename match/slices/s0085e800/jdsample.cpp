// Slice s0085e800 -- IJG libjpeg 6a decompression: upsampling module.
//
// @ 0x0085e9a0  start_pass_upsample
// @ 0x0085e9c0  sep_upsample
// @ 0x0085eab0  int_upsample
// @ 0x0085eb90  h2v1_upsample
// @ 0x0085ebf0  h2v2_upsample
// @ 0x0085ec60  h2v1_fancy_upsample
// @ 0x0085ed20  h2v2_fancy_upsample
// @ 0x0085ee50  jinit_upsampler
//
// Vendored third-party translation unit (work/third_party/src/jpeg-6a/jdsample.c)
// compiled verbatim as C (/TC), exactly as slices s008590d0 / s00858190 /
// s0085bb90 do.  No source was reconstructed by hand.
//
// The retail build of IJG 6a is compiled against a PATCHED jpeglib.h: the
// retail jpeg_decompress_struct inserts a 1024-byte comment buffer plus a
// 4-byte flag after CCIR601_sampling (everything from max_h_samp_factor on is
// shifted by +0x404: upsample +0x5c4, cconvert +0x5c8, ...) and appends a
// trailing read_dht flag; the error manager's msg_parm union is 80 bytes.  The
// jpeglib.h in this directory is that retail header (the same one shared by
// slices s008590d0 / s00858190 / s0085bb90); it is force-included first so that
// its JPEGLIB_H guard makes the unmodified header shipped next to jdsample.c a
// no-op.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /GS-
//        /Iwork/third_party/src/jpeg-6a /Iwork/third_party/build/jpeg-6a-inc
#define JPEG_INTERNALS
#include "../../../work/third_party/src/jpeg-6a/jinclude.h"
#include "jpeglib.h"
#include "../../../work/third_party/src/jpeg-6a/jdsample.c"
