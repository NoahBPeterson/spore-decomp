// slice s005cf830 -- SP::cSPEditorSpine static spine tuning + the recursive spine block
// placement helper.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Field types/offsets below are the RETAIL ones (read off the disassembly); the generated
// SP/cSPEditorSpine.h carries the dev layout, whose data members from mMinBlockScale on sit
// 8 bytes higher and whose scalar types disagree (see symbols/slices/s005cf830.txt).
#include "types.h"

// ---------------------------------------------------------------------------------------------
// 0x005CF830  SP::cSPEditorSpine::LoadStaticTuning
// ---------------------------------------------------------------------------------------------

// Retail tuning defaults are 8 bytes lower than the dev header's: retail +0x48 is the
// metrics-enabled bool (default global kSpineHavokMetricsEnabled), +0x50 the solver-iteration
// count, and so on.  Types marked with a property type in the load chain are confirmed by the
// GetBool/GetInt/GetFloat call each property key is read with.
struct cPropRecord005cf830 {
  void* mUnk00;
  void* mUnk04[3];
  short mUnk10;
  short mTypeId;      // +0x12 -- property value type (1 bool, 9 int, 0xd float)
  bool* GetBool();    // 0x0041E920
  int* GetInt();      // 0x0041E990
  float* GetFloat();  // 0x0041EA70
};

struct cPropertyList005cf830 {
  virtual int AddRef();                                       // +0x00
  virtual int Release();                                      // +0x04
  virtual void p2(); virtual void p3(); virtual void p4();
  virtual void p5(); virtual void p6(); virtual void p7();
  virtual void p8();
  virtual bool GetProperty(unsigned int id, void** out);      // +0x24
  virtual void p10();
};

struct cIPropertyManager005cf830 {
  virtual void m0(); virtual void m1(); virtual void m2();
  virtual void m3(); virtual void m4(); virtual void m5();
  virtual void m6(); virtual void m7(); virtual void m8();
  virtual void m9(); virtual void m10();
  virtual bool GetPropertyList(unsigned int id, unsigned int group,
                               cPropertyList005cf830** out);  // +0x2c
};

cIPropertyManager005cf830* PropertyManager();      // 0x0067DE30
extern unsigned int g_SpineTuningGroup;            // 0x01517FD4
extern bool kSpineHavokMetricsEnabled;             // 0x015EE380

// The property list is held by an EA::AutoRefCount: its default constructor nulls the pointer,
// operator=(null) releases any previous object and the destructor releases the survivor.
template <typename T>
struct RefPtr005cf830 {
  T* mpObject;
  RefPtr005cf830() : mpObject(0) {}
  ~RefPtr005cf830() {
    if (mpObject) {
      T* pOld = mpObject;
      mpObject = 0;
      pOld->Release();
    }
  }
  RefPtr005cf830& operator=(T* p) {
    if (mpObject) {
      T* pOld = mpObject;
      mpObject = 0;
      pOld->Release();
    }
    mpObject = p;
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};

namespace SP {

class cSPEditorSpine {
 public:
  // @ 0x005CF830
  void LoadStaticTuning();
  void LoadDynamicTuning();  // 0x005CE300

  char mUnk00[0x48];
  bool mSpineHavokMetricsEnabled;                 // +0x48
  char mUnk49[3];
  float mSpineNewVertebraRelativeScale;           // +0x4c
  int mSpineHavokWorldNumSolverIters;             // +0x50
  int mSpineHavokWorldSimType;                    // +0x54
  float mSpineHavokWorldSolverTau;                // +0x58
  float mSpineHavokWorldSolverDamp;               // +0x5c
  float mSpineFrictionConstant;                   // +0x60
  float mSpineVertebraAllowedPenetrationDepth;    // +0x64
  float mSpineVertebraMaxMassProportion;          // +0x68
  float mSpineVertebraInertiaScale;               // +0x6c
  float mSpineVertebraHavokPaddingFactor;         // +0x70
  int mSpineMinCollisionDeadZoneDistance;         // +0x74
  bool mSpineUseFewerAxialConstraints;            // +0x78
  char mUnk79[3];
  float mSpineChainTau;                           // +0x7c
  float mSpineChainDamping;                       // +0x80
  float mSpineHingeAngularLimitsTauFactor;        // +0x84
  float mSpineHingeMinAngleLimit;                 // +0x88
  float mSpineHingeMaxAngleLimit;                 // +0x8c
  float mSpineHingeMinFlexFactor;                 // +0x90
  float mSpineHingeMaxFlexFactor;                 // +0x94
  float mSpineVertebraeScaleOfLeastFlexibility;   // +0x98
};

}  // namespace SP

// The default values are written in the order the retail compiler scheduled their stores, which
// is the order the source states them in: 0.2, 0.01, 10, 10, 3, 0.5, 0.5, -55deg, 45deg, 0.9,
// 0.3, then the metrics flag, 8, 4, 1.1, false, the dead-zone key, 1.1, 1.0, 1.1.
void SP::cSPEditorSpine::LoadStaticTuning() {
  mSpineFrictionConstant = 0.2f;
  mSpineVertebraAllowedPenetrationDepth = 0.01f;
  mSpineVertebraMaxMassProportion = 10.0f;
  mSpineVertebraInertiaScale = 10.0f;
  mSpineVertebraHavokPaddingFactor = 3.0f;
  mSpineChainTau = 0.5f;
  mSpineHingeAngularLimitsTauFactor = 0.5f;
  mSpineHingeMinAngleLimit = -0.9599311f;  // -55 degrees
  mSpineHingeMaxAngleLimit = 0.7853982f;   // pi/4
  mSpineHavokWorldSolverTau = 0.9f;
  mSpineHingeMinFlexFactor = 0.3f;
  mSpineHavokMetricsEnabled = kSpineHavokMetricsEnabled;
  mSpineHavokWorldNumSolverIters = 8;
  mSpineHavokWorldSimType = 4;
  mSpineHavokWorldSolverDamp = 1.1f;
  mSpineUseFewerAxialConstraints = false;
  mSpineMinCollisionDeadZoneDistance = 0x615c643;
  mSpineChainDamping = 1.1f;
  mSpineHingeMaxFlexFactor = 1.0f;
  mSpineVertebraeScaleOfLeastFlexibility = 1.1f;

  RefPtr005cf830<cPropertyList005cf830> props;
  cIPropertyManager005cf830* pManager = PropertyManager();
  props = (cPropertyList005cf830*)0;
  if (pManager->GetPropertyList(0xbef6f201, g_SpineTuningGroup, &props.mpObject)) {
    void* pProp;
    // Every lookup is guarded by a fresh "is the list still there?" test, and each guard is the
    // last statement of its enclosing block, so all of them share the same bail-out target.
    if (props) {
      if (props->GetProperty(0x7aee00e7, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 1)
        mSpineHavokMetricsEnabled = *((cPropRecord005cf830*)pProp)->GetBool();
      if (props) {
        if (props->GetProperty(0x628b4bf5, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 9)
          mSpineHavokWorldNumSolverIters = *((cPropRecord005cf830*)pProp)->GetInt();
        if (props) {
          if (props->GetProperty(0xd8fb24c0, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 9)
            mSpineHavokWorldSimType = *((cPropRecord005cf830*)pProp)->GetInt();
          if (props) {
            if (props->GetProperty(0xa5f5a154, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 0xd)
              mSpineHavokWorldSolverTau = *((cPropRecord005cf830*)pProp)->GetFloat();
            if (props) {
              if (props->GetProperty(0xdd658204, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 0xd)
                mSpineHavokWorldSolverDamp = *((cPropRecord005cf830*)pProp)->GetFloat();
              if (props) {
                if (props->GetProperty(0xb9da0713, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 1)
                  mSpineUseFewerAxialConstraints = *((cPropRecord005cf830*)pProp)->GetBool();
                if (props) {
                  if (props->GetProperty(0xb34fe5dc, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 0xd)
                    mSpineFrictionConstant = *((cPropRecord005cf830*)pProp)->GetFloat();
                  if (props) {
                    if (props->GetProperty(0x23179da5, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 0xd)
                      mSpineVertebraAllowedPenetrationDepth = *((cPropRecord005cf830*)pProp)->GetFloat();
                    if (props) {
                      if (props->GetProperty(0xba032ba7, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 0xd)
                        mSpineVertebraMaxMassProportion = *((cPropRecord005cf830*)pProp)->GetFloat();
                      if (props) {
                        if (props->GetProperty(0xb6b96595, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 0xd)
                          mSpineVertebraInertiaScale = *((cPropRecord005cf830*)pProp)->GetFloat();
                        if (props) {
                          if (props->GetProperty(0x8a450c3a, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 0xd)
                            mSpineVertebraHavokPaddingFactor = *((cPropRecord005cf830*)pProp)->GetFloat();
                          if (props) {
                            if (props->GetProperty(0x615c643, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 9)
                              mSpineMinCollisionDeadZoneDistance = *((cPropRecord005cf830*)pProp)->GetInt();
                            if (props) {
                              if (props->GetProperty(0xbcaa69c5, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 0xd)
                                mSpineChainTau = *((cPropRecord005cf830*)pProp)->GetFloat();
                              if (props) {
                                if (props->GetProperty(0x6b2f4d59, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 0xd)
                                  mSpineChainDamping = *((cPropRecord005cf830*)pProp)->GetFloat();
                                if (props) {
                                  if (props->GetProperty(0xb24a724a, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 0xd)
                                    mSpineHingeAngularLimitsTauFactor = *((cPropRecord005cf830*)pProp)->GetFloat();
                                  if (props) {
                                    if (props->GetProperty(0x8d4d3fcf, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 0xd)
                                      mSpineHingeMinAngleLimit = *((cPropRecord005cf830*)pProp)->GetFloat();
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    // The hinge limits come back in degrees and are converted to radians after the load.
    mSpineHingeMinAngleLimit = mSpineHingeMinAngleLimit * 0.017453292f;
    if (props) {
      if (props->GetProperty(0x1631804d, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 0xd)
        mSpineHingeMaxAngleLimit = *((cPropRecord005cf830*)pProp)->GetFloat();
    }
    mSpineHingeMaxAngleLimit = mSpineHingeMaxAngleLimit * 0.017453292f;
    if (props) {
      if (props->GetProperty(0xb05ca6b1, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 0xd)
        mSpineHingeMinFlexFactor = *((cPropRecord005cf830*)pProp)->GetFloat();
      if (props) {
        if (props->GetProperty(0xb5046f83, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 0xd)
          mSpineHingeMaxFlexFactor = *((cPropRecord005cf830*)pProp)->GetFloat();
        if (props) {
          if (props->GetProperty(0x5382e2d7, &pProp) && ((cPropRecord005cf830*)pProp)->mTypeId == 0xd)
            mSpineVertebraeScaleOfLeastFlexibility = *((cPropRecord005cf830*)pProp)->GetFloat();
        }
      }
    }
  }
  LoadDynamicTuning();
}

// ---------------------------------------------------------------------------------------------
// 0x005CFDE0  recursive spine block placement helper
// ---------------------------------------------------------------------------------------------

struct Vec3_005cfde0 {
  float x, y, z;
};

struct Mat3_005cfde0 {
  float m[9];
};

struct Block_005cfde0 {
  char mUnk00[0x48];
  float mPosX;       // +0x48
  float mPosY;       // +0x4c
  float mPosZ;       // +0x50
  char mUnk54[0xa8 - 0x54];
  Mat3_005cfde0 mOrientation;  // +0xa8 (3x3)
  char mUnkcc[0x340 - 0xcc];
  Block_005cfde0** mChildrenBegin;  // +0x340
  Block_005cfde0** mChildrenEnd;    // +0x344
  char mUnk348[0xdc8 - 0x348];
  unsigned int mFlags;              // +0xdc8
  void SetOrientation(Mat3_005cfde0 const& orientation, bool immediate);
  void SetPosition(Vec3_005cfde0 const& position, bool immediate);
};

// `block` is the block being placed, `offset` the block whose position anchors it, `refPos` the
// reference point the block's position is measured against, `orientation` the source frame and
// `outOffset` the caller's "the block moved by this much" output.  `mode` picks how the new
// position is derived: 0 offset only, 1 offset plus the rotator frame, 2 rebuild the frame from
// the current orientation first.
// @ 0x005CFDE0
void FUN_005cfde0(Block_005cfde0* block, Block_005cfde0* offset, Vec3_005cfde0* refPos,
                  int context, Mat3_005cfde0* orientation, Vec3_005cfde0* outOffset, int mode,
                  char writeOut) {
  Vec3_005cfde0 delta;
  delta.x = block->mPosX - refPos->x;
  delta.y = block->mPosY - refPos->y;
  delta.z = block->mPosZ - refPos->z;
  Vec3_005cfde0 out = delta;
  if (writeOut != 0) {
    *outOffset = out;
  }
  if (mode == 0) {
    Vec3_005cfde0 position;
    position.x = offset->mPosX + delta.x;
    position.y = offset->mPosY + delta.y;
    position.z = offset->mPosZ + delta.z;
    block->SetPosition(position, false);
  } else if (mode == 1) {
    // Push the block to where the reference frame says it ended up, then undo the caller's
    // reported offset so the delta is applied once.
    Vec3_005cfde0 rotated;
    rotated.x = orientation->m[0] * outOffset->x + orientation->m[3] * outOffset->y +
                orientation->m[6] * outOffset->z;
    rotated.y = orientation->m[1] * outOffset->x + orientation->m[4] * outOffset->y +
                orientation->m[7] * outOffset->z;
    rotated.z = orientation->m[2] * outOffset->x + orientation->m[5] * outOffset->y +
                orientation->m[8] * outOffset->z;
    Vec3_005cfde0 position;
    position.x = offset->mPosX + rotated.x + delta.x - outOffset->x;
    position.y = offset->mPosY + rotated.y + delta.y - outOffset->y;
    position.z = offset->mPosZ + rotated.z + delta.z - outOffset->z;
    block->SetPosition(position, false);
  } else if (mode == 2) {
    // New world frame = the current orientation in the source frame, then the block is placed
    // along the delta measured in that frame.
    float const* o = orientation->m;
    float const* b = block->mOrientation.m;
    Mat3_005cfde0 frame;
    frame.m[0] = o[0] * b[0] + o[3] * b[1] + o[6] * b[2];
    frame.m[1] = o[1] * b[0] + o[4] * b[1] + o[7] * b[2];
    frame.m[2] = o[2] * b[0] + o[5] * b[1] + o[8] * b[2];
    frame.m[3] = o[0] * b[3] + o[3] * b[4] + o[6] * b[5];
    frame.m[4] = o[1] * b[3] + o[4] * b[4] + o[7] * b[5];
    frame.m[5] = o[2] * b[3] + o[5] * b[4] + o[8] * b[5];
    frame.m[6] = o[0] * b[6] + o[3] * b[7] + o[6] * b[8];
    frame.m[7] = o[1] * b[6] + o[4] * b[7] + o[7] * b[8];
    frame.m[8] = o[2] * b[6] + o[5] * b[7] + o[8] * b[8];
    Mat3_005cfde0 orientationCopy = frame;
    block->SetOrientation(orientationCopy, false);
    Vec3_005cfde0 position;
    position.x = offset->mPosX + (orientation->m[0] * delta.x + orientation->m[6] * delta.z +
                                  orientation->m[3] * delta.y);
    position.y = offset->mPosY + (orientation->m[1] * delta.x + orientation->m[7] * delta.z +
                                  orientation->m[4] * delta.y);
    position.z = offset->mPosZ + (orientation->m[2] * delta.x + orientation->m[8] * delta.z +
                                  orientation->m[5] * delta.y);
    block->SetPosition(position, false);
  }
  int count = (int)((char*)block->mChildrenEnd - (char*)block->mChildrenBegin) >> 2;
  for (int i = 0; i < count; ++i) {
    Block_005cfde0* child = block->mChildrenBegin[i];
    int childMode = mode;
    if (writeOut != 0 && ((child->mFlags >> 0xb) & 1) != 0)
      childMode = 0;
    FUN_005cfde0(child, offset, refPos, context, orientation, outOffset, childMode, 0);
  }
}
