// Slice s011b34f0 -- statically linked OpenSSL 0.9.8g (lib_cblock), reproduced by
// compiling the upstream translation units verbatim (same route as s011b8e10 /
// s011b7... OpenSSL slices).
//
//   d2i_pu.cpp    crypto/asn1/d2i_pu.c
//     011b34f0  d2i_PublicKey
//
//   ec_curve.cpp  crypto/ec/ec_curve.c
//     011b35d0  ec_group_new_from_data        (static)
//     011b3870  EC_GROUP_new_by_curve_name
//
//   dsa_ossl.cpp  crypto/dsa/dsa_ossl.c
//     011b38f0  dsa_do_sign                   (static)
//     011b3af0  dsa_sign_setup                (static)
//     011b3d60  dsa_do_verify                 (static)
//
//   ec2_smpl.cpp  crypto/ec/ec2_smpl.c
//     011b41d0  ec_GF2m_simple_group_set_curve
//     011b4370  ec_GF2m_simple_group_check_discriminant
//     011b44e0  ec_GF2m_simple_point_set_affine_coordinates
//     011b4580  ec_GF2m_simple_point_get_affine_coordinates
//
// Identification was by the error triples, e.g. ERR_put_error(EC_LIB_...,EC_F_...) ->
// crypto/ec/*.c, ERR_put_error(DSA_LIB,...) -> crypto/dsa/dsa_ossl.c, and
// ASN1 lib 0x9b (=ASN1_F_D2I_PUBLICKEY) -> crypto/asn1/d2i_pu.c.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC plus the OpenSSL include dirs of the pinned build
// work/third_party/build/openssl-0.9.8g-d2110920 (see manifest.txt); its generated
// opensslconf.h carries the Configure VC-WIN32 options (no-asm, no-err, BN_LLONG undef).
//
// No function bodies live here; each function is emitted by the wrapper sources listed
// above, with its `// @ 0x... <name>` markers next to the include.

// @ 0x011b34f0 d2i_PublicKey
// @ 0x011b35d0 ec_group_new_from_data
// @ 0x011b3870 EC_GROUP_new_by_curve_name
// @ 0x011b38f0 dsa_do_sign
// @ 0x011b3af0 dsa_sign_setup
// @ 0x011b3d60 dsa_do_verify
// @ 0x011b41d0 ec_GF2m_simple_group_set_curve
// @ 0x011b4370 ec_GF2m_simple_group_check_discriminant
// @ 0x011b44e0 ec_GF2m_simple_point_set_affine_coordinates
// @ 0x011b4580 ec_GF2m_simple_point_get_affine_coordinates
