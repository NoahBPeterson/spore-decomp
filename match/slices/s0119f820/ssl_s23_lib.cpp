// @ 0x011a0380  ssl23_get_cipher
// @ 0x011a03e0  ssl23_read
// @ 0x011a0450  ssl23_peek
// @ 0x011a04d0  ssl23_write
//
// ssl/s23_lib.c (OpenSSL 0.9.8g) -- the lib_cblock copy of the s23_lib.c
// translation unit: the SSLv23 method table plus the version-agnostic
// cipher/read/peek/write entry points that forward to whichever method is
// negotiated.  Compiled verbatim from upstream.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s0119f820_inc  (see manifest.txt)
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/ssl/s23_lib.c"
