// SP::cUFOKinestheticsTuning::ReadProps  @ 0x00C38D00
// Reads every tuning property from the resource's property list.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

struct Property {
  char pad[0x12];
  unsigned short mType;  // +0x12
  float* GetFloat();     // 0x0041EA70
  bool* GetBool();       // 0x0041E920
};

class cPropertyList {
 public:
  virtual void v000();
  virtual void v004();
  virtual void v008();
  virtual void v00c();
  virtual void v010();
  virtual void v014();
  virtual void v018();
  virtual void v01c();
  virtual void v020();
  virtual bool GetProperty(uint32_t id, Property*& result);  // +0x24
};

template <class T>
struct AutoRefCount {
  T* mpObject;
};

struct IHandler {
  virtual void v000();
};

// Layout confirmed against the disassembly: every field from +0x8 to +0x1A4 is a
// 4-byte float except mSolarAcceleration (+0xFC) and m2PlumpDistance (+0x184).
class cUFOKinestheticsTuning : public IHandler {
 public:
  AutoRefCount<cPropertyList> mPropList;  // +0x04

  float mHitTerrainDamage;                  // +0x08
  float mMinAltitude;                       // +0x0C
  float mMaxAltitude;                       // +0x10
  float mDamageToDestScale;                 // +0x14
  float mDamageToVelocityScale;             // +0x18
  float mHitSphereRadius;                   // +0x1C
  float mHitSphereActiveDistance;           // +0x20
  float mMinExtent;                         // +0x24
  float mBomberScale;                       // +0x28
  float mFighterScale;                      // +0x2C
  float mUberTurretScale;                   // +0x30
  float mAllyScale;                         // +0x34
  float mPlumpDistance;                     // +0x38
  float mPlumpScale;                        // +0x3C
  float mPlumpTransitionScale;              // +0x40
  float mNPCPlumpScale;                     // +0x44
  float mBasePlanetScale;                   // +0x48
  float mVelocityFactor;                    // +0x4C
  float mVelocityFactorNPC;                 // +0x50
  float mFighterVelocityFactor;             // +0x54
  float mUberTurretVelocityFactor;          // +0x58
  float mAllyVelocityFactor;                // +0x5C
  float mKeyboardMovementSpeedZoomedOut;    // +0x60
  float mKeyboardMovementSpeedZoomedIn;     // +0x64
  float mKeyboardAccelerationZoomedOut;     // +0x68
  float mKeyboardAccelerationZoomedIn;      // +0x6C
  float mBomberVelocityFactor;              // +0x70
  float mVelocityFactorZoomedOut;           // +0x74
  float mMouseMovementSpeedZoomedOut;       // +0x78
  float mMouseMovementSpeedZoomedIn;        // +0x7C
  float mMouseRotationSpeedZoomedOut;       // +0x80
  float mMouseRotationSpeedZoomedIn;        // +0x84
  float mLeavePlanetTimePad;                // +0x88
  float mMaxRotation;                       // +0x8C
  float mTargetFallOffRadius;               // +0x90
  float mBrakeFactor;                       // +0x94
  float mBrakeOvershootFactor;              // +0x98
  float mAccelerationFactor;                // +0x9C
  float mAccelerationFactorNPC;             // +0xA0
  float mVerticalAcclerationDown;           // +0xA4
  float mVerticalAcclerationUp;             // +0xA8
  float mCollisionElasticity;               // +0xAC
  float mCollisionRestitution;              // +0xB0
  float mRotationPercentageRate;            // +0xB4
  float mNoseTiltFactor;                    // +0xB8
  float mNoseTiltRate;                      // +0xBC
  float mMaxNoseTilt;                       // +0xC0
  float mVerticalTiltFactor;                // +0xC4
  float mMaxVerticalTilt;                   // +0xC8
  float mBankTiltFactor;                    // +0xCC
  float mBankTiltRate;                      // +0xD0
  float mMaxBankTilt;                       // +0xD4
  float mEscapeSequenceSpinRate;            // +0xD8
  float mEscapeSequenceVelocity;            // +0xDC
  float mTrailEffectAlwaysOn;               // +0xE0
  float mEffectMaxSpeedPlanet;              // +0xE4
  float mEffectMaxSpeedSolar;               // +0xE8
  float mEffectMaxSpeedGalaxy;              // +0xEC
  float mTrailEffectMinSize;                // +0xF0
  float mMaxAltitudeDestinationDelta;       // +0xF4
  float mSolarSpeed;                        // +0xF8
  bool mSolarAcceleration;                  // +0xFC
  char pad_fd[3];
  float mGalaxySpeed;                       // +0x100
  float mGalaxyAcceleration;                // +0x104
  float mSolarMinPlump;                     // +0x108
  float mSolarMaxPlump;                     // +0x10C
  float mGalaxyMinPlump;                    // +0x110
  float mGalaxyMaxPlump;                    // +0x114
  float mGalaxyMinPlumpDistance;            // +0x118
  float mGalaxyMaxPlumpDistance;            // +0x11C
  float mBaseUFODamagePush;                 // +0x120
  float mMaxUFODamagePush;                  // +0x124
  float mUFODamageVelocityDecayRate;        // +0x128
  float mAltMaxAltitude;                    // +0x12C
  float mAltPlumpDistance;                  // +0x130
  float mAltVelocityFactorZoomedOut;        // +0x134
  float mExtra138;                          // +0x138
  float mExtra13c;                          // +0x13C
  float mExtra140;                          // +0x140
  float mExtra144;                          // +0x144
  float mExtra148;                          // +0x148
  float mExtra14c;                          // +0x14C
  float mExtra150;                          // +0x150
  float m2HitTerrainDamage;                 // +0x154
  float m2MinAltitude;                      // +0x158
  float m2MaxAltitude;                      // +0x15C
  float m2DamageToDestScale;                // +0x160
  float m2DamageToVelocityScale;            // +0x164
  float m2HitSphereRadius;                  // +0x168
  float m2HitSphereActiveDistance;          // +0x16C
  float m2MinExtent;                        // +0x170
  float m2BomberScale;                      // +0x174
  float m2FighterScale;                     // +0x178
  float m2UberTurretScale;                  // +0x17C
  float m2AllyScale;                        // +0x180
  bool m2PlumpDistance;                     // +0x184
  char pad_185[3];
  float m2PlumpScale;                       // +0x188
  float m2PlumpTransitionScale;             // +0x18C
  float m2NPCPlumpScale;                    // +0x190
  float m2BasePlanetScale;                  // +0x194
  float m2VelocityFactor;                   // +0x198
  float m2VelocityFactorNPC;                // +0x19C
  float m2FighterVelocityFactor;            // +0x1A0
  float m2UberTurretVelocityFactor;         // +0x1A4

  void ReadProps();
};

inline void GetFloatProp(cPropertyList* list, uint32_t id, float& out) {
  Property* p;
  if (list && list->GetProperty(id, p) && p->mType == 0xd) out = *p->GetFloat();
}

inline void GetBoolProp(cPropertyList* list, uint32_t id, bool& out) {
  Property* p;
  if (list && list->GetProperty(id, p) && p->mType == 1) out = *p->GetBool();
}

// @ 0x00C38D00
void cUFOKinestheticsTuning::ReadProps() {
  GetFloatProp(mPropList.mpObject, 0x4496ebe, mHitTerrainDamage);
  GetFloatProp(mPropList.mpObject, 0x195d000, mMinAltitude);
  GetFloatProp(mPropList.mpObject, 0x195d002, mMaxAltitude);
  GetFloatProp(mPropList.mpObject, 0x195d037, mDamageToDestScale);
  GetFloatProp(mPropList.mpObject, 0x195d038, mDamageToVelocityScale);
  GetFloatProp(mPropList.mpObject, 0x331e543, mHitSphereRadius);
  GetFloatProp(mPropList.mpObject, 0x6ba86fb, mHitSphereActiveDistance);
  GetFloatProp(mPropList.mpObject, 0x331e8cf, mMinExtent);
  GetFloatProp(mPropList.mpObject, 0x33c591d, mBomberScale);
  GetFloatProp(mPropList.mpObject, 0x609ee15, mFighterScale);
  GetFloatProp(mPropList.mpObject, 0x338d246, mUberTurretScale);
  GetFloatProp(mPropList.mpObject, 0x338d24d, mAllyScale);
  GetFloatProp(mPropList.mpObject, 0x4ea4823, mPlumpDistance);
  GetFloatProp(mPropList.mpObject, 0x5b56b19, mPlumpScale);
  GetFloatProp(mPropList.mpObject, 0x5ecb58d, mPlumpTransitionScale);
  GetFloatProp(mPropList.mpObject, 0x5ecb592, mNPCPlumpScale);
  GetFloatProp(mPropList.mpObject, 0x5ecb596, mBasePlanetScale);
  GetFloatProp(mPropList.mpObject, 0x5ecb59b, mVelocityFactor);
  GetFloatProp(mPropList.mpObject, 0x5ecb5a0, mVelocityFactorNPC);
  GetFloatProp(mPropList.mpObject, 0x2faa5db, mFighterVelocityFactor);
  GetFloatProp(mPropList.mpObject, 0x2faa5d7, mUberTurretVelocityFactor);
  GetFloatProp(mPropList.mpObject, 0x49b3d7e, mAllyVelocityFactor);
  GetFloatProp(mPropList.mpObject, 0x435b5a7, mKeyboardMovementSpeedZoomedOut);
  GetFloatProp(mPropList.mpObject, 0x303bef4, mKeyboardMovementSpeedZoomedIn);
  GetFloatProp(mPropList.mpObject, 0x195d010, mKeyboardAccelerationZoomedOut);
  GetFloatProp(mPropList.mpObject, 0x339b758, mKeyboardAccelerationZoomedIn);
  GetFloatProp(mPropList.mpObject, 0x2fa986a, mBomberVelocityFactor);
  GetFloatProp(mPropList.mpObject, 0x4ea6acf, mVelocityFactorZoomedOut);
  GetFloatProp(mPropList.mpObject, 0x5b694ba, mMouseMovementSpeedZoomedOut);
  GetFloatProp(mPropList.mpObject, 0x339b716, mMaxRotation);
  GetFloatProp(mPropList.mpObject, 0x4867421, mTargetFallOffRadius);
  GetFloatProp(mPropList.mpObject, 0x195d014, mBrakeFactor);
  GetFloatProp(mPropList.mpObject, 0x195d015, mBrakeOvershootFactor);
  GetFloatProp(mPropList.mpObject, 0x3309693, mAccelerationFactor);
  GetFloatProp(mPropList.mpObject, 0x3309697, mAccelerationFactorNPC);
  GetFloatProp(mPropList.mpObject, 0x344436f, mVerticalAcclerationDown);
  GetFloatProp(mPropList.mpObject, 0x3309d37, mVerticalAcclerationUp);
  GetFloatProp(mPropList.mpObject, 0x195d012, mMouseMovementSpeedZoomedIn);
  GetFloatProp(mPropList.mpObject, 0x195d013, mMouseRotationSpeedZoomedOut);
  GetFloatProp(mPropList.mpObject, 0x32f7c0a, mMouseRotationSpeedZoomedIn);
  GetFloatProp(mPropList.mpObject, 0x32f7c06, mLeavePlanetTimePad);
  GetFloatProp(mPropList.mpObject, 0x3066aa0, mCollisionElasticity);
  GetFloatProp(mPropList.mpObject, 0x3308805, mCollisionRestitution);
  GetFloatProp(mPropList.mpObject, 0x195d011, mRotationPercentageRate);
  GetFloatProp(mPropList.mpObject, 0x2fa986f, mNoseTiltFactor);
  GetFloatProp(mPropList.mpObject, 0x195d03a, mNoseTiltRate);
  GetFloatProp(mPropList.mpObject, 0x195d039, mMaxNoseTilt);
  GetFloatProp(mPropList.mpObject, 0x681b1aa, mVerticalTiltFactor);
  GetFloatProp(mPropList.mpObject, 0x4f639fc, mMaxVerticalTilt);
  GetFloatProp(mPropList.mpObject, 0x195d03b, mBankTiltFactor);
  GetFloatProp(mPropList.mpObject, 0x330d208, mBankTiltRate);
  GetFloatProp(mPropList.mpObject, 0x3337396, mMaxBankTilt);
  GetFloatProp(mPropList.mpObject, 0x33375f6, mEscapeSequenceSpinRate);
  GetFloatProp(mPropList.mpObject, 0x33373a9, mEscapeSequenceVelocity);
  GetFloatProp(mPropList.mpObject, 0x4ea5863, mTrailEffectAlwaysOn);
  GetFloatProp(mPropList.mpObject, 0x4e6a105, mEffectMaxSpeedPlanet);
  GetFloatProp(mPropList.mpObject, 0x33b1de9, mEffectMaxSpeedSolar);
  GetFloatProp(mPropList.mpObject, 0x33b1df1, mEffectMaxSpeedGalaxy);
  GetFloatProp(mPropList.mpObject, 0x33b1dec, mTrailEffectMinSize);
  GetFloatProp(mPropList.mpObject, 0x31f7670, mMaxAltitudeDestinationDelta);
  GetFloatProp(mPropList.mpObject, 0x31f7668, mSolarSpeed);
  GetBoolProp(mPropList.mpObject, 0x195d03c, mSolarAcceleration);
  GetFloatProp(mPropList.mpObject, 0x195d03e, mGalaxySpeed);
  GetFloatProp(mPropList.mpObject, 0x195d03f, mGalaxyAcceleration);
  GetFloatProp(mPropList.mpObject, 0x195d040, mSolarMinPlump);
  GetFloatProp(mPropList.mpObject, 0x195d03d, mSolarMaxPlump);
  GetFloatProp(mPropList.mpObject, 0x37d5830, mGalaxyMinPlump);
  GetFloatProp(mPropList.mpObject, 0x4a06d7b, mGalaxyMaxPlump);
  GetFloatProp(mPropList.mpObject, 0x4a06d84, mGalaxyMinPlumpDistance);
  GetFloatProp(mPropList.mpObject, 0x4a06d8b, mGalaxyMaxPlumpDistance);
  GetFloatProp(mPropList.mpObject, 0x4a06d94, mBaseUFODamagePush);
  GetFloatProp(mPropList.mpObject, 0x4d7dbe9, mMaxUFODamagePush);
  GetFloatProp(mPropList.mpObject, 0x4d7dbea, mUFODamageVelocityDecayRate);
  GetFloatProp(mPropList.mpObject, 0x66cf309, mAltMaxAltitude);
  GetFloatProp(mPropList.mpObject, 0x66cf318, mAltPlumpDistance);
  GetFloatProp(mPropList.mpObject, 0x66d06a5, mAltVelocityFactorZoomedOut);
  GetFloatProp(mPropList.mpObject, 0x66d06a9, mExtra138);
  GetFloatProp(mPropList.mpObject, 0x66d06c0, mExtra13c);
  GetFloatProp(mPropList.mpObject, 0x66d0769, mExtra140);
  GetFloatProp(mPropList.mpObject, 0x66d0883, m2MaxAltitude);
  GetFloatProp(mPropList.mpObject, 0x66d0885, m2DamageToDestScale);
  GetFloatProp(mPropList.mpObject, 0x66d0888, m2DamageToVelocityScale);
  GetFloatProp(mPropList.mpObject, 0x66d088c, m2HitSphereRadius);
  GetFloatProp(mPropList.mpObject, 0x4d7dbeb, mExtra144);
  GetFloatProp(mPropList.mpObject, 0x4d7dbec, mExtra148);
  GetFloatProp(mPropList.mpObject, 0x5ecd92b, mExtra14c);
  GetFloatProp(mPropList.mpObject, 0x5ecd938, mExtra150);
  GetFloatProp(mPropList.mpObject, 0x4d972e7, m2HitTerrainDamage);
  GetFloatProp(mPropList.mpObject, 0x4d972e9, m2MinAltitude);
  GetFloatProp(mPropList.mpObject, 0x6400ea3, m2HitSphereActiveDistance);
  GetFloatProp(mPropList.mpObject, 0x64001ad, m2MinExtent);
  GetFloatProp(mPropList.mpObject, 0x64001c2, m2BomberScale);
  GetFloatProp(mPropList.mpObject, 0x4daaefc, m2FighterScale);
  GetFloatProp(mPropList.mpObject, 0x4dc0642, m2UberTurretScale);
  GetFloatProp(mPropList.mpObject, 0x4dcfba7, m2AllyScale);
  m2PlumpDistance = true;
  GetBoolProp(mPropList.mpObject, 0x672734f, m2PlumpDistance);
  GetFloatProp(mPropList.mpObject, 0x5ecf67c, m2PlumpScale);
  GetFloatProp(mPropList.mpObject, 0x60212c5, m2PlumpTransitionScale);
  GetFloatProp(mPropList.mpObject, 0x60212c6, m2NPCPlumpScale);
  GetFloatProp(mPropList.mpObject, 0x60212c7, m2BasePlanetScale);
  GetFloatProp(mPropList.mpObject, 0x65ba2cc, m2VelocityFactor);
  GetFloatProp(mPropList.mpObject, 0x65ba2dc, m2VelocityFactorNPC);
  GetFloatProp(mPropList.mpObject, 0x65ba2f3, m2FighterVelocityFactor);
  GetFloatProp(mPropList.mpObject, 0x65ba2f6, m2UberTurretVelocityFactor);
}
