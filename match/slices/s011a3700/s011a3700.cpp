// s011a3700 -- lib_cblock: OpenSSL handshake key-exchange message handlers.
// Rebuilt from the shipped PE.  The SSL/SSL3 structures are addressed through
// fixed offsets and are kept as literals, matching the original code.

typedef unsigned char  byte;
typedef unsigned short ushort;
typedef unsigned int   uint;

// ---------------------------------------------------------------------------
// OpenSSL / lib_cblock helpers
// ---------------------------------------------------------------------------
void __cdecl ERR_put_error(int lib, int func, int reason, const char* file, int line);
int  __cdecl ssl3_do_write(void* s, int type);
int  __cdecl FUN_01179f60(int type, const void* a, int b, void* out, int* len, void* key);
int  __cdecl DSA_sign(int type, const byte* dgst, int len, byte* sig, uint* siglen, void* dsa);
int  __cdecl ECDSA_sign(int type, const byte* dgst, int len, byte* sig, uint* siglen, void* ec);
void* __cdecl X509_get_pubkey(void* x);
int  __cdecl X509_certificate_type(void* x, void* pkey);
void __cdecl EVP_PKEY_free(void* pkey);
int  __cdecl EVP_PKEY_size(void* pkey);
int  __cdecl RSA_size(void* rsa);
int  __cdecl DH_size(void* dh);
void __cdecl RSA_free(void* rsa);
void __cdecl DH_free(void* dh);
void __cdecl EC_KEY_free(void* ec);
int  __cdecl check_srvr_ecc_cert_and_alg(void* cert, void* s3);
void __cdecl EVP_MD_CTX_init(void* ctx);
void __cdecl EVP_MD_CTX_cleanup(void* ctx);
int  __cdecl EVP_DigestFinal_ex(void* ctx, byte* md, uint* len);
int  __cdecl EVP_DigestUpdate(void* ctx, const void* data, unsigned int len);
int  __cdecl EC_KEY_set_group(void* key, void* group);
int  __cdecl EC_KEY_set_public_key(void* key, void* point);
void __cdecl EC_GROUP_free(void* group);
void __cdecl EC_POINT_free(void* point);
void __cdecl BN_CTX_free(void* ctx);
int  __cdecl FUN_011bd7d0(void* s, void* cert);
int  __cdecl FUN_011bd660(void* s, void* key);
void __cdecl FUN_0117cf90(void* cert);
void __cdecl FUN_011a0930(void* s, int a, int b);
int  __cdecl FUN_011a1f60(void* s, uint alg);
void* __cdecl FUN_01194c60();
int  __cdecl FUN_01179f50();
int  __cdecl FUN_0117ac80(const void* p, int len, void* key);
int  __cdecl FUN_01191f10();
int  __cdecl FUN_011b3870(void* group);
int  __cdecl FUN_011922c0(void* key);
int  __cdecl FUN_011b1f50(void* group);
void* __cdecl FUN_011b2140(void* key);
void* __cdecl FUN_01187a80();
int  __cdecl FUN_011b2650(void* key, void* point, const void* data, int len, void* bnctx);
int  __cdecl FUN_01196850();
void __cdecl FUN_0119a2e0(void* ctx, void* md, int a);
void __cdecl FUN_0119a3f0(void* ctx, const void* data, unsigned int len);
int  __cdecl FUN_0117a150(int type, const void* a, int b, const void* c, int d, void* key);

extern "C" int DAT_015cea60[];                            // 0x015cea60

// ---------------------------------------------------------------------------
// ssl3_send_server_key_exchange -- build the ServerKeyExchange message
// @ 0x011a3700
void FUN_011a3700(int s)
{
	int len = 0;
	if (*(int*)(s + 0x34) != 0x1190)
	{
		ssl3_do_write((void*)s, 0x16);
		return;
	}

	byte* p = *(byte**)(*(int*)(s + 0x3c) + 4);
	int*  k = *(int**)(*(int*)(*(int*)(s + 0x94)) + 4);

	byte sigMsg[20];
	typedef void (__cdecl *EncoderFn)(int, int, void*);
	EncoderFn enc = (EncoderFn)(*(int*)(*(int*)(s + 8) + 100) + 0x1c);
	enc(s, *(int*)(s + 0x58) + 0x194, sigMsg);

	int reason;
	int type = *k;
	if (type == 6)
	{
		byte params[16];
		enc(s, *(int*)(s + 0x58) + 0x184, params);
		if (FUN_01179f60(0x72, params, 0x24, p + 6, &len, (void*)k[3]) < 1)
		{
			ERR_put_error(0x14, 0x99, 4, 0, 0);
			return;
		}
		p[4] = (byte)((uint)len >> 8);
		p[5] = (byte)len;
	}
	else if (type == 0x74)
	{
		if (DSA_sign(k[1], sigMsg, 0x14, p + 6, (uint*)&len, (void*)k[3]) == 0)
		{
			ERR_put_error(0x14, 0x99, 10, 0, 0);
			return;
		}
		p[4] = (byte)((uint)len >> 8);
		p[5] = (byte)len;
	}
	else if (type == 0x198)
	{
		if (ECDSA_sign(k[1], sigMsg, 0x14, p + 6, (uint*)&len, (void*)k[3]) == 0)
		{
			ERR_put_error(0x14, 0x99, 0x2a, 0, 0);
			return;
		}
		p[4] = (byte)((uint)len >> 8);
		p[5] = (byte)len;
	}
	else
	{
		ERR_put_error(0x14, 0x99, 0x44, 0, 0);
		return;
	}
	(void)reason;

	p[0] = 0xf;
	int total = len + 2;
	p[3] = (byte)total;
	p[1] = (byte)((uint)total >> 0x10);
	p[2] = (byte)((uint)total >> 8);
	*(int*)(s + 0x34) = 0x1191;
	*(int*)(s + 0x44) = len + 6;
	*(int*)(s + 0x48) = 0;

	ssl3_do_write((void*)s, 0x16);
}

// ---------------------------------------------------------------------------
// ssl3_get_client_key_exchange -- read the client's key-exchange message
// @ 0x011a38d0
int FUN_011a38d0(int* s)
{
	int cert = 0;
	int pkey = 0;

	if (s[0xd] == 0x1170)
	{
		int* k = (int*)s[0x25];
		if (k != 0 && (*(int**)k)[0] != 0 && (*(int**)k)[1] != 0)
			s[0xd] = 0x1172;
		else
			s[0xd] = 0x1171;
	}

	if (s[0xd] != 0x1171)
		goto send;

	int ret = 0;
	{
		int (*cb)(int*, int*, int*) = *(int (**)(int*, int*, int*))(s[0x36] + 0x74);
		if (cb != 0)
		{
			ret = cb(s, &cert, &pkey);
			if (ret < 0)
			{
				s[6] = 4;
				return -1;
			}
		}
	}
	s[6] = 1;
	if (ret == 1)
	{
		if (pkey == 0 || cert == 0)
		{
			ret = 0;
			ERR_put_error(0x14, 0x97, 0x6a, 0, 0);
		}
		else
		{
			s[0xd] = 0x1171;
			if (FUN_011bd7d0(s, (void*)cert) == 0 ||
			    FUN_011bd660(s, (void*)pkey) == 0)
				ret = 0;
		}
	}

	if (cert != 0)
		FUN_0117cf90((void*)cert);
	if (pkey != 0)
		EVP_PKEY_free((void*)pkey);

	if (ret == 0)
	{
		if (*s == 0x300)
		{
			*(int*)(s[0x16] + 0x36c) = 0;
			FUN_011a0930(s, 1, 0x29);
			return 1;
		}
		*(int*)(s[0x16] + 0x36c) = 2;
	}
	s[0xd] = 0x1172;

send:
	if (s[0xd] == 0x1172)
	{
		s[0xd] = 0x1173;
		int alg;
		if (*(int*)(s[0x16] + 0x36c) == 2)
			alg = 0;
		else
			alg = **(int**)s[0x25];
		s[0x11] = FUN_011a1f60(s, (uint)alg);
		s[0x12] = 0;
	}
	return ssl3_do_write(s, 0x16);
}

// ---------------------------------------------------------------------------
// ssl3_check_cert_and_algorithm -- verify the peer certificate suits the suite
// @ 0x011a3a60
int FUN_011a3a60(int s)
{
	int key = *(int*)(*(int*)(s + 0xbc) + 0x90);
	int s3  = *(int*)(*(int*)(s + 0x58) + 0x358);
	uint alg = *(uint*)(s3 + 0xc);

	if ((alg & 0x3800) != 0)
		return 1;

	if (key == 0)
	{
		ERR_put_error(0x14, 0x82, 0x44, 0, 0);
		return 0;
	}

	int rsa = *(int*)(key + 0x3c);
	int dh  = *(int*)(key + 0x40);
	int type = *(int*)(key + 4);
	int cert = *(int*)(key + 0xc + type * 8);
	int reason = 0;

	if (type == 5)
	{
		if (check_srvr_ecc_cert_and_alg(*(void**)(key + 0x34), (void*)s3) != 0)
			return 1;
		reason = 0x130;
	}
	else
	{
		void* pkey = X509_get_pubkey((void*)cert);
		uint ctype = (uint)X509_certificate_type((void*)cert, pkey);
		EVP_PKEY_free(pkey);
		byte ct = (byte)ctype;

		if ((alg & 0x100) && (ct & 0x11) != 0x11)
			reason = 0xaa;
		else if ((alg & 0x200) && (ct & 0x12) != 0x12)
			reason = 0xa5;
		else if (((alg & 1) && (ct & 0x21) != 0x21) && rsa == 0)
			reason = 0xa9;
		else if (((alg & 0x10) && (ct & 0x44) != 0x44) && dh == 0)
			reason = 0xa3;
		else if ((alg & 2) && (ctype & 0x104) != 0x104)
			reason = 0xa4;
		else if ((alg & 4) && (ctype & 0x204) != 0x204)
			reason = 0xa2;
		else if ((*(byte*)(s3 + 0x10) & 2) && (ctype & 0x1000) == 0)
			reason = 0xfa;
		else if (alg & 1)
		{
			if (rsa != 0 &&
			    RSA_size((void*)rsa) * 8 <= (int)((-(uint)((*(uint*)(s3 + 0x10) & 8) != 0) & 0xfffffe00) + 0x400))
				return 1;
			reason = 0xa7;
		}
		else if (alg & 0x16)
		{
			if (dh != 0 &&
			    DH_size((void*)dh) * 8 <= (int)((-(uint)((*(uint*)(s3 + 0x10) & 8) != 0) & 0xfffffe00) + 0x400))
				return 1;
			reason = 0xa6;
		}
		else
			reason = 0xfa;
	}

	ERR_put_error(0x14, 0x82, reason, 0, 0);
	FUN_011a0930((void*)s, 2, 0x28);
	return 0;
}

// ---------------------------------------------------------------------------
// ssl3_get_key_exchange -- parse the server's key-exchange parameters
// @ 0x011a3cf0
void FUN_011a3cf0(int s)
{
	byte* p = *(byte**)(s + 0x40);
	int   len;
	int   ok = (*(int (__cdecl**)(int, int, int, int, int, int*))(*(int*)(s + 8) + 0x30))
	                    (s, 0x1140, 0x1141, -1, *(int*)(s + 0xfc), &len);
	if (len == 0)
		goto done;

	if (*(int*)(*(int*)(s + 0x58) + 0x354) != 0xc)
	{
		*(int*)(*(int*)(s + 0x58) + 0x368) = 1;
		return;
	}

	int key = *(int*)(*(int*)(s + 0xbc) + 0x90);
	if (key == 0)
	{
		*(int*)(*(int*)(s + 0xbc) + 0x90) = (int)FUN_01194c60();
	}
	else
	{
		if (*(int*)(key + 0x3c) != 0)
		{
			RSA_free(*(void**)(key + 0x3c));
			*(int*)(*(int*)(*(int*)(s + 0xbc) + 0x90) + 0x3c) = 0;
		}
		if (*(int*)(key + 0x40) != 0)
		{
			DH_free(*(void**)(key + 0x40));
			*(int*)(*(int*)(*(int*)(s + 0xbc) + 0x90) + 0x40) = 0;
		}
		if (*(int*)(key + 0x44) != 0)
		{
			EC_KEY_free(*(void**)(key + 0x44));
			*(int*)(*(int*)(*(int*)(s + 0xbc) + 0x90) + 0x44) = 0;
		}
	}

	uint flags = *(uint*)(*(int*)(*(int*)(s + 0x58) + 0x358) + 0xc);
	byte mdCtx[16];
	int  pkey = 0;
	int  rsaKey = 0, dhKey = 0, ecKey = 0, ecPoint = 0, bnCtx = 0;
	EVP_MD_CTX_init(mdCtx);

	if (flags & 1)
	{
		rsaKey = FUN_01179f50();
		if (rsaKey == 0)
			goto err41;

		uint n = ((uint)p[0] << 8) | p[1];
		int  used = n + 2;
		if (used > ok)
		{
			ERR_put_error(0x14, 0x8d, 0x79, 0, 0);
			goto cleanup;
		}
		*(int*)(rsaKey + 0x10) = FUN_0117ac80(p + 2, n, *(void**)(rsaKey + 0x10));
		if (*(int*)(rsaKey + 0x10) == 0)
			goto err10;

		p += 2 + n;
		n = ((uint)p[0] << 8) | p[1];
		used += n + 2;
		if (ok < used)
		{
			ERR_put_error(0x14, 0x8d, 0x78, 0, 0);
			goto cleanup;
		}
		*(int*)(rsaKey + 0x14) = FUN_0117ac80(p + 2, n, *(void**)(rsaKey + 0x14));
		if (*(int*)(rsaKey + 0x14) == 0)
			goto err10;

		p += 2 + n;
		ok -= used;
		if (flags & 0x100)
		{
			pkey = (int)X509_get_pubkey(*(void**)(*(int*)(*(int*)(s + 0xbc) + 0x90) + 0xc));
			*(int*)(*(int*)(*(int*)(s + 0xbc) + 0x90) + 0x3c) = rsaKey;
			rsaKey = 0;
		}
		else
		{
			ERR_put_error(0x14, 0x8d, 0x44, 0, 0);
			goto cleanup;
		}
	}
	else if (flags & 0x10)
	{
		dhKey = FUN_01196850();
		if (dhKey == 0)
		{
			ERR_put_error(0x14, 0x8d, 5, 0, 0);
			goto cleanup;
		}
		uint n = ((uint)p[0] << 8) | p[1];
		int  used = n + 2;
		if (ok < used)
		{
			ERR_put_error(0x14, 0x8d, 0x6e, 0, 0);
			goto cleanup;
		}
		*(int*)(dhKey + 8) = FUN_0117ac80(p + 2, n, 0);
		if (*(int*)(dhKey + 8) == 0)
			goto err10;
		p += 2 + n;
		n = ((uint)p[0] << 8) | p[1];
		used += n + 2;
		if (ok < used)
		{
			ERR_put_error(0x14, 0x8d, 0x6c, 0, 0);
			goto cleanup;
		}
		*(int*)(dhKey + 0xc) = FUN_0117ac80(p + 2, n, 0);
		if (*(int*)(dhKey + 0xc) == 0)
			goto err10;
		p += 2 + n;
		n = ((uint)p[0] << 8) | p[1];
		used += n + 2;
		if (ok < used)
		{
			ERR_put_error(0x14, 0x8d, 0x6d, 0, 0);
			goto cleanup;
		}
		*(int*)(dhKey + 0x14) = FUN_0117ac80(p + 2, n, 0);
		if (*(int*)(dhKey + 0x14) == 0)
			goto err10;
		p += 2 + n;
		ok -= used;

		if (flags & 0x100)
			pkey = (int)X509_get_pubkey(*(void**)(*(int*)(*(int*)(s + 0xbc) + 0x90) + 0xc));
		else if (flags & 0x200)
			pkey = (int)X509_get_pubkey(*(void**)(*(int*)(*(int*)(s + 0xbc) + 0x90) + 0x1c));

		*(int*)(*(int*)(*(int*)(s + 0xbc) + 0x90) + 0x40) = dhKey;
		dhKey = 0;
	}
	else if (flags & 0x80)
	{
		ecKey = FUN_01191f10();
		if (ecKey == 0)
			goto err41;
		if (ok < 3 || p[0] != 3 || (byte)p[2] - 1 > 0x18)
		{
			ERR_put_error(0x14, 0x8d, 0x13a, 0, 0);
			goto cleanup;
		}
		int group = FUN_011b3870((void*)*(int*)((byte*)DAT_015cea60 + (uint)p[2] * 4));
		if (group == 0)
			goto err10;
		if (EC_KEY_set_group((void*)ecKey, (void*)group) == 0)
			goto err10;
		EC_GROUP_free((void*)group);
		int ecdh = FUN_011922c0((void*)ecKey);
		if ((*(byte*)(*(int*)(*(int*)(s + 0x58) + 0x358) + 0x10) & 2) &&
		    FUN_011b1f50((void*)ecdh) > 0xa3)
		{
			ERR_put_error(0x14, 0x8d, 0x136, 0, 0);
			goto cleanup;
		}
		ecPoint = (int)FUN_011b2140((void*)ecdh);
		bnCtx = (int)FUN_01187a80();
		if (ecPoint == 0 || bnCtx == 0)
			goto err41;

		uint clen = p[3];
		int used = clen + 4;
		if (ok < used || FUN_011b2650((void*)ecdh, (void*)ecPoint, p + 4, clen, (void*)bnCtx) == 0)
		{
			ERR_put_error(0x14, 0x8d, 0x132, 0, 0);
			goto cleanup;
		}
		p += 4 + clen;
		ok -= used;

		if (flags & 0x100)
			pkey = (int)X509_get_pubkey(*(void**)(*(int*)(*(int*)(s + 0xbc) + 0x90) + 0xc));
		else if (flags & 0x4000)
			pkey = (int)X509_get_pubkey(*(void**)(*(int*)(*(int*)(s + 0xbc) + 0x90) + 0x34));

		EC_KEY_set_public_key((void*)ecKey, (void*)ecPoint);
		*(int*)(*(int*)(*(int*)(s + 0xbc) + 0x90) + 0x44) = ecKey;
		ecKey = 0;
		BN_CTX_free((void*)bnCtx);
		EC_POINT_free((void*)ecPoint);
		ecPoint = 0;
	}
	else
	{
		if (flags & 6)
		{
			ERR_put_error(0x14, 0x8d, 0x2f, 0, 0);
			goto cleanup;
		}
		if ((int)flags >= 0)
		{
			if (flags & 0x40)
			{
				ERR_put_error(0x14, 0x8d, 0x10, 0, 0);
				goto cleanup;
			}
		}
	}

	if ((flags & 0x400) == 0)
	{
		if (pkey == 0)
		{
			if ((flags & 0x800) == 0)
			{
				ERR_put_error(0x14, 0x8d, 0x44, 0, 0);
				goto cleanup;
			}
			if (ok != 0)
			{
				ERR_put_error(0x14, 0x8d, 0x99, 0, 0);
				goto cleanup;
			}
			goto finished;
		}

		uint sigLen = ((uint)p[0] << 8) | p[1];
		uint rem = ok - 2;
		if (sigLen == rem && (int)rem <= EVP_PKEY_size((void*)pkey) && (int)rem > 0)
		{
			if (*(int*)pkey == 6)
			{
				byte digest[16];
				uint total = 0;
				for (int i = 2; i > 0; --i)
				{
					void* md = (i == 2) ? *(void**)(*(int*)(s + 0xd8) + 0x8c)
					                    : *(void**)(*(int*)(s + 0xd8) + 0x90);
					FUN_0119a2e0(mdCtx, md, 0);
					FUN_0119a3f0(mdCtx, (void*)(*(int*)(s + 0x58) + 0xb8), 0x20);
					FUN_0119a3f0(mdCtx, (void*)(*(int*)(s + 0x58) + 0x98), 0x20);
					FUN_0119a3f0(mdCtx, *(void**)(s + 0x40), ok);
					uint got;
					EVP_DigestFinal_ex(mdCtx, digest + total, &got);
					total += got;
				}
				if (FUN_0117a150(0x72, digest, (int)total, p + 2, (int)rem, ((void*)((int*)pkey)[3])) <= 0)
					goto errSignature;
			}
			else
			{
				if (EVP_DigestUpdate(mdCtx, *(void**)(s + 0x40), ok) <= 0)
					goto errSignature;
				byte digest[64];
				uint dlen;
				EVP_DigestFinal_ex(mdCtx, digest, &dlen);
				if (FUN_0117a150(0x72, digest, (int)dlen, p + 2, (int)rem, ((void*)((int*)pkey)[3])) <= 0)
					goto errSignature;
			}
		}
		else
		{
errSignature:
			ERR_put_error(0x14, 0x8d, 0x33, 0, 0);
			goto cleanup;
		}
	}

finished:
	EVP_PKEY_free((void*)pkey);
	EVP_MD_CTX_cleanup(mdCtx);
done:
	if (0)
	{
err41:
		ERR_put_error(0x14, 0x8d, 0x41, 0, 0);
		goto cleanup;
err10:
		ERR_put_error(0x14, 0x8d, 0x10, 0, 0);
		goto cleanup;
	}
	return;

cleanup:
	if (rsaKey != 0) RSA_free((void*)rsaKey);
	if (dhKey != 0) DH_free((void*)dhKey);
	if (ecKey != 0) EC_KEY_free((void*)ecKey);
	if (ecPoint != 0) EC_POINT_free((void*)ecPoint);
	if (bnCtx != 0) BN_CTX_free((void*)bnCtx);
	if (pkey != 0) EVP_PKEY_free((void*)pkey);
	EVP_MD_CTX_cleanup(mdCtx);
}
