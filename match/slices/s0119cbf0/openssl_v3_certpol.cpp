// crypto/x509v3/*.c (OpenSSL 0.9.8g) -- the v3_akey / v3_cpols / v3_bcons
// translation units, compiled verbatim so the file-static helpers and the
// per-TU internal calling conventions come out byte-identical.
//
// The slice's nine lib_cblock addresses are the unnamed second copy of:
//
//   crypto/x509v3/v3_akey.c   (1)  0119cbf0 v2i_AUTHORITY_KEYID
//   crypto/x509v3/v3_cpols.c  (7)  0119cf10 nref_nos
//                                  0119cf90 print_notice
//                                  0119d090 notice_section
//                                  0119d350 print_qualifiers
//                                  0119d420 policy_section
//                                  0119d670 i2r_certpol
//                                  0119d700 r2i_certpol
//   crypto/x509v3/v3_bcons.c  (1)  0119d970 v2i_BASIC_CONSTRAINTS
//
// This wrapper exists only so the slice has a <<slice>.cpp>; the real sources are
// openssl_v3_akey.cpp / openssl_v3_cpols.cpp / openssl_v3_bcons.cpp, listed in
// manifest.txt.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011b8e10_inc /Iwork/third_party/build/openssl-0.9.8g-d2110920/crypto/x509v3
