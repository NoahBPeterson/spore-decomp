// @ 0x011d77e0  SHA_Final
//
// crypto/sha/sha_dgst.c (OpenSSL 0.9.8g) -- the lib_cblock copy of the
// sha_dgst.c translation unit, i.e. the md32_common.h-generated SHA_Update /
// SHA_Final.  Compiled verbatim from upstream.
//
// The cblock_resolution CSV guessed EC_POINTs_mul here, but the image at
// 0x011d77e0 reads SHA_CTX offsets (num at +0x5c, h0..h4 at +0), uses the
// SHA padding constants (0x80000000) and calls sha_block_host_order at
// 0x011d2330, so it is SHA_Final.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011cf390_inc /Iwork/third_party/build/openssl-0.9.8g-d2110920/crypto  (see manifest.txt)
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/sha/sha_dgst.c"
