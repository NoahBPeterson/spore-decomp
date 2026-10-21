// Slice s01193740: a block of OpenSSL (libssl/libcrypto) certificate, cipher-list and
// X509-store helpers that were statically linked into SporeApp.exe. They are reached
// through the "lib_cblock" object in the linker map; the real identities (from the
// embedded source strings) are:
//   ssl_cert.c  : X509/SSL cert helpers (CRYPTO_malloc + ERR_put_error wrappers)
//   ssl_ciph.c  : cipher-string parser / SSL_CIPHER getter
//   x_name.c    : X509_NAME allocator
//   x509_lu.c   : X509_STORE / X509_OBJECT helpers
// (0x1193740-0x1195b16)
//
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// ---------------------------------------------------------------- OpenSSL callees
void* CRYPTO_malloc(int num, const char* file, int line);                    // 0x1183410
void  ERR_put_error(int lib, int func, int reason, const char* file, int line); // 0x1180d50
void  CRYPTO_free(void* p, const char* file, int line);                      // 0x11835c0

int   sk_num(void* sk);                                                      // 0x117dde0
void* sk_value(void* sk, int i);                                             // 0x117ddf0
int   sk_push(void* sk, void* p);                                            // 0x117dd00
void* sk_dup(void* sk);                                                      // 0x117de90
void  sk_set_cmp_func(void* sk, void* fn);                                   // 0x117db70
void  FUN_01193270();                                                        // 0x1193270 (WriteBranch, reg ABI)
void  FUN_01193450(void* a);                                                 // 0x1193450
void  ssl_cipher_collect_ciphers(int a, int b, int c, int d, void* e, void* f); // 0x11933a0
int   FUN_0117b6f0();                                                        // 0x117b6f0 (cmp func)
void  sk_free(void* sk);                                                     // 0x117ddb0
void* sk_dup(void* sk);                                                      // (in ssl_ciph)
void  sk_pop_free(void* sk, void (*fn)(void*));                              // (in ssl_ciph)

int   RSA_up_ref(void* rsa);                                                 // 0x1179c60
void  ssl_cipher_apply_rule(int a, int b, int c, int d, int e, int f, int g, int h, void* i, void* j);
int   FUN_01193740(char* in, int* a, int* b, int* c);                         // 0x1193740
int   ssl_cipher_ptr_id_cmp();                                               // 0x
void  load_builtin_compressions();                                           // 0x1192f50
int   FUN_01193670(int* a, int* b);                                          // 0x1193670
int   FUN_0117df20();                                                        // 0x117df20 (sk_new_null)
int   FUN_01184770();                                                        // 0x1184770
int   FUN_011835c0(void* p);                                                 // 0x11835c0 (CRYPTO_free@line)
int   FUN_011847f0(void* a, int b);                                          // 0x11847f0
int   FUN_0117dde0(void* sk);                                                // 0x117dde0 (sk_num)
void* FUN_0117ddf0(void* sk, int i);                                         // 0x117ddf0 (sk_value)
int   FUN_0117dd00(void* sk, void* p);                                       // 0x117dd00 (sk_push)
void  FUN_0117ddb0(void* sk);                                                // 0x117ddb0 (sk_free)
int   FUN_0117ec00(void* a, void* b, int c, void* d, int e, int f, int g, int h); // 0x117ec00
int   FUN_011990c0(void* a, void* b, void* c);                               // 0x11990c0
int   FUN_0117b100(void* p);                                                 // 0x117b100
void  FUN_011b5fb0(void* a, void* b);                                        // 0x11b5fb0
int   FUN_011b67e0(void* a, int b, void* c, void* d);                        // 0x11b67e0
int   FUN_011b6990(void* a);                                                 // 0x11b6990
void  FUN_011b5f70(void* a, void* b);                                        // 0x11b5f70
void  FUN_01194ef0(void* p);                                                 // 0x1194ef0
void  memset_ext(void* p, int val, size_t n);                                // 0x11e073e
void  CRYPTO_lock(int mode, int type, const char* file, int line);           // 0x1181540
void  CRYPTO_add_lock(void* p, int amount, int type, const char* file, int line); // 0x11815d0
int   EC_KEY_dup(void* k);                                                   // 0x1192130
void  EC_KEY_free(void* k);                                                  // 0x1191f70
void  RSA_free(void* r);                                                     // 0x1179b40
void  DH_free(void* d);                                                      // 0x1196740
void  EVP_PKEY_free(void* k);                                                // 0x1191780
void  X509_free(void* x);                                                    // 0x117cf90
void  X509_OBJECT_up_ref_count(void* p);                                     // 0x1195660
int   X509_OBJECT_retrieve_match(int a, void* b);                            // 0x1195790
void  X509_OBJECT_free_contents(void* p);                                    // 0x11956b0
void* FUN_00e25bd0;                                                          // (eastl helper, unused)

int   DAT_016f2124;                                                          // 0x16f2124
int   DAT_014e6e84;                                                          // 0x14e6e84 (ASN1 item template)
typedef unsigned int uint;

extern "C" int strncmp(const char*, const char*, size_t);

void  BUF_MEM_free(void* b);                                                 // 0x (ssl)
void  X509_STORE_CTX_cleanup(void* c);                                       // 0x11b5ef0
void  X509_STORE_CTX_set_ex_data(void* c, int idx);                          // 0x11b5ee0
int   SSL_get_ex_data_X509_STORE_CTX_idx_0(int ssl);                         // 0x1194840
void  X509_STORE_CTX_set_default(void* c, const char* name);                 // 0x11b5f80
int   ASN1_item_ex_i2d(void* a, void* b, void* tmpl, int tag, int a5);       // 0x (asn1)
void  FUN_01195080(void* p);                                                 // 0x1195080

// The generic "new array" memset used by the allocators.
static inline void memzero(void* p, size_t n) { memset_ext(p, 0, n); }
static inline char* name_unused() { return 0; }
static void memcpy_bytes(void* d, const void* s, int n) {
    char* dp = (char*)d; const char* sp = (const char*)s;
    for (int i = 0; i < n; ++i) dp[i] = sp[i];
}
#define param_4_ (&DAT_014e6e84)

// ---------------------------------------------------------------- 0x1193740
// ssl_ciph.c: parse a single cipher-spec rule from an in/out char cursor (EAX),
// applying rules to the (param_1, param_2) cipher sets.
// @ 0x01193740
int ssl_cipher_process_rulestr(char* in, int* param_1, int* param_2, int* param_3)
{
    char  c = *in;
    int   ret = 1;
    int   rule_id = 0;
    int   use = 0;
    int   algo_ss = 0, algo_mm = 0, algo_kk = 0, algo_aa = 0;
    int   mask_ss = 0, mask_mm = 0;
    int   mask_kk = 0, mask_aa = 0;
    int   local_c = 0, local_10 = 0;

    if (c == '\0') {
        return 1;
    }
    for (;;) {
        if (c == '-') {
            rule_id = 3;
            ++in;
        } else if (c == '+') {
            rule_id = 4;
            ++in;
        } else if (c == '!') {
            rule_id = 2;
            ++in;
        } else if (c == '@') {
            rule_id = 5;
            ++in;
        } else {
            rule_id = 1;
            if (c != ':' && c != ' ' && c != ';' && c != ',') {
                /* fall through to scan */
            } else {
                ++in;
                c = *in;
                if (c == '\0') return ret;
                continue;
            }
        }

        algo_ss = 0; algo_mm = 0; algo_kk = 0; algo_aa = 0;
        mask_ss = 0; mask_mm = 0; mask_kk = 0; mask_aa = 0;
        char*  name = 0;
        size_t len = 0;
        for (;;) {
            name = in;
            len = 0;
            int     found = 0;
            int     idx = 0;
            int     matched = 0;

            while ((c = *in, (c > '@' && c < '[') || (c > '/' && c < ':') ||
                    (c > '`' && c < '{') || c == '-')) {
                ++len;
                ++in;
            }
            if (len == 0) {
                ERR_put_error(0x14, 0xe6, 0x118, 0, 0);
                use = 0;
                ++in;
                break;
            }
            if (rule_id == 5) {
                goto do_strength;
            }
            if (c == '+') {
                ++in;
            }
            idx = 0;
            found = 0;
            while ((matched = *param_3) != 0) {
                if (strncmp(name, *(char**)(matched + 4), len) == 0 &&
                    *(char*)(*(int*)(matched + 4) + len) == '\0') {
                    found = 1;
                    break;
                }
                matched = param_3[++idx];
            }
            if (!found) {
                break;
            } else {
                int* p = (int*)param_3[idx];
                algo_ss |= p[8];
                algo_mm = (~algo_ss & p[3]) | (~p[8] & algo_mm) | (p[3] & algo_mm);
                algo_kk |= p[9];
                algo_aa = (~algo_kk & p[4]) | (~p[9] & algo_aa) | (p[4] & algo_aa);
                use = 1;
                if (*p != 0) {
                    local_c = *(int*)(param_3[idx] + 8);
                    local_10 = *(uint*)(param_3[idx] + 0xc) & 0x3000000;
                    break;
                }
            }
            if (c != '+') break;
        }
        if (rule_id == 5) {
do_strength:
            if (len == 8 && strncmp(name_unused(), "STRENGTH", 8) == 0) {
                if (FUN_01193670(param_1, param_2) == 0) use = 0;
            } else {
                ERR_put_error(0x14, 0xe6, 0x118, 0, 0);
                use = 0;
            }
            for (;;) {
                c = *in;
                if (c == '\0') return use;
                if (c == ':' || c == ' ' || c == ';' || c == ',') break;
                ++in;
            }
        } else if (use) {
            ssl_cipher_apply_rule(local_c, local_10, algo_mm, algo_ss, algo_aa, algo_kk,
                                  rule_id, -1, param_1, param_2);
        } else {
            c = *in;
            if (c == '\0') return use;
            while (c != ':' && c != ' ' && c != ';' && c != ',') {
                ++in;
                c = *in;
                if (c == '\0') return use;
            }
        }
        ret = use;
        if (*in == '\0') return use;
        c = *in;
        if (c == '\0') return ret;
    }
}

// ---------------------------------------------------------------- 0x1193a90
// @ 0x01193a90
int ssl_cipher_strength_sort(int param_1, int* param_2, int* param_3, char* param_4)
{
    int*  alloc = 0;
    int*  names = 0;
    int*  sk = 0;
    void* aliases;
    int   n, i, ok;
    char* p;

    if (param_4 == 0 || param_2 == 0 || param_3 == 0) {
        return 0;
    }
    FUN_01193270();                              // EA::Dasm::PowerPC::WriteBranch (register ABI)
    n = (*(int(**)(void))(param_1 + 0x54))();
    alloc = (int*)CRYPTO_malloc(n * 0x14, ".\\ssl\\ssl_ciph.c", 0x3d8);
    if (alloc == 0) {
        ERR_put_error(0x14, 0xa6, 0x41, 0, 0);
        return 0;
    }
    ssl_cipher_collect_ciphers(param_1, n, (int)&aliases, (int)alloc, (void*)&names, (void*)0);
    aliases = (void*)CRYPTO_malloc(n * 4 + 0xbc, ".\\ssl\\ssl_ciph.c", 0x3ed);
    if (aliases == 0) {
        CRYPTO_free(alloc, ".\\ssl\\ssl_ciph.c", 0x3ed);
        ERR_put_error(0x14, 0xa6, 0x41, 0, 0);
        return 0;
    }
    FUN_01193450(aliases);                       // ssl_cipher_collect_aliases (thiscall)
    ok = 1;
    if (strncmp(param_4, "DEFAULT", 7) == 0) {
        ok = FUN_01193740("AES:ALL:!aNULL:!eNULL:+RC4:@STRENGTH", (int*)&names, (int*)&names, (int*)aliases);
        param_4 += 7;
        if (*param_4 == ':') ++param_4;
        if (ok != 0) goto after_rules;
    }
    for (p = param_4; *p != 0; ++p) { }
    if (p - param_4 != 0) {
        ok = FUN_01193740(param_4, (int*)&names, (int*)&names, (int*)aliases);
    }
after_rules:
    CRYPTO_free(aliases, ".\\ssl\\ssl_ciph.c", 0x3ed);
    if (ok == 0) {
        CRYPTO_free(alloc, ".\\ssl\\ssl_ciph.c", 0x3ed);
        return 0;
    }
    sk = (int*)FUN_0117df20();
    if (sk == 0) {
        CRYPTO_free(alloc, ".\\ssl\\ssl_ciph.c", 0x3ed);
        return 0;
    }
    {
        int* walk = names;
        while (walk != 0) {
            if (walk[1] != 0) {
                sk_push((void*)sk, (void*)walk[0]);
            }
            walk = (int*)walk[0xc / 4];
        }
    }
    CRYPTO_free(alloc, ".\\ssl\\ssl_ciph.c", 0x3ed);
    sk = (int*)sk_dup((void*)sk);
    if (sk == 0) {
        sk_free((void*)0);
        return 0;
    }
    if (*param_2 != 0) sk_free((void*)*param_2);
    *param_2 = (int)0;
    if (*param_3 != 0) sk_free((void*)*param_3);
    *param_3 = (int)sk;
    sk_set_cmp_func((void*)sk, (void*)FUN_0117b6f0);
    return (int)0;
}

// ---------------------------------------------------------------- 0x1193d20
// @ 0x01193d20
int FUN_01193d20()
{
    load_builtin_compressions();
    return DAT_016f2124;
}

// ---------------------------------------------------------------- 0x11948f0
// @ 0x011948f0
void* X509_STORE_CTX_new_0()
{
    int* p = (int*)CRYPTO_malloc(0x5c, ".\\ssl\\ssl_cert.c", 0xa7);
    if (p == 0) {
        ERR_put_error(0x14, 0xa2, 0x41, 0, 0);
        return 0;
    }
    memzero(p, 0x5c);
    *p = (int)(p + 10);
    p[0x16] = 1;
    return p;
}

// ---------------------------------------------------------------- 0x1194940
// @ 0x01194940
int* ssl_cert_dup_0(int* param_1)
{
    int* in = param_1;
    int* p = (int*)CRYPTO_malloc(0x5c, ".\\ssl\\ssl_cert.c", 0xba);
    int  eax, v, i;
    if (p == 0) {
        ERR_put_error(0x14, 0xdd, 0x41, 0, 0);
        return 0;
    }
    memzero(p, 0x5c);
    eax = in[0];
    eax -= (int)param_1;
    eax -= 0x28;
    eax >>= 3;
    *p = (int)((char*)p + eax * 8 + 0x28);
    p[1] = in[1];
    p[2] = in[2];
    p[3] = in[3];
    if (in[4] != 0) {
        RSA_up_ref((void*)in[4]);
        p[4] = in[4];
    }
    p[5] = in[5];
    if (in[6] != 0) {
        p[6] = FUN_011990c0((void*)0x1192e70, (void*)0x1192e50, (void*)in[6]);
        if (p[6] == 0) { eax = 5; goto err; }
        if (*(int*)(in[6] + 0x18) != 0) {
            v = FUN_0117b100((void*)*(int*)(in[6] + 0x18));
            if (v == 0) { eax = 3; goto err; }
            *(int*)(p[6] + 0x18) = v;
        }
        if (*(int*)(in[6] + 0x14) != 0) {
            v = FUN_0117b100((void*)*(int*)(in[6] + 0x14));
            if (v == 0) { eax = 3; goto err; }
            *(int*)(p[6] + 0x14) = v;
        }
    }
    p[7] = in[7];
    if (in[8] != 0) {
        v = EC_KEY_dup((void*)in[8]);
        p[8] = v;
        if (v == 0) { eax = 0x10; goto err; }
    }
    p[9] = in[9];
    i = 0;
    do {
        v = in[i * 2 + 10];
        if (v != 0) {
            p[i * 2 + 10] = v;
            CRYPTO_add_lock((void*)(v + 0x10), 1, 3, ".\\ssl\\ssl_cert.c", 0x108);
        }
        v = in[i * 2 + 0xb];
        if (v != 0) {
            p[i * 2 + 0xb] = v;
            CRYPTO_add_lock((void*)(v + 8), 1, 10, ".\\ssl\\ssl_cert.c", 0x10f);
            switch (i) {
            case 0: case 1: case 2: case 3: case 4: case 5:
                break;
            default:
                ERR_put_error(0x14, 0xdd, 0x112, 0, 0);
            }
        }
        ++i;
    } while (i < 6);
    p[0x16] = 1;
    return p;

err:
    ERR_put_error(0x14, 0xdd, eax, 0, 0);
    if (p[4] != 0) RSA_free((void*)p[4]);
    if (p[6] != 0) DH_free((void*)p[6]);
    if (p[8] != 0) EC_KEY_free((void*)p[8]);
    {
        int* q = p + 0xb;
        int  k = 6;
        do {
            if (q[-1] != 0) X509_free((void*)q[-1]);
            if (*q != 0)    EVP_PKEY_free((void*)*q);
            q += 2;
        } while (--k != 0);
    }
    return 0;
}

// ---------------------------------------------------------------- 0x1194c10
// @ 0x01194c10
int FUN_01194c10(int* p)
{
    int v;
    if (p == 0) {
        ERR_put_error(0x14, 0xde, 0x43, 0, 0);
        return 0;
    }
    if (*p == 0) {
        v = (int)X509_STORE_CTX_new_0();
        *p = v;
        if (v == 0) {
            ERR_put_error(0x14, 0xde, 0x41, 0, 0);
            return 0;
        }
    }
    return 1;
}

// ---------------------------------------------------------------- 0x1194c60
// @ 0x01194c60
void* FUN_01194c60()
{
    char* p = (char*)CRYPTO_malloc(0x4c, ".\\ssl\\ssl_cert.c", 0x1a0);
    if (p == 0) {
        ERR_put_error(0x14, 0xe1, 0x41, 0, 0);
        return 0;
    }
    memzero(p, 0x4c);
    *(int*)(p + 8) = (int)(p + 0xc);
    *(int*)(p + 0x48) = 1;
    return p;
}

// ---------------------------------------------------------------- 0x1194d60
// @ 0x01194d60
int FUN_01194d60(int param_1, int param_2)
{
    uint32_t local_74[0x1d];
    int  ret;

    if (param_2 == 0) return 0;
    if (sk_num((void*)param_2) == 0) return 0;

    void* v = sk_value((void*)param_2, 0);
    if (FUN_011b67e0(local_74, *(int*)(*(int*)(param_1 + 0xd8) + 0xc), v, (void*)param_2) == 0) {
        ERR_put_error(0x14, 0xcf, 0xb, 0, 0);
        return 0;
    }
    if (*(int*)(param_1 + 0x70) != 0) {
        FUN_011b5fb0(local_74, (void*)*(int*)(param_1 + 0x70));
    }
    int idx = SSL_get_ex_data_X509_STORE_CTX_idx_0(param_1);
    X509_STORE_CTX_set_ex_data(local_74, idx);
    char* name = "ssl_client";
    if (*(int*)(param_1 + 0x24) == 0) name = "ssl_server";
    X509_STORE_CTX_set_default(local_74, name);
    if (*(int*)(param_1 + 200) != 0) {
        FUN_011b5f70(local_74, (void*)*(int*)(param_1 + 200));
    }
    int fn = *(int*)(*(int*)(param_1 + 0xd8) + 100);
    if (fn == 0) {
        ret = FUN_011b6990(local_74);
    } else {
        ret = ((int(*)(void*, int))fn)(local_74, *(int*)(*(int*)(param_1 + 0xd8) + 0x68));
    }
    *(int*)(param_1 + 0xe0) = local_74[0];
    X509_STORE_CTX_cleanup(local_74);
    return ret;
}

// ---------------------------------------------------------------- 0x1194e90
// @ 0x01194e90
uint FUN_01194e90(uint* p)
{
    uint v;
    if (p[1] == 0x1000) {
        if ((*p & 0xffffff00) == 0x300 && p[0x16] != 0) {
            return *(uint*)(p[0x16] + 0x37c);
        }
        return 0;
    }
    v = p[0x3b];
    if (v == 0) v = *(uint*)(p[0x36] + 0xa0);
    return v;
}

// ---------------------------------------------------------------- 0x1194fc0
// @ 0x01194fc0
int FUN_01194fc0(int** out)
{
    int* p = (int*)CRYPTO_malloc(0x10, ".\\crypto\\asn1\\x_name.c", 0x74);
    int  v;
    if (p == 0) goto err;
    v = FUN_0117df20();
    p[0] = v;
    if (v == 0) goto err;
    v = FUN_01184770();
    p[2] = v;
    if (v != 0) goto ok;
err:
    ERR_put_error(0xd, 0xab, 0x41, 0, 0);
    if (p != 0) {
        if (p[0] != 0) sk_free((void*)p[0]);
        FUN_011835c0(p);
    }
    return 0;
ok:
    p[1] = 1;
    *out = p;
    return 1;
}

// ---------------------------------------------------------------- 0x1195090
// @ 0x01195090
int FUN_01195090(int* param_1, int* param_2, int param_3, void* param_4, int param_5,
                 int param_6, int param_7, int param_8)
{
    void* src = (void*)*param_2;
    int   local_10 = 0;
    int*  local_8 = 0;
    void* local_c = src;
    int   n = FUN_0117ec00(&local_10, &local_c, param_3, param_4, param_5, param_6, param_7, param_8);
    if (n > 0) {
        int* pu = (int*)*param_1;
        int  total = n;
        if (pu != 0) {
            BUF_MEM_free((void*)pu[2]);
            sk_pop_free((void*)*pu, FUN_01194ef0);
            FUN_011835c0(pu);
            *param_1 = 0;
        }
        if (FUN_01194fc0(&local_8) == 0 || FUN_011847f0((void*)local_8[2], (int)local_c - (int)src) == 0) {
            ERR_put_error(0xd, 0x9e, 0x3a, 0, 0);
            return 0;
        }
        memcpy_bytes(*(void**)(local_8[2] + 4), src, (int)local_c - (int)src);
        int outer = 0;
        int cnt = sk_num((void*)local_10);
        if (cnt > 0) {
            do {
                void* inner_sk = sk_value((void*)local_10, outer);
                int   j = 0;
                int   ic = sk_num(inner_sk);
                if (ic > 0) {
                    do {
                        int it = (int)sk_value(inner_sk, j);
                        *(int*)(it + 8) = outer;
                        if (sk_push((void*)*local_8, (void*)it) == 0) {
                            ERR_put_error(0xd, 0x9e, 0x3a, 0, 0);
                            return 0;
                        }
                        ++j;
                        ic = sk_num(inner_sk);
                    } while (j < ic);
                }
                sk_free(inner_sk);
                ++outer;
                cnt = sk_num((void*)local_10);
            } while (outer < cnt);
        }
        sk_free((void*)local_10);
        local_8[1] = 0;
        *param_1 = (int)local_8;
        *param_2 = (int)local_c;
        return total;
    }
    return n;
}

// ---------------------------------------------------------------- 0x1195230
// @ 0x01195230
int FUN_01195230(int** ctx)
{
    int  i = 0;
    int  last = -1;
    int  local_c = FUN_0117df20();
    int  local_8 = 0;
    int  n;
    int  total;

    if (local_c == 0) goto fail;
    n = sk_num((void*)*ctx);
    if (n > 0) {
        do {
            int it = (int)sk_value((void*)*ctx, i);
            if (*(int*)(it + 8) != last) {
                local_8 = FUN_0117df20();
                if (local_8 == 0) goto fail;
                last = sk_push((void*)local_c, (void*)local_8);
                if (last == 0) goto fail;
                last = *(int*)(it + 8);
            }
            if (sk_push((void*)local_8, (void*)it) == 0) goto fail;
            ++i;
            n = sk_num((void*)*ctx);
        } while (i < n);
    }
    total = ASN1_item_ex_i2d((void*)&local_c, 0, param_4_, -1, -1);
    if (FUN_011847f0((void*)ctx[2], total) != 0) {
        int local_4 = *(int*)((int)ctx[2] + 4);
        ASN1_item_ex_i2d((void*)&local_c, (void*)&local_4, param_4_, -1, -1);
        sk_pop_free((void*)local_c, FUN_01195080);
        ctx[1] = 0;
        return total;
    }
fail:
    sk_pop_free((void*)local_c, FUN_01195080);
    ERR_put_error(0xd, 0xcb, 0x41, 0, 0);
    return -1;
}

// ---------------------------------------------------------------- 0x1195a40
// @ 0x01195a40
int FUN_01195a40(int param_1, int param_2)
{
    int* p;
    int  v;
    int  ret = 1;

    if (param_2 == 0) {
        return 0;
    }
    p = (int*)CRYPTO_malloc(8, ".\\crypto\\x509\\x509_lu.c", 0x16c);
    if (p == 0) {
        ERR_put_error(0xb, 0x7d, 0x41, 0, 0);
        return 0;
    }
    p[0] = 2;
    p[1] = param_2;
    CRYPTO_lock(9, 0xb, ".\\crypto\\x509\\x509_lu.c", 0x175);
    X509_OBJECT_up_ref_count(p);
    v = X509_OBJECT_retrieve_match(*(int*)(param_1 + 4), p);
    if (v != 0) {
        X509_OBJECT_free_contents(p);
        FUN_011835c0(p);
        ERR_put_error(0xb, 0x7d, 0x65, 0, 0);
        ret = 0;
    } else {
        sk_push((void*)*(int*)(param_1 + 4), (void*)p);
    }
    CRYPTO_lock(10, 0xb, ".\\crypto\\x509\\x509_lu.c", 0x182);
    return ret;
}
