// @ 0x0119f820  ssl3_clear
// @ 0x0119f950  ssl3_ctrl
// @ 0x0119fbf0  ssl3_callback_ctrl
// @ 0x0119fc80  ssl3_ctx_ctrl
// @ 0x0119fee0  ssl3_get_cipher_by_char
// @ 0x011a0030  ssl3_get_req_cert_type
// @ 0x011a00a0  ssl3_shutdown
// @ 0x011a0130  ssl3_renegotiate
// @ 0x011a0160  ssl3_renegotiate_check
// @ 0x011a01d0  ssl3_write
// @ 0x011a0290  ssl3_read_internal
//
// ssl/s3_lib.c (OpenSSL 0.9.8g) -- the lib_cblock copy of the s3_lib.c
// translation unit.  Compiled verbatim from upstream so the static helpers and
// the SSL_METHOD/SSL_CTX function-pointer tables line up exactly.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s0119f820_inc  (see manifest.txt)
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/ssl/s3_lib.c"
