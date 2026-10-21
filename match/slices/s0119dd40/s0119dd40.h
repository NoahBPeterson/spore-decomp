// Slice s0119dd40 -- OpenSSL GENERAL_NAME / X509V3 "subjectAltName" plumbing (lib_cblock):
// the GENERAL_NAME printer and its per-type arms, the subjectAltName extension split/merge
// helpers (do_othername, the email/dirName builders, the section readers) and the small
// ASN1_STRING / string-copy leaves at the end of the block.
//
// These live in the C-library block (lib_cblock, link order); the 32-bit binary passes the
// first argument of 0x0119df30 / 0x0119e010 in EAX (an OpenSSL-era register convention), so
// those two keep a `reg` first parameter.
//
// Flags: /O2 /MD /Gy /TP
#pragma once
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---- minimal shapes of the OpenSSL objects touched here -----------------------------------------------

// ASN1_STRING: { length, type, data } -- the fields the builders read/write.
struct ASN1_STRING {
    int  length;    // +0x00
    int  type;      // +0x04
    u8*  data;      // +0x08
};

// ASN1_OBJECT: the Registered-ID / object-identifier payload.
struct ASN1_OBJECT {
    int  length;    // +0x00
    int  sn;        // +0x04
    int  ln;        // +0x08
    int  nid;       // +0x0c
};

// GENERAL_NAME: { type, d.ptr } where d is a union; only the pointer member is used here.
struct GENERAL_NAME {
    int    type;        // +0x00  GEN_* discriminator (0..8)
    void*  d;           // +0x04  union payload
};

// A X509_NAME_ENTRY as seen through UI_get0_output_string: the value at +8 is an ASN1_STRING.
struct X509_NAME_ENTRY {
    void*        object;    // +0x00
    int          set;       // +0x04
    ASN1_STRING* value;     // +0x08
};

// The CONF_VALUE-ish entry the builders walk (X509V3_CONF_METHOD style record).
struct v3_conf {
    char* section;   // +0x00
    char* name;      // +0x04
    char* value;     // +0x08
};

// ---- callees (extern "C" with the addresses they live at) ---------------------------------------------

extern "C" int   BIO_printf(void* bio, const char* fmt, ...);                   // 0x118a460
extern "C" int   X509_NAME_print_ex(void* out, void* nm, int indent, u32 flags); // 0x11bb130
extern "C" int   i2a_ASN1_OBJECT(void* bp, ASN1_OBJECT* o);                       // 0x1199760
extern "C" void* FUN_01177120(void* bp, const char* s);                           // 0x1177120  X509_EMAIL-ish tail

extern "C" int   X509_get_ext_by_OBJ(void* x, void* obj, int lastpos);           // 0x11801d0
extern "C" void* X509_get_ext(void* x, int loc);                                  // 0x11801f0
extern "C" void* X509V3_EXT_d2i(void* ext);                                       // 0x117f610
extern "C" int   sk_num(void* sk);                                                // 0x117dde0
extern "C" void* sk_value(void* sk, int i);                                       // 0x117ddf0
extern "C" int   sk_push(void* sk, void* p);                                      // 0x117dd00
extern "C" void  sk_free(void* sk);                                               // 0x117ddb0
extern "C" void  sk_pop_free(void* sk, void* freefn);                             // 0x117e030

extern "C" void* X509_get_subject_name(void* x);                                  // 0x117d5a0
extern "C" int   X509_NAME_get_index_by_NID(void* nm, int nid, int lastpos);      // 0x117d3f0
extern "C" void* X509_NAME_get_entry(void* nm, int loc);                          // 0x117d090
extern "C" void* UI_get0_output_string(void* ui);                                 // 0x117d360
extern "C" void* X509_NAME_delete_entry(void* nm, int loc);                       // 0x117d0d0

extern "C" void  ERR_put_error(int lib, int func, int reason, char* file, int line); // 0x1180d50
extern "C" void  ERR_add_error_data(int count, ...);                              // 0x1180a70
extern "C" void* CRYPTO_malloc(int size, const char* file, int line);             // 0x1183410
extern "C" int   EVP_Digest(const void* data, u32 count, u8* md, u32* size, void* type); // 0x119a600
extern "C" int   EVP_MD_CTX_init(void* ctx);                                      // 0x119a2c0
extern "C" int   EVP_MD_CTX_cleanup(void* ctx);                                   // 0x119a480
extern "C" void  BN_init(void* a);                                                // 0x117a9b0
extern "C" void  BN_free(void* a);                                                // 0x117a970
extern "C" void  DH_free(void* dh);                                               // 0x1196740
extern "C" void  EC_KEY_free(void* key);                                          // 0x1191f70
extern "C" void  OPENSSL_cleanse(void* p, u32 n);                                 // 0x1183810
extern "C" void  CRYPTO_free(void* p);                                            // 0x11835c0
extern "C" void* OBJ_txt2obj(const char* s, int no_name);                          // 0x117ffe0
extern "C" void* a2i_IPADDRESS(const char* s);                                     // 0x11ba090
extern "C" void* a2i_IPADDRESS_NC(const char* s);                                  // 0x11ba130
extern "C" int   X509V3_NAME_from_section(void* nm, void* cnf, u32 flags);         // 0x11b9c70
extern "C" int   name_cmp(const char* name, const char* cmp);                      // 0x11b9b10
extern "C" void  ASN1_STRING_free(void* s);                                        // 0x1199db0
extern "C" int   EVP_Digest_va();                                                  // 0x11a9000 (FUN_011a9000)

// intra-slice callees
int   do_othername(char* value, void* cnf);                       // 0x0119e120
void* FUN_0119a0e0(void* s);                                       // 0x0119a0e0  ASN1_STRING_dup-ish
void* FUN_01199d70(int type);                                      // 0x01199d70  ASN1_STRING_type_new
int   FUN_01199cb0(void* s, const void* data, int len);            // 0x01199cb0  ASN1_STRING_set
void* FUN_0117df20();                                              // 0x0117df20  sk_new_null-ish
void* FUN_011b8040();                                              // 0x011b8040  GENERAL_NAME_new
void  FUN_011b8050(void* g);                                       // 0x011b8050  GENERAL_NAME_free
void* FUN_011b9990(void* section, void* out);                      // 0x011b9990  X509V3_get_value_bool-ish
int   FUN_01194f70();                                              // 0x01194f70  X509_NAME_new
void  FUN_01194f80(void* nm);                                      // 0x01194f80  X509_NAME_free
int   FUN_011a5760(void* s);                                       // 0x011a5760
void* FUN_011835c0(void* p);                                       // 0x011835c0 (CRYPTO_free alias)

// Colliding-library helpers reached through the C runtime.
extern "C" void* operator_new_array(void* dst, int value, u32 size);  // 0x11e073e (memset)
extern "C" void* memcpy_(void* dst, const void* src, u32 size);        // 0x11e0744

// ---- the slice's functions ----------------------------------------------------------------------------
// names are Claude-coined (the image has no symbol for any of them).

int   gen_print_119dd40(void* bio, GENERAL_NAME* gen);                       // 0x0119dd40

// These are separate translation units in the original build, so they are never inlined into their callers.
__declspec(noinline) int   gen_free_ext_119df30(void* gen);                          // 0x0119df30 (arg in EAX)
__declspec(noinline) int   gen_email_arm_119e010(void* gen, int del);                // 0x0119e010 (arg in EAX)
__declspec(noinline) int   gen_dirname_119e1c0(void* section, void* out, void* conf); // 0x0119e1c0 (1st arg in EAX)
__declspec(noinline) void* gen_from_conf_119e2a0(void* gen, void* cnf, void* section, v3_conf* c, int nc); // 0x0119e2a0
__declspec(noinline) void* gen_ip_119ea00(void* cnf, void* section, char* value);    // 0x0119ea00
__declspec(noinline) int   gen_hash_119ea60(void* cnf, int* m, u8* name);            // 0x0119ea60
__declspec(noinline) int   ia5string_new_119ec10(void* a, void* b, char* str);       // 0x0119ec10
__declspec(noinline) void* gen_conf_method_119ec80(void* v3conf);                    // 0x0119ec80

void* gens_from_ext_119e520(void* cnf, void* section, void* sk);             // 0x0119e520
void* gens_from_email_119e630(void* cnf, void* section, void* sk);           // 0x0119e630
int   gen_othername_val_119e850(void* cnf, void* section, void* sk);         // 0x0119e850
void* ia5string_dup_119ebb0(void* a, u32* len);                              // 0x0119ebb0
void* gname_alloc_119f650(u32 nid);                                          // 0x0119f650
int   ssl3_new_119f6a0(int s);                                               // 0x0119f6a0
void  ssl3_free_119f720(int s);                                              // 0x0119f720
