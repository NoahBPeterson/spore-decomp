// Slice s011bb2b0 -- every function of the slice is a function of the
// statically linked OpenSSL 0.9.8g, reproduced by compiling the upstream
// translation units verbatim (the same route as match/slices/s011a81e0/):
//
//   asn1_gen.cpp   crypto/asn1/asn1_gen.c
//     011bb3d0  bitstr_cb            (static)
//     011bb460  asn1_cb              (static)
//     011bb700  asn1_str2type        (static)
//     011bbad0  ASN1_generate_v3
//
//   conf_lib.cpp   crypto/conf/conf_lib.c
//     011bbec0  NCONF_get_section
//     011bbf10  NCONF_get_string
//     011bbf70  CONF_get_section
//     011bbfe0  CONF_get_string
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011bb2b0_inc  (see manifest.txt)
#include "types.h"

// This file carries no function bodies: OpenSSL built its own translation
// units, and each function above is emitted from asn1_gen.cpp / conf_lib.cpp.
