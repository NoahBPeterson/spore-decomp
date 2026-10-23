// Slice s01190840 -- lib_openssl / lib_cblock EVP_PKEY + EC_KEY + PEM helpers
// Region flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (+ default /GS: 0x1190840 has a stack cookie)
typedef unsigned int uint;

// ---------------------------------------------------------------- masked externs
void* __cdecl CRYPTO_malloc(uint size, const char* file, int line);                      // 0x01183410
void  __cdecl ERR_put_error(int lib, int func, int reason, const char* file, int line);  // 0x01180d50
uint* __cdecl FUN_01191b20(int param_1);                                                 // 0x01191b20 (defined below)
uint* __cdecl FUN_0117b100(uint* bn);                                                    // 0x0117b100 (BN_dup-ish)
void  __cdecl BN_free(void* bn);                                                         // 0x0117a970
int   __cdecl ASN1_STRING_type(void* s);                                                 // 0x011922c0
void* __cdecl EC_GROUP_dup(void* g);                                                     // 0x011b2d20
int   __cdecl EC_KEY_set_group(void* key, void* g);                                      // 0x011922d0
void  __cdecl EC_GROUP_free(void* g);                                                    // 0x011b2a60
void  __cdecl EC_POINT_free(void* p);                                                    // EC_POINT_free
int   __cdecl BN_copy(int* a, int* b);                                                   // BN_copy
void  __cdecl EC_EX_DATA_free_all_data(void* ex);                                        // EC_EX_DATA_free_all_data
int*  __cdecl FUN_0117a9d0(void);                                                        // 0x0117a9d0 BN_new
int*  __cdecl FUN_011838a0(int* p);                                                      // 0x011838a0
int*  __cdecl FUN_01187a80(void);                                                        // 0x01187a80 BN_CTX_new
int*  __cdecl FUN_011b1d20(int* p);                                                      // 0x011b1d20 EC_GROUP_new
int   __cdecl FUN_011b2b70(int* g, int* src);                                            // 0x011b2b70 EC_GROUP_copy
int*  __cdecl FUN_011b2140(int* g);                                                      // 0x011b2140 EC_POINT_new
int   __cdecl FUN_011b2240(int* pt, int* src);                                           // 0x011b2240 EC_POINT_copy
int   __cdecl FUN_011b1f80(int* ex, int* data, int* dup, int* free_, int* clear);        // 0x011b1f80
int   __cdecl EC_GROUP_get_order(int* g, int* order, int* ctx);                          // EC_GROUP_get_order
int   __cdecl BN_rand_range(int* r, int* range);                                         // BN_rand_range
int   __cdecl EC_POINT_mul(int* g, int* r, int* n, int* q, int* m, int* ctx);            // EC_POINT_mul
void  __cdecl BN_CTX_free(void* ctx);                                                    // BN_CTX_free
uint* __cdecl FUN_011b38e0(void);                                                        // 0x011b38e0 (default DSA method)
uint* __cdecl FUN_011b4020(void);                                                        // 0x011b4020 (default engine)
int   __cdecl FUN_011836c0(uint* engine);                                                // 0x011836c0 engine_init
int   __cdecl FUN_01192300(uint* engine);                                                // 0x01192300 engine get-method
void  __cdecl FUN_01183740(void* engine);                                                // 0x01183740 engine_finish
void  __cdecl FUN_011835c0(void* p);                                                     // 0x011835c0 CRYPTO_free
void  __cdecl FUN_01184260(int type, void* p, void* ex);                                 // 0x01184260 CRYPTO_new_ex_data
void  __cdecl FUN_011842c0(int type, void* p, void* ex);                                 // 0x011842c0 CRYPTO_free_ex_data
extern uint* DAT_016f20f0;                                                               // 0x016f20f0 default DSA method slot
__declspec(dllimport) int __cdecl strncmp(const char*, const char*, unsigned);           // msvcr90!strncmp (IAT)
int   __cdecl OBJ_sn2nid(const char* s);                                                 // OBJ_sn2nid
int   __cdecl FUN_011973a0(const char* s);                                               // 0x011973a0 EVP_get_cipherbyname
int   __cdecl FUN_01190790(char** p, int* out);                                          // 0x01190790
int*  __cdecl EVP_PKEY_type(int nid);                                                    // 0x011914c0 (EVP_PKEY_type)
int   __cdecl OBJ_obj2nid(const void* o);                                                // 0x0117fa60 OBJ_obj2nid
int   __cdecl CRYPTO_add_lock(int* addr, int amount, int type, const char* file, int line); // 0x011815d0
int   __cdecl FUN_01191ed0(int** dst, unsigned char** p, uint len);                      // 0x01191ed0 d2i_DSAPublicKey
int   __cdecl FUN_01192cb0(int** dst, unsigned char** p, uint len);                      // 0x01192cb0 d2i_EC_PUBKEY
int*  __cdecl FUN_011b3870(int nid);                                                     // 0x011b3870 EC_GROUP_new_by_curve_name
void  __cdecl FUN_011b1e60(int* g, int flag);                                            // 0x011b1e60 EC_GROUP_set_asn1_flag
int   __cdecl FUN_011b34f0(int nid, int** pkey, unsigned char** p, uint len);            // 0x011b34f0
void  __cdecl EVP_PKEY_free(void* pkey);                                                 // 0x01191780 EVP_PKEY_free

// @ 0x01191620 -- FUN_01191620
// EC_KEY_copy-style: same key type required, then the kind-specific (0x74 = DSA, 0x198 = EC)
// field copy with the old BIGNUM/group freed.
int FUN_01191620(int* param_1, int* param_2) {
    int v, old;
    int kind = *param_2;
    if (*param_1 != kind) {
        ERR_put_error(6, 0x67, 0x65, 0, 0);
        return 0;
    }
    if (kind == 0x74) {
        if (((int*)param_2[3])[3] == 0 || ((int*)param_2[3])[4] == 0 ||
            ((int*)param_2[3])[5] == 0) {
            ERR_put_error(6, 0x67, 0x67, 0, 0);
            return 0;
        }
    }
    if (kind == 0x198) {
        if (ASN1_STRING_type((void*)param_2[3]) == 0) {
            ERR_put_error(6, 0x67, 0x67, 0, 0);
            return 0;
        }
    }
    if (*param_1 == 0x74) {
        v = (int)FUN_0117b100((uint*)((int*)param_2[3])[3]);
        if (!v) return 0;
        old = ((int*)param_1[3])[3];
        if (old) BN_free((void*)old);
        ((int*)param_1[3])[3] = v;
        v = (int)FUN_0117b100((uint*)((int*)param_2[3])[4]);
        if (!v) return 0;
        old = ((int*)param_1[3])[4];
        if (old) BN_free((void*)old);
        ((int*)param_1[3])[4] = v;
        v = (int)FUN_0117b100((uint*)((int*)param_2[3])[5]);
        if (!v) return 0;
        old = ((int*)param_1[3])[5];
        if (old) BN_free((void*)old);
        ((int*)param_1[3])[5] = v;
    }
    if (*param_1 == 0x198) {
        void* g = EC_GROUP_dup((void*)ASN1_STRING_type((void*)param_2[3]));
        if (!g) return 0;
        if (!EC_KEY_set_group((void*)param_1[3], g)) return 0;
        EC_GROUP_free(g);
    }
    return 1;
}

// @ 0x01191470 -- FUN_01191470
// EVP_PKEY ctor: allocate 0x18 bytes from p_lib.c, leave +4 unwritten.
uint* FUN_01191470(void) {
    uint* p = (uint*)CRYPTO_malloc(0x18, ".\\crypto\\evp\\p_lib.c", 0x13d);
    if (!p) {
        ERR_put_error(6, 0x6a, 0x41, 0, 0);
        return 0;
    }
    p[0] = 0;
    p[2] = 1;
    p[3] = 0;
    p[5] = 0;
    p[4] = 1;
    return p;
}

// @ 0x01191da0 -- FUN_01191da0
// DSA_new(): the OpenSSL one-line wrapper `return DSA_new_method(NULL)`.
uint* FUN_01191da0(void) {
    return FUN_01191b20(0);
}

// @ 0x01191f10 -- FUN_01191f10
// EC_KEY_new: allocate 0x20 bytes from ec_key.c, then the field init block.
uint* FUN_01191f10(void) {
    uint* p = (uint*)CRYPTO_malloc(0x20, ".\\crypto\\ec\\ec_key.c", 0x49);
    if (!p) {
        ERR_put_error(0x10, 0xb6, 0x41, 0, 0);
        return 0;
    }
    p[0] = 1;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 4;
    p[6] = 1;
    p[7] = 0;
    return p;
}

// @ 0x01191fe0 -- FUN_01191fe0
// EC_KEY_copy: group/point/BIGNUM copy with the old members freed, then the ex_data chain.
uint* FUN_01191fe0(uint* param_1, uint* param_2) {
    if (!param_1 || !param_2) {
        ERR_put_error(0x10, 0xb2, 0x43, 0, 0);
        return 0;
    }
    if (param_2[1]) {
        int* a = FUN_011838a0((int*)param_2[1]);
        if (param_1[1]) EC_GROUP_free((void*)param_1[1]);
        int g = (int)FUN_011b1d20(a);
        param_1[1] = (uint)g;
        if (!g) return 0;
        if (!FUN_011b2b70((int*)g, (int*)param_2[1])) return 0;
    }
    if (param_2[2] && param_2[1]) {
        if (param_1[2]) EC_POINT_free((void*)param_1[2]);
        int pt = (int)FUN_011b2140((int*)param_2[1]);
        param_1[2] = (uint)pt;
        if (!pt) return 0;
        if (!FUN_011b2240((int*)pt, (int*)param_2[2])) return 0;
    }
    if (param_2[3]) {
        if (!param_1[3]) {
            int b = (int)FUN_0117a9d0();
            param_1[3] = (uint)b;
            if (!b) return 0;
        }
        if (!BN_copy((int*)param_1[3], (int*)param_2[3])) return 0;
    }
    EC_EX_DATA_free_all_data(param_1 + 7);
    uint* p = (uint*)param_2[7];
    for (;;) {
        if (!p) {
            param_1[4] = param_2[4];
            param_1[5] = param_2[5];
            *param_1 = *param_2;
            return param_1;
        }
        int d = ((int(__cdecl*)(uint))p[2])(p[1]);
        if (!d) return 0;
        if (!FUN_011b1f80((int*)(param_1 + 7), (int*)d, (int*)p[2], (int*)p[3], (int*)p[4]))
            return 0;
        p = (uint*)*p;
    }
}

// @ 0x01192190 -- FUN_01192190
// EC_KEY_generate_key: random scalar in the group order, then r = n*G.
uint FUN_01192190(int param_1) {
    int iv5 = 0;
    int iv4 = 0;
    uint local_4 = 0;
    if (param_1 == 0 || *(int*)(param_1 + 4) == 0) {
        ERR_put_error(0x10, 0xb3, 0x43, 0, 0);
        return 0;
    }
    int iv1 = (int)FUN_0117a9d0();
    if (iv1 != 0) {
        int iv2 = (int)FUN_01187a80();
        if (iv2 != 0) {
            iv5 = *(int*)(param_1 + 0xc);
            if (iv5 == 0) iv5 = (int)FUN_0117a9d0();
            if (iv5 != 0 &&
                EC_GROUP_get_order((int*)*(int*)(param_1 + 4), (int*)iv1, (int*)iv2)) {
                do {
                    if (!BN_rand_range((int*)iv5, (int*)iv1)) goto cleanup;
                } while (*(int*)(iv5 + 4) == 0);
                iv4 = *(int*)(param_1 + 8);
                if (iv4 == 0) iv4 = (int)FUN_011b2140((int*)*(int*)(param_1 + 4));
                if (iv4 != 0 &&
                    EC_POINT_mul((int*)*(int*)(param_1 + 4), (int*)iv4, (int*)iv5, 0, 0,
                                 (int*)iv2)) {
                    *(int*)(param_1 + 0xc) = iv5;
                    *(int*)(param_1 + 8) = iv4;
                    local_4 = 1;
                }
            }
        }
cleanup:
        BN_free((void*)iv1);
        if (iv4 != 0 && *(int*)(param_1 + 8) == 0) EC_POINT_free((void*)iv4);
        if (iv5 != 0 && *(int*)(param_1 + 0xc) == 0) BN_free((void*)iv5);
        if (iv2 != 0) BN_CTX_free((void*)iv2);
    }
    return local_4;
}

// @ 0x01191b20 -- FUN_01191b20
// DSA_new_method: the 0x44-byte DSA, the method (default slot or the ENGINE argument's),
// then the OpenSSL init block (version, references, ex_data, the method init hook).
uint* FUN_01191b20(int param_1) {
    uint* p = (uint*)CRYPTO_malloc(0x44, ".\\crypto\\dsa\\dsa_lib.c", 0x75);
    if (!p) {
        ERR_put_error(0xa, 0x67, 0x41, 0, 0);
        return 0;
    }
    uint* meth = DAT_016f20f0;
    if (!meth) {
        meth = FUN_011b38e0();
        DAT_016f20f0 = meth;
    }
    p[0xf] = (uint)meth;
    if (param_1 != 0) {
        if (!FUN_011836c0((uint*)param_1)) {
            ERR_put_error(0xa, 0x67, 0x26, 0, 0);
            FUN_011835c0(p);
            return 0;
        }
        p[0x10] = (uint)param_1;
    } else {
        p[0x10] = (uint)FUN_011b4020();
    }
    if (p[0x10] != 0) {
        uint* m = (uint*)FUN_01192300((uint*)p[0x10]);
        p[0xf] = (uint)m;
        if (!m) {
            ERR_put_error(0xa, 0x67, 0x26, 0, 0);
            FUN_01183740((void*)p[0x10]);
            FUN_011835c0(p);
            return 0;
        }
    }
    p[0] = 0;
    p[1] = 0;
    p[2] = 1;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    p[8] = 0;
    p[9] = 0;
    p[0xb] = 0;
    p[0xc] = 1;
    p[0xa] = *(uint*)(p[0xf] + 0x20);
    FUN_01184260(7, p, p + 0xd);
    int (*init)(void*) = (int (*)(void*))*(uint*)(p[0xf] + 0x18);
    if (init != 0) {
        if (!init(p)) {
            if (p[0x10]) FUN_01183740((void*)p[0x10]);
            FUN_011842c0(7, p, p + 0xd);
            FUN_011835c0(p);
            p = 0;
        }
    }
    return p;
}

// @ 0x01190db0 -- FUN_01190db0
// PEM header test: optional "Proc-Type: 4,ENCRYPTED" line, then "DEK-Info: <cipher>,<ivhex>".
bool FUN_01190db0(char* param_1, int* param_2) {
    *param_2 = 0;
    char* p = param_1;
    if (p == 0 || *p == '\0' || *p == '\n') return true;
    if (strncmp(p, "Proc-Type: ", 0xb) == 0) {
        if (p[0xb] == '4' && p[0xc] == ',') {
            p += 0xd;
            if (strncmp(p, "ENCRYPTED", 9) != 0) {
                ERR_put_error(9, 0x6b, 0x6a, 0, 0);
                return false;
            }
            char c = *p;
            while (c != '\n') {
                if (c == '\0') goto err_70;
                p += 1;
                c = *p;
            }
            if (*p != '\0') {
                if (strncmp(p + 1, "DEK-Info: ", 10) != 0) {
                    ERR_put_error(9, 0x6b, 0x69, 0, 0);
                    return false;
                }
                p += 0xb;
                char* q = p;
                while ((c = *q, c > '@' && c < '[') ||
                       (c == '-' || (unsigned char)(c - 0x30) < 10)) {
                    q += 1;
                }
                *q = '\0';
                OBJ_sn2nid(p);
                int nid = FUN_011973a0(p);
                *param_2 = nid;
                *q = c;
                p = q + 1;
                if (nid == 0) {
                    ERR_put_error(9, 0x6b, 0x72, 0, 0);
                    return false;
                }
                return FUN_01190790(&p, param_2 + 1) != 0;
            }
err_70:
            ERR_put_error(9, 0x6b, 0x70, 0, 0);
            return false;
        }
    } else {
        ERR_put_error(9, 0x6b, 0x6b, 0, 0);
    }
    return false;
}

// @ 0x011918c0 -- FUN_011918c0
// X509_PUBKEY_get: cached pkey return (with a reference), else build one from the
// algorithm OID + public_key bytes and stash it back in the X509_PUBKEY.
int* FUN_011918c0(int* param_1) {
    int* ret = 0;
    unsigned char* p;
    if (param_1 == 0) return 0;
    if (param_1[2] != 0) {
        CRYPTO_add_lock((int*)(param_1[2] + 8), 1, 10, ".\\crypto\\asn1\\x_pubkey.c", 0x111);
        return (int*)param_1[2];
    }
    if (param_1[1] == 0) return 0;
    int nid = OBJ_obj2nid((void*)*param_1);
    ret = (int*)FUN_01191470();
    if (ret == 0) goto err_41;
    *ret = (int)EVP_PKEY_type(nid);
    {
        int* param = (int*)((int*)*param_1)[1];
        if (*ret == 0x74) {
            if (param != 0 && *param == 0x10) {
                ret[3] = (int)FUN_01191da0();
                if (ret[3] == 0) goto err_41;
                *(int*)(ret[3] + 8) = 0;
                p = (unsigned char*)((int*)param[1])[2];
                if (!FUN_01191ed0((int**)(ret + 3), &p, (uint)((int*)param[1])[0]))
                    goto cleanup;
            }
            ret[4] = 1;
            goto lab_aa0;
        }
        if (*ret != 0x198) goto lab_aa0;
        if (param != 0 && *param == 0x10) {
            ret[3] = (int)FUN_01191f10();
            if (ret[3] == 0) goto err_41;
            p = (unsigned char*)((int*)param[1])[2];
            if (!FUN_01192cb0((int**)(ret + 3), &p, (uint)((int*)param[1])[0])) {
                ERR_put_error(0xb, 0x77, 0x10, 0, 0);
                goto cleanup;
            }
            goto lab_a95;
        }
        if (param != 0 && *param == 6) {
            if (ret[3] == 0) ret[3] = (int)FUN_01191f10();
            int ec = ret[3];
            if (ec == 0) goto cleanup;
            int* g = FUN_011b3870(OBJ_obj2nid((void*)param[1]));
            if (g == 0) goto cleanup;
            FUN_011b1e60(g, 1);
            if (!EC_KEY_set_group((void*)ec, g)) goto cleanup;
            EC_GROUP_free(g);
        }
lab_a95:
        ret[4] = 1;
    }
lab_aa0:
    p = (unsigned char*)((int*)param_1[1])[2];
    if (!FUN_011b34f0(nid, &ret, &p, (uint)*(int*)param_1[1])) {
        ERR_put_error(0xb, 0x77, 0x66, 0, 0);
        goto cleanup;
    }
    param_1[2] = (int)ret;
    CRYPTO_add_lock((int*)((char*)ret + 8), 1, 10, ".\\crypto\\asn1\\x_pubkey.c", 0x173);
    return ret;
err_41:
    ERR_put_error(0xb, 0x77, 0x41, 0, 0);
cleanup:
    if (ret != 0) EVP_PKEY_free(ret);
    return 0;
}
