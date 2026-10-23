// Slice s0119b890 -- OpenSSL X509V3 config parsers, recovered from lib_cblock.
//
//   process_pci_value            0119b890  v3_pci.c  (static, ecx/esi register ABI)
//   r2i_pci                      0119bcd0  v3_pci.c
//   v2i_POLICY_CONSTRAINTS       0119bfd0  v3_pcons.c
//   i2v_AUTHORITY_INFO_ACCESS    0119c170  v3_info.c
//   v2i_AUTHORITY_INFO_ACCESS    0119c2e0  v3_info.c
//   SXNET_add_id_INTEGER         0119c5b0  v3_sxnet.c
//   sxnet_v2i                    0119c730  v3_sxnet.c (SXNET_add_id_asc inlined)
//   v2i_EXTENDED_KEY_USAGE       0119c890  v3_extku.c
//   v2i_crld                     0119ca30  v3_crld.c
//
// Flags: /O2 /MD /Gy /TP
#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;

struct ASN1_OBJECT;
struct ASN1_INTEGER;
struct ASN1_OCTET_STRING;
struct X509V3_CTX;
struct X509V3_EXT_METHOD;
struct CONF_VALUE;
struct SXNET;
struct SXNETID;

// ---------------------------------------------------------------------------
// Callees
// ---------------------------------------------------------------------------
extern "C" void  ERR_put_error(int lib, int func, int reason, const char* file, int line); // 0x1180d50
extern "C" void  ERR_add_error_data(int num, ...);                                          // 0x1180a70
extern "C" void* OBJ_txt2obj(const char* s, int no_name);                                   // 0x117ffe0
extern "C" int   OBJ_obj2nid(const void* o);                                                // 0x117fa60
extern "C" int   X509V3_get_value_int(CONF_VALUE* cnf, ASN1_INTEGER** aint);                // 0x11b9820
extern "C" void* X509V3_parse_list(const char* line);                                       // 0x11b9d20
extern "C" void* X509V3_get_section(X509V3_CTX* ctx, char* section);                        // 0x119ec80
extern "C" void  X509V3_section_free(X509V3_CTX* ctx, void* section);                       // 0x119ecc0
extern "C" u8*   string_to_hex(const char* str, long* len);                                 // 0x11b9990
extern "C" void* BIO_new_file(const char* filename, const char* mode);                      // 0x117b240
extern "C" int   BIO_read(void* b, void* data, int len);                                    // 0x1176fc0
extern "C" int   BIO_test_flags(void* b, int flags);                                        // 0x1176fa0
extern "C" void* CRYPTO_malloc(int num, const char* file, int line);                        // 0x1183410
extern "C" void* CRYPTO_realloc(void* addr, int num, const char* file, int line);           // 0x1183490
extern "C" void  CRYPTO_free(void* addr);                                                   // 0x11835c0
extern "C" int   BUF_strlcpy(char* dst, const char* src, int size);                         // 0x1184980
extern "C" int   BUF_strlcat(char* dst, const char* src, int size);                         // 0x11849c0
extern "C" void* sk_new_null(void);                                                         // 0x117df20
extern "C" int   sk_num(void* sk);                                                          // 0x117dde0
extern "C" void* sk_value(void* sk, int i);                                                 // 0x117ddf0
extern "C" int   sk_push(void* sk, void* data);                                             // 0x117dd00
extern "C" void  sk_pop_free(void* sk, void* func);                                         // 0x117e030
extern "C" void* ASN1_item_new(const void* it);                                             // 0x1198550
extern "C" void  ASN1_item_free(void* val, const void* it);                                 // 0x11988e0
extern "C" void  ASN1_OBJECT_free(void* a);                                                 // 0x11998c0
extern "C" int   ASN1_STRING_set(void* str, const void* data, int len);                     // 0x1199cb0
extern "C" int   ASN1_INTEGER_set(void* a, long v);                                         // 0x119a9c0
extern "C" void  ASN1_INTEGER_free(void* a);                                                // 0x1197400
extern "C" void* ASN1_OCTET_STRING_new(void);                                               // 0x1197480
extern "C" void  ASN1_OCTET_STRING_free(void* a);                                           // 0x1197490
extern "C" int   i2t_ASN1_OBJECT(char* buf, int buf_len, const void* a);                    // 0x1199740
extern "C" void* i2v_GENERAL_NAME(void* method, void* gen, void* ret);                      // 0x119dac0
extern "C" int   v2i_GENERAL_NAME_ex(void* gen, void* method, void* ctx,
                                     CONF_VALUE* cnf, int is_nc);                           // 0x119e2a0
extern "C" void* v2i_GENERAL_NAME(void* method, void* ctx, CONF_VALUE* cnf);                // 0x119e500
extern "C" void* SXNET_get_id_INTEGER(void* sx, void* zone);                                // 0x119c550
extern "C" void* s2i_ASN1_INTEGER(void* def, const char* str);                              // 0x11b93f0
extern "C" void* PROXY_CERT_INFO_EXTENSION_new(void);                                       // 0x11b6dc0
extern "C" void  X509V3_conf_free(CONF_VALUE* val);                                         // 0x11b92d0
extern "C" int   SXNET_add_id_asc(SXNET** psx, char* zone, char* user, int userlen);        // no addr
extern "C" unsigned int __cdecl strlen(const char* s);
extern "C" int          __cdecl strcmp(const char* a, const char* b);
extern "C" void  GENERAL_NAME_free(void* gen);                                              // 0x11b8050
extern "C" void* GENERAL_NAMES_new(void);                                                   // 0x11b8070
extern "C" void  GENERAL_NAMES_free(void* gens);                                            // 0x11b8080
extern "C" void  ACCESS_DESCRIPTION_free(void* acc);                                        // 0x119c150
extern "C" void  DIST_POINT_free(void* point);                                              // 0x119ca10
extern "C" void* memcpy_(void* dst, const void* src, u32 size);                             // 0x11e0744
extern "C" __declspec(dllimport) int __cdecl strncmp(const char*, const char*, u32);        // 0x13cc4fc
extern "C" __declspec(dllimport) char* __cdecl strchr(const char*, int);                    // 0x13cc504
extern "C" __declspec(dllimport) char* __cdecl strncpy(char*, const char*, u32);            // 0x13cc4f4

// ---------------------------------------------------------------------------
// Types
// ---------------------------------------------------------------------------
struct ASN1_OBJECT {
    int foo;
};

struct CONF_VALUE {
    char* section;
    char* name;
    char* value;
};

struct GENERAL_NAME {
    int type;
    union {
        void* ptr;
        ASN1_OCTET_STRING* ia5;
    } d;
};

struct ACCESS_DESCRIPTION {
    ASN1_OBJECT* method;
    GENERAL_NAME* location;
};

struct POLICY_CONSTRAINTS {
    ASN1_INTEGER* requireExplicitPolicy;
    ASN1_INTEGER* inhibitPolicyMapping;
};

struct DIST_POINT_NAME {
    int type;
    union {
        void* fullname;
        void* relativename;
    } name;
};

struct DIST_POINT {
    DIST_POINT_NAME* distpoint;
    void* reasons;
    void* CRLissuer;
};

struct PROXY_POLICY {
    ASN1_OBJECT* policyLanguage;
    ASN1_OCTET_STRING* policy;
};

struct PROXY_CERT_INFO_EXTENSION {
    ASN1_INTEGER* pcPathLengthConstraint;
    PROXY_POLICY* proxyPolicy;
};

struct ASN1_OCTET_STRING {
    int length;
    int type;
    u8* data;
};

struct SXNET {
    ASN1_INTEGER* version;
    void* ids;
};

struct SXNETID {
    ASN1_INTEGER* zone;
    ASN1_OCTET_STRING* user;
};

// ASN.1 item descriptors for the objects built here.
extern "C" char ASN1_ITEM_PROXY_CERT_INFO_EXTENSION[];   // 0x14e7db0
extern "C" char ASN1_ITEM_POLICY_CONSTRAINTS[];          // 0x14e7db0
extern "C" char ASN1_ITEM_ACCESS_DESCRIPTION[];          // 0x14e7ea0
extern "C" char ASN1_ITEM_SXNET[];                       // 0x14e8040
extern "C" char ASN1_ITEM_SXNETID[];                     // 0x14e7ffc
extern "C" char ASN1_ITEM_DIST_POINT[];                  // 0x14e8354
extern "C" char ASN1_ITEM_DIST_POINT_NAME[];             // 0x14e82fc

// ---------------------------------------------------------------------------
// process_pci_value -- file-local static compiled with ecx=language, esi=policy.
// ---------------------------------------------------------------------------
// @ 0x0119b890
static int process_pci_value(CONF_VALUE* val, ASN1_OBJECT** language,
                             ASN1_INTEGER** pathlen, ASN1_OCTET_STRING** policy)
{
    int free_policy = 0;

    if (strcmp(val->name, "language") == 0) {
        if (*language) {
            ERR_put_error(0x22, 0x96, 0x9b, 0, 0);
            ERR_add_error_data(6, "section:", val->section, ",name:", val->name,
                               ",value:", val->value);
            return 0;
        }
        if (!(*language = (ASN1_OBJECT*)OBJ_txt2obj(val->value, 0))) {
            ERR_put_error(0x22, 0x96, 0x6e, 0, 0);
            ERR_add_error_data(6, "section:", val->section, ",name:", val->name,
                               ",value:", val->value);
            return 0;
        }
    } else if (strcmp(val->name, "pathlen") == 0) {
        if (*pathlen) {
            ERR_put_error(0x22, 0x96, 0x9d, 0, 0);
            ERR_add_error_data(6, "section:", val->section, ",name:", val->name,
                               ",value:", val->value);
            return 0;
        }
        if (!X509V3_get_value_int(val, pathlen)) {
            ERR_put_error(0x22, 0x96, 0x9c, 0, 0);
            ERR_add_error_data(6, "section:", val->section, ",name:", val->name,
                               ",value:", val->value);
            return 0;
        }
    } else if (strcmp(val->name, "policy") == 0) {
        u8* tmp_data = 0;
        long val_len;
        if (!*policy) {
            *policy = (ASN1_OCTET_STRING*)ASN1_OCTET_STRING_new();
            if (!*policy) {
                ERR_put_error(0x22, 0x96, 0x41, 0, 0);
                ERR_add_error_data(6, "section:", val->section, ",name:", val->name,
                                   ",value:", val->value);
                return 0;
            }
            free_policy = 1;
        }
        if (strncmp(val->value, "hex:", 4) == 0) {
            u8* tmp_data2 = string_to_hex(val->value + 4, &val_len);

            if (!tmp_data2) goto err;

            tmp_data = (u8*)CRYPTO_realloc((*policy)->data,
                                           (*policy)->length + (int)val_len + 1,
                                           ".\\crypto\\x509v3\\v3_pci.c", 0x86);
            if (tmp_data) {
                (*policy)->data = tmp_data;
                memcpy_(&(*policy)->data[(*policy)->length], tmp_data2, val_len);
                (*policy)->length += (int)val_len;
                (*policy)->data[(*policy)->length] = 0;
            }
        } else if (strncmp(val->value, "file:", 5) == 0) {
            u8 buf[2048];
            int n;
            void* b = BIO_new_file(val->value + 5, "r");
            if (!b) {
                ERR_put_error(0x22, 0x96, 0x20, 0, 0);
                ERR_add_error_data(6, "section:", val->section, ",name:", val->name,
                                   ",value:", val->value);
                goto err;
            }
            while ((n = BIO_read(b, buf, sizeof(buf))) > 0
                   || (n == 0 && BIO_test_flags(b, 8))) {
                if (!n) continue;

                tmp_data = (u8*)CRYPTO_realloc((*policy)->data,
                                               (*policy)->length + n + 1,
                                               ".\\crypto\\x509v3\\v3_pci.c", 0xa1);

                if (!tmp_data) break;

                (*policy)->data = tmp_data;
                memcpy_(&(*policy)->data[(*policy)->length], buf, n);
                (*policy)->length += n;
                (*policy)->data[(*policy)->length] = 0;
            }

            if (n < 0) {
                ERR_put_error(0x22, 0x96, 0x20, 0, 0);
                ERR_add_error_data(6, "section:", val->section, ",name:", val->name,
                                   ",value:", val->value);
                goto err;
            }
        } else if (strncmp(val->value, "text:", 5) == 0) {
            val_len = (long)strlen(val->value + 5);
            tmp_data = (u8*)CRYPTO_realloc((*policy)->data,
                                           (*policy)->length + (int)val_len + 1,
                                           ".\\crypto\\x509v3\\v3_pci.c", 0xb8);
            if (tmp_data) {
                (*policy)->data = tmp_data;
                memcpy_(&(*policy)->data[(*policy)->length], val->value + 5, val_len);
                (*policy)->length += (int)val_len;
                (*policy)->data[(*policy)->length] = 0;
            }
        } else {
            ERR_put_error(0x22, 0x96, 0x98, 0, 0);
            ERR_add_error_data(6, "section:", val->section, ",name:", val->name,
                               ",value:", val->value);
            goto err;
        }
        if (!tmp_data) {
            ERR_put_error(0x22, 0x96, 0x41, 0, 0);
            ERR_add_error_data(6, "section:", val->section, ",name:", val->name,
                               ",value:", val->value);
            goto err;
        }
    }
    return 1;
err:
    if (free_policy) {
        ASN1_OCTET_STRING_free(*policy);
        *policy = 0;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x0119bcd0
// ---------------------------------------------------------------------------
PROXY_CERT_INFO_EXTENSION* r2i_pci(X509V3_EXT_METHOD* method,
                                   X509V3_CTX* ctx, char* value);

PROXY_CERT_INFO_EXTENSION* r2i_pci(X509V3_EXT_METHOD* method,
                                   X509V3_CTX* ctx, char* value)
{
    PROXY_CERT_INFO_EXTENSION* pci = 0;
    void* vals;
    ASN1_OBJECT* language = 0;
    ASN1_INTEGER* pathlen = 0;
    ASN1_OCTET_STRING* policy = 0;
    int i, j;

    vals = X509V3_parse_list(value);
    for (i = 0; i < sk_num(vals); i++) {
        CONF_VALUE* cnf = (CONF_VALUE*)sk_value(vals, i);
        if (!cnf->name || (*cnf->name != '@' && !cnf->value)) {
            ERR_put_error(0x22, 0x9b, 0x99, 0, 0);
            ERR_add_error_data(6, "section:", cnf->section, ",name:", cnf->name,
                               ",value:", cnf->value);
            goto err;
        }
        if (*cnf->name == '@') {
            void* sect;
            int success_p = 1;

            sect = X509V3_get_section(ctx, cnf->name + 1);
            if (!sect) {
                ERR_put_error(0x22, 0x9b, 0x87, 0, 0);
                ERR_add_error_data(6, "section:", cnf->section, ",name:", cnf->name,
                                   ",value:", cnf->value);
                goto err;
            }
            for (j = 0; success_p && j < sk_num(sect); j++) {
                success_p =
                    process_pci_value((CONF_VALUE*)sk_value(sect, j),
                                      &language, &pathlen, &policy);
            }
            X509V3_section_free(ctx, sect);
            if (!success_p) goto err;
        } else {
            if (!process_pci_value(cnf, &language, &pathlen, &policy)) {
                ERR_add_error_data(6, "section:", cnf->section, ",name:", cnf->name,
                                   ",value:", cnf->value);
                goto err;
            }
        }
    }

    /* Language is mandatory */
    if (!language) {
        ERR_put_error(0x22, 0x9b, 0x9a, 0, 0);
        goto err;
    }
    i = OBJ_obj2nid(language);
    if ((i == 0x29b || i == 0x299) && policy) {
        ERR_put_error(0x22, 0x9b, 0x9f, 0, 0);
        goto err;
    }

    pci = (PROXY_CERT_INFO_EXTENSION*)PROXY_CERT_INFO_EXTENSION_new();
    if (!pci) {
        ERR_put_error(0x22, 0x9b, 0x41, 0, 0);
        goto err;
    }

    pci->proxyPolicy->policyLanguage = language; language = 0;
    pci->proxyPolicy->policy = policy; policy = 0;
    pci->pcPathLengthConstraint = pathlen; pathlen = 0;
    goto end;
err:
    if (language) { ASN1_OBJECT_free(language); language = 0; }
    if (pathlen) { ASN1_INTEGER_free(pathlen); pathlen = 0; }
    if (policy) { ASN1_OCTET_STRING_free(policy); policy = 0; }
end:
    sk_pop_free(vals, X509V3_conf_free);
    return pci;
}

// ---------------------------------------------------------------------------
// @ 0x0119bfd0
// ---------------------------------------------------------------------------
void* v2i_POLICY_CONSTRAINTS(X509V3_EXT_METHOD* method, X509V3_CTX* ctx,
                             void* values)
{
    POLICY_CONSTRAINTS* pcons = 0;
    CONF_VALUE* val;
    int i;
    if (!(pcons = (POLICY_CONSTRAINTS*)ASN1_item_new(ASN1_ITEM_POLICY_CONSTRAINTS))) {
        ERR_put_error(0x22, 0x92, 0x41, 0, 0);
        return 0;
    }
    for (i = 0; i < sk_num(values); i++) {
        val = (CONF_VALUE*)sk_value(values, i);
        if (!strcmp(val->name, "requireExplicitPolicy")) {
            if (!X509V3_get_value_int(val, &pcons->requireExplicitPolicy)) goto err;
        } else if (!strcmp(val->name, "inhibitPolicyMapping")) {
            if (!X509V3_get_value_int(val, &pcons->inhibitPolicyMapping)) goto err;
        } else {
            ERR_put_error(0x22, 0x92, 0x6a, 0, 0);
            ERR_add_error_data(6, "section:", val->section, ",name:", val->name,
                               ",value:", val->value);
            goto err;
        }
    }
    if (!pcons->inhibitPolicyMapping && !pcons->requireExplicitPolicy) {
        ERR_put_error(0x22, 0x92, 0x97, 0, 0);
        goto err;
    }

    return pcons;
err:
    ASN1_item_free(pcons, ASN1_ITEM_POLICY_CONSTRAINTS);
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x0119c170
// ---------------------------------------------------------------------------
void* i2v_AUTHORITY_INFO_ACCESS(X509V3_EXT_METHOD* method, void* ainfo, void* ret)
{
    ACCESS_DESCRIPTION* desc;
    int i, nlen;
    char objtmp[80], *ntmp;
    CONF_VALUE* vtmp;
    for (i = 0; i < sk_num(ainfo); i++) {
        desc = (ACCESS_DESCRIPTION*)sk_value(ainfo, i);
        ret = i2v_GENERAL_NAME(method, desc->location, ret);
        if (!ret) break;
        vtmp = (CONF_VALUE*)sk_value(ret, i);
        i2t_ASN1_OBJECT(objtmp, sizeof objtmp, desc->method);
        nlen = (int)(strlen(objtmp) + strlen(vtmp->name) + 5);
        ntmp = (char*)CRYPTO_malloc(nlen, ".\\crypto\\x509v3\\v3_info.c", 0x76);
        if (!ntmp) {
            ERR_put_error(0x22, 0x8a, 0x41, 0, 0);
            return 0;
        }
        BUF_strlcpy(ntmp, objtmp, nlen);
        BUF_strlcat(ntmp, " - ", nlen);
        BUF_strlcat(ntmp, vtmp->name, nlen);
        CRYPTO_free(vtmp->name);
        vtmp->name = ntmp;
    }
    if (!ret) return sk_new_null();
    return ret;
}

// ---------------------------------------------------------------------------
// @ 0x0119c2e0
// ---------------------------------------------------------------------------
void* v2i_AUTHORITY_INFO_ACCESS(X509V3_EXT_METHOD* method, X509V3_CTX* ctx,
                                void* nval)
{
    void* ainfo;
    CONF_VALUE* cnf;
    CONF_VALUE ctmp;
    ACCESS_DESCRIPTION* acc;
    int i, objlen;
    char *objtmp, *ptmp;
    if (!(ainfo = sk_new_null())) {
        ERR_put_error(0x22, 0x8b, 0x41, 0, 0);
        return 0;
    }
    for (i = 0; i < sk_num(nval); i++) {
        cnf = (CONF_VALUE*)sk_value(nval, i);
        if (!(acc = (ACCESS_DESCRIPTION*)ASN1_item_new(ASN1_ITEM_ACCESS_DESCRIPTION))
            || !sk_push(ainfo, acc)) {
            ERR_put_error(0x22, 0x8b, 0x41, 0, 0);
            goto err;
        }
        ptmp = strchr(cnf->name, ';');
        if (!ptmp) {
            ERR_put_error(0x22, 0x8b, 0x8f, 0, 0);
            goto err;
        }
        objlen = (int)(ptmp - cnf->name);
        ctmp.name = ptmp + 1;
        ctmp.value = cnf->value;
        if (!v2i_GENERAL_NAME_ex(acc->location, method, ctx, &ctmp, 0))
            goto err;
        if (!(objtmp = (char*)CRYPTO_malloc(objlen + 1, ".\\crypto\\x509v3\\v3_info.c", 0xa4))) {
            ERR_put_error(0x22, 0x8b, 0x41, 0, 0);
            goto err;
        }
        strncpy(objtmp, cnf->name, objlen);
        objtmp[objlen] = 0;
        acc->method = (ASN1_OBJECT*)OBJ_txt2obj(objtmp, 0);
        if (!acc->method) {
            ERR_put_error(0x22, 0x8b, 0x77, 0, 0);
            ERR_add_error_data(2, "value=", objtmp);
            CRYPTO_free(objtmp);
            goto err;
        }
        CRYPTO_free(objtmp);
    }
    return ainfo;
err:
    sk_pop_free(ainfo, ACCESS_DESCRIPTION_free);
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x0119c5b0
// ---------------------------------------------------------------------------
int SXNET_add_id_INTEGER(SXNET** psx, ASN1_INTEGER* zone, char* user, int userlen)
{
    SXNET* sx = 0;
    SXNETID* id = 0;
    if (!psx || !zone || !user) {
        ERR_put_error(0x22, 0x7e, 0x6b, 0, 0);
        return 0;
    }
    if (userlen == -1) userlen = (int)strlen(user);
    if (userlen > 64) {
        ERR_put_error(0x22, 0x7e, 0x84, 0, 0);
        return 0;
    }
    if (!*psx) {
        if (!(sx = (SXNET*)ASN1_item_new(ASN1_ITEM_SXNET))) goto err;
        if (!ASN1_INTEGER_set(sx->version, 0)) goto err;
        *psx = sx;
    } else sx = *psx;
    if (SXNET_get_id_INTEGER(sx, zone)) {
        ERR_put_error(0x22, 0x7e, 0x85, 0, 0);
        return 0;
    }

    if (!(id = (SXNETID*)ASN1_item_new(ASN1_ITEM_SXNETID))) goto err;
    if (userlen == -1) userlen = (int)strlen(user);
    if (!ASN1_STRING_set(id->user, user, userlen)) goto err;
    if (!sk_push(sx->ids, id)) goto err;
    id->zone = zone;
    return 1;
err:
    ERR_put_error(0x22, 0x7e, 0x41, 0, 0);
    ASN1_item_free(id, ASN1_ITEM_SXNETID);
    ASN1_item_free(sx, ASN1_ITEM_SXNET);
    *psx = 0;
    return 0;
}

// ---------------------------------------------------------------------------
// sxnet_v2i reaches SXNET_add_id_asc; the original translation unit defined
// both in v3_sxnet.c, so the call is inlined here.  Address-less helper.
// ---------------------------------------------------------------------------
int SXNET_add_id_asc(SXNET** psx, char* zone, char* user, int userlen)
{
    ASN1_INTEGER* izone = 0;
    if (!(izone = (ASN1_INTEGER*)s2i_ASN1_INTEGER(0, zone))) {
        ERR_put_error(0x22, 0x7d, 0x83, 0, 0);
        return 0;
    }
    return SXNET_add_id_INTEGER(psx, izone, user, userlen);
}

// ---------------------------------------------------------------------------
// @ 0x0119c730
// ---------------------------------------------------------------------------
SXNET* sxnet_v2i(X509V3_EXT_METHOD* method, X509V3_CTX* ctx, void* nval)
{
    CONF_VALUE* cnf;
    SXNET* sx = 0;
    int i;
    for (i = 0; i < sk_num(nval); i++) {
        cnf = (CONF_VALUE*)sk_value(nval, i);
        if (!SXNET_add_id_asc(&sx, cnf->name, cnf->value, -1))
            return 0;
    }
    return sx;
}

// ---------------------------------------------------------------------------
// @ 0x0119c890
// ---------------------------------------------------------------------------
void* v2i_EXTENDED_KEY_USAGE(X509V3_EXT_METHOD* method, X509V3_CTX* ctx,
                             void* nval)
{
    void* extku;
    char* extval;
    ASN1_OBJECT* objtmp;
    CONF_VALUE* val;
    int i;

    if (!(extku = sk_new_null())) {
        ERR_put_error(0x22, 0x67, 0x41, 0, 0);
        return 0;
    }

    for (i = 0; i < sk_num(nval); i++) {
        val = (CONF_VALUE*)sk_value(nval, i);
        if (val->value) extval = val->value;
        else extval = val->name;
        if (!(objtmp = (ASN1_OBJECT*)OBJ_txt2obj(extval, 0))) {
            sk_pop_free(extku, ASN1_OBJECT_free);
            ERR_put_error(0x22, 0x67, 0x6e, 0, 0);
            ERR_add_error_data(6, "section:", val->section, ",name:", val->name,
                               ",value:", val->value);
            return 0;
        }
        sk_push(extku, objtmp);
    }
    return extku;
}

// ---------------------------------------------------------------------------
// @ 0x0119ca30
// ---------------------------------------------------------------------------
void* v2i_crld(X509V3_EXT_METHOD* method, X509V3_CTX* ctx, void* nval)
{
    void* crld = 0;
    void* gens = 0;
    GENERAL_NAME* gen = 0;
    CONF_VALUE* cnf;
    int i;
    if (!(crld = sk_new_null())) goto merr;
    for (i = 0; i < sk_num(nval); i++) {
        DIST_POINT* point;
        cnf = (CONF_VALUE*)sk_value(nval, i);
        if (!(gen = (GENERAL_NAME*)v2i_GENERAL_NAME(method, ctx, cnf))) goto err;
        if (!(gens = GENERAL_NAMES_new())) goto merr;
        if (!sk_push(gens, gen)) goto merr;
        gen = 0;
        if (!(point = (DIST_POINT*)ASN1_item_new(ASN1_ITEM_DIST_POINT))) goto merr;
        if (!sk_push(crld, point)) {
            ASN1_item_free(point, ASN1_ITEM_DIST_POINT);
            goto merr;
        }
        if (!(point->distpoint = (DIST_POINT_NAME*)ASN1_item_new(ASN1_ITEM_DIST_POINT_NAME)))
            goto merr;
        point->distpoint->name.fullname = gens;
        point->distpoint->type = 0;
        gens = 0;
    }
    return crld;

merr:
    ERR_put_error(0x22, 0x86, 0x41, 0, 0);
err:
    GENERAL_NAME_free(gen);
    GENERAL_NAMES_free(gens);
    sk_pop_free(crld, DIST_POINT_free);
    return 0;
}
