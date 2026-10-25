// Slice s006708d0 - SP UI missing-expansion-pack page + galaxy game-entry message handling.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE (same region as s00671840).
#include "types.h"
#include <stdio.h>
#include <intrin.h>

struct VObj { void** vt; };
typedef void   (__thiscall *FnV1)(void*);
typedef void   (__thiscall *FnV2ii)(void*, int, int);
typedef void*  (__thiscall *FnV0)(void*);
typedef void*  (__thiscall *FnV0i)(void*, int);
typedef int    (__thiscall *FnVi0)(void*);
typedef int    (__thiscall *FnVi2ii)(void*, int, int);

void DeleteObj(void* p);                 // 0x00f47380: operator delete

// ---- EA::UTFWinExtras::cXHTMLFrameSet ---------------------------------
struct FrameSet {
    void  Ctor(void* factory);                                   // 0x00996cc0
    void  Dtor();                                                // 0x009968a0
    void  Setup(int a, int b, int c, int d);                     // 0x00996280
    void* GetFrame(unsigned key);                                // 0x00996d40
    bool  CheckWin(void* win, unsigned key);                     // 0x009979f0
    bool  HandleLocationChange(unsigned key, unsigned a, unsigned b, int c); // 0x00997730
    bool  HandleFormSubmit(unsigned a, unsigned b);              // 0x009978b0
};

// globals holding frame keys / error dialog key
extern unsigned g_key_expansion_frame;    // [0x015282e4]
extern char     g_key_xhtml_dialog;       // [0x015285a4]

void FUN_00809db0(int a, void* b);        // 0x00809db0

// ---- SP::cSPUIMissingExpansionPackPage --------------------------------
struct MissingPage {
    void** vt;            // +0x00
    void** vt4;           // +0x04
    int    m8;            // +0x08
    char   fs[0x64];      // +0x0c .. +0x70  (cXHTMLFrameSet)
    void*  mpContentWin;  // +0x70
    void*  mpXHTMLWin;    // +0x74

    MissingPage();
    MissingPage* Destroy(unsigned flags);
    bool Init(void* w);
    bool DoMessage(int unused, int* msg);
    void SetVisibility(int vis);
};

// constructor
// @ 0x006715d0
MissingPage::MissingPage() {
    *(void**)((char*)this + 4) = (void*)0x13ec458;
    m8 = 0;
    ((FrameSet*)((char*)this + 0xc))->Ctor((void*)0x623f40);
    *(void**)this = (void*)0x1400944;
    *(void**)((char*)this + 4) = (void*)0x1400934;
    _ReadWriteBarrier();
    mpContentWin = 0;
    mpXHTMLWin = 0;
    ((FnV1)((VObj*)((char*)this + 0xc))->vt[0])((char*)this + 0xc);
}

// deleting destructor
// @ 0x00671630
MissingPage* MissingPage::Destroy(unsigned flags) {
    *(void**)this = (void*)0x1400944;
    *(void**)((char*)this + 4) = (void*)0x1400934;
    _ReadWriteBarrier();
    if (mpXHTMLWin) ((FnV1)((VObj*)mpXHTMLWin)->vt[1])(mpXHTMLWin);
    if (mpContentWin) ((FnV1)((VObj*)mpContentWin)->vt[1])(mpContentWin);
    ((FrameSet*)((char*)this + 0xc))->Dtor();
    *(void**)((char*)this + 4) = (void*)0x13ec458;
    *(void**)this = (void*)0x13eb938;
    if (flags & 1) DeleteObj(this);
    return this;
}

// @ 0x00671690
bool MissingPage::Init(void* w) {
    void* old = mpContentWin;
    if (w != old) {
        if (w) ((FnV1)((VObj*)w)->vt[0])(w);
        mpContentWin = w;
        if (old) ((FnV1)((VObj*)old)->vt[1])(old);
    }
    if (!mpContentWin) return false;
    ((FrameSet*)((char*)this + 0xc))->Setup(0x1002, 0x1006, 0x1003, 0x1024);
    ((FnV1)((VObj*)w)->vt[0x104 / 4])(w);
    if (!((FrameSet*)((char*)this + 0xc))->CheckWin(w, 0x34a5bc79)) return false;
    void* fr = ((FrameSet*)((char*)this + 0xc))->GetFrame(g_key_expansion_frame);
    void* nw = fr ? (char*)fr + 4 : 0;
    void* old2 = mpXHTMLWin;
    if (nw != old2) {
        if (nw) ((FnV1)((VObj*)nw)->vt[0])(nw);
        mpXHTMLWin = nw;
        if (old2) ((FnV1)((VObj*)old2)->vt[1])(old2);
    }
    return mpXHTMLWin != 0;
}

// @ 0x00671760
bool MissingPage::DoMessage(int unused, int* msg) {
    (void)unused;
    if ((void*)msg[0] != mpXHTMLWin) return false;
    int k = msg[2];
    if (k == 0x3326e8a) {
        int* p = (int*)msg[6];
        return ((FrameSet*)((char*)this + 0xc))
            ->HandleLocationChange((unsigned)msg[0], (unsigned)p[0], (unsigned)p[1], 0);
    }
    if (k == 0x3326e8b) {
        return ((FrameSet*)((char*)this + 0xc))
            ->HandleFormSubmit((unsigned)msg[0], (unsigned)msg[6]);
    }
    if (k == 0x43b0aee) {
        FUN_00809db0(0, &g_key_xhtml_dialog);
        return true;
    }
    return false;
}

// @ 0x006717e0
void MissingPage::SetVisibility(int vis) {
    void* fr = ((FrameSet*)((char*)this + 0xc))->GetFrame(g_key_expansion_frame);
    if (fr) {
        void* p = (char*)fr + 4;
        ((FnV2ii)((VObj*)p)->vt[0x7c / 4])(p, 1, vis);
    }
    void* x = mpContentWin;
    void* r = (void*)((FnVi2ii)((VObj*)x)->vt[0xf0 / 4])(x, 0x34a5bc7a, 1);
    if (r) ((FnV2ii)((VObj*)r)->vt[0x7c / 4])(r, 1, vis);
}

// ===========================================================================
// SP::cGalaxyGameEntryImpl  (0x006708d0 DeleteGame, 0x00670eb0 SetupPage).
// Retail member offsets come from the disassembly; unnamed fields keep role
// names.  The eastl::string16-typed members are modelled as a 0x10-byte
// {begin,end,cap} triple whose `assign` is the out-of-line helper at
// 0x00423650.
// ===========================================================================

extern void* DAT_01667bac;   // 0x01667bac  eastl::gEmptyString16

struct String16 {
    void* mBegin;    // +0x00
    void* mEnd;      // +0x04
    void* mCap;      // +0x08
    void* mPad;      // +0x0c
    void  assign(void* begin, void* end);   // 0x00423650
};

// a 32-bit Pollen asset id pair (GetAssetID returns a reference to one).
struct AssetKey {
    unsigned lo, hi;
};

struct cAssetMetadata {
    const AssetKey& GetAssetID() const;   // 0x005507a0 / 0x00550800 / 0x00550820
    void SetID(const AssetKey& id);       // 0x00551b60 / 0x00551b80
};

// eastl-backed growable array of 8-byte {keyLo, keyHi} entries.
struct KeyVector {
    unsigned* mBegin;  // +0x00
    unsigned* mEnd;    // +0x04
    unsigned  pad08;
};

// 0x118-byte record inside the metadata block's list.
struct Entry118 {
    char       pad00[0x10];
    unsigned   assetLo;       // +0x10
    unsigned   assetHi;       // +0x14
    char       pad18[0x20];
    unsigned   flags38;       // +0x38
    unsigned   flags3c;       // +0x3c

    unsigned   listLo;        // +0x40
    unsigned   listHi;        // +0x44
    char       pad4c[0x0c];
    unsigned   altKeyLo;      // +0x58
    unsigned   altKeyHi;      // +0x5c
    unsigned   altKey2Lo;     // +0x60
    unsigned   altKey2Hi;     // +0x64
    String16   altName;       // +0x68
    char       pad78[0x2c];
    cAssetMetadata* mpMeta;   // +0xa4
};

// the metadata block: a 0x60-byte header followed by a run of Entry118.
struct MetaBlock {
    char       pad00[0x60];
    Entry118*  mBegin;   // +0x60
    Entry118*  mEnd;     // +0x64
};

// the per-slide data record the handler reads (param_3).
struct SlideBlock {
    unsigned   mKind;          // +0x00
    char       pad04[4];
    MetaBlock* mpMetaBlock;    // +0x08
    char       pad0c[0x24];
    KeyVector* mpKeys;         // +0x30 (slot array scanned first)
    char       pad34[4];
};

// The caller passes param_3 as the second argument; the metadatum cursor is
// the *first* argument (used only through vtable calls on the parent object).
struct GalaxyGameEntry {
    char     pad00[0x14];
    cAssetMetadata* mpMetaThumb;  // +0x14  (GetAssetID compared against slots)
    AssetKey mKeyA;               // +0x18
    AssetKey mKeyB;               // +0x20
    String16 mNameA;              // +0x28
    unsigned char mHaveNameA;     // +0x38
    char     pad39[7];
    AssetKey mKeyC;               // +0x40
    String16 mNameB;              // +0x50
    unsigned char mHaveNameB;     // +0x60
    char     pad61[3];
    unsigned char mField64;       // +0x64
    int      mState;              // +0x68
    int      mField6c;            // +0x6c
    unsigned char mField70;       // +0x70

    void DeleteGame(int reason, SlideBlock* slide);        // 0x006708d0
    void SetupPage(void* layout, cAssetMetadata* meta);    // 0x00670eb0
};

extern const AssetKey* FUN_005507a0(cAssetMetadata* self);  // 0x005507a0 GetAssetID (slot A)
extern const AssetKey* FUN_00550800(cAssetMetadata* self);  // 0x00550800 GetAssetID (slot B)
extern const AssetKey* FUN_00550820(cAssetMetadata* self);  // 0x00550820 GetAssetID (slot C)
void SetAssetIdA(unsigned lo, unsigned hi);           // 0x00551b60
void SetAssetIdB(unsigned lo, unsigned hi);           // 0x00551b80

bool  FUN_00670370(unsigned lo, unsigned hi, const void* field);  // 0x00670370
void  FUN_006707a0(int a, int b, int c);                          // 0x006707a0
int   FUN_00670610(GalaxyGameEntry* self);                        // 0x00670610
void  FUN_0066f9f0(int a);                                        // 0x0066f9f0
void* GetManager();                                               // 0x0067dcd0
void  FUN_0067cb30(void* out);                                    // 0x0067cb30
void  FUN_00610460(void* p);                                      // 0x00610460
void  FUN_004786e0(void* dst, const void* src);                   // 0x004786e0
void  operator_delete__(void* p);                                 // 0x00f47380
void* SP_MessageServer();                                         // 0x0067dcc0
void* SP_AuthManager();                                           // 0x00607a60

// cSPUILayout::FindWindowByID (__thiscall: layout in ecx).
struct cSPUILayout {
    void* FindWindowByID(void* id, int recurse);   // 0x008105b0
};

extern unsigned DAT_014008b4[];   // 0x014008b4  two message ids

// FindWindowByID + AddRef-new / Release-old swap into *slot.
static __forceinline void FindAndSwap(void** slot, void* layout, void* id) {
    void* found = ((cSPUILayout*)layout)->FindWindowByID(id, 1);
    void* old = *slot;
    if (found != old) {
        if (found) ((FnV1)((VObj*)found)->vt[0])(found);
        *slot = found;
        if (old) ((FnV1)((VObj*)old)->vt[1])(old);
    }
}

// @ 0x006708d0
void GalaxyGameEntry::DeleteGame(int reason, SlideBlock* slide) {
    (void)reason;
    if (slide->mKind != 4) return;

    bool wantPrimary = (mState & 1) != 0;
    bool wantOne = (mState & 2) != 0;
    bool wantTwo = (((unsigned)mState >> 2) & 1) != 0;

    KeyVector* keys = slide->mpKeys;
    unsigned count = (unsigned)((keys->mEnd - keys->mBegin) >> 3);
    bool havePrimary = false, haveOne = false, haveTwo = false;
    for (unsigned i = 0; i < count; ++i) {
        unsigned lo = keys->mBegin[i * 2];
        unsigned hi = keys->mBegin[i * 2 + 1];
        const AssetKey& kA = *FUN_005507a0(mpMetaThumb);
        if (lo == kA.lo && hi == kA.hi) havePrimary = true;
        const AssetKey& kB = *FUN_00550800(mpMetaThumb);
        if (lo == kB.lo && hi == kB.hi) haveOne = true;
        const AssetKey& kC = *FUN_00550820(mpMetaThumb);
        if (lo == kC.lo && hi == kC.hi) haveTwo = true;
    }
    if (wantPrimary && !havePrimary) return;
    if (wantOne && !haveOne) return;
    if (wantTwo && !haveTwo) return;

    MetaBlock* blk = slide->mpMetaBlock;
    int n = (int)((blk->mEnd - blk->mBegin) / 0x118);
    bool changed = false;
    if (n != 0) {
        for (int i = 0; i < n; ++i) {
            Entry118* e = &blk->mBegin[i];

            if (wantPrimary && e->assetLo == FUN_005507a0(mpMetaThumb)->lo &&
                e->assetHi == 0) {
                if ((e->flags38 & e->flags3c) != 0xffffffffu) {
                    SetAssetIdA(e->flags38, e->flags3c);
                    changed = true;
                }
                unsigned lo = e->altKeyLo, hi = e->altKeyHi;
                if ((lo & hi) == 0xffffffffu || (lo == 0 && hi == 0)) {
                    lo = e->flags38;
                    hi = e->flags3c;
                    if ((lo & hi) != 0xffffffffu) {
                        SetAssetIdB(lo, hi);
                        changed = true;
                    }
                } else {
                    SetAssetIdB(lo, hi);
                    changed = true;
                }

                if (mField70 != 0) {
                    for (int j = 0; j < 2; ++j) {
                        String16* dst = (String16*)((char*)this + 0x18 + j * 0x28);
                        if ((*(unsigned*)((char*)dst) &
                             *(unsigned*)((char*)dst + 4)) == 0xffffffffu) {
                            unsigned kLo, kHi, sLo, sHi;
                            String16* src;
                            if (j == 0) {
                                kLo = e->flags3c;
                                sLo = e->listLo;
                                kHi = e->flags38;
                                sHi = e->listHi;
                                src = &e->altName;
                            } else {
                                kLo = e->altKeyHi;
                                kHi = e->altKeyLo;
                                sLo = e->altKey2Lo;
                                sHi = e->altKey2Hi;
                                src = (String16*)((char*)e + 0x68);
                            }
                            *(unsigned*)((char*)dst) = kHi;
                            *(unsigned*)((char*)dst + 4) = kLo;
                            if (src != (String16*)((char*)dst + 0x10)) {
                                dst->assign(src->mBegin, src->mEnd);
                            }
                            *(unsigned*)((char*)dst + 8) = sLo;
                            *(unsigned*)((char*)dst + 0xc) = sHi;
                            *(unsigned char*)((char*)dst + 0x20) = 0;
                        }
                    }
                }
                wantPrimary = false;
            }

            if (wantOne && e->assetLo == FUN_00550800(mpMetaThumb)->lo &&
                e->assetHi == 0) {
                unsigned lo = e->altKeyLo, hi = e->altKeyHi;
                unsigned wantLo = 0xffffffffu, wantHi = 0xffffffffu;
                if ((lo & hi) == 0xffffffffu || (lo == 0 && hi == 0)) {
                    lo = e->flags38;
                    hi = e->flags3c;
                    if ((lo & hi) != 0xffffffffu) {
                        wantLo = lo;
                        wantHi = hi;
                    }
                } else {
                    wantLo = lo;
                    wantHi = hi;
                }
                const AssetKey& k = *FUN_00550820(mpMetaThumb);
                if (k.lo != wantLo || k.hi != wantHi) {
                    SetAssetIdB(wantLo, wantHi);
                    changed = true;
                }
                mKeyA.lo = e->assetLo;
                mKeyA.hi = e->assetHi;
                cAssetMetadata* meta = e->mpMeta;
                mKeyB.lo = *(unsigned*)((char*)meta + 0x18);
                mKeyB.hi = *(unsigned*)((char*)meta + 0x1c);
                String16* src = (String16*)((char*)meta + 8);
                if (src != &mNameA) {
                    mNameA.assign(src->mBegin, src->mEnd);
                }
                wantOne = false;
            }

            if (wantTwo && e->assetLo == FUN_00550820(mpMetaThumb)->lo &&
                e->assetHi == 0) {
                mKeyC.lo = e->assetLo;
                mKeyC.hi = e->assetHi;
                cAssetMetadata* meta = e->mpMeta;
                *(unsigned*)((char*)this + 0x48) = *(unsigned*)((char*)meta + 0x18);
                *(unsigned*)((char*)this + 0x4c) = *(unsigned*)((char*)meta + 0x1c);
                String16* src = (String16*)((char*)meta + 8);
                if (src != &mNameB) {
                    mNameB.assign(src->mBegin, src->mEnd);
                }
                wantTwo = false;
            }
        }
    }

    int next = mState;
    switch (mState) {
        case 1:
            if (wantPrimary) { next = 0; break; }
            if (mField70 == 0) {
                const AssetKey& k1 = *FUN_00550800(mpMetaThumb);
                bool r1 = FUN_00670370(k1.lo, k1.hi, &mKeyA);
                const AssetKey& k2 = *FUN_00550820(mpMetaThumb);
                bool r2 = FUN_00670370(k2.lo, k2.hi, &mKeyC);
                if (!r1) {
                    next = 6;
                    FUN_006707a0(0, 1, 1);
                    break;
                }
                if (!r2) { next = 4; FUN_006707a0(0, 0, 1); break; }
                next = 8;
                break;
            }
            next = 0;
            mField70 = 0;
            break;
        case 2:
            if (wantOne) { next = 0; break; }
            if ((mKeyC.lo & mKeyC.hi) == 0xffffffffu) {
                const AssetKey& k = *FUN_00550820(mpMetaThumb);
                if (FUN_00670370(k.lo, k.hi, &mKeyC)) { next = 8; break; }
                next = 4;
                FUN_006707a0(0, 0, 1);
                break;
            }
            next = 8;
            break;
        case 4:
            if (wantTwo) { next = 0; break; }
            next = 8;
            break;
        case 6:
            if (!wantOne && !wantTwo) { next = 8; break; }
            next = 0;
            break;
        default:
            if (mState == 1) { next = 0; break; }
            break;
    }

    if (wantOne || wantTwo) {
        next = 1;
        mField70 = 1;
        if (mpMetaThumb != 0) {
            unsigned tmp[6];
            unsigned* dst = tmp;
            const AssetKey& k = *FUN_005507a0(mpMetaThumb);
            if (dst != 0) {
                dst[0] = k.lo;
                dst[1] = k.hi;
                dst += 2;
            }
            if (tmp != dst) {
                FUN_0067cb30(tmp);
                FUN_00610460(tmp);
            }
            if (tmp != 0 && tmp[-1] != 0) {
                operator_delete__(tmp);
            }
        }
    }

    if (next != mState) {
        mState = next;
        if (changed) {
            int* mgr = (int*)GetManager();
            ((void(__thiscall*)(void*, void*, int, int, int, int))((void**)*mgr)[0x20 / 4])(
                (void*)mgr, (void*)mpMetaThumb, 0, 0, 0, 0);
        }
        if (mState == 8 || mState == 0) {
            FUN_0066f9f0(0);
        }
    }
}

// @ 0x00670eb0
void GalaxyGameEntry::SetupPage(void* layout, cAssetMetadata* meta) {
    cAssetMetadata* old = mpMetaThumb;
    if (meta != old) {
        if (meta) ((FnV1)((VObj*)meta)->vt[0])(meta);
        mpMetaThumb = meta;
        if (old) ((FnV1)((VObj*)old)->vt[1])(old);
    }

    if (mpMetaThumb != 0) {
        void* server = SP_MessageServer();
        *(void**)((char*)this + 0xb8) = server;
        *(void**)((char*)this + 0xbc) = (char*)this + 4;
        *(void**)((char*)this + 0xc0) = &DAT_014008b4;
        *(int*)((char*)this + 0xc4) = 2;
        *(int*)((char*)this + 0xc8) = 0;
        if (server != 0) {
            for (unsigned off = 0; off < 8; off += 4) {
                ((void(__thiscall*)(void*, void*, void*))((void**)*(void**)server)[0x24 / 4])(
                    server, (char*)this + 4, *(void**)((char*)&DAT_014008b4[0] + off));
            }
        }
    }

    if (layout != 0) {
        FindAndSwap((void**)((char*)this + 0x74), layout, (void*)0x7ce7500);
        if (*(void**)((char*)this + 0x74) != 0) {
            ((void(__thiscall*)(void*, void*))((void**)*(void**)((char*)this + 0x74))[0x104 / 4])(
                *(void**)((char*)this + 0x74), this);
        }
        FindAndSwap((void**)((char*)this + 0x78), layout, (void*)0x7e4d3f0);
        if (*(void**)((char*)this + 0x78) != 0) {
            ((void(__thiscall*)(void*, int, int))((void**)*(void**)((char*)this + 0x78))[0x7c / 4])(
                *(void**)((char*)this + 0x78), 1, 0);
        }
        FindAndSwap((void**)((char*)this + 0x7c), layout, (void*)0x7c6d3c0);
        FindAndSwap((void**)((char*)this + 0x80), layout, (void*)0x7e5fcf0);
        FindAndSwap((void**)((char*)this + 0x84), layout, (void*)0x7e5fd08);
        FindAndSwap((void**)((char*)this + 0x88), layout, (void*)0xe5a99ed4);
        FindAndSwap((void**)((char*)this + 0x90), layout, (void*)0xb014f74c);
        FindAndSwap((void**)((char*)this + 0x8c), layout, (void*)0xeebd36a1);
        FindAndSwap((void**)((char*)this + 0x94), layout, (void*)0xe9079479);
        FindAndSwap((void**)((char*)this + 0x98), layout, (void*)0x53d6fe4a);
        FindAndSwap((void**)((char*)this + 0xa0), layout, (void*)0x7ce7460);
        FindAndSwap((void**)((char*)this + 0xa8), layout, (void*)0x7ce7462);
        FindAndSwap((void**)((char*)this + 0xb0), layout, (void*)0x7ce7461);
        FindAndSwap((void**)((char*)this + 0x9c), layout, (void*)0x53d6fe3a);
        FindAndSwap((void**)((char*)this + 0xa4), layout, (void*)0x7ce7450);
        FindAndSwap((void**)((char*)this + 0xac), layout, (void*)0x7ce7452);
        FindAndSwap((void**)((char*)this + 0xb4), layout, (void*)0x7ce7451);
    }

    mField6c = 0;
    mKeyA.lo = 0xffffffffu; mKeyA.hi = 0xffffffffu;
    mKeyB.lo = 0xffffffffu; mKeyB.hi = 0xffffffffu;
    if ((void*)((char*)&DAT_01667bac) != (void*)((char*)this + 0x28)) {
        mNameA.assign(&DAT_01667bac, &DAT_01667bac);
    }
    mHaveNameA = 1;
    mKeyC.lo = 0xffffffffu; mKeyC.hi = 0xffffffffu;
    *(unsigned*)((char*)this + 0x48) = 0xffffffffu;
    *(unsigned*)((char*)this + 0x4c) = 0xffffffffu;
    if ((void*)((char*)&DAT_01667bac) != (void*)((char*)this + 0x50)) {
        mNameB.assign(&DAT_01667bac, &DAT_01667bac);
    }
    mHaveNameB = 1;

    int st = FUN_00670610(this);
    mState = st;
    mField70 = 0;
    if (st == 0) {
        if (*(void**)((char*)this + 0x74) != 0) {
            ((void(__thiscall*)(void*, int, int))((void**)*(void**)((char*)this + 0x74))[0x7c / 4])(
                *(void**)((char*)this + 0x74), 2, 0);
        }
        return;
    }
    if (st == 8) {
        FUN_0066f9f0(0);
        return;
    }
    void* auth = SP_AuthManager();
    if (((unsigned char(__thiscall*)(void*))((void**)*(void**)auth)[0x24 / 4])(auth)) {
        FUN_0066f9f0(1);
        return;
    }
    FUN_006707a0(mState & 1, (mState >> 1) & 1, (mState >> 2) & 1);
}

// ---- 0x00671440 : message handler (complete, non-matching) ------------
struct MsgHandler { unsigned Handle(unsigned msg, int* arg); };

extern int* FUN_0067cb30();
extern bool SP_AddPollinatorDebugInfo(int* a, unsigned* b, int c);
extern unsigned FUN_0066f8e0(int a, int b, unsigned lo, unsigned hi);

// @ 0x00671440
unsigned MsgHandler::Handle(unsigned msg, int* arg) {
    if (msg == 0x1dd7bda9) {
        int flag = (arg[0] == 1);
        int* obj = (int*)arg[1];
        if (!obj) return 0;
        int id = ((FnVi0)((VObj*)obj)->vt[0x10 / 4])(obj);
        if (id == (int)0x86080586) {
            ((GalaxyGameEntry*)((char*)this - 4))->DeleteGame(flag, (SlideBlock*)obj);
        }
        id = ((FnVi0)((VObj*)obj)->vt[0x10 / 4])(obj);
        if (id == 0x3053c62 && obj[3] == 1) {
            unsigned lo = 0xffffffff, hi = 0xffffffff;
            if (sscanf((char*)obj[7], "tag:spore.com,2006:user/%I64u", &lo) == 1) {
                FUN_0066f8e0(flag, (int)obj, lo, hi);
            }
        }
    } else if (msg == 0x9421c619) {
        int a = arg[0], b = arg[1], c = arg[2];
        unsigned lo = 0xffffffff, hi = 0xffffffff;
        FUN_0067cb30();
        if (SP_AddPollinatorDebugInfo(&a, &lo, 0)) {
            int* p = (int*)((char*)this + 0x8c);
            int* q = (int*)((char*)this + 0x14);
            for (int i = 2; i != 0; --i) {
                if ((unsigned)q[0] == lo && (unsigned)q[1] == hi) {
                    if (p[-2]) ((FnV2ii)((VObj*)p[-2])->vt[0x7c / 4])((void*)p[-2], 1, 0);
                    if (*p) ((FnV2ii)((VObj*)*p)->vt[0x7c / 4])((void*)*p, 1, 1);
                }
                ++p;
                q += 10;
            }
        }
    }
    return 0;
}
