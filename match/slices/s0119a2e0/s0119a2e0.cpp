// Slice s0119a2e0 -- OpenSSL 0.9.8g lib_cblock copies (EVP digest, ASN1
// INTEGER/BIT STRING, tasn_utl and the x509v3 POLICY_MAPPINGS / NAME_CONSTRAINTS
// / PCI extension printers).
//
// This is a run of OpenSSL 0.9.8g translation units that Spore linked into the
// unnamed lib_cblock (symbols/lib_names.txt: lib_cblock::FUN_0119a2e0 ...).
// It continues the block covered by slice s01198850 (which ends at 0119a180).
// All 14 addresses come from seven upstream TUs, compiled verbatim as C:
//
//   crypto/evp/digest.c (2)        digest.cpp
//     0119a2e0 EVP_DigestInit_ex      0119a510 EVP_MD_CTX_copy_ex
//
//   crypto/asn1/a_int.c (4)        a_int.cpp
//     0119a850 c2i_ASN1_INTEGER       0119a9c0 ASN1_INTEGER_set
//     0119ab00 BN_to_ASN1_INTEGER     0119abd0 ASN1_INTEGER_to_BN
//
//   crypto/asn1/a_bitstr.c (2)     a_bitstr.cpp
//     0119acf0 c2i_ASN1_BIT_STRING     0119adf0 ASN1_BIT_STRING_set_bit
//
//   crypto/asn1/tasn_utl.c (1)     tasn_utl.cpp
//     0119b180 asn1_do_adb
//
//   crypto/x509v3/v3_pmaps.c (1)   v3_pmaps.cpp
//     0119b300 v2i_POLICY_MAPPINGS
//
//   crypto/x509v3/v3_ncons.c (3)   v3_ncons.cpp
//     0119b480 v2i_NAME_CONSTRAINTS   0119b610 print_nc_ipadd
//     0119b6e0 do_i2r_name_constraints
//
//   crypto/x509v3/v3_pci.c (1)     v3_pci.cpp
//     0119b7e0 i2r_pci
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s0119a2e0_inc  (see manifest.txt)
//
// The include link work/match/scratch_s0119a2e0_inc carries the OpenSSL 0.9.8g
// headers plus the e_os.h/opensslconf.h the Spore build was configured with --
// the same link as slice s01198850, which leaves OPENSSL_EXPORT_VAR_AS_FUNCTION
// undefined (every function above takes the address of the EVP_MD const structs
// directly rather than loading a function).
//
// See manifest.txt for the byte-exact set (14 / 14).

// No function bodies live in this file.  The VAs and their `// @ 0x...` markers
// are in the wrapper sources:
//   slices/s0119a2e0/digest.cpp
//   slices/s0119a2e0/a_int.cpp
//   slices/s0119a2e0/a_bitstr.cpp
//   slices/s0119a2e0/tasn_utl.cpp
//   slices/s0119a2e0/v3_pmaps.cpp
//   slices/s0119a2e0/v3_ncons.cpp
//   slices/s0119a2e0/v3_pci.cpp
