// @ 0x011c9630  ec_wNAF_mul
// @ 0x011c9fc0  ec_wNAF_precompute_mult
//
// crypto/ec/ec_mult.c (OpenSSL 0.9.8g) -- the lib_cblock copy of the ec_mult.c
// translation unit, compiled verbatim from upstream.  ec_wNAF_mul is the
// windowed-NAF multi-scalar multiplication (the group order check, the per-scalar
// window selection by BN_num_bits, the 1<<(w-1) table build, the recoding loop
// and the add/double driver); ec_wNAF_precompute_mult builds the shared
// precomputation table the same function consumes.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011c9630_inc  (see manifest.txt)
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/ec/ec_mult.c"
