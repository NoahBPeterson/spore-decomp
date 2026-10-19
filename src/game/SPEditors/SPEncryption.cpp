// src/game/SPEditors/SPEncryption.cpp -- migrated from slice(s) s0060b730 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEncryption.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Messaging/IHandler.h"
#include "EA/Messaging/Server.h"
#include "EA/IO/IStream.h"
#include "EA/IO/MemoryStream.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "evp_cipher_ctx_st.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);  // E8 call (0x011e0744)
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern char gEmptyString[];  // 0x01667bac
extern "C" int RAND_pseudo_bytes(unsigned char* buf, int num);  // 0x01178650
extern "C" void Memset32(void* pDest, uint32_t value, uint32_t count);  // 0x0092cb00
#pragma intrinsic(strlen)
#pragma intrinsic(_InterlockedExchange)
#include "eastl/allocator.h"
#include "eastl/string.h"
#include "bio_st.h"

// ---- items of slice s0060b730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);  // E8 call (0x011e0744)
extern "C" unsigned int __cdecl strlen(const char*);
extern char gEmptyString[];  // 0x01667bac
namespace eastl {
struct allocator_s0060_b730 {
  allocator_s0060_b730() {}
};
}
namespace eastl {
int CompareI(const char* p1, const char* p2, unsigned int n);  // 0x005f7870
}
namespace eastl {
template <typename T>
inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
}
namespace eastl {
template <typename T, typename A = allocator_s0060_b730>
struct basic_string_s0060_b730 {
  typedef unsigned int size_type;
  enum { npos = -1 };
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;

  basic_string_s0060_b730() : mpBegin(0), mpEnd(0), mpCapacity(0) {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  basic_string_s0060_b730(const basic_string_s0060_b730& x);  // 0x0057cb10
  __forceinline ~basic_string_s0060_b730() { DeallocateSelf(); }
  __forceinline void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, mpCapacity - mpBegin);
  }
  void DoFree(T* p, size_type) {
    if (p) EASTL_allocator_deallocate(p);
  }
  __forceinline basic_string_s0060_b730(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) {
    const size_type n = (size_type)strlen(p);
    AllocateSelf(n + 1);
    T* const pDest = mpBegin;
    memcpy(pDest, p, n);
    mpEnd = pDest + n;
    *mpEnd = 0;
  }
  size_type size() const { return (size_type)(mpEnd - mpBegin); }
  const T* c_str() const { return mpBegin; }
  basic_string_s0060_b730& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0
  basic_string_s0060_b730& assign(const T* p, size_type n);          // 0x0060bcd0
  basic_string_s0060_b730& assign(const T* p);                       // 0x006a4380
  basic_string_s0060_b730& append(const T* pBegin, const T* pEnd);   // 0x00455d60
  basic_string_s0060_b730& append(const T* p);                       // 0x0060c4e0
  basic_string_s0060_b730& sprintf(const T* pFormat, ...);           // 0x00472fe0
  void AllocateSelf(size_type n);                         // 0x00475ab0
  __forceinline basic_string_s0060_b730& operator=(const basic_string_s0060_b730& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  int compare(const basic_string_s0060_b730& x) const;                          // 0x00609fe0
  int comparei(const basic_string_s0060_b730& x) const;                         // 0x00609ee0
  static int comparei(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2) {
    const int n1 = (int)(pEnd1 - pBegin1);
    const int n2 = (int)(pEnd2 - pBegin2);
    const int nMin = min_alt(n1, n2);
    const int cmp = CompareI(pBegin1, pBegin2, (size_type)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
  }
  size_type rfind(T c, size_type position) const;                    // 0x00609f40
  size_type find(const basic_string_s0060_b730& x, size_type position) const;   // 0x00609f90
  size_type find(T c, size_type position) const;                     // 0x00607580
  basic_string_s0060_b730 substr(size_type position, size_type n) const;        // 0x006082a0
};
}
typedef eastl::basic_string_s0060_b730<char> string8;
struct evp_cipher_st;
struct bio_st_s0060_b730;
struct bio_method_st;
struct evp_cipher_ctx_st_s0060_b730 {
  uint32_t pad[35];  // size 0x8c
};
extern "C" int RAND_pseudo_bytes(unsigned char* buf, int num);  // 0x01178650
extern "C" void EVP_CIPHER_CTX_init(evp_cipher_ctx_st_s0060_b730* ctx);     // 0x011765f0
extern "C" int EVP_CIPHER_CTX_cleanup(evp_cipher_ctx_st_s0060_b730* ctx);   // 0x01176a20
extern "C" const evp_cipher_st* EVP_aes_256_cbc();               // 0x01178390 (exact cipher unverified)
extern "C" int EVP_EncryptInit_ex(evp_cipher_ctx_st_s0060_b730* ctx, const evp_cipher_st* type, void* impl, const unsigned char* key,
const unsigned char* iv);  // 0x01176d50
extern "C" int EVP_EncryptUpdate(evp_cipher_ctx_st_s0060_b730* ctx, unsigned char* out, int* outl, const unsigned char* in, int inl);  // 0x01176610
extern "C" int EVP_EncryptFinal_ex(evp_cipher_ctx_st_s0060_b730* ctx, unsigned char* out, int* outl);  // 0x01176770
extern "C" const bio_method_st* BIO_f_base64();                 // 0x01177970
extern "C" const bio_method_st* BIO_s_mem();                    // 0x011774f0
extern "C" bio_st_s0060_b730* BIO_new(const bio_method_st* type);          // 0x01177470
extern "C" void BIO_set_flags(bio_st_s0060_b730* b, int flags);            // 0x01176fb0
extern "C" bio_st_s0060_b730* BIO_push(bio_st_s0060_b730* b, bio_st_s0060_b730* append);         // 0x01177380
extern "C" int BIO_write(bio_st_s0060_b730* b, const void* data, int len); // 0x01177070
extern "C" long BIO_ctrl(bio_st_s0060_b730* b, int cmd, long larg, void* parg);  // 0x01177260
extern "C" void BIO_free_all(bio_st_s0060_b730* a);                        // 0x01177420
extern "C" void Memset32(void* pDest, uint32_t value, uint32_t count);  // 0x0092cb00
const uint32_t kAESKeyWords = 8;
// ---- items of slice s0060b730 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void EVP_CIPHER_CTX_init(evp_cipher_ctx_st_s0060_b730* ctx);     // 0x011765f0
extern "C" int EVP_CIPHER_CTX_cleanup(evp_cipher_ctx_st_s0060_b730* ctx);   // 0x01176a20
extern "C" const evp_cipher_st* EVP_aes_256_cbc();               // 0x01178390 (exact cipher unverified)
extern "C" int EVP_EncryptInit_ex(evp_cipher_ctx_st_s0060_b730* ctx, const evp_cipher_st* type, void* impl, const unsigned char* key,
const unsigned char* iv);  // 0x01176d50
extern "C" int EVP_EncryptUpdate(evp_cipher_ctx_st_s0060_b730* ctx, unsigned char* out, int* outl, const unsigned char* in, int inl);  // 0x01176610
extern "C" int EVP_EncryptFinal_ex(evp_cipher_ctx_st_s0060_b730* ctx, unsigned char* out, int* outl);  // 0x01176770
extern "C" const bio_method_st* BIO_f_base64();                 // 0x01177970
extern "C" const bio_method_st* BIO_s_mem();                    // 0x011774f0
extern "C" bio_st_s0060_b730* BIO_new(const bio_method_st* type);          // 0x01177470
extern "C" void BIO_set_flags(bio_st_s0060_b730* b, int flags);            // 0x01176fb0
extern "C" bio_st_s0060_b730* BIO_push(bio_st_s0060_b730* b, bio_st_s0060_b730* append);         // 0x01177380
extern "C" int BIO_write(bio_st_s0060_b730* b, const void* data, int len); // 0x01177070
extern "C" long BIO_ctrl(bio_st_s0060_b730* b, int cmd, long larg, void* parg);  // 0x01177260
extern "C" void BIO_free_all(bio_st_s0060_b730* a);                        // 0x01177420

// @ 0x0060bc90
namespace  {
void GetAESKey(unsigned char * pKey)
{
  pKey[0] = 0x44db12e;
  pKey[1] = 0x5005f78;
  pKey[2] = 0x50fad80;
  pKey[3] = 0xb7bcef68;
  pKey[4] = 0x662da01;
  pKey[5] = 0x4fd2bd3;
  pKey[6] = 0x662d9ed;
  pKey[7] = 0x5005f78;
}
}  // namespace 

// @ 0x0060bcd0
template <> string8& string8::assign(const char* p, size_type n)
{
  return assign(p, p + n);
}

// @ 0x0060bcf0
void Encrypt(const string8& plain, string8& out)
{
  if (plain.mpEnd - plain.mpBegin == 0) {
    out.assign("", "");
    return;
  }
  unsigned char iv[16];
  struct {
    unsigned char iv[16];
    unsigned char data[0x70];
  } packet;
  RAND_pseudo_bytes(iv, 16);
  ((uint32_t*)packet.iv)[0] = ((uint32_t*)iv)[0];
  ((uint32_t*)packet.iv)[1] = ((uint32_t*)iv)[1];
  ((uint32_t*)packet.iv)[2] = ((uint32_t*)iv)[2];
  ((uint32_t*)packet.iv)[3] = ((uint32_t*)iv)[3];
  evp_cipher_ctx_st_s0060_b730 ctx;
  EVP_CIPHER_CTX_init(&ctx);
  uint32_t key[64];
  key[0] = 0x44db12e;
  key[1] = 0x5005f78;
  key[2] = 0x50fad80;
  key[3] = 0xb7bcef68;
  key[4] = 0x662da01;
  key[5] = 0x4fd2bd3;
  key[6] = 0x662d9ed;
  key[7] = 0x5005f78;
  if (EVP_EncryptInit_ex(&ctx, EVP_aes_256_cbc(), 0, (const unsigned char*)key, iv) > 0) {
    int nOut = 0x70;
    if (EVP_EncryptUpdate(&ctx, packet.data, &nOut, (const unsigned char*)plain.c_str(), (int)plain.size()) > 0) {
      const int nFirst = nOut;
      nOut = 0x70 - nOut;
      if (EVP_EncryptFinal_ex(&ctx, packet.data + nFirst, &nOut) > 0) {
        bio_st_s0060_b730* const pBase64 = BIO_new(BIO_f_base64());
        bio_st_s0060_b730* const pMem = BIO_new(BIO_s_mem());
        BIO_set_flags(pBase64, 0x100);
        bio_st_s0060_b730* const pChain = BIO_push(pBase64, pMem);
        if (pChain) {
          BIO_write(pChain, packet.iv, nFirst + 0x10 + nOut);
          BIO_ctrl(pChain, 11, 0, 0);
          char* pData;
          nOut = (int)BIO_ctrl(pChain, 3, 0, &pData);
          out.assign(pData, nOut);
        }
        BIO_free_all(pChain);
      }
    }
  }
  Memset32(key, 0, kAESKeyWords);
  EVP_CIPHER_CTX_cleanup(&ctx);
}
