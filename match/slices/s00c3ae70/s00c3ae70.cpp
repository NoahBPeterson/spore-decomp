// Slice s00c3ae70 - SP::cSPGameDataUFO / SP::cUFOKinestheticsTuning methods in SPGameDataUFO.obj.
//   GetScale                      0xc3ae70
//   UpdateScale                   0xc3b3f0
//   UpdateDestinationFromTarget   0xc3b4d0
//   OnMessage                     0xc3b560  (`this` is the subobject at UFO+0x5e8)
//   SetNPCTool                    0xc3b5c0
//   ClearAttackBehaviorTarget     0xc3b630
//   ClearDefenseBehaviorTarget    0xc3b700
//   cUFOKinestheticsTuning::Init  0xc3b7f0
//   GetGalaxyWarpMultiplier       0xc3b880
//   cSPGameDataUFO dtor           0xc3b9a0
//   GetFieldValues                0xc3bc80
//   GetScaleRadius                0xc3be10
//   SetHeading                    0xc3be70
//
// Retail offsets: cGameData @0, cLocomotiveObject @0x34, cCombatant @0x508,
// cInteractionTarget @0x5d0 (ModAPI header, not the 2008 PDB).
#include "types.h"
#include <math.h>

#pragma intrinsic(sqrt, fabs)

typedef unsigned int   U32;
typedef unsigned char  U8;
typedef unsigned short U16;

// ---------------------------------------------------------------- math types
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

// ---------------------------------------------------------------- refcounted object
// Object whose vtable carries AddRef at +0x4 and Release at +0x8.
struct IRefObject {
    virtual void q00();                    // +0x00
    virtual int  AddRef();                 // +0x04
    virtual int  Release();                // +0x08
};

// Object whose vtable carries Release at +0x4 (property-list owner style).
struct IReleased {
    virtual void q00();                    // +0x00
    virtual int  Release();                // +0x04
};

// ---------------------------------------------------------------- externals
extern void* g_pAllocator;                 // 0x016c8b44 (operator delete allocator)
extern const char g_sz_Simulator[];        // 0x13f09b4

void  __cdecl operator_delete(void* p);                                            // 0xf47380
void* __cdecl operator_new(U32 size, const char* pName, int a, int b, void* pAlloc, U32 line); // 0xf473a0

// ---------------------------------------------------------------- constants (data, masked as relocs)
extern float gF_1485720;   // 1.0
extern float gF_1470f1c;   // 2.0
extern float gF_13ec4b4;   // FLT_MAX
extern float gF_146bb6c;   // 0.9
extern float gF_146bb70;   // 1.5258789e-05 (min extent threshold)
extern float gF_1471064;   // 0.5

// ---------------------------------------------------------------- globals / free functions
void* __cdecl App();                        // 0x0067dd10
void* __cdecl MessageServer();              // 0x0067dcc0
void* __cdecl PropertyManager();            // 0x0067de30
void* __cdecl SpaceGameGet();               // 0x01002bd0
void* __cdecl GetTriggerMgr();              // 0x00b3d4d0
void* __cdecl GetUniverseContext();         // 0x01021080
void* __cdecl IsArchivedState();            // 0x01021240
void* __cdecl PlanetModel();                // 0x00b3d350
void* __cdecl FUN_00b3d390(void*, void*);   // 0x00b3d390 (returns [0x167eb08], ignores args)
void* __cdecl FUN_00801920(void*);          // 0x00801920 (this+0x48)
int   __cdecl FUN_00c8b520(void*);          // 0x00c8b520 (bool)
float __cdecl FUN_01017030(int);            // 0x01017030
float __cdecl FUN_01017070(int);            // 0x01017070
float __cdecl FUN_01005c60(void*, int);     // 0x01005c60

// ---------------------------------------------------------------- thiscall callee stubs
struct FnC37550 { float __thiscall f(int); };        // 0x00c37550 GetLowScale  (ret 4)
struct FnC37570 { float __thiscall f(int); };        // 0x00c37570 GetHighScale (ret 4)
struct FnC375B0 { void* __thiscall f(); };           // 0x00c375b0 interface_cast (cdecl 1 arg)
struct Fn1017BB0{ float __thiscall f(); };           // 0x01017bb0 GetReferenceHeight
struct Fn7C3D30 { void  __thiscall f(Vector3*, void*, void*, void*); };  // 0x007c3d30 GetCameraLocationInfo (ret 0x10)
struct FnB81630 { void  __thiscall f(Vector3* pOut, Vector3* pIn); };    // 0x00b81630 (ret 8)
struct FnBC3110 { void  __thiscall f(); };           // 0x00bc3110 cSPTimer::Stop
struct FnB638B0 { void  __thiscall f(); };           // 0x00b638b0 cGonzagoTimer::~cGonzagoTimer
struct FnAC0520 { void  __thiscall f(); };           // 0x00ac0520
struct FnBFCD00 { void  __thiscall f(); };           // 0x00bfcd00 cCombatant::~cCombatant
struct FnC432E0 { void  __thiscall f(); };           // 0x00c432e0
struct FnB184C0 { void  __thiscall f(); };           // 0x00b184c0 cGameData::~cGameData
struct FnBCAE90 { void  __thiscall f(); };           // 0x00bcae90 cAgentOrderManager::~cAgentOrderManager
struct FnB18E40 { bool  __thiscall f(); };           // 0x00b18e40 (bool in AL)
struct Fn104E340{ int   __thiscall f(unsigned int); };            // 0x0104e340 CreateToolFromToolID (ret 8)
struct Fn104BD50{ int   __thiscall f(); };           // 0x0104bd50 (bool)
struct Fn104FA90{ void  __thiscall f(void*); };      // 0x0104fa90 UseToolStop (ret 4)
struct FnC38B10 { void  __thiscall f(); };           // 0x00c38b10
struct FnC38B90 { void  __thiscall f(); };           // 0x00c38b90
struct FnC37DC0 { float __thiscall f(); };           // 0x00c37dc0
struct FnC382E0 { void  __thiscall f(); };           // 0x00c382e0
struct Fn1005C60{ float __thiscall f(int); };        // 0x01005c60 GetWarpScale (this=SpaceGame)
struct FnC3AD40 { float __thiscall f(); };           // 0x00c3ad40
struct FnB18420 { int   __thiscall f(void*); };      // 0x00b18420 cGameData::WriteAsText (ret 4)
struct FnC0AF90 { int   __thiscall f(void*); };      // 0x00c0af90 cLocomotiveObject::GetFieldValues
struct Fn692F90 { void  __thiscall f(void*, void*, int); };          // 0x00692f90 cVarListSerializer ctor (ret 0xc)
struct Fn695960 { int   __thiscall f(void*); };      // 0x00695960 cVarListSerializer::GetFields (ret 4)
struct Fn6A08B0 { int   __cdecl f(void*, int, int*, float**); };     // 0x006a08b0 GetPropertyAsFloatArray
int __cdecl FUN_6a08b0(void* pList, int id, int* pCount, float** pArray);  // 0x006a08b0
struct Fn571DB0 { void  __thiscall f(void*, void*, void*, void*, void*); };  // 0x00571db0 RemoveHandler

// ---------------------------------------------------------------- app / camera chain
struct cViewer { void __thiscall GetCameraLocationInfo(Vector3* out, void*, void*, void*); };  // 0x7c3d30
struct cCameraController {
    virtual void  c00(); virtual void  c01(); virtual void  c02();
    virtual void* QueryInterface(U32 id);      // +0x0c
    virtual void  c10(); virtual void  c14(); virtual void  c18(); virtual void  c1c();
    virtual void  c20(); virtual void  c24(); virtual void  c28(); virtual void  c2c();
    virtual void  c30(); virtual void  c34(); virtual void  c38(); virtual void  c3c();
    virtual void  c40(); virtual void  c44(); virtual void  c48(); virtual void  c4c();
    virtual void  c50(); virtual void  c54(); virtual void  c58();
    virtual float GetDistance();               // +0x5c
};
struct cCameraManager {
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11();
    virtual void c12(); virtual void c13();
    virtual cCameraController* GetActiveCamera();  // +0x38
    virtual cViewer* GetViewer();                  // +0x1c? no
};
// App itself: slot 0x50 = GetCameraManager
struct cAppBase {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08(); virtual void a09(); virtual void a10(); virtual void a11();
    virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
    virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
    virtual cCameraManager* GetCameraManager();   // +0x50
};

// cPlayerCameraManager exposes the viewer at slot 0x1c
struct cPlayerCameraManager : public cCameraManager {
    virtual cViewer* GetViewer();                 // +0x1c (from a Manager)
};

// ---------------------------------------------------------------- refcounted handle
struct RefHolder {
    IRefObject* mpObject;                                       // +0
    RefHolder() : mpObject(0) {}
    RefHolder& operator=(IRefObject* p)
    {
        if (mpObject != p) {
            if (p) p->AddRef();
            IRefObject* pOld = mpObject;
            mpObject = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};

// ---------------------------------------------------------------- cGonzagoTimer
struct cGonzagoTimer { U32 md[8]; };   // 0x20 bytes, 0x00bc3110 .. 0x00b638b0

// ---------------------------------------------------------------- cUFOKinestheticsTuning
// Layout from the s00c38d00 slice (dev-PDB member names; retail accessors in s01060df0
// reveal that several +0x1xx fields are the '2' (galaxy) variants / role-shifted).
struct IHandler { virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c(); virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c(); virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c(); virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c(); virtual void v040(); virtual void v044(); virtual void v048(); };

struct cUFOKinestheticsTuning : public IHandler {
    void* mpPropList;                        // +0x04
    float mHitTerrainDamage;                 // +0x08
    float mMinAltitude;                      // +0x0C
    float mMaxAltitude;                      // +0x10
    float mDamageToDestScale;                // +0x14
    float mDamageToVelocityScale;            // +0x18
    float mHitSphereRadius;                  // +0x1C
    float mHitSphereActiveDistance;          // +0x20
    float mMinExtent;                        // +0x24
    float mBomberScale;                      // +0x28
    float mFighterScale;                     // +0x2C
    float mUberTurretScale;                  // +0x30
    float mAllyScale;                        // +0x34
    float mPlumpDistance;                    // +0x38
    float mPlumpScale;                       // +0x3C
    float mPlumpTransitionScale;             // +0x40
    float mNPCPlumpScale;                    // +0x44
    float mBasePlanetScale;                  // +0x48
    float mVelocityFactor;                   // +0x4C
    float mVelocityFactorNPC;                // +0x50
    float mFighterVelocityFactor;            // +0x54
    float mUberTurretVelocityFactor;         // +0x58
    float mAllyVelocityFactor;               // +0x5C
    float mKeyboardMovementSpeedZoomedOut;   // +0x60
    float mKeyboardMovementSpeedZoomedIn;    // +0x64
    float mKeyboardAccelerationZoomedOut;    // +0x68
    float mKeyboardAccelerationZoomedIn;     // +0x6C
    float mBomberVelocityFactor;             // +0x70
    float mVelocityFactorZoomedOut;          // +0x74
    float mMouseMovementSpeedZoomedOut;      // +0x78
    float mMouseMovementSpeedZoomedIn;       // +0x7C
    float mMouseRotationSpeedZoomedOut;      // +0x80
    float mMouseRotationSpeedZoomedIn;       // +0x84
    float mLeavePlanetTimePad;               // +0x88
    float mMaxRotation;                      // +0x8C
    float mTargetFallOffRadius;              // +0x90
    float mBrakeFactor;                      // +0x94
    float mBrakeOvershootFactor;             // +0x98
    float mAccelerationFactor;               // +0x9C
    float mAccelerationFactorNPC;            // +0xA0
    float mVerticalAcclerationDown;          // +0xA4
    float mVerticalAcclerationUp;            // +0xA8
    float mCollisionElasticity;              // +0xAC
    float mCollisionRestitution;             // +0xB0
    float mRotationPercentageRate;           // +0xB4
    float mNoseTiltFactor;                   // +0xB8
    float mNoseTiltRate;                     // +0xBC
    float mMaxNoseTilt;                      // +0xC0
    float mVerticalTiltFactor;               // +0xC4
    float mMaxVerticalTilt;                  // +0xC8
    float mBankTiltFactor;                   // +0xCC
    float mBankTiltRate;                     // +0xD0
    float mMaxBankTilt;                      // +0xD4
    float mEscapeSequenceSpinRate;           // +0xD8
    float mEscapeSequenceVelocity;           // +0xDC
    float mTrailEffectAlwaysOn;              // +0xE0
    float mEffectMaxSpeedPlanet;             // +0xE4
    float mEffectMaxSpeedSolar;              // +0xE8
    float mEffectMaxSpeedGalaxy;             // +0xEC
    float mTrailEffectMinSize;               // +0xF0
    float mMaxAltitudeDestinationDelta;      // +0xF4
    float mSolarSpeed;                       // +0xF8
    float mSolarAcceleration;                // +0xFC
    float mGalaxySpeed;                      // +0x100
    float mGalaxyAcceleration;               // +0x104
    float mSolarMinPlump;                    // +0x108
    float mSolarMaxPlump;                    // +0x10C
    float mGalaxyMinPlump;                   // +0x110
    float mGalaxyMaxPlump;                   // +0x114
    float mGalaxyMinPlumpDistance;           // +0x118
    float mGalaxyMaxPlumpDistance;           // +0x11C
    float mBaseUFODamagePush;                // +0x120
    float mMaxUFODamagePush;                 // +0x124
    float mUFODamageVelocityDecayRate;       // +0x128
    float mAltMaxAltitude;                   // +0x12C
    float mAltPlumpDistance;                 // +0x130
    float mAltVelocityFactorZoomedOut;       // +0x134
    float mExtra138;                         // +0x138
    float mExtra13c;                         // +0x13C
    float mExtra140;                         // +0x140
    float mExtra144;                         // +0x144
    float mExtra148;                         // +0x148
    float mExtra14c;                         // +0x14C
    float mExtra150;                         // +0x150
    float m2HitTerrainDamage;                // +0x154
    float m2MinAltitude;                     // +0x158
    float m2MaxAltitude;                     // +0x15C
    float m2DamageToDestScale;               // +0x160
    float m2DamageToVelocityScale;           // +0x164
    float m2HitSphereRadius;                 // +0x168
    float m2HitSphereActiveDistance;         // +0x16C
    float m2MinExtent;                       // +0x170
    float m2BomberScale;                     // +0x174
    float m2FighterScale;                    // +0x178
    float m2UberTurretScale;                 // +0x17C
    float m2AllyScale;                       // +0x180
    float m2PlumpDistance;                   // +0x184
    float m2PlumpScale;                      // +0x188
    float m2PlumpTransitionScale;            // +0x18C
    float m2NPCPlumpScale;                   // +0x190
    float m2BasePlanetScale;                 // +0x194
    float m2VelocityFactor;                  // +0x198
    float m2VelocityFactorNPC;               // +0x19C
    float m2FighterVelocityFactor;           // +0x1A0
    float m2UberTurretVelocityFactor;        // +0x1A4
    U32   md1a8;                             // +0x1A8 (MessageServer*)
    U32   md1ac;                             // +0x1AC (this)
    U32   md1b0;                             // +0x1B0 (= 0x146bb64)
    U32   md1b4;                             // +0x1B4 (= 1)
    U32   md1b8;                             // +0x1B8 (= 0)

    void  ReadProps();                       // 0x00c38d00
    void  Init();
    float GetGalaxyWarpMultiplier(int index, int warpMode);
};

// ---------------------------------------------------------------- the cGameData / cSpatialObject chains
class cSpatialObject {
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual const Vector3& GetPosition();          // +0x2c
};

class cGameData {
public:
    virtual void g00(); virtual void g01(); virtual void g02(); virtual void g03();
    virtual void g04(); virtual void g05(); virtual void g06(); virtual void g07();
    virtual void g08(); virtual void g09(); virtual void g10(); virtual void g11();
    virtual void g12(); virtual void g13(); virtual void g14(); virtual void g15();
    virtual void g16(); virtual void g17(); virtual void g18(); virtual void g19();
    virtual void g20(); virtual void g21(); virtual void g22(); virtual void g23();
    virtual void g24(); virtual void g25(); virtual void g26(); virtual void g27();
    virtual void g28(); virtual void g29(); virtual void g30(); virtual void g31();
    virtual void g32(); virtual void g33(); virtual void g34(); virtual void g35();
    virtual void g36(); virtual void g37(); virtual void g38(); virtual void g39();
    virtual void g40(); virtual void g41(); virtual void g42(); virtual void g43();
    virtual void g44(); virtual void g45(); virtual void g46(); virtual void g47();
    virtual void g48(); virtual void g49(); virtual void g50(); virtual void g51();
    virtual void g52(); virtual void g53(); virtual void g54(); virtual void g55();
    virtual void g56(); virtual void g57(); virtual void g58(); virtual void g59();
    virtual void g60(); virtual void g61(); virtual void g62(); virtual void g63();
    virtual void g64(); virtual void g65(); virtual void g66(); virtual void g67();
    virtual void g68(); virtual void g69(); virtual void g70(); virtual void g71();
    virtual void g72(); virtual void g73(); virtual void g74(); virtual void g75();
    virtual void g76(); virtual void g77(); virtual void g78(); virtual void g79();
    virtual void g80(); virtual void g81(); virtual void g82(); virtual void g83();
    virtual void g84(); virtual void g85(); virtual void g86(); virtual void g87();
    virtual void g88(); virtual void g89(); virtual void g90(); virtual void g91();
    virtual void g92(); virtual void g93(); virtual void g94(); virtual void g95();
    virtual void g96(); virtual void g97(); virtual void g98(); virtual void g99();
    virtual void g100(); virtual void g101(); virtual void g102(); virtual void g103();
    virtual void g104(); virtual void g105(); virtual void g106(); virtual void g107();
    virtual void g108(); virtual void g109(); virtual void g110(); virtual void g111();
    virtual void g112(); virtual void g113(); virtual void g114(); virtual void g115();
    virtual void g116(); virtual void g117(); virtual void g118(); virtual void g119();
    virtual void g120(); virtual void g121(); virtual void g122(); virtual void g123();
    virtual void g124(); virtual void g125(); virtual void g126(); virtual void g127();
    virtual void g128(); virtual void g129(); virtual void g130(); virtual void g131();
    virtual void g132(); virtual void g133(); virtual void g134(); virtual void g135();
    virtual void g136(); virtual void g137(); virtual void g138(); virtual void g139();
    virtual void g140(); virtual void g141(); virtual void g142(); virtual void g143();
    virtual void g144(); virtual void g145(); virtual void g146(); virtual void g147();
    virtual void g148(); virtual void g149(); virtual void g150(); virtual void g151();
    virtual void g152(); virtual void g153(); virtual void g154(); virtual void g155();
    virtual void g156(); virtual void g157(); virtual void g158(); virtual void g159();
    virtual void g160(); virtual void g161(); virtual void g162(); virtual void g163();
    virtual void g164(); virtual void g165(); virtual void g166(); virtual void g167();
    virtual void g168(); virtual void g169(); virtual void g170(); virtual void g171();
    virtual void g172(); virtual void g173(); virtual void g174(); virtual void g175();
    virtual void g176(); virtual void g177(); virtual void g178(); virtual void g179();
    virtual void g180(); virtual void g181(); virtual void g182(); virtual void g183();
    virtual void g184(); virtual void g185(); virtual void g186(); virtual void g187();
    virtual void g188(); virtual void g189(); virtual void g190(); virtual void g191();
    virtual void g192(); virtual void g193(); virtual void g194(); virtual void g195();
    virtual void g196(); virtual void g197(); virtual void g198(); virtual void g199();
    virtual void g200(); virtual void g201(); virtual void g202(); virtual void g203();
    virtual void g204(); virtual void g205(); virtual void g206(); virtual void g207();
    virtual void g208(); virtual void g209(); virtual void g210(); virtual void g211();
    virtual void g212(); virtual void g213(); virtual void g214(); virtual void g215();
    virtual void g216(); virtual void g217(); virtual void g218(); virtual void g219();
    virtual void g220();
};

class cLocomotiveObject {
public:
    virtual void l00(); virtual void l01(); virtual void l02(); virtual void l03();
    virtual void l04(); virtual void l05(); virtual void l06(); virtual void l07();
    virtual void l08(); virtual void l09(); virtual void l10(); virtual void l11();
    virtual void l12(); virtual void l13(); virtual void l14(); virtual void l15();
    virtual void l16(); virtual void l17(); virtual void l18(); virtual void l19();
    virtual void l20(); virtual void l21(); virtual void l22(); virtual void l23();
    virtual void l24(); virtual void l25(); virtual void l26(); virtual void l27();
    virtual void l28(); virtual void l29(); virtual void l30(); virtual void l31();
    virtual void l32(); virtual void l33(); virtual void l34(); virtual void l35();
    virtual void l36(); virtual void l37(); virtual void l38(); virtual void l39();
    virtual void l40(); virtual void l41(); virtual void l42(); virtual void l43();  // 0xac
    virtual void l44(); virtual void l45(); virtual void l46(); virtual void l47();
    virtual void l48(); virtual void l49(); virtual void l50(); virtual void l51();
    virtual void l52(); virtual void l53();
    virtual void l54();                     // 0xd8 -> slot 0xdc
};

class cCombatant {
public:
    virtual void k00(); virtual void k01(); virtual void k02();
    virtual void TakeHit();                // 0x0c
};

class cInteractionTarget {
public:
    virtual void i00();
};

// ---------------------------------------------------------------- the UFO
struct DestParam {
    void* mpArray;      // +0x00
    U32   d004;         // +0x04
    U32   d008;         // +0x08
    U32   d00c;         // +0x0c
    U32   d010;         // +0x10
    float x;            // +0x14
    float y;            // +0x18
    float z;            // +0x1c
    float f020;         // +0x20
    U32   d024;         // +0x24
    U32   d028;         // +0x28
    U32   d02c;         // +0x2c
    U32   d030;         // +0x30
    U32   d034;         // +0x34
    U32   d038;         // +0x38
    U32   d03c;         // +0x3c
    U32   d040;         // +0x40
    U32   d044;         // +0x44
    U32   d048;         // +0x48
    U32   d04c;         // +0x4c
    U8    b050;         // +0x50
    U8    pad051;       // +0x51
    U8    pad052;       // +0x52
    U8    pad053;       // +0x53
    float f054;         // +0x54
    float f058;         // +0x58
    float f05c;         // +0x5c
    U32   d060;         // +0x60
    float f064;         // +0x64
    U32   d068;         // +0x68
    float f06c;         // +0x6c
    float f070;         // +0x70
    U32   d074;         // +0x74
};

typedef void (__thiscall* VfDest)(void*, DestParam*);

struct cSPGameDataUFO {
    // --- flat retail layout: vtable pointers of the four subobjects are at
    // +0x000 (cGameData), +0x034 (cLocomotiveObject), +0x108, +0x508 (cCombatant),
    // +0x5d0 (cInteractionTarget), +0x5e8.
    // --- methods defined in this slice
    float GetScale();
    void  UpdateScale();
    void  UpdateDestinationFromTarget();
    bool  OnMessage(U32 messageID, int arg);
    void  SetNPCTool(void* pTool);
    int   ClearAttackBehaviorTarget(IRefObject* pTarget);   // this is the +0x7a8 target
    int   ClearDefenseBehaviorTarget(IRefObject* pTarget);  // this is the +0x7ac target
    int   GetFieldValues(void* pOut);
    float GetScaleRadius();
    void  SetHeading(const Vector3* pDir);
    void  Destroy();

    // --- helpers in the same module
    float GetScaleFactor();       // 0x00c3ad40

    // --- fields (flat retail layout; offsets are exact)
    void* mpVftbl0;                        // +0x000
    U8 pad004[48];                         // +0x004
    void* mpVftbl34;                       // +0x034
    U8 pad038[28];                         // +0x038
    float mf054;                           // +0x054
    float mf058;                           // +0x058
    float mf05c;                           // +0x05c
    float mf060;                           // +0x060
    float mf064;                           // +0x064
    float mf068;                           // +0x068
    float mf06c;                           // +0x06c
    float mf070;                           // +0x070
    float mf074;                           // +0x074
    float mf078;                           // +0x078
    float mf07c;                           // +0x07c
    float mf080;                           // +0x080
    U32 mFlags84;                          // +0x084
    U8 pad088[8];                          // +0x088
    float mf090;                           // +0x090
    float mf094;                           // +0x094
    U8 pad098[112];                        // +0x098
    void* mpVftbl108;                      // +0x108
    U8 pad10c[280];                        // +0x10c
    int mInt224;                           // +0x224
    int mInt228;                           // +0x228
    U8 pad22c[732];                        // +0x22c
    void* mpVftbl508;                      // +0x508
    U8 pad50c[196];                        // +0x50c
    void* mpVftbl5d0;                      // +0x5d0
    U8 pad5d4[20];                         // +0x5d4
    void* mpVftbl5e8;                      // +0x5e8
    U8 pad5ec[160];                        // +0x5ec
    void* mp68c;                           // +0x68c
    U8 pad690[56];                         // +0x690
    void* mp6c8;                           // +0x6c8
    U32 md6cc;                             // +0x6cc
    U32 mTimer6d0[8];                      // +0x6d0
    U32 mTimer6f0[8];                      // +0x6f0
    U32 md710;                             // +0x710
    int mUFOType;                          // +0x714
    float mf718;                           // +0x718
    float mf71c;                           // +0x71c
    float mf720;                           // +0x720
    U8 pad724[40];                         // +0x724
    U8 mb74c;                              // +0x74c
    U8 pad74d[3];                          // +0x74d
    Vector3 mDestination;                  // +0x750
    RefHolder mRef75C;                     // +0x75c
    RefHolder mRef760;                     // +0x760
    int mInt764;                           // +0x764
    float mf768;                           // +0x768
    int md76c;                             // +0x76c
    U32 md770[0x18 / 4];                   // +0x770
    U32 md788;                             // +0x788
    U32 md78c;                             // +0x78c
    RefHolder mRef790;                     // +0x790
    RefHolder mRef794;                     // +0x794
    RefHolder mRef798;                     // +0x798
    RefHolder mRef79c;                     // +0x79c
    RefHolder mRef7a0;                     // +0x7a0
    RefHolder mRef7a4;                     // +0x7a4
    RefHolder mRef7a8;                     // +0x7a8
    RefHolder mRef7ac;                     // +0x7ac
    void* mp7b0;                           // +0x7b0
    U8 pad7b4[4];                          // +0x7b4
    U32 mTimer7b8[8];                      // +0x7b8
    RefHolder mRef7d8;                     // +0x7d8
    U32 mFlags7dc;                         // +0x7dc
    void* mp7e0;                           // +0x7e0
    void* mp7e4;                           // +0x7e4
    void* mp7e8;                           // +0x7e8
    U8 pad7ec[4];                          // +0x7ec
    RefHolder mRef7f0;                     // +0x7f0
    U8 pad7f4[12];                         // +0x7f4
    void* mp800;                           // +0x800
    void* mp804;                           // +0x804
    void* mp808;                           // +0x808
    void* mp80c;                           // +0x80c
    int md810;                             // +0x810
    int md814;                             // +0x814
};

// ---------------------------------------------------------------- cVarListSerializer
struct cVarListSerializer {
    U32 md[0xa14 / 4];
    void ctor(void* pA, void* pB, int pC);   // 0x00692f90
    int  GetFields(void* pOut);              // 0x00695960
};

// shims for calling free extern stubs with the right abi
static __forceinline void* GetAppCameraManager()
{
    return ((cAppBase*)App())->GetCameraManager();
}

// ---------------------------------------------------------------- 0x00c3ae70
// @ 0xc3ae70
float cSPGameDataUFO::GetScale()
{
    cUFOKinestheticsTuning* pTuning = *(cUFOKinestheticsTuning**)0x168df68;

    float result = gF_1485720;

    int state = *(int*)((char*)GetTriggerMgr() + 0x2c);
    bool bGameMode = (state == 1 || state == 2);

    int context = (int)GetUniverseContext();
    switch (context) {
    case 0: {
        if (bGameMode)
            return pTuning->m2MinExtent;   // +0x170
        if ((mFlags7dc >> 9) & 1)
            return gF_1485720;
        void* pCam = 0;
        void* pActive = GetAppCameraManager();
        cCameraController* pActive2 = ((cCameraManager*)pActive)->GetActiveCamera();
        if (pActive2 != 0) {
            pCam = pActive2->QueryInterface(0x303154cd);
            if (pCam != 0 && *(char*)((char*)pCam + 0x140) != 0)
                return pTuning->mAllyVelocityFactor;   // +0x5c
        } else {
            pCam = 0;
        }
        float local = 0.0f;
        if (pCam != 0) {
            local = ((Fn1017BB0*)pCam)->f();
        } else {
            cViewer* pViewer = ((cPlayerCameraManager*)GetAppCameraManager())->GetViewer();
            if (pViewer != 0) {
                Vector3 camPos;
                pViewer->GetCameraLocationInfo(&camPos, 0, 0, 0);
                float camLen = (float)sqrtf(camPos.x * camPos.x + camPos.y * camPos.y + camPos.z * camPos.z);
                if (camLen > gF_1485720) {
                    Vector3 out;
                    ((FnB81630*)PlanetModel())->f(&out, &camPos);
                    local = camLen - (float)sqrtf(out.x * out.x + out.y * out.y + out.z * out.z);
                }
            }
        }
        if (local > pTuning->mFighterVelocityFactor) {   // +0x54
            if (mUFOType != 0)
                return pTuning->mKeyboardMovementSpeedZoomedOut;  // +0x60
            return pTuning->mUberTurretVelocityFactor;            // +0x58
        }
        return result;
    }
    case 1: {
        if (bGameMode)
            return pTuning->m2HitSphereActiveDistance;   // +0x170 (context==1 variant)
        if ((mFlags7dc >> 9) & 1)
            return pTuning->mMaxUFODamagePush;           // +0x124
        int arch = (int)IsArchivedState();
        if (arch != 0) {
            int v = (int)FUN_00c8b520(FUN_00801920((void*)arch));
            if (v == 0)
                return pTuning->mUFODamageVelocityDecayRate;   // +0x128
        }
        float lo = pTuning->mAltMaxAltitude;   // +0x12c
        float lo2 = FUN_01017030(1);
        if (lo2 > lo) lo = lo2;
        float hi = pTuning->mAltPlumpDistance; // +0x130
        float hi2 = FUN_01017070(1);
        if (hi2 < hi) hi = hi2;
        cCameraController* pActive = ((cCameraManager*)GetAppCameraManager())->GetActiveCamera();
        void* pCam = ((FnC375B0*)&pActive)->f();
        if (pCam != 0) {
            float d = ((cCameraController*)pCam)->GetDistance();
            float t = (d - lo) / (hi - lo);
            if (t <= 0.0f) t = 0.0f;
            if (t >= 1.0f) t = 1.0f;
            float a = ((FnC37550*)pTuning)->f(mUFOType);   // +0x124
            float b = ((FnC37570*)pTuning)->f(mUFOType);   // +0x128
            return (b - a) * t + a;
        }
        cViewer* pViewer = ((cPlayerCameraManager*)GetAppCameraManager())->GetViewer();
        Vector3 camPos;
        pViewer->GetCameraLocationInfo(&camPos, 0, 0, 0);
        float dx = camPos.x - mf718;
        float dy = camPos.y - mf71c;
        float dz = camPos.z - mf720;
        float dist = (float)sqrtf(dx * dx + dy * dy + dz * dz);
        float t = (dist - lo) / (hi - lo);
        if (t <= 0.0f) t = 0.0f;
        if (t >= 1.0f) t = 1.0f;
        {
            float a = pTuning->mMaxUFODamagePush;           // +0x124
            float b = pTuning->mUFODamageVelocityDecayRate; // +0x128
            return (b - a) * t + a;
        }
    }
    case 2: {
        if (bGameMode)
            return pTuning->m2BomberScale;   // +0x174
        if ((mFlags7dc >> 9) & 1) {
            if (mUFOType == 0)
                return pTuning->mExtra144;   // +0x144
            return pTuning->mExtra14c;       // +0x14c
        }
        float lo = pTuning->m2MinAltitude;   // +0x154
        float lo2 = FUN_01017030(2);
        if (lo2 > lo) lo = lo2;
        float hi = pTuning->m2MaxAltitude;   // +0x158
        float hi2 = FUN_01017070(2);
        if (hi2 < hi) hi = hi2;
        cCameraController* pActive = ((cCameraManager*)GetAppCameraManager())->GetActiveCamera();
        void* pCam = 0;
        if (pActive != 0) {
            pCam = pActive->QueryInterface(0x303154cc);
            if (pCam != 0) {
                float d = ((cCameraController*)pCam)->GetDistance();
                float t = (d - lo) / (hi - lo);
                if (t <= 0.0f) t = 0.0f;
                if (t >= 1.0f) t = 1.0f;
                float a = ((FnC37550*)pTuning)->f(mUFOType);
                float b = ((FnC37570*)pTuning)->f(mUFOType);
                return (b - a) * t + a;
            }
        }
        return ((FnC37550*)pTuning)->f(mUFOType);
    }
    default:
        return result;
    }
}

// ---------------------------------------------------------------- 0x00c3b3f0
// @ 0xc3b3f0
void cSPGameDataUFO::UpdateScale()
{
    if ((mFlags84 & 0x10) != 0 && (mFlags84 & 0x20) == 0)
        return;

    float ex = mf060 - mf054;
    float ey = mf064 - mf058;
    float ez = mf068 - mf05c;
    float v[3];
    v[0] = ex;
    v[1] = ey;
    v[2] = ez;
    float* pExtent = v + 1;
    if (!(v[0] < v[1]))
        pExtent = v;
    if (v[2] > *pExtent)
        pExtent = v + 2;
    float extent = *pExtent;

    float scale = gF_1485720;
    if (extent > gF_146bb70) {
        cUFOKinestheticsTuning* pTuning = *(cUFOKinestheticsTuning**)0x168df68;
        if (extent > pTuning->mFighterScale)        // +0x2c
            scale = pTuning->mFighterScale / extent;
        else if (extent < pTuning->mBomberScale)    // +0x28
            scale = pTuning->mBomberScale / extent;
    }

    float r = GetScaleFactor() * GetScale() * scale;
    void* pLoco = (char*)this + 0x34;
    typedef void (__thiscall* Vf)(void*, float);
    ((Vf)(*(void**)(*(char**)pLoco + 0x40)))(pLoco, r);
}

// ---------------------------------------------------------------- 0x00c3b4d0
// @ 0xc3b4d0
void cSPGameDataUFO::UpdateDestinationFromTarget()
{
    void* pLoco = (char*)this + 0x34;
    typedef void* (__thiscall* VGet)(void*);
    void* pTarget = ((VGet)(*(void**)(*(char**)pLoco + 0xac)))(pLoco);
    if (pTarget == 0)
        return;

    if ((*(U32*)((char*)pTarget + 4) >> 0x11) & 1) {
        mFlags84 |= 0x40;
        float f = *(float*)((char*)pTarget + 0x6c);
        mf090 = f;
        mf094 = f;
    }
    if ((*(U8*)((char*)pTarget + 6) & 1) != 0) {
        float r = GetScaleFactor() * ((FnC37DC0*)this)->f();
        typedef void (__thiscall* Vf)(void*, void*, float);
        ((Vf)(*(void**)(*(char**)((char*)this + 0x34) + 0x64)))(pLoco, (char*)pTarget + 0x70, r);
        mFlags84 = (mFlags84 & ~0x10) | 0x20;
    }
}

// ---------------------------------------------------------------- 0x00c3b560
// @ 0xc3b560
bool cSPGameDataUFO::OnMessage(U32 messageID, int arg)
{
    (void)arg;
    if ((messageID == 0x44f1189 || messageID == 0x67b2a95) && *(int*)((char*)this + 0x208) != 0) {
        void* pSpaceGame = SpaceGameGet();
        if (((FnB18E40*)pSpaceGame)->f()) {
            void* pServer = MessageServer();
            typedef int (__thiscall* Vf)(void*, U32, int, int, int);
            ((Vf)(*(void**)(*(char**)pServer + 0x18)))(pServer, 0x67b2a95, 0, 0, 0);
            return false;
        }
        ((FnC382E0*)((char*)this - 0x5e8))->f();
    }
    return false;
}

// ---------------------------------------------------------------- 0x00c3b5c0
// @ 0xc3b5c0
void cSPGameDataUFO::SetNPCTool(void* pTool)
{
    RefHolder* pSlot = &mRef790;
    IRefObject* pKeep = pSlot->mpObject;
    if (pKeep != 0)
        pKeep->AddRef();
    if (pSlot->mpObject != 0) {
        IRefObject* pOld = pSlot->mpObject;
        pSlot->mpObject = 0;
        pOld->Release();
    }
    void* pMgr = FUN_00b3d390(pTool, pSlot);
    ((Fn104E340*)pMgr)->f((unsigned int)pTool);
    if (pKeep != 0) {
        if (((Fn104BD50*)pKeep)->f() && pKeep != pSlot->mpObject) {
            void* pMgr2 = FUN_00b3d390(pKeep, 0);
            ((Fn104FA90*)pMgr2)->f(pKeep);
        }
        pKeep->Release();
    }
}

// ---------------------------------------------------------------- 0x00c3b630
// @ 0xc3b630
int cSPGameDataUFO::ClearAttackBehaviorTarget(IRefObject* pTarget)
{
    IRefObject* pAttack = 0;
    IRefObject* pDefense = 0;
    if (pTarget != 0) {
        typedef void* (__thiscall* VQI)(void*, U32);
        pAttack = (IRefObject*)((VQI)(*(void**)(*(char**)pTarget + 0x0c)))(pTarget, 0xee9b2232);
        pDefense = (IRefObject*)((VQI)(*(void**)(*(char**)pTarget + 0x0c)))(pTarget, 0x4e3faaf);
    }
    int saved = 0;
    if (pAttack != 0)
        saved = *(int*)((char*)pAttack + 0x224);
    else if (pDefense != 0)
        saved = *(int*)((char*)pDefense + 0x63c);

    if (mRef7a8.mpObject != 0)
        ((FnC38B10*)this)->f();

    if (pTarget != 0 && pTarget != mRef7a8.mpObject) {
        IRefObject* pOld = mRef7a8.mpObject;
        pTarget->AddRef();
        mRef7a8.mpObject = pTarget;
        if (pOld != 0)
            pOld->Release();
    }

    if (pAttack != 0) {
        ++*(int*)((char*)pAttack + 0x224);
        return saved;
    }
    if (pDefense != 0)
        ++*(int*)((char*)pDefense + 0x63c);
    return saved;
}

// ---------------------------------------------------------------- 0x00c3b700
// @ 0xc3b700
int cSPGameDataUFO::ClearDefenseBehaviorTarget(IRefObject* pTarget)
{
    IRefObject* pAttack = 0;
    IRefObject* pDefense = 0;
    if (pTarget != 0) {
        typedef void* (__thiscall* VQI)(void*, U32);
        pAttack = (IRefObject*)((VQI)(*(void**)(*(char**)pTarget + 0x0c)))(pTarget, 0xee9b2232);
        pDefense = (IRefObject*)((VQI)(*(void**)(*(char**)pTarget + 0x0c)))(pTarget, 0x4e3faaf);
    }
    int saved = 0;
    if (pAttack != 0)
        saved = *(int*)((char*)pAttack + 0x228);
    else if (pDefense != 0)
        saved = *(int*)((char*)pDefense + 0x638);

    if (mRef7ac.mpObject != 0)
        ((FnC38B90*)this)->f();

    if (pTarget != 0 && pTarget != mRef7ac.mpObject) {
        IRefObject* pOld = mRef7ac.mpObject;
        pTarget->AddRef();
        mRef7ac.mpObject = pTarget;
        if (pOld != 0)
            pOld->Release();
    }

    if (pAttack != 0) {
        ++*(int*)((char*)pAttack + 0x228);
        return saved;
    }
    if (pDefense != 0)
        ++*(int*)((char*)pDefense + 0x638);
    return saved;
}

// ---------------------------------------------------------------- 0x00c3b7f0
// @ 0xc3b7f0
void cUFOKinestheticsTuning::Init()
{
    void* pManager = PropertyManager();
    if (mpPropList != 0) {
        void* pOld = mpPropList;
        mpPropList = 0;
        ((IReleased*)pOld)->Release();
    }
    typedef void (__thiscall* Vf)(void*, U32, int, void*);
    ((Vf)(*(void**)(*(char**)pManager + 0x2c)))(pManager, 0x99fb6f5b, 0x2ae0c7e, &mpPropList);
    ReadProps();
    void* pServer = MessageServer();
    md1a8 = (U32)pServer;
    md1ac = (U32)this;
    md1b0 = 0x146bb64;
    md1b4 = 1;
    md1b8 = 0;
    if (pServer != 0) {
        if (this != 0) {
            typedef int (__thiscall* Vf2)(void*, void*, U32);
            ((Vf2)(*(void**)(*(char**)pServer + 0x24)))(pServer, this, 0xf62def);
        }
    }
}

// ---------------------------------------------------------------- 0x00c3b880
// @ 0xc3b880
float cUFOKinestheticsTuning::GetGalaxyWarpMultiplier(int index, int warpMode)
{
    float factor = gF_1485720;
    if (warpMode == 0) {
        void* pSpaceGame = SpaceGameGet();
        if ((*(U8*)((char*)pSpaceGame + 0xc4) & 0x20) != 0)
            factor = ((Fn1005C60*)pSpaceGame)->f(5);
    } else if (warpMode == 4) {
        factor = m2PlumpScale;   // +0x188
    }

    int count = 0;
    float* array = 0;
    FUN_6a08b0(mpPropList, 0x5c80689, &count, &array);
    int i = index - 1;
    if (i < count)
        return array[i] * factor;
    return factor;
}

// ---------------------------------------------------------------- 0x00c3b9a0
// @ 0xc3b9a0
void cSPGameDataUFO::Destroy()
{
    void* p655 = mp6c8;
    *(void**)this = (void*)0x146bd28;
    *(void**)((char*)this + 0x04) = (void*)0x146bd14;
    *(void**)((char*)this + 0x34) = (void*)0x146bc18;
    *(void**)((char*)this + 0x108) = (void*)0x146bc10;
    *(void**)((char*)this + 0x508) = (void*)0x146bba8;
    *(void**)((char*)this + 0x5d0) = (void*)0x146bb88;
    *(void**)((char*)this + 0x5e8) = (void*)0x146bb80;

    if (p655 != 0) {
        ((FnBCAE90*)p655)->f();
        operator_delete(p655);
    }

    if (mRef75C.mpObject != 0) {
        IRefObject* p = mRef75C.mpObject;
        mRef75C.mpObject = 0;
        typedef int (__thiscall* Vf)(void*);
        ((Vf)(*(void**)(*(char**)p + 0xc0)))(p);
    }
    if (mRef760.mpObject != 0) {
        IRefObject* p = mRef760.mpObject;
        mRef760.mpObject = 0;
        typedef int (__thiscall* Vf)(void*);
        ((Vf)(*(void**)(*(char**)p + 0xc0)))(p);
    }

    // 0x804 sync handler
    void* pHandler = mp804;
    if (pHandler != 0) {
        void* a = mp808;
        void* b = mp80c;
        void* c = (void*)md810;
        void* d = (void*)md814;
        mp804 = 0;
        ((Fn571DB0*)this)->f(pHandler, a, b, c, d);
    }
    if (mp800 != 0)
        ((IRefObject*)mp800)->Release();
    if (mRef7f0.mpObject != 0)
        ((IRefObject*)mRef7f0.mpObject)->Release();

    // eastl wstring at 0x7e0 (begin=+0, end=+4, cap=+8)
    if ((((char*)mp7e8 - (char*)mp7e0) & ~1) > 2 && mp7e0 != 0)
        operator_delete(mp7e0);

    if (mRef7d8.mpObject != 0)
        ((IRefObject*)mRef7d8.mpObject)->Release();

    ((FnB638B0*)((char*)this + 0x7b8))->f();

    if (mRef7ac.mpObject != 0)
        ((IRefObject*)mRef7ac.mpObject)->Release();
    if (mRef7a8.mpObject != 0)
        ((IRefObject*)mRef7a8.mpObject)->Release();
    if (mRef7a4.mpObject != 0)
        ((IRefObject*)mRef7a4.mpObject)->Release();
    if (mRef7a0.mpObject != 0)
        ((IRefObject*)mRef7a0.mpObject)->Release();
    if (mRef79c.mpObject != 0)
        ((IRefObject*)mRef79c.mpObject)->Release();
    if (mRef798.mpObject != 0)
        ((IRefObject*)mRef798.mpObject)->Release();
    if (mRef794.mpObject != 0)
        ((IRefObject*)mRef794.mpObject)->Release();
    if (mRef790.mpObject != 0)
        ((IRefObject*)mRef790.mpObject)->Release();

    // intrusive list at 0x770
    {
        void* pHead = *(void**)((char*)this + 0x770);
        void* pEnd = (char*)this + 0x770;
        while (pHead != pEnd) {
            void* pNext = *(void**)pHead;
            operator_delete(pHead);
            pHead = pNext;
        }
    }

    if (mRef760.mpObject != 0)
        ((IRefObject*)mRef760.mpObject)->Release();
    if (mRef75C.mpObject != 0)
        ((IRefObject*)mRef75C.mpObject)->Release();

    if (md710 != 0)
        ((IRefObject*)md710)->Release();
    ((FnB638B0*)((char*)this + 0x6f0))->f();
    ((FnB638B0*)((char*)this + 0x6d0))->f();
    if (*(void**)((char*)this + 0x68c) != 0)
        ((IRefObject*)*(void**)((char*)this + 0x68c))->Release();
    ((FnB638B0*)((char*)this + 0x668))->f();
    ((FnB638B0*)((char*)this + 0x648))->f();
    ((FnB638B0*)((char*)this + 0x628))->f();

    *(void**)((char*)this + 0x5e8) = (void*)0x13eb394;
    ((FnAC0520*)((char*)this + 0x5d0))->f();
    ((FnBFCD00*)((char*)this + 0x508))->f();
    ((FnC432E0*)((char*)this + 0x34))->f();
    ((FnB184C0*)this)->f();
}

// ---------------------------------------------------------------- 0x00c3bc80
// @ 0xc3bc80
int cSPGameDataUFO::GetFieldValues(void* pOut)
{
    cVarListSerializer localA14;    // +0x508 serialiser (constructed first, lower in the frame)
    cVarListSerializer local1428;   // `this` serialiser

    int sum = ((FnB18420*)this)->f(pOut);
    sum += ((FnC0AF90*)((char*)this + 0x34))->f(pOut);

    localA14.ctor((char*)this + 0x508, (void*)0x1570858, 0x1a80d26);
    sum += localA14.GetFields(pOut);

    local1428.ctor(this, (void*)0x1573290, 0x1a80d26);
    sum += local1428.GetFields(pOut);

    return sum;
}

// ---------------------------------------------------------------- 0x00c3be10
// @ 0xc3be10
float cSPGameDataUFO::GetScaleRadius()
{
    float v[3];
    v[0] = mf078 - mf06c;
    v[1] = mf07c - mf070;
    v[2] = mf080 - mf074;
    float* pExtent = v + 1;
    if (!(v[0] < v[1]))
        pExtent = v;
    if (v[2] > *pExtent)
        pExtent = v + 2;

    return GetScale() * *pExtent * gF_1471064;
}

// ---------------------------------------------------------------- 0x00c3be70
// @ 0xc3be70
void cSPGameDataUFO::SetHeading(const Vector3* pDir)
{
    float x = pDir->x;
    float y = pDir->y;
    float z = pDir->z;
    float inv = 1.0f / (float)sqrtf(x * x + y * y + z * z);
    float s = mf768;

    mDestination.x = s * (x * inv);
    mDestination.y = s * (inv * y);
    mDestination.z = s * (inv * z);

    mb74c = 0;
    ((FnBC3110*)((char*)this + 0x648))->f();

    DestParam dp;
    dp.d004 = 0;
    dp.d008 = 0;
    dp.d00c = 0;
    dp.x = mDestination.x;
    dp.y = mDestination.y;
    dp.z = mDestination.z;
    dp.f020 = gF_1485720;
    dp.d028 = 0;
    dp.b050 = 0;
    dp.f054 = 0.0f;
    dp.f058 = 0.0f;
    dp.f05c = 0.0f;
    dp.d060 = 1;
    dp.f064 = gF_13ec4b4;
    dp.f06c = gF_146bb6c;
    dp.f070 = 0.0f;
    dp.d074 = 0;
    void* pLoco = (char*)this + 0x34;
    ((VfDest)(*(void**)(*(char**)((char*)this + 0x34) + 0xdc)))(pLoco, &dp);
    if (dp.mpArray != 0 && ((int*)dp.mpArray)[-1] != 0)
        operator_delete(dp.mpArray);
}
