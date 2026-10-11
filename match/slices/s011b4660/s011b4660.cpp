// Slice s011b4660 (gold1 #11) -- OpenSSL 0.9.8g objects statically linked into SporeApp
// (lib_openssl).  Rebuilt with the exact library flags (third_party/manifest.json "openssl").
//
// Every entry point here is byte-identical to its faithful-build object
// (third_party/cblock_resolution.csv), so the original .c translation units are pulled in
// whole; the file-static helpers (check_policy, X509_get_pubkey_parameters, generate_key)
// only get the compiler's register conventions when the whole file is compiled, and the
// generated x_all.c wrappers are byte-identical only with the whole file.
//
// VA map (original -> upstream source / symbol):
//   // @ 0x011b4660  ec_GF2m_simple_point2oct    crypto/ec/ec2_smpl.c
//   // @ 0x011b48d0  ec_GF2m_simple_oct2point    crypto/ec/ec2_smpl.c
//   // @ 0x011b5c50  check_policy                crypto/x509/x509_vfy.c   (static)
//   // @ 0x011b5dc0  X509_get_pubkey_parameters  crypto/x509/x509_vfy.c   (static)
//   // @ 0x011b67e0  X509_STORE_CTX_init         crypto/x509/x509_vfy.c
//   // @ 0x011b6990  X509_verify_cert            crypto/x509/x509_vfy.c
//   // @ 0x011b6df0  X509_verify                 crypto/x509/x_all.c
//   // @ 0x011b6e20  X509_CRL_verify             crypto/x509/x_all.c
//   // @ 0x011b6e50  d2i_X509_bio                crypto/x509/x_all.c
//   // @ 0x011b6e70  d2i_X509_CRL_bio            crypto/x509/x_all.c
//   // @ 0x011b6e90  X509_digest                 crypto/x509/x_all.c
//   // @ 0x011b6ef0  generate_key                crypto/dh/dh_key.c       (static)
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011b4660_inc  (see manifest.txt).
// scratch_s011b4660_inc (under work/match) is a dereferenced copy of the OpenSSL build's
// headers (include/openssl/* + e_os.h + crypto/cryptlib.h).  It is *not* byte-for-byte the
// build's opensslconf.h: Spore's retail build leaves OPENSSL_EXPORT_VAR_AS_FUNCTION
// undefined, so ASN1 item pointers are exported as data (`push &X509_it`) rather than as
// functions returning the pointer (`call X509_it`).  The faithful build's generated
// opensslconf.h defined that macro, which is why its x_all.c object is only "near"; undoing
// it in the copy restores the retail encoding and makes X509_verify / X509_CRL_verify /
// X509_digest / d2i_* / i2d_* byte-exact.  The private per-directory headers (bn_lcl.h,
// ec_lcl.h, dh_locl.h) resolve relative to their .c files.

#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/ec/ec2_smpl.c"
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/x509/x509_vfy.c"
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/x509/x_all.c"
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/bio/b_dump.c"
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/dh/dh_key.c"
