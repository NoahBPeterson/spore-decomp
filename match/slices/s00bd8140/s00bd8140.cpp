// Slice s00bd8140 -- Simulator cCity timer/query helpers, cGameData and cCommunity glue.
//
// A cluster of cCity members (visit-effect and civ timers, wealth/count queries, the
// nearest-combatant scans) plus a few cGameData / cCommunity / planet helpers reached from the
// same region of SporeApp.exe. The retail offsets are read from the disassembly and modelled with
// locally declared stub classes, following the sibling-slice style.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

typedef unsigned int  u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char   s8;

struct Float3 { float x, y, z; };
struct Float4 { float x, y, z, w; };
struct cCity;

// ---------------------------------------------------------------------------------------------
// retail callees / globals
// ---------------------------------------------------------------------------------------------
extern "C" {
extern float sqrtf(float);
extern double sqrt(double);
void  __cdecl FUN_00c004a0(void);                          // 0x00c004a0
void  __fastcall FUN_00b638b0(void* ecx_this);              // 0x00b638b0 cGonzagoTimer dtor
void* __cdecl FUN_00b3d350();                              // 0x00b3d350 SP::PlanetModel
void* __cdecl FUN_00b3d300();                              // 0x00b3d300 SP::NounManager
void* __cdecl FUN_00b3d240();                              // 0x00b3d240 (effect manager)
void* __stdcall FUN_00b3d430(int a);                      // 0x00b3d430 SP::TerraformingManager
void* __cdecl FUN_00b3d480(void* a);                       // 0x00b3d480
void* __cdecl FUN_00b3d4d0();                              // 0x00b3d4d0 GetTriggerMgr
void* __cdecl FUN_01021260();                              // 0x01021260 GetActivePlanet
void* __cdecl FUN_010212a0();                              // 0x010212a0 GetActivePlanetRecord
void  __cdecl FUN_00b88590(void* a, void* buf);             // 0x00b88590 cPlanetModel::GetContinent
int   __fastcall FUN_00b1f9d0(void* ecx_this);              // 0x00b1f9d0 GetPlayerEmpireOrMinus1
int   __cdecl FUN_00b5b800();                              // 0x00b5b800 GetCurrentGameMode
int   __cdecl FUN_00b8dab0(void* a);                       // 0x00b8dab0
int   __cdecl FUN_00bbe5f0(void* a);                       // 0x00bbe5f0

// The record returned by GetActivePlanetRecord, and the terraforming manager.
struct cPlanetRecord
{
    int  GameMode();                                    // 0x00b8dab0 (thiscall)
};

struct cTerraformingMgr
{
    int  TerraformCount();                              // 0x00bbe5f0 (thiscall)
};

// The civ record returned by cPlanet::GetCiv, and the planet itself (GetActivePlanet).
struct cCivData
{
    int** GetCities();                                  // 0x00c5c65e0 (thiscall)
    void  RemoveAt(int i, void* other);                 // 0x00ff2d50 (thiscall)
    u8    pad000[0x3c];
    int*  mBeg3c;                                       // +0x3c
    int*  mEnd40;                                       // +0x40
};

struct cPlanet
{
    cCivData* GetCiv(void* a);                          // 0x00c71040 (thiscall)
};
int   __cdecl FUN_00bfc490(void* a);                       // 0x00bfc490
int   __cdecl FUN_00bfc600(void* a);                       // 0x00bfc600
void  __cdecl FUN_00ac8d60(void* a);                       // 0x00ac8d60
void  __cdecl FUN_00b8d420(void* pm, void* a);             // 0x00b8d420
void  __cdecl FUN_00b86650(void* pm, void* a, void* b);    // 0x00b86650
void  __cdecl FUN_00b866f0(void* pm, void* a, void* b);    // 0x00b866f0
void  __cdecl FUN_00b7e360(void* a);                       // 0x00b7e360
void  __cdecl FUN_00c41c60(void* a, void* b, int c);       // 0x00c41c60
void* __cdecl FUN_00b20c60(void* a, int b);                // 0x00b20c60 cGameNounManager::CreateNoun
void  __cdecl FUN_00b81720(void* pm, void* out);           // 0x00b81720
char  __cdecl FUN_00b88f60(void* pm, float a, void* out);   // 0x00b88f60
void* __cdecl FUN_00c71040(void* a);                        // 0x00c71040
void* __cdecl FUN_00c5c65e0(void* a);                       // 0x00c5c65e0  (SP::cCivData::GetCities)
void  __cdecl FUN_00c88670(void* a, void* b);               // 0x00c88670
}

// (member-call style shims for the ones invoked with an explicit ecx)
char  __fastcall FUN_00b183f0(void* ecx_this, void* edx, void* a);  // 0x00b183f0
void  __fastcall FUN_00b18550(void* ecx_this, void* edx, void* a);  // 0x00b18550
void  __fastcall FUN_00c3f2d0(void* ecx_this, void* edx, void* a);  // 0x00c3f2d0
void  __fastcall FUN_00bfc470(void* ecx_this, void* edx, int a);    // 0x00bfc470
void  __fastcall FUN_00c3f160(void* ecx_this, void* edx, int a, float b); // 0x00c3f160
void  __fastcall FUN_00bebdd0(void* ecx_this, void* edx, void* a);  // 0x00bebdd0
char  __fastcall FUN_00ac8d60(void* ecx_this, void* edx, void* a);  // 0x00ac8d60
void  __fastcall FUN_00b17180(void* ecx_this, void* edx);           // (unused placeholder)
void  __fastcall FUN_00bd7d90(void* ecx_this, void* edx);           // 0x00bd7d90
void  __fastcall FUN_00ff2d50(void* ecx_this, void* edx, int idx, void* b); // 0x00ff2d50
u32   __fastcall RandomUint32Uniform(void* ecx_this, void* edx, u32 n);     // 0x00a68fb0
char  __fastcall FUN_00c004c0(void* ecx_this, void* edx, int a);     // 0x00c004c0

extern u32   g_168d248;         // 0x0168d248
extern u32   g_169c088;         // 0x0169c088
extern float g_13f1cac;         // 0x013f1cac  (50.0f)
extern float g_13ec4b8;         // 0x013ec4b8  (1e-08f)
extern float g_13ec4d0;         // 0x013ec4d0  (100.0f)
extern float g_1468454;         // 0x01468454
extern float g_146847c;         // 0x0146847c  (FLT_MAX)
extern float g_1486110;         // 0x01486110
extern float g_1471064;         // 0x01471064  (0.5f)
extern float g_140e87c;         // 0x0140e87c  (2/3)
extern u32   g_1654c05;         // 0x01654c05  (GetCurrentGameMode result)
extern void* g_1601760;         // 0x01601760  (math random state)
extern void* g_168bd70;         // 0x0168bd70

// ---------------------------------------------------------------------------------------------
// SP::cSPTimer (0x00feba90 IsRunning, 0x00bc3190 GetElapsedTime, 0x00bc3130 Restart).
// ---------------------------------------------------------------------------------------------
struct cSPTimer
{
    virtual ~cSPTimer();
    u8 pad04[0x20 - 0x04];
    char IsRunning();                                   // 0x00feba90
    long long GetElapsedTime();                         // 0x00bc3190 (edx:eax)
    void Restart();                                     // 0x00bc3130
};

// A vtable-only interface used by the entity casts (slots +0x00 .. +0x6c).
struct IObj
{
    virtual void  v00();                                 // +0x00
    virtual void  v04();                                 // +0x04
    virtual void  v08();                                 // +0x08
    virtual void* Cast(u32 id);                          // +0x0c
    virtual void* Slot10();                              // +0x10
    virtual void  v14();                                 // +0x14
    virtual void  v18();                                 // +0x18
    virtual void  v1c();                                 // +0x1c
    virtual void  v20();                                 // +0x20
    virtual void  v24();                                 // +0x24
    virtual void  v28();                                 // +0x28
    virtual Float3* GetPosition();                       // +0x2c
    virtual void* v30();                                 // +0x30
    virtual void  v34();                                 // +0x34
    virtual u32   GetTypeId();                           // +0x38
    virtual void  v3c();                                 // +0x3c
    virtual void  v40();                                 // +0x40
    virtual void  v44();                                 // +0x44
    virtual void  v48();                                 // +0x48
    virtual u32   Slot4c(u32 a, float b);                // +0x4c
    virtual void  v50();                                 // +0x50
    virtual u32   Slot54();                              // +0x54
    virtual u32   Slot58(Float3* out);                   // +0x58
    virtual u32   Slot5c(Float3* out, u32 a);            // +0x5c
    virtual void  v60();                                 // +0x60
    virtual void  v64();                                 // +0x64
    virtual void  v68();                                 // +0x68
    virtual u32   Slot6c();                              // +0x6c

    void SetEffectId(u32 id, float v);                   // 0x00c3f160
    void DoF3d2(void* a);                                // 0x00c3f2d0
};

// The 0x19c-byte block at cCity + 0x38: a sub-object with a DoC470 method at
// +0x38 and an embedded interface at +0x100.
struct CSlot38
{
    u8   pad000[0x1d4 - 0x38];
    void DoC470(int a);                                  // 0x00bfc470
};

struct cCityRegion38
{
    u8   pad000[0x100 - 0x38];
    IObj mObj100;                                       // +0x100 embedded interface
    u8   pad104[0x1d4 - 0x104];

    CSlot38* AsSlot38() { return (CSlot38*)(void*)this; }
};

// A polymorphic sub-object with a callback at vtable + 0x38.
struct IFwd
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void Call38(void* a);                        // +0x38
};

// The object at cCommunity::mp108, with the IFwd sub-object at +0x70.
struct cCom108
{
    u8   pad000[0x70];
    IFwd mFwd70;                                         // +0x70
};

struct cCommunity
{
    void     func54h(void* a);                           // 0x00c88670
    u8       pad000[0x108];
    cCom108* mp108;                                      // +0x108
};

struct cGameNounManager
{
    IObj* CreateNoun(u32 id);                            // 0x00b20c60
    int   GetPlayerEmpireOrMinus1();                     // 0x00b1f9d0
};

struct cPlanetModel
{
    void GetContinent(u32 id);                           // 0x00b88590
    void Attach(void* b);                                // 0x00b7e360
    void Despawn(void* b);                               // 0x00b8d420
    void Spawn(void* a, void* b);                        // 0x00b86650
    void SpawnAlt(void* a, void* b);                     // 0x00b866f0
    char Probe(void* target, float a, Float3* out);      // 0x00b88f60
    Float3* Sample(Float3* out);                         // 0x00b81720
};

// Element type of the 12-byte-stride vector at cCity + 0x55c, and the object its +4
// pointer refers to.
struct cTarget55c
{
    void AddEntry(cCity* a, void* b, int c);             // 0x00c41c60
    u8   pad000[0x11c];
    void* p11c;                                          // +0x11c
};

struct cElem55c
{
    void*        p0;                                     // +0x00
    cTarget55c*  p4;                                     // +0x04
    int          kind;                                   // +0x08
};

struct cCityData;

// A polymorphic sub-object with a boolean query at vtable slot 0.
struct ISlot120
{
    char Test();                                        // 0x00bfc600
    u8   pad01[4];
};

// The combat-target carrier passed to cCity::NearestCombatant, and the element type of the
// cCity + 0x340 / + 0x354 vectors.
struct cCombatCarrier : IObj
{
    u8   pad004[0x34 - 0x04];
    IObj mObj34;                                        // +0x34 embedded interface
    u8   pad038[0x120 - 0x38];
    ISlot120 mSlot120;                                  // +0x120
    u8   pad124[0x289 - 0x124];
    u8   b289;                                          // +0x289
    u8   pad28a[0x290 - 0x28a];
    int  i290;                                          // +0x290
    u8   pad294[0x508 - 0x294];
    IObj mObj508;                                       // +0x508 embedded interface
    u8   pad50c[0x588 - 0x50c];
    ISlot120 mSlot588;                                  // +0x588
    u8   pad58c[0x684 - 0x58c];
    int  i684;                                          // +0x684
    u8   pad688[0xb1c - 0x688];
    int  iB1c;                                          // +0xb1c
};

// The interface returned by IX508::Slot54.
struct IX54
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58();
    virtual u32  Slot5c(u32 a);                         // +0x5c
};

// The interface object embedded at cElem1f4 + 0x508.
struct IX508
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50();
    virtual IX54* Slot54();                             // +0x54
    virtual void  v58();
    virtual u32   Slot5c(u32 a);                        // +0x5c
    int   GetFileCount();                               // 0x008e7f80
    float Distance();                                   // 0x00bfc490
};

// Element type of the cCity + 0x1f4 / + 0x1f8 vector.
struct cElem1f4
{
    u8    pad000[0x508];
    IX508 mObj508;                                      // +0x508
    u8    pad50c[0xc50 - 0x50c];
    float f0c50;                                        // +0xc50
};

// ---------------------------------------------------------------------------------------------
// SP::cCity -- only the members touched by this slice.
// ---------------------------------------------------------------------------------------------
struct cCity
{
    // vtable pointer at +0 (a single vptr; the individual virtual slots are not touched here).
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual char v2c();                                 // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40();

    u8    pad04[0x38 - 0x04];
    cCityRegion38 mRegion38;        // +0x38 overlay region (mTurrets & friends)
    u8    b1d4;                     // 0x1d4
    u8    pad1d5[0x1d8 - 0x1d5];
    int   i1d8;                     // 0x1d8
    int   i1dc;                     // 0x1dc
    cCity** mBeg1e0;                // 0x1e0
    cCity** mEnd1e4;                // 0x1e4
    u8    pad1e8[0x1f4 - 0x1e8];
    cElem1f4** mBeg1f4;             // 0x1f4
    cElem1f4** mEnd1f8;             // 0x1f8
    u8    pad1fc[0x208 - 0x1fc];
    IObj* mp208;                    // 0x208
    u8    pad20c[0x230 - 0x20c];
    cSPTimer mTimer230;             // 0x230
    cSPTimer mTimer250;             // 0x250
    cSPTimer mTimer270;             // 0x270
    u32   u290;                     // 0x290  (low half of the timer-270 deadline)
    u32   u294;                     // 0x294  (high half)
    u8    pad298[0x2e3 - 0x298];
    u8    b2e3;                     // 0x2e3
    u8    pad2e4[0x2e5 - 0x2e4];
    u8    b2e5;                     // 0x2e5
    u8    pad2e6[0x2f0 - 0x2e6];
    u32   u2f0;                     // 0x2f0
    int   u2f4;                     // 0x2f4
    int   u2f8;                     // 0x2f8
    u8    b2fc;                     // 0x2fc
    u8    pad2fd[0x300 - 0x2fd];
    float f300;                     // 0x300
    float f304;                     // 0x304
    u8    pad308[0x324 - 0x308];
    IObj* mp324;                    // 0x324
    u8    pad328[0x340 - 0x328];
    cCombatCarrier** mBeg340;       // 0x340
    cCombatCarrier** mEnd344;       // 0x344
    u8    pad348[0x354 - 0x348];
    cCombatCarrier** mBeg354;       // 0x354
    cCombatCarrier** mEnd358;       // 0x358
    u8    pad35c[0x508 - 0x35c];
    IObj  mObj508;                  // 0x508
    u8    pad50c[0x519 - 0x50c];
    u8    b519;                     // 0x519
    u8    pad51a[0x540 - 0x51a];
    int   i540;                     // 0x540
    u8    pad544[0x55c - 0x544];
    cElem55c* mBeg55c;              // 0x55c
    cElem55c* mEnd560;              // 0x560
    u8    pad564[0x62c - 0x564];
    cCity** mBeg62c;                // 0x62c
    cCity** mEnd630;                // 0x630
    u8    pad634[0x678 - 0x634];
    int   i678;                     // 0x678
    u8    pad67c[0x698 - 0x67c];
    u8    b698;                     // 0x698
    u8    pad699[0x6a0 - 0x699];
    cSPTimer mTimer6a0;             // 0x6a0
    u8    b6c0;                     // 0x6c0
    u8    pad6c1[0x6c8 - 0x6c1];
    cSPTimer mTimer6c8;             // 0x6c8

    // ---- slice functions (thiscall) ---------------------------------------------------
    // The 64-bit deadline at 0x290 is the (u294:u290) pair viewed as one qword.
    unsigned long long& Timer270End() { return *(unsigned long long*)&u290; }
    void  SetGameDataOwner2(void* owner);               // 0x00b18550 (modeled callee)
    void  SetField2f4(int v);                           // 0x00bd8140
    void  SetField2f8(int v);                           // 0x00bd8170
    void  GetContinent();                               // 0x00bd8210
    char  Timer230Active();                             // 0x00bd8240
    char  Timer250Active();                             // 0x00bd8280
    char  Timer270Under();                              // 0x00bd82c0
    void  AddTimer270(int ms);                          // 0x00bd8300
    void  SetVisitEffectActive(char flag, float v);     // 0x00bd8380
    char  InVisitEffectWindow();                        // 0x00bd8630
    IObj* PickSlot();                                   // 0x00bd8660
    void* NearestCombatant(IObj* carrier);              // 0x00bd8d70
    float* DirToThing(Float3* out, Float3* target);     // 0x00bd8750 (free-ish)
    int   CountTypeId();                                // 0x00bd8960
    int   NumBig();                                     // 0x00bd89c0
    int   NumBig2();                                    // 0x00bd8a00
    int   ThreeWay();                                   // 0x00bd8aa0
    int   ThreeWayB();                                  // 0x00bd8b10
    int   WealthAmount();                               // 0x00bd8b80
    void  TickThings();                                 // 0x00bd8bd0
    void  GetAmount(float* out, int* n);                // 0x00bd85c0
    char  AnyTwo();                                     // 0x00bd8f30
    char  AnyThree();                                   // 0x00bd8f60
    void  RemoveCiv(unsigned a, unsigned b);            // 0x00bd8fe0
    void  TriggerSomething(IObj* other);                // 0x00bd9060
    void  EmitEffectIds(IObj* other);                   // 0x00bd9140
};

// ---------------------------------------------------------------------------------------------
// 0x00bd8140 -- store v in the int field at +0x2f4, clamping negatives to 0.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8140
void __fastcall FUN_00bd8140(cCity* ecx_this, void* edx, int v)
{
    ecx_this->u2f4 = v;
    if (v < 0) {
        ecx_this->u2f4 = 0;
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8170 -- store v in the int field at +0x2f8, clamping negatives to 0.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8170
void __fastcall FUN_00bd8170(cCity* ecx_this, void* edx, int v)
{
    ecx_this->u2f8 = v;
    if (v < 0) {
        ecx_this->u2f8 = 0;
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8200 -- tail-call the global-mode helper unless the mode is 3.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8200
void __cdecl FUN_00bd8200()
{
    if (g_168d248 == 3) {
        return;
    }
    FUN_00c004a0();
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8210 -- cCity::GetContinent.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8210
void __fastcall FUN_00bd8210(IObj* ecx_this, void* edx)
{
    Float3 buf;
    ((cPlanetModel*)FUN_00b3d350())->GetContinent(ecx_this->Slot58(&buf));
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8240 -- cCity::Timer230Active (IsRunning && elapsed < 120000).
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8240
int __fastcall FUN_00bd8240(cCity* ecx_this, void* edx)
{
    if (ecx_this->mTimer230.IsRunning() == 0) {
        return 0;
    }
    if ((unsigned long long)ecx_this->mTimer230.GetElapsedTime() < 120000ULL) {
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8280 -- cCity::Timer250Active (IsRunning && elapsed < 30000).
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8280
int __fastcall FUN_00bd8280(cCity* ecx_this, void* edx)
{
    if (ecx_this->mTimer250.IsRunning() == 0) {
        return 0;
    }
    if ((unsigned long long)ecx_this->mTimer250.GetElapsedTime() < 30000ULL) {
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd82c0 -- cCity::Timer270Under (IsRunning && elapsed < (u294:u290)).
// ---------------------------------------------------------------------------------------------
// @ 0x00bd82c0
int __fastcall FUN_00bd82c0(cCity* ecx_this, void* edx)
{
    if (ecx_this->mTimer270.IsRunning() != 0) {
        unsigned long long t = (unsigned long long)ecx_this->mTimer270.GetElapsedTime();
        if (t < ecx_this->Timer270End()) {
            return 1;
        }
    }
    return 0;
}
// ---------------------------------------------------------------------------------------------
// 0x00bd8300 -- cCity::AddTimer270(ms).
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8300
void __fastcall FUN_00bd8300(cCity* ecx_this, void* edx, int ms)
{
    cSPTimer* t = &ecx_this->mTimer270;
    if (t->IsRunning() != 0) {
        unsigned long long limit = ecx_this->Timer270End();
        unsigned long long e = (unsigned long long)t->GetElapsedTime();
        if (e <= limit) {
            unsigned long long sum = (unsigned long long)(long long)(ms * 1000) + limit;
            ecx_this->u290 = (u32)sum;
            ecx_this->u294 = (u32)(sum >> 32);
            return;
        }
    }
    t->Restart();
    int prod = ms * 1000;
    long long v = prod;
    ecx_this->u290 = (u32)v;
    ecx_this->u294 = (u32)((unsigned long long)v >> 32);
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8380 -- cCity::SetVisitEffectActive(flag, v).
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8380
void __fastcall FUN_00bd8380(cCity* ecx_this, void* edx, char flag, float v)
{
    ecx_this->b2fc = (u8)flag;
    ecx_this->f300 = v;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd83c0 -- intrusive_ptr release: null the slot and jump to the object's +0xc0 slot.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd83c0
void __fastcall FUN_00bd83c0(void** ecx_this, void* edx)
{
    void* p = *ecx_this;
    *ecx_this = 0;
    if (p != 0) {
        (*(void(__fastcall**)(void*))(*(int*)p + 0xc0))(p);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8480 -- destroy a range of 0x80-byte entries.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8480
void* __cdecl FUN_00bd8480(void* first, void* last, void* out)
{
    while (first != last) {
        void* p78 = *(void**)((char*)first + 0x78);
        if (p78 != 0) {
            (*(void(__fastcall**)(void*))(*(int*)p78 + 0xc0))(p78);
        }
        void* p70 = *(void**)((char*)first + 0x70);
        if (p70 != 0) {
            (*(void(__fastcall**)(void*))(*(int*)p70 + 0xc0))(p70);
        }
        FUN_00b638b0((char*)first + 0x50);
        FUN_00b638b0((char*)first + 0x30);
        first = (char*)first + 0x80;
        out = (char*)out + 0x80;
    }
    return out;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd84e0 -- get the +0x30 interface then cast to id 0xee9b2232.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd84e0
u32 __fastcall FUN_00bd84e0(IObj* ecx_this, void* edx)
{
    IObj* p = (IObj*)ecx_this->v30();
    if (p != 0) {
        return (u32)p->Cast(0xee9b2232);
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8500 -- cGameData slot.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8500
void __fastcall FUN_00bd8500(cCity* ecx_this, void* edx, char flag, void* owner)
{
    ecx_this->SetGameDataOwner2(owner);
    ecx_this->b1d4 = (u8)flag;
    IObj* made = ((cGameNounManager*)FUN_00b3d300())->CreateNoun(0x2e72cae);
    IObj* old = ecx_this->mp208;
    if (made != old) {
        if (made != 0) {
            made->v00();
        }
        ecx_this->mp208 = made;
        if (old != 0) {
            old->v04();
        }
    }
    ecx_this->mp208->SetEffectId(0x168bd70, 5.0f);
    ecx_this->mp208->DoF3d2(ecx_this);
    ecx_this->mRegion38.AsSlot38()->DoC470(1);
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8590 -- cCommunity::func54h then forward.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8590
void __fastcall FUN_00bd8590(cCommunity* ecx_this, void* edx, void* a)
{
    ecx_this->func54h(a);
    cCom108* o = ecx_this->mp108;
    o->mFwd70.Call38(a);
}

// ---------------------------------------------------------------------------------------------
// 0x00bd85c0 -- sum (elem[+0xc50] + 0.5) * 2/3 over +0x1f4..+0x1f8 into *out.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd85c0
void __fastcall FUN_00bd85c0(cCity* ecx_this, void* edx, float* out, int* count)
{
    int n = (int)(ecx_this->mEnd1f8 - ecx_this->mBeg1f4);
    int i = 0;
    *count = n;
    if (n > 0) {
        float& o = *out;
        for (cElem1f4** p = ecx_this->mBeg1f4; i < *count; ++i, ++p) {
            o += ((*p)->f0c50 + 0.5f) * 0.6666667f;
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8630 -- cCity::InVisitEffectWindow.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8630
int __fastcall FUN_00bd8630(cCity* ecx_this, void* edx)
{
    if (ecx_this->i1d8 == 2) {
        cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
        int e = nm->GetPlayerEmpireOrMinus1();
        if (ecx_this->i1dc == e) {
            return 1;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8660 -- pick the nearest qualifying combatant from the live list.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8660
IObj* __fastcall FUN_00bd8660(cCity* ecx_this, void* edx)
{
    ecx_this->mRegion38.mObj100.GetPosition();
    cElem1f4* found = 0;
    int pass = 0;
    do {
        if (ecx_this->mBeg1f4 != ecx_this->mEnd1f8) {
            float bestD = g_146847c;
            for (cElem1f4** it = ecx_this->mBeg1f4; it != ecx_this->mEnd1f8; ++it) {
                cElem1f4* e = *it;
                IX508* io = &e->mObj508;
                if (io->GetFileCount() == 2) {
                    continue;
                }
                IX54* q = io->Slot54();
                if ((q == 0 || q->Slot5c(0x3d5c477) == 0) && pass <= 0) {
                    continue;
                }
                float d = io->Distance();
                if (bestD > d) {
                    bestD = d;
                    found = e;
                }
            }
            if (found != 0) {
                return (IObj*)found;
            }
        }
        ++pass;
    } while (pass < 2);
    return (IObj*)found;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8750 -- normalized direction (free function: (out, target)).
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8750
void __cdecl FUN_00bd8750(Float3* out, Float3* target)
{
    cPlanetModel* pm = (cPlanetModel*)FUN_00b3d350();
    Float3 a;
    Float3 b;
    if (pm->Probe(target, g_1468454, &a) == 0) {
        Float3* p = pm->Sample(&b);
        a.x = p->x - target->x;
        a.y = p->y - target->y;
        a.z = p->z - target->z;
    }
    float inv = (float)(1.0 / sqrt(a.y * a.y + a.z * a.z + a.x * a.x + g_13ec4b8));
    out->x = inv * a.x;
    out->y = inv * a.y;
    out->z = inv * a.z;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8810 -- cGameData slot.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8810
char __fastcall FUN_00bd8810(cCity* ecx_this, void* edx, void* param)
{
    if (FUN_00b183f0(ecx_this, 0, param) == 0) {
        return 0;
    }
    cPlanetModel* pm = (cPlanetModel*)FUN_00b3d350();
    if (pm != 0) {
        int n = (int)(ecx_this->mEnd560 - ecx_this->mBeg55c);
        if (n > 0) {
            cElem55c* e = ecx_this->mBeg55c;
            do {
                if (e->kind == 0 && e->p4->p11c == ecx_this) {
                    pm->Despawn(e->p4);
                } else if (e->kind == 1) {
                    pm->Spawn(ecx_this, e->p0);
                } else if (e->kind == 2) {
                    pm->SpawnAlt(ecx_this, e->p0);
                }
                ++e;
                --n;
            } while (n != 0);
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd88c0 -- iterate the +0x55c vector despawning valid entries.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd88c0
void __fastcall FUN_00bd88c0(cCity* ecx_this, void* edx)
{
    int n = (int)(ecx_this->mEnd560 - ecx_this->mBeg55c);
    if (n <= 0) {
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (ecx_this->mBeg55c[i].p4 != 0) {
            if (FUN_00b3d350() != 0) {
                ((cPlanetModel*)FUN_00b3d350())->Attach(ecx_this->mBeg55c[i].p4);
                cElem55c* pe = &ecx_this->mBeg55c[i];
                pe->p4->AddEntry(ecx_this, pe->p0, 1);
                ((cPlanetModel*)FUN_00b3d350())->Despawn(ecx_this->mBeg55c[i].p4);
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8960 -- count typed buildings with a nonzero +0x289, times a global.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8960
int __fastcall FUN_00bd8960(cCity* ecx_this, void* edx)
{
    cCombatCarrier** it = ecx_this->mBeg340;
    cCombatCarrier** end = ecx_this->mEnd344;
    int n = 0;
    while (it != end) {
        if (((*it)->GetTypeId() == 0xff10521 || (*it)->GetTypeId() == 0x1007ae63) && (*it)->b289 != 0) {
            ++n;
        }
        ++it;
    }
    return (int)g_169c088 * n;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd89c0 -- 6 or 12 depending on the +0x324 object's +0x6c slot.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd89c0
int __fastcall FUN_00bd89c0(cCity* ecx_this, void* edx)
{
    int r = 0xc;
    IObj* p = ecx_this->mp324;
    if (p != 0) {
        u32 v = p->Slot6c();
        switch (v) {
        case 0:
            r = 6;
            break;
        case 1:
            r = 0xc;
            break;
        case 2:
            r = 6;
            break;
        case 3:
            r = 0xc;
            break;
        }
    }
    return r;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8a00 -- like 0x00bd89c0 but reduced by a terraforming count in the game mode.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8a00
int __fastcall FUN_00bd8a00(cCity* ecx_this, void* edx)
{
    IObj* p = ecx_this->mp324;
    int v = 0xc;
    if (p != 0) {
        u32 s = p->Slot6c();
        switch (s) {
        case 0:
            v = 6;
            break;
        case 1:
            v = 0xc;
            break;
        case 2:
            v = 6;
            break;
        case 3:
            v = 0xc;
            break;
        }
    }
    int lo = v;
    if (FUN_00b5b800() == (u32)&g_1654c05) {
        void* lu = FUN_010212a0();
        if (((cPlanetRecord*)lu)->GameMode() == 5) {
            void* tf = FUN_00b3d430(0);
            int b = ((cTerraformingMgr*)tf)->TerraformCount();
            b -= (int)(((char*)ecx_this->mEnd358 - (char*)ecx_this->mBeg354) >> 2);
            const int& m = (lo < b) ? lo : b;
            return m;
        }
    }
    return lo;
}
// ---------------------------------------------------------------------------------------------
// 0x00bd8aa0 -- three-way (i540) result plus a game-mode refinement.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8aa0
int __fastcall FUN_00bd8aa0(cCity* ecx_this, void* edx)
{
    switch (ecx_this->i540) {
    case 0:
        return (-(int)(ecx_this->b519 != 0) & 0xfffffffd) + 8;
    case 1:
        return (ecx_this->b519 == 0) * 2 + 4;
    case 2:
        return (ecx_this->b519 == 0) + 3;
    }
    if (((cPlanetRecord*)FUN_010212a0())->GameMode() == 5) {
        return 8;
    }
    int r = 0;
    return r;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8b10 -- 0x00bd8aa0 refined once more by the terraforming count.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8b10
int __fastcall FUN_00bd8b10(cCity* ecx_this, void* edx)
{
    typedef int (__fastcall *FT)(cCity*);
    int v = ((FT)FUN_00bd8aa0)(ecx_this);
    int lo = v;
    if (FUN_00b5b800() == (u32)&g_1654c05) {
        void* lu = FUN_010212a0();
        if (((cPlanetRecord*)lu)->GameMode() == 5) {
            void* tf = FUN_00b3d430(0);
            int b = ((cTerraformingMgr*)tf)->TerraformCount();
            b -= (int)(((char*)ecx_this->mEnd344 - (char*)ecx_this->mBeg340) >> 2);
            const int& m = (lo < b) ? lo : b;
            return m;
        }
    }
    return lo;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8b80 -- cCity::WealthAmount.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8b80
int __fastcall FUN_00bd8b80(cCity* ecx_this, void* edx)
{
    if (FUN_00b5b800() != (u32)&g_1654c05) {
        int v = ecx_this->i678;
        if (ecx_this->b698 != 0 && ecx_this->f304 > g_13f1cac) {
            v = v + v;
        }
        if (ecx_this->b6c0 != 0 && g_13f1cac > ecx_this->f304) {
            v = v / 2;
        }
        return v;
    }
    return ecx_this->i678;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8bd0 -- cCity::TickThings.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8bd0
void __fastcall FUN_00bd8bd0(cCity* ecx_this, void* edx)
{
    if (FUN_00b5b800() == (u32)&g_1654c05) {
        return;
    }
    if (ecx_this->b698 != 0) {
        long long t = ecx_this->mTimer6a0.GetElapsedTime();
        u32 hi = (u32)((unsigned long long)t >> 32);
        u32 lo = (u32)t;
        if (hi != 0 || lo > 60000) {
            ecx_this->b698 = 0;
            ecx_this->mTimer6a0.Restart();
        } else if (FUN_00c004c0(ecx_this, 0, 0) == 0 && FUN_00c004c0(ecx_this, 0, 1) != 0) {
            ecx_this->b698 = 0;
            ecx_this->mTimer6a0.Restart();
        }
    } else {
        long long t = ecx_this->mTimer6a0.GetElapsedTime();
        u32 hi = (u32)((unsigned long long)t >> 32);
        u32 lo = (u32)t;
        if ((hi != 0 || lo > 10000) &&
            FUN_00c004c0(ecx_this, 0, 0) == 0 && FUN_00c004c0(ecx_this, 0, 1) == 0) {
            int thresh = (int)(ecx_this->f304 - g_13f1cac);
            if (ecx_this->f304 == g_13ec4d0) {
                thresh += 10;
            }
            u32 r = RandomUint32Uniform(&g_1601760, 0, 200);
            if ((int)r < thresh) {
                FUN_00bd7d90(ecx_this, 0);
            } else {
                ecx_this->mTimer6a0.Restart();
            }
        }
    }
    if (ecx_this->b6c0 != 0) {
        long long t = ecx_this->mTimer6c8.GetElapsedTime();
        u32 hi = (u32)((unsigned long long)t >> 32);
        u32 lo = (u32)t;
        if (hi != 0 || lo > 60000) {
            ecx_this->b6c0 = 0;
            ecx_this->mTimer6c8.Restart();
        }
    } else {
        long long t = ecx_this->mTimer6c8.GetElapsedTime();
        u32 hi = (u32)((unsigned long long)t >> 32);
        u32 lo = (u32)t;
        if (hi != 0 || lo > 5000) {
            int thresh = (int)(g_13f1cac - ecx_this->f304);
            u32 r = RandomUint32Uniform(&g_1601760, 0, 200);
            if ((int)r < thresh) {
                ecx_this->b6c0 = 1;
                ecx_this->mTimer6c8.Restart();
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8d70 -- cCity::NearestCombatant(carrier).
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8d70
void* __fastcall FUN_00bd8d70(cCity* ecx_this, void* edx, cCombatCarrier* carrier)
{
    if (ecx_this->v2c() != 0) {
        return 0;
    }
    u32 start = 0;
    u32 stop = 3;
    if (carrier->iB1c == 1) {
        start = 3;
        stop = 4;
    }
    float best = g_146847c;
    Float3* pf = carrier->mObj34.GetPosition();
    float fx = pf->x, fy = pf->y, fz = pf->z;
    void* target = carrier->mObj508.Slot10();
    void* chosen = 0;
    for (u32 i = start; i < stop; ++i) {
        cCity* e = ecx_this->mBeg62c[i];
        char isTwo = (char)(e->i1d8 == 2);
        char isTarget = (char)(e->i1dc == (int)target);
        char has = 0;
        cCity** it = e->mBeg1e0;
        cCity** end = e->mEnd1e4;
        if (it != end) {
            do {
                if (has != 0) {
                    break;
                }
                has = (char)(*it == target);
                ++it;
            } while (it != end);
        }
        if (isTarget != 0) {
            chosen = e;
            break;
        }
        if (isTwo == 0) {
            if (has != 0) {
                chosen = e;
                break;
            }
            Float3* q = e->mRegion38.mObj100.GetPosition();
            float dz = fz - q->z;
            float dy = fy - q->y;
            float dx = fx - q->x;
            float d = dz * dz + dy * dy + dx * dx;
            if (d < best) {
                chosen = e;
                best = d;
            }
        }
    }
    return chosen;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8f30 -- cCity::AnyTwo (any live element with i1d8 == 2).
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8f30
char __fastcall FUN_00bd8f30(cCity* ecx_this, void* edx)
{
    cCity** it = ecx_this->mBeg62c;
    cCity** end = ecx_this->mEnd630;
    char r = 0;
    while (it != end) {
        if (r != 0) {
            break;
        }
        cCity* o = *it;
        r = (o->i1d8 == 2);
        ++it;
    }
    return r;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8f60 -- cCity::AnyThree.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8f60
char __fastcall FUN_00bd8f60(cCity* ecx_this, void* edx)
{
    cCombatCarrier** it = ecx_this->mBeg340;
    cCombatCarrier** end = ecx_this->mEnd344;
    bool r = false;
    while (it != end) {
        if (r) {
            break;
        }
        cCombatCarrier* o = *it;
        if (o->i290 > 0 || o->mSlot120.Test() != 0) {
            r = true;
        }
        ++it;
    }
    cCombatCarrier** it2 = ecx_this->mBeg354;
    cCombatCarrier** end2 = ecx_this->mEnd358;
    while (it2 != end2) {
        if (r) {
            break;
        }
        cCombatCarrier* o = *it2;
        if (o->i684 > 0 || o->mSlot588.Test() != 0) {
            r = true;
        }
        ++it2;
    }
    return r;
}

// ---------------------------------------------------------------------------------------------
// 0x00bd8fe0 -- change the civ's city-list entry equal to +0x2f0.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd8fe0
void __fastcall FUN_00bd8fe0(cCity* ecx_this, void* edx, void* a, void* b)
{
    cPlanet* planet = (cPlanet*)FUN_01021260();
    if (planet == 0) {
        return;
    }
    cCivData* civ = planet->GetCiv(a);
    cCivData* other = planet->GetCiv(b);
    if (civ == 0 || other == 0) {
        return;
    }
    int n = (int)(civ->mEnd40 - civ->mBeg3c);
    int i = 0;
    if (n > 0) {
        do {
            int** cities = civ->GetCities();
            if ((*cities)[i] == (int)ecx_this->u2f0) {
                break;
            }
            ++i;
        } while (i < n);
    }
    if (i != n) {
        civ->RemoveAt(i, other);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00bd9060 -- cCity::TriggerSomething.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd9060
void __fastcall FUN_00bd9060(cCity* ecx_this, void* edx, IObj* other)
{
    ecx_this->b2e3 = 0;
    FUN_00bebdd0(ecx_this->mp324, 0, (char*)other + 0xc4);
    void* tm = FUN_00b3d4d0();
    if (*(int*)((char*)tm + 0x2c) != 1 && *(int*)((char*)tm + 0x2c) != 2) {
        void* r = FUN_00b3d480(ecx_this);
        (void)r;
        char g = FUN_00ac8d60(ecx_this, 0, other);
        if (g == 0) {
            return;
        }
    }
    IObj* p = (IObj*)(*(void*(__fastcall**)(cCity*, int))(*(int*)ecx_this + 0x6c))(ecx_this, 0);
    (*(void(__fastcall**)(IObj*, int))(*(int*)p + 0x6c))(p, 0);
}

// ---------------------------------------------------------------------------------------------
// 0x00bd9140 -- cCity::EmitEffectIds.
// ---------------------------------------------------------------------------------------------
// @ 0x00bd9140
void __fastcall FUN_00bd9140(cCity* ecx_this, void* edx, IObj* other)
{
    int i = 0;
    ecx_this->b2e5 = (u8)i;
    int n = (int)(((char*)ecx_this->mEnd344 - (char*)ecx_this->mBeg340) >> 2);
    if (i < n) {
        do {
            cCombatCarrier* e = ecx_this->mBeg340[i];
            void* mgr = FUN_00b3d240();
            IObj* o = &e->mObj34;
            u32 a = other->Slot4c(0xffffffff, 1.0f);
            Float3 tmp;
            u32 b = o->Slot5c(&tmp, a);
            u32 c = (u32)(*(void*(__fastcall**)(IObj*, u32))(*(int*)o + 0x2c))(o, b);
            (*(void(__fastcall**)(void*, u32, u32))(*(int*)mgr + 0x5c))(mgr, 0x5f4d3ce, c);
            ++i;
        } while (i < n);
    }
}
