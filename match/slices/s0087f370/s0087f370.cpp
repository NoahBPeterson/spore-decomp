// flags: /O2 /MD /Gy /EHsc /TP /GS-
// Slice s0087f370 - EA::Locale locale tables / formatter (Spore).

// ---------------------------------------------------------------------------
// external helpers (defined elsewhere in the binary)
// ---------------------------------------------------------------------------
extern int         e_compare(const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*); // 0x5e9260
extern void*       e_inc(void*);                    // 0x921580 RBTreeIncrement
extern void*       e_dec(void*);                    // 0x9215c0 RBTreeDecrement
extern void*       e_insert(void*, void*, void*, int); // 0x9216a0 RBTreeInsert
extern void*       e_opnew(int, const char*, int, int, const char*, int); // 0xf473a0
extern void        e_opdel(void*);                  // 0xf47380
extern int         e_fmt(int, const wchar_t*, wchar_t*, int, wchar_t); // 0x87d620
extern char        e_fieldparse(const wchar_t*, void*, int*, void*);   // 0x87d6d0
extern char        e_mkstr(const wchar_t*, const wchar_t*);            // 0x87da10
extern void*       e_findshort(const wchar_t*, const wchar_t*);        // 0x87dc40
extern unsigned    e_mkloc(int, int);                                  // 0x87d9a0
extern void*       e_f210(void*, const wchar_t*);                      // 0x87f210
extern void*       e_edd0(void*, int*);                                // 0x87edd0
extern void*       e_ee50(void*, int*);                                // 0x87ee50
extern void        e_fab0(int);                                        // 0x87fab0
extern void        e_repchar(int, int);                                // 0x68c8c0
extern void        e_fixstr(void*);                                    // 0x6962a0
extern void        e_dealloc(void*);                                   // 0x57cb80
extern void        e_vecdtor(void*, int, int, void*);                  // 0x401960

extern "C" char* __cdecl setlocale(int, const char*);
extern "C" int   __cdecl _setmbcp(int);
extern "C" int   __cdecl iswctype(int, int);

// ---------------------------------------------------------------------------
// fixed string / formatter buffer  (begin/cur/cap + inline buffer at +0x14)
// ---------------------------------------------------------------------------
template<int N>
struct Loc {
    wchar_t* f00;
    wchar_t* f04;
    wchar_t* f08;
    int      f0C;
    wchar_t* f10;
    wchar_t  buf[N];

    void AppendElement(const wchar_t* b, const wchar_t* e);   // 0x68cc10
    void append(const wchar_t* b, const wchar_t* e);          // 0x42f9d0
    void Assign(const wchar_t** key);                         // 0x87e0d0
    void FUN_0087fab0(int c);                                 // 0x87fab0
    void RepeatChar(int n, int c);                            // 0x68c8c0 (thiscall: ecx = formatter)

    void Release() {
        int d = (int)((char*)f08 - (char*)f00);
        if ((d & -2) > 2 && f00 != 0 && f00 != f10)
            e_opdel(f00);
    }

    void InitCap(int n) {
        wchar_t* p = buf;
        f10 = p;
        f04 = p;
        f00 = p;
        f08 = p + n;
        *p = 0;
    }

    // @ 0x0087f550
    void* FUN_0087f550(const Loc* src) {
        if (this != src) {
            if (f00 != f04) {
                *f00 = 0;
                f04 = f00;
            }
            append(src->f00, src->f04);
        }
        return this;
    }
};
template struct Loc<16>;
template struct Loc<512>;

// ---------------------------------------------------------------------------
// @ 0x0087f4f0 : construct Loc<16> + copy six trailing ints
// ---------------------------------------------------------------------------
struct Loc16Ex {
    Loc<16> s;              // +0
    int f34, f38, f3c, f40, f44, f48;
    void* FUN_0087f4f0(Loc16Ex* src);
};
// @ 0x0087f4f0
void* Loc16Ex::FUN_0087f4f0(Loc16Ex* src) {
    wchar_t* p = s.buf;
    s.f10 = p;
    s.f08 = p + 16;
    s.f04 = p;
    s.f00 = p;
    *p = 0;
    s.AppendElement(src->s.f00, src->s.f04);
    f34 = src->f34;
    f38 = src->f38;
    f3c = src->f3c;
    f40 = src->f40;
    f44 = src->f44;
    f48 = src->f48;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x0087f580 : construct Loc<16>@0 and Loc<512>@0x34 from two input strings
// ---------------------------------------------------------------------------
struct Loc16x512 {
    Loc<16>  first;         // +0
    Loc<512> second;        // +0x34
    void* FUN_0087f580(const wchar_t** a, const wchar_t** b);
};
// @ 0x0087f580
void* Loc16x512::FUN_0087f580(const wchar_t** a, const wchar_t** b) {
    first.InitCap(16);
    first.AppendElement(a[0], a[1]);
    second.InitCap(512);
    second.append(b[0], b[1]);
    return this;
}

// ---------------------------------------------------------------------------
// rbtree of fixed_string<16> -> fixed_string<512>
// ---------------------------------------------------------------------------
struct RbtNode {
    RbtNode* ch0;          // +0
    RbtNode* ch1;          // +4
    int      color;        // +8
    int      padC;         // +0xC
    Loc<16>  key;          // +0x10
    Loc<512> val;          // +0x44
};

struct RbtIter { RbtNode* node; };

struct LocaleTree {
    int   f00;             // +0
    void* sent;            // +4   (anchor; its address is the end sentinel)
    void* f08;             // +8
    void* root;            // +0xC
    int   f10;             // +0x10
    int   count;           // +0x14

    void  Clear(RbtNode* n);                                       // 0087fe10
    void** InsertNew(void** out, RbtNode* hint, const wchar_t** key, char flag);  // 0087fb40
    void  FindOrInsert(void** out, const wchar_t** key, unsigned flag);         // 0087fbe0
    void* AddOrFind(void** out, RbtNode* hint, const wchar_t** key, char flag); // 00880040
    RbtIter find(const Loc<16>* key);                                          // 0x5e96f0
};

extern LocaleTree g_tree_0154919c;
extern char       g_end_015491a0;
extern wchar_t*   g_lb_016510b8;
extern wchar_t*   g_le_016510bc;
extern const wchar_t* g_short_01548fb8[];

// @ 0x0087fe10 : recursive node destructor (member so `this` is threaded through)
void LocaleTree::Clear(RbtNode* n) {
    while (n != 0) {
        Clear(n->ch0);
        RbtNode* next = n->ch1;
        n->val.Release();
        n->key.Release();
        e_opdel(n);
        n = next;
    }
}

// @ 0x0087fb40 : insert a fresh node
// Returns the out pointer: retail reloads it into eax for the final store (mov eax,[esp+0x24];
// mov [eax],edi) and leaves it there, and equiv compares eax because the original writes it.
void** LocaleTree::InsertNew(void** out, RbtNode* hint, const wchar_t** key, char flag) {
    int cmp = 0;
    if (flag == 0 && hint != (RbtNode*)((char*)this + 4)) {
        if (e_compare(key[0], key[1], hint->key.f00, hint->key.f04) >= 0)
            cmp = 1;
    }
    RbtNode* n = (RbtNode*)e_opnew(0x458, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if ((char*)n + 0x10 != 0)
        n->key.Assign(key);
    e_insert(n, hint, (char*)this + 4, cmp);
    count++;
    *out = n;
    return out;
}

// @ 0x0087fbe0 : find position, inserting when needed
void LocaleTree::FindOrInsert(void** out, const wchar_t** key, unsigned flag) {
    (void)flag;
    RbtNode* bEnd = (RbtNode*)((char*)this + 4);
    RbtNode* puVar8 = bEnd;
    bool bVar9 = true;
    RbtNode* rootNode = (RbtNode*)root;
    if (rootNode != 0) {
        int local_8 = (int)((char*)key[1] - (char*)key[0]) >> 1;
        RbtNode* puVar5 = rootNode;
        do {
            puVar8 = puVar5;
            const unsigned short* puVar6 = (const unsigned short*)puVar8->key.f00;
            int local_c = (int)((char*)puVar8->key.f04 - (char*)puVar8->key.f00) >> 1;
            int m = local_8 <= local_c ? local_8 : local_c;
            const unsigned short* puVar3 = (const unsigned short*)key[0];
            unsigned uVar4 = 0;
            int iVar7 = m;
            for (; iVar7 != 0; --iVar7) {
                if (*puVar3 != *puVar6) {
                    uVar4 = (-(unsigned)(*puVar3 < *puVar6) & 0xfffffffe) + 1;
                    if (uVar4 != 0)
                        goto LAB;
                    break;
                }
                ++puVar3;
                ++puVar6;
            }
            uVar4 = (local_8 < local_c) ? 0xffffffffu : (unsigned)(local_c < local_8);
        LAB:
            bVar9 = (int)uVar4 < 0;
            puVar5 = bVar9 ? (RbtNode*)puVar8->ch1 : (RbtNode*)puVar8->ch0;
        } while (puVar5 != 0);
    }
    RbtNode* puVar5b = puVar8;
    if (bVar9) {
        if (puVar8 == (RbtNode*)f08)
            goto LAB2;
        puVar5b = (RbtNode*)e_dec(puVar8);
    }
    if (e_compare(puVar5b->key.f00, puVar5b->key.f04, key[0], key[1]) >= 0) {
        *out = puVar5b;
        ((char*)out)[4] = 0;
        return;
    }
LAB2:
    {
        void* tmp;
        InsertNew(&tmp, puVar8, key, 0);
        *out = tmp;
        ((char*)out)[4] = 1;
    }
}

// @ 0x00880040 : lower_bound / insert
void* LocaleTree::AddOrFind(void** out, RbtNode* hint, const wchar_t** key, char flag) {
    (void)flag;
    RbtNode* bEnd = (RbtNode*)((char*)this + 4);
    RbtNode* e = (RbtNode*)sent;
    if (hint == e || hint == bEnd) {
        if (count != 0 &&
            e_compare(e->key.f00, e->key.f04, key[0], key[1]) < 0) {
            InsertNew(out, e, key, 0);
            return out;
        }
        void* local_8[2];
        FindOrInsert(local_8, key, (unsigned)(size_t)key & 0xffffff00u);
        *out = local_8[0];
        return out;
    }
    RbtNode* nxt = (RbtNode*)e_inc(hint);
    if (e_compare(hint->key.f00, hint->key.f04, key[0], key[1]) < 0 &&
        e_compare(key[0], key[1], nxt->key.f00, nxt->key.f04) < 0) {
        int f = hint->ch0 != 0;
        RbtNode* ins = f ? nxt : hint;
        InsertNew(out, ins, key, (char)f);
        return out;
    }
    void* local_8[2];
    FindOrInsert(local_8, key, (unsigned)(size_t)key & 0xffffff00u);
    *out = local_8[0];
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x0087f370 : EA::Locale::LocaleFormatter::UpdateFormatElements
// ---------------------------------------------------------------------------
struct FmtElem {
    Loc<16> s;             // +0
    int f34;
    int f38;
    int f3c;
    int f40;
    int f44;
    int f48;
};

namespace EA { namespace Locale {
char LocaleFormatter_UpdateFormatElements(FmtElem* dst, int count, const wchar_t* str) {
    if (str == 0)
        return 1;
    FmtElem arr[16];
    for (int i = 0; i < 16; ++i)
        arr[i].s.InitCap(16);
    int n = 0x10;
    int local4 = 0;
    if (!e_fieldparse(str, arr, &n, &local4)) {
        for (int i = 15; i >= 0; --i)
            arr[i].s.Release();
        return 0;
    }
    if (n > 0) {
        FmtElem* e = arr;
        int cnt = n;
        do {
            if (count > 0) {
                int k = e->f38;
                FmtElem* d = dst;
                int m = count;
                do {
                    if (d->f38 == k) {
                        d->f3c = e->f3c;
                        d->f40 = e->f40;
                        d->f34 = (d->f34 & 0x38) | e->f34;
                    }
                    d = (FmtElem*)((char*)d + 0x4c);
                    --m;
                } while (m != 0);
            }
            e = (FmtElem*)((char*)e + 0x4c);
            --cnt;
        } while (cnt != 0);
        n = 0;
    }
    for (int i = 15; i >= 0; --i)
        arr[i].s.Release();
    return 1;
}
}}

// ---------------------------------------------------------------------------
// @ 0x0087f5e0 : EA::Locale::IsLocaleAvailable
// ---------------------------------------------------------------------------
namespace EA { namespace Locale {
bool IsLocaleAvailable(int* param_1) {
    Loc<16> la;
    Loc<16> lb;
    e_f210(&la, (const wchar_t*)*param_1);
    e_edd0(&lb, (int*)&la);
    RbtIter it = g_tree_0154919c.find(&lb);
    bool found = (it.node == (RbtNode*)&g_end_015491a0);
    lb.Release();
    if (found) {
        la.Release();
        return false;
    }
    void* pc = e_ee50(&lb, (int*)&la);
    int i3 = ((int*)pc)[0];
    int i1 = ((int*)pc)[1];
    lb.Release();
    if (i3 != i1) {
        la.Release();
        return true;
    }
    la.Release();
    return false;
}
}}

// ---------------------------------------------------------------------------
// @ 0x0087f700 : EA::Locale::`anonymous_namespace'::CRTFindAliasDataByLocaleId
// ---------------------------------------------------------------------------
namespace EA { namespace Locale { namespace {
int CRTFindAliasDataByLocaleId(int* param_1) {
    Loc<16> la;
    wchar_t buf[128];
    e_f210(&la, (const wchar_t*)*param_1);
    int len = (int)(param_1[1] - param_1[0]) >> 1;
    if (len == 2) {
        const wchar_t** p = g_short_01548fb8;
        while (*p != 0) {
            if (e_fmt(5, *p, buf, 0x80, 0x5e) > 0 && e_mkstr(buf, (const wchar_t*)param_1)) {
                e_fmt(0, *p, buf, 0x80, 0x5e);
                Loc<16> lx;
                lx.InitCap(16);
                const wchar_t* end = buf;
                while (*end != 0) ++end;
                lx.AppendElement(buf, end);
                int r = CRTFindAliasDataByLocaleId((int*)&lx);
                lx.Release();
                la.Release();
                return r;
            }
            ++p;
        }
    } else if (len > 2) {
        void* f = e_findshort((const wchar_t*)g_short_01548fb8, (const wchar_t*)param_1);
        if (f != 0 && e_fmt(1, (const wchar_t*)f, buf, 0x80, 0x5e) > 0 &&
            iswctype((int)buf[0], 0x103) != 0) {
            Loc<16> lxx;
            lxx.InitCap(16);
            e_fixstr(&lxx);
            void* r = e_findshort((const wchar_t*)g_short_01548fb8, (const wchar_t*)&lxx);
            lxx.Release();
            la.Release();
            return (int)r;
        }
    }
    la.Release();
    return 0;
}
}}}

// ---------------------------------------------------------------------------
// @ 0x0087f900 : FUN_0087f900 (install locale by alias)
// ---------------------------------------------------------------------------
extern void e_wfbappend(void* self, const wchar_t* b, const wchar_t* e); // 0x42f9d0

unsigned FUN_0087f900(int* param_1) {
    int* ps = (int*)EA::Locale::CRTFindAliasDataByLocaleId(param_1);
    if (ps == 0)
        return 0;
    char local_200[256];
    char local_100[256];
    char local_280[128];
    unsigned u3 = (unsigned)e_fmt(2, (const wchar_t*)ps, (wchar_t*)local_200, 0x80, 0x5e);
    unsigned u4 = (unsigned)e_fmt(3, (const wchar_t*)ps, (wchar_t*)local_100, 0x80, 0x5e);
    if ((int)u3 >= 0x81 || (int)u4 >= 0x81)
        return 0;
    int j = 0;
    for (unsigned i = 0; i < u3; ++i)
        local_280[j++] = local_200[i * 2];
    local_280[j++] = '_';
    for (unsigned i = 0; i < u4; ++i)
        local_280[j++] = local_100[i * 2];
    local_280[j] = 0;
    if (setlocale(1, local_280) == 0)
        goto fail;
    if (setlocale(3, local_280) == 0)
        goto fail;
    if (setlocale(4, local_280) == 0)
        goto fail;
    if (setlocale(5, local_280) == 0)
        goto fail;
    if (g_lb_016510b8 != (wchar_t*)ps) {
        if (g_lb_016510b8 != g_le_016510bc) {
            *g_lb_016510b8 = 0;
            g_le_016510bc = g_lb_016510b8;
        }
        const wchar_t* e = (const wchar_t*)ps;
        while (*e != 0)
            ++e;
        e_wfbappend((void*)0x16510b8, (const wchar_t*)ps, e);
    }
    _setmbcp(-4);
    return 1;
fail:
    setlocale(0, "");
    if (g_lb_016510b8 != g_le_016510bc) {
        *g_lb_016510b8 = 0;
        g_le_016510bc = g_lb_016510b8;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x0087fd10 : FUN_0087fd10 (make locale available / compare)
// ---------------------------------------------------------------------------
typedef unsigned short shrt;
unsigned FUN_0087fd10(int* param_1, int* param_2, char param_3) {
    if (param_3 == 0)
        return e_mkloc((int)param_1, (int)param_2);
    int* a = (int*)EA::Locale::CRTFindAliasDataByLocaleId(param_1);
    int* b = (int*)EA::Locale::CRTFindAliasDataByLocaleId(param_2);
    if (a == 0 || b == 0)
        return 0;
    shrt local_200[128];
    shrt local_100[128];
    if ((int)e_fmt(0, (const wchar_t*)a, (wchar_t*)local_100, 0x80, 0x5e) < 1)
        return 0;
    if ((int)e_fmt(0, (const wchar_t*)b, (wchar_t*)local_200, 0x80, 0x5e) < 1)
        return 0;
    shrt* puVar5 = local_100;
    shrt* puVar6 = local_200;
    int bVar7;
    for (;;) {
        shrt uVar1 = *puVar5;
        bVar7 = uVar1 < *puVar6;
        if (uVar1 != *puVar6)
            break;
        if (uVar1 == 0)
            return 1;
        uVar1 = puVar5[1];
        bVar7 = uVar1 < puVar6[1];
        if (uVar1 != puVar6[1])
            break;
        puVar5 += 2;
        puVar6 += 2;
        if (uVar1 == 0)
            return 1;
    }
    int iVar2 = (1 - (unsigned)bVar7) - (unsigned)(bVar7 != 0);
    return (unsigned)(iVar2 & 0xffffff00) | (unsigned)(iVar2 == 0);
}

// ---------------------------------------------------------------------------
// @ 0x0087fe90 : FUN_0087fe90
// ---------------------------------------------------------------------------
Loc<16>* FUN_0087fe90(Loc<16>* param_1, Loc<16>* param_2, Loc<16>* param_3) {
    Loc<16> local;
    local.InitCap(16);
    local.AppendElement(param_2->f00, param_2->f04);
    if (((int)((char*)param_2->f04 - (char*)param_2->f00) & -2) == 10) {
        param_1->InitCap(16);
        param_1->AppendElement(local.f00, local.f04);
    } else {
        local.FUN_0087fab0(0x2d);
        local.AppendElement(param_3->f00, param_3->f04);
        param_1->f10 = param_1->buf;
        param_1->f08 = param_1->buf + 16;
        param_1->f04 = param_1->buf;
        param_1->f00 = param_1->buf;
        param_1->buf[0] = 0;
        param_1->AppendElement(local.f00, local.f04);
    }
    local.Release();
    return param_1;
}

// ---------------------------------------------------------------------------
// @ 0x0087ff90 : FUN_0087ff90
// ---------------------------------------------------------------------------
struct NumFmt {
    Loc<16> s;   // +0x00
    int  f34;    // +0x34
    int  f38;    // +0x38
    int  f3c;    // +0x3c
};
char FUN_0087ff90(Loc<16>* param_1, NumFmt* param_2) {
    wchar_t* psVar5 = param_2->s.f00;
    wchar_t* psVar1 = (wchar_t*)((char*)psVar5 + ((int)((char*)param_2->s.f04 - (char*)psVar5) >> 1) * 2);
    if (psVar5 == 0)
        return 0;
    if (param_2->f3c < 0) {
        param_1->AppendElement(psVar5, psVar1);
        return 1;
    }
    if (*psVar5 == 0x2d) {
        param_1->RepeatChar(1, 0x2d);
        psVar5 += 1;
    }
    unsigned uVar2 = (unsigned)param_2->f3c;
    int iVar4 = (int)uVar2 >> 31;
    unsigned uVar3 = (unsigned)((int)((char*)psVar1 - (char*)psVar5) >> 1);
    wchar_t* end;
    if ((iVar4 < 0) ||
        ((iVar4 == 0 && uVar2 <= uVar3) || ((param_2->f34 & 2) == 0))) {
        end = psVar1;
        if (iVar4 == 0 && uVar2 < uVar3)
            end = psVar5 + uVar2;
    } else {
        param_1->RepeatChar((int)(uVar2 - uVar3), 0x30);
        end = psVar1;
    }
    param_1->AppendElement(psVar5, end);
    return 1;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

