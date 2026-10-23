// @ 0x011db540  ec_GFp_simple_group_set_curve
// @ 0x011db7e0  ec_GFp_simple_group_check_discriminant
// @ 0x011dbc80  ec_GFp_simple_point_set_affine_coordinates
// @ 0x011dbcd0  ec_GFp_simple_point_get_affine_coordinates
// @ 0x011dbf60  ec_GFp_simple_set_compressed_coordinates
//
// crypto/ec/ecp_smpl.c (OpenSSL 0.9.8g) -- the lib_cblock copy of the
// ecp_smpl.c translation unit.  Compiled verbatim from upstream so the
// static helpers and the five curve/point entry points line up exactly.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011d7de0_inc  (see manifest.txt)
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/ec/ecp_smpl.c"
