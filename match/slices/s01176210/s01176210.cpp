// Slice s01176210: lib_cblock block decoders plus the OpenSSL 0.9.8 EVP/BIO routines
// they are bundled with.  Reconstructed from the original disassembly.

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

// ---------------------------------------------------------------- block codec
struct CBlockCtx {
    int     n;      // 0x00
    float   f4;     // 0x04
    float   f8;     // 0x08
    uchar*  in;     // 0x0c
    float*  out;    // 0x10
};

extern float g_cb_t1[];   // 0x15c4ffc
extern float g_cb_t2[];   // 0x15c500c
extern float g_cb_t3[];   // 0x15c5020
extern int g_cb_mode;     // 0x16f16f0

#define CB_GET16(dst)                   \
    ((uchar*)&v)[0] = (dst)[1];         \
    ((uchar*)&v)[1] = (dst)[0]

#define CB_SAMPLE()                     \
    CB_GET16(c->in);                    \
    *c->out = (float)v;                 \
    c->in += 2;                         \
    c->out += 1;

void __cdecl sub_01176210(CBlockCtx* c);

// ---------------------------------------------------------------- EVP / BIO
struct evp_cipher_ctx_st;

struct evp_cipher_st {
    int nid;                                                    // 0x00
    int block_size;                                             // 0x04
    int key_len;                                                // 0x08
    int iv_len;                                                 // 0x0c
    ulong flags;                                                // 0x10
    int (*init)(evp_cipher_ctx_st*, const uchar*, const uchar*, int);   // 0x14
    int (*do_cipher)(evp_cipher_ctx_st*, uchar*, const uchar*, uint);   // 0x18
    int (*cleanup)(evp_cipher_ctx_st*);                          // 0x1c
    int ctx_size;                                                // 0x20
    void* set_asn1_parameters;                                   // 0x24
    void* get_asn1_parameters;                                   // 0x28
    int (*ctrl)(evp_cipher_ctx_st*, int, int, void*);            // 0x2c
    void* app_data;                                              // 0x30
};

struct evp_cipher_ctx_st {
    const evp_cipher_st* cipher;    // 0x00
    void* engine;                   // 0x04
    int encrypt;                    // 0x08
    int buf_len;                    // 0x0c
    uchar oiv[16];                  // 0x10
    uchar iv[16];                   // 0x20
    uchar buf[32];                  // 0x30
    int num;                        // 0x50
    int pad54;                      // 0x54
    int key_len;                    // 0x58
    ulong flags;                    // 0x5c
    void* cipher_data;              // 0x60
    int final_used;                 // 0x64
    int block_mask;                 // 0x68
    uchar final[32];                // 0x6c
};

struct bio_st;
struct bio_method_st;

typedef long (*bio_info_cb)(bio_st*, int, const char*, int, long, long);

struct bio_method_st {
    int type;                                         // 0x00
    const char* name;                                 // 0x04
    int (*bwrite)(bio_st*, const char*, int);         // 0x08
    int (*bread)(bio_st*, char*, int);                // 0x0c
    int (*bputs)(bio_st*, const char*);               // 0x10
    int (*bgets)(bio_st*, char*, int);                // 0x14
    long (*ctrl)(bio_st*, int, long, void*);          // 0x18
    int (*create)(bio_st*);                           // 0x1c
    int (*destroy)(bio_st*);                          // 0x20
    long (*callback_ctrl)(bio_st*, int, bio_info_cb*); // 0x24
};

struct bio_st {
    bio_method_st* method;      // 0x00
    bio_info_cb callback;       // 0x04
    char* cb_arg;               // 0x08
    int init;                   // 0x0c
    int shutdown;               // 0x10
    int flags;                  // 0x14
    int retry_reason;           // 0x18
    int num;                    // 0x1c
    void* ptr;                  // 0x20
    bio_st* next_bio;           // 0x24
    bio_st* prev_bio;           // 0x28
    int references;             // 0x2c
    ulong num_read;             // 0x30
    ulong num_write;            // 0x34
    void* ex_data;              // 0x38
    int ex_data_dummy;          // 0x3c
};

struct buf_mem_st {
    int length;     // 0x00
    char* data;     // 0x04
    int max;        // 0x08
};

extern bio_method_st BIO_s_mem_object;

extern "C" void ERR_put_error(int lib, int func, int reason, const char* file, int line);
extern "C" void OpenSSLDie(const char* file, int line, const char* assertion);
extern "C" void* CRYPTO_malloc(int num, const char* file, int line);
extern "C" void CRYPTO_free(void* p);
extern "C" int BIO_set(bio_st* b, bio_method_st* type);
extern "C" int EVP_CIPHER_CTX_cleanup(evp_cipher_ctx_st* ctx);
extern "C" ulong EVP_CIPHER_CTX_flags(void* ctx);
extern "C" int EVP_CIPHER_CTX_iv_length(void* ctx);
extern "C" int ENGINE_init(void* e);
extern "C" void* ENGINE_get_cipher_engine(int nid);
extern "C" const evp_cipher_st* ENGINE_get_cipher(void* e, int nid);
extern "C" int BUF_MEM_grow_clean(buf_mem_st* str, int len);
extern "C" void* memcpy(void* dst, const void* src, uint n);
extern "C" void* memset(void* dst, int c, uint n);
extern "C" void BIO_clear_flags(void* b, int flags);
extern "C" void BIO_set_flags(void* b, int flags);
extern "C" int mem_read(bio_st* b, char* out, int size);

int __cdecl EVP_CIPHER_CTX_ctrl(evp_cipher_ctx_st* ctx, int type, int arg, void* ptr);
int __cdecl EVP_CIPHER_CTX_set_key_length(evp_cipher_ctx_st* x, int keylen);
int __cdecl BIO_read(bio_st* b, void* data, int len);
int __cdecl BIO_write(bio_st* b, const void* data, int len);
int __cdecl BIO_puts(bio_st* b, const char* buf);
int __cdecl BIO_gets(bio_st* b, char* buf, int size);
long __cdecl BIO_ctrl(bio_st* b, int cmd, long larg, void* parg);
long __cdecl BIO_callback_ctrl(bio_st* b, int cmd, bio_info_cb* fp);
bio_st* __cdecl BIO_new(bio_method_st* type);
bio_st* __cdecl BIO_new_mem_buf(void* buf, int len);
int __cdecl mem_write(bio_st* b, const char* in, int inl);
int __cdecl mem_gets(bio_st* b, char* buf, int size);
int __cdecl cb_write_str(bio_st* b, const char* str);

// ---------------------------------------------------------------- codec
// @ 0x01176210
void __cdecl sub_01176210(CBlockCtx* c)
{
    __int16 v;

    if (*c->in != 0xee)
        return;
    c->in++;
    CB_GET16(c->in);
    c->f4 = (float)v;
    c->in += 2;
    CB_GET16(c->in);
    c->f8 = (float)v;
    c->in += 2;
    for (int i = 0; i < 4; i++)
        for (int k = 0; k < 7; k++) {
            CB_GET16(c->in);
            *c->out++ = (float)v;
            c->in += 2;
        }
}

// @ 0x011763b0
void __cdecl dec_block_a(CBlockCtx* c)
{
    uchar* in = c->in;
    float* out = c->out;
    float x2 = c->f4;
    float x3 = c->f8;
    float x4 = x2;

    while (c->n > 0) {
        c->n -= 0x1c;
        if (*in == 0xee) {
            sub_01176210(c);
            x2 = c->f4;
            x3 = c->f8;
            x4 = x2;
            in = c->in;
            out = c->out;
        } else {
            int idx = *in >> 4;
            int coef = (*in & 0xf) << 6;
            float t1 = g_cb_t1[idx];
            float t2 = g_cb_t2[idx];
            uchar* p = in + 15;
            out += 0x1c;
            for (int k = -0xe; k < 0; k++) {
                x4 = x4 * t1 + g_cb_t3[coef + (p[k] >> 4)] + x3 * t2;
                out[k * 2] = x4;
                x3 = x4;
                x4 = x4 * t1 + g_cb_t3[coef + (p[k] & 0xf)] + x2 * t2;
                x2 = x4;
                out[k * 2 + 1] = x4;
            }
            c->f4 = x2;
            c->f8 = x3;
            c->out = out;
            c->in = p;
            in = p;
        }
    }
}

// @ 0x011764b0
void __cdecl dec_block_b(CBlockCtx* c)
{
    float* out = c->out;
    uchar* in = c->in;

    out[-1] = c->f4;
    out[-2] = c->f8;
    while (c->n > 0) {
        c->n -= 0x1c;
        if (*in == 0xee) {
            sub_01176210(c);
            out = c->out;
            out[-1] = c->f4;
            out[-2] = c->f8;
            in = c->in;
        } else {
            int idx = *in >> 4;
            int coef = (*in & 0xf) << 6;
            float t1 = g_cb_t1[idx];
            float t2 = g_cb_t2[idx];
            uchar* p = in + 15;
            out += 0x1c;
            for (int k = 0; k < 14; k++) {
                float s0 = out[k * 2 - 2] * t1 + g_cb_t3[coef + (p[k] >> 4)] + out[k * 2 - 1] * t2;
                out[k * 2] = s0;
                float s1 = s0 * t1 + g_cb_t3[coef + (p[k] & 0xf)] + out[k * 2 - 1] * t2;
                out[k * 2 + 1] = s1;
            }
            c->f4 = out[27];
            c->f8 = out[26];
            c->out = out;
            c->in = p;
            in = p;
        }
    }
}

// @ 0x011765b0
CBlockCtx* __fastcall cblock_ctx_init(CBlockCtx* c)
{
    c->in = 0;
    *(int*)&c->f8 = 0;
    *(int*)&c->f4 = 0;
    ((float*)c)[0x26] = 0.0f;
    ((float*)c)[0x27] = 0.0f;
    if (g_cb_mode & 2)
        *(void**)c = (void*)dec_block_a;
    else
        *(void**)c = (void*)dec_block_b;
    return c;
}

// ---------------------------------------------------------------- EVP
// @ 0x01176770
int __cdecl EVP_EncryptFinal_ex(evp_cipher_ctx_st* ctx, uchar* out, int* outl)
{
    uint b, bl, i;
    int n, ret;

    b = ctx->cipher->block_size;
    if (b > sizeof(ctx->buf))
        OpenSSLDie(".\\crypto\\evp\\evp_enc.c", 0x15c, "b <= sizeof ctx->buf");
    if (b == 1) {
        *outl = 0;
        return 1;
    }
    bl = ctx->buf_len;
    if (ctx->flags & 0x100) {
        if (bl) {
            ERR_put_error(6, 0x7f, 0x8a, 0, 0);
            return 0;
        }
        *outl = 0;
        return 1;
    }
    n = b - bl;
    for (i = bl; i < b; i++)
        ctx->buf[i] = (uchar)n;
    ret = ctx->cipher->do_cipher(ctx, out, ctx->buf, b);
    if (ret)
        *outl = b;
    return ret;
}

// @ 0x01176910
int __cdecl EVP_DecryptFinal_ex(evp_cipher_ctx_st* ctx, uchar* out, int* outl)
{
    int i, n;
    uint b;

    *outl = 0;
    b = ctx->cipher->block_size;
    if (ctx->flags & 0x100) {
        if (ctx->buf_len) {
            ERR_put_error(6, 0x65, 0x8a, 0, 0);
            return 0;
        }
        *outl = 0;
        return 1;
    }
    if (b > 1) {
        if (ctx->buf_len || !ctx->final_used) {
            ERR_put_error(6, 0x65, 0x6d, 0, 0);
            return 0;
        }
        if (b > sizeof(ctx->final))
            OpenSSLDie(".\\crypto\\evp\\evp_enc.c", 0x1c9, "b <= sizeof ctx->final");
        n = ctx->final[b - 1];
        if (n == 0 || n > (int)b) {
            ERR_put_error(6, 0x65, 0x64, 0, 0);
            return 0;
        }
        for (i = 0; i < n; i++) {
            if (ctx->final[--b] != n) {
                ERR_put_error(6, 0x65, 0x64, 0, 0);
                return 0;
            }
        }
        n = ctx->cipher->block_size - n;
        for (i = 0; i < n; i++)
            out[i] = ctx->final[i];
        *outl = n;
        return 1;
    }
    *outl = 0;
    return 1;
}

// @ 0x01176db0
int __cdecl EVP_CIPHER_CTX_set_key_length(evp_cipher_ctx_st* x, int keylen)
{
    if (x->cipher->flags & 0x80)
        return EVP_CIPHER_CTX_ctrl(x, 1, keylen, 0);
    if (x->key_len == keylen)
        return 1;
    if (keylen > 0 && (x->cipher->flags & 0x8)) {
        x->key_len = keylen;
        return 1;
    }
    ERR_put_error(6, 0x7a, 0x82, 0, 0);
    return 0;
}

// ---------------------------------------------------------------- BIO
// @ 0x01176fc0
int __cdecl BIO_read(bio_st* b, void* data, int len)
{
    int i;
    bio_info_cb cb;

    if (b == 0 || b->method == 0 || b->method->bread == 0) {
        ERR_put_error(0x20, 0x6f, 0x79, 0, 0);
        return -2;
    }
    cb = b->callback;
    if (cb != 0 && (i = cb(b, 2, (const char*)data, len, 0, 1)) <= 0)
        return i;
    if (!b->init) {
        ERR_put_error(0x20, 0x6f, 0x78, 0, 0);
        i = -2;
    } else {
        i = b->method->bread(b, (char*)data, len);
        if (i > 0)
            b->num_read += i;
        if (cb != 0)
            i = cb(b, 0x82, (const char*)data, len, 0, i);
    }
    return i;
}

// @ 0x01177070
int __cdecl BIO_write(bio_st* b, const void* data, int len)
{
    int i;
    bio_info_cb cb;

    if (b == 0)
        return 0;
    cb = b->callback;
    if (b->method == 0 || b->method->bwrite == 0) {
        ERR_put_error(0x20, 0x71, 0x79, 0, 0);
        return -2;
    }
    if (cb != 0 && (i = cb(b, 3, (const char*)data, len, 0, 1)) <= 0)
        return i;
    if (!b->init) {
        ERR_put_error(0x20, 0x71, 0x78, 0, 0);
        i = -2;
    } else {
        i = b->method->bwrite(b, (const char*)data, len);
        if (i > 0)
            b->num_write += i;
        if (cb != 0)
            i = cb(b, 0x83, (const char*)data, len, 0, i);
    }
    return i;
}

// @ 0x01177120
int __cdecl BIO_puts(bio_st* b, const char* buf)
{
    int i;
    bio_info_cb cb;

    if (b == 0 || b->method == 0 || b->method->bputs == 0) {
        ERR_put_error(0x20, 0x6e, 0x79, 0, 0);
        return -2;
    }
    cb = b->callback;
    if (cb != 0 && (i = cb(b, 4, buf, 0, 0, 1)) <= 0)
        return i;
    if (!b->init) {
        ERR_put_error(0x20, 0x6e, 0x78, 0, 0);
        i = -2;
    } else {
        i = b->method->bputs(b, buf);
        if (i > 0)
            b->num_write += i;
        if (cb != 0)
            i = cb(b, 0x84, buf, 0, 0, i);
    }
    return i;
}

// @ 0x011771c0
int __cdecl BIO_gets(bio_st* b, char* buf, int size)
{
    int i;
    bio_info_cb cb;

    if (b == 0 || b->method == 0 || b->method->bgets == 0) {
        ERR_put_error(0x20, 0x68, 0x79, 0, 0);
        return -2;
    }
    cb = b->callback;
    if (cb != 0 && (i = cb(b, 5, buf, size, 0, 1)) <= 0)
        return i;
    if (!b->init) {
        ERR_put_error(0x20, 0x68, 0x78, 0, 0);
        i = -2;
    } else {
        i = b->method->bgets(b, buf, size);
        if (cb != 0)
            i = cb(b, 0x85, buf, size, 0, i);
    }
    return i;
}

// @ 0x01177260
long __cdecl BIO_ctrl(bio_st* b, int cmd, long larg, void* parg)
{
    long ret;
    bio_info_cb cb;

    if (b == 0)
        return 0;
    if (b->method == 0 || b->method->ctrl == 0) {
        ERR_put_error(0x20, 0x67, 0x79, 0, 0);
        return -2;
    }
    cb = b->callback;
    if (cb != 0 && (ret = cb(b, 6, (const char*)parg, cmd, larg, 1)) <= 0)
        return ret;
    ret = b->method->ctrl(b, cmd, larg, parg);
    if (cb != 0)
        ret = cb(b, 0x86, (const char*)parg, cmd, larg, ret);
    return ret;
}

// @ 0x011772f0
long __cdecl BIO_callback_ctrl(bio_st* b, int cmd, bio_info_cb* fp)
{
    long ret;
    bio_info_cb cb;

    if (b == 0)
        return 0;
    if (b->method == 0 || b->method->callback_ctrl == 0) {
        ERR_put_error(0x20, 0x83, 0x79, 0, 0);
        return -2;
    }
    cb = b->callback;
    if (cb != 0 && (ret = cb(b, 6, (const char*)&fp, cmd, 0, 1)) <= 0)
        return ret;
    ret = b->method->callback_ctrl(b, cmd, fp);
    if (cb != 0)
        ret = cb(b, 0x86, (const char*)&fp, cmd, 0, ret);
    return ret;
}

// @ 0x01177500
bio_st* __cdecl BIO_new_mem_buf(void* buf, int len)
{
    bio_st* ret;
    buf_mem_st* bm;

    if (buf == 0) {
        ERR_put_error(0x20, 0x7e, 0x73, 0, 0);
        return 0;
    }
    if (len == -1) {
        const char* p = (const char*)buf;
        const char* q = p + 1;
        uchar c;
        do {
            c = *p++;
        } while (c);
        len = (int)(p - q);
    }
    ret = BIO_new(&BIO_s_mem_object);
    if (ret == 0)
        return 0;
    bm = (buf_mem_st*)ret->ptr;
    bm->length = len;
    bm->max = len;
    bm->data = (char*)buf;
    ret->flags |= 0x200;
    ret->num = 0;
    return ret;
}

// @ 0x01177940
int __cdecl cb_write_str(bio_st* b, const char* str)
{
    const char* p = str;
    const char* q = p + 1;
    uchar c;
    do {
        c = *p++;
    } while (c);
    return mem_write(b, str, (int)(p - q));
}

// @ 0x01177680
int __cdecl mem_write(bio_st* b, const char* in, int inl)
{
    buf_mem_st* bm = (buf_mem_st*)b->ptr;
    int ret = -1;
    int blen;

    if (in == 0) {
        ERR_put_error(0x20, 0x75, 0x73, 0, 0);
        goto end;
    }
    if (b->flags & 0x200) {
        ERR_put_error(0x20, 0x75, 0x7e, 0, 0);
        goto end;
    }
    BIO_clear_flags(b, 0xf);
    blen = bm->length;
    if (BUF_MEM_grow_clean(bm, blen + inl) != blen + inl)
        goto end;
    memcpy(&bm->data[blen], in, inl);
    ret = inl;
end:
    return ret;
}

// @ 0x011778c0
int __cdecl mem_gets(bio_st* b, char* buf, int size)
{
    int i, j, ret;
    buf_mem_st* bm;

    BIO_clear_flags(b, 0xf);
    bm = (buf_mem_st*)b->ptr;
    i = bm->length;
    if (i > 0) {
        for (j = 0; j < i; j++)
            if (bm->data[j] == '\n')
                break;
        if (j == i)
            BIO_set_flags(b, 9);
        else
            j++;
        if (size - 1 < j)
            j = size - 1;
        ret = mem_read(b, buf, j);
        if (ret > 0)
            buf[ret] = 0;
        return ret;
    }
    *buf = 0;
    return 0;
}

// @ 0x01177470
bio_st* __cdecl BIO_new(bio_method_st* type)
{
    bio_st* ret;

    ret = (bio_st*)CRYPTO_malloc(sizeof(bio_st), ".\\crypto\\bio\\bio_lib.c", 0x46);
    if (ret == 0) {
        ERR_put_error(0x20, 0x6c, 0x41, 0, 0);
        return 0;
    }
    if (BIO_set(ret, type) == 0) {
        CRYPTO_free(ret);
        ret = 0;
    }
    return ret;
}

// @ 0x01176a90
int __cdecl EVP_CIPHER_CTX_ctrl(evp_cipher_ctx_st* ctx, int type, int arg, void* ptr)
{
    int ret;

    if (ctx->cipher == 0) {
        ERR_put_error(6, 0x7c, 0x83, 0, 0);
        return 0;
    }
    if (ctx->cipher->ctrl == 0) {
        ERR_put_error(6, 0x7c, 0x84, 0, 0);
        return 0;
    }
    ret = ctx->cipher->ctrl(ctx, type, arg, ptr);
    if (ret == -1) {
        ERR_put_error(6, 0x7c, 0x85, 0, 0);
        return 0;
    }
    return ret;
}

// @ 0x01176b00
int __cdecl EVP_CipherInit_ex(evp_cipher_ctx_st* ctx, const evp_cipher_st* cipher, void* impl,
                              const uchar* key, const uchar* iv, int enc)
{
    if (enc == -1)
        enc = ctx->encrypt;
    else {
        if (enc)
            enc = 1;
        ctx->encrypt = enc;
    }
    if (ctx->engine == 0 || ctx->cipher == 0 ||
        (cipher != 0 && cipher->nid != ctx->cipher->nid)) {
        if (cipher == 0) {
            if (ctx->cipher == 0) {
                ERR_put_error(6, 0x7b, 0x83, 0, 0);
                return 0;
            }
        } else {
            EVP_CIPHER_CTX_cleanup(ctx);
            ctx->encrypt = enc;
            if (impl != 0) {
                if (!ENGINE_init(impl))
                    goto err;
            } else
                impl = ENGINE_get_cipher_engine(cipher->nid);
            if (impl != 0) {
                cipher = ENGINE_get_cipher(impl, cipher->nid);
                if (cipher == 0)
                    goto err;
                ctx->engine = impl;
            } else
                ctx->engine = 0;
            ctx->cipher = cipher;
            if (cipher->ctx_size) {
                ctx->cipher_data = CRYPTO_malloc(cipher->ctx_size, ".\\crypto\\evp\\evp_enc.c", 0xa1);
                if (ctx->cipher_data == 0) {
                    ERR_put_error(6, 0x7b, 0x41, 0, 0);
                    return 0;
                }
            } else
                ctx->cipher_data = 0;
            ctx->key_len = cipher->key_len;
            ctx->flags = 0;
            if (cipher->flags & 0x40) {
                if (!EVP_CIPHER_CTX_ctrl(ctx, 1, 0, 0))
                    goto err;
            }
        }
    }
    {
        int bs = ctx->cipher->block_size;
        if (bs != 1 && bs != 8 && bs != 0x10)
            OpenSSLDie(".\\crypto\\evp\\evp_enc.c", 0xc2,
                       "ctx->cipher->block_size == 1 || ctx->cipher->block_size == 8 || "
                       "ctx->cipher->block_size == 16");
    }
    if (!(EVP_CIPHER_CTX_flags(ctx) & 0x10)) {
        switch (EVP_CIPHER_CTX_flags(ctx) & 7) {
        case 0:
        case 1:
            break;
        case 3:
        case 4:
            ctx->num = 0;
            /* fall through */
        case 2:
            if (EVP_CIPHER_CTX_iv_length(ctx) > (int)sizeof(ctx->iv))
                OpenSSLDie(".\\crypto\\evp\\evp_enc.c", 0xd3,
                           "EVP_CIPHER_CTX_iv_length(ctx) <= (int)sizeof(ctx->iv)");
            if (iv != 0)
                memcpy(ctx->oiv, iv, EVP_CIPHER_CTX_iv_length(ctx));
            memcpy(ctx->iv, ctx->oiv, EVP_CIPHER_CTX_iv_length(ctx));
            break;
        default:
            return 0;
        }
    }
    if (key != 0 || (ctx->cipher->flags & 0x20)) {
        if (!ctx->cipher->init(ctx, key, iv, enc))
            goto err;
    }
    ctx->buf_len = 0;
    ctx->final_used = 0;
    ctx->block_mask = ctx->cipher->block_size - 1;
    return 1;
err:
    ERR_put_error(6, 0x7b, 0x86, 0, 0);
    return 0;
}
