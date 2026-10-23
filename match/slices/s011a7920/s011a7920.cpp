// @ 0x011a7920  ssl3_send_server_key_exchange (OpenSSL 0.9.8g, ssl/s3_srvr.c)
//
// ssl3_send_server_key_exchange is a 2240-byte server-side handshake builder
// (RSA / DHE + ECDHE key-exchange parameter emission).  Like ssl3_accept in
// slice s011a81e0, it is reproduced by compiling the exact upstream OpenSSL
// 0.9.8g ssl/s3_srvr.c translation unit: the static helpers it calls
// (FUN_011a0930 = ssl3_send_alert / the local key-exchange routines) and the
// per-TU register calling conventions of the functions it calls only come out
// byte-identical when the whole TU is present.
//
// third_party/cblock_resolution.csv line 391 records this address:
//   011a7920,openssl,ssl3_send_server_key_exchange,exact-unique,
//   byte-identical to ssl_s3_srvr.obj:_ssl3_send_server_key_exchange
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011a81e0_inc
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/ssl/s3_srvr.c"