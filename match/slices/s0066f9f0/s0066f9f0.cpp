// Slice s0066f9f0: SP::cSPUIFeedListItem card/view helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

typedef uint16_t wchar16;

struct VObj { void** vt; };
#define VS(p, n) (((VObj*)(p))->vt[(n) / 4])

// ---- calling-convention shorthands used at every call site -----------------
typedef void             (__thiscall *Fn_v)(void*);
typedef void             (__thiscall *Fn_vp)(void*, void*);
typedef void             (__thiscall *Fn_v2i)(void*, int, int);
typedef void             (__thiscall *Fn_vff)(void*, float, float);
typedef void             (__thiscall *Fn_vuu)(void*, unsigned int, unsigned int);
typedef char             (__thiscall *Fn_cuuk)(void*, unsigned int, unsigned int, void*);
typedef char             (__thiscall *Fn_c)(void*);
typedef char             (__thiscall *Fn_cuu)(void*, unsigned int, unsigned int);
typedef void*            (__thiscall *Fn_p)(void*);
typedef void*            (__thiscall *Fn_pi)(void*, int);
typedef float*           (__thiscall *Fn_f)(void*);
typedef unsigned __int64 (__thiscall *Fn_u)(void*);
typedef const unsigned int* (__thiscall *Fn_pu)(void*);
typedef const unsigned __int64* (__thiscall *Fn_p64)(void*);
typedef char             (__thiscall *Fn_c6)(void*, void*, void*, int, int, int, int);
typedef void             (__thiscall *Fn_assign)(void*, const wchar16*, const wchar16*);
typedef void*            (__thiscall *Fn_app)(void*, const wchar16*);
typedef char             (__cdecl   *Fn_chuu)(unsigned int, unsigned int);

// ---- callees (convention spelled out; cast at each call site) --------------
void FUN_0067cb30();   // 0x0067cb30 SP::cPollinator::Get() __cdecl, 0 args -> cPollinator*
void FUN_0067dcd0();   // 0x0067dcd0 EA::ResourceMan::GetManager() __cdecl, 0 args -> void*
void FUN_0067dd30();   // 0x0067dd30 SP::ConfigManager() __cdecl, 0 args -> void*
void FUN_00607a60();   // 0x00607a60 SP::Pollen::AuthManager() __cdecl, 0 args -> void*
void FUN_005507a0();   // 0x005507a0 ecx=meta, __thiscall 0 stack args -> const u64* (GetAssetID #1)
void FUN_00550800();   // 0x00550800 ecx=meta, __thiscall 0 stack args -> const u64* (GetAssetID #2)
void FUN_00550820();   // 0x00550820 ecx=meta, __thiscall 0 stack args -> const u64* (GetAssetID #3)
void FUN_005508a0();   // 0x005508a0 ecx=meta, __thiscall 0 stack args -> u64 (edx:eax)
void FUN_00550880();   // 0x00550880 ecx=meta, __thiscall 0 stack args -> wchar16* (display text)
void FUN_0054e460();   // 0x0054e460 ecx=dir, __thiscall (lo, hi, Key*) -> char
void FUN_0054e740();   // 0x0054e740 ecx=dir, __thiscall (lo, hi) -> char (IsPending)
void FUN_00551b60();   // 0x00551b60 ecx=auth, __thiscall (lo, hi) (SetID #1)
void FUN_00551b80();   // 0x00551b80 ecx=auth, __thiscall (lo, hi) (SetID #2)
void FUN_00571db0();   // 0x00571db0 EA::Messaging::RemoveHandler __cdecl (h, b, c, d, e), 5 args
void FUN_00423650();   // 0x00423650 ecx=basic_string<wchar16>, __thiscall (first, last) (assign)
void FUN_005c3d90();   // 0x005c3d90 ecx=basic_string<wchar16>, __thiscall (text) -> this (append)
void FUN_00472f50();   // 0x00472f50 __cdecl (out, name, fmt, lo, hi) (formatted string build)
void FUN_006b5770();   // 0x006b5770 ecx=SP::cString, __thiscall (u, u, wchar_t const*)
void FUN_006b55c0();   // 0x006b55c0 ecx=SP::cString, __thiscall 0 args -> wchar16* (GetText)
void FUN_006b5240();   // 0x006b5240 ecx=SP::cString, __thiscall 0 args (dtor)
void FUN_00806e40();   // 0x00806e40 AutoSizeWindowForText __cdecl (win, 0, 0)
void FUN_00806ca0();   // 0x00806ca0 __cdecl (win, x, y)
void FUN_00610460();   // 0x00610460 ecx=cPollinator, __thiscall (arg) (PostEatFeed)
void FUN_00610780();   // 0x00610780 ecx=cPollinator, __thiscall (arg) (SubscribeToFeed)
void FUN_004786e0();   // 0x004786e0 ecx=&vector, __thiscall (end, src) (grow-append)
void FUN_00f47380();   // 0x00f47380 operator delete __cdecl (p)
void FUN_0066f150();   // 0x0066f150 __cdecl (lo, hi) -> char

extern int gVt700_0, gVt700_1, gVt700_2, gVt700_3, gVt700_4, gVt700_5;
extern int gStr700A, gStr700B;

// -----------------------------------------------------------------------------
// shared layout of the object every function in this slice operates on
// -----------------------------------------------------------------------------
struct Str16 {                 // eastl::basic_string<wchar16> header (0x10)
    wchar16* mpBegin;          // +0x00
    wchar16* mpEnd;            // +0x04
    wchar16* mpCapacity;       // +0x08
    void*    mpPad0c;          // +0x0c
};

struct Str8 {                  // eastl::basic_string<char> header (0x0c)
    char* mpBegin;             // +0x00
    char* mpEnd;               // +0x04
    char* mpCapacity;          // +0x08
};

struct ResKey {                // EA::ResourceMan::Key (0x0c)
    uint32_t mBase;            // +0x00
    uint32_t mMid;             // +0x04
    uint32_t mId;              // +0x08
};

struct FeedRow {               // one card row (0x28)
    uint32_t mIdLo;            // +0x00
    uint32_t mIdHi;            // +0x04
    uint32_t mKeyLo;           // +0x08
    uint32_t mKeyHi;           // +0x0c
    Str16    mText;            // +0x10
    uint8_t  mFlag;            // +0x20
    uint8_t  mPad21[3];        // +0x21
    uint32_t mState;           // +0x24
};

struct Owner {
    void*    mpVt00;           // +0x00  vtable slice 0
    void*    mpVt04;           // +0x04  vtable slice 1
    void*    mpVt08;           // +0x08  vtable slice 2
    void*    mpVt0c;           // +0x0c  vtable slice 3
    void*    mPad10;           // +0x10
    void*    mpAuth;           // +0x14  IRefObj* (EA auth/metadata object)
    FeedRow  mRow[2];          // +0x18 / +0x40
    uint32_t mField68;         // +0x68
    uint32_t mPad6c;           // +0x6c
    uint8_t  mActive70;        // +0x70
    uint8_t  mPad71[3];        // +0x71
    void*    mpWin74;          // +0x74
    void*    mpWin78;          // +0x78
    void*    mpWin7c;          // +0x7c
    void*    mpWin80;          // +0x80
    void*    mpWin84;          // +0x84
    void*    mpCard[6][2];     // +0x88 (mpCard[k][i] = 0x88 + 8k + 4i)
    void*    mpHandlerB8;      // +0xb8
    uint32_t mBc;              // +0xbc
    uint32_t mC0;              // +0xc0
    uint32_t mC4;              // +0xc4
    uint32_t mC8;              // +0xc8
};

struct FeedEntry {             // SP Pollinator feed entry (0x70)
    uint8_t  mPad00[0x10];     // +0x00
    uint32_t mKeyLo;           // +0x10
    uint32_t mKeyHi;           // +0x14
    uint8_t  mPad18[0x50];     // +0x18
    int      mKind;            // +0x68  == 2 for asset feeds
    uint8_t  mPad6c[4];        // +0x6c
};

struct CS64Vec {               // eastl small vector of u64 (3 inline slots)
    unsigned __int64* mpBegin; // +0x00
    unsigned __int64* mpEnd;   // +0x04
    unsigned __int64* mpCapacity; // +0x08
};

// -----------------------------------------------------------------------------
// @ 0x006700d0
// -----------------------------------------------------------------------------
// constructor (already recorded nonmatching)
void __fastcall FUN_006700d0(void* self) {
    uint32_t* p = (uint32_t*)self;
    p[1] = (uint32_t)&gVt700_1;
    p[3] = (uint32_t)&gVt700_3;
    uint32_t z = 0;
    p[4] = z;
    p[0] = (uint32_t)&gVt700_0;
    p[1] = (uint32_t)&gVt700_4;
    p[2] = (uint32_t)&gVt700_2;
    p[3] = (uint32_t)&gVt700_5;
    p[5] = z;
    uint32_t m1 = 0xffffffff;
    p[6] = m1; p[7] = m1; p[8] = m1; p[9] = m1;
    p[0xc] = (uint32_t)&gStr700B;
    uint32_t s = (uint32_t)&gStr700A;
    p[10] = s; p[0xb] = s;
    p[0x10] = m1; p[0x11] = m1; p[0x12] = m1; p[0x13] = m1;
    *(uint8_t*)(p + 0xe) = 1;
    p[0x16] = z;
    p[0x14] = s; p[0x15] = s;
    p[0x16] = p[0x14] + 2;
    *(uint8_t*)(p + 0x18) = 1;
    p[0x1a] = z; p[0x1b] = z;
    *(uint8_t*)(p + 0x1c) = 0;
    p[0x1d] = z; p[0x1e] = z; p[0x1f] = z;
    p[0x20] = z; p[0x21] = z; p[0x22] = z; p[0x23] = z;
    p[0x24] = z; p[0x25] = z; p[0x26] = z; p[0x27] = z;
    p[0x28] = z; p[0x29] = z; p[0x2a] = z; p[0x2b] = z;
    p[0x2c] = z; p[0x2d] = z; p[0x2e] = z; p[0x2f] = z;
    p[0x30] = z; p[0x31] = z; p[0x32] = z;
}

// -----------------------------------------------------------------------------
// @ 0x0066fee0
// -----------------------------------------------------------------------------
// destructor: restore the vtables, drop the message handler, release every
// window/card reference, free the two row texts and release the auth object.
void __fastcall FUN_0066fee0(void* self) {
    Owner* o = (Owner*)self;
    o->mpVt00 = (void*)0x1400888;
    o->mpVt04 = (void*)0x1400880;
    o->mpVt08 = (void*)0x1400874;
    o->mpVt0c = (void*)0x1400864;
    if (o->mpHandlerB8 != 0) {
        void* h = o->mpHandlerB8;
        o->mpHandlerB8 = 0;
        ((void (__cdecl*)(void*, unsigned int, unsigned int, unsigned int, unsigned int))FUN_00571db0)
            (h, o->mBc, o->mC0, o->mC4, o->mC8);
    }
    for (int k = 5; k >= 0; --k) {
        for (int i = 1; i >= 0; --i) {
            void* c = o->mpCard[k][i];
            if (c) ((Fn_v)VS(c, 0x04))(c);
        }
    }
    if (o->mpWin84) ((Fn_v)VS(o->mpWin84, 0x04))(o->mpWin84);
    if (o->mpWin80) ((Fn_v)VS(o->mpWin80, 0x04))(o->mpWin80);
    if (o->mpWin7c) ((Fn_v)VS(o->mpWin7c, 0x04))(o->mpWin7c);
    if (o->mpWin78) ((Fn_v)VS(o->mpWin78, 0x04))(o->mpWin78);
    if (o->mpWin74) ((Fn_v)VS(o->mpWin74, 0x04))(o->mpWin74);
    for (int i = 1; i >= 0; --i) {
        Str16* t = &o->mRow[i].mText;
        int n = (int)((char*)t->mpCapacity - (char*)t->mpBegin) & ~1;
        if (n > 2 && t->mpBegin != 0)
            ((void (__cdecl*)(void*))FUN_00f47380)(t->mpBegin);
    }
    if (o->mpAuth != 0) ((Fn_v)VS(o->mpAuth, 0x04))(o->mpAuth);
    o->mpVt0c = (void*)0x13ec458;
    o->mpVt04 = (void*)0x13eb394;
    o->mpVt00 = (void*)0x13eb938;
}

// -----------------------------------------------------------------------------
// @ 0x00670200
// -----------------------------------------------------------------------------
// reset: blank both rows, release the windows/cards, drop the handler and the
// auth object (does not touch the vtables).
void __fastcall FUN_00670200(void* self) {
    Owner* o = (Owner*)self;
    uint32_t m1 = 0xffffffffu;
    o->mRow[0].mIdLo = m1; o->mRow[0].mIdHi = m1;
    o->mRow[0].mKeyLo = m1; o->mRow[0].mKeyHi = m1;
    ((Fn_assign)FUN_00423650)(&o->mRow[0].mText, (const wchar16*)0x1667bac, (const wchar16*)0x1667bac);
    o->mRow[0].mFlag = 1;
    o->mRow[1].mIdLo = m1; o->mRow[1].mIdHi = m1;
    o->mRow[1].mKeyLo = m1; o->mRow[1].mKeyHi = m1;
    ((Fn_assign)FUN_00423650)(&o->mRow[1].mText, (const wchar16*)0x1667bac, (const wchar16*)0x1667bac);
    o->mRow[1].mFlag = 1;
    o->mField68 = 0;
    o->mActive70 = 0;
    void* w;
    if ((w = o->mpWin74) != 0) { o->mpWin74 = 0; ((Fn_v)VS(w, 0x04))(w); }
    if ((w = o->mpWin78) != 0) { o->mpWin78 = 0; ((Fn_v)VS(w, 0x04))(w); }
    if ((w = o->mpWin7c) != 0) { o->mpWin7c = 0; ((Fn_v)VS(w, 0x04))(w); }
    for (int i = 0; i < 2; ++i) {
        for (int k = 0; k < 6; ++k) {
            void* c = o->mpCard[k][i];
            if (c) { o->mpCard[k][i] = 0; ((Fn_v)VS(c, 0x04))(c); }
        }
    }
    if (o->mpAuth != 0 && o->mpHandlerB8 != 0) {
        void* h = o->mpHandlerB8;
        o->mpHandlerB8 = 0;
        ((void (__cdecl*)(void*, unsigned int, unsigned int, unsigned int, unsigned int))FUN_00571db0)
            (h, o->mBc, o->mC0, o->mC4, o->mC8);
    }
    if (o->mpAuth != 0) {
        void* a = o->mpAuth;
        o->mpAuth = 0;
        ((Fn_v)VS(a, 0x04))(a);
    }
}

// -----------------------------------------------------------------------------
// @ 0x00670370
// -----------------------------------------------------------------------------
// resolve (lo, hi) into one FeedRow: a small literal id keeps the id and gets a
// cString-built label, everything else is looked up through the asset
// directory / resource manager.
char __fastcall FUN_00670370(void* self, void* edx, uint32_t lo, uint32_t hi, FeedRow* out) {
    (void)self; (void)edx;
    uint32_t t = hi - (uint32_t)(lo == 0u);   // high word of (x - 1)
    int simple = (t == 0u && (lo - 1u) <= 0xfffffffdu);

    if (simple) {
        out->mIdLo  = lo;
        out->mIdHi  = hi;
        out->mKeyLo = 0xffffffffu;
        out->mKeyHi = 0xffffffffu;
        uint8_t cs[0x14];
        ((void (__thiscall*)(void*, unsigned int, unsigned int, void*))FUN_006b5770)
            (cs, 0x4dc2f94u, 1u, 0);
        wchar16* txt = ((wchar16* (__thiscall*)(void*))FUN_006b55c0)(cs);
        wchar16* e = txt;
        while (*e != 0) ++e;
        ((Fn_assign)FUN_00423650)(&out->mText, txt, e);
        out->mFlag = 0;
        ((void (__thiscall*)(void*))FUN_006b5240)(cs);
        return 1;
    }

    ResKey key;
    key.mBase = 0; key.mMid = 0; key.mId = 0;
    void* dir = ((void* (__cdecl*)())FUN_0067cb30)();
    dir = *(void**)((char*)dir + 0x58);
    if (!((Fn_cuuk)FUN_0054e460)(dir, lo, hi, &key)) return 0;

    ResKey desc;
    desc.mBase = key.mBase;
    desc.mMid  = 0x30bdee3u;
    desc.mId   = key.mId;

    void* res = 0;
    void* mgr = ((void* (__cdecl*)())FUN_0067dcd0)();
    char found = ((Fn_c6)VS(mgr, 0x0c))(mgr, &desc, &res, 0, 0, 0, 0);

    char ret = 0;
    if (found) {
        if (res == 0) return 0;
        void* meta = ((Fn_pi)VS(res, 0x0c))(res, 0x30bdee3);
        if (meta != 0) {
            ret = 1;
            const uint32_t* id = ((Fn_pu)FUN_005507a0)(meta);
            out->mIdLo = id[0];
            out->mIdHi = id[1];
            unsigned __int64 k = ((Fn_u)FUN_005508a0)(meta);
            out->mKeyLo = (uint32_t)k;
            out->mKeyHi = (uint32_t)(k >> 32);
            wchar16* txt = ((wchar16* (__thiscall*)(void*))FUN_00550880)(meta);
            ((Fn_app)FUN_005c3d90)(&out->mText, txt);
        }
    }
    if (res != 0) ((Fn_v)VS(res, 0x04))(res);
    return ret;
}

// -----------------------------------------------------------------------------
// @ 0x006704f0
// -----------------------------------------------------------------------------
// finish the "eat feed" flow: when the row state is 1 or 2, show the matching
// card and post the user feed id for the selected row, then clear the state.
void __fastcall FUN_006704f0(void* self, void* edx, unsigned int a, unsigned int b) {
    (void)edx; (void)a;
    Owner* o = (Owner*)self;
    unsigned int st = o->mRow[1].mState;
    if (st != 1 && st != 2) return;

    unsigned int sel   = (st == 2) ? 1u : 0u;
    unsigned int idLo  = o->mRow[sel].mIdLo;
    unsigned int idHi  = o->mRow[sel].mIdHi;

    if (b == 0x5107b1au && ((void* (__cdecl*)())FUN_0067cb30)() != 0) {
        for (int i = 0; i < 2; ++i) {
            FeedRow* r = &o->mRow[i];
            if (r->mIdLo != idLo || r->mIdHi != idHi) continue;
            void* c3 = o->mpCard[3][i];
            if (c3) ((Fn_v2i)VS(c3, 0x7c))(c3, 1, 1);
            void* c2 = o->mpCard[2][i];
            if (c2) ((Fn_v2i)VS(c2, 0x7c))(c2, 1, 0);
            if ((r->mIdLo & r->mIdHi) == 0xffffffffu) continue;
            Str8 s;
            ((void (__cdecl*)(void*, unsigned int, const char*, unsigned int, unsigned int))FUN_00472f50)
                (&s, 0u, "tag:spore.com,2006:user/%I64u", idLo, idHi);
            void* pol = ((void* (__cdecl*)())FUN_0067cb30)();
            ((void (__thiscall*)(void*, void*))FUN_00610460)(pol, s.mpBegin);
            if (((int)(s.mpCapacity - s.mpBegin) > 1) && s.mpBegin != 0)
                ((void (__cdecl*)(void*))FUN_00f47380)(s.mpBegin);
        }
    }
    o->mRow[1].mState = 0;
}

// -----------------------------------------------------------------------------
// @ 0x00670610
// -----------------------------------------------------------------------------
// reconcile the three stored asset ids with the two rows: returns the next
// row state (0/1/2/4/6/8) after maintaining mpAuth's ids and the row texts.
unsigned int __fastcall FUN_00670610(void* self) {
    Owner* o = (Owner*)self;
    if (o->mpAuth == 0) return 0;

    const uint32_t* pa = ((Fn_pu)FUN_005507a0)(o->mpAuth);
    uint32_t aLo = pa[0], aHi = pa[1];
    const uint32_t* pb = ((Fn_pu)FUN_00550800)(o->mpAuth);
    uint32_t bLo = pb[0], bHi = pb[1];
    const uint32_t* pc = ((Fn_pu)FUN_00550820)(o->mpAuth);
    uint32_t cLo = pc[0], cHi = pc[1];

    unsigned int st;
    if ((bLo & bHi) == 0xffffffffu || (bLo | bHi) == 0u) {
        if ((cLo & cHi) == 0xffffffffu || (cLo | cHi) == 0u) return 0;
        if (cLo == aLo && cHi == aHi) return 0;
        if ((aLo & aHi) != 0xffffffffu) return 1;
        ((Fn_vuu)FUN_00551b60)(o->mpAuth, cLo, cHi);
        st = 6;
    } else {
        if ((cLo & cHi) == 0xffffffffu || (cLo | cHi) == 0u) {
            if (bHi != 0u || bLo == 0xffffffffu) {
                st = 2;
            } else {
                ((Fn_vuu)FUN_00551b80)(o->mpAuth, bLo, bHi);
                cLo = bLo; cHi = bHi;
                st = 6;
            }
        } else if (cLo == aLo && cHi == aHi) {
            st = 2;
        } else {
            st = 6;
        }
    }

    uint32_t ids[4];
    ids[0] = bLo; ids[1] = bHi; ids[2] = cLo; ids[3] = cHi;
    unsigned char r0 = 0, r1 = 0;
    for (int i = 0; i < 2; ++i) {
        if ((st & (2u << i)) == 0) continue;
        char c = FUN_00670370(0, 0, ids[2 * i], ids[2 * i + 1], &o->mRow[i]);
        if (i == 0) r0 = (unsigned char)c;
        else        r1 = (unsigned char)c;
    }

    if (st == 2u || st == 6u) {
        if (r0 != 0) {
            st = 4;
        } else if (st == 6u) {
            if (r1 == 0) return 6;
            return 2;
        }
    }
    if (st != 4u) return st;
    if (r1 != 0) st = 8;
    return st;
}

// -----------------------------------------------------------------------------
// @ 0x006707a0
// -----------------------------------------------------------------------------
// collect the requested asset ids into a small vector and hand it to
// cPollinator::PostEatFeed.
void __fastcall FUN_006707a0(void* self, void* edx, char a, char b, char c) {
    (void)edx;
    Owner* o = (Owner*)self;
    if (o->mpAuth == 0) return;

    unsigned __int64 buf[3];
    CS64Vec v;
    v.mpBegin    = buf;
    v.mpEnd      = buf;
    v.mpCapacity = buf + 3;
    uint32_t wasHeap = 0;

    if (a != 0) {
        const unsigned __int64* id = ((Fn_p64)FUN_005507a0)(o->mpAuth);
        if (v.mpEnd < v.mpCapacity) {
            unsigned __int64* slot = v.mpEnd;
            v.mpEnd = slot + 1;
            if (slot != 0) *slot = *id;
        } else {
            ((void (__thiscall*)(void*, void*, void*))FUN_004786e0)(&v, v.mpEnd, (void*)id);
            wasHeap = 1;
        }
    }
    if (b != 0) {
        const unsigned __int64* id = ((Fn_p64)FUN_00550800)(o->mpAuth);
        if (v.mpEnd < v.mpCapacity) {
            unsigned __int64* slot = v.mpEnd;
            v.mpEnd = slot + 1;
            if (slot != 0) *slot = *id;
        } else {
            ((void (__thiscall*)(void*, void*, void*))FUN_004786e0)(&v, v.mpEnd, (void*)id);
            wasHeap = 1;
        }
    }
    if (c != 0) {
        const unsigned __int64* id = ((Fn_p64)FUN_00550820)(o->mpAuth);
        if (v.mpEnd < v.mpCapacity) {
            unsigned __int64* slot = v.mpEnd;
            v.mpEnd = slot + 1;
            if (slot != 0) *slot = *id;
        } else {
            ((void (__thiscall*)(void*, void*, void*))FUN_004786e0)(&v, v.mpEnd, (void*)id);
            wasHeap = 1;
        }
    }

    if (v.mpBegin != v.mpEnd) {
        void* pol = ((void* (__cdecl*)())FUN_0067cb30)();
        ((void (__thiscall*)(void*, void*))FUN_00610460)(pol, &v);
    }
    if (v.mpBegin != 0 && wasHeap != 0)
        ((void (__cdecl*)(void*))FUN_00f47380)(v.mpBegin);
}

// -----------------------------------------------------------------------------
// @ 0x0066f9f0
// -----------------------------------------------------------------------------
// card view builder / refresh: toggles the three panels, sizes and places the
// two image cards, then flags each card row and lays out the phase-2 widgets.
void __fastcall FUN_0066f9f0(void* self, void* edx, char arg) {
    (void)edx;
    Owner* o = (Owner*)self;
    if (o->mpWin78 == 0) return;
    ((Fn_v2i)VS(o->mpWin78, 0x7c))(o->mpWin78, 1, 1);

    if (arg != 0) {
        if (o->mpWin80) ((Fn_v2i)VS(o->mpWin80, 0x7c))(o->mpWin80, 1, 1);
        if (o->mpWin84 == 0) return;
        ((Fn_v2i)VS(o->mpWin84, 0x7c))(o->mpWin84, 1, 0);
        return;
    }
    if (o->mpWin80) ((Fn_v2i)VS(o->mpWin80, 0x7c))(o->mpWin80, 1, 0);
    if (o->mpWin84) ((Fn_v2i)VS(o->mpWin84, 0x7c))(o->mpWin84, 1, 1);

    // --- phase 1: image cards + per-row enable flags ------------------------
    for (int i = 0; i < 2; ++i) {
        FeedRow* r = &o->mRow[i];
        void* img = o->mpCard[2][i];
        if (img != 0) {
            ((Fn_vp)VS(img, 0x80))(img, r->mText.mpBegin);
            ((void (__cdecl*)(void*, int, int))FUN_00806e40)(img, 0, 0);
            if (((Fn_p)VS(img, 0x10))(img) != 0) {
                void* child = ((Fn_p)VS(img, 0x10))(img);
                float* r1 = ((Fn_f)VS(child, 0x38))(child);
                float a0 = r1[0], a2 = r1[2];
                float* r2 = ((Fn_f)VS(img, 0x38))(img);
                ((Fn_vff)VS(img, 0x70))(img,
                    (a2 + a0) * 0.5f - (r2[2] - r2[0]) * 0.5f, r2[1]);
            }
            char keyFlag = (char)((r->mKeyLo & r->mKeyHi) != 0xffffffffu);
            void* cfg = ((void* (__cdecl*)())FUN_0067dd30)();
            char needCfg = (char)(((Fn_pi)VS(cfg, 0x30))(cfg, 0x5de7b4a) != 0);
            void* am = ((void* (__cdecl*)())FUN_00607a60)();
            char haveAuth = ((Fn_c)VS(am, 0x24))(am);
            char f10;
            if (needCfg != 0 || haveAuth != 0) f10 = 0;
            else                               f10 = (char)(keyFlag == 0);
            ((Fn_v2i)VS(img, 0x7c))(img, 2, f10);
        }

        uint32_t idLo = r->mIdLo, idHi = r->mIdHi;
        char flag50 = (char)r->mFlag;
        char flag14 = 0, flag18 = 0;
        if ((idLo & idHi) != 0xffffffffu && (idLo | idHi) != 0u) {
            if (((Fn_chuu)FUN_0066f150)(idLo, idHi)) {
                void* dir = ((void* (__cdecl*)())FUN_0067cb30)();
                dir = *(void**)((char*)dir + 0x58);
                if (!((Fn_cuu)FUN_0054e740)(dir, idLo, idHi)) flag18 = 1;
            } else if (flag50 != 0) {
                void* am = ((void* (__cdecl*)())FUN_00607a60)();
                if (!((Fn_c)VS(am, 0x24))(am)) flag14 = 1;
            }
        }
        void* c0 = o->mpCard[0][i];
        if (c0) ((Fn_v2i)VS(c0, 0x7c))(c0, 1, flag14);
        void* c1 = o->mpCard[1][i];
        if (c1) ((Fn_v2i)VS(c1, 0x7c))(c1, 1, flag18);
    }

    {
        void* am = ((void* (__cdecl*)())FUN_00607a60)();
        if (((Fn_c)VS(am, 0x24))(am)) return;
    }

    // --- feed scan: which of the two rows is already present ----------------
    uint8_t seen[2];
    seen[0] = 0; seen[1] = 0;
    {
        void* pol = ((void* (__cdecl*)())FUN_0067cb30)();
        FeedEntry* begin = *(FeedEntry**)((char*)pol + 0xc8);
        uint32_t count = (uint32_t)((char*)*(void**)((char*)pol + 0xcc) - (char*)begin) / 0x70u;
        if (count != 0) {
            FeedEntry* e = begin;
            do {
                if (e->mKind == 2) {
                    if (e->mKeyLo == o->mRow[0].mKeyLo && e->mKeyHi == o->mRow[0].mKeyHi)
                        seen[0] = 1;
                    if (e->mKeyLo == o->mRow[1].mKeyLo && e->mKeyHi == o->mRow[1].mKeyHi)
                        seen[1] = 1;
                }
                ++e;
            } while (--count != 0);
        }
    }

    // --- phase 2: buttons, title/card layout --------------------------------
    for (int i = 0; i < 2; ++i) {
        FeedRow* row = &o->mRow[i];
        void* s5 = o->mpCard[5][i];
        if (s5) ((Fn_v2i)VS(s5, 0x7c))(s5, 1, seen[i]);
        void* s3 = o->mpCard[3][i];
        if (s3 == 0) continue;

        char al;
        if ((row->mKeyLo & row->mKeyHi) == 0xffffffffu)                         al = 0;
        else if (seen[i] != 0)                                                  al = 0;
        else {
            void* am = ((void* (__cdecl*)())FUN_00607a60)();
            unsigned __int64 authId = ((Fn_u)VS(am, 0x40))(am);
            if (row->mIdLo == (uint32_t)authId && row->mIdHi == (uint32_t)(authId >> 32))
                al = 0;
            else if (row->mIdLo == 0xfffffffeu && row->mIdHi == 0xffffffffu)
                al = 0;
            else
                al = 1;
        }
        ((Fn_v2i)VS(s3, 0x7c))(s3, 1, al);

        if (o->mpCard[3][i] == 0) continue;
        void* s1 = o->mpCard[1][i];
        if (s1 == 0) continue;

        float* q1 = ((Fn_f)VS(s1, 0x38))(s1);
        float sz = q1[2];
        float* q2 = ((Fn_f)VS(s3, 0x38))(s3);
        ((Fn_vff)VS(s3, 0x70))(s3, sz, q2[1]);

        float* rc = ((Fn_f)VS(o->mpCard[3][i], 0x38))(o->mpCard[3][i]);
        float x = rc[0], y = rc[1], z = rc[2], w = rc[3];
        float cx = (x + z) * 0.5f;
        float cy = (w + y) * 0.5f;
        void* s4 = o->mpCard[4][i];
        if (s4) ((void (__cdecl*)(void*, float, float))FUN_00806ca0)(s4, cx, cy);
        void* s5b = o->mpCard[5][i];
        if (s5b) ((void (__cdecl*)(void*, float, float))FUN_00806ca0)(s5b, cx, cy);

        void* c0 = o->mpCard[0][i];
        if (c0 != 0) {
            float* r0 = ((Fn_f)VS(c0, 0x38))(c0);
            ((Fn_vff)VS(c0, 0x70))(c0, z, r0[1]);
        }
        void* c1 = o->mpCard[1][i];
        if (c1 != 0) {
            float* r1 = ((Fn_f)VS(c1, 0x38))(c1);
            ((Fn_vff)VS(c1, 0x70))(c1, z, r1[1]);
        }
    }
}