// Slice s011a4600 (continued) -- the statically linked OpenSSL 0.9.8g
// translation unit ssl/s3_enc.c (lib_cblock copy), compiled as its own object
// exactly as in the original build:
//
//   0x011a5120  ssl3_generate_key_block
//
// (The rest of s3_enc.c -- ssl3_change_cipher_state, ssl3_setup_key_block and
// friends -- belongs to slice s011a5310; here only ssl3_generate_key_block is a
// slice target, the other bodies are inert extra definitions.)
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011a4600_inc  (see manifest.txt)
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/ssl/s3_enc.c"

// Per-function VA markers for the verbatim TU above (the body comes from the
// upstream include; the marker is kept here so every slice target is
// documented at column 0):
// @ 0x011a5120  ssl3_generate_key_block
