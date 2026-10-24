// Slice s00859e20 -- IJG libjpeg 6a main-controller helpers, compiled verbatim
// from upstream jdmainct.c as C (same wrapper as slices s008590d0 / s0085bb90).
//
// Byte-exact functions of this translation unit (see manifest.txt):
// @ 0x0085a9f0
// 0085a9f0 alloc_funny_pointers
// @ 0x0085aaa0
// 0085aaa0 make_funny_pointers
// @ 0x0085abe0
// 0085abe0 set_wraparound_pointers
//
// The remaining jdmainct.c functions (start_pass_main, process_data_*,
// set_bottom_pointers, jinit_d_main_controller) are emitted as well but sit in
// another slice's address range.
#define JPEG_INTERNALS
#include "../../../work/third_party/src/jpeg-6a/jinclude.h"
#include "jpeglib.h"
#include "../../../work/third_party/src/jpeg-6a/jdmainct.c"
