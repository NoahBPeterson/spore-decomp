// Slice s0117e620 -- OpenSSL 0.9.8g ASN.1 decoder + X509v3 extension lookup (lib_cblock).
//
// This slice is a run of the OpenSSL 0.9.8g translation units that Spore linked
// twice: once as lib_openssl (named, see symbols/lib_names.txt) and once as the
// unnamed lib_cblock block.  The 6 addresses below are the lib_cblock copy.
// They come from two upstream TUs, compiled verbatim:
//
//   crypto/asn1/tasn_dec.c (5)   tasn_dec.cpp
//     0117e620 asn1_find_end          0117ec00 ASN1_item_ex_d2i
//     0117e730 asn1_collect           0117f2a0 asn1_template_noexp_d2i
//     0117e920 asn1_d2i_ex_primitive
//
//   crypto/x509v3/v3_lib.c (1)   v3_lib.cpp
//     0117f580 X509V3_EXT_get_nid
//
// Each wrapper compiles the whole upstream TU verbatim, because the per-TU
// register calling conventions of the static helpers only come out
// byte-identical when the entire TU is present (the same route used for the
// other OpenSSL slices, e.g. match/slices/s0119f820/ and s011a5310/).
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s0117e620_inc  (see manifest.txt)
// The include link work/match/scratch_s0117e620_inc/ carries the OpenSSL
// 0.9.8g headers plus the e_os.h/opensslconf.h the Spore build was configured
// with.
//
// See manifest.txt for the byte-exact set.

// No function bodies live in this file.  The VAs and their `// @ 0x...` markers
// are in the wrapper sources:
//   slices/s0117e620/tasn_dec.cpp
//   slices/s0117e620/v3_lib.cpp
