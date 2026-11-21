/* Slice s00853750 -- libjpeg 6a jcmarker.c as shipped in SporeApp.exe: IJG's source from work/ plus the AVI1 APP0
 * patch in tools/ci/oss/jpeg-6a-retail.patch (emit_4bytes, emit_avi1_app0, a JFIF/AVI1 choice in write_file_header).
 * Never copy upstream source here (THIRD_PARTY.md).  Compiled as C (/TC).
 *
 * Byte-exact functions of this translation unit (see manifest.txt):
 */
// @ 0x00853750  emit_sof
// @ 0x008538c0  emit_sos
// @ 0x00853a80  emit_jfif_app0
// @ 0x00853c80  emit_avi1_app0
// @ 0x00853dc0  emit_adobe_app14
// @ 0x00853f20  write_any_marker
// @ 0x00853f90  write_file_header
// @ 0x00853fe0  write_frame_header
// @ 0x008540c0  write_scan_header
// @ 0x008541b0  write_tables_only
// @ 0x00854290  jinit_marker_writer
#include "../../../work/third_party/build/jpeg-6a-retail/jcmarker.c"
