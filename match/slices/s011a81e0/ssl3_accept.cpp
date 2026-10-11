// @ 0x011a81e0  ssl3_accept (OpenSSL 0.9.8g, ssl/s3_srvr.c)
//
// ssl3_accept is a 2198-byte SSLv3/TLS server accept state machine.  It is
// reproduced by compiling the exact upstream OpenSSL 0.9.8g ssl/s3_srvr.c
// translation unit: every static helper it calls (ssl3_get_client_hello,
// ssl3_send_server_hello, ssl3_get_client_key_exchange, ...) lives in that same
// TU, and their per-TU register calling conventions only come out byte-identical
// when the whole TU is present.  This is the same route that makes the other
// OpenSSL functions in this slice byte-identical (see third_party/cblock_resolution.csv).
//
// Flags: /O2 /arch:SSE /MD /Gy /TC -DOPENSSL_THREADS -DDSO_WIN32
//        -DOPENSSL_SYSNAME_WIN32 -DWIN32_LEAN_AND_MEAN -DL_ENDIAN
//        -D_CRT_SECURE_NO_DEPRECATE + OpenSSL include paths (see manifest.txt)
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/ssl/s3_srvr.c"
