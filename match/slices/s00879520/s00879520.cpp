// Slice s00879520 -- libpng 1.2.25 (lib_png / libpng.lib) statically linked into SporeApp.
// Rebuilt from the verbatim upstream pngwutil.c (pinned by third_party/manifest.json), the
// same route used for s00878120 (pngwutil.c), s00873a60 (pngrutil.c) and the OpenSSL block.
//
// VA map (original -> upstream source / symbol):
//   00879520  png_write_sRGB               pngwutil.c
//   008795d0  png_write_iCCP               pngwutil.c
//   00879720  png_write_sPLT               pngwutil.c
//   00879920  png_write_sBIT               pngwutil.c
//   00879a00  png_write_cHRM               pngwutil.c
//   00879d80  png_write_tRNS               pngwutil.c
//   00879ee0  png_write_bKGD               pngwutil.c
//   0087a040  png_write_oFFs               pngwutil.c
//   0087a130  png_write_sCAL               pngwutil.c
//   0087a1e0  png_write_pHYs               pngwutil.c
//   0087a2d0  png_write_tIME               pngwutil.c
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /GS- /fp:fast /Iwork/third_party/src/libpng-1.2.25
//        /Iwork/third_party/src/zlib-1.2.3   (third_party/manifest.json libpng cflags +
//        /GS- for the original's missing stack cookie; see s00873a60). /arch:SSE is what
//        gives png_write_cHRM its fcomi/fcompi sequence; /fp:fast is what makes the
//        iCCP/sPLT chunk-data helpers inline at these call sites.
//
// The C source is compiled as C (/TC), so the targets resolve to the upstream C symbol
// spellings (_png_write_sRGB, ...); only the bytes matter.

#include "../../../work/third_party/src/libpng-1.2.25/pngwutil.c"

// Per-function VA markers for the verbatim TU above (bodies come from the upstream include;
// markers kept here so every slice target is documented at column 0):
// @ 0x00879520
// @ 0x008795d0
// @ 0x00879720
// @ 0x00879920
// @ 0x00879a00
// @ 0x00879d80
// @ 0x00879ee0
// @ 0x0087a040
// @ 0x0087a130
// @ 0x0087a1e0
// @ 0x0087a2d0
