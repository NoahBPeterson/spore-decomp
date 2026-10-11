// Slice s011b7070 -- OpenSSL 0.9.8g objects statically linked into SporeApp (lib_openssl).
//
// These are upstream OpenSSL sources rebuilt with the exact library flags (see
// third_party/manifest.json "openssl").  For C sources whose entry points are
// file-static helpers (OpenSSL passes several via register-based calling
// conventions that MSVC derives from the call sites in the same translation
// unit), the whole original .c file is pulled in so the compiler makes the same
// choices; a lone extracted function would not match.
//
// VA map (original -> upstream source):
//   // @ 0x011b7070  compute_key              crypto/dh/dh_key.c
//   // @ 0x011b7330  add_cert_dir             crypto/x509/by_dir.c
//   // @ 0x011b7520  get_cert_by_subject      crypto/x509/by_dir.c
//   // @ 0x011b77a0  dir_ctrl                 crypto/x509/by_dir.c
//   // @ 0x011b7820  X509_load_cert_file      crypto/x509/by_file.c
//   // @ 0x011b7980  X509_load_crl_file       crypto/x509/by_file.c
//   // @ 0x011b7ae0  X509_load_cert_crl_file  crypto/x509/by_file.c
//   // @ 0x011b7c90  EVP_PBE_alg_add          crypto/evp/evp_pbe.c
//   // @ 0x011b8300  ASN1_mbstring_ncopy       crypto/asn1/a_mbstr.c
//   // @ 0x011b8720  ENGINE_get_digest        crypto/engine/tb_digest.c
//
// Module flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011b7070_inc  (see manifest.txt).
// scratch_s011b7070_inc (under work/match) is a dereferenced copy of the OpenSSL build
// headers -- include/openssl/* plus the three quoted private headers the sources need
// (cryptlib.h, e_os.h, crypto/engine/eng_int.h) -- so a single short /I resolves both
// <openssl/...> and the private "..." includes.  The build's own -D switches
// (OPENSSL_THREADS, DSO_WIN32, OPENSSL_SYSNAME_WIN32, ...) live in crypto/opensslconf.h.

// @ 0x011b7070
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/dh/dh_key.c"
// @ 0x011b7330, 0x011b7520, 0x011b77a0
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/x509/by_dir.c"
// @ 0x011b7820, 0x011b7980, 0x011b7ae0
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/x509/by_file.c"
// @ 0x011b7c90
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/evp/evp_pbe.c"
// @ 0x011b8300
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/asn1/a_mbstr.c"
// @ 0x011b8720
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/engine/tb_digest.c"
