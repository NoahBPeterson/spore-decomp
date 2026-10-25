// Slice s008571b0 -- IJG libjpeg 6a "minimum API" module (jdapimin.c), retail build.
//
// @ 0x00857730  jpeg_CreateDecompress   (retail: clears read_dht)
// @ 0x00857880  default_decompress_parms
// @ 0x00857a50  jpeg_consume_input
// @ 0x00857b20  jpeg_finish_decompress
// @ 0x00857bf0  jpeg_read_header        (retail: default-Huffman-table fallback)
//
// "jdapimin.c" next to this file is the upstream IJG 6a source with the two
// retail Spore patches applied and its own header includes removed; it is
// compiled as C here (/TC).  jdapimin.c's other functions (jpeg_destroy_decompress,
// jpeg_abort_decompress, jpeg_set_marker_processor, jpeg_input_complete,
// jpeg_has_multiple_scans) belong to neighbouring slices and are present only to
// keep the translation unit complete.
//
// See jcsample.cpp for the retail-patched jpeglib.h and the flag set.
#define JPEG_INTERNALS
#include "../../../work/third_party/src/jpeg-6a/jinclude.h"
#include "jpeglib.h"
#include "jdapimin.c"
