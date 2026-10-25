// Slice s008571b0 -- IJG libjpeg 6a decompression "standard API" module.
//
// @ 0x00857c90  output_pass_setup          (TU-local static)
// @ 0x00857d70  jpeg_read_scanlines
// @ 0x00857e10  jpeg_start_decompress
//
// Vendored third-party translation unit (work/third_party/src/jpeg-6a/jdapistd.c)
// compiled verbatim as C (/TC).  output_pass_setup is a LOCAL static that the
// retail compiler calls with cinfo in ESI; keeping the whole file in one
// translation unit reproduces that convention.
//
// See jcsample.cpp for the retail-patched jpeglib.h and the flag set.
#define JPEG_INTERNALS
#include "../../../work/third_party/src/jpeg-6a/jinclude.h"
#include "jpeglib.h"
#include "../../../work/third_party/src/jpeg-6a/jdapistd.c"
