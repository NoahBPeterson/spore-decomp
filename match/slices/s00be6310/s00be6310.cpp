// Slice s00be6310: 0x00be6310..0x00be6f60 (5 functions).
//
//   0x00be6310  Simulator::cCity::cCity        (1512 B)
//   0x00be6900  cCity::FUN_00be6900            (1160 B)  turret refresh
//   0x00be6d90  cCity::FUN_00be6d90            ( 424 B)  defense score
//   0x00be6f40  cCity::FUN_00be6f40            (  17 B)
//   0x00be6f60  cSpatialObject::FUN_00be6f60   (  36 B)
//
// Toolchain: cl 15.00.30729.01 (VS2008 SP1), /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------- callee ABI
//
// Every helper below is declared (never defined) so that the compiler emits the
// same direct `call` the original does; all of them are thiscall with the
// argument count shown by the callee's own `ret N`.

void __cdecl EASTL_allocator_deallocate(void* p);            // 0x00f47380  operator delete[]

// ---------------------------------------------------------------- shared types

// SP::cCombatant sub-object.  Only the damage state (word #2) is read by this slice.
struct cCombatant {
    int mField00;
    int mField04;
    int mDamageState;                                        // +0x08
    int GetDamageState();                                    // 0x008e7f80  (mov eax,[ecx+8]; ret)
};

// Object reachable through cCity + 0x590; the score doubles while its +0x8a flag is clear.
struct cFlagHolder {
    unsigned char mRaw000[0x8a];
    unsigned char mFlag8a;                                   // +0x8a
};

// Element of the pointer vector at cCity + 0x340: a raid participant whose combat
// state lives in a cCombatant at +0x120 and whose weight is virtual slot 0x5c/4 = 23.
struct cRaidParticipant {
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
    virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22();
    virtual float GetWeight();                               // vtable +0x5c
    unsigned char mRaw004[0x120 - 0x04];
    cCombatant    mCombatant120;                             // +0x120
};

// Element of the pointer vector at cCity + 0x354: a scored building whose combat
// state lives in a cCombatant at +0x588 and whose score is FUN_00bd0110 (an x87
// leaf returning ST(0)).
struct cBuildingScore {
    virtual void d00();
    virtual void Release();                                  // vtable +0x04
    unsigned char mRaw004[0x588 - 0x04];
    cCombatant    mCombatant588;                             // +0x588
    float Score();                                           // 0x00bd0110
};

// Plain eastl-style pointer vector (mpBegin / mpEnd / mpCapacity).
struct cPointerVector {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    unsigned Size() const { return (unsigned)(mpEnd - mpBegin); }
    void DoInsertPtr(void** pos, void* const& value);         // 0x00aea5d0
};

// Element layout of the vector at cCity + 0x528 (three dwords, stride 0x0c).
struct cElem0c {
    int mField00;
    int mField04;
    int mField08;
};

struct cElem0cVector {
    cElem0c* mpBegin;
    cElem0c* mpEnd;
    cElem0c* mpCapacity;
};

// eastl vector with a 32-slot inline buffer (used for cCity + 0x354 as well as for
// the local scratch vector inside cCity::FUN_00be6d90).  Layout: begin, end,
// capacity, one unused slot, then the inline-buffer pointer.
struct cInlinePtrVector {
    void** mpBegin;                                          // +0x00
    void** mpEnd;                                            // +0x04
    void** mpCapacity;                                       // +0x08
    void** mUnused0c;                                        // +0x0c
    void** mpBuffer;                                         // +0x10
    void Reset(void** first, void** last);                   // 0x00e25bd0  eastl::vector::erase
    void Append(void** first, void** last, float f);         // 0x00bdf600
};

// Opaque 0x64-byte SP::cActionCircle sub-objects at cCity + 0x3ec / +0x450 / +0x4b4.
struct cActionCircle {
    unsigned char mRaw000[0x64];
    void RemoveAgent(void* agent);                           // 0x00afae50
    void LayoutConstruct();                                  // 0x00afba10
};

// SP::cSpatialObject sub-object, located at cCity + 0x120 by the constructor
// (which runs SP::cSpatialObject::cSpatialObject on that address).
struct cSpatialObject {
    void* mpVtbl;                                            // +0x000  (cCity+0x120)
    unsigned char mRaw004[0xd0];
    void cSpatialObject_func80h();                           // 0x00c88510
    void FUN_00be6f60();                                     // 0x00be6f60
    cSpatialObject();                                        // 0x00c89630
};

// Leading 0x120 bytes of Simulator::cCity (the primary base sub-object built by
// FUN_00c011c0).  It carries the vertex/primary/INameableEntity vtables.
struct cCityPrefix {
    void* mpVtbl0;                                           // +0x000
    void* mpVtbl1;                                           // +0x004
    unsigned char mRaw008[0x2c];                             // +0x008..+0x033
    void* mpVtbl2;                                           // +0x034
    unsigned char mRaw038[0xe8];                             // +0x038..+0x11f
    cCityPrefix();                                           // 0x00c011c0
};

// SP::cInteractionTarget sub-object (constructor at cCity + 0x1f4).  Its second
// vtable (the cListenerBase interface) sits at +0x18.
struct cInteractionTarget {
    void* mpVtbl;                                            // +0x000
    unsigned char mRaw004[0x14];                             // +0x004..+0x017
    void* mpVtbl2;                                           // +0x018
    cInteractionTarget();                                    // 0x00ac03d0
};

// SP::cGonzagoTimer / SP::cSPTimer (0x20 bytes).
struct cTimer {
    unsigned char mRaw[0x20];
    void Construct();                                        // 0x00b63890
    void Start();                                            // 0x00bc30f0
};

// eastl 16-bit string header (three pointers).
struct cStr16 {
    void* mpBegin;                                           // +0x00
    void* mpEnd;                                             // +0x04
    void* mpCapacity;                                        // +0x08
};

// Red-black-tree container: a 4-byte header followed by the 0x14-byte anchor.
struct cRbTree {
    int           mField00;                                  // +0x00  (never touched)
    void*         mpNodeLeft;                                // +0x04
    void*         mpNodeRight;                               // +0x08
    void*         mpNodeParent;                              // +0x0c
    union {
        unsigned int  mColorWord;                            // +0x10  (zeroed as a dword)
        struct {
            unsigned char mColor;                            // +0x10
            unsigned char mPad11[3];                         // +0x11
        };
    };
    unsigned int  mnSize;                                    // +0x14
};

// One of the four 0x80-byte culture-target records allocated by FUN_00be60a0.
struct cRefCounted;                                          // vtable below
struct cCultureTargetInfo {
    void*         mPtr00[8];                                 // +0x00..+0x1f
    unsigned char mFlag20;                                   // +0x20
    unsigned char mPad21[3];                                 // +0x21
    float         mF24;                                      // +0x24
    float         mF28;                                      // +0x28
    float         mF2c;                                      // +0x2c
    unsigned char mPad30[0x40];                              // +0x30..+0x6f
    cRefCounted*  mPtr70;                                    // +0x70
    unsigned char mFlag74;                                   // +0x74
    unsigned char mPad75[3];                                 // +0x75
    cRefCounted*  mPtr78;                                    // +0x78
    unsigned char mPad7c[4];                                 // +0x7c
};

struct cCultureTargetInfoVector {
    cCultureTargetInfo* mpBegin;                             // +0x00
    cCultureTargetInfo* mpEnd;                               // +0x04
    cCultureTargetInfo* mpCapacity;                          // +0x08
    void Resize(int count);                                  // 0x00be60a0
};

// 3x3 float matrix, copied with rep movsd by the original code.
struct Mat3 {
    float m[9];
};

// Effect descriptor handed to cEffect::SetDescriptor (0x38 bytes).
struct cEffectDesc {
    unsigned short mFlags;                                   // +0x00
    short          mCount;                                   // +0x02
    float          mF04;                                     // +0x04
    float          mF08;                                     // +0x08
    float          mF0c;                                     // +0x0c
    float          mF10;                                     // +0x10
    Mat3           mMatrix;                                  // +0x14
};

// cEffect: slot 1 releases, slot 6 consumes the descriptor.
struct cEffect {
    virtual void d00();                                      // +0x00
    virtual void Release();                                  // +0x04
    virtual void SetVisible(int visible);                    // +0x08
    virtual void d03();                                      // +0x0c
    virtual void d04();                                      // +0x10
    virtual void d05();                                      // +0x14
    virtual void SetDescriptor(cEffectDesc* desc);           // +0x18
};

// cEffectsManager: slot 0x2c spawns an effect by id.
struct cEffectsManager {
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
    virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void d08(); virtual void d09(); virtual void d10();
    virtual char SpawnEffect(unsigned int id, int flags, cEffect** out);  // +0x2c
};

// Sub-object embedded at cNoun + 0x70 (transform interface).
struct cNounSub70 {
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
    virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void d08(); virtual void d09(); virtual void d10();
    virtual float* GetPosition();                            // +0x2c
    virtual float* GetOrientation();                         // +0x30
    virtual void d13(); virtual void d14(); virtual void d15();
    virtual void SetScale(float f);                          // +0x40
    void FUN_00c88530(float f);                              // 0x00c88530
};

// The noun produced by cGameNounManager::CreateNoun.  Its own vtable is slots
// 0=AddRef, 1=Release, 2=SetVisible, 3=Cast; the +0x70 sub-object has the
// transform vtable.
struct cNoun {
    virtual void AddRef();                                   // +0x00
    virtual void Release();                                  // +0x04
    virtual void SetVisible(int visible);                    // +0x08
    virtual cNoun* Cast(unsigned int type);                  // +0x0c
    unsigned char mRaw010[0x60];                             // +0x10..+0x6f
    cNounSub70    mSub70;                                    // +0x70
};

struct cGameNounManager {
    cNoun* CreateNoun(void* archetype);                      // 0x00b20c60
};

cGameNounManager* NounManager();                             // 0x00b3d300
cEffectsManager*  EffectsManager();                          // 0x0067ddd0

// Simple thiscall target modelled with the vtable slot used by FUN_00be6900.
struct cSimOrnament {
    void SetStyleModel(void* name, void* style);             // 0x00c6f770
};

// cCity's own vtable: FUN_00be6900 calls slot 0x4c to turn a 0x528 element
// into the style-model argument.
struct cCityVtbl {
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
    virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18();
    virtual void* Vfn4c(void* p);                            // +0x4c
};

// cDirectPropertyList (only GetIntProperty is used here).
struct cDirectPropertyList {
    int GetIntProperty(unsigned int id) const;               // 0x006a2660
};

// Random generator singletons.
struct cRandomGlobal {
    unsigned int RandomUint32Uniform(unsigned int n);        // 0x00a68fb0
};

extern cDirectPropertyList* g_15fd918;                       // 0x015fd918  sAppProperties
extern cRandomGlobal      g_1601760;                         // 0x01601760
extern const float        DAT_0168c330;                      // +0x0168c330
extern const float        DAT_0168c334;                      // +0x0168c334
extern const float        DAT_0168c338;                      // +0x0168c338
extern const float        DAT_0168c33c;                      // +0x0168c33c
extern const float        DAT_0168c340;                      // +0x0168c340
extern const float        DAT_0168c344;                      // +0x0168c344
extern const float        DAT_0168c348;                      // +0x0168c348
extern const float        DAT_0168c34c;                      // +0x0168c34c
extern const float        DAT_0168c350;                      // +0x0168c350
extern const float        DAT_0168c354;                      // +0x0168c354
extern const float        DAT_0168c358;                      // +0x0168c358
extern const float        DAT_0168c35c;                      // +0x0168c35c
extern const float        DAT_0168bd70;                      // +0x0168bd70
extern const float        DAT_0168bd74;                      // +0x0168bd74
extern const float        DAT_0168bd78;                      // +0x0168bd78
extern const float        DAT_013f1cac;                      // +0x013f1cac  50.0f
extern const float        DAT_01473c70;                      // +0x01473c70  10.0f
extern const float        DAT_013eecd8;                      // +0x013eecd8  20.0f

// SP::cGlobalThing reachable through the FUN_00b3d480 getter.
struct cGlobalThing {
    void FUN_00ac8d40(void* p);                               // 0x00ac8d40  (ret 4)
};

cGlobalThing* FUN_00b3d480();                                 // 0x00b3d480  (mov eax,[0x167eb3c]; ret)

// Simulator::cCity — base at +0x000 (cCityPrefix), cSpatialObject at +0x120, then
// the object's own members starting at +0x1f4.  The constructor initialises every
// member below in address order; the named gaps are never touched by this slice.
struct cRefCounted {
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
    virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
    virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
    virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void Release();                                  // vtable +0xc0
};

struct cCity : cCityPrefix, cSpatialObject {
    cCity();                                                  // 0x00be6310
    void  FUN_00be6900(char param2);                          // 0x00be6900
    float FUN_00be6d90();                                     // 0x00be6d90
    void  FUN_00be5180();                                     // 0x00be5180
    void  FUN_00be6f40();                                     // 0x00be6f40
    bool  SetDecoration(void* obj);                           // 0x00bd9660

    cInteractionTarget mInteraction;                          // +0x1f4
    cStr16           mName;                                   // +0x210
    unsigned char    mPad21c[4];                              // +0x21c
    float            mF220;                                   // +0x220
    int              mI224;                                   // +0x224
    int              mI228;                                   // +0x228
    unsigned char    mPad22c[4];                              // +0x22c
    cTimer           mTimer230;                               // +0x230
    cTimer           mTimer250;                               // +0x250
    cTimer           mTimer270;                               // +0x270
    unsigned char    mPad290[8];                              // +0x290
    int              mI298;                                   // +0x298
    int              mI29c;                                   // +0x29c
    unsigned char    mB2a0;                                   // +0x2a0
    unsigned char    mPad2a1[3];                              // +0x2a1
    cPointerVector   mVec2a4;                                 // +0x2a4
    unsigned char    mPad2b0[8];                              // +0x2b0
    cPointerVector   mVec2b8;                                 // +0x2b8
    unsigned char    mPad2c4[8];                              // +0x2c4
    int              mI2cc;                                   // +0x2cc
    int              mI2d0;                                   // +0x2d0
    unsigned char    mPad2d4[12];                             // +0x2d4
    unsigned char    mB2e0[7];                                // +0x2e0..+0x2e6
    unsigned char    mPad2e7[1];                              // +0x2e7
    int              mI2e8;                                   // +0x2e8
    int              mI2ec;                                   // +0x2ec
    int              mI2f0;                                   // +0x2f0
    int              mI2f4;                                   // +0x2f4
    int              mI2f8;                                   // +0x2f8
    unsigned char    mB2fc;                                   // +0x2fc
    unsigned char    mPad2fd[3];                              // +0x2fd
    float            mF300;                                   // +0x300
    float            mF304;                                   // +0x304
    cPointerVector   mVec308;                                 // +0x308  mCivicObjects
    unsigned char    mPad314[12];                             // +0x314
    int              mI320;                                   // +0x320  mpCityHall
    int              mI324;                                   // +0x324  mpCityWalls
    int              mI328;                                   // +0x328  mpCityTerritory
    float            mF32c;                                   // +0x32c
    float            mF330;                                   // +0x330
    float            mF334;                                   // +0x334
    float            mF338;                                   // +0x338  mFrameRate
    unsigned char    mPad33c[4];                              // +0x33c
    cPointerVector   mVec340;                                 // +0x340  mBuildings
    unsigned char    mPad34c[8];                              // +0x34c
    cInlinePtrVector mVec354;                                 // +0x354  mTurrets
    unsigned char    mPad368[4];                              // +0x368
    void*            mInlineBuf36c[32];                       // +0x36c..+0x3eb
    cActionCircle    mAction3ec;                              // +0x3ec  mBuildingsLayout
    cActionCircle    mAction450;                              // +0x450
    cActionCircle    mAction4b4;                              // +0x4b4
    unsigned char    mFlag518;                                // +0x518
    unsigned char    mB519;                                   // +0x519
    unsigned char    mPad51a[14];                             // +0x51a..+0x527
    cElem0cVector    mVec528;                                 // +0x528
    unsigned char    mPad534[8];                              // +0x534
    float            mF53c;                                   // +0x53c
    int              mI540;                                   // +0x540
    int              mI544;                                   // +0x544
    cPointerVector   mVec548;                                 // +0x548
    unsigned char    mPad554[8];                              // +0x554
    cPointerVector   mVec55c;                                 // +0x55c
    unsigned char    mPad568[8];                              // +0x568
    cRbTree          mRb570;                                  // +0x570
    unsigned char    mPad588[4];                              // +0x588
    unsigned char    mB58c;                                   // +0x58c
    unsigned char    mPad58d[3];                              // +0x58d
    cFlagHolder*     mPtr590;                                 // +0x590
    int              mI594;                                   // +0x594
    float            mF598;                                   // +0x598
    int              mI59c;                                   // +0x59c
    cRbTree          mRb5a0;                                  // +0x5a0
    unsigned char    mPad5b8[4];                              // +0x5b8
    cRbTree          mRb5bc;                                  // +0x5bc
    unsigned char    mPad5d4[4];                              // +0x5d4
    cRbTree          mRb5d8;                                  // +0x5d8
    unsigned char    mPad5f0[8];                              // +0x5f0
    cTimer           mTimer5f8;                               // +0x5f8
    cCultureTargetInfoVector mCultureTargetInfo;              // +0x618
    unsigned char    mPad624[8];                              // +0x624
    cPointerVector   mVec62c;                                 // +0x62c
    unsigned char    mPad638[0x10];                           // +0x638..+0x647
    unsigned char    mB648;                                   // +0x648
    unsigned char    mPad649[3];                              // +0x649
    int              mI64c;                                   // +0x64c
    float            mF650;                                   // +0x650
    int              mI654;                                   // +0x654
    int              mI658;                                   // +0x658
    int              mI65c;                                   // +0x65c
    int              mI660;                                   // +0x660
    int              mI664;                                   // +0x664
    int              mI668;                                   // +0x668
    int              mI66c;                                   // +0x66c
    int              mI670;                                   // +0x670
    int              mI674;                                   // +0x674
    int              mI678;                                   // +0x678
    int              mI67c;                                   // +0x67c
    int              mI680;                                   // +0x680
    cPointerVector   mVec684;                                 // +0x684
    unsigned char    mPad690[8];                              // +0x690
    unsigned char    mB698;                                   // +0x698
    unsigned char    mPad699[7];                              // +0x699..+0x69f
    cTimer           mTimer6a0;                               // +0x6a0
    unsigned char    mB6c0;                                   // +0x6c0
    unsigned char    mPad6c1[7];                              // +0x6c1
    cTimer           mTimer6c8;                               // +0x6c8
    cTimer           mTimer6e8;                               // +0x6e8
    cTimer           mTimer708;                               // +0x708
    cTimer           mTimer728;                               // +0x728
    float            mF748;                                   // +0x748
    int              mI74c;                                   // +0x74c
    float            mF750;                                   // +0x750
    int              mI754;                                   // +0x754
    float            mF758;                                   // +0x758
    int              mI75c;                                   // +0x75c
    unsigned char    mB760;                                   // +0x760
    unsigned char    mB761;                                   // +0x761
    unsigned char    mB762;                                   // +0x762
    unsigned char    mPad763[1];                              // +0x763
    int              mI764;                                   // +0x764
    int              mI768;                                   // +0x768
    unsigned char    mPad76c[4];                              // +0x76c
    cTimer           mTimer770;                               // +0x770
    cTimer           mTimer790;                               // +0x790
    unsigned char    mPad7b0[8];                              // +0x7b0
    cRbTree          mRb7b8;                                  // +0x7b8
    unsigned char    mPad7d0[4];                              // +0x7d0
    int              mI7d4;                                   // +0x7d4
    unsigned char    mPad7d8[0x18];                           // +0x7d8..+0x7ef
    int              mI7f0;                                   // +0x7f0
    int              mI7f4;                                   // +0x7f4
    int              mI7f8;                                   // +0x7f8
    int              mI7fc;                                   // +0x7fc
    int              mI800;                                   // +0x800
    unsigned char    mPad804[8];                              // +0x804
    unsigned char    mB80c;                                   // +0x80c
    unsigned char    mPad80d[3];                              // +0x80d
    int              mI810;                                   // +0x810
};

// Score weights read out of .rdata.
extern const float DAT_0169c1e0;                              // +0x0169c1e0  per-building scale
extern const float DAT_01471064;                              // +0x01471064  0.5f
extern const float DAT_013eb1c0;                              // +0x013eb1c0  1.2f
extern const float DAT_01465544;                              // +0x01465544  500.0f
extern const float DAT_01470f1c;                              // +0x01470f1c  2.0f

// @ 0x00be6310
cCity::cCity()
    : cCityPrefix(), cSpatialObject(), mInteraction()
{
    // Seven vtable installs (the listener interface at +0x20c is written twice).
    mInteraction.mpVtbl2 = (void*)0x13eb384;                  // +0x20c  cListenerBase
    mInteraction.mpVtbl  = (void*)0x14686e4;                  // +0x1f4  cCity (interaction)
    mpVtbl0              = (void*)0x14687d8;                  // +0x000
    mpVtbl1              = (void*)0x14687c4;                  // +0x004
    mpVtbl2              = (void*)0x1469cc0;                  // +0x034
    static_cast<cSpatialObject&>(*this).mpVtbl = (void*)0x1468700;  // +0x120
    mInteraction.mpVtbl2 = (void*)0x14686d4;                  // +0x20c  cCity (listener)

    // Empty eastl::string16.
    mName.mpBegin    = (void*)0x1667bac;                      // +0x210
    mName.mpEnd      = (void*)0x1667bac;                      // +0x214
    mName.mpCapacity = (void*)0x1667bae;                      // +0x218

    mF220 = 0.0f;                                             // +0x220
    mI224 = 0;                                                // +0x224
    mI228 = 0;                                                // +0x228
    mTimer230.Construct();                                    // +0x230
    mTimer250.Construct();                                    // +0x250
    mTimer270.Construct();                                    // +0x270

    mI298 = 0;                                                // +0x298
    mB2a0 = 0;                                                // +0x2a0
    mI29c = -1;                                               // +0x29c
    mVec2a4.mpBegin = 0; mVec2a4.mpEnd = 0; mVec2a4.mpCapacity = 0;   // +0x2a4
    mVec2b8.mpBegin = 0; mVec2b8.mpEnd = 0; mVec2b8.mpCapacity = 0;   // +0x2b8
    mF300 = 0.0f;                                             // +0x300
    mF304 = DAT_013f1cac;                                     // +0x304  50.0f
    mI2cc = 0;                                                // +0x2cc
    mI2d0 = 0;                                                // +0x2d0
    mB2e0[0] = 0; mB2e0[1] = 0; mB2e0[2] = 0; mB2e0[3] = 0;   // +0x2e0
    mB2e0[4] = 0; mB2e0[5] = 0; mB2e0[6] = 0;
    mI2e8 = 0;                                                // +0x2e8
    mI2ec = 0;                                                // +0x2ec
    mI2f0 = 0;                                                // +0x2f0
    mI2f4 = 0;                                                // +0x2f4
    mI2f8 = 0;                                                // +0x2f8
    mB2fc = 0;                                                // +0x2fc
    mVec308.mpBegin = 0; mVec308.mpEnd = 0; mVec308.mpCapacity = 0;   // +0x308
    mI320 = 0;                                                // +0x320  mpCityHall
    mI324 = 0;                                                // +0x324  mpCityWalls
    mI328 = 0;                                                // +0x328  mpCityTerritory
    mF32c = DAT_0168bd70;                                     // +0x32c
    mF330 = DAT_0168bd74;                                     // +0x330
    mF334 = DAT_0168bd78;                                     // +0x334
    mF338 = DAT_01473c70;                                     // +0x338  10.0f
    mVec340.mpBegin = 0; mVec340.mpEnd = 0; mVec340.mpCapacity = 0;   // +0x340

    // 32-slot inline turret vector; the buffer sits at +0x36c and its end is the
    // address of mAction3ec.
    mVec354.mpBegin    = mInlineBuf36c;                       // +0x354
    mVec354.mpEnd      = mInlineBuf36c;                       // +0x358
    mVec354.mpCapacity = mInlineBuf36c + 32;                  // +0x35c
    mVec354.mpBuffer   = mInlineBuf36c;                       // +0x364

    mAction3ec.LayoutConstruct();                             // +0x3ec
    mAction450.LayoutConstruct();                             // +0x450
    mAction4b4.LayoutConstruct();                             // +0x4b4

    mFlag518 = 1;                                             // +0x518
    mB519 = 0;                                                // +0x519
    mVec528.mpBegin = 0; mVec528.mpEnd = 0; mVec528.mpCapacity = 0;   // +0x528
    mI540 = -1;                                               // +0x540
    mF53c = 0.0f;                                             // +0x53c
    mVec548.mpBegin = 0; mVec548.mpEnd = 0; mVec548.mpCapacity = 0;   // +0x548
    mVec55c.mpBegin = 0; mVec55c.mpEnd = 0; mVec55c.mpCapacity = 0;   // +0x55c

    // Red-black tree at +0x570 (anchor at +0x574).
    mRb570.mpNodeRight  = 0;
    mRb570.mpNodeParent = 0;
    mRb570.mColorWord   = 0;
    mRb570.mpNodeParent = 0;
    mRb570.mColor       = 0;
    mRb570.mnSize       = 0;
    mRb570.mpNodeLeft   = &mRb570.mpNodeLeft;
    mRb570.mpNodeRight  = &mRb570.mpNodeLeft;

    mB58c = 0;                                                // +0x58c
    mPtr590 = 0;                                              // +0x590
    mI594 = 0x2d;                                             // +0x594
    mF598 = DAT_013eecd8;                                     // +0x598  20.0f
    mI59c = 0;                                                // +0x59c

    // Red-black tree at +0x5a0.
    mRb5a0.mpNodeRight  = 0;
    mRb5a0.mpNodeParent = 0;
    mRb5a0.mColorWord   = 0;
    mRb5a0.mpNodeParent = 0;
    mRb5a0.mColor       = 0;
    mRb5a0.mnSize       = 0;
    mRb5a0.mpNodeLeft   = &mRb5a0.mpNodeLeft;
    mRb5a0.mpNodeRight  = &mRb5a0.mpNodeLeft;

    // Red-black tree at +0x5bc (anchor at +0x5c0).
    mRb5bc.mpNodeRight  = 0;
    mRb5bc.mpNodeParent = 0;
    mRb5bc.mColorWord   = 0;
    mRb5bc.mpNodeLeft   = &mRb5bc.mpNodeLeft;
    mRb5bc.mpNodeRight  = &mRb5bc.mpNodeLeft;
    mRb5bc.mpNodeParent = 0;
    mRb5bc.mColor       = 0;
    mRb5bc.mnSize       = 0;

    // Red-black tree at +0x5d8.
    mRb5d8.mpNodeRight  = 0;
    mRb5d8.mpNodeParent = 0;
    mRb5d8.mColorWord   = 0;
    mRb5d8.mpNodeLeft   = &mRb5d8.mpNodeLeft;
    mRb5d8.mpNodeRight  = &mRb5d8.mpNodeLeft;
    mRb5d8.mpNodeParent = 0;
    mRb5d8.mColor       = 0;
    mRb5d8.mnSize       = 0;

    mTimer5f8.Construct();                                    // +0x5f8

    mCultureTargetInfo.mpBegin = 0; mCultureTargetInfo.mpEnd = 0;
    mCultureTargetInfo.mpCapacity = 0;                        // +0x618
    mVec62c.mpBegin = 0; mVec62c.mpEnd = 0; mVec62c.mpCapacity = 0;   // +0x62c
    mI64c = 0;                                                // +0x64c
    mF650 = 0.0f;                                             // +0x650
    mI654 = 0;                                                // +0x654
    mI658 = 0;                                                // +0x658
    mI65c = 0;                                                // +0x65c
    mI660 = 0;                                                // +0x660
    mI664 = 0;                                                // +0x664
    mI668 = 0;                                                // +0x668
    mI66c = 0;                                                // +0x66c
    mI670 = 0;                                                // +0x670
    mI674 = 0;                                                // +0x674
    mI678 = 0;                                                // +0x678
    mI67c = 0;                                                // +0x67c
    mI680 = 0;                                                // +0x680
    mVec684.mpBegin = 0; mVec684.mpEnd = 0; mVec684.mpCapacity = 0;   // +0x684
    mB698 = 0;                                                // +0x698
    mTimer6a0.Construct();                                    // +0x6a0
    mB6c0 = 0;                                                // +0x6c0
    mTimer6c8.Construct();                                    // +0x6c8
    mTimer6e8.Construct();                                    // +0x6e8
    mTimer708.Construct();                                    // +0x708
    mTimer728.Construct();                                    // +0x728

    mF748 = 0.0f; mI74c = -1;                                 // +0x748
    mF750 = 0.0f; mI754 = -1;                                 // +0x750
    mF758 = 0.0f; mI75c = -1;                                 // +0x758
    mB760 = 0;                                                // +0x760
    mB761 = 0;                                                // +0x761
    mB762 = 0;                                                // +0x762
    mI764 = 0;                                                // +0x764
    mI768 = 0;                                                // +0x768
    mTimer770.Construct();                                    // +0x770
    mTimer790.Construct();                                    // +0x790

    // Red-black tree at +0x7b8 (anchor at +0x7bc).
    mRb7b8.mpNodeRight  = 0;
    mRb7b8.mpNodeParent = 0;
    mRb7b8.mColorWord   = 0;
    mRb7b8.mpNodeLeft   = &mRb7b8.mpNodeLeft;
    mRb7b8.mpNodeRight  = &mRb7b8.mpNodeLeft;
    mRb7b8.mpNodeParent = 0;
    mRb7b8.mColor       = 0;
    mRb7b8.mnSize       = 0;

    mI7d4 = 0;                                                // +0x7d4
    mI7f0 = 0;                                                // +0x7f0
    mI7f8 = 0;                                                // +0x7f8
    mI7fc = 0;                                                // +0x7fc
    mI800 = 0;                                                // +0x800
    mB80c = 0;                                                // +0x80c

    mI810 = 0;                                                // +0x810
    mI544 = (int)g_1601760.RandomUint32Uniform(3);            // +0x544  random specialty

    mTimer5f8.Start();
    mTimer6a0.Start();
    mTimer6c8.Start();
    mTimer6e8.Start();
    mTimer708.Start();
    mTimer728.Start();

    mCultureTargetInfo.Resize(4);                             // 0x00be60a0

    // Initialise the four 0x80-byte culture-target records.
    for (int i = 0; i < 4; ++i) {
        cCultureTargetInfo* t = mCultureTargetInfo.mpBegin + i;
        for (int k = 0; k < 8; ++k)
            t->mPtr00[k] = 0;
        t->mFlag20 = 0;
        t->mF24 = 0.0f;
        t->mF28 = 0.0f;
        t->mF2c = 0.0f;
        if (t->mPtr70 != 0) {
            cRefCounted* p = t->mPtr70;
            t->mPtr70 = 0;
            p->Release();
        }
        t->mFlag74 = 0;
        if (t->mPtr78 != 0) {
            cRefCounted* p = t->mPtr78;
            t->mPtr78 = 0;
            p->Release();
        }
    }

    mB648 = 0;                                                // +0x648
    mI7f4 = (int)g_1601760.RandomUint32Uniform(3);            // +0x7f4
}

// @ 0x00be6900
void cCity::FUN_00be6900(char param2)
{
    int count = g_15fd918->GetIntProperty(0x6414d84);
    for (int a0 = 0; a0 < 0x24; a0 += 0xc) {
        for (int i = count; i > 0; --i) {
            // Create the decoration noun and cast it to the ornament interface.
            cGameNounManager* mgr = NounManager();
            cNoun* noun = mgr->CreateNoun((void*)0x18c88e4);
            cNoun* orn = noun ? noun->Cast(0x175cdc9) : 0;

            // Pick the style model for this turret row and apply it.
            void* elem = *(void**)((char*)mVec528.mpBegin + a0);
            void* style = ((cCityVtbl*)this)->Vfn4c(elem);
            ((cSimOrnament*)orn)->SetStyleModel((void*)0x2ae5ba7, style);

            // Reset the ornament's transform sub-object.
            orn->mSub70.SetScale(1.0f);
            orn->mSub70.FUN_00c88530(1.0f);

            // Insert into mCivicObjects (SPVector<AutoRefCount>): the temporary holds
            // one reference, the vector element another; the temporary is then dropped.
            void* tmp = orn;
            if (orn != 0)
                orn->AddRef();
            if (mVec308.mpEnd < mVec308.mpCapacity) {
                void** slot = mVec308.mpEnd;
                mVec308.mpEnd = slot + 1;
                if (slot != 0) {
                    *slot = orn;
                    if (orn != 0)
                        orn->AddRef();
                }
            } else {
                mVec308.DoInsertPtr(mVec308.mpEnd, tmp);
            }
            if (tmp != 0)
                orn->Release();

            mAction450.RemoveAgent(orn);                      // +0x450
            if (mFlag518 != 0)
                FUN_00be5180();
            SetDecoration(orn);

            if (param2 != 0) {
                cEffect* effect = 0;
                cEffectsManager* effects = EffectsManager();
                if (effect != 0) {
                    effect->Release();
                    effect = 0;
                }
                if (effects->SpawnEffect(0xaec03934, 0, &effect)) {
                    cEffectDesc desc;
                    desc.mF04 = DAT_0168c354;
                    desc.mF08 = DAT_0168c358;
                    desc.mF0c = DAT_0168c35c;
                    desc.mF10 = 1.0f;

                    Mat3 base;
                    base.m[0] = DAT_0168c330;
                    base.m[1] = DAT_0168c334;
                    base.m[2] = DAT_0168c338;
                    base.m[3] = DAT_0168c33c;
                    base.m[4] = DAT_0168c340;
                    base.m[5] = DAT_0168c344;
                    base.m[6] = DAT_0168c348;
                    base.m[7] = DAT_0168c34c;
                    base.m[8] = DAT_0168c350;
                    desc.mFlags = 0;
                    desc.mCount = 0;
                    desc.mMatrix = base;

                    // Position from the ornament transform.
                    float* pos = orn->mSub70.GetPosition();
                    desc.mF04 = pos[0];
                    desc.mF08 = pos[1];
                    desc.mF0c = pos[2];
                    desc.mFlags |= 4;
                    desc.mCount = (short)(desc.mCount + 1);

                    // Orientation quaternion -> rotation matrix.
                    float* q = orn->mSub70.GetOrientation();
                    float x = q[0];
                    float y = q[1];
                    float z = q[2];
                    float w = q[3];
                    Mat3 rot;
                    rot.m[0] = 1.0f - (z * z + y * y) * 2.0f;
                    rot.m[1] = (w * z + y * x) * 2.0f;
                    rot.m[2] = (z * x - w * y) * 2.0f;
                    rot.m[3] = (y * x - w * z) * 2.0f;
                    rot.m[4] = 1.0f - (z * z + x * x) * 2.0f;
                    rot.m[5] = (w * x + z * y) * 2.0f;
                    rot.m[6] = (w * y + z * x) * 2.0f;
                    rot.m[7] = (z * y - w * x) * 2.0f;
                    rot.m[8] = 1.0f - (y * y + x * x) * 2.0f;
                    desc.mMatrix = rot;
                    desc.mFlags |= 2;
                    desc.mCount = (short)(desc.mCount + 1);

                    effect->SetDescriptor(&desc);             // vtable +0x18
                    effect->SetVisible(0);                    // vtable +0x08
                }
                if (effect != 0)
                    effect->Release();
            }
        }
    }
}

// @ 0x00be6d90
float cCity::FUN_00be6d90()
{
    float scale = (float)mVec308.Size() * DAT_0169c1e0;

    void* buf[32];
    cInlinePtrVector buildings;
    buildings.mpBegin    = buf;
    buildings.mpEnd      = buf;
    buildings.mpCapacity = buf + 32;
    buildings.mpBuffer   = buf;
    if (&buildings != &mVec354) {
        buildings.Reset(buf, buf);
        buildings.Append(mVec354.mpBegin, mVec354.mpEnd, scale);
    }

    float buildingScore = 0.0f;
    for (void** it = buildings.mpBegin; it != buildings.mpEnd; ++it) {
        cBuildingScore* b = (cBuildingScore*)*it;
        if (b->mCombatant588.GetDamageState() != 2)
            buildingScore = buildingScore + b->Score() * DAT_01471064;
    }

    float raidScore = 0.0f;
    for (void** it = mVec340.mpBegin; it != mVec340.mpEnd; ++it) {
        cRaidParticipant* r = (cRaidParticipant*)*it;
        if (r->mCombatant120.GetDamageState() != 2)
            raidScore = raidScore + r->GetWeight() * DAT_013eb1c0;
    }

    float result = raidScore + buildingScore + scale + DAT_01465544;
    if (mPtr590->mFlag8a == 0)
        result = result * DAT_01470f1c;

    // Release the local building list and hand its buffer back (the original does this with
    // explicit code rather than a class destructor, so the function needs no unwind frame).
    for (void** it = buildings.mpBegin; it != buildings.mpEnd; ++it) {
        cBuildingScore* b = (cBuildingScore*)*it;
        if (b != 0)
            b->Release();
    }
    if (buildings.mpBegin != 0 && buildings.mpBegin != buildings.mpEnd)
        EASTL_allocator_deallocate(buildings.mpBegin);

    return result;
}

// @ 0x00be6f40
void cCity::FUN_00be6f40()
{
    FUN_00be5180();
    mFlag518 = 1;
}

// @ 0x00be6f60
void cSpatialObject::FUN_00be6f60()
{
    cSpatialObject_func80h();
    // The cSpatialObject sub-object sits at cCity + 0x120; the owning cCity is reached by
    // rebinding the base pointer.  Written explicitly because MSVC's implicit base-to-derived
    // conversion (static_cast) would insert a redundant null guard the original does not have.
    cCity* city = (cCity*)((unsigned char*)this - 0x120);
    city->FUN_00be5180();
    FUN_00b3d480()->FUN_00ac8d40(city);
}