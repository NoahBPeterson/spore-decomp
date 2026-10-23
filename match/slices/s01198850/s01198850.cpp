// Slice s01198850 -- OpenSSL 0.9.8g ASN.1 free/dup/object/string helpers (lib_cblock).
//
// This slice is a run of the OpenSSL 0.9.8g translation units that Spore linked
// twice: once as lib_openssl (named, see symbols/lib_names.txt) and once as the
// unnamed lib_cblock block.  The 14 addresses below are the lib_cblock copy.
// They come from six upstream TUs, compiled verbatim:
//
//   crypto/asn1/tasn_fre.c (1)    tasn_fre.cpp
//     01198850 ASN1_template_free
//
//   crypto/x509/x509_obj.c (1)    x509_obj.cpp
//     01198d60 X509_NAME_oneline
//
//   crypto/asn1/a_dup.c (2)       a_dup.cpp
//     011990c0 ASN1_dup               01199140 ASN1_item_dup
//
//   crypto/objects/obj_lib.c (1)  obj_lib.cpp
//     011991b0 OBJ_dup
//
//   crypto/asn1/a_object.c (4)    a_object.cpp
//     01199390 a2d_ASN1_OBJECT        01199930 c2i_ASN1_OBJECT
//     01199870 ASN1_OBJECT_new        01199a40 d2i_ASN1_OBJECT
//
//   crypto/asn1/asn1_lib.c (5)    asn1_lib.cpp
//     01199cb0 ASN1_STRING_set        01199e70 ASN1_get_object
//     01199d70 ASN1_STRING_type_new   0119a0e0 ASN1_STRING_dup
//                                     0119a180 ASN1_STRING_new
//
// Each wrapper compiles the whole upstream TU verbatim, because the per-TU
// register calling conventions of the static helpers only come out
// byte-identical when the entire TU is present (the same route used for the
// other OpenSSL slices, e.g. match/slices/s0117e620/ and s0119f820/).
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s01198850_inc  (see manifest.txt)
// The include link work/match/scratch_s01198850_inc/ carries the OpenSSL
// 0.9.8g headers plus the e_os.h/opensslconf.h the Spore build was configured
// with.
//
// Config note: the inc dir's opensslconf.h must leave
// OPENSSL_EXPORT_VAR_AS_FUNCTION *undefined* (i.e. the s0117e620 opensslconf.h,
// not the s0119f820 one).  With it defined, ASN1_ITEM_ptr(tt->item) expands to
// (tt->item)() and ASN1_template_free calls tt->item through a function
// pointer; the image loads tt->item and passes it directly, so the macro must
// be the (iptr) form.
//
// See manifest.txt for the byte-exact set.

// No function bodies live in this file.  The VAs and their `// @ 0x...` markers
// are in the wrapper sources:
//   slices/s01198850/tasn_fre.cpp
//   slices/s01198850/x509_obj.cpp
//   slices/s01198850/a_dup.cpp
//   slices/s01198850/obj_lib.cpp
//   slices/s01198850/a_object.cpp
//   slices/s01198850/asn1_lib.cpp
