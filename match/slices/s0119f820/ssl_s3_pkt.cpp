// @ 0x011a0540  ssl3_read_n
// @ 0x011a0720  ssl3_do_compress
// @ 0x011a0770  ssl3_write_pending
// @ 0x011a0860  ssl3_do_change_cipher_spec
// @ 0x011a0930  ssl3_send_alert
//
// ssl/s3_pkt.c (OpenSSL 0.9.8g) -- the lib_cblock copy of the s3_pkt.c
// translation unit (SSL record layer: buffered reads, record compression and
// the alert sender).  Compiled verbatim from upstream.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s0119f820_inc  (see manifest.txt)
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/ssl/s3_pkt.c"
