// Slice s011cd0f0: OpenSSL bignum / ASN.1 / UI helpers shipped in the
// lib_cblock static library (modular squaring, item digests, PEM reading and
// the two UI method initialisers).

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

// ---------------------------------------------------------------------------
// OpenSSL types (opaque)
// ---------------------------------------------------------------------------
struct BIGNUM;
struct BN_CTX;
struct BUF_MEM
{
    int   length;
    char* data;
    int   max;
};
struct ASN1_ITEM;
struct ASN1_OBJECT;
struct ASN1_OCTET_STRING
{
    int   length;
    uchar* data;
};
struct EVP_MD;
struct ENGINE;
struct BIO;
struct UI_METHOD;

struct X509_EXT_INFO
{
    int m_cert_info;      // 0x00
    int m_crl_info;       // 0x04
    int m_issuer;         // 0x08
    int m_ref;            // 0x0c
    int m_pad[4];         // 0x10
    int m_extensions;     // 0x20
    int m_aux;            // 0x24
    int m_ex_flags;       // 0x28
};

struct UI_METHOD
{
    const char* m_name;
    const void* m_methods;
    int         m_data;
};

extern const char* s_OpenSSL_default_name;
extern const void* s_openssl_ui_methods;
extern const char* s_WIN32_name;
extern const void* s_win32_ui_methods;

extern "C" int   strcmp(const char* a, const char* b);
extern "C" BIO*  BIO_new(const void* type);
extern "C" const void* BIO_s_file(void);

unsigned pem_parse_block(uchar* in, int* consumed, int* lens, uchar* extra, int avail);
int      pem_finish(X509_EXT_INFO* info, BIO* bio, X509_EXT_INFO** out, uchar* payload,
                    int payloadLen, const char* name, const char* nameOut, int nameLen,
                    const char* header);

extern "C" int        ERR_put_error(int lib, int func, int reason, const char* file, int line);
extern "C" ulong      ERR_peek_error(void);
extern "C" void       ERR_clear_error(void);
extern "C" BN_CTX*    BN_CTX_new(void);
extern "C" void       BN_CTX_free(BN_CTX*);
extern "C" int        BN_sqr(BIGNUM* r, const BIGNUM* a, BN_CTX* ctx);
extern "C" void       EVP_MD_CTX_init(void* ctx);
extern "C" int        EVP_MD_CTX_cleanup(void* ctx);
extern "C" int        OBJ_obj2nid(const ASN1_OBJECT* o);
extern "C" const char* OBJ_nid2sn(int nid);
extern "C" const EVP_MD* EVP_get_digestbyname(const char* name);
extern "C" int        EVP_DigestInit_ex(void* ctx, const EVP_MD* type, ENGINE* impl);
extern "C" int        EVP_DigestUpdate(void* ctx, const void* d, unsigned long cnt);
extern "C" int        EVP_DigestFinal_ex(void* ctx, uchar* md, uint* s);
extern "C" int        ASN1_item_i2d(void* val, uchar** out, const ASN1_ITEM* it);
extern "C" int        ASN1_item_d2i(void** val, const uchar** in, long len, const ASN1_ITEM* it);
extern "C" int        ASN1_object_size(int constructed, int length, int tag);
extern "C" void       OPENSSL_cleanse(void* ptr, unsigned long len);
extern "C" void       CRYPTO_free(void* ptr);
extern "C" void*      CRYPTO_malloc(int num, const char* file, int line);
extern "C" BUF_MEM*   BUF_MEM_new(void);
extern "C" int        BUF_MEM_grow(BUF_MEM* str, unsigned long len);
extern "C" void       BUF_MEM_free(BUF_MEM* a);
extern "C" int        BIO_read(BIO* b, void* data, int len);
extern "C" int        BIO_write(BIO* b, const void* data, int len);
extern "C" unsigned long BIO_ctrl(BIO* b, int cmd, long larg, void* parg);
extern "C" const char* PEM_ASN1_read_bio(char* (*d2i)(void), const char* name, void** bio,
                                         uchar** x, long* len, const char* nm, uchar** key);

// ---------------------------------------------------------------------------
// Bignum: modular squaring on top of the caller supplied reduction method
// ---------------------------------------------------------------------------
struct BN_MOD_METHOD
{
    int (*bn_mod)(BIGNUM* r, const BIGNUM* a, const BIGNUM* m, BN_CTX* ctx);
};

// ------------------------------------------------------------------ 011cd0f0
// @ 0x011cd0f0
int BN_mod_sqr(BN_MOD_METHOD* method, BIGNUM* r, const BIGNUM* a, BN_CTX* ctx)
{
    int ret = 0;
    BN_CTX* new_ctx = 0;

    if (method == 0 || r == 0 || a == 0)
    {
        ERR_put_error(0x10, 0xc9, 0x86, 0, 0);
        return 0;
    }

    if (ctx == 0)
    {
        ctx = new_ctx = BN_CTX_new();
        if (ctx == 0)
            return 0;
    }

    BIGNUM* m = (BIGNUM*)((char*)method + 0x48);

    if (BN_sqr(r, a, ctx) != 0 &&
        method->bn_mod(r, r, m, ctx) != 0)
        ret = 1;

    if (new_ctx != 0)
    {
        BN_CTX_free(new_ctx);
        return ret;
    }
    return ret;
}

// ------------------------------------------------------------------ 011cdba0
// Digest of the DER encoding of an ASN.1 item, rendered into an ASN.1 octet
// string, using the digest named by the signature algorithm object.
// @ 0x011cdba0
int ASN1_item_digest_alg(const ASN1_ITEM* it, ASN1_OBJECT** sigalg, ASN1_OCTET_STRING** md,
                         void* data, ENGINE* engine)
{
    uchar* buf = 0;
    long   len;
    void*  ctx[4];
    int    ret = -1;

    EVP_MD_CTX_init(ctx);

    int nid = OBJ_obj2nid(*sigalg);
    const EVP_MD* type = EVP_get_digestbyname(OBJ_nid2sn(nid));

    if (type == 0)
    {
        ERR_put_error(0xd, 0xc5, 0xa1, 0, 0);
        EVP_MD_CTX_cleanup(ctx);
        return -1;
    }

    if (EVP_DigestInit_ex(ctx, type, engine) == 0)
    {
        ERR_put_error(0xd, 0xc5, 6, 0, 0);
        EVP_MD_CTX_cleanup(ctx);
        return 0;
    }

    len = ASN1_item_i2d(data, &buf, it);
    if (len == 0)
    {
        ERR_put_error(0xd, 0xc5, 0x41, 0, 0);
        EVP_MD_CTX_cleanup(ctx);
        return -1;
    }

    EVP_DigestUpdate(ctx, buf, len);
    OPENSSL_cleanse(buf, len);
    CRYPTO_free(buf);

    if (EVP_DigestFinal_ex(ctx, (uchar*)(*md)->data, (uint*)&(*md)->length) < 1)
    {
        ERR_put_error(0xd, 0xc5, 6, 0, 0);
        EVP_MD_CTX_cleanup(ctx);
        return 0;
    }

    EVP_MD_CTX_cleanup(ctx);
    return 1;
}

// ------------------------------------------------------------------ 011cdd10
// Read one PEM style block out of a BIO into a freshly grown BUF_MEM, tracking
// the BEGIN/END nesting depth and growing the buffer as data arrives.
// @ 0x011cdd10
int pem_read_bio_ex(BIO* bio, BUF_MEM** out)
{
    int depth = 0;
    int readPos = 0;
    int written = 0;
    int head = 0;
    int tail;
    uint flags;
    int len[5];
    uchar data[4];
    int i;

    BUF_MEM* buf = BUF_MEM_new();
    if (buf == 0)
    {
        ERR_put_error(0xd, 0x6b, 0x41, 0, 0);
        return -1;
    }

    ERR_clear_error();

    for (;;)
    {
        if (8 >= readPos - written)
        {
            int need = (written - readPos) + 8;
            if (BUF_MEM_grow(buf, readPos + need) == 0)
            {
                ERR_put_error(0xd, 0x6b, 0x41, 0, 0);
                BUF_MEM_free(buf);
                return -1;
            }
            i = BIO_read(bio, buf->data + readPos, need);
            if (i < 0 && readPos != written)
            {
                ERR_put_error(0xd, 0x6b, 0x8e, 0, 0);
                BUF_MEM_free(buf);
                return -1;
            }
            if (i > 0)
                readPos += i;
        }

        uchar* start = (uchar*)buf->data + written;
        head = 0;
        flags = pem_parse_block(start, &head, len, data, readPos - written);

        if ((char)flags < 0)
        {
            ulong err = ERR_peek_error();
            if ((err & 0xfff) != 0x9b)
                break;
            ERR_clear_error();
        }

        written += head;

        if ((flags & 1) == 0)
        {
            if (depth != 0 && len[0] == 0 && len[4] == 0)
            {
                depth--;
            }
            else
            {
                if (readPos - written < len[0])
                {
                    int need = (len[0] - readPos) + written;
                    if (BUF_MEM_grow(buf, readPos + need) == 0)
                    {
                        ERR_put_error(0xd, 0x6b, 0x41, 0, 0);
                        BUF_MEM_free(buf);
                        return -1;
                    }
                    for (; 0 < need; need -= i)
                    {
                        i = BIO_read(bio, buf->data + readPos, need);
                        if (i < 1)
                        {
                            ERR_put_error(0xd, 0x6b, 0x8e, 0, 0);
                            BUF_MEM_free(buf);
                            return -1;
                        }
                        readPos += i;
                    }
                }
                written += len[0];
            }

            if (depth < 1)
            {
                *out = buf;
                return written;
            }
        }
        else
        {
            depth++;
        }
    }

    BUF_MEM_free(buf);
    return -1;
}

// ------------------------------------------------------------------ 011ce070
// Allocate and zero the 0x2c byte X509 extension info record.
// @ 0x011ce070
X509_EXT_INFO* x509_ext_info_new(void)
{
    X509_EXT_INFO* info = (X509_EXT_INFO*)CRYPTO_malloc(0x2c, ".\\crypto\\asn1\\x_info.c", 0x45);
    if (info == 0)
    {
        ERR_put_error(0xd, 0xaa, 0x41, 0, 0);
        return 0;
    }

    info->m_ref = 0;
    info->m_extensions = 0;
    info->m_aux = 0;
    info->m_ex_flags = 1;
    info->m_cert_info = 0;
    info->m_crl_info = 0;
    info->m_issuer = 0;
    return info;
}

// ------------------------------------------------------------------ 011ce130
// Parse one PEM block (certificate, key or parameter set) by matching the name
// against the supported names and handing the decoded payload back.
// @ 0x011ce130
int pem_read_bio_x509_aux(BIO* bio, X509_EXT_INFO** out, const char* name, const char* header)
{
    int ret = 0;
    uchar* payload = 0;
    char*  nameOut = 0;
    int    nameLen = 0;
    int    payloadLen;
    X509_EXT_INFO* info;

    if (bio == 0)
    {
        bio = BIO_new(BIO_s_file());
        if (bio == 0)
        {
            ERR_put_error(9, 0x74, 0x41, 0, 0);
            return ret;
        }
    }

    info = x509_ext_info_new();
    if (info == 0)
        return ret;

    if (BIO_read(bio, 0, 0) != 0)
    {
        if (strcmp((const char*)payload, "CERTIFICATE") == 0)
        {
            ret = pem_finish(info, bio, out, payload, payloadLen, name, nameOut, nameLen, header);
        }
    }
    return ret;
}

// ------------------------------------------------------------------ 011ced70
// Initialise the "OpenSSL default" UI method descriptor.
// @ 0x011ced70
int ui_method_openssl(UI_METHOD* ui)
{
    if (ui == 0)
        return 0;
    ui->m_name = (const char*)&s_OpenSSL_default_name;
    ui->m_methods = &s_openssl_ui_methods;
    ui->m_data = 0;
    return 1;
}

// ------------------------------------------------------------------ 011ceda0
// Initialise the WIN32 UI method descriptor.
// @ 0x011ceda0
int ui_method_win32(UI_METHOD* ui)
{
    if (ui == 0)
        return 0;
    ui->m_name = (const char*)&s_WIN32_name;
    ui->m_methods = &s_win32_ui_methods;
    ui->m_data = 0;
    return 1;
}

// ------------------------------------------------------------------ 011cedf0
// Measure and copy the PEM header of the given name into a BUF_MEM, skipping
// the characters the PEM character class table marks as white space.
// @ 0x011cedf0
int pem_header_measure(uchar* table, uchar* name, int* out)
{
    int i;
    BUF_MEM* buf = BUF_MEM_new();
    if (buf == 0)
        return 0;

    uchar* p = name;
    while (*p != 0)
        ++p;

    if (BUF_MEM_grow(buf, (p - name) + 1) == 0)
    {
        BUF_MEM_free(buf);
        return 0;
    }

    uchar* src = name;
    int len = 0;
    while (*src != 0)
    {
        uchar c = *src;
        ushort cls = *(ushort*)(table + (uint)c * 2);

        if (cls & 0x40)
        {
            ++src;
            uchar d = *src;
            cls = *(ushort*)(table + (uint)d * 2);
            while ((cls & 8) == 0 && d != c)
            {
                if (cls & 0x20)
                {
                    d = src[1];
                    ++src;
                    if ((*(ushort*)(table + (uint)d * 2) & 8) != 0)
                        break;
                }
                buf->data[len++] = (char)d;
                d = src[1];
                cls = *(ushort*)(table + (uint)d * 2);
            }
            src += 2;
            buf->data[len++] = (char)c;
        }
        else
        {
            buf->data[len++] = (char)c;
            ++src;
        }
    }

    buf->data[len] = 0;
    *out = len;
    return 1;
}
