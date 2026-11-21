// Slice s008571b0 -- IJG libjpeg 6a "minimum API" module (jdapimin.c), retail build.
//
// @ 0x00857730  jpeg_CreateDecompress   (retail: clears read_dht)
// @ 0x00857880  default_decompress_parms
// @ 0x00857a50  jpeg_consume_input
// @ 0x00857b20  jpeg_finish_decompress
// @ 0x00857bf0  jpeg_read_header        (retail: default-Huffman-table fallback)
//
// IJG's jdapimin.c from work/ plus SporeApp.exe's two changes (tools/ci/oss/jpeg-6a-retail.patch); its other
// functions belong to neighbouring slices.  Compiled as C (/TC).  Never copy upstream source here (THIRD_PARTY.md).
#include "../../../work/third_party/build/jpeg-6a-retail/jdapimin.c"
