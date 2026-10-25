// src/game/SPGonzago/SPCreatureView.cpp -- migrated from slice(s) s00e8b7a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSpatialObject.h"

// unnamed retail callees and globals (address in the comment)
extern void* g_vtbl_014863cc[];   // 0x014863cc  SP::cCreatureView vftable
extern void* g_vtbl_01455648[];   // 0x01455648  view base vftable
#include <math.h>

// ---- items of slice s00e8b7a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            i32;
extern void* g_vtbl_014863cc[];   // 0x014863cc  SP::cCreatureView vftable
extern void* g_vtbl_01455648[];   // 0x01455648  view base vftable
extern u32   g_15a881c;           // 0x015a881c
u32  GetCurrentGameMode();                                             // 0x00b5b800
void* operator new(u32 size, const char* pName, int flags, unsigned dbgFlags,
                   const char* pFile, int line);                       // 0x00f473a0
void  operator delete(void* p);                                        // 0x00f47380
__forceinline void* vcall1(void* p, u32 off, void* a)
{ return ((void*(__thiscall*)(void*, void*))(*(void***)p)[off >> 2])(p, a); }
__forceinline u8 vbool0(void* p, u32 off)
{ return ((u8(__thiscall*)(void*))(*(void***)p)[off >> 2])(p); }
__forceinline u32 vint0(void* p, u32 off)
{ return ((u32(__thiscall*)(void*))(*(void***)p)[off >> 2])(p); }
__forceinline void vvoid0(void* p, u32 off)
{ ((void(__thiscall*)(void*))(*(void***)p)[off >> 2])(p); }
class cCombatSub {
public:
    void** mpVtbl;              // +0x00
    u32  FUN_008e7f80();        // 0x008e7f80
    bool FUN_00bfc600();        // 0x00bfc600
};
class cCreature {
public:
    void** mpVtbl;              // +0x00
    char pad04[0x34 - 0x04];
    void** mpVtbl34;            // +0x34  polymorphic sub-object (slot 0x74 = a float)
    char pad38[0x6e - 0x38];
    u8   m6e;                   // +0x6e
    char pad6f[0x84 - 0x6f];
    u32  m84;                   // +0x84
    char pad88[0xc0 - 0x88];
    void** mpVtblC0;            // +0xc0  animation sub-object (slot 0x8c)
    char padC4[0x330 - 0xc4];
    u32  m330;                  // +0x330
    char pad334[0x588 - 0x334];
    cCombatSub mCombat;         // +0x588
    char pad58c[0x684 - 0x58c];
    i32  m684;                  // +0x684
    char pad688[0xb58 - 0x688];
    u32  mFlagsB58;             // +0xb58
    char padB5c[0xb5e - 0xb5c];
    u8   mB5e;                  // +0xb5e
    char padB5f[0xb61 - 0xb5f];
    u8   mB61;                  // +0xb61
    u8   mB62;                  // +0xb62
    char padB63[0xf90 - 0xb63];
    u8   mF90;                  // +0xf90

    // direct (non-virtual) members -------------------------------------------
    bool FUN_00c8b220(u32 a, u32 b, u32 c, u32 d);   // 0x00c8b220
    void FUN_00c88a00(u32 a, float f);               // 0x00c88a00
    void FUN_00c8a020(u32 a, float f);               // 0x00c8a020
    void FUN_00c88a30(u32 a, void* b);               // 0x00c88a30
    void* FUN_00c14e70(u32 id);                      // 0x00c14e70
    void FUN_00c17350(u32 id, u32 b);                // 0x00c17350
    void FUN_00c1d400(u32 a, u32 b);                 // 0x00c1d400
    void FUN_00c1d460(u32 a, u32 b);                 // 0x00c1d460
    bool FUN_00c0b780();                             // 0x00c0b780
    bool FUN_00c0b7a0();                             // 0x00c0b7a0
    bool FUN_00c0c0e0();                             // 0x00c0c0e0
    void FUN_00c201a0(bool v, u32 a, u32 b);         // 0x00c201a0
};
class cEffect {
public:
    char pad00[0x88];
    u32  m88;                   // +0x88
    void Release();             // 0x00a05270
};
class cAnimSub {
public:
    void* FUN_00c41ec0();       // 0x00c41ec0
};
class cSubState {
public:
    char pad00[0x6c];
    float m6c;                  // +0x6c
};
namespace SP {
class cCreatureView {
public:
    void** mpVtbl;              // +0x00
    u32    m04;                 // +0x04
    u32    m08;                 // +0x08
    cCreature* mpCreature;      // +0x0c
    cEffect*   mpOverhead;      // +0x10
    u8     mb14;                // +0x14
    char   pad15[0x18 - 0x15];
    void*  mp18;                // +0x18

    cCreatureView();                                    // 0x00e8bc80
    void FUN_00e8bca0(cCreature* p);                    // 0x00e8bca0
    void FUN_00e8bd70(bool b);                          // 0x00e8bd70
    bool FUN_00e8bda0();                                // 0x00e8bda0
    void FUN_00e8bdc0();                                // 0x00e8bdc0
    void UpdateInteractionEffects();                    // 0x00e8be60
    void UpdateMotiveEffects();                         // 0x00e8bf20
    void FUN_00e8c030();                                // 0x00e8c030
    cCreatureView* FUN_00e8c0c0(u8 f);                  // 0x00e8c0c0
    void CreatureCitizenUpdate(cCreature* p);           // 0x00e8c070
};
}
namespace SP {
SP::cCreatureView* __stdcall FUN_00e8bd10(void* pSrc);  // 0x00e8bd10
}
// ---- items of slice s00e8b7a0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern u32   g_15a881c;           // 0x015a881c

// @ 0x00e8bd10
SP::cCreatureView* __stdcall SP::FUN_00e8bd10(void* pSrc)
{
    void* pArg = pSrc != 0 ? vcall1(pSrc, 0x0c, (void*)0xce9f6639) : 0;
    SP::cCreatureView* pView =
        new ("Simulator/cCreatureView", 0, 0, 0, 0) SP::cCreatureView;
    pView->FUN_00e8bca0((cCreature*)pArg);
    return pView;
}

// @ 0x00e8bd70
void SP::cCreatureView::FUN_00e8bd70(bool b)
{
    cEffect* p = mpOverhead;
    if (p != 0) {
        if (b)
            p->m88 |= 1u;
        else
            p->m88 &= ~1u;
    }
    if (mpCreature != 0)
        mpCreature->mF90 = b;
}

// @ 0x00e8bda0
bool SP::cCreatureView::FUN_00e8bda0()
{
    if (mpOverhead != 0)
        return (mpOverhead->m88 & 1) != 0;
    return false;
}

// @ 0x00e8be60
void SP::cCreatureView::UpdateInteractionEffects()
{
    if (!vbool0(mpCreature, 0xa0))
        return;
    mpCreature->FUN_00c17350(0x62edba5, 0);
    switch (vint0(mpCreature, 0x98)) {
    case 1:
        mpCreature->FUN_00c1d400(0xd8b86866, 0x62edba5);
        return;
    case 2:
        mpCreature->FUN_00c1d400(0xa01d381f, 0x62edba5);
        return;
    case 3:
        mpCreature->FUN_00c1d400(0xa31d75a8, 0x62edba5);
        return;
    case 4:
        mpCreature->FUN_00c1d400(0x121dd1fe, 0x62edba5);
        return;
    case 5:
        mpCreature->FUN_00c1d400(0x7a16b9e7, 0x62edba5);
        break;
    }
}

// @ 0x00e8bf20
void SP::cCreatureView::UpdateMotiveEffects()
{
    int iVar2 = (int)vint0(mpCreature, 0xa4);

    if (((mpCreature->m330 & 1) != 0) &&
        ((cSubState*)((cAnimSub*)((char*)mpCreature + 0xc0))->FUN_00c41ec0())->m6c > 5.0f) {
        if (mpCreature->FUN_00c14e70(0x6885174) != 0)
            return;
        mpCreature->FUN_00c1d460(0x57619fab, 0x6885174);
        mpCreature->FUN_00c17350(0x62edba6, 0);
        return;
    }
    if (vbool0(mpCreature, 0xa8) != 0) {
        mpCreature->mB61 = 0;
        mpCreature->FUN_00c17350(0x6885174, 0);
        mpCreature->FUN_00c17350(0x62edba6, 0);
        // the original keeps the two `cmp edi,2 / jl` and `cmp edi,3 / jg` separate
        // (cl folds `if (i<2) return; if (i>3) return;` into one range test)
        switch (iVar2) {
        case 2:
        case 3:
            break;
        default:
            return;
        }
        if (mpCreature->FUN_00c0b780() && mpCreature->FUN_00c0b7a0()) {
            mpCreature->FUN_00c1d460(0xbde1a55d, 0x62edba6);
            return;
        }
        if (mpCreature->FUN_00c0b7a0())
            mpCreature->FUN_00c1d460(0xde4f1682, 0x62edba6);
        else
            mpCreature->FUN_00c1d460(0x275458db, 0x62edba6);
        return;
    }
    mpCreature->FUN_00c17350(0x6885174, 0);
}

// @ 0x00e8c030
void SP::cCreatureView::FUN_00e8c030()
{
    mpVtbl = g_vtbl_014863cc;
    FUN_00e8bdc0();
    if (mp18 != 0)
        vvoid0(mp18, 0x04);
    if (mpOverhead != 0)
        mpOverhead->Release();
    if (mpCreature != 0)
        vvoid0(mpCreature, 0x04);
    mpVtbl = g_vtbl_01455648;
}

// @ 0x00e8c070
void SP::cCreatureView::CreatureCitizenUpdate(cCreature* p)
{
    UpdateInteractionEffects();
    if (GetCurrentGameMode() == 0x1654c05) {
        bool v = (p->mB62 != 0) && (p->mB5e == 0);
        mpCreature->FUN_00c201a0(v, g_15a881c, 0x372a3c5);
    }
}

// @ 0x00e8c0c0
SP::cCreatureView* SP::cCreatureView::FUN_00e8c0c0(u8 f)
{
    mpVtbl = g_vtbl_014863cc;
    FUN_00e8bdc0();
    if (mp18 != 0)
        vvoid0(mp18, 0x04);
    if (mpOverhead != 0)
        mpOverhead->Release();
    if (mpCreature != 0)
        vvoid0(mpCreature, 0x04);
    u8 bDelete = f & 1;
    mpVtbl = g_vtbl_01455648;
    if (bDelete)
        operator delete(this);
    return this;
}
