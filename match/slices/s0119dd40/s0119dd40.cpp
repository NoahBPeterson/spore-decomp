#include "types.h"
#include "s0119dd40.h"

extern "C" int    __cdecl strcmp(const char*, const char*);
extern "C" void*  FUN_0119adf0(void* s, const char* data, int len);   // 0x119adf0  ASN1_STRING_set-ish
extern "C" void*  FUN_011a9000(int a);                                // 0x11a9000   EVP_sha1-ish
extern "C" int    FUN_011b9b10();                                     // 0x11b9b10   (name_cmp alias)

// @ 0x0119dd40
int gen_print_119dd40(void* bio, GENERAL_NAME* gen)
{
    switch (gen->type) {
    case 0:
        BIO_printf(bio, "othername:<unsupported>");
        return 1;
    case 1:
        BIO_printf(bio, "email:%s", *(char**)((char*)gen->d + 8));
        return 1;
    case 2:
        BIO_printf(bio, "DNS:%s", *(char**)((char*)gen->d + 8));
        return 1;
    case 3:
        BIO_printf(bio, "X400Name:<unsupported>");
        return 1;
    case 4:
        BIO_printf(bio, "DirName: ");
        X509_NAME_print_ex(bio, gen->d, 0, 0x82031f);
        return 1;
    case 5:
        BIO_printf(bio, "EdiPartyName:<unsupported>");
        return 1;
    case 6:
        BIO_printf(bio, "URI:%s", *(char**)((char*)gen->d + 8));
        return 1;
    case 8:
        BIO_printf(bio, "Registered ID");
        i2a_ASN1_OBJECT(bio, (ASN1_OBJECT*)gen->d);
        return 1;
    case 7:
        break;
    }
    {
        ASN1_STRING* s = (ASN1_STRING*)gen->d;
        u8* p = s->data;
        if (s->length == 4) {
            BIO_printf(bio, "IP Address:%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
            return 1;
        }
        if (s->length != 0x10) {
            BIO_printf(bio, "IP Address:<invalid>");
            return 1;
        }
        BIO_printf(bio, "IP Address");
        for (int i = 8; i != 0; --i) {
            BIO_printf(bio, ":%X", (p[0] << 8) | p[1]);
            p += 2;
        }
        FUN_01177120(bio, (const char*)0x1401b70);
        return 1;
    }
}

// @ 0x0119df30
int gen_free_ext_119df30(void* genv)
{
    int* gen = (int*)genv;
    if (gen == 0)
        goto bad;
    if (*gen == 1)
        return 1;
    if (gen[1] == 0)
        goto bad;
    {
        int i = X509_get_ext_by_OBJ((void*)gen[1], (void*)0x55, -1);
        if (i < 0)
            return 1;
        void* ext = X509_get_ext((void*)gen[1], i);
        if (ext == 0)
            goto err7e;
        void* sk = X509V3_EXT_d2i(ext);
        if (sk == 0)
            goto err7e;
        for (int k = 0; k < sk_num(sk); ++k) {
            void* v = sk_value(sk, k);
            if (sk_push((void*)gen[0], v) == 0) {
                ERR_put_error(0x22, 0x7b, 0x41, 0, 0);
                return 0;
            }
        }
        sk_free(sk);
        return 1;
    }
bad:
    ERR_put_error(0x22, 0x7b, 0x7f, 0, 0);
    return 0;
err7e:
    ERR_put_error(0x22, 0x7b, 0x7e, 0, 0);
    return 0;
}

// @ 0x0119e010
int gen_email_arm_119e010(void* genv, int del)
{
    int* gen = (int*)genv;
    void* nm;
    int idx;
    if (gen == 0)
        goto bad;
    if (*gen == 1)
        return 1;
    if (gen[2] == 0) {
        if (gen[3] == 0)
            goto bad;
        nm = (void*)*(int*)(gen[3]);
    } else {
        nm = X509_get_subject_name((void*)gen[2]);
    }
    idx = X509_NAME_get_index_by_NID(nm, 0x30, -1);
    if (idx < 0)
        return 1;
    for (;;) {
        void* entry = X509_NAME_get_entry(nm, idx);
        void* ui = UI_get0_output_string(entry);
        void* dup = FUN_0119a0e0(ui);
        if (del) {
            X509_NAME_delete_entry(nm, idx);
            --idx;
        }
        if (dup == 0)
            goto bad;
        {
            int* g = (int*)FUN_011b8040();
            if (g == 0)
                goto err41;
            g[1] = (int)dup;
            *g = 1;
            if (sk_push((void*)gen[0], g) == 0)
                goto err41;
        }
        idx = X509_NAME_get_index_by_NID(nm, 0x30, idx);
        if (idx < 0)
            return 1;
        dup = 0;
    }
bad:
    ERR_put_error(0x22, 0x7a, 0x7d, 0, 0);
    FUN_011b8050(0);
    ASN1_STRING_free(0);
    return 0;
err41:
    ERR_put_error(0x22, 0x7a, 0x41, 0, 0);
    FUN_011b8050(0);
    ASN1_STRING_free(0);
    return 0;
}

// @ 0x0119e1c0
// NOTE: the original passes its first parameter in EAX (an /O2 register-ABI choice, see the EAX
// convention in 0x0119df30 / 0x0119e010); written here as an ordinary cdecl 3-argument function,
// so the register setup differs.
int gen_dirname_119e1c0(void* section, void* out, void* conf)
{
    int name = FUN_01194f70();
    if (name == 0)
        return 0;
    void* m = gen_conf_method_119ec80(conf);
    if (m == 0) {
        ERR_put_error(0x22, 0x90, 0x96, 0, 0);
        ERR_add_error_data(2, "section=", section);
        FUN_01194f80((void*)name);
        return 0;
    }
    int ok = X509V3_NAME_from_section((void*)name, m, 0x1001);
    if (ok == 0)
        FUN_01194f80((void*)name);
    *(int*)((char*)out + 4) = name;
    return ok;
}

// @ 0x0119e2a0
void* gen_from_conf_119e2a0(void* genv, void* cnf, void* section, v3_conf* c, int nc)
{
    int* gen = (int*)genv;
    char* value = c->value;
    char* name = c->name;
    if (value == 0) {
        ERR_put_error(0x22, 0x75, 0x7c, 0, 0);
        return 0;
    }
    if (gen == 0) {
        gen = (int*)FUN_011b8040();
        if (gen == 0) {
            ERR_put_error(0x22, 0x75, 0x41, 0, 0);
            return 0;
        }
    }
    int t;
    if (name_cmp(name, "email") == 0) {
        t = 1;
        goto str;
    }
    if (name_cmp(name, "URI") == 0) {
        t = 6;
        goto str;
    }
    if (name_cmp(name, "DNS") == 0) {
        t = 2;
        goto str;
    }
    if (name_cmp(name, "RID") == 0) {
        void* o = OBJ_txt2obj(value, 0);
        if (o == 0) {
            ERR_put_error(0x22, 0x75, 0x77, 0, 0);
            ERR_add_error_data(2, "value=", value);
            FUN_011b8050(gen);
            return 0;
        }
        gen[1] = (int)o;
        *gen = 8;
        return gen;
    }
    if (name_cmp(name, "IP") == 0) {
        void* o;
        if (nc == 0)
            o = a2i_IPADDRESS(value);
        else
            o = a2i_IPADDRESS_NC(value);
        gen[1] = (int)o;
        if (o == 0) {
            ERR_put_error(0x22, 0x75, 0x76, 0, 0);
            ERR_add_error_data(2, "value=", value);
            FUN_011b8050(gen);
            return 0;
        }
        *gen = 7;
        return gen;
    }
    if (name_cmp(name, "dirName") == 0) {
        t = 4;
        if (gen_dirname_119e1c0(section, gen, cnf) == 0) {
            ERR_put_error(0x22, 0x75, 0x95, 0, 0);
            FUN_011b8050(gen);
            return 0;
        }
        *gen = t;
        return gen;
    }
    if (name_cmp(name, "otherName") == 0) {
        if (do_othername(value, section) == 0) {
            ERR_put_error(0x22, 0x75, 0x93, 0, 0);
            FUN_011b8050(gen);
            return 0;
        }
        *gen = 0;
        return gen;
    }
    ERR_put_error(0x22, 0x75, 0x75, 0, 0);
    ERR_add_error_data(2, "name=", name);
    FUN_011b8050(gen);
    return 0;
str:
    {
        void* s = FUN_01199d70(0x16);
        gen[1] = (int)s;
        if (s != 0) {
            char* end = value + 1;
            char* p = value;
            char c;
            do {
                c = *p;
                ++p;
            } while (c != 0);
            if (FUN_01199cb0(s, value, (int)(p - end)) != 0) {
                *gen = t;
                return gen;
            }
        }
    }
    ERR_put_error(0x22, 0x75, 0x41, 0, 0);
    FUN_011b8050(gen);
    return 0;
}

// @ 0x0119e520
void* gens_from_ext_119e520(void* cnf, void* section, void* sk)
{
    void* out = FUN_0117df20();
    if (out == 0) {
        ERR_put_error(0x22, 0x99, 0x41, 0, 0);
        return 0;
    }
    for (int i = 0; i < sk_num(sk); ++i) {
        v3_conf* c = (v3_conf*)sk_value(sk, i);
        if (name_cmp(c->name, "issuer") == 0 && c->value != 0 && strcmp(c->value, "copy") == 0) {
            if (gen_free_ext_119df30(section) == 0)
                goto fail;
        } else {
            void* g = gen_from_conf_119e2a0(0, cnf, section, c, 0);
            if (g == 0)
                goto fail;
            sk_push(out, g);
        }
    }
    return out;
fail:
    sk_pop_free(out, (void*)FUN_011b8050);
    return 0;
}

// @ 0x0119e630
void* gens_from_email_119e630(void* cnf, void* section, void* sk)
{
    void* out = FUN_0117df20();
    if (out == 0) {
        ERR_put_error(0x22, 0x9a, 0x41, 0, 0);
        return 0;
    }
    for (int i = 0; i < sk_num(sk); ++i) {
        v3_conf* c = (v3_conf*)sk_value(sk, i);
        if (name_cmp(c->name, "email") == 0 && c->value != 0 && strcmp(c->value, "copy") == 0) {
            if (gen_email_arm_119e010(out, 0) == 0)
                goto fail;
        } else if (name_cmp(c->name, "email") == 0 && c->value != 0 && strcmp(c->value, "move") == 0) {
            if (gen_email_arm_119e010(out, 1) == 0)
                goto fail;
        } else {
            void* g = gen_from_conf_119e2a0(0, cnf, section, c, 0);
            if (g == 0)
                goto fail;
            sk_push(out, g);
        }
    }
    return out;
fail:
    sk_pop_free(out, (void*)FUN_011b8050);
    return 0;
}

// @ 0x0119e850
int gen_othername_val_119e850(void* cnf, void* section, void* sk)
{
    void* s = FUN_01199d70(3);
    if (s == 0) {
        ERR_put_error(0x22, 0x65, 0x41, 0, 0);
        return 0;
    }
    for (int i = 0; i < sk_num(sk); ++i) {
        v3_conf* c = (v3_conf*)sk_value(sk, i);
        v3_conf* t = (v3_conf*)*(int*)((char*)cnf + 0x34);
        for (;;) {
            if (t->name == 0) {
                ERR_put_error(0x22, 0x65, 0x6f, 0, 0);
                ERR_add_error_data(6, "section:", c->section, ",name:", c->name, ",value:", c->value);
                ASN1_STRING_free(s);
                return 0;
            }
            if (strcmp(t->value, c->name) == 0)
                break;
            if (strcmp(t->name, c->name) == 0)
                break;
            t = (v3_conf*)((char*)t + 0xc);
        }
        if (FUN_0119adf0(s, t->section, 1) == 0) {
            ERR_put_error(0x22, 0x65, 0x41, 0, 0);
            ASN1_STRING_free(s);
            return 0;
        }
    }
    return (int)s;
}

// @ 0x0119ea00
void* gen_ip_119ea00(void* cnf, void* section, char* value)
{
    int* p = (int*)FUN_01199d70(4);
    if (p == 0) {
        ERR_put_error(0x22, 0x70, 0x41, 0, 0);
        return 0;
    }
    int loc;
    void* v = FUN_011b9990(value, &loc);
    p[2] = (int)v;
    if (v == 0) {
        ASN1_STRING_free(p);
        return 0;
    }
    *p = loc;
    return p;
}

// @ 0x0119ea60
int gen_hash_119ea60(void* cnf, int* m, u8* name)
{
    u8 digest[64];
    if (strcmp((char*)name, "hash") != 0)
        return (int)gen_ip_119ea00(cnf, m, (char*)name);
    int* p = (int*)FUN_01199d70(4);
    if (p == 0) {
        ERR_put_error(0x22, 0x73, 0x41, 0, 0);
        return 0;
    }
    if (m == 0) {
        ERR_put_error(0x22, 0x73, 0x72, 0, 0);
        ASN1_STRING_free(p);
        return 0;
    }
    if (*m == 1)
        return (int)p;
    int* algo;
    {
        int* obj;
        int  slot;
        if (m[3] == 0) {
            if (m[2] == 0)
                goto err72;
            obj  = *(int**)m[2];
            slot = obj[6];              // *(int*)(obj + 0x18)
        } else {
            obj  = *(int**)m[3];
            slot = obj[5];              // *(int*)(obj + 0x14)
        }
        algo = *(int**)(slot + 4);
        if (algo == 0)
            goto err72;
    }
    {
        u32 outlen;
        void* mt = FUN_011a9000(0);
        EVP_Digest((const void*)algo[2], (u32)*algo, digest, &outlen, mt);
        if (FUN_01199cb0(p, digest, (int)outlen) != 0)
            return (int)p;
    }
    ERR_put_error(0x22, 0x73, 0x41, 0, 0);
    ASN1_STRING_free(p);
    return 0;
err72:
    ERR_put_error(0x22, 0x73, 0x72, 0, 0);
    ASN1_STRING_free(p);
    return 0;
}

// @ 0x0119ebb0
void* ia5string_dup_119ebb0(void* a, u32* len)
{
    if (len == 0 || *len == 0)
        return 0;
    void* d = CRYPTO_malloc(*len + 1, ".\\crypto\\x509v3\\v3_ia5.c", 0x55);
    if (d == 0) {
        ERR_put_error(0x22, 0x95, 0x41, 0, 0);
        return 0;
    }
    memcpy_(d, (void*)len[2], *len);
    *((u8*)d + *len) = 0;
    return d;
}

// @ 0x0119ec10
int ia5string_new_119ec10(void* a, void* b, char* str)
{
    if (str == 0) {
        ERR_put_error(0x22, 100, 0x6b, 0, 0);
        return 0;
    }
    {
        void* s = FUN_01199d70(0x16);
        if (s != 0) {
            char* end = str + 1;
            char* p = str;
            char c;
            do {
                c = *p;
                ++p;
            } while (c != 0);
            if (FUN_01199cb0(s, str, (int)(p - end)) != 0)
                return (int)s;
            ASN1_STRING_free(s);
        }
    }
    ERR_put_error(0x22, 100, 0x41, 0, 0);
    return 0;
}

// @ 0x0119ec80
void* gen_conf_method_119ec80(void* v3conf)
{
    int* c = (int*)v3conf;
    if (c[6] != 0 && c[5] != 0) {
        void* fn = *(void**)(c[5] + 4);
        if (fn != 0)
            return ((void* (*)(int))fn)(c[6]);
    }
    ERR_put_error(0x22, 0x8e, 0x94, 0, 0);
    return 0;
}

// @ 0x0119f650
void* gname_alloc_119f650(u32 nid)
{
    if (nid < 0x41)
        return (void*)(0x15ce770 - (int)nid * 0x28);
    return 0;
}

// @ 0x0119f6a0
int ssl3_new_119f6a0(int s)
{
    void* p = CRYPTO_malloc(0x39c, ".\\ssl\\s3_lib.c", 0x67d);
    if (p == 0)
        return 0;
    operator_new_array(p, 0, 0x39c);
    EVP_MD_CTX_init((char*)p + 0x184);
    EVP_MD_CTX_init((char*)p + 0x194);
    BN_init((char*)p + 0x11c);
    BN_init((char*)p + 0x14c);
    *(void**)(s + 0x58) = p;
    (*(void (**)(int))(*(int*)(s + 8) + 8))(s);
    return 1;
}

// @ 0x0119f720
void ssl3_free_119f720(int s)
{
    if (s == 0)
        return;
    FUN_011a5760((void*)s);
    if (*(void**)(*(char**)(s + 0x58) + 0xe0) != 0)
        CRYPTO_free(*(void**)(*(char**)(s + 0x58) + 0xe0));
    if (*(void**)(*(char**)(s + 0x58) + 0xf0) != 0)
        CRYPTO_free(*(void**)(*(char**)(s + 0x58) + 0xf0));
    if (*(void**)(*(char**)(s + 0x58) + 0x114) != 0)
        CRYPTO_free(*(void**)(*(char**)(s + 0x58) + 0x114));
    if (*(void**)(*(char**)(s + 0x58) + 0x35c) != 0)
        DH_free(*(void**)(*(char**)(s + 0x58) + 0x35c));
    if (*(void**)(*(char**)(s + 0x58) + 0x360) != 0)
        EC_KEY_free(*(void**)(*(char**)(s + 0x58) + 0x360));
    if (*(void**)(*(char**)(s + 0x58) + 0x37c) != 0)
        sk_pop_free(*(void**)(*(char**)(s + 0x58) + 0x37c), (void*)FUN_01194f80);
    EVP_MD_CTX_cleanup(*(char**)(s + 0x58) + 0x184);
    EVP_MD_CTX_cleanup(*(char**)(s + 0x58) + 0x194);
    BN_free(*(char**)(s + 0x58) + 0x11c);
    BN_free(*(char**)(s + 0x58) + 0x14c);
    {
        char* p = *(char**)(s + 0x58);
        OPENSSL_cleanse(p, 0x39c);
        CRYPTO_free(p);
    }
    *(void**)(s + 0x58) = 0;
}
