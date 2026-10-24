// Slice s00bd1820 - the Simulator building class family (cBuilding and its derived
// cBuildingCityHall / cBuildingIndustry / cBuildingHouse / cBuildingEntertainment /
// cBuildingScenario), plus the cBuildingScenario coordinate-vector helpers.
//
// cBuilding is modelled as ONE flat struct. Each base subobject's vtable pointer is
// stored by hand at its fixed offset, so no multiple inheritance (and therefore no
// null-check base adjustments) is needed.

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

// A six-float box { min(x,y,z), max(x,y,z) } passed to cSpatialObject::SetLocalExtents.
struct AABB { float minx, miny, minz, maxx, maxy, maxz; };

// ----------------------------------------------------------------------------
// Globals (addresses relocated; the names matter only for readability).
extern float gVec3Zero[3];         // 0x0168b66c .. 0x0168b674
extern float gExtentMin;           // 0x01437c88
extern float gExtentMax;           // 0x013eeda0
extern float gRealOne;             // 0x01485720 (_HK_REAL_ONE)
extern float gPropDefault;         // 0x013ec5b4
extern float gScenarioRotation[9]; // 0x0168bc38
extern wchar_t gEmptyString16[];   // 0x01667bac (static empty eastl wide string)
extern const wchar_t gBuildingName[]; // 0x01467a64 L"UNINITIALIZED BUILDING NAME"

// vtable storage placeholders: the names stand in for the image's vtbl_* symbols so
// chk.py can mask the immediate stores.
extern char cBuilding_vtable0[];                 // 0x014670b8
extern char cBuilding_vtable1[];                 // 0x014670a4
extern char cBuilding_vtable2[];                 // 0x01466fe0
extern char cBuilding_vtable3[];                 // 0x01466fc0
extern char cBuilding_vtable4[];                 // 0x01466f58
extern char cBuilding_vtable5[];                 // 0x01466f30
extern char cPlaceableStructure_baseVtable[];    // 0x01466c14 (interim vptr)
extern char cBuildingCityHall_vtable0[];         // 0x014672f0
extern char cBuildingCityHall_vtable1[];         // 0x014672dc
extern char cBuildingCityHall_vtable2[];         // 0x01467218
extern char cBuildingCityHall_vtable3[];         // 0x014671f8
extern char cBuildingCityHall_vtable4[];         // 0x01467190
extern char cBuildingCityHall_vtable5[];         // 0x01467168
extern char cBuildingIndustry_vtable0[];         // 0x01467528
extern char cBuildingIndustry_vtable1[];         // 0x01467514
extern char cBuildingIndustry_vtable2[];         // 0x01467450
extern char cBuildingIndustry_vtable3[];         // 0x01467430
extern char cBuildingIndustry_vtable4[];         // 0x014673c8
extern char cBuildingIndustry_vtable5[];         // 0x014673a4
extern char cBuildingHouse_vtable0[];            // 0x01467768
extern char cBuildingHouse_vtable1[];            // 0x01467754
extern char cBuildingHouse_vtable2[];            // 0x01467690
extern char cBuildingHouse_vtable3[];            // 0x01467670
extern char cBuildingHouse_vtable4[];            // 0x01467608
extern char cBuildingHouse_vtable5[];            // 0x014675e0
extern char cBuildingEntertainment_vtable0[];    // 0x014679a0
extern char cBuildingEntertainment_vtable1[];    // 0x0146798c
extern char cBuildingEntertainment_vtable2[];    // 0x014678c8
extern char cBuildingEntertainment_vtable3[];    // 0x014678a8
extern char cBuildingEntertainment_vtable4[];    // 0x01467840
extern char cBuildingEntertainment_vtable5[];    // 0x0146781c
extern char cBuildingScenario_vtable0[];         // 0x01467c30
extern char cBuildingScenario_vtable1[];         // 0x01467c1c
extern char cBuildingScenario_vtable2[];         // 0x01467b58
extern char cBuildingScenario_vtable3[];         // 0x01467b38
extern char cBuildingScenario_vtable4[];         // 0x01467ad0
extern char cBuildingScenario_vtable5[];         // 0x01467aac

// ----------------------------------------------------------------------------
// Free helpers / base-subobject constructors in the image.
extern "C" void __fastcall ctor_cGameData(void* p);          // 0x00b18660
extern "C" void __fastcall ctor_cSpatialObject(void* p);     // 0x00c89630
extern "C" void __fastcall ctor_cInteractionTarget(void* p); // 0x00ac03d0
extern "C" void __fastcall ctor_cCombatant(void* p);         // 0x00bfd4e0
extern "C" void __fastcall ctor_cGonzagoTimer(void* p);      // 0x00b63890
extern "C" void __fastcall dtor_cBuilding(void* p);          // 0x00bd0dd0
void  DestroyRange(void* pFirst, void* pLast);               // 0x00bd17e0
void  FreeObj(void* p);                                      // 0x00f47380 operator delete
float GetPropertyFloat(u32 id, int a, void* b, float fDef);  // 0x00bcea30
void  Fn_00bcebc0(void);                                     // 0x00bcebc0
void  __fastcall Fn_00bd0000(void* pThis, void* pEdx);                 // 0x00bd0000
void  Fn_00c3f2d0(void* pThis);                                        // 0x00c3f2d0
void  __fastcall Fn_00c421b0(void* pThis, void* pEdx, void* pArg);     // 0x00c421b0
void* __fastcall Fn_00bebe10(void* pThis, void* pEdx);                 // 0x00bebe10
void  __fastcall Fn_00bd15a0(void* pThis, void* pEdx, int n);          // 0x00bd15a0
void* StarManager();                                                   // 0x00b3d2a0
void* GetCurrentGameMode();                                            // 0x00b5b800
void* BehaviorManager();                                               // 0x00b3d260
void* NounManager();                                                   // 0x00b3d300

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// ----------------------------------------------------------------------------
// cGonzagoTimer: 0x20-byte POD, constructed by ctor_cGonzagoTimer.
struct cGonzagoTimer {
    u32 mData[8];
};

// eastl::basic_string<wchar_t> (16 bytes).
struct cWString {
    wchar_t* mpBegin;    // +0x00
    wchar_t* mpEnd;      // +0x04
    wchar_t* mpCapacity; // +0x08
    void*    mpPool;     // +0x0c
    cWString& assign(const wchar_t* pFirst, const wchar_t* pLast);  // 0x00423650
};

// eastl::basic_string<char> (16 bytes).
struct cStr8 {
    char* mpBegin;       // +0x00
    char* mpEnd;         // +0x04
    char* mpCapacity;    // +0x08
    void* mpPool;        // +0x0c
    cStr8* append_sprintf(const char* pFmt, ...);   // 0x005f9450
};

// rw::math::fpu::Matrix33 (nine floats).
struct cSPMatrix3 {
    float m[9];
    void Assign(const float* pSrc);     // 0x0041cb40
};

// The growable 4-byte array kept inside cBuilding at +0x1f8 (11 dwords, 0x2c bytes).
struct cCoordArray {
    u32  mInline[6];     // +0x00 .. +0x17
    u32* mpCurrent;      // +0x18
    u32* mpUnused1c;     // +0x1c
    u32* mpCapacity;     // +0x20
    u32* mpUnused24;     // +0x24
    u32* mpUnused28;     // +0x28
    void Init(u32 nCapacity);   // 0x004ab350
    void Grow(u32* pValue);     // 0x00502dd0
};

// The 3-pointer coordinate vector embedded at +0x344 (scenario buildings).
struct cCoordVec {
    u32* mpBegin;        // +0x00
    u32* mpEnd;          // +0x04
    u32* mpCap;          // +0x08
    void DestroyRange(u32* pFirst, u32* pLast);   // 0x00bd17e0 (thiscall)
};

// Typed ABI views of the four non-primary base subobjects, so their vtable pointer
// and (for the spatial object) SetLocalExtents can be addressed without casts.
struct cSpatialObjectABI {
    void* mpVtbl;                                             // +0x00
    void SetLocalExtents(const AABB& bounds, float fScale);   // 0x00c89160
};
struct cInteractionABI { void* mpVtbl; };
struct cCombatABI      { void* mpVtbl; };
struct cPlaceABI       { void* mpVtbl; };

// ----------------------------------------------------------------------------
// cBuilding: one flat layout covering all six base subobjects and the tail.
struct cBuilding {
    void* mpVtbl0;           // +0x000  cBuilding vtable
    void* mpVtbl1;           // +0x004  cBuilding vtable (DefaultRefCounted half)
    char  mData08[0x34 - 0x08];      // +0x008 .. +0x033 (cGameData tail)
    union { void* mpVtblSpatial; cSpatialObjectABI mSpatial; };  // +0x034
    char  mData38[0x88 - 0x38];      // +0x038 .. +0x087
    u32   mField88;          // +0x088
    char  mData8c[0xa4 - 0x8c];      // +0x08c .. +0x0a3
    u8    mbFlagA4;          // +0x0a4
    u8    mbFlagA5;          // +0x0a5
    char  mDataA6[0xda - 0xa6];      // +0x0a6 .. +0x0d9
    u8    mbFlagDa;          // +0x0da
    char  mDataDb[0x108 - 0xdb];     // +0x0db .. +0x107
    union { void* mpVtblInteraction; cInteractionABI mInteraction; };  // +0x108
    char  mData10c[0x120 - 0x10c];   // +0x10c .. +0x11f
    union { void* mpVtblCombatant; cCombatABI mCombatant; };       // +0x120
    char  mData124[0x14c - 0x124];   // +0x124 .. +0x14b
    float mField14c;         // +0x14c
    char  mData150[0x158 - 0x150];   // +0x150 .. +0x157
    float mField158;         // +0x158
    char  mData15c[0x1e8 - 0x15c];   // +0x15c .. +0x1e7
    union { void* mpVtblPlaceable; cPlaceABI mPlace; };             // +0x1e8
    u32   mF1ec;             // +0x1ec
    u32   mF1f0;             // +0x1f0
    u8    mF1f4;             // +0x1f4
    char  mF1f5[3];          // +0x1f5 .. +0x1f7
    cCoordArray mCoords;     // +0x1f8
    u32   mF224;             // +0x224
    u32   mF228;             // +0x228
    u32   mF22c;             // +0x22c
    u8    mF230;             // +0x230
    char  mF231[0x238 - 0x231];      // +0x231 .. +0x237
    cGonzagoTimer mTimer1;   // +0x238
    cGonzagoTimer mTimer2;   // +0x258
    cWString mName;          // +0x278
    u8    mF288;             // +0x288
    u8    mF289;             // +0x289
    char  mF28a[2];          // +0x28a .. +0x28b
    u32   mF28c;             // +0x28c
    u32   mF290;             // +0x290
    u32   mF294;             // +0x294
    u32   mF298;             // +0x298
    u32   mF29c;             // +0x29c
    u32   mF2a0;             // +0x2a0
    u32   mF2a4;             // +0x2a4
    u32   mF2a8;             // +0x2a8
    char  mF2ac[8];          // +0x2ac .. +0x2b3 (untouched subobject)
    u32   mF2b4;             // +0x2b4
    u32   mF2b8;             // +0x2b8
    u32   mF2bc;             // +0x2bc
    char  mF2c0[8];          // +0x2c0 .. +0x2c7 (untouched subobject)
    u32   mF2c8;             // +0x2c8
    u32   mF2cc;             // +0x2cc
    u32   mF2d0;             // +0x2d0
    char  mF2d4[8];          // +0x2d4 .. +0x2db (untouched subobject)
    u32   mF2dc;             // +0x2dc
    u32   mF2e0;             // +0x2e0
    u32   mF2e4;             // +0x2e4
    char  mF2e8[8];          // +0x2e8 .. +0x2ef (untouched subobject)
    u8    mF2f0;             // +0x2f0
    char  mF2f1[3];          // +0x2f1 .. +0x2f3
    u32   mF2f4;             // +0x2f4
    u32   mF2f8;             // +0x2f8
    u32   mF2fc;             // +0x2fc
    char  mF300[8];          // +0x300 .. +0x307 (untouched subobject)
    u32   mF308;             // +0x308
    u32   mF30c;             // +0x30c
    u32   mF310;             // +0x310
    char  mF314[0x320 - 0x314];      // +0x314 .. +0x31f
    cGonzagoTimer mTimer3;   // +0x320
    u8    mF340;             // +0x340 (CityHall: mbMoneyAddedThisTick)
    u8    mF341;             // +0x341 (CityHall: field_341)
    char  mF342[2];          // +0x342 .. +0x343
    cCoordVec mTailVec;      // +0x344 (Scenario coord vector / CityHall hit-sphere ptr)
    char  mF350[0x358 - 0x350];      // +0x350 .. +0x357
    cGonzagoTimer mTimerHit; // +0x358 (CityHall)
    char  mF378[0x388 - 0x378];      // +0x378 .. +0x387
    u16   mF388;             // +0x388 (Scenario: mnFlags)
    u16   mF38a;             // +0x38a (Scenario: mnTransformCount)
    float mF38c;             // +0x38c (Scenario: mOffset.x)
    float mF390;             // +0x390 (Scenario: mOffset.y)
    float mF394;             // +0x394 (Scenario: mOffset.z)
    float mF398;             // +0x398 (Scenario: mfScale)
    cSPMatrix3 mMatrix;      // +0x39c (Scenario: mRotation)

    cBuilding();                        // 0x00bd1820
    void PushCoord(u32 value);          // 0x00bd1ab0
};

// Derived building classes reuse the flat cBuilding layout; their constructors just
// re-point the six vptr slots to the derived class's vtables.
struct cBuildingCityHall : cBuilding {
    cBuildingCityHall();
};
struct cBuildingIndustry : cBuilding {
    cBuildingIndustry();
    void* Delete(u8 flags);             // 0x00bd1bb0 (scalar deleting destructor)
};
struct cBuildingHouse : cBuilding {
    cBuildingHouse();
};
struct cBuildingEntertainment : cBuilding {
    cBuildingEntertainment();
    void* Delete(u8 flags);             // 0x00bd1c80 (scalar deleting destructor)
};
struct cBuildingScenario : cBuilding {
    cBuildingScenario();
};

// ----------------------------------------------------------------------------
// @ 0x00bd1820
// Simulator::cBuilding::cBuilding
cBuilding::cBuilding()
{
    ctor_cGameData(this);

    cSpatialObjectABI* pSpatial = &mSpatial;
    ctor_cSpatialObject(pSpatial);
    cInteractionABI* pInteraction = &mInteraction;
    ctor_cInteractionTarget(pInteraction);
    cCombatABI* pCombatant = &mCombatant;
    ctor_cCombatant(pCombatant);

    // Interim cPlaceableStructure-half vptr, then the full base vptr set.
    mpVtblPlaceable = (void*)&cPlaceableStructure_baseVtable;
    pCombatant->mpVtbl = (void*)&cBuilding_vtable4;
    mpVtbl0 = (void*)&cBuilding_vtable0;
    mpVtbl1 = (void*)&cBuilding_vtable1;
    pSpatial->mpVtbl = (void*)&cBuilding_vtable2;
    pInteraction->mpVtbl = (void*)&cBuilding_vtable3;
    mpVtblPlaceable = (void*)&cBuilding_vtable5;

    mF1ec = 0;
    mF1f0 = 0;
    mF1f4 = 1;

    // Zero the inline coordinate-array header, then initialise it with capacity 0.
    cCoordArray* pCoords = &mCoords;
    pCoords->mInline[0] = 0;
    pCoords->mInline[1] = 0;
    pCoords->mInline[2] = 0;
    pCoords->mInline[3] = 0;
    pCoords->mInline[4] = 0;
    pCoords->mInline[5] = 0;
    pCoords->mpCurrent = 0;
    pCoords->mpUnused1c = 0;
    pCoords->mpCapacity = 0;
    pCoords->mpUnused24 = 0;
    pCoords->Init(0);

    mF224 = 0;
    mF228 = 0;
    mF22c = 0;
    mF230 = 0;
    ctor_cGonzagoTimer(&mTimer1);
    ctor_cGonzagoTimer(&mTimer2);

    mName.mpBegin = gEmptyString16;
    mName.mpEnd = gEmptyString16;
    mName.mpCapacity = gEmptyString16 + 1;
    mF288 = 1;
    mF289 = 1;
    mF28c = 0;
    mF290 = 0;
    mF294 = 0;
    mF298 = 0;
    mF29c = 0;
    mF2a0 = 0;
    mF2a4 = 0;
    mF2a8 = 0;
    mF2b4 = 0;
    mF2b8 = 0;
    mF2bc = 0;
    mF2c8 = 0;
    mF2cc = 0;
    mF2d0 = 0;
    mF2dc = 0;
    mF2e0 = 0;
    mF2e4 = 0;
    mF2f0 = 0;
    mF2f4 = 0;
    mF2f8 = 0;
    mF2fc = 0;
    mF308 = 0;
    mF30c = 0;
    mF310 = 0;
    ctor_cGonzagoTimer(&mTimer3);

    mField88 = 7;
    mbFlagA5 = 1;

    AABB bounds;
    bounds.minx = gExtentMin;
    bounds.miny = gExtentMin;
    bounds.minz = gExtentMin;
    bounds.maxx = gExtentMax;
    bounds.maxy = gExtentMax;
    bounds.maxz = gExtentMax;
    pSpatial->SetLocalExtents(bounds, 1.0f);

    mbFlagA4 = 0;
    float fProp = GetPropertyFloat(0xa4c2f6bd, 0, (void*)0x17efa840, gPropDefault);
    mField14c = fProp;
    mField158 = fProp;

    u32 nLen = 0;
    while (gBuildingName[nLen] != 0)
        ++nLen;
    mName.assign(gBuildingName, gBuildingName + nLen);
    Fn_00bcebc0();
}

// ----------------------------------------------------------------------------
// @ 0x00bd1ab0
// Push one coordinate value into the mCoords array.
void cBuilding::PushCoord(u32 value)
{
    u32* pCur = mCoords.mpCurrent;
    cCoordArray* pCoords = &mCoords;
    u32* pNew = pCur + 1;
    if (pNew != pCoords->mpCapacity) {
        pCoords->mpCurrent = pNew;
        if (pCur != 0)
            *pCur = value;
    } else {
        pCoords->Grow(&value);
    }
}

// ----------------------------------------------------------------------------
// @ 0x00bd1af0
// Simulator::cBuildingCityHall::cBuildingCityHall
cBuildingCityHall::cBuildingCityHall()
{
    mpVtbl0 = (void*)&cBuildingCityHall_vtable0;
    mpVtbl1 = (void*)&cBuildingCityHall_vtable1;
    mpVtblSpatial = (void*)&cBuildingCityHall_vtable2;
    mpVtblInteraction = (void*)&cBuildingCityHall_vtable3;
    mpVtblCombatant = (void*)&cBuildingCityHall_vtable4;
    mpVtblPlaceable = (void*)&cBuildingCityHall_vtable5;
    mF340 = 0;
    mF341 = 1;
    _ReadWriteBarrier();
    cGonzagoTimer* pTimer = &mTimerHit;
    mTailVec.mpBegin = 0;
    ctor_cGonzagoTimer(pTimer);
}

// ----------------------------------------------------------------------------
// @ 0x00bd1b70
// Simulator::cBuildingIndustry::cBuildingIndustry
cBuildingIndustry::cBuildingIndustry()
{
    mpVtbl0 = (void*)&cBuildingIndustry_vtable0;
    mpVtbl1 = (void*)&cBuildingIndustry_vtable1;
    mpVtblSpatial = (void*)&cBuildingIndustry_vtable2;
    mpVtblInteraction = (void*)&cBuildingIndustry_vtable3;
    mpVtblCombatant = (void*)&cBuildingIndustry_vtable4;
    mpVtblPlaceable = (void*)&cBuildingIndustry_vtable5;
}

// ----------------------------------------------------------------------------
// @ 0x00bd1c00
// Simulator::cBuildingHouse::cBuildingHouse
cBuildingHouse::cBuildingHouse()
{
    mpVtbl0 = (void*)&cBuildingHouse_vtable0;
    mpVtbl1 = (void*)&cBuildingHouse_vtable1;
    mpVtblSpatial = (void*)&cBuildingHouse_vtable2;
    mpVtblInteraction = (void*)&cBuildingHouse_vtable3;
    mpVtblCombatant = (void*)&cBuildingHouse_vtable4;
    mpVtblPlaceable = (void*)&cBuildingHouse_vtable5;
}

// ----------------------------------------------------------------------------
// @ 0x00bd1c40
// Simulator::cBuildingEntertainment::cBuildingEntertainment
cBuildingEntertainment::cBuildingEntertainment()
{
    mpVtbl0 = (void*)&cBuildingEntertainment_vtable0;
    mpVtbl1 = (void*)&cBuildingEntertainment_vtable1;
    mpVtblSpatial = (void*)&cBuildingEntertainment_vtable2;
    mpVtblInteraction = (void*)&cBuildingEntertainment_vtable3;
    mpVtblCombatant = (void*)&cBuildingEntertainment_vtable4;
    mpVtblPlaceable = (void*)&cBuildingEntertainment_vtable5;
}

// ----------------------------------------------------------------------------
// @ 0x00bd1bb0
// Simulator::cBuildingIndustry scalar deleting destructor.
void* cBuildingIndustry::Delete(u8 flags)
{
    mpVtbl0 = (void*)&cBuildingIndustry_vtable0;
    mpVtbl1 = (void*)&cBuildingIndustry_vtable1;
    mpVtblSpatial = (void*)&cBuildingIndustry_vtable2;
    mpVtblInteraction = (void*)&cBuildingIndustry_vtable3;
    mpVtblCombatant = (void*)&cBuildingIndustry_vtable4;
    mpVtblPlaceable = (void*)&cBuildingIndustry_vtable5;
    dtor_cBuilding(this);
    if ((flags & 1) != 0)
        FreeObj(this);
    return this;
}

// ----------------------------------------------------------------------------
// @ 0x00bd1c80
// Simulator::cBuildingEntertainment scalar deleting destructor.
void* cBuildingEntertainment::Delete(u8 flags)
{
    mpVtbl0 = (void*)&cBuildingEntertainment_vtable0;
    mpVtbl1 = (void*)&cBuildingEntertainment_vtable1;
    mpVtblSpatial = (void*)&cBuildingEntertainment_vtable2;
    mpVtblInteraction = (void*)&cBuildingEntertainment_vtable3;
    mpVtblCombatant = (void*)&cBuildingEntertainment_vtable4;
    mpVtblPlaceable = (void*)&cBuildingEntertainment_vtable5;
    dtor_cBuilding(this);
    if ((flags & 1) != 0)
        FreeObj(this);
    return this;
}

// ----------------------------------------------------------------------------
// @ 0x00bd2600
// Simulator::cBuildingScenario::cBuildingScenario
cBuildingScenario::cBuildingScenario()
{
    mpVtbl0 = (void*)&cBuildingScenario_vtable0;
    mpVtbl1 = (void*)&cBuildingScenario_vtable1;
    mpVtblSpatial = (void*)&cBuildingScenario_vtable2;
    mpVtblInteraction = (void*)&cBuildingScenario_vtable3;
    mpVtblCombatant = (void*)&cBuildingScenario_vtable4;
    mpVtblPlaceable = (void*)&cBuildingScenario_vtable5;

    _ReadWriteBarrier();
    u32 zero = 0;
    mTailVec.mpBegin = (u32*)zero;
    mTailVec.mpEnd = (u32*)zero;
    mTailVec.mpCap = (u32*)zero;
    mF388 = (u16)zero;
    mF38a = (u16)zero;
    mF38c = gVec3Zero[0];
    mF390 = gVec3Zero[1];
    mF394 = gVec3Zero[2];
    mF398 = gRealOne;
    mMatrix.Assign(gScenarioRotation);
    mbFlagA4 = 1;
}

// ----------------------------------------------------------------------------
// @ 0x00bd27d0
// cBuildingScenario destructor body: stores the six scenario vptrs, destroys the
// scenario coordinate vector, then tail-calls the shared cBuilding destructor.
void __fastcall Fn_00bd27d0(cBuilding* pThis)
{
    cCoordVec* pVec = &pThis->mTailVec;
    pThis->mpVtbl0 = (void*)&cBuildingScenario_vtable0;
    pThis->mpVtbl1 = (void*)&cBuildingScenario_vtable1;
    pThis->mpVtblSpatial = (void*)&cBuildingScenario_vtable2;
    pThis->mpVtblInteraction = (void*)&cBuildingScenario_vtable3;
    pThis->mpVtblCombatant = (void*)&cBuildingScenario_vtable4;
    pThis->mpVtblPlaceable = (void*)&cBuildingScenario_vtable5;

    pVec->DestroyRange(pVec->mpBegin, pVec->mpEnd);
    u32* pBegin = pVec->mpBegin;
    if (pBegin != 0 && pBegin[-1] != 0)
        FreeObj(pBegin);
    dtor_cBuilding(pThis);
}

// ============================================================================
// Shared ABI shims for the three non-cBuilding functions in this slice.
// ============================================================================
struct cVec3f  { float x, y, z; };
struct cQuat4f { float x, y, z, w; };
struct cMat33f { float m[9]; };

extern "C" cVec3f* normalized_safe(cVec3f* pOut, const cVec3f* pIn);      // 0x00449c20
extern "C" void    Fn_00576b00(cMat33f* pOut, const cVec3f* pAxis, float fAngle); // 0x00576b00
extern "C" double  _CIacos(double fValue);
extern "C" char    Fn_0059ab10(float fValue);                             // 0x0059ab10
extern "C" void    Fn_005b26f0(cQuat4f* pOut, const cQuat4f* pA,
                               const cQuat4f* pB, float fT);              // 0x005b26f0
extern "C" cQuat4f* QuaternionFromFacingAndUp(cQuat4f* pOut,
                                               const cVec3f* pFacing,
                                               const cVec3f* pUp);        // 0x0069b600
extern "C" char    Fn_00bfc600(void* pThis, void* pEdx);                  // 0x00bfc600
extern "C" int     GetDamageState(void* pThis, void* pEdx);               // 0x008e7f80

extern float gAimTurnStep;   // 0x0156d708
extern float gAimTurnMax;    // 0x0156d70c
extern u32   gBehaviorId;    // 0x0169ebbc
extern float gEffectSize;    // 0x0147b9f0
extern char  gAppTag[];      // 0x01654c05

// ---------------------------------------------------------------------------
// cAimController::Update (00bd1cd0).  The controller steers a turret toward
// the object's hostile target; the output argument receives the aim point.
// ---------------------------------------------------------------------------
struct cPosObject;
struct cRefObject;

struct cPosVtbl {
    char    mSlots00[0x2c];
    cVec3f* (__fastcall* GetPosition)(void* pSelf, void* pEdx);           // +0x2c
};
struct cPosObject { cPosVtbl* mpVtbl; };                                  // +0x00

struct cRefVtbl {
    char        mSlots00[0x08];
    cPosObject* (__fastcall* GetRef)(void* pSelf, void* pEdx);            // +0x08
};
struct cRefObject { cRefVtbl* mpVtbl; };                                  // +0x00

struct cWeaponVtbl {
    char    mSlots00[0x58];
    cVec3f* (__fastcall* GetMuzzle)(void* pSelf, void* pEdx, cVec3f* pOut); // +0x58
};
struct cWeaponObject { cWeaponVtbl* mpVtbl; };                            // +0x00

struct cTargetVtbl {
    char  mSlots00[0xb8];
    void* (__fastcall* GetByTag)(void* pSelf, void* pEdx, u32 nTag);      // +0xb8
};

struct cCombatantObjVtbl {
    char         mSlots00[0x54];
    cRefObject*  (__fastcall* GetRefObject)(void* pSelf, void* pEdx);     // +0x54
};
struct cCombatantSub { cCombatantObjVtbl* mpVtbl; };                      // +0x00

struct cAimSpatialVtbl {
    char      mSlots00[0x2c];
    cVec3f*   (__fastcall* GetPosition)(void* pSelf, void* pEdx);         // +0x2c
    cQuat4f*  (__fastcall* GetOrientation)(void* pSelf, void* pEdx);      // +0x30
    char      mSlots34[0x3c - 0x34];
    void      (__fastcall* SetOrientation)(void* pSelf, void* pEdx, cQuat4f* pQ); // +0x3c
    char      mSlots40[0x5c - 0x40];
    void      (__fastcall* GetForward)(void* pSelf, void* pEdx, cVec3f* pOut);    // +0x5c
};
struct cAimSpatialSub { cAimSpatialVtbl* mpVtbl; };                       // +0x00

struct cAimWorld {
    cTargetVtbl*    mpVtbl;          // +0x000
    char            mData04[0x34 - 0x04];
    cAimSpatialSub  mSpatial;        // +0x034
    char            mData38[0x588 - 0x38];
    cCombatantSub   mCombatant;      // +0x588
    char            mData58c[0x684 - 0x58c];
    int             mF684;           // +0x684
    cWeaponObject*  mpWeapon;        // +0x688
    char            mData68c[0x6a4 - 0x68c];
    cRefObject*     mpF6a4;          // +0x6a4
};

struct cAimUpdateArgs {
    cVec3f       mPos;        // +0x00 (output)
    char         mData0c[0x10 - 0x0c];
    float        mScale;      // +0x10
    cAimWorld*   mpTarget;    // +0x14
};

struct cAimController {
    char   mData00[0x10];
    int    mMode;       // +0x10
    int    mCounter;    // +0x14
    cVec3f mFacing;     // +0x18
    void Update(cAimUpdateArgs* pArgs);   // 0x00bd1cd0
};

// ----------------------------------------------------------------------------
// @ 0x00bd1cd0
// cAimController::Update - steer the turret toward the current hostile target.
void cAimController::Update(cAimUpdateArgs* pArgs)
{
    pArgs->mPos.x = gVec3Zero[0];
    pArgs->mPos.y = gVec3Zero[1];
    pArgs->mPos.z = gVec3Zero[2];

    cAimWorld* pWorld = pArgs->mpTarget;
    if (pWorld == 0)
        return;

    cAimWorld* pObj = (cAimWorld*)pWorld->mpVtbl->GetByTag(pWorld, 0, 0x436f315u);
    if (pObj == 0)
        return;
    if (pObj->mF684 > 0)
        return;
    if (Fn_00bfc600(&pObj->mCombatant, 0) != 0)
        return;
    if (GetDamageState(&pObj->mCombatant, 0) == 2)
        return;

    cVec3f vForward;
    pObj->mSpatial.mpVtbl->GetForward(&pObj->mSpatial, 0, &vForward);
    cVec3f vPos = *pObj->mSpatial.mpVtbl->GetPosition(&pObj->mSpatial, 0);

    cPosObject* pTargetPos = 0;
    cRefObject* pRef = pObj->mCombatant.mpVtbl->GetRefObject(&pObj->mCombatant, 0);
    if (pRef != 0)
        pTargetPos = pRef->mpVtbl->GetRef(pRef, 0);

    cPosObject* pOtherPos = 0;
    if (pObj->mpF6a4 != 0)
        pOtherPos = pObj->mpF6a4->mpVtbl->GetRef(pObj->mpF6a4, 0);

    if (pTargetPos != 0 || pOtherPos != 0)
    {
        cPosObject* pChosen = (pTargetPos != 0) ? pTargetPos : pOtherPos;
        cVec3f vTarget = *pChosen->mpVtbl->GetPosition(pChosen, 0);
        cVec3f vDelta;
        vDelta.x = vTarget.x - vPos.x;
        vDelta.y = vTarget.y - vPos.y;
        vDelta.z = vTarget.z - vPos.z;
        cVec3f* pNorm = normalized_safe(&mFacing, &vDelta);
        mFacing = *pNorm;
        mMode = 1;
    }
    else
    {
        float fDot = mFacing.x * vForward.x +
                     mFacing.y * vForward.y +
                     mFacing.z * vForward.z;
        if (mMode != 1 && fDot <= 0.96f)
            goto build_quaternion;

        ++mCounter;
        mMode = 0;

        cVec3f vPositionDir;
        normalized_safe(&vPositionDir, &vPos);

        cVec3f vMuzzleOut;
        cVec3f* pMuzzle = pObj->mpWeapon->mpVtbl->GetMuzzle(pObj->mpWeapon, 0, &vMuzzleOut);
        cVec3f vToMuzzle;
        vToMuzzle.x = vPos.x - pMuzzle->x;
        vToMuzzle.y = vPos.y - pMuzzle->y;
        vToMuzzle.z = vPos.z - pMuzzle->z;

        cVec3f vToMuzzleDir;
        cVec3f* pToMuzzle = normalized_safe(&vToMuzzleDir, &vToMuzzle);

        float fAlong = vPositionDir.x * pToMuzzle->x +
                       vPositionDir.y * pToMuzzle->y +
                       vPositionDir.z * pToMuzzle->z;
        cVec3f vTangent;
        vTangent.x = pToMuzzle->x - vPositionDir.x * fAlong;
        vTangent.y = pToMuzzle->y - vPositionDir.y * fAlong;
        vTangent.z = pToMuzzle->z - vPositionDir.z * fAlong;
        cVec3f vTangentDir = *normalized_safe(&vTangent, &vTangent);

        float fRoll = 0.0f;
        if ((mCounter & 1) == 0)
            fRoll = ((mCounter & 3) == 0) ? gAimTurnStep : -gAimTurnStep;

        cMat33f matRot;
        Fn_00576b00(&matRot, &vPositionDir, fRoll);

        cVec3f vRotated;
        vRotated.x = matRot.m[3] * vTangentDir.y + matRot.m[6] * vTangentDir.z + matRot.m[0] * vTangentDir.x;
        vRotated.y = matRot.m[4] * vTangentDir.y + matRot.m[7] * vTangentDir.z + matRot.m[1] * vTangentDir.x;
        vRotated.z = matRot.m[5] * vTangentDir.y + matRot.m[8] * vTangentDir.z + matRot.m[2] * vTangentDir.x;

        if ((mCounter % 5) == 0)
        {
            cVec3f vOffset;
            if ((mCounter & 1) == 0)
            {
                vOffset.x = vRotated.x - vPositionDir.x * 0.6666667f;
                vOffset.y = vRotated.y - vPositionDir.y * 0.6666667f;
                vOffset.z = vRotated.z - vPositionDir.z * 0.6666667f;
            }
            else
            {
                vOffset.x = vPositionDir.x * 0.6666667f + vRotated.x;
                vOffset.y = vPositionDir.y * 0.6666667f + vRotated.y;
                vOffset.z = vPositionDir.z * 0.6666667f + vRotated.z;
            }
            vRotated = *normalized_safe(&vOffset, &vOffset);
        }

        mFacing = vRotated;
    }

build_quaternion:
    {
        cVec3f vUp;
        normalized_safe(&vUp, &vPos);
        cQuat4f qFacing;
        QuaternionFromFacingAndUp(&qFacing, &mFacing, &vUp);

        cQuat4f qOrient = *pObj->mSpatial.mpVtbl->GetOrientation(&pObj->mSpatial, 0);

        float fCos = mFacing.x * qOrient.x +
                     mFacing.y * qOrient.y +
                     mFacing.z * qOrient.z;
        if (fCos > 1.0f)
            fCos = 1.0f;
        if (fCos < 0.0f)
            fCos = 0.0f;

        float fAngle = (float)_CIacos(fCos);
        if (Fn_0059ab10(fAngle) != 0)
        {
            float fT = gAimTurnMax;
            if (mMode == 0)
                fT = gAimTurnStep * 0.666f;
            if (fAngle <= 0.0f)
            {
                fT = 1.0f;
            }
            else
            {
                fT = (pArgs->mScale * fT) / fAngle;
                if (fT >= 1.0f)
                    fT = 1.0f;
            }
            cQuat4f qBlended;
            Fn_005b26f0(&qBlended, &qOrient, &qFacing, fT);
            pObj->mSpatial.mpVtbl->SetOrientation(&pObj->mSpatial, 0, &qBlended);
        }
    }
}

// ---------------------------------------------------------------------------
// cSPCreatureCitizen::Init (00bd2310).
// ---------------------------------------------------------------------------
struct cCitizenData;
struct cListNode;
struct cNoun;

struct cCitizenDataVtbl {
    void (__fastcall* AddRef)(void* pSelf, void* pEdx);                   // +0x00
    void (__fastcall* Release)(void* pSelf, void* pEdx);                  // +0x04
    char mSlots08[0x4c - 0x08];
    u32  (__fastcall* GetEmpireId)(void* pSelf, void* pEdx);              // +0x4c
    char mSlots50[0x6c - 0x50];
    cCitizenData* (__fastcall* GetOwner)(void* pSelf, void* pEdx);        // +0x6c
};
struct cCitizenData {
    cCitizenDataVtbl* mpVtbl;      // +0x000
    char              mData04[0x1f4 - 0x04];
    u8                mF1f4;       // +0x1f4
};

struct cListNodeVtbl {
    char mSlots00[0x04];
    void (__fastcall* Release)(void* pSelf, void* pEdx);                  // +0x04
    void (__fastcall* Fn08)(void* pSelf, void* pEdx);                     // +0x08
};
struct cListNode { cListNodeVtbl* mpVtbl; };                              // +0x00

struct cCitizenSpatialVtbl {
    char mSlots00[0x2c];
    int  (__fastcall* Fn2c)(void* pSelf, void* pEdx, float fArg);         // +0x2c
    char mSlots30[0x94 - 0x30];
    void (__fastcall* Fn94)(void* pSelf, void* pEdx, void* pArg);         // +0x94
};

struct cBehaviorListVtbl {
    char mSlots00[0x0c];
    void (__fastcall* Fn0c)(void* pSelf, void* pEdx, u32 a, void* b, int c); // +0x0c
};
struct cBehaviorList { cBehaviorListVtbl* mpVtbl; };                       // +0x00

struct cBehaviorMgrVtbl {
    char mSlots00[0x38];
    void (__fastcall* Fn38)(void* pSelf, void* pEdx, void* pArg);         // +0x38
};
struct cBehaviorMgr { cBehaviorMgrVtbl* mpVtbl; };                         // +0x00

struct cNounVtbl {
    char mSlots00[0x0c];
    cCitizenData* (__fastcall* CreateRef)(void* pSelf, void* pEdx, u32 nId); // +0x0c
};
struct cNoun { cNounVtbl* mpVtbl; };                                       // +0x00

extern char cTurretVtableVtbl8[];   // 0x013ec458 (interim vptr at +0x08)
extern char cTurretVtable000[];     // 0x01466c50
extern char cTurretVtable008[];     // 0x01475114 (final vptr at +0x08)
extern "C" void __fastcall SetGameDataOwner2(void* pThis, void* pEdx, void* pArg); // 0x00b18550
extern "C" void* __fastcall GetEmpireByID(void* pThis, void* pEdx, u32 nId);        // 0x00ba9370
extern "C" int  __fastcall GetWeaponryLevel(void* pThis, void* pEdx);               // 0x00c317a0
extern "C" void* __fastcall CreateNoun(void* pThis, void* pEdx, u32 nId);           // 0x00b20c60
extern "C" void __fastcall SetEffectId(void* pThis, void* pEdx, int nId);           // 0x00c3f160
extern "C" void* NewObj(u32 nSize, const char* pName, int a, int b, int c, int d);  // 0x00f473a0

struct cTurretRotator {
    void*  mpVtbl0;    // +0x00
    void*  mpVtbl1;    // +0x04
    void*  mpVtbl2;    // +0x08
    void*  mpVtbl3;    // +0x0c
    u32    mF10;       // +0x10
    u32    mF14;       // +0x14
    cVec3f mF18;       // +0x18
};

struct cSPCreatureCitizen {
    char                  mData00[0x34];
    cCitizenSpatialVtbl*  mpVtblSpatial;   // +0x034
    char                  mData38[0xa5 - 0x38];
    u8                    mbFlagA5;        // +0x0a5
    char                  mDataA6[0xda - 0xa6];
    u8                    mbFlagDa;        // +0x0da
    char                  mDataDb[0x224 - 0xdb];
    u32                   mF224;           // +0x224
    char                  mData228[0x51c - 0x228];
    cBehaviorList         mBehaviorList;   // +0x51c
    char                  mData520[0x654 - 0x520];
    cVec3f                mF654;           // +0x654
    char                  mData660[0x688 - 0x660];
    cCitizenData*         mpF688;          // +0x688
    cListNode*            mpF68c;          // +0x68c
    cListNode*            mpF690;          // +0x690
    char                  mData694[0x6a0 - 0x694];
    cCitizenData*         mpF6a0;          // +0x6a0
    void Init(cCitizenData* pArg);         // 0x00bd2310
};

// ----------------------------------------------------------------------------
// @ 0x00bd2310
// cSPCreatureCitizen::Init - bind the citizen's game data / owner and build the
// turret rotator locomotion and noun reference.
void cSPCreatureCitizen::Init(cCitizenData* pArg)
{
    mF654.x = gVec3Zero[0];
    mF654.y = gVec3Zero[1];
    mF654.z = gVec3Zero[2];
    mbFlagDa = 0;
    mbFlagA5 = 1;

    SetGameDataOwner2(this, 0, pArg);

    {
        cCitizenData* pOld = mpF688;
        if (pArg != pOld)
        {
            if (pArg != 0)
                pArg->mpVtbl->AddRef(pArg, 0);
            mpF688 = pArg;
            if (pOld != 0)
                pOld->mpVtbl->Release(pOld, 0);
        }
    }

    {
        void* pOwnerRaw = pArg->mpVtbl->GetOwner(pArg, 0);
        void* pOwner = Fn_00bebe10(pOwnerRaw, 0);
        mpVtblSpatial->Fn94(&mpVtblSpatial, 0, pOwner);
    }

    Fn_00bd0000(this, 0);

    {
        cListNode* pNew = mpF690;
        cListNode* pOld = mpF68c;
        if (pNew != pOld)
        {
            if (pNew != 0)
                pNew->mpVtbl->Release(pNew, 0);
            mpF68c = pNew;
            if (pOld != 0)
                pOld->mpVtbl->Fn08(pOld, 0);
        }
    }

    void* pGameMode = GetCurrentGameMode();
    int nLevel = 0;
    if (pGameMode == (void*)gAppTag)
    {
        u32 nEmpireId = pArg->mpVtbl->GetEmpireId(pArg, 0);
        void* pStarManager = StarManager();
        void* pEmpire = GetEmpireByID(pStarManager, 0, nEmpireId);
        if (pEmpire != 0)
            nLevel = GetWeaponryLevel(pEmpire, 0);
    }
    Fn_00bd15a0(this, 0, nLevel);

    cBehaviorMgr* pBehaviorMgr = (cBehaviorMgr*)BehaviorManager();
    pBehaviorMgr->mpVtbl->Fn38(pBehaviorMgr, 0, &mBehaviorList);

    if (pGameMode == (void*)gAppTag)
    {
        void* pEffectArg = (mpF688 != 0) ? (void*)&mpF688->mF1f4 : 0;
        mBehaviorList.mpVtbl->Fn0c(&mBehaviorList, 0, gBehaviorId, pEffectArg, 0);
    }

    mF224 = 5;

    {
        cTurretRotator* pRotator =
            (cTurretRotator*)NewObj(0x24, "Simulator/cTurretRotatorLocomotion", 0, 0, 0, 0);
        if (pRotator != 0)
        {
            pRotator->mpVtbl2 = (void*)&cTurretVtableVtbl8;
            pRotator->mpVtbl3 = 0;
            pRotator->mpVtbl0 = (void*)&cTurretVtable000;
            pRotator->mpVtbl2 = (void*)&cTurretVtable008;
            pRotator->mF10 = 1;
            pRotator->mF14 = 0;
            pRotator->mF18.x = gVec3Zero[0];
            pRotator->mF18.y = gVec3Zero[1];
            pRotator->mF18.z = gVec3Zero[2];
        }
        Fn_00c421b0(&mpVtblSpatial, 0, pRotator);
    }

    {
        void* pNounMgr = NounManager();
        cCitizenData* pRef = 0;
        cNoun* pNoun = (cNoun*)CreateNoun(pNounMgr, 0, 0x2e72caeu);
        if (pNoun != 0)
            pRef = pNoun->mpVtbl->CreateRef(pNoun, 0, 0x2e71a5au);

        cCitizenData* pOld = mpF6a0;
        if (pRef != pOld)
        {
            if (pRef != 0)
                pRef->mpVtbl->AddRef(pRef, 0);
            mpF6a0 = pRef;
            if (pOld != 0)
                pOld->mpVtbl->Release(pOld, 0);
        }
    }

    if (mpF6a0 != 0)
    {
        Fn_00c3f2d0(this);
        int nEffect = mpVtblSpatial->Fn2c(&mpVtblSpatial, 0, gEffectSize);
        SetEffectId(mpF6a0, 0, nEffect);
    }
}

// ---------------------------------------------------------------------------
// 00bd2560 - format the CityFlatten output pairs into a string.
// ---------------------------------------------------------------------------
struct cPair { int x, y; };

struct cPairVec {
    cPair* mpBegin;    // +0x00
    cPair* mpEnd;      // +0x04
    cPair* mpCap;      // +0x08
};

struct cCityFlattenVtbl {
    char mSlots00[0x84];
    void* (__fastcall* FillPairs)(void* pSelf, void* pEdx, cPairVec* pVec); // +0x84
};

struct cCityFlatten {
    cCityFlattenVtbl* mpVtbl;   // +0x00
    void Flatten5a4(cPairVec* pVec);   // 0x00bdf750
};

struct cFlattenOuter {
    cCityFlatten* mpFlatten;    // +0x00
};

// ----------------------------------------------------------------------------
// @ 0x00bd2560
// Build the flatten pair list for the structure and append "\n<key>: <value>"
// for every entry to the supplied string.
void __fastcall Fn_00bd2560(cFlattenOuter* pOuter, void* pEdx, cStr8* pStr)
{
    cPair buffer[64];
    cPairVec vec;
    vec.mpBegin = buffer;
    vec.mpEnd = buffer;
    vec.mpCap = buffer + 64;
    buffer[0].x = 0;

    cCityFlatten* pFlatten =
        (cCityFlatten*)pOuter->mpFlatten->mpVtbl->FillPairs(pOuter->mpFlatten, 0, &vec);
    pFlatten->Flatten5a4(&vec);

    int nCount = (int)(vec.mpEnd - vec.mpBegin);
    for (int i = 0; i < nCount; ++i)
        pStr->append_sprintf("\n%d: %d", vec.mpBegin[i].x, vec.mpBegin[i].y);

    cPair* pBegin = vec.mpBegin;
    if (pBegin != 0 && ((int*)pBegin)[-1] != 0)
        FreeObj(pBegin);
}
