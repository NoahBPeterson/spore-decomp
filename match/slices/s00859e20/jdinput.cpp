// Slice s00859e20 -- IJG libjpeg 6a input-control module, compiled verbatim
// from upstream jdinput.c as C (same wrapper as slices s008590d0 / s0085bb90).
//
// Byte-exact functions of this translation unit (see manifest.txt):
// @ 0x0085a3e0
// 0085a3e0 initial_setup
// @ 0x0085a5e0
// 0085a5e0 per_scan_setup
// @ 0x0085a780
// 0085a780 latch_quant_tables
// @ 0x0085a820
// 0085a820 start_input_pass
// @ 0x0085a860
// 0085a860 consume_markers
// @ 0x0085a930
// 0085a930 reset_input_controller
// @ 0x0085a980
// 0085a980 finish_input_pass
// @ 0x0085a9a0
// 0085a9a0 jinit_input_controller
//
// initial_setup, per_scan_setup and latch_quant_tables are LOCAL (static) in
// jdinput.c, which is why the retail code receives `cinfo` in esi / ebx: cl's
// register convention for a TU-local function called from start_input_pass in
// the same object.  Compiling the upstream file verbatim reproduces it.
#define JPEG_INTERNALS
#include "../../../work/third_party/src/jpeg-6a/jinclude.h"
#include "jpeglib.h"
#include "../../../work/third_party/src/jpeg-6a/jdinput.c"
