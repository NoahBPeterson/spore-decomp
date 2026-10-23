// Slice s00878120 -- libpng 1.2.25 (lib_png / libpng.lib) statically linked into SporeApp.
// Rebuilt from the verbatim upstream pngwutil.c (pinned by third_party/manifest.json, sha256
// 295ba7b7...), the same route used for s00873a60 (pngrutil.c) and the OpenSSL block.
//
// VA map (original -> upstream source / symbol):
//   00878120  png_write_PLTE              pngwutil.c
//   00878230  png_write_hIST              pngwutil.c
//   00878310  png_check_keyword           pngwutil.c
//   008784f0  png_write_tEXt              pngwutil.c
//   008785d0  png_write_zTXt              pngwutil.c
//   00878710  (unnamed)                   pngwutil.c
//   00878e80  png_write_IHDR              pngwutil.c
//   008792a0  (unnamed)                   pngwutil.c
//   008793d0  png_write_IEND              pngwutil.c
//   00879440  png_write_gAMA              pngwutil.c
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /GS- /fp:fast /Iwork/third_party/src/libpng-1.2.25
//        /Iwork/third_party/src/zlib-1.2.3   (third_party/manifest.json libpng cflags +
//        /GS- for the original's missing stack cookie; see s00873a60)
//
// The C source is compiled as C (/TC), so the targets resolve to the upstream C symbol
// spellings (_png_write_PLTE, ...); only the bytes matter.

#include "../../../work/third_party/src/libpng-1.2.25/pngwutil.c"

// Per-function VA markers for the verbatim TU above (bodies come from the upstream include;
// markers kept here so every slice target is documented at column 0):
// @ 0x00878120
// @ 0x00878230
// @ 0x00878310
// @ 0x008784f0
// @ 0x008785d0
// @ 0x00878710
// @ 0x00878e80
// @ 0x008792a0
// @ 0x008793d0
// @ 0x00879440
