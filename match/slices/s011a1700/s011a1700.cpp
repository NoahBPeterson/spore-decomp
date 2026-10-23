// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// Slice s011a1700: the statically linked OpenSSL ssl3 record writer/reader.
// Seven cdecl helpers over the SSL / SSL3_STATE layout, modelled with raw
// byte offsets (the real headers are not available here).

#include <string.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---------------------------------------------------------------- callees
extern "C" {
int   __cdecl FUN_011a0770(char* s, int type, const void* buf, int len); // 0x11a0770
int   __cdecl FUN_011a0720(char* s);                                     // 0x11a0720
int   __cdecl FUN_0117c400(char* s);                                     // 0x117c400
int   __cdecl FUN_011874d0(int a);                                       // 0x11874d0
int   __cdecl FUN_011848a0(int a, int n);                                // 0x11848a0
int   __cdecl FUN_011a0d80(char* s, int type, const void* p, int a, int b); // 0x11a0d80
int   __cdecl FUN_011a5950(char* s, int a, int b);                       // 0x11a5950
int   __cdecl FUN_011a5900(char* s);                                     // 0x11a5900
void  __cdecl FUN_011a0930(char* s, int a, int b);                       // 0x11a0930
int   __cdecl FUN_011a1cf0(char* s, int a);                              // 0x11a1cf0
int   __cdecl FUN_011b67e0(void* out, int a, int b, int c);              // 0x11b67e0
int   __cdecl COMP_compress_block(int ctx, void* out, int outlen, void* in, int inlen); // 0x11968f0
void* __cdecl CRYPTO_malloc(int size, const char* file, int line);       // 0x1183410
void  __cdecl ERR_put_error(int lib, int fn, int reason, const char* file, int line);
int   __cdecl BIO_ctrl(void* b, int cmd, long larg, void* parg);         // 0x1177260
int   __cdecl i2d_X509(void* x, u8** pp);                                // 0x117cf60
void  __cdecl X509_free(void* x);                                        // 0x117cf90
int   __cdecl sk_num(void* st);                                          // 0x117dde0
void* __cdecl sk_value(void* st, int i);                                 // 0x117ddf0
void* __cdecl X509_get_issuer_name(void* x);                             // 0x117d590
void* __cdecl X509_get_subject_name(void* x);                            // 0x117d5a0
int   __cdecl X509_NAME_cmp(void* a, void* b);                           // 0x117d880
int   __cdecl X509_STORE_get_by_subject(void* ctx, int type, void* name, void* obj); // 0x1195850
void  __cdecl X509_STORE_CTX_cleanup(void* ctx);                         // 0x11b5ef0
}

// ======================================================================
// 0x11a1700   build and flush one record from the write buffer
// ======================================================================
// @ 0x011a1700 FUN_011a1700
int FUN_011a1700(char* s)
{
    char* s3 = *(char**)(s + 0x58);
    u8* lenp;
    int iv = 0;
    int r;

    *(int*)(s3 + 0x1b0) = 0;
    s3 = *(char**)(s + 0x58);

    if (*(int*)(s3 + 0xfc) != 0) {
        r = FUN_011a0770(s, 0x15, s3 + 0x1b4, 2);
        goto tail;
    }
    if (*(int*)(s3 + 0x1b0) != 0) {
        r = (*(int (__cdecl**)(char*))(*(int*)(s + 8) + 0x3c))(s);
        if (r <= 0) goto tail;
    }

    if (*(int*)(s + 0xbc) != 0 && *(int*)(s + 0x88) != 0 && *(int*)(s + 0x8c) != 0) {
        iv = FUN_011874d0(*(int*)(s + 0x8c));
        char* s3b = *(char**)(s + 0x58);
        if (*(int*)(s3b + 0xdc) == 0)
            *(int*)(s3b + 0xdc) = 1;
    }

    {
        u8* buf = *(u8**)(s3 + 0xf0);
        buf[0] = 0x15;
        *(int*)(s3 + 0x130) = 0x15;
        buf[1] = (u8)(*(int*)s >> 8);
        buf[2] = *(u8*)s;
        lenp = buf + 3;
        buf += 5;
        *(u8**)(s3 + 0x13c) = buf;
        *(int*)(s3 + 0x134) = 2;
        *(char**)(s3 + 0x140) = s3 + 0x1b4;

        if (*(int*)(s + 0x90) == 0) {
            *(u16*)buf = *(u16*)(s3 + 0x1b4);
            *(int*)(s3 + 0x140) = *(int*)(s3 + 0x13c);
        } else if (FUN_011a0720(s) == 0) {
            ERR_put_error(0x14, 0x68, 0x8d, 0, 0);
            *(int*)(*(char**)(s + 0x58) + 0x1b0) = 1;
            return -1;
        }

        if (iv != 0) {
            (*(void (__cdecl**)(char*, u8*, int))(*(int*)(*(int*)(s + 8) + 0x64) + 4))
                (s, buf + *(int*)(s3 + 0x134), 1);
            *(int*)(s3 + 0x134) += iv;
            *(int*)(s3 + 0x140) = (int)buf;
            *(int*)(s3 + 0x13c) = (int)buf;
        }

        (*(void (__cdecl**)(char*, int))*(int*)(*(int*)(s + 8) + 0x64))(s, 1);

        lenp[0] = *(u8*)(s3 + 0x135);
        lenp[1] = *(u8*)(s3 + 0x134);
        *(int*)(s3 + 0x134) += 5;
        int len = *(int*)(s3 + 0x134);
        *(int*)(s3 + 0x130) = 0x15;
        *(int*)(s3 + 0xfc) = len;
        *(int*)(s3 + 0xf8) = 0;
        *(int*)(*(char**)(s + 0x58) + 0x174) = 2;
        *(char**)(*(char**)(s + 0x58) + 0x180) = s3 + 0x1b4;
        *(int*)(*(char**)(s + 0x58) + 0x178) = 0x15;
        *(int*)(*(char**)(s + 0x58) + 0x17c) = 2;
        r = FUN_011a0770(s, 0x15, s3 + 0x1b4, 2);
    }

tail:
    if (r < 1) {
        *(int*)(*(char**)(s + 0x58) + 0x1b0) = 1;
        return r;
    }
    if (*(u8*)(*(char**)(s + 0x58) + 0x1b4) == 2)
        BIO_ctrl(*(void**)(s + 0x10), 0xb, 0, 0);
    if (*(int*)(s + 0x64) != 0)
        (*(void (__cdecl**)(int, int, int, char*, int, char*, int))(*(int*)(s + 0x64)))
            (1, *(int*)s, 0x15, *(char**)(s + 0x58) + 0x1b4, 2, s, *(int*)(s + 0x68));
    {
        int cb = *(int*)(s + 0xcc);
        if (cb == 0) {
            cb = *(int*)(*(char**)(s + 0xd8) + 0x9c);
            if (cb == 0)
                return r;
        }
        (*(void (__cdecl**)(char*, int, int))cb)
            (s, 0x4008,
             ((u32)*(u8*)(*(char**)(s + 0x58) + 0x1b4) << 8) |
              *(u8*)(*(char**)(s + 0x58) + 0x1b5));
    }
    return r;
}

// ======================================================================
// 0x11a1990   append bytes to the current record, flushing as needed
// ======================================================================
// @ 0x011a1990 FUN_011a1990
u32 FUN_011a1990(char* s, int type, const u8* buf, int len)
{
    char* s3 = *(char**)(s + 0x58);
    int off = *(int*)(s3 + 0x170);
    *(int*)(s3 + 0x170) = 0;
    *(int*)(s + 0x18) = 1;

    u32 r = (u32)FUN_0117c400(s);
    if ((r & 0x3000) != 0 && *(int*)(s + 0x1c) == 0) {
        r = (*(u32 (__cdecl**)(char*))(s + 0x20))(s);
        if ((int)r < 0)
            return r;
        if (r == 0) {
            ERR_put_error(0x14, 0x9e, 0xe5, 0, 0);
            return 0xffffffff;
        }
    }

    u32 n = (u32)len - (u32)off;

    for (;;) {
        int block = (n > 0x4000) ? 0x4000 : (int)n;
        int pad = 0;
        int bpad = 0;
        s3 = *(char**)(s + 0x58);

        if (*(int*)(s3 + 0xfc) != 0) {
            r = (u32)FUN_011a0770(s, type, buf + off, block);
        } else {
            if (*(int*)(s3 + 0x1b0) != 0) {
                r = (u32)(*(int (__cdecl**)(char*))(*(int*)(s + 8) + 0x3c))(s);
                if ((int)r <= 0)
                    goto out;
            }
            if (block == 0) {
                *(int*)(*(char**)(s + 0x58) + 0x170) = off;
                return 0;
            }

            if (*(int*)(s + 0xbc) != 0 && *(int*)(s + 0x88) != 0 && *(int*)(s + 0x8c) != 0) {
                bpad = FUN_011874d0(*(int*)(s + 0x8c));
                char* s3b = *(char**)(s + 0x58);
                if (*(int*)(s3b + 0xdc) == 0) {
                    if (*(int*)(s3b + 0xd8) != 0 && type == 0x17) {
                        bpad = FUN_011a0d80(s, 0x17, buf + off, 0, 1);
                        if (bpad <= 0) {
                            ERR_put_error(0x14, 0x68, 0x8d, 0, 0);
                            r = 0xffffffff;
                            goto out;
                        }
                        if ((u32)(bpad + 0x4805) > *(u32*)(*(char**)(s + 0x58) + 0xf4)) {
                            ERR_put_error(0x14, 0x68, 0x44, 0, 0);
                            r = 0xffffffff;
                            goto out;
                        }
                    }
                    *(int*)(*(char**)(s + 0x58) + 0xdc) = 1;
                }
            }

            {
                char* w = *(char**)(s + 0x58);
                u8* dst = *(u8**)(w + 0xf0) + bpad;
                u8* payload = dst + 5;
                dst[0] = (u8)type;
                *(int*)(w + 0x130) = type;
                dst[1] = (u8)(*(int*)s >> 8);
                dst[2] = *(u8*)s;
                *(u8**)(w + 0x13c) = payload;
                *(int*)(w + 0x134) = block;
                *(const u8**)(w + 0x140) = buf + off;

                if (*(int*)(s + 0x90) == 0) {
                    memcpy(payload, buf + off, block);
                    *(int*)(w + 0x140) = *(int*)(w + 0x13c);
                } else {
                    int c = COMP_compress_block(*(int*)(s + 0x90),
                                                *(void**)(w + 0x13c), 0x4400,
                                                *(void**)(w + 0x140), *(int*)(w + 0x134));
                    if (c < 0) {
                        ERR_put_error(0x14, 0x68, 0x8d, 0, 0);
                        r = 0xffffffff;
                        goto out;
                    }
                    *(int*)(w + 0x134) = c;
                    *(int*)(w + 0x140) = *(int*)(w + 0x13c);
                }

                if (pad != 0) {
                    (*(void (__cdecl**)(char*, u8*, int))(*(int*)(*(int*)(s + 8) + 0x64) + 4))
                        (s, payload + *(int*)(w + 0x134), 1);
                    *(int*)(w + 0x134) += pad;
                    *(u8**)(w + 0x140) = payload;
                    *(u8**)(w + 0x13c) = payload;
                }

                (*(void (__cdecl**)(char*, int))*(int*)(*(int*)(s + 8) + 0x64))(s, 1);

                dst[3] = *(u8*)(w + 0x135);
                dst[4] = *(u8*)(w + 0x134);
                *(int*)(w + 0x134) += 5;
                *(int*)(w + 0x130) = type;
                *(int*)(w + 0xfc) = *(int*)(w + 0x134) + bpad;
                *(int*)(w + 0xf8) = 0;
                *(int*)(*(char**)(s + 0x58) + 0x174) = block;
                *(const u8**)(*(char**)(s + 0x58) + 0x180) = buf + off;
                *(int*)(*(char**)(s + 0x58) + 0x178) = type;
                *(int*)(*(char**)(s + 0x58) + 0x17c) = block;
                r = (u32)FUN_011a0770(s, type, buf + off, block);
            }
        }

        if ((int)r <= 0) {
            *(int*)(*(char**)(s + 0x58) + 0x170) = off;
            return r;
        }
        if (r == n || (type == 0x17 && (*(u8*)(s + 0xf8) & 1) != 0)) {
            *(int*)(*(char**)(s + 0x58) + 0xdc) = 0;
            return r + (u32)off;
        }
        n -= r;
        off += (int)r;
    }

out:
    *(int*)(*(char**)(s + 0x58) + 0x170) = off;
    return r;
}

// ======================================================================
// 0x11a1d80   finish a certificate-verify handshake message
// ======================================================================
// @ 0x011a1d80 FUN_011a1d80
void FUN_011a1d80(char* s, int a2, int a3, int a4, int a5)
{
    if (*(int*)(s + 0x34) == a2) {
        char* s3 = *(char**)(s + 0x58);
        u8* wb = (u8*)*(int*)(*(int*)(s + 0x3c) + 4);
        u32 n = (*(u32 (__cdecl**)(char*, int, int, int, int, int))
                 (*(int*)(*(int*)(s + 8) + 0x64) + 0x14))
                (s, (int)(s3 + 0x184), (int)(s3 + 0x194), a4, a5, (int)(s3 + 0x248));

        *(u32*)(*(char**)(s + 0x58) + 0x2c8) = n;
        memcpy(wb + 4, *(char**)(s + 0x58) + 0x248, n);
        *(wb++) = 0x14;
        wb[0] = n >> 16;
        wb[1] = n >> 8;
        wb[2] = n;
        *(u32*)(s + 0x44) = n + 4;
        *(int*)(s + 0x48) = 0;
        *(int*)(s + 0x34) = a3;
    }
    FUN_011a1cf0(s, 0x16);
}

// ======================================================================
// 0x11a1e30   check the peer certificate against the stored session id
// ======================================================================
// @ 0x011a1e30 FUN_011a1e30
int FUN_011a1e30(char* s, int a2, int a3)
{
    int al;
    int i;
    u32 l = (*(u32 (__cdecl**)(char*, int, int, int, int, int*))(*(int*)(s + 8) + 0x30))
            (s, a2, a3, 0x14, 0x40, &i);

    if (i == 0)
        return (int)l;

    if (*(int*)(*(char**)(s + 0x58) + 0x1a4) == 0) {
        al = 0xa;
        ERR_put_error(0x14, 0x8c, 0x9a, 0, 0);
        goto f_err;
    }
    *(int*)(*(char**)(s + 0x58) + 0x1a4) = 0;
    {
        u32 fl = *(u32*)(*(char**)(s + 0x58) + 0x34c);
        u8* p = *(u8**)(s + 0x40);
        if (fl != l) {
            al = 0x32;
            ERR_put_error(0x14, 0x8c, 0x6f, 0, 0);
            goto f_err;
        }
        if (memcmp(p, *(char**)(s + 0x58) + 0x2cc, fl) != 0) {
            al = 0x33;
            ERR_put_error(0x14, 0x8c, 0x95, 0, 0);
            goto f_err;
        }
    }
    return 1;
f_err:
    FUN_011a0930(s, 2, al);
    return 0;
}

// ======================================================================
// 0x11a1f60   build the certificate chain message
// ======================================================================
// @ 0x011a1f60 FUN_011a1f60
int FUN_011a1f60(char* s, void* x)
{
    u8* p88;
    int n84, n80;
    char n7c[4];
    int n78 = 0;
    char st74[116];
    int mode, i3, i4, i2, i6;

    i3 = 7;
    if ((*(u8*)(s + 0xf8) & 8) == 0 && *(int*)(*(char**)(s + 0xd8) + 0x94) == 0)
        mode = 0;
    else
        mode = 1;

    i4 = *(int*)(s + 0x3c);
    if (FUN_011848a0(i4, 10) == 0) {
        ERR_put_error(0x14, 0x93, 7, 0, 0);
        return 0;
    }

    if (x == 0)
        goto lab210c;

    if (!mode) {
        if (FUN_011b67e0(st74, *(int*)(*(char**)(s + 0xd8) + 0xc), 0, 0) == 0) {
            ERR_put_error(0x14, 0x93, 0xb, 0, 0);
            return 0;
        }
    }

    n84 = i2d_X509(x, 0);
    i2 = FUN_011848a0(i4, n84 + 10);
    while (i2 != 0) {
        p88 = (u8*)(*(int*)(i4 + 4) + i3);
        p88[0] = (u8)(n84 >> 16);
        p88[1] = (u8)(n84 >> 8);
        p88[2] = (u8)n84;
        p88 += 3;
        i2d_X509(x, &p88);
        i3 = i3 + 3 + n84;
        if (mode)
            goto lab210c;
        if (X509_NAME_cmp(X509_get_subject_name(x), X509_get_issuer_name(x)) == 0) {
            X509_STORE_CTX_cleanup(st74);
            goto lab210c;
        }
        i2 = X509_STORE_get_by_subject(st74, 1, X509_get_issuer_name(x), n7c);
        x = (void*)n78;
        if (i2 < 1) {
            X509_STORE_CTX_cleanup(st74);
            goto lab210c;
        }
        X509_free((void*)n78);
        n84 = i2d_X509(x, 0);
        i2 = FUN_011848a0(i4, n84 + 3 + i3);
    }

lab20dd:
    ERR_put_error(0x14, 0x93, 7, 0, 0);
    return 0;

lab210c:
    i2 = *(int*)(*(char**)(s + 0xd8) + 0x94);
    if (i2 != 0) {
        i6 = 0;
        i2 = sk_num(*(void**)(*(char**)(s + 0xd8) + 0x94));
        if (i2 > 0) {
            do {
                void* v = sk_value(*(void**)(*(char**)(s + 0xd8) + 0x94), i6);
                n84 = i2d_X509(v, 0);
                n80 = n84 + 3 + i3;
                if (FUN_011848a0(i4, n80) == 0)
                    goto lab20dd;
                p88 = (u8*)(*(int*)(i4 + 4) + i3);
                p88[0] = (u8)(n84 >> 16);
                p88[1] = (u8)(n84 >> 8);
                p88[2] = (u8)n84;
                p88 += 3;
                i2d_X509(v, &p88);
                i3 = n80;
                i6++;
                i2 = sk_num(*(void**)(*(char**)(s + 0xd8) + 0x94));
            } while (i6 < i2);
        }
    }
    {
        u8* bp = *(u8**)(i4 + 4);
        i6 = i3 - 7;
        bp[4] = (u8)((u32)i6 >> 16);
        bp[5] = (u8)((u32)i6 >> 8);
        bp[6] = (u8)i6;
        int v4 = i3 - 4;
        bp[0] = 0xb;
        bp[1] = (u8)((u32)v4 >> 16);
        bp[2] = (u8)((u32)v4 >> 8);
        bp[3] = (u8)v4;
    }
    return i3;
}

// ======================================================================
// 0x11a2250   read one handshake record of the expected type
// ======================================================================
// @ 0x011a2250 FUN_011a2250
int FUN_011a2250(char* s, int a2, int a3, int a4, u32 a5, int* out)
{
    char* s3 = *(char**)(s + 0x58);

    if (*(int*)(s3 + 0x368) != 0) {
        *(int*)(s3 + 0x368) = 0;
        if (a4 >= 0 && *(u32*)(s3 + 0x354) != (u32)a4) {
            ERR_put_error(0x14, 0x8e, 0xf4, 0, 0);
            FUN_011a0930(s, 2, 0xa);
            *out = 0;
            return -1;
        }
        *out = 1;
        *(int*)(s + 0x40) = *(int*)(*(int*)(s + 0x3c) + 4) + 4;
        int v = *(int*)(*(char**)(s + 0x58) + 0x350);
        *(int*)(s + 0x44) = v;
        return v;
    }

    u8* pb = (u8*)*(int*)(*(int*)(s + 0x3c) + 4);
    if (*(int*)(s + 0x34) != a2)
        goto lab2455;

    for (;;) {
        while (*(int*)(s + 0x44) < 4) {
            int r = (*(int (__cdecl**)(char*, int, u8*, int, int))(*(int*)(s + 8) + 0x34))
                        (s, 0x16, pb + *(int*)(s + 0x44), 4 - *(int*)(s + 0x44), 0);
            if (r < 1) {
                *(int*)(s + 0x18) = 3;
                *out = 0;
                return r;
            }
            *(int*)(s + 0x44) += r;
        }
        if (*(int*)(s + 0x24) != 0 || pb[0] != 0 || pb[1] != 0 || pb[2] != 0 || pb[3] != 0)
            break;
        *(int*)(s + 0x44) = 0;
        if (*(int*)(s + 0x64) != 0)
            (*(void (__cdecl**)(int, int, int, u8*, int, char*, int))(*(int*)(s + 0x64)))
                (0, *(int*)s, 0x16, pb, 4, s, *(int*)(s + 0x68));
    }

    if (a4 < 0) {
        if (pb[0] == 1 && a2 == 0x2180 && a3 == 0x2181)
            FUN_011a5900(s);
    } else if (pb[0] != (u8)a4) {
        ERR_put_error(0x14, 0x8e, 0xf4, 0, 0);
        FUN_011a0930(s, 2, 0xa);
        *out = 0;
        return -1;
    }

    *(int*)(*(char**)(s + 0x58) + 0x354) = pb[0];
    {
        u32 len = ((u32)pb[1] << 16) | ((u32)pb[2] << 8) | (u32)pb[3];
        if (len > a5 || len > 0x7ffffffb) {
            ERR_put_error(0x14, 0x8e, 0x98, 0, 0);
            FUN_011a0930(s, 2, 0x2f);
            *out = 0;
            return -1;
        }
        if (len != 0 && FUN_011848a0(*(int*)(s + 0x3c), (int)len + 4) == 0) {
            ERR_put_error(0x14, 0x8e, 7, 0, 0);
            *out = 0;
            return -1;
        }
        *(u32*)(*(char**)(s + 0x58) + 0x350) = len;
        *(int*)(s + 0x34) = a3;
        *(int*)(s + 0x40) = *(int*)(*(int*)(s + 0x3c) + 4) + 4;
        *(int*)(s + 0x44) = 0;
    }

lab2455:
    {
        int rem = *(int*)(*(char**)(s + 0x58) + 0x350) - *(int*)(s + 0x44);
        int base = *(int*)(s + 0x40);
        while (rem > 0) {
            int r = (*(int (__cdecl**)(char*, int, int, int, int))(*(int*)(s + 8) + 0x34))
                        (s, 0x16, base + *(int*)(s + 0x44), rem, 0);
            if (r <= 0) {
                *(int*)(s + 0x18) = 3;
                *out = 0;
                return r;
            }
            *(int*)(s + 0x44) += r;
            rem -= r;
        }
        FUN_011a5950(s, *(int*)(*(int*)(s + 0x3c) + 4), *(int*)(s + 0x44) + 4);
        if (*(int*)(s + 0x64) != 0)
            (*(void (__cdecl**)(int, int, int, u8*, int, char*, int))(*(int*)(s + 0x64)))
                (0, *(int*)s, 0x16, (u8*)*(int*)(*(int*)(s + 0x3c) + 4),
                 *(int*)(s + 0x44) + 4, s, *(int*)(s + 0x68));
        *out = 1;
        return *(int*)(s + 0x44);
    }
}

// ======================================================================
// 0x11a2610   allocate the read/write record buffers
// ======================================================================
// @ 0x011a2610 FUN_011a2610
int FUN_011a2610(char* s)
{
    if (*(int*)(*(char**)(s + 0x58) + 0xe0) == 0) {
        int len = (*(u8*)(s + 0xf4) & 0x20) * 0x200 + 0x4805;
        void* p = CRYPTO_malloc(len, ".\\ssl\\s3_both.c", 0x25a);
        if (p == 0)
            goto err;
        *(void**)(*(char**)(s + 0x58) + 0xe0) = p;
        *(int*)(*(char**)(s + 0x58) + 0xe4) = len;
    }
    if (*(int*)(*(char**)(s + 0x58) + 0xf0) == 0) {
        void* p = CRYPTO_malloc(0x490a, ".\\ssl\\s3_both.c", 0x264);
        if (p == 0)
            goto err;
        *(void**)(*(char**)(s + 0x58) + 0xf0) = p;
        *(int*)(*(char**)(s + 0x58) + 0xf4) = 0x490a;
    }
    *(int*)(s + 0x4c) = *(int*)(*(char**)(s + 0x58) + 0xe0);
    return 1;
err:
    ERR_put_error(0x14, 0x9c, 0x41, 0, 0);
    return 0;
}
