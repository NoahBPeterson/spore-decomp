// lib_cblock: DES (encrypt + key schedule), BN_div_recp and the OpenSSL UI string
// allocators.  The DES parts are the classic libdes/OpenSSL table-driven implementation.

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

// ---------------------------------------------------------------------------
// DES tables shared by the round function and the key schedule.
// ---------------------------------------------------------------------------
extern const u32 g_des_sp[8][64];      // 0x014f1aa8: 8 precomputed S-box/permutation tables

#define ROR32(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

struct DES_key_schedule {
    u32 ks[32];
};

// ---------------------------------------------------------------------------
// 0x011c5230  des_encrypt1: the 16 DES rounds over one 64-bit block.
//   The two key-schedule words per round are held in ks[0..31]; the forward
//   schedule starts at ks[0], the reverse schedule at ks[30].
// ---------------------------------------------------------------------------
// @ 0x011c5230
#define DES_ROUND(dst, src, k)                                                 \
    {                                                                          \
        u32 u = (src) ^ (k)[0];                                                \
        u32 t = ROR32((src) ^ (k)[1], 4);                                      \
        (dst) ^= g_des_sp[0][(u >> 2) & 0x3f] ^ g_des_sp[2][(u >> 10) & 0x3f] ^ \
                 g_des_sp[4][(u >> 18) & 0x3f] ^ g_des_sp[6][(u >> 26) & 0x3f] ^ \
                 g_des_sp[1][(t >> 2) & 0x3f] ^ g_des_sp[3][(t >> 10) & 0x3f] ^ \
                 g_des_sp[5][(t >> 18) & 0x3f] ^ g_des_sp[7][(t >> 26) & 0x3f]; \
    }

void des_encrypt1(u32* data, DES_key_schedule* ks, int enc)
{
    u32 l = (data[0] << 3) | (data[0] >> 29);
    u32 r = (data[1] << 3) | (data[1] >> 29);
    int i;

    if (enc)
    {
        const u32* s = &ks->ks[0];
        for (i = 0; i < 16; i += 4)
        {
            DES_ROUND(r, l, s);
            DES_ROUND(l, r, s + 2);
            DES_ROUND(r, l, s + 4);
            DES_ROUND(l, r, s + 6);
            s += 8;
        }

    }
    else
    {
        // the reverse schedule is consumed from ks[30] downwards
        const u32* s = &ks->ks[28];
        for (i = 0; i < 16; i += 4)
        {
            DES_ROUND(r, l, s + 2);
            DES_ROUND(l, r, s);
            DES_ROUND(r, l, s - 2);
            DES_ROUND(l, r, s - 4);
            s -= 8;
        }

    }

    data[0] = ROR32(r, 3);
    data[1] = ROR32(l, 3);
}

// ---------------------------------------------------------------------------
// 0x011c6c40  DES_set_key_unchecked: PC1, the 16 rotations and PC2, producing
//   the two 32-bit round-key words per round.
// ---------------------------------------------------------------------------
// @ 0x011c6c40
void des_set_key_unchecked(const u8* key, u32* schedule)
{
    static const u8 shifts2[16] =
        { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1 };

    // The key is read big-endian.
    u32 c = ((u32)key[0] << 24) | ((u32)key[1] << 16) | ((u32)key[2] << 8) | key[3];
    u32 d = ((u32)key[4] << 24) | ((u32)key[5] << 16) | ((u32)key[6] << 8) | key[7];

    // PC1, done with the usual 60 simple operations (the parity bits drop out).
    u32 t;
    t = ((d >> 4) ^ c) & 0x0f0f0f0f; c ^= t; d ^= t << 4;
    t = ((c << 18) ^ c) & 0xcccc0000; c ^= t ^ (t >> 18);
    t = ((d << 18) ^ d) & 0xcccc0000; d ^= t ^ (t >> 18);
    t = ((d >> 1) ^ c) & 0x55555555; c ^= t; d ^= t << 1;
    t = ((c >> 8) ^ d) & 0x00ff00ff; d ^= t; c ^= t << 8;
    t = ((d >> 1) ^ c) & 0x55555555; c ^= t; d ^= t << 1;

    d = ((d & 0x000000ff) << 16) | (d & 0x0000ff00) |
        ((d & 0x00ff0000) >> 16) | ((c & 0xf0000000) >> 4);
    c &= 0x0fffffff;

    for (int i = 0; i < 16; i++)
    {
        if (shifts2[i])
        {
            c = (c >> 2) | (c << 26);
            d = (d >> 2) | (d << 26);
        }
        else
        {
            c = (c >> 1) | (c << 27);
            d = (d >> 1) | (d << 27);
        }
        c &= 0x0fffffff;
        d &= 0x0fffffff;

        // PC2: the 48 selected bits are packed into the two round-key words so
        // that the round function finds them at bits 2..7, 10..15, 18..23 and
        // 26..31 of (R ^ key) and of ROTATE(R ^ key, 4) respectively.
        static const u8 pc2[48] = {
            14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4,
            26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40,
            51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
        };
        u64 cd = (((u64)c) << 28) | d;
        u32 out = 0;
        for (int j = 0; j < 48; j++)
            out = (out << 1) | (u32)((cd >> (56 - pc2[j])) & 1);

        u32 k0 = 0;
        u32 k1 = 0;
        for (int g = 0; g < 4; g++)
        {
            u32 six = (out >> (42 - 6 * g)) & 0x3f;    // groups 0..3 -> first word
            u32 top = (out >> (18 - 6 * g)) & 0x3f;    // groups 4..7 -> second word
            k0 |= six << (2 + 8 * g);
            k1 |= top << (6 + 8 * g);
        }
        // The last group wraps around the right-rotation by four.
        u32 last = out & 0x3f;
        k1 |= ((last & 3) << 30) | ((last >> 2) & 0xf);
        schedule[0] = k0;
        schedule[1] = k1;
        schedule += 2;
    }
}

// ---------------------------------------------------------------------------
// Big-number pieces used by BN_div_recp.
// ---------------------------------------------------------------------------
struct BIGNUM {
    u32* d;         // +0x00
    int top;        // +0x04
    int dmax;       // +0x08
    int neg;        // +0x0c
    int flags;      // +0x10
};
typedef int BN_CTX;

struct BN_RECP_CTX {
    BIGNUM N;       // +0x00
    BIGNUM Nr;      // +0x14
    int num_bits;   // +0x28
    int shift;      // +0x2c
    int flags;      // +0x30
};

void BN_CTX_start(BN_CTX* ctx);
BIGNUM* BN_CTX_get(BN_CTX* ctx);
void BN_CTX_end(BN_CTX* ctx);
int BN_ucmp(const BIGNUM* a, const BIGNUM* b);
int BN_set_word(BIGNUM* a, u32 w);
int BN_copy(BIGNUM* a, const BIGNUM* b);
int BN_num_bits(const BIGNUM* a);
int BN_reciprocal(BIGNUM* r, BIGNUM* d, int len, BN_CTX* ctx);
int BN_rshift(BIGNUM* r, const BIGNUM* a, int n);
int BN_mul(BIGNUM* r, const BIGNUM* a, const BIGNUM* b, BN_CTX* ctx);
int BN_usub(BIGNUM* r, const BIGNUM* a, const BIGNUM* b);
int BN_add_word(BIGNUM* a, u32 w);
void ERR_put_error(int lib, int func, int reason, const char* file, int line);

// ---------------------------------------------------------------------------
// 0x011c85a0  BN_div_recp: divide m by recp->N using the reciprocal.
// ---------------------------------------------------------------------------
// @ 0x011c85a0
int BN_div_recp(BIGNUM* dv, BIGNUM* rem, const BIGNUM* m, BN_RECP_CTX* recp, BN_CTX* ctx)
{
    BIGNUM* a;
    BIGNUM* b;
    int i, j;
    int ret = 0;

    BN_CTX_start(ctx);
    a = BN_CTX_get(ctx);
    b = BN_CTX_get(ctx);
    if (dv == 0)
        dv = BN_CTX_get(ctx);
    if (rem == 0)
        rem = BN_CTX_get(ctx);
    if (a == 0 || b == 0 || dv == 0 || rem == 0)
        goto end;

    if (BN_ucmp(m, &recp->N) < 0)
    {
        BN_set_word(dv, 0);
        if (!BN_copy(rem, m))
            goto end;
        BN_CTX_end(ctx);
        return 1;
    }

    i = BN_num_bits(m);
    j = recp->num_bits * 2;
    if (i < j)
        i = j;
    if (i != recp->shift)
        recp->shift = BN_reciprocal(&recp->Nr, &recp->N, i, ctx);
    if (recp->shift == -1)
        goto end;

    if (!BN_rshift(a, m, recp->num_bits))
        goto end;
    if (!BN_mul(b, a, &recp->Nr, ctx))
        goto end;
    if (!BN_rshift(dv, b, i - recp->num_bits))
        goto end;
    dv->neg = 0;

    if (!BN_mul(b, &recp->N, dv, ctx))
        goto end;
    if (!BN_usub(rem, m, b))
        goto end;
    rem->neg = 0;

    i = 0;
    while (BN_ucmp(rem, &recp->N) >= 0)
    {
        if (i > 2)
        {
            ERR_put_error(3, 0x82, 0x65, 0, 0);
            goto end;
        }
        if (!BN_usub(rem, rem, &recp->N))
            goto end;
        if (!BN_add_word(dv, 1))
            goto end;
        i++;
    }

    rem->neg = (rem->top == 0) ? 0 : m->neg;
    ret = 1;
    dv->neg = m->neg ^ recp->N.neg;

end:
    BN_CTX_end(ctx);
    return ret;
}

// ---------------------------------------------------------------------------
// The UI string allocators (ui_lib.c).
// ---------------------------------------------------------------------------
struct UI_METHOD;

struct UI {
    UI_METHOD* meth;    // +0x00
    void* strings;      // +0x04
};

struct UI_STRING {
    int type;           // +0x00
    UI* ui;             // +0x04
    const char* prompt; // +0x08
    int min;            // +0x0c
    int max;            // +0x10
    int result_buf;     // +0x14
    int extra;          // +0x18
    int freeable;       // +0x1c
};

void* CRYPTO_malloc(int num, const char* file, int line);
int sk_push(void* st, void* p);
void* sk_new_null();
void free_string(void* str);
void* FUN_0117df20();

// @ 0x011c88e0
UI_STRING* general_allocate_prompt(UI* ui, const char* prompt, int prompt_freeable,
                                   int type, int result_buf, int min, int max)
{
    if (ui == 0)
    {
        ERR_put_error(0x28, 0x6d, 0x43, 0, 0);
        return 0;
    }
    if ((type == 1 || type == 2 || type == 3) && min == 0)
    {
        ERR_put_error(0x28, 0x6d, 0x69, 0, 0);
        return 0;
    }

    UI_STRING* str = (UI_STRING*)CRYPTO_malloc(0x20, ".\\crypto\\ui\\ui_lib.c", 0x99);
    if (str != 0)
    {
        str->ui = ui;
        str->prompt = prompt;
        str->type = type;
        str->min = min;
        str->freeable = (prompt_freeable != 0);
    }
    return str;
}

// @ 0x011c8960
int general_allocate_string(UI* ui, const char* prompt, int prompt_freeable, int type,
                            int result_buf, int min, int max)
{
    UI_STRING* str = general_allocate_prompt(ui, prompt, prompt_freeable, type, result_buf, min, max);
    if (str == 0)
        return -1;

    if (ui->strings == 0)
    {
        ui->strings = sk_new_null();
        if (ui->strings == 0)
        {
            free_string(str);
            return -1;
        }
    }

    str->max = result_buf;
    str->result_buf = min;
    str->extra = max;

    int r = sk_push(ui->strings, str);
    if (r < 1)
        return r - 1;
    return r;
}

// @ 0x011c89e0
int UI_add_input_string(UI* ui, const char* prompt, int flags, int min, int max)
{
    return general_allocate_string(ui, prompt, flags, 1, min, max, 0);
}

// @ 0x011c8a10
int UI_add_verify_string(UI* ui, const char* prompt, int flags, int min, int max, int check)
{
    return general_allocate_string(ui, prompt, flags, 2, min, max, check);
}
