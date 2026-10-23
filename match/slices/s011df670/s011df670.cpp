// Slice s011df670: OpenSSL DSO (win32) and BN_mod_sqrt.
// Reconstructed from the OpenSSL 0.9.8 sources plus the original disassembly.

typedef unsigned int uint;

// ---- Win32 API -----------------------------------------------------------
typedef void* HMODULE;
typedef void* FARPROC;
typedef const char* LPCSTR;
extern "C" __declspec(dllimport) HMODULE __stdcall LoadLibraryA(LPCSTR);
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(HMODULE);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, LPCSTR);

// ---- OpenSSL runtime -----------------------------------------------------
extern "C" void ERR_put_error(int lib, int func, int reason, const char* file, int line);
extern "C" void ERR_add_error_data(int num, ...);
extern "C" void* CRYPTO_malloc(int num, const char* file, int line);
extern "C" void CRYPTO_free(void* p);
extern "C" int sk_num(const void* st);
extern "C" void* sk_value(const void* st, int i);
extern "C" void* sk_pop(void* st);
extern "C" int sk_push(void* st, void* p);
extern "C" char* DSO_convert_filename(void* dso, int type);   // 0x011defb0

struct DSO {
    void* meth;             // +0x00
    void* meth_data;        // +0x04
    char pad08[0x1c];
    char* loaded_filename;  // +0x24
};

template <class T> static inline T& Fld(void* base, unsigned off) { return *(T*)((char*)base + off); }

// @ 0x011dfd60
int __cdecl win32_load(DSO* dso)
{
    HMODULE h = 0;
    HMODULE* p = 0;
    char* filename = DSO_convert_filename(dso, 0);

    if (filename == 0) {
        ERR_put_error(0x25, 0x78, 0x6f, 0, 0);
        goto err;
    }
    h = LoadLibraryA(filename);
    if (h == 0) {
        ERR_put_error(0x25, 0x78, 0x67, 0, 0);
        ERR_add_error_data(3, "filename(", filename, ")");
        goto err;
    }
    p = (HMODULE*)CRYPTO_malloc(4, ".\\crypto\\dso\\dso_win32.c", 0xb0);
    if (p == 0) {
        ERR_put_error(0x25, 0x78, 0x41, 0, 0);
        goto err;
    }
    *p = h;
    if (!sk_push(dso->meth_data, (char*)p)) {
        ERR_put_error(0x25, 0x78, 0x69, 0, 0);
        goto err;
    }
    dso->loaded_filename = filename;
    return 1;
err:
    if (filename != 0)
        CRYPTO_free(filename);
    if (p != 0)
        CRYPTO_free(p);
    if (h != 0)
        FreeLibrary(h);
    return 0;
}

// @ 0x011dfe40
int __cdecl win32_unload(DSO* dso)
{
    HMODULE* p;

    if (dso == 0) {
        ERR_put_error(0x25, 0x79, 0x43, 0, 0);
        return 0;
    }
    if (sk_num(dso->meth_data) < 1)
        return 1;
    p = (HMODULE*)sk_pop(dso->meth_data);
    if (p == 0) {
        ERR_put_error(0x25, 0x79, 0x68, 0, 0);
        return 0;
    }
    if (!FreeLibrary(*p)) {
        ERR_put_error(0x25, 0x79, 0x6b, 0, 0);
        sk_push(dso->meth_data, (char*)p);
        return 0;
    }
    CRYPTO_free(p);
    return 1;
}

// @ 0x011dfee0
void* __cdecl win32_bind_func(DSO* dso, const char* symname)
{
    HMODULE* ptr;
    void* sym;

    if (dso == 0 || symname == 0) {
        ERR_put_error(0x25, 0x77, 0x43, 0, 0);
        return 0;
    }
    if (sk_num(dso->meth_data) < 1) {
        ERR_put_error(0x25, 0x77, 0x69, 0, 0);
        return 0;
    }
    ptr = (HMODULE*)sk_value(dso->meth_data, sk_num(dso->meth_data) - 1);
    if (ptr == 0) {
        ERR_put_error(0x25, 0x77, 0x68, 0, 0);
        return 0;
    }
    sym = GetProcAddress(*ptr, symname);
    if (sym == 0) {
        ERR_put_error(0x25, 0x77, 0x6a, 0, 0);
        ERR_add_error_data(3, "symname(", symname, ")");
        return 0;
    }
    return sym;
}

// @ 0x011dffa0
void* __cdecl win32_bind_var(DSO* dso, const char* symname)
{
    HMODULE* ptr;
    void* sym;

    if (dso == 0 || symname == 0) {
        ERR_put_error(0x25, 0x76, 0x43, 0, 0);
        return 0;
    }
    if (sk_num(dso->meth_data) < 1) {
        ERR_put_error(0x25, 0x76, 0x69, 0, 0);
        return 0;
    }
    ptr = (HMODULE*)sk_value(dso->meth_data, sk_num(dso->meth_data) - 1);
    if (ptr == 0) {
        ERR_put_error(0x25, 0x76, 0x68, 0, 0);
        return 0;
    }
    sym = GetProcAddress(*ptr, symname);
    if (sym == 0) {
        ERR_put_error(0x25, 0x76, 0x6a, 0, 0);
        ERR_add_error_data(3, "symname(", symname, ")");
        return 0;
    }
    return sym;
}

// ---- name conversion / filename joining ----------------------------------
extern "C" char* strstr(const char* haystack, const char* needle);
extern "C" unsigned int __cdecl strlen(const char* s);
extern "C" char* strncpy(char* dst, const char* src, unsigned int n);
extern "C" int sprintf(char* dst, const char* fmt, ...);

// @ 0x011e0060
char* __cdecl win32_name_converter(DSO* dso, const char* filename)
{
    char* translated;
    int len, transform;

    len = (int)strlen(filename);
    transform = ((strstr(filename, "/") == 0) &&
                 (strstr(filename, "\\") == 0) &&
                 (strstr(filename, ":") == 0));
    if (transform)
        translated = (char*)CRYPTO_malloc(len + 5, ".\\crypto\\dso\\dso_win32.c", 0x13f);
    else
        translated = (char*)CRYPTO_malloc(len + 1, ".\\crypto\\dso\\dso_win32.c", 0x13f);
    if (translated == 0) {
        ERR_put_error(0x25, 0x88, 0x6f, 0, 0);
        return 0;
    }
    if (transform)
        sprintf(translated, "%s.dll", filename);
    else
        sprintf(translated, "%s", filename);
    return translated;
}

struct file_st {
    const char* node;
    int nodelen;
    const char* device;
    int devicelen;
    const char* predir;
    int predirlen;
    const char* dir;
    int dirlen;
    const char* file;
    int filelen;
};

extern "C" const char* openssl_strnchr(const char* string, int c, unsigned int len);

// @ 0x011e0320
char* __cdecl win32_joiner(DSO* dso, const file_st* file_split)
{
    int len = 0, offset = 0;
    char* result = 0;
    const char* start;

    if (!file_split) {
        ERR_put_error(0x25, 0x87, 0x43, 0, 0);
        return 0;
    }
    if (file_split->node) {
        len += 2 + file_split->nodelen;
        if (file_split->predir || file_split->dir || file_split->file)
            len++;
    } else if (file_split->device) {
        len += file_split->devicelen + 1;
    }
    len += file_split->predirlen;
    if (file_split->predir && (file_split->dir || file_split->file))
        len++;
    len += file_split->dirlen;
    if (file_split->dir && file_split->file)
        len++;
    len += file_split->filelen;

    if (!len) {
        ERR_put_error(0x25, 0x87, 0x71, 0, 0);
        return 0;
    }
    result = (char*)CRYPTO_malloc(len + 1, ".\\crypto\\dso\\dso_win32.c", 0x1d1);
    if (!result) {
        ERR_put_error(0x25, 0x87, 0x41, 0, 0);
        return 0;
    }
    if (file_split->node) {
        result[0] = '\\';
        result[1] = '\\';
        result[2] = '\0';
        offset += 2;
        strncpy(&result[offset], file_split->node, file_split->nodelen);
        offset += file_split->nodelen;
        if (file_split->predir || file_split->dir || file_split->file) {
            result[offset] = '\\';
            offset++;
        }
    } else if (file_split->device) {
        strncpy(&result[offset], file_split->device, file_split->devicelen);
        offset += file_split->devicelen;
        result[offset] = ':';
        offset++;
    }
    start = file_split->predir;
    while (file_split->predirlen > (start - file_split->predir)) {
        const char* end = openssl_strnchr(start, '/',
            file_split->predirlen - (start - file_split->predir));
        if (!end)
            end = start + file_split->predirlen - (start - file_split->predir);
        strncpy(&result[offset], start, end - start);
        offset += end - start;
        result[offset] = '\\';
        offset++;
        start = end + 1;
    }
    start = file_split->dir;
    while (file_split->dirlen > (start - file_split->dir)) {
        const char* end = openssl_strnchr(start, '/',
            file_split->dirlen - (start - file_split->dir));
        if (!end)
            end = start + file_split->dirlen - (start - file_split->dir);
        strncpy(&result[offset], start, end - start);
        offset += end - start;
        result[offset] = '\\';
        offset++;
        start = end + 1;
    }
    strncpy(&result[offset], file_split->file, file_split->filelen);
    offset += file_split->filelen;
    result[offset] = '\0';
    return result;
}

// ---- BN_mod_sqrt ---------------------------------------------------------
struct BIGNUM {
    unsigned* d;    // +0x00 (BN_ULONG*, 32-bit build)
    int top;        // +0x04
    int dmax;       // +0x08
    int neg;        // +0x0c
};
typedef BIGNUM BN_CTX;

#define BN_is_odd(a)        (((a)->top > 0) && ((a)->d[0] & 1))
#define BN_abs_is_word(a,w) (((a)->top == 1) && ((a)->d[0] == (unsigned)(w)))
#define BN_is_word(a,w)     (((a)->top == 1) && ((a)->d[0] == (unsigned)(w)) && ((a)->neg == 0))
#define BN_is_zero(a)       ((a)->top == 0)
#define BN_is_one(a)        BN_is_word(a,1)
#define BN_zero(a)          BN_set_word((a),0)
#define BN_one(a)           BN_set_word(a,1)
#define BNerr(f,r)          ERR_put_error(3,0x79,(r),0,0)
#define bn_check_top(a)

extern "C" BIGNUM* __cdecl BN_new(void);                                        // 0x0117a9d0
extern "C" void __cdecl BN_CTX_start(BN_CTX* ctx);                              // 0x01187b00
extern "C" BIGNUM* __cdecl BN_CTX_get(BN_CTX* ctx);                             // 0x01187b90
extern "C" void __cdecl BN_CTX_end(BN_CTX* ctx);
extern "C" void __cdecl BN_free(BIGNUM* a);
extern "C" void __cdecl BN_clear_free(BIGNUM* a);
extern "C" int __cdecl BN_is_bit_set(const BIGNUM* a, int n);
extern "C" int __cdecl BN_set_word(BIGNUM* a, unsigned w);
extern "C" int __cdecl BN_add_word(BIGNUM* a, unsigned w);
extern "C" int __cdecl BN_sub_word(BIGNUM* a, unsigned w);
extern "C" int __cdecl BN_num_bits(const BIGNUM* a);
extern "C" int __cdecl BN_pseudo_rand(BIGNUM* rnd, int bits, int top, int bottom);
extern "C" int __cdecl BN_ucmp(const BIGNUM* a, const BIGNUM* b);
extern "C" int __cdecl BN_cmp(const BIGNUM* a, const BIGNUM* b);
extern "C" int __cdecl BN_nnmod(BIGNUM* r, const BIGNUM* m, const BIGNUM* d, BN_CTX* ctx);
extern "C" int __cdecl BN_mod_lshift1_quick(BIGNUM* r, const BIGNUM* a, const BIGNUM* m);
extern "C" int __cdecl BN_rshift(BIGNUM* r, const BIGNUM* a, int n);
extern "C" int __cdecl BN_rshift1(BIGNUM* r, const BIGNUM* a);
extern "C" int __cdecl BN_mod_exp(BIGNUM* r, const BIGNUM* a, const BIGNUM* p, const BIGNUM* m, BN_CTX* ctx);
extern "C" int __cdecl BN_mod_sqr(BIGNUM* r, const BIGNUM* a, const BIGNUM* m, BN_CTX* ctx);
extern "C" int __cdecl BN_mod_mul(BIGNUM* r, const BIGNUM* a, const BIGNUM* b, const BIGNUM* m, BN_CTX* ctx); // 0x011ad640
extern "C" int __cdecl BN_kronecker(const BIGNUM* a, const BIGNUM* b, BN_CTX* ctx);
extern "C" int __cdecl BN_copy(BIGNUM* to, const BIGNUM* from);
extern "C" int __cdecl BN_add(BIGNUM* r, const BIGNUM* a, const BIGNUM* b);
extern "C" int __cdecl BN_sub(BIGNUM* r, const BIGNUM* a, const BIGNUM* b);

// @ 0x011df670
BIGNUM* __cdecl BN_mod_sqrt(BIGNUM* in, const BIGNUM* a, const BIGNUM* p, BN_CTX* ctx)
{
    BIGNUM* ret = in;
    int err = 1;
    int r;
    BIGNUM *A, *b, *q, *t, *x, *y;
    int e, i, j;

    if (!BN_is_odd(p) || BN_abs_is_word(p, 1)) {
        if (BN_abs_is_word(p, 2)) {
            if (ret == 0)
                ret = BN_new();
            if (ret == 0)
                goto end;
            if (!BN_set_word(ret, BN_is_bit_set(a, 0))) {
                if (ret != in)
                    BN_free(ret);
                return 0;
            }
            bn_check_top(ret);
            return ret;
        }
        BNerr(BN_F_BN_MOD_SQRT, 0x70);
        return 0;
    }
    if (BN_is_zero(a) || BN_is_one(a)) {
        if (ret == 0)
            ret = BN_new();
        if (ret == 0)
            goto end;
        if (!BN_set_word(ret, BN_is_one(a))) {
            if (ret != in)
                BN_free(ret);
            return 0;
        }
        bn_check_top(ret);
        return ret;
    }
    BN_CTX_start(ctx);
    A = BN_CTX_get(ctx);
    b = BN_CTX_get(ctx);
    q = BN_CTX_get(ctx);
    t = BN_CTX_get(ctx);
    x = BN_CTX_get(ctx);
    y = BN_CTX_get(ctx);
    if (y == 0)
        goto end;
    if (ret == 0)
        ret = BN_new();
    if (ret == 0)
        goto end;
    if (!BN_nnmod(A, a, p, ctx))
        goto end;
    e = 1;
    while (!BN_is_bit_set(p, e))
        e++;
    if (e == 1) {
        if (!BN_rshift(q, p, 2))
            goto end;
        q->neg = 0;
        if (!BN_add_word(q, 1))
            goto end;
        if (!BN_mod_exp(ret, A, q, p, ctx))
            goto end;
        err = 0;
        goto vrfy;
    }
    if (e == 2) {
        if (!BN_mod_lshift1_quick(t, A, p))
            goto end;
        if (!BN_rshift(q, p, 3))
            goto end;
        q->neg = 0;
        if (!BN_mod_exp(b, t, q, p, ctx))
            goto end;
        if (!BN_mod_sqr(y, b, p, ctx))
            goto end;
        if (!BN_mod_mul(t, t, y, p, ctx))
            goto end;
        if (!BN_sub_word(t, 1))
            goto end;
        if (!BN_mod_mul(x, A, b, p, ctx))
            goto end;
        if (!BN_mod_mul(x, x, t, p, ctx))
            goto end;
        if (!BN_copy(ret, x))
            goto end;
        err = 0;
        goto vrfy;
    }
    if (!BN_copy(q, p))
        goto end;
    q->neg = 0;
    i = 2;
    do {
        if (i < 22) {
            if (!BN_set_word(y, i))
                goto end;
        } else {
            if (!BN_pseudo_rand(y, BN_num_bits(p), 0, 0))
                goto end;
            if (BN_ucmp(y, p) >= 0) {
                if (!(p->neg ? BN_add : BN_sub)(y, y, p))
                    goto end;
            }
            if (BN_is_zero(y))
                if (!BN_set_word(y, i))
                    goto end;
        }
        r = BN_kronecker(y, q, ctx);
        if (r < -1)
            goto end;
        if (r == 0) {
            BNerr(BN_F_BN_MOD_SQRT, 0x70);
            goto end;
        }
    } while (r == 1 && ++i < 82);
    if (r != -1) {
        BNerr(BN_F_BN_MOD_SQRT, 0x71);
        goto end;
    }
    if (!BN_rshift(q, q, e))
        goto end;
    if (!BN_mod_exp(y, y, q, p, ctx))
        goto end;
    if (BN_is_one(y)) {
        BNerr(BN_F_BN_MOD_SQRT, 0x70);
        goto end;
    }
    if (!BN_rshift1(t, q))
        goto end;
    if (BN_is_zero(t)) {
        if (!BN_nnmod(t, A, p, ctx))
            goto end;
        if (BN_is_zero(t)) {
            BN_zero(ret);
            err = 0;
            goto end;
        } else if (!BN_one(x))
            goto end;
    } else {
        if (!BN_mod_exp(x, A, t, p, ctx))
            goto end;
        if (BN_is_zero(x)) {
            BN_zero(ret);
            err = 0;
            goto end;
        }
    }
    if (!BN_mod_sqr(b, x, p, ctx))
        goto end;
    if (!BN_mod_mul(b, b, A, p, ctx))
        goto end;
    if (!BN_mod_mul(x, x, A, p, ctx))
        goto end;
    while (1) {
        if (BN_is_one(b)) {
            if (!BN_copy(ret, x))
                goto end;
            err = 0;
            goto vrfy;
        }
        i = 1;
        if (!BN_mod_sqr(t, b, p, ctx))
            goto end;
        while (!BN_is_one(t)) {
            i++;
            if (i == e) {
                BNerr(BN_F_BN_MOD_SQRT, 0x6f);
                goto end;
            }
            if (!BN_mod_mul(t, t, t, p, ctx))
                goto end;
        }
        if (!BN_copy(t, y))
            goto end;
        for (j = e - i - 1; j > 0; j--) {
            if (!BN_mod_sqr(t, t, p, ctx))
                goto end;
        }
        if (!BN_mod_mul(y, t, t, p, ctx))
            goto end;
        if (!BN_mod_mul(x, x, t, p, ctx))
            goto end;
        if (!BN_mod_mul(b, b, y, p, ctx))
            goto end;
        e = i;
    }
vrfy:
    if (!err) {
        if (!BN_mod_sqr(x, ret, p, ctx))
            err = 1;
        if (!err && 0 != BN_cmp(x, A)) {
            BNerr(BN_F_BN_MOD_SQRT, 0x6f);
            err = 1;
        }
    }
end:
    if (err) {
        if (ret != 0 && ret != in)
            BN_clear_free(ret);
        ret = 0;
    }
    BN_CTX_end(ctx);
    bn_check_top(ret);
    return ret;
}
