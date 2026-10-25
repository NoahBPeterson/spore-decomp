// Slice s008571b0 -- IJG libjpeg 6a decompression datastream source module.
//
// @ 0x00858000  fill_input_buffer         (TU-local static)
//
// Vendored third-party translation unit (work/third_party/src/jpeg-6a/jdatasrc.c)
// compiled verbatim as C (/TC).  The other functions of the file (init_source,
// skip_input_data, term_source, jpeg_stdio_src) belong to neighbouring slices
// and are only present here to keep the translation unit complete.
//
// See jcsample.cpp for the retail-patched jpeglib.h and the flag set.
// jdatasrc.c is the upstream source next to this file, patched to read through
// the engine's gread (0x0087d4e0).
#define JPEG_INTERNALS
#include "../../../work/third_party/src/jpeg-6a/jinclude.h"
#include "jpeglib.h"
#include "jdatasrc.c"
