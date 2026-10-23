// s0117c560 -- OpenSSL 0.9.8 SSL/X509/ASN1 helpers used by the Spore client.
// Reconstructed from the shipped PE; struct layouts and offsets follow the OpenSSL 0.9.8 headers.
//
// Module flags: /O2 /MD /Gy /TP

#include <string.h>

struct ssl_st;
struct ssl_ctx_st;
struct ssl_method_st;
struct X509_NAME;
struct X509_NAME_ENTRY;
struct ASN1_OBJECT;
struct ASN1_STRING;
struct ASN1_TYPE;
struct ASN1_TLC;
struct asn1_template_st;

// ---------------------------------------------------------------------------------------------------------
// referenced objects
// ---------------------------------------------------------------------------------------------------------
struct ssl_method_st
{
	void* v00;                                        // 0x000
	int (*ssl_new)(ssl_st*);                          // 0x004
	void* v08;                                        // 0x008
	void* v0c;                                        // 0x00c
	void* func_10;                                    // 0x010
	void* v14[4];                                     // 0x014
	int (*ssl_accept)(ssl_st*);                       // 0x024
	void* v28[6];                                     // 0x028
	long (*ctrl)(ssl_st*, int, long, void*);          // 0x040
	void* v44[7];                                     // 0x044
	int (*get_timeout)(void);                         // 0x060
};

struct ssl_ctx_st
{
	ssl_method_st* method;                            // 0x000
	void* cipher_list;                                // 0x004
	void* cipher_list_by_id;                          // 0x008
	void* cert_store;                                 // 0x00c
	void* sessions;                                   // 0x010
	int session_cache_size;                           // 0x014
	void* session_cache_head;                         // 0x018
	void* session_cache_tail;                         // 0x01c
	int session_cache_mode;                           // 0x020
	int session_timeout;                              // 0x024
	void* new_session_cb;                             // 0x028
	void* remove_session_cb;                          // 0x02c
	void* get_session_cb;                             // 0x030
	char pad34[0x2c];                                 // 0x034
	int references;                                   // 0x060
	int pad64;                                        // 0x064
	int pad68;                                        // 0x068
	int pad6c[5];                                     // 0x06c
	void* ex_data;                                    // 0x080
	int ex_data_dummy;                                // 0x084
	void* md5;                                        // 0x088
	void* sha1;                                       // 0x08c
	void* sha256;                                     // 0x090
	int z94;                                          // 0x094
	int z98;                                          // 0x098
	int z9c;                                          // 0x09c
	int za0;                                          // 0x0a0
	int a4;                                           // 0x0a4
	int a8;                                           // 0x0a8
	int ac;                                           // 0x0ac
	void* cache;                                      // 0x0b0
	int b4, b8, bc, c0, c4;                           // 0x0b4
	int c8, cc, d0, d4, d8, dc, e0, e4, e8, ec;       // 0x0c8
	void* verify_param;                               // 0x0f0
	int f4;                                           // 0x0f4
};

struct ssl_st
{
	int version;                                      // 0x000
	int type;                                         // 0x004
	ssl_method_st* method;                            // 0x008
	void* rbio;                                       // 0x00c
	void* wbio;                                       // 0x010
	int in_handshake;                                 // 0x014
	int rwstate;                                      // 0x018
	int pad1c;                                        // 0x01c
	void* handshake_func;                             // 0x020
	int server;                                       // 0x024
	void* new_session;                                // 0x028
	int quiet_shutdown;                               // 0x02c
	int flags30;                                      // 0x030
	int state;                                        // 0x034
	int rstate;                                       // 0x038
	void* init_buf;                                   // 0x03c
	int pad40[6];                                     // 0x040
	void* s3;                                         // 0x058
	void* p5c;                                        // 0x05c
	int f60;                                          // 0x060
	int f64;                                          // 0x064
	int f68;                                          // 0x068
	int pad6c;                                        // 0x06c
	void* verify_param;                               // 0x070
	int pad74[8];                                     // 0x074
	void* cert;                                       // 0x094
	unsigned int sid_ctx_length;                      // 0x098
	unsigned char sid_ctx[32];                        // 0x09c
	int fbc;                                          // 0x0bc
	int fc0;                                          // 0x0c0
	int fc4;                                          // 0x0c4
	int fc8;                                          // 0x0c8
	int padcc[3];                                     // 0x0cc
	ssl_ctx_st* ctx;                                  // 0x0d8
	int pad_dc;                                       // 0x0dc
	int fe0;                                          // 0x0e0
	void* ex_data;                                    // 0x0e4
	int ex_data_dummy;                                // 0x0e8
	int pad_ec;                                       // 0x0ec
	int ff0;                                          // 0x0f0
	unsigned long options;                            // 0x0f4
	unsigned long f_f8;                               // 0x0f8
	unsigned long f_fc;                               // 0x0fc
};

struct ASN1_OBJECT { int dummy; };
struct ASN1_STRING { int length; int type; unsigned char* data; };
struct X509_NAME_ENTRY
{
	ASN1_OBJECT* object;                              // 0x000
	ASN1_STRING* value;                               // 0x004
	int set;                                          // 0x008
};
struct X509_NAME
{
	void* entries;                                    // 0x000
	int modified;                                     // 0x004
};
struct X509_PUBKEY;
struct X509_CINF
{
	char pad[0x18];
	X509_PUBKEY* key;                                 // 0x018
};
struct X509
{
	X509_CINF* cert_info;                             // 0x000
};
struct EVP_PKEY
{
	int type;                                         // 0x000
};
struct ASN1_TLC
{
	unsigned char valid;                              // 0x000
	int ret;                                          // 0x004
	long plen;                                        // 0x008
	int ptag;                                         // 0x00c
	int pclass;                                       // 0x010
	long hdrlen;                                      // 0x014
};
struct asn1_item_st
{
	char pad[0x14];
	int (*func)(void*, void*, int, int, char*, void*);// 0x014
};
struct asn1_template_st
{
	int flags;                                        // 0x000
	long itype;                                       // 0x004
	char pad08[8];                                    // 0x008
	asn1_item_st* item;                               // 0x010
};

// ---------------------------------------------------------------------------------------------------------
// imported routines
// ---------------------------------------------------------------------------------------------------------
extern "C"
{
	void ERR_put_error(int lib, int func, int reason, const char* file, int line);   // 0x01180d50
	void ERR_add_error_data(int num, ...);                          // 0x01180a70
	unsigned long ERR_peek_error(void);                             // 0x01181100
	void* CRYPTO_malloc(int num, const char* file, int line);       // 0x01183410
	void CRYPTO_free(void* addr);                                   // 0x011835c0
	int CRYPTO_add_lock(int* pointer, int amount, int type, const char* file, int line); // 0x011815d0
	int CRYPTO_new_ex_data(int class_id, void* obj, void* ad);      // 0x01184260
	void OpenSSLDie(const char* file, int line, const char* msg);   // 0x01181510
	void operator_new_arr(void* dst, int val, int size);            // 0x011e073e

	int SSL_get_ex_data_X509_STORE_CTX_idx(void);                   // 0x01194840
	void SSL_CTX_free(ssl_ctx_st*);                                 // 0x0117ba10
	void ssl_cert_free(void*);                                      // 0x01194b70
	void* ssl_cert_dup(void*);                                      // 0x01194940
	void* X509_VERIFY_PARAM_new(void);                              // 0x01194290
	void X509_VERIFY_PARAM_inherit(void* param, void* src);         // 0x011944b0
	void* X509_STORE_new(void);                                     // 0x01195420
	void* lh_new(unsigned long (*hash)(void*), int (*cmp)(void*, void*)); // 0x01194090
	unsigned long SSL_SESSION_hash(void*);                          // 0x0117b9d0
	int SSL_SESSION_cmp(void*, void*);                              // 0x0117ba00
	void* EVP_get_digestbyname(const char* name);                   // 0x011973b0
	void* FUN_011948f0(void);                                       // 0x011948f0
	void FUN_01193a90(void*, void**, void**, const char*);          // 0x01193a90
	void* FUN_01193d20(void);                                       // 0x01193d20
	void FUN_0117c200(void);                                        // 0x0117c200
	void FUN_0117c440(ssl_st*);                                     // 0x0117c440

	int sk_num(const void* sk);                                     // 0x0117dde0
	void* sk_value(const void* sk, int i);                          // 0x0117ddf0
	int sk_insert(void* sk, void* p, int where);                    // 0x0117dc00
	typedef int (*sk_cmp_fn)(void*, void*);
	void* sk_new(sk_cmp_fn cmp);                                    // 0x0117db90

	void* FUN_01194ee0(void);                                       // 0x01194ee0
	void FUN_01194ef0(void*);                                       // 0x01194ef0
	void* FUN_01194f10(void*);                                      // 0x01194f10
	void ASN1_OBJECT_free(void*);                                   // 0x011998c0
	void* FUN_011991b0(void*);                                      // 0x011991b0
	int X509_NAME_ENTRY_set_data(X509_NAME_ENTRY*, int, const unsigned char*, int); // 0x0117d2a0
	void* OBJ_txt2obj(const char* txt, int no_name);                // 0x0117ffe0

	void* FUN_011918c0(void*);                                      // 0x011918c0
	int EVP_PKEY_cmp(void*, void*);                                 // 0x011913a0
	void EVP_PKEY_free(void*);                                      // 0x01191780

	int BIO_test_flags(void* b, int flags);                         // 0x01176fa0
	int BIO_get_retry_reason(void* b);                              // 0x011cac20

	int FUN_01199e70(const unsigned char** pp, long* plength, int* ptag, int* pclass, long omax); // 0x01199e70
	void* FUN_011974f0(void);                                       // 0x011974f0
	void FUN_01197500(void*);                                       // 0x01197500
	void ASN1_TYPE_set(void*, int, void*);                          // 0x01189610
	void* FUN_01199d70(int type);                                   // 0x01199d70
	int FUN_01199cb0(void*, const unsigned char*, int);             // 0x01199cb0
	void ASN1_STRING_free(void*);                                   // 0x01199db0
	int FUN_01199930(void*, const unsigned char**, int);            // 0x01199930
	int FUN_0119acf0(void*, const unsigned char**, int);            // 0x0119acf0
	int FUN_0119a850(void*, const unsigned char**, int);            // 0x0119a850
	int FUN_0117f2a0(void*, const unsigned char**, int);            // 0x0117f2a0
	void FUN_01198850(void*);                                       // 0x01198850
	int asn1_check_eoc(const unsigned char**);                      // 0x0117e310
}

// ---------------------------------------------------------------------------------------------------------
// SSL_new (0x0117c560)
// @ 0x0117c560
ssl_st* SSL_new(ssl_ctx_st* ctx)
{
	ssl_st* s;

	if (ctx == 0)
	{
		ERR_put_error(0x14, 0xba, 0xc3, 0, 0);
		return 0;
	}
	if (ctx->method == 0)
	{
		ERR_put_error(0x14, 0xba, 0xe4, 0, 0);
		return 0;
	}
	s = (ssl_st*)CRYPTO_malloc(0x108, ".\\ssl\\ssl_lib.c", 0xfe);
	if (s == 0)
		goto err;
	operator_new_arr(s, 0, 0x108);
	s->options = (unsigned long)ctx->a4;
	s->f_f8 = (unsigned long)ctx->a8;
	s->f_fc = (unsigned long)ctx->ac;
	if (ctx->cache != 0)
	{
		s->cert = ssl_cert_dup(ctx->cache);
		if (s->cert == 0)
			goto err_free;
	}
	else
	{
		s->cert = 0;
	}
	s->f60 = ctx->b4;
	s->f64 = ctx->b8;
	s->f68 = ctx->bc;
	s->fc4 = ctx->c0;
	s->sid_ctx_length = (unsigned int)ctx->c4;
	if (s->sid_ctx_length > 0x20)
		OpenSSLDie(".\\ssl\\ssl_lib.c", 0x125, "s->sid_ctx_length <= sizeof s->sid_ctx");
	memcpy(s->sid_ctx, &ctx->c8, 0x20);
	s->fc8 = ctx->e8;
	s->fc0 = ctx->ec;
	s->verify_param = X509_VERIFY_PARAM_new();
	if (s->verify_param == 0)
		goto err_free;
	X509_VERIFY_PARAM_inherit(s->verify_param, ctx->verify_param);
	s->quiet_shutdown = ctx->f4;
	CRYPTO_add_lock(&ctx->references, 1, 0xc, ".\\ssl\\ssl_lib.c", 0x134);
	s->ctx = ctx;
	s->fe0 = 0;
	s->method = ctx->method;
	if (!s->method->ssl_new(s))
		goto err_free;
	s->ff0 = 1;
	s->server = (ctx->method->func_10 != (void*)&FUN_0117c200);
	FUN_0117c440(s);
	CRYPTO_new_ex_data(1, s, &s->ex_data);
	return s;

err_free:
	if (s->cert != 0)
		ssl_cert_free(s->cert);
	if (s->ctx != 0)
		SSL_CTX_free(s->ctx);
	CRYPTO_free(s);
err:
	ERR_put_error(0x14, 0xba, 0x41, 0, 0);
	return 0;
}

// SSL_accept (0x0117c8f0)
// @ 0x0117c8f0
int SSL_accept(ssl_st* s)
{
	if (s->handshake_func == 0)
	{
		ERR_put_error(0x14, 0xe0, 0x114, 0, 0);
		return -1;
	}
	if ((s->state & 0x3000) == 0)
		return s->method->ssl_accept(s);
	return 1;
}

// SSL_ctrl (0x0117c940)
// @ 0x0117c940
long SSL_ctrl(ssl_st* s, int cmd, long larg, void* parg)
{
	long l;

	switch (cmd)
	{
	case 0x28:
		l = s->f60;
		break;
	case 0x29:
		l = s->f60;
		s->f60 = (int)larg;
		break;
	case 0x10:
		s->f68 = (int)parg;
		return 1;
	case 0x20:
		s->options |= (unsigned long)larg;
		return (long)s->options;
	case 0x21:
		s->f_f8 |= (unsigned long)larg;
		return (long)s->f_f8;
	case 0x32:
		l = (long)s->f_fc;
		break;
	case 0x33:
		l = (long)s->f_fc;
		s->f_fc = (unsigned long)larg;
		break;
	case 0x11:
		if (s->version == 0xfeff)
		{
			*(int*)((char*)s->p5c + 0xc4) = (int)larg;
			return (long)larg;
		}
		return 0;
	default:
		return s->method->ctrl(s, cmd, larg, parg);
	}
	return l;
}

// SSL_CTX_new (0x0117ca60)
// @ 0x0117ca60
ssl_ctx_st* SSL_CTX_new(ssl_method_st* meth)
{
	ssl_ctx_st* ret = 0;

	if (meth == 0)
	{
		ERR_put_error(0x14, 0xa9, 0xc4, 0, 0);
		return 0;
	}
	if (SSL_get_ex_data_X509_STORE_CTX_idx() < 0)
	{
		ERR_put_error(0x14, 0xa9, 0x10d, 0, 0);
		goto err41;
	}
	ret = (ssl_ctx_st*)CRYPTO_malloc(0xf8, ".\\ssl\\ssl_lib.c", 0x56b);
	if (ret == 0)
		goto err41;
	operator_new_arr(ret, 0, 0xf8);
	ret->method = meth;
	ret->cert_store = 0;
	ret->session_cache_mode = 2;
	ret->session_cache_size = 0x5000;
	ret->session_cache_head = 0;
	ret->session_cache_tail = 0;
	ret->session_timeout = meth->get_timeout();
	ret->new_session_cb = 0;
	ret->remove_session_cb = 0;
	ret->get_session_cb = 0;
	ret->ec = 0;
	operator_new_arr(&ret->pad34, 0, 0x2c);
	ret->references = 1;
	ret->f4 = 0;
	ret->z9c = 0;
	ret->pad64 = 0;
	ret->pad68 = 0;
	ret->ac = 0x19000;
	ret->b4 = 0;
	ret->b8 = 0;
	ret->bc = 0;
	ret->c0 = 0;
	ret->c4 = 0;
	ret->e8 = 0;
	ret->cache = FUN_011948f0();
	if (ret->cache == 0)
		goto err41;
	ret->pad6c[0] = 0;
	ret->pad6c[1] = 0;
	ret->pad6c[2] = 0;
	ret->pad6c[3] = 0;
	ret->pad6c[4] = 0;
	ret->sessions = lh_new(SSL_SESSION_hash, SSL_SESSION_cmp);
	if (ret->sessions == 0)
		goto err41;
	ret->cert_store = X509_STORE_new();
	if (ret->cert_store == 0)
		goto err41;
	FUN_01193a90(ret->method, &ret->cipher_list, &ret->cipher_list_by_id,
		"AES:ALL:!aNULL:!eNULL:+RC4:@STRENGTH");
	if (ret->cipher_list == 0)
		goto erra1;
	if (sk_num(ret->cipher_list) <= 0)
		goto erra1;
	ret->verify_param = X509_VERIFY_PARAM_new();
	if (ret->verify_param == 0)
		goto err41;
	ret->md5 = EVP_get_digestbyname("ssl2-md5");
	if (ret->md5 == 0)
		goto errf1;
	ret->sha1 = EVP_get_digestbyname("ssl3-md5");
	if (ret->sha1 == 0)
		goto errf2;
	ret->sha256 = EVP_get_digestbyname("ssl3-sha1");
	if (ret->sha256 == 0)
		goto errf3;
	ret->za0 = (int)sk_new(0);
	if (ret->za0 == 0)
		goto err41;
	CRYPTO_new_ex_data(2, ret, &ret->ex_data);
	ret->z94 = 0;
	ret->z98 = (int)FUN_01193d20();
	return ret;

err41:
	ERR_put_error(0x14, 0xa9, 0x41, 0, 0);
	goto err;
erra1:
	ERR_put_error(0x14, 0xa9, 0xa1, 0, 0);
	goto err;
errf1:
	ERR_put_error(0x14, 0xa9, 0xf1, 0, 0);
	goto err;
errf2:
	ERR_put_error(0x14, 0xa9, 0xf2, 0, 0);
	goto err;
errf3:
	ERR_put_error(0x14, 0xa9, 0xf3, 0, 0);
	goto err;
err:
	if (ret != 0)
		SSL_CTX_free(ret);
	return 0;
}

// SSL_get_error (0x0117ccd0)
// @ 0x0117ccd0
int SSL_get_error(ssl_st* s, int ret)
{
	unsigned long e;
	int r;
	void* bio;

	if (ret > 0)
		return 0;
	e = ERR_peek_error();
	if (e != 0)
		return ((e & 0xff000000) == 0x2000000) * 4 + 1;
	if (ret < 0)
	{
		if (s->rwstate == 3)
		{
			bio = s->rbio;
			if (BIO_test_flags(bio, 1))
				return 2;
			if (BIO_test_flags(bio, 2))
				return 3;
			if (BIO_test_flags(bio, 4))
				goto retry;
		}
		if (s->rwstate == 2)
		{
			bio = s->wbio;
			if (BIO_test_flags(bio, 2))
				return 3;
			if (BIO_test_flags(bio, 1))
				return 2;
			if (BIO_test_flags(bio, 4))
				goto retry;
		}
		if (s->rwstate == 4)
			return 4;
		goto done;
	retry:
		r = BIO_get_retry_reason(bio);
		if (r == 2)
			return 7;
		if (r == 3)
			return 8;
		return 5;
	done:;
	}
	if (ret == 0)
	{
		if (s->version == 2)
			return 6;
		if ((s->flags30 & 2) != 0 && *(int*)((char*)s->s3 + 0x1a8) == 0)
			return 6;
	}
	return 5;
}

// X509_NAME_add_entry (0x0117d180)
// @ 0x0117d180
int X509_NAME_add_entry(X509_NAME* name, X509_NAME_ENTRY* ne, int loc, int set)
{
	void* sk;
	X509_NAME_ENTRY* new_name;
	X509_NAME_ENTRY* dup;
	int ret;
	int bump;

	if (name == 0)
		return 0;
	sk = name->entries;
	ret = sk_num(sk);
	if (loc > ret || loc < 0)
		loc = ret;
	name->modified = 1;
	if (set == -1)
	{
		if (loc == 0)
		{
			new_name = 0;
			bump = 1;
		}
		else
		{
			new_name = (X509_NAME_ENTRY*)sk_value(sk, loc - 1);
			set = new_name->set;
			bump = 0;
		}
	}
	else
	{
		if (loc < ret)
		{
			new_name = (X509_NAME_ENTRY*)sk_value(sk, loc);
			set = new_name->set;
		}
		else if (loc == 0)
		{
			set = 0;
		}
		else
		{
			new_name = (X509_NAME_ENTRY*)sk_value(sk, loc - 1);
			set = new_name->set + 1;
		}
		bump = (set == 0);
	}
	dup = (X509_NAME_ENTRY*)FUN_01194f10(ne);
	if (dup != 0)
	{
		dup->set = set;
		if (sk_insert(sk, dup, loc))
		{
			if (bump)
			{
				ret = sk_num(sk);
				while (loc + 1 < ret)
				{
					new_name = (X509_NAME_ENTRY*)sk_value(sk, loc);
					new_name->set = new_name->set + 1;
					loc++;
				}
			}
			return 1;
		}
		ERR_put_error(0xb, 0x71, 0x41, 0, 0);
		FUN_01194ef0(dup);
	}
	return 0;
}

// X509_NAME_ENTRY_create_by_OBJ (0x0117d410)
// @ 0x0117d410
__declspec(noinline) X509_NAME_ENTRY* X509_NAME_ENTRY_create_by_OBJ(X509_NAME_ENTRY** pne,
	ASN1_OBJECT* obj, int type, const unsigned char* bytes, int len)
{
	X509_NAME_ENTRY* ne;

	if (pne == 0 || (ne = *pne) == 0)
	{
		ne = (X509_NAME_ENTRY*)FUN_01194ee0();
		if (ne == 0)
			return 0;
	}
	if (obj != 0)
	{
		ASN1_OBJECT_free(ne->object);
		ne->object = (ASN1_OBJECT*)FUN_011991b0(obj);
		if (ne->object != 0)
		{
			if (X509_NAME_ENTRY_set_data(ne, type, bytes, len))
				goto ok_name;
		}
	}
	else
	{
		ERR_put_error(0xb, 0x73, 0x43, 0, 0);
	}
	if (pne == 0 || ne != *pne)
		FUN_01194ef0(ne);
	return 0;

ok_name:
	if (pne != 0 && *pne == 0)
		*pne = ne;
	return ne;
}

// X509_NAME_ENTRY_create_by_txt (0x0117d4d0)
// @ 0x0117d4d0
X509_NAME_ENTRY* X509_NAME_ENTRY_create_by_txt(X509_NAME_ENTRY** pne, const char* txt,
	int type, const unsigned char* bytes, int len)
{
	ASN1_OBJECT* obj;
	X509_NAME_ENTRY* ne;

	obj = (ASN1_OBJECT*)OBJ_txt2obj(txt, 0);
	if (obj == 0)
	{
		ERR_put_error(0xb, 0x83, 0x77, 0, 0);
		ERR_add_error_data(2, "name=", txt);
		return 0;
	}
	ne = X509_NAME_ENTRY_create_by_OBJ(pne, obj, type, bytes, len);
	ASN1_OBJECT_free(obj);
	return ne;
}

// X509_check_private_key (0x0117da80)
// @ 0x0117da80
int X509_check_private_key(X509* x, EVP_PKEY* k)
{
	EVP_PKEY* pkey;
	int r;
	int ret;

	if (x == 0 || x->cert_info == 0)
		pkey = 0;
	else
		pkey = (EVP_PKEY*)FUN_011918c0(x->cert_info->key);
	ret = 0;
	r = EVP_PKEY_cmp(pkey, k);
	switch (r)
	{
	case 1:
		ret = 1;
		break;
	case 0:
		ERR_put_error(0xb, 0x80, 0x74, 0, 0);
		break;
	case -2:
		if (k->type == 0x198)
			ERR_put_error(0xb, 0x80, 0x10, 0, 0);
		else if (k->type == 0x1c)
			ERR_put_error(0xb, 0x80, 0x72, 0, 0);
		else
			ERR_put_error(0xb, 0x80, 0x75, 0, 0);
		break;
	case -1:
		ERR_put_error(0xb, 0x80, 0x73, 0, 0);
		break;
	}
	EVP_PKEY_free(pkey);
	return ret;
}

// sk_new_null (0x0117df20)
// @ 0x0117df20
__declspec(noinline) void* sk_new_null(void)
{
	return sk_new(0);
}

// asn1_ex_c2i (0x0117e0a0)
// @ 0x0117e0a0
extern "C" int asn1_ex_c2i(unsigned int* pval, unsigned char* cont, int len, int type,
	char* free_cont, asn1_template_st* it)
{
	ASN1_TYPE* atype;
	ASN1_STRING* astr;
	unsigned int* pv;
	unsigned int* local_8;
	int reason;

	atype = 0;
	local_8 = 0;
	if (it->item != 0 && it->item->func != 0)
		return it->item->func(pval, cont, len, type, free_cont, it);
	if (it->itype == -4)
	{
		atype = (ASN1_TYPE*)*pval;
		if (atype == 0)
		{
			atype = (ASN1_TYPE*)FUN_011974f0();
			if (atype == 0)
				goto fail;
			*pval = (unsigned int)atype;
		}
		if ((unsigned int)type != *(unsigned int*)atype)
			ASN1_TYPE_set(atype, type, 0);
		local_8 = pval;
		pval = (unsigned int*)((char*)atype + 4);
	}
	pv = (unsigned int*)*pval;
	if (type > 10)
	{
		if (type == 0x102 || type == 0x10a)
			goto case2;
		goto string_case;
	}
	if (type == 10)
		goto case2;
	switch (type)
	{
	case 1:
		if (len == 1)
		{
			*pval = *cont;
			goto done;
		}
		reason = 0x6a;
		goto err;
	case 2:
	case 10:
		goto case2;
	case 3:
		if (FUN_0119acf0(pval, (const unsigned char**)&cont, len))
			goto done;
		goto fail;
	case 5:
		if (len == 0)
		{
			*pval = 1;
			goto done;
		}
		reason = 0x90;
		goto err;
	case 6:
		if (FUN_01199930(pval, (const unsigned char**)&cont, len))
			goto done;
		goto fail;
	default:
		goto string_case;
	}
case2:
	if (FUN_0119a850(pval, (const unsigned char**)&cont, len))
	{
		*(unsigned int*)(*pval + 4) = (*(unsigned int*)(*pval + 4) & 0x100) | type;
		goto done;
	}
	goto fail;
string_case:
	astr = (ASN1_STRING*)*pval;
	if (astr == 0)
	{
		astr = (ASN1_STRING*)FUN_01199d70(type);
		if (astr == 0)
		{
			reason = 0x41;
			goto err;
		}
		*pval = (unsigned int)astr;
	}
	else
	{
		astr->length = type;   /* the ASN1_STRING "type" field lives at +4 */
	}
	{
		unsigned int* pi = (unsigned int*)astr;
		if (*free_cont != 0)
		{
			if (pi[2] != 0)
				CRYPTO_free((void*)pi[2]);
			pi[2] = (unsigned int)cont;
			pi[0] = (unsigned int)len;
			*free_cont = 0;
			goto done;
		}
	}
	if (FUN_01199cb0(astr, cont, len))
		goto done;
	ERR_put_error(0xd, 0xcc, 0x41, 0, 0);
	ASN1_STRING_free(astr);
	*pval = 0;
	goto fail;
err:
	ERR_put_error(0xd, 0xcc, reason, 0, 0);
fail:
	FUN_01197500(atype);
	if (local_8 != 0)
		*local_8 = 0;
	return 0;
done:
	if (atype != 0 && type == 5)
		((unsigned int*)atype)[1] = 0;
	return 1;
}

// asn1_check_tlen (0x0117e340)
// @ 0x0117e340
extern "C" int asn1_check_tlen(long* len, int* tag, int* cls, char* inf, char* cst,
	const unsigned char** pp, long omax, int omode, int cmode, int imp, ASN1_TLC* tlc)
{
	const unsigned char* start;
	const unsigned char* p;
	unsigned char flags;
	long plen;
	int ptag;
	int pclass;

	start = *pp;
	if (tlc == 0 || tlc->valid == 0)
	{
		p = start;
		flags = (unsigned char)FUN_01199e70(&p, &plen, &ptag, &pclass, omax);
		if (tlc != 0)
		{
			tlc->pclass = pclass;
			tlc->ptag = ptag;
			tlc->ret = flags;
			tlc->plen = plen;
			tlc->hdrlen = p - start;
			tlc->valid = 1;
			if ((flags & 0x81) == 0 && omax < (p - start) + plen)
			{
				ERR_put_error(0xd, 0x68, 0x9b, 0, 0);
				tlc->valid = 0;
				return 0;
			}
		}
	}
	else
	{
		pclass = tlc->pclass;
		plen = tlc->plen;
		flags = (unsigned char)tlc->ret;
		ptag = tlc->ptag;
		p = start + tlc->hdrlen;
	}
	if (flags & 0x80)
	{
		ERR_put_error(0xd, 0x68, 0x66, 0, 0);
		if (tlc != 0)
			tlc->valid = 0;
		return 0;
	}
	if (omode >= 0)
	{
		if (omode != ptag || cmode != pclass)
		{
			if (imp != 0)
				return -1;
			if (tlc != 0)
				tlc->valid = 0;
			ERR_put_error(0xd, 0x68, 0xa8, 0, 0);
			return 0;
		}
		if (tlc != 0)
			tlc->valid = 0;
	}
	if (flags & 1)
		plen = (start - p) + omax;
	if (inf != 0)
		*inf = flags & 1;
	if (cst != 0)
		*cst = flags & 0x20;
	if (len != 0)
		*len = plen;
	if (cls != 0)
		*cls = (unsigned char)pclass;
	if (tag != 0)
		*tag = ptag;
	*pp = p;
	return 1;
}

// asn1_d2i_ex_primitive (0x0117e4e0)
// @ 0x0117e4e0
extern "C" int asn1_d2i_ex_primitive(void* pval, void* it, int omax, int imp)
{
	unsigned char cst;
	long len;
	int tag;
	int ret;

	(void)imp;
	if (pval == 0)
		return 0;
	if (((*(unsigned int*)it) & 0x10) == 0)
		return FUN_0117f2a0(pval, (const unsigned char**)&omax, *(int*)&omax);
	ret = asn1_check_tlen(&len, &tag, 0, 0, (char*)&cst,
		(const unsigned char**)&pval, omax, ((int*)it)[1], *(unsigned int*)it & 0xc0, 0, 0);
	if (ret != 0)
	{
		if (ret == -1)
			return -1;
		if (FUN_0117f2a0(pval, (const unsigned char**)&omax, len))
		{
			if (cst == 0)
			{
				if (len == 0)
					return 1;
				ERR_put_error(0xd, 0x84, 0x77, 0, 0);
			}
			else
			{
				if (asn1_check_eoc((const unsigned char**)&omax))
					return 1;
				ERR_put_error(0xd, 0x84, 0x89, 0, 0);
			}
			FUN_01198850(pval);
			*(int*)pval = 0;
			return 0;
		}
	}
	ERR_put_error(0xd, 0x84, 0x3a, 0, 0);
	return 0;
}
