// Slice s008571b0 -- IJG libjpeg 6a compression-side downsampler.
//
// @ 0x008571b0  h2v2_smooth_downsample
// @ 0x00857430  fullsize_smooth_downsample
// @ 0x008575b0  jinit_downsampler
//
// Vendored third-party translation unit (work/third_party/src/jpeg-6a/jcsample.c)
// compiled verbatim as C (/TC), one wrapper per source file -- the same
// approach slices s008561e0 / s008590d0 use.  The whole file is pulled in so
// that its TU-local static helpers are visible with the same register-based
// calling convention the retail compiler chose for them.
//
// "jpeglib.h" below is the retail-patched header next to this file (shared with
// slices s00858190 / s0085bb90 / s008590d0): the common fields have no
// client_data member, a 1024-byte comment buffer plus flag sits at +0x130, and a
// trailing read_dht field was appended at +0x5d0.  Its JPEGLIB_H guard makes the
// stock header shipped next to jcsample.c a no-op.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /GS-  (see manifest.txt)
#define JPEG_INTERNALS
#include "../../../work/third_party/src/jpeg-6a/jinclude.h"
#include "jpeglib.h"
#include "../../../work/third_party/src/jpeg-6a/jcsample.c"
