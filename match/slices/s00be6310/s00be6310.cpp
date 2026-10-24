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
// the local scratch vector inside cCity::FUN_00be6d90).
struct cInlinePtrVector {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    void** mpBuffer;                                         // +0x0c
    void Reset(void** first, void** last);                   // 0x00e25bd0  eastl::vector::erase
    void Append(void** first, void** last, float f);         // 0x00bdf600
};

// Opaque 0x64-byte SP::cActionCircle sub-objects at cCity + 0x3ec / +0x450 / +0x4b4.
struct cActionCircle {
    unsigned char mRaw000[0x64];
    void RemoveAgent(void* agent);                           // 0x00afae50
};

// SP::cSpatialObject sub-object, located at cCity + 0x120 by the constructor
// (which runs SP::cSpatialObject::cSpatialObject on that address).
struct cSpatialObject {
    unsigned char mRaw000[0xd4];
    void cSpatialObject_func80h();                           // 0x00c88510
    void FUN_00be6f60();                                     // 0x00be6f60
};

// Leading 0x120 bytes of Simulator::cCity (the primary base sub-object built by
// FUN_00c011c0); kept opaque because its sub-object graph is not used here.
struct cCityPrefix {
    unsigned char mRaw000[0x120];
};

// SP::cGlobalThing reachable through the FUN_00b3d480 getter.
struct cGlobalThing {
    void FUN_00ac8d40(void* p);                               // 0x00ac8d40  (ret 4)
};

cGlobalThing* FUN_00b3d480();                                 // 0x00b3d480  (mov eax,[0x167eb3c]; ret)

// Simulator::cCity — base at +0x000 (cCityPrefix), cSpatialObject at +0x120, then
// the object's own members starting at +0x1f4.
struct cCity : cCityPrefix, cSpatialObject {
    cCity();                                                  // 0x00be6310
    void  FUN_00be6900(char param2);                          // 0x00be6900
    float FUN_00be6d90();                                     // 0x00be6d90
    void  FUN_00be5180();                                     // 0x00be5180
    void  FUN_00be6f40();                                     // 0x00be6f40

    unsigned char mRaw1f4[0x308 - 0x1f4];                     // +0x1f4
    cPointerVector   mVec308;                                 // +0x308
    unsigned char    mRaw314[0x340 - 0x314];                  // +0x314
    cPointerVector   mVec340;                                 // +0x340
    unsigned char    mRaw34c[0x354 - 0x34c];                  // +0x34c
    cInlinePtrVector mVec354;                                 // +0x354
    unsigned char    mRaw364[0x450 - 0x364];                  // +0x364
    cActionCircle    mAction450;                              // +0x450
    unsigned char    mRaw4b4[0x518 - 0x4b4];                  // +0x4b4
    unsigned char    mFlag518;                                // +0x518
    unsigned char    mRaw519[0x528 - 0x519];                  // +0x519
    cElem0cVector    mVec528;                                 // +0x528
    unsigned char    mRaw534[0x590 - 0x534];                  // +0x534
    cFlagHolder*     mPtr590;                                 // +0x590
};

// Score weights read out of .rdata.
extern const float DAT_0169c1e0;                              // +0x0169c1e0  per-building scale
extern const float DAT_01471064;                              // +0x01471064  0.5f
extern const float DAT_013eb1c0;                              // +0x013eb1c0  1.2f
extern const float DAT_01465544;                              // +0x01465544  500.0f
extern const float DAT_01470f1c;                              // +0x01470f1c  2.0f

// @ 0x00be6310
cCity::cCity()
{
}

// @ 0x00be6900
void cCity::FUN_00be6900(char)
{
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