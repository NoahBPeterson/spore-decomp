// @ 0x011a7070  ssl3_get_cert_verify (OpenSSL 0.9.8g, ssl/s3_srvr.c)
// @ 0x011a7340  ssl3_get_client_certificate (OpenSSL 0.9.8g, ssl/s3_srvr.c)
// @ 0x011a7770  ssl3_send_server_certificate (OpenSSL 0.9.8g, ssl/s3_srvr.c)
//
// Three server-side SSLv3/TLS handshake routines from the statically linked
// OpenSSL 0.9.8g block.  As with ssl3_send_server_key_exchange (slice
// s011a7920) and ssl3_accept (slice s011a81e0), they are reproduced by
// compiling the exact upstream ssl/s3_srvr.c translation unit verbatim: the
// static helpers and the per-TU register calling conventions only come out
// byte-identical when the whole TU is present.
//
// third_party/cblock_resolution.csv lines 388-390 record these addresses:
//   011a7070,openssl,ssl3_get_cert_verify,exact-unique,...
//   011a7340,openssl,ssl3_get_client_certificate,exact-unique,...
//   011a7770,openssl,ssl3_send_server_certificate,exact-unique,...
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011a81e0_inc
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/ssl/s3_srvr.c"
