// @ 0x011cc4d0  BN_GF2m_mod
// @ 0x011cc7b0  BN_GF2m_mod_mul
//
// crypto/bn/bn_gf2m.c (OpenSSL 0.9.8g) -- the lib_cblock copy of the bn_gf2m.c
// translation unit.  Compiled verbatim from upstream; the file-static helpers
// (BN_GF2m_mod_arr, BN_GF2m_mod_mul_arr, BN_GF2m_poly2arr, ...) are part of the
// same object and the two exported wrappers call them at their original VAs.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011cae60_inc  (see manifest.txt)
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/bn/bn_gf2m.c"
