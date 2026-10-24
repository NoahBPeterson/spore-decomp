// Slice s01354df0 -- SporeApp.exe: the one-time initializer that fills the
// Simulator::Attribute descriptor table at 0x0157b7d0.  Ten records of 0x3c
// bytes, one per attribute: mPos, mCurrentFood, mMaxFood, mResupplyRate,
// mCubeIndex, mpFishingHitSphere, mpFishingHotSpot, mStartTime, mbActive,
// mbReplenishing.
//
// Frozen batch gold6.  32-bit x86, MSVC 2008 SP1, flags /O2 /MD /Gy /TP /arch:SSE /GS-.

#include "types.h"

// One record of the Simulator::Attribute table.  +0x0c..+0x14 are never written
// by this function; they ride along inside the 0x3c-byte block copy exactly as
// they do in the original.
struct SimAttr {
    const char* mName;      // +0x00  attribute name
    const char* mDesc;      // +0x04  name token / hash
    int         mIndex;     // +0x08  table index
    int         mPad0;      // +0x0c  never assigned here
    int         mPad1;      // +0x10  never assigned here
    int         mPad2;      // +0x14  never assigned here
    int         mZero0;     // +0x18  zero
    int         mZero1;     // +0x1c  zero
    void*       mDefault;   // +0x20  Simulator::Attribute::DefaultOffset
    void*       mFn0;       // +0x24
    void*       mFn1;       // +0x28
    void*       mFn2;       // +0x2c
    void*       mFn3;       // +0x30
    void*       mFn4;       // +0x34
    void*       mFn5;       // +0x38
};

#define ATTRS  ((SimAttr*)0x0157b7d0)

// ===========================================================================
// @ 0x01354df0  FUN_01354df0
// ===========================================================================
void FUN_01354df0(void)
{
    void* const kDef  = (void*)0x00692ca0;  // Simulator::Attribute::DefaultOffset
    void* const kInit = (void*)0x00b1fbf0;  // UTFWin::Window::Initialize
    SimAttr a;

    a.mName    = (const char*)0x01473fb4;   // "mPos"
    a.mDesc    = (const char*)0x006a7f2f9;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00b6e3a0;
    a.mFn1     = (void*)0x00ac88c0;
    a.mFn2     = (void*)0x006930f0;
    a.mFn3     = (void*)0x00695010;
    a.mFn4     = kInit;
    a.mFn5     = (void*)0x00acbba0;
    a.mIndex   = 0;
    ATTRS[0] = a;

    a.mName    = (const char*)0x01473fa4;   // "mCurrentFood"
    a.mDesc    = (const char*)0x006a7f2fa;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00572810;
    a.mFn1     = (void*)0x00ac88f0;
    a.mFn2     = (void*)0x006930b0;
    a.mFn3     = (void*)0x00694fc0;
    a.mFn4     = kInit;
    a.mFn5     = (void*)0x00acbb80;
    a.mIndex   = 0xc;
    ATTRS[1] = a;

    a.mName    = (const char*)0x01473f98;   // "mMaxFood"
    a.mDesc    = (const char*)0x006a7f2fb;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00572810;
    a.mFn1     = (void*)0x00ac88f0;
    a.mFn2     = (void*)0x006930b0;
    a.mFn3     = (void*)0x00694fc0;
    a.mFn4     = kInit;
    a.mFn5     = (void*)0x00acbb80;
    a.mIndex   = 0x10;
    ATTRS[2] = a;

    a.mName    = (const char*)0x01473f88;   // "mResupplyRate"
    a.mDesc    = (const char*)0x006a7f2fc;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00572810;
    a.mFn1     = (void*)0x00ac88f0;
    a.mFn2     = (void*)0x006930b0;
    a.mFn3     = (void*)0x00694fc0;
    a.mFn4     = kInit;
    a.mFn5     = (void*)0x00acbb80;
    a.mIndex   = 0x14;
    ATTRS[3] = a;

    a.mName    = (const char*)0x01473f7c;   // "mCubeIndex"
    a.mDesc    = (const char*)0x006a7f2fd;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00c8ec20;
    a.mFn1     = (void*)0x00c8ec40;
    a.mFn2     = (void*)0x00c2e4e0;         // UTFWin::ILayoutElement::SetSerializer
    a.mFn3     = (void*)0x00692fb0;         // ?ClearBuffer@@YAXPAPAC@Z
    a.mFn4     = kInit;
    a.mFn5     = (void*)0x00ac8050;
    a.mIndex   = 0x18;
    ATTRS[4] = a;

    a.mName    = (const char*)0x01473f68;   // "mpFishingHitSphere"
    a.mDesc    = (const char*)0x006a7f2fe;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00bd0cb0;
    a.mFn1     = (void*)0x00bca960;         // cAgentOrderManager::ActivateOne
    a.mFn2     = (void*)0x00c2e4e0;
    a.mFn3     = (void*)0x00692fb0;         // ?ClearBuffer@@YAXPAPAC@Z
    a.mFn4     = (void*)0x00b6f550;
    a.mFn5     = (void*)0x00ac8050;
    a.mIndex   = 0x24;
    ATTRS[5] = a;

    a.mName    = (const char*)0x01473f54;   // "mpFishingHotSpot"
    a.mDesc    = (const char*)0x006a7f2ff;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00bed160;
    a.mFn1     = (void*)0x00bca960;
    a.mFn2     = (void*)0x00c2e4e0;
    a.mFn3     = (void*)0x00692fb0;         // ?ClearBuffer@@YAXPAPAC@Z
    a.mFn4     = (void*)0x00b6f550;
    a.mFn5     = (void*)0x00ac8050;
    a.mIndex   = 0x28;
    ATTRS[6] = a;

    a.mName    = (const char*)0x01473f48;   // "mStartTime"
    a.mDesc    = (const char*)0x006a7f419;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00aff840;
    a.mFn1     = (void*)0x00aff870;
    a.mFn2     = (void*)0x00692fd0;         // ?ParseInt64@@YAXPAPBDPA_J@Z
    a.mFn3     = (void*)0x00694ec0;
    a.mFn4     = kInit;
    a.mFn5     = (void*)0x00595a70;
    a.mIndex   = 0x30;
    ATTRS[7] = a;

    a.mName    = (const char*)0x01473f3c;   // "mbActive"
    a.mDesc    = (const char*)0x006a7f41a;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00ac8750;
    a.mFn1     = (void*)0x00ac8780;
    a.mFn2     = (void*)0x00693090;         // ?ParseULong@@YAXPAPBDPAK@Z
    a.mFn3     = (void*)0x00694fa0;
    a.mFn4     = kInit;
    a.mFn5     = (void*)0x0057ce00;
    a.mIndex   = 0x38;
    ATTRS[8] = a;

    a.mName    = (const char*)0x01473f2c;   // "mbReplenishing"
    a.mDesc    = (const char*)0x006a7f41b;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00ac8750;
    a.mFn1     = (void*)0x00ac8780;
    a.mFn2     = (void*)0x00693090;
    a.mFn3     = (void*)0x00694fa0;
    a.mFn4     = kInit;
    a.mFn5     = (void*)0x0057ce00;
    a.mIndex   = 0x39;
    ATTRS[9] = a;
}