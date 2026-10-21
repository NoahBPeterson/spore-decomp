// Slice s0119f820 -- OpenSSL 0.9.8g SSL record/state/method code (lib_cblock).
//
// This slice is a run of the OpenSSL 0.9.8g translation units that Spore linked
// twice: once as lib_openssl (named, see symbols/lib_names.txt) and once as the
// unnamed lib_cblock block.  The 20 addresses below are the lib_cblock copy.
// They come from three upstream TUs, compiled verbatim:
//
//   ssl/s3_lib.c  (11)   ssl_s3_lib.cpp
//     0119f820 ssl3_clear            011a0030 ssl3_get_req_cert_type
//     0119f950 ssl3_ctrl             011a00a0 ssl3_shutdown
//     0119fbf0 ssl3_callback_ctrl    011a0130 ssl3_renegotiate
//     0119fc80 ssl3_ctx_ctrl         011a0160 ssl3_renegotiate_check
//     0119fee0 ssl3_get_cipher_by_char 011a01d0 ssl3_write
//                                     011a0290 ssl3_read_internal
//
//   ssl/s3_pkt.c  (5)    ssl_s3_pkt.cpp
//     011a0540 ssl3_read_n           011a0770 ssl3_write_pending
//     011a0720 ssl3_do_compress      011a0860 ssl3_do_change_cipher_spec
//                                     011a0930 ssl3_send_alert
//
//   ssl/s23_lib.c (4)    ssl_s23_lib.cpp
//     011a0380 ssl23_get_cipher      011a0450 ssl23_peek
//     011a03e0 ssl23_read            011a04d0 ssl23_write
//
// Each wrapper compiles the whole upstream TU verbatim, because the per-TU
// register calling conventions of the static helpers only come out
// byte-identical when the entire TU is present (the same route used for the
// other OpenSSL slices, e.g. match/slices/s011a5310/ and s011a81e0/).
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s0119f820_inc  (see manifest.txt)
// The include link work/match/scratch_s0119f820_inc/ carries the OpenSSL
// 0.9.8g headers plus the e_os.h/opensslconf.h the Spore build was configured
// with (OPENSSL_NO_TLSEXT, OPENSSL_NO_SSL2, OPENSSL_THREADS, ...).
//
// Every one of the 20 functions is byte-exact; see manifest.txt.
//
// Equivalence gate (tools/difftest/equiv.py, default inputs) run with
//   --src match/slices/s0119f820/<wrapper>.cpp --flags "/O2 /arch:SSE /MD /Gy /TC /Iscratch_s0119f820_inc"
// (the gate defaults to s0119f820.cpp, which holds no bodies, so --src is required
//  for it to find the symbols).  Functions that do not call other OpenSSL TUs PASS:
//   011a0030 PASS 84.2%, 011a00a0 PASS 100%, 011a0130 PASS 100%, 011a0160 PASS 100%,
//   011a0720 PASS 100%, 011a0930 PASS 91.5%.
// The rest read UNSUPPORTED because the gate requires every callee to resolve inside
// the compiled module, and these verbatim upstream TUs call into sibling OpenSSL TUs
// (_SSL_state, _ERR_put_error, _BIO_read, _ssl3_write_bytes, ...) that are not part of
// this slice.  That is expected for whole-TU verbatim slices; byte-exactness is proven
// independently by run_all.py (20/20).

// No function bodies live in this file.  The VAs and their `// @ 0x...` markers
// are in the three wrapper sources:
//   slices/s0119f820/ssl_s3_lib.cpp
//   slices/s0119f820/ssl_s3_pkt.cpp
//   slices/s0119f820/ssl_s23_lib.cpp
