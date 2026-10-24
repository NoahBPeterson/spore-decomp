// Slice s00c25a50: SP::cSPCreatureCitizen tool-selection, order and animation
// state machine (0xc25a50-0xc26730).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
// Callees outside the slice are masked relocations, so they are only declared
// with the right calling convention.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;
typedef int            intptr_t;
typedef float          f32;

struct Vec3 { f32 mX, mY, mZ; };

// ---- external classes -------------------------------------------------------

class IRefCounted {
public:
    virtual void  AddRef();                 // +0x00 slot 0
    virtual void  Release();                // +0x04 slot 1
    virtual void  v08();
    virtual void* Query(const void* pType);
    virtual void  v10();
};

class cCommunity {
public:
    void* GetLeader();                      // 0x00c00650
};

class cVariant {
public:
    cVariant& operator=(const cVariant& rhs);   // 0x00542b80
    u8 mBytes[0x14];
};

class cOrderPlay {
public:
    void* Play(u32 a, u32 b);                        // 0x00bc96a0
    void  FUN_00bc97f0(u32 a, u32 b, f32 c, u32 d);  // 0x00bc97f0
};

class cAgentOrderManager {
public:
    void* FirstPending();                   // 0x00bca2c0
    u8 mPad_04[4];
    cOrderPlay mPlay_08;                    // +0x08
};

// Raw dispatch helper for embedded sub-objects whose slots are too high to
// spell out as virtual members of the reconstructed class.
class cVTable { public: void* mpSlots[0x60]; };

class cDispatchObject {
public:
    void* Call(i32 slot) {
        return ((void* (__thiscall*)(cDispatchObject*))mpTable->mpSlots[slot >> 2])(this);
    }
    i32 CallInt(i32 slot) {
        return ((i32 (__thiscall*)(cDispatchObject*))mpTable->mpSlots[slot >> 2])(this);
    }
    f32 CallFloat(i32 slot) {
        return ((f32 (__thiscall*)(cDispatchObject*))mpTable->mpSlots[slot >> 2])(this);
    }
    void CallVoid(i32 slot) {
        ((void (__thiscall*)(cDispatchObject*))mpTable->mpSlots[slot >> 2])(this);
    }
    void* CallArg(i32 slot, i32 arg) {
        return ((void* (__thiscall*)(cDispatchObject*, i32))mpTable->mpSlots[slot >> 2])(this, arg);
    }
    f32 CallFloatArg(i32 slot, i32 arg) {
        return ((f32 (__thiscall*)(cDispatchObject*, i32))mpTable->mpSlots[slot >> 2])(this, arg);
    }
    cVTable* mpTable;                       // +0x00
};

// An order record stored at the head of the pending order queue.
class cOrder {
public:
    u32 mType_00;                           // +0x00
    u8  mPad_04[0x28 - 0x04];
    i32 mn_28;                              // +0x28  (pending / active flag)
    u8  mPad_2c[0x38 - 0x2c];
    u8  mb_38;                              // +0x38
    u8  mPad_39[0x4b - 0x39];
    u16 mw_4b;                              // +0x4b  (order sub-type)
};

// `this` of FUN_00c26730: a fixed order/selection payload that is copied field
// by field with ref-counted and Variant members.
#pragma pack(push, 1)
class cOrderData {
public:
    cOrderData* FUN_00c26730(const cOrderData* pSrc);

    i32          mn_00;                     // +0x00
    u8           mPad_04[0x10 - 0x04];
    i32          mn_10;                     // +0x10
    i32          mn_14;                     // +0x14
    i32          mn_18;                     // +0x18
    i32          mn_1c;                     // +0x1c
    u8           mb_20;                     // +0x20
    u8           mPad_21[3];
    i32          mn_24;                     // +0x24
    IRefCounted* mp_28;                     // +0x28
    i32          mn_2c;                     // +0x2c
    i32          mn_30;                     // +0x30
    i32          mn_34;                     // +0x34
    u8           mb_38;                     // +0x38
    cVariant     mv_39;                     // +0x39
    cVariant     mv_4d;                     // +0x4d
    cVariant     mv_61;                     // +0x61
    cVariant     mv_75;                     // +0x75
};
#pragma pack(pop)

// The element copied by FUN_00c266c0.
class cElem18 {
public:
    u8           mb_00;                     // +0x00
    IRefCounted* mp_04;                     // +0x04
    i32          mn_08;                     // +0x08
    f32          mf_0c;                     // +0x0c
    f32          mf_10;                     // +0x10
    f32          mf_14;                     // +0x14
};

// ---- global data ------------------------------------------------------------

extern const f32 _HK_REAL_ZERO;             // 0x01485378
extern f32 DAT_0168dbb0;                    // 0x0168dbb0
extern f32 DAT_0168dbb4;                    // 0x0168dbb4
extern f32 DAT_0168dbb8;                    // 0x0168dbb8
extern f32 DAT_0146aa40;                    // 0x0146aa40 (FLT_MAX)
extern u8  DAT_0168dc98[0x24];              // 0x0168dc98
extern f32 DAT_0168dcbc;                    // 0x0168dcbc
extern f32 DAT_0168dcc0;                    // 0x0168dcc0
extern f32 DAT_0168dcc4;                    // 0x0168dcc4
extern u32 DAT_0169ef30;                    // 0x0169ef30
extern u32 DAT_0169f028;                    // 0x0169f028
extern void* DAT_01572068;                  // 0x01572068
extern u8  DAT_02796b30[1];                 // 0x02796b30 animation name
extern u8  DAT_02c39200[1];                 // 0x02c39200 animation name

class cConstObj {
public:
    f32 FUN_0104bdb0();                     // 0x0104bdb0
    f32 FUN_00bfc490();                     // 0x00bfc490
};

// ---- the creature citizen ---------------------------------------------------

class cSPCreatureCitizen {
public:
    // callees borrowed from the creature base (masked relocations)
    int   GetToolEffect(u32 nTool);                     // 0x00c235e0
    bool  HasSpecializedTool(i32 nTool);                // 0x00c236e0
    bool  IsLeader();                                   // 0x00c232d0
    void  PerformSocialAction(i32 nMode, u32 nAnim);    // 0x00c23300
    void  InterruptAnimation(u32 id, i32 a, i32 b);     // 0x00c12310
    bool  AnimationFinished(u32 id);                    // 0x00c123f0
    void* GetCurrentAnimationGUID();                    // 0x00c0e040
    int   PlayAnimationWithTarget(u32 id, i32 a, i32 b, i32 c);   // 0x00c14910
    int   PlayAnimationWithTarget2(u32 id, i32 a, i32 b, i32 c);  // 0x00c14940
    bool  WaitForAnimEventOrEnd(u32 a, void* out, u32 id, i32 h, i32 b); // 0x00c14ef0
    void  SetCurrentToolEffect(i32 nTool, u32 a);       // 0x00c24f40
    int   FUN_00c0f4f0();                               // 0x00c0f4f0
    char  FUN_00c0e0c0(i32 nType);                      // 0x00c0e0c0
    void* FUN_00c0fa70(u32 a, u32* pOut);               // 0x00c0fa70
    u32   FUN_00c0f6b0();                               // 0x00c0f6b0
    void* FUN_00c0f9b0(i32 nKey, u32* pIndex);          // 0x00c0f9b0
    void* FUN_00c0dfb0(void* pKey);                     // 0x00c0dfb0
    void  FUN_00c0de60(void* pElem, void* pOffsets);    // 0x00c0de60
    void  FUN_00c24040(void* pTree);                    // 0x00c24040
    void  FUN_00c15150(void* pArg, i32 n);              // 0x00c15150
    void* FUN_00c17d60(i32 a, void* b, i32 c, void* d, i32 e); // 0x00c17d60
    int   FUN_00c22c40(i32 a);                          // 0x00c22c40
    int   FUN_00c22dd0();                               // 0x00c22dd0
    int   FUN_00c23f80(i32 a, i32 b, i32 c, i32 d);     // 0x00c23f80
    int   FUN_00c245e0(i32 a, i32 b, f32 c, i32 d, i32 e, i32 f); // 0x00c245e0

    // slice targets
    bool  FUN_00c25a50(void* pTree);
    void  FUN_00c25f80();
    i32   FUN_00c26120();
    i32   FUN_00c26170();
    void  FUN_00c26310(void* pTree);
    bool  IsWaitingForTool(i32 nTool);
    void  SetToolOnAnimEvent(i32 nTool);
    void  FUN_00c26450();

    // fields
    u8   mPad_000[0x34];
    cDispatchObject mSub_034;               // +0x034 (locomotion / spatial)
    u8   mPad_038[0xc0 - 0x38];
    cDispatchObject mSub_0c0;               // +0x0c0 (identity / interactive)
    u8   mPad_0c4[0xb20 - 0xc4];
    void* mp_b20;                           // +0x0b20
    u8   mPad_b24[0xb4c - 0xb24];
    cAgentOrderManager* mpOrders_b4c;       // +0x0b4c
    u8   mPad_b50[0xb54 - 0xb50];
    void* mp_b54;                           // +0x0b54
    u8   mPad_b58[0xe40 - 0xb58];
    void* mp_e40;                           // +0x0e40
    u8   mPad_e44[0xfc4 - 0xe44];
    void* mpBT_fc4;                         // +0x0fc4 behavior tree data
    void* mpInteract_fc8;                   // +0x0fc8 who is interacting
    u8   mPad_fcc[0xffc - 0xfcc];
    i32   mnCurTool_ffc;                    // +0x0ffc current tool effect bits
    u8   mPad_1000[0x1002 - 0x1000];
    u8    mb_1002;                          // +0x1002
    u8   mPad_1003[0x1004 - 0x1003];
    f32   mf_1004;                          // +0x1004
    f32   mf_1008;                          // +0x1008
    f32   mf_100c;                          // +0x100c
    void* mpOwnerCity_1010;                 // +0x1010
    void* mpOwnerTribe_1014;                // +0x1014
    u8   mPad_1018[0x102c - 0x1018];
    i32   mnToolEffectIndex;                // +0x102c
};

// ---- free callees (masked relocations) --------------------------------------

void  FUN_00c10330(i32 a, i32 b, i32 c, i32 d, i32 e, i32 f);   // 0x00c10330
void* FUN_00b3d2b0(f32 fValue, i32 a, void* b);                 // 0x00b3d2b0
void* FUN_005727b0(void* p);                                    // 0x005727b0
void* FUN_005727e0(void* p);                                    // 0x005727e0
void  FUN_00ac7d10();                                           // 0x00ac7d10 (thiscall)
void* FUN_00cee330(void* p);                                    // 0x00cee330 (this in ecx)
f32   FUN_00cee380(void* p);                                    // 0x00cee380 (this in ecx)
void  FUN_0041cb40(void* pDst, void* pSrc);                     // 0x0041cb40

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// ---------------------------------------------------------------------------
// 0x00c26120  SP::cSPCreatureCitizen::FUN_00c26120
// ---------------------------------------------------------------------------
// @ 0x00c26120
// NOTE: original ends with `sete al; test al,al; je` which MSVC 15.00 /O2
// if-converts to `jne` for every reconstructable source form; byte diff 19.
i32 cSPCreatureCitizen::FUN_00c26120() {
    i32 tool = mnToolEffectIndex;
    if (tool != 0)
        return GetToolEffect((u32)tool);
    cCommunity* pComm = (cCommunity*)mpOwnerCity_1010;
    if (pComm == 0)
        pComm = (cCommunity*)mpOwnerTribe_1014;
    if (pComm != 0 && pComm->GetLeader() == this)
        return 0x11;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00c26310  SP::cSPCreatureCitizen::FUN_00c26310
// ---------------------------------------------------------------------------
// @ 0x00c26310
// NOTE: same `sete al; test al,al; je` limitation as FUN_00c26120.
void cSPCreatureCitizen::FUN_00c26310(void* pTree) {
    i32 eff;
    if (mnToolEffectIndex != 0) {
        eff = GetToolEffect((u32)mnToolEffectIndex);
    } else {
        cCommunity* pComm = (cCommunity*)mpOwnerCity_1010;
        if (pComm == 0)
            pComm = (cCommunity*)mpOwnerTribe_1014;
        if (pComm != 0 && pComm->GetLeader() == this)
            eff = 0x11;
        else
            eff = 0;
    }
    if (pTree != mpBT_fc4 || eff != mnCurTool_ffc)
        SetCurrentToolEffect(eff, (u32)pTree);
}

// ---------------------------------------------------------------------------
// 0x00c26380  SP::cSPCreatureCitizen::IsWaitingForTool
// ---------------------------------------------------------------------------
// @ 0x00c26380 SP::cSPCreatureCitizen::IsWaitingForTool
bool cSPCreatureCitizen::IsWaitingForTool(i32 nTool) {
    i32 cur = mnCurTool_ffc;
    if (cur != GetToolEffect((u32)nTool)) {
        if (HasSpecializedTool(nTool) || mnCurTool_ffc != 0) {
            InterruptAnimation(0x2c39200, (i32)(intptr_t)mpBT_fc4, 0);
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00c263e0  SP::cSPCreatureCitizen::SetToolOnAnimEvent
// ---------------------------------------------------------------------------
// @ 0x00c263e0 SP::cSPCreatureCitizen::SetToolOnAnimEvent
void cSPCreatureCitizen::SetToolOnAnimEvent(i32 nTool) {
    i32 tool = nTool;
    if (!HasSpecializedTool(tool))
        tool = 0;
    i32 eff = GetToolEffect((u32)tool);
    if (mnCurTool_ffc != eff) {
        if ((i32)(intptr_t)GetCurrentAnimationGUID() == 0x2c39200) {
            nTool = -1;
            if (WaitForAnimEventOrEnd((u32)(intptr_t)DAT_01572068, &nTool, 0xffffffff, 0, 1))
                SetCurrentToolEffect(eff, (u32)nTool);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00c266c0  FUN_00c266c0  (range copy of 0x18-byte elements)
// ---------------------------------------------------------------------------
// @ 0x00c266c0
// NOTE: original keeps pBegin/pEnd in their stack home slots (reloading pBegin
// after the inlined AddRef); MSVC keeps them in ebp/esi here. Byte diff 80.
cElem18** __cdecl FUN_00c266c0(cElem18** ppOut, cElem18* pBegin, cElem18* pEnd, cElem18* pValue) {
    *ppOut = pValue;
    for (; pBegin != pEnd; ++pBegin) {
        cElem18* p = *ppOut;
        if (p != 0) {
            p->mb_00 = pBegin->mb_00;
            p->mp_04 = pBegin->mp_04;
            if (p->mp_04 != 0)
                p->mp_04->AddRef();
            p->mn_08 = pBegin->mn_08;
            p->mf_0c = pBegin->mf_0c;
            p->mf_10 = pBegin->mf_10;
            p->mf_14 = pBegin->mf_14;
        }
        *ppOut = *ppOut + 1;
    }
    return ppOut;
}

// ---------------------------------------------------------------------------
// 0x00c26730  cOrderData::FUN_00c26730  (order/selection copy)
// ---------------------------------------------------------------------------
// @ 0x00c26730
cOrderData* cOrderData::FUN_00c26730(const cOrderData* pSrc) {
    mn_00 = pSrc->mn_00;
    mn_10 = pSrc->mn_10;
    mn_14 = pSrc->mn_14;
    mn_18 = pSrc->mn_18;
    mn_1c = pSrc->mn_1c;
    mb_20 = pSrc->mb_20;
    mn_24 = pSrc->mn_24;
    _ReadWriteBarrier();
    IRefCounted* pNew = pSrc->mp_28;
    IRefCounted* pOld = mp_28;
    if (pNew != pOld) {
        if (pNew != 0)
            pNew->AddRef();
        mp_28 = pNew;
        if (pOld != 0)
            pOld->Release();
    }
    mn_2c = pSrc->mn_2c;
    mn_30 = pSrc->mn_30;
    mn_34 = pSrc->mn_34;
    mb_38 = pSrc->mb_38;
    mv_39 = pSrc->mv_39;
    mv_4d = pSrc->mv_4d;
    mv_61 = pSrc->mv_61;
    mv_75 = pSrc->mv_75;
    return this;
}

// ---------------------------------------------------------------------------
// 0x00c26170  SP::cSPCreatureCitizen::FUN_00c26170
// ---------------------------------------------------------------------------
// @ 0x00c26170
// NOTE: original is a byte-indexed jump table (0xc262ec -> 0xc262bc); the
// reconstructed switch compiles to a plain dword table. Semantic only.
i32 cSPCreatureCitizen::FUN_00c26170() {
    cOrder* pOrder = (cOrder*)mpOrders_b4c->FirstPending();
    if (pOrder == 0)
        return mnCurTool_ffc;
    switch (pOrder->mType_00) {
    case 1:
        return IsLeader() ? 0x11 : 4;
    case 2:
        return IsLeader() ? 0x11 : 0x10;
    case 4:
    case4_ret:
        return FUN_00c26120();
    case 5:
        if (mnToolEffectIndex == 9)
            return 0x12;
        /* fall through */
    case 3:
    case 6:
    case 0x1c:
        return mnCurTool_ffc;
    case 7:
    case 10:
    case 0xf:
        if (IsLeader())
            return 0x11;
        if (FUN_00c22dd0() == 1)
            goto case4_ret;
        if (mnToolEffectIndex == 9)
            return 0x12;
        break;
    case 0x19:
        return 0x0c;
    case 0x1a:
        if (IsLeader())
            return 0x11;
        if (FUN_00c22dd0() == 2)
            goto case4_ret;
        break;
    case 0x16:
        return 0x11;
    case 0x18:
        {
            cConstObj* pObj = (cConstObj*)FUN_00cee330(&mSub_034);
            f32 a = pObj->FUN_00bfc490();
            f32 b = ((cConstObj*)0x1581208)->FUN_0104bdb0();
            return (a < b) ? 0 : 0x13;
        }
    default:
        break;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00c25a50  SP::cSPCreatureCitizen::FUN_00c25a50
// ---------------------------------------------------------------------------
// @ 0x00c25a50
// NOTE: original is 1315 bytes with nested countdown/animation sub-states; the
// reconstruction below captures the main dispatch but is not byte-exact.
bool cSPCreatureCitizen::FUN_00c25a50(void* pTree) {
    i32 local_4c = FUN_00c0f4f0();
    if (*(f32*)((char*)mp_b20 + 0x590) == _HK_REAL_ZERO)
        local_4c = 1;
    i32 animId = (local_4c > 1 ? 1 : 0) + 0x66897b4;
    void* local_48 = FUN_00c0fa70(0x800780, 0);
    if (local_48 == 0) {
        if (mb_1002 != 0) {
            if (AnimationFinished((u32)animId)) {
                if (AnimationFinished(0x2796b30))
                    return true;
            }
            return false;
        }
        if (FUN_00c0e0c0(0x2796b30) == 0) {
            i32 obj = (i32)(intptr_t)FUN_00cee330(&mSub_034);
            if (obj != 0)
                obj += 0x34;
            else
                obj = 0;
            i32 r = PlayAnimationWithTarget(0x2796b30, obj, -1, (i32)(intptr_t)mpInteract_fc8);
            return (r & 0xffffff00) != 0;
        }
        if ((char)WaitForAnimEventOrEnd(0xbfa50b5a, &pTree, 0x2796b30, 0, 1)) {
            mf_1004 = DAT_0168dbb0;
            mf_1008 = DAT_0168dbb4;
            mf_100c = DAT_0168dbb8;
            mb_1002 = 1;
            PerformSocialAction((i32)(intptr_t)FUN_00cee330(&mSub_034), 0xffffffff);
        }
        return false;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00c25f80  SP::cSPCreatureCitizen::FUN_00c25f80
// ---------------------------------------------------------------------------
// @ 0x00c25f80
// NOTE: original is 406 bytes; reconstruction covers the main path only.
void cSPCreatureCitizen::FUN_00c25f80() {
    void* pBT = mpBT_fc4;
    if (pBT == 0)
        return;
    FUN_00c24040(pBT);
    FUN_00c15150(pBT, 1);
    if (pBT == mpBT_fc4)
        mnCurTool_ffc = 0;
}

// ---------------------------------------------------------------------------
// 0x00c26450  SP::cSPCreatureCitizen::ForceOrdersUpdate
// ---------------------------------------------------------------------------
// @ 0x00c26450 SP::cSPCreatureCitizen::ForceOrdersUpdate
// NOTE: original iterates the pending-order queue and drives Play() with a
// per-order-type action bitmask; reconstruction covers the primary switch.
void cSPCreatureCitizen::FUN_00c26450() {
    if (mpOwnerTribe_1014 == 0)
        return;
    cOrder* pOrder = (cOrder*)mpOrders_b4c->FirstPending();
    if (pOrder == 0)
        return;
    if (pOrder->mn_28 == 0 && pOrder->mb_38 != 0) {
        mpOrders_b4c->mPlay_08.FUN_00bc97f0(0x4000, 0, DAT_0146aa40, 0);
        return;
    }
    u32 anim = 0, flags = 0, extra = 0;
    switch (pOrder->mType_00) {
    case 0:  anim = 8; break;
    case 1:  anim = 0x10; extra = DAT_0169ef30; break;
    case 2:  anim = 0x20; break;
    case 3:  anim = 0x40; break;
    case 4:  anim = 0x80; break;
    case 5:  anim = 0x100; break;
    case 6:  anim = 0x200; break;
    case 7:  anim = 0x400; break;
    case 8:  anim = 0x800; break;
    case 9:  anim = 0x2000; break;
    case 10: anim = 0x8000; break;
    case 0xb: anim = 0x20000; break;
    case 0xc: anim = 0x40000; extra = DAT_0169f028; break;
    case 0xd: anim = 0x80000; break;
    case 0xe: anim = 0x100000; break;
    case 0xf: anim = 0x200000; break;
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x17: anim = 0; flags = 0x8000000; break;
    case 0x14: anim = 0x8000000; break;
    case 0x15: anim = 0x1000; break;
    case 0x16: anim = 0x10000000; break;
    case 0x18: anim = 0x1000000; break;
    case 0x19: anim = 0; flags = 0x100000; break;
    case 0x1a: anim = 0x10000; break;
    case 0x1b: anim = 0x4000000; break;
    case 0x1c: anim = 0; flags = 0x8000000; break;
    default:
        return;
    }
    FUN_00c245e0((i32)anim, (i32)flags, DAT_0146aa40, 0, (i32)extra, pOrder->mn_28);
    cOrderPlay* pPlay = (cOrderPlay*)((char*)mpOrders_b4c + 8);
    i32 r = (i32)(intptr_t)pPlay->Play(anim, flags);
    if (r == 0)
        return;
    switch (pOrder->mw_4b) {
    case 1:
    case 7:
    case 10:
        *(u32*)(r + 0xc) = *(u32*)FUN_005727b0((char*)pOrder + 0x39);
        return;
    case 5:
    case 8:
    case 0xb:
        *(u32*)(r + 0xc) = *(u32*)FUN_005727b0((char*)pOrder + 0x39);
        return;
    case 6:
    case 9:
    case 0xc:
        *(u32*)(r + 0xc) = *(u32*)FUN_005727b0((char*)pOrder + 0x39);
        return;
    case 0xd:
    case 0xe:
        *(f32*)(r + 0xc) = *(f32*)FUN_005727e0((char*)pOrder + 0x39);
        return;
    default:
        return;
    }
}