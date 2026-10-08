// Slice s00bda190 (batch hk2 slice 2).  One function: 00bdab60, 156 bytes, __thiscall, no args.
// Simulator::cCulturalTarget constructor.  Constructs three base subobjects (cGameData at
// +0, cCombatant at +0x38, cSpatialObject at +0x100), then sets this object's vtables,
// and the initial state of its own fields.  Returns this.  32-bit MSVC 2008 SP1,
// /O2 /MD /Gy /EHsc /TP /arch:SSE.

namespace SP {

class cGameData {                // base at +0, size 4 here (only the vptr is seen by this ctor)
public:
    cGameData();
    virtual void GameDataSlot0();
};

class cSecondaryBase {           // base at +4 (own vptr), size 0x34 so cCombatant lands at +0x38
public:
    virtual void SecondarySlot0();
    char pad0[0x30];
};

class cCombatant {               // base at +0x38, size 0xc8
public:
    cCombatant();
    virtual void CombatantSlot0();
    char pad0[0xc8 - 4];
};

class cSpatialObject {           // base at +0x100, size 0x88
public:
    cSpatialObject();
    virtual void SpatialSlot0();
    char pad0[0x88 - 4];
};

class cCulturalTarget : public cGameData, public cSecondaryBase, public cCombatant, public cSpatialObject {
public:
    cCulturalTarget();
    virtual void CulturalSlot0();
    char pad0[0x1d4 - 0x188];
    unsigned char mGateIndex;            // +0x1d4
    unsigned int  mAttackState;          // +0x1d8
    unsigned int  mAttackerPoliticalID;  // +0x1dc
    unsigned int* mAttackOrdersBegin;    // +0x1e0 (eastl::vector<unsigned int>)
    unsigned int* mAttackOrdersEnd;
    unsigned int* mAttackOrdersCap;
    char pad1[0x1f4 - 0x1ec];
    void**        mAttackersBegin;       // +0x1f4 (eastl::vector<AutoRefCount<cVehicle>>)
    void**        mAttackersEnd;
    void**        mAttackersCap;
    char pad2[0x208 - 0x200];
    void*         mpHitSphere;           // +0x208 (AutoRefCount<cHitSphere>)
    float         mLastDancingCrowdFraction;   // +0x20c
    float         mLastAngryCrowdFraction;     // +0x210
    int           mAngerLevel;                 // +0x214
};

// 00bdab60 SP::cCulturalTarget::cCulturalTarget
cCulturalTarget::cCulturalTarget() {
    mAttackState = 0;
    mGateIndex = 0xff;
    mAttackerPoliticalID = 0xffffffff;
    mAttackOrdersBegin = 0;
    mAttackOrdersEnd = 0;
    mAttackOrdersCap = 0;
    mAttackersBegin = 0;
    mAttackersEnd = 0;
    mAttackersCap = 0;
    mpHitSphere = 0;
    mAngerLevel = 0;
    mLastDancingCrowdFraction = 0.0f;
    mLastAngryCrowdFraction = 0.0f;
}

}  // namespace SP
