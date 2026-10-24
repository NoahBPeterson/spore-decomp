// Slice s00ca2210: 0x00CA2210..0x00CA2E80.  SP::cVehicle interactable /
// locomotion-selection helpers.
//
//  0x00ca2210  terrain-occupancy scan over a candidate position   (345 B)
//  0x00ca2370  navigation candidate search (large)                (1316 B)
//  0x00ca28a0  ray / sphere probe against the planet model        (573 B)
//  0x00ca2ae0  SP::cVehicle::CreateDefaultTool                    (928 B)
//  0x00ca2e80  locomotion-select / tool install                   (427 B)
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- shared types

void* __cdecl GetCurrentGameMode(void);   // 0x00b5b800  SP::GetCurrentGameMode
void* __cdecl EAllocNew(int size, const char* file, int a, int b, int c, int d); // 0x00f473a0

// Simulation-mode singleton sentinel (compare target of GetCurrentGameMode()).
#define SIM_MODE_ADDR ((void*)0x01654c10)

// State object referenced through +0xaf0 (has a flag word at +0x5fc).
struct cVehicleState {
    char  mPad0000[0x5fc];
    int   mFlags;              // +0x5fc
};

// Locomotion / tool manager embedded at +0x34.
struct cToolManager {
    void  FUN_00c421b0(void* p);   // 0x00c421b0
    void  FUN_00c43fe0(void* p);   // 0x00c43fe0
};

// Objects installed into the tool manager.
struct cFlyingLocomotion {
    cFlyingLocomotion* FUN_00caded0();   // 0x00caded0  (constructor)
};

struct cAllocPath {            // 0xd4 bytes
    void*  mVtbl;              // +0x00
    char   mPad04[4];
    void*  mVtbl8;             // +0x08
    int    mField0c;           // +0x0c
    void*  mOwner;             // +0x10
    int    mType;              // +0x14
    float  mVal18;             // +0x18
    char   mFlag1c;            // +0x1c
    char   mFlag1d;            // +0x1d
    char   mPad1e[0xd4 - 0x1e];
};

struct cAllocDriving {         // 0x10 bytes
    void*  mVtbl;              // +0x00
    char   mPad04[4];
    void*  mVtbl8;             // +0x08
    int    mField0c;           // +0x0c
};

// ---------------------------------------------------------------- cVehicle

struct cVehicle {
    char            mPad00[0x34];
    cToolManager    mToolMgr;         // +0x34
    char            mPad35[0x21c - 0x35];
    float           m21c;             // +0x21c
    char            mPad220[0x224 - 0x220];
    int             m224;             // +0x224
    char            mPad228[0xaf0 - 0x228];
    cVehicleState*  mAf0;             // +0xaf0
    char            mPadAf4[0xb1c - 0xaf4];
    int             mB1c;             // +0xb1c
    char            mPadB20[0xd04 - 0xb20];
    int             mD04;             // +0xd04

    bool  FUN_00ca2210(void* p);            // 0x00ca2210
    bool  FUN_00ca2370(void);               // 0x00ca2370
    void  FUN_00ca28a0(void* p);            // 0x00ca28a0
    void  CreateDefaultTool(void);          // 0x00ca2ae0
    void  FUN_00ca2e80(void);               // 0x00ca2e80
};

// ---------------------------------------------------------------- 0x00ca2210

// @ 0x00ca2210
bool cVehicle::FUN_00ca2210(void* p)
{
    /* terrain-occupancy scan; not reconstructed */
    (void)p;
    return false;
}

// ---------------------------------------------------------------- 0x00ca2370

// @ 0x00ca2370
bool cVehicle::FUN_00ca2370(void)
{
    /* navigation candidate search (large); not reconstructed */
    return false;
}

// ---------------------------------------------------------------- 0x00ca28a0

// @ 0x00ca28a0
void cVehicle::FUN_00ca28a0(void* p)
{
    /* ray / sphere probe; not reconstructed */
    (void)p;
}

// ---------------------------------------------------------------- 0x00ca2ae0

// @ 0x00ca2ae0
void cVehicle::CreateDefaultTool(void)
{
    /* tool selection (large); not reconstructed */
}

// ---------------------------------------------------------------- 0x00ca2e80

// @ 0x00ca2e80
void cVehicle::FUN_00ca2e80(void)
{
    void* gm = GetCurrentGameMode();
    bool  flag = (gm == SIM_MODE_ADDR);
    float f;

    switch (mB1c) {
    case 1:
        f = *(float*)0x0169a26c;
        m224 = 6;
        break;
    case 2:
        m224 = 5;
        mToolMgr.FUN_00c43fe0((void*)0x00b493e0);
        if (flag) {
            mAf0->mFlags |= 0x20;
            f = *(float*)0x0157c724;
        } else {
            mAf0->mFlags |= 0x20;
            f = *(float*)0x0169a274;
        }
        break;
    default:
        m224 = 7;
        f = mD04 ? *(float*)0x0169a270 : *(float*)0x0169a268;
        break;
    }

    if (flag) {
        m21c = (*(float*)0x0157c708) * f;
        if (mB1c == 2) {
            cFlyingLocomotion* q = (cFlyingLocomotion*)EAllocNew(0x3c, (const char*)0x01474adc, 0, 0, 0, 0);
            if (q != 0)
                mToolMgr.FUN_00c421b0(q->FUN_00caded0());
            else
                mToolMgr.FUN_00c421b0((void*)0);
            return;
        }
    } else {
        m21c = f;
        cAllocPath* p = (cAllocPath*)EAllocNew(0xd4, (const char*)0x01474ab8, 0, 0, 0, 0);
        if (p != 0) {
            p->mVtbl   = (void*)0x01474a88;
            p->mVtbl8  = (void*)0x01475114;
            p->mField0c = 0;
            p->mOwner  = this;
            p->mType   = mB1c;
            p->mVal18  = 0.0f;
            p->mFlag1c = 0;
            p->mFlag1d = 0;
            mToolMgr.FUN_00c421b0(p);
        } else {
            mToolMgr.FUN_00c421b0((void*)0);
        }
        return;
    }

    cAllocDriving* d = (cAllocDriving*)EAllocNew(0x10, (const char*)0x01474a98, 0, 0, 0, 0);
    if (d != 0) {
        d->mVtbl    = (void*)0x01474a34;
        d->mVtbl8   = (void*)0x01475114;
        d->mField0c = 0;
        mToolMgr.FUN_00c421b0(d);
    } else {
        mToolMgr.FUN_00c421b0((void*)0);
    }
}