// Slice s00c22010 -- cSPCreatureBase / cInteractionAgent / cCombatant /
// cLocomotiveObject members (0x00c22010 .. 0x00c22f60, 27 functions).
// Reconstructed from the retail disassembly.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#define PVN(n) virtual void pv##n();

struct Vec3 { float x, y, z; };

// ---- globals referenced by the originals ---------------------------------------------------
extern float g_1687A00;   // 0x01687a00
extern float g_1687A04;   // 0x01687a04
extern float g_1687A0C;   // 0x01687a0c
extern float g_1687A14;   // 0x01687a14
extern float g_158129C;   // 0x0158129c
extern float g_15812A0;   // 0x015812a0
extern float g_15812D4;   // 0x015812d4
extern float g_15812D8;   // 0x015812d8
extern float g_15812DC;   // 0x015812dc
extern float g_15812E0;   // 0x015812e0
extern float g_15812E4;   // 0x015812e4
extern float g_15812E8;   // 0x015812e8
extern float g_1581344;   // 0x01581344
extern float g_146AA44;   // 0x0146aa44
extern float g_146AA40;   // 0x0146aa40 (FLT_MAX)
extern float g_13EC4D0;   // 0x013ec4d0
extern float g_1485378;   // 0x01485378 (zero)
extern void* g_158128C;   // 0x0158128c
extern uint32_t g_kBodyParts;  // 0x015716e8
extern uint8_t g_168D904; // 0x0168d904

namespace EA { namespace Random {
class RandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t nLimit);   // 0x00a68fb0
};
}}
extern EA::Random::RandomLinearCongruential sMathRandom;  // 0x01601760

namespace EA { namespace IO {
bool WriteUint32(void* pStream, const uint32_t* pValue, uint32_t nCount, int nSomething);  // 0x0093aa70
bool ReadInt32(void* pStream, int* pValue, uint32_t nCount, int nSomething);               // 0x0093a780
}}

// ---- free helpers --------------------------------------------------------------------------
void*   FUN_00b3d310();                                   // 0x00b3d310  global getter
void*   FUN_00b3d240();                                   // 0x00b3d240  global getter
void*   FUN_00b3d2b0();                                   // 0x00b3d2b0  global getter
void*   FUN_00401090();                                   // 0x00401090  species manager getter
void*   GetCurrentGameMode();                             // 0x00b5b800
float   FUN_004d12a0(int nArchetype);                     // 0x004d12a0
int*    FUN_00c9cec0(int nId);                            // 0x00c9cec0
char    FUN_006a08b0(void* pGlobal, uint32_t nHash, int* pCount, void** ppArray);  // 0x006a08b0
void    FUN_00ba5df0(void* pKey, void* pLocal);           // 0x00ba5df0
int     FUN_009b2340(void* pOut, int nMax, void* pObj, void* pFlags, int, int);   // 0x009b2340
void* __fastcall FUN_00cee330(void* pListOwner);          // 0x00cee330  first list entry
float __fastcall FUN_00cee380(void* pListOwner);          // 0x00cee380  sum of entries
void    FUN_00c1f6d0(int* pPos, int a, int b, int value); // 0x00c1f6d0  fixed_vector append
void    FUN_00f47380(void* p);                            // 0x00f47380  operator delete[]

class cSpeciesProfile;
class cSPCreatureBase;
class cInteractionTarget;
class cBehaviorStimuliOwner;
class cInteractionAgent;

// ---- the species profile -------------------------------------------------------------------
class cSpeciesProfile {
public:
    uint8_t  mPad000[0x504];    // +0x000
    float    mf0504;            // +0x504
    float    mf0508;            // +0x508
    float    mf050C;            // +0x50c
    uint8_t  mPad510[0x53c - 0x510];
    uint32_t mn053C;            // +0x53c
    uint8_t  mPad540[0x56c - 0x540];
    float    mf056C;            // +0x56c
    uint8_t  mPad570[0x590 - 0x570];
    float    mf0590;            // +0x590
    float    mf0594;            // +0x594
    uint8_t  mPad598[0x634 - 0x598];
    int      mn0634;            // +0x634

    void*    FUN_004d9050(void* pAnim);   // 0x004d9050
    void*    FUN_004d9030(void* pAnim);   // 0x004d9030
    void*    FUN_004d5500(const void* pKey);  // 0x004df550  (species manager method)
};

struct ResourceKey { uint32_t mA; uint32_t mB; uint32_t mC; };

// ---- the species manager -------------------------------------------------------------------
class cSpeciesManager {
public:
    cSpeciesProfile* GetProfile(const ResourceKey& key);     // 0x004df550
    cSpeciesProfile* GetAvatarProfile();                     // 0x004df420
    void* GetSpeciesArchetype(void* pKey, int nSomething);   // 0x004e0050
    char  GetReplacementKey(const ResourceKey& key, uint32_t nMode, ResourceKey* pOut);  // 0x004df7d0
};

// ---- the loco object wrapper returned by FUN_00b3d310 ---------------------------------------
class cLocoWrapper {
public:
    void FUN_00b48770(void* pCreature, int nFlag);   // 0x00b48770
};

// ---- the object returned by FUN_00b3d2b0 ---------------------------------------------------
class cObjB3D2B0 {
public:
    void FUN_00ac7d10(float fAmount, void* pAgent, int nZero);  // 0x00ac7d10
};

// ---- the object at creature+0xa8c ----------------------------------------------------------
class cObj0xA8C {
public:
    uint8_t  mPad0[0x5fc];      // +0x000
    uint32_t mn05FC;            // +0x5fc
};

// ---- the object at creature+0xe84 (species archetype) --------------------------------------
class cSpeciesArchetype {
public:
    uint8_t mPad0[0x388];       // +0x000
    uint8_t mb0388;             // +0x388
};

// ---- the animating creature at creature+0xb54 ----------------------------------------------
class cAnimatingCreature {
public:
    uint8_t mPad0[0x17c];       // +0x000
    void*   mp017C;             // +0x17c
};

// ---- the stimuli owner at creature+0xb4c ---------------------------------------------------
class cBehaviorStimuliOwner {
public:
    uint8_t  mPad000[0x88];            // +0x000
    uint8_t  mEntries[0x1d0 - 0x88];   // +0x088
    int      mn01D0;            // +0x1d0
    int      mn01D4;            // +0x1d4
    int      mn01D8;            // +0x1d8
    uint32_t mn01DC;            // +0x1dc

    int GetStimulusId() const { return *(const int*)((const char*)mEntries + mn01DC * 0xac); }
};

// ---- an interaction target (list element / interaction callback argument) -------------------
class cInteractionTarget {
public:
    uint8_t mPad000[0x34];         // +0x000
    uint8_t mSub34[0x12c - 0x34];  // +0x034 (sub-object passed to FUN_00c15d50)
    int     mnType12C;             // +0x12c
    int     mn0130;                // +0x130
    float   mf0134;                // +0x134
    int     GetAttackState();      // 0x00c35b60
};

// ---- reference-counted object (AddRef slot 0, Release slot 4) -------------------------------
class IRefCounted {
public:
    virtual void AddRef();       // 0x00
    virtual void Release();      // 0x04
};

// ---- a tag-addressed object: slot 0x0c returns the owning creature --------------------------
class ITagObject {
public:
    virtual void s00();          // 0x00
    virtual void s04();          // 0x04
    virtual void s08();          // 0x08
    virtual void* GetByTag(uint32_t nTag);   // 0x0c
};

// ---- serialization stream wrappers ---------------------------------------------------------
class cOutStream {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7)
    virtual void* GetSerializationTarget();   // 0x20
};
class cSerTarget {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5)
    virtual void* GetStream();                // 0x18
};
class cVarListSerializer {
public:
    uint8_t mStorage[0xa14];      // stack storage
    cVarListSerializer(void* pOwner, void* pList, uint32_t nId);  // 0x692f90
    char SerializeOut(void* pStream);   // 0x692900
    char SerializeIn(void* pStream);    // 0x693e10
};

// ---- the object embedded at creature+0x58 --------------------------------------------------
class cSub58 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11) PVN(12)
    virtual void vIdx13();       // 0x34
    uint8_t mPad04[0x40 - 4];    // +0x04 .. +0x3f
};

// =============================================================================================
// the four base sub-objects of the creature, laid out by the compiler in this order:
//   cGameData          +0x000  (size 0x34)
//   cInteractionAgent  +0x034  (size 0x8c)
//   cLocomotiveObject  +0x0c0  (size 0x4e8)
//   cCombatant         +0x5a8  (size 0x40)
// =============================================================================================

class cGameData {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11)
    virtual void* vIdx12();      // 0x30
    virtual void  vIdx13(int);   // 0x34
    virtual void  vIdx14(int);   // 0x38
    PVN(15) PVN(16) PVN(17) PVN(18) PVN(19)
    virtual void  vIdx20();      // 0x50
    PVN(21) PVN(22) PVN(23) PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29)
    PVN(30) PVN(31)
    virtual float vIdx32(int);   // 0x80
    PVN(33) PVN(34) PVN(35) PVN(36) PVN(37) PVN(38) PVN(39) PVN(40) PVN(41) PVN(42)
    virtual void  vIdx43(int);   // 0xac
    PVN(44)
    virtual void* vIdx45(int);   // 0xb4
    PVN(46)
    PVN(47) PVN(48) PVN(49) PVN(50) PVN(51) PVN(52) PVN(53)
    virtual int   vIdx54();      // 0xd8
    PVN(55) PVN(56) PVN(57) PVN(58) PVN(59)
    virtual void  vIdx60(int);   // 0xf0
    uint8_t mPad00[0x30];        // +0x04 .. +0x33
};

class cInteractionAgent {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11)
    virtual void  ia30(void* pArg);            // 0x30
    PVN(13)
    virtual float GetBundleCapacity(uint32_t nToolType);  // 0x38

    void*  mpListBegin;          // +0x04
    void*  mpListEnd;            // +0x08
    uint8_t mPad0c[0x18 - 0x0c]; // +0x0c
    void*  mp0x18;               // +0x18
    uint8_t mPad1c[0x20 - 0x1c];
    float  mf0x20;               // +0x20
    cSub58 mSub58;               // +0x24
    uint8_t mPad64[0x89 - 0x64]; // +0x64
    uint8_t mb0x89;              // +0x89
    uint8_t mPad8a[0x8c - 0x8a]; // +0x8a

    float FUN_00c22530();                 // 0x00c22530
    void  FUN_010829f0(void* pArg);       // 0x010829f0
    void  FUN_00c22f60(void* pArg);       // 0x00c22f60
};

class cLocomotiveObject {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15)
    virtual void lo40(float fScale);    // 0x40
    PVN(17) PVN(18) PVN(19)
    virtual char lo50();                // 0x50
    PVN(21)
    virtual char lo58();                // 0x58

    uint8_t mPad04[0x6c - 0x04]; // +0x04
    uint8_t mb0x6c;              // +0x6c
    uint8_t mPad6d[0x75 - 0x6d]; // +0x6d
    uint8_t mb0x75;              // +0x75
    uint8_t mPad76[0x4e8 - 0x76];// +0x76

    void FUN_00c226c0(char nFlag);   // 0x00c226c0
};

class cCombatant {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18)
    PVN(19) PVN(20) PVN(21)
    virtual float GetMaxHealth();        // 0x58

    uint8_t mPad04[0x34 - 0x04]; // +0x04
    void*   mp0x34;              // +0x34
    float   mf0x38;              // +0x38
    uint8_t mPad3c[0x40 - 0x3c]; // +0x3c

    float GetHealthRatio();              // 0x00bfc490
    void  PartialRepair(float fAmount);  // 0x00bfd1a0
    void  SetHealth(float fValue);       // 0x00f924e0
    int   FUN_00c22010();                // 0x00c22010
};

// ---- the eastl fixed_vector<int,8> used by FUN_00c22010 -------------------------------------
class cFixedVectorInt8 {
public:
    int* mpBegin;                // +0x00
    int* mpEnd;                  // +0x04
    int* mpCap;                  // +0x08
    int  mBuffer[8];             // +0x0c
    void DoInsertValue(int* pPos, const int& value);   // 0x004281d0
};

// =============================================================================================
class cSPCreatureBase : public cGameData, public cInteractionAgent,
                        public cLocomotiveObject, public cCombatant {
public:
    // own members, from +0x5e8
    uint8_t  mPad5e8[0xa8c - 0x5e8];
    cObj0xA8C* mp0xA8C;          // +0xa8c
    uint8_t  mPadA90[0xb20 - 0xa90];
    cSpeciesProfile* mpSpeciesProfile;  // +0xb20
    uint32_t mn0xB24;            // +0xb24
    ResourceKey mKey0xB28;       // +0xb28
    int      mn0xB34;            // +0xb34 (age)
    uint8_t  mPadB38[0xb48 - 0xb38];
    void*    mp0xB48;            // +0xb48  (object with FUN_00bc9fe0)
    cBehaviorStimuliOwner* mpB4C;// +0xb4c
    uint8_t  mPadB50[0xb54 - 0xb50];
    cAnimatingCreature* mp0xB54; // +0xb54
    uint8_t  mPadB58[0xb67 - 0xb58];
    uint8_t  mb0xB67;            // +0xb67
    uint8_t  mPadB68[0xbbc - 0xb68];
    float    mf0xBBC;            // +0xbbc
    uint8_t  mPadBC0[0xe70 - 0xbc0];
    int      mn0xE70;            // +0xe70
    int      mn0xE74;            // +0xe74
    uint8_t  mPadE78[0xe80 - 0xe78];
    void*    mp0xE80;            // +0xe80
    cSpeciesArchetype* mp0xE84;  // +0xe84
    uint8_t  mPadE88[0xfc4 - 0xe88];
    int      mn0xFC4;            // +0xfc4
    uint8_t  mPadFC8[0xff8 - 0xfc8];
    int      mn0xFF8;            // +0xff8
    uint8_t  mPadFFC[0x1004 - 0xffc];
    float    mf0x1004;           // +0x1004
    float    mf0x1008;           // +0x1008
    float    mf0x100C;           // +0x100c
    uint8_t  mPad1010[0x1014 - 0x1010];
    void*    mp0x1014;           // +0x1014
    uint8_t  mPad1018[0x102c - 0x1018];
    int      mn0x102C;           // +0x102c

    // ---- helper calls (thiscall) ----
    void  FUN_00c21bf0(int a, int b);            // 0x00c21bf0  CheckCreatureModel
    char  FUN_00c0c2d0();                        // 0x00c0c2d0  IsDefaultSpecies_
    float FUN_00c0b9c0();                        // 0x00c0b9c0
    void  FUN_00c0b9d0(float fValue);            // 0x00c0b9d0
    char  FUN_00c0bab0();                        // 0x00c0bab0
    char  FUN_00c0ba30();                        // 0x00c0ba30
    int   FUN_00c0c080(int nId);                 // 0x00c0c080  FindIndex
    char  FUN_00b183f0(void* pArg);              // 0x00b183f0
    void  FUN_00c1d640(const char* pVox, int a, int b);  // 0x00c1d640
    void  FUN_00c15d50(void* pArg, int a, int b);        // 0x00c15d50
    void  FUN_00c42350();                        // 0x00c42350
    char  FUN_00c0e0c0(int nType);                       // 0x00c0e0c0
    void  FUN_00c14aa0(void* pStream);                   // 0x00c14aa0
    void  FUN_00c0bc20Write(void* pStream);              // 0x00c0bc20  cSPCreatureBase::Write

    // ---- sliced members ----
    void  FUN_00c22210(int nAge);                        // 0x00c22210
    void  FUN_00c22240();                                // 0x00c22240
    void  FUN_00c222f0(cSpeciesProfile* pNew);           // 0x00c222f0
    bool  FUN_00c22470(void* pArg);                      // 0x00c22470
    float GetBaseMaxHitPoints();                         // 0x00c22720
    char  FUN_00c22750();                                // 0x00c22750
    void  FUN_00c227c0();                                // 0x00c227c0
    void  FUN_00c227f0(int x, int y, int z);            // 0x00c227f0
    int   FUN_00c22830(int nValue);                      // 0x00c22830
    void  FUN_00c22870();                                // 0x00c22870
    void  FUN_00c228c0Write(void* pStream);              // 0x00c228c0
    void  FUN_00c22930Read(void* pStream);               // 0x00c22930
    char  FUN_00c229a0();                                // 0x00c229a0
    void  FUN_00c22a30();                                // 0x00c22a30
    char  FUN_00c22a80(cInteractionTarget* pTarget);     // 0x00c22a80
    void  FUN_00c22ae0();                                // 0x00c22ae0
    char  FUN_00c22ca0(int nType);                       // 0x00c22ca0
    void  FUN_00c22cb0(uint32_t nVox);                   // 0x00c22cb0
    int   FUN_00c22dd0();                                // 0x00c22dd0
    void  FUN_00c22ee0(void* pObj);                      // 0x00c22ee0
};

// ---- the object at creature+0xb48 ----------------------------------------------------------
class cObj0xB48 {
public:
    void FUN_00bc9fe0();     // 0x00bc9fe0
};

// ---- the object at creature+0x3c accepted by FUN_00c22e30 -----------------------------------
class cArg22E30 {
public:
    float   mf000;           // +0x00 (the value being drained)
    uint8_t mPad004[0x3c - 4];
    ITagObject* mp03C;       // +0x3c
};

// =============================================================================================
// definitions

// @ 0x00c22010
int cCombatant::FUN_00c22010()
{
    cSPCreatureBase* pOwner = (cSPCreatureBase*)this;
    int nResult = -1;

    if (pOwner->mp0xE84 == 0 || pOwner->mp0xE84->mb0388 == 0) {
        cAnimatingCreature* pAnim = pOwner->mp0xB54;
        if (pOwner != 0 && pAnim != 0 && pAnim->mp017C != 0) {
            uint32_t aFlags[4] = { 1, g_kBodyParts, 0, 0 };
            int aOut[255];
            int n = FUN_009b2340(aOut, 0xff, *(void**)pAnim->mp017C, aFlags, 0, 0);
            if (n != 0)
                nResult = aOut[0];
        }
    } else {
        cFixedVectorInt8 vec;
        vec.mpBegin = vec.mBuffer;
        vec.mpEnd   = vec.mBuffer;
        vec.mpCap   = vec.mBuffer + 8;

        cAnimatingCreature* pAnim = pOwner->mp0xB54;
        if (pOwner != 0 && pAnim != 0 && pAnim->mp017C != 0) {
            uint32_t aFlags[4] = { 1, g_kBodyParts, 0, 0 };
            int aOut[255];
            int n = FUN_009b2340(aOut, 0xff, *(void**)pAnim->mp017C, aFlags, 0, 0);
            if (n != 0)
                nResult = aOut[0];
        }

        if (vec.mpEnd < vec.mpCap) {
            *vec.mpEnd = nResult;
            if (vec.mpEnd != 0)
                vec.mpEnd += 1;
        } else {
            vec.DoInsertValue(vec.mpEnd, nResult);
        }
        if (pOwner->mpSpeciesProfile->mf0590 > 0.0f) {
            int* p = (int*)pOwner->mpSpeciesProfile->FUN_004d9050(pOwner->mp0xB54);
            FUN_00c1f6d0(vec.mpEnd, p[0], p[1], nResult);
        }
        if (pOwner->mpSpeciesProfile->mf0594 > 0.0f) {
            int* p = (int*)pOwner->mpSpeciesProfile->FUN_004d9030(pOwner->mp0xB54);
            FUN_00c1f6d0(vec.mpEnd, p[0], p[1], nResult);
        }
        int nCount = (int)(vec.mpEnd - vec.mpBegin);
        nResult = vec.mpBegin[sMathRandom.RandomUint32Uniform((uint32_t)nCount)];
        if (vec.mpBegin != 0 && vec.mpBegin != vec.mBuffer)
            FUN_00f47380(vec.mpBegin);
    }
    return nResult;
}

// @ 0x00c22210
void cSPCreatureBase::FUN_00c22210(int nAge)
{
    mn0xB34 = nAge;
    FUN_00c21bf0(1, 1);
    this->mSub58.vIdx13();
}

// @ 0x00c22240
void cSPCreatureBase::FUN_00c22240()
{
    float fMax = this->GetMaxHealth();
    float fRatio = this->mf0x38 / fMax;
    mn0xB34 = 1;
    FUN_00c21bf0(1, 1);
    this->mSub58.vIdx13();
    float fScale = this->vIdx32(0);
    this->lo40(fScale);
    ((cLocoWrapper*)FUN_00b3d310())->FUN_00b48770(this, 1);
    float f = this->GetMaxHealth() * fRatio;
    this->SetHealth(f);
    this->mb0x89 = 1;
    ((cObj0xB48*)mp0xB48)->FUN_00bc9fe0();
}

// @ 0x00c222f0
void cSPCreatureBase::FUN_00c222f0(cSpeciesProfile* pNew)
{
    cSpeciesProfile* pOld = mpSpeciesProfile;
    mpSpeciesProfile = pNew;

    bool bDiff;
    uint32_t nBaseline = mn0xB24;
    if (pOld == pNew && (pNew == 0 || pNew->mn053C == nBaseline))
        bDiff = false;
    else
        bDiff = true;

    bool bSame = (pOld == pNew);

    if (pNew != 0) {
        mn0xB24 = pNew->mn053C;
        mKey0xB28.mA = ((uint32_t*)&pNew->mf0504)[0];
        mKey0xB28.mB = ((uint32_t*)&pNew->mf0504)[1];
        mKey0xB28.mC = ((uint32_t*)&pNew->mf0504)[2];
    } else {
        cSpeciesManager* mgr = (cSpeciesManager*)FUN_00401090();
        cSpeciesProfile* p = mgr->GetAvatarProfile();
        mpSpeciesProfile = p;
        if (p != 0) {
            mn0xB24 = p->mn053C;
            mKey0xB28.mA = ((uint32_t*)&p->mf0504)[0];
            mKey0xB28.mB = ((uint32_t*)&p->mf0504)[1];
            mKey0xB28.mC = ((uint32_t*)&p->mf0504)[2];
        }
    }

    if (g_168D904 == 0)
        FUN_00c21bf0(bDiff ? 1 : 0, bSame ? 1 : 0);
    this->vIdx43(bDiff ? 1 : 0);

    int idx = FUN_00c0c080(0x25);
    if (this->vIdx45(idx) == 0) idx = FUN_00c0c080(0x54);
    if (this->vIdx45(idx) == 0) idx = FUN_00c0c080(0x4d);
    mn0xE74 = idx;

    int idx2 = FUN_00c0c080(0x1e);
    if (this->vIdx45(idx2) == 0) idx2 = FUN_00c0c080(0x3e);
    if (this->vIdx45(idx2) == 0)
        mn0xE70 = FUN_00c0c080(0x4a);
    else
        mn0xE70 = idx2;
}

// @ 0x00c22470
bool cSPCreatureBase::FUN_00c22470(void* pArg)
{
    if (mb0xB67 != 0 && mb0x75 == 0)
        return true;

    cSpeciesProfile* p1 = ((cSpeciesManager*)FUN_00401090())->GetProfile(mKey0xB28);
    if (FUN_00b183f0(pArg) == 0)
        return false;

    bool b;
    if (mKey0xB28.mA == 0) {
        b = (mb0x75 == 0);
    } else {
        cSpeciesProfile* p2 = ((cSpeciesManager*)FUN_00401090())->GetProfile(mKey0xB28);
        if (p1 != p2) {
            FUN_00c222f0(p2);
            b = (mpSpeciesProfile != 0);
        } else {
            mpSpeciesProfile = p2;
            FUN_00c21bf0(1, 1);
            b = (mpSpeciesProfile != 0);
        }
    }
    if (b && mp0xE80 != 0)
        mp0xE84 = (cSpeciesArchetype*)((cSpeciesManager*)FUN_00401090())
                      ->GetSpeciesArchetype(mp0xE80, 0);
    return b;
}

// @ 0x00c22530
float cInteractionAgent::FUN_00c22530()
{
    int nType = 0;
    if (FUN_00cee330(this) != 0)
        nType = ((cInteractionTarget*)FUN_00cee330(this))->mnType12C;
    return GetBundleCapacity((uint32_t)nType);
}

// @ 0x00c22560
float cInteractionAgent::GetBundleCapacity(uint32_t nToolType)
{
    float fResult = mf0x20;
    cSPCreatureBase* pOwner = (cSPCreatureBase*)this;
    uint32_t nHash = 0;
    int nCount = 0;
    void* pArray = 0;

    switch (nToolType) {
    case 1: fResult = g_15812D4; nHash = 0x48888fad; break;
    case 2: fResult = g_15812D8; nHash = 0x0d4120fd; break;
    case 3: fResult = g_15812DC; nHash = 0xbebd9b84; break;
    case 4: fResult = g_15812E0; nHash = 0x250bd2bd; break;
    case 5: return g_15812E4;
    case 6: return g_146AA40;
    case 7: return g_15812E8;
    default:
        return fResult;
    }

    int nIdx = pOwner->mpSpeciesProfile->mn0634 - 1;
    if (pOwner->mpSpeciesProfile->mn0634 != 0) {
        if (FUN_006a08b0(g_158128C, nHash, &nCount, &pArray) != 0 &&
            nIdx < nCount)
            fResult += ((float*)pArray)[nIdx];
    }
    return fResult;
}

// @ 0x00c226c0
void cLocomotiveObject::FUN_00c226c0(char nFlag)
{
    if (this->lo50() == 0) {
        if (nFlag != 0)
            ((cSPCreatureBase*)this)->vIdx60(0x29b);
        mb0x6c = (uint8_t)nFlag;
        return;
    }
    mb0x6c = (uint8_t)nFlag;
}

// @ 0x00c22720
float cSPCreatureBase::GetBaseMaxHitPoints()
{
    int n = this->vIdx54();
    float f = FUN_004d12a0(n);
    return f + mpSpeciesProfile->mf056C;
}

// @ 0x00c22750
char cSPCreatureBase::FUN_00c22750()
{
    if (FUN_00c0c2d0() != 0 ||
        this->lo58() != 0 ||
        GetCurrentGameMode() == (void*)0x1654c02 ||
        GetCurrentGameMode() == (void*)0x1654c04)
        return 1;
    return 0;
}

// @ 0x00c227c0
void cSPCreatureBase::FUN_00c227c0()
{
    mn0xFF8 = -1;
}

// @ 0x00c227f0
void cSPCreatureBase::FUN_00c227f0(int x, int y, int z)
{
    *(int*)&mf0x1004 = x;
    *(int*)&mf0x1008 = y;
    *(int*)&mf0x100C = z;
}

// @ 0x00c22830
int cSPCreatureBase::FUN_00c22830(int nValue)
{
    if (nValue != -1)
        mn0xFC4 = nValue;
    return mn0xFC4;
}

// @ 0x00c22870
void cSPCreatureBase::FUN_00c22870()
{
    // The cInteractionAgent base subobject. Spelled through a byte pointer so the
    // object code keeps the adjusted pointer in a register (a derived->base cast
    // makes this compiler emit a null check the original does not have).
    cInteractionAgent* pAgent = (cInteractionAgent*)((char*)this + sizeof(cGameData));
    if (FUN_00cee330(pAgent) == 0)
        return;
    cInteractionTarget* e = (cInteractionTarget*)FUN_00cee330(pAgent);
    void* p = (e != 0) ? (void*)e->mSub34 : 0;
    FUN_00c15d50(p, 0, 0);
    pAgent->ia30((void*)FUN_00cee330(pAgent));
}

// @ 0x00c228c0
void cSPCreatureBase::FUN_00c228c0Write(void* pStream)
{
    cOutStream* pOuter = (cOutStream*)pStream;
    cSerTarget* pTarget = (cSerTarget*)pOuter->GetSerializationTarget();
    uint32_t nTag = 0x4f176642;
    void* pS = pTarget->GetStream();
    EA::IO::WriteUint32(pS, &nTag, 1, 0);
    this->FUN_00c0bc20Write(pStream);
    cVarListSerializer ser(this, (void*)0x015721f0, 0x1a80d26);
    ser.SerializeOut(pStream);
}

// @ 0x00c22930
void cSPCreatureBase::FUN_00c22930Read(void* pStream)
{
    cOutStream* pOuter = (cOutStream*)pStream;
    cSerTarget* pTarget = (cSerTarget*)pOuter->GetSerializationTarget();
    int nTag;
    void* pS = pTarget->GetStream();
    EA::IO::ReadInt32(pS, &nTag, 1, 0);
    this->FUN_00c14aa0(pStream);
    cVarListSerializer ser(this, (void*)0x015721f0, 0x1a80d26);
    ser.SerializeIn(pStream);
}

// @ 0x00c229a0
char cSPCreatureBase::FUN_00c229a0()
{
    if (mKey0xB28.mA == 0 ||
        ((cSpeciesManager*)FUN_00401090())->GetProfile(mKey0xB28) != 0)
        return 1;

    ResourceKey local;
    local.mA = 0; local.mB = 0; local.mC = 0;
    void* p = mp0xE80;
    if (p == 0)
        p = (void*)0xbbaaecee;
    char ok = ((cSpeciesManager*)FUN_00401090())
                  ->GetReplacementKey(mKey0xB28, (uint32_t)p, &local);
    if (ok != 0) {
        FUN_00ba5df0(&mKey0xB28, &local);
        mKey0xB28 = local;
    }
    return ok;
}

// @ 0x00c22a30
void cSPCreatureBase::FUN_00c22a30()
{
    FUN_00c42350();
    mp0xA8C->mn05FC |= 0x80;
}

// @ 0x00c22a80
char cSPCreatureBase::FUN_00c22a80(cInteractionTarget* pTarget)
{
    if (pTarget->mnType12C > 4)
        return 0;
    int nState = pTarget->GetAttackState();
    if (nState != 6 && pTarget->mn0130 != 1) {
        float fDist = pTarget->mf0134;
        float fCap = this->GetBundleCapacity((uint32_t)pTarget->mnType12C);
        if (fDist < fCap)
            return 0;
    }
    return 1;
}

// @ 0x00c22ae0
void cSPCreatureBase::FUN_00c22ae0()
{
    cInteractionAgent* pAgent = (cInteractionAgent*)this;
    cInteractionTarget* pTarget = (cInteractionTarget*)FUN_00cee330(pAgent);
    if (pTarget == 0)
        return;
    if (pTarget->mnType12C == 6)
        return;

    float fBbc = FUN_00c0b9c0();
    if (g_1687A14 > fBbc) {
        /* fall through to body */
    } else {
        float fRatio = this->GetHealthRatio() * g_13EC4D0;
        if (g_1687A14 <= fRatio)
            return;
    }

    float fHealth = this->mf0x38;
    float fGap = this->GetMaxHealth() - fHealth;
    float a = fGap / g_15812A0;
    float b = (g_1687A00 - FUN_00c0b9c0()) / g_158129C;
    float m1 = (b > a) ? b : a;
    float s = FUN_00cee380(pAgent);
    float m2 = (m1 > s) ? s : m1;

    float fBbc2 = FUN_00c0b9c0();
    FUN_00c0b9d0(fBbc2 + g_158129C * m1);
    this->PartialRepair(g_15812A0 * m1);
    ((cObjB3D2B0*)FUN_00b3d2b0())->FUN_00ac7d10(m2, pAgent, 0);
}

// @ 0x00c22c40
int __stdcall FUN_00c22c40(int nType)
{
    switch (nType) {
    case 0: return 10;
    case 1: return 7;
    case 2: return 9;
    case 3: return 8;
    case 4: return 0x17;
    }
    return 0;
}

// @ 0x00c22ca0
char cSPCreatureBase::FUN_00c22ca0(int nType)
{
    return FUN_00c0e0c0(0x2c39200);
}

// @ 0x00c22cb0
void cSPCreatureBase::FUN_00c22cb0(uint32_t nVox)
{
    switch (nVox) {
    case 0:
        FUN_00c1d640("vcode_go_eat", 2, 0); return;
    case 3:
        FUN_00c1d640("vsoc_get_tool_rack", 2, 0); return;
    case 7:
    case 8:
    case 10:
    case 0xf:
        FUN_00c1d640("vcode_go_battle", 2, 0); return;
    case 0x29a:
        FUN_00c1d640("vcode_resp_illegal", 2, 0); return;
    case 0x29b:
        if (FUN_00c0bab0() != 0) { FUN_00c1d640("vcode_select_gung_ho", 2, 0); return; }
        if (FUN_00c0ba30() != 0) { FUN_00c1d640("vcode_select_grumble", 2, 0); return; }
        FUN_00c1d640("vcode_select", 2, 0); return;
    case 0x29c:
        FUN_00c1d640("vcode_arrived", 2, 0); return;
    }
    FUN_00c1d640("vcode_go_mot", 2, 0);
}

// @ 0x00c22dd0
int cSPCreatureBase::FUN_00c22dd0()
{
    if ((uint32_t)(mn0x102C - 1) <= 0xa)
        return FUN_00c9cec0(mn0x102C)[0x10 / 4];
    return 0;
}

// @ 0x00c22e30
char __cdecl FUN_00c22e30(cArg22E30* pArg, float fDelta)
{
    if (pArg->mp03C == 0)
        return 0;
    cSPCreatureBase* pCreature = (cSPCreatureBase*)pArg->mp03C->GetByTag(0x4f176642);
    if (pCreature == 0)
        return 0;
    cInteractionTarget* e =
        (cInteractionTarget*)FUN_00cee330((cInteractionAgent*)pCreature);
    cBehaviorStimuliOwner* pStim = pCreature->mpB4C;
    int nEntry = 0;
    if (pStim->mn01DC > 1)
        nEntry = pStim->GetStimulusId();
    if ((e != 0 && e->mnType12C == 5) || pStim->mn01D8 == 0x462855e ||
        nEntry == (int)0xf56bb5b1) {
        pArg->mf000 = g_1581344;
        return 1;
    }
    float fNew = pArg->mf000 - fDelta;
    pArg->mf000 = fNew;
    if (fNew > g_146AA44)
        return 1;
    return 0;
}

// @ 0x00c22ee0
void cSPCreatureBase::FUN_00c22ee0(void* pObj)
{
    void* pOld = mp0x1014;
    if (pObj != pOld) {
        if (pObj != 0)
            ((IRefCounted*)pObj)->AddRef();
        mp0x1014 = pObj;
        if (pOld != 0)
            ((IRefCounted*)pOld)->Release();
    }
    this->vIdx13((int)pObj);
    void* pRet = this->vIdx12();
    void* pOld2 = this->mp0x18;
    if (pRet != pOld2) {
        if (pRet != 0)
            ((IRefCounted*)pRet)->AddRef();
        this->mp0x18 = pRet;
        if (pOld2 != 0)
            ((IRefCounted*)pOld2)->Release();
    }
}

// @ 0x00c22f60
void cInteractionAgent::FUN_00c22f60(void* pArg)
{
    FUN_010829f0(pArg);
    // The owning creature is this base subobject minus sizeof(cGameData).
    cSPCreatureBase* pOwner = (cSPCreatureBase*)((char*)this - sizeof(cGameData));
    cInteractionAgent* pAgent = (cInteractionAgent*)((char*)pOwner + sizeof(cGameData));
    if (FUN_00cee330(pAgent) == 0)
        return;
    cInteractionTarget* e = (cInteractionTarget*)FUN_00cee330(pAgent);
    void* p = (e != 0) ? (void*)e->mSub34 : 0;
    pOwner->FUN_00c15d50(p, 0, 0);
    pAgent->ia30((void*)FUN_00cee330(pAgent));
}