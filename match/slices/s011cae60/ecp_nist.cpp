// @ 0x011ccef0  ec_GFp_nist_group_set_curve
// @ 0x011cd030  ec_GFp_nist_field_mul
//
// crypto/ec/ecp_nist.c (OpenSSL 0.9.8g) -- the lib_cblock copy of the ecp_nist.c
// translation unit, compiled verbatim from upstream.  group_set_curve picks the
// NIST reduction (BN_nist_mod_192/224/256/384/521) for the curve's prime and
// stores it in the field_data; field_mul multiplies and then reduces through
// whichever function was installed.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011cae60_inc  (see manifest.txt)
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/ec/ecp_nist.c"
