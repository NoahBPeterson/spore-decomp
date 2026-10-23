// Slice s011d7de0 -- OpenSSL 0.9.8g PKCS#12 key derivation + signal helpers +
// prime-field EC point arithmetic (lib_cblock).
//
// This slice is a run of the OpenSSL 0.9.8g translation units that Spore linked
// twice: once as lib_openssl (named, see symbols/lib_names.txt) and once as the
// unnamed lib_cblock block.  The 9 addresses below are the lib_cblock copy.
// They come from three upstream TUs, compiled verbatim:
//
//   crypto/pkcs12/p12_key.c (2)   p12_key.cpp
//     011d7de0 PKCS12_key_gen_uni
//     011d8190 PKCS12_key_gen_asc
//
//   crypto/ui/ui_openssl.c (2)    ui_openssl.cpp
//     011db070 popsig
//     011db130 pushsig
//
//   crypto/ec/ecp_smpl.c (5)      ecp_smpl.cpp
//     011db540 ec_GFp_simple_group_set_curve
//     011db7e0 ec_GFp_simple_group_check_discriminant
//     011dbc80 ec_GFp_simple_point_set_affine_coordinates
//     011dbcd0 ec_GFp_simple_point_get_affine_coordinates
//     011dbf60 ec_GFp_simple_set_compressed_coordinates
//
// Each wrapper compiles the whole upstream TU verbatim, because the per-TU
// register calling conventions of the static helpers only come out
// byte-identical when the entire TU is present (the same route used for the
// other OpenSSL slices, e.g. match/slices/s0117e620/ and s011a5310/).
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011d7de0_inc  (see manifest.txt)
// The include link work/match/scratch_s011d7de0_inc/ carries the OpenSSL
// 0.9.8g headers plus the e_os.h/opensslconf.h the Spore build was configured
// with.
//
// See manifest.txt for the byte-exact set.

// No function bodies live in this file.  The VAs and their `// @ 0x...` markers
// are in the wrapper sources:
//   slices/s011d7de0/p12_key.cpp
//   slices/s011d7de0/ui_openssl.cpp
//   slices/s011d7de0/ecp_smpl.cpp
