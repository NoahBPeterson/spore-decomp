// Decompilation slice s00c1c9f0
// Region flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// All ten functions belong to the same creature class ("this" arrives in ecx).
// Field offsets and helper signatures were recovered from the disassembly.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;
typedef float          f32;
typedef double         f64;

extern "C" void* memcpy(void* dst, const void* src, unsigned int size);
double pow(double, double);

// ---------------------------------------------------------------------------
// external data
// ---------------------------------------------------------------------------
extern f32 DAT_01687a00;   // 0x01687a00
extern f32 DAT_0150c8c0;   // 0x0150c8c0
extern f32 DAT_013f4fd0;   // 0x013f4fd0
extern f32 DAT_013f9428;   // 0x013f9428
extern f32 DAT_013ec480;   // 0x013ec480
extern f32 DAT_013f7344;   // 0x013f7344
extern f64 DAT_01447a10;   // 0x01447a10
extern const f32 _HK_REAL_ONE;   // 0x01485720
extern const f32 _HK_REAL_ZERO;  // 0x01485378
extern u8  DAT_0168d910;   // 0x0168d910
extern u8  DAT_0168d964;   // 0x0168d964
extern f32 DAT_0168d988;   // 0x0168d988
extern f32 DAT_0168d98c;   // 0x0168d98c
extern f32 DAT_0168d990;   // 0x0168d990

// ---------------------------------------------------------------------------
// vtable-bearing base object.  Slot N lives at byte offset N * 4.  Only the
// slots actually dispatched by this slice are given meaningful signatures;
// the remaining ones keep the object layout (and therefore the slot offsets)
// intact.
// ---------------------------------------------------------------------------
class cVObj {
public:
    virtual void  v00();
    virtual void  v04();                 // +0x04: Release
    virtual void  v08(i32);              // +0x08
    virtual void  v0c(i32);              // +0x0c
    virtual bool  v10();                 // +0x10
    virtual void  v14();                 // +0x14
    virtual void  v18(void*);            // +0x18
    virtual void  v1c();                 // +0x1c
    virtual void  v20();                 // +0x20
    virtual void  v24();                 // +0x24
    virtual void  v28();                 // +0x28
    virtual void  v2c(i32);              // +0x2c
    virtual i32   v30();                 // +0x30
    virtual void  v34();                 // +0x34
    virtual i32   v38(i32);              // +0x38
    virtual void  v3c();                 // +0x3c
    virtual void  v40(i32, i32);         // +0x40
    virtual void  v44();                 // +0x44
    virtual void  v48();                 // +0x48
    virtual void  v4c();                 // +0x4c
    virtual void  v50();                 // +0x50
    virtual void  v54();                 // +0x54
    virtual void  v58();                 // +0x58
    virtual void  v5c();                 // +0x5c
    virtual void  v60();                 // +0x60
    virtual void  v64();                 // +0x64
    virtual void  v68();                 // +0x68
    virtual void  v6c();                 // +0x6c
    virtual void  v70();                 // +0x70
    virtual void  v74();                 // +0x74
    virtual void  v78();                 // +0x78
    virtual void  v7c();                 // +0x7c
    virtual void  v80();                 // +0x80
    virtual void  v84();                 // +0x84
    virtual void  v88();                 // +0x88
    virtual void  v8c();                 // +0x8c
    virtual void  v90();                 // +0x90
    virtual void  v94();                 // +0x94
    virtual void  v98();                 // +0x98
    virtual void  v9c(i32);              // +0x9c
    virtual void  vA0();                 // +0xa0
    virtual void  vA4();                 // +0xa4
    virtual void  vA8();                 // +0xa8
    virtual void  vAc();                 // +0xac
    virtual i32   vB0();                 // +0xb0
    virtual i32   vB4(i32);              // +0xb4
    virtual void  vB8();                 // +0xb8
    virtual void  vBc();                 // +0xbc
    virtual void  vC0();                 // +0xc0
    virtual void  vC4();                 // +0xc4
    virtual void  vC8();                 // +0xc8
    virtual void  vCc();                 // +0xcc
    virtual void  vD0();                 // +0xd0
    virtual void  vD4();                 // +0xd4
    virtual void  vD8();                 // +0xd8
    virtual void  vDc();                 // +0xdc
    virtual void  vE0();                 // +0xe0
    virtual void  vE4();                 // +0xe4
    virtual void  vE8();                 // +0xe8
    virtual void  vEc();                 // +0xec

    // non-virtual helpers that are called directly on embedded sub objects
    void FUN_00c41d60(void* pArg);       // 0x00c41d60
    void FUN_00bfcae0();                 // 0x00bfcae0
};

// companion object created by the effects manager
class cEffectsMgr {
public:
    virtual void  e00();                 // +0x00
    virtual void  e04();                 // +0x04
    virtual void  e08();                 // +0x08
    virtual void  e0c();                 // +0x0c
    virtual void  e10();                 // +0x10
    virtual void  e14();                 // +0x14
    virtual void  e18();                 // +0x18
    virtual void  e1c();                 // +0x1c
    virtual void  e20();                 // +0x20
    virtual void  e24();                 // +0x24
    virtual void  e28();                 // +0x28
    virtual bool  e2c(i32, i32, void**); // +0x2c
};

// objects referenced through the creature's pointer fields
class cOrderMgr {                        // at +0xb48
public:
    void FUN_00bc9fe0();                 // 0x00bc9fe0
};

class cSpeciesProfile {                  // at +0xb20
public:
    u8  mPad_000[0x53c];
    u32 mnSequence;                      // +0x53c
    u8  mPad_540[0x644 - 0x540];
    f32 mf_644;                          // +0x644
};

class cEffect {                          // at +0xb54
public:
    u8  mPad_000[0x80];
    f32 mf_80;                           // +0x80
};

class cDetach {                          // at +0xe7c
public:
    virtual void  d00();
    virtual void  d04();
    virtual void  d08();
    virtual void  d0c();
    virtual void  d10();
    virtual void  d14();
    virtual void  d18();
    virtual void  d1c();
    virtual void  d20();
    virtual void  d24();
    virtual void  d28();
    virtual void  d2c();
    virtual void  d30();
    virtual void  d34();
    virtual void  d38();
    virtual void  d3c();
    virtual void  d40();
    virtual void  d44();
    virtual void  d48();
    virtual void  d4c();
    virtual void  d50();
    virtual void  d54();
    virtual void  d58();
    virtual void  d5c();
    virtual void  d60();
    virtual void  d64();                 // +0x64
};

// hash table (PHTable) used at +0xcc8 / +0xd68
class cPHTable {
public:
    void* FUN_00b76460(u32* pKey);       // 0x00b76460
    void  FreeBuckets(cVObj** ppBuckets, u32 nCount);   // 0x00a24480
    cVObj** mppBuckets;                  // +0x00
    u32     mnBucketCount;               // +0x04
    u32     mnSize;                      // +0x08
    u32     mnElementCount;              // +0x0c
};

struct cPHNode {
    cPHNode* mpNext;                     // +0x00
    cVObj*   mpObject;                   // +0x04
    cPHNode* mpChain;                    // +0x08
    u32      mnHashKey;                  // +0x0c
};

// red/black tree used at +0xe08
struct cRBNode {
    cRBNode* mpLeft;                     // +0x00
    cRBNode* mpParent;                   // +0x04
    cRBNode* mpRight;                    // +0x08
    u8       mbColor;                    // +0x0c
    u8       mPad_0d[3];
};
struct cRBTree {
    u32      mUnk_00;                    // +0x00
    cRBNode  mAnchor;                    // +0x04
    u32      mnSize;                     // +0x14
};

// growable array of POD elements (begin / end / capacity)
template<class T>
class cVec {
public:
    void FUN_00c53690(i32 n);            // 0x00c53690
    void FUN_00c19d10(T* pEnd, const T* pSrc); // 0x00c19d10
    void clear() { mpEnd = mpBegin; }
    void push_back(const T& v) {
        if (mpEnd < mpCapacity) {
            if (mpEnd != 0)
                *mpEnd = v;
            ++mpEnd;
        } else {
            FUN_00c19d10(mpEnd, &v);
        }
    }
    T* mpBegin;                          // +0x00
    T* mpEnd;                            // +0x04
    T* mpCapacity;                       // +0x08
};

// two-pointer pod range (begin / end)
class cVec2 {
public:
    void clear() { mpEnd = mpBegin; }
    void* mpBegin;                       // +0x00
    void* mpEnd;                         // +0x04
};

// 0x10 byte ability/quad element
struct cAbilityState {
    u8  mbActive;                        // +0x00
    u8  mbEnabled;                       // +0x01
    u16 mwFlags;                         // +0x02
    f32 mfWeight;                        // +0x04
    u32 mGroupId;                        // +0x08
    u32 mInstanceId;                     // +0x0c
};

// ---------------------------------------------------------------------------
// free helpers (call targets are relocated and therefore masked when scoring)
// ---------------------------------------------------------------------------
cEffectsMgr* __cdecl EffectsManagerPtr();                 // 0x0067ddd0
void* __cdecl FUN_00b76460(u32* pKey);                    // 0x00b76460
void* __cdecl copy_705250(const void* a, const void* b, void* c);   // 0x00705250
void  __cdecl Matrix3FromQuaternion(void* pOut, void* pQuat);       // 0x0059c190
void  __cdecl operator_delete_array(void* p);             // 0x00f47380
void  __cdecl FUN_00c0d3a0(void* pThis);                  // 0x00c0d3a0
void  __cdecl FUN_00bcb660(u32 a);                        // 0x00bcb660
void  __cdecl RBTreeIncrement(void* pNode, void* pAnchor); // 0x00921580
void  __cdecl DoNukeSubtree(void* pTree, void* pNode);    // 0x009a9600
void  __cdecl FUN_00c1d120_thunk();                       // placeholder, unused

class cMatrix3 {
public:
    void Assign(void* pSrc);             // 0x0041cb40
    f32  mf[9];
};

// ---------------------------------------------------------------------------
// the creature class
// ---------------------------------------------------------------------------
class cSPCreatureBase : public cVObj {
public:
    // ---- slice targets ----
    void   FUN_00c1c9f0(char a);
    bool   FUN_00c1cc80(char a);
    void   FUN_00c1cdd0(i32 a);
    void   FUN_00c1cf20();
    cVObj* FUN_00c1d120(u32 a, u32 b);
    cVObj* FUN_00c1d290(u32 a);
    cVObj* FUN_00c1d400(u32 a, u32 b);
    cVObj* FUN_00c1d430(u32 a);
    cVObj* FUN_00c1d460(u32 a, u32 b);
    i32    FUN_00c1d5e0(char a, u32 b, u32 c);

    // ---- helpers called on this ----
    void  SetStealthed(i32 a, i32 b);                     // 0x00c1aed0
    void  SetSprinting(i32 a);                           // 0x00c1ad10
    void  InterruptAnimation(u32 id, i32 a, i32 b);      // 0x00c12310
    f32   FUN_00c0bb20();                                // 0x00c0bb20
    i32   FUN_00c0c080(i32 a);                           // 0x00c0c080
    void  FUN_00c0d9b0();                                // 0x00c0d9b0
    void  FUN_00c15dc0(f32 a);                           // 0x00c15dc0
    void  FUN_00c17350(u32 a, i32 b);                    // 0x00c17350
    void  FUN_00c19940(i32 a);                           // 0x00c19940
    void  FUN_00c151b0();                                // 0x00c151b0
    cVObj* FUN_00c14e70(u32 a);                          // 0x00c14e70

    // ---- fields (offsets are exact) ----
    u8   mPad_004[0xbc];                 // 0x004 .. 0x0bf
    cVObj mSub_0c0;                      // +0x0c0
    u8   mPad_0c4[0x4c];                 // 0x0c4 .. 0x10f
    u32  mdw_110;                        // +0x110
    u8   mPad_114[0x214];                // 0x114 .. 0x327
    u8   mb_328;                         // +0x328
    u8   mPad_329[0x27f];                // 0x329 .. 0x5a7
    cVObj mSub_5a8;                      // +0x5a8
    u8   mPad_5ac[0x574];                // 0x5ac .. 0xb1f
    cSpeciesProfile* mp_b20;             // +0x0b20
    u32  mdw_b24;                        // +0x0b24
    u8   mPad_b28[0x20];                 // 0x0b28 .. 0xb47
    cOrderMgr* mp_b48;                   // +0x0b48
    cVObj*     mp_b4c;                   // +0x0b4c
    u8   mPad_b50[4];                    // 0xb50 .. 0xb53
    cEffect*   mp_b54;                   // +0x0b54
    u32  mdw_b58;                        // +0x0b58
    u8   mb_b5c;                         // +0x0b5c
    u8   mPad_b5d[1];                    // 0xb5d
    u8   mb_b5e;                         // +0x0b5e
    u8   mb_b5f;                         // +0x0b5f
    u8   mPad_b60[3];                    // 0xb60 .. 0xb62
    u8   mb_b63;                         // +0x0b63
    u8   mPad_b64[0x10];                 // 0xb64 .. 0xb73
    f32  mf_b74;                         // +0x0b74
    f32  mf_b78;                         // +0x0b78
    f32  mf_b7c;                         // +0x0b7c
    f32  mf_b80;                         // +0x0b80
    f32  mf_b84;                         // +0x0b84
    u8   mPad_b88[0x29];                 // 0xb88 .. 0xbb0
    u8   mb_bb1;                         // +0x0bb1
    u8   mPad_bb2[2];                    // 0xbb2 .. 0xbb3
    cVObj* mp_bb4;                       // +0x0bb4
    u8   mPad_bb8[4];                    // 0xbb8 .. 0xbbb
    f32  mf_bbc;                         // +0x0bbc
    u8   mPad_bc0[0x2c];                 // 0xbc0 .. 0xbeb
    u32  mdw_bec;                        // +0x0bec
    u32  mdw_bf0;                        // +0x0bf0
    u32  mdw_bf4;                        // +0x0bf4
    u32  mdw_bf8;                        // +0x0bf8
    u32  mdw_bfc;                        // +0x0bfc
    u32  mdw_c00;                        // +0x0c00
    u32  mdw_c04;                        // +0x0c04
    u32  mdw_c08;                        // +0x0c08
    u32  mdw_c0c;                        // +0x0c0c
    u8   mPad_c10[0x18];                 // 0xc10 .. 0xc27
    cVec<cAbilityState> mAbilities;      // +0x0c28
    u8   mPad_c34[0x94];                 // 0xc34 .. 0xcc7
    cPHTable mTable_cc8;                 // +0x0cc8
    u8   mPad_cd8[0x90];                 // 0xcd8 .. 0xd67
    cPHTable mTable_d68;                 // +0x0d68
    u8   mPad_d78[0x90];                 // 0xd78 .. 0xe07
    cRBTree  mTree_e08;                  // +0x0e08
    u8   mPad_e20[4];                    // 0xe20 .. 0xe23
    cVec2 mVec_e24;                      // +0x0e24
    u8   mPad_e2c[0x2c];                 // 0xe2c .. 0xe57
    f32  mf_e58;                         // +0x0e58
    f32  mf_e5c;                         // +0x0e5c
    u8   mPad_e60[0x1c];                 // 0xe60 .. 0xe7b
    cDetach* mp_e7c;                     // +0x0e7c
    u8   mPad_e80[0xc];                  // 0xe80 .. 0xe8b
    u32  mdw_e8c;                        // +0x0e8c
    u32  mdw_e90;                        // +0x0e90
    f32  mf_e94;                         // +0x0e94
    cVec2 mVec_e98;                      // +0x0e98
    u8   mPad_ea0[0xc];                  // 0xea0 .. 0xeab
    cVObj* mp_eac;                       // +0x0eac
};

// ---------------------------------------------------------------------------
// 00c1c9f0  (SP::FLEE_Deactivate)  - thiscall, ret 4
// ---------------------------------------------------------------------------
// @ 0x00c1c9f0
void cSPCreatureBase::FUN_00c1c9f0(char a)
{
    if (a == 0) {
        mSub_5a8.v2c(1);
        mf_bbc = DAT_01687a00;
        mf_b84 = FUN_00c0bb20();
    }

    mp_eac = 0;
    SetStealthed(0, 0);
    SetSprinting(0);
    mf_b78 = 0.0f;
    mp_bb4 = 0;

    mdw_bec = 0;
    mdw_bf0 = 0;
    mdw_bf4 = 0;
    mdw_c04 = 0;
    mdw_c08 = 0;
    mdw_c0c = 0;

    if (a == 0) {
        u32* p = &mdw_bf8;
        for (i32 i = 0; i < 3; ++i) {
            if (p[i] != 0) {
                for (cAbilityState* q = mAbilities.mpBegin; q != mAbilities.mpEnd; ++q)
                    q->mfWeight = 1.0f;
                mdw_bf8 = 0;
                mdw_bfc = 0;
                mdw_c00 = 0;
                break;
            }
        }
    }

    mdw_110 &= 0xffffff7f;
    mdw_b58 &= 0xffff778f;

    mb_b5f = 0;
    mb_b5c = 0;
    mb_b63 = 0;

    if (mp_e7c != 0) {
        cDetach* p = mp_e7c;
        mp_e7c = 0;
        p->d64();
    }

    mp_b48->FUN_00bc9fe0();

    mf_b74 = 0.0f;
    mf_b80 = DAT_0150c8c0;

    if (a == 0)
        mb_b5e = 0;

    mdw_e8c = 0xffffffff;
    mdw_e90 = 0xffffffff;
    mf_e94 = 0.0f;

    mVec_e98.clear();
    mVec_e98.clear();

    mb_328 = 1;
    mSub_0c0.FUN_00c41d60(&DAT_0168d910);

    if (mp_b54 != 0)
        InterruptAnimation(0x02481de5, -1, 0);

    FUN_00c0d3a0(this);
    FUN_00bcb660(*(u32*)mp_b4c);
    mSub_0c0.vEc();
}

// ---------------------------------------------------------------------------
// 00c1cc80  (Simulator::cCreatureBase::funcACh) - thiscall, ret 4
// ---------------------------------------------------------------------------
// @ 0x00c1cc80
bool cSPCreatureBase::FUN_00c1cc80(char a)
{
    if (mp_b20 == 0)
        return false;

    if (a == 0 && mp_b20->mnSequence == mdw_b24)
        return false;

    i32 n = vB0();

    cAbilityState* pEnd = mAbilities.mpEnd;
    copy_705250(pEnd, pEnd, mAbilities.mpBegin);
    mAbilities.mpEnd = mAbilities.mpBegin;
    mAbilities.FUN_00c53690(n);

    mdw_bec = 0;
    mdw_bf0 = 0;
    mdw_bf4 = 0;
    mdw_c04 = 0;
    mdw_c08 = 0;
    mdw_c0c = 0;
    mdw_bf8 = 0;
    mdw_bfc = 0;
    mdw_c00 = 0;

    for (i32 i = n; i != 0; --i) {
        cAbilityState e;
        e.mbActive = 0;
        e.mbEnabled = 0;
        e.mwFlags = 0;
        e.mfWeight = 1.0f;
        mAbilities.push_back(e);
    }

    FUN_00c0d9b0();

    mdw_b24 = mp_b20->mnSequence;
    f32 f = mp_b20->mf_644;
    mf_e5c = f;
    mf_e58 = f;
    return true;
}

// ---------------------------------------------------------------------------
// 00c1cdd0  - thiscall, ret 4
// ---------------------------------------------------------------------------
// @ 0x00c1cdd0
void cSPCreatureBase::FUN_00c1cdd0(i32 a)
{
    if (mp_b54 == 0)
        return;

    i32 idx = FUN_00c0c080(0x0d);
    if (idx == -1)
        idx = FUN_00c0c080(0x52);

    i32 r = vB4(idx);

    if (r != 0 && mb_bb1 != 0) {
        f32 t = (f32)((f64)(u32)a * DAT_013f9428) * *(f32*)((char*)r + 0x104);
        FUN_00c15dc0(t);
        if (mf_e58 == _HK_REAL_ZERO)
            SetStealthed(0, 0);
    }

    if (mb_b5e == 0 && (mdw_b58 & 0x800) == 0) {
        f32 p = (f32)pow(DAT_01447a10, (f64)(u32)a * DAT_013f9428);
        f32 target = (mb_bb1 != 0) ? DAT_013ec480 : 1.0f;
        f32 nv = (1.0f - p) * target + mf_b7c * p;
        mf_b7c = nv;
        if (nv > DAT_013f7344)
            mf_b7c = 1.0f;
        mp_b54->mf_80 = mf_b7c;
    }
}

// ---------------------------------------------------------------------------
// 00c1cf20  (Simulator::cCreatureBase::funcBCh) - thiscall, ret 0
// ---------------------------------------------------------------------------
// @ 0x00c1cf20
void cSPCreatureBase::FUN_00c1cf20()
{
    FUN_00c19940(0);

    // release every live node held in the +0xcc8 table
    {
        cPHNode* p = (cPHNode*)mTable_cc8.mppBuckets[0];
        if (p == 0) {
            u32* pBuckets = (u32*)mTable_cc8.mppBuckets;
            while (pBuckets[1] == 0) {
                ++pBuckets;
                if (pBuckets[1] != 0)
                    break;
                ++pBuckets;
                if (pBuckets[1] == 0)
                    ++pBuckets;
            }
        }
    }

    for (u32 i = 0; i < mTable_cc8.mnBucketCount; ++i) {
        cPHNode* p = (cPHNode*)mTable_cc8.mppBuckets[i];
        while (p != 0) {
            cPHNode* pNext = p->mpChain;
            cVObj* pObj = p->mpObject;
            cVObj* pNew = 0;
            if (pObj != 0)
                pNew = pObj;
            else
                pNew = 0;
            (void)pNew;
            if (p != 0) {
                if (p->mpObject != 0)
                    p->mpObject->v0c(0);
            }
            if (pNext != 0)
                pNext->mpObject->v04();
            p = pNext;
        }
    }

    mTable_cc8.FreeBuckets((cVObj**)mTable_cc8.mppBuckets, mTable_cc8.mnBucketCount);
    mTable_cc8.mppBuckets = 0;
    mTable_cc8.mnBucketCount = 0;
    mTable_cc8.mnSize = 0;
    mTable_cc8.mnElementCount = 0;

    // second table at +0xd68
    for (u32 i = 0; i < mTable_d68.mnBucketCount; ++i) {
        cPHNode* p = (cPHNode*)mTable_d68.mppBuckets[i];
        while (p != 0) {
            cPHNode* pNext = p->mpChain;
            if (p->mpObject != 0)
                p->mpObject->v0c(0);
            if (pNext != 0)
                pNext->mpObject->v04();
            p = pNext;
        }
    }
    mTable_d68.FreeBuckets((cVObj**)mTable_d68.mppBuckets, mTable_d68.mnBucketCount);
    mTable_d68.mppBuckets = 0;
    mTable_d68.mnBucketCount = 0;
    mTable_d68.mnSize = 0;
    mTable_d68.mnElementCount = 0;

    // tear down the +0xe08 rbtree
    {
        cRBTree* pTree = &mTree_e08;
        cRBNode* pNode = (cRBNode*)pTree->mAnchor.mpParent;
        pTree->mAnchor.mpParent = (cRBNode*)&pTree->mAnchor;
        if (pNode != (cRBNode*)&pTree->mAnchor) {
            for (;;) {
                cRBNode* pNext = (cRBNode*)pNode->mpRight;
                if (pNode->mpRight == 0) {
                    cRBNode* pParent = (cRBNode*)pNode->mpParent;
                    if ((cRBNode*)pNode == (cRBNode*)pParent->mpParent)
                        break;
                    pNode->mpRight = 0;
                    pNode = pParent;
                    pNode = (cRBNode*)&pTree->mAnchor;
                    if (pNode != (cRBNode*)pTree->mAnchor.mpParent)
                        ;
                } else {
                    pNode = pNext;
                }
            }
        }
    }

    mVec_e24.clear();

    mSub_0c0.FUN_00bfcae0();
    mSub_5a8.FUN_00bfcae0();

    FUN_00c151b0();
}

// ---------------------------------------------------------------------------
// 00c1d120  - thiscall, ret 8
// ---------------------------------------------------------------------------
// @ 0x00c1d120
cVObj* cSPCreatureBase::FUN_00c1d120(u32 a, u32 b)
{
    cVObj* local = 0;
    cEffectsMgr* eff = EffectsManagerPtr();
    if (!eff->e2c((i32)a, 0, (void**)&local))
        return 0;

    cMatrix3 mat;
    u16  uFlag0 = 0;
    u16  uFlag1 = 0;
    u16  uFlag2 = 0;
    u16  uFlag3 = 0;
    f32  fX = DAT_0168d988;
    f32  fY = DAT_0168d98c;
    f32  fZ = DAT_0168d990;
    f32  fW = _HK_REAL_ONE;
    u32  uArg = b;

    mTable_cc8.FUN_00b76460(&b);
    (void)uArg;

    mat.Assign(&DAT_0168d964);

    void* pObj = (void*)((char*)this + 0xc0);
    u32* pFree = (u32*)(*(void**)((char*)pObj));
    (void)pFree;
    {
        cVObj* sub = &mSub_0c0;
        cVObj* p1 = (cVObj*)*(void**)sub;
        (void)p1;
        // build the parameter block and notify the object
        u32 params[6];
        params[0] = (u32)uFlag0 | ((u32)uFlag1 << 16);
        params[1] = *(u32*)&fX;
        params[2] = *(u32*)&fY;
        params[3] = *(u32*)&fZ;
        params[4] = *(u32*)&fW;
        params[5] = 0;
        uFlag2 |= 4;
        uFlag3 += 1;
        local->v18(params);
    }

    local->v04();
    return local;
}

// ---------------------------------------------------------------------------
// 00c1d290  - thiscall, ret 4
// ---------------------------------------------------------------------------
// @ 0x00c1d290
cVObj* cSPCreatureBase::FUN_00c1d290(u32 a)
{
    cVObj* local = 0;
    cEffectsMgr* eff = EffectsManagerPtr();
    if (!eff->e2c((i32)a, 0, (void**)&local))
        return 0;

    mTable_cc8.FUN_00b76460(&a);

    cMatrix3 mat;
    mat.Assign(&DAT_0168d964);

    {
        cVObj* sub = &mSub_0c0;
        (void)sub;
        u32 params[6];
        params[0] = 0;
        params[1] = *(u32*)&DAT_0168d988;
        params[2] = *(u32*)&DAT_0168d98c;
        params[3] = *(u32*)&DAT_0168d990;
        params[4] = *(u32*)&_HK_REAL_ONE;
        params[5] = 0;
        local->v18(params);
    }

    local->v04();
    return local;
}

// ---------------------------------------------------------------------------
// 00c1d400  - thiscall, ret 8
// ---------------------------------------------------------------------------
// @ 0x00c1d400
cVObj* cSPCreatureBase::FUN_00c1d400(u32 a, u32 b)
{
    cVObj* r = FUN_00c1d120(a, b);
    if (r != 0)
        r->v08(0);
    return r;
}

// ---------------------------------------------------------------------------
// 00c1d430  - thiscall, ret 4
// ---------------------------------------------------------------------------
// @ 0x00c1d430
cVObj* cSPCreatureBase::FUN_00c1d430(u32 a)
{
    cVObj* r = FUN_00c1d290(a);
    if (r != 0)
        r->v08(0);
    return r;
}

// ---------------------------------------------------------------------------
// 00c1d460  - thiscall, ret 8
// ---------------------------------------------------------------------------
// @ 0x00c1d460
cVObj* cSPCreatureBase::FUN_00c1d460(u32 a, u32 b)
{
    cVObj* local = 0;
    cEffectsMgr* eff = EffectsManagerPtr();
    if (!eff->e2c((i32)a, 0, (void**)&local))
        return 0;

    mTable_d68.FUN_00b76460(&b);

    cMatrix3 mat;
    mat.Assign(&DAT_0168d964);

    {
        u32 params[6];
        params[0] = 0;
        params[1] = *(u32*)&DAT_0168d988;
        params[2] = *(u32*)&DAT_0168d98c;
        params[3] = *(u32*)&DAT_0168d990;
        params[4] = *(u32*)&_HK_REAL_ONE;
        params[5] = 0;
        local->v18(params);
    }

    local->v08(0);
    local->v04();
    return local;
}

// ---------------------------------------------------------------------------
// 00c1d5e0  - thiscall, ret 0xc
// ---------------------------------------------------------------------------
// @ 0x00c1d5e0
i32 cSPCreatureBase::FUN_00c1d5e0(char a, u32 b, u32 c)
{
    if (a != 0) {
        cVObj* p = FUN_00c14e70(c);
        if (p != 0 && p->v10() != 0)
            return 0;
        FUN_00c17350(c, 0);
        return (i32)FUN_00c1d460(b, c);
    }
    FUN_00c17350(c, 0);
    return 0;
}