// Slice s00873a60 (gold5 #15) -- libpng 1.2.25 (lib_png / libpng.lib) statically linked into
// SporeApp.  Rebuilt from the verbatim upstream pngrutil.c (pinned by third_party/manifest.json,
// sha256 295ba7b7...; see THIRD_PARTY.md), the same route used for the OpenSSL block
// (match/slices/s011bc410).
//
// VA map (original -> upstream source / symbol):
//   00873a60  png_handle_cHRM        pngrutil.c
//   008745a0  png_handle_tRNS        pngrutil.c
//   00874860  png_handle_bKGD        pngrutil.c
//   00874a80  png_handle_hIST        pngrutil.c
//   00874c00  png_handle_pHYs        pngrutil.c
//   00874d20  png_handle_oFFs        pngrutil.c
//   00875100  png_handle_sCAL        pngrutil.c
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /GS- /fp:fast /Iwork/third_party/src/libpng-1.2.25
//        /Iwork/third_party/src/zlib-1.2.3
//        (third_party/manifest.json libpng cflags + zlib; /GS- added to match the original's
//         missing stack cookie, /fp:fast to match SSE cvtsi2ss/mulss float codegen in cHRM)
//
// The C source is compiled as C (/TC), so the slice targets resolve to the upstream C symbol
// spellings (_png_handle_*) rather than the binary's lib_png:: manglings; only the bytes matter.

#include "../../../work/third_party/src/libpng-1.2.25/pngrutil.c"

// Per-function VA markers for the verbatim TU above (bodies come from the upstream include;
// markers kept here so every slice target is documented at column 0):
// @ 0x00873a60
// @ 0x008745a0
// @ 0x00874860
// @ 0x00874a80
// @ 0x00874c00
// @ 0x00874d20
// @ 0x00875100
