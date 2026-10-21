// @ 0x011ccc00  ec_GFp_mont_group_set_curve
// @ 0x011ccd50  ec_GFp_mont_field_mul
// @ 0x011ccda0  ec_GFp_mont_field_sqr
// @ 0x011ccde0  ec_GFp_mont_field_encode
// @ 0x011cce30  ec_GFp_mont_field_decode
// @ 0x011cce70  ec_GFp_mont_field_set_to_one
//
// crypto/ec/ecp_mont.c (OpenSSL 0.9.8g) -- the lib_cblock copy of the ecp_mont.c
// translation unit, compiled verbatim from upstream.  group_set_curve installs
// the six field wrappers above into the EC_METHOD; the wrappers themselves are
// the BN_MONT_CTX accessors that forward to BN_mod_mul_montgomery /
// BN_from_montgomery / BN_copy.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011cae60_inc  (see manifest.txt)
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/ec/ecp_mont.c"
