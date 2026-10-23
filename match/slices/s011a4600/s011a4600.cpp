// Slice s011a4600 -- the statically linked OpenSSL 0.9.8g client-handshake
// translation unit ssl/s3_clnt.c (lib_cblock copy):
//
//   0x011a4600  ssl3_get_certificate_request
//   0x011a48f0  ssl3_connect
//
// Compiled verbatim from the upstream 0.9.8g source (the same route used for
// the rest of the statically linked OpenSSL block; see match/slices/s011a2780/
// and match/slices/s011a5310/).
//
// ssl3_generate_key_block (0x011a5120) lives in the separate ssl/s3_enc.c
// translation unit and is compiled by s011a4600_s3enc.cpp; keeping it out of
// this file matters, because a single combined TU lets the compiler inline
// ssl3_init_finished_mac into ssl3_connect (the original build had the two
// files as separate objects).
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011a4600_inc  (see manifest.txt)
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/ssl/s3_clnt.c"

// Per-function VA markers for the verbatim TU above (bodies come from the
// upstream include; markers kept here so every slice target is documented at
// column 0):
// @ 0x011a4600  ssl3_get_certificate_request
// @ 0x011a48f0  ssl3_connect
