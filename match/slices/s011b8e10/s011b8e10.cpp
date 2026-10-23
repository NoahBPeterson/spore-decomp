// Slice s011b8e10 -- statically linked OpenSSL 0.9.8g, reproduced by compiling
// the upstream translation units verbatim (same route as s0117e620/s011bb2b0).
//
//   md5_dgst.cpp  crypto/md5/md5_dgst.c
//     011b8e10  MD5_Update
//     011b90b0  MD5_Final
//
//   v3_utl.cpp    crypto/x509v3/v3_utl.c
//     011b91f0  X509V3_add_value
//     011b9350  i2s_ASN1_ENUMERATED
//     011b93a0  i2s_ASN1_INTEGER
//     011b93f0  s2i_ASN1_INTEGER
//     011b9530  X509V3_get_value_bool
//     011b9900  hex_to_string
//     011b9990  string_to_hex
//     011b9d20  X509V3_parse_list
//
//   t_x509.cpp    crypto/asn1/t_x509.c
//     011ba540  X509_NAME_print
//
//   a_enum.cpp    crypto/asn1/a_enum.c
//     011ba680  ASN1_ENUMERATED_to_BN
//
//   asn1_gen.cpp  crypto/asn1/asn1_gen.c
//     011bb170  parse_tagging
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011b8e10_inc  (see manifest.txt)
#include "types.h"

// No function bodies live here; each function is emitted by the wrapper
// sources listed above, with its `// @ 0x...` marker next to the include.
