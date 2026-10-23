// Slice s00853750 -- libjpeg 6a marker writer and compressor initial_setup.
//
// This is the JPEG marker-writing half of the vendored IJG libjpeg 6a that Spore
// links into SporeApp.exe (third_party/manifest.json: jpegsrc.v6a.tar.gz,
// sha256 0e963fdd...c5929; NOT 6b).  The 12 addresses below come from two
// upstream translation units, compiled verbatim as C:
//
//   jcmarker.c (11)               jcmarker.c
//     00853750 emit_sof             008538c0 emit_sos
//     00853a80 emit_jfif_app0       00853c80 emit_avi1_app0   (Spore patch)
//     00853dc0 emit_adobe_app14     00853f20 write_any_marker
//     00853f90 write_file_header    00853fe0 write_frame_header
//     008540c0 write_scan_header    008541b0 write_tables_only
//     00854290 jinit_marker_writer
//
//   jcmaster.c (1)                jcmaster.c
//     00854300 initial_setup
//
// jcmarker.c is upstream 6a with one Spore patch that the image proves: a video
// JPEG gets an "AVI1" APP0 block instead of (or alongside) the JFIF one.  The
// patch adds emit_4bytes (image 0x00853320, another slice) and emit_avi1_app0
// (0x00853c80), and turns write_file_header into a two-way JFIF/AVI1 choice on
// a selector word at +0x168 of jpeg_compress_struct (past the end of the
// upstream struct, so it is read through a raw-offset macro).  Unlike the
// earlier slice s00852860, these marker helpers do reproduce byte-for-byte:
// compiling the whole translation unit as C makes MSVC (/O2 /TC) assign the
// same fixed registers the original build used, and emit_byte is inlined into
// each caller exactly as in the image.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC
//        /Iwork/third_party/build/jpeg-6a-inc   (jconfig.h: boolean stays int)
//        /Iwork/third_party/src/jpeg-6a         (jinclude.h, jpeglib.h, ...)
//
// Note: upstream 6a also emits emit_byte/emit_marker/emit_2bytes/emit_dqt/
// emit_dht (0x00853240..0x008535d0) and write_file_trailer (0x00854190) from
// this TU; they belong to other slices and are not claimed here.
//
// See manifest.txt for the byte-exact set (12 / 12).

// No function bodies live in this file.  The VAs and their `// @ 0x...` markers
// are in the vendored sources themselves:
//   slices/s00853750/jcmarker.c
//   slices/s00853750/jcmaster.c
