// Slice s011cf390 -- OpenSSL 0.9.8g config loader, ECDH method, RIPEMD160/SHA1
// finalisation and PKCS#5 v2 helpers (lib_cblock).
//
// This slice is a run of the OpenSSL 0.9.8g translation units that Spore linked
// twice: once as lib_openssl (named, see symbols/lib_names.txt) and once as the
// unnamed lib_cblock block.  The 7 addresses below are the lib_cblock copy.
// They come from five upstream TUs, compiled verbatim:
//
//   crypto/conf/conf_def.c (2)    conf_def.cpp
//     011cf390 def_load_bio           011cf910 def_load
//
//   crypto/ecdh/ech_lib.c (1)     ech_lib.cpp
//     011d01c0 ECDH_DATA_new_method
//
//   crypto/ripemd/rmd_dgst.c (2)  rmd_dgst.cpp
//     011d1f30 RIPEMD160_Update       011d21d0 RIPEMD160_Final
//
//   crypto/sha/sha_dgst.c (1)     sha_dgst.cpp
//     011d77e0 SHA_Final
//
//   crypto/evp/p5_crpt2.c (1)     p5_crpt2.cpp
//     011d7b50 PKCS5_v2_PBE_keyivgen
//
// Note on 011d77e0: third_party/cblock_resolution.csv guessed EC_POINTs_mul
// (ec_lib.c) at this address, but the image function reads SHA_CTX offsets
// (num at +0x5c, h0..h4 at +0), uses the SHA padding constant 0x80000000 and
// calls sha_block_host_order at 0x011d2330.  It is SHA_Final from sha_dgst.c,
// and the verbatim TU reproduces it byte-for-byte.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011cf390_inc  (see manifest.txt)
// rmd_dgst.cpp and sha_dgst.cpp also need /Iwork/third_party/build/
// openssl-0.9.8g-d2110920/crypto for md32_common.h.
//
// The include link work/match/scratch_s011cf390_inc/ carries the OpenSSL
// 0.9.8g headers plus the e_os.h/opensslconf.h the Spore build was configured
// with.  As for s01198850, the opensslconf.h must leave
// OPENSSL_EXPORT_VAR_AS_FUNCTION undefined.
//
// See manifest.txt for the byte-exact set.

// No function bodies live in this file.  The VAs and their `// @ 0x...` markers
// are in the wrapper sources:
//   slices/s011cf390/conf_def.cpp
//   slices/s011cf390/ech_lib.cpp
//   slices/s011cf390/rmd_dgst.cpp
//   slices/s011cf390/sha_dgst.cpp
//   slices/s011cf390/p5_crpt2.cpp
