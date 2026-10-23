// @ 0x011900e0  PEM_def_callback
// @ 0x011905e0  PEM_do_header
// @ 0x01190790  load_iv
//
// crypto/pem/pem_lib.c (OpenSSL 0.9.8g) -- the lib_cblock copy of the pem_lib.c
// translation unit, compiled verbatim from upstream.  The whole TU is present
// because the file-static helpers (load_iv, check_pem) and the per-TU register
// conventions only come out byte-identical with the entire translation unit.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s01189d60_inc  (see manifest.txt)
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/pem/pem_lib.c"