// @ 0x01199390  a2d_ASN1_OBJECT
// @ 0x01199870  ASN1_OBJECT_new
// @ 0x01199930  c2i_ASN1_OBJECT
// @ 0x01199a40  d2i_ASN1_OBJECT
//
// crypto/asn1/a_object.c (OpenSSL 0.9.8g) -- the lib_cblock copy of the
// a_object.c translation unit.  Compiled verbatim from upstream so the static
// helper i2t_ASN1_OBJECT (and the interleaved i2a_ASN1_OBJECT / ASN1_OBJECT_free
// entry points) sit at the addresses the image places them.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s01198850_inc  (see manifest.txt)
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/asn1/a_object.c"
