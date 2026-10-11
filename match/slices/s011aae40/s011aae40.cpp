// Slice s011aae40 (gold1 #10) -- OpenSSL 0.9.8g objects statically linked into SporeApp
// (lib_openssl).  Rebuilt with the exact library flags (third_party/manifest.json "openssl").
//
// Every entry point here is byte-identical to its faithful-build object (third_party/
// cblock_resolution.csv), so the original .c translation units are pulled in whole; the
// compiler's own choices (register conventions of the file-static helpers, instruction
// scheduling, MOD_EXP_CTIME macro expansion) only come out identical with the whole file.
//
// VA map (original -> upstream source):
//   // @ 0x011aae40  BN_mod_exp_mont_consttime  crypto/bn/bn_exp.c
//   // @ 0x011ab260  BN_mod_exp_mont_word       crypto/bn/bn_exp.c
//   // @ 0x011ab5e0  BN_mod_exp_mont            crypto/bn/bn_exp.c
//   // @ 0x011ac160  RSA_padding_add_none       crypto/rsa/rsa_none.c
//   // @ 0x011ac1c0  RSA_padding_check_none    crypto/rsa/rsa_none.c
//   // @ 0x011ac220  RSA_padding_add_SSLv23    crypto/rsa/rsa_ssl.c
//   // @ 0x011ac2d0  RSA_padding_check_SSLv23  crypto/rsa/rsa_ssl.c
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011aae40_inc  (see manifest.txt).
// scratch_s011aae40_inc (under work/match) is a dereferenced copy of the OpenSSL build's
// headers (include/openssl/* + e_os.h + crypto/cryptlib.h) so one short /I resolves both
// <openssl/...> and the private quoted headers; the private per-directory headers
// (bn_lcl.h, rsa_locl.h) resolve relative to their .c files.

// @ 0x011aae40, 0x011ab260, 0x011ab5e0
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/bn/bn_exp.c"
// @ 0x011ac160, 0x011ac1c0
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/rsa/rsa_none.c"
// @ 0x011ac220, 0x011ac2d0
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/rsa/rsa_ssl.c"
