// Slice s00e8b7a0 — Simulator creature/turret views.
//
// 0x00e8b7a0  SP::cTurretView::HandleSimulationUpdate  — per-step update of a turret view:
//   drives the "overhead" info record (flags at +0x04, sub-state byte at +0x5c) of the
//   observed object (mpObject at +0x0c), keeps the cached orientation (+0x34..+0x40) and a
//   3d sound loop (+0x44) in sync, and pushes a pile of effect-parameter updates onto the
//   creature backing the object.
// 0x00e8bc80  cCreatureView ctor, 0x00e8bca0 set-creature, 0x00e8bd10 factory,
// 0x00e8bd70/0x00e8bda0 overhead-active accessors, 0x00e8bdc0 reset, 0x00e8be60/0x00e8bf20
// effect updates, 0x00e8c030/0x00e8c0c0 destructors, 0x00e8c070 CreatureCitizenUpdate.
//
// Layouts recovered from the retail code:
//   cSpatialObjectView  0x34 bytes, mpObject at +0x0c
//   cTurretView         0x50 bytes: base + cached orientation floats +0x34..+0x40,
//                       sound handle +0x44, two ref slots +0x48/+0x4c
//   cCreatureView       0x1c bytes: vptr, +0x04, +0x08, mpCreature +0x0c,
//                       mpOverheadEffect +0x10, byte +0x14, +0x18
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;

struct Float3 { float x, y, z; };

// ---------------------------------------------------------------------------------------------
// image data
// ---------------------------------------------------------------------------------------------
extern void* g_vtbl_014863cc[];   // 0x014863cc  SP::cCreatureView vftable
extern void* g_vtbl_01455648[];   // 0x01455648  view base vftable
extern float g_1486370;           // 0x01486370
// 0x018c6de8: a zero-initialised global in a section the resolver does not accept as data
// (annotation-implausible), so it must be referenced as a literal address.
extern float g_1477fbc;           // 0x01477fbc  200.0f
extern float g_1486110;           // 0x01486110  5.0f
extern u32   g_15a881c;           // 0x015a881c

// ---------------------------------------------------------------------------------------------
// free callees
// ---------------------------------------------------------------------------------------------
u32  GetCurrentGameMode();                                             // 0x00b5b800
void Start3dSoundByName(u32 id, u32 handle, float x, float y, float z); // 0x00571f80
void FUN_00572020(u32 handle, u32 b);                                  // 0x00572020
void* FUN_00b3d300();                                                  // 0x00b3d300 SP::NounManager
void* FUN_00a206f0();                                                  // 0x00a206f0 GetSystemAT
void FUN_01043860(void* p, void* pRef, bool b);                        // 0x01043860
void FUN_01043a50(void* p, void* pRef, bool b);                        // 0x01043a50
u32  FUN_00932e80(const char* p, u32 seed, u32 len);                    // 0x00932e80 FNVHash
void FUN_00e87600(void* pView);                                        // 0x00e87600 UpdateCloudTendril
void* FUN_00cf74c0();                                                  // 0x00cf74c0 cCivModeStrategy::Get
void FUN_00cd7d10();                                                   // 0x00cd7d10
void FUN_00d3d420();                                                   // 0x00d3d420
void FUN_00ae72d0();                                                   // 0x00ae72d0
void FUN_00b1e500();                                                   // 0x00b1e500
void* operator new(u32 size, const char* pName, int flags, unsigned dbgFlags,
                   const char* pFile, int line);                       // 0x00f473a0
void  operator delete(void* p);                                        // 0x00f47380

// ---------------------------------------------------------------------------------------------
// vtable-call helpers (this = p, slot index = off/4)
// NOTE: the value-returning helpers must use the direct `(*(void***)p)` form; routing them
// through an inlined `vtblOf()` makes cl select eax as the call target instead of edx, while
// the original uses the edx form for every slot call.
// ---------------------------------------------------------------------------------------------
__forceinline void* vcall0(void* p, u32 off)
{ return ((void*(__thiscall*)(void*))(*(void***)p)[off >> 2])(p); }
__forceinline void* vcall1(void* p, u32 off, void* a)
{ return ((void*(__thiscall*)(void*, void*))(*(void***)p)[off >> 2])(p, a); }
__forceinline u8 vbool0(void* p, u32 off)
{ return ((u8(__thiscall*)(void*))(*(void***)p)[off >> 2])(p); }
__forceinline u32 vint0(void* p, u32 off)
{ return ((u32(__thiscall*)(void*))(*(void***)p)[off >> 2])(p); }
__forceinline u32 vint1(void* p, u32 off, void* a)
{ return ((u32(__thiscall*)(void*, void*))(*(void***)p)[off >> 2])(p, a); }
__forceinline float vfloat0(void* p, u32 off)
{ return ((float(__thiscall*)(void*))(*(void***)p)[off >> 2])(p); }
__forceinline void vvoid0(void* p, u32 off)
{ ((void(__thiscall*)(void*))(*(void***)p)[off >> 2])(p); }
__forceinline void vvoid1(void* p, u32 off, u32 a)
{ ((void(__thiscall*)(void*, u32))(*(void***)p)[off >> 2])(p, a); }

// ---------------------------------------------------------------------------------------------
// recovered classes
// ---------------------------------------------------------------------------------------------

// "overhead" record handed out by cTurretView's vtable slot 0x2c (flags + a small state byte).
class tViewInfo {
public:
    char pad00[0x04];
    u32  mFlags04;              // +0x04  status bits (8 = "engaging")
    char pad08[0x5c - 0x08];
    u8   mState5c;              // +0x5c  0/1/2 engagement state
};

// combat sub-object embedded in the creature at +0x588.
class cCombatSub {
public:
    void** mpVtbl;              // +0x00
    u32  FUN_008e7f80();        // 0x008e7f80
    bool FUN_00bfc600();        // 0x00bfc600
};

// the creature object backing a creature/turret view.
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

// visual effect referenced by a creature view (non-virtual Release).
class cEffect {
public:
    char pad00[0x88];
    u32  m88;                   // +0x88
    void Release();             // 0x00a05270
};

// polymorphic sub-object embedded in the creature at +0xc0 (animation/motive state).
class cAnimSub {
public:
    void* FUN_00c41ec0();       // 0x00c41ec0
};

// polymorphic sub-state returned by cAnimSub::FUN_00c41ec0 (+0x6c = a float).
class cSubState {
public:
    char pad00[0x6c];
    float m6c;                  // +0x6c
};

// ---------- civ-mode strategy ----------------------------------------------------------------
class cCivState {
public:
    char pad00[0x80];
    void* mp80;                 // +0x80
};

class cCivSub {
public:
    void* mpVtbl;
    bool FUN_00d09660();        // 0x00d09660
    bool FUN_00d096e0(void* p); // 0x00d096e0
};

class cCivStrategy {
public:
    void* mpVtbl;
    cCivState* FUN_00cf74f0();  // 0x00cf74f0 GetState
};

// ---------- noun / game-data helpers ---------------------------------------------------------
class cNounMgr {
public:
    void* FUN_00b21340(void* a, void* b, void* c, void* d, void* e);  // 0x00b21340
    void* FUN_00b25f40(u32 id);                                       // 0x00b25f40
};

class cNoun {
public:
    char pad00[0xc4];
};

struct cPtrVec {                // returned by cNounMgr::FUN_00b21340
    char   pad00[4];
    void** mpBegin;             // +0x04
    void** mpEnd;               // +0x08
};

struct cItemInfo {              // returned by FUN_00ca71d0
    void* m00;                  // +0x00
    char  pad04[0x10 - 0x04];
    i32   m10;                  // +0x10
};
void* FUN_00ca71d0(void* pItem);   // 0x00ca71d0

// ---------- views ----------------------------------------------------------------------------
class cSpatialObjectView {
public:
    void** mpVtbl;              // +0x00
    u32  m04;                   // +0x04
    u32  m08;                   // +0x08
    cCreature* mpObject;        // +0x0c
    char pad10[0x34 - 0x10];
    void HandleSimulationUpdate(int a, int b);   // 0x00e92ca0
};

class cSpatialObject {
public:
    void** mpVtbl;              // +0x00
    char pad04[0x6e - 0x04];
    u8   m6e;                   // +0x6e
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

SP::cCreatureView* __stdcall FUN_00e8bd10(void* pSrc);  // 0x00e8bd10

class cTurretView : public cSpatialObjectView {
public:
    float m34;                  // +0x34  cached orientation
    float m38;                  // +0x38
    float m3c;                  // +0x3c
    float m40;                  // +0x40
    u32   m44;                  // +0x44  sound handle
    void* m48;                  // +0x48
    void* m4c;                  // +0x4c

    void HandleSimulationUpdate(int param_2, int param_3);   // 0x00e8b7a0
};

} // namespace SP

using namespace SP;

// ---------------------------------------------------------------------------------------------
// 0x00e8bc80  cCreatureView::cCreatureView
// ---------------------------------------------------------------------------------------------
// @ 0x00e8bc80
SP::cCreatureView::cCreatureView() {
    m08 = 0;
    m04 = 0;
    mpVtbl = g_vtbl_014863cc;
    mpCreature = 0;
    mpOverhead = 0;
    mb14 = 1;
    mp18 = 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00e8bca0  cCreatureView::FUN_00e8bca0 — set the backed creature
// ---------------------------------------------------------------------------------------------
// @ 0x00e8bca0
void SP::cCreatureView::FUN_00e8bca0(cCreature* p) {
    cCreature* pOld = mpCreature;
    if (p != pOld) {
        if (p != 0)
            vvoid0(p, 0x00);            // AddRef
        mpCreature = p;
        if (pOld != 0)
            vvoid0(pOld, 0x04);         // Release
    }
    // reset the creature's animation sub-object at +0xc0 (slot 0x8c, argument 0)
    vvoid1((char*)mpCreature + 0xc0, 0x8c, 0);
    u32 flags = p->mFlagsB58;
    bool bStunned = ((flags >> 9) & 1) != 0;
    if (bStunned || p->FUN_00c0c0e0())
        mb14 = 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00e8bd10  factory: new cCreatureView over the creature obtained through slot 0xc
// ---------------------------------------------------------------------------------------------
// @ 0x00e8bd10
SP::cCreatureView* __stdcall FUN_00e8bd10(void* pSrc) {
    void* pArg = pSrc != 0 ? vcall1(pSrc, 0x0c, (void*)0xce9f6639) : 0;
    SP::cCreatureView* pView =
        new ("Simulator/cCreatureView", 0, 0, 0, 0) SP::cCreatureView;
    pView->FUN_00e8bca0((cCreature*)pArg);
    return pView;
}

// ---------------------------------------------------------------------------------------------
// 0x00e8bd70  cCreatureView::FUN_00e8bd70 — enable/disable the overhead effect
// ---------------------------------------------------------------------------------------------
// @ 0x00e8bd70
void SP::cCreatureView::FUN_00e8bd70(bool b) {
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

// ---------------------------------------------------------------------------------------------
// 0x00e8bda0  cCreatureView::FUN_00e8bda0 — is the overhead effect enabled
// ---------------------------------------------------------------------------------------------
// @ 0x00e8bda0
bool SP::cCreatureView::FUN_00e8bda0() {
    if (mpOverhead != 0)
        return (mpOverhead->m88 & 1) != 0;
    return false;
}

// ---------------------------------------------------------------------------------------------
// 0x00e8bdc0  cCreatureView::FUN_00e8bdc0 — drop all references
// ---------------------------------------------------------------------------------------------
// @ 0x00e8bdc0
void SP::cCreatureView::FUN_00e8bdc0() {
    if (mp18 != 0) {
        vvoid1(mp18, 0x0c, 1);
        if (mp18 != 0) {
            void* p18 = mp18;
            mp18 = 0;
            vvoid0(p18, 0x04);
        }
    }
    if (mpCreature->FUN_00c14e70(0x73e4cdf) != 0)
        mpCreature->FUN_00c17350(0x73e4cdf, 0);
    if (mpCreature->FUN_00c14e70(0x7e2fedf) != 0)
        mpCreature->FUN_00c17350(0x7e2fedf, 0);
    if (mpCreature != 0) {
        cCreature* p = mpCreature;
        mpCreature = 0;
        vvoid0(p, 0x04);
    }
    if (mpOverhead != 0) {
        cEffect* p = mpOverhead;
        mpOverhead = 0;
        p->Release();
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00e8be60  cCreatureView::UpdateInteractionEffects
// ---------------------------------------------------------------------------------------------
// @ 0x00e8be60
void SP::cCreatureView::UpdateInteractionEffects() {
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

// ---------------------------------------------------------------------------------------------
// 0x00e8bf20  cCreatureView::UpdateMotiveEffects
// ---------------------------------------------------------------------------------------------
// @ 0x00e8bf20
void SP::cCreatureView::UpdateMotiveEffects() {
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

// ---------------------------------------------------------------------------------------------
// 0x00e8c030  cCreatureView::~cCreatureView (non-deleting)
// ---------------------------------------------------------------------------------------------
// @ 0x00e8c030
void SP::cCreatureView::FUN_00e8c030() {
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

// ---------------------------------------------------------------------------------------------
// 0x00e8c0c0  cCreatureView scalar deleting destructor
// ---------------------------------------------------------------------------------------------
// @ 0x00e8c0c0
SP::cCreatureView* SP::cCreatureView::FUN_00e8c0c0(u8 f) {
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

// ---------------------------------------------------------------------------------------------
// 0x00e8c070  cCreatureView::CreatureCitizenUpdate
// ---------------------------------------------------------------------------------------------
// @ 0x00e8c070
void SP::cCreatureView::CreatureCitizenUpdate(cCreature* p) {
    UpdateInteractionEffects();
    if (GetCurrentGameMode() == 0x1654c05) {
        bool v = (p->mB62 != 0) && (p->mB5e == 0);
        mpCreature->FUN_00c201a0(v, g_15a881c, 0x372a3c5);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00e8b7a0  cTurretView::HandleSimulationUpdate
// ---------------------------------------------------------------------------------------------
// @ 0x00e8b7a0
void SP::cTurretView::HandleSimulationUpdate(int param_2, int param_3) {
    cSpatialObjectView::HandleSimulationUpdate(param_2, param_3);

    u32 gameMode = GetCurrentGameMode();
    bool isCivMode = (gameMode == 0x1654c05);
    tViewInfo* pInfo = (tViewInfo*)vcall0(this, 0x2c);
    if (mpObject == 0)
        return;

    cCreature* pCtx = mpObject
        ? (cCreature*)vcall1(mpObject, 0xb8, (void*)0x436f315)
        : 0;

    if (pInfo != 0) {
        if (mpObject->m6e != 0) {
            pInfo->mFlags04 |= 8u;
            pInfo->mState5c = 1;
        } else if (!vbool0(mpObject, 0x24) ||
                   (isCivMode &&
                    (pCtx == 0 || !vbool0((char*)pCtx + 0x34, 0x58)))) {
            // ---- civ-mode strategy block ----
            if (FUN_00cf74c0() != 0
                && ((cCivStrategy*)FUN_00cf74c0())->FUN_00cf74f0() != 0
                && ((cCivStrategy*)FUN_00cf74c0())->FUN_00cf74f0()->mp80 != 0
                && ((cCivSub*)((cCivStrategy*)FUN_00cf74c0())->FUN_00cf74f0()->mp80)
                       ->FUN_00d09660() != 0
                && !((cCivSub*)((cCivStrategy*)FUN_00cf74c0())->FUN_00cf74f0()->mp80)
                       ->FUN_00d096e0(pCtx)) {
                pInfo->mFlags04 |= 8u;
                pInfo->mState5c = 2;
            } else {
                pInfo->mFlags04 &= ~8u;
            }
        } else {
            pInfo->mFlags04 |= 8u;
            pInfo->mState5c = 2;
        }
    }

    if (isCivMode) {
        FUN_01043860(mpObject, &m48, false);
        FUN_01043a50(mpObject, &m4c, false);
    }

    // ---- distance to the reference point (player/system position) ----
    float* pPos = (float*)vcall0(mpObject, 0x2c);
    bool bNear = false;
    if (FUN_00a206f0() != 0) {
        float px = pPos[0];
        float py = pPos[1];
        float pz = pPos[2];
        float* pRef = (float*)vcall1(FUN_00a206f0(), 0x10, (void*)1);
        float dx = pRef[0] - px;
        float dy = pRef[1] - py;
        float dz = pRef[2] - pz;
        bNear = (float)sqrt((double)dx * (double)dx + (double)dy * (double)dy
                            + (double)dz * (double)dz) < 200.0f;
    }

    // ---- cached orientation / 3d sound loop ----
    {
        float* pO = (float*)vcall0(mpObject, 0x30);
        if (m34 == pO[0] && m38 == pO[1] && m3c == pO[2] && m40 == pO[3]) {
            if (m44 != 0) {
                FUN_00572020(m44, 0);
                m44 = 0;
            }
        } else if (isCivMode) {
            float* pO2 = (float*)vcall0(mpObject, 0x30);
            m34 = pO2[0];
            m38 = pO2[1];
            m3c = pO2[2];
            m40 = pO2[3];
            if (m44 == 0) {
                void* pSys = FUN_00a206f0();
                m44 = pSys != 0 ? vint0(pSys, 0x20) : 0;
                Start3dSoundByName(0x556b8c45, m44, pPos[0], pPos[1], pPos[2]);
            }
        } else {
            if (m44 != 0) {
                FUN_00572020(m44, 0);
                m44 = 0;
            }
        }
    }

    if (pCtx == 0)
        return;

    // ---- combat / effect parameter push ----
    cCombatSub* pCombat = &pCtx->mCombat;
    bool bFile2 = (pCombat->FUN_008e7f80() == 2);
    mpObject->FUN_00c8b220(0x23e2af64, 0x4c9bd57, bFile2, 0);
    u32 v1 = (pCtx->m684 > 0 || pCombat->FUN_00bfc600()) ? 1 : 0;
    if (mpObject->FUN_00c8b220(0x39ff8e9e, 0x4acb33c, v1, 0)) {
        cPtrVec* pVec = (cPtrVec*)((cNounMgr*)FUN_00b3d300())->FUN_00b21340(
            (void*)&FUN_00cd7d10, (void*)&FUN_00d3d420, (void*)&FUN_00ae72d0,
            (void*)&FUN_00b1e500, (void*)0x018c6de8u);
        int n = (int)(pVec->mpEnd - pVec->mpBegin);
        for (int i = 0; i < n; ++i) {
            void* pItem = pVec->mpBegin[i];
            cItemInfo* pItemInfo = (cItemInfo*)FUN_00ca71d0(pItem);
            if (pItemInfo->m10 == 1 && pItemInfo->m00 == (void*)pCtx) {
                u32 id = vint0(pItem, 0x4c);
                cNoun* pNoun = (cNoun*)((cNounMgr*)FUN_00b3d300())->FUN_00b25f40(id);
                if (pNoun != 0)
                    mpObject->FUN_00c88a30(0x4acb33c, (char*)pNoun + 0xc4);
            }
        }
    }

    FUN_00e87600(this);

    bool bFlag800 = ((pCtx->m84 & 0x800) == 0x800);
    if (mpObject->FUN_00c8b220(0x56192017, 0x30e8811, bFlag800, 0)) {
        mpObject->FUN_00c88a00(0x30e8811, g_1486370);
        float f74 = vfloat0((char*)pCtx + 0x34, 0x74);
        mpObject->FUN_00c8a020(0x30e8811, f74);
    }
    pCtx->m84 &= ~0x800u;

    u32 hash = FUN_00932e80("SG_ufo_static_cling_stunned_vehicle", 0x811c9dc5, 1);
    bool bCombat = pCombat->FUN_00bfc600();
    mpObject->FUN_00c8b220(hash, 0x5f8d750, bCombat, 0);
    u32 v2 = (pCtx->m684 > 0 || pCombat->FUN_00bfc600()) ? 1 : 0;
    if (mpObject->FUN_00c8b220(0x6dcfc3d2, 0x13bdd20b, v2, 0))
        mpObject->FUN_00c88a00(0x13bdd20b, g_1486370);
}