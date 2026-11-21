// Slice s008571b0 -- IJG libjpeg 6a decompression datastream source module.
//
// @ 0x00858000  fill_input_buffer         (TU-local static)
//
// IJG's jdatasrc.c from work/ plus SporeApp.exe's change (tools/ci/oss/jpeg-6a-retail.patch: the stdio read goes
// through the engine's gread, 0x0087d4e0).  The other functions of the file belong to neighbouring slices.
// Compiled as C (/TC).  Never copy upstream source here (THIRD_PARTY.md).
#include "../../../work/third_party/build/jpeg-6a-retail/jdatasrc.c"
