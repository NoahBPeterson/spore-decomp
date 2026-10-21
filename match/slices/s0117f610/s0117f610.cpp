// Slice s0117f610 -- OpenSSL X509V3 / SSL session + ClientHello plumbing (lib_cblock /
// lib_openssl): the extension d2i wrapper, the NID -> X509V3_EXT_METHOD lookups (standard
// table first, then the run-time extension hash), the three X509 extension accessors, the
// session allocator/copier/lookup and the ClientHello writer.
//
// Flags: /O2 /MD /Gy /TP
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

struct SSL;
struct SSL_CTX;
struct SSL_SESSION;
struct SSL_METHOD;

// ---------------------------------------------------------------------------
// Callees
// ---------------------------------------------------------------------------
extern "C" int   OBJ_obj2nid(int obj);                          // 0x117fa60
extern "C" void* FUN_0117f580(int nid);                         // 0x117f580  X509V3_EXT_get_nid
extern "C" void* ASN1_item_d2i(int a, void** pp, int len, void* it); // 0x117f530
extern "C" void* lh_retrieve(void* lh, void* data);             // 0x1194260
extern "C" void  ERR_put_error(int lib, int func, int reason, char* file, int line); // 0x1180d50
extern "C" int   X509v3_get_ext_count(void* sk);                // 0x11800b0
extern "C" int   X509v3_get_ext_by_OBJ(void* sk, void* obj, int lastpos); // 0x1180190
extern "C" void* X509V3_get_d2i(void* sk, int nid, int* crit, int* idx);  // 0x117f680

extern "C" void* CRYPTO_malloc(int size, const char* file, int line);     // 0x1183410
extern "C" void* memset_(void* dst, int value, u32 size);                 // 0x11e073e
extern "C" void* memcpy_(void* dst, const void* src, u32 size);           // 0x11e0744
extern "C" int   memcmp(const void* a, const void* b, u32 size);
extern "C" int   CRYPTO_new_ex_data(int idx, void* obj, void* ad);        // 0x1184260
extern "C" int   CRYPTO_add_lock(int* p, int n, int type, const char* file, int line); // 0x11815d0
extern "C" void  CRYPTO_lock(int mode, int type, const char* file, int line); // 0x1181540
extern "C" __declspec(dllimport) __int64 __cdecl _time64(__int64* t); // 0x13cc55c
extern "C" int   SSL_set_ssl_method(SSL* s, SSL_METHOD* method); // 0x117c190
extern "C" int   SSL_get_default_timeout(SSL* s);               // 0x117b400
extern "C" void  SSL_SESSION_free(void* sess);                  // 0x1181750
extern "C" int   SSL_has_matching_session_id(SSL* s, const void* id, u32 len); // 0x117b260
extern "C" int   SSL_CTX_add_session(SSL_CTX* ctx, SSL_SESSION* sess);   // 0x1181d80
extern "C" void  remove_session_lock(int i);                    // 0x1181be0
extern "C" int   def_generate_session_id(SSL* s, u8* id, u32* len);      // 0x1181700
extern "C" SSL_METHOD* SSLv3_method(void);                      // 0x11a5020
extern "C" SSL_METHOD* TLSv1_method(void);                      // 0x11a2750
extern "C" int   F_0117c300(SSL* s, int a);                     // 0x117c300  ssl23_setup_init_buffer
extern "C" int   ssl23_read_bytes(SSL* s, int n);               // 0x11a50a0
extern "C" int   ssl23_write_bytes(SSL* s);                     // 0x11a5030
extern "C" void* SSL_get_ciphers(SSL* s);                       // 0x117b720
extern "C" int   ssl_cipher_list_to_bytes(SSL* s, void* sk, u8* p,
                                          int (*put)(void*, u8*)); // 0x117b7d0
extern "C" int   RAND_pseudo_bytes(u8* buf, int n);             // 0x1178650
extern "C" int   sk_num(void* sk);                              // 0x117dde0
extern "C" int   ssl3_put_cipher_by_char(void* c, u8* p);       // 0x119ff30
extern "C" void* sk_value(void* sk, int i);                     // 0x117ddf0
extern "C" void  FUN_011a5950(SSL* s, u8* p, int n);            // 0x11a5950  ssl3_finish_mac
extern "C" int   SSL_connect(SSL* s);                           // 0x117ce30

// 0x015c6980 : the standard extension table, 0x18 bytes per NID entry.
extern "C" int g_stdExts_15c6980[];
// 0x016f199c : the hash of extensions registered at run time.
extern "C" void* g_extHash_16f199c;
// 0x014e4a18 : the source file name string ".\ssl\ssl_sess.c".
extern "C" char g_sslSessC_14e4a18[];

// ---------------------------------------------------------------------------
// Minimal shapes of the ASN.1 / SSL objects this slice touches.
// ---------------------------------------------------------------------------
struct ASN1_OCTET_STRING { int length; int type; u8* data; };
struct ASN1_OBJECT       { int length; int sn; int ln; int nid; };
struct X509_EXTENSION {
    ASN1_OBJECT*       object;      // +0x00
    int                critical;    // +0x04
    ASN1_OCTET_STRING* value;       // +0x08
};

// 0x18-byte entry of the standard extension table:
// { ext_nid, ext_flags, it, new_func, free_func, d2i }.
struct ExtMethod {
    int   ext_nid;                  // +0x00
    int   ext_flags;                // +0x04
    void* it;                       // +0x08
    void* new_func;                 // +0x0c
    void* free_func;                // +0x10
    void* d2i;                      // +0x14
};

// The lookup key handed to lh_retrieve: an ASN.1-ish name with a small inline name buffer.
struct ExtKey {
    int  type;                      // +0x00  always 3 here
    u8*  data;                      // +0x04  points at buf
    int  buf[2];                    // +0x08  inline name storage (never written here)
    int  nid;                       // +0x10
    int  tail[3];                   // +0x14
};

struct SSL_METHOD {
    u8   pad00[0x14];
    int  version;                                   // +0x14
    u8   pad18[0x30];
    int  (*get_cipher)(u8* p);                      // +0x48
    u8   pad4c[0x10];
    SSL_METHOD* (*get_ssl_method)(int version);     // +0x5c
};

struct SSL_CTX {
    SSL_METHOD* method;             // +0x00
    u8   pad04[0x0c];
    void* sessions;                 // +0x10  session cache (lh)
    u8   pad14[0x0c];
    int  options;                   // +0x20
    int  session_timeout;           // +0x24
    u8   pad28[0x08];
    SSL_SESSION* (*get_session_cb)(SSL*, u8*, int, int*); // +0x30
    u8   pad34[0x18];
    int  session_cache_full;        // +0x4c
    int  session_cache_timeout;     // +0x50
    u8   pad54[0x04];
    int  session_cache_hits;        // +0x58
    int  session_cache_miss;        // +0x5c
    u8   pad60[0x38];
    void* client_CA;                // +0x98
    void  (*info_callback)(SSL*, int, int); // +0x9c
    u8   pad_a0[0x4c];
    int  (*generate_session_id)(SSL*, u8*, u32*); // +0xec
};

// ssl_session_st, the fields this slice reads or writes.
struct SSL_SESSION {
    int      ssl_version;           // +0x00
    u8       pad04[0x40];
    u32      session_id_length;     // +0x44
    u8       session_id[0x20];      // +0x48
    u32      sid_ctx_length;        // +0x68
    u8       sid_ctx[0x20];         // +0x6c
    u8       pad8c[0x0c];
    int      verify_result;         // +0x98
    int      references;            // +0x9c
    int      timeout;               // +0xa0
    int      time;                  // +0xa4
    void*    cipher;                // +0xa8
    int      cipher_id;             // +0xac
    int      f_b0;                  // +0xb0
    u8       pad_b4[0x04];
    u8       ex_data[8];            // +0xb8
    int      f_c0;                  // +0xc0
    int      f_c4;                  // +0xc4
};

struct SSL {
    int         version;            // +0x00
    u8          pad04[0x04];
    SSL_METHOD* method;             // +0x08
    u8          pad0c[0x0c];
    int         in_handshake;       // +0x18
    u8          pad1c[0x04];
    int         version2;           // +0x20
    u8          pad24[0x10];
    int         state;              // +0x34
    int         rstate;             // +0x38
    int*        rbuf;               // +0x3c  { len, data, ... }
    u8          pad40[0x04];
    int         init_off;           // +0x44
    int         init_num;           // +0x48
    u8*         init_buf;           // +0x4c  data buffer
    int         num;                // +0x50
    u8          pad54[0x04];
    u8*         s3;                 // +0x58  ssl3 state
    u8          pad5c[0x08];
    void        (*msg_callback)(int write_p, int version, int content_type,
                                const void* buf, u32 len, SSL* ssl, void* arg); // +0x64
    void*       msg_callback_arg;   // +0x68
    u8          pad6c[0x2c];
    u32         sid_ctx_length;     // +0x98
    u8          sid_ctx[0x20];      // +0x9c
    SSL_SESSION* session;           // +0xbc
    int         (*generate_session_id)(SSL*, u8*, u32*); // +0xc0
    u8          f_c4;               // +0xc4
    u8          pad_c5[0x07];
    void*       f_cc;               // +0xcc
    u8          pad_d0[0x08];
    SSL_CTX*    ctx;                // +0xd8
    int         f_dc;               // +0xdc
    int         verify_result;      // +0xe0
    u8          pad_e4[0x10];
    int         options;            // +0xf4
    u8          pad_f8[0x0c];
    int         client_version;     // +0x104
};

// The session-cache lookup key: an ssl_session_st truncated to the fields the
// cache hash reads (version + session id) and padded to the original's 0xd0-byte slot.
struct SessKey {
    int  ssl_version;               // +0x00
    u8   pad04[0x40];
    u32  session_id_length;         // +0x44
    u8   session_id[0x20];          // +0x48
    u8   pad68[0xd0 - 0x68];        // +0x68
};

// Forward declarations of the intra-slice callees.
SSL_SESSION* session_new_1181660();
SSL_SESSION* get_new_session_1181a10(SSL* s, int tls1);

// ===========================================================================
// 0x0117f610  X509V3_EXT_d2i: decode the extension payload with its method
// ===========================================================================
// @ 0x0117f610
void* Ext_d2i_117f610(X509_EXTENSION* ext)
{
    int nid = OBJ_obj2nid((int)ext->object);
    if (nid == 0)
        return 0;
    ExtMethod* method = (ExtMethod*)FUN_0117f580(nid);
    if (method == 0)
        return 0;
    u8* p = ext->value->data;
    if (method->it != 0)
        return ASN1_item_d2i(0, (void**)&p, ext->value->length, method->it);
    return ((void* (__cdecl*)(int, void**, int))method->d2i)(0, (void**)&p, ext->value->length);
}

// ===========================================================================
// 0x0117f770  extension method for a NID (standard table, then the hash)
// ===========================================================================
// @ 0x0117f770
ExtMethod* Ext_get_nid_117f770(u32 nid)
{
    if (nid <= 0x30b) {
        if (nid == 0 || g_stdExts_15c6980[nid * 6 + 2] != 0)
            return (ExtMethod*)&g_stdExts_15c6980[nid * 6];
    } else {
        if (g_extHash_16f199c == 0)
            return 0;
        ExtKey key;
        key.nid  = (int)nid;
        key.type = 3;
        key.data = (u8*)key.buf;
        int* r = (int*)lh_retrieve(g_extHash_16f199c, &key);
        if (r != 0)
            return (ExtMethod*)r[1];
    }
    ERR_put_error(8, 0x67, 0x65, 0, 0);
    return 0;
}

// ===========================================================================
// 0x0117f7f0  first field (ext_nid) of the extension method for a NID
// ===========================================================================
// @ 0x0117f7f0
int Ext_get_nid_a_117f7f0(u32 nid)
{
    if (nid <= 0x30b) {
        if (nid == 0 || g_stdExts_15c6980[nid * 6 + 2] != 0)
            return g_stdExts_15c6980[nid * 6];
    } else {
        if (g_extHash_16f199c == 0)
            return 0;
        ExtKey key;
        key.nid  = (int)nid;
        key.type = 3;
        key.data = (u8*)key.buf;
        int* r = (int*)lh_retrieve(g_extHash_16f199c, &key);
        if (r != 0)
            return *(int*)r[1];
    }
    ERR_put_error(8, 0x68, 0x65, 0, 0);
    return 0;
}

// ===========================================================================
// 0x0117f870  second field (ext_flags) of the extension method for a NID
// ===========================================================================
// @ 0x0117f870
int Ext_get_nid_b_117f870(u32 nid)
{
    if (nid <= 0x30b) {
        if (nid == 0 || g_stdExts_15c6980[nid * 6 + 2] != 0)
            return g_stdExts_15c6980[nid * 6 + 1];
    } else {
        if (g_extHash_16f199c == 0)
            return 0;
        ExtKey key;
        key.nid  = (int)nid;
        key.type = 3;
        key.data = (u8*)key.buf;
        int* r = (int*)lh_retrieve(g_extHash_16f199c, &key);
        if (r != 0)
            return *(int*)((char*)r[1] + 4);
    }
    ERR_put_error(8, 0x66, 0x65, 0, 0);
    return 0;
}

// ===========================================================================
// 0x011801b0  X509_get_ext_count
// ===========================================================================
// @ 0x011801b0
int X509_get_ext_count_11801b0(int* x)
{
    return X509v3_get_ext_count((void*)*(int*)(*x + 0x24));
}

// ===========================================================================
// 0x011801d0  X509_get_ext_by_OBJ
// ===========================================================================
// @ 0x011801d0
int X509_get_ext_by_OBJ_11801d0(int* x, void* obj, int lastpos)
{
    return X509v3_get_ext_by_OBJ((void*)*(int*)(*x + 0x24), obj, lastpos);
}

// ===========================================================================
// 0x01180210  X509_get_ext_d2i
// ===========================================================================
// @ 0x01180210
void* X509_get_ext_d2i_1180210(int* x, int nid, int* crit, int* idx)
{
    return X509V3_get_d2i((void*)*(int*)(*x + 0x24), nid, crit, idx);
}

// ===========================================================================
// 0x01181660  SSL_SESSION_new
// ===========================================================================
// @ 0x01181660
SSL_SESSION* session_new_1181660()
{
    SSL_SESSION* ss = (SSL_SESSION*)CRYPTO_malloc(0xc8, g_sslSessC_14e4a18, 0x6e);
    if (ss == 0) {
        ERR_put_error(0x14, 0xbd, 0x41, 0, 0);
        return 0;
    }
    memset_(ss, 0, 0xc8);
    ss->verify_result = 1;
    ss->references = 1;
    ss->timeout = 0x130;
    ss->time = (int)_time64(0);
    ss->f_c0 = 0;
    ss->f_c4 = 0;
    ss->cipher = 0;
    CRYPTO_new_ex_data(3, ss, ss->ex_data);
    return ss;
}

// ===========================================================================
// 0x01181810  SSL_set_session
// ===========================================================================
// @ 0x01181810
int set_session_1181810(SSL* s, SSL_SESSION* sess)
{
    SSL_METHOD* meth;
    int timeout;

    if (sess != 0) {
        meth = s->ctx->method->get_ssl_method(sess->ssl_version);
        if (meth == 0) {
            meth = s->method->get_ssl_method(sess->ssl_version);
            if (meth == 0) {
                ERR_put_error(0x14, 0xc3, 0xf0, 0, 0);
                return 0;
            }
        }
        if (meth != s->method) {
            if (!SSL_set_ssl_method(s, meth))
                return 0;
            timeout = s->ctx->session_timeout;
            if (timeout == 0)
                timeout = SSL_get_default_timeout(s);
            sess->timeout = timeout;
        }
        CRYPTO_add_lock(&sess->references, 1, 0xe, g_sslSessC_14e4a18, 0x27f);
        if (s->session != 0)
            SSL_SESSION_free(s->session);
        s->session = sess;
        s->verify_result = sess->verify_result;
        return 1;
    }

    if (s->session != 0) {
        SSL_SESSION_free(s->session);
        s->session = 0;
    }
    if (s->ctx->method != s->method) {
        if (!SSL_set_ssl_method(s, s->ctx->method))
            return 0;
    }
    return 1;
}

// ===========================================================================
// 0x01181a10  SSL_get_new_session
// ===========================================================================
// @ 0x01181a10
SSL_SESSION* get_new_session_1181a10(SSL* s, int tls1)
{
    SSL_SESSION* sess = session_new_1181660();
    if (sess == 0)
        return 0;

    int timeout = s->ctx->session_timeout;
    if (timeout == 0)
        timeout = SSL_get_default_timeout(s);
    sess->timeout = timeout;

    if (s->session != 0) {
        SSL_SESSION_free(s->session);
        s->session = 0;
    }

    if (tls1 == 0) {
        sess->session_id_length = 0;
        goto sid_ctx;
    }

    {
        int v = s->version;
        if (v == 2) {
            sess->ssl_version = v;
            sess->session_id_length = 0x10;
        } else if (v == 0x300 || v == 0x301 || v == 0xfeff) {
            sess->ssl_version = v;
            sess->session_id_length = 0x20;
        } else {
            ERR_put_error(0x14, 0xb5, 0x103, 0, 0);
            goto err;
        }
    }

    {
        int (*gen)(SSL*, u8*, u32*);
        CRYPTO_lock(5, 0xc, g_sslSessC_14e4a18, 0xe7);
        gen = s->generate_session_id;
        if (gen == 0 && s->ctx->generate_session_id != 0)
            gen = s->ctx->generate_session_id;
        else if (gen == 0)
            gen = def_generate_session_id;
        CRYPTO_lock(6, 0xc, g_sslSessC_14e4a18, 0xec);

        u32 len = sess->session_id_length;
        if (!gen(s, sess->session_id, &len)) {
            ERR_put_error(0x14, 0xb5, 0x12d, 0, 0);
            goto err;
        }
        if (len == 0 || len > sess->session_id_length) {
            ERR_put_error(0x14, 0xb5, 0x12f, 0, 0);
            goto err;
        }
        if (len < sess->session_id_length && s->version == 2)
            memset_(sess->session_id + len, 0, sess->session_id_length - len);
        else
            sess->session_id_length = len;
        if (SSL_has_matching_session_id(s, sess->session_id, sess->session_id_length)) {
            ERR_put_error(0x14, 0xb5, 0x12e, 0, 0);
            goto err;
        }
    }

sid_ctx:
    if (s->sid_ctx_length > sizeof(sess->sid_ctx)) {
        ERR_put_error(0x14, 0xb5, 0x44, 0, 0);
        goto err;
    }
    memcpy_(sess->sid_ctx, s->sid_ctx, s->sid_ctx_length);
    sess->sid_ctx_length = s->sid_ctx_length;
    s->session = sess;
    sess->ssl_version = s->version;
    sess->verify_result = 0;
    return sess;

err:
    SSL_SESSION_free(sess);
    return 0;
}

// ===========================================================================
// 0x01181f50  ssl_get_prev_session: look the session id up in the cache
// ===========================================================================
// @ 0x01181f50
int get_prev_session_1181f50(SSL* s, const u8* id, int len)
{
    SessKey      key;
    SSL_SESSION* sess;
    int          not_resumable;
    int          check_error = 0;

    if (len > 0x20 || len == 0)
        return 0;

    if (!(s->ctx->options & 0x100)) {
        key.ssl_version = s->version;
        key.session_id_length = len;
        memcpy_(key.session_id, id, len);

        CRYPTO_lock(5, 0xc, g_sslSessC_14e4a18, 0x152);
        sess = (SSL_SESSION*)lh_retrieve(s->ctx->sessions, &key);
        if (sess != 0)
            CRYPTO_add_lock(&sess->references, 1, 0xe, g_sslSessC_14e4a18, 0x156);
        CRYPTO_lock(6, 0xc, g_sslSessC_14e4a18, 0x157);
        if (sess == 0)
            goto new_session;
    } else {
new_session:
        not_resumable = 1;
        s->ctx->session_cache_full++;
        if (s->ctx->get_session_cb == 0)
            return 0;
        sess = s->ctx->get_session_cb(s, (u8*)id, len, &not_resumable);
        if (sess == 0)
            return 0;
        s->ctx->session_cache_miss++;
        if (not_resumable != 0)
            CRYPTO_add_lock(&sess->references, 1, 0xe, g_sslSessC_14e4a18, 0x16c);
        if (!(s->ctx->options & 0x200))
            SSL_CTX_add_session(s->ctx, sess);
    }

    if (sess->sid_ctx_length != s->sid_ctx_length ||
        memcmp(sess->sid_ctx, s->sid_ctx, sess->sid_ctx_length) != 0)
        goto free_it;

    if ((s->f_c4 & 1) && s->sid_ctx_length == 0) {
        ERR_put_error(0x14, 0xd9, 0x115, 0, 0);
        check_error = 1;
        goto free_it;
    }

    if (sess->cipher_id == 0) {
        u32   cid = (u32)sess->f_b0;
        u8    b[4];
        u8*   p;
        b[0] = (u8)(cid >> 24);
        b[1] = (u8)(cid >> 16);
        b[2] = (u8)(cid >> 8);
        b[3] = (u8)cid;
        p = (sess->ssl_version & 0xffffff00) == 0x300 ? &b[2] : &b[1];
        sess->cipher_id = s->method->get_cipher(p);
        if (sess->cipher_id == 0)
            goto free_it;
    }

    if (sess->timeout >= (int)_time64(0) - sess->time) {
        s->ctx->session_cache_hits++;
        if (s->session != 0)
            SSL_SESSION_free(s->session);
        s->session = sess;
        s->verify_result = sess->verify_result;
        return 1;
    }
    s->ctx->session_cache_timeout++;
    remove_session_lock(1);

free_it:
    SSL_SESSION_free(sess);
    return check_error ? -1 : 0;
}

// ===========================================================================
// 0x01182240  method for a protocol version (SSLv3 / TLSv1)
// ===========================================================================
// @ 0x01182240
SSL_METHOD* Method_by_version_1182240(int version)
{
    if (version == 0x300)
        return SSLv3_method();
    if (version == 0x301)
        return TLSv1_method();
    return 0;
}

// ===========================================================================
// 0x01182260  ssl23_client_hello: build and send the ClientHello
// ===========================================================================
// @ 0x01182260
int client_hello_1182260(SSL* s)
{
    u8   maj, min;
    u8*  d;
    u8*  p;
    u8*  start;
    int  ssl2_compat;
    int  version;
    int  len;
    int  n;
    int  ret;
    u32  opt = (u32)s->options;

    ssl2_compat = (~(opt >> 24) & 1);
    version = 0;
    if (!(opt & 0x4000000))
        version = 0x301;
    else if (!(opt & 0x2000000))
        version = 0x300;
    else if (!(opt & 0x1000000))
        version = 2;

    d = (u8*)s->rbuf[1];

    if (s->state == 0x1210) {
        u8* rnd = s->s3 + 0xb8;
        u32 t = (u32)_time64(0);
        rnd[0] = (u8)(t >> 24);
        rnd[1] = (u8)(t >> 16);
        rnd[2] = (u8)(t >> 8);
        rnd[3] = (u8)t;
        if (RAND_pseudo_bytes(rnd + 4, 0x1c) <= 0)
            return -1;

        if (version == 0x301) {
            maj = 3;
            min = 1;
        } else if (version == 0x300) {
            maj = 3;
            min = 0;
        } else if (version == 2) {
            maj = 0;
            min = 2;
        } else {
            ERR_put_error(0x14, 0x74, 0xbf, 0, 0);
            return -1;
        }
        s->client_version = version;

        if (ssl2_compat) {
            /* SSLv2-style CLIENT-HELLO */
            d[2] = 1;
            d[3] = maj;
            d[4] = min;
            p = d + 11;
            len = ssl_cipher_list_to_bytes(s, SSL_get_ciphers(s), p, 0);
            if (len == 0) {
                ERR_put_error(0x14, 0x74, 0xb5, 0, 0);
                return -1;
            }
            d[5] = (u8)(len >> 8);
            d[6] = (u8)len;
            d[7] = 0;
            d[8] = 0;
            n = (s->options & 2) ? 0x10 : 0x20;
            d[7] = (u8)(n >> 8);
            d[8] = (u8)n;
            p += len;
            memset_(s->s3 + 0xb8, 0, 0x20);
            if (RAND_pseudo_bytes(s->s3 + 0xd8 - n, n) <= 0)
                return -1;
            memcpy_(p, s->s3 + 0xd8 - n, n);
            start = d + 2;
            len = (int)(p - start) + n;
            d[0] = (u8)((u32)len >> 8) | 0x80;
            d[1] = (u8)len;
            s->init_off = len + 2;
            s->init_num = 0;
            FUN_011a5950(s, start, len);
        } else {
            /* SSLv3-style ClientHello */
            d[9] = maj;
            start = d + 9;
            d[10] = min;
            n = 8;
            p = d + 11;
            {
                u32* src = (u32*)(s->s3 + 0xb8);
                u32* dst = (u32*)p;
                for (; n != 0; n--)
                    *dst++ = *src++;
            }
            p = d + 0x2b;
            *p = 0;
            p = d + 0x2c;
            len = ssl_cipher_list_to_bytes(s, SSL_get_ciphers(s), p + 2,
                                           ssl3_put_cipher_by_char);
            if (len == 0) {
                ERR_put_error(0x14, 0x74, 0xb5, 0, 0);
                return -1;
            }
            p[0] = (u8)(len >> 8);
            p[1] = (u8)len;
            p += len + 2;

            {
                void* ca = s->ctx->client_CA;
                int   i;
                int   cnt;
                cnt = ca != 0 ? sk_num(ca) : 0;
                *p++ = (u8)(cnt + 1);
                for (i = 0; i < cnt; i++)
                    *p++ = *(u8*)sk_value(s->ctx->client_CA, i);
            }
            *p = 0;
            p++;
            len = (int)(p - start);
            *p = 0x2a;
            n = len + 4;
            if ((u32)n > 0x4000) {
                ERR_put_error(0x14, 0x74, 0x44, 0, 0);
                return -1;
            }
            d[0] = 0x16;
            d[1] = maj;
            d[2] = min;
            d[3] = (u8)((u32)n >> 8);
            d[4] = (u8)n;
            s->init_off = (int)(p - d);
            s->init_num = 0;
            FUN_011a5950(s, d + 5, (int)(p - d) - 5);
        }
        s->state = 0x1211;
        s->init_num = 0;
    }

    ret = ssl23_write_bytes(s);
    if (ret >= 2 && s->msg_callback != 0) {
        if (ssl2_compat)
            s->msg_callback(1, 2, 0, (u8*)s->rbuf[1] + 2, ret - 2, s, s->msg_callback_arg);
        else
            s->msg_callback(1, version, 0x16, (u8*)s->rbuf[1] + 5, ret - 5, s, s->msg_callback_arg);
    }
    return ret;
}

// ===========================================================================
// 0x01182670  ssl23_get_server_hello: parse the first record, start the connect
// ===========================================================================
// The original receives `s` in ESI (LTCG custom register ABI), so this
// definition takes it as a normal first argument.
// @ 0x01182670
int get_server_hello_1182670(SSL* s)
{
    u8*    d;
    int    ret;
    u32    w0;
    u16    w4;
    u8     b6;
    SSL_METHOD* meth;

    ret = ssl23_read_bytes(s, 7);
    if (ret != 7)
        return ret;

    d  = s->init_buf;
    w0 = *(u32*)d;
    w4 = *(u16*)(d + 4);
    b6 = d[6];

    if ((signed char)d[0] < 0 && d[2] == 4 && d[5] == 0 && d[6] == 2) {
        ERR_put_error(0x14, 0x77, 0x102, 0, 0);
        return -1;
    }

    if (d[0] == 0x16 && d[1] == 3 && (d[2] == 0 || d[2] == 1) && d[5] == 2) {
        if (F_0117c300(s, 1) == 0)
            return -1;
        s->state = 0x1120;
        s->rstate = 0xf0;
        s->num = 7;
        s->init_buf = *(u8**)(s->s3 + 0xe0);
        *(u32*)s->init_buf = w0;
        *(u16*)(s->init_buf + 4) = w4;
        s->init_buf[6] = b6;
        *(u32*)(s->s3 + 0xec) = 7;
        *(u32*)(s->s3 + 0xe8) = 0;

        if (d[2] == 0 && !(s->options & 0x2000000)) {
            s->version = 0x300;
            meth = SSLv3_method();
        } else if (d[2] == 1 && !(s->options & 0x4000000)) {
            s->version = 0x301;
            meth = TLSv1_method();
        } else {
            ERR_put_error(0x14, 0x77, 0x102, 0, 0);
            return -1;
        }
        s->method = meth;
        s->version2 = meth->version;
        s->init_off = 0;

        if (get_new_session_1181a10(s, 0) == 0)
            return -1;
        return SSL_connect(s);
    }

    if (d[0] == 0x15 && d[1] == 3 && (d[2] == 0 || d[2] == 1) && d[3] == 0 && d[4] == 2) {
        void (*fn)(SSL*, int, int) = s->ctx->info_callback;
        if (s->f_cc != 0) {
            fn = (void (*)(SSL*, int, int))s->f_cc;
        }
        if (fn != 0)
            fn(s, 0x4004, ((int)d[5] << 8) | d[6]);
        s->in_handshake = 1;
        ERR_put_error(0x14, 0x77, d[6] + 0x3e8, 0, 0);
        return -1;
    }

    ERR_put_error(0x14, 0x77, 0xfc, 0, 0);
    return -1;
}
