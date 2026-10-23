// Slice s011bc410 (gold5 #15) -- OpenSSL 0.9.8g objects statically linked into SporeApp
// (lib_openssl).  Rebuilt from the verbatim upstream 0.9.8g translation units, the same
// route used for the rest of the OpenSSL block (see match/slices/s011a5310/).
//
// VA map (original -> upstream source / symbol):
//   011bc410  tls1_change_cipher_state         ssl/t1_enc.c
//   011bc920  tls1_setup_key_block             ssl/t1_enc.c
//   011bcac0  tls1_enc                         ssl/t1_enc.c
//   011bcef0  tls1_mac                         ssl/t1_enc.c
//   011bd580  ssl_set_pkey                     ssl/ssl_rsa.c   (static)
//   011bd660  SSL_use_PrivateKey               ssl/ssl_rsa.c
//   011bd6c0  ssl_set_cert                     ssl/ssl_rsa.c   (static)
//   011bd7d0  SSL_use_certificate              ssl/ssl_rsa.c
//   011bd900  EVP_VerifyFinal                  crypto/evp/p_verify.c
//   011bdaf0  EVP_SignFinal                    crypto/evp/p_sign.c
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011bc410_inc  (see manifest.txt).
// scratch_s011bc410_inc (under work/match) is a dereferenced copy of the OpenSSL build's
// generated headers (include/openssl/* + e_os.h + crypto/cryptlib.h).

#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/ssl/t1_enc.c"
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/ssl/ssl_rsa.c"
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/evp/p_verify.c"
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/evp/p_sign.c"

// Per-function VA markers for the verbatim TUs above (bodies come from the upstream
// includes; markers kept here so every slice target is documented at column 0):
// @ 0x011bc410
// @ 0x011bc920
// @ 0x011bcac0
// @ 0x011bcef0
// @ 0x011bd580
// @ 0x011bd660
// @ 0x011bd6c0
// @ 0x011bd7d0
// @ 0x011bd900
// @ 0x011bdaf0
