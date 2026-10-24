// Slice s0104bcc0 -- SP::cSPSpaceToolData (the space-tool game-data object), the base
// SP::cSPSpaceInventoryItem::UpdateTuning tuning decoder, the SP::cSPEditorVerbIconTray
// verb-icon registration/table and a handful of small tool accessors that share this
// address range.
//
// Layouts are the retail ones read from the disassembly.  The dev PDB has moved a few
// members, so the retail offsets below are authoritative:
//   * cSPSpaceToolData keeps three vtable pointers (+0x00/+0x08/+0x0c), the property-list
//     at +0x30, the item id triple at +0x5c, the ammo counter at +0x7c, an auto-handler
//     flag byte at +0x80, four cGonzagoTimers at +0x88..+0x108, the charge/effect
//     AutoRefCounts at +0x108..+0x12c and many tuning floats through +0x298.
//   * cSPEditorVerbIconTray holds 26 cStrings at +0x74 (stride 0x14) followed by an event
//     registration record at +0x27c.
#include "types.h"

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef int                i32;
typedef long long          i64;
typedef unsigned long long u64;
typedef unsigned int       size_t;
typedef unsigned long      uptr;
typedef float              f32;
typedef double             f64;

// --------------------------------------------------------------------------- cString
struct cString {
    u8 mData[0x14];
    void ctorRaw();                       // 0x006b5060
    void dtorRaw();                       // 0x006b5240
    const unsigned short* GetText();      // 0x006b55c0
    bool Load(u32 group, u32 id, int flag);// 0x006b54b0
};

// --------------------------------------------------------------------------- timers
struct cSPTimer {
    u8 mData[0x20];
    bool IsRunning();                     // 0x00feba90
    u64  GetElapsedTime();                // 0x00bc3190
};
struct cGonzagoTimer : cSPTimer {
    void ctorRaw();                       // 0x00b63890
    void dtorRaw();                       // 0x00b638b0
};

// ---------------------------------------------------------- property list / properties
struct Property {
    void*  mpValue;                       // +0x00
    u8     pad04[0x0c];
    u8     mFlags10;                      // +0x10
    u8     pad11;
    u16    mType12;                       // +0x12
    float* GetFloat();                    // 0x0041ea70
    u32*   GetUInt();                     // 0x0041ea00
    bool*  GetBool();                     // 0x0041e920
};

struct cPropertyList {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual bool FindProperty(u32 id, Property** ppOut);  // +0x24
};

// ------------------------------------------------------------------- item identity
struct cItemID { u32 instanceID; u32 typeID; u32 groupID; };

// ------------------------------------------------- generic ref-counted / interface obj
// Every AutoRefCount / IInterface object accessed here begins with a vtable pointer; the
// offsets used by this slice are the ones the retail code calls.
struct cToolRef {
    void** mpVftbl;                                            // +0x00
    __forceinline void RefCountRelease()                        // vtable +0x04
    { ((void (__thiscall*)(void*))mpVftbl[0x04 / 4])(this); }
    __forceinline void EffectRelease()                          // vtable +0xc0
    { ((void (__thiscall*)(void*))mpVftbl[0xc0 / 4])(this); }
    __forceinline void* ActivateVfx(void* arg)                  // vtable +0xb8
    { return ((void* (__thiscall*)(void*, void*))mpVftbl[0xb8 / 4])(this, arg); }
    __forceinline u32 ActivateFlag(u32 flag)                    // 0x00c38990
    { return ((u32 (__thiscall*)(void*, u32))mpVftbl[-1])(this, flag); }
    u32 OnActivate(u32 flag);                                   // 0x00c38990
};

// generic "object with a vtable at 0" used for the target / stream interfaces
struct cIface {
    void** mpVftbl;                                             // +0x00
    __forceinline void* Call(u32 byteOff)
    { return ((void* (__thiscall*)(void*))mpVftbl[byteOff / 4])(this); }
    __forceinline void* Call1(u32 byteOff, u32 a)
    { return ((void* (__thiscall*)(void*, u32))mpVftbl[byteOff / 4])(this, a); }
};
typedef cIface cOutStream;

// --------------------------------------------------------- messaging / terrain helpers
struct cMessagingServer {
    void** mpVftbl;                                             // +0x00
    __forceinline void RegisterEvent(void* self, u32 evt)       // vtable +0x24
    { ((void (__thiscall*)(void*, u32))mpVftbl[0x24 / 4])(self, evt); }
};

struct cTerrainSphere { u32 Check(); };                         // 0x00c75650
struct cTerrainEditor {
    cTerrainSphere* GetCurrentTerrainSphere();                   // 0x00f67d90
};

// ----------------------------------------------------------------------- dtor helpers
struct cPlanetModel {
    u8     pad00[0x24];
    void*  mpAnchor24;                       // +0x24
};

// --------------------------------------------------------------------------- serializer
struct cVarListSerializer {
    u8   mData[0xa14];
    void ctorRaw(void* owner, u32 a, u32 b);                     // 0x00692f90
    bool Serialize(cOutStream* s);                               // 0x00692900
};

// --------------------------------------------------------------------------- externs
void* __cdecl PlanetModel();                                  // 0x00b3d350
void* __cdecl NounManager();                                  // 0x00b3d300
void* __cdecl GetCurrentGameMode();                           // 0x00b5b800
void* __cdecl GetUniverseContext();                           // 0x01021080
u32   __cdecl GetPlayerEmpireID();                            // 0x01021090
void* __cdecl FUN_01021260();                                 // 0x01021260
bool  __cdecl IsHostileToAll(void* p);                        // 0x0102c600
void* __cdecl FUN_00b67740(void* p);                          // 0x00b67740
void* __cdecl GetUFOSimulator(u32 p);                         // 0x00ffbe50
bool  __cdecl cSPSpaceCommCanTarget(void* a, void* b);        // 0x0102aa50
void  __cdecl GetPropertyAsIntArray(u32 id, u32 tag, i32* pCount, void** ppArr); // 0x006a07d0
void* __cdecl EA_Messaging_GetServer();                       // 0x00883860
void  __cdecl RegisterStaticRegistrations();                  // 0x01055890
u32   __fastcall FUN_00bfc480(void* self);                    // 0x00bfc480
void  __cdecl WriteUint32(void* s, const u32* v, int n, int flag); // 0x0093aa70

// --------------------------------------------------------------- referenced globals
extern cItemID gShieldItemID;                                 // 0x016e14d0
extern cItemID gCloakItemID;                                  // 0x016e15e4
extern cItemID gRallyCallItemID;                              // 0x016e17a0
extern cItemID gSoothingSongItemID;                           // 0x016e174c
extern u8      gGameMode01654c05;                             // 0x01654c05
extern u32     gVerbEventIDs[0xe];                            // 0x0149acd4
extern u8      gChargePropertyId_013f94d4;                    // 0x013f94d4

// toolbar/animation globals read by the ctor
extern u32 gToolGlobalD8;                                     // 0x016e12d8
extern u32 gToolGlobalDC;                                     // 0x016e12dc
extern u32 gToolGlobalE0;                                     // 0x016e12e0

// vtables (addresses used as immediate constants by the ctor / dtor)
extern u8 vtbl_cSpaceToolData;                                // 0x0149ad40
extern u8 vtbl_cSpaceToolData8;                               // 0x0149ad38
extern u8 vtbl_cSpaceToolDataC;                               // 0x0149ad14

namespace SP {

struct cSPSpaceInventoryItem;

// ===========================================================================
// SP::cSPSpaceToolData
// ===========================================================================
struct cSPSpaceToolData {
    void*              mpVftable0;         // +0x00
    u32                mPad04;             // +0x04
    void*              mpVftable8;         // +0x08
    void*              mpVftableC;         // +0x0c
    u8                 mPad10[0x20];       // +0x10 .. +0x2f
    cPropertyList*     mpPropList30;       // +0x30
    u8                 mPad34[0x28];       // +0x34 .. +0x5b
    cItemID            mItemID;            // +0x5c
    u8                 mPad68[0x14];       // +0x68 .. +0x7b
    i32                mAmmo7c;            // +0x7c
    u8                 mFlag80;            // +0x80
    u8                 mPad81[7];          // +0x81 .. +0x87
    cGonzagoTimer      mIsInUse;           // +0x88
    cGonzagoTimer      mRechargeTimer;     // +0xa8
    cGonzagoTimer      mAutoFireTimer;     // +0xc8
    cGonzagoTimer      mChargeTimer;       // +0xe8
    cToolRef*          mEffect108;         // +0x108
    cToolRef*          mEffect10c;         // +0x10c
    cToolRef*          mEffect110;         // +0x110
    cToolRef*          mEffect114;         // +0x114
    cToolRef*          mEffect118;         // +0x118
    i32                mField11c;          // +0x11c
    cToolRef*          mField120;          // +0x120
    cToolRef*          mField124;          // +0x124
    cToolRef*          mField128;          // +0x128
    cToolRef*          mField12c;          // +0x12c
    u8                 mPad130[0x10];      // +0x130 .. +0x13f
    cToolRef*          mField140;          // +0x140
    f32                mField144;          // +0x144
    f32                mField148;          // +0x148
    f32                mField14c;          // +0x14c
    u8                 mField150;          // +0x150
    u8                 mPad151[3];         // +0x151 .. +0x153
    f32                mField154;          // +0x154
    f32                mField158;
    f32                mField15c;
    f32                mField160;
    f32                mField164;
    f32                mField168;
    cToolRef*          mField16c;          // +0x16c
    cToolRef*          mField170;          // +0x170
    union {
        u32 mFlags174;                     // +0x174 (bit flags)
        struct { u16 mFlagsLow174; u8 mByte176; u8 mByte177; } mFlagsBytes;
    };
    u32                mField178;          // +0x178
    u32                mField17c;          // +0x17c
    i32                mField180;          // +0x180
    i32                mField184;          // +0x184
    u32                mField188;          // +0x188
    u32                mUpgradeInstance;   // +0x18c
    u32                mField190;          // +0x190
    u32                mField194;          // +0x194
    u32                mField198;          // +0x198
    i32                mField19c;          // +0x19c
    i32                mLimit1a0;          // +0x1a0
    u32                mField1a4;          // +0x1a4
    f32                mField1a8;          // +0x1a8
    f32                mField1ac;
    f32                mField1b0;
    f32                mField1b4;
    f32                mField1b8;
    f32                mField1bc;          // +0x1bc
    f32                mField1c0;          // +0x1c0
    f32                mField1c4;          // +0x1c4
    f32                mField1c8;          // +0x1c8
    f32                mField1cc;          // +0x1cc
    f32                mField1d0;          // +0x1d0
    f32                mField1d4;          // +0x1d4
    f32                mField1d8;
    f32                mField1dc;
    f32                mField1e0;
    f32                mField1e4;
    f32                mField1e8;
    f32                mField1ec;
    f32                mField1f0;          // +0x1f0
    f32                mField1f4;
    f32                mField1f8;
    f32                mField1fc;
    f32                mField200;
    u32                mField204;          // +0x204
    u32                mField208;
    u32                mField20c;
    u32                mField210;
    f32                mField214;          // +0x214
    u32                mField218;          // +0x218
    u32                mField21c;
    u32                mField220;
    u32                mField224;
    u32                mField228;
    u32                mField22c;
    u32                mField230;
    u32                mField234;
    f32                mField238;          // +0x238
    u32                mField23c;          // +0x23c
    u8                 mPad240[4];         // +0x240
    u32                mField244;          // +0x244
    i32                mField248;          // +0x248
    i32                mField24c;          // +0x24c
    i32                mField250;          // +0x250
    u32                mStrategyClassID;   // +0x254
    cString            mWaterColorID;      // +0x258
    f32                mField26c;          // +0x26c
    f32                mField270;
    f32                mField274;
    f32                mField278;
    f32                mField27c;
    f32                mField280;
    f32                mField284;
    f32                mField288;
    f32                mField28c;
    f32                mField290;
    f32                mField294;
    f32                mField298;          // +0x298

    void baseCtorRaw();                                        // 0x00c87660
    void baseDtorRaw();                                        // 0x00c87770
    cSPSpaceToolData();
    ~cSPSpaceToolData();

    u8   FUN_00c87580(cOutStream* stream);                     // 0x00c87580
    u8   Write(cOutStream* stream);                            // 0x0104bcc0
    u32  FUN_0104bd50();                                       // 0x0104bd50
    i32  FUN_0104bde0();                                       // 0x0104bde0
    i32  FUN_0104be00();                                       // 0x0104be00
    f64  FUN_0104be30();                                       // 0x0104be30
    i32  FUN_0104bfa0();                                       // 0x0104bfa0
    u8   FUN_0104bff0();                                       // 0x0104bff0
    u8   FUN_0104c010();                                       // 0x0104c010
    u8   func48h();                                            // 0x0104ca20
    bool IsInContext();                                        // 0x0104cb70
    void FUN_0104cbd0(i32 delta);                              // 0x0104cbd0
    void FUN_0104cc00(i32 amount);                             // 0x0104cc00
    u32  IsDeselectedAfterUse();                               // 0x0104cc40
    u8   FUN_0104cc90();                                       // 0x0104cc90
    u8   FUN_0104cdb0(cIface* target);                         // 0x0104cdb0
};

struct cSPSpaceInventoryItem {
    void UpdateTuning(u32 propId, u32* out);                   // 0x0104c120
};

// ===========================================================================
// SP::cSPEditorVerbIconTray
// ===========================================================================
struct cSPEditorVerbIconTray {
    void**              mpVftbl;            // +0x00
    u8                  mPad04[0x18];       // +0x04 .. +0x1b
    u8                  mSelfObj1c[0x58];   // +0x1c .. +0x73
    cString             mTexts[26];         // +0x74 .. +0x27b
    cMessagingServer*   mpServer;           // +0x27c
    void*               mpSelf;             // +0x280
    const u32*          mpEvents;           // +0x284
    u32                 mEventCount;        // +0x288
    u32                 mField28c;          // +0x28c

    void Register();                                           // 0x0104c220
    void GetTextAt(u32 index);                                 // 0x0104c4f0
    void* Dispatch(u32 a, u32 b, void** ppOut, u32 d);         // 0x0104c510
};

}  // namespace SP

// ===========================================================================
// SP::cSPSpaceToolData::cSPSpaceToolData
// ===========================================================================
// @ 0x0104c570
SP::cSPSpaceToolData::cSPSpaceToolData()
{
    baseCtorRaw();
    mpVftable0 = &vtbl_cSpaceToolData;
    mpVftable8 = &vtbl_cSpaceToolData8;
    mpVftableC = &vtbl_cSpaceToolDataC;
    mFlag80 = 0;
    mIsInUse.ctorRaw();
    mRechargeTimer.ctorRaw();
    mAutoFireTimer.ctorRaw();
    mChargeTimer.ctorRaw();
    mEffect108 = 0;
    mEffect10c = 0;
    mEffect110 = 0;
    mEffect114 = 0;
    mEffect118 = 0;
    mField11c = -1;
    mField120 = 0;
    mField124 = 0;
    mField128 = 0;
    mField12c = 0;
    mField140 = 0;
    mField144 = 1.0f;
    mField148 = 1.0f;
    mField14c = 0.0f;
    mField150 = 0;
    mField154 = 0.0f;
    mField158 = 0.0f;
    mField15c = 0.0f;
    mField160 = 0.0f;
    mField164 = 0.0f;
    mField168 = 0.0f;
    mField16c = 0;
    mField170 = 0;
    mFlags174 = 0;
    mField178 = 0;
    mField17c = 0x8da5ffb9;
    mField180 = -1;
    mField184 = -1;
    mField188 = 0x82ce6992;
    mUpgradeInstance = 0;
    mField190 = gToolGlobalD8;
    mField194 = gToolGlobalDC;
    mField198 = gToolGlobalE0;
    mField19c = 0;
    mLimit1a0 = 0;
    mField1a4 = 0;
    mField1a8 = 0.0f;
    mField1ac = 0.0f;
    mField1b0 = 0.0f;
    mField1b4 = 0.0f;
    mField1b8 = 0.0f;
    mField1bc = 1.0f;
    mField1c0 = 0.0f;
    mField1c4 = 0.0f;
    mField1c8 = 0.0f;
    mField1cc = 1.0f;
    mField1d0 = 1.0f;
    mField1d4 = 0.0f;
    mField1d8 = 0.0f;
    mField1dc = 0.0f;
    mField1e0 = 0.0f;
    mField1e4 = 0.0f;
    mField1e8 = 0.0f;
    mField1ec = 0.0f;
    mField1f0 = 0.0f;
    mField1f4 = 0.0f;
    mField1f8 = 0.0f;
    mField1fc = 0.0f;
    mField200 = 0.0f;
    mField204 = 0;
    mField208 = 0;
    mField20c = 0;
    mField210 = 0;
    mField214 = 0.0f;
    mField218 = 0;
    mField21c = 0;
    mField220 = 0;
    mField224 = 0;
    mField228 = 0;
    mField22c = 0;
    mField230 = 0;
    mField234 = 0;
    mField238 = 0.0f;
    mField23c = 0;
    mField244 = 0;
    mField248 = -1;
    mField24c = -1;
    mField250 = -1;
    mStrategyClassID = 0;
    mWaterColorID.ctorRaw();
    mField26c = 0.0f;
    mField270 = 0.0f;
    mField274 = 0.0f;
    mField278 = 0.0f;
    mField27c = 0.0f;
    mField280 = 0.0f;
    mField284 = 0.0f;
    mField288 = 0.0f;
    mField28c = 0.0f;
    mField290 = 0.0f;
    mField294 = 0.0f;
    mField298 = 0.0f;
    cToolRef** p = &mEffect108;
    for (u32 i = 3; i != 0; i--) {
        cToolRef* r = *p;
        if (r != 0) {
            *p = 0;
            r->RefCountRelease();
        }
        p++;
    }
    mAmmo7c = 0;
}

// ===========================================================================
// SP::cSPSpaceToolData::~cSPSpaceToolData
// ===========================================================================
// @ 0x0104c910
SP::cSPSpaceToolData::~cSPSpaceToolData()
{
    mpVftable0 = &vtbl_cSpaceToolData;
    mpVftable8 = &vtbl_cSpaceToolData8;
    mpVftableC = &vtbl_cSpaceToolDataC;
    mWaterColorID.dtorRaw();
    if (mField16c != 0)  mField16c->RefCountRelease();
    if (mField140 != 0)  mField140->RefCountRelease();
    if (mField12c != 0)  mField12c->RefCountRelease();
    if (mField128 != 0)  mField128->RefCountRelease();
    if (mField124 != 0)  mField124->RefCountRelease();
    if (mField120 != 0)  mField120->RefCountRelease();
    if (mEffect118 != 0) mEffect118->EffectRelease();
    cToolRef** p = &mEffect114;
    if (mEffect114 != 0) mEffect114->EffectRelease();
    for (i32 i = 2; i >= 0; i--) {
        p--;
        cToolRef* r = *p;
        if (r != 0) r->RefCountRelease();
    }
    mChargeTimer.dtorRaw();
    mAutoFireTimer.dtorRaw();
    mRechargeTimer.dtorRaw();
    mIsInUse.dtorRaw();
    baseDtorRaw();
}

// ===========================================================================
// SP::cSPSpaceToolData::Write
// ===========================================================================
// @ 0x0104bcc0
u8 SP::cSPSpaceToolData::Write(cOutStream* stream)
{
    cIface* a = (cIface*)stream->Call(0x20);
    u32 tag = 0x707459f0;
    cIface* b = (cIface*)a->Call(0x18);
    WriteUint32(b, &tag, 1, 0);
    u8 ok = FUN_00c87580(stream);
    cVarListSerializer ser;
    ser.ctorRaw((u8*)this - 0xc, 0x15b8850, 0x1a80d26);
    u8 serOk = ser.Serialize(stream);
    if (serOk != 0 && ok != 0) return 1;
    return 0;
}

// ===========================================================================
// SP::cSPSpaceToolData::FUN_0104bd50
// ===========================================================================
// @ 0x0104bd50
u32 SP::cSPSpaceToolData::FUN_0104bd50()
{
    if (mFlag80 == 0) {
        if (!mAutoFireTimer.IsRunning()) return 0;
    }
    return 1;
}

// ===========================================================================
// SP::cSPSpaceToolData::FUN_0104bde0
// ===========================================================================
// @ 0x0104bde0
i32 SP::cSPSpaceToolData::FUN_0104bde0()
{
    i32 v = (i32)(mField1c0 * 1000.0f);
    if (v < 0) v = -1;
    return v;
}

// ===========================================================================
// SP::cSPSpaceToolData::FUN_0104be00
// ===========================================================================
// @ 0x0104be00
i32 SP::cSPSpaceToolData::FUN_0104be00()
{
    i32 v = (i32)(mField1c4 * 1000.0f);
    if (v < 0) v = -1;
    return v;
}

// ===========================================================================
// SP::cSPSpaceToolData::FUN_0104be30
// ===========================================================================
// @ 0x0104be30
f64 SP::cSPSpaceToolData::FUN_0104be30()
{
    return (f64)mField1cc * (f64)mField148;
}

// ===========================================================================
// SP::cSPSpaceToolData::FUN_0104bfa0
// ===========================================================================
// @ 0x0104bfa0
i32 SP::cSPSpaceToolData::FUN_0104bfa0()
{
    long long v = (long long)(mField1f0 * 1000.0f);
    return (int)v;
}

// ===========================================================================
// SP::cSPSpaceToolData::FUN_0104bff0
// ===========================================================================
// @ 0x0104bff0
u8 SP::cSPSpaceToolData::FUN_0104bff0()
{
    if (mStrategyClassID == 0) return 1;
    return (u8)((mStrategyClassID >> 8) & 1);
}

// ===========================================================================
// SP::cSPSpaceToolData::FUN_0104c010
// ===========================================================================
// @ 0x0104c010
u8 SP::cSPSpaceToolData::FUN_0104c010()
{
    if (mStrategyClassID == 0) return 1;
    return (u8)((mStrategyClassID >> 7) & 1);
}

// ===========================================================================
// SP::cSPSpaceInventoryItem::UpdateTuning
// ===========================================================================
// @ 0x0104c120
void SP::cSPSpaceInventoryItem::UpdateTuning(u32 propId, u32* out)
{
    i32  count = 0;
    void* arr  = 0;
    *out = 0;
    GetPropertyAsIntArray(propId, 0x5e51b17, &count, &arr);
    for (i32 i = 0; i < count; i++) {
        u32 v = ((i32*)arr)[i];
        switch (v) {
        case 0xe7ca2d90: *out |= 0x20;   break;
        case 0xa13abc9f: *out |= 2;      break;
        case 0x9b8e862f: *out |= 0x80;   break;
        case 0x9f6db313: *out |= 0x10;   break;
        case 0xa6663355: *out |= 0x200;  break;
        case 0xc710b6e9: *out |= 0x40;   break;
        case 0x2dc69129: *out |= 1;      break;
        case 0x3e9c273b: *out |= 0x100;  break;
        case 0x476a98c7: *out |= 4;      break;
        case 0x4bf0fa5a: *out |= 0x400;  break;
        case 0x78bddf27: *out |= 8;      break;
        }
    }
}

// ===========================================================================
// SP::cSPEditorVerbIconTray::Register
// ===========================================================================
// @ 0x0104c220
void SP::cSPEditorVerbIconTray::Register()
{
    RegisterStaticRegistrations();
    void* self = 0;
    if (this != 0) self = (void*)&mSelfObj1c;
    cMessagingServer* server = (cMessagingServer*)EA_Messaging_GetServer();
    mpServer = server;
    mpSelf = self;
    mpEvents = gVerbEventIDs;
    mEventCount = 0xe;
    mField28c = 0;
    if (server != 0 && self != 0) {
        u32 i = 0;
        do {
            server->RegisterEvent(self, gVerbEventIDs[i]);
            i++;
        } while (i < 0xe);
    }
    mTexts[0].Load(0x2db6dad3, 0x68b22cd, 0);
    mTexts[1].Load(0x2db6dad3, 0x653e593, 0);
    mTexts[2].Load(0x2db6dad3, 0x653e594, 0);
    mTexts[3].Load(0x2db6dad3, 0x653e595, 0);
    mTexts[4].Load(0x2db6dad3, 0x653e596, 0);
    mTexts[5].Load(0x2db6dad3, 0x653e597, 0);
    mTexts[6].Load(0x2db6dad3, 0x66f7a1a, 0);
    mTexts[7].Load(0x2db6dad3, 0x66f7a1b, 0);
    mTexts[8].Load(0x2db6dad3, 0x653e598, 0);
    mTexts[9].Load(0x2db6dad3, 0x653e599, 0);
    mTexts[10].Load(0x2db6dad3, 0x653e59a, 0);
    mTexts[11].Load(0x2db6dad3, 0x653e59b, 0);
    mTexts[12].Load(0x2db6dad3, 0x671ce05, 0);
    mTexts[13].Load(0x2db6dad3, 0x671fb24, 0);
    mTexts[14].Load(0x2db6dad3, 0x653e59c, 0);
    mTexts[15].Load(0x2db6dad3, 0x653e59d, 0);
    mTexts[16].Load(0x2db6dad3, 0x653e59e, 0);
    mTexts[17].Load(0x2db6dad3, 0x653e59f, 0);
    mTexts[18].Load(0x2db6dad3, 0x653e5a0, 0);
    mTexts[19].Load(0x2db6dad3, 0x66f7a1d, 0);
    mTexts[20].Load(0x2db6dad3, 0x66f7a1c, 0);
    mTexts[21].Load(0x2db6dad3, 0x66f7a1f, 0);
    mTexts[22].Load(0x2db6dad3, 0x66f7a1e, 0);
    mTexts[23].Load(0x2db6dad3, 0x66f7a20, 0);
    mTexts[24].Load(0x2db6dad3, 0x66f7a21, 0);
    mTexts[25].Load(0x2db6dad3, 0x66f7a22, 0);
}

// ===========================================================================
// SP::cSPEditorVerbIconTray::GetTextAt
// ===========================================================================
// @ 0x0104c4f0
void SP::cSPEditorVerbIconTray::GetTextAt(u32 index)
{
    mTexts[index].GetText();
}

// ===========================================================================
// SP::cSPEditorVerbIconTray::Dispatch
// ===========================================================================
// @ 0x0104c510
void* SP::cSPEditorVerbIconTray::Dispatch(u32 a, u32 b, void** ppOut, u32 d)
{
    void* nv = ((void* (__thiscall*)(void*, u32, u32, u32))mpVftbl[0x20 / 4])(this, a, 0x24a4ac5, d);
    void* old = *ppOut;
    if (nv == old) return old;
    if (nv != 0) ((void (__thiscall*)(void*))((void**)nv)[0])(nv);
    *ppOut = nv;
    if (old != 0) {
        ((void (__thiscall*)(void*))((void**)old)[1])(old);
        return *ppOut;
    }
    return nv;
}

// ===========================================================================
// SP::cSPSpaceToolData::func48h
// ===========================================================================
// @ 0x0104ca20
u8 SP::cSPSpaceToolData::func48h()
{
    if (mItemID.instanceID == gShieldItemID.instanceID &&
        mItemID.typeID == gShieldItemID.typeID &&
        mItemID.groupID == gShieldItemID.groupID) {
        if (mEffect114 != 0) {
            void* o = mEffect114->ActivateVfx(&gChargePropertyId_013f94d4);
            return (u8)FUN_00bfc480(o);
        }
        return (u8)FUN_00bfc480(0);
    }
    if (mItemID.instanceID == gCloakItemID.instanceID &&
        mItemID.typeID == gCloakItemID.typeID &&
        mItemID.groupID == gCloakItemID.groupID) {
        if (mEffect114 != 0) {
            cToolRef* o = (cToolRef*)mEffect114->ActivateVfx((void*)0xb033b403);
            return (u8)o->OnActivate(1);
        }
        return (u8)((cToolRef*)0)->OnActivate(1);
    }
    if (mItemID.instanceID == gRallyCallItemID.instanceID &&
        mItemID.typeID == gRallyCallItemID.typeID &&
        mItemID.groupID == gRallyCallItemID.groupID) {
        if (mIsInUse.IsRunning()) {
            i32 t = (i32)(mField1c0 * 1000.0f);
            if (t < 0) t = -1;
            u64 e = mIsInUse.GetElapsedTime();
            if (e < (u64)(i64)t) return 1;
        }
        return 0;
    }
    if (mItemID.instanceID == gSoothingSongItemID.instanceID &&
        mItemID.typeID == gSoothingSongItemID.typeID &&
        mItemID.groupID == gSoothingSongItemID.groupID) {
        cTerrainEditor* te = (cTerrainEditor*)NounManager();
        return (u8)te->GetCurrentTerrainSphere()->Check();
    }
    return 0;
}

// ===========================================================================
// SP::cSPSpaceToolData::IsInContext
// ===========================================================================
// @ 0x0104cb70
bool SP::cSPSpaceToolData::IsInContext()
{
    bool result = false;
    if (mUpgradeInstance != 0) {
        if (mUpgradeInstance != 0x5f848353) {
            result = true;
        } else if (PlanetModel() != 0 && ((cPlanetModel*)PlanetModel())->mpAnchor24 != 0) {
            if (GetCurrentGameMode() != &gGameMode01654c05) {
                result = true;
            } else if (GetUniverseContext() == 0) {
                result = true;
            }
        }
    }
    return result;
}

// ===========================================================================
// SP::cSPSpaceToolData::FUN_0104cbd0
// ===========================================================================
// @ 0x0104cbd0
void SP::cSPSpaceToolData::FUN_0104cbd0(i32 delta)
{
    i32 limit = mLimit1a0;
    if (mAmmo7c < limit) {
        i32 v = mAmmo7c + delta;
        mAmmo7c = v;
        if (v > limit) mAmmo7c = limit;
    }
}

// ===========================================================================
// SP::cSPSpaceToolData::FUN_0104cc00
// ===========================================================================
// @ 0x0104cc00
void SP::cSPSpaceToolData::FUN_0104cc00(i32 amount)
{
    if (amount == -1) amount = mField19c;
    mAmmo7c -= amount;
}

// ===========================================================================
// SP::cSPSpaceToolData::IsDeselectedAfterUse
// ===========================================================================
// @ 0x0104cc40
u32 SP::cSPSpaceToolData::IsDeselectedAfterUse()
{
    cPropertyList* pl = mpPropList30;
    if (pl != 0) {
        Property* p;
        if (pl->FindProperty(0x3348701, &p) && p->mType12 == 1 && *p->GetBool())
            goto Ltrue;
    }
    if (((mFlags174 >> 0xf) & 1) == 0) return 0;
Ltrue:
    return 1;
}

// ===========================================================================
// SP::cSPSpaceToolData::FUN_0104cc90
// ===========================================================================
// @ 0x0104cc90
u8 SP::cSPSpaceToolData::FUN_0104cc90()
{
    bool result = false;
    cPropertyList* pl = mpPropList30;
    if (pl != 0) {
        Property* p;
        if (pl->FindProperty(0x6df688d, &p) && p->mType12 == 1)
            result = *p->GetBool();
    }
    return (u8)result;
}

// ===========================================================================
// SP::cSPSpaceToolData::FUN_0104cdb0
// ===========================================================================
// @ 0x0104cdb0
u8 SP::cSPSpaceToolData::FUN_0104cdb0(cIface* target)
{
    if ((mFlagsBytes.mByte176 & 1) != 0) {
        if ((u32)target->Call(0x4c) == GetPlayerEmpireID()) return 0;
    }
    if (mStrategyClassID == 0) return 1;
    u8 result;
    bool tookCase = false;
    if (target != 0) {
        u32 t = (u32)target->Call(0x38);
        switch (t) {
        case 0x137e8e0:  result = (u8)(mStrategyClassID >> 3);  tookCase = true; break;
        case 0xb033b403: result = (u8)(mStrategyClassID >> 2);  tookCase = true; break;
        case 0xd0036e08: result = (u8)(mStrategyClassID);       tookCase = true; break;
        case 0xee9b2232: result = (u8)(mStrategyClassID >> 5);  tookCase = true; break;
        case 0x436f315:  result = (u8)(mStrategyClassID >> 4);  tookCase = true; break;
        case 0x4e3faaf:  result = (u8)(mStrategyClassID >> 10); tookCase = true; break;
        case 0x4f176642: result = (u8)(mStrategyClassID >> 1);  tookCase = true; break;
        default:
            if (target->Call1(0xc, 0xe9cb8ba) != 0) {
                result = (u8)(mStrategyClassID >> 6);
                tookCase = true;
            } else {
                result = (u8)(mStrategyClassID >> 7);
            }
            break;
        }
    } else {
        result = (u8)(mStrategyClassID >> 7);
    }
    if (GetUniverseContext() != 0) return result & 1;
    if (!tookCase) return result & 1;
    if ((result & 1) == 0) return 0;
    if ((mStrategyClassID & 0x200) == 0) return 0;
    u8 b = (u8)IsHostileToAll(FUN_01021260());
    void* s = FUN_00b67740(target);
    if (s != 0) {
        b = (u8)cSPSpaceCommCanTarget(s, GetUFOSimulator(0));
    }
    return b;
}