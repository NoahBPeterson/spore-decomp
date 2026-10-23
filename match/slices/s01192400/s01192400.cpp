// Slice s01192400 -- statically linked OpenSSL 0.9.8g, reproduced by compiling the
// upstream translation units verbatim (same route as s0117e620 / s011b8e10 / s011b34f0).
// The functions live in the lib_cblock object of the linker map; the identities come
// from the embedded source strings (".\crypto\ec\ec_asn1.c") and the OpenSSL sources.
//
//   ec_asn1.cpp    crypto/ec/ec_asn1.c
//     01192400  ec_asn1_parameters2group        (explicit EC params -> EC_GROUP)
//     01192990  ec_asn1_pkparameters2group      (ECPKPARAMETERS -> EC_GROUP)
//     01192a40  d2i_ECPKParameters
//     01192ae0  d2i_ECPrivateKey
//     01192cb0  d2i_ECParameters
//     01192d40  o2i_ECPublicKey
//
//   ssl_ciph.cpp   ssl/ssl_ciph.c
//     01192e90  ssl_load_ciphers                (EVP_get_cipherbyname/get_digestbyname table)
//     01193270  ssl_cipher_get_disabled        (returns struct disabled_masks in edx:eax)
//     01193670  ssl_cipher_strength_sort
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s01192400_inc  (see manifest.txt)
#include "types.h"

// No function bodies live here; each function is emitted by the wrapper
// sources listed above, with its `// @ 0x...` marker next to the include.
