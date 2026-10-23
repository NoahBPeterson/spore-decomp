// Slice s0085e800 -- IJG libjpeg 6a decompression: post-processing controller.
//
// @ 0x0085e800  start_pass_dpost
// @ 0x0085e900  jinit_d_post_controller
//
// Vendored third-party translation unit (work/third_party/src/jpeg-6a/jdpostct.c)
// compiled verbatim as C (/TC); see jdsample.cpp for the retail-patched
// jpeglib.h and the flag set.  The other three functions of this unit
// (post_process_1pass / post_process_prepass / post_process_2pass, at
// 0085e630 / 0085e6b0 / 0085e760) are claimed by slice s0085d930.
#define JPEG_INTERNALS
#include "../../../work/third_party/src/jpeg-6a/jinclude.h"
#include "jpeglib.h"
#include "../../../work/third_party/src/jpeg-6a/jdpostct.c"
