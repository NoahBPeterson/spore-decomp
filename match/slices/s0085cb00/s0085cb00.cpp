// Slice s0085cb00 - EA JPEG encoder (modified libjpeg) "master"/entropy family.
// 16 functions.  Field offsets follow the retail (SporeApp.exe) layout, which
// differs from stock IJG 6a.  32-bit MSVC 2008 SP1, /O2 /MD /Gy /EHsc /TP.

typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            i32;

#include <intrin.h>

namespace lib_jpeg {
    // real retail symbols live at these VAs; declare them under hex-embedded names so
    // the differential harness resolves the call targets by address.
}

// lib_jpeg helpers (real VAs, referenced by address)
extern "C" i32  Fn_00866850(i32 a, i32 b);              // lib_jpeg::jdiv_round_up
extern "C" void Fn_00866880(void *in, i32 src_row, void *out, i32 dst_row,
                            i32 num_rows, u32 rowsize); // lib_jpeg::jcopy_sample_rows

// alloc/memset-style lib helper at 0x011e073e
extern "C" void f_011e073e(void *dst, i32 val, unsigned size);

// out-of-slice encoder helpers
extern "C" {
    void f_00865450(void *);
    void f_00866700(void *);
    void f_008594d0(void);
    void f_0085ee50(void *);
    void f_0085e900(void *, i32);
    void f_00859980(void *);
    void f_0085e5c0(void);
    void f_0085a390(void);
    void f_00858f80(void *, i32);
    void f_0085afd0(void *, i32);
}

// error manager: fn at +0x00, msg_code at +0x14, parm at +0x18
struct ErrMgr {
    void (*fn)(void *);
    char pad[0x10];
    i32  msg_code;
    i32  parm;
};

struct MemMgr {
    void *(*alloc_small)(void *cinfo, i32 pool_id, u32 size);
    void *(*alloc_large)(void *cinfo, i32 pool_id, u32 size);
};

// entropy-coder state, cinfo+0x5b8 (0x60 bytes)
struct Entropy {
    void (*fn00)(void *);
    void (*fn04)(void *, i32 *);
    void (*fn08)(void *);
    void (*fn0c)(void *);
    void (*fn10)(void *);
    void (*fn14)(void *);
    void (*fn18)(void *);
    void (*fn1c)(void *);
    void (*fn20)(void *);
    void (*fn24)(void *);
    void (*fn28)(void *);
    void (*fn2c)(void *);
    void (*fn30)(void *);
    void (*fn34)(void *);
    void (*fn38)(void *);
    void (*fn3c)(void *);
    void (*fn40)(void *);
    void (*fn44)(void *);
    void (*fn48)(void *, i32 *);
    void (*fn4c)(void *);
    i32  f50;
    i32  f54;
    i32  f58;
    i32  f5c;
};

// master compressor state, cinfo+0x5c4 (0x30 bytes)
struct Master {
    void (*fn00)(void *);
    void (*fn04)(void *);
    void (*fn08)(void *);
    void (*fn0c)(void *, i32, i32 *, void **);
    u8  *buf10;
    u8  *buf14;
    u8  *buf18;
    u8  *buf1c;
    u8  *buf20;
    i32  f24;
    u32  f28;
    i32  f2c;
};

// scan/per-pass state, cinfo+0x5a4 (0x1c bytes)
struct ScanInfo {
    i32 f00, f04, f08, f0c, f10, f14, f18;
};

// component record, stride 0x54, array at cinfo+0xd8
struct Comp {
    u8  pad0[0x08];
    i32 f08;
    i32 f0c;
    u8  pad10[0x08];
    i32 f18;
    u8  pad1c[0x08];
    i32 f24;
    i32 f28;
    i32 f2c;
    u8  pad30[0x24];
};

struct CInfo {
    ErrMgr  *err;   // +0x00
    MemMgr  *mem;   // +0x04
    void    *f08;   // +0x08
    i32      f0c;   // +0x0c
    i32      f10;   // +0x10
    i32      f14;   // +0x14
    i32      f18;   // +0x18
    i32      f1c;   // +0x1c
    i32      f20;   // +0x20
    i32      f24;   // +0x24
    i32      f28;   // +0x28
    i32      f2c;   // +0x2c
    i32      f30;   // +0x30
    i32      f34;   // +0x34
    i32      f38;   // +0x38
    i32      f3c;   // +0x3c
    i32      f40;   // +0x40
    i32      f44;   // +0x44
    i32      f48;   // +0x48
    i32      f4c;   // +0x4c
    i32      f50;   // +0x50
    i32      f54;   // +0x54
    i32      f58;   // +0x58
    i32      f5c;   // +0x5c
    i32      f60;   // +0x60
    i32      f64;   // +0x64
    i32      f68;   // +0x68
    i32      f6c;   // +0x6c
    i32      f70;   // +0x70
    i32      f74;   // +0x74
    i32      f78;   // +0x78
    i32      f7c;   // +0x7c
    i32      f80;   // +0x80
    i32      f84;   // +0x84
    i32      f88;   // +0x88
    i32      f8c;   // +0x8c
    i32      f90;   // +0x90
    char     pad94[0x44];  // 0x94..0xd8
    Comp    *comps;        // +0xd8
    i32      fdc;          // +0xdc
    i32      fe0;          // +0xe0
    char     pad114[0x114 - 0xe4];
    i32      f114;         // +0x114
    char     pad118[0x12c - 0x118];
    i32      f12c;         // +0x12c
    char     pad130[0x534 - 0x130];
    i32      f534;         // +0x534
    i32      f538;         // +0x538
    i32      f53c;         // +0x53c
    i32      f540;         // +0x540
    u8      *table_base;   // +0x544
    i32      f548;         // +0x548
    char     pad54c[0x5a0 - 0x54c];
    i32      f5a0;         // +0x5a0
    void    *f5a4;         // +0x5a4
    void    *f5a8;         // +0x5a8
    void    *f5ac;         // +0x5ac
    void    *f5b0;         // +0x5b0
    void    *f5b4;         // +0x5b4
    Entropy *ent;          // +0x5b8
    void    *f5bc;         // +0x5bc
    void    *f5c0;         // +0x5c0
    Master  *master;       // +0x5c4
    void    *f5c8;         // +0x5c8
    void    *f5cc;         // +0x5cc
};

#define VTFN(p, i) (*(void **)((u8 *)(p) + (i)))
#define C(p) ((CInfo *)(p))

// in-slice forward declaration (defined later in this file)
void FUN_0085d830(void *);

extern "C" {
    void Fn_0085c960(void);
    void Fn_0085b760(void);
    void Fn_0085d480(void);
    void Fn_0085c330(void *, i32, void *, u32);
    void Fn_0085c5b0(void *, i32 *);
    void Fn_0085b9e0(void *, i32 *);
}

// ---------------------------------------------------------------------------
// @ 0x0085cb00
void FUN_0085cb00(void *param_1) {
    CInfo *c = C(param_1);
    i32 z = 0;
    *(i32 *)((u8 *)c + 0xd8) = z;
    *(i32 *)((u8 *)c + 0x90) = z;
    *(i32 *)((u8 *)c + 0x5a0) = z;
    Entropy *e1 = c->ent;
    e1->f50 = z;
    Entropy *e2 = c->ent;
    e2->f54 = z;
    Entropy *e3 = c->ent;
    e3->f5c = z;
}

// ---------------------------------------------------------------------------
// @ 0x0085cb40
void FUN_0085cb40(void *param_1) {
    CInfo *c = C(param_1);
    Entropy *e = (Entropy *)c->mem->alloc_small(param_1, 0, 0x60);
    c->ent = e;
    e->fn00 = (void (*)(void *))&FUN_0085cb00;
    e->fn04 = (void (*)(void *, i32 *))&Fn_0085c5b0;
    e->fn08 = (void (*)(void *))&Fn_0085c960;
    e->fn0c = (void (*)(void *))&Fn_0085c330;
    for (i32 off = 0x10; off < 0x50; off += 4)
        *(void **)((u8 *)e + off) = (void *)&Fn_0085c330;
    e->fn10 = (void (*)(void *))&Fn_0085b760;
    e->fn48 = (void (*)(void *, i32 *))&Fn_0085b9e0;
    i32 z = 0;
    Entropy *e1 = c->ent;
    *(i32 *)((u8 *)c + 0xd8) = z;
    *(i32 *)((u8 *)c + 0x90) = z;
    *(i32 *)((u8 *)c + 0x5a0) = z;
    e1->f50 = z;
    Entropy *e2 = c->ent;
    e2->f54 = z;
    Entropy *e3 = c->ent;
    e3->f5c = z;
}

// ---------------------------------------------------------------------------
// @ 0x0085cbf0
i32 __fastcall FUN_0085cbf0(void *unused, void *param_2) {
    (void)unused;
    CInfo *c = C(param_2);
    if (c->f4c != 0) return 0;
    if (c->f12c != 0) return 0;
    if (c->f24 != 3) return 0;
    if (c->f20 != 3) return 0;
    if (c->f28 != 2) return 0;
    if (c->f78 != 3) return 0;
    u8 *s = (u8 *)c->comps;
    if (*(i32 *)(s + 0x08) != 2) return 0;
    if (*(i32 *)(s + 0x5c) != 1) return 0;
    if (*(i32 *)(s + 0xb0) != 1) return 0;
    if (*(i32 *)(s + 0x0c) > 2) return 0;
    if (*(i32 *)(s + 0x60) != 1) return 0;
    if (*(i32 *)(s + 0xb4) != 1) return 0;
    if (*(i32 *)(s + 0x24) != c->f53c) return 0;
    if (*(i32 *)(s + 0x78) != c->f53c) return 0;
    if (*(i32 *)(s + 0xcc) != c->f53c) return 0;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x0085cc70
void FUN_0085cc70(void *param_1) {
    CInfo *c = C(param_1);
    if (c->f10 != 0xca) {
        c->err->msg_code = 0x12;
        c->err->parm = c->f10;
        c->err->fn(param_1);
    }
    i32 eax = c->f2c;
    u32 ecx = (u32)c->f30;
    i32 r2;
    if ((u32)(eax * 8) <= ecx) {
        c->f70 = Fn_00866850(c->f18, 8);
        r2 = Fn_00866850(c->f1c, 8);
        c->f53c = 1;
    } else if ((u32)(eax * 4) <= ecx) {
        c->f70 = Fn_00866850(c->f18, 4);
        r2 = Fn_00866850(c->f1c, 4);
        c->f53c = 2;
    } else if ((u32)(eax * 2) <= ecx) {
        c->f70 = Fn_00866850(c->f18, 2);
        r2 = Fn_00866850(c->f1c, 2);
        c->f53c = 4;
    } else {
        c->f70 = c->f18;
        r2 = c->f1c;
        c->f53c = 8;
    }
    c->f74 = r2;
    i32 ncomp = c->f20;
    if (ncomp > 0) {
        u8 *cc = (u8 *)c->comps + 0xc;
        for (i32 i = 0; i < ncomp; i++) {
            i32 a = c->f53c;
            i32 v = a;
            if (a < 8) {
                do {
                    if (c->f534 * a < *(i32 *)(cc - 4) * v * 2) break;
                    if (c->f538 * a < *(i32 *)(cc) * v * 2) break;
                    v *= 2;
                } while (v < 8);
            }
            *(i32 *)(cc + 0x18) = v;
            cc += 0x54;
        }
    }
    if (ncomp > 0) {
        u8 *cc = (u8 *)c->comps + 0x24;
        for (i32 i = 0; i < ncomp; i++) {
            *(i32 *)(cc + 4) = Fn_00866850(
                *(i32 *)(cc - 0x1c) * *(i32 *)(cc) * c->f18, c->f534 * 8);
            *(i32 *)(cc + 8) = Fn_00866850(
                *(i32 *)(cc - 0x18) * c->f1c * *(i32 *)(cc), c->f538 * 8);
            cc += 0x54;
        }
    }
    switch (c->f28) {
    case 1: c->f78 = 1; break;
    case 2:
    case 3: c->f78 = 3; break;
    case 4:
    case 5: c->f78 = 4; break;
    default: c->f78 = c->f20; break;
    }
    i32 v = (c->f54 == 0) ? c->f78 : 1;
    c->f7c = v;
    if (FUN_0085cbf0(param_1, c) == 0)
        c->f80 = 1;
    else
        c->f80 = c->f538;
}

// ---------------------------------------------------------------------------
// @ 0x0085cea0
void FUN_0085cea0(void *param_1) {
    CInfo *c = C(param_1);
    u8 *d = (u8 *)c->mem->alloc_small(param_1, 1, 0x580);
    u8 *base = d + 0x100;
    c->table_base = base;
    f_011e073e(d, 0, 0x100);
    for (i32 i = 0; i <= 0xff; i++)
        base[i] = (u8)i;
    f_011e073e(base + 0x100, 0xff, 0x180);
    f_011e073e(base + 0x280, 0, 0x180);
    u8 *dst = base + 0x400;
    u8 *src = base;
    __movsd((unsigned long *)dst, (unsigned long *)src, 0x20);
}

// ---------------------------------------------------------------------------
// @ 0x0085cf30
void FUN_0085cf30(void *param_1) {
    CInfo *c = C(param_1);
    ScanInfo *s = (ScanInfo *)c->f5a4;
    FUN_0085cc70(param_1);
    FUN_0085cea0(param_1);
    s->f0c = 0;
    s->f10 = FUN_0085cbf0(param_1, c);
    s->f14 = 0;
    s->f18 = 0;
    if (c->f54 == 0 || c->f40 == 0) {
        c->f64 = 0;
        c->f68 = 0;
        c->f6c = 0;
    }
    i32 one = 1;
    if (c->f54 == 0) goto Lcfdd;
    if (c->f44 != 0) {
        c->err->msg_code = 0x2e;
        c->err->fn(param_1);
    }
    if (c->f78 == 3) {
        if (c->f88 != 0) {
            c->f68 = one;
            goto Lcfaa;
        }
        if (c->f5c == 0) goto Lcfa7;
        c->f6c = one;
        goto Lcfaa;
    }
    c->f68 = 0;
    c->f6c = 0;
    c->f88 = 0;
Lcfa7:
    c->f64 = one;
Lcfaa:
    if (c->f64 != 0) {
        f_00865450(param_1);
        s->f14 = (i32)c->f5cc;
    }
    if (c->f6c != 0 || c->f68 != 0) {
        f_00866700(param_1);
        s->f18 = (i32)c->f5cc;
    }
Lcfdd:
    if (c->f44 == 0) {
        if (s->f10 == 0) {
            f_008594d0();
            f_0085ee50(param_1);
        } else {
            FUN_0085d830(param_1);
        }
        f_0085e900(param_1, c->f6c);
    }
    f_00859980(param_1);
    if (c->fe0 == 0) {
        if (c->fdc == 0)
            f_0085a390();
        else
            f_0085e5c0();
    } else {
        c->err->msg_code = 1;
        c->err->fn(param_1);
    }
    i32 t;
    if (*(i32 *)((u8 *)c->f5b4 + 0x10) == 0 && c->f40 == 0)
        t = 0;
    else
        t = one;
    f_00858f80(param_1, t);
    if (c->f44 == 0)
        f_0085afd0(param_1, 0);
    ((void (*)(void *))VTFN(c->f08, 0x18))(param_1);
    ((void (*)(void *))VTFN(c->f5b4, 8))(param_1);
    if (c->f08 != 0 && c->f40 == 0 &&
        *(i32 *)((u8 *)c->f5b4 + 0x10) != 0) {
        i32 n = c->f20;
        if (c->fdc != 0)
            n = n * 3 + 2;
        u8 *o = (u8 *)c->f08;
        *(i32 *)(o + 4) = 0;
        *(i32 *)(o + 8) = c->f540 * n;
        *(i32 *)(o + 0xc) = 0;
        *(i32 *)(o + 0x10) = (c->f6c != 0 ? 1 : 0) + 2;
        *(i32 *)((u8 *)s + 0xc) = *(i32 *)((u8 *)s + 0xc) + 1;
    }
}

// ---------------------------------------------------------------------------
// @ 0x0085d100
void FUN_0085d100(void *param_1) {
    CInfo *c = C(param_1);
    ScanInfo *s = (ScanInfo *)c->f5a4;
    if (s->f08 == 0) {
        if (c->f54 != 0 && c->f88 == 0) {
            if (c->f5c != 0 && c->f6c != 0) {
                c->f5cc = (void *)s->f18;
                s->f08 = 1;
            } else if (c->f64 != 0) {
                c->f5cc = (void *)s->f14;
            } else {
                c->err->msg_code = 0x2d;
                c->err->fn(param_1);
            }
        }
        ((void (*)(void *))VTFN(c->f5c0, 0))(param_1);
        ((void (*)(void *))VTFN(c->f5ac, 8))(param_1);
        if (c->f44 == 0) {
            if (s->f10 == 0)
                ((void (*)(void *))VTFN(c->f5c8, 0))(param_1);
            ((void (*)(void *))VTFN(c->master, 0))(param_1);
            if (c->f54 != 0)
                ((void (*)(void *, i32))VTFN(c->f5cc, 0))(param_1, s->f08);
            i32 sel = -(s->f08 != 0) & 3;
            ((void (*)(void *, i32))VTFN(c->f5b0, 0))(param_1, sel);
            ((void (*)(void *, i32))VTFN(c->f5a8, 0))(param_1, 0);
        }
    } else {
        s->f08 = 0;
        ((void (*)(void *, i32))VTFN(c->f5cc, 0))(param_1, 0);
        ((void (*)(void *, i32))VTFN(c->f5b0, 0))(param_1, 2);
        ((void (*)(void *, i32))VTFN(c->f5a8, 0))(param_1, 2);
    }
    if (c->f08 != 0) {
        u8 *o = (u8 *)c->f08;
        *(i32 *)(o + 0xc) = s->f0c;
        *(u32 *)(o + 0x10) = (u32)((s->f08 != 0) + 1) + (u32)s->f0c;
        if (c->f40 != 0 && *(i32 *)((u8 *)c->f5b4 + 0x14) == 0)
            *(i32 *)(o + 0x10) += (c->f6c != 0 ? 1 : 0) + 1;
    }
}

// ---------------------------------------------------------------------------
// @ 0x0085d260
void FUN_0085d260(void *param_1) {
    CInfo *c = C(param_1);
    ScanInfo *s = (ScanInfo *)c->f5a4;
    if (c->f54 != 0)
        ((void (*)(void *))VTFN(c->f5cc, 8))(param_1);
    s->f0c = s->f0c + 1;
}

// ---------------------------------------------------------------------------
// @ 0x0085d290
void FUN_0085d290(void *param_1) {
    CInfo *c = C(param_1);
    ScanInfo *p = (ScanInfo *)c->mem->alloc_large(param_1, 1, 0x1c);
    c->f5a4 = p;
    p->f00 = (i32)(size_t)&FUN_0085d100;
    p->f04 = (i32)(size_t)&FUN_0085d260;
    p->f08 = 0;
    return FUN_0085cf30(param_1);
}

// ---------------------------------------------------------------------------
// @ 0x0085d2d0
void FUN_0085d2d0(void *param_1) {
    CInfo *c = C(param_1);
    Master *m = c->master;
    m->buf10 = (u8 *)c->mem->alloc_small(param_1, 1, 0x400);
    m->buf14 = (u8 *)c->mem->alloc_small(param_1, 1, 0x400);
    m->buf18 = (u8 *)c->mem->alloc_small(param_1, 1, 0x400);
    m->buf1c = (u8 *)c->mem->alloc_small(param_1, 1, 0x400);
    i32 i3 = 0;
    i32 t_sp = 0x5b6900;
    i32 t_di = 0xff1daf00;
    i32 t_dx = 0xff4d0b80;
    i32 t_cx = 0x2c8d00;
    do {
        *(i32 *)(i3 + (i32)m->buf10) = t_dx >> 16;
        *(i32 *)(i3 + (i32)m->buf14) = t_di >> 16;
        *(i32 *)(i3 + (i32)m->buf18) = t_sp;
        *(i32 *)(i3 + (i32)m->buf1c) = t_cx;
        t_sp -= 0xb6d2;
        t_cx -= 0x581a;
        t_dx += 0x166e9;
        t_di += 0x1c5a2;
        i3 += 4;
    } while (t_cx >= (i32)0xffd4cb1a);
}

// ---------------------------------------------------------------------------
// @ 0x0085d3a0
void FUN_0085d3a0(void *param_1) {
    CInfo *c = C(param_1);
    Master *m = c->master;
    m->f24 = 0;
    m->f2c = c->f74;
}

// ---------------------------------------------------------------------------
// @ 0x0085d3c0
void FUN_0085d3c0(void *param_1, i32 param_2, i32 *param_3, i32 param_4,
                 i32 param_5, i32 *param_6, i32 param_7) {
    (void)param_4;
    CInfo *c = C(param_1);
    Master *m = c->master;
    u32 n;
    if (m->f24 != 0) {
        Fn_00866880((void *)&m->buf20, 0,
                                    (void *)(param_5 + *param_6 * 4), 0, 1, m->f28);
        n = 1;
        m->f24 = 0;
    } else {
        n = 2;
        if ((u32)m->f2c < 2) n = (u32)m->f2c;
        i32 i2 = *param_6;
        if ((u32)(param_7 - i2) < n) n = (u32)(param_7 - i2);
        void *stk[2];
        stk[0] = *(void **)(param_5 + i2 * 4);
        if (n < 2) {
            stk[1] = (void *)&m->buf20;
            m->f24 = 1;
        } else {
            stk[1] = *(void **)(param_5 + 4 + i2 * 4);
        }
        m->fn0c(param_1, param_2, param_3, stk);
    }
    *param_6 += n;
    m->f2c -= n;
    if (m->f24 == 0)
        (*param_3)++;
}

// ---------------------------------------------------------------------------
// @ 0x0085d4c0
void FUN_0085d4c0(void *param_1, i32 *param_2, i32 param_3, void **param_4) {
    CInfo *c = C(param_1);
    Master *m = c->master;
    i32 t10 = (i32)m->buf10;
    i32 t14 = (i32)m->buf14;
    i32 t18 = (i32)m->buf18;
    i32 t1c = (i32)m->buf1c;
    u8 *p17 = *(u8 **)(param_2[0] + param_3 * 4);
    u8 *p15 = *(u8 **)(param_2[1] + param_3 * 4);
    u8 *p12 = *(u8 **)(param_2[2] + param_3 * 4);
    u8 *out = (u8 *)*param_4;
    u32 n = (u32)c->f70 >> 1;
    for (; n != 0; n--) {
        u8 b1 = *p12;
        u8 b2 = *p15;
        p15++;
        p12++;
        i32 v5 = *(i32 *)(t10 + b1 * 4);
        i32 v3 = *(i32 *)(t1c + b2 * 4);
        i32 v7 = *(i32 *)(t18 + b1 * 4);
        u32 u = *p17;
        i32 v6 = *(i32 *)(t14 + b2 * 4);
        out[0] = *(u8 *)(v5 + t1c * 0 + u + (i32)c->table_base);
        (void)v5;
        out[0] = *(u8 *)(v5 + u + (i32)c->table_base);
        v3 = (v3 + v7) >> 16;
        out[1] = *(u8 *)(v3 + u + (i32)c->table_base);
        out[2] = *(u8 *)(u + v6 + (i32)c->table_base);
        u = p17[1];
        out[3] = *(u8 *)(v5 + u + (i32)c->table_base);
        out[4] = *(u8 *)(v3 + u + (i32)c->table_base);
        out[5] = *(u8 *)(u + v6 + (i32)c->table_base);
        p17 += 2;
        out += 6;
    }
    if (*(u8 *)((u8 *)c + 0x70) & 1) {
        i32 v3 = *(i32 *)(t1c + *p15 * 4);
        i32 v7 = *(i32 *)(t18 + *p12 * 4);
        u32 u = *p17;
        i32 v6 = *(i32 *)(t14 + *p15 * 4);
        out[0] = *(u8 *)(*(i32 *)(t10 + *p12 * 4) + u + (i32)c->table_base);
        out[1] = *(u8 *)(u + ((v3 + v7) >> 16) + (i32)c->table_base);
        out[2] = *(u8 *)(u + v6 + (i32)c->table_base);
    }
}

// ---------------------------------------------------------------------------
// @ 0x0085d610
void FUN_0085d610(void *param_1, i32 *param_2, i32 param_3, void **param_4) {
    CInfo *c = C(param_1);
    Master *m = c->master;
    i32 t10 = (i32)m->buf10;
    i32 t14 = (i32)m->buf14;
    i32 t18 = (i32)m->buf18;
    i32 t1c = (i32)m->buf1c;
    u8 **row0 = (u8 **)(param_2[0] + param_3 * 8);
    u8 *p7 = row0[0];
    u8 *p8 = row0[1];
    u8 *p14 = *(u8 **)(param_2[1] + param_3 * 4);
    u8 *p13 = (u8 *)*param_4;
    u8 *p17 = (u8 *)param_4[1];
    u8 *p12 = *(u8 **)(param_2[2] + param_3 * 4);
    u32 n = (u32)c->f70 >> 1;
    for (; n != 0; n--) {
        u8 b2 = *p14;
        p14++;
        i32 v9 = *(i32 *)(t10 + *p12 * 4);
        i32 v18 = *(i32 *)(t1c + b2 * 4);
        i32 v10 = *(i32 *)(t18 + *p12 * 4);
        i32 v11 = *(i32 *)(t14 + b2 * 4);
        u32 u = *p7;
        p13[0] = *(u8 *)(u + v9 + (i32)c->table_base);
        v18 = (v18 + v10) >> 16;
        p13[1] = *(u8 *)(u + v18 + (i32)c->table_base);
        p13[2] = *(u8 *)(u + v11 + (i32)c->table_base);
        u = p7[1];
        p13[3] = *(u8 *)(u + v9 + (i32)c->table_base);
        p13[4] = *(u8 *)(u + v18 + (i32)c->table_base);
        p13[5] = *(u8 *)(u + v11 + (i32)c->table_base);
        u = *p8;
        p17[0] = *(u8 *)(u + v9 + (i32)c->table_base);
        p17[1] = *(u8 *)(u + v18 + (i32)c->table_base);
        p17[2] = *(u8 *)(u + v11 + (i32)c->table_base);
        u = p8[1];
        p7 += 2;
        p8 += 2;
        p17[3] = *(u8 *)(u + v9 + (i32)c->table_base);
        p17[4] = *(u8 *)(u + v18 + (i32)c->table_base);
        p13 += 6;
        p17[5] = *(u8 *)(u + v11 + (i32)c->table_base);
        p17 += 6;
        p12++;
    }
    if (*(u8 *)((u8 *)c + 0x70) & 1) {
        i32 v3 = *(i32 *)(t10 + *p12 * 4);
        i32 v19 = *(i32 *)(t1c + *p14 * 4);
        i32 v6 = *(i32 *)(t18 + *p12 * 4);
        i32 v5 = *(i32 *)(t14 + *p14 * 4);
        u32 u = *p7;
        p13[0] = *(u8 *)(v3 + u + (i32)c->table_base);
        v19 = (v19 + v6) >> 16;
        p13[1] = *(u8 *)(v19 + u + (i32)c->table_base);
        p13[2] = *(u8 *)(u + v5 + (i32)c->table_base);
        u = *p8;
        p17[0] = *(u8 *)(v3 + u + (i32)c->table_base);
        p17[1] = *(u8 *)(v19 + u + (i32)c->table_base);
        p17[2] = *(u8 *)(u + v5 + (i32)c->table_base);
    }
}

// ---------------------------------------------------------------------------
// @ 0x0085d830
void FUN_0085d830(void *param_1) {
    CInfo *c = C(param_1);
    Master *m = (Master *)c->mem->alloc_small(param_1, 1, 0x30);
    c->master = m;
    m->fn00 = (void (*)(void *))&FUN_0085d3a0;
    m->fn08 = 0;
    i32 n = c->f78 * c->f70;
    m->f28 = (u32)n;
    if (c->f538 == 2) {
        m->fn04 = (void (*)(void *))&FUN_0085d3c0;
        m->fn0c = (void (*)(void *, i32, i32 *, void **))&FUN_0085d610;
        m->buf20 = (u8 *)c->mem->alloc_large(param_1, 1, (u32)n);
        return FUN_0085d2d0(param_1);
    }
    m->buf20 = 0;
    m->fn04 = (void (*)(void *))&Fn_0085d480;
    m->fn0c = (void (*)(void *, i32, i32 *, void **))&FUN_0085d4c0;
    return FUN_0085d2d0(param_1);
}

// ---------------------------------------------------------------------------
// @ 0x0085d8b0
i32 FUN_0085d8b0(void *param_1) {
    CInfo *c = C(param_1);
    u8 *v = (u8 *)c->f5bc;
    i32 *cnt = (i32 *)((u8 *)c->ent + 0x5c);
    i32 t = *(i32 *)(v + 0xc);
    *cnt += (t + ((t >> 31) & 7)) >> 3;
    *(i32 *)(v + 0xc) = 0;
    if (((i32 (*)(void *))VTFN(c->ent, 8))(param_1) == 0)
        return 0;
    for (i32 i = 0; i < c->f548; i++)
        *(i32 *)(v + 0x18 + i * 4) = 0;
    *(i32 *)(v + 0x14) = 0;
    *(i32 *)(v + 0x28) = c->f114;
    *(i32 *)(v + 0x10) = 0;
    return 1;
}
